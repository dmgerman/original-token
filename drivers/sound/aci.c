multiline_comment|/*&n; * Audio Command Interface (ACI) driver (sound/aci.c)&n; *&n; * ACI is a protocol used to communicate with the microcontroller on&n; * some sound cards produced by miro, e.g. the miroSOUND PCM12 and&n; * PCM20. The ACI has been developed for miro by Norberto Pellicci&n; * &lt;pellicci@home.com&gt;. Special thanks to both him and miro for&n; * providing the ACI specification.&n; *&n; * The main function of the ACI is to control the mixer and to get a&n; * product identification. On the PCM20, ACI also controls the radio&n; * tuner on this card, this is supported in the Video for Linux &n; * radio-miropcm20 driver.&n; * &n; * This Voxware ACI driver currently only supports the ACI functions&n; * on the miroSOUND PCM12 and PCM20 card. Support for miro sound cards &n; * with additional ACI functions can easily be added later.&n; *&n; * / NOTE / When compiling as a module, make sure to load the module &n; * after loading the mad16 module. The initialisation code expects the&n; * MAD16 default mixer to be already available.&n; *&n; * Revision history:&n; *&n; *   1995-11-10  Markus Kuhn &lt;mskuhn@cip.informatik.uni-erlangen.de&gt;&n; *        First version written.&n; *   1995-12-31  Markus Kuhn&n; *        Second revision, general code cleanup.&n; *   1996-05-16&t; Hannu Savolainen&n; *&t;  Integrated with other parts of the driver.&n; *   1996-05-28  Markus Kuhn&n; *        Initialize CS4231A mixer, make ACI first mixer,&n; *        use new private mixer API for solo mode.&n; *   1998-08-18  Ruurd Reitsma &lt;R.A.Reitsma@wbmt.tudelft.nl&gt;&n; *&t;  Small modification to export ACI functions and &n; *&t;  complete modularisation.&n; */
multiline_comment|/*&n; * Some driver specific information and features:&n; *&n; * This mixer driver identifies itself to applications as &quot;ACI&quot; in&n; * mixer_info.id as retrieved by ioctl(fd, SOUND_MIXER_INFO, &amp;mixer_info).&n; *&n; * Proprietary mixer features that go beyond the standard OSS mixer&n; * interface are:&n; * &n; * Full duplex solo configuration:&n; *&n; *   int solo_mode;&n; *   ioctl(fd, SOUND_MIXER_PRIVATE1, &amp;solo_mode);&n; *&n; *   solo_mode = 0: deactivate solo mode (default)&n; *   solo_mode &gt; 0: activate solo mode&n; *                  With activated solo mode, the PCM input can not any&n; *                  longer hear the signals produced by the PCM output.&n; *                  Activating solo mode is important in duplex mode in order&n; *                  to avoid feedback distortions.&n; *   solo_mode &lt; 0: do not change solo mode (just retrieve the status)&n; *&n; *   When the ioctl() returns 0, solo_mode contains the previous&n; *   status (0 = deactivated, 1 = activated). If solo mode is not&n; *   implemented on this card, ioctl() returns -1 and sets errno to&n; *   EINVAL.&n; *&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/module.h&gt; 
macro_line|#include &quot;sound_config.h&quot;
DECL|macro|DEBUG
macro_line|#undef  DEBUG&t;&t;/* if defined, produce a verbose report via syslog */
DECL|variable|aci_port
r_int
id|aci_port
op_assign
l_int|0x354
suffix:semicolon
multiline_comment|/* as determined by bit 4 in the OPTi 929 MC4 register */
DECL|variable|aci_idcode
r_int
r_char
id|aci_idcode
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* manufacturer and product ID */
DECL|variable|aci_version
r_int
r_char
id|aci_version
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* ACI firmware version&t;*/
DECL|variable|aci_solo
r_int
id|aci_solo
suffix:semicolon
multiline_comment|/* status bit of the card that can&squot;t be&t;&t;*&n;&t;&t;&t; * checked with ACI versions prior to 0xb0&t;*/
DECL|variable|aci_present
r_static
r_int
id|aci_present
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef MODULE                  /* Whether the aci mixer is to be reset.    */
DECL|variable|aci_reset
r_int
id|aci_reset
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Default: don&squot;t reset if the driver is a  */
id|MODULE_PARM
c_func
(paren
id|aci_reset
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
macro_line|#else                          /* module; use &quot;insmod aci.o aci_reset=1&quot; */
DECL|variable|aci_reset
r_int
id|aci_reset
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* to override.                             */
macro_line|#endif
DECL|macro|COMMAND_REGISTER
mdefine_line|#define COMMAND_REGISTER    (aci_port)
DECL|macro|STATUS_REGISTER
mdefine_line|#define STATUS_REGISTER     (aci_port + 1)
DECL|macro|BUSY_REGISTER
mdefine_line|#define BUSY_REGISTER       (aci_port + 2)
multiline_comment|/*&n; * Wait until the ACI microcontroller has set the READYFLAG in the&n; * Busy/IRQ Source Register to 0. This is required to avoid&n; * overrunning the sound card microcontroller. We do a busy wait here,&n; * because the microcontroller is not supposed to signal a busy&n; * condition for more than a few clock cycles. In case of a time-out,&n; * this function returns -1.&n; *&n; * This busy wait code normally requires less than 15 loops and&n; * practically always less than 100 loops on my i486/DX2 66 MHz.&n; *&n; * Warning: Waiting on the general status flag after reseting the MUTE&n; * function can take a VERY long time, because the PCM12 does some kind&n; * of fade-in effect. For this reason, access to the MUTE function has&n; * not been implemented at all.&n; */
DECL|function|busy_wait
r_static
r_int
id|busy_wait
c_func
(paren
r_void
)paren
(brace
r_int
id|timeout
suffix:semicolon
r_for
c_loop
(paren
id|timeout
op_assign
l_int|0
suffix:semicolon
id|timeout
OL
l_int|10000000L
suffix:semicolon
id|timeout
op_increment
)paren
r_if
c_cond
(paren
(paren
id|inb_p
c_func
(paren
id|BUSY_REGISTER
)paren
op_amp
l_int|1
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;ACI: READYFLAG timed out.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Read the GENERAL STATUS register.&n; */
DECL|function|read_general_status
r_static
r_int
id|read_general_status
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|status
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|busy_wait
c_func
(paren
)paren
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|status
op_assign
(paren
r_int
)paren
id|inb_p
c_func
(paren
id|STATUS_REGISTER
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * The four ACI command types (implied, write, read and indexed) can&n; * be sent to the microcontroller using the following four functions.&n; * If a problem occurred, they return -1.&n; */
DECL|function|aci_implied_cmd
r_int
id|aci_implied_cmd
c_func
(paren
r_int
r_char
id|opcode
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;ACI: aci_implied_cmd(0x%02x)&bslash;n&quot;
comma
id|opcode
)paren
suffix:semicolon
macro_line|#endif
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_general_status
c_func
(paren
)paren
OL
l_int|0
op_logical_or
id|busy_wait
c_func
(paren
)paren
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|outb_p
c_func
(paren
id|opcode
comma
id|COMMAND_REGISTER
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|aci_write_cmd
r_int
id|aci_write_cmd
c_func
(paren
r_int
r_char
id|opcode
comma
r_int
r_char
id|parameter
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|status
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;ACI: aci_write_cmd(0x%02x, 0x%02x)&bslash;n&quot;
comma
id|opcode
comma
id|parameter
)paren
suffix:semicolon
macro_line|#endif
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_general_status
c_func
(paren
)paren
OL
l_int|0
op_logical_or
id|busy_wait
c_func
(paren
)paren
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|outb_p
c_func
(paren
id|opcode
comma
id|COMMAND_REGISTER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|busy_wait
c_func
(paren
)paren
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|outb_p
c_func
(paren
id|parameter
comma
id|COMMAND_REGISTER
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|read_general_status
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* polarity of the INVALID flag depends on ACI version */
r_if
c_cond
(paren
(paren
id|aci_version
OL
l_int|0xb0
op_logical_and
(paren
id|status
op_amp
l_int|0x40
)paren
op_ne
l_int|0
)paren
op_logical_or
(paren
id|aci_version
op_ge
l_int|0xb0
op_logical_and
(paren
id|status
op_amp
l_int|0x40
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ACI: invalid write command 0x%02x, 0x%02x.&bslash;n&quot;
comma
id|opcode
comma
id|parameter
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This write command send 2 parameters instead of one.&n; * Only used in PCM20 radio frequency tuning control&n; */
DECL|function|aci_write_cmd_d
r_int
id|aci_write_cmd_d
c_func
(paren
r_int
r_char
id|opcode
comma
r_int
r_char
id|parameter
comma
r_int
r_char
id|parameter2
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|status
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;ACI: aci_write_cmd_d(0x%02x, 0x%02x)&bslash;n&quot;
comma
id|opcode
comma
id|parameter
comma
id|parameter2
)paren
suffix:semicolon
macro_line|#endif
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_general_status
c_func
(paren
)paren
OL
l_int|0
op_logical_or
id|busy_wait
c_func
(paren
)paren
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|outb_p
c_func
(paren
id|opcode
comma
id|COMMAND_REGISTER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|busy_wait
c_func
(paren
)paren
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|outb_p
c_func
(paren
id|parameter
comma
id|COMMAND_REGISTER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|busy_wait
c_func
(paren
)paren
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|outb_p
c_func
(paren
id|parameter2
comma
id|COMMAND_REGISTER
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|read_general_status
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* polarity of the INVALID flag depends on ACI version */
r_if
c_cond
(paren
(paren
id|aci_version
OL
l_int|0xb0
op_logical_and
(paren
id|status
op_amp
l_int|0x40
)paren
op_ne
l_int|0
)paren
op_logical_or
(paren
id|aci_version
op_ge
l_int|0xb0
op_logical_and
(paren
id|status
op_amp
l_int|0x40
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
macro_line|#if 0&t;/* Frequency tuning works, but the INVALID flag is set ??? */
id|printk
c_func
(paren
l_string|&quot;ACI: invalid write (double) command 0x%02x, 0x%02x, 0x%02x.&bslash;n&quot;
comma
id|opcode
comma
id|parameter
comma
id|parameter2
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|aci_read_cmd
r_int
id|aci_read_cmd
c_func
(paren
r_int
r_char
id|opcode
comma
r_int
id|length
comma
r_int
r_char
op_star
id|parameter
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_general_status
c_func
(paren
)paren
OL
l_int|0
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|i
OL
id|length
)paren
(brace
r_if
c_cond
(paren
id|busy_wait
c_func
(paren
)paren
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|outb_p
c_func
(paren
id|opcode
comma
id|COMMAND_REGISTER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|busy_wait
c_func
(paren
)paren
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|parameter
(braket
id|i
op_increment
)braket
op_assign
id|inb_p
c_func
(paren
id|STATUS_REGISTER
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
r_if
c_cond
(paren
id|i
op_eq
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;ACI: aci_read_cmd(0x%02x, %d) = 0x%02x&bslash;n&quot;
comma
id|opcode
comma
id|length
comma
id|parameter
(braket
id|i
op_minus
l_int|1
)braket
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;ACI: aci_read_cmd cont.: 0x%02x&bslash;n&quot;
comma
id|parameter
(braket
id|i
op_minus
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#endif
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|aci_indexed_cmd
r_int
id|aci_indexed_cmd
c_func
(paren
r_int
r_char
id|opcode
comma
r_int
r_char
id|index
comma
r_int
r_char
op_star
id|parameter
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_general_status
c_func
(paren
)paren
OL
l_int|0
op_logical_or
id|busy_wait
c_func
(paren
)paren
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|outb_p
c_func
(paren
id|opcode
comma
id|COMMAND_REGISTER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|busy_wait
c_func
(paren
)paren
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|outb_p
c_func
(paren
id|index
comma
id|COMMAND_REGISTER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|busy_wait
c_func
(paren
)paren
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
op_star
id|parameter
op_assign
id|inb_p
c_func
(paren
id|STATUS_REGISTER
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;ACI: aci_indexed_cmd(0x%02x, 0x%02x) = 0x%02x&bslash;n&quot;
comma
id|opcode
comma
id|index
comma
op_star
id|parameter
)paren
suffix:semicolon
macro_line|#endif
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The following macro SCALE can be used to scale one integer volume&n; * value into another one using only integer arithmetic. If the input&n; * value x is in the range 0 &lt;= x &lt;= xmax, then the result will be in&n; * the range 0 &lt;= SCALE(xmax,ymax,x) &lt;= ymax.&n; *&n; * This macro has for all xmax, ymax &gt; 0 and all 0 &lt;= x &lt;= xmax the&n; * following nice properties:&n; *&n; * - SCALE(xmax,ymax,xmax) = ymax&n; * - SCALE(xmax,ymax,0) = 0&n; * - SCALE(xmax,ymax,SCALE(ymax,xmax,SCALE(xmax,ymax,x))) = SCALE(xmax,ymax,x)&n; *&n; * In addition, the rounding error is minimal and nicely distributed.&n; * The proofs are left as an exercise to the reader.&n; */
DECL|macro|SCALE
mdefine_line|#define SCALE(xmax,ymax,x) (((x)*(ymax)+(xmax)/2)/(xmax))
DECL|function|getvolume
r_static
r_int
id|getvolume
c_func
(paren
id|caddr_t
id|arg
comma
r_int
r_char
id|left_index
comma
r_int
r_char
id|right_index
)paren
(brace
r_int
id|vol
suffix:semicolon
r_int
r_char
id|buf
suffix:semicolon
multiline_comment|/* left channel */
r_if
c_cond
(paren
id|aci_indexed_cmd
c_func
(paren
l_int|0xf0
comma
id|left_index
comma
op_amp
id|buf
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|vol
op_assign
id|SCALE
c_func
(paren
l_int|0x20
comma
l_int|100
comma
id|buf
OL
l_int|0x20
ques
c_cond
l_int|0x20
op_minus
id|buf
suffix:colon
l_int|0
)paren
suffix:semicolon
multiline_comment|/* right channel */
r_if
c_cond
(paren
id|aci_indexed_cmd
c_func
(paren
l_int|0xf0
comma
id|right_index
comma
op_amp
id|buf
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|vol
op_or_assign
id|SCALE
c_func
(paren
l_int|0x20
comma
l_int|100
comma
id|buf
OL
l_int|0x20
ques
c_cond
l_int|0x20
op_minus
id|buf
suffix:colon
l_int|0
)paren
op_lshift
l_int|8
suffix:semicolon
r_return
(paren
op_star
(paren
r_int
op_star
)paren
id|arg
op_assign
id|vol
)paren
suffix:semicolon
)brace
DECL|function|setvolume
r_static
r_int
id|setvolume
c_func
(paren
id|caddr_t
id|arg
comma
r_int
r_char
id|left_index
comma
r_int
r_char
id|right_index
)paren
(brace
r_int
id|vol
comma
id|ret
suffix:semicolon
multiline_comment|/* left channel */
id|vol
op_assign
op_star
(paren
r_int
op_star
)paren
id|arg
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|vol
OG
l_int|100
)paren
id|vol
op_assign
l_int|100
suffix:semicolon
id|vol
op_assign
id|SCALE
c_func
(paren
l_int|100
comma
l_int|0x20
comma
id|vol
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aci_write_cmd
c_func
(paren
id|left_index
comma
l_int|0x20
op_minus
id|vol
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|ret
op_assign
id|SCALE
c_func
(paren
l_int|0x20
comma
l_int|100
comma
id|vol
)paren
suffix:semicolon
multiline_comment|/* right channel */
id|vol
op_assign
(paren
op_star
(paren
r_int
op_star
)paren
id|arg
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|vol
OG
l_int|100
)paren
id|vol
op_assign
l_int|100
suffix:semicolon
id|vol
op_assign
id|SCALE
c_func
(paren
l_int|100
comma
l_int|0x20
comma
id|vol
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aci_write_cmd
c_func
(paren
id|right_index
comma
l_int|0x20
op_minus
id|vol
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|ret
op_or_assign
id|SCALE
c_func
(paren
l_int|0x20
comma
l_int|100
comma
id|vol
)paren
op_lshift
l_int|8
suffix:semicolon
r_return
(paren
op_star
(paren
r_int
op_star
)paren
id|arg
op_assign
id|ret
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|aci_mixer_ioctl
id|aci_mixer_ioctl
(paren
r_int
id|dev
comma
r_int
r_int
id|cmd
comma
id|caddr_t
id|arg
)paren
(brace
r_int
id|status
comma
id|vol
suffix:semicolon
r_int
r_char
id|buf
suffix:semicolon
multiline_comment|/* handle solo mode control */
r_if
c_cond
(paren
id|cmd
op_eq
id|SOUND_MIXER_PRIVATE1
)paren
(brace
r_if
c_cond
(paren
op_star
(paren
r_int
op_star
)paren
id|arg
op_ge
l_int|0
)paren
(brace
id|aci_solo
op_assign
op_logical_neg
op_logical_neg
op_star
(paren
r_int
op_star
)paren
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|aci_write_cmd
c_func
(paren
l_int|0xd2
comma
id|aci_solo
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|aci_version
op_ge
l_int|0xb0
)paren
(brace
r_if
c_cond
(paren
(paren
id|status
op_assign
id|read_general_status
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
(paren
op_star
(paren
r_int
op_star
)paren
id|arg
op_assign
(paren
id|status
op_amp
l_int|0x20
)paren
op_eq
l_int|0
)paren
suffix:semicolon
)brace
r_return
(paren
op_star
(paren
r_int
op_star
)paren
id|arg
op_assign
id|aci_solo
)paren
suffix:semicolon
)brace
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
)paren
(brace
r_if
c_cond
(paren
id|cmd
op_amp
id|IOC_IN
)paren
multiline_comment|/* read and write */
r_switch
c_cond
(paren
id|cmd
op_amp
l_int|0xff
)paren
(brace
r_case
id|SOUND_MIXER_VOLUME
suffix:colon
r_return
id|setvolume
c_func
(paren
id|arg
comma
l_int|0x01
comma
l_int|0x00
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_CD
suffix:colon
r_return
id|setvolume
c_func
(paren
id|arg
comma
l_int|0x3c
comma
l_int|0x34
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_MIC
suffix:colon
r_return
id|setvolume
c_func
(paren
id|arg
comma
l_int|0x38
comma
l_int|0x30
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_LINE
suffix:colon
r_return
id|setvolume
c_func
(paren
id|arg
comma
l_int|0x39
comma
l_int|0x31
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_SYNTH
suffix:colon
r_return
id|setvolume
c_func
(paren
id|arg
comma
l_int|0x3b
comma
l_int|0x33
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_PCM
suffix:colon
r_return
id|setvolume
c_func
(paren
id|arg
comma
l_int|0x3a
comma
l_int|0x32
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_LINE1
suffix:colon
multiline_comment|/* AUX1 */
r_return
id|setvolume
c_func
(paren
id|arg
comma
l_int|0x3d
comma
l_int|0x35
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_LINE2
suffix:colon
multiline_comment|/* AUX2 */
r_return
id|setvolume
c_func
(paren
id|arg
comma
l_int|0x3e
comma
l_int|0x36
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_IGAIN
suffix:colon
multiline_comment|/* MIC pre-amp */
id|vol
op_assign
op_star
(paren
r_int
op_star
)paren
id|arg
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|vol
OG
l_int|100
)paren
id|vol
op_assign
l_int|100
suffix:semicolon
id|vol
op_assign
id|SCALE
c_func
(paren
l_int|100
comma
l_int|3
comma
id|vol
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aci_write_cmd
c_func
(paren
l_int|0x03
comma
id|vol
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|vol
op_assign
id|SCALE
c_func
(paren
l_int|3
comma
l_int|100
comma
id|vol
)paren
suffix:semicolon
r_return
(paren
op_star
(paren
r_int
op_star
)paren
id|arg
op_assign
id|vol
op_or
(paren
id|vol
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_RECSRC
suffix:colon
r_return
(paren
op_star
(paren
r_int
op_star
)paren
id|arg
op_assign
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
multiline_comment|/* only read */
r_switch
c_cond
(paren
id|cmd
op_amp
l_int|0xff
)paren
(brace
r_case
id|SOUND_MIXER_DEVMASK
suffix:colon
r_return
(paren
op_star
(paren
r_int
op_star
)paren
id|arg
op_assign
id|SOUND_MASK_VOLUME
op_or
id|SOUND_MASK_CD
op_or
id|SOUND_MASK_MIC
op_or
id|SOUND_MASK_LINE
op_or
id|SOUND_MASK_SYNTH
op_or
id|SOUND_MASK_PCM
op_or
macro_line|#if 0
id|SOUND_MASK_IGAIN
op_or
macro_line|#endif
id|SOUND_MASK_LINE1
op_or
id|SOUND_MASK_LINE2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_STEREODEVS
suffix:colon
r_return
(paren
op_star
(paren
r_int
op_star
)paren
id|arg
op_assign
id|SOUND_MASK_VOLUME
op_or
id|SOUND_MASK_CD
op_or
id|SOUND_MASK_MIC
op_or
id|SOUND_MASK_LINE
op_or
id|SOUND_MASK_SYNTH
op_or
id|SOUND_MASK_PCM
op_or
id|SOUND_MASK_LINE1
op_or
id|SOUND_MASK_LINE2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_RECMASK
suffix:colon
r_return
(paren
op_star
(paren
r_int
op_star
)paren
id|arg
op_assign
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_RECSRC
suffix:colon
r_return
(paren
op_star
(paren
r_int
op_star
)paren
id|arg
op_assign
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_CAPS
suffix:colon
r_return
(paren
op_star
(paren
r_int
op_star
)paren
id|arg
op_assign
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_VOLUME
suffix:colon
r_return
id|getvolume
c_func
(paren
id|arg
comma
l_int|0x04
comma
l_int|0x03
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_CD
suffix:colon
r_return
id|getvolume
c_func
(paren
id|arg
comma
l_int|0x0a
comma
l_int|0x09
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_MIC
suffix:colon
r_return
id|getvolume
c_func
(paren
id|arg
comma
l_int|0x06
comma
l_int|0x05
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_LINE
suffix:colon
r_return
id|getvolume
c_func
(paren
id|arg
comma
l_int|0x08
comma
l_int|0x07
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_SYNTH
suffix:colon
r_return
id|getvolume
c_func
(paren
id|arg
comma
l_int|0x0c
comma
l_int|0x0b
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_PCM
suffix:colon
r_return
id|getvolume
c_func
(paren
id|arg
comma
l_int|0x0e
comma
l_int|0x0d
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_LINE1
suffix:colon
multiline_comment|/* AUX1 */
r_return
id|getvolume
c_func
(paren
id|arg
comma
l_int|0x11
comma
l_int|0x10
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_LINE2
suffix:colon
multiline_comment|/* AUX2 */
r_return
id|getvolume
c_func
(paren
id|arg
comma
l_int|0x13
comma
l_int|0x12
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_IGAIN
suffix:colon
multiline_comment|/* MIC pre-amp */
r_if
c_cond
(paren
id|aci_indexed_cmd
c_func
(paren
l_int|0xf0
comma
l_int|0x21
comma
op_amp
id|buf
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|vol
op_assign
id|SCALE
c_func
(paren
l_int|3
comma
l_int|100
comma
id|buf
op_le
l_int|3
ques
c_cond
id|buf
suffix:colon
l_int|3
)paren
suffix:semicolon
id|vol
op_or_assign
id|vol
op_lshift
l_int|8
suffix:semicolon
r_return
(paren
op_star
(paren
r_int
op_star
)paren
id|arg
op_assign
id|vol
)paren
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|variable|aci_mixer_operations
r_static
r_struct
id|mixer_operations
id|aci_mixer_operations
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|id
suffix:colon
l_string|&quot;ACI&quot;
comma
id|name
suffix:colon
l_string|&quot;ACI mixer&quot;
comma
id|ioctl
suffix:colon
id|aci_mixer_ioctl
)brace
suffix:semicolon
r_static
r_int
r_char
DECL|function|mad_read
id|mad_read
(paren
r_int
id|port
)paren
(brace
id|outb
(paren
l_int|0xE3
comma
l_int|0xf8f
)paren
suffix:semicolon
multiline_comment|/* Write MAD16 password */
r_return
id|inb
(paren
id|port
)paren
suffix:semicolon
multiline_comment|/* Read from port */
)brace
multiline_comment|/*&n; * Check, whether there actually is any ACI port operational and if&n; * one was found, then initialize the ACI interface, reserve the I/O&n; * addresses and attach the new mixer to the relevant VoxWare data&n; * structures.&n; *&n; * Returns:  1   ACI mixer detected&n; *           0   nothing there&n; *&n; * There is also an internal mixer in the codec (CS4231A or AD1845),&n; * that deserves no purpose in an ACI based system which uses an&n; * external ACI controlled stereo mixer. Make sure that this codec&n; * mixer has the AUX1 input selected as the recording source, that the&n; * input gain is set near maximum and that the other channels going&n; * from the inputs to the codec output are muted.&n; */
DECL|function|attach_aci
r_static
r_int
id|__init
id|attach_aci
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|boardname
op_assign
l_string|&quot;unknown&quot;
suffix:semicolon
r_int
id|volume
suffix:semicolon
DECL|macro|MC4_PORT
mdefine_line|#define MC4_PORT&t;0xf90
id|aci_port
op_assign
(paren
id|mad_read
c_func
(paren
id|MC4_PORT
)paren
op_amp
l_int|0x10
)paren
ques
c_cond
l_int|0x344
suffix:colon
l_int|0x354
suffix:semicolon
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|aci_port
comma
l_int|3
)paren
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;ACI: I/O area 0x%03x-0x%03x already used.&bslash;n&quot;
comma
id|aci_port
comma
id|aci_port
op_plus
l_int|2
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|aci_read_cmd
c_func
(paren
l_int|0xf2
comma
l_int|2
comma
id|aci_idcode
)paren
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;ACI: Failed to read idcode.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|aci_read_cmd
c_func
(paren
l_int|0xf1
comma
l_int|1
comma
op_amp
id|aci_version
)paren
)paren
(brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;ACI: Failed to read version.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|aci_idcode
(braket
l_int|0
)braket
op_eq
l_int|0x6d
)paren
(brace
multiline_comment|/* It looks like a miro sound card. */
r_switch
c_cond
(paren
id|aci_idcode
(braket
l_int|1
)braket
)paren
(brace
r_case
l_int|0x41
suffix:colon
id|boardname
op_assign
l_string|&quot;PCM1 pro / early PCM12&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x42
suffix:colon
id|boardname
op_assign
l_string|&quot;PCM12&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x43
suffix:colon
id|boardname
op_assign
l_string|&quot;PCM20&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|boardname
op_assign
l_string|&quot;unknown miro&quot;
suffix:semicolon
)brace
)brace
r_else
macro_line|#ifndef DEBUG
r_return
l_int|0
suffix:semicolon
macro_line|#endif
id|printk
c_func
(paren
l_string|&quot;&lt;ACI %02x, id %02x %02x (%s)&gt; at 0x%03x&bslash;n&quot;
comma
id|aci_version
comma
id|aci_idcode
(braket
l_int|0
)braket
comma
id|aci_idcode
(braket
l_int|1
)braket
comma
id|boardname
comma
id|aci_port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aci_reset
)paren
(brace
multiline_comment|/* initialize ACI mixer */
id|aci_implied_cmd
c_func
(paren
l_int|0xff
)paren
suffix:semicolon
id|aci_solo
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* attach the mixer */
id|request_region
c_func
(paren
id|aci_port
comma
l_int|3
comma
l_string|&quot;sound mixer (ACI)&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num_mixers
OL
id|MAX_MIXER_DEV
)paren
(brace
r_if
c_cond
(paren
id|num_mixers
OG
l_int|0
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
l_string|&quot;MAD16 WSS&quot;
comma
id|mixer_devs
(braket
id|num_mixers
op_minus
l_int|1
)braket
op_member_access_from_pointer
id|name
comma
l_int|9
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * The previously registered mixer device is the CS4231A which&n;&t;&t;&t; * has no function on an ACI card. Make the ACI mixer the first&n;&t;&t;&t; * of the two mixer devices.&n;&t;&t;&t; */
id|mixer_devs
(braket
id|num_mixers
)braket
op_assign
id|mixer_devs
(braket
id|num_mixers
op_minus
l_int|1
)braket
suffix:semicolon
id|mixer_devs
(braket
id|num_mixers
op_minus
l_int|1
)braket
op_assign
op_amp
id|aci_mixer_operations
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Initialize the CS4231A mixer with reasonable values. It is&n;&t;&t;&t; * unlikely that the user ever will want to change these as all&n;&t;&t;&t; * channels can be mixed via ACI.&n;&t;&t;&t; */
id|volume
op_assign
l_int|0x6464
suffix:semicolon
id|mixer_devs
(braket
id|num_mixers
)braket
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|num_mixers
comma
id|SOUND_MIXER_WRITE_PCM
comma
(paren
id|caddr_t
)paren
op_amp
id|volume
)paren
suffix:semicolon
id|volume
op_assign
l_int|0x6464
suffix:semicolon
id|mixer_devs
(braket
id|num_mixers
)braket
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|num_mixers
comma
id|SOUND_MIXER_WRITE_IGAIN
comma
(paren
id|caddr_t
)paren
op_amp
id|volume
)paren
suffix:semicolon
id|volume
op_assign
l_int|0
suffix:semicolon
id|mixer_devs
(braket
id|num_mixers
)braket
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|num_mixers
comma
id|SOUND_MIXER_WRITE_SPEAKER
comma
(paren
id|caddr_t
)paren
op_amp
id|volume
)paren
suffix:semicolon
id|volume
op_assign
l_int|0
suffix:semicolon
id|mixer_devs
(braket
id|num_mixers
)braket
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|num_mixers
comma
id|SOUND_MIXER_WRITE_MIC
comma
(paren
id|caddr_t
)paren
op_amp
id|volume
)paren
suffix:semicolon
id|volume
op_assign
l_int|0
suffix:semicolon
id|mixer_devs
(braket
id|num_mixers
)braket
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|num_mixers
comma
id|SOUND_MIXER_WRITE_IMIX
comma
(paren
id|caddr_t
)paren
op_amp
id|volume
)paren
suffix:semicolon
id|volume
op_assign
l_int|0
suffix:semicolon
id|mixer_devs
(braket
id|num_mixers
)braket
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|num_mixers
comma
id|SOUND_MIXER_WRITE_LINE1
comma
(paren
id|caddr_t
)paren
op_amp
id|volume
)paren
suffix:semicolon
id|volume
op_assign
l_int|0
suffix:semicolon
id|mixer_devs
(braket
id|num_mixers
)braket
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|num_mixers
comma
id|SOUND_MIXER_WRITE_LINE2
comma
(paren
id|caddr_t
)paren
op_amp
id|volume
)paren
suffix:semicolon
id|volume
op_assign
l_int|0
suffix:semicolon
id|mixer_devs
(braket
id|num_mixers
)braket
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|num_mixers
comma
id|SOUND_MIXER_WRITE_LINE3
comma
(paren
id|caddr_t
)paren
op_amp
id|volume
)paren
suffix:semicolon
id|volume
op_assign
id|SOUND_MASK_LINE1
suffix:semicolon
id|mixer_devs
(braket
id|num_mixers
)braket
op_member_access_from_pointer
id|ioctl
c_func
(paren
id|num_mixers
comma
id|SOUND_MIXER_WRITE_RECSRC
comma
(paren
id|caddr_t
)paren
op_amp
id|volume
)paren
suffix:semicolon
id|num_mixers
op_increment
suffix:semicolon
)brace
r_else
id|mixer_devs
(braket
id|num_mixers
op_increment
)braket
op_assign
op_amp
id|aci_mixer_operations
suffix:semicolon
)brace
multiline_comment|/* Just do something; otherwise the first write command fails, at&n;&t; * least with my PCM20.&n;&t; */
id|aci_mixer_ioctl
c_func
(paren
id|num_mixers
op_minus
l_int|1
comma
id|SOUND_MIXER_READ_VOLUME
comma
(paren
id|caddr_t
)paren
op_amp
id|volume
)paren
suffix:semicolon
r_if
c_cond
(paren
id|aci_reset
)paren
(brace
multiline_comment|/* Initialize ACI mixer with reasonable power-up values */
id|volume
op_assign
l_int|0x3232
suffix:semicolon
id|aci_mixer_ioctl
c_func
(paren
id|num_mixers
op_minus
l_int|1
comma
id|SOUND_MIXER_WRITE_VOLUME
comma
(paren
id|caddr_t
)paren
op_amp
id|volume
)paren
suffix:semicolon
id|volume
op_assign
l_int|0x3232
suffix:semicolon
id|aci_mixer_ioctl
c_func
(paren
id|num_mixers
op_minus
l_int|1
comma
id|SOUND_MIXER_WRITE_SYNTH
comma
(paren
id|caddr_t
)paren
op_amp
id|volume
)paren
suffix:semicolon
id|volume
op_assign
l_int|0x3232
suffix:semicolon
id|aci_mixer_ioctl
c_func
(paren
id|num_mixers
op_minus
l_int|1
comma
id|SOUND_MIXER_WRITE_PCM
comma
(paren
id|caddr_t
)paren
op_amp
id|volume
)paren
suffix:semicolon
id|volume
op_assign
l_int|0x3232
suffix:semicolon
id|aci_mixer_ioctl
c_func
(paren
id|num_mixers
op_minus
l_int|1
comma
id|SOUND_MIXER_WRITE_LINE
comma
(paren
id|caddr_t
)paren
op_amp
id|volume
)paren
suffix:semicolon
id|volume
op_assign
l_int|0x3232
suffix:semicolon
id|aci_mixer_ioctl
c_func
(paren
id|num_mixers
op_minus
l_int|1
comma
id|SOUND_MIXER_WRITE_MIC
comma
(paren
id|caddr_t
)paren
op_amp
id|volume
)paren
suffix:semicolon
id|volume
op_assign
l_int|0x3232
suffix:semicolon
id|aci_mixer_ioctl
c_func
(paren
id|num_mixers
op_minus
l_int|1
comma
id|SOUND_MIXER_WRITE_CD
comma
(paren
id|caddr_t
)paren
op_amp
id|volume
)paren
suffix:semicolon
id|volume
op_assign
l_int|0x3232
suffix:semicolon
id|aci_mixer_ioctl
c_func
(paren
id|num_mixers
op_minus
l_int|1
comma
id|SOUND_MIXER_WRITE_LINE1
comma
(paren
id|caddr_t
)paren
op_amp
id|volume
)paren
suffix:semicolon
id|volume
op_assign
l_int|0x3232
suffix:semicolon
id|aci_mixer_ioctl
c_func
(paren
id|num_mixers
op_minus
l_int|1
comma
id|SOUND_MIXER_WRITE_LINE2
comma
(paren
id|caddr_t
)paren
op_amp
id|volume
)paren
suffix:semicolon
)brace
id|aci_present
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|unload_aci
r_static
r_void
id|__exit
id|unload_aci
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|aci_present
)paren
id|release_region
c_func
(paren
id|aci_port
comma
l_int|3
)paren
suffix:semicolon
)brace
DECL|variable|attach_aci
id|module_init
c_func
(paren
id|attach_aci
)paren
suffix:semicolon
DECL|variable|unload_aci
id|module_exit
c_func
(paren
id|unload_aci
)paren
suffix:semicolon
eof
