#ifndef CLIENT_IPC_H
#define CLIENT_IPC_H

#include "transport_factory_if.h"
#include "notifier.h"
#include "timeout_constant.h"
#include "callable.h"
#include "scheduler_if.h"
#include <cstdint>

#include "client_ipc_if.h"

namespace Test {
    class ClientIpc : public ClientIpcIf {
    public:
        static ClientIpc& getInstance(); // singleton
        ~ClientIpc();
        bool initialize(TestSrvStsCb serversStateCallback, const DurationType& timeout = DEFAULT_INIT_TIMEOUT) override;
        void deinitialize(TestSrvStsCb serversStateCallback) override;
        uint32_t blockSend(const alxIpc::IdType& messageId, const void* messageBuff, const alxIpc::LengthType& msgLength, void* recvBuff, uint32_t& recvBuffSize, const uint32_t& recvTimeoutMs = RECEIVE_TIMEOUT) override;
        uint32_t asyncSend(const alxIpc::IdType& messageId, const void* messageBuff, const alxIpc::LengthType& msgLength, const uint32_t& uid = 0) override;
        void subscribe() override;

        void onMessage(const std::string name, const alxIpc::ConnectionType connectionType, const alxIpc::IdType transportId, const void* message, const alxIpc::LengthType length, const alxIpc::UidType uid);
        void onServersStateChanged(const alxIpc::ServersState& state);

    private:
        ClientIpc();
        void createIpcClient();
        void cleanup();

        const alxIpc::ConnectionParameters blockedServerAddress;
        const alxIpc::ConnectionParameters notificationServerAddress;
        const alxIpc::ConnectionParameters asyncServerAddress;

        alxIpc::TransportClientIf::UPtr ipcTransportClient;

        alx::Notifier<void(const ServersState&)> serverStateNotifier;
        ServersState ipcServerState;
    };
}
#endif // CLIENT_IPC_H