multiline_comment|/* X25 changes:&n;   Added constants ISDN_PROTO_L2_X25DTE/DCE and corresponding ISDN_FEATURE_..&n;   */
multiline_comment|/* $Id: isdnif.h,v 1.23 1998/02/20 17:36:52 fritz Exp $&n; *&n; * Linux ISDN subsystem&n; *&n; * Definition of the interface between the subsystem and its low-level drivers.&n; *&n; * Copyright 1994,95,96 by Fritz Elfert (fritz@wuemaus.franken.de)&n; * Copyright 1995,96    Thinking Objects Software GmbH Wuerzburg&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n; *&n; * $Log: isdnif.h,v $&n; * Revision 1.23  1998/02/20 17:36:52  fritz&n; * Added L2-protocols for V.110, changed FEATURE-Flag-constants.&n; *&n; * Revision 1.22  1998/01/31 22:14:12  keil&n; * changes for 2.1.82&n; *&n; * Revision 1.21  1997/10/09 21:28:13  fritz&n; * New HL&lt;-&gt;LL interface:&n; *   New BSENT callback with nr. of bytes included.&n; *   Sending without ACK.&n; *   New L1 error status (not yet in use).&n; *   Cleaned up obsolete structures.&n; * Implemented Cisco-SLARP.&n; * Changed local net-interface data to be dynamically allocated.&n; * Removed old 2.0 compatibility stuff.&n; *&n; * Revision 1.20  1997/05/27 15:18:06  fritz&n; * Added changes for recent 2.1.x kernels:&n; *   changed return type of isdn_close&n; *   queue_task_* -&gt; queue_task&n; *   clear/set_bit -&gt; test_and_... where apropriate.&n; *   changed type of hard_header_cache parameter.&n; *&n; * Revision 1.19  1997/03/25 23:13:56  keil&n; * NI-1 US protocol&n; *&n; * Revision 1.18  1997/03/04 22:09:18  calle&n; * Change macros copy_from_user and copy_to_user in inline function.&n; * These are now correct replacements of the functions for 2.1.xx&n; *&n; * Revision 1.17  1997/02/10 21:12:53  fritz&n; * More setup-interface changes.&n; *&n; * Revision 1.16  1997/02/10 19:42:57  fritz&n; * New interface for reporting incoming calls.&n; *&n; * Revision 1.15  1997/02/09 00:18:42  keil&n; * leased line support&n; *&n; * Revision 1.14  1997/02/03 23:43:00  fritz&n; * Misc changes for Kernel 2.1.X compatibility.&n; *&n; * Revision 1.13  1996/11/13 02:39:59  fritz&n; * More compatibility changes.&n; *&n; * Revision 1.12  1996/11/06 17:38:48  keil&n; * more changes for 2.1.X&n; *&n; * Revision 1.11  1996/10/23 11:59:42  fritz&n; * More compatibility changes.&n; *&n; * Revision 1.10  1996/10/22 23:14:19  fritz&n; * Changes for compatibility to 2.0.X and 2.1.X kernels.&n; *&n; * Revision 1.9  1996/06/06 21:24:24  fritz&n; * Started adding support for suspend/resume.&n; *&n; * Revision 1.8  1996/05/18 01:45:37  fritz&n; * More spelling corrections.&n; *&n; * Revision 1.7  1996/05/18 01:37:19  fritz&n; * Added spelling corrections and some minor changes&n; * to stay in sync with kernel.&n; *&n; * Revision 1.6  1996/05/17 03:59:28  fritz&n; * Marked rcvcallb and writebuf obsolete.&n; *&n; * Revision 1.5  1996/05/01 11:43:54  fritz&n; * Removed STANDALONE&n; *&n; * Revision 1.4  1996/05/01 11:38:40  fritz&n; * Added ISDN_FEATURE_L2_TRANS&n; *&n; * Revision 1.3  1996/04/29 22:57:54  fritz&n; * Added driverId and channel parameters to&n; * writecmd() and readstat().&n; * Added constant for voice-support.&n; *&n; * Revision 1.2  1996/04/20 17:02:40  fritz&n; * Changes to support skbuffs for Lowlevel-Drivers.&n; * Misc. typos&n; *&n; * Revision 1.1  1996/01/09 05:50:51  fritz&n; * Initial revision&n; *&n; */
macro_line|#ifndef isdnif_h
DECL|macro|isdnif_h
mdefine_line|#define isdnif_h
multiline_comment|/*&n; * Values for general protocol-selection&n; */
DECL|macro|ISDN_PTYPE_UNKNOWN
mdefine_line|#define ISDN_PTYPE_UNKNOWN   0   /* Protocol undefined   */
DECL|macro|ISDN_PTYPE_1TR6
mdefine_line|#define ISDN_PTYPE_1TR6      1   /* german 1TR6-protocol */
DECL|macro|ISDN_PTYPE_EURO
mdefine_line|#define ISDN_PTYPE_EURO      2   /* EDSS1-protocol       */
DECL|macro|ISDN_PTYPE_LEASED
mdefine_line|#define ISDN_PTYPE_LEASED    3   /* for leased lines     */
DECL|macro|ISDN_PTYPE_NI1
mdefine_line|#define ISDN_PTYPE_NI1       4   /* US NI-1 protocol     */
DECL|macro|ISDN_PTYPE_MAX
mdefine_line|#define ISDN_PTYPE_MAX       7   /* Max. 8 Protocols     */
multiline_comment|/*&n; * Values for Layer-2-protocol-selection&n; */
DECL|macro|ISDN_PROTO_L2_X75I
mdefine_line|#define ISDN_PROTO_L2_X75I   0   /* X75/LAPB with I-Frames            */
DECL|macro|ISDN_PROTO_L2_X75UI
mdefine_line|#define ISDN_PROTO_L2_X75UI  1   /* X75/LAPB with UI-Frames           */
DECL|macro|ISDN_PROTO_L2_X75BUI
mdefine_line|#define ISDN_PROTO_L2_X75BUI 2   /* X75/LAPB with UI-Frames           */
DECL|macro|ISDN_PROTO_L2_HDLC
mdefine_line|#define ISDN_PROTO_L2_HDLC   3   /* HDLC                              */
DECL|macro|ISDN_PROTO_L2_TRANS
mdefine_line|#define ISDN_PROTO_L2_TRANS  4   /* Transparent (Voice)               */
DECL|macro|ISDN_PROTO_L2_X25DTE
mdefine_line|#define ISDN_PROTO_L2_X25DTE 5   /* X25/LAPB DTE mode                 */
DECL|macro|ISDN_PROTO_L2_X25DCE
mdefine_line|#define ISDN_PROTO_L2_X25DCE 6   /* X25/LAPB DCE mode                 */
DECL|macro|ISDN_PROTO_L2_V11096
mdefine_line|#define ISDN_PROTO_L2_V11096 7   /* V.110 bitrate adaption 9600 Baud  */
DECL|macro|ISDN_PROTO_L2_V11019
mdefine_line|#define ISDN_PROTO_L2_V11019 8   /* V.110 bitrate adaption 19200 Baud */
DECL|macro|ISDN_PROTO_L2_V11038
mdefine_line|#define ISDN_PROTO_L2_V11038 9   /* V.110 bitrate adaption 38400 Baud */
DECL|macro|ISDN_PROTO_L2_MAX
mdefine_line|#define ISDN_PROTO_L2_MAX    15  /* Max. 16 Protocols                 */
multiline_comment|/*&n; * Values for Layer-3-protocol-selection&n; */
DECL|macro|ISDN_PROTO_L3_TRANS
mdefine_line|#define ISDN_PROTO_L3_TRANS  0   /* Transparent                 */
DECL|macro|ISDN_PROTO_L3_MAX
mdefine_line|#define ISDN_PROTO_L3_MAX    7   /* Max. 8 Protocols            */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/skbuff.h&gt;
multiline_comment|/*&n; * Commands from linklevel to lowlevel&n; *&n; */
DECL|macro|ISDN_CMD_IOCTL
mdefine_line|#define ISDN_CMD_IOCTL    0       /* Perform ioctl                         */
DECL|macro|ISDN_CMD_DIAL
mdefine_line|#define ISDN_CMD_DIAL     1       /* Dial out                              */
DECL|macro|ISDN_CMD_ACCEPTD
mdefine_line|#define ISDN_CMD_ACCEPTD  2       /* Accept an incoming call on D-Chan.    */
DECL|macro|ISDN_CMD_ACCEPTB
mdefine_line|#define ISDN_CMD_ACCEPTB  3       /* Request B-Channel connect.            */
DECL|macro|ISDN_CMD_HANGUP
mdefine_line|#define ISDN_CMD_HANGUP   4       /* Hangup                                */
DECL|macro|ISDN_CMD_CLREAZ
mdefine_line|#define ISDN_CMD_CLREAZ   5       /* Clear EAZ(s) of channel               */
DECL|macro|ISDN_CMD_SETEAZ
mdefine_line|#define ISDN_CMD_SETEAZ   6       /* Set EAZ(s) of channel                 */
DECL|macro|ISDN_CMD_GETEAZ
mdefine_line|#define ISDN_CMD_GETEAZ   7       /* Get EAZ(s) of channel                 */
DECL|macro|ISDN_CMD_SETSIL
mdefine_line|#define ISDN_CMD_SETSIL   8       /* Set Service-Indicator-List of channel */
DECL|macro|ISDN_CMD_GETSIL
mdefine_line|#define ISDN_CMD_GETSIL   9       /* Get Service-Indicator-List of channel */
DECL|macro|ISDN_CMD_SETL2
mdefine_line|#define ISDN_CMD_SETL2   10       /* Set B-Chan. Layer2-Parameter          */
DECL|macro|ISDN_CMD_GETL2
mdefine_line|#define ISDN_CMD_GETL2   11       /* Get B-Chan. Layer2-Parameter          */
DECL|macro|ISDN_CMD_SETL3
mdefine_line|#define ISDN_CMD_SETL3   12       /* Set B-Chan. Layer3-Parameter          */
DECL|macro|ISDN_CMD_GETL3
mdefine_line|#define ISDN_CMD_GETL3   13       /* Get B-Chan. Layer3-Parameter          */
DECL|macro|ISDN_CMD_LOCK
mdefine_line|#define ISDN_CMD_LOCK    14       /* Signal usage by upper levels          */
DECL|macro|ISDN_CMD_UNLOCK
mdefine_line|#define ISDN_CMD_UNLOCK  15       /* Release usage-lock                    */
DECL|macro|ISDN_CMD_SUSPEND
mdefine_line|#define ISDN_CMD_SUSPEND 16       /* Suspend connection                    */
DECL|macro|ISDN_CMD_RESUME
mdefine_line|#define ISDN_CMD_RESUME  17       /* Resume connection                     */
multiline_comment|/*&n; * Status-Values delivered from lowlevel to linklevel via&n; * statcallb().&n; *&n; */
DECL|macro|ISDN_STAT_STAVAIL
mdefine_line|#define ISDN_STAT_STAVAIL 256    /* Raw status-data available             */
DECL|macro|ISDN_STAT_ICALL
mdefine_line|#define ISDN_STAT_ICALL   257    /* Incoming call detected                */
DECL|macro|ISDN_STAT_RUN
mdefine_line|#define ISDN_STAT_RUN     258    /* Signal protocol-code is running       */
DECL|macro|ISDN_STAT_STOP
mdefine_line|#define ISDN_STAT_STOP    259    /* Signal halt of protocol-code          */
DECL|macro|ISDN_STAT_DCONN
mdefine_line|#define ISDN_STAT_DCONN   260    /* Signal D-Channel connect              */
DECL|macro|ISDN_STAT_BCONN
mdefine_line|#define ISDN_STAT_BCONN   261    /* Signal B-Channel connect              */
DECL|macro|ISDN_STAT_DHUP
mdefine_line|#define ISDN_STAT_DHUP    262    /* Signal D-Channel disconnect           */
DECL|macro|ISDN_STAT_BHUP
mdefine_line|#define ISDN_STAT_BHUP    263    /* Signal B-Channel disconnect           */
DECL|macro|ISDN_STAT_CINF
mdefine_line|#define ISDN_STAT_CINF    264    /* Charge-Info                           */
DECL|macro|ISDN_STAT_LOAD
mdefine_line|#define ISDN_STAT_LOAD    265    /* Signal new lowlevel-driver is loaded  */
DECL|macro|ISDN_STAT_UNLOAD
mdefine_line|#define ISDN_STAT_UNLOAD  266    /* Signal unload of lowlevel-driver      */
DECL|macro|ISDN_STAT_BSENT
mdefine_line|#define ISDN_STAT_BSENT   267    /* Signal packet sent                    */
DECL|macro|ISDN_STAT_NODCH
mdefine_line|#define ISDN_STAT_NODCH   268    /* Signal no D-Channel                   */
DECL|macro|ISDN_STAT_ADDCH
mdefine_line|#define ISDN_STAT_ADDCH   269    /* Add more Channels                     */
DECL|macro|ISDN_STAT_CAUSE
mdefine_line|#define ISDN_STAT_CAUSE   270    /* Cause-Message                         */
DECL|macro|ISDN_STAT_L1ERR
mdefine_line|#define ISDN_STAT_L1ERR   271    /* Signal Layer-1 Error                  */
multiline_comment|/*&n; * Values for errcode field&n; */
DECL|macro|ISDN_STAT_L1ERR_SEND
mdefine_line|#define ISDN_STAT_L1ERR_SEND 1
DECL|macro|ISDN_STAT_L1ERR_RECV
mdefine_line|#define ISDN_STAT_L1ERR_RECV 2
multiline_comment|/*&n; * Values for feature-field of interface-struct.&n; */
multiline_comment|/* Layer 2 */
DECL|macro|ISDN_FEATURE_L2_X75I
mdefine_line|#define ISDN_FEATURE_L2_X75I    (0x0001 &lt;&lt; ISDN_PROTO_L2_X75I)
DECL|macro|ISDN_FEATURE_L2_X75UI
mdefine_line|#define ISDN_FEATURE_L2_X75UI   (0x0001 &lt;&lt; ISDN_PROTO_L2_X75UI)
DECL|macro|ISDN_FEATURE_L2_X75BUI
mdefine_line|#define ISDN_FEATURE_L2_X75BUI  (0x0001 &lt;&lt; ISDN_PROTO_L2_X75BUI)
DECL|macro|ISDN_FEATURE_L2_HDLC
mdefine_line|#define ISDN_FEATURE_L2_HDLC    (0x0001 &lt;&lt; ISDN_PROTO_L2_HDLC)
DECL|macro|ISDN_FEATURE_L2_TRANS
mdefine_line|#define ISDN_FEATURE_L2_TRANS   (0x0001 &lt;&lt; ISDN_PROTO_L2_TRANS)
DECL|macro|ISDN_FEATURE_L2_X25DTE
mdefine_line|#define ISDN_FEATURE_L2_X25DTE  (0x0001 &lt;&lt; ISDN_PROTO_L2_X25DTE)
DECL|macro|ISDN_FEATURE_L2_X25DCE
mdefine_line|#define ISDN_FEATURE_L2_X25DCE  (0x0001 &lt;&lt; ISDN_PROTO_L2_X25DCE)
DECL|macro|ISDN_FEATURE_L2_V11096
mdefine_line|#define ISDN_FEATURE_L2_V11096  (0x0001 &lt;&lt; ISDN_PROTO_L2_V11096)
DECL|macro|ISDN_FEATURE_L2_V11019
mdefine_line|#define ISDN_FEATURE_L2_V11019  (0x0001 &lt;&lt; ISDN_PROTO_L2_V11019)
DECL|macro|ISDN_FEATURE_L2_V11038
mdefine_line|#define ISDN_FEATURE_L2_V11038  (0x0001 &lt;&lt; ISDN_PROTO_L2_V11038)
DECL|macro|ISDN_FEATURE_L2_MASK
mdefine_line|#define ISDN_FEATURE_L2_MASK    (0x0FFFF) /* Max. 16 protocols */
DECL|macro|ISDN_FEATURE_L2_SHIFT
mdefine_line|#define ISDN_FEATURE_L2_SHIFT   (0)
multiline_comment|/* Layer 3 */
DECL|macro|ISDN_FEATURE_L3_TRANS
mdefine_line|#define ISDN_FEATURE_L3_TRANS   (0x10000 &lt;&lt; ISDN_PROTO_L3_TRANS)
DECL|macro|ISDN_FEATURE_L3_MASK
mdefine_line|#define ISDN_FEATURE_L3_MASK    (0x0FF0000) /* Max. 8 Protocols */
DECL|macro|ISDN_FEATURE_L3_SHIFT
mdefine_line|#define ISDN_FEATURE_L3_SHIFT   (16)
multiline_comment|/* Signaling */
DECL|macro|ISDN_FEATURE_P_UNKNOWN
mdefine_line|#define ISDN_FEATURE_P_UNKNOWN  (0x1000000 &lt;&lt; ISDN_PTYPE_UNKNOWN)
DECL|macro|ISDN_FEATURE_P_1TR6
mdefine_line|#define ISDN_FEATURE_P_1TR6     (0x1000000 &lt;&lt; ISDN_PTYPE_1TR6)
DECL|macro|ISDN_FEATURE_P_EURO
mdefine_line|#define ISDN_FEATURE_P_EURO     (0x1000000 &lt;&lt; ISDN_PTYPE_EURO)
DECL|macro|ISDN_FEATURE_P_NI1
mdefine_line|#define ISDN_FEATURE_P_NI1      (0x1000000 &lt;&lt; ISDN_PTYPE_NI1)
DECL|macro|ISDN_FEATURE_P_MASK
mdefine_line|#define ISDN_FEATURE_P_MASK     (0x0FF000000) /* Max. 8 Protocols */
DECL|macro|ISDN_FEATURE_P_SHIFT
mdefine_line|#define ISDN_FEATURE_P_SHIFT    (24)
DECL|struct|setup_parm
r_typedef
r_struct
id|setup_parm
(brace
DECL|member|phone
r_char
id|phone
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Remote Phone-Number */
DECL|member|eazmsn
r_char
id|eazmsn
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Local EAZ or MSN    */
DECL|member|si1
r_int
r_char
id|si1
suffix:semicolon
multiline_comment|/* Service Indicator 1 */
DECL|member|si2
r_int
r_char
id|si2
suffix:semicolon
multiline_comment|/* Service Indicator 2 */
DECL|member|plan
r_int
r_char
id|plan
suffix:semicolon
multiline_comment|/* Numbering plan      */
DECL|member|screen
r_int
r_char
id|screen
suffix:semicolon
multiline_comment|/* Screening info      */
DECL|typedef|setup_parm
)brace
id|setup_parm
suffix:semicolon
multiline_comment|/*&n; * Structure for exchanging above infos&n; *&n; */
r_typedef
r_struct
(brace
DECL|member|driver
r_int
id|driver
suffix:semicolon
multiline_comment|/* Lowlevel-Driver-ID                    */
DECL|member|command
r_int
id|command
suffix:semicolon
multiline_comment|/* Command or Status (see above)         */
DECL|member|arg
id|ulong
id|arg
suffix:semicolon
multiline_comment|/* Additional Data                       */
r_union
(brace
DECL|member|errcode
id|ulong
id|errcode
suffix:semicolon
multiline_comment|/* Type of error with STAT_L1ERR         */
DECL|member|length
r_int
id|length
suffix:semicolon
multiline_comment|/* Amount of bytes sent with STAT_BSENT  */
DECL|member|num
r_char
id|num
(braket
l_int|50
)braket
suffix:semicolon
multiline_comment|/* Additional Data                       */
DECL|member|setup
id|setup_parm
id|setup
suffix:semicolon
DECL|member|parm
)brace
id|parm
suffix:semicolon
DECL|typedef|isdn_ctrl
)brace
id|isdn_ctrl
suffix:semicolon
multiline_comment|/*&n; * The interface-struct itself (initialized at load-time of lowlevel-driver)&n; *&n; * See Documentation/isdn/INTERFACE for a description, how the communication&n; * between the ISDN subsystem and its drivers is done.&n; *&n; */
r_typedef
r_struct
(brace
multiline_comment|/* Number of channels supported by this driver&n;   */
DECL|member|channels
r_int
id|channels
suffix:semicolon
multiline_comment|/* &n;   * Maximum Size of transmit/receive-buffer this driver supports.&n;   */
DECL|member|maxbufsize
r_int
id|maxbufsize
suffix:semicolon
multiline_comment|/* Feature-Flags for this driver.&n;   * See defines ISDN_FEATURE_... for Values&n;   */
DECL|member|features
r_int
r_int
id|features
suffix:semicolon
multiline_comment|/*&n;   * Needed for calculating&n;   * dev-&gt;hard_header_len = linklayer header + hl_hdrlen;&n;   * Drivers, not supporting sk_buff&squot;s should set this to 0.&n;   */
DECL|member|hl_hdrlen
r_int
r_int
id|hl_hdrlen
suffix:semicolon
multiline_comment|/*&n;   * Receive-Callback using sk_buff&squot;s&n;   * Parameters:&n;   *             int                    Driver-ID&n;   *             int                    local channel-number (0 ...)&n;   *             struct sk_buff *skb    received Data&n;   */
DECL|member|rcvcallb_skb
r_void
(paren
op_star
id|rcvcallb_skb
)paren
(paren
r_int
comma
r_int
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/* Status-Callback&n;   * Parameters:&n;   *             isdn_ctrl*&n;   *                   driver  = Driver ID.&n;   *                   command = One of above ISDN_STAT_... constants.&n;   *                   arg     = depending on status-type.&n;   *                   num     = depending on status-type.&n;   */
DECL|member|statcallb
r_int
(paren
op_star
id|statcallb
)paren
(paren
id|isdn_ctrl
op_star
)paren
suffix:semicolon
multiline_comment|/* Send command&n;   * Parameters:&n;   *             isdn_ctrl*&n;   *                   driver  = Driver ID.&n;   *                   command = One of above ISDN_CMD_... constants.&n;   *                   arg     = depending on command.&n;   *                   num     = depending on command.&n;   */
DECL|member|command
r_int
(paren
op_star
id|command
)paren
(paren
id|isdn_ctrl
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;   * Send data using sk_buff&squot;s&n;   * Parameters:&n;   *             int                    driverId&n;   *             int                    local channel-number (0...)&n;   *             int                    Flag: Need ACK for this packet.&n;   *             struct sk_buff *skb    Data to send&n;   */
DECL|member|writebuf_skb
r_int
(paren
op_star
id|writebuf_skb
)paren
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
multiline_comment|/* Send raw D-Channel-Commands&n;   * Parameters:&n;   *             u_char pointer data&n;   *             int    length of data&n;   *             int    Flag: 0 = Call form Kernel-Space (use memcpy,&n;   *                              no schedule allowed) &n;   *                          1 = Data is in User-Space (use memcpy_fromfs,&n;   *                              may schedule)&n;   *             int    driverId&n;   *             int    local channel-number (0 ...)&n;   */
DECL|member|writecmd
r_int
(paren
op_star
id|writecmd
)paren
(paren
r_const
id|u_char
op_star
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
multiline_comment|/* Read raw Status replies&n;   *             u_char pointer data (volatile)&n;   *             int    length of buffer&n;   *             int    Flag: 0 = Call form Kernel-Space (use memcpy,&n;   *                              no schedule allowed) &n;   *                          1 = Data is in User-Space (use memcpy_fromfs,&n;   *                              may schedule)&n;   *             int    driverId&n;   *             int    local channel-number (0 ...)&n;   */
DECL|member|readstat
r_int
(paren
op_star
id|readstat
)paren
(paren
id|u_char
op_star
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
DECL|member|id
r_char
id|id
(braket
l_int|20
)braket
suffix:semicolon
DECL|typedef|isdn_if
)brace
id|isdn_if
suffix:semicolon
multiline_comment|/*&n; * Function which must be called by lowlevel-driver at loadtime with&n; * the following fields of above struct set:&n; *&n; * channels     Number of channels that will be supported.&n; * hl_hdrlen    Space to preserve in sk_buff&squot;s when sending. Drivers, not&n; *              supporting sk_buff&squot;s should set this to 0.&n; * command      Address of Command-Handler.&n; * features     Bitwise coded Features of this driver. (use ISDN_FEATURE_...)&n; * writebuf_skb Address of Skbuff-Send-Handler.&n; * writecmd        &quot;    &quot;  D-Channel  &quot; which accepts raw D-Ch-Commands.&n; * readstat        &quot;    &quot;  D-Channel  &quot; which delivers raw Status-Data.&n; *&n; * The linklevel-driver fills the following fields:&n; *&n; * channels      Driver-ID assigned to this driver. (Must be used on all&n; *               subsequent callbacks.&n; * rcvcallb_skb  Address of handler for received Skbuff&squot;s.&n; * statcallb        &quot;    &quot;     &quot;    for status-changes.&n; *&n; */
r_extern
r_int
id|register_isdn
c_func
(paren
id|isdn_if
op_star
)paren
suffix:semicolon
macro_line|#ifndef LINUX_VERSION_CODE
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* isdnif_h */
eof
