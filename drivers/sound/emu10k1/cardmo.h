multiline_comment|/*&n; **********************************************************************&n; *     cardmo.h&n; *     Copyright 1999, 2000 Creative Labs, Inc.&n; *&n; **********************************************************************&n; *&n; *     Date                 Author          Summary of changes&n; *     ----                 ------          ------------------&n; *     October 20, 1999     Bertrand Lee    base code release&n; *     November 2, 1999     Alan Cox&t;    cleaned up&n; *&n; **********************************************************************&n; *&n; *     This program is free software; you can redistribute it and/or&n; *     modify it under the terms of the GNU General Public License as&n; *     published by the Free Software Foundation; either version 2 of&n; *     the License, or (at your option) any later version.&n; *&n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *     GNU General Public License for more details.&n; *&n; *     You should have received a copy of the GNU General Public&n; *     License along with this program; if not, write to the Free&n; *     Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139,&n; *     USA.&n; *&n; **********************************************************************&n; */
macro_line|#ifndef _CARDMO_H
DECL|macro|_CARDMO_H
mdefine_line|#define _CARDMO_H
macro_line|#include &quot;icardmid.h&quot;
macro_line|#include &lt;linux/interrupt.h&gt;
DECL|macro|CARDMIDIOUT_STATE_DEFAULT
mdefine_line|#define CARDMIDIOUT_STATE_DEFAULT    0x00000000
DECL|macro|CARDMIDIOUT_STATE_SUSPEND
mdefine_line|#define CARDMIDIOUT_STATE_SUSPEND    0x00000001
DECL|struct|emu10k1_mpuout
r_struct
id|emu10k1_mpuout
(brace
DECL|member|status
id|u32
id|status
suffix:semicolon
DECL|member|state
id|u32
id|state
suffix:semicolon
DECL|member|intr
r_volatile
r_int
id|intr
suffix:semicolon
DECL|member|firstmidiq
r_struct
id|midi_queue
op_star
id|firstmidiq
suffix:semicolon
DECL|member|lastmidiq
r_struct
id|midi_queue
op_star
id|lastmidiq
suffix:semicolon
DECL|member|laststatus
id|u8
id|laststatus
suffix:semicolon
DECL|member|tasklet
r_struct
id|tasklet_struct
id|tasklet
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|openinfo
r_struct
id|midi_openinfo
id|openinfo
suffix:semicolon
)brace
suffix:semicolon
r_int
id|emu10k1_mpuout_open
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
r_struct
id|midi_openinfo
op_star
)paren
suffix:semicolon
r_int
id|emu10k1_mpuout_close
c_func
(paren
r_struct
id|emu10k1_card
op_star
)paren
suffix:semicolon
r_int
id|emu10k1_mpuout_add_buffer
c_func
(paren
r_struct
id|emu10k1_card
op_star
comma
r_struct
id|midi_hdr
op_star
)paren
suffix:semicolon
r_int
id|emu10k1_mpuout_irqhandler
c_func
(paren
r_struct
id|emu10k1_card
op_star
)paren
suffix:semicolon
r_void
id|emu10k1_mpuout_bh
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif  /* _CARDMO_H */
eof
