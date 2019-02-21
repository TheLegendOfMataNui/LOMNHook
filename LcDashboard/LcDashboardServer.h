#pragma once

#include "LcDashboard.h"

struct MHD_Daemon;
namespace LcDashboard {
    class LcDashboardServer {
    private:
        LcDashboard* Dashboard;
        MHD_Daemon* Daemon;
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