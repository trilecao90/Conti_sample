#ifndef CLIENT_IPC_IF_H
#define CLIENT_IPC_IF_H

#include "transport_factory_if.h"
#include "timeout_constant.h"
#include "callable.h"
#include "scheduler_if.h"
#include <cstdint>

namespace Test {
    enum class ServersState : uint8_t {
        serversUp = 0,
        serversDown,
        serversPartiallyAvailable,
    };

    // Callback type that returns the IPC server state
    using TestSrvStsCb = alx::CallableIf<void(const ServersState&)>::UPtr;
    
    // Definition of duration type
    using DurationType = std::chrono::duration<uint32_t, std::milli>;

    static constexpr const alx::SchedulerIf::Duration ASYNC_GET_TIMEOUT = std::chrono::seconds(10);
    static constexpr const uint32_t RECEIVE_TIMEOUT = 5000U;

    // @brief constant that define the default timeout for the IPC initialization
    const DurationType DEFAULT_INIT_TIMEOUT = std::chrono::milliseconds(0);

    class ClientIpcIf {
    public:
        static ClientIpcIf& getClient();
        virtual ~ClientIpcIf() = default;
        virtual bool initialize(TestSrvStsCb serversStateCallback, const DurationType& timeout = DEFAULT_INIT_TIMEOUT) = 0;
        virtual void deinitialize(TestSrvStsCb serversStateCallback) = 0;
        virtual uint32_t blockSend(const alxIpc::IdType& messageId, const void* messageBuff, const alxIpc::LengthType& msgLength, void* recvBuff, uint32_t& recvBuffSize, const uint32_t& recvTimeoutMs = RECEIVE_TIMEOUT) = 0;
        virtual uint32_t asyncSend(const alxIpc::IdType& messageId, const void* messageBuff, const alxIpc::LengthType& msgLength, const uint32_t& uid = 0) = 0;
        virtual void subscribe() = 0;
    };
}

#endif // CLIENT_IPC_IF_H