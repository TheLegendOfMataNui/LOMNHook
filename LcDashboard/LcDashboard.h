#pragma once

#include <string>
#include <unordered_map>

#undef min
#undef max
#include "rapidjson/document.h"

#include "LcDashboardWidget.h"
#include "LcDashboardTable.h"

namespace LcDashboard {
    class LcDashboard {
    private:
        std::unordered_map<std::string, LcDashboardTable*> Tables;
        LcDashboardTable* FindTable(const std::string& table) const;
        LcDashboardTable* FindOrCreateTable(const std::string& table);

    public:
        ~LcDashboard();
        // Tables
        //LcDashboardTable* GetTable(const std::string& name) const;

        // JSON Serialization
        void SerializeIndex(rapidjson::Value& destination, rapidjson::Document& doc) const;
        void SerializeTable(const std::string& name, rapidjson::Value& destination, rapidjson::Document& doc) const;

        // Widgets
        //LcDashboardWidget* GetWidget(const std::string& tableName, const std::string& widgetName) const;
        void PutString(const std::string& tableName, const std::string& name, const std::string& value);
        void PutFloat(const std::string& tableName, const std::string& name, const float& value);
        void PutIntProgress(const std::string& tableName, const std::string& name, const int& value, const int& min, const int& max);
        std::string GetString(const std::string& tableName, const std::string& name, const std::string& defaultValue);
        std::string GetStringOption(const std::string& tableName, const std::string& name, const int& defaultIndex, std::string options[]);
        int GetInt(const std::string& tableName, const std::string& name, const int& defaultValue);
        int GetIntSlider(const std::string& tableName, const std::string& name, const int& defaultValue, const int& min, const int& max);
    };

    extern LcDashboard* GlobalDashboard;
}
