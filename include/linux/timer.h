macro_line|#ifndef _LINUX_TIMER_H
DECL|macro|_LINUX_TIMER_H
mdefine_line|#define _LINUX_TIMER_H
multiline_comment|/*&n; * Old-style timers. Please don&squot;t use for any new code.&n; *&n; * Numbering of these timers should be consecutive to minimize&n; * processing delays. [MJ]&n; */
DECL|macro|BLANK_TIMER
mdefine_line|#define BLANK_TIMER&t;0&t;/* Console screen-saver */
DECL|macro|BEEP_TIMER
mdefine_line|#define BEEP_TIMER&t;1&t;/* Console beep */
DECL|macro|RS_TIMER
mdefine_line|#define RS_TIMER&t;2&t;/* RS-232 ports */
DECL|macro|SWAP_TIMER
mdefine_line|#define SWAP_TIMER&t;3&t;/* Background pageout */
DECL|macro|BACKGR_TIMER
mdefine_line|#define BACKGR_TIMER    4&t;/* io_request background I/O */
DECL|macro|HD_TIMER
mdefine_line|#define HD_TIMER&t;5&t;/* Old IDE driver */
DECL|macro|FLOPPY_TIMER
mdefine_line|#define FLOPPY_TIMER&t;6&t;/* Floppy */
DECL|macro|QIC02_TAPE_TIMER
mdefine_line|#define QIC02_TAPE_TIMER 7&t;/* QIC 02 tape */
DECL|macro|MCD_TIMER
mdefine_line|#define MCD_TIMER&t;8&t;/* Mitsumi CDROM */
DECL|macro|GSCD_TIMER
mdefine_line|#define GSCD_TIMER&t;9&t;/* Goldstar CDROM */
DECL|macro|COMTROL_TIMER
mdefine_line|#define COMTROL_TIMER&t;10&t;/* Comtrol serial */
DECL|macro|DIGI_TIMER
mdefine_line|#define DIGI_TIMER&t;11&t;/* Digi serial */
DECL|macro|GDTH_TIMER
mdefine_line|#define GDTH_TIMER&t;12&t;/* Ugh - gdth scsi driver */
DECL|macro|COPRO_TIMER
mdefine_line|#define COPRO_TIMER&t;31&t;/* 387 timeout for buggy hardware (boot only) */
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
