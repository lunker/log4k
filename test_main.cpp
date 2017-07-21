//
// Created by voiceloco on 2017. 7. 21..
//

#include "iostream"
#include "src/Logger.hpp"

int main() {

    std::cout<<"Test log4k"<<std::endl;

    // set sink

    Logger logger;

    logger.init();
    logger.DEBUG("stat", "hi!");

}