#pragma once

#include <string>

#undef min
#undef max
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
        virtual void Serialize(rapidjson::Value& destination, rapidjson::Document& doc) const = 0;
    };
}