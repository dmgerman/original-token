multiline_comment|/* radiotrack (radioreveal) driver for Linux radio support&n; * (c) 1997 M. Kirkwood&n; */
multiline_comment|/* TODO: Allow for more than one of these foolish entities :-) */
multiline_comment|/* Notes on the hardware (reverse engineered from other peoples&squot;&n; * reverse engineering of AIMS&squot; code :-)&n; *&n; *  Frequency control is done digitally -- ie out(port,encodefreq(95.8));&n; *&n; *  The signal strength query is unsurprisingly inaccurate.  And it seems&n; *  to indicate that (on my card, at least) the frequency setting isn&squot;t&n; *  too great.  (I have to tune up .025MHz from what the freq should be&n; *  to get a report that the thing is tuned.)&n; *&n; *  Volume control is (ugh) analogue:&n; *   out(port, start_increasing_volume);&n; *   wait(a_wee_while);&n; *   out(port, stop_changing_the_volume);&n; *  &n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/radio.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;rtrack.h&quot;
multiline_comment|/* Let&squot;s just be a bit careful here, shall we? */
macro_line|#if (CONFIG_RADIO_RTRACK_PORT != 0x20f) &amp;&amp; (CONFIG_RADIO_RTRACK_PORT != 0x30f)
macro_line|#error Invalid port specified for RadioTrack
macro_line|#endif
multiline_comment|/* local prototypes */
r_void
id|outbits
c_func
(paren
r_int
id|bits
comma
r_int
id|data
comma
r_int
id|port
)paren
suffix:semicolon
r_void
id|decvol
c_func
(paren
r_int
id|port
)paren
suffix:semicolon
r_void
id|incvol
c_func
(paren
r_int
id|port
)paren
suffix:semicolon
r_void
id|mute
c_func
(paren
r_int
id|port
)paren
suffix:semicolon
r_void
id|unmute
c_func
(paren
r_int
id|port
)paren
suffix:semicolon
multiline_comment|/* public structurey-type things */
DECL|variable|rt_port
r_int
id|rt_port
op_assign
id|CONFIG_RADIO_RTRACK_PORT
suffix:semicolon
DECL|variable|rt_cap
r_struct
id|radio_cap
id|rt_cap
op_assign
(brace
l_int|0
comma
multiline_comment|/* device index (not dealt with here) */
id|RADIO_TYPE_RTRACK
comma
multiline_comment|/* type */
l_int|1
comma
multiline_comment|/* number of bandwidths */
l_int|0
comma
l_int|10
multiline_comment|/* volmin, volmax */
)brace
suffix:semicolon
multiline_comment|/* we only get one band/protocol with radiotrack */
DECL|variable|rt_band
r_struct
id|radio_band
id|rt_band
op_assign
(brace
l_int|0
comma
multiline_comment|/* device index */
l_int|0
comma
multiline_comment|/* bandwidth &quot;index&quot; */
id|RADIO_PROTOCOL_FM
comma
id|RADIO_BAND_FM_STD
comma
id|RADIO_FM_FRTOINT
c_func
(paren
l_float|88.0
)paren
comma
multiline_comment|/* freq range */
id|RADIO_FM_FRTOINT
c_func
(paren
l_float|108.0
)paren
comma
l_int|0
comma
l_int|1
multiline_comment|/* sig strength range */
)brace
suffix:semicolon
multiline_comment|/* p&squot;raps these should become struct radio_ops and struct radio_status? */
DECL|variable|rt_dev
r_struct
id|radio_device
id|rt_dev
op_assign
(brace
op_amp
id|rt_cap
comma
op_amp
id|rt_band
comma
op_amp
id|rt_setvol
comma
l_int|0
comma
multiline_comment|/* curvol */
op_amp
id|rt_setband
comma
l_int|0
comma
multiline_comment|/* curband */
op_amp
id|rt_setfreq
comma
l_int|0
comma
multiline_comment|/* curfreq */
op_amp
id|rt_getsigstr
comma
l_int|NULL
comma
multiline_comment|/* next (to be filled in later) */
op_amp
id|rt_port
multiline_comment|/* misc */
)brace
suffix:semicolon
DECL|function|radiotrack_init
r_void
id|radiotrack_init
c_func
(paren
)paren
(brace
r_int
id|dev_num
comma
id|i
suffix:semicolon
multiline_comment|/* XXX - probe here?? - XXX */
multiline_comment|/* try to grab the i/o port */
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|rt_port
comma
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;rtrack.c: port 0x%x already used&bslash;n&quot;
comma
id|rt_port
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|request_region
c_func
(paren
id|rt_port
comma
l_int|2
comma
l_string|&quot;rtrack&quot;
)paren
suffix:semicolon
id|dev_num
op_assign
id|radio_add_device
c_func
(paren
op_amp
id|rt_dev
)paren
suffix:semicolon
multiline_comment|/* initialise the card */
multiline_comment|/* set the volume very low */
r_for
c_loop
(paren
id|i
op_assign
id|rt_cap.volmax
suffix:semicolon
id|i
OG
id|rt_cap.volmin
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|decvol
c_func
(paren
id|rt_port
)paren
suffix:semicolon
)brace
id|rt_dev.curvol
op_assign
id|rt_cap.volmin
suffix:semicolon
)brace
DECL|function|rt_setvol
r_int
id|rt_setvol
c_func
(paren
r_struct
id|radio_device
op_star
id|dev
comma
r_int
id|vol
)paren
(brace
r_int
id|port
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
id|vol
op_eq
id|dev-&gt;curvol
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|port
op_assign
op_star
(paren
r_int
op_star
)paren
(paren
id|dev-&gt;misc
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vol
op_eq
l_int|0
)paren
(brace
id|mute
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vol
OG
id|dev-&gt;curvol
)paren
r_for
c_loop
(paren
id|i
op_assign
id|dev-&gt;curvol
suffix:semicolon
id|i
OL
id|vol
suffix:semicolon
id|i
op_increment
)paren
(brace
id|incvol
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_else
r_for
c_loop
(paren
id|i
op_assign
id|dev-&gt;curvol
suffix:semicolon
id|i
OG
id|vol
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|decvol
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;curvol
op_eq
l_int|0
)paren
(brace
id|unmute
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rt_setband
r_int
id|rt_setband
c_func
(paren
r_struct
id|radio_device
op_star
id|dev
comma
r_int
id|band
)paren
(brace
multiline_comment|/* we know in advance that we only have one band, and&n; * the wrapper checks the validity of all the inputs&n; */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rt_setfreq
r_int
id|rt_setfreq
c_func
(paren
r_struct
id|radio_device
op_star
id|dev
comma
r_int
id|freq
)paren
(brace
r_int
id|myport
op_assign
op_star
(paren
r_int
op_star
)paren
(paren
id|dev-&gt;misc
)paren
suffix:semicolon
id|outbits
c_func
(paren
l_int|16
comma
id|RTRACK_ENCODE
c_func
(paren
id|freq
)paren
comma
id|myport
)paren
suffix:semicolon
id|outbits
c_func
(paren
l_int|8
comma
l_int|0xa0
comma
id|myport
)paren
suffix:semicolon
multiline_comment|/* XXX - get rid of this once setvol is implemented properly - XXX */
multiline_comment|/* these insist on turning the thing on.  not sure I approve... */
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|myport
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xc8
comma
id|myport
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rt_getsigstr
r_int
id|rt_getsigstr
c_func
(paren
r_struct
id|radio_device
op_star
id|dev
)paren
(brace
r_int
id|res
suffix:semicolon
r_int
id|myport
op_assign
op_star
(paren
r_int
op_star
)paren
(paren
id|dev-&gt;misc
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xf8
comma
id|myport
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
id|res
op_assign
(paren
r_int
)paren
id|inb
c_func
(paren
id|myport
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xe8
comma
id|myport
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
op_eq
l_int|0xfd
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* local things */
DECL|function|outbits
r_void
id|outbits
c_func
(paren
r_int
id|bits
comma
r_int
id|data
comma
r_int
id|port
)paren
(brace
r_while
c_loop
(paren
id|bits
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|data
op_amp
l_int|1
)paren
(brace
id|outw
c_func
(paren
l_int|5
comma
id|port
)paren
suffix:semicolon
id|outw
c_func
(paren
l_int|5
comma
id|port
)paren
suffix:semicolon
id|outw
c_func
(paren
l_int|7
comma
id|port
)paren
suffix:semicolon
id|outw
c_func
(paren
l_int|7
comma
id|port
)paren
suffix:semicolon
)brace
r_else
(brace
id|outw
c_func
(paren
l_int|1
comma
id|port
)paren
suffix:semicolon
id|outw
c_func
(paren
l_int|1
comma
id|port
)paren
suffix:semicolon
id|outw
c_func
(paren
l_int|3
comma
id|port
)paren
suffix:semicolon
id|outw
c_func
(paren
l_int|3
comma
id|port
)paren
suffix:semicolon
)brace
id|data
op_rshift_assign
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|decvol
r_void
id|decvol
c_func
(paren
r_int
id|port
)paren
(brace
id|outb
c_func
(paren
l_int|0x48
comma
id|port
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xc8
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|incvol
r_void
id|incvol
c_func
(paren
r_int
id|port
)paren
(brace
id|outb
c_func
(paren
l_int|0x88
comma
id|port
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xc8
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|mute
r_void
id|mute
c_func
(paren
r_int
id|port
)paren
(brace
id|outb
c_func
(paren
l_int|0
comma
id|port
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xc0
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|unmute
r_void
id|unmute
c_func
(paren
r_int
id|port
)paren
(brace
id|outb
c_func
(paren
l_int|0
comma
id|port
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xc8
comma
id|port
)paren
suffix:semicolon
)brace
eof
