macro_line|#ifndef _LINUX_TIMER_H
DECL|macro|_LINUX_TIMER_H
mdefine_line|#define _LINUX_TIMER_H
multiline_comment|/*&n; * DON&squot;T CHANGE THESE!! Most of them are hardcoded into some assembly language&n; * as well as being defined here.&n; */
multiline_comment|/*&n; * The timers are:&n; *&n; * BLANK_TIMER&t;&t;console screen-saver timer&n; *&n; * BEEP_TIMER&t;&t;console beep timer&n; *&n; * RS_TIMER&t;&t;timer for the RS-232 ports&n; * &n; * HD_TIMER&t;&t;harddisk timer&n; *&n; * HD_TIMER2&t;&t;(atdisk2 patches)&n; *&n; * FLOPPY_TIMER&t;&t;floppy disk timer (not used right now)&n; * &n; * SCSI_TIMER&t;&t;scsi.c timeout timer&n; *&n; * NET_TIMER&t;&t;tcp/ip timeout timer&n; *&n; * COPRO_TIMER&t;&t;387 timeout for buggy hardware..&n; *&n; * QIC02_TAPE_TIMER&t;timer for QIC-02 tape driver (it&squot;s not hardcoded)&n; *&n; * MCD_TIMER&t;&t;Mitsumi CD-ROM Timer&n; *&n; * GSCD_TIMER&t;&t;Goldstar CD-ROM Timer&n; *&n; * OPTCD_TIMER&t;&t;Optics Storage CD-ROM Timer&n; *&n; */
DECL|macro|BLANK_TIMER
mdefine_line|#define BLANK_TIMER&t;0
DECL|macro|BEEP_TIMER
mdefine_line|#define BEEP_TIMER&t;1
DECL|macro|RS_TIMER
mdefine_line|#define RS_TIMER&t;2
DECL|macro|HD_TIMER
mdefine_line|#define HD_TIMER&t;16
DECL|macro|FLOPPY_TIMER
mdefine_line|#define FLOPPY_TIMER&t;17
DECL|macro|SCSI_TIMER
mdefine_line|#define SCSI_TIMER &t;18
DECL|macro|NET_TIMER
mdefine_line|#define NET_TIMER&t;19
DECL|macro|SOUND_TIMER
mdefine_line|#define SOUND_TIMER&t;20
DECL|macro|COPRO_TIMER
mdefine_line|#define COPRO_TIMER&t;21
DECL|macro|QIC02_TAPE_TIMER
mdefine_line|#define QIC02_TAPE_TIMER&t;22&t;/* hhb */
DECL|macro|MCD_TIMER
mdefine_line|#define MCD_TIMER&t;23
DECL|macro|HD_TIMER2
mdefine_line|#define HD_TIMER2&t;24
DECL|macro|GSCD_TIMER
mdefine_line|#define GSCD_TIMER&t;25
DECL|macro|OPTCD_TIMER
mdefine_line|#define OPTCD_TIMER&t;26
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
multiline_comment|/*&n; * This is completely separate from the above, and is the&n; * &quot;new and improved&quot; way of handling timers more dynamically.&n; * Hopefully efficient and general enough for most things.&n; *&n; * The &quot;hardcoded&quot; timers above are still useful for well-&n; * defined problems, but the timer-list is probably better&n; * when you need multiple outstanding timers or similar.&n; *&n; * The &quot;data&quot; field is in case you want to use the same&n; * timeout function for several timeouts. You can use this&n; * to distinguish between the different invocations.&n; */
DECL|struct|timer_list
r_struct
id|timer_list
(brace
DECL|member|next
r_struct
id|timer_list
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|timer_list
op_star
id|prev
suffix:semicolon
DECL|member|expires
r_int
r_int
id|expires
suffix:semicolon
DECL|member|data
r_int
r_int
id|data
suffix:semicolon
DECL|member|function
r_void
(paren
op_star
id|function
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|add_timer
c_func
(paren
r_struct
id|timer_list
op_star
id|timer
)paren
suffix:semicolon
r_extern
r_int
id|del_timer
c_func
(paren
r_struct
id|timer_list
op_star
id|timer
)paren
suffix:semicolon
r_extern
r_void
id|it_real_fn
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|function|init_timer
r_extern
r_inline
r_void
id|init_timer
c_func
(paren
r_struct
id|timer_list
op_star
id|timer
)paren
(brace
id|timer-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|timer-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
eof
