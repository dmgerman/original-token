multiline_comment|/*&n; *  linux/kernel/floppy.c&n; *&n; *  (C) 1991  Linus Torvalds&n; */
multiline_comment|/*&n; * 02.12.91 - Changed to static variables to indicate need for reset&n; * and recalibrate. This makes some things easier (output_byte reset&n; * checking etc), and means less interrupt jumping in case of errors,&n; * so the code is hopefully easier to understand.&n; */
multiline_comment|/*&n; * This file is certainly a mess. I&squot;ve tried my best to get it working,&n; * but I don&squot;t like programming floppies, and I have only one anyway.&n; * Urgel. I should check for more errors, and do more graceful error&n; * recovery. Seems there are problems with several drives. I&squot;ve tried to&n; * correct them. No promises. &n; */
multiline_comment|/*&n; * As with hd.c, all routines within this file can (and will) be called&n; * by interrupts, so extreme caution is needed. A hardware interrupt&n; * handler may not sleep, or a kernel panic will happen. Thus I cannot&n; * call &quot;floppy-on&quot; directly, but have to set a special timer interrupt&n; * etc.&n; *&n; * Also, I&squot;m not certain this works on more than 1 floppy. Bugs may&n; * abund.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fdreg.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR 2
macro_line|#include &quot;blk.h&quot;
DECL|variable|recalibrate
r_static
r_int
id|recalibrate
op_assign
l_int|0
suffix:semicolon
DECL|variable|reset
r_static
r_int
id|reset
op_assign
l_int|0
suffix:semicolon
DECL|variable|seek
r_static
r_int
id|seek
op_assign
l_int|0
suffix:semicolon
r_extern
r_int
r_char
id|current_DOR
suffix:semicolon
DECL|macro|immoutb_p
mdefine_line|#define immoutb_p(val,port) &bslash;&n;__asm__(&quot;outb %0,%1&bslash;n&bslash;tjmp 1f&bslash;n1:&bslash;tjmp 1f&bslash;n1:&quot;::&quot;a&quot; ((char) (val)),&quot;i&quot; (port))
DECL|macro|TYPE
mdefine_line|#define TYPE(x) ((x)&gt;&gt;2)
DECL|macro|DRIVE
mdefine_line|#define DRIVE(x) ((x)&amp;0x03)
multiline_comment|/*&n; * Note that MAX_ERRORS=8 doesn&squot;t imply that we retry every bad read&n; * max 8 times - some types of errors increase the errorcount by 2,&n; * so we might actually retry only 5-6 times before giving up.&n; */
DECL|macro|MAX_ERRORS
mdefine_line|#define MAX_ERRORS 8
multiline_comment|/*&n; * globals used by &squot;result()&squot;&n; */
DECL|macro|MAX_REPLIES
mdefine_line|#define MAX_REPLIES 7
DECL|variable|reply_buffer
r_static
r_int
r_char
id|reply_buffer
(braket
id|MAX_REPLIES
)braket
suffix:semicolon
DECL|macro|ST0
mdefine_line|#define ST0 (reply_buffer[0])
DECL|macro|ST1
mdefine_line|#define ST1 (reply_buffer[1])
DECL|macro|ST2
mdefine_line|#define ST2 (reply_buffer[2])
DECL|macro|ST3
mdefine_line|#define ST3 (reply_buffer[3])
multiline_comment|/*&n; * This struct defines the different floppy types. Unlike minix&n; * linux doesn&squot;t have a &quot;search for right type&quot;-type, as the code&n; * for that is convoluted and weird. I&squot;ve got enough problems with&n; * this driver as it is.&n; *&n; * The &squot;stretch&squot; tells if the tracks need to be boubled for some&n; * types (ie 360kB diskette in 1.2MB drive etc). Others should&n; * be self-explanatory.&n; */
DECL|struct|floppy_struct
r_static
r_struct
id|floppy_struct
(brace
DECL|member|size
DECL|member|sect
DECL|member|head
DECL|member|track
DECL|member|stretch
r_int
r_int
id|size
comma
id|sect
comma
id|head
comma
id|track
comma
id|stretch
suffix:semicolon
DECL|member|gap
DECL|member|rate
DECL|member|spec1
r_int
r_char
id|gap
comma
id|rate
comma
id|spec1
suffix:semicolon
DECL|variable|floppy_type
)brace
id|floppy_type
(braket
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
multiline_comment|/* no testing */
(brace
l_int|720
comma
l_int|9
comma
l_int|2
comma
l_int|40
comma
l_int|0
comma
l_int|0x2A
comma
l_int|0x02
comma
l_int|0xDF
)brace
comma
multiline_comment|/* 360kB PC diskettes */
(brace
l_int|2400
comma
l_int|15
comma
l_int|2
comma
l_int|80
comma
l_int|0
comma
l_int|0x1B
comma
l_int|0x00
comma
l_int|0xDF
)brace
comma
multiline_comment|/* 1.2 MB AT-diskettes */
(brace
l_int|720
comma
l_int|9
comma
l_int|2
comma
l_int|40
comma
l_int|1
comma
l_int|0x2A
comma
l_int|0x02
comma
l_int|0xDF
)brace
comma
multiline_comment|/* 360kB in 720kB drive */
(brace
l_int|1440
comma
l_int|9
comma
l_int|2
comma
l_int|80
comma
l_int|0
comma
l_int|0x2A
comma
l_int|0x02
comma
l_int|0xDF
)brace
comma
multiline_comment|/* 3.5&quot; 720kB diskette */
(brace
l_int|720
comma
l_int|9
comma
l_int|2
comma
l_int|40
comma
l_int|1
comma
l_int|0x23
comma
l_int|0x01
comma
l_int|0xDF
)brace
comma
multiline_comment|/* 360kB in 1.2MB drive */
(brace
l_int|1440
comma
l_int|9
comma
l_int|2
comma
l_int|80
comma
l_int|0
comma
l_int|0x23
comma
l_int|0x01
comma
l_int|0xDF
)brace
comma
multiline_comment|/* 720kB in 1.2MB drive */
(brace
l_int|2880
comma
l_int|18
comma
l_int|2
comma
l_int|80
comma
l_int|0
comma
l_int|0x1B
comma
l_int|0x00
comma
l_int|0xCF
)brace
comma
multiline_comment|/* 1.44MB diskette */
)brace
suffix:semicolon
multiline_comment|/*&n; * Rate is 0 for 500kb/s, 2 for 300kbps, 1 for 250kbps&n; * Spec1 is 0xSH, where S is stepping rate (F=1ms, E=2ms, D=3ms etc),&n; * H is head unload time (1=16ms, 2=32ms, etc)&n; *&n; * Spec2 is (HLD&lt;&lt;1 | ND), where HLD is head load time (1=2ms, 2=4 ms etc)&n; * and ND is set means no DMA. Hardcoded to 6 (HLD=6ms, use DMA).&n; */
r_extern
r_void
id|floppy_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_char
id|tmp_floppy_area
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/*&n; * These are global variables, as that&squot;s the easiest way to give&n; * information to interrupts. They are the data used for the current&n; * request.&n; */
DECL|variable|cur_spec1
r_static
r_int
id|cur_spec1
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|cur_rate
r_static
r_int
id|cur_rate
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|floppy
r_static
r_struct
id|floppy_struct
op_star
id|floppy
op_assign
id|floppy_type
suffix:semicolon
DECL|variable|current_drive
r_static
r_int
r_char
id|current_drive
op_assign
l_int|0
suffix:semicolon
DECL|variable|sector
r_static
r_int
r_char
id|sector
op_assign
l_int|0
suffix:semicolon
DECL|variable|head
r_static
r_int
r_char
id|head
op_assign
l_int|0
suffix:semicolon
DECL|variable|track
r_static
r_int
r_char
id|track
op_assign
l_int|0
suffix:semicolon
DECL|variable|seek_track
r_static
r_int
r_char
id|seek_track
op_assign
l_int|0
suffix:semicolon
DECL|variable|current_track
r_static
r_int
r_char
id|current_track
op_assign
l_int|255
suffix:semicolon
DECL|variable|command
r_static
r_int
r_char
id|command
op_assign
l_int|0
suffix:semicolon
DECL|variable|selected
r_int
r_char
id|selected
op_assign
l_int|0
suffix:semicolon
DECL|variable|wait_on_floppy_select
r_struct
id|task_struct
op_star
id|wait_on_floppy_select
op_assign
l_int|NULL
suffix:semicolon
DECL|function|floppy_deselect
r_void
id|floppy_deselect
c_func
(paren
r_int
r_int
id|nr
)paren
(brace
r_if
c_cond
(paren
id|nr
op_ne
(paren
id|current_DOR
op_amp
l_int|3
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;floppy_deselect: drive not selected&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
id|selected
op_assign
l_int|0
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|wait_on_floppy_select
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * floppy-change is never called from an interrupt, so we can relax a bit&n; * here, sleep etc. Note that floppy-on tries to set current_DOR to point&n; * to the desired drive, but it will probably not survive the sleep if&n; * several floppies are used at the same time: thus the loop.&n; */
DECL|function|floppy_change
r_int
id|floppy_change
c_func
(paren
r_int
r_int
id|nr
)paren
(brace
id|repeat
suffix:colon
id|floppy_on
c_func
(paren
id|nr
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|current_DOR
op_amp
l_int|3
)paren
op_ne
id|nr
op_logical_and
id|selected
)paren
id|sleep_on
c_func
(paren
op_amp
id|wait_on_floppy_select
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current_DOR
op_amp
l_int|3
)paren
op_ne
id|nr
)paren
r_goto
id|repeat
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|FD_DIR
)paren
op_amp
l_int|0x80
)paren
(brace
id|floppy_off
c_func
(paren
id|nr
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|floppy_off
c_func
(paren
id|nr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|copy_buffer
mdefine_line|#define copy_buffer(from,to) &bslash;&n;__asm__(&quot;cld ; rep ; movsl&quot; &bslash;&n;&t;::&quot;c&quot; (BLOCK_SIZE/4),&quot;S&quot; ((long)(from)),&quot;D&quot; ((long)(to)) &bslash;&n;&t;:&quot;cx&quot;,&quot;di&quot;,&quot;si&quot;)
DECL|function|setup_DMA
r_static
r_void
id|setup_DMA
c_func
(paren
r_void
)paren
(brace
r_int
id|addr
op_assign
(paren
r_int
)paren
id|CURRENT-&gt;buffer
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
l_int|0x100000
)paren
(brace
id|addr
op_assign
(paren
r_int
)paren
id|tmp_floppy_area
suffix:semicolon
r_if
c_cond
(paren
id|command
op_eq
id|FD_WRITE
)paren
id|copy_buffer
c_func
(paren
id|CURRENT-&gt;buffer
comma
id|tmp_floppy_area
)paren
suffix:semicolon
)brace
multiline_comment|/* mask DMA 2 */
id|immoutb_p
c_func
(paren
l_int|4
op_or
l_int|2
comma
l_int|10
)paren
suffix:semicolon
multiline_comment|/* output command byte. I don&squot;t know why, but everyone (minix, */
multiline_comment|/* sanches &amp; canton) output this twice, first to 12 then to 11 */
id|__asm__
c_func
(paren
l_string|&quot;outb %%al,$12&bslash;n&bslash;tjmp 1f&bslash;n1:&bslash;tjmp 1f&bslash;n1:&bslash;t&quot;
l_string|&quot;outb %%al,$11&bslash;n&bslash;tjmp 1f&bslash;n1:&bslash;tjmp 1f&bslash;n1:&quot;
op_scope_resolution
l_string|&quot;a&quot;
(paren
(paren
r_char
)paren
(paren
(paren
id|command
op_eq
id|FD_READ
)paren
ques
c_cond
id|DMA_READ
suffix:colon
id|DMA_WRITE
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* 8 low bits of addr */
id|immoutb_p
c_func
(paren
id|addr
comma
l_int|4
)paren
suffix:semicolon
id|addr
op_rshift_assign
l_int|8
suffix:semicolon
multiline_comment|/* bits 8-15 of addr */
id|immoutb_p
c_func
(paren
id|addr
comma
l_int|4
)paren
suffix:semicolon
id|addr
op_rshift_assign
l_int|8
suffix:semicolon
multiline_comment|/* bits 16-19 of addr */
id|immoutb_p
c_func
(paren
id|addr
comma
l_int|0x81
)paren
suffix:semicolon
multiline_comment|/* low 8 bits of count-1 (1024-1=0x3ff) */
id|immoutb_p
c_func
(paren
l_int|0xff
comma
l_int|5
)paren
suffix:semicolon
multiline_comment|/* high 8 bits of count-1 */
id|immoutb_p
c_func
(paren
l_int|3
comma
l_int|5
)paren
suffix:semicolon
multiline_comment|/* activate DMA 2 */
id|immoutb_p
c_func
(paren
l_int|0
op_or
l_int|2
comma
l_int|10
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|output_byte
r_static
r_void
id|output_byte
c_func
(paren
r_char
id|byte
)paren
(brace
r_int
id|counter
suffix:semicolon
r_int
r_char
id|status
suffix:semicolon
r_if
c_cond
(paren
id|reset
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|counter
op_assign
l_int|0
suffix:semicolon
id|counter
OL
l_int|10000
suffix:semicolon
id|counter
op_increment
)paren
(brace
id|status
op_assign
id|inb_p
c_func
(paren
id|FD_STATUS
)paren
op_amp
(paren
id|STATUS_READY
op_or
id|STATUS_DIR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|STATUS_READY
)paren
(brace
id|outb
c_func
(paren
id|byte
comma
id|FD_DATA
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|reset
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Unable to send byte to FDC&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
)brace
DECL|function|result
r_static
r_int
id|result
c_func
(paren
r_void
)paren
(brace
r_int
id|i
op_assign
l_int|0
comma
id|counter
comma
id|status
suffix:semicolon
r_if
c_cond
(paren
id|reset
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|counter
op_assign
l_int|0
suffix:semicolon
id|counter
OL
l_int|10000
suffix:semicolon
id|counter
op_increment
)paren
(brace
id|status
op_assign
id|inb_p
c_func
(paren
id|FD_STATUS
)paren
op_amp
(paren
id|STATUS_DIR
op_or
id|STATUS_READY
op_or
id|STATUS_BUSY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|STATUS_READY
)paren
r_return
id|i
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
(paren
id|STATUS_DIR
op_or
id|STATUS_READY
op_or
id|STATUS_BUSY
)paren
)paren
(brace
r_if
c_cond
(paren
id|i
op_ge
id|MAX_REPLIES
)paren
r_break
suffix:semicolon
id|reply_buffer
(braket
id|i
op_increment
)braket
op_assign
id|inb_p
c_func
(paren
id|FD_DATA
)paren
suffix:semicolon
)brace
)brace
id|reset
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Getstatus times out&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|bad_flp_intr
r_static
r_void
id|bad_flp_intr
c_func
(paren
r_void
)paren
(brace
id|CURRENT-&gt;errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|CURRENT-&gt;errors
OG
id|MAX_ERRORS
)paren
(brace
id|floppy_deselect
c_func
(paren
id|current_drive
)paren
suffix:semicolon
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|CURRENT-&gt;errors
OG
id|MAX_ERRORS
op_div
l_int|2
)paren
id|reset
op_assign
l_int|1
suffix:semicolon
r_else
id|recalibrate
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Ok, this interrupt is called after a DMA read/write has succeeded,&n; * so we check the results, and copy any buffers.&n; */
DECL|function|rw_interrupt
r_static
r_void
id|rw_interrupt
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|result
c_func
(paren
)paren
op_ne
l_int|7
op_logical_or
(paren
id|ST0
op_amp
l_int|0xf8
)paren
op_logical_or
(paren
id|ST1
op_amp
l_int|0xbf
)paren
op_logical_or
(paren
id|ST2
op_amp
l_int|0x73
)paren
)paren
(brace
r_if
c_cond
(paren
id|ST1
op_amp
l_int|0x02
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Drive %d is write protected&bslash;n&bslash;r&quot;
comma
id|current_drive
)paren
suffix:semicolon
id|floppy_deselect
c_func
(paren
id|current_drive
)paren
suffix:semicolon
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
id|bad_flp_intr
c_func
(paren
)paren
suffix:semicolon
id|do_fd_request
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|command
op_eq
id|FD_READ
op_logical_and
(paren
r_int
r_int
)paren
(paren
id|CURRENT-&gt;buffer
)paren
op_ge
l_int|0x100000
)paren
id|copy_buffer
c_func
(paren
id|tmp_floppy_area
comma
id|CURRENT-&gt;buffer
)paren
suffix:semicolon
id|floppy_deselect
c_func
(paren
id|current_drive
)paren
suffix:semicolon
id|end_request
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|do_fd_request
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|setup_rw_floppy
r_inline
r_void
id|setup_rw_floppy
c_func
(paren
r_void
)paren
(brace
id|setup_DMA
c_func
(paren
)paren
suffix:semicolon
id|do_floppy
op_assign
id|rw_interrupt
suffix:semicolon
id|output_byte
c_func
(paren
id|command
)paren
suffix:semicolon
id|output_byte
c_func
(paren
id|head
op_lshift
l_int|2
op_or
id|current_drive
)paren
suffix:semicolon
id|output_byte
c_func
(paren
id|track
)paren
suffix:semicolon
id|output_byte
c_func
(paren
id|head
)paren
suffix:semicolon
id|output_byte
c_func
(paren
id|sector
)paren
suffix:semicolon
id|output_byte
c_func
(paren
l_int|2
)paren
suffix:semicolon
multiline_comment|/* sector size = 512 */
id|output_byte
c_func
(paren
id|floppy-&gt;sect
)paren
suffix:semicolon
id|output_byte
c_func
(paren
id|floppy-&gt;gap
)paren
suffix:semicolon
id|output_byte
c_func
(paren
l_int|0xFF
)paren
suffix:semicolon
multiline_comment|/* sector size (0xff when n!=0 ?) */
r_if
c_cond
(paren
id|reset
)paren
id|do_fd_request
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the routine called after every seek (or recalibrate) interrupt&n; * from the floppy controller. Note that the &quot;unexpected interrupt&quot; routine&n; * also does a recalibrate, but doesn&squot;t come here.&n; */
DECL|function|seek_interrupt
r_static
r_void
id|seek_interrupt
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* sense drive status */
id|output_byte
c_func
(paren
id|FD_SENSEI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
c_func
(paren
)paren
op_ne
l_int|2
op_logical_or
(paren
id|ST0
op_amp
l_int|0xF8
)paren
op_ne
l_int|0x20
op_logical_or
id|ST1
op_ne
id|seek_track
)paren
(brace
id|bad_flp_intr
c_func
(paren
)paren
suffix:semicolon
id|do_fd_request
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|current_track
op_assign
id|ST1
suffix:semicolon
id|setup_rw_floppy
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This routine is called when everything should be correctly set up&n; * for the transfer (ie floppy motor is on and the correct floppy is&n; * selected).&n; */
DECL|function|transfer
r_static
r_void
id|transfer
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|cur_spec1
op_ne
id|floppy-&gt;spec1
)paren
(brace
id|cur_spec1
op_assign
id|floppy-&gt;spec1
suffix:semicolon
id|output_byte
c_func
(paren
id|FD_SPECIFY
)paren
suffix:semicolon
id|output_byte
c_func
(paren
id|cur_spec1
)paren
suffix:semicolon
multiline_comment|/* hut etc */
id|output_byte
c_func
(paren
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Head load time =6ms, DMA */
)brace
r_if
c_cond
(paren
id|cur_rate
op_ne
id|floppy-&gt;rate
)paren
id|outb_p
c_func
(paren
id|cur_rate
op_assign
id|floppy-&gt;rate
comma
id|FD_DCR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reset
)paren
(brace
id|do_fd_request
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|seek
)paren
(brace
id|setup_rw_floppy
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|do_floppy
op_assign
id|seek_interrupt
suffix:semicolon
r_if
c_cond
(paren
id|seek_track
)paren
(brace
id|output_byte
c_func
(paren
id|FD_SEEK
)paren
suffix:semicolon
id|output_byte
c_func
(paren
id|head
op_lshift
l_int|2
op_or
id|current_drive
)paren
suffix:semicolon
id|output_byte
c_func
(paren
id|seek_track
)paren
suffix:semicolon
)brace
r_else
(brace
id|output_byte
c_func
(paren
id|FD_RECALIBRATE
)paren
suffix:semicolon
id|output_byte
c_func
(paren
id|head
op_lshift
l_int|2
op_or
id|current_drive
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|reset
)paren
id|do_fd_request
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Special case - used after a unexpected interrupt (or reset)&n; */
DECL|function|recal_interrupt
r_static
r_void
id|recal_interrupt
c_func
(paren
r_void
)paren
(brace
id|output_byte
c_func
(paren
id|FD_SENSEI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
c_func
(paren
)paren
op_ne
l_int|2
op_logical_or
(paren
id|ST0
op_amp
l_int|0xE0
)paren
op_eq
l_int|0x60
)paren
id|reset
op_assign
l_int|1
suffix:semicolon
r_else
id|recalibrate
op_assign
l_int|0
suffix:semicolon
id|do_fd_request
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|unexpected_floppy_interrupt
r_void
id|unexpected_floppy_interrupt
c_func
(paren
r_void
)paren
(brace
id|output_byte
c_func
(paren
id|FD_SENSEI
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
c_func
(paren
)paren
op_ne
l_int|2
op_logical_or
(paren
id|ST0
op_amp
l_int|0xE0
)paren
op_eq
l_int|0x60
)paren
id|reset
op_assign
l_int|1
suffix:semicolon
r_else
id|recalibrate
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|recalibrate_floppy
r_static
r_void
id|recalibrate_floppy
c_func
(paren
r_void
)paren
(brace
id|recalibrate
op_assign
l_int|0
suffix:semicolon
id|current_track
op_assign
l_int|0
suffix:semicolon
id|do_floppy
op_assign
id|recal_interrupt
suffix:semicolon
id|output_byte
c_func
(paren
id|FD_RECALIBRATE
)paren
suffix:semicolon
id|output_byte
c_func
(paren
id|head
op_lshift
l_int|2
op_or
id|current_drive
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reset
)paren
id|do_fd_request
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|reset_interrupt
r_static
r_void
id|reset_interrupt
c_func
(paren
r_void
)paren
(brace
id|output_byte
c_func
(paren
id|FD_SENSEI
)paren
suffix:semicolon
(paren
r_void
)paren
id|result
c_func
(paren
)paren
suffix:semicolon
id|output_byte
c_func
(paren
id|FD_SPECIFY
)paren
suffix:semicolon
id|output_byte
c_func
(paren
id|cur_spec1
)paren
suffix:semicolon
multiline_comment|/* hut etc */
id|output_byte
c_func
(paren
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Head load time =6ms, DMA */
id|do_fd_request
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * reset is done by pulling bit 2 of DOR low for a while.&n; */
DECL|function|reset_floppy
r_static
r_void
id|reset_floppy
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|reset
op_assign
l_int|0
suffix:semicolon
id|cur_spec1
op_assign
op_minus
l_int|1
suffix:semicolon
id|cur_rate
op_assign
op_minus
l_int|1
suffix:semicolon
id|recalibrate
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Reset-floppy called&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|do_floppy
op_assign
id|reset_interrupt
suffix:semicolon
id|outb_p
c_func
(paren
id|current_DOR
op_amp
op_complement
l_int|0x04
comma
id|FD_DOR
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
l_int|100
suffix:semicolon
id|i
op_increment
)paren
id|__asm__
c_func
(paren
l_string|&quot;nop&quot;
)paren
suffix:semicolon
id|outb
c_func
(paren
id|current_DOR
comma
id|FD_DOR
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|floppy_on_interrupt
r_static
r_void
id|floppy_on_interrupt
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* We cannot do a floppy-select, as that might sleep. We just force it */
id|selected
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|current_drive
op_ne
(paren
id|current_DOR
op_amp
l_int|3
)paren
)paren
(brace
id|current_DOR
op_and_assign
l_int|0xFC
suffix:semicolon
id|current_DOR
op_or_assign
id|current_drive
suffix:semicolon
id|outb
c_func
(paren
id|current_DOR
comma
id|FD_DOR
)paren
suffix:semicolon
id|add_timer
c_func
(paren
l_int|2
comma
op_amp
id|transfer
)paren
suffix:semicolon
)brace
r_else
id|transfer
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|do_fd_request
r_void
id|do_fd_request
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|block
suffix:semicolon
id|seek
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|reset
)paren
(brace
id|reset_floppy
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|recalibrate
)paren
(brace
id|recalibrate_floppy
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|INIT_REQUEST
suffix:semicolon
id|floppy
op_assign
(paren
id|MINOR
c_func
(paren
id|CURRENT-&gt;dev
)paren
op_rshift
l_int|2
)paren
op_plus
id|floppy_type
suffix:semicolon
r_if
c_cond
(paren
id|current_drive
op_ne
id|CURRENT_DEV
)paren
id|seek
op_assign
l_int|1
suffix:semicolon
id|current_drive
op_assign
id|CURRENT_DEV
suffix:semicolon
id|block
op_assign
id|CURRENT-&gt;sector
suffix:semicolon
r_if
c_cond
(paren
id|block
op_plus
l_int|2
OG
id|floppy-&gt;size
)paren
(brace
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|sector
op_assign
id|block
op_mod
id|floppy-&gt;sect
suffix:semicolon
id|block
op_div_assign
id|floppy-&gt;sect
suffix:semicolon
id|head
op_assign
id|block
op_mod
id|floppy-&gt;head
suffix:semicolon
id|track
op_assign
id|block
op_div
id|floppy-&gt;head
suffix:semicolon
id|seek_track
op_assign
id|track
op_lshift
id|floppy-&gt;stretch
suffix:semicolon
r_if
c_cond
(paren
id|seek_track
op_ne
id|current_track
)paren
id|seek
op_assign
l_int|1
suffix:semicolon
id|sector
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|CURRENT-&gt;cmd
op_eq
id|READ
)paren
id|command
op_assign
id|FD_READ
suffix:semicolon
r_else
r_if
c_cond
(paren
id|CURRENT-&gt;cmd
op_eq
id|WRITE
)paren
id|command
op_assign
id|FD_WRITE
suffix:semicolon
r_else
id|panic
c_func
(paren
l_string|&quot;do_fd_request: unknown command&quot;
)paren
suffix:semicolon
id|add_timer
c_func
(paren
id|ticks_to_floppy_on
c_func
(paren
id|current_drive
)paren
comma
op_amp
id|floppy_on_interrupt
)paren
suffix:semicolon
)brace
DECL|variable|floppy_sizes
r_static
r_int
id|floppy_sizes
(braket
)braket
op_assign
initialization_block
suffix:semicolon
DECL|function|floppy_init
r_void
id|floppy_init
c_func
(paren
r_void
)paren
(brace
id|blk_size
(braket
id|MAJOR_NR
)braket
op_assign
id|floppy_sizes
suffix:semicolon
id|blk_dev
(braket
id|MAJOR_NR
)braket
dot
id|request_fn
op_assign
id|DEVICE_REQUEST
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|0x26
comma
op_amp
id|floppy_interrupt
)paren
suffix:semicolon
id|outb
c_func
(paren
id|inb_p
c_func
(paren
l_int|0x21
)paren
op_amp
op_complement
l_int|0x40
comma
l_int|0x21
)paren
suffix:semicolon
)brace
eof
