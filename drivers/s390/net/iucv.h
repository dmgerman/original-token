multiline_comment|/*&n; *  drivers/s390/net/iucv.h&n; *    Network driver for VM using iucv&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Stefan Hegewald &lt;hegewald@de.ibm.com&gt;&n; *               Hartmut Penner &lt;hpenner@de.ibm.com&gt; &n; */
macro_line|#ifndef _IUCV_H
DECL|macro|_IUCV_H
mdefine_line|#define _IUCV_H
DECL|macro|UCHAR
mdefine_line|#define UCHAR  unsigned char
DECL|macro|USHORT
mdefine_line|#define USHORT unsigned short
DECL|macro|ULONG
mdefine_line|#define ULONG  unsigned long
DECL|macro|DEFAULT_BUFFERSIZE
mdefine_line|#define DEFAULT_BUFFERSIZE  2048
DECL|macro|DEFAULT_FN_LENGTH
mdefine_line|#define DEFAULT_FN_LENGTH   27
DECL|macro|TRANSFERLENGTH
mdefine_line|#define TRANSFERLENGTH      10
multiline_comment|/* function ID&squot;s */
DECL|macro|RETRIEVE_BUFFER
mdefine_line|#define RETRIEVE_BUFFER 2
DECL|macro|REPLY
mdefine_line|#define REPLY           3
DECL|macro|SEND
mdefine_line|#define SEND            4
DECL|macro|RECEIVE
mdefine_line|#define RECEIVE         5
DECL|macro|ACCEPT
mdefine_line|#define ACCEPT          10
DECL|macro|CONNECT
mdefine_line|#define CONNECT         11
DECL|macro|DECLARE_BUFFER
mdefine_line|#define DECLARE_BUFFER  12
DECL|macro|SEVER
mdefine_line|#define SEVER           15
DECL|macro|SETMASK
mdefine_line|#define SETMASK         16
DECL|macro|SETCMASK
mdefine_line|#define SETCMASK        17
DECL|macro|PURGE
mdefine_line|#define PURGE           9999
multiline_comment|/* structures */
r_typedef
r_struct
(brace
DECL|member|res0
id|USHORT
id|res0
suffix:semicolon
DECL|member|ipflags1
id|UCHAR
id|ipflags1
suffix:semicolon
DECL|member|iprcode
id|UCHAR
id|iprcode
suffix:semicolon
DECL|member|res1
id|ULONG
id|res1
suffix:semicolon
DECL|member|res2
id|ULONG
id|res2
suffix:semicolon
DECL|member|ipbfadr1
id|ULONG
id|ipbfadr1
suffix:semicolon
DECL|member|res
id|ULONG
id|res
(braket
l_int|6
)braket
suffix:semicolon
DECL|typedef|DCLBFR_T
)brace
id|DCLBFR_T
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ippathid
id|USHORT
id|ippathid
suffix:semicolon
DECL|member|ipflags1
id|UCHAR
id|ipflags1
suffix:semicolon
DECL|member|iprcode
id|UCHAR
id|iprcode
suffix:semicolon
DECL|member|ipmsglim
id|USHORT
id|ipmsglim
suffix:semicolon
DECL|member|res1
id|USHORT
id|res1
suffix:semicolon
DECL|member|ipvmid
id|UCHAR
id|ipvmid
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ipuser
id|UCHAR
id|ipuser
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|iptarget
id|UCHAR
id|iptarget
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|CONNECT_T
)brace
id|CONNECT_T
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ippathid
id|USHORT
id|ippathid
suffix:semicolon
DECL|member|ipflags1
id|UCHAR
id|ipflags1
suffix:semicolon
DECL|member|iprcode
id|UCHAR
id|iprcode
suffix:semicolon
DECL|member|ipmsglim
id|USHORT
id|ipmsglim
suffix:semicolon
DECL|member|res1
id|USHORT
id|res1
suffix:semicolon
DECL|member|res2
id|UCHAR
id|res2
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ipuser
id|UCHAR
id|ipuser
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|res3
id|UCHAR
id|res3
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|ACCEPT_T
)brace
id|ACCEPT_T
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ippathid
id|USHORT
id|ippathid
suffix:semicolon
DECL|member|ipflags1
id|UCHAR
id|ipflags1
suffix:semicolon
DECL|member|iprcode
id|UCHAR
id|iprcode
suffix:semicolon
DECL|member|ipmsgid
id|ULONG
id|ipmsgid
suffix:semicolon
DECL|member|iptrgcls
id|ULONG
id|iptrgcls
suffix:semicolon
DECL|member|ipbfadr1
id|ULONG
id|ipbfadr1
suffix:semicolon
DECL|member|ipbfln1f
id|ULONG
id|ipbfln1f
suffix:semicolon
DECL|member|ipsrccls
id|ULONG
id|ipsrccls
suffix:semicolon
DECL|member|ipmsgtag
id|ULONG
id|ipmsgtag
suffix:semicolon
DECL|member|ipbfadr2
id|ULONG
id|ipbfadr2
suffix:semicolon
DECL|member|ipbfln2f
id|ULONG
id|ipbfln2f
suffix:semicolon
DECL|member|res
id|ULONG
id|res
suffix:semicolon
DECL|typedef|SEND_T
)brace
id|SEND_T
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ippathid
id|USHORT
id|ippathid
suffix:semicolon
DECL|member|ipflags1
id|UCHAR
id|ipflags1
suffix:semicolon
DECL|member|iprcode
id|UCHAR
id|iprcode
suffix:semicolon
DECL|member|ipmsgid
id|ULONG
id|ipmsgid
suffix:semicolon
DECL|member|iptrgcls
id|ULONG
id|iptrgcls
suffix:semicolon
DECL|member|iprmmsg1
id|ULONG
id|iprmmsg1
suffix:semicolon
DECL|member|iprmmsg2
id|ULONG
id|iprmmsg2
suffix:semicolon
DECL|member|res1
id|ULONG
id|res1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|ipbfadr2
id|ULONG
id|ipbfadr2
suffix:semicolon
DECL|member|ipbfln2f
id|ULONG
id|ipbfln2f
suffix:semicolon
DECL|member|res2
id|ULONG
id|res2
suffix:semicolon
DECL|typedef|REPLY_T
)brace
id|REPLY_T
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ippathid
id|USHORT
id|ippathid
suffix:semicolon
DECL|member|ipflags1
id|UCHAR
id|ipflags1
suffix:semicolon
DECL|member|iprcode
id|UCHAR
id|iprcode
suffix:semicolon
DECL|member|ipmsgid
id|ULONG
id|ipmsgid
suffix:semicolon
DECL|member|iptrgcls
id|ULONG
id|iptrgcls
suffix:semicolon
DECL|member|ipbfadr1
id|ULONG
id|ipbfadr1
suffix:semicolon
DECL|member|ipbfln1f
id|ULONG
id|ipbfln1f
suffix:semicolon
DECL|member|res1
id|ULONG
id|res1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ipbfln2f
id|ULONG
id|ipbfln2f
suffix:semicolon
DECL|member|res2
id|ULONG
id|res2
suffix:semicolon
DECL|typedef|RECEIVE_T
)brace
id|RECEIVE_T
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ippathid
id|USHORT
id|ippathid
suffix:semicolon
DECL|member|ipflags1
id|UCHAR
id|ipflags1
suffix:semicolon
DECL|member|iprcode
id|UCHAR
id|iprcode
suffix:semicolon
DECL|member|res1
id|ULONG
id|res1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ipuser
id|UCHAR
id|ipuser
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|res2
id|ULONG
id|res2
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|SEVER_T
)brace
id|SEVER_T
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ipmask
id|UCHAR
id|ipmask
suffix:semicolon
DECL|member|res1
id|UCHAR
id|res1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|iprcode
id|UCHAR
id|iprcode
suffix:semicolon
DECL|member|res2
id|ULONG
id|res2
(braket
l_int|9
)braket
suffix:semicolon
DECL|typedef|MASK_T
)brace
id|MASK_T
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ippathid
id|USHORT
id|ippathid
suffix:semicolon
DECL|member|ipflags1
id|UCHAR
id|ipflags1
suffix:semicolon
DECL|member|iptype
id|UCHAR
id|iptype
suffix:semicolon
DECL|member|ipmsgid
id|ULONG
id|ipmsgid
suffix:semicolon
DECL|member|ipaudit
id|ULONG
id|ipaudit
suffix:semicolon
DECL|member|iprmmsg1
id|ULONG
id|iprmmsg1
suffix:semicolon
DECL|member|iprmmsg2
id|ULONG
id|iprmmsg2
suffix:semicolon
DECL|member|ipsrccls
id|ULONG
id|ipsrccls
suffix:semicolon
DECL|member|ipmsgtag
id|ULONG
id|ipmsgtag
suffix:semicolon
DECL|member|ipbfadr2
id|ULONG
id|ipbfadr2
suffix:semicolon
DECL|member|ipbfln2f
id|ULONG
id|ipbfln2f
suffix:semicolon
DECL|member|ippollfg
id|UCHAR
id|ippollfg
suffix:semicolon
DECL|member|res2
id|UCHAR
id|res2
(braket
l_int|3
)braket
suffix:semicolon
DECL|typedef|INTERRUPT_T
)brace
id|INTERRUPT_T
suffix:semicolon
macro_line|#endif
eof
