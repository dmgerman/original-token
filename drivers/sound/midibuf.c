multiline_comment|/*&n; * sound/midibuf.c&n; *&n; * Device file manager for /dev/midi&n; *&n; * NOTE! This part of the driver is currently just a stub.&n; *&n; * Copyright by Hannu Savolainen 1993&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions are&n; * met: 1. Redistributions of source code must retain the above copyright&n; * notice, this list of conditions and the following disclaimer. 2.&n; * Redistributions in binary form must reproduce the above copyright notice,&n; * this list of conditions and the following disclaimer in the documentation&n; * and/or other materials provided with the distribution.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND ANY&n; * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED&n; * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR&n; * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER&n; * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; *&n; */
macro_line|#include &quot;sound_config.h&quot;
macro_line|#if defined(CONFIGURE_SOUNDCARD) &amp;&amp; !defined(EXCLUDE_MPU401)
macro_line|#if 0
macro_line|#include &quot;midiioctl.h&quot;
macro_line|#include &quot;midivar.h&quot;
macro_line|#endif
DECL|variable|midibuf_busy
r_static
r_int
id|midibuf_busy
op_assign
l_int|0
suffix:semicolon
r_int
DECL|function|MIDIbuf_open
id|MIDIbuf_open
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
id|mode
comma
id|err
suffix:semicolon
id|dev
op_assign
id|dev
op_rshift
l_int|4
suffix:semicolon
id|mode
op_assign
id|file-&gt;mode
op_amp
id|O_ACCMODE
suffix:semicolon
r_if
c_cond
(paren
id|midibuf_busy
)paren
r_return
id|RET_ERROR
(paren
id|EBUSY
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mpu401_dev
)paren
(brace
id|printk
(paren
l_string|&quot;Midi: MPU-401 compatible Midi interface not present&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|RET_ERROR
(paren
id|ENXIO
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|midi_devs
(braket
id|mpu401_dev
)braket
op_member_access_from_pointer
id|open
(paren
id|mpu401_dev
comma
id|mode
comma
l_int|NULL
comma
l_int|NULL
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|midibuf_busy
op_assign
l_int|1
suffix:semicolon
r_return
id|RET_ERROR
(paren
id|ENXIO
)paren
suffix:semicolon
)brace
r_void
DECL|function|MIDIbuf_release
id|MIDIbuf_release
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
id|mode
suffix:semicolon
id|dev
op_assign
id|dev
op_rshift
l_int|4
suffix:semicolon
id|mode
op_assign
id|file-&gt;mode
op_amp
id|O_ACCMODE
suffix:semicolon
id|midi_devs
(braket
id|mpu401_dev
)braket
op_member_access_from_pointer
id|close
(paren
id|mpu401_dev
)paren
suffix:semicolon
id|midibuf_busy
op_assign
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|MIDIbuf_write
id|MIDIbuf_write
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
id|snd_rw_buf
op_star
id|buf
comma
r_int
id|count
)paren
(brace
id|dev
op_assign
id|dev
op_rshift
l_int|4
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_int
DECL|function|MIDIbuf_read
id|MIDIbuf_read
(paren
r_int
id|dev
comma
r_struct
id|fileinfo
op_star
id|file
comma
id|snd_rw_buf
op_star
id|buf
comma
r_int
id|count
)paren
(brace
id|dev
op_assign
id|dev
op_rshift
l_int|4
suffix:semicolon
r_return
id|RET_ERROR
(paren
id|EIO
)paren
suffix:semicolon
)brace
r_int
DECL|function|MIDIbuf_ioctl
id|MIDIbuf_ioctl
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
r_int
r_int
id|arg
)paren
(brace
id|dev
op_assign
id|dev
op_rshift
l_int|4
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_default
suffix:colon
r_return
id|midi_devs
(braket
l_int|0
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
)brace
)brace
r_void
DECL|function|MIDIbuf_bytes_received
id|MIDIbuf_bytes_received
(paren
r_int
id|dev
comma
r_int
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
)brace
r_int
DECL|function|MIDIbuf_init
id|MIDIbuf_init
(paren
r_int
id|mem_start
)paren
(brace
r_return
id|mem_start
suffix:semicolon
)brace
macro_line|#endif
eof
