macro_line|#ifndef _LINUX_ISDN_PPP_H
DECL|macro|_LINUX_ISDN_PPP_H
mdefine_line|#define _LINUX_ISDN_PPP_H
r_extern
r_int
id|isdn_ppp_dial_slave
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_ppp_hangup_slave
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
DECL|macro|CALLTYPE_INCOMING
mdefine_line|#define CALLTYPE_INCOMING 0x1
DECL|macro|CALLTYPE_OUTGOING
mdefine_line|#define CALLTYPE_OUTGOING 0x2
DECL|macro|CALLTYPE_CALLBACK
mdefine_line|#define CALLTYPE_CALLBACK 0x4
DECL|struct|pppcallinfo
r_struct
id|pppcallinfo
(brace
DECL|member|calltype
r_int
id|calltype
suffix:semicolon
DECL|member|local_num
r_int
r_char
id|local_num
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|remote_num
r_int
r_char
id|remote_num
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|charge_units
r_int
id|charge_units
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PPPIOCGCALLINFO
mdefine_line|#define PPPIOCGCALLINFO _IOWR(&squot;t&squot;,128,struct pppcallinfo)
DECL|macro|PPPIOCBUNDLE
mdefine_line|#define PPPIOCBUNDLE   _IOW(&squot;t&squot;,129,int)
DECL|macro|PPPIOCGMPFLAGS
mdefine_line|#define PPPIOCGMPFLAGS _IOR(&squot;t&squot;,130,int)
DECL|macro|PPPIOCSMPFLAGS
mdefine_line|#define PPPIOCSMPFLAGS _IOW(&squot;t&squot;,131,int)
DECL|macro|PPPIOCSMPMTU
mdefine_line|#define PPPIOCSMPMTU   _IOW(&squot;t&squot;,132,int)
DECL|macro|PPPIOCSMPMRU
mdefine_line|#define PPPIOCSMPMRU   _IOW(&squot;t&squot;,133,int)
DECL|macro|PPP_MP
mdefine_line|#define PPP_MP         0x003d
DECL|macro|SC_MP_PROT
mdefine_line|#define SC_MP_PROT       0x00000200
DECL|macro|SC_REJ_MP_PROT
mdefine_line|#define SC_REJ_MP_PROT   0x00000400
DECL|macro|SC_OUT_SHORT_SEQ
mdefine_line|#define SC_OUT_SHORT_SEQ 0x00000800
DECL|macro|SC_IN_SHORT_SEQ
mdefine_line|#define SC_IN_SHORT_SEQ  0x00004000
DECL|macro|MP_END_FRAG
mdefine_line|#define MP_END_FRAG    0x40
DECL|macro|MP_BEGIN_FRAG
mdefine_line|#define MP_BEGIN_FRAG  0x80
macro_line|#endif
eof
