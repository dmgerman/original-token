multiline_comment|/*&n; * PCI defines and function prototypes&n; * Copyright 1994, Drew Eckhardt&n; *&n; * For more information, please consult &n; * &n; * PCI BIOS Specification Revision&n; * PCI Local Bus Specification&n; * PCI System Design Guide&n; *&n; * PCI Special Interest Group&n; * M/S HF3-15A&n; * 5200 N.E. Elam Young Parkway&n; * Hillsboro, Oregon 97124-6497&n; * +1 (503) 696-2000 &n; * +1 (800) 433-5177&n; * &n; * Manuals are $25 each or $50 for all three, plus $7 shipping &n; * within the United States, $35 abroad.&n; */
macro_line|#ifndef PCI_H
DECL|macro|PCI_H
mdefine_line|#define PCI_H
multiline_comment|/* Configuration method #1 */
DECL|macro|PCI_CONFIG1_ADDRESS_REG
mdefine_line|#define PCI_CONFIG1_ADDRESS_REG  0xcf8
DECL|macro|PCI_CONFIG1_ENABLE
mdefine_line|#define PCI_CONFIG1_ENABLE 0x80000000
DECL|macro|PCI_CONFIG1_TUPPLE
mdefine_line|#define PCI_CONFIG1_TUPPLE (bus, device, function, register)&t;&bslash;&n;        (PCI_CONFIG1_ENABLE | ((bus) &lt;&lt; 16) &amp; 0xff0000 |&t;&bslash;&n;        ((device) &lt;&lt; 11) &amp; 0xf800 | ((function) &lt;&lt; 8) &amp; 0x700 | &bslash;&n;        ((register) &lt;&lt; 2) &amp; 0xfc)
DECL|macro|PCI_CONFIG1_DATA_REG
mdefine_line|#define PCI_CONFIG1_DATA_REG     0xcfc
multiline_comment|/* Configuration method #2, deprecated */
DECL|macro|PCI_CONFIG2_ENABLE_REG
mdefine_line|#define PCI_CONFIG2_ENABLE_REG&t;0xcf8
DECL|macro|PCI_CONFIG2_ENABLE
mdefine_line|#define PCI_CONFIG2_ENABLE&t;0xf0
DECL|macro|PCI_CONFIG2_TUPPLE
mdefine_line|#define PCI_CONFIG2_TUPPLE (function)&t;&t;&t;&t;&bslash;&n;&t;(PCI_CONFIG2_ENABLE | ((function) &lt;&lt; 1) &amp; 0xe)
DECL|macro|PCI_CONFIG2_FORWARD_REG
mdefine_line|#define PCI_CONFIG2_FORWARD_REG&t;0xcfa
multiline_comment|/*&n; * Under PCI, each device has 256 bytes of configuration address space,&n; * of which the first 64 bytes is standardized as follows : &n; */
DECL|macro|PCI_VENDOR_ID
mdefine_line|#define PCI_VENDOR_ID&t;&t;0x00&t;/* 16 bits */
DECL|macro|PCI_DEVICE_ID
mdefine_line|#define PCI_DEVICE_ID&t;&t;0x02&t;/* 16 bits */
DECL|macro|PCI_COMMAND
mdefine_line|#define PCI_COMMAND&t;&t;0x04&t;/* 16 bits */
DECL|macro|PCI_COMMAND_IO
mdefine_line|#define  PCI_COMMAND_IO&t;&t;0x1&t;/* Enable response in I/O space */
DECL|macro|PCI_COMMAND_MEMORY
mdefine_line|#define  PCI_COMMAND_MEMORY&t;0x2&t;/* Enable response in I/O space */
DECL|macro|PCI_COMMAND_MASTER
mdefine_line|#define  PCI_COMMAND_MASTER&t;0x4&t;/* Enable bus mastering */
DECL|macro|PCI_COMMAND_SPECIAL
mdefine_line|#define  PCI_COMMAND_SPECIAL&t;0x8&t;/* Enable response to special cycles */
DECL|macro|PCI_COMMAND_INVALIDATE
mdefine_line|#define  PCI_COMMAND_INVALIDATE&t;0x10&t;/* Use memory write and invalidate */
DECL|macro|PCI_COMMAND_VGA_PALETTE
mdefine_line|#define  PCI_COMMAND_VGA_PALETTE&t;0x20&t;/* Enable palette snooping */
DECL|macro|PCI_COMMAND_PARITY
mdefine_line|#define  PCI_COMMAND_PARITY&t;0x40&t;/* Enable parity checking */
DECL|macro|PCI_COMMAND_WAIT
mdefine_line|#define  PCI_COMMAND_WAIT &t;0x80&t;/* Enable address/data stepping */
DECL|macro|PCI_COMMAND_SERR
mdefine_line|#define  PCI_COMMAND_SERR&t;0x100&t;/* Enable SERR */
DECL|macro|PCI_COMMAND_FAST_BACK
mdefine_line|#define  PCI_COMMAND_FAST_BACK&t;0x200&t;/* Enable back-to-back writes */
DECL|macro|PCI_STATUS
mdefine_line|#define PCI_STATUS&t;&t;0x06&t;/* 16 bits */
DECL|macro|PCI_STATUS_FAST_BACK
mdefine_line|#define  PCI_STATUS_FAST_BACK&t;0x80&t;/* Accept fast-back to back */
DECL|macro|PCI_STATUS_PARITY
mdefine_line|#define  PCI_STATUS_PARITY&t;0x100&t;/* Detected parity error */
DECL|macro|PCI_STATUS_DEVSEL_MASK
mdefine_line|#define  PCI_STATUS_DEVSEL_MASK&t;0x600&t;/* DEVSEL timing */
DECL|macro|PCI_STATUS_DEVSEL_FAST
mdefine_line|#define  PCI_STATUS_DEVSEL_FAST&t;0x000&t;
DECL|macro|PCI_STATUS_DEVSEL_MEDIUM
mdefine_line|#define  PCI_STATUS_DEVSEL_MEDIUM 0x200
DECL|macro|PCI_STATUS_DEVESEL_SLOW
mdefine_line|#define  PCI_STATUS_DEVESEL_SLOW 0x400
DECL|macro|PCI_STATUS_SIG_TARGET_ABORT
mdefine_line|#define  PCI_STATUS_SIG_TARGET_ABORT 0x800 /* Set on target abort */
DECL|macro|PCI_STATUS_REC_TARGET_ABORT
mdefine_line|#define  PCI_STATUS_REC_TARGET_ABORT 0x1000 /* Master ack of &quot; */
DECL|macro|PCI_STATUS_REC_MASTER_ABORT
mdefine_line|#define  PCI_STATUS_REC_MASTER_ABORT 0x2000 /* Set on master abort */
DECL|macro|PCI_STATUS_SIG_SYSTEM_ERROR
mdefine_line|#define  PCI_STATUS_SIG_SYSTEM_ERROR 0x4000 /* Set when we drive SERR */
DECL|macro|PCI_STATUS_DETECTED_PARITY
mdefine_line|#define  PCI_STATUS_DETECTED_PARITY 0x8000 /* Set on parity error */
DECL|macro|PCI_CLASS_REVISION
mdefine_line|#define PCI_CLASS_REVISION&t;0x08&t;/* High 24 bits are class, low 8&n;&t;&t;&t;&t;&t;   revision */
DECL|macro|PCI_REVISION_ID
mdefine_line|#define PCI_REVISION_ID         0x08    /* Revision ID */
DECL|macro|PCI_CLASS_PROG
mdefine_line|#define PCI_CLASS_PROG          0x09    /* Reg. Level Programming Interface */
DECL|macro|PCI_CLASS_DEVICE
mdefine_line|#define PCI_CLASS_DEVICE        0x0a    /* Device class */
DECL|macro|PCI_CACHE_LINE_SIZE
mdefine_line|#define PCI_CACHE_LINE_SIZE&t;0x0c&t;/* 8 bits */
DECL|macro|PCI_LATENCY_TIMER
mdefine_line|#define PCI_LATENCY_TIMER&t;0x0d&t;/* 8 bits */
DECL|macro|PCI_HEADER_TYPE
mdefine_line|#define PCI_HEADER_TYPE&t;&t;0x0e&t;/* 8 bits */
DECL|macro|PCI_BIST
mdefine_line|#define PCI_BIST&t;&t;0x0f&t;/* 8 bits */
DECL|macro|PCI_BIST_CODE_MASK
mdefine_line|#define PCI_BIST_CODE_MASK&t;0x0f&t;/* Return result */
DECL|macro|PCI_BIST_START
mdefine_line|#define PCI_BIST_START&t;&t;0x40&t;/* 1 to start BIST, 2 secs or less */
DECL|macro|PCI_BIST_CAPABLE
mdefine_line|#define PCI_BIST_CAPABLE&t;0x80&t;/* 1 if BIST capable */
multiline_comment|/*&n; * Base addresses specify locations in memory or I/O space.&n; * Decoded size can be determined by writing a value of &n; * 0xffffffff to the register, and reading it back.  Only &n; * 1 bits are decoded.&n; */
DECL|macro|PCI_BASE_ADDRESS_0
mdefine_line|#define PCI_BASE_ADDRESS_0&t;0x10&t;/* 32 bits */
DECL|macro|PCI_BASE_ADDRESS_1
mdefine_line|#define PCI_BASE_ADDRESS_1&t;0x14&t;/* 32 bits */
DECL|macro|PCI_BASE_ADDRESS_2
mdefine_line|#define PCI_BASE_ADDRESS_2&t;0x18&t;/* 32 bits */
DECL|macro|PCI_BASE_ADDRESS_3
mdefine_line|#define PCI_BASE_ADDRESS_3&t;0x1c&t;/* 32 bits */
DECL|macro|PCI_BASE_ADDRESS_4
mdefine_line|#define PCI_BASE_ADDRESS_4&t;0x20&t;/* 32 bits */
DECL|macro|PCI_BASE_ADDRESS_5
mdefine_line|#define PCI_BASE_ADDRESS_5&t;0x24&t;/* 32 bits */
DECL|macro|PCI_BASE_ADDRESS_SPACE
mdefine_line|#define  PCI_BASE_ADDRESS_SPACE&t;0x01&t;/* 0 = memory, 1 = I/O */
DECL|macro|PCI_BASE_ADDRESS_SPACE_IO
mdefine_line|#define  PCI_BASE_ADDRESS_SPACE_IO 0x01
DECL|macro|PCI_BASE_ADDRESS_SPACE_MEMORY
mdefine_line|#define  PCI_BASE_ADDRESS_SPACE_MEMORY 0x00
DECL|macro|PCI_BASE_ADDRESS_MEM_TYPE_MASK
mdefine_line|#define  PCI_BASE_ADDRESS_MEM_TYPE_MASK 0x06
DECL|macro|PCI_BASE_ADDRESS_MEM_TYPE_32
mdefine_line|#define  PCI_BASE_ADDRESS_MEM_TYPE_32&t;0x00&t;/* 32 bit address */
DECL|macro|PCI_BASE_ADDRESS_MEM_TYPE_1M
mdefine_line|#define  PCI_BASE_ADDRESS_MEM_TYPE_1M&t;0x02&t;/* Below 1M */
DECL|macro|PCI_BASE_ADDRESS_MEM_TYPE_64
mdefine_line|#define  PCI_BASE_ADDRESS_MEM_TYPE_64&t;0x04&t;/* 64 bit address */
DECL|macro|PCI_BASE_ADDRESS_MEM_MASK
mdefine_line|#define  PCI_BASE_ADDRESS_MEM_MASK&t;~7
DECL|macro|PCI_BASE_ADDRESS_IO_MASK
mdefine_line|#define  PCI_BASE_ADDRESS_IO_MASK&t;~3
multiline_comment|/* bit 1 is reserved if address_space = 1 */
multiline_comment|/* 0x28-0x2f are reserved */
DECL|macro|PCI_ROM_ADDRESS
mdefine_line|#define PCI_ROM_ADDRESS&t;&t;0x30&t;/* 32 bits */
DECL|macro|PCI_ROM_ADDRESS_ENABLE
mdefine_line|#define  PCI_ROM_ADDRESS_ENABLE&t;0x01&t;/* Write 1 to enable ROM,&n;&t;&t;&t;&t;&t;   bits 31..11 are address,&n;&t;&t;&t;&t;&t;   10..2 are reserved */
multiline_comment|/* 0x34-0x3b are reserved */
DECL|macro|PCI_INTERRUPT_LINE
mdefine_line|#define PCI_INTERRUPT_LINE&t;0x3c&t;/* 8 bits */
DECL|macro|PCI_INTERRUPT_PIN
mdefine_line|#define PCI_INTERRUPT_PIN&t;0x3d&t;/* 8 bits */
DECL|macro|PCI_MIN_GNT
mdefine_line|#define PCI_MIN_GNT&t;&t;0x3e&t;/* 8 bits */
DECL|macro|PCI_MAX_LAT
mdefine_line|#define PCI_MAX_LAT&t;&t;0x3f&t;/* 8 bits */
DECL|macro|PCI_CLASS_NOT_DEFINED
mdefine_line|#define PCI_CLASS_NOT_DEFINED&t;&t;0x0000
DECL|macro|PCI_CLASS_NOT_DEFINED_VGA
mdefine_line|#define PCI_CLASS_NOT_DEFINED_VGA&t;0x0001
DECL|macro|PCI_CLASS_STORAGE_SCSI
mdefine_line|#define PCI_CLASS_STORAGE_SCSI&t;&t;0x0100
DECL|macro|PCI_CLASS_STORAGE_IDE
mdefine_line|#define PCI_CLASS_STORAGE_IDE&t;&t;0x0101
DECL|macro|PCI_CLASS_STORAGE_FLOPPY
mdefine_line|#define PCI_CLASS_STORAGE_FLOPPY&t;0x0102
DECL|macro|PCI_CLASS_STORAGE_IPI
mdefine_line|#define PCI_CLASS_STORAGE_IPI&t;&t;0x0103
DECL|macro|PCI_CLASS_STORAGE_OTHER
mdefine_line|#define PCI_CLASS_STORAGE_OTHER&t;&t;0x0180
DECL|macro|PCI_CLASS_NETWORK_ETHERNET
mdefine_line|#define PCI_CLASS_NETWORK_ETHERNET&t;0x0200
DECL|macro|PCI_CLASS_NETWORK_TOKEN_RING
mdefine_line|#define PCI_CLASS_NETWORK_TOKEN_RING&t;0x0201
DECL|macro|PCI_CLASS_NETWORK_FDDI
mdefine_line|#define PCI_CLASS_NETWORK_FDDI&t;&t;0x0202
DECL|macro|PCI_CLASS_NETWORK_OTHER
mdefine_line|#define PCI_CLASS_NETWORK_OTHER&t;&t;0x0280
DECL|macro|PCI_CLASS_DISPLAY_VGA
mdefine_line|#define PCI_CLASS_DISPLAY_VGA&t;&t;0x0300
DECL|macro|PCI_CLASS_DISPLAY_XGA
mdefine_line|#define PCI_CLASS_DISPLAY_XGA&t;&t;0x0301
DECL|macro|PCI_CLASS_DISPLAY_OTHER
mdefine_line|#define PCI_CLASS_DISPLAY_OTHER&t;&t;0x0380
DECL|macro|PCI_CLASS_MULTIMEDIA_VIDEO
mdefine_line|#define PCI_CLASS_MULTIMEDIA_VIDEO&t;0x0400
DECL|macro|PCI_CLASS_MULTIMEDIA_AUDIO
mdefine_line|#define PCI_CLASS_MULTIMEDIA_AUDIO&t;0x0401
DECL|macro|PCI_CLASS_MULTIMEDIA_OTHER
mdefine_line|#define PCI_CLASS_MULTIMEDIA_OTHER&t;0x0480
DECL|macro|PCI_CLASS_MEMORY_RAM
mdefine_line|#define PCI_CLASS_MEMORY_RAM&t;&t;0x0500
DECL|macro|PCI_CLASS_MEMORY_FLASH
mdefine_line|#define PCI_CLASS_MEMORY_FLASH&t;&t;0x0501
DECL|macro|PCI_CLASS_MEMORY_OTHER
mdefine_line|#define PCI_CLASS_MEMORY_OTHER&t;&t;0x0580
DECL|macro|PCI_CLASS_BRIDGE_HOST
mdefine_line|#define PCI_CLASS_BRIDGE_HOST&t;&t;0x0600
DECL|macro|PCI_CLASS_BRIDGE_ISA
mdefine_line|#define PCI_CLASS_BRIDGE_ISA&t;&t;0x0601
DECL|macro|PCI_CLASS_BRIDGE_EISA
mdefine_line|#define PCI_CLASS_BRIDGE_EISA&t;&t;0x0602
DECL|macro|PCI_CLASS_BRIDGE_MC
mdefine_line|#define PCI_CLASS_BRIDGE_MC&t;&t;0x0603
DECL|macro|PCI_CLASS_BRIDGE_PCI
mdefine_line|#define PCI_CLASS_BRIDGE_PCI&t;&t;0x0604
DECL|macro|PCI_CLASS_BRIDGE_PCMCIA
mdefine_line|#define PCI_CLASS_BRIDGE_PCMCIA&t;&t;0x0605
DECL|macro|PCI_CLASS_BRIDGE_OTHER
mdefine_line|#define PCI_CLASS_BRIDGE_OTHER&t;&t;0x0680
DECL|macro|PCI_CLASS_OTHERS
mdefine_line|#define PCI_CLASS_OTHERS&t;&t;0xff
DECL|struct|pci_class_type
r_struct
id|pci_class_type
(brace
DECL|member|class_id
r_int
r_int
id|class_id
suffix:semicolon
DECL|member|class_name
r_char
op_star
id|class_name
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PCI_CLASS_NUM
mdefine_line|#define PCI_CLASS_NUM 28
DECL|macro|PCI_CLASS_TYPE
mdefine_line|#define PCI_CLASS_TYPE    { &bslash;&n;&t;{PCI_CLASS_NOT_DEFINED,&t;&t;&quot;Old unidentified device&quot;}, &bslash;&n;&t;{PCI_CLASS_NOT_DEFINED_VGA,&t;&quot;Old VGA controller&quot;}, &bslash;&n;&t;{PCI_CLASS_STORAGE_SCSI,&t;&quot;SCSI bus controller&quot;}, &bslash;&n;&t;{PCI_CLASS_STORAGE_IDE,&t;&t;&quot;IDE controller&quot;}, &bslash;&n;&t;{PCI_CLASS_STORAGE_FLOPPY,&t;&quot;Floppy controller&quot;}, &bslash;&n;&t;{PCI_CLASS_STORAGE_IPI,&t;&t;&quot;IPI bus controller&quot;}, &bslash;&n;&t;{PCI_CLASS_STORAGE_OTHER,&t;&quot;Unknown mass storage controller&quot;}, &bslash;&n;&t;{PCI_CLASS_NETWORK_ETHERNET,&t;&quot;Ethernet controller&quot;}, &bslash;&n;&t;{PCI_CLASS_NETWORK_TOKEN_RING,&t;&quot;Token ring controller&quot;}, &bslash;&n;&t;{PCI_CLASS_NETWORK_FDDI,&t;&quot;FDDI controller&quot;}, &bslash;&n;&t;{PCI_CLASS_NETWORK_OTHER,&t;&quot;Unknown network controller&quot;}, &bslash;&n;&t;{PCI_CLASS_DISPLAY_VGA,&t;&t;&quot;VGA display controller&quot;}, &bslash;&n;&t;{PCI_CLASS_DISPLAY_XGA,&t;&t;&quot;XGA display controller&quot;}, &bslash;&n;&t;{PCI_CLASS_DISPLAY_OTHER,&t;&quot;Unknown display controller&quot;}, &bslash;&n;&t;{PCI_CLASS_MULTIMEDIA_VIDEO,&t;&quot;Video device&quot;}, &bslash;&n;&t;{PCI_CLASS_MULTIMEDIA_AUDIO,&t;&quot;Audio device&quot;}, &bslash;&n;&t;{PCI_CLASS_MULTIMEDIA_OTHER,&t;&quot;Unknown multimedia device&quot;}, &bslash;&n;&t;{PCI_CLASS_MEMORY_RAM,&t;&t;&quot;RAM controller&quot;}, &bslash;&n;&t;{PCI_CLASS_MEMORY_FLASH,&t;&quot;FLASH controller&quot;}, &bslash;&n;&t;{PCI_CLASS_MEMORY_OTHER,&t;&quot;Unknown memory controller&quot;}, &bslash;&n;&t;{PCI_CLASS_BRIDGE_HOST,&t;&t;&quot;Host bridge&quot;}, &bslash;&n;&t;{PCI_CLASS_BRIDGE_ISA,&t;&t;&quot;ISA bridge&quot;}, &bslash;&n;&t;{PCI_CLASS_BRIDGE_EISA,&t;&t;&quot;EISA bridge&quot;}, &bslash;&n;&t;{PCI_CLASS_BRIDGE_MC,&t;&t;&quot;MC bridge&quot;}, &bslash;&n;&t;{PCI_CLASS_BRIDGE_PCI,&t;&t;&quot;PCI to PCI bridge&quot;}, &bslash;&n;&t;{PCI_CLASS_BRIDGE_PCMCIA,&t;&quot;PCMCIA bridge&quot;}, &bslash;&n;&t;{PCI_CLASS_BRIDGE_OTHER,&t;&quot;Unknown bridge device&quot;}, &bslash;&n;&t;{0,&t;&t;&t;&t;&quot;Unknown type of PCI device&quot;} &bslash;&n;}
DECL|macro|PCI_VENDOR_ID_NCR
mdefine_line|#define PCI_VENDOR_ID_NCR&t;&t;0x1000
DECL|macro|PCI_DEVICE_ID_NCR_53C810
mdefine_line|#define PCI_DEVICE_ID_NCR_53C810&t;0x0001
DECL|macro|PCI_DEVICE_ID_NCR_53C815
mdefine_line|#define PCI_DEVICE_ID_NCR_53C815&t;0x0004
DECL|macro|PCI_DEVICE_ID_NCR_53C820
mdefine_line|#define PCI_DEVICE_ID_NCR_53C820&t;0x0002
DECL|macro|PCI_DEVICE_ID_NCR_53C825
mdefine_line|#define PCI_DEVICE_ID_NCR_53C825&t;0x0003
DECL|macro|PCI_VENDOR_ID_ADAPTEC
mdefine_line|#define PCI_VENDOR_ID_ADAPTEC&t;&t;0x9004
DECL|macro|PCI_DEVICE_ID_ADAPTEC_2940
mdefine_line|#define PCI_DEVICE_ID_ADAPTEC_2940&t;0x7178
DECL|macro|PCI_VENDOR_ID_DPT
mdefine_line|#define PCI_VENDOR_ID_DPT               0x1044   
DECL|macro|PCI_DEVICE_ID_DPT
mdefine_line|#define PCI_DEVICE_ID_DPT               0xa400  
DECL|macro|PCI_VENDOR_ID_S3
mdefine_line|#define PCI_VENDOR_ID_S3&t;&t;0x5333
DECL|macro|PCI_DEVICE_ID_S3_864_1
mdefine_line|#define PCI_DEVICE_ID_S3_864_1&t;&t;0x88c0
DECL|macro|PCI_DEVICE_ID_S3_864_2
mdefine_line|#define PCI_DEVICE_ID_S3_864_2&t;&t;0x88c1
DECL|macro|PCI_DEVICE_ID_S3_928
mdefine_line|#define PCI_DEVICE_ID_S3_928&t;&t;0x88b0
DECL|macro|PCI_DEVICE_ID_S3_964
mdefine_line|#define PCI_DEVICE_ID_S3_964&t;&t;0x88d0
DECL|macro|PCI_DEVICE_ID_S3_811
mdefine_line|#define PCI_DEVICE_ID_S3_811&t;&t;0x8811
DECL|macro|PCI_VENDOR_ID_OPTI
mdefine_line|#define PCI_VENDOR_ID_OPTI&t;&t;0x1045
DECL|macro|PCI_DEVICE_ID_OPTI_82C822
mdefine_line|#define PCI_DEVICE_ID_OPTI_82C822&t;0xc822
DECL|macro|PCI_DEVICE_ID_OPTI_82C621
mdefine_line|#define PCI_DEVICE_ID_OPTI_82C621&t;0xc621
DECL|macro|PCI_VENDOR_ID_UMC
mdefine_line|#define PCI_VENDOR_ID_UMC&t;&t;0x1060
DECL|macro|PCI_DEVICE_ID_UMC_UM8881F
mdefine_line|#define PCI_DEVICE_ID_UMC_UM8881F&t;0x8881
DECL|macro|PCI_DEVICE_ID_UMC_UM8891A
mdefine_line|#define PCI_DEVICE_ID_UMC_UM8891A&t;0x0891
DECL|macro|PCI_DEVICE_ID_UMC_UM8886F
mdefine_line|#define PCI_DEVICE_ID_UMC_UM8886F&t;0x8886
DECL|macro|PCI_DEVICE_ID_UMC_UM8673F
mdefine_line|#define PCI_DEVICE_ID_UMC_UM8673F&t;0x0101
DECL|macro|PCI_VENDOR_ID_DEC
mdefine_line|#define PCI_VENDOR_ID_DEC&t;&t;0x1011
DECL|macro|PCI_DEVICE_ID_DEC_TULIP
mdefine_line|#define PCI_DEVICE_ID_DEC_TULIP&t;&t;0x0002
DECL|macro|PCI_DEVICE_ID_DEC_TULIP_FAST
mdefine_line|#define PCI_DEVICE_ID_DEC_TULIP_FAST&t;0x0009
DECL|macro|PCI_DEVICE_ID_DEC_FDDI
mdefine_line|#define PCI_DEVICE_ID_DEC_FDDI&t;&t;0x000F
DECL|macro|PCI_VENDOR_ID_MATROX
mdefine_line|#define PCI_VENDOR_ID_MATROX&t;&t;0x102B
DECL|macro|PCI_VENDOR_ID_INTEL
mdefine_line|#define PCI_VENDOR_ID_INTEL&t;&t;0x8086
DECL|macro|PCI_DEVICE_ID_INTEL_82378
mdefine_line|#define PCI_DEVICE_ID_INTEL_82378&t;0x0484
DECL|macro|PCI_DEVICE_ID_INTEL_82424
mdefine_line|#define PCI_DEVICE_ID_INTEL_82424&t;0x0483
DECL|macro|PCI_DEVICE_ID_INTEL_82375
mdefine_line|#define PCI_DEVICE_ID_INTEL_82375&t;0x0482
DECL|macro|PCI_DEVICE_ID_INTEL_82434
mdefine_line|#define PCI_DEVICE_ID_INTEL_82434&t;0x04a3
DECL|macro|PCI_DEVICE_ID_INTEL_82430
mdefine_line|#define PCI_DEVICE_ID_INTEL_82430&t;0x0486
DECL|macro|PCI_VENDOR_ID_SMC
mdefine_line|#define PCI_VENDOR_ID_SMC&t;&t;0x1042
DECL|macro|PCI_DEVICE_ID_SMC_37C665
mdefine_line|#define PCI_DEVICE_ID_SMC_37C665&t;0x1000
DECL|macro|PCI_VENDOR_ID_ATI
mdefine_line|#define PCI_VENDOR_ID_ATI&t;&t;0x1002
DECL|macro|PCI_DEVICE_ID_ATI_M32
mdefine_line|#define PCI_DEVICE_ID_ATI_M32&t;&t;0x4158
DECL|macro|PCI_DEVICE_ID_ATI_M64
mdefine_line|#define PCI_DEVICE_ID_ATI_M64&t;&t;0x4758
DECL|macro|PCI_VENDOR_ID_WEITEK
mdefine_line|#define PCI_VENDOR_ID_WEITEK&t;&t;0x100e
DECL|macro|PCI_DEVICE_ID_WEITEK_P9000
mdefine_line|#define PCI_DEVICE_ID_WEITEK_P9000&t;0x9001
DECL|macro|PCI_DEVICE_ID_WEITEK_P9100
mdefine_line|#define PCI_DEVICE_ID_WEITEK_P9100&t;0x9100
DECL|macro|PCI_VENDOR_ID_CIRRUS
mdefine_line|#define PCI_VENDOR_ID_CIRRUS&t;&t;0x1013
DECL|macro|PCI_DEVICE_ID_CIRRUS_5434_4
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_5434_4&t;0x00A4
DECL|macro|PCI_DEVICE_ID_CIRRUS_5434_8
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_5434_8&t;0x00A8
DECL|macro|PCI_DEVICE_ID_CIRRUS_6729
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_6729&t;0x1100
DECL|macro|PCI_VENDOR_ID_BUSLOGIC
mdefine_line|#define PCI_VENDOR_ID_BUSLOGIC&t;&t;0x104B
DECL|macro|PCI_DEVICE_ID_BUSLOGIC_946C
mdefine_line|#define PCI_DEVICE_ID_BUSLOGIC_946C&t;0x0140
DECL|macro|PCI_VENDOR_ID_N9
mdefine_line|#define PCI_VENDOR_ID_N9&t;&t;0x105D
DECL|macro|PCI_DEVICE_ID_N9_I128
mdefine_line|#define PCI_DEVICE_ID_N9_I128&t;&t;0x2309
DECL|macro|PCI_VENDOR_ID_ALI
mdefine_line|#define PCI_VENDOR_ID_ALI&t;&t;0x1025
DECL|macro|PCI_DEVICE_ID_ALI_M1435
mdefine_line|#define PCI_DEVICE_ID_ALI_M1435&t;&t;0x1435
DECL|macro|PCI_VENDOR_ID_TSENG
mdefine_line|#define PCI_VENDOR_ID_TSENG&t;&t;0x100c
DECL|macro|PCI_DEVICE_ID_TSENG_W32P_2
mdefine_line|#define PCI_DEVICE_ID_TSENG_W32P_2&t;0x3202
DECL|macro|PCI_DEVICE_ID_TSENG_W32P_5
mdefine_line|#define PCI_DEVICE_ID_TSENG_W32P_5&t;0x3205
DECL|macro|PCI_VENDOR_ID_CMD
mdefine_line|#define PCI_VENDOR_ID_CMD&t;&t;0x1095
DECL|macro|PCI_DEVICE_ID_CMD_640
mdefine_line|#define PCI_DEVICE_ID_CMD_640&t;&t;0x0640
DECL|macro|PCI_VENDOR_ID_VISION
mdefine_line|#define PCI_VENDOR_ID_VISION&t;&t;0x1098
DECL|macro|PCI_DEVICE_ID_VISION_QD8500
mdefine_line|#define PCI_DEVICE_ID_VISION_QD8500&t;0x0001
DECL|macro|PCI_VENDOR_ID_AMD
mdefine_line|#define PCI_VENDOR_ID_AMD&t;&t;0x1022
DECL|macro|PCI_DEVICE_ID_AMD_LANCE
mdefine_line|#define PCI_DEVICE_ID_AMD_LANCE&t;&t;0x2000
DECL|macro|PCI_VENDOR_ID_VLSI
mdefine_line|#define PCI_VENDOR_ID_VLSI&t;&t;0x1004
DECL|macro|PCI_DEVICE_ID_VLSI_82C593
mdefine_line|#define PCI_DEVICE_ID_VLSI_82C593&t;0x0006
DECL|macro|PCI_VENDOR_ID_AL
mdefine_line|#define PCI_VENDOR_ID_AL&t;&t;0x1005
DECL|macro|PCI_DEVICE_ID_AL_2301
mdefine_line|#define PCI_DEVICE_ID_AL_2301&t;&t;0x2301
DECL|macro|PCI_VENDOR_ID_SYMPHONY
mdefine_line|#define PCI_VENDOR_ID_SYMPHONY&t;&t;0x1c1c
DECL|macro|PCI_DEVICE_ID_SYMPHONY_101
mdefine_line|#define PCI_DEVICE_ID_SYMPHONY_101&t;0x0001
DECL|macro|PCI_VENDOR_ID_TRIDENT
mdefine_line|#define PCI_VENDOR_ID_TRIDENT&t;&t;0x1023
DECL|macro|PCI_DEVICE_ID_TRIDENT_9420
mdefine_line|#define PCI_DEVICE_ID_TRIDENT_9420&t;0x9420
DECL|struct|pci_vendor_type
r_struct
id|pci_vendor_type
(brace
DECL|member|vendor_id
r_int
r_int
id|vendor_id
suffix:semicolon
DECL|member|vendor_name
r_char
op_star
id|vendor_name
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PCI_VENDOR_NUM
mdefine_line|#define PCI_VENDOR_NUM 24
DECL|macro|PCI_VENDOR_TYPE
mdefine_line|#define PCI_VENDOR_TYPE { &bslash;&n;&t;{PCI_VENDOR_ID_NCR,&t;&t;&quot;NCR&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_ADAPTEC,&t;&t;&quot;Adaptec&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_DPT,&t;&t;&quot;DPT&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_S3,&t;&t;&quot;S3 Inc.&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_OPTI,&t;&t;&quot;OPTI&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_UMC,&t;&t;&quot;UMC&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_DEC,&t;&t;&quot;DEC&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_MATROX,&t;&t;&quot;Matrox&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_INTEL,&t;&t;&quot;Intel&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_SMC,&t;&t;&quot;SMC&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_ATI,&t;&t;&quot;ATI&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_WEITEK,&t;&t;&quot;Weitek&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_CIRRUS,&t;&t;&quot;Cirrus Logic&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_BUSLOGIC,&t;&quot;Bus Logic&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_N9,&t;&t;&quot;Number #9&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_ALI,&t;&t;&quot;ALI&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_TSENG,&t;&t;&quot;Tseng&squot;Lab&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_CMD,&t;&t;&quot;CMD&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_VISION,&t;&t;&quot;Vision&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_AMD,&t;&t;&quot;AMD&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_VLSI,&t;&t;&quot;VLSI&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_AL,&t;&t;&quot;Advance Logic&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_SYMPHONY,&t;&quot;Symphony&quot;}, &bslash;&n;&t;{PCI_VENDOR_ID_TRIDENT,&t;&t;&quot;Trident&quot;} &bslash;&n;}
multiline_comment|/* Optimisation pointer is a offset of an item into the array&t;&t;*/
multiline_comment|/* BRIDGE_MAPPING_TYPE. 0xff indicates that the device is not a PCI&t;*/
multiline_comment|/* bridge, or that we don&squot;t know for the moment how to configure it.&t;*/
multiline_comment|/* I&squot;m trying to do my best so that the kernel stays small.&t;&t;*/
multiline_comment|/* Different chipset can have same optimisation structure. i486 and&t;*/
multiline_comment|/* pentium chipsets from the same manufacturer usually have the same&t;*/
multiline_comment|/* structure &t;&t;&t;&t;&t;&t;&t;&t;*/
DECL|struct|pci_device_type
r_struct
id|pci_device_type
(brace
DECL|member|bridge_id
r_int
r_char
id|bridge_id
suffix:semicolon
DECL|member|vendor_id
r_int
r_int
id|vendor_id
suffix:semicolon
DECL|member|device_id
r_int
r_int
id|device_id
suffix:semicolon
DECL|member|device_name
r_char
op_star
id|device_name
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PCI_DEVICE_NUM
mdefine_line|#define PCI_DEVICE_NUM 45
DECL|macro|PCI_DEVICE_TYPE
mdefine_line|#define PCI_DEVICE_TYPE { &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_NCR,&t;PCI_DEVICE_ID_NCR_53C810,&t;&quot;53c810&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_NCR,&t;PCI_DEVICE_ID_NCR_53C815,&t;&quot;53c815&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_NCR,&t;PCI_DEVICE_ID_NCR_53C820,&t;&quot;53c820&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_NCR,&t;PCI_DEVICE_ID_NCR_53C825,&t;&quot;53c825&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_ADAPTEC,&t;PCI_DEVICE_ID_ADAPTEC_2940,&t;&quot;2940&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_DPT,&t;PCI_DEVICE_ID_DPT,&t;&t;&quot;SmartCache/Raid&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_S3,&t;PCI_DEVICE_ID_S3_864_1,&t;&t;&quot;Vision 864-P&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_S3,&t;PCI_DEVICE_ID_S3_864_2,&t;&t;&quot;Vision 864-P&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_S3,&t;PCI_DEVICE_ID_S3_928,&t;&t;&quot;Vision 928-P&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_S3,&t;PCI_DEVICE_ID_S3_964,&t;&t;&quot;Vision 964-P&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_S3,&t;PCI_DEVICE_ID_S3_811,&t;&t;&quot;Trio64&quot;}, &bslash;&n;&t;{0x02,&t;PCI_VENDOR_ID_OPTI,&t;PCI_DEVICE_ID_OPTI_82C822,&t;&quot;82C822&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_OPTI,&t;PCI_DEVICE_ID_OPTI_82C621,&t;&quot;82C621&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_UMC,&t;PCI_DEVICE_ID_UMC_UM8881F,&t;&quot;UM8881F&quot;}, &bslash;&n;&t;{0x01,&t;PCI_VENDOR_ID_UMC,&t;PCI_DEVICE_ID_UMC_UM8891A,&t;&quot;UM8891A&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_UMC,&t;PCI_DEVICE_ID_UMC_UM8886F,&t;&quot;UM8886F&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_UMC,&t;PCI_DEVICE_ID_UMC_UM8673F,&t;&quot;UM8673F&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_DEC,&t;PCI_DEVICE_ID_DEC_TULIP,&t;&quot;DC21040&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_DEC,&t;PCI_DEVICE_ID_DEC_TULIP_FAST,&t;&quot;DC21040&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_DEC,&t;PCI_DEVICE_ID_DEC_FDDI,&t;&t;&quot;DEFPA&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_INTEL,&t;PCI_DEVICE_ID_INTEL_82378,&t;&quot;82378IB&quot;}, &bslash;&n;&t;{0x00,&t;PCI_VENDOR_ID_INTEL,&t;PCI_DEVICE_ID_INTEL_82424,&t;&quot;82424ZX Saturn&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_INTEL,&t;PCI_DEVICE_ID_INTEL_82375,&t;&quot;82375EB&quot;}, &bslash;&n;&t;{0x00,&t;PCI_VENDOR_ID_INTEL,&t;PCI_DEVICE_ID_INTEL_82434,&t;&quot;82434LX Mercury/Neptune&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_INTEL,&t;PCI_DEVICE_ID_INTEL_82430,&t;&quot;82430ZX Aries&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_SMC,&t;PCI_DEVICE_ID_SMC_37C665,&t;&quot;FDC 37C665&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_ATI,&t;PCI_DEVICE_ID_ATI_M32,&t;&t;&quot;Mach 32&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_ATI,&t;PCI_DEVICE_ID_ATI_M64,&t;&t;&quot;Mach 64&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_WEITEK,&t;PCI_DEVICE_ID_WEITEK_P9000,&t;&quot;P9000&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_WEITEK,&t;PCI_DEVICE_ID_WEITEK_P9100,&t;&quot;P9100&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_CIRRUS,&t;PCI_DEVICE_ID_CIRRUS_5434_4,&t;&quot;GD 5434&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_CIRRUS,&t;PCI_DEVICE_ID_CIRRUS_5434_8,&t;&quot;GD 5434&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_CIRRUS,&t;PCI_DEVICE_ID_CIRRUS_6729,&t;&quot;CL 6729&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_BUSLOGIC,PCI_DEVICE_ID_BUSLOGIC_946C,&t;&quot;946C&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_N9,&t;PCI_DEVICE_ID_N9_I128,&t;&t;&quot;Imagine 128&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_ALI,&t;PCI_DEVICE_ID_ALI_M1435,&t;&quot;M1435&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_TSENG,&t;PCI_DEVICE_ID_TSENG_W32P_2,&t;&quot;ET4000W32P&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_TSENG,&t;PCI_DEVICE_ID_TSENG_W32P_5,&t;&quot;ET4000W32P&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_CMD,&t;PCI_DEVICE_ID_CMD_640,&t;&t;&quot;640A&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_VISION,&t;PCI_DEVICE_ID_VISION_QD8500,&t;&quot;QD-8500PCI&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_AMD,&t;PCI_DEVICE_ID_AMD_LANCE,&t;&quot;79C970&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_VLSI,&t;PCI_DEVICE_ID_VLSI_82C593,&t;&quot;82C593-FC1&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_AL,&t;PCI_DEVICE_ID_AL_2301,&t;&t;&quot;2301&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_SYMPHONY,&t;PCI_DEVICE_ID_SYMPHONY_101,&t;&quot;82C101&quot;}, &bslash;&n;&t;{0xff,&t;PCI_VENDOR_ID_TRIDENT,&t;PCI_DEVICE_ID_TRIDENT_9420,&t;&quot;TG 9420&quot;} &bslash;&n;}
multiline_comment|/* An item of this structure has the following meaning&t;*/
multiline_comment|/* For each optimisation, the register address, the mask&t;*/
multiline_comment|/* and value to write to turn it on.&t;&t;&t;*/
multiline_comment|/* There are 5 optimizations for the moment :&t;&t;*/
multiline_comment|/* Cache L2 write back best than write through&t;&t;*/
multiline_comment|/* Posted Write for CPU to PCI enable&t;&t;&t;*/
multiline_comment|/* Posted Write for CPU to MEMORY enable&t;&t;*/
multiline_comment|/* Posted Write for PCI to MEMORY enable&t;&t;*/
multiline_comment|/* PCI Burst enable&t;&t;&t;&t;&t;*/
multiline_comment|/* Half of the bios I&squot;ve meet don&squot;t allow you to turn&t;*/
multiline_comment|/* that on, and you can gain more than 15% on graphic&t;*/
multiline_comment|/* accesses using those optimisations...&t;&t;*/
DECL|struct|optimisation_type
r_struct
id|optimisation_type
(brace
DECL|member|type
r_char
op_star
id|type
suffix:semicolon
DECL|member|off
r_char
op_star
id|off
suffix:semicolon
DECL|member|on
r_char
op_star
id|on
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|OPTIMISATION_NUM
mdefine_line|#define OPTIMISATION_NUM 5
DECL|macro|OPTIMISATION_TYPE
mdefine_line|#define OPTIMISATION_TYPE { &bslash;&n;&t;{&quot;Cache L2&quot;,&quot;write trough&quot;,&quot;write back&quot;}, &bslash;&n;&t;{&quot;CPU-PCI posted write&quot;,&quot;off&quot;,&quot;on&quot;}, &bslash;&n;&t;{&quot;CPU-Memory posted write&quot;,&quot;off&quot;,&quot;on&quot;}, &bslash;&n;&t;{&quot;PCI-Memory posted write&quot;,&quot;off&quot;,&quot;on&quot;}, &bslash;&n;&t;{&quot;PCI burst&quot;,&quot;off&quot;,&quot;on&quot;} &bslash;&n;}
DECL|struct|bridge_mapping_type
r_struct
id|bridge_mapping_type
(brace
DECL|member|address
r_int
r_char
id|address
suffix:semicolon
DECL|member|mask
r_int
r_char
id|mask
suffix:semicolon
DECL|member|value
r_int
r_char
id|value
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Intel Neptune/Mercury/Saturn */
multiline_comment|/*&t;If the Internal cache is Write back,&t;*/
multiline_comment|/*&t;the L2 cache must be write through !&t;*/
multiline_comment|/*&t;I&squot;ve to check out how to control that&t;*/
multiline_comment|/*&t;for the moment, we won&squot;t touch the cache*/
multiline_comment|/* UMC 8891A Pentium chipset&t;&t;&t;*/
multiline_comment|/*&t;Why did you think UMC was cheaper ??&t;*/
multiline_comment|/* OPTI 82C822&t;&t;&t;&t;&t;*/
multiline_comment|/*&t;This is a dummy entry for my tests.&t;*/
multiline_comment|/*&t;I have this chipset and no docs....&t;*/
multiline_comment|/* I&squot;m gathering docs. If you can help......&t;*/
DECL|macro|BRIDGE_MAPPING_NUM
mdefine_line|#define BRIDGE_MAPPING_NUM 3
DECL|macro|BRIDGE_MAPPING_TYPE
mdefine_line|#define BRIDGE_MAPPING_TYPE { &bslash;&n;&t;{0x0&t;,0x02&t;,0x02&t;}, &bslash;&n;&t;{0x53&t;,0x02&t;,0x02&t;}, &bslash;&n;&t;{0x53&t;,0x01&t;,0x01&t;}, &bslash;&n;&t;{0x54&t;,0x01&t;,0x01&t;}, &bslash;&n;&t;{0x54&t;,0x02&t;,0x02&t;}, &bslash;&n;&bslash;&n;&t;{0x50&t;,0x10&t;,0x00&t;}, &bslash;&n;&t;{0x51&t;,0x40&t;,0x40&t;}, &bslash;&n;&t;{0x0&t;,0x0&t;,0x0&t;}, &bslash;&n;&t;{0x0&t;,0x0&t;,0x0&t;}, &bslash;&n;&t;{0x0&t;,0x0&t;,0x0&t;}, &bslash;&n;&bslash;&n;&t;{0x0&t;,0x1&t;,0x1&t;}, &bslash;&n;&t;{0x0&t;,0x2&t;,0x0&t;}, &bslash;&n;&t;{0x0&t;,0x0&t;,0x0&t;}, &bslash;&n;&t;{0x0&t;,0x0&t;,0x0&t;}, &bslash;&n;&t;{0x0&t;,0x0&t;,0x0&t;}  &bslash;&n;}
multiline_comment|/* PCI BIOS */
r_extern
r_int
id|pcibios_present
(paren
r_void
)paren
suffix:semicolon
DECL|macro|PCIBIOS_SUCCESSFUL
mdefine_line|#define PCIBIOS_SUCCESSFUL&t;&t;0x00
DECL|macro|PCIBIOS_FUNC_NOT_SUPPORTED
mdefine_line|#define PCIBIOS_FUNC_NOT_SUPPORTED&t;0x81
DECL|macro|PCIBIOS_BAD_VENDOR_ID
mdefine_line|#define PCIBIOS_BAD_VENDOR_ID&t;&t;0x83
DECL|macro|PCIBIOS_DEVICE_NOT_FOUND
mdefine_line|#define PCIBIOS_DEVICE_NOT_FOUND&t;0x86
DECL|macro|PCIBIOS_BAD_REGISTER_NUMBER
mdefine_line|#define PCIBIOS_BAD_REGISTER_NUMBER&t;0x87
multiline_comment|/*&n; * The PCIBIOS calls all bit-field the device_function variable such that &n; * the bit fielding matches that of the bl register used in the actual&n; * calls.&n; */
r_extern
r_int
id|pcibios_find_class
(paren
r_int
r_int
id|class_code
comma
r_int
r_int
id|index
comma
r_int
r_char
op_star
id|bus
comma
r_int
r_char
op_star
id|device_fn
)paren
suffix:semicolon
r_extern
r_int
id|pcibios_find_device
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device_id
comma
r_int
r_int
id|index
comma
r_int
r_char
op_star
id|bus
comma
r_int
r_char
op_star
id|device_fn
)paren
suffix:semicolon
r_extern
r_int
id|pcibios_read_config_byte
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|device_fn
comma
r_int
r_char
id|where
comma
r_int
r_char
op_star
id|value
)paren
suffix:semicolon
r_extern
r_int
id|pcibios_read_config_word
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|device_fn
comma
r_int
r_char
id|where
comma
r_int
r_int
op_star
id|value
)paren
suffix:semicolon
r_extern
r_int
id|pcibios_read_config_dword
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|device_fn
comma
r_int
r_char
id|where
comma
r_int
r_int
op_star
id|value
)paren
suffix:semicolon
r_extern
r_char
op_star
id|pcibios_strerror
(paren
r_int
id|error
)paren
suffix:semicolon
r_extern
r_int
id|pcibios_write_config_byte
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|device_fn
comma
r_int
r_char
id|where
comma
r_int
r_char
id|value
)paren
suffix:semicolon
r_extern
r_int
id|pcibios_write_config_word
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|device_fn
comma
r_int
r_char
id|where
comma
r_int
r_int
id|value
)paren
suffix:semicolon
r_extern
id|pcibios_write_config_dword
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|device_fn
comma
r_int
r_char
id|where
comma
r_int
r_int
id|value
)paren
suffix:semicolon
macro_line|#endif /* ndef PCI_H */
eof
