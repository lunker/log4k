//
// Created by voiceloco on 2017. 7. 21..
//

#include "Logger.h"
#include "logger_interface.h"

extern "C" {

	Logger* global_logger=Logger::get_logger();

	void log4k_debug (const char* channel, const char* message){
		char* tmp="hello global logger!";

		global_logger->TEST_LOG(message);
	}

	void log4k_singletone(char* message){
		
	}
}
