multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irtty.h&n; * Version:       1.0&n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Tue Dec  9 21:13:12 1997&n; * Modified at:   Sun Feb  7 01:57:33 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; *  &n; *     Copyright (c) 1997 Dag Brattli, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#ifndef IRTTY_H
DECL|macro|IRTTY_H
mdefine_line|#define IRTTY_H
macro_line|#include &lt;linux/if.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irqueue.h&gt;
macro_line|#include &lt;net/irda/irda_device.h&gt;
macro_line|#include &lt;net/irda/dongle.h&gt;
DECL|macro|IRTTY_IOC_MAGIC
mdefine_line|#define IRTTY_IOC_MAGIC &squot;e&squot;
DECL|macro|IRTTY_IOCTDONGLE
mdefine_line|#define IRTTY_IOCTDONGLE  _IO(IRTTY_IOC_MAGIC, 1)
DECL|macro|IRTTY_IOC_MAXNR
mdefine_line|#define IRTTY_IOC_MAXNR   1
macro_line|#ifndef N_IRDA
DECL|macro|N_IRDA
mdefine_line|#define N_IRDA         11   /* This one should go in &lt;/asm/termio.h&gt; */
macro_line|#endif
DECL|struct|dongle_q
r_struct
id|dongle_q
(brace
DECL|member|q
id|QUEUE
id|q
suffix:semicolon
DECL|member|dongle
r_struct
id|dongle
op_star
id|dongle
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|irtty_cb
r_struct
id|irtty_cb
(brace
DECL|member|q
id|QUEUE
id|q
suffix:semicolon
multiline_comment|/* Must be first */
multiline_comment|/* &t;char name[16]; */
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
multiline_comment|/* Ptr to TTY structure */
DECL|member|idev
r_struct
id|irda_device
id|idev
suffix:semicolon
DECL|member|dongle_q
r_struct
id|dongle_q
op_star
id|dongle_q
suffix:semicolon
multiline_comment|/* Has this tty got a dongle attached? */
)brace
suffix:semicolon
r_int
id|irtty_register_dongle
c_func
(paren
r_struct
id|dongle
op_star
id|dongle
)paren
suffix:semicolon
r_void
id|irtty_unregister_dongle
c_func
(paren
r_struct
id|dongle
op_star
id|dongle
)paren
suffix:semicolon
r_void
id|irtty_set_dtr_rts
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|dtr
comma
r_int
id|rts
)paren
suffix:semicolon
macro_line|#endif
eof
