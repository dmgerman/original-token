multiline_comment|/* &n;    bttv - Bt848 frame grabber driver&n;&n;    Copyright (C) 1996,97 Ralph Metzler (rjkm@thp.uni-koeln.de)&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef _BTTV_H_
DECL|macro|_BTTV_H_
mdefine_line|#define _BTTV_H_
DECL|macro|BTTV_VERSION_CODE
mdefine_line|#define BTTV_VERSION_CODE 0x000523
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &quot;msp3400.h&quot;
macro_line|#include &quot;bt848.h&quot;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#ifndef O_NONCAP  
DECL|macro|O_NONCAP
mdefine_line|#define O_NONCAP&t;O_TRUNC
macro_line|#endif
DECL|macro|MAX_GBUFFERS
mdefine_line|#define MAX_GBUFFERS&t;2
DECL|macro|RISCMEM_LEN
mdefine_line|#define RISCMEM_LEN&t;(32744*2)
DECL|macro|VBIBUF_SIZE
mdefine_line|#define VBIBUF_SIZE     65536
multiline_comment|/* maximum needed buffer size for extended VBI frame mode capturing */
DECL|macro|BTTV_MAX_FBUF
mdefine_line|#define BTTV_MAX_FBUF&t;0x190000
macro_line|#ifdef __KERNEL__
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
DECL|member|depth
id|ushort
id|depth
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|bttv_pll_info
r_struct
id|bttv_pll_info
(brace
DECL|member|pll_ifreq
r_int
r_int
id|pll_ifreq
suffix:semicolon
multiline_comment|/* PLL input frequency &t; */
DECL|member|pll_ofreq
r_int
r_int
id|pll_ofreq
suffix:semicolon
multiline_comment|/* PLL output frequency       */
DECL|member|pll_crystal
r_int
r_int
id|pll_crystal
suffix:semicolon
multiline_comment|/* Crystal used for input     */
DECL|member|pll_current
r_int
r_int
id|pll_current
suffix:semicolon
multiline_comment|/* Currently programmed ofreq */
)brace
suffix:semicolon
multiline_comment|/*  Per-open data for handling multiple opens on one device */
DECL|struct|device_open
r_struct
id|device_open
(brace
DECL|member|isopen
r_int
id|isopen
suffix:semicolon
DECL|member|noncapturing
r_int
id|noncapturing
suffix:semicolon
DECL|member|dev
r_struct
id|bttv
op_star
id|dev
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MAX_OPENS
mdefine_line|#define MAX_OPENS 3
DECL|struct|bttv
r_struct
id|bttv
(brace
DECL|member|video_dev
r_struct
id|video_device
id|video_dev
suffix:semicolon
DECL|member|radio_dev
r_struct
id|video_device
id|radio_dev
suffix:semicolon
DECL|member|vbi_dev
r_struct
id|video_device
id|vbi_dev
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
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|user
r_int
id|user
suffix:semicolon
DECL|member|capuser
r_int
id|capuser
suffix:semicolon
DECL|member|open_data
r_struct
id|device_open
id|open_data
(braket
id|MAX_OPENS
)braket
suffix:semicolon
DECL|member|i2c
r_struct
id|i2c_bus
id|i2c
suffix:semicolon
DECL|member|have_msp3400
r_int
id|have_msp3400
suffix:semicolon
DECL|member|have_tuner
r_int
id|have_tuner
suffix:semicolon
DECL|member|tuner_type
r_int
id|tuner_type
suffix:semicolon
DECL|member|channel
r_int
id|channel
suffix:semicolon
DECL|member|nr
r_int
r_int
id|nr
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &lt; 0x020100
DECL|member|bus
r_int
r_char
id|bus
suffix:semicolon
multiline_comment|/* PCI bus the Bt848 is on */
DECL|member|devfn
r_int
r_char
id|devfn
suffix:semicolon
macro_line|#else
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
macro_line|#endif
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
multiline_comment|/* IRQ used by Bt848 card */
DECL|member|revision
r_int
r_char
id|revision
suffix:semicolon
DECL|member|bt848_adr
r_int
r_int
id|bt848_adr
suffix:semicolon
multiline_comment|/* bus address of IO mem returned by PCI BIOS */
DECL|member|bt848_mem
r_int
r_char
op_star
id|bt848_mem
suffix:semicolon
multiline_comment|/* pointer to mapped IO memory */
DECL|member|busriscmem
r_int
r_int
id|busriscmem
suffix:semicolon
DECL|member|riscmem
id|u32
op_star
id|riscmem
suffix:semicolon
DECL|member|vbibuf
r_int
r_char
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
DECL|member|audio_chip
r_int
id|audio_chip
suffix:semicolon
DECL|member|fader_chip
r_int
id|fader_chip
suffix:semicolon
DECL|member|radio
r_int
id|radio
suffix:semicolon
DECL|member|risc_jmp
id|u32
op_star
id|risc_jmp
suffix:semicolon
DECL|member|vbi_odd
id|u32
op_star
id|vbi_odd
suffix:semicolon
DECL|member|vbi_even
id|u32
op_star
id|vbi_even
suffix:semicolon
DECL|member|bus_vbi_even
id|u32
id|bus_vbi_even
suffix:semicolon
DECL|member|bus_vbi_odd
id|u32
id|bus_vbi_odd
suffix:semicolon
DECL|member|vbiq
id|wait_queue_head_t
id|vbiq
suffix:semicolon
DECL|member|capq
id|wait_queue_head_t
id|capq
suffix:semicolon
DECL|member|capqo
id|wait_queue_head_t
id|capqo
suffix:semicolon
DECL|member|capqe
id|wait_queue_head_t
id|capqe
suffix:semicolon
DECL|member|vbip
r_int
id|vbip
suffix:semicolon
DECL|member|risc_odd
id|u32
op_star
id|risc_odd
suffix:semicolon
DECL|member|risc_even
id|u32
op_star
id|risc_even
suffix:semicolon
DECL|member|cap
r_int
id|cap
suffix:semicolon
DECL|member|cliprecs
r_struct
id|video_clip
op_star
id|cliprecs
suffix:semicolon
DECL|member|ogbuffers
r_struct
id|gbuffer
op_star
id|ogbuffers
suffix:semicolon
DECL|member|egbuffers
r_struct
id|gbuffer
op_star
id|egbuffers
suffix:semicolon
DECL|member|gwidth
DECL|member|gheight
DECL|member|gfmt
id|u16
id|gwidth
comma
id|gheight
comma
id|gfmt
suffix:semicolon
DECL|member|gwidth_next
DECL|member|gheight_next
DECL|member|gfmt_next
id|u16
id|gwidth_next
comma
id|gheight_next
comma
id|gfmt_next
suffix:semicolon
DECL|member|grisc
id|u32
op_star
id|grisc
suffix:semicolon
DECL|member|gro
r_int
r_int
id|gro
suffix:semicolon
DECL|member|gre
r_int
r_int
id|gre
suffix:semicolon
DECL|member|gro_next
r_int
r_int
id|gro_next
suffix:semicolon
DECL|member|gre_next
r_int
r_int
id|gre_next
suffix:semicolon
DECL|member|grf
DECL|member|grf_next
r_int
id|grf
comma
id|grf_next
suffix:semicolon
multiline_comment|/* frame numbers in grab queue */
DECL|member|frame_stat
r_int
id|frame_stat
(braket
id|MAX_GBUFFERS
)braket
suffix:semicolon
DECL|macro|GBUFFER_UNUSED
mdefine_line|#define GBUFFER_UNUSED       0
DECL|macro|GBUFFER_GRABBING
mdefine_line|#define GBUFFER_GRABBING     1
DECL|macro|GBUFFER_DONE
mdefine_line|#define GBUFFER_DONE         2
DECL|member|fbuffer
r_char
op_star
id|fbuffer
suffix:semicolon
DECL|member|gmode
r_int
id|gmode
suffix:semicolon
DECL|member|grabbing
r_int
id|grabbing
suffix:semicolon
DECL|member|lastgrab
r_int
id|lastgrab
suffix:semicolon
DECL|member|grab
r_int
id|grab
suffix:semicolon
DECL|member|grabcount
r_int
id|grabcount
suffix:semicolon
DECL|member|pll
r_struct
id|bttv_pll_info
id|pll
suffix:semicolon
DECL|member|Fsc
r_int
r_int
id|Fsc
suffix:semicolon
DECL|member|field
r_int
r_int
id|field
suffix:semicolon
DECL|member|last_field
r_int
r_int
id|last_field
suffix:semicolon
multiline_comment|/* number of last grabbed field */
DECL|member|i2c_command
r_int
id|i2c_command
suffix:semicolon
DECL|member|triton1
r_int
id|triton1
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
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
DECL|macro|BTTV_READEE
mdefine_line|#define BTTV_READEE&t;&t;_IOW(&squot;v&squot;,  BASE_VIDIOCPRIVATE+0, char [256])
DECL|macro|BTTV_WRITEE
mdefine_line|#define BTTV_WRITEE&t;&t;_IOR(&squot;v&squot;,  BASE_VIDIOCPRIVATE+1, char [256])
DECL|macro|BTTV_FIELDNR
mdefine_line|#define BTTV_FIELDNR&t;&t;_IOR(&squot;v&squot; , BASE_VIDIOCPRIVATE+2, unsigned int)
DECL|macro|BTTV_PLLSET
mdefine_line|#define BTTV_PLLSET&t;&t;_IOW(&squot;v&squot; , BASE_VIDIOCPRIVATE+3, struct bttv_pll_info)
DECL|macro|BTTV_BURST_ON
mdefine_line|#define BTTV_BURST_ON      &t;_IOR(&squot;v&squot; , BASE_VIDIOCPRIVATE+4, int)
DECL|macro|BTTV_BURST_OFF
mdefine_line|#define BTTV_BURST_OFF     &t;_IOR(&squot;v&squot; , BASE_VIDIOCPRIVATE+5, int)
DECL|macro|BTTV_VERSION
mdefine_line|#define BTTV_VERSION  &t;        _IOR(&squot;v&squot; , BASE_VIDIOCPRIVATE+6, int)
DECL|macro|BTTV_PICNR
mdefine_line|#define BTTV_PICNR&t;&t;_IOR(&squot;v&squot; , BASE_VIDIOCPRIVATE+7, int)
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
DECL|macro|BTTV_AVERMEDIA
mdefine_line|#define BTTV_AVERMEDIA     0x06 
DECL|macro|BTTV_MATRIX_VISION
mdefine_line|#define BTTV_MATRIX_VISION 0x07 
DECL|macro|BTTV_FLYVIDEO
mdefine_line|#define BTTV_FLYVIDEO      0x08
DECL|macro|BTTV_TURBOTV
mdefine_line|#define BTTV_TURBOTV       0x09
DECL|macro|BTTV_HAUPPAUGE878
mdefine_line|#define BTTV_HAUPPAUGE878  0x0a
DECL|macro|BTTV_MIROPRO
mdefine_line|#define BTTV_MIROPRO       0x0b
DECL|macro|BTTV_ADSTECH_TV
mdefine_line|#define BTTV_ADSTECH_TV    0x0c
DECL|macro|BTTV_AVERMEDIA98
mdefine_line|#define BTTV_AVERMEDIA98   0x0d
DECL|macro|BTTV_VHX
mdefine_line|#define BTTV_VHX           0x0e
DECL|macro|BTTV_ZOLTRIX
mdefine_line|#define BTTV_ZOLTRIX       0x0f
DECL|macro|BTTV_PIXVIEWPLAYTV
mdefine_line|#define BTTV_PIXVIEWPLAYTV 0x10
DECL|macro|BTTV_WINVIEW_601
mdefine_line|#define BTTV_WINVIEW_601   0x11
DECL|macro|BTTV_AVEC_INTERCAP
mdefine_line|#define BTTV_AVEC_INTERCAP 0x12
DECL|macro|BTTV_LIFE_FLYKIT
mdefine_line|#define BTTV_LIFE_FLYKIT   0x13
DECL|macro|BTTV_CEI_RAFFLES
mdefine_line|#define BTTV_CEI_RAFFLES   0x14
DECL|macro|BTTV_CONFERENCETV
mdefine_line|#define BTTV_CONFERENCETV  0x15
DECL|macro|BTTV_PHOEBE_TVMAS
mdefine_line|#define BTTV_PHOEBE_TVMAS  0x16
DECL|macro|BTTV_MODTEC_205
mdefine_line|#define BTTV_MODTEC_205    0x17
DECL|macro|BTTV_MAGICTVIEW061
mdefine_line|#define BTTV_MAGICTVIEW061 0x18
DECL|macro|AUDIO_TUNER
mdefine_line|#define AUDIO_TUNER        0x00
DECL|macro|AUDIO_RADIO
mdefine_line|#define AUDIO_RADIO        0x01
DECL|macro|AUDIO_EXTERN
mdefine_line|#define AUDIO_EXTERN       0x02
DECL|macro|AUDIO_INTERN
mdefine_line|#define AUDIO_INTERN       0x03
DECL|macro|AUDIO_OFF
mdefine_line|#define AUDIO_OFF          0x04 
DECL|macro|AUDIO_ON
mdefine_line|#define AUDIO_ON           0x05
DECL|macro|AUDIO_MUTE
mdefine_line|#define AUDIO_MUTE         0x80
DECL|macro|AUDIO_UNMUTE
mdefine_line|#define AUDIO_UNMUTE       0x81
DECL|macro|TDA9850
mdefine_line|#define TDA9850            0x01
DECL|macro|TDA8425
mdefine_line|#define TDA8425            0x02
DECL|macro|TDA9840
mdefine_line|#define TDA9840            0x03
DECL|macro|TEA6300
mdefine_line|#define TEA6300            0x04
DECL|macro|TEA6320
mdefine_line|#define TEA6320            0x05
DECL|macro|I2C_TSA5522
mdefine_line|#define I2C_TSA5522        0xc2
DECL|macro|I2C_TDA9840
mdefine_line|#define I2C_TDA9840&t;   0x84
DECL|macro|I2C_TDA9850
mdefine_line|#define I2C_TDA9850        0xb6
DECL|macro|I2C_TDA8425
mdefine_line|#define I2C_TDA8425        0x82
DECL|macro|I2C_HAUPEE
mdefine_line|#define I2C_HAUPEE         0xa0
DECL|macro|I2C_STBEE
mdefine_line|#define I2C_STBEE          0xae
DECL|macro|I2C_VHX
mdefine_line|#define I2C_VHX &t;   0xc0
DECL|macro|I2C_TEA6300
mdefine_line|#define I2C_TEA6300        0x80 /* same as TEA6320 */
DECL|macro|I2C_TEA6320
mdefine_line|#define I2C_TEA6320        0x80
DECL|macro|TDA9840_SW
mdefine_line|#define TDA9840_SW&t;   0x00
DECL|macro|TDA9840_LVADJ
mdefine_line|#define TDA9840_LVADJ&t;   0x02
DECL|macro|TDA9840_STADJ
mdefine_line|#define TDA9840_STADJ&t;   0x03
DECL|macro|TDA9840_TEST
mdefine_line|#define TDA9840_TEST&t;   0x04
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
DECL|macro|TDA8425_VL
mdefine_line|#define TDA8425_VL         0x00
DECL|macro|TDA8425_VR
mdefine_line|#define TDA8425_VR         0x01
DECL|macro|TDA8425_BA
mdefine_line|#define TDA8425_BA         0x02
DECL|macro|TDA8425_TR
mdefine_line|#define TDA8425_TR         0x03
DECL|macro|TDA8425_S1
mdefine_line|#define TDA8425_S1         0x08
DECL|macro|TEA6300_VL
mdefine_line|#define TEA6300_VL         0x00&t;&t;/* volume control left */
DECL|macro|TEA6300_VR
mdefine_line|#define TEA6300_VR         0x01&t;&t;/* volume control right */
DECL|macro|TEA6300_BA
mdefine_line|#define TEA6300_BA         0x02&t;&t;/* bass control */
DECL|macro|TEA6300_TR
mdefine_line|#define TEA6300_TR         0x03&t;&t;/* treble control */
DECL|macro|TEA6300_FA
mdefine_line|#define TEA6300_FA         0x04&t;&t;/* fader control */
DECL|macro|TEA6300_SW
mdefine_line|#define TEA6300_SW         0x05&t;&t;/* mute and source switch */
DECL|macro|TEA6320_V
mdefine_line|#define TEA6320_V          0x00
DECL|macro|TEA6320_FFR
mdefine_line|#define TEA6320_FFR        0x01  /* volume front right */
DECL|macro|TEA6320_FFL
mdefine_line|#define TEA6320_FFL        0x02  /* volume front left */
DECL|macro|TEA6320_FRR
mdefine_line|#define TEA6320_FRR        0x03  /* volume rear right */
DECL|macro|TEA6320_FRL
mdefine_line|#define TEA6320_FRL        0x04  /* volume rear left */
DECL|macro|TEA6320_BA
mdefine_line|#define TEA6320_BA         0x05  /* bass */
DECL|macro|TEA6320_TR
mdefine_line|#define TEA6320_TR         0x06  /* treble */
DECL|macro|TEA6320_S
mdefine_line|#define TEA6320_S          0x07  /* switch register */
multiline_comment|/* values for those registers: */
DECL|macro|TEA6320_S_SA
mdefine_line|#define TEA6320_S_SA       0x01  /* stereo A input */
DECL|macro|TEA6320_S_SB
mdefine_line|#define TEA6320_S_SB       0x07  /* stereo B -- databook wrong? this works */
DECL|macro|TEA6320_S_SC
mdefine_line|#define TEA6320_S_SC       0x04  /* stereo C */
DECL|macro|TEA6320_S_GMU
mdefine_line|#define TEA6320_S_GMU      0x80  /* general mute */
DECL|macro|PT2254_L_CHANEL
mdefine_line|#define PT2254_L_CHANEL 0x10
DECL|macro|PT2254_R_CHANEL
mdefine_line|#define PT2254_R_CHANEL 0x08
DECL|macro|PT2254_DBS_IN_2
mdefine_line|#define PT2254_DBS_IN_2 0x400
DECL|macro|PT2254_DBS_IN_10
mdefine_line|#define PT2254_DBS_IN_10 0x20000
DECL|macro|WINVIEW_PT2254_CLK
mdefine_line|#define WINVIEW_PT2254_CLK  0x40
DECL|macro|WINVIEW_PT2254_DATA
mdefine_line|#define WINVIEW_PT2254_DATA 0x20
DECL|macro|WINVIEW_PT2254_STROBE
mdefine_line|#define WINVIEW_PT2254_STROBE 0x80
macro_line|#endif
eof
