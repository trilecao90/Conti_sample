#ifndef CONSOLE_H
#define CONSOLE_H

#include "ConsoleMgrIf.h"
#include "client_ipc_if.h"

namespace Test {
    class TestConsole {
    public:
        ~TestConsole();
        static TestConsole& GetInstance(void); // singleton

    private:
        TestConsole(void);
        void onConnectionStatus(const Test::ServersState& serverState);
        /// @brief Callback function that receives commands from Console Service
        /// @details This function must parse the command in argc argv format and trigger required actions.
        /// @return void
        void consoleCallback(alxConsole::ConsoleStringVector& arguments);
    };
};
#endif // CONSOLE_H
