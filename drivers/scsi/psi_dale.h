multiline_comment|/*+M*************************************************************************&n; * Perceptive Solutions, Inc. PCI-2000 device driver proc support for Linux.&n; *&n; * Copyright (c) 1997 Perceptive Solutions, Inc.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *&n; *&t;File Name:&t;&t;psi_dale.h&n; *&n; *&t;Description:&t;This file contains the interface defines and&n; *&t;&t;&t;&t;&t;error codes.&n; *&n; *-M*************************************************************************/
macro_line|#ifndef PSI_DALE
DECL|macro|PSI_DALE
mdefine_line|#define PSI_DALE
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Dale PCI setup&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|VENDOR_PSI
mdefine_line|#define&t;VENDOR_PSI&t;&t;&t;0x1256
DECL|macro|DEVICE_DALE_1
mdefine_line|#define&t;DEVICE_DALE_1&t;&t;0x4401&t;&t;/* &squot;D1&squot; */
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Misc konstants&t;&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|DALE_MAXDRIVES
mdefine_line|#define&t;DALE_MAXDRIVES&t;&t;&t;4
DECL|macro|SECTORSXFER
mdefine_line|#define&t;SECTORSXFER&t;&t;&t;&t;8
DECL|macro|BYTES_PER_SECTOR
mdefine_line|#define&t;BYTES_PER_SECTOR&t;&t;512
DECL|macro|DEFAULT_TIMING_MODE
mdefine_line|#define&t;DEFAULT_TIMING_MODE&t;&t;5
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;EEPROM locations&t;&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|DALE_FLASH_PAGE_SIZE
mdefine_line|#define&t;DALE_FLASH_PAGE_SIZE&t;128&t;&t;&t;&t;
singleline_comment|// number of bytes per page
DECL|macro|DALE_FLASH_SIZE
mdefine_line|#define&t;DALE_FLASH_SIZE&t;&t;&t;65536L
DECL|macro|DALE_FLASH_BIOS
mdefine_line|#define&t;DALE_FLASH_BIOS&t;&t;&t;0x00080000L&t;&t;
singleline_comment|// BIOS base address
DECL|macro|DALE_FLASH_SETUP
mdefine_line|#define&t;DALE_FLASH_SETUP&t;&t;0x00088000L&t;&t;
singleline_comment|// SETUP PROGRAM base address offset from BIOS
DECL|macro|DALE_FLASH_RAID
mdefine_line|#define&t;DALE_FLASH_RAID&t;&t;&t;0x00088400L&t;&t;
singleline_comment|// RAID signature storage
DECL|macro|DALE_FLASH_FACTORY
mdefine_line|#define&t;DALE_FLASH_FACTORY&t;&t;0x00089000L&t;&t;
singleline_comment|// FACTORY data base address offset from BIOS
DECL|macro|DALE_FLASH_BIOS_SIZE
mdefine_line|#define&t;DALE_FLASH_BIOS_SIZE&t;32768U&t;&t;&t;
singleline_comment|// size of FLASH BIOS REGION
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;DALE Register address offsets&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|REG_DATA
mdefine_line|#define&t;REG_DATA&t;&t;&t;&t;0x80
DECL|macro|REG_ERROR
mdefine_line|#define&t;REG_ERROR&t;&t;&t;&t;0x84
DECL|macro|REG_SECTOR_COUNT
mdefine_line|#define&t;REG_SECTOR_COUNT&t;&t;0x88
DECL|macro|REG_LBA_0
mdefine_line|#define&t;REG_LBA_0&t;&t;&t;&t;0x8C
DECL|macro|REG_LBA_8
mdefine_line|#define&t;REG_LBA_8&t;&t;&t;&t;0x90
DECL|macro|REG_LBA_16
mdefine_line|#define&t;REG_LBA_16&t;&t;&t;&t;0x94
DECL|macro|REG_LBA_24
mdefine_line|#define&t;REG_LBA_24&t;&t;&t;&t;0x98
DECL|macro|REG_STAT_CMD
mdefine_line|#define&t;REG_STAT_CMD&t;&t;&t;0x9C
DECL|macro|REG_STAT_SEL
mdefine_line|#define&t;REG_STAT_SEL&t;&t;&t;0xA0
DECL|macro|REG_FAIL
mdefine_line|#define&t;REG_FAIL&t;&t;&t;&t;0xB0
DECL|macro|REG_ALT_STAT
mdefine_line|#define&t;REG_ALT_STAT&t;&t;&t;0xB8
DECL|macro|REG_DRIVE_ADRS
mdefine_line|#define&t;REG_DRIVE_ADRS&t;&t;&t;0xBC
DECL|macro|DALE_DATA_SLOW
mdefine_line|#define&t;DALE_DATA_SLOW&t;&t;&t;0x00040000L
DECL|macro|DALE_DATA_MODE2
mdefine_line|#define&t;DALE_DATA_MODE2&t;&t;&t;0x00040000L
DECL|macro|DALE_DATA_MODE3
mdefine_line|#define&t;DALE_DATA_MODE3&t;&t;&t;0x00050000L
DECL|macro|DALE_DATA_MODE4
mdefine_line|#define&t;DALE_DATA_MODE4&t;&t;&t;0x00060000L
DECL|macro|DALE_DATA_MODE4P
mdefine_line|#define&t;DALE_DATA_MODE4P&t;&t;0x00070000L
DECL|macro|RTR_LOCAL_RANGE
mdefine_line|#define RTR_LOCAL_RANGE&t;&t;&t;&t;&t;0x000
DECL|macro|RTR_LOCAL_REMAP
mdefine_line|#define RTR_LOCAL_REMAP&t;&t;&t;&t;&t;0x004
DECL|macro|RTR_EXP_RANGE
mdefine_line|#define RTR_EXP_RANGE&t;&t;&t;&t;&t;0x010
DECL|macro|RTR_EXP_REMAP
mdefine_line|#define RTR_EXP_REMAP&t;&t;&t;&t;&t;0x014
DECL|macro|RTR_REGIONS
mdefine_line|#define RTR_REGIONS&t;&t;&t;&t;&t;&t;0x018
DECL|macro|RTR_DM_MASK
mdefine_line|#define RTR_DM_MASK&t;&t;&t;&t;&t;&t;0x01C
DECL|macro|RTR_DM_LOCAL_BASE
mdefine_line|#define RTR_DM_LOCAL_BASE&t;&t;&t;&t;0x020
DECL|macro|RTR_DM_IO_BASE
mdefine_line|#define RTR_DM_IO_BASE&t;&t;&t;&t;&t;0x024
DECL|macro|RTR_DM_PCI_REMAP
mdefine_line|#define RTR_DM_PCI_REMAP&t;&t;&t;&t;0x028
DECL|macro|RTR_DM_IO_CONFIG
mdefine_line|#define RTR_DM_IO_CONFIG&t;&t;&t;&t;0x02C
DECL|macro|RTR_MAILBOX
mdefine_line|#define RTR_MAILBOX&t;&t;&t;&t;&t;&t;0x040
DECL|macro|RTR_LOCAL_DOORBELL
mdefine_line|#define RTR_LOCAL_DOORBELL&t;&t;&t;&t;0x060
DECL|macro|RTR_PCI_DOORBELL
mdefine_line|#define RTR_PCI_DOORBELL&t;&t;&t;&t;0x064
DECL|macro|RTR_INT_CONTROL_STATUS
mdefine_line|#define RTR_INT_CONTROL_STATUS &t;&t;&t;0x068
DECL|macro|RTR_EEPROM_CONTROL_STATUS
mdefine_line|#define RTR_EEPROM_CONTROL_STATUS&t;&t;0x06C
DECL|macro|RTL_DMA0_MODE
mdefine_line|#define RTL_DMA0_MODE&t;&t;&t;&t;&t;0x00
DECL|macro|RTL_DMA0_PCI_ADDR
mdefine_line|#define RTL_DMA0_PCI_ADDR&t;&t;&t;&t;0x04
DECL|macro|RTL_DMA0_LOCAL_ADDR
mdefine_line|#define RTL_DMA0_LOCAL_ADDR&t;&t;&t;&t;0x08
DECL|macro|RTL_DMA0_COUNT
mdefine_line|#define RTL_DMA0_COUNT&t;&t;&t;&t;&t;0x0C
DECL|macro|RTL_DMA0_DESC_PTR
mdefine_line|#define RTL_DMA0_DESC_PTR&t;&t;&t;&t;0x10
DECL|macro|RTL_DMA1_MODE
mdefine_line|#define RTL_DMA1_MODE&t;&t;&t;&t;&t;0x14
DECL|macro|RTL_DMA1_PCI_ADDR
mdefine_line|#define RTL_DMA1_PCI_ADDR&t;&t;&t;&t;0x18
DECL|macro|RTL_DMA1_LOCAL_ADDR
mdefine_line|#define RTL_DMA1_LOCAL_ADDR&t;&t;&t;&t;0x1C
DECL|macro|RTL_DMA1_COUNT
mdefine_line|#define RTL_DMA1_COUNT&t;&t;&t;&t;&t;0x20
DECL|macro|RTL_DMA1_DESC_PTR
mdefine_line|#define RTL_DMA1_DESC_PTR&t;&t;&t;&t;0x24
DECL|macro|RTL_DMA_COMMAND_STATUS
mdefine_line|#define RTL_DMA_COMMAND_STATUS&t;&t;&t;0x28
DECL|macro|RTL_DMA_ARB0
mdefine_line|#define RTL_DMA_ARB0&t;&t;&t;&t;&t;0x2C
DECL|macro|RTL_DMA_ARB1
mdefine_line|#define RTL_DMA_ARB1&t;&t;&t;&t;&t;0x30
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Dale Scratchpad locations&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|DALE_CHANNEL_DEVICE_0
mdefine_line|#define&t;DALE_CHANNEL_DEVICE_0&t;0&t;&t;
singleline_comment|// device channel locations
DECL|macro|DALE_CHANNEL_DEVICE_1
mdefine_line|#define&t;DALE_CHANNEL_DEVICE_1&t;1
DECL|macro|DALE_CHANNEL_DEVICE_2
mdefine_line|#define&t;DALE_CHANNEL_DEVICE_2&t;2
DECL|macro|DALE_CHANNEL_DEVICE_3
mdefine_line|#define&t;DALE_CHANNEL_DEVICE_3&t;3
DECL|macro|DALE_SCRATH_DEVICE_0
mdefine_line|#define&t;DALE_SCRATH_DEVICE_0&t;4&t;&t;
singleline_comment|// device type codes
DECL|macro|DALE_SCRATH_DEVICE_1
mdefine_line|#define&t;DALE_SCRATH_DEVICE_1&t;5
DECL|macro|DALE_SCRATH_DEVICE_2
mdefine_line|#define DALE_SCRATH_DEVICE_2&t;6
DECL|macro|DALE_SCRATH_DEVICE_3
mdefine_line|#define&t;DALE_SCRATH_DEVICE_3&t;7
DECL|macro|DALE_RAID_0_STATUS
mdefine_line|#define&t;DALE_RAID_0_STATUS&t;&t;8
DECL|macro|DALE_RAID_1_STATUS
mdefine_line|#define DALE_RAID_1_STATUS&t;&t;9
DECL|macro|DALE_TIMING_MODE
mdefine_line|#define&t;DALE_TIMING_MODE&t;&t;12&t;&t;
singleline_comment|// bus master timing mode (2, 3, 4, 5)
DECL|macro|DALE_NUM_DRIVES
mdefine_line|#define&t;DALE_NUM_DRIVES&t;&t;&t;13&t;&t;
singleline_comment|// number of addressable drives on this board
DECL|macro|DALE_RAID_ON
mdefine_line|#define&t;DALE_RAID_ON&t;&t;&t;14 &t;&t;
singleline_comment|// RAID status On
DECL|macro|DALE_LAST_ERROR
mdefine_line|#define&t;DALE_LAST_ERROR&t;&t;&t;15&t;&t;
singleline_comment|// Last error code from BIOS
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Dale cable select bits&t;&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|SEL_NONE
mdefine_line|#define&t;SEL_NONE&t;&t;&t;&t;0x00
DECL|macro|SEL_1
mdefine_line|#define&t;SEL_1&t;&t;&t;&t;&t;0x01
DECL|macro|SEL_2
mdefine_line|#define&t;SEL_2&t;&t;&t;&t;&t;0x02
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Programmable Interrupt Controller&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|PIC1
mdefine_line|#define&t;PIC1&t;&t;&t;&t;&t;0x20&t;&t;&t;&t;
singleline_comment|// first 8259 base port address
DECL|macro|PIC2
mdefine_line|#define&t;PIC2&t;&t;&t;&t;&t;0xA0&t;&t;&t;&t;
singleline_comment|// second 8259 base port address
DECL|macro|INT_OCW1
mdefine_line|#define&t;INT_OCW1&t;&t;&t;&t;1&t;&t;&t;&t;&t;
singleline_comment|// Operation Control Word 1: IRQ mask
DECL|macro|EOI
mdefine_line|#define&t;EOI&t;&t;&t;&t;&t;&t;0x20&t;&t;&t;&t;
singleline_comment|// non-specific end-of-interrupt
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Device/Geometry controls&t;&t;&t;&t;*/
multiline_comment|/************************************************/
DECL|macro|GEOMETRY_NONE
mdefine_line|#define GEOMETRY_NONE&t; &t;0x0&t;&t;&t;
singleline_comment|// No device
DECL|macro|GEOMETRY_SET
mdefine_line|#define GEOMETRY_SET&t;&t;0x1&t;&t;&t;
singleline_comment|// Geometry set
DECL|macro|GEOMETRY_LBA
mdefine_line|#define&t;GEOMETRY_LBA&t;&t;0x2&t;&t;&t;
singleline_comment|// Geometry set in default LBA mode
DECL|macro|GEOMETRY_PHOENIX
mdefine_line|#define&t;GEOMETRY_PHOENIX&t;0x3&t;&t;&t;
singleline_comment|// Geometry set in Pheonix BIOS compatibility mode
DECL|macro|DEVICE_NONE
mdefine_line|#define&t;DEVICE_NONE&t;&t;&t;0x0&t;&t;&t;
singleline_comment|// No device present
DECL|macro|DEVICE_INACTIVE
mdefine_line|#define&t;DEVICE_INACTIVE&t;&t;0x1&t;&t;&t;
singleline_comment|// device present but not registered active
DECL|macro|DEVICE_ATAPI
mdefine_line|#define&t;DEVICE_ATAPI&t;&t;0x2&t;&t;&t;
singleline_comment|// ATAPI device (CD_ROM, Tape, Etc...)
DECL|macro|DEVICE_DASD_NONLBA
mdefine_line|#define&t;DEVICE_DASD_NONLBA&t;0x3&t;&t;&t;
singleline_comment|// Non LBA incompatible device
DECL|macro|DEVICE_DASD_LBA
mdefine_line|#define&t;DEVICE_DASD_LBA&t;&t;0x4&t;&t;&t;
singleline_comment|// LBA compatible device
multiline_comment|/************************************************/
multiline_comment|/*&t;&t;Setup Structure Definitions&t;&t;&t;&t;*/
multiline_comment|/************************************************/
r_typedef
r_struct
singleline_comment|// device setup parameters
(brace
DECL|member|geometryControl
id|UCHAR
id|geometryControl
suffix:semicolon
singleline_comment|// geometry control flags
DECL|member|device
id|UCHAR
id|device
suffix:semicolon
singleline_comment|// device code
DECL|member|sectors
id|USHORT
id|sectors
suffix:semicolon
singleline_comment|// number of sectors per track
DECL|member|heads
id|USHORT
id|heads
suffix:semicolon
singleline_comment|// number of heads
DECL|member|cylinders
id|USHORT
id|cylinders
suffix:semicolon
singleline_comment|// number of cylinders for this device
DECL|member|blocks
id|ULONG
id|blocks
suffix:semicolon
singleline_comment|// number of blocks on device
DECL|member|realCapacity
id|ULONG
id|realCapacity
suffix:semicolon
singleline_comment|// number of real blocks on this device for drive changed testing
DECL|typedef|SETUP_DEVICE
DECL|typedef|PSETUP_DEVICE
)brace
id|SETUP_DEVICE
comma
op_star
id|PSETUP_DEVICE
suffix:semicolon
r_typedef
r_struct
singleline_comment|// master setup structure
(brace
DECL|member|startupDelay
id|USHORT
id|startupDelay
suffix:semicolon
DECL|member|promptBIOS
id|BOOL
id|promptBIOS
suffix:semicolon
DECL|member|fastFormat
id|BOOL
id|fastFormat
suffix:semicolon
DECL|member|shareInterrupt
id|BOOL
id|shareInterrupt
suffix:semicolon
DECL|member|rebootRebuil
id|BOOL
id|rebootRebuil
suffix:semicolon
DECL|member|timingMode
id|USHORT
id|timingMode
suffix:semicolon
DECL|member|spare5
id|USHORT
id|spare5
suffix:semicolon
DECL|member|spare6
id|USHORT
id|spare6
suffix:semicolon
DECL|member|setupDevice
id|SETUP_DEVICE
id|setupDevice
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|SETUP
DECL|typedef|PSETUP
)brace
id|SETUP
comma
op_star
id|PSETUP
suffix:semicolon
macro_line|#endif
eof
