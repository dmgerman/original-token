multiline_comment|/*&n; * Definitions for display drivers for console use on PowerMacs.&n; *&n; * Copyright (C) 1997 Paul Mackerras.&n; *&t;&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
r_extern
r_int
id|serial_console
suffix:semicolon
multiline_comment|/* set to use serial port as console */
multiline_comment|/*&n; * Video mode values.&n; * These are supposed to be the same as the values that&n; * Apple uses in MacOS.&n; */
DECL|macro|VMODE_NVRAM
mdefine_line|#define VMODE_NVRAM&t;&t;0&t;/* use value stored in nvram */
DECL|macro|VMODE_512_384_60I
mdefine_line|#define VMODE_512_384_60I&t;1&t;/* 512x384, 60Hz interlaced (NTSC) */
DECL|macro|VMODE_512_384_60
mdefine_line|#define VMODE_512_384_60&t;2&t;/* 512x384, 60Hz */
DECL|macro|VMODE_640_480_50I
mdefine_line|#define VMODE_640_480_50I&t;3&t;/* 640x480, 50Hz interlaced (PAL) */
DECL|macro|VMODE_640_480_60I
mdefine_line|#define VMODE_640_480_60I&t;4&t;/* 640x480, 60Hz interlaced (NTSC) */
DECL|macro|VMODE_640_480_60
mdefine_line|#define VMODE_640_480_60&t;5&t;/* 640x480, 60Hz (VGA) */
DECL|macro|VMODE_640_480_67
mdefine_line|#define VMODE_640_480_67&t;6&t;/* 640x480, 67Hz */
DECL|macro|VMODE_640_870_75P
mdefine_line|#define VMODE_640_870_75P&t;7&t;/* 640x870, 75Hz (portrait) */
DECL|macro|VMODE_768_576_50I
mdefine_line|#define VMODE_768_576_50I&t;8&t;/* 768x576, 50Hz (PAL full frame) */
DECL|macro|VMODE_800_600_56
mdefine_line|#define VMODE_800_600_56&t;9&t;/* 800x600, 56Hz */
DECL|macro|VMODE_800_600_60
mdefine_line|#define VMODE_800_600_60&t;10&t;/* 800x600, 60Hz */
DECL|macro|VMODE_800_600_72
mdefine_line|#define VMODE_800_600_72&t;11&t;/* 800x600, 72Hz */
DECL|macro|VMODE_800_600_75
mdefine_line|#define VMODE_800_600_75&t;12&t;/* 800x600, 75Hz */
DECL|macro|VMODE_832_624_75
mdefine_line|#define VMODE_832_624_75&t;13&t;/* 832x624, 75Hz */
DECL|macro|VMODE_1024_768_60
mdefine_line|#define VMODE_1024_768_60&t;14&t;/* 1024x768, 60Hz */
DECL|macro|VMODE_1024_768_70
mdefine_line|#define VMODE_1024_768_70&t;15&t;/* 1024x768, 70Hz (or 72Hz?) */
DECL|macro|VMODE_1024_768_75V
mdefine_line|#define VMODE_1024_768_75V&t;16&t;/* 1024x768, 75Hz (VESA) */
DECL|macro|VMODE_1024_768_75
mdefine_line|#define VMODE_1024_768_75&t;17&t;/* 1024x768, 75Hz */
DECL|macro|VMODE_1152_870_75
mdefine_line|#define VMODE_1152_870_75&t;18&t;/* 1152x870, 75Hz */
DECL|macro|VMODE_1280_960_75
mdefine_line|#define VMODE_1280_960_75&t;19&t;/* 1280x960, 75Hz */
DECL|macro|VMODE_1280_1024_75
mdefine_line|#define VMODE_1280_1024_75&t;20&t;/* 1280x1024, 75Hz */
DECL|macro|VMODE_MAX
mdefine_line|#define VMODE_MAX&t;&t;20
DECL|macro|VMODE_CHOOSE
mdefine_line|#define VMODE_CHOOSE&t;&t;99&t;/* choose based on monitor sense */
multiline_comment|/*&n; * Color mode values, used to select number of bits/pixel.&n; */
DECL|macro|CMODE_NVRAM
mdefine_line|#define CMODE_NVRAM&t;&t;-1&t;/* use value stored in nvram */
DECL|macro|CMODE_8
mdefine_line|#define CMODE_8&t;&t;&t;0&t;/* 8 bits/pixel */
DECL|macro|CMODE_16
mdefine_line|#define CMODE_16&t;&t;1&t;/* 16 (actually 15) bits/pixel */
DECL|macro|CMODE_32
mdefine_line|#define CMODE_32&t;&t;2&t;/* 32 (actually 24) bits/pixel */
r_extern
r_int
id|video_mode
suffix:semicolon
r_extern
r_int
id|color_mode
suffix:semicolon
multiline_comment|/*&n; * Addresses in NVRAM where video mode and pixel size are stored.&n; */
DECL|macro|NV_VMODE
mdefine_line|#define NV_VMODE&t;0x140f
DECL|macro|NV_CMODE
mdefine_line|#define NV_CMODE&t;0x1410
multiline_comment|/*&n; * Horizontal and vertical resolution information.&n; */
DECL|struct|vmode_attr
r_extern
r_struct
id|vmode_attr
(brace
DECL|member|hres
r_int
id|hres
suffix:semicolon
DECL|member|vres
r_int
id|vres
suffix:semicolon
DECL|member|vfreq
r_int
id|vfreq
suffix:semicolon
DECL|member|interlaced
r_int
id|interlaced
suffix:semicolon
)brace
id|vmode_attrs
(braket
id|VMODE_MAX
)braket
suffix:semicolon
r_extern
r_struct
id|vc_mode
id|display_info
suffix:semicolon
DECL|macro|DEFAULT_VESA_BLANKING_MODE
mdefine_line|#define DEFAULT_VESA_BLANKING_MODE&t;VESA_NO_BLANKING
r_extern
r_int
id|pixel_size
suffix:semicolon
multiline_comment|/* in bytes */
r_extern
r_int
id|n_scanlines
suffix:semicolon
multiline_comment|/* # of scan lines */
r_extern
r_int
id|line_pitch
suffix:semicolon
multiline_comment|/* # bytes in 1 scan line */
r_extern
r_int
id|row_pitch
suffix:semicolon
multiline_comment|/* # bytes in 1 row of characters */
r_extern
r_int
r_char
op_star
id|fb_start
suffix:semicolon
multiline_comment|/* addr of top left pixel of top left char */
multiline_comment|/* map monitor sense value to video mode */
r_extern
r_int
id|map_monitor_sense
c_func
(paren
r_int
id|sense
)paren
suffix:semicolon
r_void
id|set_palette
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|pmac_find_display
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|vesa_blank
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|vesa_unblank
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|set_vesa_blanking
c_func
(paren
r_const
r_int
r_int
)paren
suffix:semicolon
r_void
id|vesa_powerdown
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|hide_cursor
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|pmac_init_palette
c_func
(paren
r_void
)paren
suffix:semicolon
eof
