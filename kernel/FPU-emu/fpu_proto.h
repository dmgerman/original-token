multiline_comment|/* errors.c */
r_extern
r_void
id|Un_impl
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|emu_printall
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|exception
c_func
(paren
r_int
id|n
)paren
suffix:semicolon
r_extern
r_void
id|real_2op_NaN
c_func
(paren
r_struct
id|fpu_reg
op_star
id|a
comma
r_struct
id|fpu_reg
op_star
id|b
comma
r_struct
id|fpu_reg
op_star
id|dest
)paren
suffix:semicolon
r_extern
r_void
id|arith_invalid
c_func
(paren
r_struct
id|fpu_reg
op_star
id|dest
)paren
suffix:semicolon
r_extern
r_void
id|divide_by_zero
c_func
(paren
r_int
id|sign
comma
r_struct
id|fpu_reg
op_star
id|dest
)paren
suffix:semicolon
r_extern
r_void
id|arith_overflow
c_func
(paren
r_struct
id|fpu_reg
op_star
id|dest
)paren
suffix:semicolon
r_extern
r_void
id|arith_underflow
c_func
(paren
r_struct
id|fpu_reg
op_star
id|dest
)paren
suffix:semicolon
r_extern
r_void
id|stack_overflow
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|stack_underflow
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* fpu_arith.c */
r_extern
r_void
id|fadd__
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fmul__
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fsub__
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fsubr_
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fdiv__
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fdivr_
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fadd_i
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fmul_i
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fsubri
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fsub_i
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fdivri
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fdiv_i
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|faddp_
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fmulp_
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fsubrp
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fsubp_
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fdivrp
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fdivp_
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* fpu_aux.c */
r_extern
r_void
id|finit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|finit_
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fstsw_
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fp_nop
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fld_i_
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fxch_i
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ffree_
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fst_i_
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fstp_i
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* fpu_entry.c */
r_extern
r_void
id|math_emulate
c_func
(paren
r_int
id|arg
)paren
suffix:semicolon
multiline_comment|/* fpu_etc.c */
r_extern
r_void
id|fp_etc
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* fpu_trig.c */
r_extern
r_void
id|convert_l2reg
c_func
(paren
r_int
op_star
id|arg
comma
r_struct
id|fpu_reg
op_star
id|dest
)paren
suffix:semicolon
r_extern
r_void
id|trig_a
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|trig_b
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* get_address.c */
r_extern
r_void
id|get_address
c_func
(paren
r_int
r_char
id|FPU_modrm
)paren
suffix:semicolon
multiline_comment|/* load_store.c */
r_extern
r_void
id|load_store_instr
c_func
(paren
r_char
id|type
)paren
suffix:semicolon
multiline_comment|/* poly_2xm1.c */
r_extern
r_int
id|poly_2xm1
c_func
(paren
r_struct
id|fpu_reg
op_star
id|arg
comma
r_struct
id|fpu_reg
op_star
id|result
)paren
suffix:semicolon
multiline_comment|/* poly_atan.c */
r_extern
r_void
id|poly_atan
c_func
(paren
r_struct
id|fpu_reg
op_star
id|arg
)paren
suffix:semicolon
r_extern
r_void
id|poly_add_1
c_func
(paren
r_struct
id|fpu_reg
op_star
id|src
)paren
suffix:semicolon
multiline_comment|/* poly_l2.c */
r_extern
r_void
id|poly_l2
c_func
(paren
r_struct
id|fpu_reg
op_star
id|arg
comma
r_struct
id|fpu_reg
op_star
id|result
)paren
suffix:semicolon
r_extern
r_int
id|poly_l2p1
c_func
(paren
r_struct
id|fpu_reg
op_star
id|arg
comma
r_struct
id|fpu_reg
op_star
id|result
)paren
suffix:semicolon
multiline_comment|/* poly_sin.c */
r_extern
r_void
id|poly_sine
c_func
(paren
r_struct
id|fpu_reg
op_star
id|arg
comma
r_struct
id|fpu_reg
op_star
id|result
)paren
suffix:semicolon
multiline_comment|/* poly_tan.c */
r_extern
r_void
id|poly_tan
c_func
(paren
r_struct
id|fpu_reg
op_star
id|arg
comma
r_struct
id|fpu_reg
op_star
id|y_reg
)paren
suffix:semicolon
multiline_comment|/* reg_add_sub.c */
r_extern
r_void
id|reg_add
c_func
(paren
r_struct
id|fpu_reg
op_star
id|a
comma
r_struct
id|fpu_reg
op_star
id|b
comma
r_struct
id|fpu_reg
op_star
id|dest
)paren
suffix:semicolon
r_extern
r_void
id|reg_sub
c_func
(paren
r_struct
id|fpu_reg
op_star
id|a
comma
r_struct
id|fpu_reg
op_star
id|b
comma
r_struct
id|fpu_reg
op_star
id|dest
)paren
suffix:semicolon
multiline_comment|/* reg_compare.c */
r_extern
r_int
id|compare
c_func
(paren
r_struct
id|fpu_reg
op_star
id|b
)paren
suffix:semicolon
r_extern
r_void
id|compare_st_data
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fcom_st
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fcompst
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fcompp
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fucom_
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fucomp
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fucompp
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* reg_constant.c */
r_extern
r_void
id|fconst
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* reg_ld_str.c */
r_extern
r_void
id|reg_load_extended
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|reg_load_double
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|reg_load_single
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|reg_load_int64
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|reg_load_int32
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|reg_load_int16
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|reg_load_bcd
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|reg_store_extended
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|reg_store_double
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|reg_store_single
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|reg_store_int64
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|reg_store_int32
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|reg_store_int16
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|reg_store_bcd
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|round_to_int
c_func
(paren
r_struct
id|fpu_reg
op_star
id|r
)paren
suffix:semicolon
r_extern
r_char
op_star
id|fldenv
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|frstor
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_char
op_star
id|fstenv
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fsave
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* reg_mul.c */
r_extern
r_void
id|reg_mul
c_func
(paren
r_struct
id|fpu_reg
op_star
id|a
comma
r_struct
id|fpu_reg
op_star
id|b
comma
r_struct
id|fpu_reg
op_star
id|dest
)paren
suffix:semicolon
eof
