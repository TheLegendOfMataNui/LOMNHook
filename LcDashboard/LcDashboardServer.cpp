#include "stdafx.h"
#include "LcDashboardServer.h"

#include <libwebsockets.h>

#pragma comment(lib, "Ws2_32.lib")

static const lws_http_mount StaticFileMount = {
    /* .mount_next */		    NULL,		/* linked-list "next" */
    /* .mountpoint */		    "/",		/* mountpoint URL */
    /* .origin */			    "./mods/dashboard-client", /* serve from dir */
    /* .def */			        "index.html",	/* default filename */
    /* .protocol */			    NULL,
    /* .cgienv */			    NULL,
    /* .extra_mimetypes */	    NULL,
    /* .interpret */		    NULL,
    /* .cgi_timeout */		    0,
    /* .cache_max_age */	    0,
    /* .auth_mask */		    0,
    /* .cache_reusable */		0,
    /* .cache_revalidate */		0,
    /* .cache_intermediaries */	0,
    /* .origin_protocol */		LWSMPRO_FILE,	/* files in a dir */
    /* .mountpoint_len */		1,		/* char count */
    /* .basic_auth_login_file */NULL,
};

namespace LcDashboard {
    LcDashboardServer::LcDashboardServer(LcDashboard* dashboard, const uint16_t& port) : Dashboard(dashboard), Port(port) {
        lws_set_log_level(LLL_USER | LLL_ERR | LLL_WARN | LLL_NOTICE, nullptr);
        this->Start();
    }

    LcDashboardServer::~LcDashboardServer() {
        if (this->IsRunning) {
            this->Stop();
        }
    }

    void LcDashboardServer::Start() {
        if (!this->IsRunning) {

            lws_context_creation_info info = { };
            info.port = this->Port;
            info.mounts = &StaticFileMount;

            this->Context = lws_create_context(&info);

            this->IsRunning = true;
        }
    }

    void LcDashboardServer::Stop() {
        if (this->IsRunning) {
            lws_context_destroy(this->Context);
            this->Context = nullptr;
            this->IsRunning = false;
        }
    }
    
    void LcDashboardServer::Process() {
        if (this->IsRunning) {
            int status = lws_service(this->Context, 0);
            if (status < 0) {
                OutputDebugStringW(L"LcDashboard Server unexpectedly shutdown!\n");
                lws_context_destroy(this->Context);
                this->Context = nullptr;
                this->IsRunning = false;
            }
        }
    }
}
