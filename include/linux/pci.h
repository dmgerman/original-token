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
multiline_comment|/*&n; * Base adddresses specify locations in memory or I/O space.&n; * Decoded size can be determined by writing a value of &n; * 0xffffffff to the register, and reading it back.  Only &n; * 1 bits are decoded.&n; */
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
DECL|macro|PCI_VENDOR_ID_NCR
mdefine_line|#define PCI_VENDOR_ID_NCR&t;&t;0x1000
DECL|macro|PCI_DEVICE_ID_NCR_53C810
mdefine_line|#define PCI_DEVICE_ID_NCR_53C810&t;0x0001
DECL|macro|PCI_DEVICE_ID_NCR_53C820
mdefine_line|#define PCI_DEVICE_ID_NCR_53C820&t;0x0002
DECL|macro|PCI_DEVICE_ID_NCR_53C825
mdefine_line|#define PCI_DEVICE_ID_NCR_53C825&t;0x0003
multiline_comment|/* PCI BIOS */
r_extern
r_int
id|pcibios_present
(paren
r_void
)paren
suffix:semicolon
DECL|macro|PCIBIOS_SUCCESFUL
mdefine_line|#define PCIBIOS_SUCCESFUL&t;&t;0x00
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
