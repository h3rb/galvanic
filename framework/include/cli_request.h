/******************************************************************
 __     __    _     _       __    _      _   __
/ /`_  / /\  | |   \ \  /  / /\  | |\ | | | / /`
\_\_/ /_/--\ |_|__  \_\/  /_/--\ |_| \| |_| \_\_,

 Copyright (c) 2020 H. Elwood Gilliland III
 This open source framework is available under the MIT License,
 see LICENSE file accompanying this file for more information
*******************************************************************/
#pragma once

#include "zerotypes.h"

#include "commandline.h"
#include "session.h"


class CLI_Request : public CommandLineFeature {
public:
 CLI_Request() : CommandLineFeature() {
  key="request";
  shortkey="r";
  help="Process a JSON input file containing request data.";
  varname="filepath";
 }
 void Action( CommandLineOption *in ) {
  
 }
};
