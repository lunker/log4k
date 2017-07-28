//
// Created by voiceloco on 2017. 7. 21..
//

#ifndef LOG4K_LOGGER_HPP
#define LOG4K_LOGGER_HPP

//#include <glib.h>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>

#include <boost/log/sources/basic_logger.hpp>

#include <glib.h>
#include <map>

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;


enum severity_level {
    debug,
    info,
    warning,
    error,
    fixme,
    trace,
    undefined
};

typedef src::severity_channel_logger_mt <
        severity_level,     // the type of the severity level
        std::string         // the type of the channel name
> m_logger_mt;


BOOST_LOG_INLINE_GLOBAL_LOGGER_INIT (stat_logger, m_logger_mt)
{
    m_logger_mt stat_logger (keywords::channel = "stat");

    return stat_logger;
}

BOOST_LOG_INLINE_GLOBAL_LOGGER_INIT (app_logger, m_logger_mt)
{
    m_logger_mt app_logger (keywords::channel = "app");

    return app_logger;
}

#endif //LOG4K_LOGGER_HPP

class Logger {

public:
	static void init();
	static Logger* get_logger();

	void DEBUG(std::string channel, std::string message);
	void INFO();
	void LOG(std::string &level, std::string &message);
	void TEST_LOG( gchar* channel, guint level, gchar* message, gchar* func_name);
	
	void register_relation(gchar* p_name, gchar* c_name);
	void add_property(gchar* element_name, gchar* key, gchar* value);
	gchar* find_root(gchar* element_name);

	/*	logging */
	void log_with_level();

	/* set log4k debug mode*/
	void enable_debug();
	void disable_debug();
//	void is_debug();

private:

	static Logger* instance;

	gboolean is_debug=FALSE;
	gint count=1;
	std::map<gchar*, gchar* > r_map; // key : child_name, value: parent_name
	std::map<gchar*, std::map<gchar*, gchar*>> prop_map;// hold property 

	Logger();
	~Logger();
	void finalize();
}; // end Class

