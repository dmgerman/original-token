multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;baycom_par.c  -- baycom par96 and picpar radio modem driver.&n; *&n; *&t;Copyright (C) 1997  Thomas Sailer (sailer@ife.ee.ethz.ch)&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License&n; *&t;along with this program; if not, write to the Free Software&n; *&t;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  Please note that the GPL allows you to use the driver, NOT the radio.&n; *  In order to use the radio, you need a license from the communications&n; *  authority of your country.&n; *&n; *&n; *  Supported modems&n; *&n; *  par96:  This is a modem for 9600 baud FSK compatible to the G3RUH standard.&n; *          The modem does all the filtering and regenerates the receiver clock.&n; *          Data is transferred from and to the PC via a shift register.&n; *          The shift register is filled with 16 bits and an interrupt is&n; *          signalled. The PC then empties the shift register in a burst. This&n; *          modem connects to the parallel port, hence the name. The modem&n; *          leaves the implementation of the HDLC protocol and the scrambler&n; *          polynomial to the PC. This modem is no longer available (at least&n; *          from Baycom) and has been replaced by the PICPAR modem (see below).&n; *          You may however still build one from the schematics published in&n; *          cq-DL :-).&n; *&n; *  picpar: This is a redesign of the par96 modem by Henning Rech, DF9IC. The&n; *          modem is protocol compatible to par96, but uses only three low&n; *          power ICs and can therefore be fed from the parallel port and&n; *          does not require an additional power supply. It features&n; *          built in DCD circuitry. The driver should therefore be configured&n; *          for hardware DCD.&n; *&n; *&n; *  Command line options (insmod command line)&n; *&n; *  mode     driver mode string. Valid choices are par96 and picpar.&n; *  iobase   base address of the port; common values are 0x378, 0x278, 0x3bc&n; *&n; *&n; *  History:&n; *   0.1  26.06.96  Adapted from baycom.c and made network driver interface&n; *        18.10.96  Changed to new user space access routines (copy_{to,from}_user)&n; *   0.3  26.04.97  init code/data tagged&n; *   0.4  08.07.97  alternative ser12 decoding algorithm (uses delta CTS ints)&n; *   0.5  11.11.97  split into separate files for ser12/par96&n; */
multiline_comment|/*****************************************************************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/hdlcdrv.h&gt;
macro_line|#include &lt;linux/baycom.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
multiline_comment|/* --------------------------------------------------------------------- */
multiline_comment|/*&n; * currently this module is supposed to support both module styles, i.e.&n; * the old one present up to about 2.1.9, and the new one functioning&n; * starting with 2.1.21. The reason is I have a kit allowing to compile&n; * this module also under 2.0.x which was requested by several people.&n; * This will go in 2.2&n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#if LINUX_VERSION_CODE &gt;= 0x20100
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#else
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
DECL|macro|put_user
macro_line|#undef put_user
DECL|macro|get_user
macro_line|#undef get_user
DECL|macro|put_user
mdefine_line|#define put_user(x,ptr) ({ __put_user((unsigned long)(x),(ptr),sizeof(*(ptr))); 0; })
DECL|macro|get_user
mdefine_line|#define get_user(x,ptr) ({ x = ((__typeof__(*(ptr)))__get_user((ptr),sizeof(*(ptr)))); 0; })
DECL|function|copy_from_user
r_extern
id|__inline__
r_int
id|copy_from_user
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
r_int
id|n
)paren
(brace
r_int
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|from
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|copy_to_user
r_extern
id|__inline__
r_int
id|copy_to_user
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
r_int
id|n
)paren
(brace
r_int
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|to
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt;= 0x20123
macro_line|#include &lt;linux/init.h&gt;
macro_line|#else
DECL|macro|__init
mdefine_line|#define __init
DECL|macro|__initdata
mdefine_line|#define __initdata
DECL|macro|__initfunc
mdefine_line|#define __initfunc(x) x
macro_line|#endif
multiline_comment|/* --------------------------------------------------------------------- */
DECL|macro|BAYCOM_DEBUG
mdefine_line|#define BAYCOM_DEBUG
multiline_comment|/*&n; * modem options; bit mask&n; */
DECL|macro|BAYCOM_OPTIONS_SOFTDCD
mdefine_line|#define BAYCOM_OPTIONS_SOFTDCD  1
multiline_comment|/* --------------------------------------------------------------------- */
DECL|variable|bc_drvname
r_static
r_const
r_char
id|bc_drvname
(braket
)braket
op_assign
l_string|&quot;baycom_par&quot;
suffix:semicolon
DECL|variable|bc_drvinfo
r_static
r_const
r_char
id|bc_drvinfo
(braket
)braket
op_assign
id|KERN_INFO
l_string|&quot;baycom_par: (C) 1997 Thomas Sailer, HB9JNX/AE4WA&bslash;n&quot;
id|KERN_INFO
l_string|&quot;baycom_par: version 0.5 compiled &quot;
id|__TIME__
l_string|&quot; &quot;
id|__DATE__
l_string|&quot;&bslash;n&quot;
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|macro|NR_PORTS
mdefine_line|#define NR_PORTS 4
DECL|variable|baycom_device
r_static
r_struct
id|device
id|baycom_device
(braket
id|NR_PORTS
)braket
suffix:semicolon
r_static
r_struct
(brace
DECL|member|mode
r_const
r_char
op_star
id|mode
suffix:semicolon
DECL|member|iobase
r_int
id|iobase
suffix:semicolon
DECL|variable|baycom_ports
)brace
id|baycom_ports
(braket
id|NR_PORTS
)braket
op_assign
(brace
(brace
l_int|NULL
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|macro|SER12_EXTENT
mdefine_line|#define SER12_EXTENT 8
DECL|macro|LPT_DATA
mdefine_line|#define LPT_DATA(dev)    ((dev)-&gt;base_addr+0)
DECL|macro|LPT_STATUS
mdefine_line|#define LPT_STATUS(dev)  ((dev)-&gt;base_addr+1)
DECL|macro|LPT_CONTROL
mdefine_line|#define LPT_CONTROL(dev) ((dev)-&gt;base_addr+2)
DECL|macro|LPT_IRQ_ENABLE
mdefine_line|#define LPT_IRQ_ENABLE      0x10
DECL|macro|PAR96_BURSTBITS
mdefine_line|#define PAR96_BURSTBITS 16
DECL|macro|PAR96_BURST
mdefine_line|#define PAR96_BURST     4
DECL|macro|PAR96_PTT
mdefine_line|#define PAR96_PTT       2
DECL|macro|PAR96_TXBIT
mdefine_line|#define PAR96_TXBIT     1
DECL|macro|PAR96_ACK
mdefine_line|#define PAR96_ACK       0x40
DECL|macro|PAR96_RXBIT
mdefine_line|#define PAR96_RXBIT     0x20
DECL|macro|PAR96_DCD
mdefine_line|#define PAR96_DCD       0x10
DECL|macro|PAR97_POWER
mdefine_line|#define PAR97_POWER     0xf8
multiline_comment|/* ---------------------------------------------------------------------- */
multiline_comment|/*&n; * Information that need to be kept for each board.&n; */
DECL|struct|baycom_state
r_struct
id|baycom_state
(brace
DECL|member|hdrv
r_struct
id|hdlcdrv_state
id|hdrv
suffix:semicolon
DECL|member|pdev
r_struct
id|pardevice
op_star
id|pdev
suffix:semicolon
DECL|member|options
r_int
r_int
id|options
suffix:semicolon
DECL|struct|modem_state
r_struct
id|modem_state
(brace
DECL|member|arb_divider
r_int
id|arb_divider
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|member|shreg
r_int
r_int
id|shreg
suffix:semicolon
DECL|struct|modem_state_par96
r_struct
id|modem_state_par96
(brace
DECL|member|dcd_count
r_int
id|dcd_count
suffix:semicolon
DECL|member|dcd_shreg
r_int
r_int
id|dcd_shreg
suffix:semicolon
DECL|member|descram
r_int
r_int
id|descram
suffix:semicolon
DECL|member|scram
r_int
r_int
id|scram
suffix:semicolon
DECL|member|par96
)brace
id|par96
suffix:semicolon
DECL|member|modem
)brace
id|modem
suffix:semicolon
macro_line|#ifdef BAYCOM_DEBUG
DECL|struct|debug_vals
r_struct
id|debug_vals
(brace
DECL|member|last_jiffies
r_int
r_int
id|last_jiffies
suffix:semicolon
DECL|member|cur_intcnt
r_int
id|cur_intcnt
suffix:semicolon
DECL|member|last_intcnt
r_int
id|last_intcnt
suffix:semicolon
DECL|member|cur_pllcorr
r_int
id|cur_pllcorr
suffix:semicolon
DECL|member|last_pllcorr
r_int
id|last_pllcorr
suffix:semicolon
DECL|member|debug_vals
)brace
id|debug_vals
suffix:semicolon
macro_line|#endif /* BAYCOM_DEBUG */
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|macro|min
mdefine_line|#define min(a, b) (((a) &lt; (b)) ? (a) : (b))
DECL|macro|max
mdefine_line|#define max(a, b) (((a) &gt; (b)) ? (a) : (b))
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|baycom_int_freq
r_static
r_void
id|__inline__
id|baycom_int_freq
c_func
(paren
r_struct
id|baycom_state
op_star
id|bc
)paren
(brace
macro_line|#ifdef BAYCOM_DEBUG
r_int
r_int
id|cur_jiffies
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/*&n;&t; * measure the interrupt frequency&n;&t; */
id|bc-&gt;debug_vals.cur_intcnt
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cur_jiffies
op_minus
id|bc-&gt;debug_vals.last_jiffies
)paren
op_ge
id|HZ
)paren
(brace
id|bc-&gt;debug_vals.last_jiffies
op_assign
id|cur_jiffies
suffix:semicolon
id|bc-&gt;debug_vals.last_intcnt
op_assign
id|bc-&gt;debug_vals.cur_intcnt
suffix:semicolon
id|bc-&gt;debug_vals.cur_intcnt
op_assign
l_int|0
suffix:semicolon
id|bc-&gt;debug_vals.last_pllcorr
op_assign
id|bc-&gt;debug_vals.cur_pllcorr
suffix:semicolon
id|bc-&gt;debug_vals.cur_pllcorr
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* BAYCOM_DEBUG */
)brace
multiline_comment|/* --------------------------------------------------------------------- */
multiline_comment|/*&n; * ===================== PAR96 specific routines =========================&n; */
DECL|macro|PAR96_DESCRAM_TAP1
mdefine_line|#define PAR96_DESCRAM_TAP1 0x20000
DECL|macro|PAR96_DESCRAM_TAP2
mdefine_line|#define PAR96_DESCRAM_TAP2 0x01000
DECL|macro|PAR96_DESCRAM_TAP3
mdefine_line|#define PAR96_DESCRAM_TAP3 0x00001
DECL|macro|PAR96_DESCRAM_TAPSH1
mdefine_line|#define PAR96_DESCRAM_TAPSH1 17
DECL|macro|PAR96_DESCRAM_TAPSH2
mdefine_line|#define PAR96_DESCRAM_TAPSH2 12
DECL|macro|PAR96_DESCRAM_TAPSH3
mdefine_line|#define PAR96_DESCRAM_TAPSH3 0
DECL|macro|PAR96_SCRAM_TAP1
mdefine_line|#define PAR96_SCRAM_TAP1 0x20000 /* X^17 */
DECL|macro|PAR96_SCRAM_TAPN
mdefine_line|#define PAR96_SCRAM_TAPN 0x00021 /* X^0+X^5 */
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|par96_tx
r_static
id|__inline__
r_void
id|par96_tx
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|baycom_state
op_star
id|bc
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|data
op_assign
id|hdlcdrv_getbits
c_func
(paren
op_amp
id|bc-&gt;hdrv
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
id|PAR96_BURSTBITS
suffix:semicolon
id|i
op_increment
comma
id|data
op_rshift_assign
l_int|1
)paren
(brace
r_int
r_char
id|val
op_assign
id|PAR97_POWER
suffix:semicolon
id|bc-&gt;modem.par96.scram
op_assign
(paren
(paren
id|bc-&gt;modem.par96.scram
op_lshift
l_int|1
)paren
op_or
(paren
id|bc-&gt;modem.par96.scram
op_amp
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|data
op_amp
l_int|1
)paren
)paren
id|bc-&gt;modem.par96.scram
op_xor_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|bc-&gt;modem.par96.scram
op_amp
(paren
id|PAR96_SCRAM_TAP1
op_lshift
l_int|1
)paren
)paren
id|bc-&gt;modem.par96.scram
op_xor_assign
(paren
id|PAR96_SCRAM_TAPN
op_lshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bc-&gt;modem.par96.scram
op_amp
(paren
id|PAR96_SCRAM_TAP1
op_lshift
l_int|2
)paren
)paren
id|val
op_or_assign
id|PAR96_TXBIT
suffix:semicolon
id|outb
c_func
(paren
id|val
comma
id|LPT_DATA
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|val
op_or
id|PAR96_BURST
comma
id|LPT_DATA
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|par96_rx
r_static
id|__inline__
r_void
id|par96_rx
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|baycom_state
op_star
id|bc
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|data
comma
id|mask
comma
id|mask2
comma
id|descx
suffix:semicolon
multiline_comment|/*&n;&t; * do receiver; differential decode and descramble on the fly&n;&t; */
r_for
c_loop
(paren
id|data
op_assign
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PAR96_BURSTBITS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bc-&gt;modem.par96.descram
op_assign
(paren
id|bc-&gt;modem.par96.descram
op_lshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|LPT_STATUS
c_func
(paren
id|dev
)paren
)paren
op_amp
id|PAR96_RXBIT
)paren
id|bc-&gt;modem.par96.descram
op_or_assign
l_int|1
suffix:semicolon
id|descx
op_assign
id|bc-&gt;modem.par96.descram
op_xor
(paren
id|bc-&gt;modem.par96.descram
op_rshift
l_int|1
)paren
suffix:semicolon
multiline_comment|/* now the diff decoded data is inverted in descram */
id|outb
c_func
(paren
id|PAR97_POWER
op_or
id|PAR96_PTT
comma
id|LPT_DATA
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|descx
op_xor_assign
(paren
(paren
id|descx
op_rshift
id|PAR96_DESCRAM_TAPSH1
)paren
op_xor
(paren
id|descx
op_rshift
id|PAR96_DESCRAM_TAPSH2
)paren
)paren
suffix:semicolon
id|data
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|descx
op_amp
l_int|1
)paren
)paren
id|data
op_or_assign
l_int|0x8000
suffix:semicolon
id|outb
c_func
(paren
id|PAR97_POWER
op_or
id|PAR96_PTT
op_or
id|PAR96_BURST
comma
id|LPT_DATA
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
)brace
id|hdlcdrv_putbits
c_func
(paren
op_amp
id|bc-&gt;hdrv
comma
id|data
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * do DCD algorithm&n;&t; */
r_if
c_cond
(paren
id|bc-&gt;options
op_amp
id|BAYCOM_OPTIONS_SOFTDCD
)paren
(brace
id|bc-&gt;modem.par96.dcd_shreg
op_assign
(paren
id|bc-&gt;modem.par96.dcd_shreg
op_rshift
l_int|16
)paren
op_or
(paren
id|data
op_lshift
l_int|16
)paren
suffix:semicolon
multiline_comment|/* search for flags and set the dcd counter appropriately */
r_for
c_loop
(paren
id|mask
op_assign
l_int|0x1fe00
comma
id|mask2
op_assign
l_int|0xfc00
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PAR96_BURSTBITS
suffix:semicolon
id|i
op_increment
comma
id|mask
op_lshift_assign
l_int|1
comma
id|mask2
op_lshift_assign
l_int|1
)paren
r_if
c_cond
(paren
(paren
id|bc-&gt;modem.par96.dcd_shreg
op_amp
id|mask
)paren
op_eq
id|mask2
)paren
id|bc-&gt;modem.par96.dcd_count
op_assign
id|HDLCDRV_MAXFLEN
op_plus
l_int|4
suffix:semicolon
multiline_comment|/* check for abort/noise sequences */
r_for
c_loop
(paren
id|mask
op_assign
l_int|0x1fe00
comma
id|mask2
op_assign
l_int|0x1fe00
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|PAR96_BURSTBITS
suffix:semicolon
id|i
op_increment
comma
id|mask
op_lshift_assign
l_int|1
comma
id|mask2
op_lshift_assign
l_int|1
)paren
r_if
c_cond
(paren
(paren
(paren
id|bc-&gt;modem.par96.dcd_shreg
op_amp
id|mask
)paren
op_eq
id|mask2
)paren
op_logical_and
(paren
id|bc-&gt;modem.par96.dcd_count
op_ge
l_int|0
)paren
)paren
id|bc-&gt;modem.par96.dcd_count
op_sub_assign
id|HDLCDRV_MAXFLEN
op_minus
l_int|10
suffix:semicolon
multiline_comment|/* decrement and set the dcd variable */
r_if
c_cond
(paren
id|bc-&gt;modem.par96.dcd_count
op_ge
l_int|0
)paren
id|bc-&gt;modem.par96.dcd_count
op_sub_assign
l_int|2
suffix:semicolon
id|hdlcdrv_setdcd
c_func
(paren
op_amp
id|bc-&gt;hdrv
comma
id|bc-&gt;modem.par96.dcd_count
OG
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|hdlcdrv_setdcd
c_func
(paren
op_amp
id|bc-&gt;hdrv
comma
op_logical_neg
op_logical_neg
(paren
id|inb
c_func
(paren
id|LPT_STATUS
c_func
(paren
id|dev
)paren
)paren
op_amp
id|PAR96_DCD
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|par96_interrupt
r_static
r_void
id|par96_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|parport
op_star
id|pp
op_assign
(paren
r_struct
id|parport
op_star
)paren
id|dev_id
suffix:semicolon
r_struct
id|pardevice
op_star
id|pd
op_assign
id|pp-&gt;cad
suffix:semicolon
r_struct
id|device
op_star
id|dev
op_assign
(paren
r_struct
id|device
op_star
)paren
id|pd
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|baycom_state
op_star
id|bc
op_assign
(paren
r_struct
id|baycom_state
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|bc
op_logical_or
id|bc-&gt;hdrv.magic
op_ne
id|HDLCDRV_MAGIC
)paren
r_return
suffix:semicolon
id|baycom_int_freq
c_func
(paren
id|bc
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * check if transmitter active&n;&t; */
r_if
c_cond
(paren
id|hdlcdrv_ptt
c_func
(paren
op_amp
id|bc-&gt;hdrv
)paren
)paren
id|par96_tx
c_func
(paren
id|dev
comma
id|bc
)paren
suffix:semicolon
r_else
(brace
id|par96_rx
c_func
(paren
id|dev
comma
id|bc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|bc-&gt;modem.arb_divider
op_le
l_int|0
)paren
(brace
id|bc-&gt;modem.arb_divider
op_assign
l_int|6
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
id|hdlcdrv_arbitrate
c_func
(paren
id|dev
comma
op_amp
id|bc-&gt;hdrv
)paren
suffix:semicolon
)brace
)brace
id|sti
c_func
(paren
)paren
suffix:semicolon
id|hdlcdrv_transmitter
c_func
(paren
id|dev
comma
op_amp
id|bc-&gt;hdrv
)paren
suffix:semicolon
id|hdlcdrv_receiver
c_func
(paren
id|dev
comma
op_amp
id|bc-&gt;hdrv
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|par96_preempt
r_static
r_int
id|par96_preempt
c_func
(paren
r_void
op_star
id|handle
)paren
(brace
multiline_comment|/* we cannot relinquish the port in the middle of an operation */
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|par96_wakeup
r_static
r_void
id|par96_wakeup
c_func
(paren
r_void
op_star
id|handle
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
(paren
r_struct
id|device
op_star
)paren
id|handle
suffix:semicolon
r_struct
id|baycom_state
op_star
id|bc
op_assign
(paren
r_struct
id|baycom_state
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;baycom_par: %s: why am I being woken up?&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parport_claim
c_func
(paren
id|bc-&gt;pdev
)paren
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;baycom_par: %s: I&squot;m broken.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|par96_open
r_static
r_int
id|par96_open
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|baycom_state
op_star
id|bc
op_assign
(paren
r_struct
id|baycom_state
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_struct
id|parport
op_star
id|pp
op_assign
id|parport_enumerate
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|bc
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_while
c_loop
(paren
id|pp
op_logical_and
id|pp-&gt;base
op_ne
id|dev-&gt;base_addr
)paren
id|pp
op_assign
id|pp-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pp
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;baycom_par: parport at 0x%lx unknown&bslash;n&quot;
comma
id|dev-&gt;base_addr
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pp-&gt;irq
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;baycom_par: parport at 0x%lx has no irq&bslash;n&quot;
comma
id|pp-&gt;base
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|memset
c_func
(paren
op_amp
id|bc-&gt;modem
comma
l_int|0
comma
r_sizeof
(paren
id|bc-&gt;modem
)paren
)paren
suffix:semicolon
id|bc-&gt;hdrv.par.bitrate
op_assign
l_int|9600
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bc-&gt;pdev
op_assign
id|parport_register_device
c_func
(paren
id|pp
comma
id|dev-&gt;name
comma
id|par96_preempt
comma
id|par96_wakeup
comma
id|par96_interrupt
comma
id|PARPORT_DEV_LURK
comma
id|dev
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;baycom_par: cannot register parport at 0x%lx&bslash;n&quot;
comma
id|pp-&gt;base
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|parport_claim
c_func
(paren
id|bc-&gt;pdev
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;baycom_par: parport at 0x%lx busy&bslash;n&quot;
comma
id|pp-&gt;base
)paren
suffix:semicolon
id|parport_unregister_device
c_func
(paren
id|bc-&gt;pdev
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|dev-&gt;irq
op_assign
id|pp-&gt;irq
suffix:semicolon
multiline_comment|/* bc-&gt;pdev-&gt;port-&gt;ops-&gt;change_mode(bc-&gt;pdev-&gt;port, PARPORT_MODE_PCSPP);  not yet implemented */
multiline_comment|/* switch off PTT */
id|outb
c_func
(paren
id|PAR96_PTT
op_or
id|PAR97_POWER
comma
id|LPT_DATA
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
multiline_comment|/*bc-&gt;pdev-&gt;port-&gt;ops-&gt;enable_irq(bc-&gt;pdev-&gt;port);  not yet implemented */
id|outb
c_func
(paren
id|LPT_IRQ_ENABLE
comma
id|LPT_CONTROL
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: par96 at iobase 0x%lx irq %u options 0x%x&bslash;n&quot;
comma
id|bc_drvname
comma
id|dev-&gt;base_addr
comma
id|dev-&gt;irq
comma
id|bc-&gt;options
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|par96_close
r_static
r_int
id|par96_close
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|baycom_state
op_star
id|bc
op_assign
(paren
r_struct
id|baycom_state
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|bc
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* disable interrupt */
id|outb
c_func
(paren
l_int|0
comma
id|LPT_CONTROL
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
multiline_comment|/*bc-&gt;pdev-&gt;port-&gt;ops-&gt;disable_irq(bc-&gt;pdev-&gt;port);  not yet implemented */
multiline_comment|/* switch off PTT */
id|outb
c_func
(paren
id|PAR96_PTT
op_or
id|PAR97_POWER
comma
id|LPT_DATA
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|parport_release
c_func
(paren
id|bc-&gt;pdev
)paren
suffix:semicolon
id|parport_unregister_device
c_func
(paren
id|bc-&gt;pdev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: close par96 at iobase 0x%lx irq %u&bslash;n&quot;
comma
id|bc_drvname
comma
id|dev-&gt;base_addr
comma
id|dev-&gt;irq
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
multiline_comment|/*&n; * ===================== hdlcdrv driver interface =========================&n; */
r_static
r_int
id|baycom_ioctl
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|ifreq
op_star
id|ifr
comma
r_struct
id|hdlcdrv_ioctl
op_star
id|hi
comma
r_int
id|cmd
)paren
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|variable|par96_ops
r_static
r_struct
id|hdlcdrv_ops
id|par96_ops
op_assign
(brace
id|bc_drvname
comma
id|bc_drvinfo
comma
id|par96_open
comma
id|par96_close
comma
id|baycom_ioctl
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|baycom_setmode
r_static
r_int
id|baycom_setmode
c_func
(paren
r_struct
id|baycom_state
op_star
id|bc
comma
r_const
r_char
op_star
id|modestr
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|modestr
comma
l_string|&quot;picpar&quot;
comma
l_int|6
)paren
)paren
id|bc-&gt;options
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|modestr
comma
l_string|&quot;par96&quot;
comma
l_int|5
)paren
)paren
id|bc-&gt;options
op_assign
id|BAYCOM_OPTIONS_SOFTDCD
suffix:semicolon
r_else
id|bc-&gt;options
op_assign
op_logical_neg
op_logical_neg
id|strchr
c_func
(paren
id|modestr
comma
l_char|&squot;*&squot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|baycom_ioctl
r_static
r_int
id|baycom_ioctl
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|ifreq
op_star
id|ifr
comma
r_struct
id|hdlcdrv_ioctl
op_star
id|hi
comma
r_int
id|cmd
)paren
(brace
r_struct
id|baycom_state
op_star
id|bc
suffix:semicolon
r_struct
id|baycom_ioctl
id|bi
suffix:semicolon
r_int
id|cmd2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_logical_neg
id|dev-&gt;priv
op_logical_or
(paren
(paren
r_struct
id|baycom_state
op_star
)paren
id|dev-&gt;priv
)paren
op_member_access_from_pointer
id|hdrv.magic
op_ne
id|HDLCDRV_MAGIC
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;bc_ioctl: invalid device struct&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|bc
op_assign
(paren
r_struct
id|baycom_state
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_ne
id|SIOCDEVPRIVATE
)paren
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|cmd2
comma
(paren
r_int
op_star
)paren
id|ifr-&gt;ifr_data
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_switch
c_cond
(paren
id|hi-&gt;cmd
)paren
(brace
r_default
suffix:colon
r_break
suffix:semicolon
r_case
id|HDLCDRVCTL_GETMODE
suffix:colon
id|strcpy
c_func
(paren
id|hi-&gt;data.modename
comma
id|bc-&gt;options
ques
c_cond
l_string|&quot;par96&quot;
suffix:colon
l_string|&quot;picpar&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|ifr-&gt;ifr_data
comma
id|hi
comma
r_sizeof
(paren
r_struct
id|hdlcdrv_ioctl
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|HDLCDRVCTL_SETMODE
suffix:colon
r_if
c_cond
(paren
id|dev-&gt;start
op_logical_or
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
id|hi-&gt;data.modename
(braket
r_sizeof
(paren
id|hi-&gt;data.modename
)paren
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_return
id|baycom_setmode
c_func
(paren
id|bc
comma
id|hi-&gt;data.modename
)paren
suffix:semicolon
r_case
id|HDLCDRVCTL_MODELIST
suffix:colon
id|strcpy
c_func
(paren
id|hi-&gt;data.modename
comma
l_string|&quot;par96,picpar&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|ifr-&gt;ifr_data
comma
id|hi
comma
r_sizeof
(paren
r_struct
id|hdlcdrv_ioctl
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|HDLCDRVCTL_MODEMPARMASK
suffix:colon
r_return
id|HDLCDRV_PARMASK_IOBASE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|bi
comma
id|ifr-&gt;ifr_data
comma
r_sizeof
(paren
id|bi
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_switch
c_cond
(paren
id|bi.cmd
)paren
(brace
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
macro_line|#ifdef BAYCOM_DEBUG
r_case
id|BAYCOMCTL_GETDEBUG
suffix:colon
id|bi.data.dbg.debug1
op_assign
id|bc-&gt;hdrv.ptt_keyed
suffix:semicolon
id|bi.data.dbg.debug2
op_assign
id|bc-&gt;debug_vals.last_intcnt
suffix:semicolon
id|bi.data.dbg.debug3
op_assign
id|bc-&gt;debug_vals.last_pllcorr
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* BAYCOM_DEBUG */
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|ifr-&gt;ifr_data
comma
op_amp
id|bi
comma
r_sizeof
(paren
id|bi
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|baycom_par_init
c_func
(paren
r_void
)paren
)paren
(brace
r_int
id|i
comma
id|j
comma
id|found
op_assign
l_int|0
suffix:semicolon
r_char
id|set_hw
op_assign
l_int|1
suffix:semicolon
r_struct
id|baycom_state
op_star
id|bc
suffix:semicolon
r_char
id|ifname
(braket
id|HDLCDRV_IFNAMELEN
)braket
suffix:semicolon
id|printk
c_func
(paren
id|bc_drvinfo
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * register net devices&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_PORTS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
id|baycom_device
op_plus
id|i
suffix:semicolon
id|sprintf
c_func
(paren
id|ifname
comma
l_string|&quot;bcp%d&quot;
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|baycom_ports
(braket
id|i
)braket
dot
id|mode
)paren
id|set_hw
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|set_hw
)paren
id|baycom_ports
(braket
id|i
)braket
dot
id|iobase
op_assign
l_int|0
suffix:semicolon
id|j
op_assign
id|hdlcdrv_register_hdlcdrv
c_func
(paren
id|dev
comma
op_amp
id|par96_ops
comma
r_sizeof
(paren
r_struct
id|baycom_state
)paren
comma
id|ifname
comma
id|baycom_ports
(braket
id|i
)braket
dot
id|iobase
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|j
)paren
(brace
id|bc
op_assign
(paren
r_struct
id|baycom_state
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|set_hw
op_logical_and
id|baycom_setmode
c_func
(paren
id|bc
comma
id|baycom_ports
(braket
id|i
)braket
dot
id|mode
)paren
)paren
id|set_hw
op_assign
l_int|0
suffix:semicolon
id|found
op_increment
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: cannot register net device&bslash;n&quot;
comma
id|bc_drvname
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
macro_line|#ifdef MODULE
multiline_comment|/*&n; * command line settable parameters&n; */
DECL|variable|mode
r_static
r_const
r_char
op_star
id|mode
(braket
id|NR_PORTS
)braket
op_assign
(brace
l_string|&quot;picpar&quot;
comma
)brace
suffix:semicolon
DECL|variable|iobase
r_static
r_int
id|iobase
(braket
id|NR_PORTS
)braket
op_assign
(brace
l_int|0x378
comma
)brace
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x20115
id|MODULE_PARM
c_func
(paren
id|mode
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|NR_PORTS
)paren
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|mode
comma
l_string|&quot;baycom operating mode; eg. par96 or picpar&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|iobase
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|NR_PORTS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|iobase
comma
l_string|&quot;baycom io base address&quot;
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Thomas M. Sailer, sailer@ife.ee.ethz.ch, hb9jnx@hb9w.che.eu&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Baycom par96 and picpar amateur radio modem driver&quot;
)paren
suffix:semicolon
macro_line|#endif
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|init_module
c_func
(paren
r_void
)paren
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
id|NR_PORTS
)paren
op_logical_and
(paren
id|mode
(braket
id|i
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|baycom_ports
(braket
id|i
)braket
dot
id|mode
op_assign
id|mode
(braket
id|i
)braket
suffix:semicolon
id|baycom_ports
(braket
id|i
)braket
dot
id|iobase
op_assign
id|iobase
(braket
id|i
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OL
id|NR_PORTS
op_minus
l_int|1
)paren
id|baycom_ports
(braket
id|i
op_plus
l_int|1
)braket
dot
id|mode
op_assign
l_int|NULL
suffix:semicolon
r_return
id|baycom_par_init
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
id|NR_PORTS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
id|baycom_device
op_plus
id|i
suffix:semicolon
r_struct
id|baycom_state
op_star
id|bc
op_assign
(paren
r_struct
id|baycom_state
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_if
c_cond
(paren
id|bc
)paren
(brace
r_if
c_cond
(paren
id|bc-&gt;hdrv.magic
op_ne
id|HDLCDRV_MAGIC
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;baycom: invalid magic in &quot;
l_string|&quot;cleanup_module&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|hdlcdrv_unregister_hdlcdrv
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#else /* MODULE */
multiline_comment|/* --------------------------------------------------------------------- */
multiline_comment|/*&n; * format: baycom_par=io,mode&n; * mode: par96,picpar&n; */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|baycom_par_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
id|NR_PORTS
)paren
op_logical_and
(paren
id|baycom_ports
(braket
id|i
)braket
dot
id|mode
)paren
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_ge
id|NR_PORTS
)paren
op_logical_or
(paren
id|ints
(braket
l_int|0
)braket
OL
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: too many or invalid interface &quot;
l_string|&quot;specifications&bslash;n&quot;
comma
id|bc_drvname
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|baycom_ports
(braket
id|i
)braket
dot
id|mode
op_assign
id|str
suffix:semicolon
id|baycom_ports
(braket
id|i
)braket
dot
id|iobase
op_assign
id|ints
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|NR_PORTS
op_minus
l_int|1
)paren
id|baycom_ports
(braket
id|i
op_plus
l_int|1
)braket
dot
id|mode
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
multiline_comment|/* --------------------------------------------------------------------- */
eof