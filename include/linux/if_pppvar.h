multiline_comment|/*&t;From: if_pppvar.h,v 1.2 1995/06/12 11:36:51 paulus Exp */
multiline_comment|/*&n; * if_pppvar.h - private structures and declarations for PPP.&n; *&n; * Copyright (c) 1994 The Australian National University.&n; * All rights reserved.&n; *&n; * Permission to use, copy, modify, and distribute this software and its&n; * documentation is hereby granted, provided that the above copyright&n; * notice appears in all copies.  This software is provided without any&n; * warranty, express or implied. The Australian National University&n; * makes no representations about the suitability of this software for&n; * any purpose.&n; *&n; * IN NO EVENT SHALL THE AUSTRALIAN NATIONAL UNIVERSITY BE LIABLE TO ANY&n; * PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES&n; * ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF&n; * THE AUSTRALIAN NATIONAL UNIVERSITY HAVE BEEN ADVISED OF THE POSSIBILITY&n; * OF SUCH DAMAGE.&n; *&n; * THE AUSTRALIAN NATIONAL UNIVERSITY SPECIFICALLY DISCLAIMS ANY WARRANTIES,&n; * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY&n; * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS&n; * ON AN &quot;AS IS&quot; BASIS, AND THE AUSTRALIAN NATIONAL UNIVERSITY HAS NO&n; * OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS,&n; * OR MODIFICATIONS.&n; *&n; * Copyright (c) 1989 Carnegie Mellon University.&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms are permitted&n; * provided that the above copyright notice and this paragraph are&n; * duplicated in all such forms and that any documentation,&n; * advertising materials, and other materials related to such&n; * distribution and use acknowledge that the software was developed&n; * by Carnegie Mellon University.  The name of the&n; * University may not be used to endorse or promote products derived&n; * from this software without specific prior written permission.&n; * THIS SOFTWARE IS PROVIDED ``AS IS&squot;&squot; AND WITHOUT ANY EXPRESS OR&n; * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED&n; * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.&n; */
multiline_comment|/*&n; *  ==FILEVERSION 971001==&n; *&n; *  NOTE TO MAINTAINERS:&n; *     If you modify this file at all, please set the above date.&n; *     if_pppvar.h is shipped with a PPP distribution as well as with the kernel;&n; *     if everyone increases the FILEVERSION number above, then scripts&n; *     can do the right thing when deciding whether to install a new if_pppvar.h&n; *     file.  Don&squot;t change the format of that line otherwise, so the&n; *     installation script can recognize it.&n; */
multiline_comment|/*&n; * Supported network protocols.  These values are used for&n; * indexing sc_npmode.&n; */
DECL|macro|NP_IP
mdefine_line|#define NP_IP&t;0&t;&t;/* Internet Protocol */
DECL|macro|NUM_NP
mdefine_line|#define NUM_NP&t;1&t;&t;/* Number of NPs. */
multiline_comment|/*&n; * Buffers for the PPP process have the following structure&n; */
DECL|macro|RBUFSIZE
mdefine_line|#define RBUFSIZE  2048&t;&t; /* MUST be a power of 2 and be &lt;= 4095 */
DECL|struct|ppp_buffer
r_struct
id|ppp_buffer
(brace
DECL|member|size
id|__s32
id|size
suffix:semicolon
multiline_comment|/* Size of the buffer area&t;*/
DECL|member|count
id|__s32
id|count
suffix:semicolon
multiline_comment|/* Count of characters in bufr&t;*/
DECL|member|head
id|__s32
id|head
suffix:semicolon
multiline_comment|/* index to head of list&t;*/
DECL|member|tail
id|__s32
id|tail
suffix:semicolon
multiline_comment|/* index to tail of list&t;*/
DECL|member|locked
r_int
r_int
id|locked
suffix:semicolon
multiline_comment|/* Buffer is being sent&t;&t;*/
DECL|member|type
id|__s32
id|type
suffix:semicolon
multiline_comment|/* Type of the buffer&t;&t;*/
multiline_comment|/* =0, device read buffer&t;*/
multiline_comment|/* =1, device write buffer&t;*/
multiline_comment|/* =2, daemon write buffer&t;*/
multiline_comment|/* =3, daemon read buffer&t;*/
DECL|member|fcs
id|__u16
id|fcs
suffix:semicolon
multiline_comment|/* Frame Check Sequence (CRC)&t;*/
DECL|member|magic
id|__u16
id|magic
suffix:semicolon
multiline_comment|/* Extra space if needed&t;*/
)brace
suffix:semicolon
multiline_comment|/* Given a pointer to the ppp_buffer then return base address of buffer */
DECL|macro|buf_base
mdefine_line|#define buf_base(buf) ((__u8 *) (&amp;buf[1]))
multiline_comment|/*&n; * Structure describing each ppp unit.&n; */
DECL|struct|ppp
r_struct
id|ppp
(brace
DECL|member|magic
id|__s32
id|magic
suffix:semicolon
multiline_comment|/* magic value for structure&t;*/
DECL|member|next
r_struct
id|ppp
op_star
id|next
suffix:semicolon
multiline_comment|/* unit with next index&t;&t;*/
multiline_comment|/* Bitmapped flag fields. */
DECL|member|inuse
r_int
r_int
id|inuse
suffix:semicolon
multiline_comment|/* are we allocated?&t;&t;*/
DECL|member|escape
id|__u8
id|escape
suffix:semicolon
multiline_comment|/* 0x20 if prev char was PPP_ESC*/
DECL|member|toss
id|__u8
id|toss
suffix:semicolon
multiline_comment|/* toss this frame&t;&t;*/
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
multiline_comment|/* miscellany&t;&t;&t;*/
DECL|member|xmit_async_map
id|__u32
id|xmit_async_map
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 1 bit means that given control &n;&t;&t;&t;&t;&t;   character is quoted on output*/
DECL|member|recv_async_map
id|__u32
id|recv_async_map
suffix:semicolon
multiline_comment|/* 1 bit means that given control &n;&t;&t;&t;&t;&t;   character is ignored on input*/
DECL|member|mtu
id|__s32
id|mtu
suffix:semicolon
multiline_comment|/* maximum xmit frame size&t;*/
DECL|member|mru
id|__s32
id|mru
suffix:semicolon
multiline_comment|/* maximum receive frame size&t;*/
multiline_comment|/* Information about the current tty data */
DECL|member|line
id|__s32
id|line
suffix:semicolon
multiline_comment|/* PPP channel number&t;*/
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
multiline_comment|/* ptr to TTY structure&t;*/
DECL|member|backup_tty
r_struct
id|tty_struct
op_star
id|backup_tty
suffix:semicolon
multiline_comment|/* TTY to use if tty gets closed */
DECL|member|bytes_sent
id|__s32
id|bytes_sent
suffix:semicolon
multiline_comment|/* Bytes sent on frame&t;*/
DECL|member|bytes_rcvd
id|__s32
id|bytes_rcvd
suffix:semicolon
multiline_comment|/* Bytes recvd on frame&t;*/
multiline_comment|/* VJ Header compression data */
DECL|member|slcomp
r_struct
id|slcompress
op_star
id|slcomp
suffix:semicolon
multiline_comment|/* for header compression&t;*/
multiline_comment|/* Transmission information */
DECL|member|xbuf
r_struct
id|ppp_buffer
op_star
id|xbuf
suffix:semicolon
multiline_comment|/* Buffer currently being sent&t;*/
DECL|member|s1buf
r_struct
id|ppp_buffer
op_star
id|s1buf
suffix:semicolon
multiline_comment|/* Pointer to daemon buffer&t;*/
DECL|member|s2buf
r_struct
id|ppp_buffer
op_star
id|s2buf
suffix:semicolon
multiline_comment|/* Pointer to device buffer&t;*/
DECL|member|last_xmit
r_int
r_int
id|last_xmit
suffix:semicolon
multiline_comment|/* time of last transmission&t;*/
DECL|member|last_recv
r_int
r_int
id|last_recv
suffix:semicolon
multiline_comment|/* time last packet received    */
multiline_comment|/* These are pointers to the malloc()ed frame buffers.&n;     These buffers are used while processing a packet.&t;If a packet&n;     has to hang around for the user process to read it, it lingers in&n;     the user buffers below. */
DECL|member|wbuf
r_struct
id|ppp_buffer
op_star
id|wbuf
suffix:semicolon
multiline_comment|/* Transmission information&t;*/
DECL|member|tbuf
r_struct
id|ppp_buffer
op_star
id|tbuf
suffix:semicolon
multiline_comment|/* daemon transmission buffer&t;*/
DECL|member|rbuf
r_struct
id|ppp_buffer
op_star
id|rbuf
suffix:semicolon
multiline_comment|/* Receive information&t;*/
DECL|member|ubuf
r_struct
id|ppp_buffer
op_star
id|ubuf
suffix:semicolon
multiline_comment|/* User buffer information&t;*/
DECL|member|cbuf
r_struct
id|ppp_buffer
op_star
id|cbuf
suffix:semicolon
multiline_comment|/* compression buffer&t;&t;*/
multiline_comment|/* Queues for select() functionality */
DECL|member|write_wait
r_struct
id|wait_queue
op_star
id|write_wait
suffix:semicolon
multiline_comment|/* queue for reading processes */
DECL|member|read_wait
r_struct
id|wait_queue
op_star
id|read_wait
suffix:semicolon
multiline_comment|/* queue for writing processes */
multiline_comment|/* Statistic information */
DECL|member|stats
r_struct
id|pppstat
id|stats
suffix:semicolon
multiline_comment|/* statistic information&t;*/
multiline_comment|/* PPP compression protocol information */
DECL|member|sc_bytessent
id|__u32
id|sc_bytessent
suffix:semicolon
multiline_comment|/* count of octets sent */
DECL|member|sc_bytesrcvd
id|__u32
id|sc_bytesrcvd
suffix:semicolon
multiline_comment|/* count of octets received */
DECL|member|sc_npmode
r_enum
id|NPmode
id|sc_npmode
(braket
id|NUM_NP
)braket
suffix:semicolon
multiline_comment|/* what to do with each NP */
DECL|member|sc_xcomp
r_struct
id|compressor
op_star
id|sc_xcomp
suffix:semicolon
multiline_comment|/* transmit compressor */
DECL|member|sc_xc_state
r_void
op_star
id|sc_xc_state
suffix:semicolon
multiline_comment|/* transmit compressor state */
DECL|member|sc_rcomp
r_struct
id|compressor
op_star
id|sc_rcomp
suffix:semicolon
multiline_comment|/* receive decompressor */
DECL|member|sc_rc_state
r_void
op_star
id|sc_rc_state
suffix:semicolon
multiline_comment|/* receive decompressor state */
DECL|member|sc_xfer
id|__s32
id|sc_xfer
suffix:semicolon
multiline_comment|/* PID of reserved PPP table */
DECL|member|name
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
multiline_comment|/* net device structure */
DECL|member|estats
r_struct
id|enet_statistics
id|estats
suffix:semicolon
multiline_comment|/* more detailed stats */
)brace
suffix:semicolon
eof
