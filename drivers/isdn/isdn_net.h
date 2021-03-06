multiline_comment|/* $Id: isdn_net.h,v 1.19 2000/06/21 09:54:29 keil Exp $&n;&n; * header for Linux ISDN subsystem, network related functions (linklevel).&n; *&n; * Copyright 1994-1999  by Fritz Elfert (fritz@isdn4linux.de)&n; * Copyright 1995,96    by Thinking Objects Software GmbH Wuerzburg&n; * Copyright 1995,96    by Michael Hipp (Michael.Hipp@student.uni-tuebingen.de)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
multiline_comment|/* Definitions for hupflags:                */
DECL|macro|ISDN_WAITCHARGE
mdefine_line|#define ISDN_WAITCHARGE  1      /* did not get a charge info yet            */
DECL|macro|ISDN_HAVECHARGE
mdefine_line|#define ISDN_HAVECHARGE  2      /* We know a charge info                    */
DECL|macro|ISDN_CHARGEHUP
mdefine_line|#define ISDN_CHARGEHUP   4      /* We want to use the charge mechanism      */
DECL|macro|ISDN_INHUP
mdefine_line|#define ISDN_INHUP       8      /* Even if incoming, close after huptimeout */
DECL|macro|ISDN_MANCHARGE
mdefine_line|#define ISDN_MANCHARGE  16      /* Charge Interval manually set             */
multiline_comment|/*&n; * Definitions for Cisco-HDLC header.&n; */
DECL|struct|cisco_hdr
r_typedef
r_struct
id|cisco_hdr
(brace
DECL|member|addr
id|__u8
id|addr
suffix:semicolon
multiline_comment|/* unicast/broadcast */
DECL|member|ctrl
id|__u8
id|ctrl
suffix:semicolon
multiline_comment|/* Always 0          */
DECL|member|type
id|__u16
id|type
suffix:semicolon
multiline_comment|/* IP-typefield      */
DECL|typedef|cisco_hdr
)brace
id|cisco_hdr
suffix:semicolon
DECL|struct|cisco_slarp
r_typedef
r_struct
id|cisco_slarp
(brace
DECL|member|code
id|__u32
id|code
suffix:semicolon
multiline_comment|/* SLREQ/SLREPLY/KEEPALIVE */
r_union
(brace
r_struct
(brace
DECL|member|ifaddr
id|__u32
id|ifaddr
suffix:semicolon
multiline_comment|/* My interface address     */
DECL|member|netmask
id|__u32
id|netmask
suffix:semicolon
multiline_comment|/* My interface netmask     */
DECL|member|reply
)brace
id|reply
suffix:semicolon
r_struct
(brace
DECL|member|my_seq
id|__u32
id|my_seq
suffix:semicolon
multiline_comment|/* Packet sequence number   */
DECL|member|your_seq
id|__u32
id|your_seq
suffix:semicolon
DECL|member|keepalive
)brace
id|keepalive
suffix:semicolon
DECL|member|slarp
)brace
id|slarp
suffix:semicolon
DECL|member|rel
id|__u16
id|rel
suffix:semicolon
multiline_comment|/* Always 0xffff            */
DECL|member|t1
id|__u16
id|t1
suffix:semicolon
multiline_comment|/* Uptime in usec &gt;&gt; 16     */
DECL|member|t0
id|__u16
id|t0
suffix:semicolon
multiline_comment|/* Uptime in usec &amp; 0xffff  */
DECL|typedef|cisco_slarp
)brace
id|cisco_slarp
suffix:semicolon
DECL|macro|CISCO_ADDR_UNICAST
mdefine_line|#define CISCO_ADDR_UNICAST    0x0f
DECL|macro|CISCO_ADDR_BROADCAST
mdefine_line|#define CISCO_ADDR_BROADCAST  0x8f
DECL|macro|CISCO_TYPE_INET
mdefine_line|#define CISCO_TYPE_INET       0x0800
DECL|macro|CISCO_TYPE_SLARP
mdefine_line|#define CISCO_TYPE_SLARP      0x8035
DECL|macro|CISCO_SLARP_REPLY
mdefine_line|#define CISCO_SLARP_REPLY     0
DECL|macro|CISCO_SLARP_REQUEST
mdefine_line|#define CISCO_SLARP_REQUEST   1
DECL|macro|CISCO_SLARP_KEEPALIVE
mdefine_line|#define CISCO_SLARP_KEEPALIVE 2
r_extern
r_char
op_star
id|isdn_net_new
c_func
(paren
r_char
op_star
comma
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_char
op_star
id|isdn_net_newslave
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_net_rm
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_net_rmall
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|isdn_net_stat_callback
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
id|isdn_net_setcfg
c_func
(paren
id|isdn_net_ioctl_cfg
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_net_getcfg
c_func
(paren
id|isdn_net_ioctl_cfg
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_net_addphone
c_func
(paren
id|isdn_net_ioctl_phone
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_net_getphones
c_func
(paren
id|isdn_net_ioctl_phone
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_net_getpeer
c_func
(paren
id|isdn_net_ioctl_phone
op_star
comma
id|isdn_net_ioctl_phone
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_net_delphone
c_func
(paren
id|isdn_net_ioctl_phone
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_net_find_icall
c_func
(paren
r_int
comma
r_int
comma
r_int
comma
id|setup_parm
op_star
)paren
suffix:semicolon
r_extern
r_void
id|isdn_net_hangup
c_func
(paren
r_struct
id|net_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|isdn_net_dial
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|isdn_net_autohup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|isdn_net_force_hangup
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_net_force_dial
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
id|isdn_net_dev
op_star
id|isdn_net_findif
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_net_rcv_skb
c_func
(paren
r_int
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_void
id|isdn_net_slarp_out
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|isdn_net_dial_req
c_func
(paren
id|isdn_net_local
op_star
)paren
suffix:semicolon
r_extern
r_void
id|isdn_net_writebuf_skb
c_func
(paren
id|isdn_net_local
op_star
id|lp
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_extern
r_void
id|isdn_net_write_super
c_func
(paren
id|isdn_net_local
op_star
id|lp
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
DECL|macro|ISDN_NET_MAX_QUEUE_LENGTH
mdefine_line|#define ISDN_NET_MAX_QUEUE_LENGTH 2
multiline_comment|/*&n; * is this particular channel busy?&n; */
DECL|function|isdn_net_lp_busy
r_static
id|__inline__
r_int
id|isdn_net_lp_busy
c_func
(paren
id|isdn_net_local
op_star
id|lp
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|lp-&gt;frame_cnt
)paren
OL
id|ISDN_NET_MAX_QUEUE_LENGTH
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * For the given net device, this will get a non-busy channel out of the&n; * corresponding bundle. The returned channel is locked.&n; */
DECL|function|isdn_net_get_locked_lp
r_static
id|__inline__
id|isdn_net_local
op_star
id|isdn_net_get_locked_lp
c_func
(paren
id|isdn_net_dev
op_star
id|nd
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|isdn_net_local
op_star
id|lp
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|nd-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
id|lp
op_assign
id|nd-&gt;queue
suffix:semicolon
multiline_comment|/* get lp on top of queue */
id|spin_lock_bh
c_func
(paren
op_amp
id|nd-&gt;queue-&gt;xmit_lock
)paren
suffix:semicolon
r_while
c_loop
(paren
id|isdn_net_lp_busy
c_func
(paren
id|nd-&gt;queue
)paren
)paren
(brace
id|spin_unlock_bh
c_func
(paren
op_amp
id|nd-&gt;queue-&gt;xmit_lock
)paren
suffix:semicolon
id|nd-&gt;queue
op_assign
id|nd-&gt;queue-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|nd-&gt;queue
op_eq
id|lp
)paren
(brace
multiline_comment|/* not found -- should never happen */
id|lp
op_assign
l_int|NULL
suffix:semicolon
r_goto
id|errout
suffix:semicolon
)brace
id|spin_lock_bh
c_func
(paren
op_amp
id|nd-&gt;queue-&gt;xmit_lock
)paren
suffix:semicolon
)brace
id|lp
op_assign
id|nd-&gt;queue
suffix:semicolon
id|nd-&gt;queue
op_assign
id|nd-&gt;queue-&gt;next
suffix:semicolon
id|errout
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|nd-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|lp
suffix:semicolon
)brace
multiline_comment|/*&n; * add a channel to a bundle&n; */
DECL|function|isdn_net_add_to_bundle
r_static
id|__inline__
r_void
id|isdn_net_add_to_bundle
c_func
(paren
id|isdn_net_dev
op_star
id|nd
comma
id|isdn_net_local
op_star
id|nlp
)paren
(brace
id|isdn_net_local
op_star
id|lp
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|nd-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
id|lp
op_assign
id|nd-&gt;queue
suffix:semicolon
id|nlp-&gt;last
op_assign
id|lp-&gt;last
suffix:semicolon
id|lp-&gt;last-&gt;next
op_assign
id|nlp
suffix:semicolon
id|lp-&gt;last
op_assign
id|nlp
suffix:semicolon
id|nlp-&gt;next
op_assign
id|lp
suffix:semicolon
id|nd-&gt;queue
op_assign
id|nlp
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|nd-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * remove a channel from the bundle it belongs to&n; */
DECL|function|isdn_net_rm_from_bundle
r_static
id|__inline__
r_void
id|isdn_net_rm_from_bundle
c_func
(paren
id|isdn_net_local
op_star
id|lp
)paren
(brace
id|isdn_net_local
op_star
id|master_lp
op_assign
id|lp
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;master
)paren
id|master_lp
op_assign
(paren
id|isdn_net_local
op_star
)paren
id|lp-&gt;master-&gt;priv
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|master_lp-&gt;netdev-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
id|lp-&gt;last-&gt;next
op_assign
id|lp-&gt;next
suffix:semicolon
id|lp-&gt;next-&gt;last
op_assign
id|lp-&gt;last
suffix:semicolon
r_if
c_cond
(paren
id|master_lp-&gt;netdev-&gt;queue
op_eq
id|lp
)paren
id|master_lp-&gt;netdev-&gt;queue
op_assign
id|lp-&gt;next
suffix:semicolon
id|lp-&gt;next
op_assign
id|lp-&gt;last
op_assign
id|lp
suffix:semicolon
multiline_comment|/* (re)set own pointers */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|master_lp-&gt;netdev-&gt;queue_lock
comma
id|flags
)paren
suffix:semicolon
)brace
eof
