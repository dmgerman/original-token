multiline_comment|/* $Id: weitek.c,v 1.15 1997/07/22 06:14:11 davem Exp $&n; * weitek.c: Tadpole P9100/P9000 console driver&n; *&n; * Copyright (C) 1996 David Redman (djhr@tadpole.co.uk)&n; */
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/fbio.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/* These must be included after asm/fbio.h */
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;linux/selection.h&gt;
macro_line|#include &lt;linux/console_struct.h&gt;
macro_line|#include &quot;fb.h&quot;
macro_line|#include &quot;cg_common.h&quot;
multiline_comment|/*&n; * mmap info&n; */
DECL|macro|WEITEK_VRAM_OFFSET
mdefine_line|#define WEITEK_VRAM_OFFSET&t;0
DECL|macro|WEITEK_VRAM_SIZE
mdefine_line|#define WEITEK_VRAM_SIZE&t;(2*1024*1024)&t;/* maximum */
DECL|macro|WEITEK_GX_REG_OFFSET
mdefine_line|#define WEITEK_GX_REG_OFFSET&t;WEITEK_VRAM_SIZE
DECL|macro|WEITEK_GX_REG_SIZE
mdefine_line|#define WEITEK_GX_REG_SIZE&t;8192
DECL|macro|WEITEK_VID_REG_OFFSET
mdefine_line|#define WEITEK_VID_REG_OFFSET&t;(WEITEK_GX_REG_OFFSET+WEITEK_GX_REG_SIZE)
DECL|macro|WEITEK_VID_REG_SIZE
mdefine_line|#define WEITEK_VID_REG_SIZE&t;0x1000
DECL|macro|CONTROL_OFFSET
mdefine_line|#define CONTROL_OFFSET&t;0
DECL|macro|RAMDAC_OFFSET
mdefine_line|#define RAMDAC_OFFSET&t;(CONTROL_OFFSET+0x200)
macro_line|#if 0
r_static
r_int
id|weitek_mmap
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
id|base
comma
id|fbinfo_t
op_star
id|fb
)paren
(brace
r_int
r_int
id|size
comma
id|page
comma
id|r
comma
id|map_size
suffix:semicolon
r_int
r_int
id|map_offset
op_assign
l_int|0
suffix:semicolon
id|size
op_assign
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_offset
op_amp
op_complement
id|PAGE_MASK
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/* To stop the swapper from even considering these pages */
id|vma-&gt;vm_flags
op_or_assign
id|FB_MMAP_VM_FLAGS
suffix:semicolon
multiline_comment|/* Each page, see which map applies */
r_for
c_loop
(paren
id|page
op_assign
l_int|0
suffix:semicolon
id|page
OL
id|size
suffix:semicolon
)paren
(brace
r_switch
c_cond
(paren
id|vma-&gt;vm_offset
op_plus
id|page
)paren
(brace
r_case
id|WEITEK_VRAM_OFFSET
suffix:colon
id|map_size
op_assign
id|size
op_minus
id|page
suffix:semicolon
id|map_offset
op_assign
id|get_phys
(paren
(paren
r_int
r_int
)paren
id|fb-&gt;base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map_size
OG
id|fb-&gt;type.fb_size
)paren
id|map_size
op_assign
id|fb-&gt;type.fb_size
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WEITEK_GX_REG_OFFSET
suffix:colon
id|map_size
op_assign
id|size
op_minus
id|page
suffix:semicolon
id|map_offset
op_assign
id|get_phys
(paren
(paren
r_int
r_int
)paren
id|fb-&gt;base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map_size
OG
id|fb-&gt;type.fb_size
)paren
id|map_size
op_assign
id|fb-&gt;type.fb_size
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|map_size
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|map_size
)paren
(brace
id|page
op_add_assign
id|PAGE_SIZE
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|page
op_plus
id|map_size
OG
id|size
)paren
id|map_size
op_assign
id|size
op_minus
id|page
suffix:semicolon
id|r
op_assign
id|io_remap_page_range
(paren
id|vma-&gt;vm_start
op_plus
id|page
comma
id|map_offset
comma
id|map_size
comma
id|vma-&gt;vm_page_prot
comma
id|fb-&gt;space
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|page
op_add_assign
id|map_size
suffix:semicolon
)brace
id|vma-&gt;vm_dentry
op_assign
id|dget
c_func
(paren
id|file-&gt;f_dentry
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if 0
r_static
r_void
id|weitek_loadcmap
(paren
r_void
op_star
id|fbinfo
comma
r_int
id|index
comma
r_int
id|count
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;weitek_cmap: unimplemented!&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|weitek_setup
c_func
(paren
id|fbinfo_t
op_star
id|fb
comma
r_int
id|slot
comma
id|u32
id|addr
comma
r_int
id|io
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;weitek%d at 0x%8.8x&bslash;n&quot;
comma
id|slot
comma
id|addr
)paren
suffix:semicolon
multiline_comment|/* Fill in parameters we left out */
id|fb-&gt;type.fb_type
op_assign
id|FBTYPE_NOTSUN1
suffix:semicolon
id|fb-&gt;type.fb_cmsize
op_assign
l_int|256
suffix:semicolon
id|fb-&gt;mmap
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* weitek_mmap; */
id|fb-&gt;loadcmap
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* unimplemented */
id|fb-&gt;ioctl
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* no special ioctls */
id|fb-&gt;reset
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* no special reset */
multiline_comment|/* Map the card registers */
r_if
c_cond
(paren
op_logical_neg
id|fb-&gt;base
)paren
(brace
id|prom_printf
(paren
l_string|&quot;Missing mapping routine and no address found&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
eof
