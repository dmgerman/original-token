multiline_comment|/*&n; * arch/sparc/kernel/traps.c&n; *&n; * Copyright 1994 David S. Miller (davem@caip.rutgers.edu)&n; */
multiline_comment|/*&n; * I hate traps on the sparc, grrr...&n; */
DECL|function|do_hw_interrupt
r_void
id|do_hw_interrupt
c_func
(paren
r_int
r_int
id|type
comma
r_int
r_int
id|vector
)paren
(brace
r_if
c_cond
(paren
id|vector
op_eq
l_int|14
)paren
(brace
id|jiffies
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Just print garbage for everything else for now. */
id|printk
c_func
(paren
l_string|&quot;Unimplemented Sparc TRAP, vector = %lx type = %lx&bslash;n&quot;
comma
id|vector
comma
id|type
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_extern
r_int
r_int
op_star
id|trapbase
suffix:semicolon
DECL|function|trap_init
r_void
id|trap_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* load up the trap table */
id|__asm__
c_func
(paren
l_string|&quot;wr %0, 0x0, %%tbr&bslash;n&bslash;t&quot;
l_string|&quot;nop; nop; nop&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|trapbase
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
