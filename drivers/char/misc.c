multiline_comment|/*&n; * linux/drivers/char/misc.c&n; *&n; * Generic misc open routine by Johan Myreen&n; *&n; * Based on code from Linus&n; *&n; * Teemu Rantanen&squot;s Microsoft Busmouse support and Derrick Cole&squot;s&n; *   changes incorporated into 0.97pl4&n; *   by Peter Cervasio (pete%q106fm.uucp@wupost.wustl.edu) (08SEP92)&n; *   See busmouse.c for particulars.&n; *&n; * Made things a lot mode modular - easy to compile in just one or two&n; * of the misc drivers, as they are now completely independent. Linus.&n; *&n; * Support for loadable modules. 8-Sep-95 Philip Blundell &lt;pjb27@cam.ac.uk&gt;&n; *&n; * Fixed a failing symbol register to free the device registration&n; *&t;&t;Alan Cox &lt;alan@lxorguk.ukuu.org.uk&gt; 21-Jan-96&n; *&n; * Dynamic minors and /proc/mice by Alessandro Rubini. 26-Mar-96&n; *&n; * Renamed to misc and miscdevice to be more accurate. Alan Cox 26-Mar-96&n; *&n; * Handling of mouse minor numbers for kerneld:&n; *  Idea by Jacques Gelinas &lt;jack@solucorp.qc.ca&gt;,&n; *  adapted by Bjorn Ekwall &lt;bj0rn@blox.se&gt;&n; *  corrected by Alan Cox &lt;alan@lxorguk.ukuu.org.uk&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifdef CONFIG_APM
macro_line|#include &lt;linux/apm_bios.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/selection.h&gt;
macro_line|#ifdef CONFIG_KERNELD
macro_line|#include &lt;linux/kerneld.h&gt;
macro_line|#endif
multiline_comment|/*&n; * Head entry for the doubly linked miscdevice list&n; */
DECL|variable|misc_list
r_static
r_struct
id|miscdevice
id|misc_list
op_assign
(brace
l_int|0
comma
l_string|&quot;head&quot;
comma
l_int|NULL
comma
op_amp
id|misc_list
comma
op_amp
id|misc_list
)brace
suffix:semicolon
multiline_comment|/*&n; * Assigned numbers, used for dynamic minors&n; */
DECL|macro|DYNAMIC_MINORS
mdefine_line|#define DYNAMIC_MINORS 64 /* like dynamic majors */
DECL|variable|misc_minors
r_static
r_int
r_char
id|misc_minors
(braket
id|DYNAMIC_MINORS
op_div
l_int|8
)braket
suffix:semicolon
macro_line|#ifndef MODULE
r_extern
r_int
id|bus_mouse_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|psaux_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ms_bus_mouse_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|atixl_busmouse_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|amiga_mouse_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|atari_mouse_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|sun_mouse_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|watchdog_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|wdt_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|acq_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pcwatchdog_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|rtc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|dsp56k_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|nvram_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|radio_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|hfmodem_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROC_FS
DECL|function|misc_read_proc
r_static
r_int
id|misc_read_proc
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|len
comma
r_int
op_star
id|eof
comma
r_void
op_star
r_private
)paren
(brace
r_struct
id|miscdevice
op_star
id|p
suffix:semicolon
id|len
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|misc_list.next
suffix:semicolon
id|p
op_ne
op_amp
id|misc_list
op_logical_and
id|len
OL
l_int|4000
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%3i %s&bslash;n&quot;
comma
id|p-&gt;minor
comma
id|p-&gt;name
ques
c_cond
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
op_star
id|start
op_assign
id|buf
op_plus
id|offset
suffix:semicolon
r_return
id|len
OG
id|offset
ques
c_cond
id|len
op_minus
id|offset
suffix:colon
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* PROC_FS */
macro_line|#endif /* !MODULE */
DECL|function|misc_open
r_static
r_int
id|misc_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|minor
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|miscdevice
op_star
id|c
op_assign
id|misc_list.next
suffix:semicolon
id|file-&gt;f_op
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_ne
op_amp
id|misc_list
)paren
op_logical_and
(paren
id|c-&gt;minor
op_ne
id|minor
)paren
)paren
id|c
op_assign
id|c-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
op_amp
id|misc_list
)paren
(brace
macro_line|#ifdef CONFIG_KERNELD
r_char
id|modname
(braket
l_int|20
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|modname
comma
l_string|&quot;char-major-%d-%d&quot;
comma
id|MISC_MAJOR
comma
id|minor
)paren
suffix:semicolon
id|request_module
c_func
(paren
id|modname
)paren
suffix:semicolon
id|c
op_assign
id|misc_list.next
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_ne
op_amp
id|misc_list
)paren
op_logical_and
(paren
id|c-&gt;minor
op_ne
id|minor
)paren
)paren
id|c
op_assign
id|c-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
op_amp
id|misc_list
)paren
macro_line|#endif
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|file-&gt;f_op
op_assign
id|c-&gt;fops
)paren
op_logical_and
id|file-&gt;f_op-&gt;open
)paren
r_return
id|file-&gt;f_op
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|file
)paren
suffix:semicolon
r_else
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|variable|misc_fops
r_static
r_struct
id|file_operations
id|misc_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* seek */
l_int|NULL
comma
multiline_comment|/* read */
l_int|NULL
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* poll */
l_int|NULL
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
id|misc_open
comma
l_int|NULL
multiline_comment|/* release */
)brace
suffix:semicolon
DECL|function|misc_register
r_int
id|misc_register
c_func
(paren
r_struct
id|miscdevice
op_star
id|misc
)paren
(brace
r_if
c_cond
(paren
id|misc-&gt;next
op_logical_or
id|misc-&gt;prev
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|misc-&gt;minor
op_eq
id|MISC_DYNAMIC_MINOR
)paren
(brace
r_int
id|i
op_assign
id|DYNAMIC_MINORS
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|i
op_ge
l_int|0
)paren
r_if
c_cond
(paren
(paren
id|misc_minors
(braket
id|i
op_rshift
l_int|3
)braket
op_amp
(paren
l_int|1
op_lshift
(paren
id|i
op_amp
l_int|7
)paren
)paren
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|misc-&gt;minor
op_assign
id|i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|misc-&gt;minor
OL
id|DYNAMIC_MINORS
)paren
id|misc_minors
(braket
id|misc-&gt;minor
op_rshift
l_int|3
)braket
op_or_assign
l_int|1
op_lshift
(paren
id|misc-&gt;minor
op_amp
l_int|7
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|misc-&gt;next
op_assign
op_amp
id|misc_list
suffix:semicolon
id|misc-&gt;prev
op_assign
id|misc_list.prev
suffix:semicolon
id|misc-&gt;prev-&gt;next
op_assign
id|misc
suffix:semicolon
id|misc-&gt;next-&gt;prev
op_assign
id|misc
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|misc_deregister
r_int
id|misc_deregister
c_func
(paren
r_struct
id|miscdevice
op_star
id|misc
)paren
(brace
r_int
id|i
op_assign
id|misc-&gt;minor
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|misc-&gt;next
op_logical_or
op_logical_neg
id|misc-&gt;prev
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
id|misc-&gt;prev-&gt;next
op_assign
id|misc-&gt;next
suffix:semicolon
id|misc-&gt;next-&gt;prev
op_assign
id|misc-&gt;prev
suffix:semicolon
id|misc-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|misc-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|i
template_param
l_int|0
)paren
(brace
id|misc_minors
(braket
id|i
op_rshift
l_int|3
)braket
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|misc-&gt;minor
op_amp
l_int|7
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|macro|misc_init
mdefine_line|#define misc_init init_module
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|unregister_chrdev
c_func
(paren
id|MISC_MAJOR
comma
l_string|&quot;misc&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|misc_register
id|EXPORT_SYMBOL
c_func
(paren
id|misc_register
)paren
suffix:semicolon
DECL|variable|misc_deregister
id|EXPORT_SYMBOL
c_func
(paren
id|misc_deregister
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_PROC_FS) &amp;&amp; !defined(MODULE)
DECL|variable|proc_misc
r_static
r_struct
id|proc_dir_entry
op_star
id|proc_misc
suffix:semicolon
macro_line|#endif
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|misc_init
c_func
(paren
r_void
)paren
)paren
(brace
macro_line|#ifndef MODULE
macro_line|#ifdef CONFIG_PROC_FS
id|proc_misc
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;misc&quot;
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proc_misc
)paren
id|proc_misc-&gt;read_proc
op_assign
id|misc_read_proc
suffix:semicolon
macro_line|#endif /* PROC_FS */
macro_line|#ifdef CONFIG_BUSMOUSE
id|bus_mouse_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined CONFIG_PSMOUSE
id|psaux_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MS_BUSMOUSE
id|ms_bus_mouse_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATIXL_BUSMOUSE
id|atixl_busmouse_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_AMIGAMOUSE
id|amiga_mouse_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATARIMOUSE
id|atari_mouse_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SUN_MOUSE
id|sun_mouse_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PC110_PAD
id|pc110pad_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *&t;Only one watchdog can succeed. We probe the pcwatchdog first,&n; *&t;then the wdt cards and finally the software watchdog which always&n; *&t;works. This means if your hardware watchdog dies or is &squot;borrowed&squot;&n; *&t;for some reason the software watchdog still gives you some cover.&n; */
macro_line|#ifdef CONFIG_PCWATCHDOG
id|pcwatchdog_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_WDT
id|wdt_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ACQUIRE_WDT
id|acq_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SOFT_WATCHDOG
id|watchdog_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_APM
id|apm_bios_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_H8
id|h8_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_RTC
id|rtc_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATARI_DSP56K
id|dsp56k_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_HFMODEM
id|hfmodem_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_NVRAM
id|nvram_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MISC_RADIO
id|radio_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_HFMODEM
id|hfmodem_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* !MODULE */
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|MISC_MAJOR
comma
l_string|&quot;misc&quot;
comma
op_amp
id|misc_fops
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unable to get major %d for misc devices&bslash;n&quot;
comma
id|MISC_MAJOR
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
