multiline_comment|/*&n; *  hosts.c Copyright (C) 1992 Drew Eckhardt&n; *          Copyright (C) 1993, 1994, 1995 Eric Youngdale&n; *&n; *  mid to lowlevel SCSI driver interface&n; *      Initial versions: Drew Eckhardt&n; *      Subsequent revisions: Eric Youngdale&n; *&n; *  &lt;drew@colorado.edu&gt;&n; */
multiline_comment|/*&n; *  This file contains the medium level SCSI&n; *  host interface initialization, as well as the scsi_hosts array of SCSI&n; *  hosts currently present in the system.&n; */
multiline_comment|/*&n; * Don&squot;t import our own symbols, as this would severely mess up our&n; * symbol tables.&n; */
DECL|macro|_SCSI_SYMS_VER_
mdefine_line|#define _SCSI_SYMS_VER_
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0L
macro_line|#endif
DECL|macro|HOSTS_C
mdefine_line|#define HOSTS_C
macro_line|#include &quot;hosts.h&quot;
macro_line|#ifdef CONFIG_SCSI_AHA152X
macro_line|#include &quot;aha152x.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_AHA1542
macro_line|#include &quot;aha1542.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_AHA1740
macro_line|#include &quot;aha1740.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_AIC7XXX
macro_line|#include &quot;aic7xxx.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_BUSLOGIC
macro_line|#include &quot;BusLogic.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_EATA_DMA
macro_line|#include &quot;eata_dma.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_EATA_PIO
macro_line|#include &quot;eata_pio.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_U14_34F
macro_line|#include &quot;u14-34f.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_FUTURE_DOMAIN
macro_line|#include &quot;fdomain.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_GENERIC_NCR5380
macro_line|#include &quot;g_NCR5380.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_IN2000
macro_line|#include &quot;in2000.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_PAS16
macro_line|#include &quot;pas16.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_QLOGIC
macro_line|#include &quot;qlogic.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_SEAGATE
macro_line|#include &quot;seagate.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_T128
macro_line|#include &quot;t128.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_NCR53C7xx
macro_line|#include &quot;53c7,8xx.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_ULTRASTOR
macro_line|#include &quot;ultrastor.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_7000FASST
macro_line|#include &quot;wd7000.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_EATA
macro_line|#include &quot;eata.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_NCR53C406A
macro_line|#include &quot;NCR53c406a.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_DEBUG
macro_line|#include &quot;scsi_debug.h&quot;
macro_line|#endif
multiline_comment|/*&n;static const char RCSid[] = &quot;$Header: /usr/src/linux/kernel/blk_drv/scsi/RCS/hosts.c,v 1.3 1993/09/24 12:21:00 drew Exp drew $&quot;;&n;*/
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
DECL|variable|builtin_scsi_hosts
r_static
id|Scsi_Host_Template
id|builtin_scsi_hosts
(braket
)braket
op_assign
(brace
multiline_comment|/* BusLogic must come before aha1542.c */
macro_line|#ifdef CONFIG_SCSI_BUSLOGIC
id|BUSLOGIC
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_U14_34F
id|ULTRASTOR_14_34F
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_ULTRASTOR
id|ULTRASTOR_14F
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_AHA152X
id|AHA152X
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_AHA1542
id|AHA1542
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_AHA1740
id|AHA1740
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_AIC7XXX
id|AIC7XXX
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_FUTURE_DOMAIN
id|FDOMAIN_16X0
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_IN2000
id|IN2000
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_GENERIC_NCR5380
id|GENERIC_NCR5380
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_NCR53C406A&t;/* 53C406A should come before QLOGIC */
id|NCR53c406a
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_QLOGIC
id|QLOGIC
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_PAS16
id|MV_PAS16
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_SEAGATE
id|SEAGATE_ST0X
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_T128
id|TRANTOR_T128
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_NCR53C7xx
id|NCR53c7xx
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_EATA_DMA
id|EATA_DMA
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_EATA_PIO
id|EATA_PIO
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_7000FASST
id|WD7000
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_EATA
id|EATA
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_DEBUG
id|SCSI_DEBUG
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|MAX_SCSI_HOSTS
mdefine_line|#define MAX_SCSI_HOSTS (sizeof(builtin_scsi_hosts) / sizeof(Scsi_Host_Template))
multiline_comment|/*&n; *  Our semaphores and timeout counters, where size depends on &n; *      MAX_SCSI_HOSTS here.&n; */
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
multiline_comment|/* If we are removing the last host registered, it is safe to reuse&n;     * its host number (this avoids &quot;holes&quot; at boot time) (DB) &n;     */
r_if
c_cond
(paren
id|max_scsi_hosts
op_eq
id|next_scsi_host
op_logical_and
op_logical_neg
id|scsi_loadable_module_flag
)paren
id|max_scsi_hosts
op_decrement
suffix:semicolon
id|next_scsi_host
op_decrement
suffix:semicolon
id|scsi_init_free
c_func
(paren
(paren
r_char
op_star
)paren
id|sh
comma
r_sizeof
(paren
r_struct
id|Scsi_Host
)paren
op_plus
id|sh-&gt;extra_bytes
)paren
suffix:semicolon
)brace
)def_block
multiline_comment|/* We call this when we come across a new host adapter. We only do this&n; * once we are 100% sure that we want to use this host adapter -  it is a&n; * pain to reverse this, so we try and avoid it &n; */
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
suffix:semicolon
id|retval
op_assign
(paren
r_struct
id|Scsi_Host
op_star
)paren
id|scsi_init_malloc
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
id|retval-&gt;host_busy
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;block
op_assign
l_int|NULL
suffix:semicolon
id|retval-&gt;wish_block
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
id|scsi_loadable_module_flag
suffix:semicolon
id|retval-&gt;host_no
op_assign
id|max_scsi_hosts
op_increment
suffix:semicolon
multiline_comment|/* never reuse host_no (DB) */
id|next_scsi_host
op_increment
suffix:semicolon
id|retval-&gt;host_queue
op_assign
l_int|NULL
suffix:semicolon
id|retval-&gt;host_wait
op_assign
l_int|NULL
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
r_while
c_loop
(paren
id|shpnt-&gt;next
)paren
(brace
id|shpnt
op_assign
id|shpnt-&gt;next
suffix:semicolon
)brace
id|shpnt-&gt;next
op_assign
id|retval
suffix:semicolon
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
DECL|function|scsi_init
r_int
r_int
id|scsi_init
c_func
(paren
)paren
(brace
r_static
r_int
id|called
op_assign
l_int|0
suffix:semicolon
r_int
id|i
comma
id|pcount
suffix:semicolon
id|Scsi_Host_Template
op_star
id|tpnt
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|shpnt
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
r_if
c_cond
(paren
id|called
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|called
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|tpnt
op_assign
op_amp
id|builtin_scsi_hosts
(braket
l_int|0
)braket
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_SCSI_HOSTS
suffix:semicolon
op_increment
id|i
comma
id|tpnt
op_increment
)paren
(brace
multiline_comment|/*&n;&t; * Initialize our semaphores.  -1 is interpreted to mean&n;&t; * &quot;inactive&quot; - where as 0 will indicate a time out condition.&n;&t; */
id|pcount
op_assign
id|next_scsi_host
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tpnt-&gt;detect
)paren
op_logical_and
(paren
id|tpnt-&gt;present
op_assign
id|tpnt
op_member_access_from_pointer
id|detect
c_func
(paren
id|tpnt
)paren
)paren
)paren
(brace
multiline_comment|/* The only time this should come up is when people use&n;&t;     * some kind of patched driver of some kind or another. */
r_if
c_cond
(paren
id|pcount
op_eq
id|next_scsi_host
)paren
(brace
r_if
c_cond
(paren
id|tpnt-&gt;present
OG
l_int|1
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Failure to register low-level scsi driver&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* The low-level driver failed to register a driver.  We&n;&t;&t; * can do this now. */
id|scsi_register
c_func
(paren
id|tpnt
comma
l_int|0
)paren
suffix:semicolon
)brace
id|tpnt-&gt;next
op_assign
id|scsi_hosts
suffix:semicolon
id|scsi_hosts
op_assign
id|tpnt
suffix:semicolon
multiline_comment|/* Add the driver to /proc/scsi */
macro_line|#if CONFIG_PROC_FS 
id|build_proc_dir_entries
c_func
(paren
id|tpnt
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
r_for
c_loop
(paren
id|shpnt
op_assign
id|scsi_hostlist
suffix:semicolon
id|shpnt
suffix:semicolon
id|shpnt
op_assign
id|shpnt-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|shpnt-&gt;hostt-&gt;info
)paren
(brace
id|name
op_assign
id|shpnt-&gt;hostt
op_member_access_from_pointer
id|info
c_func
(paren
id|shpnt
)paren
suffix:semicolon
)brace
r_else
id|name
op_assign
id|shpnt-&gt;hostt-&gt;name
suffix:semicolon
id|printk
(paren
l_string|&quot;scsi%d : %s&bslash;n&quot;
comma
multiline_comment|/* And print a little message */
id|shpnt-&gt;host_no
comma
id|name
)paren
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;scsi : %d host%s.&bslash;n&quot;
comma
id|next_scsi_host
comma
(paren
id|next_scsi_host
op_eq
l_int|1
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|scsi_make_blocked_list
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Now attach the high level drivers */
macro_line|#ifdef CONFIG_BLK_DEV_SD
id|scsi_register_device
c_func
(paren
op_amp
id|sd_template
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_SR
id|scsi_register_device
c_func
(paren
op_amp
id|sr_template
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_CHR_DEV_ST
id|scsi_register_device
c_func
(paren
op_amp
id|st_template
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_CHR_DEV_SG
id|scsi_register_device
c_func
(paren
op_amp
id|sg_template
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if 0      
id|max_scsi_hosts
op_assign
id|next_scsi_host
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
