multiline_comment|/*     &n; **********************************************************************&n; *     icardwav.h&n; *     Copyright 1999, 2000 Creative Labs, Inc. &n; * &n; ********************************************************************** &n; * &n; *     Date                 Author          Summary of changes &n; *     ----                 ------          ------------------ &n; *     October 20, 1999     Bertrand Lee    base code release &n; * &n; ********************************************************************** &n; * &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version. &n; * &n; *     This program is distributed in the hope that it will be useful, &n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of &n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the &n; *     GNU General Public License for more details. &n; * &n; *     You should have received a copy of the GNU General Public &n; *     License along with this program; if not, write to the Free &n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, &n; *     USA. &n; * &n; ********************************************************************** &n; */
macro_line|#ifndef _ICARDWAV_H
DECL|macro|_ICARDWAV_H
mdefine_line|#define _ICARDWAV_H
multiline_comment|/* Enumeration for SetControl */
r_enum
(brace
DECL|enumerator|WAVECURPOS
id|WAVECURPOS
op_assign
l_int|0x10
comma
)brace
suffix:semicolon
DECL|struct|wave_format
r_struct
id|wave_format
(brace
DECL|member|samplingrate
id|u32
id|samplingrate
suffix:semicolon
DECL|member|bitsperchannel
id|u32
id|bitsperchannel
suffix:semicolon
DECL|member|channels
id|u32
id|channels
suffix:semicolon
multiline_comment|/* 1 = Mono, 2 = Stereo */
)brace
suffix:semicolon
multiline_comment|/* emu10k1_wave states */
DECL|macro|CARDWAVE_STATE_STOPPED
mdefine_line|#define CARDWAVE_STATE_STOPPED     0x0001
DECL|macro|CARDWAVE_STATE_STARTED
mdefine_line|#define CARDWAVE_STATE_STARTED     0x0002
macro_line|#endif /* _ICARDWAV_H */
eof
