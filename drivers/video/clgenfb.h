multiline_comment|/*&n; * drivers/video/clgenfb.h - Cirrus Logic chipset constants&n; *&n; * Copyright 1999 Jeff Garzik &lt;jgarzik@pobox.com&gt;&n; *&n; * Original clgenfb author:  Frank Neumann&n; *&n; * Based on retz3fb.c and clgen.c:&n; *      Copyright (C) 1997 Jes Sorensen&n; *      Copyright (C) 1996 Frank Neumann&n; *&n; ***************************************************************&n; *&n; * Format this code with GNU indent &squot;-kr -i8 -pcs&squot; options.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; *&n; */
multiline_comment|/* OLD COMMENT: definitions for Piccolo/SD64 VGA controller chip   */
multiline_comment|/* OLD COMMENT: these definitions might most of the time also work */
multiline_comment|/* OLD COMMENT: for other CL-GD542x/543x based boards..            */
multiline_comment|/*** External/General Registers ***/
DECL|macro|POS102
mdefine_line|#define POS102&t;0x102  &t;/* POS102 register */
DECL|macro|VSSM
mdefine_line|#define VSSM&t;0x46e8 &t;/* Adapter Sleep */
DECL|macro|VSSM2
mdefine_line|#define VSSM2&t;0x3c3&t;/* Motherboard Sleep */
multiline_comment|/*** VGA Sequencer Registers ***/
DECL|macro|SEQR0
mdefine_line|#define SEQR0&t;0x0&t;/* Reset */
multiline_comment|/* the following are from the &quot;extension registers&quot; group */
DECL|macro|SEQR6
mdefine_line|#define SEQR6&t;0x6&t;/* Unlock ALL Extensions */
DECL|macro|SEQR7
mdefine_line|#define SEQR7&t;0x7&t;/* Extended Sequencer Mode */
DECL|macro|SEQR8
mdefine_line|#define SEQR8&t;0x8&t;/* EEPROM Control */
DECL|macro|SEQR9
mdefine_line|#define SEQR9&t;0x9&t;/* Scratch Pad 0 (do not access!) */
DECL|macro|SEQRA
mdefine_line|#define SEQRA&t;0xa&t;/* Scratch Pad 1 (do not access!) */
DECL|macro|SEQRB
mdefine_line|#define SEQRB&t;0xb&t;/* VCLK0 Numerator */
DECL|macro|SEQRC
mdefine_line|#define SEQRC&t;0xc&t;/* VCLK1 Numerator */
DECL|macro|SEQRD
mdefine_line|#define SEQRD&t;0xd&t;/* VCLK2 Numerator */
DECL|macro|SEQRE
mdefine_line|#define SEQRE&t;0xe&t;/* VCLK3 Numerator */
DECL|macro|SEQRF
mdefine_line|#define SEQRF&t;0xf&t;/* DRAM Control */
DECL|macro|SEQR10
mdefine_line|#define SEQR10&t;0x10&t;/* Graphics Cursor X Position */
DECL|macro|SEQR11
mdefine_line|#define SEQR11&t;0x11&t;/* Graphics Cursor Y Position */
DECL|macro|SEQR12
mdefine_line|#define SEQR12&t;0x12&t;/* Graphics Cursor Attributes */
DECL|macro|SEQR13
mdefine_line|#define SEQR13&t;0x13&t;/* Graphics Cursor Pattern Address Offset */
DECL|macro|SEQR14
mdefine_line|#define SEQR14&t;0x14&t;/* Scratch Pad 2 (CL-GD5426/&squot;28 Only) (do not access!) */
DECL|macro|SEQR15
mdefine_line|#define SEQR15&t;0x15&t;/* Scratch Pad 3 (CL-GD5426/&squot;28 Only) (do not access!) */
DECL|macro|SEQR16
mdefine_line|#define SEQR16&t;0x16&t;/* Performance Tuning (CL-GD5424/&squot;26/&squot;28 Only) */
DECL|macro|SEQR17
mdefine_line|#define SEQR17&t;0x17&t;/* Configuration ReadBack and Extended Control (CL-GF5428 Only) */
DECL|macro|SEQR18
mdefine_line|#define SEQR18&t;0x18&t;/* Signature Generator Control (Not CL-GD5420) */
DECL|macro|SEQR19
mdefine_line|#define SEQR19&t;0x19&t;/* Signature Generator Result Low Byte (Not CL-GD5420) */
DECL|macro|SEQR1A
mdefine_line|#define SEQR1A&t;0x1a&t;/* Signature Generator Result High Byte (Not CL-GD5420) */
DECL|macro|SEQR1B
mdefine_line|#define SEQR1B&t;0x1b&t;/* VCLK0 Denominator and Post-Scalar Value */
DECL|macro|SEQR1C
mdefine_line|#define SEQR1C&t;0x1c&t;/* VCLK1 Denominator and Post-Scalar Value */
DECL|macro|SEQR1D
mdefine_line|#define SEQR1D&t;0x1d&t;/* VCLK2 Denominator and Post-Scalar Value */
DECL|macro|SEQR1E
mdefine_line|#define SEQR1E&t;0x1e&t;/* VCLK3 Denominator and Post-Scalar Value */
DECL|macro|SEQR1F
mdefine_line|#define SEQR1F&t;0x1f&t;/* BIOS ROM write enable and MCLK Select */
multiline_comment|/*** CRT Controller Registers ***/
DECL|macro|CRT22
mdefine_line|#define CRT22&t;0x22&t;/* Graphics Data Latches ReadBack */
DECL|macro|CRT24
mdefine_line|#define CRT24&t;0x24&t;/* Attribute Controller Toggle ReadBack */
DECL|macro|CRT26
mdefine_line|#define CRT26&t;0x26&t;/* Attribute Controller Index ReadBack */
multiline_comment|/* the following are from the &quot;extension registers&quot; group */
DECL|macro|CRT19
mdefine_line|#define CRT19&t;0x19&t;/* Interlace End */
DECL|macro|CRT1A
mdefine_line|#define CRT1A&t;0x1a&t;/* Interlace Control */
DECL|macro|CRT1B
mdefine_line|#define CRT1B&t;0x1b&t;/* Extended Display Controls */
DECL|macro|CRT1C
mdefine_line|#define CRT1C&t;0x1c&t;/* Sync adjust and genlock register */
DECL|macro|CRT1D
mdefine_line|#define CRT1D&t;0x1d&t;/* Overlay Extended Control register */
DECL|macro|CRT25
mdefine_line|#define CRT25&t;0x25&t;/* Part Status Register */
DECL|macro|CRT27
mdefine_line|#define CRT27&t;0x27&t;/* ID Register */
DECL|macro|CRT51
mdefine_line|#define CRT51&t;0x51&t;/* P4 disable &quot;flicker fixer&quot; */
multiline_comment|/*** Graphics Controller Registers ***/
multiline_comment|/* the following are from the &quot;extension registers&quot; group */
DECL|macro|GR9
mdefine_line|#define GR9&t;0x9&t;/* Offset Register 0 */
DECL|macro|GRA
mdefine_line|#define GRA&t;0xa&t;/* Offset Register 1 */
DECL|macro|GRB
mdefine_line|#define GRB&t;0xb&t;/* Graphics Controller Mode Extensions */
DECL|macro|GRC
mdefine_line|#define GRC&t;0xc&t;/* Color Key (CL-GD5424/&squot;26/&squot;28 Only) */
DECL|macro|GRD
mdefine_line|#define GRD&t;0xd&t;/* Color Key Mask (CL-GD5424/&squot;26/&squot;28 Only) */
DECL|macro|GRE
mdefine_line|#define GRE&t;0xe&t;/* Miscellaneous Control (Cl-GD5428 Only) */
DECL|macro|GRF
mdefine_line|#define GRF&t;0xf&t;/* Display Compression Control register */
DECL|macro|GR10
mdefine_line|#define GR10&t;0x10&t;/* 16-bit Pixel BG Color High Byte (Not CL-GD5420) */
DECL|macro|GR11
mdefine_line|#define GR11&t;0x11&t;/* 16-bit Pixel FG Color High Byte (Not CL-GD5420) */
DECL|macro|GR12
mdefine_line|#define GR12&t;0x12&t;/* Background Color Byte 2 Register */
DECL|macro|GR13
mdefine_line|#define GR13&t;0x13&t;/* Foreground Color Byte 2 Register */
DECL|macro|GR14
mdefine_line|#define GR14&t;0x14&t;/* Background Color Byte 3 Register */
DECL|macro|GR15
mdefine_line|#define GR15&t;0x15&t;/* Foreground Color Byte 3 Register */
multiline_comment|/* the following are CL-GD5426/&squot;28 specific blitter registers */
DECL|macro|GR20
mdefine_line|#define GR20&t;0x20&t;/* BLT Width Low */
DECL|macro|GR21
mdefine_line|#define GR21&t;0x21&t;/* BLT Width High */
DECL|macro|GR22
mdefine_line|#define GR22&t;0x22&t;/* BLT Height Low */
DECL|macro|GR23
mdefine_line|#define GR23&t;0x23&t;/* BLT Height High */
DECL|macro|GR24
mdefine_line|#define GR24&t;0x24&t;/* BLT Destination Pitch Low */
DECL|macro|GR25
mdefine_line|#define GR25&t;0x25&t;/* BLT Destination Pitch High */
DECL|macro|GR26
mdefine_line|#define GR26&t;0x26&t;/* BLT Source Pitch Low */
DECL|macro|GR27
mdefine_line|#define GR27&t;0x27&t;/* BLT Source Pitch High */
DECL|macro|GR28
mdefine_line|#define GR28&t;0x28&t;/* BLT Destination Start Low */
DECL|macro|GR29
mdefine_line|#define GR29&t;0x29&t;/* BLT Destination Start Mid */
DECL|macro|GR2A
mdefine_line|#define GR2A    0x2a&t;/* BLT Destination Start High */
DECL|macro|GR2C
mdefine_line|#define GR2C&t;0x2c&t;/* BLT Source Start Low */
DECL|macro|GR2D
mdefine_line|#define GR2D&t;0x2d&t;/* BLT Source Start Mid */
DECL|macro|GR2E
mdefine_line|#define GR2E&t;0x2e&t;/* BLT Source Start High */
DECL|macro|GR2F
mdefine_line|#define GR2F&t;0x2f&t;/* Picasso IV Blitter compat mode..? */
DECL|macro|GR30
mdefine_line|#define GR30&t;0x30&t;/* BLT Mode */
DECL|macro|GR31
mdefine_line|#define GR31&t;0x31&t;/* BLT Start/Status */
DECL|macro|GR32
mdefine_line|#define GR32&t;0x32&t;/* BLT Raster Operation */
DECL|macro|GR33
mdefine_line|#define GR33&t;0x33&t;/* another P4 &quot;compat&quot; register.. */
DECL|macro|GR34
mdefine_line|#define GR34&t;0x34&t;/* Transparent Color Select Low */
DECL|macro|GR35
mdefine_line|#define GR35&t;0x35&t;/* Transparent Color Select High */
DECL|macro|GR38
mdefine_line|#define GR38&t;0x38&t;/* Source Transparent Color Mask Low */
DECL|macro|GR39
mdefine_line|#define GR39&t;0x39&t;/* Source Transparent Color Mask High */
multiline_comment|/*** Attribute Controller Registers ***/
DECL|macro|AR33
mdefine_line|#define AR33&t;0x33&t;/* The &quot;real&quot; Pixel Panning register (?) */
DECL|macro|AR34
mdefine_line|#define AR34&t;0x34&t;/* *TEST* */
multiline_comment|/* board types */
DECL|macro|BT_NONE
mdefine_line|#define BT_NONE     0
DECL|macro|BT_SD64
mdefine_line|#define BT_SD64     1
DECL|macro|BT_PICCOLO
mdefine_line|#define BT_PICCOLO  2
DECL|macro|BT_PICASSO
mdefine_line|#define BT_PICASSO  3
DECL|macro|BT_SPECTRUM
mdefine_line|#define BT_SPECTRUM 4
DECL|macro|BT_PICASSO4
mdefine_line|#define BT_PICASSO4 5
DECL|macro|BT_GD543X
mdefine_line|#define BT_GD543X    6&t;&t;/* Alpine family */
DECL|macro|BT_GD5480
mdefine_line|#define BT_GD5480    7
eof
