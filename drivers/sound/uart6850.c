multiline_comment|/*&n; * sound/uart6850.c&n; *&n; * Copyright by Hannu Savolainen 1993&n; *&n; * Mon Nov 22 22:38:35 MET 1993 marco@driq.home.usn.nl:&n; *      added 6850 support, used with COVOX SoundMaster II and custom cards.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions are&n; * met: 1. Redistributions of source code must retain the above copyright&n; * notice, this list of conditions and the following disclaimer. 2.&n; * Redistributions in binary form must reproduce the above copyright notice,&n; * this list of conditions and the following disclaimer in the documentation&n; * and/or other materials provided with the distribution.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND ANY&n; * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED&n; * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR&n; * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER&n; * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; */
macro_line|#include &quot;sound_config.h&quot;
macro_line|#ifdef CONFIGURE_SOUNDCARD
macro_line|#if !defined(EXCLUDE_UART6850) &amp;&amp; !defined(EXCLUDE_MIDI)
DECL|macro|DATAPORT
mdefine_line|#define&t;DATAPORT   (uart6850_base)&t;/*&n;&t;&t;&t;&t;&t;   * * * Midi6850 Data I/O Port on IBM&n;&t;&t;&t;&t;&t;   *  */
DECL|macro|COMDPORT
mdefine_line|#define&t;COMDPORT   (uart6850_base+1)&t;/*&n;&t;&t;&t;&t;&t;   * * * Midi6850 Command Port on IBM   */
DECL|macro|STATPORT
mdefine_line|#define&t;STATPORT   (uart6850_base+1)&t;/*&n;&t;&t;&t;&t;&t;   * * * Midi6850 Status Port on IBM   */
DECL|macro|uart6850_status
mdefine_line|#define uart6850_status()&t;&t;INB(STATPORT)
DECL|macro|input_avail
mdefine_line|#define input_avail()&t;&t;((uart6850_status()&amp;INPUT_AVAIL))
DECL|macro|output_ready
mdefine_line|#define output_ready()&t;&t;((uart6850_status()&amp;OUTPUT_READY))
DECL|macro|uart6850_cmd
mdefine_line|#define uart6850_cmd(cmd)&t;OUTB(cmd, COMDPORT)
DECL|macro|uart6850_read
mdefine_line|#define uart6850_read()&t;&t;INB(DATAPORT)
DECL|macro|uart6850_write
mdefine_line|#define uart6850_write(byte)&t;OUTB(byte, DATAPORT)
DECL|macro|OUTPUT_READY
mdefine_line|#define&t;OUTPUT_READY&t;0x02&t;/*&n;&t;&t;&t;&t;   * * * Mask for Data Read Ready Bit   */
DECL|macro|INPUT_AVAIL
mdefine_line|#define&t;INPUT_AVAIL&t;0x01&t;/*&n;&t;&t;&t;&t;   * * * Mask for Data Send Ready Bit   */
DECL|macro|UART_RESET
mdefine_line|#define&t;UART_RESET&t;0x95&t;/*&n;&t;&t;&t;&t;   * * * 6850 Total Reset Command   */
DECL|macro|UART_MODE_ON
mdefine_line|#define&t;UART_MODE_ON&t;0x03&t;/*&n;&t;&t;&t;&t;   * * * 6850 Send/Receive UART Mode   */
DECL|variable|uart6850_opened
r_static
r_int
id|uart6850_opened
op_assign
l_int|0
suffix:semicolon
DECL|variable|uart6850_base
r_static
r_int
id|uart6850_base
op_assign
l_int|0x330
suffix:semicolon
DECL|variable|uart6850_irq
r_static
r_int
id|uart6850_irq
suffix:semicolon
DECL|variable|uart6850_detected
r_static
r_int
id|uart6850_detected
op_assign
l_int|0
suffix:semicolon
DECL|variable|my_dev
r_static
r_int
id|my_dev
suffix:semicolon
r_static
r_int
id|reset_uart6850
(paren
r_void
)paren
suffix:semicolon
DECL|variable|midi_input_intr
r_static
r_void
(paren
op_star
id|midi_input_intr
)paren
(paren
r_int
id|dev
comma
r_int
r_char
id|data
)paren
suffix:semicolon
r_static
r_void
DECL|function|uart6850_input_loop
id|uart6850_input_loop
(paren
r_void
)paren
(brace
r_int
id|count
suffix:semicolon
id|count
op_assign
l_int|10
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
multiline_comment|/*&n;&t;&t;&t;&t; * Not timed out&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|input_avail
(paren
)paren
)paren
(brace
r_int
r_char
id|c
op_assign
id|uart6850_read
(paren
)paren
suffix:semicolon
id|count
op_assign
l_int|100
suffix:semicolon
r_if
c_cond
(paren
id|uart6850_opened
op_amp
id|OPEN_READ
)paren
id|midi_input_intr
(paren
id|my_dev
comma
id|c
)paren
suffix:semicolon
)brace
r_else
r_while
c_loop
(paren
op_logical_neg
id|input_avail
(paren
)paren
op_logical_and
id|count
)paren
id|count
op_decrement
suffix:semicolon
)brace
r_void
DECL|function|m6850intr
id|m6850intr
(paren
r_int
id|unit
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
(paren
l_string|&quot;M&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|input_avail
(paren
)paren
)paren
id|uart6850_input_loop
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * It looks like there is no input interrupts in the UART mode. Let&squot;s try&n; * polling.&n; */
r_static
r_void
DECL|function|poll_uart6850
id|poll_uart6850
(paren
r_int
r_int
id|dummy
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|DEFINE_TIMER
(paren
id|uart6850_timer
comma
id|poll_uart6850
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|uart6850_opened
op_amp
id|OPEN_READ
)paren
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * No longer required&n;&t;&t;&t;&t; */
id|DISABLE_INTR
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|input_avail
(paren
)paren
)paren
id|uart6850_input_loop
(paren
)paren
suffix:semicolon
id|ACTIVATE_TIMER
(paren
id|uart6850_timer
comma
id|poll_uart6850
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t;&t; * Come back later&n;&t;&t;&t;&t;&t;&t;&t; */
id|RESTORE_INTR
(paren
id|flags
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|uart6850_open
id|uart6850_open
(paren
r_int
id|dev
comma
r_int
id|mode
comma
r_void
(paren
op_star
id|input
)paren
(paren
r_int
id|dev
comma
r_int
r_char
id|data
)paren
comma
r_void
(paren
op_star
id|output
)paren
(paren
r_int
id|dev
)paren
)paren
(brace
r_if
c_cond
(paren
id|uart6850_opened
)paren
(brace
id|printk
(paren
l_string|&quot;Midi6850: Midi busy&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|RET_ERROR
(paren
id|EBUSY
)paren
suffix:semicolon
)brace
id|uart6850_cmd
(paren
id|UART_RESET
)paren
suffix:semicolon
id|uart6850_input_loop
(paren
)paren
suffix:semicolon
id|midi_input_intr
op_assign
id|input
suffix:semicolon
id|uart6850_opened
op_assign
id|mode
suffix:semicolon
id|poll_uart6850
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * Enable input polling&n;&t;&t;&t;&t; */
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|uart6850_close
id|uart6850_close
(paren
r_int
id|dev
)paren
(brace
id|uart6850_cmd
(paren
id|UART_MODE_ON
)paren
suffix:semicolon
id|uart6850_opened
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|uart6850_out
id|uart6850_out
(paren
r_int
id|dev
comma
r_int
r_char
id|midi_byte
)paren
(brace
r_int
id|timeout
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n;   * Test for input since pending input seems to block the output.&n;   */
id|DISABLE_INTR
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|input_avail
(paren
)paren
)paren
id|uart6850_input_loop
(paren
)paren
suffix:semicolon
id|RESTORE_INTR
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;   * Sometimes it takes about 13000 loops before the output becomes ready&n;   * (After reset). Normally it takes just about 10 loops.&n;   */
r_for
c_loop
(paren
id|timeout
op_assign
l_int|30000
suffix:semicolon
id|timeout
OG
l_int|0
op_logical_and
op_logical_neg
id|output_ready
(paren
)paren
suffix:semicolon
id|timeout
op_decrement
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t;&t;&t;&t; * Wait&n;&t;&t;&t;&t;&t;&t;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|output_ready
(paren
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;Midi6850: Timeout&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|uart6850_write
(paren
id|midi_byte
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|uart6850_command
id|uart6850_command
(paren
r_int
id|dev
comma
r_int
r_char
op_star
id|midi_byte
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|uart6850_start_read
id|uart6850_start_read
(paren
r_int
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|uart6850_end_read
id|uart6850_end_read
(paren
r_int
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|uart6850_ioctl
id|uart6850_ioctl
(paren
r_int
id|dev
comma
r_int
id|cmd
comma
r_int
id|arg
)paren
(brace
r_return
id|RET_ERROR
(paren
id|EINVAL
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|uart6850_kick
id|uart6850_kick
(paren
r_int
id|dev
)paren
(brace
)brace
r_static
r_int
DECL|function|uart6850_buffer_status
id|uart6850_buffer_status
(paren
r_int
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * No data in buffers&n;&t;&t;&t;&t; */
)brace
DECL|macro|MIDI_SYNTH_NAME
mdefine_line|#define MIDI_SYNTH_NAME&t;&quot;6850 UART Midi&quot;
DECL|macro|MIDI_SYNTH_CAPS
mdefine_line|#define MIDI_SYNTH_CAPS&t;SYNTH_CAP_INPUT
macro_line|#include &quot;midi_synth.h&quot;
DECL|variable|uart6850_operations
r_static
r_struct
id|midi_operations
id|uart6850_operations
op_assign
(brace
(brace
l_string|&quot;6850 UART&quot;
comma
l_int|0
comma
l_int|0
comma
id|SNDCARD_UART6850
)brace
comma
op_amp
id|std_midi_synth
comma
id|uart6850_open
comma
id|uart6850_close
comma
id|uart6850_ioctl
comma
id|uart6850_out
comma
id|uart6850_start_read
comma
id|uart6850_end_read
comma
id|uart6850_kick
comma
id|uart6850_command
comma
id|uart6850_buffer_status
)brace
suffix:semicolon
r_int
DECL|function|attach_uart6850
id|attach_uart6850
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
id|ok
comma
id|timeout
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|num_midis
op_ge
id|MAX_MIDI_DEV
)paren
(brace
id|printk
(paren
l_string|&quot;Sound: Too many midi devices detected&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|mem_start
suffix:semicolon
)brace
id|uart6850_base
op_assign
id|hw_config-&gt;io_base
suffix:semicolon
id|uart6850_irq
op_assign
id|hw_config-&gt;irq
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uart6850_detected
)paren
r_return
id|RET_ERROR
(paren
id|EIO
)paren
suffix:semicolon
id|DISABLE_INTR
(paren
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|timeout
op_assign
l_int|30000
suffix:semicolon
id|timeout
OL
l_int|0
op_logical_and
op_logical_neg
id|output_ready
(paren
)paren
suffix:semicolon
id|timeout
op_decrement
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t;&t;&t;&t; * Wait&n;&t;&t;&t;&t;&t;&t;&t;&t;&t; */
id|uart6850_cmd
(paren
id|UART_MODE_ON
)paren
suffix:semicolon
id|ok
op_assign
l_int|1
suffix:semicolon
id|RESTORE_INTR
(paren
id|flags
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot; &lt;6850 Midi Interface&gt;&quot;
)paren
suffix:semicolon
id|std_midi_synth.midi_dev
op_assign
id|my_dev
op_assign
id|num_midis
suffix:semicolon
id|midi_devs
(braket
id|num_midis
op_increment
)braket
op_assign
op_amp
id|uart6850_operations
suffix:semicolon
r_return
id|mem_start
suffix:semicolon
)brace
r_static
r_int
DECL|function|reset_uart6850
id|reset_uart6850
(paren
r_void
)paren
(brace
id|uart6850_read
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * OK&n;&t;&t;&t;&t; */
)brace
r_int
DECL|function|probe_uart6850
id|probe_uart6850
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
id|ok
op_assign
l_int|0
suffix:semicolon
id|uart6850_base
op_assign
id|hw_config-&gt;io_base
suffix:semicolon
id|uart6850_irq
op_assign
id|hw_config-&gt;irq
suffix:semicolon
r_if
c_cond
(paren
id|snd_set_irq_handler
(paren
id|uart6850_irq
comma
id|m6850intr
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|ok
op_assign
id|reset_uart6850
(paren
)paren
suffix:semicolon
id|uart6850_detected
op_assign
id|ok
suffix:semicolon
r_return
id|ok
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
