multiline_comment|/*&n; *  scsi_module.c Copyright (1994, 1995) Eric Youngdale.&n; *&n; * Support for loading low-level scsi drivers using the linux kernel loadable&n; * module interface.&n; *&n; * To use, the host adapter should first define and initialize the variable&n; * driver_template (datatype Scsi_Host_Template), and then include this file.&n; * This should also be wrapped in a #ifdef MODULE/#endif.&n; *&n; * The low -level driver must also define a release function which will&n; * free any irq assignments, release any dma channels, release any I/O&n; * address space that might be reserved, and otherwise clean up after itself.&n; * The idea is that the same driver should be able to be reloaded without&n; * any difficulty.  This makes debugging new drivers easier, as you should&n; * be able to load the driver, test it, unload, modify and reload.&n; *&n; * One *very* important caveat.  If the driver may need to do DMA on the&n; * ISA bus, you must have unchecked_isa_dma set in the device template,&n; * even if this might be changed during the detect routine.  This is&n; * because the shpnt structure will be allocated in a special way so that&n; * it will be below the appropriate DMA limit - thus if your driver uses&n; * the hostdata field of shpnt, and the board must be able to access this&n; * via DMA, the shpnt structure must be in a DMA accessible region of&n; * memory.  This comment would be relevant for something like the buslogic&n; * driver where there are many boards, only some of which do DMA onto the&n; * ISA bus.  There is no convenient way of specifying whether the host&n; * needs to be in a ISA DMA accessible region of memory when you call&n; * scsi_register.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|function|init_this_scsi_driver
r_static
r_int
id|__init
id|init_this_scsi_driver
c_func
(paren
r_void
)paren
(brace
id|driver_template.module
op_assign
id|THIS_MODULE
suffix:semicolon
id|scsi_register_module
c_func
(paren
id|MODULE_SCSI_HA
comma
op_amp
id|driver_template
)paren
suffix:semicolon
r_if
c_cond
(paren
id|driver_template.present
)paren
r_return
l_int|0
suffix:semicolon
id|scsi_unregister_module
c_func
(paren
id|MODULE_SCSI_HA
comma
op_amp
id|driver_template
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|exit_this_scsi_driver
r_static
r_void
id|__exit
id|exit_this_scsi_driver
c_func
(paren
r_void
)paren
(brace
id|scsi_unregister_module
c_func
(paren
id|MODULE_SCSI_HA
comma
op_amp
id|driver_template
)paren
suffix:semicolon
)brace
DECL|variable|init_this_scsi_driver
id|module_init
c_func
(paren
id|init_this_scsi_driver
)paren
suffix:semicolon
DECL|variable|exit_this_scsi_driver
id|module_exit
c_func
(paren
id|exit_this_scsi_driver
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we almost follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
