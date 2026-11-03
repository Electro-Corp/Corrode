/*
    Project Corrode Argument parser
    (stolen from another project of mine: https://github.com/Electro-Corp/NetworkTools)
*/
#pragma once

#include <string>
#include <cstring>
#include <iostream>

// Get variable in command line
static std::string getParam(char* command, int args, char* argv[]){
    for(int i = 0; i < args; i++){
        if(strcmp(command, argv[i]) == 0){
            if(i + 1 < args){
                return std::string{argv[i + 1]};
            }else{
                return std::string{""};
            }
        }
    }
    return "";
}

// Does param exist
static int doesParamExist(char* command, int args, char* argv[]){
    for(int i = 0; i < args; i++){
        if(strcmp(command, argv[i]) == 0){
            return 1;
        }
    }
    return 0;
}