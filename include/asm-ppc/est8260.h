DECL|macro|IMAP_ADDR
mdefine_line|#define IMAP_ADDR&t;((uint)0xf0000000)
multiline_comment|/* A Board Information structure that is given to a program when&n; * prom starts it up.&n; */
DECL|struct|bd_info
r_typedef
r_struct
id|bd_info
(brace
DECL|member|bi_memstart
r_int
r_int
id|bi_memstart
suffix:semicolon
multiline_comment|/* Memory start address */
DECL|member|bi_memsize
r_int
r_int
id|bi_memsize
suffix:semicolon
multiline_comment|/* Memory (end) size in bytes */
DECL|member|bi_intfreq
r_int
r_int
id|bi_intfreq
suffix:semicolon
multiline_comment|/* Internal Freq, in Hz */
DECL|member|bi_busfreq
r_int
r_int
id|bi_busfreq
suffix:semicolon
multiline_comment|/* Bus Freq, in MHz */
DECL|member|bi_cpmfreq
r_int
r_int
id|bi_cpmfreq
suffix:semicolon
multiline_comment|/* CPM Freq, in MHz */
DECL|member|bi_brgfreq
r_int
r_int
id|bi_brgfreq
suffix:semicolon
multiline_comment|/* BRG Freq, in MHz */
DECL|member|bi_enetaddr
r_int
r_char
id|bi_enetaddr
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|bi_baudrate
r_int
r_int
id|bi_baudrate
suffix:semicolon
DECL|typedef|bd_t
)brace
id|bd_t
suffix:semicolon
r_extern
id|bd_t
id|m8xx_board_info
suffix:semicolon
eof
