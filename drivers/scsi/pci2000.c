multiline_comment|/*+M*************************************************************************&n; * Perceptive Solutions, Inc. PCI-2000 device driver proc support for Linux.&n; *&n; * Copyright (c) 1997 Perceptive Solutions, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *&n; *&t;File Name:&t;&t;pci2000i.c&n; *&n; *-M*************************************************************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/bios32.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;pci2000.h&quot;
macro_line|#include &quot;psi_roy.h&quot;
macro_line|#include&lt;linux/stat.h&gt;
DECL|variable|Proc_Scsi_Pci2000
r_struct
id|proc_dir_entry
id|Proc_Scsi_Pci2000
op_assign
(brace
id|PROC_SCSI_PCI2000
comma
l_int|7
comma
l_string|&quot;pci2000&quot;
comma
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
comma
l_int|2
)brace
suffix:semicolon
singleline_comment|//#define DEBUG 1
macro_line|#ifdef DEBUG
DECL|macro|DEB
mdefine_line|#define DEB(x) x
DECL|macro|STOP_HERE
mdefine_line|#define STOP_HERE&t;{int st;for(st=0;st&lt;100;st++){st=1;}}
macro_line|#else
DECL|macro|DEB
mdefine_line|#define DEB(x)
DECL|macro|STOP_HERE
mdefine_line|#define STOP_HERE
macro_line|#endif
r_typedef
r_struct
(brace
DECL|member|address
id|ULONG
id|address
suffix:semicolon
DECL|member|length
id|ULONG
id|length
suffix:semicolon
DECL|typedef|SCATGATH
DECL|typedef|PSCATGATH
)brace
id|SCATGATH
comma
op_star
id|PSCATGATH
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|SCpnt
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
DECL|member|scatGath
id|SCATGATH
id|scatGath
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|tag
id|UCHAR
id|tag
suffix:semicolon
DECL|typedef|DEV2000
DECL|typedef|PDEV2000
)brace
id|DEV2000
comma
op_star
id|PDEV2000
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|basePort
id|USHORT
id|basePort
suffix:semicolon
DECL|member|mb0
id|USHORT
id|mb0
suffix:semicolon
DECL|member|mb1
id|USHORT
id|mb1
suffix:semicolon
DECL|member|mb2
id|USHORT
id|mb2
suffix:semicolon
DECL|member|mb3
id|USHORT
id|mb3
suffix:semicolon
DECL|member|mb4
id|USHORT
id|mb4
suffix:semicolon
DECL|member|cmd
id|USHORT
id|cmd
suffix:semicolon
DECL|member|tag
id|USHORT
id|tag
suffix:semicolon
DECL|member|dev
id|DEV2000
id|dev
(braket
id|MAX_BUS
)braket
(braket
id|MAX_UNITS
)braket
suffix:semicolon
DECL|typedef|ADAPTER2000
DECL|typedef|PADAPTER2000
)brace
id|ADAPTER2000
comma
op_star
id|PADAPTER2000
suffix:semicolon
DECL|macro|HOSTDATA
mdefine_line|#define HOSTDATA(host) ((PADAPTER2000)&amp;host-&gt;hostdata)
DECL|variable|PsiHost
r_static
r_struct
id|Scsi_Host
op_star
id|PsiHost
(braket
id|MAXADAPTER
)braket
op_assign
(brace
l_int|NULL
comma
)brace
suffix:semicolon
singleline_comment|// One for each adapter
DECL|variable|NumAdapters
r_static
r_int
id|NumAdapters
op_assign
l_int|0
suffix:semicolon
multiline_comment|/****************************************************************&n; *&t;Name:&t;&t;&t;WaitReady&t;:LOCAL&n; *&n; *&t;Description:&t;Wait for controller ready.&n; *&n; *&t;Parameters:&t;&t;padapter - Pointer adapter data structure.&n; *&n; *&t;Returns:&t;&t;TRUE on not ready.&n; *&n; ****************************************************************/
DECL|function|WaitReady
r_static
r_int
id|WaitReady
(paren
id|PADAPTER2000
id|padapter
)paren
(brace
id|ULONG
id|timer
suffix:semicolon
id|timer
op_assign
id|jiffies
op_plus
id|TIMEOUT_COMMAND
suffix:semicolon
singleline_comment|// calculate the timeout value
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
id|inb_p
(paren
id|padapter-&gt;cmd
)paren
)paren
r_return
id|FALSE
suffix:semicolon
)brace
r_while
c_loop
(paren
id|timer
OG
id|jiffies
)paren
suffix:semicolon
singleline_comment|// test for timeout
r_return
id|TRUE
suffix:semicolon
)brace
multiline_comment|/****************************************************************&n; *&t;Name:&t;OpDone&t;:LOCAL&n; *&n; *&t;Description:&t;Clean up operation and issue done to caller.&n; *&n; *&t;Parameters:&t;&t;SCpnt&t;- Pointer to SCSI command structure.&n; *&t;&t;&t;&t;&t;status&t;- Caller status.&n; *&n; *&t;Returns:&t;&t;Nothing.&n; *&n; ****************************************************************/
DECL|function|OpDone
r_static
r_void
id|OpDone
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
id|ULONG
id|status
)paren
(brace
id|SCpnt-&gt;result
op_assign
id|status
suffix:semicolon
id|SCpnt-&gt;scsi_done
(paren
id|SCpnt
)paren
suffix:semicolon
)brace
multiline_comment|/****************************************************************&n; *&t;Name:&t;Command&t;&t;:LOCAL&n; *&n; *&t;Description:&t;Issue queued command to the PCI-2000.&n; *&n; *&t;Parameters:&t;&t;padapter - Pointer to adapter information structure.&n; *&t;&t;&t;&t;&t;cmd&t;&t; - PCI-2000 command byte.&n; *&n; *&t;Returns:&t;&t;Non-zero command tag if operation is accepted.&n; *&n; ****************************************************************/
DECL|function|Command
r_static
id|UCHAR
id|Command
(paren
id|PADAPTER2000
id|padapter
comma
id|UCHAR
id|cmd
)paren
(brace
id|outb_p
(paren
id|cmd
comma
id|padapter-&gt;cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|WaitReady
(paren
id|padapter
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|inw_p
(paren
id|padapter-&gt;mb0
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|inb_p
(paren
id|padapter-&gt;mb1
)paren
suffix:semicolon
)brace
multiline_comment|/****************************************************************&n; *&t;Name:&t;BuildSgList&t;&t;:LOCAL&n; *&n; *&t;Description:&t;Build the scatter gather list for controller.&n; *&n; *&t;Parameters:&t;&t;SCpnt&t; - Pointer to SCSI command structure.&n; *&t;&t;&t;&t;&t;padapter - Pointer to adapter information structure.&n; *&t;&t;&t;&t;&t;pdev&t; - Pointer to adapter device structure.&n; *&n; *&t;Returns:&t;&t;Non-zero in not scatter gather.&n; *&n; ****************************************************************/
DECL|function|BuildSgList
r_static
r_int
id|BuildSgList
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
id|PADAPTER2000
id|padapter
comma
id|PDEV2000
id|pdev
)paren
(brace
r_int
id|z
suffix:semicolon
r_if
c_cond
(paren
id|SCpnt-&gt;use_sg
)paren
(brace
r_for
c_loop
(paren
id|z
op_assign
l_int|0
suffix:semicolon
id|z
OL
id|SCpnt-&gt;use_sg
suffix:semicolon
id|z
op_increment
)paren
(brace
id|pdev-&gt;scatGath
(braket
id|z
)braket
dot
id|address
op_assign
id|virt_to_bus
(paren
(paren
(paren
r_struct
id|scatterlist
op_star
)paren
id|SCpnt-&gt;request_buffer
)paren
(braket
id|z
)braket
dot
id|address
)paren
suffix:semicolon
id|pdev-&gt;scatGath
(braket
id|z
)braket
dot
id|length
op_assign
(paren
(paren
r_struct
id|scatterlist
op_star
)paren
id|SCpnt-&gt;request_buffer
)paren
(braket
id|z
)braket
dot
id|length
suffix:semicolon
)brace
id|outl
(paren
id|virt_to_bus
(paren
id|pdev-&gt;scatGath
)paren
comma
id|padapter-&gt;mb2
)paren
suffix:semicolon
id|outl
(paren
(paren
id|SCpnt-&gt;use_sg
op_lshift
l_int|24
)paren
op_or
id|SCpnt-&gt;request_bufflen
comma
id|padapter-&gt;mb3
)paren
suffix:semicolon
r_return
id|FALSE
suffix:semicolon
)brace
id|outl
(paren
id|virt_to_bus
(paren
id|SCpnt-&gt;request_buffer
)paren
comma
id|padapter-&gt;mb2
)paren
suffix:semicolon
id|outl
(paren
id|SCpnt-&gt;request_bufflen
comma
id|padapter-&gt;mb3
)paren
suffix:semicolon
r_return
id|TRUE
suffix:semicolon
)brace
multiline_comment|/****************************************************************&n; *&t;Name:&t;Irq_Handler&t;:LOCAL&n; *&n; *&t;Description:&t;Interrupt handler.&n; *&n; *&t;Parameters:&t;&t;irq&t;&t;- Hardware IRQ number.&n; *&t;&t;&t;&t;&t;dev_id&t;-&n; *&t;&t;&t;&t;&t;regs&t;-&n; *&n; *&t;Returns:&t;&t;TRUE if drive is not ready in time.&n; *&n; ****************************************************************/
DECL|function|Irq_Handler
r_static
r_void
id|Irq_Handler
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|shost
op_assign
l_int|NULL
suffix:semicolon
singleline_comment|// Pointer to host data block
id|PADAPTER2000
id|padapter
suffix:semicolon
singleline_comment|// Pointer to adapter control structure
id|PDEV2000
id|pdev
suffix:semicolon
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
id|UCHAR
id|tag
op_assign
l_int|0
suffix:semicolon
id|UCHAR
id|tag0
suffix:semicolon
id|ULONG
id|error
suffix:semicolon
r_int
id|pun
suffix:semicolon
r_int
id|bus
suffix:semicolon
r_int
id|z
suffix:semicolon
id|DEB
c_func
(paren
id|printk
(paren
l_string|&quot;&bslash;npci2000 recieved interrupt &quot;
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|z
op_assign
l_int|0
suffix:semicolon
id|z
OL
id|NumAdapters
suffix:semicolon
id|z
op_increment
)paren
singleline_comment|// scan for interrupt to process
(brace
r_if
c_cond
(paren
id|PsiHost
(braket
id|z
)braket
op_member_access_from_pointer
id|irq
op_eq
(paren
id|UCHAR
)paren
(paren
id|irq
op_amp
l_int|0xFF
)paren
)paren
(brace
id|tag
op_assign
id|inb_p
(paren
id|HOSTDATA
c_func
(paren
id|PsiHost
(braket
id|z
)braket
)paren
op_member_access_from_pointer
id|tag
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tag
)paren
(brace
id|shost
op_assign
id|PsiHost
(braket
id|z
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|shost
)paren
(brace
id|DEB
(paren
id|printk
(paren
l_string|&quot;&bslash;npci2000: not my interrupt&quot;
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|padapter
op_assign
id|HOSTDATA
c_func
(paren
id|shost
)paren
suffix:semicolon
id|tag0
op_assign
id|tag
op_amp
l_int|0x7F
suffix:semicolon
singleline_comment|// mask off the error bit
r_for
c_loop
(paren
id|bus
op_assign
l_int|0
suffix:semicolon
id|bus
OL
id|MAX_BUS
suffix:semicolon
id|bus
op_increment
)paren
singleline_comment|// scan the busses
(brace
r_for
c_loop
(paren
id|pun
op_assign
l_int|0
suffix:semicolon
id|pun
OL
id|MAX_UNITS
suffix:semicolon
id|pun
op_increment
)paren
singleline_comment|// scan the targets
(brace
id|pdev
op_assign
op_amp
id|padapter-&gt;dev
(braket
id|bus
)braket
(braket
id|pun
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pdev-&gt;tag
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|pdev-&gt;tag
op_eq
id|tag0
)paren
singleline_comment|// is this it?
(brace
id|pdev-&gt;tag
op_assign
l_int|0
suffix:semicolon
id|SCpnt
op_assign
id|pdev-&gt;SCpnt
suffix:semicolon
r_goto
id|irqProceed
suffix:semicolon
)brace
)brace
)brace
id|outb_p
(paren
l_int|0xFF
comma
id|padapter-&gt;tag
)paren
suffix:semicolon
singleline_comment|// clear the op interrupt
id|outb_p
(paren
id|CMD_DONE
comma
id|padapter-&gt;cmd
)paren
suffix:semicolon
singleline_comment|// complete the op
r_return
suffix:semicolon
singleline_comment|// done, but, with what?
id|irqProceed
suffix:colon
suffix:semicolon
r_if
c_cond
(paren
id|tag
op_amp
id|ERR08_TAGGED
)paren
singleline_comment|// is there an error here?
(brace
r_if
c_cond
(paren
id|WaitReady
(paren
id|padapter
)paren
)paren
(brace
id|OpDone
(paren
id|SCpnt
comma
id|DID_TIME_OUT
op_lshift
l_int|16
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|outb_p
(paren
id|tag0
comma
id|padapter-&gt;mb0
)paren
suffix:semicolon
singleline_comment|// get real error code
id|outb_p
(paren
id|CMD_ERROR
comma
id|padapter-&gt;cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|WaitReady
(paren
id|padapter
)paren
)paren
singleline_comment|// wait for controller to suck up the op
(brace
id|OpDone
(paren
id|SCpnt
comma
id|DID_TIME_OUT
op_lshift
l_int|16
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|error
op_assign
id|inl
(paren
id|padapter-&gt;mb0
)paren
suffix:semicolon
singleline_comment|// get error data
id|outb_p
(paren
l_int|0xFF
comma
id|padapter-&gt;tag
)paren
suffix:semicolon
singleline_comment|// clear the op interrupt
id|outb_p
(paren
id|CMD_DONE
comma
id|padapter-&gt;cmd
)paren
suffix:semicolon
singleline_comment|// complete the op
id|DEB
(paren
id|printk
(paren
l_string|&quot;status: %lX &quot;
comma
id|error
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|0x00020002
)paren
singleline_comment|// is this error a check condition?
(brace
r_if
c_cond
(paren
id|bus
)paren
singleline_comment|// are we doint SCSI commands?
(brace
id|OpDone
(paren
id|SCpnt
comma
(paren
id|DID_OK
op_lshift
l_int|16
)paren
op_or
l_int|2
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|SCpnt-&gt;cmnd
op_eq
id|SCSIOP_TEST_UNIT_READY
)paren
id|OpDone
(paren
id|SCpnt
comma
(paren
id|DRIVER_SENSE
op_lshift
l_int|24
)paren
op_or
(paren
id|DID_OK
op_lshift
l_int|16
)paren
op_or
l_int|2
)paren
suffix:semicolon
singleline_comment|// test caller we have sense data too
r_else
id|OpDone
(paren
id|SCpnt
comma
id|DID_ERROR
op_lshift
l_int|16
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|OpDone
(paren
id|SCpnt
comma
id|DID_ERROR
op_lshift
l_int|16
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|outb_p
(paren
l_int|0xFF
comma
id|padapter-&gt;tag
)paren
suffix:semicolon
singleline_comment|// clear the op interrupt
id|outb_p
(paren
id|CMD_DONE
comma
id|padapter-&gt;cmd
)paren
suffix:semicolon
singleline_comment|// complete the op
id|OpDone
(paren
id|SCpnt
comma
id|DID_OK
op_lshift
l_int|16
)paren
suffix:semicolon
)brace
multiline_comment|/****************************************************************&n; *&t;Name:&t;Pci2220i_QueueCommand&n; *&n; *&t;Description:&t;Process a queued command from the SCSI manager.&n; *&n; *&t;Parameters:&t;&t;SCpnt - Pointer to SCSI command structure.&n; *&t;&t;&t;&t;&t;done  - Pointer to done function to call.&n; *&n; *&t;Returns:&t;&t;Status code.&n; *&n; ****************************************************************/
DECL|function|Pci2000_QueueCommand
r_int
id|Pci2000_QueueCommand
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
id|UCHAR
op_star
id|cdb
op_assign
(paren
id|UCHAR
op_star
)paren
id|SCpnt-&gt;cmnd
suffix:semicolon
singleline_comment|// Pointer to SCSI CDB
id|PADAPTER2000
id|padapter
op_assign
id|HOSTDATA
c_func
(paren
id|SCpnt-&gt;host
)paren
suffix:semicolon
singleline_comment|// Pointer to adapter control structure
r_int
id|rc
op_assign
op_minus
l_int|1
suffix:semicolon
singleline_comment|// command return code
id|UCHAR
id|bus
op_assign
id|SCpnt-&gt;channel
suffix:semicolon
id|UCHAR
id|pun
op_assign
id|SCpnt-&gt;target
suffix:semicolon
id|UCHAR
id|lun
op_assign
id|SCpnt-&gt;lun
suffix:semicolon
id|UCHAR
id|cmd
suffix:semicolon
id|PDEV2000
id|pdev
op_assign
op_amp
id|padapter-&gt;dev
(braket
id|bus
)braket
(braket
id|pun
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|done
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pci2000_queuecommand: %02X: done can&squot;t be NULL&bslash;n&quot;
comma
op_star
id|cdb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|SCpnt-&gt;scsi_done
op_assign
id|done
suffix:semicolon
id|pdev-&gt;SCpnt
op_assign
id|SCpnt
suffix:semicolon
singleline_comment|// Save this command data
r_if
c_cond
(paren
id|WaitReady
(paren
id|padapter
)paren
)paren
(brace
id|rc
op_assign
id|DID_ERROR
suffix:semicolon
r_goto
id|finished
suffix:semicolon
)brace
id|outw_p
(paren
id|pun
op_or
(paren
id|lun
op_lshift
l_int|8
)paren
comma
id|padapter-&gt;mb0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bus
)paren
(brace
id|DEB
(paren
r_if
(paren
op_star
id|cdb
)paren
id|printk
(paren
l_string|&quot;&bslash;nCDB: %X-  %X %X %X %X %X %X %X %X %X %X &quot;
comma
id|SCpnt-&gt;cmd_len
comma
id|cdb
(braket
l_int|0
)braket
comma
id|cdb
(braket
l_int|1
)braket
comma
id|cdb
(braket
l_int|2
)braket
comma
id|cdb
(braket
l_int|3
)braket
comma
id|cdb
(braket
l_int|4
)braket
comma
id|cdb
(braket
l_int|5
)braket
comma
id|cdb
(braket
l_int|6
)braket
comma
id|cdb
(braket
l_int|7
)braket
comma
id|cdb
(braket
l_int|8
)braket
comma
id|cdb
(braket
l_int|9
)braket
)paren
)paren
suffix:semicolon
id|DEB
(paren
r_if
(paren
op_star
id|cdb
)paren
id|printk
(paren
l_string|&quot;&bslash;ntimeout_per_command: %d, timeout_total: %d, timeout: %d, internal_timout: %d&quot;
comma
id|SCpnt-&gt;timeout_per_command
comma
id|SCpnt-&gt;timeout_total
comma
id|SCpnt-&gt;timeout
comma
id|SCpnt-&gt;internal_timeout
)paren
)paren
suffix:semicolon
id|outl
(paren
id|SCpnt-&gt;timeout_per_command
comma
id|padapter-&gt;mb1
)paren
suffix:semicolon
id|outb_p
(paren
id|CMD_SCSI_TIMEOUT
comma
id|padapter-&gt;cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|WaitReady
(paren
id|padapter
)paren
)paren
(brace
id|rc
op_assign
id|DID_ERROR
suffix:semicolon
r_goto
id|finished
suffix:semicolon
)brace
id|outw_p
(paren
id|pun
op_or
(paren
id|lun
op_lshift
l_int|8
)paren
comma
id|padapter-&gt;mb0
)paren
suffix:semicolon
id|outw_p
(paren
id|SCpnt-&gt;cmd_len
op_lshift
l_int|8
comma
id|padapter-&gt;mb0
op_plus
l_int|2
)paren
suffix:semicolon
id|outl
(paren
id|virt_to_bus
(paren
id|cdb
)paren
comma
id|padapter-&gt;mb1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|BuildSgList
(paren
id|SCpnt
comma
id|padapter
comma
id|pdev
)paren
)paren
id|cmd
op_assign
id|CMD_SCSI_THRU
suffix:semicolon
r_else
id|cmd
op_assign
id|CMD_SCSI_THRU_SG
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pdev-&gt;tag
op_assign
id|Command
(paren
id|padapter
comma
id|cmd
)paren
)paren
op_eq
l_int|0
)paren
id|rc
op_assign
id|DID_TIME_OUT
suffix:semicolon
r_goto
id|finished
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|lun
)paren
(brace
id|rc
op_assign
id|DID_BAD_TARGET
suffix:semicolon
r_goto
id|finished
suffix:semicolon
)brace
)brace
r_switch
c_cond
(paren
op_star
id|cdb
)paren
(brace
r_case
id|SCSIOP_INQUIRY
suffix:colon
singleline_comment|// inquiry CDB
(brace
r_if
c_cond
(paren
id|SCpnt-&gt;use_sg
)paren
(brace
id|outl
(paren
id|virt_to_bus
(paren
(paren
(paren
r_struct
id|scatterlist
op_star
)paren
(paren
id|SCpnt-&gt;request_buffer
)paren
)paren
op_member_access_from_pointer
id|address
)paren
comma
id|padapter-&gt;mb2
)paren
suffix:semicolon
)brace
r_else
(brace
id|outl
(paren
id|virt_to_bus
(paren
id|SCpnt-&gt;request_buffer
)paren
comma
id|padapter-&gt;mb2
)paren
suffix:semicolon
)brace
id|outl
(paren
id|SCpnt-&gt;request_bufflen
comma
id|padapter-&gt;mb3
)paren
suffix:semicolon
id|cmd
op_assign
id|CMD_DASD_SCSI_INQ
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|SCSIOP_TEST_UNIT_READY
suffix:colon
singleline_comment|// test unit ready CDB
id|outl
(paren
id|virt_to_bus
(paren
id|SCpnt-&gt;sense_buffer
)paren
comma
id|padapter-&gt;mb2
)paren
suffix:semicolon
id|outl
(paren
r_sizeof
(paren
id|SCpnt-&gt;sense_buffer
)paren
comma
id|padapter-&gt;mb3
)paren
suffix:semicolon
id|cmd
op_assign
id|CMD_TEST_READY
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCSIOP_READ_CAPACITY
suffix:colon
singleline_comment|// read capctiy CDB
r_if
c_cond
(paren
id|SCpnt-&gt;use_sg
)paren
(brace
id|outl
(paren
id|virt_to_bus
(paren
(paren
(paren
r_struct
id|scatterlist
op_star
)paren
(paren
id|SCpnt-&gt;request_buffer
)paren
)paren
op_member_access_from_pointer
id|address
)paren
comma
id|padapter-&gt;mb2
)paren
suffix:semicolon
)brace
r_else
(brace
id|outl
(paren
id|virt_to_bus
(paren
id|SCpnt-&gt;request_buffer
)paren
comma
id|padapter-&gt;mb2
)paren
suffix:semicolon
)brace
id|outl
(paren
l_int|8
comma
id|padapter-&gt;mb3
)paren
suffix:semicolon
id|cmd
op_assign
id|CMD_DASD_CAP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCSIOP_VERIFY
suffix:colon
singleline_comment|// verify CDB
id|outw_p
(paren
(paren
id|USHORT
)paren
id|cdb
(braket
l_int|8
)braket
op_or
(paren
(paren
id|USHORT
)paren
id|cdb
(braket
l_int|7
)braket
op_lshift
l_int|8
)paren
comma
id|padapter-&gt;mb0
op_plus
l_int|2
)paren
suffix:semicolon
id|outl
(paren
id|XSCSI2LONG
(paren
op_amp
id|cdb
(braket
l_int|2
)braket
)paren
comma
id|padapter-&gt;mb1
)paren
suffix:semicolon
id|cmd
op_assign
id|CMD_READ_SG
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCSIOP_READ
suffix:colon
singleline_comment|// read10 CDB
id|outw_p
(paren
(paren
id|USHORT
)paren
id|cdb
(braket
l_int|8
)braket
op_or
(paren
(paren
id|USHORT
)paren
id|cdb
(braket
l_int|7
)braket
op_lshift
l_int|8
)paren
comma
id|padapter-&gt;mb0
op_plus
l_int|2
)paren
suffix:semicolon
id|outl
(paren
id|XSCSI2LONG
(paren
op_amp
id|cdb
(braket
l_int|2
)braket
)paren
comma
id|padapter-&gt;mb1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|BuildSgList
(paren
id|SCpnt
comma
id|padapter
comma
id|pdev
)paren
)paren
id|cmd
op_assign
id|CMD_READ
suffix:semicolon
r_else
id|cmd
op_assign
id|CMD_READ_SG
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCSIOP_READ6
suffix:colon
singleline_comment|// read6  CDB
id|outw_p
(paren
id|cdb
(braket
l_int|4
)braket
comma
id|padapter-&gt;mb0
op_plus
l_int|2
)paren
suffix:semicolon
id|outl
(paren
(paren
id|SCSI2LONG
(paren
op_amp
id|cdb
(braket
l_int|1
)braket
)paren
)paren
op_amp
l_int|0x001FFFFF
comma
id|padapter-&gt;mb1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|BuildSgList
(paren
id|SCpnt
comma
id|padapter
comma
id|pdev
)paren
)paren
id|cmd
op_assign
id|CMD_READ
suffix:semicolon
r_else
id|cmd
op_assign
id|CMD_READ_SG
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCSIOP_WRITE
suffix:colon
singleline_comment|// write10 CDB
id|outw_p
(paren
(paren
id|USHORT
)paren
id|cdb
(braket
l_int|8
)braket
op_or
(paren
(paren
id|USHORT
)paren
id|cdb
(braket
l_int|7
)braket
op_lshift
l_int|8
)paren
comma
id|padapter-&gt;mb0
op_plus
l_int|2
)paren
suffix:semicolon
id|outl
(paren
id|XSCSI2LONG
(paren
op_amp
id|cdb
(braket
l_int|2
)braket
)paren
comma
id|padapter-&gt;mb1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|BuildSgList
(paren
id|SCpnt
comma
id|padapter
comma
id|pdev
)paren
)paren
id|cmd
op_assign
id|CMD_WRITE
suffix:semicolon
r_else
id|cmd
op_assign
id|CMD_WRITE_SG
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCSIOP_WRITE6
suffix:colon
singleline_comment|// write6  CDB
id|outw_p
(paren
id|cdb
(braket
l_int|4
)braket
comma
id|padapter-&gt;mb0
op_plus
l_int|2
)paren
suffix:semicolon
id|outl
(paren
(paren
id|SCSI2LONG
(paren
op_amp
id|cdb
(braket
l_int|1
)braket
)paren
)paren
op_amp
l_int|0x001FFFFF
comma
id|padapter-&gt;mb1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|BuildSgList
(paren
id|SCpnt
comma
id|padapter
comma
id|pdev
)paren
)paren
id|cmd
op_assign
id|CMD_WRITE
suffix:semicolon
r_else
id|cmd
op_assign
id|CMD_WRITE_SG
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCSIOP_START_STOP_UNIT
suffix:colon
id|cmd
op_assign
id|CMD_EJECT_MEDIA
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCSIOP_MEDIUM_REMOVAL
suffix:colon
r_switch
c_cond
(paren
id|cdb
(braket
l_int|4
)braket
)paren
(brace
r_case
l_int|0
suffix:colon
id|cmd
op_assign
id|CMD_UNLOCK_DOOR
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|cmd
op_assign
id|CMD_LOCK_DOOR
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|cmd
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd
)paren
r_break
suffix:semicolon
r_default
suffix:colon
id|DEB
(paren
id|printk
(paren
l_string|&quot;pci2220i_queuecommand: Unsupported command %02X&bslash;n&quot;
comma
op_star
id|cdb
)paren
)paren
suffix:semicolon
id|OpDone
(paren
id|SCpnt
comma
id|DID_ERROR
op_lshift
l_int|16
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|pdev-&gt;tag
op_assign
id|Command
(paren
id|padapter
comma
id|cmd
)paren
)paren
op_eq
l_int|0
)paren
id|rc
op_assign
id|DID_TIME_OUT
suffix:semicolon
id|finished
suffix:colon
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
op_minus
l_int|1
)paren
id|OpDone
(paren
id|SCpnt
comma
id|rc
op_lshift
l_int|16
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/****************************************************************&n; *&t;Name:&t;internal_done :LOCAL&n; *&n; *&t;Description:&t;Done handler for non-queued commands&n; *&n; *&t;Parameters:&t;&t;SCpnt - Pointer to SCSI command structure.&n; *&n; *&t;Returns:&t;&t;Nothing.&n; *&n; ****************************************************************/
DECL|function|internal_done
r_static
r_void
id|internal_done
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
id|SCpnt-&gt;SCp.Status
op_increment
suffix:semicolon
)brace
multiline_comment|/****************************************************************&n; *&t;Name:&t;Pci2220i_Command&n; *&n; *&t;Description:&t;Process a command from the SCSI manager.&n; *&n; *&t;Parameters:&t;&t;SCpnt - Pointer to SCSI command structure.&n; *&n; *&t;Returns:&t;&t;Status code.&n; *&n; ****************************************************************/
DECL|function|Pci2000_Command
r_int
id|Pci2000_Command
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
l_string|&quot;pci2000_command: ..calling pci2000_queuecommand&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|Pci2000_QueueCommand
(paren
id|SCpnt
comma
id|internal_done
)paren
suffix:semicolon
id|SCpnt-&gt;SCp.Status
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|SCpnt-&gt;SCp.Status
)paren
id|barrier
(paren
)paren
suffix:semicolon
r_return
id|SCpnt-&gt;result
suffix:semicolon
)brace
multiline_comment|/****************************************************************&n; *&t;Name:&t;Pci2220i_Detect&n; *&n; *&t;Description:&t;Detect and initialize our boards.&n; *&n; *&t;Parameters:&t;&t;tpnt - Pointer to SCSI host template structure.&n; *&n; *&t;Returns:&t;&t;Number of adapters found.&n; *&n; ****************************************************************/
DECL|function|Pci2000_Detect
r_int
id|Pci2000_Detect
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
(brace
r_int
id|pci_index
op_assign
l_int|0
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|pshost
suffix:semicolon
id|PADAPTER2000
id|padapter
suffix:semicolon
r_int
id|z
suffix:semicolon
r_int
id|setirq
suffix:semicolon
r_if
c_cond
(paren
id|pcibios_present
(paren
)paren
)paren
(brace
r_for
c_loop
(paren
id|pci_index
op_assign
l_int|0
suffix:semicolon
id|pci_index
op_le
id|MAXADAPTER
suffix:semicolon
op_increment
id|pci_index
)paren
(brace
id|UCHAR
id|pci_bus
comma
id|pci_device_fn
suffix:semicolon
r_if
c_cond
(paren
id|pcibios_find_device
(paren
id|VENDOR_PSI
comma
id|DEVICE_ROY_1
comma
id|pci_index
comma
op_amp
id|pci_bus
comma
op_amp
id|pci_device_fn
)paren
op_ne
l_int|0
)paren
r_break
suffix:semicolon
id|pshost
op_assign
id|scsi_register
(paren
id|tpnt
comma
r_sizeof
(paren
id|ADAPTER2000
)paren
)paren
suffix:semicolon
id|padapter
op_assign
id|HOSTDATA
c_func
(paren
id|pshost
)paren
suffix:semicolon
id|pcibios_read_config_word
(paren
id|pci_bus
comma
id|pci_device_fn
comma
id|PCI_BASE_ADDRESS_1
comma
op_amp
id|padapter-&gt;basePort
)paren
suffix:semicolon
id|padapter-&gt;basePort
op_and_assign
l_int|0xFFFE
suffix:semicolon
id|DEB
(paren
id|printk
(paren
l_string|&quot;&bslash;nBase Regs = %#04X&quot;
comma
id|padapter-&gt;basePort
)paren
)paren
suffix:semicolon
singleline_comment|// get the base I/O port address
id|padapter-&gt;mb0
op_assign
id|padapter-&gt;basePort
op_plus
id|RTR_MAILBOX
suffix:semicolon
singleline_comment|// get the 32 bit mail boxes
id|padapter-&gt;mb1
op_assign
id|padapter-&gt;basePort
op_plus
id|RTR_MAILBOX
op_plus
l_int|4
suffix:semicolon
id|padapter-&gt;mb2
op_assign
id|padapter-&gt;basePort
op_plus
id|RTR_MAILBOX
op_plus
l_int|8
suffix:semicolon
id|padapter-&gt;mb3
op_assign
id|padapter-&gt;basePort
op_plus
id|RTR_MAILBOX
op_plus
l_int|12
suffix:semicolon
id|padapter-&gt;mb4
op_assign
id|padapter-&gt;basePort
op_plus
id|RTR_MAILBOX
op_plus
l_int|16
suffix:semicolon
id|padapter-&gt;cmd
op_assign
id|padapter-&gt;basePort
op_plus
id|RTR_LOCAL_DOORBELL
suffix:semicolon
singleline_comment|// command register
id|padapter-&gt;tag
op_assign
id|padapter-&gt;basePort
op_plus
id|RTR_PCI_DOORBELL
suffix:semicolon
singleline_comment|// tag/response register
r_if
c_cond
(paren
id|WaitReady
(paren
id|padapter
)paren
)paren
r_goto
id|unregister
suffix:semicolon
id|outb_p
(paren
l_int|0x84
comma
id|padapter-&gt;mb0
)paren
suffix:semicolon
id|outb_p
(paren
id|CMD_SPECIFY
comma
id|padapter-&gt;cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|WaitReady
(paren
id|padapter
)paren
)paren
r_goto
id|unregister
suffix:semicolon
id|pcibios_read_config_byte
(paren
id|pci_bus
comma
id|pci_device_fn
comma
id|PCI_INTERRUPT_LINE
comma
op_amp
id|pshost-&gt;irq
)paren
suffix:semicolon
id|setirq
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|z
op_assign
l_int|0
suffix:semicolon
id|z
OL
id|pci_index
suffix:semicolon
id|z
op_increment
)paren
singleline_comment|// scan for shared interrupts
(brace
r_if
c_cond
(paren
id|PsiHost
(braket
id|z
)braket
op_member_access_from_pointer
id|irq
op_eq
id|pshost-&gt;irq
)paren
singleline_comment|// if shared then, don&squot;t posses
id|setirq
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|setirq
)paren
singleline_comment|// if not shared, posses
(brace
r_if
c_cond
(paren
id|request_irq
(paren
id|pshost-&gt;irq
comma
id|Irq_Handler
comma
l_int|0
comma
l_string|&quot;pci2000&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;Unable to allocate IRQ for PSI-2000 controller.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|unregister
suffix:semicolon
)brace
)brace
id|PsiHost
(braket
id|pci_index
)braket
op_assign
id|pshost
suffix:semicolon
singleline_comment|// save SCSI_HOST pointer
id|pshost-&gt;unique_id
op_assign
id|padapter-&gt;basePort
suffix:semicolon
id|pshost-&gt;max_id
op_assign
l_int|16
suffix:semicolon
id|pshost-&gt;max_channel
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nPSI-2000 EIDE CONTROLLER: at I/O = %X  IRQ = %d&bslash;n&quot;
comma
id|padapter-&gt;basePort
comma
id|pshost-&gt;irq
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;(C) 1997 Perceptive Solutions, Inc. All rights reserved&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
id|unregister
suffix:colon
suffix:semicolon
id|scsi_unregister
(paren
id|pshost
)paren
suffix:semicolon
)brace
)brace
id|NumAdapters
op_assign
id|pci_index
suffix:semicolon
r_return
id|pci_index
suffix:semicolon
)brace
multiline_comment|/****************************************************************&n; *&t;Name:&t;Pci2220i_Abort&n; *&n; *&t;Description:&t;Process the Abort command from the SCSI manager.&n; *&n; *&t;Parameters:&t;&t;SCpnt - Pointer to SCSI command structure.&n; *&n; *&t;Returns:&t;&t;Allways snooze.&n; *&n; ****************************************************************/
DECL|function|Pci2000_Abort
r_int
id|Pci2000_Abort
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
id|DEB
(paren
id|printk
(paren
l_string|&quot;pci2000_abort&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
id|SCSI_ABORT_SNOOZE
suffix:semicolon
)brace
multiline_comment|/****************************************************************&n; *&t;Name:&t;Pci2220i_Reset&n; *&n; *&t;Description:&t;Process the Reset command from the SCSI manager.&n; *&n; *&t;Parameters:&t;&t;SCpnt - Pointer to SCSI command structure.&n; *&t;&t;&t;&t;&t;flags - Flags about the reset command&n; *&n; *&t;Returns:&t;&t;No active command at this time, so this means&n; *&t;&t;&t;&t;&t;that each time we got some kind of response the&n; *&t;&t;&t;&t;&t;last time through.  Tell the mid-level code to&n; *&t;&t;&t;&t;&t;request sense information in order to decide what&n; *&t;&t;&t;&t;&t;to do next.&n; *&n; ****************************************************************/
DECL|function|Pci2000_Reset
r_int
id|Pci2000_Reset
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
comma
r_int
r_int
id|reset_flags
)paren
(brace
r_return
id|SCSI_RESET_PUNT
suffix:semicolon
)brace
macro_line|#include &quot;sd.h&quot;
multiline_comment|/****************************************************************&n; *&t;Name:&t;Pci2220i_BiosParam&n; *&n; *&t;Description:&t;Process the biosparam request from the SCSI manager to&n; *&t;&t;&t;&t;&t;return C/H/S data.&n; *&n; *&t;Parameters:&t;&t;disk - Pointer to SCSI disk structure.&n; *&t;&t;&t;&t;&t;dev&t; - Major/minor number from kernel.&n; *&t;&t;&t;&t;&t;geom - Pointer to integer array to place geometry data.&n; *&n; *&t;Returns:&t;&t;zero.&n; *&n; ****************************************************************/
DECL|function|Pci2000_BiosParam
r_int
id|Pci2000_BiosParam
(paren
id|Scsi_Disk
op_star
id|disk
comma
id|kdev_t
id|dev
comma
r_int
id|geom
(braket
)braket
)paren
(brace
id|PADAPTER2000
id|padapter
suffix:semicolon
id|padapter
op_assign
id|HOSTDATA
c_func
(paren
id|disk-&gt;device-&gt;host
)paren
suffix:semicolon
r_if
c_cond
(paren
id|WaitReady
(paren
id|padapter
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|outb_p
(paren
id|disk-&gt;device-&gt;id
comma
id|padapter-&gt;mb0
)paren
suffix:semicolon
id|outb_p
(paren
id|CMD_GET_PARMS
comma
id|padapter-&gt;cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|WaitReady
(paren
id|padapter
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|geom
(braket
l_int|0
)braket
op_assign
id|inb_p
(paren
id|padapter-&gt;mb2
op_plus
l_int|3
)paren
suffix:semicolon
id|geom
(braket
l_int|1
)braket
op_assign
id|inb_p
(paren
id|padapter-&gt;mb2
op_plus
l_int|2
)paren
suffix:semicolon
id|geom
(braket
l_int|2
)braket
op_assign
id|inw_p
(paren
id|padapter-&gt;mb2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
multiline_comment|/* Eventually this will go into an include file, but this will be later */
DECL|variable|driver_template
id|Scsi_Host_Template
id|driver_template
op_assign
id|PCI2220I
suffix:semicolon
macro_line|#include &quot;scsi_module.c&quot;
macro_line|#endif
eof