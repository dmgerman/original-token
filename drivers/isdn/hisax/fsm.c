multiline_comment|/* $Id: fsm.c,v 1.4 1997/04/06 22:56:42 keil Exp $&n;&n; * Author       Karsten Keil (keil@temic-ech.spacenet.de)&n; *              based on the teles driver from Jan den Ouden&n; *&n; * Thanks to    Jan den Ouden&n; *              Fritz Elfert&n; *&n; * $Log: fsm.c,v $&n; * Revision 1.4  1997/04/06 22:56:42  keil&n; * Some cosmetic changes&n; *&n; * Revision 1.3  1997/02/16 01:04:08  fritz&n; * Bugfix: Changed timer handling caused hang with 2.1.X&n; *&n; * Revision 1.2  1997/01/09 20:57:27  keil&n; * cleanup &amp; FSM_TIMER_DEBUG&n; *&n; * Revision 1.1  1996/10/13 20:04:52  keil&n; * Initial revision&n; *&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &quot;hisax.h&quot;
DECL|macro|FSM_TIMER_DEBUG
mdefine_line|#define FSM_TIMER_DEBUG 0
r_void
DECL|function|FsmNew
id|FsmNew
c_func
(paren
r_struct
id|Fsm
op_star
id|fsm
comma
r_struct
id|FsmNode
op_star
id|fnlist
comma
r_int
id|fncount
)paren
(brace
r_int
id|i
suffix:semicolon
id|fsm-&gt;jumpmatrix
op_assign
(paren
r_int
op_star
)paren
id|kmalloc
c_func
(paren
l_int|4L
op_star
id|fsm-&gt;state_count
op_star
id|fsm-&gt;event_count
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
id|fsm-&gt;jumpmatrix
comma
l_int|0
comma
l_int|4L
op_star
id|fsm-&gt;state_count
op_star
id|fsm-&gt;event_count
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
id|fncount
suffix:semicolon
id|i
op_increment
)paren
id|fsm-&gt;jumpmatrix
(braket
id|fsm-&gt;state_count
op_star
id|fnlist
(braket
id|i
)braket
dot
id|event
op_plus
id|fnlist
(braket
id|i
)braket
dot
id|state
)braket
op_assign
(paren
r_int
)paren
id|fnlist
(braket
id|i
)braket
dot
id|routine
suffix:semicolon
)brace
r_void
DECL|function|FsmFree
id|FsmFree
c_func
(paren
r_struct
id|Fsm
op_star
id|fsm
)paren
(brace
id|kfree
c_func
(paren
(paren
r_void
op_star
)paren
id|fsm-&gt;jumpmatrix
)paren
suffix:semicolon
)brace
r_int
DECL|function|FsmEvent
id|FsmEvent
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_int
id|event
comma
r_void
op_star
id|arg
)paren
(brace
r_void
(paren
op_star
id|r
)paren
(paren
r_struct
id|FsmInst
op_star
comma
r_int
comma
r_void
op_star
)paren
suffix:semicolon
r_char
id|str
(braket
l_int|80
)braket
suffix:semicolon
id|r
op_assign
(paren
r_void
(paren
op_star
)paren
)paren
id|fi-&gt;fsm-&gt;jumpmatrix
(braket
id|fi-&gt;fsm-&gt;state_count
op_star
id|event
op_plus
id|fi-&gt;state
)braket
suffix:semicolon
r_if
c_cond
(paren
id|r
)paren
(brace
r_if
c_cond
(paren
id|fi-&gt;debug
)paren
(brace
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;State %s Event %s&quot;
comma
id|fi-&gt;fsm-&gt;strState
(braket
id|fi-&gt;state
)braket
comma
id|fi-&gt;fsm-&gt;strEvent
(braket
id|event
)braket
)paren
suffix:semicolon
id|fi
op_member_access_from_pointer
id|printdebug
c_func
(paren
id|fi
comma
id|str
)paren
suffix:semicolon
)brace
id|r
c_func
(paren
id|fi
comma
id|event
comma
id|arg
)paren
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|fi-&gt;debug
)paren
(brace
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;State %s Event %s no routine&quot;
comma
id|fi-&gt;fsm-&gt;strState
(braket
id|fi-&gt;state
)braket
comma
id|fi-&gt;fsm-&gt;strEvent
(braket
id|event
)braket
)paren
suffix:semicolon
id|fi
op_member_access_from_pointer
id|printdebug
c_func
(paren
id|fi
comma
id|str
)paren
suffix:semicolon
)brace
r_return
(paren
op_logical_neg
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|FsmChangeState
id|FsmChangeState
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_int
id|newstate
)paren
(brace
r_char
id|str
(braket
l_int|80
)braket
suffix:semicolon
id|fi-&gt;state
op_assign
id|newstate
suffix:semicolon
r_if
c_cond
(paren
id|fi-&gt;debug
)paren
(brace
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;ChangeState %s&quot;
comma
id|fi-&gt;fsm-&gt;strState
(braket
id|newstate
)braket
)paren
suffix:semicolon
id|fi
op_member_access_from_pointer
id|printdebug
c_func
(paren
id|fi
comma
id|str
)paren
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|FsmExpireTimer
id|FsmExpireTimer
c_func
(paren
r_struct
id|FsmTimer
op_star
id|ft
)paren
(brace
macro_line|#if FSM_TIMER_DEBUG
r_if
c_cond
(paren
id|ft-&gt;fi-&gt;debug
)paren
(brace
r_char
id|str
(braket
l_int|40
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;FsmExpireTimer %lx&quot;
comma
(paren
r_int
)paren
id|ft
)paren
suffix:semicolon
id|ft-&gt;fi
op_member_access_from_pointer
id|printdebug
c_func
(paren
id|ft-&gt;fi
comma
id|str
)paren
suffix:semicolon
)brace
macro_line|#endif
id|FsmEvent
c_func
(paren
id|ft-&gt;fi
comma
id|ft-&gt;event
comma
id|ft-&gt;arg
)paren
suffix:semicolon
)brace
r_void
DECL|function|FsmInitTimer
id|FsmInitTimer
c_func
(paren
r_struct
id|FsmInst
op_star
id|fi
comma
r_struct
id|FsmTimer
op_star
id|ft
)paren
(brace
id|ft-&gt;fi
op_assign
id|fi
suffix:semicolon
id|ft-&gt;tl.function
op_assign
(paren
r_void
op_star
)paren
id|FsmExpireTimer
suffix:semicolon
id|ft-&gt;tl.data
op_assign
(paren
r_int
)paren
id|ft
suffix:semicolon
macro_line|#if FSM_TIMER_DEBUG
r_if
c_cond
(paren
id|ft-&gt;fi-&gt;debug
)paren
(brace
r_char
id|str
(braket
l_int|40
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;FsmInitTimer %lx&quot;
comma
(paren
r_int
)paren
id|ft
)paren
suffix:semicolon
id|ft-&gt;fi
op_member_access_from_pointer
id|printdebug
c_func
(paren
id|ft-&gt;fi
comma
id|str
)paren
suffix:semicolon
)brace
macro_line|#endif
id|init_timer
c_func
(paren
op_amp
id|ft-&gt;tl
)paren
suffix:semicolon
)brace
r_void
DECL|function|FsmDelTimer
id|FsmDelTimer
c_func
(paren
r_struct
id|FsmTimer
op_star
id|ft
comma
r_int
id|where
)paren
(brace
macro_line|#if FSM_TIMER_DEBUG
r_if
c_cond
(paren
id|ft-&gt;fi-&gt;debug
)paren
(brace
r_char
id|str
(braket
l_int|40
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;FsmDelTimer %lx %d&quot;
comma
(paren
r_int
)paren
id|ft
comma
id|where
)paren
suffix:semicolon
id|ft-&gt;fi
op_member_access_from_pointer
id|printdebug
c_func
(paren
id|ft-&gt;fi
comma
id|str
)paren
suffix:semicolon
)brace
macro_line|#endif
id|del_timer
c_func
(paren
op_amp
id|ft-&gt;tl
)paren
suffix:semicolon
)brace
r_int
DECL|function|FsmAddTimer
id|FsmAddTimer
c_func
(paren
r_struct
id|FsmTimer
op_star
id|ft
comma
r_int
id|millisec
comma
r_int
id|event
comma
r_void
op_star
id|arg
comma
r_int
id|where
)paren
(brace
macro_line|#if FSM_TIMER_DEBUG
r_if
c_cond
(paren
id|ft-&gt;fi-&gt;debug
)paren
(brace
r_char
id|str
(braket
l_int|40
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|str
comma
l_string|&quot;FsmAddTimer %lx %d %d&quot;
comma
(paren
r_int
)paren
id|ft
comma
id|millisec
comma
id|where
)paren
suffix:semicolon
id|ft-&gt;fi
op_member_access_from_pointer
id|printdebug
c_func
(paren
id|ft-&gt;fi
comma
id|str
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|ft-&gt;tl.next
op_logical_or
id|ft-&gt;tl.prev
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;FsmAddTimer: timer already active!&bslash;n&quot;
)paren
suffix:semicolon
id|ft-&gt;fi
op_member_access_from_pointer
id|printdebug
c_func
(paren
id|ft-&gt;fi
comma
l_string|&quot;FsmAddTimer already active!&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|init_timer
c_func
(paren
op_amp
id|ft-&gt;tl
)paren
suffix:semicolon
id|ft-&gt;event
op_assign
id|event
suffix:semicolon
id|ft-&gt;arg
op_assign
id|arg
suffix:semicolon
id|ft-&gt;tl.expires
op_assign
id|jiffies
op_plus
(paren
id|millisec
op_star
id|HZ
)paren
op_div
l_int|1000
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|ft-&gt;tl
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|FsmTimerRunning
id|FsmTimerRunning
c_func
(paren
r_struct
id|FsmTimer
op_star
id|ft
)paren
(brace
r_return
(paren
id|ft-&gt;tl.next
op_ne
l_int|NULL
)paren
suffix:semicolon
)brace
r_void
DECL|function|jiftime
id|jiftime
c_func
(paren
r_char
op_star
id|s
comma
r_int
id|mark
)paren
(brace
id|s
op_add_assign
l_int|8
suffix:semicolon
op_star
id|s
op_decrement
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_star
id|s
op_decrement
op_assign
id|mark
op_mod
l_int|10
op_plus
l_char|&squot;0&squot;
suffix:semicolon
id|mark
op_div_assign
l_int|10
suffix:semicolon
op_star
id|s
op_decrement
op_assign
id|mark
op_mod
l_int|10
op_plus
l_char|&squot;0&squot;
suffix:semicolon
id|mark
op_div_assign
l_int|10
suffix:semicolon
op_star
id|s
op_decrement
op_assign
l_char|&squot;.&squot;
suffix:semicolon
op_star
id|s
op_decrement
op_assign
id|mark
op_mod
l_int|10
op_plus
l_char|&squot;0&squot;
suffix:semicolon
id|mark
op_div_assign
l_int|10
suffix:semicolon
op_star
id|s
op_decrement
op_assign
id|mark
op_mod
l_int|6
op_plus
l_char|&squot;0&squot;
suffix:semicolon
id|mark
op_div_assign
l_int|6
suffix:semicolon
op_star
id|s
op_decrement
op_assign
l_char|&squot;:&squot;
suffix:semicolon
op_star
id|s
op_decrement
op_assign
id|mark
op_mod
l_int|10
op_plus
l_char|&squot;0&squot;
suffix:semicolon
id|mark
op_div_assign
l_int|10
suffix:semicolon
op_star
id|s
op_decrement
op_assign
id|mark
op_mod
l_int|10
op_plus
l_char|&squot;0&squot;
suffix:semicolon
)brace
eof