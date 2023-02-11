//
// Created by Cesar Valdez on 09/02/2023.
//



#ifndef INTERPRETER_SCANNER_H
#define INTERPRETER_SCANNER_H

#include <iostream>
#include <string>
#include <vector>

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
