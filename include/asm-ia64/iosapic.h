macro_line|#ifndef __ASM_IA64_IOSAPIC_H
DECL|macro|__ASM_IA64_IOSAPIC_H
mdefine_line|#define __ASM_IA64_IOSAPIC_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|IO_SAPIC_DEFAULT_ADDR
mdefine_line|#define&t;IO_SAPIC_DEFAULT_ADDR&t;0xFEC00000
DECL|macro|IO_SAPIC_REG_SELECT
mdefine_line|#define&t;IO_SAPIC_REG_SELECT&t;0x0
DECL|macro|IO_SAPIC_WINDOW
mdefine_line|#define&t;IO_SAPIC_WINDOW&t;&t;0x10
DECL|macro|IO_SAPIC_EOI
mdefine_line|#define&t;IO_SAPIC_EOI&t;&t;0x40
DECL|macro|IO_SAPIC_VERSION
mdefine_line|#define&t;IO_SAPIC_VERSION&t;0x1
multiline_comment|/*&n; * Redirection table entry&n; */
DECL|macro|IO_SAPIC_RTE_LOW
mdefine_line|#define&t;IO_SAPIC_RTE_LOW(i)&t;(0x10+i*2)
DECL|macro|IO_SAPIC_RTE_HIGH
mdefine_line|#define&t;IO_SAPIC_RTE_HIGH(i)&t;(0x11+i*2)
DECL|macro|IO_SAPIC_DEST_SHIFT
mdefine_line|#define&t;IO_SAPIC_DEST_SHIFT&t;&t;16
multiline_comment|/*&n; * Delivery mode&n; */
DECL|macro|IO_SAPIC_DELIVERY_SHIFT
mdefine_line|#define&t;IO_SAPIC_DELIVERY_SHIFT&t;&t;8
DECL|macro|IO_SAPIC_FIXED
mdefine_line|#define&t;IO_SAPIC_FIXED&t;&t;&t;0x0
DECL|macro|IO_SAPIC_LOWEST_PRIORITY
mdefine_line|#define&t;IO_SAPIC_LOWEST_PRIORITY&t;0x1
DECL|macro|IO_SAPIC_PMI
mdefine_line|#define&t;IO_SAPIC_PMI&t;&t;&t;0x2
DECL|macro|IO_SAPIC_NMI
mdefine_line|#define&t;IO_SAPIC_NMI&t;&t;&t;0x4
DECL|macro|IO_SAPIC_INIT
mdefine_line|#define&t;IO_SAPIC_INIT&t;&t;&t;0x5
DECL|macro|IO_SAPIC_EXTINT
mdefine_line|#define&t;IO_SAPIC_EXTINT&t;&t;&t;0x7
multiline_comment|/*&n; * Interrupt polarity&n; */
DECL|macro|IO_SAPIC_POLARITY_SHIFT
mdefine_line|#define&t;IO_SAPIC_POLARITY_SHIFT&t;&t;13
DECL|macro|IO_SAPIC_POL_HIGH
mdefine_line|#define&t;IO_SAPIC_POL_HIGH&t;&t;0
DECL|macro|IO_SAPIC_POL_LOW
mdefine_line|#define&t;IO_SAPIC_POL_LOW&t;&t;1
multiline_comment|/*&n; * Trigger mode&n; */
DECL|macro|IO_SAPIC_TRIGGER_SHIFT
mdefine_line|#define&t;IO_SAPIC_TRIGGER_SHIFT&t;&t;15
DECL|macro|IO_SAPIC_EDGE
mdefine_line|#define&t;IO_SAPIC_EDGE&t;&t;&t;0
DECL|macro|IO_SAPIC_LEVEL
mdefine_line|#define&t;IO_SAPIC_LEVEL&t;&t;&t;1
multiline_comment|/*&n; * Mask bit&n; */
DECL|macro|IO_SAPIC_MASK_SHIFT
mdefine_line|#define&t;IO_SAPIC_MASK_SHIFT&t;&t;16
DECL|macro|IO_SAPIC_UNMASK
mdefine_line|#define&t;IO_SAPIC_UNMASK&t;&t;&t;0
DECL|macro|IO_SAPIC_MSAK
mdefine_line|#define&t;IO_SAPIC_MSAK&t;&t;&t;1
multiline_comment|/*&n; * Bus types&n; */
DECL|macro|BUS_ISA
mdefine_line|#define  BUS_ISA         0               /* ISA Bus */
DECL|macro|BUS_PCI
mdefine_line|#define  BUS_PCI         1               /* PCI Bus */
macro_line|#ifndef CONFIG_IA64_PCI_FIRMWARE_IRQ
DECL|struct|intr_routing_entry
r_struct
id|intr_routing_entry
(brace
DECL|member|srcbus
r_int
r_char
id|srcbus
suffix:semicolon
DECL|member|srcbusno
r_int
r_char
id|srcbusno
suffix:semicolon
DECL|member|srcbusirq
r_int
r_char
id|srcbusirq
suffix:semicolon
DECL|member|iosapic_pin
r_int
r_char
id|iosapic_pin
suffix:semicolon
DECL|member|dstiosapic
r_int
r_char
id|dstiosapic
suffix:semicolon
DECL|member|mode
r_int
r_char
id|mode
suffix:semicolon
DECL|member|trigger
r_int
r_char
id|trigger
suffix:semicolon
DECL|member|polarity
r_int
r_char
id|polarity
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|intr_routing_entry
id|intr_routing
(braket
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/irq.h&gt;
multiline_comment|/*&n; * IOSAPIC Version Register return 32 bit structure like:&n; * {&n; *&t;unsigned int version   : 8;&n; *&t;unsigned int reserved1 : 8;&n; *&t;unsigned int pins      : 8;&n; *&t;unsigned int reserved2 : 8;&n; * }&n; */
r_extern
r_int
r_int
id|iosapic_version
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|iosapic_init
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|struct|iosapic_vector
r_struct
id|iosapic_vector
(brace
DECL|member|iosapic_base
r_int
r_int
id|iosapic_base
suffix:semicolon
multiline_comment|/* IOSAPIC Base address */
DECL|member|pin
r_char
id|pin
suffix:semicolon
multiline_comment|/* IOSAPIC pin (-1 == No data) */
DECL|member|bus
r_int
r_char
id|bus
suffix:semicolon
multiline_comment|/* Bus number */
DECL|member|baseirq
r_int
r_char
id|baseirq
suffix:semicolon
multiline_comment|/* Base IRQ handled by this IOSAPIC */
DECL|member|bustype
r_int
r_char
id|bustype
suffix:semicolon
multiline_comment|/* Bus type (ISA, PCI, etc) */
DECL|member|busdata
r_int
r_int
id|busdata
suffix:semicolon
multiline_comment|/* Bus specific ID */
multiline_comment|/* These bitfields use the values defined above */
DECL|member|dmode
r_int
r_char
id|dmode
suffix:colon
l_int|3
suffix:semicolon
DECL|member|polarity
r_int
r_char
id|polarity
suffix:colon
l_int|1
suffix:semicolon
DECL|member|trigger
r_int
r_char
id|trigger
suffix:colon
l_int|1
suffix:semicolon
DECL|member|UNUSED
r_int
r_char
id|UNUSED
suffix:colon
l_int|3
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|iosapic_vector
id|iosapic_vector
(braket
id|NR_IRQS
)braket
suffix:semicolon
DECL|macro|iosapic_addr
mdefine_line|#define iosapic_addr(v)     iosapic_vector[v].iosapic_base
DECL|macro|iosapic_pin
mdefine_line|#define iosapic_pin(v)      iosapic_vector[v].pin
DECL|macro|iosapic_bus
mdefine_line|#define iosapic_bus(v)      iosapic_vector[v].bus
DECL|macro|iosapic_baseirq
mdefine_line|#define iosapic_baseirq(v)  iosapic_vector[v].baseirq
DECL|macro|iosapic_bustype
mdefine_line|#define iosapic_bustype(v)  iosapic_vector[v].bustype
DECL|macro|iosapic_busdata
mdefine_line|#define iosapic_busdata(v)  iosapic_vector[v].busdata
DECL|macro|iosapic_dmode
mdefine_line|#define iosapic_dmode(v)    iosapic_vector[v].dmode
DECL|macro|iosapic_trigger
mdefine_line|#define iosapic_trigger(v)  iosapic_vector[v].trigger
DECL|macro|iosapic_polarity
mdefine_line|#define iosapic_polarity(v) iosapic_vector[v].polarity
macro_line|# endif /* !__ASSEMBLY__ */
macro_line|#endif /* __ASM_IA64_IOSAPIC_H */
eof
