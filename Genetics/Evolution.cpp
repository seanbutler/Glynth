//
// Created by sean on 30/07/2020.
//

#include "Evolution.h"

namespace Genetics {

    void Evolution::MutateIndividual(Agent* agent)
    {

        Mutagen mutagen;
        mutagen.AddMutation(new RandomizeComparisonMutation(0.5));
        //mutagen.AddMutation(new RandomizeNumberMutation(0.5));
        //mutagen.AddMutation(new RandomizeArithmeticMutation(0.5));

        for (auto node : agent->parser.abstractSyntaxTree ) {
            MutateNodeAndChildren(node, mutagen);
        }
    }

    void Evolution::MutateNodeAndChildren(ASTNode *node, Mutagen& mutagen)
    {
        mutagen.Apply(node);
        for(auto node : node->children)
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
        for(auto I : population) {
            returnVec.push_back(I.agent);
        }
        return returnVec;
    }

    void Evolution::SetFitnessFunction(const std::function<float(Agent*)>& function)
    {
        fitnessFunction = function;
    }

    void Evolution::MutatePopulation() {

        for(auto I : population) {
            MutateIndividual(I.agent);
            I.scored = false;
        }
    }

    void Evolution::AssessFitness()
    {
        for(auto I : population) {
            if(I.scored) continue;
            // Make a copy of the agents state so it can be reverted after fitness test
            auto varsCopy = I.agent->alienVars.values;
            I.fitness = fitnessFunction(I.agent);
            I.agent->alienVars.values = varsCopy;
            I.scored = true;
        }

        // Order the population from most to least fit
        std::sort(population.begin(), population.end(), [](Individual a, Individual b) {
            return a.fitness > b.fitness;
        });
    }

    Agent * Evolution::CopyAgent(Agent *original)
    {
        Agent* copy = new Agent(*original);
        for(int i = 0; i < original->parser.abstractSyntaxTree.size(); i++)
        {
            CopyNodeAndChildren(original->parser.abstractSyntaxTree[i], copy->parser.abstractSyntaxTree[i]);
        }
        return copy;
    }

    ASTNode * Evolution::CopyNodeAndChildren(ASTNode *&original, ASTNode *&copy)
    {

    }
}
