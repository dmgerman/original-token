multiline_comment|/*&n; *  linux/arch/alpha/kernel/setup.c&n; *&n; *  Copyright (C) 1995  David S. Miller (davem@caip.rutgers.edu)&n; */
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
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;   /* for console registration + cheese */
r_extern
r_void
id|get_idprom
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|probe_devices
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Gcc is hard to keep happy ;-)&n; */
DECL|variable|screen_info
r_struct
id|screen_info
id|screen_info
op_assign
(brace
l_int|0
comma
l_int|0
comma
multiline_comment|/* orig-x, orig-y */
(brace
l_int|0
comma
l_int|0
comma
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
multiline_comment|/* orig-video-lines */
)brace
suffix:semicolon
multiline_comment|/* At least I hide the sneaky floppy_track_buffer in my dirty assembly&n; * code. ;-)&n; */
DECL|function|bios32_init
r_int
r_int
id|bios32_init
c_func
(paren
r_int
r_int
id|memory_start
comma
r_int
r_int
id|memory_end
)paren
(brace
r_return
id|memory_start
suffix:semicolon
)brace
multiline_comment|/* Lame prom console routines, gets registered below. Thanks for the&n; * tip Linus.&n; */
DECL|function|sparc_console_print
r_void
id|sparc_console_print
c_func
(paren
r_const
r_char
op_star
id|p
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
(paren
id|p
op_increment
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|romvec
op_member_access_from_pointer
id|pv_putchar
c_func
(paren
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
(paren
op_star
(paren
id|romvec-&gt;pv_putchar
)paren
)paren
(paren
id|c
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/* This routine will in the future do all the nasty prom stuff&n; * to probe for the mmu type and it&squot;s parameters, etc. This will&n; * also be where SMP things happen plus the Sparc specific memory&n; * physical memory probe as on the alpha.&n; */
r_extern
r_void
id|register_console
c_func
(paren
r_void
(paren
op_star
id|proc
)paren
(paren
r_const
r_char
op_star
)paren
)paren
suffix:semicolon
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
id|register_console
c_func
(paren
id|sparc_console_print
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Sparc PROM-Console registered...&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;calling get_idprom...&bslash;n&quot;
)paren
suffix:semicolon
id|get_idprom
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* probe_devices expects this to be done */
id|printk
c_func
(paren
l_string|&quot;calling probe_devices...&bslash;n&quot;
)paren
suffix:semicolon
id|probe_devices
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* cpu/fpu, mmu probes */
id|swpipl
c_func
(paren
l_int|13
)paren
suffix:semicolon
op_star
id|memory_start_p
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
op_amp
id|end
)paren
)paren
suffix:semicolon
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
eof
