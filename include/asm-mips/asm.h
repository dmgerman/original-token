multiline_comment|/*&n; * include/asm-mips/asm.h&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995 by Ralf Baechle&n; *&n; * Some useful macros for MIPS assembler code&n; *&n; * Some of the routines below contain useless nops that will be optimized&n; * away by gas in -O mode. These nops are however required to fill delay&n; * slots in noreorder mode.&n; */
macro_line|#ifndef&t;__ASM_ASM_H
DECL|macro|__ASM_ASM_H
mdefine_line|#define&t;__ASM_ASM_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/regdef.h&gt;
macro_line|#include &lt;asm/fpregdef.h&gt;
macro_line|#ifndef CAT
macro_line|#ifdef __STDC__
DECL|macro|__CAT
mdefine_line|#define __CAT(str1,str2) str1##str2
macro_line|#else
DECL|macro|__CAT
mdefine_line|#define __CAT(str1,str2) str1/**/str2
macro_line|#endif
DECL|macro|CAT
mdefine_line|#define CAT(str1,str2) __CAT(str1,str2)
macro_line|#endif
multiline_comment|/*&n; * Macros to handle different pointer sizes for 32/64-bit code&n; */
macro_line|#if __mips == 3
DECL|macro|PTR
mdefine_line|#define PTR&t;.quad
DECL|macro|PTRSIZE
mdefine_line|#define PTRSIZE&t;8
DECL|macro|PTRLOG
mdefine_line|#define PTRLOG&t;3
DECL|macro|lp
mdefine_line|#define lp&t;ld
macro_line|#else
DECL|macro|PTR
mdefine_line|#define PTR&t;.word
DECL|macro|PTRSIZE
mdefine_line|#define PTRSIZE&t;4
DECL|macro|PTRLOG
mdefine_line|#define PTRLOG&t;2
DECL|macro|lp
mdefine_line|#define lp&t;lw
macro_line|#endif
multiline_comment|/*&n; * ELF specific declarations&n; */
macro_line|#ifdef __ELF__
DECL|macro|TYPE
mdefine_line|#define TYPE(symbol,_type)                              &bslash;&n;&t;&t;&t;.type&t;symbol,@_type
DECL|macro|SIZE
mdefine_line|#define SIZE(symbol,_size)                              &bslash;&n;&t;&t;&t;.size&t;symbol,_size
macro_line|#else
DECL|macro|TYPE
mdefine_line|#define TYPE(symbol,type)
DECL|macro|SIZE
mdefine_line|#define SIZE(symbol,size)
macro_line|#endif
multiline_comment|/*&n; * PIC specific declarations&n; * Not used for the kernel but here seems to be the right place.&n; */
macro_line|#ifdef __PIC__
DECL|macro|CPRESTORE
mdefine_line|#define CPRESTORE(register)                             &bslash;&n;&t;&t;&t;.cprestore register
DECL|macro|CPADD
mdefine_line|#define CPADD(register)                                 &bslash;&n;&t;&t;&t;.cpadd&t;register
DECL|macro|CPLOAD
mdefine_line|#define CPLOAD(register)                                &bslash;&n;&t;&t;&t;.cpload&t;register
macro_line|#else
DECL|macro|CPRESTORE
mdefine_line|#define CPRESTORE(register)
DECL|macro|CPADD
mdefine_line|#define CPADD(register)
DECL|macro|CPLOAD
mdefine_line|#define CPLOAD(register)
macro_line|#endif
multiline_comment|/*&n; * LEAF - declare leaf routine&n; */
DECL|macro|LEAF
mdefine_line|#define&t;LEAF(symbol)                                    &bslash;&n;&t;&t;&t;.globl&t;symbol;                 &bslash;&n;&t;&t;&t;.align&t;2;                      &bslash;&n;&t;&t;&t;TYPE(symbol,function);          &bslash;&n;&t;&t;&t;.ent&t;symbol,0;               &bslash;&n;symbol:&t;&t;&t;.frame&t;sp,0,ra
multiline_comment|/*&n; * NESTED - declare nested routine entry point&n; */
DECL|macro|NESTED
mdefine_line|#define&t;NESTED(symbol, framesize, rpc)                  &bslash;&n;&t;&t;&t;.globl&t;symbol;                 &bslash;&n;&t;&t;&t;.align&t;2;                      &bslash;&n;&t;&t;&t;TYPE(symbol,function);          &bslash;&n;&t;&t;&t;.ent&t;symbol,0;               &bslash;&n;symbol:&t;&t;&t;.frame&t;sp, framesize, rpc
multiline_comment|/*&n; * END - mark end of function&n; */
DECL|macro|END
mdefine_line|#define&t;END(function)                                   &bslash;&n;&t;&t;&t;.end&t;function;&t;&t;&bslash;&n;&t;&t;&t;SIZE(function,.-function)
multiline_comment|/*&n; * EXPORT - export definition of symbol&n; */
DECL|macro|EXPORT
mdefine_line|#define&t;EXPORT(symbol)                                  &bslash;&n;&t;&t;&t;.globl&t;symbol;                 &bslash;&n;symbol:
multiline_comment|/*&n; * ABS - export absolute symbol&n; */
DECL|macro|ABS
mdefine_line|#define&t;ABS(symbol,value)                               &bslash;&n;&t;&t;&t;.globl&t;symbol;                 &bslash;&n;symbol&t;&t;&t;=&t;value
DECL|macro|PANIC
mdefine_line|#define&t;PANIC(msg)                                      &bslash;&n;&t;&t;&t;la&t;a0,8f;                  &bslash;&n;&t;&t;&t;jal&t;panic;                  &bslash;&n;&t;&t;&t;nop;                            &bslash;&n;9:&t;&t;&t;b&t;9b;                     &bslash;&n;&t;&t;&t;nop;                            &bslash;&n;&t;&t;&t;TEXT(msg)
multiline_comment|/*&n; * Print formated string&n; */
DECL|macro|PRINT
mdefine_line|#define PRINT(string)                                   &bslash;&n;&t;&t;&t;la&t;a0,8f;                  &bslash;&n;&t;&t;&t;jal&t;printk;                 &bslash;&n;&t;&t;&t;nop;                            &bslash;&n;&t;&t;&t;TEXT(string)
DECL|macro|TEXT
mdefine_line|#define&t;TEXT(msg)                                       &bslash;&n;&t;&t;&t;.data;                          &bslash;&n;8:&t;&t;&t;.asciiz&t;msg;                    &bslash;&n;&t;&t;&t;.text
multiline_comment|/*&n; * Build text tables&n; */
DECL|macro|TTABLE
mdefine_line|#define TTABLE(string)                                  &bslash;&n;&t;&t;.text;                                  &bslash;&n;&t;&t;.word&t;1f;                             &bslash;&n;&t;&t;.data;                                  &bslash;&n;1:&t;&t;.asciz&t;string;                         &bslash;&n;&t;&t;.text;
multiline_comment|/*&n; * Move to kernel mode and disable interrupts&n; * Set cp0 enable bit as sign that we&squot;re running on the kernel stack&n; * Use with .set noat!&n; * Note that the mtc0 will be effective on R4000 pipeline stage 7. This&n; * means that another three instructions will be executed with interrupts&n; * disabled.&n; */
DECL|macro|CLI
mdefine_line|#define CLI                                             &bslash;&n;&t;&t;mfc0&t;AT,CP0_STATUS;                  &bslash;&n;&t;&t;li&t;t0,ST0_CU0|0x1f;                &bslash;&n;&t;&t;or&t;AT,t0;                          &bslash;&n;&t;&t;xori&t;AT,0x1f;                        &bslash;&n;&t;&t;mtc0&t;AT,CP0_STATUS;&t;&t;&t;&bslash;&n;
multiline_comment|/*&n; * Move to kernel mode and enable interrupts&n; * Set cp0 enable bit as sign that we&squot;re running on the kernel stack&n; * Use with .set noat!&n; * Note that the mtc0 will be effective on R4000 pipeline stage 7. This&n; * means that another three instructions will be executed with interrupts&n; * disabled.  Arch/mips/kernel/r4xx0.S makes use of this fact.&n; */
DECL|macro|STI
mdefine_line|#define STI                                             &bslash;&n;&t;&t;mfc0&t;AT,CP0_STATUS;                  &bslash;&n;&t;&t;li&t;t0,ST0_CU0|0x1f;                &bslash;&n;&t;&t;or&t;AT,t0;                          &bslash;&n;&t;&t;xori&t;AT,0x1e;                        &bslash;&n;&t;&t;mtc0&t;AT,CP0_STATUS;&t;&t;&t;&bslash;&n;
multiline_comment|/*&n; * Special nop to fill load delay slots&n; */
macro_line|#ifndef __R4000__
DECL|macro|NOP
mdefine_line|#define NOP     nop
macro_line|#else
DECL|macro|NOP
mdefine_line|#define NOP
macro_line|#endif
multiline_comment|/*&n; * Return from exception&n; */
macro_line|#if defined (CONFIG_CPU_R3000)
DECL|macro|ERET
mdefine_line|#define ERET rfe
macro_line|#elif defined (CONFIG_CPU_R4X00) || defined (CONFIG_CPU_R4600)
DECL|macro|ERET
mdefine_line|#define ERET                                            &bslash;&n;&t;&t;.set&t;mips3;                          &bslash;&n;&t;&t;eret;                                   &bslash;&n;&t;&t;.set&t;mips0
macro_line|#else
macro_line|#error &quot;Implement ERET macro!&quot;
macro_line|#endif
multiline_comment|/*&n; * R8000/R10000 (MIPS ISA IV) pref instruction.&n; * Use with .set noreorder only!&n; */
macro_line|#if defined (CONFIG_CPU_R8000) || defined(CONFIG_CPU_R10000)
DECL|macro|PREF
mdefine_line|#define PREF(hint,addr)                                 &bslash;&n;&t;&t;pref&t;hint,addr
DECL|macro|PREFX
mdefine_line|#define PREFX(hint,addr)                                &bslash;&n;&t;&t;prefx&t;hint,addr
macro_line|#else
DECL|macro|PREF
mdefine_line|#define PREF
DECL|macro|PREFX
mdefine_line|#define PREFX
macro_line|#endif
multiline_comment|/*&n; * R8000/R10000 (MIPS ISA IV) movn/movz instructions and&n; * equivalents for old CPUs. Use with .set noreorder only!&n; */
macro_line|#if defined (CONFIG_CPU_R8000) || defined (CONFIG_CPU_R10000)
DECL|macro|MOVN
mdefine_line|#define MOVN(rd,rs,rt)                                  &bslash;&n;&t;&t;movn&t;rd,rs,rt
DECL|macro|MOVZ
mdefine_line|#define MOVZ(rd,rs,rt)                                  &bslash;&n;&t;&t;movz&t;rd,rs,rt
macro_line|#elif defined (CONFIG_CPU_R4000) || defined (CONFIG_CPU_R6000)
DECL|macro|MOVN
mdefine_line|#define MOVN(rd,rs,rt)                                  &bslash;&n;&t;&t;bnezl&t;rt,9f                           &bslash;&n;&t;&t;move&t;rd,rs                           &bslash;&n;9:
DECL|macro|MOVZ
mdefine_line|#define MOVZ(rd,rs,rt)                                  &bslash;&n;&t;&t;beqzl&t;rt,9f                           &bslash;&n;&t;&t;movz&t;rd,rt                           &bslash;&n;9:
macro_line|#else /* R2000, R3000 */
DECL|macro|MOVN
mdefine_line|#define MOVN(rd,rs,rt)                                  &bslash;&n;&t;&t;beqz&t;rt,9f                           &bslash;&n;&t;&t;nop                                     &bslash;&n;&t;&t;move&t;rd,rs                           &bslash;&n;9:
DECL|macro|MOVZ
mdefine_line|#define MOVZ(rd,rs,rt)                                  &bslash;&n;&t;&t;bneqz&t;rt,9f                           &bslash;&n;&t;&t;nop                                     &bslash;&n;&t;&t;movz&t;rd,rt                           &bslash;&n;9:
macro_line|#endif
macro_line|#endif /* __ASM_ASM_H */
eof
