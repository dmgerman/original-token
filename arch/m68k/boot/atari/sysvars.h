DECL|struct|_osheader
r_typedef
r_struct
id|_osheader
(brace
DECL|member|os_entry
r_int
r_int
id|os_entry
suffix:semicolon
DECL|member|os_version
r_int
r_int
id|os_version
suffix:semicolon
DECL|member|reseth
r_void
op_star
id|reseth
suffix:semicolon
DECL|member|os_beg
r_struct
id|_osheader
op_star
id|os_beg
suffix:semicolon
DECL|member|os_end
r_void
op_star
id|os_end
suffix:semicolon
DECL|member|os_rsv1
r_int
id|os_rsv1
suffix:semicolon
DECL|member|os_magic
r_void
op_star
id|os_magic
suffix:semicolon
DECL|member|os_date
r_int
id|os_date
suffix:semicolon
DECL|member|os_conf
r_int
r_int
id|os_conf
suffix:semicolon
DECL|member|os_dosdate
r_int
r_int
id|os_dosdate
suffix:semicolon
DECL|member|p_root
r_char
op_star
op_star
id|p_root
suffix:semicolon
DECL|member|pkbshift
r_int
r_char
op_star
op_star
id|pkbshift
suffix:semicolon
DECL|member|p_run
r_void
op_star
op_star
id|p_run
suffix:semicolon
DECL|member|p_rsv2
r_char
op_star
id|p_rsv2
suffix:semicolon
DECL|typedef|OSHEADER
)brace
id|OSHEADER
suffix:semicolon
DECL|macro|phystop
mdefine_line|#define phystop    ((unsigned long *)0x42e)
DECL|macro|_sysbase
mdefine_line|#define _sysbase   ((OSHEADER **)0x4f2)
DECL|macro|_p_cookies
mdefine_line|#define _p_cookies ((unsigned long **)0x5a0)
DECL|macro|ramtop
mdefine_line|#define ramtop     ((unsigned long *)0x5a4)
eof