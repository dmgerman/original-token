multiline_comment|/*&n;** -----------------------------------------------------------------------------&n;**&n;**  Perle Specialix driver for Linux&n;**  Ported from existing RIO Driver for SCO sources.&n; *&n; *  (C) 1990 - 2000 Specialix International Ltd., Byfleet, Surrey, UK.&n; *&n; *      This program is free software; you can redistribute it and/or modify&n; *      it under the terms of the GNU General Public License as published by&n; *      the Free Software Foundation; either version 2 of the License, or&n; *      (at your option) any later version.&n; *&n; *      This program is distributed in the hope that it will be useful,&n; *      but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *      GNU General Public License for more details.&n; *&n; *      You should have received a copy of the GNU General Public License&n; *      along with this program; if not, write to the Free Software&n; *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**&t;Module&t;&t;: func.h&n;**&t;SID&t;&t;: 1.3&n;**&t;Last Modified&t;: 11/6/98 11:34:10&n;**&t;Retrieved&t;: 11/6/98 11:34:21&n;**&n;**  ident @(#)func.h&t;1.3&n;**&n;** -----------------------------------------------------------------------------&n;*/
macro_line|#ifndef __func_h_def
DECL|macro|__func_h_def
mdefine_line|#define __func_h_def
macro_line|#ifdef SCCS_LABELS
macro_line|#ifndef lint
DECL|variable|_func_h_sccs_
r_static
r_char
op_star
id|_func_h_sccs_
op_assign
l_string|&quot;@(#)func.h&t;1.3&quot;
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/* rioboot.c */
r_int
id|RIOBootCodeRTA
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|DownLoad
op_star
)paren
suffix:semicolon
r_int
id|RIOBootCodeHOST
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_register
r_struct
id|DownLoad
op_star
)paren
suffix:semicolon
r_int
id|RIOBootCodeUNKNOWN
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|DownLoad
op_star
)paren
suffix:semicolon
r_void
id|msec_timeout
c_func
(paren
r_struct
id|Host
op_star
)paren
suffix:semicolon
r_int
id|RIOBootRup
c_func
(paren
r_struct
id|rio_info
op_star
comma
id|uint
comma
r_struct
id|Host
op_star
comma
r_struct
id|PKT
op_star
)paren
suffix:semicolon
r_int
id|RIOBootComplete
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|Host
op_star
comma
id|uint
comma
r_struct
id|PktCmd
op_star
)paren
suffix:semicolon
r_int
id|RIOBootOk
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|Host
op_star
comma
id|ulong
)paren
suffix:semicolon
r_int
id|RIORtaBound
c_func
(paren
r_struct
id|rio_info
op_star
comma
id|uint
)paren
suffix:semicolon
r_void
id|FillSlot
c_func
(paren
r_int
comma
r_int
comma
id|uint
comma
r_struct
id|Host
op_star
)paren
suffix:semicolon
multiline_comment|/* riocmd.c */
r_int
id|RIOFoadRta
c_func
(paren
r_struct
id|Host
op_star
comma
r_struct
id|Map
op_star
)paren
suffix:semicolon
r_int
id|RIOZombieRta
c_func
(paren
r_struct
id|Host
op_star
comma
r_struct
id|Map
op_star
)paren
suffix:semicolon
r_int
id|RIOCommandRta
c_func
(paren
r_struct
id|rio_info
op_star
comma
id|uint
comma
r_int
(paren
op_star
id|func
)paren
(paren
r_struct
id|Host
op_star
comma
r_struct
id|Map
op_star
)paren
)paren
suffix:semicolon
r_int
id|RIOIdentifyRta
c_func
(paren
r_struct
id|rio_info
op_star
comma
id|caddr_t
)paren
suffix:semicolon
r_int
id|RIOKillNeighbour
c_func
(paren
r_struct
id|rio_info
op_star
comma
id|caddr_t
)paren
suffix:semicolon
r_int
id|RIOSuspendBootRta
c_func
(paren
r_struct
id|Host
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|RIOFoadWakeup
c_func
(paren
r_struct
id|rio_info
op_star
)paren
suffix:semicolon
r_int
id|RIOCommandRup
c_func
(paren
r_struct
id|rio_info
op_star
comma
id|uint
comma
r_struct
id|Host
op_star
comma
r_struct
id|PKT
op_star
)paren
suffix:semicolon
r_struct
id|CmdBlk
op_star
id|RIOGetCmdBlk
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|RIOFreeCmdBlk
c_func
(paren
r_struct
id|CmdBlk
op_star
)paren
suffix:semicolon
r_int
id|RIOQueueCmdBlk
c_func
(paren
r_struct
id|Host
op_star
comma
id|uint
comma
r_struct
id|CmdBlk
op_star
)paren
suffix:semicolon
r_void
id|RIOPollHostCommands
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|Host
op_star
)paren
suffix:semicolon
r_int
id|RIOStrlen
c_func
(paren
r_register
r_char
op_star
)paren
suffix:semicolon
r_int
id|RIOStrCmp
c_func
(paren
r_register
r_char
op_star
comma
r_register
r_char
op_star
)paren
suffix:semicolon
r_int
id|RIOStrnCmp
c_func
(paren
r_register
r_char
op_star
comma
r_register
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|RIOStrNCpy
c_func
(paren
r_char
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|RIOWFlushMark
c_func
(paren
r_int
comma
r_struct
id|CmdBlk
op_star
)paren
suffix:semicolon
r_int
id|RIORFlushEnable
c_func
(paren
r_int
comma
r_struct
id|CmdBlk
op_star
)paren
suffix:semicolon
r_int
id|RIOUnUse
c_func
(paren
r_int
comma
r_struct
id|CmdBlk
op_star
)paren
suffix:semicolon
r_void
id|ShowPacket
c_func
(paren
id|uint
comma
r_struct
id|PKT
op_star
)paren
suffix:semicolon
multiline_comment|/* rioctrl.c */
r_int
id|copyin
c_func
(paren
r_int
comma
id|caddr_t
comma
r_int
)paren
suffix:semicolon
r_int
id|copyout
c_func
(paren
id|caddr_t
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|riocontrol
c_func
(paren
r_struct
id|rio_info
op_star
comma
id|dev_t
comma
r_int
comma
id|caddr_t
comma
r_int
)paren
suffix:semicolon
r_int
id|RIOPreemptiveCmd
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|Port
op_star
comma
id|uchar
)paren
suffix:semicolon
multiline_comment|/* rioinit.c */
r_void
id|rioinit
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|RioHostInfo
op_star
)paren
suffix:semicolon
r_void
id|RIOInitHosts
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|RioHostInfo
op_star
)paren
suffix:semicolon
r_void
id|RIOISAinit
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|RIODoAT
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
id|caddr_t
id|RIOCheckForATCard
c_func
(paren
r_int
)paren
suffix:semicolon
r_int
id|RIOAssignAT
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_int
comma
id|caddr_t
comma
r_int
)paren
suffix:semicolon
r_int
id|RIOBoardTest
c_func
(paren
id|paddr_t
comma
id|caddr_t
comma
id|uchar
comma
r_int
)paren
suffix:semicolon
r_int
id|RIOScrub
c_func
(paren
r_int
comma
id|BYTE
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|RIOAllocateInterrupts
c_func
(paren
r_struct
id|rio_info
op_star
)paren
suffix:semicolon
r_void
id|RIOStopInterrupts
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_void
id|RIOAllocDataStructs
c_func
(paren
r_struct
id|rio_info
op_star
)paren
suffix:semicolon
r_void
id|RIOSetupDataStructs
c_func
(paren
r_struct
id|rio_info
op_star
)paren
suffix:semicolon
r_int
id|RIODefaultName
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|Host
op_star
comma
id|uint
)paren
suffix:semicolon
r_int
id|RIOReport
c_func
(paren
r_struct
id|rio_info
op_star
)paren
suffix:semicolon
r_struct
id|rioVersion
op_star
id|RIOVersid
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|RIOMapin
c_func
(paren
id|paddr_t
comma
r_int
comma
id|caddr_t
op_star
)paren
suffix:semicolon
r_void
id|RIOMapout
c_func
(paren
id|paddr_t
comma
r_int
comma
id|caddr_t
)paren
suffix:semicolon
r_void
id|RIOHostReset
c_func
(paren
id|uint
comma
r_volatile
r_struct
id|DpRam
op_star
comma
id|uint
)paren
suffix:semicolon
multiline_comment|/* riointr.c */
r_void
id|riopoll
c_func
(paren
r_struct
id|rio_info
op_star
)paren
suffix:semicolon
r_void
id|riointr
c_func
(paren
r_struct
id|rio_info
op_star
)paren
suffix:semicolon
r_void
id|RIOTxEnable
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_void
id|RIOServiceHost
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|Host
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|RIOReceive
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|Port
op_star
)paren
suffix:semicolon
r_int
id|riotproc
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_register
r_struct
id|ttystatics
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* rioparam.c */
r_int
id|RIOParam
c_func
(paren
r_struct
id|Port
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|RIODelay
c_func
(paren
r_struct
id|Port
op_star
id|PortP
comma
r_int
)paren
suffix:semicolon
r_int
id|RIODelay_ni
c_func
(paren
r_struct
id|Port
op_star
id|PortP
comma
r_int
)paren
suffix:semicolon
r_void
id|ms_timeout
c_func
(paren
r_struct
id|Port
op_star
)paren
suffix:semicolon
r_int
id|can_add_transmit
c_func
(paren
r_struct
id|PKT
op_star
op_star
comma
r_struct
id|Port
op_star
)paren
suffix:semicolon
r_void
id|add_transmit
c_func
(paren
r_struct
id|Port
op_star
)paren
suffix:semicolon
r_void
id|put_free_end
c_func
(paren
r_struct
id|Host
op_star
comma
r_struct
id|PKT
op_star
)paren
suffix:semicolon
r_int
id|can_remove_receive
c_func
(paren
r_struct
id|PKT
op_star
op_star
comma
r_struct
id|Port
op_star
)paren
suffix:semicolon
r_void
id|remove_receive
c_func
(paren
r_struct
id|Port
op_star
)paren
suffix:semicolon
multiline_comment|/* rioroute.c */
r_int
id|RIORouteRup
c_func
(paren
r_struct
id|rio_info
op_star
comma
id|uint
comma
r_struct
id|Host
op_star
comma
r_struct
id|PKT
op_star
)paren
suffix:semicolon
r_void
id|RIOFixPhbs
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|Host
op_star
comma
id|uint
)paren
suffix:semicolon
r_int
id|RIOCheckIsolated
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|Host
op_star
comma
id|uint
)paren
suffix:semicolon
r_int
id|RIOIsolate
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|Host
op_star
comma
id|uint
)paren
suffix:semicolon
r_int
id|RIOCheck
c_func
(paren
r_struct
id|Host
op_star
comma
id|uint
)paren
suffix:semicolon
id|uint
id|GetUnitType
c_func
(paren
id|uint
)paren
suffix:semicolon
r_int
id|RIOSetChange
c_func
(paren
r_struct
id|rio_info
op_star
)paren
suffix:semicolon
r_void
id|RIOConCon
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|Host
op_star
comma
id|uint
comma
id|uint
comma
id|uint
comma
id|uint
comma
r_int
)paren
suffix:semicolon
r_int
id|RIOFindFreeID
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|Host
op_star
comma
id|uint
op_star
comma
id|uint
op_star
)paren
suffix:semicolon
r_int
id|RIOFreeDisconnected
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|Host
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|RIORemoveFromSavedTable
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|Map
op_star
)paren
suffix:semicolon
multiline_comment|/* riotty.c */
r_int
id|riotopen
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_int
id|riotclose
c_func
(paren
r_void
op_star
id|ptr
)paren
suffix:semicolon
r_int
id|RIOCookMode
c_func
(paren
r_struct
id|ttystatics
op_star
)paren
suffix:semicolon
r_int
id|riotioctl
c_func
(paren
r_struct
id|rio_info
op_star
comma
id|dev_t
comma
r_register
r_int
comma
r_register
id|caddr_t
)paren
suffix:semicolon
r_void
id|ttyseth
c_func
(paren
r_struct
id|Port
op_star
comma
r_struct
id|ttystatics
op_star
comma
r_struct
id|old_sgttyb
op_star
id|sg
)paren
suffix:semicolon
multiline_comment|/* riotable.c */
r_int
id|RIONewTable
c_func
(paren
r_struct
id|rio_info
op_star
)paren
suffix:semicolon
r_int
id|RIOApel
c_func
(paren
r_struct
id|rio_info
op_star
)paren
suffix:semicolon
r_int
id|RIODeleteRta
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|Map
op_star
)paren
suffix:semicolon
r_int
id|RIOAssignRta
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|Map
op_star
)paren
suffix:semicolon
r_int
id|RIOReMapPorts
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|Host
op_star
comma
r_struct
id|Map
op_star
)paren
suffix:semicolon
r_int
id|RIOChangeName
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|Map
op_star
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/* riodrvr.c */
r_struct
id|rio_info
op_star
id|rio_install
c_func
(paren
r_struct
id|RioHostInfo
op_star
)paren
suffix:semicolon
r_int
id|rio_uninstall
c_func
(paren
r_register
r_struct
id|rio_info
op_star
)paren
suffix:semicolon
r_int
id|rio_open
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_int
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_int
id|rio_close
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_int
id|rio_read
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|rio_write
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|file
op_star
id|f
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|rio_ioctl
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|file
op_star
comma
r_int
comma
r_char
op_star
)paren
suffix:semicolon
r_int
id|rio_select
c_func
(paren
r_struct
id|rio_info
op_star
comma
r_struct
id|file
op_star
id|f
comma
r_int
comma
r_struct
id|sel
op_star
)paren
suffix:semicolon
r_int
id|rio_intr
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_int
id|rio_isr_thread
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_struct
id|rio_info
op_star
id|rio_info_store
c_func
(paren
r_int
id|cmd
comma
r_struct
id|rio_info
op_star
id|p
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|rio_pcicopy
c_func
(paren
r_char
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|n
)paren
suffix:semicolon
r_extern
r_int
id|rio_minor
(paren
id|kdev_t
id|device
)paren
suffix:semicolon
r_extern
r_int
id|rio_ismodem
(paren
id|kdev_t
id|device
)paren
suffix:semicolon
r_extern
r_void
id|rio_udelay
(paren
r_int
id|usecs
)paren
suffix:semicolon
r_extern
r_void
id|rio_start_card_running
(paren
r_struct
id|Host
op_star
id|HostP
)paren
suffix:semicolon
macro_line|#endif&t;/* __func_h_def */
eof
