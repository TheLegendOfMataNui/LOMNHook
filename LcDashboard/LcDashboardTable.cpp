#include "stdafx.h"
#include "LcDashboardTable.h"

namespace LcDashboard {
    LcDashboardTable::LcDashboardTable(const std::string& name) {
        this->Name = name;
    }

    LcDashboardTable::~LcDashboardTable() {
        // TODO: Delete all widgets
    }
}