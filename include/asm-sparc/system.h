macro_line|#ifndef __SPARC_SYSTEM_H
DECL|macro|__SPARC_SYSTEM_H
mdefine_line|#define __SPARC_SYSTEM_H
multiline_comment|/*&n; * System defines.. Note that this is included both from .c and .S&n; * files, so it does only defines, not any C code.&n; */
multiline_comment|/*&n; * I wish the boot time image was as beautiful as the Alpha&squot;s&n; * but no such luck. The icky PROM loads us at 0x0, and jumps&n; * to magic address 0x4000 to start thing going. This means that&n; * I can stick the pcb and user/kernel stacks in the area from&n; * 0x0-0x4000 and be reasonably sure that this is sane.&n; *&n; * Sorry, I can&squot;t impress people with cool looking 64-bit values&n; * yet. ;-)&n; */
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/psr.h&gt;
DECL|macro|INIT_PCB
mdefine_line|#define INIT_PCB&t;0x00011fe0
DECL|macro|INIT_STACK
mdefine_line|#define INIT_STACK&t;0x00013fe0
DECL|macro|START_ADDR
mdefine_line|#define START_ADDR&t;0x00004000
DECL|macro|START_SIZE
mdefine_line|#define START_SIZE&t;(32*1024)
DECL|macro|EMPTY_PGT
mdefine_line|#define EMPTY_PGT&t;0x00001000
DECL|macro|EMPTY_PGE
mdefine_line|#define EMPTY_PGE&t;0x00001000
DECL|macro|ZERO_PGE
mdefine_line|#define ZERO_PGE&t;0x00001000
DECL|macro|IRQ_ENA_ADR
mdefine_line|#define IRQ_ENA_ADR     0x2000        /* This is a bitmap of all activated IRQ&squot;s&n;&t;&t;&t;&t;       * which is mapped in head.S during boot.&n;&t;&t;&t;&t;       */
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|wrent
c_func
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|wrkgp
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|linux_romvec
op_star
id|romvec
suffix:semicolon
DECL|macro|halt
mdefine_line|#define halt() { romvec-&gt;pv_halt(); }
DECL|macro|move_to_user_mode
mdefine_line|#define move_to_user_mode() halt()
DECL|macro|switch_to
mdefine_line|#define switch_to(x) halt()
macro_line|#ifndef stbar  /* store barrier Sparc insn to synchronize stores in PSO */
DECL|macro|stbar
mdefine_line|#define stbar() __asm__ __volatile__(&quot;stbar&quot;: : :&quot;memory&quot;)
macro_line|#endif
multiline_comment|/* Changing the PIL on the sparc is a bit hairy. I&squot;ll figure out some&n; * more optimized way of doing this soon. This is bletcherous code.&n; */
DECL|macro|swpipl
mdefine_line|#define swpipl(__new_ipl) &bslash;&n;({ unsigned long psr, retval; &bslash;&n;__asm__ __volatile__( &bslash;&n;        &quot;rd %%psr, %0&bslash;n&bslash;t&quot; : &quot;=&amp;r&quot; (psr)); &bslash;&n;retval = psr; &bslash;&n;psr = (psr &amp; ~(PSR_PIL)); &bslash;&n;psr |= ((__new_ipl &lt;&lt; 8) &amp; PSR_PIL); &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;wr  %0, 0x0, %%psr&bslash;n&bslash;t&quot; &bslash;&n;&t;: : &quot;r&quot; (psr)); &bslash;&n;retval = ((retval&gt;&gt;8)&amp;15); &bslash;&n;retval; })
DECL|macro|cli
mdefine_line|#define cli()&t;&t;&t;swpipl(15)  /* 15 = no int&squot;s except nmi&squot;s */
DECL|macro|sti
mdefine_line|#define sti()&t;&t;&t;swpipl(0)   /* same as alpha */
DECL|macro|save_flags
mdefine_line|#define save_flags(flags)&t;do { flags = swpipl(15); } while (0)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(flags)&t;swpipl(flags)
DECL|macro|iret
mdefine_line|#define iret() __asm__ __volatile__ (&quot;jmp %%l1&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;&t;     &quot;rett %%l2&bslash;n&bslash;t&quot;: : :&quot;memory&quot;)
DECL|macro|_set_gate
mdefine_line|#define _set_gate(gate_addr,type,dpl,addr) &bslash;&n;__asm__ __volatile__ (&quot;nop&bslash;n&bslash;t&quot;)
DECL|macro|set_intr_gate
mdefine_line|#define set_intr_gate(n,addr) &bslash;&n;&t;_set_gate(&amp;idt[n],14,0,addr)
DECL|macro|set_trap_gate
mdefine_line|#define set_trap_gate(n,addr) &bslash;&n;&t;_set_gate(&amp;idt[n],15,0,addr)
DECL|macro|set_system_gate
mdefine_line|#define set_system_gate(n,addr) &bslash;&n;&t;_set_gate(&amp;idt[n],15,3,addr)
DECL|macro|set_call_gate
mdefine_line|#define set_call_gate(a,addr) &bslash;&n;&t;_set_gate(a,12,3,addr)
DECL|function|get_psr
r_extern
r_inline
r_int
r_int
id|get_psr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|ret_val
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;rd %%psr, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret_val
)paren
)paren
suffix:semicolon
r_return
id|ret_val
suffix:semicolon
)brace
DECL|function|put_psr
r_extern
r_inline
r_void
id|put_psr
c_func
(paren
r_int
r_int
id|new_psr
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;wr %0, 0x0, %%psr&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|new_psr
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Must this be atomic? */
DECL|function|xchg_u32
r_extern
r_inline
r_void
op_star
id|xchg_u32
c_func
(paren
r_int
op_star
id|m
comma
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ld [%1],%2&bslash;n&bslash;t&quot;
l_string|&quot;st %0, [%1]&bslash;n&bslash;t&quot;
l_string|&quot;or %%g0, %2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
comma
l_string|&quot;=r&quot;
(paren
id|m
)paren
comma
l_string|&quot;=r&quot;
(paren
id|dummy
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|val
suffix:semicolon
)brace
multiline_comment|/* pointers are 32 bits on the sparc (at least the v8, and they&squot;ll work&n; * on the V9 none the less). I don&squot;t need the xchg_u64 routine for now.&n; */
DECL|function|xchg_ptr
r_extern
r_inline
r_void
op_star
id|xchg_ptr
c_func
(paren
r_void
op_star
id|m
comma
r_void
op_star
id|val
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|xchg_u32
c_func
(paren
(paren
r_int
op_star
)paren
id|m
comma
(paren
r_int
r_int
)paren
id|val
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif
eof
