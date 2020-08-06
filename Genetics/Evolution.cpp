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
        for(auto &n : node->children)
        {
            MutateNodeAndChildren(n, mutagen);
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
            agent->Assemble();
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
            I.agent->alienVars.values = varsCopy;
            I.scored = true;
        }
    }

    /// Returns a deep copy of any given agent
    Agent * Evolution::CopyAgent(Agent *original)
    {
        auto copy = new Agent(*original);
        for(int i = 0; i < original->parser.abstractSyntaxTree.size(); i++)
        {
            CopyNodeAndChildren(original->parser.abstractSyntaxTree[i], copy->parser.abstractSyntaxTree[i]);
        }
        copy->Assemble();
        return copy;
    }

    /// Recursive function used to create deep copies of ASTNodes
    void Evolution::CopyNodeAndChildren(ASTNode *&original, ASTNode *&copy)
    {
        //copy = new ASTNode(*original);
        // Temp fix to allow for deep copies
        if(dynamic_cast<RandFuncAST*>(original))
            copy = new RandFuncAST(*dynamic_cast<RandFuncAST*>(original));
        else if(dynamic_cast<BinOperandAST*>(original))
            copy = new BinOperandAST(*dynamic_cast<BinOperandAST*>(original));
        else if(dynamic_cast<WhileStatementAST*>(original))
            copy = new WhileStatementAST(*dynamic_cast<WhileStatementAST*>(original));
        else if(dynamic_cast<IfStatementAST*>(original))
            copy = new IfStatementAST(*dynamic_cast<IfStatementAST*>(original));
        else if(dynamic_cast<AssignmentStatementAST*>(original))
            copy = new AssignmentStatementAST(*dynamic_cast<AssignmentStatementAST*>(original));
        else if(dynamic_cast<AlienVarAST*>(original))
            copy = new AlienVarAST(*dynamic_cast<AlienVarAST*>(original));
        else if(dynamic_cast<BlockAST*>(original))
            copy = new BlockAST(*dynamic_cast<BlockAST*>(original));
        else if(dynamic_cast<IdentifierAST*>(original))
            copy = new IdentifierAST(*dynamic_cast<IdentifierAST*>(original));
        else if(dynamic_cast<MoveAST*>(original))
            copy = new MoveAST(*dynamic_cast<MoveAST*>(original));
        else if(dynamic_cast<NumberAST*>(original))
            copy = new NumberAST(*dynamic_cast<NumberAST*>(original));
        else if(dynamic_cast<OutputAST*>(original))
            copy = new OutputAST(*dynamic_cast<OutputAST*>(original));
        else if(dynamic_cast<VariableDeclarationAST*>(original))
            copy = new VariableDeclarationAST(*dynamic_cast<VariableDeclarationAST*>(original));
        else if(dynamic_cast<YieldAST*>(original))
            copy = new YieldAST(*dynamic_cast<YieldAST*>(original));
        // Temp fix to allow for deep copies

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
            randomiseAgentVars(newPopulation.back().agent);
        }

        for(auto &pop : population)
        {
            delete pop.agent;
        }

        std::copy(newPopulation.begin(), newPopulation.end(), population.begin());
    }
}
