multiline_comment|/*&n; * sound/patmgr.c&n; *&n; * The patch maneger interface for the /dev/sequencer&n; */
multiline_comment|/*&n; * Copyright by Hannu Savolainen 1993-1996&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions are&n; * met: 1. Redistributions of source code must retain the above copyright&n; * notice, this list of conditions and the following disclaimer. 2.&n; * Redistributions in binary form must reproduce the above copyright notice,&n; * this list of conditions and the following disclaimer in the documentation&n; * and/or other materials provided with the distribution.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND ANY&n; * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED&n; * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR&n; * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER&n; * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|PATMGR_C
mdefine_line|#define PATMGR_C
macro_line|#include &quot;sound_config.h&quot;
macro_line|#if defined(CONFIG_SEQUENCER)
DECL|variable|server_procs
r_static
id|wait_handle
op_star
id|server_procs
(braket
id|MAX_SYNTH_DEV
)braket
op_assign
(brace
l_int|NULL
)brace
suffix:semicolon
DECL|variable|server_wait_flag
r_static
r_volatile
r_struct
id|snd_wait
id|server_wait_flag
(braket
id|MAX_SYNTH_DEV
)braket
op_assign
(brace
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|mbox
r_static
r_struct
id|patmgr_info
op_star
id|mbox
(braket
id|MAX_SYNTH_DEV
)braket
op_assign
(brace
l_int|NULL
)brace
suffix:semicolon
DECL|variable|msg_direction
r_static
r_volatile
r_int
id|msg_direction
(braket
id|MAX_SYNTH_DEV
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
DECL|variable|pmgr_opened
r_static
r_int
id|pmgr_opened
(braket
id|MAX_SYNTH_DEV
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
DECL|macro|A_TO_S
mdefine_line|#define A_TO_S&t;1
DECL|macro|S_TO_A
mdefine_line|#define S_TO_A &t;2
DECL|variable|appl_proc
r_static
id|wait_handle
op_star
id|appl_proc
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|appl_wait_flag
r_static
r_volatile
r_struct
id|snd_wait
id|appl_wait_flag
op_assign
(brace
l_int|0
)brace
suffix:semicolon
r_int
DECL|function|pmgr_open
id|pmgr_open
(paren
r_int
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev
OL
l_int|0
op_logical_or
id|dev
op_ge
id|num_synths
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|pmgr_opened
(braket
id|dev
)braket
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|pmgr_opened
(braket
id|dev
)braket
op_assign
l_int|1
suffix:semicolon
id|server_wait_flag
(braket
id|dev
)braket
dot
id|mode
op_assign
id|WK_NONE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|pmgr_release
id|pmgr_release
(paren
r_int
id|dev
)paren
(brace
r_if
c_cond
(paren
id|mbox
(braket
id|dev
)braket
)paren
multiline_comment|/*&n;&t;&t;&t;&t; * Killed in action. Inform the client&n;&t;&t;&t;&t; */
(brace
id|mbox
(braket
id|dev
)braket
op_member_access_from_pointer
id|key
op_assign
id|PM_ERROR
suffix:semicolon
id|mbox
(braket
id|dev
)braket
op_member_access_from_pointer
id|parm1
op_assign
op_minus
id|EIO
suffix:semicolon
r_if
c_cond
(paren
(paren
id|appl_wait_flag.mode
op_amp
id|WK_SLEEP
)paren
)paren
(brace
id|appl_wait_flag.mode
op_assign
id|WK_WAKEUP
suffix:semicolon
id|module_wake_up
(paren
op_amp
id|appl_proc
)paren
suffix:semicolon
)brace
suffix:semicolon
)brace
id|pmgr_opened
(braket
id|dev
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|pmgr_read
id|pmgr_read
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ok
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ne
r_sizeof
(paren
r_struct
id|patmgr_info
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;PATMGR%d: Invalid read count&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|ok
op_logical_and
op_logical_neg
id|current_got_fatal_signal
(paren
)paren
)paren
(brace
id|save_flags
(paren
id|flags
)paren
suffix:semicolon
id|cli
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|mbox
(braket
id|dev
)braket
op_logical_and
id|msg_direction
(braket
id|dev
)braket
op_eq
id|A_TO_S
)paren
op_logical_and
op_logical_neg
id|current_got_fatal_signal
(paren
)paren
)paren
(brace
id|server_wait_flag
(braket
id|dev
)braket
dot
id|mode
op_assign
id|WK_SLEEP
suffix:semicolon
id|module_interruptible_sleep_on
(paren
op_amp
id|server_procs
(braket
id|dev
)braket
)paren
suffix:semicolon
id|server_wait_flag
(braket
id|dev
)braket
dot
id|mode
op_and_assign
op_complement
id|WK_SLEEP
suffix:semicolon
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mbox
(braket
id|dev
)braket
op_logical_and
id|msg_direction
(braket
id|dev
)braket
op_eq
id|A_TO_S
)paren
(brace
id|memcpy_tofs
(paren
op_amp
(paren
(paren
id|buf
)paren
(braket
l_int|0
)braket
)paren
comma
(paren
r_char
op_star
)paren
id|mbox
(braket
id|dev
)braket
comma
id|count
)paren
suffix:semicolon
id|msg_direction
(braket
id|dev
)braket
op_assign
l_int|0
suffix:semicolon
id|ok
op_assign
l_int|1
suffix:semicolon
)brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|ok
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_int
DECL|function|pmgr_write
id|pmgr_write
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|4
)paren
(brace
id|printk
(paren
l_string|&quot;PATMGR%d: Write count &lt; 4&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|memcpy_fromfs
(paren
(paren
r_char
op_star
)paren
id|mbox
(braket
id|dev
)braket
comma
op_amp
(paren
(paren
id|buf
)paren
(braket
l_int|0
)braket
)paren
comma
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
(paren
r_int
r_char
op_star
)paren
id|mbox
(braket
id|dev
)braket
op_eq
id|SEQ_FULLSIZE
)paren
(brace
r_int
id|tmp_dev
suffix:semicolon
id|tmp_dev
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|mbox
(braket
id|dev
)braket
)paren
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|tmp_dev
op_ne
id|dev
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_return
id|synth_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|load_patch
(paren
id|dev
comma
op_star
(paren
r_int
r_int
op_star
)paren
id|mbox
(braket
id|dev
)braket
comma
id|buf
comma
l_int|4
comma
id|count
comma
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_ne
r_sizeof
(paren
r_struct
id|patmgr_info
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;PATMGR%d: Invalid write count&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/*&n;   * If everything went OK, there should be a preallocated buffer in the&n;   * mailbox and a client waiting.&n;   */
id|save_flags
(paren
id|flags
)paren
suffix:semicolon
id|cli
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mbox
(braket
id|dev
)braket
op_logical_and
op_logical_neg
id|msg_direction
(braket
id|dev
)braket
)paren
(brace
id|memcpy_fromfs
(paren
op_amp
(paren
(paren
r_char
op_star
)paren
id|mbox
(braket
id|dev
)braket
)paren
(braket
l_int|4
)braket
comma
op_amp
(paren
(paren
id|buf
)paren
(braket
l_int|4
)braket
)paren
comma
id|count
op_minus
l_int|4
)paren
suffix:semicolon
id|msg_direction
(braket
id|dev
)braket
op_assign
id|S_TO_A
suffix:semicolon
r_if
c_cond
(paren
(paren
id|appl_wait_flag.mode
op_amp
id|WK_SLEEP
)paren
)paren
(brace
(brace
id|appl_wait_flag.mode
op_assign
id|WK_WAKEUP
suffix:semicolon
id|module_wake_up
(paren
op_amp
id|appl_proc
)paren
suffix:semicolon
)brace
suffix:semicolon
)brace
)brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_int
DECL|function|pmgr_access
id|pmgr_access
(paren
r_int
id|dev
comma
r_struct
id|patmgr_info
op_star
id|rec
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|save_flags
(paren
id|flags
)paren
suffix:semicolon
id|cli
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mbox
(braket
id|dev
)braket
)paren
id|printk
(paren
l_string|&quot;  PATMGR: Server %d mbox full. Why?&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_else
(brace
id|rec-&gt;key
op_assign
id|PM_K_COMMAND
suffix:semicolon
id|mbox
(braket
id|dev
)braket
op_assign
id|rec
suffix:semicolon
id|msg_direction
(braket
id|dev
)braket
op_assign
id|A_TO_S
suffix:semicolon
r_if
c_cond
(paren
(paren
id|server_wait_flag
(braket
id|dev
)braket
dot
id|mode
op_amp
id|WK_SLEEP
)paren
)paren
(brace
(brace
id|server_wait_flag
(braket
id|dev
)braket
dot
id|mode
op_assign
id|WK_WAKEUP
suffix:semicolon
id|module_wake_up
(paren
op_amp
id|server_procs
(braket
id|dev
)braket
)paren
suffix:semicolon
)brace
suffix:semicolon
)brace
id|appl_wait_flag.mode
op_assign
id|WK_SLEEP
suffix:semicolon
id|module_interruptible_sleep_on
(paren
op_amp
id|appl_proc
)paren
suffix:semicolon
id|appl_wait_flag.mode
op_and_assign
op_complement
id|WK_SLEEP
suffix:semicolon
suffix:semicolon
r_if
c_cond
(paren
id|msg_direction
(braket
id|dev
)braket
op_ne
id|S_TO_A
)paren
(brace
id|rec-&gt;key
op_assign
id|PM_ERROR
suffix:semicolon
id|rec-&gt;parm1
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|rec-&gt;key
op_eq
id|PM_ERROR
)paren
(brace
id|err
op_assign
id|rec-&gt;parm1
suffix:semicolon
r_if
c_cond
(paren
id|err
OG
l_int|0
)paren
id|err
op_assign
op_minus
id|err
suffix:semicolon
)brace
id|mbox
(braket
id|dev
)braket
op_assign
l_int|NULL
suffix:semicolon
id|msg_direction
(braket
id|dev
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_int
DECL|function|pmgr_inform
id|pmgr_inform
(paren
r_int
id|dev
comma
r_int
id|event
comma
r_int
r_int
id|p1
comma
r_int
r_int
id|p2
comma
r_int
r_int
id|p3
comma
r_int
r_int
id|p4
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_struct
id|patmgr_info
op_star
id|tmp_mbox
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmgr_opened
(braket
id|dev
)braket
)paren
r_return
l_int|0
suffix:semicolon
id|tmp_mbox
op_assign
(paren
r_struct
id|patmgr_info
op_star
)paren
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|patmgr_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp_mbox
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
l_string|&quot;pmgr: Couldn&squot;t allocate memory for a message&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|save_flags
(paren
id|flags
)paren
suffix:semicolon
id|cli
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mbox
(braket
id|dev
)braket
)paren
id|printk
(paren
l_string|&quot;  PATMGR: Server %d mbox full. Why?&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_else
(brace
id|mbox
(braket
id|dev
)braket
op_assign
id|tmp_mbox
suffix:semicolon
id|mbox
(braket
id|dev
)braket
op_member_access_from_pointer
id|key
op_assign
id|PM_K_EVENT
suffix:semicolon
id|mbox
(braket
id|dev
)braket
op_member_access_from_pointer
id|command
op_assign
id|event
suffix:semicolon
id|mbox
(braket
id|dev
)braket
op_member_access_from_pointer
id|parm1
op_assign
id|p1
suffix:semicolon
id|mbox
(braket
id|dev
)braket
op_member_access_from_pointer
id|parm2
op_assign
id|p2
suffix:semicolon
id|mbox
(braket
id|dev
)braket
op_member_access_from_pointer
id|parm3
op_assign
id|p3
suffix:semicolon
id|msg_direction
(braket
id|dev
)braket
op_assign
id|A_TO_S
suffix:semicolon
r_if
c_cond
(paren
(paren
id|server_wait_flag
(braket
id|dev
)braket
dot
id|mode
op_amp
id|WK_SLEEP
)paren
)paren
(brace
(brace
id|server_wait_flag
(braket
id|dev
)braket
dot
id|mode
op_assign
id|WK_WAKEUP
suffix:semicolon
id|module_wake_up
(paren
op_amp
id|server_procs
(braket
id|dev
)braket
)paren
suffix:semicolon
)brace
suffix:semicolon
)brace
id|appl_wait_flag.mode
op_assign
id|WK_SLEEP
suffix:semicolon
id|module_interruptible_sleep_on
(paren
op_amp
id|appl_proc
)paren
suffix:semicolon
id|appl_wait_flag.mode
op_and_assign
op_complement
id|WK_SLEEP
suffix:semicolon
suffix:semicolon
id|mbox
(braket
id|dev
)braket
op_assign
l_int|NULL
suffix:semicolon
id|msg_direction
(braket
id|dev
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
id|kfree
(paren
id|tmp_mbox
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#endif
eof
