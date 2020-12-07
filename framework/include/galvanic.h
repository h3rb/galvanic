/******************************************************************
 __     __    _     _       __    _      _   __
/ /`_  / /\  | |   \ \  /  / /\  | |\ | | | / /`
\_\_/ /_/--\ |_|__  \_\/  /_/--\ |_| \| |_| \_\_,

 Copyright (c) 2020 H. Elwood Gilliland III
 This open source framework is available under the MIT License,
 see LICENSE file accompanying this file for more information
*******************************************************************/
#pragma once

#include "commandline.h"
#include "settings.h"


class Galvanic {
public:
#if defined (BUILD_APACHE_MODULE)
std::string Execute( Strings &ELEMENTS, Strings &HEADERS, Strings &POST, Zstring &body ) {
 return string("It works!");
}
#else
 CommandLine commandLine;
 int Execute( int argc, char **argv ) {
  PopulateCommandLineFeatures();
  commandLine.Main(argc,argv);
  commandLineFeatures.Execute(&commandLine);
  return 0;
 }
#endif
};
