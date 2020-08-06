//
// Created by sean on 30/07/2020.
//

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
        //mutagen.AddMutation(new RandomizeNumberMutation(0.5));
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

    // Returns the top percent (0-1) of the populations agents
    std::vector<Agent *> Evolution::GetTopPopulationAgents(float percent)
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
    void Evolution::InitialisePopulation(int popSize, AgentType agentType, const std::string& agentFilePath)
    {
        for(int i = 0; i < popSize; i++)
        {
            auto agent = new Agent(agentType);
            agent->Compile(agentFilePath);
            randomiseAgentVars(agent);
            population.emplace_back(agent);
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
        for(auto &I : population) {
            if(I.scored) continue;
            // Make a copy of the agents state so it can be reverted after fitness test
            auto varsCopy = I.agent->alienVars.values;
            I.fitness = fitnessFunction(I.agent);
            // Allow even the worst individuals to have a small chance of reproducing
            if(I.fitness < 1)
                I.fitness = 1;
            I.agent->alienVars.values = varsCopy;
            I.scored = true;
        }
    }

    /// Takes the current population and applies crossover, reproduction and mutation to
    /// create and replace the current population with a new one
    void Evolution::GenerateNewPopulation(float crossover, float reproduction, float mutation)
    {
        std::vector<Individual> newPopulation;
        std::discrete_distribution<int> typeDist {crossover, reproduction, mutation};

        // Use the fitness scores for each population as the weights for a probabilistic generator
        std::vector<int> weights;
        for(auto &pop : population)
        {
            weights.push_back(pop.fitness);
        }
        std::discrete_distribution<int> probDist (weights.begin(), weights.end());

        // Create the new population one at a time
        for(int i = 0; i < population.size(); i++)
        {
            // Pick a probabilistically random method to create a new population
            switch (typeDist(randEngine))
            {
                // Crossover
                case 0:
                {

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
                // Mutation
                case 2:
                {
                    int copyIndex = probDist(randEngine);
                    newPopulation.push_back(population[copyIndex]);
                    newPopulation.back().agent = new Agent(*population[copyIndex].agent);
                    MutateIndividual(newPopulation.back().agent);
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
