multiline_comment|/* &n;&t;pg.c    (c) 1998  Grant R. Guenther &lt;grant@torque.net&gt;&n;&t;&t;&t;  Under the terms of the GNU public license.&n;&n;&t;The pg driver provides a simple character device interface for&n;&t;sending ATAPI commands to a device.  With the exception of the&n;&t;ATAPI reset operation, all operations are performed by a pair&n;&t;of read and write operations to the appropriate /dev/pgN device.&n;&t;A write operation delivers a command and any outbound data in&n;&t;a single buffer.  Normally, the write will succeed unless the&n;&t;device is offline or malfunctioning, or there is already another&n;&t;command pending.  If the write succeeds, it should be followed&n;&t;immediately by a read operation, to obtain any returned data and&n;&t;status information.  A read will fail if there is no operation&n;&t;in progress.&n;&n;&t;As a special case, the device can be reset with a write operation,&n;&t;and in this case, no following read is expected, or permitted.&n;&n;&t;There are no ioctl() operations.  Any single operation&n;&t;may transfer at most PG_MAX_DATA bytes.  Note that the driver must&n;&t;copy the data through an internal buffer.  In keeping with all&n;&t;current ATAPI devices, command packets are assumed to be exactly&n;&t;12 bytes in length.&n;&n;&t;To permit future changes to this interface, the headers in the&n;&t;read and write buffers contain a single character &quot;magic&quot; flag.&n;&t;Currently this flag must be the character &quot;P&quot;.&n;&n;&t;By default, the driver will autoprobe for a single parallel&n;&t;port ATAPI device, but if their individual parameters are&n;&t;specified, the driver can handle up to 4 devices.&n;&n;&t;To use this device, you must have the following device &n;&t;special files defined:&n;&n;&t;&t;/dev/pg0 c 97 0&n;&t;&t;/dev/pg1 c 97 1&n;&t;&t;/dev/pg2 c 97 2&n;&t;&t;/dev/pg3 c 97 3&n;&n;&t;(You&squot;ll need to change the 97 to something else if you use&n;&t;the &squot;major&squot; parameter to install the driver on a different&n;&t;major number.)&n;&n;&t;The behaviour of the pg driver can be altered by setting&n;&t;some parameters from the insmod command line.  The following&n;&t;parameters are adjustable:&n;&n;&t;    drive0      These four arguments can be arrays of       &n;&t;    drive1      1-6 integers as follows:&n;&t;    drive2&n;&t;    drive3      &lt;prt&gt;,&lt;pro&gt;,&lt;uni&gt;,&lt;mod&gt;,&lt;slv&gt;,&lt;dly&gt;&n;&n;&t;&t;&t;Where,&n;&n;&t;&t;&lt;prt&gt;   is the base of the parallel port address for&n;&t;&t;&t;the corresponding drive.  (required)&n;&n;&t;&t;&lt;pro&gt;   is the protocol number for the adapter that&n;&t;&t;&t;supports this drive.  These numbers are&n;&t;&t;&t;logged by &squot;paride&squot; when the protocol modules&n;&t;&t;&t;are initialised.  (0 if not given)&n;&n;&t;&t;&lt;uni&gt;   for those adapters that support chained&n;&t;&t;&t;devices, this is the unit selector for the&n;&t;&t;&t;chain of devices on the given port.  It should&n;&t;&t;&t;be zero for devices that don&squot;t support chaining.&n;&t;&t;&t;(0 if not given)&n;&n;&t;&t;&lt;mod&gt;   this can be -1 to choose the best mode, or one&n;&t;&t;&t;of the mode numbers supported by the adapter.&n;&t;&t;&t;(-1 if not given)&n;&n;&t;&t;&lt;slv&gt;   ATAPI devices can be jumpered to master or slave.&n;&t;&t;&t;Set this to 0 to choose the master drive, 1 to&n;&t;&t;&t;choose the slave, -1 (the default) to choose the&n;&t;&t;&t;first drive found.&n;&n;&t;&t;&lt;dly&gt;   some parallel ports require the driver to &n;&t;&t;&t;go more slowly.  -1 sets a default value that&n;&t;&t;&t;should work with the chosen protocol.  Otherwise,&n;&t;&t;&t;set this to a small integer, the larger it is&n;&t;&t;&t;the slower the port i/o.  In some cases, setting&n;&t;&t;&t;this to zero will speed up the device. (default -1)&n;&n;&t;    major&t;You may use this parameter to overide the&n;&t;&t;&t;default major number (97) that this driver&n;&t;&t;&t;will use.  Be sure to change the device&n;&t;&t;&t;name as well.&n;&n;&t;    name&t;This parameter is a character string that&n;&t;&t;&t;contains the name the kernel will use for this&n;&t;&t;&t;device (in /proc output, for instance).&n;&t;&t;&t;(default &quot;pg&quot;).&n;&n;&t;    verbose     This parameter controls the amount of logging&n;&t;&t;&t;that is done by the driver.  Set it to 0 for &n;&t;&t;&t;quiet operation, to 1 to enable progress&n;&t;&t;&t;messages while the driver probes for devices,&n;&t;&t;&t;or to 2 for full debug logging.  (default 0)&n;&n;&t;If this driver is built into the kernel, you can use &n;&t;the following command line parameters, with the same values&n;&t;as the corresponding module parameters listed above:&n;&n;&t;    pg.drive0&n;&t;    pg.drive1&n;&t;    pg.drive2&n;&t;    pg.drive3&n;&n;&t;In addition, you can use the parameter pg.disable to disable&n;&t;the driver entirely.&n;&n;*/
multiline_comment|/* Changes:&n;&n;&t;1.01&t;GRG 1998.06.16&t;Bug fixes&n;&t;1.02    GRG 1998.09.24  Added jumbo support&n;&n;*/
DECL|macro|PG_VERSION
mdefine_line|#define PG_VERSION      &quot;1.02&quot;
DECL|macro|PG_MAJOR
mdefine_line|#define PG_MAJOR&t;97
DECL|macro|PG_NAME
mdefine_line|#define PG_NAME&t;&t;&quot;pg&quot;
DECL|macro|PG_UNITS
mdefine_line|#define PG_UNITS&t;4
macro_line|#ifndef PI_PG
DECL|macro|PI_PG
mdefine_line|#define PI_PG&t;4
macro_line|#endif
multiline_comment|/* Here are things one can override from the insmod command.&n;   Most are autoprobed by paride unless set here.  Verbose is 0&n;   by default.&n;&n;*/
DECL|variable|verbose
r_static
r_int
id|verbose
op_assign
l_int|0
suffix:semicolon
DECL|variable|major
r_static
r_int
id|major
op_assign
id|PG_MAJOR
suffix:semicolon
DECL|variable|name
r_static
r_char
op_star
id|name
op_assign
id|PG_NAME
suffix:semicolon
DECL|variable|disable
r_static
r_int
id|disable
op_assign
l_int|0
suffix:semicolon
DECL|variable|drive0
r_static
r_int
id|drive0
(braket
l_int|6
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|drive1
r_static
r_int
id|drive1
(braket
l_int|6
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|drive2
r_static
r_int
id|drive2
(braket
l_int|6
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|drive3
r_static
r_int
id|drive3
(braket
l_int|6
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|drives
r_static
r_int
(paren
op_star
id|drives
(braket
l_int|4
)braket
)paren
(braket
l_int|6
)braket
op_assign
(brace
op_amp
id|drive0
comma
op_amp
id|drive1
comma
op_amp
id|drive2
comma
op_amp
id|drive3
)brace
suffix:semicolon
DECL|variable|pg_drive_count
r_static
r_int
id|pg_drive_count
suffix:semicolon
DECL|macro|D_PRT
mdefine_line|#define D_PRT   0
DECL|macro|D_PRO
mdefine_line|#define D_PRO   1
DECL|macro|D_UNI
mdefine_line|#define D_UNI   2
DECL|macro|D_MOD
mdefine_line|#define D_MOD   3
DECL|macro|D_SLV
mdefine_line|#define D_SLV   4
DECL|macro|D_DLY
mdefine_line|#define D_DLY   5
DECL|macro|DU
mdefine_line|#define DU              (*drives[unit])
multiline_comment|/* end of parameters */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/mtio.h&gt;
macro_line|#include &lt;linux/pg.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#ifndef MODULE
macro_line|#include &quot;setup.h&quot;
DECL|variable|pg_stt
r_static
id|STT
id|pg_stt
(braket
l_int|5
)braket
op_assign
(brace
(brace
l_string|&quot;drive0&quot;
comma
l_int|6
comma
id|drive0
)brace
comma
(brace
l_string|&quot;drive1&quot;
comma
l_int|6
comma
id|drive1
)brace
comma
(brace
l_string|&quot;drive2&quot;
comma
l_int|6
comma
id|drive2
)brace
comma
(brace
l_string|&quot;drive3&quot;
comma
l_int|6
comma
id|drive3
)brace
comma
(brace
l_string|&quot;disable&quot;
comma
l_int|1
comma
op_amp
id|disable
)brace
)brace
suffix:semicolon
DECL|function|pg_setup
r_void
id|pg_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
(brace
id|generic_setup
c_func
(paren
id|pg_stt
comma
l_int|5
comma
id|str
)paren
suffix:semicolon
)brace
macro_line|#endif
id|MODULE_PARM
c_func
(paren
id|verbose
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|major
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|name
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|drive0
comma
l_string|&quot;1-6i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|drive1
comma
l_string|&quot;1-6i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|drive2
comma
l_string|&quot;1-6i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|drive3
comma
l_string|&quot;1-6i&quot;
)paren
suffix:semicolon
macro_line|#include &quot;paride.h&quot;
DECL|macro|PG_SPIN_DEL
mdefine_line|#define PG_SPIN_DEL     50              /* spin delay in micro-seconds  */
DECL|macro|PG_SPIN
mdefine_line|#define PG_SPIN         200
DECL|macro|PG_TMO
mdefine_line|#define PG_TMO&t;&t;HZ
DECL|macro|PG_RESET_TMO
mdefine_line|#define PG_RESET_TMO&t;10*HZ
DECL|macro|STAT_ERR
mdefine_line|#define STAT_ERR        0x01
DECL|macro|STAT_INDEX
mdefine_line|#define STAT_INDEX      0x02
DECL|macro|STAT_ECC
mdefine_line|#define STAT_ECC        0x04
DECL|macro|STAT_DRQ
mdefine_line|#define STAT_DRQ        0x08
DECL|macro|STAT_SEEK
mdefine_line|#define STAT_SEEK       0x10
DECL|macro|STAT_WRERR
mdefine_line|#define STAT_WRERR      0x20
DECL|macro|STAT_READY
mdefine_line|#define STAT_READY      0x40
DECL|macro|STAT_BUSY
mdefine_line|#define STAT_BUSY       0x80
DECL|macro|ATAPI_IDENTIFY
mdefine_line|#define ATAPI_IDENTIFY&t;&t;0x12
r_int
id|pg_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef MODULE
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_static
r_int
id|pg_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_static
r_int
id|pg_release
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
r_static
id|ssize_t
id|pg_read
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
suffix:semicolon
r_static
id|ssize_t
id|pg_write
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
suffix:semicolon
r_static
r_int
id|pg_detect
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|pg_identify
(paren
r_int
id|unit
comma
r_int
id|log
)paren
suffix:semicolon
DECL|macro|PG_NAMELEN
mdefine_line|#define PG_NAMELEN      8
DECL|struct|pg_unit
r_struct
id|pg_unit
(brace
DECL|member|pia
r_struct
id|pi_adapter
id|pia
suffix:semicolon
multiline_comment|/* interface to paride layer */
DECL|member|pi
r_struct
id|pi_adapter
op_star
id|pi
suffix:semicolon
DECL|member|busy
r_int
id|busy
suffix:semicolon
multiline_comment|/* write done, read expected */
DECL|member|start
r_int
id|start
suffix:semicolon
multiline_comment|/* jiffies at command start */
DECL|member|dlen
r_int
id|dlen
suffix:semicolon
multiline_comment|/* transfer size requested */
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
multiline_comment|/* timeout requested */
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* last sense key */
DECL|member|drive
r_int
id|drive
suffix:semicolon
multiline_comment|/* drive */
DECL|member|access
r_int
id|access
suffix:semicolon
multiline_comment|/* count of active opens ... */
DECL|member|present
r_int
id|present
suffix:semicolon
multiline_comment|/* device present ? */
DECL|member|bufptr
r_char
op_star
id|bufptr
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|PG_NAMELEN
)braket
suffix:semicolon
multiline_comment|/* pg0, pg1, ... */
)brace
suffix:semicolon
DECL|variable|pg
r_struct
id|pg_unit
id|pg
(braket
id|PG_UNITS
)braket
suffix:semicolon
multiline_comment|/*  &squot;unit&squot; must be defined in all functions - either as a local or a param */
DECL|macro|PG
mdefine_line|#define PG pg[unit]
DECL|macro|PI
mdefine_line|#define PI PG.pi
DECL|variable|pg_scratch
r_static
r_char
id|pg_scratch
(braket
l_int|512
)braket
suffix:semicolon
multiline_comment|/* scratch block buffer */
multiline_comment|/* kernel glue structures */
DECL|variable|pg_fops
r_static
r_struct
id|file_operations
id|pg_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|pg_read
comma
multiline_comment|/* read */
id|pg_write
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir - bad */
l_int|NULL
comma
multiline_comment|/* select */
l_int|NULL
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
id|pg_open
comma
multiline_comment|/* open */
l_int|NULL
comma
multiline_comment|/* flush */
id|pg_release
comma
multiline_comment|/* release */
l_int|NULL
comma
multiline_comment|/* fsync */
l_int|NULL
comma
multiline_comment|/* fasync */
l_int|NULL
comma
multiline_comment|/* media change ? */
l_int|NULL
multiline_comment|/* revalidate new media */
)brace
suffix:semicolon
DECL|function|pg_init_units
r_void
id|pg_init_units
c_func
(paren
r_void
)paren
(brace
r_int
id|unit
comma
id|j
suffix:semicolon
id|pg_drive_count
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|unit
op_assign
l_int|0
suffix:semicolon
id|unit
OL
id|PG_UNITS
suffix:semicolon
id|unit
op_increment
)paren
(brace
id|PG.pi
op_assign
op_amp
id|PG.pia
suffix:semicolon
id|PG.access
op_assign
l_int|0
suffix:semicolon
id|PG.busy
op_assign
l_int|0
suffix:semicolon
id|PG.present
op_assign
l_int|0
suffix:semicolon
id|PG.bufptr
op_assign
l_int|NULL
suffix:semicolon
id|PG.drive
op_assign
id|DU
(braket
id|D_SLV
)braket
suffix:semicolon
id|j
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|j
OL
id|PG_NAMELEN
op_minus
l_int|2
)paren
op_logical_and
(paren
id|PG.name
(braket
id|j
)braket
op_assign
id|name
(braket
id|j
)braket
)paren
)paren
id|j
op_increment
suffix:semicolon
id|PG.name
(braket
id|j
op_increment
)braket
op_assign
l_char|&squot;0&squot;
op_plus
id|unit
suffix:semicolon
id|PG.name
(braket
id|j
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|DU
(braket
id|D_PRT
)braket
)paren
id|pg_drive_count
op_increment
suffix:semicolon
)brace
)brace
DECL|function|pg_init
r_int
id|pg_init
(paren
r_void
)paren
multiline_comment|/* preliminary initialisation */
(brace
r_int
id|unit
suffix:semicolon
r_if
c_cond
(paren
id|disable
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|pg_init_units
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pg_detect
c_func
(paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|major
comma
id|name
comma
op_amp
id|pg_fops
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pg_init: unable to get major number %d&bslash;n&quot;
comma
id|major
)paren
suffix:semicolon
r_for
c_loop
(paren
id|unit
op_assign
l_int|0
suffix:semicolon
id|unit
OL
id|PG_UNITS
suffix:semicolon
id|unit
op_increment
)paren
r_if
c_cond
(paren
id|PG.present
)paren
id|pi_release
c_func
(paren
id|PI
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
multiline_comment|/* Glue for modules ... */
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
macro_line|#ifdef PARIDE_JUMBO
(brace
r_extern
id|paride_init
c_func
(paren
)paren
suffix:semicolon
id|paride_init
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
id|err
op_assign
id|pg_init
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_int
id|unit
suffix:semicolon
id|unregister_chrdev
c_func
(paren
id|major
comma
id|name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|unit
op_assign
l_int|0
suffix:semicolon
id|unit
OL
id|PG_UNITS
suffix:semicolon
id|unit
op_increment
)paren
r_if
c_cond
(paren
id|PG.present
)paren
id|pi_release
c_func
(paren
id|PI
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|WR
mdefine_line|#define&t;WR(c,r,v)&t;pi_write_regr(PI,c,r,v)
DECL|macro|RR
mdefine_line|#define&t;RR(c,r)&t;&t;(pi_read_regr(PI,c,r))
DECL|macro|DRIVE
mdefine_line|#define DRIVE           (0xa0+0x10*PG.drive)
DECL|function|pg_sleep
r_static
r_void
id|pg_sleep
c_func
(paren
r_int
id|cs
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|cs
)paren
suffix:semicolon
)brace
DECL|function|pg_wait
r_static
r_int
id|pg_wait
c_func
(paren
r_int
id|unit
comma
r_int
id|go
comma
r_int
id|stop
comma
r_int
id|tmo
comma
r_char
op_star
id|msg
)paren
(brace
r_int
id|j
comma
id|r
comma
id|e
comma
id|s
comma
id|p
suffix:semicolon
id|PG.status
op_assign
l_int|0
suffix:semicolon
id|j
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
(paren
id|r
op_assign
id|RR
c_func
(paren
l_int|1
comma
l_int|6
)paren
)paren
op_amp
id|go
)paren
op_logical_or
(paren
id|stop
op_logical_and
(paren
op_logical_neg
(paren
id|r
op_amp
id|stop
)paren
)paren
)paren
)paren
op_logical_and
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|tmo
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|j
op_increment
OL
id|PG_SPIN
)paren
id|udelay
c_func
(paren
id|PG_SPIN_DEL
)paren
suffix:semicolon
r_else
id|pg_sleep
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|r
op_amp
(paren
id|STAT_ERR
op_amp
id|stop
)paren
)paren
op_logical_or
id|time_after_eq
c_func
(paren
id|jiffies
comma
id|tmo
)paren
)paren
(brace
id|s
op_assign
id|RR
c_func
(paren
l_int|0
comma
l_int|7
)paren
suffix:semicolon
id|e
op_assign
id|RR
c_func
(paren
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|p
op_assign
id|RR
c_func
(paren
l_int|0
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
OG
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;%s: %s: stat=0x%x err=0x%x phase=%d%s&bslash;n&quot;
comma
id|PG.name
comma
id|msg
comma
id|s
comma
id|e
comma
id|p
comma
id|time_after_eq
c_func
(paren
id|jiffies
comma
id|tmo
)paren
ques
c_cond
l_string|&quot; timeout&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|time_after_eq
c_func
(paren
id|jiffies
comma
id|tmo
)paren
)paren
id|e
op_or_assign
l_int|0x100
suffix:semicolon
id|PG.status
op_assign
(paren
id|e
op_rshift
l_int|4
)paren
op_amp
l_int|0xff
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pg_command
r_static
r_int
id|pg_command
c_func
(paren
r_int
id|unit
comma
r_char
op_star
id|cmd
comma
r_int
id|dlen
comma
r_int
id|tmo
)paren
(brace
r_int
id|k
suffix:semicolon
id|pi_connect
c_func
(paren
id|PI
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0
comma
l_int|6
comma
id|DRIVE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pg_wait
c_func
(paren
id|unit
comma
id|STAT_BUSY
op_or
id|STAT_DRQ
comma
l_int|0
comma
id|tmo
comma
l_string|&quot;before command&quot;
)paren
)paren
(brace
id|pi_disconnect
c_func
(paren
id|PI
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|WR
c_func
(paren
l_int|0
comma
l_int|4
comma
id|dlen
op_mod
l_int|256
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0
comma
l_int|5
comma
id|dlen
op_div
l_int|256
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0
comma
l_int|7
comma
l_int|0xa0
)paren
suffix:semicolon
multiline_comment|/* ATAPI packet command */
r_if
c_cond
(paren
id|pg_wait
c_func
(paren
id|unit
comma
id|STAT_BUSY
comma
id|STAT_DRQ
comma
id|tmo
comma
l_string|&quot;command DRQ&quot;
)paren
)paren
(brace
id|pi_disconnect
c_func
(paren
id|PI
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|RR
c_func
(paren
l_int|0
comma
l_int|2
)paren
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: command phase error&bslash;n&quot;
comma
id|PG.name
)paren
suffix:semicolon
id|pi_disconnect
c_func
(paren
id|PI
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|pi_write_block
c_func
(paren
id|PI
comma
id|cmd
comma
l_int|12
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
OG
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Command sent, dlen=%d packet= &quot;
comma
id|PG.name
comma
id|dlen
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|12
suffix:semicolon
id|k
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
id|cmd
(braket
id|k
)braket
op_amp
l_int|0xff
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pg_completion
r_static
r_int
id|pg_completion
c_func
(paren
r_int
id|unit
comma
r_char
op_star
id|buf
comma
r_int
id|tmo
)paren
(brace
r_int
id|r
comma
id|d
comma
id|n
comma
id|p
suffix:semicolon
id|r
op_assign
id|pg_wait
c_func
(paren
id|unit
comma
id|STAT_BUSY
comma
id|STAT_DRQ
op_or
id|STAT_READY
op_or
id|STAT_ERR
comma
id|tmo
comma
l_string|&quot;completion&quot;
)paren
suffix:semicolon
id|PG.dlen
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|RR
c_func
(paren
l_int|0
comma
l_int|7
)paren
op_amp
id|STAT_DRQ
)paren
(brace
id|d
op_assign
(paren
id|RR
c_func
(paren
l_int|0
comma
l_int|4
)paren
op_plus
l_int|256
op_star
id|RR
c_func
(paren
l_int|0
comma
l_int|5
)paren
)paren
suffix:semicolon
id|n
op_assign
(paren
(paren
id|d
op_plus
l_int|3
)paren
op_amp
l_int|0xfffc
)paren
suffix:semicolon
id|p
op_assign
id|RR
c_func
(paren
l_int|0
comma
l_int|2
)paren
op_amp
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|0
)paren
id|pi_write_block
c_func
(paren
id|PI
comma
id|buf
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|2
)paren
id|pi_read_block
c_func
(paren
id|PI
comma
id|buf
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
OG
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;%s: %s %d bytes&bslash;n&quot;
comma
id|PG.name
comma
id|p
ques
c_cond
l_string|&quot;Read&quot;
suffix:colon
l_string|&quot;Write&quot;
comma
id|n
)paren
suffix:semicolon
id|PG.dlen
op_add_assign
(paren
l_int|1
op_minus
id|p
)paren
op_star
id|d
suffix:semicolon
id|buf
op_add_assign
id|d
suffix:semicolon
id|r
op_assign
id|pg_wait
c_func
(paren
id|unit
comma
id|STAT_BUSY
comma
id|STAT_DRQ
op_or
id|STAT_READY
op_or
id|STAT_ERR
comma
id|tmo
comma
l_string|&quot;completion&quot;
)paren
suffix:semicolon
)brace
id|pi_disconnect
c_func
(paren
id|PI
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|pg_reset
r_static
r_int
id|pg_reset
c_func
(paren
r_int
id|unit
)paren
(brace
r_int
id|i
comma
id|k
comma
id|flg
suffix:semicolon
r_int
id|expect
(braket
l_int|5
)braket
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|0x14
comma
l_int|0xeb
)brace
suffix:semicolon
id|pi_connect
c_func
(paren
id|PI
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0
comma
l_int|6
comma
id|DRIVE
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0
comma
l_int|7
comma
l_int|8
)paren
suffix:semicolon
id|pg_sleep
c_func
(paren
l_int|20
op_star
id|HZ
op_div
l_int|1000
)paren
suffix:semicolon
id|k
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|k
op_increment
OL
id|PG_RESET_TMO
)paren
op_logical_and
(paren
id|RR
c_func
(paren
l_int|1
comma
l_int|6
)paren
op_amp
id|STAT_BUSY
)paren
)paren
id|pg_sleep
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|flg
op_assign
l_int|1
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
l_int|5
suffix:semicolon
id|i
op_increment
)paren
(brace
id|flg
op_and_assign
(paren
id|RR
c_func
(paren
l_int|0
comma
id|i
op_plus
l_int|1
)paren
op_eq
id|expect
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|verbose
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Reset (%d) signature = &quot;
comma
id|PG.name
comma
id|k
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
l_int|5
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%3x&quot;
comma
id|RR
c_func
(paren
l_int|0
comma
id|i
op_plus
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|flg
)paren
id|printk
c_func
(paren
l_string|&quot; (incorrect)&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|pi_disconnect
c_func
(paren
id|PI
)paren
suffix:semicolon
r_return
id|flg
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|xs
r_static
r_void
id|xs
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
id|targ
comma
r_int
id|offs
comma
r_int
id|len
)paren
(brace
r_int
id|j
comma
id|k
comma
id|l
suffix:semicolon
id|j
op_assign
l_int|0
suffix:semicolon
id|l
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|len
suffix:semicolon
id|k
op_increment
)paren
r_if
c_cond
(paren
(paren
id|buf
(braket
id|k
op_plus
id|offs
)braket
op_ne
l_int|0x20
)paren
op_logical_or
(paren
id|buf
(braket
id|k
op_plus
id|offs
)braket
op_ne
id|l
)paren
)paren
(brace
id|l
op_assign
id|targ
(braket
id|j
op_increment
)braket
op_assign
id|buf
(braket
id|k
op_plus
id|offs
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|l
op_eq
l_int|0x20
)paren
id|j
op_decrement
suffix:semicolon
id|targ
(braket
id|j
)braket
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|pg_identify
r_static
r_int
id|pg_identify
c_func
(paren
r_int
id|unit
comma
r_int
id|log
)paren
(brace
r_int
id|s
suffix:semicolon
r_char
op_star
id|ms
(braket
l_int|2
)braket
op_assign
(brace
l_string|&quot;master&quot;
comma
l_string|&quot;slave&quot;
)brace
suffix:semicolon
r_char
id|mf
(braket
l_int|10
)braket
comma
id|id
(braket
l_int|18
)braket
suffix:semicolon
r_char
id|id_cmd
(braket
l_int|12
)braket
op_assign
(brace
id|ATAPI_IDENTIFY
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|36
comma
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
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_char
id|buf
(braket
l_int|36
)braket
suffix:semicolon
id|s
op_assign
id|pg_command
c_func
(paren
id|unit
comma
id|id_cmd
comma
l_int|36
comma
id|jiffies
op_plus
id|PG_TMO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|s
op_assign
id|pg_completion
c_func
(paren
id|unit
comma
id|buf
comma
id|jiffies
op_plus
id|PG_TMO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|log
)paren
(brace
id|xs
c_func
(paren
id|buf
comma
id|mf
comma
l_int|8
comma
l_int|8
)paren
suffix:semicolon
id|xs
c_func
(paren
id|buf
comma
id|id
comma
l_int|16
comma
l_int|16
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: %s %s, %s&bslash;n&quot;
comma
id|PG.name
comma
id|mf
comma
id|id
comma
id|ms
(braket
id|PG.drive
)braket
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pg_probe
r_static
r_int
id|pg_probe
c_func
(paren
r_int
id|unit
)paren
multiline_comment|/*&t;returns  0, with id set if drive is detected&n;&t;&t;-1, if drive detection failed&n;*/
(brace
r_if
c_cond
(paren
id|PG.drive
op_eq
op_minus
l_int|1
)paren
(brace
r_for
c_loop
(paren
id|PG.drive
op_assign
l_int|0
suffix:semicolon
id|PG.drive
op_le
l_int|1
suffix:semicolon
id|PG.drive
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|pg_reset
c_func
(paren
id|unit
)paren
)paren
r_return
id|pg_identify
c_func
(paren
id|unit
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|pg_reset
c_func
(paren
id|unit
)paren
)paren
r_return
id|pg_identify
c_func
(paren
id|unit
comma
l_int|1
)paren
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|pg_detect
r_static
r_int
id|pg_detect
c_func
(paren
r_void
)paren
(brace
r_int
id|k
comma
id|unit
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: %s version %s, major %d&bslash;n&quot;
comma
id|name
comma
id|name
comma
id|PG_VERSION
comma
id|major
)paren
suffix:semicolon
id|k
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pg_drive_count
op_eq
l_int|0
)paren
(brace
id|unit
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pi_init
c_func
(paren
id|PI
comma
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
id|pg_scratch
comma
id|PI_PG
comma
id|verbose
comma
id|PG.name
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pg_probe
c_func
(paren
id|unit
)paren
)paren
(brace
id|PG.present
op_assign
l_int|1
suffix:semicolon
id|k
op_increment
suffix:semicolon
)brace
r_else
id|pi_release
c_func
(paren
id|PI
)paren
suffix:semicolon
)brace
)brace
r_else
r_for
c_loop
(paren
id|unit
op_assign
l_int|0
suffix:semicolon
id|unit
OL
id|PG_UNITS
suffix:semicolon
id|unit
op_increment
)paren
r_if
c_cond
(paren
id|DU
(braket
id|D_PRT
)braket
)paren
r_if
c_cond
(paren
id|pi_init
c_func
(paren
id|PI
comma
l_int|0
comma
id|DU
(braket
id|D_PRT
)braket
comma
id|DU
(braket
id|D_MOD
)braket
comma
id|DU
(braket
id|D_UNI
)braket
comma
id|DU
(braket
id|D_PRO
)braket
comma
id|DU
(braket
id|D_DLY
)braket
comma
id|pg_scratch
comma
id|PI_PG
comma
id|verbose
comma
id|PG.name
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pg_probe
c_func
(paren
id|unit
)paren
)paren
(brace
id|PG.present
op_assign
l_int|1
suffix:semicolon
id|k
op_increment
suffix:semicolon
)brace
r_else
id|pi_release
c_func
(paren
id|PI
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|k
)paren
r_return
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: No ATAPI device detected&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|macro|DEVICE_NR
mdefine_line|#define DEVICE_NR(dev)&t;(MINOR(dev) % 128)
DECL|function|pg_open
r_static
r_int
id|pg_open
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|unit
op_assign
id|DEVICE_NR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|unit
op_ge
id|PG_UNITS
)paren
op_logical_or
(paren
op_logical_neg
id|PG.present
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|PG.access
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|PG.access
OG
l_int|1
)paren
(brace
id|PG.access
op_decrement
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|MOD_INC_USE_COUNT
suffix:semicolon
r_if
c_cond
(paren
id|PG.busy
)paren
(brace
id|pg_reset
c_func
(paren
id|unit
)paren
suffix:semicolon
id|PG.busy
op_assign
l_int|0
suffix:semicolon
)brace
id|pg_identify
c_func
(paren
id|unit
comma
(paren
id|verbose
OG
l_int|1
)paren
)paren
suffix:semicolon
id|PG.bufptr
op_assign
id|kmalloc
c_func
(paren
id|PG_MAX_DATA
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PG.bufptr
op_eq
l_int|NULL
)paren
(brace
id|PG.access
op_decrement
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: buffer allocation failed&bslash;n&quot;
comma
id|PG.name
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pg_release
r_static
r_int
id|pg_release
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|unit
op_assign
id|DEVICE_NR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|unit
op_ge
id|PG_UNITS
)paren
op_logical_or
(paren
id|PG.access
op_le
l_int|0
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|PG.access
op_decrement
suffix:semicolon
id|kfree
c_func
(paren
id|PG.bufptr
)paren
suffix:semicolon
id|PG.bufptr
op_assign
l_int|NULL
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pg_write
r_static
id|ssize_t
id|pg_write
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|ino
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|unit
op_assign
id|DEVICE_NR
c_func
(paren
id|ino-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|pg_write_hdr
id|hdr
suffix:semicolon
r_int
id|hs
op_assign
r_sizeof
(paren
id|hdr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PG.busy
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|hs
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|copy_from_user
c_func
(paren
(paren
r_char
op_star
)paren
op_amp
id|hdr
comma
id|buf
comma
id|hs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hdr.magic
op_ne
id|PG_MAGIC
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|hdr.dlen
OG
id|PG_MAX_DATA
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|count
op_minus
id|hs
)paren
OG
id|PG_MAX_DATA
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|hdr.func
op_eq
id|PG_RESET
)paren
(brace
r_if
c_cond
(paren
id|count
op_ne
id|hs
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|pg_reset
c_func
(paren
id|unit
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hdr.func
op_ne
id|PG_COMMAND
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|PG.start
op_assign
id|jiffies
suffix:semicolon
id|PG.timeout
op_assign
id|hdr.timeout
op_star
id|HZ
op_plus
id|HZ
op_div
l_int|2
op_plus
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|pg_command
c_func
(paren
id|unit
comma
id|hdr.packet
comma
id|hdr.dlen
comma
id|jiffies
op_plus
id|PG_TMO
)paren
)paren
(brace
r_if
c_cond
(paren
id|PG.status
op_amp
l_int|0x10
)paren
r_return
op_minus
id|ETIME
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|PG.busy
op_assign
l_int|1
suffix:semicolon
id|copy_from_user
c_func
(paren
id|PG.bufptr
comma
id|buf
op_plus
id|hs
comma
id|count
op_minus
id|hs
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|pg_read
r_static
id|ssize_t
id|pg_read
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|ino
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
id|unit
op_assign
id|DEVICE_NR
c_func
(paren
id|ino-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|pg_read_hdr
id|hdr
suffix:semicolon
r_int
id|hs
op_assign
r_sizeof
(paren
id|hdr
)paren
suffix:semicolon
r_int
id|copy
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PG.busy
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|hs
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|PG.busy
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pg_completion
c_func
(paren
id|unit
comma
id|PG.bufptr
comma
id|PG.timeout
)paren
)paren
r_if
c_cond
(paren
id|PG.status
op_amp
l_int|0x10
)paren
r_return
op_minus
id|ETIME
suffix:semicolon
id|hdr.magic
op_assign
id|PG_MAGIC
suffix:semicolon
id|hdr.dlen
op_assign
id|PG.dlen
suffix:semicolon
id|copy
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|hdr.dlen
OL
l_int|0
)paren
(brace
id|hdr.dlen
op_assign
op_minus
l_int|1
op_star
id|hdr.dlen
suffix:semicolon
id|copy
op_assign
id|hdr.dlen
suffix:semicolon
r_if
c_cond
(paren
id|copy
OG
(paren
id|count
op_minus
id|hs
)paren
)paren
id|copy
op_assign
id|count
op_minus
id|hs
suffix:semicolon
)brace
id|hdr.duration
op_assign
(paren
id|jiffies
op_minus
id|PG.start
op_plus
id|HZ
op_div
l_int|2
)paren
op_div
id|HZ
suffix:semicolon
id|hdr.scsi
op_assign
id|PG.status
op_amp
l_int|0x0f
suffix:semicolon
id|copy_to_user
c_func
(paren
id|buf
comma
(paren
r_char
op_star
)paren
op_amp
id|hdr
comma
id|hs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy
OG
l_int|0
)paren
id|copy_to_user
c_func
(paren
id|buf
op_plus
id|hs
comma
id|PG.bufptr
comma
id|copy
)paren
suffix:semicolon
r_return
id|copy
op_plus
id|hs
suffix:semicolon
)brace
multiline_comment|/* end of pg.c */
eof
