multiline_comment|/*&n; * PowerPC memory management structures&n; */
macro_line|#ifndef _PPC_MMU_H_
DECL|macro|_PPC_MMU_H_
mdefine_line|#define _PPC_MMU_H_
multiline_comment|/* Hardware Page Table Entry */
DECL|struct|_PTE
r_typedef
r_struct
id|_PTE
(brace
DECL|member|v
r_int
r_int
id|v
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Entry is valid */
DECL|member|vsid
r_int
r_int
id|vsid
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* Virtual segment identifier */
DECL|member|h
r_int
r_int
id|h
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Hash algorithm indicator */
DECL|member|api
r_int
r_int
id|api
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Abbreviated page index */
DECL|member|rpn
r_int
r_int
id|rpn
suffix:colon
l_int|20
suffix:semicolon
multiline_comment|/* Real (physical) page number */
r_int
r_int
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|r
r_int
r_int
id|r
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Referenced */
DECL|member|c
r_int
r_int
id|c
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Changed */
DECL|member|w
r_int
r_int
id|w
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Write-thru cache mode */
DECL|member|i
r_int
r_int
id|i
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Cache inhibited */
DECL|member|m
r_int
r_int
id|m
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Memory coherence */
DECL|member|g
r_int
r_int
id|g
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Guarded */
r_int
r_int
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|pp
r_int
r_int
id|pp
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Page protection */
DECL|typedef|PTE
)brace
id|PTE
suffix:semicolon
multiline_comment|/* Values for PP (assumes Ks=0, Kp=1) */
DECL|macro|PP_RWXX
mdefine_line|#define PP_RWXX&t;0&t;/* Supervisor read/write, User none */
DECL|macro|PP_RWRX
mdefine_line|#define PP_RWRX 1&t;/* Supervisor read/write, User read */
DECL|macro|PP_RWRW
mdefine_line|#define PP_RWRW 2&t;/* Supervisor read/write, User read/write */
DECL|macro|PP_RXRX
mdefine_line|#define PP_RXRX 3&t;/* Supervisor read,       User read */
multiline_comment|/* Segment Register */
DECL|struct|_SEGREG
r_typedef
r_struct
id|_SEGREG
(brace
DECL|member|t
r_int
r_int
id|t
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Normal or I/O  type */
DECL|member|ks
r_int
r_int
id|ks
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supervisor &squot;key&squot; (normally 0) */
DECL|member|kp
r_int
r_int
id|kp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* User &squot;key&squot; (normally 1) */
DECL|member|n
r_int
r_int
id|n
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* No-execute */
r_int
r_int
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|vsid
r_int
r_int
id|vsid
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* Virtual Segment Identifier */
DECL|typedef|SEGREG
)brace
id|SEGREG
suffix:semicolon
multiline_comment|/* Block Address Translation (BAT) Registers */
DECL|struct|_BATU
r_typedef
r_struct
id|_BATU
multiline_comment|/* Upper part of BAT */
(brace
DECL|member|bepi
r_int
r_int
id|bepi
suffix:colon
l_int|15
suffix:semicolon
multiline_comment|/* Effective page index (virtual address) */
r_int
r_int
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|bl
r_int
r_int
id|bl
suffix:colon
l_int|11
suffix:semicolon
multiline_comment|/* Block size mask */
DECL|member|vs
r_int
r_int
id|vs
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Supervisor valid */
DECL|member|vp
r_int
r_int
id|vp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* User valid */
DECL|typedef|BATU
)brace
id|BATU
suffix:semicolon
DECL|struct|_BATL
r_typedef
r_struct
id|_BATL
multiline_comment|/* Lower part of BAT */
(brace
DECL|member|brpn
r_int
r_int
id|brpn
suffix:colon
l_int|15
suffix:semicolon
multiline_comment|/* Real page index (physical address) */
r_int
r_int
suffix:colon
l_int|10
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|w
r_int
r_int
id|w
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Write-thru cache */
DECL|member|i
r_int
r_int
id|i
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Cache inhibit */
DECL|member|m
r_int
r_int
id|m
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Memory coherence */
DECL|member|g
r_int
r_int
id|g
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Guarded (MBZ) */
r_int
r_int
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|pp
r_int
r_int
id|pp
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Page access protections */
DECL|typedef|BATL
)brace
id|BATL
suffix:semicolon
DECL|struct|_BAT
r_typedef
r_struct
id|_BAT
(brace
DECL|member|batu
id|BATU
id|batu
suffix:semicolon
multiline_comment|/* Upper register */
DECL|member|batl
id|BATL
id|batl
suffix:semicolon
multiline_comment|/* Lower register */
DECL|typedef|BAT
)brace
id|BAT
suffix:semicolon
multiline_comment|/* Block size masks */
DECL|macro|BL_128K
mdefine_line|#define BL_128K&t;0x000
DECL|macro|BL_256K
mdefine_line|#define BL_256K 0x001
DECL|macro|BL_512K
mdefine_line|#define BL_512K 0x003
DECL|macro|BL_1M
mdefine_line|#define BL_1M   0x007
DECL|macro|BL_2M
mdefine_line|#define BL_2M   0x00F
DECL|macro|BL_4M
mdefine_line|#define BL_4M   0x01F
DECL|macro|BL_8M
mdefine_line|#define BL_8M   0x03F
DECL|macro|BL_16M
mdefine_line|#define BL_16M  0x07F
DECL|macro|BL_32M
mdefine_line|#define BL_32M  0x0FF
DECL|macro|BL_64M
mdefine_line|#define BL_64M  0x1FF
DECL|macro|BL_128M
mdefine_line|#define BL_128M 0x3FF
DECL|macro|BL_256M
mdefine_line|#define BL_256M 0x7FF
multiline_comment|/* BAT Access Protection */
DECL|macro|BPP_XX
mdefine_line|#define BPP_XX&t;0x00&t;&t;/* No access */
DECL|macro|BPP_RX
mdefine_line|#define BPP_RX&t;0x01&t;&t;/* Read only */
DECL|macro|BPP_RW
mdefine_line|#define BPP_RW&t;0x02&t;&t;/* Read/write */
multiline_comment|/*&n; * Simulated two-level MMU.  This structure is used by the kernel&n; * to keep track of MMU mappings and is used to update/maintain&n; * the hardware HASH table which is really a cache of mappings.&n; *&n; * The simulated structures mimic the hardware available on other&n; * platforms, notably the 80x86 and 680x0.&n; */
DECL|struct|_pte
r_typedef
r_struct
id|_pte
(brace
DECL|member|page_num
r_int
r_int
id|page_num
suffix:colon
l_int|20
suffix:semicolon
DECL|member|unused
r_int
r_int
id|unused
suffix:colon
l_int|6
suffix:semicolon
DECL|member|acc
r_int
r_int
id|acc
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Read/write/execute permissions */
DECL|member|r
r_int
r_int
id|r
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Page has been referenced */
DECL|member|m
r_int
r_int
id|m
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Page has been modified */
DECL|member|v
r_int
r_int
id|v
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Entry is valid */
DECL|typedef|pte
)brace
id|pte
suffix:semicolon
DECL|macro|ACC_Rxx
mdefine_line|#define ACC_Rxx&t;0x04
DECL|macro|ACC_xWx
mdefine_line|#define ACC_xWx 0x02
DECL|macro|ACC_xxX
mdefine_line|#define ACC_xxX 0x01
DECL|macro|ACC_RWX
mdefine_line|#define ACC_RWX (ACC_Rxx|ACC_xWx|ACC_xxX)
DECL|macro|PD_SHIFT
mdefine_line|#define PD_SHIFT (10+12)&t;&t;/* Page directory */
DECL|macro|PD_MASK
mdefine_line|#define PD_MASK  0x02FF
DECL|macro|PT_SHIFT
mdefine_line|#define PT_SHIFT (12)&t;&t;&t;/* Page Table */
DECL|macro|PT_MASK
mdefine_line|#define PT_MASK  0x02FF
DECL|macro|PG_SHIFT
mdefine_line|#define PG_SHIFT (12)&t;&t;&t;/* Page Entry */
multiline_comment|/* MMU context */
DECL|struct|_MMU_context
r_typedef
r_struct
id|_MMU_context
(brace
DECL|member|segs
id|SEGREG
id|segs
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Segment registers */
DECL|member|pmap
id|pte
op_star
op_star
id|pmap
suffix:semicolon
multiline_comment|/* Two-level page-map structure */
DECL|typedef|MMU_context
)brace
id|MMU_context
suffix:semicolon
macro_line|#if 0
id|BAT
id|ibat
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Instruction BAT images */
id|BAT
id|dbat
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Data BAT images */
id|PTE
op_star
id|hash_table
suffix:semicolon
multiline_comment|/* Hardware hashed page table */
r_int
id|hash_table_size
suffix:semicolon
r_int
id|hash_table_mask
suffix:semicolon
r_int
r_int
id|sdr
suffix:semicolon
multiline_comment|/* Hardware image of SDR */
macro_line|#endif   
multiline_comment|/* Used to set up SDR register */
DECL|macro|HASH_TABLE_SIZE_64K
mdefine_line|#define HASH_TABLE_SIZE_64K&t;0x00010000
DECL|macro|HASH_TABLE_SIZE_128K
mdefine_line|#define HASH_TABLE_SIZE_128K&t;0x00020000
DECL|macro|HASH_TABLE_SIZE_256K
mdefine_line|#define HASH_TABLE_SIZE_256K&t;0x00040000
DECL|macro|HASH_TABLE_SIZE_512K
mdefine_line|#define HASH_TABLE_SIZE_512K&t;0x00080000
DECL|macro|HASH_TABLE_SIZE_1M
mdefine_line|#define HASH_TABLE_SIZE_1M&t;0x00100000
DECL|macro|HASH_TABLE_SIZE_2M
mdefine_line|#define HASH_TABLE_SIZE_2M&t;0x00200000
DECL|macro|HASH_TABLE_SIZE_4M
mdefine_line|#define HASH_TABLE_SIZE_4M&t;0x00400000
DECL|macro|HASH_TABLE_MASK_64K
mdefine_line|#define HASH_TABLE_MASK_64K&t;0x000   
DECL|macro|HASH_TABLE_MASK_128K
mdefine_line|#define HASH_TABLE_MASK_128K&t;0x001   
DECL|macro|HASH_TABLE_MASK_256K
mdefine_line|#define HASH_TABLE_MASK_256K&t;0x003   
DECL|macro|HASH_TABLE_MASK_512K
mdefine_line|#define HASH_TABLE_MASK_512K&t;0x007
DECL|macro|HASH_TABLE_MASK_1M
mdefine_line|#define HASH_TABLE_MASK_1M&t;0x00F   
DECL|macro|HASH_TABLE_MASK_2M
mdefine_line|#define HASH_TABLE_MASK_2M&t;0x01F   
DECL|macro|HASH_TABLE_MASK_4M
mdefine_line|#define HASH_TABLE_MASK_4M&t;0x03F   
DECL|macro|MMU_PAGE_SIZE
mdefine_line|#define MMU_PAGE_SIZE&t;4096
macro_line|#endif
eof
