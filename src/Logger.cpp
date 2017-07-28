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
#include <mutex>

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

std::mutex mtx;
Logger* Logger::instance = nullptr;
Logger::Logger() {
    std::cout<<"Logger ructor"<<std::endl;
    init();
}

Logger::~Logger() {
	std::cout<<"Destroy Logger"<<std::endl;
}

severity_level level_to_severity(guint level){
	switch(level){
		case 0:
			return debug;
			break;
		case 1:
			return info;
			break;
		case 2:
			return warning;
			break;
		case 3:
			return error;
			break;
	}
}

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

Logger* Logger::get_logger(){
	mtx.lock();
	if(instance==NULL) instance=new Logger();
	return instance;
}

static void
stat_formatter (logging::record_view const &rec,
                  logging::formatting_ostream &strm)
{
  auto date_time_formatter = expr::stream
                             << expr::format_date_time< boost::posix_time::ptime > ("TimeStamp",
                                 "%Y-%m-%d %H:%M:%S,%f");

  date_time_formatter (rec, strm) << " ";
  strm << "[" << std::to_string (getpid() ) << "]" << " ";
	strm << "[" << logging::extract< severity_level > ("Severity", rec) << "]" << " ";
  strm << logging::extract< std::string > ("Category", rec) << " ";
  strm << logging::extract< std::string > ("FileName", rec) << ":";
  strm << "[" << logging::extract< std::string > ("Function", rec) << "() " << "]" << " "; 
  strm << rec[expr::smessage];
}

static void
app_formatter (logging::record_view const &rec,
                  logging::formatting_ostream &strm)
{
	auto date_time_formatter = expr::stream
                             << expr::format_date_time< boost::posix_time::ptime > ("TimeStamp",
                                 "%Y-%m-%d %H:%M:%S,%f");

///  strm << "[" << date_time_formatter (rec, strm) << "]" << " ";
  date_time_formatter (rec, strm) << " ";
  strm << "[" << std::to_string (getpid() ) << "]" << " ";
	strm << "[" << logging::extract< severity_level > ("Severity", rec) << "]" << " ";
  strm << "[" << logging::extract< std::string > ("Category", rec) << "]" << " ";
  strm << "[" << logging::extract< std::string > ("FileName", rec) << "]" << " ";
  strm << "[" << logging::extract< std::string > ("Function", rec) << "() " << "]" << " "; 
  strm << rec[expr::smessage];
}

void Logger::init() {

    // std::string path ="/Users/voiceloco";
    std::string path ="/home/lunker/logs";
    int fileSize=10;
    int fileNumber=2;
    boost::shared_ptr< logging::core > core = logging::core::get();

    // text-backend for call history
    boost::shared_ptr< sinks::text_file_backend > stat_backend =
            boost::make_shared< sinks::text_file_backend > (
                    keywords::file_name = path + "/running/" + "stat_%Y-%m-%d.%5N" + ".log",
										keywords::open_mode = std::ios_base::app|std::ios_base::out,
                    keywords::rotation_size = fileSize * 1024 * 1024,
                    keywords::time_based_rotation = sinks::file::rotation_at_time_point (0, 0, 0)
            );
    // text-backend for kms logger
    boost::shared_ptr< sinks::text_file_backend > app_backend =
            boost::make_shared< sinks::text_file_backend > (
                    keywords::file_name = path + "/running/" + "app_%Y-%m-%d.%5N" + ".log",
										keywords::open_mode = std::ios_base::app|std::ios_base::out,
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
    stat_sink->set_formatter (&stat_formatter);
    app_sink->set_formatter (&app_formatter);
		
}

void Logger::DEBUG (std::string channel, std::string message) {
    if (channel.compare("stat") == 0){
        BOOST_LOG_SEV(stat_logger::get(), warning) << message;
    }
    else{
        BOOST_LOG_SEV(app_logger::get(), warning) << message;
    }
}

void Logger::LOG(std::string &level, std::string &message) {

}

void Logger::TEST_LOG( gchar* channel, guint level,  gchar* message, gchar* func_name) {
	m_logger_mt logger;
	if(strcmp(channel, "app") == 0 ){
		logger=app_logger::get();	
	}
	else{
		logger=stat_logger::get();	
		
	}

	BOOST_LOG_SEV(logger, level_to_severity (level) ) << "count : " << count;
	count++;

	BOOST_LOG_SEV (logger, level_to_severity(level) ) <<
      logging::add_value ("Category", "TODO::get category(gst object name)" ) <<
      logging::add_value ("FileName",
                          "TODO::get file name " ) <<
      logging::add_value ("Function", func_name) <<
      message;
}

void Logger::register_relation( gchar* p_name,  gchar* c_name){
	if(r_map.find(c_name) == r_map.end() ) { 
		// child element is not exist in relation map

		if(r_map.find(p_name) == r_map.end() ){
			// New parent element
			// Insert parent as root 
			r_map.insert(std::pair<gchar*, gchar*> (p_name, "none"));
		}

		r_map.insert(std::pair <gchar*, gchar*> (c_name, p_name) );
	}
	else {
		// lunker::TODO
		// duplicated register
		// throw error 
	}
}

gchar* Logger::find_root( gchar* element_name){
//	gboolean is_empty=true;
	gchar* parent;
	gchar* child=element_name;

	while(r_map.find(child) != r_map.end()){
//		is_empty=false;
		parent=r_map.find(child)->second;

		if(strcmp(parent, "none") != 0){
			// parent exist
			child=parent;
		}
		else{
			// child has no parent 
			// child is root 
			// return child element name
			return child;
		}
	}// iterate all relation map
}

void Logger::add_property( gchar* element_name,  gchar* key, gchar* value){

}

void Logger::enable_debug(){
	is_debug=TRUE;
}

void Logger::disable_debug(){
	is_debug=FALSE;
}

void release(){

}



/*
gboolean Logger::is_debug(){
	return is_debug;
}
*/


