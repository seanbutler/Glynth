//
// Created by sean on 30/07/2020.
//

#include <future>
#include "Evolution.h"

namespace Genetics {

    Evolution::Evolution()
    {
        std::random_device rd;
        randEngine.seed(rd());
    }

    void Evolution::MutateIndividual(Agent* agent)
    {

        Mutagen mutagen;
        mutagen.AddMutation(new RandomizeComparisonMutation(0.5));
        mutagen.AddMutation(new RandomizeNumberMutation(0.5));
        mutagen.AddMutation(new RandomizeArithmeticMutation(0.5));

        for (auto &node : agent->parser.abstractSyntaxTree ) {
            MutateNodeAndChildren(node, mutagen);
        }

    }

    void Evolution::MutateNodeAndChildren(ASTNode *node, Mutagen& mutagen)
    {
        mutagen.Apply(node);
        for(auto &n : node->children)
        {
            MutateNodeAndChildren(n, mutagen);
        }
    }

    void Evolution::AddIndividual(Agent *newIndividual)
    {
        population.emplace_back(newIndividual);
    }

    void Evolution::AddIndividuals(const std::vector<Agent *>& newIndividuals)
    {
        for(auto agent : newIndividuals)
        {
            population.emplace_back(agent);
        }
    }


    // Returns the top percent (0-1) of the populations agents. If clearPopulation is set, all agents other than the
    // returned ones are deleted and the population is cleared out.
    std::vector<Agent *> Evolution::GetTopPopulationAgents(float percent, bool clearPopulation)
    {
        // Order population
        std::sort(population.begin(), population.end(), [](Individual a, Individual b){
           return a.fitness > b.fitness;
        });

        std::vector<Agent*> returnVec;
        returnVec.reserve((float)population.size()*percent);
        for(int i = 0; i < (int)((float)population.size()*percent); i++) {
            returnVec.push_back(population[i].agent);
        }
        if(clearPopulation)
        {
            for (int i = (int) ((float) population.size() * percent); i < population.size(); i++) {
                delete population[i].agent;
            }
            population.clear();
        }
        return returnVec;
    }

    /// Defines the fitness function that will be applied to each individual once per generation
    void Evolution::SetFitnessFunction(const std::function<float(Agent*)>& function)
    {
        fitnessFunction = function;
    }

    /// Defines the function that will be used to create the agent of each population member
    void Evolution::SetRandomiseFunction(const std::function<void(Agent*)> &function)
    {
        randomiseAgentVars = function;
    }

    /// Fills the population using the function set by SetInitFunction
    void Evolution::InitialisePopulation(int popSize, const std::string& agentFilePath)
    {
        for(int i = 0; i < popSize; i++)
        {
            auto agent = new HurtfulAgent();
            agent->Compile(agentFilePath);
            randomiseAgentVars(agent);
            population.emplace_back(agent);
        }
    }


    /// Creates a new population with random abstract syntax trees using a ramped half and half method.
    void Evolution::InitialiseRandomPopulation(int popSize, int maxDepth, int maxBranchWidth)
    {
        float rampedDepth = (float)maxDepth/4;
        float rampIncrement = (((float)maxDepth / 4) * 3) / (float)popSize;
        bool full = false;

        for(int i = 0; i< popSize; i++)
        {
            auto agent = new HurtfulAgent();
            agent->parser.GenerateRandomAST((int)rampedDepth, maxBranchWidth, full);
            randomiseAgentVars(agent);
            population.emplace_back(agent);
            full = !full;
            rampedDepth += rampIncrement;
        }
    }

    /// Randomises every member of the current population
    void Evolution::RandomisePopulation()
    {
        for(auto &I : population) {

            MutateIndividual(I.agent);
            I.scored = false;
        }
    }

    /// Calculates a fitness for each individual based on the designated fitness function
    void Evolution::AssessFitness()
    {

        std::vector<std::future<float>> futures;
        futures.reserve(population.size());
        for(auto &I : population) {
            //if(I.scored) continue;
            futures.push_back(std::async(std::launch::async, fitnessFunction, I.agent));
        }

        int i = 0;
        for(auto &I : population) {
            //if(I.scored) continue;
            futures[i].wait();
            I.fitness = futures[i].get();
            i++;
            // Allow even the worst individuals to have a small chance of reproducing
            if(I.fitness < 1)
                I.fitness = 1;
            I.scored = true;
        }
    }

    /// Takes the current population and applies crossover, reproduction and mutation to
    /// create and replace the current population with a new one
    void Evolution::GenerateNewPopulation(float crossover, float reproduction, float pointMutation, float branchMutation)
    {
        static int generation = -1;
        generation++;

        std::vector<Individual> newPopulation;
        std::discrete_distribution<int> typeDist {crossover, reproduction, pointMutation, branchMutation};

        // Use the fitness scores for each population as the weights for a probabilistic generator
        std::vector<int> weights;
        for(auto &pop : population)
        {
            weights.push_back(pop.fitness);
        }
        std::discrete_distribution<int> probDist (weights.begin(), weights.end());

        // Create the new population one at a time
        for(int i = 0; i < population.size(); i++) {
            // Pick a probabilistically random method to create a new population
            switch (typeDist(randEngine))
            {
                // Crossover
                case 0:
                {
                    Agent* a = population[probDist(randEngine)].agent;
                    Agent* b = nullptr;
                    do {
                        b = population[probDist(randEngine)].agent;
                    } while (*&b == *&a);
                    newPopulation.emplace_back();
                    newPopulation.back().agent = a->Cross(b);
                    break;
                }
                // Reproduction
                case 1:
                {
                    int copyIndex = probDist(randEngine);
                    newPopulation.push_back(population[copyIndex]);
                    newPopulation.back().agent = new Agent(*population[copyIndex].agent);
                    break;
                }
                // Point Mutation
                case 2:
                {
                    int copyIndex = probDist(randEngine);
                    newPopulation.push_back(population[copyIndex]);
                    newPopulation.back().agent = new Agent(*population[copyIndex].agent);
                    MutateIndividual(newPopulation.back().agent);
                    break;
                }
                // Branch Mutation
                case 3:
                {
                    Agent* a = population[probDist(randEngine)].agent;
                    Agent* b = new HurtfulAgent();
                    // TODO: Make this use the first agents depth and width rather than hardcoded 6/4
                    b->parser.GenerateRandomAST(6, 4, false);
                    newPopulation.emplace_back();
                    newPopulation.back().agent = a->Cross(b);
                    delete b;
                    break;
                }
            }
            randomiseAgentVars(newPopulation.back().agent);
            newPopulation.back().scored = false;
        }

        for(auto &pop : population)
        {
            delete pop.agent;
        }

        std::copy(newPopulation.begin(), newPopulation.end(), population.begin());
    }
}
