macro_line|#ifndef _LINUX_FB_H
DECL|macro|_LINUX_FB_H
mdefine_line|#define _LINUX_FB_H
multiline_comment|/* Definitions of frame buffers&t;&t;&t;&t;&t;&t;*/
multiline_comment|/* ioctls&n;   0x46 is &squot;F&squot;&t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|macro|FBIOGET_VSCREENINFO
mdefine_line|#define FBIOGET_VSCREENINFO &t;0x4600
DECL|macro|FBIOPUT_VSCREENINFO
mdefine_line|#define FBIOPUT_VSCREENINFO &t;0x4601
DECL|macro|FBIOGET_FSCREENINFO
mdefine_line|#define FBIOGET_FSCREENINFO &t;0x4602
DECL|macro|FBIOGETCMAP
mdefine_line|#define FBIOGETCMAP&t;&t;0x4604
DECL|macro|FBIOPUTCMAP
mdefine_line|#define FBIOPUTCMAP&t;&t;0x4605
DECL|macro|FBIOPAN_DISPLAY
mdefine_line|#define FBIOPAN_DISPLAY         0x4606
DECL|macro|FB_TYPE_PACKED_PIXELS
mdefine_line|#define FB_TYPE_PACKED_PIXELS&t;&t;0&t;/* Packed Pixels&t;*/
DECL|macro|FB_TYPE_PLANES
mdefine_line|#define FB_TYPE_PLANES&t;&t;&t;1&t;/* Non interleaved planes */
DECL|macro|FB_TYPE_INTERLEAVED_PLANES
mdefine_line|#define FB_TYPE_INTERLEAVED_PLANES&t;2&t;/* Interleaved planes&t;*/
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
DECL|macro|FB_VISUAL_STATIC_DIRECTCOLOR
mdefine_line|#define FB_VISUAL_STATIC_DIRECTCOLOR&t;6&t;/* Direct color readonly */
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
r_int
r_int
id|smem_start
suffix:semicolon
multiline_comment|/* Start of frame buffer mem */
DECL|member|smem_len
r_int
r_int
id|smem_len
suffix:semicolon
multiline_comment|/* Length of frame buffer mem */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* see FB_TYPE_* &t;&t;*/
DECL|member|type_aux
r_int
id|type_aux
suffix:semicolon
multiline_comment|/* Interleave for interleaved Planes */
DECL|member|visual
r_int
id|visual
suffix:semicolon
multiline_comment|/* see FB_VISUAL_*  &t;&t;*/
DECL|member|xpanstep
id|u_short
id|xpanstep
suffix:semicolon
multiline_comment|/* zero if no hardware panning  */
DECL|member|ypanstep
id|u_short
id|ypanstep
suffix:semicolon
multiline_comment|/* zero if no hardware panning  */
DECL|member|ywrapstep
id|u_short
id|ywrapstep
suffix:semicolon
multiline_comment|/* zero if no hardware ywrap    */
DECL|member|line_length
id|u_long
id|line_length
suffix:semicolon
multiline_comment|/* length of a line in bytes    */
DECL|member|reserved
r_int
id|reserved
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* Reserved for future compatibility */
)brace
suffix:semicolon
DECL|struct|fb_bitfield
r_struct
id|fb_bitfield
(brace
DECL|member|offset
r_int
id|offset
suffix:semicolon
multiline_comment|/* beginning of bitfield&t;*/
DECL|member|length
r_int
id|length
suffix:semicolon
multiline_comment|/* length of bitfield&t;&t;*/
DECL|member|msb_right
r_int
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
DECL|macro|FB_ACCEL_NONE
mdefine_line|#define FB_ACCEL_NONE&t;&t;0&t;/* no hardware accelerator&t;*/
DECL|macro|FB_ACCEL_ATARIBLITT
mdefine_line|#define FB_ACCEL_ATARIBLITT&t;1&t;/* Atari Blitter&t;&t;*/
DECL|macro|FB_ACCEL_AMIGABLITT
mdefine_line|#define FB_ACCEL_AMIGABLITT&t;2&t;/* Amiga Blitter                */
DECL|macro|FB_ACCEL_CYBERVISION
mdefine_line|#define FB_ACCEL_CYBERVISION&t;3&t;/* Cybervision64 (S3 Trio64)    */
DECL|macro|FB_ACCEL_RETINAZ3
mdefine_line|#define FB_ACCEL_RETINAZ3&t;4&t;/* RetinaZ3 (NCR77C32BLT)       */
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
DECL|macro|FB_VMODE_NONINTERLACED
mdefine_line|#define FB_VMODE_NONINTERLACED  0&t;/* non interlaced */
DECL|macro|FB_VMODE_INTERLACED
mdefine_line|#define FB_VMODE_INTERLACED &t;1&t;/* interlaced&t;*/
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
r_int
id|xres
suffix:semicolon
multiline_comment|/* visible resolution&t;&t;*/
DECL|member|yres
r_int
id|yres
suffix:semicolon
DECL|member|xres_virtual
r_int
id|xres_virtual
suffix:semicolon
multiline_comment|/* virtual resolution&t;&t;*/
DECL|member|yres_virtual
r_int
id|yres_virtual
suffix:semicolon
DECL|member|xoffset
r_int
id|xoffset
suffix:semicolon
multiline_comment|/* offset from virtual to visible */
DECL|member|yoffset
r_int
id|yoffset
suffix:semicolon
multiline_comment|/* resolution&t;&t;&t;*/
DECL|member|bits_per_pixel
r_int
id|bits_per_pixel
suffix:semicolon
multiline_comment|/* guess what &t;&t;&t;*/
DECL|member|grayscale
r_int
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
r_int
id|nonstd
suffix:semicolon
multiline_comment|/* != 0 Non standard pixel format */
DECL|member|activate
r_int
id|activate
suffix:semicolon
multiline_comment|/* see FB_ACTIVATE_* &t;&t;*/
DECL|member|height
r_int
id|height
suffix:semicolon
multiline_comment|/* height of picture in mm    */
DECL|member|width
r_int
id|width
suffix:semicolon
multiline_comment|/* width of picture in mm     */
DECL|member|accel
r_int
id|accel
suffix:semicolon
multiline_comment|/* see FB_ACCEL_*&t;&t;*/
multiline_comment|/* Timing: All values in pixclocks, except pixclock (of course) */
DECL|member|pixclock
r_int
r_int
id|pixclock
suffix:semicolon
multiline_comment|/* pixel clock in ps (pico seconds) */
DECL|member|left_margin
r_int
r_int
id|left_margin
suffix:semicolon
multiline_comment|/* time from sync to picture&t;*/
DECL|member|right_margin
r_int
r_int
id|right_margin
suffix:semicolon
multiline_comment|/* time from picture to sync&t;*/
DECL|member|upper_margin
r_int
r_int
id|upper_margin
suffix:semicolon
multiline_comment|/* time from sync to picture&t;*/
DECL|member|lower_margin
r_int
r_int
id|lower_margin
suffix:semicolon
DECL|member|hsync_len
r_int
r_int
id|hsync_len
suffix:semicolon
multiline_comment|/* length of horizontal sync&t;*/
DECL|member|vsync_len
r_int
r_int
id|vsync_len
suffix:semicolon
multiline_comment|/* length of vertical sync&t;*/
DECL|member|sync
r_int
id|sync
suffix:semicolon
multiline_comment|/* see FB_SYNC_*&t;&t;*/
DECL|member|vmode
r_int
id|vmode
suffix:semicolon
multiline_comment|/* see FB_VMODE_*&t;&t;*/
DECL|member|reserved
r_int
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
r_int
id|start
suffix:semicolon
multiline_comment|/* First entry&t;*/
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* Number of entries */
DECL|member|red
r_int
r_int
op_star
id|red
suffix:semicolon
multiline_comment|/* Red values&t;*/
DECL|member|green
r_int
r_int
op_star
id|green
suffix:semicolon
DECL|member|blue
r_int
r_int
op_star
id|blue
suffix:semicolon
DECL|member|transp
r_int
r_int
op_star
id|transp
suffix:semicolon
multiline_comment|/* transparency, can be NULL */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/fs.h&gt;
DECL|struct|fb_ops
r_struct
id|fb_ops
(brace
multiline_comment|/* get non settable parameters&t;*/
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
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* get settable parameters&t;*/
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
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* set settable parameters&t;*/
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
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* get colormap&t;&t;&t;*/
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
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* set colormap&t;&t;&t;*/
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
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* pan display                   */
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
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* perform fb specific ioctl&t;*/
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
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
r_int
id|register_framebuffer
c_func
(paren
r_char
op_star
comma
r_int
op_star
comma
r_struct
id|fb_ops
op_star
comma
r_int
comma
r_struct
id|fb_var_screeninfo
op_star
)paren
suffix:semicolon
r_int
id|unregister_framebuffer
c_func
(paren
r_int
)paren
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
id|u_char
op_star
id|screen_base
suffix:semicolon
multiline_comment|/* pointer to top of virtual screen */
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
DECL|member|vrows
r_int
id|vrows
suffix:semicolon
multiline_comment|/* number of virtual rows */
DECL|member|cursor_x
r_int
id|cursor_x
suffix:semicolon
multiline_comment|/* current cursor position */
DECL|member|cursor_y
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
DECL|member|fontheight
r_int
id|fontheight
suffix:semicolon
DECL|member|fontwidth
r_int
id|fontwidth
suffix:semicolon
DECL|member|userfont
r_int
id|userfont
suffix:semicolon
multiline_comment|/* != 0 if fontdata kmalloc()ed */
DECL|member|dispsw
r_struct
id|display_switch
op_star
id|dispsw
suffix:semicolon
multiline_comment|/* low level operations */
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
multiline_comment|/* at boottime detected video mode */
DECL|member|disp
r_struct
id|display
op_star
id|disp
suffix:semicolon
multiline_comment|/* pointer to display variables */
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
)paren
suffix:semicolon
multiline_comment|/* tell fb to (un)blank the screen */
DECL|member|setcmap
r_int
(paren
op_star
id|setcmap
)paren
(paren
r_struct
id|fb_cmap
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* tell fb to set the colormap */
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#if 1
DECL|macro|FBCMD_GET_CURRENTPAR
mdefine_line|#define FBCMD_GET_CURRENTPAR&t;    0xDEAD0005
DECL|macro|FBCMD_SET_CURRENTPAR
mdefine_line|#define FBCMD_SET_CURRENTPAR        0xDEAD8005
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
id|u_short
id|crsr_width
suffix:semicolon
multiline_comment|/* width and height of the cursor in */
DECL|member|crsr_height
id|u_short
id|crsr_height
suffix:semicolon
multiline_comment|/* pixels (zero if no cursor)&t;*/
DECL|member|crsr_xsize
id|u_short
id|crsr_xsize
suffix:semicolon
multiline_comment|/* cursor size in display pixels */
DECL|member|crsr_ysize
id|u_short
id|crsr_ysize
suffix:semicolon
DECL|member|crsr_color1
id|u_short
id|crsr_color1
suffix:semicolon
multiline_comment|/* colormap entry for cursor color1 */
DECL|member|crsr_color2
id|u_short
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
id|u_short
id|width
suffix:semicolon
DECL|member|height
id|u_short
id|height
suffix:semicolon
DECL|member|xspot
id|u_short
id|xspot
suffix:semicolon
DECL|member|yspot
id|u_short
id|yspot
suffix:semicolon
DECL|member|data
id|u_char
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
r_int
id|xoffset
suffix:semicolon
DECL|member|yoffset
r_int
id|yoffset
suffix:semicolon
DECL|member|mode
id|u_short
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
DECL|macro|FBCMD_DRAWLINE
mdefine_line|#define FBCMD_DRAWLINE&t;&t;0x4621
DECL|macro|FBCMD_MOVE
mdefine_line|#define FBCMD_MOVE&t;&t;0x4622
DECL|macro|FB_LINE_XOR
mdefine_line|#define FB_LINE_XOR&t;1
DECL|macro|FB_LINE_BOX
mdefine_line|#define FB_LINE_BOX&t;2
DECL|macro|FB_LINE_FILLED
mdefine_line|#define FB_LINE_FILLED&t;4
DECL|struct|fb_line
r_struct
id|fb_line
(brace
DECL|member|start_x
r_int
id|start_x
suffix:semicolon
DECL|member|start_y
r_int
id|start_y
suffix:semicolon
DECL|member|end_x
r_int
id|end_x
suffix:semicolon
DECL|member|end_y
r_int
id|end_y
suffix:semicolon
DECL|member|color
r_int
id|color
suffix:semicolon
DECL|member|option
r_int
id|option
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fb_move
r_struct
id|fb_move
(brace
DECL|member|src_x
r_int
id|src_x
suffix:semicolon
DECL|member|src_y
r_int
id|src_y
suffix:semicolon
DECL|member|dest_x
r_int
id|dest_x
suffix:semicolon
DECL|member|dest_y
r_int
id|dest_y
suffix:semicolon
DECL|member|height
r_int
id|height
suffix:semicolon
DECL|member|width
r_int
id|width
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* Preliminary */
macro_line|#endif /* _LINUX_FB_H */
eof
