macro_line|#ifndef _LINUX_SWAP_H
DECL|macro|_LINUX_SWAP_H
mdefine_line|#define _LINUX_SWAP_H
DECL|macro|SWAP_FLAG_PREFER
mdefine_line|#define SWAP_FLAG_PREFER&t;0x8000&t;/* set if swap priority specified */
DECL|macro|SWAP_FLAG_PRIO_MASK
mdefine_line|#define SWAP_FLAG_PRIO_MASK&t;0x7fff
DECL|macro|SWAP_FLAG_PRIO_SHIFT
mdefine_line|#define SWAP_FLAG_PRIO_SHIFT&t;0
DECL|macro|MAX_SWAPFILES
mdefine_line|#define MAX_SWAPFILES 8
macro_line|#ifdef __KERNEL__
DECL|macro|SWP_USED
mdefine_line|#define SWP_USED&t;1
DECL|macro|SWP_WRITEOK
mdefine_line|#define SWP_WRITEOK&t;3
DECL|macro|SWAP_CLUSTER_MAX
mdefine_line|#define SWAP_CLUSTER_MAX 32
DECL|struct|swap_info_struct
r_struct
id|swap_info_struct
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|swap_device
id|kdev_t
id|swap_device
suffix:semicolon
DECL|member|swap_file
r_struct
id|inode
op_star
id|swap_file
suffix:semicolon
DECL|member|swap_map
r_int
r_char
op_star
id|swap_map
suffix:semicolon
DECL|member|swap_lockmap
r_int
r_char
op_star
id|swap_lockmap
suffix:semicolon
DECL|member|lowest_bit
r_int
id|lowest_bit
suffix:semicolon
DECL|member|highest_bit
r_int
id|highest_bit
suffix:semicolon
DECL|member|cluster_next
r_int
id|cluster_next
suffix:semicolon
DECL|member|cluster_nr
r_int
id|cluster_nr
suffix:semicolon
DECL|member|prio
r_int
id|prio
suffix:semicolon
multiline_comment|/* swap priority */
DECL|member|pages
r_int
id|pages
suffix:semicolon
DECL|member|max
r_int
r_int
id|max
suffix:semicolon
DECL|member|next
r_int
id|next
suffix:semicolon
multiline_comment|/* next entry on swap list */
)brace
suffix:semicolon
r_extern
r_int
id|nr_swap_pages
suffix:semicolon
r_extern
r_int
id|nr_free_pages
suffix:semicolon
r_extern
r_int
id|nr_async_pages
suffix:semicolon
r_extern
r_int
id|min_free_pages
suffix:semicolon
r_extern
r_int
id|free_pages_low
suffix:semicolon
r_extern
r_int
id|free_pages_high
suffix:semicolon
multiline_comment|/* Incomplete types for prototype declarations: */
r_struct
id|task_struct
suffix:semicolon
r_struct
id|vm_area_struct
suffix:semicolon
r_struct
id|sysinfo
suffix:semicolon
multiline_comment|/* linux/ipc/shm.c */
r_extern
r_int
id|shm_swap
(paren
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* linux/mm/vmscan.c */
r_extern
r_int
id|try_to_free_page
c_func
(paren
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* linux/mm/page_io.c */
r_extern
r_void
id|rw_swap_page
c_func
(paren
r_int
comma
r_int
r_int
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|macro|read_swap_page
mdefine_line|#define read_swap_page(nr,buf) &bslash;&n;&t;rw_swap_page(READ,(nr),(buf),1)
DECL|macro|write_swap_page
mdefine_line|#define write_swap_page(nr,buf) &bslash;&n;&t;rw_swap_page(WRITE,(nr),(buf),1)
r_extern
r_void
id|swap_after_unlock_page
(paren
r_int
r_int
id|entry
)paren
suffix:semicolon
multiline_comment|/* linux/mm/page_alloc.c */
r_extern
r_void
id|swap_in
c_func
(paren
r_struct
id|task_struct
op_star
comma
r_struct
id|vm_area_struct
op_star
comma
id|pte_t
op_star
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* linux/mm/swap_state.c */
r_extern
r_void
id|show_swap_cache_info
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|add_to_swap_cache
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|init_swap_cache
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|swap_duplicate
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* linux/mm/swapfile.c */
r_extern
r_int
id|nr_swapfiles
suffix:semicolon
r_extern
r_struct
id|swap_info_struct
id|swap_info
(braket
)braket
suffix:semicolon
r_void
id|si_swapinfo
c_func
(paren
r_struct
id|sysinfo
op_star
)paren
suffix:semicolon
r_int
r_int
id|get_swap_page
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|swap_free
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * vm_ops not present page codes for shared memory.&n; *&n; * Will go away eventually..&n; */
DECL|macro|SHM_SWP_TYPE
mdefine_line|#define SHM_SWP_TYPE 0x40
multiline_comment|/*&n; * swap cache stuff (in linux/mm/swap_state.c)&n; */
DECL|macro|SWAP_CACHE_INFO
mdefine_line|#define SWAP_CACHE_INFO
r_extern
r_int
r_int
op_star
id|swap_cache
suffix:semicolon
macro_line|#ifdef SWAP_CACHE_INFO
r_extern
r_int
r_int
id|swap_cache_add_total
suffix:semicolon
r_extern
r_int
r_int
id|swap_cache_add_success
suffix:semicolon
r_extern
r_int
r_int
id|swap_cache_del_total
suffix:semicolon
r_extern
r_int
r_int
id|swap_cache_del_success
suffix:semicolon
r_extern
r_int
r_int
id|swap_cache_find_total
suffix:semicolon
r_extern
r_int
r_int
id|swap_cache_find_success
suffix:semicolon
macro_line|#endif
DECL|function|in_swap_cache
r_extern
r_inline
r_int
r_int
id|in_swap_cache
c_func
(paren
r_int
r_int
id|index
)paren
(brace
r_return
id|swap_cache
(braket
id|index
)braket
suffix:semicolon
)brace
DECL|function|find_in_swap_cache
r_extern
r_inline
r_int
id|find_in_swap_cache
c_func
(paren
r_int
r_int
id|index
)paren
(brace
r_int
r_int
id|entry
suffix:semicolon
macro_line|#ifdef SWAP_CACHE_INFO
id|swap_cache_find_total
op_increment
suffix:semicolon
macro_line|#endif
id|entry
op_assign
id|xchg
c_func
(paren
id|swap_cache
op_plus
id|index
comma
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef SWAP_CACHE_INFO
r_if
c_cond
(paren
id|entry
)paren
id|swap_cache_find_success
op_increment
suffix:semicolon
macro_line|#endif&t;
r_return
id|entry
suffix:semicolon
)brace
DECL|function|delete_from_swap_cache
r_extern
r_inline
r_int
id|delete_from_swap_cache
c_func
(paren
r_int
r_int
id|index
)paren
(brace
r_int
r_int
id|entry
suffix:semicolon
macro_line|#ifdef SWAP_CACHE_INFO
id|swap_cache_del_total
op_increment
suffix:semicolon
macro_line|#endif&t;
id|entry
op_assign
id|xchg
c_func
(paren
id|swap_cache
op_plus
id|index
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
(brace
macro_line|#ifdef SWAP_CACHE_INFO
id|swap_cache_del_success
op_increment
suffix:semicolon
macro_line|#endif
id|swap_free
c_func
(paren
id|entry
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__*/
macro_line|#endif /* _LINUX_SWAP_H */
eof
