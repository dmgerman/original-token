macro_line|#include &lt;linux/autoconf.h&gt;
multiline_comment|/*&n; * We should not even be trying to compile this if we are not doing&n; * a module.&n; */
macro_line|#ifndef MODULE
macro_line|#error Go away.
macro_line|#endif
multiline_comment|/*&n; * Even though we are building a module, we need to undef this, since&n; * we are building a symbol table to be used by other modules.  For&n; * the symbol table to build properly, we need to undefine this.&n; */
DECL|macro|MODULE
macro_line|#undef MODULE
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &quot;../block/blk.h&quot;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;constants.h&quot;
macro_line|#include &quot;sd.h&quot;
multiline_comment|/*&n; * This source file contains the symbol table used by scsi loadable&n; * modules.&n; */
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
macro_line|#ifdef CONFIG_MODVERSIONS
(brace
(paren
r_void
op_star
)paren
l_int|1
multiline_comment|/* Version version :-) */
comma
id|SYMBOL_NAME_STR
c_func
(paren
l_string|&quot;Using_Versions&quot;
)paren
)brace
comma
macro_line|#endif
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
eof
