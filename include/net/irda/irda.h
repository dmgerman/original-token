multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irda.h&n; * Version:       &n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Tue Dec  9 21:13:12 1997&n; * Modified at:   Mon Nov  2 14:49:11 1998&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998 Dag Brattli, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#ifndef IRDA_H
DECL|macro|IRDA_H
mdefine_line|#define IRDA_H
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE 1
macro_line|#endif
macro_line|#ifndef FALSE 
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
DECL|macro|ALIGN
mdefine_line|#define ALIGN __attribute__((aligned))
DECL|macro|PACK
mdefine_line|#define PACK __attribute__((packed))
multiline_comment|/* use 0 for production, 1 for verification, &gt;2 for debug */
macro_line|#ifndef NET_DEBUG
DECL|macro|NET_DEBUG
mdefine_line|#define NET_DEBUG 3
DECL|variable|net_debug
r_static
r_int
r_int
id|net_debug
op_assign
id|NET_DEBUG
suffix:semicolon
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...) if (net_debug &gt;= (n)) printk( KERN_DEBUG args)
DECL|macro|ASSERT
mdefine_line|#define ASSERT(expr, func) &bslash;&n;if(!(expr)) { &bslash;&n;        printk( &quot;Assertion failed! %s,%s,%s,line=%d&bslash;n&quot;,&bslash;&n;        #expr,__FILE__,__FUNCTION__,__LINE__); &bslash;&n;        ##func}
macro_line|#else
macro_line|#error
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...)
DECL|macro|ASSERT
mdefine_line|#define ASSERT(expr, func)
macro_line|#endif /* NET_DEBUG */
macro_line|#ifdef CHECK_SKB
DECL|variable|check_skb
r_static
r_int
r_int
id|check_skb
op_assign
id|CHECK_SKB
suffix:semicolon
DECL|macro|SK_FREED_SKB
mdefine_line|#define SK_FREED_SKB    0x0DE2C0DE
DECL|macro|SK_GOOD_SKB
mdefine_line|#define SK_GOOD_SKB     0xDEC0DED1
DECL|macro|SK_HEAD_SKB
mdefine_line|#define SK_HEAD_SKB     0x12231298
r_extern
r_int
id|skb_check
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
comma
r_int
comma
r_char
op_star
)paren
suffix:semicolon
macro_line|#ifdef IS_SKB
DECL|macro|IS_SKB
macro_line|#undef IS_SKB
macro_line|#endif
DECL|macro|IS_SKB
mdefine_line|#define IS_SKB(skb, func) &bslash;&n;if( skb_check((skb), 0, __LINE__,__FILE__) == -1) { &bslash;&n;       ##func}
macro_line|#ifdef IS_SKB_HEAD
DECL|macro|IS_SKB_HEAD
macro_line|#undef IS_SKB_HEAD
macro_line|#endif
DECL|macro|IS_SKB_HEAD
mdefine_line|#define IS_SKB_HEAD(skb)  skb_check((skb), 1, __LINE__,__FILE__)
DECL|macro|ALLOC_SKB_MAGIC
mdefine_line|#define ALLOC_SKB_MAGIC(skb) &bslash;&n;if( check_skb) &bslash;&n;        skb-&gt;magic_debug_cookie = SK_GOOD_SKB;
DECL|macro|FREE_SKB_MAGIC
mdefine_line|#define FREE_SKB_MAGIC(skb) &bslash;&n;if( check_skb) {&bslash;&n;&t;skb-&gt;magic_debug_cookie = SK_FREED_SKB; &bslash;&n;}
macro_line|#else
DECL|macro|IS_SKB
macro_line|#undef IS_SKB
DECL|macro|IS_SKB
mdefine_line|#define IS_SKB(skb, func)
DECL|macro|IS_SKB_HEAD
macro_line|#undef IS_SKB_HEAD
DECL|macro|IS_SKB_HEAD
mdefine_line|#define IS_SKB_HEAD(skb) 
DECL|macro|ALLOC_SKB_MAGIC
mdefine_line|#define ALLOC_SKB_MAGIC(skb) 
DECL|macro|FREE_SKB_MAGIC
mdefine_line|#define FREE_SKB_MAGIC(skb)
macro_line|#endif /* CHECK_SKB */
multiline_comment|/*&n; *  Magic numbers used by Linux/IR. Random numbers which must be unique to &n; *  give the best protection&n; */
DECL|macro|IRTTY_MAGIC
mdefine_line|#define IRTTY_MAGIC        0x2357
DECL|macro|LAP_MAGIC
mdefine_line|#define LAP_MAGIC          0x1357
DECL|macro|LMP_MAGIC
mdefine_line|#define LMP_MAGIC          0x4321
DECL|macro|LMP_LSAP_MAGIC
mdefine_line|#define LMP_LSAP_MAGIC     0x69333
DECL|macro|LMP_LAP_MAGIC
mdefine_line|#define LMP_LAP_MAGIC      0x3432
DECL|macro|IRDA_DEVICE_MAGIC
mdefine_line|#define IRDA_DEVICE_MAGIC  0x63454
DECL|macro|IAS_MAGIC
mdefine_line|#define IAS_MAGIC          0x007
DECL|macro|TTP_MAGIC
mdefine_line|#define TTP_MAGIC          0x241169
DECL|macro|TTP_TSAP_MAGIC
mdefine_line|#define TTP_TSAP_MAGIC     0x4345
DECL|macro|IROBEX_MAGIC
mdefine_line|#define IROBEX_MAGIC       0x341324
DECL|macro|HB_MAGIC
mdefine_line|#define HB_MAGIC           0x64534
DECL|macro|IRLAN_MAGIC
mdefine_line|#define IRLAN_MAGIC        0x754
DECL|macro|IAS_OBJECT_MAGIC
mdefine_line|#define IAS_OBJECT_MAGIC   0x34234
DECL|macro|IAS_ATTRIB_MAGIC
mdefine_line|#define IAS_ATTRIB_MAGIC   0x45232
DECL|macro|IAS_DEVICE_ID
mdefine_line|#define IAS_DEVICE_ID 0x5342
DECL|macro|IAS_PNP_ID
mdefine_line|#define IAS_PNP_ID    0xd342
DECL|macro|IAS_OBEX_ID
mdefine_line|#define IAS_OBEX_ID   0x34323
DECL|macro|IAS_IRLAN_ID
mdefine_line|#define IAS_IRLAN_ID  0x34234
DECL|macro|IAS_IRCOMM_ID
mdefine_line|#define IAS_IRCOMM_ID 0x2343
DECL|macro|IAS_IRLPT_ID
mdefine_line|#define IAS_IRLPT_ID  0x9876
macro_line|#endif /* IRDA_H */
eof
