#include "stdafx.h"
#include "LcDashboardServer.h"

#include <libwebsockets.h>
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "rapidjson/allocators.h"

#pragma comment(lib, "Ws2_32.lib")

struct APIRequestState {
    
};

const int HEADER_LENGTH_MAX = 300;
const char* API_ENDPOINT_INDEX = "/index";
int APIJSONHandler(lws* wsi, lws_callback_reasons reason, void* user, void* in, size_t len) {
    APIRequestState* state = (APIRequestState*)user;
    const char* url = (const char*)in;
    LcDashboard::LcDashboardServer* server = (LcDashboard::LcDashboardServer*)lws_context_user(lws_get_context(wsi));

    if (reason == LWS_CALLBACK_HTTP) {
        http_status status = http_status::HTTP_STATUS_NOT_FOUND;
        rapidjson::Document json(rapidjson::Type::kObjectType);

        if (strcmp(url, API_ENDPOINT_INDEX) == 0) {
            // Serve index of dashboard
            status = http_status::HTTP_STATUS_OK;
            rapidjson::Value data(rapidjson::kObjectType);
            server->GetDashboard()->SerializeIndex(data, json);
            json.AddMember("data", data, json.GetAllocator());
        }

        if (status == http_status::HTTP_STATUS_OK) {
            json.AddMember("success", true, json.GetAllocator());
        }
        else {
            json.AddMember("success", false, json.GetAllocator());
        }

        rapidjson::StringBuffer jsonBuffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(jsonBuffer);
        json.Accept(writer);
        const char* data = jsonBuffer.GetString();
        uint8_t* buffer = new uint8_t[LWS_PRE + HEADER_LENGTH_MAX + strlen(data) + 1];
        uint8_t* current = &buffer[LWS_PRE];
        uint8_t* end = &buffer[LWS_PRE + HEADER_LENGTH_MAX + strlen(data) + 1];

        if (lws_add_http_common_headers(wsi, status, "text/json", strlen(data), &current, end)) {
            delete[] buffer;
            return 1;
        }
        if (lws_finalize_write_http_header(wsi, &buffer[LWS_PRE], &current, end)) {
            delete[] buffer;
            return 1;
        }
        current = &buffer[LWS_PRE];
        current += lws_snprintf((char*)current, end - current, data);
        if (lws_write(wsi, &buffer[LWS_PRE], lws_ptr_diff(current, &buffer[LWS_PRE]), LWS_WRITE_HTTP_FINAL) != lws_ptr_diff(current, &buffer[LWS_PRE])) {
            delete[] buffer;
            return 1;
        }
        delete[] buffer;
        return lws_http_transaction_completed(wsi);
    }
    else {
        return lws_callback_http_dummy(wsi, reason, user, in, len);
    }
}

const lws_protocols Protocols[]{
    { "http", APIJSONHandler, sizeof(APIRequestState), 0 },
    { NULL, NULL, 0, 0 }
};

const lws_http_mount APIJSONMount = {
    /* .mount_next */		    NULL,		/* linked-list "next" */
    /* .mountpoint */		    "/api",		/* mountpoint URL */
    /* .origin */			    NULL,       /* serve from dir */
    /* .def */			        NULL,	    /* default filename */
    /* .protocol */			    "http",
    /* .cgienv */			    NULL,
    /* .extra_mimetypes */	    NULL,
    /* .interpret */		    NULL,
    /* .cgi_timeout */		    0,
    /* .cache_max_age */	    0,
    /* .auth_mask */		    0,
    /* .cache_reusable */		0,
    /* .cache_revalidate */		0,
    /* .cache_intermediaries */	0,
    /* .origin_protocol */		LWSMPRO_CALLBACK,	/* files in a dir */
    /* .mountpoint_len */		4,		/* char count */
    /* .basic_auth_login_file */NULL,
};

const lws_http_mount StaticFileMount = {
    /* .mount_next */		    &APIJSONMount,		/* linked-list "next" */
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

    LcDashboard* LcDashboardServer::GetDashboard() const {
        return this->Dashboard;
    }

    void LcDashboardServer::Start() {
        if (!this->IsRunning) {

            lws_context_creation_info info = { };
            info.port = this->Port;
            info.mounts = &StaticFileMount;
            info.protocols = Protocols;
            info.user = this;

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
