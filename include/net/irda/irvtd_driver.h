multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irvtd_driver.h&n; * Version:       0.1&n; * &n; *     Copyright (c) 1998, Takahide Higuchi &lt;thiguchi@pluto.dti.ne.jp&gt;, &n; *     All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     I, Takahide Higuchi, provide no warranty for any of this software. &n; *     This material is provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;net/irda/irlap.h&gt;
macro_line|#include &lt;net/irda/irlmp.h&gt;
macro_line|#include &lt;net/irda/irttp.h&gt;
DECL|macro|VSP_TYPE_NORMAL
mdefine_line|#define VSP_TYPE_NORMAL   1
DECL|macro|VSP_TYPE_CALLOUT
mdefine_line|#define VSP_TYPE_CALLOUT  2
DECL|macro|IRCOMM_MAJOR
mdefine_line|#define IRCOMM_MAJOR  60;  /* Zero means automatic allocation&n;                              60,61,62,and 63 is reserved for experiment */
DECL|macro|IRVTD_MINOR
mdefine_line|#define IRVTD_MINOR 64
DECL|macro|IRVTD_CALLOUT_MINOR
mdefine_line|#define IRVTD_CALLOUT_MINOR 32
DECL|macro|IRVTD_TYPE_NORMAL
mdefine_line|#define IRVTD_TYPE_NORMAL 11
DECL|macro|IRVTD_TYPE_CALLOUT
mdefine_line|#define IRVTD_TYPE_CALLOUT 12
DECL|macro|IRCOMM_HEADER
mdefine_line|#define IRCOMM_HEADER 1       
DECL|macro|IRCOMM_RESERVE
mdefine_line|#define IRCOMM_RESERVE LAP_HEADER+LMP_HEADER+TTP_HEADER+IRCOMM_HEADER
multiline_comment|/*&n; * Definitions for ircomm_cb_struct flags field&n; *  this section is &quot;stolen&quot; from linux-kernel (drivers/char/serial.c)&n; */
DECL|macro|IRVTD_ASYNC_HUP_NOTIFY
mdefine_line|#define IRVTD_ASYNC_HUP_NOTIFY 0x0001 /* Notify getty on hangups and closes &n;&t;&t;&t;&t;   on the callout port */
multiline_comment|/* #define IRVTD_ASYNC_FOURPORT  0x0002 */
multiline_comment|/* Set OU1, OUT2 per AST Fourport settings */
DECL|macro|IRVTD_ASYNC_SAK
mdefine_line|#define IRVTD_ASYNC_SAK&t;0x0004&t;/* Secure Attention Key (Orange book) */
DECL|macro|IRVTD_ASYNC_SPLIT_TERMIOS
mdefine_line|#define IRVTD_ASYNC_SPLIT_TERMIOS 0x0008 /* Separate termios for dialin/callout */
DECL|macro|IRVTD_ASYNC_SPD_MASK
mdefine_line|#define IRVTD_ASYNC_SPD_MASK&t;0x0030
DECL|macro|IRVTD_ASYNC_SPD_HI
mdefine_line|#define IRVTD_ASYNC_SPD_HI&t;0x0010&t;/* Use 56000 instead of 38400 bps */
DECL|macro|IRVTD_ASYNC_SPD_VHI
mdefine_line|#define IRVTD_ASYNC_SPD_VHI&t;0x0020  /* Use 115200 instead of 38400 bps */
DECL|macro|IRVTD_ASYNC_SPD_CUST
mdefine_line|#define IRVTD_ASYNC_SPD_CUST&t;0x0030  /* Use user-specified divisor */
DECL|macro|IRVTD_ASYNC_SKIP_TEST
mdefine_line|#define IRVTD_ASYNC_SKIP_TEST&t;0x0040  /* Skip UART test during autoconfiguration */
DECL|macro|IRVTD_ASYNC_AUTO_IRQ
mdefine_line|#define IRVTD_ASYNC_AUTO_IRQ    0x0080  /* Do automatic IRQ during autoconfiguration */
DECL|macro|IRVTD_ASYNC_SESSION_LOCKOUT
mdefine_line|#define IRVTD_ASYNC_SESSION_LOCKOUT 0x0100 /* Lock out cua opens based on session */
DECL|macro|IRVTD_ASYNC_PGRP_LOCKOUT
mdefine_line|#define IRVTD_ASYNC_PGRP_LOCKOUT    0x0200  /* Lock out cua opens based on pgrp */
DECL|macro|IRVTD_ASYNC_CALLOUT_NOHUP
mdefine_line|#define IRVTD_ASYNC_CALLOUT_NOHUP   0x0400 /* Don&squot;t do hangups for cua device */
DECL|macro|IRVTD_ASYNC_FLAGS
mdefine_line|#define IRVTD_ASYNC_FLAGS&t;0x0FFF&t;/* Possible legal async flags */
DECL|macro|IRVTD_ASYNC_USR_MASK
mdefine_line|#define IRVTD_ASYNC_USR_MASK 0x0430&t;/* Legal flags that non-privileged&n;&t;&t;&t;&t; * users can set or reset */
multiline_comment|/* Internal flags used only by kernel/chr_drv/serial.c */
DECL|macro|IRVTD_ASYNC_INITIALIZED
mdefine_line|#define IRVTD_ASYNC_INITIALIZED&t;0x80000000 /* Serial port was initialized */
DECL|macro|IRVTD_ASYNC_CALLOUT_ACTIVE
mdefine_line|#define IRVTD_ASYNC_CALLOUT_ACTIVE&t;0x40000000 /* Call out device is active */
DECL|macro|IRVTD_ASYNC_NORMAL_ACTIVE
mdefine_line|#define IRVTD_ASYNC_NORMAL_ACTIVE&t;0x20000000 /* Normal device is active */
DECL|macro|IRVTD_ASYNC_BOOT_AUTOCONF
mdefine_line|#define IRVTD_ASYNC_BOOT_AUTOCONF&t;0x10000000 /* Autoconfigure port on bootup */
DECL|macro|IRVTD_ASYNC_CLOSING
mdefine_line|#define IRVTD_ASYNC_CLOSING&t;&t;0x08000000 /* Serial port is closing */
DECL|macro|IRVTD_ASYNC_CTS_FLOW
mdefine_line|#define IRVTD_ASYNC_CTS_FLOW&t;&t;0x04000000 /* Do CTS flow control */
DECL|macro|IRVTD_ASYNC_CHECK_CD
mdefine_line|#define IRVTD_ASYNC_CHECK_CD&t;&t;0x02000000 /* i.e., CLOCAL */
DECL|macro|IRVTD_ASYNC_SHARE_IRQ
mdefine_line|#define IRVTD_ASYNC_SHARE_IRQ&t;&t;0x01000000 /* for multifunction cards */
DECL|macro|IRVTD_ASYNC_CLOSING_WAIT_INF
mdefine_line|#define IRVTD_ASYNC_CLOSING_WAIT_INF  0
DECL|macro|IRVTD_ASYNC_CLOSING_WAIT_NONE
mdefine_line|#define IRVTD_ASYNC_CLOSING_WAIT_NONE 65535
multiline_comment|/**************************************/
DECL|macro|DELTA_DTR
mdefine_line|#define DELTA_DTR 0x01
DECL|macro|DELTA_RTS
mdefine_line|#define DELTA_RTS 0x02
DECL|macro|MCR_DTR
mdefine_line|#define MCR_DTR 0x04
DECL|macro|MCR_RTS
mdefine_line|#define MCR_RTS 0x08
DECL|macro|DELTA_CTS
mdefine_line|#define DELTA_CTS 0x01
DECL|macro|DELTA_DSR
mdefine_line|#define DELTA_DSR 0x02
DECL|macro|DELTA_RI
mdefine_line|#define DELTA_RI  0x04 
DECL|macro|DELTA_DCD
mdefine_line|#define DELTA_DCD 0x08
DECL|macro|MSR_CTS
mdefine_line|#define MSR_CTS   0x10
DECL|macro|MSR_DSR
mdefine_line|#define MSR_DSR   0x20
DECL|macro|MSR_RI
mdefine_line|#define MSR_RI    0x40 
DECL|macro|MSR_DCD
mdefine_line|#define MSR_DCD   0x80
DECL|macro|LSR_OE
mdefine_line|#define LSR_OE     0x02    /* Overrun error indicator */
DECL|macro|LSR_PE
mdefine_line|#define LSR_PE     0x04    /* Parity error indicator */
DECL|macro|LSR_FE
mdefine_line|#define LSR_FE     0x08    /* Frame error indicator */
DECL|macro|LSR_BI
mdefine_line|#define LSR_BI     0x01    /* Break interrupt indicator */
multiline_comment|/**************************************/
r_int
id|irvtd_register_ttydriver
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|irvtd_unregister_ttydriver
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|irvtd_flush_chars
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
eof
