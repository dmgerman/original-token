multiline_comment|/* Parallel-port initialisation code.&n; * &n; * Authors: David Campbell &lt;campbell@torque.net&gt;&n; *          Tim Waugh &lt;tim@cyberelk.demon.co.uk&gt;&n; *&t;    Jose Renau &lt;renau@acm.org&gt;&n; *&n; * based on work by Grant Guenther &lt;grant@torque.net&gt;&n; *              and Philip Blundell &lt;Philip.Blundell@pobox.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/tasks.h&gt;
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
id|PARPORT_DMA_AUTO
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
id|parport_ax_init
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
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|parport_setup
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
)paren
(brace
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|str
op_logical_and
op_logical_neg
id|strncmp
c_func
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
)brace
r_else
r_if
c_cond
(paren
id|str
)paren
id|printk
(paren
id|KERN_ERR
l_string|&quot;parport: `%s&squot;: huh?&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
r_else
id|printk
(paren
id|KERN_ERR
l_string|&quot;parport: parport=.. what?&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|ints
(braket
l_int|1
)braket
op_eq
l_int|0
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
suffix:semicolon
)brace
r_if
c_cond
(paren
id|parport_setup_ptr
OL
id|PARPORT_MAX
)paren
(brace
r_char
op_star
id|sep
suffix:semicolon
id|io
(braket
id|parport_setup_ptr
)braket
op_assign
id|ints
(braket
l_int|1
)braket
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
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OG
l_int|1
)paren
(brace
id|irq
(braket
id|parport_setup_ptr
)braket
op_assign
id|ints
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OG
l_int|2
)paren
(brace
id|dma
(braket
id|parport_setup_ptr
)braket
op_assign
id|ints
(braket
l_int|3
)braket
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
id|str
op_eq
l_int|NULL
)paren
r_goto
id|done
suffix:semicolon
r_goto
id|dma_from_str
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|str
op_eq
l_int|NULL
)paren
r_goto
id|done
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|str
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
c_func
(paren
id|str
comma
l_string|&quot;none&quot;
comma
l_int|4
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;parport: bad irq `%s&squot;&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|sep
op_assign
id|strchr
c_func
(paren
id|str
comma
l_char|&squot;,&squot;
)paren
)paren
op_eq
l_int|NULL
)paren
r_goto
id|done
suffix:semicolon
id|str
op_assign
id|sep
op_plus
l_int|1
suffix:semicolon
id|dma_from_str
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|str
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
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;none&quot;
comma
l_int|4
)paren
op_ne
l_int|0
)paren
(brace
r_char
op_star
id|ep
suffix:semicolon
id|dma
(braket
id|parport_setup_ptr
)braket
op_assign
id|simple_strtoul
c_func
(paren
id|str
comma
op_amp
id|ep
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ep
op_eq
id|str
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;parport: bad dma `%s&squot;&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|done
suffix:colon
id|parport_setup_ptr
op_increment
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;parport=%s ignored, too many ports&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
)brace
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
(paren
r_void
)paren
id|parport_proc_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* We can go on without it. */
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
id|parport_proc_cleanup
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|parport_init
c_func
(paren
r_void
)paren
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
macro_line|#ifdef CONFIG_PNP_PARPORT
id|parport_probe_hook
op_assign
op_amp
id|parport_probe_one
suffix:semicolon
macro_line|#endif
macro_line|#ifdef&t;CONFIG_PROC_FS
id|parport_proc_init
c_func
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
macro_line|#ifdef CONFIG_PARPORT_AX
id|parport_ax_init
c_func
(paren
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
DECL|variable|parport_quiesce
id|EXPORT_SYMBOL
c_func
(paren
id|parport_quiesce
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
DECL|variable|parport_ieee1284_nibble_mode_ok
id|EXPORT_SYMBOL
c_func
(paren
id|parport_ieee1284_nibble_mode_ok
)paren
suffix:semicolon
DECL|variable|parport_wait_peripheral
id|EXPORT_SYMBOL
c_func
(paren
id|parport_wait_peripheral
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
DECL|variable|parport_probe_hook
id|EXPORT_SYMBOL
c_func
(paren
id|parport_probe_hook
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
