multiline_comment|/*&n; * sound/sys_timer.c&n; *&n; * The default timer for the Level 2 sequencer interface&n; * Uses the (1/HZ sec) timer of kernel.&n; */
multiline_comment|/*&n; * Copyright (C) by Hannu Savolainen 1993-1997&n; *&n; * OSS/Free for Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.&n; */
multiline_comment|/*&n; * Thomas Sailer   : ioctl code reworked (vmalloc/vfree removed)&n; * Andrew Veliath  : adapted tmr2ticks from level 1 sequencer (avoid overflow)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;sound_config.h&quot;
macro_line|#ifdef CONFIG_SEQUENCER
DECL|variable|opened
DECL|variable|tmr_running
r_static
r_volatile
r_int
id|opened
op_assign
l_int|0
comma
id|tmr_running
op_assign
l_int|0
suffix:semicolon
DECL|variable|tmr_offs
DECL|variable|tmr_ctr
r_static
r_volatile
id|time_t
id|tmr_offs
comma
id|tmr_ctr
suffix:semicolon
DECL|variable|ticks_offs
r_static
r_volatile
r_int
r_int
id|ticks_offs
suffix:semicolon
DECL|variable|curr_tempo
DECL|variable|curr_timebase
r_static
r_volatile
r_int
id|curr_tempo
comma
id|curr_timebase
suffix:semicolon
DECL|variable|curr_ticks
r_static
r_volatile
r_int
r_int
id|curr_ticks
suffix:semicolon
DECL|variable|next_event_time
r_static
r_volatile
r_int
r_int
id|next_event_time
suffix:semicolon
DECL|variable|prev_event_time
r_static
r_int
r_int
id|prev_event_time
suffix:semicolon
r_static
r_void
id|poll_def_tmr
c_func
(paren
r_int
r_int
id|dummy
)paren
suffix:semicolon
DECL|variable|def_tmr
r_static
r_struct
id|timer_list
id|def_tmr
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
id|poll_def_tmr
)brace
suffix:semicolon
r_static
r_int
r_int
DECL|function|tmr2ticks
id|tmr2ticks
c_func
(paren
r_int
id|tmr_value
)paren
(brace
multiline_comment|/*&n;&t; *    Convert timer ticks to MIDI ticks&n;&t; */
r_int
r_int
id|tmp
suffix:semicolon
r_int
r_int
id|scale
suffix:semicolon
multiline_comment|/* tmr_value (ticks per sec) *&n;&t;   1000000 (usecs per sec) / HZ (ticks per sec) -=&gt; usecs */
id|tmp
op_assign
id|tmr_value
op_star
(paren
l_int|1000000
op_div
id|HZ
)paren
suffix:semicolon
id|scale
op_assign
(paren
l_int|60
op_star
l_int|1000000
)paren
op_div
(paren
id|curr_tempo
op_star
id|curr_timebase
)paren
suffix:semicolon
multiline_comment|/* usecs per MIDI tick */
r_return
(paren
id|tmp
op_plus
id|scale
op_div
l_int|2
)paren
op_div
id|scale
suffix:semicolon
)brace
r_static
r_void
DECL|function|poll_def_tmr
id|poll_def_tmr
c_func
(paren
r_int
r_int
id|dummy
)paren
(brace
r_if
c_cond
(paren
id|opened
)paren
(brace
(brace
id|def_tmr.expires
op_assign
(paren
l_int|1
)paren
op_plus
id|jiffies
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|def_tmr
)paren
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
id|tmr_running
)paren
(brace
id|tmr_ctr
op_increment
suffix:semicolon
id|curr_ticks
op_assign
id|ticks_offs
op_plus
id|tmr2ticks
c_func
(paren
id|tmr_ctr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|curr_ticks
op_ge
id|next_event_time
)paren
(brace
id|next_event_time
op_assign
(paren
r_int
r_int
)paren
op_minus
l_int|1
suffix:semicolon
id|sequencer_timer
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
r_static
r_void
DECL|function|tmr_reset
id|tmr_reset
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|tmr_offs
op_assign
l_int|0
suffix:semicolon
id|ticks_offs
op_assign
l_int|0
suffix:semicolon
id|tmr_ctr
op_assign
l_int|0
suffix:semicolon
id|next_event_time
op_assign
(paren
r_int
r_int
)paren
op_minus
l_int|1
suffix:semicolon
id|prev_event_time
op_assign
l_int|0
suffix:semicolon
id|curr_ticks
op_assign
l_int|0
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|def_tmr_open
id|def_tmr_open
c_func
(paren
r_int
id|dev
comma
r_int
id|mode
)paren
(brace
r_if
c_cond
(paren
id|opened
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|tmr_reset
c_func
(paren
)paren
suffix:semicolon
id|curr_tempo
op_assign
l_int|60
suffix:semicolon
id|curr_timebase
op_assign
l_int|100
suffix:semicolon
id|opened
op_assign
l_int|1
suffix:semicolon
suffix:semicolon
(brace
id|def_tmr.expires
op_assign
(paren
l_int|1
)paren
op_plus
id|jiffies
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|def_tmr
)paren
suffix:semicolon
)brace
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|def_tmr_close
id|def_tmr_close
c_func
(paren
r_int
id|dev
)paren
(brace
id|opened
op_assign
id|tmr_running
op_assign
l_int|0
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|def_tmr
)paren
suffix:semicolon
suffix:semicolon
)brace
r_static
r_int
DECL|function|def_tmr_event
id|def_tmr_event
c_func
(paren
r_int
id|dev
comma
r_int
r_char
op_star
id|event
)paren
(brace
r_int
r_char
id|cmd
op_assign
id|event
(braket
l_int|1
)braket
suffix:semicolon
r_int
r_int
id|parm
op_assign
op_star
(paren
r_int
op_star
)paren
op_amp
id|event
(braket
l_int|4
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|TMR_WAIT_REL
suffix:colon
id|parm
op_add_assign
id|prev_event_time
suffix:semicolon
r_case
id|TMR_WAIT_ABS
suffix:colon
r_if
c_cond
(paren
id|parm
OG
l_int|0
)paren
(brace
r_int
id|time
suffix:semicolon
r_if
c_cond
(paren
id|parm
op_le
id|curr_ticks
)paren
multiline_comment|/* It&squot;s the time */
r_return
id|TIMER_NOT_ARMED
suffix:semicolon
id|time
op_assign
id|parm
suffix:semicolon
id|next_event_time
op_assign
id|prev_event_time
op_assign
id|time
suffix:semicolon
r_return
id|TIMER_ARMED
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|TMR_START
suffix:colon
id|tmr_reset
c_func
(paren
)paren
suffix:semicolon
id|tmr_running
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TMR_STOP
suffix:colon
id|tmr_running
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TMR_CONTINUE
suffix:colon
id|tmr_running
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TMR_TEMPO
suffix:colon
r_if
c_cond
(paren
id|parm
)paren
(brace
r_if
c_cond
(paren
id|parm
OL
l_int|8
)paren
id|parm
op_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|parm
OG
l_int|360
)paren
id|parm
op_assign
l_int|360
suffix:semicolon
id|tmr_offs
op_assign
id|tmr_ctr
suffix:semicolon
id|ticks_offs
op_add_assign
id|tmr2ticks
c_func
(paren
id|tmr_ctr
)paren
suffix:semicolon
id|tmr_ctr
op_assign
l_int|0
suffix:semicolon
id|curr_tempo
op_assign
id|parm
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|TMR_ECHO
suffix:colon
id|seq_copy_to_input
c_func
(paren
id|event
comma
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
suffix:semicolon
)brace
r_return
id|TIMER_NOT_ARMED
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|def_tmr_get_time
id|def_tmr_get_time
c_func
(paren
r_int
id|dev
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|opened
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|curr_ticks
suffix:semicolon
)brace
multiline_comment|/* same as sound_timer.c:timer_ioctl!? */
DECL|function|def_tmr_ioctl
r_static
r_int
id|def_tmr_ioctl
c_func
(paren
r_int
id|dev
comma
r_int
r_int
id|cmd
comma
id|caddr_t
id|arg
)paren
(brace
r_int
id|val
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SNDCTL_TMR_SOURCE
suffix:colon
r_return
id|__put_user
c_func
(paren
id|TMR_INTERNAL
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|SNDCTL_TMR_START
suffix:colon
id|tmr_reset
c_func
(paren
)paren
suffix:semicolon
id|tmr_running
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SNDCTL_TMR_STOP
suffix:colon
id|tmr_running
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SNDCTL_TMR_CONTINUE
suffix:colon
id|tmr_running
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SNDCTL_TMR_TIMEBASE
suffix:colon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|val
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
(brace
r_if
c_cond
(paren
id|val
OL
l_int|1
)paren
id|val
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|val
OG
l_int|1000
)paren
id|val
op_assign
l_int|1000
suffix:semicolon
id|curr_timebase
op_assign
id|val
suffix:semicolon
)brace
r_return
id|__put_user
c_func
(paren
id|curr_timebase
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|SNDCTL_TMR_TEMPO
suffix:colon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|val
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|val
)paren
(brace
r_if
c_cond
(paren
id|val
OL
l_int|8
)paren
id|val
op_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|val
OG
l_int|250
)paren
id|val
op_assign
l_int|250
suffix:semicolon
id|tmr_offs
op_assign
id|tmr_ctr
suffix:semicolon
id|ticks_offs
op_add_assign
id|tmr2ticks
c_func
(paren
id|tmr_ctr
)paren
suffix:semicolon
id|tmr_ctr
op_assign
l_int|0
suffix:semicolon
id|curr_tempo
op_assign
id|val
suffix:semicolon
id|reprogram_timer
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|__put_user
c_func
(paren
id|curr_tempo
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|SNDCTL_SEQ_CTRLRATE
suffix:colon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|val
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|val
op_ne
l_int|0
)paren
multiline_comment|/* Can&squot;t change */
r_return
op_minus
id|EINVAL
suffix:semicolon
id|val
op_assign
(paren
(paren
id|curr_tempo
op_star
id|curr_timebase
)paren
op_plus
l_int|30
)paren
op_div
l_int|60
suffix:semicolon
r_return
id|__put_user
c_func
(paren
id|val
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|SNDCTL_SEQ_GETTIME
suffix:colon
r_return
id|__put_user
c_func
(paren
id|curr_ticks
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|SNDCTL_TMR_METRONOME
suffix:colon
multiline_comment|/* NOP */
r_break
suffix:semicolon
r_default
suffix:colon
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_static
r_void
DECL|function|def_tmr_arm
id|def_tmr_arm
c_func
(paren
r_int
id|dev
comma
r_int
id|time
)paren
(brace
r_if
c_cond
(paren
id|time
OL
l_int|0
)paren
id|time
op_assign
id|curr_ticks
op_plus
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|time
op_le
id|curr_ticks
)paren
multiline_comment|/* It&squot;s the time */
r_return
suffix:semicolon
id|next_event_time
op_assign
id|prev_event_time
op_assign
id|time
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|default_sound_timer
r_struct
id|sound_timer_operations
id|default_sound_timer
op_assign
(brace
(brace
l_string|&quot;System clock&quot;
comma
l_int|0
)brace
comma
l_int|0
comma
multiline_comment|/* Priority */
l_int|0
comma
multiline_comment|/* Local device link */
id|def_tmr_open
comma
id|def_tmr_close
comma
id|def_tmr_event
comma
id|def_tmr_get_time
comma
id|def_tmr_ioctl
comma
id|def_tmr_arm
)brace
suffix:semicolon
macro_line|#endif
eof
