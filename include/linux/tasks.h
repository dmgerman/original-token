macro_line|#ifndef _LINUX_TASKS_H
DECL|macro|_LINUX_TASKS_H
mdefine_line|#define _LINUX_TASKS_H
multiline_comment|/*&n; * This is the maximum nr of tasks - change it if you need to&n; */
macro_line|#ifdef CONFIG_SMP
DECL|macro|NR_CPUS
mdefine_line|#define NR_CPUS&t;32&t;&t;/* Max processors that can be running in SMP */
macro_line|#else
DECL|macro|NR_CPUS
mdefine_line|#define NR_CPUS 1
macro_line|#endif
DECL|macro|NR_TASKS
mdefine_line|#define NR_TASKS&t;512
DECL|macro|MAX_TASKS_PER_USER
mdefine_line|#define MAX_TASKS_PER_USER (NR_TASKS/2)
DECL|macro|MIN_TASKS_LEFT_FOR_ROOT
mdefine_line|#define MIN_TASKS_LEFT_FOR_ROOT 4
macro_line|#endif
eof
