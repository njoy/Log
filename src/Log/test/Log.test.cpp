#define CATCH_CONFIG_MAIN

#include <iostream>
#include <iterator>
#include <string>
#include <sstream>

#include "Log.hpp"
#include "catch.hpp"

  

TEST_CASE("info logging"){
  std::string testString = "hello world";
  std::stringstream buffer;
  njoy::Log::add_sink( buffer );
  njoy::Log::info( testString );
  std::string resultString = buffer.str();
  REQUIRE( resultString == ( "[info] " + testString  +'\n' ) );
}

TEST_CASE("warning logging"){
  std::string testString = "hello world";
  std::stringstream buffer;
  njoy::Log::add_sink( buffer );
  njoy::Log::warning( testString );
  std::string resultString = buffer.str();
  REQUIRE( resultString == ( "[warning] " + testString  +'\n' ) );
}

TEST_CASE("error logging"){
  std::string testString = "hello world";
  std::stringstream buffer;
  njoy::Log::add_sink( buffer );
  njoy::Log::error( testString );
  std::string resultString = buffer.str();
  REQUIRE( resultString == ( "[error] " + testString  +'\n' ) );
}

TEST_CASE("debug logging"){
  std::string testString = "hello world";
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

TEST_CASE("file sink"){
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
