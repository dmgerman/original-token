multiline_comment|/*&n; * $Id: dmascc.h,v 1.1 1997/12/01 10:44:55 oe1kib Exp $&n; *&n; * Driver for high-speed SCC boards (those with DMA support)&n; * Copyright (C) 1997 Klaus Kudielka&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
multiline_comment|/* Ioctls */
DECL|macro|SIOCGSCCPARAM
mdefine_line|#define SIOCGSCCPARAM SIOCDEVPRIVATE
DECL|macro|SIOCSSCCPARAM
mdefine_line|#define SIOCSSCCPARAM (SIOCDEVPRIVATE+1)
multiline_comment|/* Frequency of timer 0 */
DECL|macro|TMR_0_HZ
mdefine_line|#define TMR_0_HZ      25600
multiline_comment|/* Configurable parameters */
DECL|struct|scc_param
r_struct
id|scc_param
(brace
DECL|member|pclk_hz
r_int
id|pclk_hz
suffix:semicolon
multiline_comment|/* frequency of BRG input (read-only - don&squot;t change) */
DECL|member|brg_tc
r_int
id|brg_tc
suffix:semicolon
multiline_comment|/* baud rate generator terminal count - BRG disabled if &lt; 0 */
DECL|member|nrzi
r_int
id|nrzi
suffix:semicolon
multiline_comment|/* 0 (nrz), 1 (nrzi) */
DECL|member|clocks
r_int
id|clocks
suffix:semicolon
multiline_comment|/* see documentation */
DECL|member|txdelay
r_int
id|txdelay
suffix:semicolon
multiline_comment|/* [1/TMR_0_HZ] */
DECL|member|txtime
r_int
id|txtime
suffix:semicolon
multiline_comment|/* [1/HZ] */
DECL|member|sqdelay
r_int
id|sqdelay
suffix:semicolon
multiline_comment|/* [1/TMR_0_HZ] */
DECL|member|waittime
r_int
id|waittime
suffix:semicolon
multiline_comment|/* [1/TMR_0_HZ] */
DECL|member|slottime
r_int
id|slottime
suffix:semicolon
multiline_comment|/* [1/TMR_0_HZ] */
DECL|member|persist
r_int
id|persist
suffix:semicolon
multiline_comment|/* 0 ... 255 */
DECL|member|dma
r_int
id|dma
suffix:semicolon
multiline_comment|/* 1, 3 */
)brace
suffix:semicolon
eof
