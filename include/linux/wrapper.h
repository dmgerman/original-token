macro_line|#ifndef _WRAPPER_H_
DECL|macro|_WRAPPER_H_
mdefine_line|#define _WRAPPER_H_
DECL|macro|vma_set_inode
mdefine_line|#define vma_set_inode(v,i)&t;((v)-&gt;vm_inode = (i))
DECL|macro|vma_get_flags
mdefine_line|#define vma_get_flags(v)&t;((v)-&gt;vm_flags)
DECL|macro|vma_get_pgoff
mdefine_line|#define vma_get_pgoff(v)&t;((v)-&gt;vm_pgoff)
DECL|macro|vma_get_start
mdefine_line|#define vma_get_start(v)&t;((v)-&gt;vm_start)
DECL|macro|vma_get_end
mdefine_line|#define vma_get_end(v)&t;&t;((v)-&gt;vm_end)
DECL|macro|vma_get_page_prot
mdefine_line|#define vma_get_page_prot(v)&t;((v)-&gt;vm_page_prot)
DECL|macro|mem_map_reserve
mdefine_line|#define mem_map_reserve(p)&t;set_bit(PG_reserved, &amp;((p)-&gt;flags))
DECL|macro|mem_map_unreserve
mdefine_line|#define mem_map_unreserve(p)&t;clear_bit(PG_reserved, &amp;((p)-&gt;flags))
macro_line|#endif /* _WRAPPER_H_ */
eof
