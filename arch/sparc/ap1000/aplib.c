multiline_comment|/*&n;   * Copyright 1996 The Australian National University.&n;   * Copyright 1996 Fujitsu Laboratories Limited&n;   * &n;   * This software may be distributed under the terms of the Gnu&n;   * Public License version 2 or later&n;  */
multiline_comment|/* kernel based aplib.&n;&n;   This was initially implemented in user space, but we eventually&n;   relented when we discovered some really nasty MSC hardware bugs and&n;   decided to disallow access to the device registers by users. Pity :-(&n;&n;   Andrew Tridgell, November 1996 &n;*/
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ap1000/pgtapmmu.h&gt;
macro_line|#include &lt;asm/ap1000/apreg.h&gt;
macro_line|#include &lt;asm/ap1000/apservice.h&gt;
macro_line|#include &lt;asm/ap1000/aplib.h&gt;
r_extern
r_int
op_star
id|tnet_rel_cid_table
suffix:semicolon
r_extern
r_int
id|_cid
comma
id|_ncel
comma
id|_ncelx
comma
id|_ncely
comma
id|_cidx
comma
id|_cidy
suffix:semicolon
multiline_comment|/* this is used to stop the task hogging the MSC while paging in data */
DECL|function|page_in
r_static
r_inline
r_void
id|page_in
c_func
(paren
r_char
op_star
id|addr
comma
r_int
id|size
)paren
(brace
r_int
id|sum
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|size
OG
l_int|0
)paren
(brace
id|sum
op_add_assign
op_star
(paren
r_volatile
r_char
op_star
)paren
id|addr
suffix:semicolon
id|addr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|size
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
multiline_comment|/* this sets up the aplib structures using info passed in from user space&n;   it should only be called once, and should be the first aplib call &n;   it should be followed by APLIB_SYNC &n;   */
DECL|function|aplib_init
r_static
r_inline
r_int
id|aplib_init
c_func
(paren
r_struct
id|aplib_init
op_star
id|init
)paren
(brace
r_struct
id|aplib_struct
op_star
id|aplib
suffix:semicolon
r_int
id|error
comma
id|i
suffix:semicolon
r_int
id|old_uid
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|init
comma
r_sizeof
(paren
op_star
id|init
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|init-&gt;phys_cells
comma
r_sizeof
(paren
r_int
)paren
op_star
id|init-&gt;numcells
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|init-&gt;ringbuffer
comma
id|init-&gt;ringbuf_size
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_char
op_star
)paren
id|APLIB_PAGE_BASE
comma
id|APLIB_PAGE_LEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MPP_IS_PAR_TASK
c_func
(paren
id|current-&gt;taskid
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;aplib
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|aplib
op_assign
id|current-&gt;aplib
op_assign
(paren
r_struct
id|aplib_struct
op_star
)paren
id|APLIB_PAGE_BASE
suffix:semicolon
multiline_comment|/* lock the aplib structure in memory */
id|old_uid
op_assign
id|current-&gt;euid
suffix:semicolon
id|current-&gt;euid
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|aplib
comma
l_int|0
comma
id|APLIB_PAGE_LEN
)paren
suffix:semicolon
id|error
op_assign
id|sys_mlock
c_func
(paren
id|aplib
comma
id|APLIB_PAGE_LEN
)paren
suffix:semicolon
id|current-&gt;euid
op_assign
id|old_uid
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mlock1 failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/* lock the ringbuffer in memory */
id|old_uid
op_assign
id|current-&gt;euid
suffix:semicolon
id|current-&gt;euid
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|init-&gt;ringbuffer
comma
l_int|0
comma
id|init-&gt;ringbuf_size
op_star
l_int|4
)paren
suffix:semicolon
id|error
op_assign
id|sys_mlock
c_func
(paren
id|init-&gt;ringbuffer
comma
id|init-&gt;ringbuf_size
op_star
l_int|4
)paren
suffix:semicolon
id|current-&gt;euid
op_assign
id|old_uid
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mlock2 failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|aplib-&gt;ringbuf
op_assign
id|init-&gt;ringbuffer
suffix:semicolon
id|aplib-&gt;ringbuf_size
op_assign
id|init-&gt;ringbuf_size
suffix:semicolon
id|aplib-&gt;numcells
op_assign
id|init-&gt;numcells
suffix:semicolon
id|aplib-&gt;cid
op_assign
id|init-&gt;cid
suffix:semicolon
id|aplib-&gt;tid
op_assign
id|current-&gt;taskid
suffix:semicolon
id|aplib-&gt;numcells_x
op_assign
id|init-&gt;numcells_x
suffix:semicolon
id|aplib-&gt;numcells_y
op_assign
id|init-&gt;numcells_y
suffix:semicolon
id|aplib-&gt;cidx
op_assign
id|init-&gt;cid
op_mod
id|init-&gt;numcells_x
suffix:semicolon
id|aplib-&gt;cidy
op_assign
id|init-&gt;cid
op_div
id|init-&gt;numcells_x
suffix:semicolon
id|aplib-&gt;physical_cid
op_assign
(paren
r_int
op_star
)paren
(paren
id|aplib
op_plus
l_int|1
)paren
suffix:semicolon
id|aplib-&gt;rel_cid
op_assign
id|aplib-&gt;physical_cid
op_plus
id|init-&gt;numcells
suffix:semicolon
r_if
c_cond
(paren
(paren
r_char
op_star
)paren
(paren
id|aplib-&gt;rel_cid
op_plus
id|init-&gt;numcells
)paren
OG
(paren
r_char
op_star
)paren
(paren
id|APLIB_PAGE_BASE
op_plus
id|APLIB_PAGE_LEN
)paren
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|aplib-&gt;physical_cid
comma
id|init-&gt;phys_cells
comma
r_sizeof
(paren
r_int
)paren
op_star
id|init-&gt;numcells
)paren
suffix:semicolon
multiline_comment|/* initialise the relative cid table */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|aplib-&gt;numcells
suffix:semicolon
id|i
op_increment
)paren
id|aplib-&gt;rel_cid
(braket
id|i
)braket
op_assign
id|tnet_rel_cid_table
(braket
id|aplib-&gt;physical_cid
(braket
id|i
)braket
)braket
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* n == which sync line (ignored)&n;   returns logical or of the stat values across the cells (1 bit resolution) &n;&n;   This has to be done very carefully as the tasks can startup on the cells&n;   in any order, so we don&squot;t know which tasks have started up when this&n;   is called&n;*/
DECL|function|aplib_sync
r_static
r_inline
r_int
id|aplib_sync
c_func
(paren
r_int
id|n
comma
r_int
id|stat
)paren
(brace
r_struct
id|aplib_struct
op_star
id|aplib
op_assign
id|current-&gt;aplib
suffix:semicolon
r_static
r_int
id|sync_flags
(braket
id|MPP_NUM_TASKS
)braket
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
id|stat
op_and_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|aplib-&gt;numcells
OL
l_int|2
)paren
r_return
id|stat
suffix:semicolon
id|tsk
op_sub_assign
id|MPP_TASK_BASE
suffix:semicolon
r_if
c_cond
(paren
id|aplib-&gt;cid
op_eq
l_int|0
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
id|aplib-&gt;numcells
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
id|aplib-&gt;numcells
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
(paren
id|u_long
)paren
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
id|aplib-&gt;numcells
suffix:semicolon
id|i
op_increment
)paren
id|ap_put
c_func
(paren
id|aplib-&gt;physical_cid
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
(paren
id|u_long
)paren
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
)brace
r_else
(brace
id|ap_put
c_func
(paren
id|aplib-&gt;physical_cid
(braket
l_int|0
)braket
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
(paren
id|u_long
)paren
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
)brace
multiline_comment|/* I haven&squot;t written the xy_ calls yet ... */
multiline_comment|/* aplib_xy_ior(stat,&amp;stat); */
r_return
id|stat
suffix:semicolon
)brace
DECL|function|_putget
r_static
r_inline
r_void
id|_putget
c_func
(paren
r_int
id|q
comma
r_int
id|rcell
comma
r_int
op_star
id|src_addr
comma
r_int
id|size
comma
r_int
op_star
id|dest_addr
comma
r_int
op_star
id|dest_flag
comma
r_int
op_star
id|src_flag
)paren
(brace
r_int
id|flags
suffix:semicolon
r_volatile
r_int
op_star
id|entry
op_assign
(paren
r_volatile
r_int
op_star
)paren
id|q
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
op_star
id|entry
op_assign
id|rcell
suffix:semicolon
op_star
id|entry
op_assign
id|size
suffix:semicolon
op_star
id|entry
op_assign
(paren
r_int
)paren
id|dest_addr
suffix:semicolon
op_star
id|entry
op_assign
l_int|0
suffix:semicolon
op_star
id|entry
op_assign
(paren
r_int
)paren
id|dest_flag
suffix:semicolon
op_star
id|entry
op_assign
(paren
r_int
)paren
id|src_flag
suffix:semicolon
op_star
id|entry
op_assign
(paren
r_int
)paren
id|src_addr
suffix:semicolon
op_star
id|entry
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
multiline_comment|/* a basic put() operation. Note the avoidance of odd word boundaries&n;   and transfers sizes beyond what the hardware can deal with */
DECL|function|aplib_put
r_static
r_inline
r_int
id|aplib_put
c_func
(paren
r_struct
id|aplib_putget
op_star
id|put
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|aplib_struct
op_star
id|aplib
op_assign
id|current-&gt;aplib
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|put
comma
r_sizeof
(paren
op_star
id|put
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
id|put-&gt;cid
op_ge
id|aplib-&gt;numcells
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_do
(brace
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
id|put-&gt;size
op_logical_and
(paren
(paren
(paren
r_int
)paren
id|put-&gt;src_addr
)paren
op_amp
l_int|4
)paren
)paren
(brace
id|n
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|put-&gt;size
OG
id|MAX_PUT_SIZE
)paren
(brace
id|n
op_assign
id|MAX_PUT_SIZE
suffix:semicolon
)brace
r_else
(brace
id|n
op_assign
id|put-&gt;size
suffix:semicolon
)brace
id|put-&gt;size
op_sub_assign
id|n
suffix:semicolon
id|page_in
c_func
(paren
(paren
r_char
op_star
)paren
id|put-&gt;src_addr
comma
id|n
op_lshift
l_int|2
)paren
suffix:semicolon
id|_putget
c_func
(paren
id|MSC_PUT_QUEUE
comma
id|aplib-&gt;rel_cid
(braket
id|put-&gt;cid
)braket
comma
id|put-&gt;src_addr
comma
id|n
comma
id|put-&gt;dest_addr
comma
id|put-&gt;size
ques
c_cond
l_int|0
suffix:colon
id|put-&gt;dest_flag
comma
id|put-&gt;size
ques
c_cond
l_int|0
suffix:colon
id|put-&gt;src_flag
)paren
suffix:semicolon
id|put-&gt;dest_addr
op_add_assign
id|n
suffix:semicolon
id|put-&gt;src_addr
op_add_assign
id|n
suffix:semicolon
)brace
r_while
c_loop
(paren
id|put-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|put-&gt;ack
)paren
(brace
id|aplib-&gt;ack_request
op_increment
suffix:semicolon
id|_putget
c_func
(paren
id|MSC_GET_QUEUE
comma
id|aplib-&gt;rel_cid
(braket
id|put-&gt;cid
)braket
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|aplib-&gt;ack_flag
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* a basic get() operation */
DECL|function|aplib_get
r_static
r_inline
r_int
id|aplib_get
c_func
(paren
r_struct
id|aplib_putget
op_star
id|get
)paren
(brace
r_struct
id|aplib_struct
op_star
id|aplib
op_assign
id|current-&gt;aplib
suffix:semicolon
r_int
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|get
comma
r_sizeof
(paren
op_star
id|get
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
id|get-&gt;cid
op_ge
id|aplib-&gt;numcells
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_do
(brace
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
id|get-&gt;size
op_logical_and
(paren
(paren
(paren
r_int
)paren
id|get-&gt;src_addr
)paren
op_amp
l_int|4
)paren
)paren
(brace
id|n
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|get-&gt;size
OG
id|MAX_PUT_SIZE
)paren
(brace
id|n
op_assign
id|MAX_PUT_SIZE
suffix:semicolon
)brace
r_else
(brace
id|n
op_assign
id|get-&gt;size
suffix:semicolon
)brace
id|get-&gt;size
op_sub_assign
id|n
suffix:semicolon
id|page_in
c_func
(paren
(paren
r_char
op_star
)paren
id|get-&gt;dest_addr
comma
id|n
op_lshift
l_int|2
)paren
suffix:semicolon
id|_putget
c_func
(paren
id|MSC_GET_QUEUE
comma
id|aplib-&gt;rel_cid
(braket
id|get-&gt;cid
)braket
comma
id|get-&gt;src_addr
comma
id|n
comma
id|get-&gt;dest_addr
comma
id|get-&gt;size
ques
c_cond
l_int|0
suffix:colon
id|get-&gt;dest_flag
comma
id|get-&gt;size
ques
c_cond
l_int|0
suffix:colon
id|get-&gt;src_flag
)paren
suffix:semicolon
id|get-&gt;dest_addr
op_add_assign
id|n
suffix:semicolon
id|get-&gt;src_addr
op_add_assign
id|n
suffix:semicolon
)brace
r_while
c_loop
(paren
id|get-&gt;size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* we have received a protocol message - now do the get &n; This function is called from interrupt level with interrupts&n; disabled &n;&n; note that send-&gt;size is now in words&n;*/
DECL|function|aplib_bigrecv
r_void
id|aplib_bigrecv
c_func
(paren
r_int
op_star
id|msgp
)paren
(brace
r_struct
id|aplib_struct
op_star
id|aplib
suffix:semicolon
r_struct
id|aplib_send
op_star
id|send
op_assign
(paren
r_struct
id|aplib_send
op_star
)paren
(paren
id|msgp
op_plus
l_int|2
)paren
suffix:semicolon
r_int
id|tid
op_assign
(paren
id|msgp
(braket
l_int|1
)braket
op_amp
l_int|0x3FF
)paren
suffix:semicolon
r_int
id|cid
op_assign
(paren
id|msgp
(braket
l_int|0
)braket
op_rshift
l_int|22
)paren
op_amp
l_int|0x1FF
suffix:semicolon
r_int
id|octx
comma
id|ctx
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
r_int
id|room
suffix:semicolon
id|tsk
op_assign
id|task
(braket
id|tid
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tsk
op_logical_or
op_logical_neg
id|tsk-&gt;aplib
)paren
r_return
suffix:semicolon
id|octx
op_assign
id|apmmu_get_context
c_func
(paren
)paren
suffix:semicolon
id|ctx
op_assign
id|MPP_TASK_TO_CTX
c_func
(paren
id|tid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|octx
op_ne
id|ctx
)paren
id|apmmu_set_context
c_func
(paren
id|ctx
)paren
suffix:semicolon
id|aplib
op_assign
id|tsk-&gt;aplib
suffix:semicolon
r_if
c_cond
(paren
id|aplib-&gt;write_pointer
OL
id|aplib-&gt;read_pointer
)paren
id|room
op_assign
id|aplib-&gt;read_pointer
op_minus
(paren
id|aplib-&gt;write_pointer
op_plus
l_int|1
)paren
suffix:semicolon
r_else
id|room
op_assign
id|aplib-&gt;ringbuf_size
op_minus
(paren
(paren
id|aplib-&gt;write_pointer
op_plus
l_int|1
)paren
op_minus
id|aplib-&gt;read_pointer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|room
OL
(paren
id|send-&gt;size
op_plus
l_int|2
)paren
)paren
(brace
id|send_sig
c_func
(paren
id|SIGLOST
comma
id|tsk
comma
l_int|1
)paren
suffix:semicolon
r_goto
id|finished
suffix:semicolon
)brace
id|aplib-&gt;ringbuf
(braket
id|aplib-&gt;write_pointer
op_increment
)braket
op_assign
id|send-&gt;info1
suffix:semicolon
id|aplib-&gt;ringbuf
(braket
id|aplib-&gt;write_pointer
op_increment
)braket
op_assign
id|send-&gt;info2
suffix:semicolon
multiline_comment|/* now finally do the get() */
id|_putget
c_func
(paren
id|MSC_GET_QUEUE
comma
id|aplib-&gt;rel_cid
(braket
id|cid
)braket
comma
id|send-&gt;src_addr
comma
id|send-&gt;size
comma
op_amp
id|aplib-&gt;ringbuf
(braket
id|aplib-&gt;write_pointer
)braket
comma
op_amp
id|aplib-&gt;rbuf_flag2
comma
id|send-&gt;flag_addr
)paren
suffix:semicolon
id|aplib-&gt;write_pointer
op_add_assign
id|send-&gt;size
suffix:semicolon
r_if
c_cond
(paren
id|aplib-&gt;write_pointer
op_ge
id|aplib-&gt;ringbuf_size
)paren
id|aplib-&gt;write_pointer
op_sub_assign
id|aplib-&gt;ringbuf_size
suffix:semicolon
id|finished
suffix:colon
r_if
c_cond
(paren
id|octx
op_ne
id|ctx
)paren
id|apmmu_set_context
c_func
(paren
id|octx
)paren
suffix:semicolon
)brace
multiline_comment|/* note the 8 byte alignment fix for the MSC bug */
DECL|function|aplib_send
r_static
r_inline
r_int
id|aplib_send
c_func
(paren
r_struct
id|aplib_send
op_star
id|send
)paren
(brace
r_struct
id|aplib_struct
op_star
id|aplib
op_assign
id|current-&gt;aplib
suffix:semicolon
r_int
id|wordSize
suffix:semicolon
r_int
id|byteAlign
comma
id|byteFix
suffix:semicolon
id|u_long
id|src
suffix:semicolon
id|u_long
id|info1
comma
id|info2
suffix:semicolon
r_volatile
r_int
op_star
id|q
op_assign
(paren
r_volatile
r_int
op_star
)paren
id|MSC_SEND_QUEUE_S
suffix:semicolon
r_extern
r_int
id|system_recv_flag
suffix:semicolon
r_int
id|error
suffix:semicolon
r_int
id|flags
comma
id|rcell
suffix:semicolon
r_int
id|flag_ptr
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|send
comma
r_sizeof
(paren
op_star
id|send
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
id|send-&gt;cid
op_ge
id|aplib-&gt;numcells
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|send-&gt;tag
op_eq
id|RBUF_SYSTEM
op_logical_or
id|send-&gt;tag
op_eq
id|RBUF_BIGSEND
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_char
op_star
)paren
id|send-&gt;src_addr
comma
id|send-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|page_in
c_func
(paren
(paren
r_char
op_star
)paren
id|send-&gt;src_addr
comma
id|send-&gt;size
)paren
suffix:semicolon
id|rcell
op_assign
id|aplib-&gt;rel_cid
(braket
id|send-&gt;cid
)braket
suffix:semicolon
id|byteAlign
op_assign
id|send-&gt;src_addr
op_amp
l_int|0x3
suffix:semicolon
id|byteFix
op_assign
id|send-&gt;size
op_amp
l_int|0x3
suffix:semicolon
id|wordSize
op_assign
(paren
id|send-&gt;size
op_plus
id|byteAlign
op_plus
l_int|3
)paren
op_rshift
l_int|2
suffix:semicolon
id|src
op_assign
id|send-&gt;src_addr
op_amp
op_complement
l_int|3
suffix:semicolon
multiline_comment|/* this handles the MSC alignment bug */
r_if
c_cond
(paren
id|wordSize
OG
l_int|1
op_logical_and
(paren
id|src
op_amp
l_int|4
)paren
)paren
(brace
id|info1
op_or_assign
l_int|0x80000000
suffix:semicolon
id|src
op_sub_assign
l_int|4
suffix:semicolon
id|wordSize
op_increment
suffix:semicolon
)brace
id|info1
op_assign
(paren
id|aplib-&gt;cid
op_lshift
l_int|22
)paren
op_or
(paren
id|byteFix
op_lshift
l_int|20
)paren
op_or
id|wordSize
suffix:semicolon
id|info2
op_assign
(paren
id|send-&gt;tag
op_lshift
l_int|28
)paren
op_or
(paren
id|byteAlign
op_lshift
l_int|26
)paren
op_or
(paren
id|send-&gt;type
op_lshift
l_int|10
)paren
op_or
id|aplib-&gt;tid
suffix:semicolon
id|flag_ptr
op_assign
(paren
r_int
)paren
op_amp
id|send-&gt;flag
suffix:semicolon
r_if
c_cond
(paren
id|send-&gt;size
OG
id|SMALL_SEND_THRESHOLD
)paren
(brace
id|send-&gt;info1
op_assign
id|info1
suffix:semicolon
id|send-&gt;info2
op_assign
id|info2
suffix:semicolon
id|send-&gt;size
op_assign
id|wordSize
suffix:semicolon
id|send-&gt;src_addr
op_assign
id|src
suffix:semicolon
id|send-&gt;flag_addr
op_assign
(paren
r_int
)paren
op_amp
id|send-&gt;flag
suffix:semicolon
id|flag_ptr
op_assign
l_int|0
suffix:semicolon
id|wordSize
op_assign
r_sizeof
(paren
op_star
id|send
)paren
op_rshift
l_int|2
suffix:semicolon
id|src
op_assign
(paren
r_int
)paren
id|send
suffix:semicolon
id|info1
op_assign
(paren
id|aplib-&gt;cid
op_lshift
l_int|22
)paren
op_or
id|wordSize
suffix:semicolon
id|info2
op_assign
(paren
id|RBUF_BIGSEND
op_lshift
l_int|28
)paren
op_or
id|aplib-&gt;tid
suffix:semicolon
)brace
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
op_star
id|q
op_assign
id|rcell
suffix:semicolon
op_star
id|q
op_assign
id|wordSize
suffix:semicolon
op_star
id|q
op_assign
(paren
id|u_long
)paren
op_amp
id|system_recv_flag
suffix:semicolon
op_star
id|q
op_assign
id|flag_ptr
suffix:semicolon
op_star
id|q
op_assign
(paren
id|u_long
)paren
id|src
suffix:semicolon
op_star
id|q
op_assign
l_int|0
suffix:semicolon
op_star
id|q
op_assign
id|info1
suffix:semicolon
op_star
id|q
op_assign
id|info2
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|aplib_probe
r_static
r_inline
r_int
id|aplib_probe
c_func
(paren
r_void
)paren
(brace
id|tnet_check_completion
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|aplib_poll
r_static
r_inline
r_int
id|aplib_poll
c_func
(paren
r_int
id|counter
)paren
(brace
r_struct
id|aplib_struct
op_star
id|aplib
op_assign
id|current-&gt;aplib
suffix:semicolon
r_while
c_loop
(paren
id|counter
op_eq
id|aplib-&gt;rbuf_flag1
op_plus
id|aplib-&gt;rbuf_flag2
)paren
(brace
id|tnet_check_completion
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|need_resched
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_aplib
r_int
id|sys_aplib
c_func
(paren
r_int
id|call
comma
r_int
id|a1
comma
r_int
id|a2
comma
r_int
id|a3
comma
r_int
id|a4
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;aplib
op_logical_and
id|call
op_ne
id|APLIB_INIT
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|call
)paren
(brace
r_case
id|APLIB_INIT
suffix:colon
r_return
id|aplib_init
c_func
(paren
(paren
r_struct
id|aplib_init
op_star
)paren
id|a1
)paren
suffix:semicolon
r_case
id|APLIB_SYNC
suffix:colon
r_return
id|aplib_sync
c_func
(paren
id|a1
comma
id|a2
)paren
suffix:semicolon
r_case
id|APLIB_PUT
suffix:colon
r_return
id|aplib_put
c_func
(paren
(paren
r_struct
id|aplib_putget
op_star
)paren
id|a1
)paren
suffix:semicolon
r_case
id|APLIB_GET
suffix:colon
r_return
id|aplib_get
c_func
(paren
(paren
r_struct
id|aplib_putget
op_star
)paren
id|a1
)paren
suffix:semicolon
r_case
id|APLIB_SEND
suffix:colon
r_return
id|aplib_send
c_func
(paren
(paren
r_struct
id|aplib_send
op_star
)paren
id|a1
)paren
suffix:semicolon
r_case
id|APLIB_PROBE
suffix:colon
r_return
id|aplib_probe
c_func
(paren
)paren
suffix:semicolon
r_case
id|APLIB_POLL
suffix:colon
r_return
id|aplib_poll
c_func
(paren
(paren
r_int
)paren
id|a1
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
eof