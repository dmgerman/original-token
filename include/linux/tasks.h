macro_line|#ifndef _LINUX_TASKS_H
DECL|macro|_LINUX_TASKS_H
mdefine_line|#define _LINUX_TASKS_H
multiline_comment|/*&n; * This is the maximum nr of tasks - change it if you need to&n; */
DECL|macro|NR_TASKS
mdefine_line|#define NR_TASKS&t;512
DECL|macro|MAX_TASKS_PER_USER
mdefine_line|#define MAX_TASKS_PER_USER (NR_TASKS/2)
DECL|macro|MIN_TASKS_LEFT_FOR_ROOT
mdefine_line|#define MIN_TASKS_LEFT_FOR_ROOT 4
macro_line|#endif
eof
