multiline_comment|/* -- ISP16 cdrom detection and configuration&n; *&n; *    Copyright (c) 1995,1996 Eric van der Maarel &lt;H.T.M.v.d.Maarel@marin.nl&gt;&n; *&n; *    Version 0.6&n; *&n; *    History:&n; *    0.5 First release.&n; *        Was included in the sjcd and optcd cdrom drivers.&n; *    0.6 First &quot;stand-alone&quot; version.&n; *        Removed sound configuration.&n; *        Added &quot;module&quot; support.&n; *&n; *      9 November 1999 -- Make kernel-parameter implementation work with 2.3.x &n; *&t;                   Removed init_module &amp; cleanup_module in favor of &n; *&t;&t;&t;   module_init &amp; module_exit.&n; *&t;&t;&t;   Torben Mathiasen &lt;tmm@image.dk&gt;&n; *&n; *    Detect cdrom interface on ISP16 sound card.&n; *    Configure cdrom interface.&n; *&n; *    Algorithm for the card with OPTi 82C928 taken&n; *    from the CDSETUP.SYS driver for MSDOS,&n; *    by OPTi Computers, version 2.03.&n; *    Algorithm for the card with OPTi 82C929 as communicated&n; *    to me by Vadim Model and Leo Spiekman.&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2 of the License, or&n; *    (at your option) any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
DECL|macro|ISP16_VERSION_MAJOR
mdefine_line|#define ISP16_VERSION_MAJOR 0
DECL|macro|ISP16_VERSION_MINOR
mdefine_line|#define ISP16_VERSION_MINOR 6
macro_line|#ifdef MODULE
macro_line|#include &lt;linux/module.h&gt;
macro_line|#endif  /* MODULE */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;isp16.h&quot;
r_static
r_int
id|isp16_detect
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|isp16_c928__detect
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|isp16_c929__detect
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|isp16_cdi_config
c_func
(paren
r_int
id|base
comma
id|u_char
id|drive_type
comma
r_int
id|irq
comma
r_int
id|dma
)paren
suffix:semicolon
DECL|variable|isp16_type
r_static
r_int
id|isp16_type
suffix:semicolon
multiline_comment|/* dependent on type of interface card */
DECL|variable|isp16_ctrl
r_static
id|u_char
id|isp16_ctrl
suffix:semicolon
DECL|variable|isp16_enable_port
r_static
id|u_short
id|isp16_enable_port
suffix:semicolon
DECL|variable|isp16_cdrom_base
r_static
r_int
id|isp16_cdrom_base
op_assign
id|ISP16_CDROM_IO_BASE
suffix:semicolon
DECL|variable|isp16_cdrom_irq
r_static
r_int
id|isp16_cdrom_irq
op_assign
id|ISP16_CDROM_IRQ
suffix:semicolon
DECL|variable|isp16_cdrom_dma
r_static
r_int
id|isp16_cdrom_dma
op_assign
id|ISP16_CDROM_DMA
suffix:semicolon
DECL|variable|isp16_cdrom_type
r_static
r_char
op_star
id|isp16_cdrom_type
op_assign
id|ISP16_CDROM_TYPE
suffix:semicolon
macro_line|#ifdef MODULE
id|MODULE_PARM
c_func
(paren
id|isp16_cdrom_base
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|isp16_cdrom_irq
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|isp16_cdrom_dma
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|isp16_cdrom_type
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
r_void
id|isp16_exit
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|ISP16_IN
mdefine_line|#define ISP16_IN(p) (outb(isp16_ctrl,ISP16_CTRL_PORT), inb(p))
DECL|macro|ISP16_OUT
mdefine_line|#define ISP16_OUT(p,b) (outb(isp16_ctrl,ISP16_CTRL_PORT), outb(b,p))
macro_line|#ifndef MODULE
r_static
r_int
DECL|function|isp16_setup
id|__init
id|isp16_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|ints
(braket
l_int|4
)braket
suffix:semicolon
(paren
r_void
)paren
id|get_options
c_func
(paren
id|str
comma
id|ARRAY_SIZE
c_func
(paren
id|ints
)paren
comma
id|ints
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OG
l_int|0
)paren
id|isp16_cdrom_base
op_assign
id|ints
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OG
l_int|1
)paren
id|isp16_cdrom_irq
op_assign
id|ints
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OG
l_int|2
)paren
id|isp16_cdrom_dma
op_assign
id|ints
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|str
)paren
id|isp16_cdrom_type
op_assign
id|str
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;isp16=&quot;
comma
id|isp16_setup
)paren
suffix:semicolon
macro_line|#endif /* MODULE */
multiline_comment|/*&n; *  ISP16 initialisation.&n; *&n; */
r_int
id|__init
DECL|function|isp16_init
id|isp16_init
c_func
(paren
r_void
)paren
(brace
id|u_char
id|expected_drive
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ISP16: configuration cdrom interface, version %d.%d.&bslash;n&quot;
comma
id|ISP16_VERSION_MAJOR
comma
id|ISP16_VERSION_MINOR
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|isp16_cdrom_type
comma
l_string|&quot;noisp16&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ISP16: no cdrom interface configured.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|ISP16_IO_BASE
comma
id|ISP16_IO_SIZE
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ISP16: i/o ports already in use.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|isp16_type
op_assign
id|isp16_detect
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ISP16: no cdrom interface found.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ISP16: cdrom interface (with OPTi 82C92%d chip) detected.&bslash;n&quot;
comma
(paren
id|isp16_type
op_eq
l_int|2
)paren
ques
c_cond
l_int|9
suffix:colon
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|isp16_cdrom_type
comma
l_string|&quot;Sanyo&quot;
)paren
)paren
id|expected_drive
op_assign
(paren
id|isp16_type
ques
c_cond
id|ISP16_SANYO1
suffix:colon
id|ISP16_SANYO0
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|isp16_cdrom_type
comma
l_string|&quot;Sony&quot;
)paren
)paren
id|expected_drive
op_assign
id|ISP16_SONY
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|isp16_cdrom_type
comma
l_string|&quot;Panasonic&quot;
)paren
)paren
id|expected_drive
op_assign
(paren
id|isp16_type
ques
c_cond
id|ISP16_PANASONIC1
suffix:colon
id|ISP16_PANASONIC0
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|isp16_cdrom_type
comma
l_string|&quot;Mitsumi&quot;
)paren
)paren
id|expected_drive
op_assign
id|ISP16_MITSUMI
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;ISP16: %s not supported by cdrom interface.&bslash;n&quot;
comma
id|isp16_cdrom_type
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|isp16_cdi_config
c_func
(paren
id|isp16_cdrom_base
comma
id|expected_drive
comma
id|isp16_cdrom_irq
comma
id|isp16_cdrom_dma
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ISP16: cdrom interface has not been properly configured.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ISP16: cdrom interface set up with io base 0x%03X, irq %d, dma %d,&quot;
l_string|&quot; type %s.&bslash;n&quot;
comma
id|isp16_cdrom_base
comma
id|isp16_cdrom_irq
comma
id|isp16_cdrom_dma
comma
id|isp16_cdrom_type
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|isp16_detect
id|isp16_detect
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|isp16_c929__detect
c_func
(paren
)paren
op_ge
l_int|0
)paren
r_return
l_int|2
suffix:semicolon
r_else
r_return
id|isp16_c928__detect
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|isp16_c928__detect
id|isp16_c928__detect
c_func
(paren
r_void
)paren
(brace
id|u_char
id|ctrl
suffix:semicolon
id|u_char
id|enable_cdrom
suffix:semicolon
id|u_char
id|io
suffix:semicolon
r_int
id|i
op_assign
op_minus
l_int|1
suffix:semicolon
id|isp16_ctrl
op_assign
id|ISP16_C928__CTRL
suffix:semicolon
id|isp16_enable_port
op_assign
id|ISP16_C928__ENABLE_PORT
suffix:semicolon
multiline_comment|/* read&squot; and write&squot; are a special read and write, respectively */
multiline_comment|/* read&squot; ISP16_CTRL_PORT, clear last two bits and write&squot; back the result */
id|ctrl
op_assign
id|ISP16_IN
c_func
(paren
id|ISP16_CTRL_PORT
)paren
op_amp
l_int|0xFC
suffix:semicolon
id|ISP16_OUT
c_func
(paren
id|ISP16_CTRL_PORT
comma
id|ctrl
)paren
suffix:semicolon
multiline_comment|/* read&squot; 3,4 and 5-bit from the cdrom enable port */
id|enable_cdrom
op_assign
id|ISP16_IN
c_func
(paren
id|ISP16_C928__ENABLE_PORT
)paren
op_amp
l_int|0x38
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|enable_cdrom
op_amp
l_int|0x20
)paren
)paren
(brace
multiline_comment|/* 5-bit not set */
multiline_comment|/* read&squot; last 2 bits of ISP16_IO_SET_PORT */
id|io
op_assign
id|ISP16_IN
c_func
(paren
id|ISP16_IO_SET_PORT
)paren
op_amp
l_int|0x03
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|io
op_amp
l_int|0x01
)paren
op_lshift
l_int|1
)paren
op_eq
(paren
id|io
op_amp
l_int|0x02
)paren
)paren
(brace
multiline_comment|/* bits are the same */
r_if
c_cond
(paren
id|io
op_eq
l_int|0
)paren
(brace
multiline_comment|/* ...the same and 0 */
id|i
op_assign
l_int|0
suffix:semicolon
id|enable_cdrom
op_or_assign
l_int|0x20
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* ...the same and 1 */
multiline_comment|/* my card, first time &squot;round */
id|i
op_assign
l_int|1
suffix:semicolon
id|enable_cdrom
op_or_assign
l_int|0x28
suffix:semicolon
)brace
id|ISP16_OUT
c_func
(paren
id|ISP16_C928__ENABLE_PORT
comma
id|enable_cdrom
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* bits are not the same */
id|ISP16_OUT
c_func
(paren
id|ISP16_CTRL_PORT
comma
id|ctrl
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
multiline_comment|/* -&gt; not detected: possibly incorrect conclusion */
)brace
)brace
r_else
r_if
c_cond
(paren
id|enable_cdrom
op_eq
l_int|0x20
)paren
id|i
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|enable_cdrom
op_eq
l_int|0x28
)paren
multiline_comment|/* my card, already initialised */
id|i
op_assign
l_int|1
suffix:semicolon
id|ISP16_OUT
c_func
(paren
id|ISP16_CTRL_PORT
comma
id|ctrl
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|isp16_c929__detect
id|isp16_c929__detect
c_func
(paren
r_void
)paren
(brace
id|u_char
id|ctrl
suffix:semicolon
id|u_char
id|tmp
suffix:semicolon
id|isp16_ctrl
op_assign
id|ISP16_C929__CTRL
suffix:semicolon
id|isp16_enable_port
op_assign
id|ISP16_C929__ENABLE_PORT
suffix:semicolon
multiline_comment|/* read&squot; and write&squot; are a special read and write, respectively */
multiline_comment|/* read&squot; ISP16_CTRL_PORT and save */
id|ctrl
op_assign
id|ISP16_IN
c_func
(paren
id|ISP16_CTRL_PORT
)paren
suffix:semicolon
multiline_comment|/* write&squot; zero to the ctrl port and get response */
id|ISP16_OUT
c_func
(paren
id|ISP16_CTRL_PORT
comma
l_int|0
)paren
suffix:semicolon
id|tmp
op_assign
id|ISP16_IN
c_func
(paren
id|ISP16_CTRL_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
l_int|2
)paren
multiline_comment|/* isp16 with 82C929 not detected */
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* restore ctrl port value */
id|ISP16_OUT
c_func
(paren
id|ISP16_CTRL_PORT
comma
id|ctrl
)paren
suffix:semicolon
r_return
l_int|2
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|isp16_cdi_config
id|isp16_cdi_config
c_func
(paren
r_int
id|base
comma
id|u_char
id|drive_type
comma
r_int
id|irq
comma
r_int
id|dma
)paren
(brace
id|u_char
id|base_code
suffix:semicolon
id|u_char
id|irq_code
suffix:semicolon
id|u_char
id|dma_code
suffix:semicolon
id|u_char
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drive_type
op_eq
id|ISP16_MITSUMI
)paren
op_logical_and
(paren
id|dma
op_ne
l_int|0
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;ISP16: Mitsumi cdrom drive has no dma support.&bslash;n&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|base
)paren
(brace
r_case
l_int|0x340
suffix:colon
id|base_code
op_assign
id|ISP16_BASE_340
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x330
suffix:colon
id|base_code
op_assign
id|ISP16_BASE_330
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x360
suffix:colon
id|base_code
op_assign
id|ISP16_BASE_360
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x320
suffix:colon
id|base_code
op_assign
id|ISP16_BASE_320
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;ISP16: base address 0x%03X not supported by cdrom interface.&bslash;n&quot;
comma
id|base
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
l_int|0
suffix:colon
id|irq_code
op_assign
id|ISP16_IRQ_X
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* disable irq */
r_case
l_int|5
suffix:colon
id|irq_code
op_assign
id|ISP16_IRQ_5
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ISP16: irq 5 shouldn&squot;t be used by cdrom interface,&quot;
l_string|&quot; due to possible conflicts with the sound card.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|irq_code
op_assign
id|ISP16_IRQ_7
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ISP16: irq 7 shouldn&squot;t be used by cdrom interface,&quot;
l_string|&quot; due to possible conflicts with the sound card.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|irq_code
op_assign
id|ISP16_IRQ_3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9
suffix:colon
id|irq_code
op_assign
id|ISP16_IRQ_9
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
id|irq_code
op_assign
id|ISP16_IRQ_10
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|11
suffix:colon
id|irq_code
op_assign
id|ISP16_IRQ_11
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;ISP16: irq %d not supported by cdrom interface.&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|dma
)paren
(brace
r_case
l_int|0
suffix:colon
id|dma_code
op_assign
id|ISP16_DMA_X
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* disable dma */
r_case
l_int|1
suffix:colon
id|printk
c_func
(paren
l_string|&quot;ISP16: dma 1 cannot be used by cdrom interface,&quot;
l_string|&quot; due to conflict with the sound card.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|dma_code
op_assign
id|ISP16_DMA_3
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|dma_code
op_assign
id|ISP16_DMA_5
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|dma_code
op_assign
id|ISP16_DMA_6
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|dma_code
op_assign
id|ISP16_DMA_7
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;ISP16: dma %d not supported by cdrom interface.&bslash;n&quot;
comma
id|dma
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|drive_type
op_ne
id|ISP16_SONY
op_logical_and
id|drive_type
op_ne
id|ISP16_PANASONIC0
op_logical_and
id|drive_type
op_ne
id|ISP16_PANASONIC1
op_logical_and
id|drive_type
op_ne
id|ISP16_SANYO0
op_logical_and
id|drive_type
op_ne
id|ISP16_SANYO1
op_logical_and
id|drive_type
op_ne
id|ISP16_MITSUMI
op_logical_and
id|drive_type
op_ne
id|ISP16_DRIVE_X
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ISP16: drive type (code 0x%02X) not supported by cdrom&quot;
l_string|&quot; interface.&bslash;n&quot;
comma
id|drive_type
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* set type of interface */
id|i
op_assign
id|ISP16_IN
c_func
(paren
id|ISP16_DRIVE_SET_PORT
)paren
op_amp
id|ISP16_DRIVE_SET_MASK
suffix:semicolon
multiline_comment|/* clear some bits */
id|ISP16_OUT
c_func
(paren
id|ISP16_DRIVE_SET_PORT
comma
id|i
op_or
id|drive_type
)paren
suffix:semicolon
multiline_comment|/* enable cdrom on interface with 82C929 chip */
r_if
c_cond
(paren
id|isp16_type
OG
l_int|1
)paren
id|ISP16_OUT
c_func
(paren
id|isp16_enable_port
comma
id|ISP16_ENABLE_CDROM
)paren
suffix:semicolon
multiline_comment|/* set base address, irq and dma */
id|i
op_assign
id|ISP16_IN
c_func
(paren
id|ISP16_IO_SET_PORT
)paren
op_amp
id|ISP16_IO_SET_MASK
suffix:semicolon
multiline_comment|/* keep some bits */
id|ISP16_OUT
c_func
(paren
id|ISP16_IO_SET_PORT
comma
id|i
op_or
id|base_code
op_or
id|irq_code
op_or
id|dma_code
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|isp16_exit
r_void
id|__exit
id|isp16_exit
c_func
(paren
r_void
)paren
(brace
id|release_region
c_func
(paren
id|ISP16_IO_BASE
comma
id|ISP16_IO_SIZE
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ISP16: module released.&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|variable|isp16_init
id|module_init
c_func
(paren
id|isp16_init
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|isp16_exit
id|module_exit
c_func
(paren
id|isp16_exit
)paren
suffix:semicolon
eof
