multiline_comment|/*&n; *  linux/arch/alpha/kernel/setup.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; */
multiline_comment|/*&n; * bootup setup stuff..&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/ldt.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/config.h&gt;&t;/* CONFIG_ALPHA_LCA etc */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|variable|hae
r_struct
id|hae
id|hae
op_assign
(brace
l_int|0
comma
(paren
r_int
r_int
op_star
)paren
id|HAE_ADDRESS
)brace
suffix:semicolon
DECL|variable|hwrpb
r_struct
id|hwrpb_struct
op_star
id|hwrpb
suffix:semicolon
DECL|variable|aux_device_present
r_int
r_char
id|aux_device_present
op_assign
l_int|0xaa
suffix:semicolon
multiline_comment|/*&n; * This is setup by the secondary bootstrap loader.  Because&n; * the zero page is zeroed out as soon as the vm system is&n; * initialized, we need to copy things out into a more permanent&n; * place.&n; */
DECL|macro|PARAM
mdefine_line|#define PARAM&t;&t;&t;ZERO_PAGE
DECL|macro|COMMAND_LINE
mdefine_line|#define COMMAND_LINE&t;&t;((char*)(PARAM + 0x0000))
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE&t;256
DECL|variable|command_line
r_static
r_char
id|command_line
(braket
id|COMMAND_LINE_SIZE
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * The format of &quot;screen_info&quot; is strange, and due to early&n; * i386-setup code. This is just enough to make the console&n; * code think we&squot;re on a VGA color display.&n; */
DECL|variable|screen_info
r_struct
id|screen_info
id|screen_info
op_assign
(brace
l_int|0
comma
l_int|25
comma
multiline_comment|/* orig-x, orig-y */
(brace
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* unused */
l_int|0
comma
multiline_comment|/* orig-video-page */
l_int|0
comma
multiline_comment|/* orig-video-mode */
l_int|80
comma
multiline_comment|/* orig-video-cols */
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ega_ax, ega_bx, ega_cx */
l_int|25
comma
multiline_comment|/* orig-video-lines */
l_int|1
comma
multiline_comment|/* orig-video-isVGA */
l_int|16
multiline_comment|/* orig-video-points */
)brace
suffix:semicolon
DECL|function|find_end_memory
r_static
r_int
r_int
id|find_end_memory
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|high
op_assign
l_int|0
suffix:semicolon
r_struct
id|memclust_struct
op_star
id|cluster
suffix:semicolon
r_struct
id|memdesc_struct
op_star
id|memdesc
suffix:semicolon
id|memdesc
op_assign
(paren
r_struct
id|memdesc_struct
op_star
)paren
(paren
id|INIT_HWRPB-&gt;mddt_offset
op_plus
(paren
r_int
r_int
)paren
id|INIT_HWRPB
)paren
suffix:semicolon
id|cluster
op_assign
id|memdesc-&gt;cluster
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|memdesc-&gt;numclusters
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
comma
id|cluster
op_increment
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|tmp
op_assign
(paren
id|cluster-&gt;start_pfn
op_plus
id|cluster-&gt;numpages
)paren
op_lshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OG
id|high
)paren
id|high
op_assign
id|tmp
suffix:semicolon
)brace
multiline_comment|/* round it up to an even number of pages.. */
id|high
op_assign
(paren
id|high
op_plus
id|PAGE_SIZE
)paren
op_amp
(paren
id|PAGE_MASK
op_star
l_int|2
)paren
suffix:semicolon
r_return
id|PAGE_OFFSET
op_plus
id|high
suffix:semicolon
)brace
DECL|function|setup_arch
r_void
id|setup_arch
c_func
(paren
r_char
op_star
op_star
id|cmdline_p
comma
r_int
r_int
op_star
id|memory_start_p
comma
r_int
r_int
op_star
id|memory_end_p
)paren
(brace
r_extern
r_int
id|_end
suffix:semicolon
id|hwrpb
op_assign
(paren
r_struct
id|hwrpb_struct
op_star
)paren
(paren
id|IDENT_ADDR
op_plus
id|INIT_HWRPB-&gt;phys_addr
)paren
suffix:semicolon
id|set_hae
c_func
(paren
id|hae.cache
)paren
suffix:semicolon
multiline_comment|/* sync HAE register w/hae_cache */
id|wrmces
c_func
(paren
l_int|0x7
)paren
suffix:semicolon
multiline_comment|/* reset enable correctable error reports */
id|ROOT_DEV
op_assign
id|to_kdev_t
c_func
(paren
l_int|0x0802
)paren
suffix:semicolon
multiline_comment|/* sda2 */
id|command_line
(braket
id|COMMAND_LINE_SIZE
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|strcpy
c_func
(paren
id|command_line
comma
id|COMMAND_LINE
)paren
suffix:semicolon
op_star
id|cmdline_p
op_assign
id|command_line
suffix:semicolon
op_star
id|memory_start_p
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_end
suffix:semicolon
op_star
id|memory_end_p
op_assign
id|find_end_memory
c_func
(paren
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_ALPHA_LCA)
op_star
id|memory_start_p
op_assign
id|lca_init
c_func
(paren
op_star
id|memory_start_p
comma
op_star
id|memory_end_p
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_ALPHA_APECS)
op_star
id|memory_start_p
op_assign
id|apecs_init
c_func
(paren
op_star
id|memory_start_p
comma
op_star
id|memory_end_p
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|sys_ioperm
id|asmlinkage
r_int
id|sys_ioperm
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|num
comma
r_int
id|on
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/*&n; * BUFFER is PAGE_SIZE bytes long.&n; */
DECL|function|get_cpuinfo
r_int
id|get_cpuinfo
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
r_const
r_char
op_star
id|cpu_name
(braket
)braket
op_assign
(brace
l_string|&quot;EV3&quot;
comma
l_string|&quot;EV4&quot;
comma
l_string|&quot;Unknown 1&quot;
comma
l_string|&quot;LCA4&quot;
comma
l_string|&quot;EV5&quot;
comma
l_string|&quot;EV45&quot;
)brace
suffix:semicolon
DECL|macro|SYSTYPE_NAME_BIAS
macro_line|#&t;define SYSTYPE_NAME_BIAS&t;20
r_const
r_char
op_star
id|systype_name
(braket
)braket
op_assign
(brace
l_string|&quot;Cabriolet&quot;
comma
l_string|&quot;EB66P&quot;
comma
l_string|&quot;-18&quot;
comma
l_string|&quot;-17&quot;
comma
l_string|&quot;-16&quot;
comma
l_string|&quot;-15&quot;
comma
l_string|&quot;-14&quot;
comma
l_string|&quot;-13&quot;
comma
l_string|&quot;-12&quot;
comma
l_string|&quot;-11&quot;
comma
l_string|&quot;-10&quot;
comma
l_string|&quot;-9&quot;
comma
l_string|&quot;-8&quot;
comma
l_string|&quot;-7&quot;
comma
l_string|&quot;-6&quot;
comma
l_string|&quot;-5&quot;
comma
l_string|&quot;-4&quot;
comma
l_string|&quot;-3&quot;
comma
l_string|&quot;-2&quot;
comma
l_string|&quot;-1&quot;
comma
l_string|&quot;0&quot;
comma
l_string|&quot;ADU&quot;
comma
l_string|&quot;Cobra&quot;
comma
l_string|&quot;Ruby&quot;
comma
l_string|&quot;Flamingo&quot;
comma
l_string|&quot;5&quot;
comma
l_string|&quot;Jensen&quot;
comma
l_string|&quot;Pelican&quot;
comma
l_string|&quot;8&quot;
comma
l_string|&quot;Sable&quot;
comma
l_string|&quot;AXPvme&quot;
comma
l_string|&quot;Noname&quot;
comma
l_string|&quot;Turbolaser&quot;
comma
l_string|&quot;Avanti&quot;
comma
l_string|&quot;Mustang&quot;
comma
l_string|&quot;Alcor&quot;
comma
l_string|&quot;16&quot;
comma
l_string|&quot;Mikasa&quot;
comma
l_string|&quot;18&quot;
comma
l_string|&quot;EB66&quot;
comma
l_string|&quot;EB64+&quot;
)brace
suffix:semicolon
r_struct
id|percpu_struct
op_star
id|cpu
suffix:semicolon
r_int
r_int
id|cpu_index
suffix:semicolon
r_int
id|sysname_index
suffix:semicolon
r_extern
r_struct
id|unaligned_stat
(brace
r_int
r_int
id|count
comma
id|va
comma
id|pc
suffix:semicolon
)brace
id|unaligned
(braket
l_int|2
)braket
suffix:semicolon
DECL|macro|N
macro_line|#&t;define N(a)&t;(sizeof(a)/sizeof(a[0]))
id|cpu
op_assign
(paren
r_struct
id|percpu_struct
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|hwrpb
op_plus
id|hwrpb-&gt;processor_offset
)paren
suffix:semicolon
id|cpu_index
op_assign
(paren
r_int
)paren
(paren
id|cpu-&gt;type
op_minus
l_int|1
)paren
suffix:semicolon
id|sysname_index
op_assign
id|hwrpb-&gt;sys_type
op_plus
id|SYSTYPE_NAME_BIAS
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;cpu&bslash;t&bslash;t&bslash;t: Alpha&bslash;n&quot;
l_string|&quot;cpu model&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;cpu variation&bslash;t&bslash;t: %ld&bslash;n&quot;
l_string|&quot;cpu revision&bslash;t&bslash;t: %ld&bslash;n&quot;
l_string|&quot;cpu serial number&bslash;t: %s&bslash;n&quot;
l_string|&quot;system type&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;system variation&bslash;t: %ld&bslash;n&quot;
l_string|&quot;system revision&bslash;t&bslash;t: %ld&bslash;n&quot;
l_string|&quot;system serial number&bslash;t: %s&bslash;n&quot;
l_string|&quot;cycle frequency [Hz]&bslash;t: %lu&bslash;n&quot;
l_string|&quot;timer frequency [Hz]&bslash;t: %lu.%02lu&bslash;n&quot;
l_string|&quot;page size [bytes]&bslash;t: %ld&bslash;n&quot;
l_string|&quot;phys. address bits&bslash;t: %ld&bslash;n&quot;
l_string|&quot;max. addr. space #&bslash;t: %ld&bslash;n&quot;
l_string|&quot;BogoMIPS&bslash;t&bslash;t: %lu.%02lu&bslash;n&quot;
l_string|&quot;kernel unaligned acc&bslash;t: %ld (pc=%lx,va=%lx)&bslash;n&quot;
l_string|&quot;user unaligned acc&bslash;t: %ld (pc=%lx,va=%lx)&bslash;n&quot;
comma
(paren
id|cpu_index
OL
id|N
c_func
(paren
id|cpu_name
)paren
ques
c_cond
id|cpu_name
(braket
id|cpu_index
)braket
suffix:colon
l_string|&quot;Unknown&quot;
)paren
comma
id|cpu-&gt;variation
comma
id|cpu-&gt;revision
comma
(paren
r_char
op_star
)paren
id|cpu-&gt;serial_no
comma
(paren
id|sysname_index
OL
id|N
c_func
(paren
id|systype_name
)paren
ques
c_cond
id|systype_name
(braket
id|sysname_index
)braket
suffix:colon
l_string|&quot;Unknown&quot;
)paren
comma
id|hwrpb-&gt;sys_variation
comma
id|hwrpb-&gt;sys_revision
comma
(paren
r_char
op_star
)paren
id|hwrpb-&gt;ssn
comma
id|hwrpb-&gt;cycle_freq
comma
id|hwrpb-&gt;intr_freq
op_div
l_int|4096
comma
(paren
l_int|100
op_star
id|hwrpb-&gt;intr_freq
op_div
l_int|4096
)paren
op_mod
l_int|100
comma
id|hwrpb-&gt;pagesize
comma
id|hwrpb-&gt;pa_bits
comma
id|hwrpb-&gt;max_asn
comma
id|loops_per_sec
op_div
l_int|500000
comma
(paren
id|loops_per_sec
op_div
l_int|5000
)paren
op_mod
l_int|100
comma
id|unaligned
(braket
l_int|0
)braket
dot
id|count
comma
id|unaligned
(braket
l_int|0
)braket
dot
id|pc
comma
id|unaligned
(braket
l_int|0
)braket
dot
id|va
comma
id|unaligned
(braket
l_int|1
)braket
dot
id|count
comma
id|unaligned
(braket
l_int|1
)braket
dot
id|pc
comma
id|unaligned
(braket
l_int|1
)braket
dot
id|va
)paren
suffix:semicolon
DECL|macro|N
macro_line|#       undef N
)brace
eof
