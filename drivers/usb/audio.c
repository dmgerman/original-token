macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;usb.h&quot;
r_static
r_int
id|usb_audio_probe
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|usb_audio_disconnect
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|usb_audio_list
)paren
suffix:semicolon
DECL|struct|usb_audio
r_struct
id|usb_audio
(brace
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|usb_audio_driver
r_static
r_struct
id|usb_driver
id|usb_audio_driver
op_assign
(brace
l_string|&quot;audio&quot;
comma
id|usb_audio_probe
comma
id|usb_audio_disconnect
comma
(brace
l_int|NULL
comma
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|function|usb_audio_irq
r_static
r_int
id|usb_audio_irq
c_func
(paren
r_int
id|state
comma
r_void
op_star
id|buffer
comma
r_int
id|len
comma
r_void
op_star
id|dev_id
)paren
(brace
r_struct
id|usb_audio
op_star
id|aud
op_assign
(paren
r_struct
id|usb_audio
op_star
)paren
id|dev_id
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;irq on %p&bslash;n&quot;
comma
id|aud
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|usb_audio_probe
r_static
r_int
id|usb_audio_probe
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
(brace
r_struct
id|usb_interface_descriptor
op_star
id|interface
suffix:semicolon
r_struct
id|usb_endpoint_descriptor
op_star
id|endpoint
suffix:semicolon
r_struct
id|usb_audio
op_star
id|aud
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|na
op_assign
l_int|0
suffix:semicolon
id|interface
op_assign
op_amp
id|dev-&gt;config
(braket
l_int|0
)braket
dot
id|altsetting
(braket
l_int|0
)braket
dot
id|interface
(braket
l_int|0
)braket
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
id|dev-&gt;config
(braket
l_int|0
)braket
dot
id|bNumInterfaces
suffix:semicolon
id|i
op_increment
)paren
(brace
id|endpoint
op_assign
op_amp
id|interface-&gt;endpoint
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|interface-&gt;bInterfaceClass
op_ne
l_int|1
)paren
(brace
r_continue
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;USB audio device detected.&bslash;n&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|interface-&gt;bInterfaceSubClass
)paren
(brace
r_case
l_int|0x01
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;audio: Control device.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x02
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;audio: streaming.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x03
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;audio: nonstreaming.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|na
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|na
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|aud
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|usb_audio
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aud
)paren
(brace
id|memset
c_func
(paren
id|aud
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|aud
)paren
)paren
suffix:semicolon
id|aud-&gt;dev
op_assign
id|dev
suffix:semicolon
id|dev
op_member_access_from_pointer
r_private
op_assign
id|aud
suffix:semicolon
id|endpoint
op_assign
op_amp
id|interface-&gt;endpoint
(braket
l_int|0
)braket
suffix:semicolon
singleline_comment|//        &t;if (usb_set_configuration(dev, dev-&gt;config[0].bConfigurationValue)) {
singleline_comment|//&t;&t;&t;printk (KERN_INFO &quot; Failed usb_set_configuration: Audio&bslash;n&quot;);
singleline_comment|//&t;&t;&t;break;
singleline_comment|//&t;&t;}
singleline_comment|//        &t;usb_set_protocol(dev, 0);
singleline_comment|//        &t;usb_set_idle(dev, 0, 0);
id|usb_request_irq
c_func
(paren
id|dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|dev
comma
id|endpoint-&gt;bEndpointAddress
)paren
comma
id|usb_audio_irq
comma
id|endpoint-&gt;bInterval
comma
id|aud
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|aud-&gt;list
comma
op_amp
id|usb_audio_list
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|aud
)paren
id|kfree
(paren
id|aud
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|usb_audio_disconnect
r_static
r_void
id|usb_audio_disconnect
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
)paren
(brace
r_struct
id|usb_audio
op_star
id|aud
op_assign
(paren
r_struct
id|usb_audio
op_star
)paren
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|aud
)paren
(brace
id|dev
op_member_access_from_pointer
r_private
op_assign
l_int|NULL
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|aud-&gt;list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|aud
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;USB audio driver removed.&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|usb_audio_init
r_int
id|usb_audio_init
c_func
(paren
r_void
)paren
(brace
id|usb_register
c_func
(paren
op_amp
id|usb_audio_driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Support functions for parsing&n; */
DECL|function|usb_audio_interface
r_void
id|usb_audio_interface
c_func
(paren
r_struct
id|usb_interface_descriptor
op_star
id|interface
comma
id|u8
op_star
id|data
)paren
(brace
)brace
DECL|function|usb_audio_endpoint
r_void
id|usb_audio_endpoint
c_func
(paren
r_struct
id|usb_endpoint_descriptor
op_star
id|interface
comma
id|u8
op_star
id|data
)paren
(brace
)brace
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|usb_audio_init
c_func
(paren
)paren
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
id|usb_deregister
c_func
(paren
op_amp
id|usb_audio_driver
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
