multiline_comment|/* isdn_budget.h&n; *&n; * Linux ISDN subsystem, budget-accounting for network interfaces.&n; *&n; * Copyright 1997       by Christian Lademann &lt;cal@zls.de&gt;&n; * &n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n; *&n; */
multiline_comment|/*&n;30.06.97:cal:angelegt&n;04.11.97:cal:budget.period: int --&gt; time_t&n;*/
macro_line|#ifndef __isdn_budget_h__
DECL|macro|__isdn_budget_h__
mdefine_line|#define __isdn_budget_h__
macro_line|#include&t;&lt;linux/types.h&gt;
DECL|macro|ISDN_BUDGET_DIAL
mdefine_line|#define&t;ISDN_BUDGET_DIAL&t;&t;0
DECL|macro|ISDN_BUDGET_CHARGE
mdefine_line|#define&t;ISDN_BUDGET_CHARGE&t;&t;1
DECL|macro|ISDN_BUDGET_ONLINE
mdefine_line|#define&t;ISDN_BUDGET_ONLINE&t;&t;2
DECL|macro|ISDN_BUDGET_NUM_BUDGET
mdefine_line|#define&t;ISDN_BUDGET_NUM_BUDGET&t;&t;3
DECL|macro|ISDN_BUDGET_INIT
mdefine_line|#define&t;ISDN_BUDGET_INIT&t;&t;0
DECL|macro|ISDN_BUDGET_CHECK_DIAL
mdefine_line|#define&t;ISDN_BUDGET_CHECK_DIAL&t;&t;1
DECL|macro|ISDN_BUDGET_CHECK_CHARGE
mdefine_line|#define&t;ISDN_BUDGET_CHECK_CHARGE&t;2
DECL|macro|ISDN_BUDGET_CHECK_ONLINE
mdefine_line|#define&t;ISDN_BUDGET_CHECK_ONLINE&t;3
DECL|macro|ISDN_BUDGET_START_ONLINE
mdefine_line|#define&t;ISDN_BUDGET_START_ONLINE&t;10
DECL|macro|ISDN_BUDGET_SET_BUDGET
mdefine_line|#define&t;ISDN_BUDGET_SET_BUDGET&t;0
DECL|macro|ISDN_BUDGET_GET_BUDGET
mdefine_line|#define&t;ISDN_BUDGET_GET_BUDGET&t;1
r_typedef
r_struct
(brace
DECL|member|name
r_char
id|name
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* Interface */
DECL|member|command
r_int
id|command
comma
multiline_comment|/* subcommand */
DECL|member|budget
id|budget
comma
multiline_comment|/* budget-nr. */
DECL|member|amount
id|amount
comma
multiline_comment|/* set/get budget-amount */
DECL|member|used
id|used
suffix:semicolon
multiline_comment|/* set/get used amount */
DECL|member|period
id|time_t
id|period
comma
multiline_comment|/* set/get length of period */
DECL|member|period_started
id|period_started
suffix:semicolon
multiline_comment|/* set/get startpoint of period */
DECL|typedef|isdn_ioctl_budget
)brace
id|isdn_ioctl_budget
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|isdn_net_budget
c_func
(paren
r_int
comma
r_struct
id|device
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_budget_ioctl
c_func
(paren
id|isdn_ioctl_budget
op_star
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __isdn_budget_h__ */
eof
