multiline_comment|/*&n; * $Id: prep_pci.c,v 1.31 1999/04/21 18:21:37 cort Exp $&n; * PReP pci functions.&n; * Originally by Gary Thomas&n; * rewritten and updated by Cort Dougan (cort@cs.nmt.edu)&n; *&n; * The motherboard routes/maps will disappear shortly. -- Cort&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/openpic.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/residual.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &quot;pci.h&quot;
DECL|macro|MAX_DEVNR
mdefine_line|#define MAX_DEVNR 22
multiline_comment|/* Which PCI interrupt line does a given device [slot] use? */
multiline_comment|/* Note: This really should be two dimensional based in slot/pin used */
DECL|variable|Motherboard_map
r_int
r_char
op_star
id|Motherboard_map
suffix:semicolon
DECL|variable|Motherboard_map_name
r_int
r_char
op_star
id|Motherboard_map_name
suffix:semicolon
multiline_comment|/* How is the 82378 PIRQ mapping setup? */
DECL|variable|Motherboard_routes
r_int
r_char
op_star
id|Motherboard_routes
suffix:semicolon
multiline_comment|/* Tables for known hardware */
multiline_comment|/* Motorola PowerStackII - Utah */
DECL|variable|__prepdata
r_static
r_char
id|Utah_pci_IRQ_map
(braket
l_int|23
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - unused */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|4
comma
multiline_comment|/* Slot 2  - SCSI - NCR825A  */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|1
comma
multiline_comment|/* Slot 4  - Ethernet - DEC2114x */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|2
comma
multiline_comment|/* Slot 6  - PCI Card slot #1 */
l_int|3
comma
multiline_comment|/* Slot 7  - PCI Card slot #2 */
l_int|4
comma
multiline_comment|/* Slot 8  - PCI Card slot #3 */
l_int|4
comma
multiline_comment|/* Slot 9  - PCI Bridge */
multiline_comment|/* added here in case we ever support PCI bridges */
multiline_comment|/* Secondary PCI bus cards are at slot-9,6 &amp; slot-9,7 */
l_int|0
comma
multiline_comment|/* Slot 10 - unused */
l_int|0
comma
multiline_comment|/* Slot 11 - unused */
l_int|4
comma
multiline_comment|/* Slot 12 - SCSI - NCR825A */
l_int|0
comma
multiline_comment|/* Slot 13 - unused */
l_int|2
comma
multiline_comment|/* Slot 14 - enet */
l_int|0
comma
multiline_comment|/* Slot 15 - unused */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|__prepdata
r_static
r_char
id|Utah_pci_IRQ_routes
(braket
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Line 0 - Unused */
l_int|9
comma
multiline_comment|/* Line 1 */
l_int|11
comma
multiline_comment|/* Line 2 */
l_int|14
comma
multiline_comment|/* Line 3 */
l_int|15
comma
multiline_comment|/* Line 4 */
)brace
suffix:semicolon
multiline_comment|/* Motorola PowerStackII - Omaha */
multiline_comment|/* no integrated SCSI or ethernet */
DECL|variable|__prepdata
r_static
r_char
id|Omaha_pci_IRQ_map
(braket
l_int|23
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - unused */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|3
comma
multiline_comment|/* Slot 2  - Winbond EIDE */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|0
comma
multiline_comment|/* Slot 4  - unused */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|1
comma
multiline_comment|/* Slot 6  - PCI slot 1 */
l_int|2
comma
multiline_comment|/* Slot 7  - PCI slot 2  */
l_int|3
comma
multiline_comment|/* Slot 8  - PCI slot 3 */
l_int|4
comma
multiline_comment|/* Slot 9  - PCI slot 4 */
multiline_comment|/* needs indirect access */
l_int|0
comma
multiline_comment|/* Slot 10 - unused */
l_int|0
comma
multiline_comment|/* Slot 11 - unused */
l_int|0
comma
multiline_comment|/* Slot 12 - unused */
l_int|0
comma
multiline_comment|/* Slot 13 - unused */
l_int|0
comma
multiline_comment|/* Slot 14 - unused */
l_int|0
comma
multiline_comment|/* Slot 15 - unused */
l_int|1
comma
multiline_comment|/* Slot 16  - PCI slot 1 */
l_int|2
comma
multiline_comment|/* Slot 17  - PCI slot 2  */
l_int|3
comma
multiline_comment|/* Slot 18  - PCI slot 3 */
l_int|4
comma
multiline_comment|/* Slot 19  - PCI slot 4 */
multiline_comment|/* needs indirect access */
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|__prepdata
r_static
r_char
id|Omaha_pci_IRQ_routes
(braket
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Line 0 - Unused */
l_int|9
comma
multiline_comment|/* Line 1 */
l_int|11
comma
multiline_comment|/* Line 2 */
l_int|14
comma
multiline_comment|/* Line 3 */
l_int|15
multiline_comment|/* Line 4 */
)brace
suffix:semicolon
multiline_comment|/* Motorola PowerStack */
DECL|variable|__prepdata
r_static
r_char
id|Blackhawk_pci_IRQ_map
(braket
l_int|19
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - unused */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|0
comma
multiline_comment|/* Slot 2  - unused */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|0
comma
multiline_comment|/* Slot 4  - unused */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|0
comma
multiline_comment|/* Slot 6  - unused */
l_int|0
comma
multiline_comment|/* Slot 7  - unused */
l_int|0
comma
multiline_comment|/* Slot 8  - unused */
l_int|0
comma
multiline_comment|/* Slot 9  - unused */
l_int|0
comma
multiline_comment|/* Slot 10 - unused */
l_int|0
comma
multiline_comment|/* Slot 11 - unused */
l_int|3
comma
multiline_comment|/* Slot 12 - SCSI */
l_int|0
comma
multiline_comment|/* Slot 13 - unused */
l_int|1
comma
multiline_comment|/* Slot 14 - Ethernet */
l_int|0
comma
multiline_comment|/* Slot 15 - unused */
l_int|1
comma
multiline_comment|/* Slot P7 */
l_int|2
comma
multiline_comment|/* Slot P6 */
l_int|3
comma
multiline_comment|/* Slot P5 */
)brace
suffix:semicolon
DECL|variable|__prepdata
r_static
r_char
id|Blackhawk_pci_IRQ_routes
(braket
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Line 0 - Unused */
l_int|9
comma
multiline_comment|/* Line 1 */
l_int|11
comma
multiline_comment|/* Line 2 */
l_int|15
comma
multiline_comment|/* Line 3 */
l_int|15
multiline_comment|/* Line 4 */
)brace
suffix:semicolon
multiline_comment|/* Motorola MVME16xx */
DECL|variable|__prepdata
r_static
r_char
id|Genesis_pci_IRQ_map
(braket
l_int|16
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - unused */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|0
comma
multiline_comment|/* Slot 2  - unused */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|0
comma
multiline_comment|/* Slot 4  - unused */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|0
comma
multiline_comment|/* Slot 6  - unused */
l_int|0
comma
multiline_comment|/* Slot 7  - unused */
l_int|0
comma
multiline_comment|/* Slot 8  - unused */
l_int|0
comma
multiline_comment|/* Slot 9  - unused */
l_int|0
comma
multiline_comment|/* Slot 10 - unused */
l_int|0
comma
multiline_comment|/* Slot 11 - unused */
l_int|3
comma
multiline_comment|/* Slot 12 - SCSI */
l_int|0
comma
multiline_comment|/* Slot 13 - unused */
l_int|1
comma
multiline_comment|/* Slot 14 - Ethernet */
l_int|0
comma
multiline_comment|/* Slot 15 - unused */
)brace
suffix:semicolon
DECL|variable|__prepdata
r_static
r_char
id|Genesis_pci_IRQ_routes
(braket
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Line 0 - Unused */
l_int|10
comma
multiline_comment|/* Line 1 */
l_int|11
comma
multiline_comment|/* Line 2 */
l_int|14
comma
multiline_comment|/* Line 3 */
l_int|15
multiline_comment|/* Line 4 */
)brace
suffix:semicolon
multiline_comment|/* Motorola Genesis2 MVME26XX, MVME 36XX */
multiline_comment|/* The final version for these boards should use the Raven PPC/PCI bridge &n;interrupt controller which is much sophisticated and allows more&n;devices on the PCI bus. */
DECL|variable|__prepdata
r_static
r_char
id|Genesis2_pci_IRQ_map
(braket
l_int|23
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - ECC memory controller/PCI bridge */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|0
comma
multiline_comment|/* Slot 2  - unused */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|0
comma
multiline_comment|/* Slot 4  - unused */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|0
comma
multiline_comment|/* Slot 6  - unused */
l_int|0
comma
multiline_comment|/* Slot 7  - unused */
l_int|0
comma
multiline_comment|/* Slot 8  - unused */
l_int|0
comma
multiline_comment|/* Slot 9  - unused */
l_int|0
comma
multiline_comment|/* Slot 10 - unused */
l_int|0
comma
multiline_comment|/* Slot 11 - ISA bridge */
l_int|3
comma
multiline_comment|/* Slot 12 - SCSI */
l_int|2
comma
multiline_comment|/* Slot 13 - Universe PCI/VME bridge (and 22..24) */
l_int|1
comma
multiline_comment|/* Slot 14 - Ethernet */
l_int|0
comma
multiline_comment|/* Slot 15 - Unused (graphics on 3600, would be 20 ?) */
l_int|4
comma
multiline_comment|/* Slot 16 - PMC slot, assume uses INTA */
l_int|0
comma
multiline_comment|/* Slot 17 */
l_int|0
comma
multiline_comment|/* Slot 18 */
l_int|0
comma
multiline_comment|/* Slot 19 */
l_int|0
comma
multiline_comment|/* Slot 20 */
l_int|0
comma
multiline_comment|/* Slot 21 */
l_int|0
comma
multiline_comment|/* Slot 22 */
)brace
suffix:semicolon
DECL|variable|__prepdata
r_static
r_char
id|Genesis2_pci_IRQ_routes
(braket
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Line 0 - Unused */
l_int|10
comma
multiline_comment|/* Line 1 - INTA */
l_int|11
comma
multiline_comment|/* Line 2 - INTB */
l_int|14
comma
multiline_comment|/* Line 3 - INTC */
l_int|15
multiline_comment|/* Line 4 - INTD */
)brace
suffix:semicolon
multiline_comment|/* Motorola Series-E */
DECL|variable|__prepdata
r_static
r_char
id|Comet_pci_IRQ_map
(braket
l_int|16
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - unused */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|0
comma
multiline_comment|/* Slot 2  - unused */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|0
comma
multiline_comment|/* Slot 4  - unused */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|0
comma
multiline_comment|/* Slot 6  - unused */
l_int|0
comma
multiline_comment|/* Slot 7  - unused */
l_int|0
comma
multiline_comment|/* Slot 8  - unused */
l_int|0
comma
multiline_comment|/* Slot 9  - unused */
l_int|0
comma
multiline_comment|/* Slot 10 - unused */
l_int|0
comma
multiline_comment|/* Slot 11 - unused */
l_int|3
comma
multiline_comment|/* Slot 12 - SCSI */
l_int|0
comma
multiline_comment|/* Slot 13 - unused */
l_int|1
comma
multiline_comment|/* Slot 14 - Ethernet */
l_int|0
comma
multiline_comment|/* Slot 15 - unused */
)brace
suffix:semicolon
DECL|variable|__prepdata
r_static
r_char
id|Comet_pci_IRQ_routes
(braket
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Line 0 - Unused */
l_int|10
comma
multiline_comment|/* Line 1 */
l_int|11
comma
multiline_comment|/* Line 2 */
l_int|14
comma
multiline_comment|/* Line 3 */
l_int|15
multiline_comment|/* Line 4 */
)brace
suffix:semicolon
multiline_comment|/*&n; * ibm 830 (and 850?).&n; * This is actually based on the Carolina motherboard&n; * -- Cort&n; */
DECL|variable|__prepdata
r_static
r_char
id|ibm8xx_pci_IRQ_map
(braket
l_int|23
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - unused */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|0
comma
multiline_comment|/* Slot 2  - unused */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|0
comma
multiline_comment|/* Slot 4  - unused */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|0
comma
multiline_comment|/* Slot 6  - unused */
l_int|0
comma
multiline_comment|/* Slot 7  - unused */
l_int|0
comma
multiline_comment|/* Slot 8  - unused */
l_int|0
comma
multiline_comment|/* Slot 9  - unused */
l_int|0
comma
multiline_comment|/* Slot 10 - unused */
l_int|0
comma
multiline_comment|/* Slot 11 - FireCoral */
l_int|4
comma
multiline_comment|/* Slot 12 - Ethernet  PCIINTD# */
l_int|2
comma
multiline_comment|/* Slot 13 - PCI Slot #2 */
l_int|2
comma
multiline_comment|/* Slot 14 - S3 Video PCIINTD# */
l_int|0
comma
multiline_comment|/* Slot 15 - onboard SCSI (INDI) [1] */
l_int|3
comma
multiline_comment|/* Slot 16 - NCR58C810 RS6000 Only PCIINTC# */
l_int|0
comma
multiline_comment|/* Slot 17 - unused */
l_int|2
comma
multiline_comment|/* Slot 18 - PCI Slot 2 PCIINTx# (See below) */
l_int|0
comma
multiline_comment|/* Slot 19 - unused */
l_int|0
comma
multiline_comment|/* Slot 20 - unused */
l_int|0
comma
multiline_comment|/* Slot 21 - unused */
l_int|2
comma
multiline_comment|/* Slot 22 - PCI slot 1 PCIINTx# (See below) */
)brace
suffix:semicolon
DECL|variable|__prepdata
r_static
r_char
id|ibm8xx_pci_IRQ_routes
(braket
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Line 0 - unused */
l_int|13
comma
multiline_comment|/* Line 1 */
l_int|10
comma
multiline_comment|/* Line 2 */
l_int|15
comma
multiline_comment|/* Line 3 */
l_int|15
comma
multiline_comment|/* Line 4 */
)brace
suffix:semicolon
multiline_comment|/*&n; * a 6015 ibm board&n; * -- Cort&n; */
DECL|variable|__prepdata
r_static
r_char
id|ibm6015_pci_IRQ_map
(braket
l_int|23
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Slot 0  - unused */
l_int|0
comma
multiline_comment|/* Slot 1  - unused */
l_int|0
comma
multiline_comment|/* Slot 2  - unused */
l_int|0
comma
multiline_comment|/* Slot 3  - unused */
l_int|0
comma
multiline_comment|/* Slot 4  - unused */
l_int|0
comma
multiline_comment|/* Slot 5  - unused */
l_int|0
comma
multiline_comment|/* Slot 6  - unused */
l_int|0
comma
multiline_comment|/* Slot 7  - unused */
l_int|0
comma
multiline_comment|/* Slot 8  - unused */
l_int|0
comma
multiline_comment|/* Slot 9  - unused */
l_int|0
comma
multiline_comment|/* Slot 10 - unused */
l_int|0
comma
multiline_comment|/* Slot 11 -  */
l_int|1
comma
multiline_comment|/* Slot 12 - SCSI */
l_int|2
comma
multiline_comment|/* Slot 13 -  */
l_int|2
comma
multiline_comment|/* Slot 14 -  */
l_int|1
comma
multiline_comment|/* Slot 15 -  */
l_int|1
comma
multiline_comment|/* Slot 16 -  */
l_int|0
comma
multiline_comment|/* Slot 17 -  */
l_int|2
comma
multiline_comment|/* Slot 18 -  */
l_int|0
comma
multiline_comment|/* Slot 19 -  */
l_int|0
comma
multiline_comment|/* Slot 20 -  */
l_int|0
comma
multiline_comment|/* Slot 21 -  */
l_int|2
comma
multiline_comment|/* Slot 22 -  */
)brace
suffix:semicolon
DECL|variable|__prepdata
r_static
r_char
id|ibm6015_pci_IRQ_routes
(braket
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Line 0 - unused */
l_int|13
comma
multiline_comment|/* Line 1 */
l_int|10
comma
multiline_comment|/* Line 2 */
l_int|15
comma
multiline_comment|/* Line 3 */
l_int|15
comma
multiline_comment|/* Line 4 */
)brace
suffix:semicolon
multiline_comment|/* IBM Nobis and 850 */
DECL|variable|__prepdata
r_static
r_char
id|Nobis_pci_IRQ_map
(braket
l_int|23
)braket
id|__prepdata
op_assign
initialization_block
suffix:semicolon
DECL|variable|__prepdata
r_static
r_char
id|Nobis_pci_IRQ_routes
(braket
)braket
id|__prepdata
op_assign
(brace
l_int|0
comma
multiline_comment|/* Line 0 - Unused */
l_int|13
comma
multiline_comment|/* Line 1 */
l_int|13
comma
multiline_comment|/* Line 2 */
l_int|13
comma
multiline_comment|/* Line 3 */
l_int|13
multiline_comment|/* Line 4 */
)brace
suffix:semicolon
multiline_comment|/* We have to turn on LEVEL mode for changed IRQ&squot;s */
multiline_comment|/* All PCI IRQ&squot;s need to be level mode, so this should be something&n; * other than hard-coded as well... IRQ&squot;s are individually mappable&n; * to either edge or level.&n; */
DECL|macro|CAROLINA_IRQ_EDGE_MASK_LO
mdefine_line|#define CAROLINA_IRQ_EDGE_MASK_LO   0x00  /* IRQ&squot;s 0-7  */
DECL|macro|CAROLINA_IRQ_EDGE_MASK_HI
mdefine_line|#define CAROLINA_IRQ_EDGE_MASK_HI   0xA4  /* IRQ&squot;s 8-15 [10,13,15] */
multiline_comment|/*&n; * 8259 edge/level control definitions&n; */
DECL|macro|ISA8259_M_ELCR
mdefine_line|#define ISA8259_M_ELCR 0x4d0
DECL|macro|ISA8259_S_ELCR
mdefine_line|#define ISA8259_S_ELCR 0x4d1
DECL|macro|ELCRS_INT15_LVL
mdefine_line|#define ELCRS_INT15_LVL         0x80
DECL|macro|ELCRS_INT14_LVL
mdefine_line|#define ELCRS_INT14_LVL         0x40
DECL|macro|ELCRS_INT12_LVL
mdefine_line|#define ELCRS_INT12_LVL         0x10
DECL|macro|ELCRS_INT11_LVL
mdefine_line|#define ELCRS_INT11_LVL         0x08
DECL|macro|ELCRS_INT10_LVL
mdefine_line|#define ELCRS_INT10_LVL         0x04
DECL|macro|ELCRS_INT9_LVL
mdefine_line|#define ELCRS_INT9_LVL          0x02
DECL|macro|ELCRS_INT8_LVL
mdefine_line|#define ELCRS_INT8_LVL          0x01
DECL|macro|ELCRM_INT7_LVL
mdefine_line|#define ELCRM_INT7_LVL          0x80
DECL|macro|ELCRM_INT5_LVL
mdefine_line|#define ELCRM_INT5_LVL          0x20
DECL|macro|CFGPTR
mdefine_line|#define CFGPTR(dev) (0x80800000 | (1&lt;&lt;(dev&gt;&gt;3)) | ((dev&amp;7)&lt;&lt;8) | offset)
DECL|macro|DEVNO
mdefine_line|#define DEVNO(dev)  (dev&gt;&gt;3)                                  
id|__prep
r_int
DECL|function|prep_pcibios_read_config_dword
id|prep_pcibios_read_config_dword
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
(brace
r_int
r_int
id|_val
suffix:semicolon
r_int
r_int
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bus
op_ne
l_int|0
)paren
op_logical_or
(paren
id|DEVNO
c_func
(paren
id|dev
)paren
OG
id|MAX_DEVNR
)paren
)paren
(brace
op_star
id|val
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
r_else
(brace
id|ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|CFGPTR
c_func
(paren
id|dev
)paren
suffix:semicolon
id|_val
op_assign
id|le32_to_cpu
c_func
(paren
op_star
id|ptr
)paren
suffix:semicolon
)brace
op_star
id|val
op_assign
id|_val
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
id|__prep
r_int
DECL|function|prep_pcibios_read_config_word
id|prep_pcibios_read_config_word
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
(brace
r_int
r_int
id|_val
suffix:semicolon
r_int
r_int
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bus
op_ne
l_int|0
)paren
op_logical_or
(paren
id|DEVNO
c_func
(paren
id|dev
)paren
OG
id|MAX_DEVNR
)paren
)paren
(brace
op_star
id|val
op_assign
l_int|0xFFFF
suffix:semicolon
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
r_else
(brace
id|ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|CFGPTR
c_func
(paren
id|dev
)paren
suffix:semicolon
id|_val
op_assign
id|le16_to_cpu
c_func
(paren
op_star
id|ptr
)paren
suffix:semicolon
)brace
op_star
id|val
op_assign
id|_val
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
id|__prep
r_int
DECL|function|prep_pcibios_read_config_byte
id|prep_pcibios_read_config_byte
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev
comma
r_int
r_char
id|offset
comma
r_int
r_char
op_star
id|val
)paren
(brace
r_int
r_char
id|_val
suffix:semicolon
r_int
r_char
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bus
op_ne
l_int|0
)paren
op_logical_or
(paren
id|DEVNO
c_func
(paren
id|dev
)paren
OG
id|MAX_DEVNR
)paren
)paren
(brace
op_star
id|val
op_assign
l_int|0xFF
suffix:semicolon
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
r_else
(brace
id|ptr
op_assign
(paren
r_int
r_char
op_star
)paren
id|CFGPTR
c_func
(paren
id|dev
)paren
suffix:semicolon
id|_val
op_assign
op_star
id|ptr
suffix:semicolon
)brace
op_star
id|val
op_assign
id|_val
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
id|__prep
r_int
DECL|function|prep_pcibios_write_config_dword
id|prep_pcibios_write_config_dword
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|_val
suffix:semicolon
r_int
r_int
op_star
id|ptr
suffix:semicolon
id|_val
op_assign
id|le32_to_cpu
c_func
(paren
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bus
op_ne
l_int|0
)paren
op_logical_or
(paren
id|DEVNO
c_func
(paren
id|dev
)paren
OG
id|MAX_DEVNR
)paren
)paren
(brace
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
r_else
(brace
id|ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|CFGPTR
c_func
(paren
id|dev
)paren
suffix:semicolon
op_star
id|ptr
op_assign
id|_val
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
id|__prep
r_int
DECL|function|prep_pcibios_write_config_word
id|prep_pcibios_write_config_word
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
(brace
r_int
r_int
id|_val
suffix:semicolon
r_int
r_int
op_star
id|ptr
suffix:semicolon
id|_val
op_assign
id|le16_to_cpu
c_func
(paren
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bus
op_ne
l_int|0
)paren
op_logical_or
(paren
id|DEVNO
c_func
(paren
id|dev
)paren
OG
id|MAX_DEVNR
)paren
)paren
(brace
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
r_else
(brace
id|ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|CFGPTR
c_func
(paren
id|dev
)paren
suffix:semicolon
op_star
id|ptr
op_assign
id|_val
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
id|__prep
r_int
DECL|function|prep_pcibios_write_config_byte
id|prep_pcibios_write_config_byte
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev
comma
r_int
r_char
id|offset
comma
r_int
r_char
id|val
)paren
(brace
r_int
r_char
id|_val
suffix:semicolon
r_int
r_char
op_star
id|ptr
suffix:semicolon
id|_val
op_assign
id|val
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bus
op_ne
l_int|0
)paren
op_logical_or
(paren
id|DEVNO
c_func
(paren
id|dev
)paren
OG
id|MAX_DEVNR
)paren
)paren
(brace
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
r_else
(brace
id|ptr
op_assign
(paren
r_int
r_char
op_star
)paren
id|CFGPTR
c_func
(paren
id|dev
)paren
suffix:semicolon
op_star
id|ptr
op_assign
id|_val
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
r_int
id|prep_route_pci_interrupts
c_func
(paren
r_void
)paren
)paren
(brace
r_int
r_char
op_star
id|ibc_pirq
op_assign
(paren
r_int
r_char
op_star
)paren
l_int|0x80800860
suffix:semicolon
r_int
r_char
op_star
id|ibc_pcicon
op_assign
(paren
r_int
r_char
op_star
)paren
l_int|0x80800840
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|_prep_type
op_eq
id|_PREP_Motorola
)paren
(brace
r_int
r_int
id|irq_mode
suffix:semicolon
r_switch
c_cond
(paren
id|inb
c_func
(paren
l_int|0x800
)paren
op_amp
l_int|0xF0
)paren
(brace
r_case
l_int|0x10
suffix:colon
multiline_comment|/* MVME16xx */
id|Motherboard_map_name
op_assign
l_string|&quot;Genesis&quot;
suffix:semicolon
id|Motherboard_map
op_assign
id|Genesis_pci_IRQ_map
suffix:semicolon
id|Motherboard_routes
op_assign
id|Genesis_pci_IRQ_routes
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x20
suffix:colon
multiline_comment|/* Series E */
id|Motherboard_map_name
op_assign
l_string|&quot;Powerstack (Series E)&quot;
suffix:semicolon
id|Motherboard_map
op_assign
id|Comet_pci_IRQ_map
suffix:semicolon
id|Motherboard_routes
op_assign
id|Comet_pci_IRQ_routes
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x50
suffix:colon
multiline_comment|/* PowerStackII Pro3000 */
id|Motherboard_map_name
op_assign
l_string|&quot;Omaha (PowerStack II Pro3000)&quot;
suffix:semicolon
id|Motherboard_map
op_assign
id|Omaha_pci_IRQ_map
suffix:semicolon
id|Motherboard_routes
op_assign
id|Omaha_pci_IRQ_routes
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x60
suffix:colon
multiline_comment|/* PowerStackII Pro4000 */
id|Motherboard_map_name
op_assign
l_string|&quot;Utah (Powerstack II Pro4000)&quot;
suffix:semicolon
id|Motherboard_map
op_assign
id|Utah_pci_IRQ_map
suffix:semicolon
id|Motherboard_routes
op_assign
id|Utah_pci_IRQ_routes
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xE0
suffix:colon
multiline_comment|/* MVME 26xx, 36xx, MTX ? */
id|Motherboard_map_name
op_assign
l_string|&quot;Genesis2&quot;
suffix:semicolon
id|Motherboard_map
op_assign
id|Genesis2_pci_IRQ_map
suffix:semicolon
id|Motherboard_routes
op_assign
id|Genesis2_pci_IRQ_routes
suffix:semicolon
multiline_comment|/* Return: different ibc_pcicon and&n;&t;&t;&t;   pirq already set up by firmware. */
r_return
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x40
suffix:colon
multiline_comment|/* PowerStack */
r_default
suffix:colon
multiline_comment|/* Can&squot;t hurt, can it? */
id|Motherboard_map_name
op_assign
l_string|&quot;Blackhawk (Powerstack)&quot;
suffix:semicolon
id|Motherboard_map
op_assign
id|Blackhawk_pci_IRQ_map
suffix:semicolon
id|Motherboard_routes
op_assign
id|Blackhawk_pci_IRQ_routes
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* AJF adjust level/edge control according to routes */
id|irq_mode
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_mode
op_or_assign
(paren
l_int|1
op_lshift
id|Motherboard_routes
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|outb
c_func
(paren
id|irq_mode
op_amp
l_int|0xff
comma
l_int|0x4d0
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|irq_mode
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
l_int|0x4d1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|_prep_type
op_eq
id|_PREP_IBM
)paren
(brace
r_int
r_char
id|pl_id
suffix:semicolon
multiline_comment|/*&n;&t;&t; * my carolina is 0xf0&n;&t;&t; * 6015 has 0xfc&n;&t;&t; * -- Cort&n;&t;&t; */
id|printk
c_func
(paren
l_string|&quot;IBM ID: %08x&bslash;n&quot;
comma
id|inb
c_func
(paren
l_int|0x0852
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|inb
c_func
(paren
l_int|0x0852
)paren
)paren
(brace
r_case
l_int|0xff
suffix:colon
id|Motherboard_map_name
op_assign
l_string|&quot;IBM 850/860 Portable&bslash;n&quot;
suffix:semicolon
id|Motherboard_map
op_assign
id|Nobis_pci_IRQ_map
suffix:semicolon
id|Motherboard_routes
op_assign
id|Nobis_pci_IRQ_routes
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xfc
suffix:colon
id|Motherboard_map_name
op_assign
l_string|&quot;IBM 6015&quot;
suffix:semicolon
id|Motherboard_map
op_assign
id|ibm6015_pci_IRQ_map
suffix:semicolon
id|Motherboard_routes
op_assign
id|ibm6015_pci_IRQ_routes
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|Motherboard_map_name
op_assign
l_string|&quot;IBM 8xx (Carolina)&quot;
suffix:semicolon
id|Motherboard_map
op_assign
id|ibm8xx_pci_IRQ_map
suffix:semicolon
id|Motherboard_routes
op_assign
id|ibm8xx_pci_IRQ_routes
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*printk(&quot;Changing IRQ mode&bslash;n&quot;);*/
id|pl_id
op_assign
id|inb
c_func
(paren
l_int|0x04d0
)paren
suffix:semicolon
multiline_comment|/*printk(&quot;Low mask is %#0x&bslash;n&quot;, pl_id);*/
id|outb
c_func
(paren
id|pl_id
op_or
id|CAROLINA_IRQ_EDGE_MASK_LO
comma
l_int|0x04d0
)paren
suffix:semicolon
id|pl_id
op_assign
id|inb
c_func
(paren
l_int|0x04d1
)paren
suffix:semicolon
multiline_comment|/*printk(&quot;Hi mask is  %#0x&bslash;n&quot;, pl_id);*/
id|outb
c_func
(paren
id|pl_id
op_or
id|CAROLINA_IRQ_EDGE_MASK_HI
comma
l_int|0x04d1
)paren
suffix:semicolon
id|pl_id
op_assign
id|inb
c_func
(paren
l_int|0x04d1
)paren
suffix:semicolon
multiline_comment|/*printk(&quot;Hi mask now %#0x&bslash;n&quot;, pl_id);*/
)brace
r_else
r_if
c_cond
(paren
id|_prep_type
op_eq
id|_PREP_Radstone
)paren
(brace
r_int
r_char
id|ucElcrM
comma
id|ucElcrS
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set up edge/level&n;&t;&t; */
r_switch
c_cond
(paren
id|ucSystemType
)paren
(brace
r_case
id|RS_SYS_TYPE_PPC1
suffix:colon
(brace
r_if
c_cond
(paren
id|ucBoardRevMaj
OL
l_int|5
)paren
(brace
id|ucElcrS
op_assign
id|ELCRS_INT15_LVL
suffix:semicolon
)brace
r_else
(brace
id|ucElcrS
op_assign
id|ELCRS_INT9_LVL
op_or
id|ELCRS_INT11_LVL
op_or
id|ELCRS_INT14_LVL
op_or
id|ELCRS_INT15_LVL
suffix:semicolon
)brace
id|ucElcrM
op_assign
id|ELCRM_INT5_LVL
op_or
id|ELCRM_INT7_LVL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|RS_SYS_TYPE_PPC1a
suffix:colon
(brace
id|ucElcrS
op_assign
id|ELCRS_INT9_LVL
op_or
id|ELCRS_INT11_LVL
op_or
id|ELCRS_INT14_LVL
op_or
id|ELCRS_INT15_LVL
suffix:semicolon
id|ucElcrM
op_assign
id|ELCRM_INT5_LVL
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|RS_SYS_TYPE_PPC2
suffix:colon
r_case
id|RS_SYS_TYPE_PPC2a
suffix:colon
r_case
id|RS_SYS_TYPE_PPC2ep
suffix:colon
r_case
id|RS_SYS_TYPE_PPC4
suffix:colon
r_case
id|RS_SYS_TYPE_PPC4a
suffix:colon
r_default
suffix:colon
(brace
)brace
(brace
id|ucElcrS
op_assign
id|ELCRS_INT9_LVL
op_or
id|ELCRS_INT10_LVL
op_or
id|ELCRS_INT11_LVL
op_or
id|ELCRS_INT14_LVL
op_or
id|ELCRS_INT15_LVL
suffix:semicolon
id|ucElcrM
op_assign
id|ELCRM_INT5_LVL
op_or
id|ELCRM_INT7_LVL
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Write edge/level selection&n;&t;&t; */
id|outb
c_func
(paren
id|ucElcrS
comma
id|ISA8259_S_ELCR
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ucElcrM
comma
id|ISA8259_M_ELCR
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Radstone boards have PCI interrupts all set up&n;&t;&t; * so leave well alone&n;&t;&t; */
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;No known machine pci routing!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Set up mapping from slots */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
op_le
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ibc_pirq
(braket
id|i
op_minus
l_int|1
)braket
op_assign
id|Motherboard_routes
(braket
id|i
)braket
suffix:semicolon
)brace
multiline_comment|/* Enable PCI interrupts */
op_star
id|ibc_pcicon
op_or_assign
l_int|0x20
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_static
r_inline
r_void
id|fixup_pci_interrupts
c_func
(paren
id|PnP_TAG_PACKET
op_star
id|pkt
)paren
)paren
(brace
DECL|macro|data
mdefine_line|#define data pkt-&gt;L4_Pack.L4_Data.L4_PPCPack.PPCData
id|u_int
id|bus
op_assign
id|data
(braket
l_int|16
)braket
suffix:semicolon
id|u_char
op_star
id|End
comma
op_star
id|p
suffix:semicolon
id|End
op_assign
id|data
op_plus
id|ld_le16
c_func
(paren
(paren
id|u_short
op_star
)paren
(paren
op_amp
id|pkt-&gt;L4_Pack.Count0
)paren
)paren
op_minus
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Interrupt mapping from %d to %d&bslash;n&quot;
comma
l_int|20
comma
id|End
op_minus
id|data
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|data
op_plus
l_int|20
suffix:semicolon
id|p
OL
id|End
suffix:semicolon
id|p
op_add_assign
l_int|12
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|pci_devices
suffix:semicolon
id|dev
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
)paren
(brace
r_int
id|code
comma
id|irq
suffix:semicolon
id|u_char
id|pin
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;bus-&gt;number
op_ne
id|bus
op_logical_or
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
op_ne
id|PCI_SLOT
c_func
(paren
id|p
(braket
l_int|1
)braket
)paren
)paren
r_continue
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_PIN
comma
op_amp
id|pin
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pin
)paren
(brace
r_continue
suffix:semicolon
)brace
id|code
op_assign
id|ld_le16
c_func
(paren
(paren
r_int
r_int
op_star
)paren
(paren
id|p
op_plus
l_int|4
op_plus
l_int|2
op_star
(paren
id|pin
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Set vector to 0 for unrouted PCI ints. This code&n;                         * is ugly but handles correctly the special case of&n;                         * interrupt 0 (8259 cascade) on OpenPIC&n;                         */
id|irq
op_assign
(paren
id|code
op_eq
l_int|0xffff
)paren
ques
c_cond
l_int|0
suffix:colon
id|code
op_amp
l_int|0x7fff
suffix:semicolon
r_if
c_cond
(paren
id|p
(braket
l_int|2
)braket
op_eq
l_int|2
)paren
(brace
multiline_comment|/* OpenPIC */
r_if
c_cond
(paren
id|irq
)paren
(brace
id|openpic_set_sense
c_func
(paren
id|irq
comma
id|code
OL
l_int|0x8000
)paren
suffix:semicolon
id|irq
op_assign
id|openpic_to_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_else
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|p
(braket
l_int|2
)braket
op_ne
l_int|1
)paren
(brace
multiline_comment|/* Not 8259 */
id|printk
c_func
(paren
l_string|&quot;Unknown or unsupported &quot;
l_string|&quot;interrupt controller&quot;
l_string|&quot;type %d.&bslash;n&quot;
comma
id|p
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
)brace
)brace
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_static
r_inline
r_void
id|fixup_bases
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
)paren
(brace
r_int
id|k
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|6
suffix:semicolon
id|k
op_increment
)paren
(brace
multiline_comment|/* FIXME: get the base address physical offset from &n;&t;&t;&t;the Raven instead of hard coding it.&n;&t;&t;&t;&t;-- Troy */
r_if
c_cond
(paren
id|dev-&gt;base_address
(braket
id|k
)braket
op_logical_and
(paren
id|dev-&gt;base_address
(braket
id|k
)braket
op_amp
id|PCI_BASE_ADDRESS_SPACE
)paren
op_eq
id|PCI_BASE_ADDRESS_SPACE_MEMORY
)paren
id|dev-&gt;base_address
(braket
id|k
)braket
op_add_assign
l_int|0xC0000000
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev-&gt;base_address
(braket
id|k
)braket
op_amp
(paren
id|PCI_BASE_ADDRESS_SPACE
op_or
id|PCI_BASE_ADDRESS_MEM_TYPE_MASK
)paren
)paren
op_eq
(paren
id|PCI_BASE_ADDRESS_SPACE_MEMORY
op_or
id|PCI_BASE_ADDRESS_MEM_TYPE_64
)paren
)paren
id|k
op_increment
suffix:semicolon
)brace
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|prep_pcibios_fixup
c_func
(paren
r_void
)paren
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_extern
r_int
r_char
op_star
id|Motherboard_map
suffix:semicolon
r_extern
r_int
r_char
op_star
id|Motherboard_routes
suffix:semicolon
r_int
r_char
id|i
suffix:semicolon
r_if
c_cond
(paren
id|_prep_type
op_eq
id|_PREP_Radstone
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Radstone boards require no PCI fixups&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|prep_route_pci_interrupts
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|pci_devices
suffix:semicolon
id|dev
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
)paren
(brace
multiline_comment|/*&n;                         * Use our old hard-coded kludge to figure out what&n;                         * irq this device uses.  This is necessary on things&n;                         * without residual data. -- Cort&n;                         */
r_int
r_char
id|d
op_assign
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|Motherboard_routes
(braket
id|Motherboard_map
(braket
id|d
)braket
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
l_int|5
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;base_address
(braket
id|i
)braket
OG
l_int|0x10000000
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Relocating PCI address %lx -&gt; %lx&bslash;n&quot;
comma
id|dev-&gt;base_address
(braket
id|i
)braket
comma
(paren
id|dev-&gt;base_address
(braket
id|i
)braket
op_amp
l_int|0x00FFFFFF
)paren
op_or
l_int|0x01000000
)paren
suffix:semicolon
id|dev-&gt;base_address
(braket
id|i
)braket
op_assign
(paren
id|dev-&gt;base_address
(braket
id|i
)braket
op_amp
l_int|0x00FFFFFF
)paren
op_or
l_int|0x01000000
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|PCI_BASE_ADDRESS_0
op_plus
(paren
id|i
op_star
l_int|0x4
)paren
comma
id|dev-&gt;base_address
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
macro_line|#if 0
multiline_comment|/*&n;                         * If we have residual data and if it knows about this&n;                         * device ask it what the irq is.&n;                         *  -- Cort&n;                         */
id|ppcd
op_assign
id|residual_find_device_id
c_func
(paren
op_complement
l_int|0L
comma
id|dev-&gt;device
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
)brace
DECL|variable|indirect
id|decl_config_access_method
c_func
(paren
id|indirect
)paren
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|prep_setup_pci_ptrs
c_func
(paren
r_void
)paren
)paren
(brace
id|PPC_DEVICE
op_star
id|hostbridge
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PReP architecture&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_prep_type
op_eq
id|_PREP_Radstone
)paren
(brace
id|pci_config_address
op_assign
(paren
r_int
op_star
)paren
l_int|0x80000cf8
suffix:semicolon
id|pci_config_data
op_assign
(paren
r_char
op_star
)paren
l_int|0x80000cfc
suffix:semicolon
id|set_config_access_method
c_func
(paren
id|indirect
)paren
suffix:semicolon
)brace
r_else
(brace
id|hostbridge
op_assign
id|residual_find_device
c_func
(paren
id|PROCESSORDEVICE
comma
l_int|NULL
comma
id|BridgeController
comma
id|PCIBridge
comma
op_minus
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hostbridge
op_logical_and
id|hostbridge-&gt;DeviceId.Interface
op_eq
id|PCIBridgeIndirect
)paren
(brace
id|PnP_TAG_PACKET
op_star
id|pkt
suffix:semicolon
id|set_config_access_method
c_func
(paren
id|indirect
)paren
suffix:semicolon
id|pkt
op_assign
id|PnP_find_large_vendor_packet
c_func
(paren
id|res-&gt;DevicePnPHeap
op_plus
id|hostbridge-&gt;AllocatedOffset
comma
l_int|3
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pkt
)paren
(brace
DECL|macro|p
mdefine_line|#define p pkt-&gt;L4_Pack.L4_Data.L4_PPCPack
id|pci_config_address
op_assign
(paren
r_int
op_star
)paren
id|ld_le32
c_func
(paren
(paren
r_int
op_star
)paren
id|p.PPCData
)paren
suffix:semicolon
id|pci_config_data
op_assign
(paren
r_int
r_char
op_star
)paren
id|ld_le32
c_func
(paren
(paren
r_int
op_star
)paren
(paren
id|p.PPCData
op_plus
l_int|8
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|pci_config_address
op_assign
(paren
r_int
op_star
)paren
l_int|0x80000cf8
suffix:semicolon
id|pci_config_data
op_assign
(paren
r_int
r_char
op_star
)paren
l_int|0x80000cfc
suffix:semicolon
)brace
)brace
r_else
(brace
id|set_config_access_method
c_func
(paren
id|prep
)paren
suffix:semicolon
)brace
)brace
id|ppc_md.pcibios_fixup
op_assign
id|prep_pcibios_fixup
suffix:semicolon
)brace
eof
