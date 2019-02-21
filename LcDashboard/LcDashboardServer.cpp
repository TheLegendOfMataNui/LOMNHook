#include "stdafx.h"
#include "LcDashboardServer.h"

#include "libmicrohttpd-x86/include/microhttpd.h"
//#include "libmicrohttpd-x86/include/"

const char* HTTP_GET = "GET";
int HTTPAnswerConnection(void* cls, MHD_Connection* connection, const char* url, const char* method, const char* version, const char* uploadData, size_t* uploadSize, void** con_cls) {
    if (strcmp(HTTP_GET, method) != 0) {
        return MHD_NO;
    }

    const char* page = "<html><head><title>LcDashboardServer</title></head><body>Sup, it's LcDashboard!</body></html>";
    int result = MHD_HTTP_OK;

    MHD_Response* response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
    result = MHD_queue_response(connection, result, response);
    MHD_destroy_response(response);
    return result;
}

namespace LcDashboard {
    LcDashboardServer::LcDashboardServer(LcDashboard* dashboard, const uint16_t& port) : Dashboard(dashboard), Daemon(nullptr), Port(port) {
        this->Start();
    }

    LcDashboardServer::~LcDashboardServer() {
        if (this->IsRunning) {
            this->Stop();
        }
    }

    void LcDashboardServer::Start() {
        if (!this->IsRunning) {
            this->Daemon = MHD_start_daemon(MHD_FLAG::MHD_NO_FLAG, this->Port, nullptr, nullptr, &HTTPAnswerConnection, nullptr, MHD_OPTION_END);
            this->IsRunning = true;
        }
    }

    void LcDashboardServer::Stop() {
        if (this->IsRunning) {
            MHD_stop_daemon(this->Daemon);
            this->Daemon = nullptr;
            this->IsRunning = false;
        }
    }
    
    void LcDashboardServer::Process() {
        if (this->IsRunning) {
            int result = MHD_run(this->Daemon);
            OutputDebugStringA("");
        }
    }
}
