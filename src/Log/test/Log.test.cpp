#define CATCH_CONFIG_MAIN

#include <iostream>
#include <iterator>
#include <string>
#include <sstream>

#include "Log.hpp"
#include "catch.hpp"

TEST_CASE( "Log test" ){
  std::stringstream buffer;
  std::string testString = "hello world";
  njoy::Log::add_sink( buffer );

  SECTION("info logging"){
    njoy::Log::info( testString );
    std::string resultString = buffer.str();
    auto rend = std::make_reverse_iterator( resultString.end() ) + 1;
    auto rbegin = rend + 18;
    auto partialResult = std::string( rbegin.base(), rend.base() );
    REQUIRE( partialResult == ( "[info] " + testString ) );
  }

  SECTION("warning logging"){
    njoy::Log::warning( testString );
    std::string resultString = buffer.str();
    auto rend = std::make_reverse_iterator( resultString.end() ) + 1;
    auto rbegin = rend + 21;
    auto partialResult = std::string( rbegin.base(), rend.base() );
    REQUIRE( partialResult == ( "[warning] " + testString ) );
  }

  SECTION("error logging"){
    njoy::Log::error( testString );
    std::string resultString = buffer.str();
    auto rend = std::make_reverse_iterator( resultString.end() ) + 1;
    auto rbegin = rend + 19;
    auto partialResult = std::string( rbegin.base(), rend.base() );
    REQUIRE( partialResult == ( "[error] " + testString ) );
  }

  #ifndef NDEBUG
  SECTION("debug logging"){
    njoy::Log::debug( testString );
    std::string resultString = buffer.str();
    auto rend = std::make_reverse_iterator( resultString.end() ) + 1;
    auto rbegin = rend + 19;
    auto partialResult = std::string( rbegin.base(), rend.base() );
    REQUIRE( partialResult == ( "[debug] " + testString ) );
  }
  #endif

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
