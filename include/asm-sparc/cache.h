multiline_comment|/* cache.h:  Cache specific code for the Sparc.  These include flushing&n; *           and direct tag/data line access.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_CACHE_H
DECL|macro|_SPARC_CACHE_H
mdefine_line|#define _SPARC_CACHE_H
macro_line|#include &lt;asm/asi.h&gt;
multiline_comment|/* Direct access to the instruction cache is provided through and&n; * alternate address space.  The IDC bit must be off in the ICCR on&n; * HyperSparcs for these accesses to work.  The code below does not do&n; * any checking, the caller must do so.  These routines are for&n; * diagnostics only, but coule end up being useful.  Use with care.&n; * Also, you are asking for trouble if you execute these in one of the&n; * three instructions following a %asr/%psr access or modification.&n; */
multiline_comment|/* First, cache-tag access. */
DECL|function|get_icache_tag
r_extern
r_inline
r_int
r_int
id|get_icache_tag
c_func
(paren
r_int
id|setnum
comma
r_int
id|tagnum
)paren
(brace
r_int
r_int
id|vaddr
comma
id|retval
suffix:semicolon
id|vaddr
op_assign
(paren
(paren
id|setnum
op_amp
l_int|1
)paren
op_lshift
l_int|12
)paren
op_or
(paren
(paren
id|tagnum
op_amp
l_int|0x7f
)paren
op_lshift
l_int|5
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda [%1] %2, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|vaddr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_TXTC_TAG
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|put_icache_tag
r_extern
r_inline
r_void
id|put_icache_tag
c_func
(paren
r_int
id|setnum
comma
r_int
id|tagnum
comma
r_int
r_int
id|entry
)paren
(brace
r_int
r_int
id|vaddr
suffix:semicolon
id|vaddr
op_assign
(paren
(paren
id|setnum
op_amp
l_int|1
)paren
op_lshift
l_int|12
)paren
op_or
(paren
(paren
id|tagnum
op_amp
l_int|0x7f
)paren
op_lshift
l_int|5
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %0, [%1] %2&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|entry
)paren
comma
l_string|&quot;r&quot;
(paren
id|vaddr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_TXTC_TAG
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Second cache-data access.  The data is returned two-32bit quantities&n; * at a time.&n; */
DECL|function|get_icache_data
r_extern
r_inline
r_void
id|get_icache_data
c_func
(paren
r_int
id|setnum
comma
r_int
id|tagnum
comma
r_int
id|subblock
comma
r_int
r_int
op_star
id|data
)paren
(brace
r_int
r_int
id|value1
comma
id|value2
comma
id|vaddr
suffix:semicolon
id|vaddr
op_assign
(paren
(paren
id|setnum
op_amp
l_int|0x1
)paren
op_lshift
l_int|12
)paren
op_or
(paren
(paren
id|tagnum
op_amp
l_int|0x7f
)paren
op_lshift
l_int|5
)paren
op_or
(paren
(paren
id|subblock
op_amp
l_int|0x3
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldda [%2] %3, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;or %%g0, %%g2, %0&bslash;n&bslash;t&quot;
l_string|&quot;or %%g0, %%g3, %1&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|value1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|value2
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|vaddr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_TXTC_DATA
)paren
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
)paren
suffix:semicolon
id|data
(braket
l_int|0
)braket
op_assign
id|value1
suffix:semicolon
id|data
(braket
l_int|1
)braket
op_assign
id|value2
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|put_icache_data
r_extern
r_inline
r_void
id|put_icache_data
c_func
(paren
r_int
id|setnum
comma
r_int
id|tagnum
comma
r_int
id|subblock
comma
r_int
r_int
op_star
id|data
)paren
(brace
r_int
r_int
id|value1
comma
id|value2
comma
id|vaddr
suffix:semicolon
id|vaddr
op_assign
(paren
(paren
id|setnum
op_amp
l_int|0x1
)paren
op_lshift
l_int|12
)paren
op_or
(paren
(paren
id|tagnum
op_amp
l_int|0x7f
)paren
op_lshift
l_int|5
)paren
op_or
(paren
(paren
id|subblock
op_amp
l_int|0x3
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
id|value1
op_assign
id|data
(braket
l_int|0
)braket
suffix:semicolon
id|value2
op_assign
id|data
(braket
l_int|1
)braket
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;or %%g0, %0, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;or %%g0, %1, %%g3&bslash;n&bslash;t&quot;
l_string|&quot;stda %%g2, [%2] %3&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|value1
)paren
comma
l_string|&quot;r&quot;
(paren
id|value2
)paren
comma
l_string|&quot;r&quot;
(paren
id|vaddr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_TXTC_DATA
)paren
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;memory&quot;
multiline_comment|/* no joke */
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Different types of flushes with the ICACHE.  Some of the flushes&n; * affect both the ICACHE and the external cache.  Others only clear&n; * the ICACHE entries on the cpu itself.  V8&squot;s (most) allow&n; * granularity of flushes on the packet (element in line), whole line,&n; * and entire cache (ie. all lines) level.  The ICACHE only flushes are&n; * ROSS HyperSparc specific and are in ross.h&n; */
multiline_comment|/* Flushes which clear out both the on-chip and external caches */
DECL|function|flush_ei_page
r_extern
r_inline
r_void
id|flush_ei_page
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_FLUSH_PAGE
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|flush_ei_seg
r_extern
r_inline
r_void
id|flush_ei_seg
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_FLUSH_SEG
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|flush_ei_region
r_extern
r_inline
r_void
id|flush_ei_region
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_FLUSH_REGION
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|flush_ei_ctx
r_extern
r_inline
r_void
id|flush_ei_ctx
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_FLUSH_CTX
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|flush_ei_user
r_extern
r_inline
r_void
id|flush_ei_user
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_FLUSH_USER
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif /* !(_SPARC_CACHE_H) */
eof