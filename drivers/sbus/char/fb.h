multiline_comment|/* $Id: fb.h,v 1.24 1997/03/24 17:44:15 jj Exp $&n; * fb.h: contains the definitions of the structures that various sun&n; *       frame buffer can use to do console driver stuff.&n; *&n; * (C) 1996 Dave Redman     (djhr@tadpole.co.uk)&n; * (C) 1996 Miguel de Icaza (miguel@nuclecu.unam.mx)&n; * (C) 1996 David Miller    (davem@rutgers.edu)&n; * (C) 1996 Peter Zaitcev   (zaitcev@lab.ipmce.su)&n; * (C) 1996 Eddie C. Dost   (ecd@skynet.be)&n; * (C) 1996 Jakub Jelinek   (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#ifndef __SPARC_FB_H_
DECL|macro|__SPARC_FB_H_
mdefine_line|#define __SPARC_FB_H_
macro_line|#include &lt;linux/init.h&gt;
DECL|macro|FRAME_BUFFERS
mdefine_line|#define FRAME_BUFFERS    8
DECL|macro|CHAR_WIDTH
mdefine_line|#define CHAR_WIDTH&t; 8
DECL|macro|CHAR_HEIGHT
mdefine_line|#define CHAR_HEIGHT&t; 16
multiline_comment|/* Change this if we run into problems if the kernel want&squot;s to free or&n; * use our frame buffer pages, never seen it though.&n; */
DECL|macro|FB_MMAP_VM_FLAGS
mdefine_line|#define FB_MMAP_VM_FLAGS (VM_SHM| VM_LOCKED)
DECL|macro|color
macro_line|#undef color
multiline_comment|/* cursor status, kernel tracked copy */
DECL|struct|cg_cursor
r_struct
id|cg_cursor
(brace
DECL|member|enable
r_int
id|enable
suffix:semicolon
multiline_comment|/* cursor is enabled */
DECL|member|cpos
r_struct
id|fbcurpos
id|cpos
suffix:semicolon
multiline_comment|/* position */
DECL|member|chot
r_struct
id|fbcurpos
id|chot
suffix:semicolon
multiline_comment|/* hot-spot */
DECL|member|size
r_struct
id|fbcurpos
id|size
suffix:semicolon
multiline_comment|/* size of mask &amp; image fields */
DECL|member|hwsize
r_struct
id|fbcurpos
id|hwsize
suffix:semicolon
multiline_comment|/* hw max size */
DECL|member|bits
r_int
id|bits
(braket
l_int|2
)braket
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* space for mask &amp; image bits */
DECL|member|color
r_char
id|color
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* cursor colors */
)brace
suffix:semicolon
DECL|struct|cg6_info
r_struct
id|cg6_info
(brace
DECL|member|bt
r_struct
id|bt_regs
op_star
id|bt
suffix:semicolon
multiline_comment|/* color control */
DECL|member|fbc
r_struct
id|cg6_fbc
op_star
id|fbc
suffix:semicolon
DECL|member|fhc
r_int
r_int
op_star
id|fhc
suffix:semicolon
DECL|member|tec
r_struct
id|cg6_tec
op_star
id|tec
suffix:semicolon
DECL|member|thc
r_struct
id|cg6_thc
op_star
id|thc
suffix:semicolon
DECL|member|dhc
r_void
op_star
id|dhc
suffix:semicolon
DECL|member|rom
r_int
r_char
op_star
id|rom
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|tcx_info
r_struct
id|tcx_info
(brace
DECL|member|bt
r_struct
id|bt_regs
op_star
id|bt
suffix:semicolon
multiline_comment|/* color control */
DECL|member|tec
r_struct
id|tcx_tec
op_star
id|tec
suffix:semicolon
DECL|member|thc
r_struct
id|tcx_thc
op_star
id|thc
suffix:semicolon
DECL|member|tcx_cplane
r_void
op_star
id|tcx_cplane
suffix:semicolon
DECL|member|tcx_sizes
r_int
id|tcx_sizes
(braket
l_int|13
)braket
suffix:semicolon
DECL|member|tcx_offsets
r_int
id|tcx_offsets
(braket
l_int|13
)braket
suffix:semicolon
DECL|member|lowdepth
r_int
id|lowdepth
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|leo_info
r_struct
id|leo_info
(brace
DECL|member|cursor
r_struct
id|leo_cursor
op_star
id|cursor
suffix:semicolon
DECL|member|lc_ss0_krn
r_struct
id|leo_lc_ss0_krn
op_star
id|lc_ss0_krn
suffix:semicolon
DECL|member|lc_ss0_usr
r_struct
id|leo_lc_ss0_usr
op_star
id|lc_ss0_usr
suffix:semicolon
DECL|member|lc_ss1_krn
r_struct
id|leo_lc_ss1_krn
op_star
id|lc_ss1_krn
suffix:semicolon
DECL|member|lc_ss1_usr
r_struct
id|leo_lc_ss1_usr
op_star
id|lc_ss1_usr
suffix:semicolon
DECL|member|ld_ss0
r_struct
id|leo_ld_ss0
op_star
id|ld_ss0
suffix:semicolon
DECL|member|ld_ss1
r_struct
id|leo_ld_ss1
op_star
id|ld_ss1
suffix:semicolon
DECL|member|ld_gbl
r_struct
id|leo_ld_gbl
op_star
id|ld_gbl
suffix:semicolon
DECL|member|lx_krn
r_struct
id|leo_lx_krn
op_star
id|lx_krn
suffix:semicolon
DECL|member|cluts
id|u32
op_star
id|cluts
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|xlut
id|u8
op_star
id|xlut
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|bwtwo_info
r_struct
id|bwtwo_info
(brace
DECL|member|regs
r_struct
id|bwtwo_regs
op_star
id|regs
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cg3_info
r_struct
id|cg3_info
(brace
DECL|member|regs
r_struct
id|cg3_regs
op_star
id|regs
suffix:semicolon
multiline_comment|/* brooktree (color) registers, and more */
DECL|member|cgrdi
r_int
id|cgrdi
suffix:semicolon
multiline_comment|/* 1 if this is a cgRDI */
)brace
suffix:semicolon
DECL|struct|cg14_info
r_struct
id|cg14_info
(brace
DECL|member|regs
r_struct
id|cg14_regs
op_star
id|regs
suffix:semicolon
DECL|member|cursor_regs
r_struct
id|cg14_cursor
op_star
id|cursor_regs
suffix:semicolon
DECL|member|dac
r_struct
id|cg14_dac
op_star
id|dac
suffix:semicolon
DECL|member|xlut
r_struct
id|cg14_xlut
op_star
id|xlut
suffix:semicolon
DECL|member|clut
r_struct
id|cg14_clut
op_star
id|clut
suffix:semicolon
DECL|member|ramsize
r_int
id|ramsize
suffix:semicolon
DECL|member|video_mode
r_int
id|video_mode
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|bt
r_int
r_int
id|bt
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ibm
r_int
r_char
id|ibm
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|dacptr
)brace
id|dacptr
suffix:semicolon
DECL|struct|weitek_info
r_struct
id|weitek_info
(brace
DECL|member|p9000
r_int
id|p9000
suffix:semicolon
multiline_comment|/* p9000? or p9100 */
DECL|member|dac
id|dacptr
op_star
id|dac
suffix:semicolon
multiline_comment|/* dac structures */
DECL|member|fbsize
r_int
r_int
id|fbsize
suffix:semicolon
multiline_comment|/* size of frame buffer */
)brace
suffix:semicolon
multiline_comment|/* Array holding the information for the frame buffers */
DECL|struct|fbinfo
r_typedef
r_struct
id|fbinfo
(brace
r_union
(brace
DECL|member|bwtwo
r_struct
id|bwtwo_info
id|bwtwo
suffix:semicolon
DECL|member|cg3
r_struct
id|cg3_info
id|cg3
suffix:semicolon
DECL|member|cg6
r_struct
id|cg6_info
id|cg6
suffix:semicolon
DECL|member|cg14
r_struct
id|cg14_info
id|cg14
suffix:semicolon
DECL|member|tcx
r_struct
id|tcx_info
id|tcx
suffix:semicolon
DECL|member|leo
r_struct
id|leo_info
id|leo
suffix:semicolon
DECL|member|info
)brace
id|info
suffix:semicolon
multiline_comment|/* per frame information */
DECL|member|space
r_int
id|space
suffix:semicolon
multiline_comment|/* I/O space this card resides in */
DECL|member|blanked
r_int
id|blanked
suffix:semicolon
multiline_comment|/* true if video blanked */
DECL|member|open
r_int
id|open
suffix:semicolon
multiline_comment|/* is this fb open? */
DECL|member|mmaped
r_int
id|mmaped
suffix:semicolon
multiline_comment|/* has this fb been mmapped? */
DECL|member|vtconsole
r_int
id|vtconsole
suffix:semicolon
multiline_comment|/* virtual console where it is opened */
DECL|member|base
r_int
id|base
suffix:semicolon
multiline_comment|/* frame buffer base    */
DECL|member|type
r_struct
id|fbtype
id|type
suffix:semicolon
multiline_comment|/* frame buffer type    */
DECL|member|real_type
r_int
id|real_type
suffix:semicolon
multiline_comment|/* real frame buffer FBTYPE* */
DECL|member|emulations
r_int
id|emulations
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* possible emulations (-1 N/A) */
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
multiline_comment|/* node of the device in prom tree */
DECL|member|base_depth
r_int
id|base_depth
suffix:semicolon
multiline_comment|/* depth of fb-&gt;base piece */
DECL|member|cursor
r_struct
id|cg_cursor
id|cursor
suffix:semicolon
multiline_comment|/* kernel state of hw cursor */
DECL|member|mmap
r_int
(paren
op_star
id|mmap
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_struct
id|vm_area_struct
op_star
comma
r_int
id|fb_base
comma
r_struct
id|fbinfo
op_star
)paren
suffix:semicolon
DECL|member|loadcmap
r_void
(paren
op_star
id|loadcmap
)paren
(paren
r_struct
id|fbinfo
op_star
id|fb
comma
r_int
id|index
comma
r_int
id|count
)paren
suffix:semicolon
DECL|member|blank
r_void
(paren
op_star
id|blank
)paren
(paren
r_struct
id|fbinfo
op_star
id|fb
)paren
suffix:semicolon
DECL|member|unblank
r_void
(paren
op_star
id|unblank
)paren
(paren
r_struct
id|fbinfo
op_star
id|fb
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
id|uint
comma
r_int
r_int
comma
r_struct
id|fbinfo
op_star
)paren
suffix:semicolon
DECL|member|reset
r_void
(paren
op_star
id|reset
)paren
(paren
r_struct
id|fbinfo
op_star
id|fb
)paren
suffix:semicolon
DECL|member|switch_from_graph
r_void
(paren
op_star
id|switch_from_graph
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|setcursor
r_void
(paren
op_star
id|setcursor
)paren
(paren
r_struct
id|fbinfo
op_star
)paren
suffix:semicolon
DECL|member|setcurshape
r_void
(paren
op_star
id|setcurshape
)paren
(paren
r_struct
id|fbinfo
op_star
)paren
suffix:semicolon
DECL|member|setcursormap
r_void
(paren
op_star
id|setcursormap
)paren
(paren
r_struct
id|fbinfo
op_star
comma
r_int
r_char
op_star
comma
r_int
r_char
op_star
comma
r_int
r_char
op_star
)paren
suffix:semicolon
DECL|member|postsetup
r_int
r_int
(paren
op_star
id|postsetup
)paren
(paren
r_struct
id|fbinfo
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|blitc
r_void
(paren
op_star
id|blitc
)paren
(paren
r_int
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|setw
r_void
(paren
op_star
id|setw
)paren
(paren
r_int
comma
r_int
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|cpyw
r_void
(paren
op_star
id|cpyw
)paren
(paren
r_int
comma
r_int
comma
r_int
r_int
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|fill
r_void
(paren
op_star
id|fill
)paren
(paren
r_int
comma
r_int
comma
r_int
op_star
)paren
suffix:semicolon
DECL|member|color_map
r_int
r_char
op_star
id|color_map
suffix:semicolon
DECL|member|proc_entry
r_struct
id|openpromfs_dev
id|proc_entry
suffix:semicolon
DECL|typedef|fbinfo_t
)brace
id|fbinfo_t
suffix:semicolon
DECL|macro|CM
mdefine_line|#define CM(i, j) [3*(i)+(j)]
r_extern
r_int
r_char
id|reverse_color_table
(braket
)braket
suffix:semicolon
DECL|macro|CHARATTR_TO_SUNCOLOR
mdefine_line|#define CHARATTR_TO_SUNCOLOR(attr) &bslash;&n;&t;((reverse_color_table[(attr) &gt;&gt; 12] &lt;&lt; 4) | &bslash;&n;&t;  reverse_color_table[((attr) &gt;&gt; 8) &amp; 0x0f])
r_extern
id|fbinfo_t
op_star
id|fbinfo
suffix:semicolon
r_extern
r_int
id|fbinfos
suffix:semicolon
r_struct
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* prom name */
DECL|member|width
DECL|member|height
r_int
id|width
comma
id|height
suffix:semicolon
multiline_comment|/* prefered w,h match */
DECL|member|fbtype
r_void
(paren
op_star
id|fbtype
)paren
(paren
id|fbinfo_t
op_star
)paren
suffix:semicolon
multiline_comment|/* generic device type */
multiline_comment|/* device specific init routine  */
DECL|member|fbinit
r_int
r_int
(paren
op_star
id|fbinit
)paren
(paren
id|fbinfo_t
op_star
id|fbinfo
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
DECL|variable|fb_entry
)brace
id|fb_entry
suffix:semicolon
r_extern
r_int
id|fb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|fb_restore_palette
)paren
(paren
id|fbinfo_t
op_star
id|fbinfo
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|fb_hide_cursor
)paren
(paren
r_int
id|cursor_pos
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|fb_set_cursor
)paren
(paren
r_int
id|oldpos
comma
r_int
id|idx
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|fb_clear_screen
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|fb_blitc
)paren
(paren
r_int
r_char
op_star
comma
r_int
comma
r_int
r_int
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|fb_font_init
)paren
(paren
r_int
r_char
op_star
id|font
)paren
suffix:semicolon
multiline_comment|/* All framebuffers are likely to require this info */
multiline_comment|/* Screen dimensions and color depth. */
r_extern
r_int
id|con_depth
comma
id|con_width
suffix:semicolon
r_extern
r_int
id|con_height
comma
id|con_linebytes
suffix:semicolon
r_extern
r_int
id|ints_per_line
suffix:semicolon
multiline_comment|/* used in the mmap routines */
r_extern
r_int
r_int
id|get_phys
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|get_iospace
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|render_screen
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sun_hw_hide_cursor
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sun_hw_set_cursor
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|sun_hw_scursor
c_func
(paren
r_struct
id|fbcursor
op_star
comma
id|fbinfo_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sun_hw_cursor_shown
suffix:semicolon
r_extern
r_int
id|sun_prom_console_id
suffix:semicolon
r_extern
r_int
r_int
id|sun_cg_postsetup
c_func
(paren
id|fbinfo_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|FB_DEV
mdefine_line|#define FB_DEV(x) (MINOR(x) / 32)
r_extern
r_void
id|cg3_setup
(paren
id|fbinfo_t
op_star
comma
r_int
comma
r_int
r_int
comma
r_int
comma
r_struct
id|linux_sbus_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|cg6_setup
(paren
id|fbinfo_t
op_star
comma
r_int
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|cg14_setup
(paren
id|fbinfo_t
op_star
comma
r_int
comma
r_int
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|bwtwo_setup
(paren
id|fbinfo_t
op_star
comma
r_int
comma
r_int
r_int
comma
r_int
comma
r_struct
id|linux_sbus_device
op_star
)paren
suffix:semicolon
r_extern
r_void
id|leo_setup
(paren
id|fbinfo_t
op_star
comma
r_int
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|tcx_setup
(paren
id|fbinfo_t
op_star
comma
r_int
comma
r_int
comma
r_int
r_int
comma
r_struct
id|linux_sbus_device
op_star
)paren
suffix:semicolon
macro_line|#endif __SPARC_FB_H_
eof
