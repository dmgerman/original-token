multiline_comment|/*&n; * $Id: kernelcapi.h,v 1.1 1997/03/04 21:27:33 calle Exp $&n; * &n; * Kernel CAPI 2.0 Interface for Linux&n; * &n; * (c) Copyright 1997 by Carsten Paeth (calle@calle.in-berlin.de)&n; * &n; * $Log: kernelcapi.h,v $&n; * Revision 1.1  1997/03/04 21:27:33  calle&n; * First version in isdn4linux&n; *&n; * Revision 2.2  1997/02/12 09:31:39  calle&n; * new version&n; *&n; * Revision 1.1  1997/01/31 10:32:20  calle&n; * Initial revision&n; *&n; * &n; */
macro_line|#ifndef __KERNEL_CAPI_H__
DECL|macro|__KERNEL_CAPI_H__
mdefine_line|#define __KERNEL_CAPI_H__
DECL|macro|CAPI_MAXAPPL
mdefine_line|#define CAPI_MAXAPPL&t;20&t;/*&n;&t;&t;&t;&t;   * maximum number of applications &n;&t;&t;&t;&t; */
DECL|macro|CAPI_MAXCONTR
mdefine_line|#define CAPI_MAXCONTR&t;4&t;/*&n;&t;&t;&t;&t;   * maximum number of controller &n;&t;&t;&t;&t; */
DECL|macro|CAPI_MAXDATAWINDOW
mdefine_line|#define CAPI_MAXDATAWINDOW&t;8
macro_line|#ifdef __KERNEL__
DECL|struct|capi_interface
r_struct
id|capi_interface
(brace
DECL|member|capi_installed
r_int
(paren
op_star
id|capi_installed
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|capi_register
id|__u16
c_func
(paren
op_star
id|capi_register
)paren
(paren
id|capi_register_params
op_star
id|rparam
comma
id|__u16
op_star
id|applidp
)paren
suffix:semicolon
DECL|member|capi_release
id|__u16
c_func
(paren
op_star
id|capi_release
)paren
(paren
id|__u16
id|applid
)paren
suffix:semicolon
DECL|member|capi_put_message
id|__u16
c_func
(paren
op_star
id|capi_put_message
)paren
(paren
id|__u16
id|applid
comma
r_struct
id|sk_buff
op_star
id|msg
)paren
suffix:semicolon
DECL|member|capi_get_message
id|__u16
c_func
(paren
op_star
id|capi_get_message
)paren
(paren
id|__u16
id|applid
comma
r_struct
id|sk_buff
op_star
op_star
id|msgp
)paren
suffix:semicolon
DECL|member|capi_set_signal
id|__u16
c_func
(paren
op_star
id|capi_set_signal
)paren
(paren
id|__u16
id|applid
comma
r_void
(paren
op_star
id|signal
)paren
(paren
id|__u16
id|applid
comma
id|__u32
id|param
)paren
comma
id|__u32
id|param
)paren
suffix:semicolon
DECL|member|capi_get_manufacturer
id|__u16
c_func
(paren
op_star
id|capi_get_manufacturer
)paren
(paren
id|__u16
id|contr
comma
id|__u8
id|buf
(braket
id|CAPI_MANUFACTURER_LEN
)braket
)paren
suffix:semicolon
DECL|member|capi_get_version
id|__u16
c_func
(paren
op_star
id|capi_get_version
)paren
(paren
id|__u16
id|contr
comma
r_struct
id|capi_version
op_star
id|verp
)paren
suffix:semicolon
DECL|member|capi_get_serial
id|__u16
c_func
(paren
op_star
id|capi_get_serial
)paren
(paren
id|__u16
id|contr
comma
id|__u8
id|serial
(braket
id|CAPI_SERIAL_LEN
)braket
)paren
suffix:semicolon
DECL|member|capi_get_profile
id|__u16
c_func
(paren
op_star
id|capi_get_profile
)paren
(paren
id|__u16
id|contr
comma
r_struct
id|capi_profile
op_star
id|profp
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * to init controllers, data is always in user memory&n;&t; */
DECL|member|capi_manufacturer
r_int
(paren
op_star
id|capi_manufacturer
)paren
(paren
r_int
r_int
id|cmd
comma
r_void
op_star
id|data
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|KCI_CONTRUP
mdefine_line|#define&t;KCI_CONTRUP&t;0
DECL|macro|KCI_CONTRDOWN
mdefine_line|#define&t;KCI_CONTRDOWN&t;1
DECL|struct|capi_interface_user
r_struct
id|capi_interface_user
(brace
DECL|member|name
r_char
id|name
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|callback
r_void
(paren
op_star
id|callback
)paren
(paren
r_int
r_int
id|cmd
comma
id|__u16
id|contr
comma
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|member|next
r_struct
id|capi_interface_user
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|capi_interface
op_star
id|attach_capi_interface
c_func
(paren
r_struct
id|capi_interface_user
op_star
)paren
suffix:semicolon
r_int
id|detach_capi_interface
c_func
(paren
r_struct
id|capi_interface_user
op_star
)paren
suffix:semicolon
DECL|macro|CAPI_NOERROR
mdefine_line|#define CAPI_NOERROR                      0x0000
DECL|macro|CAPI_TOOMANYAPPLS
mdefine_line|#define CAPI_TOOMANYAPPLS&t;&t;  0x1001
DECL|macro|CAPI_LOGBLKSIZETOSMALL
mdefine_line|#define CAPI_LOGBLKSIZETOSMALL&t;          0x1002
DECL|macro|CAPI_BUFFEXECEEDS64K
mdefine_line|#define CAPI_BUFFEXECEEDS64K &t;          0x1003
DECL|macro|CAPI_MSGBUFSIZETOOSMALL
mdefine_line|#define CAPI_MSGBUFSIZETOOSMALL&t;          0x1004
DECL|macro|CAPI_ANZLOGCONNNOTSUPPORTED
mdefine_line|#define CAPI_ANZLOGCONNNOTSUPPORTED&t;  0x1005
DECL|macro|CAPI_REGRESERVED
mdefine_line|#define CAPI_REGRESERVED&t;&t;  0x1006
DECL|macro|CAPI_REGBUSY
mdefine_line|#define CAPI_REGBUSY &t;&t;          0x1007
DECL|macro|CAPI_REGOSRESOURCEERR
mdefine_line|#define CAPI_REGOSRESOURCEERR&t;          0x1008
DECL|macro|CAPI_REGNOTINSTALLED
mdefine_line|#define CAPI_REGNOTINSTALLED &t;          0x1009
DECL|macro|CAPI_REGCTRLERNOTSUPPORTEXTEQUIP
mdefine_line|#define CAPI_REGCTRLERNOTSUPPORTEXTEQUIP  0x100a
DECL|macro|CAPI_REGCTRLERONLYSUPPORTEXTEQUIP
mdefine_line|#define CAPI_REGCTRLERONLYSUPPORTEXTEQUIP 0x100b
DECL|macro|CAPI_ILLAPPNR
mdefine_line|#define CAPI_ILLAPPNR&t;&t;          0x1101
DECL|macro|CAPI_ILLCMDORSUBCMDORMSGTOSMALL
mdefine_line|#define CAPI_ILLCMDORSUBCMDORMSGTOSMALL   0x1102
DECL|macro|CAPI_SENDQUEUEFULL
mdefine_line|#define CAPI_SENDQUEUEFULL&t;&t;  0x1103
DECL|macro|CAPI_RECEIVEQUEUEEMPTY
mdefine_line|#define CAPI_RECEIVEQUEUEEMPTY&t;          0x1104
DECL|macro|CAPI_RECEIVEOVERFLOW
mdefine_line|#define CAPI_RECEIVEOVERFLOW &t;          0x1105
DECL|macro|CAPI_UNKNOWNNOTPAR
mdefine_line|#define CAPI_UNKNOWNNOTPAR&t;&t;  0x1106
DECL|macro|CAPI_MSGBUSY
mdefine_line|#define CAPI_MSGBUSY &t;&t;          0x1107
DECL|macro|CAPI_MSGOSRESOURCEERR
mdefine_line|#define CAPI_MSGOSRESOURCEERR&t;          0x1108
DECL|macro|CAPI_MSGNOTINSTALLED
mdefine_line|#define CAPI_MSGNOTINSTALLED &t;          0x1109
DECL|macro|CAPI_MSGCTRLERNOTSUPPORTEXTEQUIP
mdefine_line|#define CAPI_MSGCTRLERNOTSUPPORTEXTEQUIP  0x110a
DECL|macro|CAPI_MSGCTRLERONLYSUPPORTEXTEQUIP
mdefine_line|#define CAPI_MSGCTRLERONLYSUPPORTEXTEQUIP 0x110b
macro_line|#endif&t;&t;&t;&t;/* __KERNEL__ */
macro_line|#endif&t;&t;&t;&t;/* __KERNEL_CAPI_H__ */
eof
