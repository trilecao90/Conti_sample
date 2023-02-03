#ifndef PRINTERS_H
#define PRINTERS_H

#include "logging.h"

using namespace alxLog;

enum class TestUnits : uint8_t {
    Manager,
    Console,
    Client,
    ServerIpc,
    Server,
};

REGISTER_FACILITY_UNITS(Facility::TestIpcSample, TestUnits);
DEFINE_LITERAL_CODE(TestUnits, Manager,     "MNGR")
DEFINE_LITERAL_CODE(TestUnits, Console,     "CNSL")
DEFINE_LITERAL_CODE(TestUnits, Client,      "CLNT_IPC")
DEFINE_LITERAL_CODE(TestUnits, ServerIpc,   "SRVR_IPC")
DEFINE_LITERAL_CODE(TestUnits, Server,      "SRVR")

template <TestUnits unit>
using TestLogger            = Logger<Facility::TestIpcSample, unit>;
using TestLoggerMgr         = TestLogger<TestUnits::Manager>;
using TestLoggerCnsl        = TestLogger<TestUnits::Console>;
using TestLoggerClient      = TestLogger<TestUnits::Client>;
using TestLoggerServerIpc   = TestLogger<TestUnits::ServerIpc>;
using TestLoggerServer      = TestLogger<TestUnits::Server>;

#endif