/******************************************************************
 __     __    _     _       __    _      _   __
/ /`_  / /\  | |   \ \  /  / /\  | |\ | | | / /`
\_\_/ /_/--\ |_|__  \_\/  /_/--\ |_| \| |_| \_\_,

 Copyright (c) 2020 H. Elwood Gilliland III
 This open source framework is available under the MIT License,
 see LICENSE file accompanying this file for more information
*******************************************************************/
#pragma once

#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListObjectsRequest.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <aws/s3/model/DeleteObjectRequest.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

#include "zerotypes.h"


class S3Result {
public:
  Zbool error;
  Zstring exception,message;
};

class S3Configuration {
public:
   Zstring bucket;
   Aws::Client::ClientConfiguration config;
   Aws::S3::Model::BucketLocationConstraint region;
   Aws::Client::ClientConfiguration &Get() { return config; }
   bool Configure( const char *bucket, const char *region ) {
    this->bucket=bucket;
    if ( !SetRegion(region) ) return false;
   }
   bool SetRegion( const char *region_name ) {
    // Set the AWS Region to use, based on the user's AWS Region input ID.
    if (strcmp(region_name, "ap-northeast-1") == 0) {
      config.region = Aws::Region::AP_NORTHEAST_1;
      region = Aws::S3::Model::BucketLocationConstraint::ap_northeast_1;
    } else if (strcmp(region_name, "ap-northeast-2") == 0) {
      config.region = Aws::Region::AP_NORTHEAST_2;
      region = Aws::S3::Model::BucketLocationConstraint::ap_northeast_2;
    } else if (strcmp(region_name, "ap-south-1") == 0) {
      config.region = Aws::Region::AP_SOUTH_1;
      region = Aws::S3::Model::BucketLocationConstraint::ap_south_1;
    } else if (strcmp(region_name, "ap-southeast-1") == 0) {
      config.region = Aws::Region::AP_SOUTHEAST_1;
      region = Aws::S3::Model::BucketLocationConstraint::ap_southeast_1;
    } else if (strcmp(region_name, "ap-southeast-2") == 0) {
      config.region = Aws::Region::AP_SOUTHEAST_2;
      region = Aws::S3::Model::BucketLocationConstraint::ap_southeast_2;
    } else if (strcmp(region_name, "cn-north-1") == 0) {
      config.region = Aws::Region::CN_NORTH_1;
      region = Aws::S3::Model::BucketLocationConstraint::cn_north_1;
    } else if (strcmp(region_name, "eu-central-1") == 0) {
      config.region = Aws::Region::EU_CENTRAL_1;
      region = Aws::S3::Model::BucketLocationConstraint::eu_central_1;
    } else if (strcmp(region_name, "eu-west-1") == 0) {
      config.region = Aws::Region::EU_WEST_1;
      region = Aws::S3::Model::BucketLocationConstraint::eu_west_1;
    } else if (strcmp(region_name, "sa-east-1") == 0) {
      config.region = Aws::Region::SA_EAST_1;
      region = Aws::S3::Model::BucketLocationConstraint::sa_east_1;
    } else if (strcmp(region_name, "us-west-1") == 0) {
      config.region = Aws::Region::US_WEST_1;
      region = Aws::S3::Model::BucketLocationConstraint::us_west_1;
    } else if (strcmp(region_name, "us-west-2") == 0) {
      config.region = Aws::Region::US_WEST_2;
      region = Aws::S3::Model::BucketLocationConstraint::us_west_2;
    } else if (strcmp(region_name, "us-east-1") == 0) {
      config.region = Aws::Region::US_EAST_1;
      region = Aws::S3::Model::BucketLocationConstraint::us_west_2;
    } else if (strcmp(region_name, "us-east-2") == 0) {
      config.region = Aws::Region::US_EAST_2;
      region = Aws::S3::Model::BucketLocationConstraint::us_east_2;
    } else {
      std::cout << "Unrecognized AWS Region ID '" << region_name << "'" << std::endl;
      return false;
    }
    return true;
   }
};

class S3 {
public:
   
   S3() {}
   
   void Init() {
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    SetRegion("us-east-2");
    config.Instantiate();
   }
   
   void Shutdown() {
    Aws::SDKOptions options;
    Aws::ShutdownAPI(options);
   }
   
   Zdis<S3Configuration> config;
   
   bool Configure( const char *bucket, const char *region ) {
    return config->Configure(bucket,region);
   }
   
   bool SetRegion( const char *region_name ) {
    return config->SetRegion(region_name);
   }
   
   string Get( const char *endpoint, S3Result &out ) {
    Aws::S3::S3Client s3_client(config->Get());
    Aws::S3::Model::GetObjectRequest object_request;
    object_request.SetBucket(Aws::String(config->bucket.c_str()));
    object_request.SetKey(Aws::String(endpoint));
    auto get_object_outcome = s3_client.GetObject(object_request);
    if (get_object_outcome.IsSuccess()) {
     out.error=false;
     auto &retrieved_file = get_object_outcome.GetResultWithOwnership().GetBody();
     std::stringstream buffer;
     buffer << retrieved_file.rdbuf();
     std::string result=buffer.str();
     return result;       
    } else {
     out.error=true;
     auto error = get_object_outcome.GetError();
     std::cout << "ERROR: " << error.GetExceptionName() << ": " << error.GetMessage() << std::endl;
     out.exception=error.GetExceptionName().c_str();
     out.message=error.GetMessage().c_str();
     return string("<ERROR>");
    }
   }
   
   bool Put( const char *endpoint, const char *data, S3Result &out ) {
    Aws::S3::S3Client s3_client(config->Get());
    Aws::S3::Model::PutObjectRequest object_request;
    object_request.SetBucket(Aws::String(config->bucket.c_str()));
    object_request.SetKey(Aws::String(endpoint));
    auto put_data = Aws::MakeShared<Aws::StringStream>("PutObjectInputStream", std::stringstream::in | std::stringstream::out | std::stringstream::binary);
    put_data->write(reinterpret_cast<const char*>(data), strlen(data));
    object_request.SetBody(put_data);
    auto put_object_outcome = s3_client.PutObject(object_request);
    if ( !put_object_outcome.IsSuccess() ) {
      auto error = put_object_outcome.GetError();
      std::cout << "ERROR: " << error.GetExceptionName() << ": " << error.GetMessage() << std::endl;
      out.exception=error.GetExceptionName().c_str();
      out.message=error.GetMessage().c_str();
      return false;
    }
    return true;
   }
   
   int Put( const char *prefix, Strings &files, Strings &basenames ) {
    S3Result out;
    int errors=0;
    int i=0;
    EACH(files.first,String,fn) {
      String *ep=(String *) basenames.Element(i);
      i++;
      if ( !ep ) { errors++; break; }
      std::string endpoint=string(prefix)+ep->s.c_str();
      std::string data=file_as_string(fn->s.c_str());
      if ( data.length() < 1 ) { errors++; continue; }
      if ( !Put(endpoint.c_str(),data.c_str(),out) ) errors++;
    }
    return errors;
   }
   
   void List( Strings &list, S3Result &out ) {   
    Aws::S3::S3Client s3_client(config->Get()); 
    Aws::S3::Model::ListObjectsRequest objects_request;
    objects_request.WithBucket(Aws::String(config->bucket.c_str()));     
    auto list_objects_outcome = s3_client.ListObjects(objects_request);     
    if ( list_objects_outcome.IsSuccess() ) {
     out.error=false;
     Aws::Vector<Aws::S3::Model::Object> object_list = list_objects_outcome.GetResult().GetContents();
     for (auto const &s3_object : object_list) list.Add(s3_object.GetKey().c_str());
    } else {
     auto error = list_objects_outcome.GetError();
     out.error=true;
     std::cout << "ListObjects error: " << error.GetExceptionName() << " " << error.GetMessage() << std::endl;
     out.exception=error.GetExceptionName().c_str();
     out.message=error.GetMessage().c_str();
    }
   }
   
   void Delete( const char *endpoint, S3Result &out ) {
    Aws::S3::S3Client s3_client(config->Get());
    Aws::S3::Model::DeleteObjectRequest delete_endpoint_request;
    delete_endpoint_request.SetBucket(Aws::String(config->bucket.c_str()));
    delete_endpoint_request.SetKey(Aws::String(endpoint));
    auto outcome = s3_client.DeleteObject(delete_endpoint_request);
    if (outcome.IsSuccess()) out.error=false;
    else {
     out.error=true;
     auto error = outcome.GetError();
     std::cout << "DeleteBucket error: " << error.GetExceptionName() << " - " << error.GetMessage() << std::endl;
     out.exception=error.GetExceptionName().c_str();
     out.message=error.GetMessage().c_str();
    }
   }
   
};

extern S3 s3;
