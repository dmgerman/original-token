multiline_comment|/*&n; * SNI specific definitions&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1997 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_SNI_H 
DECL|macro|__ASM_MIPS_SNI_H
mdefine_line|#define __ASM_MIPS_SNI_H 
DECL|macro|SNI_PORT_BASE
mdefine_line|#define SNI_PORT_BASE&t;0xb4000000
multiline_comment|/*&n; * ASIC PCI registers for little endian configuration.&n; */
macro_line|#ifndef __MIPSEL__
macro_line|#error &quot;Fix me for big endian&quot;
macro_line|#endif
DECL|macro|PCIMT_UCONF
mdefine_line|#define PCIMT_UCONF&t;&t;0xbfff0000
DECL|macro|PCIMT_IOADTIMEOUT2
mdefine_line|#define PCIMT_IOADTIMEOUT2&t;0xbfff0008
DECL|macro|PCIMT_IOMEMCONF
mdefine_line|#define PCIMT_IOMEMCONF&t;&t;0xbfff0010
DECL|macro|PCIMT_IOMMU
mdefine_line|#define PCIMT_IOMMU&t;&t;0xbfff0018
DECL|macro|PCIMT_IOADTIMEOUT1
mdefine_line|#define PCIMT_IOADTIMEOUT1&t;0xbfff0020
DECL|macro|PCIMT_DMAACCESS
mdefine_line|#define PCIMT_DMAACCESS&t;&t;0xbfff0028
DECL|macro|PCIMT_DMAHIT
mdefine_line|#define PCIMT_DMAHIT&t;&t;0xbfff0030
DECL|macro|PCIMT_ERRSTATUS
mdefine_line|#define PCIMT_ERRSTATUS&t;&t;0xbfff0038
DECL|macro|PCIMT_ERRADDR
mdefine_line|#define PCIMT_ERRADDR&t;&t;0xbfff0040
DECL|macro|PCIMT_SYNDROME
mdefine_line|#define PCIMT_SYNDROME&t;&t;0xbfff0048
DECL|macro|PCIMT_ITPEND
mdefine_line|#define PCIMT_ITPEND&t;&t;0xbfff0050
DECL|macro|PCIMT_IRQSEL
mdefine_line|#define PCIMT_IRQSEL&t;&t;0xbfff0058
DECL|macro|PCIMT_TESTMEM
mdefine_line|#define PCIMT_TESTMEM&t;&t;0xbfff0060
DECL|macro|PCIMT_ECCREG
mdefine_line|#define PCIMT_ECCREG&t;&t;0xbfff0068
DECL|macro|PCIMT_CONFIG_ADDRESS
mdefine_line|#define PCIMT_CONFIG_ADDRESS&t;0xbfff0070
DECL|macro|PCIMT_ASIC_ID
mdefine_line|#define PCIMT_ASIC_ID&t;&t;0xbfff0078&t;/* read */
DECL|macro|PCIMT_SOFT_RESET
mdefine_line|#define PCIMT_SOFT_RESET&t;0xbfff0078&t;/* write */
DECL|macro|PCIMT_PIA_OE
mdefine_line|#define PCIMT_PIA_OE&t;&t;0xbfff0080
DECL|macro|PCIMT_PIA_DATAOUT
mdefine_line|#define PCIMT_PIA_DATAOUT&t;0xbfff0088
DECL|macro|PCIMT_PIA_DATAIN
mdefine_line|#define PCIMT_PIA_DATAIN&t;0xbfff0090
DECL|macro|PCIMT_CACHECONF
mdefine_line|#define PCIMT_CACHECONF&t;&t;0xbfff0098
DECL|macro|PCIMT_INVSPACE
mdefine_line|#define PCIMT_INVSPACE&t;&t;0xbfff00a0
DECL|macro|PCIMT_PCI_CONF
mdefine_line|#define PCIMT_PCI_CONF&t;&t;0xbfff0100
multiline_comment|/*&n; * Data port for the PCI bus.&n; */
DECL|macro|PCIMT_CONFIG_DATA
mdefine_line|#define PCIMT_CONFIG_DATA&t;0xb4000cfc
multiline_comment|/*&n; * Board specific registers&n; */
DECL|macro|PCIMT_CSMSR
mdefine_line|#define PCIMT_CSMSR&t;&t;0xbfd00000
DECL|macro|PCIMT_CSSWITCH
mdefine_line|#define PCIMT_CSSWITCH&t;&t;0xbfd10000
DECL|macro|PCIMT_CSITPEND
mdefine_line|#define PCIMT_CSITPEND&t;&t;0xbfd20000
DECL|macro|PCIMT_AUTO_PO_EN
mdefine_line|#define PCIMT_AUTO_PO_EN&t;0xbfd30000
DECL|macro|PCIMT_CLR_TEMP
mdefine_line|#define PCIMT_CLR_TEMP&t;&t;0xbfd40000
DECL|macro|PCIMT_AUTO_PO_DIS
mdefine_line|#define PCIMT_AUTO_PO_DIS&t;0xbfd50000
DECL|macro|PCIMT_EXMSR
mdefine_line|#define PCIMT_EXMSR&t;&t;0xbfd60000
DECL|macro|PCIMT_UNUSED1
mdefine_line|#define PCIMT_UNUSED1&t;&t;0xbfd70000
DECL|macro|PCIMT_CSWCSM
mdefine_line|#define PCIMT_CSWCSM&t;&t;0xbfd80000
DECL|macro|PCIMT_UNUSED2
mdefine_line|#define PCIMT_UNUSED2&t;&t;0xbfd90000
DECL|macro|PCIMT_CSLED
mdefine_line|#define PCIMT_CSLED&t;&t;0xbfda0000
DECL|macro|PCIMT_CSMAPISA
mdefine_line|#define PCIMT_CSMAPISA&t;&t;0xbfdb0000
DECL|macro|PCIMT_CSRSTBP
mdefine_line|#define PCIMT_CSRSTBP&t;&t;0xbfdc0000
DECL|macro|PCIMT_CLRPOFF
mdefine_line|#define PCIMT_CLRPOFF&t;&t;0xbfdd0000
DECL|macro|PCIMT_CSTIMER
mdefine_line|#define PCIMT_CSTIMER&t;&t;0xbfde0000
DECL|macro|PCIMT_PWDN
mdefine_line|#define PCIMT_PWDN&t;&t;0xbfdf0000
multiline_comment|/*&n; * Interrupt 0-16 are reserved for PCI and EISA interrupts.  The&n; * interrupts from 16 are assigned to the other interrupts generated&n; * by the PCI chipset.&n; */
DECL|macro|PCIMT_IRQ_ETHERNET
mdefine_line|#define PCIMT_IRQ_ETHERNET&t;16
DECL|macro|PCIMT_IRQ_TEMPERATURE
mdefine_line|#define PCIMT_IRQ_TEMPERATURE&t;17
DECL|macro|PCIMT_IRQ_EISA_NMI
mdefine_line|#define PCIMT_IRQ_EISA_NMI&t;18
DECL|macro|PCIMT_IRQ_POWER_OFF
mdefine_line|#define PCIMT_IRQ_POWER_OFF&t;19
DECL|macro|PCIMT_IRQ_BUTTON
mdefine_line|#define PCIMT_IRQ_BUTTON&t;20
DECL|macro|PCIMT_IRQ_INTA
mdefine_line|#define PCIMT_IRQ_INTA&t;&t;21
DECL|macro|PCIMT_IRQ_INTB
mdefine_line|#define PCIMT_IRQ_INTB&t;&t;22
DECL|macro|PCIMT_IRQ_INTC
mdefine_line|#define PCIMT_IRQ_INTC&t;&t;23
DECL|macro|PCIMT_IRQ_INTD
mdefine_line|#define PCIMT_IRQ_INTD&t;&t;24
DECL|macro|PCIMT_IRQ_SCSI
mdefine_line|#define PCIMT_IRQ_SCSI&t;&t;25
multiline_comment|/*&n; * Base address for the mapped 16mb EISA bus segment.&n; */
DECL|macro|PCIMT_EISA_BASE
mdefine_line|#define PCIMT_EISA_BASE&t;&t;0xb0000000
macro_line|#endif /* __ASM_MIPS_SNI_H */
eof