#ifdef BUILD_APACHE_MODULE

#include <memory>

#include "GalvanicHandler.h"
#include "http_config.h"

auto galvanicHandler = std::make_unique<GalvanicHandler>();

#ifdef __cplusplus
extern "C"
{
#endif
    void galvanic_hooks(apr_pool_t* pool);
    module AP_MODULE_DECLARE_DATA foo_module = {
        STANDARD20_MODULE_STUFF,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        galvanic_hooks
    };
#ifdef __cplusplus
}
#endif

// Apache callback to register our hooks
void galvanic_hooks(apr_pool_t* pool) {
    ap_hook_handler(
            [](request_rec *req) {
                return galvanicHandler->RunHandler(req);
            },
            NULL, NULL, APR_HOOK_MIDDLE);
}

#endif