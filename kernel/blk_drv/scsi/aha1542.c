multiline_comment|/* $Id: aha1542.c,v 1.1 1992/07/24 06:27:38 root Exp root $&n; *  linux/kernel/aha1542.c&n; *&n; *  Copyright (C) 1992  Tommy Thorn&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;aha1542.h&quot;
macro_line|#ifdef DEBUG
DECL|macro|DEB
mdefine_line|#define DEB(x) x
macro_line|#else
DECL|macro|DEB
mdefine_line|#define DEB(x)
macro_line|#endif
multiline_comment|/*&n;static const char RCSid[] = &quot;$Header: /usr/src/linux/kernel/blk_drv/scsi/RCS/aha1542.c,v 1.1 1992/07/24 06:27:38 root Exp root $&quot;;&n;*/
DECL|macro|base
mdefine_line|#define base 0x330
DECL|macro|intr_chan
mdefine_line|#define intr_chan 11
DECL|variable|mb
r_static
r_struct
id|mailbox
id|mb
(braket
l_int|2
)braket
suffix:semicolon
DECL|variable|ccb
r_static
r_struct
id|ccb
id|ccb
suffix:semicolon
DECL|variable|WAITtimeout
DECL|variable|WAITnexttimeout
r_int
id|WAITtimeout
comma
id|WAITnexttimeout
op_assign
l_int|3000000
suffix:semicolon
DECL|variable|do_done
r_void
(paren
op_star
id|do_done
)paren
(paren
r_int
comma
r_int
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|aha1542_host
r_int
id|aha1542_host
op_assign
l_int|0
suffix:semicolon
r_extern
r_void
id|aha1542_interrupt
c_func
(paren
)paren
suffix:semicolon
DECL|macro|aha1542_intr_reset
mdefine_line|#define aha1542_intr_reset()  outb(IRST, CONTROL)
DECL|macro|aha1542_enable_intr
mdefine_line|#define aha1542_enable_intr() outb(inb_p(0xA1) &amp; ~8, 0xA1)
DECL|macro|aha1542_disable_intr
mdefine_line|#define aha1542_disable_intr() outb(inb_p(0xA1) | 8, 0xA1)
DECL|macro|WAIT
mdefine_line|#define WAIT(port, mask, allof, noneof)&t;&t;&t;&t;&t;&bslash;&n; { register WAITbits;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;   register WAITtimeout = WAITnexttimeout;&t;&t;&t;&t;&bslash;&n;   while (1) {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;     WAITbits = inb(port) &amp; (mask);&t;&t;&t;&t;&t;&bslash;&n;     if ((WAITbits &amp; (allof)) == (allof) &amp;&amp; ((WAITbits &amp; (noneof)) == 0)) &bslash;&n;       break;                                                         &t;&bslash;&n;     if (--WAITtimeout == 0) goto fail;&t;&t;&t;&t;&t;&bslash;&n;   }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; }
DECL|function|aha1542_stat
r_static
r_void
id|aha1542_stat
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*    int s = inb(STATUS), i = inb(INTRFLAGS);&n;  printk(&quot;status=%x intrflags=%x&bslash;n&quot;, s, i, WAITnexttimeout-WAITtimeout); */
)brace
DECL|function|aha1542_out
r_static
r_int
id|aha1542_out
c_func
(paren
id|unchar
op_star
id|cmdp
comma
r_int
id|len
)paren
(brace
r_while
c_loop
(paren
id|len
op_decrement
)paren
(brace
id|WAIT
c_func
(paren
id|STATUS
comma
id|CDF
comma
l_int|0
comma
id|CDF
)paren
suffix:semicolon
id|outb
c_func
(paren
op_star
id|cmdp
op_increment
comma
id|DATA
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|printk
c_func
(paren
l_string|&quot;aha1542_out failed(%d): &quot;
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|aha1542_stat
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|aha1542_in
r_static
r_int
id|aha1542_in
c_func
(paren
id|unchar
op_star
id|cmdp
comma
r_int
id|len
)paren
(brace
r_while
c_loop
(paren
id|len
op_decrement
)paren
(brace
id|WAIT
c_func
(paren
id|STATUS
comma
id|DF
comma
id|DF
comma
l_int|0
)paren
suffix:semicolon
op_star
id|cmdp
op_increment
op_assign
id|inb
c_func
(paren
id|DATA
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|printk
c_func
(paren
l_string|&quot;aha1542_in failed(%d): &quot;
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|aha1542_stat
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|makecode
r_int
id|makecode
c_func
(paren
r_int
id|hosterr
comma
r_int
id|scsierr
)paren
(brace
r_switch
c_cond
(paren
id|hosterr
)paren
(brace
r_case
l_int|0x0
suffix:colon
r_case
l_int|0xa
suffix:colon
multiline_comment|/* Linked command complete without error and linked normally */
r_case
l_int|0xb
suffix:colon
multiline_comment|/* Linked command complete without error, interrupt generated */
id|hosterr
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x11
suffix:colon
multiline_comment|/* Selection time out-The initiator selection or target&n;&t;&t;    reselection was not complete within the SCSI Time out period */
id|hosterr
op_assign
id|DID_TIME_OUT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x12
suffix:colon
multiline_comment|/* Data overrun/underrun-The target attempted to transfer more data&n;&t;&t;    thean was allocated by the Data Length field or the sum of the&n;&t;&t;    Scatter / Gather Data Length fields. */
r_case
l_int|0x13
suffix:colon
multiline_comment|/* Unexpected bus free-The target dropped the SCSI BSY at an unexpected time. */
r_case
l_int|0x15
suffix:colon
multiline_comment|/* MBO command was not 00, 01 or 02-The first byte of the CB was&n;&t;&t;    invalid. This usually indicates a software failure. */
r_case
l_int|0x16
suffix:colon
multiline_comment|/* Invalid CCB Operation Code-The first byte of the CCB was invalid.&n;&t;&t;    This usually indicates a software failure. */
r_case
l_int|0x17
suffix:colon
multiline_comment|/* Linked CCB does not have the same LUN-A subsequent CCB of a set&n;&t;&t;    of linked CCB&squot;s does not specify the same logical unit number as&n;&t;&t;    the first. */
r_case
l_int|0x18
suffix:colon
multiline_comment|/* Invalid Target Direction received from Host-The direction of a&n;&t;&t;    Target Mode CCB was invalid. */
r_case
l_int|0x19
suffix:colon
multiline_comment|/* Duplicate CCB Received in Target Mode-More than once CCB was&n;&t;&t;    received to service data transfer between the same target LUN&n;&t;&t;    and initiator SCSI ID in the same direction. */
r_case
l_int|0x1a
suffix:colon
multiline_comment|/* Invalid CCB or Segment List Parameter-A segment list with a zero&n;&t;&t;    length segment or invalid segment list boundaries was received.&n;&t;&t;    A CCB parameter was invalid. */
id|hosterr
op_assign
id|DID_ERROR
suffix:semicolon
multiline_comment|/* Couldn&squot;t find any better */
r_break
suffix:semicolon
r_case
l_int|0x14
suffix:colon
multiline_comment|/* Target bus phase sequence failure-An invalid bus phase or bus&n;&t;&t;    phase sequence was requested by the target. The host adapter&n;&t;&t;    will generate a SCSI Reset Condition, notifying the host with&n;&t;&t;    a SCRD interrupt */
id|hosterr
op_assign
id|DID_RESET
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;makecode: unknown hoststatus %x&bslash;n&quot;
comma
id|hosterr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|scsierr
op_or
(paren
id|hosterr
op_lshift
l_int|16
)paren
suffix:semicolon
)brace
DECL|function|aha1542_test_port
r_int
id|aha1542_test_port
c_func
(paren
r_void
)paren
(brace
r_volatile
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Reset the adapter. I ought to make a hard reset, but it&squot;s not really nessesary */
multiline_comment|/*  DEB(printk(&quot;aha1542_test_port called &bslash;n&quot;)); */
id|outb
c_func
(paren
id|SRST
op_or
id|IRST
multiline_comment|/*|SCRST*/
comma
id|CONTROL
)paren
suffix:semicolon
id|debug
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Expect INIT and IDLE, any of the others are bad */
id|WAIT
c_func
(paren
id|STATUS
comma
id|STATMASK
comma
id|INIT
op_or
id|IDLE
comma
id|STST
op_or
id|DIAGF
op_or
id|INVDCMD
op_or
id|DF
op_or
id|CDF
)paren
suffix:semicolon
id|debug
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* Shouldn&squot;t have generated any interrupts during reset */
r_if
c_cond
(paren
id|inb
c_func
(paren
id|INTRFLAGS
)paren
op_amp
id|INTRMASK
)paren
r_goto
id|fail
suffix:semicolon
id|debug
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* Test the basic ECHO command */
id|outb
c_func
(paren
id|CMD_ECHO
comma
id|DATA
)paren
suffix:semicolon
id|debug
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* Wait for CDF=0. If any of the others are set, it&squot;s bad */
id|WAIT
c_func
(paren
id|STATUS
comma
id|STATMASK
comma
l_int|0
comma
id|STST
op_or
id|DIAGF
op_or
id|INVDCMD
op_or
id|DF
op_or
id|CDF
)paren
suffix:semicolon
id|debug
op_assign
l_int|5
suffix:semicolon
multiline_comment|/* The meaning of life */
id|outb
c_func
(paren
l_int|42
comma
id|DATA
)paren
suffix:semicolon
id|debug
op_assign
l_int|6
suffix:semicolon
multiline_comment|/* Expect only DF, that is, data ready */
id|WAIT
c_func
(paren
id|STATUS
comma
id|STATMASK
comma
id|DF
comma
id|STST
op_or
id|DIAGF
op_or
id|CDF
op_or
id|INVDCMD
)paren
suffix:semicolon
id|debug
op_assign
l_int|7
suffix:semicolon
multiline_comment|/* Is the answer correct? */
r_if
c_cond
(paren
id|inb
c_func
(paren
id|DATA
)paren
op_ne
l_int|42
)paren
r_goto
id|fail
suffix:semicolon
id|debug
op_assign
l_int|8
suffix:semicolon
multiline_comment|/* Reading port should reset DF */
r_if
c_cond
(paren
id|inb
c_func
(paren
id|STATUS
)paren
op_amp
id|DF
)paren
r_goto
id|fail
suffix:semicolon
id|debug
op_assign
l_int|9
suffix:semicolon
multiline_comment|/* When HACC, command is completed, and we&squot;re though testing */
id|WAIT
c_func
(paren
id|INTRFLAGS
comma
id|HACC
comma
id|HACC
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* now initialize adapter */
id|debug
op_assign
l_int|10
suffix:semicolon
multiline_comment|/* Clear interrupts */
id|outb
c_func
(paren
id|IRST
comma
id|CONTROL
)paren
suffix:semicolon
id|debug
op_assign
l_int|11
suffix:semicolon
r_return
id|debug
suffix:semicolon
multiline_comment|/* 1 = ok */
id|fail
suffix:colon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* 0 = not ok */
)brace
multiline_comment|/* What&squot;s this little function for? */
DECL|function|aha1542_info
r_char
op_star
id|aha1542_info
c_func
(paren
r_void
)paren
(brace
r_static
r_char
id|buffer
(braket
)braket
op_assign
l_string|&quot;&quot;
suffix:semicolon
multiline_comment|/* looks nicer without anything here */
r_return
id|buffer
suffix:semicolon
)brace
multiline_comment|/* A &quot;high&quot; level interrupt handler */
DECL|function|aha1542_intr_handle
r_void
id|aha1542_intr_handle
c_func
(paren
r_void
)paren
(brace
r_void
(paren
op_star
id|my_done
)paren
(paren
r_int
comma
r_int
)paren
op_assign
id|do_done
suffix:semicolon
r_int
id|errstatus
suffix:semicolon
id|do_done
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef DEBUG
(brace
r_int
id|flag
op_assign
id|inb
c_func
(paren
id|INTRFLAGS
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;aha1542_intr_handle: &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flag
op_amp
id|ANYINTR
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;no interrupt?&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flag
op_amp
id|MBIF
)paren
id|printk
c_func
(paren
l_string|&quot;MBIF &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flag
op_amp
id|MBOA
)paren
id|printk
c_func
(paren
l_string|&quot;MBOF &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flag
op_amp
id|HACC
)paren
id|printk
c_func
(paren
l_string|&quot;HACC &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flag
op_amp
id|SCRD
)paren
id|printk
c_func
(paren
l_string|&quot;SCRD &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;status %02x&bslash;n&quot;
comma
id|inb
c_func
(paren
id|STATUS
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ccb.tarstat
op_or
id|ccb.hastat
)paren
id|printk
c_func
(paren
l_string|&quot;aha1542_command: returning %x (status %d)&bslash;n&quot;
comma
id|ccb.tarstat
op_plus
(paren
(paren
r_int
)paren
id|ccb.hastat
op_lshift
l_int|16
)paren
comma
id|mb
(braket
l_int|1
)braket
dot
id|status
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
id|aha1542_intr_reset
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|my_done
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;aha1542_intr_handle: Unexpected interrupt&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* is there mail :-) */
r_if
c_cond
(paren
op_logical_neg
id|mb
(braket
l_int|1
)braket
dot
id|status
)paren
(brace
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;aha1542_intr_handle: strange: mbif but no mail!&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|my_done
c_func
(paren
id|aha1542_host
comma
id|DID_TIME_OUT
op_lshift
l_int|16
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* more error checking left out here */
r_if
c_cond
(paren
id|mb
(braket
l_int|1
)braket
dot
id|status
op_ne
l_int|1
)paren
multiline_comment|/* This is surely wrong, but I don&squot;t know what&squot;s right */
id|errstatus
op_assign
id|makecode
c_func
(paren
id|ccb.hastat
comma
id|ccb.tarstat
)paren
suffix:semicolon
r_else
id|errstatus
op_assign
l_int|0
suffix:semicolon
id|mb
(braket
l_int|1
)braket
dot
id|status
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ccb.tarstat
op_eq
l_int|2
)paren
(brace
r_int
id|i
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;aha1542_intr_handle: sense:&quot;
)paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|12
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
id|ccb.cdb
(braket
id|ccb.cdblen
op_plus
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t;DEB(printk(&quot;aha1542_intr_handle: buf:&quot;));&n;&t;for (i = 0; i &lt; bufflen; i++)&n;&t;  printk(&quot;%02x &quot;, ((unchar *)buff)[i]);&n;&t;printk(&quot;&bslash;n&quot;);&n;*/
)brace
id|DEB
c_func
(paren
r_if
(paren
id|errstatus
)paren
id|printk
c_func
(paren
l_string|&quot;aha1542_intr_handle: returning %6x&bslash;n&quot;
comma
id|errstatus
)paren
)paren
suffix:semicolon
id|my_done
c_func
(paren
id|aha1542_host
comma
id|errstatus
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|aha1542_queuecommand
r_int
id|aha1542_queuecommand
c_func
(paren
id|unchar
id|target
comma
r_const
r_void
op_star
id|cmnd
comma
r_void
op_star
id|buff
comma
r_int
id|bufflen
comma
r_void
(paren
op_star
id|done
)paren
(paren
r_int
comma
r_int
)paren
)paren
(brace
id|unchar
id|ahacmd
op_assign
id|CMD_START_SCSI
suffix:semicolon
id|unchar
id|direction
suffix:semicolon
id|unchar
op_star
id|cmd
op_assign
(paren
id|unchar
op_star
)paren
id|cmnd
suffix:semicolon
id|DEB
c_func
(paren
r_int
id|i
)paren
suffix:semicolon
id|DEB
c_func
(paren
r_if
(paren
id|target
OG
l_int|1
)paren
(brace
id|done
c_func
(paren
id|aha1542_host
comma
id|DID_TIME_OUT
op_lshift
l_int|16
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cmd
op_eq
id|REQUEST_SENSE
)paren
(brace
id|memcpy
c_func
(paren
id|buff
comma
op_amp
id|ccb.cdb
(braket
id|ccb.cdblen
)braket
comma
id|bufflen
)paren
suffix:semicolon
id|done
c_func
(paren
id|aha1542_host
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef DEBUG
r_if
c_cond
(paren
op_star
id|cmd
op_eq
id|READ_10
op_logical_or
op_star
id|cmd
op_eq
id|WRITE_10
)paren
id|i
op_assign
id|xscsi2int
c_func
(paren
id|cmd
op_plus
l_int|2
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|cmd
op_eq
id|READ_6
op_logical_or
op_star
id|cmd
op_eq
id|WRITE_6
)paren
id|i
op_assign
id|scsi2int
c_func
(paren
id|cmd
op_plus
l_int|2
)paren
suffix:semicolon
r_else
id|i
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|done
)paren
id|printk
c_func
(paren
l_string|&quot;aha1542_queuecommand: dev %d cmd %02x pos %d len %d &quot;
comma
id|target
comma
op_star
id|cmd
comma
id|i
comma
id|bufflen
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;aha1542_command: dev %d cmd %02x pos %d len %d &quot;
comma
id|target
comma
op_star
id|cmd
comma
id|i
comma
id|bufflen
)paren
suffix:semicolon
id|aha1542_stat
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;aha1542_queuecommand: dumping scsi cmd:&quot;
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
(paren
op_star
id|cmd
op_le
l_int|0x1f
ques
c_cond
l_int|6
suffix:colon
l_int|10
)paren
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
id|cmd
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cmd
op_eq
id|WRITE_10
op_logical_or
op_star
id|cmd
op_eq
id|WRITE_6
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* we are still testing, so *don&squot;t* write */
macro_line|#endif
id|memset
c_func
(paren
op_amp
id|ccb
comma
l_int|0
comma
r_sizeof
id|ccb
)paren
suffix:semicolon
id|ccb.cdblen
op_assign
(paren
op_star
id|cmd
op_le
l_int|0x1f
)paren
ques
c_cond
l_int|6
suffix:colon
l_int|10
suffix:semicolon
multiline_comment|/* SCSI Command Descriptor Block Length */
id|direction
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cmd
op_eq
id|READ_10
op_logical_or
op_star
id|cmd
op_eq
id|READ_6
)paren
id|direction
op_assign
l_int|8
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|cmd
op_eq
id|WRITE_10
op_logical_or
op_star
id|cmd
op_eq
id|WRITE_6
)paren
id|direction
op_assign
l_int|16
suffix:semicolon
id|memcpy
c_func
(paren
id|ccb.cdb
comma
id|cmd
comma
id|ccb.cdblen
)paren
suffix:semicolon
id|ccb.op
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* SCSI Initiator Command */
id|ccb.idlun
op_assign
(paren
id|target
op_amp
l_int|7
)paren
op_lshift
l_int|5
op_or
id|direction
suffix:semicolon
multiline_comment|/* SCSI Target Id */
id|ccb.rsalen
op_assign
l_int|12
suffix:semicolon
id|any2scsi
c_func
(paren
id|ccb.datalen
comma
id|bufflen
)paren
suffix:semicolon
id|any2scsi
c_func
(paren
id|ccb.dataptr
comma
id|buff
)paren
suffix:semicolon
id|ccb.linkptr
(braket
l_int|0
)braket
op_assign
id|ccb.linkptr
(braket
l_int|1
)braket
op_assign
id|ccb.linkptr
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|ccb.commlinkid
op_assign
l_int|0
suffix:semicolon
id|mb
(braket
l_int|0
)braket
dot
id|status
op_assign
l_int|1
suffix:semicolon
id|mb
(braket
l_int|1
)braket
dot
id|status
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef DEBUGd
id|printk
c_func
(paren
l_string|&quot;aha1542_command: sending.. &quot;
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
r_sizeof
(paren
id|ccb
)paren
op_minus
l_int|10
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
(paren
(paren
id|unchar
op_star
)paren
op_amp
id|ccb
)paren
(braket
id|i
)braket
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|done
)paren
(brace
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;aha1542_queuecommand: now waiting for interrupt &quot;
)paren
suffix:semicolon
id|aha1542_stat
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|do_done
)paren
id|printk
c_func
(paren
l_string|&quot;aha1542_queuecommand: Two concurrent queuecommand?&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|do_done
op_assign
id|done
suffix:semicolon
id|aha1542_out
c_func
(paren
op_amp
id|ahacmd
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* start scsi command */
id|DEB
c_func
(paren
id|aha1542_stat
c_func
(paren
)paren
)paren
suffix:semicolon
id|aha1542_enable_intr
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;aha1542_queuecommand: done can&squot;t be NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|internal_done_flag
r_volatile
r_static
r_int
id|internal_done_flag
op_assign
l_int|0
suffix:semicolon
DECL|variable|internal_done_errcode
r_volatile
r_static
r_int
id|internal_done_errcode
op_assign
l_int|0
suffix:semicolon
DECL|function|internal_done
r_static
r_void
id|internal_done
c_func
(paren
r_int
id|host
comma
r_int
id|errcode
)paren
(brace
id|internal_done_errcode
op_assign
id|errcode
suffix:semicolon
op_increment
id|internal_done_flag
suffix:semicolon
)brace
DECL|function|aha1542_command
r_int
id|aha1542_command
c_func
(paren
id|unchar
id|target
comma
r_const
r_void
op_star
id|cmnd
comma
r_void
op_star
id|buff
comma
r_int
id|bufflen
)paren
(brace
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;aha1542_command: ..calling aha1542_queuecommand&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|aha1542_queuecommand
c_func
(paren
id|target
comma
id|cmnd
comma
id|buff
comma
id|bufflen
comma
id|internal_done
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|internal_done_flag
)paren
suffix:semicolon
id|internal_done_flag
op_assign
l_int|0
suffix:semicolon
r_return
id|internal_done_errcode
suffix:semicolon
)brace
multiline_comment|/* Initialize mailboxes */
DECL|function|setup_mailboxes
r_static
r_void
id|setup_mailboxes
c_func
(paren
)paren
(brace
r_static
id|unchar
id|cmd
(braket
l_int|5
)braket
op_assign
(brace
id|CMD_MBINIT
comma
l_int|1
)brace
suffix:semicolon
id|mb
(braket
l_int|0
)braket
dot
id|status
op_assign
id|mb
(braket
l_int|1
)braket
dot
id|status
op_assign
l_int|0
suffix:semicolon
id|aha1542_intr_reset
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* reset interrupts, so they don&squot;t block */
id|any2scsi
c_func
(paren
(paren
id|cmd
op_plus
l_int|2
)paren
comma
id|mb
)paren
suffix:semicolon
id|any2scsi
c_func
(paren
id|mb
(braket
l_int|0
)braket
dot
id|ccbptr
comma
op_amp
id|ccb
)paren
suffix:semicolon
id|aha1542_out
c_func
(paren
id|cmd
comma
l_int|5
)paren
suffix:semicolon
id|WAIT
c_func
(paren
id|INTRFLAGS
comma
id|INTRMASK
comma
id|HACC
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|0
)paren
(brace
id|fail
suffix:colon
id|printk
c_func
(paren
l_string|&quot;aha1542_detect: failed setting up mailboxes&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|aha1542_intr_reset
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* a hack to avoid a strange compilation error */
DECL|function|call_buh
r_void
id|call_buh
c_func
(paren
)paren
(brace
id|set_intr_gate
c_func
(paren
l_int|0x2b
comma
op_amp
id|aha1542_interrupt
)paren
suffix:semicolon
)brace
multiline_comment|/* Query the board to find out if it is a 1542 or a 1740, or whatever. */
DECL|function|aha1542_query
r_static
r_void
id|aha1542_query
c_func
(paren
)paren
(brace
r_static
id|unchar
id|inquiry_cmd
(braket
)braket
op_assign
(brace
id|CMD_INQUIRY
)brace
suffix:semicolon
r_static
id|unchar
id|inquiry_result
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
id|i
op_assign
id|inb
c_func
(paren
id|STATUS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_amp
id|DF
)paren
(brace
id|i
op_assign
id|inb
c_func
(paren
id|DATA
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Stale data:%x &quot;
)paren
suffix:semicolon
)brace
suffix:semicolon
id|aha1542_out
c_func
(paren
id|inquiry_cmd
comma
l_int|1
)paren
suffix:semicolon
id|aha1542_in
c_func
(paren
id|inquiry_result
comma
l_int|4
)paren
suffix:semicolon
id|WAIT
c_func
(paren
id|INTRFLAGS
comma
id|INTRMASK
comma
id|HACC
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|0
)paren
(brace
id|fail
suffix:colon
id|printk
c_func
(paren
l_string|&quot;aha1542_detect: query card type&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|aha1542_intr_reset
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Inquiry:&quot;
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%x &quot;
comma
id|inquiry_result
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* return non-zero on detection */
DECL|function|aha1542_detect
r_int
id|aha1542_detect
c_func
(paren
r_int
id|hostnum
)paren
(brace
r_int
id|i
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;aha1542_detect: &bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|i
op_assign
id|aha1542_test_port
c_func
(paren
)paren
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Set the Bus on/off-times as not to ruin floppy performens */
(brace
r_static
id|unchar
id|oncmd
(braket
)braket
op_assign
(brace
id|CMD_BUSON_TIME
comma
l_int|5
)brace
suffix:semicolon
r_static
id|unchar
id|offcmd
(braket
)braket
op_assign
(brace
id|CMD_BUSOFF_TIME
comma
l_int|9
)brace
suffix:semicolon
id|aha1542_intr_reset
c_func
(paren
)paren
suffix:semicolon
id|aha1542_out
c_func
(paren
id|oncmd
comma
l_int|2
)paren
suffix:semicolon
id|WAIT
c_func
(paren
id|INTRFLAGS
comma
id|INTRMASK
comma
id|HACC
comma
l_int|0
)paren
suffix:semicolon
id|aha1542_intr_reset
c_func
(paren
)paren
suffix:semicolon
id|aha1542_out
c_func
(paren
id|offcmd
comma
l_int|2
)paren
suffix:semicolon
id|WAIT
c_func
(paren
id|INTRFLAGS
comma
id|INTRMASK
comma
id|HACC
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|0
)paren
(brace
id|fail
suffix:colon
id|printk
c_func
(paren
l_string|&quot;aha1542_detect: setting bus on/off-time failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|aha1542_intr_reset
c_func
(paren
)paren
suffix:semicolon
)brace
id|aha1542_query
c_func
(paren
)paren
suffix:semicolon
id|DEB
c_func
(paren
id|aha1542_stat
c_func
(paren
)paren
)paren
suffix:semicolon
id|setup_mailboxes
c_func
(paren
)paren
suffix:semicolon
id|DEB
c_func
(paren
id|aha1542_stat
c_func
(paren
)paren
)paren
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;aha1542_detect: enable interrupt channel %d&bslash;n&quot;
comma
id|intr_chan
)paren
)paren
suffix:semicolon
id|call_buh
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intr_chan
op_ge
l_int|8
)paren
id|outb
c_func
(paren
id|inb_p
c_func
(paren
l_int|0x21
)paren
op_amp
l_int|0xfb
comma
l_int|0x21
)paren
suffix:semicolon
multiline_comment|/* open for slave ?? */
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;aha1542_detect: enabling interrupts&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|aha1542_enable_intr
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot; *** READ CAPACITY ***&bslash;n&quot;
)paren
)paren
suffix:semicolon
(brace
id|unchar
id|buf
(braket
l_int|8
)braket
suffix:semicolon
r_static
id|unchar
id|cmd
(braket
)braket
op_assign
(brace
id|READ_CAPACITY
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
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
r_int
id|i
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
r_sizeof
(paren
id|buf
)paren
suffix:semicolon
op_increment
id|i
)paren
id|buf
(braket
id|i
)braket
op_assign
l_int|0x87
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
l_int|2
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
op_logical_neg
id|aha1542_command
c_func
(paren
id|i
comma
id|cmd
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;aha_detect: LU %d sector_size %d device_size %d&bslash;n&quot;
comma
id|i
comma
id|xscsi2int
c_func
(paren
id|buf
op_plus
l_int|4
)paren
comma
id|xscsi2int
c_func
(paren
id|buf
)paren
)paren
suffix:semicolon
)brace
)brace
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot; *** NOW RUNNING MY OWN TEST *** &bslash;n&quot;
)paren
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
l_int|4
suffix:semicolon
op_increment
id|i
)paren
(brace
r_int
r_char
id|cmd
(braket
l_int|10
)braket
suffix:semicolon
r_static
id|buffer
(braket
l_int|512
)braket
suffix:semicolon
id|cmd
(braket
l_int|0
)braket
op_assign
id|READ_10
suffix:semicolon
id|cmd
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|xany2scsi
c_func
(paren
id|cmd
op_plus
l_int|2
comma
id|i
)paren
suffix:semicolon
id|cmd
(braket
l_int|6
)braket
op_assign
l_int|0
suffix:semicolon
id|cmd
(braket
l_int|7
)braket
op_assign
l_int|0
suffix:semicolon
id|cmd
(braket
l_int|8
)braket
op_assign
l_int|1
suffix:semicolon
id|cmd
(braket
l_int|9
)braket
op_assign
l_int|0
suffix:semicolon
id|aha1542_command
c_func
(paren
l_int|0
comma
id|cmd
comma
id|buffer
comma
l_int|512
)paren
suffix:semicolon
)brace
macro_line|#endif
id|aha1542_host
op_assign
id|hostnum
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|aha1542_abort
r_int
id|aha1542_abort
c_func
(paren
r_int
id|i
)paren
(brace
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;aha1542_abort&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|aha1542_reset
r_int
id|aha1542_reset
c_func
(paren
r_void
)paren
(brace
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;aha1542_reset called&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__asm__
c_func
(paren
"&quot;"
id|_aha1542_interrupt
suffix:colon
id|cld
id|pushl
op_mod
id|eax
id|pushl
op_mod
id|ecx
id|pushl
op_mod
id|edx
id|push
op_mod
id|ds
id|push
op_mod
id|es
id|push
op_mod
id|fs
id|movl
"$"
l_int|0x10
comma
op_mod
id|eax
id|mov
op_mod
id|ax
comma
op_mod
id|ds
id|mov
op_mod
id|ax
comma
op_mod
id|es
id|movl
"$"
l_int|0x17
comma
op_mod
id|eax
id|mov
op_mod
id|ax
comma
op_mod
id|fs
id|movb
"$"
l_int|0x20
comma
op_mod
id|al
id|outb
op_mod
id|al
comma
"$"
l_int|0xA0
macro_line|# EOI to interrupt controller #1
id|jmp
l_float|1f
macro_line|# give port chance to breathe
l_int|1
suffix:colon
id|jmp
l_float|1f
l_int|1
suffix:colon
id|outb
op_mod
id|al
comma
"$"
l_int|0x20
macro_line|# Please, someone, change this to use the timer
macro_line|#&t;andl $0xfffeffff,_timer_active
id|movl
"$"
id|_aha1542_intr_handle
comma
op_mod
id|edx
id|call
op_star
op_mod
id|edx
macro_line|# ``interesting&squot;&squot; way of handling intr.
id|pop
op_mod
id|fs
id|pop
op_mod
id|es
id|pop
op_mod
id|ds
id|popl
op_mod
id|edx
id|popl
op_mod
id|ecx
id|popl
op_mod
id|eax
id|iret
"&quot;"
)paren
suffix:semicolon
eof
