#pragma once

#include <string>
using std::string;

#include "../framework/include/zerotypes.h"
#include "../framework/include/galvanic.h"
#undef DONE // collides with apache2
#include "http_protocol.h"

class GalvanicHandler {
    public:
        int RunHandler(request_rec *req) {
            if (!req->handler || module_name != req->handler) return DECLINED;
            InitZeroTypesLibrary();
            GetHeaders(req);
            GetPost(req);
            GetBody(req);
            Galvanic galvanic;
            http_out=galvanic.Execute( HEADERS, POST, body );
            ap_rputs(http_out.c_str(), req);              
            return OK;
        }
    private:
        string module_name = "galvanic";
        Strings HEADERS, POST;
        Zstring body, http_out;
        void GetHeaders(request_rec *req) {
            
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
         }
        }
        void GetBody(request_rec *req) {
            
        }
};

extern GalvanicHandler galvanicHandler;