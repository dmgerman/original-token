multiline_comment|/*&n; * sound/pss.c&n; *&n; * The low level driver for the Personal Sound System (ECHO ESC614).&n; */
multiline_comment|/*&n; * Copyright by Hannu Savolainen 1993-1996&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions are&n; * met: 1. Redistributions of source code must retain the above copyright&n; * notice, this list of conditions and the following disclaimer. 2.&n; * Redistributions in binary form must reproduce the above copyright notice,&n; * this list of conditions and the following disclaimer in the documentation&n; * and/or other materials provided with the distribution.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND ANY&n; * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED&n; * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR&n; * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER&n; * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;sound_config.h&quot;
macro_line|#if defined(CONFIG_PSS) &amp;&amp; defined(CONFIG_AUDIO)
multiline_comment|/*&n; * PSS registers.&n; */
DECL|macro|REG
mdefine_line|#define REG(x)&t;(devc-&gt;base+x)
DECL|macro|PSS_DATA
mdefine_line|#define&t;PSS_DATA&t;0
DECL|macro|PSS_STATUS
mdefine_line|#define&t;PSS_STATUS&t;2
DECL|macro|PSS_CONTROL
mdefine_line|#define PSS_CONTROL&t;2
DECL|macro|PSS_ID
mdefine_line|#define&t;PSS_ID&t;&t;4
DECL|macro|PSS_IRQACK
mdefine_line|#define&t;PSS_IRQACK&t;4
DECL|macro|PSS_PIO
mdefine_line|#define&t;PSS_PIO&t;&t;0x1a
multiline_comment|/*&n; * Config registers&n; */
DECL|macro|CONF_PSS
mdefine_line|#define CONF_PSS&t;0x10
DECL|macro|CONF_WSS
mdefine_line|#define CONF_WSS&t;0x12
DECL|macro|CONF_SB
mdefine_line|#define CONF_SB&t;&t;0x13
DECL|macro|CONF_CDROM
mdefine_line|#define CONF_CDROM&t;0x16
DECL|macro|CONF_MIDI
mdefine_line|#define CONF_MIDI&t;0x18
multiline_comment|/*&n; * Status bits.&n; */
DECL|macro|PSS_FLAG3
mdefine_line|#define PSS_FLAG3     0x0800
DECL|macro|PSS_FLAG2
mdefine_line|#define PSS_FLAG2     0x0400
DECL|macro|PSS_FLAG1
mdefine_line|#define PSS_FLAG1     0x1000
DECL|macro|PSS_FLAG0
mdefine_line|#define PSS_FLAG0     0x0800
DECL|macro|PSS_WRITE_EMPTY
mdefine_line|#define PSS_WRITE_EMPTY  0x8000
DECL|macro|PSS_READ_FULL
mdefine_line|#define PSS_READ_FULL    0x4000
macro_line|#include &quot;coproc.h&quot;
macro_line|#ifdef PSS_HAVE_LD
macro_line|#include &quot;synth-ld.h&quot;
macro_line|#else
DECL|variable|pss_synthLen
r_static
r_int
id|pss_synthLen
op_assign
l_int|0
suffix:semicolon
DECL|variable|pss_synth
r_static
r_int
r_char
id|pss_synth
(braket
l_int|1
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
macro_line|#endif
DECL|struct|pss_config
r_typedef
r_struct
id|pss_config
(brace
DECL|member|base
r_int
id|base
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|dma
r_int
id|dma
suffix:semicolon
DECL|member|osp
r_int
op_star
id|osp
suffix:semicolon
)brace
DECL|typedef|pss_config
id|pss_config
suffix:semicolon
DECL|variable|pss_data
r_static
id|pss_config
id|pss_data
suffix:semicolon
DECL|variable|devc
r_static
id|pss_config
op_star
id|devc
op_assign
op_amp
id|pss_data
suffix:semicolon
DECL|variable|pss_initialized
r_static
r_int
id|pss_initialized
op_assign
l_int|0
suffix:semicolon
DECL|variable|nonstandard_microcode
r_static
r_int
id|nonstandard_microcode
op_assign
l_int|0
suffix:semicolon
r_int
DECL|function|probe_pss
id|probe_pss
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
r_int
id|id
suffix:semicolon
r_int
id|irq
comma
id|dma
suffix:semicolon
id|devc-&gt;base
op_assign
id|hw_config-&gt;io_base
suffix:semicolon
id|irq
op_assign
id|devc-&gt;irq
op_assign
id|hw_config-&gt;irq
suffix:semicolon
id|dma
op_assign
id|devc-&gt;dma
op_assign
id|hw_config-&gt;dma
suffix:semicolon
id|devc-&gt;osp
op_assign
id|hw_config-&gt;osp
suffix:semicolon
r_if
c_cond
(paren
id|devc-&gt;base
op_ne
l_int|0x220
op_logical_and
id|devc-&gt;base
op_ne
l_int|0x240
)paren
r_if
c_cond
(paren
id|devc-&gt;base
op_ne
l_int|0x230
op_logical_and
id|devc-&gt;base
op_ne
l_int|0x250
)paren
multiline_comment|/* Some cards use these */
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|check_region
(paren
id|devc-&gt;base
comma
l_int|16
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;PSS: I/O port conflict&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|id
op_assign
id|inw
(paren
id|REG
(paren
id|PSS_ID
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|id
op_rshift
l_int|8
)paren
op_ne
l_char|&squot;E&squot;
)paren
(brace
multiline_comment|/* printk (&quot;No PSS signature detected at 0x%x (0x%x)&bslash;n&quot;, devc-&gt;base, id); */
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|set_irq
id|set_irq
(paren
id|pss_config
op_star
id|devc
comma
r_int
id|dev
comma
r_int
id|irq
)paren
(brace
r_static
r_int
r_int
id|irq_bits
(braket
l_int|16
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0008
comma
l_int|0x0000
comma
l_int|0x0010
comma
l_int|0x0000
comma
l_int|0x0018
comma
l_int|0x0000
comma
l_int|0x0020
comma
l_int|0x0028
comma
l_int|0x0030
comma
l_int|0x0038
comma
l_int|0x0000
comma
l_int|0x0000
comma
l_int|0x0000
)brace
suffix:semicolon
r_int
r_int
id|tmp
comma
id|bits
suffix:semicolon
r_if
c_cond
(paren
id|irq
template_param
l_int|15
)paren
r_return
l_int|0
suffix:semicolon
id|tmp
op_assign
id|inw
(paren
id|REG
(paren
id|dev
)paren
)paren
op_amp
op_complement
l_int|0x38
suffix:semicolon
multiline_comment|/* Load confreg, mask IRQ bits out */
r_if
c_cond
(paren
(paren
id|bits
op_assign
id|irq_bits
(braket
id|irq
)braket
)paren
op_eq
l_int|0
op_logical_and
id|irq
op_ne
l_int|0
)paren
(brace
id|printk
(paren
l_string|&quot;PSS: Invalid IRQ %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|outw
(paren
id|tmp
op_or
id|bits
comma
id|REG
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|set_io_base
id|set_io_base
(paren
id|pss_config
op_star
id|devc
comma
r_int
id|dev
comma
r_int
id|base
)paren
(brace
r_int
r_int
id|tmp
op_assign
id|inw
(paren
id|REG
(paren
id|dev
)paren
)paren
op_amp
l_int|0x003f
suffix:semicolon
r_int
r_int
id|bits
op_assign
(paren
id|base
op_amp
l_int|0x0ffc
)paren
op_lshift
l_int|4
suffix:semicolon
id|outw
(paren
id|bits
op_or
id|tmp
comma
id|REG
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|set_dma
id|set_dma
(paren
id|pss_config
op_star
id|devc
comma
r_int
id|dev
comma
r_int
id|dma
)paren
(brace
r_static
r_int
r_int
id|dma_bits
(braket
l_int|8
)braket
op_assign
(brace
l_int|0x0001
comma
l_int|0x0002
comma
l_int|0x0000
comma
l_int|0x0003
comma
l_int|0x0000
comma
l_int|0x0005
comma
l_int|0x0006
comma
l_int|0x0007
)brace
suffix:semicolon
r_int
r_int
id|tmp
comma
id|bits
suffix:semicolon
r_if
c_cond
(paren
id|dma
template_param
l_int|7
)paren
r_return
l_int|0
suffix:semicolon
id|tmp
op_assign
id|inw
(paren
id|REG
(paren
id|dev
)paren
)paren
op_amp
op_complement
l_int|0x07
suffix:semicolon
multiline_comment|/* Load confreg, mask DMA bits out */
r_if
c_cond
(paren
(paren
id|bits
op_assign
id|dma_bits
(braket
id|dma
)braket
)paren
op_eq
l_int|0
op_logical_and
id|dma
op_ne
l_int|4
)paren
(brace
id|printk
(paren
l_string|&quot;PSS: Invalid DMA %d&bslash;n&quot;
comma
id|dma
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|outw
(paren
id|tmp
op_or
id|bits
comma
id|REG
(paren
id|dev
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|pss_reset_dsp
id|pss_reset_dsp
(paren
id|pss_config
op_star
id|devc
)paren
(brace
r_int
r_int
id|i
comma
id|limit
op_assign
id|jiffies
op_plus
l_int|10
suffix:semicolon
id|outw
(paren
l_int|0x2000
comma
id|REG
(paren
id|PSS_CONTROL
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32768
op_logical_and
id|jiffies
OL
id|limit
suffix:semicolon
id|i
op_increment
)paren
id|inw
(paren
id|REG
(paren
id|PSS_CONTROL
)paren
)paren
suffix:semicolon
id|outw
(paren
l_int|0x0000
comma
id|REG
(paren
id|PSS_CONTROL
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|pss_put_dspword
id|pss_put_dspword
(paren
id|pss_config
op_star
id|devc
comma
r_int
r_int
id|word
)paren
(brace
r_int
id|i
comma
id|val
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|327680
suffix:semicolon
id|i
op_increment
)paren
(brace
id|val
op_assign
id|inw
(paren
id|REG
(paren
id|PSS_STATUS
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|PSS_WRITE_EMPTY
)paren
(brace
id|outw
(paren
id|word
comma
id|REG
(paren
id|PSS_DATA
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|pss_get_dspword
id|pss_get_dspword
(paren
id|pss_config
op_star
id|devc
comma
r_int
r_int
op_star
id|word
)paren
(brace
r_int
id|i
comma
id|val
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|327680
suffix:semicolon
id|i
op_increment
)paren
(brace
id|val
op_assign
id|inw
(paren
id|REG
(paren
id|PSS_STATUS
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|PSS_READ_FULL
)paren
(brace
op_star
id|word
op_assign
id|inw
(paren
id|REG
(paren
id|PSS_DATA
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|pss_download_boot
id|pss_download_boot
(paren
id|pss_config
op_star
id|devc
comma
r_int
r_char
op_star
id|block
comma
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_int
id|i
comma
id|limit
comma
id|val
comma
id|count
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|CPF_FIRST
)paren
(brace
multiline_comment|/*_____ Warn DSP software that a boot is coming */
id|outw
(paren
l_int|0x00fe
comma
id|REG
(paren
id|PSS_DATA
)paren
)paren
suffix:semicolon
id|limit
op_assign
id|jiffies
op_plus
l_int|10
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32768
op_logical_and
id|jiffies
OL
id|limit
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|inw
(paren
id|REG
(paren
id|PSS_DATA
)paren
)paren
op_eq
l_int|0x5500
)paren
r_break
suffix:semicolon
id|outw
(paren
op_star
id|block
op_increment
comma
id|REG
(paren
id|PSS_DATA
)paren
)paren
suffix:semicolon
id|pss_reset_dsp
(paren
id|devc
)paren
suffix:semicolon
)brace
id|count
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|j
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|327670
suffix:semicolon
id|j
op_increment
)paren
(brace
multiline_comment|/*_____ Wait for BG to appear */
r_if
c_cond
(paren
id|inw
(paren
id|REG
(paren
id|PSS_STATUS
)paren
)paren
op_amp
id|PSS_FLAG3
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|j
op_eq
l_int|327670
)paren
(brace
multiline_comment|/* It&squot;s ok we timed out when the file was empty */
r_if
c_cond
(paren
id|count
op_ge
id|size
op_logical_and
id|flags
op_amp
id|CPF_LAST
)paren
r_break
suffix:semicolon
r_else
(brace
id|printk
(paren
l_string|&quot;&bslash;nPSS: DownLoad timeout problems, byte %d=%d&bslash;n&quot;
comma
id|count
comma
id|size
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*_____ Send the next byte */
id|outw
(paren
op_star
id|block
op_increment
comma
id|REG
(paren
id|PSS_DATA
)paren
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|CPF_LAST
)paren
(brace
multiline_comment|/*_____ Why */
id|outw
(paren
l_int|0
comma
id|REG
(paren
id|PSS_DATA
)paren
)paren
suffix:semicolon
id|limit
op_assign
id|jiffies
op_plus
l_int|10
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32768
op_logical_and
id|jiffies
OL
id|limit
suffix:semicolon
id|i
op_increment
)paren
id|val
op_assign
id|inw
(paren
id|REG
(paren
id|PSS_STATUS
)paren
)paren
suffix:semicolon
id|limit
op_assign
id|jiffies
op_plus
l_int|10
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32768
op_logical_and
id|jiffies
OL
id|limit
suffix:semicolon
id|i
op_increment
)paren
(brace
id|val
op_assign
id|inw
(paren
id|REG
(paren
id|PSS_STATUS
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
l_int|0x4000
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/* now read the version */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32000
suffix:semicolon
id|i
op_increment
)paren
(brace
id|val
op_assign
id|inw
(paren
id|REG
(paren
id|PSS_STATUS
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|PSS_READ_FULL
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|32000
)paren
r_return
l_int|0
suffix:semicolon
id|val
op_assign
id|inw
(paren
id|REG
(paren
id|PSS_DATA
)paren
)paren
suffix:semicolon
multiline_comment|/* printk(&quot;&lt;PSS: microcode version %d.%d loaded&gt;&quot;, val/16, val % 16); */
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_int
DECL|function|attach_pss
id|attach_pss
(paren
r_int
id|mem_start
comma
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
r_int
id|id
suffix:semicolon
r_char
id|tmp
(braket
l_int|100
)braket
suffix:semicolon
id|devc-&gt;base
op_assign
id|hw_config-&gt;io_base
suffix:semicolon
id|devc-&gt;irq
op_assign
id|hw_config-&gt;irq
suffix:semicolon
id|devc-&gt;dma
op_assign
id|hw_config-&gt;dma
suffix:semicolon
id|devc-&gt;osp
op_assign
id|hw_config-&gt;osp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|probe_pss
(paren
id|hw_config
)paren
)paren
r_return
id|mem_start
suffix:semicolon
id|id
op_assign
id|inw
(paren
id|REG
(paren
id|PSS_ID
)paren
)paren
op_amp
l_int|0x00ff
suffix:semicolon
multiline_comment|/*&n;     * Disable all emulations. Will be enabled later (if required).&n;   */
id|outw
(paren
l_int|0x0000
comma
id|REG
(paren
id|CONF_PSS
)paren
)paren
suffix:semicolon
id|outw
(paren
l_int|0x0000
comma
id|REG
(paren
id|CONF_WSS
)paren
)paren
suffix:semicolon
id|outw
(paren
l_int|0x0000
comma
id|REG
(paren
id|CONF_SB
)paren
)paren
suffix:semicolon
id|outw
(paren
l_int|0x0000
comma
id|REG
(paren
id|CONF_MIDI
)paren
)paren
suffix:semicolon
id|outw
(paren
l_int|0x0000
comma
id|REG
(paren
id|CONF_CDROM
)paren
)paren
suffix:semicolon
macro_line|#if YOU_REALLY_WANT_TO_ALLOCATE_THESE_RESOURCES
r_if
c_cond
(paren
id|sound_alloc_dma
(paren
id|hw_config-&gt;dma
comma
l_string|&quot;PSS&quot;
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;pss.c: Can&squot;t allocate DMA channel&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|mem_start
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|set_irq
(paren
id|devc
comma
id|CONF_PSS
comma
id|devc-&gt;irq
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;PSS: IRQ error&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|mem_start
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|set_dma
(paren
id|devc
comma
id|CONF_PSS
comma
id|devc-&gt;dma
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;PSS: DRQ error&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|mem_start
suffix:semicolon
)brace
macro_line|#endif
id|pss_initialized
op_assign
l_int|1
suffix:semicolon
id|sprintf
(paren
id|tmp
comma
l_string|&quot;ECHO-PSS  Rev. %d&quot;
comma
id|id
)paren
suffix:semicolon
id|conf_printf
(paren
id|tmp
comma
id|hw_config
)paren
suffix:semicolon
r_return
id|mem_start
suffix:semicolon
)brace
r_int
DECL|function|probe_pss_mpu
id|probe_pss_mpu
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
id|timeout
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pss_initialized
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|check_region
(paren
id|hw_config-&gt;io_base
comma
l_int|2
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;PSS: MPU I/O port conflict&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|set_io_base
(paren
id|devc
comma
id|CONF_MIDI
comma
id|hw_config-&gt;io_base
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;PSS: MIDI base error.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|set_irq
(paren
id|devc
comma
id|CONF_MIDI
comma
id|hw_config-&gt;irq
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;PSS: MIDI IRQ error.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pss_synthLen
)paren
(brace
id|printk
(paren
l_string|&quot;PSS: Can&squot;t enable MPU. MIDI synth microcode not available.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pss_download_boot
(paren
id|devc
comma
id|pss_synth
comma
id|pss_synthLen
comma
id|CPF_FIRST
op_or
id|CPF_LAST
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;PSS: Unable to load MIDI synth microcode to DSP.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Finally wait until the DSP algorithm has initialized itself and&n; * deactivates receive interrupt.&n; */
r_for
c_loop
(paren
id|timeout
op_assign
l_int|900000
suffix:semicolon
id|timeout
OG
l_int|0
suffix:semicolon
id|timeout
op_decrement
)paren
(brace
r_if
c_cond
(paren
(paren
id|inb
(paren
id|hw_config-&gt;io_base
op_plus
l_int|1
)paren
op_amp
l_int|0x80
)paren
op_eq
l_int|0
)paren
multiline_comment|/* Input data avail */
id|inb
(paren
id|hw_config-&gt;io_base
)paren
suffix:semicolon
multiline_comment|/* Discard it */
r_else
r_break
suffix:semicolon
multiline_comment|/* No more input */
)brace
macro_line|#if (defined(CONFIG_MPU401) || defined(CONFIG_MPU_EMU)) &amp;&amp; defined(CONFIG_MIDI)
r_return
id|probe_mpu401
(paren
id|hw_config
)paren
suffix:semicolon
macro_line|#else
r_return
l_int|0
macro_line|#endif
)brace
r_static
r_int
DECL|function|pss_coproc_open
id|pss_coproc_open
(paren
r_void
op_star
id|dev_info
comma
r_int
id|sub_device
)paren
(brace
r_switch
c_cond
(paren
id|sub_device
)paren
(brace
r_case
id|COPR_MIDI
suffix:colon
r_if
c_cond
(paren
id|pss_synthLen
op_eq
l_int|0
)paren
(brace
id|printk
(paren
l_string|&quot;PSS: MIDI synth microcode not available.&bslash;n&quot;
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
id|nonstandard_microcode
)paren
r_if
c_cond
(paren
op_logical_neg
id|pss_download_boot
(paren
id|devc
comma
id|pss_synth
comma
id|pss_synthLen
comma
id|CPF_FIRST
op_or
id|CPF_LAST
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;PSS: Unable to load MIDI synth microcode to DSP.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|nonstandard_microcode
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|pss_coproc_close
id|pss_coproc_close
(paren
r_void
op_star
id|dev_info
comma
r_int
id|sub_device
)paren
(brace
r_return
suffix:semicolon
)brace
r_static
r_void
DECL|function|pss_coproc_reset
id|pss_coproc_reset
(paren
r_void
op_star
id|dev_info
)paren
(brace
r_if
c_cond
(paren
id|pss_synthLen
)paren
r_if
c_cond
(paren
op_logical_neg
id|pss_download_boot
(paren
id|devc
comma
id|pss_synth
comma
id|pss_synthLen
comma
id|CPF_FIRST
op_or
id|CPF_LAST
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;PSS: Unable to load MIDI synth microcode to DSP.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|nonstandard_microcode
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|download_boot_block
id|download_boot_block
(paren
r_void
op_star
id|dev_info
comma
id|copr_buffer
op_star
id|buf
)paren
(brace
r_if
c_cond
(paren
id|buf-&gt;len
op_le
l_int|0
op_logical_or
id|buf-&gt;len
OG
r_sizeof
(paren
id|buf-&gt;data
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pss_download_boot
(paren
id|devc
comma
id|buf-&gt;data
comma
id|buf-&gt;len
comma
id|buf-&gt;flags
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;PSS: Unable to load microcode block to DSP.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|nonstandard_microcode
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* The MIDI microcode has been overwritten */
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|pss_coproc_ioctl
id|pss_coproc_ioctl
(paren
r_void
op_star
id|dev_info
comma
r_int
r_int
id|cmd
comma
id|caddr_t
id|arg
comma
r_int
id|local
)paren
(brace
multiline_comment|/* printk(&quot;PSS coproc ioctl %x %x %d&bslash;n&quot;, cmd, arg, local); */
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SNDCTL_COPR_RESET
suffix:colon
id|pss_coproc_reset
(paren
id|dev_info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SNDCTL_COPR_LOAD
suffix:colon
(brace
id|copr_buffer
op_star
id|buf
suffix:semicolon
r_int
id|err
suffix:semicolon
id|buf
op_assign
(paren
id|copr_buffer
op_star
)paren
id|kmalloc
(paren
r_sizeof
(paren
id|copr_buffer
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOSPC
suffix:semicolon
id|memcpy_fromfs
(paren
(paren
r_char
op_star
)paren
id|buf
comma
op_amp
(paren
(paren
(paren
r_char
op_star
)paren
id|arg
)paren
(braket
l_int|0
)braket
)paren
comma
r_sizeof
(paren
op_star
id|buf
)paren
)paren
suffix:semicolon
id|err
op_assign
id|download_boot_block
(paren
id|dev_info
comma
id|buf
)paren
suffix:semicolon
id|kfree
(paren
id|buf
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SNDCTL_COPR_RDATA
suffix:colon
(brace
id|copr_debug_buf
id|buf
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
id|memcpy_fromfs
(paren
(paren
r_char
op_star
)paren
op_amp
id|buf
comma
op_amp
(paren
(paren
(paren
r_char
op_star
)paren
id|arg
)paren
(braket
l_int|0
)braket
)paren
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
id|save_flags
(paren
id|flags
)paren
suffix:semicolon
id|cli
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pss_put_dspword
(paren
id|devc
comma
l_int|0x00d0
)paren
)paren
(brace
id|restore_flags
(paren
id|flags
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
op_logical_neg
id|pss_put_dspword
(paren
id|devc
comma
(paren
r_int
r_int
)paren
(paren
id|buf.parm1
op_amp
l_int|0xffff
)paren
)paren
)paren
(brace
id|restore_flags
(paren
id|flags
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
op_logical_neg
id|pss_get_dspword
(paren
id|devc
comma
op_amp
id|tmp
)paren
)paren
(brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|buf.parm1
op_assign
id|tmp
suffix:semicolon
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
id|memcpy_tofs
(paren
(paren
op_amp
(paren
(paren
r_char
op_star
)paren
id|arg
)paren
(braket
l_int|0
)braket
)paren
comma
op_amp
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SNDCTL_COPR_WDATA
suffix:colon
(brace
id|copr_debug_buf
id|buf
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
id|memcpy_fromfs
(paren
(paren
r_char
op_star
)paren
op_amp
id|buf
comma
op_amp
(paren
(paren
(paren
r_char
op_star
)paren
id|arg
)paren
(braket
l_int|0
)braket
)paren
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
id|save_flags
(paren
id|flags
)paren
suffix:semicolon
id|cli
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pss_put_dspword
(paren
id|devc
comma
l_int|0x00d1
)paren
)paren
(brace
id|restore_flags
(paren
id|flags
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
op_logical_neg
id|pss_put_dspword
(paren
id|devc
comma
(paren
r_int
r_int
)paren
(paren
id|buf.parm1
op_amp
l_int|0xffff
)paren
)paren
)paren
(brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|tmp
op_assign
(paren
r_int
r_int
)paren
id|buf.parm2
op_amp
l_int|0xffff
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pss_put_dspword
(paren
id|devc
comma
id|tmp
)paren
)paren
(brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SNDCTL_COPR_WCODE
suffix:colon
(brace
id|copr_debug_buf
id|buf
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
id|memcpy_fromfs
(paren
(paren
r_char
op_star
)paren
op_amp
id|buf
comma
op_amp
(paren
(paren
(paren
r_char
op_star
)paren
id|arg
)paren
(braket
l_int|0
)braket
)paren
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
id|save_flags
(paren
id|flags
)paren
suffix:semicolon
id|cli
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pss_put_dspword
(paren
id|devc
comma
l_int|0x00d3
)paren
)paren
(brace
id|restore_flags
(paren
id|flags
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
op_logical_neg
id|pss_put_dspword
(paren
id|devc
comma
(paren
r_int
r_int
)paren
(paren
id|buf.parm1
op_amp
l_int|0xffff
)paren
)paren
)paren
(brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|tmp
op_assign
(paren
(paren
r_int
r_int
)paren
id|buf.parm2
op_rshift
l_int|8
)paren
op_amp
l_int|0xffff
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pss_put_dspword
(paren
id|devc
comma
id|tmp
)paren
)paren
(brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|tmp
op_assign
(paren
r_int
r_int
)paren
id|buf.parm2
op_amp
l_int|0x00ff
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pss_put_dspword
(paren
id|devc
comma
id|tmp
)paren
)paren
(brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SNDCTL_COPR_RCODE
suffix:colon
(brace
id|copr_debug_buf
id|buf
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
id|memcpy_fromfs
(paren
(paren
r_char
op_star
)paren
op_amp
id|buf
comma
op_amp
(paren
(paren
(paren
r_char
op_star
)paren
id|arg
)paren
(braket
l_int|0
)braket
)paren
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
id|save_flags
(paren
id|flags
)paren
suffix:semicolon
id|cli
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pss_put_dspword
(paren
id|devc
comma
l_int|0x00d2
)paren
)paren
(brace
id|restore_flags
(paren
id|flags
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
op_logical_neg
id|pss_put_dspword
(paren
id|devc
comma
(paren
r_int
r_int
)paren
(paren
id|buf.parm1
op_amp
l_int|0xffff
)paren
)paren
)paren
(brace
id|restore_flags
(paren
id|flags
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
op_logical_neg
id|pss_get_dspword
(paren
id|devc
comma
op_amp
id|tmp
)paren
)paren
multiline_comment|/* Read msb */
(brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|buf.parm1
op_assign
id|tmp
op_lshift
l_int|8
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pss_get_dspword
(paren
id|devc
comma
op_amp
id|tmp
)paren
)paren
multiline_comment|/* Read lsb */
(brace
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|buf.parm1
op_or_assign
id|tmp
op_amp
l_int|0x00ff
suffix:semicolon
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
id|memcpy_tofs
(paren
(paren
op_amp
(paren
(paren
r_char
op_star
)paren
id|arg
)paren
(braket
l_int|0
)braket
)paren
comma
op_amp
id|buf
comma
r_sizeof
(paren
id|buf
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|variable|pss_coproc_operations
r_static
id|coproc_operations
id|pss_coproc_operations
op_assign
(brace
l_string|&quot;ADSP-2115&quot;
comma
id|pss_coproc_open
comma
id|pss_coproc_close
comma
id|pss_coproc_ioctl
comma
id|pss_coproc_reset
comma
op_amp
id|pss_data
)brace
suffix:semicolon
r_int
DECL|function|attach_pss_mpu
id|attach_pss_mpu
(paren
r_int
id|mem_start
comma
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
id|prev_devs
suffix:semicolon
r_int
id|ret
suffix:semicolon
macro_line|#if (defined(CONFIG_MPU401) || defined(CONFIG_MPU_EMU)) &amp;&amp; defined(CONFIG_MIDI)
id|prev_devs
op_assign
id|num_midis
suffix:semicolon
id|ret
op_assign
id|attach_mpu401
(paren
id|mem_start
comma
id|hw_config
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num_midis
op_eq
(paren
id|prev_devs
op_plus
l_int|1
)paren
)paren
multiline_comment|/* The MPU driver installed itself */
id|midi_devs
(braket
id|prev_devs
)braket
op_member_access_from_pointer
id|coproc
op_assign
op_amp
id|pss_coproc_operations
suffix:semicolon
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
r_int
DECL|function|probe_pss_mss
id|probe_pss_mss
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
id|timeout
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pss_initialized
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|check_region
(paren
id|hw_config-&gt;io_base
comma
l_int|8
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;PSS: WSS I/O port conflict&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|set_io_base
(paren
id|devc
comma
id|CONF_WSS
comma
id|hw_config-&gt;io_base
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;PSS: WSS base error.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|set_irq
(paren
id|devc
comma
id|CONF_WSS
comma
id|hw_config-&gt;irq
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;PSS: WSS IRQ error.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|set_dma
(paren
id|devc
comma
id|CONF_WSS
comma
id|hw_config-&gt;dma
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;PSS: WSS DRQ error&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     * For some reason the card returns 0xff in the WSS status register&n;     * immediately after boot. Propably MIDI+SB emulation algorithm&n;     * downloaded to the ADSP2115 spends some time initializing the card.&n;     * Let&squot;s try to wait until it finishes this task.&n;   */
r_for
c_loop
(paren
id|timeout
op_assign
l_int|0
suffix:semicolon
id|timeout
OL
l_int|100000
op_logical_and
(paren
id|inb
(paren
id|hw_config-&gt;io_base
op_plus
l_int|3
)paren
op_amp
l_int|0x3f
)paren
op_ne
l_int|0x04
suffix:semicolon
id|timeout
op_increment
)paren
suffix:semicolon
r_return
id|probe_ms_sound
(paren
id|hw_config
)paren
suffix:semicolon
)brace
r_int
DECL|function|attach_pss_mss
id|attach_pss_mss
(paren
r_int
id|mem_start
comma
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
id|prev_devs
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|prev_devs
op_assign
id|num_audiodevs
suffix:semicolon
id|ret
op_assign
id|attach_ms_sound
(paren
id|mem_start
comma
id|hw_config
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num_audiodevs
op_eq
(paren
id|prev_devs
op_plus
l_int|1
)paren
)paren
multiline_comment|/* The MSS driver installed itself */
id|audio_devs
(braket
id|prev_devs
)braket
op_member_access_from_pointer
id|coproc
op_assign
op_amp
id|pss_coproc_operations
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_void
DECL|function|unload_pss
id|unload_pss
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
)brace
r_void
DECL|function|unload_pss_mpu
id|unload_pss_mpu
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
id|unload_mpu401
(paren
id|hw_config
)paren
suffix:semicolon
)brace
r_void
DECL|function|unload_pss_mss
id|unload_pss_mss
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
id|unload_ms_sound
(paren
id|hw_config
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
