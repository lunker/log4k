//
// Created by voiceloco on 2017. 7. 21..
//

#include "iostream"
#include "src/Logger.h"

#include "src/logger_interface.h"

int main() {

    std::cout<<"Test log4k"<<std::endl;

    // set sink

    Logger logger;

    logger.init();
    logger.DEBUG("stat", "hi!");

    log4k_debug("adsf","22");
}