multiline_comment|/* Parallel-port initialisation code.&n; * &n; * Authors: David Campbell &lt;campbell@torque.net&gt;&n; *          Tim Waugh &lt;tim@cyberelk.demon.co.uk&gt;&n; *&t;    Jose Renau &lt;renau@acm.org&gt;&n; *&n; * based on work by Grant Guenther &lt;grant@torque.net&gt;&n; *              and Philip Blundell &lt;Philip.Blundell@pobox.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifndef MODULE
DECL|variable|__initdata
r_static
r_int
id|io
(braket
id|PARPORT_MAX
op_plus
l_int|1
)braket
id|__initdata
op_assign
(brace
(braket
l_int|0
dot
dot
dot
id|PARPORT_MAX
)braket
op_assign
l_int|0
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_PARPORT_PC
DECL|variable|__initdata
r_static
r_int
id|io_hi
(braket
id|PARPORT_MAX
op_plus
l_int|1
)braket
id|__initdata
op_assign
(brace
(braket
l_int|0
dot
dot
dot
id|PARPORT_MAX
)braket
op_assign
l_int|0
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|__initdata
r_static
r_int
id|irq
(braket
id|PARPORT_MAX
)braket
id|__initdata
op_assign
(brace
(braket
l_int|0
dot
dot
dot
id|PARPORT_MAX
op_minus
l_int|1
)braket
op_assign
id|PARPORT_IRQ_PROBEONLY
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|dma
(braket
id|PARPORT_MAX
)braket
id|__initdata
op_assign
(brace
(braket
l_int|0
dot
dot
dot
id|PARPORT_MAX
op_minus
l_int|1
)braket
op_assign
id|PARPORT_DMA_NONE
)brace
suffix:semicolon
r_extern
r_int
id|parport_pc_init
c_func
(paren
r_int
op_star
id|io
comma
r_int
op_star
id|io_hi
comma
r_int
op_star
id|irq
comma
r_int
op_star
id|dma
)paren
suffix:semicolon
r_extern
r_int
id|parport_sunbpp_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|parport_amiga_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|parport_mfc3_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|parport_setup_ptr
id|__initdata
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Acceptable parameters:&n; *&n; * parport=0&n; * parport=auto&n; * parport=0xBASE[,IRQ[,DMA]]&n; *&n; * IRQ/DMA may be numeric or &squot;auto&squot; or &squot;none&squot;&n; */
DECL|function|parport_setup
r_static
r_int
id|__init
id|parport_setup
(paren
r_char
op_star
id|str
)paren
(brace
r_char
op_star
id|endptr
suffix:semicolon
r_char
op_star
id|sep
suffix:semicolon
r_int
id|val
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|str
op_logical_or
op_logical_neg
op_star
id|str
op_logical_or
(paren
op_star
id|str
op_eq
l_char|&squot;0&squot;
op_logical_and
op_logical_neg
op_star
(paren
id|str
op_plus
l_int|1
)paren
)paren
)paren
(brace
multiline_comment|/* Disable parport if &quot;parport=0&quot; in cmdline */
id|io
(braket
l_int|0
)braket
op_assign
id|PARPORT_DISABLE
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
(paren
id|str
comma
l_string|&quot;auto&quot;
comma
l_int|4
)paren
)paren
(brace
id|irq
(braket
l_int|0
)braket
op_assign
id|PARPORT_IRQ_AUTO
suffix:semicolon
id|dma
(braket
l_int|0
)braket
op_assign
id|PARPORT_DMA_AUTO
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|val
op_assign
id|simple_strtoul
(paren
id|str
comma
op_amp
id|endptr
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|endptr
op_eq
id|str
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;parport=%s not understood&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|parport_setup_ptr
op_eq
id|PARPORT_MAX
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;parport=%s ignored, too many ports&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|io
(braket
id|parport_setup_ptr
)braket
op_assign
id|val
suffix:semicolon
id|irq
(braket
id|parport_setup_ptr
)braket
op_assign
id|PARPORT_IRQ_NONE
suffix:semicolon
id|dma
(braket
id|parport_setup_ptr
)braket
op_assign
id|PARPORT_DMA_NONE
suffix:semicolon
id|sep
op_assign
id|strchr
(paren
id|str
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sep
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
(paren
id|sep
comma
l_string|&quot;auto&quot;
comma
l_int|4
)paren
)paren
id|irq
(braket
id|parport_setup_ptr
)braket
op_assign
id|PARPORT_IRQ_AUTO
suffix:semicolon
r_else
r_if
c_cond
(paren
id|strncmp
(paren
id|sep
comma
l_string|&quot;none&quot;
comma
l_int|4
)paren
)paren
(brace
id|val
op_assign
id|simple_strtoul
(paren
id|sep
comma
op_amp
id|endptr
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|endptr
op_eq
id|sep
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;parport=%s: irq not understood&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|irq
(braket
id|parport_setup_ptr
)braket
op_assign
id|val
suffix:semicolon
)brace
)brace
id|sep
op_assign
id|strchr
(paren
id|sep
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sep
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
(paren
id|sep
comma
l_string|&quot;auto&quot;
comma
l_int|4
)paren
)paren
id|dma
(braket
id|parport_setup_ptr
)braket
op_assign
id|PARPORT_DMA_AUTO
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
(paren
id|sep
comma
l_string|&quot;nofifo&quot;
comma
l_int|6
)paren
)paren
id|dma
(braket
id|parport_setup_ptr
)braket
op_assign
id|PARPORT_DMA_NOFIFO
suffix:semicolon
r_else
r_if
c_cond
(paren
id|strncmp
(paren
id|sep
comma
l_string|&quot;none&quot;
comma
l_int|4
)paren
)paren
(brace
id|val
op_assign
id|simple_strtoul
(paren
id|sep
comma
op_amp
id|endptr
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|endptr
op_eq
id|sep
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;parport=%s: dma not understood&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|dma
(braket
id|parport_setup_ptr
)braket
op_assign
id|val
suffix:semicolon
)brace
)brace
id|parport_setup_ptr
op_increment
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
(paren
l_string|&quot;parport=&quot;
comma
id|parport_setup
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SYSCTL
id|parport_default_proc_register
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
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
macro_line|#ifdef CONFIG_SYSCTL
id|parport_default_proc_unregister
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#else
DECL|function|parport_init
r_int
id|__init
id|parport_init
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|io
(braket
l_int|0
)braket
op_eq
id|PARPORT_DISABLE
)paren
r_return
l_int|1
suffix:semicolon
macro_line|#ifdef CONFIG_SYSCTL
id|parport_default_proc_register
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PARPORT_PC
id|parport_pc_init
c_func
(paren
id|io
comma
id|io_hi
comma
id|irq
comma
id|dma
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PARPORT_AMIGA
id|parport_amiga_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PARPORT_MFC3
id|parport_mfc3_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PARPORT_ATARI
id|parport_atari_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PARPORT_ARC
id|parport_arc_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PARPORT_SUNBPP
id|parport_sunbpp_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Exported symbols for modules. */
DECL|variable|parport_claim
id|EXPORT_SYMBOL
c_func
(paren
id|parport_claim
)paren
suffix:semicolon
DECL|variable|parport_claim_or_block
id|EXPORT_SYMBOL
c_func
(paren
id|parport_claim_or_block
)paren
suffix:semicolon
DECL|variable|parport_release
id|EXPORT_SYMBOL
c_func
(paren
id|parport_release
)paren
suffix:semicolon
DECL|variable|parport_register_port
id|EXPORT_SYMBOL
c_func
(paren
id|parport_register_port
)paren
suffix:semicolon
DECL|variable|parport_announce_port
id|EXPORT_SYMBOL
c_func
(paren
id|parport_announce_port
)paren
suffix:semicolon
DECL|variable|parport_unregister_port
id|EXPORT_SYMBOL
c_func
(paren
id|parport_unregister_port
)paren
suffix:semicolon
DECL|variable|parport_register_driver
id|EXPORT_SYMBOL
c_func
(paren
id|parport_register_driver
)paren
suffix:semicolon
DECL|variable|parport_unregister_driver
id|EXPORT_SYMBOL
c_func
(paren
id|parport_unregister_driver
)paren
suffix:semicolon
DECL|variable|parport_register_device
id|EXPORT_SYMBOL
c_func
(paren
id|parport_register_device
)paren
suffix:semicolon
DECL|variable|parport_unregister_device
id|EXPORT_SYMBOL
c_func
(paren
id|parport_unregister_device
)paren
suffix:semicolon
DECL|variable|parport_enumerate
id|EXPORT_SYMBOL
c_func
(paren
id|parport_enumerate
)paren
suffix:semicolon
DECL|variable|parport_negotiate
id|EXPORT_SYMBOL
c_func
(paren
id|parport_negotiate
)paren
suffix:semicolon
DECL|variable|parport_write
id|EXPORT_SYMBOL
c_func
(paren
id|parport_write
)paren
suffix:semicolon
DECL|variable|parport_read
id|EXPORT_SYMBOL
c_func
(paren
id|parport_read
)paren
suffix:semicolon
DECL|variable|parport_ieee1284_wakeup
id|EXPORT_SYMBOL
c_func
(paren
id|parport_ieee1284_wakeup
)paren
suffix:semicolon
DECL|variable|parport_wait_peripheral
id|EXPORT_SYMBOL
c_func
(paren
id|parport_wait_peripheral
)paren
suffix:semicolon
DECL|variable|parport_poll_peripheral
id|EXPORT_SYMBOL
c_func
(paren
id|parport_poll_peripheral
)paren
suffix:semicolon
DECL|variable|parport_wait_event
id|EXPORT_SYMBOL
c_func
(paren
id|parport_wait_event
)paren
suffix:semicolon
DECL|variable|parport_set_timeout
id|EXPORT_SYMBOL
c_func
(paren
id|parport_set_timeout
)paren
suffix:semicolon
DECL|variable|parport_ieee1284_interrupt
id|EXPORT_SYMBOL
c_func
(paren
id|parport_ieee1284_interrupt
)paren
suffix:semicolon
DECL|variable|parport_ieee1284_ecp_write_data
id|EXPORT_SYMBOL
c_func
(paren
id|parport_ieee1284_ecp_write_data
)paren
suffix:semicolon
DECL|variable|parport_ieee1284_ecp_read_data
id|EXPORT_SYMBOL
c_func
(paren
id|parport_ieee1284_ecp_read_data
)paren
suffix:semicolon
DECL|variable|parport_ieee1284_ecp_write_addr
id|EXPORT_SYMBOL
c_func
(paren
id|parport_ieee1284_ecp_write_addr
)paren
suffix:semicolon
DECL|variable|parport_ieee1284_write_compat
id|EXPORT_SYMBOL
c_func
(paren
id|parport_ieee1284_write_compat
)paren
suffix:semicolon
DECL|variable|parport_ieee1284_read_nibble
id|EXPORT_SYMBOL
c_func
(paren
id|parport_ieee1284_read_nibble
)paren
suffix:semicolon
DECL|variable|parport_ieee1284_read_byte
id|EXPORT_SYMBOL
c_func
(paren
id|parport_ieee1284_read_byte
)paren
suffix:semicolon
DECL|variable|parport_ieee1284_epp_write_data
id|EXPORT_SYMBOL
c_func
(paren
id|parport_ieee1284_epp_write_data
)paren
suffix:semicolon
DECL|variable|parport_ieee1284_epp_read_data
id|EXPORT_SYMBOL
c_func
(paren
id|parport_ieee1284_epp_read_data
)paren
suffix:semicolon
DECL|variable|parport_ieee1284_epp_write_addr
id|EXPORT_SYMBOL
c_func
(paren
id|parport_ieee1284_epp_write_addr
)paren
suffix:semicolon
DECL|variable|parport_ieee1284_epp_read_addr
id|EXPORT_SYMBOL
c_func
(paren
id|parport_ieee1284_epp_read_addr
)paren
suffix:semicolon
DECL|variable|parport_proc_register
id|EXPORT_SYMBOL
c_func
(paren
id|parport_proc_register
)paren
suffix:semicolon
DECL|variable|parport_proc_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|parport_proc_unregister
)paren
suffix:semicolon
DECL|variable|parport_device_proc_register
id|EXPORT_SYMBOL
c_func
(paren
id|parport_device_proc_register
)paren
suffix:semicolon
DECL|variable|parport_device_proc_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|parport_device_proc_unregister
)paren
suffix:semicolon
DECL|variable|parport_default_proc_register
id|EXPORT_SYMBOL
c_func
(paren
id|parport_default_proc_register
)paren
suffix:semicolon
DECL|variable|parport_default_proc_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|parport_default_proc_unregister
)paren
suffix:semicolon
DECL|variable|parport_parse_irqs
id|EXPORT_SYMBOL
c_func
(paren
id|parport_parse_irqs
)paren
suffix:semicolon
DECL|variable|parport_parse_dmas
id|EXPORT_SYMBOL
c_func
(paren
id|parport_parse_dmas
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PARPORT_1284
DECL|variable|parport_open
id|EXPORT_SYMBOL
c_func
(paren
id|parport_open
)paren
suffix:semicolon
DECL|variable|parport_close
id|EXPORT_SYMBOL
c_func
(paren
id|parport_close
)paren
suffix:semicolon
DECL|variable|parport_device_id
id|EXPORT_SYMBOL
c_func
(paren
id|parport_device_id
)paren
suffix:semicolon
DECL|variable|parport_device_num
id|EXPORT_SYMBOL
c_func
(paren
id|parport_device_num
)paren
suffix:semicolon
DECL|variable|parport_device_coords
id|EXPORT_SYMBOL
c_func
(paren
id|parport_device_coords
)paren
suffix:semicolon
DECL|variable|parport_daisy_deselect_all
id|EXPORT_SYMBOL
c_func
(paren
id|parport_daisy_deselect_all
)paren
suffix:semicolon
DECL|variable|parport_daisy_select
id|EXPORT_SYMBOL
c_func
(paren
id|parport_daisy_select
)paren
suffix:semicolon
DECL|variable|parport_daisy_init
id|EXPORT_SYMBOL
c_func
(paren
id|parport_daisy_init
)paren
suffix:semicolon
DECL|variable|parport_find_device
id|EXPORT_SYMBOL
c_func
(paren
id|parport_find_device
)paren
suffix:semicolon
DECL|variable|parport_find_class
id|EXPORT_SYMBOL
c_func
(paren
id|parport_find_class
)paren
suffix:semicolon
macro_line|#endif
DECL|function|inc_parport_count
r_void
id|inc_parport_count
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef MODULE
id|MOD_INC_USE_COUNT
suffix:semicolon
macro_line|#endif
)brace
DECL|function|dec_parport_count
r_void
id|dec_parport_count
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef MODULE
id|MOD_DEC_USE_COUNT
suffix:semicolon
macro_line|#endif
)brace
eof
