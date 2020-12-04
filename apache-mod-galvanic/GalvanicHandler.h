#pragma once

#include <string>
using std::string;

#include "http_protocol.h"
#include "../framework/include/zerotypes.h"

class GalvanicHandler {
    public:
        int RunHandler(request_rec *req) {
            if (!req->handler || module_name != req->handler) return DECLINED;

            int main(int argc, char **argv ) {
            InitZeroTypesLibrary();
            Galvanic galvanic;
            int result=galvanic.ModuleHandler( req );
            if ( result ) {
              ap_rputs(http_out.c_str(), req);              
            }
            return OK;
        }
    private:
        string module_name = "galvanic";
        Zstring http_out;
};