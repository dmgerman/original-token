multiline_comment|/********************************************************************** &n; * Reading the NVRAM on the Interphase 5526 PCI Fibre Channel Card. &n; * All contents in this file : courtesy Interphase Corporation.&n; * Special thanks to Kevin Quick, kquick@iphase.com.&n; **********************************************************************/
DECL|macro|FF_MAGIC
mdefine_line|#define FF_MAGIC        0x4646
DECL|macro|DB_MAGIC
mdefine_line|#define DB_MAGIC        0x4442
DECL|macro|DL_MAGIC
mdefine_line|#define DL_MAGIC        0x444d
DECL|macro|CMD_LEN
mdefine_line|#define CMD_LEN         9
multiline_comment|/***********&n; *&n; *      Switches and defines for header files.&n; *&n; *      The following defines are used to turn on and off&n; *      various options in the header files. Primarily useful&n; *      for debugging.&n; *&n; ***********/
DECL|variable|novram_default
r_static
r_const
r_int
r_int
id|novram_default
(braket
l_int|4
)braket
op_assign
(brace
id|FF_MAGIC
comma
id|DB_MAGIC
comma
id|DL_MAGIC
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/*&n; * a list of the commands that can be sent to the NOVRAM&n; */
DECL|macro|NR_EXTEND
mdefine_line|#define NR_EXTEND  0x100
DECL|macro|NR_WRITE
mdefine_line|#define NR_WRITE   0x140
DECL|macro|NR_READ
mdefine_line|#define NR_READ    0x180
DECL|macro|NR_ERASE
mdefine_line|#define NR_ERASE   0x1c0
DECL|macro|EWDS
mdefine_line|#define EWDS    0x00
DECL|macro|WRAL
mdefine_line|#define WRAL    0x10
DECL|macro|ERAL
mdefine_line|#define ERAL    0x20
DECL|macro|EWEN
mdefine_line|#define EWEN    0x30
multiline_comment|/*&n; * Defines for the pins on the NOVRAM&n; */
DECL|macro|BIT
mdefine_line|#define BIT(x)          (1 &lt;&lt; (x))
DECL|macro|NVDI_B
mdefine_line|#define NVDI_B          31
DECL|macro|NVDI
mdefine_line|#define NVDI            BIT(NVDI_B)
DECL|macro|NVDO
mdefine_line|#define NVDO            BIT(9)
DECL|macro|NVCE
mdefine_line|#define NVCE            BIT(30)
DECL|macro|NVSK
mdefine_line|#define NVSK            BIT(29)
DECL|macro|NV_MANUAL
mdefine_line|#define NV_MANUAL       BIT(28)
multiline_comment|/***********&n; *&n; *      Include files.&n; *&n; ***********/
DECL|macro|KeStallExecutionProcessor
mdefine_line|#define KeStallExecutionProcessor(x)    {volatile int d, p;&bslash;&n;&t;&t;  for (d=0; d&lt;x; d++) for (p=0; p&lt;10; p++);&bslash;&n;&t;&t;&t;&t;     }
multiline_comment|/***********************&n; *&n; * This define ands the value and the current config register and puts&n; * the result in the config register&n; *&n; ***********************/
DECL|macro|CFG_AND
mdefine_line|#define CFG_AND(val) { volatile int t; &bslash;&n;&t;&t;&t;   t = readl(fi-&gt;n_r.ptr_novram_hw_control_reg);   &bslash;&n;&t;&t;&t;   t &amp;= (val);                                  &bslash;&n;&t;&t;&t;   writel(t, fi-&gt;n_r.ptr_novram_hw_control_reg);   &bslash;&n;&t;&t;   }
multiline_comment|/***********************&n; *&n; * This define ors the value and the current config register and puts&n; * the result in the config register&n; *&n; ***********************/
DECL|macro|CFG_OR
mdefine_line|#define CFG_OR(val) { volatile int t; &bslash;&n;&t;&t;&t;   t = readl(fi-&gt;n_r.ptr_novram_hw_control_reg);   &bslash;&n;&t;&t;&t;   t |= (val);                                  &bslash;&n;&t;&t;&t;   writel(t, fi-&gt;n_r.ptr_novram_hw_control_reg);   &bslash;&n;&t;&t;   }
multiline_comment|/***********************&n; *&n; * Send a command to the NOVRAM, the command is in cmd.&n; *&n; * clear CE and SK. Then assert CE.&n; * Clock each of the command bits out in the correct order with SK&n; * exit with CE still asserted&n; *&n; ***********************/
DECL|macro|NVRAM_CMD
mdefine_line|#define NVRAM_CMD(cmd) { int i; &bslash;&n;&t;&t;&t; int c = cmd; &bslash;&n;&t;&t;&t; CFG_AND(~(NVCE|NVSK)); &bslash;&n;&t;&t;&t; CFG_OR(NVCE); &bslash;&n;&t;&t;&t; for (i=0; i&lt;CMD_LEN; i++) { &bslash;&n;&t;&t;&t;     NVRAM_CLKOUT((c &amp; (1 &lt;&lt; (CMD_LEN - 1))) ? 1 : 0);&bslash;&n;&t;&t;&t;     c &lt;&lt;= 1; } }
multiline_comment|/***********************&n; *&n; * clear the CE, this must be used after each command is complete&n; *&n; ***********************/
DECL|macro|NVRAM_CLR_CE
mdefine_line|#define NVRAM_CLR_CE    CFG_AND(~NVCE)
multiline_comment|/***********************&n; *&n; * clock the data bit in bitval out to the NOVRAM.  The bitval must be&n; * a 1 or 0, or the clockout operation is undefined&n; *&n; ***********************/
DECL|macro|NVRAM_CLKOUT
mdefine_line|#define NVRAM_CLKOUT(bitval) {&bslash;&n;&t;&t;&t;   CFG_AND(~NVDI); &bslash;&n;&t;&t;&t;   CFG_OR((bitval) &lt;&lt; NVDI_B); &bslash;&n;&t;&t;&t;   KeStallExecutionProcessor(5);&bslash;&n;&t;&t;&t;   CFG_OR(NVSK); &bslash;&n;&t;&t;&t;   KeStallExecutionProcessor(5);&bslash;&n;&t;&t;&t;   CFG_AND( ~NVSK); &bslash;&n;&t;&t;&t;   }
multiline_comment|/***********************&n; *&n; * clock the data bit in and return a 1 or 0, depending on the value&n; * that was received from the NOVRAM&n; *&n; ***********************/
DECL|macro|NVRAM_CLKIN
mdefine_line|#define NVRAM_CLKIN(val)        {&bslash;&n;&t;&t;       CFG_OR(NVSK); &bslash;&n;&t;&t;&t;   KeStallExecutionProcessor(5);&bslash;&n;&t;&t;       CFG_AND(~NVSK); &bslash;&n;&t;&t;&t;   KeStallExecutionProcessor(5);&bslash;&n;&t;&t;       val = (readl(fi-&gt;n_r.ptr_novram_hw_status_reg) &amp; NVDO) ? 1 : 0; &bslash;&n;&t;&t;       }
multiline_comment|/***********&n; *&n; *      Function Prototypes&n; *&n; ***********/
r_static
r_int
id|iph5526_nr_get
c_func
(paren
r_struct
id|fc_info
op_star
id|fi
comma
r_int
id|addr
)paren
suffix:semicolon
r_static
r_void
id|iph5526_nr_do_init
c_func
(paren
r_struct
id|fc_info
op_star
id|fi
)paren
suffix:semicolon
r_static
r_void
id|iph5526_nr_checksum
c_func
(paren
r_struct
id|fc_info
op_star
id|fi
)paren
suffix:semicolon
multiline_comment|/*******************************************************************&n; *&n; *      Local routine:  iph5526_nr_do_init&n; *      Purpose:        initialize novram server&n; *      Description:&n; *&n; *      iph5526_nr_do_init reads the novram into the temporary holding place.&n; *      A checksum is done on the area and the Magic Cookies are checked.&n; *      If any of them are bad, the NOVRAM is initialized with the &n; *      default values and a warning message is displayed.&n; *&n; *******************************************************************/
DECL|function|iph5526_nr_do_init
r_static
r_void
id|iph5526_nr_do_init
c_func
(paren
r_struct
id|fc_info
op_star
id|fi
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|chksum
op_assign
l_int|0
suffix:semicolon
r_int
id|bad
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|IPH5526_NOVRAM_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|fi-&gt;n_r.data
(braket
id|i
)braket
op_assign
id|iph5526_nr_get
c_func
(paren
id|fi
comma
id|i
)paren
suffix:semicolon
id|chksum
op_add_assign
id|fi-&gt;n_r.data
(braket
id|i
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chksum
)paren
id|bad
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|fi-&gt;n_r.data
(braket
id|IPH5526_NOVRAM_SIZE
op_minus
l_int|4
)braket
op_ne
id|FF_MAGIC
)paren
id|bad
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|fi-&gt;n_r.data
(braket
id|IPH5526_NOVRAM_SIZE
op_minus
l_int|3
)braket
op_ne
id|DB_MAGIC
)paren
id|bad
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|fi-&gt;n_r.data
(braket
id|IPH5526_NOVRAM_SIZE
op_minus
l_int|2
)braket
op_ne
id|DL_MAGIC
)paren
id|bad
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|bad
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|IPH5526_NOVRAM_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
OL
(paren
id|IPH5526_NOVRAM_SIZE
op_minus
l_int|4
)paren
)paren
(brace
id|fi-&gt;n_r.data
(braket
id|i
)braket
op_assign
l_int|0xffff
suffix:semicolon
)brace
r_else
(brace
id|fi-&gt;n_r.data
(braket
id|i
)braket
op_assign
id|novram_default
(braket
id|i
op_minus
(paren
id|IPH5526_NOVRAM_SIZE
op_minus
l_int|4
)paren
)braket
suffix:semicolon
)brace
)brace
id|iph5526_nr_checksum
c_func
(paren
id|fi
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************&n; *&n; *      Local routine:  iph5526_nr_get&n; *      Purpose:        read a single word of NOVRAM&n; *      Description:&n; *&n; *      read the 16 bits that make up a word addr of the novram.  &n; *      The 16 bits of data that are read are returned as the return value&n; *&n; *******************************************************************/
DECL|function|iph5526_nr_get
r_static
r_int
id|iph5526_nr_get
c_func
(paren
r_struct
id|fc_info
op_star
id|fi
comma
r_int
id|addr
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|t
suffix:semicolon
r_int
id|val
op_assign
l_int|0
suffix:semicolon
id|CFG_OR
c_func
(paren
id|NV_MANUAL
)paren
suffix:semicolon
multiline_comment|/*&n;     * read the first bit that was clocked with the falling edge of the&n;     * the last command data clock&n;     */
id|NVRAM_CMD
c_func
(paren
id|NR_READ
op_plus
id|addr
)paren
suffix:semicolon
multiline_comment|/*&n;     * Now read the rest of the bits, the next bit read is D1, then D2,&n;     * and so on&n;     */
id|val
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|NVRAM_CLKIN
c_func
(paren
id|t
)paren
suffix:semicolon
id|val
op_lshift_assign
l_int|1
suffix:semicolon
id|val
op_or_assign
id|t
suffix:semicolon
)brace
id|NVRAM_CLR_CE
suffix:semicolon
id|CFG_OR
c_func
(paren
id|NVDI
)paren
suffix:semicolon
id|CFG_AND
c_func
(paren
op_complement
id|NV_MANUAL
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/*******************************************************************&n; *&n; *      Local routine:  iph5526_nr_checksum&n; *      Purpose:        calculate novram checksum on fi-&gt;n_r.data&n; *      Description:&n; *&n; *      calculate a checksum for the novram on the image that is&n; *      currently in fi-&gt;n_r.data&n; *&n; *******************************************************************/
DECL|function|iph5526_nr_checksum
r_static
r_void
id|iph5526_nr_checksum
c_func
(paren
r_struct
id|fc_info
op_star
id|fi
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|chksum
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
id|IPH5526_NOVRAM_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|i
op_increment
)paren
id|chksum
op_add_assign
id|fi-&gt;n_r.data
(braket
id|i
)braket
suffix:semicolon
id|fi-&gt;n_r.data
(braket
id|i
)braket
op_assign
op_minus
id|chksum
suffix:semicolon
)brace
eof
