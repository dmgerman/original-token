macro_line|#ifndef __LINUX_FBIO_H
DECL|macro|__LINUX_FBIO_H
mdefine_line|#define __LINUX_FBIO_H
multiline_comment|/* Constants used for fbio SunOS compatibility -miguel */
multiline_comment|/* Frame buffer types */
DECL|macro|FBTYPE_NOTYPE
mdefine_line|#define FBTYPE_NOTYPE           -1
DECL|macro|FBTYPE_SUN1BW
mdefine_line|#define FBTYPE_SUN1BW           0   /* mono */
DECL|macro|FBTYPE_SUN1COLOR
mdefine_line|#define FBTYPE_SUN1COLOR        1 
DECL|macro|FBTYPE_SUN2BW
mdefine_line|#define FBTYPE_SUN2BW           2 
DECL|macro|FBTYPE_SUN2COLOR
mdefine_line|#define FBTYPE_SUN2COLOR        3 
DECL|macro|FBTYPE_SUN2GP
mdefine_line|#define FBTYPE_SUN2GP           4 
DECL|macro|FBTYPE_SUN5COLOR
mdefine_line|#define FBTYPE_SUN5COLOR        5 
DECL|macro|FBTYPE_SUN3COLOR
mdefine_line|#define FBTYPE_SUN3COLOR        6 
DECL|macro|FBTYPE_MEMCOLOR
mdefine_line|#define FBTYPE_MEMCOLOR         7 
DECL|macro|FBTYPE_SUN4COLOR
mdefine_line|#define FBTYPE_SUN4COLOR        8 
DECL|macro|FBTYPE_NOTSUN1
mdefine_line|#define FBTYPE_NOTSUN1          9 
DECL|macro|FBTYPE_NOTSUN2
mdefine_line|#define FBTYPE_NOTSUN2          10
DECL|macro|FBTYPE_NOTSUN3
mdefine_line|#define FBTYPE_NOTSUN3          11
DECL|macro|FBTYPE_SUNFAST_COLOR
mdefine_line|#define FBTYPE_SUNFAST_COLOR    12  /* cg6 */
DECL|macro|FBTYPE_SUNROP_COLOR
mdefine_line|#define FBTYPE_SUNROP_COLOR     13
DECL|macro|FBTYPE_SUNFB_VIDEO
mdefine_line|#define FBTYPE_SUNFB_VIDEO      14
DECL|macro|FBTYPE_SUNGIFB
mdefine_line|#define FBTYPE_SUNGIFB          15
DECL|macro|FBTYPE_SUNGPLAS
mdefine_line|#define FBTYPE_SUNGPLAS         16
DECL|macro|FBTYPE_SUNGP3
mdefine_line|#define FBTYPE_SUNGP3           17
DECL|macro|FBTYPE_SUNGT
mdefine_line|#define FBTYPE_SUNGT            18
DECL|macro|FBTYPE_SUNLEO
mdefine_line|#define FBTYPE_SUNLEO           19      /* zx Leo card */
DECL|macro|FBTYPE_MDICOLOR
mdefine_line|#define FBTYPE_MDICOLOR         20      /* cg14 */
DECL|macro|FBTYPE_LASTPLUSONE
mdefine_line|#define FBTYPE_LASTPLUSONE      21
multiline_comment|/* fbio ioctls */
multiline_comment|/* Returned by FBIOGTYPE */
DECL|struct|fbtype
r_struct
id|fbtype
(brace
DECL|member|fb_type
r_int
id|fb_type
suffix:semicolon
multiline_comment|/* fb type, see above */
DECL|member|fb_height
r_int
id|fb_height
suffix:semicolon
multiline_comment|/* pixels */
DECL|member|fb_width
r_int
id|fb_width
suffix:semicolon
multiline_comment|/* pixels */
DECL|member|fb_depth
r_int
id|fb_depth
suffix:semicolon
DECL|member|fb_cmsize
r_int
id|fb_cmsize
suffix:semicolon
multiline_comment|/* color map entries */
DECL|member|fb_size
r_int
id|fb_size
suffix:semicolon
multiline_comment|/* fb size in bytes */
)brace
suffix:semicolon
DECL|macro|FBIOGTYPE
mdefine_line|#define FBIOGTYPE _IOR(&squot;F&squot;, 0, struct fbtype)
multiline_comment|/* Used by FBIOPUTCMAP */
DECL|struct|fbcmap
r_struct
id|fbcmap
(brace
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* first element (0 origin) */
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|red
r_int
r_char
op_star
id|red
suffix:semicolon
DECL|member|green
r_int
r_char
op_star
id|green
suffix:semicolon
DECL|member|blue
r_int
r_char
op_star
id|blue
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FBIOPUTCMAP
mdefine_line|#define FBIOPUTCMAP _IOW(&squot;F&squot;, 3, struct fbcmap)
multiline_comment|/* # of device specific values */
DECL|macro|FB_ATTR_NDEVSPECIFIC
mdefine_line|#define FB_ATTR_NDEVSPECIFIC    8
multiline_comment|/* # of possible emulations */
DECL|macro|FB_ATTR_NEMUTYPES
mdefine_line|#define FB_ATTR_NEMUTYPES       4
DECL|struct|fbsattr
r_struct
id|fbsattr
(brace
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|emu_type
r_int
id|emu_type
suffix:semicolon
multiline_comment|/* -1 if none */
DECL|member|dev_specific
r_int
id|dev_specific
(braket
id|FB_ATTR_NDEVSPECIFIC
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fbgattr
r_struct
id|fbgattr
(brace
DECL|member|real_type
r_int
id|real_type
suffix:semicolon
multiline_comment|/* real frame buffer type */
DECL|member|owner
r_int
id|owner
suffix:semicolon
multiline_comment|/* unknown */
DECL|member|fbtype
r_struct
id|fbtype
id|fbtype
suffix:semicolon
multiline_comment|/* real frame buffer fbtype */
DECL|member|sattr
r_struct
id|fbsattr
id|sattr
suffix:semicolon
DECL|member|emu_types
r_int
id|emu_types
(braket
id|FB_ATTR_NEMUTYPES
)braket
suffix:semicolon
multiline_comment|/* supported emulations */
)brace
suffix:semicolon
DECL|macro|FBIOSATTR
mdefine_line|#define FBIOSATTR  _IOW(&squot;F&squot;, 5, struct fbgattr) /* Unsupported: */
DECL|macro|FBIOGATTR
mdefine_line|#define FBIOGATTR  _IOR(&squot;F&squot;, 6, struct fbgattr)&t;/* supported */
DECL|macro|FBIOSVIDEO
mdefine_line|#define FBIOSVIDEO _IOW(&squot;F&squot;, 7, int)
DECL|macro|FBIOGVIDEO
mdefine_line|#define FBIOGVIDEO _IOR(&squot;F&squot;, 8, int)
multiline_comment|/* Cursor position */
DECL|struct|fbcurpos
r_struct
id|fbcurpos
(brace
macro_line|#ifdef __KERNEL__
DECL|member|fbx
DECL|member|fby
r_int
id|fbx
comma
id|fby
suffix:semicolon
macro_line|#else
r_int
id|x
comma
id|y
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* Cursor operations */
DECL|macro|FB_CUR_SETCUR
mdefine_line|#define FB_CUR_SETCUR   0x01&t;/* Enable/disable cursor display */
DECL|macro|FB_CUR_SETPOS
mdefine_line|#define FB_CUR_SETPOS   0x02&t;/* set cursor position */
DECL|macro|FB_CUR_SETHOT
mdefine_line|#define FB_CUR_SETHOT   0x04&t;/* set cursor hotspot */
DECL|macro|FB_CUR_SETCMAP
mdefine_line|#define FB_CUR_SETCMAP  0x08&t;/* set color map for the cursor */
DECL|macro|FB_CUR_SETSHAPE
mdefine_line|#define FB_CUR_SETSHAPE 0x10&t;/* set shape */
DECL|macro|FB_CUR_SETALL
mdefine_line|#define FB_CUR_SETALL   0x1F&t;/* all of the above */
DECL|struct|fbcursor
r_struct
id|fbcursor
(brace
DECL|member|set
r_int
id|set
suffix:semicolon
multiline_comment|/* what to set, choose from the list above */
DECL|member|enable
r_int
id|enable
suffix:semicolon
multiline_comment|/* cursor on/off */
DECL|member|pos
r_struct
id|fbcurpos
id|pos
suffix:semicolon
multiline_comment|/* cursor position */
DECL|member|hot
r_struct
id|fbcurpos
id|hot
suffix:semicolon
multiline_comment|/* cursor hot spot */
DECL|member|cmap
r_struct
id|fbcmap
id|cmap
suffix:semicolon
multiline_comment|/* color map info */
DECL|member|size
r_struct
id|fbcurpos
id|size
suffix:semicolon
multiline_comment|/* cursor bit map size */
DECL|member|image
r_char
op_star
id|image
suffix:semicolon
multiline_comment|/* cursor image bits */
DECL|member|mask
r_char
op_star
id|mask
suffix:semicolon
multiline_comment|/* cursor mask bits */
)brace
suffix:semicolon
multiline_comment|/* set/get cursor attributes/shape */
DECL|macro|FBIOSCURSOR
mdefine_line|#define FBIOSCURSOR     _IOW(&squot;F&squot;, 24, struct fbcursor)
DECL|macro|FBIOGCURSOR
mdefine_line|#define FBIOGCURSOR     _IOWR(&squot;F&squot;, 25, struct fbcursor)
multiline_comment|/* set/get cursor position */
DECL|macro|FBIOSCURPOS
mdefine_line|#define FBIOSCURPOS     _IOW(&squot;F&squot;, 26, struct fbcurpos)
DECL|macro|FBIOGCURPOS
mdefine_line|#define FBIOGCURPOS     _IOW(&squot;F&squot;, 27, struct fbcurpos)
multiline_comment|/* get max cursor size */
DECL|macro|FBIOGCURMAX
mdefine_line|#define FBIOGCURMAX     _IOR(&squot;F&squot;, 28, struct fbcurpos)
macro_line|#ifdef __KERNEL__
multiline_comment|/* Addresses on the fd of a cgsix that are mappable */
DECL|macro|CG6_FBC
mdefine_line|#define CG6_FBC    0x70000000
DECL|macro|CG6_TEC
mdefine_line|#define CG6_TEC    0x70001000
DECL|macro|CG6_BTREGS
mdefine_line|#define CG6_BTREGS 0x70002000
DECL|macro|CG6_FHC
mdefine_line|#define CG6_FHC    0x70004000
DECL|macro|CG6_THC
mdefine_line|#define CG6_THC    0x70005000
DECL|macro|CG6_ROM
mdefine_line|#define CG6_ROM    0x70006000
DECL|macro|CG6_RAM
mdefine_line|#define CG6_RAM    0x70016000
DECL|macro|CG6_DHC
mdefine_line|#define CG6_DHC    0x80000000
DECL|macro|CG3_MMAP_OFFSET
mdefine_line|#define CG3_MMAP_OFFSET 0x4000000
macro_line|#endif /* KERNEL */
macro_line|#endif /* __LINUX_FBIO_H */
eof
