multiline_comment|/*&n; * asm-m68k/zorro.h -- Amiga AutoConfig (Zorro) Expansion Device Definitions&n; *&n; * Copyright (C) 1995 Geert Uytterhoeven&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef _ASM_M68K_ZORRO_H_
DECL|macro|_ASM_M68K_ZORRO_H_
mdefine_line|#define _ASM_M68K_ZORRO_H_
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/amigatypes.h&gt;
multiline_comment|/*&n; * Defined Board Manufacturers&n; *&n; * Please update arch/m68k/amiga/zorro.c if you make changes here&n; * Many IDs were obtained by using ExpName V1.4 ((C) Richard K&#xfffd;rber)&n; * and by looking at the NetBSD-Amiga kernel source&n; */
DECL|macro|MANUF_MEMPHIS
mdefine_line|#define MANUF_MEMPHIS          (0x0100)&t;/* Memphis */
DECL|macro|PROD_STORMBRINGER
mdefine_line|#define PROD_STORMBRINGER      (0x00)&t;/* Stormbringer */
DECL|macro|MANUF_COMMODORE2
mdefine_line|#define MANUF_COMMODORE2       (0x0201)&t;/* Commodore Germany */
DECL|macro|PROD_A2088
mdefine_line|#define PROD_A2088             (0x01)&t;/* CBM A2088 Bridgeboard */
DECL|macro|PROD_A2386SX
mdefine_line|#define PROD_A2386SX           (0x67)&t;/* CBM A2386-SX Bridgeboard */
DECL|macro|MANUF_COMMODORE
mdefine_line|#define MANUF_COMMODORE        (0x0202)&t;/* Commodore USA */
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
DECL|macro|PROD_ROMULATOR
mdefine_line|#define PROD_ROMULATOR         (0x60)&t;/* CBM Romulator Card */
DECL|macro|PROD_A3000TESTFIX
mdefine_line|#define PROD_A3000TESTFIX      (0x61)&t;/* CBM A3000 Test Fixture */
DECL|macro|PROD_A2065
mdefine_line|#define PROD_A2065             (0x70)&t;/* CBM A2065 Ethernet Card */
DECL|macro|MANUF_CARDCO
mdefine_line|#define MANUF_CARDCO           (0x03EC)&t;/* Cardco */
DECL|macro|PROD_CC_A2410
mdefine_line|#define PROD_CC_A2410          (0xF5)&t;/* Cardco A2410 Hires Graphics Card */
DECL|macro|MANUF_MICROBOTICS
mdefine_line|#define MANUF_MICROBOTICS      (0x03F2)&t;/* MicroBotics */
DECL|macro|PROD_VXL_30
mdefine_line|#define PROD_VXL_30            (0x45)&t;/* VXL-30 Turbo Board */
DECL|macro|MANUF_ASDG
mdefine_line|#define MANUF_ASDG             (0x03FF)&t;/* ASDG */
DECL|macro|PROD_LAN_ROVER
mdefine_line|#define PROD_LAN_ROVER         (0xFE)&t;/* Lan Rover Ethernet */
DECL|macro|PROD_ASDG_DUAL_SERIAL
mdefine_line|#define PROD_ASDG_DUAL_SERIAL  (0xFF)&t;/* Dual Serial Card */
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
DECL|macro|PROD_WORDSYNC
mdefine_line|#define PROD_WORDSYNC          (0x0C)&t;/* Supra Wordsync SCSI Controller */
DECL|macro|PROD_WORDSYNC_II
mdefine_line|#define PROD_WORDSYNC_II       (0x0D)&t;/* Supra Wordsync II SCSI Controller */
DECL|macro|PROD_SUPRA_2400MODEM
mdefine_line|#define PROD_SUPRA_2400MODEM   (0x10)&t;/* Supra 2400 Modem */
DECL|macro|MANUF_CSA
mdefine_line|#define MANUF_CSA              (0x0422)&t;/* CSA */
DECL|macro|PROD_MAGNUM
mdefine_line|#define PROD_MAGNUM            (0x11)&t;/* Magnum 40 SCSI Controller */
DECL|macro|PROD_12GAUGE
mdefine_line|#define PROD_12GAUGE           (0x15)&t;/* 12 Gauge SCSI Controller */
DECL|macro|MANUF_HACKER
mdefine_line|#define MANUF_HACKER           (0x07DB)&t;/* Test only: no product definitions */
DECL|macro|MANUF_POWER_COMPUTING
mdefine_line|#define MANUF_POWER_COMPUTING  (0x07DC)&t;/* Power Computing */
DECL|macro|PROD_DKB_1240
mdefine_line|#define PROD_DKB_1240          (0x12)&t;/* Viper II Turbo Board (DKB 1240) */
DECL|macro|MANUF_GVP
mdefine_line|#define MANUF_GVP              (0x07E1)&t;/* Great Valley Products */
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
DECL|macro|PROD_GFORCE_040_SCSI
mdefine_line|#define PROD_GFORCE_040_SCSI   (0x16)&t;/* GForce 040 with SCSI (new) */
DECL|macro|PROD_GVPIV_24
mdefine_line|#define PROD_GVPIV_24          (0x20)&t;/* GVP IV-24 Graphics Board */
multiline_comment|/* #define PROD_GVPIO_EXT      (0xFF)*/
multiline_comment|/* GVP I/O Extender */
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
DECL|macro|MANUF_BSC
mdefine_line|#define MANUF_BSC              (0x07FE)&t;/* BSC */
DECL|macro|PROD_ALF_3_SCSI
mdefine_line|#define PROD_ALF_3_SCSI        (0x03)&t;/* BSC ALF 3 SCSI Controller */
DECL|macro|MANUF_C_LTD
mdefine_line|#define MANUF_C_LTD            (0x0802)&t;/* C Ltd. */
DECL|macro|PROD_KRONOS_SCSI
mdefine_line|#define PROD_KRONOS_SCSI       (0x04)&t;/* Kronos SCSI Controller */
DECL|macro|MANUF_JOCHHEIM
mdefine_line|#define MANUF_JOCHHEIM         (0x0804)&t;/* Jochheim */
DECL|macro|PROD_JOCHHEIM_RAM
mdefine_line|#define PROD_JOCHHEIM_RAM      (0x01)&t;/* Jochheim RAM */
DECL|macro|MANUF_CHECKPOINT
mdefine_line|#define MANUF_CHECKPOINT       (0x0807)&t;/* Checkpoint Technologies */
DECL|macro|PROD_SERIAL_SOLUTION
mdefine_line|#define PROD_SERIAL_SOLUTION   (0x00)&t;/* Serial Solution */
DECL|macro|MANUF_GOLEM
mdefine_line|#define MANUF_GOLEM            (0x0819)&t;/* Golem */
DECL|macro|PROD_GOLEM_SCSI_II
mdefine_line|#define PROD_GOLEM_SCSI_II     (0x02)&t;/* Golem SCSI-II Controller */
DECL|macro|MANUF_HARDITAL_SYNTHES
mdefine_line|#define MANUF_HARDITAL_SYNTHES (0x0817)&t;/* Hardital Synthesis */
DECL|macro|PROD_HARDITAL_SCSI
mdefine_line|#define PROD_HARDITAL_SCSI     (0x01)&t;/* Hardital Synthesis SCSI Controller */
DECL|macro|MANUF_HARDITAL2
mdefine_line|#define MANUF_HARDITAL2        (0x0820)&t;/* Hardital Synthesis */
DECL|macro|PROD_TQM
mdefine_line|#define PROD_TQM               (0x14)&t;/* TQM 68030+68882 Turbo Board */
DECL|macro|MANUF_BSC2
mdefine_line|#define MANUF_BSC2             (0x082C)&t;/* BSC */
DECL|macro|PROD_OKTAGON_SCSI
mdefine_line|#define PROD_OKTAGON_SCSI      (0x05)&t;/* BSC Oktagon 2008 SCSI Controller */
DECL|macro|PROD_TANDEM
mdefine_line|#define PROD_TANDEM            (0x06)&t;/* BSC Tandem */
DECL|macro|PROD_OKTAGON_RAM
mdefine_line|#define PROD_OKTAGON_RAM       (0x08)&t;/* BSC Oktagon 2008 RAM */
DECL|macro|PROD_MULTIFACE_I
mdefine_line|#define PROD_MULTIFACE_I       (0x10)&t;/* Alfa Data MultiFace I */
DECL|macro|PROD_MULTIFACE_II
mdefine_line|#define PROD_MULTIFACE_II      (0x11)&t;/* Alfa Data MultiFace II */
DECL|macro|PROD_MULTIFACE_III
mdefine_line|#define PROD_MULTIFACE_III     (0x12)&t;/* Alfa Data MultiFace III */
DECL|macro|PROD_ISDN_MASTER
mdefine_line|#define PROD_ISDN_MASTER       (0x40)&t;/* BSC ISDN Master */
DECL|macro|MANUF_ADV_SYS_SOFT
mdefine_line|#define MANUF_ADV_SYS_SOFT     (0x0836)&t;/* Advanced Systems &amp; Software */
DECL|macro|PROD_NEXUS_SCSI
mdefine_line|#define PROD_NEXUS_SCSI        (0x01)&t;/* Nexus SCSI Controller */
DECL|macro|PROD_NEXUS_RAM
mdefine_line|#define PROD_NEXUS_RAM         (0x08)&t;/* Nexus RAM */
DECL|macro|MANUF_IVS
mdefine_line|#define MANUF_IVS              (0x0840)&t;/* IVS */
DECL|macro|PROD_TRUMPCARD_500
mdefine_line|#define PROD_TRUMPCARD_500     (0x30)&t;/* Trumpcard 500 SCSI Controller */
DECL|macro|PROD_TRUMPCARD
mdefine_line|#define PROD_TRUMPCARD         (0x34)&t;/* Trumpcard SCSI Controller */
DECL|macro|PROD_VECTOR
mdefine_line|#define PROD_VECTOR            (0xF3)&t;/* Vector SCSI Controller */
DECL|macro|MANUF_XPERT_PRODEV
mdefine_line|#define MANUF_XPERT_PRODEV     (0x0845)&t;/* XPert/ProDev */
DECL|macro|PROD_MERLIN_RAM
mdefine_line|#define PROD_MERLIN_RAM        (0x03)&t;/* Merlin Graphics Board */
DECL|macro|PROD_MERLIN_REG
mdefine_line|#define PROD_MERLIN_REG        (0x04)
DECL|macro|MANUF_HYDRA_SYSTEMS
mdefine_line|#define MANUF_HYDRA_SYSTEMS    (0x0849)&t;/* Hydra Systems */
DECL|macro|PROD_AMIGANET
mdefine_line|#define PROD_AMIGANET          (0x01)&t;/* Amiganet Board */
DECL|macro|MANUF_DIG_MICRONICS
mdefine_line|#define MANUF_DIG_MICRONICS    (0x0851)&t;/* Digital Micronics Inc */
DECL|macro|PROD_DMI_RESOLVER
mdefine_line|#define PROD_DMI_RESOLVER      (0x01)&t;/* DMI Resolver Graphics Board */
DECL|macro|MANUF_HELFRICH1
mdefine_line|#define MANUF_HELFRICH1        (0x0861)&t;/* Helfrich */
DECL|macro|PROD_RAINBOW3
mdefine_line|#define PROD_RAINBOW3          (0x21)&t;/* Rainbow3 Graphics Board */
DECL|macro|MANUF_SW_RESULT_ENTS
mdefine_line|#define MANUF_SW_RESULT_ENTS   (0x0866)&t;/* Software Result Enterprises */
DECL|macro|PROD_GG2PLUS
mdefine_line|#define PROD_GG2PLUS           (0x01)&t;/* GG2+ Bus Converter */
DECL|macro|MANUF_VILLAGE_TRONIC
mdefine_line|#define MANUF_VILLAGE_TRONIC   (0x0877)&t;/* Village Tronic */
DECL|macro|PROD_PICASSO_II_RAM
mdefine_line|#define PROD_PICASSO_II_RAM    (0x0B)&t;/* Picasso II Graphics Board */
DECL|macro|PROD_PICASSO_II_REG
mdefine_line|#define PROD_PICASSO_II_REG    (0x0C)
DECL|macro|PROD_ARIADNE
mdefine_line|#define PROD_ARIADNE           (0xC9)&t;/* Ariadne Ethernet */
DECL|macro|MANUF_UTILITIES_ULTD
mdefine_line|#define MANUF_UTILITIES_ULTD   (0x087B)&t;/* Utilities Unlimited */
DECL|macro|PROD_EMPLANT_DELUXE
mdefine_line|#define PROD_EMPLANT_DELUXE    (0x15)&t;/* Emplant Deluxe SCSI Controller */
DECL|macro|PROD_EMPLANT_DELUXE2
mdefine_line|#define PROD_EMPLANT_DELUXE2   (0x20)&t;/* Emplant Deluxe SCSI Controller */
DECL|macro|MANUF_MTEC
mdefine_line|#define MANUF_MTEC             (0x0890)&t;/* MTEC Germany */
DECL|macro|PROD_MTEC_68030
mdefine_line|#define PROD_MTEC_68030        (0x03)&t;/* 68030 Turbo Board */
DECL|macro|PROD_MTEC_T1230
mdefine_line|#define PROD_MTEC_T1230        (0x20)&t;/* MTEC T1230/28 Turbo Board */
DECL|macro|MANUF_GVP2
mdefine_line|#define MANUF_GVP2             (0x0891)&t;/* Great Valley Products */
DECL|macro|PROD_SPECTRUM_RAM
mdefine_line|#define PROD_SPECTRUM_RAM      (0x01)&t;/* GVP Spectrum Graphics Board */
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
DECL|macro|PROD_SD64_RAM
mdefine_line|#define PROD_SD64_RAM          (0x0A)&t;/* SD64 Graphics Board */
DECL|macro|PROD_SD64_REG
mdefine_line|#define PROD_SD64_REG          (0x0B)
DECL|macro|MANUF_MACROSYSTEMS
mdefine_line|#define MANUF_MACROSYSTEMS     (0x089B)&t;/* MacroSystems USA */
DECL|macro|PROD_WARP_ENGINE
mdefine_line|#define PROD_WARP_ENGINE       (0x13)&t;/* Warp Engine SCSI Controller */
DECL|macro|MANUF_HARMS_PROF
mdefine_line|#define MANUF_HARMS_PROF       (0x0A00)&t;/* Harms Professional */
DECL|macro|PROD_3500_TURBO
mdefine_line|#define PROD_3500_TURBO        (0xD0)&t;/* 3500 Turbo board */
DECL|macro|MANUF_VORTEX
mdefine_line|#define MANUF_VORTEX           (0x2017)&t;/* Vortex */
DECL|macro|PROD_GOLDEN_GATE_386
mdefine_line|#define PROD_GOLDEN_GATE_386   (0x07)&t;/* Golden Gate 80386 Board */
DECL|macro|PROD_GOLDEN_GATE_RAM
mdefine_line|#define PROD_GOLDEN_GATE_RAM   (0x08)&t;/* Golden Gate RAM */
DECL|macro|PROD_GOLDEN_GATE_486
mdefine_line|#define PROD_GOLDEN_GATE_486   (0x09)&t;/* Golden Gate 80486 Board */
DECL|macro|MANUF_DATAFLYER
mdefine_line|#define MANUF_DATAFLYER        (0x2062)&t;/* DataFlyer */
DECL|macro|PROD_DATAFLYER_4000SX
mdefine_line|#define PROD_DATAFLYER_4000SX  (0x01)&t;/* DataFlyer 4000SX SCSI Controller */
DECL|macro|MANUF_PHASE5
mdefine_line|#define MANUF_PHASE5           (0x2140)&t;/* Phase5 */
DECL|macro|PROD_FASTLANE_RAM
mdefine_line|#define PROD_FASTLANE_RAM      (0x0A)&t;/* FastLane RAM */
DECL|macro|PROD_FASTLANE_SCSI
mdefine_line|#define PROD_FASTLANE_SCSI     (0x0B)&t;/* FastLane/Blizzard 1230-II SCSI */
DECL|macro|PROD_CYBERSTORM_SCSI
mdefine_line|#define PROD_CYBERSTORM_SCSI   (0x0C)&t;/* CyberStorm Fast SCSI-II Controller */
DECL|macro|PROD_BLIZZARD_1230_III
mdefine_line|#define PROD_BLIZZARD_1230_III (0x0D)&t;/* Blizzard 1230-III Turbo Board */
DECL|macro|PROD_BLIZZARD_1230_IV
mdefine_line|#define PROD_BLIZZARD_1230_IV  (0x11)&t;/* Blizzard 1230-IV Turbo Board */
DECL|macro|PROD_CYBERVISION
mdefine_line|#define PROD_CYBERVISION       (0x22)&t;/* CyberVision64 Graphics Board */
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
DECL|macro|PROD_RETINA_Z3
mdefine_line|#define PROD_RETINA_Z3         (0x10)&t;/* Retina Z3 Graphics Board */
DECL|macro|PROD_FALCON_040
mdefine_line|#define PROD_FALCON_040        (0xFD)&t;/* Falcon &squot;040 Turbo Board */
multiline_comment|/* Illegal Manufacturer IDs. These do NOT appear in amiga/zorro.c! */
DECL|macro|MANUF_HACKER_INC
mdefine_line|#define MANUF_HACKER_INC       (0x07DB)&t;/* Hacker Inc. */
DECL|macro|PROD_HACKER_SCSI
mdefine_line|#define PROD_HACKER_SCSI       (0x01)&t;/* Hacker Inc. SCSI Controller */
DECL|macro|MANUF_RES_MNGT_FORCE
mdefine_line|#define MANUF_RES_MNGT_FORCE   (0x07DB)&t;/* Resource Management Force */
DECL|macro|PROD_QUICKNET
mdefine_line|#define PROD_QUICKNET          (0x02)&t;/* QuickNet Ethernet */
multiline_comment|/*&n; * GVP&squot;s identifies most of their product through the &squot;extended&n; * product code&squot; (epc). The epc has to be and&squot;ed with the GVPEPCMASK&n; * before the identification.&n; */
DECL|macro|GVP_EPCMASK
mdefine_line|#define GVP_EPCMASK (0xf8)
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
macro_line|#ifdef CONFIG_ZORRO
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
macro_line|#endif CONFIG_ZORRO
macro_line|#endif&t;/* __ASSEMBLY__ */
macro_line|#endif /* _ASM_M68K_ZORRO_H_ */
eof
