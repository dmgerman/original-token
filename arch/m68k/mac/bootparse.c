macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/macintosh.h&gt;
multiline_comment|/*&n; *&t;Booter vars&n; */
DECL|variable|boothowto
r_int
id|boothowto
suffix:semicolon
DECL|variable|_boothowto
r_int
id|_boothowto
suffix:semicolon
multiline_comment|/*&n; *&t;Called early to parse the environment (passed to us from the booter)&n; *&t;into a bootinfo struct. Will die as soon as we have our own booter&n; */
DECL|macro|atol
mdefine_line|#define atol(x)&t;simple_strtoul(x,NULL,0)
DECL|function|parse_booter
r_void
id|parse_booter
c_func
(paren
r_char
op_star
id|env
)paren
(brace
r_char
op_star
id|name
suffix:semicolon
r_char
op_star
id|value
suffix:semicolon
macro_line|#if 0
r_while
c_loop
(paren
l_int|0
op_logical_and
op_star
id|env
)paren
macro_line|#else
r_while
c_loop
(paren
op_star
id|env
)paren
macro_line|#endif
(brace
id|name
op_assign
id|env
suffix:semicolon
id|value
op_assign
id|name
suffix:semicolon
r_while
c_loop
(paren
op_star
id|value
op_ne
l_char|&squot;=&squot;
op_logical_and
op_star
id|value
)paren
(brace
id|value
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|value
op_eq
l_char|&squot;=&squot;
)paren
(brace
op_star
id|value
op_increment
op_assign
l_int|0
suffix:semicolon
)brace
id|env
op_assign
id|value
suffix:semicolon
r_while
c_loop
(paren
op_star
id|env
)paren
(brace
id|env
op_increment
suffix:semicolon
)brace
id|env
op_increment
suffix:semicolon
macro_line|#if 0 &t;&t;&t;
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;VIDEO_ADDR&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_mch.videoaddr
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;ROW_BYTES&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_mch.videorow
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;SCREEN_DEPTH&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_mch.videodepth
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;DIMENSIONS&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_mch.dimensions
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
macro_line|#endif &t;&t;&t;
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;BOOTTIME&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_bi_data.boottime
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;GMTBIAS&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_bi_data.gmtbias
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;BOOTERVER&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_bi_data.bootver
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;MACOS_VIDEO&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_bi_data.videological
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;MACOS_SCC&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_bi_data.sccbase
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;MACHINEID&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_bi_data.id
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;MEMSIZE&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_bi_data.memsize
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;SERIAL_MODEM_FLAGS&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_bi_data.serialmf
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;SERIAL_MODEM_HSKICLK&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_bi_data.serialhsk
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;SERIAL_MODEM_GPICLK&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_bi_data.serialgpi
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;SERIAL_PRINT_FLAGS&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_bi_data.printmf
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;SERIAL_PRINT_HSKICLK&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_bi_data.printhsk
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;SERIAL_PRINT_GPICLK&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_bi_data.printgpi
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;PROCESSOR&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_bi_data.cpuid
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;ROMBASE&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_bi_data.rombase
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;TIMEDBRA&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_bi_data.timedbra
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;ADBDELAY&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|mac_bi_data.adbdelay
op_assign
id|atol
c_func
(paren
id|value
)paren
suffix:semicolon
)brace
)brace
macro_line|#if 0&t;/* XXX: TODO with m68k_mach_* */
multiline_comment|/* Fill in the base stuff */
id|boot_info.machtype
op_assign
id|MACH_MAC
suffix:semicolon
multiline_comment|/* Read this from the macinfo we got ! */
multiline_comment|/*&t;boot_info.cputype=CPU_68020|FPUB_68881;*/
multiline_comment|/* &t;boot_info.memory[0].addr=0;*/
multiline_comment|/* &t;boot_info.memory[0].size=((mac_bi_data.id&gt;&gt;7)&amp;31)&lt;&lt;20;*/
id|boot_info.num_memory
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* On a MacII */
id|boot_info.ramdisk_size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* For now */
op_star
id|boot_info.command_line
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
)brace
DECL|function|print_booter
r_void
id|print_booter
c_func
(paren
r_char
op_star
id|env
)paren
(brace
r_char
op_star
id|name
suffix:semicolon
r_char
op_star
id|value
suffix:semicolon
r_while
c_loop
(paren
op_star
id|env
)paren
(brace
id|name
op_assign
id|env
suffix:semicolon
id|value
op_assign
id|name
suffix:semicolon
r_while
c_loop
(paren
op_star
id|value
op_ne
l_char|&squot;=&squot;
op_logical_and
op_star
id|value
)paren
(brace
id|value
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|value
op_eq
l_char|&squot;=&squot;
)paren
(brace
op_star
id|value
op_increment
op_assign
l_int|0
suffix:semicolon
)brace
id|env
op_assign
id|value
suffix:semicolon
r_while
c_loop
(paren
op_star
id|env
)paren
(brace
id|env
op_increment
suffix:semicolon
)brace
id|env
op_increment
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s=%s&bslash;n&quot;
comma
id|name
comma
id|value
)paren
suffix:semicolon
)brace
)brace
eof
