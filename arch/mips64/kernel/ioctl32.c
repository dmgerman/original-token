multiline_comment|/*&n; * ioctl32.c: Conversion between 32bit and 64bit native ioctls.&n; *&n; * Copyright (C) 2000 Silicon Graphics, Inc.&n; * Written by Ulf Carlsson (ulfc@engr.sgi.com)&n; *&n; * Mostly from the sparc64 ioctl32 implementation.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/vt.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/route.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|A
mdefine_line|#define A(__x) ((unsigned long)(__x))
r_int
id|sys_ioctl
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
DECL|struct|timeval32
r_struct
id|timeval32
(brace
DECL|member|tv_sec
r_int
id|tv_sec
suffix:semicolon
DECL|member|tv_usec
r_int
id|tv_usec
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|EXT2_IOC32_GETFLAGS
mdefine_line|#define EXT2_IOC32_GETFLAGS               _IOR(&squot;f&squot;, 1, int)
DECL|macro|EXT2_IOC32_SETFLAGS
mdefine_line|#define EXT2_IOC32_SETFLAGS               _IOW(&squot;f&squot;, 2, int)
DECL|macro|EXT2_IOC32_GETVERSION
mdefine_line|#define EXT2_IOC32_GETVERSION             _IOR(&squot;v&squot;, 1, int)
DECL|macro|EXT2_IOC32_SETVERSION
mdefine_line|#define EXT2_IOC32_SETVERSION             _IOW(&squot;v&squot;, 2, int)
DECL|struct|ifmap32
r_struct
id|ifmap32
(brace
DECL|member|mem_start
r_int
r_int
id|mem_start
suffix:semicolon
DECL|member|mem_end
r_int
r_int
id|mem_end
suffix:semicolon
DECL|member|base_addr
r_int
r_int
id|base_addr
suffix:semicolon
DECL|member|irq
r_int
r_char
id|irq
suffix:semicolon
DECL|member|dma
r_int
r_char
id|dma
suffix:semicolon
DECL|member|port
r_int
r_char
id|port
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ifreq32
r_struct
id|ifreq32
(brace
DECL|macro|IFHWADDRLEN
mdefine_line|#define IFHWADDRLEN     6
DECL|macro|IFNAMSIZ
mdefine_line|#define IFNAMSIZ        16
r_union
(brace
DECL|member|ifrn_name
r_char
id|ifrn_name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* if name, e.g. &quot;en0&quot; */
DECL|member|ifr_ifrn
)brace
id|ifr_ifrn
suffix:semicolon
r_union
(brace
DECL|member|ifru_addr
r_struct
id|sockaddr
id|ifru_addr
suffix:semicolon
DECL|member|ifru_dstaddr
r_struct
id|sockaddr
id|ifru_dstaddr
suffix:semicolon
DECL|member|ifru_broadaddr
r_struct
id|sockaddr
id|ifru_broadaddr
suffix:semicolon
DECL|member|ifru_netmask
r_struct
id|sockaddr
id|ifru_netmask
suffix:semicolon
DECL|member|ifru_hwaddr
r_struct
id|sockaddr
id|ifru_hwaddr
suffix:semicolon
DECL|member|ifru_flags
r_int
id|ifru_flags
suffix:semicolon
DECL|member|ifru_ivalue
r_int
id|ifru_ivalue
suffix:semicolon
DECL|member|ifru_mtu
r_int
id|ifru_mtu
suffix:semicolon
DECL|member|ifru_map
r_struct
id|ifmap32
id|ifru_map
suffix:semicolon
DECL|member|ifru_slave
r_char
id|ifru_slave
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* Just fits the size */
DECL|member|ifru_newname
r_char
id|ifru_newname
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|ifru_data
id|__kernel_caddr_t32
id|ifru_data
suffix:semicolon
DECL|member|ifr_ifru
)brace
id|ifr_ifru
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ifconf32
r_struct
id|ifconf32
(brace
DECL|member|ifc_len
r_int
id|ifc_len
suffix:semicolon
multiline_comment|/* size of buffer       */
DECL|member|ifcbuf
id|__kernel_caddr_t32
id|ifcbuf
suffix:semicolon
)brace
suffix:semicolon
DECL|function|dev_ifname32
r_static
r_int
id|dev_ifname32
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|ireq32
op_star
id|uir32
op_assign
(paren
r_struct
id|ireq32
op_star
)paren
id|arg
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_struct
id|ifreq32
id|ifr32
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ifr32
comma
id|uir32
comma
r_sizeof
(paren
r_struct
id|ifreq32
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
id|dev
op_assign
id|__dev_get_by_index
c_func
(paren
id|ifr32.ifr_ifindex
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|read_unlock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|ifr32.ifr_name
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|dev_base_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|uir32
comma
op_amp
id|ifr32
comma
r_sizeof
(paren
r_struct
id|ifreq32
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dev_ifconf
r_static
r_inline
r_int
id|dev_ifconf
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|ioconf32
op_star
id|uifc32
op_assign
(paren
r_struct
id|ioconf32
op_star
)paren
id|arg
suffix:semicolon
r_struct
id|ifconf32
id|ifc32
suffix:semicolon
r_struct
id|ifconf
id|ifc
suffix:semicolon
r_struct
id|ifreq32
op_star
id|ifr32
suffix:semicolon
r_struct
id|ifreq
op_star
id|ifr
suffix:semicolon
id|mm_segment_t
id|old_fs
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ifc32
comma
id|uifc32
comma
r_sizeof
(paren
r_struct
id|ifconf32
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|ifc32.ifcbuf
op_eq
l_int|0
)paren
(brace
id|ifc32.ifc_len
op_assign
l_int|0
suffix:semicolon
id|ifc.ifc_len
op_assign
l_int|0
suffix:semicolon
id|ifc.ifc_buf
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|ifc.ifc_len
op_assign
(paren
(paren
id|ifc32.ifc_len
op_div
r_sizeof
(paren
r_struct
id|ifreq32
)paren
)paren
)paren
op_star
r_sizeof
(paren
r_struct
id|ifreq
)paren
suffix:semicolon
id|ifc.ifc_buf
op_assign
id|kmalloc
(paren
id|ifc.ifc_len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ifc.ifc_buf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|ifr
op_assign
id|ifc.ifc_req
suffix:semicolon
id|ifr32
op_assign
(paren
r_struct
id|ifreq32
op_star
)paren
id|A
c_func
(paren
id|ifc32.ifcbuf
)paren
suffix:semicolon
id|len
op_assign
id|ifc32.ifc_len
op_div
r_sizeof
(paren
r_struct
id|ifreq32
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|ifr
op_increment
comma
id|ifr32
op_increment
comma
r_sizeof
(paren
r_struct
id|ifreq32
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|err
op_assign
id|sys_ioctl
(paren
id|fd
comma
id|SIOCGIFCONF
comma
(paren
r_int
r_int
)paren
op_amp
id|ifc
)paren
suffix:semicolon
id|set_fs
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|ifr
op_assign
id|ifc.ifc_req
suffix:semicolon
id|ifr32
op_assign
(paren
r_struct
id|ifreq32
op_star
)paren
id|A
c_func
(paren
id|ifc32.ifcbuf
)paren
suffix:semicolon
id|len
op_assign
id|ifc.ifc_len
op_div
r_sizeof
(paren
r_struct
id|ifreq
)paren
suffix:semicolon
id|ifc32.ifc_len
op_assign
id|len
op_star
r_sizeof
(paren
r_struct
id|ifreq32
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|ifr32
op_increment
comma
id|ifr
op_increment
comma
r_sizeof
(paren
r_struct
id|ifreq32
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|uifc32
comma
op_amp
id|ifc32
comma
r_sizeof
(paren
r_struct
id|ifconf32
)paren
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|ifc.ifc_buf
op_ne
l_int|NULL
)paren
(brace
id|kfree
(paren
id|ifc.ifc_buf
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|dev_ifsioc
r_static
r_inline
r_int
id|dev_ifsioc
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|ifreq32
op_star
id|uifr
op_assign
(paren
r_struct
id|ifreq32
op_star
)paren
id|arg
suffix:semicolon
r_struct
id|ifreq
id|ifr
suffix:semicolon
id|mm_segment_t
id|old_fs
suffix:semicolon
r_int
id|err
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SIOCSIFMAP
suffix:colon
id|err
op_assign
id|copy_from_user
c_func
(paren
op_amp
id|ifr
comma
id|uifr
comma
r_sizeof
(paren
id|ifr.ifr_name
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|ifr.ifr_map.mem_start
comma
op_amp
(paren
id|uifr-&gt;ifr_ifru.ifru_map.mem_start
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|ifr.ifr_map.mem_end
comma
op_amp
(paren
id|uifr-&gt;ifr_ifru.ifru_map.mem_end
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|ifr.ifr_map.base_addr
comma
op_amp
(paren
id|uifr-&gt;ifr_ifru.ifru_map.base_addr
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|ifr.ifr_map.irq
comma
op_amp
(paren
id|uifr-&gt;ifr_ifru.ifru_map.irq
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|ifr.ifr_map.dma
comma
op_amp
(paren
id|uifr-&gt;ifr_ifru.ifru_map.dma
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|ifr.ifr_map.port
comma
op_amp
(paren
id|uifr-&gt;ifr_ifru.ifru_map.port
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ifr
comma
id|uifr
comma
r_sizeof
(paren
r_struct
id|ifreq32
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|err
op_assign
id|sys_ioctl
(paren
id|fd
comma
id|cmd
comma
(paren
r_int
r_int
)paren
op_amp
id|ifr
)paren
suffix:semicolon
id|set_fs
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SIOCGIFFLAGS
suffix:colon
r_case
id|SIOCGIFMETRIC
suffix:colon
r_case
id|SIOCGIFMTU
suffix:colon
r_case
id|SIOCGIFMEM
suffix:colon
r_case
id|SIOCGIFHWADDR
suffix:colon
r_case
id|SIOCGIFINDEX
suffix:colon
r_case
id|SIOCGIFADDR
suffix:colon
r_case
id|SIOCGIFBRDADDR
suffix:colon
r_case
id|SIOCGIFDSTADDR
suffix:colon
r_case
id|SIOCGIFNETMASK
suffix:colon
r_case
id|SIOCGIFTXQLEN
suffix:colon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|uifr
comma
op_amp
id|ifr
comma
r_sizeof
(paren
r_struct
id|ifreq32
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
id|SIOCGIFMAP
suffix:colon
id|err
op_assign
id|copy_to_user
c_func
(paren
id|uifr
comma
op_amp
id|ifr
comma
r_sizeof
(paren
id|ifr.ifr_name
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|ifr.ifr_map.mem_start
comma
op_amp
(paren
id|uifr-&gt;ifr_ifru.ifru_map.mem_start
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|ifr.ifr_map.mem_end
comma
op_amp
(paren
id|uifr-&gt;ifr_ifru.ifru_map.mem_end
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|ifr.ifr_map.base_addr
comma
op_amp
(paren
id|uifr-&gt;ifr_ifru.ifru_map.base_addr
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|ifr.ifr_map.irq
comma
op_amp
(paren
id|uifr-&gt;ifr_ifru.ifru_map.irq
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|ifr.ifr_map.dma
comma
op_amp
(paren
id|uifr-&gt;ifr_ifru.ifru_map.dma
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|ifr.ifr_map.port
comma
op_amp
(paren
id|uifr-&gt;ifr_ifru.ifru_map.port
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
id|err
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|struct|rtentry32
r_struct
id|rtentry32
(brace
DECL|member|rt_pad1
r_int
r_int
id|rt_pad1
suffix:semicolon
DECL|member|rt_dst
r_struct
id|sockaddr
id|rt_dst
suffix:semicolon
multiline_comment|/* target address&t;&t;*/
DECL|member|rt_gateway
r_struct
id|sockaddr
id|rt_gateway
suffix:semicolon
multiline_comment|/* gateway addr (RTF_GATEWAY)&t;*/
DECL|member|rt_genmask
r_struct
id|sockaddr
id|rt_genmask
suffix:semicolon
multiline_comment|/* target network mask (IP)&t;*/
DECL|member|rt_flags
r_int
r_int
id|rt_flags
suffix:semicolon
DECL|member|rt_pad2
r_int
id|rt_pad2
suffix:semicolon
DECL|member|rt_pad3
r_int
r_int
id|rt_pad3
suffix:semicolon
DECL|member|rt_pad4
r_int
r_int
id|rt_pad4
suffix:semicolon
DECL|member|rt_metric
r_int
id|rt_metric
suffix:semicolon
multiline_comment|/* +1 for binary compatibility!&t;*/
DECL|member|rt_dev
r_int
r_int
id|rt_dev
suffix:semicolon
multiline_comment|/* forcing the device at add&t;*/
DECL|member|rt_mtu
r_int
r_int
id|rt_mtu
suffix:semicolon
multiline_comment|/* per route MTU/Window &t;*/
macro_line|#ifndef __KERNEL__
DECL|macro|rt_mss
mdefine_line|#define rt_mss&t;rt_mtu&t;&t;&t;/* Compatibility :-(            */
macro_line|#endif
DECL|member|rt_window
r_int
r_int
id|rt_window
suffix:semicolon
multiline_comment|/* Window clamping &t;&t;*/
DECL|member|rt_irtt
r_int
r_int
id|rt_irtt
suffix:semicolon
multiline_comment|/* Initial RTT&t;&t;&t;*/
)brace
suffix:semicolon
DECL|function|routing_ioctl
r_static
r_inline
r_int
id|routing_ioctl
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|rtentry32
op_star
id|ur
op_assign
(paren
r_struct
id|rtentry32
op_star
)paren
id|arg
suffix:semicolon
r_struct
id|rtentry
id|r
suffix:semicolon
r_char
id|devname
(braket
l_int|16
)braket
suffix:semicolon
id|u32
id|rtdev
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|mm_segment_t
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
id|copy_from_user
(paren
op_amp
id|r.rt_dst
comma
op_amp
(paren
id|ur-&gt;rt_dst
)paren
comma
l_int|3
op_star
r_sizeof
(paren
r_struct
id|sockaddr
)paren
)paren
suffix:semicolon
id|ret
op_or_assign
id|__get_user
(paren
id|r.rt_flags
comma
op_amp
(paren
id|ur-&gt;rt_flags
)paren
)paren
suffix:semicolon
id|ret
op_or_assign
id|__get_user
(paren
id|r.rt_metric
comma
op_amp
(paren
id|ur-&gt;rt_metric
)paren
)paren
suffix:semicolon
id|ret
op_or_assign
id|__get_user
(paren
id|r.rt_mtu
comma
op_amp
(paren
id|ur-&gt;rt_mtu
)paren
)paren
suffix:semicolon
id|ret
op_or_assign
id|__get_user
(paren
id|r.rt_window
comma
op_amp
(paren
id|ur-&gt;rt_window
)paren
)paren
suffix:semicolon
id|ret
op_or_assign
id|__get_user
(paren
id|r.rt_irtt
comma
op_amp
(paren
id|ur-&gt;rt_irtt
)paren
)paren
suffix:semicolon
id|ret
op_or_assign
id|__get_user
(paren
id|rtdev
comma
op_amp
(paren
id|ur-&gt;rt_dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtdev
)paren
(brace
id|ret
op_or_assign
id|copy_from_user
(paren
id|devname
comma
(paren
r_char
op_star
)paren
id|A
c_func
(paren
id|rtdev
)paren
comma
l_int|15
)paren
suffix:semicolon
id|r.rt_dev
op_assign
id|devname
suffix:semicolon
id|devname
(braket
l_int|15
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|r.rt_dev
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|set_fs
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|ret
op_assign
id|sys_ioctl
(paren
id|fd
comma
id|cmd
comma
(paren
r_int
)paren
op_amp
id|r
)paren
suffix:semicolon
id|set_fs
(paren
id|old_fs
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|do_ext2_ioctl
r_static
r_int
id|do_ext2_ioctl
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
multiline_comment|/* These are just misnamed, they actually get/put from/to user an int */
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|EXT2_IOC32_GETFLAGS
suffix:colon
id|cmd
op_assign
id|EXT2_IOC_GETFLAGS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EXT2_IOC32_SETFLAGS
suffix:colon
id|cmd
op_assign
id|EXT2_IOC_SETFLAGS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EXT2_IOC32_GETVERSION
suffix:colon
id|cmd
op_assign
id|EXT2_IOC_GETVERSION
suffix:semicolon
r_break
suffix:semicolon
r_case
id|EXT2_IOC32_SETVERSION
suffix:colon
id|cmd
op_assign
id|EXT2_IOC_SETVERSION
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|sys_ioctl
c_func
(paren
id|fd
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
)brace
DECL|function|w_long
r_static
r_int
id|w_long
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
id|mm_segment_t
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
id|set_fs
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|err
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|cmd
comma
(paren
r_int
r_int
)paren
op_amp
id|val
)paren
suffix:semicolon
id|set_fs
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
op_logical_and
id|put_user
c_func
(paren
(paren
r_int
r_int
)paren
id|val
comma
(paren
id|u32
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|struct|ioctl32_handler
r_struct
id|ioctl32_handler
(brace
DECL|member|cmd
r_int
r_int
id|cmd
suffix:semicolon
DECL|member|function
r_int
(paren
op_star
id|function
)paren
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ioctl32_list
r_struct
id|ioctl32_list
(brace
DECL|member|handler
r_struct
id|ioctl32_handler
id|handler
suffix:semicolon
DECL|member|next
r_struct
id|ioctl32_list
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IOCTL32_DEFAULT
mdefine_line|#define IOCTL32_DEFAULT(cmd)&t;&t;{ { cmd, (void *) sys_ioctl }, 0 }
DECL|macro|IOCTL32_HANDLER
mdefine_line|#define IOCTL32_HANDLER(cmd, handler)&t;{ { cmd, (void *) handler }, 0 }
DECL|variable|ioctl32_handler_table
r_static
r_struct
id|ioctl32_list
id|ioctl32_handler_table
(braket
)braket
op_assign
(brace
id|IOCTL32_DEFAULT
c_func
(paren
id|TCGETA
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TCSETA
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TCSETAW
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TCSETAF
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TCSBRK
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TCXONC
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TCFLSH
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TCGETS
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TCSETS
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TCSETSW
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TCSETSF
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCLINUX
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCGETD
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCSETD
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCEXCL
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCNXCL
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCCONS
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCGSOFTCAR
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCSSOFTCAR
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCSWINSZ
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCGWINSZ
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCMGET
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCMBIC
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCMBIS
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCMSET
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCPKT
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCNOTTY
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCSTI
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCOUTQ
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCSPGRP
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCGPGRP
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCSCTTY
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCGPTN
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCSPTLCK
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCGSERIAL
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCSSERIAL
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|TIOCSERGETLSR
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|FIOCLEX
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|FIONCLEX
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|FIOASYNC
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|FIONBIO
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|FIONREAD
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|PIO_FONT
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|GIO_FONT
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDSIGACCEPT
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDGETKEYCODE
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDSETKEYCODE
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KIOCSOUND
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDMKTONE
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDGKBTYPE
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDSETMODE
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDGETMODE
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDSKBMODE
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDGKBMODE
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDSKBMETA
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDGKBMETA
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDGKBENT
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDSKBENT
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDGKBSENT
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDSKBSENT
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDGKBDIACR
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDSKBDIACR
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDGKBLED
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDSKBLED
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDGETLED
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|KDSETLED
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|GIO_SCRNMAP
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|PIO_SCRNMAP
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|GIO_UNISCRNMAP
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|PIO_UNISCRNMAP
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|PIO_FONTRESET
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|PIO_UNIMAPCLR
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|VT_SETMODE
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|VT_GETMODE
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|VT_GETSTATE
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|VT_OPENQRY
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|VT_ACTIVATE
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|VT_WAITACTIVE
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|VT_RELDISP
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|VT_DISALLOCATE
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|VT_RESIZE
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|VT_RESIZEX
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|VT_LOCKSWITCH
)paren
comma
id|IOCTL32_DEFAULT
c_func
(paren
id|VT_UNLOCKSWITCH
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCGIFNAME
comma
id|dev_ifname32
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCGIFCONF
comma
id|dev_ifconf
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCGIFFLAGS
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCSIFFLAGS
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCGIFMETRIC
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCSIFMETRIC
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCGIFMTU
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCSIFMTU
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCGIFMEM
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCSIFMEM
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCGIFHWADDR
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCSIFHWADDR
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCADDMULTI
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCDELMULTI
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCGIFINDEX
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCGIFMAP
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCSIFMAP
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCGIFADDR
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCSIFADDR
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCGIFBRDADDR
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCSIFBRDADDR
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCGIFDSTADDR
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCSIFDSTADDR
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCGIFNETMASK
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCSIFNETMASK
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCSIFPFLAGS
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCGIFPFLAGS
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCGIFTXQLEN
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCSIFTXQLEN
comma
id|dev_ifsioc
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCADDRT
comma
id|routing_ioctl
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|SIOCDELRT
comma
id|routing_ioctl
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|EXT2_IOC32_GETFLAGS
comma
id|do_ext2_ioctl
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|EXT2_IOC32_SETFLAGS
comma
id|do_ext2_ioctl
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|EXT2_IOC32_GETVERSION
comma
id|do_ext2_ioctl
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|EXT2_IOC32_SETVERSION
comma
id|do_ext2_ioctl
)paren
comma
id|IOCTL32_HANDLER
c_func
(paren
id|BLKGETSIZE
comma
id|w_long
)paren
)brace
suffix:semicolon
DECL|macro|NR_IOCTL32_HANDLERS
mdefine_line|#define NR_IOCTL32_HANDLERS&t;(sizeof(ioctl32_handler_table) /&t;&bslash;&n;&t;&t;&t;&t; sizeof(ioctl32_handler_table[0]))
DECL|variable|ioctl32_hash_table
r_static
r_struct
id|ioctl32_list
op_star
id|ioctl32_hash_table
(braket
l_int|1024
)braket
suffix:semicolon
DECL|function|ioctl32_hash
r_static
r_inline
r_int
id|ioctl32_hash
c_func
(paren
r_int
r_int
id|cmd
)paren
(brace
r_return
(paren
(paren
id|cmd
op_rshift
l_int|6
)paren
op_xor
(paren
id|cmd
op_rshift
l_int|4
)paren
op_xor
id|cmd
)paren
op_amp
l_int|0x3ff
suffix:semicolon
)brace
DECL|function|sys32_ioctl
r_int
id|sys32_ioctl
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
(paren
op_star
id|handler
)paren
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_struct
id|file
op_star
id|filp
suffix:semicolon
r_struct
id|ioctl32_list
op_star
id|l
suffix:semicolon
r_int
id|error
suffix:semicolon
id|l
op_assign
id|ioctl32_hash_table
(braket
id|ioctl32_hash
c_func
(paren
id|cmd
)paren
)braket
suffix:semicolon
id|error
op_assign
op_minus
id|EBADF
suffix:semicolon
id|filp
op_assign
id|fget
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|filp
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|filp-&gt;f_op
op_logical_or
op_logical_neg
id|filp-&gt;f_op-&gt;ioctl
)paren
(brace
id|error
op_assign
id|sys_ioctl
(paren
id|fd
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_while
c_loop
(paren
id|l
op_logical_and
id|l-&gt;handler.cmd
op_ne
id|cmd
)paren
id|l
op_assign
id|l-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|l
)paren
(brace
id|handler
op_assign
(paren
r_void
op_star
)paren
id|l-&gt;handler.function
suffix:semicolon
id|error
op_assign
id|handler
c_func
(paren
id|fd
comma
id|cmd
comma
id|arg
comma
id|filp
)paren
suffix:semicolon
)brace
r_else
(brace
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;unknown ioctl: %08x&bslash;n&quot;
comma
id|cmd
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|fput
c_func
(paren
id|filp
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|ioctl32_insert
r_static
r_void
id|ioctl32_insert
c_func
(paren
r_struct
id|ioctl32_list
op_star
id|entry
)paren
(brace
r_int
id|hash
op_assign
id|ioctl32_hash
c_func
(paren
id|entry-&gt;handler.cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ioctl32_hash_table
(braket
id|hash
)braket
)paren
id|ioctl32_hash_table
(braket
id|hash
)braket
op_assign
id|entry
suffix:semicolon
r_else
(brace
r_struct
id|ioctl32_list
op_star
id|l
suffix:semicolon
id|l
op_assign
id|ioctl32_hash_table
(braket
id|hash
)braket
suffix:semicolon
r_while
c_loop
(paren
id|l-&gt;next
)paren
id|l
op_assign
id|l-&gt;next
suffix:semicolon
id|l-&gt;next
op_assign
id|entry
suffix:semicolon
id|entry-&gt;next
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|init_ioctl32
r_static
r_int
id|__init
id|init_ioctl32
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
id|NR_IOCTL32_HANDLERS
suffix:semicolon
id|i
op_increment
)paren
id|ioctl32_insert
c_func
(paren
op_amp
id|ioctl32_handler_table
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|init_ioctl32
id|__initcall
c_func
(paren
id|init_ioctl32
)paren
suffix:semicolon
eof
