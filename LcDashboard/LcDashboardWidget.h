#pragma once

#include <string>

#include "rapidjson/document.h"

#include <Native/ScIdentifier.h>

namespace LcDashboard {
    
    class LcDashboardWidget {
    private:
        std::string Name;
        LOMNHook::Native::ScIdentifier WidgetTypeID;

    public:
        const std::string& GetName() const;
        const LOMNHook::Native::ScIdentifier& GetWidgetTypeID() const;
        virtual rapidjson::Value Serialize() const = 0;
    };
}