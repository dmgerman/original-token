macro_line|#ifndef _LINUX_FB_H
DECL|macro|_LINUX_FB_H
mdefine_line|#define _LINUX_FB_H
macro_line|#include &lt;asm/types.h&gt;
multiline_comment|/* Definitions of frame buffers&t;&t;&t;&t;&t;&t;*/
DECL|macro|FB_MAJOR
mdefine_line|#define FB_MAJOR&t;29
DECL|macro|FB_MODES_SHIFT
mdefine_line|#define FB_MODES_SHIFT&t;&t;5&t;/* 32 modes per framebuffer */
DECL|macro|FB_NUM_MINORS
mdefine_line|#define FB_NUM_MINORS&t;&t;256&t;/* 256 Minors               */
DECL|macro|FB_MAX
mdefine_line|#define FB_MAX&t;&t;&t;(FB_NUM_MINORS / (1 &lt;&lt; FB_MODES_SHIFT))
DECL|macro|GET_FB_IDX
mdefine_line|#define GET_FB_IDX(node)&t;(MINOR(node) &gt;&gt; FB_MODES_SHIFT)
multiline_comment|/* ioctls&n;   0x46 is &squot;F&squot;&t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|FBIOGET_VSCREENINFO
mdefine_line|#define FBIOGET_VSCREENINFO&t;0x4600
DECL|macro|FBIOPUT_VSCREENINFO
mdefine_line|#define FBIOPUT_VSCREENINFO&t;0x4601
DECL|macro|FBIOGET_FSCREENINFO
mdefine_line|#define FBIOGET_FSCREENINFO&t;0x4602
DECL|macro|FBIOGETCMAP
mdefine_line|#define FBIOGETCMAP&t;&t;0x4604
DECL|macro|FBIOPUTCMAP
mdefine_line|#define FBIOPUTCMAP&t;&t;0x4605
DECL|macro|FBIOPAN_DISPLAY
mdefine_line|#define FBIOPAN_DISPLAY&t;&t;0x4606
multiline_comment|/* 0x4607-0x460B are defined below */
multiline_comment|/* #define FBIOGET_MONITORSPEC&t;0x460C */
multiline_comment|/* #define FBIOPUT_MONITORSPEC&t;0x460D */
multiline_comment|/* #define FBIOSWITCH_MONIBIT&t;0x460E */
DECL|macro|FBIOGET_CON2FBMAP
mdefine_line|#define FBIOGET_CON2FBMAP&t;0x460F
DECL|macro|FBIOPUT_CON2FBMAP
mdefine_line|#define FBIOPUT_CON2FBMAP&t;0x4610
DECL|macro|FB_TYPE_PACKED_PIXELS
mdefine_line|#define FB_TYPE_PACKED_PIXELS&t;&t;0&t;/* Packed Pixels&t;*/
DECL|macro|FB_TYPE_PLANES
mdefine_line|#define FB_TYPE_PLANES&t;&t;&t;1&t;/* Non interleaved planes */
DECL|macro|FB_TYPE_INTERLEAVED_PLANES
mdefine_line|#define FB_TYPE_INTERLEAVED_PLANES&t;2&t;/* Interleaved planes&t;*/
DECL|macro|FB_TYPE_TEXT
mdefine_line|#define FB_TYPE_TEXT&t;&t;&t;3&t;/* Text/attributes&t;*/
DECL|macro|FB_AUX_TEXT_MDA
mdefine_line|#define FB_AUX_TEXT_MDA&t;&t;0&t;/* Monochrome text */
DECL|macro|FB_AUX_TEXT_CGA
mdefine_line|#define FB_AUX_TEXT_CGA&t;&t;1&t;/* CGA/EGA/VGA Color text */
DECL|macro|FB_AUX_TEXT_S3_MMIO
mdefine_line|#define FB_AUX_TEXT_S3_MMIO&t;2&t;/* S3 MMIO fasttext */
DECL|macro|FB_VISUAL_MONO01
mdefine_line|#define FB_VISUAL_MONO01&t;&t;0&t;/* Monochr. 1=Black 0=White */
DECL|macro|FB_VISUAL_MONO10
mdefine_line|#define FB_VISUAL_MONO10&t;&t;1&t;/* Monochr. 1=White 0=Black */
DECL|macro|FB_VISUAL_TRUECOLOR
mdefine_line|#define FB_VISUAL_TRUECOLOR&t;&t;2&t;/* True color&t;*/
DECL|macro|FB_VISUAL_PSEUDOCOLOR
mdefine_line|#define FB_VISUAL_PSEUDOCOLOR&t;&t;3&t;/* Pseudo color (like atari) */
DECL|macro|FB_VISUAL_DIRECTCOLOR
mdefine_line|#define FB_VISUAL_DIRECTCOLOR&t;&t;4&t;/* Direct color */
DECL|macro|FB_VISUAL_STATIC_PSEUDOCOLOR
mdefine_line|#define FB_VISUAL_STATIC_PSEUDOCOLOR&t;5&t;/* Pseudo color readonly */
DECL|macro|FB_ACCEL_NONE
mdefine_line|#define FB_ACCEL_NONE&t;&t;0&t;/* no hardware accelerator&t;*/
DECL|macro|FB_ACCEL_ATARIBLITT
mdefine_line|#define FB_ACCEL_ATARIBLITT&t;1&t;/* Atari Blitter&t;&t;*/
DECL|macro|FB_ACCEL_AMIGABLITT
mdefine_line|#define FB_ACCEL_AMIGABLITT&t;2&t;/* Amiga Blitter                */
DECL|macro|FB_ACCEL_S3_TRIO64
mdefine_line|#define FB_ACCEL_S3_TRIO64&t;3&t;/* Cybervision64 (S3 Trio64)    */
DECL|macro|FB_ACCEL_NCR_77C32BLT
mdefine_line|#define FB_ACCEL_NCR_77C32BLT&t;4&t;/* RetinaZ3 (NCR 77C32BLT)      */
DECL|macro|FB_ACCEL_S3_VIRGE
mdefine_line|#define FB_ACCEL_S3_VIRGE&t;5&t;/* Cybervision64/3D (S3 ViRGE)&t;*/
DECL|macro|FB_ACCEL_ATI_MACH64GX
mdefine_line|#define FB_ACCEL_ATI_MACH64GX&t;6&t;/* ATI Mach 64GX family&t;&t;*/
DECL|macro|FB_ACCEL_DEC_TGA
mdefine_line|#define FB_ACCEL_DEC_TGA&t;7&t;/* DEC 21030 TGA&t;&t;*/
DECL|macro|FB_ACCEL_ATI_MACH64CT
mdefine_line|#define FB_ACCEL_ATI_MACH64CT&t;8&t;/* ATI Mach 64CT family&t;&t;*/
DECL|macro|FB_ACCEL_ATI_MACH64VT
mdefine_line|#define FB_ACCEL_ATI_MACH64VT&t;9&t;/* ATI Mach 64CT family VT class */
DECL|macro|FB_ACCEL_ATI_MACH64GT
mdefine_line|#define FB_ACCEL_ATI_MACH64GT&t;10&t;/* ATI Mach 64CT family GT class */
DECL|macro|FB_ACCEL_SUN_CREATOR
mdefine_line|#define FB_ACCEL_SUN_CREATOR&t;11&t;/* Sun Creator/Creator3D&t;*/
DECL|macro|FB_ACCEL_SUN_CGSIX
mdefine_line|#define FB_ACCEL_SUN_CGSIX&t;12&t;/* Sun cg6&t;&t;&t;*/
DECL|macro|FB_ACCEL_SUN_LEO
mdefine_line|#define FB_ACCEL_SUN_LEO&t;13&t;/* Sun leo/zx&t;&t;&t;*/
DECL|struct|fb_fix_screeninfo
r_struct
id|fb_fix_screeninfo
(brace
DECL|member|id
r_char
id|id
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* identification string eg &quot;TT Builtin&quot; */
DECL|member|smem_start
r_char
op_star
id|smem_start
suffix:semicolon
multiline_comment|/* Start of frame buffer mem */
multiline_comment|/* (physical address) */
DECL|member|smem_len
id|__u32
id|smem_len
suffix:semicolon
multiline_comment|/* Length of frame buffer mem */
DECL|member|type
id|__u32
id|type
suffix:semicolon
multiline_comment|/* see FB_TYPE_*&t;&t;*/
DECL|member|type_aux
id|__u32
id|type_aux
suffix:semicolon
multiline_comment|/* Interleave for interleaved Planes */
DECL|member|visual
id|__u32
id|visual
suffix:semicolon
multiline_comment|/* see FB_VISUAL_*&t;&t;*/
DECL|member|xpanstep
id|__u16
id|xpanstep
suffix:semicolon
multiline_comment|/* zero if no hardware panning  */
DECL|member|ypanstep
id|__u16
id|ypanstep
suffix:semicolon
multiline_comment|/* zero if no hardware panning  */
DECL|member|ywrapstep
id|__u16
id|ywrapstep
suffix:semicolon
multiline_comment|/* zero if no hardware ywrap    */
DECL|member|line_length
id|__u32
id|line_length
suffix:semicolon
multiline_comment|/* length of a line in bytes    */
DECL|member|mmio_start
r_char
op_star
id|mmio_start
suffix:semicolon
multiline_comment|/* Start of Memory Mapped I/O   */
multiline_comment|/* (physical address) */
DECL|member|mmio_len
id|__u32
id|mmio_len
suffix:semicolon
multiline_comment|/* Length of Memory Mapped I/O  */
DECL|member|accel
id|__u32
id|accel
suffix:semicolon
multiline_comment|/* Type of acceleration available */
DECL|member|reserved
id|__u16
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Reserved for future compatibility */
)brace
suffix:semicolon
multiline_comment|/* Interpretation of offset for color fields: All offsets are from the right,&n; * inside a &quot;pixel&quot; value, which is exactly &squot;bits_per_pixel&squot; wide (means: you&n; * can use the offset as right argument to &lt;&lt;). A pixel afterwards is a bit&n; * stream and is written to video memory as that unmodified. This implies&n; * big-endian byte order if bits_per_pixel is greater than 8.&n; */
DECL|struct|fb_bitfield
r_struct
id|fb_bitfield
(brace
DECL|member|offset
id|__u32
id|offset
suffix:semicolon
multiline_comment|/* beginning of bitfield&t;*/
DECL|member|length
id|__u32
id|length
suffix:semicolon
multiline_comment|/* length of bitfield&t;&t;*/
DECL|member|msb_right
id|__u32
id|msb_right
suffix:semicolon
multiline_comment|/* != 0 : Most significant bit is */
multiline_comment|/* right */
)brace
suffix:semicolon
DECL|macro|FB_NONSTD_HAM
mdefine_line|#define FB_NONSTD_HAM&t;&t;1&t;/* Hold-And-Modify (HAM)        */
DECL|macro|FB_ACTIVATE_NOW
mdefine_line|#define FB_ACTIVATE_NOW&t;&t;0&t;/* set values immediately (or vbl)*/
DECL|macro|FB_ACTIVATE_NXTOPEN
mdefine_line|#define FB_ACTIVATE_NXTOPEN&t;1&t;/* activate on next open&t;*/
DECL|macro|FB_ACTIVATE_TEST
mdefine_line|#define FB_ACTIVATE_TEST&t;2&t;/* don&squot;t set, round up impossible */
DECL|macro|FB_ACTIVATE_MASK
mdefine_line|#define FB_ACTIVATE_MASK       15
multiline_comment|/* values&t;&t;&t;*/
DECL|macro|FB_ACTIVATE_VBL
mdefine_line|#define FB_ACTIVATE_VBL&t;       16&t;/* activate values on next vbl  */
DECL|macro|FB_CHANGE_CMAP_VBL
mdefine_line|#define FB_CHANGE_CMAP_VBL     32&t;/* change colormap on vbl&t;*/
DECL|macro|FB_ACCELF_TEXT
mdefine_line|#define FB_ACCELF_TEXT&t;&t;1&t;/* text mode acceleration */
DECL|macro|FB_SYNC_HOR_HIGH_ACT
mdefine_line|#define FB_SYNC_HOR_HIGH_ACT&t;1&t;/* horizontal sync high active&t;*/
DECL|macro|FB_SYNC_VERT_HIGH_ACT
mdefine_line|#define FB_SYNC_VERT_HIGH_ACT&t;2&t;/* vertical sync high active&t;*/
DECL|macro|FB_SYNC_EXT
mdefine_line|#define FB_SYNC_EXT&t;&t;4&t;/* external sync&t;&t;*/
DECL|macro|FB_SYNC_COMP_HIGH_ACT
mdefine_line|#define FB_SYNC_COMP_HIGH_ACT&t;8&t;/* composite sync high active   */
DECL|macro|FB_SYNC_BROADCAST
mdefine_line|#define FB_SYNC_BROADCAST&t;16&t;/* broadcast video timings      */
multiline_comment|/* vtotal = 144d/288n/576i =&gt; PAL  */
multiline_comment|/* vtotal = 121d/242n/484i =&gt; NTSC */
DECL|macro|FB_SYNC_ON_GREEN
mdefine_line|#define FB_SYNC_ON_GREEN&t;32&t;/* sync on green */
DECL|macro|FB_VMODE_NONINTERLACED
mdefine_line|#define FB_VMODE_NONINTERLACED  0&t;/* non interlaced */
DECL|macro|FB_VMODE_INTERLACED
mdefine_line|#define FB_VMODE_INTERLACED&t;1&t;/* interlaced&t;*/
DECL|macro|FB_VMODE_DOUBLE
mdefine_line|#define FB_VMODE_DOUBLE&t;&t;2&t;/* double scan */
DECL|macro|FB_VMODE_MASK
mdefine_line|#define FB_VMODE_MASK&t;&t;255
DECL|macro|FB_VMODE_YWRAP
mdefine_line|#define FB_VMODE_YWRAP&t;&t;256&t;/* ywrap instead of panning     */
DECL|macro|FB_VMODE_SMOOTH_XPAN
mdefine_line|#define FB_VMODE_SMOOTH_XPAN&t;512&t;/* smooth xpan possible (internally used) */
DECL|macro|FB_VMODE_CONUPDATE
mdefine_line|#define FB_VMODE_CONUPDATE&t;512&t;/* don&squot;t update x/yoffset&t;*/
DECL|struct|fb_var_screeninfo
r_struct
id|fb_var_screeninfo
(brace
DECL|member|xres
id|__u32
id|xres
suffix:semicolon
multiline_comment|/* visible resolution&t;&t;*/
DECL|member|yres
id|__u32
id|yres
suffix:semicolon
DECL|member|xres_virtual
id|__u32
id|xres_virtual
suffix:semicolon
multiline_comment|/* virtual resolution&t;&t;*/
DECL|member|yres_virtual
id|__u32
id|yres_virtual
suffix:semicolon
DECL|member|xoffset
id|__u32
id|xoffset
suffix:semicolon
multiline_comment|/* offset from virtual to visible */
DECL|member|yoffset
id|__u32
id|yoffset
suffix:semicolon
multiline_comment|/* resolution&t;&t;&t;*/
DECL|member|bits_per_pixel
id|__u32
id|bits_per_pixel
suffix:semicolon
multiline_comment|/* guess what&t;&t;&t;*/
DECL|member|grayscale
id|__u32
id|grayscale
suffix:semicolon
multiline_comment|/* != 0 Graylevels instead of colors */
DECL|member|red
r_struct
id|fb_bitfield
id|red
suffix:semicolon
multiline_comment|/* bitfield in fb mem if true color, */
DECL|member|green
r_struct
id|fb_bitfield
id|green
suffix:semicolon
multiline_comment|/* else only length is significant */
DECL|member|blue
r_struct
id|fb_bitfield
id|blue
suffix:semicolon
DECL|member|transp
r_struct
id|fb_bitfield
id|transp
suffix:semicolon
multiline_comment|/* transparency&t;&t;&t;*/
DECL|member|nonstd
id|__u32
id|nonstd
suffix:semicolon
multiline_comment|/* != 0 Non standard pixel format */
DECL|member|activate
id|__u32
id|activate
suffix:semicolon
multiline_comment|/* see FB_ACTIVATE_*&t;&t;*/
DECL|member|height
id|__u32
id|height
suffix:semicolon
multiline_comment|/* height of picture in mm    */
DECL|member|width
id|__u32
id|width
suffix:semicolon
multiline_comment|/* width of picture in mm     */
DECL|member|accel_flags
id|__u32
id|accel_flags
suffix:semicolon
multiline_comment|/* acceleration flags (hints)&t;*/
multiline_comment|/* Timing: All values in pixclocks, except pixclock (of course) */
DECL|member|pixclock
id|__u32
id|pixclock
suffix:semicolon
multiline_comment|/* pixel clock in ps (pico seconds) */
DECL|member|left_margin
id|__u32
id|left_margin
suffix:semicolon
multiline_comment|/* time from sync to picture&t;*/
DECL|member|right_margin
id|__u32
id|right_margin
suffix:semicolon
multiline_comment|/* time from picture to sync&t;*/
DECL|member|upper_margin
id|__u32
id|upper_margin
suffix:semicolon
multiline_comment|/* time from sync to picture&t;*/
DECL|member|lower_margin
id|__u32
id|lower_margin
suffix:semicolon
DECL|member|hsync_len
id|__u32
id|hsync_len
suffix:semicolon
multiline_comment|/* length of horizontal sync&t;*/
DECL|member|vsync_len
id|__u32
id|vsync_len
suffix:semicolon
multiline_comment|/* length of vertical sync&t;*/
DECL|member|sync
id|__u32
id|sync
suffix:semicolon
multiline_comment|/* see FB_SYNC_*&t;&t;*/
DECL|member|vmode
id|__u32
id|vmode
suffix:semicolon
multiline_comment|/* see FB_VMODE_*&t;&t;*/
DECL|member|reserved
id|__u32
id|reserved
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Reserved for future compatibility */
)brace
suffix:semicolon
DECL|struct|fb_cmap
r_struct
id|fb_cmap
(brace
DECL|member|start
id|__u32
id|start
suffix:semicolon
multiline_comment|/* First entry&t;*/
DECL|member|len
id|__u32
id|len
suffix:semicolon
multiline_comment|/* Number of entries */
DECL|member|red
id|__u16
op_star
id|red
suffix:semicolon
multiline_comment|/* Red values&t;*/
DECL|member|green
id|__u16
op_star
id|green
suffix:semicolon
DECL|member|blue
id|__u16
op_star
id|blue
suffix:semicolon
DECL|member|transp
id|__u16
op_star
id|transp
suffix:semicolon
multiline_comment|/* transparency, can be NULL */
)brace
suffix:semicolon
DECL|struct|fb_con2fbmap
r_struct
id|fb_con2fbmap
(brace
DECL|member|console
id|__u32
id|console
suffix:semicolon
DECL|member|framebuffer
id|__u32
id|framebuffer
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fb_monspecs
r_struct
id|fb_monspecs
(brace
DECL|member|hfmin
id|__u32
id|hfmin
suffix:semicolon
multiline_comment|/* hfreq lower limit (Hz) */
DECL|member|hfmax
id|__u32
id|hfmax
suffix:semicolon
multiline_comment|/* hfreq upper limit (Hz) */
DECL|member|vfmin
id|__u16
id|vfmin
suffix:semicolon
multiline_comment|/* vfreq lower limit (Hz) */
DECL|member|vfmax
id|__u16
id|vfmax
suffix:semicolon
multiline_comment|/* vfreq upper limit (Hz) */
DECL|member|dpms
r_int
id|dpms
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* supports DPMS */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/fs.h&gt;
r_struct
id|fb_info
suffix:semicolon
r_struct
id|fb_info_gen
suffix:semicolon
r_struct
id|vm_area_struct
suffix:semicolon
r_struct
id|file
suffix:semicolon
multiline_comment|/*&n;     *  Frame buffer operations&n;     */
DECL|struct|fb_ops
r_struct
id|fb_ops
(brace
multiline_comment|/* open/release and usage marking */
DECL|member|fb_open
r_int
(paren
op_star
id|fb_open
)paren
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|user
)paren
suffix:semicolon
DECL|member|fb_release
r_int
(paren
op_star
id|fb_release
)paren
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|user
)paren
suffix:semicolon
multiline_comment|/* get non settable parameters */
DECL|member|fb_get_fix
r_int
(paren
op_star
id|fb_get_fix
)paren
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* get settable parameters */
DECL|member|fb_get_var
r_int
(paren
op_star
id|fb_get_var
)paren
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* set settable parameters */
DECL|member|fb_set_var
r_int
(paren
op_star
id|fb_set_var
)paren
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* get colormap */
DECL|member|fb_get_cmap
r_int
(paren
op_star
id|fb_get_cmap
)paren
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|kspc
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* set colormap */
DECL|member|fb_set_cmap
r_int
(paren
op_star
id|fb_set_cmap
)paren
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|kspc
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* pan display */
DECL|member|fb_pan_display
r_int
(paren
op_star
id|fb_pan_display
)paren
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* perform fb specific ioctl */
DECL|member|fb_ioctl
r_int
(paren
op_star
id|fb_ioctl
)paren
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
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/* perform fb specific mmap */
DECL|member|fb_mmap
r_int
(paren
op_star
id|fb_mmap
)paren
(paren
r_struct
id|fb_info
op_star
id|info
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
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;    *    This is the interface between the low-level console driver and the&n;    *    low-level frame buffer device&n;    */
DECL|struct|display
r_struct
id|display
(brace
multiline_comment|/* Filled in by the frame buffer device */
DECL|member|var
r_struct
id|fb_var_screeninfo
id|var
suffix:semicolon
multiline_comment|/* variable infos. yoffset and vmode */
multiline_comment|/* are updated by fbcon.c */
DECL|member|cmap
r_struct
id|fb_cmap
id|cmap
suffix:semicolon
multiline_comment|/* colormap */
DECL|member|screen_base
r_char
op_star
id|screen_base
suffix:semicolon
multiline_comment|/* pointer to top of virtual screen */
multiline_comment|/* (virtual address) */
DECL|member|visual
r_int
id|visual
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* see FB_TYPE_* */
DECL|member|type_aux
r_int
id|type_aux
suffix:semicolon
multiline_comment|/* Interleave for interleaved Planes */
DECL|member|ypanstep
id|u_short
id|ypanstep
suffix:semicolon
multiline_comment|/* zero if no hardware ypan */
DECL|member|ywrapstep
id|u_short
id|ywrapstep
suffix:semicolon
multiline_comment|/* zero if no hardware ywrap */
DECL|member|line_length
id|u_long
id|line_length
suffix:semicolon
multiline_comment|/* length of a line in bytes */
DECL|member|can_soft_blank
id|u_short
id|can_soft_blank
suffix:semicolon
multiline_comment|/* zero if no hardware blanking */
DECL|member|inverse
id|u_short
id|inverse
suffix:semicolon
multiline_comment|/* != 0 text black on white as default */
DECL|member|dispsw
r_struct
id|display_switch
op_star
id|dispsw
suffix:semicolon
multiline_comment|/* low level operations */
DECL|member|dispsw_data
r_void
op_star
id|dispsw_data
suffix:semicolon
multiline_comment|/* optional dispsw helper data */
macro_line|#if 0
r_struct
id|fb_fix_cursorinfo
id|fcrsr
suffix:semicolon
r_struct
id|fb_var_cursorinfo
op_star
id|vcrsr
suffix:semicolon
r_struct
id|fb_cursorstate
id|crsrstate
suffix:semicolon
macro_line|#endif
multiline_comment|/* Filled in by the low-level console driver */
DECL|member|conp
r_struct
id|vc_data
op_star
id|conp
suffix:semicolon
multiline_comment|/* pointer to console data */
DECL|member|fb_info
r_struct
id|fb_info
op_star
id|fb_info
suffix:semicolon
multiline_comment|/* frame buffer for this console */
DECL|member|vrows
r_int
id|vrows
suffix:semicolon
multiline_comment|/* number of virtual rows */
DECL|member|cursor_x
r_int
r_int
id|cursor_x
suffix:semicolon
multiline_comment|/* current cursor position */
DECL|member|cursor_y
r_int
r_int
id|cursor_y
suffix:semicolon
DECL|member|fgcol
r_int
id|fgcol
suffix:semicolon
multiline_comment|/* text colors */
DECL|member|bgcol
r_int
id|bgcol
suffix:semicolon
DECL|member|next_line
id|u_long
id|next_line
suffix:semicolon
multiline_comment|/* offset to one line below */
DECL|member|next_plane
id|u_long
id|next_plane
suffix:semicolon
multiline_comment|/* offset to next plane */
DECL|member|fontdata
id|u_char
op_star
id|fontdata
suffix:semicolon
multiline_comment|/* Font associated to this display */
DECL|member|_fontheightlog
r_int
r_int
id|_fontheightlog
suffix:semicolon
DECL|member|_fontwidthlog
r_int
r_int
id|_fontwidthlog
suffix:semicolon
DECL|member|_fontheight
r_int
r_int
id|_fontheight
suffix:semicolon
DECL|member|_fontwidth
r_int
r_int
id|_fontwidth
suffix:semicolon
DECL|member|userfont
r_int
id|userfont
suffix:semicolon
multiline_comment|/* != 0 if fontdata kmalloc()ed */
DECL|member|scrollmode
id|u_short
id|scrollmode
suffix:semicolon
multiline_comment|/* Scroll Method */
DECL|member|yscroll
r_int
id|yscroll
suffix:semicolon
multiline_comment|/* Hardware scrolling */
DECL|member|fgshift
DECL|member|bgshift
r_int
r_char
id|fgshift
comma
id|bgshift
suffix:semicolon
DECL|member|charmask
r_int
r_int
id|charmask
suffix:semicolon
multiline_comment|/* 0xff or 0x1ff */
)brace
suffix:semicolon
DECL|struct|fb_info
r_struct
id|fb_info
(brace
DECL|member|modename
r_char
id|modename
(braket
l_int|40
)braket
suffix:semicolon
multiline_comment|/* default video mode */
DECL|member|node
r_int
id|node
suffix:semicolon
DECL|member|fbops
r_struct
id|fb_ops
op_star
id|fbops
suffix:semicolon
DECL|member|monspecs
r_struct
id|fb_monspecs
id|monspecs
suffix:semicolon
DECL|member|disp
r_struct
id|display
op_star
id|disp
suffix:semicolon
multiline_comment|/* initial display variable */
DECL|member|display_fg
r_struct
id|vc_data
op_star
id|display_fg
suffix:semicolon
multiline_comment|/* Console visible on this display */
DECL|member|fontname
r_char
id|fontname
(braket
l_int|40
)braket
suffix:semicolon
multiline_comment|/* default font name */
DECL|member|changevar
r_int
(paren
op_star
id|changevar
)paren
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* tell console var has changed */
DECL|member|switch_con
r_int
(paren
op_star
id|switch_con
)paren
(paren
r_int
comma
r_struct
id|fb_info
op_star
)paren
suffix:semicolon
multiline_comment|/* tell fb to switch consoles */
DECL|member|updatevar
r_int
(paren
op_star
id|updatevar
)paren
(paren
r_int
comma
r_struct
id|fb_info
op_star
)paren
suffix:semicolon
multiline_comment|/* tell fb to update the vars */
DECL|member|blank
r_void
(paren
op_star
id|blank
)paren
(paren
r_int
comma
r_struct
id|fb_info
op_star
)paren
suffix:semicolon
multiline_comment|/* tell fb to (un)blank the screen */
multiline_comment|/* arg = 0: unblank */
multiline_comment|/* arg &gt; 0: VESA level (arg-1) */
multiline_comment|/* From here on everything is device dependent */
)brace
suffix:semicolon
multiline_comment|/*&n;     *  This structure abstracts from the underlying hardware. It is not&n;     *  mandatory but used by the `generic&squot; frame buffer operations.&n;     *  Read drivers/video/skeletonfb.c for more information.&n;     */
DECL|struct|fbgen_hwswitch
r_struct
id|fbgen_hwswitch
(brace
DECL|member|detect
r_void
(paren
op_star
id|detect
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|encode_fix
r_int
(paren
op_star
id|encode_fix
)paren
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_const
r_void
op_star
id|par
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
suffix:semicolon
DECL|member|decode_var
r_int
(paren
op_star
id|decode_var
)paren
(paren
r_const
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_void
op_star
id|par
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
suffix:semicolon
DECL|member|encode_var
r_int
(paren
op_star
id|encode_var
)paren
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_const
r_void
op_star
id|par
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
suffix:semicolon
DECL|member|get_par
r_void
(paren
op_star
id|get_par
)paren
(paren
r_void
op_star
id|par
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
suffix:semicolon
DECL|member|set_par
r_void
(paren
op_star
id|set_par
)paren
(paren
r_const
r_void
op_star
id|par
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
suffix:semicolon
DECL|member|getcolreg
r_int
(paren
op_star
id|getcolreg
)paren
(paren
r_int
id|regno
comma
r_int
op_star
id|red
comma
r_int
op_star
id|green
comma
r_int
op_star
id|blue
comma
r_int
op_star
id|transp
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
DECL|member|setcolreg
r_int
(paren
op_star
id|setcolreg
)paren
(paren
r_int
id|regno
comma
r_int
id|red
comma
r_int
id|green
comma
r_int
id|blue
comma
r_int
id|transp
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
DECL|member|pan_display
r_int
(paren
op_star
id|pan_display
)paren
(paren
r_const
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
suffix:semicolon
DECL|member|blank
r_int
(paren
op_star
id|blank
)paren
(paren
r_int
id|blank_mode
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
suffix:semicolon
DECL|member|set_dispsw
r_void
(paren
op_star
id|set_dispsw
)paren
(paren
r_const
r_void
op_star
id|par
comma
r_struct
id|display
op_star
id|disp
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fb_info_gen
r_struct
id|fb_info_gen
(brace
DECL|member|info
r_struct
id|fb_info
id|info
suffix:semicolon
multiline_comment|/* Entries for a generic frame buffer device */
multiline_comment|/* Yes, this starts looking like C++ */
DECL|member|parsize
id|u_int
id|parsize
suffix:semicolon
DECL|member|fbhw
r_struct
id|fbgen_hwswitch
op_star
id|fbhw
suffix:semicolon
multiline_comment|/* From here on everything is device dependent */
)brace
suffix:semicolon
multiline_comment|/*&n;     *  `Generic&squot; versions of the frame buffer device operations&n;     */
r_extern
r_int
id|fbgen_get_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_int
id|fbgen_get_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_int
id|fbgen_set_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_int
id|fbgen_get_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|kspc
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_int
id|fbgen_set_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|kspc
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_int
id|fbgen_pan_display
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_int
id|fbgen_ioctl
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
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/*&n;     *  Helper functions&n;     */
r_extern
r_int
id|fbgen_do_set_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|isactive
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
suffix:semicolon
r_extern
r_void
id|fbgen_set_disp
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
suffix:semicolon
r_extern
r_void
id|fbgen_install_cmap
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
suffix:semicolon
r_extern
r_int
id|fbgen_update_var
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_int
id|fbgen_switch
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_extern
r_void
id|fbgen_blank
c_func
(paren
r_int
id|blank
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
DECL|struct|fb_videomode
r_struct
id|fb_videomode
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|var
r_struct
id|fb_var_screeninfo
id|var
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* drivers/char/fbmem.c */
r_extern
r_int
id|register_framebuffer
c_func
(paren
r_struct
id|fb_info
op_star
id|fb_info
)paren
suffix:semicolon
r_extern
r_int
id|unregister_framebuffer
c_func
(paren
r_const
r_struct
id|fb_info
op_star
id|fb_info
)paren
suffix:semicolon
r_extern
r_int
id|fbmon_valid_timings
c_func
(paren
id|u_int
id|pixclock
comma
id|u_int
id|htotal
comma
id|u_int
id|vtotal
comma
r_const
r_struct
id|fb_info
op_star
id|fb_info
)paren
suffix:semicolon
r_extern
r_int
id|fbmon_dpms
c_func
(paren
r_const
r_struct
id|fb_info
op_star
id|fb_info
)paren
suffix:semicolon
r_extern
r_int
id|num_registered_fb
suffix:semicolon
r_extern
r_struct
id|fb_info
op_star
id|registered_fb
(braket
id|FB_MAX
)braket
suffix:semicolon
r_extern
r_char
id|con2fb_map
(braket
id|MAX_NR_CONSOLES
)braket
suffix:semicolon
multiline_comment|/* drivers/video/fbcon.c */
r_extern
r_struct
id|display
id|fb_display
(braket
id|MAX_NR_CONSOLES
)braket
suffix:semicolon
multiline_comment|/* drivers/video/fbcmap.c */
r_extern
r_int
id|fb_alloc_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|len
comma
r_int
id|transp
)paren
suffix:semicolon
r_extern
r_void
id|fb_copy_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|from
comma
r_struct
id|fb_cmap
op_star
id|to
comma
r_int
id|fsfromto
)paren
suffix:semicolon
r_extern
r_int
id|fb_get_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|kspc
comma
r_int
(paren
op_star
id|getcolreg
)paren
(paren
id|u_int
comma
id|u_int
op_star
comma
id|u_int
op_star
comma
id|u_int
op_star
comma
id|u_int
op_star
comma
r_struct
id|fb_info
op_star
)paren
comma
r_struct
id|fb_info
op_star
id|fb_info
)paren
suffix:semicolon
r_extern
r_int
id|fb_set_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|kspc
comma
r_int
(paren
op_star
id|setcolreg
)paren
(paren
id|u_int
comma
id|u_int
comma
id|u_int
comma
id|u_int
comma
id|u_int
comma
r_struct
id|fb_info
op_star
)paren
comma
r_struct
id|fb_info
op_star
id|fb_info
)paren
suffix:semicolon
r_extern
r_struct
id|fb_cmap
op_star
id|fb_default_cmap
c_func
(paren
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|fb_invert_cmaps
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* VESA Blanking Levels */
DECL|macro|VESA_NO_BLANKING
mdefine_line|#define VESA_NO_BLANKING&t;0
DECL|macro|VESA_VSYNC_SUSPEND
mdefine_line|#define VESA_VSYNC_SUSPEND&t;1
DECL|macro|VESA_HSYNC_SUSPEND
mdefine_line|#define VESA_HSYNC_SUSPEND&t;2
DECL|macro|VESA_POWERDOWN
mdefine_line|#define VESA_POWERDOWN&t;&t;3
macro_line|#endif /* __KERNEL__ */
macro_line|#if 1
DECL|macro|FBCMD_GET_CURRENTPAR
mdefine_line|#define FBCMD_GET_CURRENTPAR&t;0xDEAD0005
DECL|macro|FBCMD_SET_CURRENTPAR
mdefine_line|#define FBCMD_SET_CURRENTPAR&t;0xDEAD8005
macro_line|#endif
macro_line|#if 1 /* Preliminary */
multiline_comment|/*&n;    *    Hardware Cursor&n;    */
DECL|macro|FBIOGET_FCURSORINFO
mdefine_line|#define FBIOGET_FCURSORINFO     0x4607
DECL|macro|FBIOGET_VCURSORINFO
mdefine_line|#define FBIOGET_VCURSORINFO     0x4608
DECL|macro|FBIOPUT_VCURSORINFO
mdefine_line|#define FBIOPUT_VCURSORINFO     0x4609
DECL|macro|FBIOGET_CURSORSTATE
mdefine_line|#define FBIOGET_CURSORSTATE     0x460A
DECL|macro|FBIOPUT_CURSORSTATE
mdefine_line|#define FBIOPUT_CURSORSTATE     0x460B
DECL|struct|fb_fix_cursorinfo
r_struct
id|fb_fix_cursorinfo
(brace
DECL|member|crsr_width
id|__u16
id|crsr_width
suffix:semicolon
multiline_comment|/* width and height of the cursor in */
DECL|member|crsr_height
id|__u16
id|crsr_height
suffix:semicolon
multiline_comment|/* pixels (zero if no cursor)&t;*/
DECL|member|crsr_xsize
id|__u16
id|crsr_xsize
suffix:semicolon
multiline_comment|/* cursor size in display pixels */
DECL|member|crsr_ysize
id|__u16
id|crsr_ysize
suffix:semicolon
DECL|member|crsr_color1
id|__u16
id|crsr_color1
suffix:semicolon
multiline_comment|/* colormap entry for cursor color1 */
DECL|member|crsr_color2
id|__u16
id|crsr_color2
suffix:semicolon
multiline_comment|/* colormap entry for cursor color2 */
)brace
suffix:semicolon
DECL|struct|fb_var_cursorinfo
r_struct
id|fb_var_cursorinfo
(brace
DECL|member|width
id|__u16
id|width
suffix:semicolon
DECL|member|height
id|__u16
id|height
suffix:semicolon
DECL|member|xspot
id|__u16
id|xspot
suffix:semicolon
DECL|member|yspot
id|__u16
id|yspot
suffix:semicolon
DECL|member|data
id|__u8
id|data
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* field with [height][width]        */
)brace
suffix:semicolon
DECL|struct|fb_cursorstate
r_struct
id|fb_cursorstate
(brace
DECL|member|xoffset
id|__s16
id|xoffset
suffix:semicolon
DECL|member|yoffset
id|__s16
id|yoffset
suffix:semicolon
DECL|member|mode
id|__u16
id|mode
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FB_CURSOR_OFF
mdefine_line|#define FB_CURSOR_OFF&t;&t;0
DECL|macro|FB_CURSOR_ON
mdefine_line|#define FB_CURSOR_ON&t;&t;1
DECL|macro|FB_CURSOR_FLASH
mdefine_line|#define FB_CURSOR_FLASH&t;&t;2
macro_line|#endif /* Preliminary */
macro_line|#endif /* _LINUX_FB_H */
eof
