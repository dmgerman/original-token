multiline_comment|/* $Id: openprom.h,v 1.3 1997/03/18 18:03:20 jj Exp $ */
macro_line|#ifndef __SPARC64_OPENPROM_H
DECL|macro|__SPARC64_OPENPROM_H
mdefine_line|#define __SPARC64_OPENPROM_H
multiline_comment|/* openprom.h:  Prom structures and defines for access to the OPENBOOT&n; *              prom routines and data areas.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
multiline_comment|/* Empirical constants... */
DECL|macro|KADB_DEBUGGER_BEGVM
mdefine_line|#define KADB_DEBUGGER_BEGVM     0xffc00000    /* Where kern debugger is in virt-mem */
DECL|macro|LINUX_OPPROM_BEGVM
mdefine_line|#define&t;LINUX_OPPROM_BEGVM&t;0xffd00000
DECL|macro|LINUX_OPPROM_ENDVM
mdefine_line|#define&t;LINUX_OPPROM_ENDVM&t;0xfff00000
DECL|macro|LINUX_OPPROM_MAGIC
mdefine_line|#define&t;LINUX_OPPROM_MAGIC      0x10010407
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* V0 prom device operations. */
DECL|struct|linux_dev_v0_funcs
r_struct
id|linux_dev_v0_funcs
(brace
DECL|member|v0_devopen
r_int
(paren
op_star
id|v0_devopen
)paren
(paren
r_char
op_star
id|device_str
)paren
suffix:semicolon
DECL|member|v0_devclose
r_int
(paren
op_star
id|v0_devclose
)paren
(paren
r_int
id|dev_desc
)paren
suffix:semicolon
DECL|member|v0_rdblkdev
r_int
(paren
op_star
id|v0_rdblkdev
)paren
(paren
r_int
id|dev_desc
comma
r_int
id|num_blks
comma
r_int
id|blk_st
comma
r_char
op_star
id|buf
)paren
suffix:semicolon
DECL|member|v0_wrblkdev
r_int
(paren
op_star
id|v0_wrblkdev
)paren
(paren
r_int
id|dev_desc
comma
r_int
id|num_blks
comma
r_int
id|blk_st
comma
r_char
op_star
id|buf
)paren
suffix:semicolon
DECL|member|v0_wrnetdev
r_int
(paren
op_star
id|v0_wrnetdev
)paren
(paren
r_int
id|dev_desc
comma
r_int
id|num_bytes
comma
r_char
op_star
id|buf
)paren
suffix:semicolon
DECL|member|v0_rdnetdev
r_int
(paren
op_star
id|v0_rdnetdev
)paren
(paren
r_int
id|dev_desc
comma
r_int
id|num_bytes
comma
r_char
op_star
id|buf
)paren
suffix:semicolon
DECL|member|v0_rdchardev
r_int
(paren
op_star
id|v0_rdchardev
)paren
(paren
r_int
id|dev_desc
comma
r_int
id|num_bytes
comma
r_int
id|dummy
comma
r_char
op_star
id|buf
)paren
suffix:semicolon
DECL|member|v0_wrchardev
r_int
(paren
op_star
id|v0_wrchardev
)paren
(paren
r_int
id|dev_desc
comma
r_int
id|num_bytes
comma
r_int
id|dummy
comma
r_char
op_star
id|buf
)paren
suffix:semicolon
DECL|member|v0_seekdev
r_int
(paren
op_star
id|v0_seekdev
)paren
(paren
r_int
id|dev_desc
comma
r_int
id|logical_offst
comma
r_int
id|from
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* V2 and later prom device operations. */
DECL|struct|linux_dev_v2_funcs
r_struct
id|linux_dev_v2_funcs
(brace
DECL|member|v2_inst2pkg
r_int
(paren
op_star
id|v2_inst2pkg
)paren
(paren
r_int
id|d
)paren
suffix:semicolon
multiline_comment|/* Convert ihandle to phandle */
DECL|member|v2_dumb_mem_alloc
r_char
op_star
(paren
op_star
id|v2_dumb_mem_alloc
)paren
(paren
r_char
op_star
id|va
comma
r_int
id|sz
)paren
suffix:semicolon
DECL|member|v2_dumb_mem_free
r_void
(paren
op_star
id|v2_dumb_mem_free
)paren
(paren
r_char
op_star
id|va
comma
r_int
id|sz
)paren
suffix:semicolon
multiline_comment|/* To map devices into virtual I/O space. */
DECL|member|v2_dumb_mmap
r_char
op_star
(paren
op_star
id|v2_dumb_mmap
)paren
(paren
r_char
op_star
id|virta
comma
r_int
id|which_io
comma
r_int
id|paddr
comma
r_int
id|sz
)paren
suffix:semicolon
DECL|member|v2_dumb_munmap
r_void
(paren
op_star
id|v2_dumb_munmap
)paren
(paren
r_char
op_star
id|virta
comma
r_int
id|size
)paren
suffix:semicolon
DECL|member|v2_dev_open
r_int
(paren
op_star
id|v2_dev_open
)paren
(paren
r_char
op_star
id|devpath
)paren
suffix:semicolon
DECL|member|v2_dev_close
r_void
(paren
op_star
id|v2_dev_close
)paren
(paren
r_int
id|d
)paren
suffix:semicolon
DECL|member|v2_dev_read
r_int
(paren
op_star
id|v2_dev_read
)paren
(paren
r_int
id|d
comma
r_char
op_star
id|buf
comma
r_int
id|nbytes
)paren
suffix:semicolon
DECL|member|v2_dev_write
r_int
(paren
op_star
id|v2_dev_write
)paren
(paren
r_int
id|d
comma
r_char
op_star
id|buf
comma
r_int
id|nbytes
)paren
suffix:semicolon
DECL|member|v2_dev_seek
r_int
(paren
op_star
id|v2_dev_seek
)paren
(paren
r_int
id|d
comma
r_int
id|hi
comma
r_int
id|lo
)paren
suffix:semicolon
multiline_comment|/* Never issued (multistage load support) */
DECL|member|v2_wheee2
r_void
(paren
op_star
id|v2_wheee2
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|v2_wheee3
r_void
(paren
op_star
id|v2_wheee3
)paren
(paren
r_void
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|linux_mlist_v0
r_struct
id|linux_mlist_v0
(brace
DECL|member|theres_more
r_struct
id|linux_mlist_v0
op_star
id|theres_more
suffix:semicolon
DECL|member|start_adr
r_int
id|start_adr
suffix:semicolon
DECL|member|num_bytes
r_int
id|num_bytes
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|linux_mem_v0
r_struct
id|linux_mem_v0
(brace
DECL|member|v0_totphys
r_struct
id|linux_mlist_v0
op_star
op_star
id|v0_totphys
suffix:semicolon
DECL|member|v0_prommap
r_struct
id|linux_mlist_v0
op_star
op_star
id|v0_prommap
suffix:semicolon
DECL|member|v0_available
r_struct
id|linux_mlist_v0
op_star
op_star
id|v0_available
suffix:semicolon
multiline_comment|/* What we can use */
)brace
suffix:semicolon
multiline_comment|/* Arguments sent to the kernel from the boot prompt. */
DECL|struct|linux_arguments_v0
r_struct
id|linux_arguments_v0
(brace
DECL|member|argv
r_char
op_star
id|argv
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|args
r_char
id|args
(braket
l_int|100
)braket
suffix:semicolon
DECL|member|boot_dev
r_char
id|boot_dev
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|boot_dev_ctrl
r_int
id|boot_dev_ctrl
suffix:semicolon
DECL|member|boot_dev_unit
r_int
id|boot_dev_unit
suffix:semicolon
DECL|member|dev_partition
r_int
id|dev_partition
suffix:semicolon
DECL|member|kernel_file_name
r_char
op_star
id|kernel_file_name
suffix:semicolon
DECL|member|aieee1
r_void
op_star
id|aieee1
suffix:semicolon
multiline_comment|/* XXX */
)brace
suffix:semicolon
multiline_comment|/* V2 and up boot things. */
DECL|struct|linux_bootargs_v2
r_struct
id|linux_bootargs_v2
(brace
DECL|member|bootpath
r_char
op_star
op_star
id|bootpath
suffix:semicolon
DECL|member|bootargs
r_char
op_star
op_star
id|bootargs
suffix:semicolon
DECL|member|fd_stdin
r_int
op_star
id|fd_stdin
suffix:semicolon
DECL|member|fd_stdout
r_int
op_star
id|fd_stdout
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The top level PROM vector. */
DECL|struct|linux_romvec
r_struct
id|linux_romvec
(brace
multiline_comment|/* Version numbers. */
DECL|member|pv_magic_cookie
r_int
r_int
id|pv_magic_cookie
suffix:semicolon
DECL|member|pv_romvers
r_int
r_int
id|pv_romvers
suffix:semicolon
DECL|member|pv_plugin_revision
r_int
r_int
id|pv_plugin_revision
suffix:semicolon
DECL|member|pv_printrev
r_int
r_int
id|pv_printrev
suffix:semicolon
multiline_comment|/* Version 0 memory descriptors. */
DECL|member|pv_v0mem
r_struct
id|linux_mem_v0
id|pv_v0mem
suffix:semicolon
multiline_comment|/* Node operations. */
DECL|member|pv_nodeops
r_struct
id|linux_nodeops
op_star
id|pv_nodeops
suffix:semicolon
DECL|member|pv_bootstr
r_char
op_star
op_star
id|pv_bootstr
suffix:semicolon
DECL|member|pv_v0devops
r_struct
id|linux_dev_v0_funcs
id|pv_v0devops
suffix:semicolon
DECL|member|pv_stdin
r_char
op_star
id|pv_stdin
suffix:semicolon
DECL|member|pv_stdout
r_char
op_star
id|pv_stdout
suffix:semicolon
DECL|macro|PROMDEV_KBD
mdefine_line|#define&t;PROMDEV_KBD&t;0&t;&t;/* input from keyboard */
DECL|macro|PROMDEV_SCREEN
mdefine_line|#define&t;PROMDEV_SCREEN&t;0&t;&t;/* output to screen */
DECL|macro|PROMDEV_TTYA
mdefine_line|#define&t;PROMDEV_TTYA&t;1&t;&t;/* in/out to ttya */
DECL|macro|PROMDEV_TTYB
mdefine_line|#define&t;PROMDEV_TTYB&t;2&t;&t;/* in/out to ttyb */
multiline_comment|/* Blocking getchar/putchar.  NOT REENTRANT! (grr) */
DECL|member|pv_getchar
r_int
(paren
op_star
id|pv_getchar
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|pv_putchar
r_void
(paren
op_star
id|pv_putchar
)paren
(paren
r_int
id|ch
)paren
suffix:semicolon
multiline_comment|/* Non-blocking variants. */
DECL|member|pv_nbgetchar
r_int
(paren
op_star
id|pv_nbgetchar
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|pv_nbputchar
r_int
(paren
op_star
id|pv_nbputchar
)paren
(paren
r_int
id|ch
)paren
suffix:semicolon
DECL|member|pv_putstr
r_void
(paren
op_star
id|pv_putstr
)paren
(paren
r_char
op_star
id|str
comma
r_int
id|len
)paren
suffix:semicolon
multiline_comment|/* Miscellany. */
DECL|member|pv_reboot
r_void
(paren
op_star
id|pv_reboot
)paren
(paren
r_char
op_star
id|bootstr
)paren
suffix:semicolon
DECL|member|pv_printf
r_void
(paren
op_star
id|pv_printf
)paren
(paren
id|__const__
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
DECL|member|pv_abort
r_void
(paren
op_star
id|pv_abort
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|pv_ticks
id|__volatile__
r_int
op_star
id|pv_ticks
suffix:semicolon
DECL|member|pv_halt
r_void
(paren
op_star
id|pv_halt
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|pv_synchook
r_void
(paren
op_star
op_star
id|pv_synchook
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Evaluate a forth string, not different proto for V0 and V2-&gt;up. */
r_union
(brace
DECL|member|v0_eval
r_void
(paren
op_star
id|v0_eval
)paren
(paren
r_int
id|len
comma
r_char
op_star
id|str
)paren
suffix:semicolon
DECL|member|v2_eval
r_void
(paren
op_star
id|v2_eval
)paren
(paren
r_char
op_star
id|str
)paren
suffix:semicolon
DECL|member|pv_fortheval
)brace
id|pv_fortheval
suffix:semicolon
DECL|member|pv_v0bootargs
r_struct
id|linux_arguments_v0
op_star
op_star
id|pv_v0bootargs
suffix:semicolon
multiline_comment|/* Get ether address. */
DECL|member|pv_enaddr
r_int
r_int
(paren
op_star
id|pv_enaddr
)paren
(paren
r_int
id|d
comma
r_char
op_star
id|enaddr
)paren
suffix:semicolon
DECL|member|pv_v2bootargs
r_struct
id|linux_bootargs_v2
id|pv_v2bootargs
suffix:semicolon
DECL|member|pv_v2devops
r_struct
id|linux_dev_v2_funcs
id|pv_v2devops
suffix:semicolon
DECL|member|filler
r_int
id|filler
(braket
l_int|15
)braket
suffix:semicolon
multiline_comment|/* This one is sun4c/sun4 only. */
DECL|member|pv_setctxt
r_void
(paren
op_star
id|pv_setctxt
)paren
(paren
r_int
id|ctxt
comma
r_char
op_star
id|va
comma
r_int
id|pmeg
)paren
suffix:semicolon
multiline_comment|/* Prom version 3 Multiprocessor routines. This stuff is crazy.&n;&t; * No joke. Calling these when there is only one cpu probably&n;&t; * crashes the machine, have to test this. :-)&n;&t; */
multiline_comment|/* v3_cpustart() will start the cpu &squot;whichcpu&squot; in mmu-context&n;&t; * &squot;thiscontext&squot; executing at address &squot;prog_counter&squot;&n;&t; */
DECL|member|v3_cpustart
r_int
(paren
op_star
id|v3_cpustart
)paren
(paren
r_int
r_int
id|whichcpu
comma
r_int
id|ctxtbl_ptr
comma
r_int
id|thiscontext
comma
r_char
op_star
id|prog_counter
)paren
suffix:semicolon
multiline_comment|/* v3_cpustop() will cause cpu &squot;whichcpu&squot; to stop executing&n;&t; * until a resume cpu call is made.&n;&t; */
DECL|member|v3_cpustop
r_int
(paren
op_star
id|v3_cpustop
)paren
(paren
r_int
r_int
id|whichcpu
)paren
suffix:semicolon
multiline_comment|/* v3_cpuidle() will idle cpu &squot;whichcpu&squot; until a stop or&n;&t; * resume cpu call is made.&n;&t; */
DECL|member|v3_cpuidle
r_int
(paren
op_star
id|v3_cpuidle
)paren
(paren
r_int
r_int
id|whichcpu
)paren
suffix:semicolon
multiline_comment|/* v3_cpuresume() will resume processor &squot;whichcpu&squot; executing&n;&t; * starting with whatever &squot;pc&squot; and &squot;npc&squot; were left at the&n;&t; * last &squot;idle&squot; or &squot;stop&squot; call.&n;&t; */
DECL|member|v3_cpuresume
r_int
(paren
op_star
id|v3_cpuresume
)paren
(paren
r_int
r_int
id|whichcpu
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Routines for traversing the prom device tree. */
DECL|struct|linux_nodeops
r_struct
id|linux_nodeops
(brace
DECL|member|no_nextnode
r_int
(paren
op_star
id|no_nextnode
)paren
(paren
r_int
id|node
)paren
suffix:semicolon
DECL|member|no_child
r_int
(paren
op_star
id|no_child
)paren
(paren
r_int
id|node
)paren
suffix:semicolon
DECL|member|no_proplen
r_int
(paren
op_star
id|no_proplen
)paren
(paren
r_int
id|node
comma
r_char
op_star
id|name
)paren
suffix:semicolon
DECL|member|no_getprop
r_int
(paren
op_star
id|no_getprop
)paren
(paren
r_int
id|node
comma
r_char
op_star
id|name
comma
r_char
op_star
id|val
)paren
suffix:semicolon
DECL|member|no_setprop
r_int
(paren
op_star
id|no_setprop
)paren
(paren
r_int
id|node
comma
r_char
op_star
id|name
comma
r_char
op_star
id|val
comma
r_int
id|len
)paren
suffix:semicolon
DECL|member|no_nextprop
r_char
op_star
(paren
op_star
id|no_nextprop
)paren
(paren
r_int
id|node
comma
r_char
op_star
id|name
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* More fun PROM structures for device probing. */
DECL|macro|PROMREG_MAX
mdefine_line|#define PROMREG_MAX     16
DECL|macro|PROMVADDR_MAX
mdefine_line|#define PROMVADDR_MAX   16
DECL|macro|PROMINTR_MAX
mdefine_line|#define PROMINTR_MAX    15
DECL|struct|linux_prom_registers
r_struct
id|linux_prom_registers
(brace
DECL|member|which_io
r_int
id|which_io
suffix:semicolon
multiline_comment|/* hi part of physical address */
DECL|member|phys_addr
r_int
id|phys_addr
suffix:semicolon
multiline_comment|/* The physical address of this register */
DECL|member|reg_size
r_int
id|reg_size
suffix:semicolon
multiline_comment|/* How many bytes does this register take up? */
)brace
suffix:semicolon
DECL|struct|linux_prom64_registers
r_struct
id|linux_prom64_registers
(brace
DECL|member|phys_addr
r_int
id|phys_addr
suffix:semicolon
DECL|member|reg_size
r_int
id|reg_size
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|linux_prom_irqs
r_struct
id|linux_prom_irqs
(brace
DECL|member|pri
r_int
id|pri
suffix:semicolon
multiline_comment|/* IRQ priority */
DECL|member|vector
r_int
id|vector
suffix:semicolon
multiline_comment|/* This is foobar, what does it do? */
)brace
suffix:semicolon
multiline_comment|/* Element of the &quot;ranges&quot; vector */
DECL|struct|linux_prom_ranges
r_struct
id|linux_prom_ranges
(brace
DECL|member|ot_child_space
r_int
r_int
id|ot_child_space
suffix:semicolon
DECL|member|ot_child_base
r_int
r_int
id|ot_child_base
suffix:semicolon
multiline_comment|/* Bus feels this */
DECL|member|ot_parent_space
r_int
r_int
id|ot_parent_space
suffix:semicolon
DECL|member|ot_parent_base
r_int
r_int
id|ot_parent_base
suffix:semicolon
multiline_comment|/* CPU looks from here */
DECL|member|or_size
r_int
r_int
id|or_size
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(__SPARC64_OPENPROM_H) */
eof
