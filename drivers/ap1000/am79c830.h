multiline_comment|/*&n;   * Copyright 1996 The Australian National University.&n;   * Copyright 1996 Fujitsu Laboratories Limited&n;   * &n;   * This software may be distributed under the terms of the Gnu&n;   * Public License version 2 or later&n;  */
multiline_comment|/*&n; * Definitions for the AM79C830 FORMAC (Fiber Optic Ring MAC) chip.&n; */
DECL|typedef|formac_reg
r_typedef
r_int
id|formac_reg
suffix:semicolon
DECL|struct|formac
r_struct
id|formac
(brace
DECL|member|cmdreg1
id|formac_reg
id|cmdreg1
suffix:semicolon
multiline_comment|/* command register 1 */
DECL|member|cmdreg2
id|formac_reg
id|cmdreg2
suffix:semicolon
multiline_comment|/* command register 2 */
DECL|macro|st1u
mdefine_line|#define st1u&t;cmdreg1&t;&t;/* status reg 1, upper */
DECL|macro|st1l
mdefine_line|#define st1l&t;cmdreg2&t;&t;/* status reg 1, lower */
DECL|member|st2u
id|formac_reg
id|st2u
suffix:semicolon
multiline_comment|/* status reg 2, upper */
DECL|member|st2l
id|formac_reg
id|st2l
suffix:semicolon
multiline_comment|/* status reg 2, lower */
DECL|member|imsk1u
id|formac_reg
id|imsk1u
suffix:semicolon
multiline_comment|/* interrupt mask 1, upper */
DECL|member|imsk1l
id|formac_reg
id|imsk1l
suffix:semicolon
multiline_comment|/* interrupt mask 1, lower */
DECL|member|imsk2u
id|formac_reg
id|imsk2u
suffix:semicolon
multiline_comment|/* interrupt mask 2, upper */
DECL|member|imsk2l
id|formac_reg
id|imsk2l
suffix:semicolon
multiline_comment|/* interrupt mask 2, lower */
DECL|member|said
id|formac_reg
id|said
suffix:semicolon
multiline_comment|/* short address, individual */
DECL|member|laim
id|formac_reg
id|laim
suffix:semicolon
multiline_comment|/* long adrs, indiv, MS word */
DECL|member|laic
id|formac_reg
id|laic
suffix:semicolon
multiline_comment|/* long adrs, indiv, middle word */
DECL|member|lail
id|formac_reg
id|lail
suffix:semicolon
multiline_comment|/* long adrs, indiv, LS word */
DECL|member|sagp
id|formac_reg
id|sagp
suffix:semicolon
multiline_comment|/* short address, group */
DECL|member|lagm
id|formac_reg
id|lagm
suffix:semicolon
multiline_comment|/* short adrs, group, MS word */
DECL|member|lagc
id|formac_reg
id|lagc
suffix:semicolon
multiline_comment|/* short adrs, group, middle word */
DECL|member|lagl
id|formac_reg
id|lagl
suffix:semicolon
multiline_comment|/* short adrs, group, LS word */
DECL|member|mdreg1
id|formac_reg
id|mdreg1
suffix:semicolon
multiline_comment|/* mode reg 1 */
DECL|member|stmchn
id|formac_reg
id|stmchn
suffix:semicolon
multiline_comment|/* state machine reg */
DECL|member|mir1
id|formac_reg
id|mir1
suffix:semicolon
multiline_comment|/* MAC information reg, upper */
DECL|member|mir0
id|formac_reg
id|mir0
suffix:semicolon
multiline_comment|/* MAC information reg, lower */
DECL|member|tmax
id|formac_reg
id|tmax
suffix:semicolon
multiline_comment|/* TMax value (2&squot;s-comp) */
DECL|member|tvx
id|formac_reg
id|tvx
suffix:semicolon
multiline_comment|/* TVX value (2&squot;s-comp) */
DECL|member|trt
id|formac_reg
id|trt
suffix:semicolon
multiline_comment|/* TRT timer value */
DECL|member|tht
id|formac_reg
id|tht
suffix:semicolon
multiline_comment|/* THT timer value */
DECL|member|tneg
id|formac_reg
id|tneg
suffix:semicolon
multiline_comment|/* current TNeg (2&squot;s-comp) */
DECL|member|tmrs
id|formac_reg
id|tmrs
suffix:semicolon
multiline_comment|/* extra bits of tneg, trt, tht; late count */
DECL|member|treq0
id|formac_reg
id|treq0
suffix:semicolon
multiline_comment|/* our TReq (2&squot;s-comp), lower */
DECL|member|treq1
id|formac_reg
id|treq1
suffix:semicolon
multiline_comment|/* our TReq (2&squot;s-comp), upper */
DECL|member|pri0
id|formac_reg
id|pri0
suffix:semicolon
multiline_comment|/* priority reg for async queue 0 */
DECL|member|pri1
id|formac_reg
id|pri1
suffix:semicolon
multiline_comment|/* priority reg for async queue 1 */
DECL|member|pri2
id|formac_reg
id|pri2
suffix:semicolon
multiline_comment|/* priority reg for async queue 2 */
DECL|member|tsync
id|formac_reg
id|tsync
suffix:semicolon
multiline_comment|/* TSync value (2&squot;s-comp) */
DECL|member|mdreg2
id|formac_reg
id|mdreg2
suffix:semicolon
multiline_comment|/* mode reg 2 */
DECL|member|frmthr
id|formac_reg
id|frmthr
suffix:semicolon
multiline_comment|/* frame threshold reg */
DECL|member|eacb
id|formac_reg
id|eacb
suffix:semicolon
multiline_comment|/* end address of claim/beacon area */
DECL|member|earv
id|formac_reg
id|earv
suffix:semicolon
multiline_comment|/* end address of receive area */
DECL|member|eas
id|formac_reg
id|eas
suffix:semicolon
multiline_comment|/* end address of sync queue */
DECL|member|eaa0
id|formac_reg
id|eaa0
suffix:semicolon
multiline_comment|/* end address of async queue 0 */
DECL|member|eaa1
id|formac_reg
id|eaa1
suffix:semicolon
multiline_comment|/* end address of async queue 1 */
DECL|member|eaa2
id|formac_reg
id|eaa2
suffix:semicolon
multiline_comment|/* end address of async queue 2 */
DECL|member|sacl
id|formac_reg
id|sacl
suffix:semicolon
multiline_comment|/* start address of claim frame */
DECL|member|sabc
id|formac_reg
id|sabc
suffix:semicolon
multiline_comment|/* start address of beacon frame */
DECL|member|wpxsf
id|formac_reg
id|wpxsf
suffix:semicolon
multiline_comment|/* write pointer, special frames */
DECL|member|rpxsf
id|formac_reg
id|rpxsf
suffix:semicolon
multiline_comment|/* read pointer, special frames */
DECL|member|dummy1
id|formac_reg
id|dummy1
suffix:semicolon
multiline_comment|/* not used */
DECL|member|rpr
id|formac_reg
id|rpr
suffix:semicolon
multiline_comment|/* read pointer, receive */
DECL|member|wpr
id|formac_reg
id|wpr
suffix:semicolon
multiline_comment|/* write pointer, receive */
DECL|member|swpr
id|formac_reg
id|swpr
suffix:semicolon
multiline_comment|/* shadow write pointer, receive */
DECL|member|wpxs
id|formac_reg
id|wpxs
suffix:semicolon
multiline_comment|/* write pointer, sync queue */
DECL|member|wpxa0
id|formac_reg
id|wpxa0
suffix:semicolon
multiline_comment|/* write pointer, async queue 0 */
DECL|member|wpxa1
id|formac_reg
id|wpxa1
suffix:semicolon
multiline_comment|/* write pointer, async queue 1 */
DECL|member|wpxa2
id|formac_reg
id|wpxa2
suffix:semicolon
multiline_comment|/* write pointer, async queue 2 */
DECL|member|swpxs
id|formac_reg
id|swpxs
suffix:semicolon
multiline_comment|/* shadow write pointer, sync queue */
DECL|member|swpxa0
id|formac_reg
id|swpxa0
suffix:semicolon
multiline_comment|/* shadow write pointer, async queue 0 */
DECL|member|swpxa1
id|formac_reg
id|swpxa1
suffix:semicolon
multiline_comment|/* shadow write pointer, async queue 1 */
DECL|member|swpxa2
id|formac_reg
id|swpxa2
suffix:semicolon
multiline_comment|/* shadow write pointer, async queue 2 */
DECL|member|rpxs
id|formac_reg
id|rpxs
suffix:semicolon
multiline_comment|/* read pointer, sync queue */
DECL|member|rpxa0
id|formac_reg
id|rpxa0
suffix:semicolon
multiline_comment|/* read pointer, async queue 0 */
DECL|member|rpxa1
id|formac_reg
id|rpxa1
suffix:semicolon
multiline_comment|/* read pointer, async queue 1 */
DECL|member|rpxa2
id|formac_reg
id|rpxa2
suffix:semicolon
multiline_comment|/* read pointer, async queue 2 */
DECL|member|marr
id|formac_reg
id|marr
suffix:semicolon
multiline_comment|/* memory address for random reads */
DECL|member|marw
id|formac_reg
id|marw
suffix:semicolon
multiline_comment|/* memory address for random writes */
DECL|member|mdru
id|formac_reg
id|mdru
suffix:semicolon
multiline_comment|/* memory data register, upper */
DECL|member|mdrl
id|formac_reg
id|mdrl
suffix:semicolon
multiline_comment|/* memory data register, lower */
DECL|member|tmsync
id|formac_reg
id|tmsync
suffix:semicolon
multiline_comment|/* TSync timer value */
DECL|member|fcntr
id|formac_reg
id|fcntr
suffix:semicolon
multiline_comment|/* frame counter */
DECL|member|lcntr
id|formac_reg
id|lcntr
suffix:semicolon
multiline_comment|/* lost counter */
DECL|member|ecntr
id|formac_reg
id|ecntr
suffix:semicolon
multiline_comment|/* error counter */
)brace
suffix:semicolon
multiline_comment|/* Values for cmdreg1 */
DECL|macro|C1_SOFTWARE_RESET
mdefine_line|#define C1_SOFTWARE_RESET&t;1
DECL|macro|C1_IRMEMWI
mdefine_line|#define C1_IRMEMWI&t;&t;2
DECL|macro|C1_IRMEMWO
mdefine_line|#define C1_IRMEMWO&t;&t;3
DECL|macro|C1_IDLE_LISTEN
mdefine_line|#define C1_IDLE_LISTEN&t;&t;4
DECL|macro|C1_CLAIM_LISTEN
mdefine_line|#define C1_CLAIM_LISTEN&t;&t;5
DECL|macro|C1_BEACON_LISTEN
mdefine_line|#define C1_BEACON_LISTEN&t;6
DECL|macro|C1_LOAD_TVX
mdefine_line|#define C1_LOAD_TVX&t;&t;7
DECL|macro|C1_SEND_NR_TOKEN
mdefine_line|#define C1_SEND_NR_TOKEN&t;0x0c
DECL|macro|C1_SEND_R_TOKEN
mdefine_line|#define C1_SEND_R_TOKEN&t;&t;0x0d
DECL|macro|C1_ENTER_SI_MODE
mdefine_line|#define C1_ENTER_SI_MODE&t;0x0e
DECL|macro|C1_EXIT_SI_MODE
mdefine_line|#define C1_EXIT_SI_MODE&t;&t;0x0f
DECL|macro|C1_CLR_SYNCQ_LOCK
mdefine_line|#define C1_CLR_SYNCQ_LOCK&t;0x11
DECL|macro|C1_CLR_ASYNCQ0_LOCK
mdefine_line|#define C1_CLR_ASYNCQ0_LOCK&t;0x12
DECL|macro|C1_CLR_ASYNCQ1_LOCK
mdefine_line|#define C1_CLR_ASYNCQ1_LOCK&t;0x14
DECL|macro|C1_CLR_ASYNCQ2_LOCK
mdefine_line|#define C1_CLR_ASYNCQ2_LOCK&t;0x18
DECL|macro|C1_CLR_RECVQ_LOCK
mdefine_line|#define C1_CLR_RECVQ_LOCK&t;0x20
DECL|macro|C1_CLR_ALL_LOCKS
mdefine_line|#define C1_CLR_ALL_LOCKS&t;0x3f
multiline_comment|/* Values for cmdreg2 */
DECL|macro|C2_XMIT_SYNCQ
mdefine_line|#define C2_XMIT_SYNCQ&t;&t;1
DECL|macro|C2_XMIT_ASYNCQ0
mdefine_line|#define C2_XMIT_ASYNCQ0&t;&t;2
DECL|macro|C2_XMIT_ASYNCQ1
mdefine_line|#define C2_XMIT_ASYNCQ1&t;&t;4
DECL|macro|C2_XMIT_ASYNCQ2
mdefine_line|#define C2_XMIT_ASYNCQ2&t;&t;8
DECL|macro|C2_ABORT_XMIT
mdefine_line|#define C2_ABORT_XMIT&t;&t;0x10
DECL|macro|C2_RESET_XMITQS
mdefine_line|#define C2_RESET_XMITQS&t;&t;0x20
DECL|macro|C2_SET_TAG
mdefine_line|#define C2_SET_TAG&t;&t;0x30
DECL|macro|C2_EN_RECV_FRAME
mdefine_line|#define C2_EN_RECV_FRAME&t;0x40
multiline_comment|/* Bits in (st1u &lt;&lt; 16) + st1l (and (imsk1u &lt;&lt; 16) + imsk1l) */
DECL|macro|S1_XMIT_ABORT
mdefine_line|#define S1_XMIT_ABORT&t;&t;0x80000000
DECL|macro|S1_XABORT_ASYNC2
mdefine_line|#define S1_XABORT_ASYNC2&t;0x40000000
DECL|macro|S1_XABORT_ASYNC1
mdefine_line|#define S1_XABORT_ASYNC1&t;0x20000000
DECL|macro|S1_XABORT_ASYNC0
mdefine_line|#define S1_XABORT_ASYNC0&t;0x10000000
DECL|macro|S1_XABORT_SYNC
mdefine_line|#define S1_XABORT_SYNC&t;&t;0x08000000
DECL|macro|S1_XBUF_FULL_SYNC
mdefine_line|#define S1_XBUF_FULL_SYNC&t;0x04000000
DECL|macro|S1_XBUF_FULL_ASYNC
mdefine_line|#define S1_XBUF_FULL_ASYNC&t;0x02000000
DECL|macro|S1_XDONE_SYNC
mdefine_line|#define S1_XDONE_SYNC&t;&t;0x01000000
DECL|macro|S1_END_CHAIN_ASYNC2
mdefine_line|#define S1_END_CHAIN_ASYNC2&t;0x00800000
DECL|macro|S1_END_CHAIN_ASYNC1
mdefine_line|#define S1_END_CHAIN_ASYNC1&t;0x00400000
DECL|macro|S1_END_CHAIN_ASYNC0
mdefine_line|#define S1_END_CHAIN_ASYNC0&t;0x00200000
DECL|macro|S1_END_CHAIN_SYNC
mdefine_line|#define S1_END_CHAIN_SYNC&t;0x00100000
DECL|macro|S1_END_FRAME_ASYNC2
mdefine_line|#define S1_END_FRAME_ASYNC2&t;0x00080000
DECL|macro|S1_END_FRAME_ASYNC1
mdefine_line|#define S1_END_FRAME_ASYNC1&t;0x00040000
DECL|macro|S1_END_FRAME_ASYNC0
mdefine_line|#define S1_END_FRAME_ASYNC0&t;0x00020000
DECL|macro|S1_END_FRAME_SYNC
mdefine_line|#define S1_END_FRAME_SYNC&t;0x00010000
DECL|macro|S1_BUF_UNDERRUN_ASYNC2
mdefine_line|#define S1_BUF_UNDERRUN_ASYNC2&t;0x00008000
DECL|macro|S1_BUF_UNDERRUN_ASYNC1
mdefine_line|#define S1_BUF_UNDERRUN_ASYNC1&t;0x00004000
DECL|macro|S1_BUF_UNDERRUN_ASYNC0
mdefine_line|#define S1_BUF_UNDERRUN_ASYNC0&t;0x00002000
DECL|macro|S1_BUF_UNDERRUN_SYNC
mdefine_line|#define S1_BUF_UNDERRUN_SYNC&t;0x00001000
DECL|macro|S1_PAR_ERROR_ASYNC2
mdefine_line|#define S1_PAR_ERROR_ASYNC2&t;0x00000800
DECL|macro|S1_PAR_ERROR_ASYNC1
mdefine_line|#define S1_PAR_ERROR_ASYNC1&t;0x00000400
DECL|macro|S1_PAR_ERROR_ASYNC0
mdefine_line|#define S1_PAR_ERROR_ASYNC0&t;0x00000200
DECL|macro|S1_PAR_ERROR_SYNC
mdefine_line|#define S1_PAR_ERROR_SYNC&t;0x00000100
DECL|macro|S1_XINSTR_FULL_ASYNC2
mdefine_line|#define S1_XINSTR_FULL_ASYNC2&t;0x00000080
DECL|macro|S1_XINSTR_FULL_ASYNC1
mdefine_line|#define S1_XINSTR_FULL_ASYNC1&t;0x00000040
DECL|macro|S1_XINSTR_FULL_ASYNC0
mdefine_line|#define S1_XINSTR_FULL_ASYNC0&t;0x00000020
DECL|macro|S1_XINSTR_FULL_SYNC
mdefine_line|#define S1_XINSTR_FULL_SYNC&t;0x00000010
DECL|macro|S1_QUEUE_LOCK_ASYNC2
mdefine_line|#define S1_QUEUE_LOCK_ASYNC2&t;0x00000008
DECL|macro|S1_QUEUE_LOCK_ASYNC1
mdefine_line|#define S1_QUEUE_LOCK_ASYNC1&t;0x00000004
DECL|macro|S1_QUEUE_LOCK_ASYNC0
mdefine_line|#define S1_QUEUE_LOCK_ASYNC0&t;0x00000002
DECL|macro|S1_QUEUE_LOCK_SYNC
mdefine_line|#define S1_QUEUE_LOCK_SYNC&t;0x00000001
multiline_comment|/* Bits in (st2u &lt;&lt; 16) + st2l (and (imsk2u &lt;&lt; 16) + imsk2l) */
DECL|macro|S2_RECV_COMPLETE
mdefine_line|#define S2_RECV_COMPLETE&t;0x80000000
DECL|macro|S2_RECV_BUF_EMPTY
mdefine_line|#define S2_RECV_BUF_EMPTY&t;0x40000000
DECL|macro|S2_RECV_ABORT
mdefine_line|#define S2_RECV_ABORT&t;&t;0x20000000
DECL|macro|S2_RECV_BUF_FULL
mdefine_line|#define S2_RECV_BUF_FULL&t;0x10000000
DECL|macro|S2_RECV_FIFO_OVF
mdefine_line|#define S2_RECV_FIFO_OVF&t;0x08000000
DECL|macro|S2_RECV_FRAME
mdefine_line|#define S2_RECV_FRAME&t;&t;0x04000000
DECL|macro|S2_RECV_FRCT_OVF
mdefine_line|#define S2_RECV_FRCT_OVF&t;0x02000000
DECL|macro|S2_NP_SIMULT_LOAD
mdefine_line|#define S2_NP_SIMULT_LOAD&t;0x01000000
DECL|macro|S2_ERR_SPECIAL_FR
mdefine_line|#define S2_ERR_SPECIAL_FR&t;0x00800000
DECL|macro|S2_CLAIM_STATE
mdefine_line|#define S2_CLAIM_STATE&t;&t;0x00400000
DECL|macro|S2_MY_CLAIM
mdefine_line|#define S2_MY_CLAIM&t;&t;0x00200000
DECL|macro|S2_HIGHER_CLAIM
mdefine_line|#define S2_HIGHER_CLAIM&t;&t;0x00100000
DECL|macro|S2_LOWER_CLAIM
mdefine_line|#define S2_LOWER_CLAIM&t;&t;0x00080000
DECL|macro|S2_BEACON_STATE
mdefine_line|#define S2_BEACON_STATE&t;&t;0x00040000
DECL|macro|S2_MY_BEACON
mdefine_line|#define S2_MY_BEACON&t;&t;0x00020000
DECL|macro|S2_OTHER_BEACON
mdefine_line|#define S2_OTHER_BEACON&t;&t;0x00010000
DECL|macro|S2_RING_OP
mdefine_line|#define S2_RING_OP&t;&t;0x00008000
DECL|macro|S2_MULTIPLE_DA
mdefine_line|#define S2_MULTIPLE_DA&t;&t;0x00004000
DECL|macro|S2_TOKEN_ERR
mdefine_line|#define S2_TOKEN_ERR&t;&t;0x00002000
DECL|macro|S2_TOKEN_ISSUED
mdefine_line|#define S2_TOKEN_ISSUED&t;&t;0x00001000
DECL|macro|S2_TVX_EXP
mdefine_line|#define S2_TVX_EXP&t;&t;0x00000800
DECL|macro|S2_TRT_EXP
mdefine_line|#define S2_TRT_EXP&t;&t;0x00000400
DECL|macro|S2_MISSED_FRAME
mdefine_line|#define S2_MISSED_FRAME&t;&t;0x00000200
DECL|macro|S2_ADDRESS_DET
mdefine_line|#define S2_ADDRESS_DET&t;&t;0x00000100
DECL|macro|S2_PHY_INVALID
mdefine_line|#define S2_PHY_INVALID&t;&t;0x00000080
DECL|macro|S2_LOST_CTR_OVF
mdefine_line|#define S2_LOST_CTR_OVF&t;&t;0x00000040
DECL|macro|S2_ERR_CTR_OVF
mdefine_line|#define S2_ERR_CTR_OVF&t;&t;0x00000020
DECL|macro|S2_FRAME_CTR_OVF
mdefine_line|#define S2_FRAME_CTR_OVF&t;0x00000010
DECL|macro|S2_SHORT_IFG
mdefine_line|#define S2_SHORT_IFG&t;&t;0x00000008
DECL|macro|S2_DUPL_CLAIM
mdefine_line|#define S2_DUPL_CLAIM&t;&t;0x00000004
DECL|macro|S2_TRT_EXP_RECOV
mdefine_line|#define S2_TRT_EXP_RECOV&t;0x00000002
multiline_comment|/* Bits in mdreg1 */
DECL|macro|M1_SINGLE_FRAME
mdefine_line|#define M1_SINGLE_FRAME&t;&t;0x8000
DECL|macro|M1_MODE
mdefine_line|#define M1_MODE&t;&t;&t;0x7000
DECL|macro|M1_MODE_INITIALIZE
mdefine_line|#define M1_MODE_INITIALIZE&t;0x0000
DECL|macro|M1_MODE_MEMORY
mdefine_line|#define M1_MODE_MEMORY&t;&t;0x1000
DECL|macro|M1_MODE_ONLINE_SP
mdefine_line|#define M1_MODE_ONLINE_SP&t;0x2000
DECL|macro|M1_MODE_ONLINE
mdefine_line|#define M1_MODE_ONLINE&t;&t;0x3000
DECL|macro|M1_MODE_INT_LOOP
mdefine_line|#define M1_MODE_INT_LOOP&t;0x4000
DECL|macro|M1_MODE_EXT_LOOP
mdefine_line|#define M1_MODE_EXT_LOOP&t;0x7000
DECL|macro|M1_SHORT_ADRS
mdefine_line|#define M1_SHORT_ADRS&t;&t;0x0800
DECL|macro|M1_ADDET
mdefine_line|#define M1_ADDET&t;&t;0x0700
DECL|macro|M1_ADDET_NORM
mdefine_line|#define M1_ADDET_NORM&t;&t;0x0000
DECL|macro|M1_ADDET_METOO
mdefine_line|#define M1_ADDET_METOO&t;&t;0x0100
DECL|macro|M1_ADDET_NSA_NOTME
mdefine_line|#define M1_ADDET_NSA_NOTME&t;0x0200
DECL|macro|M1_ADDET_NSA
mdefine_line|#define M1_ADDET_NSA&t;&t;0x0300
DECL|macro|M1_ADDET_DISABLE_RECV
mdefine_line|#define M1_ADDET_DISABLE_RECV&t;0x0400
DECL|macro|M1_ADDET_LIM_PROMISC
mdefine_line|#define M1_ADDET_LIM_PROMISC&t;0x0600
DECL|macro|M1_ADDET_PROMISC
mdefine_line|#define M1_ADDET_PROMISC&t;0x0700
DECL|macro|M1_SELECT_RA
mdefine_line|#define M1_SELECT_RA&t;&t;0x0080
DECL|macro|M1_DISABLE_CARRY
mdefine_line|#define M1_DISABLE_CARRY&t;0x0040
DECL|macro|M1_EXT_GRP
mdefine_line|#define M1_EXT_GRP&t;&t;0x0030
DECL|macro|M1_EXT_GRP_MYGRP
mdefine_line|#define M1_EXT_GRP_MYGRP&t;0x0000
DECL|macro|M1_EXT_GRP_SOFT
mdefine_line|#define M1_EXT_GRP_SOFT&t;&t;0x0010
DECL|macro|M1_EXT_GRP_UPPER24
mdefine_line|#define M1_EXT_GRP_UPPER24&t;0x0020
DECL|macro|M1_EXT_GRP_UPPER16
mdefine_line|#define M1_EXT_GRP_UPPER16&t;0x0030
DECL|macro|M1_LOCK_XMIT_QS
mdefine_line|#define M1_LOCK_XMIT_QS&t;&t;0x0008
DECL|macro|M1_FULL_DUPLEX
mdefine_line|#define M1_FULL_DUPLEX&t;&t;0x0004
DECL|macro|M1_XMTINH_PIN
mdefine_line|#define M1_XMTINH_PIN&t;&t;0x0002
multiline_comment|/* Bits in mdreg2 */
DECL|macro|M2_TAGMODE
mdefine_line|#define M2_TAGMODE&t;&t;0x8000
DECL|macro|M2_STRIP_FCS
mdefine_line|#define M2_STRIP_FCS&t;&t;0x4000
DECL|macro|M2_CHECK_PARITY
mdefine_line|#define M2_CHECK_PARITY&t;&t;0x2000
DECL|macro|M2_EVEN_PARITY
mdefine_line|#define M2_EVEN_PARITY&t;&t;0x1000
DECL|macro|M2_LSB_FIRST
mdefine_line|#define M2_LSB_FIRST&t;&t;0x0800
DECL|macro|M2_RCV_BYTE_BDRY_MASK
mdefine_line|#define M2_RCV_BYTE_BDRY_MASK&t;0x0600
DECL|macro|M2_RCV_BYTE_BDRY
mdefine_line|#define M2_RCV_BYTE_BDRY&t;0x0200
DECL|macro|M2_ENABLE_HSREQ
mdefine_line|#define M2_ENABLE_HSREQ&t;&t;0x0100
DECL|macro|M2_ENABLE_NPDMA
mdefine_line|#define M2_ENABLE_NPDMA&t;&t;0x0080
DECL|macro|M2_SYNC_NPDMA
mdefine_line|#define M2_SYNC_NPDMA&t;&t;0x0040
DECL|macro|M2_SYMBOL_CTRL
mdefine_line|#define M2_SYMBOL_CTRL&t;&t;0x0020
DECL|macro|M2_RECV_BAD_FRAMES
mdefine_line|#define M2_RECV_BAD_FRAMES&t;0x0010
DECL|macro|M2_AFULL_MASK
mdefine_line|#define M2_AFULL_MASK&t;&t;0x000f
DECL|macro|M2_AFULL
mdefine_line|#define M2_AFULL&t;&t;0x0001
multiline_comment|/* Bits in stmchn */
DECL|macro|SM_REV_MASK
mdefine_line|#define SM_REV_MASK&t;&t;0xe000
DECL|macro|SM_REV
mdefine_line|#define SM_REV&t;&t;&t;0x2000
DECL|macro|SM_SEND_IMM_MODE
mdefine_line|#define SM_SEND_IMM_MODE&t;0x1000
DECL|macro|SM_TOKEN_MODE
mdefine_line|#define SM_TOKEN_MODE&t;&t;0x0c00
DECL|macro|SM_TOKEN_MODE_NR
mdefine_line|#define SM_TOKEN_MODE_NR&t;0x0000
DECL|macro|SM_TOKEN_MODE_ENTER_R
mdefine_line|#define SM_TOKEN_MODE_ENTER_R&t;0x0400
DECL|macro|SM_TOKEN_MODE_ENTER_NR
mdefine_line|#define SM_TOKEN_MODE_ENTER_NR&t;0x0800
DECL|macro|SM_TOKEN_MODE_R
mdefine_line|#define SM_TOKEN_MODE_R&t;&t;0x0c00
DECL|macro|SM_RCV_STATE
mdefine_line|#define SM_RCV_STATE&t;&t;0x0380
DECL|macro|SM_XMIT_STATE
mdefine_line|#define SM_XMIT_STATE&t;&t;0x0070
DECL|macro|SM_MDR_PENDING
mdefine_line|#define SM_MDR_PENDING&t;&t;0x0008
DECL|macro|SM_MDR_TAG
mdefine_line|#define SM_MDR_TAG&t;&t;0x0004
multiline_comment|/* Bits in transmit descriptor */
DECL|macro|TD_MORE
mdefine_line|#define TD_MORE&t;&t;&t;0x80000000
DECL|macro|TD_MAGIC
mdefine_line|#define TD_MAGIC&t;&t;0x40000000
DECL|macro|TD_BYTE_BDRY_MASK
mdefine_line|#define TD_BYTE_BDRY_MASK&t;0x18000000
DECL|macro|TD_BYTE_BDRY_1
mdefine_line|#define TD_BYTE_BDRY_1&t;&t;0x08000000
DECL|macro|TD_XMIT_DONE
mdefine_line|#define TD_XMIT_DONE&t;&t;0x04000000
DECL|macro|TD_NO_FCS
mdefine_line|#define TD_NO_FCS&t;&t;0x02000000
DECL|macro|TD_XMIT_ABORT
mdefine_line|#define TD_XMIT_ABORT&t;&t;0x01000000
DECL|macro|TD_BYTE_BDRY_LG
mdefine_line|#define TD_BYTE_BDRY_LG&t;&t;27
multiline_comment|/* Bits in pointer in buffer memory (nontag mode) */
DECL|macro|PT_MAGIC
mdefine_line|#define PT_MAGIC&t;&t;0xa0000000
multiline_comment|/* Bits in receive status word */
DECL|macro|RS_VALID
mdefine_line|#define RS_VALID&t;&t;0x80000000
DECL|macro|RS_ABORTED
mdefine_line|#define RS_ABORTED&t;&t;0x40000000
DECL|macro|RS_SRC_ROUTE
mdefine_line|#define RS_SRC_ROUTE&t;&t;0x10000000
DECL|macro|RS_E_INDIC
mdefine_line|#define RS_E_INDIC&t;&t;0x08000000
DECL|macro|RS_A_INDIC
mdefine_line|#define RS_A_INDIC&t;&t;0x04000000
DECL|macro|RS_C_INDIC
mdefine_line|#define RS_C_INDIC&t;&t;0x02000000
DECL|macro|RS_ERROR
mdefine_line|#define RS_ERROR&t;&t;0x01000000
DECL|macro|RS_ADDR_MATCH
mdefine_line|#define RS_ADDR_MATCH&t;&t;0x00800000
DECL|macro|RS_FRAME_TYPE
mdefine_line|#define RS_FRAME_TYPE&t;&t;0x00700000
DECL|macro|RS_FT_SMT
mdefine_line|#define RS_FT_SMT&t;&t;0x00000000
DECL|macro|RS_FT_LLC
mdefine_line|#define RS_FT_LLC&t;&t;0x00100000
DECL|macro|RS_FT_IMPL
mdefine_line|#define RS_FT_IMPL&t;&t;0x00200000
DECL|macro|RS_FT_MAC
mdefine_line|#define RS_FT_MAC&t;&t;0x00400000
DECL|macro|RS_FT_LLC_SYNC
mdefine_line|#define RS_FT_LLC_SYNC&t;&t;0x00500000
DECL|macro|RS_FT_IMPL_SYNC
mdefine_line|#define RS_FT_IMPL_SYNC&t;&t;0x00600000
DECL|macro|RS_BYTE_BDRY_MASK
mdefine_line|#define RS_BYTE_BDRY_MASK&t;0x00030000
DECL|macro|RS_BYTE_BDRY
mdefine_line|#define RS_BYTE_BDRY&t;&t;0x00010000
DECL|macro|RS_BYTE_BDRY_LG
mdefine_line|#define RS_BYTE_BDRY_LG&t;&t;16
DECL|macro|RS_LENGTH
mdefine_line|#define RS_LENGTH&t;&t;0x0000ffff
eof
