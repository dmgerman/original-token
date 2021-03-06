multiline_comment|/*&n; **********************************************************************&n; *     audio.c -- /dev/dsp interface for emu10k1 driver&n; *     Copyright 1999, 2000 Creative Labs, Inc.&n; *&n; **********************************************************************&n; *&n; *     Date                 Author          Summary of changes&n; *     ----                 ------          ------------------&n; *     October 20, 1999     Bertrand Lee    base code release&n; *     November 2, 1999&t;    Alan Cox        cleaned up types/leaks&n; *&n; **********************************************************************&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *     GNU General Public License for more details.&n; *&n; *     You should have received a copy of the GNU General Public&n; *     License along with this program; if not, write to the Free&n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139,&n; *     USA.&n; *&n; **********************************************************************&n; */
macro_line|#ifndef _AUDIO_H
DECL|macro|_AUDIO_H
mdefine_line|#define _AUDIO_H
DECL|macro|MINFRAGS
mdefine_line|#define MINFRAGS&t;2&t;/* _don&squot;t_ got bellow 2 */
DECL|struct|emu10k1_wavedevice
r_struct
id|emu10k1_wavedevice
(brace
DECL|member|card
r_struct
id|emu10k1_card
op_star
id|card
suffix:semicolon
DECL|member|wiinst
r_struct
id|wiinst
op_star
id|wiinst
suffix:semicolon
DECL|member|woinst
r_struct
id|woinst
op_star
id|woinst
suffix:semicolon
DECL|member|enablebits
id|u16
id|enablebits
suffix:semicolon
)brace
suffix:semicolon
r_void
id|emu10k1_waveout_bh
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_void
id|emu10k1_wavein_bh
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif /* _AUDIO_H */
eof
