multiline_comment|/*&n; * ti113x.h 1.15 1999/09/03 16:43:35&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License. &n; *&n; * The initial developer of the original code is David A. Hinds&n; * &lt;dhinds@hyper.stanford.edu&gt;.  Portions created by David A. Hinds&n; * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU Public License version 2 (the &quot;GPL&quot;), in which&n; * case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use&n; * your version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n; */
macro_line|#ifndef _LINUX_TI113X_H
DECL|macro|_LINUX_TI113X_H
mdefine_line|#define _LINUX_TI113X_H
macro_line|#ifndef PCI_VENDOR_ID_TI
DECL|macro|PCI_VENDOR_ID_TI
mdefine_line|#define PCI_VENDOR_ID_TI&t;&t;0x104c
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TI_1130
DECL|macro|PCI_DEVICE_ID_TI_1130
mdefine_line|#define PCI_DEVICE_ID_TI_1130&t;&t;0xac12
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TI_1131
DECL|macro|PCI_DEVICE_ID_TI_1131
mdefine_line|#define PCI_DEVICE_ID_TI_1131&t;&t;0xac15
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TI_1031
DECL|macro|PCI_DEVICE_ID_TI_1031
mdefine_line|#define PCI_DEVICE_ID_TI_1031&t;&t;0xac13
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TI_1250A
DECL|macro|PCI_DEVICE_ID_TI_1250A
mdefine_line|#define PCI_DEVICE_ID_TI_1250A&t;&t;0xac16
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TI_1220
DECL|macro|PCI_DEVICE_ID_TI_1220
mdefine_line|#define PCI_DEVICE_ID_TI_1220&t;&t;0xac17
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TI_1221
DECL|macro|PCI_DEVICE_ID_TI_1221
mdefine_line|#define PCI_DEVICE_ID_TI_1221&t;&t;0xac19
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TI_1210
DECL|macro|PCI_DEVICE_ID_TI_1210
mdefine_line|#define PCI_DEVICE_ID_TI_1210&t;&t;0xac1a
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TI_1450
DECL|macro|PCI_DEVICE_ID_TI_1450
mdefine_line|#define PCI_DEVICE_ID_TI_1450&t;&t;0xac1b
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TI_1225
DECL|macro|PCI_DEVICE_ID_TI_1225
mdefine_line|#define PCI_DEVICE_ID_TI_1225&t;&t;0xac1c
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TI_1251A
DECL|macro|PCI_DEVICE_ID_TI_1251A
mdefine_line|#define PCI_DEVICE_ID_TI_1251A&t;&t;0xac1d
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TI_1211
DECL|macro|PCI_DEVICE_ID_TI_1211
mdefine_line|#define PCI_DEVICE_ID_TI_1211&t;&t;0xac1e
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TI_1251B
DECL|macro|PCI_DEVICE_ID_TI_1251B
mdefine_line|#define PCI_DEVICE_ID_TI_1251B&t;&t;0xac1f
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_TI_1420
DECL|macro|PCI_DEVICE_ID_TI_1420
mdefine_line|#define PCI_DEVICE_ID_TI_1420&t;&t;0xac51
macro_line|#endif
multiline_comment|/* Register definitions for TI 113X PCI-to-CardBus bridges */
multiline_comment|/* System Control Register */
DECL|macro|TI113X_SYSTEM_CONTROL
mdefine_line|#define TI113X_SYSTEM_CONTROL&t;&t;0x0080&t;/* 32 bit */
DECL|macro|TI113X_SCR_SMIROUTE
mdefine_line|#define  TI113X_SCR_SMIROUTE&t;&t;0x04000000
DECL|macro|TI113X_SCR_SMISTATUS
mdefine_line|#define  TI113X_SCR_SMISTATUS&t;&t;0x02000000
DECL|macro|TI113X_SCR_SMIENB
mdefine_line|#define  TI113X_SCR_SMIENB&t;&t;0x01000000
DECL|macro|TI113X_SCR_VCCPROT
mdefine_line|#define  TI113X_SCR_VCCPROT&t;&t;0x00200000
DECL|macro|TI113X_SCR_REDUCEZV
mdefine_line|#define  TI113X_SCR_REDUCEZV&t;&t;0x00100000
DECL|macro|TI113X_SCR_CDREQEN
mdefine_line|#define  TI113X_SCR_CDREQEN&t;&t;0x00080000
DECL|macro|TI113X_SCR_CDMACHAN
mdefine_line|#define  TI113X_SCR_CDMACHAN&t;&t;0x00070000
DECL|macro|TI113X_SCR_SOCACTIVE
mdefine_line|#define  TI113X_SCR_SOCACTIVE&t;&t;0x00002000
DECL|macro|TI113X_SCR_PWRSTREAM
mdefine_line|#define  TI113X_SCR_PWRSTREAM&t;&t;0x00000800
DECL|macro|TI113X_SCR_DELAYUP
mdefine_line|#define  TI113X_SCR_DELAYUP&t;&t;0x00000400
DECL|macro|TI113X_SCR_DELAYDOWN
mdefine_line|#define  TI113X_SCR_DELAYDOWN&t;&t;0x00000200
DECL|macro|TI113X_SCR_INTERROGATE
mdefine_line|#define  TI113X_SCR_INTERROGATE&t;&t;0x00000100
DECL|macro|TI113X_SCR_CLKRUN_SEL
mdefine_line|#define  TI113X_SCR_CLKRUN_SEL&t;&t;0x00000080
DECL|macro|TI113X_SCR_PWRSAVINGS
mdefine_line|#define  TI113X_SCR_PWRSAVINGS&t;&t;0x00000040
DECL|macro|TI113X_SCR_SUBSYSRW
mdefine_line|#define  TI113X_SCR_SUBSYSRW&t;&t;0x00000020
DECL|macro|TI113X_SCR_CB_DPAR
mdefine_line|#define  TI113X_SCR_CB_DPAR&t;&t;0x00000010
DECL|macro|TI113X_SCR_CDMA_EN
mdefine_line|#define  TI113X_SCR_CDMA_EN&t;&t;0x00000008
DECL|macro|TI113X_SCR_ASYNC_IRQ
mdefine_line|#define  TI113X_SCR_ASYNC_IRQ&t;&t;0x00000004
DECL|macro|TI113X_SCR_KEEPCLK
mdefine_line|#define  TI113X_SCR_KEEPCLK&t;&t;0x00000002
DECL|macro|TI113X_SCR_CLKRUN_ENA
mdefine_line|#define  TI113X_SCR_CLKRUN_ENA&t;&t;0x00000001  
DECL|macro|TI122X_SCR_SER_STEP
mdefine_line|#define  TI122X_SCR_SER_STEP&t;&t;0xc0000000
DECL|macro|TI122X_SCR_INTRTIE
mdefine_line|#define  TI122X_SCR_INTRTIE&t;&t;0x20000000
DECL|macro|TI122X_SCR_CBRSVD
mdefine_line|#define  TI122X_SCR_CBRSVD&t;&t;0x00400000
DECL|macro|TI122X_SCR_MRBURSTDN
mdefine_line|#define  TI122X_SCR_MRBURSTDN&t;&t;0x00008000
DECL|macro|TI122X_SCR_MRBURSTUP
mdefine_line|#define  TI122X_SCR_MRBURSTUP&t;&t;0x00004000
DECL|macro|TI122X_SCR_RIMUX
mdefine_line|#define  TI122X_SCR_RIMUX&t;&t;0x00000001
multiline_comment|/* Multimedia Control Register */
DECL|macro|TI1250_MULTIMEDIA_CTL
mdefine_line|#define TI1250_MULTIMEDIA_CTL&t;&t;0x0084&t;/* 8 bit */
DECL|macro|TI1250_MMC_ZVOUTEN
mdefine_line|#define  TI1250_MMC_ZVOUTEN&t;&t;0x80
DECL|macro|TI1250_MMC_PORTSEL
mdefine_line|#define  TI1250_MMC_PORTSEL&t;&t;0x40
DECL|macro|TI1250_MMC_ZVEN1
mdefine_line|#define  TI1250_MMC_ZVEN1&t;&t;0x02
DECL|macro|TI1250_MMC_ZVEN0
mdefine_line|#define  TI1250_MMC_ZVEN0&t;&t;0x01
DECL|macro|TI1250_GENERAL_STATUS
mdefine_line|#define TI1250_GENERAL_STATUS&t;&t;0x0085&t;/* 8 bit */
DECL|macro|TI1250_GPIO0_CONTROL
mdefine_line|#define TI1250_GPIO0_CONTROL&t;&t;0x0088&t;/* 8 bit */
DECL|macro|TI1250_GPIO1_CONTROL
mdefine_line|#define TI1250_GPIO1_CONTROL&t;&t;0x0089&t;/* 8 bit */
DECL|macro|TI1250_GPIO2_CONTROL
mdefine_line|#define TI1250_GPIO2_CONTROL&t;&t;0x008a&t;/* 8 bit */
DECL|macro|TI1250_GPIO3_CONTROL
mdefine_line|#define TI1250_GPIO3_CONTROL&t;&t;0x008b&t;/* 8 bit */
DECL|macro|TI122X_IRQMUX
mdefine_line|#define TI122X_IRQMUX&t;&t;&t;0x008c&t;/* 32 bit */
multiline_comment|/* Retry Status Register */
DECL|macro|TI113X_RETRY_STATUS
mdefine_line|#define TI113X_RETRY_STATUS&t;&t;0x0090&t;/* 8 bit */
DECL|macro|TI113X_RSR_PCIRETRY
mdefine_line|#define  TI113X_RSR_PCIRETRY&t;&t;0x80
DECL|macro|TI113X_RSR_CBRETRY
mdefine_line|#define  TI113X_RSR_CBRETRY&t;&t;0x40
DECL|macro|TI113X_RSR_TEXP_CBB
mdefine_line|#define  TI113X_RSR_TEXP_CBB&t;&t;0x20
DECL|macro|TI113X_RSR_MEXP_CBB
mdefine_line|#define  TI113X_RSR_MEXP_CBB&t;&t;0x10
DECL|macro|TI113X_RSR_TEXP_CBA
mdefine_line|#define  TI113X_RSR_TEXP_CBA&t;&t;0x08
DECL|macro|TI113X_RSR_MEXP_CBA
mdefine_line|#define  TI113X_RSR_MEXP_CBA&t;&t;0x04
DECL|macro|TI113X_RSR_TEXP_PCI
mdefine_line|#define  TI113X_RSR_TEXP_PCI&t;&t;0x02
DECL|macro|TI113X_RSR_MEXP_PCI
mdefine_line|#define  TI113X_RSR_MEXP_PCI&t;&t;0x01
multiline_comment|/* Card Control Register */
DECL|macro|TI113X_CARD_CONTROL
mdefine_line|#define TI113X_CARD_CONTROL&t;&t;0x0091&t;/* 8 bit */
DECL|macro|TI113X_CCR_RIENB
mdefine_line|#define  TI113X_CCR_RIENB&t;&t;0x80
DECL|macro|TI113X_CCR_ZVENABLE
mdefine_line|#define  TI113X_CCR_ZVENABLE&t;&t;0x40
DECL|macro|TI113X_CCR_PCI_IRQ_ENA
mdefine_line|#define  TI113X_CCR_PCI_IRQ_ENA&t;&t;0x20
DECL|macro|TI113X_CCR_PCI_IREQ
mdefine_line|#define  TI113X_CCR_PCI_IREQ&t;&t;0x10
DECL|macro|TI113X_CCR_PCI_CSC
mdefine_line|#define  TI113X_CCR_PCI_CSC&t;&t;0x08
DECL|macro|TI113X_CCR_SPKROUTEN
mdefine_line|#define  TI113X_CCR_SPKROUTEN&t;&t;0x02
DECL|macro|TI113X_CCR_IFG
mdefine_line|#define  TI113X_CCR_IFG&t;&t;&t;0x01
DECL|macro|TI1220_CCR_PORT_SEL
mdefine_line|#define  TI1220_CCR_PORT_SEL&t;&t;0x20
DECL|macro|TI122X_CCR_AUD2MUX
mdefine_line|#define  TI122X_CCR_AUD2MUX&t;&t;0x04
multiline_comment|/* Device Control Register */
DECL|macro|TI113X_DEVICE_CONTROL
mdefine_line|#define TI113X_DEVICE_CONTROL&t;&t;0x0092&t;/* 8 bit */
DECL|macro|TI113X_DCR_5V_FORCE
mdefine_line|#define  TI113X_DCR_5V_FORCE&t;&t;0x40
DECL|macro|TI113X_DCR_3V_FORCE
mdefine_line|#define  TI113X_DCR_3V_FORCE&t;&t;0x20
DECL|macro|TI113X_DCR_IMODE_MASK
mdefine_line|#define  TI113X_DCR_IMODE_MASK&t;&t;0x06
DECL|macro|TI113X_DCR_IMODE_ISA
mdefine_line|#define  TI113X_DCR_IMODE_ISA&t;&t;0x02
DECL|macro|TI113X_DCR_IMODE_SERIAL
mdefine_line|#define  TI113X_DCR_IMODE_SERIAL&t;0x04
DECL|macro|TI12XX_DCR_IMODE_PCI_ONLY
mdefine_line|#define  TI12XX_DCR_IMODE_PCI_ONLY&t;0x00
DECL|macro|TI12XX_DCR_IMODE_ALL_SERIAL
mdefine_line|#define  TI12XX_DCR_IMODE_ALL_SERIAL&t;0x06
multiline_comment|/* Buffer Control Register */
DECL|macro|TI113X_BUFFER_CONTROL
mdefine_line|#define TI113X_BUFFER_CONTROL&t;&t;0x0093&t;/* 8 bit */
DECL|macro|TI113X_BCR_CB_READ_DEPTH
mdefine_line|#define  TI113X_BCR_CB_READ_DEPTH&t;0x08
DECL|macro|TI113X_BCR_CB_WRITE_DEPTH
mdefine_line|#define  TI113X_BCR_CB_WRITE_DEPTH&t;0x04
DECL|macro|TI113X_BCR_PCI_READ_DEPTH
mdefine_line|#define  TI113X_BCR_PCI_READ_DEPTH&t;0x02
DECL|macro|TI113X_BCR_PCI_WRITE_DEPTH
mdefine_line|#define  TI113X_BCR_PCI_WRITE_DEPTH&t;0x01
multiline_comment|/* Diagnostic Register */
DECL|macro|TI1250_DIAGNOSTIC
mdefine_line|#define TI1250_DIAGNOSTIC&t;&t;0x0093&t;/* 8 bit */
DECL|macro|TI1250_DIAG_TRUE_VALUE
mdefine_line|#define  TI1250_DIAG_TRUE_VALUE&t;&t;0x80
DECL|macro|TI1250_DIAG_PCI_IREQ
mdefine_line|#define  TI1250_DIAG_PCI_IREQ&t;&t;0x40
DECL|macro|TI1250_DIAG_PCI_CSC
mdefine_line|#define  TI1250_DIAG_PCI_CSC&t;&t;0x20
DECL|macro|TI1250_DIAG_ASYNC_CSC
mdefine_line|#define  TI1250_DIAG_ASYNC_CSC&t;&t;0x01
multiline_comment|/* DMA Registers */
DECL|macro|TI113X_DMA_0
mdefine_line|#define TI113X_DMA_0&t;&t;&t;0x0094&t;/* 32 bit */
DECL|macro|TI113X_DMA_1
mdefine_line|#define TI113X_DMA_1&t;&t;&t;0x0098&t;/* 32 bit */
multiline_comment|/* ExCA IO offset registers */
DECL|macro|TI113X_IO_OFFSET
mdefine_line|#define TI113X_IO_OFFSET(map)&t;&t;(0x36+((map)&lt;&lt;1))
macro_line|#endif /* _LINUX_TI113X_H */
eof
