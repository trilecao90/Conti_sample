#include <string>
#include "groupname_constants.h"
#include "timeout_constant.h"
#include "socket_constant.h"

#include "mailboxes.h"
#include "messages.h"
#include "printers.h"

#include "client_ipc.h"

using namespace Test;

ClientIpcIf& ClientIpcIf::getClient() {
    return ClientIpc::getInstance();
}

ClientIpc& ClientIpc::getInstance() {
    static ClientIpc instance;
    return instance;
}

ClientIpc::ClientIpc() : blockedServerAddress(alxIpc::ConnectionParameters{alxIpc::BLOCKED,
                                                                            socketConstant::TestIpcMgr::inet::IPC_SERVER_IP,
                                                                            socketConstant::TestIpcMgr::inet::IPC_BLOCKED_PORT}),
                            notificationServerAddress(alxIpc::ConnectionParameters{alxIpc::NOTIFICATION,
                                                                            socketConstant::TestIpcMgr::inet::IPC_SERVER_IP,
                                                                            socketConstant::TestIpcMgr::inet::IPC_NOTIFICATION_PORT}),
                            asyncServerAddress(alxIpc::ConnectionParameters{alxIpc::ASYNC,
                                                                            socketConstant::TestIpcMgr::inet::IPC_SERVER_IP,
                                                                            socketConstant::TestIpcMgr::inet::IPC_ASYNC_PORT}) {
    TestLoggerClient() << INFO << "Enter function " << __PRETTY_FUNCTION__;
    createIpcClient();
    TestLoggerClient() << INFO << "Leave function " << __PRETTY_FUNCTION__;
}

ClientIpc::~ClientIpc() {
    TestLoggerClient() << INFO << "Enter function " << __PRETTY_FUNCTION__;
    cleanup();
    TestLoggerClient() << INFO << "Leave function " << __PRETTY_FUNCTION__;
}

void ClientIpc::cleanup() {
    TestLoggerClient() << INFO << "Enter function " << __PRETTY_FUNCTION__;
    if(ipcTransportClient) {
        ipcTransportClient->terminate();
    }
    ipcTransportClient.reset();
    serverStateNotifier.clear();
    TestLoggerClient() << INFO << "Leave function " << __PRETTY_FUNCTION__;
}

void ClientIpc::createIpcClient() {
    TestLoggerClient() << INFO << "Enter function " << __PRETTY_FUNCTION__;

    static std::mutex ipcMutex;
    std::lock_guard<std::mutex> lock(ipcMutex);
    
    std::vector<alxIpc::ConnectionParameters> connectionParams = {blockedServerAddress, asyncServerAddress, notificationServerAddress};

    ipcTransportClient = alxIpc::TransportFactoryIf::get().makeTransportClient(
        connectionParams,
        alx::simpleBind(this, &ClientIpc::onMessage),
        nullptr,                                                    // gives info on server connection if required
        nullptr,                                                    // gives detailed reason on server disconnect if required
        "",                                                         // client user check if required for client security
        alx::GroupArray({groupNameConstants::TESTIPC_GROUPNAME}) // user check if its in the service group if required for client security
    );

    TestLoggerClient() << INFO << "Leave function " << __PRETTY_FUNCTION__;
}

bool ClientIpc::initialize(TestSrvStsCb serversStateCallback, const DurationType& timeout) {
    TestLoggerClient() << INFO << "Enter function " << __PRETTY_FUNCTION__;

    if (!ipcTransportClient.get()) {
        createIpcClient();
    }

    (void)serverStateNotifier.addAndTrigger(std::move(serversStateCallback), ipcServerState);

    TestLoggerClient() << INFO << "Leave function " << __PRETTY_FUNCTION__;

    return ipcTransportClient->start(alx::simpleBind(this, &ClientIpc::onServersStateChanged), timeout);
}

void ClientIpc::deinitialize(TestSrvStsCb serversStateCallback) {
    TestLoggerClient() << INFO << "Enter function " << __PRETTY_FUNCTION__;

    (void)serverStateNotifier.removeCallable(std::move(serversStateCallback));

    if (serverStateNotifier.empty()) { // if last subscriber
        cleanup();
    }

    TestLoggerClient() << INFO << "Leave function " << __PRETTY_FUNCTION__;
}

void ClientIpc::onMessage(const std::string, const alxIpc::ConnectionType, const alxIpc::IdType messageID, const void* message, const alxIpc::LengthType length, const alxIpc::UidType) {
    TestLoggerClient() << INFO << "Enter function " << __PRETTY_FUNCTION__;

    switch (messageID) {
        case TEST_IPC_ASYNC_RSP: {
            TestLoggerClient() << INFO << "Receive message: " << (char*) message;
            break;
        }
        case TEST_IPC_ASYNC_PUBLISH_RSP: {
            TestLoggerClient() << INFO << "Receive message: " << (char*) message;
            break;
        }
        default: {
            break;
        }
    }

    TestLoggerClient() << INFO << "Leave function " << __PRETTY_FUNCTION__;
}

void ClientIpc::onServersStateChanged(const alxIpc::ServersState& state) {
    TestLoggerClient() << INFO << "Enter function " << __PRETTY_FUNCTION__;

    std::unique_lock<std::recursive_mutex> lock(serverStateNotifier.getLock());

    switch (state) {
        case alxIpc::ServersState::serversUp: {
            ipcServerState = ServersState::serversUp;
            break;        
        }

        case alxIpc::ServersState::serversPartiallyAvailable: {
            ipcServerState = ServersState::serversPartiallyAvailable;
            break;
        }

        case alxIpc::ServersState::serversDown: {
            ipcServerState = ServersState::serversDown;
            break;
        }
        default: {
            ipcServerState = ServersState::serversDown;
            break;
        }
    }
    serverStateNotifier.notifyPermanentCallable(ipcServerState);

    TestLoggerClient() << INFO << "Leave function " << __PRETTY_FUNCTION__;
}

void ClientIpc::subscribe() {
    TestLoggerClient() << INFO << "Enter function " << __PRETTY_FUNCTION__;
    TestLoggerClient() << INFO << "Leave function " << __PRETTY_FUNCTION__;
}

uint32_t ClientIpc::blockSend(const alxIpc::IdType& messageId, const void* messageBuff, const alxIpc::LengthType& msgLength, void* recvBuff, uint32_t& recvBuffSize, const uint32_t& recvTimeoutMs) {
    TestLoggerClient() << INFO << "Enter function " << __PRETTY_FUNCTION__;

    uint32_t result;
    if (ipcTransportClient) {
        TestLoggerClient() << INFO << "Send message: " << (char*) messageBuff;
        result = ipcTransportClient->blockSend(blockedServerAddress.getAddress(), messageId, messageBuff, msgLength, recvBuff, recvBuffSize, recvTimeoutMs);
    }
    else {
        TestLoggerClient() << ERROR << "ipcTransportClient is not created";
    }

    TestLoggerClient() << INFO << "Leave function " << __PRETTY_FUNCTION__;

    return result;
}

uint32_t ClientIpc::asyncSend(const alxIpc::IdType& messageId, const void* messageBuff, const alxIpc::LengthType& msgLength, const uint32_t& uid) {
    TestLoggerClient() << INFO << "Enter function " << __PRETTY_FUNCTION__;

    uint32_t result;
    if (ipcTransportClient) {
        TestLoggerClient() << INFO << "Send message: " << (char*) messageBuff;
        result = ipcTransportClient->asyncSend(asyncServerAddress.getAddress(), messageId, messageBuff, msgLength);
    }
    else {
        TestLoggerClient() << ERROR << "ipcTransportClient is not created";
    }

    TestLoggerClient() << INFO << "Leave function " << __PRETTY_FUNCTION__;

    return result;
}