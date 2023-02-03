/* ************************************************************************
 * Copyright (C) 2021 Continental AG and subsidiaries
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains Continental Confidential Proprietary Information.
 * ************************************************************************/

/** @file socket_constant.h
 * common log stream inet types
 *
 * @project             FC Telematics
 * @author              Alex Maya
 * @date                21-Jan-2021
 *
 *****************************************************************************/

#ifndef INET_SOCKET_CONSTANT_H
#define INET_SOCKET_CONSTANT_H

namespace socketConstant {
    const std::string LOCAL_IP_ADDRESS = "127.0.0.1";
#ifdef HOST_VM
    const std::string NAD_IPC_SERVER_IP = LOCAL_IP_ADDRESS;
    const std::string A35_IPC_SERVER_IP = LOCAL_IP_ADDRESS;
#else
    const std::string NAD_IPC_SERVER_IP = "192.168.225.1";
    const std::string A35_IPC_SERVER_IP = "192.168.0.2";
#endif

    namespace logmgr {
        namespace inet {

            static const std::string IPC_SERVER_IP      = LOCAL_IP_ADDRESS;

            static const std::string STREAM_SERVER_IP   = A35_IPC_SERVER_IP;

            static const uint16_t IPC_BLOCKED_PORT      = 17000U;

            static const uint16_t IPC_NOTIFICATION_PORT = 17001U;

            static const uint16_t STREAM_SERVER_PORT    = 17002U;

            // need to manually add core.sx file under /data/log/cores for testing
            static const uint16_t STREAM_SERVER_PORT_M4 = 17003U;

            // need to manually change /opt/conti/etc/syslog-ng.conf to add messages2 to /data/log/ for testing
            static const uint16_t STREAM_SERVER_PORT_A7 = 17004U;
        }

        namespace udp {

            static const std::string UDP_SERVER_IP      = "192.168.0.1";

            static const uint16_t UDP_PORT              = 17010U;

            static const std::string STREAM_SERVER_READY_UDP_MSG     = "logmgr stream server ready\n";

            static const std::string  M4_STREAM_SERVER_READY_UDP_MSG = "logmgr m4 stream server ready\n";

            static const std::string  A7_STREAM_SERVER_READY_UDP_MSG = "logmgr a7 stream server ready\n";

        }
    }
    namespace referenceVoice {
        namespace inet {
            static const std::string IPC_SERVER_IP      = NAD_IPC_SERVER_IP; // should be ip address of processor where server resides
            static const uint16_t IPC_BLOCKED_PORT      = 17013U;
            static const uint16_t IPC_NOTIFICATION_PORT = 17014U;
        }
    }
    namespace antennamgr {
        namespace inet {
            static const std::string IPC_SERVER_IP      = NAD_IPC_SERVER_IP; // server resides on A7
            static const uint16_t IPC_BLOCKED_PORT      = 17021U;
            static const uint16_t IPC_NOTIFICATION_PORT = 17022U;
        }
    }
    namespace alcmgr {
        namespace inet {
            static const std::string IPC_SERVER_IP          = LOCAL_IP_ADDRESS;
            static const std::string IPC_STREAM_SERVER_IP   = A35_IPC_SERVER_IP;
            static const uint16_t IPC_ASYNC_PORT            = 17031U;
            static const std::string IPC_NAD_SERVER_IP      = NAD_IPC_SERVER_IP; // server resides on A7
            static const uint16_t IPC_NAD_ASYNC_PORT        = 17032U;
        }
    }
    namespace mobilemgr {
        namespace inet {
            static const std::string IPC_SERVER_IP      = NAD_IPC_SERVER_IP; // server resides on A7
            static const uint16_t IPC_BLOCKED_PORT      = 17025U;
            static const uint16_t IPC_NOTIFICATION_PORT = 17026U;
        }
    }
    namespace voicemgr {
        namespace inet {
            static const std::string IPC_SERVER_IP      = NAD_IPC_SERVER_IP; // server resides on A7
            static const uint16_t IPC_BLOCKED_PORT      = 17028U;
            static const uint16_t IPC_NOTIFICATION_PORT = 17029U;
        }
    }
    namespace FtrMgr {
        namespace inet {
            static const std::string IPC_SERVER_IP      = NAD_IPC_SERVER_IP; // server resides on A7
            static const uint16_t IPC_ASYNC_PORT        = 17033U;
            static const uint16_t IPC_BLOCKED_PORT      = 17034U;
        }
    }
    namespace remoteCtrlMgr {
        namespace inet {
            static const std::string IPC_SERVER_IP      = NAD_IPC_SERVER_IP; // server resides on A7
            static const uint16_t IPC_ASYNC_PORT        = 17036U;
            static const uint16_t IPC_BLOCKED_PORT      = 17037U;
            static const uint16_t IPC_NOTIFICATION_PORT = 17038U;
        }
    }
    namespace cfgmgr {
        namespace inet {
            static const std::string IPC_SERVER_IP      = NAD_IPC_SERVER_IP; // server resides on A7
            static const uint16_t IPC_ASYNC_PORT        = 17040U;
            static const uint16_t IPC_BLOCKED_PORT      = 17041U;
        }
    }
    namespace connectedcore{
            namespace inet {
                static const std::string IPC_SERVER_IP     = NAD_IPC_SERVER_IP; // server resides on A7
                static const uint16_t IPC_ASYNC_PORT       = 17043U;
                static const uint16_t IPC_BLOCKED_PORT     = 17044U;
                static const uint16_t IPC_NOTIFICATION_PORT= 17045U;
            }
    }
    namespace TestIpcMgr{
            namespace inet {
                static const std::string IPC_SERVER_IP     = NAD_IPC_SERVER_IP; // server resides on A7
                static const uint16_t IPC_ASYNC_PORT       = 17060U;
                static const uint16_t IPC_BLOCKED_PORT     = 17061U;
                static const uint16_t IPC_NOTIFICATION_PORT= 17062U;
            }
    }
}
#endif //INET_SOCKET_CONSTANT_H
