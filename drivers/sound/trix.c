multiline_comment|/*&n; * sound/trix.c&n; *&n; * Low level driver for the MediaTriX AudioTriX Pro&n; * (MT-0002-PC Control Chip)&n; *&n; * Copyright by Hannu Savolainen 1995&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions are&n; * met: 1. Redistributions of source code must retain the above copyright&n; * notice, this list of conditions and the following disclaimer. 2.&n; * Redistributions in binary form must reproduce the above copyright notice,&n; * this list of conditions and the following disclaimer in the documentation&n; * and/or other materials provided with the distribution.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND ANY&n; * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED&n; * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR&n; * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER&n; * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; */
macro_line|#include &quot;sound_config.h&quot;
macro_line|#if defined(CONFIGURE_SOUNDCARD) &amp;&amp; !defined(EXCLUDE_TRIX)
macro_line|#ifdef INCLUDE_TRIX_BOOT
macro_line|#include &quot;trix_boot.h&quot;
macro_line|#endif
DECL|variable|kilroy_was_here
r_static
r_int
id|kilroy_was_here
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Don&squot;t detect twice */
DECL|variable|sb_initialized
r_static
r_int
id|sb_initialized
op_assign
l_int|0
suffix:semicolon
DECL|variable|mpu_initialized
r_static
r_int
id|mpu_initialized
op_assign
l_int|0
suffix:semicolon
r_static
r_int
r_char
DECL|function|trix_read
id|trix_read
(paren
r_int
id|addr
)paren
(brace
id|OUTB
(paren
(paren
r_int
r_char
)paren
id|addr
comma
l_int|0x390
)paren
suffix:semicolon
multiline_comment|/* MT-0002-PC ASIC address */
r_return
id|INB
(paren
l_int|0x391
)paren
suffix:semicolon
multiline_comment|/* MT-0002-PC ASIC data */
)brace
r_static
r_void
DECL|function|trix_write
id|trix_write
(paren
r_int
id|addr
comma
r_int
id|data
)paren
(brace
id|OUTB
(paren
(paren
r_int
r_char
)paren
id|addr
comma
l_int|0x390
)paren
suffix:semicolon
multiline_comment|/* MT-0002-PC ASIC address */
id|OUTB
(paren
(paren
r_int
r_char
)paren
id|data
comma
l_int|0x391
)paren
suffix:semicolon
multiline_comment|/* MT-0002-PC ASIC data */
)brace
r_static
r_void
DECL|function|download_boot
id|download_boot
(paren
r_int
id|base
)paren
(brace
macro_line|#ifdef INCLUDE_TRIX_BOOT
r_int
id|i
op_assign
l_int|0
comma
id|n
op_assign
r_sizeof
(paren
id|trix_boot
)paren
suffix:semicolon
id|trix_write
(paren
l_int|0xf8
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* ??????? */
id|OUTB
(paren
l_int|0x01
comma
id|base
op_plus
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Clear the internal data pointer */
id|OUTB
(paren
l_int|0x00
comma
id|base
op_plus
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Restart */
multiline_comment|/*&n;     *  Write the boot code to the RAM upload/download register.&n;     *  Each write increments the internal data pointer.&n;   */
id|OUTB
(paren
l_int|0x01
comma
id|base
op_plus
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Clear the internal data pointer */
id|OUTB
(paren
l_int|0x1A
comma
l_int|0x390
)paren
suffix:semicolon
multiline_comment|/* Select RAM download/upload port */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|n
suffix:semicolon
id|i
op_increment
)paren
id|OUTB
(paren
id|trix_boot
(braket
id|i
)braket
comma
l_int|0x391
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|n
suffix:semicolon
id|i
OL
l_int|10016
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* Clear up to first 16 bytes of data RAM */
id|OUTB
(paren
l_int|0x00
comma
l_int|0x391
)paren
suffix:semicolon
id|OUTB
(paren
l_int|0x00
comma
id|base
op_plus
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Reset */
id|OUTB
(paren
l_int|0x50
comma
l_int|0x390
)paren
suffix:semicolon
multiline_comment|/* ?????? */
macro_line|#endif
)brace
r_static
r_int
DECL|function|trix_set_wss_port
id|trix_set_wss_port
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
r_char
id|addr_bits
suffix:semicolon
r_if
c_cond
(paren
id|kilroy_was_here
)paren
multiline_comment|/* Already initialized */
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|trix_read
(paren
l_int|0x15
)paren
op_ne
l_int|0x71
)paren
multiline_comment|/* No asic signature */
r_return
l_int|0
suffix:semicolon
id|kilroy_was_here
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;     * Disable separate wave playback and recording DMA channels since&n;     * the driver doesn&squot;t support duplex mode yet.&n;   */
id|trix_write
(paren
l_int|0x13
comma
id|trix_read
(paren
l_int|0x13
)paren
op_amp
op_complement
l_int|0x80
)paren
suffix:semicolon
id|trix_write
(paren
l_int|0x14
comma
id|trix_read
(paren
l_int|0x14
)paren
op_amp
op_complement
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/*&n;     * Configure the ASIC to place the codec to the proper I/O location&n;   */
r_switch
c_cond
(paren
id|hw_config-&gt;io_base
)paren
(brace
r_case
l_int|0x530
suffix:colon
id|addr_bits
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x604
suffix:colon
id|addr_bits
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xE80
suffix:colon
id|addr_bits
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xF40
suffix:colon
id|addr_bits
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
id|trix_write
(paren
l_int|0x19
comma
(paren
id|trix_read
(paren
l_int|0x19
)paren
op_amp
l_int|0x03
)paren
op_or
id|addr_bits
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *    Probe and attach routines for the Windows Sound System mode of&n; *      AudioTriX Pro&n; */
r_int
DECL|function|probe_trix_wss
id|probe_trix_wss
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
multiline_comment|/*&n;     * Check if the IO port returns valid signature. The original MS Sound&n;     * system returns 0x04 while some cards (AudioTriX Pro for example)&n;     * return 0x00.&n;   */
r_if
c_cond
(paren
op_logical_neg
id|trix_set_wss_port
(paren
id|hw_config
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|INB
(paren
id|hw_config-&gt;io_base
op_plus
l_int|3
)paren
op_amp
l_int|0x3f
)paren
op_ne
l_int|0x00
)paren
(brace
id|DDB
(paren
id|printk
(paren
l_string|&quot;No MSS signature detected on port 0x%x&bslash;n&quot;
comma
id|hw_config-&gt;io_base
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hw_config-&gt;irq
OG
l_int|11
)paren
(brace
id|printk
(paren
l_string|&quot;AudioTriX: Bad WSS IRQ %d&bslash;n&quot;
comma
id|hw_config-&gt;irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hw_config-&gt;dma
op_ne
l_int|0
op_logical_and
id|hw_config-&gt;dma
op_ne
l_int|1
op_logical_and
id|hw_config-&gt;dma
op_ne
l_int|3
)paren
(brace
id|printk
(paren
l_string|&quot;AudioTriX: Bad WSS DMA %d&bslash;n&quot;
comma
id|hw_config-&gt;dma
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     * Check that DMA0 is not in use with a 8 bit board.&n;   */
r_if
c_cond
(paren
id|hw_config-&gt;dma
op_eq
l_int|0
op_logical_and
id|INB
(paren
id|hw_config-&gt;io_base
op_plus
l_int|3
)paren
op_amp
l_int|0x80
)paren
(brace
id|printk
(paren
l_string|&quot;AudioTriX: Can&squot;t use DMA0 with a 8 bit card&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hw_config-&gt;irq
OG
l_int|7
op_logical_and
id|hw_config-&gt;irq
op_ne
l_int|9
op_logical_and
id|INB
(paren
id|hw_config-&gt;io_base
op_plus
l_int|3
)paren
op_amp
l_int|0x80
)paren
(brace
id|printk
(paren
l_string|&quot;AudioTriX: Can&squot;t use IRQ%d with a 8 bit card&bslash;n&quot;
comma
id|hw_config-&gt;irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|ad1848_detect
(paren
id|hw_config-&gt;io_base
op_plus
l_int|4
)paren
suffix:semicolon
)brace
r_int
DECL|function|attach_trix_wss
id|attach_trix_wss
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
r_static
r_int
r_char
id|interrupt_bits
(braket
l_int|12
)braket
op_assign
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|0x08
comma
op_minus
l_int|1
comma
l_int|0x10
comma
l_int|0x18
comma
l_int|0x20
)brace
suffix:semicolon
r_char
id|bits
suffix:semicolon
r_static
r_int
r_char
id|dma_bits
(braket
l_int|4
)braket
op_assign
(brace
l_int|1
comma
l_int|2
comma
l_int|0
comma
l_int|3
)brace
suffix:semicolon
r_int
id|config_port
op_assign
id|hw_config-&gt;io_base
op_plus
l_int|0
comma
id|version_port
op_assign
id|hw_config-&gt;io_base
op_plus
l_int|3
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kilroy_was_here
)paren
r_return
id|mem_start
suffix:semicolon
multiline_comment|/*&n;     * Set the IRQ and DMA addresses.&n;   */
id|bits
op_assign
id|interrupt_bits
(braket
id|hw_config-&gt;irq
)braket
suffix:semicolon
r_if
c_cond
(paren
id|bits
op_eq
op_minus
l_int|1
)paren
r_return
id|mem_start
suffix:semicolon
id|OUTB
(paren
id|bits
op_or
l_int|0x40
comma
id|config_port
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|INB
(paren
id|version_port
)paren
op_amp
l_int|0x40
)paren
op_eq
l_int|0
)paren
id|printk
(paren
l_string|&quot;[IRQ Conflict?]&quot;
)paren
suffix:semicolon
id|OUTB
(paren
id|bits
op_or
id|dma_bits
(braket
id|hw_config-&gt;dma
)braket
comma
id|config_port
)paren
suffix:semicolon
multiline_comment|/* Write IRQ+DMA setup */
id|ad1848_init
(paren
l_string|&quot;AudioTriX Pro&quot;
comma
id|hw_config-&gt;io_base
op_plus
l_int|4
comma
id|hw_config-&gt;irq
comma
id|hw_config-&gt;dma
comma
id|hw_config-&gt;dma
)paren
suffix:semicolon
r_return
id|mem_start
suffix:semicolon
)brace
r_int
DECL|function|probe_trix_sb
id|probe_trix_sb
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
id|tmp
suffix:semicolon
r_int
r_char
id|conf
suffix:semicolon
r_static
r_char
id|irq_translate
(braket
)braket
op_assign
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|0
comma
l_int|1
comma
l_int|2
comma
op_minus
l_int|1
comma
l_int|3
)brace
suffix:semicolon
macro_line|#ifndef INCLUDE_TRIX_BOOT
r_return
l_int|0
suffix:semicolon
multiline_comment|/* No boot code -&gt; no fun */
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|kilroy_was_here
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* AudioTriX Pro has not been detected earlier */
r_if
c_cond
(paren
id|sb_initialized
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|hw_config-&gt;io_base
op_amp
l_int|0xffffff8f
op_ne
l_int|0x200
)paren
r_return
l_int|0
suffix:semicolon
id|tmp
op_assign
id|hw_config-&gt;irq
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OG
l_int|7
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|irq_translate
(braket
id|tmp
)braket
op_eq
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
id|tmp
op_assign
id|hw_config-&gt;dma
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
l_int|1
op_logical_and
id|tmp
op_ne
l_int|3
)paren
r_return
l_int|0
suffix:semicolon
id|conf
op_assign
l_int|0x84
suffix:semicolon
multiline_comment|/* DMA and IRQ enable */
id|conf
op_or_assign
id|hw_config-&gt;io_base
op_amp
l_int|0x70
suffix:semicolon
multiline_comment|/* I/O address bits */
id|conf
op_or_assign
id|irq_translate
(braket
id|hw_config-&gt;irq
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hw_config-&gt;dma
op_eq
l_int|3
)paren
id|conf
op_or_assign
l_int|0x08
suffix:semicolon
id|trix_write
(paren
l_int|0x1b
comma
id|conf
)paren
suffix:semicolon
id|download_boot
(paren
id|hw_config-&gt;io_base
)paren
suffix:semicolon
id|sb_initialized
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_int
DECL|function|attach_trix_sb
id|attach_trix_sb
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
macro_line|#ifndef EXCLUDE_SB
r_extern
r_int
id|sb_no_recording
suffix:semicolon
id|sb_dsp_disable_midi
(paren
)paren
suffix:semicolon
id|sb_no_recording
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
id|printk
(paren
l_string|&quot; &lt;AudioTriX (SB)&gt;&quot;
)paren
suffix:semicolon
r_return
id|mem_start
suffix:semicolon
)brace
r_int
DECL|function|attach_trix_mpu
id|attach_trix_mpu
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
macro_line|#if (!defined(EXCLUDE_MPU401) || !defined(EXCLUDE_MPU_EMU)) &amp;&amp; !defined(EXCLUDE_MIDI)
r_return
id|attach_mpu401
(paren
id|mem_start
comma
id|hw_config
)paren
suffix:semicolon
macro_line|#else
r_return
id|mem_start
suffix:semicolon
macro_line|#endif
)brace
r_int
DECL|function|probe_trix_mpu
id|probe_trix_mpu
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
macro_line|#if (!defined(EXCLUDE_MPU401) || !defined(EXCLUDE_MPU_EMU)) &amp;&amp; !defined(EXCLUDE_MIDI)
r_int
r_char
id|conf
suffix:semicolon
r_static
r_char
id|irq_bits
(braket
)braket
op_assign
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|1
comma
l_int|2
comma
l_int|3
comma
op_minus
l_int|1
comma
l_int|4
comma
op_minus
l_int|1
comma
l_int|5
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kilroy_was_here
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* AudioTriX Pro has not been detected earlier */
r_if
c_cond
(paren
op_logical_neg
id|sb_initialized
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mpu_initialized
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|hw_config-&gt;irq
OG
l_int|9
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|irq_bits
(braket
id|hw_config-&gt;irq
)braket
op_eq
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|hw_config-&gt;io_base
)paren
(brace
r_case
l_int|0x330
suffix:colon
id|conf
op_assign
l_int|0x00
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x370
suffix:colon
id|conf
op_assign
l_int|0x04
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x3b0
suffix:colon
id|conf
op_assign
l_int|0x08
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x3f0
suffix:colon
id|conf
op_assign
l_int|0x0c
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Invalid port */
)brace
id|conf
op_or_assign
id|irq_bits
(braket
id|hw_config-&gt;irq
)braket
op_lshift
l_int|4
suffix:semicolon
id|trix_write
(paren
l_int|0x19
comma
(paren
id|trix_read
(paren
l_int|0x19
)paren
op_amp
l_int|0x83
)paren
op_or
id|conf
)paren
suffix:semicolon
id|mpu_initialized
op_assign
l_int|1
suffix:semicolon
r_return
id|probe_mpu401
(paren
id|hw_config
)paren
suffix:semicolon
macro_line|#else
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
eof