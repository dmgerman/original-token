multiline_comment|/* $Id: isdn_common.h,v 1.17 1999/10/27 21:21:17 detabc Exp $&n;&n; * header for Linux ISDN subsystem, common used functions and debugging-switches (linklevel).&n; *&n; * Copyright 1994-1999  by Fritz Elfert (fritz@isdn4linux.de)&n; * Copyright 1995,96    by Thinking Objects Software GmbH Wuerzburg&n; * Copyright 1995,96    by Michael Hipp (Michael.Hipp@student.uni-tuebingen.de)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * $Log: isdn_common.h,v $&n; * Revision 1.17  1999/10/27 21:21:17  detabc&n; * Added support for building logically-bind-group&squot;s per interface.&n; * usefull for outgoing call&squot;s with more then one isdn-card.&n; *&n; * Switchable support to dont reset the hangup-timeout for&n; * receive frames. Most part&squot;s of the timru-rules for receiving frames&n; * are now obsolete. If the input- or forwarding-firewall deny&n; * the frame, the line will be not hold open.&n; *&n; * Revision 1.16  1999/07/01 08:29:54  keil&n; * compatibility to 2.3 kernel&n; *&n; * Revision 1.15  1999/04/18 14:06:50  fritz&n; * Removed TIMRU stuff.&n; *&n; * Revision 1.14  1999/04/12 12:33:18  fritz&n; * Changes from 2.0 tree.&n; *&n; * Revision 1.13  1999/03/02 12:04:47  armin&n; * -added ISDN_STAT_ADDCH to increase supported channels after&n; *  register_isdn().&n; * -ttyI now goes on-hook on ATZ when B-Ch is connected.&n; * -added timer-function for register S7 (Wait for Carrier).&n; * -analog modem (ISDN_PROTO_L2_MODEM) implementations.&n; * -on L2_MODEM a string will be appended to the CONNECT-Message,&n; *  which is provided by the HL-Driver in parm.num in ISDN_STAT_BCONN.&n; * -variable &quot;dialing&quot; used for ATA also, for interrupting call&n; *  establishment and register S7.&n; *&n; * Revision 1.12  1998/06/26 15:12:27  fritz&n; * Added handling of STAT_ICALL with incomplete CPN.&n; * Added AT&amp;L for ttyI emulator.&n; * Added more locking stuff in tty_write.&n; *&n; * Revision 1.11  1998/04/14 16:28:47  he&n; * Fixed user space access with interrupts off and remaining&n; * copy_{to,from}_user() -&gt; -EFAULT return codes&n; *&n; * Revision 1.10  1998/03/07 18:21:03  cal&n; * Dynamic Timeout-Rule-Handling vs. 971110 included&n; *&n; * Revision 1.9  1998/02/20 17:19:01  fritz&n; * Added common stub for sending commands to lowlevel.&n; *&n; * Revision 1.8  1997/10/09 21:28:49  fritz&n; * New HL&lt;-&gt;LL interface:&n; *   New BSENT callback with nr. of bytes included.&n; *   Sending without ACK.&n; *   New L1 error status (not yet in use).&n; *   Cleaned up obsolete structures.&n; * Implemented Cisco-SLARP.&n; * Changed local net-interface data to be dynamically allocated.&n; * Removed old 2.0 compatibility stuff.&n; *&n; * Revision 1.7  1997/10/01 09:20:30  fritz&n; * Removed old compatibility stuff for 2.0.X kernels.&n; * From now on, this code is for 2.1.X ONLY!&n; * Old stuff is still in the separate branch.&n; *&n; * Revision 1.6  1997/02/28 02:32:44  fritz&n; * Cleanup: Moved some tty related stuff from isdn_common.c&n; *          to isdn_tty.c&n; * Bugfix:  Bisync protocol did not behave like documented.&n; *&n; * Revision 1.5  1997/02/10 10:05:45  fritz&n; * More changes for Kernel 2.1.X&n; * Symbol information moved to isdn_syms.c&n; *&n; * Revision 1.4  1997/02/03 22:56:50  fritz&n; * Removed isdn_writebuf_stub prototype.&n; *&n; * Revision 1.3  1996/05/19 00:13:05  fritz&n; * Removed debug flag.&n; *&n; * Revision 1.2  1996/04/20 16:20:40  fritz&n; * Misc. typos.&n; *&n; * Revision 1.1  1996/01/10 21:37:19  fritz&n; * Initial revision&n; *&n; */
DECL|macro|ISDN_DEBUG_MODEM_OPEN
macro_line|#undef  ISDN_DEBUG_MODEM_OPEN
DECL|macro|ISDN_DEBUG_MODEM_IOCTL
macro_line|#undef  ISDN_DEBUG_MODEM_IOCTL
DECL|macro|ISDN_DEBUG_MODEM_WAITSENT
macro_line|#undef  ISDN_DEBUG_MODEM_WAITSENT
DECL|macro|ISDN_DEBUG_MODEM_HUP
macro_line|#undef  ISDN_DEBUG_MODEM_HUP
DECL|macro|ISDN_DEBUG_MODEM_ICALL
macro_line|#undef  ISDN_DEBUG_MODEM_ICALL
DECL|macro|ISDN_DEBUG_MODEM_DUMP
macro_line|#undef  ISDN_DEBUG_MODEM_DUMP
DECL|macro|ISDN_DEBUG_MODEM_VOICE
macro_line|#undef  ISDN_DEBUG_MODEM_VOICE
DECL|macro|ISDN_DEBUG_AT
macro_line|#undef  ISDN_DEBUG_AT
DECL|macro|ISDN_DEBUG_NET_DUMP
macro_line|#undef  ISDN_DEBUG_NET_DUMP
DECL|macro|ISDN_DEBUG_NET_DIAL
macro_line|#undef  ISDN_DEBUG_NET_DIAL
DECL|macro|ISDN_DEBUG_NET_ICALL
macro_line|#undef  ISDN_DEBUG_NET_ICALL
multiline_comment|/* Prototypes */
r_extern
r_void
id|isdn_MOD_INC_USE_COUNT
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|isdn_MOD_DEC_USE_COUNT
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|isdn_free_channel
c_func
(paren
r_int
id|di
comma
r_int
id|ch
comma
r_int
id|usage
)paren
suffix:semicolon
r_extern
r_void
id|isdn_all_eaz
c_func
(paren
r_int
id|di
comma
r_int
id|ch
)paren
suffix:semicolon
r_extern
r_int
id|isdn_command
c_func
(paren
id|isdn_ctrl
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_dc2minor
c_func
(paren
r_int
id|di
comma
r_int
id|ch
)paren
suffix:semicolon
r_extern
r_void
id|isdn_info_update
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_char
op_star
id|isdn_map_eaz2msn
c_func
(paren
r_char
op_star
id|msn
comma
r_int
id|di
)paren
suffix:semicolon
r_extern
r_void
id|isdn_timer_ctrl
c_func
(paren
r_int
id|tf
comma
r_int
id|onoff
)paren
suffix:semicolon
r_extern
r_void
id|isdn_unexclusive_channel
c_func
(paren
r_int
id|di
comma
r_int
id|ch
)paren
suffix:semicolon
r_extern
r_int
id|isdn_getnum
c_func
(paren
r_char
op_star
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_readbchan
c_func
(paren
r_int
comma
r_int
comma
id|u_char
op_star
comma
id|u_char
op_star
comma
r_int
comma
id|wait_queue_head_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_get_free_channel
c_func
(paren
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|isdn_writebuf_skb_stub
c_func
(paren
r_int
comma
r_int
comma
r_int
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_int
id|register_isdn
c_func
(paren
id|isdn_if
op_star
id|i
)paren
suffix:semicolon
r_extern
r_int
id|isdn_wildmat
c_func
(paren
r_char
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_add_channels
c_func
(paren
id|driver
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#if defined(ISDN_DEBUG_NET_DUMP) || defined(ISDN_DEBUG_MODEM_DUMP)
r_extern
r_void
id|isdn_dumppkt
c_func
(paren
r_char
op_star
comma
id|u_char
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
eof
