multiline_comment|/*&n; * sound/patmgr.c&n; *&n; * The patch maneger interface for the /dev/sequencer&n; *&n; * Copyright by Hannu Savolainen 1993&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions are&n; * met: 1. Redistributions of source code must retain the above copyright&n; * notice, this list of conditions and the following disclaimer. 2.&n; * Redistributions in binary form must reproduce the above copyright notice,&n; * this list of conditions and the following disclaimer in the documentation&n; * and/or other materials provided with the distribution.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND ANY&n; * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED&n; * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR&n; * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER&n; * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; */
DECL|macro|PATMGR_C
mdefine_line|#define PATMGR_C
macro_line|#include &quot;sound_config.h&quot;
macro_line|#if defined(CONFIGURE_SOUNDCARD) &amp;&amp; !defined(EXCLUDE_SEQUENCER)
id|DEFINE_WAIT_QUEUES
(paren
id|server_procs
(braket
id|MAX_SYNTH_DEV
)braket
comma
id|server_wait_flag
(braket
id|MAX_SYNTH_DEV
)braket
)paren
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
id|DEFINE_WAIT_QUEUE
(paren
id|appl_proc
comma
id|appl_wait_flag
)paren
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
id|RET_ERROR
(paren
id|ENXIO
)paren
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
id|RET_ERROR
(paren
id|EBUSY
)paren
suffix:semicolon
id|pmgr_opened
(braket
id|dev
)braket
op_assign
l_int|1
suffix:semicolon
id|RESET_WAIT_QUEUE
(paren
id|server_procs
(braket
id|dev
)braket
comma
id|server_wait_flag
(braket
id|dev
)braket
)paren
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
multiline_comment|/* Killed in action. Inform the client */
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
id|RET_ERROR
(paren
id|EIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SOMEONE_WAITING
(paren
id|appl_proc
comma
id|appl_wait_flag
)paren
)paren
id|WAKE_UP
(paren
id|appl_proc
comma
id|appl_wait_flag
)paren
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
id|snd_rw_buf
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
id|RET_ERROR
(paren
id|EIO
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|ok
op_logical_and
op_logical_neg
id|PROCESS_ABORTING
(paren
id|server_procs
(braket
id|dev
)braket
comma
id|server_wait_flag
(braket
id|dev
)braket
)paren
)paren
(brace
id|DISABLE_INTR
(paren
id|flags
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
id|PROCESS_ABORTING
(paren
id|server_procs
(braket
id|dev
)braket
comma
id|server_wait_flag
(braket
id|dev
)braket
)paren
)paren
(brace
id|DO_SLEEP
(paren
id|server_procs
(braket
id|dev
)braket
comma
id|server_wait_flag
(braket
id|dev
)braket
comma
l_int|0
)paren
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
id|COPY_TO_USER
(paren
id|buf
comma
l_int|0
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
id|RESTORE_INTR
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
id|RET_ERROR
(paren
id|EINTR
)paren
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
id|snd_rw_buf
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
id|RET_ERROR
(paren
id|EIO
)paren
suffix:semicolon
)brace
id|COPY_FROM_USER
(paren
id|mbox
(braket
id|dev
)braket
comma
id|buf
comma
l_int|0
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
id|RET_ERROR
(paren
id|ENXIO
)paren
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
id|RET_ERROR
(paren
id|EIO
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;   * If everything went OK, there should be a preallocated buffer in the&n;   * mailbox and a client waiting.&n;   */
id|DISABLE_INTR
(paren
id|flags
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
id|COPY_FROM_USER
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
id|buf
comma
l_int|4
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
id|SOMEONE_WAITING
(paren
id|appl_proc
comma
id|appl_wait_flag
)paren
)paren
(brace
id|WAKE_UP
(paren
id|appl_proc
comma
id|appl_wait_flag
)paren
suffix:semicolon
)brace
)brace
id|RESTORE_INTR
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
id|DISABLE_INTR
(paren
id|flags
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
id|SOMEONE_WAITING
(paren
id|server_procs
(braket
id|dev
)braket
comma
id|server_wait_flag
(braket
id|dev
)braket
)paren
)paren
(brace
id|WAKE_UP
(paren
id|server_procs
(braket
id|dev
)braket
comma
id|server_wait_flag
(braket
id|dev
)braket
)paren
suffix:semicolon
)brace
id|DO_SLEEP
(paren
id|appl_proc
comma
id|appl_wait_flag
comma
l_int|0
)paren
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
id|RET_ERROR
(paren
id|EIO
)paren
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
id|RESTORE_INTR
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
id|DISABLE_INTR
(paren
id|flags
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
(paren
r_struct
id|patmgr_info
op_star
)paren
id|KERNEL_MALLOC
(paren
r_sizeof
(paren
r_struct
id|patmgr_info
)paren
)paren
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
id|SOMEONE_WAITING
(paren
id|server_procs
(braket
id|dev
)braket
comma
id|server_wait_flag
(braket
id|dev
)braket
)paren
)paren
(brace
id|WAKE_UP
(paren
id|server_procs
(braket
id|dev
)braket
comma
id|server_wait_flag
(braket
id|dev
)braket
)paren
suffix:semicolon
)brace
id|DO_SLEEP
(paren
id|appl_proc
comma
id|appl_wait_flag
comma
l_int|0
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
id|KERNEL_FREE
(paren
id|mbox
(braket
id|dev
)braket
)paren
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
id|RESTORE_INTR
(paren
id|flags
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#endif
eof
