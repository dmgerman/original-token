multiline_comment|/*********************************************************************&n; *                &n; * Filename:      crc.h&n; * Version:       &n; * Description:   CRC routines&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Mon Aug  4 20:40:53 1997&n; * Modified at:   Sat Dec 12 23:09:29 1998&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; ********************************************************************/
macro_line|#ifndef IR_CRC_H
DECL|macro|IR_CRC_H
mdefine_line|#define IR_CRC_H
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|INIT_FCS
mdefine_line|#define INIT_FCS  0xffff   /* Initial FCS value */
DECL|macro|GOOD_FCS
mdefine_line|#define GOOD_FCS  0xf0b8   /* Good final FCS value */
multiline_comment|/* Recompute the FCS with one more character appended. */
DECL|macro|IR_FCS
mdefine_line|#define IR_FCS(fcs, byte) (((fcs)&gt;&gt;8)^irda_crc16_table[((fcs)^(byte)) &amp; 0xff])
multiline_comment|/* Recompute the FCS with len bytes appended. */
r_int
r_int
id|crc_calc
c_func
(paren
id|__u16
id|fcs
comma
id|__u8
r_const
op_star
id|buf
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
id|__u16
r_const
id|irda_crc16_table
(braket
)braket
suffix:semicolon
macro_line|#endif
eof
