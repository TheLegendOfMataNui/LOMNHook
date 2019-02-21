#pragma once

#include <string>
#include <unordered_map>

#include "rapidjson/document.h"

#include "LcDashboardWidget.h"

namespace LcDashboard {
    class LcDashboardTable {
    private:
        std::string Name;
        std::unordered_map<std::string, LcDashboardWidget*> Widgets;

    public:
        LcDashboardTable(const std::string& name);
        ~LcDashboardTable();
        LcDashboardWidget* GetWidget(const std::string& name) const;
        void AddWidget(LcDashboardWidget* const widget);
        void RemoveWidget(const std::string& name);
        rapidjson::Value Serialize() const;
    };
}