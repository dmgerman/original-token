multiline_comment|/*&n; * linux/include/asm-arm/arch-brutus/uncompress.h&n; *&n; * (C) 1999 Nicolas Pitre &lt;nico@cam.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if&t;defined(CONFIG_SA1100_EMPEG) || &bslash;&n;&t;defined(CONFIG_SA1100_VICTOR) || &bslash;&n;&t;defined(CONFIG_SA1100_LART)
DECL|macro|SERBASE
mdefine_line|#define SERBASE _Ser3UTCR0;
macro_line|#elif&t;defined(CONFIG_SA1100_BRUTUS)
DECL|macro|SERBASE
mdefine_line|#define SERBASE _Ser1UTCR0;
macro_line|#endif
macro_line|#ifdef SERBASE
macro_line|#include &quot;hardware.h&quot;
macro_line|#include &quot;serial_reg.h&quot;
DECL|variable|serial_port
r_static
r_volatile
r_int
r_int
op_star
id|serial_port
op_assign
(paren
r_int
r_int
op_star
)paren
id|SERBASE
suffix:semicolon
multiline_comment|/*&n; * The following code assumes the serial port has already been&n; * initialized by the bootloader or such...&n; */
DECL|function|puts
r_static
r_void
id|puts
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
op_star
id|s
suffix:semicolon
id|i
op_increment
comma
id|s
op_increment
)paren
(brace
multiline_comment|/* wait for space in the UART&squot;s transmiter */
r_while
c_loop
(paren
op_logical_neg
(paren
id|serial_port
(braket
id|UTSR1
)braket
op_amp
id|UTSR1_TNF
)paren
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* send the character out. */
id|serial_port
(braket
id|UART_TX
)braket
op_assign
op_star
id|s
suffix:semicolon
multiline_comment|/* if a LF, also do CR... */
r_if
c_cond
(paren
op_star
id|s
op_eq
l_int|10
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|serial_port
(braket
id|UTSR1
)braket
op_amp
id|UTSR1_TNF
)paren
)paren
(brace
suffix:semicolon
)brace
id|serial_port
(braket
id|UART_TX
)braket
op_assign
l_int|13
suffix:semicolon
)brace
)brace
)brace
macro_line|#else
DECL|function|puts
r_static
r_inline
r_void
id|puts
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
)brace
macro_line|#endif
multiline_comment|/* Nothing to do for these */
DECL|macro|arch_decomp_setup
mdefine_line|#define arch_decomp_setup()
DECL|macro|arch_decomp_wdog
mdefine_line|#define arch_decomp_wdog()
eof
