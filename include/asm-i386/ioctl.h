multiline_comment|/* $Id: ioctl.h,v 1.5 1993/07/19 21:53:50 root Exp root $&n; *&n; * linux/ioctl.h for Linux by H.H. Bergman.&n; */
macro_line|#ifndef _ASMI386_IOCTL_H
DECL|macro|_ASMI386_IOCTL_H
mdefine_line|#define _ASMI386_IOCTL_H
macro_line|#include &lt;asm/page.h&gt;&t;&t;/* for PAGE_SIZE */
multiline_comment|/* ioctl command encoding: 32 bits total, command in lower 16 bits,&n; * size of the parameter structure in the lower 14 bits of the&n; * upper 16 bits.&n; * Encoding the size of the parameter structure in the ioctl request&n; * is useful for catching programs compiled with old versions&n; * and to avoid overwriting user space outside the user buffer area.&n; * The highest 2 bits are reserved for indicating the ``access mode&squot;&squot;.&n; * NOTE: This limits the max parameter size to 16kB -1 !&n; */
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
DECL|macro|IOCSIZE_MAX
mdefine_line|#define IOCSIZE_MAX&t;((PAGE_SIZE-1)&amp;(IOCSIZE_MASK &gt;&gt; IOCSIZE_SHIFT))
DECL|macro|IOCCMD_MASK
mdefine_line|#define IOCCMD_MASK&t;0x0000ffff&t;/* command code */
DECL|macro|IOCCMD_SHIFT
mdefine_line|#define IOCCMD_SHIFT&t;0
DECL|macro|IOCPARM_MASK
mdefine_line|#define IOCPARM_MASK IOCCMD_MASK
DECL|macro|IOCPARM_SHIFT
mdefine_line|#define IOCPARM_SHIFT IOCCMD_SHIFT
DECL|macro|IOC_SIZE
mdefine_line|#define IOC_SIZE(cmd)&t;(((cmd) &amp; IOCSIZE_MASK) &gt;&gt; IOCSIZE_SHIFT)
DECL|macro|IOCBASECMD
mdefine_line|#define IOCBASECMD(cmd)&t;((cmd) &amp; ~IOCPARM_MASK)
DECL|macro|IOCGROUP
mdefine_line|#define IOCGROUP(cmd)&t;(((cmd) &gt;&gt; 8) &amp; 0xFF)
multiline_comment|/* _IO(magic, subcode); size field is zero and the &n; * subcode determines the command.&n; */
DECL|macro|_IO
mdefine_line|#define _IO(c,d)&t;(IOC_VOID | ((c)&lt;&lt;8) | (d)) /* param encoded */
multiline_comment|/* _IOXX(magic, subcode, arg_t); where arg_t is the type of the&n; * (last) argument field in the ioctl call, if present.&n; */
DECL|macro|_IOW
mdefine_line|#define _IOW(c,d,t)&t;(IOC_IN | ((sizeof(t)&lt;&lt;16) &amp; IOCSIZE_MASK) | &bslash;&n;&t;&t;&t;&t;  ((c)&lt;&lt;8) | (d))
DECL|macro|_IOR
mdefine_line|#define _IOR(c,d,t)&t;(IOC_OUT | ((sizeof(t)&lt;&lt;16) &amp; IOCSIZE_MASK) | &bslash;&n;&t;&t;&t;&t;   ((c)&lt;&lt;8) | (d))
multiline_comment|/* WR rather than RW to avoid conflict with stdio.h */
DECL|macro|_IOWR
mdefine_line|#define _IOWR(c,d,t)&t;(IOC_INOUT | ((sizeof(t)&lt;&lt;16) &amp; IOCSIZE_MASK) | &bslash;&n;&t;&t;&t;&t;     ((c)&lt;&lt;8) | (d))
multiline_comment|/*&n; * The following is for compatibility across the various Linux&n; * platforms.  The i386 ioctl numbering scheme doesn&squot;t really enforce&n; * a type field.  De facto, however, the top 8 bits of the lower 16&n; * bits are indeed used as a type field, so we might just as well make&n; * this explicit here.  Please be sure to use the decoding macros&n; * below from now on.&n; */
DECL|macro|_IOC_NRBITS
mdefine_line|#define _IOC_NRBITS&t;8
DECL|macro|_IOC_TYPEBITS
mdefine_line|#define _IOC_TYPEBITS&t;8
DECL|macro|_IOC_SIZEBITS
mdefine_line|#define _IOC_SIZEBITS&t;14
DECL|macro|_IOC_DIRBITS
mdefine_line|#define _IOC_DIRBITS&t;2
DECL|macro|_IOC_NRMASK
mdefine_line|#define _IOC_NRMASK&t;((1 &lt;&lt; _IOC_NRBITS)-1)
DECL|macro|_IOC_TYPEMASK
mdefine_line|#define _IOC_TYPEMASK&t;((1 &lt;&lt; _IOC_TYPEBITS)-1)
DECL|macro|_IOC_SIZEMASK
mdefine_line|#define _IOC_SIZEMASK&t;((1 &lt;&lt; _IOC_SIZEBITS)-1)
DECL|macro|_IOC_DIRMASK
mdefine_line|#define _IOC_DIRMASK&t;((1 &lt;&lt; _IOC_DIRBITS)-1)
DECL|macro|_IOC_NRSHIFT
mdefine_line|#define _IOC_NRSHIFT&t;0
DECL|macro|_IOC_TYPESHIFT
mdefine_line|#define _IOC_TYPESHIFT&t;(_IOC_NRSHIFT+_IOC_NRBITS)
DECL|macro|_IOC_SIZESHIFT
mdefine_line|#define _IOC_SIZESHIFT&t;(_IOC_TYPESHIFT+_IOC_TYPEBITS)
DECL|macro|_IOC_DIRSHIFT
mdefine_line|#define _IOC_DIRSHIFT&t;(_IOC_SIZESHIFT+_IOC_SIZEBITS)
multiline_comment|/*&n; * Direction bits.&n; */
DECL|macro|_IOC_NONE
mdefine_line|#define _IOC_NONE&t;0U
DECL|macro|_IOC_READ
mdefine_line|#define _IOC_READ&t;1U
DECL|macro|_IOC_WRITE
mdefine_line|#define _IOC_WRITE&t;2U
multiline_comment|/* used to decode ioctl numbers.. */
DECL|macro|_IOC_DIR
mdefine_line|#define _IOC_DIR(nr)&t;&t;(((nr) &gt;&gt; _IOC_DIRSHIFT) &amp; _IOC_DIRMASK)
DECL|macro|_IOC_NR
mdefine_line|#define _IOC_NR(nr)&t;&t;(((nr) &gt;&gt; _IOC_NRSHIFT) &amp; _IOC_NRMASK)
DECL|macro|_IOC_SIZE
mdefine_line|#define _IOC_SIZE(nr)&t;&t;(((nr) &gt;&gt; _IOC_SIZESHIFT) &amp; _IOC_SIZEMASK)
macro_line|#endif /* _ASMI386_IOCTL_H */
eof
