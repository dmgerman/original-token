multiline_comment|/*&n; * ioport.h&t;Definitions of routines for detecting, reserving and&n; *&t;&t;allocating system resources.&n; *&n; * Authors:&t;Donald Becker (becker@cesdis.gsfc.nasa.gov)&n; *&t;&t;David Hinds (dhinds@zen.stanford.edu)&n; */
macro_line|#ifndef _LINUX_IOPORT_H
DECL|macro|_LINUX_IOPORT_H
mdefine_line|#define _LINUX_IOPORT_H
DECL|macro|RES_IO
mdefine_line|#define RES_IO&t;&t;0
DECL|macro|RES_MEM
mdefine_line|#define RES_MEM&t;&t;1
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
r_struct
id|resource_entry
op_star
id|iolist
comma
op_star
id|memlist
suffix:semicolon
r_extern
r_int
id|get_resource_list
c_func
(paren
r_int
r_class
comma
r_char
op_star
id|buf
)paren
suffix:semicolon
r_extern
r_int
id|check_resource
c_func
(paren
r_int
r_class
comma
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
id|request_resource
c_func
(paren
r_int
r_class
comma
r_int
r_int
id|from
comma
r_int
r_int
id|extent
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|release_resource
c_func
(paren
r_int
r_class
comma
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
r_int
id|occupy_resource
c_func
(paren
r_int
r_class
comma
r_int
r_int
id|base
comma
r_int
r_int
id|end
comma
r_int
r_int
id|num
comma
r_int
r_int
id|align
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|vacate_resource
c_func
(paren
r_int
r_class
comma
r_int
r_int
id|from
comma
r_int
r_int
id|extent
)paren
suffix:semicolon
DECL|macro|get_ioport_list
mdefine_line|#define get_ioport_list(buf)&t;get_resource_list(RES_IO, buf)
DECL|macro|get_mem_list
mdefine_line|#define get_mem_list(buf)&t;get_resource_list(RES_MEM, buf)
DECL|macro|HAVE_PORTRESERVE
mdefine_line|#define HAVE_PORTRESERVE
multiline_comment|/*&n; * Call check_region() before probing for your hardware.&n; * Once you have found you hardware, register it with request_region().&n; * If you unload the driver, use release_region to free ports.&n; */
DECL|macro|check_region
mdefine_line|#define check_region(f,e)&t;&t;check_resource(RES_IO,f,e)
DECL|macro|request_region
mdefine_line|#define request_region(f,e,n)&t;&t;request_resource(RES_IO,f,e,n)
DECL|macro|release_region
mdefine_line|#define release_region(f,e)&t;&t;release_resource(RES_IO,f,e)
DECL|macro|occupy_region
mdefine_line|#define occupy_region(b,e,n,a,s)&t;occupy_resource(RES_IO,b,e,n,a,s)
DECL|macro|vacate_region
mdefine_line|#define vacate_region(f,e)&t;&t;vacate_resource(RES_IO,f,e)
DECL|macro|HAVE_MEMRESERVE
mdefine_line|#define HAVE_MEMRESERVE
DECL|macro|check_mem_region
mdefine_line|#define check_mem_region(f,e)&t;&t;check_resource(RES_MEM,f,e)
DECL|macro|request_mem_region
mdefine_line|#define request_mem_region(f,e,n)&t;request_resource(RES_MEM,f,e,n)
DECL|macro|release_mem_region
mdefine_line|#define release_mem_region(f,e)&t;&t;release_resource(RES_MEM,f,e)
DECL|macro|occupy_mem_region
mdefine_line|#define occupy_mem_region(b,e,n,a,s)&t;occupy_resource(RES_MEM,b,e,n,a,s)
DECL|macro|vacate_mem_region
mdefine_line|#define vacate_mem_region(f,e)&t;&t;vacate_resource(RES_MEM,f,e)
DECL|macro|HAVE_AUTOIRQ
mdefine_line|#define HAVE_AUTOIRQ
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
macro_line|#endif&t;/* _LINUX_IOPORT_H */
eof
