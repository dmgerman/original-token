macro_line|#ifndef __LINUX_PKT_SCHED_H
DECL|macro|__LINUX_PKT_SCHED_H
mdefine_line|#define __LINUX_PKT_SCHED_H
DECL|macro|PSCHED_TC_INIT
mdefine_line|#define PSCHED_TC_INIT&t;&t;1
DECL|macro|PSCHED_TC_DESTROY
mdefine_line|#define PSCHED_TC_DESTROY&t;2
DECL|macro|PSCHED_TC_ATTACH
mdefine_line|#define PSCHED_TC_ATTACH&t;3
DECL|macro|PSCHED_TC_DETACH
mdefine_line|#define PSCHED_TC_DETACH&t;4
multiline_comment|/* &quot;Logical&quot; priority bands, not depending of concrete packet scheduler.&n;   Every scheduler will map them to real traffic classes, if it have&n;   no more precise machanism.&n; */
DECL|macro|TC_PRIO_BESTEFFORT
mdefine_line|#define TC_PRIO_BESTEFFORT&t;&t;0
DECL|macro|TC_PRIO_FILLER
mdefine_line|#define TC_PRIO_FILLER&t;&t;&t;1
DECL|macro|TC_PRIO_BULK
mdefine_line|#define TC_PRIO_BULK&t;&t;&t;2
DECL|macro|TC_PRIO_INTERACTIVE_BULK
mdefine_line|#define TC_PRIO_INTERACTIVE_BULK&t;4
DECL|macro|TC_PRIO_INTERACTIVE
mdefine_line|#define TC_PRIO_INTERACTIVE&t;&t;6
DECL|macro|TC_PRIO_CONTROL
mdefine_line|#define TC_PRIO_CONTROL&t;&t;&t;7
DECL|struct|pschedctl
r_struct
id|pschedctl
(brace
DECL|member|command
r_int
id|command
suffix:semicolon
DECL|member|handle
r_int
id|handle
suffix:semicolon
DECL|member|child
r_int
id|child
suffix:semicolon
DECL|member|ifindex
r_int
id|ifindex
suffix:semicolon
DECL|member|id
r_char
id|id
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
DECL|member|arglen
r_int
id|arglen
suffix:semicolon
DECL|member|args
r_char
id|args
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* CBQ section */
DECL|macro|CBQ_MAXPRIO
mdefine_line|#define CBQ_MAXPRIO&t;8
DECL|macro|CBQ_MAXLEVEL
mdefine_line|#define CBQ_MAXLEVEL&t;8
multiline_comment|/* CSZ section */
DECL|struct|cszctl
r_struct
id|cszctl
(brace
DECL|member|flow_id
r_int
id|flow_id
suffix:semicolon
DECL|member|handle
r_int
id|handle
suffix:semicolon
DECL|member|rate
r_int
r_int
id|rate
suffix:semicolon
DECL|member|max_bytes
r_int
r_int
id|max_bytes
suffix:semicolon
DECL|member|depth
r_int
r_int
id|depth
suffix:semicolon
DECL|member|L_tab
r_int
r_int
id|L_tab
(braket
l_int|256
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cszinitctl
r_struct
id|cszinitctl
(brace
DECL|member|flows
r_int
id|flows
suffix:semicolon
DECL|member|cell_log
r_int
id|cell_log
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* TBF section */
DECL|struct|tbfctl
r_struct
id|tbfctl
(brace
DECL|member|cell_log
r_int
id|cell_log
suffix:semicolon
DECL|member|bytes
r_int
r_int
id|bytes
suffix:semicolon
DECL|member|depth
r_int
r_int
id|depth
suffix:semicolon
DECL|member|L_tab
r_int
r_int
id|L_tab
(braket
l_int|256
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* SFQ section */
DECL|struct|sfqctl
r_struct
id|sfqctl
(brace
DECL|member|quantum
r_int
id|quantum
suffix:semicolon
DECL|member|depth
r_int
id|depth
suffix:semicolon
DECL|member|divisor
r_int
id|divisor
suffix:semicolon
DECL|member|flows
r_int
id|flows
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* RED section */
DECL|struct|redctl
r_struct
id|redctl
(brace
DECL|member|qmaxbytes
r_int
id|qmaxbytes
suffix:semicolon
multiline_comment|/* HARD maximal queue length&t;*/
DECL|member|qth_min
r_int
id|qth_min
suffix:semicolon
multiline_comment|/* Min average length threshold: A scaled */
DECL|member|qth_max
r_int
id|qth_max
suffix:semicolon
multiline_comment|/* Max average length threshold: A scaled */
DECL|member|Alog
r_char
id|Alog
suffix:semicolon
multiline_comment|/* Point position in average lengths */
DECL|member|Wlog
r_char
id|Wlog
suffix:semicolon
multiline_comment|/* log(W)&t;&t;*/
DECL|member|Rlog
r_char
id|Rlog
suffix:semicolon
multiline_comment|/* random number bits&t;*/
DECL|member|C1log
r_char
id|C1log
suffix:semicolon
multiline_comment|/* log(1/C1)&t;&t;*/
DECL|member|Slog
r_char
id|Slog
suffix:semicolon
DECL|member|Stab
r_char
id|Stab
(braket
l_int|256
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
