multiline_comment|/*&n;   * Copyright 1996 The Australian National University.&n;   * Copyright 1996 Fujitsu Laboratories Limited&n;   * &n;   * This software may be distributed under the terms of the Gnu&n;   * Public License version 2 or later&n;  */
multiline_comment|/*&n; * Definitions for Am79c864 PLC (Physical Layer Controller)&n; */
DECL|typedef|plc_reg
r_typedef
r_int
id|plc_reg
suffix:semicolon
DECL|struct|plc
r_struct
id|plc
(brace
DECL|member|ctrl_a
id|plc_reg
id|ctrl_a
suffix:semicolon
DECL|member|ctrl_b
id|plc_reg
id|ctrl_b
suffix:semicolon
DECL|member|intr_mask
id|plc_reg
id|intr_mask
suffix:semicolon
DECL|member|xmit_vector
id|plc_reg
id|xmit_vector
suffix:semicolon
DECL|member|vec_length
id|plc_reg
id|vec_length
suffix:semicolon
DECL|member|le_threshold
id|plc_reg
id|le_threshold
suffix:semicolon
DECL|member|c_min
id|plc_reg
id|c_min
suffix:semicolon
DECL|member|tl_min
id|plc_reg
id|tl_min
suffix:semicolon
DECL|member|tb_min
id|plc_reg
id|tb_min
suffix:semicolon
DECL|member|t_out
id|plc_reg
id|t_out
suffix:semicolon
DECL|member|dummy1
id|plc_reg
id|dummy1
suffix:semicolon
DECL|member|lc_length
id|plc_reg
id|lc_length
suffix:semicolon
DECL|member|t_scrub
id|plc_reg
id|t_scrub
suffix:semicolon
DECL|member|ns_max
id|plc_reg
id|ns_max
suffix:semicolon
DECL|member|tpc_load
id|plc_reg
id|tpc_load
suffix:semicolon
DECL|member|tne_load
id|plc_reg
id|tne_load
suffix:semicolon
DECL|member|status_a
id|plc_reg
id|status_a
suffix:semicolon
DECL|member|status_b
id|plc_reg
id|status_b
suffix:semicolon
DECL|member|tpc
id|plc_reg
id|tpc
suffix:semicolon
DECL|member|tne
id|plc_reg
id|tne
suffix:semicolon
DECL|member|clk_div
id|plc_reg
id|clk_div
suffix:semicolon
DECL|member|bist_sig
id|plc_reg
id|bist_sig
suffix:semicolon
DECL|member|rcv_vector
id|plc_reg
id|rcv_vector
suffix:semicolon
DECL|member|intr_event
id|plc_reg
id|intr_event
suffix:semicolon
DECL|member|viol_sym_ct
id|plc_reg
id|viol_sym_ct
suffix:semicolon
DECL|member|min_idle_ct
id|plc_reg
id|min_idle_ct
suffix:semicolon
DECL|member|link_err_ct
id|plc_reg
id|link_err_ct
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Bits in ctrl_a */
DECL|macro|CA_NOISE_TIMER
mdefine_line|#define CA_NOISE_TIMER&t;&t;0x4000
DECL|macro|CA_TNE_16BIT
mdefine_line|#define CA_TNE_16BIT&t;&t;0x2000
DECL|macro|CA_TPC_16BIT
mdefine_line|#define CA_TPC_16BIT&t;&t;0x1000
DECL|macro|CA_REQ_SCRUB
mdefine_line|#define CA_REQ_SCRUB&t;&t;0x0800
DECL|macro|CA_VSYM_INTR_MODE
mdefine_line|#define CA_VSYM_INTR_MODE&t;0x0200
DECL|macro|CA_MINI_INTR_MODE
mdefine_line|#define CA_MINI_INTR_MODE&t;0x0100
DECL|macro|CA_LOOPBACK
mdefine_line|#define CA_LOOPBACK&t;&t;0x0080
DECL|macro|CA_FOT_OFF
mdefine_line|#define CA_FOT_OFF&t;&t;0x0040
DECL|macro|CA_EB_LOOP
mdefine_line|#define CA_EB_LOOP&t;&t;0x0020
DECL|macro|CA_LM_LOOP
mdefine_line|#define CA_LM_LOOP&t;&t;0x0010
DECL|macro|CA_BYPASS
mdefine_line|#define CA_BYPASS&t;&t;0x0008
DECL|macro|CA_REM_LOOP
mdefine_line|#define CA_REM_LOOP&t;&t;0x0004
DECL|macro|CA_RF_DISABLE
mdefine_line|#define CA_RF_DISABLE&t;&t;0x0002
DECL|macro|CA_RUN_BIST
mdefine_line|#define CA_RUN_BIST&t;&t;0x0001
multiline_comment|/* Bits in ctrl_b */
DECL|macro|CB_CONFIG_CTRL
mdefine_line|#define CB_CONFIG_CTRL&t;&t;0x8000
DECL|macro|CB_MATCH_LS
mdefine_line|#define CB_MATCH_LS&t;&t;0x7800
DECL|macro|CB_MATCH_LS_ANY
mdefine_line|#define CB_MATCH_LS_ANY&t;&t;0x0000
DECL|macro|CB_MATCH_LS_QLS
mdefine_line|#define CB_MATCH_LS_QLS&t;&t;0x4000
DECL|macro|CB_MATCH_LS_MLS
mdefine_line|#define CB_MATCH_LS_MLS&t;&t;0x2000
DECL|macro|CB_MATCH_LS_HLS
mdefine_line|#define CB_MATCH_LS_HLS&t;&t;0x1000
DECL|macro|CB_MATCH_LS_ILS
mdefine_line|#define CB_MATCH_LS_ILS&t;&t;0x0800
DECL|macro|CB_MAINT_LS
mdefine_line|#define CB_MAINT_LS&t;&t;0x0700
DECL|macro|CB_MAINT_LS_QLS
mdefine_line|#define CB_MAINT_LS_QLS&t;&t;0x0000
DECL|macro|CB_MAINT_LS_ILS
mdefine_line|#define CB_MAINT_LS_ILS&t;&t;0x0100
DECL|macro|CB_MAINT_LS_HLS
mdefine_line|#define CB_MAINT_LS_HLS&t;&t;0x0200
DECL|macro|CB_MAINT_LS_MLS
mdefine_line|#define CB_MAINT_LS_MLS&t;&t;0x0300
DECL|macro|CB_MAINT_LS_PDR
mdefine_line|#define CB_MAINT_LS_PDR&t;&t;0x0600
DECL|macro|CB_CLASS_S
mdefine_line|#define CB_CLASS_S&t;&t;0x0080
DECL|macro|CB_PC_LCT
mdefine_line|#define CB_PC_LCT&t;&t;0x0060
DECL|macro|CB_PC_LCT_NONE
mdefine_line|#define CB_PC_LCT_NONE&t;&t;0x0000
DECL|macro|CB_PC_LCT_PDR
mdefine_line|#define CB_PC_LCT_PDR&t;&t;0x0020
DECL|macro|CB_PC_LCT_IDLE
mdefine_line|#define CB_PC_LCT_IDLE&t;&t;0x0040
DECL|macro|CB_PC_LCT_LOOP
mdefine_line|#define CB_PC_LCT_LOOP&t;&t;0x0060
DECL|macro|CB_PC_JOIN
mdefine_line|#define CB_PC_JOIN&t;&t;0x0010
DECL|macro|CB_LONG_LCT
mdefine_line|#define CB_LONG_LCT&t;&t;0x0008
DECL|macro|CB_PC_MAINT
mdefine_line|#define CB_PC_MAINT&t;&t;0x0004
DECL|macro|CB_PCM_CTRL
mdefine_line|#define CB_PCM_CTRL&t;&t;0x0003
DECL|macro|CB_PC_START
mdefine_line|#define CB_PC_START&t;&t;0x0001
DECL|macro|CB_PC_TRACE
mdefine_line|#define CB_PC_TRACE&t;&t;0x0002
DECL|macro|CB_PC_STOP
mdefine_line|#define CB_PC_STOP&t;&t;0x0003
multiline_comment|/* Bits in status_a */
DECL|macro|SA_SIG_DETECT
mdefine_line|#define SA_SIG_DETECT&t;&t;0x0400
DECL|macro|SA_PREV_LS
mdefine_line|#define SA_PREV_LS&t;&t;0x0300
DECL|macro|SA_PREV_LS_QLS
mdefine_line|#define SA_PREV_LS_QLS&t;&t;0x0000
DECL|macro|SA_PREV_LS_MLS
mdefine_line|#define SA_PREV_LS_MLS&t;&t;0x0100
DECL|macro|SA_PREV_LS_HLS
mdefine_line|#define SA_PREV_LS_HLS&t;&t;0x0200
DECL|macro|SA_PREV_LS_ILS
mdefine_line|#define SA_PREV_LS_ILS&t;&t;0x0300
DECL|macro|SA_LINE_ST
mdefine_line|#define SA_LINE_ST&t;&t;0x00e0
DECL|macro|SA_LINE_ST_NLS
mdefine_line|#define SA_LINE_ST_NLS&t;&t;0x0000
DECL|macro|SA_LINE_ST_ALS
mdefine_line|#define SA_LINE_ST_ALS&t;&t;0x0020
DECL|macro|SA_LINE_ST_ILS4
mdefine_line|#define SA_LINE_ST_ILS4&t;&t;0x0060
DECL|macro|SA_LINE_ST_QLS
mdefine_line|#define SA_LINE_ST_QLS&t;&t;0x0080
DECL|macro|SA_LINE_ST_MLS
mdefine_line|#define SA_LINE_ST_MLS&t;&t;0x00a0
DECL|macro|SA_LINE_ST_HLS
mdefine_line|#define SA_LINE_ST_HLS&t;&t;0x00c0
DECL|macro|SA_LINE_ST_ILS
mdefine_line|#define SA_LINE_ST_ILS&t;&t;0x00e0
DECL|macro|SA_LSM_STATE
mdefine_line|#define SA_LSM_STATE&t;&t;0x0010
DECL|macro|SA_UNKN_LINE_ST
mdefine_line|#define SA_UNKN_LINE_ST&t;&t;0x0008
DECL|macro|SA_SYM_PAIR_CTR
mdefine_line|#define SA_SYM_PAIR_CTR&t;&t;0x0007
multiline_comment|/* Bits in status_b */
DECL|macro|SB_RF_STATE
mdefine_line|#define SB_RF_STATE&t;&t;0xc000
DECL|macro|SB_RF_STATE_REPEAT
mdefine_line|#define SB_RF_STATE_REPEAT&t;0x0000
DECL|macro|SB_RF_STATE_IDLE
mdefine_line|#define SB_RF_STATE_IDLE&t;0x4000
DECL|macro|SB_RF_STATE_HALT1
mdefine_line|#define SB_RF_STATE_HALT1&t;0x8000
DECL|macro|SB_RF_STATE_HALT2
mdefine_line|#define SB_RF_STATE_HALT2&t;0xc000
DECL|macro|SB_PCI_STATE
mdefine_line|#define SB_PCI_STATE&t;&t;0x3000
DECL|macro|SB_PCI_STATE_REMOVED
mdefine_line|#define SB_PCI_STATE_REMOVED&t;0x0000
DECL|macro|SB_PCI_STATE_INS_SCR
mdefine_line|#define SB_PCI_STATE_INS_SCR&t;0x1000
DECL|macro|SB_PCI_STATE_REM_SCR
mdefine_line|#define SB_PCI_STATE_REM_SCR&t;0x2000
DECL|macro|SB_PCI_STATE_INSERTED
mdefine_line|#define SB_PCI_STATE_INSERTED&t;0x3000
DECL|macro|SB_PCI_SCRUB
mdefine_line|#define SB_PCI_SCRUB&t;&t;0x0800
DECL|macro|SB_PCM_STATE
mdefine_line|#define SB_PCM_STATE&t;&t;0x0780
DECL|macro|SB_PCM_STATE_OFF
mdefine_line|#define SB_PCM_STATE_OFF&t;0x0000
DECL|macro|SB_PCM_STATE_BREAK
mdefine_line|#define SB_PCM_STATE_BREAK&t;0x0080
DECL|macro|SB_PCM_STATE_TRACE
mdefine_line|#define SB_PCM_STATE_TRACE&t;0x0100
DECL|macro|SB_PCM_STATE_CONNECT
mdefine_line|#define SB_PCM_STATE_CONNECT&t;0x0180
DECL|macro|SB_PCM_STATE_NEXT
mdefine_line|#define SB_PCM_STATE_NEXT&t;0x0200
DECL|macro|SB_PCM_STATE_SIGNAL
mdefine_line|#define SB_PCM_STATE_SIGNAL&t;0x0280
DECL|macro|SB_PCM_STATE_JOIN
mdefine_line|#define SB_PCM_STATE_JOIN&t;0x0300
DECL|macro|SB_PCM_STATE_VERIFY
mdefine_line|#define SB_PCM_STATE_VERIFY&t;0x0380
DECL|macro|SB_PCM_STATE_ACTIVE
mdefine_line|#define SB_PCM_STATE_ACTIVE&t;0x0400
DECL|macro|SB_PCM_STATE_MAIN
mdefine_line|#define SB_PCM_STATE_MAIN&t;0x0480
DECL|macro|SB_PCM_SIGNALING
mdefine_line|#define SB_PCM_SIGNALING&t;0x0040
DECL|macro|SB_LSF
mdefine_line|#define SB_LSF&t;&t;&t;0x0020
DECL|macro|SB_RCF
mdefine_line|#define SB_RCF&t;&t;&t;0x0010
DECL|macro|SB_TCF
mdefine_line|#define SB_TCF&t;&t;&t;0x0008
DECL|macro|SB_BREAK_REASON
mdefine_line|#define SB_BREAK_REASON&t;&t;0x0007
DECL|macro|SB_BREAK_REASON_NONE
mdefine_line|#define SB_BREAK_REASON_NONE&t;0x0000
DECL|macro|SB_BREAK_REASON_START
mdefine_line|#define SB_BREAK_REASON_START&t;0x0001
DECL|macro|SB_BREAK_REASON_T_OUT
mdefine_line|#define SB_BREAK_REASON_T_OUT&t;0x0002
DECL|macro|SB_BREAK_REASON_NS_MAX
mdefine_line|#define SB_BREAK_REASON_NS_MAX&t;0x0003
DECL|macro|SB_BREAK_REASON_QLS
mdefine_line|#define SB_BREAK_REASON_QLS&t;0x0004
DECL|macro|SB_BREAK_REASON_ILS
mdefine_line|#define SB_BREAK_REASON_ILS&t;0x0005
DECL|macro|SB_BREAK_REASON_HLS
mdefine_line|#define SB_BREAK_REASON_HLS&t;0x0006
multiline_comment|/* Bits in intr_event and intr_mask */
DECL|macro|IE_NP_ERROR
mdefine_line|#define IE_NP_ERROR&t;&t;0x8000
DECL|macro|IE_SIGNAL_OFF
mdefine_line|#define IE_SIGNAL_OFF&t;&t;0x4000
DECL|macro|IE_LE_CTR
mdefine_line|#define IE_LE_CTR&t;&t;0x2000
DECL|macro|IE_MINI_CTR
mdefine_line|#define IE_MINI_CTR&t;&t;0x1000
DECL|macro|IE_VSYM_CTR
mdefine_line|#define IE_VSYM_CTR&t;&t;0x0800
DECL|macro|IE_PHY_INVALID
mdefine_line|#define IE_PHY_INVALID&t;&t;0x0400
DECL|macro|IE_EBUF_ERR
mdefine_line|#define IE_EBUF_ERR&t;&t;0x0200
DECL|macro|IE_TNE_EXP
mdefine_line|#define IE_TNE_EXP&t;&t;0x0100
DECL|macro|IE_TPC_EXP
mdefine_line|#define IE_TPC_EXP&t;&t;0x0080
DECL|macro|IE_PCM_ENABLED
mdefine_line|#define IE_PCM_ENABLED&t;&t;0x0040
DECL|macro|IE_PCM_BREAK
mdefine_line|#define IE_PCM_BREAK&t;&t;0x0020
DECL|macro|IE_SELF_TEST
mdefine_line|#define IE_SELF_TEST&t;&t;0x0010
DECL|macro|IE_TRACE_PROP
mdefine_line|#define IE_TRACE_PROP&t;&t;0x0008
DECL|macro|IE_PCM_CODE
mdefine_line|#define IE_PCM_CODE&t;&t;0x0004
DECL|macro|IE_LS_MATCH
mdefine_line|#define IE_LS_MATCH&t;&t;0x0002
DECL|macro|IE_PARITY_ERR
mdefine_line|#define IE_PARITY_ERR&t;&t;0x0001
multiline_comment|/* Correct value for BIST signature */
DECL|macro|BIST_CORRECT
mdefine_line|#define BIST_CORRECT&t;&t;0x6ecd
eof
