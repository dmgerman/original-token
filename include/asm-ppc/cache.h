multiline_comment|/*&n; * include/asm-ppc/cache.h&n; */
macro_line|#ifndef __ARCH_PPC_CACHE_H
DECL|macro|__ARCH_PPC_CACHE_H
mdefine_line|#define __ARCH_PPC_CACHE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*#include &lt;asm/system.h&gt;*/
multiline_comment|/* bytes per L1 cache line */
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define        L1_CACHE_BYTES  32      
DECL|macro|L1_CACHE_ALIGN
mdefine_line|#define        L1_CACHE_ALIGN(x)       (((x)+(L1_CACHE_BYTES-1))&amp;~(L1_CACHE_BYTES-1))
DECL|macro|L1_CACHE_PAGES
mdefine_line|#define L1_CACHE_PAGES&t;&t;8
macro_line|#if defined(__KERNEL__) &amp;&amp; !defined(__ASSEMBLY__)
DECL|function|unlock_dcache
r_static
r_inline
r_int
r_int
id|unlock_dcache
c_func
(paren
r_void
)paren
(brace
macro_line|#ifndef CONFIG_8xx&t;
id|ulong
id|hid0
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* 601 doesn&squot;t do this */
r_if
c_cond
(paren
(paren
id|ulong
)paren
id|_get_PVR
c_func
(paren
)paren
op_eq
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;mfspr %0,1008 &bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|hid0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|hid0
op_amp
id|HID0_DLOCK
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;mtspr 1008,%0 &bslash;n&bslash;t&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|hid0
op_amp
op_complement
(paren
id|HID0_DLOCK
)paren
)paren
)paren
suffix:semicolon
r_return
(paren
id|hid0
op_amp
id|HID0_DLOCK
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
macro_line|#else /* ndef CONFIG_8xx */
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
DECL|function|lock_dcache
r_static
r_inline
r_void
id|lock_dcache
c_func
(paren
r_int
r_int
id|lockit
)paren
(brace
macro_line|#ifndef CONFIG_8xx
multiline_comment|/* 601 doesn&squot;t do this */
r_if
c_cond
(paren
op_logical_neg
id|lockit
op_logical_or
(paren
(paren
id|ulong
)paren
id|_get_PVR
c_func
(paren
)paren
op_eq
l_int|1
)paren
)paren
r_return
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;mfspr&t;%0,1008 &bslash;n&bslash;t&quot;
l_string|&quot;ori&t;%0,%0,%2 &bslash;n&bslash;t&quot;
l_string|&quot;mtspr&t;1008,%0 &bslash;n&bslash;t&quot;
l_string|&quot;sync &bslash;n&bslash;t isync &bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|lockit
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|lockit
)paren
comma
l_string|&quot;i&quot;
(paren
id|HID0_DLOCK
)paren
)paren
suffix:semicolon
macro_line|#endif /* ndef CONFIG_8xx */
)brace
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* prep registers for L2 */
DECL|macro|CACHECRBA
mdefine_line|#define CACHECRBA       0x80000823      /* Cache configuration register address */
DECL|macro|L2CACHE_MASK
mdefine_line|#define L2CACHE_MASK&t;0x03&t;/* Mask for 2 L2 Cache bits */
DECL|macro|L2CACHE_512KB
mdefine_line|#define L2CACHE_512KB&t;0x00&t;/* 512KB */
DECL|macro|L2CACHE_256KB
mdefine_line|#define L2CACHE_256KB&t;0x01&t;/* 256KB */
DECL|macro|L2CACHE_1MB
mdefine_line|#define L2CACHE_1MB&t;0x02&t;/* 1MB */
DECL|macro|L2CACHE_NONE
mdefine_line|#define L2CACHE_NONE&t;0x03&t;/* NONE */
DECL|macro|L2CACHE_PARITY
mdefine_line|#define L2CACHE_PARITY  0x08    /* Mask for L2 Cache Parity Protected bit */
macro_line|#ifdef CONFIG_8xx
multiline_comment|/* Cache control on the MPC8xx is provided through some additional&n; * special purpose registers.&n; */
DECL|macro|IC_CST
mdefine_line|#define IC_CST&t;&t;560&t;/* Instruction cache control/status */
DECL|macro|IC_ADR
mdefine_line|#define IC_ADR&t;&t;561&t;/* Address needed for some commands */
DECL|macro|IC_DAT
mdefine_line|#define IC_DAT&t;&t;562&t;/* Read-only data register */
DECL|macro|DC_CST
mdefine_line|#define DC_CST&t;&t;568&t;/* Data cache control/status */
DECL|macro|DC_ADR
mdefine_line|#define DC_ADR&t;&t;569&t;/* Address needed for some commands */
DECL|macro|DC_DAT
mdefine_line|#define DC_DAT&t;&t;570&t;/* Read-only data register */
multiline_comment|/* Commands.  Only the first few are available to the instruction cache.&n;*/
DECL|macro|IDC_ENABLE
mdefine_line|#define&t;IDC_ENABLE&t;0x02000000&t;/* Cache enable */
DECL|macro|IDC_DISABLE
mdefine_line|#define IDC_DISABLE&t;0x04000000&t;/* Cache disable */
DECL|macro|IDC_LDLCK
mdefine_line|#define IDC_LDLCK&t;0x06000000&t;/* Load and lock */
DECL|macro|IDC_UNLINE
mdefine_line|#define IDC_UNLINE&t;0x08000000&t;/* Unlock line */
DECL|macro|IDC_UNALL
mdefine_line|#define IDC_UNALL&t;0x0a000000&t;/* Unlock all */
DECL|macro|IDC_INVALL
mdefine_line|#define IDC_INVALL&t;0x0c000000&t;/* Invalidate all */
DECL|macro|DC_FLINE
mdefine_line|#define DC_FLINE&t;0x0e000000&t;/* Flush data cache line */
DECL|macro|DC_SFWT
mdefine_line|#define DC_SFWT&t;&t;0x01000000&t;/* Set forced writethrough mode */
DECL|macro|DC_CFWT
mdefine_line|#define DC_CFWT&t;&t;0x03000000&t;/* Clear forced writethrough mode */
DECL|macro|DC_SLES
mdefine_line|#define DC_SLES&t;&t;0x05000000&t;/* Set little endian swap mode */
DECL|macro|DC_CLES
mdefine_line|#define DC_CLES&t;&t;0x07000000&t;/* Clear little endian swap mode */
multiline_comment|/* Status.&n;*/
DECL|macro|IDC_ENABLED
mdefine_line|#define IDC_ENABLED&t;0x80000000&t;/* Cache is enabled */
DECL|macro|IDC_CERR1
mdefine_line|#define IDC_CERR1&t;0x00200000&t;/* Cache error 1 */
DECL|macro|IDC_CERR2
mdefine_line|#define IDC_CERR2&t;0x00100000&t;/* Cache error 2 */
DECL|macro|IDC_CERR3
mdefine_line|#define IDC_CERR3&t;0x00080000&t;/* Cache error 3 */
DECL|macro|DC_DFWT
mdefine_line|#define DC_DFWT&t;&t;0x40000000&t;/* Data cache is forced write through */
DECL|macro|DC_LES
mdefine_line|#define DC_LES&t;&t;0x20000000&t;/* Caches are little endian mode */
macro_line|#endif /* CONFIG_8xx */
macro_line|#endif
eof
