multiline_comment|/*&n;   * Copyright 1996 The Australian National University.&n;   * Copyright 1996 Fujitsu Laboratories Limited&n;   * &n;   * This software may be distributed under the terms of the Gnu&n;   * Public License version 2 or later&n;  */
multiline_comment|/*&n; * Routines for controlling the Am79c864 physical layer controller.&n; *&n; * This chip implements some parts of the FDDI SMT standard&n; * (PCM: physical connection management, LEM: link error monitor, etc.)&n; * as well as the FDDI PHY standard.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &quot;apfddi.h&quot;
macro_line|#include &quot;smt-types.h&quot;
macro_line|#include &quot;am79c864.h&quot;
macro_line|#include &quot;plc.h&quot;
macro_line|#include &quot;apfddi-reg.h&quot;
r_typedef
r_enum
(brace
DECL|enumerator|off
id|off
comma
DECL|enumerator|signalling
id|signalling
comma
DECL|enumerator|doing_lct
id|doing_lct
comma
DECL|enumerator|joining
id|joining
comma
DECL|enumerator|active
id|active
DECL|typedef|PlcPhase
)brace
id|PlcPhase
suffix:semicolon
DECL|struct|plc_state
r_struct
id|plc_state
(brace
DECL|member|loopback
id|LoopbackType
id|loopback
suffix:semicolon
DECL|member|t_val
r_char
id|t_val
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|r_val
r_char
id|r_val
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|n
r_int
id|n
suffix:semicolon
DECL|member|peer_type
id|PortType
id|peer_type
suffix:semicolon
DECL|member|phase
id|PlcPhase
id|phase
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|this_plc_info
r_struct
id|plc_info
op_star
id|this_plc_info
suffix:semicolon
DECL|variable|this_plc_state
r_struct
id|plc_state
id|this_plc_state
suffix:semicolon
DECL|function|plc_init
r_void
id|plc_init
c_func
(paren
r_struct
id|plc_info
op_star
id|pip
)paren
(brace
r_int
r_class
comma
id|x
suffix:semicolon
r_struct
id|plc_state
op_star
id|psp
op_assign
op_amp
id|this_plc_state
suffix:semicolon
id|this_plc_info
op_assign
id|pip
suffix:semicolon
multiline_comment|/* first turn it off, clear registers */
r_class
op_assign
id|pip-&gt;port_type
op_eq
id|pt_s
ques
c_cond
id|CB_CLASS_S
suffix:colon
l_int|0
suffix:semicolon
id|plc-&gt;ctrl_b
op_assign
id|CB_PC_STOP
op_plus
r_class
suffix:semicolon
id|plc-&gt;intr_mask
op_assign
id|IE_NP_ERROR
suffix:semicolon
id|x
op_assign
id|plc-&gt;intr_event
suffix:semicolon
multiline_comment|/* these register clear when read */
id|x
op_assign
id|plc-&gt;viol_sym_ct
suffix:semicolon
id|x
op_assign
id|plc-&gt;min_idle_ct
suffix:semicolon
id|x
op_assign
id|plc-&gt;link_err_ct
suffix:semicolon
multiline_comment|/* initialize registers */
id|plc-&gt;ctrl_a
op_assign
l_int|0
suffix:semicolon
id|plc-&gt;ctrl_b
op_assign
r_class
suffix:semicolon
id|plc-&gt;c_min
op_assign
id|pip-&gt;c_min
op_rshift
l_int|8
suffix:semicolon
id|plc-&gt;tl_min
op_assign
id|pip-&gt;tl_min
op_rshift
l_int|8
suffix:semicolon
id|plc-&gt;tb_min
op_assign
id|pip-&gt;tb_min
op_rshift
l_int|8
suffix:semicolon
id|plc-&gt;t_out
op_assign
id|pip-&gt;t_out
op_rshift
l_int|8
suffix:semicolon
id|plc-&gt;t_scrub
op_assign
id|pip-&gt;t_scrub
op_rshift
l_int|8
suffix:semicolon
id|plc-&gt;ns_max
op_assign
id|pip-&gt;ns_max
op_rshift
l_int|2
suffix:semicolon
id|psp-&gt;phase
op_assign
id|off
suffix:semicolon
)brace
r_int
DECL|function|plc_inited
id|plc_inited
c_func
(paren
r_struct
id|plc_info
op_star
id|pip
)paren
(brace
r_int
r_class
comma
id|x
suffix:semicolon
r_struct
id|plc_state
op_star
id|psp
op_assign
op_amp
id|this_plc_state
suffix:semicolon
r_class
op_assign
id|pip-&gt;port_type
op_eq
id|pt_s
ques
c_cond
id|CB_CLASS_S
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|plc-&gt;ctrl_a
op_amp
(paren
id|CA_LOOPBACK
op_or
id|CA_FOT_OFF
op_or
id|CA_EB_LOOP
op_or
id|CA_LM_LOOP
)paren
)paren
op_ne
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|plc-&gt;ctrl_b
op_amp
(paren
id|CB_CONFIG_CTRL
op_or
id|CB_CLASS_S
op_or
id|CB_PC_MAINT
)paren
)paren
op_ne
r_class
)paren
r_return
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|plc-&gt;status_a
op_amp
id|SA_SIG_DETECT
)paren
r_return
l_int|3
suffix:semicolon
r_if
c_cond
(paren
(paren
id|plc-&gt;status_b
op_amp
(paren
id|SB_PCI_STATE
op_or
id|SB_PCM_STATE
)paren
)paren
op_ne
(paren
id|SB_PCI_STATE_INSERTED
op_or
id|SB_PCM_STATE_ACTIVE
)paren
)paren
r_return
l_int|4
suffix:semicolon
multiline_comment|/* all seems OK, reset the timers and counters just to be sure */
id|plc-&gt;intr_mask
op_assign
id|IE_NP_ERROR
suffix:semicolon
id|x
op_assign
id|plc-&gt;intr_event
suffix:semicolon
multiline_comment|/* these register clear when read */
id|x
op_assign
id|plc-&gt;viol_sym_ct
suffix:semicolon
id|x
op_assign
id|plc-&gt;min_idle_ct
suffix:semicolon
id|x
op_assign
id|plc-&gt;link_err_ct
suffix:semicolon
id|plc-&gt;c_min
op_assign
id|pip-&gt;c_min
op_rshift
l_int|8
suffix:semicolon
id|plc-&gt;tl_min
op_assign
id|pip-&gt;tl_min
op_rshift
l_int|8
suffix:semicolon
id|plc-&gt;tb_min
op_assign
id|pip-&gt;tb_min
op_rshift
l_int|8
suffix:semicolon
id|plc-&gt;t_out
op_assign
id|pip-&gt;t_out
op_rshift
l_int|8
suffix:semicolon
id|plc-&gt;t_scrub
op_assign
id|pip-&gt;t_scrub
op_rshift
l_int|8
suffix:semicolon
id|plc-&gt;ns_max
op_assign
id|pip-&gt;ns_max
op_rshift
l_int|2
suffix:semicolon
id|psp-&gt;phase
op_assign
id|active
suffix:semicolon
multiline_comment|/* XXX should initialize other fields of this_plc_state */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|plc_sleep
r_void
id|plc_sleep
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|pc_start
r_void
id|pc_start
c_func
(paren
id|LoopbackType
id|loopback
)paren
(brace
r_int
id|x
suffix:semicolon
r_struct
id|plc_info
op_star
id|pip
op_assign
id|this_plc_info
suffix:semicolon
r_struct
id|plc_state
op_star
id|psp
op_assign
op_amp
id|this_plc_state
suffix:semicolon
multiline_comment|/* make sure it&squot;s off */
id|plc-&gt;ctrl_b
op_and_assign
op_complement
id|CB_PCM_CTRL
suffix:semicolon
id|plc-&gt;ctrl_b
op_or_assign
id|CB_PC_STOP
suffix:semicolon
multiline_comment|/* set up loopback required */
id|psp-&gt;loopback
op_assign
id|loopback
suffix:semicolon
id|x
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|loopback
)paren
(brace
r_case
id|loop_plc_lm
suffix:colon
id|x
op_assign
id|CA_LM_LOOP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|loop_plc_eb
suffix:colon
id|x
op_assign
id|CA_EB_LOOP
suffix:semicolon
r_break
suffix:semicolon
r_case
id|loop_pdx
suffix:colon
id|x
op_assign
id|CA_LOOPBACK
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|x
op_assign
l_int|0
suffix:semicolon
)brace
id|plc-&gt;ctrl_a
op_assign
id|x
suffix:semicolon
multiline_comment|/* set up bits to be exchanged */
id|psp-&gt;t_val
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|psp-&gt;t_val
(braket
l_int|1
)braket
op_assign
(paren
(paren
r_int
)paren
id|pip-&gt;port_type
op_rshift
l_int|1
)paren
op_amp
l_int|1
suffix:semicolon
id|psp-&gt;t_val
(braket
l_int|2
)braket
op_assign
(paren
r_int
)paren
id|pip-&gt;port_type
op_amp
l_int|1
suffix:semicolon
id|psp-&gt;t_val
(braket
l_int|4
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* XXX assume we want short LCT */
id|psp-&gt;t_val
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|psp-&gt;t_val
(braket
l_int|6
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* XXX too lazy to fire up my MAC for LCT */
id|psp-&gt;t_val
(braket
l_int|8
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* XXX don&squot;t wanna local loop */
id|psp-&gt;t_val
(braket
l_int|9
)braket
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* gotta MAC on port output */
id|pc_restart
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|pc_restart
r_void
id|pc_restart
c_func
(paren
r_void
)paren
(brace
r_struct
id|plc_state
op_star
id|psp
op_assign
op_amp
id|this_plc_state
suffix:semicolon
r_if
c_cond
(paren
id|psp-&gt;phase
op_ne
id|off
)paren
id|printk
c_func
(paren
l_string|&quot;restarting pcm&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|psp-&gt;phase
op_eq
id|active
)paren
id|set_cf_join
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* we&squot;re down :-( */
id|psp-&gt;n
op_assign
l_int|0
suffix:semicolon
id|plc-&gt;vec_length
op_assign
l_int|3
op_minus
l_int|1
suffix:semicolon
id|plc-&gt;xmit_vector
op_assign
id|psp-&gt;t_val
(braket
l_int|0
)braket
op_plus
(paren
id|psp-&gt;t_val
(braket
l_int|1
)braket
op_lshift
l_int|1
)paren
op_plus
(paren
id|psp-&gt;t_val
(braket
l_int|2
)braket
op_lshift
l_int|2
)paren
suffix:semicolon
id|plc-&gt;intr_mask
op_assign
id|IE_NP_ERROR
op_or
id|IE_PCM_BREAK
op_or
id|IE_PCM_CODE
suffix:semicolon
id|plc-&gt;ctrl_b
op_and_assign
op_complement
id|CB_PCM_CTRL
suffix:semicolon
id|plc-&gt;ctrl_b
op_or_assign
id|CB_PC_START
suffix:semicolon
multiline_comment|/* light blue paper and stand clear */
id|psp-&gt;phase
op_assign
id|signalling
suffix:semicolon
)brace
DECL|function|pc_stop
r_void
id|pc_stop
c_func
(paren
r_void
)paren
(brace
r_struct
id|plc_state
op_star
id|psp
op_assign
op_amp
id|this_plc_state
suffix:semicolon
r_if
c_cond
(paren
id|psp-&gt;phase
op_eq
id|active
)paren
id|set_cf_join
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|plc-&gt;ctrl_b
op_and_assign
op_complement
id|CB_PCM_CTRL
suffix:semicolon
id|plc-&gt;ctrl_b
op_or_assign
id|CB_PC_STOP
suffix:semicolon
id|plc-&gt;intr_mask
op_assign
id|IE_NP_ERROR
suffix:semicolon
id|psp-&gt;phase
op_assign
id|off
suffix:semicolon
)brace
DECL|function|plc_poll
r_void
id|plc_poll
c_func
(paren
r_void
)paren
(brace
r_struct
id|plc_state
op_star
id|psp
op_assign
op_amp
id|this_plc_state
suffix:semicolon
r_int
id|events
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|csr0
op_amp
id|CS0_PHY_IRQ
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|events
op_assign
id|plc-&gt;intr_event
op_amp
id|plc-&gt;intr_mask
suffix:semicolon
r_if
c_cond
(paren
id|events
op_amp
id|IE_NP_ERROR
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;plc: NP error!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|events
op_amp
id|IE_PCM_BREAK
)paren
(brace
id|i
op_assign
id|plc-&gt;status_b
op_amp
id|SB_BREAK_REASON
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|SB_BREAK_REASON_START
)paren
(brace
r_if
c_cond
(paren
id|psp-&gt;phase
op_eq
id|signalling
op_logical_or
id|psp-&gt;phase
op_eq
id|doing_lct
)paren
id|pcm_dump_rtcodes
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;pcm: break reason %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|psp-&gt;phase
op_ne
id|off
)paren
id|pc_restart
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* XXX need to check for trace? */
)brace
)brace
r_if
c_cond
(paren
id|events
op_amp
id|IE_PCM_CODE
)paren
(brace
r_if
c_cond
(paren
id|psp-&gt;phase
op_eq
id|signalling
)paren
id|pcm_pseudo_code
c_func
(paren
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|psp-&gt;phase
op_eq
id|doing_lct
)paren
id|pcm_lct_done
c_func
(paren
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;XXX pcm_code interrupt in phase %d?&bslash;n&quot;
comma
id|psp-&gt;phase
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|events
op_amp
id|IE_PCM_ENABLED
)paren
(brace
r_if
c_cond
(paren
id|psp-&gt;phase
op_eq
id|joining
)paren
id|pcm_enabled
c_func
(paren
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;XXX pcm_enabled interrupt in phase %d?&bslash;n&quot;
comma
id|psp-&gt;phase
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|events
op_amp
id|IE_TRACE_PROP
)paren
(brace
r_if
c_cond
(paren
id|psp-&gt;phase
op_eq
id|active
)paren
id|pcm_trace_prop
c_func
(paren
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;XXX trace_prop interrupt in phase %d&bslash;n&quot;
comma
id|psp-&gt;phase
)paren
suffix:semicolon
)brace
)brace
DECL|function|pcm_pseudo_code
r_void
id|pcm_pseudo_code
c_func
(paren
r_void
)paren
(brace
r_struct
id|plc_info
op_star
id|pip
op_assign
id|this_plc_info
suffix:semicolon
r_struct
id|plc_state
op_star
id|psp
op_assign
op_amp
id|this_plc_state
suffix:semicolon
r_int
id|i
comma
id|nb
comma
id|lct
comma
id|hislct
suffix:semicolon
multiline_comment|/* unpack the bits from the peer */
id|nb
op_assign
id|plc-&gt;vec_length
op_plus
l_int|1
suffix:semicolon
id|i
op_assign
id|plc-&gt;rcv_vector
suffix:semicolon
r_do
(brace
id|psp-&gt;r_val
(braket
id|psp-&gt;n
op_increment
)braket
op_assign
id|i
op_amp
l_int|1
suffix:semicolon
id|i
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|nb
OG
l_int|0
)paren
suffix:semicolon
multiline_comment|/* send some more, do LCT, whatever */
r_switch
c_cond
(paren
id|psp-&gt;n
)paren
(brace
r_case
l_int|3
suffix:colon
multiline_comment|/*&n;&t; * Got escape flag, port type; send compatibility,&n;&t; * LCT duration, MAC for LCT flag.&n;&t; */
r_if
c_cond
(paren
id|psp-&gt;r_val
(braket
l_int|0
)braket
)paren
(brace
multiline_comment|/* help! what do I do now? */
id|pcm_dump_rtcodes
c_func
(paren
)paren
suffix:semicolon
id|pc_restart
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|psp-&gt;peer_type
op_assign
(paren
id|PortType
)paren
(paren
(paren
id|psp-&gt;r_val
(braket
l_int|1
)braket
op_lshift
l_int|1
)paren
op_plus
id|psp-&gt;r_val
(braket
l_int|2
)braket
)paren
suffix:semicolon
multiline_comment|/* XXX we&squot;re type S, we talk to anybody */
id|psp-&gt;t_val
(braket
l_int|3
)braket
op_assign
l_int|1
suffix:semicolon
id|plc-&gt;vec_length
op_assign
l_int|4
op_minus
l_int|1
suffix:semicolon
id|plc-&gt;xmit_vector
op_assign
id|psp-&gt;t_val
(braket
l_int|3
)braket
op_plus
(paren
id|psp-&gt;t_val
(braket
l_int|4
)braket
op_lshift
l_int|1
)paren
op_plus
(paren
id|psp-&gt;t_val
(braket
l_int|5
)braket
op_lshift
l_int|2
)paren
op_plus
(paren
id|psp-&gt;t_val
(braket
l_int|6
)braket
op_lshift
l_int|3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
multiline_comment|/*&n;&t; * Got compatibility, LCT duration, MAC for LCT flag;&n;&t; * time to do the LCT.&n;&t; */
id|lct
op_assign
(paren
id|psp-&gt;t_val
(braket
l_int|4
)braket
op_lshift
l_int|1
)paren
op_plus
id|psp-&gt;t_val
(braket
l_int|5
)braket
suffix:semicolon
id|hislct
op_assign
(paren
id|psp-&gt;r_val
(braket
l_int|4
)braket
op_lshift
l_int|1
)paren
op_plus
id|psp-&gt;r_val
(braket
l_int|5
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hislct
OG
id|lct
)paren
id|lct
op_assign
id|hislct
suffix:semicolon
multiline_comment|/* set LCT duration */
r_switch
c_cond
(paren
id|lct
)paren
(brace
r_case
l_int|0
suffix:colon
id|plc-&gt;lc_length
op_assign
id|pip-&gt;lc_short
op_rshift
l_int|8
suffix:semicolon
id|plc-&gt;ctrl_b
op_and_assign
op_complement
id|CB_LONG_LCT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|plc-&gt;lc_length
op_assign
id|pip-&gt;lc_medium
op_rshift
l_int|8
suffix:semicolon
id|plc-&gt;ctrl_b
op_and_assign
op_complement
id|CB_LONG_LCT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|plc-&gt;ctrl_b
op_or_assign
id|CB_LONG_LCT
suffix:semicolon
multiline_comment|/* XXX set up a timeout for pip-&gt;lc_long */
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|plc-&gt;ctrl_b
op_or_assign
id|CB_LONG_LCT
suffix:semicolon
multiline_comment|/* XXX set up a timeout for pip-&gt;lc_extended */
r_break
suffix:semicolon
)brace
multiline_comment|/* start the LCT */
id|i
op_assign
id|plc-&gt;link_err_ct
suffix:semicolon
multiline_comment|/* clear the register */
id|plc-&gt;ctrl_b
op_and_assign
op_complement
id|CB_PC_LCT
suffix:semicolon
multiline_comment|/* XXX assume we&squot;re not using the MAC for LCT;&n;&t;   if he&squot;s got a MAC, loop his stuff back, otherwise send idle. */
r_if
c_cond
(paren
id|psp-&gt;r_val
(braket
l_int|6
)braket
)paren
id|plc-&gt;ctrl_b
op_or_assign
id|CB_PC_LCT_LOOP
suffix:semicolon
r_else
id|plc-&gt;ctrl_b
op_or_assign
id|CB_PC_LCT_IDLE
suffix:semicolon
id|psp-&gt;phase
op_assign
id|doing_lct
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
multiline_comment|/*&n;&t; * Got LCT result, send MAC for local loop and MAC on port&n;&t; * output flags.&n;&t; */
r_if
c_cond
(paren
id|psp-&gt;t_val
(braket
l_int|7
)braket
op_logical_or
id|psp-&gt;r_val
(braket
l_int|7
)braket
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;LCT failed, restarting.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* LCT failed - do at least a medium length test next time. */
r_if
c_cond
(paren
id|psp-&gt;t_val
(braket
l_int|4
)braket
op_eq
l_int|0
op_logical_and
id|psp-&gt;t_val
(braket
l_int|5
)braket
op_eq
l_int|0
)paren
id|psp-&gt;t_val
(braket
l_int|5
)braket
op_assign
l_int|1
suffix:semicolon
id|pcm_dump_rtcodes
c_func
(paren
)paren
suffix:semicolon
id|pc_restart
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|plc-&gt;vec_length
op_assign
l_int|2
op_minus
l_int|1
suffix:semicolon
id|plc-&gt;xmit_vector
op_assign
id|psp-&gt;t_val
(braket
l_int|8
)braket
op_plus
(paren
id|psp-&gt;t_val
(braket
l_int|9
)braket
op_lshift
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
multiline_comment|/*&n;&t; * Got MAC for local loop and MAC on port output flags.&n;&t; * Let&squot;s join.&n;&t; */
id|plc-&gt;intr_mask
op_assign
id|IE_NP_ERROR
op_or
id|IE_PCM_BREAK
op_or
id|IE_PCM_ENABLED
suffix:semicolon
id|plc-&gt;ctrl_b
op_or_assign
id|CB_PC_JOIN
suffix:semicolon
id|psp-&gt;phase
op_assign
id|joining
suffix:semicolon
multiline_comment|/* printk(&quot;pcm: joining&bslash;n&quot;); */
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;pcm_pseudo_code bug: n = %d&bslash;n&quot;
comma
id|psp-&gt;n
)paren
suffix:semicolon
)brace
)brace
DECL|function|pcm_lct_done
r_void
id|pcm_lct_done
c_func
(paren
r_void
)paren
(brace
r_struct
id|plc_state
op_star
id|psp
op_assign
op_amp
id|this_plc_state
suffix:semicolon
r_int
id|i
suffix:semicolon
id|i
op_assign
id|plc-&gt;link_err_ct
suffix:semicolon
id|psp-&gt;t_val
(braket
l_int|7
)braket
op_assign
id|i
OG
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;pcm: lct %s (%d errors)&bslash;n&quot;
comma
id|psp-&gt;t_val
(braket
l_int|7
)braket
ques
c_cond
l_string|&quot;failed&quot;
suffix:colon
l_string|&quot;passed&quot;
comma
id|i
)paren
suffix:semicolon
id|plc-&gt;ctrl_b
op_and_assign
op_complement
(paren
id|CB_PC_LCT
op_or
id|CB_LONG_LCT
)paren
suffix:semicolon
id|plc-&gt;vec_length
op_assign
l_int|1
op_minus
l_int|1
suffix:semicolon
id|plc-&gt;xmit_vector
op_assign
id|psp-&gt;t_val
(braket
l_int|7
)braket
suffix:semicolon
id|psp-&gt;phase
op_assign
id|signalling
suffix:semicolon
)brace
DECL|function|pcm_dump_rtcodes
r_void
id|pcm_dump_rtcodes
c_func
(paren
r_void
)paren
(brace
r_struct
id|plc_state
op_star
id|psp
op_assign
op_amp
id|this_plc_state
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|psp-&gt;n
OG
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pcm signalling interrupted after %d bits:&bslash;nt_val:&quot;
comma
id|psp-&gt;n
)paren
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
id|psp-&gt;n
suffix:semicolon
op_increment
id|i
)paren
id|printk
c_func
(paren
l_string|&quot; %d&quot;
comma
id|psp-&gt;t_val
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nr_val:&quot;
)paren
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
id|psp-&gt;n
suffix:semicolon
op_increment
id|i
)paren
id|printk
c_func
(paren
l_string|&quot; %d&quot;
comma
id|psp-&gt;r_val
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|pcm_enabled
r_void
id|pcm_enabled
c_func
(paren
r_void
)paren
(brace
r_struct
id|plc_state
op_star
id|psp
op_assign
op_amp
id|this_plc_state
suffix:semicolon
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;pcm: enabled&bslash;n&quot;
)paren
suffix:semicolon
id|psp-&gt;phase
op_assign
id|active
suffix:semicolon
id|i
op_assign
id|plc-&gt;link_err_ct
suffix:semicolon
multiline_comment|/* clear the register */
multiline_comment|/* XXX should set up LEM here */
multiline_comment|/* XXX do we want to count violation symbols, minimum idle gaps,&n;       or elasticity buffer errors? */
id|plc-&gt;intr_mask
op_assign
id|IE_NP_ERROR
op_or
id|IE_PCM_BREAK
op_or
id|IE_TRACE_PROP
suffix:semicolon
id|set_cf_join
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* we&squot;re up :-) */
)brace
DECL|function|pcm_trace_prop
r_void
id|pcm_trace_prop
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* XXX help! what do I do now? */
id|pc_stop
c_func
(paren
)paren
suffix:semicolon
)brace
eof