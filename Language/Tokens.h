//
// Created by sean on 17/06/2020.
//

#ifndef GLYNTH_TOKENS_H
#define GLYNTH_TOKENS_H


enum class Token : int {
    KEYWORD_VAR,
    KEYWORD_WHILE,
    KEYWORD_IF,
    KEYWORD_YIELD,
    KEYWORD_EXIT,
    KEYWORD_OUTPUT,
    KEYWORD_MOVE,
    KEYWORD_TURN,

    KEYWORD_RANDFUN,
    KEYWORD_SENSEFUN,

    IDENTIFIER,
    NUMBER,

    SYM_ASSIGN,
    SYM_LBRACES,
    SYM_RBRACES,
    SYM_LPAREN,
    SYM_RPAREN,
    SYM_LBRACKET,
    SYM_RBRACKET,
    SYM_COLON,
    SYM_SEMICOLON,
    SYM_HASH,

    OP_GT,
    OP_GTE,
    OP_LT,
    OP_LTE,
    OP_EQ,
    OP_NE,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,

    OP_AND,
    OP_OR,
    //OP_NOT,

    END_OF_FILE = -1,
    ERROR = -2
};


#endif //GLYNTH_TOKENS_H
