macro_line|#ifndef _WRAPPER_H_
DECL|macro|_WRAPPER_H_
mdefine_line|#define _WRAPPER_H_
DECL|macro|wait_handle
mdefine_line|#define wait_handle struct wait_queue
DECL|macro|file_handle
mdefine_line|#define file_handle struct file
DECL|macro|inode_handle
mdefine_line|#define inode_handle struct inode
DECL|macro|select_table_handle
mdefine_line|#define select_table_handle select_table
DECL|macro|vm_area_handle
mdefine_line|#define vm_area_handle struct vm_area_struct
DECL|macro|connect_wrapper
mdefine_line|#define connect_wrapper(x) 0
DECL|macro|current_got_fatal_signal
mdefine_line|#define current_got_fatal_signal() (signal_pending(current))
DECL|macro|current_set_timeout
mdefine_line|#define current_set_timeout(val) current-&gt;timeout = val
DECL|macro|module_interruptible_sleep_on
mdefine_line|#define module_interruptible_sleep_on interruptible_sleep_on
DECL|macro|module_wake_up
mdefine_line|#define module_wake_up wake_up
DECL|macro|module_select_wait
mdefine_line|#define module_select_wait select_wait
DECL|macro|module_register_chrdev
mdefine_line|#define module_register_chrdev register_chrdev
DECL|macro|module_unregister_chrdev
mdefine_line|#define module_unregister_chrdev unregister_chrdev
DECL|macro|module_register_blkdev
mdefine_line|#define module_register_blkdev register_blkdev
DECL|macro|module_unregister_blkdev
mdefine_line|#define module_unregister_blkdev unregister_blkdev
DECL|macro|inode_get_rdev
mdefine_line|#define inode_get_rdev(i) i-&gt;i_rdev
DECL|macro|inode_get_count
mdefine_line|#define inode_get_count(i) i-&gt;i_count
DECL|macro|inode_inc_count
mdefine_line|#define inode_inc_count(i) i-&gt;i_count++
DECL|macro|inode_dec_count
mdefine_line|#define inode_dec_count(i) i-&gt;i_count--
DECL|macro|file_get_flags
mdefine_line|#define file_get_flags(f) f-&gt;f_flags
DECL|macro|vma_set_inode
mdefine_line|#define vma_set_inode(v,i) v-&gt;vm_inode = i
DECL|macro|vma_get_flags
mdefine_line|#define vma_get_flags(v) v-&gt;vm_flags
DECL|macro|vma_get_pgoff
mdefine_line|#define vma_get_pgoff(v) v-&gt;vm_pgoff
DECL|macro|vma_get_start
mdefine_line|#define vma_get_start(v) v-&gt;vm_start
DECL|macro|vma_get_end
mdefine_line|#define vma_get_end(v) v-&gt;vm_end
DECL|macro|vma_get_page_prot
mdefine_line|#define vma_get_page_prot(v) v-&gt;vm_page_prot
DECL|macro|mem_map_reserve
mdefine_line|#define mem_map_reserve(p) set_bit(PG_reserved, &amp;mem_map[p].flags)
DECL|macro|mem_map_unreserve
mdefine_line|#define mem_map_unreserve(p) clear_bit(PG_reserved, &amp;mem_map[p].flags)
DECL|macro|mem_map_inc_count
mdefine_line|#define mem_map_inc_count(p) atomic_inc(&amp;(mem_map[p].count))
DECL|macro|mem_map_dec_count
mdefine_line|#define mem_map_dec_count(p) atomic_dec(&amp;(mem_map[p].count))
macro_line|#endif
eof
