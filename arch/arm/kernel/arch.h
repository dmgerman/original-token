DECL|struct|machine_desc
r_struct
id|machine_desc
(brace
DECL|member|nr
r_int
r_int
id|nr
suffix:semicolon
multiline_comment|/* architecture number&t;*/
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* architecture name&t;*/
DECL|member|param_offset
r_int
r_int
id|param_offset
suffix:semicolon
multiline_comment|/* parameter page&t;*/
DECL|member|video_start
r_int
r_int
id|video_start
suffix:semicolon
multiline_comment|/* start of video RAM&t;*/
DECL|member|video_end
r_int
r_int
id|video_end
suffix:semicolon
multiline_comment|/* end of video RAM&t;*/
DECL|member|reserve_lp0
r_int
r_int
id|reserve_lp0
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* never has lp0&t;*/
DECL|member|reserve_lp1
r_int
r_int
id|reserve_lp1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* never has lp1&t;*/
DECL|member|reserve_lp2
r_int
r_int
id|reserve_lp2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* never has lp2&t;*/
DECL|member|broken_hlt
r_int
r_int
id|broken_hlt
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* hlt is broken&t;*/
DECL|member|soft_reboot
r_int
r_int
id|soft_reboot
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* soft reboot&t;&t;*/
DECL|member|fixup
r_void
(paren
op_star
id|fixup
)paren
(paren
r_struct
id|machine_desc
op_star
comma
r_struct
id|param_struct
op_star
comma
r_char
op_star
op_star
comma
r_struct
id|meminfo
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
eof
