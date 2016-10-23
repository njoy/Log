Log
=====
A global logger singleton for NJOY21 projects built upon the spdlog library.

Minimal Example
====================

```c++
#include <sstream>
#include "Log.hpp"

int main(){

  /* Logs use python-like format strings. See the fmt library for more information */
  Log::info( "I am {} years old", 23 );

  /* In addition, to the info level, warning, error, and debug levels are provided */
  Log::warning( "I am having {} for {}", "bean burrito", "lunch");
  Log::error( "The restaurant put {} on my {}", "pork", "bean burrito" );
  Log::debug( "This log will not be displayed when compiled with NDEBUG defined" );

  /* Additional sinks can be added to the logger */
  std::ostring_stream oss;
  Log::add_sink( oss );
  Log::add_sink( "path/to/my/log/file" );
}
```
