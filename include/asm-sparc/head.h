DECL|macro|KERNSIZE
mdefine_line|#define KERNSIZE&t;134217728
DECL|macro|KERNBASE
mdefine_line|#define KERNBASE&t;0           /* new strategy */
DECL|macro|LOAD_ADDR
mdefine_line|#define LOAD_ADDR       0x4000
DECL|macro|C_STACK
mdefine_line|#define C_STACK         96
DECL|macro|SUN4C_SEGSZ
mdefine_line|#define SUN4C_SEGSZ     (1 &lt;&lt; 18)
DECL|macro|NBPG
mdefine_line|#define NBPG&t;&t;4096&t;
DECL|macro|UPAGES
mdefine_line|#define UPAGES&t;&t;2
DECL|macro|PROM_BASE
mdefine_line|#define PROM_BASE&t;-1568768
DECL|macro|PAGESHIFT_SUN4C
mdefine_line|#define PAGESHIFT_SUN4C 12          /* This is good for sun4m&squot;s also */
DECL|macro|ASI_CONTROL
mdefine_line|#define ASI_CONTROL     0x02        /* for cache enable, context registers, etc. */
DECL|macro|ASI_SEGMAP
mdefine_line|#define ASI_SEGMAP      0x03
DECL|macro|ASI_PTE
mdefine_line|#define ASI_PTE         0x04
DECL|macro|AC_CONTEXT
mdefine_line|#define AC_CONTEXT      0x30000000
DECL|macro|USRSTACK
mdefine_line|#define USRSTACK        KERNBASE
DECL|macro|IE_REG_PTE_PG
mdefine_line|#define IE_REG_PTE_PG   -201326592
DECL|macro|INT_ENABLE_REG_PHYSADR
mdefine_line|#define INT_ENABLE_REG_PHYSADR      0xf5000000
DECL|macro|IE_ALLIE
mdefine_line|#define IE_ALLIE        0x01
multiline_comment|/* This crap should go elsewhere */
DECL|macro|PSR_IMPL
mdefine_line|#define PSR_IMPL        0xf0000000      /* implementation */
DECL|macro|PSR_VER
mdefine_line|#define PSR_VER         0x0f000000      /* version */
DECL|macro|PSR_ICC
mdefine_line|#define PSR_ICC         0x00f00000      /* integer condition codes */
DECL|macro|PSR_N
mdefine_line|#define PSR_N           0x00800000      /* negative */
DECL|macro|PSR_Z
mdefine_line|#define PSR_Z           0x00400000      /* zero */
DECL|macro|PSR_O
mdefine_line|#define PSR_O           0x00200000      /* overflow */
DECL|macro|PSR_C
mdefine_line|#define PSR_C           0x00100000      /* carry */
DECL|macro|PSR_EC
mdefine_line|#define PSR_EC          0x00002000      /* coprocessor enable */
DECL|macro|PSR_EF
mdefine_line|#define PSR_EF          0x00001000      /* FP enable */
DECL|macro|PSR_PIL
mdefine_line|#define PSR_PIL         0x00000f00      /* interrupt level */
DECL|macro|PSR_S
mdefine_line|#define PSR_S           0x00000080      /* supervisor (kernel) mode */
DECL|macro|PSR_PS
mdefine_line|#define PSR_PS          0x00000040      /* previous supervisor mode (traps) */
DECL|macro|PSR_ET
mdefine_line|#define PSR_ET          0x00000020      /* trap enable */
DECL|macro|PSR_CWP
mdefine_line|#define PSR_CWP         0x0000001f      /* current window pointer */
DECL|macro|PCB_WIM
mdefine_line|#define PCB_WIM         20
DECL|macro|HZ
mdefine_line|#define HZ              100
multiline_comment|/* Offsets into the proc structure for window info, etc. Just dummies&n;   for now.&n;*/
DECL|macro|TASK_WIM
mdefine_line|#define TASK_WIM      0x8
DECL|macro|TASK_UW
mdefine_line|#define TASK_UW       0x16
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE     8192
DECL|macro|TASK_RW
mdefine_line|#define TASK_RW       0x32
DECL|macro|TASK_NSAVED
mdefine_line|#define TASK_NSAVED   0x40
DECL|macro|PG_VSHIFT
mdefine_line|#define PG_VSHIFT     0x16
DECL|macro|PG_PROTSHIFT
mdefine_line|#define PG_PROTSHIFT  0x6
DECL|macro|PG_PROTUWRITE
mdefine_line|#define PG_PROTUWRITE 0x4
eof
