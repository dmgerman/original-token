macro_line|#ifndef _ACENIC_H_
DECL|macro|_ACENIC_H_
mdefine_line|#define _ACENIC_H_
macro_line|#if ((BITS_PER_LONG != 32) &amp;&amp; (BITS_PER_LONG != 64))
macro_line|#error &quot;BITS_PER_LONG not defined or not valid&quot;
macro_line|#endif
DECL|struct|ace_regs
r_struct
id|ace_regs
(brace
DECL|member|pad0
id|u32
id|pad0
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* PCI control registers */
DECL|member|HostCtrl
id|u32
id|HostCtrl
suffix:semicolon
multiline_comment|/* 0x40 */
DECL|member|LocalCtrl
id|u32
id|LocalCtrl
suffix:semicolon
DECL|member|pad1
id|u32
id|pad1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|MiscCfg
id|u32
id|MiscCfg
suffix:semicolon
multiline_comment|/* 0x50 */
DECL|member|pad2
id|u32
id|pad2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|PciState
id|u32
id|PciState
suffix:semicolon
DECL|member|pad3
id|u32
id|pad3
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 0x60 */
DECL|member|WinBase
id|u32
id|WinBase
suffix:semicolon
DECL|member|WinData
id|u32
id|WinData
suffix:semicolon
DECL|member|pad4
id|u32
id|pad4
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* 0x70 */
DECL|member|DmaWriteState
id|u32
id|DmaWriteState
suffix:semicolon
multiline_comment|/* 0xa0 */
DECL|member|pad5
id|u32
id|pad5
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|DmaReadState
id|u32
id|DmaReadState
suffix:semicolon
multiline_comment|/* 0xb0 */
DECL|member|pad6
id|u32
id|pad6
(braket
l_int|26
)braket
suffix:semicolon
DECL|member|AssistState
id|u32
id|AssistState
suffix:semicolon
DECL|member|pad7
id|u32
id|pad7
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 0x120 */
DECL|member|CpuCtrl
id|u32
id|CpuCtrl
suffix:semicolon
multiline_comment|/* 0x140 */
DECL|member|Pc
id|u32
id|Pc
suffix:semicolon
DECL|member|pad8
id|u32
id|pad8
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|SramAddr
id|u32
id|SramAddr
suffix:semicolon
multiline_comment|/* 0x154 */
DECL|member|SramData
id|u32
id|SramData
suffix:semicolon
DECL|member|pad9
id|u32
id|pad9
(braket
l_int|49
)braket
suffix:semicolon
DECL|member|MacRxState
id|u32
id|MacRxState
suffix:semicolon
multiline_comment|/* 0x220 */
DECL|member|pad10
id|u32
id|pad10
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|CpuBCtrl
id|u32
id|CpuBCtrl
suffix:semicolon
multiline_comment|/* 0x240 */
DECL|member|PcB
id|u32
id|PcB
suffix:semicolon
DECL|member|pad11
id|u32
id|pad11
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|SramBAddr
id|u32
id|SramBAddr
suffix:semicolon
multiline_comment|/* 0x254 */
DECL|member|SramBData
id|u32
id|SramBData
suffix:semicolon
DECL|member|pad12
id|u32
id|pad12
(braket
l_int|105
)braket
suffix:semicolon
DECL|member|pad13
id|u32
id|pad13
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* 0x400 */
DECL|member|Stats
id|u32
id|Stats
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|Mb0Hi
id|u32
id|Mb0Hi
suffix:semicolon
multiline_comment|/* 0x500 */
DECL|member|Mb0Lo
id|u32
id|Mb0Lo
suffix:semicolon
DECL|member|Mb1Hi
id|u32
id|Mb1Hi
suffix:semicolon
DECL|member|CmdPrd
id|u32
id|CmdPrd
suffix:semicolon
DECL|member|Mb2Hi
id|u32
id|Mb2Hi
suffix:semicolon
DECL|member|TxPrd
id|u32
id|TxPrd
suffix:semicolon
DECL|member|Mb3Hi
id|u32
id|Mb3Hi
suffix:semicolon
DECL|member|Mb3Lo
id|u32
id|Mb3Lo
suffix:semicolon
DECL|member|Mb4Hi
id|u32
id|Mb4Hi
suffix:semicolon
DECL|member|Mb4Lo
id|u32
id|Mb4Lo
suffix:semicolon
DECL|member|Mb5Hi
id|u32
id|Mb5Hi
suffix:semicolon
DECL|member|Mb5Lo
id|u32
id|Mb5Lo
suffix:semicolon
DECL|member|Mb6Hi
id|u32
id|Mb6Hi
suffix:semicolon
DECL|member|Mb6Lo
id|u32
id|Mb6Lo
suffix:semicolon
DECL|member|Mb7Hi
id|u32
id|Mb7Hi
suffix:semicolon
DECL|member|Mb7Lo
id|u32
id|Mb7Lo
suffix:semicolon
DECL|member|Mb8Hi
id|u32
id|Mb8Hi
suffix:semicolon
DECL|member|Mb8Lo
id|u32
id|Mb8Lo
suffix:semicolon
DECL|member|Mb9Hi
id|u32
id|Mb9Hi
suffix:semicolon
DECL|member|Mb9Lo
id|u32
id|Mb9Lo
suffix:semicolon
DECL|member|MbAHi
id|u32
id|MbAHi
suffix:semicolon
DECL|member|MbALo
id|u32
id|MbALo
suffix:semicolon
DECL|member|MbBHi
id|u32
id|MbBHi
suffix:semicolon
DECL|member|MbBLo
id|u32
id|MbBLo
suffix:semicolon
DECL|member|MbCHi
id|u32
id|MbCHi
suffix:semicolon
DECL|member|MbCLo
id|u32
id|MbCLo
suffix:semicolon
DECL|member|MbDHi
id|u32
id|MbDHi
suffix:semicolon
DECL|member|MbDLo
id|u32
id|MbDLo
suffix:semicolon
DECL|member|MbEHi
id|u32
id|MbEHi
suffix:semicolon
DECL|member|MbELo
id|u32
id|MbELo
suffix:semicolon
DECL|member|MbFHi
id|u32
id|MbFHi
suffix:semicolon
DECL|member|MbFLo
id|u32
id|MbFLo
suffix:semicolon
DECL|member|pad14
id|u32
id|pad14
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|MacAddrHi
id|u32
id|MacAddrHi
suffix:semicolon
multiline_comment|/* 0x600 */
DECL|member|MacAddrLo
id|u32
id|MacAddrLo
suffix:semicolon
DECL|member|InfoPtrHi
id|u32
id|InfoPtrHi
suffix:semicolon
DECL|member|InfoPtrLo
id|u32
id|InfoPtrLo
suffix:semicolon
DECL|member|MultiCastHi
id|u32
id|MultiCastHi
suffix:semicolon
multiline_comment|/* 0x610 */
DECL|member|MultiCastLo
id|u32
id|MultiCastLo
suffix:semicolon
DECL|member|ModeStat
id|u32
id|ModeStat
suffix:semicolon
DECL|member|DmaReadCfg
id|u32
id|DmaReadCfg
suffix:semicolon
DECL|member|DmaWriteCfg
id|u32
id|DmaWriteCfg
suffix:semicolon
multiline_comment|/* 0x620 */
DECL|member|pad15
id|u32
id|pad15
suffix:semicolon
DECL|member|EvtCsm
id|u32
id|EvtCsm
suffix:semicolon
DECL|member|CmdCsm
id|u32
id|CmdCsm
suffix:semicolon
DECL|member|TuneRxCoalTicks
id|u32
id|TuneRxCoalTicks
suffix:semicolon
multiline_comment|/* 0x630 */
DECL|member|TuneTxCoalTicks
id|u32
id|TuneTxCoalTicks
suffix:semicolon
DECL|member|TuneStatTicks
id|u32
id|TuneStatTicks
suffix:semicolon
DECL|member|TuneMaxTxDesc
id|u32
id|TuneMaxTxDesc
suffix:semicolon
DECL|member|TuneMaxRxDesc
id|u32
id|TuneMaxRxDesc
suffix:semicolon
multiline_comment|/* 0x640 */
DECL|member|TuneTrace
id|u32
id|TuneTrace
suffix:semicolon
DECL|member|TuneLink
id|u32
id|TuneLink
suffix:semicolon
DECL|member|TuneFastLink
id|u32
id|TuneFastLink
suffix:semicolon
DECL|member|TracePtr
id|u32
id|TracePtr
suffix:semicolon
multiline_comment|/* 0x650 */
DECL|member|TraceStrt
id|u32
id|TraceStrt
suffix:semicolon
DECL|member|TraceLen
id|u32
id|TraceLen
suffix:semicolon
DECL|member|IfIdx
id|u32
id|IfIdx
suffix:semicolon
DECL|member|IfMtu
id|u32
id|IfMtu
suffix:semicolon
multiline_comment|/* 0x660 */
DECL|member|MaskInt
id|u32
id|MaskInt
suffix:semicolon
DECL|member|LnkState
id|u32
id|LnkState
suffix:semicolon
DECL|member|FastLnkState
id|u32
id|FastLnkState
suffix:semicolon
DECL|member|pad16
id|u32
id|pad16
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 0x670 */
DECL|member|RxRetCsm
id|u32
id|RxRetCsm
suffix:semicolon
multiline_comment|/* 0x680 */
DECL|member|pad17
id|u32
id|pad17
(braket
l_int|31
)braket
suffix:semicolon
DECL|member|CmdRng
id|u32
id|CmdRng
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* 0x700 */
DECL|member|Window
id|u32
id|Window
(braket
l_int|0x200
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ACE_WINDOW_SIZE
mdefine_line|#define ACE_WINDOW_SIZE&t;0x800
DECL|macro|ACE_JUMBO_MTU
mdefine_line|#define ACE_JUMBO_MTU 9000
DECL|macro|ACE_STD_MTU
mdefine_line|#define ACE_STD_MTU 1500
DECL|macro|ACE_TRACE_SIZE
mdefine_line|#define ACE_TRACE_SIZE 0x8000
multiline_comment|/*&n; * Host control register bits.&n; */
DECL|macro|IN_INT
mdefine_line|#define IN_INT&t;&t;0x01
DECL|macro|CLR_INT
mdefine_line|#define CLR_INT&t;&t;0x02
DECL|macro|BYTE_SWAP
mdefine_line|#define BYTE_SWAP&t;0x10
DECL|macro|WORD_SWAP
mdefine_line|#define WORD_SWAP&t;0x20
DECL|macro|MASK_INTS
mdefine_line|#define MASK_INTS&t;0x40
multiline_comment|/*&n; * Local control register bits.&n; */
DECL|macro|EEPROM_DATA_IN
mdefine_line|#define EEPROM_DATA_IN&t;&t;0x800000
DECL|macro|EEPROM_DATA_OUT
mdefine_line|#define EEPROM_DATA_OUT&t;&t;0x400000
DECL|macro|EEPROM_WRITE_ENABLE
mdefine_line|#define EEPROM_WRITE_ENABLE&t;0x200000
DECL|macro|EEPROM_CLK_OUT
mdefine_line|#define EEPROM_CLK_OUT&t;&t;0x100000
DECL|macro|EEPROM_BASE
mdefine_line|#define EEPROM_BASE&t;&t;0xa0000000
DECL|macro|EEPROM_WRITE_SELECT
mdefine_line|#define EEPROM_WRITE_SELECT&t;0xa0
DECL|macro|EEPROM_READ_SELECT
mdefine_line|#define EEPROM_READ_SELECT&t;0xa1
DECL|macro|SRAM_BANK_512K
mdefine_line|#define SRAM_BANK_512K&t;&t;0x200
multiline_comment|/*&n; * Misc Config bits&n; */
DECL|macro|SYNC_SRAM_TIMING
mdefine_line|#define SYNC_SRAM_TIMING&t;0x100000
multiline_comment|/*&n; * CPU state bits.&n; */
DECL|macro|CPU_RESET
mdefine_line|#define CPU_RESET&t;&t;0x01
DECL|macro|CPU_TRACE
mdefine_line|#define CPU_TRACE&t;&t;0x02
DECL|macro|CPU_PROM_FAILED
mdefine_line|#define CPU_PROM_FAILED&t;&t;0x10
DECL|macro|CPU_HALT
mdefine_line|#define CPU_HALT&t;&t;0x00010000
DECL|macro|CPU_HALTED
mdefine_line|#define CPU_HALTED&t;&t;0xffff0000
multiline_comment|/*&n; * PCI State bits.&n; */
DECL|macro|DMA_READ_MAX_4
mdefine_line|#define DMA_READ_MAX_4&t;&t;0x04
DECL|macro|DMA_READ_MAX_16
mdefine_line|#define DMA_READ_MAX_16&t;&t;0x08
DECL|macro|DMA_READ_MAX_32
mdefine_line|#define DMA_READ_MAX_32&t;&t;0x0c
DECL|macro|DMA_READ_MAX_64
mdefine_line|#define DMA_READ_MAX_64&t;&t;0x10
DECL|macro|DMA_READ_MAX_128
mdefine_line|#define DMA_READ_MAX_128&t;0x14
DECL|macro|DMA_READ_MAX_256
mdefine_line|#define DMA_READ_MAX_256&t;0x18
DECL|macro|DMA_READ_MAX_1K
mdefine_line|#define DMA_READ_MAX_1K&t;&t;0x1c
DECL|macro|DMA_WRITE_MAX_4
mdefine_line|#define DMA_WRITE_MAX_4&t;&t;0x20
DECL|macro|DMA_WRITE_MAX_16
mdefine_line|#define DMA_WRITE_MAX_16&t;0x40
DECL|macro|DMA_WRITE_MAX_32
mdefine_line|#define DMA_WRITE_MAX_32&t;0x60
DECL|macro|DMA_WRITE_MAX_64
mdefine_line|#define DMA_WRITE_MAX_64&t;0x80
DECL|macro|DMA_WRITE_MAX_128
mdefine_line|#define DMA_WRITE_MAX_128&t;0xa0
DECL|macro|DMA_WRITE_MAX_256
mdefine_line|#define DMA_WRITE_MAX_256&t;0xc0
DECL|macro|DMA_WRITE_MAX_1K
mdefine_line|#define DMA_WRITE_MAX_1K&t;0xe0
DECL|macro|MEM_READ_MULTIPLE
mdefine_line|#define MEM_READ_MULTIPLE&t;0x00020000
DECL|macro|DMA_WRITE_ALL_ALIGN
mdefine_line|#define DMA_WRITE_ALL_ALIGN&t;0x00800000
DECL|macro|READ_CMD_MEM
mdefine_line|#define READ_CMD_MEM&t;&t;0x06000000
DECL|macro|WRITE_CMD_MEM
mdefine_line|#define WRITE_CMD_MEM&t;&t;0x70000000
multiline_comment|/*&n; * Mode status&n; */
DECL|macro|ACE_BYTE_SWAP_DATA
mdefine_line|#define ACE_BYTE_SWAP_DATA&t;0x10
DECL|macro|ACE_WARN
mdefine_line|#define ACE_WARN&t;&t;0x08
DECL|macro|ACE_WORD_SWAP
mdefine_line|#define ACE_WORD_SWAP&t;&t;0x04
DECL|macro|ACE_FATAL
mdefine_line|#define ACE_FATAL&t;&t;0x40000000
multiline_comment|/*&n; * DMA config&n; */
DECL|macro|DMA_THRESH_8W
mdefine_line|#define DMA_THRESH_8W&t;&t;0x80;
multiline_comment|/*&n; * Tuning parameters&n; */
DECL|macro|TICKS_PER_SEC
mdefine_line|#define TICKS_PER_SEC&t;&t;1000000
multiline_comment|/*&n; * Link bits&n; */
DECL|macro|LNK_PREF
mdefine_line|#define LNK_PREF&t;&t;0x00008000
DECL|macro|LNK_10MB
mdefine_line|#define LNK_10MB&t;&t;0x00010000
DECL|macro|LNK_100MB
mdefine_line|#define LNK_100MB&t;&t;0x00020000
DECL|macro|LNK_1000MB
mdefine_line|#define LNK_1000MB&t;&t;0x00040000
DECL|macro|LNK_FULL_DUPLEX
mdefine_line|#define LNK_FULL_DUPLEX&t;&t;0x00080000
DECL|macro|LNK_HALF_DUPLEX
mdefine_line|#define LNK_HALF_DUPLEX&t;&t;0x00100000
DECL|macro|LNK_TX_FLOW_CTL_Y
mdefine_line|#define LNK_TX_FLOW_CTL_Y&t;0x00200000
DECL|macro|LNK_NEG_ADVANCED
mdefine_line|#define LNK_NEG_ADVANCED&t;0x00400000
DECL|macro|LNK_RX_FLOW_CTL_Y
mdefine_line|#define LNK_RX_FLOW_CTL_Y&t;0x00800000
DECL|macro|LNK_NIC
mdefine_line|#define LNK_NIC&t;&t;&t;0x01000000
DECL|macro|LNK_JAM
mdefine_line|#define LNK_JAM&t;&t;&t;0x02000000
DECL|macro|LNK_JUMBO
mdefine_line|#define LNK_JUMBO&t;&t;0x04000000
DECL|macro|LNK_ALTEON
mdefine_line|#define LNK_ALTEON&t;&t;0x08000000
DECL|macro|LNK_NEG_FCTL
mdefine_line|#define LNK_NEG_FCTL&t;&t;0x10000000
DECL|macro|LNK_NEGOTIATE
mdefine_line|#define LNK_NEGOTIATE&t;&t;0x20000000
DECL|macro|LNK_ENABLE
mdefine_line|#define LNK_ENABLE&t;&t;0x40000000
DECL|macro|LNK_UP
mdefine_line|#define LNK_UP&t;&t;&t;0x80000000
multiline_comment|/*&n; * Event definitions&n; */
DECL|macro|EVT_RING_ENTRIES
mdefine_line|#define EVT_RING_ENTRIES&t;256
DECL|macro|EVT_RING_SIZE
mdefine_line|#define EVT_RING_SIZE&t;(EVT_RING_ENTRIES * sizeof(struct event))
DECL|struct|event
r_struct
id|event
(brace
macro_line|#ifdef __LITTLE_ENDIAN
DECL|member|idx
id|u32
id|idx
suffix:colon
l_int|12
suffix:semicolon
DECL|member|code
id|u32
id|code
suffix:colon
l_int|12
suffix:semicolon
DECL|member|evt
id|u32
id|evt
suffix:colon
l_int|8
suffix:semicolon
macro_line|#else
id|u32
id|evt
suffix:colon
l_int|8
suffix:semicolon
id|u32
id|code
suffix:colon
l_int|12
suffix:semicolon
id|u32
id|idx
suffix:colon
l_int|12
suffix:semicolon
macro_line|#endif
DECL|member|pad
id|u32
id|pad
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Events&n; */
DECL|macro|E_FW_RUNNING
mdefine_line|#define E_FW_RUNNING&t;&t;0x01
DECL|macro|E_STATS_UPDATED
mdefine_line|#define E_STATS_UPDATED&t;&t;0x04
DECL|macro|E_STATS_UPDATE
mdefine_line|#define E_STATS_UPDATE&t;&t;0x04
DECL|macro|E_LNK_STATE
mdefine_line|#define E_LNK_STATE&t;&t;0x06
DECL|macro|E_C_LINK_UP
mdefine_line|#define E_C_LINK_UP&t;&t;0x01
DECL|macro|E_C_LINK_DOWN
mdefine_line|#define E_C_LINK_DOWN&t;&t;0x02
DECL|macro|E_ERROR
mdefine_line|#define E_ERROR&t;&t;&t;0x07
DECL|macro|E_C_ERR_INVAL_CMD
mdefine_line|#define E_C_ERR_INVAL_CMD&t;0x01
DECL|macro|E_C_ERR_UNIMP_CMD
mdefine_line|#define E_C_ERR_UNIMP_CMD&t;0x02
DECL|macro|E_C_ERR_BAD_CFG
mdefine_line|#define E_C_ERR_BAD_CFG&t;&t;0x03
DECL|macro|E_MCAST_LIST
mdefine_line|#define E_MCAST_LIST&t;&t;0x08
DECL|macro|E_C_MCAST_ADDR_ADD
mdefine_line|#define E_C_MCAST_ADDR_ADD&t;0x01
DECL|macro|E_C_MCAST_ADDR_DEL
mdefine_line|#define E_C_MCAST_ADDR_DEL&t;0x02
DECL|macro|E_RESET_JUMBO_RNG
mdefine_line|#define E_RESET_JUMBO_RNG&t;0x09
multiline_comment|/*&n; * Commands&n; */
DECL|macro|CMD_RING_ENTRIES
mdefine_line|#define CMD_RING_ENTRIES&t;64
DECL|struct|cmd
r_struct
id|cmd
(brace
macro_line|#ifdef __LITTLE_ENDIAN
DECL|member|idx
id|u32
id|idx
suffix:colon
l_int|12
suffix:semicolon
DECL|member|code
id|u32
id|code
suffix:colon
l_int|12
suffix:semicolon
DECL|member|evt
id|u32
id|evt
suffix:colon
l_int|8
suffix:semicolon
macro_line|#else
id|u32
id|evt
suffix:colon
l_int|8
suffix:semicolon
id|u32
id|code
suffix:colon
l_int|12
suffix:semicolon
id|u32
id|idx
suffix:colon
l_int|12
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|C_HOST_STATE
mdefine_line|#define C_HOST_STATE&t;&t;0x01
DECL|macro|C_C_STACK_UP
mdefine_line|#define C_C_STACK_UP&t;&t;0x01
DECL|macro|C_C_STACK_DOWN
mdefine_line|#define C_C_STACK_DOWN&t;&t;0x02
DECL|macro|C_FDR_FILTERING
mdefine_line|#define C_FDR_FILTERING&t;&t;0x02
DECL|macro|C_C_FDR_FILT_ENABLE
mdefine_line|#define C_C_FDR_FILT_ENABLE&t;0x01
DECL|macro|C_C_FDR_FILT_DISABLE
mdefine_line|#define C_C_FDR_FILT_DISABLE&t;0x02
DECL|macro|C_SET_RX_PRD_IDX
mdefine_line|#define C_SET_RX_PRD_IDX&t;0x03
DECL|macro|C_UPDATE_STATS
mdefine_line|#define C_UPDATE_STATS&t;&t;0x04
DECL|macro|C_RESET_JUMBO_RNG
mdefine_line|#define C_RESET_JUMBO_RNG&t;0x05
DECL|macro|C_ADD_MULTICAST_ADDR
mdefine_line|#define C_ADD_MULTICAST_ADDR&t;0x08
DECL|macro|C_DEL_MULTICAST_ADDR
mdefine_line|#define C_DEL_MULTICAST_ADDR&t;0x09
DECL|macro|C_SET_PROMISC_MODE
mdefine_line|#define C_SET_PROMISC_MODE&t;0x0a
DECL|macro|C_C_PROMISC_ENABLE
mdefine_line|#define C_C_PROMISC_ENABLE&t;0x01
DECL|macro|C_C_PROMISC_DISABLE
mdefine_line|#define C_C_PROMISC_DISABLE&t;0x02
DECL|macro|C_LNK_NEGOTIATION
mdefine_line|#define C_LNK_NEGOTIATION&t;0x0b
DECL|macro|C_SET_MAC_ADDR
mdefine_line|#define C_SET_MAC_ADDR&t;&t;0x0c
DECL|macro|C_CLEAR_PROFILE
mdefine_line|#define C_CLEAR_PROFILE&t;&t;0x0d
DECL|macro|C_SET_MULTICAST_MODE
mdefine_line|#define C_SET_MULTICAST_MODE&t;0x0e
DECL|macro|C_C_MCAST_ENABLE
mdefine_line|#define C_C_MCAST_ENABLE&t;0x01
DECL|macro|C_C_MCAST_DISABLE
mdefine_line|#define C_C_MCAST_DISABLE&t;0x02
DECL|macro|C_CLEAR_STATS
mdefine_line|#define C_CLEAR_STATS&t;&t;0x0f
DECL|macro|C_SET_RX_JUMBO_PRD_IDX
mdefine_line|#define C_SET_RX_JUMBO_PRD_IDX&t;0x10
DECL|macro|C_REFRESH_STATS
mdefine_line|#define C_REFRESH_STATS&t;&t;0x11
multiline_comment|/*&n; * Descriptor types.&n; */
DECL|macro|DESC_TX
mdefine_line|#define DESC_TX&t;&t;&t;0x01
DECL|macro|DESC_RX
mdefine_line|#define DESC_RX&t;&t;&t;0x02
DECL|macro|DESC_END
mdefine_line|#define DESC_END&t;&t;0x04
DECL|macro|DESC_MORE
mdefine_line|#define DESC_MORE&t;&t;0x08
multiline_comment|/*&n; * RX control block flags&n; */
DECL|macro|RX_TCP_UDP_SUM
mdefine_line|#define RX_TCP_UDP_SUM&t;&t;0x01
DECL|macro|RX_IP_SUM
mdefine_line|#define RX_IP_SUM&t;&t;0x02
DECL|macro|RX_SPLIT_HDRS
mdefine_line|#define RX_SPLIT_HDRS&t;&t;0x04
DECL|macro|RX_NO_PSEUDO_HDR_SUM
mdefine_line|#define RX_NO_PSEUDO_HDR_SUM&t;0x08
multiline_comment|/*&n; * Descriptor flags&n; */
DECL|macro|JUMBO_FLAG
mdefine_line|#define JUMBO_FLAG&t;&t;0x10
multiline_comment|/*&n; * TX ring&n; */
DECL|macro|TX_RING_ENTRIES
mdefine_line|#define TX_RING_ENTRIES&t;128
DECL|macro|TX_RING_SIZE
mdefine_line|#define TX_RING_SIZE&t;(TX_RING_ENTRIES * sizeof(struct tx_desc))
DECL|macro|TX_RING_BASE
mdefine_line|#define TX_RING_BASE&t;0x3800
DECL|struct|tx_desc
r_struct
id|tx_desc
(brace
macro_line|#if (BITS_PER_LONG == 64)
DECL|member|addr
id|u64
id|addr
suffix:semicolon
macro_line|#else
id|u32
id|zero
suffix:semicolon
id|u32
id|addr
suffix:semicolon
macro_line|#endif
macro_line|#if __LITTLE_ENDIAN
DECL|member|flags
id|u16
id|flags
suffix:semicolon
DECL|member|size
id|u16
id|size
suffix:semicolon
macro_line|#else
DECL|member|size
id|u16
id|size
suffix:semicolon
DECL|member|flags
id|u16
id|flags
suffix:semicolon
macro_line|#endif
DECL|member|nic_addr
id|u32
id|nic_addr
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RX_STD_RING_ENTRIES
mdefine_line|#define RX_STD_RING_ENTRIES&t;512
DECL|macro|RX_STD_RING_SIZE
mdefine_line|#define RX_STD_RING_SIZE&t;(RX_STD_RING_ENTRIES * sizeof(struct rx_desc))
DECL|macro|RX_JUMBO_RING_ENTRIES
mdefine_line|#define RX_JUMBO_RING_ENTRIES&t;256
DECL|macro|RX_JUMBO_RING_SIZE
mdefine_line|#define RX_JUMBO_RING_SIZE&t;(RX_JUMBO_RING_ENTRIES *sizeof(struct rx_desc))
DECL|macro|RX_RETURN_RING_ENTRIES
mdefine_line|#define RX_RETURN_RING_ENTRIES&t;(2 * RX_STD_RING_ENTRIES)
DECL|macro|RX_RETURN_RING_SIZE
mdefine_line|#define RX_RETURN_RING_SIZE&t;(RX_RETURN_RING_ENTRIES * &bslash;&n;&t;&t;&t;&t; sizeof(struct rx_desc))
DECL|macro|RX_RING_THRESH
mdefine_line|#define RX_RING_THRESH&t;&t;32
DECL|struct|rx_desc
r_struct
id|rx_desc
(brace
macro_line|#if (BITS_PER_LONG == 64)
DECL|member|addr
id|u64
id|addr
suffix:semicolon
macro_line|#else
id|u32
id|zero
suffix:semicolon
id|u32
id|addr
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __LITTLE_ENDIAN
DECL|member|size
id|u16
id|size
suffix:semicolon
DECL|member|idx
id|u16
id|idx
suffix:semicolon
macro_line|#else
DECL|member|idx
id|u16
id|idx
suffix:semicolon
DECL|member|size
id|u16
id|size
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __LITTLE_ENDIAN
DECL|member|flags
id|u16
id|flags
suffix:semicolon
DECL|member|type
id|u16
id|type
suffix:semicolon
macro_line|#else
DECL|member|type
id|u16
id|type
suffix:semicolon
DECL|member|flags
id|u16
id|flags
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __LITTLE_ENDIAN
DECL|member|tcp_udp_csum
id|u16
id|tcp_udp_csum
suffix:semicolon
DECL|member|ip_csum
id|u16
id|ip_csum
suffix:semicolon
macro_line|#else
DECL|member|ip_csum
id|u16
id|ip_csum
suffix:semicolon
DECL|member|tcp_udp_csum
id|u16
id|tcp_udp_csum
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __LITTLE_ENDIAN
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
DECL|member|err_flags
id|u16
id|err_flags
suffix:semicolon
macro_line|#else
DECL|member|err_flags
id|u16
id|err_flags
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
macro_line|#endif
DECL|member|nic_addr
id|u32
id|nic_addr
suffix:semicolon
DECL|member|pad
id|u32
id|pad
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This struct is shared with the NIC firmware.&n; */
DECL|struct|ring_ctrl
r_struct
id|ring_ctrl
(brace
macro_line|#if (BITS_PER_LONG == 64)
DECL|member|rngptr
id|u64
id|rngptr
suffix:semicolon
macro_line|#else
id|u32
id|zero
suffix:semicolon
id|u32
id|rngptr
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __LITTLE_ENDIAN
DECL|member|flags
id|u16
id|flags
suffix:semicolon
DECL|member|max_len
id|u16
id|max_len
suffix:semicolon
macro_line|#else
DECL|member|max_len
id|u16
id|max_len
suffix:semicolon
DECL|member|flags
id|u16
id|flags
suffix:semicolon
macro_line|#endif
DECL|member|pad
id|u32
id|pad
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ace_mac_stats
r_struct
id|ace_mac_stats
(brace
DECL|member|excess_colls
id|u32
id|excess_colls
suffix:semicolon
DECL|member|coll_1
id|u32
id|coll_1
suffix:semicolon
DECL|member|coll_2
id|u32
id|coll_2
suffix:semicolon
DECL|member|coll_3
id|u32
id|coll_3
suffix:semicolon
DECL|member|coll_4
id|u32
id|coll_4
suffix:semicolon
DECL|member|coll_5
id|u32
id|coll_5
suffix:semicolon
DECL|member|coll_6
id|u32
id|coll_6
suffix:semicolon
DECL|member|coll_7
id|u32
id|coll_7
suffix:semicolon
DECL|member|coll_8
id|u32
id|coll_8
suffix:semicolon
DECL|member|coll_9
id|u32
id|coll_9
suffix:semicolon
DECL|member|coll_10
id|u32
id|coll_10
suffix:semicolon
DECL|member|coll_11
id|u32
id|coll_11
suffix:semicolon
DECL|member|coll_12
id|u32
id|coll_12
suffix:semicolon
DECL|member|coll_13
id|u32
id|coll_13
suffix:semicolon
DECL|member|coll_14
id|u32
id|coll_14
suffix:semicolon
DECL|member|coll_15
id|u32
id|coll_15
suffix:semicolon
DECL|member|late_coll
id|u32
id|late_coll
suffix:semicolon
DECL|member|defers
id|u32
id|defers
suffix:semicolon
DECL|member|crc_err
id|u32
id|crc_err
suffix:semicolon
DECL|member|underrun
id|u32
id|underrun
suffix:semicolon
DECL|member|crs_err
id|u32
id|crs_err
suffix:semicolon
DECL|member|pad
id|u32
id|pad
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|drop_ula
id|u32
id|drop_ula
suffix:semicolon
DECL|member|drop_mc
id|u32
id|drop_mc
suffix:semicolon
DECL|member|drop_fc
id|u32
id|drop_fc
suffix:semicolon
DECL|member|drop_space
id|u32
id|drop_space
suffix:semicolon
DECL|member|coll
id|u32
id|coll
suffix:semicolon
DECL|member|kept_bc
id|u32
id|kept_bc
suffix:semicolon
DECL|member|kept_mc
id|u32
id|kept_mc
suffix:semicolon
DECL|member|kept_uc
id|u32
id|kept_uc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ace_info
r_struct
id|ace_info
(brace
r_union
(brace
DECL|member|stats
id|u32
id|stats
(braket
l_int|256
)braket
suffix:semicolon
DECL|member|s
)brace
id|s
suffix:semicolon
DECL|member|evt_ctrl
r_struct
id|ring_ctrl
id|evt_ctrl
suffix:semicolon
DECL|member|cmd_ctrl
r_struct
id|ring_ctrl
id|cmd_ctrl
suffix:semicolon
DECL|member|tx_ctrl
r_struct
id|ring_ctrl
id|tx_ctrl
suffix:semicolon
DECL|member|rx_std_ctrl
r_struct
id|ring_ctrl
id|rx_std_ctrl
suffix:semicolon
DECL|member|rx_jumbo_ctrl
r_struct
id|ring_ctrl
id|rx_jumbo_ctrl
suffix:semicolon
DECL|member|rx_return_ctrl
r_struct
id|ring_ctrl
id|rx_return_ctrl
suffix:semicolon
macro_line|#if (BITS_PER_LONG == 64)
DECL|member|evt_prd_ptr
id|u64
id|evt_prd_ptr
suffix:semicolon
DECL|member|rx_ret_prd_ptr
id|u64
id|rx_ret_prd_ptr
suffix:semicolon
DECL|member|tx_csm_ptr
id|u64
id|tx_csm_ptr
suffix:semicolon
DECL|member|stats2_ptr
id|u64
id|stats2_ptr
suffix:semicolon
macro_line|#else
DECL|member|evt_prd_ptr_hi
id|u32
id|evt_prd_ptr_hi
suffix:semicolon
DECL|member|evt_prd_ptr
id|u32
id|evt_prd_ptr
suffix:semicolon
DECL|member|rx_ret_prd_ptr_hi
id|u32
id|rx_ret_prd_ptr_hi
suffix:semicolon
DECL|member|rx_ret_prd_ptr
id|u32
id|rx_ret_prd_ptr
suffix:semicolon
DECL|member|tx_csm_ptr_hi
id|u32
id|tx_csm_ptr_hi
suffix:semicolon
DECL|member|tx_csm_ptr
id|u32
id|tx_csm_ptr
suffix:semicolon
DECL|member|stats2_ptr_hi
id|u32
id|stats2_ptr_hi
suffix:semicolon
DECL|member|stats2_ptr
id|u32
id|stats2_ptr
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/*&n; * Struct private for the AceNIC.&n; */
DECL|struct|ace_private
r_struct
id|ace_private
(brace
DECL|member|regs
r_struct
id|ace_regs
op_star
id|regs
suffix:semicolon
multiline_comment|/* register base */
DECL|member|sgt
r_volatile
id|__u32
op_star
id|sgt
suffix:semicolon
DECL|member|pkt_buf
r_struct
id|sk_buff
op_star
id|pkt_buf
suffix:semicolon
multiline_comment|/* Receive buffer */
multiline_comment|/*&n; * The send ring is located in the shared memory window&n; */
DECL|member|tx_ring
r_struct
id|tx_desc
op_star
id|tx_ring
suffix:semicolon
DECL|member|rx_std_ring
r_struct
id|rx_desc
id|rx_std_ring
(braket
id|RX_STD_RING_ENTRIES
)braket
suffix:semicolon
DECL|member|rx_jumbo_ring
r_struct
id|rx_desc
id|rx_jumbo_ring
(braket
id|RX_JUMBO_RING_ENTRIES
)braket
suffix:semicolon
DECL|member|rx_return_ring
r_struct
id|rx_desc
id|rx_return_ring
(braket
id|RX_RETURN_RING_ENTRIES
)braket
suffix:semicolon
DECL|member|evt_ring
r_struct
id|event
id|evt_ring
(braket
id|EVT_RING_ENTRIES
)braket
suffix:semicolon
DECL|member|info
r_struct
id|ace_info
op_star
id|info
suffix:semicolon
DECL|member|tx_skbuff
r_struct
id|sk_buff
op_star
id|tx_skbuff
(braket
id|TX_RING_ENTRIES
)braket
suffix:semicolon
DECL|member|rx_std_skbuff
r_struct
id|sk_buff
op_star
id|rx_std_skbuff
(braket
id|RX_STD_RING_ENTRIES
)braket
suffix:semicolon
DECL|member|rx_jumbo_skbuff
r_struct
id|sk_buff
op_star
id|rx_jumbo_skbuff
(braket
id|RX_JUMBO_RING_ENTRIES
)braket
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|cur_rx
DECL|member|tx_prd
id|u32
id|cur_rx
comma
id|tx_prd
suffix:semicolon
DECL|member|dirty_rx
DECL|member|tx_ret_csm
DECL|member|dirty_event
id|u32
id|dirty_rx
comma
id|tx_ret_csm
comma
id|dirty_event
suffix:semicolon
DECL|member|rx_std_skbprd
DECL|member|rx_jumbo_skbprd
id|u32
id|rx_std_skbprd
comma
id|rx_jumbo_skbprd
suffix:semicolon
DECL|member|tx_full
id|u32
id|tx_full
suffix:semicolon
DECL|member|evt_prd
r_volatile
id|u32
id|evt_prd
id|__attribute__
(paren
(paren
id|aligned
(paren
id|L1_CACHE_BYTES
)paren
)paren
)paren
suffix:semicolon
DECL|member|rx_ret_prd
r_volatile
id|u32
id|rx_ret_prd
id|__attribute__
(paren
(paren
id|aligned
(paren
id|L1_CACHE_BYTES
)paren
)paren
)paren
suffix:semicolon
DECL|member|tx_csm
r_volatile
id|u32
id|tx_csm
id|__attribute__
(paren
(paren
id|aligned
(paren
id|L1_CACHE_BYTES
)paren
)paren
)paren
suffix:semicolon
DECL|member|next
r_struct
id|device
op_star
id|next
id|__attribute__
(paren
(paren
id|aligned
(paren
id|L1_CACHE_BYTES
)paren
)paren
)paren
suffix:semicolon
DECL|member|trace_buf
r_int
r_char
op_star
id|trace_buf
suffix:semicolon
DECL|member|fw_running
DECL|member|fw_up
DECL|member|jumbo
DECL|member|promisc
r_int
id|fw_running
comma
id|fw_up
comma
id|jumbo
comma
id|promisc
suffix:semicolon
DECL|member|version
r_int
id|version
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|vendor
id|u16
id|vendor
suffix:semicolon
DECL|member|pci_command
id|u16
id|pci_command
suffix:semicolon
DECL|member|pdev
r_struct
id|pci_dev
op_star
id|pdev
suffix:semicolon
macro_line|#if 0
id|u8
id|pci_bus
suffix:semicolon
id|u8
id|pci_dev_fun
suffix:semicolon
macro_line|#endif
DECL|member|name
r_char
id|name
(braket
l_int|24
)braket
suffix:semicolon
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Prototypes&n; */
r_static
r_int
id|ace_init
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|board_idx
)paren
suffix:semicolon
r_static
r_int
id|ace_load_std_rx_ring
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|ace_load_jumbo_rx_ring
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|ace_flush_jumbo_rx_ring
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|ace_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
r_int
id|ace_open
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|ace_start_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|ace_close
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|ace_timer
c_func
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
r_static
r_void
id|ace_dump_trace
c_func
(paren
r_struct
id|ace_private
op_star
id|ap
)paren
suffix:semicolon
r_static
r_void
id|ace_set_multicast_list
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|ace_change_mtu
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|new_mtu
)paren
suffix:semicolon
r_static
r_int
id|ace_set_mac_addr
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|p
)paren
suffix:semicolon
r_static
r_struct
id|net_device_stats
op_star
id|ace_get_stats
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
id|u8
id|read_eeprom_byte
c_func
(paren
r_struct
id|ace_regs
op_star
id|regs
comma
r_int
r_int
id|offset
)paren
suffix:semicolon
macro_line|#endif /* _ACENIC_H_ */
eof
