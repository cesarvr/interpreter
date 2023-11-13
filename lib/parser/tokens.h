//
// Created by Cesar Valdez on 13/02/2023.
//

#ifndef INTERPRETER_TOKENS_H
#define INTERPRETER_TOKENS_H
#include <iostream>

const bool DEBUG = false;

enum TokenType {
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR, BANG,
    BANG_EQUAL, EQUAL, EQUAL_EQUAL, GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals.
    IDENTIFIER, STRING, NUMBER,

    // Keywords.
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE, _EOF,
};

class Object{
    std::string str;
    double number;

public:
    Object(){}
    Object(std::string _str): str(_str) {}
    Object(double num): number(num){}

    std::string getString(){
        return str;
    }

    double getDouble(){
        return number;
    }
};

class Token {
private:
    TokenType type;
    std::string lexeme;
    Object literal;
    int line;

public:
    Token(TokenType _type, std::string _lexeme, Object _literal, int _line):
            type{_type},
            lexeme(_lexeme),
            literal(_literal),
            line{_line}
    {}

    std::string toString(){
        std::stringstream ss;
        return ss.str();
    }

    std::string getLexeme(){
        return lexeme;
    }

    TokenType getType(){
        return type;
    }

    Object getLiteral(){
        return literal;
    }
};

#endif //INTERPRETER_TOKENS_H
