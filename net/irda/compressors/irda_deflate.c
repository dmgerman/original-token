multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irda_deflate.c&n; * Version:       &n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Fri Oct  9 02:52:08 1998&n; * Modified at:   Mon Dec 14 19:48:54 1998&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *  ==FILEVERSION 980319==&n; *&n; * irda_deflate.c - interface the zlib procedures for Deflate compression&n; * and decompression (as used by gzip) to the IrDA code.&n; * This version is for use with Linux kernel 2.1.X.&n; *&n; * Copyright (c) 1994 The Australian National University.&n; * All rights reserved.&n; *&n; * Permission to use, copy, modify, and distribute this software and its&n; * documentation is hereby granted, provided that the above copyright&n; * notice appears in all copies.  This software is provided without any&n; * warranty, express or implied. The Australian National University&n; * makes no representations about the suitability of this software for&n; * any purpose.&n; *&n; * IN NO EVENT SHALL THE AUSTRALIAN NATIONAL UNIVERSITY BE LIABLE TO ANY&n; * PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES&n; * ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF&n; * THE AUSTRALIAN NATIONAL UNIVERSITY HAS BEEN ADVISED OF THE POSSIBILITY&n; * OF SUCH DAMAGE.&n; *&n; * THE AUSTRALIAN NATIONAL UNIVERSITY SPECIFICALLY DISCLAIMS ANY WARRANTIES,&n; * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY&n; * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS&n; * ON AN &quot;AS IS&quot; BASIS, AND THE AUSTRALIAN NATIONAL UNIVERSITY HAS NO&n; * OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS,&n; * OR MODIFICATIONS.&n; *&n; * From: deflate.c,v 1.1 1996/01/18 03:17:48 paulus Exp&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt; 
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;&t;/* to get the struct task_struct */
macro_line|#include &lt;linux/string.h&gt;&t;/* used in new tty drivers */
macro_line|#include &lt;linux/signal.h&gt;&t;/* used in new tty drivers */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/ppp_defs.h&gt;
macro_line|#include &lt;linux/ppp-comp.h&gt;
multiline_comment|/*&n; * This is not that nice, but what can we do when the code has been placed&n; * elsewhere&n; */
macro_line|#include &quot;../../../drivers/net/zlib.c&quot;
multiline_comment|/*&n; * State for a Deflate (de)compressor.&n; */
DECL|struct|irda_deflate_state
r_struct
id|irda_deflate_state
(brace
DECL|member|seqno
r_int
id|seqno
suffix:semicolon
DECL|member|w_size
r_int
id|w_size
suffix:semicolon
DECL|member|unit
r_int
id|unit
suffix:semicolon
DECL|member|mru
r_int
id|mru
suffix:semicolon
DECL|member|debug
r_int
id|debug
suffix:semicolon
DECL|member|strm
id|z_stream
id|strm
suffix:semicolon
DECL|member|stats
r_struct
id|compstat
id|stats
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|DEFLATE_OVHD
mdefine_line|#define DEFLATE_OVHD&t;2&t;&t;/* Deflate overhead/packet */
r_static
r_void
op_star
id|zalloc
id|__P
c_func
(paren
(paren
r_void
op_star
comma
r_int
r_int
id|items
comma
r_int
r_int
id|size
)paren
)paren
suffix:semicolon
r_static
r_void
op_star
id|zalloc_init
id|__P
c_func
(paren
(paren
r_void
op_star
comma
r_int
r_int
id|items
comma
r_int
r_int
id|size
)paren
)paren
suffix:semicolon
r_static
r_void
id|zfree
id|__P
c_func
(paren
(paren
r_void
op_star
comma
r_void
op_star
id|ptr
)paren
)paren
suffix:semicolon
r_static
r_void
op_star
id|z_comp_alloc
id|__P
c_func
(paren
(paren
r_int
r_char
op_star
id|options
comma
r_int
id|opt_len
)paren
)paren
suffix:semicolon
r_static
r_void
op_star
id|z_decomp_alloc
id|__P
c_func
(paren
(paren
r_int
r_char
op_star
id|options
comma
r_int
id|opt_len
)paren
)paren
suffix:semicolon
r_static
r_void
id|z_comp_free
id|__P
c_func
(paren
(paren
r_void
op_star
id|state
)paren
)paren
suffix:semicolon
r_static
r_void
id|z_decomp_free
id|__P
c_func
(paren
(paren
r_void
op_star
id|state
)paren
)paren
suffix:semicolon
r_static
r_int
id|z_comp_init
id|__P
c_func
(paren
(paren
r_void
op_star
id|state
comma
r_int
r_char
op_star
id|options
comma
r_int
id|opt_len
comma
r_int
id|unit
comma
r_int
id|hdrlen
comma
r_int
id|debug
)paren
)paren
suffix:semicolon
r_static
r_int
id|z_decomp_init
id|__P
c_func
(paren
(paren
r_void
op_star
id|state
comma
r_int
r_char
op_star
id|options
comma
r_int
id|opt_len
comma
r_int
id|unit
comma
r_int
id|hdrlen
comma
r_int
id|mru
comma
r_int
id|debug
)paren
)paren
suffix:semicolon
r_static
r_int
id|z_compress
id|__P
c_func
(paren
(paren
r_void
op_star
id|state
comma
r_int
r_char
op_star
id|rptr
comma
r_int
r_char
op_star
id|obuf
comma
r_int
id|isize
comma
r_int
id|osize
)paren
)paren
suffix:semicolon
r_static
r_void
id|z_incomp
id|__P
c_func
(paren
(paren
r_void
op_star
id|state
comma
r_int
r_char
op_star
id|ibuf
comma
r_int
id|icnt
)paren
)paren
suffix:semicolon
r_static
r_int
id|z_decompress
id|__P
c_func
(paren
(paren
r_void
op_star
id|state
comma
r_int
r_char
op_star
id|ibuf
comma
r_int
id|isize
comma
r_int
r_char
op_star
id|obuf
comma
r_int
id|osize
)paren
)paren
suffix:semicolon
r_static
r_void
id|z_comp_reset
id|__P
c_func
(paren
(paren
r_void
op_star
id|state
)paren
)paren
suffix:semicolon
r_static
r_void
id|z_decomp_reset
id|__P
c_func
(paren
(paren
r_void
op_star
id|state
)paren
)paren
suffix:semicolon
r_static
r_void
id|z_comp_stats
id|__P
c_func
(paren
(paren
r_void
op_star
id|state
comma
r_struct
id|compstat
op_star
id|stats
)paren
)paren
suffix:semicolon
DECL|struct|chunk_header
r_struct
id|chunk_header
(brace
DECL|member|valloced
r_int
id|valloced
suffix:semicolon
multiline_comment|/* allocated with valloc, not kmalloc */
DECL|member|guard
r_int
id|guard
suffix:semicolon
multiline_comment|/* check for overwritten header */
)brace
suffix:semicolon
DECL|macro|GUARD_MAGIC
mdefine_line|#define GUARD_MAGIC&t;0x77a8011a
DECL|macro|MIN_VMALLOC
mdefine_line|#define MIN_VMALLOC&t;2048&t;/* use kmalloc for blocks &lt; this */
multiline_comment|/*&n; * Space allocation and freeing routines for use by zlib routines.&n; */
DECL|function|zfree
r_void
id|zfree
c_func
(paren
r_void
op_star
id|arg
comma
r_void
op_star
id|ptr
)paren
(brace
r_struct
id|chunk_header
op_star
id|hdr
op_assign
(paren
(paren
r_struct
id|chunk_header
op_star
)paren
id|ptr
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|hdr-&gt;guard
op_ne
id|GUARD_MAGIC
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;zfree: header corrupted (%x %x) at %p&bslash;n&quot;
comma
id|hdr-&gt;valloced
comma
id|hdr-&gt;guard
comma
id|hdr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hdr-&gt;valloced
)paren
id|vfree
c_func
(paren
id|hdr
)paren
suffix:semicolon
r_else
id|kfree
c_func
(paren
id|hdr
)paren
suffix:semicolon
)brace
r_void
op_star
DECL|function|zalloc
id|zalloc
c_func
(paren
id|arg
comma
id|items
comma
id|size
)paren
r_void
op_star
id|arg
suffix:semicolon
r_int
r_int
id|items
comma
id|size
suffix:semicolon
(brace
r_struct
id|chunk_header
op_star
id|hdr
suffix:semicolon
r_int
id|nbytes
suffix:semicolon
id|nbytes
op_assign
id|items
op_star
id|size
op_plus
r_sizeof
(paren
op_star
id|hdr
)paren
suffix:semicolon
id|hdr
op_assign
id|kmalloc
c_func
(paren
id|nbytes
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdr
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|hdr-&gt;valloced
op_assign
l_int|0
suffix:semicolon
id|hdr-&gt;guard
op_assign
id|GUARD_MAGIC
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
(paren
id|hdr
op_plus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|zalloc_init
r_void
op_star
id|zalloc_init
c_func
(paren
r_void
op_star
id|arg
comma
r_int
r_int
id|items
comma
r_int
r_int
id|size
)paren
(brace
r_struct
id|chunk_header
op_star
id|hdr
suffix:semicolon
r_int
id|nbytes
suffix:semicolon
id|nbytes
op_assign
id|items
op_star
id|size
op_plus
r_sizeof
(paren
op_star
id|hdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
op_ge
id|MIN_VMALLOC
)paren
id|hdr
op_assign
id|vmalloc
c_func
(paren
id|nbytes
)paren
suffix:semicolon
r_else
id|hdr
op_assign
id|kmalloc
c_func
(paren
id|nbytes
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdr
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|hdr-&gt;valloced
op_assign
id|nbytes
op_ge
id|MIN_VMALLOC
suffix:semicolon
id|hdr-&gt;guard
op_assign
id|GUARD_MAGIC
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
(paren
id|hdr
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|z_comp_free
id|z_comp_free
c_func
(paren
id|arg
)paren
r_void
op_star
id|arg
suffix:semicolon
(brace
r_struct
id|irda_deflate_state
op_star
id|state
op_assign
(paren
r_struct
id|irda_deflate_state
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|state
)paren
(brace
id|deflateEnd
c_func
(paren
op_amp
id|state-&gt;strm
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|state
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Allocate space for a compressor.&n; */
r_static
r_void
op_star
DECL|function|z_comp_alloc
id|z_comp_alloc
c_func
(paren
id|options
comma
id|opt_len
)paren
r_int
r_char
op_star
id|options
suffix:semicolon
r_int
id|opt_len
suffix:semicolon
(brace
r_struct
id|irda_deflate_state
op_star
id|state
suffix:semicolon
r_int
id|w_size
suffix:semicolon
r_if
c_cond
(paren
id|opt_len
op_ne
id|CILEN_DEFLATE
op_logical_or
(paren
id|options
(braket
l_int|0
)braket
op_ne
id|CI_DEFLATE
op_logical_and
id|options
(braket
l_int|0
)braket
op_ne
id|CI_DEFLATE_DRAFT
)paren
op_logical_or
id|options
(braket
l_int|1
)braket
op_ne
id|CILEN_DEFLATE
op_logical_or
id|DEFLATE_METHOD
c_func
(paren
id|options
(braket
l_int|2
)braket
)paren
op_ne
id|DEFLATE_METHOD_VAL
op_logical_or
id|options
(braket
l_int|3
)braket
op_ne
id|DEFLATE_CHK_SEQUENCE
)paren
r_return
l_int|NULL
suffix:semicolon
id|w_size
op_assign
id|DEFLATE_SIZE
c_func
(paren
id|options
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|w_size
op_assign
id|MAX_WBITS
suffix:semicolon
r_if
c_cond
(paren
id|w_size
template_param
id|DEFLATE_MAX_SIZE
)paren
r_return
l_int|NULL
suffix:semicolon
id|state
op_assign
(paren
r_struct
id|irda_deflate_state
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|state
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|memset
(paren
id|state
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|irda_deflate_state
)paren
)paren
suffix:semicolon
id|state-&gt;strm.next_in
op_assign
l_int|NULL
suffix:semicolon
id|state-&gt;strm.zalloc
op_assign
id|zalloc_init
suffix:semicolon
id|state-&gt;strm.zfree
op_assign
id|zfree
suffix:semicolon
id|state-&gt;w_size
op_assign
id|w_size
suffix:semicolon
r_if
c_cond
(paren
id|deflateInit2
c_func
(paren
op_amp
id|state-&gt;strm
comma
id|Z_DEFAULT_COMPRESSION
comma
id|DEFLATE_METHOD_VAL
comma
op_minus
id|w_size
comma
l_int|8
comma
id|Z_DEFAULT_STRATEGY
)paren
op_ne
id|Z_OK
)paren
r_goto
id|out_free
suffix:semicolon
id|state-&gt;strm.zalloc
op_assign
id|zalloc
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|state
suffix:semicolon
id|out_free
suffix:colon
id|z_comp_free
c_func
(paren
id|state
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_int
DECL|function|z_comp_init
id|z_comp_init
c_func
(paren
id|arg
comma
id|options
comma
id|opt_len
comma
id|unit
comma
id|hdrlen
comma
id|debug
)paren
r_void
op_star
id|arg
suffix:semicolon
r_int
r_char
op_star
id|options
suffix:semicolon
r_int
id|opt_len
comma
id|unit
comma
id|hdrlen
comma
id|debug
suffix:semicolon
(brace
r_struct
id|irda_deflate_state
op_star
id|state
op_assign
(paren
r_struct
id|irda_deflate_state
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|opt_len
OL
id|CILEN_DEFLATE
op_logical_or
(paren
id|options
(braket
l_int|0
)braket
op_ne
id|CI_DEFLATE
op_logical_and
id|options
(braket
l_int|0
)braket
op_ne
id|CI_DEFLATE_DRAFT
)paren
op_logical_or
id|options
(braket
l_int|1
)braket
op_ne
id|CILEN_DEFLATE
op_logical_or
id|DEFLATE_METHOD
c_func
(paren
id|options
(braket
l_int|2
)braket
)paren
op_ne
id|DEFLATE_METHOD_VAL
op_logical_or
id|DEFLATE_SIZE
c_func
(paren
id|options
(braket
l_int|2
)braket
)paren
op_ne
id|state-&gt;w_size
op_logical_or
id|options
(braket
l_int|3
)braket
op_ne
id|DEFLATE_CHK_SEQUENCE
)paren
r_return
l_int|0
suffix:semicolon
id|state-&gt;seqno
op_assign
l_int|0
suffix:semicolon
id|state-&gt;unit
op_assign
id|unit
suffix:semicolon
id|state-&gt;debug
op_assign
id|debug
suffix:semicolon
id|deflateReset
c_func
(paren
op_amp
id|state-&gt;strm
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|z_comp_reset
r_static
r_void
id|z_comp_reset
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_struct
id|irda_deflate_state
op_star
id|state
op_assign
(paren
r_struct
id|irda_deflate_state
op_star
)paren
id|arg
suffix:semicolon
id|state-&gt;seqno
op_assign
l_int|0
suffix:semicolon
id|deflateReset
c_func
(paren
op_amp
id|state-&gt;strm
)paren
suffix:semicolon
)brace
r_int
DECL|function|z_compress
id|z_compress
c_func
(paren
id|arg
comma
id|rptr
comma
id|obuf
comma
id|isize
comma
id|osize
)paren
r_void
op_star
id|arg
suffix:semicolon
r_int
r_char
op_star
id|rptr
suffix:semicolon
multiline_comment|/* uncompressed packet (in) */
r_int
r_char
op_star
id|obuf
suffix:semicolon
multiline_comment|/* compressed packet (out) */
r_int
id|isize
comma
id|osize
suffix:semicolon
(brace
r_struct
id|irda_deflate_state
op_star
id|state
op_assign
(paren
r_struct
id|irda_deflate_state
op_star
)paren
id|arg
suffix:semicolon
r_int
id|r
comma
id|olen
comma
id|oavail
suffix:semicolon
id|olen
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Don&squot;t generate compressed packets which are larger than&n;&t;   the uncompressed packet. */
r_if
c_cond
(paren
id|osize
OG
id|isize
)paren
id|osize
op_assign
id|isize
suffix:semicolon
id|state-&gt;strm.next_out
op_assign
id|obuf
suffix:semicolon
id|state-&gt;strm.avail_out
op_assign
id|oavail
op_assign
id|osize
suffix:semicolon
id|state-&gt;strm.next_in
op_assign
id|rptr
suffix:semicolon
id|state-&gt;strm.avail_in
op_assign
id|isize
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|r
op_assign
id|deflate
c_func
(paren
op_amp
id|state-&gt;strm
comma
id|Z_PACKET_FLUSH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_ne
id|Z_OK
)paren
(brace
r_if
c_cond
(paren
id|state-&gt;debug
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;z_compress: deflate returned %d&bslash;n&quot;
comma
id|r
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|state-&gt;strm.avail_out
op_eq
l_int|0
)paren
(brace
id|olen
op_add_assign
id|oavail
suffix:semicolon
id|state-&gt;strm.next_out
op_assign
l_int|NULL
suffix:semicolon
id|state-&gt;strm.avail_out
op_assign
id|oavail
op_assign
l_int|1000000
suffix:semicolon
)brace
r_else
(brace
r_break
suffix:semicolon
multiline_comment|/* all done */
)brace
)brace
id|olen
op_add_assign
id|oavail
op_minus
id|state-&gt;strm.avail_out
suffix:semicolon
multiline_comment|/*&n;&t; * See if we managed to reduce the size of the packet.&n;&t; */
r_if
c_cond
(paren
id|olen
OL
id|isize
)paren
(brace
id|state-&gt;stats.comp_bytes
op_add_assign
id|olen
suffix:semicolon
id|state-&gt;stats.comp_packets
op_increment
suffix:semicolon
)brace
r_else
(brace
id|state-&gt;stats.inc_bytes
op_add_assign
id|isize
suffix:semicolon
id|state-&gt;stats.inc_packets
op_increment
suffix:semicolon
id|olen
op_assign
l_int|0
suffix:semicolon
)brace
id|state-&gt;stats.unc_bytes
op_add_assign
id|isize
suffix:semicolon
id|state-&gt;stats.unc_packets
op_increment
suffix:semicolon
r_return
id|olen
suffix:semicolon
)brace
r_static
r_void
DECL|function|z_comp_stats
id|z_comp_stats
c_func
(paren
id|arg
comma
id|stats
)paren
r_void
op_star
id|arg
suffix:semicolon
r_struct
id|compstat
op_star
id|stats
suffix:semicolon
(brace
r_struct
id|irda_deflate_state
op_star
id|state
op_assign
(paren
r_struct
id|irda_deflate_state
op_star
)paren
id|arg
suffix:semicolon
op_star
id|stats
op_assign
id|state-&gt;stats
suffix:semicolon
)brace
DECL|function|z_decomp_free
r_static
r_void
id|z_decomp_free
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_struct
id|irda_deflate_state
op_star
id|state
op_assign
(paren
r_struct
id|irda_deflate_state
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|state
)paren
(brace
id|inflateEnd
c_func
(paren
op_amp
id|state-&gt;strm
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|state
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Allocate space for a decompressor.&n; */
r_static
r_void
op_star
DECL|function|z_decomp_alloc
id|z_decomp_alloc
c_func
(paren
id|options
comma
id|opt_len
)paren
r_int
r_char
op_star
id|options
suffix:semicolon
r_int
id|opt_len
suffix:semicolon
(brace
r_struct
id|irda_deflate_state
op_star
id|state
suffix:semicolon
r_int
id|w_size
suffix:semicolon
r_if
c_cond
(paren
id|opt_len
op_ne
id|CILEN_DEFLATE
op_logical_or
(paren
id|options
(braket
l_int|0
)braket
op_ne
id|CI_DEFLATE
op_logical_and
id|options
(braket
l_int|0
)braket
op_ne
id|CI_DEFLATE_DRAFT
)paren
op_logical_or
id|options
(braket
l_int|1
)braket
op_ne
id|CILEN_DEFLATE
op_logical_or
id|DEFLATE_METHOD
c_func
(paren
id|options
(braket
l_int|2
)braket
)paren
op_ne
id|DEFLATE_METHOD_VAL
op_logical_or
id|options
(braket
l_int|3
)braket
op_ne
id|DEFLATE_CHK_SEQUENCE
)paren
r_return
l_int|NULL
suffix:semicolon
id|w_size
op_assign
id|DEFLATE_SIZE
c_func
(paren
id|options
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|w_size
op_assign
id|MAX_WBITS
suffix:semicolon
r_if
c_cond
(paren
id|w_size
template_param
id|DEFLATE_MAX_SIZE
)paren
r_return
l_int|NULL
suffix:semicolon
id|state
op_assign
(paren
r_struct
id|irda_deflate_state
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|state
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|state
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|memset
(paren
id|state
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|irda_deflate_state
)paren
)paren
suffix:semicolon
id|state-&gt;w_size
op_assign
id|w_size
suffix:semicolon
id|state-&gt;strm.next_out
op_assign
l_int|NULL
suffix:semicolon
id|state-&gt;strm.zalloc
op_assign
id|zalloc_init
suffix:semicolon
id|state-&gt;strm.zfree
op_assign
id|zfree
suffix:semicolon
r_if
c_cond
(paren
id|inflateInit2
c_func
(paren
op_amp
id|state-&gt;strm
comma
op_minus
id|w_size
)paren
op_ne
id|Z_OK
)paren
r_goto
id|out_free
suffix:semicolon
id|state-&gt;strm.zalloc
op_assign
id|zalloc
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|state
suffix:semicolon
id|out_free
suffix:colon
id|z_decomp_free
c_func
(paren
id|state
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_int
DECL|function|z_decomp_init
id|z_decomp_init
c_func
(paren
id|arg
comma
id|options
comma
id|opt_len
comma
id|unit
comma
id|hdrlen
comma
id|mru
comma
id|debug
)paren
r_void
op_star
id|arg
suffix:semicolon
r_int
r_char
op_star
id|options
suffix:semicolon
r_int
id|opt_len
comma
id|unit
comma
id|hdrlen
comma
id|mru
comma
id|debug
suffix:semicolon
(brace
r_struct
id|irda_deflate_state
op_star
id|state
op_assign
(paren
r_struct
id|irda_deflate_state
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|opt_len
OL
id|CILEN_DEFLATE
op_logical_or
(paren
id|options
(braket
l_int|0
)braket
op_ne
id|CI_DEFLATE
op_logical_and
id|options
(braket
l_int|0
)braket
op_ne
id|CI_DEFLATE_DRAFT
)paren
op_logical_or
id|options
(braket
l_int|1
)braket
op_ne
id|CILEN_DEFLATE
op_logical_or
id|DEFLATE_METHOD
c_func
(paren
id|options
(braket
l_int|2
)braket
)paren
op_ne
id|DEFLATE_METHOD_VAL
op_logical_or
id|DEFLATE_SIZE
c_func
(paren
id|options
(braket
l_int|2
)braket
)paren
op_ne
id|state-&gt;w_size
op_logical_or
id|options
(braket
l_int|3
)braket
op_ne
id|DEFLATE_CHK_SEQUENCE
)paren
r_return
l_int|0
suffix:semicolon
id|state-&gt;seqno
op_assign
l_int|0
suffix:semicolon
id|state-&gt;unit
op_assign
id|unit
suffix:semicolon
id|state-&gt;debug
op_assign
id|debug
suffix:semicolon
id|state-&gt;mru
op_assign
id|mru
suffix:semicolon
id|inflateReset
c_func
(paren
op_amp
id|state-&gt;strm
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|z_decomp_reset
r_static
r_void
id|z_decomp_reset
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_struct
id|irda_deflate_state
op_star
id|state
op_assign
(paren
r_struct
id|irda_deflate_state
op_star
)paren
id|arg
suffix:semicolon
id|state-&gt;seqno
op_assign
l_int|0
suffix:semicolon
id|inflateReset
c_func
(paren
op_amp
id|state-&gt;strm
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Decompress a Deflate-compressed packet.&n; *&n; * Because of patent problems, we return DECOMP_ERROR for errors&n; * found by inspecting the input data and for system problems, but&n; * DECOMP_FATALERROR for any errors which could possibly be said to&n; * be being detected &quot;after&quot; decompression.  For DECOMP_ERROR,&n; * we can issue a CCP reset-request; for DECOMP_FATALERROR, we may be&n; * infringing a patent of Motorola&squot;s if we do, so we take CCP down&n; * instead.&n; *&n; * Given that the frame has the correct sequence number and a good FCS,&n; * errors such as invalid codes in the input most likely indicate a&n; * bug, so we return DECOMP_FATALERROR for them in order to turn off&n; * compression, even though they are detected by inspecting the input.&n; */
r_int
DECL|function|z_decompress
id|z_decompress
c_func
(paren
id|arg
comma
id|ibuf
comma
id|isize
comma
id|obuf
comma
id|osize
)paren
r_void
op_star
id|arg
suffix:semicolon
r_int
r_char
op_star
id|ibuf
suffix:semicolon
r_int
id|isize
suffix:semicolon
r_int
r_char
op_star
id|obuf
suffix:semicolon
r_int
id|osize
suffix:semicolon
(brace
r_struct
id|irda_deflate_state
op_star
id|state
op_assign
(paren
r_struct
id|irda_deflate_state
op_star
)paren
id|arg
suffix:semicolon
r_int
id|olen
comma
id|r
suffix:semicolon
r_int
id|overflow
suffix:semicolon
r_int
r_char
id|overflow_buf
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|isize
op_le
id|DEFLATE_OVHD
)paren
(brace
r_if
c_cond
(paren
id|state-&gt;debug
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;z_decompress%d: short pkt (%d)&bslash;n&quot;
comma
id|state-&gt;unit
comma
id|isize
)paren
suffix:semicolon
r_return
id|DECOMP_ERROR
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Set up to call inflate.&n;&t; */
id|state-&gt;strm.next_in
op_assign
id|ibuf
suffix:semicolon
id|state-&gt;strm.avail_in
op_assign
id|isize
suffix:semicolon
id|state-&gt;strm.next_out
op_assign
id|obuf
suffix:semicolon
id|state-&gt;strm.avail_out
op_assign
id|osize
suffix:semicolon
id|overflow
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Call inflate, supplying more input or output as needed.&n;&t; */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|r
op_assign
id|inflate
c_func
(paren
op_amp
id|state-&gt;strm
comma
id|Z_PACKET_FLUSH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_ne
id|Z_OK
)paren
(brace
r_if
c_cond
(paren
id|state-&gt;debug
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;z_decompress%d: inflate returned %d (%s)&bslash;n&quot;
comma
id|state-&gt;unit
comma
id|r
comma
(paren
id|state-&gt;strm.msg
ques
c_cond
id|state-&gt;strm.msg
suffix:colon
l_string|&quot;&quot;
)paren
)paren
suffix:semicolon
r_return
id|DECOMP_FATALERROR
suffix:semicolon
)brace
r_if
c_cond
(paren
id|state-&gt;strm.avail_out
op_ne
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/* all done */
r_if
c_cond
(paren
op_logical_neg
id|overflow
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * We&squot;ve filled up the output buffer; the only way to&n;&t;&t;&t; * find out whether inflate has any more characters&n;&t;&t;&t; * left is to give it another byte of output space.&n;&t;&t;&t; */
id|state-&gt;strm.next_out
op_assign
id|overflow_buf
suffix:semicolon
id|state-&gt;strm.avail_out
op_assign
l_int|1
suffix:semicolon
id|overflow
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|state-&gt;debug
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;z_decompress%d: ran out of mru&bslash;n&quot;
comma
id|state-&gt;unit
)paren
suffix:semicolon
r_return
id|DECOMP_FATALERROR
suffix:semicolon
)brace
)brace
id|olen
op_assign
id|osize
op_plus
id|overflow
op_minus
id|state-&gt;strm.avail_out
suffix:semicolon
id|state-&gt;stats.unc_bytes
op_add_assign
id|olen
suffix:semicolon
id|state-&gt;stats.unc_packets
op_increment
suffix:semicolon
id|state-&gt;stats.comp_bytes
op_add_assign
id|isize
suffix:semicolon
id|state-&gt;stats.comp_packets
op_increment
suffix:semicolon
r_return
id|olen
suffix:semicolon
)brace
multiline_comment|/*&n; * Incompressible data has arrived - add it to the history.&n; */
r_static
r_void
DECL|function|z_incomp
id|z_incomp
c_func
(paren
id|arg
comma
id|ibuf
comma
id|icnt
)paren
r_void
op_star
id|arg
suffix:semicolon
r_int
r_char
op_star
id|ibuf
suffix:semicolon
r_int
id|icnt
suffix:semicolon
(brace
r_struct
id|irda_deflate_state
op_star
id|state
op_assign
(paren
r_struct
id|irda_deflate_state
op_star
)paren
id|arg
suffix:semicolon
r_int
id|r
suffix:semicolon
multiline_comment|/*&n;&t; * Check that the protocol is one we handle.&n;&t; */
multiline_comment|/*&n;&t; * We start at the either the 1st or 2nd byte of the protocol field,&n;&t; * depending on whether the protocol value is compressible.&n;&t; */
id|state-&gt;strm.next_in
op_assign
id|ibuf
suffix:semicolon
id|state-&gt;strm.avail_in
op_assign
id|icnt
suffix:semicolon
id|r
op_assign
id|inflateIncomp
c_func
(paren
op_amp
id|state-&gt;strm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_ne
id|Z_OK
)paren
(brace
multiline_comment|/* gak! */
r_if
c_cond
(paren
id|state-&gt;debug
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;z_incomp%d: inflateIncomp returned %d (%s)&bslash;n&quot;
comma
id|state-&gt;unit
comma
id|r
comma
(paren
id|state-&gt;strm.msg
ques
c_cond
id|state-&gt;strm.msg
suffix:colon
l_string|&quot;&quot;
)paren
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Update stats.&n;&t; */
id|state-&gt;stats.inc_bytes
op_add_assign
id|icnt
suffix:semicolon
id|state-&gt;stats.inc_packets
op_increment
suffix:semicolon
id|state-&gt;stats.unc_bytes
op_add_assign
id|icnt
suffix:semicolon
id|state-&gt;stats.unc_packets
op_increment
suffix:semicolon
)brace
multiline_comment|/*************************************************************&n; * Module interface table&n; *************************************************************/
multiline_comment|/* These are in ppp.c */
r_extern
r_int
id|irda_register_compressor
(paren
r_struct
id|compressor
op_star
id|cp
)paren
suffix:semicolon
r_extern
r_void
id|irda_unregister_compressor
(paren
r_struct
id|compressor
op_star
id|cp
)paren
suffix:semicolon
multiline_comment|/*&n; * Procedures exported to if_ppp.c.&n; */
DECL|variable|irda_deflate
r_static
r_struct
id|compressor
id|irda_deflate
op_assign
(brace
id|CI_DEFLATE
comma
multiline_comment|/* compress_proto */
id|z_comp_alloc
comma
multiline_comment|/* comp_alloc */
id|z_comp_free
comma
multiline_comment|/* comp_free */
id|z_comp_init
comma
multiline_comment|/* comp_init */
id|z_comp_reset
comma
multiline_comment|/* comp_reset */
id|z_compress
comma
multiline_comment|/* compress */
id|z_comp_stats
comma
multiline_comment|/* comp_stat */
id|z_decomp_alloc
comma
multiline_comment|/* decomp_alloc */
id|z_decomp_free
comma
multiline_comment|/* decomp_free */
id|z_decomp_init
comma
multiline_comment|/* decomp_init */
id|z_decomp_reset
comma
multiline_comment|/* decomp_reset */
id|z_decompress
comma
multiline_comment|/* decompress */
id|z_incomp
comma
multiline_comment|/* incomp */
id|z_comp_stats
comma
multiline_comment|/* decomp_stat */
)brace
suffix:semicolon
DECL|variable|irda_deflate_draft
r_static
r_struct
id|compressor
id|irda_deflate_draft
op_assign
(brace
id|CI_DEFLATE_DRAFT
comma
multiline_comment|/* compress_proto */
id|z_comp_alloc
comma
multiline_comment|/* comp_alloc */
id|z_comp_free
comma
multiline_comment|/* comp_free */
id|z_comp_init
comma
multiline_comment|/* comp_init */
id|z_comp_reset
comma
multiline_comment|/* comp_reset */
id|z_compress
comma
multiline_comment|/* compress */
id|z_comp_stats
comma
multiline_comment|/* comp_stat */
id|z_decomp_alloc
comma
multiline_comment|/* decomp_alloc */
id|z_decomp_free
comma
multiline_comment|/* decomp_free */
id|z_decomp_init
comma
multiline_comment|/* decomp_init */
id|z_decomp_reset
comma
multiline_comment|/* decomp_reset */
id|z_decompress
comma
multiline_comment|/* decompress */
id|z_incomp
comma
multiline_comment|/* incomp */
id|z_comp_stats
comma
multiline_comment|/* decomp_stat */
)brace
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|irda_deflate_init
c_func
(paren
r_void
)paren
)paren
(brace
r_int
id|answer
op_assign
id|irda_register_compressor
(paren
op_amp
id|irda_deflate
)paren
suffix:semicolon
r_if
c_cond
(paren
id|answer
op_eq
l_int|0
)paren
id|printk
(paren
id|KERN_INFO
l_string|&quot;IrDA Deflate Compression module registered&bslash;n&quot;
)paren
suffix:semicolon
id|irda_register_compressor
c_func
(paren
op_amp
id|irda_deflate_draft
)paren
suffix:semicolon
r_return
id|answer
suffix:semicolon
)brace
DECL|function|irda_deflate_cleanup
r_void
id|irda_deflate_cleanup
c_func
(paren
r_void
)paren
(brace
id|irda_unregister_compressor
(paren
op_amp
id|irda_deflate
)paren
suffix:semicolon
id|irda_unregister_compressor
(paren
op_amp
id|irda_deflate_draft
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
multiline_comment|/*************************************************************&n; * Module support routines&n; *************************************************************/
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|irda_deflate_init
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|cleanup_module
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|MOD_IN_USE
)paren
id|printk
(paren
id|KERN_INFO
l_string|&quot;Deflate Compression module busy, remove delayed&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|irda_deflate_cleanup
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
