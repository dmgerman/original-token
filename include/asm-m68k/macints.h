multiline_comment|/*&n;** macints.h -- Macintosh Linux interrupt handling structs and prototypes&n;**&n;** Copyright 1997 by Michael Schmitz&n;**&n;** This file is subject to the terms and conditions of the GNU General Public&n;** License.  See the file COPYING in the main directory of this archive&n;** for more details.&n;**&n;*/
macro_line|#ifndef _ASM_MACINTS_H_
DECL|macro|_ASM_MACINTS_H_
mdefine_line|#define _ASM_MACINTS_H_
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/*&n;** Macintosh Interrupt sources.&n;**&n;** Note: these are all routed via the generic VIA interrupt routine!&n;**&n;*/
DECL|macro|SRC_VIA1
mdefine_line|#define SRC_VIA1&t;&t;0
DECL|macro|SRC_VIA2
mdefine_line|#define SRC_VIA2&t;&t;1
DECL|macro|VIA1_SOURCE_BASE
mdefine_line|#define VIA1_SOURCE_BASE&t;8
DECL|macro|VIA2_SOURCE_BASE
mdefine_line|#define VIA2_SOURCE_BASE&t;16
DECL|macro|RBF_SOURCE_BASE
mdefine_line|#define RBF_SOURCE_BASE&t;&t;24
DECL|macro|MAC_SCC_SOURCE_BASE
mdefine_line|#define MAC_SCC_SOURCE_BASE&t;32
DECL|macro|NUBUS_SOURCE_BASE
mdefine_line|#define NUBUS_SOURCE_BASE&t;40
DECL|macro|NUBUS_MAX_SOURCES
mdefine_line|#define NUBUS_MAX_SOURCES&t;8
multiline_comment|/* FIXME: sources not contigous ... */
DECL|macro|NUM_MAC_SOURCES
mdefine_line|#define NUM_MAC_SOURCES   (NUBUS_SOURCE_BASE+NUBUS_MAX_SOURCES-VIA1_SOURCE_BASE)
DECL|macro|IRQ_SRC_MASK
mdefine_line|#define IRQ_SRC_MASK (VIA1_SOURCE_BASE|VIA2_SOURCE_BASE|MAC_SCC_SOURCE_BASE)
DECL|macro|IRQ_IDX_MASK
mdefine_line|#define IRQ_IDX_MASK 7
multiline_comment|/* &n; * quick hack to adapt old MACHSPEC-aware source&n; */
DECL|macro|IRQ_IDX
mdefine_line|#define&t;IRQ_IDX(irq)&t;(irq)
macro_line|#if 0
multiline_comment|/* convert vector number to int source number */
mdefine_line|#define IRQ_VECTOR_TO_SOURCE(v)&t;(v)
multiline_comment|/* convert irq_handler index to vector number */
mdefine_line|#define IRQ_SOURCE_TO_VECTOR(i)&t;(i)
macro_line|#endif
multiline_comment|/* interrupt service types */
DECL|macro|IRQ_TYPE_SLOW
mdefine_line|#define IRQ_TYPE_SLOW     0
DECL|macro|IRQ_TYPE_FAST
mdefine_line|#define IRQ_TYPE_FAST     1
DECL|macro|IRQ_TYPE_PRIO
mdefine_line|#define IRQ_TYPE_PRIO     2
DECL|macro|IRQ_SPURIOUS
mdefine_line|#define&t;IRQ_SPURIOUS      (0)
multiline_comment|/* auto-vector interrupts */
DECL|macro|IRQ_AUTO_1
mdefine_line|#define IRQ_AUTO_1        (1)
DECL|macro|IRQ_AUTO_2
mdefine_line|#define IRQ_AUTO_2        (2)
DECL|macro|IRQ_AUTO_3
mdefine_line|#define IRQ_AUTO_3        (3)
DECL|macro|IRQ_AUTO_4
mdefine_line|#define IRQ_AUTO_4        (4)
DECL|macro|IRQ_AUTO_5
mdefine_line|#define IRQ_AUTO_5        (5)
DECL|macro|IRQ_AUTO_6
mdefine_line|#define IRQ_AUTO_6        (6)
DECL|macro|IRQ_AUTO_7
mdefine_line|#define IRQ_AUTO_7        (7)
multiline_comment|/* VIA1 interrupts */
DECL|macro|IRQ_VIA1_0
mdefine_line|#define IRQ_VIA1_0&t;  (8)&t;/* one second int. */
DECL|macro|IRQ_VIA1_1
mdefine_line|#define IRQ_VIA1_1        (9)&t;/* VBlank int. */
DECL|macro|IRQ_MAC_VBL
mdefine_line|#define IRQ_MAC_VBL&t;  IRQ_VIA1_1
DECL|macro|IRQ_VIA1_2
mdefine_line|#define IRQ_VIA1_2 &t;  (10)&t;/* ADB SR shifts complete */
DECL|macro|IRQ_MAC_ADB
mdefine_line|#define IRQ_MAC_ADB&t;  IRQ_VIA1_2
DECL|macro|IRQ_MAC_ADB_SR
mdefine_line|#define IRQ_MAC_ADB_SR&t;  IRQ_VIA1_2
DECL|macro|IRQ_VIA1_3
mdefine_line|#define IRQ_VIA1_3&t;  (11)&t;/* ADB SR CB2 ?? */
DECL|macro|IRQ_MAC_ADB_SD
mdefine_line|#define IRQ_MAC_ADB_SD&t;  IRQ_VIA1_3
DECL|macro|IRQ_VIA1_4
mdefine_line|#define IRQ_VIA1_4        (12)&t;/* ADB SR ext. clock pulse */
DECL|macro|IRQ_MAC_ADB_CL
mdefine_line|#define IRQ_MAC_ADB_CL&t;  IRQ_VIA1_4
DECL|macro|IRQ_VIA1_5
mdefine_line|#define IRQ_VIA1_5&t;  (13)
DECL|macro|IRQ_MAC_TIMER_2
mdefine_line|#define IRQ_MAC_TIMER_2&t;  IRQ_VIA1_5
DECL|macro|IRQ_VIA1_6
mdefine_line|#define IRQ_VIA1_6&t;  (14)
DECL|macro|IRQ_MAC_TIMER_1
mdefine_line|#define IRQ_MAC_TIMER_1&t;  IRQ_VIA1_6
DECL|macro|IRQ_VIA1_7
mdefine_line|#define IRQ_VIA1_7        (15)
multiline_comment|/* VIA2 interrupts */
DECL|macro|IRQ_VIA2_0
mdefine_line|#define IRQ_VIA2_0&t;  (16)
DECL|macro|IRQ_MAC_SCSIDRQ
mdefine_line|#define IRQ_MAC_SCSIDRQ&t;  IRQ_VIA2_0
DECL|macro|IRQ_VIA2_1
mdefine_line|#define IRQ_VIA2_1        (17)
DECL|macro|IRQ_MAC_NUBUS
mdefine_line|#define IRQ_MAC_NUBUS&t;  IRQ_VIA2_1
DECL|macro|IRQ_VIA2_2
mdefine_line|#define IRQ_VIA2_2 &t;  (18)
DECL|macro|IRQ_VIA2_3
mdefine_line|#define IRQ_VIA2_3&t;  (19)
DECL|macro|IRQ_MAC_SCSI
mdefine_line|#define IRQ_MAC_SCSI&t;  IRQ_VIA2_3
DECL|macro|IRQ_VIA2_4
mdefine_line|#define IRQ_VIA2_4        (20)
DECL|macro|IRQ_VIA2_5
mdefine_line|#define IRQ_VIA2_5&t;  (21)
DECL|macro|IRQ_VIA2_6
mdefine_line|#define IRQ_VIA2_6&t;  (22)
DECL|macro|IRQ_VIA2_7
mdefine_line|#define IRQ_VIA2_7        (23)
multiline_comment|/* RBV interrupts */
DECL|macro|IRQ_RBV_0
mdefine_line|#define IRQ_RBV_0&t;  (24)
DECL|macro|IRQ_RBV_1
mdefine_line|#define IRQ_RBV_1&t;  (25)
DECL|macro|IRQ_RBV_2
mdefine_line|#define IRQ_RBV_2 &t;  (26)
DECL|macro|IRQ_RBV_3
mdefine_line|#define IRQ_RBV_3&t;  (27)
DECL|macro|IRQ_RBV_4
mdefine_line|#define IRQ_RBV_4&t;  (28)
DECL|macro|IRQ_RBV_5
mdefine_line|#define IRQ_RBV_5&t;  (29)
DECL|macro|IRQ_RBV_6
mdefine_line|#define IRQ_RBV_6&t;  (30)
DECL|macro|IRQ_RBV_7
mdefine_line|#define IRQ_RBV_7&t;  (31)
DECL|macro|IRQ_SCC
mdefine_line|#define IRQ_SCC &t;     (32)
DECL|macro|IRQ_SCCB
mdefine_line|#define IRQ_SCCB&t;     (32)
DECL|macro|IRQ_SCCA
mdefine_line|#define IRQ_SCCA&t;     (33)
macro_line|#if 0 /* FIXME: are there multiple interrupt conditions on the SCC ?? */
multiline_comment|/* SCC interrupts */
mdefine_line|#define IRQ_SCCB_TX&t;     (32)
mdefine_line|#define IRQ_SCCB_STAT&t;     (33)
mdefine_line|#define IRQ_SCCB_RX&t;     (34)
mdefine_line|#define IRQ_SCCB_SPCOND&t;     (35)
mdefine_line|#define IRQ_SCCA_TX&t;     (36)
mdefine_line|#define IRQ_SCCA_STAT&t;     (37)
mdefine_line|#define IRQ_SCCA_RX&t;     (38)
mdefine_line|#define IRQ_SCCA_SPCOND&t;     (39)
macro_line|#endif
DECL|macro|IRQ_NUBUS_1
mdefine_line|#define IRQ_NUBUS_1&t;     (40)
DECL|macro|INT_CLK
mdefine_line|#define INT_CLK   24576&t;    /* CLK while int_clk =2.456MHz and divide = 100 */
DECL|macro|INT_TICKS
mdefine_line|#define INT_TICKS 246&t;    /* to make sched_time = 99.902... HZ */
DECL|macro|VIA_ENABLE
mdefine_line|#define VIA_ENABLE&t;0
DECL|macro|VIA_PENDING
mdefine_line|#define VIA_PENDING&t;1
DECL|macro|VIA_SERVICE
mdefine_line|#define VIA_SERVICE&t;2
DECL|macro|VIA_MASK
mdefine_line|#define VIA_MASK&t;3
multiline_comment|/* &n; * Utility functions for setting/clearing bits in the interrupt registers of&n; * the VIA. &n; */
r_void
id|mac_enable_irq
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_void
id|mac_disable_irq
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_void
id|mac_turnon_irq
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_void
id|mac_turnoff_irq
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_void
id|mac_clear_pending_irq
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_int
id|mac_irq_pending
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_int
id|nubus_request_irq
c_func
(paren
r_int
id|slot
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
)paren
suffix:semicolon
r_int
id|nubus_free_irq
c_func
(paren
r_int
id|slot
)paren
suffix:semicolon
r_int
r_int
id|mac_register_nubus_int
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|mac_unregister_nubus_int
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|mac_default_handler
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|via1_irq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|via2_irq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|rbv_irq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|mac_bang
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|mac_SCC_handler
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
macro_line|#endif /* asm/macints.h */
eof
