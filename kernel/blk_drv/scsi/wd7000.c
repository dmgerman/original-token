multiline_comment|/* $Id: $&n; *  linux/kernel/wd7000.c&n; *&n; *  Copyright (C) 1992  Thomas Wuensche&n; *&t;closely related to the aha1542 driver from Tommy Thorn&n; *&t;( as close as different hardware allows on a lowlevel-driver :-) )&n; *&n; *  Revised (and renamed) by John Boyd &lt;boyd@cis.ohio-state.edu&gt; to&n; *  accomodate Eric Youngdale&squot;s modifications to scsi.c.  Nov 1992.&n; *&n; *  Additional changes to support scatter/gather.  Dec. 1992.  tw/jb&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;../blk.h&quot;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
multiline_comment|/* #define DEBUG  */
macro_line|#include &quot;wd7000.h&quot;
macro_line|#ifdef DEBUG
DECL|macro|DEB
mdefine_line|#define DEB(x) x
macro_line|#else
DECL|macro|DEB
mdefine_line|#define DEB(x)
macro_line|#endif
multiline_comment|/*&n;   Driver data structures:&n;   - mb and scbs are required for interfacing with the host adapter.&n;     An SCB has extra fields not visible to the adapter; mb&squot;s&n;     _cannot_ do this, since the adapter assumes they are contiguous in&n;     memory, 4 bytes each, with ICMBs following OGMBs, and uses this fact&n;     to access them.&n;   - An icb is for host-only (non-SCSI) commands.  ICBs are 16 bytes each;&n;     the additional bytes are used only by the driver.&n;   - For now, a pool of SCBs are kept in global storage by this driver,&n;     and are allocated and freed as needed.&n;&n;  The 7000-FASST2 marks OGMBs empty as soon as it has _started_ a command,&n;  not when it has finished.  Since the SCB must be around for completion,&n;  problems arise when SCBs correspond to OGMBs, which may be reallocated&n;  earlier (or delayed unnecessarily until a command completes).&n;  Mailboxes are used as transient data structures, simply for&n;  carrying SCB addresses to/from the 7000-FASST2.&n;&n;  Note also since SCBs are not &quot;permanently&quot; associated with mailboxes,&n;  there is no need to keep a global list of Scsi_Cmnd pointers indexed&n;  by OGMB.   Again, SCBs reference their Scsi_Cmnds directly, so mailbox&n;  indices need not be involved.&n;*/
r_static
r_struct
(brace
DECL|member|ogmb
r_struct
id|wd_mailbox
id|ogmb
(braket
id|OGMB_CNT
)braket
suffix:semicolon
DECL|member|icmb
r_struct
id|wd_mailbox
id|icmb
(braket
id|ICMB_CNT
)braket
suffix:semicolon
DECL|variable|mb
)brace
id|mb
suffix:semicolon
DECL|variable|next_ogmb
r_static
r_int
id|next_ogmb
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* to reduce contention at mailboxes */
DECL|variable|scbs
r_static
id|Scb
id|scbs
(braket
id|MAX_SCBS
)braket
suffix:semicolon
DECL|variable|scbfree
r_static
id|Scb
op_star
id|scbfree
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|wd7000_host
r_static
r_int
id|wd7000_host
op_assign
l_int|0
suffix:semicolon
DECL|variable|controlstat
r_static
id|unchar
id|controlstat
op_assign
l_int|0
suffix:semicolon
DECL|variable|rev_1
DECL|variable|rev_2
r_static
id|unchar
id|rev_1
op_assign
l_int|0
comma
id|rev_2
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* filled in by wd7000_revision */
DECL|macro|wd7000_intr_ack
mdefine_line|#define wd7000_intr_ack()  outb(0,INTR_ACK)
DECL|macro|WAITnexttimeout
mdefine_line|#define WAITnexttimeout 3000000
DECL|function|wd7000_enable_intr
r_static
r_inline
r_void
id|wd7000_enable_intr
c_func
(paren
)paren
(brace
id|controlstat
op_or_assign
id|INT_EN
suffix:semicolon
id|outb
c_func
(paren
id|controlstat
comma
id|CONTROL
)paren
suffix:semicolon
)brace
DECL|function|wd7000_enable_dma
r_static
r_inline
r_void
id|wd7000_enable_dma
c_func
(paren
)paren
(brace
id|controlstat
op_or_assign
id|DMA_EN
suffix:semicolon
id|outb
c_func
(paren
id|controlstat
comma
id|CONTROL
)paren
suffix:semicolon
id|set_dma_mode
c_func
(paren
id|DMA_CH
comma
id|DMA_MODE_CASCADE
)paren
suffix:semicolon
id|enable_dma
c_func
(paren
id|DMA_CH
)paren
suffix:semicolon
)brace
DECL|macro|WAIT
mdefine_line|#define WAIT(port, mask, allof, noneof)&t;&t;&t;&t;&t;&bslash;&n; { register WAITbits;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;   register WAITtimeout = WAITnexttimeout;&t;&t;&t;&t;&bslash;&n;   while (1) {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;     WAITbits = inb(port) &amp; (mask);&t;&t;&t;&t;&t;&bslash;&n;     if ((WAITbits &amp; (allof)) == (allof) &amp;&amp; ((WAITbits &amp; (noneof)) == 0)) &bslash;&n;       break;                                                         &t;&bslash;&n;     if (--WAITtimeout == 0) goto fail;&t;&t;&t;&t;&t;&bslash;&n;   }&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; }
DECL|function|delay
r_static
r_inline
r_void
id|delay
c_func
(paren
r_int
id|how_long
)paren
(brace
r_int
r_int
id|time
op_assign
id|jiffies
op_plus
id|how_long
suffix:semicolon
r_while
c_loop
(paren
id|jiffies
OL
id|time
)paren
suffix:semicolon
)brace
DECL|function|command_out
r_static
r_inline
r_int
id|command_out
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
id|ASC_STAT
comma
id|STATMASK
comma
id|CMD_RDY
comma
l_int|0
)paren
suffix:semicolon
id|outb
c_func
(paren
op_star
id|cmdp
op_increment
comma
id|COMMAND
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
id|fail
suffix:colon
id|printk
c_func
(paren
l_string|&quot;wd7000_out WAIT failed(%d): &quot;
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alloc_scb
r_static
r_inline
id|Scb
op_star
id|alloc_scb
c_func
(paren
r_void
)paren
(brace
id|Scb
op_star
id|scb
suffix:semicolon
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
r_if
c_cond
(paren
id|scbfree
op_eq
l_int|NULL
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;wd7000: can&squot;t allocate free SCB.&bslash;n&quot;
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|scb
op_assign
id|scbfree
suffix:semicolon
id|scbfree
op_assign
id|scb-&gt;next
suffix:semicolon
id|memset
c_func
(paren
id|scb
comma
l_int|0
comma
r_sizeof
(paren
id|Scb
)paren
)paren
suffix:semicolon
id|scb-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|scb
suffix:semicolon
)brace
DECL|function|free_scb
r_static
r_inline
r_void
id|free_scb
c_func
(paren
id|Scb
op_star
id|scb
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
id|memset
c_func
(paren
id|scb
comma
l_int|0
comma
r_sizeof
(paren
id|Scb
)paren
)paren
suffix:semicolon
id|scb-&gt;next
op_assign
id|scbfree
suffix:semicolon
id|scbfree
op_assign
id|scb
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|init_scbs
r_static
r_inline
r_void
id|init_scbs
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
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
id|scbfree
op_assign
op_amp
(paren
id|scbs
(braket
l_int|0
)braket
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
id|MAX_SCBS
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
id|scbs
(braket
id|i
)braket
dot
id|next
op_assign
op_amp
(paren
id|scbs
(braket
id|i
op_plus
l_int|1
)braket
)paren
suffix:semicolon
id|scbs
(braket
id|MAX_SCBS
op_minus
l_int|1
)braket
dot
id|next
op_assign
l_int|NULL
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|mail_out
r_static
r_int
id|mail_out
c_func
(paren
id|Scb
op_star
id|scbptr
)paren
multiline_comment|/*&n; *  Note: this can also be used for ICBs; just cast to the parm type.&n; */
(brace
r_int
id|i
comma
id|ogmb
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;wd7000_scb_out: %06x&quot;
)paren
suffix:semicolon
)paren
multiline_comment|/* We first look for a free outgoing mailbox */
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
id|ogmb
op_assign
id|next_ogmb
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
id|OGMB_CNT
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mb.ogmb
(braket
id|ogmb
)braket
dot
id|status
op_eq
l_int|0
)paren
(brace
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot; using OGMB %x&quot;
comma
id|ogmb
)paren
)paren
suffix:semicolon
id|mb.ogmb
(braket
id|ogmb
)braket
dot
id|status
op_assign
l_int|1
suffix:semicolon
id|any2scsi
c_func
(paren
id|mb.ogmb
(braket
id|ogmb
)braket
dot
id|scbptr
comma
id|scbptr
)paren
suffix:semicolon
id|next_ogmb
op_assign
(paren
id|ogmb
op_plus
l_int|1
)paren
op_mod
id|OGMB_CNT
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
id|ogmb
op_assign
(paren
op_increment
id|ogmb
)paren
op_mod
id|OGMB_CNT
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;, scb is %x&quot;
comma
id|scbptr
)paren
suffix:semicolon
)paren
r_if
c_cond
(paren
id|i
op_ge
id|OGMB_CNT
)paren
(brace
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;, no free OGMBs.&bslash;n&quot;
)paren
suffix:semicolon
)paren
multiline_comment|/* Alternatively, issue &quot;interrupt on free OGMB&quot;, and sleep... */
r_return
l_int|0
suffix:semicolon
)brace
id|wd7000_enable_intr
c_func
(paren
)paren
suffix:semicolon
r_do
(brace
id|WAIT
c_func
(paren
id|ASC_STAT
comma
id|STATMASK
comma
id|CMD_RDY
comma
l_int|0
)paren
suffix:semicolon
id|outb
c_func
(paren
id|START_OGMB
op_or
id|ogmb
comma
id|COMMAND
)paren
suffix:semicolon
id|WAIT
c_func
(paren
id|ASC_STAT
comma
id|STATMASK
comma
id|CMD_RDY
comma
l_int|0
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|inb
c_func
(paren
id|ASC_STAT
)paren
op_amp
id|CMD_REJ
)paren
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;, awaiting interrupt.&bslash;n&quot;
)paren
suffix:semicolon
)paren
r_return
l_int|1
suffix:semicolon
id|fail
suffix:colon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;, WAIT timed out.&bslash;n&quot;
)paren
suffix:semicolon
)paren
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|make_code
r_int
id|make_code
c_func
(paren
r_int
id|hosterr
comma
r_int
id|scsierr
)paren
(brace
macro_line|#ifdef DEBUG
r_int
id|in_error
op_assign
id|hosterr
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
(paren
id|hosterr
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* Reserved */
id|hosterr
op_assign
id|DID_ERROR
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* Command Complete, no errors */
id|hosterr
op_assign
id|DID_OK
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* Command complete, error logged in scb status (scsierr) */
id|hosterr
op_assign
id|DID_OK
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
multiline_comment|/* Command failed to complete - timeout */
id|hosterr
op_assign
id|DID_TIME_OUT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
multiline_comment|/* Command terminated; Bus reset by external device */
id|hosterr
op_assign
id|DID_RESET
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
multiline_comment|/* Unexpected Command Received w/ host as target */
id|hosterr
op_assign
id|DID_BAD_TARGET
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|80
suffix:colon
multiline_comment|/* Unexpected Reselection */
r_case
l_int|81
suffix:colon
multiline_comment|/* Unexpected Selection */
id|hosterr
op_assign
id|DID_BAD_INTR
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|82
suffix:colon
multiline_comment|/* Abort Command Message  */
id|hosterr
op_assign
id|DID_ABORT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|83
suffix:colon
multiline_comment|/* SCSI Bus Software Reset */
r_case
l_int|84
suffix:colon
multiline_comment|/* SCSI Bus Hardware Reset */
id|hosterr
op_assign
id|DID_RESET
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Reserved */
id|hosterr
op_assign
id|DID_ERROR
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
r_if
c_cond
(paren
id|scsierr
op_logical_or
id|hosterr
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;nSCSI command error: SCSI %02x host %04x return %d&quot;
comma
id|scsierr
comma
id|in_error
comma
id|hosterr
)paren
suffix:semicolon
macro_line|#endif
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
DECL|function|wd7000_scsi_done
r_static
r_void
id|wd7000_scsi_done
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;wd7000_scsi_done: %06x&bslash;n&quot;
comma
id|SCpnt
)paren
suffix:semicolon
)paren
id|SCpnt-&gt;SCp.phase
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|wd7000_intr_handle
r_void
id|wd7000_intr_handle
c_func
(paren
r_int
id|irq
)paren
(brace
r_int
id|flag
comma
id|icmb
comma
id|errstatus
comma
id|icmb_status
suffix:semicolon
r_int
id|host_error
comma
id|scsi_error
suffix:semicolon
id|Scb
op_star
id|scb
suffix:semicolon
multiline_comment|/* for SCSI commands */
id|unchar
op_star
id|icb
suffix:semicolon
multiline_comment|/* for host commands */
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
id|flag
op_assign
id|inb
c_func
(paren
id|INTR_STAT
)paren
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;wd7000_intr_handle: intr stat = %02x&quot;
comma
id|flag
)paren
suffix:semicolon
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|inb
c_func
(paren
id|ASC_STAT
)paren
op_amp
l_int|0x80
)paren
)paren
(brace
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;&bslash;nwd7000_intr_handle: phantom interrupt...&bslash;n&quot;
)paren
suffix:semicolon
)paren
id|wd7000_intr_ack
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* check for an incoming mailbox */
r_if
c_cond
(paren
(paren
id|flag
op_amp
l_int|0x40
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/*  for a free OGMB - need code for this case... */
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;wd7000_intr_handle: free outgoing mailbox&bslash;n&quot;
)paren
suffix:semicolon
)paren
id|wd7000_intr_ack
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* The interrupt is for an incoming mailbox */
id|icmb
op_assign
id|flag
op_amp
l_int|0x3f
suffix:semicolon
id|scb
op_assign
(paren
r_struct
id|scb
op_star
)paren
id|scsi2int
c_func
(paren
id|mb.icmb
(braket
id|icmb
)braket
dot
id|scbptr
)paren
suffix:semicolon
id|icmb_status
op_assign
id|mb.icmb
(braket
id|icmb
)braket
dot
id|status
suffix:semicolon
id|mb.icmb
(braket
id|icmb
)braket
dot
id|status
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot; ICMB %d posted for SCB/ICB %06x, status %02x, vue %02x&quot;
comma
id|icmb
comma
id|scb
comma
id|icmb_status
comma
id|scb-&gt;vue
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
(paren
id|scb-&gt;op
op_amp
l_int|0x80
)paren
)paren
(brace
multiline_comment|/* an SCB is done */
id|SCpnt
op_assign
id|scb-&gt;SCpnt
suffix:semicolon
r_if
c_cond
(paren
op_decrement
(paren
id|SCpnt-&gt;SCp.phase
)paren
op_le
l_int|0
)paren
(brace
multiline_comment|/* all scbs for SCpnt are done */
id|host_error
op_assign
id|scb-&gt;vue
op_or
(paren
id|icmb_status
op_lshift
l_int|8
)paren
suffix:semicolon
id|scsi_error
op_assign
id|scb-&gt;status
suffix:semicolon
id|errstatus
op_assign
id|make_code
c_func
(paren
id|host_error
comma
id|scsi_error
)paren
suffix:semicolon
id|SCpnt-&gt;result
op_assign
id|errstatus
suffix:semicolon
r_if
c_cond
(paren
id|SCpnt-&gt;host_scribble
op_ne
l_int|NULL
)paren
id|scsi_free
c_func
(paren
id|SCpnt-&gt;host_scribble
comma
id|WD7000_SCRIBBLE
)paren
suffix:semicolon
id|free_scb
c_func
(paren
id|scb
)paren
suffix:semicolon
id|SCpnt
op_member_access_from_pointer
id|scsi_done
c_func
(paren
id|SCpnt
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* an ICB is done */
id|icb
op_assign
(paren
id|unchar
op_star
)paren
id|scb
suffix:semicolon
id|icb
(braket
id|ICB_STATUS
)braket
op_assign
id|icmb_status
suffix:semicolon
id|icb
(braket
id|ICB_PHASE
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|wd7000_intr_ack
c_func
(paren
)paren
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;.&bslash;n&quot;
)paren
suffix:semicolon
)paren
r_return
suffix:semicolon
)brace
DECL|function|wd7000_queuecommand
r_int
id|wd7000_queuecommand
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
(brace
id|Scb
op_star
id|scb
suffix:semicolon
id|Sgb
op_star
id|sgb
suffix:semicolon
id|unchar
op_star
id|cdb
suffix:semicolon
id|unchar
id|idlun
suffix:semicolon
r_int
id|cdblen
suffix:semicolon
id|cdb
op_assign
(paren
id|unchar
op_star
)paren
id|SCpnt-&gt;cmnd
suffix:semicolon
id|cdblen
op_assign
(paren
op_star
id|cdb
op_le
l_int|0x1f
ques
c_cond
l_int|6
suffix:colon
l_int|10
)paren
suffix:semicolon
id|idlun
op_assign
(paren
(paren
id|SCpnt-&gt;target
op_lshift
l_int|5
)paren
op_amp
l_int|0xe0
)paren
op_or
(paren
id|SCpnt-&gt;lun
op_amp
l_int|7
)paren
suffix:semicolon
id|SCpnt-&gt;scsi_done
op_assign
id|done
suffix:semicolon
id|SCpnt-&gt;SCp.phase
op_assign
l_int|1
suffix:semicolon
id|scb
op_assign
id|alloc_scb
c_func
(paren
)paren
suffix:semicolon
id|scb-&gt;idlun
op_assign
id|idlun
suffix:semicolon
id|memcpy
c_func
(paren
id|scb-&gt;cdb
comma
id|cdb
comma
id|cdblen
)paren
suffix:semicolon
id|scb-&gt;direc
op_assign
l_int|0x40
suffix:semicolon
multiline_comment|/* Disable direction check */
id|scb-&gt;SCpnt
op_assign
id|SCpnt
suffix:semicolon
multiline_comment|/* so we can find stuff later */
id|SCpnt-&gt;host_scribble
op_assign
l_int|NULL
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;request_bufflen is %x, bufflen is %x&bslash;n&quot;
comma
"&bslash;"
id|SCpnt-&gt;request_bufflen
comma
id|SCpnt-&gt;bufflen
)paren
suffix:semicolon
)paren
r_if
c_cond
(paren
id|SCpnt-&gt;use_sg
)paren
(brace
r_struct
id|scatterlist
op_star
id|sg
op_assign
(paren
r_struct
id|scatterlist
op_star
)paren
id|SCpnt-&gt;request_buffer
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|scsi_hosts
(braket
id|wd7000_host
)braket
dot
id|sg_tablesize
op_le
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;wd7000_queuecommand: scatter/gather not supported.&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;Using scatter/gather with %d elements.&bslash;n&quot;
comma
id|SCpnt-&gt;use_sg
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; &t;    Allocate memory for a scatter/gather-list in wd7000 format.&n; &t;    Save the pointer at host_scribble.&n;  &t;*/
macro_line|#ifdef DEBUG
r_if
c_cond
(paren
id|SCpnt-&gt;use_sg
OG
id|WD7000_SG
)paren
id|panic
c_func
(paren
l_string|&quot;WD7000: requesting too many scatterblocks&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|SCpnt-&gt;host_scribble
op_assign
id|scsi_malloc
c_func
(paren
id|WD7000_SCRIBBLE
)paren
suffix:semicolon
id|sgb
op_assign
(paren
id|Sgb
op_star
)paren
id|SCpnt-&gt;host_scribble
suffix:semicolon
r_if
c_cond
(paren
id|sgb
op_eq
l_int|NULL
)paren
id|panic
c_func
(paren
l_string|&quot;wd7000_queuecommand: scsi_malloc() failed.&bslash;n&quot;
)paren
suffix:semicolon
id|scb-&gt;op
op_assign
l_int|1
suffix:semicolon
id|any2scsi
c_func
(paren
id|scb-&gt;dataptr
comma
id|sgb
)paren
suffix:semicolon
id|any2scsi
c_func
(paren
id|scb-&gt;maxlen
comma
id|SCpnt-&gt;use_sg
op_star
r_sizeof
(paren
id|Sgb
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
id|SCpnt-&gt;use_sg
suffix:semicolon
id|i
op_increment
)paren
(brace
id|any2scsi
c_func
(paren
id|sgb-&gt;ptr
comma
id|sg
(braket
id|i
)braket
dot
id|address
)paren
suffix:semicolon
id|any2scsi
c_func
(paren
id|sgb-&gt;len
comma
id|sg
(braket
id|i
)braket
dot
id|length
)paren
suffix:semicolon
id|sgb
op_increment
suffix:semicolon
)brace
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;Using %d bytes for %d scatter/gather blocks&bslash;n&quot;
comma
"&bslash;"
id|scsi2int
c_func
(paren
id|scb-&gt;maxlen
)paren
comma
id|SCpnt-&gt;use_sg
)paren
suffix:semicolon
)paren
)brace
r_else
(brace
id|scb-&gt;op
op_assign
l_int|0
suffix:semicolon
id|any2scsi
c_func
(paren
id|scb-&gt;dataptr
comma
id|SCpnt-&gt;request_buffer
)paren
suffix:semicolon
id|any2scsi
c_func
(paren
id|scb-&gt;maxlen
comma
id|SCpnt-&gt;request_bufflen
)paren
suffix:semicolon
)brace
r_return
id|mail_out
c_func
(paren
id|scb
)paren
suffix:semicolon
)brace
DECL|function|wd7000_command
r_int
id|wd7000_command
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
id|wd7000_queuecommand
c_func
(paren
id|SCpnt
comma
id|wd7000_scsi_done
)paren
suffix:semicolon
r_while
c_loop
(paren
id|SCpnt-&gt;SCp.phase
OG
l_int|0
)paren
suffix:semicolon
multiline_comment|/* phase counts scbs down to 0 */
r_return
id|SCpnt-&gt;result
suffix:semicolon
)brace
DECL|function|wd7000_init
r_int
id|wd7000_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|unchar
id|init_block
(braket
)braket
op_assign
(brace
id|INITIALIZATION
comma
l_int|7
comma
id|BUS_ON
comma
id|BUS_OFF
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|OGMB_CNT
comma
id|ICMB_CNT
)brace
suffix:semicolon
multiline_comment|/* Reset the adapter. */
id|outb
c_func
(paren
id|SCSI_RES
op_or
id|ASC_RES
comma
id|CONTROL
)paren
suffix:semicolon
id|delay
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* reset pulse: this is 10ms, only need 25us */
id|outb
c_func
(paren
l_int|0
comma
id|CONTROL
)paren
suffix:semicolon
id|controlstat
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;       Wait 2 seconds, then expect Command Port Ready.&n;&n;       I suspect something else needs to be done here, but I don&squot;t know&n;       what.  The OEM doc says power-up diagnostics take 2 seconds, and&n;       indeed, SCSI commands submitted before then will time out, but&n;       none of what follows seems deterred by _not_ waiting 2 secs.&n;    */
id|delay
c_func
(paren
l_int|200
)paren
suffix:semicolon
id|WAIT
c_func
(paren
id|ASC_STAT
comma
id|STATMASK
comma
id|CMD_RDY
comma
l_int|0
)paren
suffix:semicolon
id|DEB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;wd7000_init: Power-on Diagnostics finished&bslash;n&quot;
)paren
suffix:semicolon
)paren
r_if
c_cond
(paren
(paren
id|i
op_assign
id|inb
c_func
(paren
id|INTR_STAT
)paren
)paren
op_ne
l_int|1
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;wd7000_init: Power-on Diagnostics error&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Clear mailboxes */
id|memset
c_func
(paren
op_amp
id|mb
comma
l_int|0
comma
r_sizeof
(paren
id|mb
)paren
)paren
suffix:semicolon
multiline_comment|/* Set up SCB free list */
id|init_scbs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Set up init block */
id|any2scsi
c_func
(paren
id|init_block
op_plus
l_int|5
comma
op_amp
id|mb
)paren
suffix:semicolon
multiline_comment|/* Execute init command */
r_if
c_cond
(paren
op_logical_neg
id|command_out
c_func
(paren
id|init_block
comma
r_sizeof
(paren
id|init_block
)paren
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;WD-7000 Initialization failed.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Wait until init finished */
id|WAIT
c_func
(paren
id|ASC_STAT
comma
id|STATMASK
comma
id|CMD_RDY
op_or
id|ASC_INI
comma
l_int|0
)paren
suffix:semicolon
id|outb
c_func
(paren
id|DISABLE_UNS_INTR
comma
id|COMMAND
)paren
suffix:semicolon
id|WAIT
c_func
(paren
id|ASC_STAT
comma
id|STATMASK
comma
id|CMD_RDY
op_or
id|ASC_INI
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Enable Interrupt and DMA */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|IRQ_LVL
comma
id|wd7000_intr_handle
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Unable to allocate IRQ for WD-7000.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
id|request_dma
c_func
(paren
id|DMA_CH
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Unable to allocate DMA channel for WD-7000.&bslash;n&quot;
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|IRQ_LVL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
id|wd7000_enable_dma
c_func
(paren
)paren
suffix:semicolon
id|wd7000_enable_intr
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;WD-7000 initialized.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
id|fail
suffix:colon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* 0 = not ok */
)brace
DECL|function|wd7000_revision
r_void
id|wd7000_revision
c_func
(paren
r_void
)paren
(brace
r_volatile
id|unchar
id|icb
(braket
id|ICB_LEN
)braket
op_assign
(brace
l_int|0x8c
)brace
suffix:semicolon
multiline_comment|/* read firmware revision level */
id|icb
(braket
id|ICB_PHASE
)braket
op_assign
l_int|1
suffix:semicolon
id|mail_out
c_func
(paren
(paren
r_struct
id|scb
op_star
)paren
id|icb
)paren
suffix:semicolon
r_while
c_loop
(paren
id|icb
(braket
id|ICB_PHASE
)braket
)paren
multiline_comment|/* wait for completion */
suffix:semicolon
id|rev_1
op_assign
id|icb
(braket
l_int|1
)braket
suffix:semicolon
id|rev_2
op_assign
id|icb
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*&n;        For boards at rev 7.0 or later, enable scatter/gather.&n;    */
r_if
c_cond
(paren
id|rev_1
op_ge
l_int|7
)paren
id|scsi_hosts
(braket
id|wd7000_host
)braket
dot
id|sg_tablesize
op_assign
id|WD7000_SG
suffix:semicolon
)brace
DECL|variable|wd_bases
r_static
r_const
r_char
op_star
id|wd_bases
(braket
)braket
op_assign
(brace
(paren
r_char
op_star
)paren
l_int|0xce000
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|signature
r_char
op_star
id|signature
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|typedef|Signature
)brace
id|Signature
suffix:semicolon
DECL|variable|signatures
r_static
r_const
id|Signature
id|signatures
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;SSTBIOS&quot;
comma
l_int|0xd
comma
l_int|0x7
)brace
)brace
suffix:semicolon
DECL|macro|NUM_SIGNATURES
mdefine_line|#define NUM_SIGNATURES (sizeof(signatures)/sizeof(Signature))
DECL|function|wd7000_detect
r_int
id|wd7000_detect
c_func
(paren
r_int
id|hostnum
)paren
multiline_comment|/* &n; *  return non-zero on detection&n; */
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_char
r_const
op_star
id|base_address
op_assign
l_int|NULL
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
r_sizeof
(paren
id|wd_bases
)paren
op_div
r_sizeof
(paren
r_char
op_star
)paren
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|NUM_SIGNATURES
suffix:semicolon
id|j
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|wd_bases
(braket
id|i
)braket
op_plus
id|signatures
(braket
id|j
)braket
dot
id|offset
)paren
comma
(paren
r_void
op_star
)paren
id|signatures
(braket
id|j
)braket
dot
id|signature
comma
id|signatures
(braket
id|j
)braket
dot
id|length
)paren
)paren
(brace
id|base_address
op_assign
id|wd_bases
(braket
id|i
)braket
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;WD-7000 detected.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|base_address
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Store our host number */
id|wd7000_host
op_assign
id|hostnum
suffix:semicolon
id|wd7000_init
c_func
(paren
)paren
suffix:semicolon
id|wd7000_revision
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* will set scatter/gather by rev level */
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|wd7000_append_info
r_static
r_void
id|wd7000_append_info
c_func
(paren
r_char
op_star
id|info
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
multiline_comment|/*&n; *  This is just so I can use vsprintf...&n; */
(brace
id|va_list
id|args
suffix:semicolon
r_extern
r_int
id|vsprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_const
r_char
op_star
id|fmt
comma
id|va_list
id|args
)paren
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsprintf
c_func
(paren
id|info
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|wd7000_info
r_const
r_char
op_star
id|wd7000_info
c_func
(paren
r_void
)paren
(brace
r_static
r_char
id|info
(braket
l_int|80
)braket
op_assign
l_string|&quot;Western Digital WD-7000, Firmware Revision &quot;
suffix:semicolon
id|wd7000_revision
c_func
(paren
)paren
suffix:semicolon
id|wd7000_append_info
c_func
(paren
id|info
op_plus
id|strlen
c_func
(paren
id|info
)paren
comma
l_string|&quot;%d.%d.&bslash;n&quot;
comma
id|rev_1
comma
id|rev_2
)paren
suffix:semicolon
r_return
id|info
suffix:semicolon
)brace
DECL|function|wd7000_abort
r_int
id|wd7000_abort
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_int
id|i
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;wd7000_abort: Scsi_Cmnd = 0x%08x, code = %d &quot;
comma
id|SCpnt
comma
id|i
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;id %d lun %d cdb&quot;
comma
id|SCpnt-&gt;target
comma
id|SCpnt-&gt;lun
)paren
suffix:semicolon
(brace
r_int
id|j
suffix:semicolon
id|unchar
op_star
id|cdbj
op_assign
(paren
id|unchar
op_star
)paren
id|SCpnt-&gt;cmnd
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
(paren
op_star
id|cdbj
op_le
l_int|0x1f
ques
c_cond
l_int|6
suffix:colon
l_int|10
)paren
suffix:semicolon
id|j
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot; %02x&quot;
comma
op_star
(paren
id|cdbj
op_increment
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; result %08x&bslash;n&quot;
comma
id|SCpnt-&gt;result
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|wd7000_reset
r_int
id|wd7000_reset
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;wd7000_reset&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|wd7000_biosparam
r_int
id|wd7000_biosparam
c_func
(paren
r_int
id|size
comma
r_int
id|dev
comma
r_int
op_star
id|info
)paren
multiline_comment|/*&n; *  This is borrowed directly from aha1542.c, but my disks are organized&n; *   this way, so I think it will work OK.&n; */
(brace
id|info
(braket
l_int|0
)braket
op_assign
l_int|32
suffix:semicolon
id|info
(braket
l_int|1
)braket
op_assign
l_int|64
suffix:semicolon
id|info
(braket
l_int|2
)braket
op_assign
(paren
id|size
op_plus
l_int|2047
)paren
op_rshift
l_int|11
suffix:semicolon
r_if
c_cond
(paren
id|info
(braket
l_int|2
)braket
op_ge
l_int|1024
)paren
id|info
(braket
l_int|2
)braket
op_assign
l_int|1024
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
