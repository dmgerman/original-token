multiline_comment|/*&n; * We should not even be trying to compile this if we are not doing&n; * a module.&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_MODULES
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;scsi_ioctl.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;constants.h&quot;
macro_line|#include &quot;sd.h&quot;
multiline_comment|/*&n; * This source file contains the symbol table used by scsi loadable&n; * modules.&n; */
r_extern
r_int
id|scsicam_bios_param
(paren
id|Disk
op_star
id|disk
comma
r_int
id|dev
comma
r_int
op_star
id|ip
)paren
suffix:semicolon
r_extern
r_void
id|print_command
(paren
r_int
r_char
op_star
id|command
)paren
suffix:semicolon
r_extern
r_void
id|print_sense
c_func
(paren
r_const
r_char
op_star
id|devclass
comma
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
DECL|variable|scsi_symbol_table
r_struct
id|symbol_table
id|scsi_symbol_table
op_assign
(brace
macro_line|#include &lt;linux/symtab_begin.h&gt;
id|X
c_func
(paren
id|scsi_register_module
)paren
comma
id|X
c_func
(paren
id|scsi_unregister_module
)paren
comma
id|X
c_func
(paren
id|scsi_free
)paren
comma
id|X
c_func
(paren
id|scsi_malloc
)paren
comma
id|X
c_func
(paren
id|scsi_register
)paren
comma
id|X
c_func
(paren
id|scsi_unregister
)paren
comma
id|X
c_func
(paren
id|scsicam_bios_param
)paren
comma
id|X
c_func
(paren
id|allocate_device
)paren
comma
id|X
c_func
(paren
id|scsi_do_cmd
)paren
comma
id|X
c_func
(paren
id|scsi_command_size
)paren
comma
id|X
c_func
(paren
id|scsi_init_malloc
)paren
comma
id|X
c_func
(paren
id|scsi_init_free
)paren
comma
id|X
c_func
(paren
id|scsi_ioctl
)paren
comma
id|X
c_func
(paren
id|print_command
)paren
comma
id|X
c_func
(paren
id|print_sense
)paren
comma
id|X
c_func
(paren
id|print_msg
)paren
comma
id|X
c_func
(paren
id|print_status
)paren
comma
id|X
c_func
(paren
id|dma_free_sectors
)paren
comma
id|X
c_func
(paren
id|kernel_scsi_ioctl
)paren
comma
id|X
c_func
(paren
id|need_isa_buffer
)paren
comma
id|X
c_func
(paren
id|request_queueable
)paren
comma
id|X
c_func
(paren
id|print_Scsi_Cmnd
)paren
comma
id|X
c_func
(paren
id|scsi_mark_host_reset
)paren
comma
id|X
c_func
(paren
id|scsi_mark_bus_reset
)paren
comma
macro_line|#if defined(CONFIG_PROC_FS)
id|X
c_func
(paren
id|proc_print_scsidevice
)paren
comma
macro_line|#endif
multiline_comment|/*&n; * These are here only while I debug the rest of the scsi stuff.&n; */
id|X
c_func
(paren
id|scsi_hostlist
)paren
comma
id|X
c_func
(paren
id|scsi_hosts
)paren
comma
id|X
c_func
(paren
id|scsi_devicelist
)paren
comma
id|X
c_func
(paren
id|scsi_devices
)paren
comma
multiline_comment|/********************************************************&n;     * Do not add anything below this line,&n;     * as the stacked modules depend on this!&n;     */
macro_line|#include &lt;linux/symtab_end.h&gt;
)brace
suffix:semicolon
macro_line|#endif
eof
