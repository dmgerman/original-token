multiline_comment|/*&n; *  linux/drivers/video/macmodes.c -- Standard MacOS video modes&n; *&n; *&t;Copyright (C) 1998 Geert Uytterhoeven&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &quot;macmodes.h&quot;
DECL|struct|mac_mode
r_struct
id|mac_mode
(brace
DECL|member|number
r_int
id|number
suffix:semicolon
DECL|member|xres
id|u32
id|xres
suffix:semicolon
DECL|member|yres
id|u32
id|yres
suffix:semicolon
DECL|member|pixclock
id|u32
id|pixclock
suffix:semicolon
DECL|member|left_margin
id|u32
id|left_margin
suffix:semicolon
DECL|member|right_margin
id|u32
id|right_margin
suffix:semicolon
DECL|member|upper_margin
id|u32
id|upper_margin
suffix:semicolon
DECL|member|lower_margin
id|u32
id|lower_margin
suffix:semicolon
DECL|member|hsync_len
id|u32
id|hsync_len
suffix:semicolon
DECL|member|vsync_len
id|u32
id|vsync_len
suffix:semicolon
DECL|member|sync
id|u32
id|sync
suffix:semicolon
DECL|member|vmode
id|u32
id|vmode
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* 512x384, 60Hz, Interlaced (NTSC) */
macro_line|#if 0
r_static
r_const
r_struct
id|mac_mode
id|mac_mode_1
op_assign
(brace
id|VMODE_512_384_60I
comma
l_int|512
comma
l_int|384
comma
id|pixclock
comma
id|left
comma
id|right
comma
id|upper
comma
id|lower
comma
id|hslen
comma
id|vslen
comma
id|sync
comma
id|FB_VMODE_INTERLACED
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* 512x384, 60Hz, Non-Interlaced */
macro_line|#if 0
r_static
r_const
r_struct
id|mac_mode
id|mac_mode_2
op_assign
(brace
id|VMODE_512_384_60
comma
l_int|512
comma
l_int|384
comma
id|pixclock
comma
id|left
comma
id|right
comma
id|upper
comma
id|lower
comma
id|hslen
comma
id|vslen
comma
id|sync
comma
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* 640x480, 50Hz, Interlaced (PAL) */
macro_line|#if 0
r_static
r_const
r_struct
id|mac_mode
id|mac_mode_3
op_assign
(brace
id|VMODE_640_480_50I
comma
l_int|640
comma
l_int|480
comma
id|pixclock
comma
id|left
comma
id|right
comma
id|upper
comma
id|lower
comma
id|hslen
comma
id|vslen
comma
id|sync
comma
id|FB_VMODE_INTERLACED
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* 640x480, 60Hz, Interlaced (NTSC) */
macro_line|#if 0
r_static
r_const
r_struct
id|mac_mode
id|mac_mode_4
op_assign
(brace
id|VMODE_640_480_60I
comma
l_int|640
comma
l_int|480
comma
id|pixclock
comma
id|left
comma
id|right
comma
id|upper
comma
id|lower
comma
id|hslen
comma
id|vslen
comma
id|sync
comma
id|FB_VMODE_INTERLACED
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* 640x480, 60 Hz, Non-Interlaced (25.175 MHz dotclock) */
DECL|variable|mac_mode_5
r_static
r_const
r_struct
id|mac_mode
id|mac_mode_5
op_assign
(brace
id|VMODE_640_480_60
comma
l_int|640
comma
l_int|480
comma
l_int|39722
comma
l_int|32
comma
l_int|32
comma
l_int|33
comma
l_int|10
comma
l_int|96
comma
l_int|2
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
multiline_comment|/* 640x480, 67Hz, Non-Interlaced (30.0 MHz dotclock) */
DECL|variable|mac_mode_6
r_static
r_const
r_struct
id|mac_mode
id|mac_mode_6
op_assign
(brace
id|VMODE_640_480_67
comma
l_int|640
comma
l_int|480
comma
l_int|33334
comma
l_int|80
comma
l_int|80
comma
l_int|39
comma
l_int|3
comma
l_int|64
comma
l_int|3
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
multiline_comment|/* 640x870, 75Hz (portrait), Non-Interlaced */
macro_line|#if 0
r_static
r_const
r_struct
id|mac_mode
id|mac_mode_7
op_assign
(brace
id|VMODE_640_870_75P
comma
l_int|640
comma
l_int|870
comma
id|pixclock
comma
id|left
comma
id|right
comma
id|upper
comma
id|lower
comma
id|hslen
comma
id|vslen
comma
id|sync
comma
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* 768x576, 50Hz (PAL full frame), Interlaced */
macro_line|#if 0
r_static
r_const
r_struct
id|mac_mode
id|mac_mode_8
op_assign
(brace
id|VMODE_768_576_50I
comma
l_int|768
comma
l_int|576
comma
id|pixclock
comma
id|left
comma
id|right
comma
id|upper
comma
id|lower
comma
id|hslen
comma
id|vslen
comma
id|sync
comma
id|FB_VMODE_INTERLACED
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* 800x600, 56 Hz, Non-Interlaced (36.00 MHz dotclock) */
DECL|variable|mac_mode_9
r_static
r_const
r_struct
id|mac_mode
id|mac_mode_9
op_assign
(brace
id|VMODE_800_600_56
comma
l_int|800
comma
l_int|600
comma
l_int|27778
comma
l_int|112
comma
l_int|40
comma
l_int|22
comma
l_int|1
comma
l_int|72
comma
l_int|2
comma
id|FB_SYNC_HOR_HIGH_ACT
op_or
id|FB_SYNC_VERT_HIGH_ACT
comma
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
multiline_comment|/* 800x600, 60 Hz, Non-Interlaced (40.00 MHz dotclock) */
DECL|variable|mac_mode_10
r_static
r_const
r_struct
id|mac_mode
id|mac_mode_10
op_assign
(brace
id|VMODE_800_600_60
comma
l_int|800
comma
l_int|600
comma
l_int|25000
comma
l_int|72
comma
l_int|56
comma
l_int|23
comma
l_int|1
comma
l_int|128
comma
l_int|4
comma
id|FB_SYNC_HOR_HIGH_ACT
op_or
id|FB_SYNC_VERT_HIGH_ACT
comma
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
multiline_comment|/* 800x600, 72 Hz, Non-Interlaced (50.00 MHz dotclock) */
DECL|variable|mac_mode_11
r_static
r_const
r_struct
id|mac_mode
id|mac_mode_11
op_assign
(brace
id|VMODE_800_600_72
comma
l_int|800
comma
l_int|600
comma
l_int|20000
comma
l_int|48
comma
l_int|72
comma
l_int|23
comma
l_int|37
comma
l_int|120
comma
l_int|6
comma
id|FB_SYNC_HOR_HIGH_ACT
op_or
id|FB_SYNC_VERT_HIGH_ACT
comma
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
multiline_comment|/* 800x600, 75 Hz, Non-Interlaced (49.50 MHz dotclock) */
DECL|variable|mac_mode_12
r_static
r_const
r_struct
id|mac_mode
id|mac_mode_12
op_assign
(brace
id|VMODE_800_600_75
comma
l_int|800
comma
l_int|600
comma
l_int|20203
comma
l_int|144
comma
l_int|32
comma
l_int|21
comma
l_int|1
comma
l_int|80
comma
l_int|3
comma
id|FB_SYNC_HOR_HIGH_ACT
op_or
id|FB_SYNC_VERT_HIGH_ACT
comma
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
multiline_comment|/* 832x624, 75Hz, Non-Interlaced (57.6 MHz */
DECL|variable|mac_mode_13
r_static
r_const
r_struct
id|mac_mode
id|mac_mode_13
op_assign
(brace
id|VMODE_832_624_75
comma
l_int|832
comma
l_int|624
comma
l_int|17362
comma
l_int|208
comma
l_int|48
comma
l_int|39
comma
l_int|1
comma
l_int|64
comma
l_int|3
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
multiline_comment|/* 1024x768, 60 Hz, Non-Interlaced (65.00 MHz dotclock) */
DECL|variable|mac_mode_14
r_static
r_const
r_struct
id|mac_mode
id|mac_mode_14
op_assign
(brace
id|VMODE_1024_768_60
comma
l_int|1024
comma
l_int|768
comma
l_int|15385
comma
l_int|144
comma
l_int|40
comma
l_int|29
comma
l_int|3
comma
l_int|136
comma
l_int|6
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
multiline_comment|/* 1024x768, 72 Hz, Non-Interlaced (75.00 MHz dotclock) */
DECL|variable|mac_mode_15
r_static
r_const
r_struct
id|mac_mode
id|mac_mode_15
op_assign
(brace
id|VMODE_1024_768_70
comma
l_int|1024
comma
l_int|768
comma
l_int|13334
comma
l_int|128
comma
l_int|40
comma
l_int|29
comma
l_int|3
comma
l_int|136
comma
l_int|6
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
multiline_comment|/* 1024x768, 75 Hz, Non-Interlaced (78.75 MHz dotclock) */
DECL|variable|mac_mode_16
r_static
r_const
r_struct
id|mac_mode
id|mac_mode_16
op_assign
(brace
id|VMODE_1024_768_75V
comma
l_int|1024
comma
l_int|768
comma
l_int|12699
comma
l_int|176
comma
l_int|16
comma
l_int|28
comma
l_int|1
comma
l_int|96
comma
l_int|3
comma
id|FB_SYNC_HOR_HIGH_ACT
op_or
id|FB_SYNC_VERT_HIGH_ACT
comma
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
multiline_comment|/* 1024x768, 75 Hz, Non-Interlaced (78.75 MHz dotclock) */
DECL|variable|mac_mode_17
r_static
r_const
r_struct
id|mac_mode
id|mac_mode_17
op_assign
(brace
id|VMODE_1024_768_75
comma
l_int|1024
comma
l_int|768
comma
l_int|12699
comma
l_int|160
comma
l_int|32
comma
l_int|28
comma
l_int|1
comma
l_int|96
comma
l_int|3
comma
id|FB_SYNC_HOR_HIGH_ACT
op_or
id|FB_SYNC_VERT_HIGH_ACT
comma
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
multiline_comment|/* 1152x870, 75 Hz, Non-Interlaced (100.0 MHz dotclock) */
DECL|variable|mac_mode_18
r_static
r_const
r_struct
id|mac_mode
id|mac_mode_18
op_assign
(brace
id|VMODE_1152_870_75
comma
l_int|1152
comma
l_int|870
comma
l_int|10000
comma
l_int|128
comma
l_int|48
comma
l_int|39
comma
l_int|3
comma
l_int|128
comma
l_int|3
comma
id|FB_SYNC_HOR_HIGH_ACT
op_or
id|FB_SYNC_VERT_HIGH_ACT
comma
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
multiline_comment|/* 1280x960, 75 Hz, Non-Interlaced (126.00 MHz dotclock) */
DECL|variable|mac_mode_19
r_static
r_const
r_struct
id|mac_mode
id|mac_mode_19
op_assign
(brace
id|VMODE_1280_960_75
comma
l_int|1280
comma
l_int|960
comma
l_int|7937
comma
l_int|224
comma
l_int|32
comma
l_int|36
comma
l_int|1
comma
l_int|144
comma
l_int|3
comma
l_int|0
comma
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
multiline_comment|/* 1280x1024, 75 Hz, Non-Interlaced (135.00 MHz dotclock) */
DECL|variable|mac_mode_20
r_static
r_const
r_struct
id|mac_mode
id|mac_mode_20
op_assign
(brace
id|VMODE_1280_1024_75
comma
l_int|1280
comma
l_int|1024
comma
l_int|7408
comma
l_int|232
comma
l_int|64
comma
l_int|38
comma
l_int|1
comma
l_int|112
comma
l_int|3
comma
id|FB_SYNC_HOR_HIGH_ACT
op_or
id|FB_SYNC_VERT_HIGH_ACT
comma
id|FB_VMODE_NONINTERLACED
)brace
suffix:semicolon
DECL|variable|mac_modes
r_static
r_const
r_struct
id|mac_mode
op_star
id|mac_modes
(braket
l_int|20
)braket
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* 512x384, 60Hz interlaced (NTSC) */
l_int|NULL
comma
multiline_comment|/* 512x384, 60Hz */
l_int|NULL
comma
multiline_comment|/* 640x480, 50Hz interlaced (PAL) */
l_int|NULL
comma
multiline_comment|/* 640x480, 60Hz interlaced (NTSC) */
op_amp
id|mac_mode_5
comma
multiline_comment|/* 640x480, 60Hz (VGA) */
op_amp
id|mac_mode_6
comma
multiline_comment|/* 640x480, 67Hz */
l_int|NULL
comma
multiline_comment|/* 640x870, 75Hz (portrait) */
l_int|NULL
comma
multiline_comment|/* 768x576, 50Hz (PAL full frame) */
op_amp
id|mac_mode_9
comma
multiline_comment|/* 800x600, 56Hz */
op_amp
id|mac_mode_10
comma
multiline_comment|/* 800x600, 60Hz */
op_amp
id|mac_mode_11
comma
multiline_comment|/* 800x600, 72Hz */
op_amp
id|mac_mode_12
comma
multiline_comment|/* 800x600, 75Hz */
op_amp
id|mac_mode_13
comma
multiline_comment|/* 832x624, 75Hz */
op_amp
id|mac_mode_14
comma
multiline_comment|/* 1024x768, 60Hz */
op_amp
id|mac_mode_15
comma
multiline_comment|/* 1024x768, 70Hz (or 72Hz?) */
op_amp
id|mac_mode_16
comma
multiline_comment|/* 1024x768, 75Hz (VESA) */
op_amp
id|mac_mode_17
comma
multiline_comment|/* 1024x768, 75Hz */
op_amp
id|mac_mode_18
comma
multiline_comment|/* 1152x870, 75Hz */
op_amp
id|mac_mode_19
comma
multiline_comment|/* 1280x960, 75Hz */
op_amp
id|mac_mode_20
comma
multiline_comment|/* 1280x1024, 75Hz */
)brace
suffix:semicolon
DECL|variable|mac_modes_inv
r_static
r_const
r_struct
id|mac_mode
op_star
id|mac_modes_inv
(braket
)braket
op_assign
(brace
op_amp
id|mac_mode_6
comma
multiline_comment|/* 640x480, 67Hz */
op_amp
id|mac_mode_5
comma
multiline_comment|/* 640x480, 60Hz (VGA) */
op_amp
id|mac_mode_12
comma
multiline_comment|/* 800x600, 75Hz */
op_amp
id|mac_mode_11
comma
multiline_comment|/* 800x600, 72Hz */
op_amp
id|mac_mode_10
comma
multiline_comment|/* 800x600, 60Hz */
op_amp
id|mac_mode_9
comma
multiline_comment|/* 800x600, 56Hz */
op_amp
id|mac_mode_13
comma
multiline_comment|/* 832x624, 75Hz */
op_amp
id|mac_mode_17
comma
multiline_comment|/* 1024x768, 75Hz */
op_amp
id|mac_mode_16
comma
multiline_comment|/* 1024x768, 75Hz (VESA) */
op_amp
id|mac_mode_15
comma
multiline_comment|/* 1024x768, 70Hz (or 72Hz?) */
op_amp
id|mac_mode_14
comma
multiline_comment|/* 1024x768, 60Hz */
op_amp
id|mac_mode_18
comma
multiline_comment|/* 1152x870, 75Hz */
op_amp
id|mac_mode_19
comma
multiline_comment|/* 1280x960, 75Hz */
op_amp
id|mac_mode_20
comma
multiline_comment|/* 1280x1024, 75Hz */
)brace
suffix:semicolon
DECL|struct|mon_map
r_static
r_struct
id|mon_map
(brace
DECL|member|sense
r_int
id|sense
suffix:semicolon
DECL|member|vmode
r_int
id|vmode
suffix:semicolon
DECL|variable|monitor_map
)brace
id|monitor_map
(braket
)braket
op_assign
(brace
(brace
l_int|0x000
comma
id|VMODE_1280_1024_75
)brace
comma
multiline_comment|/* 21&quot; RGB */
(brace
l_int|0x114
comma
id|VMODE_640_870_75P
)brace
comma
multiline_comment|/* Portrait Monochrome */
(brace
l_int|0x221
comma
id|VMODE_512_384_60
)brace
comma
multiline_comment|/* 12&quot; RGB*/
(brace
l_int|0x331
comma
id|VMODE_1280_1024_75
)brace
comma
multiline_comment|/* 21&quot; RGB (Radius) */
(brace
l_int|0x334
comma
id|VMODE_1280_1024_75
)brace
comma
multiline_comment|/* 21&quot; mono (Radius) */
(brace
l_int|0x335
comma
id|VMODE_1280_1024_75
)brace
comma
multiline_comment|/* 21&quot; mono */
(brace
l_int|0x40A
comma
id|VMODE_640_480_60I
)brace
comma
multiline_comment|/* NTSC */
(brace
l_int|0x51E
comma
id|VMODE_640_870_75P
)brace
comma
multiline_comment|/* Portrait RGB */
(brace
l_int|0x603
comma
id|VMODE_832_624_75
)brace
comma
multiline_comment|/* 12&quot;-16&quot; multiscan */
(brace
l_int|0x60b
comma
id|VMODE_1024_768_70
)brace
comma
multiline_comment|/* 13&quot;-19&quot; multiscan */
(brace
l_int|0x623
comma
id|VMODE_1152_870_75
)brace
comma
multiline_comment|/* 13&quot;-21&quot; multiscan */
(brace
l_int|0x62b
comma
id|VMODE_640_480_67
)brace
comma
multiline_comment|/* 13&quot;/14&quot; RGB */
(brace
l_int|0x700
comma
id|VMODE_640_480_50I
)brace
comma
multiline_comment|/* PAL */
(brace
l_int|0x714
comma
id|VMODE_640_480_60I
)brace
comma
multiline_comment|/* NTSC */
(brace
l_int|0x717
comma
id|VMODE_800_600_75
)brace
comma
multiline_comment|/* VGA */
(brace
l_int|0x72d
comma
id|VMODE_832_624_75
)brace
comma
multiline_comment|/* 16&quot; RGB (Goldfish) */
(brace
l_int|0x730
comma
id|VMODE_768_576_50I
)brace
comma
multiline_comment|/* PAL (Alternate) */
(brace
l_int|0x73a
comma
id|VMODE_1152_870_75
)brace
comma
multiline_comment|/* 3rd party 19&quot; */
(brace
l_int|0x73f
comma
id|VMODE_640_480_67
)brace
comma
multiline_comment|/* no sense lines connected at all */
(brace
op_minus
l_int|1
comma
id|VMODE_640_480_60
)brace
comma
multiline_comment|/* catch-all, must be last */
)brace
suffix:semicolon
multiline_comment|/*&n;     *  Convert a MacOS vmode/cmode pair to a frame buffer video mode structure&n;     */
DECL|function|mac_vmode_to_var
r_int
id|mac_vmode_to_var
c_func
(paren
r_int
id|vmode
comma
r_int
id|cmode
comma
r_struct
id|fb_var_screeninfo
op_star
id|var
)paren
(brace
r_const
r_struct
id|mac_mode
op_star
id|mode
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|vmode
OG
l_int|0
op_logical_and
id|vmode
op_le
id|VMODE_MAX
)paren
id|mode
op_assign
id|mac_modes
(braket
id|vmode
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mode
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
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
r_switch
c_cond
(paren
id|cmode
)paren
(brace
r_case
id|CMODE_8
suffix:colon
id|var-&gt;bits_per_pixel
op_assign
l_int|8
suffix:semicolon
id|var-&gt;red.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CMODE_16
suffix:colon
id|var-&gt;bits_per_pixel
op_assign
l_int|16
suffix:semicolon
id|var-&gt;red.offset
op_assign
l_int|10
suffix:semicolon
id|var-&gt;red.length
op_assign
l_int|5
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|5
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|5
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|5
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CMODE_32
suffix:colon
id|var-&gt;bits_per_pixel
op_assign
l_int|32
suffix:semicolon
id|var-&gt;red.offset
op_assign
l_int|16
suffix:semicolon
id|var-&gt;red.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|8
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;transp.offset
op_assign
l_int|24
suffix:semicolon
id|var-&gt;transp.length
op_assign
l_int|8
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
id|var-&gt;xres
op_assign
id|mode-&gt;xres
suffix:semicolon
id|var-&gt;yres
op_assign
id|mode-&gt;yres
suffix:semicolon
id|var-&gt;xres_virtual
op_assign
id|mode-&gt;xres
suffix:semicolon
id|var-&gt;yres_virtual
op_assign
id|mode-&gt;yres
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
id|mode-&gt;pixclock
suffix:semicolon
id|var-&gt;left_margin
op_assign
id|mode-&gt;left_margin
suffix:semicolon
id|var-&gt;right_margin
op_assign
id|mode-&gt;right_margin
suffix:semicolon
id|var-&gt;upper_margin
op_assign
id|mode-&gt;upper_margin
suffix:semicolon
id|var-&gt;lower_margin
op_assign
id|mode-&gt;lower_margin
suffix:semicolon
id|var-&gt;hsync_len
op_assign
id|mode-&gt;hsync_len
suffix:semicolon
id|var-&gt;vsync_len
op_assign
id|mode-&gt;vsync_len
suffix:semicolon
id|var-&gt;sync
op_assign
id|mode-&gt;sync
suffix:semicolon
id|var-&gt;vmode
op_assign
id|mode-&gt;vmode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Convert a frame buffer video mode structure to a MacOS vmode/cmode pair&n;     */
DECL|function|mac_var_to_vmode
r_int
id|mac_var_to_vmode
c_func
(paren
r_const
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
op_star
id|vmode
comma
r_int
op_star
id|cmode
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
op_le
l_int|8
)paren
op_star
id|cmode
op_assign
id|CMODE_8
suffix:semicolon
r_else
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
op_le
l_int|16
)paren
op_star
id|cmode
op_assign
id|CMODE_16
suffix:semicolon
r_else
r_if
c_cond
(paren
id|var-&gt;bits_per_pixel
op_le
l_int|32
)paren
op_star
id|cmode
op_assign
id|CMODE_32
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
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
r_sizeof
(paren
id|mac_modes_inv
)paren
op_div
r_sizeof
(paren
op_star
id|mac_modes_inv
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_const
r_struct
id|mac_mode
op_star
id|mode
op_assign
id|mac_modes_inv
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;xres
OG
id|mode-&gt;xres
op_logical_or
id|var-&gt;yres
OG
id|mode-&gt;yres
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;xres_virtual
OG
id|mode-&gt;xres
op_logical_or
id|var-&gt;yres_virtual
OG
id|mode-&gt;yres
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;pixclock
OG
id|mode-&gt;pixclock
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;vmode
op_ne
id|mode-&gt;vmode
)paren
r_continue
suffix:semicolon
op_star
id|vmode
op_assign
id|mode-&gt;number
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Convert a Mac monitor sense number to a MacOS vmode number&n;     */
DECL|function|mac_map_monitor_sense
r_int
id|mac_map_monitor_sense
c_func
(paren
r_int
id|sense
)paren
(brace
r_struct
id|mon_map
op_star
id|map
suffix:semicolon
r_for
c_loop
(paren
id|map
op_assign
id|monitor_map
suffix:semicolon
id|map-&gt;sense
op_ge
l_int|0
suffix:semicolon
op_increment
id|map
)paren
r_if
c_cond
(paren
id|map-&gt;sense
op_eq
id|sense
)paren
r_break
suffix:semicolon
r_return
id|map-&gt;vmode
suffix:semicolon
)brace
eof