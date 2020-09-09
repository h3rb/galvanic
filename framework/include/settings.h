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
#include "json.hpp"

ONE(DatabaseSetting,{})
 Zstring ip,port,username,password,schema;
 const char *IP() { return ip.c_str(); }
 const char *Port() { return port.c_str(); }
 const char *Username() { return username.c_str(); }
 const char *Password() { return password.c_str(); }
 const char *Schema() { return schema.c_str(); }
 void Set( json &j ) {
  ip=j["ip"];
  port=j["port"];
  username=j["username"];
  password=j["password"];
  schema=j["schema"];
  name=schema;
 }
MANY_(DatabaseSetting,{})
 DatabaseSetting *Add( json &j ) {
  if ( j.is_array() ) {
   for ( auto it = j.begin(); it != j.end(); ++it ) if ( it.value().is_object() ) Add(it.value());
   return (DatabaseSetting *) first;
  } else {
   DatabaseSetting *d=new DatabaseSetting;
   d->Set(j);
   Append(d);
   return d;
  }
 }
DONE(DatabaseSetting);

ONE(S3Setting,{})
 Zstring bucket,region,rootkey;
 const char *Bucket() { return bucket.c_str(); }
 const char *Region() { return region.c_str(); }
 const char *Rootkey() { return rootkey.c_str(); }
 void Set( json &j  ) {
  bucket=j["bucket"];
  region=j["region"];
  rootkey=j["rootkey"];
  name=rootkey;
 }
MANY_(S3Setting,{})
 S3Setting *Add( json &j ) {
  if ( j.is_array() ) {
   for ( auto it = j.begin(); it != j.end(); ++it ) if ( it.value().is_object() ) Add(it.value());
   return (S3Setting *) first;
  } else {
   S3Setting *s=new S3Setting;
   s->Set(j);
   Append(s);
   return s;
  }
 }
DONE(S3Setting);

class Settings {
public:
 Zp<DatabaseSetting> defaultDB;
 Zp<S3Setting> defaultS3;
 DatabaseSettings databases;
 S3Settings buckets;
 json j;
 void Load( const char *filename ) {
  Zstring file;
  file.Load(filename);
  j = json::parse(file.c_str());
  if ( j.find("port") != j.end() ) defaultDB = databases.Add(j);
  if ( j.find("rootkey") != j.end() ) defaultS3 = buckets.Add(j);
  { auto it = j.find("db");        if ( it != j.end() ) databases.Add(it.value()); }
  { auto it = j.find("database");  if ( it != j.end() ) databases.Add(it.value()); }
  { auto it = j.find("databases"); if ( it != j.end() ) databases.Add(it.value()); }
  { auto it = j.find("schema");    if ( it != j.end() ) databases.Add(it.value()); }
  { auto it = j.find("schemas");   if ( it != j.end() ) databases.Add(it.value()); }
  { auto it = j.find("bucket");    if ( it != j.end() ) buckets.Add(it.value()); }
  { auto it = j.find("buckets");   if ( it != j.end() ) buckets.Add(it.value()); }
  if ( !defaultDB ) defaultDB = (DatabaseSetting *) databases.first;
  if ( !defaultS3 ) defaultS3 = (S3Setting *) buckets.first;
 }
};

extern Settings settings;
