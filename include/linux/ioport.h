multiline_comment|/*&n; * ioport.h&t;Definitions of routines for detecting, reserving and&n; *&t;&t;allocating system resources.&n; *&n; * Authors:&t;Linus Torvalds&n; */
macro_line|#ifndef _LINUX_IOPORT_H
DECL|macro|_LINUX_IOPORT_H
mdefine_line|#define _LINUX_IOPORT_H
DECL|macro|DEVICE_IO_NOTSET
mdefine_line|#define DEVICE_IO_NOTSET&t;(~0)
DECL|macro|DEVICE_IO_AUTO
mdefine_line|#define DEVICE_IO_AUTO&t;&t;((~0)-1)
DECL|macro|DEVICE_IO_FLAG_WRITEABLE
mdefine_line|#define DEVICE_IO_FLAG_WRITEABLE&t;(1&lt;&lt;0)
DECL|macro|DEVICE_IO_FLAG_CACHEABLE
mdefine_line|#define DEVICE_IO_FLAG_CACHEABLE&t;(1&lt;&lt;1)
DECL|macro|DEVICE_IO_FLAG_RANGELENGTH
mdefine_line|#define DEVICE_IO_FLAG_RANGELENGTH&t;(1&lt;&lt;2)
DECL|macro|DEVICE_IO_FLAG_SHADOWABLE
mdefine_line|#define DEVICE_IO_FLAG_SHADOWABLE&t;(1&lt;&lt;4)
DECL|macro|DEVICE_IO_FLAG_EXPANSIONROM
mdefine_line|#define DEVICE_IO_FLAG_EXPANSIONROM&t;(1&lt;&lt;5)
DECL|macro|DEVICE_IO_TYPE_8BIT
mdefine_line|#define DEVICE_IO_TYPE_8BIT&t;&t;0
DECL|macro|DEVICE_IO_TYPE_16BIT
mdefine_line|#define DEVICE_IO_TYPE_16BIT&t;&t;1
DECL|macro|DEVICE_IO_TYPE_8AND16BIT
mdefine_line|#define DEVICE_IO_TYPE_8AND16BIT&t;2
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
DECL|member|bits
r_int
r_char
id|bits
suffix:semicolon
multiline_comment|/* decoded bits */
DECL|member|fixed
r_int
r_char
id|fixed
suffix:semicolon
multiline_comment|/* fixed range */
DECL|member|hw_flags
r_int
r_int
id|hw_flags
suffix:semicolon
multiline_comment|/* hardware flags */
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
multiline_comment|/* region type */
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
multiline_comment|/*&n; * PCI-like IO resources have these defined flags.&n; * The low four bits come directly from the PCI specs,&n; * the rest are extended sw flags..&n; */
DECL|macro|IORESOURCE_IOPORT
mdefine_line|#define IORESOURCE_IOPORT&t;0x01&t;/* 0 - memory mapped, 1 - IO ports */
DECL|macro|IORESOURCE_MEMTYPE_MASK
mdefine_line|#define IORESOURCE_MEMTYPE_MASK&t;0x06&t;/* PCI-specific mapping info */
DECL|macro|IORESOURCE_PREFETCH
mdefine_line|#define IORESOURCE_PREFETCH&t;0x08&t;/* No side effects */
DECL|macro|IORESOURCE_BUSY
mdefine_line|#define IORESOURCE_BUSY&t;&t;0x10&t;/* Driver uses this resource */
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
