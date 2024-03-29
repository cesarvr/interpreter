//
// Created by Cesar Valdez on 09/02/2023.
//



#ifndef INTERPRETER_SCANNER_H
#define INTERPRETER_SCANNER_H

#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "../error/report.h"
#include "tokens.h"

class ReadBlock{
    ReadBlock(std::string ){
        
    }
};

int chrCounter(std::string& payload, char &&chr){
    int cnt = 0;
    for(auto c: payload){
        if(chr == c) cnt ++;
    }
    return cnt;
}

class Scanner {
    private:
        std::string source;
        std::vector<Token> tokens;
        int start=0, current=0, line=1;
        std::map<std::string, TokenType> keywords;
        
        bool isAlpha(const char& chr){
            return (chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z') ||
                chr == '_';
        }

        bool isAlphaNumeric(const char& chr){
            return isAlpha(chr) || isDigit(chr);
        }

        void identifier(){
            while(isAlphaNumeric(peek())) advance();

            addToken(IDENTIFIER);
        }

    public:
        Scanner(std::string source): source(source){
            keywords["and"] = AND;
            keywords["class"] = CLASS;
            keywords["else"] = ELSE;
            keywords["false"] = FALSE;
            keywords["for"] = FOR;
            keywords["fun"] = FUN;
            keywords["if"] =  IF;
            keywords["nil"] = NIL;
            keywords["or"] =  OR;
            keywords["print"] =  PRINT;
            keywords["return"] = RETURN;
            keywords["super"] =  SUPER;
            keywords["this"] =   THIS;
            keywords["true"] =   TRUE;
            keywords["var"] =    VAR;
            keywords["while"] =  WHILE;
        }

        bool isAtEnd() {
            return current >= source.size();
        }

        char advance() {
            return source[current++];
        }

        void addToken(TokenType type){
            addToken(type, Object{});
        }

        void addToken(TokenType type, Object literal){
            std::string text = source.substr(start, (current-start));
            tokens.push_back(Token{type, text, literal, line});
        }

        bool match(char expected) {
            if(isAtEnd()) return false;
            if(source[current] != expected) return false;

            current++;
            return true;
        }

        char peek() {
            if (isAtEnd()) return '\0';
            return source[current];
        }

        char peekNext() {
            if(source.size() <= current + 1) return '\0';
            return source[current + 1];
        }

        char peekPrevious(){
            if (isAtEnd()) return '\0';
            return source[current - 1];
        }

        void read_string() {
            while(peek() != '\"' && !isAtEnd()){
                if(peek() == '\n') line++;
                advance();
            }

            if(isAtEnd()) {
                Report::error(line, "Unterminated string.");
                return;
            }

            advance();

            //removing quotes and fetching the string.
            std::string str_value = source.substr(start+1, (current-(start+1))-1);

            addToken(STRING, str_value);
        }

        bool isDigit(char chr) {
            return chr >= '0' && chr <= '9';
        }


        void number() {
            while (isDigit(peek())) advance();
            if (peek() == '.' && isDigit(peekNext())) {
                // Consume the "."
                advance();

                while (isDigit(peek())) advance();
            }

            std::string number = source.substr(start, (current-start));
            addToken(NUMBER, Object{std::stod(number)});
        }

        void scanToken() {
            auto chr = advance();

            switch(chr){
                case '(': addToken(LEFT_PAREN); break;
                case ')': addToken(RIGHT_PAREN); break;
                case '{': addToken(LEFT_BRACE); break;
                case '}': addToken(RIGHT_BRACE); break;
                case ',': addToken(COMMA); break;
                case '.': addToken(DOT); break;
                case '-': addToken(MINUS); break;
                case '+': addToken(PLUS); break;
                case ';': addToken(SEMICOLON); break;
                case '*': addToken(STAR); break;
                case 'o': 
                          if(match('r')){
                              addToken(OR);
                          }
                case '!':
                          addToken(match('=') ? BANG_EQUAL : BANG);
                          break;
                case '=':
                          addToken(match('=') ? EQUAL_EQUAL : EQUAL);
                          break;
                case '<':
                          addToken(match('=') ? LESS_EQUAL : LESS);
                          break;
                case '>':
                          addToken(match('=') ? GREATER_EQUAL : GREATER);
                          break;
                case '/':
                          // A comment goes until the end of the line.
                          if (match('/')) {
                              while (peek() != '\n' && !isAtEnd())
                                  advance();
                          }else if(match('*')){
                              auto end_block = source.find("*/");
                              if(end_block == std::string::npos){
                                  Report::error(line, "Invalid or unexpected token.");
                                  break;
                              }
                              
                              auto block = source.substr(current, end_block);
                              current = static_cast<int>(end_block + 2);
                              line = line + chrCounter(block, '\n');
                              
                          } else {
                              addToken(SLASH);
                          }
                          break;
                case ' ':
                case '\r':
                case '\t':
                          // Ignore whitespace.
                          break;

                case '\n':
                          line++;
                          break;
                case '\"':
                          read_string();
                          break;

                default:
                          if(isDigit(chr)){
                              number();
                          }else if(isAlpha(chr)) {
                              identifier();
                          }else{
                              Report::error(line, "Unexpected character.");
                          }
                          break;
            }
        }
    
        int getCurrentLine(){
            return line;
        }

        std::vector<Token> scanTokens(){
            while(!isAtEnd()){
                start = current;
                scanToken();
            }

            tokens.push_back(Token{_EOF, "", Object{}, line});
            return tokens;
        }
};


std::vector<std::string> tokenizer(std::string basicString, char placeholder = ' '){
    auto size = basicString.size();
    std::vector<std::string> tokens;
    std::string buffer;
    for(int index=0; index<size; index++){
        if(basicString[index] != placeholder){
            buffer.push_back(basicString[index]);
        }else {
            tokens.push_back(buffer);
            buffer.clear();
        }
    }
    tokens.push_back(buffer);
    return tokens;
}


#endif //INTERPRETER_SCANNER_H
