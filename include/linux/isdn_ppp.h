r_extern
r_int
id|isdn_ppp_dial_slave
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
DECL|struct|pppinfo
r_struct
id|pppinfo
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* set by user */
r_union
(brace
DECL|member|clid
r_char
id|clid
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* calling ID */
DECL|member|bundles
r_int
id|bundles
suffix:semicolon
DECL|member|linknumber
r_int
id|linknumber
suffix:semicolon
DECL|member|info
)brace
id|info
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PPPIOCLINKINFO
mdefine_line|#define PPPIOCLINKINFO _IOWR(&squot;t&squot;,128,struct pppinfo)
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
eof
