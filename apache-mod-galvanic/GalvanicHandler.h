#pragma once

#define BLOCKSIZE 4096

#include <string>
using std::string;

#include "../framework/include/zerotypes.h"
#include "../framework/include/galvanic.h"
#undef DONE // collides with apache2
#include "http_protocol.h"
#include "util_script.h"

int headers_table_do(void* rec, const char* key, const char* value);
int get_table_do(void* rec, const char* key, const char* value);

class GalvanicHandler {
    public:
        int RunHandler(request_rec *req) {
            if (!req->handler || module_name != req->handler) return DECLINED;
            InitZeroTypesLibrary();
            GetElements(req);
            GetHeaders(req);
            GetGet(req);
            GetPost(req);
            GetBody(req);
            Galvanic galvanic;
            http_out=galvanic.Execute( ELEMENTS, HEADERS, POST, body );
            ap_rputs(http_out.c_str(), req);              
            return OK;
        }
    private:
        string module_name = "galvanic";
        Strings HEADERS, GET, POST, ELEMENTS;
        Zstring body, http_out;
        void GetElements(request_rec *req) {
         ELEMENTS.Append(new String("handler",req->handler));
         ELEMENTS.Append(new String("protocol",req->protocol));
         ELEMENTS.Append(new String("hostname",req->hostname));
         ELEMENTS.Append(new String("method",req->method));
         ELEMENTS.Append(new String("filename",req->filename,true));
         ELEMENTS.Append(new String("args",req->args,true));
         ELEMENTS.Append(new String("range",req->range));
         ELEMENTS.Append(new String("user",req->user,true));
         ELEMENTS.Append(new String("useragent_ip",req->useragent_ip,true));
         ELEMENTS.Append(new String("useragent_host",req->useragent_host,true));
         ELEMENTS.Append(new String("status_line",req->status_line));
         ELEMENTS.Append(new String("content_type",req->content_type));
         ELEMENTS.Append(new String("content_encoding",req->content_encoding));
         ELEMENTS.Append(new String("vlist_validator",req->vlist_validator,true));
         ELEMENTS.Append(new String("canonical_filename",req->canonical_filename,true));
         ELEMENTS.Append(new String("path_info",req->path_info,true));
         ELEMENTS.Append(new String("log_id",req->log_id));
         ELEMENTS.Append(new String("the_request",req->the_request));
        }
        void GetHeaders(request_rec *req) {
         apr_table_do(headers_table_do, req, req->headers_in, NULL);
        }
        void GetGet(request_rec *req) {
         apr_table_t *G = NULL;
         ap_args_to_table(req, &G);         
         apr_table_do(get_table_do, req, req->headers_in, NULL);
        }
        void GetPost(request_rec *req) {
         apr_array_header_t *pairs = NULL;
         apr_off_t len;
         apr_size_t size;
         int res;
         res = ap_parse_form_data(req, NULL, &pairs, -1, HUGE_STRING_LEN);
         if (res != OK || !pairs) return;
         while (pairs && !apr_is_empty_array(pairs)) {
             ap_form_pair_t *pair = (ap_form_pair_t *) apr_array_pop(pairs);
             apr_brigade_length(pair->value, 1, &len);
             char buff[len+1];
             buff[len]=0;
             apr_brigade_flatten(pair->value, buff, &size);
             String *s=new String;
             s->s=string(pair->name);
             s->value = string(buff);
             POST.Append(s);
         }
        }
        void GetBody(request_rec *req) {
         if(M_PUT != req->method_number && M_POST != req->method_number) return;            
         int ret = ap_setup_client_block(req, REQUEST_CHUNKED_ERROR);
         if(OK == ret && ap_should_client_block(req)) {
          char* buffer = (char*)apr_pcalloc(req->pool, BLOCKSIZE);
          int len;
          while((len=ap_get_client_block(req, buffer, BLOCKSIZE)) > 0) {
            body += string(buffer);
          }
         }
        }
};

extern GalvanicHandler galvanicHandler;