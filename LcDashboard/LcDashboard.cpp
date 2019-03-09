#include "stdafx.h"
#include "LcDashboard.h"

namespace LcDashboard {
    LcDashboard* GlobalDashboard = nullptr;

    LcDashboardTable* LcDashboard::FindTable(const std::string& table) const {
        auto it = this->Tables.find(table);
        if (it == this->Tables.end())
            return nullptr;
        else
            return it->second;
    }

    LcDashboardTable* LcDashboard::FindOrCreateTable(const std::string& table) {
        LcDashboardTable* result = this->FindTable(table);
        if (result == nullptr) {
            result = new LcDashboardTable(table);
            this->Tables.insert(std::pair<std::string, LcDashboardTable*>(table, result));
        }
        return result;
    }

    LcDashboard::~LcDashboard() {
        for (auto pair : this->Tables) {
            delete pair.second;
        }
    }

    void LcDashboard::SerializeIndex(rapidjson::Value& destination, rapidjson::Document& doc) const {
        rapidjson::Value tableArray(rapidjson::kArrayType);
        rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>& a = doc.GetAllocator();

        for (auto pair : this->Tables) {
            // NOTE: Assuming that the char* backing the table name will last longer than these JSON nodes.
            tableArray.PushBack(rapidjson::Value(rapidjson::kStringType).SetString(pair.first.c_str(), pair.first.size(), a), a);
        }
        destination.AddMember("tables", tableArray, a);
    }

    void LcDashboard::SerializeTable(const std::string& name, rapidjson::Value& destination, rapidjson::Document& doc) const {
        // TODO: Implement
        destination.AddMember("type", "<NotImplemented>", doc.GetAllocator());
        destination.AddMember("data", "<NotImplemented>", doc.GetAllocator());
    }

    void LcDashboard::PutString(const std::string& tableName, const std::string& name, const std::string& value) {
        LcDashboardTable* table = this->FindOrCreateTable(tableName);
        // TODO: Implement
    }
}