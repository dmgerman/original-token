macro_line|#ifdef __KERNEL__
multiline_comment|/* Compatibility for various Linux kernel versions */
macro_line|#ifndef _LINUX_ISDN_COMPAT_H
DECL|macro|_LINUX_ISDN_COMPAT_H
mdefine_line|#define _LINUX_ISDN_COMPAT_H
macro_line|#ifndef LINUX_VERSION_CODE
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif
macro_line|#ifndef KERNEL_VERSION
DECL|macro|KERNEL_VERSION
mdefine_line|#define KERNEL_VERSION(x,y,z) (((x)&lt;&lt;16)+((y)&lt;&lt;8)+(z))
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,1,0)
macro_line|#include &lt;linux/mm.h&gt;
DECL|macro|ioremap
mdefine_line|#define ioremap vremap
DECL|macro|ioremap_nocache
mdefine_line|#define ioremap_nocache vremap
DECL|macro|iounmap
mdefine_line|#define iounmap vfree
DECL|function|copy_from_user
r_static
r_inline
r_int
r_int
id|copy_from_user
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
r_int
id|n
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|from
comma
id|n
)paren
)paren
op_ne
l_int|0
)paren
r_return
id|i
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|copy_to_user
r_static
r_inline
r_int
r_int
id|copy_to_user
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
r_int
id|n
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|to
comma
id|n
)paren
)paren
op_ne
l_int|0
)paren
r_return
id|i
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|GET_USER
mdefine_line|#define GET_USER(x, addr) ( x = get_user(addr) )
macro_line|#ifdef __alpha__ /* needed for 2.0.x with alpha-patches */
DECL|macro|RWTYPE
mdefine_line|#define RWTYPE long
DECL|macro|LSTYPE
mdefine_line|#define LSTYPE long
DECL|macro|RWARG
mdefine_line|#define RWARG unsigned long
macro_line|#else
DECL|macro|RWTYPE
mdefine_line|#define RWTYPE int
DECL|macro|LSTYPE
mdefine_line|#define LSTYPE int
DECL|macro|RWARG
mdefine_line|#define RWARG int
macro_line|#endif
DECL|macro|LSARG
mdefine_line|#define LSARG off_t
macro_line|#else
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|GET_USER
mdefine_line|#define GET_USER get_user
DECL|macro|PUT_USER
mdefine_line|#define PUT_USER put_user
DECL|macro|RWTYPE
mdefine_line|#define RWTYPE long
DECL|macro|LSTYPE
mdefine_line|#define LSTYPE long long
DECL|macro|RWARG
mdefine_line|#define RWARG unsigned long
DECL|macro|LSARG
mdefine_line|#define LSARG long long
macro_line|#endif /* LINUX_VERSION_CODE */
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,1,15)
DECL|macro|SET_SKB_FREE
mdefine_line|#define SET_SKB_FREE(x) ( x-&gt;free = 1 )
DECL|macro|idev_kfree_skb
mdefine_line|#define idev_kfree_skb(a,b) dev_kfree_skb(a,b)
macro_line|#else
DECL|macro|SET_SKB_FREE
mdefine_line|#define SET_SKB_FREE(x)
DECL|macro|idev_kfree_skb
mdefine_line|#define idev_kfree_skb(a,b) dev_kfree_skb(a)
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,1,18)
DECL|macro|COMPAT_HAS_NEW_SYMTAB
mdefine_line|#define COMPAT_HAS_NEW_SYMTAB
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,1,31)
DECL|macro|CLOSETYPE
mdefine_line|#define CLOSETYPE void
DECL|macro|CLOSEVAL
mdefine_line|#define CLOSEVAL
macro_line|#else
DECL|macro|CLOSETYPE
mdefine_line|#define CLOSETYPE int
DECL|macro|CLOSEVAL
mdefine_line|#define CLOSEVAL (0)
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,1,37)
DECL|macro|test_and_clear_bit
mdefine_line|#define test_and_clear_bit clear_bit
DECL|macro|test_and_set_bit
mdefine_line|#define test_and_set_bit set_bit
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,1,81)
DECL|macro|kstat_irqs
mdefine_line|#define kstat_irqs( PAR ) kstat.interrupts[PAR]
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,1,91)
DECL|macro|COMPAT_HAS_NEW_PCI
mdefine_line|#define COMPAT_HAS_NEW_PCI
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,13)
DECL|macro|get_pcibase
mdefine_line|#define get_pcibase(ps, nr) ps-&gt;base_address[nr]
macro_line|#else
DECL|macro|get_pcibase
mdefine_line|#define get_pcibase(ps, nr) ps-&gt;resource[nr].start
macro_line|#endif
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,1,127)
DECL|macro|schedule_timeout
mdefine_line|#define schedule_timeout(a) current-&gt;timeout = jiffies + (a); schedule ();
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,3,0)
DECL|macro|COMPAT_HAS_NEW_WAITQ
mdefine_line|#define COMPAT_HAS_NEW_WAITQ
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt; KERNEL_VERSION(2,3,12)
DECL|macro|COMPAT_HAS_NEW_SETUP
mdefine_line|#define COMPAT_HAS_NEW_SETUP
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,14)
DECL|macro|net_device
mdefine_line|#define net_device device
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_ISDN_COMPAT_H */
eof
