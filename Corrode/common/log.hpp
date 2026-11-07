/*
    Project Corrode
    common/log - Logger utility
*/
#pragma once

#include <string>
#include <iostream>

namespace Util{
    // Log a message to std::out 
    // TODO: Make option to log to file as well and add timestamp
    static void Log(std::string location, std::string message){
        std::cout << "[" << location << "] " << message << "\n"; 
    }
} // Util