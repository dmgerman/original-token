multiline_comment|/*&n; *&t;hosts.c Copyright (C) 1992 Drew Eckhardt &n; *&t;mid to lowlevel SCSI driver interface by&n; *&t;&t;Drew Eckhardt &n; *&n; *&t;&lt;drew@colorado.edu&gt;&n; */
multiline_comment|/*&n; *&t;This file contains the medium level SCSI&n; *&t;host interface initialization, as well as the scsi_hosts array of SCSI&n; *&t;hosts currently present in the system. &n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_SCSI
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#ifndef NULL 
DECL|macro|NULL
mdefine_line|#define NULL 0L
macro_line|#endif
macro_line|#ifdef FIGURE_MAX_SCSI_HOSTS
DECL|macro|MAX_SCSI_HOSTS
mdefine_line|#define MAX_SCSI_HOSTS
macro_line|#endif
macro_line|#include &quot;hosts.h&quot;
macro_line|#ifdef CONFIG_SCSI_AHA1542
macro_line|#include &quot;aha1542.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_FUTURE_DOMAIN
macro_line|#include &quot;fdomain.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_SEAGATE
macro_line|#include &quot;seagate.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_ULTRASTOR
macro_line|#include &quot;ultrastor.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_7000FASST
macro_line|#include &quot;7000fasst.h&quot;
macro_line|#endif
multiline_comment|/*&n;static const char RCSid[] = &quot;$Header: /usr/src/linux/kernel/blk_drv/scsi/RCS/hosts.c,v 1.1 1992/07/24 06:27:38 root Exp root $&quot;;&n;*/
multiline_comment|/*&n; *&t;The scsi host entries should be in the order you wish the &n; *&t;cards to be detected.  A driver may appear more than once IFF&n; *&t;it can deal with being detected (and therefore initialized) &n; *&t;with more than one simulatenous host number, can handle being&n; *&t;rentrant, etc.&n; *&n; *&t;They may appear in any order, as each SCSI host  is told which host number it is&n; *&t;during detection.&n; */
multiline_comment|/*&n; *&t;When figure is run, we don&squot;t want to link to any object code.  Since &n; *&t;the macro for each host will contain function pointers, we cannot &n; *&t;use it and instead must use a &quot;blank&quot; that does no such &n; *&t;idiocy.&n; */
macro_line|#ifdef FIGURE_MAX_SCSI_HOSTS
DECL|macro|BLANKIFY
mdefine_line|#define BLANKIFY(what) BLANK_HOST
macro_line|#else
DECL|macro|BLANKIFY
mdefine_line|#define BLANKIFY(what) what
macro_line|#endif
DECL|variable|scsi_hosts
id|Scsi_Host
id|scsi_hosts
(braket
)braket
op_assign
(brace
macro_line|#ifdef CONFIG_SCSI_AHA1542
id|BLANKIFY
c_func
(paren
id|AHA1542
)paren
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_FUTURE_DOMAIN
id|BLANKIFY
c_func
(paren
id|FDOMAIN_16X0
)paren
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_SEAGATE
id|BLANKIFY
c_func
(paren
id|SEAGATE_ST0X
)paren
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_ULTRASTOR
id|BLANKIFY
c_func
(paren
id|ULTRASTOR_14F
)paren
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_7000FASST
id|BLANKIFY
c_func
(paren
id|WD7000FASST
)paren
comma
macro_line|#endif
)brace
suffix:semicolon
macro_line|#ifdef FIGURE_MAX_SCSI_HOSTS
DECL|macro|MAX_SCSI_HOSTS
macro_line|#undef MAX_SCSI_HOSTS
DECL|macro|MAX_SCSI_HOSTS
mdefine_line|#define  MAX_SCSI_HOSTS  (sizeof(scsi_hosts) / sizeof(Scsi_Host))
macro_line|#endif
macro_line|#ifdef FIGURE_MAX_SCSI_HOSTS
macro_line|#include &lt;stdio.h&gt;
DECL|function|main
r_void
id|main
(paren
r_void
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;%d&quot;
comma
id|MAX_SCSI_HOSTS
)paren
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/*&n; *&t;Our semaphores and timeout counters, where size depends on MAX_SCSI_HOSTS here. &n; */
DECL|variable|host_busy
r_volatile
r_int
r_char
id|host_busy
(braket
id|MAX_SCSI_HOSTS
)braket
suffix:semicolon
DECL|variable|host_timeout
r_volatile
r_int
id|host_timeout
(braket
id|MAX_SCSI_HOSTS
)braket
suffix:semicolon
DECL|variable|host_queue
r_volatile
id|Scsi_Cmnd
op_star
id|host_queue
(braket
id|MAX_SCSI_HOSTS
)braket
suffix:semicolon
DECL|function|scsi_init
r_void
id|scsi_init
c_func
(paren
r_void
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
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|called
)paren
(brace
id|called
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
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
)paren
(brace
multiline_comment|/*&n; * Initialize our semaphores.  -1 is interpreted to mean &n; * &quot;inactive&quot; - where as 0 will indicate a time out condition.&n; */
id|host_busy
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|host_timeout
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|host_queue
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|scsi_hosts
(braket
id|i
)braket
dot
id|detect
)paren
op_logical_and
(paren
id|scsi_hosts
(braket
id|i
)braket
dot
id|present
op_assign
id|scsi_hosts
(braket
id|i
)braket
dot
id|detect
c_func
(paren
id|i
)paren
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;scsi%d : %s.&bslash;n&bslash;r&quot;
comma
id|count
comma
id|scsi_hosts
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;%s&quot;
comma
id|scsi_hosts
(braket
id|i
)braket
dot
id|info
c_func
(paren
)paren
)paren
suffix:semicolon
op_increment
id|count
suffix:semicolon
)brace
)brace
id|printk
(paren
l_string|&quot;scsi : %d hosts. &bslash;n&bslash;r&quot;
comma
id|count
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
macro_line|#else
DECL|function|main
r_void
id|main
c_func
(paren
r_void
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;0&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif&t;
eof
