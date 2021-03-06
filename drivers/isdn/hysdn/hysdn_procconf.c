multiline_comment|/* $Id: hysdn_procconf.c,v 1.8 2000/11/13 22:51:47 kai Exp $&n;&n; * Linux driver for HYSDN cards, /proc/net filesystem dir and conf functions.&n; * written by Werner Cornelius (werner@titro.de) for Hypercope GmbH&n; *&n; * Copyright 1999  by Werner Cornelius (werner@titro.de)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &quot;hysdn_defs.h&quot;
DECL|variable|hysdn_procconf_revision
r_static
r_char
op_star
id|hysdn_procconf_revision
op_assign
l_string|&quot;$Revision: 1.8 $&quot;
suffix:semicolon
DECL|macro|INFO_OUT_LEN
mdefine_line|#define INFO_OUT_LEN 80&t;&t;/* length of info line including lf */
multiline_comment|/********************************************************/
multiline_comment|/* defines and data structure for conf write operations */
multiline_comment|/********************************************************/
DECL|macro|CONF_STATE_DETECT
mdefine_line|#define CONF_STATE_DETECT 0&t;/* waiting for detect */
DECL|macro|CONF_STATE_CONF
mdefine_line|#define CONF_STATE_CONF   1&t;/* writing config data */
DECL|macro|CONF_STATE_POF
mdefine_line|#define CONF_STATE_POF    2&t;/* writing pof data */
DECL|macro|CONF_LINE_LEN
mdefine_line|#define CONF_LINE_LEN    80&t;/* 80 chars max */
DECL|struct|conf_writedata
r_struct
id|conf_writedata
(brace
DECL|member|card
id|hysdn_card
op_star
id|card
suffix:semicolon
multiline_comment|/* card the device is connected to */
DECL|member|buf_size
r_int
id|buf_size
suffix:semicolon
multiline_comment|/* actual number of bytes in the buffer */
DECL|member|needed_size
r_int
id|needed_size
suffix:semicolon
multiline_comment|/* needed size when reading pof */
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* actual interface states from above constants */
DECL|member|conf_line
id|uchar
id|conf_line
(braket
id|CONF_LINE_LEN
)braket
suffix:semicolon
multiline_comment|/* buffered conf line */
DECL|member|channel
id|word
id|channel
suffix:semicolon
multiline_comment|/* active channel number */
DECL|member|pof_buffer
id|uchar
op_star
id|pof_buffer
suffix:semicolon
multiline_comment|/* buffer when writing pof */
)brace
suffix:semicolon
multiline_comment|/***********************************************************************/
multiline_comment|/* process_line parses one config line and transfers it to the card if */
multiline_comment|/* necessary.                                                          */
multiline_comment|/* if the return value is negative an error occured.                   */
multiline_comment|/***********************************************************************/
r_static
r_int
DECL|function|process_line
id|process_line
c_func
(paren
r_struct
id|conf_writedata
op_star
id|cnf
)paren
(brace
id|uchar
op_star
id|cp
op_assign
id|cnf-&gt;conf_line
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|cnf-&gt;card-&gt;debug_flags
op_amp
id|LOG_CNF_LINE
)paren
id|hysdn_addlog
c_func
(paren
id|cnf-&gt;card
comma
l_string|&quot;conf line: %s&quot;
comma
id|cp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;-&squot;
)paren
(brace
multiline_comment|/* option */
id|cp
op_increment
suffix:semicolon
multiline_comment|/* point to option char */
r_if
c_cond
(paren
op_star
id|cp
op_increment
op_ne
l_char|&squot;c&squot;
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* option unknown or used */
id|i
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* start value for channel */
r_while
c_loop
(paren
(paren
op_star
id|cp
op_le
l_char|&squot;9&squot;
)paren
op_logical_and
(paren
op_star
id|cp
op_ge
l_char|&squot;0&squot;
)paren
)paren
id|i
op_assign
id|i
op_star
l_int|10
op_plus
op_star
id|cp
op_increment
op_minus
l_char|&squot;0&squot;
suffix:semicolon
multiline_comment|/* get decimal number */
r_if
c_cond
(paren
id|i
OG
l_int|65535
)paren
(brace
r_if
c_cond
(paren
id|cnf-&gt;card-&gt;debug_flags
op_amp
id|LOG_CNF_MISC
)paren
id|hysdn_addlog
c_func
(paren
id|cnf-&gt;card
comma
l_string|&quot;conf channel invalid  %d&quot;
comma
id|i
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ERR_INV_CHAN
)paren
suffix:semicolon
multiline_comment|/* invalid channel */
)brace
id|cnf-&gt;channel
op_assign
id|i
op_amp
l_int|0xFFFF
suffix:semicolon
multiline_comment|/* set new channel number */
r_return
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* success */
)brace
multiline_comment|/* option */
r_if
c_cond
(paren
op_star
id|cp
op_eq
l_char|&squot;*&squot;
)paren
(brace
multiline_comment|/* line to send */
r_if
c_cond
(paren
id|cnf-&gt;card-&gt;debug_flags
op_amp
id|LOG_CNF_DATA
)paren
id|hysdn_addlog
c_func
(paren
id|cnf-&gt;card
comma
l_string|&quot;conf chan=%d %s&quot;
comma
id|cnf-&gt;channel
comma
id|cp
)paren
suffix:semicolon
r_return
(paren
id|hysdn_tx_cfgline
c_func
(paren
id|cnf-&gt;card
comma
id|cnf-&gt;conf_line
op_plus
l_int|1
comma
id|cnf-&gt;channel
)paren
)paren
suffix:semicolon
multiline_comment|/* send the line without * */
)brace
multiline_comment|/* line to send */
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* process_line */
multiline_comment|/*************************/
multiline_comment|/* dummy file operations */
multiline_comment|/*************************/
r_static
id|loff_t
DECL|function|hysdn_dummy_lseek
id|hysdn_dummy_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|orig
)paren
(brace
r_return
op_minus
id|ESPIPE
suffix:semicolon
)brace
multiline_comment|/* hysdn_dummy_lseek */
multiline_comment|/***********************************/
multiline_comment|/* conf file operations and tables */
multiline_comment|/***********************************/
multiline_comment|/****************************************************/
multiline_comment|/* write conf file -&gt; boot or send cfg line to card */
multiline_comment|/****************************************************/
r_static
id|ssize_t
DECL|function|hysdn_conf_write
id|hysdn_conf_write
c_func
(paren
r_struct
id|file
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
comma
id|loff_t
op_star
id|off
)paren
(brace
r_struct
id|conf_writedata
op_star
id|cnf
suffix:semicolon
r_int
id|i
suffix:semicolon
id|uchar
id|ch
comma
op_star
id|cp
suffix:semicolon
r_if
c_cond
(paren
op_amp
id|file-&gt;f_pos
op_ne
id|off
)paren
multiline_comment|/* fs error check */
r_return
(paren
op_minus
id|ESPIPE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* nothing to handle */
r_if
c_cond
(paren
op_logical_neg
(paren
id|cnf
op_assign
id|file-&gt;private_data
)paren
)paren
r_return
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
multiline_comment|/* should never happen */
r_if
c_cond
(paren
id|cnf-&gt;state
op_eq
id|CONF_STATE_DETECT
)paren
(brace
multiline_comment|/* auto detect cnf or pof data */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|ch
comma
id|buf
comma
l_int|1
)paren
)paren
multiline_comment|/* get first char for detect */
r_return
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ch
op_eq
l_int|0x1A
)paren
(brace
multiline_comment|/* we detected a pof file */
r_if
c_cond
(paren
(paren
id|cnf-&gt;needed_size
op_assign
id|pof_write_open
c_func
(paren
id|cnf-&gt;card
comma
op_amp
id|cnf-&gt;pof_buffer
)paren
)paren
op_le
l_int|0
)paren
r_return
(paren
id|cnf-&gt;needed_size
)paren
suffix:semicolon
multiline_comment|/* an error occured -&gt; exit */
id|cnf-&gt;buf_size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* buffer is empty */
id|cnf-&gt;state
op_assign
id|CONF_STATE_POF
suffix:semicolon
multiline_comment|/* new state */
)brace
r_else
(brace
multiline_comment|/* conf data has been detected */
id|cnf-&gt;buf_size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* buffer is empty */
id|cnf-&gt;state
op_assign
id|CONF_STATE_CONF
suffix:semicolon
multiline_comment|/* requested conf data write */
r_if
c_cond
(paren
id|cnf-&gt;card-&gt;state
op_ne
id|CARD_STATE_RUN
)paren
r_return
(paren
op_minus
id|ERR_NOT_BOOTED
)paren
suffix:semicolon
id|cnf-&gt;conf_line
(braket
id|CONF_LINE_LEN
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* limit string length */
id|cnf-&gt;channel
op_assign
l_int|4098
suffix:semicolon
multiline_comment|/* default channel for output */
)brace
)brace
multiline_comment|/* state was auto detect */
r_if
c_cond
(paren
id|cnf-&gt;state
op_eq
id|CONF_STATE_POF
)paren
(brace
multiline_comment|/* pof write active */
id|i
op_assign
id|cnf-&gt;needed_size
op_minus
id|cnf-&gt;buf_size
suffix:semicolon
multiline_comment|/* bytes still missing for write */
r_if
c_cond
(paren
id|i
op_le
l_int|0
)paren
r_return
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* size error handling pof */
r_if
c_cond
(paren
id|i
OL
id|count
)paren
id|count
op_assign
id|i
suffix:semicolon
multiline_comment|/* limit requested number of bytes */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|cnf-&gt;pof_buffer
op_plus
id|cnf-&gt;buf_size
comma
id|buf
comma
id|count
)paren
)paren
r_return
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
multiline_comment|/* error while copying */
id|cnf-&gt;buf_size
op_add_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|cnf-&gt;needed_size
op_eq
id|cnf-&gt;buf_size
)paren
(brace
id|cnf-&gt;needed_size
op_assign
id|pof_write_buffer
c_func
(paren
id|cnf-&gt;card
comma
id|cnf-&gt;buf_size
)paren
suffix:semicolon
multiline_comment|/* write data */
r_if
c_cond
(paren
id|cnf-&gt;needed_size
op_le
l_int|0
)paren
(brace
id|cnf-&gt;card-&gt;state
op_assign
id|CARD_STATE_BOOTERR
suffix:semicolon
multiline_comment|/* show boot error */
r_return
(paren
id|cnf-&gt;needed_size
)paren
suffix:semicolon
multiline_comment|/* an error occured */
)brace
id|cnf-&gt;buf_size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* buffer is empty again */
)brace
)brace
multiline_comment|/* pof write active */
r_else
(brace
multiline_comment|/* conf write active */
r_if
c_cond
(paren
id|cnf-&gt;card-&gt;state
op_ne
id|CARD_STATE_RUN
)paren
(brace
r_if
c_cond
(paren
id|cnf-&gt;card-&gt;debug_flags
op_amp
id|LOG_CNF_MISC
)paren
id|hysdn_addlog
c_func
(paren
id|cnf-&gt;card
comma
l_string|&quot;cnf write denied -&gt; not booted&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ERR_NOT_BOOTED
)paren
suffix:semicolon
)brace
id|i
op_assign
(paren
id|CONF_LINE_LEN
op_minus
l_int|1
)paren
op_minus
id|cnf-&gt;buf_size
suffix:semicolon
multiline_comment|/* bytes available in buffer */
r_if
c_cond
(paren
id|i
OG
l_int|0
)paren
(brace
multiline_comment|/* copy remaining bytes into buffer */
r_if
c_cond
(paren
id|count
OG
id|i
)paren
id|count
op_assign
id|i
suffix:semicolon
multiline_comment|/* limit transfer */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|cnf-&gt;conf_line
op_plus
id|cnf-&gt;buf_size
comma
id|buf
comma
id|count
)paren
)paren
r_return
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
multiline_comment|/* error while copying */
id|i
op_assign
id|count
suffix:semicolon
multiline_comment|/* number of chars in buffer */
id|cp
op_assign
id|cnf-&gt;conf_line
op_plus
id|cnf-&gt;buf_size
suffix:semicolon
r_while
c_loop
(paren
id|i
)paren
(brace
multiline_comment|/* search for end of line */
r_if
c_cond
(paren
(paren
op_star
id|cp
OL
l_char|&squot; &squot;
)paren
op_logical_and
(paren
op_star
id|cp
op_ne
l_int|9
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* end of line found */
id|cp
op_increment
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
multiline_comment|/* search for end of line */
r_if
c_cond
(paren
id|i
)paren
(brace
multiline_comment|/* delimiter found */
op_star
id|cp
op_increment
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* string termination */
id|count
op_sub_assign
(paren
id|i
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* subtract remaining bytes from count */
r_while
c_loop
(paren
(paren
id|i
)paren
op_logical_and
(paren
op_star
id|cp
OL
l_char|&squot; &squot;
)paren
op_logical_and
(paren
op_star
id|cp
op_ne
l_int|9
)paren
)paren
(brace
id|i
op_decrement
suffix:semicolon
multiline_comment|/* discard next char */
id|count
op_increment
suffix:semicolon
multiline_comment|/* mark as read */
id|cp
op_increment
suffix:semicolon
multiline_comment|/* next char */
)brace
id|cnf-&gt;buf_size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* buffer is empty after transfer */
r_if
c_cond
(paren
(paren
id|i
op_assign
id|process_line
c_func
(paren
id|cnf
)paren
)paren
OL
l_int|0
)paren
multiline_comment|/* handle the line */
id|count
op_assign
id|i
suffix:semicolon
multiline_comment|/* return the error */
)brace
multiline_comment|/* delimiter found */
r_else
(brace
id|cnf-&gt;buf_size
op_add_assign
id|count
suffix:semicolon
multiline_comment|/* add chars to string */
r_if
c_cond
(paren
id|cnf-&gt;buf_size
op_ge
id|CONF_LINE_LEN
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|cnf-&gt;card-&gt;debug_flags
op_amp
id|LOG_CNF_MISC
)paren
id|hysdn_addlog
c_func
(paren
id|cnf-&gt;card
comma
l_string|&quot;cnf line too long %d chars pos %d&quot;
comma
id|cnf-&gt;buf_size
comma
id|count
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ERR_CONF_LONG
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* not delimited */
)brace
multiline_comment|/* copy remaining bytes into buffer */
r_else
(brace
r_if
c_cond
(paren
id|cnf-&gt;card-&gt;debug_flags
op_amp
id|LOG_CNF_MISC
)paren
id|hysdn_addlog
c_func
(paren
id|cnf-&gt;card
comma
l_string|&quot;cnf line too long&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ERR_CONF_LONG
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* conf write active */
r_return
(paren
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/* hysdn_conf_write */
multiline_comment|/*******************************************/
multiline_comment|/* read conf file -&gt; output card info data */
multiline_comment|/*******************************************/
r_static
id|ssize_t
DECL|function|hysdn_conf_read
id|hysdn_conf_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|off
)paren
(brace
r_char
op_star
id|cp
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|off
op_ne
op_amp
id|file-&gt;f_pos
)paren
multiline_comment|/* fs error check */
r_return
op_minus
id|ESPIPE
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
id|FMODE_READ
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|cp
op_assign
id|file-&gt;private_data
)paren
)paren
r_return
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
multiline_comment|/* should never happen */
id|i
op_assign
id|strlen
c_func
(paren
id|cp
)paren
suffix:semicolon
multiline_comment|/* get total string length */
r_if
c_cond
(paren
op_star
id|off
OL
id|i
)paren
(brace
multiline_comment|/* still bytes to transfer */
id|cp
op_add_assign
op_star
id|off
suffix:semicolon
multiline_comment|/* point to desired data offset */
id|i
op_sub_assign
op_star
id|off
suffix:semicolon
multiline_comment|/* remaining length */
r_if
c_cond
(paren
id|i
OG
id|count
)paren
id|i
op_assign
id|count
suffix:semicolon
multiline_comment|/* limit length to transfer */
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|cp
comma
id|i
)paren
)paren
r_return
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
multiline_comment|/* copy error */
op_star
id|off
op_add_assign
id|i
suffix:semicolon
multiline_comment|/* adjust offset */
)brace
r_else
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
r_return
(paren
op_minus
id|EPERM
)paren
suffix:semicolon
multiline_comment|/* no permission to read */
r_return
(paren
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/* hysdn_conf_read */
multiline_comment|/******************/
multiline_comment|/* open conf file */
multiline_comment|/******************/
r_static
r_int
DECL|function|hysdn_conf_open
id|hysdn_conf_open
c_func
(paren
r_struct
id|inode
op_star
id|ino
comma
r_struct
id|file
op_star
id|filep
)paren
(brace
id|hysdn_card
op_star
id|card
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|pd
suffix:semicolon
r_struct
id|conf_writedata
op_star
id|cnf
suffix:semicolon
r_char
op_star
id|cp
comma
op_star
id|tmp
suffix:semicolon
multiline_comment|/* now search the addressed card */
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|card
op_assign
id|card_root
suffix:semicolon
r_while
c_loop
(paren
id|card
)paren
(brace
id|pd
op_assign
id|card-&gt;procconf
suffix:semicolon
r_if
c_cond
(paren
id|pd-&gt;low_ino
op_eq
(paren
id|ino-&gt;i_ino
op_amp
l_int|0xFFFF
)paren
)paren
r_break
suffix:semicolon
id|card
op_assign
id|card-&gt;next
suffix:semicolon
multiline_comment|/* search next entry */
)brace
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
multiline_comment|/* device is unknown/invalid */
)brace
r_if
c_cond
(paren
id|card-&gt;debug_flags
op_amp
(paren
id|LOG_PROC_OPEN
op_or
id|LOG_PROC_ALL
)paren
)paren
id|hysdn_addlog
c_func
(paren
id|card
comma
l_string|&quot;config open for uid=%d gid=%d mode=0x%x&quot;
comma
id|filep-&gt;f_uid
comma
id|filep-&gt;f_gid
comma
id|filep-&gt;f_mode
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|filep-&gt;f_mode
op_amp
(paren
id|FMODE_READ
op_or
id|FMODE_WRITE
)paren
)paren
op_eq
id|FMODE_WRITE
)paren
(brace
multiline_comment|/* write only access -&gt; write boot file or conf line */
r_if
c_cond
(paren
op_logical_neg
(paren
id|cnf
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|conf_writedata
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
)brace
id|cnf-&gt;card
op_assign
id|card
suffix:semicolon
id|cnf-&gt;buf_size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* nothing buffered */
id|cnf-&gt;state
op_assign
id|CONF_STATE_DETECT
suffix:semicolon
multiline_comment|/* start auto detect */
id|filep-&gt;private_data
op_assign
id|cnf
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|filep-&gt;f_mode
op_amp
(paren
id|FMODE_READ
op_or
id|FMODE_WRITE
)paren
)paren
op_eq
id|FMODE_READ
)paren
(brace
multiline_comment|/* read access -&gt; output card info data */
r_if
c_cond
(paren
op_logical_neg
(paren
id|tmp
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|INFO_OUT_LEN
op_star
l_int|2
op_plus
l_int|2
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
multiline_comment|/* out of memory */
)brace
id|filep-&gt;private_data
op_assign
id|tmp
suffix:semicolon
multiline_comment|/* start of string */
multiline_comment|/* first output a headline */
id|sprintf
c_func
(paren
id|tmp
comma
l_string|&quot;id bus slot type irq iobase dp-mem     b-chans fax-chans state device&quot;
)paren
suffix:semicolon
id|cp
op_assign
id|tmp
suffix:semicolon
multiline_comment|/* start of string */
r_while
c_loop
(paren
op_star
id|cp
)paren
id|cp
op_increment
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
id|cp
op_minus
id|tmp
)paren
op_mod
(paren
id|INFO_OUT_LEN
op_plus
l_int|1
)paren
)paren
op_ne
id|INFO_OUT_LEN
)paren
op_star
id|cp
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
op_star
id|cp
op_increment
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
multiline_comment|/* and now the data */
id|sprintf
c_func
(paren
id|cp
comma
l_string|&quot;%d  %3d %4d %4d %3d 0x%04x 0x%08lx %7d %9d %3d   %s&quot;
comma
id|card-&gt;myid
comma
id|card-&gt;bus
comma
id|PCI_SLOT
c_func
(paren
id|card-&gt;devfn
)paren
comma
id|card-&gt;brdtype
comma
id|card-&gt;irq
comma
id|card-&gt;iobase
comma
id|card-&gt;membase
comma
id|card-&gt;bchans
comma
id|card-&gt;faxchans
comma
id|card-&gt;state
comma
id|hysdn_net_getname
c_func
(paren
id|card
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|cp
)paren
id|cp
op_increment
suffix:semicolon
r_while
c_loop
(paren
(paren
(paren
id|cp
op_minus
id|tmp
)paren
op_mod
(paren
id|INFO_OUT_LEN
op_plus
l_int|1
)paren
)paren
op_ne
id|INFO_OUT_LEN
)paren
op_star
id|cp
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
op_star
id|cp
op_increment
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
op_star
id|cp
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* end of string */
)brace
r_else
(brace
multiline_comment|/* simultaneous read/write access forbidden ! */
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
op_minus
id|EPERM
)paren
suffix:semicolon
multiline_comment|/* no permission this time */
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* hysdn_conf_open */
multiline_comment|/***************************/
multiline_comment|/* close a config file.    */
multiline_comment|/***************************/
r_static
r_int
DECL|function|hysdn_conf_close
id|hysdn_conf_close
c_func
(paren
r_struct
id|inode
op_star
id|ino
comma
r_struct
id|file
op_star
id|filep
)paren
(brace
id|hysdn_card
op_star
id|card
suffix:semicolon
r_struct
id|conf_writedata
op_star
id|cnf
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|pd
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* search the addressed card */
id|card
op_assign
id|card_root
suffix:semicolon
r_while
c_loop
(paren
id|card
)paren
(brace
id|pd
op_assign
id|card-&gt;procconf
suffix:semicolon
r_if
c_cond
(paren
id|pd-&gt;low_ino
op_eq
(paren
id|ino-&gt;i_ino
op_amp
l_int|0xFFFF
)paren
)paren
r_break
suffix:semicolon
id|card
op_assign
id|card-&gt;next
suffix:semicolon
multiline_comment|/* search next entry */
)brace
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
multiline_comment|/* device is unknown/invalid */
)brace
r_if
c_cond
(paren
id|card-&gt;debug_flags
op_amp
(paren
id|LOG_PROC_OPEN
op_or
id|LOG_PROC_ALL
)paren
)paren
id|hysdn_addlog
c_func
(paren
id|card
comma
l_string|&quot;config close for uid=%d gid=%d mode=0x%x&quot;
comma
id|filep-&gt;f_uid
comma
id|filep-&gt;f_gid
comma
id|filep-&gt;f_mode
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|filep-&gt;f_mode
op_amp
(paren
id|FMODE_READ
op_or
id|FMODE_WRITE
)paren
)paren
op_eq
id|FMODE_WRITE
)paren
(brace
multiline_comment|/* write only access -&gt; write boot file or conf line */
r_if
c_cond
(paren
id|filep-&gt;private_data
)paren
(brace
id|cnf
op_assign
id|filep-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|cnf-&gt;state
op_eq
id|CONF_STATE_POF
)paren
id|retval
op_assign
id|pof_write_close
c_func
(paren
id|cnf-&gt;card
)paren
suffix:semicolon
multiline_comment|/* close the pof write */
id|kfree
c_func
(paren
id|filep-&gt;private_data
)paren
suffix:semicolon
multiline_comment|/* free allocated memory for buffer */
)brace
multiline_comment|/* handle write private data */
)brace
r_else
r_if
c_cond
(paren
(paren
id|filep-&gt;f_mode
op_amp
(paren
id|FMODE_READ
op_or
id|FMODE_WRITE
)paren
)paren
op_eq
id|FMODE_READ
)paren
(brace
multiline_comment|/* read access -&gt; output card info data */
r_if
c_cond
(paren
id|filep-&gt;private_data
)paren
id|kfree
c_func
(paren
id|filep-&gt;private_data
)paren
suffix:semicolon
multiline_comment|/* release memory */
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
(paren
id|retval
)paren
suffix:semicolon
)brace
multiline_comment|/* hysdn_conf_close */
multiline_comment|/******************************************************/
multiline_comment|/* table for conf filesystem functions defined above. */
multiline_comment|/******************************************************/
DECL|variable|conf_fops
r_static
r_struct
id|file_operations
id|conf_fops
op_assign
(brace
id|llseek
suffix:colon
id|hysdn_dummy_lseek
comma
id|read
suffix:colon
id|hysdn_conf_read
comma
id|write
suffix:colon
id|hysdn_conf_write
comma
id|open
suffix:colon
id|hysdn_conf_open
comma
id|release
suffix:colon
id|hysdn_conf_close
comma
)brace
suffix:semicolon
multiline_comment|/*****************************/
multiline_comment|/* hysdn subdir in /proc/net */
multiline_comment|/*****************************/
DECL|variable|hysdn_proc_entry
r_struct
id|proc_dir_entry
op_star
id|hysdn_proc_entry
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*******************************************************************************/
multiline_comment|/* hysdn_procconf_init is called when the module is loaded and after the cards */
multiline_comment|/* have been detected. The needed proc dir and card config files are created.  */
multiline_comment|/* The log init is called at last.                                             */
multiline_comment|/*******************************************************************************/
r_int
DECL|function|hysdn_procconf_init
id|hysdn_procconf_init
c_func
(paren
r_void
)paren
(brace
id|hysdn_card
op_star
id|card
suffix:semicolon
id|uchar
id|conf_name
(braket
l_int|20
)braket
suffix:semicolon
id|hysdn_proc_entry
op_assign
id|create_proc_entry
c_func
(paren
id|PROC_SUBDIR_NAME
comma
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
comma
id|proc_net
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hysdn_proc_entry
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;HYSDN: unable to create hysdn subdir&bslash;n&quot;
)paren
suffix:semicolon
r_return
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|card
op_assign
id|card_root
suffix:semicolon
multiline_comment|/* point to first card */
r_while
c_loop
(paren
id|card
)paren
(brace
id|sprintf
c_func
(paren
id|conf_name
comma
l_string|&quot;%s%d&quot;
comma
id|PROC_CONF_BASENAME
comma
id|card-&gt;myid
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|card-&gt;procconf
op_assign
(paren
r_void
op_star
)paren
id|create_proc_entry
c_func
(paren
id|conf_name
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|hysdn_proc_entry
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
(paren
(paren
r_struct
id|proc_dir_entry
op_star
)paren
id|card-&gt;procconf
)paren
op_member_access_from_pointer
id|proc_fops
op_assign
op_amp
id|conf_fops
suffix:semicolon
(paren
(paren
r_struct
id|proc_dir_entry
op_star
)paren
id|card-&gt;procconf
)paren
op_member_access_from_pointer
id|owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|hysdn_proclog_init
c_func
(paren
id|card
)paren
suffix:semicolon
multiline_comment|/* init the log file entry */
)brace
id|card
op_assign
id|card-&gt;next
suffix:semicolon
multiline_comment|/* next entry */
)brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;HYSDN: procfs Rev. %s initialised&bslash;n&quot;
comma
id|hysdn_getrev
c_func
(paren
id|hysdn_procconf_revision
)paren
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* hysdn_procconf_init */
multiline_comment|/*************************************************************************************/
multiline_comment|/* hysdn_procconf_release is called when the module is unloaded and before the cards */
multiline_comment|/* resources are released. The module counter is assumed to be 0 !                   */
multiline_comment|/*************************************************************************************/
r_void
DECL|function|hysdn_procconf_release
id|hysdn_procconf_release
c_func
(paren
r_void
)paren
(brace
id|hysdn_card
op_star
id|card
suffix:semicolon
id|uchar
id|conf_name
(braket
l_int|20
)braket
suffix:semicolon
id|card
op_assign
id|card_root
suffix:semicolon
multiline_comment|/* start with first card */
r_while
c_loop
(paren
id|card
)paren
(brace
id|sprintf
c_func
(paren
id|conf_name
comma
l_string|&quot;%s%d&quot;
comma
id|PROC_CONF_BASENAME
comma
id|card-&gt;myid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;procconf
)paren
id|remove_proc_entry
c_func
(paren
id|conf_name
comma
id|hysdn_proc_entry
)paren
suffix:semicolon
id|hysdn_proclog_release
c_func
(paren
id|card
)paren
suffix:semicolon
multiline_comment|/* init the log file entry */
id|card
op_assign
id|card-&gt;next
suffix:semicolon
multiline_comment|/* point to next card */
)brace
id|remove_proc_entry
c_func
(paren
id|PROC_SUBDIR_NAME
comma
id|proc_net
)paren
suffix:semicolon
)brace
multiline_comment|/* hysdn_procfs_release */
eof
