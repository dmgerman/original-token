multiline_comment|/* $Id: isdn_tty.h,v 1.19 2000/02/16 14:59:33 paul Exp $&n;&n; * header for Linux ISDN subsystem, tty related functions (linklevel).&n; *&n; * Copyright 1994-1999  by Fritz Elfert (fritz@isdn4linux.de)&n; * Copyright 1995,96    by Thinking Objects Software GmbH Wuerzburg&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * $Log: isdn_tty.h,v $&n; * Revision 1.19  2000/02/16 14:59:33  paul&n; * translated ISDN_MODEM_ANZREG to ISDN_MODEM_NUMREG for english speakers;&n; * used defines for result codes;&n; * fixed RING ... RUNG problem (no empty lines in between).&n; *&n; * Revision 1.18  2000/01/20 19:55:33  keil&n; * Add FAX Class 1 support&n; *&n; * Revision 1.17  1999/09/21 19:00:35  armin&n; * Extended FCON message with added CPN&n; * can now be activated with Bit 1 of Reg 23.&n; *&n; * Revision 1.16  1999/08/22 20:26:10  calle&n; * backported changes from kernel 2.3.14:&n; * - several #include &quot;config.h&quot; gone, others come.&n; * - &quot;struct device&quot; changed to &quot;struct net_device&quot; in 2.3.14, added a&n; *   define in isdn_compat.h for older kernel versions.&n; *&n; * Revision 1.15  1999/07/31 12:59:48  armin&n; * Added tty fax capabilities.&n; *&n; * Revision 1.14  1999/07/11 17:14:15  armin&n; * Added new layer 2 and 3 protocols for Fax and DSP functions.&n; * Moved &quot;Add CPN to RING message&quot; to new register S23,&n; * &quot;Display message&quot; is now correct on register S13 bit 7.&n; * New audio command AT+VDD implemented (deactivate DTMF decoder and&n; * activate possible existing hardware/DSP decoder).&n; * Moved some tty defines to .h file.&n; * Made whitespace possible in AT command line.&n; * Some AT-emulator output bugfixes.&n; * First Fax G3 implementations.&n; *&n; * Revision 1.13  1999/04/12 12:33:46  fritz&n; * Changes from 2.0 tree.&n; *&n; * Revision 1.12  1999/03/02 12:04:51  armin&n; * -added ISDN_STAT_ADDCH to increase supported channels after&n; *  register_isdn().&n; * -ttyI now goes on-hook on ATZ when B-Ch is connected.&n; * -added timer-function for register S7 (Wait for Carrier).&n; * -analog modem (ISDN_PROTO_L2_MODEM) implementations.&n; * -on L2_MODEM a string will be appended to the CONNECT-Message,&n; *  which is provided by the HL-Driver in parm.num in ISDN_STAT_BCONN.&n; * -variable &quot;dialing&quot; used for ATA also, for interrupting call&n; *  establishment and register S7.&n; *&n; * Revision 1.11  1998/03/19 13:18:27  keil&n; * Start of a CAPI like interface for supplementary Service&n; * first service: SUSPEND&n; *&n; * Revision 1.10  1997/03/02 14:29:26  fritz&n; * More ttyI related cleanup.&n; *&n; * Revision 1.9  1997/02/28 02:32:49  fritz&n; * Cleanup: Moved some tty related stuff from isdn_common.c&n; *          to isdn_tty.c&n; * Bugfix:  Bisync protocol did not behave like documented.&n; *&n; * Revision 1.8  1997/02/10 20:12:50  fritz&n; * Changed interface for reporting incoming calls.&n; *&n; * Revision 1.7  1997/02/03 23:06:10  fritz&n; * Reformatted according CodingStyle&n; *&n; * Revision 1.6  1997/01/14 01:35:19  fritz&n; * Changed prototype of isdn_tty_modem_hup.&n; *&n; * Revision 1.5  1996/05/17 03:52:31  fritz&n; * Changed DLE handling for audio receive.&n; *&n; * Revision 1.4  1996/05/11 21:52:34  fritz&n; * Changed queue management to use sk_buffs.&n; *&n; * Revision 1.3  1996/05/07 09:16:34  fritz&n; * Changed isdn_try_read parameter.&n; *&n; * Revision 1.2  1996/04/30 21:05:27  fritz&n; * Test commit&n; *&n; * Revision 1.1  1996/01/10 21:39:22  fritz&n; * Initial revision&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|DLE
mdefine_line|#define DLE 0x10
DECL|macro|ETX
mdefine_line|#define ETX 0x03
DECL|macro|DC4
mdefine_line|#define DC4 0x14
multiline_comment|/*&n; * Definition of some special Registers of AT-Emulator&n; */
DECL|macro|REG_RINGATA
mdefine_line|#define REG_RINGATA   0
DECL|macro|REG_RINGCNT
mdefine_line|#define REG_RINGCNT   1  /* ring counter register */
DECL|macro|REG_ESC
mdefine_line|#define REG_ESC       2
DECL|macro|REG_CR
mdefine_line|#define REG_CR        3
DECL|macro|REG_LF
mdefine_line|#define REG_LF        4
DECL|macro|REG_BS
mdefine_line|#define REG_BS        5
DECL|macro|REG_WAITC
mdefine_line|#define REG_WAITC     7
DECL|macro|REG_RESP
mdefine_line|#define REG_RESP     12  /* show response messages register */
DECL|macro|BIT_RESP
mdefine_line|#define BIT_RESP      1  /* show response messages bit      */
DECL|macro|REG_RESPNUM
mdefine_line|#define REG_RESPNUM  12  /* show numeric responses register */
DECL|macro|BIT_RESPNUM
mdefine_line|#define BIT_RESPNUM   2  /* show numeric responses bit      */
DECL|macro|REG_ECHO
mdefine_line|#define REG_ECHO     12
DECL|macro|BIT_ECHO
mdefine_line|#define BIT_ECHO      4
DECL|macro|REG_DCD
mdefine_line|#define REG_DCD      12
DECL|macro|BIT_DCD
mdefine_line|#define BIT_DCD       8
DECL|macro|REG_CTS
mdefine_line|#define REG_CTS      12
DECL|macro|BIT_CTS
mdefine_line|#define BIT_CTS      16
DECL|macro|REG_DTRR
mdefine_line|#define REG_DTRR     12
DECL|macro|BIT_DTRR
mdefine_line|#define BIT_DTRR     32
DECL|macro|REG_DSR
mdefine_line|#define REG_DSR      12
DECL|macro|BIT_DSR
mdefine_line|#define BIT_DSR      64
DECL|macro|REG_CPPP
mdefine_line|#define REG_CPPP     12
DECL|macro|BIT_CPPP
mdefine_line|#define BIT_CPPP    128
DECL|macro|REG_T70
mdefine_line|#define REG_T70      13
DECL|macro|BIT_T70
mdefine_line|#define BIT_T70       2
DECL|macro|BIT_T70_EXT
mdefine_line|#define BIT_T70_EXT  32
DECL|macro|REG_DTRHUP
mdefine_line|#define REG_DTRHUP   13
DECL|macro|BIT_DTRHUP
mdefine_line|#define BIT_DTRHUP    4
DECL|macro|REG_RESPXT
mdefine_line|#define REG_RESPXT   13
DECL|macro|BIT_RESPXT
mdefine_line|#define BIT_RESPXT    8
DECL|macro|REG_CIDONCE
mdefine_line|#define REG_CIDONCE  13
DECL|macro|BIT_CIDONCE
mdefine_line|#define BIT_CIDONCE  16
DECL|macro|REG_RUNG
mdefine_line|#define REG_RUNG     13  /* show RUNG message register      */
DECL|macro|BIT_RUNG
mdefine_line|#define BIT_RUNG     64  /* show RUNG message bit           */
DECL|macro|REG_DISPLAY
mdefine_line|#define REG_DISPLAY  13
DECL|macro|BIT_DISPLAY
mdefine_line|#define BIT_DISPLAY 128
DECL|macro|REG_L2PROT
mdefine_line|#define REG_L2PROT   14
DECL|macro|REG_L3PROT
mdefine_line|#define REG_L3PROT   15
DECL|macro|REG_PSIZE
mdefine_line|#define REG_PSIZE    16
DECL|macro|REG_WSIZE
mdefine_line|#define REG_WSIZE    17
DECL|macro|REG_SI1
mdefine_line|#define REG_SI1      18
DECL|macro|REG_SI2
mdefine_line|#define REG_SI2      19
DECL|macro|REG_SI1I
mdefine_line|#define REG_SI1I     20
DECL|macro|REG_PLAN
mdefine_line|#define REG_PLAN     21
DECL|macro|REG_SCREEN
mdefine_line|#define REG_SCREEN   22
DECL|macro|REG_CPN
mdefine_line|#define REG_CPN      23
DECL|macro|BIT_CPN
mdefine_line|#define BIT_CPN       1
DECL|macro|BIT_CPNFCON
mdefine_line|#define BIT_CPNFCON   2
multiline_comment|/* defines for result codes */
DECL|macro|RESULT_OK
mdefine_line|#define RESULT_OK&t;&t;0
DECL|macro|RESULT_CONNECT
mdefine_line|#define RESULT_CONNECT&t;&t;1
DECL|macro|RESULT_RING
mdefine_line|#define RESULT_RING&t;&t;2
DECL|macro|RESULT_NO_CARRIER
mdefine_line|#define RESULT_NO_CARRIER&t;3
DECL|macro|RESULT_ERROR
mdefine_line|#define RESULT_ERROR&t;&t;4
DECL|macro|RESULT_CONNECT64000
mdefine_line|#define RESULT_CONNECT64000&t;5
DECL|macro|RESULT_NO_DIALTONE
mdefine_line|#define RESULT_NO_DIALTONE&t;6
DECL|macro|RESULT_BUSY
mdefine_line|#define RESULT_BUSY&t;&t;7
DECL|macro|RESULT_NO_ANSWER
mdefine_line|#define RESULT_NO_ANSWER&t;8
DECL|macro|RESULT_RINGING
mdefine_line|#define RESULT_RINGING&t;&t;9
DECL|macro|RESULT_NO_MSN_EAZ
mdefine_line|#define RESULT_NO_MSN_EAZ&t;10
DECL|macro|RESULT_VCON
mdefine_line|#define RESULT_VCON&t;&t;11
DECL|macro|RESULT_RUNG
mdefine_line|#define RESULT_RUNG&t;&t;12
DECL|macro|TTY_IS_FCLASS1
mdefine_line|#define TTY_IS_FCLASS1(info) &bslash;&n;&t;((info-&gt;emu.mdmreg[REG_L2PROT] == ISDN_PROTO_L2_FAX) &amp;&amp; &bslash;&n;&t; (info-&gt;emu.mdmreg[REG_L3PROT] == ISDN_PROTO_L3_FCLASS1))
DECL|macro|TTY_IS_FCLASS2
mdefine_line|#define TTY_IS_FCLASS2(info) &bslash;&n;&t;((info-&gt;emu.mdmreg[REG_L2PROT] == ISDN_PROTO_L2_FAX) &amp;&amp; &bslash;&n;&t; (info-&gt;emu.mdmreg[REG_L3PROT] == ISDN_PROTO_L3_FCLASS2))
r_extern
r_void
id|isdn_tty_modem_escape
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|isdn_tty_modem_ring
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|isdn_tty_carrier_timeout
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|isdn_tty_modem_xmit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|isdn_tty_modem_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|isdn_tty_readmodem
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|isdn_tty_find_icall
c_func
(paren
r_int
comma
r_int
comma
id|setup_parm
)paren
suffix:semicolon
r_extern
r_void
id|isdn_tty_cleanup_xmit
c_func
(paren
id|modem_info
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_tty_stat_callback
c_func
(paren
r_int
comma
id|isdn_ctrl
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_tty_rcv_skb
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
id|isdn_tty_capi_facility
c_func
(paren
id|capi_msg
op_star
id|cm
)paren
suffix:semicolon
r_extern
r_void
id|isdn_tty_at_cout
c_func
(paren
r_char
op_star
comma
id|modem_info
op_star
)paren
suffix:semicolon
r_extern
r_void
id|isdn_tty_modem_hup
c_func
(paren
id|modem_info
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ISDN_TTY_FAX
r_extern
r_int
id|isdn_tty_cmd_PLUSF_FAX
c_func
(paren
r_char
op_star
op_star
comma
id|modem_info
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_tty_fax_command
c_func
(paren
id|modem_info
op_star
comma
id|isdn_ctrl
op_star
)paren
suffix:semicolon
r_extern
r_void
id|isdn_tty_fax_bitorder
c_func
(paren
id|modem_info
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
