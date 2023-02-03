#include "controllerIf.h"
#include "message_defs.h"
#include "mailbox_timer.h"

#include "mailboxes.h"
#include "messages.h"
#include "printers.h"
#include "server.h"

using namespace Test;

TaskServer::TaskServer() : TaskIf(SERVER_MBOX, true) {
    TestLoggerServer() << INFO << "Enter function " << __PRETTY_FUNCTION__;
    TestLoggerServer() << INFO << "Leave function " << __PRETTY_FUNCTION__;
}

void TaskServer::init(void) {
    TestLoggerServer() << INFO << "Enter function " << __PRETTY_FUNCTION__;
    alx::ControllerIf::getController().subscribe(getMailbox(), TEST_IPC_BLOCK_PUBLISH_REQ);
    alx::ControllerIf::getController().subscribe(getMailbox(), TEST_IPC_ASYNC_PUBLISH_REQ);
    TestLoggerServer() << INFO << "Leave function " << __PRETTY_FUNCTION__;
}

void TaskServer::entry(void) {
    TestLoggerServer() << INFO << "Enter function " << __PRETTY_FUNCTION__;
    
    while (!alx::ControllerIf::getController().isTerminating()) {
        alx::Message inbox_msg;
        alx::ControllerIf::getController().peek(inbox_msg.header);
        MsgBuffer msgBuffer(inbox_msg.header.length);
        inbox_msg.payload = msgBuffer;
        alx::ControllerIf::getController().get(inbox_msg, msgBuffer.capacity());
        switch (inbox_msg.header.id) {
            case TEST_IPC_BLOCK_REQ: {
                resp_msg.header.mailbox = inbox_msg.header.mailbox;
                resp_msg.header.id = TEST_IPC_BLOCK_RSP;
                resp_msg.payload = (uint8_t*) "TEST_IPC_BLOCK_RSP";
                resp_msg.header.length = strlen((char*) resp_msg.payload);
                TestLoggerServer() << INFO << "Receive message: " << (char*) inbox_msg.payload;
                TestLoggerServer() << INFO << "Respond message: " << (char*) resp_msg.payload;
                alx::ControllerIf::getController().send(resp_msg.header.mailbox, resp_msg.header.id, resp_msg.payload, resp_msg.header.length);
                break;
            }
            case TEST_IPC_ASYNC_REQ: {
                resp_msg.header.mailbox = inbox_msg.header.mailbox;
                resp_msg.header.id = TEST_IPC_ASYNC_RSP;
                resp_msg.payload = (uint8_t*) "TEST_IPC_ASYNC_RSP";
                resp_msg.header.length = strlen((char*) resp_msg.payload);
                TestLoggerServer() << INFO << "Receive message: " << (char*) inbox_msg.payload;
                TestLoggerServer() << INFO << "Respond message: " << (char*) resp_msg.payload;
                alx::ControllerIf::getController().send(resp_msg.header.mailbox, resp_msg.header.id, resp_msg.payload, resp_msg.header.length);
                break;
            }
            case TEST_IPC_BLOCK_PUBLISH_REQ: {
                resp_msg.header.id = TEST_IPC_BLOCK_PUBLISH_RSP;
                resp_msg.payload = (uint8_t*) "TEST_IPC_BLOCK_PUBLISH_RSP";
                resp_msg.header.length = strlen((char*) resp_msg.payload);
                TestLoggerServer() << INFO << "Receive message: " << (char*) inbox_msg.payload;
                TestLoggerServer() << INFO << "Respond message: " << (char*) resp_msg.payload;
                alx::ControllerIf::getController().publish(resp_msg);
                break;
            }
            case TEST_IPC_ASYNC_PUBLISH_REQ: {
                resp_msg.header.id = TEST_IPC_ASYNC_PUBLISH_RSP;
                resp_msg.payload = (uint8_t*) "TEST_IPC_ASYNC_PUBLISH_RSP";
                resp_msg.header.length = strlen((char*) resp_msg.payload);
                TestLoggerServer() << INFO << "Receive message: " << (char*) inbox_msg.payload;
                TestLoggerServer() << INFO << "Respond message: " << (char*) resp_msg.payload;
                alx::ControllerIf::getController().publish(resp_msg);
                break;
            }
            default: {
                break;
            }
        }
    }

    TestLoggerServer() << INFO << "Leave function " << __PRETTY_FUNCTION__;
}

void TaskServer :: terminate(void) {
    TestLoggerServer() << INFO << "Enter function " << __PRETTY_FUNCTION__;
    TestLoggerServer() << INFO << "Leave function " << __PRETTY_FUNCTION__;
}

std::string TaskServer :: getName() const {
    TestLoggerServer() << INFO << "Enter function " << __PRETTY_FUNCTION__;
    TestLoggerServer() << INFO << "Leave function " << __PRETTY_FUNCTION__;
    return "TaskServer";
}