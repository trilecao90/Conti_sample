/* ************************************************************************
 * Copyright (C) 2021 Continental AG and subsidiaries
 *
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 * The code contains Continental Confidential Proprietary Information.
 * ************************************************************************/

/* @file        groupname_constants.h
 * @brief       group name definitions found in etc/passwd declared in gm/main/imx-<target>-gm/config/pd_passwd
 *
 * @project     FC Telematics
 * @author      Nikunj Patel
 * @date        26-February 2021
 *
 ***************************************************************************/
#ifndef GROUPNAME_CONSTANTS_H
#define GROUPNAME_CONSTANTS_H

namespace groupNameConstants {

constexpr const char* VOICEMGR_GROUPNAME   = "voicemgr";
constexpr const char* LOGMGR_GROUPNAME     = "logmgr";
constexpr const char* FILEMGR_GROUPNAME    = "filemgr";
constexpr const char* SDB_GROUPNAME        = "sdb";
constexpr const char* MOBILEMGR_GROUPNAME  = "mobilemgr";
constexpr const char* DIAGMGR_GROUPNAME    = "diagmgr";
constexpr const char* CDLMGR_GROUPNAME     = "cdlmgr";
constexpr const char* FAULTMGR_GROUPNAME   = "faultmgr";
constexpr const char* EVENTMGR_GROUPNAME   = "eventmgr";
constexpr const char* SWLMGR_GROUPNAME     = "swlmgr";
constexpr const char* ETHMGR_GROUPNAME     = "ethmgr";
constexpr const char* IPMGR_GROUPNAME      = "ipmgr";
constexpr const char* ANTENNAMGR_GROUPNAME = "antennamgr";
constexpr const char* TIMEMASTER_GROUPNAME = "timemaster";
constexpr const char* FTRMGR_GROUPNAME     = "ftrmgr";
constexpr const char* REMOTECTRL_GROUPNAME = "remotectrl";
constexpr const char* REMOTESRVC_GROUPNAME = "remotesrvc";
constexpr const char* CFGMGR_GROUPNAME     = "cfgmgr";
constexpr const char* CONNCORE_GROUPNAME   = "conncore";
constexpr const char* TESTIPC_GROUPNAME    = "testipc";
}
#endif
