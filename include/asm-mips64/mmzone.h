multiline_comment|/*&n; * Written by Kanoj Sarcar (kanoj@sgi.com) Aug 99&n; */
macro_line|#ifndef _ASM_MMZONE_H_
DECL|macro|_ASM_MMZONE_H_
mdefine_line|#define _ASM_MMZONE_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
DECL|struct|plat_pglist_data
r_typedef
r_struct
id|plat_pglist_data
(brace
DECL|member|gendata
id|pg_data_t
id|gendata
suffix:semicolon
DECL|member|physstart
r_int
r_int
id|physstart
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|start_mapnr
r_int
r_int
id|start_mapnr
suffix:semicolon
DECL|typedef|plat_pg_data_t
)brace
id|plat_pg_data_t
suffix:semicolon
multiline_comment|/*&n; * Following are macros that are specific to this numa platform.&n; */
r_extern
r_int
id|numa_debug
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|plat_pg_data_t
op_star
id|plat_node_data
(braket
)braket
suffix:semicolon
DECL|macro|PHYSADDR_TO_NID
mdefine_line|#define PHYSADDR_TO_NID(pa)&t;&t;NASID_TO_COMPACT_NODEID(NASID_GET(pa))
DECL|macro|PLAT_NODE_DATA
mdefine_line|#define PLAT_NODE_DATA(n)&t;&t;(plat_node_data[n])
DECL|macro|PLAT_NODE_DATA_STARTNR
mdefine_line|#define PLAT_NODE_DATA_STARTNR(n)&t;(PLAT_NODE_DATA(n)-&gt;start_mapnr)
DECL|macro|PLAT_NODE_DATA_LOCALNR
mdefine_line|#define PLAT_NODE_DATA_LOCALNR(p, n) &bslash;&n;&t;&t;&t;(((p) - PLAT_NODE_DATA(n)-&gt;physstart) &gt;&gt; PAGE_SHIFT)
DECL|macro|PAGE_TO_PLAT_NODE
mdefine_line|#define PAGE_TO_PLAT_NODE(p)&t;&t;(plat_pg_data_t *)((p)-&gt;zone-&gt;zone_pgdat)
macro_line|#ifdef CONFIG_DISCONTIGMEM
multiline_comment|/*&n; * Following are macros that each numa implmentation must define.&n; */
multiline_comment|/*&n; * Given a kernel address, find the home node of the underlying memory.&n; * For production kern_addr_valid, change to return &quot;numnodes&quot; instead&n; * of panicing.&n; */
DECL|macro|KVADDR_TO_NID
mdefine_line|#define KVADDR_TO_NID(kaddr) &bslash;&n;&t;((NASID_TO_COMPACT_NODEID(NASID_GET(__pa(kaddr))) != -1) ? &bslash;&n;&t;(NASID_TO_COMPACT_NODEID(NASID_GET(__pa(kaddr)))) : &bslash;&n;&t;(printk(&quot;NUMABUG: %s line %d addr 0x%lx&quot;, __FILE__, __LINE__, kaddr), &bslash;&n;&t;numa_debug(), -1))
multiline_comment|/*&n; * Return a pointer to the node data for node n.&n; */
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(n)&t;(&amp;((PLAT_NODE_DATA(n))-&gt;gendata))
multiline_comment|/*&n; * NODE_MEM_MAP gives the kaddr for the mem_map of the node.&n; */
DECL|macro|NODE_MEM_MAP
mdefine_line|#define NODE_MEM_MAP(nid)&t;(NODE_DATA(nid)-&gt;node_mem_map)
multiline_comment|/*&n; * Given a mem_map_t, LOCAL_MAP_BASE finds the owning node for the&n; * physical page and returns the kaddr for the mem_map of that node.&n; */
DECL|macro|LOCAL_MAP_BASE
mdefine_line|#define LOCAL_MAP_BASE(page) &bslash;&n;&t;&t;&t;NODE_MEM_MAP(KVADDR_TO_NID((unsigned long)(page)))
multiline_comment|/*&n; * Given a kaddr, ADDR_TO_MAPBASE finds the owning node of the memory&n; * and returns the the mem_map of that node.&n; */
DECL|macro|ADDR_TO_MAPBASE
mdefine_line|#define ADDR_TO_MAPBASE(kaddr) &bslash;&n;&t;&t;&t;NODE_MEM_MAP(KVADDR_TO_NID((unsigned long)(kaddr)))
multiline_comment|/*&n; * Given a kaddr, LOCAL_BASE_ADDR finds the owning node of the memory&n; * and returns the kaddr corresponding to first physical page in the&n; * node&squot;s mem_map.&n; */
DECL|macro|LOCAL_BASE_ADDR
mdefine_line|#define LOCAL_BASE_ADDR(kaddr)&t;((unsigned long)(kaddr) &amp; ~(NODE_MAX_MEM_SIZE-1))
macro_line|#endif /* CONFIG_DISCONTIGMEM */
macro_line|#endif /* _ASM_MMZONE_H_ */
eof
