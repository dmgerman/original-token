multiline_comment|/*&n; * Format of an instruction in memory.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_INST_H
DECL|macro|__ASM_MIPS_INST_H
mdefine_line|#define __ASM_MIPS_INST_H
multiline_comment|/*&n; * Major opcodes; before MIPS IV cop1x was called cop3.&n; */
DECL|enum|major_op
r_enum
id|major_op
(brace
DECL|enumerator|spec_op
DECL|enumerator|bcond_op
DECL|enumerator|j_op
DECL|enumerator|jal_op
id|spec_op
comma
id|bcond_op
comma
id|j_op
comma
id|jal_op
comma
DECL|enumerator|beq_op
DECL|enumerator|bne_op
DECL|enumerator|blez_op
DECL|enumerator|bgtz_op
id|beq_op
comma
id|bne_op
comma
id|blez_op
comma
id|bgtz_op
comma
DECL|enumerator|addi_op
DECL|enumerator|addiu_op
DECL|enumerator|slti_op
DECL|enumerator|sltiu_op
id|addi_op
comma
id|addiu_op
comma
id|slti_op
comma
id|sltiu_op
comma
DECL|enumerator|andi_op
DECL|enumerator|ori_op
DECL|enumerator|xori_op
DECL|enumerator|lui_op
id|andi_op
comma
id|ori_op
comma
id|xori_op
comma
id|lui_op
comma
DECL|enumerator|cop0_op
DECL|enumerator|cop1_op
DECL|enumerator|cop2_op
DECL|enumerator|cop1x_op
id|cop0_op
comma
id|cop1_op
comma
id|cop2_op
comma
id|cop1x_op
comma
DECL|enumerator|beql_op
DECL|enumerator|bnel_op
DECL|enumerator|blezl_op
DECL|enumerator|bgtzl_op
id|beql_op
comma
id|bnel_op
comma
id|blezl_op
comma
id|bgtzl_op
comma
DECL|enumerator|daddi_op
DECL|enumerator|daddiu_op
DECL|enumerator|ldl_op
DECL|enumerator|ldr_op
id|daddi_op
comma
id|daddiu_op
comma
id|ldl_op
comma
id|ldr_op
comma
DECL|enumerator|major_1c_op
DECL|enumerator|major_1d_op
DECL|enumerator|major_1e_op
DECL|enumerator|major_1f_op
id|major_1c_op
comma
id|major_1d_op
comma
id|major_1e_op
comma
id|major_1f_op
comma
DECL|enumerator|lb_op
DECL|enumerator|lh_op
DECL|enumerator|lwl_op
DECL|enumerator|lw_op
id|lb_op
comma
id|lh_op
comma
id|lwl_op
comma
id|lw_op
comma
DECL|enumerator|lbu_op
DECL|enumerator|lhu_op
DECL|enumerator|lwr_op
DECL|enumerator|lwu_op
id|lbu_op
comma
id|lhu_op
comma
id|lwr_op
comma
id|lwu_op
comma
DECL|enumerator|sb_op
DECL|enumerator|sh_op
DECL|enumerator|swl_op
DECL|enumerator|sw_op
id|sb_op
comma
id|sh_op
comma
id|swl_op
comma
id|sw_op
comma
DECL|enumerator|sdl_op
DECL|enumerator|sdr_op
DECL|enumerator|swr_op
DECL|enumerator|cache_op
id|sdl_op
comma
id|sdr_op
comma
id|swr_op
comma
id|cache_op
comma
DECL|enumerator|ll_op
DECL|enumerator|lwc1_op
DECL|enumerator|lwc2_op
DECL|enumerator|pref_op
id|ll_op
comma
id|lwc1_op
comma
id|lwc2_op
comma
id|pref_op
comma
DECL|enumerator|lld_op
DECL|enumerator|ldc1_op
DECL|enumerator|ldc2_op
DECL|enumerator|ld_op
id|lld_op
comma
id|ldc1_op
comma
id|ldc2_op
comma
id|ld_op
comma
DECL|enumerator|sc_op
DECL|enumerator|swc1_op
DECL|enumerator|swc2_op
DECL|enumerator|major_3b_op
id|sc_op
comma
id|swc1_op
comma
id|swc2_op
comma
id|major_3b_op
comma
multiline_comment|/* Opcode 0x3b is unused */
DECL|enumerator|scd_op
DECL|enumerator|sdc1_op
DECL|enumerator|sdc2_op
DECL|enumerator|sd_op
id|scd_op
comma
id|sdc1_op
comma
id|sdc2_op
comma
id|sd_op
)brace
suffix:semicolon
multiline_comment|/*&n; * func field of spec opcode.&n; */
DECL|enum|spec_op
r_enum
id|spec_op
(brace
DECL|enumerator|sll_op
DECL|enumerator|movc_op
DECL|enumerator|srl_op
DECL|enumerator|sra_op
id|sll_op
comma
id|movc_op
comma
id|srl_op
comma
id|sra_op
comma
DECL|enumerator|sllv_op
DECL|enumerator|srlv_op
DECL|enumerator|srav_op
DECL|enumerator|spec1_unused_op
id|sllv_op
comma
id|srlv_op
comma
id|srav_op
comma
id|spec1_unused_op
comma
multiline_comment|/* Opcode 0x07 is unused */
DECL|enumerator|jr_op
DECL|enumerator|jalr_op
DECL|enumerator|movz_op
DECL|enumerator|movn_op
id|jr_op
comma
id|jalr_op
comma
id|movz_op
comma
id|movn_op
comma
DECL|enumerator|syscall_op
DECL|enumerator|break_op
DECL|enumerator|spim_op
DECL|enumerator|sync_op
id|syscall_op
comma
id|break_op
comma
id|spim_op
comma
id|sync_op
comma
DECL|enumerator|mfhi_op
DECL|enumerator|mthi_op
DECL|enumerator|mflo_op
DECL|enumerator|mtlo_op
id|mfhi_op
comma
id|mthi_op
comma
id|mflo_op
comma
id|mtlo_op
comma
DECL|enumerator|dsllv_op
DECL|enumerator|spec2_unused_op
DECL|enumerator|dsrlv_op
DECL|enumerator|dsrav_op
id|dsllv_op
comma
id|spec2_unused_op
comma
id|dsrlv_op
comma
id|dsrav_op
comma
DECL|enumerator|mult_op
DECL|enumerator|multu_op
DECL|enumerator|div_op
DECL|enumerator|divu_op
id|mult_op
comma
id|multu_op
comma
id|div_op
comma
id|divu_op
comma
DECL|enumerator|dmult_op
DECL|enumerator|dmultu_op
DECL|enumerator|ddiv_op
DECL|enumerator|ddivu_op
id|dmult_op
comma
id|dmultu_op
comma
id|ddiv_op
comma
id|ddivu_op
comma
DECL|enumerator|add_op
DECL|enumerator|addu_op
DECL|enumerator|sub_op
DECL|enumerator|subu_op
id|add_op
comma
id|addu_op
comma
id|sub_op
comma
id|subu_op
comma
DECL|enumerator|and_op
DECL|enumerator|or_op
DECL|enumerator|xor_op
DECL|enumerator|nor_op
id|and_op
comma
id|or_op
comma
id|xor_op
comma
id|nor_op
comma
DECL|enumerator|spec3_unused_op
DECL|enumerator|spec4_unused_op
DECL|enumerator|slt_op
DECL|enumerator|sltu_op
id|spec3_unused_op
comma
id|spec4_unused_op
comma
id|slt_op
comma
id|sltu_op
comma
DECL|enumerator|dadd_op
DECL|enumerator|daddu_op
DECL|enumerator|dsub_op
DECL|enumerator|dsubu_op
id|dadd_op
comma
id|daddu_op
comma
id|dsub_op
comma
id|dsubu_op
comma
DECL|enumerator|tge_op
DECL|enumerator|tgeu_op
DECL|enumerator|tlt_op
DECL|enumerator|tltu_op
id|tge_op
comma
id|tgeu_op
comma
id|tlt_op
comma
id|tltu_op
comma
DECL|enumerator|teq_op
DECL|enumerator|spec5_unused_op
DECL|enumerator|tne_op
DECL|enumerator|spec6_unused_op
id|teq_op
comma
id|spec5_unused_op
comma
id|tne_op
comma
id|spec6_unused_op
comma
DECL|enumerator|dsll_op
DECL|enumerator|spec7_unused_op
DECL|enumerator|dsrl_op
DECL|enumerator|dsra_op
id|dsll_op
comma
id|spec7_unused_op
comma
id|dsrl_op
comma
id|dsra_op
comma
DECL|enumerator|dsll32_op
DECL|enumerator|spec8_unused_op
DECL|enumerator|dsrl32_op
DECL|enumerator|dsra32_op
id|dsll32_op
comma
id|spec8_unused_op
comma
id|dsrl32_op
comma
id|dsra32_op
)brace
suffix:semicolon
multiline_comment|/*&n; * rt field of bcond opcodes.&n; */
DECL|enum|rt_op
r_enum
id|rt_op
(brace
DECL|enumerator|bltz_op
DECL|enumerator|bgez_op
DECL|enumerator|bltzl_op
DECL|enumerator|bgezl_op
id|bltz_op
comma
id|bgez_op
comma
id|bltzl_op
comma
id|bgezl_op
comma
DECL|enumerator|spimi_op
DECL|enumerator|unused_rt_op_0x05
DECL|enumerator|unused_rt_op_0x06
DECL|enumerator|unused_rt_op_0x07
id|spimi_op
comma
id|unused_rt_op_0x05
comma
id|unused_rt_op_0x06
comma
id|unused_rt_op_0x07
comma
DECL|enumerator|tgei_op
DECL|enumerator|tgeiu_op
DECL|enumerator|tlti_op
DECL|enumerator|tltiu_op
id|tgei_op
comma
id|tgeiu_op
comma
id|tlti_op
comma
id|tltiu_op
comma
DECL|enumerator|teqi_op
DECL|enumerator|unused_0x0d_rt_op
DECL|enumerator|tnei_op
DECL|enumerator|unused_0x0f_rt_op
id|teqi_op
comma
id|unused_0x0d_rt_op
comma
id|tnei_op
comma
id|unused_0x0f_rt_op
comma
DECL|enumerator|bltzal_op
DECL|enumerator|bgezal_op
DECL|enumerator|bltzall_op
DECL|enumerator|bgezall_op
id|bltzal_op
comma
id|bgezal_op
comma
id|bltzall_op
comma
id|bgezall_op
multiline_comment|/*&n;&t; * The others (0x14 - 0x1f) are unused.&n; &t; */
)brace
suffix:semicolon
multiline_comment|/*&n; * rs field of cop opcodes.&n; */
DECL|enum|cop_op
r_enum
id|cop_op
(brace
DECL|enumerator|mfc_op
DECL|enumerator|dmfc_op
id|mfc_op
op_assign
l_int|0x00
comma
id|dmfc_op
op_assign
l_int|0x01
comma
DECL|enumerator|cfc_op
DECL|enumerator|mtc_op
id|cfc_op
op_assign
l_int|0x02
comma
id|mtc_op
op_assign
l_int|0x04
comma
DECL|enumerator|dmtc_op
DECL|enumerator|ctc_op
id|dmtc_op
op_assign
l_int|0x05
comma
id|ctc_op
op_assign
l_int|0x06
comma
DECL|enumerator|bc_op
DECL|enumerator|cop_op
id|bc_op
op_assign
l_int|0x08
comma
id|cop_op
op_assign
l_int|0x10
comma
DECL|enumerator|copm_op
id|copm_op
op_assign
l_int|0x18
)brace
suffix:semicolon
multiline_comment|/*&n; * func field of cop0 coi opcodes.&n; */
DECL|enum|cop0_coi_func
r_enum
id|cop0_coi_func
(brace
DECL|enumerator|tlbr_op
DECL|enumerator|tlbwi_op
id|tlbr_op
op_assign
l_int|0x01
comma
id|tlbwi_op
op_assign
l_int|0x02
comma
DECL|enumerator|tlbwr_op
DECL|enumerator|tlbp_op
id|tlbwr_op
op_assign
l_int|0x06
comma
id|tlbp_op
op_assign
l_int|0x08
comma
DECL|enumerator|rfe_op
DECL|enumerator|eret_op
id|rfe_op
op_assign
l_int|0x10
comma
id|eret_op
op_assign
l_int|0x18
)brace
suffix:semicolon
multiline_comment|/*&n; * func field of cop0 com opcodes.&n; */
DECL|enum|cop0_com_func
r_enum
id|cop0_com_func
(brace
DECL|enumerator|tlbr1_op
DECL|enumerator|tlbw_op
id|tlbr1_op
op_assign
l_int|0x01
comma
id|tlbw_op
op_assign
l_int|0x02
comma
DECL|enumerator|tlbp1_op
DECL|enumerator|dctr_op
id|tlbp1_op
op_assign
l_int|0x08
comma
id|dctr_op
op_assign
l_int|0x09
comma
DECL|enumerator|dctw_op
id|dctw_op
op_assign
l_int|0x0a
)brace
suffix:semicolon
multiline_comment|/*&n; * fmt field of cop1 opcodes.&n; */
DECL|enum|cop1_fmt
r_enum
id|cop1_fmt
(brace
DECL|enumerator|s_fmt
DECL|enumerator|d_fmt
DECL|enumerator|e_fmt
DECL|enumerator|q_fmt
id|s_fmt
comma
id|d_fmt
comma
id|e_fmt
comma
id|q_fmt
comma
DECL|enumerator|w_fmt
DECL|enumerator|l_fmt
id|w_fmt
comma
id|l_fmt
)brace
suffix:semicolon
multiline_comment|/*&n; * func field of cop1 instructions using d, s or w format.&n; */
DECL|enum|cop1_sdw_func
r_enum
id|cop1_sdw_func
(brace
DECL|enumerator|fadd_op
DECL|enumerator|fsub_op
id|fadd_op
op_assign
l_int|0x00
comma
id|fsub_op
op_assign
l_int|0x01
comma
DECL|enumerator|fmul_op
DECL|enumerator|fdiv_op
id|fmul_op
op_assign
l_int|0x02
comma
id|fdiv_op
op_assign
l_int|0x03
comma
DECL|enumerator|fsqrt_op
DECL|enumerator|fabs_op
id|fsqrt_op
op_assign
l_int|0x04
comma
id|fabs_op
op_assign
l_int|0x05
comma
DECL|enumerator|fmov_op
DECL|enumerator|fneg_op
id|fmov_op
op_assign
l_int|0x06
comma
id|fneg_op
op_assign
l_int|0x07
comma
DECL|enumerator|froundl_op
DECL|enumerator|ftruncl_op
id|froundl_op
op_assign
l_int|0x08
comma
id|ftruncl_op
op_assign
l_int|0x09
comma
DECL|enumerator|fceill_op
DECL|enumerator|ffloorl_op
id|fceill_op
op_assign
l_int|0x0a
comma
id|ffloorl_op
op_assign
l_int|0x0b
comma
DECL|enumerator|fround_op
DECL|enumerator|ftrunc_op
id|fround_op
op_assign
l_int|0x0c
comma
id|ftrunc_op
op_assign
l_int|0x0d
comma
DECL|enumerator|fceil_op
DECL|enumerator|ffloor_op
id|fceil_op
op_assign
l_int|0x0e
comma
id|ffloor_op
op_assign
l_int|0x0f
comma
DECL|enumerator|fmovc_op
DECL|enumerator|fmovz_op
id|fmovc_op
op_assign
l_int|0x11
comma
id|fmovz_op
op_assign
l_int|0x12
comma
DECL|enumerator|fmovn_op
DECL|enumerator|frecip_op
id|fmovn_op
op_assign
l_int|0x13
comma
id|frecip_op
op_assign
l_int|0x15
comma
DECL|enumerator|frsqrt_op
DECL|enumerator|fcvts_op
id|frsqrt_op
op_assign
l_int|0x16
comma
id|fcvts_op
op_assign
l_int|0x20
comma
DECL|enumerator|fcvtd_op
DECL|enumerator|fcvte_op
id|fcvtd_op
op_assign
l_int|0x21
comma
id|fcvte_op
op_assign
l_int|0x22
comma
DECL|enumerator|fcvtw_op
DECL|enumerator|fcvtl_op
id|fcvtw_op
op_assign
l_int|0x24
comma
id|fcvtl_op
op_assign
l_int|0x25
comma
DECL|enumerator|fcmp_op
id|fcmp_op
op_assign
l_int|0x30
)brace
suffix:semicolon
multiline_comment|/*&n; * func field of cop1x opcodes (MIPS IV).&n; */
DECL|enum|cop1x_func
r_enum
id|cop1x_func
(brace
DECL|enumerator|lwxc1_op
DECL|enumerator|ldxc1_op
id|lwxc1_op
op_assign
l_int|0x00
comma
id|ldxc1_op
op_assign
l_int|0x01
comma
DECL|enumerator|pfetch_op
DECL|enumerator|swxc1_op
id|pfetch_op
op_assign
l_int|0x07
comma
id|swxc1_op
op_assign
l_int|0x08
comma
DECL|enumerator|sdxc1_op
DECL|enumerator|madd_s_op
id|sdxc1_op
op_assign
l_int|0x09
comma
id|madd_s_op
op_assign
l_int|0x20
comma
DECL|enumerator|madd_d_op
DECL|enumerator|madd_e_op
id|madd_d_op
op_assign
l_int|0x21
comma
id|madd_e_op
op_assign
l_int|0x22
comma
DECL|enumerator|msub_s_op
DECL|enumerator|msub_d_op
id|msub_s_op
op_assign
l_int|0x28
comma
id|msub_d_op
op_assign
l_int|0x29
comma
DECL|enumerator|msub_e_op
DECL|enumerator|nmadd_s_op
id|msub_e_op
op_assign
l_int|0x2a
comma
id|nmadd_s_op
op_assign
l_int|0x30
comma
DECL|enumerator|nmadd_d_op
DECL|enumerator|nmadd_e_op
id|nmadd_d_op
op_assign
l_int|0x31
comma
id|nmadd_e_op
op_assign
l_int|0x32
comma
DECL|enumerator|nmsub_s_op
DECL|enumerator|nmsub_d_op
id|nmsub_s_op
op_assign
l_int|0x38
comma
id|nmsub_d_op
op_assign
l_int|0x39
comma
DECL|enumerator|nmsub_e_op
id|nmsub_e_op
op_assign
l_int|0x3a
)brace
suffix:semicolon
multiline_comment|/*&n; * func field for mad opcodes (MIPS IV).&n; */
DECL|enum|mad_func
r_enum
id|mad_func
(brace
DECL|enumerator|madd_op
DECL|enumerator|msub_op
id|madd_op
op_assign
l_int|0x08
comma
id|msub_op
op_assign
l_int|0x0a
comma
DECL|enumerator|nmadd_op
DECL|enumerator|nmsub_op
id|nmadd_op
op_assign
l_int|0x0c
comma
id|nmsub_op
op_assign
l_int|0x0e
)brace
suffix:semicolon
multiline_comment|/*&n; * Damn ...  bitfields depend from byteorder :-(&n; */
macro_line|#ifdef __MIPSEB__
DECL|struct|j_format
r_struct
id|j_format
(brace
multiline_comment|/* Jump format */
DECL|member|opcode
r_int
r_int
id|opcode
suffix:colon
l_int|6
suffix:semicolon
DECL|member|target
r_int
r_int
id|target
suffix:colon
l_int|26
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|i_format
r_struct
id|i_format
(brace
multiline_comment|/* Immediate format (addi, lw, ...) */
DECL|member|opcode
r_int
r_int
id|opcode
suffix:colon
l_int|6
suffix:semicolon
DECL|member|rs
r_int
r_int
id|rs
suffix:colon
l_int|5
suffix:semicolon
DECL|member|rt
r_int
r_int
id|rt
suffix:colon
l_int|5
suffix:semicolon
DECL|member|simmediate
r_int
r_int
id|simmediate
suffix:colon
l_int|16
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|u_format
r_struct
id|u_format
(brace
multiline_comment|/* Unsigned immediate format (ori, xori, ...) */
DECL|member|opcode
r_int
r_int
id|opcode
suffix:colon
l_int|6
suffix:semicolon
DECL|member|rs
r_int
r_int
id|rs
suffix:colon
l_int|5
suffix:semicolon
DECL|member|rt
r_int
r_int
id|rt
suffix:colon
l_int|5
suffix:semicolon
DECL|member|uimmediate
r_int
r_int
id|uimmediate
suffix:colon
l_int|16
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|c_format
r_struct
id|c_format
(brace
multiline_comment|/* Cache (&gt;= R6000) format */
DECL|member|opcode
r_int
r_int
id|opcode
suffix:colon
l_int|6
suffix:semicolon
DECL|member|rs
r_int
r_int
id|rs
suffix:colon
l_int|5
suffix:semicolon
DECL|member|c_op
r_int
r_int
id|c_op
suffix:colon
l_int|3
suffix:semicolon
DECL|member|cache
r_int
r_int
id|cache
suffix:colon
l_int|2
suffix:semicolon
DECL|member|simmediate
r_int
r_int
id|simmediate
suffix:colon
l_int|16
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|r_format
r_struct
id|r_format
(brace
multiline_comment|/* Register format */
DECL|member|opcode
r_int
r_int
id|opcode
suffix:colon
l_int|6
suffix:semicolon
DECL|member|rs
r_int
r_int
id|rs
suffix:colon
l_int|5
suffix:semicolon
DECL|member|rt
r_int
r_int
id|rt
suffix:colon
l_int|5
suffix:semicolon
DECL|member|rd
r_int
r_int
id|rd
suffix:colon
l_int|5
suffix:semicolon
DECL|member|re
r_int
r_int
id|re
suffix:colon
l_int|5
suffix:semicolon
DECL|member|func
r_int
r_int
id|func
suffix:colon
l_int|6
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|p_format
r_struct
id|p_format
(brace
multiline_comment|/* Performance counter format (R10000) */
DECL|member|opcode
r_int
r_int
id|opcode
suffix:colon
l_int|6
suffix:semicolon
DECL|member|rs
r_int
r_int
id|rs
suffix:colon
l_int|5
suffix:semicolon
DECL|member|rt
r_int
r_int
id|rt
suffix:colon
l_int|5
suffix:semicolon
DECL|member|rd
r_int
r_int
id|rd
suffix:colon
l_int|5
suffix:semicolon
DECL|member|re
r_int
r_int
id|re
suffix:colon
l_int|5
suffix:semicolon
DECL|member|func
r_int
r_int
id|func
suffix:colon
l_int|6
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|f_format
r_struct
id|f_format
(brace
multiline_comment|/* FPU register format */
DECL|member|opcode
r_int
r_int
id|opcode
suffix:colon
l_int|6
suffix:semicolon
r_int
r_int
suffix:colon
l_int|1
suffix:semicolon
DECL|member|fmt
r_int
r_int
id|fmt
suffix:colon
l_int|4
suffix:semicolon
DECL|member|rt
r_int
r_int
id|rt
suffix:colon
l_int|5
suffix:semicolon
DECL|member|rd
r_int
r_int
id|rd
suffix:colon
l_int|5
suffix:semicolon
DECL|member|re
r_int
r_int
id|re
suffix:colon
l_int|5
suffix:semicolon
DECL|member|func
r_int
r_int
id|func
suffix:colon
l_int|6
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ma_format
r_struct
id|ma_format
(brace
multiline_comment|/* FPU multipy and add format (MIPS IV) */
DECL|member|opcode
r_int
r_int
id|opcode
suffix:colon
l_int|6
suffix:semicolon
DECL|member|fr
r_int
r_int
id|fr
suffix:colon
l_int|5
suffix:semicolon
DECL|member|ft
r_int
r_int
id|ft
suffix:colon
l_int|5
suffix:semicolon
DECL|member|fs
r_int
r_int
id|fs
suffix:colon
l_int|5
suffix:semicolon
DECL|member|fd
r_int
r_int
id|fd
suffix:colon
l_int|5
suffix:semicolon
DECL|member|func
r_int
r_int
id|func
suffix:colon
l_int|4
suffix:semicolon
DECL|member|fmt
r_int
r_int
id|fmt
suffix:colon
l_int|2
suffix:semicolon
)brace
suffix:semicolon
macro_line|#elif defined(__MIPSEL__)
DECL|struct|j_format
r_struct
id|j_format
(brace
multiline_comment|/* Jump format */
DECL|member|target
r_int
r_int
id|target
suffix:colon
l_int|26
suffix:semicolon
DECL|member|opcode
r_int
r_int
id|opcode
suffix:colon
l_int|6
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|i_format
r_struct
id|i_format
(brace
multiline_comment|/* Immediate format */
DECL|member|simmediate
r_int
r_int
id|simmediate
suffix:colon
l_int|16
suffix:semicolon
DECL|member|rt
r_int
r_int
id|rt
suffix:colon
l_int|5
suffix:semicolon
DECL|member|rs
r_int
r_int
id|rs
suffix:colon
l_int|5
suffix:semicolon
DECL|member|opcode
r_int
r_int
id|opcode
suffix:colon
l_int|6
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|u_format
r_struct
id|u_format
(brace
multiline_comment|/* Unsigned immediate format */
DECL|member|uimmediate
r_int
r_int
id|uimmediate
suffix:colon
l_int|16
suffix:semicolon
DECL|member|rt
r_int
r_int
id|rt
suffix:colon
l_int|5
suffix:semicolon
DECL|member|rs
r_int
r_int
id|rs
suffix:colon
l_int|5
suffix:semicolon
DECL|member|opcode
r_int
r_int
id|opcode
suffix:colon
l_int|6
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|c_format
r_struct
id|c_format
(brace
multiline_comment|/* Cache (&gt;= R6000) format */
DECL|member|simmediate
r_int
r_int
id|simmediate
suffix:colon
l_int|16
suffix:semicolon
DECL|member|cache
r_int
r_int
id|cache
suffix:colon
l_int|2
suffix:semicolon
DECL|member|c_op
r_int
r_int
id|c_op
suffix:colon
l_int|3
suffix:semicolon
DECL|member|rs
r_int
r_int
id|rs
suffix:colon
l_int|5
suffix:semicolon
DECL|member|opcode
r_int
r_int
id|opcode
suffix:colon
l_int|6
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|r_format
r_struct
id|r_format
(brace
multiline_comment|/* Register format */
DECL|member|func
r_int
r_int
id|func
suffix:colon
l_int|6
suffix:semicolon
DECL|member|re
r_int
r_int
id|re
suffix:colon
l_int|5
suffix:semicolon
DECL|member|rd
r_int
r_int
id|rd
suffix:colon
l_int|5
suffix:semicolon
DECL|member|rt
r_int
r_int
id|rt
suffix:colon
l_int|5
suffix:semicolon
DECL|member|rs
r_int
r_int
id|rs
suffix:colon
l_int|5
suffix:semicolon
DECL|member|opcode
r_int
r_int
id|opcode
suffix:colon
l_int|6
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|p_format
r_struct
id|p_format
(brace
multiline_comment|/* Performance counter format (R10000) */
DECL|member|func
r_int
r_int
id|func
suffix:colon
l_int|6
suffix:semicolon
DECL|member|re
r_int
r_int
id|re
suffix:colon
l_int|5
suffix:semicolon
DECL|member|rd
r_int
r_int
id|rd
suffix:colon
l_int|5
suffix:semicolon
DECL|member|rt
r_int
r_int
id|rt
suffix:colon
l_int|5
suffix:semicolon
DECL|member|rs
r_int
r_int
id|rs
suffix:colon
l_int|5
suffix:semicolon
DECL|member|opcode
r_int
r_int
id|opcode
suffix:colon
l_int|6
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|f_format
r_struct
id|f_format
(brace
multiline_comment|/* FPU register format */
DECL|member|func
r_int
r_int
id|func
suffix:colon
l_int|6
suffix:semicolon
DECL|member|re
r_int
r_int
id|re
suffix:colon
l_int|5
suffix:semicolon
DECL|member|rd
r_int
r_int
id|rd
suffix:colon
l_int|5
suffix:semicolon
DECL|member|rt
r_int
r_int
id|rt
suffix:colon
l_int|5
suffix:semicolon
DECL|member|fmt
r_int
r_int
id|fmt
suffix:colon
l_int|4
suffix:semicolon
r_int
r_int
suffix:colon
l_int|1
suffix:semicolon
DECL|member|opcode
r_int
r_int
id|opcode
suffix:colon
l_int|6
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ma_format
r_struct
id|ma_format
(brace
multiline_comment|/* FPU multipy and add format (MIPS IV) */
DECL|member|fmt
r_int
r_int
id|fmt
suffix:colon
l_int|2
suffix:semicolon
DECL|member|func
r_int
r_int
id|func
suffix:colon
l_int|4
suffix:semicolon
DECL|member|fd
r_int
r_int
id|fd
suffix:colon
l_int|5
suffix:semicolon
DECL|member|fs
r_int
r_int
id|fs
suffix:colon
l_int|5
suffix:semicolon
DECL|member|ft
r_int
r_int
id|ft
suffix:colon
l_int|5
suffix:semicolon
DECL|member|fr
r_int
r_int
id|fr
suffix:colon
l_int|5
suffix:semicolon
DECL|member|opcode
r_int
r_int
id|opcode
suffix:colon
l_int|6
suffix:semicolon
)brace
suffix:semicolon
macro_line|#else /* !defined (__MIPSEB__) &amp;&amp; !defined (__MIPSEL__) */
macro_line|#error &quot;MIPS but neither __MIPSEL__ nor __MIPSEB__?&quot;
macro_line|#endif
DECL|union|mips_instruction
r_union
id|mips_instruction
(brace
DECL|member|word
r_int
r_int
id|word
suffix:semicolon
DECL|member|halfword
r_int
r_int
id|halfword
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|byte
r_int
r_char
id|byte
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|j_format
r_struct
id|j_format
id|j_format
suffix:semicolon
DECL|member|i_format
r_struct
id|i_format
id|i_format
suffix:semicolon
DECL|member|u_format
r_struct
id|u_format
id|u_format
suffix:semicolon
DECL|member|c_format
r_struct
id|c_format
id|c_format
suffix:semicolon
DECL|member|r_format
r_struct
id|r_format
id|r_format
suffix:semicolon
DECL|member|f_format
r_struct
id|f_format
id|f_format
suffix:semicolon
DECL|member|ma_format
r_struct
id|ma_format
id|ma_format
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __ASM_MIPS_INST_H */
eof