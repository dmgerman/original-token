multiline_comment|/*&n; *    linux/arch/m68k/amiga/zorro.c&n; *&n; *    Copyright (C) 1995 Geert Uytterhoeven&n; *&n; *    This file is subject to the terms and conditions of the GNU General Public&n; *    License.  See the file README.legal in the main directory of this archive&n; *    for more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/zorro.h&gt;
macro_line|#ifdef CONFIG_ZORRO
multiline_comment|/*&n;    *    Zorro Expansion Device Manufacturers and Products&n;    */
DECL|struct|Manufacturer
r_struct
id|Manufacturer
(brace
DECL|member|Name
r_char
op_star
id|Name
suffix:semicolon
DECL|member|ID
id|u_short
id|ID
suffix:semicolon
DECL|member|NumProd
id|u_short
id|NumProd
suffix:semicolon
DECL|member|Products
r_struct
id|Product
op_star
id|Products
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|Product
r_struct
id|Product
(brace
DECL|member|Name
r_char
op_star
id|Name
suffix:semicolon
DECL|member|ID
id|u_char
id|ID
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|GVP_Product
r_struct
id|GVP_Product
(brace
DECL|member|Name
r_char
op_star
id|Name
suffix:semicolon
DECL|member|ID
r_enum
id|GVP_ident
id|ID
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;    *    Macro&squot;s to make life easier&n;    */
DECL|macro|BEGIN_PROD
mdefine_line|#define BEGIN_PROD(id) static struct Product Prod_##id[] = {
DECL|macro|PROD
mdefine_line|#define PROD(name, id) &bslash;&n;   { name, PROD_##id },
DECL|macro|BEGIN_GVP_PROD
mdefine_line|#define BEGIN_GVP_PROD static struct GVP_Product Ext_Prod_GVP[] = {
DECL|macro|GVP_PROD
mdefine_line|#define GVP_PROD(name, id) &bslash;&n;   { name, GVP_##id },
DECL|macro|BEGIN_MANUF
mdefine_line|#define BEGIN_MANUF static struct Manufacturer Manufacturers[] = {
DECL|macro|MANUF
mdefine_line|#define MANUF(name, id) &bslash;&n;   { name, MANUF_##id, sizeof(Prod_##id)/sizeof(struct Product), Prod_##id },
DECL|macro|END
mdefine_line|#define END };
multiline_comment|/*&n;    *    Known Zorro Expansion Devices&n;    *&n;    *    Warning: Make sure the Manufacturer and Product names are not too&n;    *             long (max. 80 characters per board identification line)&n;    */
id|BEGIN_PROD
c_func
(paren
id|MEMPHIS
)paren
id|PROD
c_func
(paren
l_string|&quot;Stormbringer&quot;
comma
id|STORMBRINGER
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|COMMODORE2
)paren
id|PROD
c_func
(paren
l_string|&quot;A2088 Bridgeboard&quot;
comma
id|A2088
)paren
id|PROD
c_func
(paren
l_string|&quot;A2386-SX Bridgeboard&quot;
comma
id|A2386SX
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|COMMODORE
)paren
id|PROD
c_func
(paren
l_string|&quot;A2090/A2090A HD Controller&quot;
comma
id|A2090A
)paren
id|PROD
c_func
(paren
l_string|&quot;A590 SCSI Controller&quot;
comma
id|A590
)paren
id|PROD
c_func
(paren
l_string|&quot;A2091 SCSI Controller&quot;
comma
id|A2091
)paren
id|PROD
c_func
(paren
l_string|&quot;A2090B 2090 Autoboot Card&quot;
comma
id|A2090B
)paren
id|PROD
c_func
(paren
l_string|&quot;A2060 Arcnet Card&quot;
comma
id|ARCNET
)paren
id|PROD
c_func
(paren
l_string|&quot;A2052/58.RAM | 590/2091.RAM&quot;
comma
id|CBMRAM
)paren
id|PROD
c_func
(paren
l_string|&quot;A560 Memory Module&quot;
comma
id|A560RAM
)paren
id|PROD
c_func
(paren
l_string|&quot;A2232 Serial Prototype&quot;
comma
id|A2232PROTO
)paren
id|PROD
c_func
(paren
l_string|&quot;A2232 Serial Production&quot;
comma
id|A2232
)paren
id|PROD
c_func
(paren
l_string|&quot;A2620 68020/RAM Card&quot;
comma
id|A2620
)paren
id|PROD
c_func
(paren
l_string|&quot;A2630 68030/RAM Card&quot;
comma
id|A2630
)paren
id|PROD
c_func
(paren
l_string|&quot;A4091 SCSI Controller&quot;
comma
id|A4091
)paren
id|PROD
c_func
(paren
l_string|&quot;Romulator Card&quot;
comma
id|ROMULATOR
)paren
id|PROD
c_func
(paren
l_string|&quot;A3000 Test Fixture&quot;
comma
id|A3000TESTFIX
)paren
id|PROD
c_func
(paren
l_string|&quot;A2065 Ethernet Card&quot;
comma
id|A2065
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|CARDCO
)paren
id|PROD
c_func
(paren
l_string|&quot;Cardco A2410 Hires Graphics card&quot;
comma
id|CC_A2410
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|MICROBOTICS
)paren
id|PROD
c_func
(paren
l_string|&quot;VXL-30 Turbo Board&quot;
comma
id|VXL_30
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|ASDG
)paren
id|PROD
c_func
(paren
l_string|&quot;Lan Rover Ethernet&quot;
comma
id|LAN_ROVER
)paren
id|PROD
c_func
(paren
l_string|&quot;Dual Serial Card&quot;
comma
id|ASDG_DUAL_SERIAL
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|UNIV_OF_LOWELL
)paren
id|PROD
c_func
(paren
l_string|&quot;A2410 Hires Graphics Card&quot;
comma
id|A2410
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|AMERISTAR
)paren
id|PROD
c_func
(paren
l_string|&quot;A2065 Ethernet Card&quot;
comma
id|AMERISTAR2065
)paren
id|PROD
c_func
(paren
l_string|&quot;A560 Arcnet Card&quot;
comma
id|A560
)paren
id|PROD
c_func
(paren
l_string|&quot;A4066 Ethernet Card&quot;
comma
id|A4066
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|SUPRA
)paren
id|PROD
c_func
(paren
l_string|&quot;Wordsync SCSI Controller&quot;
comma
id|WORDSYNC
)paren
id|PROD
c_func
(paren
l_string|&quot;Wordsync II SCSI Controller&quot;
comma
id|WORDSYNC_II
)paren
id|PROD
c_func
(paren
l_string|&quot;2400 Modem&quot;
comma
id|SUPRA_2400MODEM
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|CSA
)paren
id|PROD
c_func
(paren
l_string|&quot;Magnum 40 SCSI Controller&quot;
comma
id|MAGNUM
)paren
id|PROD
c_func
(paren
l_string|&quot;12 Gauge SCSI Controller&quot;
comma
l_int|12
id|GAUGE
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|POWER_COMPUTING
)paren
id|PROD
c_func
(paren
l_string|&quot;Viper II Turbo Board (DKB 1240)&quot;
comma
id|DKB_1240
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|GVP
)paren
id|PROD
c_func
(paren
l_string|&quot;Generic GVP product&quot;
comma
id|GVP
)paren
id|PROD
c_func
(paren
l_string|&quot;Series II SCSI Controller&quot;
comma
id|GVPIISCSI
)paren
id|PROD
c_func
(paren
l_string|&quot;Series II SCSI Controller&quot;
comma
id|GVPIISCSI_2
)paren
id|PROD
c_func
(paren
l_string|&quot;Series II RAM&quot;
comma
id|GVPIIRAM
)paren
id|PROD
c_func
(paren
l_string|&quot;GFORCE 040 with SCSI Controller&quot;
comma
id|GFORCE_040_SCSI
)paren
id|PROD
c_func
(paren
l_string|&quot;IV-24 Graphics Board&quot;
comma
id|GVPIV_24
)paren
multiline_comment|/*&n;   PROD(&quot;I/O Extender&quot;, GVPIO_EXT)&n;*/
id|END
id|BEGIN_GVP_PROD
id|GVP_PROD
c_func
(paren
l_string|&quot;GFORCE 040&quot;
comma
id|GFORCE_040
)paren
id|GVP_PROD
c_func
(paren
l_string|&quot;GFORCE 040 with SCSI controller&quot;
comma
id|GFORCE_040_SCSI
)paren
id|GVP_PROD
c_func
(paren
l_string|&quot;A1291 SCSI controller&quot;
comma
id|A1291_SCSI
)paren
id|GVP_PROD
c_func
(paren
l_string|&quot;COMBO 030 R4&quot;
comma
id|COMBO_R4
)paren
id|GVP_PROD
c_func
(paren
l_string|&quot;COMBO 030 R4 with SCSI controller&quot;
comma
id|COMBO_R4_SCSI
)paren
id|GVP_PROD
c_func
(paren
l_string|&quot;Phone Pak&quot;
comma
id|PHONEPAK
)paren
id|GVP_PROD
c_func
(paren
l_string|&quot;IO-Extender&quot;
comma
id|IOEXT
)paren
id|GVP_PROD
c_func
(paren
l_string|&quot;GFORCE 030&quot;
comma
id|GFORCE_030
)paren
id|GVP_PROD
c_func
(paren
l_string|&quot;GFORCE 030 with SCSI controller&quot;
comma
id|GFORCE_030_SCSI
)paren
id|GVP_PROD
c_func
(paren
l_string|&quot;A530&quot;
comma
id|A530
)paren
id|GVP_PROD
c_func
(paren
l_string|&quot;A530 with SCSI&quot;
comma
id|A530_SCSI
)paren
id|GVP_PROD
c_func
(paren
l_string|&quot;COMBO 030 R3&quot;
comma
id|COMBO_R3
)paren
id|GVP_PROD
c_func
(paren
l_string|&quot;COMBO 030 R3 with SCSI controller&quot;
comma
id|COMBO_R3_SCSI
)paren
id|GVP_PROD
c_func
(paren
l_string|&quot;SERIES-II SCSI controller&quot;
comma
id|SERIESII
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|PPI
)paren
id|PROD
c_func
(paren
l_string|&quot;Mercury Turbo Board&quot;
comma
id|MERCURY
)paren
id|PROD
c_func
(paren
l_string|&quot;PP&amp;S A3000 68040 Turbo Board&quot;
comma
id|PPS_A3000_040
)paren
id|PROD
c_func
(paren
l_string|&quot;PP&amp;S A2000 68040 Turbo Board&quot;
comma
id|PPS_A2000_040
)paren
id|PROD
c_func
(paren
l_string|&quot;Zeus SCSI Controller&quot;
comma
id|ZEUS
)paren
id|PROD
c_func
(paren
l_string|&quot;PP&amp;S A500 68040 Turbo Board&quot;
comma
id|PPS_A500_040
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|BSC
)paren
id|PROD
c_func
(paren
l_string|&quot;ALF 3 SCSI Controller&quot;
comma
id|ALF_3_SCSI
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|C_LTD
)paren
id|PROD
c_func
(paren
l_string|&quot;Kronos SCSI Controller&quot;
comma
id|KRONOS_SCSI
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|JOCHHEIM
)paren
id|PROD
c_func
(paren
l_string|&quot;Jochheim RAM&quot;
comma
id|JOCHHEIM_RAM
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|CHECKPOINT
)paren
id|PROD
c_func
(paren
l_string|&quot;Serial Solution&quot;
comma
id|SERIAL_SOLUTION
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|GOLEM
)paren
id|PROD
c_func
(paren
l_string|&quot;Golem SCSI-II Controller&quot;
comma
id|GOLEM_SCSI_II
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|HARDITAL_SYNTHES
)paren
id|PROD
c_func
(paren
l_string|&quot;SCSI Controller&quot;
comma
id|HARDITAL_SCSI
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|BSC2
)paren
id|PROD
c_func
(paren
l_string|&quot;Oktagon 2008 SCSI Controller&quot;
comma
id|OKTAGON_SCSI
)paren
id|PROD
c_func
(paren
l_string|&quot;Tandem&quot;
comma
id|TANDEM
)paren
id|PROD
c_func
(paren
l_string|&quot;Oktagon 2008 RAM&quot;
comma
id|OKTAGON_RAM
)paren
id|PROD
c_func
(paren
l_string|&quot;Alfa Data MultiFace I&quot;
comma
id|MULTIFACE_I
)paren
id|PROD
c_func
(paren
l_string|&quot;Alfa Data MultiFace II&quot;
comma
id|MULTIFACE_II
)paren
id|PROD
c_func
(paren
l_string|&quot;Alfa Data MultiFace III&quot;
comma
id|MULTIFACE_III
)paren
id|PROD
c_func
(paren
l_string|&quot;ISDN Master&quot;
comma
id|ISDN_MASTER
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|ADV_SYS_SOFT
)paren
id|PROD
c_func
(paren
l_string|&quot;Nexus SCSI Controller&quot;
comma
id|NEXUS_SCSI
)paren
id|PROD
c_func
(paren
l_string|&quot;Nexus RAM&quot;
comma
id|NEXUS_RAM
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|IVS
)paren
id|PROD
c_func
(paren
l_string|&quot;Trumpcard 500 SCSI Controller&quot;
comma
id|TRUMPCARD_500
)paren
id|PROD
c_func
(paren
l_string|&quot;Trumpcard SCSI Controller&quot;
comma
id|TRUMPCARD
)paren
id|PROD
c_func
(paren
l_string|&quot;Vector SCSI Controller&quot;
comma
id|VECTOR
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|XPERT_PRODEV
)paren
id|PROD
c_func
(paren
l_string|&quot;Merlin Graphics Board (RAM)&quot;
comma
id|MERLIN_RAM
)paren
id|PROD
c_func
(paren
l_string|&quot;Merlin Graphics Board (REG)&quot;
comma
id|MERLIN_REG
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|HYDRA_SYSTEMS
)paren
id|PROD
c_func
(paren
l_string|&quot;Amiganet Board&quot;
comma
id|AMIGANET
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|DIG_MICRONICS
)paren
id|PROD
c_func
(paren
l_string|&quot;DMI Resolver Graphics Board&quot;
comma
id|DMI_RESOLVER
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|HELFRICH1
)paren
id|PROD
c_func
(paren
l_string|&quot;Rainbow3 Graphics Board&quot;
comma
id|RAINBOW3
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|SW_RESULT_ENTS
)paren
id|PROD
c_func
(paren
l_string|&quot;GG2+ Bus Converter&quot;
comma
id|GG2PLUS
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|VILLAGE_TRONIC
)paren
id|PROD
c_func
(paren
l_string|&quot;Ariadne Ethernet Card&quot;
comma
id|ARIADNE
)paren
id|PROD
c_func
(paren
l_string|&quot;Picasso II Graphics Board (RAM)&quot;
comma
id|PICASSO_II_RAM
)paren
id|PROD
c_func
(paren
l_string|&quot;Picasso II Graphics Board (REG)&quot;
comma
id|PICASSO_II_REG
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|UTILITIES_ULTD
)paren
id|PROD
c_func
(paren
l_string|&quot;Emplant Deluxe SCSI Controller&quot;
comma
id|EMPLANT_DELUXE
)paren
id|PROD
c_func
(paren
l_string|&quot;Emplant Deluxe SCSI Controller&quot;
comma
id|EMPLANT_DELUXE2
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|MTEC
)paren
id|PROD
c_func
(paren
l_string|&quot;68030 Turbo Board&quot;
comma
id|MTEC_68030
)paren
id|PROD
c_func
(paren
l_string|&quot;T1230/28 Turbo Board&quot;
comma
id|MTEC_T1230
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|GVP2
)paren
id|PROD
c_func
(paren
l_string|&quot;Spectrum Graphics Board (RAM)&quot;
comma
id|SPECTRUM_RAM
)paren
id|PROD
c_func
(paren
l_string|&quot;Spectrum Graphics Board (REG)&quot;
comma
id|SPECTRUM_REG
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|HELFRICH2
)paren
id|PROD
c_func
(paren
l_string|&quot;Piccolo Graphics Board (RAM)&quot;
comma
id|PICCOLO_RAM
)paren
id|PROD
c_func
(paren
l_string|&quot;Piccolo Graphics Board (REG)&quot;
comma
id|PICCOLO_REG
)paren
id|PROD
c_func
(paren
l_string|&quot;PeggyPlus MPEG Decoder Board&quot;
comma
id|PEGGY_PLUS
)paren
id|PROD
c_func
(paren
l_string|&quot;SD64 Graphics Board (RAM)&quot;
comma
id|SD64_RAM
)paren
id|PROD
c_func
(paren
l_string|&quot;SD64 Graphics Board (REG)&quot;
comma
id|SD64_REG
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|MACROSYSTEMS
)paren
id|PROD
c_func
(paren
l_string|&quot;Warp Engine SCSI Controller&quot;
comma
id|WARP_ENGINE
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|HARMS_PROF
)paren
id|PROD
c_func
(paren
l_string|&quot;3500 Turbo board&quot;
comma
l_int|3500
id|_TURBO
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|VORTEX
)paren
id|PROD
c_func
(paren
l_string|&quot;Golden Gate 80386 Board&quot;
comma
id|GOLDEN_GATE_386
)paren
id|PROD
c_func
(paren
l_string|&quot;Golden Gate RAM&quot;
comma
id|GOLDEN_GATE_RAM
)paren
id|PROD
c_func
(paren
l_string|&quot;Golden Gate 80486 Board&quot;
comma
id|GOLDEN_GATE_486
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|DATAFLYER
)paren
id|PROD
c_func
(paren
l_string|&quot;4000SX SCSI Controller&quot;
comma
id|DATAFLYER_4000SX
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|PHASE5
)paren
id|PROD
c_func
(paren
l_string|&quot;FastLane RAM&quot;
comma
id|FASTLANE_RAM
)paren
id|PROD
c_func
(paren
l_string|&quot;FastLane/Blizzard 1230-II SCSI Controller&quot;
comma
id|FASTLANE_SCSI
)paren
id|PROD
c_func
(paren
l_string|&quot;Blizzard 1230-III Turbo Board&quot;
comma
id|BLIZZARD_1230_III
)paren
id|PROD
c_func
(paren
l_string|&quot;Blizzard 1230-IV Turbo Board&quot;
comma
id|BLIZZARD_1230_IV
)paren
id|PROD
c_func
(paren
l_string|&quot;CyberVision64 Graphics Board&quot;
comma
id|CYBERVISION
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|APOLLO
)paren
id|PROD
c_func
(paren
l_string|&quot;AT-Apollo&quot;
comma
id|AT_APOLLO
)paren
id|PROD
c_func
(paren
l_string|&quot;Turbo Board&quot;
comma
id|APOLLO_TURBO
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|UWE_GERLACH
)paren
id|PROD
c_func
(paren
l_string|&quot;RAM/ROM&quot;
comma
id|UG_RAM_ROM
)paren
id|END
id|BEGIN_PROD
c_func
(paren
id|MACROSYSTEMS2
)paren
id|PROD
c_func
(paren
l_string|&quot;Maestro&quot;
comma
id|MAESTRO
)paren
id|PROD
c_func
(paren
l_string|&quot;VLab&quot;
comma
id|VLAB
)paren
id|PROD
c_func
(paren
l_string|&quot;Maestro Pro&quot;
comma
id|MAESTRO_PRO
)paren
id|PROD
c_func
(paren
l_string|&quot;Retina Z2 Graphics Board&quot;
comma
id|RETINA_Z2
)paren
id|PROD
c_func
(paren
l_string|&quot;MultiEvolution&quot;
comma
id|MULTI_EVOLUTION
)paren
id|PROD
c_func
(paren
l_string|&quot;Retina Z3 Graphics Board&quot;
comma
id|RETINA_Z3
)paren
id|END
id|BEGIN_MANUF
id|MANUF
c_func
(paren
l_string|&quot;Memphis&quot;
comma
id|MEMPHIS
)paren
id|MANUF
c_func
(paren
l_string|&quot;Commodore&quot;
comma
id|COMMODORE2
)paren
id|MANUF
c_func
(paren
l_string|&quot;Commodore&quot;
comma
id|COMMODORE
)paren
id|MANUF
c_func
(paren
l_string|&quot;Cardco&quot;
comma
id|CARDCO
)paren
id|MANUF
c_func
(paren
l_string|&quot;MicroBotics&quot;
comma
id|MICROBOTICS
)paren
id|MANUF
c_func
(paren
l_string|&quot;ASDG&quot;
comma
id|ASDG
)paren
id|MANUF
c_func
(paren
l_string|&quot;University of Lowell&quot;
comma
id|UNIV_OF_LOWELL
)paren
id|MANUF
c_func
(paren
l_string|&quot;Ameristar&quot;
comma
id|AMERISTAR
)paren
id|MANUF
c_func
(paren
l_string|&quot;Supra&quot;
comma
id|SUPRA
)paren
id|MANUF
c_func
(paren
l_string|&quot;CSA&quot;
comma
id|CSA
)paren
id|MANUF
c_func
(paren
l_string|&quot;Power Computing&quot;
comma
id|POWER_COMPUTING
)paren
id|MANUF
c_func
(paren
l_string|&quot;Great Valley Products&quot;
comma
id|GVP
)paren
id|MANUF
c_func
(paren
l_string|&quot;Progressive Peripherals&quot;
comma
id|PPI
)paren
id|MANUF
c_func
(paren
l_string|&quot;BSC&quot;
comma
id|BSC
)paren
id|MANUF
c_func
(paren
l_string|&quot;C Ltd.&quot;
comma
id|C_LTD
)paren
id|MANUF
c_func
(paren
l_string|&quot;Jochheim&quot;
comma
id|JOCHHEIM
)paren
id|MANUF
c_func
(paren
l_string|&quot;Checkpoint Technologies&quot;
comma
id|CHECKPOINT
)paren
id|MANUF
c_func
(paren
l_string|&quot;Golem&quot;
comma
id|GOLEM
)paren
id|MANUF
c_func
(paren
l_string|&quot;Hardital Synthesis&quot;
comma
id|HARDITAL_SYNTHES
)paren
id|MANUF
c_func
(paren
l_string|&quot;BSC&quot;
comma
id|BSC2
)paren
id|MANUF
c_func
(paren
l_string|&quot;Advanced Systems &amp; Software&quot;
comma
id|ADV_SYS_SOFT
)paren
id|MANUF
c_func
(paren
l_string|&quot;IVS&quot;
comma
id|IVS
)paren
id|MANUF
c_func
(paren
l_string|&quot;XPert/ProDev&quot;
comma
id|XPERT_PRODEV
)paren
id|MANUF
c_func
(paren
l_string|&quot;Hydra Systems&quot;
comma
id|HYDRA_SYSTEMS
)paren
id|MANUF
c_func
(paren
l_string|&quot;Digital Micronics&quot;
comma
id|DIG_MICRONICS
)paren
id|MANUF
c_func
(paren
l_string|&quot;Helfrich&quot;
comma
id|HELFRICH1
)paren
id|MANUF
c_func
(paren
l_string|&quot;Software Result Enterprises&quot;
comma
id|SW_RESULT_ENTS
)paren
id|MANUF
c_func
(paren
l_string|&quot;Village Tronic&quot;
comma
id|VILLAGE_TRONIC
)paren
id|MANUF
c_func
(paren
l_string|&quot;Utilities Unlimited&quot;
comma
id|UTILITIES_ULTD
)paren
id|MANUF
c_func
(paren
l_string|&quot;MTEC&quot;
comma
id|MTEC
)paren
id|MANUF
c_func
(paren
l_string|&quot;Great Valley Products&quot;
comma
id|GVP2
)paren
id|MANUF
c_func
(paren
l_string|&quot;Helfrich&quot;
comma
id|HELFRICH2
)paren
id|MANUF
c_func
(paren
l_string|&quot;MacroSystems&quot;
comma
id|MACROSYSTEMS
)paren
id|MANUF
c_func
(paren
l_string|&quot;Harms Professional&quot;
comma
id|HARMS_PROF
)paren
id|MANUF
c_func
(paren
l_string|&quot;Vortex&quot;
comma
id|VORTEX
)paren
id|MANUF
c_func
(paren
l_string|&quot;DataFlyer&quot;
comma
id|DATAFLYER
)paren
id|MANUF
c_func
(paren
l_string|&quot;Phase5&quot;
comma
id|PHASE5
)paren
id|MANUF
c_func
(paren
l_string|&quot;Apollo&quot;
comma
id|APOLLO
)paren
id|MANUF
c_func
(paren
l_string|&quot;Uwe Gerlach&quot;
comma
id|UWE_GERLACH
)paren
id|MANUF
c_func
(paren
l_string|&quot;MacroSystems&quot;
comma
id|MACROSYSTEMS2
)paren
id|END
DECL|macro|NUM_MANUF
mdefine_line|#define NUM_MANUF (sizeof(Manufacturers)/sizeof(struct Manufacturer))
DECL|macro|NUM_GVP_PROD
mdefine_line|#define NUM_GVP_PROD (sizeof(Ext_Prod_GVP)/sizeof(struct GVP_Product))
macro_line|#endif /* CONFIG_ZORRO */
multiline_comment|/*&n;    *    Configured Expansion Devices&n;    */
DECL|variable|BoardPartFlags
r_static
id|u_long
id|BoardPartFlags
(braket
id|NUM_AUTO
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/*&n;    *    Find the key for the next unconfigured expansion device of a specific&n;    *    type.&n;    *&n;    *    Part is a device specific number (0 &lt;= part &lt;= 31) to allow for the&n;    *    independent configuration of independent parts of an expansion board.&n;    *    Thanks to Jes Soerensen for this idea!&n;    *&n;    *    Index is used to specify the first board in the autocon list&n;    *    to be tested. It was inserted in order to solve the problem&n;    *    with the GVP boards that uses the same product code, but&n;    *    it should help if there are other companies uses the same&n;    *    method as GVP. Drivers for boards which are not using this&n;    *    method does not need to think of this - just set index = 0.&n;    *    &n;    *    Example:&n;    *&n;    *       while ((key = zorro_find(MY_MANUF, MY_PROD, MY_PART, 0))) {&n;    *          cd = zorro_get_board(key);&n;    *          initialise_this_board;&n;    *          zorro_config_board(key, MY_PART);&n;    *       }&n;    */
DECL|function|zorro_find
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
(brace
r_int
id|key
suffix:semicolon
r_struct
id|ConfigDev
op_star
id|cd
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_AMIGA
op_logical_or
op_logical_neg
id|AMIGAHW_PRESENT
c_func
(paren
id|ZORRO
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|part
OL
l_int|0
)paren
op_logical_or
(paren
id|part
OG
l_int|31
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;zorro_find: bad part %d&bslash;n&quot;
comma
id|part
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_for
c_loop
(paren
id|key
op_assign
id|index
op_plus
l_int|1
suffix:semicolon
id|key
op_le
id|boot_info.bi_amiga.num_autocon
suffix:semicolon
id|key
op_increment
)paren
(brace
id|cd
op_assign
op_amp
id|boot_info.bi_amiga.autocon
(braket
id|key
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cd-&gt;cd_Rom.er_Manufacturer
op_eq
id|manuf
)paren
op_logical_and
(paren
id|cd-&gt;cd_Rom.er_Product
op_eq
id|prod
)paren
op_logical_and
op_logical_neg
(paren
id|BoardPartFlags
(braket
id|key
op_minus
l_int|1
)braket
op_amp
(paren
l_int|1
op_lshift
id|part
)paren
)paren
)paren
r_break
suffix:semicolon
)brace
r_return
id|key
op_le
id|boot_info.bi_amiga.num_autocon
ques
c_cond
id|key
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;    *    Get the board for a specified key&n;    */
DECL|function|zorro_get_board
r_struct
id|ConfigDev
op_star
id|zorro_get_board
c_func
(paren
r_int
id|key
)paren
(brace
r_struct
id|ConfigDev
op_star
id|cd
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|key
OL
l_int|1
)paren
op_logical_or
(paren
id|key
OG
id|boot_info.bi_amiga.num_autocon
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;zorro_get_board: bad key %d&bslash;n&quot;
comma
id|key
)paren
suffix:semicolon
r_else
id|cd
op_assign
op_amp
id|boot_info.bi_amiga.autocon
(braket
id|key
op_minus
l_int|1
)braket
suffix:semicolon
r_return
id|cd
suffix:semicolon
)brace
multiline_comment|/*&n;    *    Mark a part of a board as configured&n;    */
DECL|function|zorro_config_board
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
(brace
r_if
c_cond
(paren
(paren
id|key
OL
l_int|1
)paren
op_logical_or
(paren
id|key
OG
id|boot_info.bi_amiga.num_autocon
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;zorro_config_board: bad key %d&bslash;n&quot;
comma
id|key
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|part
OL
l_int|0
)paren
op_logical_or
(paren
id|part
OG
l_int|31
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;zorro_config_board: bad part %d&bslash;n&quot;
comma
id|part
)paren
suffix:semicolon
r_else
id|BoardPartFlags
(braket
id|key
op_minus
l_int|1
)braket
op_or_assign
l_int|1
op_lshift
id|part
suffix:semicolon
)brace
multiline_comment|/*&n;    *    Mark a part of a board as unconfigured&n;    *&n;    *    This function is mainly intended for the unloading of LKMs&n;    */
DECL|function|zorro_unconfig_board
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
(brace
r_if
c_cond
(paren
(paren
id|key
OL
l_int|1
)paren
op_logical_or
(paren
id|key
OG
id|boot_info.bi_amiga.num_autocon
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;zorro_unconfig_board: bad key %d&bslash;n&quot;
comma
id|key
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|part
OL
l_int|0
)paren
op_logical_or
(paren
id|part
OG
l_int|31
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;zorro_unconfig_board: bad part %d&bslash;n&quot;
comma
id|part
)paren
suffix:semicolon
r_else
id|BoardPartFlags
(braket
id|key
op_minus
l_int|1
)braket
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|part
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ZORRO
multiline_comment|/*&n;    *    Identify an AutoConfig Expansion Device&n;    *&n;    *    If the board was configured by a Linux/m68k driver, an asterisk will&n;    *    be printed before the board address (except for unknown and `Hacker&n;    *    Test&squot; boards).&n;    */
DECL|function|identify
r_static
r_int
id|identify
c_func
(paren
r_int
id|devnum
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|ConfigDev
op_star
id|cd
suffix:semicolon
r_int
id|manuf
comma
id|prod
suffix:semicolon
id|u_long
id|addr
comma
id|size
suffix:semicolon
r_char
op_star
id|manufname
comma
op_star
id|prodname
comma
op_star
id|is_mem
suffix:semicolon
r_char
id|zorro
comma
id|mag
comma
id|configured
suffix:semicolon
r_int
id|identified
op_assign
l_int|0
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|k
comma
id|len
op_assign
l_int|0
suffix:semicolon
r_enum
id|GVP_ident
id|epc
suffix:semicolon
id|cd
op_assign
op_amp
id|boot_info.bi_amiga.autocon
(braket
id|devnum
)braket
suffix:semicolon
id|manuf
op_assign
id|cd-&gt;cd_Rom.er_Manufacturer
suffix:semicolon
id|prod
op_assign
id|cd-&gt;cd_Rom.er_Product
suffix:semicolon
id|addr
op_assign
(paren
id|u_long
)paren
id|cd-&gt;cd_BoardAddr
suffix:semicolon
id|size
op_assign
id|cd-&gt;cd_BoardSize
suffix:semicolon
id|configured
op_assign
id|BoardPartFlags
(braket
id|devnum
)braket
ques
c_cond
l_char|&squot;*&squot;
suffix:colon
l_char|&squot; &squot;
suffix:semicolon
id|manufname
op_assign
id|prodname
op_assign
l_string|&quot;&lt;UNKNOWN&gt;&quot;
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_MANUF
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|Manufacturers
(braket
id|i
)braket
dot
id|ID
op_eq
id|manuf
)paren
(brace
id|manufname
op_assign
id|Manufacturers
(braket
id|i
)braket
dot
id|Name
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|Manufacturers
(braket
id|i
)braket
dot
id|NumProd
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|Manufacturers
(braket
id|i
)braket
dot
id|Products
(braket
id|j
)braket
dot
id|ID
op_eq
id|prod
)paren
r_if
c_cond
(paren
(paren
id|manuf
op_ne
id|MANUF_GVP
)paren
op_logical_or
(paren
id|prod
op_ne
id|PROD_GVP
)paren
)paren
(brace
id|prodname
op_assign
id|Manufacturers
(braket
id|i
)braket
dot
id|Products
(braket
id|j
)braket
dot
id|Name
suffix:semicolon
id|identified
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
r_else
(brace
id|epc
op_assign
op_star
(paren
r_enum
id|GVP_ident
op_star
)paren
id|ZTWO_VADDR
c_func
(paren
id|addr
op_plus
l_int|0x8000
)paren
op_amp
id|GVP_EPCMASK
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|NUM_GVP_PROD
suffix:semicolon
id|k
op_increment
)paren
r_if
c_cond
(paren
id|Ext_Prod_GVP
(braket
id|k
)braket
dot
id|ID
op_eq
id|epc
)paren
(brace
id|prodname
op_assign
id|Ext_Prod_GVP
(braket
id|k
)braket
dot
id|Name
suffix:semicolon
id|identified
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|cd-&gt;cd_Rom.er_Type
op_amp
id|ERT_TYPEMASK
)paren
(brace
r_case
id|ERT_ZORROII
suffix:colon
id|zorro
op_assign
l_char|&squot;2&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ERT_ZORROIII
suffix:colon
id|zorro
op_assign
l_char|&squot;3&squot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|zorro
op_assign
l_char|&squot;?&squot;
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|size
op_amp
l_int|0xfffff
)paren
(brace
id|size
op_rshift_assign
l_int|10
suffix:semicolon
id|mag
op_assign
l_char|&squot;K&squot;
suffix:semicolon
)brace
r_else
(brace
id|size
op_rshift_assign
l_int|20
suffix:semicolon
id|mag
op_assign
l_char|&squot;M&squot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cd-&gt;cd_Rom.er_Type
op_amp
id|ERTF_MEMLIST
)paren
id|is_mem
op_assign
l_string|&quot; MEM&quot;
suffix:semicolon
r_else
id|is_mem
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_if
c_cond
(paren
id|identified
)paren
id|len
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot; %c0x%08lx: %s %s (Z%c, %ld%c%s)&bslash;n&quot;
comma
id|configured
comma
id|addr
comma
id|manufname
comma
id|prodname
comma
id|zorro
comma
id|size
comma
id|mag
comma
id|is_mem
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|manuf
op_eq
id|MANUF_HACKER
)paren
id|len
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;  0x%08lx: Hacker Test Board 0x%02x (Z%c, %ld%c%s)&bslash;n&quot;
comma
id|addr
comma
id|prod
comma
id|zorro
comma
id|size
comma
id|mag
comma
id|is_mem
)paren
suffix:semicolon
r_else
(brace
id|len
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;  0x%08lx: [%04x:%02x] made by %s (Z%c, %ld%c%s)&bslash;n&quot;
comma
id|addr
comma
id|manuf
comma
id|prod
comma
id|manufname
comma
id|zorro
comma
id|size
comma
id|mag
comma
id|is_mem
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;  Please report this unknown device to &quot;
l_string|&quot;Geert.Uytterhoeven@cs.kuleuven.ac.be&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n;    *    Identify all known AutoConfig Expansion Devices&n;    */
DECL|function|zorro_identify
r_void
id|zorro_identify
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
id|tmp
(braket
l_int|160
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|AMIGAHW_PRESENT
c_func
(paren
id|ZORRO
)paren
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Probing AutoConfig expansion device(s):&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|boot_info.bi_amiga.num_autocon
suffix:semicolon
id|i
op_increment
)paren
(brace
id|identify
c_func
(paren
id|i
comma
id|tmp
)paren
suffix:semicolon
id|printk
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|boot_info.bi_amiga.num_autocon
)paren
id|printk
c_func
(paren
l_string|&quot;No AutoConfig expansion devices present.&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;    *    Get the list of all AutoConfig Expansion Devices&n;    */
DECL|function|zorro_get_list
r_int
id|zorro_get_list
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
r_int
id|i
comma
id|j
comma
id|len
op_assign
l_int|0
suffix:semicolon
r_char
id|tmp
(braket
l_int|160
)braket
suffix:semicolon
r_if
c_cond
(paren
id|MACH_IS_AMIGA
op_logical_and
id|AMIGAHW_PRESENT
c_func
(paren
id|ZORRO
)paren
)paren
(brace
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;AutoConfig expansion devices:&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|boot_info.bi_amiga.num_autocon
suffix:semicolon
id|i
op_increment
)paren
(brace
id|j
op_assign
id|identify
c_func
(paren
id|i
comma
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_plus
id|j
op_ge
l_int|4075
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;4K limit reached!&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|strcpy
c_func
(paren
id|buffer
op_plus
id|len
comma
id|tmp
)paren
suffix:semicolon
id|len
op_add_assign
id|j
suffix:semicolon
)brace
)brace
r_return
id|len
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_ZORRO */
multiline_comment|/*&n;    *    Bitmask indicating portions of available Zorro II RAM that are unused&n;    *    by the system. Every bit represents a 64K chunk, for a maximum of 8MB&n;    *    (128 chunks, physical 0x00200000-0x009fffff).&n;    *&n;    *    If you want to use (= allocate) portions of this RAM, you should clear&n;    *    the corresponding bits.&n;    *&n;    *    Possible uses:&n;    *       - z2ram device&n;    *       - SCSI DMA bounce buffers&n;    */
DECL|variable|zorro_unused_z2ram
id|u_long
id|zorro_unused_z2ram
(braket
l_int|4
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|function|mark_region
r_static
r_void
id|mark_region
c_func
(paren
id|u_long
id|addr
comma
id|u_long
id|size
comma
r_int
id|flag
)paren
(brace
id|u_long
id|start
comma
id|end
comma
id|chunk
suffix:semicolon
r_if
c_cond
(paren
id|flag
)paren
(brace
id|start
op_assign
(paren
id|addr
op_plus
id|Z2RAM_CHUNKMASK
)paren
op_amp
op_complement
id|Z2RAM_CHUNKMASK
suffix:semicolon
id|end
op_assign
(paren
id|addr
op_plus
id|size
)paren
op_amp
op_complement
id|Z2RAM_CHUNKMASK
suffix:semicolon
)brace
r_else
(brace
id|start
op_assign
id|addr
op_amp
op_complement
id|Z2RAM_CHUNKMASK
suffix:semicolon
id|end
op_assign
(paren
id|addr
op_plus
id|size
op_plus
id|Z2RAM_CHUNKMASK
)paren
op_amp
op_complement
id|Z2RAM_CHUNKMASK
suffix:semicolon
)brace
r_if
c_cond
(paren
id|end
op_le
id|Z2RAM_START
op_logical_or
id|start
op_ge
id|Z2RAM_END
)paren
r_return
suffix:semicolon
id|start
op_assign
id|start
OL
id|Z2RAM_START
ques
c_cond
l_int|0x00000000
suffix:colon
id|start
op_minus
id|Z2RAM_START
suffix:semicolon
id|end
op_assign
id|end
OG
id|Z2RAM_END
ques
c_cond
id|Z2RAM_SIZE
suffix:colon
id|end
op_minus
id|Z2RAM_START
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
id|chunk
op_assign
id|start
op_rshift
id|Z2RAM_CHUNKSHIFT
suffix:semicolon
r_if
c_cond
(paren
id|flag
)paren
id|set_bit
c_func
(paren
id|chunk
comma
id|zorro_unused_z2ram
)paren
suffix:semicolon
r_else
id|clear_bit
c_func
(paren
id|chunk
comma
id|zorro_unused_z2ram
)paren
suffix:semicolon
id|start
op_add_assign
id|Z2RAM_CHUNKSIZE
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;    *    Initialization&n;    */
DECL|function|zorro_init
r_void
id|zorro_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|ConfigDev
op_star
id|cd
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|AMIGAHW_PRESENT
c_func
(paren
id|ZORRO
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/* Mark all available Zorro II memory */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|boot_info.bi_amiga.num_autocon
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cd
op_assign
op_amp
id|boot_info.bi_amiga.autocon
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|cd-&gt;cd_Rom.er_Type
op_amp
id|ERTF_MEMLIST
)paren
id|mark_region
c_func
(paren
(paren
id|u_long
)paren
id|cd-&gt;cd_BoardAddr
comma
id|cd-&gt;cd_BoardSize
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/* Unmark all used Zorro II memory */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|boot_info.num_memory
suffix:semicolon
id|i
op_increment
)paren
id|mark_region
c_func
(paren
id|boot_info.memory
(braket
id|i
)braket
dot
id|addr
comma
id|boot_info.memory
(braket
id|i
)braket
dot
id|size
comma
l_int|0
)paren
suffix:semicolon
)brace
eof