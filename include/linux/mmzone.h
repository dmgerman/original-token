macro_line|#ifndef _LINUX_MMZONE_H
DECL|macro|_LINUX_MMZONE_H
mdefine_line|#define _LINUX_MMZONE_H
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/list.h&gt;
multiline_comment|/*&n; * Free memory management - zoned buddy allocator.&n; */
DECL|macro|MAX_ORDER
mdefine_line|#define MAX_ORDER 10
DECL|struct|free_area_struct
r_typedef
r_struct
id|free_area_struct
(brace
DECL|member|free_list
r_struct
id|list_head
id|free_list
suffix:semicolon
DECL|member|map
r_int
r_int
op_star
id|map
suffix:semicolon
DECL|typedef|free_area_t
)brace
id|free_area_t
suffix:semicolon
r_struct
id|pglist_data
suffix:semicolon
DECL|struct|zone_struct
r_typedef
r_struct
id|zone_struct
(brace
multiline_comment|/*&n;&t; * Commonly accessed fields:&n;&t; */
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|free_pages
r_int
r_int
id|free_pages
suffix:semicolon
DECL|member|low_on_memory
r_int
id|low_on_memory
suffix:semicolon
DECL|member|pages_min
DECL|member|pages_low
DECL|member|pages_high
r_int
r_int
id|pages_min
comma
id|pages_low
comma
id|pages_high
suffix:semicolon
DECL|member|zone_pgdat
r_struct
id|pglist_data
op_star
id|zone_pgdat
suffix:semicolon
multiline_comment|/*&n;&t; * free areas of different sizes&n;&t; */
DECL|member|free_area
id|free_area_t
id|free_area
(braket
id|MAX_ORDER
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * rarely used fields:&n;&t; */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|typedef|zone_t
)brace
id|zone_t
suffix:semicolon
DECL|macro|ZONE_DMA
mdefine_line|#define ZONE_DMA&t;&t;0
DECL|macro|ZONE_NORMAL
mdefine_line|#define ZONE_NORMAL&t;&t;1
DECL|macro|ZONE_HIGHMEM
mdefine_line|#define ZONE_HIGHMEM&t;&t;2
DECL|macro|MAX_NR_ZONES
mdefine_line|#define MAX_NR_ZONES&t;&t;3
multiline_comment|/*&n; * One allocation request operates on a zonelist. A zonelist&n; * is a list of zones, the first one is the &squot;goal&squot; of the&n; * allocation, the other zones are fallback zones, in decreasing&n; * priority.&n; *&n; * Right now a zonelist takes up less than a cacheline. We never&n; * modify it apart from boot-up, and only a few indices are used,&n; * so despite the zonelist table being relatively big, the cache&n; * footprint of this construct is very small.&n; */
DECL|struct|zonelist_struct
r_typedef
r_struct
id|zonelist_struct
(brace
DECL|member|zones
id|zone_t
op_star
id|zones
(braket
id|MAX_NR_ZONES
op_plus
l_int|1
)braket
suffix:semicolon
singleline_comment|// NULL delimited
DECL|member|gfp_mask
r_int
id|gfp_mask
suffix:semicolon
DECL|typedef|zonelist_t
)brace
id|zonelist_t
suffix:semicolon
DECL|macro|NR_GFPINDEX
mdefine_line|#define NR_GFPINDEX&t;&t;0x100
r_struct
id|bootmem_data
suffix:semicolon
DECL|struct|pglist_data
r_typedef
r_struct
id|pglist_data
(brace
DECL|member|node_zones
id|zone_t
id|node_zones
(braket
id|MAX_NR_ZONES
)braket
suffix:semicolon
DECL|member|node_zonelists
id|zonelist_t
id|node_zonelists
(braket
id|NR_GFPINDEX
)braket
suffix:semicolon
DECL|member|node_mem_map
r_struct
id|page
op_star
id|node_mem_map
suffix:semicolon
DECL|member|valid_addr_bitmap
r_int
r_int
op_star
id|valid_addr_bitmap
suffix:semicolon
DECL|member|bdata
r_struct
id|bootmem_data
op_star
id|bdata
suffix:semicolon
DECL|typedef|pg_data_t
)brace
id|pg_data_t
suffix:semicolon
r_extern
r_int
id|numnodes
suffix:semicolon
DECL|macro|memclass
mdefine_line|#define memclass(pgzone, tzone)&t;(((pgzone)-&gt;zone_pgdat == (tzone)-&gt;zone_pgdat) &bslash;&n;&t;&t;&t;&amp;&amp; (((pgzone) - (pgzone)-&gt;zone_pgdat-&gt;node_zones) &lt;= &bslash;&n;&t;&t;&t;((tzone) - (pgzone)-&gt;zone_pgdat-&gt;node_zones)))
macro_line|#ifndef CONFIG_DISCONTIGMEM
r_extern
id|pg_data_t
id|contig_page_data
suffix:semicolon
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(nid)&t;&t;(&amp;contig_page_data)
DECL|macro|NODE_MEM_MAP
mdefine_line|#define NODE_MEM_MAP(nid)&t;mem_map
macro_line|#else /* !CONFIG_DISCONTIGMEM */
macro_line|#include &lt;asm/mmzone.h&gt;
macro_line|#endif /* !CONFIG_DISCONTIGMEM */
DECL|macro|MAP_ALIGN
mdefine_line|#define MAP_ALIGN(x)&t;((((x) % sizeof(mem_map_t)) == 0) ? (x) : ((x) + &bslash;&n;&t;&t;sizeof(mem_map_t) - ((x) % sizeof(mem_map_t))))
macro_line|#ifdef CONFIG_DISCONTIGMEM
DECL|macro|LOCAL_MAP_NR
mdefine_line|#define LOCAL_MAP_NR(kvaddr) &bslash;&n;&t;(((unsigned long)(kvaddr)-LOCAL_BASE_ADDR((kvaddr))) &gt;&gt; PAGE_SHIFT)
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(kaddr)&t;(LOCAL_MAP_NR((kaddr)) + &bslash;&n;&t;&t;(((unsigned long)ADDR_TO_MAPBASE((kaddr)) - PAGE_OFFSET) / &bslash;&n;&t;&t;sizeof(mem_map_t)))
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;((KVADDR_TO_NID((unsigned long)addr) &gt;= &bslash;&n;&t;numnodes) ? 0 : (test_bit(LOCAL_MAP_NR((addr)), &bslash;&n;&t;NODE_DATA(KVADDR_TO_NID((unsigned long)addr))-&gt;valid_addr_bitmap)))
macro_line|#endif /* CONFIG_DISCONTIGMEM */
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_MMZONE_H */
eof
