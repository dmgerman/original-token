multiline_comment|/*&n; * hp100.h: Hewlett Packard HP10/100VG ANY LAN ethernet driver for Linux.&n; *&n; * Author:  Jaroslav Kysela, &lt;perex@pf.jcu.cz&gt;&n; *&n; * Header file...&n; *&n; * This driver is based on the &squot;hpfepkt&squot; crynwr packet driver.&n; *&n; * This source/code is public free; you can distribute it and/or modify &n; * it under terms of the GNU General Public License (published by the&n; * Free Software Foundation) either version two of this License, or any &n; * later version.&n; */
multiline_comment|/****************************************************************************&n; *  Hardware Constants&n; ****************************************************************************/
multiline_comment|/*&n; *  ATT2MD01 Register Page Constants&n; */
DECL|macro|HP100_PAGE_PERFORMANCE
mdefine_line|#define HP100_PAGE_PERFORMANCE&t;0x0&t;/* Page 0 */
DECL|macro|HP100_PAGE_MAC_ADDRESS
mdefine_line|#define HP100_PAGE_MAC_ADDRESS&t;0x1&t;/* Page 1 */
DECL|macro|HP100_PAGE_HW_MAP
mdefine_line|#define HP100_PAGE_HW_MAP&t;0x2&t;/* Page 2 */
DECL|macro|HP100_PAGE_EEPROM_CTRL
mdefine_line|#define HP100_PAGE_EEPROM_CTRL&t;0x3&t;/* Page 3 */
DECL|macro|HP100_PAGE_MAC_CTRL
mdefine_line|#define HP100_PAGE_MAC_CTRL&t;0x4&t;/* Page 4 */
DECL|macro|HP100_PAGE_MMU_CFG
mdefine_line|#define HP100_PAGE_MMU_CFG&t;0x5&t;/* Page 5 */
DECL|macro|HP100_PAGE_ID_MAC_ADDR
mdefine_line|#define HP100_PAGE_ID_MAC_ADDR&t;0x6&t;/* Page 6 */
DECL|macro|HP100_PAGE_MMU_POINTER
mdefine_line|#define HP100_PAGE_MMU_POINTER&t;0x7&t;/* Page 7 */
multiline_comment|/*&n; *  ATT2MD01 Register Addresses&n; */
multiline_comment|/*  Present on all pages  */
DECL|macro|HP100_REG_HW_ID
mdefine_line|#define HP100_REG_HW_ID&t;&t;0x00&t;/* R:  (16) Unique card ID           */
DECL|macro|HP100_REG_TRACE
mdefine_line|#define HP100_REG_TRACE&t;&t;0x00&t;/* W:  (16) Used for debug output    */
DECL|macro|HP100_REG_PAGING
mdefine_line|#define HP100_REG_PAGING&t;0x02&t;/* R:  (16),15:4 Card ID             */
multiline_comment|/* W:  (16),3:0 Switch pages         */
DECL|macro|HP100_REG_OPTION_LSW
mdefine_line|#define HP100_REG_OPTION_LSW&t;0x04&t;/* RW: (16) Select card functions    */
DECL|macro|HP100_REG_OPTION_MSW
mdefine_line|#define HP100_REG_OPTION_MSW&t;0x06&t;/* RW: (16) Select card functions    */
multiline_comment|/*  Page 0 - Performance  */
DECL|macro|HP100_REG_IRQ_STATUS
mdefine_line|#define HP100_REG_IRQ_STATUS&t;0x08&t;/* RW: (16) Which ints are pending   */
DECL|macro|HP100_REG_IRQ_MASK
mdefine_line|#define HP100_REG_IRQ_MASK&t;0x0a&t;/* RW: (16) Select ints to allow     */
DECL|macro|HP100_REG_FRAGMENT_LEN
mdefine_line|#define HP100_REG_FRAGMENT_LEN&t;0x0c&t;/* RW: (16)12:0 Current fragment len */
DECL|macro|HP100_REG_OFFSET
mdefine_line|#define HP100_REG_OFFSET&t;0x0e&t;/* RW: (16)12:0 Offset to start read */
DECL|macro|HP100_REG_DATA32
mdefine_line|#define HP100_REG_DATA32&t;0x10&t;/* RW: (32) I/O mode data port       */
DECL|macro|HP100_REG_DATA16
mdefine_line|#define HP100_REG_DATA16&t;0x12&t;/* RW: WORDs must be read from here  */
DECL|macro|HP100_REG_TX_MEM_FREE
mdefine_line|#define HP100_REG_TX_MEM_FREE&t;0x14&t;/* RD: (32) Amount of free Tx mem    */
DECL|macro|HP100_REG_RX_PKT_CNT
mdefine_line|#define HP100_REG_RX_PKT_CNT&t;0x18&t;/* RD: (8) Rx count of pkts on card  */
DECL|macro|HP100_REG_TX_PKT_CNT
mdefine_line|#define HP100_REG_TX_PKT_CNT&t;0x19&t;/* RD: (8) Tx count of pkts on card  */
multiline_comment|/*  Page 1 - MAC Address/Hash Table  */
DECL|macro|HP100_REG_MAC_ADDR
mdefine_line|#define HP100_REG_MAC_ADDR&t;0x08&t;/* RW: (8) Cards MAC address&t;     */
DECL|macro|HP100_REG_HASH_BYTE0
mdefine_line|#define HP100_REG_HASH_BYTE0&t;0x10&t;/* RW: (8) Cards multicast filter    */
multiline_comment|/*  Page 2 - Hardware Mapping  */
DECL|macro|HP100_REG_MEM_MAP_LSW
mdefine_line|#define HP100_REG_MEM_MAP_LSW&t;0x08&t;/* RW: (16) LSW of cards mem addr    */
DECL|macro|HP100_REG_MEM_MAP_MSW
mdefine_line|#define HP100_REG_MEM_MAP_MSW&t;0x0a&t;/* RW: (16) MSW of cards mem addr    */
DECL|macro|HP100_REG_IO_MAP
mdefine_line|#define HP100_REG_IO_MAP&t;0x0c&t;/* RW: (8) Cards I/O address         */
DECL|macro|HP100_REG_IRQ_CHANNEL
mdefine_line|#define HP100_REG_IRQ_CHANNEL&t;0x0d&t;/* RW: (8) IRQ and edge/level int    */
DECL|macro|HP100_REG_SRAM
mdefine_line|#define HP100_REG_SRAM&t;&t;0x0e&t;/* RW: (8) How much RAM on card      */
DECL|macro|HP100_REG_BM
mdefine_line|#define HP100_REG_BM&t;&t;0x0f&t;/* RW: (8) Controls BM functions     */
multiline_comment|/*  Page 3 - EEPROM/Boot ROM  */
DECL|macro|HP100_REG_EEPROM_CTRL
mdefine_line|#define HP100_REG_EEPROM_CTRL&t;0x08&t;/* RW: (16) Used to load EEPROM      */
multiline_comment|/*  Page 4 - LAN Configuration  */
DECL|macro|HP100_REG_LAN_CFG_10
mdefine_line|#define HP100_REG_LAN_CFG_10&t;0x08&t;/* RW: (16) Set 10M XCVR functions   */
DECL|macro|HP100_REG_LAN_CFG_VG
mdefine_line|#define HP100_REG_LAN_CFG_VG&t;0x0a&t;/* RW: (16) Set 100M XCVR functions  */
DECL|macro|HP100_REG_MAC_CFG_1
mdefine_line|#define HP100_REG_MAC_CFG_1&t;0x0c&t;/* RW: (8) Types of pkts to accept   */
DECL|macro|HP100_REG_MAC_CFG_2
mdefine_line|#define HP100_REG_MAC_CFG_2&t;0x0d&t;/* RW: (8) Misc MAC functions        */
multiline_comment|/* The follow clear when read: */
DECL|macro|HP100_REG_DROPPED
mdefine_line|#define HP100_REG_DROPPED&t;0x10&t;/* R:  (16),11:0 Pkts cant fit in mem*/
DECL|macro|HP100_REG_CRC
mdefine_line|#define HP100_REG_CRC&t;&t;0x12&t;/* R:  (8) Pkts with CRC             */
DECL|macro|HP100_REG_ABORT
mdefine_line|#define HP100_REG_ABORT&t;&t;0x13&t;/* R:  (8) Aborted Tx pkts           */
multiline_comment|/*  Page 5 - MMU  */
DECL|macro|HP100_REG_RX_MEM_STOP
mdefine_line|#define HP100_REG_RX_MEM_STOP&t;0x0c&t;/* RW: (16) End of Rx ring addr      */
DECL|macro|HP100_REG_TX_MEM_STOP
mdefine_line|#define HP100_REG_TX_MEM_STOP&t;0x0e&t;/* RW: (16) End of Tx ring addr      */
multiline_comment|/*  Page 6 - Card ID/Physical LAN Address  */
DECL|macro|HP100_REG_BOARD_ID
mdefine_line|#define HP100_REG_BOARD_ID&t;0x08&t;/* R:  (8) EISA/ISA card ID          */
DECL|macro|HP100_REG_BOARD_IO_CHCK
mdefine_line|#define HP100_REG_BOARD_IO_CHCK 0x0c&t;/* R:  (8) Added to ID to get FFh    */
DECL|macro|HP100_REG_SOFT_MODEL
mdefine_line|#define HP100_REG_SOFT_MODEL&t;0x0d&t;/* R:  (8) Config program defined    */
DECL|macro|HP100_REG_LAN_ADDR
mdefine_line|#define HP100_REG_LAN_ADDR&t;0x10&t;/* R:  (8) MAC addr of card          */
DECL|macro|HP100_REG_LAN_ADDR_CHCK
mdefine_line|#define HP100_REG_LAN_ADDR_CHCK 0x16&t;/* R:  (8) Added to addr to get FFh  */
multiline_comment|/*  Page 7 - MMU Current Pointers  */
DECL|macro|HP100_REG_RX_MEM_BR
mdefine_line|#define HP100_REG_RX_MEM_BR&t;0x08&t;/* R:  (16) Current begin of Rx ring */
DECL|macro|HP100_REG_RX_MEM_ER
mdefine_line|#define HP100_REG_RX_MEM_ER&t;0x0a&t;/* R:  (16) Current end of Rx ring   */
DECL|macro|HP100_REG_TX_MEM_BR
mdefine_line|#define HP100_REG_TX_MEM_BR&t;0x0c&t;/* R:  (16) Current begin of Tx ring */
DECL|macro|HP100_REG_TX_MEM_ER
mdefine_line|#define HP100_REG_TX_MEM_ER&t;0x0e&t;/* R:  (16) Current end of Rx ring   */
DECL|macro|HP100_REG_MEM_DEBUG
mdefine_line|#define HP100_REG_MEM_DEBUG&t;0x1a&t;/* RW: (16) Used for memory tests    */
multiline_comment|/*&n; *  HardwareIDReg bits/masks&n; */
DECL|macro|HP100_HW_ID_0
mdefine_line|#define HP100_HW_ID_0&t;&t;0x50&t;/* Hardware ID bytes.                */
DECL|macro|HP100_HW_ID_1
mdefine_line|#define HP100_HW_ID_1&t;&t;0x48
DECL|macro|HP100_HW_ID_2_REVA
mdefine_line|#define HP100_HW_ID_2_REVA&t;0x50&t;/* Rev. A ID. NOTE: lower nibble not used */
DECL|macro|HP100_HW_ID_3
mdefine_line|#define HP100_HW_ID_3&t;&t;0x53
multiline_comment|/*&n; *  OptionLSWReg bits/masks&n; */
DECL|macro|HP100_DEBUG_EN
mdefine_line|#define HP100_DEBUG_EN&t;&t;0x8000&t;/* 0:Disable, 1:Enable Debug Dump Pointer */
DECL|macro|HP100_RX_HDR
mdefine_line|#define HP100_RX_HDR&t;&t;0x4000&t;/* 0:Disable, 1:Enable putting pkt into */
multiline_comment|/*   system memory before Rx interrupt */
DECL|macro|HP100_MMAP_DIS
mdefine_line|#define HP100_MMAP_DIS&t;&t;0x2000&t;/* 0:Enable, 1:Disable memory mapping. */
multiline_comment|/*   MMAP_DIS must be 0 and MEM_EN must */
multiline_comment|/*   be 1 for memory-mapped mode to be */
multiline_comment|/*   enabled */
DECL|macro|HP100_EE_EN
mdefine_line|#define HP100_EE_EN&t;&t;0x1000&t;/* 0:Disable,1:Enable EEPROM writing */
DECL|macro|HP100_BM_WRITE
mdefine_line|#define HP100_BM_WRITE&t;&t;0x0800&t;/* 0:Slave, 1:Bus Master for Tx data */
DECL|macro|HP100_BM_READ
mdefine_line|#define HP100_BM_READ&t;&t;0x0400&t;/* 0:Slave, 1:Bus Master for Rx data */
DECL|macro|HP100_TRI_INT
mdefine_line|#define HP100_TRI_INT&t;&t;0x0200&t;/* 0:Dont, 1:Do tri-state the int */
DECL|macro|HP100_MEM_EN
mdefine_line|#define HP100_MEM_EN&t;&t;0x0040&t;/* Config program set this to */
multiline_comment|/*   0:Disable, 1:Enable mem map. */
multiline_comment|/*   See MMAP_DIS. */
DECL|macro|HP100_IO_EN
mdefine_line|#define HP100_IO_EN&t;&t;0x0020&t;/* 0:Disable, 1:Enable I/O transfers */
DECL|macro|HP100_BOOT_EN
mdefine_line|#define HP100_BOOT_EN&t;&t;0x0010&t;/* 0:Disable, 1:Enable boot ROM access */
DECL|macro|HP100_FAKE_INT
mdefine_line|#define HP100_FAKE_INT&t;&t;0x0008&t;/* 0:No int, 1:int */
DECL|macro|HP100_INT_EN
mdefine_line|#define HP100_INT_EN&t;&t;0x0004&t;/* 0:Disable, 1:Enable ints from card */
DECL|macro|HP100_HW_RST
mdefine_line|#define HP100_HW_RST&t;&t;0x0002&t;/* 0:Reset, 1:Out of reset */
multiline_comment|/*&n; *  OptionMSWReg bits/masks&n; */
DECL|macro|HP100_PRIORITY_TX
mdefine_line|#define HP100_PRIORITY_TX&t;0x0080&t;/* 0:Don&squot;t, 1:Do all Tx pkts as priority */
DECL|macro|HP100_EE_LOAD
mdefine_line|#define HP100_EE_LOAD&t;&t;0x0040&t;/* 1:EEPROM loading, 0 when done */
DECL|macro|HP100_ADV_NXT_PKT
mdefine_line|#define HP100_ADV_NXT_PKT&t;0x0004&t;/* 1:Advance to next pkt in Rx queue, */
multiline_comment|/*   h/w will set to 0 when done */
DECL|macro|HP100_TX_CMD
mdefine_line|#define HP100_TX_CMD&t;&t;0x0002&t;/* 1:Tell h/w download done, h/w will set */
multiline_comment|/*   to 0 when done */
multiline_comment|/*&n; *  InterruptStatusReg/InterruptMaskReg bits/masks.  These bits will 0 when a 1 &n; *  is written to them.&n; */
DECL|macro|HP100_RX_PACKET
mdefine_line|#define HP100_RX_PACKET&t;&t;0x0400&t;/* 0:No, 1:Yes pkt has been Rx */
DECL|macro|HP100_RX_ERROR
mdefine_line|#define HP100_RX_ERROR&t;&t;0x0200&t;/* 0:No, 1:Yes Rx pkt had error */
DECL|macro|HP100_TX_SPACE_AVAIL
mdefine_line|#define HP100_TX_SPACE_AVAIL&t;0x0010&t;/* 0:&lt;8192, 1:&gt;=8192 Tx free bytes */
DECL|macro|HP100_TX_COMPLETE
mdefine_line|#define HP100_TX_COMPLETE&t;0x0008&t;/* 0:No, 1:Yes a Tx has completed */
DECL|macro|HP100_TX_ERROR
mdefine_line|#define HP100_TX_ERROR&t;&t;0x0002&t;/* 0:No, 1:Yes Tx pkt had error */
multiline_comment|/*&n; *  TxMemoryFreeCountReg bits/masks.&n; */
DECL|macro|HP100_AUTO_COMPARE
mdefine_line|#define HP100_AUTO_COMPARE&t;0x8000&t;/* Says at least 8k is available for Tx. */
multiline_comment|/*   NOTE: This mask is for the upper */
multiline_comment|/*   word of the register. */
multiline_comment|/*&n; *  IRQChannelReg bits/masks.&n; */
DECL|macro|HP100_ZERO_WAIT_EN
mdefine_line|#define HP100_ZERO_WAIT_EN&t;0x80&t;/* 0:No, 1:Yes assers NOWS signal */
DECL|macro|HP100_LEVEL_IRQ
mdefine_line|#define HP100_LEVEL_IRQ&t;&t;0x10&t;/* 0:Edge, 1:Level type interrupts. */
multiline_comment|/*   Only valid on EISA cards. */
DECL|macro|HP100_IRQ_MASK
mdefine_line|#define HP100_IRQ_MASK&t;&t;0x0F&t;/* Isolate the IRQ bits */
multiline_comment|/*&n; *  SRAMReg bits/masks.&n; */
DECL|macro|HP100_RAM_SIZE_MASK
mdefine_line|#define HP100_RAM_SIZE_MASK&t;0xe0&t;/* AND to get SRAM size index */
DECL|macro|HP100_RAM_SIZE_SHIFT
mdefine_line|#define HP100_RAM_SIZE_SHIFT&t;0x05&t;/* Shift count to put index in lower bits */
multiline_comment|/*&n; *  BMReg bits/masks.&n; */
DECL|macro|HP100_BM_SLAVE
mdefine_line|#define HP100_BM_SLAVE&t;&t;0x04&t;/* 0:Slave, 1:BM mode */
multiline_comment|/*&n; *  EEPROMControlReg bits/masks.&n; */
DECL|macro|HP100_EEPROM_LOAD
mdefine_line|#define HP100_EEPROM_LOAD&t;0x0001&t;/* 0-&gt;1 loads the EEPROM into registers. */
multiline_comment|/*   When it goes back to 0, load is  */
multiline_comment|/*   complete.  This should take ~600us. */
multiline_comment|/*&n; *  LANCntrCfg10Reg bits/masks.&n; */
DECL|macro|HP100_SQU_ST
mdefine_line|#define HP100_SQU_ST&t;&t;0x0100&t;/* 0:No, 1:Yes collision signal sent */
multiline_comment|/*   after Tx.  Only used for AUI. */
DECL|macro|HP100_MAC10_SEL
mdefine_line|#define HP100_MAC10_SEL&t;&t;0x00c0&t;/* Get bits to indicate MAC */
DECL|macro|HP100_AUI_SEL
mdefine_line|#define HP100_AUI_SEL&t;&t;0x0020&t;/* Status of AUI selection */
DECL|macro|HP100_LOW_TH
mdefine_line|#define HP100_LOW_TH&t;&t;0x0010&t;/* 0:No, 1:Yes allow better cabling */
DECL|macro|HP100_LINK_BEAT_DIS
mdefine_line|#define HP100_LINK_BEAT_DIS&t;0x0008&t;/* 0:Enable, 1:Disable link beat */
DECL|macro|HP100_LINK_BEAT_ST
mdefine_line|#define HP100_LINK_BEAT_ST&t;0x0004&t;/* 0:No, 1:Yes link beat being Rx */
DECL|macro|HP100_R_ROL_ST
mdefine_line|#define HP100_R_ROL_ST&t;&t;0x0002&t;/* 0:No, 1:Yes Rx twisted pair has been */
multiline_comment|/*   reversed */
DECL|macro|HP100_AUI_ST
mdefine_line|#define HP100_AUI_ST&t;&t;0x0001&t;/* 0:No, 1:Yes use AUI on TP card */
multiline_comment|/* MAC Selection, use with MAC10_SEL bits */
DECL|macro|HP100_AUTO_SEL_10
mdefine_line|#define HP100_AUTO_SEL_10&t;0x0&t;/* Auto select */
DECL|macro|HP100_XCVR_LXT901_10
mdefine_line|#define HP100_XCVR_LXT901_10&t;0x1&t;/* LXT901 10BaseT transceiver */
DECL|macro|HP100_XCVR_7213
mdefine_line|#define HP100_XCVR_7213&t;&t;0x2&t;/* 7213 transceiver */
DECL|macro|HP100_XCVR_82503
mdefine_line|#define HP100_XCVR_82503&t;0x3&t;/* 82503 transceiver */
multiline_comment|/*&n; *  LANCntrCfgVGReg bits/masks.&n; */
DECL|macro|HP100_FRAME_FORMAT
mdefine_line|#define HP100_FRAME_FORMAT&t;0x0800&t;/* 0:802.3, 1:802.5 frames */
DECL|macro|HP100_BRIDGE
mdefine_line|#define HP100_BRIDGE&t;&t;0x0400&t;/* 0:No, 1:Yes tell hub it&squot;s a bridge */
DECL|macro|HP100_PROM_MODE
mdefine_line|#define HP100_PROM_MODE&t;&t;0x0200&t;/* 0:No, 1:Yes tell hub card is */
multiline_comment|/*   promiscuous */
DECL|macro|HP100_REPEATER
mdefine_line|#define HP100_REPEATER&t;&t;0x0100&t;/* 0:No, 1:Yes tell hub MAC wants to be */
multiline_comment|/*   a cascaded repeater */
DECL|macro|HP100_MAC100_SEL
mdefine_line|#define HP100_MAC100_SEL&t;0x0080&t;/* 0:No, 1:Yes use 100 Mbit MAC */
DECL|macro|HP100_LINK_UP_ST
mdefine_line|#define HP100_LINK_UP_ST&t;0x0040&t;/* 0:No, 1:Yes endnode logged in */
DECL|macro|HP100_LINK_CABLE_ST
mdefine_line|#define HP100_LINK_CABLE_ST&t;0x0020&t;/* 0:No, 1:Yes cable can hear tones from */
multiline_comment|/*   hub */
DECL|macro|HP100_LOAD_ADDR
mdefine_line|#define HP100_LOAD_ADDR&t;&t;0x0010&t;/* 0-&gt;1 card addr will be sent to hub. */
multiline_comment|/*   100ms later the link status bits are */
multiline_comment|/*   valid */
DECL|macro|HP100_LINK_CMD
mdefine_line|#define HP100_LINK_CMD&t;&t;0x0008&t;/* 0-&gt;1 link will attempt to log in. */
multiline_comment|/*   100ms later the link status bits are */
multiline_comment|/*   valid */
DECL|macro|HP100_LINK_GOOD_ST
mdefine_line|#define HP100_LINK_GOOD_ST&t;0x0002&t;/* 0:No, 1:Yes cable passed training */
DECL|macro|HP100_VG_RESET
mdefine_line|#define HP100_VG_RESET&t;&t;0x0001&t;/* 0:Yes, 1:No reset the 100VG MAC */
multiline_comment|/*&n; *  MACConfiguration1Reg bits/masks.&n; */
DECL|macro|HP100_RX_IDLE
mdefine_line|#define HP100_RX_IDLE&t;&t;0x80&t;/* 0:Yes, 1:No currently receiving pkts */
DECL|macro|HP100_TX_IDLE
mdefine_line|#define HP100_TX_IDLE&t;&t;0x40&t;/* 0:Yes, 1:No currently Txing pkts */
DECL|macro|HP100_RX_EN
mdefine_line|#define HP100_RX_EN&t;&t;0x20&t;/* 0:No, 1:Yes allow receiving of pkts */
DECL|macro|HP100_TX_EN
mdefine_line|#define HP100_TX_EN&t;&t;0x10&t;/* 0:No, 1:Yes allow transmiting of pkts */
DECL|macro|HP100_ACC_ERRORED
mdefine_line|#define HP100_ACC_ERRORED&t;0x08&t;/* 0:No, 1:Yes allow Rx of errored pkts */
DECL|macro|HP100_ACC_MC
mdefine_line|#define HP100_ACC_MC&t;&t;0x04&t;/* 0:No, 1:Yes allow Rx of multicast pkts */
DECL|macro|HP100_ACC_BC
mdefine_line|#define HP100_ACC_BC&t;&t;0x02&t;/* 0:No, 1:Yes allow Rx of broadcast pkts */
DECL|macro|HP100_ACC_PHY
mdefine_line|#define HP100_ACC_PHY&t;&t;0x01&t;/* 0:No, 1:Yes allow Rx of ALL physical pkts */
DECL|macro|HP100_MAC1MODEMASK
mdefine_line|#define HP100_MAC1MODEMASK&t;0xf0&t;/* Hide ACC bits */
DECL|macro|HP100_MAC1MODE1
mdefine_line|#define HP100_MAC1MODE1&t;&t;0x00&t;/* Receive nothing, must also disable RX */
DECL|macro|HP100_MAC1MODE2
mdefine_line|#define HP100_MAC1MODE2&t;&t;0x00
DECL|macro|HP100_MAC1MODE3
mdefine_line|#define HP100_MAC1MODE3&t;&t;HP100_MAC1MODE2 | HP100_ACC_BC
DECL|macro|HP100_MAC1MODE4
mdefine_line|#define HP100_MAC1MODE4&t;&t;HP100_MAC1MODE3 | HP100_ACC_MC
DECL|macro|HP100_MAC1MODE5
mdefine_line|#define HP100_MAC1MODE5&t;&t;HP100_MAC1MODE4 /* set mc hash to all ones also */
DECL|macro|HP100_MAC1MODE6
mdefine_line|#define HP100_MAC1MODE6&t;&t;HP100_MAC1MODE5 | HP100_ACC_PHY&t;/* Promiscuous */
multiline_comment|/* Note MODE6 will receive all GOOD packets on the LAN. This really needs&n;   a mode 7 defined to be LAN Analyzer mode, which will receive errored and&n;   runt packets, and keep the CRC bytes. */
DECL|macro|HP100_MAC1MODE7
mdefine_line|#define HP100_MAC1MODE7&t;&t;MAC1MODE6 OR ACC_ERRORED
multiline_comment|/*&n; *  MACConfiguration2Reg bits/masks.&n; */
DECL|macro|HP100_TR_MODE
mdefine_line|#define HP100_TR_MODE&t;&t;0x80&t;/* 0:No, 1:Yes support Token Ring formats */
DECL|macro|HP100_TX_SAME
mdefine_line|#define HP100_TX_SAME&t;&t;0x40&t;/* 0:No, 1:Yes Tx same packet continuous */
DECL|macro|HP100_LBK_XCVR
mdefine_line|#define HP100_LBK_XCVR&t;&t;0x20&t;/* 0:No, 1:Yes loopback through MAC &amp; */
multiline_comment|/*   transceiver */
DECL|macro|HP100_LBK_MAC
mdefine_line|#define HP100_LBK_MAC&t;&t;0x10&t;/* 0:No, 1:Yes loopback through MAC */
DECL|macro|HP100_CRC_I
mdefine_line|#define HP100_CRC_I&t;&t;0x08&t;/* 0:No, 1:Yes inhibit CRC on Tx packets */
DECL|macro|HP100_KEEP_CRC
mdefine_line|#define HP100_KEEP_CRC&t;&t;0x02&t;/* 0:No, 1:Yes keep CRC on Rx packets. */
multiline_comment|/*   The length will reflect this. */
DECL|macro|HP100_MAC2MODEMASK
mdefine_line|#define HP100_MAC2MODEMASK&t;0x02
DECL|macro|HP100_MAC2MODE1
mdefine_line|#define HP100_MAC2MODE1&t;&t;0x00
DECL|macro|HP100_MAC2MODE2
mdefine_line|#define HP100_MAC2MODE2&t;&t;0x00
DECL|macro|HP100_MAC2MODE3
mdefine_line|#define HP100_MAC2MODE3&t;&t;0x00
DECL|macro|HP100_MAC2MODE4
mdefine_line|#define HP100_MAC2MODE4&t;&t;0x00
DECL|macro|HP100_MAC2MODE5
mdefine_line|#define HP100_MAC2MODE5&t;&t;0x00
DECL|macro|HP100_MAC2MODE6
mdefine_line|#define HP100_MAC2MODE6&t;&t;0x00
DECL|macro|HP100_MAC2MODE7
mdefine_line|#define HP100_MAC2MODE7&t;&t;KEEP_CRC
multiline_comment|/*&n; *  Set/Reset bits&n; */
DECL|macro|HP100_SET_HB
mdefine_line|#define HP100_SET_HB&t;&t;0x0100&t;/* 0:Set fields to 0 whose mask is 1 */
DECL|macro|HP100_SET_LB
mdefine_line|#define HP100_SET_LB&t;&t;0x0001&t;/* HB sets upper byte, LB sets lower byte */
DECL|macro|HP100_RESET_HB
mdefine_line|#define HP100_RESET_HB&t;&t;0x0000&t;/* For readability when resetting bits */
DECL|macro|HP100_RESET_LB
mdefine_line|#define HP100_RESET_LB&t;&t;0x0000&t;/* For readability when resetting bits */
multiline_comment|/*&n; *  Misc. Constants&n; */
DECL|macro|HP100_LAN_100
mdefine_line|#define HP100_LAN_100&t;&t;100     /* lan_type value for VG */
DECL|macro|HP100_LAN_10
mdefine_line|#define HP100_LAN_10&t;&t;10&t;/* lan_type value for 10BaseT */
DECL|macro|HP100_LAN_ERR
mdefine_line|#define HP100_LAN_ERR&t;&t;(-1)&t;/* lan_type value for link down */
multiline_comment|/*&n; *  Receive Header Definition.&n; */
DECL|struct|hp100_rx_header
r_struct
id|hp100_rx_header
(brace
DECL|member|rx_length
id|u_short
id|rx_length
suffix:semicolon
multiline_comment|/* Pkt length is bits 12:0 */
DECL|member|rx_status
id|u_short
id|rx_status
suffix:semicolon
multiline_comment|/* status of the packet */
)brace
suffix:semicolon
DECL|macro|HP100_PKT_LEN_MASK
mdefine_line|#define HP100_PKT_LEN_MASK&t;0x1FFF&t;/* AND with RxLength to get length bits */
multiline_comment|/* Receive Packet Status.  Note, the error bits are only valid if ACC_ERRORED &n;   bit in the MAC Configuration Register 1 is set. */
DECL|macro|HP100_RX_PRI
mdefine_line|#define HP100_RX_PRI&t;&t;0x8000&t;/* 0:No, 1:Yes packet is priority */
DECL|macro|HP100_SDF_ERR
mdefine_line|#define HP100_SDF_ERR&t;&t;0x4000&t;/* 0:No, 1:Yes start of frame error */
DECL|macro|HP100_SKEW_ERR
mdefine_line|#define HP100_SKEW_ERR&t;&t;0x2000&t;/* 0:No, 1:Yes skew out of range */
DECL|macro|HP100_BAD_SYMBOL_ERR
mdefine_line|#define HP100_BAD_SYMBOL_ERR&t;0x1000&t;/* 0:No, 1:Yes invalid symbol received */
DECL|macro|HP100_RCV_IPM_ERR
mdefine_line|#define HP100_RCV_IPM_ERR&t;0x0800&t;/* 0:No, 1:Yes pkt had an invalid packet */
multiline_comment|/*   marker */
DECL|macro|HP100_SYMBOL_BAL_ERR
mdefine_line|#define HP100_SYMBOL_BAL_ERR&t;0x0400&t;/* 0:No, 1:Yes symbol balance error */
DECL|macro|HP100_VG_ALN_ERR
mdefine_line|#define HP100_VG_ALN_ERR&t;0x0200&t;/* 0:No, 1:Yes non-octet received */
DECL|macro|HP100_TRUNC_ERR
mdefine_line|#define HP100_TRUNC_ERR&t;&t;0x0100&t;/* 0:No, 1:Yes the packet was truncated */
DECL|macro|HP100_RUNT_ERR
mdefine_line|#define HP100_RUNT_ERR&t;&t;0x0040&t;/* 0:No, 1:Yes pkt length &lt; Min Pkt */
multiline_comment|/*   Length Reg. */
DECL|macro|HP100_ALN_ERR
mdefine_line|#define HP100_ALN_ERR&t;&t;0x0010&t;/* 0:No, 1:Yes align error. */
DECL|macro|HP100_CRC_ERR
mdefine_line|#define HP100_CRC_ERR&t;&t;0x0008&t;/* 0:No, 1:Yes CRC occurred. */
multiline_comment|/* The last three bits indicate the type of destination address */
DECL|macro|HP100_MULTI_ADDR_HASH
mdefine_line|#define HP100_MULTI_ADDR_HASH&t;0x0006&t;/* 110: Addr multicast, matched hash */
DECL|macro|HP100_BROADCAST_ADDR
mdefine_line|#define HP100_BROADCAST_ADDR&t;0x0003&t;/* x11: Addr broadcast */
DECL|macro|HP100_MULTI_ADDR_NO_HASH
mdefine_line|#define HP100_MULTI_ADDR_NO_HASH 0x0002&t;/* 010: Addr multicast, didn&squot;t match hash */
DECL|macro|HP100_PHYS_ADDR_MATCH
mdefine_line|#define HP100_PHYS_ADDR_MATCH&t;0x0001&t;/* x01: Addr was physical and mine */
DECL|macro|HP100_PHYS_ADDR_NO_MATCH
mdefine_line|#define HP100_PHYS_ADDR_NO_MATCH 0x0000&t;/* x00: Addr was physical but not mine */
multiline_comment|/*&n; *  macros&n; */
DECL|macro|hp100_inb
mdefine_line|#define hp100_inb( reg ) &bslash;&n;        inb( ioaddr + HP100_REG_##reg )
DECL|macro|hp100_inw
mdefine_line|#define hp100_inw( reg ) &bslash;&n;&t;inw( ioaddr + HP100_REG_##reg )
DECL|macro|hp100_inl
mdefine_line|#define hp100_inl( reg ) &bslash;&n;&t;inl( ioaddr + HP100_REG_##reg )
DECL|macro|hp100_outb
mdefine_line|#define hp100_outb( data, reg ) &bslash;&n;&t;outb( data, ioaddr + HP100_REG_##reg )
DECL|macro|hp100_outw
mdefine_line|#define hp100_outw( data, reg ) &bslash;&n;&t;outw( data, ioaddr + HP100_REG_##reg )
DECL|macro|hp100_outl
mdefine_line|#define hp100_outl( data, reg ) &bslash;&n;&t;outl( data, ioaddr + HP100_REG_##reg )
DECL|macro|hp100_orb
mdefine_line|#define hp100_orb( data, reg ) &bslash;&n;&t;outb( inb( ioaddr + HP100_REG_##reg ) | (data), ioaddr + HP100_REG_##reg )
DECL|macro|hp100_orw
mdefine_line|#define hp100_orw( data, reg ) &bslash;&n;&t;outw( inw( ioaddr + HP100_REG_##reg ) | (data), ioaddr + HP100_REG_##reg )
DECL|macro|hp100_andb
mdefine_line|#define hp100_andb( data, reg ) &bslash;&n;&t;outb( inb( ioaddr + HP100_REG_##reg ) &amp; (data), ioaddr + HP100_REG_##reg )
DECL|macro|hp100_andw
mdefine_line|#define hp100_andw( data, reg ) &bslash;&n;&t;outw( inw( ioaddr + HP100_REG_##reg ) &amp; (data), ioaddr + HP100_REG_##reg )
DECL|macro|hp100_page
mdefine_line|#define hp100_page( page ) &bslash;&n;&t;outw( HP100_PAGE_##page, ioaddr + HP100_REG_PAGING )
DECL|macro|hp100_ints_off
mdefine_line|#define hp100_ints_off() &bslash;&n;&t;outw( HP100_INT_EN | HP100_RESET_LB, ioaddr + HP100_REG_OPTION_LSW )
DECL|macro|hp100_ints_on
mdefine_line|#define hp100_ints_on() &bslash;&n;&t;outw( HP100_INT_EN | HP100_SET_LB, ioaddr + HP100_REG_OPTION_LSW )
DECL|macro|hp100_mem_map_enable
mdefine_line|#define hp100_mem_map_enable() &bslash;&n;&t;outw( HP100_MMAP_DIS | HP100_RESET_HB, ioaddr + HP100_REG_OPTION_LSW )
DECL|macro|hp100_mem_map_disable
mdefine_line|#define hp100_mem_map_disable() &bslash;&n;&t;outw( HP100_MMAP_DIS | HP100_SET_HB, ioaddr + HP100_REG_OPTION_LSW )
DECL|macro|hp100_reset_card
mdefine_line|#define hp100_reset_card() &bslash;&n;&t;outw( HP100_HW_RST | HP100_RESET_LB, ioaddr + HP100_REG_OPTION_LSW )
DECL|macro|hp100_unreset_card
mdefine_line|#define hp100_unreset_card() &bslash;&n;&t;outw( HP100_HW_RST | HP100_SET_LB, ioaddr + HP100_REG_OPTION_LSW )
eof
