multiline_comment|/* $Id: irixioctl.c,v 1.2 1997/08/08 18:12:19 miguel Exp $&n; * irixioctl.c: A fucking mess...&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ioctl.h&gt;
macro_line|#include &lt;asm/ioctls.h&gt;
DECL|macro|DEBUG_IOCTLS
macro_line|#undef DEBUG_IOCTLS
DECL|struct|irix_termios
r_struct
id|irix_termios
(brace
DECL|member|c_iflag
DECL|member|c_oflag
DECL|member|c_cflag
DECL|member|c_lflag
id|tcflag_t
id|c_iflag
comma
id|c_oflag
comma
id|c_cflag
comma
id|c_lflag
suffix:semicolon
DECL|member|c_cc
id|cc_t
id|c_cc
(braket
id|NCCS
)braket
suffix:semicolon
)brace
suffix:semicolon
r_extern
id|asmlinkage
r_int
id|sys_ioctl
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_int
id|sys_write
c_func
(paren
r_int
r_int
id|fd
comma
r_char
op_star
id|buf
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|start_tty
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
DECL|function|get_tty
r_static
r_struct
id|tty_struct
op_star
id|get_tty
c_func
(paren
r_int
id|fd
)paren
(brace
r_struct
id|file
op_star
id|filp
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_ge
id|NR_OPEN
op_logical_or
op_logical_neg
(paren
id|filp
op_assign
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
)paren
)paren
(brace
r_return
(paren
(paren
r_struct
id|tty_struct
op_star
)paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filp-&gt;private_data
)paren
(brace
r_struct
id|tty_struct
op_star
id|ttyp
op_assign
(paren
r_struct
id|tty_struct
op_star
)paren
id|filp-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|ttyp-&gt;magic
op_eq
id|TTY_MAGIC
)paren
(brace
r_return
id|ttyp
suffix:semicolon
)brace
)brace
r_return
(paren
(paren
r_struct
id|tty_struct
op_star
)paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|get_real_tty
r_static
r_struct
id|tty_struct
op_star
id|get_real_tty
c_func
(paren
r_struct
id|tty_struct
op_star
id|tp
)paren
(brace
r_if
c_cond
(paren
id|tp-&gt;driver.type
op_eq
id|TTY_DRIVER_TYPE_PTY
op_logical_and
id|tp-&gt;driver.subtype
op_eq
id|PTY_TYPE_MASTER
)paren
(brace
r_return
id|tp-&gt;link
suffix:semicolon
)brace
r_else
r_return
id|tp
suffix:semicolon
)brace
DECL|function|irix_ioctl
id|asmlinkage
r_int
id|irix_ioctl
c_func
(paren
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|tty_struct
op_star
id|tp
comma
op_star
id|rtp
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_int
id|old_fs
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;[%s:%d] irix_ioctl(%d, &quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|fd
)paren
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
l_int|0x00005401
suffix:colon
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;TCGETA, %08lx) &quot;
comma
id|arg
)paren
suffix:semicolon
macro_line|#endif
id|error
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|TCGETA
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0000540d
suffix:colon
(brace
r_struct
id|termios
id|kt
suffix:semicolon
r_struct
id|irix_termios
op_star
id|it
op_assign
(paren
r_struct
id|irix_termios
op_star
)paren
id|arg
suffix:semicolon
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;TCGETS, %08lx) &quot;
comma
id|arg
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|it
comma
r_sizeof
(paren
op_star
id|it
)paren
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
id|error
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|TCGETS
comma
(paren
r_int
r_int
)paren
op_amp
id|kt
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_break
suffix:semicolon
)brace
id|__put_user
c_func
(paren
id|kt.c_iflag
comma
op_amp
id|it-&gt;c_iflag
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|kt.c_oflag
comma
op_amp
id|it-&gt;c_oflag
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|kt.c_cflag
comma
op_amp
id|it-&gt;c_cflag
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|kt.c_lflag
comma
op_amp
id|it-&gt;c_lflag
)paren
suffix:semicolon
r_for
c_loop
(paren
id|error
op_assign
l_int|0
suffix:semicolon
id|error
OL
id|NCCS
suffix:semicolon
id|error
op_increment
)paren
(brace
id|__put_user
c_func
(paren
id|kt.c_cc
(braket
id|error
)braket
comma
op_amp
id|it-&gt;c_cc
(braket
id|error
)braket
)paren
suffix:semicolon
)brace
id|error
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
l_int|0x0000540e
suffix:colon
(brace
r_struct
id|termios
id|kt
suffix:semicolon
r_struct
id|irix_termios
op_star
id|it
op_assign
(paren
r_struct
id|irix_termios
op_star
)paren
id|arg
suffix:semicolon
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;TCSETS, %08lx) &quot;
comma
id|arg
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|it
comma
r_sizeof
(paren
op_star
id|it
)paren
)paren
)paren
(brace
id|error
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
id|error
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|TCGETS
comma
(paren
r_int
r_int
)paren
op_amp
id|kt
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
r_break
suffix:semicolon
)brace
id|__get_user
c_func
(paren
id|kt.c_iflag
comma
op_amp
id|it-&gt;c_iflag
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|kt.c_oflag
comma
op_amp
id|it-&gt;c_oflag
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|kt.c_cflag
comma
op_amp
id|it-&gt;c_cflag
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|kt.c_lflag
comma
op_amp
id|it-&gt;c_lflag
)paren
suffix:semicolon
r_for
c_loop
(paren
id|error
op_assign
l_int|0
suffix:semicolon
id|error
OL
id|NCCS
suffix:semicolon
id|error
op_increment
)paren
(brace
id|__get_user
c_func
(paren
id|kt.c_cc
(braket
id|error
)braket
comma
op_amp
id|it-&gt;c_cc
(braket
id|error
)braket
)paren
suffix:semicolon
)brace
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
id|error
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|TCSETS
comma
(paren
r_int
r_int
)paren
op_amp
id|kt
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
l_int|0x0000540f
suffix:colon
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;TCSETSW, %08lx) &quot;
comma
id|arg
)paren
suffix:semicolon
macro_line|#endif
id|error
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|TCSETSW
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x00005471
suffix:colon
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;TIOCNOTTY, %08lx) &quot;
comma
id|arg
)paren
suffix:semicolon
macro_line|#endif
id|error
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|TIOCNOTTY
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x00007416
suffix:colon
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;TIOCGSID, %08lx) &quot;
comma
id|arg
)paren
suffix:semicolon
macro_line|#endif
id|tp
op_assign
id|get_tty
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tp
)paren
(brace
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|rtp
op_assign
id|get_real_tty
c_func
(paren
id|tp
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;rtp-&gt;session=%d &quot;
comma
id|rtp-&gt;session
)paren
suffix:semicolon
macro_line|#endif
id|error
op_assign
id|put_user
c_func
(paren
id|rtp-&gt;session
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x746e
suffix:colon
multiline_comment|/* TIOCSTART, same effect as hitting ^Q */
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;TIOCSTART, %08lx) &quot;
comma
id|arg
)paren
suffix:semicolon
macro_line|#endif
id|tp
op_assign
id|get_tty
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tp
)paren
(brace
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|rtp
op_assign
id|get_real_tty
c_func
(paren
id|tp
)paren
suffix:semicolon
id|start_tty
c_func
(paren
id|rtp
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x20006968
suffix:colon
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;SIOCGETLABEL, %08lx) &quot;
comma
id|arg
)paren
suffix:semicolon
macro_line|#endif
id|error
op_assign
op_minus
id|ENOPKG
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x40047477
suffix:colon
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;TIOCGPGRP, %08lx) &quot;
comma
id|arg
)paren
suffix:semicolon
macro_line|#endif
id|error
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|TIOCGPGRP
comma
id|arg
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;arg=%d &quot;
comma
op_star
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_case
l_int|0x40087468
suffix:colon
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;TIOCGWINSZ, %08lx) &quot;
comma
id|arg
)paren
suffix:semicolon
macro_line|#endif
id|error
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|TIOCGWINSZ
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x8004667e
suffix:colon
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;FIONBIO, %08lx) arg=%d &quot;
comma
id|arg
comma
op_star
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
macro_line|#endif
id|error
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|FIONBIO
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x80047476
suffix:colon
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;TIOCSPGRP, %08lx) arg=%d &quot;
comma
id|arg
comma
op_star
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
macro_line|#endif
id|error
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|TIOCSPGRP
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x8020690c
suffix:colon
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;SIOCSIFADDR, %08lx) arg=%d &quot;
comma
id|arg
comma
op_star
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
macro_line|#endif
id|error
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCSIFADDR
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x80206910
suffix:colon
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;SIOCSIFFLAGS, %08lx) arg=%d &quot;
comma
id|arg
comma
op_star
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
macro_line|#endif
id|error
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCSIFFLAGS
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xc0206911
suffix:colon
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;SIOCGIFFLAGS, %08lx) arg=%d &quot;
comma
id|arg
comma
op_star
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
macro_line|#endif
id|error
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCGIFFLAGS
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xc020691b
suffix:colon
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;SIOCGIFMETRIC, %08lx) arg=%d &quot;
comma
id|arg
comma
op_star
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
macro_line|#endif
id|error
op_assign
id|sys_ioctl
c_func
(paren
id|fd
comma
id|SIOCGIFMETRIC
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
(brace
r_char
op_star
id|msg
op_assign
l_string|&quot;Unimplemented IOCTL cmd tell dm@engr.sgi.com&bslash;n&quot;
suffix:semicolon
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;UNIMP_IOCTL, %08lx)&bslash;n&quot;
comma
id|arg
)paren
suffix:semicolon
macro_line|#endif
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
id|sys_write
c_func
(paren
l_int|2
comma
id|msg
comma
id|strlen
c_func
(paren
id|msg
)paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;[%s:%d] Does unimplemented IRIX ioctl cmd %08lx&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|cmd
)paren
suffix:semicolon
id|do_exit
c_func
(paren
l_int|255
)paren
suffix:semicolon
)brace
)brace
suffix:semicolon
macro_line|#ifdef DEBUG_IOCTLS
id|printk
c_func
(paren
l_string|&quot;error=%d&bslash;n&quot;
comma
id|error
)paren
suffix:semicolon
macro_line|#endif
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
eof
