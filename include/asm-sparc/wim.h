multiline_comment|/* wim.h: Defines the layout of the &quot;Window Invalid Register&quot; on&n;          Version 8 of the Sparc Architecture.&n;&n;   Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)&n;*/
macro_line|#ifndef __LINUX_SPARC_WIM_H
DECL|macro|__LINUX_SPARC_WIM_H
mdefine_line|#define __LINUX_SPARC_WIM_H
macro_line|#ifdef __LINUX_SPARC_V8     /* register doesn&squot;t exist on the V9 */
multiline_comment|/* The Window Invalid Register %wim, holds a set of which register&n;   windows are &squot;valid&squot; at this point in time.&n;&n;   ------------------------------------------------------------&n;   |W31|W30|W29|W28|W27|W26|W25|W24|W23|....|W5|W4|W3|W2|W1|W0|&n;   ------------------------------------------------------------&n;&n;   Each register window on the chip gets one bit. If the bit is&n;   set then the window is currently &squot;invalid&squot; and hardware will&n;   trap if that window is entered via a &squot;save&squot;, &squot;restore&squot;, or&n;   &squot;rett&squot; instruction. Privileged software is responsible for&n;   updating this on trap fills/spills etc. Therefore if a &squot;save&squot;&n;   instruction is executed and it causes the Current Window&n;   Pointer to equal a register window which has it&squot;s bit set in&n;   %wim we get a &squot;overflow&squot; trap, a restore into such a register&n;   invokes a window &squot;spill&squot; trap.&n;*/
DECL|macro|__LINUX_SPARC_HAS_WIM
mdefine_line|#define __LINUX_SPARC_HAS_WIM
multiline_comment|/* Macro to fine the %wim bit mask for the current window pointer */
DECL|macro|CWP_TO_WIM_MASK
mdefine_line|#define CWP_TO_WIM_MASK(cwp)  (1&lt;&lt;(cwp))
multiline_comment|/* Assembly version of above macro, &squot;cwp&squot; and &squot;wimask&squot; must be registers */
DECL|macro|ASM_CWP_TO_WIM_MASK
mdefine_line|#define ASM_CWP_TO_WIM_MASK(cwp,wimask) &bslash;&n;          or  %g0, 0x1, wimask &bslash;&n;          sll wimask, cwp, wimask
multiline_comment|/* Assembly macro to find if the given window is set to invalid in the %wim.&n;   Again &squot;window&squot;, &squot;result&squot;, and &squot;scratch&squot; must be in registers. This leaves &n;   a non-zero value in result if the window is indeed invalid. This routine&n;   works because we keep exactly one window invalid at all times to maximize&n;   register utilization, which means both kernel and user windows can be in&n;   the register file at the same time in certain trap situations.&n;*/
DECL|macro|ASM_REG_WIN_INVAL
mdefine_line|#define ASM_REG_WIN_INVAL(window,result,scratch) &bslash;&n;         rd  %wim, result &bslash;&n;         or  %g0, 0x1, scratch &bslash;&n;         sll scratch, window, scratch &bslash;&n;         and scratch, result, result
macro_line|#endif /* !(__LINUX_SPARC_V8) */
macro_line|#endif  /* !(__LINUX_SPARC_WIM_H) */
eof
