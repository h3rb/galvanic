#pragma once

#include "zerotypes.h"


ONE(CommandLineOption,{})
 Zp<CommandLineOption> base;
 Zstring raw,key,value;
 Strings options;
 CommandLineOption( char *command, CommandLineOption *base=nullptr ) : ListItem() {
  this->base=base;
  raw=command;
  Parse();
 }
 void Parse() {
  if ( raw.inside("=") ) {
   Strings parts;
   parts.SplitPush(raw.c_str(),'=');
   if ( parts.count == 2 ) {
    key=parts.Get(0);
    value=parts.Get(1);
    if ( value.inside(",") ) {
     options.SplitPush(value.c_str(),',');
     EACH(options.first,String,s) {
      Strings parts;
      parts.SplitPush(s->c_str(),'=');
      if ( parts.count == 2 ) {
       s->s=parts.Get(0);
       s->value=parts.Get(1);
      }
     }
    }
   }
  } else key=raw;
 }
 string asString() {
  Zstring out;
  out += raw;
  out += ": ";
  out += key;
  out += "|";
  out += value;
  return out;
 }
MANY(CommandLineOption,CommandLineOptionHandle,CommandLineOptionHandles,"CommandLine",CommandLine,{})
 CommandLineOption base;
 void Main( int argc, char **argv ) {
  base.raw=argv[0];
  for ( int i=1; i<argc; i++ ) {
   Append(new CommandLineOption(argv[i],&base));
  }
 }
 void Print() {
  cout << "base: " << base.raw.value << endl;
  cout << count.value << " command line parameters found" << endl;
  int i=0;
  FOREACH(CommandLineOption,clo) cout << "[" << i++ << "]" << clo->asString() << endl;
 }
DONE(CommandLineOption);
