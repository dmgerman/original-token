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
macro_line|#include &lt;asm/apollohw.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;fbcon-mfb.h&quot;
multiline_comment|/* apollo video HW definitions */
multiline_comment|/*&n; * Control Registers.   IOBASE + $x&n; *&n; * Note: these are the Memory/IO BASE definitions for a mono card set to the&n; * alternate address&n; *&n; * Control 3A and 3B serve identical functions except that 3A&n; * deals with control 1 and 3b deals with Color LUT reg.&n; */
DECL|macro|AP_IOBASE
mdefine_line|#define AP_IOBASE       0x5d80          /* Base address of 1 plane board. */
DECL|macro|AP_STATUS
mdefine_line|#define AP_STATUS       0x5d80          /* Status register.  Read */
DECL|macro|AP_WRITE_ENABLE
mdefine_line|#define AP_WRITE_ENABLE 0x5d80          /* Write Enable Register Write */
DECL|macro|AP_DEVICE_ID
mdefine_line|#define AP_DEVICE_ID    0x5d81          /* Device ID Register. Read */
DECL|macro|AP_ROP_1
mdefine_line|#define AP_ROP_1        0x5d82          /* Raster Operation reg. Write Word */
DECL|macro|AP_DIAG_MEM_REQ
mdefine_line|#define AP_DIAG_MEM_REQ 0x5d84          /* Diagnostic Memory Request. Write Word */
DECL|macro|AP_CONTROL_0
mdefine_line|#define AP_CONTROL_0    0x5d88          /* Control Register 0.  Read/Write */
DECL|macro|AP_CONTROL_1
mdefine_line|#define AP_CONTROL_1    0x5d8a          /* Control Register 1.  Read/Write */
DECL|macro|AP_CONTROL_3A
mdefine_line|#define AP_CONTROL_3A   0x5d8e          /* Control Register 3a. Read/Write */
DECL|macro|AP_CONTROL_2
mdefine_line|#define AP_CONTROL_2    0x5d8c          /* Control Register 2. Read/Write */
DECL|macro|FRAME_BUFFER_START
mdefine_line|#define FRAME_BUFFER_START 0x0FA0000
DECL|macro|FRAME_BUFFER_LEN
mdefine_line|#define FRAME_BUFFER_LEN 0x40000
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
DECL|macro|NORMAL
mdefine_line|#define NORMAL      0x80 /* 1xxx.xxxx */   /* What is happening here ?? */
DECL|macro|INVERSE
mdefine_line|#define INVERSE     0x00 /* 0xxx.xxxx */   /* Clearing this reverses the screen */
DECL|macro|PIX_BLT
mdefine_line|#define PIX_BLT     0x00 /* 0xxx.xxxx */
DECL|macro|AD_HIBIT
mdefine_line|#define AD_HIBIT        0x40 /* xIxx.xxxx */
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
multiline_comment|/* CREG 2 */
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
macro_line|#if 0
mdefine_line|#define outb(a,d) *(char *)(a)=(d)
mdefine_line|#define outw(a,d) *(unsigned short *)a=d
macro_line|#endif
multiline_comment|/* frame buffer operations */
r_static
r_int
id|dnfb_open
c_func
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
r_static
r_int
id|dnfb_release
c_func
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
r_static
r_int
id|dnfb_get_fix
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
id|dnfb_get_var
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
id|dnfb_set_var
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
id|dnfb_get_cmap
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
id|dnfb_set_cmap
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
id|dnfb_pan_display
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
id|dnfb_ioctl
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
id|dnfb_set_disp
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
DECL|variable|dnfb_ops
r_static
r_struct
id|fb_ops
id|dnfb_ops
op_assign
(brace
id|dnfb_open
comma
id|dnfb_release
comma
id|dnfb_get_fix
comma
id|dnfb_get_var
comma
id|dnfb_set_var
comma
id|dnfb_get_cmap
comma
id|dnfb_set_cmap
comma
id|dnfb_pan_display
comma
id|dnfb_ioctl
)brace
suffix:semicolon
DECL|variable|currcon
r_static
r_int
id|currcon
op_assign
l_int|0
suffix:semicolon
DECL|variable|dnfb_name
r_static
r_char
id|dnfb_name
(braket
)braket
op_assign
l_string|&quot;Apollo&quot;
suffix:semicolon
DECL|function|dnfb_open
r_static
r_int
id|dnfb_open
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|user
)paren
(brace
multiline_comment|/*&n;         * Nothing, only a usage count for the moment&n;         */
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dnfb_release
r_static
r_int
id|dnfb_release
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|user
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dnfb_get_fix
r_static
r_int
id|dnfb_get_fix
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
id|memset
c_func
(paren
id|fix
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|fb_fix_screeninfo
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|fix-&gt;id
comma
l_string|&quot;Apollo Mono&quot;
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
l_int|256
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dnfb_get_var
r_static
r_int
id|dnfb_get_var
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
id|memset
c_func
(paren
id|var
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|fb_var_screeninfo
)paren
)paren
suffix:semicolon
id|var-&gt;xres
op_assign
l_int|1280
suffix:semicolon
id|var-&gt;yres
op_assign
l_int|1024
suffix:semicolon
id|var-&gt;xres_virtual
op_assign
l_int|2048
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
DECL|function|dnfb_set_var
r_static
r_int
id|dnfb_set_var
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
r_if
c_cond
(paren
id|var-&gt;xres
op_ne
l_int|1280
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
id|var-&gt;xres_virtual
op_ne
l_int|2048
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
DECL|function|dnfb_get_cmap
r_static
r_int
id|dnfb_get_cmap
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
DECL|function|dnfb_set_cmap
r_static
r_int
id|dnfb_set_cmap
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
DECL|function|dnfb_pan_display
r_static
r_int
id|dnfb_pan_display
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
DECL|function|dnfb_ioctl
r_static
r_int
id|dnfb_ioctl
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
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|dnfb_set_disp
r_static
r_void
id|dnfb_set_disp
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
id|dnfb_get_fix
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
id|fix.smem_start
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
macro_line|#ifdef FBCON_HAS_MFB
id|disp
(braket
id|con
)braket
dot
id|dispsw
op_assign
op_amp
id|fbcon_mfb
suffix:semicolon
macro_line|#else
id|disp
(braket
id|con
)braket
dot
id|dispsw
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
)brace
DECL|function|dnfb_init
r_void
id|dnfb_init
c_func
(paren
r_void
)paren
(brace
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
id|dnfb_name
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
id|dnfb_ops
suffix:semicolon
id|outb
c_func
(paren
id|RESET_CREG
comma
id|AP_CONTROL_3A
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
id|S_DATA_PLN
comma
id|AP_CONTROL_2
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
id|dnfb_get_var
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
id|dnfb_set_disp
c_func
(paren
op_minus
l_int|1
comma
op_amp
id|fb_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
op_amp
id|fb_info
)paren
OL
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;unable to register apollo frame buffer&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fb%d: apollo frame buffer alive and kicking !&bslash;n&quot;
comma
id|GET_FB_IDX
c_func
(paren
id|fb_info.node
)paren
)paren
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
l_int|0
comma
id|AP_CONTROL_3A
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
op_amp
op_complement
id|ENAB_DISP
comma
id|AP_CONTROL_1
)paren
suffix:semicolon
)brace
r_else
(brace
id|outb
c_func
(paren
l_int|1
comma
id|AP_CONTROL_3A
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
)brace
)brace
eof
