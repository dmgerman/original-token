multiline_comment|/*&n; * indy_sc.c: Indy cache managment functions.&n; *&n; * Copyright (C) 1997 Ralf Baechle (ralf@gnu.org),&n; * derived from r4xx0.c by David S. Miller (dm@engr.sgi.com).&n; *&n; * $Id: indy_sc.c,v 1.4 1998/05/04 09:12:57 ralf Exp $&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/bcache.h&gt;
macro_line|#include &lt;asm/sgi.h&gt;
macro_line|#include &lt;asm/sgimc.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
multiline_comment|/* Secondary cache size in bytes, if present.  */
DECL|variable|scache_size
r_static
r_int
r_int
id|scache_size
suffix:semicolon
DECL|macro|DEBUG_CACHE
macro_line|#undef DEBUG_CACHE
DECL|macro|SC_SIZE
mdefine_line|#define SC_SIZE 0x00080000
DECL|macro|SC_LINE
mdefine_line|#define SC_LINE 32
DECL|macro|CI_MASK
mdefine_line|#define CI_MASK (SC_SIZE - SC_LINE)
DECL|macro|SC_ROUND
mdefine_line|#define SC_ROUND(n) ((n) + SC_LINE - 1)
DECL|macro|SC_INDEX
mdefine_line|#define SC_INDEX(n) ((n) &amp; CI_MASK)
DECL|function|indy_sc_wipe
r_static
r_inline
r_void
id|indy_sc_wipe
c_func
(paren
r_int
r_int
id|first
comma
r_int
r_int
id|last
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
dot
id|set
id|noreorder
dot
id|set
id|mips3
dot
id|set
id|noat
id|li
"$"
l_int|1
comma
l_int|0x80
macro_line|# Go 64 bit
id|mtc0
"$"
l_int|1
comma
"$"
l_int|12
id|dli
"$"
l_int|1
comma
l_int|0x9000000080000000
op_logical_or
op_mod
l_int|0
comma
"$"
l_int|1
macro_line|# first line to flush
op_logical_or
op_mod
l_int|1
comma
"$"
l_int|1
macro_line|# last line to flush
dot
id|set
id|at
l_int|1
suffix:colon
id|sw
"$"
l_int|0
comma
l_int|0
(paren
op_mod
l_int|0
)paren
id|bne
op_mod
l_int|0
comma
op_mod
l_int|1
comma
l_int|1
id|b
id|daddu
op_mod
l_int|0
comma
l_int|32
id|mtc0
"$"
l_int|0
comma
"$"
l_int|12
macro_line|# Back to 32 bit
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|nop
suffix:semicolon
dot
id|set
id|mips0
dot
id|set
id|reorder
"&quot;"
suffix:colon
l_string|&quot;=r&quot;
(paren
id|first
)paren
comma
l_string|&quot;=r&quot;
(paren
id|last
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|first
)paren
comma
l_string|&quot;1&quot;
(paren
id|last
)paren
suffix:colon
l_string|&quot;$1&quot;
)paren
suffix:semicolon
)brace
DECL|function|indy_sc_wback_invalidate
r_static
r_void
id|indy_sc_wback_invalidate
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|first_line
comma
id|last_line
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
macro_line|#ifdef DEBUG_CACHE
id|printk
c_func
(paren
l_string|&quot;indy_sc_wback_invalidate[%08lx,%08lx]&quot;
comma
id|addr
comma
id|size
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Which lines to flush?  */
id|first_line
op_assign
id|SC_INDEX
c_func
(paren
id|addr
)paren
suffix:semicolon
id|last_line
op_assign
id|SC_INDEX
c_func
(paren
id|SC_ROUND
c_func
(paren
id|addr
op_plus
id|size
)paren
)paren
suffix:semicolon
id|__save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|first_line
op_le
id|last_line
)paren
(brace
id|indy_sc_wipe
c_func
(paren
id|first_line
comma
id|last_line
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* Cache index wrap around.  Due to the way the buddy system works&n;&t;   this case should not happen.  We&squot;re prepared to handle it,&n;&t;   though. */
id|indy_sc_wipe
c_func
(paren
id|last_line
comma
id|SC_SIZE
)paren
suffix:semicolon
id|indy_sc_wipe
c_func
(paren
l_int|0
comma
id|first_line
)paren
suffix:semicolon
id|out
suffix:colon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|indy_sc_enable
r_static
r_void
id|indy_sc_enable
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|addr
comma
id|tmp1
comma
id|tmp2
suffix:semicolon
multiline_comment|/* This is really cool... */
macro_line|#ifdef DEBUG_CACHE
id|printk
c_func
(paren
l_string|&quot;Enabling R4600 SCACHE&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
dot
id|set
id|noreorder
dot
id|set
id|mips3
id|mfc0
op_mod
l_int|2
comma
"$"
l_int|12
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|li
op_mod
l_int|1
comma
l_int|0x80
id|mtc0
op_mod
l_int|1
comma
"$"
l_int|12
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|li
op_mod
l_int|0
comma
l_int|0x1
id|dsll
op_mod
l_int|0
comma
l_int|31
id|lui
op_mod
l_int|1
comma
l_int|0x9000
id|dsll32
op_mod
l_int|1
comma
l_int|0
op_logical_or
op_mod
l_int|0
comma
op_mod
l_int|1
comma
op_mod
l_int|0
id|sb
"$"
l_int|0
comma
l_int|0
(paren
op_mod
l_int|0
)paren
id|mtc0
"$"
l_int|0
comma
"$"
l_int|12
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|mtc0
op_mod
l_int|2
comma
"$"
l_int|12
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|nop
suffix:semicolon
dot
id|set
id|mips0
dot
id|set
id|reorder
"&quot;"
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|tmp2
)paren
comma
l_string|&quot;=r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|indy_sc_disable
r_static
r_void
id|indy_sc_disable
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tmp1
comma
id|tmp2
comma
id|tmp3
suffix:semicolon
macro_line|#ifdef DEBUG_CACHE
id|printk
c_func
(paren
l_string|&quot;Disabling R4600 SCACHE&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
dot
id|set
id|noreorder
dot
id|set
id|mips3
id|li
op_mod
l_int|0
comma
l_int|0x1
id|dsll
op_mod
l_int|0
comma
l_int|31
id|lui
op_mod
l_int|1
comma
l_int|0x9000
id|dsll32
op_mod
l_int|1
comma
l_int|0
op_logical_or
op_mod
l_int|0
comma
op_mod
l_int|1
comma
op_mod
l_int|0
id|mfc0
op_mod
l_int|2
comma
"$"
l_int|12
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|li
op_mod
l_int|1
comma
l_int|0x80
id|mtc0
op_mod
l_int|1
comma
"$"
l_int|12
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|sh
"$"
l_int|0
comma
l_int|0
(paren
op_mod
l_int|0
)paren
id|mtc0
"$"
l_int|0
comma
"$"
l_int|12
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|mtc0
op_mod
l_int|2
comma
"$"
l_int|12
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|nop
suffix:semicolon
id|nop
suffix:semicolon
dot
id|set
id|mips2
dot
id|set
id|reorder
l_string|&quot; : &quot;
op_assign
id|r
l_string|&quot; (tmp1), &quot;
op_assign
id|r
l_string|&quot; (tmp2), &quot;
op_assign
id|r
"&quot;"
(paren
id|tmp3
)paren
)paren
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_static
r_inline
r_int
id|indy_sc_probe
c_func
(paren
r_void
)paren
)paren
(brace
r_volatile
r_int
r_int
op_star
id|cpu_control
suffix:semicolon
r_int
r_int
id|cmd
op_assign
l_int|0xc220
suffix:semicolon
r_int
r_int
id|data
op_assign
l_int|0
suffix:semicolon
r_int
id|i
comma
id|n
suffix:semicolon
macro_line|#ifdef __MIPSEB__
id|cpu_control
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|KSEG1ADDR
c_func
(paren
l_int|0x1fa00034
)paren
suffix:semicolon
macro_line|#else
id|cpu_control
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|KSEG1ADDR
c_func
(paren
l_int|0x1fa00030
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|DEASSERT
mdefine_line|#define DEASSERT(bit) (*(cpu_control) &amp;= (~(bit)))
DECL|macro|ASSERT
mdefine_line|#define ASSERT(bit) (*(cpu_control) |= (bit))
DECL|macro|DELAY
mdefine_line|#define DELAY  for(n = 0; n &lt; 100000; n++) __asm__ __volatile__(&quot;&quot;)
id|DEASSERT
c_func
(paren
id|SGIMC_EEPROM_PRE
)paren
suffix:semicolon
id|DEASSERT
c_func
(paren
id|SGIMC_EEPROM_SDATAO
)paren
suffix:semicolon
id|DEASSERT
c_func
(paren
id|SGIMC_EEPROM_SECLOCK
)paren
suffix:semicolon
id|DEASSERT
c_func
(paren
id|SGIMC_EEPROM_PRE
)paren
suffix:semicolon
id|DELAY
suffix:semicolon
id|ASSERT
c_func
(paren
id|SGIMC_EEPROM_CSEL
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|SGIMC_EEPROM_SECLOCK
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|11
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cmd
op_amp
(paren
l_int|1
op_lshift
l_int|15
)paren
)paren
(brace
id|ASSERT
c_func
(paren
id|SGIMC_EEPROM_SDATAO
)paren
suffix:semicolon
)brace
r_else
id|DEASSERT
c_func
(paren
id|SGIMC_EEPROM_SDATAO
)paren
suffix:semicolon
id|DEASSERT
c_func
(paren
id|SGIMC_EEPROM_SECLOCK
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|SGIMC_EEPROM_SECLOCK
)paren
suffix:semicolon
id|cmd
op_lshift_assign
l_int|1
suffix:semicolon
)brace
id|DEASSERT
c_func
(paren
id|SGIMC_EEPROM_SDATAO
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
r_sizeof
(paren
r_int
r_int
)paren
op_star
l_int|8
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|DEASSERT
c_func
(paren
id|SGIMC_EEPROM_SECLOCK
)paren
suffix:semicolon
id|DELAY
suffix:semicolon
id|ASSERT
c_func
(paren
id|SGIMC_EEPROM_SECLOCK
)paren
suffix:semicolon
id|DELAY
suffix:semicolon
id|data
op_lshift_assign
l_int|1
suffix:semicolon
id|tmp
op_assign
op_star
id|cpu_control
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_amp
id|SGIMC_EEPROM_SDATAI
)paren
(brace
id|data
op_or_assign
l_int|1
suffix:semicolon
)brace
)brace
id|DEASSERT
c_func
(paren
id|SGIMC_EEPROM_SECLOCK
)paren
suffix:semicolon
id|DEASSERT
c_func
(paren
id|SGIMC_EEPROM_CSEL
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|SGIMC_EEPROM_PRE
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|SGIMC_EEPROM_SECLOCK
)paren
suffix:semicolon
id|data
op_lshift_assign
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|data
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|scache_size
op_assign
id|data
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;R4600/R5000 SCACHE size %ldK, linesize 32 bytes.&bslash;n&quot;
comma
id|scache_size
op_rshift
l_int|10
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* XXX Check with wje if the Indy caches can differenciate between&n;   writeback + invalidate and just invalidate.  */
DECL|variable|indy_sc_ops
r_struct
id|bcache_ops
id|indy_sc_ops
op_assign
(brace
id|indy_sc_enable
comma
id|indy_sc_disable
comma
id|indy_sc_wback_invalidate
comma
id|indy_sc_wback_invalidate
)brace
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|indy_sc_init
c_func
(paren
r_void
)paren
)paren
(brace
r_if
c_cond
(paren
id|indy_sc_probe
c_func
(paren
)paren
)paren
(brace
id|indy_sc_enable
c_func
(paren
)paren
suffix:semicolon
id|bcops
op_assign
op_amp
id|indy_sc_ops
suffix:semicolon
)brace
)brace
eof