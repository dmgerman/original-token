multiline_comment|/*&n; * control.c: Console support for PowerMac &quot;control&quot; display adaptor.&n; *&n; * Copyright (C) 1996 Paul Mackerras.&n; *&t;&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/vc_ioctl.h&gt;
macro_line|#include &lt;linux/nvram.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/cuda.h&gt;
macro_line|#include &lt;linux/selection.h&gt;
macro_line|#include &quot;pmac-cons.h&quot;
macro_line|#include &quot;control.h&quot;
multiline_comment|/*&n; * Structure of the registers for the RADACAL colormap device.&n; */
DECL|struct|cmap_regs
r_struct
id|cmap_regs
(brace
DECL|member|addr
r_int
r_char
id|addr
suffix:semicolon
DECL|member|pad1
r_char
id|pad1
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|d1
r_int
r_char
id|d1
suffix:semicolon
DECL|member|pad2
r_char
id|pad2
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|d2
r_int
r_char
id|d2
suffix:semicolon
DECL|member|pad3
r_char
id|pad3
(braket
l_int|15
)braket
suffix:semicolon
DECL|member|lut
r_int
r_char
id|lut
suffix:semicolon
DECL|member|pad4
r_char
id|pad4
(braket
l_int|15
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Structure of the registers for the &quot;control&quot; display adaptor&quot;.&n; */
DECL|macro|PAD
mdefine_line|#define PAD(x)&t;char x[12]
DECL|struct|preg
r_struct
id|preg
(brace
multiline_comment|/* padded register */
DECL|member|r
r_int
id|r
suffix:semicolon
DECL|member|pad
r_char
id|pad
(braket
l_int|12
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|control_regs
r_struct
id|control_regs
(brace
DECL|member|vcount
r_struct
id|preg
id|vcount
suffix:semicolon
multiline_comment|/* vertical counter */
multiline_comment|/* Vertical parameters are in units of 1/2 scan line */
DECL|member|vswin
r_struct
id|preg
id|vswin
suffix:semicolon
multiline_comment|/* between vsblank and vssync */
DECL|member|vsblank
r_struct
id|preg
id|vsblank
suffix:semicolon
multiline_comment|/* vert start blank */
DECL|member|veblank
r_struct
id|preg
id|veblank
suffix:semicolon
multiline_comment|/* vert end blank (display start) */
DECL|member|vewin
r_struct
id|preg
id|vewin
suffix:semicolon
multiline_comment|/* between vesync and veblank */
DECL|member|vesync
r_struct
id|preg
id|vesync
suffix:semicolon
multiline_comment|/* vert end sync */
DECL|member|vssync
r_struct
id|preg
id|vssync
suffix:semicolon
multiline_comment|/* vert start sync */
DECL|member|vperiod
r_struct
id|preg
id|vperiod
suffix:semicolon
multiline_comment|/* vert period */
DECL|member|reg8
r_struct
id|preg
id|reg8
suffix:semicolon
multiline_comment|/* Horizontal params are in units of 2 pixels */
DECL|member|hperiod
r_struct
id|preg
id|hperiod
suffix:semicolon
multiline_comment|/* horiz period - 2 */
DECL|member|hsblank
r_struct
id|preg
id|hsblank
suffix:semicolon
multiline_comment|/* horiz start blank */
DECL|member|heblank
r_struct
id|preg
id|heblank
suffix:semicolon
multiline_comment|/* horiz end blank */
DECL|member|hesync
r_struct
id|preg
id|hesync
suffix:semicolon
multiline_comment|/* horiz end sync */
DECL|member|hssync
r_struct
id|preg
id|hssync
suffix:semicolon
multiline_comment|/* horiz start sync */
DECL|member|rege
r_struct
id|preg
id|rege
suffix:semicolon
DECL|member|regf
r_struct
id|preg
id|regf
suffix:semicolon
DECL|member|reg10
r_struct
id|preg
id|reg10
suffix:semicolon
DECL|member|reg11
r_struct
id|preg
id|reg11
suffix:semicolon
DECL|member|ctrl
r_struct
id|preg
id|ctrl
suffix:semicolon
multiline_comment|/* display control */
DECL|member|start_addr
r_struct
id|preg
id|start_addr
suffix:semicolon
multiline_comment|/* start address: 5 lsbs zero */
DECL|member|pitch
r_struct
id|preg
id|pitch
suffix:semicolon
multiline_comment|/* addrs diff between scan lines */
DECL|member|mon_sense
r_struct
id|preg
id|mon_sense
suffix:semicolon
multiline_comment|/* monitor sense bits */
DECL|member|flags
r_struct
id|preg
id|flags
suffix:semicolon
DECL|member|mode
r_struct
id|preg
id|mode
suffix:semicolon
DECL|member|reg18
r_struct
id|preg
id|reg18
suffix:semicolon
DECL|member|reg19
r_struct
id|preg
id|reg19
suffix:semicolon
DECL|member|res
r_struct
id|preg
id|res
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
r_static
r_void
id|set_control_clock
c_func
(paren
r_int
r_char
op_star
id|params
)paren
suffix:semicolon
r_static
r_int
id|read_control_sense
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|control_vram_reqd
c_func
(paren
r_int
id|vmode
comma
r_int
id|cmode
)paren
suffix:semicolon
DECL|variable|total_vram
r_static
r_int
id|total_vram
suffix:semicolon
multiline_comment|/* total amount of video memory, bytes */
DECL|variable|frame_buffer
r_static
r_int
r_char
op_star
id|frame_buffer
suffix:semicolon
DECL|variable|cmap_regs
r_static
r_struct
id|cmap_regs
op_star
id|cmap_regs
suffix:semicolon
DECL|variable|disp_regs
r_static
r_struct
id|control_regs
op_star
id|disp_regs
suffix:semicolon
DECL|variable|control_use_bank2
r_static
r_int
id|control_use_bank2
suffix:semicolon
multiline_comment|/*&n; * Register initialization tables for the control display.&n; *&n; * Dot clock rate is&n; * 3.9064MHz * 2**clock_params[2] * clock_params[1] / clock_params[0].&n; *&n; * The values for vertical frequency (V) in the comments below&n; * are the values measured using the modes under MacOS.&n; */
DECL|struct|control_regvals
r_struct
id|control_regvals
(brace
DECL|member|pitch
r_int
id|pitch
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* bytes/line, indexed by color_mode */
DECL|member|offset
r_int
id|offset
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* first pixel address */
DECL|member|regs
r_int
id|regs
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* for vswin .. reg10 */
DECL|member|mode
r_int
r_char
id|mode
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* indexed by color_mode */
DECL|member|radacal_ctrl
r_int
r_char
id|radacal_ctrl
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|clock_params
r_int
r_char
id|clock_params
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Register values for 1280x1024, 75Hz mode (20) */
DECL|variable|control_reg_init_20
r_static
r_struct
id|control_regvals
id|control_reg_init_20
op_assign
(brace
(brace
l_int|1280
comma
l_int|2560
comma
l_int|0
)brace
comma
(brace
l_int|0x10
comma
l_int|0x20
comma
l_int|0
)brace
comma
(brace
l_int|2129
comma
l_int|2128
comma
l_int|80
comma
l_int|42
comma
l_int|4
comma
l_int|2130
comma
l_int|2132
comma
l_int|88
comma
l_int|420
comma
l_int|411
comma
l_int|91
comma
l_int|35
comma
l_int|421
comma
l_int|18
comma
l_int|211
comma
l_int|386
comma
)brace
comma
(brace
l_int|1
comma
l_int|1
comma
l_int|1
)brace
comma
(brace
l_int|0x50
comma
l_int|0x64
comma
l_int|0x64
)brace
comma
(brace
l_int|13
comma
l_int|56
comma
l_int|3
)brace
multiline_comment|/* pixel clock = 134.61MHz for V=74.81Hz */
)brace
suffix:semicolon
multiline_comment|/* Register values for 1280x960, 75Hz mode (19) */
DECL|variable|control_reg_init_19
r_static
r_struct
id|control_regvals
id|control_reg_init_19
op_assign
(brace
(brace
l_int|1280
comma
l_int|2560
comma
l_int|0
)brace
comma
(brace
l_int|0x10
comma
l_int|0x20
comma
l_int|0
)brace
comma
(brace
l_int|1997
comma
l_int|1996
comma
l_int|76
comma
l_int|40
comma
l_int|4
comma
l_int|1998
comma
l_int|2000
comma
l_int|86
comma
l_int|418
comma
l_int|409
comma
l_int|89
comma
l_int|35
comma
l_int|419
comma
l_int|18
comma
l_int|210
comma
l_int|384
comma
)brace
comma
(brace
l_int|1
comma
l_int|1
comma
l_int|1
)brace
comma
(brace
l_int|0x50
comma
l_int|0x64
comma
l_int|0x64
)brace
comma
(brace
l_int|31
comma
l_int|125
comma
l_int|3
)brace
multiline_comment|/* pixel clock = 126.01MHz for V=75.01 Hz */
)brace
suffix:semicolon
multiline_comment|/* Register values for 1152x870, 75Hz mode (18) */
DECL|variable|control_reg_init_18
r_static
r_struct
id|control_regvals
id|control_reg_init_18
op_assign
(brace
(brace
l_int|1152
comma
l_int|2304
comma
l_int|4608
)brace
comma
(brace
l_int|0x10
comma
l_int|0x28
comma
l_int|0x50
)brace
comma
(brace
l_int|1825
comma
l_int|1822
comma
l_int|82
comma
l_int|43
comma
l_int|4
comma
l_int|1828
comma
l_int|1830
comma
l_int|120
comma
l_int|726
comma
l_int|705
comma
l_int|129
comma
l_int|63
comma
l_int|727
comma
l_int|32
comma
l_int|364
comma
l_int|664
)brace
comma
(brace
l_int|2
comma
l_int|1
comma
l_int|1
)brace
comma
(brace
l_int|0x10
comma
l_int|0x14
comma
l_int|0x28
)brace
comma
(brace
l_int|19
comma
l_int|61
comma
l_int|3
)brace
multiline_comment|/* pixel clock = 100.33MHz for V=75.31Hz */
)brace
suffix:semicolon
multiline_comment|/* Register values for 1024x768, 75Hz mode (17) */
DECL|variable|control_reg_init_17
r_static
r_struct
id|control_regvals
id|control_reg_init_17
op_assign
(brace
(brace
l_int|1024
comma
l_int|2048
comma
l_int|4096
)brace
comma
(brace
l_int|0x10
comma
l_int|0x28
comma
l_int|0x50
)brace
comma
(brace
l_int|1603
comma
l_int|1600
comma
l_int|64
comma
l_int|34
comma
l_int|4
comma
l_int|1606
comma
l_int|1608
comma
l_int|120
comma
l_int|662
comma
l_int|641
comma
l_int|129
comma
l_int|47
comma
l_int|663
comma
l_int|24
comma
l_int|332
comma
l_int|616
)brace
comma
(brace
l_int|2
comma
l_int|1
comma
l_int|1
)brace
comma
(brace
l_int|0x10
comma
l_int|0x14
comma
l_int|0x28
)brace
comma
(brace
l_int|11
comma
l_int|28
comma
l_int|3
)brace
multiline_comment|/* pixel clock = 79.55MHz for V=74.50Hz */
)brace
suffix:semicolon
multiline_comment|/* Register values for 1024x768, 72Hz mode (15) */
DECL|variable|control_reg_init_15
r_static
r_struct
id|control_regvals
id|control_reg_init_15
op_assign
(brace
(brace
l_int|1024
comma
l_int|2048
comma
l_int|4096
)brace
comma
(brace
l_int|0x10
comma
l_int|0x28
comma
l_int|0x50
)brace
comma
(brace
l_int|1607
comma
l_int|1604
comma
l_int|68
comma
l_int|39
comma
l_int|10
comma
l_int|1610
comma
l_int|1612
comma
l_int|132
comma
l_int|670
comma
l_int|653
comma
l_int|141
comma
l_int|67
comma
l_int|671
comma
l_int|34
comma
l_int|336
comma
l_int|604
comma
)brace
comma
(brace
l_int|2
comma
l_int|1
comma
l_int|1
)brace
comma
(brace
l_int|0x10
comma
l_int|0x14
comma
l_int|0x28
)brace
comma
(brace
l_int|12
comma
l_int|30
comma
l_int|3
)brace
multiline_comment|/* pixel clock = 78.12MHz for V=72.12Hz */
)brace
suffix:semicolon
multiline_comment|/* Register values for 1024x768, 60Hz mode (14) */
DECL|variable|control_reg_init_14
r_static
r_struct
id|control_regvals
id|control_reg_init_14
op_assign
(brace
(brace
l_int|1024
comma
l_int|2048
comma
l_int|4096
)brace
comma
(brace
l_int|0x10
comma
l_int|0x28
comma
l_int|0x50
)brace
comma
(brace
l_int|1607
comma
l_int|1604
comma
l_int|68
comma
l_int|39
comma
l_int|10
comma
l_int|1610
comma
l_int|1612
comma
l_int|132
comma
l_int|670
comma
l_int|653
comma
l_int|141
comma
l_int|67
comma
l_int|671
comma
l_int|34
comma
l_int|336
comma
l_int|604
comma
)brace
comma
(brace
l_int|2
comma
l_int|1
comma
l_int|1
)brace
comma
(brace
l_int|0x10
comma
l_int|0x14
comma
l_int|0x28
)brace
comma
(brace
l_int|15
comma
l_int|31
comma
l_int|3
)brace
multiline_comment|/* pixel clock = 64.58MHz for V=59.62Hz */
)brace
suffix:semicolon
multiline_comment|/* Register values for 832x624, 75Hz mode (13) */
DECL|variable|control_reg_init_13
r_static
r_struct
id|control_regvals
id|control_reg_init_13
op_assign
(brace
(brace
l_int|832
comma
l_int|1664
comma
l_int|3328
)brace
comma
(brace
l_int|0x10
comma
l_int|0x28
comma
l_int|0x50
)brace
comma
(brace
l_int|1331
comma
l_int|1330
comma
l_int|82
comma
l_int|43
comma
l_int|4
comma
l_int|1332
comma
l_int|1334
comma
l_int|128
comma
l_int|574
comma
l_int|553
comma
l_int|137
comma
l_int|31
comma
l_int|575
comma
l_int|16
comma
l_int|288
comma
l_int|544
)brace
comma
(brace
l_int|2
comma
l_int|1
comma
l_int|0
)brace
comma
(brace
l_int|0x10
comma
l_int|0x14
comma
l_int|0x18
)brace
comma
(brace
l_int|23
comma
l_int|42
comma
l_int|3
)brace
multiline_comment|/* pixel clock = 57.07MHz for V=74.27Hz */
)brace
suffix:semicolon
multiline_comment|/* Register values for 800x600, 75Hz mode (12) */
DECL|variable|control_reg_init_12
r_static
r_struct
id|control_regvals
id|control_reg_init_12
op_assign
(brace
(brace
l_int|800
comma
l_int|1600
comma
l_int|3200
)brace
comma
(brace
l_int|0x10
comma
l_int|0x28
comma
l_int|0x50
)brace
comma
(brace
l_int|1247
comma
l_int|1246
comma
l_int|46
comma
l_int|25
comma
l_int|4
comma
l_int|1248
comma
l_int|1250
comma
l_int|104
comma
l_int|526
comma
l_int|513
comma
l_int|113
comma
l_int|39
comma
l_int|527
comma
l_int|20
comma
l_int|264
comma
l_int|488
comma
)brace
comma
(brace
l_int|2
comma
l_int|1
comma
l_int|0
)brace
comma
(brace
l_int|0x10
comma
l_int|0x14
comma
l_int|0x18
)brace
comma
(brace
l_int|7
comma
l_int|11
comma
l_int|3
)brace
multiline_comment|/* pixel clock = 49.11MHz for V=74.40Hz */
)brace
suffix:semicolon
multiline_comment|/* Register values for 800x600, 72Hz mode (11) */
DECL|variable|control_reg_init_11
r_static
r_struct
id|control_regvals
id|control_reg_init_11
op_assign
(brace
(brace
l_int|800
comma
l_int|1600
comma
l_int|3200
)brace
comma
(brace
l_int|0x10
comma
l_int|0x28
comma
l_int|0x50
)brace
comma
(brace
l_int|1293
comma
l_int|1256
comma
l_int|56
comma
l_int|33
comma
l_int|10
comma
l_int|1330
comma
l_int|1332
comma
l_int|76
comma
l_int|518
comma
l_int|485
comma
l_int|85
comma
l_int|59
comma
l_int|519
comma
l_int|30
comma
l_int|260
comma
l_int|460
comma
)brace
comma
(brace
l_int|2
comma
l_int|1
comma
l_int|0
)brace
comma
(brace
l_int|0x10
comma
l_int|0x14
comma
l_int|0x18
)brace
comma
(brace
l_int|17
comma
l_int|27
comma
l_int|3
)brace
multiline_comment|/* pixel clock = 49.63MHz for V=71.66Hz */
)brace
suffix:semicolon
multiline_comment|/* Register values for 800x600, 60Hz mode (10) */
DECL|variable|control_reg_init_10
r_static
r_struct
id|control_regvals
id|control_reg_init_10
op_assign
(brace
(brace
l_int|800
comma
l_int|1600
comma
l_int|3200
)brace
comma
(brace
l_int|0x10
comma
l_int|0x28
comma
l_int|0x50
)brace
comma
(brace
l_int|1293
comma
l_int|1256
comma
l_int|56
comma
l_int|33
comma
l_int|10
comma
l_int|1330
comma
l_int|1332
comma
l_int|76
comma
l_int|518
comma
l_int|485
comma
l_int|85
comma
l_int|59
comma
l_int|519
comma
l_int|30
comma
l_int|260
comma
l_int|460
comma
)brace
comma
(brace
l_int|2
comma
l_int|1
comma
l_int|0
)brace
comma
(brace
l_int|0x10
comma
l_int|0x14
comma
l_int|0x18
)brace
comma
(brace
l_int|20
comma
l_int|53
comma
l_int|2
)brace
multiline_comment|/* pixel clock = 41.41MHz for V=59.78Hz */
)brace
suffix:semicolon
multiline_comment|/* Register values for 640x870, 75Hz Full Page Display (7) */
DECL|variable|control_reg_init_7
r_static
r_struct
id|control_regvals
id|control_reg_init_7
op_assign
(brace
(brace
l_int|640
comma
l_int|1280
comma
l_int|2560
)brace
comma
(brace
l_int|0x10
comma
l_int|0x30
comma
l_int|0x68
)brace
comma
(brace
l_int|0x727
comma
l_int|0x724
comma
l_int|0x58
comma
l_int|0x2e
comma
l_int|0x4
comma
l_int|0x72a
comma
l_int|0x72c
comma
l_int|0x40
comma
l_int|0x19e
comma
l_int|0x18c
comma
l_int|0x4c
comma
l_int|0x27
comma
l_int|0x19f
comma
l_int|0x14
comma
l_int|0xd0
comma
l_int|0x178
)brace
comma
(brace
l_int|2
comma
l_int|1
comma
l_int|0
)brace
comma
(brace
l_int|0x10
comma
l_int|0x14
comma
l_int|0x18
)brace
comma
(brace
l_int|9
comma
l_int|33
comma
l_int|2
)brace
multiline_comment|/* pixel clock = 57.29MHz for V=75.01Hz */
)brace
suffix:semicolon
multiline_comment|/* Register values for 640x480, 67Hz mode (6) */
DECL|variable|control_reg_init_6
r_static
r_struct
id|control_regvals
id|control_reg_init_6
op_assign
(brace
(brace
l_int|640
comma
l_int|1280
comma
l_int|2560
)brace
comma
(brace
l_int|0
comma
l_int|8
comma
l_int|0x10
)brace
comma
(brace
l_int|1045
comma
l_int|1042
comma
l_int|82
comma
l_int|43
comma
l_int|4
comma
l_int|1048
comma
l_int|1050
comma
l_int|72
comma
l_int|430
comma
l_int|393
comma
l_int|73
comma
l_int|31
comma
l_int|431
comma
l_int|16
comma
l_int|216
comma
l_int|400
)brace
comma
(brace
l_int|2
comma
l_int|1
comma
l_int|0
)brace
comma
(brace
l_int|0x10
comma
l_int|0x14
comma
l_int|0x18
)brace
comma
(brace
l_int|14
comma
l_int|27
comma
l_int|2
)brace
multiline_comment|/* pixel clock = 30.13MHz for V=66.43Hz */
)brace
suffix:semicolon
multiline_comment|/* Register values for 640x480, 60Hz mode (5) */
DECL|variable|control_reg_init_5
r_static
r_struct
id|control_regvals
id|control_reg_init_5
op_assign
(brace
(brace
l_int|640
comma
l_int|1280
comma
l_int|2560
)brace
comma
(brace
l_int|0x10
comma
l_int|0x28
comma
l_int|0x50
)brace
comma
(brace
l_int|1037
comma
l_int|1026
comma
l_int|66
comma
l_int|34
comma
l_int|2
comma
l_int|1048
comma
l_int|1050
comma
l_int|56
comma
l_int|398
comma
l_int|385
comma
l_int|65
comma
l_int|47
comma
l_int|399
comma
l_int|24
comma
l_int|200
comma
l_int|352
comma
)brace
comma
(brace
l_int|2
comma
l_int|1
comma
l_int|0
)brace
comma
(brace
l_int|0x10
comma
l_int|0x14
comma
l_int|0x18
)brace
comma
(brace
l_int|23
comma
l_int|37
comma
l_int|2
)brace
multiline_comment|/* pixel clock = 25.14MHz for V=59.85Hz */
)brace
suffix:semicolon
DECL|variable|control_reg_init
r_static
r_struct
id|control_regvals
op_star
id|control_reg_init
(braket
l_int|20
)braket
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|control_reg_init_5
comma
op_amp
id|control_reg_init_6
comma
op_amp
id|control_reg_init_7
comma
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|control_reg_init_10
comma
op_amp
id|control_reg_init_11
comma
op_amp
id|control_reg_init_12
comma
op_amp
id|control_reg_init_13
comma
op_amp
id|control_reg_init_14
comma
op_amp
id|control_reg_init_15
comma
l_int|NULL
comma
op_amp
id|control_reg_init_17
comma
op_amp
id|control_reg_init_18
comma
op_amp
id|control_reg_init_19
comma
op_amp
id|control_reg_init_20
)brace
suffix:semicolon
multiline_comment|/*&n; * Get the monitor sense value.&n; * Note that this can be called before calibrate_delay,&n; * so we can&squot;t use udelay.&n; */
r_static
r_int
DECL|function|read_control_sense
id|read_control_sense
c_func
(paren
)paren
(brace
r_int
id|sense
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|disp_regs-&gt;mon_sense.r
comma
l_int|7
)paren
suffix:semicolon
multiline_comment|/* drive all lines high */
id|__delay
c_func
(paren
l_int|200
)paren
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|disp_regs-&gt;mon_sense.r
comma
l_int|077
)paren
suffix:semicolon
multiline_comment|/* turn off drivers */
id|__delay
c_func
(paren
l_int|2000
)paren
suffix:semicolon
id|sense
op_assign
(paren
id|in_le32
c_func
(paren
op_amp
id|disp_regs-&gt;mon_sense.r
)paren
op_amp
l_int|0x1c0
)paren
op_lshift
l_int|2
suffix:semicolon
multiline_comment|/* drive each sense line low in turn and collect the other 2 */
id|out_le32
c_func
(paren
op_amp
id|disp_regs-&gt;mon_sense.r
comma
l_int|033
)paren
suffix:semicolon
multiline_comment|/* drive A low */
id|__delay
c_func
(paren
l_int|2000
)paren
suffix:semicolon
id|sense
op_or_assign
(paren
id|in_le32
c_func
(paren
op_amp
id|disp_regs-&gt;mon_sense.r
)paren
op_amp
l_int|0xc0
)paren
op_rshift
l_int|2
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|disp_regs-&gt;mon_sense.r
comma
l_int|055
)paren
suffix:semicolon
multiline_comment|/* drive B low */
id|__delay
c_func
(paren
l_int|2000
)paren
suffix:semicolon
id|sense
op_or_assign
(paren
(paren
id|in_le32
c_func
(paren
op_amp
id|disp_regs-&gt;mon_sense.r
)paren
op_amp
l_int|0x100
)paren
op_rshift
l_int|5
)paren
op_or
(paren
(paren
id|in_le32
c_func
(paren
op_amp
id|disp_regs-&gt;mon_sense.r
)paren
op_amp
l_int|0x40
)paren
op_rshift
l_int|4
)paren
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|disp_regs-&gt;mon_sense.r
comma
l_int|066
)paren
suffix:semicolon
multiline_comment|/* drive C low */
id|__delay
c_func
(paren
l_int|2000
)paren
suffix:semicolon
id|sense
op_or_assign
(paren
id|in_le32
c_func
(paren
op_amp
id|disp_regs-&gt;mon_sense.r
)paren
op_amp
l_int|0x180
)paren
op_rshift
l_int|7
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|disp_regs-&gt;mon_sense.r
comma
l_int|077
)paren
suffix:semicolon
multiline_comment|/* turn off drivers */
r_return
id|sense
suffix:semicolon
)brace
DECL|function|control_vram_reqd
r_static
r_inline
r_int
id|control_vram_reqd
c_func
(paren
r_int
id|vmode
comma
r_int
id|cmode
)paren
(brace
r_return
id|vmode_attrs
(braket
id|vmode
op_minus
l_int|1
)braket
dot
id|vres
op_star
id|control_reg_init
(braket
id|vmode
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|pitch
(braket
id|cmode
)braket
suffix:semicolon
)brace
r_void
DECL|function|map_control_display
id|map_control_display
c_func
(paren
r_struct
id|device_node
op_star
id|dp
)paren
(brace
r_int
id|i
comma
id|sense
suffix:semicolon
r_int
r_int
id|addr
comma
id|size
suffix:semicolon
r_int
id|bank1
comma
id|bank2
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;next
op_ne
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;Warning: only using first control display device&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dp-&gt;n_addrs
op_ne
l_int|2
)paren
id|panic
c_func
(paren
l_string|&quot;expecting 2 addresses for control (got %d)&quot;
comma
id|dp-&gt;n_addrs
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;pmac_display_init: node = %p, addrs =&quot;
comma
id|dp-&gt;node
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dp-&gt;n_addrs
suffix:semicolon
op_increment
id|i
)paren
id|printk
c_func
(paren
l_string|&quot; %x(%x)&quot;
comma
id|dp-&gt;addrs
(braket
id|i
)braket
dot
id|address
comma
id|dp-&gt;addrs
(braket
id|i
)braket
dot
id|size
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;, intrs =&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dp-&gt;n_intrs
suffix:semicolon
op_increment
id|i
)paren
id|printk
c_func
(paren
l_string|&quot; %x&quot;
comma
id|dp-&gt;intrs
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Map in frame buffer and registers */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dp-&gt;n_addrs
suffix:semicolon
op_increment
id|i
)paren
(brace
id|addr
op_assign
id|dp-&gt;addrs
(braket
id|i
)braket
dot
id|address
suffix:semicolon
id|size
op_assign
id|dp-&gt;addrs
(braket
id|i
)braket
dot
id|size
suffix:semicolon
r_if
c_cond
(paren
id|size
op_ge
l_int|0x800000
)paren
(brace
multiline_comment|/* use the big-endian aperture (??) */
id|addr
op_add_assign
l_int|0x800000
suffix:semicolon
multiline_comment|/* map at most 8MB for the frame buffer */
id|frame_buffer
op_assign
id|ioremap
c_func
(paren
id|addr
comma
l_int|0x800000
)paren
suffix:semicolon
)brace
r_else
(brace
id|disp_regs
op_assign
id|ioremap
c_func
(paren
id|addr
comma
id|size
)paren
suffix:semicolon
)brace
)brace
id|cmap_regs
op_assign
id|ioremap
c_func
(paren
l_int|0xf301b000
comma
l_int|0x1000
)paren
suffix:semicolon
multiline_comment|/* XXX not in prom? */
multiline_comment|/* Work out which banks of VRAM we have installed. */
id|frame_buffer
(braket
l_int|0
)braket
op_assign
l_int|0x5a
suffix:semicolon
id|frame_buffer
(braket
l_int|1
)braket
op_assign
l_int|0xc7
suffix:semicolon
id|bank1
op_assign
id|frame_buffer
(braket
l_int|0
)braket
op_eq
l_int|0x5a
op_logical_and
id|frame_buffer
(braket
l_int|1
)braket
op_eq
l_int|0xc7
suffix:semicolon
id|frame_buffer
(braket
l_int|0x600000
)braket
op_assign
l_int|0xa5
suffix:semicolon
id|frame_buffer
(braket
l_int|0x600001
)braket
op_assign
l_int|0x38
suffix:semicolon
id|bank2
op_assign
id|frame_buffer
(braket
l_int|0x600000
)braket
op_eq
l_int|0xa5
op_logical_and
id|frame_buffer
(braket
l_int|0x600001
)braket
op_eq
l_int|0x38
suffix:semicolon
id|total_vram
op_assign
(paren
id|bank1
op_plus
id|bank2
)paren
op_star
l_int|0x200000
suffix:semicolon
multiline_comment|/* If we don&squot;t have bank 1 installed, we hope we have bank 2 :-) */
id|control_use_bank2
op_assign
op_logical_neg
id|bank1
suffix:semicolon
r_if
c_cond
(paren
id|control_use_bank2
)paren
id|frame_buffer
op_add_assign
l_int|0x600000
suffix:semicolon
id|sense
op_assign
id|read_control_sense
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|video_mode
op_eq
id|VMODE_NVRAM
)paren
(brace
id|video_mode
op_assign
id|nvram_read_byte
c_func
(paren
id|NV_VMODE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|video_mode
op_le
l_int|0
op_logical_or
id|video_mode
OG
id|VMODE_MAX
op_logical_or
id|control_reg_init
(braket
id|video_mode
op_minus
l_int|1
)braket
op_eq
l_int|0
)paren
id|video_mode
op_assign
id|VMODE_CHOOSE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|video_mode
op_eq
id|VMODE_CHOOSE
)paren
id|video_mode
op_assign
id|map_monitor_sense
c_func
(paren
id|sense
)paren
suffix:semicolon
r_if
c_cond
(paren
id|control_reg_init
(braket
id|video_mode
op_minus
l_int|1
)braket
op_eq
l_int|0
)paren
id|video_mode
op_assign
id|VMODE_640_480_60
suffix:semicolon
multiline_comment|/*&n;&t; * Reduce the pixel size if we don&squot;t have enough VRAM.&n;&t; */
r_if
c_cond
(paren
id|color_mode
op_eq
id|CMODE_NVRAM
)paren
id|color_mode
op_assign
id|nvram_read_byte
c_func
(paren
id|NV_CMODE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|color_mode
template_param
id|CMODE_32
)paren
id|color_mode
op_assign
id|CMODE_8
suffix:semicolon
r_while
c_loop
(paren
id|color_mode
OG
id|CMODE_8
op_logical_and
id|control_vram_reqd
c_func
(paren
id|video_mode
comma
id|color_mode
)paren
OG
id|total_vram
)paren
op_decrement
id|color_mode
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Monitor sense value = 0x%x, &quot;
comma
id|sense
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|set_control_clock
id|set_control_clock
c_func
(paren
r_int
r_char
op_star
id|params
)paren
(brace
r_struct
id|cuda_request
id|req
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
op_increment
id|i
)paren
(brace
id|cuda_request
c_func
(paren
op_amp
id|req
comma
l_int|NULL
comma
l_int|5
comma
id|CUDA_PACKET
comma
id|CUDA_GET_SET_IIC
comma
l_int|0x50
comma
id|i
op_plus
l_int|1
comma
id|params
(braket
id|i
)braket
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|req.got_reply
)paren
id|cuda_poll
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|control_init
id|control_init
c_func
(paren
)paren
(brace
r_struct
id|preg
op_star
id|rp
suffix:semicolon
r_int
id|i
comma
id|yoff
comma
id|hres
suffix:semicolon
r_int
id|ctrl
comma
id|flags
suffix:semicolon
r_int
op_star
id|p
suffix:semicolon
r_struct
id|control_regvals
op_star
id|init
suffix:semicolon
r_if
c_cond
(paren
id|video_mode
op_le
l_int|0
op_logical_or
id|video_mode
OG
id|VMODE_MAX
op_logical_or
(paren
id|init
op_assign
id|control_reg_init
(braket
id|video_mode
op_minus
l_int|1
)braket
)paren
op_eq
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;control: display mode %d not supported&quot;
comma
id|video_mode
)paren
suffix:semicolon
id|n_scanlines
op_assign
id|vmode_attrs
(braket
id|video_mode
op_minus
l_int|1
)braket
dot
id|vres
suffix:semicolon
id|hres
op_assign
id|vmode_attrs
(braket
id|video_mode
op_minus
l_int|1
)braket
dot
id|hres
suffix:semicolon
id|pixel_size
op_assign
l_int|1
op_lshift
id|color_mode
suffix:semicolon
id|line_pitch
op_assign
id|init-&gt;pitch
(braket
id|color_mode
)braket
suffix:semicolon
id|row_pitch
op_assign
id|line_pitch
op_star
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|control_vram_reqd
c_func
(paren
id|video_mode
comma
id|color_mode
)paren
OG
l_int|0x200000
)paren
id|flags
op_assign
l_int|0x51
suffix:semicolon
r_else
r_if
c_cond
(paren
id|control_use_bank2
)paren
id|flags
op_assign
l_int|0x39
suffix:semicolon
r_else
id|flags
op_assign
l_int|0x31
suffix:semicolon
r_if
c_cond
(paren
id|video_mode
op_ge
id|VMODE_1280_960_75
op_logical_and
id|color_mode
op_ge
id|CMODE_16
)paren
id|ctrl
op_assign
l_int|0x7f
suffix:semicolon
r_else
id|ctrl
op_assign
l_int|0x3b
suffix:semicolon
multiline_comment|/* Initialize display timing registers */
id|out_le32
c_func
(paren
op_amp
id|disp_regs-&gt;ctrl.r
comma
l_int|0x43b
)paren
suffix:semicolon
id|set_control_clock
c_func
(paren
id|init-&gt;clock_params
)paren
suffix:semicolon
id|cmap_regs-&gt;addr
op_assign
l_int|0x20
suffix:semicolon
id|cmap_regs-&gt;d2
op_assign
id|init-&gt;radacal_ctrl
(braket
id|color_mode
)braket
suffix:semicolon
id|cmap_regs-&gt;addr
op_assign
l_int|0x21
suffix:semicolon
id|cmap_regs-&gt;d2
op_assign
id|control_use_bank2
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
id|cmap_regs-&gt;addr
op_assign
l_int|0x10
suffix:semicolon
id|cmap_regs-&gt;d2
op_assign
l_int|0
suffix:semicolon
id|cmap_regs-&gt;addr
op_assign
l_int|0x11
suffix:semicolon
id|cmap_regs-&gt;d2
op_assign
l_int|0
suffix:semicolon
id|rp
op_assign
op_amp
id|disp_regs-&gt;vswin
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
op_increment
id|i
comma
op_increment
id|rp
)paren
id|out_le32
c_func
(paren
op_amp
id|rp-&gt;r
comma
id|init-&gt;regs
(braket
id|i
)braket
)paren
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|disp_regs-&gt;pitch.r
comma
id|line_pitch
)paren
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|disp_regs-&gt;mode.r
comma
id|init-&gt;mode
(braket
id|color_mode
)braket
)paren
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|disp_regs-&gt;flags.r
comma
id|flags
)paren
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|disp_regs-&gt;start_addr.r
comma
l_int|0
)paren
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|disp_regs-&gt;reg18.r
comma
l_int|0x1e5
)paren
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|disp_regs-&gt;reg19.r
comma
l_int|0
)paren
suffix:semicolon
id|pmac_init_palette
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Initialize colormap */
multiline_comment|/* Turn on display */
id|out_le32
c_func
(paren
op_amp
id|disp_regs-&gt;ctrl.r
comma
id|ctrl
)paren
suffix:semicolon
id|yoff
op_assign
(paren
id|n_scanlines
op_mod
l_int|16
)paren
op_div
l_int|2
suffix:semicolon
id|fb_start
op_assign
id|frame_buffer
op_plus
id|yoff
op_star
id|line_pitch
op_plus
id|init-&gt;offset
(braket
id|color_mode
)braket
suffix:semicolon
multiline_comment|/* Clear screen */
id|p
op_assign
(paren
r_int
op_star
)paren
(paren
id|frame_buffer
op_plus
id|init-&gt;offset
(braket
id|color_mode
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|n_scanlines
op_star
id|line_pitch
op_div
r_sizeof
(paren
r_int
)paren
suffix:semicolon
id|i
op_ne
l_int|0
suffix:semicolon
op_decrement
id|i
)paren
op_star
id|p
op_increment
op_assign
l_int|0
suffix:semicolon
id|display_info.height
op_assign
id|n_scanlines
suffix:semicolon
id|display_info.width
op_assign
id|hres
suffix:semicolon
id|display_info.depth
op_assign
id|pixel_size
op_star
l_int|8
suffix:semicolon
id|display_info.pitch
op_assign
id|line_pitch
suffix:semicolon
id|display_info.mode
op_assign
id|video_mode
suffix:semicolon
id|strncpy
c_func
(paren
id|display_info.name
comma
l_string|&quot;control&quot;
comma
r_sizeof
(paren
id|display_info.name
)paren
)paren
suffix:semicolon
id|display_info.fb_address
op_assign
(paren
r_int
r_int
)paren
id|frame_buffer
op_plus
id|init-&gt;offset
(braket
id|color_mode
)braket
suffix:semicolon
id|display_info.cmap_adr_address
op_assign
(paren
r_int
r_int
)paren
op_amp
id|cmap_regs-&gt;addr
suffix:semicolon
id|display_info.cmap_data_address
op_assign
(paren
r_int
r_int
)paren
op_amp
id|cmap_regs-&gt;lut
suffix:semicolon
id|display_info.disp_reg_address
op_assign
(paren
r_int
r_int
)paren
op_amp
id|disp_regs
suffix:semicolon
)brace
r_int
DECL|function|control_setmode
id|control_setmode
c_func
(paren
r_struct
id|vc_mode
op_star
id|mode
comma
r_int
id|doit
)paren
(brace
r_int
id|cmode
suffix:semicolon
r_if
c_cond
(paren
id|mode-&gt;mode
op_le
l_int|0
op_logical_or
id|mode-&gt;mode
OG
id|VMODE_MAX
op_logical_or
id|control_reg_init
(braket
id|mode-&gt;mode
op_minus
l_int|1
)braket
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|mode-&gt;depth
)paren
(brace
r_case
l_int|24
suffix:colon
r_case
l_int|32
suffix:colon
id|cmode
op_assign
id|CMODE_32
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|cmode
op_assign
id|CMODE_16
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
r_case
l_int|0
suffix:colon
multiline_comment|/* (default) */
id|cmode
op_assign
id|CMODE_8
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|control_vram_reqd
c_func
(paren
id|mode-&gt;mode
comma
id|cmode
)paren
OG
id|total_vram
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|doit
)paren
(brace
id|video_mode
op_assign
id|mode-&gt;mode
suffix:semicolon
id|color_mode
op_assign
id|cmode
suffix:semicolon
id|control_init
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|control_set_palette
id|control_set_palette
c_func
(paren
r_int
r_char
id|red
(braket
)braket
comma
r_int
r_char
id|green
(braket
)braket
comma
r_int
r_char
id|blue
(braket
)braket
comma
r_int
id|index
comma
r_int
id|ncolors
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ncolors
suffix:semicolon
op_increment
id|i
)paren
(brace
id|cmap_regs-&gt;addr
op_assign
id|index
op_plus
id|i
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|cmap_regs-&gt;lut
op_assign
id|red
(braket
id|i
)braket
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|cmap_regs-&gt;lut
op_assign
id|green
(braket
id|i
)braket
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|cmap_regs-&gt;lut
op_assign
id|blue
(braket
id|i
)braket
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|control_set_blanking
id|control_set_blanking
c_func
(paren
r_int
id|blank_mode
)paren
(brace
r_int
id|ctrl
suffix:semicolon
id|ctrl
op_assign
id|ld_le32
c_func
(paren
op_amp
id|disp_regs-&gt;ctrl.r
)paren
op_or
l_int|0x33
suffix:semicolon
r_if
c_cond
(paren
id|blank_mode
op_amp
id|VESA_VSYNC_SUSPEND
)paren
id|ctrl
op_and_assign
op_complement
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|blank_mode
op_amp
id|VESA_HSYNC_SUSPEND
)paren
id|ctrl
op_and_assign
op_complement
l_int|0x30
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|disp_regs-&gt;ctrl.r
comma
id|ctrl
)paren
suffix:semicolon
)brace
eof
