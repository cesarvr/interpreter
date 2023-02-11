#include <iostream>
#include <vector>
#include "lib/scanner.h"

using namespace std;

void runLoxScriptFile(char *string);

void showLoxPrompt();

void run(std::string basicString);

int main(int argc, char** argv) {
    std::cout << "Hello, World!" << std::endl;

    if(argc > 1){
        cout << "usage lox [script]";
        exit(1);
    }else if(argc == 1){
        runLoxScriptFile(*argv);
    }else{
        showLoxPrompt();
    }


    return 0;
}

void showLoxPrompt() {

    while(true){
        for (std::string line; std::getline(std::cin, line);) {
            std::cout << line << std::endl;
            if(line.empty()) break;
            run(line);
        }
    }
}


void run(string basicString) {
    auto tokens = tokenizer(basicString);
    for(auto token: tokens) {
        cout << "token: " << token << endl;
    }
}

void runLoxScriptFile(char *string) {

}
