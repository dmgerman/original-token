multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Generic frame diversion&n; *&n; * Version:&t;@(#)eth.c&t;0.41&t;09/09/2000&n; *&n; * Authors:&t;&n; * &t;&t;Benoit LOCHER:&t;initial integration within the kernel with support for ethernet&n; * &t;&t;Dave Miller:&t;improvement on the code (correctness, performance and source files)&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/udp.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;net/dst.h&gt;
macro_line|#include &lt;net/arp.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/ipv6.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;linux/divert.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
DECL|variable|sysctl_divert_version
r_const
r_char
id|sysctl_divert_version
(braket
l_int|32
)braket
op_assign
l_string|&quot;0.46&quot;
suffix:semicolon
multiline_comment|/* Current version */
DECL|function|dv_init
r_int
id|__init
id|dv_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;NET4: Frame Diverter %s&bslash;n&quot;
comma
id|sysctl_divert_version
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Allocate a divert_blk for a device. This must be an ethernet nic.&n; */
DECL|function|alloc_divert_blk
r_int
id|alloc_divert_blk
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|alloc_size
op_assign
(paren
r_sizeof
(paren
r_struct
id|divert_blk
)paren
op_plus
l_int|3
)paren
op_amp
op_complement
l_int|3
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|dev-&gt;name
comma
l_string|&quot;eth&quot;
comma
l_int|3
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;divert: allocating divert_blk for %s&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|dev-&gt;divert
op_assign
(paren
r_struct
id|divert_blk
op_star
)paren
id|kmalloc
c_func
(paren
id|alloc_size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;divert
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;divert: unable to allocate divert_blk for %s&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_else
(brace
id|memset
c_func
(paren
id|dev-&gt;divert
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|divert_blk
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;divert: not allocating divert_blk for non-ethernet device %s&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|dev-&gt;divert
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Free a divert_blk allocated by the above function, if it was &n; * allocated on that device.&n; */
DECL|function|free_divert_blk
r_void
id|free_divert_blk
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;divert
)paren
(brace
id|kfree
c_func
(paren
id|dev-&gt;divert
)paren
suffix:semicolon
id|dev-&gt;divert
op_assign
l_int|NULL
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;divert: freeing divert_blk for %s&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;divert: no divert_blk to free, %s not ethernet&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Adds a tcp/udp (source or dest) port to an array&n; */
DECL|function|add_port
r_int
id|add_port
c_func
(paren
id|u16
id|ports
(braket
)braket
comma
id|u16
id|port
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|port
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Storing directly in network format for performance,&n;&t; * thanks Dave :)&n;&t; */
id|port
op_assign
id|htons
c_func
(paren
id|port
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
id|MAX_DIVERT_PORTS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ports
(braket
id|i
)braket
op_eq
id|port
)paren
r_return
op_minus
id|EALREADY
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_DIVERT_PORTS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ports
(braket
id|i
)braket
op_eq
l_int|0
)paren
(brace
id|ports
(braket
id|i
)braket
op_assign
id|port
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
multiline_comment|/*&n; * Removes a port from an array tcp/udp (source or dest)&n; */
DECL|function|remove_port
r_int
id|remove_port
c_func
(paren
id|u16
id|ports
(braket
)braket
comma
id|u16
id|port
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|port
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Storing directly in network format for performance,&n;&t; * thanks Dave !&n;&t; */
id|port
op_assign
id|htons
c_func
(paren
id|port
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
id|MAX_DIVERT_PORTS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ports
(braket
id|i
)braket
op_eq
id|port
)paren
(brace
id|ports
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Some basic sanity checks on the arguments passed to divert_ioctl() */
DECL|function|check_args
r_int
id|check_args
c_func
(paren
r_struct
id|divert_cf
op_star
id|div_cf
comma
r_struct
id|net_device
op_star
op_star
id|dev
)paren
(brace
r_char
id|devname
(braket
l_int|32
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/* GETVERSION: all other args are unused */
r_if
c_cond
(paren
id|div_cf-&gt;cmd
op_eq
id|DIVCMD_GETVERSION
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Network device index should reasonably be between 0 and 1000 :) */
r_if
c_cond
(paren
id|div_cf-&gt;dev_index
template_param
l_int|1000
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Let&squot;s try to find the ifname */
id|sprintf
c_func
(paren
id|devname
comma
l_string|&quot;eth%d&quot;
comma
id|div_cf-&gt;dev_index
)paren
suffix:semicolon
op_star
id|dev
op_assign
id|dev_get_by_name
c_func
(paren
id|devname
)paren
suffix:semicolon
multiline_comment|/* dev should NOT be null */
r_if
c_cond
(paren
op_star
id|dev
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* user issuing the ioctl must be a super one :) */
r_if
c_cond
(paren
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/* Device must have a divert_blk member NOT null */
r_if
c_cond
(paren
(paren
op_star
id|dev
)paren
op_member_access_from_pointer
id|divert
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * control function of the diverter&n; */
DECL|macro|DVDBG
mdefine_line|#define&t;DVDBG(a)&t;&bslash;&n;&t;printk(KERN_DEBUG &quot;divert_ioctl() line %d %s&bslash;n&quot;, __LINE__, (a))
DECL|function|divert_ioctl
r_int
id|divert_ioctl
c_func
(paren
r_int
r_int
id|cmd
comma
r_struct
id|divert_cf
op_star
id|arg
)paren
(brace
r_struct
id|divert_cf
id|div_cf
suffix:semicolon
r_struct
id|divert_blk
op_star
id|div_blk
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SIOCGIFDIVERT
suffix:colon
id|DVDBG
c_func
(paren
l_string|&quot;SIOCGIFDIVERT, copy_from_user&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|div_cf
comma
id|arg
comma
r_sizeof
(paren
r_struct
id|divert_cf
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|DVDBG
c_func
(paren
l_string|&quot;before check_args&quot;
)paren
suffix:semicolon
id|ret
op_assign
id|check_args
c_func
(paren
op_amp
id|div_cf
comma
op_amp
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|DVDBG
c_func
(paren
l_string|&quot;after checkargs&quot;
)paren
suffix:semicolon
id|div_blk
op_assign
id|dev-&gt;divert
suffix:semicolon
id|DVDBG
c_func
(paren
l_string|&quot;befre switch()&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|div_cf.cmd
)paren
(brace
r_case
id|DIVCMD_GETSTATUS
suffix:colon
multiline_comment|/* Now, just give the user the raw divert block&n;&t;&t;&t; * for him to play with :)&n;&t;&t;&t; */
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|div_cf.arg1.ptr
comma
id|dev-&gt;divert
comma
r_sizeof
(paren
r_struct
id|divert_blk
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVCMD_GETVERSION
suffix:colon
id|DVDBG
c_func
(paren
l_string|&quot;GETVERSION: checking ptr&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|div_cf.arg1.ptr
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|DVDBG
c_func
(paren
l_string|&quot;GETVERSION: copying data to userland&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|div_cf.arg1.ptr
comma
id|sysctl_divert_version
comma
l_int|32
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|DVDBG
c_func
(paren
l_string|&quot;GETVERSION: data copied&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIOCSIFDIVERT
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|div_cf
comma
id|arg
comma
r_sizeof
(paren
r_struct
id|divert_cf
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|ret
op_assign
id|check_args
c_func
(paren
op_amp
id|div_cf
comma
op_amp
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|ret
suffix:semicolon
id|div_blk
op_assign
id|dev-&gt;divert
suffix:semicolon
r_switch
c_cond
(paren
id|div_cf.cmd
)paren
(brace
r_case
id|DIVCMD_RESET
suffix:colon
id|div_blk-&gt;divert
op_assign
l_int|0
suffix:semicolon
id|div_blk-&gt;protos
op_assign
id|DIVERT_PROTO_NONE
suffix:semicolon
id|memset
c_func
(paren
id|div_blk-&gt;tcp_dst
comma
l_int|0
comma
id|MAX_DIVERT_PORTS
op_star
r_sizeof
(paren
id|u16
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|div_blk-&gt;tcp_src
comma
l_int|0
comma
id|MAX_DIVERT_PORTS
op_star
r_sizeof
(paren
id|u16
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|div_blk-&gt;udp_dst
comma
l_int|0
comma
id|MAX_DIVERT_PORTS
op_star
r_sizeof
(paren
id|u16
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|div_blk-&gt;udp_src
comma
l_int|0
comma
id|MAX_DIVERT_PORTS
op_star
r_sizeof
(paren
id|u16
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|DIVCMD_DIVERT
suffix:colon
r_switch
c_cond
(paren
id|div_cf.arg1.int32
)paren
(brace
r_case
id|DIVARG1_ENABLE
suffix:colon
r_if
c_cond
(paren
id|div_blk-&gt;divert
)paren
r_return
op_minus
id|EALREADY
suffix:semicolon
id|div_blk-&gt;divert
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVARG1_DISABLE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|div_blk-&gt;divert
)paren
r_return
op_minus
id|EALREADY
suffix:semicolon
id|div_blk-&gt;divert
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVCMD_IP
suffix:colon
r_switch
c_cond
(paren
id|div_cf.arg1.int32
)paren
(brace
r_case
id|DIVARG1_ENABLE
suffix:colon
r_if
c_cond
(paren
id|div_blk-&gt;protos
op_amp
id|DIVERT_PROTO_IP
)paren
r_return
op_minus
id|EALREADY
suffix:semicolon
id|div_blk-&gt;protos
op_or_assign
id|DIVERT_PROTO_IP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVARG1_DISABLE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|div_blk-&gt;protos
op_amp
id|DIVERT_PROTO_IP
)paren
)paren
r_return
op_minus
id|EALREADY
suffix:semicolon
id|div_blk-&gt;protos
op_and_assign
op_complement
id|DIVERT_PROTO_IP
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVCMD_TCP
suffix:colon
r_switch
c_cond
(paren
id|div_cf.arg1.int32
)paren
(brace
r_case
id|DIVARG1_ENABLE
suffix:colon
r_if
c_cond
(paren
id|div_blk-&gt;protos
op_amp
id|DIVERT_PROTO_TCP
)paren
r_return
op_minus
id|EALREADY
suffix:semicolon
id|div_blk-&gt;protos
op_or_assign
id|DIVERT_PROTO_TCP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVARG1_DISABLE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|div_blk-&gt;protos
op_amp
id|DIVERT_PROTO_TCP
)paren
)paren
r_return
op_minus
id|EALREADY
suffix:semicolon
id|div_blk-&gt;protos
op_and_assign
op_complement
id|DIVERT_PROTO_TCP
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVCMD_TCPDST
suffix:colon
r_switch
c_cond
(paren
id|div_cf.arg1.int32
)paren
(brace
r_case
id|DIVARG1_ADD
suffix:colon
r_return
id|add_port
c_func
(paren
id|div_blk-&gt;tcp_dst
comma
id|div_cf.arg2.uint16
)paren
suffix:semicolon
r_case
id|DIVARG1_REMOVE
suffix:colon
r_return
id|remove_port
c_func
(paren
id|div_blk-&gt;tcp_dst
comma
id|div_cf.arg2.uint16
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVCMD_TCPSRC
suffix:colon
r_switch
c_cond
(paren
id|div_cf.arg1.int32
)paren
(brace
r_case
id|DIVARG1_ADD
suffix:colon
r_return
id|add_port
c_func
(paren
id|div_blk-&gt;tcp_src
comma
id|div_cf.arg2.uint16
)paren
suffix:semicolon
r_case
id|DIVARG1_REMOVE
suffix:colon
r_return
id|remove_port
c_func
(paren
id|div_blk-&gt;tcp_src
comma
id|div_cf.arg2.uint16
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVCMD_UDP
suffix:colon
r_switch
c_cond
(paren
id|div_cf.arg1.int32
)paren
(brace
r_case
id|DIVARG1_ENABLE
suffix:colon
r_if
c_cond
(paren
id|div_blk-&gt;protos
op_amp
id|DIVERT_PROTO_UDP
)paren
r_return
op_minus
id|EALREADY
suffix:semicolon
id|div_blk-&gt;protos
op_or_assign
id|DIVERT_PROTO_UDP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVARG1_DISABLE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|div_blk-&gt;protos
op_amp
id|DIVERT_PROTO_UDP
)paren
)paren
r_return
op_minus
id|EALREADY
suffix:semicolon
id|div_blk-&gt;protos
op_and_assign
op_complement
id|DIVERT_PROTO_UDP
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVCMD_UDPDST
suffix:colon
r_switch
c_cond
(paren
id|div_cf.arg1.int32
)paren
(brace
r_case
id|DIVARG1_ADD
suffix:colon
r_return
id|add_port
c_func
(paren
id|div_blk-&gt;udp_dst
comma
id|div_cf.arg2.uint16
)paren
suffix:semicolon
r_case
id|DIVARG1_REMOVE
suffix:colon
r_return
id|remove_port
c_func
(paren
id|div_blk-&gt;udp_dst
comma
id|div_cf.arg2.uint16
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVCMD_UDPSRC
suffix:colon
r_switch
c_cond
(paren
id|div_cf.arg1.int32
)paren
(brace
r_case
id|DIVARG1_ADD
suffix:colon
r_return
id|add_port
c_func
(paren
id|div_blk-&gt;udp_src
comma
id|div_cf.arg2.uint16
)paren
suffix:semicolon
r_case
id|DIVARG1_REMOVE
suffix:colon
r_return
id|remove_port
c_func
(paren
id|div_blk-&gt;udp_src
comma
id|div_cf.arg2.uint16
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVCMD_ICMP
suffix:colon
r_switch
c_cond
(paren
id|div_cf.arg1.int32
)paren
(brace
r_case
id|DIVARG1_ENABLE
suffix:colon
r_if
c_cond
(paren
id|div_blk-&gt;protos
op_amp
id|DIVERT_PROTO_ICMP
)paren
r_return
op_minus
id|EALREADY
suffix:semicolon
id|div_blk-&gt;protos
op_or_assign
id|DIVERT_PROTO_ICMP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DIVARG1_DISABLE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|div_blk-&gt;protos
op_amp
id|DIVERT_PROTO_ICMP
)paren
)paren
r_return
op_minus
id|EALREADY
suffix:semicolon
id|div_blk-&gt;protos
op_and_assign
op_complement
id|DIVERT_PROTO_ICMP
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Check if packet should have its dest mac address set to the box itself&n; * for diversion&n; */
DECL|macro|ETH_DIVERT_FRAME
mdefine_line|#define&t;ETH_DIVERT_FRAME(skb) &bslash;&n;&t;memcpy(skb-&gt;mac.ethernet, skb-&gt;dev-&gt;dev_addr, ETH_ALEN); &bslash;&n;&t;skb-&gt;pkt_type=PACKET_HOST
DECL|function|divert_frame
r_void
id|divert_frame
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|ethhdr
op_star
id|eth
op_assign
id|skb-&gt;mac.ethernet
suffix:semicolon
r_struct
id|iphdr
op_star
id|iph
suffix:semicolon
r_struct
id|tcphdr
op_star
id|tcph
suffix:semicolon
r_struct
id|udphdr
op_star
id|udph
suffix:semicolon
r_struct
id|divert_blk
op_star
id|divert
op_assign
id|skb-&gt;dev-&gt;divert
suffix:semicolon
r_int
id|i
comma
id|src
comma
id|dst
suffix:semicolon
r_int
r_char
op_star
id|skb_data_end
op_assign
id|skb-&gt;data
op_plus
id|skb-&gt;len
suffix:semicolon
multiline_comment|/* Packet is already aimed at us, return */
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|eth
comma
id|skb-&gt;dev-&gt;dev_addr
comma
id|ETH_ALEN
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* proto is not IP, do nothing */
r_if
c_cond
(paren
id|eth-&gt;h_proto
op_ne
id|htons
c_func
(paren
id|ETH_P_IP
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* Divert all IP frames ? */
r_if
c_cond
(paren
id|divert-&gt;protos
op_amp
id|DIVERT_PROTO_IP
)paren
(brace
id|ETH_DIVERT_FRAME
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Check for possible (maliciously) malformed IP frame (thanks Dave) */
id|iph
op_assign
(paren
r_struct
id|iphdr
op_star
)paren
id|skb-&gt;data
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|iph-&gt;ihl
op_lshift
l_int|2
)paren
op_plus
(paren
r_int
r_char
op_star
)paren
(paren
id|iph
)paren
)paren
op_ge
id|skb_data_end
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;divert: malformed IP packet !&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|iph-&gt;protocol
)paren
(brace
multiline_comment|/* Divert all ICMP frames ? */
r_case
id|IPPROTO_ICMP
suffix:colon
r_if
c_cond
(paren
id|divert-&gt;protos
op_amp
id|DIVERT_PROTO_ICMP
)paren
(brace
id|ETH_DIVERT_FRAME
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_break
suffix:semicolon
multiline_comment|/* Divert all TCP frames ? */
r_case
id|IPPROTO_TCP
suffix:colon
r_if
c_cond
(paren
id|divert-&gt;protos
op_amp
id|DIVERT_PROTO_TCP
)paren
(brace
id|ETH_DIVERT_FRAME
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Check for possible (maliciously) malformed IP&n;&t;&t; * frame (thanx Dave)&n;&t;&t; */
id|tcph
op_assign
(paren
r_struct
id|tcphdr
op_star
)paren
(paren
(paren
(paren
r_int
r_char
op_star
)paren
id|iph
)paren
op_plus
(paren
id|iph-&gt;ihl
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
r_char
op_star
)paren
(paren
id|tcph
op_plus
l_int|1
)paren
)paren
op_ge
id|skb_data_end
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;divert: malformed TCP packet !&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Divert some tcp dst/src ports only ?*/
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_DIVERT_PORTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dst
op_assign
id|divert-&gt;tcp_dst
(braket
id|i
)braket
suffix:semicolon
id|src
op_assign
id|divert-&gt;tcp_src
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dst
op_logical_and
id|dst
op_eq
id|tcph-&gt;dest
)paren
op_logical_or
(paren
id|src
op_logical_and
id|src
op_eq
id|tcph-&gt;source
)paren
)paren
(brace
id|ETH_DIVERT_FRAME
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
multiline_comment|/* Divert all UDP frames ? */
r_case
id|IPPROTO_UDP
suffix:colon
r_if
c_cond
(paren
id|divert-&gt;protos
op_amp
id|DIVERT_PROTO_UDP
)paren
(brace
id|ETH_DIVERT_FRAME
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Check for possible (maliciously) malformed IP&n;&t;&t; * packet (thanks Dave)&n;&t;&t; */
id|udph
op_assign
(paren
r_struct
id|udphdr
op_star
)paren
(paren
(paren
(paren
r_int
r_char
op_star
)paren
id|iph
)paren
op_plus
(paren
id|iph-&gt;ihl
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
r_char
op_star
)paren
(paren
id|udph
op_plus
l_int|1
)paren
)paren
op_ge
id|skb_data_end
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;divert: malformed UDP packet !&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Divert some udp dst/src ports only ? */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_DIVERT_PORTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dst
op_assign
id|divert-&gt;udp_dst
(braket
id|i
)braket
suffix:semicolon
id|src
op_assign
id|divert-&gt;udp_src
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dst
op_logical_and
id|dst
op_eq
id|udph-&gt;dest
)paren
op_logical_or
(paren
id|src
op_logical_and
id|src
op_eq
id|udph-&gt;source
)paren
)paren
(brace
id|ETH_DIVERT_FRAME
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
)brace
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
