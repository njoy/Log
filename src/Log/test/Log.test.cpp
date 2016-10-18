#define CATCH_CONFIG_MAIN

#include <iostream>
#include <iterator>
#include <string>
#include <sstream>

#include "Log.hpp"
#include "catch.hpp"

TEST_CASE("Log"){
  std::string testString = "hello world";
  std::stringstream buffer;
  njoy::Log::add_sink( buffer );

  njoy::Log::info( testString );
  std::string resultString = buffer.str();
  REQUIRE( resultString == ( "[info] " + testString  +'\n' ) );

  buffer = std::stringstream();
  njoy::Log::warning( testString );
  resultString = buffer.str();
  REQUIRE( resultString == ( "[warning] " + testString  +'\n' ) );

  buffer = std::stringstream();
  njoy::Log::error( testString );
  resultString = buffer.str();
  REQUIRE( resultString == ( "[error] " + testString  +'\n' ) );

  buffer = std::stringstream();
  njoy::Log::debug( testString );
  resultString = buffer.str();
#ifdef NDEBUG
  REQUIRE( resultString == ( "" ) );
#else
  REQUIRE( resultString == ( "[debug] " + testString  +'\n' ) );
#endif
  
  auto collectFileContents = [](){
    std::stringstream ss;
    std::ifstream fs("sink.txt", std::ifstream::in);
    REQUIRE( fs );
    ss << fs.rdbuf();
    return ss.str();
  };

  njoy::Log::add_sink( "./sink.txt" );
  njoy::Log::info( testString );
  njoy::Log::flush();
    
  resultString = collectFileContents();
  REQUIRE( resultString == ( "[info] " +  testString + '\n' ) );
  REQUIRE( not std::remove("./sink.txt") );
}
