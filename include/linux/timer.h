macro_line|#ifndef _TIMER_H
DECL|macro|_TIMER_H
mdefine_line|#define _TIMER_H
multiline_comment|/*&n; * DON&squot;T CHANGE THESE!! Most of them are hardcoded into some assembly language&n; * as well as being defined here.&n; */
multiline_comment|/*&n; * The timers are:&n; *&n; * BLANK_TIMER&t;&t;console screen-saver timer&n; *&n; * BEEP_TIMER&t;&t;console beep timer&n; *&n; * SERx_TIMER&t;&t;serial incoming characters timer&n; *&n; * SERx_TIMEOUT&t;&t;timeout for serial writes&n; *&n; * HD_TIMER&t;&t;harddisk timer&n; *&n; * FLOPPY_TIMER&t;&t;floppy disk timer (not used right now)&n; * &n; * SCSI_TIMER&t;&t;scsi.c timeout timer&n; */
DECL|macro|BLANK_TIMER
mdefine_line|#define BLANK_TIMER&t;0
DECL|macro|BEEP_TIMER
mdefine_line|#define BEEP_TIMER&t;1
DECL|macro|SER1_TIMER
mdefine_line|#define SER1_TIMER&t;2
DECL|macro|SER2_TIMER
mdefine_line|#define SER2_TIMER&t;3
DECL|macro|SER3_TIMER
mdefine_line|#define SER3_TIMER&t;4
DECL|macro|SER4_TIMER
mdefine_line|#define SER4_TIMER&t;5
DECL|macro|SER1_TIMEOUT
mdefine_line|#define SER1_TIMEOUT&t;8
DECL|macro|SER2_TIMEOUT
mdefine_line|#define SER2_TIMEOUT&t;9
DECL|macro|SER3_TIMEOUT
mdefine_line|#define SER3_TIMEOUT&t;10
DECL|macro|SER4_TIMEOUT
mdefine_line|#define SER4_TIMEOUT&t;11
DECL|macro|HD_TIMER
mdefine_line|#define HD_TIMER&t;16
DECL|macro|FLOPPY_TIMER
mdefine_line|#define FLOPPY_TIMER&t;17
DECL|macro|SCSI_TIMER
mdefine_line|#define SCSI_TIMER &t;18
DECL|struct|timer_struct
r_struct
id|timer_struct
(brace
DECL|member|expires
r_int
r_int
id|expires
suffix:semicolon
DECL|member|fn
r_void
(paren
op_star
id|fn
)paren
(paren
r_void
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
r_int
id|timer_active
suffix:semicolon
r_extern
r_struct
id|timer_struct
id|timer_table
(braket
l_int|32
)braket
suffix:semicolon
macro_line|#endif
eof
