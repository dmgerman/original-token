multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irda.h&n; * Version:       &n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Mon Mar  8 14:06:12 1999&n; * Modified at:   Mon Mar 22 14:14:54 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1999 Dag Brattli, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#ifndef KERNEL_IRDA_H
DECL|macro|KERNEL_IRDA_H
mdefine_line|#define KERNEL_IRDA_H
multiline_comment|/* Hint bit positions for first hint byte */
DECL|macro|HINT_PNP
mdefine_line|#define HINT_PNP         0x01
DECL|macro|HINT_PDA
mdefine_line|#define HINT_PDA         0x02
DECL|macro|HINT_COMPUTER
mdefine_line|#define HINT_COMPUTER    0x04
DECL|macro|HINT_PRINTER
mdefine_line|#define HINT_PRINTER     0x08
DECL|macro|HINT_MODEM
mdefine_line|#define HINT_MODEM       0x10
DECL|macro|HINT_FAX
mdefine_line|#define HINT_FAX         0x20
DECL|macro|HINT_LAN
mdefine_line|#define HINT_LAN         0x40
DECL|macro|HINT_EXTENSION
mdefine_line|#define HINT_EXTENSION   0x80
multiline_comment|/* Hint bit positions for second hint byte (first extension byte) */
DECL|macro|HINT_TELEPHONY
mdefine_line|#define HINT_TELEPHONY   0x01
DECL|macro|HINT_FILE_SERVER
mdefine_line|#define HINT_FILE_SERVER 0x02
DECL|macro|HINT_COMM
mdefine_line|#define HINT_COMM        0x04
DECL|macro|HINT_MESSAGE
mdefine_line|#define HINT_MESSAGE     0x08
DECL|macro|HINT_HTTP
mdefine_line|#define HINT_HTTP        0x10
DECL|macro|HINT_OBEX
mdefine_line|#define HINT_OBEX        0x20
multiline_comment|/* IrLMP character code values */
DECL|macro|CS_ASCII
mdefine_line|#define CS_ASCII       0x00
DECL|macro|CS_ISO_8859_1
mdefine_line|#define&t;CS_ISO_8859_1  0x01
DECL|macro|CS_ISO_8859_2
mdefine_line|#define&t;CS_ISO_8859_2  0x02
DECL|macro|CS_ISO_8859_3
mdefine_line|#define&t;CS_ISO_8859_3  0x03
DECL|macro|CS_ISO_8859_4
mdefine_line|#define&t;CS_ISO_8859_4  0x04
DECL|macro|CS_ISO_8859_5
mdefine_line|#define&t;CS_ISO_8859_5  0x05
DECL|macro|CS_ISO_8859_6
mdefine_line|#define&t;CS_ISO_8859_6  0x06
DECL|macro|CS_ISO_8859_7
mdefine_line|#define&t;CS_ISO_8859_7  0x07
DECL|macro|CS_ISO_8859_8
mdefine_line|#define&t;CS_ISO_8859_8  0x08
DECL|macro|CS_ISO_8859_9
mdefine_line|#define&t;CS_ISO_8859_9  0x09
DECL|macro|CS_UNICODE
mdefine_line|#define CS_UNICODE     0xff
DECL|macro|SOL_IRLMP
mdefine_line|#define SOL_IRLMP      266 /* Same as SOL_IRDA for now */
DECL|macro|SOL_IRTTP
mdefine_line|#define SOL_IRTTP      266 /* Same as SOL_IRDA for now */
DECL|macro|IRLMP_ENUMDEVICES
mdefine_line|#define IRLMP_ENUMDEVICES        1
DECL|macro|IRLMP_IAS_SET
mdefine_line|#define IRLMP_IAS_SET            2
DECL|macro|IRLMP_IAS_QUERY
mdefine_line|#define IRLMP_IAS_QUERY          3
DECL|macro|IRLMP_DISCOVERY_MASK_SET
mdefine_line|#define IRLMP_DISCOVERY_MASK_SET 4
DECL|macro|IRTTP_QOS_SET
mdefine_line|#define IRTTP_QOS_SET            5
DECL|macro|IRTTP_QOS_GET
mdefine_line|#define IRTTP_QOS_GET            6
DECL|macro|IRTTP_MAX_SDU_SIZE
mdefine_line|#define IRTTP_MAX_SDU_SIZE       7
DECL|macro|IAS_MAX_STRING
mdefine_line|#define IAS_MAX_STRING           256
DECL|macro|IAS_MAX_OCTET_STRING
mdefine_line|#define IAS_MAX_OCTET_STRING     1024
DECL|macro|IAS_MAX_CLASSNAME
mdefine_line|#define IAS_MAX_CLASSNAME        64
DECL|macro|IAS_MAX_ATTRIBNAME
mdefine_line|#define IAS_MAX_ATTRIBNAME       256
DECL|macro|LSAP_ANY
mdefine_line|#define LSAP_ANY                 0xff
DECL|struct|sockaddr_irda
r_struct
id|sockaddr_irda
(brace
DECL|member|sir_family
id|sa_family_t
id|sir_family
suffix:semicolon
multiline_comment|/* AF_IRDA */
DECL|member|sir_lsap_sel
r_int
r_char
id|sir_lsap_sel
suffix:semicolon
multiline_comment|/* LSAP/TSAP selector */
DECL|member|sir_addr
r_int
r_int
id|sir_addr
suffix:semicolon
multiline_comment|/* Device address */
DECL|member|sir_name
r_char
id|sir_name
(braket
l_int|25
)braket
suffix:semicolon
multiline_comment|/* Usually &lt;service&gt;:IrDA:TinyTP */
)brace
suffix:semicolon
DECL|struct|irda_device_info
r_struct
id|irda_device_info
(brace
DECL|member|saddr
r_int
r_int
id|saddr
suffix:semicolon
multiline_comment|/* Address of remote device */
DECL|member|daddr
r_int
r_int
id|daddr
suffix:semicolon
multiline_comment|/* Link where it was discovered */
DECL|member|info
r_char
id|info
(braket
l_int|22
)braket
suffix:semicolon
multiline_comment|/* Description */
DECL|member|charset
r_int
r_char
id|charset
suffix:semicolon
multiline_comment|/* Charset used for description */
DECL|member|hints
r_int
r_char
id|hints
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Hint bits */
)brace
suffix:semicolon
DECL|struct|irda_device_list
r_struct
id|irda_device_list
(brace
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|dev
r_struct
id|irda_device_info
id|dev
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|irda_ias_set
r_struct
id|irda_ias_set
(brace
DECL|member|irda_class_name
r_char
id|irda_class_name
(braket
id|IAS_MAX_CLASSNAME
)braket
suffix:semicolon
DECL|member|irda_attrib_name
r_char
id|irda_attrib_name
(braket
id|IAS_MAX_ATTRIBNAME
)braket
suffix:semicolon
DECL|member|irda_attrib_type
r_int
r_int
id|irda_attrib_type
suffix:semicolon
r_union
(brace
DECL|member|irda_attrib_int
r_int
r_int
id|irda_attrib_int
suffix:semicolon
r_struct
(brace
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|OctetSeq
id|u_char
id|OctetSeq
(braket
id|IAS_MAX_OCTET_STRING
)braket
suffix:semicolon
DECL|member|irda_attrib_octet_seq
)brace
id|irda_attrib_octet_seq
suffix:semicolon
r_struct
(brace
DECL|member|len
r_int
r_char
id|len
suffix:semicolon
DECL|member|charset
r_int
r_char
id|charset
suffix:semicolon
DECL|member|string
r_int
r_char
id|string
(braket
id|IAS_MAX_STRING
)braket
suffix:semicolon
DECL|member|irda_attrib_string
)brace
id|irda_attrib_string
suffix:semicolon
DECL|member|attribute
)brace
id|attribute
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* KERNEL_IRDA_H */
eof
