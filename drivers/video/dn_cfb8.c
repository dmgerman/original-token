macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
macro_line|#include &lt;asm/apollohw.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;dn_accel.h&quot;
macro_line|#include &quot;fbcon.h&quot;
macro_line|#include &quot;fbcon-mfb.h&quot;
multiline_comment|/* apollo video HW definitions */
multiline_comment|/*&n; * Control Registers.   IOBASE + $x&n; *&n; * Note: these are the Memory/IO BASE definitions for a mono card set to the&n; * alternate address&n; *&n; * Control 3A and 3B serve identical functions except that 3A&n; * deals with control 1 and 3b deals with Color LUT reg.&n; */
DECL|macro|AP_IOBASE
mdefine_line|#define AP_IOBASE       0x3d0          /* Base address of 1 plane board. */
DECL|macro|AP_STATUS
mdefine_line|#define AP_STATUS       isaIO2mem(AP_IOBASE+0) /* Status register.  Read */
DECL|macro|AP_WRITE_ENABLE
mdefine_line|#define AP_WRITE_ENABLE isaIO2mem(AP_IOBASE+0) /* Write Enable Register Write */
DECL|macro|AP_DEVICE_ID
mdefine_line|#define AP_DEVICE_ID    isaIO2mem(AP_IOBASE+1) /* Device ID Register. Read */
DECL|macro|AP_ROP_0
mdefine_line|#define AP_ROP_0        isaIO2mem(AP_IOBASE+2) /* Raster Operation reg. Write Word */
DECL|macro|AP_ROP_1
mdefine_line|#define AP_ROP_1        isaIO2mem(AP_IOBASE+4) /* Raster Operation reg. Write Word */
DECL|macro|AP_DIAG_MEM_REQ
mdefine_line|#define AP_DIAG_MEM_REQ isaIO2mem(AP_IOBASE+6) /* Diagnostic Memory Request. Write Word */
DECL|macro|AP_CONTROL_0
mdefine_line|#define AP_CONTROL_0    isaIO2mem(AP_IOBASE+8) /* Control Register 0.  Read/Write */
DECL|macro|AP_LUT_DATA
mdefine_line|#define AP_LUT_DATA     isaIO2mem(AP_IOBASE+9) /* Control Register 0.  Read/Write */
DECL|macro|AP_CONTROL_1
mdefine_line|#define AP_CONTROL_1    isaIO2mem(AP_IOBASE+0xa) /* Control Register 1.  Read/Write */
DECL|macro|AP_LUT_CONTROL
mdefine_line|#define AP_LUT_CONTROL  isaIO2mem(AP_IOBASE+0xb) /* Control Register 1.  Read/Write */
DECL|macro|AP_CONTROL_2A
mdefine_line|#define AP_CONTROL_2A   isaIO2mem(AP_IOBASE+0xc) /* Control Register 2. Read/Write */
DECL|macro|AP_CONTROL_2B
mdefine_line|#define AP_CONTROL_2B   isaIO2mem(AP_IOBASE+0xd) /* Control Register 2. Read/Write */
DECL|macro|AP_CONTROL_3A
mdefine_line|#define AP_CONTROL_3A   isaIO2mem(AP_IOBASE+0xe) /* Control Register 3a. Read/Write */
DECL|macro|AP_CONTROL_3B
mdefine_line|#define AP_CONTROL_3B   isaIO2mem(AP_IOBASE+0xf) /* Control Register 3a. Read/Write */
DECL|macro|FRAME_BUFFER_START
mdefine_line|#define FRAME_BUFFER_START 0x0A0000
DECL|macro|FRAME_BUFFER_LEN
mdefine_line|#define FRAME_BUFFER_LEN 0x20000
multiline_comment|/* CREG 0 */
DECL|macro|VECTOR_MODE
mdefine_line|#define VECTOR_MODE 0x40 /* 010x.xxxx */
DECL|macro|DBLT_MODE
mdefine_line|#define DBLT_MODE   0x80 /* 100x.xxxx */
DECL|macro|NORMAL_MODE
mdefine_line|#define NORMAL_MODE 0xE0 /* 111x.xxxx */
DECL|macro|SHIFT_BITS
mdefine_line|#define SHIFT_BITS  0x1F /* xxx1.1111 */
multiline_comment|/* other bits are Shift value */
multiline_comment|/* CREG 1 */
DECL|macro|AD_BLT
mdefine_line|#define AD_BLT      0x80 /* 1xxx.xxxx */
DECL|macro|ROP_EN
mdefine_line|#define ROP_EN          0x10 /* xxx1.xxxx */
DECL|macro|DST_EQ_SRC
mdefine_line|#define DST_EQ_SRC      0x00 /* xxx0.xxxx */
DECL|macro|nRESET_SYNC
mdefine_line|#define nRESET_SYNC     0x08 /* xxxx.1xxx */
DECL|macro|SYNC_ENAB
mdefine_line|#define SYNC_ENAB       0x02 /* xxxx.xx1x */
DECL|macro|BLANK_DISP
mdefine_line|#define BLANK_DISP      0x00 /* xxxx.xxx0 */
DECL|macro|ENAB_DISP
mdefine_line|#define ENAB_DISP       0x01 /* xxxx.xxx1 */
DECL|macro|NORM_CREG1
mdefine_line|#define NORM_CREG1      (nRESET_SYNC | SYNC_ENAB | ENAB_DISP) /* no reset sync */
multiline_comment|/* CREG 2B */
multiline_comment|/*&n; * Following 3 defines are common to 1, 4 and 8 plane.&n; */
DECL|macro|S_DATA_1s
mdefine_line|#define S_DATA_1s   0x00 /* 00xx.xxxx */ /* set source to all 1&squot;s -- vector drawing */
DECL|macro|S_DATA_PIX
mdefine_line|#define S_DATA_PIX  0x40 /* 01xx.xxxx */ /* takes source from ls-bits and replicates over 16 bits */
DECL|macro|S_DATA_PLN
mdefine_line|#define S_DATA_PLN  0xC0 /* 11xx.xxxx */ /* normal, each data access =16-bits in&n; one plane of image mem */
multiline_comment|/* CREG 3A/CREG 3B */
DECL|macro|RESET_CREG
macro_line|#       define RESET_CREG 0x80 /* 1000.0000 */
multiline_comment|/* ROP REG  -  all one nibble */
multiline_comment|/*      ********* NOTE : this is used r0,r1,r2,r3 *********** */
DECL|macro|ROP
mdefine_line|#define ROP(r2,r3,r0,r1) ( (U_SHORT)((r0)|((r1)&lt;&lt;4)|((r2)&lt;&lt;8)|((r3)&lt;&lt;12)) )
DECL|macro|DEST_ZERO
mdefine_line|#define DEST_ZERO               0x0
DECL|macro|SRC_AND_DEST
mdefine_line|#define SRC_AND_DEST    0x1
DECL|macro|SRC_AND_nDEST
mdefine_line|#define SRC_AND_nDEST   0x2
DECL|macro|SRC
mdefine_line|#define SRC                             0x3
DECL|macro|nSRC_AND_DEST
mdefine_line|#define nSRC_AND_DEST   0x4
DECL|macro|DEST
mdefine_line|#define DEST                    0x5
DECL|macro|SRC_XOR_DEST
mdefine_line|#define SRC_XOR_DEST    0x6
DECL|macro|SRC_OR_DEST
mdefine_line|#define SRC_OR_DEST             0x7
DECL|macro|SRC_NOR_DEST
mdefine_line|#define SRC_NOR_DEST    0x8
DECL|macro|SRC_XNOR_DEST
mdefine_line|#define SRC_XNOR_DEST   0x9
DECL|macro|nDEST
mdefine_line|#define nDEST                   0xA
DECL|macro|SRC_OR_nDEST
mdefine_line|#define SRC_OR_nDEST    0xB
DECL|macro|nSRC
mdefine_line|#define nSRC                    0xC
DECL|macro|nSRC_OR_DEST
mdefine_line|#define nSRC_OR_DEST    0xD
DECL|macro|SRC_NAND_DEST
mdefine_line|#define SRC_NAND_DEST   0xE
DECL|macro|DEST_ONE
mdefine_line|#define DEST_ONE                0xF
DECL|macro|SWAP
mdefine_line|#define SWAP(A) ((A&gt;&gt;8) | ((A&amp;0xff) &lt;&lt;8))
r_void
id|dn_video_setup
c_func
(paren
r_char
op_star
id|options
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
multiline_comment|/* frame buffer operations */
r_static
r_int
id|dn_fb_open
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|dn_fb_release
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|dn_fb_get_fix
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
r_static
r_int
id|dn_fb_get_var
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
r_static
r_int
id|dn_fb_set_var
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
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|dn_fb_get_cmap
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
r_static
r_int
id|dn_fb_set_cmap
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
r_static
r_int
id|dn_fb_pan_display
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
r_static
r_int
id|dn_fb_ioctl
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
r_static
r_int
id|dnfbcon_switch
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
r_static
r_int
id|dnfbcon_updatevar
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
r_static
r_void
id|dnfbcon_blank
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
r_static
r_void
id|dn_fb_set_disp
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
DECL|variable|disp
r_static
r_struct
id|display
id|disp
(braket
id|MAX_NR_CONSOLES
)braket
suffix:semicolon
DECL|variable|fb_info
r_static
r_struct
id|fb_info
id|fb_info
suffix:semicolon
DECL|variable|dn_fb_ops
r_static
r_struct
id|fb_ops
id|dn_fb_ops
op_assign
(brace
id|dn_fb_open
comma
id|dn_fb_release
comma
id|dn_fb_get_fix
comma
id|dn_fb_get_var
comma
id|dn_fb_set_var
comma
id|dn_fb_get_cmap
comma
id|dn_fb_set_cmap
comma
id|dn_fb_pan_display
comma
id|dn_fb_ioctl
)brace
suffix:semicolon
DECL|variable|currcon
r_static
r_int
id|currcon
op_assign
l_int|0
suffix:semicolon
DECL|macro|NUM_TOTAL_MODES
mdefine_line|#define NUM_TOTAL_MODES 1
DECL|variable|dn_fb_predefined
r_struct
id|fb_var_screeninfo
id|dn_fb_predefined
(braket
)braket
op_assign
(brace
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|dn_fb_name
r_static
r_char
id|dn_fb_name
(braket
)braket
op_assign
l_string|&quot;Apollo &quot;
suffix:semicolon
multiline_comment|/* accel stuff */
DECL|macro|USE_DN_ACCEL
mdefine_line|#define USE_DN_ACCEL
DECL|variable|dispsw_apollofb
r_static
r_struct
id|display_switch
id|dispsw_apollofb
suffix:semicolon
DECL|function|dn_fb_open
r_static
r_int
id|dn_fb_open
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/*&n;         * Nothing, only a usage count for the moment&n;         */
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dn_fb_release
r_static
r_int
id|dn_fb_release
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dn_fb_get_fix
r_static
r_int
id|dn_fb_get_fix
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
(brace
id|strcpy
c_func
(paren
id|fix-&gt;id
comma
l_string|&quot;Apollo Color8&quot;
)paren
suffix:semicolon
id|fix-&gt;smem_start
op_assign
(paren
r_char
op_star
)paren
(paren
id|FRAME_BUFFER_START
op_plus
id|IO_BASE
)paren
suffix:semicolon
id|fix-&gt;smem_len
op_assign
id|FRAME_BUFFER_LEN
suffix:semicolon
id|fix-&gt;type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
id|fix-&gt;type_aux
op_assign
l_int|0
suffix:semicolon
id|fix-&gt;visual
op_assign
id|FB_VISUAL_MONO10
suffix:semicolon
id|fix-&gt;xpanstep
op_assign
l_int|0
suffix:semicolon
id|fix-&gt;ypanstep
op_assign
l_int|0
suffix:semicolon
id|fix-&gt;ywrapstep
op_assign
l_int|0
suffix:semicolon
id|fix-&gt;line_length
op_assign
l_int|128
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dn_fb_get_var
r_static
r_int
id|dn_fb_get_var
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
(brace
id|var-&gt;xres
op_assign
l_int|1024
suffix:semicolon
id|var-&gt;yres
op_assign
l_int|800
suffix:semicolon
id|var-&gt;xres_virtual
op_assign
l_int|1024
suffix:semicolon
id|var-&gt;yres_virtual
op_assign
l_int|1024
suffix:semicolon
id|var-&gt;xoffset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;yoffset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;bits_per_pixel
op_assign
l_int|1
suffix:semicolon
id|var-&gt;grayscale
op_assign
l_int|0
suffix:semicolon
id|var-&gt;nonstd
op_assign
l_int|0
suffix:semicolon
id|var-&gt;activate
op_assign
l_int|0
suffix:semicolon
id|var-&gt;height
op_assign
op_minus
l_int|1
suffix:semicolon
id|var-&gt;width
op_assign
op_minus
l_int|1
suffix:semicolon
id|var-&gt;pixclock
op_assign
l_int|0
suffix:semicolon
id|var-&gt;left_margin
op_assign
l_int|0
suffix:semicolon
id|var-&gt;right_margin
op_assign
l_int|0
suffix:semicolon
id|var-&gt;hsync_len
op_assign
l_int|0
suffix:semicolon
id|var-&gt;vsync_len
op_assign
l_int|0
suffix:semicolon
id|var-&gt;sync
op_assign
l_int|0
suffix:semicolon
id|var-&gt;vmode
op_assign
id|FB_VMODE_NONINTERLACED
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dn_fb_set_var
r_static
r_int
id|dn_fb_set_var
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
(brace
id|printk
c_func
(paren
l_string|&quot;fb_set_var&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;xres
op_ne
l_int|1024
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|var-&gt;yres
op_ne
l_int|800
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|var-&gt;xres_virtual
op_ne
l_int|1024
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|var-&gt;yres_virtual
op_ne
l_int|1024
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|var-&gt;xoffset
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|var-&gt;yoffset
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
op_ne
l_int|1
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|var-&gt;grayscale
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|var-&gt;nonstd
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|var-&gt;activate
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|var-&gt;pixclock
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|var-&gt;left_margin
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|var-&gt;right_margin
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|var-&gt;hsync_len
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|var-&gt;vsync_len
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|var-&gt;sync
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|var-&gt;vmode
op_ne
id|FB_VMODE_NONINTERLACED
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dn_fb_get_cmap
r_static
r_int
id|dn_fb_get_cmap
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
(brace
id|printk
c_func
(paren
l_string|&quot;get cmap not supported&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|dn_fb_set_cmap
r_static
r_int
id|dn_fb_set_cmap
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
(brace
id|printk
c_func
(paren
l_string|&quot;set cmap not supported&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|dn_fb_pan_display
r_static
r_int
id|dn_fb_pan_display
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
(brace
id|printk
c_func
(paren
l_string|&quot;panning not supported&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|dn_fb_ioctl
r_static
r_int
id|dn_fb_ioctl
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
(brace
id|printk
c_func
(paren
l_string|&quot;no IOCTLs as of yet.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|dn_fb_set_disp
r_static
r_void
id|dn_fb_set_disp
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
(brace
r_struct
id|fb_fix_screeninfo
id|fix
suffix:semicolon
id|dn_fb_get_fix
c_func
(paren
op_amp
id|fix
comma
id|con
comma
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|con
op_eq
op_minus
l_int|1
)paren
(brace
id|con
op_assign
l_int|0
suffix:semicolon
)brace
id|disp
(braket
id|con
)braket
dot
id|screen_base
op_assign
(paren
id|u_char
op_star
)paren
id|fix.smem_start
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;screenbase: %p&bslash;n&quot;
comma
id|fix.smem_start
)paren
suffix:semicolon
id|disp
(braket
id|con
)braket
dot
id|visual
op_assign
id|fix.visual
suffix:semicolon
id|disp
(braket
id|con
)braket
dot
id|type
op_assign
id|fix.type
suffix:semicolon
id|disp
(braket
id|con
)braket
dot
id|type_aux
op_assign
id|fix.type_aux
suffix:semicolon
id|disp
(braket
id|con
)braket
dot
id|ypanstep
op_assign
id|fix.ypanstep
suffix:semicolon
id|disp
(braket
id|con
)braket
dot
id|ywrapstep
op_assign
id|fix.ywrapstep
suffix:semicolon
id|disp
(braket
id|con
)braket
dot
id|can_soft_blank
op_assign
l_int|1
suffix:semicolon
id|disp
(braket
id|con
)braket
dot
id|inverse
op_assign
l_int|0
suffix:semicolon
id|disp
(braket
id|con
)braket
dot
id|line_length
op_assign
id|fix.line_length
suffix:semicolon
id|disp
(braket
id|con
)braket
dot
id|dispsw
op_assign
op_amp
id|dispsw_apollofb
suffix:semicolon
)brace
DECL|function|dn_fb_init
r_int
r_int
id|dn_fb_init
c_func
(paren
r_int
r_int
id|mem_start
)paren
(brace
r_int
id|err
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;dn_fb_init&bslash;n&quot;
)paren
suffix:semicolon
id|fb_info.changevar
op_assign
l_int|NULL
suffix:semicolon
id|strcpy
c_func
(paren
op_amp
id|fb_info.modename
(braket
l_int|0
)braket
comma
id|dn_fb_name
)paren
suffix:semicolon
id|fb_info.fontname
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|fb_info.disp
op_assign
id|disp
suffix:semicolon
id|fb_info.switch_con
op_assign
op_amp
id|dnfbcon_switch
suffix:semicolon
id|fb_info.updatevar
op_assign
op_amp
id|dnfbcon_updatevar
suffix:semicolon
id|fb_info.blank
op_assign
op_amp
id|dnfbcon_blank
suffix:semicolon
id|fb_info.node
op_assign
op_minus
l_int|1
suffix:semicolon
id|fb_info.fbops
op_assign
op_amp
id|dn_fb_ops
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;dn_fb_init: register&bslash;n&quot;
)paren
suffix:semicolon
id|err
op_assign
id|register_framebuffer
c_func
(paren
op_amp
id|fb_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;unable to register apollo frame buffer&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* now we have registered we can safely setup the hardware */
id|outb
c_func
(paren
id|RESET_CREG
comma
id|AP_CONTROL_3A
)paren
suffix:semicolon
id|outb
c_func
(paren
id|RESET_CREG
comma
id|AP_CONTROL_3B
)paren
suffix:semicolon
id|outw
c_func
(paren
l_int|0x0
comma
id|AP_WRITE_ENABLE
)paren
suffix:semicolon
id|outb
c_func
(paren
id|NORMAL_MODE
comma
id|AP_CONTROL_0
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|AD_BLT
op_or
id|DST_EQ_SRC
op_or
id|NORM_CREG1
)paren
comma
id|AP_CONTROL_1
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|AP_CONTROL_2A
)paren
suffix:semicolon
id|outb
c_func
(paren
id|S_DATA_PLN
comma
id|AP_CONTROL_2B
)paren
suffix:semicolon
id|outw
c_func
(paren
id|SWAP
c_func
(paren
l_int|0x3
)paren
comma
id|AP_ROP_1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;apollo frame buffer alive and kicking !&bslash;n&quot;
)paren
suffix:semicolon
id|dn_fb_get_var
c_func
(paren
op_amp
id|disp
(braket
l_int|0
)braket
dot
id|var
comma
l_int|0
comma
op_amp
id|fb_info
)paren
suffix:semicolon
id|dn_fb_set_disp
c_func
(paren
op_minus
l_int|1
comma
op_amp
id|fb_info
)paren
suffix:semicolon
r_return
id|mem_start
suffix:semicolon
)brace
DECL|function|dnfbcon_switch
r_static
r_int
id|dnfbcon_switch
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
(brace
id|currcon
op_assign
id|con
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dnfbcon_updatevar
r_static
r_int
id|dnfbcon_updatevar
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
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dnfbcon_blank
r_static
r_void
id|dnfbcon_blank
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
(brace
r_if
c_cond
(paren
id|blank
)paren
(brace
id|outb
c_func
(paren
l_int|0x0
comma
id|AP_CONTROL_3A
)paren
suffix:semicolon
)brace
r_else
(brace
id|outb
c_func
(paren
l_int|0x1
comma
id|AP_CONTROL_3A
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
DECL|function|dn_video_setup
r_void
id|dn_video_setup
c_func
(paren
r_char
op_star
id|options
comma
r_int
op_star
id|ints
)paren
(brace
r_return
suffix:semicolon
)brace
DECL|function|dn_bitblt
r_void
id|dn_bitblt
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|x_src
comma
r_int
id|y_src
comma
r_int
id|x_dest
comma
r_int
id|y_dest
comma
r_int
id|x_count
comma
r_int
id|y_count
)paren
(brace
r_int
id|incr
comma
id|y_delta
comma
id|pre_read
op_assign
l_int|0
comma
id|x_end
comma
id|x_word_count
suffix:semicolon
id|ushort
op_star
id|src
comma
id|dummy
suffix:semicolon
id|uint
id|start_mask
comma
id|end_mask
comma
id|dest
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
id|incr
op_assign
(paren
id|y_dest
op_le
id|y_src
)paren
ques
c_cond
l_int|1
suffix:colon
op_minus
l_int|1
suffix:semicolon
id|src
op_assign
(paren
id|ushort
op_star
)paren
(paren
id|p-&gt;screen_base
op_plus
id|y_src
op_star
id|p-&gt;next_line
op_plus
(paren
id|x_src
op_rshift
l_int|4
)paren
)paren
suffix:semicolon
id|dest
op_assign
id|y_dest
op_star
(paren
id|p-&gt;next_line
op_rshift
l_int|1
)paren
op_plus
(paren
id|x_dest
op_rshift
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|incr
OG
l_int|0
)paren
(brace
id|y_delta
op_assign
(paren
id|p-&gt;next_line
op_star
l_int|8
)paren
op_minus
id|x_src
op_minus
id|x_count
suffix:semicolon
id|x_end
op_assign
id|x_dest
op_plus
id|x_count
op_minus
l_int|1
suffix:semicolon
id|x_word_count
op_assign
(paren
id|x_end
op_rshift
l_int|4
)paren
op_minus
(paren
id|x_dest
op_rshift
l_int|4
)paren
op_plus
l_int|1
suffix:semicolon
id|start_mask
op_assign
l_int|0xffff0000
op_rshift
(paren
id|x_dest
op_amp
l_int|0xf
)paren
suffix:semicolon
id|end_mask
op_assign
l_int|0x7ffff
op_rshift
(paren
id|x_end
op_amp
l_int|0xf
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
(paren
(paren
id|x_dest
op_amp
l_int|0xf
)paren
op_minus
(paren
id|x_src
op_amp
l_int|0xf
)paren
)paren
op_mod
l_int|16
)paren
op_or
(paren
l_int|0x4
op_lshift
l_int|5
)paren
comma
id|AP_CONTROL_0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|x_dest
op_amp
l_int|0xf
)paren
OL
(paren
id|x_src
op_amp
l_int|0xf
)paren
)paren
(brace
id|pre_read
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
(brace
id|y_delta
op_assign
op_minus
(paren
(paren
id|p-&gt;next_line
op_star
l_int|8
)paren
op_minus
id|x_src
op_minus
id|x_count
)paren
suffix:semicolon
id|x_end
op_assign
id|x_dest
op_minus
id|x_count
op_plus
l_int|1
suffix:semicolon
id|x_word_count
op_assign
(paren
id|x_dest
op_rshift
l_int|4
)paren
op_minus
(paren
id|x_end
op_rshift
l_int|4
)paren
op_plus
l_int|1
suffix:semicolon
id|start_mask
op_assign
l_int|0x7ffff
op_rshift
(paren
id|x_dest
op_amp
l_int|0xf
)paren
suffix:semicolon
id|end_mask
op_assign
l_int|0xffff0000
op_rshift
(paren
id|x_end
op_amp
l_int|0xf
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
(paren
op_minus
(paren
(paren
id|x_src
op_amp
l_int|0xf
)paren
op_minus
(paren
id|x_dest
op_amp
l_int|0xf
)paren
)paren
)paren
op_mod
l_int|16
)paren
op_or
(paren
l_int|0x4
op_lshift
l_int|5
)paren
comma
id|AP_CONTROL_0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|x_dest
op_amp
l_int|0xf
)paren
OG
(paren
id|x_src
op_amp
l_int|0xf
)paren
)paren
(brace
id|pre_read
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|y_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pre_read
)paren
(brace
id|dummy
op_assign
op_star
id|src
suffix:semicolon
id|src
op_add_assign
id|incr
suffix:semicolon
)brace
r_if
c_cond
(paren
id|x_word_count
)paren
(brace
id|outb
c_func
(paren
id|start_mask
comma
id|AP_WRITE_ENABLE
)paren
suffix:semicolon
op_star
id|src
op_assign
id|dest
suffix:semicolon
id|src
op_add_assign
id|incr
suffix:semicolon
id|dest
op_add_assign
id|incr
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|AP_WRITE_ENABLE
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|1
suffix:semicolon
id|j
OL
(paren
id|x_word_count
op_minus
l_int|1
)paren
suffix:semicolon
id|j
op_increment
)paren
(brace
op_star
id|src
op_assign
id|dest
suffix:semicolon
id|src
op_add_assign
id|incr
suffix:semicolon
id|dest
op_add_assign
id|incr
suffix:semicolon
)brace
id|outb
c_func
(paren
id|start_mask
comma
id|AP_WRITE_ENABLE
)paren
suffix:semicolon
op_star
id|src
op_assign
id|dest
suffix:semicolon
id|dest
op_add_assign
id|incr
suffix:semicolon
id|src
op_add_assign
id|incr
suffix:semicolon
)brace
r_else
(brace
id|outb
c_func
(paren
id|start_mask
op_or
id|end_mask
comma
id|AP_WRITE_ENABLE
)paren
suffix:semicolon
op_star
id|src
op_assign
id|dest
suffix:semicolon
id|dest
op_add_assign
id|incr
suffix:semicolon
id|src
op_add_assign
id|incr
suffix:semicolon
)brace
id|src
op_add_assign
(paren
id|y_delta
op_div
l_int|16
)paren
suffix:semicolon
id|dest
op_add_assign
(paren
id|y_delta
op_div
l_int|16
)paren
suffix:semicolon
)brace
id|outb
c_func
(paren
id|NORMAL_MODE
comma
id|AP_CONTROL_0
)paren
suffix:semicolon
)brace
DECL|function|bmove_apollofb
r_static
r_void
id|bmove_apollofb
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|dy
comma
r_int
id|dx
comma
r_int
id|height
comma
r_int
id|width
)paren
(brace
macro_line|#ifdef USE_DN_ACCEL
id|dn_bitblt
c_func
(paren
id|p
comma
id|sx
comma
id|sy
op_star
id|p-&gt;fontheight
comma
id|dx
comma
id|dy
op_star
id|p-&gt;fontheight
comma
id|width
op_star
id|p-&gt;fontwidth
comma
id|height
op_star
id|p-&gt;fontheight
)paren
suffix:semicolon
macro_line|#else
id|u_char
op_star
id|src
comma
op_star
id|dest
suffix:semicolon
id|u_int
id|rows
suffix:semicolon
r_if
c_cond
(paren
id|sx
op_eq
l_int|0
op_logical_and
id|dx
op_eq
l_int|0
op_logical_and
id|width
op_eq
id|p-&gt;next_line
)paren
(brace
id|src
op_assign
id|p-&gt;screen_base
op_plus
id|sy
op_star
id|p-&gt;fontheight
op_star
id|width
suffix:semicolon
id|dest
op_assign
id|p-&gt;screen_base
op_plus
id|dy
op_star
id|p-&gt;fontheight
op_star
id|width
suffix:semicolon
id|mymemmove
c_func
(paren
id|dest
comma
id|src
comma
id|height
op_star
id|p-&gt;fontheight
op_star
id|width
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dy
op_le
id|sy
)paren
(brace
id|src
op_assign
id|p-&gt;screen_base
op_plus
id|sy
op_star
id|p-&gt;fontheight
op_star
id|p-&gt;next_line
op_plus
id|sx
suffix:semicolon
id|dest
op_assign
id|p-&gt;screen_base
op_plus
id|dy
op_star
id|p-&gt;fontheight
op_star
id|p-&gt;next_line
op_plus
id|dx
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|height
op_star
id|p-&gt;fontheight
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
)paren
(brace
id|mymemmove
c_func
(paren
id|dest
comma
id|src
comma
id|width
)paren
suffix:semicolon
id|src
op_add_assign
id|p-&gt;next_line
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_line
suffix:semicolon
)brace
)brace
r_else
(brace
id|src
op_assign
id|p-&gt;screen_base
op_plus
(paren
(paren
id|sy
op_plus
id|height
)paren
op_star
id|p-&gt;fontheight
op_minus
l_int|1
)paren
op_star
id|p-&gt;next_line
op_plus
id|sx
suffix:semicolon
id|dest
op_assign
id|p-&gt;screen_base
op_plus
(paren
(paren
id|dy
op_plus
id|height
)paren
op_star
id|p-&gt;fontheight
op_minus
l_int|1
)paren
op_star
id|p-&gt;next_line
op_plus
id|dx
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|height
op_star
id|p-&gt;fontheight
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
)paren
(brace
id|mymemmove
c_func
(paren
id|dest
comma
id|src
comma
id|width
)paren
suffix:semicolon
id|src
op_sub_assign
id|p-&gt;next_line
suffix:semicolon
id|dest
op_sub_assign
id|p-&gt;next_line
suffix:semicolon
)brace
)brace
macro_line|#endif
)brace
DECL|function|clear_apollofb
r_static
r_void
id|clear_apollofb
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|height
comma
r_int
id|width
)paren
(brace
id|u_char
op_star
id|dest
suffix:semicolon
id|u_int
id|rows
suffix:semicolon
id|dest
op_assign
id|p-&gt;screen_base
op_plus
id|sy
op_star
id|p-&gt;fontheight
op_star
id|p-&gt;next_line
op_plus
id|sx
suffix:semicolon
r_if
c_cond
(paren
id|sx
op_eq
l_int|0
op_logical_and
id|width
op_eq
id|p-&gt;next_line
)paren
r_if
c_cond
(paren
id|attr_reverse
c_func
(paren
id|p
comma
id|conp
)paren
)paren
id|mymemset
c_func
(paren
id|dest
comma
id|height
op_star
id|p-&gt;fontheight
op_star
id|width
)paren
suffix:semicolon
r_else
id|mymemclear
c_func
(paren
id|dest
comma
id|height
op_star
id|p-&gt;fontheight
op_star
id|width
)paren
suffix:semicolon
r_else
r_for
c_loop
(paren
id|rows
op_assign
id|height
op_star
id|p-&gt;fontheight
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_line
)paren
r_if
c_cond
(paren
id|attr_reverse
c_func
(paren
id|p
comma
id|conp
)paren
)paren
id|mymemset
c_func
(paren
id|dest
comma
id|width
)paren
suffix:semicolon
r_else
id|mymemclear_small
c_func
(paren
id|dest
comma
id|width
)paren
suffix:semicolon
)brace
DECL|function|putc_apollofb
r_static
r_void
id|putc_apollofb
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_int
id|c
comma
r_int
id|yy
comma
r_int
id|xx
)paren
(brace
id|u_char
op_star
id|dest
comma
op_star
id|cdat
suffix:semicolon
id|u_int
id|rows
comma
id|bold
comma
id|revs
comma
id|underl
suffix:semicolon
id|u_char
id|d
suffix:semicolon
id|c
op_and_assign
l_int|0xff
suffix:semicolon
id|dest
op_assign
id|p-&gt;screen_base
op_plus
id|yy
op_star
id|p-&gt;fontheight
op_star
id|p-&gt;next_line
op_plus
id|xx
suffix:semicolon
id|cdat
op_assign
id|p-&gt;fontdata
op_plus
id|c
op_star
id|p-&gt;fontheight
suffix:semicolon
id|bold
op_assign
id|attr_bold
c_func
(paren
id|p
comma
id|conp
)paren
suffix:semicolon
id|revs
op_assign
id|attr_reverse
c_func
(paren
id|p
comma
id|conp
)paren
suffix:semicolon
id|underl
op_assign
id|attr_underline
c_func
(paren
id|p
comma
id|conp
)paren
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|p-&gt;fontheight
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_line
)paren
(brace
id|d
op_assign
op_star
id|cdat
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|underl
op_logical_and
op_logical_neg
id|rows
)paren
id|d
op_assign
l_int|0xff
suffix:semicolon
r_else
r_if
c_cond
(paren
id|bold
)paren
id|d
op_or_assign
id|d
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|revs
)paren
id|d
op_assign
op_complement
id|d
suffix:semicolon
op_star
id|dest
op_assign
id|d
suffix:semicolon
)brace
)brace
DECL|function|putcs_apollofb
r_static
r_void
id|putcs_apollofb
c_func
(paren
r_struct
id|vc_data
op_star
id|conp
comma
r_struct
id|display
op_star
id|p
comma
r_const
r_char
op_star
id|s
comma
r_int
id|count
comma
r_int
id|yy
comma
r_int
id|xx
)paren
(brace
id|u_char
op_star
id|dest
comma
op_star
id|dest0
comma
op_star
id|cdat
suffix:semicolon
id|u_int
id|rows
comma
id|bold
comma
id|revs
comma
id|underl
suffix:semicolon
id|u_char
id|c
comma
id|d
suffix:semicolon
id|dest0
op_assign
id|p-&gt;screen_base
op_plus
id|yy
op_star
id|p-&gt;fontheight
op_star
id|p-&gt;next_line
op_plus
id|xx
suffix:semicolon
id|bold
op_assign
id|attr_bold
c_func
(paren
id|p
comma
id|conp
)paren
suffix:semicolon
id|revs
op_assign
id|attr_reverse
c_func
(paren
id|p
comma
id|conp
)paren
suffix:semicolon
id|underl
op_assign
id|attr_underline
c_func
(paren
id|p
comma
id|conp
)paren
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
id|c
op_assign
op_star
id|s
op_increment
suffix:semicolon
id|dest
op_assign
id|dest0
op_increment
suffix:semicolon
id|cdat
op_assign
id|p-&gt;fontdata
op_plus
id|c
op_star
id|p-&gt;fontheight
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|p-&gt;fontheight
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_line
)paren
(brace
id|d
op_assign
op_star
id|cdat
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|underl
op_logical_and
op_logical_neg
id|rows
)paren
id|d
op_assign
l_int|0xff
suffix:semicolon
r_else
r_if
c_cond
(paren
id|bold
)paren
id|d
op_or_assign
id|d
op_rshift
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|revs
)paren
id|d
op_assign
op_complement
id|d
suffix:semicolon
op_star
id|dest
op_assign
id|d
suffix:semicolon
)brace
)brace
)brace
DECL|function|rev_char_apollofb
r_static
r_void
id|rev_char_apollofb
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|xx
comma
r_int
id|yy
)paren
(brace
id|u_char
op_star
id|dest
suffix:semicolon
id|u_int
id|rows
suffix:semicolon
id|dest
op_assign
id|p-&gt;screen_base
op_plus
id|yy
op_star
id|p-&gt;fontheight
op_star
id|p-&gt;next_line
op_plus
id|xx
suffix:semicolon
r_for
c_loop
(paren
id|rows
op_assign
id|p-&gt;fontheight
suffix:semicolon
id|rows
op_decrement
suffix:semicolon
id|dest
op_add_assign
id|p-&gt;next_line
)paren
op_star
id|dest
op_assign
op_complement
op_star
id|dest
suffix:semicolon
)brace
DECL|variable|dispsw_apollofb
r_static
r_struct
id|display_switch
id|dispsw_apollofb
op_assign
(brace
id|fbcon_mfb_setup
comma
id|bmove_apollofb
comma
id|clear_apollofb
comma
id|putc_apollofb
comma
id|putcs_apollofb
comma
id|rev_char_apollofb
)brace
suffix:semicolon
eof
