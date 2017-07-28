//
// Created by voiceloco on 2017. 7. 21..
//

#ifndef LOG4K_LOGGER_INTERFACE_H
#define LOG4K_LOGGER_INTERFACE_H

#include <glib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CHANNEL_APP "app"
#define CHANNEL_STAT "stat"
#define LEVEL_DEBUG 0
#define LEVEL_INFO 1
#define LEVEL_WARN 2
#define LEVEL_ERROR 3

#define APP_DEBUG(message) log4k_log(CHANNEL_APP, LEVEL_DEBUG, message, __FUNCTION__)
#define APP_WARNING(message) log4k_log(CHANNEL_APP, LEVEL_WARN, message, __FUNCTION__)
#define APP_INFO(message) log4k_log(CHANNEL_APP, LEVEL_INFO, message, __FUNCTION__)
#define APP_ERROR(message) log4k_log(CHANNEL_APP, LEVEL_ERROR, message, __FUNCTION__)

#define APP_DEBUG(message) log4k_log(CHANNEL_APP, LEVEL_DEBUG, message, __FUNCTION__)
#define APP_WARNING(message) log4k_log(CHANNEL_APP, LEVEL_WARN, message, __FUNCTION__)
#define APP_INFO(message) log4k_log(CHANNEL_APP, LEVEL_INFO, message, __FUNCTION__)
#define APP_ERROR(message) log4k_log(CHANNEL_APP, LEVEL_ERROR, message, __FUNCTION__)



typedef struct Logger Logger;

// static Logger* instance;
// Logger* instance;
void log4k_log(const gchar* channel, guint level, const gchar* message, const gchar* func_name);
void log4k_register_relation(gchar* p_name, gchar* c_name);
void log4k_add_property();
void log4k_set_property();

#ifdef __cplusplus
};
#endif


#endif //LOG4K_LOGGER_INTERFACE_H
