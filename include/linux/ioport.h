multiline_comment|/*&n; * portio.h&t;Definitions of routines for detecting, reserving and&n; *&t;&t;allocating system resources.&n; *&n; * Version:&t;0.01&t;8/30/93&n; *&n; * Author:&t;Donald Becker (becker@super.org)&n; */
macro_line|#ifndef _LINUX_PORTIO_H
DECL|macro|_LINUX_PORTIO_H
mdefine_line|#define _LINUX_PORTIO_H
DECL|macro|HAVE_PORTRESERVE
mdefine_line|#define HAVE_PORTRESERVE
multiline_comment|/*&n; * Call check_region() before probing for your hardware.&n; * Once you have found you hardware, register it with snarf_region().&n; * If you unload the driver, use release_region to free ports.&n; */
r_extern
r_void
id|reserve_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
r_extern
r_int
id|check_region
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|extent
)paren
suffix:semicolon
r_extern
r_void
id|snarf_region
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|extent
)paren
suffix:semicolon
r_extern
r_void
id|register_iomem
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|extent
comma
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|release_region
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|extent
)paren
suffix:semicolon
r_extern
r_int
id|get_ioport_list
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
DECL|macro|HAVE_AUTOIRQ
mdefine_line|#define HAVE_AUTOIRQ
r_extern
r_void
op_star
id|irq2dev_map
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Use only if you own the IRQ. */
r_extern
r_void
id|autoirq_setup
c_func
(paren
r_int
id|waittime
)paren
suffix:semicolon
r_extern
r_int
id|autoirq_report
c_func
(paren
r_int
id|waittime
)paren
suffix:semicolon
macro_line|#endif&t;/* _LINUX_PORTIO_H */
eof
