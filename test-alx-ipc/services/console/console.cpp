#include <algorithm>
#include <cstring>
#include <sstream>
#include "controllerIf.h"
#include "hex_dump.h"

#include "mailboxes.h"
#include "messages.h"
#include "printers.h"
#include "client_ipc.h"
#include "console.h"

using namespace Test;

TestConsole& TestConsole::GetInstance(void) {
    TestLoggerCnsl() << INFO << "Enter function " << __PRETTY_FUNCTION__;
    static TestConsole instance;
    TestLoggerCnsl() << INFO << "Leave function " << __PRETTY_FUNCTION__;
    return instance;
};

TestConsole::TestConsole(void) {
    TestLoggerCnsl() << INFO << "Enter function " << __PRETTY_FUNCTION__;
    alxConsole::ConsoleStringCb consoleCb = alx::simpleBind(this, &TestConsole::consoleCallback);
    (void)alxConsole::ConsoleMgrIf::get().subscribe("test-alx-ipc", "console.xml", consoleCb, CONSOLE_DIR"test-alx-ipc/");
    ClientIpcIf::getClient().initialize(alx::makeCb(this, &TestConsole::onConnectionStatus));
    TestLoggerCnsl() << INFO << "Leave function " << __PRETTY_FUNCTION__;
}

TestConsole::~TestConsole() {
    TestLoggerCnsl() << INFO << "Enter function " << __PRETTY_FUNCTION__;
    (void)alxConsole::ConsoleMgrIf::get().unsubscribe("console.xml");
    ClientIpcIf::getClient().deinitialize(alx::makeCb(this, &TestConsole::onConnectionStatus));
    TestLoggerCnsl() << INFO << "Leave function " << __PRETTY_FUNCTION__;
}

void TestConsole::onConnectionStatus(const Test::ServersState& serverState) {
    TestLoggerCnsl() << INFO << "Enter function " << __PRETTY_FUNCTION__;
    TestLoggerCnsl() << INFO << "Server state currently: " << static_cast<uint8_t>(serverState);
    TestLoggerCnsl() << INFO << "Leave function " << __PRETTY_FUNCTION__;
}

void TestConsole::consoleCallback(alxConsole::ConsoleStringVector& arguments) {
    TestLoggerCnsl() << INFO << "Enter function " << __PRETTY_FUNCTION__;

    TestLoggerCnsl() << INFO << "Receive command: " << arguments[1].c_str();

    if(arguments[0] == "test-alx-ipc") {
        if (arguments[1] == "send_block_msg") {
            std::string buff_req = "TEST_IPC_BLOCK_REQ";
            char buff_resp[128] = { 0 };
            uint32_t buff_resp_size = sizeof(buff_resp);
            TestLoggerCnsl() << INFO << "Send message: " << buff_req.c_str();
            ClientIpcIf::getClient().blockSend(TEST_IPC_BLOCK_REQ, buff_req.c_str(), buff_req.size(), buff_resp, buff_resp_size);
            TestLoggerCnsl() << INFO << "Receive message: " << buff_resp;
        }
        if (arguments[1] == "send_block_publish_msg") {
            std::string buff_req = "TEST_IPC_BLOCK_PUBLISH_REQ";
            char buff_resp[128] = { 0 };
            uint32_t buff_resp_size = sizeof(buff_resp);
            TestLoggerCnsl() << INFO << "Send message: " << buff_req.c_str();
            ClientIpcIf::getClient().blockSend(TEST_IPC_BLOCK_PUBLISH_REQ, buff_req.c_str(), buff_req.size(), buff_resp, buff_resp_size);
            TestLoggerCnsl() << INFO << "Receive message: " << buff_resp;
        }
        else if(arguments[1] == "send_async_msg") {
            std::string buff_req = "TEST_IPC_ASYNC_REQ";
            TestLoggerCnsl() << INFO << "Send message: " << buff_req.c_str();
            ClientIpcIf::getClient().asyncSend(TEST_IPC_ASYNC_REQ, buff_req.c_str(), buff_req.size());
        }
        else if(arguments[1] == "send_async_publish_msg") {
            std::string buff_req = "TEST_IPC_ASYNC_PUBLISH_REQ";
            TestLoggerCnsl() << INFO << "Send message: " << buff_req.c_str();
            ClientIpcIf::getClient().asyncSend(TEST_IPC_ASYNC_PUBLISH_REQ, buff_req.c_str(), buff_req.size());
        }
    }

    TestLoggerCnsl() << INFO << "Leave function " << __PRETTY_FUNCTION__;
}
