multiline_comment|/*&n; * tags.c: Initialize the arch tags the way the MIPS kernel setup&n; *         expects.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; *&n; * $Id: tags.c,v 1.2 1998/03/27 08:53:48 ralf Exp $&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/sgimc.h&gt;
multiline_comment|/* XXX This tag thing is a fucking rats nest, I&squot;m very inclined to completely&n; * XXX rework the MIPS people&squot;s multi-arch code _NOW_.&n; */
DECL|variable|machtype_SGI_INDY
r_static
r_int
r_int
id|machtype_SGI_INDY
op_assign
id|MACH_SGI_INDY
suffix:semicolon
DECL|variable|machgroup_SGI
r_static
r_int
r_int
id|machgroup_SGI
op_assign
id|MACH_GROUP_SGI
suffix:semicolon
DECL|variable|memlower_SGI_INDY
r_static
r_int
r_int
id|memlower_SGI_INDY
op_assign
(paren
id|KSEG0
op_plus
id|SGIMC_SEG0_BADDR
)paren
suffix:semicolon
DECL|variable|cputype_SGI_INDY
r_static
r_int
r_int
id|cputype_SGI_INDY
op_assign
id|CPU_R4400SC
suffix:semicolon
DECL|variable|tlb_entries_SGI_INDY
r_static
r_int
r_int
id|tlb_entries_SGI_INDY
op_assign
l_int|48
suffix:semicolon
DECL|variable|dummy_SGI_INDY
r_static
r_int
r_int
id|dummy_SGI_INDY
op_assign
l_int|0
suffix:semicolon
DECL|variable|dummy_dinfo_SGI_INDY
r_static
r_struct
id|drive_info_struct
id|dummy_dinfo_SGI_INDY
op_assign
(brace
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
DECL|variable|arcs_cmdline
r_char
id|arcs_cmdline
(braket
id|CL_SIZE
)braket
suffix:semicolon
DECL|macro|TAG
mdefine_line|#define TAG(t,l)   {tag_##t,(l)} /* XXX RATS NEST CODE!!! XXX */
DECL|macro|TAGVAL
mdefine_line|#define TAGVAL(v)  (void*)&amp;(v)   /* XXX FUCKING LOSING!!! XXX */
DECL|variable|taglist_sgi_indy
id|tag_def
id|taglist_sgi_indy
(braket
)braket
op_assign
(brace
(brace
id|TAG
c_func
(paren
id|machtype
comma
id|ULONGSIZE
)paren
comma
id|TAGVAL
c_func
(paren
id|machtype_SGI_INDY
)paren
)brace
comma
(brace
id|TAG
c_func
(paren
id|machgroup
comma
id|ULONGSIZE
)paren
comma
id|TAGVAL
c_func
(paren
id|machgroup_SGI
)paren
)brace
comma
(brace
id|TAG
c_func
(paren
id|memlower
comma
id|ULONGSIZE
)paren
comma
id|TAGVAL
c_func
(paren
id|memlower_SGI_INDY
)paren
)brace
comma
(brace
id|TAG
c_func
(paren
id|cputype
comma
id|ULONGSIZE
)paren
comma
id|TAGVAL
c_func
(paren
id|cputype_SGI_INDY
)paren
)brace
comma
(brace
id|TAG
c_func
(paren
id|tlb_entries
comma
id|ULONGSIZE
)paren
comma
id|TAGVAL
c_func
(paren
id|tlb_entries_SGI_INDY
)paren
)brace
comma
(brace
id|TAG
c_func
(paren
id|vram_base
comma
id|ULONGSIZE
)paren
comma
id|TAGVAL
c_func
(paren
id|dummy_SGI_INDY
)paren
)brace
comma
(brace
id|TAG
c_func
(paren
id|drive_info
comma
id|DRVINFOSIZE
)paren
comma
id|TAGVAL
c_func
(paren
id|dummy_dinfo_SGI_INDY
)paren
)brace
comma
(brace
id|TAG
c_func
(paren
id|mount_root_rdonly
comma
id|ULONGSIZE
)paren
comma
id|TAGVAL
c_func
(paren
id|dummy_SGI_INDY
)paren
)brace
comma
(brace
id|TAG
c_func
(paren
id|command_line
comma
id|CL_SIZE
)paren
comma
id|TAGVAL
c_func
(paren
id|arcs_cmdline
(braket
l_int|0
)braket
)paren
)brace
comma
(brace
id|TAG
c_func
(paren
id|dummy
comma
l_int|0
)paren
comma
l_int|NULL
)brace
multiline_comment|/* XXX COLOSTOMY BAG!!!! XXX */
)brace
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|prom_setup_archtags
c_func
(paren
r_void
)paren
)paren
(brace
id|tag_def
op_star
id|tdp
op_assign
op_amp
id|taglist_sgi_indy
(braket
l_int|0
)braket
suffix:semicolon
id|tag
op_star
id|tp
suffix:semicolon
id|tp
op_assign
(paren
id|tag
op_star
)paren
(paren
id|mips_memory_upper
op_minus
r_sizeof
(paren
id|tag
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|tdp-&gt;t.tag
op_ne
id|tag_dummy
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
r_char
op_star
id|d
suffix:semicolon
op_star
id|tp
op_assign
id|tdp-&gt;t
suffix:semicolon
id|size
op_assign
id|tp-&gt;size
suffix:semicolon
id|d
op_assign
(paren
r_char
op_star
)paren
id|tdp-&gt;d
suffix:semicolon
id|tp
op_assign
(paren
id|tag
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
id|tp
)paren
op_minus
(paren
id|tp-&gt;size
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
)paren
(brace
id|memcpy
c_func
(paren
id|tp
comma
id|d
comma
id|size
)paren
suffix:semicolon
)brace
id|tp
op_decrement
suffix:semicolon
id|tdp
op_increment
suffix:semicolon
)brace
op_star
id|tp
op_assign
id|tdp-&gt;t
suffix:semicolon
multiline_comment|/* copy last dummy element over */
)brace
eof
