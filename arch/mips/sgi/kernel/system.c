multiline_comment|/*&n; * system.c: Probe the system type using ARCS prom interface library.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; *&n; * $Id: system.c,v 1.2 1997/06/30 15:26:32 ralf Exp $&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/sgi.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#ifndef __GOGOGO__
macro_line|#error &quot;... You&squot;re fearless, aren&squot;t you?&quot;
macro_line|#endif
DECL|variable|sgimach
r_enum
id|sgi_mach
id|sgimach
suffix:semicolon
DECL|struct|smatch
r_struct
id|smatch
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|sgi_mtable
r_static
r_struct
id|smatch
id|sgi_mtable
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;SGI-IP4&quot;
comma
id|ip4
)brace
comma
(brace
l_string|&quot;SGI-IP5&quot;
comma
id|ip5
)brace
comma
(brace
l_string|&quot;SGI-IP6&quot;
comma
id|ip6
)brace
comma
(brace
l_string|&quot;SGI-IP7&quot;
comma
id|ip7
)brace
comma
(brace
l_string|&quot;SGI-IP9&quot;
comma
id|ip9
)brace
comma
(brace
l_string|&quot;SGI-IP12&quot;
comma
id|ip12
)brace
comma
(brace
l_string|&quot;SGI-IP15&quot;
comma
id|ip15
)brace
comma
(brace
l_string|&quot;SGI-IP17&quot;
comma
id|ip17
)brace
comma
(brace
l_string|&quot;SGI-IP19&quot;
comma
id|ip19
)brace
comma
(brace
l_string|&quot;SGI-IP20&quot;
comma
id|ip20
)brace
comma
(brace
l_string|&quot;SGI-IP21&quot;
comma
id|ip21
)brace
comma
(brace
l_string|&quot;SGI-IP22&quot;
comma
id|ip22
)brace
comma
(brace
l_string|&quot;SGI-IP25&quot;
comma
id|ip25
)brace
comma
(brace
l_string|&quot;SGI-IP26&quot;
comma
id|ip26
)brace
comma
(brace
l_string|&quot;SGI-IP28&quot;
comma
id|ip28
)brace
comma
(brace
l_string|&quot;SGI-IP30&quot;
comma
id|ip30
)brace
comma
(brace
l_string|&quot;SGI-IP32&quot;
comma
id|ip32
)brace
)brace
suffix:semicolon
DECL|macro|NUM_MACHS
mdefine_line|#define NUM_MACHS 17 /* for now */
DECL|variable|sgi_cputable
r_static
r_struct
id|smatch
id|sgi_cputable
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;MIPS-R2000&quot;
comma
id|CPU_R2000
)brace
comma
(brace
l_string|&quot;MIPS-R3000&quot;
comma
id|CPU_R3000
)brace
comma
(brace
l_string|&quot;MIPS-R3000A&quot;
comma
id|CPU_R3000A
)brace
comma
(brace
l_string|&quot;MIPS-R4000&quot;
comma
id|CPU_R4000SC
)brace
comma
(brace
l_string|&quot;MIPS-R4400&quot;
comma
id|CPU_R4400SC
)brace
comma
(brace
l_string|&quot;MIPS-R4600&quot;
comma
id|CPU_R4600
)brace
comma
(brace
l_string|&quot;MIPS-R8000&quot;
comma
id|CPU_R8000
)brace
comma
(brace
l_string|&quot;MIPS-R5000&quot;
comma
id|CPU_R5000
)brace
comma
(brace
l_string|&quot;MIPS-R5000A&quot;
comma
id|CPU_R5000A
)brace
)brace
suffix:semicolon
DECL|macro|NUM_CPUS
mdefine_line|#define NUM_CPUS 9 /* for now */
DECL|function|string_to_mach
r_static
r_enum
id|sgi_mach
id|string_to_mach
c_func
(paren
r_char
op_star
id|s
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
id|NUM_MACHS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|s
comma
id|sgi_mtable
(braket
id|i
)braket
dot
id|name
)paren
)paren
(brace
r_return
(paren
r_enum
id|sgi_mach
)paren
id|sgi_mtable
(braket
id|i
)braket
dot
id|type
suffix:semicolon
)brace
)brace
id|prom_printf
c_func
(paren
l_string|&quot;&bslash;nYeee, could not determine SGI architecture type &lt;%s&gt;&bslash;n&quot;
comma
id|s
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;press a key to reboot&bslash;n&quot;
)paren
suffix:semicolon
id|prom_getchar
c_func
(paren
)paren
suffix:semicolon
id|romvec
op_member_access_from_pointer
id|imode
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
r_enum
id|sgi_mach
)paren
l_int|0
suffix:semicolon
)brace
DECL|function|string_to_cpu
r_static
r_int
id|string_to_cpu
c_func
(paren
r_char
op_star
id|s
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
id|NUM_CPUS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|s
comma
id|sgi_cputable
(braket
id|i
)braket
dot
id|name
)paren
)paren
(brace
r_return
id|sgi_mtable
(braket
id|i
)braket
dot
id|type
suffix:semicolon
)brace
)brace
id|prom_printf
c_func
(paren
l_string|&quot;&bslash;nYeee, could not determine MIPS cpu type &lt;%s&gt;&bslash;n&quot;
comma
id|s
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;press a key to reboot&bslash;n&quot;
)paren
suffix:semicolon
id|prom_getchar
c_func
(paren
)paren
suffix:semicolon
id|romvec
op_member_access_from_pointer
id|imode
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * We&squot; call this early before loadmmu().  If we do the other way around&n; * the firmware will crash and burn.&n; */
DECL|function|sgi_sysinit
r_void
id|sgi_sysinit
c_func
(paren
r_void
)paren
(brace
id|pcomponent
op_star
id|p
comma
op_star
id|toplev
comma
op_star
id|cpup
op_assign
l_int|0
suffix:semicolon
r_int
id|cputype
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* The root component tells us what machine architecture we&n;&t; * have here.&n;&t; */
id|p
op_assign
id|prom_getchild
c_func
(paren
id|PROM_NULL_COMPONENT
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ARCH: %s&bslash;n&quot;
comma
id|p-&gt;iname
)paren
suffix:semicolon
id|sgimach
op_assign
id|string_to_mach
c_func
(paren
id|p-&gt;iname
)paren
suffix:semicolon
multiline_comment|/* Now scan for cpu(s). */
id|toplev
op_assign
id|p
op_assign
id|prom_getchild
c_func
(paren
id|p
)paren
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
r_int
id|ncpus
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;type
op_eq
id|Cpu
)paren
(brace
r_if
c_cond
(paren
op_increment
id|ncpus
OG
l_int|1
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;&bslash;nYeee, SGI MP not ready yet&bslash;n&quot;
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;press a key to reboot&bslash;n&quot;
)paren
suffix:semicolon
id|prom_getchar
c_func
(paren
)paren
suffix:semicolon
id|romvec
op_member_access_from_pointer
id|imode
c_func
(paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;CPU: %s &quot;
comma
id|p-&gt;iname
)paren
suffix:semicolon
id|cpup
op_assign
id|p
suffix:semicolon
id|cputype
op_assign
id|string_to_cpu
c_func
(paren
id|cpup-&gt;iname
)paren
suffix:semicolon
)brace
id|p
op_assign
id|prom_getsibling
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cputype
op_eq
op_minus
l_int|1
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;&bslash;nYeee, could not find cpu ARCS component&bslash;n&quot;
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;press a key to reboot&bslash;n&quot;
)paren
suffix:semicolon
id|prom_getchar
c_func
(paren
)paren
suffix:semicolon
id|romvec
op_member_access_from_pointer
id|imode
c_func
(paren
)paren
suffix:semicolon
)brace
id|p
op_assign
id|prom_getchild
c_func
(paren
id|cpup
)paren
suffix:semicolon
r_while
c_loop
(paren
id|p
)paren
(brace
r_switch
c_cond
(paren
id|p
op_member_access_from_pointer
r_class
)paren
(brace
r_case
id|processor
suffix:colon
r_switch
c_cond
(paren
id|p-&gt;type
)paren
(brace
r_case
id|Fpu
suffix:colon
id|printk
c_func
(paren
l_string|&quot;FPU&lt;%s&gt; &quot;
comma
id|p-&gt;iname
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_break
suffix:semicolon
r_case
id|cache
suffix:colon
r_switch
c_cond
(paren
id|p-&gt;type
)paren
(brace
r_case
id|picache
suffix:colon
id|printk
c_func
(paren
l_string|&quot;ICACHE &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|pdcache
suffix:colon
id|printk
c_func
(paren
l_string|&quot;DCACHE &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|sccache
suffix:colon
id|printk
c_func
(paren
l_string|&quot;SCACHE &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
suffix:semicolon
id|p
op_assign
id|prom_getsibling
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof