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
 CommandLine commandLine;
 int Execute( int argc, char **argv ) {
  commandLine.Main(argc,argv);
  commandLine.Print();
  return 0;
 }
};
