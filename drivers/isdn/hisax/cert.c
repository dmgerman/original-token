multiline_comment|/* $Id: cert.c,v 2.1 1998/11/15 23:51:15 keil Exp $&n;&n; * Author       Karsten Keil (keil@isdn4linux.de)&n; *&n; *&t;&t;This file is (c) under GNU PUBLIC LICENSE&n; *&t;&t;For changes and modifications please read&n; *&t;&t;../../../Documentation/isdn/HiSax.cert&n; *&n; * $Log: cert.c,v $&n; * Revision 2.1  1998/11/15 23:51:15  keil&n; * certification stuff&n; *&n; * Revision 1.2.2.1  1998/11/03 21:46:37  keil&n; * first version&n; *&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
r_int
DECL|function|certification_check
id|certification_check
c_func
(paren
r_int
id|output
)paren
(brace
macro_line|#ifdef CERTIFICATION
macro_line|#if CERTIFICATION == 0
r_if
c_cond
(paren
id|output
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: Approval certification valid&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: Approved with ELSA Quickstep series cards&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: Approval registration numbers:&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: German D133361J CETECOM ICT Services GmbH&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: EU (D133362J) CETECOM ICT Services GmbH&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#if CERTIFICATION == 1
r_if
c_cond
(paren
id|output
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: Approval certification failed because of&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: unauthorized source code changes&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
macro_line|#endif
macro_line|#if CERTIFICATION == 127
r_if
c_cond
(paren
id|output
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: Approval certification not possible&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: because &bslash;&quot;md5sum&bslash;&quot; is not available&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|2
suffix:semicolon
macro_line|#endif
macro_line|#else
r_if
c_cond
(paren
id|output
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;HiSax: Certification not verified&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|3
suffix:semicolon
macro_line|#endif
)brace
eof
