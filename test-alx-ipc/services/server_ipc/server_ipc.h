#ifndef SERVER_IPC_H
#define SERVER_IPC_H

#include "task_ipc.h"
#include "dynamic_buffer.h"
#include "transport_server_if.h"
#include "server_ipc_if.h"

namespace Test {
    class TaskServerIpcTest : public alx::TaskIf {
    public:
        // override TaskIf
        void entry(void) override;
        void init(void) override;
        void terminate(void) override;
        std::string getName() const override;
        TaskServerIpcTest(alxIpc::ServerIpcIf& ipcServer);
    private:
        using MsgBuffer = alx::DynamicBuffer<128U>;
        alxIpc::ServerIpcIf& m_ipcServer;
        alx::Message client_msg;
        alx::Message fwd_msg;
    };
}

#endif // SERVER_IPC_H