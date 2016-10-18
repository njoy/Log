#define CATCH_CONFIG_MAIN

#include <iostream>
#include <iterator>
#include <string>
#include <sstream>

#include "Log.hpp"
#include "catch.hpp"

TEST_CASE( "Log test" ){
  std::string testString = "hello world";

  SECTION("info logging"){
    std::stringstream buffer;
    njoy::Log::add_sink( buffer );
    njoy::Log::info( testString );
    std::string resultString = buffer.str();
    REQUIRE( resultString == ( "[info] " + testString  +'\n' ) );
  }

  SECTION("warning logging"){
    std::stringstream buffer;
    njoy::Log::add_sink( buffer );
    njoy::Log::warning( testString );
    std::string resultString = buffer.str();
    REQUIRE( resultString == ( "[warning] " + testString  +'\n' ) );
  }

  SECTION("error logging"){
    std::stringstream buffer;
    njoy::Log::add_sink( buffer );
    njoy::Log::error( testString );
    std::string resultString = buffer.str();
    REQUIRE( resultString == ( "[error] " + testString  +'\n' ) );
  }

  SECTION("debug logging"){
    std::stringstream buffer;
    njoy::Log::add_sink( buffer );
    njoy::Log::debug( testString );
    std::string resultString = buffer.str();
    #ifdef NDEBUG
    REQUIRE( resultString == ( "" ) );
    #else
    REQUIRE( resultString == ( "[debug] " + testString  +'\n' ) );
    #endif
  }

  SECTION("file sink"){
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
    
    auto resultString = collectFileContents();
    REQUIRE( resultString == ( "[info] " +  testString + '\n' ) );
    REQUIRE( not std::remove("./sink.txt") );
  }
}
