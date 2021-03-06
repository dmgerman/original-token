multiline_comment|/* Minimal serial functions needed to send messages out the serial&n; * port on SMC1.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &quot;asm/mpc8260.h&quot;
macro_line|#include &quot;asm/cpm_8260.h&quot;
DECL|variable|no_print
id|uint
id|no_print
suffix:semicolon
r_extern
r_char
op_star
id|params
(braket
)braket
suffix:semicolon
r_extern
r_int
id|nparams
suffix:semicolon
DECL|variable|cons_hold
DECL|variable|sgptr
r_static
id|u_char
id|cons_hold
(braket
l_int|128
)braket
comma
op_star
id|sgptr
suffix:semicolon
DECL|variable|cons_hold_cnt
r_static
r_int
id|cons_hold_cnt
suffix:semicolon
r_void
DECL|function|serial_init
id|serial_init
c_func
(paren
id|bd_t
op_star
id|bd
)paren
(brace
r_volatile
id|smc_t
op_star
id|sp
suffix:semicolon
r_volatile
id|smc_uart_t
op_star
id|up
suffix:semicolon
r_volatile
id|cbd_t
op_star
id|tbdf
comma
op_star
id|rbdf
suffix:semicolon
r_volatile
id|immap_t
op_star
id|ip
suffix:semicolon
r_volatile
id|iop8260_t
op_star
id|io
suffix:semicolon
r_volatile
id|cpm8260_t
op_star
id|cp
suffix:semicolon
id|uint
id|dpaddr
comma
id|memaddr
suffix:semicolon
id|ip
op_assign
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
suffix:semicolon
id|sp
op_assign
(paren
id|smc_t
op_star
)paren
op_amp
(paren
id|ip-&gt;im_smc
(braket
l_int|0
)braket
)paren
suffix:semicolon
op_star
(paren
id|ushort
op_star
)paren
(paren
op_amp
id|ip-&gt;im_dprambase
(braket
id|PROFF_SMC1_BASE
)braket
)paren
op_assign
id|PROFF_SMC1
suffix:semicolon
id|up
op_assign
(paren
id|smc_uart_t
op_star
)paren
op_amp
id|ip-&gt;im_dprambase
(braket
id|PROFF_SMC1
)braket
suffix:semicolon
id|cp
op_assign
op_amp
id|ip-&gt;im_cpm
suffix:semicolon
id|io
op_assign
op_amp
id|ip-&gt;im_ioport
suffix:semicolon
multiline_comment|/* Disable transmitter/receiver.&n;&t;*/
id|sp-&gt;smc_smcmr
op_and_assign
op_complement
(paren
id|SMCMR_REN
op_or
id|SMCMR_TEN
)paren
suffix:semicolon
multiline_comment|/* Use Port D for SMC1 instead of other functions.&n;&t;*/
id|io-&gt;iop_ppard
op_or_assign
l_int|0x00c00000
suffix:semicolon
id|io-&gt;iop_pdird
op_or_assign
l_int|0x00400000
suffix:semicolon
id|io-&gt;iop_pdird
op_and_assign
op_complement
l_int|0x00800000
suffix:semicolon
id|io-&gt;iop_psord
op_and_assign
op_complement
l_int|0x00c00000
suffix:semicolon
multiline_comment|/* Allocate space for two buffer descriptors in the DP ram.&n;&t; * For now, this address seems OK, but it may have to&n;&t; * change with newer versions of the firmware.&n;&t; */
id|dpaddr
op_assign
l_int|0x0800
suffix:semicolon
multiline_comment|/* Grab a few bytes from the top of memory.&n;&t; */
macro_line|#if 1
id|memaddr
op_assign
(paren
id|bd-&gt;bi_memsize
op_minus
l_int|256
)paren
op_amp
op_complement
l_int|15
suffix:semicolon
macro_line|#else
id|memaddr
op_assign
l_int|0x0f002c00
suffix:semicolon
macro_line|#endif
multiline_comment|/* Set the physical address of the host memory buffers in&n;&t; * the buffer descriptors.&n;&t; */
id|rbdf
op_assign
(paren
id|cbd_t
op_star
)paren
op_amp
id|ip-&gt;im_dprambase
(braket
id|dpaddr
)braket
suffix:semicolon
id|rbdf-&gt;cbd_bufaddr
op_assign
id|memaddr
suffix:semicolon
id|rbdf-&gt;cbd_sc
op_assign
l_int|0
suffix:semicolon
id|tbdf
op_assign
id|rbdf
op_plus
l_int|1
suffix:semicolon
id|tbdf-&gt;cbd_bufaddr
op_assign
id|memaddr
op_plus
l_int|128
suffix:semicolon
id|tbdf-&gt;cbd_sc
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set up the uart parameters in the parameter ram.&n;&t;*/
id|up-&gt;smc_rbase
op_assign
id|dpaddr
suffix:semicolon
id|up-&gt;smc_tbase
op_assign
id|dpaddr
op_plus
r_sizeof
(paren
id|cbd_t
)paren
suffix:semicolon
id|up-&gt;smc_rfcr
op_assign
id|CPMFCR_EB
suffix:semicolon
id|up-&gt;smc_tfcr
op_assign
id|CPMFCR_EB
suffix:semicolon
id|up-&gt;smc_brklen
op_assign
l_int|0
suffix:semicolon
id|up-&gt;smc_brkec
op_assign
l_int|0
suffix:semicolon
id|up-&gt;smc_brkcr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set UART mode, 8 bit, no parity, one stop.&n;&t; * Enable receive and transmit.&n;&t; */
id|sp-&gt;smc_smcmr
op_assign
id|smcr_mk_clen
c_func
(paren
l_int|9
)paren
op_or
id|SMCMR_SM_UART
suffix:semicolon
multiline_comment|/* Mask all interrupts and remove anything pending.&n;&t;*/
id|sp-&gt;smc_smcm
op_assign
l_int|0
suffix:semicolon
id|sp-&gt;smc_smce
op_assign
l_int|0xff
suffix:semicolon
multiline_comment|/* Set up the baud rate generator.&n;&t; */
id|ip-&gt;im_clkrst.car_sccr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* DIV 4 BRG */
id|ip-&gt;im_cpmux.cmx_smr
op_assign
l_int|0
suffix:semicolon
id|ip-&gt;im_brgc1
op_assign
(paren
(paren
(paren
(paren
id|bd-&gt;bi_brgfreq
op_star
l_int|1000000
)paren
op_div
l_int|16
)paren
op_div
id|bd-&gt;bi_baudrate
)paren
op_lshift
l_int|1
)paren
op_or
id|CPM_BRG_EN
suffix:semicolon
multiline_comment|/* Make the first buffer the only buffer.&n;&t;*/
id|tbdf-&gt;cbd_sc
op_or_assign
id|BD_SC_WRAP
suffix:semicolon
id|rbdf-&gt;cbd_sc
op_or_assign
id|BD_SC_EMPTY
op_or
id|BD_SC_WRAP
suffix:semicolon
macro_line|#if 0
multiline_comment|/* Single character receive.&n;&t;*/
id|up-&gt;smc_mrblr
op_assign
l_int|1
suffix:semicolon
id|up-&gt;smc_maxidl
op_assign
l_int|0
suffix:semicolon
macro_line|#else
id|up-&gt;smc_mrblr
op_assign
l_int|128
suffix:semicolon
id|up-&gt;smc_maxidl
op_assign
l_int|8
suffix:semicolon
macro_line|#endif
multiline_comment|/* Initialize Tx/Rx parameters.&n;&t;*/
id|cp-&gt;cp_cpcr
op_assign
id|mk_cr_cmd
c_func
(paren
id|CPM_CR_SMC1_PAGE
comma
id|CPM_CR_SMC1_SBLOCK
comma
l_int|0
comma
id|CPM_CR_INIT_TRX
)paren
op_or
id|CPM_CR_FLG
suffix:semicolon
r_while
c_loop
(paren
id|cp-&gt;cp_cpcr
op_amp
id|CPM_CR_FLG
)paren
suffix:semicolon
multiline_comment|/* Enable transmitter/receiver.&n;&t;*/
id|sp-&gt;smc_smcmr
op_or_assign
id|SMCMR_REN
op_or
id|SMCMR_TEN
suffix:semicolon
)brace
r_void
DECL|function|serial_putchar
id|serial_putchar
c_func
(paren
r_const
r_char
id|c
)paren
(brace
r_volatile
id|cbd_t
op_star
id|tbdf
suffix:semicolon
r_volatile
r_char
op_star
id|buf
suffix:semicolon
r_volatile
id|smc_uart_t
op_star
id|up
suffix:semicolon
r_volatile
id|immap_t
op_star
id|ip
suffix:semicolon
r_extern
id|bd_t
op_star
id|board_info
suffix:semicolon
id|ip
op_assign
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
suffix:semicolon
id|up
op_assign
(paren
id|smc_uart_t
op_star
)paren
op_amp
(paren
id|ip-&gt;im_dprambase
(braket
id|PROFF_SMC1
)braket
)paren
suffix:semicolon
id|tbdf
op_assign
(paren
id|cbd_t
op_star
)paren
op_amp
id|ip-&gt;im_dprambase
(braket
id|up-&gt;smc_tbase
)braket
suffix:semicolon
multiline_comment|/* Wait for last character to go.&n;&t;*/
id|buf
op_assign
(paren
r_char
op_star
)paren
id|tbdf-&gt;cbd_bufaddr
suffix:semicolon
r_while
c_loop
(paren
id|tbdf-&gt;cbd_sc
op_amp
id|BD_SC_READY
)paren
suffix:semicolon
op_star
id|buf
op_assign
id|c
suffix:semicolon
id|tbdf-&gt;cbd_datlen
op_assign
l_int|1
suffix:semicolon
id|tbdf-&gt;cbd_sc
op_or_assign
id|BD_SC_READY
suffix:semicolon
)brace
r_char
DECL|function|serial_getc
id|serial_getc
c_func
(paren
)paren
(brace
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|cons_hold_cnt
op_le
l_int|0
)paren
(brace
id|cons_hold_cnt
op_assign
id|serial_readbuf
c_func
(paren
id|cons_hold
)paren
suffix:semicolon
id|sgptr
op_assign
id|cons_hold
suffix:semicolon
)brace
id|c
op_assign
op_star
id|sgptr
op_increment
suffix:semicolon
id|cons_hold_cnt
op_decrement
suffix:semicolon
r_return
id|c
suffix:semicolon
)brace
r_int
DECL|function|serial_readbuf
id|serial_readbuf
c_func
(paren
id|u_char
op_star
id|cbuf
)paren
(brace
r_volatile
id|cbd_t
op_star
id|rbdf
suffix:semicolon
r_volatile
r_char
op_star
id|buf
suffix:semicolon
r_volatile
id|smc_uart_t
op_star
id|up
suffix:semicolon
r_volatile
id|immap_t
op_star
id|ip
suffix:semicolon
r_int
id|i
comma
id|nc
suffix:semicolon
id|ip
op_assign
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
suffix:semicolon
id|up
op_assign
(paren
id|smc_uart_t
op_star
)paren
op_amp
(paren
id|ip-&gt;im_dprambase
(braket
id|PROFF_SMC1
)braket
)paren
suffix:semicolon
id|rbdf
op_assign
(paren
id|cbd_t
op_star
)paren
op_amp
id|ip-&gt;im_dprambase
(braket
id|up-&gt;smc_rbase
)braket
suffix:semicolon
multiline_comment|/* Wait for character to show up.&n;&t;*/
id|buf
op_assign
(paren
r_char
op_star
)paren
id|rbdf-&gt;cbd_bufaddr
suffix:semicolon
r_while
c_loop
(paren
id|rbdf-&gt;cbd_sc
op_amp
id|BD_SC_EMPTY
)paren
suffix:semicolon
id|nc
op_assign
id|rbdf-&gt;cbd_datlen
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
id|nc
suffix:semicolon
id|i
op_increment
)paren
op_star
id|cbuf
op_increment
op_assign
op_star
id|buf
op_increment
suffix:semicolon
id|rbdf-&gt;cbd_sc
op_or_assign
id|BD_SC_EMPTY
suffix:semicolon
r_return
id|nc
suffix:semicolon
)brace
r_int
DECL|function|serial_tstc
id|serial_tstc
c_func
(paren
)paren
(brace
r_volatile
id|cbd_t
op_star
id|rbdf
suffix:semicolon
r_volatile
id|smc_uart_t
op_star
id|up
suffix:semicolon
r_volatile
id|immap_t
op_star
id|ip
suffix:semicolon
id|ip
op_assign
(paren
id|immap_t
op_star
)paren
id|IMAP_ADDR
suffix:semicolon
id|up
op_assign
(paren
id|smc_uart_t
op_star
)paren
op_amp
(paren
id|ip-&gt;im_dprambase
(braket
id|PROFF_SMC1
)braket
)paren
suffix:semicolon
id|rbdf
op_assign
(paren
id|cbd_t
op_star
)paren
op_amp
id|ip-&gt;im_dprambase
(braket
id|up-&gt;smc_rbase
)braket
suffix:semicolon
r_return
op_logical_neg
(paren
id|rbdf-&gt;cbd_sc
op_amp
id|BD_SC_EMPTY
)paren
suffix:semicolon
)brace
eof
