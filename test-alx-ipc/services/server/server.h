#ifndef SERVER_H
#define SERVER_H
#include "task_ipc.h"
#include "dynamic_buffer.h"
#include "transport_server_if.h"
#include "server_ipc_if.h"

namespace Test {
    class TaskServer : public alx::TaskIf {
    public:
        void entry(void) override;
        void init(void) override;
        void terminate(void) override;
        std::string getName() const override;
        TaskServer();
    private:
        using MsgBuffer = alx::DynamicBuffer<128U>;
        alx::Message resp_msg;
    };
}
#endif // SERVER_H