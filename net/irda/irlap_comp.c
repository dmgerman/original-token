multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irlap_comp.c&n; * Version:       &n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Fri Oct  9 09:18:07 1998&n; * Modified at:   Sun May  9 11:37:06 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Sources:       ppp.c, isdn_ppp.c&n; * &n; *     Copyright (c) 1998-1999 Dag Brattli, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irqueue.h&gt;
macro_line|#include &lt;net/irda/irlap.h&gt;
macro_line|#include &lt;net/irda/irlap_comp.h&gt;
macro_line|#include &quot;../../drivers/net/zlib.h&quot;
DECL|variable|irlap_compressors
id|hashbin_t
op_star
id|irlap_compressors
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * Function irda_register_compressor (cp)&n; *&n; *    Register new compressor with the IrLAP&n; *&n; */
DECL|function|irda_register_compressor
r_int
id|irda_register_compressor
c_func
(paren
r_struct
id|compressor
op_star
id|cp
)paren
(brace
r_struct
id|irda_compressor
op_star
r_new
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Check if this compressor has been registred before */
r_if
c_cond
(paren
id|hashbin_find
(paren
id|irlap_compressors
comma
id|cp-&gt;compress_proto
comma
l_int|NULL
)paren
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), Compressor already registered&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Make new IrDA compressor */
r_new
op_assign
(paren
r_struct
id|irda_compressor
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|irda_compressor
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_eq
l_int|NULL
)paren
r_return
l_int|1
suffix:semicolon
id|memset
c_func
(paren
r_new
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|irda_compressor
)paren
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|cp
op_assign
id|cp
suffix:semicolon
multiline_comment|/* Insert IrDA compressor into hashbin */
id|hashbin_insert
c_func
(paren
id|irlap_compressors
comma
(paren
id|QUEUE
op_star
)paren
r_new
comma
id|cp-&gt;compress_proto
comma
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_unregister_compressor (cp)&n; *&n; *    Unregister compressor&n; *&n; */
DECL|function|irda_unregister_compressor
r_void
id|irda_unregister_compressor
(paren
r_struct
id|compressor
op_star
id|cp
)paren
(brace
r_struct
id|irda_compressor
op_star
id|node
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
id|node
op_assign
id|hashbin_remove
c_func
(paren
id|irlap_compressors
comma
id|cp-&gt;compress_proto
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), compressor not found!&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|node
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_set_compression (self, proto)&n; *&n; *    The the compression protocol to be used by this session&n; *&n; */
DECL|function|irda_set_compression
r_int
id|irda_set_compression
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
comma
r_int
id|proto
)paren
(brace
r_struct
id|compressor
op_star
id|cp
suffix:semicolon
r_struct
id|irda_compressor
op_star
id|comp
suffix:semicolon
id|__u8
id|options
(braket
id|CILEN_DEFLATE
)braket
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
op_minus
id|ENODEV
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|LAP_MAGIC
comma
r_return
op_minus
id|EBADR
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Initialize options */
id|options
(braket
l_int|0
)braket
op_assign
id|CI_DEFLATE
suffix:semicolon
id|options
(braket
l_int|1
)braket
op_assign
id|CILEN_DEFLATE
suffix:semicolon
id|options
(braket
l_int|2
)braket
op_assign
id|DEFLATE_METHOD
c_func
(paren
id|DEFLATE_METHOD_VAL
)paren
suffix:semicolon
id|options
(braket
l_int|3
)braket
op_assign
id|DEFLATE_CHK_SEQUENCE
suffix:semicolon
id|comp
op_assign
id|hashbin_find
c_func
(paren
id|irlap_compressors
comma
id|proto
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|comp
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), Unable to find compressor&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|cp
op_assign
id|comp-&gt;cp
suffix:semicolon
multiline_comment|/* &n;&t; *  Compressor part&n;&t; */
r_if
c_cond
(paren
id|self-&gt;compressor.state
op_ne
l_int|NULL
)paren
(paren
op_star
id|self-&gt;compressor.cp-&gt;comp_free
)paren
(paren
id|self-&gt;compressor.state
)paren
suffix:semicolon
id|self-&gt;compressor.state
op_assign
l_int|NULL
suffix:semicolon
id|self-&gt;compressor.cp
op_assign
id|cp
suffix:semicolon
id|self-&gt;compressor.state
op_assign
id|cp
op_member_access_from_pointer
id|comp_alloc
c_func
(paren
id|options
comma
r_sizeof
(paren
id|options
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|self-&gt;compressor.state
op_eq
l_int|NULL
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), Failed!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
multiline_comment|/* &n;&t; *  Decompress part&n;&t; */
r_if
c_cond
(paren
id|self-&gt;decompressor.state
op_ne
l_int|NULL
)paren
id|irda_decomp_free
c_func
(paren
id|self-&gt;decompressor.state
)paren
suffix:semicolon
id|self-&gt;decompressor.state
op_assign
l_int|NULL
suffix:semicolon
id|self-&gt;decompressor.cp
op_assign
id|cp
suffix:semicolon
id|self-&gt;decompressor.state
op_assign
id|cp
op_member_access_from_pointer
id|decomp_alloc
c_func
(paren
id|options
comma
r_sizeof
(paren
id|options
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|self-&gt;decompressor.state
op_eq
l_int|NULL
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), Failed!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOBUFS
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_free_compression (self)&n; *&n; *    &n; *&n; */
DECL|function|irda_free_compression
r_void
id|irda_free_compression
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
)paren
(brace
id|DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|self-&gt;compressor.state
)paren
(brace
id|irda_comp_free
c_func
(paren
id|self-&gt;compressor.state
)paren
suffix:semicolon
id|self-&gt;compressor.state
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|self-&gt;decompressor.state
)paren
(brace
id|irda_decomp_free
c_func
(paren
id|self-&gt;decompressor.state
)paren
suffix:semicolon
id|self-&gt;decompressor.state
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Function irlap_compress_init (self)&n; *&n; *    &n; *&n; */
DECL|function|irlap_compressor_init
r_void
id|irlap_compressor_init
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
comma
r_int
id|compress
)paren
(brace
r_int
id|debug
op_assign
id|TRUE
suffix:semicolon
id|__u8
id|options
(braket
id|CILEN_DEFLATE
)braket
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|LAP_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Initialize options */
id|options
(braket
l_int|0
)braket
op_assign
id|CI_DEFLATE
suffix:semicolon
id|options
(braket
l_int|1
)braket
op_assign
id|CILEN_DEFLATE
suffix:semicolon
id|options
(braket
l_int|2
)braket
op_assign
id|DEFLATE_METHOD_VAL
suffix:semicolon
id|options
(braket
l_int|3
)braket
op_assign
id|DEFLATE_CHK_SEQUENCE
suffix:semicolon
multiline_comment|/*&n;&t; *  We&squot;re agreeing to send compressed packets.&n;&t; */
r_if
c_cond
(paren
id|self-&gt;compressor.state
op_eq
l_int|NULL
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), state == NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_star
id|self-&gt;compressor.cp-&gt;comp_init
)paren
(paren
id|self-&gt;compressor.state
comma
id|options
comma
r_sizeof
(paren
id|options
)paren
comma
l_int|0
comma
l_int|0
comma
id|debug
)paren
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), Compressor running!&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* ppp-&gt;flags |= SC_COMP_RUN; */
)brace
multiline_comment|/*&n;&t; *  Initialize decompressor&n;&t; */
r_if
c_cond
(paren
id|self-&gt;decompressor.state
op_eq
l_int|NULL
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), state == NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|self-&gt;decompressor.cp-&gt;decomp_init
)paren
(paren
id|self-&gt;decompressor.state
comma
id|options
comma
r_sizeof
(paren
id|options
)paren
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|debug
)paren
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), Decompressor running!&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* ppp-&gt;flags |= SC_DECOMP_RUN; */
multiline_comment|/* ppp-&gt;flags &amp;= ~(SC_DC_ERROR | SC_DC_FERROR); */
)brace
)brace
multiline_comment|/*&n; * Function irlap_compress_frame (self, skb)&n; *&n; *&n; *&n; */
DECL|function|irlap_compress_frame
r_struct
id|sk_buff
op_star
id|irlap_compress_frame
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|sk_buff
op_star
id|new_skb
suffix:semicolon
r_int
id|count
suffix:semicolon
id|ASSERT
c_func
(paren
id|skb
op_ne
l_int|NULL
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;() skb-&gt;len=%d, jiffies=%ld&bslash;n&quot;
comma
(paren
r_int
)paren
id|skb-&gt;len
comma
id|jiffies
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|LAP_MAGIC
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Check if compressor got initialized */
r_if
c_cond
(paren
id|self-&gt;compressor.state
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* Tell peer that this frame is not compressed */
id|skb_push
c_func
(paren
id|skb
comma
id|LAP_COMP_HEADER
)paren
suffix:semicolon
id|skb-&gt;data
(braket
l_int|0
)braket
op_assign
id|IRDA_NORMAL
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
multiline_comment|/* FIXME: Find out what is the max overhead (not 10) */
id|new_skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|skb-&gt;len
op_plus
id|LAP_MAX_HEADER
op_plus
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_skb
)paren
(brace
r_return
id|skb
suffix:semicolon
)brace
id|skb_reserve
c_func
(paren
id|new_skb
comma
id|LAP_MAX_HEADER
)paren
suffix:semicolon
id|skb_put
c_func
(paren
id|new_skb
comma
id|skb-&gt;len
op_plus
l_int|10
)paren
suffix:semicolon
id|count
op_assign
(paren
id|self-&gt;compressor.cp-&gt;compress
)paren
(paren
id|self-&gt;compressor.state
comma
id|skb-&gt;data
comma
id|new_skb-&gt;data
comma
id|skb-&gt;len
comma
id|new_skb-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_le
l_int|0
)paren
(brace
id|DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;(), Unable to compress frame!&bslash;n&quot;
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|new_skb
)paren
suffix:semicolon
multiline_comment|/* Tell peer that this frame is not compressed */
id|skb_push
c_func
(paren
id|skb
comma
l_int|1
)paren
suffix:semicolon
id|skb-&gt;data
(braket
l_int|0
)braket
op_assign
id|IRDA_NORMAL
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
id|skb_trim
c_func
(paren
id|new_skb
comma
id|count
)paren
suffix:semicolon
multiline_comment|/* Tell peer that this frame is compressed */
id|skb_push
c_func
(paren
id|new_skb
comma
l_int|1
)paren
suffix:semicolon
id|new_skb-&gt;data
(braket
l_int|0
)braket
op_assign
id|IRDA_COMPRESSED
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;() new_skb-&gt;len=%d&bslash;n, jiffies=%ld&quot;
comma
(paren
r_int
)paren
id|new_skb-&gt;len
comma
id|jiffies
)paren
suffix:semicolon
r_return
id|new_skb
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irlap_decompress_frame (self, skb)&n; *&n; *    &n; *&n; */
DECL|function|irlap_decompress_frame
r_struct
id|sk_buff
op_star
id|irlap_decompress_frame
c_func
(paren
r_struct
id|irlap_cb
op_star
id|self
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
(brace
r_struct
id|sk_buff
op_star
id|new_skb
suffix:semicolon
r_int
id|count
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;() skb-&gt;len=%d&bslash;n&quot;
comma
(paren
r_int
)paren
id|skb-&gt;len
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|LAP_MAGIC
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;compressor.state
op_ne
l_int|NULL
comma
r_return
l_int|NULL
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* Check if frame is compressed */
r_if
c_cond
(paren
id|skb-&gt;data
(braket
l_int|0
)braket
op_eq
id|IRDA_NORMAL
)paren
(brace
multiline_comment|/* Remove compression header */
id|skb_pull
c_func
(paren
id|skb
comma
id|LAP_COMP_HEADER
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The frame is not compressed. Pass it to the&n;&t;&t; * decompression code so it can update its&n;&t;&t; * dictionary if necessary.&n;&t;&t; */
id|irda_incomp
c_func
(paren
id|self-&gt;decompressor.state
comma
id|skb-&gt;data
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
multiline_comment|/* Remove compression header */
id|skb_pull
c_func
(paren
id|skb
comma
id|LAP_COMP_HEADER
)paren
suffix:semicolon
id|new_skb
op_assign
id|dev_alloc_skb
c_func
(paren
l_int|2048
)paren
suffix:semicolon
multiline_comment|/* FIXME: find the right size */
r_if
c_cond
(paren
op_logical_neg
id|new_skb
)paren
(brace
r_return
id|skb
suffix:semicolon
)brace
id|skb_put
c_func
(paren
id|new_skb
comma
l_int|2048
)paren
suffix:semicolon
id|count
op_assign
id|irda_decompress
c_func
(paren
id|self-&gt;decompressor.state
comma
id|skb-&gt;data
comma
id|skb-&gt;len
comma
id|new_skb-&gt;data
comma
id|new_skb-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_le
l_int|0
)paren
(brace
id|DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;(), Unable to decompress frame!&bslash;n&quot;
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|new_skb
)paren
suffix:semicolon
r_return
id|skb
suffix:semicolon
)brace
id|skb_trim
c_func
(paren
id|new_skb
comma
id|count
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;() new_skb-&gt;len=%d&bslash;n&quot;
comma
(paren
r_int
)paren
id|new_skb-&gt;len
)paren
suffix:semicolon
r_return
id|new_skb
suffix:semicolon
)brace
eof
