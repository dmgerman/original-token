multiline_comment|/* &n;    bttv - Bt848 frame grabber driver&n;&n;    Copyright (C) 1996,97 Ralph Metzler (rjkm@thp.uni-koeln.de)&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef _BTTV_H_
DECL|macro|_BTTV_H_
mdefine_line|#define _BTTV_H_
DECL|macro|TEST_VBI
mdefine_line|#define TEST_VBI
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &quot;bt848.h&quot;
DECL|typedef|dword
r_typedef
r_int
r_int
id|dword
suffix:semicolon
DECL|struct|riscprog
r_struct
id|riscprog
(brace
DECL|member|length
id|uint
id|length
suffix:semicolon
DECL|member|busadr
id|dword
op_star
id|busadr
suffix:semicolon
DECL|member|prog
id|dword
op_star
id|prog
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* values that can be set by user programs */
DECL|struct|bttv_window
r_struct
id|bttv_window
(brace
DECL|member|x
DECL|member|y
r_int
id|x
comma
id|y
suffix:semicolon
DECL|member|width
DECL|member|height
id|ushort
id|width
comma
id|height
suffix:semicolon
DECL|member|bpp
DECL|member|bpl
id|ushort
id|bpp
comma
id|bpl
suffix:semicolon
DECL|member|swidth
DECL|member|sheight
id|ushort
id|swidth
comma
id|sheight
suffix:semicolon
DECL|member|cropx
DECL|member|cropy
r_int
id|cropx
comma
id|cropy
suffix:semicolon
DECL|member|cropwidth
DECL|member|cropheight
id|ushort
id|cropwidth
comma
id|cropheight
suffix:semicolon
DECL|member|vidadr
r_int
id|vidadr
suffix:semicolon
DECL|member|freq
id|ushort
id|freq
suffix:semicolon
DECL|member|norm
r_int
id|norm
suffix:semicolon
DECL|member|interlace
r_int
id|interlace
suffix:semicolon
DECL|member|color_fmt
r_int
id|color_fmt
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* private data that can only be read (or set indirectly) by user program */
DECL|struct|bttv
r_struct
id|bttv
(brace
DECL|member|video_dev
r_struct
id|video_device
id|video_dev
suffix:semicolon
DECL|member|picture
r_struct
id|video_picture
id|picture
suffix:semicolon
multiline_comment|/* Current picture params */
DECL|member|audio_dev
r_struct
id|video_audio
id|audio_dev
suffix:semicolon
multiline_comment|/* Current audio params */
DECL|member|bus
id|u_char
id|bus
suffix:semicolon
multiline_comment|/* PCI bus the Bt848 is on */
DECL|member|devfn
id|u_char
id|devfn
suffix:semicolon
DECL|member|revision
id|u_char
id|revision
suffix:semicolon
DECL|member|irq
id|u_char
id|irq
suffix:semicolon
multiline_comment|/* IRQ used by Bt848 card */
DECL|member|bt848_adr
id|uint
id|bt848_adr
suffix:semicolon
multiline_comment|/* bus address of IO mem returned by PCI BIOS */
DECL|member|bt848_mem
id|u_char
op_star
id|bt848_mem
suffix:semicolon
multiline_comment|/* pointer to mapped IO memory */
DECL|member|busriscmem
id|ulong
id|busriscmem
suffix:semicolon
DECL|member|riscmem
id|dword
op_star
id|riscmem
suffix:semicolon
DECL|member|vbibuf
id|u_char
op_star
id|vbibuf
suffix:semicolon
DECL|member|win
r_struct
id|bttv_window
id|win
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* card type  */
DECL|member|audio
r_int
id|audio
suffix:semicolon
multiline_comment|/* audio mode */
DECL|member|user
r_int
id|user
suffix:semicolon
DECL|member|tuner
r_int
id|tuner
suffix:semicolon
DECL|member|tuneradr
r_int
id|tuneradr
suffix:semicolon
DECL|member|dbx
r_int
id|dbx
suffix:semicolon
DECL|member|risc_jmp
id|dword
op_star
id|risc_jmp
suffix:semicolon
DECL|member|vbi_odd
id|dword
op_star
id|vbi_odd
suffix:semicolon
DECL|member|vbi_even
id|dword
op_star
id|vbi_even
suffix:semicolon
DECL|member|bus_vbi_even
id|dword
id|bus_vbi_even
suffix:semicolon
DECL|member|bus_vbi_odd
id|dword
id|bus_vbi_odd
suffix:semicolon
DECL|member|vbiq
r_struct
id|wait_queue
op_star
id|vbiq
suffix:semicolon
DECL|member|capq
r_struct
id|wait_queue
op_star
id|capq
suffix:semicolon
DECL|member|vbip
r_int
id|vbip
suffix:semicolon
DECL|member|risc_odd
id|dword
op_star
id|risc_odd
suffix:semicolon
DECL|member|risc_even
id|dword
op_star
id|risc_even
suffix:semicolon
DECL|member|cap
r_int
id|cap
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*The following should be done in more portable way. It depends on define&n;  of _ALPHA_BTTV in the Makefile.*/
macro_line|#ifdef _ALPHA_BTTV
DECL|macro|btwrite
mdefine_line|#define btwrite(dat,adr)    writel((dat),(char *) (btv-&gt;bt848_adr+(adr)))
DECL|macro|btread
mdefine_line|#define btread(adr)         readl(btv-&gt;bt848_adr+(adr))
macro_line|#else
DECL|macro|btwrite
mdefine_line|#define btwrite(dat,adr)    writel((dat), (char *) (btv-&gt;bt848_mem+(adr)))
DECL|macro|btread
mdefine_line|#define btread(adr)         readl(btv-&gt;bt848_mem+(adr))
macro_line|#endif
DECL|macro|btand
mdefine_line|#define btand(dat,adr)      btwrite((dat) &amp; btread(adr), adr)
DECL|macro|btor
mdefine_line|#define btor(dat,adr)       btwrite((dat) | btread(adr), adr)
DECL|macro|btaor
mdefine_line|#define btaor(dat,mask,adr) btwrite((dat) | ((mask) &amp; btread(adr)), adr)
multiline_comment|/* bttv ioctls */
DECL|macro|BTTV_WRITE_BTREG
mdefine_line|#define BTTV_WRITE_BTREG   0x00
DECL|macro|BTTV_READ_BTREG
mdefine_line|#define BTTV_READ_BTREG    0x01
DECL|macro|BTTV_SET_BTREG
mdefine_line|#define BTTV_SET_BTREG     0x02
DECL|macro|BTTV_SETRISC
mdefine_line|#define BTTV_SETRISC       0x03
DECL|macro|BTTV_SETWTW
mdefine_line|#define BTTV_SETWTW        0x04
DECL|macro|BTTV_GETWTW
mdefine_line|#define BTTV_GETWTW        0x05
DECL|macro|BTTV_DMA
mdefine_line|#define BTTV_DMA           0x06
DECL|macro|BTTV_CAP_OFF
mdefine_line|#define BTTV_CAP_OFF       0x07
DECL|macro|BTTV_CAP_ON
mdefine_line|#define BTTV_CAP_ON        0x08
DECL|macro|BTTV_GETBTTV
mdefine_line|#define BTTV_GETBTTV       0x09
DECL|macro|BTTV_SETFREQ
mdefine_line|#define BTTV_SETFREQ       0x0a
DECL|macro|BTTV_SETCHAN
mdefine_line|#define BTTV_SETCHAN       0x0b
DECL|macro|BTTV_INPUT
mdefine_line|#define BTTV_INPUT         0x0c
DECL|macro|BTTV_READEE
mdefine_line|#define BTTV_READEE        0x0d
DECL|macro|BTTV_WRITEEE
mdefine_line|#define BTTV_WRITEEE       0x0e
DECL|macro|BTTV_BRIGHT
mdefine_line|#define BTTV_BRIGHT        0x0f
DECL|macro|BTTV_HUE
mdefine_line|#define BTTV_HUE           0x10
DECL|macro|BTTV_COLOR
mdefine_line|#define BTTV_COLOR         0x11
DECL|macro|BTTV_CONTRAST
mdefine_line|#define BTTV_CONTRAST      0x12
DECL|macro|BTTV_SET_FFREQ
mdefine_line|#define BTTV_SET_FFREQ     0x13
DECL|macro|BTTV_MUTE
mdefine_line|#define BTTV_MUTE          0x14
DECL|macro|BTTV_GRAB
mdefine_line|#define BTTV_GRAB          0x20
DECL|macro|BTTV_TESTM
mdefine_line|#define BTTV_TESTM         0x20
DECL|macro|BTTV_UNKNOWN
mdefine_line|#define BTTV_UNKNOWN       0x00
DECL|macro|BTTV_MIRO
mdefine_line|#define BTTV_MIRO          0x01
DECL|macro|BTTV_HAUPPAUGE
mdefine_line|#define BTTV_HAUPPAUGE     0x02
DECL|macro|BTTV_STB
mdefine_line|#define BTTV_STB           0x03
DECL|macro|BTTV_INTEL
mdefine_line|#define BTTV_INTEL         0x04
DECL|macro|BTTV_DIAMOND
mdefine_line|#define BTTV_DIAMOND       0x05 
DECL|macro|AUDIO_TUNER
mdefine_line|#define AUDIO_TUNER        0x00
DECL|macro|AUDIO_EXTERN
mdefine_line|#define AUDIO_EXTERN       0x01
DECL|macro|AUDIO_INTERN
mdefine_line|#define AUDIO_INTERN       0x02
DECL|macro|AUDIO_OFF
mdefine_line|#define AUDIO_OFF          0x03 
DECL|macro|AUDIO_ON
mdefine_line|#define AUDIO_ON           0x04
DECL|macro|AUDIO_MUTE
mdefine_line|#define AUDIO_MUTE         0x80
DECL|macro|AUDIO_UNMUTE
mdefine_line|#define AUDIO_UNMUTE       0x81
DECL|macro|I2C_TSA5522
mdefine_line|#define I2C_TSA5522        0xc2
DECL|macro|I2C_TDA9850
mdefine_line|#define I2C_TDA9850        0xb6
DECL|macro|I2C_HAUPEE
mdefine_line|#define I2C_HAUPEE         0xa0
DECL|macro|I2C_STBEE
mdefine_line|#define I2C_STBEE          0xae
DECL|macro|TDA9850_CON1
mdefine_line|#define TDA9850_CON1       0x04
DECL|macro|TDA9850_CON2
mdefine_line|#define TDA9850_CON2       0x05
DECL|macro|TDA9850_CON3
mdefine_line|#define TDA9850_CON3       0x06
DECL|macro|TDA9850_CON4
mdefine_line|#define TDA9850_CON4       0x07
DECL|macro|TDA9850_ALI1
mdefine_line|#define TDA9850_ALI1       0x08
DECL|macro|TDA9850_ALI2
mdefine_line|#define TDA9850_ALI2       0x09
DECL|macro|TDA9850_ALI3
mdefine_line|#define TDA9850_ALI3       0x0a
macro_line|#endif
eof
