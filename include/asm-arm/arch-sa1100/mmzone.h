multiline_comment|/*&n; * linux/include/asm-arm/arch-sa1100/mmzone.h&n; *&n; * (C) 1999-2000, Nicolas Pitre &lt;nico@cam.org&gt;&n; * (inspired by Kanoj Sarcar&squot;s code)&n; *&n; * Because of the wide memory address space between physical RAM banks on the &n; * SA1100, it&squot;s much convenient to use Linux&squot;s NUMA support to implement our &n; * memory map representation.  Assuming all memory nodes have equal access &n; * characteristics, we then have generic discontigous memory support.&n; *&n; * Of course, all this isn&squot;t mandatory for SA1100 implementations with only&n; * one used memory bank.  For those, simply undefine CONFIG_DISCONTIGMEM.&n; */
multiline_comment|/*&n; * Currently defined in arch/arm/mm/mm-sa1100.c&n; */
r_extern
id|pg_data_t
id|sa1100_node_data
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * 32MB max in each bank, must fit with __virt_to_phys() &amp; __phys_to_virt()&n; */
DECL|macro|NODE_MAX_MEM_SHIFT
mdefine_line|#define NODE_MAX_MEM_SHIFT&t;25
DECL|macro|NODE_MAX_MEM_SIZE
mdefine_line|#define NODE_MAX_MEM_SIZE&t;(1&lt;&lt;NODE_MAX_MEM_SHIFT)
multiline_comment|/*&n; * Given a kernel address, find the home node of the underlying memory.&n; */
DECL|macro|KVADDR_TO_NID
mdefine_line|#define KVADDR_TO_NID(addr) &bslash;&n;&t;&t;(((unsigned long)(addr) - PAGE_OFFSET) &gt;&gt; NODE_MAX_MEM_SHIFT)
multiline_comment|/*&n; * Return a pointer to the node data for node n.&n; */
DECL|macro|NODE_DATA
mdefine_line|#define NODE_DATA(nid)&t;(&amp;sa1100_node_data[nid])
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
multiline_comment|/*&n; * Given a kaddr, LOCAL_MEM_MAP finds the owning node of the memory&n; * and returns the index corresponding to the appropriate page in the&n; * node&squot;s mem_map.&n; */
DECL|macro|LOCAL_MAP_NR
mdefine_line|#define LOCAL_MAP_NR(kvaddr) &bslash;&n;&t;(((unsigned long)(kvaddr)-LOCAL_BASE_ADDR((kvaddr))) &gt;&gt; PAGE_SHIFT)
multiline_comment|/* &n; * With discontigmem, the conceptual mem_map array starts from PAGE_OFFSET.&n; * Given a kaddr, MAP_NR returns the appropriate global mem_map index so &n; * it matches the corresponding node&squot;s local mem_map.&n; */
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(kaddr)&t;(LOCAL_MAP_NR((kaddr)) + &bslash;&n;&t;&t;(((unsigned long)ADDR_TO_MAPBASE((kaddr)) - PAGE_OFFSET) / &bslash;&n;&t;&t;sizeof(mem_map_t)))
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(kaddr)&t;(mem_map + MAP_NR(kaddr))
DECL|macro|VALID_PAGE
mdefine_line|#define VALID_PAGE(page)&t;((page - mem_map) &lt; max_mapnr)
eof
