macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/* forward-declare task_struct */
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/*&n; * Don&squot;t change this structure - ASM code&n; * relies on it.&n; */
DECL|struct|processor
r_extern
r_struct
id|processor
(brace
multiline_comment|/* MISC&n;&t; * get data abort address/flags&n;&t; */
DECL|member|_data_abort
r_void
(paren
op_star
id|_data_abort
)paren
(paren
r_int
r_int
id|pc
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * check for any bugs&n;&t; */
DECL|member|_check_bugs
r_void
(paren
op_star
id|_check_bugs
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set up any processor specifics&n;&t; */
DECL|member|_proc_init
r_void
(paren
op_star
id|_proc_init
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Disable any processor specifics&n;&t; */
DECL|member|_proc_fin
r_void
(paren
op_star
id|_proc_fin
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Processor architecture specific&n;&t; */
multiline_comment|/* MEMC&n;&t; *&n;&t; * remap memc tables&n;&t; */
DECL|member|_remap_memc
r_void
(paren
op_star
id|_remap_memc
)paren
(paren
r_void
op_star
id|tsk
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * update task&squot;s idea of mmap&n;&t; */
DECL|member|_update_map
r_void
(paren
op_star
id|_update_map
)paren
(paren
r_void
op_star
id|tsk
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * update task&squot;s idea after abort&n;&t; */
DECL|member|_update_mmu_cache
r_void
(paren
op_star
id|_update_mmu_cache
)paren
(paren
r_void
op_star
id|vma
comma
r_int
r_int
id|addr
comma
id|pte_t
id|pte
)paren
suffix:semicolon
multiline_comment|/* XCHG&n;&t; */
DECL|member|_xchg_1
r_int
r_int
(paren
op_star
id|_xchg_1
)paren
(paren
r_int
r_int
id|x
comma
r_volatile
r_void
op_star
id|ptr
)paren
suffix:semicolon
DECL|member|_xchg_2
r_int
r_int
(paren
op_star
id|_xchg_2
)paren
(paren
r_int
r_int
id|x
comma
r_volatile
r_void
op_star
id|ptr
)paren
suffix:semicolon
DECL|member|_xchg_4
r_int
r_int
(paren
op_star
id|_xchg_4
)paren
(paren
r_int
r_int
id|x
comma
r_volatile
r_void
op_star
id|ptr
)paren
suffix:semicolon
)brace
id|processor
suffix:semicolon
r_extern
r_const
r_struct
id|processor
id|arm2_processor_functions
suffix:semicolon
r_extern
r_const
r_struct
id|processor
id|arm250_processor_functions
suffix:semicolon
r_extern
r_const
r_struct
id|processor
id|arm3_processor_functions
suffix:semicolon
DECL|macro|cpu_data_abort
mdefine_line|#define cpu_data_abort(pc)&t;&t;&t;processor._data_abort(pc)
DECL|macro|cpu_check_bugs
mdefine_line|#define cpu_check_bugs()&t;&t;&t;processor._check_bugs()
DECL|macro|cpu_proc_init
mdefine_line|#define cpu_proc_init()&t;&t;&t;&t;processor._proc_init()
DECL|macro|cpu_proc_fin
mdefine_line|#define cpu_proc_fin()&t;&t;&t;&t;processor._proc_fin()
DECL|macro|cpu_remap_memc
mdefine_line|#define cpu_remap_memc(tsk)&t;&t;&t;processor._remap_memc(tsk)
DECL|macro|cpu_update_map
mdefine_line|#define cpu_update_map(tsk)&t;&t;&t;processor._update_map(tsk)
DECL|macro|cpu_update_mmu_cache
mdefine_line|#define cpu_update_mmu_cache(vma,addr,pte)&t;processor._update_mmu_cache(vma,addr,pte)
DECL|macro|cpu_xchg_1
mdefine_line|#define cpu_xchg_1(x,ptr)&t;&t;&t;processor._xchg_1(x,ptr)
DECL|macro|cpu_xchg_2
mdefine_line|#define cpu_xchg_2(x,ptr)&t;&t;&t;processor._xchg_2(x,ptr)
DECL|macro|cpu_xchg_4
mdefine_line|#define cpu_xchg_4(x,ptr)&t;&t;&t;processor._xchg_4(x,ptr)
macro_line|#endif
eof
