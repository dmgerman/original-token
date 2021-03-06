multiline_comment|/*&n;&n;drivers.c&n;&n;Copyright (c) 1999 The Puffin Group &n;&n;This is a collection of routines intended to register all the devices&n;in a system, and register device drivers.&n;&n;*/
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pdc.h&gt;
r_extern
r_struct
id|hp_hardware
op_star
id|parisc_get_reference
c_func
(paren
r_int
r_int
id|hw_type
comma
r_int
r_int
id|hversion
comma
r_int
r_int
id|sversion
)paren
suffix:semicolon
multiline_comment|/* I&squot;m assuming there&squot;ll never be 64 devices.  We should probably make &n;   this more flexible.  */
DECL|macro|MAX_DEVICES
mdefine_line|#define MAX_DEVICES 64
DECL|variable|num_devices
r_int
r_int
id|num_devices
op_assign
l_int|0
suffix:semicolon
DECL|variable|devices
r_struct
id|hp_device
id|devices
(braket
id|MAX_DEVICES
)braket
suffix:semicolon
DECL|variable|pdc_result
r_static
r_int
r_int
id|pdc_result
(braket
l_int|32
)braket
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|16
)paren
)paren
)paren
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|iodc_data
r_static
id|u8
id|iodc_data
(braket
l_int|32
)braket
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|64
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;XXX should we be using a locked array ?&n; */
DECL|function|register_driver
r_int
id|register_driver
c_func
(paren
r_struct
id|pa_iodc_driver
op_star
id|driver
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_struct
id|hp_device
op_star
id|device
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|driver-&gt;check
suffix:semicolon
id|driver
op_increment
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num_devices
suffix:semicolon
id|i
op_increment
)paren
(brace
id|device
op_assign
op_amp
id|devices
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|device-&gt;managed
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|driver-&gt;check
op_amp
id|DRIVER_CHECK_HWTYPE
)paren
op_logical_and
(paren
id|driver-&gt;hw_type
op_ne
id|device-&gt;hw_type
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|driver-&gt;check
op_amp
id|DRIVER_CHECK_HVERSION
)paren
op_logical_and
(paren
id|driver-&gt;hversion
op_ne
id|device-&gt;hversion
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|driver-&gt;check
op_amp
id|DRIVER_CHECK_HVERSION_REV
)paren
op_logical_and
(paren
id|driver-&gt;hversion_rev
op_ne
id|device-&gt;hversion_rev
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|driver-&gt;check
op_amp
id|DRIVER_CHECK_SVERSION
)paren
op_logical_and
(paren
id|driver-&gt;sversion
op_ne
id|device-&gt;sversion
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|driver-&gt;check
op_amp
id|DRIVER_CHECK_SVERSION_REV
)paren
op_logical_and
(paren
id|driver-&gt;sversion_rev
op_ne
id|device-&gt;sversion_rev
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|driver-&gt;check
op_amp
id|DRIVER_CHECK_OPT
)paren
op_logical_and
(paren
id|driver-&gt;opt
op_ne
id|device-&gt;opt
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|driver-&gt;callback
)paren
(paren
id|device
comma
id|driver
)paren
op_eq
l_int|0
)paren
(brace
id|device-&gt;managed
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;Warning : device (%d, 0x%x, 0x%x, 0x%x, 0x%x) NOT claimed by %s %s&bslash;n&quot;
comma
id|device-&gt;hw_type
comma
id|device-&gt;hversion
comma
id|device-&gt;hversion_rev
comma
id|device-&gt;sversion
comma
id|device-&gt;sversion_rev
comma
id|driver-&gt;name
comma
id|driver-&gt;version
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|register_module
r_struct
id|hp_device
op_star
id|register_module
c_func
(paren
r_void
op_star
id|hpa
)paren
(brace
r_struct
id|hp_device
op_star
id|d
suffix:semicolon
r_int
id|status
suffix:semicolon
id|d
op_assign
op_amp
id|devices
(braket
id|num_devices
)braket
suffix:semicolon
id|status
op_assign
id|pdc_iodc_read
c_func
(paren
op_amp
id|pdc_result
comma
id|hpa
comma
l_int|0
comma
op_amp
id|iodc_data
comma
l_int|32
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|PDC_RET_OK
)paren
(brace
multiline_comment|/* There is no device here, so we&squot;ll skip it */
r_return
l_int|0
suffix:semicolon
)brace
id|d-&gt;hw_type
op_assign
id|iodc_data
(braket
l_int|3
)braket
op_amp
l_int|0x1f
suffix:semicolon
id|d-&gt;hversion
op_assign
(paren
id|iodc_data
(braket
l_int|0
)braket
op_lshift
l_int|4
)paren
op_or
(paren
(paren
id|iodc_data
(braket
l_int|1
)braket
op_amp
l_int|0xf0
)paren
op_rshift
l_int|4
)paren
suffix:semicolon
id|d-&gt;sversion
op_assign
(paren
(paren
id|iodc_data
(braket
l_int|4
)braket
op_amp
l_int|0x0f
)paren
op_lshift
l_int|16
)paren
op_or
(paren
id|iodc_data
(braket
l_int|5
)braket
op_lshift
l_int|8
)paren
op_or
(paren
id|iodc_data
(braket
l_int|6
)braket
)paren
suffix:semicolon
id|d-&gt;hversion_rev
op_assign
id|iodc_data
(braket
l_int|1
)braket
op_amp
l_int|0x0f
suffix:semicolon
id|d-&gt;sversion_rev
op_assign
id|iodc_data
(braket
l_int|4
)braket
op_rshift
l_int|4
suffix:semicolon
id|d-&gt;opt
op_assign
id|iodc_data
(braket
l_int|7
)braket
suffix:semicolon
id|d-&gt;hpa
op_assign
id|hpa
suffix:semicolon
id|d-&gt;managed
op_assign
l_int|0
suffix:semicolon
id|d-&gt;reference
op_assign
id|parisc_get_reference
c_func
(paren
id|d-&gt;hw_type
comma
id|d-&gt;hversion
comma
id|d-&gt;sversion
)paren
suffix:semicolon
id|num_devices
op_increment
suffix:semicolon
r_return
id|d
suffix:semicolon
)brace
DECL|function|print_devices
r_void
id|print_devices
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|hp_device
op_star
id|d
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Found devices:&bslash;n&quot;
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
id|num_devices
suffix:semicolon
id|i
op_increment
)paren
(brace
id|d
op_assign
op_amp
id|devices
(braket
id|i
)braket
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%d. %s (%d) at 0x%p, versions 0x%x, 0x%x, 0x%x, 0x%x, 0x%x&bslash;n&quot;
comma
id|i
op_plus
l_int|1
comma
(paren
id|d-&gt;reference
)paren
ques
c_cond
id|d-&gt;reference-&gt;name
suffix:colon
l_string|&quot;Unknown device&quot;
comma
id|d-&gt;hw_type
comma
id|d-&gt;hpa
comma
id|d-&gt;hversion
comma
id|d-&gt;hversion_rev
comma
id|d-&gt;sversion
comma
id|d-&gt;sversion_rev
comma
id|d-&gt;opt
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;That&squot;s a total of %d devices.&bslash;n&quot;
comma
id|num_devices
)paren
suffix:semicolon
)brace
eof
