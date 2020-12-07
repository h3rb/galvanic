#include "GalvanicHandler.h"

#include "http_protocol.h"


int GalvanicHandler::RunHandler(request_rec *req) {
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