//
// Created by voiceloco on 2017. 7. 21..
//

#include "Logger.h"

#include <boost/format.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/channel_feature.hpp>
#include <boost/log/sources/channel_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <sys/types.h>
#include <unistd.h>

extern "C" {
//#include "../interface/logger_interface.h"
}

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

typedef sinks::synchronous_sink< sinks::text_file_backend > sink_t;
boost::shared_ptr< sink_t > stat_sink;
boost::shared_ptr< sink_t > app_sink;

#define WRITE(LOGGER, SEVERITY,MSG) BOOST_LOG_SEV(LOGGER, SERVERITY) << MSG

void init_file_collecting (boost::shared_ptr< sink_t > sink,
                           const std::string &path,
                           int fileSize,
                           int fileNumber)
{
    sink->locked_backend()->set_file_collector (sinks::file::make_collector (
            keywords::target = path,
            keywords::max_size = (fileSize * fileNumber) * 1024 * 1024,
            keywords::min_free_space = fileSize * 1024 * 1024
    ) );
}

Logger::Logger() {
    std::cout<<"Logger Constructor"<<std::endl;
    init();
}

void Logger::init() {
    std::string path ="/Users/voiceloco";
    int fileSize=10;
    int fileNumber=5;
    boost::shared_ptr< logging::core > core = logging::core::get();

    // text-backend for call history
    boost::shared_ptr< sinks::text_file_backend > stat_backend =
            boost::make_shared< sinks::text_file_backend > (
                    keywords::file_name = path + "/running/" + "stat_%Y-%m-%d_%H-%M-%S.%5N.pid" +
                                          std::to_string (getpid() ) + ".log",
                    keywords::rotation_size = fileSize * 1024 * 1024,
                    keywords::time_based_rotation = sinks::file::rotation_at_time_point (0, 0, 0)
            );
    // text-backend for kms logger
    boost::shared_ptr< sinks::text_file_backend > app_backend =
            boost::make_shared< sinks::text_file_backend > (
                    keywords::file_name = path + "/running/" + "app_%Y-%m-%d_%H-%M-%S.%5N.pid" +
                                          std::to_string (getpid() ) + ".log",
                    keywords::rotation_size = fileSize * 1024 * 1024,
                    keywords::time_based_rotation = sinks::file::rotation_at_time_point (0, 0, 0)
            );

    /* Enable auto-flushing after each log record written */
    stat_backend->auto_flush (true);
    app_backend->auto_flush (true);

    stat_sink = boost::shared_ptr< sink_t > (new sink_t (stat_backend) );
    app_sink = boost::shared_ptr< sink_t > (new sink_t (app_backend) );

    stat_sink->set_filter (
            expr::has_attr< std::string > ("Channel") &&
            expr::attr< std::string > ("Channel") == "stat"
    );
    app_sink->set_filter (
            expr::has_attr< std::string > ("Channel") &&
            expr::attr< std::string > ("Channel") == "app"
    );

    /* Set up where the rotated files will be stored */
    init_file_collecting (stat_sink, path + "/logs", fileSize, fileNumber);
    init_file_collecting (app_sink, path + "/logs", fileSize, fileNumber);


    /* Upon restart, scan the directory for files matching the file_name pattern */
    stat_sink->locked_backend()->scan_for_files();
    app_sink->locked_backend()->scan_for_files();

    core->add_sink (stat_sink);
    core->add_sink (app_sink);

    // set formatter to sink
//    stat_sink->set_formatter (&system_formatter);
}



void Logger::DEBUG (std::string channel, std::string message) {
    if (channel.compare("stat")){
        BOOST_LOG_SEV(stat_logger::get(), warning) << message;
    }
    else{
        BOOST_LOG_SEV(app_logger::get(), warning) << message;
    }
}

void Logger::LOG(std::string &level, std::string &message) {

}

void Logger::TEST_LOG(char* message) {
    init();
    BOOST_LOG_SEV(app_logger::get(), warning) << "WOWOWOWOWOWOWOW";
    BOOST_LOG_SEV(app_logger::get(), warning) << std::string(message);
}

