multiline_comment|/*&n; * ioport.h&t;Definitions of routines for detecting, reserving and&n; *&t;&t;allocating system resources.&n; *&n; * Authors:&t;Linus Torvalds&n; */
macro_line|#ifndef _LINUX_IOPORT_H
DECL|macro|_LINUX_IOPORT_H
mdefine_line|#define _LINUX_IOPORT_H
multiline_comment|/*&n; * Resources are tree-like, allowing&n; * nesting etc..&n; */
DECL|struct|resource
r_struct
id|resource
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|start
DECL|member|end
r_int
r_int
id|start
comma
id|end
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|parent
DECL|member|sibling
DECL|member|child
r_struct
id|resource
op_star
id|parent
comma
op_star
id|sibling
comma
op_star
id|child
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * IO resources have these defined flags.&n; */
DECL|macro|IORESOURCE_BITS
mdefine_line|#define IORESOURCE_BITS&t;&t;0x000000ff&t;/* Bus-specific bits */
DECL|macro|IORESOURCE_IO
mdefine_line|#define IORESOURCE_IO&t;&t;0x00000100&t;/* Resource type */
DECL|macro|IORESOURCE_MEM
mdefine_line|#define IORESOURCE_MEM&t;&t;0x00000200
DECL|macro|IORESOURCE_IRQ
mdefine_line|#define IORESOURCE_IRQ&t;&t;0x00000400
DECL|macro|IORESOURCE_DMA
mdefine_line|#define IORESOURCE_DMA&t;&t;0x00000800
DECL|macro|IORESOURCE_PREFETCH
mdefine_line|#define IORESOURCE_PREFETCH&t;0x00001000&t;/* No side effects */
DECL|macro|IORESOURCE_READONLY
mdefine_line|#define IORESOURCE_READONLY&t;0x00002000
DECL|macro|IORESOURCE_CACHEABLE
mdefine_line|#define IORESOURCE_CACHEABLE&t;0x00004000
DECL|macro|IORESOURCE_RANGELENGTH
mdefine_line|#define IORESOURCE_RANGELENGTH&t;0x00008000
DECL|macro|IORESOURCE_SHADOWABLE
mdefine_line|#define IORESOURCE_SHADOWABLE&t;0x00010000
DECL|macro|IORESOURCE_UNSET
mdefine_line|#define IORESOURCE_UNSET&t;0x00020000
DECL|macro|IORESOURCE_AUTO
mdefine_line|#define IORESOURCE_AUTO&t;&t;0x00040000
DECL|macro|IORESOURCE_BUSY
mdefine_line|#define IORESOURCE_BUSY&t;&t;0x80000000&t;/* Driver has marked this resource busy */
multiline_comment|/* PC/ISA/whatever - the normal PC address spaces: IO and memory */
r_extern
r_struct
id|resource
id|ioport_resource
suffix:semicolon
r_extern
r_struct
id|resource
id|iomem_resource
suffix:semicolon
r_extern
r_int
id|get_resource_list
c_func
(paren
r_struct
id|resource
op_star
comma
r_char
op_star
id|buf
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|request_resource
c_func
(paren
r_struct
id|resource
op_star
id|root
comma
r_struct
id|resource
op_star
r_new
)paren
suffix:semicolon
r_extern
r_int
id|release_resource
c_func
(paren
r_struct
id|resource
op_star
r_new
)paren
suffix:semicolon
multiline_comment|/* Convenience shorthand with allocation */
DECL|macro|request_region
mdefine_line|#define request_region(start,n,name)&t;__request_region(&amp;ioport_resource, (start), (n), (name))
r_extern
r_struct
id|resource
op_star
id|__request_region
c_func
(paren
r_struct
id|resource
op_star
comma
r_int
r_int
id|start
comma
r_int
r_int
id|n
comma
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/* Compatibility cruft */
DECL|macro|check_region
mdefine_line|#define check_region(start,n)&t;__check_region(&amp;ioport_resource, (start), (n))
DECL|macro|release_region
mdefine_line|#define release_region(start,n)&t;__release_region(&amp;ioport_resource, (start), (n))
r_extern
r_int
id|__check_region
c_func
(paren
r_struct
id|resource
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|__release_region
c_func
(paren
r_struct
id|resource
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|get_ioport_list
mdefine_line|#define get_ioport_list(buf)&t;get_resource_list(&amp;ioport_resource, buf, PAGE_SIZE)
DECL|macro|get_mem_list
mdefine_line|#define get_mem_list(buf)&t;get_resource_list(&amp;iomem_resource, buf, PAGE_SIZE)
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
