multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/time.h&n; *&n; * Copyright (C) 1998 Deborah Wallach.&n; * Twiddles  (C) 1999 &t;Hugo Fiennes &lt;hugo@empeg.com&gt;&n; * &n; * 2000/03/29 (C) Nicolas Pitre &lt;nico@cam.org&gt;&n; *&t;Rewritten: big cleanup, much simpler, better HZ acuracy.&n; *&n; */
multiline_comment|/* IRQs are disabled before entering here from do_gettimeofday() */
DECL|function|sa1100_gettimeoffset
r_static
r_int
r_int
id|sa1100_gettimeoffset
(paren
r_void
)paren
(brace
r_int
r_int
id|ticks_to_match
comma
id|elapsed
comma
id|usec
suffix:semicolon
multiline_comment|/* Get ticks before next timer match */
id|ticks_to_match
op_assign
id|OSMR0
op_minus
id|OSCR
suffix:semicolon
multiline_comment|/* We need elapsed ticks since last match */
id|elapsed
op_assign
id|LATCH
op_minus
id|ticks_to_match
suffix:semicolon
multiline_comment|/* Now convert them to usec */
id|usec
op_assign
(paren
r_int
r_int
)paren
(paren
id|elapsed
op_star
id|tick
)paren
op_div
id|LATCH
suffix:semicolon
r_return
id|usec
suffix:semicolon
)brace
DECL|function|sa1100_timer_interrupt
r_static
r_void
id|sa1100_timer_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|flags
suffix:semicolon
r_int
id|next_match
suffix:semicolon
multiline_comment|/* Loop until we get ahead of the free running timer.&n;&t; * This ensures an exact clock tick count and time acuracy.&n;&t; * IRQs are disabled inside the loop to ensure coherence between&n;&t; * lost_ticks (updated in do_timer()) and the match reg value, so we&n;&t; * can use do_gettimeofday() from interrupt handlers.&n;&t; */
r_do
(brace
id|do_leds
c_func
(paren
)paren
suffix:semicolon
id|save_flags_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|do_timer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|OSSR
op_assign
id|OSSR_M0
suffix:semicolon
multiline_comment|/* Clear match on timer 0 */
id|next_match
op_assign
(paren
id|OSMR0
op_add_assign
id|LATCH
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
r_int
r_int
)paren
(paren
id|next_match
op_minus
id|OSCR
)paren
op_le
l_int|0
)paren
(brace
suffix:semicolon
)brace
)brace
DECL|function|setup_timer
r_extern
r_inline
r_void
id|setup_timer
(paren
r_void
)paren
(brace
id|gettimeoffset
op_assign
id|sa1100_gettimeoffset
suffix:semicolon
id|timer_irq.handler
op_assign
id|sa1100_timer_interrupt
suffix:semicolon
id|OSMR0
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* set initial match at 0 */
id|OSSR
op_assign
l_int|0xf
suffix:semicolon
multiline_comment|/* clear status on all timers */
id|setup_arm_irq
c_func
(paren
id|IRQ_OST0
comma
op_amp
id|timer_irq
)paren
suffix:semicolon
id|OIER
op_or_assign
id|OIER_E0
suffix:semicolon
multiline_comment|/* enable match on timer 0 to cause interrupts */
id|OSCR
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* initialize free-running timer, force first match */
)brace
eof
