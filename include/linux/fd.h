macro_line|#ifndef _LINUX_FD_H
DECL|macro|_LINUX_FD_H
mdefine_line|#define _LINUX_FD_H
DECL|macro|FDCLRPRM
mdefine_line|#define FDCLRPRM 0 /* clear user-defined parameters */
DECL|macro|FDSETPRM
mdefine_line|#define FDSETPRM 1 /* set user-defined parameters for current media */
DECL|macro|FDDEFPRM
mdefine_line|#define FDDEFPRM 2 /* set user-defined parameters until explicitly cleared */
DECL|macro|FDGETPRM
mdefine_line|#define FDGETPRM 3 /* get disk parameters */
DECL|macro|FDMSGON
mdefine_line|#define&t;FDMSGON  4 /* issue kernel messages on media type change */
DECL|macro|FDMSGOFF
mdefine_line|#define&t;FDMSGOFF 5 /* don&squot;t issue kernel messages on media type change */
DECL|macro|FDFMTBEG
mdefine_line|#define FDFMTBEG 6 /* begin formatting a disk */
DECL|macro|FDFMTTRK
mdefine_line|#define&t;FDFMTTRK 7 /* format the specified track */
DECL|macro|FDFMTEND
mdefine_line|#define FDFMTEND 8 /* end formatting a disk */
DECL|macro|FDSETEMSGTRESH
mdefine_line|#define FDSETEMSGTRESH&t;10&t;/* set fdc error reporting treshold */
DECL|macro|FD_FILL_BYTE
mdefine_line|#define FD_FILL_BYTE 0xF6 /* format fill byte */
DECL|macro|FORMAT_NONE
mdefine_line|#define FORMAT_NONE&t;0&t;/* no format request */
DECL|macro|FORMAT_WAIT
mdefine_line|#define FORMAT_WAIT&t;1&t;/* format request is waiting */
DECL|macro|FORMAT_BUSY
mdefine_line|#define FORMAT_BUSY&t;2&t;/* formatting in progress */
DECL|macro|FORMAT_OKAY
mdefine_line|#define FORMAT_OKAY&t;3&t;/* successful completion */
DECL|macro|FORMAT_ERROR
mdefine_line|#define FORMAT_ERROR&t;4&t;/* formatting error */
DECL|struct|floppy_struct
r_struct
id|floppy_struct
(brace
DECL|member|size
r_int
r_int
id|size
comma
multiline_comment|/* nr of 512-byte sectors total */
DECL|member|sect
id|sect
comma
multiline_comment|/* sectors per track */
DECL|member|head
id|head
comma
multiline_comment|/* nr of heads */
DECL|member|track
id|track
comma
multiline_comment|/* nr of tracks */
DECL|member|stretch
id|stretch
suffix:semicolon
multiline_comment|/* !=0 means double track steps */
DECL|member|gap
r_int
r_char
id|gap
comma
multiline_comment|/* gap1 size */
DECL|member|rate
id|rate
comma
multiline_comment|/* data rate. |= 0x40 for perpendicular */
DECL|member|spec1
id|spec1
comma
multiline_comment|/* stepping rate, head unload time */
DECL|member|fmt_gap
id|fmt_gap
suffix:semicolon
multiline_comment|/* gap2 size */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* used only for predefined formats */
)brace
suffix:semicolon
DECL|struct|format_descr
r_struct
id|format_descr
(brace
DECL|member|device
DECL|member|head
DECL|member|track
r_int
r_int
id|device
comma
id|head
comma
id|track
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
