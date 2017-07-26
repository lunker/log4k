//
// Created by voiceloco on 2017. 7. 21..
//

#include "Logger.h"
#include "logger_interface.h"

extern "C" {

    void log4k_debug (char* channel, char* message){
        Logger::TEST_LOG(message);
    }
}