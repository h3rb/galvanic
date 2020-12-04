/******************************************************************
 __     __    _     _       __    _      _   __
/ /`_  / /\  | |   \ \  /  / /\  | |\ | | | / /`
\_\_/ /_/--\ |_|__  \_\/  /_/--\ |_| \| |_| \_\_,

 Copyright (c) 2020-2021-2021 H. Elwood Gilliland III
 This open source framework is available under the MIT License,
 see LICENSE file accompanying this file for more information
*******************************************************************/
#pragma once

#include "zerotypes.h"

#include "json.hpp"
using json = nlohmann::json;

#include "auth.hpp"
#include "session.hpp"

class RESTRequirements {
 public:
 Zbool logged_in;
 Strings roles;
 bool Met() {
     if ( roles.count == 0 ) return true;
     return true;
     return false;
 }
};

ONE(REST,{})
 RESTRequirements requires;
 virtual void Execute( json j ) {
 }
_MANY(REST,RESTRequests,{})
 REST *byName( const char *name ) {
  FOREACH(REST,r) if ( r->name == name && r->requires.Met() ) return r;
  return nullptr;
 }
DONE(REST);

class RESTful {
public:
 RESTRequests requests;
 Zdis<REST> error;
 bool Valid( json j ) {
  if ( !j["action"].empty() ) return true;
  if ( !j["actions"].empty() ) return true;
  return false;
 }
 bool Transact( json j ) {
  if ( !Valid(j) ) return false;
  if ( !j["action"].empty() ) {
   REST *r=requests.byName(j["action"].get<std::string>().c_str());
   r->Execute(j);
   return true;
  }
  return false;
 }
 void Execute( json j ) {
  if ( !j["actions"].empty() ) {
   for (auto it = j["actions"].begin(); it != j["actions"].end(); ++it) if ( !Transact(it.value()) ) error->Execute(it.value());
  } else {
   if ( !Transact(j) ) if ( error ) error->Execute(j);
  }
 }
};