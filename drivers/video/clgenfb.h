multiline_comment|/* definitions for Piccolo/SD64 VGA controller chip   */
multiline_comment|/* these definitions might most of the time also work */
multiline_comment|/* for other CL-GD542x/543x based boards..            */
multiline_comment|/*** External/General Registers ***/
DECL|macro|POS102
mdefine_line|#define POS102&t;0x102  &t;/* POS102 register */
DECL|macro|VSSM
mdefine_line|#define VSSM&t;0x46e8 &t;/* Adapter Sleep */
DECL|macro|VSSM2
mdefine_line|#define VSSM2&t;0x3c3&t;/* Motherboard Sleep */
DECL|macro|MISC_W
mdefine_line|#define MISC_W&t;0x3c2&t;/* Miscellaneous Output register, write */
DECL|macro|MISC_R
mdefine_line|#define MISC_R&t;0x3cc&t;/* Miscellaneous Output register, read */
DECL|macro|FC_W
mdefine_line|#define FC_W&t;0x3da&t;/* Feature Control Register, write (color) */
DECL|macro|FC_R
mdefine_line|#define FC_R&t;0x3ca&t;/* Feature Control Register, read */
DECL|macro|FEAT
mdefine_line|#define FEAT&t;0x3c2&t;/* Input Status Register 0 */
DECL|macro|STAT
mdefine_line|#define STAT&t;0x3da&t;/* Input Status Register 1, read-only */
DECL|macro|M_3C6
mdefine_line|#define M_3C6&t;0x3c6&t;/* Pixel Mask */
DECL|macro|M_3C7_W
mdefine_line|#define M_3C7_W&t;0x3c7   /* Pixel Address Read Mode (write) */
DECL|macro|M_3C7_R
mdefine_line|#define M_3C7_R&t;0x3c7&t;/* DAC State (read-only */
DECL|macro|M_3C8
mdefine_line|#define M_3C8&t;0x3c8&t;/* Pixel Address Write Mode */
DECL|macro|M_3C9
mdefine_line|#define M_3C9&t;0x3c9&t;/* Pixel Data */
multiline_comment|/*** VGA Sequencer Registers ***/
DECL|macro|SEQRX
mdefine_line|#define SEQRX&t;0x3c4&t;/* Sequencer Index */
DECL|macro|SEQR0
mdefine_line|#define SEQR0&t;0x0&t;/* Reset */
DECL|macro|SEQR1
mdefine_line|#define SEQR1     0x1&t;/* Clocking Mode */
DECL|macro|SEQR2
mdefine_line|#define SEQR2&t;0x2&t;/* Plane Mask / Write Pixel Extension */
DECL|macro|SEQR3
mdefine_line|#define SEQR3&t;0x3&t;/* Character Map Select */
DECL|macro|SEQR4
mdefine_line|#define SEQR4&t;0x4&t;/* Memory Mode */
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
DECL|macro|CRTX
mdefine_line|#define CRTX&t;0x3d4&t;/* CRTC Index */
DECL|macro|CRT0
mdefine_line|#define&t;CRT0&t;0x0&t;/* Horizontal Total */
DECL|macro|CRT1
mdefine_line|#define CRT1&t;0x1&t;/* Horizontal Display End */
DECL|macro|CRT2
mdefine_line|#define CRT2&t;0x2&t;/* Horizontal Blanking Start */
DECL|macro|CRT3
mdefine_line|#define CRT3&t;0x3&t;/* Horizontal Blabking End */
DECL|macro|CRT4
mdefine_line|#define CRT4&t;0x4&t;/* Horizontal Sync Start */
DECL|macro|CRT5
mdefine_line|#define CRT5&t;0x5&t;/* Horizontal Sync End */
DECL|macro|CRT6
mdefine_line|#define CRT6 &t;0x6&t;/* Vertical Total */
DECL|macro|CRT7
mdefine_line|#define CRT7&t;0x7&t;/* Overflow */
DECL|macro|CRT8
mdefine_line|#define CRT8&t;0x8&t;/* Screen A Preset Row Scan */
DECL|macro|CRT9
mdefine_line|#define CRT9&t;0x9&t;/* Character Cell Height */
DECL|macro|CRTA
mdefine_line|#define CRTA&t;0xa&t;/* Text Cursor Start */
DECL|macro|CRTB
mdefine_line|#define CRTB&t;0xb&t;/* Text Cursor End */
DECL|macro|CRTC
mdefine_line|#define CRTC&t;0xc&t;/* Screen Start Address High */
DECL|macro|CRTD
mdefine_line|#define CRTD&t;0xd&t;/* Screen Start Address Low */
DECL|macro|CRTE
mdefine_line|#define CRTE&t;0xe&t;/* Text Cursor Location High */
DECL|macro|CRTF
mdefine_line|#define CRTF&t;0xf&t;/* Text Cursor Location Low */
DECL|macro|CRT10
mdefine_line|#define CRT10&t;0x10&t;/* Vertical Sync Start */
DECL|macro|CRT11
mdefine_line|#define CRT11&t;0x11&t;/* Vertical Sync End */
DECL|macro|CRT12
mdefine_line|#define CRT12&t;0x12&t;/* Vertical Display End */
DECL|macro|CRT13
mdefine_line|#define CRT13&t;0x13&t;/* Offset */
DECL|macro|CRT14
mdefine_line|#define CRT14&t;0x14&t;/* Underline Row Scan */
DECL|macro|CRT15
mdefine_line|#define CRT15  &t;0x15&t;/* Vertical Blanking Start */
DECL|macro|CRT16
mdefine_line|#define CRT16&t;0x16&t;/* Vertical Blanking End */
DECL|macro|CRT17
mdefine_line|#define CRT17&t;0x17&t;/* Mode Control */
DECL|macro|CRT18
mdefine_line|#define CRT18&t;0x18&t;/* Line Compare */
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
DECL|macro|GRX
mdefine_line|#define GRX&t;0x3ce&t;/* Graphics Controller Index */
DECL|macro|GR0
mdefine_line|#define GR0&t;0x0&t;/* Set/Reset, Write Mode 5 Background Extension */
DECL|macro|GR1
mdefine_line|#define GR1&t;0x1&t;/* Set/Reset Enable, Write Mode 4, 5 Foreground Ext. */
DECL|macro|GR2
mdefine_line|#define GR2&t;0x2&t;/* Color Compare */
DECL|macro|GR3
mdefine_line|#define GR3&t;0x3&t;/* Data Rotate */
DECL|macro|GR4
mdefine_line|#define GR4&t;0x4&t;/* Read Map Select */
DECL|macro|GR5
mdefine_line|#define GR5&t;0x5&t;/* Mode */
DECL|macro|GR6
mdefine_line|#define GR6&t;0x6&t;/* Miscellaneous */
DECL|macro|GR7
mdefine_line|#define GR7&t;0x7     /* Color Don&squot;t Care */
DECL|macro|GR8
mdefine_line|#define GR8&t;0x8&t;/* Bit Mask */
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
DECL|macro|ARX
mdefine_line|#define ARX&t;0x3c0&t;/* Attribute Controller Index */
DECL|macro|AR0
mdefine_line|#define AR0     0x0&t;/* Attribute Controller Palette Register 0 */
DECL|macro|AR1
mdefine_line|#define AR1     0x1&t;/* Attribute Controller Palette Register 1 */
DECL|macro|AR2
mdefine_line|#define AR2     0x2&t;/* Attribute Controller Palette Register 2 */
DECL|macro|AR3
mdefine_line|#define AR3     0x3&t;/* Attribute Controller Palette Register 3 */
DECL|macro|AR4
mdefine_line|#define AR4     0x4&t;/* Attribute Controller Palette Register 4 */
DECL|macro|AR5
mdefine_line|#define AR5     0x5&t;/* Attribute Controller Palette Register 5 */
DECL|macro|AR6
mdefine_line|#define AR6     0x6&t;/* Attribute Controller Palette Register 6 */
DECL|macro|AR7
mdefine_line|#define AR7     0x7&t;/* Attribute Controller Palette Register 7 */
DECL|macro|AR8
mdefine_line|#define AR8     0x8&t;/* Attribute Controller Palette Register 8 */
DECL|macro|AR9
mdefine_line|#define AR9     0x9&t;/* Attribute Controller Palette Register 9 */
DECL|macro|ARA
mdefine_line|#define ARA     0xa&t;/* Attribute Controller Palette Register 10 */
DECL|macro|ARB
mdefine_line|#define ARB     0xb&t;/* Attribute Controller Palette Register 11 */
DECL|macro|ARC
mdefine_line|#define ARC     0xc&t;/* Attribute Controller Palette Register 12 */
DECL|macro|ARD
mdefine_line|#define ARD     0xd&t;/* Attribute Controller Palette Register 13 */
DECL|macro|ARE
mdefine_line|#define ARE     0xe&t;/* Attribute Controller Palette Register 14 */
DECL|macro|ARF
mdefine_line|#define ARF     0xf&t;/* Attribute Controller Palette Register 15 */
DECL|macro|AR10
mdefine_line|#define AR10&t;0x10&t;/* Attribute Controller Mode Register */
DECL|macro|AR11
mdefine_line|#define AR11&t;0x11&t;/* Overscan (Border) Color Register */
DECL|macro|AR12
mdefine_line|#define AR12&t;0x12    /* Color Plane Enable Register */
DECL|macro|AR13
mdefine_line|#define AR13&t;0x13&t;/* Pixel Panning Register */
DECL|macro|AR14
mdefine_line|#define AR14&t;0x14&t;/* Color Select Register */
DECL|macro|AR33
mdefine_line|#define AR33&t;0x33&t;/* The &quot;real&quot; Pixel Panning register (?) */
DECL|macro|AR34
mdefine_line|#define AR34&t;0x34&t;/* *TEST* */
multiline_comment|/*** Extension Registers ***/
DECL|macro|HDR
mdefine_line|#define HDR&t;0x3c6&t;/* Hidden DAC Register (Not CL-GD5420) */
eof
