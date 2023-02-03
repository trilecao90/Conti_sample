#include "controllerIf.h"
#include "message_defs.h"

#include "mailboxes.h"
#include "messages.h"
#include "printers.h"
#include "server_ipc.h"

using namespace Test;

TaskServerIpcTest::TaskServerIpcTest(alxIpc::ServerIpcIf &ipcServer) : TaskIf(SERVER_IPC_MBOX, false), m_ipcServer(ipcServer) {
    TestLoggerServerIpc() << INFO << "Enter function " << __PRETTY_FUNCTION__;
    TestLoggerServerIpc() << INFO << "Leave function " << __PRETTY_FUNCTION__;
}

void TaskServerIpcTest::init(void) {
    TestLoggerServerIpc() << INFO << "Enter function " << __PRETTY_FUNCTION__;
    alx::ControllerIf::getController().subscribe(getMailbox(), TEST_IPC_BLOCK_PUBLISH_RSP);
    alx::ControllerIf::getController().subscribe(getMailbox(), TEST_IPC_ASYNC_PUBLISH_RSP);
    TestLoggerServerIpc() << INFO << "Leave function " << __PRETTY_FUNCTION__;
}

void TaskServerIpcTest::entry(void) {
    TestLoggerServerIpc() << INFO << "Enter function " << __PRETTY_FUNCTION__;

    while (!alx::ControllerIf::getController().isTerminating()) {
        alx::Message inbox_msg;
        alx::ControllerIf::getController().peek(inbox_msg.header);
        MsgBuffer msgBuffer(inbox_msg.header.length);
        inbox_msg.payload = msgBuffer;
        alx::ControllerIf::getController().get(inbox_msg, msgBuffer.capacity());
        fwd_msg = inbox_msg;
        switch (inbox_msg.header.id) {
            case TEST_IPC_BLOCK_REQ: {
                client_msg = inbox_msg;
                fwd_msg.header.mailbox = SERVER_MBOX;
                TestLoggerServerIpc() << INFO << "Receive message: " << (char*) inbox_msg.payload;
                TestLoggerServerIpc() << INFO << "Forward message: " << (char*) fwd_msg.payload;
                alx::ControllerIf::getController().send(fwd_msg.header.mailbox, fwd_msg.header.id, fwd_msg.payload, fwd_msg.header.length);
                break;
            }
            case TEST_IPC_ASYNC_REQ: {
                client_msg = inbox_msg;
                fwd_msg.header.mailbox = SERVER_MBOX;
                TestLoggerServerIpc() << INFO << "Receive message: " << (char*) inbox_msg.payload;
                TestLoggerServerIpc() << INFO << "Forward message: " << (char*) fwd_msg.payload;
                alx::ControllerIf::getController().send(fwd_msg.header.mailbox, fwd_msg.header.id, fwd_msg.payload, fwd_msg.header.length);
                break;
            }
            case TEST_IPC_BLOCK_PUBLISH_REQ: {
                client_msg = inbox_msg;
                TestLoggerServerIpc() << INFO << "Receive message: " << (char*) inbox_msg.payload;
                TestLoggerServerIpc() << INFO << "Forward message: " << (char*) fwd_msg.payload;
                alx::ControllerIf::getController().publish(fwd_msg);
                break;
            }
            case TEST_IPC_ASYNC_PUBLISH_REQ: {
                client_msg = inbox_msg;
                TestLoggerServerIpc() << INFO << "Receive message: " << (char*) inbox_msg.payload;
                TestLoggerServerIpc() << INFO << "Forward message: " << (char*) fwd_msg.payload;
                alx::ControllerIf::getController().publish(fwd_msg);
                break;
            }
            case TEST_IPC_BLOCK_RSP: {
                fwd_msg.header.mailbox = client_msg.header.mailbox;
                fwd_msg.header.token = client_msg.header.token;
                TestLoggerServerIpc() << INFO << "Receive message: " << (char*) inbox_msg.payload;
                TestLoggerServerIpc() << INFO << "Forward message: " << (char*) fwd_msg.payload;
                m_ipcServer.send(alxIpc::SendTypes::Block, fwd_msg.header.mailbox, fwd_msg.header.id, fwd_msg.header.token, fwd_msg.payload, fwd_msg.header.length);
                break;
            }
            case TEST_IPC_ASYNC_RSP: {
                fwd_msg.header.mailbox = client_msg.header.mailbox;
                fwd_msg.header.token = client_msg.header.token;
                TestLoggerServerIpc() << INFO << "Receive message: " << (char*) inbox_msg.payload;
                TestLoggerServerIpc() << INFO << "Forward message: " << (char*) fwd_msg.payload;
                m_ipcServer.send(alxIpc::SendTypes::Async, fwd_msg.header.mailbox, fwd_msg.header.id, fwd_msg.header.token, fwd_msg.payload, fwd_msg.header.length);
                break;
            }
            case TEST_IPC_BLOCK_PUBLISH_RSP: {
                fwd_msg.header.mailbox = client_msg.header.mailbox;
                fwd_msg.header.token = client_msg.header.token;
                TestLoggerServerIpc() << INFO << "Receive message: " << (char*) inbox_msg.payload;
                TestLoggerServerIpc() << INFO << "Forward message: " << (char*) fwd_msg.payload;
                m_ipcServer.send(alxIpc::SendTypes::Block, fwd_msg.header.mailbox, fwd_msg.header.id, fwd_msg.header.token, fwd_msg.payload, fwd_msg.header.length);
                break;
            }
            case TEST_IPC_ASYNC_PUBLISH_RSP: {
                fwd_msg.header.mailbox = client_msg.header.mailbox;
                fwd_msg.header.token = client_msg.header.token;
                TestLoggerServerIpc() << INFO << "Receive message: " << (char*) inbox_msg.payload;
                TestLoggerServerIpc() << INFO << "Forward message: " << (char*) fwd_msg.payload;
                m_ipcServer.send(alxIpc::SendTypes::Async, fwd_msg.header.mailbox, fwd_msg.header.id, fwd_msg.header.token, fwd_msg.payload, fwd_msg.header.length);
                break;
            }
            default: {
                break;
            }
        }
    }

    TestLoggerServerIpc() << INFO << "Leave function " << __PRETTY_FUNCTION__;
}

void TaskServerIpcTest::terminate(void) {
    TestLoggerServerIpc() << INFO << "Enter function " << __PRETTY_FUNCTION__;
    TestLoggerServerIpc() << INFO << "Leave function " << __PRETTY_FUNCTION__;
}

std::string TaskServerIpcTest::getName() const {
    TestLoggerServerIpc() << INFO << "Enter function " << __PRETTY_FUNCTION__;
    TestLoggerServerIpc() << INFO << "Leave function " << __PRETTY_FUNCTION__;
    return "TaskServerIpcTest";
}