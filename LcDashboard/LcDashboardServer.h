#pragma once

#include "LcDashboard.h"

struct lws_context;
namespace LcDashboard {
    class LcDashboardServer {
    private:
        LcDashboard* Dashboard;
        lws_context* Context;
        bool IsRunning = false;
        uint16_t Port;

    public:
        LcDashboardServer(LcDashboard* dashboard, const uint16_t& port);
        ~LcDashboardServer();
        void Start();
        void Stop();
        void Process();
    };
}