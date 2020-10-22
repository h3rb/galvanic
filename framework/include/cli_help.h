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
#include "version.h"

class CLI_Help : public CommandLineFeature {
public:
 CLI_Help() : CommandLineFeature() {
  key="help";
  shortkey="h";
  help="Show command line options.";
  text="Galvanic: A C++ Server-side RESTful Web Framework\n";
  text+="Version: ";
  text+=GALVANIC_VERSION_STRING;
  text+="\n\nUsage:  galvanic settings=[filepath.json] request=[filepath.json]\n\n";
 }
 string Fit(const char *in) {
  Zstring s(in);
  while ( s.length < 25 ) s+=" ";
  return s.value;
 }
 Zstring text;
 Strings addendums;
 void Action( CommandLineOption *in ) {
  Zstring output=text;
  EACH(commandLineFeatures.first,CommandLineFeature,clf) {
   Zstring equalstext;
   if ( clf->varname.length > 0 ) equalstext=string("=[")+clf->varname+string("]");
   if ( clf->shortkey.length > 0 && clf->key.length > 0 ) {
    output+=Fit( (string("-")+clf->shortkey+equalstext+string(", ")+clf->key+equalstext+string("  ")).c_str());
   } else if ( clf->shortkey.length > 0 )
    output+=Fit((string("-")+clf->shortkey).c_str());
   else if ( clf->key.length > 0 ) {
    output+=Fit((string("-")+clf->key).c_str());
   }
   output+=clf->help; output+="\n";
  }
  EACH(addendums.first,String,s) {
   output+=s->c_str(); output+="\n";
  }
  cout << output.value << endl;
 }

};
