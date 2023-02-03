#include "controllerIf.h"
#include "socket_constant.h"
#include "tpsys.h"

#include "mailboxes.h"
#include "messages.h"
#include "printers.h"
#include "server_ipc.h"
#include "server.h"
#include "console.h"

using namespace alx;
using namespace alxIpc;
using namespace Test;

#define APP_NAME "test-alx-ipc"

namespace alxLog {
    alxLog::externalAppNameType externalAppName = APP_NAME;
}

int main() {
    alx::ControllerIf::prologue();

    tpSYS_ReturnCode_t ipc_init_result = tpSYS_initIPC(E_SYS_IPC_DBUS, nullptr, nullptr);

    if (E_SYS_IPC_RET_SUCCESS != ipc_init_result) {
        TestLoggerMgr() << ERROR << "Unable to initialize IPC, return value = " << ipc_init_result;
    }

    TaskServer serverTask;

    std::vector<alxIpc::ConnectionParameters> connectionParametersVector = {
        ConnectionParameters{BLOCKED,
                              socketConstant::TestIpcMgr::inet::IPC_SERVER_IP,
                              socketConstant::TestIpcMgr::inet::IPC_BLOCKED_PORT},
        ConnectionParameters{NOTIFICATION,
                              socketConstant::TestIpcMgr::inet::IPC_SERVER_IP,
                              socketConstant::TestIpcMgr::inet::IPC_NOTIFICATION_PORT},
        ConnectionParameters{ASYNC,
                              socketConstant::TestIpcMgr::inet::IPC_SERVER_IP,
                              socketConstant::TestIpcMgr::inet::IPC_ASYNC_PORT}};

    TaskIpcServer ServerIpcGeneral(connectionParametersVector,
                                  SERVER_IPC_MBOX,
                                  TEST_IPC_CONNECTION,
                                  TEST_IPC_DISCONNECTION);

    TaskServerIpcTest ServerIpcTask(ServerIpcGeneral);

    (void)alx::ControllerIf::getController().addTask(serverTask);
    (void)alx::ControllerIf::getController().addTask(ServerIpcTask);
    (void)alx::ControllerIf::getController().addTask(ServerIpcGeneral);

    (void)Test::TestConsole::GetInstance();

    alx::ControllerIf::getController().start();

    return 0;
}

/*
Test log:

uif63571@igd1946u:/exthome/uif63571/A7_v2/package/suz/vmbuild/tst/bin$ ./test-alx-ipc 
uif63571@igd1946u:/exthome/uif63571/A7_v2/package/suz/vmbuild/tst/bin$ ./ConsoleService 

TestIpcSample-SRVR[060795392]: Enter function Test::TaskServer::TaskServer()
TestIpcSample-SRVR[060795392]: Leave function Test::TaskServer::TaskServer()
TestIpcSample-SRVR_IPC[060795393]: Enter function Test::TaskServerIpcTest::TaskServerIpcTest(alxIpc::ServerIpcIf&)
TestIpcSample-SRVR_IPC[060795393]: Leave function Test::TaskServerIpcTest::TaskServerIpcTest(alxIpc::ServerIpcIf&)
TestIpcSample-SRVR[060795393]: Enter function virtual std::__cxx11::string Test::TaskServer::getName() const
TestIpcSample-SRVR[060795393]: Leave function virtual std::__cxx11::string Test::TaskServer::getName() const
TestIpcSample-SRVR[060795393]: Enter function virtual std::__cxx11::string Test::TaskServer::getName() const
TestIpcSample-SRVR[060795393]: Leave function virtual std::__cxx11::string Test::TaskServer::getName() const
TestIpcSample-SRVR[060795393]: Enter function virtual std::__cxx11::string Test::TaskServer::getName() const
TestIpcSample-SRVR[060795393]: Leave function virtual std::__cxx11::string Test::TaskServer::getName() const
TestIpcSample-SRVR_IPC[060795393]: Enter function virtual std::__cxx11::string Test::TaskServerIpcTest::getName() const
TestIpcSample-SRVR_IPC[060795393]: Leave function virtual std::__cxx11::string Test::TaskServerIpcTest::getName() const
TestIpcSample-SRVR_IPC[060795393]: Enter function virtual std::__cxx11::string Test::TaskServerIpcTest::getName() const
TestIpcSample-SRVR_IPC[060795393]: Leave function virtual std::__cxx11::string Test::TaskServerIpcTest::getName() const
TestIpcSample-SRVR[060795393]: Enter function virtual std::__cxx11::string Test::TaskServer::getName() const
TestIpcSample-SRVR[060795393]: Leave function virtual std::__cxx11::string Test::TaskServer::getName() const
TestIpcSample-SRVR[060795394]: Enter function virtual std::__cxx11::string Test::TaskServer::getName() const
TestIpcSample-SRVR[060795394]: Leave function virtual std::__cxx11::string Test::TaskServer::getName() const
TestIpcSample-SRVR_IPC[060795394]: Enter function virtual std::__cxx11::string Test::TaskServerIpcTest::getName() const
TestIpcSample-SRVR_IPC[060795394]: Leave function virtual std::__cxx11::string Test::TaskServerIpcTest::getName() const
TestIpcSample-SRVR_IPC[060795394]: Enter function virtual std::__cxx11::string Test::TaskServerIpcTest::getName() const
TestIpcSample-SRVR_IPC[060795394]: Leave function virtual std::__cxx11::string Test::TaskServerIpcTest::getName() const
TestIpcSample-SRVR_IPC[060795394]: Enter function virtual std::__cxx11::string Test::TaskServerIpcTest::getName() const
TestIpcSample-SRVR_IPC[060795394]: Leave function virtual std::__cxx11::string Test::TaskServerIpcTest::getName() const
ALX-CTRL setThreadName name TaskServerIpcTest was resized to TaskServerIpcTe
TestIpcSample-CNSL[060795394]: Enter function static Test::TestConsole& Test::TestConsole::GetInstance()
TestIpcSample-CNSL[060795394]: Enter function Test::TestConsole::TestConsole()
TestIpcSample-CLNT_IPC[060795396]: Enter function Test::ClientIpc::ClientIpc()
TestIpcSample-CLNT_IPC[060795396]: Enter function void Test::ClientIpc::createIpcClient()
TestIpcSample-CLNT_IPC[060795396]: Leave function void Test::ClientIpc::createIpcClient()
TestIpcSample-CLNT_IPC[060795396]: Leave function Test::ClientIpc::ClientIpc()
TestIpcSample-CLNT_IPC[060795396]: Enter function virtual bool Test::ClientIpc::initialize(Test::TestSrvStsCb, const DurationType&)
TestIpcSample-CNSL[060795396]: Enter function void Test::TestConsole::onConnectionStatus(const Test::ServersState&)
TestIpcSample-CNSL[060795396]: Server state currently: 0
TestIpcSample-CNSL[060795396]: Leave function void Test::TestConsole::onConnectionStatus(const Test::ServersState&)
TestIpcSample-CLNT_IPC[060795396]: Leave function virtual bool Test::ClientIpc::initialize(Test::TestSrvStsCb, const DurationType&)
TestIpcSample-CNSL[060795397]: Leave function Test::TestConsole::TestConsole()
TestIpcSample-CNSL[060795397]: Leave function static Test::TestConsole& Test::TestConsole::GetInstance()
TestIpcSample-SRVR[060795398]: Enter function virtual void Test::TaskServer::init()
TestIpcSample-SRVR[060795398]: Leave function virtual void Test::TaskServer::init()
TestIpcSample-SRVR_IPC[060795398]: Enter function virtual void Test::TaskServerIpcTest::init()
TestIpcSample-SRVR_IPC[060795398]: Leave function virtual void Test::TaskServerIpcTest::init()
ALX-CTRL[060795398]: STARTUP DONE: 3
TestIpcSample-SRVR[060795398]: Enter function virtual void Test::TaskServer::entry()
TestIpcSample-SRVR_IPC[060795398]: Enter function virtual void Test::TaskServerIpcTest::entry()
ALX-THR[060795398]:  Task Exited: IPC SERVER TASK
ALX-IPC-Cli[060795648]: validateInetClient: Ipc Client: 127.0.0.1-4057636 fd 11 connectionType BLOCKED inetClientSocketName 127.0.0.1:46814 SUCCESS
ALX-IPC-Srv[060795649]: acceptClient 127.0.0.1 new client fd 13 connectionType BLOCKED socketName 127.0.0.1:46814.blocked connCb true SUCCESS
ALX-IPC-Cli[060795649]: validateInetClient: Ipc Client: 127.0.0.1-4057636 fd 14 connectionType ASYNC inetClientSocketName 127.0.0.1:55504 SUCCESS
ALX-IPC-Task[060795649]: TaskIpcServer Inet-127.0.0.1:17061-127.0.0.1:17062-127.0.0.1:17060 CONNECTED client 127.0.0.1:46814 connType BLOCKED mailbox 1
ALX-IPC-Cli[060795649]: validateInetClient: Ipc Client: 127.0.0.1-4057636 fd 15 connectionType NOTIFICATION inetClientSocketName 127.0.0.1:57114 SUCCESS
ALX-IPC-Srv[060795649]: acceptClient 127.0.0.1 new client fd 16 connectionType NOTIFICATION socketName 127.0.0.1:57114.notification connCb true SUCCESS
ALX-IPC-Task[060795649]: TaskIpcServer Inet-127.0.0.1:17061-127.0.0.1:17062-127.0.0.1:17060 CONNECTED client 127.0.0.1:57114 connType NOTIFICATION mailbox 2
TestIpcSample-CLNT_IPC[060795650]: Enter function void Test::ClientIpc::onServersStateChanged(const alxIpc::ServersState&)
ALX-IPC-Srv[060795650]: acceptClient 127.0.0.1 new client fd 17 connectionType ASYNC socketName 127.0.0.1:55504.async connCb true SUCCESS
TestIpcSample-CNSL[060795650]: Enter function void Test::TestConsole::onConnectionStatus(const Test::ServersState&)
ALX-IPC-Task[060795650]: TaskIpcServer Inet-127.0.0.1:17061-127.0.0.1:17062-127.0.0.1:17060 CONNECTED client 127.0.0.1:55504 connType ASYNC mailbox 3
TestIpcSample-CNSL[060795650]: Server state currently: 2
TestIpcSample-CNSL[060795650]: Leave function void Test::TestConsole::onConnectionStatus(const Test::ServersState&)
TestIpcSample-CLNT_IPC[060795650]: Leave function void Test::ClientIpc::onServersStateChanged(const alxIpc::ServersState&)
TestIpcSample-CLNT_IPC[060795650]: Enter function void Test::ClientIpc::onServersStateChanged(const alxIpc::ServersState&)
TestIpcSample-CNSL[060795650]: Enter function void Test::TestConsole::onConnectionStatus(const Test::ServersState&)
TestIpcSample-CNSL[060795650]: Server state currently: 2
TestIpcSample-CNSL[060795650]: Leave function void Test::TestConsole::onConnectionStatus(const Test::ServersState&)
TestIpcSample-CLNT_IPC[060795650]: Leave function void Test::ClientIpc::onServersStateChanged(const alxIpc::ServersState&)
TestIpcSample-CLNT_IPC[060795650]: Enter function void Test::ClientIpc::onServersStateChanged(const alxIpc::ServersState&)
TestIpcSample-CNSL[060795650]: Enter function void Test::TestConsole::onConnectionStatus(const Test::ServersState&)
TestIpcSample-CNSL[060795650]: Server state currently: 0
TestIpcSample-CNSL[060795650]: Leave function void Test::TestConsole::onConnectionStatus(const Test::ServersState&)
TestIpcSample-CLNT_IPC[060795650]: Leave function void Test::ClientIpc::onServersStateChanged(const alxIpc::ServersState&)

ALX-IPC-Cli[060798199]: connectUnixClientToServer: Ipc Client: ConClnt-4057636 client socket name: ConClnt-4057636.async server: ConSrvr.async connectionType: ASYNC fd 18 SUCCESS

Console command: test-alx-ipc send_block_publish_msg

TestIpcSample-CNSL[060835218]: Enter function void Test::TestConsole::consoleCallback(alxConsole::ConsoleStringVector&)
TestIpcSample-CNSL[060835218]: Receive command: send_block_publish_msg
TestIpcSample-CNSL[060835218]: Send message: TEST_IPC_BLOCK_PUBLISH_REQ
TestIpcSample-CLNT_IPC[060835218]: Enter function virtual uint32_t Test::ClientIpc::blockSend(const IdType&, const void*, const LengthType&, void*, uint32_t&, const uint32_t&)
TestIpcSample-CLNT_IPC[060835218]: Send message: TEST_IPC_BLOCK_PUBLISH_REQ
TestIpcSample-SRVR_IPC[060835219]: Receive message: TEST_IPC_BLOCK_PUBLISH_REQ
TestIpcSample-SRVR_IPC[060835219]: Forward message: TEST_IPC_BLOCK_PUBLISH_REQ
TestIpcSample-SRVR[060835219]: Receive message: TEST_IPC_BLOCK_PUBLISH_REQ
TestIpcSample-SRVR[060835219]: Respond message: TEST_IPC_BLOCK_PUBLISH_RSP
TestIpcSample-SRVR_IPC[060835219]: Receive message: TEST_IPC_BLOCK_PUBLISH_RSP
TestIpcSample-SRVR_IPC[060835219]: Forward message: TEST_IPC_BLOCK_PUBLISH_RSP
TestIpcSample-CLNT_IPC[060835220]: Leave function virtual uint32_t Test::ClientIpc::blockSend(const IdType&, const void*, const LengthType&, void*, uint32_t&, const uint32_t&)
TestIpcSample-CNSL[060835220]: Receive message: TEST_IPC_BLOCK_PUBLISH_RSP
TestIpcSample-CNSL[060835220]: Leave function void Test::TestConsole::consoleCallback(alxConsole::ConsoleStringVector&)

Console command: test-alx-ipc send_block_msg

TestIpcSample-CNSL[060862947]: Enter function void Test::TestConsole::consoleCallback(alxConsole::ConsoleStringVector&)
TestIpcSample-CNSL[060862947]: Receive command: send_block_msg
TestIpcSample-CNSL[060862947]: Send message: TEST_IPC_BLOCK_REQ
TestIpcSample-CLNT_IPC[060862947]: Enter function virtual uint32_t Test::ClientIpc::blockSend(const IdType&, const void*, const LengthType&, void*, uint32_t&, const uint32_t&)
TestIpcSample-CLNT_IPC[060862947]: Send message: TEST_IPC_BLOCK_REQ
TestIpcSample-SRVR_IPC[060862988]: Receive message: TEST_IPC_BLOCK_REQLISH_RSP
TestIpcSample-SRVR_IPC[060862988]: Forward message: TEST_IPC_BLOCK_REQLISH_RSP
TestIpcSample-SRVR[060862989]: Receive message: TEST_IPC_BLOCK_REQLISH_REQ
TestIpcSample-SRVR[060862989]: Respond message: TEST_IPC_BLOCK_RSP
TestIpcSample-SRVR_IPC[060862989]: Receive message: TEST_IPC_BLOCK_RSPLISH_RSP
TestIpcSample-SRVR_IPC[060862989]: Forward message: TEST_IPC_BLOCK_RSPLISH_RSP
TestIpcSample-CLNT_IPC[060862989]: Leave function virtual uint32_t Test::ClientIpc::blockSend(const IdType&, const void*, const LengthType&, void*, uint32_t&, const uint32_t&)
TestIpcSample-CNSL[060862989]: Receive message: TEST_IPC_BLOCK_RSP
TestIpcSample-CNSL[060862989]: Leave function void Test::TestConsole::consoleCallback(alxConsole::ConsoleStringVector&)

Console command: test-alx-ipc send_async_publish_msg

TestIpcSample-CNSL[060889279]: Enter function void Test::TestConsole::consoleCallback(alxConsole::ConsoleStringVector&)
TestIpcSample-CNSL[060889279]: Receive command: send_async_publish_msg
TestIpcSample-CNSL[060889279]: Send message: TEST_IPC_ASYNC_PUBLISH_REQ
TestIpcSample-CLNT_IPC[060889279]: Enter function virtual uint32_t Test::ClientIpc::asyncSend(const IdType&, const void*, const LengthType&, const uint32_t&)
TestIpcSample-CLNT_IPC[060889279]: Send message: TEST_IPC_ASYNC_PUBLISH_REQ
TestIpcSample-CLNT_IPC[060889279]: Leave function virtual uint32_t Test::ClientIpc::asyncSend(const IdType&, const void*, const LengthType&, const uint32_t&)
TestIpcSample-CNSL[060889279]: Leave function void Test::TestConsole::consoleCallback(alxConsole::ConsoleStringVector&)
TestIpcSample-SRVR_IPC[060889280]: Receive message: TEST_IPC_ASYNC_PUBLISH_REQ
TestIpcSample-SRVR_IPC[060889280]: Forward message: TEST_IPC_ASYNC_PUBLISH_REQ
TestIpcSample-SRVR[060889280]: Receive message: TEST_IPC_ASYNC_PUBLISH_REQ
TestIpcSample-SRVR[060889280]: Respond message: TEST_IPC_ASYNC_PUBLISH_RSP
TestIpcSample-SRVR_IPC[060889280]: Receive message: TEST_IPC_ASYNC_PUBLISH_RSP
TestIpcSample-SRVR_IPC[060889280]: Forward message: TEST_IPC_ASYNC_PUBLISH_RSP
TestIpcSample-CLNT_IPC[060889281]: Enter function void Test::ClientIpc::onMessage(std::__cxx11::string, alxIpc::ConnectionType, alxIpc::IdType, const void*, alxIpc::LengthType, alxIpc::UidType)
TestIpcSample-CLNT_IPC[060889281]: Receive message: TEST_IPC_ASYNC_PUBLISH_RSP
TestIpcSample-CLNT_IPC[060889281]: Leave function void Test::ClientIpc::onMessage(std::__cxx11::string, alxIpc::ConnectionType, alxIpc::IdType, const void*, alxIpc::LengthType, alxIpc::UidType)

Console command: test-alx-ipc send_async_msg

TestIpcSample-CNSL[060905146]: Enter function void Test::TestConsole::consoleCallback(alxConsole::ConsoleStringVector&)
TestIpcSample-CNSL[060905146]: Receive command: send_async_msg
TestIpcSample-CNSL[060905146]: Send message: TEST_IPC_ASYNC_REQ
TestIpcSample-CLNT_IPC[060905146]: Enter function virtual uint32_t Test::ClientIpc::asyncSend(const IdType&, const void*, const LengthType&, const uint32_t&)
TestIpcSample-CLNT_IPC[060905146]: Send message: TEST_IPC_ASYNC_REQ
TestIpcSample-CLNT_IPC[060905147]: Leave function virtual uint32_t Test::ClientIpc::asyncSend(const IdType&, const void*, const LengthType&, const uint32_t&)
TestIpcSample-CNSL[060905147]: Leave function void Test::TestConsole::consoleCallback(alxConsole::ConsoleStringVector&)
TestIpcSample-SRVR_IPC[060905188]: Receive message: TEST_IPC_ASYNC_REQLISH_RSP
TestIpcSample-SRVR_IPC[060905188]: Forward message: TEST_IPC_ASYNC_REQLISH_RSP
TestIpcSample-SRVR[060905189]: Receive message: TEST_IPC_ASYNC_REQLISH_REQ
TestIpcSample-SRVR[060905189]: Respond message: TEST_IPC_ASYNC_RSP
TestIpcSample-SRVR_IPC[060905189]: Receive message: TEST_IPC_ASYNC_RSPLISH_RSP
TestIpcSample-SRVR_IPC[060905189]: Forward message: TEST_IPC_ASYNC_RSPLISH_RSP
TestIpcSample-CLNT_IPC[060905189]: Enter function void Test::ClientIpc::onMessage(std::__cxx11::string, alxIpc::ConnectionType, alxIpc::IdType, const void*, alxIpc::LengthType, alxIpc::UidType)
TestIpcSample-CLNT_IPC[060905189]: Receive message: TEST_IPC_ASYNC_RSPLISH_RSP
TestIpcSample-CLNT_IPC[060905189]: Leave function void Test::ClientIpc::onMessage(std::__cxx11::string, alxIpc::ConnectionType, alxIpc::IdType, const void*, alxIpc::LengthType, alxIpc::UidType)
*/