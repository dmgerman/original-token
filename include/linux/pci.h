multiline_comment|/*&n; * PCI defines and function prototypes&n; * Copyright 1994, Drew Eckhardt&n; *&n; * For more information, please consult &n; * &n; * PCI BIOS Specification Revision&n; * PCI Local Bus Specification&n; * PCI System Design Guide&n; *&n; * PCI Special Interest Group&n; * M/S HF3-15A&n; * 5200 N.E. Elam Young Parkway&n; * Hillsboro, Oregon 97124-6497&n; * +1 (503) 696-2000 &n; * +1 (800) 433-5177&n; * &n; * Manuals are $25 each or $50 for all three, plus $7 shipping &n; * within the United States, $35 abroad.&n; */
multiline_comment|/*&t;PROCEDURE TO REPORT NEW PCI DEVICES&n; * We are trying to collect information on new PCI devices, using&n; * the standard PCI identification procedure. If some warning is&n; * displayed at boot time, please report &n; *&t;- /proc/pci&n; *&t;- your exact hardware description. Try to find out&n; *&t;  which device is unknown. It may be you mainboard chipset.&n; *&t;  PCI-CPU bridge or PCI-ISA bridge.&n; *&t;- If you can&squot;t find the actual information in your hardware&n; *&t;  booklet, try to read the references of the chip on the board.&n; *&t;- Send all that to linux-pcisupport@cck.uni-kl.de&n; *&t;  and I&squot;ll add your device to the list as soon as possible&n; *&n; * BEFORE you send a mail, please check the latest linux releases&n; * to be sure it has not been recently added.&n; *&n; *        Thanks&n; *&t;&t;Jens Maurer&n; */
macro_line|#ifndef LINUX_PCI_H
DECL|macro|LINUX_PCI_H
mdefine_line|#define LINUX_PCI_H
multiline_comment|/*&n; * Under PCI, each device has 256 bytes of configuration address space,&n; * of which the first 64 bytes are standardized as follows:&n; */
DECL|macro|PCI_VENDOR_ID
mdefine_line|#define PCI_VENDOR_ID&t;&t;0x00&t;/* 16 bits */
DECL|macro|PCI_DEVICE_ID
mdefine_line|#define PCI_DEVICE_ID&t;&t;0x02&t;/* 16 bits */
DECL|macro|PCI_COMMAND
mdefine_line|#define PCI_COMMAND&t;&t;0x04&t;/* 16 bits */
DECL|macro|PCI_COMMAND_IO
mdefine_line|#define  PCI_COMMAND_IO&t;&t;0x1&t;/* Enable response in I/O space */
DECL|macro|PCI_COMMAND_MEMORY
mdefine_line|#define  PCI_COMMAND_MEMORY&t;0x2&t;/* Enable response in Memory space */
DECL|macro|PCI_COMMAND_MASTER
mdefine_line|#define  PCI_COMMAND_MASTER&t;0x4&t;/* Enable bus mastering */
DECL|macro|PCI_COMMAND_SPECIAL
mdefine_line|#define  PCI_COMMAND_SPECIAL&t;0x8&t;/* Enable response to special cycles */
DECL|macro|PCI_COMMAND_INVALIDATE
mdefine_line|#define  PCI_COMMAND_INVALIDATE&t;0x10&t;/* Use memory write and invalidate */
DECL|macro|PCI_COMMAND_VGA_PALETTE
mdefine_line|#define  PCI_COMMAND_VGA_PALETTE 0x20&t;/* Enable palette snooping */
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
DECL|macro|PCI_STATUS_66MHZ
mdefine_line|#define  PCI_STATUS_66MHZ&t;0x20&t;/* Support 66 Mhz PCI 2.1 bus */
DECL|macro|PCI_STATUS_UDF
mdefine_line|#define  PCI_STATUS_UDF&t;&t;0x40&t;/* Support User Definable Features */
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
DECL|macro|PCI_STATUS_DEVSEL_SLOW
mdefine_line|#define  PCI_STATUS_DEVSEL_SLOW 0x400
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
DECL|macro|PCI_BASE_ADDRESS_MEM_PREFETCH
mdefine_line|#define  PCI_BASE_ADDRESS_MEM_PREFETCH&t;0x08&t;/* prefetchable? */
DECL|macro|PCI_BASE_ADDRESS_MEM_MASK
mdefine_line|#define  PCI_BASE_ADDRESS_MEM_MASK&t;(~0x0f)
DECL|macro|PCI_BASE_ADDRESS_IO_MASK
mdefine_line|#define  PCI_BASE_ADDRESS_IO_MASK&t;(~0x03)
multiline_comment|/* bit 1 is reserved if address_space = 1 */
DECL|macro|PCI_CARDBUS_CIS
mdefine_line|#define PCI_CARDBUS_CIS&t;&t;0x28
DECL|macro|PCI_SUBSYSTEM_ID
mdefine_line|#define PCI_SUBSYSTEM_ID&t;0x2c
DECL|macro|PCI_SUBSYSTEM_VENDOR_ID
mdefine_line|#define PCI_SUBSYSTEM_VENDOR_ID&t;0x2e  
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
DECL|macro|PCI_BASE_CLASS_STORAGE
mdefine_line|#define PCI_BASE_CLASS_STORAGE&t;&t;0x01
DECL|macro|PCI_CLASS_STORAGE_SCSI
mdefine_line|#define PCI_CLASS_STORAGE_SCSI&t;&t;0x0100
DECL|macro|PCI_CLASS_STORAGE_IDE
mdefine_line|#define PCI_CLASS_STORAGE_IDE&t;&t;0x0101
DECL|macro|PCI_CLASS_STORAGE_FLOPPY
mdefine_line|#define PCI_CLASS_STORAGE_FLOPPY&t;0x0102
DECL|macro|PCI_CLASS_STORAGE_IPI
mdefine_line|#define PCI_CLASS_STORAGE_IPI&t;&t;0x0103
DECL|macro|PCI_CLASS_STORAGE_RAID
mdefine_line|#define PCI_CLASS_STORAGE_RAID&t;&t;0x0104
DECL|macro|PCI_CLASS_STORAGE_OTHER
mdefine_line|#define PCI_CLASS_STORAGE_OTHER&t;&t;0x0180
DECL|macro|PCI_BASE_CLASS_NETWORK
mdefine_line|#define PCI_BASE_CLASS_NETWORK&t;&t;0x02
DECL|macro|PCI_CLASS_NETWORK_ETHERNET
mdefine_line|#define PCI_CLASS_NETWORK_ETHERNET&t;0x0200
DECL|macro|PCI_CLASS_NETWORK_TOKEN_RING
mdefine_line|#define PCI_CLASS_NETWORK_TOKEN_RING&t;0x0201
DECL|macro|PCI_CLASS_NETWORK_FDDI
mdefine_line|#define PCI_CLASS_NETWORK_FDDI&t;&t;0x0202
DECL|macro|PCI_CLASS_NETWORK_ATM
mdefine_line|#define PCI_CLASS_NETWORK_ATM&t;&t;0x0203
DECL|macro|PCI_CLASS_NETWORK_OTHER
mdefine_line|#define PCI_CLASS_NETWORK_OTHER&t;&t;0x0280
DECL|macro|PCI_BASE_CLASS_DISPLAY
mdefine_line|#define PCI_BASE_CLASS_DISPLAY&t;&t;0x03
DECL|macro|PCI_CLASS_DISPLAY_VGA
mdefine_line|#define PCI_CLASS_DISPLAY_VGA&t;&t;0x0300
DECL|macro|PCI_CLASS_DISPLAY_XGA
mdefine_line|#define PCI_CLASS_DISPLAY_XGA&t;&t;0x0301
DECL|macro|PCI_CLASS_DISPLAY_OTHER
mdefine_line|#define PCI_CLASS_DISPLAY_OTHER&t;&t;0x0380
DECL|macro|PCI_BASE_CLASS_MULTIMEDIA
mdefine_line|#define PCI_BASE_CLASS_MULTIMEDIA&t;0x04
DECL|macro|PCI_CLASS_MULTIMEDIA_VIDEO
mdefine_line|#define PCI_CLASS_MULTIMEDIA_VIDEO&t;0x0400
DECL|macro|PCI_CLASS_MULTIMEDIA_AUDIO
mdefine_line|#define PCI_CLASS_MULTIMEDIA_AUDIO&t;0x0401
DECL|macro|PCI_CLASS_MULTIMEDIA_OTHER
mdefine_line|#define PCI_CLASS_MULTIMEDIA_OTHER&t;0x0480
DECL|macro|PCI_BASE_CLASS_MEMORY
mdefine_line|#define PCI_BASE_CLASS_MEMORY&t;&t;0x05
DECL|macro|PCI_CLASS_MEMORY_RAM
mdefine_line|#define  PCI_CLASS_MEMORY_RAM&t;&t;0x0500
DECL|macro|PCI_CLASS_MEMORY_FLASH
mdefine_line|#define  PCI_CLASS_MEMORY_FLASH&t;&t;0x0501
DECL|macro|PCI_CLASS_MEMORY_OTHER
mdefine_line|#define  PCI_CLASS_MEMORY_OTHER&t;&t;0x0580
DECL|macro|PCI_BASE_CLASS_BRIDGE
mdefine_line|#define PCI_BASE_CLASS_BRIDGE&t;&t;0x06
DECL|macro|PCI_CLASS_BRIDGE_HOST
mdefine_line|#define  PCI_CLASS_BRIDGE_HOST&t;&t;0x0600
DECL|macro|PCI_CLASS_BRIDGE_ISA
mdefine_line|#define  PCI_CLASS_BRIDGE_ISA&t;&t;0x0601
DECL|macro|PCI_CLASS_BRIDGE_EISA
mdefine_line|#define  PCI_CLASS_BRIDGE_EISA&t;&t;0x0602
DECL|macro|PCI_CLASS_BRIDGE_MC
mdefine_line|#define  PCI_CLASS_BRIDGE_MC&t;&t;0x0603
DECL|macro|PCI_CLASS_BRIDGE_PCI
mdefine_line|#define  PCI_CLASS_BRIDGE_PCI&t;&t;0x0604
DECL|macro|PCI_CLASS_BRIDGE_PCMCIA
mdefine_line|#define  PCI_CLASS_BRIDGE_PCMCIA&t;0x0605
DECL|macro|PCI_CLASS_BRIDGE_NUBUS
mdefine_line|#define  PCI_CLASS_BRIDGE_NUBUS&t;&t;0x0606
DECL|macro|PCI_CLASS_BRIDGE_CARDBUS
mdefine_line|#define  PCI_CLASS_BRIDGE_CARDBUS&t;0x0607
DECL|macro|PCI_CLASS_BRIDGE_OTHER
mdefine_line|#define  PCI_CLASS_BRIDGE_OTHER&t;&t;0x0680
DECL|macro|PCI_BASE_CLASS_COMMUNICATION
mdefine_line|#define PCI_BASE_CLASS_COMMUNICATION&t;0x07
DECL|macro|PCI_CLASS_COMMUNICATION_SERIAL
mdefine_line|#define PCI_CLASS_COMMUNICATION_SERIAL&t;0x0700
DECL|macro|PCI_CLASS_COMMUNICATION_PARALLEL
mdefine_line|#define PCI_CLASS_COMMUNICATION_PARALLEL 0x0701
DECL|macro|PCI_CLASS_COMMUNICATION_OTHER
mdefine_line|#define PCI_CLASS_COMMUNICATION_OTHER&t;0x0780
DECL|macro|PCI_BASE_CLASS_SYSTEM
mdefine_line|#define PCI_BASE_CLASS_SYSTEM&t;&t;0x08
DECL|macro|PCI_CLASS_SYSTEM_PIC
mdefine_line|#define PCI_CLASS_SYSTEM_PIC&t;&t;0x0800
DECL|macro|PCI_CLASS_SYSTEM_DMA
mdefine_line|#define PCI_CLASS_SYSTEM_DMA&t;&t;0x0801
DECL|macro|PCI_CLASS_SYSTEM_TIMER
mdefine_line|#define PCI_CLASS_SYSTEM_TIMER&t;&t;0x0802
DECL|macro|PCI_CLASS_SYSTEM_RTC
mdefine_line|#define PCI_CLASS_SYSTEM_RTC&t;&t;0x0803
DECL|macro|PCI_CLASS_SYSTEM_OTHER
mdefine_line|#define PCI_CLASS_SYSTEM_OTHER&t;&t;0x0880
DECL|macro|PCI_BASE_CLASS_INPUT
mdefine_line|#define PCI_BASE_CLASS_INPUT&t;&t;0x09
DECL|macro|PCI_CLASS_INPUT_KEYBOARD
mdefine_line|#define PCI_CLASS_INPUT_KEYBOARD&t;0x0900
DECL|macro|PCI_CLASS_INPUT_PEN
mdefine_line|#define PCI_CLASS_INPUT_PEN&t;&t;0x0901
DECL|macro|PCI_CLASS_INPUT_MOUSE
mdefine_line|#define PCI_CLASS_INPUT_MOUSE&t;&t;0x0902
DECL|macro|PCI_CLASS_INPUT_OTHER
mdefine_line|#define PCI_CLASS_INPUT_OTHER&t;&t;0x0980
DECL|macro|PCI_BASE_CLASS_DOCKING
mdefine_line|#define PCI_BASE_CLASS_DOCKING&t;&t;0x0a
DECL|macro|PCI_CLASS_DOCKING_GENERIC
mdefine_line|#define PCI_CLASS_DOCKING_GENERIC&t;0x0a00
DECL|macro|PCI_CLASS_DOCKING_OTHER
mdefine_line|#define PCI_CLASS_DOCKING_OTHER&t;&t;0x0a01
DECL|macro|PCI_BASE_CLASS_PROCESSOR
mdefine_line|#define PCI_BASE_CLASS_PROCESSOR&t;0x0b
DECL|macro|PCI_CLASS_PROCESSOR_386
mdefine_line|#define PCI_CLASS_PROCESSOR_386&t;&t;0x0b00
DECL|macro|PCI_CLASS_PROCESSOR_486
mdefine_line|#define PCI_CLASS_PROCESSOR_486&t;&t;0x0b01
DECL|macro|PCI_CLASS_PROCESSOR_PENTIUM
mdefine_line|#define PCI_CLASS_PROCESSOR_PENTIUM&t;0x0b02
DECL|macro|PCI_CLASS_PROCESSOR_ALPHA
mdefine_line|#define PCI_CLASS_PROCESSOR_ALPHA&t;0x0b10
DECL|macro|PCI_CLASS_PROCESSOR_POWERPC
mdefine_line|#define PCI_CLASS_PROCESSOR_POWERPC&t;0x0b20
DECL|macro|PCI_CLASS_PROCESSOR_CO
mdefine_line|#define PCI_CLASS_PROCESSOR_CO&t;&t;0x0b40
DECL|macro|PCI_BASE_CLASS_SERIAL
mdefine_line|#define PCI_BASE_CLASS_SERIAL&t;&t;0x0c
DECL|macro|PCI_CLASS_SERIAL_FIREWIRE
mdefine_line|#define PCI_CLASS_SERIAL_FIREWIRE&t;0x0c00
DECL|macro|PCI_CLASS_SERIAL_ACCESS
mdefine_line|#define PCI_CLASS_SERIAL_ACCESS&t;&t;0x0c01
DECL|macro|PCI_CLASS_SERIAL_SSA
mdefine_line|#define PCI_CLASS_SERIAL_SSA&t;&t;0x0c02
DECL|macro|PCI_CLASS_SERIAL_USB
mdefine_line|#define PCI_CLASS_SERIAL_USB&t;&t;0x0c03
DECL|macro|PCI_CLASS_SERIAL_FIBER
mdefine_line|#define PCI_CLASS_SERIAL_FIBER&t;&t;0x0c04
DECL|macro|PCI_CLASS_OTHERS
mdefine_line|#define PCI_CLASS_OTHERS&t;&t;0xff
multiline_comment|/*&n; * Vendor and card ID&squot;s: sort these numerically according to vendor&n; * (and according to card ID within vendor)&n; */
DECL|macro|PCI_VENDOR_ID_COMPAQ
mdefine_line|#define PCI_VENDOR_ID_COMPAQ&t;&t;0x0e11
DECL|macro|PCI_DEVICE_ID_COMPAQ_1280
mdefine_line|#define PCI_DEVICE_ID_COMPAQ_1280&t;0x3033
DECL|macro|PCI_DEVICE_ID_COMPAQ_SMART2P
mdefine_line|#define PCI_DEVICE_ID_COMPAQ_SMART2P&t;0xae10
DECL|macro|PCI_DEVICE_ID_COMPAQ_NETEL100
mdefine_line|#define PCI_DEVICE_ID_COMPAQ_NETEL100&t;0xae32
DECL|macro|PCI_DEVICE_ID_COMPAQ_NETEL10
mdefine_line|#define PCI_DEVICE_ID_COMPAQ_NETEL10&t;0xae34
DECL|macro|PCI_DEVICE_ID_COMPAQ_NETFLEX3I
mdefine_line|#define PCI_DEVICE_ID_COMPAQ_NETFLEX3I&t;0xae35
DECL|macro|PCI_DEVICE_ID_COMPAQ_NETEL100D
mdefine_line|#define PCI_DEVICE_ID_COMPAQ_NETEL100D&t;0xae40
DECL|macro|PCI_DEVICE_ID_COMPAQ_NETEL100PI
mdefine_line|#define PCI_DEVICE_ID_COMPAQ_NETEL100PI&t;0xae43
DECL|macro|PCI_DEVICE_ID_COMPAQ_NETEL100I
mdefine_line|#define PCI_DEVICE_ID_COMPAQ_NETEL100I&t;0xb011
DECL|macro|PCI_DEVICE_ID_COMPAQ_THUNDER
mdefine_line|#define PCI_DEVICE_ID_COMPAQ_THUNDER&t;0xf130
DECL|macro|PCI_DEVICE_ID_COMPAQ_NETFLEX3B
mdefine_line|#define PCI_DEVICE_ID_COMPAQ_NETFLEX3B&t;0xf150
DECL|macro|PCI_VENDOR_ID_NCR
mdefine_line|#define PCI_VENDOR_ID_NCR&t;&t;0x1000
DECL|macro|PCI_DEVICE_ID_NCR_53C810
mdefine_line|#define PCI_DEVICE_ID_NCR_53C810&t;0x0001
DECL|macro|PCI_DEVICE_ID_NCR_53C820
mdefine_line|#define PCI_DEVICE_ID_NCR_53C820&t;0x0002
DECL|macro|PCI_DEVICE_ID_NCR_53C825
mdefine_line|#define PCI_DEVICE_ID_NCR_53C825&t;0x0003
DECL|macro|PCI_DEVICE_ID_NCR_53C815
mdefine_line|#define PCI_DEVICE_ID_NCR_53C815&t;0x0004
DECL|macro|PCI_DEVICE_ID_NCR_53C860
mdefine_line|#define PCI_DEVICE_ID_NCR_53C860&t;0x0006
DECL|macro|PCI_DEVICE_ID_NCR_53C896
mdefine_line|#define PCI_DEVICE_ID_NCR_53C896&t;0x000b
DECL|macro|PCI_DEVICE_ID_NCR_53C895
mdefine_line|#define PCI_DEVICE_ID_NCR_53C895&t;0x000c
DECL|macro|PCI_DEVICE_ID_NCR_53C885
mdefine_line|#define PCI_DEVICE_ID_NCR_53C885&t;0x000d
DECL|macro|PCI_DEVICE_ID_NCR_53C875
mdefine_line|#define PCI_DEVICE_ID_NCR_53C875&t;0x000f
DECL|macro|PCI_DEVICE_ID_NCR_53C876
mdefine_line|#define PCI_DEVICE_ID_NCR_53C876&t;0x008f
DECL|macro|PCI_VENDOR_ID_ATI
mdefine_line|#define PCI_VENDOR_ID_ATI&t;&t;0x1002
DECL|macro|PCI_DEVICE_ID_ATI_68800
mdefine_line|#define PCI_DEVICE_ID_ATI_68800&t;&t;0x4158
DECL|macro|PCI_DEVICE_ID_ATI_215CT222
mdefine_line|#define PCI_DEVICE_ID_ATI_215CT222&t;0x4354
DECL|macro|PCI_DEVICE_ID_ATI_210888CX
mdefine_line|#define PCI_DEVICE_ID_ATI_210888CX&t;0x4358
DECL|macro|PCI_DEVICE_ID_ATI_215GB
mdefine_line|#define PCI_DEVICE_ID_ATI_215GB&t;&t;0x4742
DECL|macro|PCI_DEVICE_ID_ATI_215GP
mdefine_line|#define PCI_DEVICE_ID_ATI_215GP&t;&t;0x4750
DECL|macro|PCI_DEVICE_ID_ATI_215GT
mdefine_line|#define PCI_DEVICE_ID_ATI_215GT&t;&t;0x4754
DECL|macro|PCI_DEVICE_ID_ATI_215GTB
mdefine_line|#define PCI_DEVICE_ID_ATI_215GTB&t;0x4755
DECL|macro|PCI_DEVICE_ID_ATI_210888GX
mdefine_line|#define PCI_DEVICE_ID_ATI_210888GX&t;0x4758
DECL|macro|PCI_DEVICE_ID_ATI_264VT
mdefine_line|#define PCI_DEVICE_ID_ATI_264VT&t;&t;0x5654
DECL|macro|PCI_VENDOR_ID_VLSI
mdefine_line|#define PCI_VENDOR_ID_VLSI&t;&t;0x1004
DECL|macro|PCI_DEVICE_ID_VLSI_82C592
mdefine_line|#define PCI_DEVICE_ID_VLSI_82C592&t;0x0005
DECL|macro|PCI_DEVICE_ID_VLSI_82C593
mdefine_line|#define PCI_DEVICE_ID_VLSI_82C593&t;0x0006
DECL|macro|PCI_DEVICE_ID_VLSI_82C594
mdefine_line|#define PCI_DEVICE_ID_VLSI_82C594&t;0x0007
DECL|macro|PCI_DEVICE_ID_VLSI_82C597
mdefine_line|#define PCI_DEVICE_ID_VLSI_82C597&t;0x0009
DECL|macro|PCI_DEVICE_ID_VLSI_82C541
mdefine_line|#define PCI_DEVICE_ID_VLSI_82C541&t;0x000c
DECL|macro|PCI_DEVICE_ID_VLSI_82C543
mdefine_line|#define PCI_DEVICE_ID_VLSI_82C543&t;0x000d
DECL|macro|PCI_DEVICE_ID_VLSI_VAS96011
mdefine_line|#define PCI_DEVICE_ID_VLSI_VAS96011&t;0x0702
DECL|macro|PCI_VENDOR_ID_ADL
mdefine_line|#define PCI_VENDOR_ID_ADL&t;&t;0x1005
DECL|macro|PCI_DEVICE_ID_ADL_2301
mdefine_line|#define PCI_DEVICE_ID_ADL_2301&t;&t;0x2301
DECL|macro|PCI_VENDOR_ID_NS
mdefine_line|#define PCI_VENDOR_ID_NS&t;&t;0x100b
DECL|macro|PCI_DEVICE_ID_NS_87415
mdefine_line|#define PCI_DEVICE_ID_NS_87415&t;&t;0x0002
DECL|macro|PCI_DEVICE_ID_NS_87410
mdefine_line|#define PCI_DEVICE_ID_NS_87410&t;&t;0xd001
DECL|macro|PCI_VENDOR_ID_TSENG
mdefine_line|#define PCI_VENDOR_ID_TSENG&t;&t;0x100c
DECL|macro|PCI_DEVICE_ID_TSENG_W32P_2
mdefine_line|#define PCI_DEVICE_ID_TSENG_W32P_2&t;0x3202
DECL|macro|PCI_DEVICE_ID_TSENG_W32P_b
mdefine_line|#define PCI_DEVICE_ID_TSENG_W32P_b&t;0x3205
DECL|macro|PCI_DEVICE_ID_TSENG_W32P_c
mdefine_line|#define PCI_DEVICE_ID_TSENG_W32P_c&t;0x3206
DECL|macro|PCI_DEVICE_ID_TSENG_W32P_d
mdefine_line|#define PCI_DEVICE_ID_TSENG_W32P_d&t;0x3207
DECL|macro|PCI_DEVICE_ID_TSENG_ET6000
mdefine_line|#define PCI_DEVICE_ID_TSENG_ET6000&t;0x3208
DECL|macro|PCI_VENDOR_ID_WEITEK
mdefine_line|#define PCI_VENDOR_ID_WEITEK&t;&t;0x100e
DECL|macro|PCI_DEVICE_ID_WEITEK_P9000
mdefine_line|#define PCI_DEVICE_ID_WEITEK_P9000&t;0x9001
DECL|macro|PCI_DEVICE_ID_WEITEK_P9100
mdefine_line|#define PCI_DEVICE_ID_WEITEK_P9100&t;0x9100
DECL|macro|PCI_VENDOR_ID_DEC
mdefine_line|#define PCI_VENDOR_ID_DEC&t;&t;0x1011
DECL|macro|PCI_DEVICE_ID_DEC_BRD
mdefine_line|#define PCI_DEVICE_ID_DEC_BRD&t;&t;0x0001
DECL|macro|PCI_DEVICE_ID_DEC_TULIP
mdefine_line|#define PCI_DEVICE_ID_DEC_TULIP&t;&t;0x0002
DECL|macro|PCI_DEVICE_ID_DEC_TGA
mdefine_line|#define PCI_DEVICE_ID_DEC_TGA&t;&t;0x0004
DECL|macro|PCI_DEVICE_ID_DEC_TULIP_FAST
mdefine_line|#define PCI_DEVICE_ID_DEC_TULIP_FAST&t;0x0009
DECL|macro|PCI_DEVICE_ID_DEC_TGA2
mdefine_line|#define PCI_DEVICE_ID_DEC_TGA2&t;&t;0x000D
DECL|macro|PCI_DEVICE_ID_DEC_FDDI
mdefine_line|#define PCI_DEVICE_ID_DEC_FDDI&t;&t;0x000F
DECL|macro|PCI_DEVICE_ID_DEC_TULIP_PLUS
mdefine_line|#define PCI_DEVICE_ID_DEC_TULIP_PLUS&t;0x0014
DECL|macro|PCI_DEVICE_ID_DEC_21142
mdefine_line|#define PCI_DEVICE_ID_DEC_21142&t;&t;0x0019
DECL|macro|PCI_DEVICE_ID_DEC_21052
mdefine_line|#define PCI_DEVICE_ID_DEC_21052&t;&t;0x0021
DECL|macro|PCI_DEVICE_ID_DEC_21152
mdefine_line|#define PCI_DEVICE_ID_DEC_21152&t;&t;0x0024
DECL|macro|PCI_VENDOR_ID_CIRRUS
mdefine_line|#define PCI_VENDOR_ID_CIRRUS&t;&t;0x1013
DECL|macro|PCI_DEVICE_ID_CIRRUS_7548
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_7548&t;0x0038
DECL|macro|PCI_DEVICE_ID_CIRRUS_5430
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_5430&t;0x00a0
DECL|macro|PCI_DEVICE_ID_CIRRUS_5434_4
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_5434_4&t;0x00a4
DECL|macro|PCI_DEVICE_ID_CIRRUS_5434_8
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_5434_8&t;0x00a8
DECL|macro|PCI_DEVICE_ID_CIRRUS_5436
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_5436&t;0x00ac
DECL|macro|PCI_DEVICE_ID_CIRRUS_5446
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_5446&t;0x00b8
DECL|macro|PCI_DEVICE_ID_CIRRUS_5480
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_5480&t;0x00bc
DECL|macro|PCI_DEVICE_ID_CIRRUS_5464
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_5464&t;0x00d4
DECL|macro|PCI_DEVICE_ID_CIRRUS_5465
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_5465&t;0x00d6
DECL|macro|PCI_DEVICE_ID_CIRRUS_6729
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_6729&t;0x1100
DECL|macro|PCI_DEVICE_ID_CIRRUS_6832
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_6832&t;0x1110
DECL|macro|PCI_DEVICE_ID_CIRRUS_7542
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_7542&t;0x1200
DECL|macro|PCI_DEVICE_ID_CIRRUS_7543
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_7543&t;0x1202
DECL|macro|PCI_DEVICE_ID_CIRRUS_7541
mdefine_line|#define PCI_DEVICE_ID_CIRRUS_7541&t;0x1204
DECL|macro|PCI_VENDOR_ID_IBM
mdefine_line|#define PCI_VENDOR_ID_IBM&t;&t;0x1014
DECL|macro|PCI_DEVICE_ID_IBM_FIRE_CORAL
mdefine_line|#define PCI_DEVICE_ID_IBM_FIRE_CORAL&t;0x000a
DECL|macro|PCI_DEVICE_ID_IBM_TR
mdefine_line|#define PCI_DEVICE_ID_IBM_TR&t;&t;0x0018
DECL|macro|PCI_DEVICE_ID_IBM_82G2675
mdefine_line|#define PCI_DEVICE_ID_IBM_82G2675&t;0x001d
DECL|macro|PCI_DEVICE_ID_IBM_82351
mdefine_line|#define PCI_DEVICE_ID_IBM_82351&t;&t;0x0022
DECL|macro|PCI_VENDOR_ID_WD
mdefine_line|#define PCI_VENDOR_ID_WD&t;&t;0x101c
DECL|macro|PCI_DEVICE_ID_WD_7197
mdefine_line|#define PCI_DEVICE_ID_WD_7197&t;&t;0x3296
DECL|macro|PCI_VENDOR_ID_AMD
mdefine_line|#define PCI_VENDOR_ID_AMD&t;&t;0x1022
DECL|macro|PCI_DEVICE_ID_AMD_LANCE
mdefine_line|#define PCI_DEVICE_ID_AMD_LANCE&t;&t;0x2000
DECL|macro|PCI_DEVICE_ID_AMD_SCSI
mdefine_line|#define PCI_DEVICE_ID_AMD_SCSI&t;&t;0x2020
DECL|macro|PCI_VENDOR_ID_TRIDENT
mdefine_line|#define PCI_VENDOR_ID_TRIDENT&t;&t;0x1023
DECL|macro|PCI_DEVICE_ID_TRIDENT_9420
mdefine_line|#define PCI_DEVICE_ID_TRIDENT_9420&t;0x9420
DECL|macro|PCI_DEVICE_ID_TRIDENT_9440
mdefine_line|#define PCI_DEVICE_ID_TRIDENT_9440&t;0x9440
DECL|macro|PCI_DEVICE_ID_TRIDENT_9660
mdefine_line|#define PCI_DEVICE_ID_TRIDENT_9660&t;0x9660
DECL|macro|PCI_DEVICE_ID_TRIDENT_9750
mdefine_line|#define PCI_DEVICE_ID_TRIDENT_9750&t;0x9750
DECL|macro|PCI_VENDOR_ID_AI
mdefine_line|#define PCI_VENDOR_ID_AI&t;&t;0x1025
DECL|macro|PCI_DEVICE_ID_AI_M1435
mdefine_line|#define PCI_DEVICE_ID_AI_M1435&t;&t;0x1435
DECL|macro|PCI_VENDOR_ID_MATROX
mdefine_line|#define PCI_VENDOR_ID_MATROX&t;&t;0x102B
DECL|macro|PCI_DEVICE_ID_MATROX_MGA_2
mdefine_line|#define PCI_DEVICE_ID_MATROX_MGA_2&t;0x0518
DECL|macro|PCI_DEVICE_ID_MATROX_MIL
mdefine_line|#define PCI_DEVICE_ID_MATROX_MIL&t;0x0519
DECL|macro|PCI_DEVICE_ID_MATROX_MYS
mdefine_line|#define PCI_DEVICE_ID_MATROX_MYS&t;0x051A
DECL|macro|PCI_DEVICE_ID_MATROX_MIL_2
mdefine_line|#define PCI_DEVICE_ID_MATROX_MIL_2&t;0x051b
DECL|macro|PCI_DEVICE_ID_MATROX_MGA_IMP
mdefine_line|#define PCI_DEVICE_ID_MATROX_MGA_IMP&t;0x0d10
DECL|macro|PCI_VENDOR_ID_CT
mdefine_line|#define PCI_VENDOR_ID_CT&t;&t;0x102c
DECL|macro|PCI_DEVICE_ID_CT_65545
mdefine_line|#define PCI_DEVICE_ID_CT_65545&t;&t;0x00d8
DECL|macro|PCI_DEVICE_ID_CT_65548
mdefine_line|#define PCI_DEVICE_ID_CT_65548&t;&t;0x00dc
DECL|macro|PCI_DEVICE_ID_CT_65550
mdefine_line|#define PCI_DEVICE_ID_CT_65550&t;&t;0x00e0
DECL|macro|PCI_DEVICE_ID_CT_65554
mdefine_line|#define PCI_DEVICE_ID_CT_65554&t;&t;0x00e4
DECL|macro|PCI_VENDOR_ID_MIRO
mdefine_line|#define PCI_VENDOR_ID_MIRO&t;&t;0x1031
DECL|macro|PCI_DEVICE_ID_MIRO_36050
mdefine_line|#define PCI_DEVICE_ID_MIRO_36050&t;0x5601
DECL|macro|PCI_VENDOR_ID_NEC
mdefine_line|#define PCI_VENDOR_ID_NEC&t;&t;0x1033
DECL|macro|PCI_DEVICE_ID_NEC_PCX2
mdefine_line|#define PCI_DEVICE_ID_NEC_PCX2&t;&t;0x0046
DECL|macro|PCI_VENDOR_ID_FD
mdefine_line|#define PCI_VENDOR_ID_FD&t;&t;0x1036
DECL|macro|PCI_DEVICE_ID_FD_36C70
mdefine_line|#define PCI_DEVICE_ID_FD_36C70&t;&t;0x0000
DECL|macro|PCI_VENDOR_ID_SI
mdefine_line|#define PCI_VENDOR_ID_SI&t;&t;0x1039
DECL|macro|PCI_DEVICE_ID_SI_6201
mdefine_line|#define PCI_DEVICE_ID_SI_6201&t;&t;0x0001
DECL|macro|PCI_DEVICE_ID_SI_6202
mdefine_line|#define PCI_DEVICE_ID_SI_6202&t;&t;0x0002
DECL|macro|PCI_DEVICE_ID_SI_6205
mdefine_line|#define PCI_DEVICE_ID_SI_6205&t;&t;0x0205
DECL|macro|PCI_DEVICE_ID_SI_503
mdefine_line|#define PCI_DEVICE_ID_SI_503&t;&t;0x0008
DECL|macro|PCI_DEVICE_ID_SI_501
mdefine_line|#define PCI_DEVICE_ID_SI_501&t;&t;0x0406
DECL|macro|PCI_DEVICE_ID_SI_496
mdefine_line|#define PCI_DEVICE_ID_SI_496&t;&t;0x0496
DECL|macro|PCI_DEVICE_ID_SI_601
mdefine_line|#define PCI_DEVICE_ID_SI_601&t;&t;0x0601
DECL|macro|PCI_DEVICE_ID_SI_5107
mdefine_line|#define PCI_DEVICE_ID_SI_5107&t;&t;0x5107
DECL|macro|PCI_DEVICE_ID_SI_5511
mdefine_line|#define PCI_DEVICE_ID_SI_5511&t;&t;0x5511
DECL|macro|PCI_DEVICE_ID_SI_5513
mdefine_line|#define PCI_DEVICE_ID_SI_5513&t;&t;0x5513
DECL|macro|PCI_DEVICE_ID_SI_5571
mdefine_line|#define PCI_DEVICE_ID_SI_5571&t;&t;0x5571
DECL|macro|PCI_DEVICE_ID_SI_5597
mdefine_line|#define PCI_DEVICE_ID_SI_5597&t;&t;0x5597
DECL|macro|PCI_DEVICE_ID_SI_7001
mdefine_line|#define PCI_DEVICE_ID_SI_7001&t;&t;0x7001
DECL|macro|PCI_VENDOR_ID_HP
mdefine_line|#define PCI_VENDOR_ID_HP&t;&t;0x103c
DECL|macro|PCI_DEVICE_ID_HP_J2585A
mdefine_line|#define PCI_DEVICE_ID_HP_J2585A&t;&t;0x1030
DECL|macro|PCI_DEVICE_ID_HP_J2585B
mdefine_line|#define PCI_DEVICE_ID_HP_J2585B&t;&t;0x1031
DECL|macro|PCI_VENDOR_ID_HOLTEK
mdefine_line|#define PCI_VENDOR_ID_HOLTEK&t;&t;0x9412
DECL|macro|PCI_DEVICE_ID_HOLTEK_6565
mdefine_line|#define PCI_DEVICE_ID_HOLTEK_6565&t;0x6565
DECL|macro|PCI_VENDOR_ID_PCTECH
mdefine_line|#define PCI_VENDOR_ID_PCTECH&t;&t;0x1042
DECL|macro|PCI_DEVICE_ID_PCTECH_RZ1000
mdefine_line|#define PCI_DEVICE_ID_PCTECH_RZ1000&t;0x1000
DECL|macro|PCI_DEVICE_ID_PCTECH_RZ1001
mdefine_line|#define PCI_DEVICE_ID_PCTECH_RZ1001&t;0x1001
DECL|macro|PCI_VENDOR_ID_DPT
mdefine_line|#define PCI_VENDOR_ID_DPT               0x1044   
DECL|macro|PCI_DEVICE_ID_DPT
mdefine_line|#define PCI_DEVICE_ID_DPT               0xa400  
DECL|macro|PCI_VENDOR_ID_OPTI
mdefine_line|#define PCI_VENDOR_ID_OPTI&t;&t;0x1045
DECL|macro|PCI_DEVICE_ID_OPTI_92C178
mdefine_line|#define PCI_DEVICE_ID_OPTI_92C178&t;0xc178
DECL|macro|PCI_DEVICE_ID_OPTI_82C557
mdefine_line|#define PCI_DEVICE_ID_OPTI_82C557&t;0xc557
DECL|macro|PCI_DEVICE_ID_OPTI_82C558
mdefine_line|#define PCI_DEVICE_ID_OPTI_82C558&t;0xc558
DECL|macro|PCI_DEVICE_ID_OPTI_82C621
mdefine_line|#define PCI_DEVICE_ID_OPTI_82C621&t;0xc621
DECL|macro|PCI_DEVICE_ID_OPTI_82C700
mdefine_line|#define PCI_DEVICE_ID_OPTI_82C700&t;0xc700
DECL|macro|PCI_DEVICE_ID_OPTI_82C701
mdefine_line|#define PCI_DEVICE_ID_OPTI_82C701&t;0xc701
DECL|macro|PCI_DEVICE_ID_OPTI_82C814
mdefine_line|#define PCI_DEVICE_ID_OPTI_82C814&t;0xc814
DECL|macro|PCI_DEVICE_ID_OPTI_82C822
mdefine_line|#define PCI_DEVICE_ID_OPTI_82C822&t;0xc822
DECL|macro|PCI_VENDOR_ID_SGS
mdefine_line|#define PCI_VENDOR_ID_SGS&t;&t;0x104a
DECL|macro|PCI_DEVICE_ID_SGS_2000
mdefine_line|#define PCI_DEVICE_ID_SGS_2000&t;&t;0x0008
DECL|macro|PCI_DEVICE_ID_SGS_1764
mdefine_line|#define PCI_DEVICE_ID_SGS_1764&t;&t;0x0009
DECL|macro|PCI_VENDOR_ID_BUSLOGIC
mdefine_line|#define PCI_VENDOR_ID_BUSLOGIC&t;&t;      0x104B
DECL|macro|PCI_DEVICE_ID_BUSLOGIC_MULTIMASTER_NC
mdefine_line|#define PCI_DEVICE_ID_BUSLOGIC_MULTIMASTER_NC 0x0140
DECL|macro|PCI_DEVICE_ID_BUSLOGIC_MULTIMASTER
mdefine_line|#define PCI_DEVICE_ID_BUSLOGIC_MULTIMASTER    0x1040
DECL|macro|PCI_DEVICE_ID_BUSLOGIC_FLASHPOINT
mdefine_line|#define PCI_DEVICE_ID_BUSLOGIC_FLASHPOINT     0x8130
DECL|macro|PCI_VENDOR_ID_TI
mdefine_line|#define PCI_VENDOR_ID_TI&t;&t;0x104c
DECL|macro|PCI_DEVICE_ID_TI_TVP4010
mdefine_line|#define PCI_DEVICE_ID_TI_TVP4010&t;0x3d04
DECL|macro|PCI_DEVICE_ID_TI_TVP4020
mdefine_line|#define PCI_DEVICE_ID_TI_TVP4020&t;0x3d07
DECL|macro|PCI_DEVICE_ID_TI_PCI1130
mdefine_line|#define PCI_DEVICE_ID_TI_PCI1130&t;0xac12
DECL|macro|PCI_DEVICE_ID_TI_PCI1131
mdefine_line|#define PCI_DEVICE_ID_TI_PCI1131&t;0xac15
DECL|macro|PCI_VENDOR_ID_OAK
mdefine_line|#define PCI_VENDOR_ID_OAK&t;&t;0x104e
DECL|macro|PCI_DEVICE_ID_OAK_OTI107
mdefine_line|#define PCI_DEVICE_ID_OAK_OTI107&t;0x0107
multiline_comment|/* Winbond have two vendor IDs! See 0x10ad as well */
DECL|macro|PCI_VENDOR_ID_WINBOND2
mdefine_line|#define PCI_VENDOR_ID_WINBOND2&t;&t;0x1050
DECL|macro|PCI_DEVICE_ID_WINBOND2_89C940
mdefine_line|#define PCI_DEVICE_ID_WINBOND2_89C940&t;0x0940
DECL|macro|PCI_VENDOR_ID_MOTOROLA
mdefine_line|#define PCI_VENDOR_ID_MOTOROLA&t;&t;0x1057
DECL|macro|PCI_DEVICE_ID_MOTOROLA_MPC105
mdefine_line|#define PCI_DEVICE_ID_MOTOROLA_MPC105&t;0x0001
DECL|macro|PCI_DEVICE_ID_MOTOROLA_MPC106
mdefine_line|#define PCI_DEVICE_ID_MOTOROLA_MPC106&t;0x0002
DECL|macro|PCI_DEVICE_ID_MOTOROLA_RAVEN
mdefine_line|#define PCI_DEVICE_ID_MOTOROLA_RAVEN&t;0x4801
DECL|macro|PCI_VENDOR_ID_PROMISE
mdefine_line|#define PCI_VENDOR_ID_PROMISE&t;&t;0x105a
DECL|macro|PCI_DEVICE_ID_PROMISE_20246
mdefine_line|#define PCI_DEVICE_ID_PROMISE_20246&t;0x4d33
DECL|macro|PCI_DEVICE_ID_PROMISE_5300
mdefine_line|#define PCI_DEVICE_ID_PROMISE_5300&t;0x5300
DECL|macro|PCI_VENDOR_ID_N9
mdefine_line|#define PCI_VENDOR_ID_N9&t;&t;0x105d
DECL|macro|PCI_DEVICE_ID_N9_I128
mdefine_line|#define PCI_DEVICE_ID_N9_I128&t;&t;0x2309
DECL|macro|PCI_DEVICE_ID_N9_I128_2
mdefine_line|#define PCI_DEVICE_ID_N9_I128_2&t;&t;0x2339
DECL|macro|PCI_VENDOR_ID_UMC
mdefine_line|#define PCI_VENDOR_ID_UMC&t;&t;0x1060
DECL|macro|PCI_DEVICE_ID_UMC_UM8673F
mdefine_line|#define PCI_DEVICE_ID_UMC_UM8673F&t;0x0101
DECL|macro|PCI_DEVICE_ID_UMC_UM8891A
mdefine_line|#define PCI_DEVICE_ID_UMC_UM8891A&t;0x0891
DECL|macro|PCI_DEVICE_ID_UMC_UM8886BF
mdefine_line|#define PCI_DEVICE_ID_UMC_UM8886BF&t;0x673a
DECL|macro|PCI_DEVICE_ID_UMC_UM8886A
mdefine_line|#define PCI_DEVICE_ID_UMC_UM8886A&t;0x886a
DECL|macro|PCI_DEVICE_ID_UMC_UM8881F
mdefine_line|#define PCI_DEVICE_ID_UMC_UM8881F&t;0x8881
DECL|macro|PCI_DEVICE_ID_UMC_UM8886F
mdefine_line|#define PCI_DEVICE_ID_UMC_UM8886F&t;0x8886
DECL|macro|PCI_DEVICE_ID_UMC_UM9017F
mdefine_line|#define PCI_DEVICE_ID_UMC_UM9017F&t;0x9017
DECL|macro|PCI_DEVICE_ID_UMC_UM8886N
mdefine_line|#define PCI_DEVICE_ID_UMC_UM8886N&t;0xe886
DECL|macro|PCI_DEVICE_ID_UMC_UM8891N
mdefine_line|#define PCI_DEVICE_ID_UMC_UM8891N&t;0xe891
DECL|macro|PCI_VENDOR_ID_X
mdefine_line|#define PCI_VENDOR_ID_X&t;&t;&t;0x1061
DECL|macro|PCI_DEVICE_ID_X_AGX016
mdefine_line|#define PCI_DEVICE_ID_X_AGX016&t;&t;0x0001
DECL|macro|PCI_VENDOR_ID_PICOP
mdefine_line|#define PCI_VENDOR_ID_PICOP&t;&t;0x1066
DECL|macro|PCI_DEVICE_ID_PICOP_PT86C52X
mdefine_line|#define PCI_DEVICE_ID_PICOP_PT86C52X&t;0x0001
DECL|macro|PCI_VENDOR_ID_APPLE
mdefine_line|#define PCI_VENDOR_ID_APPLE&t;&t;0x106b
DECL|macro|PCI_DEVICE_ID_APPLE_BANDIT
mdefine_line|#define PCI_DEVICE_ID_APPLE_BANDIT&t;0x0001
DECL|macro|PCI_DEVICE_ID_APPLE_GC
mdefine_line|#define PCI_DEVICE_ID_APPLE_GC&t;&t;0x0002
DECL|macro|PCI_DEVICE_ID_APPLE_HYDRA
mdefine_line|#define PCI_DEVICE_ID_APPLE_HYDRA&t;0x000e
DECL|macro|PCI_VENDOR_ID_NEXGEN
mdefine_line|#define PCI_VENDOR_ID_NEXGEN&t;&t;0x1074
DECL|macro|PCI_DEVICE_ID_NEXGEN_82C501
mdefine_line|#define PCI_DEVICE_ID_NEXGEN_82C501&t;0x4e78
DECL|macro|PCI_VENDOR_ID_QLOGIC
mdefine_line|#define PCI_VENDOR_ID_QLOGIC&t;&t;0x1077
DECL|macro|PCI_DEVICE_ID_QLOGIC_ISP1020
mdefine_line|#define PCI_DEVICE_ID_QLOGIC_ISP1020&t;0x1020
DECL|macro|PCI_DEVICE_ID_QLOGIC_ISP1022
mdefine_line|#define PCI_DEVICE_ID_QLOGIC_ISP1022&t;0x1022
DECL|macro|PCI_VENDOR_ID_LEADTEK
mdefine_line|#define PCI_VENDOR_ID_LEADTEK&t;&t;0x107d
DECL|macro|PCI_DEVICE_ID_LEADTEK_805
mdefine_line|#define PCI_DEVICE_ID_LEADTEK_805&t;0x0000
DECL|macro|PCI_VENDOR_ID_CONTAQ
mdefine_line|#define PCI_VENDOR_ID_CONTAQ&t;&t;0x1080
DECL|macro|PCI_DEVICE_ID_CONTAQ_82C599
mdefine_line|#define PCI_DEVICE_ID_CONTAQ_82C599&t;0x0600
DECL|macro|PCI_VENDOR_ID_FOREX
mdefine_line|#define PCI_VENDOR_ID_FOREX&t;&t;0x1083
DECL|macro|PCI_VENDOR_ID_OLICOM
mdefine_line|#define PCI_VENDOR_ID_OLICOM&t;&t;0x108d
DECL|macro|PCI_DEVICE_ID_OLICOM_OC3136
mdefine_line|#define PCI_DEVICE_ID_OLICOM_OC3136&t;0x0001
DECL|macro|PCI_DEVICE_ID_OLICOM_OC2315
mdefine_line|#define PCI_DEVICE_ID_OLICOM_OC2315&t;0x0011
DECL|macro|PCI_DEVICE_ID_OLICOM_OC2325
mdefine_line|#define PCI_DEVICE_ID_OLICOM_OC2325&t;0x0012
DECL|macro|PCI_DEVICE_ID_OLICOM_OC2183
mdefine_line|#define PCI_DEVICE_ID_OLICOM_OC2183&t;0x0013
DECL|macro|PCI_DEVICE_ID_OLICOM_OC2326
mdefine_line|#define PCI_DEVICE_ID_OLICOM_OC2326&t;0x0014
DECL|macro|PCI_DEVICE_ID_OLICOM_OC6151
mdefine_line|#define PCI_DEVICE_ID_OLICOM_OC6151&t;0x0021
DECL|macro|PCI_VENDOR_ID_SUN
mdefine_line|#define PCI_VENDOR_ID_SUN&t;&t;0x108e
DECL|macro|PCI_DEVICE_ID_SUN_EBUS
mdefine_line|#define PCI_DEVICE_ID_SUN_EBUS&t;&t;0x1000
DECL|macro|PCI_DEVICE_ID_SUN_HAPPYMEAL
mdefine_line|#define PCI_DEVICE_ID_SUN_HAPPYMEAL&t;0x1001
DECL|macro|PCI_DEVICE_ID_SUN_PBM
mdefine_line|#define PCI_DEVICE_ID_SUN_PBM&t;&t;0x8000
DECL|macro|PCI_VENDOR_ID_CMD
mdefine_line|#define PCI_VENDOR_ID_CMD&t;&t;0x1095
DECL|macro|PCI_DEVICE_ID_CMD_640
mdefine_line|#define PCI_DEVICE_ID_CMD_640&t;&t;0x0640
DECL|macro|PCI_DEVICE_ID_CMD_643
mdefine_line|#define PCI_DEVICE_ID_CMD_643&t;&t;0x0643
DECL|macro|PCI_DEVICE_ID_CMD_646
mdefine_line|#define PCI_DEVICE_ID_CMD_646&t;&t;0x0646
DECL|macro|PCI_DEVICE_ID_CMD_670
mdefine_line|#define PCI_DEVICE_ID_CMD_670&t;&t;0x0670
DECL|macro|PCI_VENDOR_ID_VISION
mdefine_line|#define PCI_VENDOR_ID_VISION&t;&t;0x1098
DECL|macro|PCI_DEVICE_ID_VISION_QD8500
mdefine_line|#define PCI_DEVICE_ID_VISION_QD8500&t;0x0001
DECL|macro|PCI_DEVICE_ID_VISION_QD8580
mdefine_line|#define PCI_DEVICE_ID_VISION_QD8580&t;0x0002
DECL|macro|PCI_VENDOR_ID_BROOKTREE
mdefine_line|#define PCI_VENDOR_ID_BROOKTREE&t;&t;0x109e
DECL|macro|PCI_DEVICE_ID_BROOKTREE_848
mdefine_line|#define PCI_DEVICE_ID_BROOKTREE_848&t;0x0350
DECL|macro|PCI_VENDOR_ID_SIERRA
mdefine_line|#define PCI_VENDOR_ID_SIERRA&t;&t;0x10a8
DECL|macro|PCI_DEVICE_ID_SIERRA_STB
mdefine_line|#define PCI_DEVICE_ID_SIERRA_STB&t;0x0000
DECL|macro|PCI_VENDOR_ID_ACC
mdefine_line|#define PCI_VENDOR_ID_ACC&t;&t;0x10aa
DECL|macro|PCI_DEVICE_ID_ACC_2056
mdefine_line|#define PCI_DEVICE_ID_ACC_2056&t;&t;0x0000
DECL|macro|PCI_VENDOR_ID_WINBOND
mdefine_line|#define PCI_VENDOR_ID_WINBOND&t;&t;0x10ad
DECL|macro|PCI_DEVICE_ID_WINBOND_83769
mdefine_line|#define PCI_DEVICE_ID_WINBOND_83769&t;0x0001
DECL|macro|PCI_DEVICE_ID_WINBOND_82C105
mdefine_line|#define PCI_DEVICE_ID_WINBOND_82C105&t;0x0105
DECL|macro|PCI_DEVICE_ID_WINBOND_83C553
mdefine_line|#define PCI_DEVICE_ID_WINBOND_83C553&t;0x0565
DECL|macro|PCI_VENDOR_ID_DATABOOK
mdefine_line|#define PCI_VENDOR_ID_DATABOOK&t;&t;0x10b3
DECL|macro|PCI_DEVICE_ID_DATABOOK_87144
mdefine_line|#define PCI_DEVICE_ID_DATABOOK_87144&t;0xb106
DECL|macro|PCI_VENDOR_ID_3COM
mdefine_line|#define PCI_VENDOR_ID_3COM&t;&t;0x10b7
DECL|macro|PCI_DEVICE_ID_3COM_3C590
mdefine_line|#define PCI_DEVICE_ID_3COM_3C590&t;0x5900
DECL|macro|PCI_DEVICE_ID_3COM_3C595TX
mdefine_line|#define PCI_DEVICE_ID_3COM_3C595TX&t;0x5950
DECL|macro|PCI_DEVICE_ID_3COM_3C595T4
mdefine_line|#define PCI_DEVICE_ID_3COM_3C595T4&t;0x5951
DECL|macro|PCI_DEVICE_ID_3COM_3C595MII
mdefine_line|#define PCI_DEVICE_ID_3COM_3C595MII&t;0x5952
DECL|macro|PCI_DEVICE_ID_3COM_3C900TPO
mdefine_line|#define PCI_DEVICE_ID_3COM_3C900TPO&t;0x9000
DECL|macro|PCI_DEVICE_ID_3COM_3C900COMBO
mdefine_line|#define PCI_DEVICE_ID_3COM_3C900COMBO&t;0x9001
DECL|macro|PCI_DEVICE_ID_3COM_3C905TX
mdefine_line|#define PCI_DEVICE_ID_3COM_3C905TX&t;0x9050
DECL|macro|PCI_VENDOR_ID_SMC
mdefine_line|#define PCI_VENDOR_ID_SMC&t;&t;0x10b8
DECL|macro|PCI_DEVICE_ID_SMC_EPIC100
mdefine_line|#define PCI_DEVICE_ID_SMC_EPIC100&t;0x0005
DECL|macro|PCI_VENDOR_ID_AL
mdefine_line|#define PCI_VENDOR_ID_AL&t;&t;0x10b9
DECL|macro|PCI_DEVICE_ID_AL_M1445
mdefine_line|#define PCI_DEVICE_ID_AL_M1445&t;&t;0x1445
DECL|macro|PCI_DEVICE_ID_AL_M1449
mdefine_line|#define PCI_DEVICE_ID_AL_M1449&t;&t;0x1449
DECL|macro|PCI_DEVICE_ID_AL_M1451
mdefine_line|#define PCI_DEVICE_ID_AL_M1451&t;&t;0x1451
DECL|macro|PCI_DEVICE_ID_AL_M1461
mdefine_line|#define PCI_DEVICE_ID_AL_M1461&t;&t;0x1461
DECL|macro|PCI_DEVICE_ID_AL_M1489
mdefine_line|#define PCI_DEVICE_ID_AL_M1489&t;&t;0x1489
DECL|macro|PCI_DEVICE_ID_AL_M1511
mdefine_line|#define PCI_DEVICE_ID_AL_M1511&t;&t;0x1511
DECL|macro|PCI_DEVICE_ID_AL_M1513
mdefine_line|#define PCI_DEVICE_ID_AL_M1513&t;&t;0x1513
DECL|macro|PCI_DEVICE_ID_AL_M1521
mdefine_line|#define PCI_DEVICE_ID_AL_M1521&t;&t;0x1521
DECL|macro|PCI_DEVICE_ID_AL_M1523
mdefine_line|#define PCI_DEVICE_ID_AL_M1523&t;&t;0x1523
DECL|macro|PCI_DEVICE_ID_AL_M1531
mdefine_line|#define PCI_DEVICE_ID_AL_M1531&t;&t;0x1531
DECL|macro|PCI_DEVICE_ID_AL_M1533
mdefine_line|#define PCI_DEVICE_ID_AL_M1533&t;&t;0x1533
DECL|macro|PCI_DEVICE_ID_AL_M4803
mdefine_line|#define PCI_DEVICE_ID_AL_M4803&t;&t;0x5215
DECL|macro|PCI_DEVICE_ID_AL_M5219
mdefine_line|#define PCI_DEVICE_ID_AL_M5219&t;&t;0x5219
DECL|macro|PCI_DEVICE_ID_AL_M5229
mdefine_line|#define PCI_DEVICE_ID_AL_M5229&t;&t;0x5229
DECL|macro|PCI_VENDOR_ID_MITSUBISHI
mdefine_line|#define PCI_VENDOR_ID_MITSUBISHI&t;0x10ba
DECL|macro|PCI_VENDOR_ID_SURECOM
mdefine_line|#define PCI_VENDOR_ID_SURECOM&t;&t;0x10bd
DECL|macro|PCI_DEVICE_ID_SURECOM_NE34
mdefine_line|#define PCI_DEVICE_ID_SURECOM_NE34&t;0x0e34
DECL|macro|PCI_VENDOR_ID_NEOMAGIC
mdefine_line|#define PCI_VENDOR_ID_NEOMAGIC          0x10c8
DECL|macro|PCI_DEVICE_ID_NEOMAGIC_MAGICGRAPH_NM2070
mdefine_line|#define PCI_DEVICE_ID_NEOMAGIC_MAGICGRAPH_NM2070 0x0001
DECL|macro|PCI_DEVICE_ID_NEOMAGIC_MAGICGRAPH_128V
mdefine_line|#define PCI_DEVICE_ID_NEOMAGIC_MAGICGRAPH_128V 0x0002
DECL|macro|PCI_DEVICE_ID_NEOMAGIC_MAGICGRAPH_128ZV
mdefine_line|#define PCI_DEVICE_ID_NEOMAGIC_MAGICGRAPH_128ZV 0x0003
DECL|macro|PCI_DEVICE_ID_NEOMAGIC_MAGICGRAPH_NM2160
mdefine_line|#define PCI_DEVICE_ID_NEOMAGIC_MAGICGRAPH_NM2160 0x0004
DECL|macro|PCI_VENDOR_ID_ASP
mdefine_line|#define PCI_VENDOR_ID_ASP&t;&t;0x10cd
DECL|macro|PCI_DEVICE_ID_ASP_ABP940
mdefine_line|#define PCI_DEVICE_ID_ASP_ABP940&t;0x1200
DECL|macro|PCI_DEVICE_ID_ASP_ABP940U
mdefine_line|#define PCI_DEVICE_ID_ASP_ABP940U&t;0x1300
DECL|macro|PCI_VENDOR_ID_CERN
mdefine_line|#define PCI_VENDOR_ID_CERN&t;&t;0x10dc
DECL|macro|PCI_DEVICE_ID_CERN_SPSB_PMC
mdefine_line|#define PCI_DEVICE_ID_CERN_SPSB_PMC&t;0x0001
DECL|macro|PCI_DEVICE_ID_CERN_SPSB_PCI
mdefine_line|#define PCI_DEVICE_ID_CERN_SPSB_PCI&t;0x0002
DECL|macro|PCI_VENDOR_ID_NVIDIA
mdefine_line|#define PCI_VENDOR_ID_NVIDIA&t;&t;0x10de
DECL|macro|PCI_VENDOR_ID_IMS
mdefine_line|#define PCI_VENDOR_ID_IMS&t;&t;0x10e0
DECL|macro|PCI_DEVICE_ID_IMS_8849
mdefine_line|#define PCI_DEVICE_ID_IMS_8849&t;&t;0x8849
DECL|macro|PCI_VENDOR_ID_TEKRAM2
mdefine_line|#define PCI_VENDOR_ID_TEKRAM2&t;&t;0x10e1
DECL|macro|PCI_DEVICE_ID_TEKRAM2_690c
mdefine_line|#define PCI_DEVICE_ID_TEKRAM2_690c&t;0x690c
DECL|macro|PCI_VENDOR_ID_TUNDRA
mdefine_line|#define PCI_VENDOR_ID_TUNDRA&t;&t;0x10e3
DECL|macro|PCI_DEVICE_ID_TUNDRA_CA91C042
mdefine_line|#define PCI_DEVICE_ID_TUNDRA_CA91C042&t;0x0000
DECL|macro|PCI_VENDOR_ID_AMCC
mdefine_line|#define PCI_VENDOR_ID_AMCC&t;&t;0x10e8
DECL|macro|PCI_DEVICE_ID_AMCC_MYRINET
mdefine_line|#define PCI_DEVICE_ID_AMCC_MYRINET&t;0x8043
DECL|macro|PCI_DEVICE_ID_AMCC_S5933
mdefine_line|#define PCI_DEVICE_ID_AMCC_S5933&t;0x807d
DECL|macro|PCI_VENDOR_ID_INTERG
mdefine_line|#define PCI_VENDOR_ID_INTERG&t;&t;0x10ea
DECL|macro|PCI_DEVICE_ID_INTERG_1680
mdefine_line|#define PCI_DEVICE_ID_INTERG_1680&t;0x1680
DECL|macro|PCI_DEVICE_ID_INTERG_1682
mdefine_line|#define PCI_DEVICE_ID_INTERG_1682&t;0x1682
DECL|macro|PCI_VENDOR_ID_REALTEK
mdefine_line|#define PCI_VENDOR_ID_REALTEK&t;&t;0x10ec
DECL|macro|PCI_DEVICE_ID_REALTEK_8029
mdefine_line|#define PCI_DEVICE_ID_REALTEK_8029&t;0x8029
DECL|macro|PCI_DEVICE_ID_REALTEK_8129
mdefine_line|#define PCI_DEVICE_ID_REALTEK_8129&t;0x8129
DECL|macro|PCI_VENDOR_ID_TRUEVISION
mdefine_line|#define PCI_VENDOR_ID_TRUEVISION&t;0x10fa
DECL|macro|PCI_DEVICE_ID_TRUEVISION_T1000
mdefine_line|#define PCI_DEVICE_ID_TRUEVISION_T1000&t;0x000c
DECL|macro|PCI_VENDOR_ID_INIT
mdefine_line|#define PCI_VENDOR_ID_INIT&t;&t;0x1101
DECL|macro|PCI_DEVICE_ID_INIT_320P
mdefine_line|#define PCI_DEVICE_ID_INIT_320P&t;&t;0x9100
DECL|macro|PCI_VENDOR_ID_VIA
mdefine_line|#define PCI_VENDOR_ID_VIA&t;&t;0x1106
DECL|macro|PCI_DEVICE_ID_VIA_82C505
mdefine_line|#define PCI_DEVICE_ID_VIA_82C505&t;0x0505
DECL|macro|PCI_DEVICE_ID_VIA_82C561
mdefine_line|#define PCI_DEVICE_ID_VIA_82C561&t;0x0561
DECL|macro|PCI_DEVICE_ID_VIA_82C586_1
mdefine_line|#define PCI_DEVICE_ID_VIA_82C586_1&t;0x0571
DECL|macro|PCI_DEVICE_ID_VIA_82C576
mdefine_line|#define PCI_DEVICE_ID_VIA_82C576&t;0x0576
DECL|macro|PCI_DEVICE_ID_VIA_82C585
mdefine_line|#define PCI_DEVICE_ID_VIA_82C585&t;0x0585
DECL|macro|PCI_DEVICE_ID_VIA_82C586_0
mdefine_line|#define PCI_DEVICE_ID_VIA_82C586_0&t;0x0586
DECL|macro|PCI_DEVICE_ID_VIA_82C595
mdefine_line|#define PCI_DEVICE_ID_VIA_82C595&t;0x0595
DECL|macro|PCI_DEVICE_ID_VIA_82C926
mdefine_line|#define PCI_DEVICE_ID_VIA_82C926&t;0x0926
DECL|macro|PCI_DEVICE_ID_VIA_82C416
mdefine_line|#define PCI_DEVICE_ID_VIA_82C416&t;0x1571
DECL|macro|PCI_DEVICE_ID_VIA_82C595_97
mdefine_line|#define PCI_DEVICE_ID_VIA_82C595_97&t;0x1595
DECL|macro|PCI_DEVICE_ID_VIA_82C586_2
mdefine_line|#define PCI_DEVICE_ID_VIA_82C586_2&t;0x3038
DECL|macro|PCI_DEVICE_ID_VIA_82C586_3
mdefine_line|#define PCI_DEVICE_ID_VIA_82C586_3&t;0x3040
DECL|macro|PCI_VENDOR_ID_VORTEX
mdefine_line|#define PCI_VENDOR_ID_VORTEX&t;&t;0x1119
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT60x0
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT60x0&t;0x0000
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6000B
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6000B&t;0x0001
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x10
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x10&t;0x0002
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x20
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x20&t;0x0003
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6530
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6530&t;0x0004
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6550
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6550&t;0x0005
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x17
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x17&t;0x0006
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x27
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x27&t;0x0007
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6537
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6537&t;0x0008
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6557
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6557&t;0x0009
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x15
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x15&t;0x000a
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x25
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x25&t;0x000b
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6535
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6535&t;0x000c
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6555
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6555&t;0x000d
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x17RP
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x17RP&t;0x0100
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x27RP
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x27RP&t;0x0101
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6537RP
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6537RP&t;0x0102
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6557RP
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6557RP&t;0x0103
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x11RP
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x11RP&t;0x0104
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x21RP
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x21RP&t;0x0105
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x17RP1
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x17RP1&t;0x0110
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x27RP1
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x27RP1&t;0x0111
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6537RP1
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6537RP1&t;0x0112
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6557RP1
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6557RP1&t;0x0113
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x11RP1
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x11RP1&t;0x0114
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x21RP1
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x21RP1&t;0x0115
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x17RP2
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x17RP2&t;0x0120
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x27RP2
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x27RP2&t;0x0121
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6537RP2
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6537RP2&t;0x0122
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6557RP2
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6557RP2&t;0x0123
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x11RP2
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x11RP2&t;0x0124
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x21RP2
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x21RP2&t;0x0125
DECL|macro|PCI_VENDOR_ID_EF
mdefine_line|#define PCI_VENDOR_ID_EF&t;&t;0x111a
DECL|macro|PCI_DEVICE_ID_EF_ATM_FPGA
mdefine_line|#define PCI_DEVICE_ID_EF_ATM_FPGA&t;0x0000
DECL|macro|PCI_DEVICE_ID_EF_ATM_ASIC
mdefine_line|#define PCI_DEVICE_ID_EF_ATM_ASIC&t;0x0002
DECL|macro|PCI_VENDOR_ID_FORE
mdefine_line|#define PCI_VENDOR_ID_FORE&t;&t;0x1127
DECL|macro|PCI_DEVICE_ID_FORE_PCA200PC
mdefine_line|#define PCI_DEVICE_ID_FORE_PCA200PC&t;0x0210
DECL|macro|PCI_DEVICE_ID_FORE_PCA200E
mdefine_line|#define PCI_DEVICE_ID_FORE_PCA200E&t;0x0300
DECL|macro|PCI_VENDOR_ID_IMAGINGTECH
mdefine_line|#define PCI_VENDOR_ID_IMAGINGTECH&t;0x112f
DECL|macro|PCI_DEVICE_ID_IMAGINGTECH_ICPCI
mdefine_line|#define PCI_DEVICE_ID_IMAGINGTECH_ICPCI&t;0x0000
DECL|macro|PCI_VENDOR_ID_PHILIPS
mdefine_line|#define PCI_VENDOR_ID_PHILIPS&t;&t;0x1131
DECL|macro|PCI_DEVICE_ID_PHILIPS_SAA7146
mdefine_line|#define PCI_DEVICE_ID_PHILIPS_SAA7146&t;0x7146
DECL|macro|PCI_VENDOR_ID_PLX
mdefine_line|#define PCI_VENDOR_ID_PLX&t;&t;0x113c
DECL|macro|PCI_DEVICE_ID_PLX_9060
mdefine_line|#define PCI_DEVICE_ID_PLX_9060&t;&t;0x0001
DECL|macro|PCI_VENDOR_ID_ALLIANCE
mdefine_line|#define PCI_VENDOR_ID_ALLIANCE&t;&t;0x1142
DECL|macro|PCI_DEVICE_ID_ALLIANCE_PROMOTIO
mdefine_line|#define PCI_DEVICE_ID_ALLIANCE_PROMOTIO&t;0x3210
DECL|macro|PCI_DEVICE_ID_ALLIANCE_PROVIDEO
mdefine_line|#define PCI_DEVICE_ID_ALLIANCE_PROVIDEO&t;0x6422
DECL|macro|PCI_DEVICE_ID_ALLIANCE_AT24
mdefine_line|#define PCI_DEVICE_ID_ALLIANCE_AT24&t;0x6424
DECL|macro|PCI_DEVICE_ID_ALLIANCE_AT3D
mdefine_line|#define PCI_DEVICE_ID_ALLIANCE_AT3D&t;0x643d
DECL|macro|PCI_VENDOR_ID_VMIC
mdefine_line|#define PCI_VENDOR_ID_VMIC&t;&t;0x114a
DECL|macro|PCI_DEVICE_ID_VMIC_VME
mdefine_line|#define PCI_DEVICE_ID_VMIC_VME&t;&t;0x7587
DECL|macro|PCI_VENDOR_ID_DIGI
mdefine_line|#define PCI_VENDOR_ID_DIGI&t;&t;0x114f
DECL|macro|PCI_DEVICE_ID_DIGI_RIGHTSWITCH
mdefine_line|#define PCI_DEVICE_ID_DIGI_RIGHTSWITCH&t;0x0003
DECL|macro|PCI_VENDOR_ID_MUTECH
mdefine_line|#define PCI_VENDOR_ID_MUTECH&t;&t;0x1159
DECL|macro|PCI_DEVICE_ID_MUTECH_MV1000
mdefine_line|#define PCI_DEVICE_ID_MUTECH_MV1000&t;0x0001
DECL|macro|PCI_VENDOR_ID_RENDITION
mdefine_line|#define PCI_VENDOR_ID_RENDITION&t;&t;0x1163
DECL|macro|PCI_DEVICE_ID_RENDITION_VERITE
mdefine_line|#define PCI_DEVICE_ID_RENDITION_VERITE&t;0x0001
DECL|macro|PCI_VENDOR_ID_TOSHIBA
mdefine_line|#define PCI_VENDOR_ID_TOSHIBA&t;&t;0x1179
DECL|macro|PCI_DEVICE_ID_TOSHIBA_601
mdefine_line|#define PCI_DEVICE_ID_TOSHIBA_601&t;0x0601
DECL|macro|PCI_VENDOR_ID_RICOH
mdefine_line|#define PCI_VENDOR_ID_RICOH&t;&t;0x1180
DECL|macro|PCI_DEVICE_ID_RICOH_RL5C466
mdefine_line|#define PCI_DEVICE_ID_RICOH_RL5C466&t;0x0466
DECL|macro|PCI_VENDOR_ID_ZEITNET
mdefine_line|#define PCI_VENDOR_ID_ZEITNET&t;&t;0x1193
DECL|macro|PCI_DEVICE_ID_ZEITNET_1221
mdefine_line|#define PCI_DEVICE_ID_ZEITNET_1221&t;0x0001
DECL|macro|PCI_DEVICE_ID_ZEITNET_1225
mdefine_line|#define PCI_DEVICE_ID_ZEITNET_1225&t;0x0002
DECL|macro|PCI_VENDOR_ID_OMEGA
mdefine_line|#define PCI_VENDOR_ID_OMEGA&t;&t;0x119b
DECL|macro|PCI_DEVICE_ID_OMEGA_82C092G
mdefine_line|#define PCI_DEVICE_ID_OMEGA_82C092G&t;0x1221
DECL|macro|PCI_VENDOR_ID_LITEON
mdefine_line|#define PCI_VENDOR_ID_LITEON&t;&t;0x11ad
DECL|macro|PCI_DEVICE_ID_LITEON_LNE100TX
mdefine_line|#define PCI_DEVICE_ID_LITEON_LNE100TX&t;0x0002
DECL|macro|PCI_VENDOR_ID_NP
mdefine_line|#define PCI_VENDOR_ID_NP&t;&t;0x11bc
DECL|macro|PCI_DEVICE_ID_NP_PCI_FDDI
mdefine_line|#define PCI_DEVICE_ID_NP_PCI_FDDI&t;0x0001
DECL|macro|PCI_VENDOR_ID_SPECIALIX
mdefine_line|#define PCI_VENDOR_ID_SPECIALIX&t;&t;0x11cb
DECL|macro|PCI_DEVICE_ID_SPECIALIX_XIO
mdefine_line|#define PCI_DEVICE_ID_SPECIALIX_XIO&t;0x4000
DECL|macro|PCI_DEVICE_ID_SPECIALIX_RIO
mdefine_line|#define PCI_DEVICE_ID_SPECIALIX_RIO&t;0x8000
DECL|macro|PCI_VENDOR_ID_AURAVISION
mdefine_line|#define PCI_VENDOR_ID_AURAVISION&t;0x11d1
DECL|macro|PCI_DEVICE_ID_AURAVISION_VXP524
mdefine_line|#define PCI_DEVICE_ID_AURAVISION_VXP524&t;0x01f7
DECL|macro|PCI_VENDOR_ID_IKON
mdefine_line|#define PCI_VENDOR_ID_IKON&t;&t;0x11d5
DECL|macro|PCI_DEVICE_ID_IKON_10115
mdefine_line|#define PCI_DEVICE_ID_IKON_10115&t;0x0115
DECL|macro|PCI_DEVICE_ID_IKON_10117
mdefine_line|#define PCI_DEVICE_ID_IKON_10117&t;0x0117
DECL|macro|PCI_VENDOR_ID_ZORAN
mdefine_line|#define PCI_VENDOR_ID_ZORAN&t;&t;0x11de
DECL|macro|PCI_DEVICE_ID_ZORAN_36057
mdefine_line|#define PCI_DEVICE_ID_ZORAN_36057&t;0x6057
DECL|macro|PCI_DEVICE_ID_ZORAN_36120
mdefine_line|#define PCI_DEVICE_ID_ZORAN_36120&t;0x6120
DECL|macro|PCI_VENDOR_ID_COMPEX
mdefine_line|#define PCI_VENDOR_ID_COMPEX&t;&t;0x11f6
DECL|macro|PCI_DEVICE_ID_COMPEX_ENET100VG4
mdefine_line|#define PCI_DEVICE_ID_COMPEX_ENET100VG4&t;0x0112
DECL|macro|PCI_DEVICE_ID_COMPEX_RL2000
mdefine_line|#define PCI_DEVICE_ID_COMPEX_RL2000&t;0x1401
DECL|macro|PCI_VENDOR_ID_RP
mdefine_line|#define PCI_VENDOR_ID_RP               0x11fe
DECL|macro|PCI_DEVICE_ID_RP8OCTA
mdefine_line|#define PCI_DEVICE_ID_RP8OCTA          0x0001
DECL|macro|PCI_DEVICE_ID_RP8INTF
mdefine_line|#define PCI_DEVICE_ID_RP8INTF          0x0002
DECL|macro|PCI_DEVICE_ID_RP16INTF
mdefine_line|#define PCI_DEVICE_ID_RP16INTF         0x0003
DECL|macro|PCI_DEVICE_ID_RP32INTF
mdefine_line|#define PCI_DEVICE_ID_RP32INTF         0x0004
DECL|macro|PCI_VENDOR_ID_CYCLADES
mdefine_line|#define PCI_VENDOR_ID_CYCLADES&t;&t;0x120e
DECL|macro|PCI_DEVICE_ID_CYCLOM_Y_Lo
mdefine_line|#define PCI_DEVICE_ID_CYCLOM_Y_Lo&t;0x0100
DECL|macro|PCI_DEVICE_ID_CYCLOM_Y_Hi
mdefine_line|#define PCI_DEVICE_ID_CYCLOM_Y_Hi&t;0x0101
DECL|macro|PCI_DEVICE_ID_CYCLOM_Z_Lo
mdefine_line|#define PCI_DEVICE_ID_CYCLOM_Z_Lo&t;0x0200
DECL|macro|PCI_DEVICE_ID_CYCLOM_Z_Hi
mdefine_line|#define PCI_DEVICE_ID_CYCLOM_Z_Hi&t;0x0201
DECL|macro|PCI_VENDOR_ID_3DFX
mdefine_line|#define PCI_VENDOR_ID_3DFX&t;&t;0x121a
DECL|macro|PCI_DEVICE_ID_3DFX_VOODOO
mdefine_line|#define PCI_DEVICE_ID_3DFX_VOODOO&t;0x0001
DECL|macro|PCI_VENDOR_ID_SIGMADES
mdefine_line|#define PCI_VENDOR_ID_SIGMADES&t;&t;0x1236
DECL|macro|PCI_DEVICE_ID_SIGMADES_6425
mdefine_line|#define PCI_DEVICE_ID_SIGMADES_6425&t;0x6401
DECL|macro|PCI_VENDOR_ID_OPTIBASE
mdefine_line|#define PCI_VENDOR_ID_OPTIBASE&t;&t;0x1255
DECL|macro|PCI_DEVICE_ID_OPTIBASE_FORGE
mdefine_line|#define PCI_DEVICE_ID_OPTIBASE_FORGE&t;0x1110
DECL|macro|PCI_DEVICE_ID_OPTIBASE_FUSION
mdefine_line|#define PCI_DEVICE_ID_OPTIBASE_FUSION&t;0x1210
DECL|macro|PCI_DEVICE_ID_OPTIBASE_VPLEX
mdefine_line|#define PCI_DEVICE_ID_OPTIBASE_VPLEX&t;0x2110
DECL|macro|PCI_DEVICE_ID_OPTIBASE_VPLEXCC
mdefine_line|#define PCI_DEVICE_ID_OPTIBASE_VPLEXCC&t;0x2120
DECL|macro|PCI_DEVICE_ID_OPTIBASE_VQUEST
mdefine_line|#define PCI_DEVICE_ID_OPTIBASE_VQUEST&t;0x2130
DECL|macro|PCI_VENDOR_ID_ENSONIQ
mdefine_line|#define PCI_VENDOR_ID_ENSONIQ&t;&t;0x1274
DECL|macro|PCI_DEVICE_ID_ENSONIQ_AUDIOPCI
mdefine_line|#define PCI_DEVICE_ID_ENSONIQ_AUDIOPCI&t;0x5000
DECL|macro|PCI_VENDOR_ID_PICTUREL
mdefine_line|#define PCI_VENDOR_ID_PICTUREL&t;&t;0x12c5
DECL|macro|PCI_DEVICE_ID_PICTUREL_PCIVST
mdefine_line|#define PCI_DEVICE_ID_PICTUREL_PCIVST&t;0x0081
DECL|macro|PCI_VENDOR_ID_NVIDIA_SGS
mdefine_line|#define PCI_VENDOR_ID_NVIDIA_SGS&t;0x12d2
DECL|macro|PCI_DEVICE_ID_NVIDIA_SGS_RIVA128
mdefine_line|#define PCI_DEVICE_ID_NVIDIA_SGS_RIVA128 0x0018
DECL|macro|PCI_VENDOR_ID_SYMPHONY
mdefine_line|#define PCI_VENDOR_ID_SYMPHONY&t;&t;0x1c1c
DECL|macro|PCI_DEVICE_ID_SYMPHONY_101
mdefine_line|#define PCI_DEVICE_ID_SYMPHONY_101&t;0x0001
DECL|macro|PCI_VENDOR_ID_TEKRAM
mdefine_line|#define PCI_VENDOR_ID_TEKRAM&t;&t;0x1de1
DECL|macro|PCI_DEVICE_ID_TEKRAM_DC290
mdefine_line|#define PCI_DEVICE_ID_TEKRAM_DC290&t;0xdc29
DECL|macro|PCI_VENDOR_ID_3DLABS
mdefine_line|#define PCI_VENDOR_ID_3DLABS&t;&t;0x3d3d
DECL|macro|PCI_DEVICE_ID_3DLABS_300SX
mdefine_line|#define PCI_DEVICE_ID_3DLABS_300SX&t;0x0001
DECL|macro|PCI_DEVICE_ID_3DLABS_500TX
mdefine_line|#define PCI_DEVICE_ID_3DLABS_500TX&t;0x0002
DECL|macro|PCI_DEVICE_ID_3DLABS_DELTA
mdefine_line|#define PCI_DEVICE_ID_3DLABS_DELTA&t;0x0003
DECL|macro|PCI_DEVICE_ID_3DLABS_PERMEDIA
mdefine_line|#define PCI_DEVICE_ID_3DLABS_PERMEDIA&t;0x0004
DECL|macro|PCI_VENDOR_ID_AVANCE
mdefine_line|#define PCI_VENDOR_ID_AVANCE&t;&t;0x4005
DECL|macro|PCI_DEVICE_ID_AVANCE_ALG2064
mdefine_line|#define PCI_DEVICE_ID_AVANCE_ALG2064&t;0x2064
DECL|macro|PCI_DEVICE_ID_AVANCE_2302
mdefine_line|#define PCI_DEVICE_ID_AVANCE_2302&t;0x2302
DECL|macro|PCI_VENDOR_ID_NETVIN
mdefine_line|#define PCI_VENDOR_ID_NETVIN&t;&t;0x4a14
DECL|macro|PCI_DEVICE_ID_NETVIN_NV5000SC
mdefine_line|#define PCI_DEVICE_ID_NETVIN_NV5000SC&t;0x5000
DECL|macro|PCI_VENDOR_ID_S3
mdefine_line|#define PCI_VENDOR_ID_S3&t;&t;0x5333
DECL|macro|PCI_DEVICE_ID_S3_PLATO_PXS
mdefine_line|#define PCI_DEVICE_ID_S3_PLATO_PXS&t;0x0551
DECL|macro|PCI_DEVICE_ID_S3_ViRGE
mdefine_line|#define PCI_DEVICE_ID_S3_ViRGE&t;&t;0x5631
DECL|macro|PCI_DEVICE_ID_S3_TRIO
mdefine_line|#define PCI_DEVICE_ID_S3_TRIO&t;&t;0x8811
DECL|macro|PCI_DEVICE_ID_S3_AURORA64VP
mdefine_line|#define PCI_DEVICE_ID_S3_AURORA64VP&t;0x8812
DECL|macro|PCI_DEVICE_ID_S3_TRIO64UVP
mdefine_line|#define PCI_DEVICE_ID_S3_TRIO64UVP&t;0x8814
DECL|macro|PCI_DEVICE_ID_S3_ViRGE_VX
mdefine_line|#define PCI_DEVICE_ID_S3_ViRGE_VX&t;0x883d
DECL|macro|PCI_DEVICE_ID_S3_868
mdefine_line|#define PCI_DEVICE_ID_S3_868&t;&t;0x8880
DECL|macro|PCI_DEVICE_ID_S3_928
mdefine_line|#define PCI_DEVICE_ID_S3_928&t;&t;0x88b0
DECL|macro|PCI_DEVICE_ID_S3_864_1
mdefine_line|#define PCI_DEVICE_ID_S3_864_1&t;&t;0x88c0
DECL|macro|PCI_DEVICE_ID_S3_864_2
mdefine_line|#define PCI_DEVICE_ID_S3_864_2&t;&t;0x88c1
DECL|macro|PCI_DEVICE_ID_S3_964_1
mdefine_line|#define PCI_DEVICE_ID_S3_964_1&t;&t;0x88d0
DECL|macro|PCI_DEVICE_ID_S3_964_2
mdefine_line|#define PCI_DEVICE_ID_S3_964_2&t;&t;0x88d1
DECL|macro|PCI_DEVICE_ID_S3_968
mdefine_line|#define PCI_DEVICE_ID_S3_968&t;&t;0x88f0
DECL|macro|PCI_DEVICE_ID_S3_TRIO64V2
mdefine_line|#define PCI_DEVICE_ID_S3_TRIO64V2&t;0x8901
DECL|macro|PCI_DEVICE_ID_S3_PLATO_PXG
mdefine_line|#define PCI_DEVICE_ID_S3_PLATO_PXG&t;0x8902
DECL|macro|PCI_DEVICE_ID_S3_ViRGE_DXGX
mdefine_line|#define PCI_DEVICE_ID_S3_ViRGE_DXGX&t;0x8a01
DECL|macro|PCI_DEVICE_ID_S3_ViRGE_GX2
mdefine_line|#define PCI_DEVICE_ID_S3_ViRGE_GX2&t;0x8a10
DECL|macro|PCI_VENDOR_ID_INTEL
mdefine_line|#define PCI_VENDOR_ID_INTEL&t;&t;0x8086
DECL|macro|PCI_DEVICE_ID_INTEL_82375
mdefine_line|#define PCI_DEVICE_ID_INTEL_82375&t;0x0482
DECL|macro|PCI_DEVICE_ID_INTEL_82424
mdefine_line|#define PCI_DEVICE_ID_INTEL_82424&t;0x0483
DECL|macro|PCI_DEVICE_ID_INTEL_82378
mdefine_line|#define PCI_DEVICE_ID_INTEL_82378&t;0x0484
DECL|macro|PCI_DEVICE_ID_INTEL_82430
mdefine_line|#define PCI_DEVICE_ID_INTEL_82430&t;0x0486
DECL|macro|PCI_DEVICE_ID_INTEL_82434
mdefine_line|#define PCI_DEVICE_ID_INTEL_82434&t;0x04a3
DECL|macro|PCI_DEVICE_ID_INTEL_82092AA_0
mdefine_line|#define PCI_DEVICE_ID_INTEL_82092AA_0&t;0x1221
DECL|macro|PCI_DEVICE_ID_INTEL_82092AA_1
mdefine_line|#define PCI_DEVICE_ID_INTEL_82092AA_1&t;0x1222
DECL|macro|PCI_DEVICE_ID_INTEL_7116
mdefine_line|#define PCI_DEVICE_ID_INTEL_7116&t;0x1223
DECL|macro|PCI_DEVICE_ID_INTEL_82596
mdefine_line|#define PCI_DEVICE_ID_INTEL_82596&t;0x1226
DECL|macro|PCI_DEVICE_ID_INTEL_82865
mdefine_line|#define PCI_DEVICE_ID_INTEL_82865&t;0x1227
DECL|macro|PCI_DEVICE_ID_INTEL_82557
mdefine_line|#define PCI_DEVICE_ID_INTEL_82557&t;0x1229
DECL|macro|PCI_DEVICE_ID_INTEL_82437
mdefine_line|#define PCI_DEVICE_ID_INTEL_82437&t;0x122d
DECL|macro|PCI_DEVICE_ID_INTEL_82371FB_0
mdefine_line|#define PCI_DEVICE_ID_INTEL_82371FB_0&t;0x122e
DECL|macro|PCI_DEVICE_ID_INTEL_82371FB_1
mdefine_line|#define PCI_DEVICE_ID_INTEL_82371FB_1&t;0x1230
DECL|macro|PCI_DEVICE_ID_INTEL_82371MX
mdefine_line|#define PCI_DEVICE_ID_INTEL_82371MX&t;0x1234
DECL|macro|PCI_DEVICE_ID_INTEL_82437MX
mdefine_line|#define PCI_DEVICE_ID_INTEL_82437MX&t;0x1235
DECL|macro|PCI_DEVICE_ID_INTEL_82441
mdefine_line|#define PCI_DEVICE_ID_INTEL_82441&t;0x1237
DECL|macro|PCI_DEVICE_ID_INTEL_82439
mdefine_line|#define PCI_DEVICE_ID_INTEL_82439&t;0x1250
DECL|macro|PCI_DEVICE_ID_INTEL_82371SB_0
mdefine_line|#define PCI_DEVICE_ID_INTEL_82371SB_0&t;0x7000
DECL|macro|PCI_DEVICE_ID_INTEL_82371SB_1
mdefine_line|#define PCI_DEVICE_ID_INTEL_82371SB_1&t;0x7010
DECL|macro|PCI_DEVICE_ID_INTEL_82371SB_2
mdefine_line|#define PCI_DEVICE_ID_INTEL_82371SB_2&t;0x7020
DECL|macro|PCI_DEVICE_ID_INTEL_82437VX
mdefine_line|#define PCI_DEVICE_ID_INTEL_82437VX&t;0x7030
DECL|macro|PCI_DEVICE_ID_INTEL_82439TX
mdefine_line|#define PCI_DEVICE_ID_INTEL_82439TX&t;0x7100
DECL|macro|PCI_DEVICE_ID_INTEL_82371AB_0
mdefine_line|#define PCI_DEVICE_ID_INTEL_82371AB_0&t;0x7110
DECL|macro|PCI_DEVICE_ID_INTEL_82371AB
mdefine_line|#define PCI_DEVICE_ID_INTEL_82371AB&t;0x7111
DECL|macro|PCI_DEVICE_ID_INTEL_82371AB_2
mdefine_line|#define PCI_DEVICE_ID_INTEL_82371AB_2&t;0x7112
DECL|macro|PCI_DEVICE_ID_INTEL_82371AB_3
mdefine_line|#define PCI_DEVICE_ID_INTEL_82371AB_3&t;0x7113
DECL|macro|PCI_DEVICE_ID_INTEL_82443LX_0
mdefine_line|#define PCI_DEVICE_ID_INTEL_82443LX_0&t;0x7180
DECL|macro|PCI_DEVICE_ID_INTEL_82443LX_1
mdefine_line|#define PCI_DEVICE_ID_INTEL_82443LX_1&t;0x7181
DECL|macro|PCI_DEVICE_ID_INTEL_P6
mdefine_line|#define PCI_DEVICE_ID_INTEL_P6&t;&t;0x84c4
DECL|macro|PCI_DEVICE_ID_INTEL_82450GX
mdefine_line|#define PCI_DEVICE_ID_INTEL_82450GX&t;0x84c5
DECL|macro|PCI_VENDOR_ID_KTI
mdefine_line|#define PCI_VENDOR_ID_KTI&t;&t;0x8e2e
DECL|macro|PCI_DEVICE_ID_KTI_ET32P2
mdefine_line|#define PCI_DEVICE_ID_KTI_ET32P2&t;0x3000
DECL|macro|PCI_VENDOR_ID_ADAPTEC
mdefine_line|#define PCI_VENDOR_ID_ADAPTEC&t;&t;0x9004
DECL|macro|PCI_DEVICE_ID_ADAPTEC_7850
mdefine_line|#define PCI_DEVICE_ID_ADAPTEC_7850&t;0x5078
DECL|macro|PCI_DEVICE_ID_ADAPTEC_7855
mdefine_line|#define PCI_DEVICE_ID_ADAPTEC_7855&t;0x5578
DECL|macro|PCI_DEVICE_ID_ADAPTEC_5800
mdefine_line|#define PCI_DEVICE_ID_ADAPTEC_5800&t;0x5800
DECL|macro|PCI_DEVICE_ID_ADAPTEC_7860
mdefine_line|#define PCI_DEVICE_ID_ADAPTEC_7860&t;0x6078
DECL|macro|PCI_DEVICE_ID_ADAPTEC_7861
mdefine_line|#define PCI_DEVICE_ID_ADAPTEC_7861&t;0x6178
DECL|macro|PCI_DEVICE_ID_ADAPTEC_7870
mdefine_line|#define PCI_DEVICE_ID_ADAPTEC_7870&t;0x7078
DECL|macro|PCI_DEVICE_ID_ADAPTEC_7871
mdefine_line|#define PCI_DEVICE_ID_ADAPTEC_7871&t;0x7178
DECL|macro|PCI_DEVICE_ID_ADAPTEC_7872
mdefine_line|#define PCI_DEVICE_ID_ADAPTEC_7872&t;0x7278
DECL|macro|PCI_DEVICE_ID_ADAPTEC_7873
mdefine_line|#define PCI_DEVICE_ID_ADAPTEC_7873&t;0x7378
DECL|macro|PCI_DEVICE_ID_ADAPTEC_7874
mdefine_line|#define PCI_DEVICE_ID_ADAPTEC_7874&t;0x7478
DECL|macro|PCI_DEVICE_ID_ADAPTEC_7895
mdefine_line|#define PCI_DEVICE_ID_ADAPTEC_7895&t;0x7895
DECL|macro|PCI_DEVICE_ID_ADAPTEC_7880
mdefine_line|#define PCI_DEVICE_ID_ADAPTEC_7880&t;0x8078
DECL|macro|PCI_DEVICE_ID_ADAPTEC_7881
mdefine_line|#define PCI_DEVICE_ID_ADAPTEC_7881&t;0x8178
DECL|macro|PCI_DEVICE_ID_ADAPTEC_7882
mdefine_line|#define PCI_DEVICE_ID_ADAPTEC_7882&t;0x8278
DECL|macro|PCI_DEVICE_ID_ADAPTEC_7883
mdefine_line|#define PCI_DEVICE_ID_ADAPTEC_7883&t;0x8378
DECL|macro|PCI_DEVICE_ID_ADAPTEC_7884
mdefine_line|#define PCI_DEVICE_ID_ADAPTEC_7884&t;0x8478
DECL|macro|PCI_VENDOR_ID_ATRONICS
mdefine_line|#define PCI_VENDOR_ID_ATRONICS&t;&t;0x907f
DECL|macro|PCI_DEVICE_ID_ATRONICS_2015
mdefine_line|#define PCI_DEVICE_ID_ATRONICS_2015&t;0x2015
DECL|macro|PCI_VENDOR_ID_ARK
mdefine_line|#define PCI_VENDOR_ID_ARK&t;&t;0xedd8
DECL|macro|PCI_DEVICE_ID_ARK_STING
mdefine_line|#define PCI_DEVICE_ID_ARK_STING&t;&t;0xa091
DECL|macro|PCI_DEVICE_ID_ARK_STINGARK
mdefine_line|#define PCI_DEVICE_ID_ARK_STINGARK&t;0xa099
DECL|macro|PCI_DEVICE_ID_ARK_2000MT
mdefine_line|#define PCI_DEVICE_ID_ARK_2000MT&t;0xa0a1
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * The PCI interface treats multi-function devices as independent&n; * devices.  The slot/function address of each device is encoded&n; * in a single byte as follows:&n; *&n; *&t;7:3 = slot&n; *&t;2:0 = function&n; */
DECL|macro|PCI_DEVFN
mdefine_line|#define PCI_DEVFN(slot,func)&t;((((slot) &amp; 0x1f) &lt;&lt; 3) | ((func) &amp; 0x07))
DECL|macro|PCI_SLOT
mdefine_line|#define PCI_SLOT(devfn)&t;&t;(((devfn) &gt;&gt; 3) &amp; 0x1f)
DECL|macro|PCI_FUNC
mdefine_line|#define PCI_FUNC(devfn)&t;&t;((devfn) &amp; 0x07)
multiline_comment|/*&n; * There is one pci_dev structure for each slot-number/function-number&n; * combination:&n; */
DECL|struct|pci_dev
r_struct
id|pci_dev
(brace
DECL|member|bus
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
multiline_comment|/* bus this device is on */
DECL|member|sibling
r_struct
id|pci_dev
op_star
id|sibling
suffix:semicolon
multiline_comment|/* next device on this bus */
DECL|member|next
r_struct
id|pci_dev
op_star
id|next
suffix:semicolon
multiline_comment|/* chain of all devices */
DECL|member|sysdata
r_void
op_star
id|sysdata
suffix:semicolon
multiline_comment|/* hook for sys-specific extension */
DECL|member|devfn
r_int
r_int
id|devfn
suffix:semicolon
multiline_comment|/* encoded device &amp; function index */
DECL|member|vendor
r_int
r_int
id|vendor
suffix:semicolon
DECL|member|device
r_int
r_int
id|device
suffix:semicolon
DECL|member|class
r_int
r_int
r_class
suffix:semicolon
multiline_comment|/* 3 bytes: (base,sub,prog-if) */
DECL|member|master
r_int
r_int
id|master
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* set if device is master capable */
multiline_comment|/*&n;&t; * In theory, the irq level can be read from configuration&n;&t; * space and all would be fine.  However, old PCI chips don&squot;t&n;&t; * support these registers and return 0 instead.  For example,&n;&t; * the Vision864-P rev 0 chip can uses INTA, but returns 0 in&n;&t; * the interrupt line and pin registers.  pci_init()&n;&t; * initializes this field with the value at PCI_INTERRUPT_LINE&n;&t; * and it is the job of pcibios_fixup() to change it if&n;&t; * necessary.  The field must not be 0 unless the device&n;&t; * cannot generate interrupts at all.&n;&t; */
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* irq generated by this device */
multiline_comment|/* Base registers for this device, can be adjusted by&n;&t; * pcibios_fixup() as necessary.&n;&t; */
DECL|member|base_address
r_int
r_int
id|base_address
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pci_bus
r_struct
id|pci_bus
(brace
DECL|member|parent
r_struct
id|pci_bus
op_star
id|parent
suffix:semicolon
multiline_comment|/* parent bus this bridge is on */
DECL|member|children
r_struct
id|pci_bus
op_star
id|children
suffix:semicolon
multiline_comment|/* chain of P2P bridges on this bus */
DECL|member|next
r_struct
id|pci_bus
op_star
id|next
suffix:semicolon
multiline_comment|/* chain of all PCI buses */
DECL|member|self
r_struct
id|pci_dev
op_star
id|self
suffix:semicolon
multiline_comment|/* bridge device as seen by parent */
DECL|member|devices
r_struct
id|pci_dev
op_star
id|devices
suffix:semicolon
multiline_comment|/* devices behind this bridge */
DECL|member|sysdata
r_void
op_star
id|sysdata
suffix:semicolon
multiline_comment|/* hook for sys-specific extension */
DECL|member|number
r_int
r_char
id|number
suffix:semicolon
multiline_comment|/* bus number */
DECL|member|primary
r_int
r_char
id|primary
suffix:semicolon
multiline_comment|/* number of primary bridge */
DECL|member|secondary
r_int
r_char
id|secondary
suffix:semicolon
multiline_comment|/* number of secondary bridge */
DECL|member|subordinate
r_int
r_char
id|subordinate
suffix:semicolon
multiline_comment|/* max number of subordinate buses */
)brace
suffix:semicolon
multiline_comment|/*&n; * This is used to map a vendor-id/device-id pair into device-specific&n; * information.&n; */
DECL|struct|pci_dev_info
r_struct
id|pci_dev_info
(brace
DECL|member|vendor
r_int
r_int
id|vendor
suffix:semicolon
multiline_comment|/* vendor id */
DECL|member|device
r_int
r_int
id|device
suffix:semicolon
multiline_comment|/* device id */
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* device name */
DECL|member|bridge_type
r_int
r_char
id|bridge_type
suffix:semicolon
multiline_comment|/* bridge type or 0xff */
)brace
suffix:semicolon
r_extern
r_struct
id|pci_bus
id|pci_root
suffix:semicolon
multiline_comment|/* root bus */
r_extern
r_struct
id|pci_dev
op_star
id|pci_devices
suffix:semicolon
multiline_comment|/* list of all devices */
r_extern
r_int
r_int
id|pci_init
(paren
r_int
r_int
id|mem_start
comma
r_int
r_int
id|mem_end
)paren
suffix:semicolon
r_extern
r_int
r_int
id|pci_scan_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
op_star
id|mem_startp
)paren
suffix:semicolon
r_extern
r_struct
id|pci_dev_info
op_star
id|pci_lookup_dev
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|dev
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|pci_strclass
(paren
r_int
r_int
r_class
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|pci_strvendor
(paren
r_int
r_int
id|vendor
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|pci_strdev
(paren
r_int
r_int
id|vendor
comma
r_int
r_int
id|device
)paren
suffix:semicolon
r_extern
r_int
id|get_pci_list
(paren
r_char
op_star
id|buf
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* LINUX_PCI_H */
eof
