multiline_comment|/*&n; *  hosts.c Copyright (C) 1992 Drew Eckhardt&n; *          Copyright (C) 1993, 1994, 1995 Eric Youngdale&n; *&n; *  mid to lowlevel SCSI driver interface&n; *      Initial versions: Drew Eckhardt&n; *      Subsequent revisions: Eric Youngdale&n; *&n; *  &lt;drew@colorado.edu&gt;&n; *&n; *  Jiffies wrap fixes (host-&gt;resetting), 3 Dec 1998 Andrea Arcangeli&n; *  Added QLOGIC QLA1280 SCSI controller kernel host support. &n; *     August 4, 1999 Fred Lewis, Intel DuPont&n; *&n; *  Updated to reflect the new initialization scheme for the higher &n; *  level of scsi drivers (sd/sr/st)&n; *  September 17, 2000 Torben Mathiasen &lt;tmm@image.dk&gt;&n; */
multiline_comment|/*&n; *  This file contains the medium level SCSI&n; *  host interface initialization, as well as the scsi_hosts array of SCSI&n; *  hosts currently present in the system.&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
multiline_comment|/*&n;static const char RCSid[] = &quot;$Header: /vger/u4/cvs/linux/drivers/scsi/hosts.c,v 1.20 1996/12/12 19:18:32 davem Exp $&quot;;&n;*/
multiline_comment|/*&n; *  The scsi host entries should be in the order you wish the&n; *  cards to be detected.  A driver may appear more than once IFF&n; *  it can deal with being detected (and therefore initialized)&n; *  with more than one simultaneous host number, can handle being&n; *  reentrant, etc.&n; *&n; *  They may appear in any order, as each SCSI host is told which host &n; *  number it is during detection.&n; */
multiline_comment|/* This is a placeholder for controllers that are not configured into&n; * the system - we do this to ensure that the controller numbering is&n; * always consistent, no matter how the kernel is configured. */
DECL|macro|NO_CONTROLLER
mdefine_line|#define NO_CONTROLLER {NULL, NULL, NULL, NULL, NULL, NULL, NULL, &bslash;&n;&t;&t;&t;   NULL, NULL, 0, 0, 0, 0, 0, 0}
multiline_comment|/*&n; *  When figure is run, we don&squot;t want to link to any object code.  Since&n; *  the macro for each host will contain function pointers, we cannot&n; *  use it and instead must use a &quot;blank&quot; that does no such&n; *  idiocy.&n; */
DECL|variable|scsi_hosts
id|Scsi_Host_Template
op_star
id|scsi_hosts
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; *  Our semaphores and timeout counters, where size depends on &n; *      MAX_SCSI_HOSTS here.&n; */
DECL|variable|scsi_host_no_list
id|Scsi_Host_Name
op_star
id|scsi_host_no_list
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|scsi_hostlist
r_struct
id|Scsi_Host
op_star
id|scsi_hostlist
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|scsi_devicelist
r_struct
id|Scsi_Device_Template
op_star
id|scsi_devicelist
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|max_scsi_hosts
r_int
id|max_scsi_hosts
op_assign
l_int|0
suffix:semicolon
DECL|variable|next_scsi_host
r_int
id|next_scsi_host
op_assign
l_int|0
suffix:semicolon
r_void
DECL|function|scsi_unregister
(def_block
id|scsi_unregister
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|sh
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|shpnt
suffix:semicolon
id|Scsi_Host_Name
op_star
id|shn
suffix:semicolon
r_if
c_cond
(paren
id|scsi_hostlist
op_eq
id|sh
)paren
(brace
id|scsi_hostlist
op_assign
id|sh-&gt;next
suffix:semicolon
)brace
r_else
(brace
id|shpnt
op_assign
id|scsi_hostlist
suffix:semicolon
r_while
c_loop
(paren
id|shpnt-&gt;next
op_ne
id|sh
)paren
(brace
id|shpnt
op_assign
id|shpnt-&gt;next
suffix:semicolon
)brace
id|shpnt-&gt;next
op_assign
id|shpnt-&gt;next-&gt;next
suffix:semicolon
)brace
multiline_comment|/*&n;     * We have to unregister the host from the scsi_host_no_list as well.&n;     * Decide by the host_no not by the name because most host drivers are&n;     * able to handle more than one adapters from the same kind (or family).&n;     */
r_for
c_loop
(paren
id|shn
op_assign
id|scsi_host_no_list
suffix:semicolon
id|shn
op_logical_and
(paren
id|sh-&gt;host_no
op_ne
id|shn-&gt;host_no
)paren
suffix:semicolon
id|shn
op_assign
id|shn-&gt;next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shn
)paren
id|shn-&gt;host_registered
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* else {} : This should not happen, we should panic here... */
multiline_comment|/* If we are removing the last host registered, it is safe to reuse&n;     * its host number (this avoids &quot;holes&quot; at boot time) (DB) &n;     * It is also safe to reuse those of numbers directly below which have&n;     * been released earlier (to avoid some holes in numbering).&n;     */
r_if
c_cond
(paren
id|sh-&gt;host_no
op_eq
id|max_scsi_hosts
op_minus
l_int|1
)paren
(brace
r_while
c_loop
(paren
op_decrement
id|max_scsi_hosts
op_ge
id|next_scsi_host
)paren
(brace
id|shpnt
op_assign
id|scsi_hostlist
suffix:semicolon
r_while
c_loop
(paren
id|shpnt
op_logical_and
id|shpnt-&gt;host_no
op_ne
id|max_scsi_hosts
op_minus
l_int|1
)paren
(brace
id|shpnt
op_assign
id|shpnt-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|shpnt
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
)brace
id|next_scsi_host
op_decrement
suffix:semicolon
id|kfree
c_func
(paren
(paren
r_char
op_star
)paren
id|sh
)paren
suffix:semicolon
)brace
)def_block
multiline_comment|/* We call this when we come across a new host adapter. We only do this&n; * once we are 100% sure that we want to use this host adapter -  it is a&n; * pain to reverse this, so we try to avoid it &n; */
DECL|function|scsi_register
r_struct
id|Scsi_Host
op_star
(def_block
id|scsi_register
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
comma
r_int
id|j
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|retval
comma
op_star
id|shpnt
comma
op_star
id|o_shp
suffix:semicolon
id|Scsi_Host_Name
op_star
id|shn
comma
op_star
id|shn2
suffix:semicolon
r_int
id|flag_new
op_assign
l_int|1
suffix:semicolon
r_const
r_char
op_star
id|hname
suffix:semicolon
r_int
id|hname_len
suffix:semicolon
id|retval
op_assign
(paren
r_struct
id|Scsi_Host
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|Scsi_Host
)paren
op_plus
id|j
comma
(paren
id|tpnt-&gt;unchecked_isa_dma
op_logical_and
id|j
ques
c_cond
id|GFP_DMA
suffix:colon
l_int|0
)paren
op_or
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;scsi: out of memory in scsi_register.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|retval
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|Scsi_Host
)paren
op_plus
id|j
)paren
suffix:semicolon
multiline_comment|/* trying to find a reserved entry (host_no) */
id|hname
op_assign
(paren
id|tpnt-&gt;proc_name
)paren
ques
c_cond
id|tpnt-&gt;proc_name
suffix:colon
l_string|&quot;&quot;
suffix:semicolon
id|hname_len
op_assign
id|strlen
c_func
(paren
id|hname
)paren
suffix:semicolon
r_for
c_loop
(paren
id|shn
op_assign
id|scsi_host_no_list
suffix:semicolon
id|shn
suffix:semicolon
id|shn
op_assign
id|shn-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|shn-&gt;host_registered
)paren
op_logical_and
(paren
id|hname_len
OG
l_int|0
)paren
op_logical_and
(paren
l_int|0
op_eq
id|strncmp
c_func
(paren
id|hname
comma
id|shn-&gt;name
comma
id|hname_len
)paren
)paren
)paren
(brace
id|flag_new
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;host_no
op_assign
id|shn-&gt;host_no
suffix:semicolon
id|shn-&gt;host_registered
op_assign
l_int|1
suffix:semicolon
id|shn-&gt;loaded_as_module
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|atomic_set
c_func
(paren
op_amp
id|retval-&gt;host_active
comma
l_int|0
)paren
suffix:semicolon
id|retval-&gt;host_busy
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;host_failed
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|j
OG
l_int|0xffff
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Too many extra bytes requested&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|retval-&gt;extra_bytes
op_assign
id|j
suffix:semicolon
id|retval-&gt;loaded_as_module
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|flag_new
)paren
(brace
id|shn
op_assign
(paren
id|Scsi_Host_Name
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|Scsi_Host_Name
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|shn-&gt;name
op_assign
id|kmalloc
c_func
(paren
id|hname_len
op_plus
l_int|1
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hname_len
OG
l_int|0
)paren
id|strncpy
c_func
(paren
id|shn-&gt;name
comma
id|hname
comma
id|hname_len
)paren
suffix:semicolon
id|shn-&gt;name
(braket
id|hname_len
)braket
op_assign
l_int|0
suffix:semicolon
id|shn-&gt;host_no
op_assign
id|max_scsi_hosts
op_increment
suffix:semicolon
id|shn-&gt;host_registered
op_assign
l_int|1
suffix:semicolon
id|shn-&gt;loaded_as_module
op_assign
l_int|1
suffix:semicolon
id|shn-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|scsi_host_no_list
)paren
(brace
r_for
c_loop
(paren
id|shn2
op_assign
id|scsi_host_no_list
suffix:semicolon
id|shn2-&gt;next
suffix:semicolon
id|shn2
op_assign
id|shn2-&gt;next
)paren
suffix:semicolon
id|shn2-&gt;next
op_assign
id|shn
suffix:semicolon
)brace
r_else
id|scsi_host_no_list
op_assign
id|shn
suffix:semicolon
id|retval-&gt;host_no
op_assign
id|shn-&gt;host_no
suffix:semicolon
)brace
id|next_scsi_host
op_increment
suffix:semicolon
id|retval-&gt;host_queue
op_assign
l_int|NULL
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|retval-&gt;host_wait
)paren
suffix:semicolon
id|retval-&gt;resetting
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;last_reset
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;irq
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;dma_channel
op_assign
l_int|0xff
suffix:semicolon
multiline_comment|/* These three are default values which can be overridden */
id|retval-&gt;max_channel
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;max_id
op_assign
l_int|8
suffix:semicolon
id|retval-&gt;max_lun
op_assign
l_int|8
suffix:semicolon
multiline_comment|/*&n;     * All drivers right now should be able to handle 12 byte commands.&n;     * Every so often there are requests for 16 byte commands, but individual&n;     * low-level drivers need to certify that they actually do something&n;     * sensible with such commands.&n;     */
id|retval-&gt;max_cmd_len
op_assign
l_int|12
suffix:semicolon
id|retval-&gt;unique_id
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;io_port
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;hostt
op_assign
id|tpnt
suffix:semicolon
id|retval-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|retval-&gt;in_recovery
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;ehandler
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Initial value until the thing starts up. */
id|retval-&gt;eh_notify
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Who we notify when we exit. */
id|retval-&gt;host_blocked
op_assign
id|FALSE
suffix:semicolon
id|retval-&gt;host_self_blocked
op_assign
id|FALSE
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;Register %x %x: %d&bslash;n&quot;
comma
(paren
r_int
)paren
id|retval
comma
(paren
r_int
)paren
id|retval-&gt;hostt
comma
id|j
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* The next six are the default values which can be overridden&n;     * if need be */
id|retval-&gt;this_id
op_assign
id|tpnt-&gt;this_id
suffix:semicolon
id|retval-&gt;can_queue
op_assign
id|tpnt-&gt;can_queue
suffix:semicolon
id|retval-&gt;sg_tablesize
op_assign
id|tpnt-&gt;sg_tablesize
suffix:semicolon
id|retval-&gt;cmd_per_lun
op_assign
id|tpnt-&gt;cmd_per_lun
suffix:semicolon
id|retval-&gt;unchecked_isa_dma
op_assign
id|tpnt-&gt;unchecked_isa_dma
suffix:semicolon
id|retval-&gt;use_clustering
op_assign
id|tpnt-&gt;use_clustering
suffix:semicolon
id|retval-&gt;select_queue_depths
op_assign
id|tpnt-&gt;select_queue_depths
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scsi_hostlist
)paren
(brace
id|scsi_hostlist
op_assign
id|retval
suffix:semicolon
)brace
r_else
(brace
id|shpnt
op_assign
id|scsi_hostlist
suffix:semicolon
r_if
c_cond
(paren
id|retval-&gt;host_no
OL
id|shpnt-&gt;host_no
)paren
(brace
id|retval-&gt;next
op_assign
id|shpnt
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* want all to see these writes in this order */
id|scsi_hostlist
op_assign
id|retval
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|o_shp
op_assign
id|shpnt
comma
id|shpnt
op_assign
id|shpnt-&gt;next
suffix:semicolon
id|shpnt
suffix:semicolon
id|o_shp
op_assign
id|shpnt
comma
id|shpnt
op_assign
id|shpnt-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|retval-&gt;host_no
OL
id|shpnt-&gt;host_no
)paren
(brace
id|retval-&gt;next
op_assign
id|shpnt
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|o_shp-&gt;next
op_assign
id|retval
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|shpnt
)paren
id|o_shp-&gt;next
op_assign
id|retval
suffix:semicolon
)brace
)brace
r_return
id|retval
suffix:semicolon
)brace
)def_block
r_int
DECL|function|scsi_register_device
id|scsi_register_device
c_func
(paren
r_struct
id|Scsi_Device_Template
op_star
id|sdpnt
)paren
(brace
r_if
c_cond
(paren
id|sdpnt-&gt;next
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Device already registered&quot;
)paren
suffix:semicolon
)brace
id|sdpnt-&gt;next
op_assign
id|scsi_devicelist
suffix:semicolon
id|scsi_devicelist
op_assign
id|sdpnt
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
