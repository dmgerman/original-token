multiline_comment|/* $Id: cgthree.c,v 1.16 1997/04/10 03:02:41 davem Exp $&n; * cgtree.c: cg3 frame buffer driver&n; *&n; * Copyright (C) 1996 Miguel de Icaza (miguel@nuclecu.unam.mx)&n; * Copyright (C) 1996 Jakub Jelinek   (jj@sunsite.mff.cuni.cz)&n; * Copyright (C) 1997 Eddie C. Dost   (ecd@skynet.be)&n; *&n; * Support for cgRDI added, Nov/96, jj.&n; */
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/fbio.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &quot;../../char/vt_kern.h&quot;
macro_line|#include &quot;../../char/selection.h&quot;
macro_line|#include &quot;../../char/console_struct.h&quot;
macro_line|#include &quot;fb.h&quot;
macro_line|#include &quot;cg_common.h&quot;
multiline_comment|/* Control Register Constants */
DECL|macro|CG3_CR_ENABLE_INTS
mdefine_line|#define CG3_CR_ENABLE_INTS&t;0x80
DECL|macro|CG3_CR_ENABLE_VIDEO
mdefine_line|#define CG3_CR_ENABLE_VIDEO&t;0x40
DECL|macro|CG3_CR_ENABLE_TIMING
mdefine_line|#define CG3_CR_ENABLE_TIMING&t;0x20
DECL|macro|CG3_CR_ENABLE_CURCMP
mdefine_line|#define CG3_CR_ENABLE_CURCMP&t;0x10
DECL|macro|CG3_CR_XTAL_MASK
mdefine_line|#define CG3_CR_XTAL_MASK&t;0x0c
DECL|macro|CG3_CR_DIVISOR_MASK
mdefine_line|#define CG3_CR_DIVISOR_MASK&t;0x03
multiline_comment|/* Status Register Constants */
DECL|macro|CG3_SR_PENDING_INT
mdefine_line|#define CG3_SR_PENDING_INT&t;0x80
DECL|macro|CG3_SR_RES_MASK
mdefine_line|#define CG3_SR_RES_MASK&t;&t;0x70
DECL|macro|CG3_SR_1152_900_76_A
mdefine_line|#define CG3_SR_1152_900_76_A&t;0x40
DECL|macro|CG3_SR_1152_900_76_B
mdefine_line|#define CG3_SR_1152_900_76_B&t;0x60
DECL|macro|CG3_SR_ID_MASK
mdefine_line|#define CG3_SR_ID_MASK&t;&t;0x0f
DECL|macro|CG3_SR_ID_COLOR
mdefine_line|#define CG3_SR_ID_COLOR&t;&t;0x01
DECL|macro|CG3_SR_ID_MONO
mdefine_line|#define CG3_SR_ID_MONO&t;&t;0x02
DECL|macro|CG3_SR_ID_MONO_ECL
mdefine_line|#define CG3_SR_ID_MONO_ECL&t;0x03
DECL|enum|cg3_type
r_enum
id|cg3_type
(brace
DECL|enumerator|CG3_AT_66HZ
id|CG3_AT_66HZ
op_assign
l_int|0
comma
DECL|enumerator|CG3_AT_76HZ
id|CG3_AT_76HZ
comma
DECL|enumerator|CG3_RDI
id|CG3_RDI
)brace
suffix:semicolon
DECL|struct|cg3_regs
r_struct
id|cg3_regs
(brace
DECL|member|cmap
r_struct
id|bt_regs
id|cmap
suffix:semicolon
DECL|member|control
r_volatile
id|u8
id|control
suffix:semicolon
DECL|member|status
r_volatile
id|u8
id|status
suffix:semicolon
DECL|member|cursor_start
r_volatile
id|u8
id|cursor_start
suffix:semicolon
DECL|member|cursor_end
r_volatile
id|u8
id|cursor_end
suffix:semicolon
DECL|member|h_blank_start
r_volatile
id|u8
id|h_blank_start
suffix:semicolon
DECL|member|h_blank_end
r_volatile
id|u8
id|h_blank_end
suffix:semicolon
DECL|member|h_sync_start
r_volatile
id|u8
id|h_sync_start
suffix:semicolon
DECL|member|h_sync_end
r_volatile
id|u8
id|h_sync_end
suffix:semicolon
DECL|member|comp_sync_end
r_volatile
id|u8
id|comp_sync_end
suffix:semicolon
DECL|member|v_blank_start_high
r_volatile
id|u8
id|v_blank_start_high
suffix:semicolon
DECL|member|v_blank_start_low
r_volatile
id|u8
id|v_blank_start_low
suffix:semicolon
DECL|member|v_blank_end
r_volatile
id|u8
id|v_blank_end
suffix:semicolon
DECL|member|v_sync_start
r_volatile
id|u8
id|v_sync_start
suffix:semicolon
DECL|member|v_sync_end
r_volatile
id|u8
id|v_sync_end
suffix:semicolon
DECL|member|xfer_holdoff_start
r_volatile
id|u8
id|xfer_holdoff_start
suffix:semicolon
DECL|member|xfer_holdoff_end
r_volatile
id|u8
id|xfer_holdoff_end
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The cg3 palette is loaded with 4 color values at each time  */
multiline_comment|/* so you end up with: (rgb)(r), (gb)(rg), (b)(rgb), and so on */
r_static
r_void
DECL|function|cg3_loadcmap
id|cg3_loadcmap
(paren
id|fbinfo_t
op_star
id|fb
comma
r_int
id|index
comma
r_int
id|count
)paren
(brace
r_struct
id|bt_regs
op_star
id|bt
op_assign
op_amp
id|fb-&gt;info.cg3.regs-&gt;cmap
suffix:semicolon
r_int
op_star
id|i
comma
id|steps
suffix:semicolon
id|i
op_assign
(paren
(paren
(paren
r_int
op_star
)paren
id|fb-&gt;color_map
)paren
op_plus
id|D4M3
c_func
(paren
id|index
)paren
)paren
suffix:semicolon
id|steps
op_assign
id|D4M3
c_func
(paren
id|index
op_plus
id|count
op_minus
l_int|1
)paren
op_minus
id|D4M3
c_func
(paren
id|index
)paren
op_plus
l_int|3
suffix:semicolon
op_star
(paren
r_volatile
id|u8
op_star
)paren
op_amp
id|bt-&gt;addr
op_assign
(paren
id|u8
)paren
id|D4M4
c_func
(paren
id|index
)paren
suffix:semicolon
r_while
c_loop
(paren
id|steps
op_decrement
)paren
id|bt-&gt;color_map
op_assign
op_star
id|i
op_increment
suffix:semicolon
)brace
multiline_comment|/* The cg3 is presumed to emulate a cg4, I guess older programs will want that&n; * addresses above 0x4000000 are for cg3, below that it&squot;s cg4 emulation.&n; */
r_static
r_int
DECL|function|cg3_mmap
id|cg3_mmap
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
id|uint
id|size
comma
id|page
comma
id|r
comma
id|map_size
suffix:semicolon
id|uint
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
id|CG3_MMAP_OFFSET
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
id|uint
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
id|vma-&gt;vm_inode
op_assign
id|inode
suffix:semicolon
id|inode-&gt;i_count
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|cg3_blank
id|cg3_blank
(paren
id|fbinfo_t
op_star
id|fb
)paren
(brace
id|fb-&gt;info.cg3.regs-&gt;control
op_and_assign
op_complement
id|CG3_CR_ENABLE_VIDEO
suffix:semicolon
)brace
r_static
r_void
DECL|function|cg3_unblank
id|cg3_unblank
(paren
id|fbinfo_t
op_star
id|fb
)paren
(brace
id|fb-&gt;info.cg3.regs-&gt;control
op_or_assign
id|CG3_CR_ENABLE_VIDEO
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
id|u8
id|cg3regvals_66hz
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* 1152 x 900, 66 Hz */
l_int|0x14
comma
l_int|0xbb
comma
l_int|0x15
comma
l_int|0x2b
comma
l_int|0x16
comma
l_int|0x04
comma
l_int|0x17
comma
l_int|0x14
comma
l_int|0x18
comma
l_int|0xae
comma
l_int|0x19
comma
l_int|0x03
comma
l_int|0x1a
comma
l_int|0xa8
comma
l_int|0x1b
comma
l_int|0x24
comma
l_int|0x1c
comma
l_int|0x01
comma
l_int|0x1d
comma
l_int|0x05
comma
l_int|0x1e
comma
l_int|0xff
comma
l_int|0x1f
comma
l_int|0x01
comma
l_int|0x10
comma
l_int|0x20
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|u8
id|cg3regvals_76hz
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* 1152 x 900, 76 Hz */
l_int|0x14
comma
l_int|0xb7
comma
l_int|0x15
comma
l_int|0x27
comma
l_int|0x16
comma
l_int|0x03
comma
l_int|0x17
comma
l_int|0x0f
comma
l_int|0x18
comma
l_int|0xae
comma
l_int|0x19
comma
l_int|0x03
comma
l_int|0x1a
comma
l_int|0xae
comma
l_int|0x1b
comma
l_int|0x2a
comma
l_int|0x1c
comma
l_int|0x01
comma
l_int|0x1d
comma
l_int|0x09
comma
l_int|0x1e
comma
l_int|0xff
comma
l_int|0x1f
comma
l_int|0x01
comma
l_int|0x10
comma
l_int|0x24
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|u8
id|cg3regvals_rdi
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* 640 x 480, cgRDI */
l_int|0x14
comma
l_int|0x70
comma
l_int|0x15
comma
l_int|0x20
comma
l_int|0x16
comma
l_int|0x08
comma
l_int|0x17
comma
l_int|0x10
comma
l_int|0x18
comma
l_int|0x06
comma
l_int|0x19
comma
l_int|0x02
comma
l_int|0x1a
comma
l_int|0x31
comma
l_int|0x1b
comma
l_int|0x51
comma
l_int|0x1c
comma
l_int|0x06
comma
l_int|0x1d
comma
l_int|0x0c
comma
l_int|0x1e
comma
l_int|0xff
comma
l_int|0x1f
comma
l_int|0x01
comma
l_int|0x10
comma
l_int|0x22
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|u8
op_star
id|cg3_regvals
(braket
)braket
id|__initdata
op_assign
(brace
id|cg3regvals_66hz
comma
id|cg3regvals_76hz
comma
id|cg3regvals_rdi
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
id|u_char
id|cg3_dacvals
(braket
)braket
id|__initdata
op_assign
(brace
l_int|4
comma
l_int|0xff
comma
l_int|5
comma
l_int|0x00
comma
l_int|6
comma
l_int|0x70
comma
l_int|7
comma
l_int|0x00
comma
l_int|0
)brace
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|cg3_setup
(paren
id|fbinfo_t
op_star
id|fb
comma
r_int
id|slot
comma
r_int
r_int
id|cg3
comma
r_int
id|cg3_io
comma
r_struct
id|linux_sbus_device
op_star
id|sbdp
)paren
)paren
(brace
r_struct
id|cg3_info
op_star
id|cg3info
op_assign
(paren
r_struct
id|cg3_info
op_star
)paren
op_amp
id|fb-&gt;info.cg3
suffix:semicolon
r_if
c_cond
(paren
id|strstr
(paren
id|sbdp-&gt;prom_name
comma
l_string|&quot;cgRDI&quot;
)paren
)paren
(brace
r_char
id|buffer
(braket
l_int|40
)braket
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_int
id|w
comma
id|h
suffix:semicolon
id|prom_getstring
(paren
id|sbdp-&gt;prom_node
comma
l_string|&quot;params&quot;
comma
id|buffer
comma
r_sizeof
(paren
id|buffer
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|buffer
)paren
(brace
id|w
op_assign
id|simple_strtoul
(paren
id|buffer
comma
op_amp
id|p
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|w
op_logical_and
op_star
id|p
op_eq
l_char|&squot;x&squot;
)paren
(brace
id|h
op_assign
id|simple_strtoul
(paren
id|p
op_plus
l_int|1
comma
op_amp
id|p
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|h
op_logical_and
op_star
id|p
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|fb-&gt;type.fb_width
op_assign
id|w
suffix:semicolon
id|fb-&gt;type.fb_height
op_assign
id|h
suffix:semicolon
)brace
)brace
)brace
id|printk
(paren
l_string|&quot;cgRDI%d at 0x%8.8x&bslash;n&quot;
comma
id|slot
comma
(paren
id|uint
)paren
id|cg3
)paren
suffix:semicolon
id|cg3info-&gt;cgrdi
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|printk
(paren
l_string|&quot;cgthree%d at 0x%8.8x&bslash;n&quot;
comma
id|slot
comma
(paren
id|uint
)paren
id|cg3
)paren
suffix:semicolon
id|cg3info-&gt;cgrdi
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Fill in parameters we left out */
id|fb-&gt;type.fb_cmsize
op_assign
l_int|256
suffix:semicolon
id|fb-&gt;mmap
op_assign
id|cg3_mmap
suffix:semicolon
id|fb-&gt;loadcmap
op_assign
id|cg3_loadcmap
suffix:semicolon
id|fb-&gt;postsetup
op_assign
id|sun_cg_postsetup
suffix:semicolon
id|fb-&gt;ioctl
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* no special ioctls */
id|fb-&gt;reset
op_assign
l_int|0
suffix:semicolon
id|fb-&gt;blank
op_assign
id|cg3_blank
suffix:semicolon
id|fb-&gt;unblank
op_assign
id|cg3_unblank
suffix:semicolon
multiline_comment|/* Map the card registers */
id|cg3info-&gt;regs
op_assign
id|sparc_alloc_io
(paren
(paren
id|u32
)paren
(paren
id|cg3
op_plus
id|CG3_REGS
)paren
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|cg3_regs
)paren
comma
l_string|&quot;cg3_regs&quot;
comma
id|cg3_io
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prom_getbool
c_func
(paren
id|sbdp-&gt;prom_node
comma
l_string|&quot;width&quot;
)paren
)paren
(brace
multiline_comment|/* Ugh, broken PROM didn&squot;t initialize us.&n;&t;&t; * Let&squot;s deal with this ourselves.&n;&t;&t; */
id|u8
id|status
comma
id|mon
suffix:semicolon
r_enum
id|cg3_type
id|type
suffix:semicolon
id|u8
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|cg3info-&gt;cgrdi
)paren
(brace
id|type
op_assign
id|CG3_RDI
suffix:semicolon
)brace
r_else
(brace
id|status
op_assign
id|cg3info-&gt;regs-&gt;status
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
id|CG3_SR_ID_MASK
)paren
op_eq
id|CG3_SR_ID_COLOR
)paren
(brace
id|mon
op_assign
id|status
op_amp
id|CG3_SR_RES_MASK
suffix:semicolon
r_if
c_cond
(paren
id|mon
op_eq
id|CG3_SR_1152_900_76_A
op_logical_or
id|mon
op_eq
id|CG3_SR_1152_900_76_B
)paren
id|type
op_assign
id|CG3_AT_76HZ
suffix:semicolon
r_else
id|type
op_assign
id|CG3_AT_66HZ
suffix:semicolon
)brace
r_else
(brace
id|prom_printf
c_func
(paren
l_string|&quot;cgthree: can&squot;t handle SR %02x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* fool gcc. */
)brace
)brace
r_for
c_loop
(paren
id|p
op_assign
id|cg3_regvals
(braket
id|type
)braket
suffix:semicolon
op_star
id|p
suffix:semicolon
id|p
op_add_assign
l_int|2
)paren
(paren
(paren
id|u8
op_star
)paren
id|cg3info-&gt;regs
)paren
(braket
id|p
(braket
l_int|0
)braket
)braket
op_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|cg3_dacvals
suffix:semicolon
op_star
id|p
suffix:semicolon
id|p
op_add_assign
l_int|2
)paren
(brace
op_star
(paren
r_volatile
id|u8
op_star
)paren
op_amp
id|cg3info-&gt;regs-&gt;cmap.addr
op_assign
id|p
(braket
l_int|0
)braket
suffix:semicolon
op_star
(paren
r_volatile
id|u8
op_star
)paren
op_amp
id|cg3info-&gt;regs-&gt;cmap.control
op_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|fb-&gt;base
)paren
(brace
id|fb-&gt;base
op_assign
(paren
id|uint
)paren
id|sparc_alloc_io
(paren
(paren
id|u32
)paren
(paren
id|cg3
op_plus
id|CG3_RAM
)paren
comma
l_int|0
comma
id|fb-&gt;type.fb_size
comma
l_string|&quot;cg3_ram&quot;
comma
id|cg3_io
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
eof
