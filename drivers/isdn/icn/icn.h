multiline_comment|/* $Id: icn.h,v 1.12 1996/01/22 05:01:22 fritz Exp fritz $&n; *&n; * ISDN lowlevel-module for the ICN active ISDN-Card.&n; *&n; * Copyright 1994 by Fritz Elfert (fritz@wuemaus.franken.de)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n; *&n; * $Log: icn.h,v $&n; * Revision 1.12  1996/01/22 05:01:22  fritz&n; * Revert to GPL.&n; *&n; * Revision 1.11  1995/12/18  18:25:00  fritz&n; * Support for ICN-2B Cards.&n; * Change for supporting user-setable service-octet.&n; *&n; * Revision 1.10  1995/10/29  21:43:10  fritz&n; * Added support for leased lines.&n; *&n; * Revision 1.9  1995/04/23  13:42:10  fritz&n; * Added some constants for distingushing 1TR6 and DSS1&n; *&n; * Revision 1.8  1995/03/25  23:18:55  fritz&n; * Changed ICN_PORTLEN to reflect correct number of ports.&n; *&n; * Revision 1.7  1995/03/15  12:52:06  fritz&n; * Some cleanup&n; *&n; * Revision 1.6  1995/02/20  03:49:22  fritz&n; * Fixed ICN_MAX_SQUEUE to correctly reflect outstanding bytes, not number&n; * of buffers.&n; *&n; * Revision 1.5  1995/01/29  23:36:50  fritz&n; * Minor cleanup.&n; *&n; * Revision 1.4  1995/01/09  07:41:20  fritz&n; * Added GPL-Notice&n; *&n; * Revision 1.3  1995/01/04  05:14:20  fritz&n; * removed include of linux/asm/string.h for compiling with Linux 1.1.76&n; *&n; * Revision 1.2  1995/01/02  02:15:57  fritz&n; * Misc. Bugfixes&n; *&n; * Revision 1.1  1994/12/14  18:02:38  fritz&n; * Initial revision&n; *&n; */
macro_line|#ifndef icn_h
DECL|macro|icn_h
mdefine_line|#define icn_h
DECL|macro|ICN_IOCTL_SETMMIO
mdefine_line|#define ICN_IOCTL_SETMMIO   0
DECL|macro|ICN_IOCTL_GETMMIO
mdefine_line|#define ICN_IOCTL_GETMMIO   1
DECL|macro|ICN_IOCTL_SETPORT
mdefine_line|#define ICN_IOCTL_SETPORT   2
DECL|macro|ICN_IOCTL_GETPORT
mdefine_line|#define ICN_IOCTL_GETPORT   3
DECL|macro|ICN_IOCTL_LOADBOOT
mdefine_line|#define ICN_IOCTL_LOADBOOT  4
DECL|macro|ICN_IOCTL_LOADPROTO
mdefine_line|#define ICN_IOCTL_LOADPROTO 5
DECL|macro|ICN_IOCTL_LEASEDCFG
mdefine_line|#define ICN_IOCTL_LEASEDCFG 6
DECL|macro|ICN_IOCTL_GETDOUBLE
mdefine_line|#define ICN_IOCTL_GETDOUBLE 7
DECL|macro|ICN_IOCTL_DEBUGVAR
mdefine_line|#define ICN_IOCTL_DEBUGVAR  8
macro_line|#if defined(__KERNEL__) || defined(__DEBUGVAR__)
macro_line|#ifdef __KERNEL__
multiline_comment|/* Kernel includes */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/isdnif.h&gt;
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
multiline_comment|/* some useful macros for debugging */
macro_line|#ifdef ICN_DEBUG_PORT
DECL|macro|OUTB_P
mdefine_line|#define OUTB_P(v,p) {printk(KERN_DEBUG &quot;icn: outb_p(0x%02x,0x%03x)&bslash;n&quot;,v,p); outb_p(v,p);}
macro_line|#else
DECL|macro|OUTB_P
mdefine_line|#define OUTB_P outb
macro_line|#endif
multiline_comment|/* Defaults for Port-Address and shared-memory */
DECL|macro|ICN_BASEADDR
mdefine_line|#define ICN_BASEADDR 0x320
DECL|macro|ICN_PORTLEN
mdefine_line|#define ICN_PORTLEN (0x04)
DECL|macro|ICN_MEMADDR
mdefine_line|#define ICN_MEMADDR 0x0d0000
multiline_comment|/* Macros for accessing ports */
DECL|macro|ICN_CFG
mdefine_line|#define ICN_CFG    (dev-&gt;port)
DECL|macro|ICN_MAPRAM
mdefine_line|#define ICN_MAPRAM (dev-&gt;port+1)
DECL|macro|ICN_RUN
mdefine_line|#define ICN_RUN    (dev-&gt;port+2)
DECL|macro|ICN_BANK
mdefine_line|#define ICN_BANK   (dev-&gt;port+3)
DECL|macro|ICN_FLAGS_B1ACTIVE
mdefine_line|#define ICN_FLAGS_B1ACTIVE 1&t;/* B-Channel-1 is open                 */
DECL|macro|ICN_FLAGS_B2ACTIVE
mdefine_line|#define ICN_FLAGS_B2ACTIVE 2&t;/* B-Channel-2 is open                 */
DECL|macro|ICN_FLAGS_RBTIMER
mdefine_line|#define ICN_FLAGS_RBTIMER  8&t;/* cyclic scheduling of B-Channel-poll */
DECL|macro|ICN_BOOT_TIMEOUT1
mdefine_line|#define ICN_BOOT_TIMEOUT1  100&t;/* Delay for Boot-download (jiffies)   */
DECL|macro|ICN_CHANLOCK_DELAY
mdefine_line|#define ICN_CHANLOCK_DELAY  10&t;/* Delay for Channel-mapping (jiffies) */
DECL|macro|ICN_TIMER_BCREAD
mdefine_line|#define ICN_TIMER_BCREAD 3&t;/* B-Channel poll-cycle                */
DECL|macro|ICN_TIMER_DCREAD
mdefine_line|#define ICN_TIMER_DCREAD 50&t;/* D-Channel poll-cycle                */
DECL|macro|ICN_CODE_STAGE1
mdefine_line|#define ICN_CODE_STAGE1 4096&t;/* Size of bootcode                    */
DECL|macro|ICN_CODE_STAGE2
mdefine_line|#define ICN_CODE_STAGE2 65536&t;/* Size of protocol-code               */
DECL|macro|ICN_MAX_SQUEUE
mdefine_line|#define ICN_MAX_SQUEUE 65536&t;/* Max. outstanding send-data          */
DECL|macro|ICN_FRAGSIZE
mdefine_line|#define ICN_FRAGSIZE (250)&t;/* Max. size of send-fragments         */
DECL|macro|ICN_BCH
mdefine_line|#define ICN_BCH 2&t;&t;/* Number of supported channels        */
multiline_comment|/* type-definitions for accessing the mmap-io-areas */
DECL|macro|SHM_DCTL_OFFSET
mdefine_line|#define SHM_DCTL_OFFSET (0)&t;/* Offset to data-controlstructures in shm */
DECL|macro|SHM_CCTL_OFFSET
mdefine_line|#define SHM_CCTL_OFFSET (0x1d2)&t;/* Offset to comm-controlstructures in shm */
DECL|macro|SHM_CBUF_OFFSET
mdefine_line|#define SHM_CBUF_OFFSET (0x200)&t;/* Offset to comm-buffers in shm           */
DECL|macro|SHM_DBUF_OFFSET
mdefine_line|#define SHM_DBUF_OFFSET (0x2000)&t;/* Offset to data-buffers in shm           */
r_typedef
r_struct
(brace
DECL|member|length
r_int
r_char
id|length
suffix:semicolon
multiline_comment|/* Bytecount of fragment (max 250)     */
DECL|member|endflag
r_int
r_char
id|endflag
suffix:semicolon
multiline_comment|/* 0=last frag., 0xff=frag. continued  */
DECL|member|data
r_int
r_char
id|data
(braket
id|ICN_FRAGSIZE
)braket
suffix:semicolon
multiline_comment|/* The data                            */
multiline_comment|/* Fill to 256 bytes */
DECL|member|unused
r_char
id|unused
(braket
l_int|0x100
op_minus
id|ICN_FRAGSIZE
op_minus
l_int|2
)braket
suffix:semicolon
DECL|typedef|frag_buf
)brace
id|frag_buf
suffix:semicolon
r_typedef
r_union
(brace
r_struct
(brace
DECL|member|scns
r_int
r_char
id|scns
suffix:semicolon
multiline_comment|/* Index to free SendFrag.             */
DECL|member|scnr
r_int
r_char
id|scnr
suffix:semicolon
multiline_comment|/* Index to active SendFrag   READONLY */
DECL|member|ecns
r_int
r_char
id|ecns
suffix:semicolon
multiline_comment|/* Index to free RcvFrag.     READONLY */
DECL|member|ecnr
r_int
r_char
id|ecnr
suffix:semicolon
multiline_comment|/* Index to valid RcvFrag              */
DECL|member|unused
r_char
id|unused
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|fuell1
r_int
r_int
id|fuell1
suffix:semicolon
multiline_comment|/* Internal Buf Bytecount              */
DECL|member|data_control
)brace
id|data_control
suffix:semicolon
r_struct
(brace
DECL|member|unused
r_char
id|unused
(braket
id|SHM_CCTL_OFFSET
)braket
suffix:semicolon
DECL|member|iopc_i
r_int
r_char
id|iopc_i
suffix:semicolon
multiline_comment|/* Read-Ptr Status-Queue      READONLY */
DECL|member|iopc_o
r_int
r_char
id|iopc_o
suffix:semicolon
multiline_comment|/* Write-Ptr Status-Queue              */
DECL|member|pcio_i
r_int
r_char
id|pcio_i
suffix:semicolon
multiline_comment|/* Write-Ptr Command-Queue             */
DECL|member|pcio_o
r_int
r_char
id|pcio_o
suffix:semicolon
multiline_comment|/* Read-Ptr Command Queue     READONLY */
DECL|member|comm_control
)brace
id|comm_control
suffix:semicolon
r_struct
(brace
DECL|member|unused
r_char
id|unused
(braket
id|SHM_CBUF_OFFSET
)braket
suffix:semicolon
DECL|member|pcio_buf
r_int
r_char
id|pcio_buf
(braket
l_int|0x100
)braket
suffix:semicolon
multiline_comment|/* Ring-Buffer Command-Queue           */
DECL|member|iopc_buf
r_int
r_char
id|iopc_buf
(braket
l_int|0x100
)braket
suffix:semicolon
multiline_comment|/* Ring-Buffer Status-Queue            */
DECL|member|comm_buffers
)brace
id|comm_buffers
suffix:semicolon
r_struct
(brace
DECL|member|unused
r_char
id|unused
(braket
id|SHM_DBUF_OFFSET
)braket
suffix:semicolon
DECL|member|receive_buf
id|frag_buf
id|receive_buf
(braket
l_int|0x10
)braket
suffix:semicolon
DECL|member|send_buf
id|frag_buf
id|send_buf
(braket
l_int|0x10
)braket
suffix:semicolon
DECL|member|data_buffers
)brace
id|data_buffers
suffix:semicolon
DECL|typedef|icn_shmem
)brace
id|icn_shmem
suffix:semicolon
multiline_comment|/* Sendbuffer-queue-element */
r_typedef
r_struct
(brace
DECL|member|next
r_char
op_star
id|next
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|rptr
id|u_char
op_star
id|rptr
suffix:semicolon
DECL|member|buffer
id|u_char
id|buffer
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|pqueue
)brace
id|pqueue
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
multiline_comment|/* Base-port-adress                 */
DECL|member|shmem
id|icn_shmem
op_star
id|shmem
suffix:semicolon
multiline_comment|/* Pointer to memory-mapped-buffers */
DECL|member|myid
r_int
id|myid
suffix:semicolon
multiline_comment|/* Driver-Nr. assigned by linklevel */
DECL|member|rvalid
r_int
id|rvalid
suffix:semicolon
multiline_comment|/* IO-portregion has been requested */
DECL|member|mvalid
r_int
id|mvalid
suffix:semicolon
multiline_comment|/* IO-shmem has been requested      */
DECL|member|leased
r_int
id|leased
suffix:semicolon
multiline_comment|/* Flag: This Adapter is connected  */
multiline_comment|/*       to a leased line           */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Statusflags                      */
DECL|member|doubleS0
r_int
id|doubleS0
suffix:semicolon
multiline_comment|/* Flag: Double-S0-Card             */
DECL|member|secondhalf
r_int
id|secondhalf
suffix:semicolon
multiline_comment|/* Flag: Second half of a doubleS0  */
DECL|member|ptype
r_int
id|ptype
suffix:semicolon
multiline_comment|/* Protocoltype (1TR6 or Euro)      */
DECL|member|st_timer
r_struct
id|timer_list
id|st_timer
suffix:semicolon
multiline_comment|/* Timer for Status-Polls           */
DECL|member|rb_timer
r_struct
id|timer_list
id|rb_timer
suffix:semicolon
multiline_comment|/* Timer for B-Channel-Polls        */
DECL|member|channel
r_int
id|channel
suffix:semicolon
multiline_comment|/* Currently mapped Channel         */
DECL|member|chanlock
r_int
id|chanlock
suffix:semicolon
multiline_comment|/* Semaphore for Channel-Mapping    */
DECL|member|rcvbuf
id|u_char
id|rcvbuf
(braket
id|ICN_BCH
)braket
(braket
l_int|4096
)braket
suffix:semicolon
multiline_comment|/* B-Channel-Receive-Buffers      */
DECL|member|rcvidx
r_int
id|rcvidx
(braket
id|ICN_BCH
)braket
suffix:semicolon
multiline_comment|/* Index for above buffers          */
DECL|member|l2_proto
r_int
id|l2_proto
(braket
id|ICN_BCH
)braket
suffix:semicolon
multiline_comment|/* Current layer-2-protocol         */
DECL|member|interface
id|isdn_if
id|interface
suffix:semicolon
multiline_comment|/* Interface to upper layer         */
DECL|member|iptr
r_int
id|iptr
suffix:semicolon
multiline_comment|/* Index to imsg-buffer             */
DECL|member|imsg
r_char
id|imsg
(braket
l_int|60
)braket
suffix:semicolon
multiline_comment|/* Internal buf for status-parsing  */
DECL|member|msg_buf
r_char
id|msg_buf
(braket
l_int|2048
)braket
suffix:semicolon
multiline_comment|/* Buffer for status-messages       */
DECL|member|msg_buf_write
r_char
op_star
id|msg_buf_write
suffix:semicolon
multiline_comment|/* Writepointer for statusbuffer    */
DECL|member|msg_buf_read
r_char
op_star
id|msg_buf_read
suffix:semicolon
multiline_comment|/* Readpointer for statusbuffer     */
DECL|member|msg_buf_end
r_char
op_star
id|msg_buf_end
suffix:semicolon
multiline_comment|/* Pointer to end of statusbuffer   */
DECL|member|sndcount
r_int
id|sndcount
(braket
id|ICN_BCH
)braket
suffix:semicolon
multiline_comment|/* Byte-counters for B-Ch.-send     */
DECL|member|spqueue
id|pqueue
op_star
id|spqueue
(braket
id|ICN_BCH
)braket
suffix:semicolon
multiline_comment|/* Pointers to start of Send-Queue  */
macro_line|#ifdef DEBUG_RCVCALLBACK
DECL|member|akt_pending
r_int
id|akt_pending
(braket
id|ICN_BCH
)braket
suffix:semicolon
DECL|member|max_pending
r_int
id|max_pending
(braket
id|ICN_BCH
)braket
suffix:semicolon
macro_line|#endif
DECL|typedef|icn_dev
)brace
id|icn_dev
suffix:semicolon
DECL|typedef|icn_devptr
r_typedef
id|icn_dev
op_star
id|icn_devptr
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|variable|dev
r_static
id|icn_dev
op_star
id|dev
op_assign
(paren
id|icn_dev
op_star
)paren
l_int|0
suffix:semicolon
DECL|variable|dev2
r_static
id|icn_dev
op_star
id|dev2
op_assign
(paren
id|icn_dev
op_star
)paren
l_int|0
suffix:semicolon
multiline_comment|/* With modutils &gt;= 1.1.67 Integers can be changed while loading a&n; * module. For this reason define the Port-Base an Shmem-Base as&n; * integers.&n; */
DECL|variable|portbase
r_int
id|portbase
op_assign
id|ICN_BASEADDR
suffix:semicolon
DECL|variable|membase
r_int
id|membase
op_assign
id|ICN_MEMADDR
suffix:semicolon
DECL|variable|icn_id
r_char
op_star
id|icn_id
op_assign
l_string|&quot;&bslash;0&quot;
suffix:semicolon
DECL|variable|icn_id2
r_char
op_star
id|icn_id2
op_assign
l_string|&quot;&bslash;0&quot;
suffix:semicolon
DECL|variable|regname
r_static
r_char
id|regname
(braket
l_int|35
)braket
suffix:semicolon
multiline_comment|/* Name used for port/mem-registration */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
multiline_comment|/* Utility-Macros */
multiline_comment|/* Return true, if there is a free transmit-buffer */
DECL|macro|sbfree
mdefine_line|#define sbfree (((dev-&gt;shmem-&gt;data_control.scns+1) &amp; 0xf) != &bslash;&n;                dev-&gt;shmem-&gt;data_control.scnr)
multiline_comment|/* Switch to next transmit-buffer */
DECL|macro|sbnext
mdefine_line|#define sbnext (dev-&gt;shmem-&gt;data_control.scns = &bslash;&n;               ((dev-&gt;shmem-&gt;data_control.scns+1) &amp; 0xf))
multiline_comment|/* Shortcuts for transmit-buffer-access */
DECL|macro|sbuf_n
mdefine_line|#define sbuf_n dev-&gt;shmem-&gt;data_control.scns
DECL|macro|sbuf_d
mdefine_line|#define sbuf_d dev-&gt;shmem-&gt;data_buffers.send_buf[sbuf_n].data
DECL|macro|sbuf_l
mdefine_line|#define sbuf_l dev-&gt;shmem-&gt;data_buffers.send_buf[sbuf_n].length
DECL|macro|sbuf_f
mdefine_line|#define sbuf_f dev-&gt;shmem-&gt;data_buffers.send_buf[sbuf_n].endflag
multiline_comment|/* Return true, if there is receive-data is available */
DECL|macro|rbavl
mdefine_line|#define rbavl  (dev-&gt;shmem-&gt;data_control.ecnr != &bslash;&n;                dev-&gt;shmem-&gt;data_control.ecns)
multiline_comment|/* Switch to next receive-buffer */
DECL|macro|rbnext
mdefine_line|#define rbnext (dev-&gt;shmem-&gt;data_control.ecnr = &bslash;&n;               ((dev-&gt;shmem-&gt;data_control.ecnr+1) &amp; 0xf))
multiline_comment|/* Shortcuts for receive-buffer-access */
DECL|macro|rbuf_n
mdefine_line|#define rbuf_n dev-&gt;shmem-&gt;data_control.ecnr
DECL|macro|rbuf_d
mdefine_line|#define rbuf_d dev-&gt;shmem-&gt;data_buffers.receive_buf[rbuf_n].data
DECL|macro|rbuf_l
mdefine_line|#define rbuf_l dev-&gt;shmem-&gt;data_buffers.receive_buf[rbuf_n].length
DECL|macro|rbuf_f
mdefine_line|#define rbuf_f dev-&gt;shmem-&gt;data_buffers.receive_buf[rbuf_n].endflag
multiline_comment|/* Shortcuts for command-buffer-access */
DECL|macro|cmd_o
mdefine_line|#define cmd_o (dev-&gt;shmem-&gt;comm_control.pcio_o)
DECL|macro|cmd_i
mdefine_line|#define cmd_i (dev-&gt;shmem-&gt;comm_control.pcio_i)
multiline_comment|/* Return free space in command-buffer */
DECL|macro|cmd_free
mdefine_line|#define cmd_free ((cmd_i&gt;=cmd_o)?0x100-cmd_i+cmd_o:cmd_o-cmd_i)
multiline_comment|/* Shortcuts for message-buffer-access */
DECL|macro|msg_o
mdefine_line|#define msg_o (dev-&gt;shmem-&gt;comm_control.iopc_o)
DECL|macro|msg_i
mdefine_line|#define msg_i (dev-&gt;shmem-&gt;comm_control.iopc_i)
multiline_comment|/* Return length of Message, if avail. */
DECL|macro|msg_avail
mdefine_line|#define msg_avail ((msg_o&gt;msg_i)?0x100-msg_o+msg_i:msg_i-msg_o)
DECL|macro|MIN
mdefine_line|#define MIN(a,b) ((a&lt;b)?a:b)
DECL|macro|MAX
mdefine_line|#define MAX(a,b) ((a&gt;b)?a:b)
multiline_comment|/* Hopefully, a separate resource-registration-scheme for shared-memory&n; * will be introduced into the kernel. Until then, we use the normal&n; * routines, designed for port-registration.&n; */
DECL|macro|check_shmem
mdefine_line|#define check_shmem   check_region
DECL|macro|release_shmem
mdefine_line|#define release_shmem release_region
DECL|macro|request_shmem
mdefine_line|#define request_shmem request_region
macro_line|#endif&t;&t;&t;&t;/* defined(__KERNEL__) || defined(__DEBUGVAR__) */
macro_line|#endif&t;&t;&t;&t;/* icn_h */
eof
