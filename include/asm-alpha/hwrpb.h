macro_line|#ifndef _HWRPB_H
DECL|macro|_HWRPB_H
mdefine_line|#define _HWRPB_H
DECL|macro|INIT_HWRPB
mdefine_line|#define INIT_HWRPB ((struct hwrpb_struct *) 0x10000000)
multiline_comment|/*&n; * DEC processor types for Alpha systems.  Found in HWRPB.&n; * These values are architected.&n; */
DECL|macro|EV3_CPU
mdefine_line|#define EV3_CPU                 1       /* EV3                  */
DECL|macro|EV4_CPU
mdefine_line|#define EV4_CPU                 2       /* EV4 (21064)          */
DECL|macro|LCA4_CPU
mdefine_line|#define LCA4_CPU                4       /* LCA4 (21066/21068)   */
DECL|macro|EV5_CPU
mdefine_line|#define EV5_CPU                 5       /* EV5 (21164)          */
DECL|macro|EV45_CPU
mdefine_line|#define EV45_CPU                6       /* EV4.5 (21064/xxx)    */
multiline_comment|/*&n; * DEC system types for Alpha systems.  Found in HWRPB.&n; * These values are architected.&n; */
DECL|macro|ST_ADU
mdefine_line|#define ST_ADU&t;&t;&t;  1&t;/* Alpha ADU systype&t;*/
DECL|macro|ST_DEC_4000
mdefine_line|#define ST_DEC_4000&t;&t;  2&t;/* Cobra systype&t;*/
DECL|macro|ST_DEC_7000
mdefine_line|#define ST_DEC_7000&t;&t;  3&t;/* Ruby systype&t;&t;*/
DECL|macro|ST_DEC_3000_500
mdefine_line|#define ST_DEC_3000_500&t;&t;  4&t;/* Flamingo systype&t;*/
DECL|macro|ST_DEC_2000_300
mdefine_line|#define ST_DEC_2000_300&t;&t;  6&t;/* Jensen systype&t;*/
DECL|macro|ST_DEC_3000_300
mdefine_line|#define ST_DEC_3000_300&t;&t;  7&t;/* Pelican systype&t;*/
DECL|macro|ST_DEC_2100_A500
mdefine_line|#define ST_DEC_2100_A500&t;  9&t;/* Sable systype&t;*/
DECL|macro|ST_DEC_AXPVME_64
mdefine_line|#define ST_DEC_AXPVME_64&t; 10&t;/* AXPvme system type&t;*/
DECL|macro|ST_DEC_AXPPCI_33
mdefine_line|#define ST_DEC_AXPPCI_33&t; 11&t;/* NoName system type&t;*/
DECL|macro|ST_DEC_TLASER
mdefine_line|#define ST_DEC_TLASER&t;&t; 12&t;/* Turbolaser systype&t;*/
DECL|macro|ST_DEC_2100_A50
mdefine_line|#define ST_DEC_2100_A50&t;&t; 13&t;/* Avanti systype&t;*/
DECL|macro|ST_DEC_MUSTANG
mdefine_line|#define ST_DEC_MUSTANG&t;&t; 14&t;/* Mustang systype&t;*/
DECL|macro|ST_DEC_ALCOR
mdefine_line|#define ST_DEC_ALCOR&t;&t; 15&t;/* Alcor (EV5) systype&t;*/
DECL|macro|ST_DEC_1000
mdefine_line|#define ST_DEC_1000&t;&t; 17&t;/* Mikasa systype&t;*/
DECL|macro|ST_DEC_EB66
mdefine_line|#define ST_DEC_EB66&t;&t; 19&t;/* EB66 systype&t;&t;*/
DECL|macro|ST_DEC_EB64P
mdefine_line|#define ST_DEC_EB64P&t;&t; 20&t;/* EB64+ systype&t;*/
DECL|macro|ST_DEC_EB66P
mdefine_line|#define ST_DEC_EB66P&t;&t;-19&t;/* EB66 systype&t;&t;*/
DECL|macro|ST_DEC_EBPC64
mdefine_line|#define ST_DEC_EBPC64&t;&t;-20&t;/* Cabriolet (AlphaPC64) systype */
macro_line|#defien ST_DEC_EB164&t;&t; 26&t;/* EB164 systype&t;*/
DECL|struct|pcb_struct
r_struct
id|pcb_struct
(brace
DECL|member|ksp
r_int
r_int
id|ksp
suffix:semicolon
DECL|member|usp
r_int
r_int
id|usp
suffix:semicolon
DECL|member|ptbr
r_int
r_int
id|ptbr
suffix:semicolon
DECL|member|pcc
r_int
r_int
id|pcc
suffix:semicolon
DECL|member|asn
r_int
r_int
id|asn
suffix:semicolon
DECL|member|unique
r_int
r_int
id|unique
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|res1
DECL|member|res2
r_int
r_int
id|res1
comma
id|res2
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|percpu_struct
r_struct
id|percpu_struct
(brace
DECL|member|hwpcb
r_int
r_int
id|hwpcb
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|pal_mem_size
r_int
r_int
id|pal_mem_size
suffix:semicolon
DECL|member|pal_scratch_size
r_int
r_int
id|pal_scratch_size
suffix:semicolon
DECL|member|pal_mem_pa
r_int
r_int
id|pal_mem_pa
suffix:semicolon
DECL|member|pal_scratch_pa
r_int
r_int
id|pal_scratch_pa
suffix:semicolon
DECL|member|pal_revision
r_int
r_int
id|pal_revision
suffix:semicolon
DECL|member|type
r_int
r_int
id|type
suffix:semicolon
DECL|member|variation
r_int
r_int
id|variation
suffix:semicolon
DECL|member|revision
r_int
r_int
id|revision
suffix:semicolon
DECL|member|serial_no
r_int
r_int
id|serial_no
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|logout_area_pa
r_int
r_int
id|logout_area_pa
suffix:semicolon
DECL|member|logout_area_len
r_int
r_int
id|logout_area_len
suffix:semicolon
DECL|member|halt_PCBB
r_int
r_int
id|halt_PCBB
suffix:semicolon
DECL|member|halt_PC
r_int
r_int
id|halt_PC
suffix:semicolon
DECL|member|halt_PS
r_int
r_int
id|halt_PS
suffix:semicolon
DECL|member|halt_arg
r_int
r_int
id|halt_arg
suffix:semicolon
DECL|member|halt_ra
r_int
r_int
id|halt_ra
suffix:semicolon
DECL|member|halt_pv
r_int
r_int
id|halt_pv
suffix:semicolon
DECL|member|halt_reason
r_int
r_int
id|halt_reason
suffix:semicolon
DECL|member|res
r_int
r_int
id|res
suffix:semicolon
DECL|member|ipc_buffer
r_int
r_int
id|ipc_buffer
(braket
l_int|21
)braket
suffix:semicolon
DECL|member|palcode_avail
r_int
r_int
id|palcode_avail
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|compatibility
r_int
r_int
id|compatibility
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|procdesc_struct
r_struct
id|procdesc_struct
(brace
DECL|member|weird_vms_stuff
r_int
r_int
id|weird_vms_stuff
suffix:semicolon
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|vf_map_struct
r_struct
id|vf_map_struct
(brace
DECL|member|va
r_int
r_int
id|va
suffix:semicolon
DECL|member|pa
r_int
r_int
id|pa
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|crb_struct
r_struct
id|crb_struct
(brace
DECL|member|dispatch_va
r_struct
id|procdesc_struct
op_star
id|dispatch_va
suffix:semicolon
DECL|member|dispatch_pa
r_struct
id|procdesc_struct
op_star
id|dispatch_pa
suffix:semicolon
DECL|member|fixup_va
r_struct
id|procdesc_struct
op_star
id|fixup_va
suffix:semicolon
DECL|member|fixup_pa
r_struct
id|procdesc_struct
op_star
id|fixup_pa
suffix:semicolon
multiline_comment|/* virtual-&gt;physical map */
DECL|member|map_entries
r_int
r_int
id|map_entries
suffix:semicolon
DECL|member|map_pages
r_int
r_int
id|map_pages
suffix:semicolon
DECL|member|map
r_struct
id|vf_map_struct
id|map
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|memclust_struct
r_struct
id|memclust_struct
(brace
DECL|member|start_pfn
r_int
r_int
id|start_pfn
suffix:semicolon
DECL|member|numpages
r_int
r_int
id|numpages
suffix:semicolon
DECL|member|numtested
r_int
r_int
id|numtested
suffix:semicolon
DECL|member|bitmap_va
r_int
r_int
id|bitmap_va
suffix:semicolon
DECL|member|bitmap_pa
r_int
r_int
id|bitmap_pa
suffix:semicolon
DECL|member|bitmap_chksum
r_int
r_int
id|bitmap_chksum
suffix:semicolon
DECL|member|usage
r_int
r_int
id|usage
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|memdesc_struct
r_struct
id|memdesc_struct
(brace
DECL|member|chksum
r_int
r_int
id|chksum
suffix:semicolon
DECL|member|optional_pa
r_int
r_int
id|optional_pa
suffix:semicolon
DECL|member|numclusters
r_int
r_int
id|numclusters
suffix:semicolon
DECL|member|cluster
r_struct
id|memclust_struct
id|cluster
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hwrpb_struct
r_struct
id|hwrpb_struct
(brace
DECL|member|phys_addr
r_int
r_int
id|phys_addr
suffix:semicolon
multiline_comment|/* check: physical address of the hwrpb */
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
multiline_comment|/* check: &quot;HWRPB&bslash;0&bslash;0&bslash;0&quot; */
DECL|member|revision
r_int
r_int
id|revision
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* size of hwrpb */
DECL|member|cpuid
r_int
r_int
id|cpuid
suffix:semicolon
DECL|member|pagesize
r_int
r_int
id|pagesize
suffix:semicolon
multiline_comment|/* 8192, I hope */
DECL|member|pa_bits
r_int
r_int
id|pa_bits
suffix:semicolon
multiline_comment|/* number of physical address bits */
DECL|member|max_asn
r_int
r_int
id|max_asn
suffix:semicolon
DECL|member|ssn
r_int
r_char
id|ssn
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* system serial number: big bother is watching */
DECL|member|sys_type
r_int
r_int
id|sys_type
suffix:semicolon
DECL|member|sys_variation
r_int
r_int
id|sys_variation
suffix:semicolon
DECL|member|sys_revision
r_int
r_int
id|sys_revision
suffix:semicolon
DECL|member|intr_freq
r_int
r_int
id|intr_freq
suffix:semicolon
multiline_comment|/* interval clock frequency * 4096 */
DECL|member|cycle_freq
r_int
r_int
id|cycle_freq
suffix:semicolon
multiline_comment|/* cycle counter frequency */
DECL|member|vptb
r_int
r_int
id|vptb
suffix:semicolon
multiline_comment|/* Virtual Page Table Base address */
DECL|member|res1
r_int
r_int
id|res1
suffix:semicolon
DECL|member|tbhb_offset
r_int
r_int
id|tbhb_offset
suffix:semicolon
multiline_comment|/* Translation Buffer Hint Block */
DECL|member|nr_processors
r_int
r_int
id|nr_processors
suffix:semicolon
DECL|member|processor_size
r_int
r_int
id|processor_size
suffix:semicolon
DECL|member|processor_offset
r_int
r_int
id|processor_offset
suffix:semicolon
DECL|member|ctb_nr
r_int
r_int
id|ctb_nr
suffix:semicolon
DECL|member|ctb_size
r_int
r_int
id|ctb_size
suffix:semicolon
multiline_comment|/* console terminal block size */
DECL|member|ctbt_offset
r_int
r_int
id|ctbt_offset
suffix:semicolon
multiline_comment|/* console terminal block table offset */
DECL|member|crb_offset
r_int
r_int
id|crb_offset
suffix:semicolon
multiline_comment|/* console callback routine block */
DECL|member|mddt_offset
r_int
r_int
id|mddt_offset
suffix:semicolon
multiline_comment|/* memory data descriptor table */
DECL|member|cdb_offset
r_int
r_int
id|cdb_offset
suffix:semicolon
multiline_comment|/* configuration data block (or NULL) */
DECL|member|frut_offset
r_int
r_int
id|frut_offset
suffix:semicolon
multiline_comment|/* FRU table (or NULL) */
DECL|member|save_terminal
r_void
(paren
op_star
id|save_terminal
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|member|save_terminal_data
r_int
r_int
id|save_terminal_data
suffix:semicolon
DECL|member|restore_terminal
r_void
(paren
op_star
id|restore_terminal
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|member|restore_terminal_data
r_int
r_int
id|restore_terminal_data
suffix:semicolon
DECL|member|CPU_restart
r_void
(paren
op_star
id|CPU_restart
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|member|CPU_restart_data
r_int
r_int
id|CPU_restart_data
suffix:semicolon
DECL|member|res2
r_int
r_int
id|res2
suffix:semicolon
DECL|member|res3
r_int
r_int
id|res3
suffix:semicolon
DECL|member|chksum
r_int
r_int
id|chksum
suffix:semicolon
DECL|member|rxrdy
r_int
r_int
id|rxrdy
suffix:semicolon
DECL|member|txrdy
r_int
r_int
id|txrdy
suffix:semicolon
DECL|member|dsrdbt_offset
r_int
r_int
id|dsrdbt_offset
suffix:semicolon
multiline_comment|/* &quot;Dynamic System Recognition Data Block Table&quot; Whee */
)brace
suffix:semicolon
macro_line|#endif
eof
