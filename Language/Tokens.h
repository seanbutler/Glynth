//
// Created by sean on 17/06/2020.
//

#ifndef GLYNTH_TOKENS_H
#define GLYNTH_TOKENS_H


enum class Token : int {
    KEYWORD_VAR,
    KEYWORD_FUNC,
    KEYWORD_WHILE,
    KEYWORD_IF,
    KEYWORD_RETURN,
    KEYWORD_YIELD,
    KEYWORD_EXIT,

    IDENTIFIER,
    NUMBER,

    OP_GT,
    OP_LT,
    OP_EQ,
    OP_NE,
    OP_ASSIGN,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,

    SYM_LBRACES,
    SYM_RBRACES,
    SYM_LPAREN,
    SYM_RPAREN,
    SYM_LBRACKET,
    SYM_RBRACKET,
    SYM_COLON,
    SYM_SEMICOLON,

    END_OF_FILE = -1,
    ERROR = -2
};




#endif //GLYNTH_TOKENS_H
