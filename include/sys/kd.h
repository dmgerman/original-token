macro_line|#ifndef _KD_H
DECL|macro|_KD_H
mdefine_line|#define _KD_H
multiline_comment|/* 0x4B is &squot;K&squot;, to avoid collision with termios and vt */
DECL|macro|SWAPMONO
mdefine_line|#define SWAPMONO&t;0x4B00&t;/* use mca as output device */
DECL|macro|SWAPCGA
mdefine_line|#define SWAPCGA&t;&t;0x4B01&t;/* use cga as output device */
DECL|macro|SWAPEGA
mdefine_line|#define SWAPEGA&t;&t;0x4B02&t;/* use ega as output device */
DECL|macro|SWAPVGA
mdefine_line|#define SWAPVGA&t;&t;0x4B03&t;/* use vga as output device */
DECL|macro|CONS_CURRENT
mdefine_line|#define CONS_CURRENT&t;0x4B04&t;/* return current output device */
DECL|macro|MONO
mdefine_line|#define&t;&t;MONO&t;&t;0x01
DECL|macro|CGA
mdefine_line|#define&t;&t;CGA&t;&t;0x02
DECL|macro|EGA
mdefine_line|#define&t;&t;EGA&t;&t;0x03
DECL|macro|SW_B40x25
mdefine_line|#define SW_B40x25&t;0x4B05&t;/* 40x25 mono text (cga/ega) */
DECL|macro|SW_C40x25
mdefine_line|#define SW_C40x25&t;0x4B06&t;/* 40x24 color text (cga/ega) */
DECL|macro|SW_B80x25
mdefine_line|#define SW_B80x25&t;0x4B07&t;/* 80x25 mono text (cga/ega) */
DECL|macro|SW_C80x25
mdefine_line|#define SW_C80x25&t;0x4B08&t;/* 80x25 color text (cga/ega) */
DECL|macro|SW_BG320
mdefine_line|#define SW_BG320&t;0x4B09&t;/* 320x200 mono graphics (cga/ega) */
DECL|macro|SW_CG320
mdefine_line|#define SW_CG320&t;0x4B0A&t;/* 320x200 color graphics (cga/ega) */
DECL|macro|SW_BG640
mdefine_line|#define SW_BG640&t;0x4B0B&t;/* 640x200 mono graphics (cga/ega) */
DECL|macro|SW_CG320_D
mdefine_line|#define SW_CG320_D&t;0x4B0C&t;/* 320x200 graphics (ega mode d) */
DECL|macro|SW_CG640_E
mdefine_line|#define SW_CG640_E&t;0x4B0D&t;/* 640x200 graphics (ega mode e) */
DECL|macro|SW_EGAMONOAPA
mdefine_line|#define SW_EGAMONOAPA&t;0x4B0E&t;/* 640x350 graphics (ega mode f) */
DECL|macro|SW_ENH_MONOAPA2
mdefine_line|#define SW_ENH_MONOAPA2&t;0x4B0F&t;/* 640x350 graphics extd mem (ega mode f*) */
DECL|macro|SW_CG640x350
mdefine_line|#define SW_CG640x350&t;0x4B10&t;/* 640x350 graphics (ega mode 10) */
DECL|macro|SW_ENH_CG640
mdefine_line|#define SW_ENH_CG640&t;0x4B11&t;/* 640x350 graphics extd mem (ega mode 10*) */
DECL|macro|SW_EGAMONO80x25
mdefine_line|#define SW_EGAMONO80x25&t;0x4B12&t;/* 80x25 mono text (ega mode 7) */
DECL|macro|SW_ENHB40x25
mdefine_line|#define SW_ENHB40x25&t;0x4B13&t;/* enhanced 40x25 mono text (ega) */
DECL|macro|SW_ENHC40x25
mdefine_line|#define SW_ENHC40x25&t;0x4B14&t;/* enhanced 40x25 color text (ega) */
DECL|macro|SW_ENHB80x25
mdefine_line|#define SW_ENHB80x25&t;0x4B15&t;/* enhanced 80x25 mono text (ega) */
DECL|macro|SW_ENHC80x25
mdefine_line|#define SW_ENHC80x25&t;0x4B16&t;/* enhanced 80x25 color text (ega) */
DECL|macro|SW_ENHB80x43
mdefine_line|#define SW_ENHB80x43&t;0x4B17&t;/* enhanced 80x43 mono text (ega) */
DECL|macro|SW_ENHC80x43
mdefine_line|#define SW_ENHC80x43&t;0x4B18&t;/* enhanced 80x43 color text (ega) */
DECL|macro|SW_MCAMODE
mdefine_line|#define SW_MCAMODE&t;0x4B19&t;/* reinit mca */
DECL|macro|SW_ATT640
mdefine_line|#define SW_ATT640&t;0x4B1A&t;/* 640x400 16color */
multiline_comment|/* should add more vga modes, etc */
DECL|macro|CONS_GET
mdefine_line|#define CONS_GET&t;0x4B1B&t;/* get current display mode */
DECL|macro|M_B40x25
mdefine_line|#define&t;&t;M_B40x25&t;0&t;/* 40x25 mono (cga/ega) */
DECL|macro|M_C40x25
mdefine_line|#define&t;&t;M_C40x25&t;1&t;/* 40x25 color (cga/ega) */
DECL|macro|M_B80x25
mdefine_line|#define&t;&t;M_B80x25&t;2&t;/* 80x25 mono (cga/ega) */
DECL|macro|M_C80x25
mdefine_line|#define&t;&t;M_C80x25&t;3&t;/* 80x25 color (cga/ega) */
DECL|macro|M_BG320
mdefine_line|#define&t;&t;M_BG320&t;&t;4&t;/* 320x200 mono (cga/ega) */
DECL|macro|M_CG320
mdefine_line|#define&t;&t;M_CG320&t;&t;5&t;/* 320x200 color (cga/ega) */
DECL|macro|M_BG640
mdefine_line|#define&t;&t;M_BG640&t;&t;6&t;/* 640x200 mono (cga/ega) */
DECL|macro|M_EGAMONO80x25
mdefine_line|#define&t;&t;M_EGAMONO80x25&t;7&t;/* 80x25 mono (ega) */
DECL|macro|M_CG320_D
mdefine_line|#define&t;&t;M_CG320_D&t;13&t;/* ega mode d */
DECL|macro|M_CG640_E
mdefine_line|#define&t;&t;M_CG640_E&t;14&t;/* ega mode e */
DECL|macro|M_EFAMONOAPA
mdefine_line|#define&t;&t;M_EFAMONOAPA&t;15&t;/* ega mode f */
DECL|macro|M_CG640x350
mdefine_line|#define&t;&t;M_CG640x350&t;16&t;/* ega mode 10 */
DECL|macro|M_ENHMONOAPA2
mdefine_line|#define&t;&t;M_ENHMONOAPA2&t;17&t;/* ega mode f with ext mem */
DECL|macro|M_ENH_CG640
mdefine_line|#define&t;&t;M_ENH_CG640&t;18&t;/* ega mode 10* */
DECL|macro|M_ENH_B40x25
mdefine_line|#define&t;&t;M_ENH_B40x25&t;19&t;/* ega enh 40x25 mono */
DECL|macro|M_ENH_C40x25
mdefine_line|#define&t;&t;M_ENH_C40x25&t;20&t;/* ega enh 40x25 color */
DECL|macro|M_ENH_B80x25
mdefine_line|#define&t;&t;M_ENH_B80x25&t;21&t;/* ega enh 80x25 mono */
DECL|macro|M_ENH_C80x25
mdefine_line|#define&t;&t;M_ENH_C80x25&t;22&t;/* ega enh 80x25 color */
DECL|macro|M_ENH_B80x43
mdefine_line|#define&t;&t;M_ENH_B80x43&t;0x70&t;/* ega enh 80x43 mono */
DECL|macro|M_ENH_C80x43
mdefine_line|#define&t;&t;M_ENH_C80x43&t;0x71&t;/* ega enh 80x43 color */
DECL|macro|M_MCA_MODE
mdefine_line|#define&t;&t;M_MCA_MODE&t;0xff&t;/* monochrome adapter mode */
DECL|macro|MCA_GET
mdefine_line|#define MCA_GET&t;&t;0x4B1C&t;/* get mca display mode */
DECL|macro|CGA_GET
mdefine_line|#define CGA_GET&t;&t;0x4B1D&t;/* get cga display mode */
DECL|macro|EGA_GET
mdefine_line|#define EGA_GET&t;&t;0x4B1E&t;/* get ega display mode */
DECL|macro|MAPCONS
mdefine_line|#define MAPCONS&t;&t;0x4B1F&t;/* map current video mem into address space */
DECL|macro|MAPMONO
mdefine_line|#define MAPMONO&t;&t;0x4B20&t;/* map mca video mem into address space */
DECL|macro|MAPCGA
mdefine_line|#define MAPCGA&t;&t;0x4B21&t;/* map cga video mem into address space */
DECL|macro|MAPEGA
mdefine_line|#define MAPEGA&t;&t;0x4B22&t;/* map ega video mem into address space */
DECL|macro|MAPVGA
mdefine_line|#define MAPVGA&t;&t;0x4B23&t;/* map vga video mem into address space */
DECL|struct|port_io_struc
r_struct
id|port_io_struc
(brace
DECL|member|dir
r_char
id|dir
suffix:semicolon
multiline_comment|/* direction in vs out */
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
DECL|member|data
r_char
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IN_ON_PORT
mdefine_line|#define&t;&t;IN_ON_PORT&t;0x00
DECL|macro|OUT_ON_PORT
mdefine_line|#define&t;&t;OUT_ON_PORT&t;0x01
DECL|struct|port_io_arg
r_struct
id|port_io_arg
(brace
DECL|member|args
r_struct
id|port_io_struc
id|args
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MCAIO
mdefine_line|#define MCAIO&t;&t;0x4B24&t;/* i/o to mca video board */
DECL|macro|CGAIO
mdefine_line|#define CGAIO&t;&t;0x4B25&t;/* i/o to cga video board */
DECL|macro|EGAIO
mdefine_line|#define EGAIO&t;&t;0x4B26&t;/* i/o to ega video board */
DECL|macro|VGAIO
mdefine_line|#define VGAIO&t;&t;0x4B27&t;/* i/o to vga video board */
DECL|macro|GIO_FONT8x8
mdefine_line|#define GIO_FONT8x8&t;0x4B28&t;/* gets current 8x8 font used */
DECL|macro|PIO_FONT8x8
mdefine_line|#define PIO_FONT8x8&t;0x4B29&t;/* use supplied 8x8 font */
DECL|macro|GIO_FONT8x14
mdefine_line|#define GIO_FONT8x14&t;0x4B2A&t;/* gets current 8x14 font used */
DECL|macro|PIO_FONT8x14
mdefine_line|#define PIO_FONT8x14&t;0x4B2B&t;/* use supplied 8x14 font */
DECL|macro|GIO_FONT8x16
mdefine_line|#define GIO_FONT8x16&t;0x4B2C&t;/* gets current 8x16 font used */
DECL|macro|PIO_FONT8x16
mdefine_line|#define PIO_FONT8x16&t;0x4B2D&t;/* use supplied 8x16 font */
DECL|macro|MKDIOADDR
mdefine_line|#define MKDIOADDR&t;32&t;/* io bitmap size from &lt;linux/sched.h&gt; */
DECL|struct|kd_disparam
r_struct
id|kd_disparam
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* type of display */
DECL|member|addr
r_char
op_star
id|addr
suffix:semicolon
multiline_comment|/* display mem address */
DECL|member|ioaddr
id|ushort
id|ioaddr
(braket
id|MKDIOADDR
)braket
suffix:semicolon
multiline_comment|/* valid i/o addresses */
)brace
suffix:semicolon
DECL|macro|KDDISPTYPE
mdefine_line|#define KDDISPTYPE&t;0x4B2E&t;/* gets display info */
DECL|macro|KD_MONO
mdefine_line|#define&t;&t;KD_MONO&t;&t;0x01
DECL|macro|KD_HERCULES
mdefine_line|#define&t;&t;KD_HERCULES&t;0x02
DECL|macro|KD_CGA
mdefine_line|#define&t;&t;KD_CGA&t;&t;0x03
DECL|macro|KD_EGA
mdefine_line|#define&t;&t;KD_EGA&t;&t;0x04
DECL|macro|KIOCSOUND
mdefine_line|#define KIOCSOUND&t;0x4B2F&t;/* start sound generation (0 for off) */
DECL|macro|KDMKTONE
mdefine_line|#define KDMKTONE&t;0x4B30&t;/* generate tone */
DECL|macro|KDGETLED
mdefine_line|#define KDGETLED&t;0x4B31&t;/* return current led flags */
DECL|macro|KDSETLED
mdefine_line|#define KDSETLED&t;0x4B32&t;/* set current led flags */
DECL|macro|LED_SCR
mdefine_line|#define &t;LED_SCR&t;&t;0x01&t;/* scroll lock */
DECL|macro|LED_CAP
mdefine_line|#define &t;LED_CAP&t;&t;0x04&t;/* caps lock */
DECL|macro|LED_NUM
mdefine_line|#define &t;LED_NUM&t;&t;0x02&t;/* num lock */
DECL|macro|KDGKBTYPE
mdefine_line|#define KDGKBTYPE&t;0x4B33&t;/* get keyboard type */
DECL|macro|KB_84
mdefine_line|#define &t;KB_84&t;&t;0x01
DECL|macro|KB_101
mdefine_line|#define &t;KB_101&t;&t;0x02
DECL|macro|KB_OTHER
mdefine_line|#define &t;KB_OTHER&t;0x03
DECL|macro|KDADDIO
mdefine_line|#define KDADDIO&t;&t;0x4B34&t;/* add i/o port as valid */
DECL|macro|KDDELIO
mdefine_line|#define KDDELIO&t;&t;0x4B35&t;/* del i/o port as valid */
DECL|macro|KDENABIO
mdefine_line|#define KDENABIO&t;0x4B36&t;/* enable i/o to video board */
DECL|macro|KDDISABIO
mdefine_line|#define KDDISABIO&t;0x4B37&t;/* disable i/o to video board */
DECL|struct|kd_quemode
r_struct
id|kd_quemode
(brace
DECL|member|qsize
r_int
id|qsize
suffix:semicolon
multiline_comment|/* desired # elem in queue */
DECL|member|signo
r_int
id|signo
suffix:semicolon
multiline_comment|/* signal to send when queue not empty */
DECL|member|qaddr
r_char
op_star
id|qaddr
suffix:semicolon
multiline_comment|/* user virt addr of queue */
)brace
suffix:semicolon
DECL|macro|KDQUEMODE
mdefine_line|#define KDQUEMODE&t;0x4B38&t;/* enable/disable special queue mode */
DECL|macro|KDSBORDER
mdefine_line|#define KDSBORDER&t;0x4B39&t;/* set screen boarder in ega text mode */
DECL|macro|KDSETMODE
mdefine_line|#define KDSETMODE&t;0x4B3A&t;/* set text/grahics mode */
DECL|macro|KD_TEXT
mdefine_line|#define&t;&t;KD_TEXT&t;&t;0x00
DECL|macro|KD_GRAPHICS
mdefine_line|#define&t;&t;KD_GRAPHICS&t;0x01
DECL|macro|KD_TEXT0
mdefine_line|#define&t;&t;KD_TEXT0&t;0x02&t;/* ? */
DECL|macro|KD_TEXT1
mdefine_line|#define&t;&t;KD_TEXT1&t;0x03&t;/* ? */
DECL|macro|KDGETMODE
mdefine_line|#define KDGETMODE&t;0x4B3B&t;/* get current mode */
DECL|struct|kd_memloc
r_struct
id|kd_memloc
(brace
DECL|member|vaddr
r_char
op_star
id|vaddr
suffix:semicolon
multiline_comment|/* virt addr to map to */
DECL|member|physaddr
r_char
op_star
id|physaddr
suffix:semicolon
multiline_comment|/* phys addr to map from */
DECL|member|length
r_int
id|length
suffix:semicolon
multiline_comment|/* number of bytes */
DECL|member|ioflg
r_int
id|ioflg
suffix:semicolon
multiline_comment|/* enable i/o if set */
)brace
suffix:semicolon
DECL|macro|KDMAPDISP
mdefine_line|#define KDMAPDISP&t;0x4B3C&t;/* map display into address space */
DECL|macro|KDUNMAPDISP
mdefine_line|#define KDUNMAPDISP&t;0x4B3D&t;/* unmap display from address space */
DECL|macro|KDVDCTYPE
mdefine_line|#define KDVDCTYPE&t;0x4B3E&t;/* return vdc controller/display info */
DECL|macro|KIOCINFO
mdefine_line|#define KIOCINFO&t;0x4B3F&t;/* tell what the device is */
DECL|typedef|scrnmap_t
r_typedef
r_char
id|scrnmap_t
suffix:semicolon
DECL|macro|E_TABSZ
mdefine_line|#define&t;&t;E_TABSZ&t;&t;256
DECL|macro|GIO_SCRNMAP
mdefine_line|#define GIO_SCRNMAP&t;0x4B40&t;/* get screen mapping from kernel */
DECL|macro|PIO_SCRNMAP
mdefine_line|#define PIO_SCRNMAP&t;0x4B41&t;/* put screen mapping table in kernel */
DECL|macro|GIO_ATTR
mdefine_line|#define GIO_ATTR&t;0x4B42&t;/* get screen attributes */
DECL|macro|GIO_COLOR
mdefine_line|#define GIO_COLOR&t;0x4B43&t;/* return nonzero if display is color */
DECL|macro|K_RAW
mdefine_line|#define&t;&t;K_RAW&t;&t;0x00
DECL|macro|K_XLATE
mdefine_line|#define&t;&t;K_XLATE&t;&t;0x01
DECL|macro|KDGKBMODE
mdefine_line|#define KDGKBMODE&t;0x4B44&t;/* gets current keyboard mode */
DECL|macro|KDSKBMODE
mdefine_line|#define KDSKBMODE&t;0x4B45&t;/* sets current keyboard mode */
DECL|struct|kbentry
r_struct
id|kbentry
(brace
DECL|member|kb_table
id|u_char
id|kb_table
suffix:semicolon
DECL|member|kb_index
id|u_char
id|kb_index
suffix:semicolon
DECL|member|kb_value
id|u_char
id|kb_value
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|K_NORMTAB
mdefine_line|#define&t;&t;K_NORMTAB&t;0x00
DECL|macro|K_SHIFTTAB
mdefine_line|#define&t;&t;K_SHIFTTAB&t;0x01
DECL|macro|K_ALTTAB
mdefine_line|#define&t;&t;K_ALTTAB&t;0x02
DECL|macro|K_ALTSHIFTTAB
mdefine_line|#define&t;&t;K_ALTSHIFTTAB&t;0x03
DECL|macro|K_SRQTAB
mdefine_line|#define&t;&t;K_SRQTAB&t;0x04
DECL|macro|KDGKBENT
mdefine_line|#define KDGKBENT&t;0x4B46&t;/* gets one entry in translation table */
DECL|macro|KDSKBENT
mdefine_line|#define KDSKBENT&t;0x4B47&t;/* sets one entry in translation table */
macro_line|#endif /* _KD_H */
eof
