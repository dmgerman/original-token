multiline_comment|/* Tests for presence or absence of hardware registers.&n; * This code was originally in atari/config.c, but I noticed&n; * that it was also in drivers/nubus/nubus.c and I wanted to&n; * use it in hp300/config.c, so it seemed sensible to pull it&n; * out into its own file.&n; * &n; * The test is for use when trying to read a hardware register&n; * that isn&squot;t present would cause a bus error. We set up a &n; * temporary handler so that this doesn&squot;t kill the kernel.&n; *&n; * There is a test-by-reading and a test-by-writing; I present&n; * them here complete with the comments from the original atari&n; * config.c...&n; *                -- PMM &lt;pmaydell@chiark.greenend.org.uk&gt;, 05/1998&n; */
multiline_comment|/* This function tests for the presence of an address, specially a&n; * hardware register address. It is called very early in the kernel&n; * initialization process, when the VBR register isn&squot;t set up yet. On&n; * an Atari, it still points to address 0, which is unmapped. So a bus&n; * error would cause another bus error while fetching the exception&n; * vector, and the CPU would do nothing at all. So we needed to set up&n; * a temporary VBR and a vector table for the duration of the test.&n; */
DECL|function|hwreg_present
r_int
id|hwreg_present
c_func
(paren
r_volatile
r_void
op_star
id|regp
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_int
id|save_sp
comma
id|save_vbr
suffix:semicolon
r_int
id|tmp_vectors
(braket
l_int|3
)braket
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;movec&t;%/vbr,%2&bslash;n&bslash;t&quot;
l_string|&quot;movel&t;#Lberr1,%4@(8)&bslash;n&bslash;t&quot;
l_string|&quot;movec&t;%4,%/vbr&bslash;n&bslash;t&quot;
l_string|&quot;movel&t;%/sp,%1&bslash;n&bslash;t&quot;
l_string|&quot;moveq&t;#0,%0&bslash;n&bslash;t&quot;
l_string|&quot;tstb&t;%3@&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;moveq&t;#1,%0&bslash;n&quot;
l_string|&quot;Lberr1:&bslash;n&bslash;t&quot;
l_string|&quot;movel&t;%1,%/sp&bslash;n&bslash;t&quot;
l_string|&quot;movec&t;%2,%/vbr&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|ret
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|save_sp
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|save_vbr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|regp
)paren
comma
l_string|&quot;a&quot;
(paren
id|tmp_vectors
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Basically the same, but writes a value into a word register, protected&n; * by a bus error handler. Returns 1 if successful, 0 otherwise.&n; */
DECL|function|hwreg_write
r_int
id|hwreg_write
c_func
(paren
r_volatile
r_void
op_star
id|regp
comma
r_int
r_int
id|val
)paren
(brace
r_int
id|ret
suffix:semicolon
r_int
id|save_sp
comma
id|save_vbr
suffix:semicolon
r_int
id|tmp_vectors
(braket
l_int|3
)braket
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;movec&t;%/vbr,%2&bslash;n&bslash;t&quot;
l_string|&quot;movel&t;#Lberr2,%4@(8)&bslash;n&bslash;t&quot;
l_string|&quot;movec&t;%4,%/vbr&bslash;n&bslash;t&quot;
l_string|&quot;movel&t;%/sp,%1&bslash;n&bslash;t&quot;
l_string|&quot;moveq&t;#0,%0&bslash;n&bslash;t&quot;
l_string|&quot;movew&t;%5,%3@&bslash;n&bslash;t&quot;
l_string|&quot;nop&t;&bslash;n&bslash;t&quot;
multiline_comment|/* If this nop isn&squot;t present, &squot;ret&squot; may already be&n;&t;&t;&t;&t; * loaded with 1 at the time the bus error&n;&t;&t;&t;&t; * happens! */
l_string|&quot;moveq&t;#1,%0&bslash;n&quot;
l_string|&quot;Lberr2:&bslash;n&bslash;t&quot;
l_string|&quot;movel&t;%1,%/sp&bslash;n&bslash;t&quot;
l_string|&quot;movec&t;%2,%/vbr&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|ret
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|save_sp
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|save_vbr
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|regp
)paren
comma
l_string|&quot;a&quot;
(paren
id|tmp_vectors
)paren
comma
l_string|&quot;g&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
