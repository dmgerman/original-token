macro_line|#ifndef __ALPHA_IRONGATE__H__
DECL|macro|__ALPHA_IRONGATE__H__
mdefine_line|#define __ALPHA_IRONGATE__H__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/compiler.h&gt;
multiline_comment|/*&n; * IRONGATE is the internal name for the AMD-751 K7 core logic chipset&n; * which provides memory controller and PCI access for NAUTILUS-based&n; * EV6 (21264) systems.&n; *&n; * This file is based on:&n; *&n; * IronGate management library, (c) 1999 Alpha Processor, Inc.&n; * Begun 19 January 1999 by Stig Telfer, Alpha Processor, Inc.&n; */
multiline_comment|/*&n; * The 21264 supports, and internally recognizes, a 44-bit physical&n; * address space that is divided equally between memory address space&n; * and I/O address space. Memory address space resides in the lower&n; * half of the physical address space (PA[43]=0) and I/O address space&n; * resides in the upper half of the physical address space (PA[43]=1).&n; *&n; */
multiline_comment|/* Eh? Not offset from memory?  */
DECL|macro|IRONGATE_DMA_WIN_BASE
mdefine_line|#define IRONGATE_DMA_WIN_BASE&t;&t; (0U)
DECL|macro|IRONGATE_DMA_WIN_SIZE
mdefine_line|#define IRONGATE_DMA_WIN_SIZE&t;&t; (0U)
multiline_comment|/*&n; * Irongate CSR map.  Some of the CSRs are 8 or 16 bits, but all access&n; * through the routines given is 32-bit.&n; *&n; * The first 0x40 bytes are standard as per the PCI spec.&n; */
DECL|typedef|igcsr32
r_typedef
r_volatile
id|__u32
id|igcsr32
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|dev_vendor
id|igcsr32
id|dev_vendor
suffix:semicolon
multiline_comment|/* 0x00 - device ID, vendor ID */
DECL|member|stat_cmd
id|igcsr32
id|stat_cmd
suffix:semicolon
multiline_comment|/* 0x04 - status, command */
DECL|member|class
id|igcsr32
r_class
suffix:semicolon
multiline_comment|/* 0x08 - class code, rev ID */
DECL|member|latency
id|igcsr32
id|latency
suffix:semicolon
multiline_comment|/* 0x0C - header type, PCI latency */
DECL|member|bar0
id|igcsr32
id|bar0
suffix:semicolon
multiline_comment|/* 0x10 - BAR0 - AGP */
DECL|member|bar1
id|igcsr32
id|bar1
suffix:semicolon
multiline_comment|/* 0x14 - BAR1 - GART */
DECL|member|bar2
id|igcsr32
id|bar2
suffix:semicolon
multiline_comment|/* 0x18 - Power Management reg block */
DECL|member|rsrvd0
id|igcsr32
id|rsrvd0
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* 0x1C-0x33 reserved */
DECL|member|capptr
id|igcsr32
id|capptr
suffix:semicolon
multiline_comment|/* 0x34 - Capabilities pointer */
DECL|member|rsrvd1
id|igcsr32
id|rsrvd1
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x38-0x3F reserved */
DECL|member|bacsr10
id|igcsr32
id|bacsr10
suffix:semicolon
multiline_comment|/* 0x40 - base address chip selects */
DECL|member|bacsr32
id|igcsr32
id|bacsr32
suffix:semicolon
multiline_comment|/* 0x44 - base address chip selects */
DECL|member|bacsr54
id|igcsr32
id|bacsr54
suffix:semicolon
multiline_comment|/* 0x48 - base address chip selects */
DECL|member|rsrvd2
id|igcsr32
id|rsrvd2
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* 0x4C-0x4F reserved */
DECL|member|drammap
id|igcsr32
id|drammap
suffix:semicolon
multiline_comment|/* 0x50 - address mapping control */
DECL|member|dramtm
id|igcsr32
id|dramtm
suffix:semicolon
multiline_comment|/* 0x54 - timing, driver strength */
DECL|member|dramms
id|igcsr32
id|dramms
suffix:semicolon
multiline_comment|/* 0x58 - ECC, mode/status */
DECL|member|rsrvd3
id|igcsr32
id|rsrvd3
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* 0x5C-0x5F reserved */
DECL|member|biu0
id|igcsr32
id|biu0
suffix:semicolon
multiline_comment|/* 0x60 - bus interface unit */
DECL|member|biusip
id|igcsr32
id|biusip
suffix:semicolon
multiline_comment|/* 0x64 - Serial initialisation pkt */
DECL|member|rsrvd4
id|igcsr32
id|rsrvd4
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x68-0x6F reserved */
DECL|member|mro
id|igcsr32
id|mro
suffix:semicolon
multiline_comment|/* 0x70 - memory request optimiser */
DECL|member|rsrvd5
id|igcsr32
id|rsrvd5
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 0x74-0x7F reserved */
DECL|member|whami
id|igcsr32
id|whami
suffix:semicolon
multiline_comment|/* 0x80 - who am I */
DECL|member|pciarb
id|igcsr32
id|pciarb
suffix:semicolon
multiline_comment|/* 0x84 - PCI arbitration control */
DECL|member|pcicfg
id|igcsr32
id|pcicfg
suffix:semicolon
multiline_comment|/* 0x88 - PCI config status */
DECL|member|rsrvd6
id|igcsr32
id|rsrvd6
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* 0x8C-0x9F reserved */
multiline_comment|/* AGP (bus 1) control registers */
DECL|member|agpcap
id|igcsr32
id|agpcap
suffix:semicolon
multiline_comment|/* 0xA0 - AGP Capability Identifier */
DECL|member|agpstat
id|igcsr32
id|agpstat
suffix:semicolon
multiline_comment|/* 0xA4 - AGP status register */
DECL|member|agpcmd
id|igcsr32
id|agpcmd
suffix:semicolon
multiline_comment|/* 0xA8 - AGP control register */
DECL|member|agpva
id|igcsr32
id|agpva
suffix:semicolon
multiline_comment|/* 0xAC - AGP Virtual Address Space */
DECL|member|agpmode
id|igcsr32
id|agpmode
suffix:semicolon
multiline_comment|/* 0xB0 - AGP/GART mode control */
DECL|typedef|Irongate0
)brace
id|Irongate0
suffix:semicolon
multiline_comment|/* Bitfield and mask register definitions */
multiline_comment|/* Device, vendor IDs - offset 0x00 */
r_typedef
r_union
(brace
DECL|member|i
id|igcsr32
id|i
suffix:semicolon
multiline_comment|/* integer value of CSR */
r_struct
(brace
DECL|member|v
r_int
id|v
suffix:colon
l_int|16
suffix:semicolon
DECL|member|d
r_int
id|d
suffix:colon
l_int|16
suffix:semicolon
DECL|member|r
)brace
id|r
suffix:semicolon
multiline_comment|/* structured interpretation */
DECL|typedef|ig_dev_vendor_t
)brace
id|ig_dev_vendor_t
suffix:semicolon
multiline_comment|/* Status, command registers - offset 0x04 */
r_typedef
r_union
(brace
DECL|member|i
id|igcsr32
id|i
suffix:semicolon
r_struct
(brace
DECL|member|command
r_int
id|command
suffix:semicolon
DECL|member|status
r_int
id|status
suffix:semicolon
DECL|member|s
)brace
id|s
suffix:semicolon
r_struct
(brace
multiline_comment|/* command register fields */
DECL|member|iospc
r_int
id|iospc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always reads zero */
DECL|member|memspc
r_int
id|memspc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* PCI memory space accesses? */
DECL|member|iten
r_int
id|iten
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 1: can be bus initiator */
DECL|member|scmon
r_int
id|scmon
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 0 special cycles not chckd */
DECL|member|mwic
r_int
id|mwic
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 0 - no mem write &amp; invalid */
DECL|member|vgaps
r_int
id|vgaps
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* always 0 - palette rds not special */
DECL|member|per
r_int
id|per
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* parity error resp: always 0 */
DECL|member|step
r_int
id|step
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* address/data stepping : always 0 */
DECL|member|serre
r_int
id|serre
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 1 = sys err output driver enable */
DECL|member|fbbce
r_int
id|fbbce
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* fast back-back cycle : always 0 */
DECL|member|zero1
r_int
id|zero1
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* must be zero */
multiline_comment|/* status register fields */
DECL|member|zero2
r_int
id|zero2
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* must be zero */
DECL|member|cl
r_int
id|cl
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* config space capa list: always 1 */
DECL|member|pci66
r_int
id|pci66
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 66 MHz PCI support - always 0 */
DECL|member|udf
r_int
id|udf
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* user defined features - always 0 */
DECL|member|fbbc
r_int
id|fbbc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* back-back transactions - always 0 */
DECL|member|ppe
r_int
id|ppe
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* PCI parity error detected (0) */
DECL|member|devsel
r_int
id|devsel
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* DEVSEL timing (always 01) */
DECL|member|sta
r_int
id|sta
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* signalled target abort (0) */
DECL|member|rta
r_int
id|rta
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* recvd target abort */
DECL|member|ria
r_int
id|ria
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* recvd initiator abort */
DECL|member|serr
r_int
id|serr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* SERR has been asserted */
DECL|member|dpe
r_int
id|dpe
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* DRAM parity error (0) */
DECL|member|r
)brace
id|r
suffix:semicolon
DECL|typedef|ig_stat_cmd_t
)brace
id|ig_stat_cmd_t
suffix:semicolon
multiline_comment|/* Revision ID, Programming interface, subclass, baseclass - offset 0x08 */
r_typedef
r_union
(brace
DECL|member|i
id|igcsr32
id|i
suffix:semicolon
r_struct
(brace
multiline_comment|/* revision ID */
DECL|member|step
r_int
id|step
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* stepping Revision ID */
DECL|member|die
r_int
id|die
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* die Revision ID */
DECL|member|pif
r_int
id|pif
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* programming interface (0x00) */
DECL|member|sub
r_int
id|sub
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* subclass code (0x00) */
DECL|member|base
r_int
id|base
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* baseclass code (0x06) */
DECL|member|r
)brace
id|r
suffix:semicolon
DECL|typedef|ig_class_t
)brace
id|ig_class_t
suffix:semicolon
multiline_comment|/* Latency Timer, PCI Header type - offset 0x0C */
r_typedef
r_union
(brace
DECL|member|i
id|igcsr32
id|i
suffix:semicolon
r_struct
(brace
DECL|member|zero1
r_int
id|zero1
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|lat
r_int
id|lat
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* latency in PCI bus clocks */
DECL|member|hdr
r_int
id|hdr
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* PCI header type */
DECL|member|zero2
r_int
id|zero2
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|r
)brace
id|r
suffix:semicolon
DECL|typedef|ig_latency_t
)brace
id|ig_latency_t
suffix:semicolon
multiline_comment|/* Base Address Register 0 - offset 0x10 */
r_typedef
r_union
(brace
DECL|member|i
id|igcsr32
id|i
suffix:semicolon
r_struct
(brace
DECL|member|mem
r_int
id|mem
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Reg pts to memory (always 0) */
DECL|member|type
r_int
id|type
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* 32 bit register = 0b00 */
DECL|member|pref
r_int
id|pref
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* graphics mem prefetchable=1 */
DECL|member|baddrl
r_int
id|baddrl
suffix:colon
l_int|21
suffix:semicolon
multiline_comment|/* 32M = minimum alloc -&gt; all zero */
DECL|member|size
r_int
id|size
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* size requirements for AGP */
DECL|member|zero
r_int
id|zero
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved=0 */
DECL|member|r
)brace
id|r
suffix:semicolon
DECL|typedef|ig_bar0_t
)brace
id|ig_bar0_t
suffix:semicolon
multiline_comment|/* Base Address Register 1 - offset 0x14 */
r_typedef
r_union
(brace
DECL|member|i
id|igcsr32
id|i
suffix:semicolon
r_struct
(brace
DECL|member|mem
r_int
id|mem
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* BAR0 maps to memory -&gt; 0 */
DECL|member|type
r_int
id|type
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* BAR1 is 32-bit -&gt; 0b00 */
DECL|member|pref
r_int
id|pref
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* graphics mem prefetchable=1 */
DECL|member|baddrl
r_int
id|baddrl
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* 4K alloc for AGP CSRs -&gt; 0b00 */
DECL|member|baddrh
r_int
id|baddrh
suffix:colon
l_int|20
suffix:semicolon
multiline_comment|/* base addr of AGP CSRs A[30:11] */
DECL|member|r
)brace
id|r
suffix:semicolon
DECL|typedef|ig_bar1_t
)brace
id|ig_bar1_t
suffix:semicolon
multiline_comment|/* Base Address Register 2 - offset 0x18 */
r_typedef
r_union
(brace
DECL|member|i
id|igcsr32
id|i
suffix:semicolon
r_struct
(brace
DECL|member|io
r_int
id|io
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* BAR2 maps to I/O space -&gt; 1 */
DECL|member|zero1
r_int
id|zero1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|addr
r_int
id|addr
suffix:colon
l_int|22
suffix:semicolon
multiline_comment|/* BAR2[31:10] - PM2_BLK base */
DECL|member|zero2
r_int
id|zero2
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|r
)brace
id|r
suffix:semicolon
DECL|typedef|ig_bar2_t
)brace
id|ig_bar2_t
suffix:semicolon
multiline_comment|/* Capabilities Pointer - offset 0x34 */
r_typedef
r_union
(brace
DECL|member|i
id|igcsr32
id|i
suffix:semicolon
r_struct
(brace
DECL|member|cap
r_int
id|cap
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* =0xA0, offset of AGP ctrl regs */
DECL|member|zero
r_int
id|zero
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|r
)brace
id|r
suffix:semicolon
DECL|typedef|ig_capptr_t
)brace
id|ig_capptr_t
suffix:semicolon
multiline_comment|/* Base Address Chip Select Register 1,0 - offset 0x40 */
multiline_comment|/* Base Address Chip Select Register 3,2 - offset 0x44 */
multiline_comment|/* Base Address Chip Select Register 5,4 - offset 0x48 */
r_typedef
r_union
(brace
DECL|member|i
id|igcsr32
id|i
suffix:semicolon
r_struct
(brace
multiline_comment|/* lower bank */
DECL|member|en0
r_int
id|en0
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* memory bank enabled */
DECL|member|mask0
r_int
id|mask0
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Address mask for A[28:23] */
DECL|member|base0
r_int
id|base0
suffix:colon
l_int|9
suffix:semicolon
multiline_comment|/* Bank Base Address A[31:23] */
multiline_comment|/* upper bank */
DECL|member|en1
r_int
id|en1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* memory bank enabled */
DECL|member|mask1
r_int
id|mask1
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Address mask for A[28:23] */
DECL|member|base1
r_int
id|base1
suffix:colon
l_int|9
suffix:semicolon
multiline_comment|/* Bank Base Address A[31:23] */
DECL|member|r
)brace
id|r
suffix:semicolon
DECL|typedef|ig_bacsr_t
DECL|typedef|ig_bacsr10_t
DECL|typedef|ig_bacsr32_t
DECL|typedef|ig_bacsr54_t
)brace
id|ig_bacsr_t
comma
id|ig_bacsr10_t
comma
id|ig_bacsr32_t
comma
id|ig_bacsr54_t
suffix:semicolon
multiline_comment|/* SDRAM Address Mapping Control Register - offset 0x50 */
r_typedef
r_union
(brace
DECL|member|i
id|igcsr32
id|i
suffix:semicolon
r_struct
(brace
DECL|member|z1
r_int
id|z1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|bnks0
r_int
id|bnks0
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0-&gt;2 banks in chip select 0 */
DECL|member|am0
r_int
id|am0
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* row/column addressing */
DECL|member|z2
r_int
id|z2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|z3
r_int
id|z3
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|bnks1
r_int
id|bnks1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0-&gt;2 banks in chip select 1 */
DECL|member|am1
r_int
id|am1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* row/column addressing */
DECL|member|z4
r_int
id|z4
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|z5
r_int
id|z5
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|bnks2
r_int
id|bnks2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0-&gt;2 banks in chip select 2 */
DECL|member|am2
r_int
id|am2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* row/column addressing */
DECL|member|z6
r_int
id|z6
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|z7
r_int
id|z7
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|bnks3
r_int
id|bnks3
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0-&gt;2 banks in chip select 3 */
DECL|member|am3
r_int
id|am3
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* row/column addressing */
DECL|member|z8
r_int
id|z8
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|z9
r_int
id|z9
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|bnks4
r_int
id|bnks4
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0-&gt;2 banks in chip select 4 */
DECL|member|am4
r_int
id|am4
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* row/column addressing */
DECL|member|z10
r_int
id|z10
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|z11
r_int
id|z11
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|bnks5
r_int
id|bnks5
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* 0-&gt;2 banks in chip select 5 */
DECL|member|am5
r_int
id|am5
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* row/column addressing */
DECL|member|z12
r_int
id|z12
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|rsrvd
r_int
id|rsrvd
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|r
)brace
id|r
suffix:semicolon
DECL|typedef|ig_drammap_t
)brace
id|ig_drammap_t
suffix:semicolon
multiline_comment|/* DRAM timing and driver strength register - offset 0x54 */
r_typedef
r_union
(brace
DECL|member|i
id|igcsr32
id|i
suffix:semicolon
r_struct
(brace
multiline_comment|/* DRAM timing parameters */
DECL|member|trcd
r_int
id|trcd
suffix:colon
l_int|2
suffix:semicolon
DECL|member|tcl
r_int
id|tcl
suffix:colon
l_int|2
suffix:semicolon
DECL|member|tras
r_int
id|tras
suffix:colon
l_int|3
suffix:semicolon
DECL|member|trp
r_int
id|trp
suffix:colon
l_int|2
suffix:semicolon
DECL|member|trc
r_int
id|trc
suffix:colon
l_int|3
suffix:semicolon
DECL|member|icl
r_int
id|icl
suffix:colon
l_int|2
suffix:semicolon
DECL|member|ph
r_int
id|ph
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Chipselect driver strength */
DECL|member|adra
r_int
id|adra
suffix:colon
l_int|1
suffix:semicolon
DECL|member|adrb
r_int
id|adrb
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ctrl
r_int
id|ctrl
suffix:colon
l_int|3
suffix:semicolon
DECL|member|dqm
r_int
id|dqm
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cs
r_int
id|cs
suffix:colon
l_int|1
suffix:semicolon
DECL|member|clk
r_int
id|clk
suffix:colon
l_int|1
suffix:semicolon
DECL|member|rsrvd
r_int
id|rsrvd
suffix:colon
l_int|8
suffix:semicolon
DECL|member|r
)brace
id|r
suffix:semicolon
DECL|typedef|ig_dramtm_t
)brace
id|ig_dramtm_t
suffix:semicolon
multiline_comment|/* DRAM Mode / Status and ECC Register - offset 0x58 */
r_typedef
r_union
(brace
DECL|member|i
id|igcsr32
id|i
suffix:semicolon
r_struct
(brace
DECL|member|chipsel
r_int
id|chipsel
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* failing ECC chip select */
DECL|member|zero1
r_int
id|zero1
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* always reads zero */
DECL|member|status
r_int
id|status
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* ECC Detect logic status */
DECL|member|zero2
r_int
id|zero2
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* always reads zero */
DECL|member|cycles
r_int
id|cycles
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* cycles per refresh, see table */
DECL|member|en
r_int
id|en
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* ECC enable */
DECL|member|r
r_int
id|r
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Large burst enable (=0) */
DECL|member|bre
r_int
id|bre
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Burst refresh enable */
DECL|member|zero3
r_int
id|zero3
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* reserved = 0 */
DECL|member|mwe
r_int
id|mwe
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Enable writes to DRAM mode reg */
DECL|member|type
r_int
id|type
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* SDRAM = 0, default */
DECL|member|sdraminit
r_int
id|sdraminit
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* SDRAM init - set params first! */
DECL|member|zero4
r_int
id|zero4
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* reserved = 0 */
DECL|member|r
)brace
id|r
suffix:semicolon
DECL|typedef|ig_dramms_t
)brace
id|ig_dramms_t
suffix:semicolon
multiline_comment|/*&n; * Memory spaces:&n; */
multiline_comment|/* ??? the following probably needs fixing */
multiline_comment|/* Irongate is consistent with a subset of the Tsunami memory map */
multiline_comment|/* XXX: Do we need to conditionalize on this?  */
macro_line|#ifdef USE_48_BIT_KSEG
DECL|macro|IRONGATE_BIAS
mdefine_line|#define IRONGATE_BIAS 0x80000000000UL
macro_line|#else
DECL|macro|IRONGATE_BIAS
mdefine_line|#define IRONGATE_BIAS 0x10000000000UL
macro_line|#endif
DECL|macro|IRONGATE_MEM
mdefine_line|#define IRONGATE_MEM&t;&t;(IDENT_ADDR | IRONGATE_BIAS | 0x000000000UL)
DECL|macro|IRONGATE_IACK_SC
mdefine_line|#define IRONGATE_IACK_SC&t;(IDENT_ADDR | IRONGATE_BIAS | 0x1F8000000UL)
DECL|macro|IRONGATE_IO
mdefine_line|#define IRONGATE_IO&t;&t;(IDENT_ADDR | IRONGATE_BIAS | 0x1FC000000UL)
DECL|macro|IRONGATE_CONF
mdefine_line|#define IRONGATE_CONF&t;&t;(IDENT_ADDR | IRONGATE_BIAS | 0x1FE000000UL)
DECL|macro|IRONGATE0
mdefine_line|#define IRONGATE0&t;&t;((Irongate0 *) IRONGATE_CONF)
multiline_comment|/*&n; * Data structure for handling IRONGATE machine checks:&n; * This is the standard OSF logout frame&n; */
DECL|macro|SCB_Q_SYSERR
mdefine_line|#define SCB_Q_SYSERR&t;0x620&t;&t;&t;/* OSF definitions */
DECL|macro|SCB_Q_PROCERR
mdefine_line|#define SCB_Q_PROCERR&t;0x630
DECL|macro|SCB_Q_SYSMCHK
mdefine_line|#define SCB_Q_SYSMCHK&t;0x660
DECL|macro|SCB_Q_PROCMCHK
mdefine_line|#define SCB_Q_PROCMCHK&t;0x670
DECL|struct|el_IRONGATE_sysdata_mcheck
r_struct
id|el_IRONGATE_sysdata_mcheck
(brace
DECL|member|FrameSize
id|__u32
id|FrameSize
suffix:semicolon
multiline_comment|/* Bytes, including this field */
DECL|member|FrameFlags
id|__u32
id|FrameFlags
suffix:semicolon
multiline_comment|/* &lt;31&gt; = Retry, &lt;30&gt; = Second Error */
DECL|member|CpuOffset
id|__u32
id|CpuOffset
suffix:semicolon
multiline_comment|/* Offset to CPU-specific into */
DECL|member|SystemOffset
id|__u32
id|SystemOffset
suffix:semicolon
multiline_comment|/* Offset to system-specific info */
DECL|member|MCHK_Code
id|__u32
id|MCHK_Code
suffix:semicolon
DECL|member|MCHK_Frame_Rev
id|__u32
id|MCHK_Frame_Rev
suffix:semicolon
DECL|member|I_STAT
id|__u64
id|I_STAT
suffix:semicolon
DECL|member|DC_STAT
id|__u64
id|DC_STAT
suffix:semicolon
DECL|member|C_ADDR
id|__u64
id|C_ADDR
suffix:semicolon
DECL|member|DC1_SYNDROME
id|__u64
id|DC1_SYNDROME
suffix:semicolon
DECL|member|DC0_SYNDROME
id|__u64
id|DC0_SYNDROME
suffix:semicolon
DECL|member|C_STAT
id|__u64
id|C_STAT
suffix:semicolon
DECL|member|C_STS
id|__u64
id|C_STS
suffix:semicolon
DECL|member|RESERVED0
id|__u64
id|RESERVED0
suffix:semicolon
DECL|member|EXC_ADDR
id|__u64
id|EXC_ADDR
suffix:semicolon
DECL|member|IER_CM
id|__u64
id|IER_CM
suffix:semicolon
DECL|member|ISUM
id|__u64
id|ISUM
suffix:semicolon
DECL|member|MM_STAT
id|__u64
id|MM_STAT
suffix:semicolon
DECL|member|PAL_BASE
id|__u64
id|PAL_BASE
suffix:semicolon
DECL|member|I_CTL
id|__u64
id|I_CTL
suffix:semicolon
DECL|member|PCTX
id|__u64
id|PCTX
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE extern inline
DECL|macro|__IO_EXTERN_INLINE
mdefine_line|#define __IO_EXTERN_INLINE
macro_line|#endif
multiline_comment|/*&n; * Translate physical memory address as seen on (PCI) bus into&n; * a kernel virtual address and vv.&n; */
DECL|function|irongate_virt_to_bus
id|__EXTERN_INLINE
r_int
r_int
id|irongate_virt_to_bus
c_func
(paren
r_void
op_star
id|address
)paren
(brace
r_return
id|virt_to_phys
c_func
(paren
id|address
)paren
op_plus
id|IRONGATE_DMA_WIN_BASE
suffix:semicolon
)brace
DECL|function|irongate_bus_to_virt
id|__EXTERN_INLINE
r_void
op_star
id|irongate_bus_to_virt
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_return
id|phys_to_virt
c_func
(paren
id|address
op_minus
id|IRONGATE_DMA_WIN_BASE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * I/O functions:&n; *&n; * IRONGATE (AMD-751) PCI/memory support chip for the EV6 (21264) and&n; * K7 can only use linear accesses to get at PCI memory and I/O spaces.&n; */
DECL|macro|vucp
mdefine_line|#define vucp&t;volatile unsigned char *
DECL|macro|vusp
mdefine_line|#define vusp&t;volatile unsigned short *
DECL|macro|vuip
mdefine_line|#define vuip&t;volatile unsigned int *
DECL|macro|vulp
mdefine_line|#define vulp&t;volatile unsigned long *
DECL|function|irongate_inb
id|__EXTERN_INLINE
r_int
r_int
id|irongate_inb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|__kernel_ldbu
c_func
(paren
op_star
(paren
id|vucp
)paren
(paren
id|addr
op_plus
id|IRONGATE_IO
)paren
)paren
suffix:semicolon
)brace
DECL|function|irongate_outb
id|__EXTERN_INLINE
r_void
id|irongate_outb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__kernel_stb
c_func
(paren
id|b
comma
op_star
(paren
id|vucp
)paren
(paren
id|addr
op_plus
id|IRONGATE_IO
)paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|irongate_inw
id|__EXTERN_INLINE
r_int
r_int
id|irongate_inw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|__kernel_ldwu
c_func
(paren
op_star
(paren
id|vusp
)paren
(paren
id|addr
op_plus
id|IRONGATE_IO
)paren
)paren
suffix:semicolon
)brace
DECL|function|irongate_outw
id|__EXTERN_INLINE
r_void
id|irongate_outw
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__kernel_stw
c_func
(paren
id|b
comma
op_star
(paren
id|vusp
)paren
(paren
id|addr
op_plus
id|IRONGATE_IO
)paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|irongate_inl
id|__EXTERN_INLINE
r_int
r_int
id|irongate_inl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
id|vuip
)paren
(paren
id|addr
op_plus
id|IRONGATE_IO
)paren
suffix:semicolon
)brace
DECL|function|irongate_outl
id|__EXTERN_INLINE
r_void
id|irongate_outl
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
id|vuip
)paren
(paren
id|addr
op_plus
id|IRONGATE_IO
)paren
op_assign
id|b
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Memory functions.  All accesses are done through linear space.&n; */
DECL|function|irongate_readb
id|__EXTERN_INLINE
r_int
r_int
id|irongate_readb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|__kernel_ldbu
c_func
(paren
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|irongate_readw
id|__EXTERN_INLINE
r_int
r_int
id|irongate_readw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|__kernel_ldwu
c_func
(paren
op_star
(paren
id|vusp
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|irongate_readl
id|__EXTERN_INLINE
r_int
r_int
id|irongate_readl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
id|vuip
)paren
id|addr
suffix:semicolon
)brace
DECL|function|irongate_readq
id|__EXTERN_INLINE
r_int
r_int
id|irongate_readq
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
id|vulp
)paren
id|addr
suffix:semicolon
)brace
DECL|function|irongate_writeb
id|__EXTERN_INLINE
r_void
id|irongate_writeb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__kernel_stb
c_func
(paren
id|b
comma
op_star
(paren
id|vucp
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|irongate_writew
id|__EXTERN_INLINE
r_void
id|irongate_writew
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__kernel_stw
c_func
(paren
id|b
comma
op_star
(paren
id|vusp
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|irongate_writel
id|__EXTERN_INLINE
r_void
id|irongate_writel
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
id|vuip
)paren
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|function|irongate_writeq
id|__EXTERN_INLINE
r_void
id|irongate_writeq
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
id|vulp
)paren
id|addr
op_assign
id|b
suffix:semicolon
)brace
DECL|function|irongate_ioremap
id|__EXTERN_INLINE
r_int
r_int
id|irongate_ioremap
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|addr
op_plus
id|IRONGATE_MEM
suffix:semicolon
)brace
DECL|function|irongate_is_ioaddr
id|__EXTERN_INLINE
r_int
id|irongate_is_ioaddr
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|addr
op_ge
id|IRONGATE_MEM
suffix:semicolon
)brace
DECL|macro|vucp
macro_line|#undef vucp
DECL|macro|vusp
macro_line|#undef vusp
DECL|macro|vuip
macro_line|#undef vuip
DECL|macro|vulp
macro_line|#undef vulp
macro_line|#ifdef __WANT_IO_DEF
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus&t;irongate_virt_to_bus
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt&t;irongate_bus_to_virt
DECL|macro|__inb
mdefine_line|#define __inb&t;&t;irongate_inb
DECL|macro|__inw
mdefine_line|#define __inw&t;&t;irongate_inw
DECL|macro|__inl
mdefine_line|#define __inl&t;&t;irongate_inl
DECL|macro|__outb
mdefine_line|#define __outb&t;&t;irongate_outb
DECL|macro|__outw
mdefine_line|#define __outw&t;&t;irongate_outw
DECL|macro|__outl
mdefine_line|#define __outl&t;&t;irongate_outl
DECL|macro|__readb
mdefine_line|#define __readb&t;&t;irongate_readb
DECL|macro|__readw
mdefine_line|#define __readw&t;&t;irongate_readw
DECL|macro|__writeb
mdefine_line|#define __writeb&t;irongate_writeb
DECL|macro|__writew
mdefine_line|#define __writew&t;irongate_writew
DECL|macro|__readl
mdefine_line|#define __readl&t;&t;irongate_readl
DECL|macro|__readq
mdefine_line|#define __readq&t;&t;irongate_readq
DECL|macro|__writel
mdefine_line|#define __writel&t;irongate_writel
DECL|macro|__writeq
mdefine_line|#define __writeq&t;irongate_writeq
DECL|macro|__ioremap
mdefine_line|#define __ioremap&t;irongate_ioremap
DECL|macro|__is_ioaddr
mdefine_line|#define __is_ioaddr&t;irongate_is_ioaddr
DECL|macro|inb
mdefine_line|#define inb(port)&t;__inb((port))
DECL|macro|inw
mdefine_line|#define inw(port)&t;__inw((port))
DECL|macro|inl
mdefine_line|#define inl(port)&t;__inl((port))
DECL|macro|outb
mdefine_line|#define outb(v, port)&t;__outb((v),(port))
DECL|macro|outw
mdefine_line|#define outw(v, port)&t;__outw((v),(port))
DECL|macro|outl
mdefine_line|#define outl(v, port)&t;__outl((v),(port))
DECL|macro|__raw_readb
mdefine_line|#define __raw_readb(a)&t;&t;__readb((unsigned long)(a))
DECL|macro|__raw_readw
mdefine_line|#define __raw_readw(a)&t;&t;__readw((unsigned long)(a))
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl(a)&t;&t;__readl((unsigned long)(a))
DECL|macro|__raw_readq
mdefine_line|#define __raw_readq(a)&t;&t;__readq((unsigned long)(a))
DECL|macro|__raw_writeb
mdefine_line|#define __raw_writeb(v,a)&t;__writeb((v),(unsigned long)(a))
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew(v,a)&t;__writew((v),(unsigned long)(a))
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel(v,a)&t;__writel((v),(unsigned long)(a))
DECL|macro|__raw_writeq
mdefine_line|#define __raw_writeq(v,a)&t;__writeq((v),(unsigned long)(a))
macro_line|#endif /* __WANT_IO_DEF */
macro_line|#ifdef __IO_EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
DECL|macro|__IO_EXTERN_INLINE
macro_line|#undef __IO_EXTERN_INLINE
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ALPHA_IRONGATE__H__ */
eof
