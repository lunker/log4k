//
// Created by voiceloco on 2017. 7. 21..
//

#include "../src/Logger.hpp"
#include "logger_interface.h"

extern "C" {

    void log4k_debug (gchar* channel, gchar* message){
        Logger.DEBUG("stat", message);
    }

}