multiline_comment|/*********************************************************************&n; *                &n; * Filename:      parameters.c&n; * Version:       1.0&n; * Description:   A more general way to handle (pi,pl,pv) parameters&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Mon Jun  7 10:25:11 1999&n; * Modified at:   Fri Nov  5 08:20:38 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1999 Dag Brattli, All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; * &n; *     This program is distributed in the hope that it will be useful,&n; *     but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; *     GNU General Public License for more details.&n; * &n; *     You should have received a copy of the GNU General Public License &n; *     along with this program; if not, write to the Free Software &n; *     Foundation, Inc., 59 Temple Place, Suite 330, Boston, &n; *     MA 02111-1307 USA&n; *     &n; ********************************************************************/
macro_line|#include &lt;asm/unaligned.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/parameters.h&gt;
r_static
r_int
id|irda_extract_integer
c_func
(paren
r_void
op_star
id|self
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
comma
id|__u8
id|pi
comma
id|PV_TYPE
id|type
comma
id|PI_HANDLER
id|func
)paren
suffix:semicolon
r_static
r_int
id|irda_extract_string
c_func
(paren
r_void
op_star
id|self
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
comma
id|__u8
id|pi
comma
id|PV_TYPE
id|type
comma
id|PI_HANDLER
id|func
)paren
suffix:semicolon
r_static
r_int
id|irda_extract_octseq
c_func
(paren
r_void
op_star
id|self
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
comma
id|__u8
id|pi
comma
id|PV_TYPE
id|type
comma
id|PI_HANDLER
id|func
)paren
suffix:semicolon
r_static
r_int
id|irda_extract_no_value
c_func
(paren
r_void
op_star
id|self
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
comma
id|__u8
id|pi
comma
id|PV_TYPE
id|type
comma
id|PI_HANDLER
id|func
)paren
suffix:semicolon
r_static
r_int
id|irda_insert_integer
c_func
(paren
r_void
op_star
id|self
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
comma
id|__u8
id|pi
comma
id|PV_TYPE
id|type
comma
id|PI_HANDLER
id|func
)paren
suffix:semicolon
r_static
r_int
id|irda_insert_no_value
c_func
(paren
r_void
op_star
id|self
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
comma
id|__u8
id|pi
comma
id|PV_TYPE
id|type
comma
id|PI_HANDLER
id|func
)paren
suffix:semicolon
multiline_comment|/* Parameter value call table. Must match PV_TYPE */
DECL|variable|pv_extract_table
r_static
id|PV_HANDLER
id|pv_extract_table
(braket
)braket
op_assign
(brace
id|irda_extract_integer
comma
multiline_comment|/* Handler for any length integers */
id|irda_extract_integer
comma
multiline_comment|/* Handler for 8  bits integers */
id|irda_extract_integer
comma
multiline_comment|/* Handler for 16 bits integers */
id|irda_extract_string
comma
multiline_comment|/* Handler for strings */
id|irda_extract_integer
comma
multiline_comment|/* Handler for 32 bits integers */
id|irda_extract_octseq
comma
multiline_comment|/* Handler for octet sequences */
id|irda_extract_no_value
multiline_comment|/* Handler for no value parameters */
)brace
suffix:semicolon
DECL|variable|pv_insert_table
r_static
id|PV_HANDLER
id|pv_insert_table
(braket
)braket
op_assign
(brace
id|irda_insert_integer
comma
multiline_comment|/* Handler for any length integers */
id|irda_insert_integer
comma
multiline_comment|/* Handler for 8  bits integers */
id|irda_insert_integer
comma
multiline_comment|/* Handler for 16 bits integers */
l_int|NULL
comma
multiline_comment|/* Handler for strings */
id|irda_insert_integer
comma
multiline_comment|/* Handler for 32 bits integers */
l_int|NULL
comma
multiline_comment|/* Handler for octet sequences */
id|irda_insert_no_value
multiline_comment|/* Handler for no value parameters */
)brace
suffix:semicolon
multiline_comment|/*&n; * Function irda_insert_no_value (self, buf, len, pi, type, func)&n; *&n; *    &n; *&n; */
DECL|function|irda_insert_no_value
r_static
r_int
id|irda_insert_no_value
c_func
(paren
r_void
op_star
id|self
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
comma
id|__u8
id|pi
comma
id|PV_TYPE
id|type
comma
id|PI_HANDLER
id|func
)paren
(brace
id|param_t
id|p
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|p.pi
op_assign
id|pi
suffix:semicolon
id|p.pl
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Call handler for this parameter */
id|ret
op_assign
(paren
op_star
id|func
)paren
(paren
id|self
comma
op_amp
id|p
comma
id|PV_GET
)paren
suffix:semicolon
multiline_comment|/* Extract values anyway, since handler may need them */
id|irda_param_pack
c_func
(paren
id|buf
comma
l_string|&quot;bb&quot;
comma
id|p.pi
comma
op_amp
id|p.pl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_return
l_int|2
suffix:semicolon
multiline_comment|/* Inserted pl+2 bytes */
)brace
multiline_comment|/*&n; * Function irda_extract_no_value (self, buf, len, type, func)&n; *&n; *    Extracts a parameter without a pv field (pl=0)&n; *&n; */
DECL|function|irda_extract_no_value
r_static
r_int
id|irda_extract_no_value
c_func
(paren
r_void
op_star
id|self
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
comma
id|__u8
id|pi
comma
id|PV_TYPE
id|type
comma
id|PI_HANDLER
id|func
)paren
(brace
id|param_t
id|p
suffix:semicolon
r_int
id|ret
suffix:semicolon
multiline_comment|/* Extract values anyway, since handler may need them */
id|irda_param_unpack
c_func
(paren
id|buf
comma
l_string|&quot;bb&quot;
comma
op_amp
id|p.pi
comma
op_amp
id|p.pl
)paren
suffix:semicolon
multiline_comment|/* Call handler for this parameter */
id|ret
op_assign
(paren
op_star
id|func
)paren
(paren
id|self
comma
op_amp
id|p
comma
id|PV_PUT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
r_return
l_int|2
suffix:semicolon
multiline_comment|/* Extracted pl+2 bytes */
)brace
multiline_comment|/*&n; * Function irda_insert_integer (self, buf, len, pi, type, func)&n; *&n; *    &n; *&n; */
DECL|function|irda_insert_integer
r_static
r_int
id|irda_insert_integer
c_func
(paren
r_void
op_star
id|self
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
comma
id|__u8
id|pi
comma
id|PV_TYPE
id|type
comma
id|PI_HANDLER
id|func
)paren
(brace
id|param_t
id|p
suffix:semicolon
r_int
id|n
op_assign
l_int|0
suffix:semicolon
r_int
id|err
suffix:semicolon
id|p.pi
op_assign
id|pi
suffix:semicolon
multiline_comment|/* In case handler needs to know */
id|p.pl
op_assign
id|type
op_amp
id|PV_MASK
suffix:semicolon
multiline_comment|/* The integer type codes the lenght as well */
id|p.pv.i
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Clear value */
multiline_comment|/* Call handler for this parameter */
id|err
op_assign
(paren
op_star
id|func
)paren
(paren
id|self
comma
op_amp
id|p
comma
id|PV_GET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* &n;&t; * If parameter lenght is still 0, then (1) this is an any length &n;&t; * integer, and (2) the handler function does not care which length&n;&t; * we choose to use, so we pick the one the gives the fewest bytes.&n;&t; */
r_if
c_cond
(paren
id|p.pl
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|p.pv.i
OL
l_int|0xff
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;(), using 1 byte&bslash;n&quot;
)paren
suffix:semicolon
id|p.pl
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|p.pv.i
OL
l_int|0xffff
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;(), using 2 bytes&bslash;n&quot;
)paren
suffix:semicolon
id|p.pl
op_assign
l_int|2
suffix:semicolon
)brace
r_else
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;(), using 4 bytes&bslash;n&quot;
)paren
suffix:semicolon
id|p.pl
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* Default length */
)brace
)brace
multiline_comment|/* Check if buffer is long enough for insertion */
r_if
c_cond
(paren
id|len
OL
(paren
l_int|2
op_plus
id|p.pl
)paren
)paren
(brace
id|WARNING
c_func
(paren
id|__FUNCTION__
l_string|&quot;(), buffer to short for insertion!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;(), pi=%#x, pl=%d, pi=%d&bslash;n&quot;
comma
id|p.pi
comma
id|p.pl
comma
id|p.pv.i
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|p.pl
)paren
(brace
r_case
l_int|1
suffix:colon
id|n
op_add_assign
id|irda_param_pack
c_func
(paren
id|buf
comma
l_string|&quot;bbb&quot;
comma
id|p.pi
comma
id|p.pl
comma
id|p.pv.b
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_if
c_cond
(paren
id|type
op_amp
id|PV_BIG_ENDIAN
)paren
id|cpu_to_be16s
c_func
(paren
op_amp
id|p.pv.s
)paren
suffix:semicolon
r_else
id|cpu_to_le16s
c_func
(paren
op_amp
id|p.pv.s
)paren
suffix:semicolon
id|n
op_add_assign
id|irda_param_pack
c_func
(paren
id|buf
comma
l_string|&quot;bbs&quot;
comma
id|p.pi
comma
id|p.pl
comma
id|p.pv.s
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
r_if
c_cond
(paren
id|type
op_amp
id|PV_BIG_ENDIAN
)paren
id|cpu_to_be32s
c_func
(paren
op_amp
id|p.pv.i
)paren
suffix:semicolon
r_else
id|cpu_to_le32s
c_func
(paren
op_amp
id|p.pv.i
)paren
suffix:semicolon
id|n
op_add_assign
id|irda_param_pack
c_func
(paren
id|buf
comma
l_string|&quot;bbi&quot;
comma
id|p.pi
comma
id|p.pl
comma
id|p.pv.i
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|WARNING
c_func
(paren
id|__FUNCTION__
l_string|&quot;() length %d not supported&bslash;n&quot;
comma
id|p.pl
)paren
suffix:semicolon
multiline_comment|/* Skip parameter */
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|p.pl
op_plus
l_int|2
suffix:semicolon
multiline_comment|/* Inserted pl+2 bytes */
)brace
multiline_comment|/*&n; * Function irda_extract integer (self, buf, len, pi, type, func)&n; *&n; *    Extract a possibly variable length integer from buffer, and call &n; *    handler for processing of the parameter&n; */
DECL|function|irda_extract_integer
r_static
r_int
id|irda_extract_integer
c_func
(paren
r_void
op_star
id|self
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
comma
id|__u8
id|pi
comma
id|PV_TYPE
id|type
comma
id|PI_HANDLER
id|func
)paren
(brace
id|param_t
id|p
suffix:semicolon
r_int
id|n
op_assign
l_int|0
suffix:semicolon
r_int
id|err
suffix:semicolon
id|p.pi
op_assign
id|pi
suffix:semicolon
multiline_comment|/* In case handler needs to know */
id|p.pl
op_assign
id|buf
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Extract lenght of value */
id|p.pv.i
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Clear value */
multiline_comment|/* Check if buffer is long enough for parsing */
r_if
c_cond
(paren
id|len
OL
(paren
l_int|2
op_plus
id|p.pl
)paren
)paren
(brace
id|WARNING
c_func
(paren
id|__FUNCTION__
l_string|&quot;(), buffer to short for parsing! &quot;
l_string|&quot;Need %d bytes, but len is only %d&bslash;n&quot;
comma
id|p.pl
comma
id|len
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* &n;&t; * Check that the integer length is what we expect it to be. If the&n;&t; * handler want a 16 bits integer then a 32 bits is not good enough&n;&t; */
r_if
c_cond
(paren
(paren
(paren
id|type
op_amp
id|PV_MASK
)paren
op_ne
id|PV_INTEGER
)paren
op_logical_and
(paren
(paren
id|type
op_amp
id|PV_MASK
)paren
op_ne
id|p.pl
)paren
)paren
(brace
id|ERROR
c_func
(paren
id|__FUNCTION__
l_string|&quot;(), invalid parameter length! &quot;
l_string|&quot;Expected %d bytes, but value had %d bytes!&bslash;n&quot;
comma
id|type
op_amp
id|PV_MASK
comma
id|p.pl
)paren
suffix:semicolon
multiline_comment|/* Skip parameter */
r_return
id|p.pl
op_plus
l_int|2
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|p.pl
)paren
(brace
r_case
l_int|1
suffix:colon
id|n
op_add_assign
id|irda_param_unpack
c_func
(paren
id|buf
op_plus
l_int|2
comma
l_string|&quot;b&quot;
comma
op_amp
id|p.pv.b
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|n
op_add_assign
id|irda_param_unpack
c_func
(paren
id|buf
op_plus
l_int|2
comma
l_string|&quot;s&quot;
comma
op_amp
id|p.pv.s
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|PV_BIG_ENDIAN
)paren
id|be16_to_cpus
c_func
(paren
op_amp
id|p.pv.s
)paren
suffix:semicolon
r_else
id|le16_to_cpus
c_func
(paren
op_amp
id|p.pv.s
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|n
op_add_assign
id|irda_param_unpack
c_func
(paren
id|buf
op_plus
l_int|2
comma
l_string|&quot;i&quot;
comma
op_amp
id|p.pv.i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|PV_BIG_ENDIAN
)paren
id|be32_to_cpus
c_func
(paren
op_amp
id|p.pv.i
)paren
suffix:semicolon
r_else
id|le32_to_cpus
c_func
(paren
op_amp
id|p.pv.i
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|WARNING
c_func
(paren
id|__FUNCTION__
l_string|&quot;() length %d not supported&bslash;n&quot;
comma
id|p.pl
)paren
suffix:semicolon
multiline_comment|/* Skip parameter */
r_return
id|p.pl
op_plus
l_int|2
suffix:semicolon
)brace
multiline_comment|/* Call handler for this parameter */
id|err
op_assign
(paren
op_star
id|func
)paren
(paren
id|self
comma
op_amp
id|p
comma
id|PV_PUT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_return
id|p.pl
op_plus
l_int|2
suffix:semicolon
multiline_comment|/* Extracted pl+2 bytes */
)brace
multiline_comment|/*&n; * Function irda_extract_string (self, buf, len, type, func)&n; *&n; *    &n; *&n; */
DECL|function|irda_extract_string
r_static
r_int
id|irda_extract_string
c_func
(paren
r_void
op_star
id|self
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
comma
id|__u8
id|pi
comma
id|PV_TYPE
id|type
comma
id|PI_HANDLER
id|func
)paren
(brace
r_char
id|str
(braket
l_int|33
)braket
suffix:semicolon
id|param_t
id|p
suffix:semicolon
r_int
id|err
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
id|p.pi
op_assign
id|pi
suffix:semicolon
multiline_comment|/* In case handler needs to know */
id|p.pl
op_assign
id|buf
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Extract lenght of value */
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;(), pi=%#x, pl=%d&bslash;n&quot;
comma
id|p.pi
comma
id|p.pl
)paren
suffix:semicolon
multiline_comment|/* Check if buffer is long enough for parsing */
r_if
c_cond
(paren
id|len
OL
(paren
l_int|2
op_plus
id|p.pl
)paren
)paren
(brace
id|WARNING
c_func
(paren
id|__FUNCTION__
l_string|&quot;(), buffer to short for parsing! &quot;
l_string|&quot;Need %d bytes, but len is only %d&bslash;n&quot;
comma
id|p.pl
comma
id|len
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Should be safe to copy string like this since we have already &n;&t; * checked that the buffer is long enough */
id|strncpy
c_func
(paren
id|str
comma
id|buf
op_plus
l_int|2
comma
id|p.pl
)paren
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|2
comma
id|__FUNCTION__
l_string|&quot;(), str=0x%02x 0x%02x&bslash;n&quot;
comma
(paren
id|__u8
)paren
id|str
(braket
l_int|0
)braket
comma
(paren
id|__u8
)paren
id|str
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* Null terminate string */
id|str
(braket
id|p.pl
op_plus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|p.pv.c
op_assign
id|str
suffix:semicolon
multiline_comment|/* Handler will need to take a copy */
multiline_comment|/* Call handler for this parameter */
id|err
op_assign
(paren
op_star
id|func
)paren
(paren
id|self
comma
op_amp
id|p
comma
id|PV_PUT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_return
id|p.pl
op_plus
l_int|2
suffix:semicolon
multiline_comment|/* Extracted pl+2 bytes */
)brace
multiline_comment|/*&n; * Function irda_extract_octseq (self, buf, len, type, func)&n; *&n; *    &n; *&n; */
DECL|function|irda_extract_octseq
r_static
r_int
id|irda_extract_octseq
c_func
(paren
r_void
op_star
id|self
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
comma
id|__u8
id|pi
comma
id|PV_TYPE
id|type
comma
id|PI_HANDLER
id|func
)paren
(brace
id|param_t
id|p
suffix:semicolon
id|p.pi
op_assign
id|pi
suffix:semicolon
multiline_comment|/* In case handler needs to know */
id|p.pl
op_assign
id|buf
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Extract lenght of value */
multiline_comment|/* Check if buffer is long enough for parsing */
r_if
c_cond
(paren
id|len
OL
(paren
l_int|2
op_plus
id|p.pl
)paren
)paren
(brace
id|WARNING
c_func
(paren
id|__FUNCTION__
l_string|&quot;(), buffer to short for parsing! &quot;
l_string|&quot;Need %d bytes, but len is only %d&bslash;n&quot;
comma
id|p.pl
comma
id|len
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), not impl&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|p.pl
op_plus
l_int|2
suffix:semicolon
multiline_comment|/* Extracted pl+2 bytes */
)brace
multiline_comment|/*&n; * Function irda_param_pack (skb, fmt, ...)&n; *&n; *    Format:&n; *        &squot;i&squot; = 32 bits integer&n; *        &squot;s&squot; = string&n; *&n; */
DECL|function|irda_param_pack
r_int
id|irda_param_pack
c_func
(paren
id|__u8
op_star
id|buf
comma
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_int
id|n
op_assign
l_int|0
suffix:semicolon
id|pv_t
id|arg
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|fmt
suffix:semicolon
op_star
id|p
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|p
op_increment
)paren
(brace
r_switch
c_cond
(paren
op_star
id|p
)paren
(brace
r_case
l_char|&squot;b&squot;
suffix:colon
multiline_comment|/* 8 bits unsigned byte */
id|buf
(braket
id|n
op_increment
)braket
op_assign
id|va_arg
c_func
(paren
id|args
comma
id|__u8
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
multiline_comment|/* 16 bits unsigned short */
id|arg.s
op_assign
id|va_arg
c_func
(paren
id|args
comma
id|__u16
)paren
suffix:semicolon
id|put_unaligned
c_func
(paren
id|arg.s
comma
(paren
id|__u16
op_star
)paren
(paren
id|buf
op_plus
id|n
)paren
)paren
suffix:semicolon
id|n
op_add_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;i&squot;
suffix:colon
multiline_comment|/* 32 bits unsigned integer */
id|arg.i
op_assign
id|va_arg
c_func
(paren
id|args
comma
id|__u32
)paren
suffix:semicolon
id|put_unaligned
c_func
(paren
id|arg.i
comma
(paren
id|__u32
op_star
)paren
(paren
id|buf
op_plus
id|n
)paren
)paren
suffix:semicolon
id|n
op_add_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;c&squot;
suffix:colon
multiline_comment|/* &bslash;0 terminated string */
id|arg.c
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_char
op_star
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|buf
op_plus
id|n
comma
id|arg.c
)paren
suffix:semicolon
id|n
op_add_assign
id|strlen
c_func
(paren
id|arg.c
)paren
op_plus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_param_unpack (skb, fmt, ...)&n; *&n; *    &n; *&n; */
DECL|function|irda_param_unpack
r_int
id|irda_param_unpack
c_func
(paren
id|__u8
op_star
id|buf
comma
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_int
id|n
op_assign
l_int|0
suffix:semicolon
id|pv_t
id|arg
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|fmt
suffix:semicolon
op_star
id|p
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|p
op_increment
)paren
(brace
r_switch
c_cond
(paren
op_star
id|p
)paren
(brace
r_case
l_char|&squot;b&squot;
suffix:colon
multiline_comment|/* 8 bits byte */
id|arg.bp
op_assign
id|va_arg
c_func
(paren
id|args
comma
id|__u8
op_star
)paren
suffix:semicolon
op_star
id|arg.bp
op_assign
id|buf
(braket
id|n
op_increment
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
multiline_comment|/* 16 bits short */
id|arg.sp
op_assign
id|va_arg
c_func
(paren
id|args
comma
id|__u16
op_star
)paren
suffix:semicolon
op_star
id|arg.sp
op_assign
id|get_unaligned
c_func
(paren
(paren
id|__u16
op_star
)paren
(paren
id|buf
op_plus
id|n
)paren
)paren
suffix:semicolon
id|n
op_add_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;i&squot;
suffix:colon
multiline_comment|/* 32 bits unsigned integer */
id|arg.ip
op_assign
id|va_arg
c_func
(paren
id|args
comma
id|__u32
op_star
)paren
suffix:semicolon
op_star
id|arg.ip
op_assign
id|get_unaligned
c_func
(paren
(paren
id|__u32
op_star
)paren
(paren
id|buf
op_plus
id|n
)paren
)paren
suffix:semicolon
id|n
op_add_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if 0
r_case
l_char|&squot;c&squot;
suffix:colon
multiline_comment|/* &bslash;0 terminated string */
id|arg.c
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_char
op_star
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|arg.c
comma
id|buf
op_plus
id|n
)paren
suffix:semicolon
id|n
op_add_assign
id|strlen
c_func
(paren
id|arg.c
)paren
op_plus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_param_insert (self, pi, buf, len, info)&n; *&n; *    Insert the specified parameter (pi) into buffer. Returns number of&n; *    bytes inserted&n; */
DECL|function|irda_param_insert
r_int
id|irda_param_insert
c_func
(paren
r_void
op_star
id|self
comma
id|__u8
id|pi
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
comma
id|pi_param_info_t
op_star
id|info
)paren
(brace
id|pi_minor_info_t
op_star
id|pi_minor_info
suffix:semicolon
id|__u8
id|pi_minor
suffix:semicolon
id|__u8
id|pi_major
suffix:semicolon
r_int
id|type
suffix:semicolon
r_int
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|n
op_assign
l_int|0
suffix:semicolon
id|ASSERT
c_func
(paren
id|buf
op_ne
l_int|NULL
comma
r_return
id|ret
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|info
op_ne
l_int|0
comma
r_return
id|ret
suffix:semicolon
)paren
suffix:semicolon
id|pi_minor
op_assign
id|pi
op_amp
id|info-&gt;pi_mask
suffix:semicolon
id|pi_major
op_assign
id|pi
op_rshift
id|info-&gt;pi_major_offset
suffix:semicolon
multiline_comment|/* Check if the identifier value (pi) is valid */
r_if
c_cond
(paren
(paren
id|pi_major
OG
id|info-&gt;len
op_minus
l_int|1
)paren
op_logical_or
(paren
id|pi_minor
OG
id|info-&gt;tables
(braket
id|pi_major
)braket
dot
id|len
op_minus
l_int|1
)paren
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), no handler for parameter=0x%02x&bslash;n&quot;
comma
id|pi
)paren
suffix:semicolon
multiline_comment|/* Skip this parameter */
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Lookup the info on how to parse this parameter */
id|pi_minor_info
op_assign
op_amp
id|info-&gt;tables
(braket
id|pi_major
)braket
dot
id|pi_minor_call_table
(braket
id|pi_minor
)braket
suffix:semicolon
multiline_comment|/* Find expected data type for this parameter identifier (pi)*/
id|type
op_assign
id|pi_minor_info-&gt;type
suffix:semicolon
multiline_comment|/*  Check if handler has been implemented */
r_if
c_cond
(paren
op_logical_neg
id|pi_minor_info-&gt;func
)paren
(brace
id|MESSAGE
c_func
(paren
id|__FUNCTION__
l_string|&quot;(), no handler for pi=%#x&bslash;n&quot;
comma
id|pi
)paren
suffix:semicolon
multiline_comment|/* Skip this parameter */
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Insert parameter value */
id|ret
op_assign
(paren
op_star
id|pv_insert_table
(braket
id|type
op_amp
id|PV_MASK
)braket
)paren
(paren
id|self
comma
id|buf
op_plus
id|n
comma
id|len
comma
id|pi
comma
id|type
comma
id|pi_minor_info-&gt;func
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_param_extract_all (self, buf, len, info)&n; *&n; *    Parse all parameters. If len is correct, then everything should be&n; *    safe. Returns the number of bytes that was parsed&n; *&n; */
DECL|function|irda_param_extract
r_int
id|irda_param_extract
c_func
(paren
r_void
op_star
id|self
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
comma
id|pi_param_info_t
op_star
id|info
)paren
(brace
id|pi_minor_info_t
op_star
id|pi_minor_info
suffix:semicolon
id|__u8
id|pi_minor
suffix:semicolon
id|__u8
id|pi_major
suffix:semicolon
r_int
id|type
suffix:semicolon
r_int
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|n
op_assign
l_int|0
suffix:semicolon
id|ASSERT
c_func
(paren
id|buf
op_ne
l_int|NULL
comma
r_return
id|ret
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|info
op_ne
l_int|0
comma
r_return
id|ret
suffix:semicolon
)paren
suffix:semicolon
id|pi_minor
op_assign
id|buf
(braket
id|n
)braket
op_amp
id|info-&gt;pi_mask
suffix:semicolon
id|pi_major
op_assign
id|buf
(braket
id|n
)braket
op_rshift
id|info-&gt;pi_major_offset
suffix:semicolon
multiline_comment|/* Check if the identifier value (pi) is valid */
r_if
c_cond
(paren
(paren
id|pi_major
OG
id|info-&gt;len
op_minus
l_int|1
)paren
op_logical_or
(paren
id|pi_minor
OG
id|info-&gt;tables
(braket
id|pi_major
)braket
dot
id|len
op_minus
l_int|1
)paren
)paren
(brace
id|IRDA_DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), no handler for parameter=0x%02x&bslash;n&quot;
comma
id|buf
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/* Skip this parameter */
id|n
op_add_assign
(paren
l_int|2
op_plus
id|buf
(braket
id|n
op_plus
l_int|1
)braket
)paren
suffix:semicolon
id|len
op_sub_assign
(paren
l_int|2
op_plus
id|buf
(braket
id|n
op_plus
l_int|1
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Continue */
)brace
multiline_comment|/* Lookup the info on how to parse this parameter */
id|pi_minor_info
op_assign
op_amp
id|info-&gt;tables
(braket
id|pi_major
)braket
dot
id|pi_minor_call_table
(braket
id|pi_minor
)braket
suffix:semicolon
multiline_comment|/* Find expected data type for this parameter identifier (pi)*/
id|type
op_assign
id|pi_minor_info-&gt;type
suffix:semicolon
id|IRDA_DEBUG
c_func
(paren
l_int|3
comma
id|__FUNCTION__
l_string|&quot;(), pi=[%d,%d], type=%d&bslash;n&quot;
comma
id|pi_major
comma
id|pi_minor
comma
id|type
)paren
suffix:semicolon
multiline_comment|/*  Check if handler has been implemented */
r_if
c_cond
(paren
op_logical_neg
id|pi_minor_info-&gt;func
)paren
(brace
id|MESSAGE
c_func
(paren
id|__FUNCTION__
l_string|&quot;(), no handler for pi=%#x&bslash;n&quot;
comma
id|buf
(braket
id|n
)braket
)paren
suffix:semicolon
multiline_comment|/* Skip this parameter */
id|n
op_add_assign
(paren
l_int|2
op_plus
id|buf
(braket
id|n
op_plus
l_int|1
)braket
)paren
suffix:semicolon
id|len
op_sub_assign
(paren
l_int|2
op_plus
id|buf
(braket
id|n
op_plus
l_int|1
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Continue */
)brace
multiline_comment|/* Parse parameter value */
id|ret
op_assign
(paren
op_star
id|pv_extract_table
(braket
id|type
op_amp
id|PV_MASK
)braket
)paren
(paren
id|self
comma
id|buf
op_plus
id|n
comma
id|len
comma
id|buf
(braket
id|n
)braket
comma
id|type
comma
id|pi_minor_info-&gt;func
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_param_extract_all (self, buf, len, info)&n; *&n; *    Parse all parameters. If len is correct, then everything should be&n; *    safe. Returns the number of bytes that was parsed&n; *&n; */
DECL|function|irda_param_extract_all
r_int
id|irda_param_extract_all
c_func
(paren
r_void
op_star
id|self
comma
id|__u8
op_star
id|buf
comma
r_int
id|len
comma
id|pi_param_info_t
op_star
id|info
)paren
(brace
r_int
id|ret
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|n
op_assign
l_int|0
suffix:semicolon
id|ASSERT
c_func
(paren
id|buf
op_ne
l_int|NULL
comma
r_return
id|ret
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|info
op_ne
l_int|0
comma
r_return
id|ret
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Parse all parameters. Each parameter must be at least two bytes&n;&t; * long or else there is no point in trying to parse it&n;&t; */
r_while
c_loop
(paren
id|len
OG
l_int|2
)paren
(brace
id|ret
op_assign
id|irda_param_extract
c_func
(paren
id|self
comma
id|buf
op_plus
id|n
comma
id|len
comma
id|info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|n
op_add_assign
id|ret
suffix:semicolon
id|len
op_sub_assign
id|ret
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
eof
