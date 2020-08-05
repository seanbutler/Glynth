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
        //mutagen.AddMutation(new RandomizeArithmeticMutation(0.5));

        for (auto &node : agent->parser.abstractSyntaxTree ) {
            MutateNodeAndChildren(node, mutagen);
        }
    }

    void Evolution::MutateNodeAndChildren(ASTNode *node, Mutagen& mutagen)
    {
        mutagen.Apply(node);
        for(auto &node : node->children)
        {
            MutateNodeAndChildren(node, mutagen);
        }
    }

    void Evolution::AddIndividual(Agent *newIndividual)
    {
        population.emplace_back(newIndividual);
    }

    std::vector<Agent *> Evolution::GetPopulationAgents()
    {
        std::vector<Agent*> returnVec;
        for(auto &I : population) {
            returnVec.push_back(I.agent);
        }
        return returnVec;
    }

    /// Defines the fitness function that will be applied to each individual once per generation
    void Evolution::SetFitnessFunction(const std::function<float(Agent*)>& function)
    {
        fitnessFunction = function;
    }

    /// Defines the function that will be used to create the agent of each population member
    void Evolution::SetInitFunction(const std::function<Agent*()> &function)
    {
        initFunction = function;
    }

    /// Fills the population using the function set by SetInitFunction
    void Evolution::InitialisePopulation(int popSize)
    {
        for(int i = 0; i < popSize; i++)
            population.emplace_back(initFunction());
    }

    /// Randomises every member of the current population
    void Evolution::RandomizePopulation()
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
            I.agent->alienVars.values = varsCopy;
            I.scored = true;
        }
    }

    /// Returns a deep copy of any given agent
    Agent * Evolution::CopyAgent(Agent *original)
    {
        Agent* copy = new Agent(*original);
        for(int i = 0; i < original->parser.abstractSyntaxTree.size(); i++)
        {
            CopyNodeAndChildren(original->parser.abstractSyntaxTree[i], copy->parser.abstractSyntaxTree[i]);
        }

        return copy;
    }

    /// Recursive function used to create deep copies of ASTNodes
    void Evolution::CopyNodeAndChildren(ASTNode *&original, ASTNode *&copy)
    {
        copy = new ASTNode(*original);
        if(!original->children.empty())
        {
            for(int i = 0; i < original->children.size(); i++)
            {
                CopyNodeAndChildren(original->children[i], copy->children[i]);
            }
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
            // Pick a random (probabilistic) method to create a new population
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
                    newPopulation.back().agent = CopyAgent(population[copyIndex].agent);
                    break;
                }
                // Mutation
                case 2:
                {
                    int copyIndex = probDist(randEngine);
                    newPopulation.push_back(population[copyIndex]);
                    newPopulation.back().agent = CopyAgent(population[copyIndex].agent);
                    MutateIndividual(newPopulation.back().agent);
                    break;
                }
            }
        }

        for(auto &pop : population)
        {
            delete pop.agent;
        }

        std::copy(newPopulation.begin(), newPopulation.end(), population.begin());
    }
}
