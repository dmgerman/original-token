multiline_comment|/*&n; * Procedures for interfacing to the Open Firmware PROM on&n; * Power Macintosh computers.&n; *&n; * In particular, we are interested in the device tree&n; * and in using some of its services (exit, write to stdout).&n; *&n; * Paul Mackerras&t;August 1996.&n; * Copyright (C) 1996 Paul Mackerras.&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/page.h&gt;
DECL|macro|getpromprop
mdefine_line|#define getpromprop(node, name, buf, len)&t;&bslash;&n;&t;((int)call_prom(&quot;getprop&quot;, 4, 1, (node), (name), (buf), (len)))
DECL|variable|prom_stdout
id|ihandle
id|prom_stdout
suffix:semicolon
DECL|variable|prom_chosen
id|ihandle
id|prom_chosen
suffix:semicolon
DECL|variable|command_line
r_char
id|command_line
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|screen_initialized
r_int
id|screen_initialized
op_assign
l_int|0
suffix:semicolon
DECL|variable|prom_display_path
r_char
id|prom_display_path
(braket
l_int|128
)braket
suffix:semicolon
DECL|struct|prom_args
r_struct
id|prom_args
(brace
DECL|member|service
r_const
r_char
op_star
id|service
suffix:semicolon
DECL|member|nargs
r_int
id|nargs
suffix:semicolon
DECL|member|nret
r_int
id|nret
suffix:semicolon
DECL|member|args
r_void
op_star
id|args
(braket
l_int|10
)braket
suffix:semicolon
DECL|variable|prom_args
)brace
id|prom_args
suffix:semicolon
DECL|struct|pci_address
r_struct
id|pci_address
(brace
DECL|member|a_hi
r_int
id|a_hi
suffix:semicolon
DECL|member|a_mid
r_int
id|a_mid
suffix:semicolon
DECL|member|a_lo
r_int
id|a_lo
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pci_reg_property
r_struct
id|pci_reg_property
(brace
DECL|member|addr
r_struct
id|pci_address
id|addr
suffix:semicolon
DECL|member|size_hi
r_int
id|size_hi
suffix:semicolon
DECL|member|size_lo
r_int
id|size_lo
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pci_range
r_struct
id|pci_range
(brace
DECL|member|addr
r_struct
id|pci_address
id|addr
suffix:semicolon
DECL|member|phys
r_int
id|phys
suffix:semicolon
DECL|member|size_hi
r_int
id|size_hi
suffix:semicolon
DECL|member|size_lo
r_int
id|size_lo
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|prom_entry
r_void
(paren
op_star
id|prom_entry
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
r_extern
r_int
id|prom_trashed
suffix:semicolon
r_static
r_int
id|prom_callback
c_func
(paren
r_struct
id|prom_args
op_star
)paren
suffix:semicolon
r_static
r_int
r_int
id|inspect_node
c_func
(paren
id|phandle
comma
r_struct
id|device_node
op_star
comma
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
r_static
r_void
id|check_display
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|prom_next_node
c_func
(paren
id|phandle
op_star
)paren
suffix:semicolon
r_extern
r_int
id|pmac_display_supported
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|enter_prom
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_void
DECL|function|prom_exit
id|prom_exit
c_func
(paren
)paren
(brace
r_struct
id|prom_args
id|args
suffix:semicolon
id|args.service
op_assign
l_string|&quot;exit&quot;
suffix:semicolon
id|args.nargs
op_assign
l_int|0
suffix:semicolon
id|args.nret
op_assign
l_int|0
suffix:semicolon
id|enter_prom
c_func
(paren
op_amp
id|args
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
multiline_comment|/* should never get here */
suffix:semicolon
)brace
r_void
op_star
DECL|function|call_prom
id|call_prom
c_func
(paren
r_const
r_char
op_star
id|service
comma
r_int
id|nargs
comma
r_int
id|nret
comma
dot
dot
dot
)paren
(brace
id|va_list
id|list
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|prom_trashed
)paren
id|panic
c_func
(paren
l_string|&quot;prom called after its memory was reclaimed&quot;
)paren
suffix:semicolon
id|prom_args.service
op_assign
id|service
suffix:semicolon
id|prom_args.nargs
op_assign
id|nargs
suffix:semicolon
id|prom_args.nret
op_assign
id|nret
suffix:semicolon
id|va_start
c_func
(paren
id|list
comma
id|nret
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
id|nargs
suffix:semicolon
op_increment
id|i
)paren
id|prom_args.args
(braket
id|i
)braket
op_assign
id|va_arg
c_func
(paren
id|list
comma
r_void
op_star
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|list
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
id|nret
suffix:semicolon
op_increment
id|i
)paren
id|prom_args.args
(braket
id|i
op_plus
id|nargs
)braket
op_assign
l_int|0
suffix:semicolon
id|enter_prom
c_func
(paren
op_amp
id|prom_args
)paren
suffix:semicolon
r_return
id|prom_args.args
(braket
id|nargs
)braket
suffix:semicolon
)brace
r_void
DECL|function|prom_print
id|prom_print
c_func
(paren
r_const
r_char
op_star
id|msg
)paren
(brace
r_const
r_char
op_star
id|p
comma
op_star
id|q
suffix:semicolon
r_const
r_char
op_star
id|crlf
op_assign
l_string|&quot;&bslash;r&bslash;n&quot;
suffix:semicolon
r_if
c_cond
(paren
id|screen_initialized
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|msg
suffix:semicolon
op_star
id|p
op_ne
l_int|0
suffix:semicolon
id|p
op_assign
id|q
)paren
(brace
r_for
c_loop
(paren
id|q
op_assign
id|p
suffix:semicolon
op_star
id|q
op_ne
l_int|0
op_logical_and
op_star
id|q
op_ne
l_char|&squot;&bslash;n&squot;
suffix:semicolon
op_increment
id|q
)paren
suffix:semicolon
r_if
c_cond
(paren
id|q
OG
id|p
)paren
id|call_prom
c_func
(paren
l_string|&quot;write&quot;
comma
l_int|3
comma
l_int|1
comma
id|prom_stdout
comma
id|p
comma
id|q
op_minus
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|q
op_ne
l_int|0
)paren
(brace
op_increment
id|q
suffix:semicolon
id|call_prom
c_func
(paren
l_string|&quot;write&quot;
comma
l_int|3
comma
l_int|1
comma
id|prom_stdout
comma
id|crlf
comma
l_int|2
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * We enter here early on, when the Open Firmware prom is still&n; * handling exceptions and the MMU hash table for us.&n; */
r_void
DECL|function|prom_init
id|prom_init
c_func
(paren
r_char
op_star
id|params
comma
r_int
id|unused
comma
r_void
(paren
op_star
id|pp
)paren
(paren
r_void
op_star
)paren
)paren
(brace
multiline_comment|/* First get a handle for the stdout device */
r_if
c_cond
(paren
id|_machine
op_ne
id|_MACH_Pmac
)paren
multiline_comment|/* prep */
r_return
suffix:semicolon
id|prom_entry
op_assign
id|pp
suffix:semicolon
id|prom_chosen
op_assign
id|call_prom
c_func
(paren
l_string|&quot;finddevice&quot;
comma
l_int|1
comma
l_int|1
comma
l_string|&quot;/chosen&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|prom_chosen
op_eq
(paren
r_void
op_star
)paren
op_minus
l_int|1
)paren
id|prom_exit
c_func
(paren
)paren
suffix:semicolon
id|call_prom
c_func
(paren
l_string|&quot;getprop&quot;
comma
l_int|4
comma
l_int|1
comma
id|prom_chosen
comma
l_string|&quot;stdout&quot;
comma
op_amp
id|prom_stdout
comma
(paren
r_void
op_star
)paren
r_sizeof
(paren
id|prom_stdout
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If we were booted via quik, params points to the physical address&n;&t; * of the command-line parameters.&n;&t; * If we were booted from an xcoff image (i.e. netbooted or&n;&t; * booted from floppy), we get the command line from the bootargs&n;&t; * property of the /chosen node.  If an initial ramdisk is present,&n;&t; * params and unused are used for initrd_start and initrd_size,&n;&t; * otherwise they contain 0xdeadbeef.  &n;&t; */
id|command_line
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|params
op_ge
l_int|0x4000
op_logical_and
(paren
r_int
r_int
)paren
id|params
OL
l_int|0x800000
op_logical_and
id|unused
op_eq
l_int|0
)paren
(brace
id|strncpy
c_func
(paren
id|command_line
comma
id|params
op_plus
id|KERNELBASE
comma
r_sizeof
(paren
id|command_line
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|params
op_minus
id|KERNELBASE
OL
l_int|0x800000
op_logical_and
id|unused
op_ne
l_int|0
op_logical_and
id|unused
op_ne
l_int|0xdeadbeef
)paren
(brace
id|initrd_start
op_assign
(paren
r_int
r_int
)paren
id|params
suffix:semicolon
id|initrd_end
op_assign
id|initrd_start
op_plus
id|unused
suffix:semicolon
id|ROOT_DEV
op_assign
id|MKDEV
c_func
(paren
id|RAMDISK_MAJOR
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
id|call_prom
c_func
(paren
l_string|&quot;getprop&quot;
comma
l_int|4
comma
l_int|1
comma
id|prom_chosen
comma
l_string|&quot;bootargs&quot;
comma
id|command_line
comma
r_sizeof
(paren
id|command_line
)paren
)paren
suffix:semicolon
)brace
id|command_line
(braket
r_sizeof
(paren
id|command_line
)paren
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|check_display
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * If we have a display that we don&squot;t know how to drive,&n; * we will want to try to execute OF&squot;s open method for it&n; * later.  However, OF may fall over if we do that after&n; * we&squot;ve taken over the MMU and done set_prom_callback.&n; * So we check whether we will need to open the display,&n; * and if so, open it now.&n; */
r_static
r_void
DECL|function|check_display
id|check_display
c_func
(paren
)paren
(brace
id|phandle
id|node
suffix:semicolon
id|ihandle
id|ih
suffix:semicolon
r_char
id|type
(braket
l_int|16
)braket
comma
id|name
(braket
l_int|64
)braket
comma
id|path
(braket
l_int|128
)braket
suffix:semicolon
r_for
c_loop
(paren
id|node
op_assign
l_int|0
suffix:semicolon
id|prom_next_node
c_func
(paren
op_amp
id|node
)paren
suffix:semicolon
)paren
(brace
id|type
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|getpromprop
c_func
(paren
id|node
comma
l_string|&quot;device_type&quot;
comma
id|type
comma
r_sizeof
(paren
id|type
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;display&quot;
)paren
op_ne
l_int|0
)paren
r_continue
suffix:semicolon
id|name
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|getpromprop
c_func
(paren
id|node
comma
l_string|&quot;name&quot;
comma
id|name
comma
r_sizeof
(paren
id|name
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmac_display_supported
c_func
(paren
id|name
)paren
)paren
multiline_comment|/* we have a supported display */
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;No supported display found&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|node
op_assign
l_int|0
suffix:semicolon
id|prom_next_node
c_func
(paren
op_amp
id|node
)paren
suffix:semicolon
)paren
(brace
id|type
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|getpromprop
c_func
(paren
id|node
comma
l_string|&quot;device_type&quot;
comma
id|type
comma
r_sizeof
(paren
id|type
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|type
comma
l_string|&quot;display&quot;
)paren
op_ne
l_int|0
)paren
r_continue
suffix:semicolon
multiline_comment|/* It seems OF doesn&squot;t null-terminate the path :-( */
id|memset
c_func
(paren
id|path
comma
l_int|0
comma
r_sizeof
(paren
id|path
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|call_prom
c_func
(paren
l_string|&quot;package-to-path&quot;
comma
l_int|3
comma
l_int|1
comma
id|node
comma
id|path
comma
r_sizeof
(paren
id|path
)paren
op_minus
l_int|1
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;can&squot;t get path for display %p&bslash;n&quot;
comma
id|node
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|ih
op_assign
id|call_prom
c_func
(paren
l_string|&quot;open&quot;
comma
l_int|1
comma
l_int|1
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ih
op_eq
l_int|0
op_logical_or
id|ih
op_eq
(paren
id|ihandle
)paren
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;couldn&squot;t open display %s&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Opened display device %s using &quot;
l_string|&quot;Open Firmware&bslash;n&quot;
comma
id|path
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|prom_display_path
comma
id|path
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|prom_next_node
id|prom_next_node
c_func
(paren
id|phandle
op_star
id|nodep
)paren
(brace
id|phandle
id|node
suffix:semicolon
r_if
c_cond
(paren
(paren
id|node
op_assign
op_star
id|nodep
)paren
op_ne
l_int|0
op_logical_and
(paren
op_star
id|nodep
op_assign
id|call_prom
c_func
(paren
l_string|&quot;child&quot;
comma
l_int|1
comma
l_int|1
comma
id|node
)paren
)paren
op_ne
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|nodep
op_assign
id|call_prom
c_func
(paren
l_string|&quot;peer&quot;
comma
l_int|1
comma
l_int|1
comma
id|node
)paren
)paren
op_ne
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
(paren
id|node
op_assign
id|call_prom
c_func
(paren
l_string|&quot;parent&quot;
comma
l_int|1
comma
l_int|1
comma
id|node
)paren
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|nodep
op_assign
id|call_prom
c_func
(paren
l_string|&quot;peer&quot;
comma
l_int|1
comma
l_int|1
comma
id|node
)paren
)paren
op_ne
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Callback routine for the PROM to call us.&n; * No services are implemented yet :-)&n; */
r_static
r_int
DECL|function|prom_callback
id|prom_callback
c_func
(paren
r_struct
id|prom_args
op_star
id|argv
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;uh oh, prom callback &squot;%s&squot; (%d/%d)&bslash;n&quot;
comma
id|argv-&gt;service
comma
id|argv-&gt;nargs
comma
id|argv-&gt;nret
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Register a callback with the Open Firmware PROM so it can ask&n; * us to map/unmap memory, etc.&n; */
r_void
DECL|function|set_prom_callback
id|set_prom_callback
c_func
(paren
)paren
(brace
id|call_prom
c_func
(paren
l_string|&quot;set-callback&quot;
comma
l_int|1
comma
l_int|1
comma
id|prom_callback
)paren
suffix:semicolon
)brace
r_void
DECL|function|abort
m_abort
(paren
)paren
(brace
macro_line|#ifdef CONFIG_XMON
id|xmon
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|prom_exit
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Make a copy of the device tree from the PROM.&n; */
DECL|variable|allnodes
r_static
r_struct
id|device_node
op_star
id|allnodes
suffix:semicolon
DECL|variable|allnextp
r_static
r_struct
id|device_node
op_star
op_star
id|allnextp
suffix:semicolon
DECL|macro|ALIGN
mdefine_line|#define ALIGN(x) (((x) + sizeof(unsigned long)-1) &amp; -sizeof(unsigned long))
r_int
r_int
DECL|function|copy_device_tree
id|copy_device_tree
c_func
(paren
r_int
r_int
id|mem_start
comma
r_int
r_int
id|mem_end
)paren
(brace
id|phandle
id|root
suffix:semicolon
id|root
op_assign
id|call_prom
c_func
(paren
l_string|&quot;peer&quot;
comma
l_int|1
comma
l_int|1
comma
(paren
id|phandle
)paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|root
op_eq
(paren
id|phandle
)paren
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;couldn&squot;t get device tree root&bslash;n&quot;
)paren
suffix:semicolon
id|allnextp
op_assign
op_amp
id|allnodes
suffix:semicolon
id|mem_start
op_assign
id|inspect_node
c_func
(paren
id|root
comma
l_int|0
comma
l_int|0
comma
id|mem_start
comma
id|mem_end
)paren
suffix:semicolon
op_star
id|allnextp
op_assign
l_int|0
suffix:semicolon
r_return
id|mem_start
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|inspect_node
id|inspect_node
c_func
(paren
id|phandle
id|node
comma
r_struct
id|device_node
op_star
id|dad
comma
r_int
r_int
id|base_address
comma
r_int
r_int
id|mem_start
comma
r_int
r_int
id|mem_end
)paren
(brace
r_struct
id|reg_property
op_star
id|reg
comma
op_star
id|rp
suffix:semicolon
r_struct
id|pci_reg_property
op_star
id|pci_addrs
suffix:semicolon
r_int
id|l
comma
id|i
suffix:semicolon
id|phandle
id|child
suffix:semicolon
r_struct
id|device_node
op_star
id|np
suffix:semicolon
r_struct
id|property
op_star
id|pp
comma
op_star
op_star
id|prev_propp
suffix:semicolon
r_char
op_star
id|prev_name
suffix:semicolon
id|np
op_assign
(paren
r_struct
id|device_node
op_star
)paren
id|mem_start
suffix:semicolon
id|mem_start
op_add_assign
r_sizeof
(paren
r_struct
id|device_node
)paren
suffix:semicolon
id|memset
c_func
(paren
id|np
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|np
)paren
)paren
suffix:semicolon
id|np-&gt;node
op_assign
id|node
suffix:semicolon
op_star
id|allnextp
op_assign
id|np
suffix:semicolon
id|allnextp
op_assign
op_amp
id|np-&gt;allnext
suffix:semicolon
id|np-&gt;parent
op_assign
id|dad
suffix:semicolon
r_if
c_cond
(paren
id|dad
op_ne
l_int|0
)paren
(brace
multiline_comment|/* we temporarily use the `next&squot; field as `last_child&squot;. */
r_if
c_cond
(paren
id|dad-&gt;next
op_eq
l_int|0
)paren
id|dad-&gt;child
op_assign
id|np
suffix:semicolon
r_else
id|dad-&gt;next-&gt;sibling
op_assign
id|np
suffix:semicolon
id|dad-&gt;next
op_assign
id|np
suffix:semicolon
)brace
multiline_comment|/* get and store all properties */
id|prev_propp
op_assign
op_amp
id|np-&gt;properties
suffix:semicolon
id|prev_name
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|pp
op_assign
(paren
r_struct
id|property
op_star
)paren
id|mem_start
suffix:semicolon
id|pp-&gt;name
op_assign
(paren
r_char
op_star
)paren
(paren
id|pp
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|call_prom
c_func
(paren
l_string|&quot;nextprop&quot;
comma
l_int|3
comma
l_int|1
comma
id|node
comma
id|prev_name
comma
id|pp-&gt;name
)paren
op_le
l_int|0
)paren
r_break
suffix:semicolon
id|mem_start
op_assign
id|ALIGN
c_func
(paren
(paren
r_int
r_int
)paren
id|pp-&gt;name
op_plus
id|strlen
c_func
(paren
id|pp-&gt;name
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|pp-&gt;value
op_assign
(paren
r_int
r_char
op_star
)paren
id|mem_start
suffix:semicolon
id|pp-&gt;length
op_assign
(paren
r_int
)paren
id|call_prom
c_func
(paren
l_string|&quot;getprop&quot;
comma
l_int|4
comma
l_int|1
comma
id|node
comma
id|pp-&gt;name
comma
id|pp-&gt;value
comma
id|mem_end
op_minus
id|mem_start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pp-&gt;length
OL
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;hey, where did property %s go?&quot;
comma
id|pp-&gt;name
)paren
suffix:semicolon
id|mem_start
op_assign
id|ALIGN
c_func
(paren
id|mem_start
op_plus
id|pp-&gt;length
)paren
suffix:semicolon
id|prev_name
op_assign
id|pp-&gt;name
suffix:semicolon
op_star
id|prev_propp
op_assign
id|pp
suffix:semicolon
id|prev_propp
op_assign
op_amp
id|pp-&gt;next
suffix:semicolon
)brace
op_star
id|prev_propp
op_assign
l_int|0
suffix:semicolon
id|np-&gt;name
op_assign
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;name&quot;
comma
l_int|0
)paren
suffix:semicolon
id|np-&gt;type
op_assign
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;device_type&quot;
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* get all the device addresses and interrupts */
id|reg
op_assign
(paren
r_struct
id|reg_property
op_star
)paren
id|mem_start
suffix:semicolon
id|pci_addrs
op_assign
(paren
r_struct
id|pci_reg_property
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;assigned-addresses&quot;
comma
op_amp
id|l
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pci_addrs
op_ne
l_int|0
)paren
(brace
r_while
c_loop
(paren
(paren
id|l
op_sub_assign
r_sizeof
(paren
r_struct
id|pci_reg_property
)paren
)paren
op_ge
l_int|0
)paren
(brace
multiline_comment|/* XXX assumes PCI addresses mapped 1-1 to physical */
id|reg
(braket
id|i
)braket
dot
id|address
op_assign
id|pci_addrs
(braket
id|i
)braket
dot
id|addr.a_lo
suffix:semicolon
id|reg
(braket
id|i
)braket
dot
id|size
op_assign
id|pci_addrs
(braket
id|i
)braket
dot
id|size_lo
suffix:semicolon
op_increment
id|i
suffix:semicolon
)brace
)brace
r_else
(brace
id|rp
op_assign
(paren
r_struct
id|reg_property
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;reg&quot;
comma
op_amp
id|l
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rp
op_ne
l_int|0
)paren
(brace
r_while
c_loop
(paren
(paren
id|l
op_sub_assign
r_sizeof
(paren
r_struct
id|reg_property
)paren
)paren
op_ge
l_int|0
)paren
(brace
id|reg
(braket
id|i
)braket
dot
id|address
op_assign
id|rp
(braket
id|i
)braket
dot
id|address
op_plus
id|base_address
suffix:semicolon
id|reg
(braket
id|i
)braket
dot
id|size
op_assign
id|rp
(braket
id|i
)braket
dot
id|size
suffix:semicolon
op_increment
id|i
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|i
OG
l_int|0
)paren
(brace
id|np-&gt;addrs
op_assign
id|reg
suffix:semicolon
id|np-&gt;n_addrs
op_assign
id|i
suffix:semicolon
id|mem_start
op_add_assign
id|i
op_star
r_sizeof
(paren
r_struct
id|reg_property
)paren
suffix:semicolon
)brace
id|np-&gt;intrs
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;AAPL,interrupts&quot;
comma
op_amp
id|l
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;intrs
op_ne
l_int|0
)paren
id|np-&gt;n_intrs
op_assign
id|l
op_div
r_sizeof
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* get the node&squot;s full name */
id|l
op_assign
(paren
r_int
)paren
id|call_prom
c_func
(paren
l_string|&quot;package-to-path&quot;
comma
l_int|3
comma
l_int|1
comma
id|node
comma
(paren
r_char
op_star
)paren
id|mem_start
comma
id|mem_end
op_minus
id|mem_start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l
op_ge
l_int|0
)paren
(brace
id|np-&gt;full_name
op_assign
(paren
r_char
op_star
)paren
id|mem_start
suffix:semicolon
id|np-&gt;full_name
(braket
id|l
)braket
op_assign
l_int|0
suffix:semicolon
id|mem_start
op_assign
id|ALIGN
c_func
(paren
id|mem_start
op_plus
id|l
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|np-&gt;type
op_ne
l_int|0
op_logical_and
id|strcmp
c_func
(paren
id|np-&gt;type
comma
l_string|&quot;dbdma&quot;
)paren
op_eq
l_int|0
op_logical_and
id|np-&gt;n_addrs
OG
l_int|0
)paren
id|base_address
op_assign
id|np-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
suffix:semicolon
id|child
op_assign
id|call_prom
c_func
(paren
l_string|&quot;child&quot;
comma
l_int|1
comma
l_int|1
comma
id|node
)paren
suffix:semicolon
r_while
c_loop
(paren
id|child
op_ne
(paren
r_void
op_star
)paren
l_int|0
)paren
(brace
id|mem_start
op_assign
id|inspect_node
c_func
(paren
id|child
comma
id|np
comma
id|base_address
comma
id|mem_start
comma
id|mem_end
)paren
suffix:semicolon
id|child
op_assign
id|call_prom
c_func
(paren
l_string|&quot;peer&quot;
comma
l_int|1
comma
l_int|1
comma
id|child
)paren
suffix:semicolon
)brace
r_return
id|mem_start
suffix:semicolon
)brace
multiline_comment|/*&n; * Construct a return a list of the device_nodes with a given name.&n; */
r_struct
id|device_node
op_star
DECL|function|find_devices
id|find_devices
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|device_node
op_star
id|head
comma
op_star
op_star
id|prevp
comma
op_star
id|np
suffix:semicolon
id|prevp
op_assign
op_amp
id|head
suffix:semicolon
r_for
c_loop
(paren
id|np
op_assign
id|allnodes
suffix:semicolon
id|np
op_ne
l_int|0
suffix:semicolon
id|np
op_assign
id|np-&gt;allnext
)paren
(brace
r_if
c_cond
(paren
id|np-&gt;name
op_ne
l_int|0
op_logical_and
id|strcasecmp
c_func
(paren
id|np-&gt;name
comma
id|name
)paren
op_eq
l_int|0
)paren
(brace
op_star
id|prevp
op_assign
id|np
suffix:semicolon
id|prevp
op_assign
op_amp
id|np-&gt;next
suffix:semicolon
)brace
)brace
op_star
id|prevp
op_assign
l_int|0
suffix:semicolon
r_return
id|head
suffix:semicolon
)brace
multiline_comment|/*&n; * Construct a return a list of the device_nodes with a given type.&n; */
r_struct
id|device_node
op_star
DECL|function|find_type_devices
id|find_type_devices
c_func
(paren
r_const
r_char
op_star
id|type
)paren
(brace
r_struct
id|device_node
op_star
id|head
comma
op_star
op_star
id|prevp
comma
op_star
id|np
suffix:semicolon
id|prevp
op_assign
op_amp
id|head
suffix:semicolon
r_for
c_loop
(paren
id|np
op_assign
id|allnodes
suffix:semicolon
id|np
op_ne
l_int|0
suffix:semicolon
id|np
op_assign
id|np-&gt;allnext
)paren
(brace
r_if
c_cond
(paren
id|np-&gt;type
op_ne
l_int|0
op_logical_and
id|strcasecmp
c_func
(paren
id|np-&gt;type
comma
id|type
)paren
op_eq
l_int|0
)paren
(brace
op_star
id|prevp
op_assign
id|np
suffix:semicolon
id|prevp
op_assign
op_amp
id|np-&gt;next
suffix:semicolon
)brace
)brace
op_star
id|prevp
op_assign
l_int|0
suffix:semicolon
r_return
id|head
suffix:semicolon
)brace
multiline_comment|/*&n; * Find the device_node with a given full_name.&n; */
r_struct
id|device_node
op_star
DECL|function|find_path_device
id|find_path_device
c_func
(paren
r_const
r_char
op_star
id|path
)paren
(brace
r_struct
id|device_node
op_star
id|np
suffix:semicolon
r_for
c_loop
(paren
id|np
op_assign
id|allnodes
suffix:semicolon
id|np
op_ne
l_int|0
suffix:semicolon
id|np
op_assign
id|np-&gt;allnext
)paren
r_if
c_cond
(paren
id|np-&gt;full_name
op_ne
l_int|0
op_logical_and
id|strcasecmp
c_func
(paren
id|np-&gt;full_name
comma
id|path
)paren
op_eq
l_int|0
)paren
r_return
id|np
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Find a property with a given name for a given node&n; * and return the value.&n; */
r_int
r_char
op_star
DECL|function|get_property
id|get_property
c_func
(paren
r_struct
id|device_node
op_star
id|np
comma
r_const
r_char
op_star
id|name
comma
r_int
op_star
id|lenp
)paren
(brace
r_struct
id|property
op_star
id|pp
suffix:semicolon
r_for
c_loop
(paren
id|pp
op_assign
id|np-&gt;properties
suffix:semicolon
id|pp
op_ne
l_int|0
suffix:semicolon
id|pp
op_assign
id|pp-&gt;next
)paren
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|pp-&gt;name
comma
id|name
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|lenp
op_ne
l_int|0
)paren
op_star
id|lenp
op_assign
id|pp-&gt;length
suffix:semicolon
r_return
id|pp-&gt;value
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|print_properties
id|print_properties
c_func
(paren
r_struct
id|device_node
op_star
id|np
)paren
(brace
r_struct
id|property
op_star
id|pp
suffix:semicolon
r_char
op_star
id|cp
suffix:semicolon
r_int
id|i
comma
id|n
suffix:semicolon
r_for
c_loop
(paren
id|pp
op_assign
id|np-&gt;properties
suffix:semicolon
id|pp
op_ne
l_int|0
suffix:semicolon
id|pp
op_assign
id|pp-&gt;next
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s&quot;
comma
id|pp-&gt;name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|strlen
c_func
(paren
id|pp-&gt;name
)paren
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
op_increment
id|i
)paren
id|printk
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|cp
op_assign
(paren
r_char
op_star
)paren
id|pp-&gt;value
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|pp-&gt;length
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
op_decrement
id|i
comma
op_increment
id|cp
)paren
r_if
c_cond
(paren
(paren
id|i
OG
l_int|1
op_logical_and
(paren
op_star
id|cp
template_param
l_int|0x7e
)paren
)paren
op_logical_or
(paren
id|i
op_eq
l_int|1
op_logical_and
op_star
id|cp
op_ne
l_int|0
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|0
op_logical_and
id|pp-&gt;length
OG
l_int|1
)paren
(brace
multiline_comment|/* looks like a string */
id|printk
c_func
(paren
l_string|&quot; %s&bslash;n&quot;
comma
(paren
r_char
op_star
)paren
id|pp-&gt;value
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* dump it in hex */
id|n
op_assign
id|pp-&gt;length
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
l_int|64
)paren
id|n
op_assign
l_int|64
suffix:semicolon
r_if
c_cond
(paren
id|pp-&gt;length
op_mod
l_int|4
op_eq
l_int|0
)paren
(brace
r_int
r_int
op_star
id|p
op_assign
(paren
r_int
r_int
op_star
)paren
id|pp-&gt;value
suffix:semicolon
id|n
op_div_assign
l_int|4
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
id|n
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|i
op_ne
l_int|0
op_logical_and
(paren
id|i
op_mod
l_int|4
)paren
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n                &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; %08x&quot;
comma
op_star
id|p
op_increment
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_int
r_char
op_star
id|bp
op_assign
id|pp-&gt;value
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
id|n
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|i
op_ne
l_int|0
op_logical_and
(paren
id|i
op_mod
l_int|16
)paren
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n                &quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; %02x&quot;
comma
op_star
id|bp
op_increment
)paren
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pp-&gt;length
OG
l_int|64
)paren
id|printk
c_func
(paren
l_string|&quot;                 ... (length = %d)&bslash;n&quot;
comma
id|pp-&gt;length
)paren
suffix:semicolon
)brace
)brace
)brace
eof
