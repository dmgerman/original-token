multiline_comment|/* &n;    bttv - Bt848 frame grabber driver&n;&n;    Copyright (C) 1996,97 Ralph Metzler (rjkm@thp.uni-koeln.de)&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;*/
macro_line|#ifndef _BTTV_H_
DECL|macro|_BTTV_H_
mdefine_line|#define _BTTV_H_
DECL|macro|BTTV_VERSION_CODE
mdefine_line|#define BTTV_VERSION_CODE KERNEL_VERSION(0,7,21) 
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
macro_line|#include &quot;audiochip.h&quot;
macro_line|#include &quot;bt848.h&quot;
DECL|macro|WAIT_QUEUE
mdefine_line|#define WAIT_QUEUE                 wait_queue_head_t
multiline_comment|/* returns card type, &n;   for possible values see lines below beginning with #define BTTV_UNKNOWN&n;   returns negative value if error ocurred &n;*/
r_extern
r_int
id|bttv_get_id
c_func
(paren
r_int
r_int
id|card
)paren
suffix:semicolon
multiline_comment|/* sets GPOE register (BT848_GPIO_OUT_EN) to new value:&n;   data | (current_GPOE_value &amp; ~mask)&n;   returns negative value if error ocurred&n;*/
r_extern
r_int
id|bttv_gpio_enable
c_func
(paren
r_int
r_int
id|card
comma
r_int
r_int
id|mask
comma
r_int
r_int
id|data
)paren
suffix:semicolon
multiline_comment|/* fills data with GPDATA register contents&n;   returns negative value if error ocurred&n;*/
r_extern
r_int
id|bttv_read_gpio
c_func
(paren
r_int
r_int
id|card
comma
r_int
r_int
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/* sets GPDATA register to new value:&n;  (data &amp; mask) | (current_GPDATA_value &amp; ~mask)&n;  returns negative value if error ocurred &n;*/
r_extern
r_int
id|bttv_write_gpio
c_func
(paren
r_int
r_int
id|card
comma
r_int
r_int
id|mask
comma
r_int
r_int
id|data
)paren
suffix:semicolon
multiline_comment|/* returns pointer to task queue which can be used as parameter to &n;   interruptible_sleep_on&n;   in interrupt handler if BT848_INT_GPINT bit is set - this queue is activated&n;   (wake_up_interruptible) and following call to the function bttv_read_gpio &n;   should return new value of GPDATA,&n;   returns NULL value if error ocurred or queue is not available&n;   WARNING: because there is no buffer for GPIO data, one MUST &n;   process data ASAP&n;*/
r_extern
id|WAIT_QUEUE
op_star
id|bttv_get_gpio_queue
c_func
(paren
r_int
r_int
id|card
)paren
suffix:semicolon
macro_line|#ifndef O_NONCAP  
DECL|macro|O_NONCAP
mdefine_line|#define O_NONCAP&t;O_TRUNC
macro_line|#endif
DECL|macro|MAX_GBUFFERS
mdefine_line|#define MAX_GBUFFERS&t;64
DECL|macro|RISCMEM_LEN
mdefine_line|#define RISCMEM_LEN&t;(32744*2)
DECL|macro|VBI_MAXLINES
mdefine_line|#define VBI_MAXLINES    16
DECL|macro|VBIBUF_SIZE
mdefine_line|#define VBIBUF_SIZE     (2048*VBI_MAXLINES*2)
DECL|macro|BTTV_MAX_FBUF
mdefine_line|#define BTTV_MAX_FBUF&t;0x208000
DECL|macro|I2C_CLIENTS_MAX
mdefine_line|#define I2C_CLIENTS_MAX 8
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
DECL|struct|bttv_gbuf
r_struct
id|bttv_gbuf
(brace
DECL|member|stat
r_int
id|stat
suffix:semicolon
DECL|macro|GBUFFER_UNUSED
mdefine_line|#define GBUFFER_UNUSED       0
DECL|macro|GBUFFER_GRABBING
mdefine_line|#define GBUFFER_GRABBING     1
DECL|macro|GBUFFER_DONE
mdefine_line|#define GBUFFER_DONE         2
DECL|macro|GBUFFER_ERROR
mdefine_line|#define GBUFFER_ERROR        3
DECL|member|width
id|u16
id|width
suffix:semicolon
DECL|member|height
id|u16
id|height
suffix:semicolon
DECL|member|fmt
id|u16
id|fmt
suffix:semicolon
DECL|member|risc
id|u32
op_star
id|risc
suffix:semicolon
DECL|member|ro
r_int
r_int
id|ro
suffix:semicolon
DECL|member|re
r_int
r_int
id|re
suffix:semicolon
)brace
suffix:semicolon
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
multiline_comment|/* i2c */
DECL|member|i2c_adap
r_struct
id|i2c_adapter
id|i2c_adap
suffix:semicolon
DECL|member|i2c_algo
r_struct
id|i2c_algo_bit_data
id|i2c_algo
suffix:semicolon
DECL|member|i2c_client
r_struct
id|i2c_client
id|i2c_client
suffix:semicolon
DECL|member|i2c_state
r_int
id|i2c_state
suffix:semicolon
DECL|member|i2c_clients
r_struct
id|i2c_client
op_star
id|i2c_clients
(braket
id|I2C_CLIENTS_MAX
)braket
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
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
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
DECL|member|fb_color_ctl
r_int
id|fb_color_ctl
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
multiline_comment|/* set to one of the chips supported by bttv.c */
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
id|WAIT_QUEUE
id|vbiq
suffix:semicolon
DECL|member|capq
id|WAIT_QUEUE
id|capq
suffix:semicolon
DECL|member|capqo
id|WAIT_QUEUE
id|capqo
suffix:semicolon
DECL|member|capqe
id|WAIT_QUEUE
id|capqe
suffix:semicolon
DECL|member|vbip
r_int
id|vbip
suffix:semicolon
DECL|member|risc_scr_odd
id|u32
op_star
id|risc_scr_odd
suffix:semicolon
DECL|member|risc_scr_even
id|u32
op_star
id|risc_scr_even
suffix:semicolon
DECL|member|risc_cap_odd
id|u32
id|risc_cap_odd
suffix:semicolon
DECL|member|risc_cap_even
id|u32
id|risc_cap_even
suffix:semicolon
DECL|member|scr_on
r_int
id|scr_on
suffix:semicolon
DECL|member|vbi_on
r_int
id|vbi_on
suffix:semicolon
DECL|member|cliprecs
r_struct
id|video_clip
op_star
id|cliprecs
suffix:semicolon
DECL|member|gbuf
r_struct
id|bttv_gbuf
op_star
id|gbuf
suffix:semicolon
DECL|member|gqueue
r_int
id|gqueue
(braket
id|MAX_GBUFFERS
)braket
suffix:semicolon
DECL|member|gq_in
DECL|member|gq_out
DECL|member|gq_grab
r_int
id|gq_in
comma
id|gq_out
comma
id|gq_grab
suffix:semicolon
DECL|member|fbuffer
r_char
op_star
id|fbuffer
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
DECL|member|gpioq
id|WAIT_QUEUE
id|gpioq
suffix:semicolon
DECL|member|shutdown
r_int
id|shutdown
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#if defined(__powerpc__) /* big-endian */
DECL|function|io_st_le32
r_extern
id|__inline__
r_void
id|io_st_le32
c_func
(paren
r_volatile
r_int
op_star
id|addr
comma
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;stwbrx %1,0,%2&quot;
suffix:colon
"&bslash;"
l_string|&quot;=m&quot;
(paren
op_star
id|addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;eieio&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
DECL|macro|btwrite
mdefine_line|#define btwrite(dat,adr)  io_st_le32((unsigned *)(btv-&gt;bt848_mem+(adr)),(dat))
DECL|macro|btread
mdefine_line|#define btread(adr)       ld_le32((unsigned *)(btv-&gt;bt848_mem+(adr)))
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
DECL|macro|BTTV_VBISIZE
mdefine_line|#define BTTV_VBISIZE            _IOR(&squot;v&squot; , BASE_VIDIOCPRIVATE+8, int)
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
DECL|macro|BTTV_VOBIS_BOOSTAR
mdefine_line|#define BTTV_VOBIS_BOOSTAR 0x19
DECL|macro|BTTV_HAUPPAUG_WCAM
mdefine_line|#define BTTV_HAUPPAUG_WCAM 0x1a
DECL|macro|BTTV_MAXI
mdefine_line|#define BTTV_MAXI          0x1b
DECL|macro|BTTV_TERRATV
mdefine_line|#define BTTV_TERRATV       0x1c
DECL|macro|BTTV_PXC200
mdefine_line|#define BTTV_PXC200        0x1d
DECL|macro|BTTV_FLYVIDEO_98
mdefine_line|#define BTTV_FLYVIDEO_98   0x1e
DECL|macro|BTTV_IPROTV
mdefine_line|#define BTTV_IPROTV        0x1f
DECL|macro|BTTV_INTEL_C_S_PCI
mdefine_line|#define BTTV_INTEL_C_S_PCI 0x20
DECL|macro|BTTV_TERRATVALUE
mdefine_line|#define BTTV_TERRATVALUE   0x21
DECL|macro|BTTV_WINFAST2000
mdefine_line|#define BTTV_WINFAST2000   0x22
DECL|macro|BTTV_CHRONOS_VS2
mdefine_line|#define BTTV_CHRONOS_VS2   0x23
DECL|macro|BTTV_TYPHOON_TVIEW
mdefine_line|#define BTTV_TYPHOON_TVIEW 0x24
DECL|macro|BTTV_PXELVWPLTVPRO
mdefine_line|#define BTTV_PXELVWPLTVPRO 0x25
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
DECL|macro|TDA9840
mdefine_line|#define TDA9840            0x02
DECL|macro|TDA8425
mdefine_line|#define TDA8425            0x03
DECL|macro|TEA6300
mdefine_line|#define TEA6300            0x04
DECL|macro|I2C_TSA5522
mdefine_line|#define I2C_TSA5522        0xc2
DECL|macro|I2C_TDA9840
mdefine_line|#define I2C_TDA9840        0x84
DECL|macro|I2C_TDA9850
mdefine_line|#define I2C_TDA9850        0xb6
DECL|macro|I2C_TDA8425
mdefine_line|#define I2C_TDA8425        0x82
DECL|macro|I2C_HAUPEE
mdefine_line|#define I2C_HAUPEE         0xa0
DECL|macro|I2C_STBEE
mdefine_line|#define I2C_STBEE          0xae
DECL|macro|I2C_VHX
mdefine_line|#define I2C_VHX            0xc0
DECL|macro|I2C_MSP3400
mdefine_line|#define I2C_MSP3400        0x80
DECL|macro|I2C_TEA6300
mdefine_line|#define I2C_TEA6300        0x80
DECL|macro|I2C_DPL3518
mdefine_line|#define I2C_DPL3518&t;   0x84
DECL|macro|TDA9840_SW
mdefine_line|#define TDA9840_SW         0x00
DECL|macro|TDA9840_LVADJ
mdefine_line|#define TDA9840_LVADJ      0x02
DECL|macro|TDA9840_STADJ
mdefine_line|#define TDA9840_STADJ      0x03
DECL|macro|TDA9840_TEST
mdefine_line|#define TDA9840_TEST       0x04
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
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
