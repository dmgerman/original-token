multiline_comment|/*&n; * sercons.c&n; *      choose the right serial device at boot time&n; *&n; * triemer 6-SEP-1998&n; *      sercons.c is designed to allow the three different kinds &n; *      of serial devices under the decstation world to co-exist&n; *      in the same kernel.  The idea here is to abstract &n; *      the pieces of the drivers that are common to this file&n; *      so that they do not clash at compile time and runtime.&n; *&n; * HK 16-SEP-1998 v0.002&n; *      removed the PROM console as this is not a real serial&n; *      device. Added support for PROM console in drivers/char/tty_io.c&n; *      instead. Although it may work to enable more than one &n; *      console device I strongly recommend to use only one.&n; */
macro_line|#include &lt;asm/init.h&gt;
macro_line|#include &lt;asm/dec/machtype.h&gt;
macro_line|#ifdef CONFIG_ZS
r_extern
r_int
id|zs_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DZ
r_extern
r_int
id|dz_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SERIAL_CONSOLE
macro_line|#ifdef CONFIG_ZS
r_extern
r_int
id|zs_serial_console_init
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DZ
r_extern
r_int
id|dz_serial_console_init
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/* rs_init - starts up the serial interface -&n;   handle normal case of starting up the serial interface */
macro_line|#ifdef CONFIG_SERIAL
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|rs_init
c_func
(paren
r_void
)paren
)paren
(brace
macro_line|#if defined(CONFIG_ZS) &amp;&amp; defined(CONFIG_DZ)
r_if
c_cond
(paren
id|IOASIC
)paren
r_return
id|zs_init
c_func
(paren
)paren
suffix:semicolon
r_else
r_return
id|dz_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
macro_line|#ifdef CONFIG_ZS
r_return
id|zs_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DZ
r_return
id|dz_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_SERIAL_CONSOLE
multiline_comment|/* serial_console_init handles the special case of starting&n; *   up the console on the serial port&n; */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|serial_console_init
c_func
(paren
r_int
id|kmem_start
comma
r_int
id|kmem_end
)paren
)paren
(brace
macro_line|#if defined(CONFIG_ZS) &amp;&amp; defined(CONFIG_DZ)
r_if
c_cond
(paren
id|IOASIC
)paren
id|kmem_start
op_assign
id|zs_serial_console_init
c_func
(paren
id|kmem_start
comma
id|kmem_end
)paren
suffix:semicolon
r_else
id|kmem_start
op_assign
id|dz_serial_console_init
c_func
(paren
id|kmem_start
comma
id|kmem_end
)paren
suffix:semicolon
macro_line|#else
macro_line|#ifdef CONFIG_ZS
id|kmem_start
op_assign
id|zs_serial_console_init
c_func
(paren
id|kmem_start
comma
id|kmem_end
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DZ
id|kmem_start
op_assign
id|dz_serial_console_init
c_func
(paren
id|kmem_start
comma
id|kmem_end
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
r_return
id|kmem_start
suffix:semicolon
)brace
macro_line|#endif
eof
