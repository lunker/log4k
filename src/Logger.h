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

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;


enum severity_level {
    error,
    warning,
    fixme,
    info,
    debug,
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
    Logger();
    void DEBUG(std::string channel, std::string message);
    void INFO();
    void LOG(std::string &level, std::string &message);
    static void TEST_LOG(char* message);
private:
    m_logger_mt test_logger;
};
namespace test {
    inline m_logger_mt test_logger2(keywords::channel="test");

    void test_logger2_debug(char* message);
}