#pragma once

#include <string>
using std::string;

struct request_rec;
#include "../framework/include/zerotypes.h"

class GalvanicHandler {
    public:
        int RunHandler(request_rec *req);
    private:
        string module_name = "galvanic";
        Zstring http_out;
};