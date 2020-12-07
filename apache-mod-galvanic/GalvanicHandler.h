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
            Galvanic galvanic;
            http_out=galvanic.Execute( HEADERS, POST, body );
            ap_rputs(http_out.c_str(), req);              
            return OK;
        }
    private:
        string module_name = "galvanic";
        Strings HEADERS, POST;
        Zstring body, http_out;
};

extern GalvanicHandler galvanicHandler;