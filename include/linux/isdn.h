multiline_comment|/* $Id: isdn.h,v 1.29 1997/05/27 15:18:02 fritz Exp $&n; *&n; * Main header for the Linux ISDN subsystem (linklevel).&n; *&n; * Copyright 1994,95,96 by Fritz Elfert (fritz@wuemaus.franken.de)&n; * Copyright 1995,96    by Thinking Objects Software GmbH Wuerzburg&n; * Copyright 1995,96    by Michael Hipp (Michael.Hipp@student.uni-tuebingen.de)&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n; *&n; * $Log: isdn.h,v $&n; * Revision 1.29  1997/05/27 15:18:02  fritz&n; * Added changes for recent 2.1.x kernels:&n; *   changed return type of isdn_close&n; *   queue_task_* -&gt; queue_task&n; *   clear/set_bit -&gt; test_and_... where apropriate.&n; *   changed type of hard_header_cache parameter.&n; *&n; * Revision 1.28  1997/03/07 01:33:01  fritz&n; * Added proper ifdef&squot;s for CONFIG_ISDN_AUDIO&n; *&n; * Revision 1.27  1997/03/05 21:11:49  fritz&n; * Minor fixes.&n; *&n; * Revision 1.26  1997/02/28 02:37:53  fritz&n; * Added some comments.&n; *&n; * Revision 1.25  1997/02/23 16:54:23  hipp&n; * some initial changes for future PPP compresion&n; *&n; * Revision 1.24  1997/02/18 09:42:45  fritz&n; * Bugfix: Increased ISDN_MODEM_ANZREG.&n; * Increased TTY_DV.&n; *&n; * Revision 1.23  1997/02/10 22:07:13  fritz&n; * Added 2 modem registers for numbering plan and screening info.&n; *&n; * Revision 1.22  1997/02/03 23:42:08  fritz&n; * Added ISDN_TIMER_RINGING&n; * Misc. changes for Kernel 2.1.X compatibility&n; *&n; * Revision 1.21  1997/01/17 01:19:10  fritz&n; * Applied chargeint patch.&n; *&n; * Revision 1.20  1997/01/17 00:41:19  fritz&n; * Increased TTY_DV.&n; *&n; * Revision 1.19  1997/01/14 01:41:07  fritz&n; * Added ATI2 related variables.&n; * Added variables for audio support in skbuffs.&n; *&n; * Revision 1.18  1996/11/06 17:37:50  keil&n; * more changes for 2.1.X&n; *&n; * Revision 1.17  1996/09/07 12:53:57  hipp&n; * moved a few isdn_ppp.c specific defines to drives/isdn/isdn_ppp.h&n; *&n; * Revision 1.16  1996/08/12 16:20:56  hipp&n; * renamed ppp_minor to ppp_slot&n; *&n; * Revision 1.15  1996/06/15 14:56:57  fritz&n; * Added version signatures for data structures used&n; * by userlevel programs.&n; *&n; * Revision 1.14  1996/06/06 21:24:23  fritz&n; * Started adding support for suspend/resume.&n; *&n; * Revision 1.13  1996/06/05 02:18:20  fritz&n; * Added DTMF decoding stuff.&n; *&n; * Revision 1.12  1996/06/03 19:55:08  fritz&n; * Fixed typos.&n; *&n; * Revision 1.11  1996/05/31 01:37:47  fritz&n; * Minor changes, due to changes in isdn_tty.c&n; *&n; * Revision 1.10  1996/05/18 01:37:18  fritz&n; * Added spelling corrections and some minor changes&n; * to stay in sync with kernel.&n; *&n; * Revision 1.9  1996/05/17 03:58:20  fritz&n; * Added flags for DLE handling.&n; *&n; * Revision 1.8  1996/05/11 21:49:55  fritz&n; * Removed queue management variables.&n; * Changed queue management to use sk_buffs.&n; *&n; * Revision 1.7  1996/05/07 09:10:06  fritz&n; * Reorganized tty-related structs.&n; *&n; * Revision 1.6  1996/05/06 11:38:27  hipp&n; * minor change in ippp struct&n; *&n; * Revision 1.5  1996/04/30 11:03:16  fritz&n; * Added Michael&squot;s ippp-bind patch.&n; *&n; * Revision 1.4  1996/04/29 23:00:02  fritz&n; * Added variables for voice-support.&n; *&n; * Revision 1.3  1996/04/20 16:54:58  fritz&n; * Increased maximum number of channels.&n; * Added some flags for isdn_net to handle callback more reliable.&n; * Fixed delay-definitions to be more accurate.&n; * Misc. typos&n; *&n; * Revision 1.2  1996/02/11 02:10:02  fritz&n; * Changed IOCTL-names&n; * Added rx_netdev, st_netdev, first_skb, org_hcb, and org_hcu to&n; * Netdevice-local struct.&n; *&n; * Revision 1.1  1996/01/10 20:55:07  fritz&n; * Initial revision&n; *&n; */
macro_line|#ifndef isdn_h
DECL|macro|isdn_h
mdefine_line|#define isdn_h
macro_line|#include &lt;linux/ioctl.h&gt;
DECL|macro|ISDN_TTY_MAJOR
mdefine_line|#define ISDN_TTY_MAJOR    43
DECL|macro|ISDN_TTYAUX_MAJOR
mdefine_line|#define ISDN_TTYAUX_MAJOR 44
DECL|macro|ISDN_MAJOR
mdefine_line|#define ISDN_MAJOR        45
multiline_comment|/* The minor-devicenumbers for Channel 0 and 1 are used as arguments for&n; * physical Channel-Mapping, so they MUST NOT be changed without changing&n; * the correspondent code in isdn.c&n; */
DECL|macro|ISDN_MAX_DRIVERS
mdefine_line|#define ISDN_MAX_DRIVERS    32
DECL|macro|ISDN_MAX_CHANNELS
mdefine_line|#define ISDN_MAX_CHANNELS   64
DECL|macro|ISDN_MINOR_B
mdefine_line|#define ISDN_MINOR_B        0
DECL|macro|ISDN_MINOR_BMAX
mdefine_line|#define ISDN_MINOR_BMAX     (ISDN_MAX_CHANNELS-1)
DECL|macro|ISDN_MINOR_CTRL
mdefine_line|#define ISDN_MINOR_CTRL     ISDN_MAX_CHANNELS
DECL|macro|ISDN_MINOR_CTRLMAX
mdefine_line|#define ISDN_MINOR_CTRLMAX  (2*ISDN_MAX_CHANNELS-1)
DECL|macro|ISDN_MINOR_PPP
mdefine_line|#define ISDN_MINOR_PPP      (2*ISDN_MAX_CHANNELS)
DECL|macro|ISDN_MINOR_PPPMAX
mdefine_line|#define ISDN_MINOR_PPPMAX   (3*ISDN_MAX_CHANNELS-1)
DECL|macro|ISDN_MINOR_STATUS
mdefine_line|#define ISDN_MINOR_STATUS   255
multiline_comment|/* New ioctl-codes */
DECL|macro|IIOCNETAIF
mdefine_line|#define IIOCNETAIF  _IO(&squot;I&squot;,1)
DECL|macro|IIOCNETDIF
mdefine_line|#define IIOCNETDIF  _IO(&squot;I&squot;,2)
DECL|macro|IIOCNETSCF
mdefine_line|#define IIOCNETSCF  _IO(&squot;I&squot;,3)
DECL|macro|IIOCNETGCF
mdefine_line|#define IIOCNETGCF  _IO(&squot;I&squot;,4)
DECL|macro|IIOCNETANM
mdefine_line|#define IIOCNETANM  _IO(&squot;I&squot;,5)
DECL|macro|IIOCNETDNM
mdefine_line|#define IIOCNETDNM  _IO(&squot;I&squot;,6)
DECL|macro|IIOCNETGNM
mdefine_line|#define IIOCNETGNM  _IO(&squot;I&squot;,7)
DECL|macro|IIOCGETSET
mdefine_line|#define IIOCGETSET  _IO(&squot;I&squot;,8)
DECL|macro|IIOCSETSET
mdefine_line|#define IIOCSETSET  _IO(&squot;I&squot;,9)
DECL|macro|IIOCSETVER
mdefine_line|#define IIOCSETVER  _IO(&squot;I&squot;,10)
DECL|macro|IIOCNETHUP
mdefine_line|#define IIOCNETHUP  _IO(&squot;I&squot;,11)
DECL|macro|IIOCSETGST
mdefine_line|#define IIOCSETGST  _IO(&squot;I&squot;,12)
DECL|macro|IIOCSETBRJ
mdefine_line|#define IIOCSETBRJ  _IO(&squot;I&squot;,13)
DECL|macro|IIOCSIGPRF
mdefine_line|#define IIOCSIGPRF  _IO(&squot;I&squot;,14)
DECL|macro|IIOCGETPRF
mdefine_line|#define IIOCGETPRF  _IO(&squot;I&squot;,15)
DECL|macro|IIOCSETPRF
mdefine_line|#define IIOCSETPRF  _IO(&squot;I&squot;,16)
DECL|macro|IIOCGETMAP
mdefine_line|#define IIOCGETMAP  _IO(&squot;I&squot;,17)
DECL|macro|IIOCSETMAP
mdefine_line|#define IIOCSETMAP  _IO(&squot;I&squot;,18)
DECL|macro|IIOCNETASL
mdefine_line|#define IIOCNETASL  _IO(&squot;I&squot;,19)
DECL|macro|IIOCNETDIL
mdefine_line|#define IIOCNETDIL  _IO(&squot;I&squot;,20)
DECL|macro|IIOCGETCPS
mdefine_line|#define IIOCGETCPS  _IO(&squot;I&squot;,21)
DECL|macro|IIOCGETDVR
mdefine_line|#define IIOCGETDVR  _IO(&squot;I&squot;,22)
DECL|macro|IIOCNETALN
mdefine_line|#define IIOCNETALN  _IO(&squot;I&squot;,32)
DECL|macro|IIOCNETDLN
mdefine_line|#define IIOCNETDLN  _IO(&squot;I&squot;,33)
DECL|macro|IIOCDBGVAR
mdefine_line|#define IIOCDBGVAR  _IO(&squot;I&squot;,127)
DECL|macro|IIOCDRVCTL
mdefine_line|#define IIOCDRVCTL  _IO(&squot;I&squot;,128)
multiline_comment|/* Packet encapsulations for net-interfaces */
DECL|macro|ISDN_NET_ENCAP_ETHER
mdefine_line|#define ISDN_NET_ENCAP_ETHER     0
DECL|macro|ISDN_NET_ENCAP_RAWIP
mdefine_line|#define ISDN_NET_ENCAP_RAWIP     1
DECL|macro|ISDN_NET_ENCAP_IPTYP
mdefine_line|#define ISDN_NET_ENCAP_IPTYP     2
DECL|macro|ISDN_NET_ENCAP_CISCOHDLC
mdefine_line|#define ISDN_NET_ENCAP_CISCOHDLC 3
DECL|macro|ISDN_NET_ENCAP_SYNCPPP
mdefine_line|#define ISDN_NET_ENCAP_SYNCPPP   4
DECL|macro|ISDN_NET_ENCAP_UIHDLC
mdefine_line|#define ISDN_NET_ENCAP_UIHDLC    5
multiline_comment|/* Facility which currently uses an ISDN-channel */
DECL|macro|ISDN_USAGE_NONE
mdefine_line|#define ISDN_USAGE_NONE       0
DECL|macro|ISDN_USAGE_RAW
mdefine_line|#define ISDN_USAGE_RAW        1
DECL|macro|ISDN_USAGE_MODEM
mdefine_line|#define ISDN_USAGE_MODEM      2
DECL|macro|ISDN_USAGE_NET
mdefine_line|#define ISDN_USAGE_NET        3
DECL|macro|ISDN_USAGE_VOICE
mdefine_line|#define ISDN_USAGE_VOICE      4
DECL|macro|ISDN_USAGE_FAX
mdefine_line|#define ISDN_USAGE_FAX        5
DECL|macro|ISDN_USAGE_MASK
mdefine_line|#define ISDN_USAGE_MASK       7 /* Mask to get plain usage */
DECL|macro|ISDN_USAGE_EXCLUSIVE
mdefine_line|#define ISDN_USAGE_EXCLUSIVE 64 /* This bit is set, if channel is exclusive */
DECL|macro|ISDN_USAGE_OUTGOING
mdefine_line|#define ISDN_USAGE_OUTGOING 128 /* This bit is set, if channel is outgoing  */
DECL|macro|ISDN_MODEM_ANZREG
mdefine_line|#define ISDN_MODEM_ANZREG    23        /* Number of Modem-Registers        */
DECL|macro|ISDN_MSNLEN
mdefine_line|#define ISDN_MSNLEN          20
r_typedef
r_struct
(brace
DECL|member|drvid
r_char
id|drvid
(braket
l_int|25
)braket
suffix:semicolon
DECL|member|arg
r_int
r_int
id|arg
suffix:semicolon
DECL|typedef|isdn_ioctl_struct
)brace
id|isdn_ioctl_struct
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|isdndev
r_int
r_int
id|isdndev
suffix:semicolon
DECL|member|atmodem
r_int
r_int
id|atmodem
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
DECL|member|info
r_int
r_int
id|info
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
DECL|typedef|debugvar_addr
)brace
id|debugvar_addr
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|name
r_char
id|name
(braket
l_int|10
)braket
suffix:semicolon
DECL|member|phone
r_char
id|phone
(braket
id|ISDN_MSNLEN
)braket
suffix:semicolon
DECL|member|outgoing
r_int
id|outgoing
suffix:semicolon
DECL|typedef|isdn_net_ioctl_phone
)brace
id|isdn_net_ioctl_phone
suffix:semicolon
DECL|macro|NET_DV
mdefine_line|#define NET_DV 0x02 /* Data version for net_cfg     */
DECL|macro|TTY_DV
mdefine_line|#define TTY_DV 0x04 /* Data version for iprofd etc. */
r_typedef
r_struct
(brace
DECL|member|name
r_char
id|name
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* Name of interface                     */
DECL|member|master
r_char
id|master
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* Name of Master for Bundling           */
DECL|member|slave
r_char
id|slave
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* Name of Slave for Bundling            */
DECL|member|eaz
r_char
id|eaz
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* EAZ/MSN                               */
DECL|member|drvid
r_char
id|drvid
(braket
l_int|25
)braket
suffix:semicolon
multiline_comment|/* DriverId for Bindings                 */
DECL|member|onhtime
r_int
id|onhtime
suffix:semicolon
multiline_comment|/* Hangup-Timeout                        */
DECL|member|charge
r_int
id|charge
suffix:semicolon
multiline_comment|/* Charge-Units                          */
DECL|member|l2_proto
r_int
id|l2_proto
suffix:semicolon
multiline_comment|/* Layer-2 protocol                      */
DECL|member|l3_proto
r_int
id|l3_proto
suffix:semicolon
multiline_comment|/* Layer-3 protocol                      */
DECL|member|p_encap
r_int
id|p_encap
suffix:semicolon
multiline_comment|/* Encapsulation                         */
DECL|member|exclusive
r_int
id|exclusive
suffix:semicolon
multiline_comment|/* Channel, if bound exclusive           */
DECL|member|dialmax
r_int
id|dialmax
suffix:semicolon
multiline_comment|/* Dial Retry-Counter                    */
DECL|member|slavedelay
r_int
id|slavedelay
suffix:semicolon
multiline_comment|/* Delay until slave starts up           */
DECL|member|cbdelay
r_int
id|cbdelay
suffix:semicolon
multiline_comment|/* Delay before Callback                 */
DECL|member|chargehup
r_int
id|chargehup
suffix:semicolon
multiline_comment|/* Flag: Charge-Hangup                   */
DECL|member|ihup
r_int
id|ihup
suffix:semicolon
multiline_comment|/* Flag: Hangup-Timeout on incoming line */
DECL|member|secure
r_int
id|secure
suffix:semicolon
multiline_comment|/* Flag: Secure                          */
DECL|member|callback
r_int
id|callback
suffix:semicolon
multiline_comment|/* Flag: Callback                        */
DECL|member|cbhup
r_int
id|cbhup
suffix:semicolon
multiline_comment|/* Flag: Reject Call before Callback     */
DECL|member|pppbind
r_int
id|pppbind
suffix:semicolon
multiline_comment|/* ippp device for bindings              */
DECL|member|chargeint
r_int
id|chargeint
suffix:semicolon
multiline_comment|/* Use fixed charge interval length      */
DECL|typedef|isdn_net_ioctl_cfg
)brace
id|isdn_net_ioctl_cfg
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#ifndef STANDALONE
macro_line|#include &lt;linux/config.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/serial_reg.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/tcp.h&gt;
macro_line|#ifdef CONFIG_ISDN_PPP
macro_line|#ifdef CONFIG_ISDN_PPP_VJ
macro_line|#  include &lt;net/slhc_vj.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/ppp_defs.h&gt;
macro_line|#include &lt;linux/if_ppp.h&gt;
macro_line|#include &lt;linux/if_pppvar.h&gt;
macro_line|#include &lt;linux/isdn_ppp.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/isdnif.h&gt;
DECL|macro|ISDN_DRVIOCTL_MASK
mdefine_line|#define ISDN_DRVIOCTL_MASK       0x7f  /* Mask for Device-ioctl */
multiline_comment|/* Until now unused */
DECL|macro|ISDN_SERVICE_VOICE
mdefine_line|#define ISDN_SERVICE_VOICE 1
DECL|macro|ISDN_SERVICE_AB
mdefine_line|#define ISDN_SERVICE_AB    1&lt;&lt;1 
DECL|macro|ISDN_SERVICE_X21
mdefine_line|#define ISDN_SERVICE_X21   1&lt;&lt;2
DECL|macro|ISDN_SERVICE_G4
mdefine_line|#define ISDN_SERVICE_G4    1&lt;&lt;3
DECL|macro|ISDN_SERVICE_BTX
mdefine_line|#define ISDN_SERVICE_BTX   1&lt;&lt;4
DECL|macro|ISDN_SERVICE_DFUE
mdefine_line|#define ISDN_SERVICE_DFUE  1&lt;&lt;5
DECL|macro|ISDN_SERVICE_X25
mdefine_line|#define ISDN_SERVICE_X25   1&lt;&lt;6
DECL|macro|ISDN_SERVICE_TTX
mdefine_line|#define ISDN_SERVICE_TTX   1&lt;&lt;7
DECL|macro|ISDN_SERVICE_MIXED
mdefine_line|#define ISDN_SERVICE_MIXED 1&lt;&lt;8
DECL|macro|ISDN_SERVICE_FW
mdefine_line|#define ISDN_SERVICE_FW    1&lt;&lt;9
DECL|macro|ISDN_SERVICE_GTEL
mdefine_line|#define ISDN_SERVICE_GTEL  1&lt;&lt;10
DECL|macro|ISDN_SERVICE_BTXN
mdefine_line|#define ISDN_SERVICE_BTXN  1&lt;&lt;11
DECL|macro|ISDN_SERVICE_BTEL
mdefine_line|#define ISDN_SERVICE_BTEL  1&lt;&lt;12
multiline_comment|/* Macros checking plain usage */
DECL|macro|USG_NONE
mdefine_line|#define USG_NONE(x)         ((x &amp; ISDN_USAGE_MASK)==ISDN_USAGE_NONE)
DECL|macro|USG_RAW
mdefine_line|#define USG_RAW(x)          ((x &amp; ISDN_USAGE_MASK)==ISDN_USAGE_RAW)
DECL|macro|USG_MODEM
mdefine_line|#define USG_MODEM(x)        ((x &amp; ISDN_USAGE_MASK)==ISDN_USAGE_MODEM)
DECL|macro|USG_VOICE
mdefine_line|#define USG_VOICE(x)        ((x &amp; ISDN_USAGE_MASK)==ISDN_USAGE_VOICE)
DECL|macro|USG_NET
mdefine_line|#define USG_NET(x)          ((x &amp; ISDN_USAGE_MASK)==ISDN_USAGE_NET)
DECL|macro|USG_OUTGOING
mdefine_line|#define USG_OUTGOING(x)     ((x &amp; ISDN_USAGE_OUTGOING)==ISDN_USAGE_OUTGOING)
DECL|macro|USG_MODEMORVOICE
mdefine_line|#define USG_MODEMORVOICE(x) (((x &amp; ISDN_USAGE_MASK)==ISDN_USAGE_MODEM) || &bslash;&n;                             ((x &amp; ISDN_USAGE_MASK)==ISDN_USAGE_VOICE)     )
multiline_comment|/* Timer-delays and scheduling-flags */
DECL|macro|ISDN_TIMER_RES
mdefine_line|#define ISDN_TIMER_RES       3                     /* Main Timer-Resolution  */
DECL|macro|ISDN_TIMER_02SEC
mdefine_line|#define ISDN_TIMER_02SEC     (HZ/(ISDN_TIMER_RES+1)/5) /* Slow-Timer1 .2 sec */
DECL|macro|ISDN_TIMER_1SEC
mdefine_line|#define ISDN_TIMER_1SEC      (HZ/(ISDN_TIMER_RES+1)) /* Slow-Timer2 1 sec   */
DECL|macro|ISDN_TIMER_RINGING
mdefine_line|#define ISDN_TIMER_RINGING   5 /* tty RINGs = ISDN_TIMER_1SEC * this factor */
DECL|macro|ISDN_TIMER_MODEMREAD
mdefine_line|#define ISDN_TIMER_MODEMREAD 1
DECL|macro|ISDN_TIMER_MODEMPLUS
mdefine_line|#define ISDN_TIMER_MODEMPLUS 2
DECL|macro|ISDN_TIMER_MODEMRING
mdefine_line|#define ISDN_TIMER_MODEMRING 4
DECL|macro|ISDN_TIMER_MODEMXMIT
mdefine_line|#define ISDN_TIMER_MODEMXMIT 8
DECL|macro|ISDN_TIMER_NETDIAL
mdefine_line|#define ISDN_TIMER_NETDIAL   16
DECL|macro|ISDN_TIMER_NETHANGUP
mdefine_line|#define ISDN_TIMER_NETHANGUP 32
DECL|macro|ISDN_TIMER_IPPP
mdefine_line|#define ISDN_TIMER_IPPP      64
DECL|macro|ISDN_TIMER_FAST
mdefine_line|#define ISDN_TIMER_FAST      (ISDN_TIMER_MODEMREAD | ISDN_TIMER_MODEMPLUS | &bslash;&n;                              ISDN_TIMER_MODEMXMIT)
DECL|macro|ISDN_TIMER_SLOW
mdefine_line|#define ISDN_TIMER_SLOW      (ISDN_TIMER_MODEMRING | ISDN_TIMER_NETHANGUP | &bslash;&n;                              ISDN_TIMER_NETDIAL)
multiline_comment|/* Timeout-Values for isdn_net_dial() */
DECL|macro|ISDN_TIMER_DTIMEOUT10
mdefine_line|#define ISDN_TIMER_DTIMEOUT10 (10*HZ/(ISDN_TIMER_02SEC*(ISDN_TIMER_RES+1)))
DECL|macro|ISDN_TIMER_DTIMEOUT15
mdefine_line|#define ISDN_TIMER_DTIMEOUT15 (15*HZ/(ISDN_TIMER_02SEC*(ISDN_TIMER_RES+1)))
multiline_comment|/* GLOBAL_FLAGS */
DECL|macro|ISDN_GLOBAL_STOPPED
mdefine_line|#define ISDN_GLOBAL_STOPPED 1
multiline_comment|/*=================== Start of ip-over-ISDN stuff =========================*/
multiline_comment|/* Feature- and status-flags for a net-interface */
DECL|macro|ISDN_NET_CONNECTED
mdefine_line|#define ISDN_NET_CONNECTED  0x01       /* Bound to ISDN-Channel             */
DECL|macro|ISDN_NET_SECURE
mdefine_line|#define ISDN_NET_SECURE     0x02       /* Accept calls from phonelist only  */
DECL|macro|ISDN_NET_CALLBACK
mdefine_line|#define ISDN_NET_CALLBACK   0x04       /* activate callback                 */
DECL|macro|ISDN_NET_CBHUP
mdefine_line|#define ISDN_NET_CBHUP      0x08       /* hangup before callback            */
DECL|macro|ISDN_NET_CBOUT
mdefine_line|#define ISDN_NET_CBOUT      0x10       /* remote machine does callback      */
macro_line|#if 0
multiline_comment|/* Unused??? */
mdefine_line|#define ISDN_NET_CLONE      0x08       /* clone a tmp interface when called */
mdefine_line|#define ISDN_NET_TMP        0x10       /* tmp interface until getting an IP */
mdefine_line|#define ISDN_NET_DYNAMIC    0x20       /* this link is dynamically allocated */
macro_line|#endif
DECL|macro|ISDN_NET_MAGIC
mdefine_line|#define ISDN_NET_MAGIC      0x49344C02 /* for paranoia-checking             */
multiline_comment|/* Phone-list-element */
r_typedef
r_struct
(brace
DECL|member|next
r_void
op_star
id|next
suffix:semicolon
DECL|member|num
r_char
id|num
(braket
id|ISDN_MSNLEN
)braket
suffix:semicolon
DECL|typedef|isdn_net_phone
)brace
id|isdn_net_phone
suffix:semicolon
multiline_comment|/* Local interface-data */
DECL|struct|isdn_net_local_s
r_typedef
r_struct
id|isdn_net_local_s
(brace
DECL|member|magic
id|ulong
id|magic
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* Name of device                   */
DECL|member|stats
r_struct
id|enet_statistics
id|stats
suffix:semicolon
multiline_comment|/* Ethernet Statistics              */
DECL|member|isdn_device
r_int
id|isdn_device
suffix:semicolon
multiline_comment|/* Index to isdn-device             */
DECL|member|isdn_channel
r_int
id|isdn_channel
suffix:semicolon
multiline_comment|/* Index to isdn-channel            */
DECL|member|ppp_slot
r_int
id|ppp_slot
suffix:semicolon
multiline_comment|/* PPPD device slot number          */
DECL|member|pre_device
r_int
id|pre_device
suffix:semicolon
multiline_comment|/* Preselected isdn-device          */
DECL|member|pre_channel
r_int
id|pre_channel
suffix:semicolon
multiline_comment|/* Preselected isdn-channel         */
DECL|member|exclusive
r_int
id|exclusive
suffix:semicolon
multiline_comment|/* If non-zero idx to reserved chan.*/
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* Connection-flags                 */
DECL|member|dialretry
r_int
id|dialretry
suffix:semicolon
multiline_comment|/* Counter for Dialout-retries      */
DECL|member|dialmax
r_int
id|dialmax
suffix:semicolon
multiline_comment|/* Max. Number of Dial-retries      */
DECL|member|cbdelay
r_int
id|cbdelay
suffix:semicolon
multiline_comment|/* Delay before Callback starts     */
DECL|member|dtimer
r_int
id|dtimer
suffix:semicolon
multiline_comment|/* Timeout-counter for dialing      */
DECL|member|msn
r_char
id|msn
(braket
id|ISDN_MSNLEN
)braket
suffix:semicolon
multiline_comment|/* MSNs/EAZs for this interface */
DECL|member|cbhup
id|u_char
id|cbhup
suffix:semicolon
multiline_comment|/* Flag: Reject Call before Callback*/
DECL|member|dialstate
id|u_char
id|dialstate
suffix:semicolon
multiline_comment|/* State for dialing                */
DECL|member|p_encap
id|u_char
id|p_encap
suffix:semicolon
multiline_comment|/* Packet encapsulation             */
multiline_comment|/*   0 = Ethernet over ISDN         */
multiline_comment|/*   1 = RAW-IP                     */
multiline_comment|/*   2 = IP with type field         */
DECL|member|l2_proto
id|u_char
id|l2_proto
suffix:semicolon
multiline_comment|/* Layer-2-protocol                 */
multiline_comment|/* See ISDN_PROTO_L2..-constants in */
multiline_comment|/* isdnif.h                         */
multiline_comment|/*   0 = X75/LAPB with I-Frames     */
multiline_comment|/*   1 = X75/LAPB with UI-Frames    */
multiline_comment|/*   2 = X75/LAPB with BUI-Frames   */
multiline_comment|/*   3 = HDLC                       */
DECL|member|l3_proto
id|u_char
id|l3_proto
suffix:semicolon
multiline_comment|/* Layer-3-protocol                 */
multiline_comment|/* See ISDN_PROTO_L3..-constants in */
multiline_comment|/* isdnif.h                         */
multiline_comment|/*   0 = Transparent                */
DECL|member|huptimer
r_int
id|huptimer
suffix:semicolon
multiline_comment|/* Timeout-counter for auto-hangup  */
DECL|member|charge
r_int
id|charge
suffix:semicolon
multiline_comment|/* Counter for charging units       */
DECL|member|chargetime
r_int
id|chargetime
suffix:semicolon
multiline_comment|/* Timer for Charging info          */
DECL|member|hupflags
r_int
id|hupflags
suffix:semicolon
multiline_comment|/* Flags for charge-unit-hangup:    */
multiline_comment|/* bit0: chargeint is invalid       */
multiline_comment|/* bit1: Getting charge-interval    */
multiline_comment|/* bit2: Do charge-unit-hangup      */
multiline_comment|/* bit3: Do hangup even on incoming */
DECL|member|outgoing
r_int
id|outgoing
suffix:semicolon
multiline_comment|/* Flag: outgoing call              */
DECL|member|onhtime
r_int
id|onhtime
suffix:semicolon
multiline_comment|/* Time to keep link up             */
DECL|member|chargeint
r_int
id|chargeint
suffix:semicolon
multiline_comment|/* Interval between charge-infos    */
DECL|member|onum
r_int
id|onum
suffix:semicolon
multiline_comment|/* Flag: at least 1 outgoing number */
DECL|member|cps
r_int
id|cps
suffix:semicolon
multiline_comment|/* current speed of this interface  */
DECL|member|transcount
r_int
id|transcount
suffix:semicolon
multiline_comment|/* byte-counter for cps-calculation */
DECL|member|sqfull
r_int
id|sqfull
suffix:semicolon
multiline_comment|/* Flag: netdev-queue overloaded    */
DECL|member|sqfull_stamp
id|ulong
id|sqfull_stamp
suffix:semicolon
multiline_comment|/* Start-Time of overload           */
DECL|member|slavedelay
id|ulong
id|slavedelay
suffix:semicolon
multiline_comment|/* Dynamic bundling delaytime       */
DECL|member|srobin
r_struct
id|device
op_star
id|srobin
suffix:semicolon
multiline_comment|/* Ptr to Master device for slaves  */
DECL|member|phone
id|isdn_net_phone
op_star
id|phone
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* List of remote-phonenumbers      */
multiline_comment|/* phone[0] = Incoming Numbers      */
multiline_comment|/* phone[1] = Outgoing Numbers      */
DECL|member|dial
id|isdn_net_phone
op_star
id|dial
suffix:semicolon
multiline_comment|/* Pointer to dialed number         */
DECL|member|master
r_struct
id|device
op_star
id|master
suffix:semicolon
multiline_comment|/* Ptr to Master device for slaves  */
DECL|member|slave
r_struct
id|device
op_star
id|slave
suffix:semicolon
multiline_comment|/* Ptr to Slave device for masters  */
DECL|member|next
r_struct
id|isdn_net_local_s
op_star
id|next
suffix:semicolon
multiline_comment|/* Ptr to next link in bundle       */
DECL|member|last
r_struct
id|isdn_net_local_s
op_star
id|last
suffix:semicolon
multiline_comment|/* Ptr to last link in bundle       */
DECL|member|netdev
r_struct
id|isdn_net_dev_s
op_star
id|netdev
suffix:semicolon
multiline_comment|/* Ptr to netdev                    */
DECL|member|first_skb
r_struct
id|sk_buff
op_star
id|first_skb
suffix:semicolon
multiline_comment|/* Ptr to skb that triggers dialing */
DECL|member|sav_skb
r_struct
id|sk_buff
op_star
id|sav_skb
suffix:semicolon
multiline_comment|/* Ptr to skb, rejected by LL-driver*/
multiline_comment|/* Ptr to orig. hard_header_cache   */
DECL|member|org_hhc
r_int
(paren
op_star
id|org_hhc
)paren
(paren
r_struct
id|neighbour
op_star
id|neigh
comma
r_struct
id|hh_cache
op_star
id|hh
)paren
suffix:semicolon
multiline_comment|/* Ptr to orig. header_cache_update */
DECL|member|org_hcu
r_void
(paren
op_star
id|org_hcu
)paren
(paren
r_struct
id|hh_cache
op_star
comma
r_struct
id|device
op_star
comma
r_int
r_char
op_star
)paren
suffix:semicolon
DECL|member|pppbind
r_int
id|pppbind
suffix:semicolon
multiline_comment|/* ippp device for bindings         */
DECL|typedef|isdn_net_local
)brace
id|isdn_net_local
suffix:semicolon
macro_line|#ifdef CONFIG_ISDN_PPP
DECL|struct|ippp_bundle
r_struct
id|ippp_bundle
(brace
DECL|member|mp_mrru
r_int
id|mp_mrru
suffix:semicolon
multiline_comment|/* unused                             */
DECL|member|last
r_struct
id|mpqueue
op_star
id|last
suffix:semicolon
multiline_comment|/* currently defined in isdn_net_dev  */
DECL|member|min
r_int
id|min
suffix:semicolon
multiline_comment|/* currently calculated &squot;on the fly&squot;  */
DECL|member|next_num
r_int
id|next_num
suffix:semicolon
multiline_comment|/* we wanna see this seq.-number next */
DECL|member|sq
r_struct
id|sqqueue
op_star
id|sq
suffix:semicolon
DECL|member|modify
r_int
id|modify
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* set to 1 while modifying sqqueue   */
DECL|member|bundled
r_int
id|bundled
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* bundle active ?                    */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* the interface itself */
DECL|struct|isdn_net_dev_s
r_typedef
r_struct
id|isdn_net_dev_s
(brace
DECL|member|local
id|isdn_net_local
id|local
suffix:semicolon
DECL|member|queue
id|isdn_net_local
op_star
id|queue
suffix:semicolon
DECL|member|next
r_void
op_star
id|next
suffix:semicolon
multiline_comment|/* Pointer to next isdn-interface   */
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* interface to upper levels        */
macro_line|#ifdef CONFIG_ISDN_PPP
DECL|member|mp_last
r_struct
id|mpqueue
op_star
id|mp_last
suffix:semicolon
DECL|member|ib
r_struct
id|ippp_bundle
id|ib
suffix:semicolon
macro_line|#endif
DECL|typedef|isdn_net_dev
)brace
id|isdn_net_dev
suffix:semicolon
multiline_comment|/*===================== End of ip-over-ISDN stuff ===========================*/
multiline_comment|/*======================= Start of ISDN-tty stuff ===========================*/
DECL|macro|ISDN_ASYNC_MAGIC
mdefine_line|#define ISDN_ASYNC_MAGIC          0x49344C01 /* for paranoia-checking        */
DECL|macro|ISDN_ASYNC_INITIALIZED
mdefine_line|#define ISDN_ASYNC_INITIALIZED&t;  0x80000000 /* port was initialized         */
DECL|macro|ISDN_ASYNC_CALLOUT_ACTIVE
mdefine_line|#define ISDN_ASYNC_CALLOUT_ACTIVE 0x40000000 /* Call out device active       */
DECL|macro|ISDN_ASYNC_NORMAL_ACTIVE
mdefine_line|#define ISDN_ASYNC_NORMAL_ACTIVE  0x20000000 /* Normal device active         */
DECL|macro|ISDN_ASYNC_CLOSING
mdefine_line|#define ISDN_ASYNC_CLOSING&t;  0x08000000 /* Serial port is closing       */
DECL|macro|ISDN_ASYNC_CTS_FLOW
mdefine_line|#define ISDN_ASYNC_CTS_FLOW&t;  0x04000000 /* Do CTS flow control          */
DECL|macro|ISDN_ASYNC_CHECK_CD
mdefine_line|#define ISDN_ASYNC_CHECK_CD&t;  0x02000000 /* i.e., CLOCAL                 */
DECL|macro|ISDN_ASYNC_HUP_NOTIFY
mdefine_line|#define ISDN_ASYNC_HUP_NOTIFY         0x0001 /* Notify tty on hangups/closes */
DECL|macro|ISDN_ASYNC_SESSION_LOCKOUT
mdefine_line|#define ISDN_ASYNC_SESSION_LOCKOUT    0x0100 /* Lock cua opens on session    */
DECL|macro|ISDN_ASYNC_PGRP_LOCKOUT
mdefine_line|#define ISDN_ASYNC_PGRP_LOCKOUT       0x0200 /* Lock cua opens on pgrp       */
DECL|macro|ISDN_ASYNC_CALLOUT_NOHUP
mdefine_line|#define ISDN_ASYNC_CALLOUT_NOHUP      0x0400 /* No hangup for cui            */
DECL|macro|ISDN_ASYNC_SPLIT_TERMIOS
mdefine_line|#define ISDN_ASYNC_SPLIT_TERMIOS      0x0008 /* Sep. termios for dialin/out  */
DECL|macro|ISDN_SERIAL_XMIT_SIZE
mdefine_line|#define ISDN_SERIAL_XMIT_SIZE           4000 /* Maximum bufsize for write    */
DECL|macro|ISDN_SERIAL_TYPE_NORMAL
mdefine_line|#define ISDN_SERIAL_TYPE_NORMAL            1
DECL|macro|ISDN_SERIAL_TYPE_CALLOUT
mdefine_line|#define ISDN_SERIAL_TYPE_CALLOUT           2
macro_line|#ifdef CONFIG_ISDN_AUDIO
multiline_comment|/* For using sk_buffs with audio we need some private variables&n; * within each sk_buff. For this purpose, we declare a struct here,&n; * and put it always at skb-&gt;head. A few macros help accessing the&n; * variables. Of course, we need to check skb_headroom prior to&n; * any access.&n; */
DECL|struct|isdn_audio_skb
r_typedef
r_struct
id|isdn_audio_skb
(brace
DECL|member|dle_count
r_int
r_int
id|dle_count
suffix:semicolon
DECL|member|lock
r_int
r_char
id|lock
suffix:semicolon
DECL|typedef|isdn_audio_skb
)brace
id|isdn_audio_skb
suffix:semicolon
DECL|macro|ISDN_AUDIO_SKB_DLECOUNT
mdefine_line|#define ISDN_AUDIO_SKB_DLECOUNT(skb) (((isdn_audio_skb*)skb-&gt;head)-&gt;dle_count)
DECL|macro|ISDN_AUDIO_SKB_LOCK
mdefine_line|#define ISDN_AUDIO_SKB_LOCK(skb) (((isdn_audio_skb*)skb-&gt;head)-&gt;lock)
macro_line|#endif
multiline_comment|/* Private data of AT-command-interpreter */
DECL|struct|atemu
r_typedef
r_struct
id|atemu
(brace
DECL|member|profile
id|u_char
id|profile
(braket
id|ISDN_MODEM_ANZREG
)braket
suffix:semicolon
multiline_comment|/* Modem-Regs. Profile 0 */
DECL|member|mdmreg
id|u_char
id|mdmreg
(braket
id|ISDN_MODEM_ANZREG
)braket
suffix:semicolon
multiline_comment|/* Modem-Registers       */
DECL|member|pmsn
r_char
id|pmsn
(braket
id|ISDN_MSNLEN
)braket
suffix:semicolon
multiline_comment|/* EAZ/MSNs Profile 0             */
DECL|member|msn
r_char
id|msn
(braket
id|ISDN_MSNLEN
)braket
suffix:semicolon
multiline_comment|/* EAZ/MSN                          */
macro_line|#ifdef CONFIG_ISDN_AUDIO
DECL|member|vpar
id|u_char
id|vpar
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* Voice-parameters                 */
DECL|member|lastDLE
r_int
id|lastDLE
suffix:semicolon
multiline_comment|/* Flag for voice-coding: DLE seen  */
macro_line|#endif
DECL|member|mdmcmdl
r_int
id|mdmcmdl
suffix:semicolon
multiline_comment|/* Length of Modem-Commandbuffer    */
DECL|member|pluscount
r_int
id|pluscount
suffix:semicolon
multiline_comment|/* Counter for +++ sequence         */
DECL|member|lastplus
r_int
id|lastplus
suffix:semicolon
multiline_comment|/* Timestamp of last +              */
DECL|member|mdmcmd
r_char
id|mdmcmd
(braket
l_int|255
)braket
suffix:semicolon
multiline_comment|/* Modem-Commandbuffer              */
DECL|typedef|atemu
)brace
id|atemu
suffix:semicolon
multiline_comment|/* Private data (similar to async_struct in &lt;linux/serial.h&gt;) */
DECL|struct|modem_info
r_typedef
r_struct
id|modem_info
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* defined in tty.h               */
DECL|member|x_char
r_int
id|x_char
suffix:semicolon
multiline_comment|/* xon/xoff character             */
DECL|member|mcr
r_int
id|mcr
suffix:semicolon
multiline_comment|/* Modem control register         */
DECL|member|msr
r_int
id|msr
suffix:semicolon
multiline_comment|/* Modem status register          */
DECL|member|lsr
r_int
id|lsr
suffix:semicolon
multiline_comment|/* Line status register           */
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* # of fd on device              */
DECL|member|blocked_open
r_int
id|blocked_open
suffix:semicolon
multiline_comment|/* # of blocked opens             */
DECL|member|session
r_int
id|session
suffix:semicolon
multiline_comment|/* Session of opening process     */
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
multiline_comment|/* pgrp of opening process        */
DECL|member|online
r_int
id|online
suffix:semicolon
multiline_comment|/* 1 = B-Channel is up, drop data */
multiline_comment|/* 2 = B-Channel is up, deliver d.*/
DECL|member|dialing
r_int
id|dialing
suffix:semicolon
multiline_comment|/* Dial in progress               */
DECL|member|rcvsched
r_int
id|rcvsched
suffix:semicolon
multiline_comment|/* Receive needs schedule         */
DECL|member|isdn_driver
r_int
id|isdn_driver
suffix:semicolon
multiline_comment|/* Index to isdn-driver           */
DECL|member|isdn_channel
r_int
id|isdn_channel
suffix:semicolon
multiline_comment|/* Index to isdn-channel          */
DECL|member|drv_index
r_int
id|drv_index
suffix:semicolon
multiline_comment|/* Index to dev-&gt;usage            */
DECL|member|ncarrier
r_int
id|ncarrier
suffix:semicolon
multiline_comment|/* Flag: schedule NO CARRIER      */
DECL|member|last_cause
r_int
r_char
id|last_cause
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Last cause message             */
DECL|member|last_num
r_int
r_char
id|last_num
(braket
id|ISDN_MSNLEN
)braket
suffix:semicolon
multiline_comment|/* Last phone-number              */
DECL|member|last_l2
r_int
r_char
id|last_l2
suffix:semicolon
multiline_comment|/* Last layer-2 protocol          */
DECL|member|last_si
r_int
r_char
id|last_si
suffix:semicolon
multiline_comment|/* Last service                   */
DECL|member|last_lhup
r_int
r_char
id|last_lhup
suffix:semicolon
multiline_comment|/* Last hangup local?             */
DECL|member|last_dir
r_int
r_char
id|last_dir
suffix:semicolon
multiline_comment|/* Last direction (in or out)     */
DECL|member|nc_timer
r_struct
id|timer_list
id|nc_timer
suffix:semicolon
multiline_comment|/* Timer for delayed NO CARRIER   */
DECL|member|send_outstanding
r_int
id|send_outstanding
suffix:semicolon
multiline_comment|/* # of outstanding send-requests */
DECL|member|xmit_size
r_int
id|xmit_size
suffix:semicolon
multiline_comment|/* max. # of chars in xmit_buf    */
DECL|member|xmit_count
r_int
id|xmit_count
suffix:semicolon
multiline_comment|/* # of chars in xmit_buf         */
DECL|member|xmit_buf
r_int
r_char
op_star
id|xmit_buf
suffix:semicolon
multiline_comment|/* transmit buffer                */
DECL|member|xmit_queue
r_struct
id|sk_buff_head
id|xmit_queue
suffix:semicolon
multiline_comment|/* transmit queue                 */
macro_line|#ifdef CONFIG_ISDN_AUDIO
DECL|member|vonline
r_int
id|vonline
suffix:semicolon
multiline_comment|/* Voice-channel status           */
multiline_comment|/* Bit 0 = recording              */
multiline_comment|/* Bit 1 = playback               */
multiline_comment|/* Bit 2 = playback, DLE-ETX seen */
DECL|member|dtmf_queue
r_struct
id|sk_buff_head
id|dtmf_queue
suffix:semicolon
multiline_comment|/* queue for dtmf results         */
DECL|member|adpcms
r_void
op_star
id|adpcms
suffix:semicolon
multiline_comment|/* state for adpcm decompression  */
DECL|member|adpcmr
r_void
op_star
id|adpcmr
suffix:semicolon
multiline_comment|/* state for adpcm compression    */
DECL|member|dtmf_state
r_void
op_star
id|dtmf_state
suffix:semicolon
multiline_comment|/* state for dtmf decoder         */
macro_line|#endif
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
multiline_comment|/* Pointer to corresponding tty   */
DECL|member|emu
id|atemu
id|emu
suffix:semicolon
multiline_comment|/* AT-emulator data               */
DECL|member|normal_termios
r_struct
id|termios
id|normal_termios
suffix:semicolon
multiline_comment|/* For saving termios structs     */
DECL|member|callout_termios
r_struct
id|termios
id|callout_termios
suffix:semicolon
DECL|member|open_wait
r_struct
id|wait_queue
op_star
id|open_wait
suffix:semicolon
DECL|member|close_wait
r_struct
id|wait_queue
op_star
id|close_wait
suffix:semicolon
DECL|typedef|modem_info
)brace
id|modem_info
suffix:semicolon
DECL|macro|ISDN_MODEM_WINSIZE
mdefine_line|#define ISDN_MODEM_WINSIZE 8
multiline_comment|/* Description of one ISDN-tty */
r_typedef
r_struct
(brace
DECL|member|refcount
r_int
id|refcount
suffix:semicolon
multiline_comment|/* Number of opens        */
DECL|member|tty_modem
r_struct
id|tty_driver
id|tty_modem
suffix:semicolon
multiline_comment|/* tty-device             */
DECL|member|cua_modem
r_struct
id|tty_driver
id|cua_modem
suffix:semicolon
multiline_comment|/* cua-device             */
DECL|member|modem_table
r_struct
id|tty_struct
op_star
id|modem_table
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* ?? copied from Orig */
DECL|member|modem_termios
r_struct
id|termios
op_star
id|modem_termios
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
DECL|member|modem_termios_locked
r_struct
id|termios
op_star
id|modem_termios_locked
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
DECL|member|info
id|modem_info
id|info
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* Private data           */
DECL|typedef|modem
)brace
id|modem
suffix:semicolon
multiline_comment|/*======================= End of ISDN-tty stuff ============================*/
multiline_comment|/*======================= Start of sync-ppp stuff ==========================*/
DECL|macro|NUM_RCV_BUFFS
mdefine_line|#define NUM_RCV_BUFFS     64
DECL|macro|PPP_HARD_HDR_LEN
mdefine_line|#define PPP_HARD_HDR_LEN 4
macro_line|#ifdef CONFIG_ISDN_PPP
DECL|struct|sqqueue
r_struct
id|sqqueue
(brace
DECL|member|next
r_struct
id|sqqueue
op_star
id|next
suffix:semicolon
DECL|member|sqno_start
r_int
id|sqno_start
suffix:semicolon
DECL|member|sqno_end
r_int
id|sqno_end
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|timer
r_int
id|timer
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mpqueue
r_struct
id|mpqueue
(brace
DECL|member|next
r_struct
id|mpqueue
op_star
id|next
suffix:semicolon
DECL|member|last
r_struct
id|mpqueue
op_star
id|last
suffix:semicolon
DECL|member|sqno
r_int
id|sqno
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|BEbyte
r_int
id|BEbyte
suffix:semicolon
DECL|member|time
r_int
r_int
id|time
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ippp_buf_queue
r_struct
id|ippp_buf_queue
(brace
DECL|member|next
r_struct
id|ippp_buf_queue
op_star
id|next
suffix:semicolon
DECL|member|last
r_struct
id|ippp_buf_queue
op_star
id|last
suffix:semicolon
DECL|member|buf
r_char
op_star
id|buf
suffix:semicolon
multiline_comment|/* NULL here indicates end of queue */
DECL|member|len
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ippp_struct
r_struct
id|ippp_struct
(brace
DECL|member|next_link
r_struct
id|ippp_struct
op_star
id|next_link
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|rq
r_struct
id|ippp_buf_queue
id|rq
(braket
id|NUM_RCV_BUFFS
)braket
suffix:semicolon
multiline_comment|/* packet queue for isdn_ppp_read() */
DECL|member|first
r_struct
id|ippp_buf_queue
op_star
id|first
suffix:semicolon
multiline_comment|/* pointer to (current) first packet */
DECL|member|last
r_struct
id|ippp_buf_queue
op_star
id|last
suffix:semicolon
multiline_comment|/* pointer to (current) last used packet in queue */
DECL|member|wq
r_struct
id|wait_queue
op_star
id|wq
suffix:semicolon
DECL|member|wq1
r_struct
id|wait_queue
op_star
id|wq1
suffix:semicolon
DECL|member|tk
r_struct
id|task_struct
op_star
id|tk
suffix:semicolon
DECL|member|mpppcfg
r_int
r_int
id|mpppcfg
suffix:semicolon
DECL|member|pppcfg
r_int
r_int
id|pppcfg
suffix:semicolon
DECL|member|mru
r_int
r_int
id|mru
suffix:semicolon
DECL|member|mpmru
r_int
r_int
id|mpmru
suffix:semicolon
DECL|member|mpmtu
r_int
r_int
id|mpmtu
suffix:semicolon
DECL|member|maxcid
r_int
r_int
id|maxcid
suffix:semicolon
DECL|member|lp
id|isdn_net_local
op_star
id|lp
suffix:semicolon
DECL|member|unit
r_int
id|unit
suffix:semicolon
DECL|member|minor
r_int
id|minor
suffix:semicolon
DECL|member|last_link_seqno
r_int
id|last_link_seqno
suffix:semicolon
DECL|member|mp_seqno
r_int
id|mp_seqno
suffix:semicolon
DECL|member|range
r_int
id|range
suffix:semicolon
macro_line|#ifdef CONFIG_ISDN_PPP_VJ
DECL|member|cbuf
r_int
r_char
op_star
id|cbuf
suffix:semicolon
DECL|member|slcomp
r_struct
id|slcompress
op_star
id|slcomp
suffix:semicolon
macro_line|#endif
DECL|member|debug
r_int
r_int
id|debug
suffix:semicolon
DECL|member|compressor
r_struct
id|isdn_ppp_compressor
op_star
id|compressor
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*======================== End of sync-ppp stuff ===========================*/
multiline_comment|/*======================= Start of general stuff ===========================*/
r_typedef
r_struct
(brace
DECL|member|next
r_char
op_star
id|next
suffix:semicolon
DECL|member|private
r_char
op_star
r_private
suffix:semicolon
DECL|typedef|infostruct
)brace
id|infostruct
suffix:semicolon
multiline_comment|/* Description of hardware-level-driver */
r_typedef
r_struct
(brace
DECL|member|flags
id|ulong
id|flags
suffix:semicolon
multiline_comment|/* Flags                            */
DECL|member|channels
r_int
id|channels
suffix:semicolon
multiline_comment|/* Number of channels               */
DECL|member|reject_bus
r_int
id|reject_bus
suffix:semicolon
multiline_comment|/* Flag: Reject rejected call on bus*/
DECL|member|st_waitq
r_struct
id|wait_queue
op_star
id|st_waitq
suffix:semicolon
multiline_comment|/* Wait-Queue for status-read&squot;s     */
DECL|member|maxbufsize
r_int
id|maxbufsize
suffix:semicolon
multiline_comment|/* Maximum Buffersize supported     */
DECL|member|pktcount
r_int
r_int
id|pktcount
suffix:semicolon
multiline_comment|/* Until now: unused                */
DECL|member|running
r_int
id|running
suffix:semicolon
multiline_comment|/* Flag: Protocolcode running       */
DECL|member|loaded
r_int
id|loaded
suffix:semicolon
multiline_comment|/* Flag: Driver loaded              */
DECL|member|stavail
r_int
id|stavail
suffix:semicolon
multiline_comment|/* Chars avail on Status-device     */
DECL|member|interface
id|isdn_if
op_star
id|interface
suffix:semicolon
multiline_comment|/* Interface to driver              */
DECL|member|rcverr
r_int
op_star
id|rcverr
suffix:semicolon
multiline_comment|/* Error-counters for B-Ch.-receive */
DECL|member|rcvcount
r_int
op_star
id|rcvcount
suffix:semicolon
multiline_comment|/* Byte-counters for B-Ch.-receive  */
macro_line|#ifdef CONFIG_ISDN_AUDIO
DECL|member|DLEflag
r_int
r_int
id|DLEflag
suffix:semicolon
multiline_comment|/* Flags: Insert DLE at next read   */
macro_line|#endif
DECL|member|rpqueue
r_struct
id|sk_buff_head
op_star
id|rpqueue
suffix:semicolon
multiline_comment|/* Pointers to start of Rcv-Queue   */
DECL|member|rcv_waitq
r_struct
id|wait_queue
op_star
op_star
id|rcv_waitq
suffix:semicolon
multiline_comment|/* Wait-Queues for B-Channel-Reads  */
DECL|member|snd_waitq
r_struct
id|wait_queue
op_star
op_star
id|snd_waitq
suffix:semicolon
multiline_comment|/* Wait-Queue for B-Channel-Send&squot;s  */
DECL|member|msn2eaz
r_char
id|msn2eaz
(braket
l_int|10
)braket
(braket
id|ISDN_MSNLEN
)braket
suffix:semicolon
multiline_comment|/* Mapping-Table MSN-&gt;EAZ   */
DECL|typedef|driver
)brace
id|driver
suffix:semicolon
multiline_comment|/* Main driver-data */
DECL|struct|isdn_devt
r_typedef
r_struct
id|isdn_devt
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Bitmapped Flags:           */
multiline_comment|/*                            */
DECL|member|drivers
r_int
id|drivers
suffix:semicolon
multiline_comment|/* Current number of drivers  */
DECL|member|channels
r_int
id|channels
suffix:semicolon
multiline_comment|/* Current number of channels */
DECL|member|net_verbose
r_int
id|net_verbose
suffix:semicolon
multiline_comment|/* Verbose-Flag               */
DECL|member|modempoll
r_int
id|modempoll
suffix:semicolon
multiline_comment|/* Flag: tty-read active      */
DECL|member|tflags
r_int
id|tflags
suffix:semicolon
multiline_comment|/* Timer-Flags:               */
multiline_comment|/*  see ISDN_TIMER_..defines  */
DECL|member|global_flags
r_int
id|global_flags
suffix:semicolon
DECL|member|infochain
id|infostruct
op_star
id|infochain
suffix:semicolon
multiline_comment|/* List of open info-devs.    */
DECL|member|info_waitq
r_struct
id|wait_queue
op_star
id|info_waitq
suffix:semicolon
multiline_comment|/* Wait-Queue for isdninfo    */
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* Misc.-function Timer       */
DECL|member|chanmap
r_int
id|chanmap
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* Map minor-&gt;device-channel  */
DECL|member|drvmap
r_int
id|drvmap
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* Map minor-&gt;driver-index    */
DECL|member|usage
r_int
id|usage
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* Used by tty/ip/voice       */
DECL|member|num
r_char
id|num
(braket
id|ISDN_MAX_CHANNELS
)braket
(braket
id|ISDN_MSNLEN
)braket
suffix:semicolon
multiline_comment|/* Remote number of active ch.*/
DECL|member|m_idx
r_int
id|m_idx
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* Index for mdm....          */
DECL|member|drv
id|driver
op_star
id|drv
(braket
id|ISDN_MAX_DRIVERS
)braket
suffix:semicolon
multiline_comment|/* Array of drivers           */
DECL|member|netdev
id|isdn_net_dev
op_star
id|netdev
suffix:semicolon
multiline_comment|/* Linked list of net-if&squot;s    */
DECL|member|drvid
r_char
id|drvid
(braket
id|ISDN_MAX_DRIVERS
)braket
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* Driver-ID                 */
DECL|member|profd
r_struct
id|task_struct
op_star
id|profd
suffix:semicolon
multiline_comment|/* For iprofd                 */
DECL|member|mdm
id|modem
id|mdm
suffix:semicolon
multiline_comment|/* tty-driver-data            */
DECL|member|rx_netdev
id|isdn_net_dev
op_star
id|rx_netdev
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* rx netdev-pointers     */
DECL|member|st_netdev
id|isdn_net_dev
op_star
id|st_netdev
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* stat netdev-pointers   */
DECL|member|ibytes
id|ulong
id|ibytes
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* Statistics incoming bytes  */
DECL|member|obytes
id|ulong
id|obytes
(braket
id|ISDN_MAX_CHANNELS
)braket
suffix:semicolon
multiline_comment|/* Statistics outgoing bytes  */
DECL|typedef|isdn_dev
)brace
id|isdn_dev
suffix:semicolon
r_extern
id|isdn_dev
op_star
id|dev
suffix:semicolon
multiline_comment|/* Utility-Macros */
DECL|macro|MIN
mdefine_line|#define MIN(a,b) ((a&lt;b)?a:b)
DECL|macro|MAX
mdefine_line|#define MAX(a,b) ((a&gt;b)?a:b)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* isdn_h */
eof
