multiline_comment|/* $Id: sgialib.h,v 1.1 1997/06/06 09:39:56 ralf Exp $&n; * sgialib.h: SGI ARCS firmware interface library for the Linux kernel.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#ifndef _MIPS_SGIALIB_H
DECL|macro|_MIPS_SGIALIB_H
mdefine_line|#define _MIPS_SGIALIB_H
macro_line|#include &lt;asm/sgiarcs.h&gt;
r_extern
r_struct
id|linux_promblock
op_star
id|sgi_pblock
suffix:semicolon
r_extern
r_struct
id|linux_romvec
op_star
id|romvec
suffix:semicolon
r_extern
r_int
id|prom_argc
suffix:semicolon
r_extern
r_char
op_star
op_star
id|prom_argv
comma
op_star
op_star
id|prom_envp
suffix:semicolon
multiline_comment|/* Init the PROM library and it&squot;s internal data structures.  Called&n; * at boot time from head.S before start_kernel is invoked.&n; */
r_extern
r_int
id|prom_init
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|envp
)paren
suffix:semicolon
multiline_comment|/* Simple char-by-char console I/O. */
r_extern
r_void
id|prom_putchar
c_func
(paren
r_char
id|c
)paren
suffix:semicolon
r_extern
r_char
id|prom_getchar
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Generic printf() using ARCS console I/O. */
r_extern
r_void
id|prom_printf
c_func
(paren
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
multiline_comment|/* Memory descriptor management. */
DECL|macro|PROM_MAX_PMEMBLOCKS
mdefine_line|#define PROM_MAX_PMEMBLOCKS    32
DECL|struct|prom_pmemblock
r_struct
id|prom_pmemblock
(brace
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
multiline_comment|/* Within KSEG0. */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* In bytes. */
)brace
suffix:semicolon
multiline_comment|/* Get next memory descriptor after CURR, returns first descriptor&n; * in chain is CURR is NULL.&n; */
r_extern
r_struct
id|linux_mdesc
op_star
id|prom_getmdesc
c_func
(paren
r_struct
id|linux_mdesc
op_star
id|curr
)paren
suffix:semicolon
DECL|macro|PROM_NULL_MDESC
mdefine_line|#define PROM_NULL_MDESC   ((struct linux_mdesc *) 0)
multiline_comment|/* Called by prom_init to setup the physical memory pmemblock&n; * array.&n; */
r_extern
r_void
id|prom_meminit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|prom_fixup_mem_map
c_func
(paren
r_int
r_int
id|start_mem
comma
r_int
r_int
id|end_mem
)paren
suffix:semicolon
multiline_comment|/* Returns pointer to PROM physical memory block array. */
r_extern
r_struct
id|prom_pmemblock
op_star
id|prom_getpblock_array
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* PROM device tree library routines. */
DECL|macro|PROM_NULL_COMPONENT
mdefine_line|#define PROM_NULL_COMPONENT ((pcomponent *) 0)
multiline_comment|/* Get sibling component of THIS. */
r_extern
id|pcomponent
op_star
id|prom_getsibling
c_func
(paren
id|pcomponent
op_star
id|this
)paren
suffix:semicolon
multiline_comment|/* Get child component of THIS. */
r_extern
id|pcomponent
op_star
id|prom_getchild
c_func
(paren
id|pcomponent
op_star
id|this
)paren
suffix:semicolon
multiline_comment|/* Get parent component of CHILD. */
r_extern
id|pcomponent
op_star
id|prom_getparent
c_func
(paren
id|pcomponent
op_star
id|child
)paren
suffix:semicolon
multiline_comment|/* Copy component opaque data of component THIS into BUFFER&n; * if component THIS has opaque data.  Returns success or&n; * failure status.&n; */
r_extern
r_int
id|prom_getcdata
c_func
(paren
r_void
op_star
id|buffer
comma
id|pcomponent
op_star
id|this
)paren
suffix:semicolon
multiline_comment|/* Other misc. component routines. */
r_extern
id|pcomponent
op_star
id|prom_childadd
c_func
(paren
id|pcomponent
op_star
id|this
comma
id|pcomponent
op_star
id|tmp
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_extern
r_int
id|prom_delcomponent
c_func
(paren
id|pcomponent
op_star
id|this
)paren
suffix:semicolon
r_extern
id|pcomponent
op_star
id|prom_componentbypath
c_func
(paren
r_char
op_star
id|path
)paren
suffix:semicolon
multiline_comment|/* This is called at prom_init time to setup the tags which the&n; * MIPS kernel setup code wants to diddle with. &n; */
r_extern
r_void
id|prom_setup_archtags
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Environemt variable routines. */
r_extern
r_char
op_star
id|prom_getenv
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_int
id|prom_setenv
c_func
(paren
r_char
op_star
id|name
comma
r_char
op_star
id|value
)paren
suffix:semicolon
multiline_comment|/* ARCS command line acquisition and parsing. */
r_extern
r_char
op_star
id|prom_getcmdline
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|prom_init_cmdline
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Acquiring info about the current time, etc. */
r_extern
r_struct
id|linux_tinfo
op_star
id|prom_gettinfo
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|prom_getrtime
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* File operations. */
r_extern
r_int
id|prom_getvdirent
c_func
(paren
r_int
r_int
id|fd
comma
r_struct
id|linux_vdirent
op_star
id|ent
comma
r_int
r_int
id|num
comma
r_int
r_int
op_star
id|cnt
)paren
suffix:semicolon
r_extern
r_int
id|prom_open
c_func
(paren
r_char
op_star
id|name
comma
r_enum
id|linux_omode
id|md
comma
r_int
r_int
op_star
id|fd
)paren
suffix:semicolon
r_extern
r_int
id|prom_close
c_func
(paren
r_int
r_int
id|fd
)paren
suffix:semicolon
r_extern
r_int
id|prom_read
c_func
(paren
r_int
r_int
id|fd
comma
r_void
op_star
id|buf
comma
r_int
r_int
id|num
comma
r_int
r_int
op_star
id|cnt
)paren
suffix:semicolon
r_extern
r_int
id|prom_getrstatus
c_func
(paren
r_int
r_int
id|fd
)paren
suffix:semicolon
r_extern
r_int
id|prom_write
c_func
(paren
r_int
r_int
id|fd
comma
r_void
op_star
id|buf
comma
r_int
r_int
id|num
comma
r_int
r_int
op_star
id|cnt
)paren
suffix:semicolon
r_extern
r_int
id|prom_seek
c_func
(paren
r_int
r_int
id|fd
comma
r_struct
id|linux_bigint
op_star
id|off
comma
r_enum
id|linux_seekmode
id|sm
)paren
suffix:semicolon
r_extern
r_int
id|prom_mount
c_func
(paren
r_char
op_star
id|name
comma
r_enum
id|linux_mountops
id|op
)paren
suffix:semicolon
r_extern
r_int
id|prom_getfinfo
c_func
(paren
r_int
r_int
id|fd
comma
r_struct
id|linux_finfo
op_star
id|buf
)paren
suffix:semicolon
r_extern
r_int
id|prom_setfinfo
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|msk
)paren
suffix:semicolon
multiline_comment|/* Running stand-along programs. */
r_extern
r_int
id|prom_load
c_func
(paren
r_char
op_star
id|name
comma
r_int
r_int
id|end
comma
r_int
r_int
op_star
id|pc
comma
r_int
r_int
op_star
id|eaddr
)paren
suffix:semicolon
r_extern
r_int
id|prom_invoke
c_func
(paren
r_int
r_int
id|pc
comma
r_int
r_int
id|sp
comma
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|envp
)paren
suffix:semicolon
r_extern
r_int
id|prom_exec
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|envp
)paren
suffix:semicolon
multiline_comment|/* Misc. routines. */
r_extern
r_void
id|prom_halt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|prom_powerdown
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|prom_restart
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|prom_reboot
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|prom_imode
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|prom_cfgsave
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|linux_sysid
op_star
id|prom_getsysid
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|prom_cacheflush
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* !(_MIPS_SGIALIB_H) */
eof
