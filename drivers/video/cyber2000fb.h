multiline_comment|/*&n; * linux/drivers/video/cyber2000fb.h&n; *&n; * Integraphics Cyber2000 frame buffer device&n; */
DECL|macro|arraysize
mdefine_line|#define arraysize(x)    (sizeof(x)/sizeof(*(x)))
DECL|macro|cyber2000_outb
mdefine_line|#define cyber2000_outb(dat,reg)&t;writeb(dat, CyberRegs + reg)
DECL|macro|cyber2000_outw
mdefine_line|#define cyber2000_outw(dat,reg)&t;writew(dat, CyberRegs + reg)
DECL|macro|cyber2000_outl
mdefine_line|#define cyber2000_outl(dat,reg)&t;writel(dat, CyberRegs + reg)
DECL|macro|cyber2000_inb
mdefine_line|#define cyber2000_inb(reg)&t;readb(CyberRegs + reg)
DECL|macro|cyber2000_inw
mdefine_line|#define cyber2000_inw(reg)&t;readw(CyberRegs + reg)
DECL|macro|cyber2000_inl
mdefine_line|#define cyber2000_inl(reg)&t;readl(CyberRegs + reg)
DECL|function|cyber2000_crtcw
r_static
r_inline
r_void
id|cyber2000_crtcw
c_func
(paren
r_int
id|reg
comma
r_int
id|val
)paren
(brace
id|cyber2000_outb
c_func
(paren
id|reg
comma
l_int|0x3d4
)paren
suffix:semicolon
id|cyber2000_outb
c_func
(paren
id|val
comma
l_int|0x3d5
)paren
suffix:semicolon
)brace
DECL|function|cyber2000_grphw
r_static
r_inline
r_void
id|cyber2000_grphw
c_func
(paren
r_int
id|reg
comma
r_int
id|val
)paren
(brace
id|cyber2000_outb
c_func
(paren
id|reg
comma
l_int|0x3ce
)paren
suffix:semicolon
id|cyber2000_outb
c_func
(paren
id|val
comma
l_int|0x3cf
)paren
suffix:semicolon
)brace
DECL|function|cyber2000_attrw
r_static
r_inline
r_void
id|cyber2000_attrw
c_func
(paren
r_int
id|reg
comma
r_int
id|val
)paren
(brace
id|cyber2000_inb
c_func
(paren
l_int|0x3da
)paren
suffix:semicolon
id|cyber2000_outb
c_func
(paren
id|reg
comma
l_int|0x3c0
)paren
suffix:semicolon
id|cyber2000_inb
c_func
(paren
l_int|0x3c1
)paren
suffix:semicolon
id|cyber2000_outb
c_func
(paren
id|val
comma
l_int|0x3c0
)paren
suffix:semicolon
)brace
DECL|function|cyber2000_seqw
r_static
r_inline
r_void
id|cyber2000_seqw
c_func
(paren
r_int
id|reg
comma
r_int
id|val
)paren
(brace
id|cyber2000_outb
c_func
(paren
id|reg
comma
l_int|0x3c4
)paren
suffix:semicolon
id|cyber2000_outb
c_func
(paren
id|val
comma
l_int|0x3c5
)paren
suffix:semicolon
)brace
DECL|struct|cyber2000fb_par
r_struct
id|cyber2000fb_par
(brace
DECL|member|screen_base
r_char
op_star
id|screen_base
suffix:semicolon
DECL|member|screen_base_p
r_int
r_int
id|screen_base_p
suffix:semicolon
DECL|member|regs_base
r_int
r_int
id|regs_base
suffix:semicolon
DECL|member|regs_base_p
r_int
r_int
id|regs_base_p
suffix:semicolon
DECL|member|screen_end
r_int
r_int
id|screen_end
suffix:semicolon
DECL|member|screen_size
r_int
r_int
id|screen_size
suffix:semicolon
DECL|member|palette_size
r_int
r_int
id|palette_size
suffix:semicolon
DECL|member|currcon
r_int
r_int
id|currcon
suffix:semicolon
DECL|member|dev_name
r_char
id|dev_name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|initialised
r_int
r_int
id|initialised
suffix:semicolon
multiline_comment|/*&n;&t; * palette&n;&t; */
r_struct
(brace
DECL|member|red
id|u8
id|red
suffix:semicolon
DECL|member|green
id|u8
id|green
suffix:semicolon
DECL|member|blue
id|u8
id|blue
suffix:semicolon
DECL|member|palette
)brace
id|palette
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * colour mapping table&n;&t; */
r_union
(brace
macro_line|#ifdef FBCON_HAS_CFB16
DECL|member|cfb16
id|u16
id|cfb16
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB24
DECL|member|cfb24
id|u32
id|cfb24
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#endif
DECL|member|c_table
)brace
id|c_table
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PIXFORMAT_8BPP
mdefine_line|#define PIXFORMAT_8BPP&t;&t;0
DECL|macro|PIXFORMAT_16BPP
mdefine_line|#define PIXFORMAT_16BPP&t;&t;1
DECL|macro|PIXFORMAT_24BPP
mdefine_line|#define PIXFORMAT_24BPP&t;&t;2
DECL|macro|VISUALID_256
mdefine_line|#define VISUALID_256&t;&t;1
DECL|macro|VISUALID_64K
mdefine_line|#define VISUALID_64K&t;&t;2
DECL|macro|VISUALID_16M
mdefine_line|#define VISUALID_16M&t;&t;4
DECL|macro|VISUALID_32K
mdefine_line|#define VISUALID_32K&t;&t;6
DECL|macro|CO_CMD_L_PATTERN_FGCOL
mdefine_line|#define CO_CMD_L_PATTERN_FGCOL&t;0x8000
DECL|macro|CO_CMD_L_INC_LEFT
mdefine_line|#define CO_CMD_L_INC_LEFT&t;0x0004
DECL|macro|CO_CMD_L_INC_UP
mdefine_line|#define CO_CMD_L_INC_UP&t;&t;0x0002
DECL|macro|CO_CMD_H_SRC_PIXMAP
mdefine_line|#define CO_CMD_H_SRC_PIXMAP&t;0x2000
DECL|macro|CO_CMD_H_BLITTER
mdefine_line|#define CO_CMD_H_BLITTER&t;0x0800
DECL|macro|CO_REG_CONTROL
mdefine_line|#define CO_REG_CONTROL&t;&t;0xbf011
DECL|macro|CO_REG_SRC_WIDTH
mdefine_line|#define CO_REG_SRC_WIDTH&t;0xbf018
DECL|macro|CO_REG_PIX_FORMAT
mdefine_line|#define CO_REG_PIX_FORMAT&t;0xbf01c
DECL|macro|CO_REG_FORE_MIX
mdefine_line|#define CO_REG_FORE_MIX&t;&t;0xbf048
DECL|macro|CO_REG_FOREGROUND
mdefine_line|#define CO_REG_FOREGROUND&t;0xbf058
DECL|macro|CO_REG_WIDTH
mdefine_line|#define CO_REG_WIDTH&t;&t;0xbf060
DECL|macro|CO_REG_HEIGHT
mdefine_line|#define CO_REG_HEIGHT&t;&t;0xbf062
DECL|macro|CO_REG_X_PHASE
mdefine_line|#define CO_REG_X_PHASE&t;&t;0xbf078
DECL|macro|CO_REG_CMD_L
mdefine_line|#define CO_REG_CMD_L&t;&t;0xbf07c
DECL|macro|CO_REG_CMD_H
mdefine_line|#define CO_REG_CMD_H&t;&t;0xbf07e
DECL|macro|CO_REG_SRC_PTR
mdefine_line|#define CO_REG_SRC_PTR&t;&t;0xbf170
DECL|macro|CO_REG_DEST_PTR
mdefine_line|#define CO_REG_DEST_PTR&t;&t;0xbf178
DECL|macro|CO_REG_DEST_WIDTH
mdefine_line|#define CO_REG_DEST_WIDTH&t;0xbf218
eof
