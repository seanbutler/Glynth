//
// Created by sean on 06/08/2020.
//

#include "./Agent.h"
#include "../Utils/RandomNumberGenerator.h"
#include <vector>

//static std::vector<std::pair<int, int>> DetectableAgentType::positionTable;

/// Recursively generates a random AST. The tree will be at most maxTreeDepth nodes in depth, with each block
/// generating between 1 and maxBranchWidth branches. If full is ture the full method will be used to populate,
/// otherwise grow will be used.
void Agent::GenerateRandomAST(int maxTreeDepth, int maxBranchWidth, bool full)
{
    TreeState state;
    state.maxDepth = maxTreeDepth;
    state.maxBranchWidth = maxBranchWidth;
    state.full = full;
    for(int i = 0; i < util::RandomNumberGenerator::RandNum(1, maxBranchWidth); i++)
    {
        parser.abstractSyntaxTree.push_back(GenerateBlockChild(state));
    }
}

/// Randomly creates a new if or while node and a new block node
ASTNode* Agent::GenerateBlock(TreeState state)
{
    state.currentDepth += 2;
    ASTNode* node = nullptr;
    if(util::RandomNumberGenerator::RandNum(0,1) == 0)
    {
        node = new IfStatementAST(GenerateCondition(state), new BlockAST());
    }
    else
    {
        node = new WhileStatementAST(GenerateCondition(state), new BlockAST());
    }

    for(int i = 0; i < util::RandomNumberGenerator::RandNum(0, state.maxBranchWidth); i++)
    {
        node->children[1]->children.push_back(GenerateBlockChild(state));
    }
    return node;
}

/// Creates a random condition node, either binary comparison or a flat number (true/false)
ASTNode * Agent::GenerateCondition(TreeState state)
{
    switch (util::RandomNumberGenerator::RandNum(0,state.currentDepth < state.maxDepth ? 1 : 0))
    {
        case 0:
            return GenerateNum(state);
        case 1: // Case 1 is ignored when depth limit is reached
            return GenerateBinComp(state);
        default: // Should never hit default
            return nullptr;
    }
}

/// Creates a random binary comparison node: > >= < <= == !=
ASTNode * Agent::GenerateBinComp(TreeState state)
{
    state.currentDepth++;
    switch (util::RandomNumberGenerator::RandNum(0,5))
    {
        case 0:
            return new BinOperandAST(Token::OP_GT, GenerateNum(state), GenerateNum(state));
        case 1:
            return new BinOperandAST(Token::OP_GTE, GenerateNum(state), GenerateNum(state));
        case 2:
            return new BinOperandAST(Token::OP_LT, GenerateNum(state), GenerateNum(state));
        case 3:
            return new BinOperandAST(Token::OP_LTE, GenerateNum(state), GenerateNum(state));
        case 4:
            return new BinOperandAST(Token::OP_EQ, GenerateNum(state), GenerateNum(state));
        case 5:
            return new BinOperandAST(Token::OP_NE, GenerateNum(state), GenerateNum(state));
        default: // Should never hit default
            return nullptr;
    }
}

/// Creates a new variable node. Note state is passed by ref here since it needs to add the variable to scopedVars
ASTNode * Agent::GenerateVar(TreeState& state)
{
    state.currentDepth++;
    std::string name = "v" + std::to_string(varCount++);
    auto node = new AssignmentStatementAST(new IdentifierAST(name), GenerateNum(state));
    state.scopedVars.push_back(name);
    return node;
}

/// Creates a new variable assignment node, assigning a random number as defined by GenerateNum() to a random variable
/// that is in scope for this part of the tree
ASTNode * Agent::GenerateAssignment(TreeState state)
{
    state.currentDepth++;
    int randInd = util::RandomNumberGenerator::RandNum(0, (int)state.scopedVars.size()-1);
    return new AssignmentStatementAST(new IdentifierAST(state.scopedVars[randInd]), GenerateNum(state));
}


/// Creates a random numeric value, either a static number, a variable, or a result of binary operators on numbers and
/// variables. Note this is also recursive, as each number used in the binary operators calls this function again.
ASTNode * Agent::GenerateNum(TreeState state)
{
    int randInd = util::RandomNumberGenerator::RandNum(0, (int)state.scopedVars.size()-1);
    switch (util::RandomNumberGenerator::RandNum(0, state.currentDepth < state.maxDepth ? 3 : 2)) {
        case 0:
            state.currentDepth++;
            return new NumberAST(util::RandomNumberGenerator::RandNum(0, 100));
        case 1:
            if(state.scopedVars.empty())
                return GenerateNum(state);
            return new IdentifierAST(state.scopedVars[randInd]);
        case 2:
            return new AlienVarAST();
        case 3: // Case 3 is ignored when depth limit is reached
            return GenerateArithBin(state);
        default: // Should never hit default
            return nullptr;
    }
}


/// Creates a random arithmetic binary operator node: * / + -
ASTNode * Agent::GenerateArithBin(TreeState state)
{
    state.currentDepth++;
    switch (util::RandomNumberGenerator::RandNum(0, 3)) {
        case 0:
            return new BinOperandAST(Token::OP_MUL, GenerateNum(state), GenerateNum(state));
        case 1:
            return new BinOperandAST(Token::OP_DIV, GenerateNum(state), GenerateNum(state));
        case 2:
            return new BinOperandAST(Token::OP_ADD, GenerateNum(state), GenerateNum(state));
        case 3:
            return new BinOperandAST(Token::OP_SUB, GenerateNum(state), GenerateNum(state));
        default: // Should never hit default
            return nullptr;
    }
}

/// Creates a random AST Node that is legal as a child of a block
ASTNode* Agent::GenerateBlockChild(TreeState state)
{
    switch (util::RandomNumberGenerator::RandNum(0, state.currentDepth < state.maxDepth ? 3 : 2)) {
        case 0:
            return GenerateVar(state);
        case 1:
            if((int)state.scopedVars.size() > 0)
                return GenerateAssignment(state);
            else
                GenerateBlockChild(state); // If no variables are in scope, then just re-roll
        case 2:
            state.currentDepth++;
            return new MoveAST(GenerateNum(state));
        case 3: // Case 3 is ignored when depth limit is reached
            return GenerateBlock(state);
        default: // Should never hit default
            return nullptr;

    }
}