multiline_comment|/*&n;** amigaints.h -- Amiga Linux interrupt handling structs and prototypes&n;**&n;** Copyright 1992 by Greg Harp&n;**&n;** This file is subject to the terms and conditions of the GNU General Public&n;** License.  See the file COPYING in the main directory of this archive&n;** for more details.&n;**&n;** Created 10/2/92 by Greg Harp&n;*/
macro_line|#ifndef _ASMm68k_AMIGAINTS_H_
DECL|macro|_ASMm68k_AMIGAINTS_H_
mdefine_line|#define _ASMm68k_AMIGAINTS_H_
multiline_comment|/*&n;** Amiga Interrupt sources.&n;**&n;*/
DECL|macro|NUM_AMIGA_SOURCES
mdefine_line|#define NUM_AMIGA_SOURCES   (24)
multiline_comment|/* vertical blanking interrupt */
DECL|macro|IRQ_AMIGA_VERTB
mdefine_line|#define IRQ_AMIGA_VERTB     (IRQ_MACHSPEC | 0)
multiline_comment|/* copper interrupt */
DECL|macro|IRQ_AMIGA_COPPER
mdefine_line|#define IRQ_AMIGA_COPPER    (IRQ_MACHSPEC | 1)
multiline_comment|/* Audio interrupts */
DECL|macro|IRQ_AMIGA_AUD0
mdefine_line|#define IRQ_AMIGA_AUD0&t;    (IRQ_MACHSPEC | 2)
DECL|macro|IRQ_AMIGA_AUD1
mdefine_line|#define IRQ_AMIGA_AUD1&t;    (IRQ_MACHSPEC | 3)
DECL|macro|IRQ_AMIGA_AUD2
mdefine_line|#define IRQ_AMIGA_AUD2&t;    (IRQ_MACHSPEC | 4)
DECL|macro|IRQ_AMIGA_AUD3
mdefine_line|#define IRQ_AMIGA_AUD3&t;    (IRQ_MACHSPEC | 5)
multiline_comment|/* Blitter done interrupt */
DECL|macro|IRQ_AMIGA_BLIT
mdefine_line|#define IRQ_AMIGA_BLIT&t;    (IRQ_MACHSPEC | 6)
multiline_comment|/* floppy disk interrupts */
DECL|macro|IRQ_AMIGA_DSKSYN
mdefine_line|#define IRQ_AMIGA_DSKSYN    (IRQ_MACHSPEC | 7)
DECL|macro|IRQ_AMIGA_DSKBLK
mdefine_line|#define IRQ_AMIGA_DSKBLK    (IRQ_MACHSPEC | 8)
multiline_comment|/* builtin serial port interrupts */
DECL|macro|IRQ_AMIGA_RBF
mdefine_line|#define IRQ_AMIGA_RBF&t;    (IRQ_MACHSPEC | 9)
DECL|macro|IRQ_AMIGA_TBE
mdefine_line|#define IRQ_AMIGA_TBE&t;    (IRQ_MACHSPEC | 10)
multiline_comment|/* CIA interrupt sources */
DECL|macro|IRQ_AMIGA_CIAA_TA
mdefine_line|#define IRQ_AMIGA_CIAA_TA   (IRQ_MACHSPEC | 11)
DECL|macro|IRQ_AMIGA_CIAA_TB
mdefine_line|#define IRQ_AMIGA_CIAA_TB   (IRQ_MACHSPEC | 12)
DECL|macro|IRQ_AMIGA_CIAA_ALRM
mdefine_line|#define IRQ_AMIGA_CIAA_ALRM (IRQ_MACHSPEC | 13)
DECL|macro|IRQ_AMIGA_CIAA_SP
mdefine_line|#define IRQ_AMIGA_CIAA_SP   (IRQ_MACHSPEC | 14)
DECL|macro|IRQ_AMIGA_CIAA_FLG
mdefine_line|#define IRQ_AMIGA_CIAA_FLG  (IRQ_MACHSPEC | 15)
DECL|macro|IRQ_AMIGA_CIAB_TA
mdefine_line|#define IRQ_AMIGA_CIAB_TA   (IRQ_MACHSPEC | 16)
DECL|macro|IRQ_AMIGA_CIAB_TB
mdefine_line|#define IRQ_AMIGA_CIAB_TB   (IRQ_MACHSPEC | 17)
DECL|macro|IRQ_AMIGA_CIAB_ALRM
mdefine_line|#define IRQ_AMIGA_CIAB_ALRM (IRQ_MACHSPEC | 18)
DECL|macro|IRQ_AMIGA_CIAB_SP
mdefine_line|#define IRQ_AMIGA_CIAB_SP   (IRQ_MACHSPEC | 19)
DECL|macro|IRQ_AMIGA_CIAB_FLG
mdefine_line|#define IRQ_AMIGA_CIAB_FLG  (IRQ_MACHSPEC | 20)
DECL|macro|IRQ_AMIGA_SOFT
mdefine_line|#define IRQ_AMIGA_SOFT      (IRQ_MACHSPEC | 21)
DECL|macro|IRQ_AMIGA_PORTS
mdefine_line|#define IRQ_AMIGA_PORTS&t;    (IRQ_MACHSPEC | 22)
DECL|macro|IRQ_AMIGA_EXTER
mdefine_line|#define IRQ_AMIGA_EXTER&t;    (IRQ_MACHSPEC | 23)
DECL|macro|IRQ_FLOPPY
mdefine_line|#define IRQ_FLOPPY&t;    IRQ_AMIGA_DSKBLK
multiline_comment|/* INTREQR masks */
DECL|macro|IRQ1_MASK
mdefine_line|#define IRQ1_MASK   0x0007&t;/* INTREQR mask for IRQ 1 */
DECL|macro|IRQ2_MASK
mdefine_line|#define IRQ2_MASK   0x0008&t;/* INTREQR mask for IRQ 2 */
DECL|macro|IRQ3_MASK
mdefine_line|#define IRQ3_MASK   0x0070&t;/* INTREQR mask for IRQ 3 */
DECL|macro|IRQ4_MASK
mdefine_line|#define IRQ4_MASK   0x0780&t;/* INTREQR mask for IRQ 4 */
DECL|macro|IRQ5_MASK
mdefine_line|#define IRQ5_MASK   0x1800&t;/* INTREQR mask for IRQ 5 */
DECL|macro|IRQ6_MASK
mdefine_line|#define IRQ6_MASK   0x2000&t;/* INTREQR mask for IRQ 6 */
DECL|macro|IRQ7_MASK
mdefine_line|#define IRQ7_MASK   0x4000&t;/* INTREQR mask for IRQ 7 */
DECL|macro|IF_SETCLR
mdefine_line|#define IF_SETCLR   0x8000      /* set/clr bit */
DECL|macro|IF_INTEN
mdefine_line|#define IF_INTEN    0x4000&t;/* master interrupt bit in INT* registers */
DECL|macro|IF_EXTER
mdefine_line|#define IF_EXTER    0x2000&t;/* external level 6 and CIA B interrupt */
DECL|macro|IF_DSKSYN
mdefine_line|#define IF_DSKSYN   0x1000&t;/* disk sync interrupt */
DECL|macro|IF_RBF
mdefine_line|#define IF_RBF&t;    0x0800&t;/* serial receive buffer full interrupt */
DECL|macro|IF_AUD3
mdefine_line|#define IF_AUD3     0x0400&t;/* audio channel 3 done interrupt */
DECL|macro|IF_AUD2
mdefine_line|#define IF_AUD2     0x0200&t;/* audio channel 2 done interrupt */
DECL|macro|IF_AUD1
mdefine_line|#define IF_AUD1     0x0100&t;/* audio channel 1 done interrupt */
DECL|macro|IF_AUD0
mdefine_line|#define IF_AUD0     0x0080&t;/* audio channel 0 done interrupt */
DECL|macro|IF_BLIT
mdefine_line|#define IF_BLIT     0x0040&t;/* blitter done interrupt */
DECL|macro|IF_VERTB
mdefine_line|#define IF_VERTB    0x0020&t;/* vertical blanking interrupt */
DECL|macro|IF_COPER
mdefine_line|#define IF_COPER    0x0010&t;/* copper interrupt */
DECL|macro|IF_PORTS
mdefine_line|#define IF_PORTS    0x0008&t;/* external level 2 and CIA A interrupt */
DECL|macro|IF_SOFT
mdefine_line|#define IF_SOFT     0x0004&t;/* software initiated interrupt */
DECL|macro|IF_DSKBLK
mdefine_line|#define IF_DSKBLK   0x0002&t;/* diskblock DMA finished */
DECL|macro|IF_TBE
mdefine_line|#define IF_TBE&t;    0x0001&t;/* serial transmit buffer empty interrupt */
multiline_comment|/* CIA interrupt control register bits */
DECL|macro|CIA_ICR_TA
mdefine_line|#define CIA_ICR_TA   0x01
DECL|macro|CIA_ICR_TB
mdefine_line|#define CIA_ICR_TB   0x02
DECL|macro|CIA_ICR_ALRM
mdefine_line|#define CIA_ICR_ALRM 0x04
DECL|macro|CIA_ICR_SP
mdefine_line|#define CIA_ICR_SP   0x08
DECL|macro|CIA_ICR_FLG
mdefine_line|#define CIA_ICR_FLG  0x10
macro_line|#endif /* asm-m68k/amigaints.h */
eof
