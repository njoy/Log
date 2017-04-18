#ifndef NJOY_LOG
#define NJOY_LOG

#include <memory>

#define FMT_HEADER_ONLY
#include "fmt/format.h"
#include "fmt/ostream.h"

#define SPDLOG_FMT_EXTERNAL
#include "spdlog/spdlog.h"
#include "spdlog/sinks/dist_sink.h"
#include "spdlog/sinks/file_sinks.h"
#include "spdlog/sinks/ostream_sink.h"

namespace njoy {

class Log {
  static auto initialize_sink(){
    auto sinks = std::make_shared< spdlog::sinks::dist_sink_st >();
    sinks->add_sink( std::make_shared< spdlog::sinks::stdout_sink_mt >() );
    return sinks;
  }

  static auto& sink(){
    static auto sink_ptr = initialize_sink();
    return sink_ptr;
  }
  
  static auto initialize_logger(){
    auto instance = std::make_shared< spdlog::logger >("njoy", sink() );
    instance->set_pattern( "[%l] %v" );
    #ifndef NDEBUG
    instance->set_level( spdlog::level::debug );
    #endif
    return instance;
  }

  static auto& logger(){
    static auto instance = initialize_logger();
    return instance;
  }

  public:

  static void add_sink( std::ostream& os ){
    sink()->add_sink( std::make_shared
                      < spdlog::sinks::ostream_sink_st >( os ) );
  }

  static void add_sink( const std::string& fn ){
    sink()->add_sink( std::make_shared
                      < spdlog::sinks::simple_file_sink_st >( fn ) );
  }

  static void flush(){
    logger()->flush();
  }
  
  template< typename... Args >
  static void info( Args... args ){
    logger()->info( std::forward<Args>(args)... );
  }

#ifdef NDEBUG
  template< typename... Args >
  static void debug( Args... ){}
#else
  template< typename... Args >
  static void debug( Args... args ){
    logger()->debug( std::forward<Args>(args)... );
  }
#endif

  template< typename... Args >
  static void warning( Args... args ){
    logger()->warn( std::forward<Args>(args)... );
  }

  template< typename... Args >
  static void error( Args... args ){
    logger()->error( std::forward<Args>(args)... );
  }
};

}

#endif
