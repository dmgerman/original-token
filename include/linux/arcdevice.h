multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  NET  is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the ARCnet handlers.&n; *&n; * Version:&t;@(#)arcdevice.h&t;1.0&t;31/07/97&n; *&n; * Authors:&t;Avery Pennarun &lt;apenwarr@bond.net&gt;&n; *              David Woodhouse &lt;dwmw2@cam.ac.uk&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#ifndef _LINUX_ARCDEVICE_H
DECL|macro|_LINUX_ARCDEVICE_H
mdefine_line|#define _LINUX_ARCDEVICE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/if_arcnet.h&gt;
macro_line|#ifdef __KERNEL__
DECL|macro|ARC_20020
mdefine_line|#define ARC_20020     1
DECL|macro|ARC_RIM_I
mdefine_line|#define ARC_RIM_I     2
DECL|macro|ARC_90xx
mdefine_line|#define ARC_90xx      3
DECL|macro|ARC_90xx_IO
mdefine_line|#define ARC_90xx_IO   4
DECL|macro|MAX_ARCNET_DEVS
mdefine_line|#define MAX_ARCNET_DEVS 8
multiline_comment|/* The card sends the reconfiguration signal when it loses the connection to&n; * the rest of its network. It is a &squot;Hello, is anybody there?&squot; cry.  This&n; * usually happens when a new computer on the network is powered on or when&n; * the cable is broken.&n; *&n; * Define DETECT_RECONFIGS if you want to detect network reconfigurations.&n; * Recons may be a real nuisance on a larger ARCnet network; if you are a&n; * network administrator you probably would like to count them.&n; * Reconfigurations will be recorded in stats.tx_carrier_errors (the last&n; * field of the /proc/net/dev file).&n; *&n; * Define SHOW_RECONFIGS if you really want to see a log message whenever&n; * a RECON occurs.&n; */
DECL|macro|DETECT_RECONFIGS
mdefine_line|#define DETECT_RECONFIGS
DECL|macro|SHOW_RECONFIGS
macro_line|#undef SHOW_RECONFIGS
multiline_comment|/* RECON_THRESHOLD is the maximum number of RECON messages to receive within&n; * one minute before printing a &quot;cabling problem&quot; warning.  You must have&n; * DETECT_RECONFIGS enabled if you want to use this.  The default value&n; * should be fine.&n; *&n; * After that, a &quot;cabling restored&quot; message will be printed on the next IRQ&n; * if no RECON messages have been received for 10 seconds.&n; *&n; * Do not define RECON_THRESHOLD at all if you want to disable this feature.&n; */
DECL|macro|RECON_THRESHOLD
mdefine_line|#define RECON_THRESHOLD 30
multiline_comment|/* Define this to the minimum &quot;timeout&quot; value.  If a transmit takes longer&n; * than TX_TIMEOUT jiffies, Linux will abort the TX and retry.  On a large&n; * network, or one with heavy network traffic, this timeout may need to be&n; * increased.  The larger it is, though, the longer it will be between&n; * necessary transmits - don&squot;t set this too large.&n; */
DECL|macro|TX_TIMEOUT
mdefine_line|#define TX_TIMEOUT 20
multiline_comment|/* New debugging bitflags: each option can be enabled individually.&n; *&n; * These can be set while the driver is running by typing:&n; *&t;ifconfig arc0 down metric 1xxx HOSTNAME&n; *&t;&t;where 1xxx is 1000 + the debug level you want&n; *&t;&t;and HOSTNAME is your hostname/ip address&n; * and then resetting your routes.&n; *&n; * An ioctl() should be used for this instead, someday.&n; *&n; * Note: only debug flags included in the ARCNET_DEBUG_MAX define will&n; *   actually be available.  GCC will (at least, GCC 2.7.0 will) notice&n; *   lines using a BUGLVL not in ARCNET_DEBUG_MAX and automatically optimize&n; *   them out.&n; */
DECL|macro|D_NORMAL
mdefine_line|#define D_NORMAL&t;1&t;/* important operational info&t;&t;*/
DECL|macro|D_EXTRA
mdefine_line|#define D_EXTRA&t;&t;2&t;/* useful, but non-vital information&t;*/
DECL|macro|D_INIT
mdefine_line|#define&t;D_INIT&t;&t;4&t;/* show init/probe messages&t;&t;*/
DECL|macro|D_INIT_REASONS
mdefine_line|#define D_INIT_REASONS&t;8&t;/* show reasons for discarding probes&t;*/
multiline_comment|/* debug levels below give LOTS of output during normal operation! */
DECL|macro|D_DURING
mdefine_line|#define D_DURING&t;16&t;/* trace operations (including irq&squot;s)&t;*/
DECL|macro|D_TX
mdefine_line|#define D_TX&t;&t;32&t;/* show tx packets&t;&t;&t;*/
DECL|macro|D_RX
mdefine_line|#define D_RX&t;&t;64&t;/* show rx packets&t;&t;&t;*/
DECL|macro|D_SKB
mdefine_line|#define D_SKB&t;&t;128&t;/* show skb&squot;s&t;&t;&t;&t;*/
macro_line|#ifndef ARCNET_DEBUG_MAX
DECL|macro|ARCNET_DEBUG_MAX
mdefine_line|#define ARCNET_DEBUG_MAX (~0)&t;&t;/* enable ALL debug messages&t; */
macro_line|#endif
macro_line|#ifndef ARCNET_DEBUG
DECL|macro|ARCNET_DEBUG
mdefine_line|#define ARCNET_DEBUG (D_NORMAL|D_EXTRA)
macro_line|#endif
r_extern
r_int
id|arcnet_debug
suffix:semicolon
multiline_comment|/* macros to simplify debug checking */
DECL|macro|BUGLVL
mdefine_line|#define BUGLVL(x) if ((ARCNET_DEBUG_MAX)&amp;arcnet_debug&amp;(x))
DECL|macro|BUGMSG2
mdefine_line|#define BUGMSG2(x,msg,args...) BUGLVL(x) printk(msg, ## args)
DECL|macro|BUGMSG
mdefine_line|#define BUGMSG(x,msg,args...) BUGMSG2(x,&quot;%s%6s: &quot; msg, &bslash;&n;            x==D_NORMAL&t;? KERN_WARNING : &bslash;&n;      x&lt;=D_INIT_REASONS&t;? KERN_INFO    : KERN_DEBUG , &bslash;&n;&t;dev-&gt;name , ## args)
DECL|macro|SETMASK
mdefine_line|#define SETMASK AINTMASK(lp-&gt;intmask)
multiline_comment|/* Time needed to resetthe card - in jiffies.  This works on my SMC&n;&t; * PC100.  I can&squot;t find a reference that tells me just how long I&n;&t; * should wait.&n;&t; */
DECL|macro|RESETtime
mdefine_line|#define RESETtime (HZ * 3 / 10)&t;&t;/* reset */
multiline_comment|/* these are the max/min lengths of packet data. (including&n;&t; * ClientData header)&n;&t; * note: packet sizes 250, 251, 252 are impossible (God knows why)&n;&t; *  so exception packets become necessary.&n;&t; *&n;&t; * These numbers are compared with the length of the full packet,&n;&t; * including ClientData header.&n;&t; */
DECL|macro|MTU
mdefine_line|#define MTU&t;253&t;/* normal packet max size */
DECL|macro|MinTU
mdefine_line|#define MinTU&t;257&t;/* extended packet min size */
DECL|macro|XMTU
mdefine_line|#define XMTU&t;508&t;/* extended packet max size */
multiline_comment|/* status/interrupt mask bit fields */
DECL|macro|TXFREEflag
mdefine_line|#define TXFREEflag&t;0x01            /* transmitter available */
DECL|macro|TXACKflag
mdefine_line|#define TXACKflag       0x02            /* transmitted msg. ackd */
DECL|macro|RECONflag
mdefine_line|#define RECONflag       0x04            /* system reconfigured */
DECL|macro|TESTflag
mdefine_line|#define TESTflag        0x08            /* test flag */
DECL|macro|RESETflag
mdefine_line|#define RESETflag       0x10            /* power-on-reset */
DECL|macro|RES1flag
mdefine_line|#define RES1flag        0x20            /* reserved - usually set by jumper */
DECL|macro|RES2flag
mdefine_line|#define RES2flag        0x40            /* reserved - usually set by jumper */
DECL|macro|NORXflag
mdefine_line|#define NORXflag        0x80            /* receiver inhibited */
multiline_comment|/* Flags used for IO-mapped memory operations */
DECL|macro|AUTOINCflag
mdefine_line|#define AUTOINCflag     0x40    /* Increase location with each access */
DECL|macro|IOMAPflag
mdefine_line|#define IOMAPflag       0x02    /* (for 90xx) Use IO mapped memory, not mmap */
DECL|macro|ENABLE16flag
mdefine_line|#define ENABLE16flag    0x80    /* (for 90xx) Enable 16-bit mode */
multiline_comment|/* in the command register, the following bits have these meanings:&n;        *                0-2     command&n;        *                3-4     page number (for enable rcv/xmt command)&n;        *                 7      receive broadcasts&n;        */
DECL|macro|NOTXcmd
mdefine_line|#define NOTXcmd         0x01            /* disable transmitter */
DECL|macro|NORXcmd
mdefine_line|#define NORXcmd         0x02            /* disable receiver */
DECL|macro|TXcmd
mdefine_line|#define TXcmd           0x03            /* enable transmitter */
DECL|macro|RXcmd
mdefine_line|#define RXcmd           0x04            /* enable receiver */
DECL|macro|CONFIGcmd
mdefine_line|#define CONFIGcmd       0x05            /* define configuration */
DECL|macro|CFLAGScmd
mdefine_line|#define CFLAGScmd       0x06            /* clear flags */
DECL|macro|TESTcmd
mdefine_line|#define TESTcmd         0x07            /* load test flags */
multiline_comment|/* flags for &quot;clear flags&quot; command */
DECL|macro|RESETclear
mdefine_line|#define RESETclear      0x08            /* power-on-reset */
DECL|macro|CONFIGclear
mdefine_line|#define CONFIGclear     0x10            /* system reconfigured */
multiline_comment|/* flags for &quot;load test flags&quot; command */
DECL|macro|TESTload
mdefine_line|#define TESTload        0x08            /* test flag (diagnostic) */
multiline_comment|/* byte deposited into first address of buffers on reset */
DECL|macro|TESTvalue
mdefine_line|#define TESTvalue       0321&t;&t; /* that&squot;s octal for 0xD1 :) */
multiline_comment|/* for &quot;enable receiver&quot; command */
DECL|macro|RXbcasts
mdefine_line|#define RXbcasts        0x80            /* receive broadcasts */
multiline_comment|/* flags for &quot;define configuration&quot; command */
DECL|macro|NORMALconf
mdefine_line|#define NORMALconf      0x00            /* 1-249 byte packets */
DECL|macro|EXTconf
mdefine_line|#define EXTconf         0x08            /* 250-504 byte packets */
multiline_comment|/* Starts receiving packets into recbuf.&n;&t; */
DECL|macro|EnableReceiver
mdefine_line|#define EnableReceiver()&t;ACOMMAND(RXcmd|(recbuf&lt;&lt;3)|RXbcasts)
DECL|macro|JIFFER
mdefine_line|#define JIFFER(time) for (delayval=jiffies+time; jiffies&lt;delayval;) ;
multiline_comment|/* a complete ARCnet packet */
DECL|union|ArcPacket
r_union
id|ArcPacket
(brace
DECL|member|hardheader
r_struct
id|archdr
id|hardheader
suffix:semicolon
multiline_comment|/* the hardware header */
DECL|member|raw
id|u_char
id|raw
(braket
l_int|512
)braket
suffix:semicolon
multiline_comment|/* raw packet info, incl ClientData */
)brace
suffix:semicolon
multiline_comment|/* the &quot;client data&quot; header - RFC1201 information&n;&t; * notice that this screws up if it&squot;s not an even number of bytes&n;&t; * &lt;sigh&gt;&n;&t; */
DECL|struct|ClientData
r_struct
id|ClientData
(brace
multiline_comment|/* data that&squot;s NOT part of real packet - we MUST get rid of it before&n;&t; * actually sending!!&n;&t; */
DECL|member|saddr
id|u_char
id|saddr
comma
multiline_comment|/* Source address - needed for IPX */
DECL|member|daddr
id|daddr
suffix:semicolon
multiline_comment|/* Destination address */
multiline_comment|/* data that IS part of real packet */
DECL|member|protocol_id
id|u_char
id|protocol_id
comma
multiline_comment|/* ARC_P_IP, ARC_P_ARP, etc */
DECL|member|split_flag
id|split_flag
suffix:semicolon
multiline_comment|/* for use with split packets */
DECL|member|sequence
id|u_short
id|sequence
suffix:semicolon
multiline_comment|/* sequence number */
)brace
suffix:semicolon
DECL|macro|EXTRA_CLIENTDATA
mdefine_line|#define EXTRA_CLIENTDATA (sizeof(struct ClientData)-4)
multiline_comment|/* the &quot;client data&quot; header - RFC1051 information&n;&t; * this also screws up if it&squot;s not an even number of bytes&n;&t; * &lt;sigh again&gt;&n;&t; */
DECL|struct|S_ClientData
r_struct
id|S_ClientData
(brace
multiline_comment|/* data that&squot;s NOT part of real packet - we MUST get rid of it before&n;&t; * actually sending!!&n;&t; */
DECL|member|saddr
id|u_char
id|saddr
comma
multiline_comment|/* Source address - needed for IPX */
DECL|member|daddr
id|daddr
comma
multiline_comment|/* Destination address */
DECL|member|junk
id|junk
suffix:semicolon
multiline_comment|/* padding to make an even length */
multiline_comment|/* data that IS part of real packet */
DECL|member|protocol_id
id|u_char
id|protocol_id
suffix:semicolon
multiline_comment|/* ARC_P_IP, ARC_P_ARP, etc */
)brace
suffix:semicolon
DECL|macro|S_EXTRA_CLIENTDATA
mdefine_line|#define S_EXTRA_CLIENTDATA (sizeof(struct S_ClientData)-1)
multiline_comment|/* &quot;Incoming&quot; is information needed for each address that could be sending&n; * to us.  Mostly for partially-received split packets.&n; */
DECL|struct|Incoming
r_struct
id|Incoming
(brace
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/* packet data buffer             */
DECL|member|lastpacket
r_int
r_char
id|lastpacket
comma
multiline_comment|/* number of last packet (from 1) */
DECL|member|numpackets
id|numpackets
suffix:semicolon
multiline_comment|/* number of packets in split     */
DECL|member|sequence
id|u_short
id|sequence
suffix:semicolon
multiline_comment|/* sequence number of assembly&t;  */
)brace
suffix:semicolon
DECL|struct|Outgoing
r_struct
id|Outgoing
(brace
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
multiline_comment|/* buffer from upper levels */
DECL|member|hdr
r_struct
id|ClientData
op_star
id|hdr
suffix:semicolon
multiline_comment|/* clientdata of last packet */
DECL|member|data
id|u_char
op_star
id|data
suffix:semicolon
multiline_comment|/* pointer to data in packet */
DECL|member|length
r_int
id|length
comma
multiline_comment|/* bytes total */
DECL|member|dataleft
id|dataleft
comma
multiline_comment|/* bytes left */
DECL|member|segnum
id|segnum
comma
multiline_comment|/* segment being sent */
DECL|member|numsegs
id|numsegs
comma
multiline_comment|/* number of segments */
DECL|member|seglen
id|seglen
suffix:semicolon
multiline_comment|/* length of segment */
)brace
suffix:semicolon
DECL|struct|arcnet_local
r_struct
id|arcnet_local
(brace
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|sequence
id|u_short
id|sequence
suffix:semicolon
multiline_comment|/* sequence number (incs with each packet) */
DECL|member|aborted_seq
id|u_short
id|aborted_seq
suffix:semicolon
DECL|member|stationid
id|u_char
id|stationid
comma
multiline_comment|/* our 8-bit station address */
DECL|member|recbuf
id|recbuf
comma
multiline_comment|/* receive buffer # (0 or 1) */
DECL|member|txbuf
id|txbuf
comma
multiline_comment|/* transmit buffer # (2 or 3) */
DECL|member|txready
id|txready
comma
multiline_comment|/* buffer where a packet is ready to send */
DECL|member|config
id|config
comma
multiline_comment|/* current value of CONFIG register */
DECL|member|timeout
id|timeout
comma
multiline_comment|/* Extended timeout for COM20020 */
DECL|member|backplane
id|backplane
comma
multiline_comment|/* Backplane flag for COM20020 */
DECL|member|setup
id|setup
comma
multiline_comment|/* Contents of setup register */
DECL|member|intmask
id|intmask
suffix:semicolon
multiline_comment|/* current value of INTMASK register */
DECL|member|intx
r_int
id|intx
comma
multiline_comment|/* in TX routine? */
DECL|member|in_txhandler
id|in_txhandler
comma
multiline_comment|/* in TX_IRQ handler? */
DECL|member|sending
id|sending
comma
multiline_comment|/* transmit in progress? */
DECL|member|lastload_dest
id|lastload_dest
comma
multiline_comment|/* can last loaded packet be acked? */
DECL|member|lasttrans_dest
id|lasttrans_dest
suffix:semicolon
multiline_comment|/* can last TX&squot;d packet be acked? */
macro_line|#if defined(DETECT_RECONFIGS) &amp;&amp; defined(RECON_THRESHOLD)
DECL|member|first_recon
id|time_t
id|first_recon
comma
multiline_comment|/* time of &quot;first&quot; RECON message to count */
DECL|member|last_recon
id|last_recon
suffix:semicolon
multiline_comment|/* time of most recent RECON */
DECL|member|num_recons
r_int
id|num_recons
comma
multiline_comment|/* number of RECONs between first and last. */
DECL|member|network_down
id|network_down
suffix:semicolon
multiline_comment|/* do we think the network is down? */
macro_line|#endif
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
multiline_comment|/* the timer interrupt struct */
DECL|member|incoming
r_struct
id|Incoming
id|incoming
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* one from each address */
DECL|member|outgoing
r_struct
id|Outgoing
id|outgoing
suffix:semicolon
multiline_comment|/* packet currently being sent */
DECL|member|card_type
r_int
id|card_type
suffix:semicolon
DECL|member|card_type_str
r_char
op_star
id|card_type_str
suffix:semicolon
DECL|member|inthandler
r_void
(paren
op_star
id|inthandler
)paren
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|arcnet_reset
r_int
(paren
op_star
id|arcnet_reset
)paren
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|reset_delay
)paren
suffix:semicolon
DECL|member|asetmask
r_void
(paren
op_star
id|asetmask
)paren
(paren
r_struct
id|device
op_star
id|dev
comma
id|u_char
id|mask
)paren
suffix:semicolon
DECL|member|acommand
r_void
(paren
op_star
id|acommand
)paren
(paren
r_struct
id|device
op_star
id|dev
comma
id|u_char
id|command
)paren
suffix:semicolon
DECL|member|astatus
id|u_char
(paren
op_star
id|astatus
)paren
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|en_dis_able_TX
r_void
(paren
op_star
id|en_dis_able_TX
)paren
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|enable
)paren
suffix:semicolon
DECL|member|prepare_tx
r_void
(paren
op_star
id|prepare_tx
)paren
(paren
r_struct
id|device
op_star
id|dev
comma
id|u_char
op_star
id|hdr
comma
r_int
id|hdrlen
comma
r_char
op_star
id|data
comma
r_int
id|length
comma
r_int
id|daddr
comma
r_int
id|exceptA
comma
r_int
id|offset
)paren
suffix:semicolon
DECL|member|openclose_device
r_void
(paren
op_star
id|openclose_device
)paren
(paren
r_int
id|open
)paren
suffix:semicolon
DECL|member|adev
r_struct
id|device
op_star
id|adev
suffix:semicolon
multiline_comment|/* RFC1201 protocol device */
multiline_comment|/* These are last to ensure that the chipset drivers don&squot;t depend on the&n;   * CONFIG_ARCNET_ETH and CONFIG_ARCNET_1051 options. &n;   */
macro_line|#ifdef CONFIG_ARCNET_ETH
DECL|member|edev
r_struct
id|device
op_star
id|edev
suffix:semicolon
multiline_comment|/* Ethernet-Encap device */
macro_line|#endif
macro_line|#ifdef CONFIG_ARCNET_1051
DECL|member|sdev
r_struct
id|device
op_star
id|sdev
suffix:semicolon
multiline_comment|/* RFC1051 protocol device */
macro_line|#endif
)brace
suffix:semicolon
macro_line|#endif  /* __KERNEL__ */
macro_line|#endif&t;/* _LINUX_ARCDEVICE_H */
eof
