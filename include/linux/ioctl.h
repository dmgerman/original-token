multiline_comment|/* $Id: ioctl.h,v 1.2 1992/11/18 01:31:16 root Exp root $&n; *&n; * linux/ioctl.h for Linux by H.H. Bergman.&n; */
macro_line|#ifndef _LINUX_IOCTL_H
DECL|macro|_LINUX_IOCTL_H
mdefine_line|#define _LINUX_IOCTL_H
multiline_comment|/* ioctl command encoding: 32 bits total, command in lower 16 bits,&n; * size of the parameter structure in the upper 14 bits.&n; * Encoding size in ioctl request is useful for catching old versions&n; * and to avoid overwriting user space outside the user buffer area.&n; * The highest 2 bits are reserved.&n; * NOTE: This limits the max blocksize to 16kB -1 !&n; */
DECL|macro|IOC_VOID
mdefine_line|#define IOC_VOID&t;0x00000000&t;/* param in size field */
DECL|macro|IOC_IN
mdefine_line|#define IOC_IN&t;&t;0x40000000&t;/* user --&gt; kernel */
DECL|macro|IOC_OUT
mdefine_line|#define IOC_OUT&t;&t;0x80000000&t;/* kernel --&gt; user */
DECL|macro|IOC_INOUT
mdefine_line|#define IOC_INOUT&t;(IOC_IN | IOC_OUT)&t;/* both */
DECL|macro|IOCSIZE_MASK
mdefine_line|#define IOCSIZE_MASK&t;0x3fff0000&t;/* size (max 16k-1 bytes) */
DECL|macro|IOCSIZE_SHIFT
mdefine_line|#define IOCSIZE_SHIFT&t;16&t;&t;/* how to get the size */
DECL|macro|IOCCMD_MASK
mdefine_line|#define IOCCMD_MASK&t;0x0000ffff&t;/* command code */
DECL|macro|IOCCMD_SHIFT
mdefine_line|#define IOCCMD_SHIFT&t;0
DECL|macro|_IO
mdefine_line|#define _IO(c,d)&t;(IOC_VOID | ((d)&lt;&lt;16) | c) /* param encoded */
multiline_comment|/* use _IOXX(magic, subcode, arg_t) where arg_t is the type of the&n; * (last) argument field in the ioctl call, if present.&n; */
DECL|macro|_IOW
mdefine_line|#define _IOW(c,d,t)&t;(IOC_IN | ((sizeof(t)&lt;&lt;16) &amp; IOCSIZE_MASK) | &bslash;&n;&t;&t;&t;&t;  (c&lt;&lt;8) | d)
DECL|macro|_IOR
mdefine_line|#define _IOR(c,d,t)&t;(IOC_OUT | ((sizeof(t)&lt;&lt;16) &amp; IOCSIZE_MASK) | &bslash;&n;&t;&t;&t;&t;   (c&lt;&lt;8) | d)
multiline_comment|/* WR rather than RW to avoid conflict with stdio.h */
DECL|macro|_IOWR
mdefine_line|#define _IOWR(c,d,t)&t;(IOC_INOUT | ((sizeof(t)&lt;&lt;16) &amp; IOCSIZE_MASK) | &bslash;&n;&t;&t;&t;&t;     (c&lt;&lt;8) | d)
macro_line|#endif /* _LINUX_IOCTL_H */
eof
