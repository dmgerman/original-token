multiline_comment|/*&n; * $Id: prep_pci.c,v 1.23 1998/10/21 10:52:24 cort Exp $&n; * PReP pci functions.&n; * Originally by Gary Thomas&n; * rewritten and updated by Cort Dougan (cort@cs.nmt.edu)&n; *&n; * The motherboard routes/maps will disappear shortly. -- Cort&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
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
l_int|14
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
id|dev
op_rshift_assign
l_int|3
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
id|dev
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
(paren
l_int|0x80800000
op_or
(paren
l_int|1
op_lshift
id|dev
)paren
op_or
id|offset
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
id|dev
op_rshift_assign
l_int|3
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
id|dev
OG
id|MAX_DEVNR
)paren
)paren
(brace
op_star
id|val
op_assign
(paren
r_int
r_int
)paren
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
(paren
l_int|0x80800000
op_or
(paren
l_int|1
op_lshift
id|dev
)paren
op_or
id|offset
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
r_volatile
r_int
r_char
op_star
id|ptr
suffix:semicolon
id|dev
op_rshift_assign
l_int|3
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
id|dev
OG
id|MAX_DEVNR
)paren
)paren
(brace
op_star
(paren
r_int
r_int
op_star
)paren
id|val
op_assign
(paren
r_int
r_int
)paren
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
r_char
op_star
)paren
(paren
l_int|0x80800000
op_or
(paren
l_int|1
op_lshift
id|dev
)paren
op_or
(paren
id|offset
op_xor
l_int|1
)paren
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
id|dev
op_rshift_assign
l_int|3
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
id|dev
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
(paren
l_int|0x80800000
op_or
(paren
l_int|1
op_lshift
id|dev
)paren
op_or
id|offset
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
id|dev
op_rshift_assign
l_int|3
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
id|dev
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
(paren
l_int|0x80800000
op_or
(paren
l_int|1
op_lshift
id|dev
)paren
op_or
id|offset
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
id|dev
op_rshift_assign
l_int|3
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
id|dev
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
(paren
l_int|0x80800000
op_or
(paren
l_int|1
op_lshift
id|dev
)paren
op_or
(paren
id|offset
op_xor
l_int|1
)paren
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
id|route_pci_interrupts
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
multiline_comment|/* MTX -- close enough?? to Genesis, so reuse it */
id|Motherboard_map_name
op_assign
l_string|&quot;Motorola MTX&quot;
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
eof
