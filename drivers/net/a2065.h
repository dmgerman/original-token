multiline_comment|/*&n; * Amiga Linux/68k A2065 Ethernet Driver&n; *&n; * (C) Copyright 1995 by Geert Uytterhoeven&n; *&t;&t;&t;(Geert.Uytterhoeven@cs.kuleuven.ac.be)&n; *&n; * ---------------------------------------------------------------------------&n; *&n; * This program is based on&n; *&n; *&t;ariadne.?:&t;Amiga Linux/68k Ariadne Ethernet Driver&n; *&t;&t;&t;(C) Copyright 1995 by Geert Uytterhoeven,&n; *&t;&t;&t;Peter De Schrijver&n; *&n; *&t;lance.c:&t;An AMD LANCE ethernet driver for linux.&n; *&t;&t;&t;Written 1993-94 by Donald Becker.&n; *&n; *&t;Am79C960:&t;PCnet(tm)-ISA Single-Chip Ethernet Controller&n; *&t;&t;&t;Advanced Micro Devices&n; *&t;&t;&t;Publication #16907, Rev. B, Amendment/0, May 1994&n; *&n; * ---------------------------------------------------------------------------&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file README.legal in the main directory of the Linux/68k&n; * distribution for more details.&n; *&n; * ---------------------------------------------------------------------------&n; *&n; * The A2065 is a Zorro-II board made by Commodore/Ameristar. It contains:&n; *&n; *&t;- an Am7990 Local Area Network Controller for Ethernet (LANCE) with&n; *&t;  both 10BASE-2 (thin coax) and AUI (DB-15) connectors&n; */
multiline_comment|/*&n; *&t;&t;Am7990 Local Area Network Controller for Ethernet (LANCE)&n; */
DECL|struct|Am7990
r_struct
id|Am7990
(brace
DECL|member|RDP
r_volatile
id|u_short
id|RDP
suffix:semicolon
multiline_comment|/* Register Data Port */
DECL|member|RAP
r_volatile
id|u_short
id|RAP
suffix:semicolon
multiline_comment|/* Register Address Port */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;&t;Am7990 Control and Status Registers&n; */
DECL|macro|CSR0
mdefine_line|#define CSR0&t;&t;0x0000&t;&t;/* LANCE Controller Status */
DECL|macro|CSR1
mdefine_line|#define CSR1&t;&t;0x0001&t;&t;/* IADR[15:0] */
DECL|macro|CSR2
mdefine_line|#define CSR2&t;&t;0x0002&t;&t;/* IADR[23:16] */
DECL|macro|CSR3
mdefine_line|#define CSR3&t;&t;0x0003&t;&t;/* Misc */
multiline_comment|/*&n; *&t;&t;Bit definitions for CSR0 (LANCE Controller Status)&n; */
DECL|macro|ERR
mdefine_line|#define ERR&t;&t;0x8000&t;&t;/* Error */
DECL|macro|BABL
mdefine_line|#define BABL&t;&t;0x4000&t;&t;/* Babble: Transmitted too many bits */
DECL|macro|CERR
mdefine_line|#define CERR&t;&t;0x2000&t;&t;/* No Heartbeat (10BASE-T) */
DECL|macro|MISS
mdefine_line|#define MISS&t;&t;0x1000&t;&t;/* Missed Frame */
DECL|macro|MERR
mdefine_line|#define MERR&t;&t;0x0800&t;&t;/* Memory Error */
DECL|macro|RINT
mdefine_line|#define RINT&t;&t;0x0400&t;&t;/* Receive Interrupt */
DECL|macro|TINT
mdefine_line|#define TINT&t;&t;0x0200&t;&t;/* Transmit Interrupt */
DECL|macro|IDON
mdefine_line|#define IDON&t;&t;0x0100&t;&t;/* Initialization Done */
DECL|macro|INTR
mdefine_line|#define INTR&t;&t;0x0080&t;&t;/* Interrupt Flag */
DECL|macro|INEA
mdefine_line|#define INEA&t;&t;0x0040&t;&t;/* Interrupt Enable */
DECL|macro|RXON
mdefine_line|#define RXON&t;&t;0x0020&t;&t;/* Receive On */
DECL|macro|TXON
mdefine_line|#define TXON&t;&t;0x0010&t;&t;/* Transmit On */
DECL|macro|TDMD
mdefine_line|#define TDMD&t;&t;0x0008&t;&t;/* Transmit Demand */
DECL|macro|STOP
mdefine_line|#define STOP&t;&t;0x0004&t;&t;/* Stop */
DECL|macro|STRT
mdefine_line|#define STRT&t;&t;0x0002&t;&t;/* Start */
DECL|macro|INIT
mdefine_line|#define INIT&t;&t;0x0001&t;&t;/* Initialize */
multiline_comment|/*&n; *&t;&t;Bit definitions for CSR3&n; */
DECL|macro|BSWP
mdefine_line|#define BSWP&t;&t;0x0004&t;&t;/* Byte Swap&n;&t;&t;&t;&t;&t;   (on for big endian byte order) */
DECL|macro|ACON
mdefine_line|#define ACON&t;&t;0x0002&t;&t;/* ALE Control&n;&t;&t;&t;&t;&t;   (on for active low ALE) */
DECL|macro|BCON
mdefine_line|#define BCON&t;&t;0x0001&t;&t;/* Byte Control */
multiline_comment|/*&n; *&t;&t;Initialization Block&n; */
DECL|struct|InitBlock
r_struct
id|InitBlock
(brace
DECL|member|Mode
id|u_short
id|Mode
suffix:semicolon
multiline_comment|/* Mode */
DECL|member|PADR
id|u_char
id|PADR
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Physical Address */
DECL|member|LADRF
id|u_long
id|LADRF
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Logical Address Filter */
DECL|member|RDRA
id|u_short
id|RDRA
suffix:semicolon
multiline_comment|/* Receive Descriptor Ring Address */
DECL|member|RLEN
id|u_short
id|RLEN
suffix:semicolon
multiline_comment|/* Receive Descriptor Ring Length */
DECL|member|TDRA
id|u_short
id|TDRA
suffix:semicolon
multiline_comment|/* Transmit Descriptor Ring Address */
DECL|member|TLEN
id|u_short
id|TLEN
suffix:semicolon
multiline_comment|/* Transmit Descriptor Ring Length */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;&t;Mode Flags&n; */
DECL|macro|PROM
mdefine_line|#define PROM&t;&t;0x8000&t;&t;/* Promiscuous Mode */
DECL|macro|INTL
mdefine_line|#define INTL&t;&t;0x0040&t;&t;/* Internal Loopback */
DECL|macro|DRTY
mdefine_line|#define DRTY&t;&t;0x0020&t;&t;/* Disable Retry */
DECL|macro|FCOLL
mdefine_line|#define FCOLL&t;&t;0x0010&t;&t;/* Force Collision */
DECL|macro|DXMTFCS
mdefine_line|#define DXMTFCS&t;&t;0x0008&t;&t;/* Disable Transmit CRC */
DECL|macro|LOOP
mdefine_line|#define LOOP&t;&t;0x0004&t;&t;/* Loopback Enable */
DECL|macro|DTX
mdefine_line|#define DTX&t;&t;0x0002&t;&t;/* Disable Transmitter */
DECL|macro|DRX
mdefine_line|#define DRX&t;&t;0x0001&t;&t;/* Disable Receiver */
multiline_comment|/*&n; *&t;&t;Receive Descriptor Ring Entry&n; */
DECL|struct|RDRE
r_struct
id|RDRE
(brace
DECL|member|RMD0
r_volatile
id|u_short
id|RMD0
suffix:semicolon
multiline_comment|/* LADR[15:0] */
DECL|member|RMD1
r_volatile
id|u_short
id|RMD1
suffix:semicolon
multiline_comment|/* HADR[23:16] | Receive Flags */
DECL|member|RMD2
r_volatile
id|u_short
id|RMD2
suffix:semicolon
multiline_comment|/* Buffer Byte Count&n;&t;&t;&t;&t;&t;   (two&squot;s complement) */
DECL|member|RMD3
r_volatile
id|u_short
id|RMD3
suffix:semicolon
multiline_comment|/* Message Byte Count */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;&t;Transmit Descriptor Ring Entry&n; */
DECL|struct|TDRE
r_struct
id|TDRE
(brace
DECL|member|TMD0
r_volatile
id|u_short
id|TMD0
suffix:semicolon
multiline_comment|/* LADR[15:0] */
DECL|member|TMD1
r_volatile
id|u_short
id|TMD1
suffix:semicolon
multiline_comment|/* HADR[23:16] | Transmit Flags */
DECL|member|TMD2
r_volatile
id|u_short
id|TMD2
suffix:semicolon
multiline_comment|/* Buffer Byte Count&n;&t;&t;&t;&t;&t;   (two&squot;s complement) */
DECL|member|TMD3
r_volatile
id|u_short
id|TMD3
suffix:semicolon
multiline_comment|/* Error Flags */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;&t;Receive Flags&n; */
DECL|macro|RF_OWN
mdefine_line|#define RF_OWN&t;&t;0x8000&t;&t;/* LANCE owns the descriptor */
DECL|macro|RF_ERR
mdefine_line|#define RF_ERR&t;&t;0x4000&t;&t;/* Error */
DECL|macro|RF_FRAM
mdefine_line|#define RF_FRAM&t;&t;0x2000&t;&t;/* Framing Error */
DECL|macro|RF_OFLO
mdefine_line|#define RF_OFLO&t;&t;0x1000&t;&t;/* Overflow Error */
DECL|macro|RF_CRC
mdefine_line|#define RF_CRC&t;&t;0x0800&t;&t;/* CRC Error */
DECL|macro|RF_BUFF
mdefine_line|#define RF_BUFF&t;&t;0x0400&t;&t;/* Buffer Error */
DECL|macro|RF_STP
mdefine_line|#define RF_STP&t;&t;0x0200&t;&t;/* Start of Packet */
DECL|macro|RF_ENP
mdefine_line|#define RF_ENP&t;&t;0x0100&t;&t;/* End of Packet */
multiline_comment|/*&n; *&t;&t;Transmit Flags&n; */
DECL|macro|TF_OWN
mdefine_line|#define TF_OWN&t;&t;0x8000&t;&t;/* LANCE owns the descriptor */
DECL|macro|TF_ERR
mdefine_line|#define TF_ERR&t;&t;0x4000&t;&t;/* Error */
DECL|macro|TF_RES
mdefine_line|#define TF_RES&t;&t;0x2000&t;&t;/* Reserved,&n;&t;&t;&t;&t;&t;   LANCE writes this with a zero */
DECL|macro|TF_MORE
mdefine_line|#define TF_MORE&t;&t;0x1000&t;&t;/* More than one retry needed */
DECL|macro|TF_ONE
mdefine_line|#define TF_ONE&t;&t;0x0800&t;&t;/* One retry needed */
DECL|macro|TF_DEF
mdefine_line|#define TF_DEF&t;&t;0x0400&t;&t;/* Deferred */
DECL|macro|TF_STP
mdefine_line|#define TF_STP&t;&t;0x0200&t;&t;/* Start of Packet */
DECL|macro|TF_ENP
mdefine_line|#define TF_ENP&t;&t;0x0100&t;&t;/* End of Packet */
multiline_comment|/*&n; *&t;&t;Error Flags&n; */
DECL|macro|EF_BUFF
mdefine_line|#define EF_BUFF &t;0x8000&t;&t;/* Buffer Error */
DECL|macro|EF_UFLO
mdefine_line|#define EF_UFLO &t;0x4000&t;&t;/* Underflow Error */
DECL|macro|EF_LCOL
mdefine_line|#define EF_LCOL &t;0x1000&t;&t;/* Late Collision */
DECL|macro|EF_LCAR
mdefine_line|#define EF_LCAR &t;0x0800&t;&t;/* Loss of Carrier */
DECL|macro|EF_RTRY
mdefine_line|#define EF_RTRY &t;0x0400&t;&t;/* Retry Error */
DECL|macro|EF_TDR
mdefine_line|#define EF_TDR&t;&t;0x003f&t;&t;/* Time Domain Reflectometry */
multiline_comment|/*&n; *&t;&t;A2065 Expansion Board Structure&n; */
DECL|struct|A2065Board
r_struct
id|A2065Board
(brace
DECL|member|Pad1
id|u_char
id|Pad1
(braket
l_int|0x4000
)braket
suffix:semicolon
DECL|member|Lance
r_struct
id|Am7990
id|Lance
suffix:semicolon
DECL|member|Pad2
id|u_char
id|Pad2
(braket
l_int|0x3ffc
)braket
suffix:semicolon
DECL|member|RAM
r_volatile
id|u_char
id|RAM
(braket
l_int|0x8000
)braket
suffix:semicolon
)brace
suffix:semicolon
eof
