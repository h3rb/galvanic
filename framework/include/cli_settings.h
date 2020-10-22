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
#include "settings.h"


class CLI_Settings : public CommandLineFeature {
public:
 CLI_Settings() : CommandLineFeature() {
  key="settings";
  shortkey="s";
  help="Process a JSON input file containing settings.";
  varname="filepath";
 }
 void Action( CommandLineOption *in ) {
  settings.Load(in->value.c_str());
 }
};