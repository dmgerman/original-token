multiline_comment|/*&n; * asm-m68k/zorro.h -- Amiga AutoConfig (Zorro) Expansion Device Definitions&n; *&n; * Copyright (C) 1995 Geert Uytterhoeven&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef _M68K_ZORRO_H
DECL|macro|_M68K_ZORRO_H
mdefine_line|#define _M68K_ZORRO_H
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Defined Board Manufacturers&n; *&n; * Please update arch/m68k/amiga/zorro.c if you make changes here&n; * Many IDs were obtained from ExpName/Identify ((C) Richard K&#xfffd;rber)&n; * and by looking at the NetBSD-Amiga kernel sources&n; */
DECL|macro|MANUF_PACIFIC
mdefine_line|#define MANUF_PACIFIC          (0x00D3)&t;/* Pacific Peripherals */
DECL|macro|PROD_SE_2000_A500
mdefine_line|#define PROD_SE_2000_A500      (0x00)&t;/* SE 2000 A500 */
DECL|macro|PROD_PACIFIC_HD
mdefine_line|#define PROD_PACIFIC_HD        (0x0A)&t;/* HD Controller */
DECL|macro|MANUF_KUPKE
mdefine_line|#define MANUF_KUPKE            (0x00DD)&t;/* Kupke */
DECL|macro|PROD_GOLEM_BOX_2
mdefine_line|#define PROD_GOLEM_BOX_2       (0x00)&t;/* Golem RAM Box 2MB */
DECL|macro|MANUF_MEMPHIS
mdefine_line|#define MANUF_MEMPHIS          (0x0100)&t;/* Memphis */
DECL|macro|PROD_STORMBRINGER
mdefine_line|#define PROD_STORMBRINGER      (0x00)&t;/* Stormbringer */
DECL|macro|MANUF_COMMODORE2
mdefine_line|#define MANUF_COMMODORE2       (0x0201)&t;/* Commodore Braunschweig */
DECL|macro|PROD_A2088
mdefine_line|#define PROD_A2088             (0x01)&t;/* CBM A2088 XT Bridgeboard */
DECL|macro|PROD_A2286
mdefine_line|#define PROD_A2286             (0x02)&t;/* CBM A2286 AT Bridgeboard */
DECL|macro|PROD_A4091_2
mdefine_line|#define PROD_A4091_2           (0x54)&t;/* CBM A4091 SCSI Controller */
DECL|macro|PROD_A2386SX
mdefine_line|#define PROD_A2386SX           (0x67)&t;/* CBM A2386-SX Bridgeboard */
DECL|macro|MANUF_COMMODORE
mdefine_line|#define MANUF_COMMODORE        (0x0202)&t;/* Commodore West Chester */
DECL|macro|PROD_A2090A
mdefine_line|#define PROD_A2090A            (0x01)&t;/* CBM A2090/A2090A HD Controller */
DECL|macro|PROD_A590
mdefine_line|#define PROD_A590              (0x02)&t;/* CBM A590 SCSI Controller */
DECL|macro|PROD_A2091
mdefine_line|#define PROD_A2091             (0x03)&t;/* CBM A2091 SCSI Controller */
DECL|macro|PROD_A2090B
mdefine_line|#define PROD_A2090B            (0x04)&t;/* CBM A2090B 2090 Autoboot Card */
DECL|macro|PROD_ARCNET
mdefine_line|#define PROD_ARCNET            (0x09)&t;/* CBM A2060 Arcnet Card */
DECL|macro|PROD_CBMRAM
mdefine_line|#define PROD_CBMRAM            (0x0A)&t;/* CBM A2052/58.RAM | 590/2091.RAM */
DECL|macro|PROD_A560RAM
mdefine_line|#define PROD_A560RAM           (0x20)&t;/* CBM A560 Memory Module */
DECL|macro|PROD_A2232PROTO
mdefine_line|#define PROD_A2232PROTO        (0x45)&t;/* CBM A2232 Serial Prototype */
DECL|macro|PROD_A2232
mdefine_line|#define PROD_A2232             (0x46)&t;/* CBM A2232 Serial Production */
DECL|macro|PROD_A2620
mdefine_line|#define PROD_A2620             (0x50)&t;/* CBM A2620 68020/RAM Card */
DECL|macro|PROD_A2630
mdefine_line|#define PROD_A2630             (0x51)&t;/* CBM A2630 68030/RAM Card */
DECL|macro|PROD_A4091
mdefine_line|#define PROD_A4091             (0x54)&t;/* CBM A4091 SCSI Controller */
DECL|macro|PROD_A2065_2
mdefine_line|#define PROD_A2065_2           (0x5A)&t;/* A2065 Ethernet Card */
DECL|macro|PROD_ROMULATOR
mdefine_line|#define PROD_ROMULATOR         (0x60)&t;/* CBM Romulator Card */
DECL|macro|PROD_A3000TESTFIX
mdefine_line|#define PROD_A3000TESTFIX      (0x61)&t;/* CBM A3000 Test Fixture */
DECL|macro|PROD_A2386SX_2
mdefine_line|#define PROD_A2386SX_2         (0x67)&t;/* A2386-SX Bridgeboard */
DECL|macro|PROD_A2065
mdefine_line|#define PROD_A2065             (0x70)&t;/* CBM A2065 Ethernet Card */
DECL|macro|MANUF_COMMODORE3
mdefine_line|#define MANUF_COMMODORE3       (0x0203)&t;/* Commodore West Chester */
DECL|macro|PROD_A2090A_CM
mdefine_line|#define PROD_A2090A_CM         (0x03)&t;/* A2090A Combitec/MacroSystem */
DECL|macro|MANUF_KCS
mdefine_line|#define MANUF_KCS              (0x02FF)&t;/* Kolff Computer Supplies */
DECL|macro|PROD_POWER_BOARD
mdefine_line|#define PROD_POWER_BOARD       (0x00)&t;/* KCS Power PC Board */
DECL|macro|MANUF_CARDCO
mdefine_line|#define MANUF_CARDCO           (0x03EC)&t;/* Cardco */
DECL|macro|PROD_KRONOS_2000_SCSI
mdefine_line|#define PROD_KRONOS_2000_SCSI  (0x04)&t;/* Kronos 2000 SCSI Controller */
DECL|macro|PROD_A1000_SCSI
mdefine_line|#define PROD_A1000_SCSI        (0x0C)&t;/* A1000 SCSI Controller */
DECL|macro|PROD_ESCORT_SCSI
mdefine_line|#define PROD_ESCORT_SCSI       (0x0E)&t;/* Escort SCSI Controller */
DECL|macro|PROD_CC_A2410
mdefine_line|#define PROD_CC_A2410          (0xF5)&t;/* Cardco A2410 Hires Graphics Card */
DECL|macro|MANUF_A_SQUARED
mdefine_line|#define MANUF_A_SQUARED        (0x03ED)&t;/* A-Squared */
DECL|macro|PROD_LIVE_2000
mdefine_line|#define PROD_LIVE_2000         (0x01)&t;/* Live! 2000 */
DECL|macro|MANUF_COMSPEC
mdefine_line|#define MANUF_COMSPEC          (0x03EE)&t;/* ComSpec Communications */
DECL|macro|PROD_AX2000
mdefine_line|#define PROD_AX2000            (0x01)&t;/* AX2000 */
DECL|macro|MANUF_ANAKIN
mdefine_line|#define MANUF_ANAKIN           (0x03F1)&t;/* Anakin */
DECL|macro|PROD_EASYL
mdefine_line|#define PROD_EASYL             (0x01)&t;/* Easyl Tablet */
DECL|macro|MANUF_MICROBOTICS
mdefine_line|#define MANUF_MICROBOTICS      (0x03F2)&t;/* MicroBotics */
DECL|macro|PROD_STARBOARD_II
mdefine_line|#define PROD_STARBOARD_II      (0x00)&t;/* StarBoard II */
DECL|macro|PROD_STARDRIVE
mdefine_line|#define PROD_STARDRIVE         (0x02)&t;/* StarDrive */
DECL|macro|PROD_8_UP_A
mdefine_line|#define PROD_8_UP_A            (0x03)&t;/* 8-Up (Rev A) */
DECL|macro|PROD_8_UP_Z
mdefine_line|#define PROD_8_UP_Z            (0x04)&t;/* 8-Up (Rev Z) */
DECL|macro|PROD_VXL_RAM
mdefine_line|#define PROD_VXL_RAM           (0x44)&t;/* VXL RAM */
DECL|macro|PROD_VXL_30
mdefine_line|#define PROD_VXL_30            (0x45)&t;/* VXL-30 Turbo Board */
DECL|macro|PROD_MBX_1200
mdefine_line|#define PROD_MBX_1200          (0x81)&t;/* MBX 1200 */
DECL|macro|PROD_HARDFRAME_2000
mdefine_line|#define PROD_HARDFRAME_2000    (0x9E)&t;/* Hardframe 2000 */
DECL|macro|PROD_MBX_1200_2
mdefine_line|#define PROD_MBX_1200_2        (0xC1)&t;/* MBX 1200 */
DECL|macro|MANUF_ACCESS
mdefine_line|#define MANUF_ACCESS           (0x03F4)&t;/* Access Associates */
DECL|macro|MANUF_EXPANSION_TECH
mdefine_line|#define MANUF_EXPANSION_TECH   (0x03F6)&t;/* Expansion Technologies */
DECL|macro|MANUF_ASDG
mdefine_line|#define MANUF_ASDG             (0x03FF)&t;/* ASDG */
DECL|macro|PROD_ASDG_MEMORY
mdefine_line|#define PROD_ASDG_MEMORY       (0x01)&t;/* Memory Expansion */
DECL|macro|PROD_ASDG_MEMORY_2
mdefine_line|#define PROD_ASDG_MEMORY_2     (0x02)&t;/* Memory Expansion */
DECL|macro|PROD_LAN_ROVER
mdefine_line|#define PROD_LAN_ROVER         (0xFE)&t;/* Lan Rover Ethernet */
DECL|macro|PROD_TWIN_X
mdefine_line|#define PROD_TWIN_X            (0xFF)&t;/* Twin-X Serial Card */
DECL|macro|MANUF_IMTRONICS
mdefine_line|#define MANUF_IMTRONICS        (0x0404)&t;/* Imtronics */
DECL|macro|PROD_HURRICANE_2800
mdefine_line|#define PROD_HURRICANE_2800    (0x39)&t;/* Hurricane 2800 68030 */
DECL|macro|PROD_HURRICANE_2800_2
mdefine_line|#define PROD_HURRICANE_2800_2  (0x57)&t;/* Hurricane 2800 68030 */
DECL|macro|MANUF_UNIV_OF_LOWELL
mdefine_line|#define MANUF_UNIV_OF_LOWELL   (0x0406)&t;/* University of Lowell */
DECL|macro|PROD_A2410
mdefine_line|#define PROD_A2410             (0x00)&t;/* CBM A2410 Hires Graphics Card */
DECL|macro|MANUF_AMERISTAR
mdefine_line|#define MANUF_AMERISTAR        (0x041D)&t;/* Ameristar */
DECL|macro|PROD_AMERISTAR2065
mdefine_line|#define PROD_AMERISTAR2065     (0x01)&t;/* A2065 Ethernet Card */
DECL|macro|PROD_A560
mdefine_line|#define PROD_A560              (0x09)&t;/* Arcnet Card */
DECL|macro|PROD_A4066
mdefine_line|#define PROD_A4066             (0x0A)&t;/* A4066 Ethernet Card */
DECL|macro|MANUF_SUPRA
mdefine_line|#define MANUF_SUPRA            (0x0420)&t;/* Supra */
DECL|macro|PROD_SUPRADRIVE_4x4
mdefine_line|#define PROD_SUPRADRIVE_4x4    (0x01)&t;/* SupraDrive 4x4 SCSI Controller */
DECL|macro|PROD_SUPRA_2000
mdefine_line|#define PROD_SUPRA_2000        (0x03)&t;/* 2000 DMA HD */
DECL|macro|PROD_SUPRA_500
mdefine_line|#define PROD_SUPRA_500         (0x05)&t;/* 500 HD/RAM */
DECL|macro|PROD_SUPRA_500RX
mdefine_line|#define PROD_SUPRA_500RX       (0x09)&t;/* 500RX/2000 RAM */
DECL|macro|PROD_SUPRA_500RX_2
mdefine_line|#define PROD_SUPRA_500RX_2     (0x0A)&t;/* 500RX/2000 RAM */
DECL|macro|PROD_SUPRA_2400ZI
mdefine_line|#define PROD_SUPRA_2400ZI      (0x0B)&t;/* 2400zi Modem */
DECL|macro|PROD_WORDSYNC
mdefine_line|#define PROD_WORDSYNC          (0x0C)&t;/* Supra Wordsync SCSI Controller */
DECL|macro|PROD_WORDSYNC_II
mdefine_line|#define PROD_WORDSYNC_II       (0x0D)&t;/* Supra Wordsync II SCSI Controller */
DECL|macro|PROD_SUPRA_2400ZIPLUS
mdefine_line|#define PROD_SUPRA_2400ZIPLUS  (0x10)&t;/* 2400zi+ Modem */
DECL|macro|MANUF_CSA
mdefine_line|#define MANUF_CSA              (0x0422)&t;/* CSA */
DECL|macro|PROD_MAGNUM
mdefine_line|#define PROD_MAGNUM            (0x11)&t;/* Magnum 40 SCSI Controller */
DECL|macro|PROD_12GAUGE
mdefine_line|#define PROD_12GAUGE           (0x15)&t;/* 12 Gauge SCSI Controller */
DECL|macro|MANUF_GVP3
mdefine_line|#define MANUF_GVP3             (0x06E1)&t;/* Great Valley Products */
DECL|macro|PROD_IMPACT
mdefine_line|#define PROD_IMPACT            (0x08)&t;/* Impact SCSI/Memory */
DECL|macro|MANUF_BYTEBOX
mdefine_line|#define MANUF_BYTEBOX          (0x07DA)&t;/* ByteBox */
DECL|macro|PROD_BYTEBOX_A500
mdefine_line|#define PROD_BYTEBOX_A500      (0x00)&t;/* A500 */
DECL|macro|MANUF_HACKER
mdefine_line|#define MANUF_HACKER           (0x07DB)&t;/* Test only: no product definitions */
DECL|macro|MANUF_POWER_COMPUTING
mdefine_line|#define MANUF_POWER_COMPUTING  (0x07DC)&t;/* Power Computing (DKB) */
DECL|macro|PROD_DKB_3128
mdefine_line|#define PROD_DKB_3128          (0x0E)&t;/* DKB 3128 RAM */
DECL|macro|PROD_VIPER_II_COBRA
mdefine_line|#define PROD_VIPER_II_COBRA    (0x12)&t;/* Viper II Turbo Board (DKB Cobra) */
DECL|macro|MANUF_GVP
mdefine_line|#define MANUF_GVP              (0x07E1)&t;/* Great Valley Products */
DECL|macro|PROD_IMPACT_I_4K
mdefine_line|#define PROD_IMPACT_I_4K       (0x01)&t;/* Impact Series-I SCSI 4K */
DECL|macro|PROD_IMPACT_I_16K_2
mdefine_line|#define PROD_IMPACT_I_16K_2    (0x02)&t;/* Impact Series-I SCSI 16K/2 */
DECL|macro|PROD_IMPACT_I_16K_3
mdefine_line|#define PROD_IMPACT_I_16K_3    (0x03)&t;/* Impact Series-I SCSI 16K/3 */
DECL|macro|PROD_IMPACT_3001_IDE
mdefine_line|#define PROD_IMPACT_3001_IDE   (0x08)&t;/* Impact 3001 IDE */
DECL|macro|PROD_IMPACT_3001_RAM
mdefine_line|#define PROD_IMPACT_3001_RAM   (0x09)&t;/* Impact 3001 RAM */
DECL|macro|PROD_GVPIISCSI
mdefine_line|#define PROD_GVPIISCSI         (0x0B)&t;/* GVP Series II SCSI Controller */
DECL|macro|PROD_GVPIISCSI_2
mdefine_line|#define PROD_GVPIISCSI_2       (0x09)&t;/* evidence that the driver works&n;&t;&t;&t;&t;&t;   for this product code also */
DECL|macro|PROD_GVPIIRAM
mdefine_line|#define PROD_GVPIIRAM          (0x0A)&t;/* GVP Series II RAM */
DECL|macro|PROD_GVP
mdefine_line|#define PROD_GVP               (0x0B)&t;/* This code is used by a wide range of&n;&t;&t;&t;&t;&t;   GVP products - use the epc to&n;&t;&t;&t;&t;&t;   identify it correctly */
DECL|macro|PROD_GVP_A2000_030
mdefine_line|#define PROD_GVP_A2000_030     (0x0D)&t;/* GVP A2000 68030 Turbo Board */
DECL|macro|PROD_IMPACT_3001_IDE_2
mdefine_line|#define PROD_IMPACT_3001_IDE_2 (0x0D)&t;/* Impact 3001 IDE */
DECL|macro|PROD_GFORCE_040_SCSI
mdefine_line|#define PROD_GFORCE_040_SCSI   (0x16)&t;/* GForce 040 with SCSI (new) */
DECL|macro|PROD_GVPIV_24
mdefine_line|#define PROD_GVPIV_24          (0x20)&t;/* GVP IV-24 Graphics Board */
DECL|macro|PROD_GFORCE_040
mdefine_line|#define PROD_GFORCE_040        (0xFF)&t;/* GForce 040 Turbo Board */
multiline_comment|/* #define PROD_GVPIO_EXT      (0xFF)*/
multiline_comment|/* GVP I/O Extender */
DECL|macro|MANUF_SYNERGY
mdefine_line|#define MANUF_SYNERGY          (0x07E5)&t;/* Synergy */
DECL|macro|MANUF_XETEC
mdefine_line|#define MANUF_XETEC            (0x07E6)&t;/* Xetec */
DECL|macro|PROD_FASTCARD_SCSI
mdefine_line|#define PROD_FASTCARD_SCSI     (0x01)&t;/* FastCard SCSI Controller */
DECL|macro|PROD_FASTCARD_RAM
mdefine_line|#define PROD_FASTCARD_RAM      (0x02)&t;/* FastCard RAM */
DECL|macro|MANUF_PPI
mdefine_line|#define MANUF_PPI              (0x07EA)&t;/* Progressive Peripherals Inc. */
DECL|macro|PROD_MERCURY
mdefine_line|#define PROD_MERCURY           (0x00)&t;/* Mercury Turbo Board */
DECL|macro|PROD_PPS_A3000_040
mdefine_line|#define PROD_PPS_A3000_040     (0x01)&t;/* PP&amp;S A3000 68040 Turbo Board */
DECL|macro|PROD_PPS_A2000_040
mdefine_line|#define PROD_PPS_A2000_040     (0x69)&t;/* PP&amp;S A2000 68040 Turbo Board */
DECL|macro|PROD_ZEUS
mdefine_line|#define PROD_ZEUS              (0x96)&t;/* Zeus SCSI Controller */
DECL|macro|PROD_PPS_A500_040
mdefine_line|#define PROD_PPS_A500_040      (0xBB)&t;/* PP&amp;S A500 68040 Turbo Board */
DECL|macro|MANUF_XEBEC
mdefine_line|#define MANUF_XEBEC            (0x07EC)&t;/* Xebec */
DECL|macro|MANUF_SPIRIT
mdefine_line|#define MANUF_SPIRIT           (0x07F2)&t;/* Spirit */
DECL|macro|PROD_HDA_506
mdefine_line|#define PROD_HDA_506           (0x04)&t;/* HDA 506 Harddisk */
DECL|macro|PROD_OCTABYTE_RAM
mdefine_line|#define PROD_OCTABYTE_RAM      (0x06)&t;/* OctaByte RAM */
DECL|macro|MANUF_BSC
mdefine_line|#define MANUF_BSC              (0x07FE)&t;/* BSC */
DECL|macro|PROD_ALF_3_SCSI
mdefine_line|#define PROD_ALF_3_SCSI        (0x03)&t;/* BSC ALF 3 SCSI Controller */
DECL|macro|MANUF_BSC3
mdefine_line|#define MANUF_BSC3             (0x0801)&t;/* BSC */
DECL|macro|PROD_ALF_2_SCSI
mdefine_line|#define PROD_ALF_2_SCSI        (0x01)&t;/* ALF 2 SCSI Controller */
DECL|macro|PROD_ALF_3_SCSI_2
mdefine_line|#define PROD_ALF_3_SCSI_2      (0x03)&t;/* ALF 3 SCSI Controller */
DECL|macro|MANUF_C_LTD
mdefine_line|#define MANUF_C_LTD            (0x0802)&t;/* C Ltd. */
DECL|macro|PROD_KRONOS_SCSI
mdefine_line|#define PROD_KRONOS_SCSI       (0x04)&t;/* Kronos SCSI Controller */
DECL|macro|PROD_A1000_SCSI_2
mdefine_line|#define PROD_A1000_SCSI_2      (0x0C)&t;/* A1000 SCSI Controller */
DECL|macro|MANUF_JOCHHEIM
mdefine_line|#define MANUF_JOCHHEIM         (0x0804)&t;/* Jochheim */
DECL|macro|PROD_JOCHHEIM_RAM
mdefine_line|#define PROD_JOCHHEIM_RAM      (0x01)&t;/* Jochheim RAM */
DECL|macro|MANUF_CHECKPOINT
mdefine_line|#define MANUF_CHECKPOINT       (0x0807)&t;/* Checkpoint Technologies */
DECL|macro|PROD_SERIAL_SOLUTION
mdefine_line|#define PROD_SERIAL_SOLUTION   (0x00)&t;/* Serial Solution */
DECL|macro|MANUF_ICD
mdefine_line|#define MANUF_ICD              (0x0817)&t;/* ICD */
DECL|macro|PROD_ADVANTAGE_2000
mdefine_line|#define PROD_ADVANTAGE_2000    (0x01)&t;/* Advantage 2000 SCSI Controller */
DECL|macro|MANUF_KUPKE2
mdefine_line|#define MANUF_KUPKE2           (0x0819)&t;/* Kupke */
DECL|macro|PROD_KUPKE_SCSI_II
mdefine_line|#define PROD_KUPKE_SCSI_II     (0x02)&t;/* Golem SCSI-II Controller */
DECL|macro|PROD_GOLEM_BOX
mdefine_line|#define PROD_GOLEM_BOX         (0x03)&t;/* Golem Box */
DECL|macro|PROD_KUPKE_SCSI_AT
mdefine_line|#define PROD_KUPKE_SCSI_AT     (0x05)&t;/* SCSI/AT Controller */
DECL|macro|MANUF_HARDITAL
mdefine_line|#define MANUF_HARDITAL         (0x0820)&t;/* Hardital Synthesis */
DECL|macro|PROD_TQM
mdefine_line|#define PROD_TQM               (0x14)&t;/* TQM 68030+68882 Turbo Board */
DECL|macro|MANUF_BSC2
mdefine_line|#define MANUF_BSC2             (0x082C)&t;/* BSC */
DECL|macro|PROD_OKTAGON_SCSI
mdefine_line|#define PROD_OKTAGON_SCSI      (0x05)&t;/* BSC Oktagon 2008 SCSI Controller */
DECL|macro|PROD_TANDEM
mdefine_line|#define PROD_TANDEM            (0x06)&t;/* BSC Tandem AT-2008/508 IDE */
DECL|macro|PROD_OKTAGON_RAM
mdefine_line|#define PROD_OKTAGON_RAM       (0x08)&t;/* BSC Oktagon 2008 RAM */
DECL|macro|PROD_MULTIFACE_I
mdefine_line|#define PROD_MULTIFACE_I       (0x10)&t;/* Alfa Data MultiFace I */
DECL|macro|PROD_MULTIFACE_II
mdefine_line|#define PROD_MULTIFACE_II      (0x11)&t;/* Alfa Data MultiFace II */
DECL|macro|PROD_MULTIFACE_III
mdefine_line|#define PROD_MULTIFACE_III     (0x12)&t;/* Alfa Data MultiFace III */
DECL|macro|PROD_ISDN_MASTERCARD
mdefine_line|#define PROD_ISDN_MASTERCARD   (0x40)&t;/* BSC ISDN MasterCard */
DECL|macro|PROD_ISDN_MASTERCARD_2
mdefine_line|#define PROD_ISDN_MASTERCARD_2 (0x41)&t;/* BSC ISDN MasterCard II */
DECL|macro|MANUF_ADV_SYS_SOFT
mdefine_line|#define MANUF_ADV_SYS_SOFT     (0x0836)&t;/* Advanced Systems &amp; Software */
DECL|macro|PROD_NEXUS_SCSI
mdefine_line|#define PROD_NEXUS_SCSI        (0x01)&t;/* Nexus SCSI Controller */
DECL|macro|PROD_NEXUS_RAM
mdefine_line|#define PROD_NEXUS_RAM         (0x08)&t;/* Nexus RAM */
DECL|macro|MANUF_IMPULSE
mdefine_line|#define MANUF_IMPULSE          (0x0838)&t;/* Impulse */
DECL|macro|PROD_FIRECRACKER_24
mdefine_line|#define PROD_FIRECRACKER_24    (0x00)&t;/* FireCracker 24 */
DECL|macro|MANUF_IVS
mdefine_line|#define MANUF_IVS              (0x0840)&t;/* IVS */
DECL|macro|PROD_GRANDSLAM
mdefine_line|#define PROD_GRANDSLAM         (0x04)&t;/* GrandSlam RAM */
DECL|macro|PROD_IVS_OVERDRIVE
mdefine_line|#define PROD_IVS_OVERDRIVE     (0x10)&t;/* OverDrive HD */
DECL|macro|PROD_TRUMPCARD_CLASSIC
mdefine_line|#define PROD_TRUMPCARD_CLASSIC (0x30)&t;/* Trumpcard Classic SCSI Controller */
DECL|macro|PROD_TRUMPCARD_PRO
mdefine_line|#define PROD_TRUMPCARD_PRO     (0x34)&t;/* Trumpcard Pro SCSI Controller */
DECL|macro|PROD_META_4
mdefine_line|#define PROD_META_4            (0x40)&t;/* Meta-4 RAM */
DECL|macro|PROD_VECTOR
mdefine_line|#define PROD_VECTOR            (0xF3)&t;/* Vector SCSI Controller */
DECL|macro|MANUF_VECTOR
mdefine_line|#define MANUF_VECTOR           (0x0841)&t;/* Vector */
DECL|macro|PROD_CONNECTION
mdefine_line|#define PROD_CONNECTION        (0xE3)&t;/* Connection Serial IO */
DECL|macro|MANUF_XPERT_PRODEV
mdefine_line|#define MANUF_XPERT_PRODEV     (0x0845)&t;/* XPert/ProDev */
DECL|macro|PROD_VISIONA_RAM
mdefine_line|#define PROD_VISIONA_RAM       (0x01)&t;/* Visiona Graphics Board */
DECL|macro|PROD_VISIONA_REG
mdefine_line|#define PROD_VISIONA_REG       (0x02)
DECL|macro|PROD_MERLIN_RAM
mdefine_line|#define PROD_MERLIN_RAM        (0x03)&t;/* Merlin Graphics Board */
DECL|macro|PROD_MERLIN_REG
mdefine_line|#define PROD_MERLIN_REG        (0x04)
DECL|macro|MANUF_HYDRA_SYSTEMS
mdefine_line|#define MANUF_HYDRA_SYSTEMS    (0x0849)&t;/* Hydra Systems */
DECL|macro|PROD_AMIGANET
mdefine_line|#define PROD_AMIGANET          (0x01)&t;/* Amiganet Board */
DECL|macro|MANUF_SUNRIZE
mdefine_line|#define MANUF_SUNRIZE          (0x084F)&t;/* Sunrize Industries */
DECL|macro|PROD_AD516
mdefine_line|#define PROD_AD516             (0x02)&t;/* AD516 Audio */
DECL|macro|MANUF_TRICERATOPS
mdefine_line|#define MANUF_TRICERATOPS      (0x0850)&t;/* Triceratops */
DECL|macro|PROD_TRICERATOPS
mdefine_line|#define PROD_TRICERATOPS       (0x01)&t;/* Triceratops Multi I/O Board */
DECL|macro|MANUF_APPLIED_MAGIC
mdefine_line|#define MANUF_APPLIED_MAGIC    (0x0851)&t;/* Applied Magic Inc */
DECL|macro|PROD_DMI_RESOLVER
mdefine_line|#define PROD_DMI_RESOLVER      (0x01)&t;/* DMI Resolver Graphics Board */
DECL|macro|PROD_DIGITAL_BCASTER
mdefine_line|#define PROD_DIGITAL_BCASTER   (0x06)&t;/* Digital Broadcaster */
DECL|macro|MANUF_GFX_BASE
mdefine_line|#define MANUF_GFX_BASE         (0x085E)&t;/* GFX-Base */
DECL|macro|PROD_GDA_1_RAM
mdefine_line|#define PROD_GDA_1_RAM         (0x00)&t;/* GDA-1 Graphics Board */
DECL|macro|PROD_GDA_1_REG
mdefine_line|#define PROD_GDA_1_REG         (0x01)
DECL|macro|MANUF_ROCTEC
mdefine_line|#define MANUF_ROCTEC           (0x0860)&t;/* RocTec */
DECL|macro|PROD_RH_800C
mdefine_line|#define PROD_RH_800C           (0x01)&t;/* RH 800C Hard Disk Controller */
DECL|macro|PROD_RH_800C_RAM
mdefine_line|#define PROD_RH_800C_RAM       (0x01)&t;/* RH 800C RAM */
DECL|macro|MANUF_HELFRICH1
mdefine_line|#define MANUF_HELFRICH1        (0x0861)&t;/* Helfrich */
DECL|macro|PROD_RAINBOW3
mdefine_line|#define PROD_RAINBOW3          (0x21)&t;/* Rainbow3 Graphics Board */
DECL|macro|MANUF_SW_RESULT_ENTS
mdefine_line|#define MANUF_SW_RESULT_ENTS   (0x0866)&t;/* Software Result Enterprises */
DECL|macro|PROD_GG2PLUS
mdefine_line|#define PROD_GG2PLUS           (0x01)&t;/* GG2+ Bus Converter */
DECL|macro|MANUF_MASOBOSHI
mdefine_line|#define MANUF_MASOBOSHI        (0x086D)&t;/* Masoboshi */
DECL|macro|PROD_MASTER_CARD_RAM
mdefine_line|#define PROD_MASTER_CARD_RAM   (0x03)&t;/* Master Card RAM */
DECL|macro|PROD_MASTER_CARD_SCSI
mdefine_line|#define PROD_MASTER_CARD_SCSI  (0x04)&t;/* Master Card SCSI Controller */
DECL|macro|PROD_MVD_819
mdefine_line|#define PROD_MVD_819           (0x07)&t;/* MVD 819 */
DECL|macro|MANUF_DELACOMP
mdefine_line|#define MANUF_DELACOMP         (0x0873)&t;/* DelaComp */
DECL|macro|PROD_DELACOMP_RAM_2000
mdefine_line|#define PROD_DELACOMP_RAM_2000 (0x01)&t;/* RAM Expansion 2000 */
DECL|macro|MANUF_VILLAGE_TRONIC
mdefine_line|#define MANUF_VILLAGE_TRONIC   (0x0877)&t;/* Village Tronic */
DECL|macro|PROD_DOMINO_RAM
mdefine_line|#define PROD_DOMINO_RAM        (0x01)&t;/* Domino Graphics Board (RAM) */
DECL|macro|PROD_DOMINO_REG
mdefine_line|#define PROD_DOMINO_REG        (0x02)&t;/* Domino Graphics Board (REG) */
DECL|macro|PROD_PICASSO_II_RAM
mdefine_line|#define PROD_PICASSO_II_RAM    (0x0B)&t;/* Picasso II Graphics Board */
DECL|macro|PROD_PICASSO_II_REG
mdefine_line|#define PROD_PICASSO_II_REG    (0x0C)
DECL|macro|PROD_PICASSO_II_REG_2
mdefine_line|#define PROD_PICASSO_II_REG_2  (0x0D)
DECL|macro|PROD_ARIADNE
mdefine_line|#define PROD_ARIADNE           (0xC9)&t;/* Ariadne Ethernet */
DECL|macro|MANUF_UTILITIES_ULTD
mdefine_line|#define MANUF_UTILITIES_ULTD   (0x087B)&t;/* Utilities Unlimited */
DECL|macro|PROD_EMPLANT_DELUXE
mdefine_line|#define PROD_EMPLANT_DELUXE    (0x15)&t;/* Emplant Deluxe SCSI Controller */
DECL|macro|PROD_EMPLANT_DELUXE2
mdefine_line|#define PROD_EMPLANT_DELUXE2   (0x20)&t;/* Emplant Deluxe SCSI Controller */
DECL|macro|MANUF_AMITRIX
mdefine_line|#define MANUF_AMITRIX          (0x0880)&t;/* Amitrix */
DECL|macro|PROD_AMITRIX_MULTI_IO
mdefine_line|#define PROD_AMITRIX_MULTI_IO  (0x01)&t;/* Multi-IO */
DECL|macro|PROD_AMITRIX_CD_RAM
mdefine_line|#define PROD_AMITRIX_CD_RAM    (0x02)&t;/* CD-RAM Memory */
DECL|macro|MANUF_MTEC
mdefine_line|#define MANUF_MTEC             (0x0890)&t;/* MTEC Germany */
DECL|macro|PROD_MTEC_68030
mdefine_line|#define PROD_MTEC_68030        (0x03)&t;/* 68030 Turbo Board */
DECL|macro|PROD_MTEC_T1230
mdefine_line|#define PROD_MTEC_T1230        (0x20)&t;/* A1200 T68030/42 RTC Turbo Board */
DECL|macro|PROD_MTEC_RAM
mdefine_line|#define PROD_MTEC_RAM          (0x22)&t;/* MTEC 8MB RAM */
DECL|macro|MANUF_GVP2
mdefine_line|#define MANUF_GVP2             (0x0891)&t;/* Great Valley Products */
DECL|macro|PROD_SPECTRUM_RAM
mdefine_line|#define PROD_SPECTRUM_RAM      (0x01)&t;/* EGS 28/24 Spectrum Graphics Board */
DECL|macro|PROD_SPECTRUM_REG
mdefine_line|#define PROD_SPECTRUM_REG      (0x02)
DECL|macro|MANUF_HELFRICH2
mdefine_line|#define MANUF_HELFRICH2        (0x0893)&t;/* Helfrich */
DECL|macro|PROD_PICCOLO_RAM
mdefine_line|#define PROD_PICCOLO_RAM       (0x05)&t;/* Piccolo Graphics Board */
DECL|macro|PROD_PICCOLO_REG
mdefine_line|#define PROD_PICCOLO_REG       (0x06)
DECL|macro|PROD_PEGGY_PLUS
mdefine_line|#define PROD_PEGGY_PLUS        (0x07)&t;/* PeggyPlus MPEG Decoder Board */
DECL|macro|PROD_VIDEOCRUNCHER
mdefine_line|#define PROD_VIDEOCRUNCHER     (0x08)&t;/* VideoCruncher */
DECL|macro|PROD_SD64_RAM
mdefine_line|#define PROD_SD64_RAM          (0x0A)&t;/* SD64 Graphics Board */
DECL|macro|PROD_SD64_REG
mdefine_line|#define PROD_SD64_REG          (0x0B)
DECL|macro|MANUF_MACROSYSTEMS
mdefine_line|#define MANUF_MACROSYSTEMS     (0x089B)&t;/* MacroSystems USA */
DECL|macro|PROD_WARP_ENGINE
mdefine_line|#define PROD_WARP_ENGINE       (0x13)&t;/* Warp Engine 40xx SCSI Controller */
DECL|macro|MANUF_ELBOX
mdefine_line|#define MANUF_ELBOX            (0x089E)&t;/* ElBox Computer */
DECL|macro|PROD_ELBOX_1200
mdefine_line|#define PROD_ELBOX_1200        (0x06)&t;/* Elbox 1200/4 RAM */
DECL|macro|MANUF_HARMS_PROF
mdefine_line|#define MANUF_HARMS_PROF       (0x0A00)&t;/* Harms Professional */
DECL|macro|PROD_HARMS_030_PLUS
mdefine_line|#define PROD_HARMS_030_PLUS    (0x10)&t;/* 030 plus */
DECL|macro|PROD_3500_TURBO
mdefine_line|#define PROD_3500_TURBO        (0xD0)&t;/* 3500 Turbo board */
DECL|macro|MANUF_MICRONIK
mdefine_line|#define MANUF_MICRONIK         (0x0A50)&t;/* Micronik */
DECL|macro|PROD_RCA_120
mdefine_line|#define PROD_RCA_120           (0x0A)&t;/* RCA 120 RAM */
DECL|macro|MANUF_IMTRONICS2
mdefine_line|#define MANUF_IMTRONICS2       (0x1028)&t;/* Imtronics */
DECL|macro|PROD_HURRICANE_2800_3
mdefine_line|#define PROD_HURRICANE_2800_3  (0x39)&t;/* Hurricane 2800 68030 */
DECL|macro|PROD_HURRICANE_2800_4
mdefine_line|#define PROD_HURRICANE_2800_4  (0x57)&t;/* Hurricane 2800 68030 */
DECL|macro|MANUF_KUPKE3
mdefine_line|#define MANUF_KUPKE3           (0x1248)&t;/* Kupke */
DECL|macro|PROD_GOLEM_3000
mdefine_line|#define PROD_GOLEM_3000        (0x01)&t;/* Golem HD 3000 */
DECL|macro|MANUF_INFORMATION
mdefine_line|#define MANUF_INFORMATION      (0x157C)&t;/* Information */
DECL|macro|PROD_ISDN_ENGINE_I
mdefine_line|#define PROD_ISDN_ENGINE_I     (0x64)&t;/* ISDN Engine I */
DECL|macro|MANUF_VORTEX
mdefine_line|#define MANUF_VORTEX           (0x2017)&t;/* Vortex */
DECL|macro|PROD_GOLDEN_GATE_386SX
mdefine_line|#define PROD_GOLDEN_GATE_386SX (0x07)&t;/* Golden Gate 80386SX Board */
DECL|macro|PROD_GOLDEN_GATE_RAM
mdefine_line|#define PROD_GOLDEN_GATE_RAM   (0x08)&t;/* Golden Gate RAM */
DECL|macro|PROD_GOLDEN_GATE_486
mdefine_line|#define PROD_GOLDEN_GATE_486   (0x09)&t;/* Golden Gate 80486 Board */
DECL|macro|MANUF_DATAFLYER
mdefine_line|#define MANUF_DATAFLYER        (0x2062)&t;/* DataFlyer */
DECL|macro|PROD_DATAFLYER_4000SXS
mdefine_line|#define PROD_DATAFLYER_4000SXS (0x01)&t;/* DataFlyer 4000SX SCSI Controller */
DECL|macro|PROD_DATAFLYER_4000SXR
mdefine_line|#define PROD_DATAFLYER_4000SXR (0x02)&t;/* DataFlyer 4000SX RAM */
DECL|macro|MANUF_READYSOFT
mdefine_line|#define MANUF_READYSOFT        (0x2100)&t;/* ReadySoft */
DECL|macro|PROD_AMAX
mdefine_line|#define PROD_AMAX              (0x01)&t;/* AMax II/IV */
DECL|macro|MANUF_PHASE5
mdefine_line|#define MANUF_PHASE5           (0x2140)&t;/* Phase5 */
DECL|macro|PROD_BLIZZARD_RAM
mdefine_line|#define PROD_BLIZZARD_RAM      (0x01)&t;/* Blizzard RAM */
DECL|macro|PROD_BLIZZARD
mdefine_line|#define PROD_BLIZZARD          (0x02)&t;/* Blizzard */
DECL|macro|PROD_BLIZZARD_1220_IV
mdefine_line|#define PROD_BLIZZARD_1220_IV  (0x06)&t;/* Blizzard 1220-IV Turbo Board */
DECL|macro|PROD_FASTLANE_RAM
mdefine_line|#define PROD_FASTLANE_RAM      (0x0A)&t;/* FastLane RAM */
DECL|macro|PROD_FASTLANE_SCSI
mdefine_line|#define PROD_FASTLANE_SCSI     (0x0B)&t;/* FastLane/Blizzard 1230-II SCSI/CyberSCSI */
DECL|macro|PROD_CYBERSTORM_SCSI
mdefine_line|#define PROD_CYBERSTORM_SCSI   (0x0C)&t;/* Blizzard 1220/CyberStorm */
DECL|macro|PROD_BLIZZARD_1230_III
mdefine_line|#define PROD_BLIZZARD_1230_III (0x0D)&t;/* Blizzard 1230-III Turbo Board */
DECL|macro|PROD_BLIZZARD_1230_IV
mdefine_line|#define PROD_BLIZZARD_1230_IV  (0x11)&t;/* Blizzard 1230-IV/1260 Turbo Board */
DECL|macro|PROD_BLIZZARD_2060SCSI
mdefine_line|#define PROD_BLIZZARD_2060SCSI (0x18)&t;/* Blizzard 2060 SCSI Controller */
DECL|macro|PROD_CYBERSTORM_II
mdefine_line|#define PROD_CYBERSTORM_II     (0x19)&t;/* CyberStorm Mk II */
DECL|macro|PROD_CYBERVISION
mdefine_line|#define PROD_CYBERVISION       (0x22)&t;/* CyberVision64 Graphics Board */
DECL|macro|MANUF_DPS
mdefine_line|#define MANUF_DPS              (0x2169)&t;/* DPS */
DECL|macro|PROD_DPS_PAR
mdefine_line|#define PROD_DPS_PAR           (0x01)&t;/* Personal Animation Recorder */
DECL|macro|MANUF_APOLLO2
mdefine_line|#define MANUF_APOLLO2          (0x2200)&t;/* Apollo */
DECL|macro|PROD_A620
mdefine_line|#define PROD_A620              (0x00)&t;/* A620 68020 Accelerator */
DECL|macro|MANUF_APOLLO
mdefine_line|#define MANUF_APOLLO           (0x2222)&t;/* Apollo */
DECL|macro|PROD_AT_APOLLO
mdefine_line|#define PROD_AT_APOLLO         (0x22)&t;/* AT-Apollo */
DECL|macro|PROD_APOLLO_TURBO
mdefine_line|#define PROD_APOLLO_TURBO      (0x23)&t;/* Apollo Turbo Board */
DECL|macro|MANUF_UWE_GERLACH
mdefine_line|#define MANUF_UWE_GERLACH      (0x3FF7)&t;/* Uwe Gerlach */
DECL|macro|PROD_UG_RAM_ROM
mdefine_line|#define PROD_UG_RAM_ROM        (0xd4)&t;/* RAM/ROM */
DECL|macro|MANUF_MACROSYSTEMS2
mdefine_line|#define MANUF_MACROSYSTEMS2    (0x4754)&t;/* MacroSystems Germany */
DECL|macro|PROD_MAESTRO
mdefine_line|#define PROD_MAESTRO           (0x03)&t;/* Maestro */
DECL|macro|PROD_VLAB
mdefine_line|#define PROD_VLAB              (0x04)&t;/* VLab */
DECL|macro|PROD_MAESTRO_PRO
mdefine_line|#define PROD_MAESTRO_PRO       (0x05)&t;/* Maestro Pro */
DECL|macro|PROD_RETINA_Z2
mdefine_line|#define PROD_RETINA_Z2         (0x06)&t;/* Retina Z2 Graphics Board */
DECL|macro|PROD_MULTI_EVOLUTION
mdefine_line|#define PROD_MULTI_EVOLUTION   (0x08)&t;/* MultiEvolution */
DECL|macro|PROD_TOCCATA
mdefine_line|#define PROD_TOCCATA           (0x0C)&t;/* Toccata Sound Board */
DECL|macro|PROD_RETINA_Z3
mdefine_line|#define PROD_RETINA_Z3         (0x10)&t;/* Retina Z3 Graphics Board */
DECL|macro|PROD_VLAB_MOTION
mdefine_line|#define PROD_VLAB_MOTION       (0x12)&t;/* VLab Motion */
DECL|macro|PROD_FALCON_040
mdefine_line|#define PROD_FALCON_040        (0xFD)&t;/* Falcon &squot;040 Turbo Board */
DECL|macro|MANUF_COMBITEC
mdefine_line|#define MANUF_COMBITEC         (0x6766)&t;/* Combitec */
DECL|macro|MANUF_SKI
mdefine_line|#define MANUF_SKI              (0x8000)&t;/* SKI Peripherals */
DECL|macro|PROD_SKI_SCSI_SERIAL
mdefine_line|#define PROD_SKI_SCSI_SERIAL   (0x80)&t;/* SCSI / Dual Serial */
DECL|macro|MANUF_CAMERON
mdefine_line|#define MANUF_CAMERON          (0xAA01)&t;/* Cameron */
DECL|macro|PROD_CAMERON_SCANNER
mdefine_line|#define PROD_CAMERON_SCANNER   (0x10)&t;/* Scanner Interface */
DECL|macro|MANUF_REIS_WARE
mdefine_line|#define MANUF_REIS_WARE        (0xAA11)&t;/* Reis-Ware */
DECL|macro|PROD_RW_HANDYSCANNER
mdefine_line|#define PROD_RW_HANDYSCANNER   (0x11)&t;/* Handyscanner */
multiline_comment|/* Illegal Manufacturer IDs. These do NOT appear in arch/m68k/amiga/zorro.c! */
DECL|macro|MANUF_HACKER_INC
mdefine_line|#define MANUF_HACKER_INC       (0x07DB)&t;/* Hacker Inc. */
DECL|macro|PROD_HACKER_SCSI
mdefine_line|#define PROD_HACKER_SCSI       (0x01)&t;/* Hacker Inc. SCSI Controller */
DECL|macro|MANUF_RES_MNGT_FORCE
mdefine_line|#define MANUF_RES_MNGT_FORCE   (0x07DB)&t;/* Resource Management Force */
DECL|macro|PROD_QUICKNET
mdefine_line|#define PROD_QUICKNET          (0x02)&t;/* QuickNet Ethernet */
DECL|macro|MANUF_VECTOR2
mdefine_line|#define MANUF_VECTOR2          (0x07DB)&t;/* Vector */
DECL|macro|PROD_CONNECTION_2
mdefine_line|#define PROD_CONNECTION_2      (0xE0)&t;/* Vector Connection */
DECL|macro|PROD_CONNECTION_3
mdefine_line|#define PROD_CONNECTION_3      (0xE1)&t;/* Vector Connection */
DECL|macro|PROD_CONNECTION_4
mdefine_line|#define PROD_CONNECTION_4      (0xE2)&t;/* Vector Connection */
DECL|macro|PROD_CONNECTION_5
mdefine_line|#define PROD_CONNECTION_5      (0xE3)&t;/* Vector Connection */
multiline_comment|/*&n; * GVP&squot;s identifies most of their product through the &squot;extended&n; * product code&squot; (epc). The epc has to be and&squot;ed with the GVP_PRODMASK&n; * before the identification.&n; */
DECL|macro|GVP_PRODMASK
mdefine_line|#define GVP_PRODMASK    (0xf8)
DECL|macro|GVP_SCSICLKMASK
mdefine_line|#define GVP_SCSICLKMASK (0x01)
DECL|enum|GVP_ident
r_enum
id|GVP_ident
(brace
DECL|enumerator|GVP_GFORCE_040
id|GVP_GFORCE_040
op_assign
l_int|0x20
comma
DECL|enumerator|GVP_GFORCE_040_SCSI
id|GVP_GFORCE_040_SCSI
op_assign
l_int|0x30
comma
DECL|enumerator|GVP_A1291_SCSI
id|GVP_A1291_SCSI
op_assign
l_int|0x40
comma
DECL|enumerator|GVP_COMBO_R4
id|GVP_COMBO_R4
op_assign
l_int|0x60
comma
DECL|enumerator|GVP_COMBO_R4_SCSI
id|GVP_COMBO_R4_SCSI
op_assign
l_int|0x70
comma
DECL|enumerator|GVP_PHONEPAK
id|GVP_PHONEPAK
op_assign
l_int|0x78
comma
DECL|enumerator|GVP_IOEXT
id|GVP_IOEXT
op_assign
l_int|0x98
comma
DECL|enumerator|GVP_GFORCE_030
id|GVP_GFORCE_030
op_assign
l_int|0xa0
comma
DECL|enumerator|GVP_GFORCE_030_SCSI
id|GVP_GFORCE_030_SCSI
op_assign
l_int|0xb0
comma
DECL|enumerator|GVP_A530
id|GVP_A530
op_assign
l_int|0xc0
comma
DECL|enumerator|GVP_A530_SCSI
id|GVP_A530_SCSI
op_assign
l_int|0xd0
comma
DECL|enumerator|GVP_COMBO_R3
id|GVP_COMBO_R3
op_assign
l_int|0xe0
comma
DECL|enumerator|GVP_COMBO_R3_SCSI
id|GVP_COMBO_R3_SCSI
op_assign
l_int|0xf0
comma
DECL|enumerator|GVP_SERIESII
id|GVP_SERIESII
op_assign
l_int|0xf8
comma
)brace
suffix:semicolon
DECL|enum|GVP_flags
r_enum
id|GVP_flags
(brace
DECL|enumerator|GVP_IO
id|GVP_IO
op_assign
l_int|0x01
comma
DECL|enumerator|GVP_ACCEL
id|GVP_ACCEL
op_assign
l_int|0x02
comma
DECL|enumerator|GVP_SCSI
id|GVP_SCSI
op_assign
l_int|0x04
comma
DECL|enumerator|GVP_24BITDMA
id|GVP_24BITDMA
op_assign
l_int|0x08
comma
DECL|enumerator|GVP_25BITDMA
id|GVP_25BITDMA
op_assign
l_int|0x10
comma
DECL|enumerator|GVP_NOBANK
id|GVP_NOBANK
op_assign
l_int|0x20
comma
DECL|enumerator|GVP_14MHZ
id|GVP_14MHZ
op_assign
l_int|0x40
comma
)brace
suffix:semicolon
DECL|struct|Node
r_struct
id|Node
(brace
DECL|member|ln_Succ
r_struct
id|Node
op_star
id|ln_Succ
suffix:semicolon
multiline_comment|/* Pointer to next (successor) */
DECL|member|ln_Pred
r_struct
id|Node
op_star
id|ln_Pred
suffix:semicolon
multiline_comment|/* Pointer to previous (predecessor) */
DECL|member|ln_Type
id|u_char
id|ln_Type
suffix:semicolon
DECL|member|ln_Pri
r_char
id|ln_Pri
suffix:semicolon
multiline_comment|/* Priority, for sorting */
DECL|member|ln_Name
r_char
op_star
id|ln_Name
suffix:semicolon
multiline_comment|/* ID string, null terminated */
)brace
suffix:semicolon
DECL|struct|ExpansionRom
r_struct
id|ExpansionRom
(brace
multiline_comment|/* -First 16 bytes of the expansion ROM */
DECL|member|er_Type
id|u_char
id|er_Type
suffix:semicolon
multiline_comment|/* Board type, size and flags */
DECL|member|er_Product
id|u_char
id|er_Product
suffix:semicolon
multiline_comment|/* Product number, assigned by manufacturer */
DECL|member|er_Flags
id|u_char
id|er_Flags
suffix:semicolon
multiline_comment|/* Flags */
DECL|member|er_Reserved03
id|u_char
id|er_Reserved03
suffix:semicolon
multiline_comment|/* Must be zero ($ff inverted) */
DECL|member|er_Manufacturer
id|u_short
id|er_Manufacturer
suffix:semicolon
multiline_comment|/* Unique ID,ASSIGNED BY COMMODORE-AMIGA! */
DECL|member|er_SerialNumber
id|u_long
id|er_SerialNumber
suffix:semicolon
multiline_comment|/* Available for use by manufacturer */
DECL|member|er_InitDiagVec
id|u_short
id|er_InitDiagVec
suffix:semicolon
multiline_comment|/* Offset to optional &quot;DiagArea&quot; structure */
DECL|member|er_Reserved0c
id|u_char
id|er_Reserved0c
suffix:semicolon
DECL|member|er_Reserved0d
id|u_char
id|er_Reserved0d
suffix:semicolon
DECL|member|er_Reserved0e
id|u_char
id|er_Reserved0e
suffix:semicolon
DECL|member|er_Reserved0f
id|u_char
id|er_Reserved0f
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* er_Type board type bits */
DECL|macro|ERT_TYPEMASK
mdefine_line|#define ERT_TYPEMASK&t;0xc0
DECL|macro|ERT_ZORROII
mdefine_line|#define ERT_ZORROII&t;0xc0
DECL|macro|ERT_ZORROIII
mdefine_line|#define ERT_ZORROIII&t;0x80
multiline_comment|/* other bits defined in er_Type */
DECL|macro|ERTB_MEMLIST
mdefine_line|#define ERTB_MEMLIST&t;5&t;&t;/* Link RAM into free memory list */
DECL|macro|ERTF_MEMLIST
mdefine_line|#define ERTF_MEMLIST&t;(1&lt;&lt;5)
DECL|struct|ConfigDev
r_struct
id|ConfigDev
(brace
DECL|member|cd_Node
r_struct
id|Node
id|cd_Node
suffix:semicolon
DECL|member|cd_Flags
id|u_char
id|cd_Flags
suffix:semicolon
multiline_comment|/* (read/write) */
DECL|member|cd_Pad
id|u_char
id|cd_Pad
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|cd_Rom
r_struct
id|ExpansionRom
id|cd_Rom
suffix:semicolon
multiline_comment|/* copy of board&squot;s expansion ROM */
DECL|member|cd_BoardAddr
r_void
op_star
id|cd_BoardAddr
suffix:semicolon
multiline_comment|/* where in memory the board was placed */
DECL|member|cd_BoardSize
id|u_long
id|cd_BoardSize
suffix:semicolon
multiline_comment|/* size of board in bytes */
DECL|member|cd_SlotAddr
id|u_short
id|cd_SlotAddr
suffix:semicolon
multiline_comment|/* which slot number (PRIVATE) */
DECL|member|cd_SlotSize
id|u_short
id|cd_SlotSize
suffix:semicolon
multiline_comment|/* number of slots (PRIVATE) */
DECL|member|cd_Driver
r_void
op_star
id|cd_Driver
suffix:semicolon
multiline_comment|/* pointer to node of driver */
DECL|member|cd_NextCD
r_struct
id|ConfigDev
op_star
id|cd_NextCD
suffix:semicolon
multiline_comment|/* linked list of drivers to config */
DECL|member|cd_Unused
id|u_long
id|cd_Unused
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* for whatever the driver wants */
)brace
suffix:semicolon
macro_line|#else&t;/* __ASSEMBLY__ */
id|LN_Succ
op_assign
l_int|0
id|LN_Pred
op_assign
id|LN_Succ
op_plus
l_int|4
id|LN_Type
op_assign
id|LN_Pred
op_plus
l_int|4
id|LN_Pri
op_assign
id|LN_Type
op_plus
l_int|1
id|LN_Name
op_assign
id|LN_Pri
op_plus
l_int|1
id|LN_sizeof
op_assign
id|LN_Name
op_plus
l_int|4
id|ER_Type
op_assign
l_int|0
id|ER_Product
op_assign
id|ER_Type
op_plus
l_int|1
id|ER_Flags
op_assign
id|ER_Product
op_plus
l_int|1
id|ER_Reserved03
op_assign
id|ER_Flags
op_plus
l_int|1
id|ER_Manufacturer
op_assign
id|ER_Reserved03
op_plus
l_int|1
id|ER_SerialNumber
op_assign
id|ER_Manufacturer
op_plus
l_int|2
id|ER_InitDiagVec
op_assign
id|ER_SerialNumber
op_plus
l_int|4
id|ER_Reserved0c
op_assign
id|ER_InitDiagVec
op_plus
l_int|2
id|ER_Reserved0d
op_assign
id|ER_Reserved0c
op_plus
l_int|1
id|ER_Reserved0e
op_assign
id|ER_Reserved0d
op_plus
l_int|1
id|ER_Reserved0f
op_assign
id|ER_Reserved0e
op_plus
l_int|1
id|ER_sizeof
op_assign
id|ER_Reserved0f
op_plus
l_int|1
id|CD_Node
op_assign
l_int|0
id|CD_Flags
op_assign
id|CD_Node
op_plus
id|LN_sizeof
id|CD_Pad
op_assign
id|CD_Flags
op_plus
l_int|1
id|CD_Rom
op_assign
id|CD_Pad
op_plus
l_int|1
id|CD_BoardAddr
op_assign
id|CD_Rom
op_plus
id|ER_sizeof
id|CD_BoardSize
op_assign
id|CD_BoardAddr
op_plus
l_int|4
id|CD_SlotAddr
op_assign
id|CD_BoardSize
op_plus
l_int|4
id|CD_SlotSize
op_assign
id|CD_SlotAddr
op_plus
l_int|2
id|CD_Driver
op_assign
id|CD_SlotSize
op_plus
l_int|2
id|CD_NextCD
op_assign
id|CD_Driver
op_plus
l_int|4
id|CD_Unused
op_assign
id|CD_NextCD
op_plus
l_int|4
id|CD_sizeof
op_assign
id|CD_Unused
op_plus
(paren
l_int|4
op_star
l_int|4
)paren
macro_line|#endif&t;/* __ASSEMBLY__ */
macro_line|#ifndef __ASSEMBLY__
DECL|macro|ZORRO_NUM_AUTO
mdefine_line|#define ZORRO_NUM_AUTO&t;&t;16
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|zorro_num_autocon
suffix:semicolon
multiline_comment|/* # of autoconfig devices found */
r_extern
r_struct
id|ConfigDev
id|zorro_autocon
(braket
id|ZORRO_NUM_AUTO
)braket
suffix:semicolon
multiline_comment|/*&n; * Zorro Functions&n; */
r_extern
r_int
id|zorro_find
c_func
(paren
r_int
id|manuf
comma
r_int
id|prod
comma
r_int
id|part
comma
r_int
id|index
)paren
suffix:semicolon
r_extern
r_struct
id|ConfigDev
op_star
id|zorro_get_board
c_func
(paren
r_int
id|key
)paren
suffix:semicolon
r_extern
r_void
id|zorro_config_board
c_func
(paren
r_int
id|key
comma
r_int
id|part
)paren
suffix:semicolon
r_extern
r_void
id|zorro_unconfig_board
c_func
(paren
r_int
id|key
comma
r_int
id|part
)paren
suffix:semicolon
multiline_comment|/*&n; * Bitmask indicating portions of available Zorro II RAM that are unused&n; * by the system. Every bit represents a 64K chunk, for a maximum of 8MB&n; * (128 chunks, physical 0x00200000-0x009fffff).&n; *&n; * If you want to use (= allocate) portions of this RAM, you should clear&n; * the corresponding bits.&n; */
r_extern
id|u_long
id|zorro_unused_z2ram
(braket
l_int|4
)braket
suffix:semicolon
DECL|macro|Z2RAM_START
mdefine_line|#define Z2RAM_START&t;&t;(0x00200000)
DECL|macro|Z2RAM_END
mdefine_line|#define Z2RAM_END&t;&t;(0x00a00000)
DECL|macro|Z2RAM_SIZE
mdefine_line|#define Z2RAM_SIZE&t;&t;(0x00800000)
DECL|macro|Z2RAM_CHUNKSIZE
mdefine_line|#define Z2RAM_CHUNKSIZE&t;&t;(0x00010000)
DECL|macro|Z2RAM_CHUNKMASK
mdefine_line|#define Z2RAM_CHUNKMASK&t;&t;(0x0000ffff)
DECL|macro|Z2RAM_CHUNKSHIFT
mdefine_line|#define Z2RAM_CHUNKSHIFT&t;(16)
multiline_comment|/*&n; * Verbose Board Identification&n; */
r_extern
r_void
id|zorro_identify
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|zorro_get_list
c_func
(paren
r_char
op_star
id|buffer
)paren
suffix:semicolon
macro_line|#endif&t;/* !__ASSEMBLY__ */
macro_line|#endif&t;/* __KERNEL__ */
macro_line|#endif /* __ASMm68K_ZORRO_H */
eof
