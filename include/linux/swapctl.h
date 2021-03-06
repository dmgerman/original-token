macro_line|#ifndef _LINUX_SWAPCTL_H
DECL|macro|_LINUX_SWAPCTL_H
mdefine_line|#define _LINUX_SWAPCTL_H
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
DECL|struct|buffer_mem_v1
r_typedef
r_struct
id|buffer_mem_v1
(brace
DECL|member|min_percent
r_int
r_int
id|min_percent
suffix:semicolon
DECL|member|borrow_percent
r_int
r_int
id|borrow_percent
suffix:semicolon
DECL|member|max_percent
r_int
r_int
id|max_percent
suffix:semicolon
DECL|typedef|buffer_mem_v1
)brace
id|buffer_mem_v1
suffix:semicolon
DECL|typedef|buffer_mem_t
r_typedef
id|buffer_mem_v1
id|buffer_mem_t
suffix:semicolon
r_extern
id|buffer_mem_t
id|buffer_mem
suffix:semicolon
r_extern
id|buffer_mem_t
id|page_cache
suffix:semicolon
DECL|struct|freepages_v1
r_typedef
r_struct
id|freepages_v1
(brace
DECL|member|min
r_int
r_int
id|min
suffix:semicolon
DECL|member|low
r_int
r_int
id|low
suffix:semicolon
DECL|member|high
r_int
r_int
id|high
suffix:semicolon
DECL|typedef|freepages_v1
)brace
id|freepages_v1
suffix:semicolon
DECL|typedef|freepages_t
r_typedef
id|freepages_v1
id|freepages_t
suffix:semicolon
r_extern
id|freepages_t
id|freepages
suffix:semicolon
DECL|struct|pager_daemon_v1
r_typedef
r_struct
id|pager_daemon_v1
(brace
DECL|member|tries_base
r_int
r_int
id|tries_base
suffix:semicolon
DECL|member|tries_min
r_int
r_int
id|tries_min
suffix:semicolon
DECL|member|swap_cluster
r_int
r_int
id|swap_cluster
suffix:semicolon
DECL|typedef|pager_daemon_v1
)brace
id|pager_daemon_v1
suffix:semicolon
DECL|typedef|pager_daemon_t
r_typedef
id|pager_daemon_v1
id|pager_daemon_t
suffix:semicolon
r_extern
id|pager_daemon_t
id|pager_daemon
suffix:semicolon
macro_line|#endif /* _LINUX_SWAPCTL_H */
eof
