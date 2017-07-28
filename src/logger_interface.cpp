//
// Created by voiceloco on 2017. 7. 21..
//

#include "Logger.h"
#include "logger_interface.h"

extern "C" {

	Logger* global_logger=Logger::get_logger();

	void log4k_log (const gchar* channel, guint level, const char* message, const gchar* func_name){
		global_logger->TEST_LOG((char* )channel, level,(char*) message, (char*) func_name);
	}

	void log4k_register_relation(gchar* p_name, gchar* c_name){
		global_logger->register_relation(p_name, c_name);
	}
	
	void log4k_set_property(){

	}
	void log4k_add_property(){

	}
}
