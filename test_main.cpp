//
// Created by voiceloco on 2017. 7. 21..
//

#include "./src/logger.hpp"

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

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

typedef sinks::synchronous_sink< sinks::text_file_backend > sink_t;
boost::shared_ptr< sink_t > stat_sink;
boost::shared_ptr< sink_t > debug_sink;



int main() {

    std::cout<<"Test log4k"<<std::endl;

    // set sink

    // logging
    BOOST_LOG(stat_logger::get()) << "Test Stat logger";
    BOOST_LOG(debug_logger::get()) << "Test debug logger";

}