multiline_comment|/*&n; *&t;Apple Peripheral System Controller (PSC)&n; *&n; *&t;The PSC is used on the AV Macs to control IO functions not handled&n; *&t;by the VIAs (Ethernet, DSP, SCC).&n; */
DECL|macro|PSCBASE
mdefine_line|#define PSCBASE&t;&t;0x50F31000
multiline_comment|/*&n; *&t;The IER/IFR registers work like the VIA, except that it has 4&n; *&t;of them each on different interrupt levels.&n; */
DECL|macro|pIFR3
mdefine_line|#define pIFR3&t;&t;0x130
DECL|macro|pIFR4
mdefine_line|#define pIFR4&t;&t;0x140
DECL|macro|pIFR5
mdefine_line|#define pIFR5&t;&t;0x150
DECL|macro|pIFR6
mdefine_line|#define pIFR6&t;&t;0x160
DECL|macro|pIER3
mdefine_line|#define pIER3&t;&t;0x134
DECL|macro|pIER4
mdefine_line|#define pIER4&t;&t;0x144
DECL|macro|pIER5
mdefine_line|#define pIER5&t;&t;0x154
DECL|macro|pIER6
mdefine_line|#define pIER6&t;&t;0x164
multiline_comment|/*&n; *&t;Ethernet Control Registers&n; */
DECL|macro|PSC_ENETRD_CTL
mdefine_line|#define PSC_ENETRD_CTL  0xc10
DECL|macro|PSC_ENETWR_CTL
mdefine_line|#define PSC_ENETWR_CTL  0xc20
multiline_comment|/*&n; *&t;Receive DMA channel (add +0x10 for 2nd channel)&n; */
DECL|macro|PSC_ENETRD_ADDR
mdefine_line|#define PSC_ENETRD_ADDR 0x1020 
DECL|macro|PSC_ENETRD_LEN
mdefine_line|#define PSC_ENETRD_LEN  0x1024
DECL|macro|PSC_ENETRD_CMD
mdefine_line|#define PSC_ENETRD_CMD  0x1028
multiline_comment|/*&n; *&t;Transmit DMA channel (add +0x10 for 2nd channel)&n; */
DECL|macro|PSC_ENETWR_ADDR
mdefine_line|#define PSC_ENETWR_ADDR 0x1040
DECL|macro|PSC_ENETWR_LEN
mdefine_line|#define PSC_ENETWR_LEN  0x1044
DECL|macro|PSC_ENETWR_CMD
mdefine_line|#define PSC_ENETWR_CMD  0x1048
multiline_comment|/*&n; *&t;Access functions&n; */
r_extern
r_volatile
r_int
r_char
op_star
id|psc
suffix:semicolon
DECL|function|psc_write_word
r_extern
r_inline
r_void
id|psc_write_word
c_func
(paren
r_int
id|offset
comma
id|u16
id|data
)paren
(brace
op_star
(paren
(paren
r_volatile
id|u16
op_star
)paren
(paren
id|psc
op_plus
id|offset
)paren
)paren
op_assign
id|data
suffix:semicolon
)brace
DECL|function|psc_write_long
r_extern
r_inline
r_void
id|psc_write_long
c_func
(paren
r_int
id|offset
comma
id|u32
id|data
)paren
(brace
op_star
(paren
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|psc
op_plus
id|offset
)paren
)paren
op_assign
id|data
suffix:semicolon
)brace
DECL|function|psc_read_word
r_extern
r_inline
id|u16
id|psc_read_word
c_func
(paren
r_int
id|offset
)paren
(brace
r_return
op_star
(paren
(paren
r_volatile
id|u16
op_star
)paren
(paren
id|psc
op_plus
id|offset
)paren
)paren
suffix:semicolon
)brace
DECL|function|psc_read_long
r_extern
r_inline
id|u32
id|psc_read_long
c_func
(paren
r_int
id|offset
)paren
(brace
r_return
op_star
(paren
(paren
r_volatile
id|u32
op_star
)paren
(paren
id|psc
op_plus
id|offset
)paren
)paren
suffix:semicolon
)brace
eof
