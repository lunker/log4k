//
// Created by voiceloco on 2017. 7. 21..
//

#ifndef LOG4K_LOGGER_INTERFACE_H
#define LOG4K_LOGGER_INTERFACE_H

//#include <glib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Logger Logger;

//void log4k_debug(gchar* level, gchar * message);

void log4k_debug(char* level, char * message);

#ifdef __cplusplus
};
#endif





#endif //LOG4K_LOGGER_INTERFACE_H
