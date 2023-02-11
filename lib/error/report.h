//
// Created by Cesar Valdez on 09/02/2023.
//

#ifndef INTERPRETER_REPORT_H
#define INTERPRETER_REPORT_H

#include <iostream>

class Report{
private:
    static bool report(int line, std::string where, std::string msg){
        std::cout << "[line " << line << "] Error" << where << ": " + msg << std::endl;
        return true;
    }
public:
    static bool error(int line, std::string msg) {
        return report(line, "", msg);
    }
};

#endif //INTERPRETER_REPORT_H
