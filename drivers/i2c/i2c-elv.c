multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/* i2c-elv.c i2c-hw access for philips style parallel port adapters&t;     */
multiline_comment|/* ------------------------------------------------------------------------- */
multiline_comment|/*   Copyright (C) 1995-99 Simon G. Vogl&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&t;&t;     */
multiline_comment|/* ------------------------------------------------------------------------- &n;&n;/* With some changes from Ky&#xfffd;sti M&#xfffd;lkki &lt;kmalkki@cc.hut.fi&gt; and even&n;   Frodo Looijaard &lt;frodol@dds.nl&gt; */
multiline_comment|/* $Id: i2c-elv.c,v 1.12 1999/12/21 23:45:58 frodo Exp $ */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020135
macro_line|#include &lt;linux/init.h&gt;
macro_line|#else
DECL|macro|__init
mdefine_line|#define __init 
macro_line|#endif
multiline_comment|/* 2.0.0 kernel compatibility */
macro_line|#if LINUX_VERSION_CODE &lt; 0x020100
DECL|macro|MODULE_AUTHOR
mdefine_line|#define MODULE_AUTHOR(noone)
DECL|macro|MODULE_DESCRIPTION
mdefine_line|#define MODULE_DESCRIPTION(none)
DECL|macro|MODULE_PARM
mdefine_line|#define MODULE_PARM(no,param)
DECL|macro|MODULE_PARM_DESC
mdefine_line|#define MODULE_PARM_DESC(no,description)
DECL|macro|EXPORT_SYMBOL
mdefine_line|#define EXPORT_SYMBOL(noexport)
DECL|macro|EXPORT_NO_SYMBOLS
mdefine_line|#define EXPORT_NO_SYMBOLS
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020100
macro_line|#  include &lt;asm/uaccess.h&gt;
macro_line|#else
macro_line|#  include &lt;asm/segment.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
DECL|macro|DEFAULT_BASE
mdefine_line|#define DEFAULT_BASE 0x378
DECL|variable|base
r_static
r_int
id|base
op_assign
l_int|0
suffix:semicolon
DECL|variable|PortData
r_static
r_int
r_char
id|PortData
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* ----- global defines -----------------------------------------------&t;*/
DECL|macro|DEB
mdefine_line|#define DEB(x)&t;&t;/* should be reasonable open, close &amp;c. &t;*/
DECL|macro|DEB2
mdefine_line|#define DEB2(x) &t;/* low level debugging - very slow &t;&t;*/
DECL|macro|DEBE
mdefine_line|#define DEBE(x)&t;x&t;/* error messages &t;&t;&t;&t;*/
DECL|macro|DEBINIT
mdefine_line|#define DEBINIT(x) x&t;/* detection status messages&t;&t;&t;*/
multiline_comment|/* --- Convenience defines for the parallel port:                       */
DECL|macro|BASE
mdefine_line|#define BASE    (unsigned int)(data)
DECL|macro|DATA
mdefine_line|#define DATA    BASE                    /* Centronics data port         */
DECL|macro|STAT
mdefine_line|#define STAT    (BASE+1)                /* Centronics status port       */
DECL|macro|CTRL
mdefine_line|#define CTRL    (BASE+2)                /* Centronics control port      */
multiline_comment|/* ----- local functions ----------------------------------------------&t;*/
DECL|function|bit_elv_setscl
r_static
r_void
id|bit_elv_setscl
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|state
)paren
(brace
r_if
c_cond
(paren
id|state
)paren
(brace
id|PortData
op_and_assign
l_int|0xfe
suffix:semicolon
)brace
r_else
(brace
id|PortData
op_or_assign
l_int|1
suffix:semicolon
)brace
id|outb
c_func
(paren
id|PortData
comma
id|DATA
)paren
suffix:semicolon
)brace
DECL|function|bit_elv_setsda
r_static
r_void
id|bit_elv_setsda
c_func
(paren
r_void
op_star
id|data
comma
r_int
id|state
)paren
(brace
r_if
c_cond
(paren
id|state
)paren
(brace
id|PortData
op_and_assign
l_int|0xfd
suffix:semicolon
)brace
r_else
(brace
id|PortData
op_or_assign
l_int|2
suffix:semicolon
)brace
id|outb
c_func
(paren
id|PortData
comma
id|DATA
)paren
suffix:semicolon
)brace
DECL|function|bit_elv_getscl
r_static
r_int
id|bit_elv_getscl
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
(paren
l_int|0
op_eq
(paren
(paren
id|inb_p
c_func
(paren
id|STAT
)paren
)paren
op_amp
l_int|0x08
)paren
)paren
suffix:semicolon
)brace
DECL|function|bit_elv_getsda
r_static
r_int
id|bit_elv_getsda
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_return
(paren
l_int|0
op_eq
(paren
(paren
id|inb_p
c_func
(paren
id|STAT
)paren
)paren
op_amp
l_int|0x40
)paren
)paren
suffix:semicolon
)brace
DECL|function|bit_elv_init
r_static
r_int
id|bit_elv_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|base
comma
(paren
id|base
op_eq
l_int|0x3bc
)paren
ques
c_cond
l_int|3
suffix:colon
l_int|8
)paren
OL
l_int|0
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* test for ELV adap. &t;*/
r_if
c_cond
(paren
id|inb
c_func
(paren
id|base
op_plus
l_int|1
)paren
op_amp
l_int|0x80
)paren
(brace
multiline_comment|/* BUSY should be high&t;*/
id|DEBINIT
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;i2c-elv.o: Busy was low.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_else
(brace
id|outb
c_func
(paren
l_int|0x0c
comma
id|base
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* SLCT auf low&t;&t;*/
id|udelay
c_func
(paren
l_int|400
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inb
c_func
(paren
id|base
op_plus
l_int|1
)paren
op_logical_and
l_int|0x10
)paren
)paren
(brace
id|outb
c_func
(paren
l_int|0x04
comma
id|base
op_plus
l_int|2
)paren
suffix:semicolon
id|DEBINIT
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;i2c-elv.o: Select was high.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
id|request_region
c_func
(paren
id|base
comma
(paren
id|base
op_eq
l_int|0x3bc
)paren
ques
c_cond
l_int|3
suffix:colon
l_int|8
comma
l_string|&quot;i2c (ELV adapter)&quot;
)paren
suffix:semicolon
id|PortData
op_assign
l_int|0
suffix:semicolon
id|bit_elv_setsda
c_func
(paren
(paren
r_void
op_star
)paren
id|base
comma
l_int|1
)paren
suffix:semicolon
id|bit_elv_setscl
c_func
(paren
(paren
r_void
op_star
)paren
id|base
comma
l_int|1
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bit_elv_exit
r_static
r_void
id|bit_elv_exit
c_func
(paren
r_void
)paren
(brace
id|release_region
c_func
(paren
id|base
comma
(paren
id|base
op_eq
l_int|0x3bc
)paren
ques
c_cond
l_int|3
suffix:colon
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|bit_elv_reg
r_static
r_int
id|bit_elv_reg
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bit_elv_unreg
r_static
r_int
id|bit_elv_unreg
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bit_elv_inc_use
r_static
r_void
id|bit_elv_inc_use
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
macro_line|#ifdef MODULE
id|MOD_INC_USE_COUNT
suffix:semicolon
macro_line|#endif
)brace
DECL|function|bit_elv_dec_use
r_static
r_void
id|bit_elv_dec_use
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
macro_line|#ifdef MODULE
id|MOD_DEC_USE_COUNT
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* ------------------------------------------------------------------------&n; * Encapsulate the above functions in the correct operations structure.&n; * This is only done when more than one hardware adapter is supported.&n; */
DECL|variable|bit_elv_data
r_static
r_struct
id|i2c_algo_bit_data
id|bit_elv_data
op_assign
(brace
l_int|NULL
comma
id|bit_elv_setsda
comma
id|bit_elv_setscl
comma
id|bit_elv_getsda
comma
id|bit_elv_getscl
comma
l_int|80
comma
l_int|80
comma
l_int|100
comma
multiline_comment|/*      waits, timeout */
)brace
suffix:semicolon
DECL|variable|bit_elv_ops
r_static
r_struct
id|i2c_adapter
id|bit_elv_ops
op_assign
(brace
l_string|&quot;ELV Parallel port adaptor&quot;
comma
id|I2C_HW_B_ELV
comma
l_int|NULL
comma
op_amp
id|bit_elv_data
comma
id|bit_elv_inc_use
comma
id|bit_elv_dec_use
comma
id|bit_elv_reg
comma
id|bit_elv_unreg
comma
)brace
suffix:semicolon
DECL|function|i2c_bitelv_init
r_int
id|__init
id|i2c_bitelv_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;i2c-elv.o: i2c ELV parallel port adapter module&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base
op_eq
l_int|0
)paren
(brace
multiline_comment|/* probe some values */
id|base
op_assign
id|DEFAULT_BASE
suffix:semicolon
id|bit_elv_data.data
op_assign
(paren
r_void
op_star
)paren
id|DEFAULT_BASE
suffix:semicolon
r_if
c_cond
(paren
id|bit_elv_init
c_func
(paren
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|i2c_bit_add_bus
c_func
(paren
op_amp
id|bit_elv_ops
)paren
OL
l_int|0
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
r_else
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
r_else
(brace
id|bit_elv_ops.data
op_assign
(paren
r_void
op_star
)paren
id|base
suffix:semicolon
r_if
c_cond
(paren
id|bit_elv_init
c_func
(paren
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|i2c_bit_add_bus
c_func
(paren
op_amp
id|bit_elv_ops
)paren
OL
l_int|0
)paren
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
r_else
(brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;i2c-elv.o: found device at %#x.&bslash;n&quot;
comma
id|base
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|EXPORT_NO_SYMBOLS
suffix:semicolon
macro_line|#ifdef MODULE
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Simon G. Vogl &lt;simon@tk.uni-linz.ac.at&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;I2C-Bus adapter routines for ELV parallel port adapter&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|base
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|i2c_bitelv_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|i2c_bit_del_bus
c_func
(paren
op_amp
id|bit_elv_ops
)paren
suffix:semicolon
id|bit_elv_exit
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
