multiline_comment|/*&n; * sound/sound_switch.c&n; *&n; * The system call switch handler&n; */
multiline_comment|/*&n; * Copyright by Hannu Savolainen 1993-1996&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions are&n; * met: 1. Redistributions of source code must retain the above copyright&n; * notice, this list of conditions and the following disclaimer. 2.&n; * Redistributions in binary form must reproduce the above copyright notice,&n; * this list of conditions and the following disclaimer in the documentation&n; * and/or other materials provided with the distribution.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND ANY&n; * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED&n; * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR&n; * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER&n; * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;sound_config.h&quot;
DECL|struct|sbc_device
r_struct
id|sbc_device
(brace
DECL|member|usecount
r_int
id|usecount
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|in_use
r_static
r_int
id|in_use
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Total # of open devices */
multiline_comment|/*&n; * /dev/sndstatus -device&n; */
DECL|variable|status_buf
r_static
r_char
op_star
id|status_buf
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|status_len
DECL|variable|status_ptr
r_static
r_int
id|status_len
comma
id|status_ptr
suffix:semicolon
DECL|variable|status_busy
r_static
r_int
id|status_busy
op_assign
l_int|0
suffix:semicolon
r_static
r_int
DECL|function|put_status
id|put_status
(paren
r_char
op_star
id|s
)paren
(brace
r_int
id|l
op_assign
id|strnlen
(paren
id|s
comma
l_int|256
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status_len
op_plus
id|l
op_ge
l_int|4000
)paren
r_return
l_int|0
suffix:semicolon
id|memcpy
(paren
op_amp
id|status_buf
(braket
id|status_len
)braket
comma
id|s
comma
id|l
)paren
suffix:semicolon
id|status_len
op_add_assign
id|l
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|put_status_int
id|put_status_int
(paren
r_int
r_int
id|val
comma
r_int
id|radix
)paren
(brace
r_int
id|l
comma
id|v
suffix:semicolon
r_static
r_char
id|hx
(braket
)braket
op_assign
l_string|&quot;0123456789abcdef&quot;
suffix:semicolon
r_char
id|buf
(braket
l_int|11
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|val
)paren
r_return
id|put_status
(paren
l_string|&quot;0&quot;
)paren
suffix:semicolon
id|l
op_assign
l_int|0
suffix:semicolon
id|buf
(braket
l_int|10
)braket
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|val
)paren
(brace
id|v
op_assign
id|val
op_mod
id|radix
suffix:semicolon
id|val
op_assign
id|val
op_div
id|radix
suffix:semicolon
id|buf
(braket
l_int|9
op_minus
id|l
)braket
op_assign
id|hx
(braket
id|v
)braket
suffix:semicolon
id|l
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status_len
op_plus
id|l
op_ge
l_int|4000
)paren
r_return
l_int|0
suffix:semicolon
id|memcpy
(paren
op_amp
id|status_buf
(braket
id|status_len
)braket
comma
op_amp
id|buf
(braket
l_int|10
op_minus
id|l
)braket
comma
id|l
)paren
suffix:semicolon
id|status_len
op_add_assign
id|l
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_void
DECL|function|init_status
id|init_status
(paren
r_void
)paren
(brace
multiline_comment|/*&n;   * Write the status information to the status_buf and update status_len.&n;   * There is a limit of 4000 bytes for the data.&n;   */
r_int
id|i
suffix:semicolon
id|status_ptr
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef SOUND_UNAME_A
id|put_status
(paren
l_string|&quot;Sound Driver:&quot;
id|SOUND_VERSION_STRING
l_string|&quot; (&quot;
id|SOUND_CONFIG_DATE
l_string|&quot; &quot;
id|SOUND_CONFIG_BY
l_string|&quot;,&bslash;n&quot;
id|SOUND_UNAME_A
l_string|&quot;)&quot;
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
id|put_status
(paren
l_string|&quot;Sound Driver:&quot;
id|SOUND_VERSION_STRING
l_string|&quot; (&quot;
id|SOUND_CONFIG_DATE
l_string|&quot; &quot;
id|SOUND_CONFIG_BY
l_string|&quot;@&quot;
id|SOUND_CONFIG_HOST
l_string|&quot;.&quot;
id|SOUND_CONFIG_DOMAIN
l_string|&quot;)&quot;
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;Config options: &quot;
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status_int
(paren
id|SELECTED_SOUND_OPTIONS
comma
l_int|16
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;&bslash;n&bslash;nInstalled drivers: &bslash;n&quot;
)paren
)paren
r_return
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
id|num_sound_drivers
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|sound_drivers
(braket
id|i
)braket
dot
id|card_type
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;Type &quot;
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status_int
(paren
id|sound_drivers
(braket
id|i
)braket
dot
id|card_type
comma
l_int|10
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;: &quot;
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
id|sound_drivers
(braket
id|i
)braket
dot
id|name
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;&bslash;n&quot;
)paren
)paren
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;&bslash;n&bslash;nCard config: &bslash;n&quot;
)paren
)paren
r_return
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
id|num_sound_cards
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|snd_installed_cards
(braket
id|i
)braket
dot
id|card_type
op_ne
l_int|0
)paren
(brace
r_int
id|drv
comma
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|snd_installed_cards
(braket
id|i
)braket
dot
id|enabled
)paren
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;(&quot;
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * if (!put_status_int(snd_installed_cards[i].card_type, 10)) return;&n;&t; * if (!put_status (&quot;: &quot;)) return;&n;&t; */
r_if
c_cond
(paren
(paren
id|drv
op_assign
id|snd_find_driver
(paren
id|snd_installed_cards
(braket
id|i
)braket
dot
id|card_type
)paren
)paren
op_ne
op_minus
l_int|1
)paren
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
id|sound_drivers
(braket
id|drv
)braket
dot
id|name
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot; at 0x&quot;
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status_int
(paren
id|snd_installed_cards
(braket
id|i
)braket
dot
id|config.io_base
comma
l_int|16
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot; irq &quot;
)paren
)paren
r_return
suffix:semicolon
id|tmp
op_assign
id|snd_installed_cards
(braket
id|i
)braket
dot
id|config.irq
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OL
l_int|0
)paren
id|tmp
op_assign
op_minus
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status_int
(paren
id|tmp
comma
l_int|10
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|snd_installed_cards
(braket
id|i
)braket
dot
id|config.dma
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot; drq &quot;
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status_int
(paren
id|snd_installed_cards
(braket
id|i
)braket
dot
id|config.dma
comma
l_int|10
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|snd_installed_cards
(braket
id|i
)braket
dot
id|config.dma2
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;,&quot;
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status_int
(paren
id|snd_installed_cards
(braket
id|i
)braket
dot
id|config.dma2
comma
l_int|10
)paren
)paren
r_return
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|snd_installed_cards
(braket
id|i
)braket
dot
id|enabled
)paren
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;)&quot;
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;&bslash;n&quot;
)paren
)paren
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sound_started
)paren
(brace
id|put_status
(paren
l_string|&quot;&bslash;n&bslash;n***** Sound driver not started *****&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_AUDIO
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;&bslash;nAudio devices: NOT ENABLED IN CONFIG&bslash;n&quot;
)paren
)paren
r_return
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;&bslash;nAudio devices:&bslash;n&quot;
)paren
)paren
r_return
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
id|num_audiodevs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|put_status_int
(paren
id|i
comma
l_int|10
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;: &quot;
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
id|audio_devs
(braket
id|i
)braket
op_member_access_from_pointer
id|name
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|audio_devs
(braket
id|i
)braket
op_member_access_from_pointer
id|flags
op_amp
id|DMA_DUPLEX
)paren
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot; (DUPLEX)&quot;
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;&bslash;n&quot;
)paren
)paren
r_return
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef CONFIG_SEQUENCER
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;&bslash;nSynth devices: NOT ENABLED IN CONFIG&bslash;n&quot;
)paren
)paren
r_return
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;&bslash;nSynth devices:&bslash;n&quot;
)paren
)paren
r_return
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
id|num_synths
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|put_status_int
(paren
id|i
comma
l_int|10
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;: &quot;
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
id|synth_devs
(braket
id|i
)braket
op_member_access_from_pointer
id|info-&gt;name
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;&bslash;n&quot;
)paren
)paren
r_return
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef CONFIG_MIDI
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;&bslash;nMidi devices: NOT ENABLED IN CONFIG&bslash;n&quot;
)paren
)paren
r_return
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;&bslash;nMidi devices:&bslash;n&quot;
)paren
)paren
r_return
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
id|num_midis
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|put_status_int
(paren
id|i
comma
l_int|10
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;: &quot;
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
id|midi_devs
(braket
id|i
)braket
op_member_access_from_pointer
id|info.name
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;&bslash;n&quot;
)paren
)paren
r_return
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;&bslash;nTimers:&bslash;n&quot;
)paren
)paren
r_return
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
id|num_sound_timers
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|put_status_int
(paren
id|i
comma
l_int|10
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;: &quot;
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
id|sound_timer_devs
(braket
id|i
)braket
op_member_access_from_pointer
id|info.name
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;&bslash;n&quot;
)paren
)paren
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;&bslash;nMixers:&bslash;n&quot;
)paren
)paren
r_return
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
id|num_mixers
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|put_status_int
(paren
id|i
comma
l_int|10
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;: &quot;
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
id|mixer_devs
(braket
id|i
)braket
op_member_access_from_pointer
id|name
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|put_status
(paren
l_string|&quot;&bslash;n&quot;
)paren
)paren
r_return
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|read_status
id|read_status
(paren
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
multiline_comment|/*&n;   * Return at most &squot;count&squot; bytes from the status_buf.&n;   */
r_int
id|l
comma
id|c
suffix:semicolon
id|l
op_assign
id|count
suffix:semicolon
id|c
op_assign
id|status_len
op_minus
id|status_ptr
suffix:semicolon
r_if
c_cond
(paren
id|l
OG
id|c
)paren
id|l
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
id|l
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|memcpy_tofs
(paren
op_amp
(paren
(paren
id|buf
)paren
(braket
l_int|0
)braket
)paren
comma
op_amp
id|status_buf
(braket
id|status_ptr
)braket
comma
id|l
)paren
suffix:semicolon
id|status_ptr
op_add_assign
id|l
suffix:semicolon
r_return
id|l
suffix:semicolon
)brace
r_int
DECL|function|sound_read_sw
id|sound_read_sw
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
id|DEB
(paren
id|printk
(paren
l_string|&quot;sound_read_sw(dev=%d, count=%d)&bslash;n&quot;
comma
id|dev
comma
id|count
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|dev
op_amp
l_int|0x0f
)paren
(brace
r_case
id|SND_DEV_STATUS
suffix:colon
r_return
id|read_status
(paren
id|buf
comma
id|count
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_AUDIO
r_case
id|SND_DEV_DSP
suffix:colon
r_case
id|SND_DEV_DSP16
suffix:colon
r_case
id|SND_DEV_AUDIO
suffix:colon
r_return
id|audio_read
(paren
id|dev
comma
id|file
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SEQUENCER
r_case
id|SND_DEV_SEQ
suffix:colon
r_case
id|SND_DEV_SEQ2
suffix:colon
r_return
id|sequencer_read
(paren
id|dev
comma
id|file
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIDI
r_case
id|SND_DEV_MIDIN
suffix:colon
r_return
id|MIDIbuf_read
(paren
id|dev
comma
id|file
comma
id|buf
comma
id|count
)paren
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|printk
(paren
l_string|&quot;Sound: Undefined minor device %d&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_int
DECL|function|sound_write_sw
id|sound_write_sw
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
id|DEB
(paren
id|printk
(paren
l_string|&quot;sound_write_sw(dev=%d, count=%d)&bslash;n&quot;
comma
id|dev
comma
id|count
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|dev
op_amp
l_int|0x0f
)paren
(brace
macro_line|#ifdef CONFIG_SEQUENCER
r_case
id|SND_DEV_SEQ
suffix:colon
r_case
id|SND_DEV_SEQ2
suffix:colon
r_return
id|sequencer_write
(paren
id|dev
comma
id|file
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_AUDIO
r_case
id|SND_DEV_DSP
suffix:colon
r_case
id|SND_DEV_DSP16
suffix:colon
r_case
id|SND_DEV_AUDIO
suffix:colon
r_return
id|audio_write
(paren
id|dev
comma
id|file
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIDI
r_case
id|SND_DEV_MIDIN
suffix:colon
r_return
id|MIDIbuf_write
(paren
id|dev
comma
id|file
comma
id|buf
comma
id|count
)paren
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
r_int
DECL|function|sound_open_sw
id|sound_open_sw
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
)paren
(brace
r_int
id|retval
suffix:semicolon
id|DEB
(paren
id|printk
(paren
l_string|&quot;sound_open_sw(dev=%d)&bslash;n&quot;
comma
id|dev
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev
op_ge
id|SND_NDEVS
)paren
op_logical_or
(paren
id|dev
OL
l_int|0
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;Invalid minor device %d&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|dev
op_amp
l_int|0x0f
)paren
(brace
r_case
id|SND_DEV_STATUS
suffix:colon
r_if
c_cond
(paren
id|status_busy
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|status_busy
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status_buf
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
(paren
l_int|4000
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|status_len
op_assign
id|status_ptr
op_assign
l_int|0
suffix:semicolon
id|init_status
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SND_DEV_CTL
suffix:colon
r_return
l_int|0
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_SEQUENCER
r_case
id|SND_DEV_SEQ
suffix:colon
r_case
id|SND_DEV_SEQ2
suffix:colon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|sequencer_open
(paren
id|dev
comma
id|file
)paren
)paren
OL
l_int|0
)paren
r_return
id|retval
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIDI
r_case
id|SND_DEV_MIDIN
suffix:colon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|MIDIbuf_open
(paren
id|dev
comma
id|file
)paren
)paren
OL
l_int|0
)paren
r_return
id|retval
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_AUDIO
r_case
id|SND_DEV_DSP
suffix:colon
r_case
id|SND_DEV_DSP16
suffix:colon
r_case
id|SND_DEV_AUDIO
suffix:colon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|audio_open
(paren
id|dev
comma
id|file
)paren
)paren
OL
l_int|0
)paren
r_return
id|retval
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|printk
(paren
l_string|&quot;Invalid minor device %d&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|in_use
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|sound_release_sw
id|sound_release_sw
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
)paren
(brace
id|DEB
(paren
id|printk
(paren
l_string|&quot;sound_release_sw(dev=%d)&bslash;n&quot;
comma
id|dev
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|dev
op_amp
l_int|0x0f
)paren
(brace
r_case
id|SND_DEV_STATUS
suffix:colon
r_if
c_cond
(paren
id|status_buf
)paren
id|kfree
(paren
id|status_buf
)paren
suffix:semicolon
id|status_buf
op_assign
l_int|NULL
suffix:semicolon
id|status_busy
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SND_DEV_CTL
suffix:colon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_SEQUENCER
r_case
id|SND_DEV_SEQ
suffix:colon
r_case
id|SND_DEV_SEQ2
suffix:colon
id|sequencer_release
(paren
id|dev
comma
id|file
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIDI
r_case
id|SND_DEV_MIDIN
suffix:colon
id|MIDIbuf_release
(paren
id|dev
comma
id|file
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_AUDIO
r_case
id|SND_DEV_DSP
suffix:colon
r_case
id|SND_DEV_DSP16
suffix:colon
r_case
id|SND_DEV_AUDIO
suffix:colon
id|audio_release
(paren
id|dev
comma
id|file
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|printk
(paren
l_string|&quot;Sound error: Releasing unknown device 0x%02x&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
)brace
id|in_use
op_decrement
suffix:semicolon
)brace
r_int
DECL|function|sound_ioctl_sw
id|sound_ioctl_sw
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
r_int
r_int
id|cmd
comma
id|caddr_t
id|arg
)paren
(brace
id|DEB
(paren
id|printk
(paren
l_string|&quot;sound_ioctl_sw(dev=%d, cmd=0x%x, arg=0x%x)&bslash;n&quot;
comma
id|dev
comma
id|cmd
comma
id|arg
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|cmd
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
op_eq
l_char|&squot;M&squot;
op_logical_and
id|num_mixers
OG
l_int|0
)paren
multiline_comment|/* Mixer ioctl */
r_if
c_cond
(paren
(paren
id|dev
op_amp
l_int|0x0f
)paren
op_ne
id|SND_DEV_CTL
)paren
(brace
r_int
id|dtype
op_assign
id|dev
op_amp
l_int|0x0f
suffix:semicolon
r_int
id|mixdev
suffix:semicolon
r_switch
c_cond
(paren
id|dtype
)paren
(brace
macro_line|#ifdef CONFIG_AUDIO
r_case
id|SND_DEV_DSP
suffix:colon
r_case
id|SND_DEV_DSP16
suffix:colon
r_case
id|SND_DEV_AUDIO
suffix:colon
id|mixdev
op_assign
id|audio_devs
(braket
id|dev
op_rshift
l_int|4
)braket
op_member_access_from_pointer
id|mixer_dev
suffix:semicolon
r_if
c_cond
(paren
id|mixdev
OL
l_int|0
op_logical_or
id|mixdev
op_ge
id|num_mixers
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_return
id|mixer_devs
(braket
id|mixdev
)braket
op_member_access_from_pointer
id|ioctl
(paren
id|mixdev
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_return
id|mixer_devs
(braket
l_int|0
)braket
op_member_access_from_pointer
id|ioctl
(paren
l_int|0
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
)brace
)brace
r_switch
c_cond
(paren
id|dev
op_amp
l_int|0x0f
)paren
(brace
r_case
id|SND_DEV_CTL
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|num_mixers
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|dev
op_assign
id|dev
op_rshift
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_ge
id|num_mixers
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_return
id|mixer_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|ioctl
(paren
id|dev
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_SEQUENCER
r_case
id|SND_DEV_SEQ
suffix:colon
r_case
id|SND_DEV_SEQ2
suffix:colon
r_return
id|sequencer_ioctl
(paren
id|dev
comma
id|file
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_AUDIO
r_case
id|SND_DEV_DSP
suffix:colon
r_case
id|SND_DEV_DSP16
suffix:colon
r_case
id|SND_DEV_AUDIO
suffix:colon
r_return
id|audio_ioctl
(paren
id|dev
comma
id|file
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIDI
r_case
id|SND_DEV_MIDIN
suffix:colon
r_return
id|MIDIbuf_ioctl
(paren
id|dev
comma
id|file
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_return
op_minus
id|EPERM
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
eof
