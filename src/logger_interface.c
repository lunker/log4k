//
// Created by voiceloco on 2017. 7. 21..
//

#include "Logger.h"
#include "logger_interface.h"

extern "C" {

	Logger* global_logger=Logger::get_logger();

	void log4k_debug (char* channel, char* message){
		char* tmp="hello global logger!";

		// instance->TEST_LOG(message);
		global_logger->TEST_LOG(tmp);
	}

	void log4k_singletone(char* message){
		
	}
}
