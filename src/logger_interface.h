//
// Created by voiceloco on 2017. 7. 21..
//

#ifndef LOG4K_LOGGER_INTERFACE_H
#define LOG4K_LOGGER_INTERFACE_H

//#include <glib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LOG(message) log4k_debug(message,message)

typedef struct Logger Logger;

// static Logger* instance;
// Logger* instance;

void log4k_debug(const char* level, const char * message);
void log4k_singleton(char* message);

#ifdef __cplusplus
};
#endif





#endif //LOG4K_LOGGER_INTERFACE_H
