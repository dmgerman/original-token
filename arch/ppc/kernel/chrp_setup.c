multiline_comment|/*&n; *  linux/arch/ppc/kernel/setup.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *  Adapted from &squot;alpha&squot; version by Gary Thomas&n; *  Modified by Cort Dougan (cort@cs.nmt.edu)&n; */
multiline_comment|/*&n; * bootup setup stuff..&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/openpic.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/adb.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/gg2.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hydra.h&gt;
macro_line|#include &lt;asm/keyboard.h&gt;
macro_line|#include &quot;time.h&quot;
macro_line|#include &quot;local_irq.h&quot;
macro_line|#include &quot;i8259.h&quot;
macro_line|#include &quot;open_pic.h&quot;
r_extern
r_volatile
r_int
r_char
op_star
id|chrp_int_ack_special
suffix:semicolon
r_int
r_int
id|chrp_get_rtc_time
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|chrp_set_rtc_time
c_func
(paren
r_int
r_int
id|nowtime
)paren
suffix:semicolon
r_void
id|chrp_calibrate_decr
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|chrp_time_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|chrp_setup_pci_ptrs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|chrp_progress
c_func
(paren
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|chrp_event_scan
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pckbd_setkeycode
c_func
(paren
r_int
r_int
id|scancode
comma
r_int
r_int
id|keycode
)paren
suffix:semicolon
r_extern
r_int
id|pckbd_getkeycode
c_func
(paren
r_int
r_int
id|scancode
)paren
suffix:semicolon
r_extern
r_int
id|pckbd_translate
c_func
(paren
r_int
r_char
id|scancode
comma
r_int
r_char
op_star
id|keycode
comma
r_char
id|raw_mode
)paren
suffix:semicolon
r_extern
r_char
id|pckbd_unexpected_up
c_func
(paren
r_int
r_char
id|keycode
)paren
suffix:semicolon
r_extern
r_void
id|pckbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
suffix:semicolon
r_extern
r_void
id|pckbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|pckbd_sysrq_xlate
(braket
l_int|128
)braket
suffix:semicolon
r_extern
r_int
id|mackbd_setkeycode
c_func
(paren
r_int
r_int
id|scancode
comma
r_int
r_int
id|keycode
)paren
suffix:semicolon
r_extern
r_int
id|mackbd_getkeycode
c_func
(paren
r_int
r_int
id|scancode
)paren
suffix:semicolon
r_extern
r_int
id|mackbd_translate
c_func
(paren
r_int
r_char
id|scancode
comma
r_int
r_char
op_star
id|keycode
comma
r_char
id|raw_mode
)paren
suffix:semicolon
r_extern
r_char
id|mackbd_unexpected_up
c_func
(paren
r_int
r_char
id|keycode
)paren
suffix:semicolon
r_extern
r_void
id|mackbd_leds
c_func
(paren
r_int
r_char
id|leds
)paren
suffix:semicolon
r_extern
r_void
id|mackbd_init_hw
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_char
id|mackbd_sysrq_xlate
(braket
l_int|128
)braket
suffix:semicolon
DECL|variable|boot_dev
id|kdev_t
id|boot_dev
suffix:semicolon
r_extern
id|PTE
op_star
id|Hash
comma
op_star
id|Hash_end
suffix:semicolon
r_extern
r_int
r_int
id|Hash_size
comma
id|Hash_mask
suffix:semicolon
r_extern
r_int
id|probingmem
suffix:semicolon
r_extern
r_int
r_int
id|loops_per_sec
suffix:semicolon
DECL|variable|empty_zero_page
r_int
r_int
id|empty_zero_page
(braket
l_int|1024
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_RAM
r_extern
r_int
id|rd_doload
suffix:semicolon
multiline_comment|/* 1 = load ramdisk, 0 = don&squot;t load */
r_extern
r_int
id|rd_prompt
suffix:semicolon
multiline_comment|/* 1 = prompt for ramdisk, 0 = don&squot;t prompt */
r_extern
r_int
id|rd_image_start
suffix:semicolon
multiline_comment|/* starting block # of image */
macro_line|#endif
DECL|variable|gg2_memtypes
r_static
r_const
r_char
op_star
id|gg2_memtypes
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot;FPM&quot;
comma
l_string|&quot;SDRAM&quot;
comma
l_string|&quot;EDO&quot;
comma
l_string|&quot;BEDO&quot;
)brace
suffix:semicolon
DECL|variable|gg2_cachesizes
r_static
r_const
r_char
op_star
id|gg2_cachesizes
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot;256 KB&quot;
comma
l_string|&quot;512 KB&quot;
comma
l_string|&quot;1 MB&quot;
comma
l_string|&quot;Reserved&quot;
)brace
suffix:semicolon
DECL|variable|gg2_cachetypes
r_static
r_const
r_char
op_star
id|gg2_cachetypes
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot;Asynchronous&quot;
comma
l_string|&quot;Reserved&quot;
comma
l_string|&quot;Flow-Through Synchronous&quot;
comma
l_string|&quot;Pipelined Synchronous&quot;
)brace
suffix:semicolon
DECL|variable|gg2_cachemodes
r_static
r_const
r_char
op_star
id|gg2_cachemodes
(braket
l_int|4
)braket
op_assign
(brace
l_string|&quot;Disabled&quot;
comma
l_string|&quot;Write-Through&quot;
comma
l_string|&quot;Copy-Back&quot;
comma
l_string|&quot;Transparent Mode&quot;
)brace
suffix:semicolon
r_int
DECL|function|chrp_get_cpuinfo
id|chrp_get_cpuinfo
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
r_int
id|i
comma
id|len
comma
id|sdramen
suffix:semicolon
r_int
r_int
id|t
suffix:semicolon
r_struct
id|device_node
op_star
id|root
suffix:semicolon
r_const
r_char
op_star
id|model
op_assign
l_string|&quot;&quot;
suffix:semicolon
id|root
op_assign
id|find_path_device
c_func
(paren
l_string|&quot;/&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|root
)paren
id|model
op_assign
id|get_property
c_func
(paren
id|root
comma
l_string|&quot;model&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;machine&bslash;t&bslash;t: CHRP %s&bslash;n&quot;
comma
id|model
)paren
suffix:semicolon
multiline_comment|/* longtrail (goldengate) stuff */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|model
comma
l_string|&quot;IBM,LongTrail&quot;
comma
l_int|13
)paren
)paren
(brace
multiline_comment|/* VLSI VAS96011/12 `Golden Gate 2&squot; */
multiline_comment|/* Memory banks */
id|sdramen
op_assign
(paren
id|in_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|GG2_PCI_CONFIG_BASE
op_plus
id|GG2_PCI_DRAM_CTRL
)paren
)paren
op_rshift
l_int|31
)paren
op_amp
l_int|1
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
(paren
id|sdramen
ques
c_cond
l_int|4
suffix:colon
l_int|6
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|t
op_assign
id|in_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|GG2_PCI_CONFIG_BASE
op_plus
id|GG2_PCI_DRAM_BANK0
op_plus
id|i
op_star
l_int|4
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|t
op_amp
l_int|1
)paren
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|t
op_rshift
l_int|8
)paren
op_amp
l_int|0x1f
)paren
(brace
r_case
l_int|0x1f
suffix:colon
id|model
op_assign
l_string|&quot;4 MB&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x1e
suffix:colon
id|model
op_assign
l_string|&quot;8 MB&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x1c
suffix:colon
id|model
op_assign
l_string|&quot;16 MB&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x18
suffix:colon
id|model
op_assign
l_string|&quot;32 MB&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x10
suffix:colon
id|model
op_assign
l_string|&quot;64 MB&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x00
suffix:colon
id|model
op_assign
l_string|&quot;128 MB&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|model
op_assign
l_string|&quot;Reserved&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;memory bank %d&bslash;t: %s %s&bslash;n&quot;
comma
id|i
comma
id|model
comma
id|gg2_memtypes
(braket
id|sdramen
ques
c_cond
l_int|1
suffix:colon
(paren
(paren
id|t
op_rshift
l_int|1
)paren
op_amp
l_int|3
)paren
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* L2 cache */
id|t
op_assign
id|in_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|GG2_PCI_CONFIG_BASE
op_plus
id|GG2_PCI_CC_CTRL
)paren
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;board l2&bslash;t: %s %s (%s)&bslash;n&quot;
comma
id|gg2_cachesizes
(braket
(paren
id|t
op_rshift
l_int|7
)paren
op_amp
l_int|3
)braket
comma
id|gg2_cachetypes
(braket
(paren
id|t
op_rshift
l_int|2
)paren
op_amp
l_int|3
)braket
comma
id|gg2_cachemodes
(braket
id|t
op_amp
l_int|3
)braket
)paren
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; *  Fixes for the National Semiconductor PC78308VUL SuperI/O&n; *&n; *  Some versions of Open Firmware incorrectly initialize the IRQ settings&n; *  for keyboard and mouse&n; */
DECL|function|sio_write
r_static
r_inline
r_void
id|__init
id|sio_write
c_func
(paren
id|u8
id|val
comma
id|u8
id|index
)paren
(brace
id|outb
c_func
(paren
id|index
comma
l_int|0x15c
)paren
suffix:semicolon
id|outb
c_func
(paren
id|val
comma
l_int|0x15d
)paren
suffix:semicolon
)brace
DECL|function|sio_read
r_static
r_inline
id|u8
id|__init
id|sio_read
c_func
(paren
id|u8
id|index
)paren
(brace
id|outb
c_func
(paren
id|index
comma
l_int|0x15c
)paren
suffix:semicolon
r_return
id|inb
c_func
(paren
l_int|0x15d
)paren
suffix:semicolon
)brace
DECL|function|sio_fixup_irq
r_static
r_void
id|__init
id|sio_fixup_irq
c_func
(paren
r_const
r_char
op_star
id|name
comma
id|u8
id|device
comma
id|u8
id|level
comma
id|u8
id|type
)paren
(brace
id|u8
id|level0
comma
id|type0
comma
id|active
suffix:semicolon
r_struct
id|device_node
op_star
id|root
suffix:semicolon
id|root
op_assign
id|find_path_device
c_func
(paren
l_string|&quot;/&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|root
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|get_property
c_func
(paren
id|root
comma
l_string|&quot;model&quot;
comma
l_int|NULL
)paren
comma
l_string|&quot;IBM,LongTrail&quot;
comma
l_int|13
)paren
)paren
(brace
multiline_comment|/* select logical device */
id|sio_write
c_func
(paren
id|device
comma
l_int|0x07
)paren
suffix:semicolon
id|active
op_assign
id|sio_read
c_func
(paren
l_int|0x30
)paren
suffix:semicolon
id|level0
op_assign
id|sio_read
c_func
(paren
l_int|0x70
)paren
suffix:semicolon
id|type0
op_assign
id|sio_read
c_func
(paren
l_int|0x71
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sio: %s irq level %d, type %d, %sactive: &quot;
comma
id|name
comma
id|level0
comma
id|type0
comma
op_logical_neg
id|active
ques
c_cond
l_string|&quot;in&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|level0
op_eq
id|level
op_logical_and
id|type0
op_eq
id|type
op_logical_and
id|active
)paren
id|printk
c_func
(paren
l_string|&quot;OK&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;remapping to level %d, type %d, active&bslash;n&quot;
comma
id|level
comma
id|type
)paren
suffix:semicolon
id|sio_write
c_func
(paren
l_int|0x01
comma
l_int|0x30
)paren
suffix:semicolon
id|sio_write
c_func
(paren
id|level
comma
l_int|0x70
)paren
suffix:semicolon
id|sio_write
c_func
(paren
id|type
comma
l_int|0x71
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|sio_init
r_static
r_void
id|__init
id|sio_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* logical device 0 (KBC/Keyboard) */
id|sio_fixup_irq
c_func
(paren
l_string|&quot;keyboard&quot;
comma
l_int|0
comma
l_int|1
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* select logical device 1 (KBC/Mouse) */
id|sio_fixup_irq
c_func
(paren
l_string|&quot;mouse&quot;
comma
l_int|1
comma
l_int|12
comma
l_int|2
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|chrp_setup_arch
id|chrp_setup_arch
c_func
(paren
r_void
)paren
(brace
r_extern
r_char
id|cmd_line
(braket
)braket
suffix:semicolon
r_struct
id|device_node
op_star
id|device
suffix:semicolon
multiline_comment|/* init to some ~sane value until calibrate_delay() runs */
id|loops_per_sec
op_assign
l_int|50000000
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
multiline_comment|/* this is fine for chrp */
id|initrd_below_start_ok
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|initrd_start
)paren
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
r_else
macro_line|#endif
id|ROOT_DEV
op_assign
id|to_kdev_t
c_func
(paren
l_int|0x0802
)paren
suffix:semicolon
multiline_comment|/* sda2 (sda1 is for the kernel) */
id|printk
c_func
(paren
l_string|&quot;Boot arguments: %s&bslash;n&quot;
comma
id|cmd_line
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x20
comma
l_int|0x20
comma
l_string|&quot;pic1&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0xa0
comma
l_int|0x20
comma
l_string|&quot;pic2&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x00
comma
l_int|0x20
comma
l_string|&quot;dma1&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x40
comma
l_int|0x20
comma
l_string|&quot;timer&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x80
comma
l_int|0x10
comma
l_string|&quot;dma page reg&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0xc0
comma
l_int|0x20
comma
l_string|&quot;dma2&quot;
)paren
suffix:semicolon
multiline_comment|/* PCI bridge config space access area -&n;&t; * appears to be not in devtree on longtrail. */
id|ioremap
c_func
(paren
id|GG2_PCI_CONFIG_BASE
comma
l_int|0x80000
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *  Temporary fixes for PCI devices.&n;&t; *  -- Geert&n;&t; */
id|hydra_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Mac I/O */
multiline_comment|/* Some IBM machines don&squot;t have the hydra -- Cort */
r_if
c_cond
(paren
op_logical_neg
id|OpenPIC
)paren
(brace
id|OpenPIC
op_assign
(paren
r_struct
id|OpenPIC
op_star
)paren
op_star
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|find_path_device
c_func
(paren
l_string|&quot;/&quot;
)paren
comma
l_string|&quot;platform-open-pic&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|OpenPIC
op_assign
id|ioremap
c_func
(paren
(paren
r_int
r_int
)paren
id|OpenPIC
comma
r_sizeof
(paren
r_struct
id|OpenPIC
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *  Fix the Super I/O configuration&n;&t; */
id|sio_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DUMMY_CONSOLE
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
id|pmac_find_bridges
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Get the event scan rate for the rtas so we know how&n;&t; * often it expects a heartbeat. -- Cort&n;&t; */
r_if
c_cond
(paren
id|rtas_data
)paren
(brace
r_struct
id|property
op_star
id|p
suffix:semicolon
id|device
op_assign
id|find_devices
c_func
(paren
l_string|&quot;rtas&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|device-&gt;properties
suffix:semicolon
id|p
op_logical_and
id|strncmp
c_func
(paren
id|p-&gt;name
comma
l_string|&quot;rtas-event-scan-rate&quot;
comma
l_int|20
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
multiline_comment|/* nothing */
suffix:semicolon
r_if
c_cond
(paren
id|p
op_logical_and
op_star
(paren
r_int
r_int
op_star
)paren
id|p-&gt;value
)paren
(brace
id|ppc_md.heartbeat
op_assign
id|chrp_event_scan
suffix:semicolon
id|ppc_md.heartbeat_reset
op_assign
(paren
id|HZ
op_div
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|p-&gt;value
)paren
op_star
l_int|30
)paren
op_minus
l_int|1
suffix:semicolon
id|ppc_md.heartbeat_count
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;RTAS Event Scan Rate: %lu (%lu jiffies)&bslash;n&quot;
comma
op_star
(paren
r_int
r_int
op_star
)paren
id|p-&gt;value
comma
id|ppc_md.heartbeat_reset
)paren
suffix:semicolon
)brace
)brace
)brace
r_void
DECL|function|chrp_event_scan
id|chrp_event_scan
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|log
(braket
l_int|1024
)braket
suffix:semicolon
r_int
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* XXX: we should loop until the hardware says no more error logs -- Cort */
id|call_rtas
c_func
(paren
l_string|&quot;event-scan&quot;
comma
l_int|4
comma
l_int|1
comma
op_amp
id|ret
comma
l_int|0xffffffff
comma
l_int|0
comma
id|__pa
c_func
(paren
id|log
)paren
comma
l_int|1024
)paren
suffix:semicolon
id|ppc_md.heartbeat_count
op_assign
id|ppc_md.heartbeat_reset
suffix:semicolon
)brace
r_void
DECL|function|chrp_restart
id|chrp_restart
c_func
(paren
r_char
op_star
id|cmd
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;RTAS system-reboot returned %d&bslash;n&quot;
comma
id|call_rtas
c_func
(paren
l_string|&quot;system-reboot&quot;
comma
l_int|0
comma
l_int|1
comma
l_int|NULL
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
r_void
DECL|function|chrp_power_off
id|chrp_power_off
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* allow power on only with power button press */
id|printk
c_func
(paren
l_string|&quot;RTAS power-off returned %d&bslash;n&quot;
comma
id|call_rtas
c_func
(paren
l_string|&quot;power-off&quot;
comma
l_int|2
comma
l_int|1
comma
l_int|NULL
comma
l_int|0xffffffff
comma
l_int|0xffffffff
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
r_void
DECL|function|chrp_halt
id|chrp_halt
c_func
(paren
r_void
)paren
(brace
id|chrp_power_off
c_func
(paren
)paren
suffix:semicolon
)brace
id|u_int
DECL|function|chrp_irq_cannonicalize
id|chrp_irq_cannonicalize
c_func
(paren
id|u_int
id|irq
)paren
(brace
r_if
c_cond
(paren
id|irq
op_eq
l_int|2
)paren
(brace
r_return
l_int|9
suffix:semicolon
)brace
r_else
(brace
r_return
id|irq
suffix:semicolon
)brace
)brace
DECL|function|chrp_get_irq
r_int
id|chrp_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|irq
suffix:semicolon
id|irq
op_assign
id|openpic_irq
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
id|IRQ_8259_CASCADE
)paren
(brace
multiline_comment|/*&n;                 * This magic address generates a PCI IACK cycle.&n;                 */
r_if
c_cond
(paren
id|chrp_int_ack_special
)paren
id|irq
op_assign
op_star
id|chrp_int_ack_special
suffix:semicolon
r_else
id|irq
op_assign
id|i8259_irq
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|openpic_eoi
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
op_eq
id|OPENPIC_VEC_SPURIOUS
)paren
multiline_comment|/*&n;                 * Spurious interrupts should never be&n;                 * acknowledged&n;                 */
id|irq
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * I would like to openpic_eoi here but there seem to be timing problems&n;&t; * between the openpic ack and the openpic eoi.&n;&t; *   -- Cort&n;&t; */
r_return
id|irq
suffix:semicolon
)brace
DECL|function|chrp_post_irq
r_void
id|chrp_post_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|irq
)paren
(brace
multiline_comment|/*&n;&t; * If it&squot;s an i8259 irq then we&squot;ve already done the&n;&t; * openpic irq.  So we just check to make sure the controller&n;&t; * is an openpic and if it is then eoi&n;&t; *&n;&t; * We do it this way since our irq_desc[irq].handler can change&n;&t; * with RTL and no longer be open_pic -- Cort&n;&t; */
r_if
c_cond
(paren
id|irq
op_ge
id|open_pic_irq_offset
)paren
id|openpic_eoi
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|chrp_init_IRQ
r_void
id|__init
id|chrp_init_IRQ
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|np
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|np
op_assign
id|find_devices
c_func
(paren
l_string|&quot;pci&quot;
)paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Cannot find pci to get ack address&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|chrp_int_ack_special
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
(paren
op_star
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|np
comma
l_string|&quot;8259-interrupt-acknowledge&quot;
comma
l_int|NULL
)paren
)paren
suffix:semicolon
)brace
id|open_pic_irq_offset
op_assign
l_int|16
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|16
suffix:semicolon
id|i
OL
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|open_pic
suffix:semicolon
id|openpic_init
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|enable_irq
c_func
(paren
id|IRQ_8259_CASCADE
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|i8259_pic
suffix:semicolon
id|i8259_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_XMON
id|request_irq
c_func
(paren
id|openpic_to_irq
c_func
(paren
id|HYDRA_INT_ADB_NMI
)paren
comma
id|xmon_irq
comma
l_int|0
comma
l_string|&quot;NMI&quot;
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif&t;/* CONFIG_XMON */
macro_line|#ifdef __SMP__
id|request_irq
c_func
(paren
id|openpic_to_irq
c_func
(paren
id|OPENPIC_VEC_IPI
)paren
comma
id|openpic_ipi_action
comma
l_int|0
comma
l_string|&quot;IPI0&quot;
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif&t;/* __SMP__ */
)brace
r_void
id|__init
DECL|function|chrp_init2
id|chrp_init2
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_NVRAM  
id|pmac_nvram_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_IDE_MODULE)
multiline_comment|/*&n; * IDE stuff.&n; */
DECL|variable|chrp_ide_irq
r_int
r_int
id|chrp_ide_irq
op_assign
l_int|0
suffix:semicolon
DECL|variable|chrp_ide_ports_known
r_int
id|chrp_ide_ports_known
op_assign
l_int|0
suffix:semicolon
DECL|variable|chrp_ide_regbase
id|ide_ioreg_t
id|chrp_ide_regbase
(braket
id|MAX_HWIFS
)braket
suffix:semicolon
DECL|variable|chrp_idedma_regbase
id|ide_ioreg_t
id|chrp_idedma_regbase
suffix:semicolon
r_void
DECL|function|chrp_ide_probe
id|chrp_ide_probe
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|pdev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_WINBOND
comma
id|PCI_DEVICE_ID_WINBOND_82C105
comma
l_int|NULL
)paren
suffix:semicolon
id|chrp_ide_ports_known
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|pdev
)paren
(brace
id|chrp_ide_regbase
(braket
l_int|0
)braket
op_assign
id|pdev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|chrp_ide_regbase
(braket
l_int|1
)braket
op_assign
id|pdev-&gt;resource
(braket
l_int|2
)braket
dot
id|start
suffix:semicolon
id|chrp_idedma_regbase
op_assign
id|pdev-&gt;resource
(braket
l_int|4
)braket
dot
id|start
suffix:semicolon
id|chrp_ide_irq
op_assign
id|pdev-&gt;irq
suffix:semicolon
)brace
)brace
r_void
DECL|function|chrp_ide_insw
id|chrp_ide_insw
c_func
(paren
id|ide_ioreg_t
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
(brace
id|ide_insw
c_func
(paren
id|port
op_plus
id|_IO_BASE
comma
id|buf
comma
id|ns
)paren
suffix:semicolon
)brace
r_void
DECL|function|chrp_ide_outsw
id|chrp_ide_outsw
c_func
(paren
id|ide_ioreg_t
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
(brace
id|ide_outsw
c_func
(paren
id|port
op_plus
id|_IO_BASE
comma
id|buf
comma
id|ns
)paren
suffix:semicolon
)brace
r_int
DECL|function|chrp_ide_default_irq
id|chrp_ide_default_irq
c_func
(paren
id|ide_ioreg_t
id|base
)paren
(brace
r_if
c_cond
(paren
id|chrp_ide_ports_known
op_eq
l_int|0
)paren
id|chrp_ide_probe
c_func
(paren
)paren
suffix:semicolon
r_return
id|chrp_ide_irq
suffix:semicolon
)brace
id|ide_ioreg_t
DECL|function|chrp_ide_default_io_base
id|chrp_ide_default_io_base
c_func
(paren
r_int
id|index
)paren
(brace
r_if
c_cond
(paren
id|chrp_ide_ports_known
op_eq
l_int|0
)paren
id|chrp_ide_probe
c_func
(paren
)paren
suffix:semicolon
r_return
id|chrp_ide_regbase
(braket
id|index
)braket
suffix:semicolon
)brace
r_int
DECL|function|chrp_ide_check_region
id|chrp_ide_check_region
c_func
(paren
id|ide_ioreg_t
id|from
comma
r_int
r_int
id|extent
)paren
(brace
r_return
id|check_region
c_func
(paren
id|from
comma
id|extent
)paren
suffix:semicolon
)brace
r_void
DECL|function|chrp_ide_request_region
id|chrp_ide_request_region
c_func
(paren
id|ide_ioreg_t
id|from
comma
r_int
r_int
id|extent
comma
r_const
r_char
op_star
id|name
)paren
(brace
id|request_region
c_func
(paren
id|from
comma
id|extent
comma
id|name
)paren
suffix:semicolon
)brace
r_void
DECL|function|chrp_ide_release_region
id|chrp_ide_release_region
c_func
(paren
id|ide_ioreg_t
id|from
comma
r_int
r_int
id|extent
)paren
(brace
id|release_region
c_func
(paren
id|from
comma
id|extent
)paren
suffix:semicolon
)brace
r_void
DECL|function|chrp_ide_fix_driveid
id|chrp_ide_fix_driveid
c_func
(paren
r_struct
id|hd_driveid
op_star
id|id
)paren
(brace
id|ppc_generic_ide_fix_driveid
c_func
(paren
id|id
)paren
suffix:semicolon
)brace
r_void
DECL|function|chrp_ide_init_hwif_ports
id|chrp_ide_init_hwif_ports
c_func
(paren
id|hw_regs_t
op_star
id|hw
comma
id|ide_ioreg_t
id|data_port
comma
id|ide_ioreg_t
id|ctrl_port
comma
r_int
op_star
id|irq
)paren
(brace
id|ide_ioreg_t
id|reg
op_assign
id|data_port
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|IDE_DATA_OFFSET
suffix:semicolon
id|i
op_le
id|IDE_STATUS_OFFSET
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hw-&gt;io_ports
(braket
id|i
)braket
op_assign
id|reg
suffix:semicolon
id|reg
op_add_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ctrl_port
)paren
(brace
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
id|ctrl_port
suffix:semicolon
)brace
r_else
(brace
id|hw-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
op_ne
l_int|NULL
)paren
id|hw-&gt;irq
op_assign
id|chrp_ide_irq
suffix:semicolon
)brace
macro_line|#endif
r_void
id|__init
DECL|function|chrp_init
id|chrp_init
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
)paren
(brace
id|chrp_setup_pci_ptrs
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
multiline_comment|/* take care of initrd if we have one */
r_if
c_cond
(paren
id|r6
)paren
(brace
id|initrd_start
op_assign
id|r6
op_plus
id|KERNELBASE
suffix:semicolon
id|initrd_end
op_assign
id|r6
op_plus
id|r7
op_plus
id|KERNELBASE
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_BLK_DEV_INITRD */
multiline_comment|/* pci_dram_offset/isa_io_base/isa_mem_base set by setup_pci_ptrs() */
id|ISA_DMA_THRESHOLD
op_assign
op_complement
l_int|0L
suffix:semicolon
id|DMA_MODE_READ
op_assign
l_int|0x44
suffix:semicolon
id|DMA_MODE_WRITE
op_assign
l_int|0x48
suffix:semicolon
id|ppc_md.setup_arch
op_assign
id|chrp_setup_arch
suffix:semicolon
id|ppc_md.setup_residual
op_assign
l_int|NULL
suffix:semicolon
id|ppc_md.get_cpuinfo
op_assign
id|chrp_get_cpuinfo
suffix:semicolon
id|ppc_md.irq_cannonicalize
op_assign
id|chrp_irq_cannonicalize
suffix:semicolon
id|ppc_md.init_IRQ
op_assign
id|chrp_init_IRQ
suffix:semicolon
id|ppc_md.get_irq
op_assign
id|chrp_get_irq
suffix:semicolon
id|ppc_md.post_irq
op_assign
id|chrp_post_irq
suffix:semicolon
id|ppc_md.init
op_assign
id|chrp_init2
suffix:semicolon
id|ppc_md.restart
op_assign
id|chrp_restart
suffix:semicolon
id|ppc_md.power_off
op_assign
id|chrp_power_off
suffix:semicolon
id|ppc_md.halt
op_assign
id|chrp_halt
suffix:semicolon
id|ppc_md.time_init
op_assign
id|chrp_time_init
suffix:semicolon
id|ppc_md.set_rtc_time
op_assign
id|chrp_set_rtc_time
suffix:semicolon
id|ppc_md.get_rtc_time
op_assign
id|chrp_get_rtc_time
suffix:semicolon
id|ppc_md.calibrate_decr
op_assign
id|chrp_calibrate_decr
suffix:semicolon
macro_line|#ifdef CONFIG_VT
macro_line|#ifdef CONFIG_MAC_KEYBOARD
r_if
c_cond
(paren
id|adb_driver
op_eq
l_int|NULL
)paren
(brace
macro_line|#endif /* CONFIG_MAC_KEYBOAD */
id|ppc_md.kbd_setkeycode
op_assign
id|pckbd_setkeycode
suffix:semicolon
id|ppc_md.kbd_getkeycode
op_assign
id|pckbd_getkeycode
suffix:semicolon
id|ppc_md.kbd_translate
op_assign
id|pckbd_translate
suffix:semicolon
id|ppc_md.kbd_unexpected_up
op_assign
id|pckbd_unexpected_up
suffix:semicolon
id|ppc_md.kbd_leds
op_assign
id|pckbd_leds
suffix:semicolon
id|ppc_md.kbd_init_hw
op_assign
id|pckbd_init_hw
suffix:semicolon
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
id|ppc_md.ppc_kbd_sysrq_xlate
op_assign
id|pckbd_sysrq_xlate
suffix:semicolon
id|SYSRQ_KEY
op_assign
l_int|0x54
suffix:semicolon
macro_line|#endif /* CONFIG_MAGIC_SYSRQ */
macro_line|#ifdef CONFIG_MAC_KEYBOARD
)brace
r_else
(brace
id|ppc_md.kbd_setkeycode
op_assign
id|mackbd_setkeycode
suffix:semicolon
id|ppc_md.kbd_getkeycode
op_assign
id|mackbd_getkeycode
suffix:semicolon
id|ppc_md.kbd_translate
op_assign
id|mackbd_translate
suffix:semicolon
id|ppc_md.kbd_unexpected_up
op_assign
id|mackbd_unexpected_up
suffix:semicolon
id|ppc_md.kbd_leds
op_assign
id|mackbd_leds
suffix:semicolon
id|ppc_md.kbd_init_hw
op_assign
id|mackbd_init_hw
suffix:semicolon
macro_line|#ifdef CONFIG_MAGIC_SYSRQ
id|ppc_md.ppc_kbd_sysrq_xlate
op_assign
id|mackbd_sysrq_xlate
suffix:semicolon
id|SYSRQ_KEY
op_assign
l_int|0x69
suffix:semicolon
macro_line|#endif /* CONFIG_MAGIC_SYSRQ */
)brace
macro_line|#endif /* CONFIG_MAC_KEYBOARD */
macro_line|#endif /* CONFIG_VT */
r_if
c_cond
(paren
id|rtas_data
)paren
id|ppc_md.progress
op_assign
id|chrp_progress
suffix:semicolon
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_IDE_MODULE)
id|ppc_ide_md.insw
op_assign
id|chrp_ide_insw
suffix:semicolon
id|ppc_ide_md.outsw
op_assign
id|chrp_ide_outsw
suffix:semicolon
id|ppc_ide_md.default_irq
op_assign
id|chrp_ide_default_irq
suffix:semicolon
id|ppc_ide_md.default_io_base
op_assign
id|chrp_ide_default_io_base
suffix:semicolon
id|ppc_ide_md.ide_check_region
op_assign
id|chrp_ide_check_region
suffix:semicolon
id|ppc_ide_md.ide_request_region
op_assign
id|chrp_ide_request_region
suffix:semicolon
id|ppc_ide_md.ide_release_region
op_assign
id|chrp_ide_release_region
suffix:semicolon
id|ppc_ide_md.fix_driveid
op_assign
id|chrp_ide_fix_driveid
suffix:semicolon
id|ppc_ide_md.ide_init_hwif
op_assign
id|chrp_ide_init_hwif_ports
suffix:semicolon
id|ppc_ide_md.io_base
op_assign
id|_IO_BASE
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Print the banner, then scroll down so boot progress&n;&t; * can be printed.  -- Cort &n;&t; */
r_if
c_cond
(paren
id|ppc_md.progress
)paren
id|ppc_md
dot
id|progress
c_func
(paren
l_string|&quot;Linux/PPC &quot;
id|UTS_RELEASE
l_string|&quot;&bslash;n&quot;
comma
l_int|0x0
)paren
suffix:semicolon
)brace
r_void
DECL|function|chrp_progress
id|chrp_progress
c_func
(paren
r_char
op_star
id|s
comma
r_int
r_int
id|hex
)paren
(brace
r_extern
r_int
r_int
id|rtas_data
suffix:semicolon
r_int
id|max_width
comma
id|width
suffix:semicolon
r_struct
id|device_node
op_star
id|root
suffix:semicolon
r_char
op_star
id|os
op_assign
id|s
suffix:semicolon
r_int
r_int
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
(paren
id|root
op_assign
id|find_path_device
c_func
(paren
l_string|&quot;/rtas&quot;
)paren
)paren
op_logical_and
(paren
id|p
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|root
comma
l_string|&quot;ibm,display-line-length&quot;
comma
l_int|NULL
)paren
)paren
)paren
id|max_width
op_assign
op_star
id|p
suffix:semicolon
r_else
id|max_width
op_assign
l_int|0x10
suffix:semicolon
r_if
c_cond
(paren
(paren
id|_machine
op_ne
id|_MACH_chrp
)paren
op_logical_or
op_logical_neg
id|rtas_data
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|call_rtas
c_func
(paren
l_string|&quot;display-character&quot;
comma
l_int|1
comma
l_int|1
comma
l_int|NULL
comma
l_char|&squot;&bslash;r&squot;
)paren
)paren
(brace
multiline_comment|/* assume no display-character RTAS method - use hex display */
r_return
suffix:semicolon
)brace
id|width
op_assign
id|max_width
suffix:semicolon
r_while
c_loop
(paren
op_star
id|os
)paren
(brace
r_if
c_cond
(paren
(paren
op_star
id|os
op_eq
l_char|&squot;&bslash;n&squot;
)paren
op_logical_or
(paren
op_star
id|os
op_eq
l_char|&squot;&bslash;r&squot;
)paren
)paren
id|width
op_assign
id|max_width
suffix:semicolon
r_else
id|width
op_decrement
suffix:semicolon
id|call_rtas
c_func
(paren
l_string|&quot;display-character&quot;
comma
l_int|1
comma
l_int|1
comma
l_int|NULL
comma
op_star
id|os
op_increment
)paren
suffix:semicolon
multiline_comment|/* if we overwrite the screen length */
r_if
c_cond
(paren
id|width
op_eq
l_int|0
)paren
r_while
c_loop
(paren
(paren
op_star
id|os
op_ne
l_int|0
)paren
op_logical_and
(paren
op_star
id|os
op_ne
l_char|&squot;&bslash;n&squot;
)paren
op_logical_and
(paren
op_star
id|os
op_ne
l_char|&squot;&bslash;r&squot;
)paren
)paren
id|os
op_increment
suffix:semicolon
)brace
multiline_comment|/*while ( width-- &gt; 0 )*/
id|call_rtas
c_func
(paren
l_string|&quot;display-character&quot;
comma
l_int|1
comma
l_int|1
comma
l_int|NULL
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
)brace
eof
