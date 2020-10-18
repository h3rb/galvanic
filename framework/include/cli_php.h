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

extern Zbool PHP_Request;

class CLI_PHP : public CommandLineFeature {
public:
 CLI_PHP() : CommandLineFeature() {
  key="php";
  shortkey="p";
  help="Resulting output format for PHP.";
 }
 void Action( CommandLineOption *in ) {
  PHP_Request=true;
 }
};
