multiline_comment|/*&n;   * Copyright 1996 The Australian National University.&n;   * Copyright 1996 Fujitsu Laboratories Limited&n;   * &n;   * This software may be distributed under the terms of the Gnu&n;   * Public License version 2 or later&n;  */
multiline_comment|/* sync functions using the Tnet */
macro_line|#include &lt;asm/ap1000/apreg.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tasks.h&gt;
r_extern
r_int
id|cap_cid0
suffix:semicolon
r_extern
r_int
id|_ncel
comma
id|_ncelx
comma
id|_ncely
comma
id|_cid
suffix:semicolon
DECL|variable|sync_flags
r_static
r_volatile
r_int
id|sync_flags
(braket
id|MPP_NUM_TASKS
)braket
suffix:semicolon
DECL|function|ap_sync
r_int
id|ap_sync
c_func
(paren
r_int
id|numcells
comma
r_int
op_star
id|phys_map
)paren
(brace
r_int
id|basecell
suffix:semicolon
r_int
id|i
comma
id|err
suffix:semicolon
r_int
id|tsk
op_assign
id|current-&gt;taskid
suffix:semicolon
r_if
c_cond
(paren
id|numcells
OL
l_int|2
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MPP_IS_PAR_TASK
c_func
(paren
id|tsk
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nonparallel task %d called ap_sync&bslash;n&quot;
comma
id|tsk
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|tsk
op_sub_assign
id|MPP_TASK_BASE
suffix:semicolon
id|basecell
op_assign
id|phys_map
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|cap_cid0
op_eq
id|basecell
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|wait_on_int
c_func
(paren
op_amp
id|sync_flags
(braket
id|tsk
)braket
comma
id|numcells
op_minus
l_int|1
comma
l_int|5
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|sync_flags
(braket
id|tsk
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|numcells
op_eq
id|_ncel
)paren
(brace
id|ap_bput
c_func
(paren
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|sync_flags
(braket
id|tsk
)braket
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|numcells
suffix:semicolon
id|i
op_increment
)paren
id|ap_put
c_func
(paren
id|phys_map
(braket
id|i
)braket
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|sync_flags
(braket
id|tsk
)braket
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|ap_put
c_func
(paren
id|basecell
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|sync_flags
(braket
id|tsk
)braket
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|wait_on_int
c_func
(paren
op_amp
id|sync_flags
(braket
id|tsk
)braket
comma
l_int|1
comma
l_int|5
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|sync_flags
(braket
id|tsk
)braket
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof