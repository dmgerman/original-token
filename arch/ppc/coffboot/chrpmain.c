multiline_comment|/*&n; * Copyright (C) Paul Mackerras 1997.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &quot;nonstdio.h&quot;
macro_line|#include &quot;zlib.h&quot;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/page.h&gt;
r_extern
r_void
op_star
id|finddevice
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|getprop
c_func
(paren
r_void
op_star
comma
r_const
r_char
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|make_bi_recs
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_void
id|gunzip
c_func
(paren
r_void
op_star
comma
r_int
comma
r_int
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_void
id|stop_imac_ethernet
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|stop_imac_usb
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|get_16be
mdefine_line|#define get_16be(x)&t;(*(unsigned short *)(x))
DECL|macro|get_32be
mdefine_line|#define get_32be(x)&t;(*(unsigned *)(x))
DECL|macro|RAM_START
mdefine_line|#define RAM_START&t;0x00000000
DECL|macro|RAM_END
mdefine_line|#define RAM_END&t;&t;(8&lt;&lt;20)
DECL|macro|PROG_START
mdefine_line|#define PROG_START&t;0x00010000
DECL|variable|avail_ram
r_char
op_star
id|avail_ram
suffix:semicolon
DECL|variable|end_avail
r_char
op_star
id|end_avail
suffix:semicolon
r_extern
r_char
id|_end
(braket
)braket
suffix:semicolon
r_extern
r_char
id|image_data
(braket
)braket
suffix:semicolon
r_extern
r_int
id|image_len
suffix:semicolon
r_extern
r_char
id|initrd_data
(braket
)braket
suffix:semicolon
r_extern
r_int
id|initrd_len
suffix:semicolon
DECL|function|boot
id|boot
c_func
(paren
r_int
id|a1
comma
r_int
id|a2
comma
r_void
op_star
id|prom
)paren
(brace
r_int
id|ns
comma
id|oh
comma
id|i
suffix:semicolon
r_int
id|sa
comma
id|len
suffix:semicolon
r_void
op_star
id|dst
suffix:semicolon
r_int
r_char
op_star
id|im
suffix:semicolon
r_int
id|initrd_start
comma
id|initrd_size
suffix:semicolon
r_extern
r_char
id|_start
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;chrpboot starting: loaded at 0x%x&bslash;n&quot;
comma
op_amp
id|_start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|initrd_len
)paren
(brace
id|initrd_size
op_assign
id|initrd_len
suffix:semicolon
id|initrd_start
op_assign
(paren
id|RAM_END
op_minus
id|initrd_size
)paren
op_amp
op_complement
l_int|0xFFF
suffix:semicolon
id|a1
op_assign
id|initrd_start
suffix:semicolon
id|a2
op_assign
id|initrd_size
suffix:semicolon
id|claim
c_func
(paren
id|initrd_start
comma
id|RAM_END
op_minus
id|initrd_start
comma
l_int|0
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;initial ramdisk moving 0x%x &lt;- 0x%x (%x bytes)&bslash;n&quot;
comma
id|initrd_start
comma
id|initrd_data
comma
id|initrd_size
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|initrd_start
comma
id|initrd_data
comma
id|initrd_size
)paren
suffix:semicolon
)brace
id|im
op_assign
id|image_data
suffix:semicolon
id|len
op_assign
id|image_len
suffix:semicolon
multiline_comment|/* claim 3MB starting at PROG_START */
id|claim
c_func
(paren
id|PROG_START
comma
l_int|3
op_lshift
l_int|20
comma
l_int|0
)paren
suffix:semicolon
id|dst
op_assign
(paren
r_void
op_star
)paren
id|PROG_START
suffix:semicolon
r_if
c_cond
(paren
id|im
(braket
l_int|0
)braket
op_eq
l_int|0x1f
op_logical_and
id|im
(braket
l_int|1
)braket
op_eq
l_int|0x8b
)paren
(brace
multiline_comment|/* claim 512kB for scratch space */
id|avail_ram
op_assign
(paren
r_char
op_star
)paren
id|claim
c_func
(paren
l_int|0
comma
l_int|512
op_lshift
l_int|10
comma
l_int|0x10
)paren
suffix:semicolon
id|end_avail
op_assign
id|avail_ram
op_plus
(paren
l_int|512
op_lshift
l_int|10
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;avail_ram = %x&bslash;n&quot;
comma
id|avail_ram
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;gunzipping (0x%x &lt;- 0x%x:0x%0x)...&quot;
comma
id|dst
comma
id|im
comma
id|im
op_plus
id|len
)paren
suffix:semicolon
id|gunzip
c_func
(paren
id|dst
comma
l_int|3
op_lshift
l_int|20
comma
id|im
comma
op_amp
id|len
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;done %u bytes&bslash;n&quot;
comma
id|len
)paren
suffix:semicolon
)brace
r_else
(brace
id|memmove
c_func
(paren
id|dst
comma
id|im
comma
id|len
)paren
suffix:semicolon
)brace
id|flush_cache
c_func
(paren
id|dst
comma
id|len
)paren
suffix:semicolon
id|stop_imac_ethernet
c_func
(paren
)paren
suffix:semicolon
id|stop_imac_usb
c_func
(paren
)paren
suffix:semicolon
id|make_bi_recs
c_func
(paren
(paren
r_int
r_int
)paren
id|dst
op_plus
id|len
)paren
suffix:semicolon
id|sa
op_assign
(paren
r_int
r_int
)paren
id|PROG_START
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;start address = 0x%x&bslash;n&quot;
comma
id|sa
)paren
suffix:semicolon
(paren
op_star
(paren
r_void
(paren
op_star
)paren
(paren
)paren
)paren
id|sa
)paren
(paren
l_int|0
comma
l_int|0
comma
id|prom
comma
id|a1
comma
id|a2
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;returned?&bslash;n&quot;
)paren
suffix:semicolon
id|pause
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|make_bi_recs
r_void
id|make_bi_recs
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_struct
id|bi_record
op_star
id|rec
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
id|_ALIGN
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
op_plus
(paren
l_int|1
op_lshift
l_int|20
)paren
op_minus
l_int|1
comma
(paren
l_int|1
op_lshift
l_int|20
)paren
)paren
suffix:semicolon
id|rec-&gt;tag
op_assign
id|BI_FIRST
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
id|rec-&gt;tag
op_assign
id|BI_BOOTLOADER_ID
suffix:semicolon
id|sprintf
c_func
(paren
(paren
r_char
op_star
)paren
id|rec-&gt;data
comma
l_string|&quot;coffboot&quot;
)paren
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
op_plus
id|strlen
c_func
(paren
l_string|&quot;coffboot&quot;
)paren
op_plus
l_int|1
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
id|rec-&gt;tag
op_assign
id|BI_MACHTYPE
suffix:semicolon
id|rec-&gt;data
(braket
l_int|0
)braket
op_assign
id|_MACH_Pmac
suffix:semicolon
id|rec-&gt;data
(braket
l_int|1
)braket
op_assign
l_int|1
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
op_plus
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
macro_line|#ifdef SYSMAP_OFFSET
id|rec-&gt;tag
op_assign
id|BI_SYSMAP
suffix:semicolon
id|rec-&gt;data
(braket
l_int|0
)braket
op_assign
id|SYSMAP_OFFSET
suffix:semicolon
id|rec-&gt;data
(braket
l_int|1
)braket
op_assign
id|SYSMAP_SIZE
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
op_plus
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
macro_line|#endif /* SYSMAP_OFFSET */
id|rec-&gt;tag
op_assign
id|BI_LAST
suffix:semicolon
id|rec-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|bi_record
)paren
suffix:semicolon
id|rec
op_assign
(paren
r_struct
id|bi_record
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|rec
op_plus
id|rec-&gt;size
)paren
suffix:semicolon
)brace
DECL|macro|eieio
mdefine_line|#define eieio()&t;asm volatile(&quot;eieio&quot;);
DECL|function|stop_imac_ethernet
r_void
id|stop_imac_ethernet
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|macio
comma
op_star
id|enet
suffix:semicolon
r_int
r_int
id|macio_addr
(braket
l_int|5
)braket
comma
id|enet_reg
(braket
l_int|6
)braket
suffix:semicolon
r_int
id|len
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|dbdma
suffix:semicolon
id|macio
op_assign
id|finddevice
c_func
(paren
l_string|&quot;/pci/mac-io&quot;
)paren
suffix:semicolon
id|enet
op_assign
id|finddevice
c_func
(paren
l_string|&quot;/pci/mac-io/ethernet&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|macio
op_eq
l_int|NULL
op_logical_or
id|enet
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|len
op_assign
id|getprop
c_func
(paren
id|macio
comma
l_string|&quot;assigned-addresses&quot;
comma
id|macio_addr
comma
r_sizeof
(paren
id|macio_addr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ne
r_sizeof
(paren
id|macio_addr
)paren
)paren
r_return
suffix:semicolon
id|len
op_assign
id|getprop
c_func
(paren
id|enet
comma
l_string|&quot;reg&quot;
comma
id|enet_reg
comma
r_sizeof
(paren
id|enet_reg
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ne
r_sizeof
(paren
id|enet_reg
)paren
)paren
r_return
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;macio base %x, dma at %x &amp; %x&bslash;n&quot;
comma
id|macio_addr
(braket
l_int|2
)braket
comma
id|enet_reg
(braket
l_int|2
)braket
comma
id|enet_reg
(braket
l_int|4
)braket
)paren
suffix:semicolon
multiline_comment|/* hope this is mapped... */
id|dbdma
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|macio_addr
(braket
l_int|2
)braket
op_plus
id|enet_reg
(braket
l_int|2
)braket
)paren
suffix:semicolon
op_star
id|dbdma
op_assign
l_int|0x80
suffix:semicolon
multiline_comment|/* clear the RUN bit */
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|dbdma
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|macio_addr
(braket
l_int|2
)braket
op_plus
id|enet_reg
(braket
l_int|4
)braket
)paren
suffix:semicolon
op_star
id|dbdma
op_assign
l_int|0x80
suffix:semicolon
multiline_comment|/* clear the RUN bit */
id|eieio
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|stop_imac_usb
r_void
id|stop_imac_usb
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|usb
suffix:semicolon
r_int
r_int
id|usb_addr
(braket
l_int|5
)braket
suffix:semicolon
r_int
id|len
suffix:semicolon
r_volatile
r_int
r_int
op_star
id|usb_ctrl
suffix:semicolon
id|usb
op_assign
id|finddevice
c_func
(paren
l_string|&quot;/pci/usb&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usb
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|len
op_assign
id|getprop
c_func
(paren
id|usb
comma
l_string|&quot;assigned-addresses&quot;
comma
id|usb_addr
comma
r_sizeof
(paren
id|usb_addr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ne
r_sizeof
(paren
id|usb_addr
)paren
)paren
r_return
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;usb base %x&bslash;n&quot;
comma
id|usb_addr
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|usb_ctrl
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|usb_addr
(braket
l_int|2
)braket
op_plus
l_int|8
)paren
suffix:semicolon
op_star
id|usb_ctrl
op_assign
l_int|0x01000000
suffix:semicolon
multiline_comment|/* cpu_to_le32(1) */
id|eieio
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|zalloc
r_void
op_star
id|zalloc
c_func
(paren
r_void
op_star
id|x
comma
r_int
id|items
comma
r_int
id|size
)paren
(brace
r_void
op_star
id|p
op_assign
id|avail_ram
suffix:semicolon
id|size
op_mul_assign
id|items
suffix:semicolon
id|size
op_assign
(paren
id|size
op_plus
l_int|7
)paren
op_amp
op_minus
l_int|8
suffix:semicolon
id|avail_ram
op_add_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|avail_ram
OG
id|end_avail
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;oops... out of memory&bslash;n&quot;
)paren
suffix:semicolon
id|pause
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
DECL|function|zfree
r_void
id|zfree
c_func
(paren
r_void
op_star
id|x
comma
r_void
op_star
id|addr
comma
r_int
id|nb
)paren
(brace
)brace
DECL|macro|HEAD_CRC
mdefine_line|#define HEAD_CRC&t;2
DECL|macro|EXTRA_FIELD
mdefine_line|#define EXTRA_FIELD&t;4
DECL|macro|ORIG_NAME
mdefine_line|#define ORIG_NAME&t;8
DECL|macro|COMMENT
mdefine_line|#define COMMENT&t;&t;0x10
DECL|macro|RESERVED
mdefine_line|#define RESERVED&t;0xe0
DECL|macro|DEFLATED
mdefine_line|#define DEFLATED&t;8
DECL|function|gunzip
r_void
id|gunzip
c_func
(paren
r_void
op_star
id|dst
comma
r_int
id|dstlen
comma
r_int
r_char
op_star
id|src
comma
r_int
op_star
id|lenp
)paren
(brace
id|z_stream
id|s
suffix:semicolon
r_int
id|r
comma
id|i
comma
id|flags
suffix:semicolon
multiline_comment|/* skip header */
id|i
op_assign
l_int|10
suffix:semicolon
id|flags
op_assign
id|src
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|src
(braket
l_int|2
)braket
op_ne
id|DEFLATED
op_logical_or
(paren
id|flags
op_amp
id|RESERVED
)paren
op_ne
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;bad gzipped data&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|EXTRA_FIELD
)paren
op_ne
l_int|0
)paren
id|i
op_assign
l_int|12
op_plus
id|src
(braket
l_int|10
)braket
op_plus
(paren
id|src
(braket
l_int|11
)braket
op_lshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|ORIG_NAME
)paren
op_ne
l_int|0
)paren
r_while
c_loop
(paren
id|src
(braket
id|i
op_increment
)braket
op_ne
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|COMMENT
)paren
op_ne
l_int|0
)paren
r_while
c_loop
(paren
id|src
(braket
id|i
op_increment
)braket
op_ne
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|HEAD_CRC
)paren
op_ne
l_int|0
)paren
id|i
op_add_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
op_star
id|lenp
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;gunzip: ran out of data in header&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
)paren
suffix:semicolon
)brace
id|s.zalloc
op_assign
id|zalloc
suffix:semicolon
id|s.zfree
op_assign
id|zfree
suffix:semicolon
id|r
op_assign
id|inflateInit2
c_func
(paren
op_amp
id|s
comma
op_minus
id|MAX_WBITS
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
id|printf
c_func
(paren
l_string|&quot;inflateInit2 returned %d&bslash;n&quot;
comma
id|r
)paren
suffix:semicolon
m_exit
(paren
)paren
suffix:semicolon
)brace
id|s.next_in
op_assign
id|src
op_plus
id|i
suffix:semicolon
id|s.avail_in
op_assign
op_star
id|lenp
op_minus
id|i
suffix:semicolon
id|s.next_out
op_assign
id|dst
suffix:semicolon
id|s.avail_out
op_assign
id|dstlen
suffix:semicolon
id|r
op_assign
id|inflate
c_func
(paren
op_amp
id|s
comma
id|Z_FINISH
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_ne
id|Z_OK
op_logical_and
id|r
op_ne
id|Z_STREAM_END
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;inflate returned %d msg: %s&bslash;n&quot;
comma
id|r
comma
id|s.msg
)paren
suffix:semicolon
m_exit
(paren
)paren
suffix:semicolon
)brace
op_star
id|lenp
op_assign
id|s.next_out
op_minus
(paren
r_int
r_char
op_star
)paren
id|dst
suffix:semicolon
id|inflateEnd
c_func
(paren
op_amp
id|s
)paren
suffix:semicolon
)brace
eof
