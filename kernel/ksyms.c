multiline_comment|/* &n; * Herein lies all the functions/variables that are &quot;exported&quot; for linkage&n; * with dynamically loaded kernel modules.&n; *&t;&t;&t;Jon.&n; *&n; * - Stacked module support and unified symbol table added (June 1994)&n; * - External symbol table support added (December 1994)&n; * - Versions on symbols added (December 1994)&n; * by Bjorn Ekwall &lt;bj0rn@blox.se&gt;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/sys.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/binfmts.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/sem.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
r_extern
r_int
r_char
id|aux_device_present
comma
id|kbd_read_mask
suffix:semicolon
macro_line|#ifdef __alpha__
macro_line|# include &lt;asm/io.h&gt;
macro_line|# include &lt;asm/hwrpb.h&gt;
r_extern
r_void
id|bcopy
(paren
r_const
r_char
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_struct
id|hwrpb_struct
op_star
id|hwrpb
suffix:semicolon
multiline_comment|/* these are C runtime functions with special calling conventions: */
r_extern
r_void
id|__divl
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__reml
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__divq
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__remq
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__divlu
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__remlu
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__divqu
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__remqu
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NET
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/firewall.h&gt;
macro_line|#include &lt;linux/trdevice.h&gt;
macro_line|#ifdef CONFIG_AX25
macro_line|#include &lt;net/ax25.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_INET
macro_line|#include &lt;linux/ip.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/arp.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/route.h&gt;
macro_line|#include &lt;linux/net_alias.h&gt;
macro_line|#if defined(CONFIG_PPP) || defined(CONFIG_SLIP)
macro_line|#include &quot;../drivers/net/slhc.h&quot;
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_NET_ALIAS
macro_line|#include &lt;linux/net_alias.h&gt;
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_PCI
macro_line|#include &lt;linux/bios32.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_MSDOS_FS) &amp;&amp; !defined(CONFIG_UMSDOS_FS)
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_PROC_FS)
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#ifdef __SMP__
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#endif
r_extern
r_char
op_star
id|get_options
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
suffix:semicolon
r_extern
r_void
id|set_device_ro
c_func
(paren
r_int
id|dev
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
r_struct
id|file_operations
op_star
id|get_blkfops
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
op_star
id|sys_call_table
suffix:semicolon
macro_line|#if&t;defined(CONFIG_ULTRA)&t;||&t;defined(CONFIG_WD80x3)&t;&t;|| &bslash;&n;&t;defined(CONFIG_EL2)&t;||&t;defined(CONFIG_NE2000)&t;&t;|| &bslash;&n;&t;defined(CONFIG_E2100)&t;||&t;defined(CONFIG_HPLAN_PLUS)&t;|| &bslash;&n;&t;defined(CONFIG_HPLAN)&t;||&t;defined(CONFIG_AC3200)&t;&t;
macro_line|#include &quot;../drivers/net/8390.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI
macro_line|#include &quot;../drivers/scsi/scsi.h&quot;
macro_line|#include &quot;../drivers/scsi/scsi_ioctl.h&quot;
macro_line|#include &quot;../drivers/scsi/hosts.h&quot;
macro_line|#include &quot;../drivers/scsi/constants.h&quot;
macro_line|#include &quot;../drivers/scsi/sd.h&quot;
macro_line|#include &lt;linux/scsicam.h&gt;
r_extern
r_int
id|generic_proc_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|sys_tz
suffix:semicolon
r_extern
r_int
id|request_dma
c_func
(paren
r_int
r_int
id|dmanr
comma
r_char
op_star
id|deviceID
)paren
suffix:semicolon
r_extern
r_void
id|free_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|rarp_ioctl_hook
)paren
(paren
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|iABI_hook
)paren
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BINFMT_ELF
macro_line|#include &lt;linux/elfcore.h&gt;
r_extern
r_int
id|dump_fpu
c_func
(paren
id|elf_fpregset_t
op_star
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|symbol_table
r_struct
id|symbol_table
id|symbol_table
op_assign
(brace
macro_line|#include &lt;linux/symtab_begin.h&gt;
macro_line|#ifdef MODVERSIONS
(brace
(paren
r_void
op_star
)paren
l_int|1
multiline_comment|/* Version version :-) */
comma
id|SYMBOL_NAME_STR
(paren
id|Using_Versions
)paren
)brace
comma
macro_line|#endif
multiline_comment|/* platform dependent support */
macro_line|#ifdef __alpha__
id|X
c_func
(paren
id|_inb
)paren
comma
id|X
c_func
(paren
id|_inw
)paren
comma
id|X
c_func
(paren
id|_inl
)paren
comma
id|X
c_func
(paren
id|_outb
)paren
comma
id|X
c_func
(paren
id|_outw
)paren
comma
id|X
c_func
(paren
id|_outl
)paren
comma
id|X
c_func
(paren
id|bcopy
)paren
comma
multiline_comment|/* generated by gcc-2.7.0 for string assignments */
id|X
c_func
(paren
id|hwrpb
)paren
comma
id|X
c_func
(paren
id|__divl
)paren
comma
id|X
c_func
(paren
id|__reml
)paren
comma
id|X
c_func
(paren
id|__divq
)paren
comma
id|X
c_func
(paren
id|__remq
)paren
comma
id|X
c_func
(paren
id|__divlu
)paren
comma
id|X
c_func
(paren
id|__remlu
)paren
comma
id|X
c_func
(paren
id|__divqu
)paren
comma
id|X
c_func
(paren
id|__remqu
)paren
comma
id|X
c_func
(paren
id|strlen
)paren
comma
multiline_comment|/* used by ftape */
id|X
c_func
(paren
id|memcmp
)paren
comma
id|X
c_func
(paren
id|memmove
)paren
comma
id|X
c_func
(paren
id|__constant_c_memset
)paren
comma
macro_line|#endif
multiline_comment|/* stackable module support */
id|X
c_func
(paren
id|rename_module_symbol
)paren
comma
id|X
c_func
(paren
id|register_symtab
)paren
comma
id|X
c_func
(paren
id|get_options
)paren
comma
multiline_comment|/* system info variables */
multiline_comment|/* These check that they aren&squot;t defines (0/1) */
macro_line|#ifndef EISA_bus__is_a_macro
id|X
c_func
(paren
id|EISA_bus
)paren
comma
macro_line|#endif
macro_line|#ifndef MCA_bus__is_a_macro
id|X
c_func
(paren
id|MCA_bus
)paren
comma
macro_line|#endif
macro_line|#ifndef wp_works_ok__is_a_macro
id|X
c_func
(paren
id|wp_works_ok
)paren
comma
macro_line|#endif
macro_line|#ifdef CONFIG_PCI
multiline_comment|/* PCI BIOS support */
id|X
c_func
(paren
id|pcibios_present
)paren
comma
id|X
c_func
(paren
id|pcibios_find_class
)paren
comma
id|X
c_func
(paren
id|pcibios_find_device
)paren
comma
id|X
c_func
(paren
id|pcibios_read_config_byte
)paren
comma
id|X
c_func
(paren
id|pcibios_read_config_word
)paren
comma
id|X
c_func
(paren
id|pcibios_read_config_dword
)paren
comma
id|X
c_func
(paren
id|pcibios_strerror
)paren
comma
id|X
c_func
(paren
id|pcibios_write_config_byte
)paren
comma
id|X
c_func
(paren
id|pcibios_write_config_word
)paren
comma
id|X
c_func
(paren
id|pcibios_write_config_dword
)paren
comma
macro_line|#endif
multiline_comment|/* process memory management */
id|X
c_func
(paren
id|verify_area
)paren
comma
id|X
c_func
(paren
id|do_mmap
)paren
comma
id|X
c_func
(paren
id|do_munmap
)paren
comma
id|X
c_func
(paren
id|insert_vm_struct
)paren
comma
id|X
c_func
(paren
id|merge_segments
)paren
comma
multiline_comment|/* internal kernel memory management */
id|X
c_func
(paren
id|__get_free_pages
)paren
comma
id|X
c_func
(paren
id|free_pages
)paren
comma
id|X
c_func
(paren
id|kmalloc
)paren
comma
id|X
c_func
(paren
id|kfree
)paren
comma
id|X
c_func
(paren
id|vmalloc
)paren
comma
id|X
c_func
(paren
id|vremap
)paren
comma
id|X
c_func
(paren
id|vfree
)paren
comma
id|X
c_func
(paren
id|mem_map
)paren
comma
id|X
c_func
(paren
id|remap_page_range
)paren
comma
id|X
c_func
(paren
id|high_memory
)paren
comma
multiline_comment|/* filesystem internal functions */
id|X
c_func
(paren
id|getname
)paren
comma
id|X
c_func
(paren
id|putname
)paren
comma
id|X
c_func
(paren
id|__iget
)paren
comma
id|X
c_func
(paren
id|iput
)paren
comma
id|X
c_func
(paren
id|namei
)paren
comma
id|X
c_func
(paren
id|lnamei
)paren
comma
id|X
c_func
(paren
id|open_namei
)paren
comma
id|X
c_func
(paren
id|close_fp
)paren
comma
id|X
c_func
(paren
id|check_disk_change
)paren
comma
id|X
c_func
(paren
id|invalidate_buffers
)paren
comma
id|X
c_func
(paren
id|invalidate_inodes
)paren
comma
id|X
c_func
(paren
id|fsync_dev
)paren
comma
id|X
c_func
(paren
id|permission
)paren
comma
id|X
c_func
(paren
id|inode_setattr
)paren
comma
id|X
c_func
(paren
id|inode_change_ok
)paren
comma
id|X
c_func
(paren
id|generic_mmap
)paren
comma
id|X
c_func
(paren
id|set_blocksize
)paren
comma
id|X
c_func
(paren
id|getblk
)paren
comma
id|X
c_func
(paren
id|bread
)paren
comma
id|X
c_func
(paren
id|breada
)paren
comma
id|X
c_func
(paren
id|__brelse
)paren
comma
id|X
c_func
(paren
id|__bforget
)paren
comma
id|X
c_func
(paren
id|ll_rw_block
)paren
comma
id|X
c_func
(paren
id|__wait_on_buffer
)paren
comma
id|X
c_func
(paren
id|dcache_lookup
)paren
comma
id|X
c_func
(paren
id|dcache_add
)paren
comma
id|X
c_func
(paren
id|aout_core_dump
)paren
comma
id|X
c_func
(paren
id|add_blkdev_randomness
)paren
comma
multiline_comment|/* device registration */
id|X
c_func
(paren
id|register_chrdev
)paren
comma
id|X
c_func
(paren
id|unregister_chrdev
)paren
comma
id|X
c_func
(paren
id|register_blkdev
)paren
comma
id|X
c_func
(paren
id|unregister_blkdev
)paren
comma
id|X
c_func
(paren
id|tty_register_driver
)paren
comma
id|X
c_func
(paren
id|tty_unregister_driver
)paren
comma
id|X
c_func
(paren
id|tty_std_termios
)paren
comma
multiline_comment|/* block device driver support */
id|X
c_func
(paren
id|block_read
)paren
comma
id|X
c_func
(paren
id|block_write
)paren
comma
id|X
c_func
(paren
id|block_fsync
)paren
comma
id|X
c_func
(paren
id|wait_for_request
)paren
comma
id|X
c_func
(paren
id|blksize_size
)paren
comma
id|X
c_func
(paren
id|hardsect_size
)paren
comma
id|X
c_func
(paren
id|blk_size
)paren
comma
id|X
c_func
(paren
id|blk_dev
)paren
comma
id|X
c_func
(paren
id|is_read_only
)paren
comma
id|X
c_func
(paren
id|set_device_ro
)paren
comma
id|X
c_func
(paren
id|bmap
)paren
comma
id|X
c_func
(paren
id|sync_dev
)paren
comma
id|X
c_func
(paren
id|get_blkfops
)paren
comma
multiline_comment|/* Module creation of serial units */
id|X
c_func
(paren
id|register_serial
)paren
comma
id|X
c_func
(paren
id|unregister_serial
)paren
comma
multiline_comment|/* tty routines */
id|X
c_func
(paren
id|tty_hangup
)paren
comma
id|X
c_func
(paren
id|tty_wait_until_sent
)paren
comma
id|X
c_func
(paren
id|tty_check_change
)paren
comma
id|X
c_func
(paren
id|tty_hung_up_p
)paren
comma
id|X
c_func
(paren
id|do_SAK
)paren
comma
id|X
c_func
(paren
id|console_print
)paren
comma
multiline_comment|/* filesystem registration */
id|X
c_func
(paren
id|register_filesystem
)paren
comma
id|X
c_func
(paren
id|unregister_filesystem
)paren
comma
multiline_comment|/* executable format registration */
id|X
c_func
(paren
id|register_binfmt
)paren
comma
id|X
c_func
(paren
id|unregister_binfmt
)paren
comma
multiline_comment|/* execution environment registration */
id|X
c_func
(paren
id|lookup_exec_domain
)paren
comma
id|X
c_func
(paren
id|register_exec_domain
)paren
comma
id|X
c_func
(paren
id|unregister_exec_domain
)paren
comma
multiline_comment|/* interrupt handling */
id|X
c_func
(paren
id|request_irq
)paren
comma
id|X
c_func
(paren
id|free_irq
)paren
comma
id|X
c_func
(paren
id|enable_irq
)paren
comma
id|X
c_func
(paren
id|disable_irq
)paren
comma
id|X
c_func
(paren
id|probe_irq_on
)paren
comma
id|X
c_func
(paren
id|probe_irq_off
)paren
comma
id|X
c_func
(paren
id|bh_active
)paren
comma
id|X
c_func
(paren
id|bh_mask
)paren
comma
id|X
c_func
(paren
id|bh_base
)paren
comma
id|X
c_func
(paren
id|add_timer
)paren
comma
id|X
c_func
(paren
id|del_timer
)paren
comma
id|X
c_func
(paren
id|tq_timer
)paren
comma
id|X
c_func
(paren
id|tq_immediate
)paren
comma
id|X
c_func
(paren
id|tq_scheduler
)paren
comma
id|X
c_func
(paren
id|tq_last
)paren
comma
id|X
c_func
(paren
id|timer_active
)paren
comma
id|X
c_func
(paren
id|timer_table
)paren
comma
id|X
c_func
(paren
id|intr_count
)paren
comma
multiline_comment|/* autoirq from  drivers/net/auto_irq.c */
id|X
c_func
(paren
id|autoirq_setup
)paren
comma
id|X
c_func
(paren
id|autoirq_report
)paren
comma
multiline_comment|/* dma handling */
id|X
c_func
(paren
id|request_dma
)paren
comma
id|X
c_func
(paren
id|free_dma
)paren
comma
macro_line|#ifdef HAVE_DISABLE_HLT
id|X
c_func
(paren
id|disable_hlt
)paren
comma
id|X
c_func
(paren
id|enable_hlt
)paren
comma
macro_line|#endif
multiline_comment|/* IO port handling */
id|X
c_func
(paren
id|check_region
)paren
comma
id|X
c_func
(paren
id|request_region
)paren
comma
id|X
c_func
(paren
id|release_region
)paren
comma
multiline_comment|/* process management */
id|X
c_func
(paren
id|wake_up
)paren
comma
id|X
c_func
(paren
id|wake_up_interruptible
)paren
comma
id|X
c_func
(paren
id|sleep_on
)paren
comma
id|X
c_func
(paren
id|interruptible_sleep_on
)paren
comma
id|X
c_func
(paren
id|schedule
)paren
comma
id|X
c_func
(paren
id|current_set
)paren
comma
macro_line|#if defined(__i386__) &amp;&amp; defined(__SMP__)
id|X
c_func
(paren
id|apic_reg
)paren
comma
multiline_comment|/* Needed internally for the I386 inlines */
macro_line|#endif&t;
id|X
c_func
(paren
id|jiffies
)paren
comma
id|X
c_func
(paren
id|xtime
)paren
comma
id|X
c_func
(paren
id|do_gettimeofday
)paren
comma
id|X
c_func
(paren
id|loops_per_sec
)paren
comma
id|X
c_func
(paren
id|need_resched
)paren
comma
id|X
c_func
(paren
id|kstat
)paren
comma
id|X
c_func
(paren
id|kill_proc
)paren
comma
id|X
c_func
(paren
id|kill_pg
)paren
comma
id|X
c_func
(paren
id|kill_sl
)paren
comma
multiline_comment|/* misc */
id|X
c_func
(paren
id|panic
)paren
comma
id|X
c_func
(paren
id|printk
)paren
comma
id|X
c_func
(paren
id|sprintf
)paren
comma
id|X
c_func
(paren
id|vsprintf
)paren
comma
id|X
c_func
(paren
id|kdevname
)paren
comma
id|X
c_func
(paren
id|simple_strtoul
)paren
comma
id|X
c_func
(paren
id|system_utsname
)paren
comma
id|X
c_func
(paren
id|sys_call_table
)paren
comma
multiline_comment|/* Signal interfaces */
id|X
c_func
(paren
id|send_sig
)paren
comma
multiline_comment|/* Program loader interfaces */
id|X
c_func
(paren
id|setup_arg_pages
)paren
comma
id|X
c_func
(paren
id|copy_strings
)paren
comma
id|X
c_func
(paren
id|create_tables
)paren
comma
id|X
c_func
(paren
id|do_execve
)paren
comma
id|X
c_func
(paren
id|flush_old_exec
)paren
comma
id|X
c_func
(paren
id|open_inode
)paren
comma
id|X
c_func
(paren
id|read_exec
)paren
comma
multiline_comment|/* Miscellaneous access points */
id|X
c_func
(paren
id|si_meminfo
)paren
comma
macro_line|#ifdef CONFIG_NET
multiline_comment|/* Socket layer registration */
id|X
c_func
(paren
id|sock_register
)paren
comma
id|X
c_func
(paren
id|sock_unregister
)paren
comma
macro_line|#ifdef CONFIG_FIREWALL
multiline_comment|/* Firewall registration */
id|X
c_func
(paren
id|register_firewall
)paren
comma
id|X
c_func
(paren
id|unregister_firewall
)paren
comma
macro_line|#endif
macro_line|#ifdef CONFIG_INET&t;
multiline_comment|/* Internet layer registration */
id|X
c_func
(paren
id|inet_add_protocol
)paren
comma
id|X
c_func
(paren
id|inet_del_protocol
)paren
comma
id|X
c_func
(paren
id|rarp_ioctl_hook
)paren
comma
id|X
c_func
(paren
id|init_etherdev
)paren
comma
id|X
c_func
(paren
id|ip_rt_route
)paren
comma
id|X
c_func
(paren
id|ip_rt_put
)paren
comma
id|X
c_func
(paren
id|arp_send
)paren
comma
macro_line|#ifdef CONFIG_IP_FORWARD
id|X
c_func
(paren
id|ip_forward
)paren
comma
macro_line|#endif
macro_line|#if&t;defined(CONFIG_ULTRA)&t;||&t;defined(CONFIG_WD80x3)&t;&t;|| &bslash;&n;&t;defined(CONFIG_EL2)&t;||&t;defined(CONFIG_NE2000)&t;&t;|| &bslash;&n;&t;defined(CONFIG_E2100)&t;||&t;defined(CONFIG_HPLAN_PLUS)&t;|| &bslash;&n;&t;defined(CONFIG_HPLAN)&t;||&t;defined(CONFIG_AC3200)
multiline_comment|/* If 8390 NIC support is built in, we will need these. */
id|X
c_func
(paren
id|ei_open
)paren
comma
id|X
c_func
(paren
id|ei_close
)paren
comma
id|X
c_func
(paren
id|ei_debug
)paren
comma
id|X
c_func
(paren
id|ei_interrupt
)paren
comma
id|X
c_func
(paren
id|ethdev_init
)paren
comma
id|X
c_func
(paren
id|NS8390_init
)paren
comma
macro_line|#endif
macro_line|#if defined(CONFIG_PPP) || defined(CONFIG_SLIP)
multiline_comment|/* VJ header compression */
id|X
c_func
(paren
id|slhc_init
)paren
comma
id|X
c_func
(paren
id|slhc_free
)paren
comma
id|X
c_func
(paren
id|slhc_remember
)paren
comma
id|X
c_func
(paren
id|slhc_compress
)paren
comma
id|X
c_func
(paren
id|slhc_uncompress
)paren
comma
id|X
c_func
(paren
id|slhc_toss
)paren
comma
macro_line|#endif
macro_line|#ifdef CONFIG_NET_ALIAS
macro_line|#include &lt;linux/net_alias.h&gt;
macro_line|#endif
macro_line|#endif
multiline_comment|/* Device callback registration */
id|X
c_func
(paren
id|register_netdevice_notifier
)paren
comma
id|X
c_func
(paren
id|unregister_netdevice_notifier
)paren
comma
macro_line|#ifdef CONFIG_NET_ALIAS
id|X
c_func
(paren
id|register_net_alias_type
)paren
comma
id|X
c_func
(paren
id|unregister_net_alias_type
)paren
comma
macro_line|#endif
macro_line|#endif
multiline_comment|/* support for loadable net drivers */
macro_line|#ifdef CONFIG_AX25
id|X
c_func
(paren
id|ax25_encapsulate
)paren
comma
id|X
c_func
(paren
id|ax25_rebuild_header
)paren
comma
macro_line|#endif&t;
macro_line|#ifdef CONFIG_INET
id|X
c_func
(paren
id|register_netdev
)paren
comma
id|X
c_func
(paren
id|unregister_netdev
)paren
comma
id|X
c_func
(paren
id|ether_setup
)paren
comma
id|X
c_func
(paren
id|eth_type_trans
)paren
comma
id|X
c_func
(paren
id|eth_copy_and_sum
)paren
comma
id|X
c_func
(paren
id|alloc_skb
)paren
comma
id|X
c_func
(paren
id|kfree_skb
)paren
comma
id|X
c_func
(paren
id|dev_alloc_skb
)paren
comma
id|X
c_func
(paren
id|dev_kfree_skb
)paren
comma
id|X
c_func
(paren
id|netif_rx
)paren
comma
id|X
c_func
(paren
id|dev_rint
)paren
comma
id|X
c_func
(paren
id|dev_tint
)paren
comma
id|X
c_func
(paren
id|irq2dev_map
)paren
comma
id|X
c_func
(paren
id|dev_add_pack
)paren
comma
id|X
c_func
(paren
id|dev_remove_pack
)paren
comma
id|X
c_func
(paren
id|dev_get
)paren
comma
id|X
c_func
(paren
id|dev_ioctl
)paren
comma
id|X
c_func
(paren
id|dev_queue_xmit
)paren
comma
id|X
c_func
(paren
id|dev_base
)paren
comma
id|X
c_func
(paren
id|dev_close
)paren
comma
id|X
c_func
(paren
id|arp_find
)paren
comma
id|X
c_func
(paren
id|n_tty_ioctl
)paren
comma
id|X
c_func
(paren
id|tty_register_ldisc
)paren
comma
id|X
c_func
(paren
id|kill_fasync
)paren
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI
multiline_comment|/* Supports loadable scsi drivers &n; &t; * technically some of this stuff could be moved to scsi.c, but&n; &t; * scsi.c is initialized before the memory manager is set up.&n; &t; * So we add it here too.  There is a duplicate set in scsi.c&n; &t; * that is used when the entire scsi subsystem is a loadable&n; &t; * module.&n;&t; */
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
id|scsi_mark_host_bus_reset
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
id|X
c_func
(paren
id|generic_proc_info
)paren
comma
id|X
c_func
(paren
id|scsi_devices
)paren
comma
id|X
c_func
(paren
id|gendisk_head
)paren
comma
multiline_comment|/* Needed for sd.c */
id|X
c_func
(paren
id|resetup_one_dev
)paren
comma
multiline_comment|/* Needed for sd.c */
macro_line|#if defined(CONFIG_PROC_FS)
id|X
c_func
(paren
id|proc_print_scsidevice
)paren
comma
macro_line|#endif
macro_line|#else
multiline_comment|/*&n;&t; * With no scsi configured, we still need to export a few&n;&t; * symbols so that scsi can be loaded later via insmod.&n;&t; */
id|X
c_func
(paren
id|gendisk_head
)paren
comma
id|X
c_func
(paren
id|resetup_one_dev
)paren
comma
macro_line|#endif
multiline_comment|/* Added to make file system as module */
id|X
c_func
(paren
id|set_writetime
)paren
comma
id|X
c_func
(paren
id|sys_tz
)paren
comma
id|X
c_func
(paren
id|__wait_on_super
)paren
comma
id|X
c_func
(paren
id|file_fsync
)paren
comma
id|X
c_func
(paren
id|clear_inode
)paren
comma
id|X
c_func
(paren
id|refile_buffer
)paren
comma
id|X
c_func
(paren
id|___strtok
)paren
comma
id|X
c_func
(paren
id|init_fifo
)paren
comma
id|X
c_func
(paren
id|super_blocks
)paren
comma
id|X
c_func
(paren
id|chrdev_inode_operations
)paren
comma
id|X
c_func
(paren
id|blkdev_inode_operations
)paren
comma
id|X
c_func
(paren
id|read_ahead
)paren
comma
id|X
c_func
(paren
id|get_hash_table
)paren
comma
id|X
c_func
(paren
id|get_empty_inode
)paren
comma
id|X
c_func
(paren
id|insert_inode_hash
)paren
comma
id|X
c_func
(paren
id|event
)paren
comma
id|X
c_func
(paren
id|__down
)paren
comma
macro_line|#if defined(CONFIG_MSDOS_FS) &amp;&amp; !defined(CONFIG_UMSDOS_FS)
multiline_comment|/* support for umsdos fs */
id|X
c_func
(paren
id|msdos_bmap
)paren
comma
id|X
c_func
(paren
id|msdos_create
)paren
comma
id|X
c_func
(paren
id|msdos_file_read
)paren
comma
id|X
c_func
(paren
id|msdos_file_write
)paren
comma
id|X
c_func
(paren
id|msdos_lookup
)paren
comma
id|X
c_func
(paren
id|msdos_mkdir
)paren
comma
id|X
c_func
(paren
id|msdos_mmap
)paren
comma
id|X
c_func
(paren
id|msdos_put_inode
)paren
comma
id|X
c_func
(paren
id|msdos_put_super
)paren
comma
id|X
c_func
(paren
id|msdos_read_inode
)paren
comma
id|X
c_func
(paren
id|msdos_read_super
)paren
comma
id|X
c_func
(paren
id|msdos_readdir
)paren
comma
id|X
c_func
(paren
id|msdos_rename
)paren
comma
id|X
c_func
(paren
id|msdos_rmdir
)paren
comma
id|X
c_func
(paren
id|msdos_smap
)paren
comma
id|X
c_func
(paren
id|msdos_statfs
)paren
comma
id|X
c_func
(paren
id|msdos_truncate
)paren
comma
id|X
c_func
(paren
id|msdos_unlink
)paren
comma
id|X
c_func
(paren
id|msdos_unlink_umsdos
)paren
comma
id|X
c_func
(paren
id|msdos_write_inode
)paren
comma
macro_line|#endif
macro_line|#ifdef CONFIG_PROC_FS
id|X
c_func
(paren
id|proc_register
)paren
comma
id|X
c_func
(paren
id|proc_unregister
)paren
comma
id|X
c_func
(paren
id|in_group_p
)paren
comma
id|X
c_func
(paren
id|generate_cluster
)paren
comma
macro_line|#ifdef CONFIG_SCSI
id|X
c_func
(paren
id|proc_scsi
)paren
comma
id|X
c_func
(paren
id|proc_scsi_inode_operations
)paren
comma
macro_line|#endif
id|X
c_func
(paren
id|proc_net_inode_operations
)paren
comma
id|X
c_func
(paren
id|proc_net
)paren
comma
macro_line|#endif
multiline_comment|/* all busmice */
id|X
c_func
(paren
id|add_mouse_randomness
)paren
comma
id|X
c_func
(paren
id|fasync_helper
)paren
comma
multiline_comment|/* psaux mouse */
id|X
c_func
(paren
id|aux_device_present
)paren
comma
id|X
c_func
(paren
id|kbd_read_mask
)paren
comma
macro_line|#ifdef CONFIG_TR
id|X
c_func
(paren
id|tr_setup
)paren
comma
id|X
c_func
(paren
id|tr_type_trans
)paren
comma
macro_line|#endif
macro_line|#ifdef CONFIG_BINFMT_ELF
id|X
c_func
(paren
id|dump_fpu
)paren
comma
macro_line|#endif
multiline_comment|/********************************************************&n;&t; * Do not add anything below this line,&n;&t; * as the stacked modules depend on this!&n;&t; */
macro_line|#include &lt;linux/symtab_end.h&gt;
)brace
suffix:semicolon
multiline_comment|/*&n;int symbol_table_size = sizeof (symbol_table) / sizeof (symbol_table[0]);&n;*/
eof
