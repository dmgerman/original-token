multiline_comment|/* These structs are used by the system-use-sharing protocol, in which the&n;   Rock Ridge extensions are imbedded.  It is quite possible that other&n;   extensions are present on the disk, and this is fine as long as they&n;   all use SUSP */
DECL|struct|SU_SP
r_struct
id|SU_SP
(brace
DECL|member|magic
r_int
r_char
id|magic
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|skip
r_int
r_char
id|skip
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|SU_CE
r_struct
id|SU_CE
(brace
DECL|member|extent
r_char
id|extent
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|offset
r_char
id|offset
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|size
r_char
id|size
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|SU_ER
r_struct
id|SU_ER
(brace
DECL|member|len_id
r_int
r_char
id|len_id
suffix:semicolon
DECL|member|len_des
r_int
r_char
id|len_des
suffix:semicolon
DECL|member|len_src
r_int
r_char
id|len_src
suffix:semicolon
DECL|member|ext_ver
r_int
r_char
id|ext_ver
suffix:semicolon
DECL|member|data
r_char
id|data
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|RR_RR
r_struct
id|RR_RR
(brace
DECL|member|flags
r_char
id|flags
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|RR_PX
r_struct
id|RR_PX
(brace
DECL|member|mode
r_char
id|mode
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|n_links
r_char
id|n_links
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|uid
r_char
id|uid
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|gid
r_char
id|gid
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|RR_PN
r_struct
id|RR_PN
(brace
DECL|member|dev_high
r_char
id|dev_high
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|dev_low
r_char
id|dev_low
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|SL_component
r_struct
id|SL_component
(brace
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|member|len
r_int
r_char
id|len
suffix:semicolon
DECL|member|text
r_char
id|text
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|RR_SL
r_struct
id|RR_SL
(brace
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|member|link
r_struct
id|SL_component
id|link
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|RR_NM
r_struct
id|RR_NM
(brace
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|RR_CL
r_struct
id|RR_CL
(brace
DECL|member|location
r_char
id|location
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|RR_PL
r_struct
id|RR_PL
(brace
DECL|member|location
r_char
id|location
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|stamp
r_struct
id|stamp
(brace
DECL|member|time
r_char
id|time
(braket
l_int|7
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|RR_TF
r_struct
id|RR_TF
(brace
DECL|member|flags
r_char
id|flags
suffix:semicolon
DECL|member|times
r_struct
id|stamp
id|times
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Variable number of these beasts */
)brace
suffix:semicolon
multiline_comment|/* These are the bits and their meanings for flags in the TF structure. */
DECL|macro|TF_CREATE
mdefine_line|#define TF_CREATE 1
DECL|macro|TF_MODIFY
mdefine_line|#define TF_MODIFY 2
DECL|macro|TF_ACCESS
mdefine_line|#define TF_ACCESS 4
DECL|macro|TF_ATTRIBUTES
mdefine_line|#define TF_ATTRIBUTES 8
DECL|macro|TF_BACKUP
mdefine_line|#define TF_BACKUP 16
DECL|macro|TF_EXPIRATION
mdefine_line|#define TF_EXPIRATION 32
DECL|macro|TF_EFFECTIVE
mdefine_line|#define TF_EFFECTIVE 64
DECL|macro|TF_LONG_FORM
mdefine_line|#define TF_LONG_FORM 128
DECL|struct|rock_ridge
r_struct
id|rock_ridge
(brace
DECL|member|signature
r_char
id|signature
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|len
r_int
r_char
id|len
suffix:semicolon
DECL|member|version
r_int
r_char
id|version
suffix:semicolon
(def_block
r_union
(brace
DECL|member|SP
r_struct
id|SU_SP
id|SP
suffix:semicolon
DECL|member|CE
r_struct
id|SU_CE
id|CE
suffix:semicolon
DECL|member|ER
r_struct
id|SU_ER
id|ER
suffix:semicolon
DECL|member|RR
r_struct
id|RR_RR
id|RR
suffix:semicolon
DECL|member|PX
r_struct
id|RR_PX
id|PX
suffix:semicolon
DECL|member|PN
r_struct
id|RR_PN
id|PN
suffix:semicolon
DECL|member|SL
r_struct
id|RR_SL
id|SL
suffix:semicolon
DECL|member|NM
r_struct
id|RR_NM
id|NM
suffix:semicolon
DECL|member|CL
r_struct
id|RR_CL
id|CL
suffix:semicolon
DECL|member|PL
r_struct
id|RR_PL
id|PL
suffix:semicolon
DECL|member|TF
r_struct
id|RR_TF
id|TF
suffix:semicolon
DECL|member|u
)brace
)def_block
id|u
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RR_PX
mdefine_line|#define RR_PX 1   /* POSIX attributes */
DECL|macro|RR_PN
mdefine_line|#define RR_PN 2   /* POSIX devices */
DECL|macro|RR_SL
mdefine_line|#define RR_SL 4   /* Symbolic link */
DECL|macro|RR_NM
mdefine_line|#define RR_NM 8   /* Alternate Name */
DECL|macro|RR_CL
mdefine_line|#define RR_CL 16  /* Child link */
DECL|macro|RR_PL
mdefine_line|#define RR_PL 32  /* Parent link */
DECL|macro|RR_RE
mdefine_line|#define RR_RE 64  /* Relocation directory */
DECL|macro|RR_TF
mdefine_line|#define RR_TF 128 /* Timestamps */
eof
