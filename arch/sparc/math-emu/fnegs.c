DECL|function|FNEGS
r_int
id|FNEGS
c_func
(paren
r_int
r_int
op_star
id|rd
comma
r_int
r_int
op_star
id|rs2
)paren
(brace
multiline_comment|/* just change the sign bit */
id|rd
(braket
l_int|0
)braket
op_assign
id|rs2
(braket
l_int|0
)braket
op_xor
l_int|0x80000000UL
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof