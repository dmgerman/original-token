multiline_comment|/*&n;    Copyright 1994 Digital Equipment Corporation.&n;&n;    This software may be used and distributed according to  the terms of the&n;    GNU Public License, incorporated herein by reference.&n;&n;    The author may    be  reached as davies@wanton.lkg.dec.com  or   Digital&n;    Equipment Corporation, 550 King Street, Littleton MA 01460.&n;&n;    =========================================================================&n;*/
multiline_comment|/*&n;** DC21040 CSR&lt;1..15&gt; Register Address Map&n;*/
DECL|macro|DE4X5_BMR
mdefine_line|#define DE4X5_BMR    iobase+(0x000 &lt;&lt; lp-&gt;bus)  /* Bus Mode Register */
DECL|macro|DE4X5_TPD
mdefine_line|#define DE4X5_TPD    iobase+(0x008 &lt;&lt; lp-&gt;bus)  /* Transmit Poll Demand Reg */
DECL|macro|DE4X5_RPD
mdefine_line|#define DE4X5_RPD    iobase+(0x010 &lt;&lt; lp-&gt;bus)  /* Receive Poll Demand Reg */
DECL|macro|DE4X5_RRBA
mdefine_line|#define DE4X5_RRBA   iobase+(0x018 &lt;&lt; lp-&gt;bus)  /* RX Ring Base Address Reg */
DECL|macro|DE4X5_TRBA
mdefine_line|#define DE4X5_TRBA   iobase+(0x020 &lt;&lt; lp-&gt;bus)  /* TX Ring Base Address Reg */
DECL|macro|DE4X5_STS
mdefine_line|#define DE4X5_STS    iobase+(0x028 &lt;&lt; lp-&gt;bus)  /* Status Register */
DECL|macro|DE4X5_OMR
mdefine_line|#define DE4X5_OMR    iobase+(0x030 &lt;&lt; lp-&gt;bus)  /* Operation Mode Register */
DECL|macro|DE4X5_IMR
mdefine_line|#define DE4X5_IMR    iobase+(0x038 &lt;&lt; lp-&gt;bus)  /* Interrupt Mask Register */
DECL|macro|DE4X5_MFC
mdefine_line|#define DE4X5_MFC    iobase+(0x040 &lt;&lt; lp-&gt;bus)  /* Missed Frame Counter */
DECL|macro|DE4X5_APROM
mdefine_line|#define DE4X5_APROM  iobase+(0x048 &lt;&lt; lp-&gt;bus)  /* Ethernet Address PROM */
DECL|macro|DE4X5_BROM
mdefine_line|#define DE4X5_BROM   iobase+(0x048 &lt;&lt; lp-&gt;bus)  /* Boot ROM Register */
DECL|macro|DE4X5_SROM
mdefine_line|#define DE4X5_SROM   iobase+(0x048 &lt;&lt; lp-&gt;bus)  /* Serial ROM Register */
DECL|macro|DE4X5_MII
mdefine_line|#define DE4X5_MII    iobase+(0x048 &lt;&lt; lp-&gt;bus)  /* MII Interface Register */
DECL|macro|DE4X5_DDR
mdefine_line|#define DE4X5_DDR    iobase+(0x050 &lt;&lt; lp-&gt;bus)  /* Data Diagnostic Register */
DECL|macro|DE4X5_FDR
mdefine_line|#define DE4X5_FDR    iobase+(0x058 &lt;&lt; lp-&gt;bus)  /* Full Duplex Register */
DECL|macro|DE4X5_GPT
mdefine_line|#define DE4X5_GPT    iobase+(0x058 &lt;&lt; lp-&gt;bus)  /* General Purpose Timer Reg.*/
DECL|macro|DE4X5_GEP
mdefine_line|#define DE4X5_GEP    iobase+(0x060 &lt;&lt; lp-&gt;bus)  /* General Purpose Register */
DECL|macro|DE4X5_SISR
mdefine_line|#define DE4X5_SISR   iobase+(0x060 &lt;&lt; lp-&gt;bus)  /* SIA Status Register */
DECL|macro|DE4X5_SICR
mdefine_line|#define DE4X5_SICR   iobase+(0x068 &lt;&lt; lp-&gt;bus)  /* SIA Connectivity Register */
DECL|macro|DE4X5_STRR
mdefine_line|#define DE4X5_STRR   iobase+(0x070 &lt;&lt; lp-&gt;bus)  /* SIA TX/RX Register */
DECL|macro|DE4X5_SIGR
mdefine_line|#define DE4X5_SIGR   iobase+(0x078 &lt;&lt; lp-&gt;bus)  /* SIA General Register */
multiline_comment|/*&n;** EISA Register Address Map&n;*/
DECL|macro|EISA_ID
mdefine_line|#define EISA_ID      iobase+0x0c80   /* EISA ID Registers */ 
DECL|macro|EISA_ID0
mdefine_line|#define EISA_ID0     iobase+0x0c80   /* EISA ID Register 0 */ 
DECL|macro|EISA_ID1
mdefine_line|#define EISA_ID1     iobase+0x0c81   /* EISA ID Register 1 */ 
DECL|macro|EISA_ID2
mdefine_line|#define EISA_ID2     iobase+0x0c82   /* EISA ID Register 2 */ 
DECL|macro|EISA_ID3
mdefine_line|#define EISA_ID3     iobase+0x0c83   /* EISA ID Register 3 */ 
DECL|macro|EISA_CR
mdefine_line|#define EISA_CR      iobase+0x0c84   /* EISA Control Register */
DECL|macro|EISA_REG0
mdefine_line|#define EISA_REG0    iobase+0x0c88   /* EISA Configuration Register 0 */
DECL|macro|EISA_REG1
mdefine_line|#define EISA_REG1    iobase+0x0c89   /* EISA Configuration Register 1 */
DECL|macro|EISA_REG2
mdefine_line|#define EISA_REG2    iobase+0x0c8a   /* EISA Configuration Register 2 */
DECL|macro|EISA_REG3
mdefine_line|#define EISA_REG3    iobase+0x0c8f   /* EISA Configuration Register 3 */
DECL|macro|EISA_APROM
mdefine_line|#define EISA_APROM   iobase+0x0c90   /* Ethernet Address PROM */
multiline_comment|/*&n;** PCI/EISA Configuration Registers Address Map&n;*/
DECL|macro|PCI_CFID
mdefine_line|#define PCI_CFID     iobase+0x0008   /* PCI Configuration ID Register */
DECL|macro|PCI_CFCS
mdefine_line|#define PCI_CFCS     iobase+0x000c   /* PCI Command/Status Register */
DECL|macro|PCI_CFRV
mdefine_line|#define PCI_CFRV     iobase+0x0018   /* PCI Revision Register */
DECL|macro|PCI_CFLT
mdefine_line|#define PCI_CFLT     iobase+0x001c   /* PCI Latency Timer Register */
DECL|macro|PCI_CBIO
mdefine_line|#define PCI_CBIO     iobase+0x0028   /* PCI Base I/O Register */
DECL|macro|PCI_CBMA
mdefine_line|#define PCI_CBMA     iobase+0x002c   /* PCI Base Memory Address Register */
DECL|macro|PCI_CBER
mdefine_line|#define PCI_CBER     iobase+0x0030   /* PCI Expansion ROM Base Address Reg. */
DECL|macro|PCI_CFIT
mdefine_line|#define PCI_CFIT     iobase+0x003c   /* PCI Configuration Interrupt Register */
DECL|macro|PCI_CFDA
mdefine_line|#define PCI_CFDA     iobase+0x0040   /* PCI Driver Area Register */
multiline_comment|/*&n;** EISA Configuration Register 0 bit definitions&n;*/
DECL|macro|ER0_BSW
mdefine_line|#define ER0_BSW       0x80           /* EISA Bus Slave Width, 1: 32 bits */
DECL|macro|ER0_BMW
mdefine_line|#define ER0_BMW       0x40           /* EISA Bus Master Width, 1: 32 bits */
DECL|macro|ER0_EPT
mdefine_line|#define ER0_EPT       0x20           /* EISA PREEMPT Time, 0: 23 BCLKs */
DECL|macro|ER0_ISTS
mdefine_line|#define ER0_ISTS      0x10           /* Interrupt Status (X) */
DECL|macro|ER0_LI
mdefine_line|#define ER0_LI        0x08           /* Latch Interrupts */
DECL|macro|ER0_INTL
mdefine_line|#define ER0_INTL      0x06           /* INTerrupt Level */
DECL|macro|ER0_INTT
mdefine_line|#define ER0_INTT      0x01           /* INTerrupt Type, 0: Level, 1: Edge */
multiline_comment|/*&n;** EISA Configuration Register 1 bit definitions&n;*/
DECL|macro|ER1_IAM
mdefine_line|#define ER1_IAM       0xe0           /* ISA Address Mode */
DECL|macro|ER1_IAE
mdefine_line|#define ER1_IAE       0x10           /* ISA Addressing Enable */
DECL|macro|ER1_UPIN
mdefine_line|#define ER1_UPIN      0x0f           /* User Pins */
multiline_comment|/*&n;** EISA Configuration Register 2 bit definitions&n;*/
DECL|macro|ER2_BRS
mdefine_line|#define ER2_BRS       0xc0           /* Boot ROM Size */
DECL|macro|ER2_BRA
mdefine_line|#define ER2_BRA       0x3c           /* Boot ROM Address &lt;16:13&gt; */
multiline_comment|/*&n;** EISA Configuration Register 3 bit definitions&n;*/
DECL|macro|ER3_BWE
mdefine_line|#define ER3_BWE       0x40           /* Burst Write Enable */
DECL|macro|ER3_BRE
mdefine_line|#define ER3_BRE       0x04           /* Burst Read Enable */
DECL|macro|ER3_LSR
mdefine_line|#define ER3_LSR       0x02           /* Local Software Reset */
multiline_comment|/*&n;** PCI Configuration ID Register (PCI_CFID)&n;*/
DECL|macro|CFID_DID
mdefine_line|#define CFID_DID    0xff00           /* Device ID */
DECL|macro|CFID_VID
mdefine_line|#define CFID_VID    0x00ff           /* Vendor ID */
DECL|macro|DC21040_DID
mdefine_line|#define DC21040_DID 0x0002           /* Unique Device ID # */
DECL|macro|DC21040_VID
mdefine_line|#define DC21040_VID 0x1011           /* DC21040 Manufacturer */
DECL|macro|DC21041_DID
mdefine_line|#define DC21041_DID 0x0014           /* Unique Device ID # */
DECL|macro|DC21041_VID
mdefine_line|#define DC21041_VID 0x1011           /* DC21041 Manufacturer */
DECL|macro|DC21140_DID
mdefine_line|#define DC21140_DID 0x0009           /* Unique Device ID # */
DECL|macro|DC21140_VID
mdefine_line|#define DC21140_VID 0x1011           /* DC21140 Manufacturer */
multiline_comment|/*&n;** Chipset defines&n;*/
DECL|macro|DC21040
mdefine_line|#define DC21040     DC21040_DID
DECL|macro|DC21041
mdefine_line|#define DC21041     DC21041_DID
DECL|macro|DC21140
mdefine_line|#define DC21140     DC21140_DID
DECL|macro|is_DC21040
mdefine_line|#define is_DC21040 ((vendor == DC21040_VID) &amp;&amp; (device == DC21040_DID))
DECL|macro|is_DC21041
mdefine_line|#define is_DC21041 ((vendor == DC21041_VID) &amp;&amp; (device == DC21041_DID))
DECL|macro|is_DC21140
mdefine_line|#define is_DC21140 ((vendor == DC21140_VID) &amp;&amp; (device == DC21140_DID))
multiline_comment|/*&n;** PCI Configuration Command/Status Register (PCI_CFCS)&n;*/
DECL|macro|CFCS_DPE
mdefine_line|#define CFCS_DPE    0x80000000       /* Detected Parity Error (S) */
DECL|macro|CFCS_SSE
mdefine_line|#define CFCS_SSE    0x40000000       /* Signal System Error   (S) */
DECL|macro|CFCS_RMA
mdefine_line|#define CFCS_RMA    0x20000000       /* Receive Master Abort  (S) */
DECL|macro|CFCS_RTA
mdefine_line|#define CFCS_RTA    0x10000000       /* Receive Target Abort  (S) */
DECL|macro|CFCS_DST
mdefine_line|#define CFCS_DST    0x06000000       /* DEVSEL Timing         (S) */
DECL|macro|CFCS_DPR
mdefine_line|#define CFCS_DPR    0x01000000       /* Data Parity Report    (S) */
DECL|macro|CFCS_FBB
mdefine_line|#define CFCS_FBB    0x00800000       /* Fast Back-To-Back     (S) */
DECL|macro|CFCS_SLE
mdefine_line|#define CFCS_SLE    0x00000100       /* System Error Enable   (C) */
DECL|macro|CFCS_PER
mdefine_line|#define CFCS_PER    0x00000040       /* Parity Error Response (C) */
DECL|macro|CFCS_MO
mdefine_line|#define CFCS_MO     0x00000004       /* Master Operation      (C) */
DECL|macro|CFCS_MSA
mdefine_line|#define CFCS_MSA    0x00000002       /* Memory Space Access   (C) */
DECL|macro|CFCS_IOSA
mdefine_line|#define CFCS_IOSA   0x00000001       /* I/O Space Access      (C) */
multiline_comment|/*&n;** PCI Configuration Revision Register (PCI_CFRV)&n;*/
DECL|macro|CFRV_BC
mdefine_line|#define CFRV_BC     0xff000000       /* Base Class */
DECL|macro|CFRV_SC
mdefine_line|#define CFRV_SC     0x00ff0000       /* Subclass */
DECL|macro|CFRV_SN
mdefine_line|#define CFRV_SN     0x000000f0       /* Step Number */
DECL|macro|CFRV_RN
mdefine_line|#define CFRV_RN     0x0000000f       /* Revision Number */
DECL|macro|BASE_CLASS
mdefine_line|#define BASE_CLASS  0x02000000       /* Indicates Network Controller */
DECL|macro|SUB_CLASS
mdefine_line|#define SUB_CLASS   0x00000000       /* Indicates Ethernet Controller */
DECL|macro|STEP_NUMBER
mdefine_line|#define STEP_NUMBER 0x00000020       /* Increments for future chips */
DECL|macro|REV_NUMBER
mdefine_line|#define REV_NUMBER  0x00000003       /* 0x00, 0x01, 0x02, 0x03: Rev in Step */
DECL|macro|CFRV_MASK
mdefine_line|#define CFRV_MASK   0xffff0000       /* Register mask */
multiline_comment|/*&n;** PCI Configuration Latency Timer Register (PCI_CFLT)&n;*/
DECL|macro|CFLT_BC
mdefine_line|#define CFLT_BC     0x0000ff00       /* Latency Timer bits */
multiline_comment|/*&n;** PCI Configuration Base I/O Address Register (PCI_CBIO)&n;*/
DECL|macro|CBIO_MASK
mdefine_line|#define CBIO_MASK   0xffffff80       /* Base I/O Address Mask */
DECL|macro|CBIO_IOSI
mdefine_line|#define CBIO_IOSI   0x00000001       /* I/O Space Indicator (RO, value is 1) */
multiline_comment|/*&n;** PCI Configuration Expansion ROM Base Address Register (PCI_CBER)&n;*/
DECL|macro|CBER_MASK
mdefine_line|#define CBER_MASK   0xfffffc00       /* Expansion ROM Base Address Mask */
DECL|macro|CBER_ROME
mdefine_line|#define CBER_ROME   0x00000001       /* ROM Enable */
multiline_comment|/*&n;** PCI Configuration Driver Area Register (PCI_CFDA)&n;*/
DECL|macro|CFDA_PSM
mdefine_line|#define CFDA_PSM    0x80000000       /* Power Saving Mode */
multiline_comment|/*&n;** DC21040 Bus Mode Register (DE4X5_BMR)&n;*/
DECL|macro|BMR_DBO
mdefine_line|#define BMR_DBO    0x00100000       /* Descriptor Byte Ordering (Endian) */
DECL|macro|BMR_TAP
mdefine_line|#define BMR_TAP    0x000e0000       /* Transmit Automatic Polling */
DECL|macro|BMR_DAS
mdefine_line|#define BMR_DAS    0x00010000       /* Diagnostic Address Space */
DECL|macro|BMR_CAL
mdefine_line|#define BMR_CAL    0x0000c000       /* Cache Alignment */
DECL|macro|BMR_PBL
mdefine_line|#define BMR_PBL    0x00003f00       /* Programmable Burst Length */
DECL|macro|BMR_BLE
mdefine_line|#define BMR_BLE    0x00000080       /* Big/Little Endian */
DECL|macro|BMR_DSL
mdefine_line|#define BMR_DSL    0x0000007c       /* Descriptor Skip Length */
DECL|macro|BMR_BAR
mdefine_line|#define BMR_BAR    0x00000002       /* Bus ARbitration */
DECL|macro|BMR_SWR
mdefine_line|#define BMR_SWR    0x00000001       /* Software Reset */
DECL|macro|TAP_NOPOLL
mdefine_line|#define TAP_NOPOLL 0x00000000       /* No automatic polling */
DECL|macro|TAP_200US
mdefine_line|#define TAP_200US  0x00020000       /* TX automatic polling every 200us */
DECL|macro|TAP_800US
mdefine_line|#define TAP_800US  0x00040000       /* TX automatic polling every 800us */
DECL|macro|TAP_1_6MS
mdefine_line|#define TAP_1_6MS  0x00060000       /* TX automatic polling every 1.6ms */
DECL|macro|TAP_12_8US
mdefine_line|#define TAP_12_8US 0x00080000       /* TX automatic polling every 12.8us */
DECL|macro|TAP_25_6US
mdefine_line|#define TAP_25_6US 0x000a0000       /* TX automatic polling every 25.6us */
DECL|macro|TAP_51_2US
mdefine_line|#define TAP_51_2US 0x000c0000       /* TX automatic polling every 51.2us */
DECL|macro|TAP_102_4US
mdefine_line|#define TAP_102_4US 0x000e0000      /* TX automatic polling every 102.4us */
DECL|macro|CAL_NOUSE
mdefine_line|#define CAL_NOUSE  0x00000000       /* Not used */
DECL|macro|CAL_8LONG
mdefine_line|#define CAL_8LONG  0x00004000       /* 8-longword alignment */
DECL|macro|CAL_16LONG
mdefine_line|#define CAL_16LONG 0x00008000       /* 16-longword alignment */
DECL|macro|CAL_32LONG
mdefine_line|#define CAL_32LONG 0x0000c000       /* 32-longword alignment */
DECL|macro|PBL_0
mdefine_line|#define PBL_0      0x00000000       /*  DMA burst length = amount in RX FIFO */
DECL|macro|PBL_1
mdefine_line|#define PBL_1      0x00000100       /*  1 longword  DMA burst length */
DECL|macro|PBL_2
mdefine_line|#define PBL_2      0x00000200       /*  2 longwords DMA burst length */
DECL|macro|PBL_4
mdefine_line|#define PBL_4      0x00000400       /*  4 longwords DMA burst length */
DECL|macro|PBL_8
mdefine_line|#define PBL_8      0x00000800       /*  8 longwords DMA burst length */
DECL|macro|PBL_16
mdefine_line|#define PBL_16     0x00001000       /* 16 longwords DMA burst length */
DECL|macro|PBL_32
mdefine_line|#define PBL_32     0x00002000       /* 32 longwords DMA burst length */
DECL|macro|DSL_0
mdefine_line|#define DSL_0      0x00000000       /*  0 longword  / descriptor */
DECL|macro|DSL_1
mdefine_line|#define DSL_1      0x00000004       /*  1 longword  / descriptor */
DECL|macro|DSL_2
mdefine_line|#define DSL_2      0x00000008       /*  2 longwords / descriptor */
DECL|macro|DSL_4
mdefine_line|#define DSL_4      0x00000010       /*  4 longwords / descriptor */
DECL|macro|DSL_8
mdefine_line|#define DSL_8      0x00000020       /*  8 longwords / descriptor */
DECL|macro|DSL_16
mdefine_line|#define DSL_16     0x00000040       /* 16 longwords / descriptor */
DECL|macro|DSL_32
mdefine_line|#define DSL_32     0x00000080       /* 32 longwords / descriptor */
multiline_comment|/*&n;** DC21040 Transmit Poll Demand Register (DE4X5_TPD)&n;*/
DECL|macro|TPD
mdefine_line|#define TPD        0x00000001       /* Transmit Poll Demand */
multiline_comment|/*&n;** DC21040 Receive Poll Demand Register (DE4X5_RPD)&n;*/
DECL|macro|RPD
mdefine_line|#define RPD        0x00000001       /* Receive Poll Demand */
multiline_comment|/*&n;** DC21040 Receive Ring Base Address Register (DE4X5_RRBA)&n;*/
DECL|macro|RRBA
mdefine_line|#define RRBA       0xfffffffc       /* RX Descriptor List Start Address */
multiline_comment|/*&n;** DC21040 Transmit Ring Base Address Register (DE4X5_TRBA)&n;*/
DECL|macro|TRBA
mdefine_line|#define TRBA       0xfffffffc       /* TX Descriptor List Start Address */
multiline_comment|/*&n;** DC21040 Status Register (DE4X5_STS)&n;*/
DECL|macro|STS_BE
mdefine_line|#define STS_BE     0x03800000       /* Bus Error Bits */
DECL|macro|STS_TS
mdefine_line|#define STS_TS     0x00700000       /* Transmit Process State */
DECL|macro|STS_RS
mdefine_line|#define STS_RS     0x000e0000       /* Receive Process State */
DECL|macro|STS_NIS
mdefine_line|#define STS_NIS    0x00010000       /* Normal Interrupt Summary */
DECL|macro|STS_AIS
mdefine_line|#define STS_AIS    0x00008000       /* Abnormal Interrupt Summary */
DECL|macro|STS_ER
mdefine_line|#define STS_ER     0x00004000       /* Early Receive */
DECL|macro|STS_SE
mdefine_line|#define STS_SE     0x00002000       /* System Error */
DECL|macro|STS_LNF
mdefine_line|#define STS_LNF    0x00001000       /* Link Fail */
DECL|macro|STS_FD
mdefine_line|#define STS_FD     0x00000800       /* Full-Duplex Short Frame Received */
DECL|macro|STS_TM
mdefine_line|#define STS_TM     0x00000800       /* Timer Expired (DC21041) */
DECL|macro|STS_AT
mdefine_line|#define STS_AT     0x00000400       /* AUI/TP Pin */
DECL|macro|STS_RWT
mdefine_line|#define STS_RWT    0x00000200       /* Receive Watchdog Time-Out */
DECL|macro|STS_RPS
mdefine_line|#define STS_RPS    0x00000100       /* Receive Process Stopped */
DECL|macro|STS_RU
mdefine_line|#define STS_RU     0x00000080       /* Receive Buffer Unavailable */
DECL|macro|STS_RI
mdefine_line|#define STS_RI     0x00000040       /* Receive Interrupt */
DECL|macro|STS_UNF
mdefine_line|#define STS_UNF    0x00000020       /* Transmit Underflow */
DECL|macro|STS_LNP
mdefine_line|#define STS_LNP    0x00000010       /* Link Pass */
DECL|macro|STS_TJT
mdefine_line|#define STS_TJT    0x00000008       /* Transmit Jabber Time-Out */
DECL|macro|STS_TU
mdefine_line|#define STS_TU     0x00000004       /* Transmit Buffer Unavailable */
DECL|macro|STS_TPS
mdefine_line|#define STS_TPS    0x00000002       /* Transmit Process Stopped */
DECL|macro|STS_TI
mdefine_line|#define STS_TI     0x00000001       /* Transmit Interrupt */
DECL|macro|EB_PAR
mdefine_line|#define EB_PAR     0x00000000       /* Parity Error */
DECL|macro|EB_MA
mdefine_line|#define EB_MA      0x00800000       /* Master Abort */
DECL|macro|EB_TA
mdefine_line|#define EB_TA      0x01000000       /* Target Abort */
DECL|macro|EB_RES0
mdefine_line|#define EB_RES0    0x01800000       /* Reserved */
DECL|macro|EB_RES1
mdefine_line|#define EB_RES1    0x02000000       /* Reserved */
DECL|macro|TS_STOP
mdefine_line|#define TS_STOP    0x00000000       /* Stopped */
DECL|macro|TS_FTD
mdefine_line|#define TS_FTD     0x00100000       /* Fetch Transmit Descriptor */
DECL|macro|TS_WEOT
mdefine_line|#define TS_WEOT    0x00200000       /* Wait for End Of Transmission */
DECL|macro|TS_QDAT
mdefine_line|#define TS_QDAT    0x00300000       /* Queue skb data into TX FIFO */
DECL|macro|TS_RES
mdefine_line|#define TS_RES     0x00400000       /* Reserved */
DECL|macro|TS_SPKT
mdefine_line|#define TS_SPKT    0x00500000       /* Setup Packet */
DECL|macro|TS_SUSP
mdefine_line|#define TS_SUSP    0x00600000       /* Suspended */
DECL|macro|TS_CLTD
mdefine_line|#define TS_CLTD    0x00700000       /* Close Transmit Descriptor */
DECL|macro|RS_STOP
mdefine_line|#define RS_STOP    0x00000000       /* Stopped */
DECL|macro|RS_FRD
mdefine_line|#define RS_FRD     0x00020000       /* Fetch Receive Descriptor */
DECL|macro|RS_CEOR
mdefine_line|#define RS_CEOR    0x00040000       /* Check for End of Receive Packet */
DECL|macro|RS_WFRP
mdefine_line|#define RS_WFRP    0x00060000       /* Wait for Receive Packet */
DECL|macro|RS_SUSP
mdefine_line|#define RS_SUSP    0x00080000       /* Suspended */
DECL|macro|RS_CLRD
mdefine_line|#define RS_CLRD    0x000a0000       /* Close Receive Descriptor */
DECL|macro|RS_FLUSH
mdefine_line|#define RS_FLUSH   0x000c0000       /* Flush RX FIFO */
DECL|macro|RS_QRFS
mdefine_line|#define RS_QRFS    0x000e0000       /* Queue RX FIFO into RX Skb */
DECL|macro|INT_CANCEL
mdefine_line|#define INT_CANCEL 0x0001ffff       /* For zeroing all interrupt sources */
multiline_comment|/*&n;** DC21040 Operation Mode Register (DE4X5_OMR)&n;*/
DECL|macro|OMR_SDP
mdefine_line|#define OMR_SDP    0x02000000       /* SD Polarity - MUST BE ASSERTED */
DECL|macro|OMR_SCR
mdefine_line|#define OMR_SCR    0x01000000       /* Scrambler Mode */
DECL|macro|OMR_PCS
mdefine_line|#define OMR_PCS    0x00800000       /* PCS Function */
DECL|macro|OMR_TTM
mdefine_line|#define OMR_TTM    0x00400000       /* Transmit Threshold Mode */
DECL|macro|OMR_SF
mdefine_line|#define OMR_SF     0x00200000       /* Store and Forward */
DECL|macro|OMR_HBD
mdefine_line|#define OMR_HBD    0x00080000       /* HeartBeat Disable */
DECL|macro|OMR_PS
mdefine_line|#define OMR_PS     0x00040000       /* Port Select */
DECL|macro|OMR_CA
mdefine_line|#define OMR_CA     0x00020000       /* Capture Effect Enable */
DECL|macro|OMR_BP
mdefine_line|#define OMR_BP     0x00010000       /* Back Pressure */
DECL|macro|OMR_TR
mdefine_line|#define OMR_TR     0x0000c000       /* Threshold Control Bits */
DECL|macro|OMR_ST
mdefine_line|#define OMR_ST     0x00002000       /* Start/Stop Transmission Command */
DECL|macro|OMR_FC
mdefine_line|#define OMR_FC     0x00001000       /* Force Collision Mode */
DECL|macro|OMR_OM
mdefine_line|#define OMR_OM     0x00000c00       /* Operating Mode */
DECL|macro|OMR_FD
mdefine_line|#define OMR_FD     0x00000200       /* Full Duplex Mode */
DECL|macro|OMR_FKD
mdefine_line|#define OMR_FKD    0x00000100       /* Flaky Oscillator Disable */
DECL|macro|OMR_PM
mdefine_line|#define OMR_PM     0x00000080       /* Pass All Multicast */
DECL|macro|OMR_PR
mdefine_line|#define OMR_PR     0x00000040       /* Promiscuous Mode */
DECL|macro|OMR_SB
mdefine_line|#define OMR_SB     0x00000020       /* Start/Stop Backoff Counter */
DECL|macro|OMR_IF
mdefine_line|#define OMR_IF     0x00000010       /* Inverse Filtering */
DECL|macro|OMR_PB
mdefine_line|#define OMR_PB     0x00000008       /* Pass Bad Frames */
DECL|macro|OMR_HO
mdefine_line|#define OMR_HO     0x00000004       /* Hash Only Filtering Mode */
DECL|macro|OMR_SR
mdefine_line|#define OMR_SR     0x00000002       /* Start/Stop Receive */
DECL|macro|OMR_HP
mdefine_line|#define OMR_HP     0x00000001       /* Hash/Perfect Receive Filtering Mode */
DECL|macro|TR_72
mdefine_line|#define TR_72      0x00000000       /* Threshold set to 72 bytes */
DECL|macro|TR_96
mdefine_line|#define TR_96      0x00004000       /* Threshold set to 96 bytes */
DECL|macro|TR_128
mdefine_line|#define TR_128     0x00008000       /* Threshold set to 128 bytes */
DECL|macro|TR_160
mdefine_line|#define TR_160     0x0000c000       /* Threshold set to 160 bytes */
multiline_comment|/*&n;** DC21040 Interrupt Mask Register (DE4X5_IMR)&n;*/
DECL|macro|IMR_NIM
mdefine_line|#define IMR_NIM    0x00010000       /* Normal Interrupt Summary Mask */
DECL|macro|IMR_AIM
mdefine_line|#define IMR_AIM    0x00008000       /* Abnormal Interrupt Summary Mask */
DECL|macro|IMR_ERM
mdefine_line|#define IMR_ERM    0x00004000       /* Early Receive Mask */
DECL|macro|IMR_SEM
mdefine_line|#define IMR_SEM    0x00002000       /* System Error Mask */
DECL|macro|IMR_LFM
mdefine_line|#define IMR_LFM    0x00001000       /* Link Fail Mask */
DECL|macro|IMR_FDM
mdefine_line|#define IMR_FDM    0x00000800       /* Full-Duplex (Short Frame) Mask */
DECL|macro|IMR_TMM
mdefine_line|#define IMR_TMM    0x00000800       /* Timer Expired Mask (DC21041) */
DECL|macro|IMR_ATM
mdefine_line|#define IMR_ATM    0x00000400       /* AUI/TP Switch Mask */
DECL|macro|IMR_RWM
mdefine_line|#define IMR_RWM    0x00000200       /* Receive Watchdog Time-Out Mask */
DECL|macro|IMR_RSM
mdefine_line|#define IMR_RSM    0x00000100       /* Receive Stopped Mask */
DECL|macro|IMR_RUM
mdefine_line|#define IMR_RUM    0x00000080       /* Receive Buffer Unavailable Mask */
DECL|macro|IMR_RIM
mdefine_line|#define IMR_RIM    0x00000040       /* Receive Interrupt Mask */
DECL|macro|IMR_UNM
mdefine_line|#define IMR_UNM    0x00000020       /* Underflow Interrupt Mask */
DECL|macro|IMR_LPM
mdefine_line|#define IMR_LPM    0x00000010       /* Link Pass */
DECL|macro|IMR_TJM
mdefine_line|#define IMR_TJM    0x00000008       /* Transmit Time-Out Jabber Mask */
DECL|macro|IMR_TUM
mdefine_line|#define IMR_TUM    0x00000004       /* Transmit Buffer Unavailable Mask */
DECL|macro|IMR_TSM
mdefine_line|#define IMR_TSM    0x00000002       /* Transmission Stopped Mask */
DECL|macro|IMR_TIM
mdefine_line|#define IMR_TIM    0x00000001       /* Transmit Interrupt Mask */
multiline_comment|/*&n;** DC21040 Missed Frames Counter (DE4X5_MFC)&n;*/
DECL|macro|MFC_OVFL
mdefine_line|#define MFC_OVFL   0x00010000       /* Missed Frames Counter Overflow Bit */
DECL|macro|MFC_CNTR
mdefine_line|#define MFC_CNTR   0x0000ffff       /* Missed Frames Counter Bits */
multiline_comment|/*&n;** DC21140 Missed Frames and FIFO Overflow Counters (DE4X5_MFC)&n;*/
DECL|macro|MFC_FOCO
mdefine_line|#define MFC_FOCO   0x10000000       /* FIFO Overflow Counter Overflow Bit */
DECL|macro|MFC_FOC
mdefine_line|#define MFC_FOC    0x0ffe0000       /* FIFO Overflow Counter Bits */
DECL|macro|MFC_OVFL
mdefine_line|#define MFC_OVFL   0x00010000       /* Missed Frames Counter Overflow Bit */
DECL|macro|MFC_CNTR
mdefine_line|#define MFC_CNTR   0x0000ffff       /* Missed Frames Counter Bits */
DECL|macro|MFC_FOCM
mdefine_line|#define MFC_FOCM   0x1ffe0000       /* FIFO Overflow Counter Mask */
multiline_comment|/*&n;** DC21040 Ethernet Address PROM (DE4X5_APROM)&n;*/
DECL|macro|APROM_DN
mdefine_line|#define APROM_DN   0x80000000       /* Data Not Valid */
DECL|macro|APROM_DT
mdefine_line|#define APROM_DT   0x000000ff       /* Address Byte */
multiline_comment|/*&n;** DC21041 Boot/Ethernet Address ROM (DE4X5_BROM)&n;*/
DECL|macro|BROM_MODE
mdefine_line|#define BROM_MODE 0x00008000       /* MODE_1: 0,  MODE_0: 1  (read only) */
DECL|macro|BROM_RD
mdefine_line|#define BROM_RD   0x00004000       /* Read from Boot ROM */
DECL|macro|BROM_WR
mdefine_line|#define BROM_WR   0x00002000       /* Write to Boot ROM */
DECL|macro|BROM_BR
mdefine_line|#define BROM_BR   0x00001000       /* Select Boot ROM when set */
DECL|macro|BROM_SR
mdefine_line|#define BROM_SR   0x00000800       /* Select Serial ROM when set */
DECL|macro|BROM_REG
mdefine_line|#define BROM_REG  0x00000400       /* External Register Select */
DECL|macro|BROM_DT
mdefine_line|#define BROM_DT   0x000000ff       /* Data Byte */
multiline_comment|/*&n;** DC21041 Serial/Ethernet Address ROM (DE4X5_SROM, DE4X5_MII)&n;*/
DECL|macro|MII_MDI
mdefine_line|#define MII_MDI   0x00080000       /* MII Management Data In */
DECL|macro|MII_MDO
mdefine_line|#define MII_MDO   0x00060000       /* MII Management Mode/Data Out */
DECL|macro|MII_MRD
mdefine_line|#define MII_MRD   0x00040000       /* MII Management Define Read Mode */
DECL|macro|MII_MWR
mdefine_line|#define MII_MWR   0x00000000       /* MII Management Define Write Mode */
DECL|macro|MII_MDT
mdefine_line|#define MII_MDT   0x00020000       /* MII Management Data Out */
DECL|macro|MII_MDC
mdefine_line|#define MII_MDC   0x00010000       /* MII Management Clock */
DECL|macro|MII_RD
mdefine_line|#define MII_RD    0x00004000       /* Read from MII */
DECL|macro|MII_WR
mdefine_line|#define MII_WR    0x00002000       /* Write to MII */
DECL|macro|MII_SEL
mdefine_line|#define MII_SEL   0x00000800       /* Select MII when RESET */
DECL|macro|SROM_MODE
mdefine_line|#define SROM_MODE 0x00008000       /* MODE_1: 0,  MODE_0: 1  (read only) */
DECL|macro|SROM_RD
mdefine_line|#define SROM_RD   0x00004000       /* Read from Boot ROM */
DECL|macro|SROM_WR
mdefine_line|#define SROM_WR   0x00002000       /* Write to Boot ROM */
DECL|macro|SROM_BR
mdefine_line|#define SROM_BR   0x00001000       /* Select Boot ROM when set */
DECL|macro|SROM_SR
mdefine_line|#define SROM_SR   0x00000800       /* Select Serial ROM when set */
DECL|macro|SROM_REG
mdefine_line|#define SROM_REG  0x00000400       /* External Register Select */
DECL|macro|SROM_DT
mdefine_line|#define SROM_DT   0x000000ff       /* Data Byte */
DECL|macro|DT_OUT
mdefine_line|#define DT_OUT    0x00000008       /* Serial Data Out */
DECL|macro|DT_IN
mdefine_line|#define DT_IN     0x00000004       /* Serial Data In */
DECL|macro|DT_CLK
mdefine_line|#define DT_CLK    0x00000002       /* Serial ROM Clock */
DECL|macro|DT_CS
mdefine_line|#define DT_CS     0x00000001       /* Serial ROM Chip Select */
DECL|macro|MII_PREAMBLE
mdefine_line|#define MII_PREAMBLE 0xffffffff    /* MII Management Preamble */
DECL|macro|MII_TEST
mdefine_line|#define MII_TEST     0xaaaaaaaa    /* MII Test Signal */
DECL|macro|MII_STRD
mdefine_line|#define MII_STRD     0x06          /* Start of Frame+Op Code: use low nibble */
DECL|macro|MII_STWR
mdefine_line|#define MII_STWR     0x0a          /* Start of Frame+Op Code: use low nibble */
DECL|macro|MII_CR
mdefine_line|#define MII_CR       0x00          /* MII Management Control Register */
DECL|macro|MII_SR
mdefine_line|#define MII_SR       0x01          /* MII Management Status Register */
DECL|macro|MII_ID0
mdefine_line|#define MII_ID0      0x02          /* PHY Identifier Register 0 */
DECL|macro|MII_ID1
mdefine_line|#define MII_ID1      0x03          /* PHY Identifier Register 1 */
DECL|macro|MII_ANA
mdefine_line|#define MII_ANA      0x04          /* Auto Negotiation Advertisement */
DECL|macro|MII_ANLPA
mdefine_line|#define MII_ANLPA    0x05          /* Auto Negotiation Link Partner Ability */
DECL|macro|MII_ANE
mdefine_line|#define MII_ANE      0x06          /* Auto Negotiation Expansion */
DECL|macro|MII_ANP
mdefine_line|#define MII_ANP      0x07          /* Auto Negotiation Next Page TX */
DECL|macro|DE4X5_MAX_MII
mdefine_line|#define DE4X5_MAX_MII 32           /* Maximum address of MII PHY devices */
multiline_comment|/*&n;** MII Management Control Register&n;*/
DECL|macro|MII_CR_RST
mdefine_line|#define MII_CR_RST  0x8000         /* RESET the PHY chip */
DECL|macro|MII_CR_LPBK
mdefine_line|#define MII_CR_LPBK 0x4000         /* Loopback enable */
DECL|macro|MII_CR_SPD
mdefine_line|#define MII_CR_SPD  0x2000         /* 0: 10Mb/s; 1: 100Mb/s */
DECL|macro|MII_CR_10
mdefine_line|#define MII_CR_10   0x0000         /* Set 10Mb/s */
DECL|macro|MII_CR_100
mdefine_line|#define MII_CR_100  0x2000         /* Set 100Mb/s */
DECL|macro|MII_CR_ASSE
mdefine_line|#define MII_CR_ASSE 0x1000         /* Auto Speed Select Enable */
DECL|macro|MII_CR_PD
mdefine_line|#define MII_CR_PD   0x0800         /* Power Down */
DECL|macro|MII_CR_ISOL
mdefine_line|#define MII_CR_ISOL 0x0400         /* Isolate Mode */
DECL|macro|MII_CR_RAN
mdefine_line|#define MII_CR_RAN  0x0200         /* Restart Auto Negotiation */
DECL|macro|MII_CR_FDM
mdefine_line|#define MII_CR_FDM  0x0100         /* Full Duplex Mode */
DECL|macro|MII_CR_CTE
mdefine_line|#define MII_CR_CTE  0x0080         /* Collision Test Enable */
multiline_comment|/*&n;** MII Management Status Register&n;*/
DECL|macro|MII_SR_T4C
mdefine_line|#define MII_SR_T4C  0x8000         /* 100BASE-T4 capable */
DECL|macro|MII_SR_TXFD
mdefine_line|#define MII_SR_TXFD 0x4000         /* 100BASE-TX Full Duplex capable */
DECL|macro|MII_SR_TXHD
mdefine_line|#define MII_SR_TXHD 0x2000         /* 100BASE-TX Half Duplex capable */
DECL|macro|MII_SR_TFD
mdefine_line|#define MII_SR_TFD  0x1000         /* 10BASE-T Full Duplex capable */
DECL|macro|MII_SR_THD
mdefine_line|#define MII_SR_THD  0x0800         /* 10BASE-T Half Duplex capable */
DECL|macro|MII_SR_ASSC
mdefine_line|#define MII_SR_ASSC 0x0020         /* Auto Speed Selection Complete*/
DECL|macro|MII_SR_RFD
mdefine_line|#define MII_SR_RFD  0x0010         /* Remote Fault Detected */
DECL|macro|MII_SR_ANC
mdefine_line|#define MII_SR_ANC  0x0008         /* Auto Negotiation capable */
DECL|macro|MII_SR_LKS
mdefine_line|#define MII_SR_LKS  0x0004         /* Link Status */
DECL|macro|MII_SR_JABD
mdefine_line|#define MII_SR_JABD 0x0002         /* Jabber Detect */
DECL|macro|MII_SR_XC
mdefine_line|#define MII_SR_XC   0x0001         /* Extended Capabilities */
multiline_comment|/*&n;** MII Management Auto Negotiation Advertisement Register&n;*/
DECL|macro|MII_ANA_TAF
mdefine_line|#define MII_ANA_TAF  0x03e0        /* Technology Ability Field */
DECL|macro|MII_ANA_T4AM
mdefine_line|#define MII_ANA_T4AM 0x0400        /* T4 Technology Ability Mask */
DECL|macro|MII_ANA_TXAM
mdefine_line|#define MII_ANA_TXAM 0x0180        /* TX Technology Ability Mask */
DECL|macro|MII_ANA_FDAM
mdefine_line|#define MII_ANA_FDAM 0x0140        /* Full Duplex Technology Ability Mask */
DECL|macro|MII_ANA_HDAM
mdefine_line|#define MII_ANA_HDAM 0x02a0        /* Half Duplex Technology Ability Mask */
DECL|macro|MII_ANA_100M
mdefine_line|#define MII_ANA_100M 0x0380        /* 100Mb Technology Ability Mask */
DECL|macro|MII_ANA_10M
mdefine_line|#define MII_ANA_10M  0x0060        /* 10Mb Technology Ability Mask */
DECL|macro|MII_ANA_CSMA
mdefine_line|#define MII_ANA_CSMA 0x0001        /* CSMA-CD Capable */
multiline_comment|/*&n;** MII Management Auto Negotiation Remote End Register&n;*/
DECL|macro|MII_ANLPA_NP
mdefine_line|#define MII_ANLPA_NP   0x8000      /* Next Page (Enable) */
DECL|macro|MII_ANLPA_ACK
mdefine_line|#define MII_ANLPA_ACK  0x4000      /* Remote Acknowledge */
DECL|macro|MII_ANLPA_RF
mdefine_line|#define MII_ANLPA_RF   0x2000      /* Remote Fault */
DECL|macro|MII_ANLPA_TAF
mdefine_line|#define MII_ANLPA_TAF  0x03e0      /* Technology Ability Field */
DECL|macro|MII_ANLPA_T4AM
mdefine_line|#define MII_ANLPA_T4AM 0x0400      /* T4 Technology Ability Mask */
DECL|macro|MII_ANLPA_TXAM
mdefine_line|#define MII_ANLPA_TXAM 0x0180      /* TX Technology Ability Mask */
DECL|macro|MII_ANLPA_FDAM
mdefine_line|#define MII_ANLPA_FDAM 0x0140      /* Full Duplex Technology Ability Mask */
DECL|macro|MII_ANLPA_HDAM
mdefine_line|#define MII_ANLPA_HDAM 0x02a0      /* Half Duplex Technology Ability Mask */
DECL|macro|MII_ANLPA_100M
mdefine_line|#define MII_ANLPA_100M 0x0380      /* 100Mb Technology Ability Mask */
DECL|macro|MII_ANLPA_10M
mdefine_line|#define MII_ANLPA_10M  0x0060      /* 10Mb Technology Ability Mask */
DECL|macro|MII_ANLPA_CSMA
mdefine_line|#define MII_ANLPA_CSMA 0x0001      /* CSMA-CD Capable */
multiline_comment|/*&n;** SROM Media Definitions (ABG SROM Section)&n;*/
DECL|macro|MEDIA_NWAY
mdefine_line|#define MEDIA_NWAY     0x0080      /* Nway (Auto Negotiation) on PHY */
DECL|macro|MEDIA_MII
mdefine_line|#define MEDIA_MII      0x0040      /* MII Present on the adapter */
DECL|macro|MEDIA_FIBRE
mdefine_line|#define MEDIA_FIBRE    0x0008      /* Fibre Media present */
DECL|macro|MEDIA_AUI
mdefine_line|#define MEDIA_AUI      0x0004      /* AUI Media present */
DECL|macro|MEDIA_TP
mdefine_line|#define MEDIA_TP       0x0002      /* TP Media present */
DECL|macro|MEDIA_BNC
mdefine_line|#define MEDIA_BNC      0x0001      /* BNC Media present */
multiline_comment|/*&n;** DC21040 Full Duplex Register (DE4X5_FDR)&n;*/
DECL|macro|FDR_FDACV
mdefine_line|#define FDR_FDACV  0x0000ffff      /* Full Duplex Auto Configuration Value */
multiline_comment|/*&n;** DC21041 General Purpose Timer Register (DE4X5_GPT)&n;*/
DECL|macro|GPT_CON
mdefine_line|#define GPT_CON  0x00010000        /* One shot: 0,  Continuous: 1 */
DECL|macro|GPT_VAL
mdefine_line|#define GPT_VAL  0x0000ffff        /* Timer Value */
multiline_comment|/*&n;** DC21140 General Purpose Register (DE4X5_GEP) (hardware dependent bits)&n;*/
multiline_comment|/* Valid ONLY for DE500 hardware */
DECL|macro|GEP_LNP
mdefine_line|#define GEP_LNP  0x00000080        /* Link Pass               (input) */
DECL|macro|GEP_SLNK
mdefine_line|#define GEP_SLNK 0x00000040        /* SYM LINK                (input) */
DECL|macro|GEP_SDET
mdefine_line|#define GEP_SDET 0x00000020        /* Signal Detect           (input) */
DECL|macro|GEP_HRST
mdefine_line|#define GEP_HRST 0x00000010        /* Hard RESET (to PHY)     (output) */
DECL|macro|GEP_FDXD
mdefine_line|#define GEP_FDXD 0x00000008        /* Full Duplex Disable     (output) */
DECL|macro|GEP_PHYL
mdefine_line|#define GEP_PHYL 0x00000004        /* PHY Loopback            (output) */
DECL|macro|GEP_FLED
mdefine_line|#define GEP_FLED 0x00000002        /* Force Activity LED on   (output) */
DECL|macro|GEP_MODE
mdefine_line|#define GEP_MODE 0x00000001        /* 0: 10Mb/s,  1: 100Mb/s           */
DECL|macro|GEP_INIT
mdefine_line|#define GEP_INIT 0x0000011f        /* Setup inputs (0) and outputs (1) */
multiline_comment|/*&n;** DC21040 SIA Status Register (DE4X5_SISR)&n;*/
DECL|macro|SISR_LPC
mdefine_line|#define SISR_LPC   0xffff0000      /* Link Partner&squot;s Code Word */
DECL|macro|SISR_LPN
mdefine_line|#define SISR_LPN   0x00008000      /* Link Partner Negotiable */
DECL|macro|SISR_ANS
mdefine_line|#define SISR_ANS   0x00007000      /* Auto Negotiation Arbitration State */
DECL|macro|SISR_NSN
mdefine_line|#define SISR_NSN   0x00000800      /* Non Stable NLPs Detected */
DECL|macro|SISR_ANR_FDS
mdefine_line|#define SISR_ANR_FDS 0x00000400    /* Auto Negotiate Restart/Full Duplex Sel.*/
DECL|macro|SISR_NRA
mdefine_line|#define SISR_NRA   0x00000200      /* Non Selected Port Receive Activity */
DECL|macro|SISR_SRA
mdefine_line|#define SISR_SRA   0x00000100      /* Selected Port Receive Activity */
DECL|macro|SISR_DAO
mdefine_line|#define SISR_DAO   0x00000080      /* PLL All One */
DECL|macro|SISR_DAZ
mdefine_line|#define SISR_DAZ   0x00000040      /* PLL All Zero */
DECL|macro|SISR_DSP
mdefine_line|#define SISR_DSP   0x00000020      /* PLL Self-Test Pass */
DECL|macro|SISR_DSD
mdefine_line|#define SISR_DSD   0x00000010      /* PLL Self-Test Done */
DECL|macro|SISR_APS
mdefine_line|#define SISR_APS   0x00000008      /* Auto Polarity State */
DECL|macro|SISR_LKF
mdefine_line|#define SISR_LKF   0x00000004      /* Link Fail Status */
DECL|macro|SISR_NCR
mdefine_line|#define SISR_NCR   0x00000002      /* Network Connection Error */
DECL|macro|SISR_PAUI
mdefine_line|#define SISR_PAUI  0x00000001      /* AUI_TP Indication */
DECL|macro|SIA_RESET
mdefine_line|#define SIA_RESET  0x00000000      /* SIA Reset */
DECL|macro|ANS_NDIS
mdefine_line|#define ANS_NDIS   0x00000000      /* Nway disable */
DECL|macro|ANS_TDIS
mdefine_line|#define ANS_TDIS   0x00001000      /* Transmit Disable */
DECL|macro|ANS_ADET
mdefine_line|#define ANS_ADET   0x00002000      /* Ability Detect */
DECL|macro|ANS_ACK
mdefine_line|#define ANS_ACK    0x00003000      /* Acknowledge */
DECL|macro|ANS_CACK
mdefine_line|#define ANS_CACK   0x00004000      /* Complete Acknowledge */
DECL|macro|ANS_NWOK
mdefine_line|#define ANS_NWOK   0x00005000      /* Nway OK - FLP Link Good */
DECL|macro|ANS_LCHK
mdefine_line|#define ANS_LCHK   0x00006000      /* Link Check */
multiline_comment|/*&n;** DC21040 SIA Connectivity Register (DE4X5_SICR)&n;*/
DECL|macro|SICR_SDM
mdefine_line|#define SICR_SDM   0xffff0000       /* SIA Diagnostics Mode */
DECL|macro|SICR_OE57
mdefine_line|#define SICR_OE57  0x00008000       /* Output Enable 5 6 7 */
DECL|macro|SICR_OE24
mdefine_line|#define SICR_OE24  0x00004000       /* Output Enable 2 4 */
DECL|macro|SICR_OE13
mdefine_line|#define SICR_OE13  0x00002000       /* Output Enable 1 3 */
DECL|macro|SICR_IE
mdefine_line|#define SICR_IE    0x00001000       /* Input Enable */
DECL|macro|SICR_EXT
mdefine_line|#define SICR_EXT   0x00000000       /* SIA MUX Select External SIA Mode */
DECL|macro|SICR_D_SIA
mdefine_line|#define SICR_D_SIA 0x00000400       /* SIA MUX Select Diagnostics - SIA Sigs */
DECL|macro|SICR_DPLL
mdefine_line|#define SICR_DPLL  0x00000800       /* SIA MUX Select Diagnostics - DPLL Sigs*/
DECL|macro|SICR_APLL
mdefine_line|#define SICR_APLL  0x00000a00       /* SIA MUX Select Diagnostics - DPLL Sigs*/
DECL|macro|SICR_D_RxM
mdefine_line|#define SICR_D_RxM 0x00000c00       /* SIA MUX Select Diagnostics - RxM Sigs */
DECL|macro|SICR_M_RxM
mdefine_line|#define SICR_M_RxM 0x00000d00       /* SIA MUX Select Diagnostics - RxM Sigs */
DECL|macro|SICR_LNKT
mdefine_line|#define SICR_LNKT  0x00000e00       /* SIA MUX Select Diagnostics - Link Test*/
DECL|macro|SICR_SEL
mdefine_line|#define SICR_SEL   0x00000f00       /* SIA MUX Select AUI or TP with LEDs */
DECL|macro|SICR_ASE
mdefine_line|#define SICR_ASE   0x00000080       /* APLL Start Enable*/
DECL|macro|SICR_SIM
mdefine_line|#define SICR_SIM   0x00000040       /* Serial Interface Input Multiplexer */
DECL|macro|SICR_ENI
mdefine_line|#define SICR_ENI   0x00000020       /* Encoder Input Multiplexer */
DECL|macro|SICR_EDP
mdefine_line|#define SICR_EDP   0x00000010       /* SIA PLL External Input Enable */
DECL|macro|SICR_AUI
mdefine_line|#define SICR_AUI   0x00000008       /* 10Base-T or AUI */
DECL|macro|SICR_CAC
mdefine_line|#define SICR_CAC   0x00000004       /* CSR Auto Configuration */
DECL|macro|SICR_PS
mdefine_line|#define SICR_PS    0x00000002       /* Pin AUI/TP Selection */
DECL|macro|SICR_SRL
mdefine_line|#define SICR_SRL   0x00000001       /* SIA Reset */
DECL|macro|SICR_RESET
mdefine_line|#define SICR_RESET 0xffff0000       /* Reset value for SICR */
multiline_comment|/*&n;** DC21040 SIA Transmit and Receive Register (DE4X5_STRR)&n;*/
DECL|macro|STRR_TAS
mdefine_line|#define STRR_TAS   0x00008000       /* 10Base-T/AUI Autosensing Enable */
DECL|macro|STRR_SPP
mdefine_line|#define STRR_SPP   0x00004000       /* Set Polarity Plus */
DECL|macro|STRR_APE
mdefine_line|#define STRR_APE   0x00002000       /* Auto Polarity Enable */
DECL|macro|STRR_LTE
mdefine_line|#define STRR_LTE   0x00001000       /* Link Test Enable */
DECL|macro|STRR_SQE
mdefine_line|#define STRR_SQE   0x00000800       /* Signal Quality Enable */
DECL|macro|STRR_CLD
mdefine_line|#define STRR_CLD   0x00000400       /* Collision Detect Enable */
DECL|macro|STRR_CSQ
mdefine_line|#define STRR_CSQ   0x00000200       /* Collision Squelch Enable */
DECL|macro|STRR_RSQ
mdefine_line|#define STRR_RSQ   0x00000100       /* Receive Squelch Enable */
DECL|macro|STRR_ANE
mdefine_line|#define STRR_ANE   0x00000080       /* Auto Negotiate Enable */
DECL|macro|STRR_HDE
mdefine_line|#define STRR_HDE   0x00000040       /* Half Duplex Enable */
DECL|macro|STRR_CPEN
mdefine_line|#define STRR_CPEN  0x00000030       /* Compensation Enable */
DECL|macro|STRR_LSE
mdefine_line|#define STRR_LSE   0x00000008       /* Link Pulse Send Enable */
DECL|macro|STRR_DREN
mdefine_line|#define STRR_DREN  0x00000004       /* Driver Enable */
DECL|macro|STRR_LBK
mdefine_line|#define STRR_LBK   0x00000002       /* Loopback Enable */
DECL|macro|STRR_ECEN
mdefine_line|#define STRR_ECEN  0x00000001       /* Encoder Enable */
DECL|macro|STRR_RESET
mdefine_line|#define STRR_RESET 0xffffffff       /* Reset value for STRR */
multiline_comment|/*&n;** DC21040 SIA General Register (DE4X5_SIGR)&n;*/
DECL|macro|SIGR_LV2
mdefine_line|#define SIGR_LV2   0x00008000       /* General Purpose LED2 value */
DECL|macro|SIGR_LE2
mdefine_line|#define SIGR_LE2   0x00004000       /* General Purpose LED2 enable */
DECL|macro|SIGR_FRL
mdefine_line|#define SIGR_FRL   0x00002000       /* Force Receiver Low */
DECL|macro|SIGR_DPST
mdefine_line|#define SIGR_DPST  0x00001000       /* PLL Self Test Start */
DECL|macro|SIGR_LSD
mdefine_line|#define SIGR_LSD   0x00000800       /* LED Stretch Disable */
DECL|macro|SIGR_FLF
mdefine_line|#define SIGR_FLF   0x00000400       /* Force Link Fail */
DECL|macro|SIGR_FUSQ
mdefine_line|#define SIGR_FUSQ  0x00000200       /* Force Unsquelch */
DECL|macro|SIGR_TSCK
mdefine_line|#define SIGR_TSCK  0x00000100       /* Test Clock */
DECL|macro|SIGR_LV1
mdefine_line|#define SIGR_LV1   0x00000080       /* General Purpose LED1 value */
DECL|macro|SIGR_LE1
mdefine_line|#define SIGR_LE1   0x00000040       /* General Purpose LED1 enable */
DECL|macro|SIGR_RWR
mdefine_line|#define SIGR_RWR   0x00000020       /* Receive Watchdog Release */
DECL|macro|SIGR_RWD
mdefine_line|#define SIGR_RWD   0x00000010       /* Receive Watchdog Disable */
DECL|macro|SIGR_ABM
mdefine_line|#define SIGR_ABM   0x00000008       /* BNC: 0,  AUI:1 */
DECL|macro|SIGR_JCK
mdefine_line|#define SIGR_JCK   0x00000004       /* Jabber Clock */
DECL|macro|SIGR_HUJ
mdefine_line|#define SIGR_HUJ   0x00000002       /* Host Unjab */
DECL|macro|SIGR_JBD
mdefine_line|#define SIGR_JBD   0x00000001       /* Jabber Disable */
DECL|macro|SIGR_RESET
mdefine_line|#define SIGR_RESET 0xffff0000       /* Reset value for SIGR */
multiline_comment|/*&n;** Receive Descriptor Bit Summary&n;*/
DECL|macro|R_OWN
mdefine_line|#define R_OWN      0x80000000       /* Own Bit */
DECL|macro|RD_FL
mdefine_line|#define RD_FL      0x7fff0000       /* Frame Length */
DECL|macro|RD_ES
mdefine_line|#define RD_ES      0x00008000       /* Error Summary */
DECL|macro|RD_LE
mdefine_line|#define RD_LE      0x00004000       /* Length Error */
DECL|macro|RD_DT
mdefine_line|#define RD_DT      0x00003000       /* Data Type */
DECL|macro|RD_RF
mdefine_line|#define RD_RF      0x00000800       /* Runt Frame */
DECL|macro|RD_MF
mdefine_line|#define RD_MF      0x00000400       /* Multicast Frame */
DECL|macro|RD_FS
mdefine_line|#define RD_FS      0x00000200       /* First Descriptor */
DECL|macro|RD_LS
mdefine_line|#define RD_LS      0x00000100       /* Last Descriptor */
DECL|macro|RD_TL
mdefine_line|#define RD_TL      0x00000080       /* Frame Too Long */
DECL|macro|RD_CS
mdefine_line|#define RD_CS      0x00000040       /* Collision Seen */
DECL|macro|RD_FT
mdefine_line|#define RD_FT      0x00000020       /* Frame Type */
DECL|macro|RD_RJ
mdefine_line|#define RD_RJ      0x00000010       /* Receive Watchdog */
DECL|macro|RD_DB
mdefine_line|#define RD_DB      0x00000004       /* Dribbling Bit */
DECL|macro|RD_CE
mdefine_line|#define RD_CE      0x00000002       /* CRC Error */
DECL|macro|RD_OF
mdefine_line|#define RD_OF      0x00000001       /* Overflow */
DECL|macro|RD_RER
mdefine_line|#define RD_RER     0x02000000       /* Receive End Of Ring */
DECL|macro|RD_RCH
mdefine_line|#define RD_RCH     0x01000000       /* Second Address Chained */
DECL|macro|RD_RBS2
mdefine_line|#define RD_RBS2    0x003ff800       /* Buffer 2 Size */
DECL|macro|RD_RBS1
mdefine_line|#define RD_RBS1    0x000007ff       /* Buffer 1 Size */
multiline_comment|/*&n;** Transmit Descriptor Bit Summary&n;*/
DECL|macro|T_OWN
mdefine_line|#define T_OWN      0x80000000       /* Own Bit */
DECL|macro|TD_ES
mdefine_line|#define TD_ES      0x00008000       /* Error Summary */
DECL|macro|TD_TO
mdefine_line|#define TD_TO      0x00004000       /* Transmit Jabber Time-Out */
DECL|macro|TD_LO
mdefine_line|#define TD_LO      0x00000800       /* Loss Of Carrier */
DECL|macro|TD_NC
mdefine_line|#define TD_NC      0x00000400       /* No Carrier */
DECL|macro|TD_LC
mdefine_line|#define TD_LC      0x00000200       /* Late Collision */
DECL|macro|TD_EC
mdefine_line|#define TD_EC      0x00000100       /* Excessive Collisions */
DECL|macro|TD_HF
mdefine_line|#define TD_HF      0x00000080       /* Heartbeat Fail */
DECL|macro|TD_CC
mdefine_line|#define TD_CC      0x00000078       /* Collision Counter */
DECL|macro|TD_LF
mdefine_line|#define TD_LF      0x00000004       /* Link Fail */
DECL|macro|TD_UF
mdefine_line|#define TD_UF      0x00000002       /* Underflow Error */
DECL|macro|TD_DE
mdefine_line|#define TD_DE      0x00000001       /* Deferred */
DECL|macro|TD_IC
mdefine_line|#define TD_IC      0x80000000       /* Interrupt On Completion */
DECL|macro|TD_LS
mdefine_line|#define TD_LS      0x40000000       /* Last Segment */
DECL|macro|TD_FS
mdefine_line|#define TD_FS      0x20000000       /* First Segment */
DECL|macro|TD_FT1
mdefine_line|#define TD_FT1     0x10000000       /* Filtering Type */
DECL|macro|TD_SET
mdefine_line|#define TD_SET     0x08000000       /* Setup Packet */
DECL|macro|TD_AC
mdefine_line|#define TD_AC      0x04000000       /* Add CRC Disable */
DECL|macro|TD_TER
mdefine_line|#define TD_TER     0x02000000       /* Transmit End Of Ring */
DECL|macro|TD_TCH
mdefine_line|#define TD_TCH     0x01000000       /* Second Address Chained */
DECL|macro|TD_DPD
mdefine_line|#define TD_DPD     0x00800000       /* Disabled Padding */
DECL|macro|TD_FT0
mdefine_line|#define TD_FT0     0x00400000       /* Filtering Type */
DECL|macro|TD_RBS2
mdefine_line|#define TD_RBS2    0x003ff800       /* Buffer 2 Size */
DECL|macro|TD_RBS1
mdefine_line|#define TD_RBS1    0x000007ff       /* Buffer 1 Size */
DECL|macro|PERFECT_F
mdefine_line|#define PERFECT_F  0x00000000
DECL|macro|HASH_F
mdefine_line|#define HASH_F     TD_FT0
DECL|macro|INVERSE_F
mdefine_line|#define INVERSE_F  TD_FT1
DECL|macro|HASH_O_F
mdefine_line|#define HASH_O_F   TD_FT1| TD_F0
multiline_comment|/*&n;** Media / mode state machine definitions&n;*/
DECL|macro|NC
mdefine_line|#define NC              0x0000     /* No Connection */
DECL|macro|TP
mdefine_line|#define TP              0x0001     /* 10Base-T */
DECL|macro|TP_NW
mdefine_line|#define TP_NW           0x0002     /* 10Base-T with Nway */
DECL|macro|BNC
mdefine_line|#define BNC             0x0004     /* Thinwire */
DECL|macro|AUI
mdefine_line|#define AUI             0x0008     /* Thickwire */
DECL|macro|BNC_AUI
mdefine_line|#define BNC_AUI         0x0010     /* BNC/AUI on DC21040 indistinguishable */
DECL|macro|ANS
mdefine_line|#define ANS             0x0020     /* Intermediate AutoNegotiation State */
DECL|macro|ANS_1
mdefine_line|#define ANS_1           0x0021     /* Intermediate AutoNegotiation State */
DECL|macro|_10Mb
mdefine_line|#define _10Mb           0x0040     /* 10Mb/s Ethernet */
DECL|macro|_100Mb
mdefine_line|#define _100Mb          0x0080     /* 100Mb/s Ethernet */
DECL|macro|SPD_DET
mdefine_line|#define SPD_DET         0x0100     /* Parallel speed detection */
DECL|macro|INIT
mdefine_line|#define INIT            0x0200     /* Initial state */
DECL|macro|EXT_SIA
mdefine_line|#define EXT_SIA         0x0400     /* External SIA for motherboard chip */
DECL|macro|ANS_SUSPECT
mdefine_line|#define ANS_SUSPECT     0x0802     /* Suspect the ANS (TP) port is down */
DECL|macro|TP_SUSPECT
mdefine_line|#define TP_SUSPECT      0x0803     /* Suspect the TP port is down */
DECL|macro|BNC_AUI_SUSPECT
mdefine_line|#define BNC_AUI_SUSPECT 0x0804     /* Suspect the BNC or AUI port is down */
DECL|macro|EXT_SIA_SUSPECT
mdefine_line|#define EXT_SIA_SUSPECT 0x0805     /* Suspect the EXT SIA port is down */
DECL|macro|BNC_SUSPECT
mdefine_line|#define BNC_SUSPECT     0x0806     /* Suspect the BNC port is down */
DECL|macro|AUI_SUSPECT
mdefine_line|#define AUI_SUSPECT     0x0807     /* Suspect the AUI port is down */
DECL|macro|AUTO
mdefine_line|#define AUTO            0x4000     /* Auto sense the media or speed */
DECL|macro|TIMER_CB
mdefine_line|#define TIMER_CB        0x80000000 /* Timer callback detection */
multiline_comment|/*&n;** Miscellaneous&n;*/
DECL|macro|PCI
mdefine_line|#define PCI  0
DECL|macro|EISA
mdefine_line|#define EISA 1
DECL|macro|HASH_TABLE_LEN
mdefine_line|#define HASH_TABLE_LEN   512       /* Bits */
DECL|macro|HASH_BITS
mdefine_line|#define HASH_BITS        0x01ff    /* 9 LS bits */
DECL|macro|SETUP_FRAME_LEN
mdefine_line|#define SETUP_FRAME_LEN  192       /* Bytes */
DECL|macro|IMPERF_PA_OFFSET
mdefine_line|#define IMPERF_PA_OFFSET 156       /* Bytes */
DECL|macro|POLL_DEMAND
mdefine_line|#define POLL_DEMAND          1
DECL|macro|LOST_MEDIA_THRESHOLD
mdefine_line|#define LOST_MEDIA_THRESHOLD 3
DECL|macro|LOST_MEDIA
mdefine_line|#define LOST_MEDIA           (lp-&gt;lostMedia &gt; LOST_MEDIA_THRESHOLD)
DECL|macro|MASK_INTERRUPTS
mdefine_line|#define MASK_INTERRUPTS      1
DECL|macro|UNMASK_INTERRUPTS
mdefine_line|#define UNMASK_INTERRUPTS    0
DECL|macro|DE4X5_STRLEN
mdefine_line|#define DE4X5_STRLEN         8
DECL|macro|DE4X5_INIT
mdefine_line|#define DE4X5_INIT           0     /* Initialisation time */
DECL|macro|DE4X5_RUN
mdefine_line|#define DE4X5_RUN            1     /* Run time */
DECL|macro|DE4X5_SAVE_STATE
mdefine_line|#define DE4X5_SAVE_STATE     0
DECL|macro|DE4X5_RESTORE_STATE
mdefine_line|#define DE4X5_RESTORE_STATE  1
multiline_comment|/*&n;** Address Filtering Modes&n;*/
DECL|macro|PERFECT
mdefine_line|#define PERFECT              0     /* 16 perfect physical addresses */
DECL|macro|HASH_PERF
mdefine_line|#define HASH_PERF            1     /* 1 perfect, 512 multicast addresses */
DECL|macro|PERFECT_REJ
mdefine_line|#define PERFECT_REJ          2     /* Reject 16 perfect physical addresses */
DECL|macro|ALL_HASH
mdefine_line|#define ALL_HASH             3     /* Hashes all physical &amp; multicast addrs */
DECL|macro|ALL
mdefine_line|#define ALL                  0     /* Clear out all the setup frame */
DECL|macro|PHYS_ADDR_ONLY
mdefine_line|#define PHYS_ADDR_ONLY       1     /* Update the physical address only */
multiline_comment|/*&n;** Booleans&n;*/
DECL|macro|NO
mdefine_line|#define NO                   0
DECL|macro|FALSE
mdefine_line|#define FALSE                0
DECL|macro|CLOSED
mdefine_line|#define CLOSED               0
DECL|macro|YES
mdefine_line|#define YES                  ~0
DECL|macro|TRUE
mdefine_line|#define TRUE                 ~0
DECL|macro|OPEN
mdefine_line|#define OPEN                 ~0
multiline_comment|/*&n;** IEEE OUIs for various PHY vendor/chip combos - Reg 2 values only. Since&n;** the vendors seem split 50-50 on how to calculate the OUI register values&n;** anyway, just reading Reg2 seems reasonable for now [see de4x5_get_oui()].&n;*/
DECL|macro|NATIONAL_TX
mdefine_line|#define NATIONAL_TX 0x2000
DECL|macro|BROADCOM_T4
mdefine_line|#define BROADCOM_T4 0x03e0
DECL|macro|SEEQ_T4
mdefine_line|#define SEEQ_T4     0x0016
DECL|macro|CYPRESS_T4
mdefine_line|#define CYPRESS_T4  0x0014
multiline_comment|/*&n;** Speed Selection stuff&n;*/
DECL|macro|SET_10Mb
mdefine_line|#define SET_10Mb {&bslash;&n;  if (lp-&gt;phy[lp-&gt;active].id) {&bslash;&n;    omr = inl(DE4X5_OMR) &amp; ~(OMR_TTM | OMR_PCS | OMR_SCR | OMR_FD);&bslash;&n;    if ((lp-&gt;tmp != MII_SR_ASSC) || (lp-&gt;autosense != AUTO)) {&bslash;&n;      mii_wr(MII_CR_10|(de4x5_full_duplex?MII_CR_FDM:0), MII_CR, lp-&gt;phy[lp-&gt;active].addr, DE4X5_MII);&bslash;&n;    }&bslash;&n;    omr |= ((de4x5_full_duplex ? OMR_FD : 0) | OMR_TTM);&bslash;&n;    outl(omr, DE4X5_OMR);&bslash;&n;    outl(0, DE4X5_GEP);&bslash;&n;  } else {&bslash;&n;    omr = (inl(DE4X5_OMR) &amp; ~(OMR_PS | OMR_HBD | OMR_TTM | OMR_PCS | OMR_SCR | OMR_FD));&bslash;&n;    omr |= (de4x5_full_duplex ? OMR_FD : 0);&bslash;&n;    outl(omr | OMR_TTM, DE4X5_OMR);&bslash;&n;    outl((de4x5_full_duplex ? 0 : GEP_FDXD), DE4X5_GEP);&bslash;&n;  }&bslash;&n;}
DECL|macro|SET_100Mb
mdefine_line|#define SET_100Mb {&bslash;&n;  if (lp-&gt;phy[lp-&gt;active].id) {&bslash;&n;    int fdx=0;&bslash;&n;    if (lp-&gt;phy[lp-&gt;active].id == NATIONAL_TX) {&bslash;&n;        mii_wr(mii_rd(0x18, lp-&gt;phy[lp-&gt;active].addr, DE4X5_MII) &amp; ~0x2000,&bslash;&n;                      0x18, lp-&gt;phy[lp-&gt;active].addr, DE4X5_MII);&bslash;&n;    }&bslash;&n;    omr = inl(DE4X5_OMR) &amp; ~(OMR_TTM | OMR_PCS | OMR_SCR | OMR_FD);&bslash;&n;    sr = mii_rd(MII_SR, lp-&gt;phy[lp-&gt;active].addr, DE4X5_MII);&bslash;&n;    if (!(sr &amp; MII_ANA_T4AM) &amp;&amp; de4x5_full_duplex) fdx=1;&bslash;&n;    if ((lp-&gt;tmp != MII_SR_ASSC) || (lp-&gt;autosense != AUTO)) {&bslash;&n;      mii_wr(MII_CR_100|(fdx?MII_CR_FDM:0), MII_CR, lp-&gt;phy[lp-&gt;active].addr, DE4X5_MII);&bslash;&n;    }&bslash;&n;    if (fdx) omr |= OMR_FD;&bslash;&n;    outl(omr, DE4X5_OMR);&bslash;&n;  } else {&bslash;&n;    omr = (inl(DE4X5_OMR) &amp; ~(OMR_PS | OMR_HBD | OMR_TTM | OMR_PCS | OMR_SCR | OMR_FD));&bslash;&n;    omr |= (de4x5_full_duplex ? OMR_FD : 0);&bslash;&n;    outl(omr | OMR_PS | OMR_HBD | OMR_PCS | OMR_SCR, DE4X5_OMR);&bslash;&n;    outl((de4x5_full_duplex ? 0 : GEP_FDXD) | GEP_MODE, DE4X5_GEP);&bslash;&n;  }&bslash;&n;}
multiline_comment|/* FIX ME so I don&squot;t jam 10Mb networks */
DECL|macro|SET_100Mb_PDET
mdefine_line|#define SET_100Mb_PDET {&bslash;&n;  if (lp-&gt;phy[lp-&gt;active].id) {&bslash;&n;    mii_wr(MII_CR_100|MII_CR_ASSE, MII_CR, lp-&gt;phy[lp-&gt;active].addr, DE4X5_MII);&bslash;&n;    omr = (inl(DE4X5_OMR) &amp; ~(OMR_TTM | OMR_PCS | OMR_SCR | OMR_FD));&bslash;&n;    outl(omr, DE4X5_OMR);&bslash;&n;  } else {&bslash;&n;    omr = (inl(DE4X5_OMR) &amp; ~(OMR_PS | OMR_HBD | OMR_TTM | OMR_PCS | OMR_SCR | OMR_FD));&bslash;&n;    outl(omr | OMR_PS | OMR_HBD | OMR_PCS | OMR_SCR, DE4X5_OMR);&bslash;&n;    outl(GEP_FDXD | GEP_MODE, DE4X5_GEP);&bslash;&n;  }&bslash;&n;}
multiline_comment|/*&n;** Include the IOCTL stuff&n;*/
macro_line|#include &lt;linux/sockios.h&gt;
DECL|macro|DE4X5IOCTL
mdefine_line|#define&t;DE4X5IOCTL&t;SIOCDEVPRIVATE
DECL|struct|de4x5_ioctl
r_struct
id|de4x5_ioctl
(brace
DECL|member|cmd
r_int
r_int
id|cmd
suffix:semicolon
multiline_comment|/* Command to run */
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
multiline_comment|/* Length of the data buffer */
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
multiline_comment|/* Pointer to the data buffer */
)brace
suffix:semicolon
multiline_comment|/* &n;** Recognised commands for the driver &n;*/
DECL|macro|DE4X5_GET_HWADDR
mdefine_line|#define DE4X5_GET_HWADDR&t;0x01 /* Get the hardware address */
DECL|macro|DE4X5_SET_HWADDR
mdefine_line|#define DE4X5_SET_HWADDR&t;0x02 /* Get the hardware address */
DECL|macro|DE4X5_SET_PROM
mdefine_line|#define DE4X5_SET_PROM  &t;0x03 /* Set Promiscuous Mode */
DECL|macro|DE4X5_CLR_PROM
mdefine_line|#define DE4X5_CLR_PROM  &t;0x04 /* Clear Promiscuous Mode */
DECL|macro|DE4X5_SAY_BOO
mdefine_line|#define DE4X5_SAY_BOO&t;        0x05 /* Say &quot;Boo!&quot; to the kernel log file */
DECL|macro|DE4X5_GET_MCA
mdefine_line|#define DE4X5_GET_MCA   &t;0x06 /* Get a multicast address */
DECL|macro|DE4X5_SET_MCA
mdefine_line|#define DE4X5_SET_MCA   &t;0x07 /* Set a multicast address */
DECL|macro|DE4X5_CLR_MCA
mdefine_line|#define DE4X5_CLR_MCA    &t;0x08 /* Clear a multicast address */
DECL|macro|DE4X5_MCA_EN
mdefine_line|#define DE4X5_MCA_EN    &t;0x09 /* Enable a multicast address group */
DECL|macro|DE4X5_GET_STATS
mdefine_line|#define DE4X5_GET_STATS  &t;0x0a /* Get the driver statistics */
DECL|macro|DE4X5_CLR_STATS
mdefine_line|#define DE4X5_CLR_STATS &t;0x0b /* Zero out the driver statistics */
DECL|macro|DE4X5_GET_OMR
mdefine_line|#define DE4X5_GET_OMR           0x0c /* Get the OMR Register contents */
DECL|macro|DE4X5_SET_OMR
mdefine_line|#define DE4X5_SET_OMR           0x0d /* Set the OMR Register contents */
DECL|macro|DE4X5_GET_REG
mdefine_line|#define DE4X5_GET_REG           0x0e /* Get the DE4X5 Registers */
eof
