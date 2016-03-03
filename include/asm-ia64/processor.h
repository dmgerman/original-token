macro_line|#ifndef _ASM_IA64_PROCESSOR_H
DECL|macro|_ASM_IA64_PROCESSOR_H
mdefine_line|#define _ASM_IA64_PROCESSOR_H
multiline_comment|/*&n; * Copyright (C) 1998-2000 Hewlett-Packard Co&n; * Copyright (C) 1998-2000 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1998-2000 Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; * Copyright (C) 1999 Asit Mallick &lt;asit.k.mallick@intel.com&gt;&n; * Copyright (C) 1999 Don Dugger &lt;don.dugger@intel.com&gt;&n; *&n; * 11/24/98&t;S.Eranian&t;added ia64_set_iva()&n; * 12/03/99&t;D. Mosberger&t;implement thread_saved_pc() via kernel unwind API&n; * 06/16/00&t;A. Mallick&t;added csd/ssd/tssd for ia32 support&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/types.h&gt;
DECL|macro|IA64_NUM_DBG_REGS
mdefine_line|#define IA64_NUM_DBG_REGS&t;8
multiline_comment|/*&n; * Limits for PMC and PMD are set to less than maximum architected values&n; * but should be sufficient for a while&n; */
DECL|macro|IA64_NUM_PMC_REGS
mdefine_line|#define IA64_NUM_PMC_REGS&t;32
DECL|macro|IA64_NUM_PMD_REGS
mdefine_line|#define IA64_NUM_PMD_REGS&t;32
DECL|macro|IA64_NUM_PMD_COUNTERS
mdefine_line|#define IA64_NUM_PMD_COUNTERS&t;4
multiline_comment|/*&n; * TASK_SIZE really is a mis-named.  It really is the maximum user&n; * space address (plus one).  On IA-64, there are five regions of 2TB&n; * each (assuming 8KB page size), for a total of 8TB of user virtual&n; * address space.&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;&t;(current-&gt;thread.task_size)
multiline_comment|/*&n; * This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;(current-&gt;thread.map_base)
multiline_comment|/*&n; * Bus types&n; */
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus 0
DECL|macro|EISA_bus__is_a_macro
mdefine_line|#define EISA_bus__is_a_macro /* for versions in ksyms.c */
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro /* for versions in ksyms.c */
multiline_comment|/* Processor status register bits: */
DECL|macro|IA64_PSR_BE_BIT
mdefine_line|#define IA64_PSR_BE_BIT&t;&t;1
DECL|macro|IA64_PSR_UP_BIT
mdefine_line|#define IA64_PSR_UP_BIT&t;&t;2
DECL|macro|IA64_PSR_AC_BIT
mdefine_line|#define IA64_PSR_AC_BIT&t;&t;3
DECL|macro|IA64_PSR_MFL_BIT
mdefine_line|#define IA64_PSR_MFL_BIT&t;4
DECL|macro|IA64_PSR_MFH_BIT
mdefine_line|#define IA64_PSR_MFH_BIT&t;5
DECL|macro|IA64_PSR_IC_BIT
mdefine_line|#define IA64_PSR_IC_BIT&t;&t;13
DECL|macro|IA64_PSR_I_BIT
mdefine_line|#define IA64_PSR_I_BIT&t;&t;14
DECL|macro|IA64_PSR_PK_BIT
mdefine_line|#define IA64_PSR_PK_BIT&t;&t;15
DECL|macro|IA64_PSR_DT_BIT
mdefine_line|#define IA64_PSR_DT_BIT&t;&t;17
DECL|macro|IA64_PSR_DFL_BIT
mdefine_line|#define IA64_PSR_DFL_BIT&t;18
DECL|macro|IA64_PSR_DFH_BIT
mdefine_line|#define IA64_PSR_DFH_BIT&t;19
DECL|macro|IA64_PSR_SP_BIT
mdefine_line|#define IA64_PSR_SP_BIT&t;&t;20
DECL|macro|IA64_PSR_PP_BIT
mdefine_line|#define IA64_PSR_PP_BIT&t;&t;21
DECL|macro|IA64_PSR_DI_BIT
mdefine_line|#define IA64_PSR_DI_BIT&t;&t;22
DECL|macro|IA64_PSR_SI_BIT
mdefine_line|#define IA64_PSR_SI_BIT&t;&t;23
DECL|macro|IA64_PSR_DB_BIT
mdefine_line|#define IA64_PSR_DB_BIT&t;&t;24
DECL|macro|IA64_PSR_LP_BIT
mdefine_line|#define IA64_PSR_LP_BIT&t;&t;25
DECL|macro|IA64_PSR_TB_BIT
mdefine_line|#define IA64_PSR_TB_BIT&t;&t;26
DECL|macro|IA64_PSR_RT_BIT
mdefine_line|#define IA64_PSR_RT_BIT&t;&t;27
multiline_comment|/* The following are not affected by save_flags()/restore_flags(): */
DECL|macro|IA64_PSR_CPL0_BIT
mdefine_line|#define IA64_PSR_CPL0_BIT&t;32
DECL|macro|IA64_PSR_CPL1_BIT
mdefine_line|#define IA64_PSR_CPL1_BIT&t;33
DECL|macro|IA64_PSR_IS_BIT
mdefine_line|#define IA64_PSR_IS_BIT&t;&t;34
DECL|macro|IA64_PSR_MC_BIT
mdefine_line|#define IA64_PSR_MC_BIT&t;&t;35
DECL|macro|IA64_PSR_IT_BIT
mdefine_line|#define IA64_PSR_IT_BIT&t;&t;36
DECL|macro|IA64_PSR_ID_BIT
mdefine_line|#define IA64_PSR_ID_BIT&t;&t;37
DECL|macro|IA64_PSR_DA_BIT
mdefine_line|#define IA64_PSR_DA_BIT&t;&t;38
DECL|macro|IA64_PSR_DD_BIT
mdefine_line|#define IA64_PSR_DD_BIT&t;&t;39
DECL|macro|IA64_PSR_SS_BIT
mdefine_line|#define IA64_PSR_SS_BIT&t;&t;40
DECL|macro|IA64_PSR_RI_BIT
mdefine_line|#define IA64_PSR_RI_BIT&t;&t;41
DECL|macro|IA64_PSR_ED_BIT
mdefine_line|#define IA64_PSR_ED_BIT&t;&t;43
DECL|macro|IA64_PSR_BN_BIT
mdefine_line|#define IA64_PSR_BN_BIT&t;&t;44
DECL|macro|IA64_PSR_BE
mdefine_line|#define IA64_PSR_BE&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_BE_BIT)
DECL|macro|IA64_PSR_UP
mdefine_line|#define IA64_PSR_UP&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_UP_BIT)
DECL|macro|IA64_PSR_AC
mdefine_line|#define IA64_PSR_AC&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_AC_BIT)
DECL|macro|IA64_PSR_MFL
mdefine_line|#define IA64_PSR_MFL&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_MFL_BIT)
DECL|macro|IA64_PSR_MFH
mdefine_line|#define IA64_PSR_MFH&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_MFH_BIT)
DECL|macro|IA64_PSR_IC
mdefine_line|#define IA64_PSR_IC&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_IC_BIT)
DECL|macro|IA64_PSR_I
mdefine_line|#define IA64_PSR_I&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_I_BIT)
DECL|macro|IA64_PSR_PK
mdefine_line|#define IA64_PSR_PK&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_PK_BIT)
DECL|macro|IA64_PSR_DT
mdefine_line|#define IA64_PSR_DT&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_DT_BIT)
DECL|macro|IA64_PSR_DFL
mdefine_line|#define IA64_PSR_DFL&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_DFL_BIT)
DECL|macro|IA64_PSR_DFH
mdefine_line|#define IA64_PSR_DFH&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_DFH_BIT)
DECL|macro|IA64_PSR_SP
mdefine_line|#define IA64_PSR_SP&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_SP_BIT)
DECL|macro|IA64_PSR_PP
mdefine_line|#define IA64_PSR_PP&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_PP_BIT)
DECL|macro|IA64_PSR_DI
mdefine_line|#define IA64_PSR_DI&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_DI_BIT)
DECL|macro|IA64_PSR_SI
mdefine_line|#define IA64_PSR_SI&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_SI_BIT)
DECL|macro|IA64_PSR_DB
mdefine_line|#define IA64_PSR_DB&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_DB_BIT)
DECL|macro|IA64_PSR_LP
mdefine_line|#define IA64_PSR_LP&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_LP_BIT)
DECL|macro|IA64_PSR_TB
mdefine_line|#define IA64_PSR_TB&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_TB_BIT)
DECL|macro|IA64_PSR_RT
mdefine_line|#define IA64_PSR_RT&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_RT_BIT)
multiline_comment|/* The following are not affected by save_flags()/restore_flags(): */
DECL|macro|IA64_PSR_IS
mdefine_line|#define IA64_PSR_IS&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_IS_BIT)
DECL|macro|IA64_PSR_MC
mdefine_line|#define IA64_PSR_MC&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_MC_BIT)
DECL|macro|IA64_PSR_IT
mdefine_line|#define IA64_PSR_IT&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_IT_BIT)
DECL|macro|IA64_PSR_ID
mdefine_line|#define IA64_PSR_ID&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_ID_BIT)
DECL|macro|IA64_PSR_DA
mdefine_line|#define IA64_PSR_DA&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_DA_BIT)
DECL|macro|IA64_PSR_DD
mdefine_line|#define IA64_PSR_DD&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_DD_BIT)
DECL|macro|IA64_PSR_SS
mdefine_line|#define IA64_PSR_SS&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_SS_BIT)
DECL|macro|IA64_PSR_RI
mdefine_line|#define IA64_PSR_RI&t;(__IA64_UL(3) &lt;&lt; IA64_PSR_RI_BIT)
DECL|macro|IA64_PSR_ED
mdefine_line|#define IA64_PSR_ED&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_ED_BIT)
DECL|macro|IA64_PSR_BN
mdefine_line|#define IA64_PSR_BN&t;(__IA64_UL(1) &lt;&lt; IA64_PSR_BN_BIT)
multiline_comment|/* User mask bits: */
DECL|macro|IA64_PSR_UM
mdefine_line|#define IA64_PSR_UM&t;(IA64_PSR_BE | IA64_PSR_UP | IA64_PSR_AC | IA64_PSR_MFL | IA64_PSR_MFH)
multiline_comment|/* Default Control Register */
DECL|macro|IA64_DCR_PP_BIT
mdefine_line|#define IA64_DCR_PP_BIT&t;&t; 0&t;/* privileged performance monitor default */
DECL|macro|IA64_DCR_BE_BIT
mdefine_line|#define IA64_DCR_BE_BIT&t;&t; 1&t;/* big-endian default */
DECL|macro|IA64_DCR_LC_BIT
mdefine_line|#define IA64_DCR_LC_BIT&t;&t; 2&t;/* ia32 lock-check enable */
DECL|macro|IA64_DCR_DM_BIT
mdefine_line|#define IA64_DCR_DM_BIT&t;&t; 8&t;/* defer TLB miss faults */
DECL|macro|IA64_DCR_DP_BIT
mdefine_line|#define IA64_DCR_DP_BIT&t;&t; 9&t;/* defer page-not-present faults */
DECL|macro|IA64_DCR_DK_BIT
mdefine_line|#define IA64_DCR_DK_BIT&t;&t;10&t;/* defer key miss faults */
DECL|macro|IA64_DCR_DX_BIT
mdefine_line|#define IA64_DCR_DX_BIT&t;&t;11&t;/* defer key permission faults */
DECL|macro|IA64_DCR_DR_BIT
mdefine_line|#define IA64_DCR_DR_BIT&t;&t;12&t;/* defer access right faults */
DECL|macro|IA64_DCR_DA_BIT
mdefine_line|#define IA64_DCR_DA_BIT&t;&t;13&t;/* defer access bit faults */
DECL|macro|IA64_DCR_DD_BIT
mdefine_line|#define IA64_DCR_DD_BIT&t;&t;14&t;/* defer debug faults */
DECL|macro|IA64_DCR_PP
mdefine_line|#define IA64_DCR_PP&t;(__IA64_UL(1) &lt;&lt; IA64_DCR_PP_BIT)
DECL|macro|IA64_DCR_BE
mdefine_line|#define IA64_DCR_BE&t;(__IA64_UL(1) &lt;&lt; IA64_DCR_BE_BIT)
DECL|macro|IA64_DCR_LC
mdefine_line|#define IA64_DCR_LC&t;(__IA64_UL(1) &lt;&lt; IA64_DCR_LC_BIT)
DECL|macro|IA64_DCR_DM
mdefine_line|#define IA64_DCR_DM&t;(__IA64_UL(1) &lt;&lt; IA64_DCR_DM_BIT)
DECL|macro|IA64_DCR_DP
mdefine_line|#define IA64_DCR_DP&t;(__IA64_UL(1) &lt;&lt; IA64_DCR_DP_BIT)
DECL|macro|IA64_DCR_DK
mdefine_line|#define IA64_DCR_DK&t;(__IA64_UL(1) &lt;&lt; IA64_DCR_DK_BIT)
DECL|macro|IA64_DCR_DX
mdefine_line|#define IA64_DCR_DX&t;(__IA64_UL(1) &lt;&lt; IA64_DCR_DX_BIT)
DECL|macro|IA64_DCR_DR
mdefine_line|#define IA64_DCR_DR&t;(__IA64_UL(1) &lt;&lt; IA64_DCR_DR_BIT)
DECL|macro|IA64_DCR_DA
mdefine_line|#define IA64_DCR_DA&t;(__IA64_UL(1) &lt;&lt; IA64_DCR_DA_BIT)
DECL|macro|IA64_DCR_DD
mdefine_line|#define IA64_DCR_DD&t;(__IA64_UL(1) &lt;&lt; IA64_DCR_DD_BIT)
multiline_comment|/* Interrupt Status Register */
DECL|macro|IA64_ISR_X_BIT
mdefine_line|#define IA64_ISR_X_BIT&t;&t;32&t;/* execute access */
DECL|macro|IA64_ISR_W_BIT
mdefine_line|#define IA64_ISR_W_BIT&t;&t;33&t;/* write access */
DECL|macro|IA64_ISR_R_BIT
mdefine_line|#define IA64_ISR_R_BIT&t;&t;34&t;/* read access */
DECL|macro|IA64_ISR_NA_BIT
mdefine_line|#define IA64_ISR_NA_BIT&t;&t;35&t;/* non-access */
DECL|macro|IA64_ISR_SP_BIT
mdefine_line|#define IA64_ISR_SP_BIT&t;&t;36&t;/* speculative load exception */
DECL|macro|IA64_ISR_RS_BIT
mdefine_line|#define IA64_ISR_RS_BIT&t;&t;37&t;/* mandatory register-stack exception */
DECL|macro|IA64_ISR_IR_BIT
mdefine_line|#define IA64_ISR_IR_BIT&t;&t;38&t;/* invalid register frame exception */
DECL|macro|IA64_ISR_X
mdefine_line|#define IA64_ISR_X&t;(__IA64_UL(1) &lt;&lt; IA64_ISR_X_BIT)
DECL|macro|IA64_ISR_W
mdefine_line|#define IA64_ISR_W&t;(__IA64_UL(1) &lt;&lt; IA64_ISR_W_BIT)
DECL|macro|IA64_ISR_R
mdefine_line|#define IA64_ISR_R&t;(__IA64_UL(1) &lt;&lt; IA64_ISR_R_BIT)
DECL|macro|IA64_ISR_NA
mdefine_line|#define IA64_ISR_NA&t;(__IA64_UL(1) &lt;&lt; IA64_ISR_NA_BIT)
DECL|macro|IA64_ISR_SP
mdefine_line|#define IA64_ISR_SP&t;(__IA64_UL(1) &lt;&lt; IA64_ISR_SP_BIT)
DECL|macro|IA64_ISR_RS
mdefine_line|#define IA64_ISR_RS&t;(__IA64_UL(1) &lt;&lt; IA64_ISR_RS_BIT)
DECL|macro|IA64_ISR_IR
mdefine_line|#define IA64_ISR_IR&t;(__IA64_UL(1) &lt;&lt; IA64_ISR_IR_BIT)
DECL|macro|IA64_THREAD_FPH_VALID
mdefine_line|#define IA64_THREAD_FPH_VALID&t;(__IA64_UL(1) &lt;&lt; 0)&t;/* floating-point high state valid? */
DECL|macro|IA64_THREAD_DBG_VALID
mdefine_line|#define IA64_THREAD_DBG_VALID&t;(__IA64_UL(1) &lt;&lt; 1)&t;/* debug registers valid? */
DECL|macro|IA64_THREAD_PM_VALID
mdefine_line|#define IA64_THREAD_PM_VALID&t;(__IA64_UL(1) &lt;&lt; 2)&t;/* performance registers valid? */
DECL|macro|IA64_THREAD_UAC_NOPRINT
mdefine_line|#define IA64_THREAD_UAC_NOPRINT&t;(__IA64_UL(1) &lt;&lt; 3)&t;/* don&squot;t log unaligned accesses */
DECL|macro|IA64_THREAD_UAC_SIGBUS
mdefine_line|#define IA64_THREAD_UAC_SIGBUS&t;(__IA64_UL(1) &lt;&lt; 4)&t;/* generate SIGBUS on unaligned acc. */
DECL|macro|IA64_THREAD_KRBS_SYNCED
mdefine_line|#define IA64_THREAD_KRBS_SYNCED&t;(__IA64_UL(1) &lt;&lt; 5)&t;/* krbs synced with process vm? */
DECL|macro|IA64_THREAD_MAP_SHARED
mdefine_line|#define IA64_THREAD_MAP_SHARED&t;(__IA64_UL(1) &lt;&lt; 6)&t;/* ugly: just a tmp flag for mmap() */
DECL|macro|IA64_KERNEL_DEATH
mdefine_line|#define IA64_KERNEL_DEATH&t;(__IA64_UL(1) &lt;&lt; 63)&t;/* see die_if_kernel()... */
DECL|macro|IA64_THREAD_UAC_SHIFT
mdefine_line|#define IA64_THREAD_UAC_SHIFT&t;3
DECL|macro|IA64_THREAD_UAC_MASK
mdefine_line|#define IA64_THREAD_UAC_MASK&t;(IA64_THREAD_UAC_NOPRINT | IA64_THREAD_UAC_SIGBUS)
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/fpu.h&gt;
macro_line|#include &lt;asm/offsets.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/rse.h&gt;
macro_line|#include &lt;asm/unwind.h&gt;
multiline_comment|/* like above but expressed as bitfields for more efficient access: */
DECL|struct|ia64_psr
r_struct
id|ia64_psr
(brace
DECL|member|reserved0
id|__u64
id|reserved0
suffix:colon
l_int|1
suffix:semicolon
DECL|member|be
id|__u64
id|be
suffix:colon
l_int|1
suffix:semicolon
DECL|member|up
id|__u64
id|up
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ac
id|__u64
id|ac
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mfl
id|__u64
id|mfl
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mfh
id|__u64
id|mfh
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
id|__u64
id|reserved1
suffix:colon
l_int|7
suffix:semicolon
DECL|member|ic
id|__u64
id|ic
suffix:colon
l_int|1
suffix:semicolon
DECL|member|i
id|__u64
id|i
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pk
id|__u64
id|pk
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
id|__u64
id|reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dt
id|__u64
id|dt
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dfl
id|__u64
id|dfl
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dfh
id|__u64
id|dfh
suffix:colon
l_int|1
suffix:semicolon
DECL|member|sp
id|__u64
id|sp
suffix:colon
l_int|1
suffix:semicolon
DECL|member|pp
id|__u64
id|pp
suffix:colon
l_int|1
suffix:semicolon
DECL|member|di
id|__u64
id|di
suffix:colon
l_int|1
suffix:semicolon
DECL|member|si
id|__u64
id|si
suffix:colon
l_int|1
suffix:semicolon
DECL|member|db
id|__u64
id|db
suffix:colon
l_int|1
suffix:semicolon
DECL|member|lp
id|__u64
id|lp
suffix:colon
l_int|1
suffix:semicolon
DECL|member|tb
id|__u64
id|tb
suffix:colon
l_int|1
suffix:semicolon
DECL|member|rt
id|__u64
id|rt
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved3
id|__u64
id|reserved3
suffix:colon
l_int|4
suffix:semicolon
DECL|member|cpl
id|__u64
id|cpl
suffix:colon
l_int|2
suffix:semicolon
DECL|member|is
id|__u64
id|is
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mc
id|__u64
id|mc
suffix:colon
l_int|1
suffix:semicolon
DECL|member|it
id|__u64
id|it
suffix:colon
l_int|1
suffix:semicolon
DECL|member|id
id|__u64
id|id
suffix:colon
l_int|1
suffix:semicolon
DECL|member|da
id|__u64
id|da
suffix:colon
l_int|1
suffix:semicolon
DECL|member|dd
id|__u64
id|dd
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ss
id|__u64
id|ss
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ri
id|__u64
id|ri
suffix:colon
l_int|2
suffix:semicolon
DECL|member|ed
id|__u64
id|ed
suffix:colon
l_int|1
suffix:semicolon
DECL|member|bn
id|__u64
id|bn
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved4
id|__u64
id|reserved4
suffix:colon
l_int|19
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * This shift should be large enough to be able to represent&n; * 1000000/itc_freq with good accuracy while being small enough to fit&n; * 1000000&lt;&lt;IA64_USEC_PER_CYC_SHIFT in 64 bits.&n; */
DECL|macro|IA64_USEC_PER_CYC_SHIFT
mdefine_line|#define IA64_USEC_PER_CYC_SHIFT&t;41
multiline_comment|/*&n; * CPU type, hardware bug flags, and per-CPU state.&n; */
DECL|struct|cpuinfo_ia64
r_struct
id|cpuinfo_ia64
(brace
DECL|member|pgd_quick
id|__u64
op_star
id|pgd_quick
suffix:semicolon
DECL|member|pmd_quick
id|__u64
op_star
id|pmd_quick
suffix:semicolon
DECL|member|pte_quick
id|__u64
op_star
id|pte_quick
suffix:semicolon
DECL|member|pgtable_cache_sz
id|__u64
id|pgtable_cache_sz
suffix:semicolon
multiline_comment|/* CPUID-derived information: */
DECL|member|ppn
id|__u64
id|ppn
suffix:semicolon
DECL|member|features
id|__u64
id|features
suffix:semicolon
DECL|member|number
id|__u8
id|number
suffix:semicolon
DECL|member|revision
id|__u8
id|revision
suffix:semicolon
DECL|member|model
id|__u8
id|model
suffix:semicolon
DECL|member|family
id|__u8
id|family
suffix:semicolon
DECL|member|archrev
id|__u8
id|archrev
suffix:semicolon
DECL|member|vendor
r_char
id|vendor
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|itc_freq
id|__u64
id|itc_freq
suffix:semicolon
multiline_comment|/* frequency of ITC counter */
DECL|member|proc_freq
id|__u64
id|proc_freq
suffix:semicolon
multiline_comment|/* frequency of processor */
DECL|member|cyc_per_usec
id|__u64
id|cyc_per_usec
suffix:semicolon
multiline_comment|/* itc_freq/1000000 */
DECL|member|usec_per_cyc
id|__u64
id|usec_per_cyc
suffix:semicolon
multiline_comment|/* 2^IA64_USEC_PER_CYC_SHIFT*1000000/itc_freq */
DECL|member|unimpl_va_mask
id|__u64
id|unimpl_va_mask
suffix:semicolon
multiline_comment|/* mask of unimplemented virtual address bits (from PAL) */
DECL|member|unimpl_pa_mask
id|__u64
id|unimpl_pa_mask
suffix:semicolon
multiline_comment|/* mask of unimplemented physical address bits (from PAL) */
DECL|member|ptce_base
id|__u64
id|ptce_base
suffix:semicolon
DECL|member|ptce_count
id|__u32
id|ptce_count
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|ptce_stride
id|__u32
id|ptce_stride
(braket
l_int|2
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|member|loops_per_jiffy
id|__u64
id|loops_per_jiffy
suffix:semicolon
DECL|member|ipi_count
id|__u64
id|ipi_count
suffix:semicolon
DECL|member|prof_counter
id|__u64
id|prof_counter
suffix:semicolon
DECL|member|prof_multiplier
id|__u64
id|prof_multiplier
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|my_cpu_data
mdefine_line|#define my_cpu_data&t;&t;cpu_data[smp_processor_id()]
r_extern
r_struct
id|cpuinfo_ia64
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_void
id|identify_cpu
(paren
r_struct
id|cpuinfo_ia64
op_star
)paren
suffix:semicolon
r_extern
r_void
id|print_cpu_info
(paren
r_struct
id|cpuinfo_ia64
op_star
)paren
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|seg
r_int
r_int
id|seg
suffix:semicolon
DECL|typedef|mm_segment_t
)brace
id|mm_segment_t
suffix:semicolon
DECL|macro|SET_UNALIGN_CTL
mdefine_line|#define SET_UNALIGN_CTL(task,value)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(task)-&gt;thread.flags = (((task)-&gt;thread.flags &amp; ~IA64_THREAD_UAC_MASK)&t;&t;&t;&bslash;&n;&t;&t;&t;&t;| (((value) &lt;&lt; IA64_THREAD_UAC_SHIFT) &amp; IA64_THREAD_UAC_MASK));&t;&bslash;&n;&t;0;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|GET_UNALIGN_CTL
mdefine_line|#define GET_UNALIGN_CTL(task,addr)&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;put_user(((task)-&gt;thread.flags &amp; IA64_THREAD_UAC_MASK) &gt;&gt; IA64_THREAD_UAC_SHIFT,&t;&bslash;&n;&t;&t; (int *) (addr));&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
r_struct
id|siginfo
suffix:semicolon
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|ksp
id|__u64
id|ksp
suffix:semicolon
multiline_comment|/* kernel stack pointer */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* various flags */
DECL|member|fph
r_struct
id|ia64_fpreg
id|fph
(braket
l_int|96
)braket
suffix:semicolon
multiline_comment|/* saved/loaded on demand */
DECL|member|dbr
id|__u64
id|dbr
(braket
id|IA64_NUM_DBG_REGS
)braket
suffix:semicolon
DECL|member|ibr
id|__u64
id|ibr
(braket
id|IA64_NUM_DBG_REGS
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_PERFMON
DECL|member|pmc
id|__u64
id|pmc
(braket
id|IA64_NUM_PMC_REGS
)braket
suffix:semicolon
DECL|member|pmd
id|__u64
id|pmd
(braket
id|IA64_NUM_PMD_REGS
)braket
suffix:semicolon
r_struct
(brace
DECL|member|val
id|__u64
id|val
suffix:semicolon
multiline_comment|/* virtual 64bit counter */
DECL|member|rval
id|__u64
id|rval
suffix:semicolon
multiline_comment|/* reset value on overflow */
DECL|member|sig
r_int
id|sig
suffix:semicolon
multiline_comment|/* signal used to notify */
DECL|member|pid
r_int
id|pid
suffix:semicolon
multiline_comment|/* process to notify */
DECL|member|pmu_counters
)brace
id|pmu_counters
(braket
id|IA64_NUM_PMD_COUNTERS
)braket
suffix:semicolon
DECL|macro|INIT_THREAD_PM
macro_line|# define INIT_THREAD_PM&t;&t;{0, }, {0, }, {{ 0, 0, 0, 0}, },
macro_line|#else
DECL|macro|INIT_THREAD_PM
macro_line|# define INIT_THREAD_PM
macro_line|#endif
DECL|member|map_base
id|__u64
id|map_base
suffix:semicolon
multiline_comment|/* base address for get_unmapped_area() */
DECL|member|task_size
id|__u64
id|task_size
suffix:semicolon
multiline_comment|/* limit for task size */
macro_line|#ifdef CONFIG_IA32_SUPPORT
DECL|member|eflag
id|__u64
id|eflag
suffix:semicolon
multiline_comment|/* IA32 EFLAGS reg */
DECL|member|fsr
id|__u64
id|fsr
suffix:semicolon
multiline_comment|/* IA32 floating pt status reg */
DECL|member|fcr
id|__u64
id|fcr
suffix:semicolon
multiline_comment|/* IA32 floating pt control reg */
DECL|member|fir
id|__u64
id|fir
suffix:semicolon
multiline_comment|/* IA32 fp except. instr. reg */
DECL|member|fdr
id|__u64
id|fdr
suffix:semicolon
multiline_comment|/* IA32 fp except. data reg */
DECL|member|csd
id|__u64
id|csd
suffix:semicolon
multiline_comment|/* IA32 code selector descriptor */
DECL|member|ssd
id|__u64
id|ssd
suffix:semicolon
multiline_comment|/* IA32 stack selector descriptor */
DECL|member|tssd
id|__u64
id|tssd
suffix:semicolon
multiline_comment|/* IA32 TSS descriptor */
DECL|member|old_iob
id|__u64
id|old_iob
suffix:semicolon
multiline_comment|/* old IOBase value */
r_union
(brace
DECL|member|sigmask
id|__u64
id|sigmask
suffix:semicolon
multiline_comment|/* aligned mask for sigsuspend scall */
DECL|member|un
)brace
id|un
suffix:semicolon
DECL|macro|INIT_THREAD_IA32
macro_line|# define INIT_THREAD_IA32&t;0, 0, 0x17800000037fULL, 0, 0, 0, 0, 0, 0, {0},
macro_line|#else
DECL|macro|INIT_THREAD_IA32
macro_line|# define INIT_THREAD_IA32
macro_line|#endif /* CONFIG_IA32_SUPPORT */
DECL|member|siginfo
r_struct
id|siginfo
op_star
id|siginfo
suffix:semicolon
multiline_comment|/* current siginfo struct for ptrace() */
)brace
suffix:semicolon
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&amp;init_mm, PAGE_OFFSET, PAGE_OFFSET + 0x10000000, NULL, PAGE_SHARED,&t;&bslash;&n;        VM_READ | VM_WRITE | VM_EXEC, 1, NULL, NULL&t;&t;&t;&t;&bslash;&n;}
DECL|macro|INIT_THREAD
mdefine_line|#define INIT_THREAD {&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;/* ksp */&t;&bslash;&n;&t;0,&t;&t;&t;&t;/* flags */&t;&bslash;&n;&t;{{{{0}}}, },&t;&t;&t;/* fph */&t;&bslash;&n;&t;{0, },&t;&t;&t;&t;/* dbr */&t;&bslash;&n;&t;{0, },&t;&t;&t;&t;/* ibr */&t;&bslash;&n;&t;INIT_THREAD_PM&t;&t;&t;&t;&t;&bslash;&n;&t;0x2000000000000000,&t;&t;/* map_base */&t;&bslash;&n;&t;0xa000000000000000,&t;&t;/* task_size */&t;&bslash;&n;&t;INIT_THREAD_IA32&t;&t;&t;&t;&bslash;&n;&t;0&t;&t;&t;&t;/* siginfo */&t;&bslash;&n;}
DECL|macro|start_thread
mdefine_line|#define start_thread(regs,new_ip,new_sp) do {&t;&t;&t;&t;&t;&bslash;&n;&t;set_fs(USER_DS);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_psr(regs)-&gt;dfh = 1;&t;/* disable fph */&t;&t;&t;&bslash;&n;&t;ia64_psr(regs)-&gt;mfh = 0;&t;/* clear mfh */&t;&t;&t;&t;&bslash;&n;&t;ia64_psr(regs)-&gt;cpl = 3;&t;/* set user mode */&t;&t;&t;&bslash;&n;&t;ia64_psr(regs)-&gt;ri = 0;&t;&t;/* clear return slot number */&t;&t;&bslash;&n;&t;ia64_psr(regs)-&gt;is = 0;&t;&t;/* IA-64 instruction set */&t;&t;&bslash;&n;&t;regs-&gt;cr_iip = new_ip;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;ar_rsc = 0xf;&t;&t;/* eager mode, privilege level 3 */&t;&bslash;&n;&t;regs-&gt;r12 = new_sp - 16;&t;/* allocate 16 byte scratch area */&t;&bslash;&n;&t;regs-&gt;ar_bspstore = IA64_RBS_BOT;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;ar_rnat = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;loadrs = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* Forward declarations, a strange C thing... */
r_struct
id|mm_struct
suffix:semicolon
r_struct
id|task_struct
suffix:semicolon
multiline_comment|/*&n; * Free all resources held by a thread. This is called after the&n; * parent of DEAD_TASK has collected the exist status of the task via&n; * wait().  This is a no-op on IA-64.&n; */
DECL|macro|release_thread
mdefine_line|#define release_thread(dead_task)
multiline_comment|/*&n; * This is the mechanism for creating a new kernel thread.&n; *&n; * NOTE 1: Only a kernel-only process (ie the swapper or direct&n; * descendants who haven&squot;t done an &quot;execve()&quot;) should use this: it&n; * will work within a system call from a &quot;real&quot; process, but the&n; * process memory space will not be free&squot;d until both the parent and&n; * the child have exited.&n; *&n; * NOTE 2: This MUST NOT be an inlined function.  Otherwise, we get&n; * into trouble in init/main.c when the child thread returns to&n; * do_basic_setup() and the timing is such that free_initmem() has&n; * been called already.&n; */
r_extern
r_int
id|kernel_thread
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
multiline_comment|/* Copy and release all segment info associated with a VM */
DECL|macro|copy_segments
mdefine_line|#define copy_segments(tsk, mm)&t;&t;&t;do { } while (0)
DECL|macro|release_segments
mdefine_line|#define release_segments(mm)&t;&t;&t;do { } while (0)
multiline_comment|/* Get wait channel for task P.  */
r_extern
r_int
r_int
id|get_wchan
(paren
r_struct
id|task_struct
op_star
id|p
)paren
suffix:semicolon
multiline_comment|/* Return instruction pointer of blocked task TSK.  */
DECL|macro|KSTK_EIP
mdefine_line|#define KSTK_EIP(tsk)&t;&t;&t;&t;&t;&bslash;&n;  ({&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;struct pt_regs *_regs = ia64_task_regs(tsk);&t;&bslash;&n;&t;_regs-&gt;cr_iip + ia64_psr(_regs)-&gt;ri;&t;&t;&bslash;&n;  })
multiline_comment|/* Return stack pointer of blocked task TSK.  */
DECL|macro|KSTK_ESP
mdefine_line|#define KSTK_ESP(tsk)  ((tsk)-&gt;thread.ksp)
macro_line|#ifndef CONFIG_SMP
r_static
r_inline
r_struct
id|task_struct
op_star
DECL|function|ia64_get_fpu_owner
id|ia64_get_fpu_owner
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|t
suffix:semicolon
id|__asm__
(paren
l_string|&quot;mov %0=ar.k5&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|t
)paren
)paren
suffix:semicolon
r_return
id|t
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_set_fpu_owner
id|ia64_set_fpu_owner
(paren
r_struct
id|task_struct
op_star
id|t
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov ar.k5=%0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|t
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* !CONFIG_SMP */
r_extern
r_void
id|__ia64_init_fpu
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__ia64_save_fpu
(paren
r_struct
id|ia64_fpreg
op_star
id|fph
)paren
suffix:semicolon
r_extern
r_void
id|__ia64_load_fpu
(paren
r_struct
id|ia64_fpreg
op_star
id|fph
)paren
suffix:semicolon
r_extern
r_void
id|ia64_save_debug_regs
(paren
r_int
r_int
op_star
id|save_area
)paren
suffix:semicolon
r_extern
r_void
id|ia64_load_debug_regs
(paren
r_int
r_int
op_star
id|save_area
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IA32_SUPPORT
r_extern
r_void
id|ia32_save_state
(paren
r_struct
id|thread_struct
op_star
id|thread
)paren
suffix:semicolon
r_extern
r_void
id|ia32_load_state
(paren
r_struct
id|thread_struct
op_star
id|thread
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PERFMON
r_extern
r_void
id|ia64_save_pm_regs
(paren
r_struct
id|task_struct
op_star
id|task
)paren
suffix:semicolon
r_extern
r_void
id|ia64_load_pm_regs
(paren
r_struct
id|task_struct
op_star
id|task
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|ia64_fph_enable
mdefine_line|#define ia64_fph_enable()&t;__asm__ __volatile__ (&quot;;; rsm psr.dfh;; srlz.d;;&quot; ::: &quot;memory&quot;);
DECL|macro|ia64_fph_disable
mdefine_line|#define ia64_fph_disable()&t;__asm__ __volatile__ (&quot;;; ssm psr.dfh;; srlz.d;;&quot; ::: &quot;memory&quot;);
multiline_comment|/* load fp 0.0 into fph */
r_static
r_inline
r_void
DECL|function|ia64_init_fpu
id|ia64_init_fpu
(paren
r_void
)paren
(brace
id|ia64_fph_enable
c_func
(paren
)paren
suffix:semicolon
id|__ia64_init_fpu
c_func
(paren
)paren
suffix:semicolon
id|ia64_fph_disable
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* save f32-f127 at FPH */
r_static
r_inline
r_void
DECL|function|ia64_save_fpu
id|ia64_save_fpu
(paren
r_struct
id|ia64_fpreg
op_star
id|fph
)paren
(brace
id|ia64_fph_enable
c_func
(paren
)paren
suffix:semicolon
id|__ia64_save_fpu
c_func
(paren
id|fph
)paren
suffix:semicolon
id|ia64_fph_disable
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* load f32-f127 from FPH */
r_static
r_inline
r_void
DECL|function|ia64_load_fpu
id|ia64_load_fpu
(paren
r_struct
id|ia64_fpreg
op_star
id|fph
)paren
(brace
id|ia64_fph_enable
c_func
(paren
)paren
suffix:semicolon
id|__ia64_load_fpu
c_func
(paren
id|fph
)paren
suffix:semicolon
id|ia64_fph_disable
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_fc
id|ia64_fc
(paren
r_void
op_star
id|addr
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;fc %0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_sync_i
id|ia64_sync_i
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;;; sync.i&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_srlz_i
id|ia64_srlz_i
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;;; srlz.i ;;&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_srlz_d
id|ia64_srlz_d
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;;; srlz.d&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_static
r_inline
id|__u64
DECL|function|ia64_get_rr
id|ia64_get_rr
(paren
id|__u64
id|reg_bits
)paren
(brace
id|__u64
id|r
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov %0=rr[%1]&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|r
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|reg_bits
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_set_rr
id|ia64_set_rr
(paren
id|__u64
id|reg_bits
comma
id|__u64
id|rr_val
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov rr[%0]=%1&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|reg_bits
)paren
comma
l_string|&quot;r&quot;
(paren
id|rr_val
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_static
r_inline
id|__u64
DECL|function|ia64_get_dcr
id|ia64_get_dcr
(paren
r_void
)paren
(brace
id|__u64
id|r
suffix:semicolon
id|__asm__
(paren
l_string|&quot;mov %0=cr.dcr&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_set_dcr
id|ia64_set_dcr
(paren
id|__u64
id|val
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov cr.dcr=%0;;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
id|__u64
DECL|function|ia64_get_lid
id|ia64_get_lid
(paren
r_void
)paren
(brace
id|__u64
id|r
suffix:semicolon
id|__asm__
(paren
l_string|&quot;mov %0=cr.lid&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_invala
id|ia64_invala
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;invala&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Save the processor status flags in FLAGS and then clear the&n; * interrupt collection and interrupt enable bits.&n; */
DECL|macro|ia64_clear_ic
mdefine_line|#define ia64_clear_ic(flags)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__ (&quot;mov %0=psr;; rsm psr.i | psr.ic;; srlz.i;;&quot;&t;&bslash;&n;&t;&t;&t;      : &quot;=r&quot;(flags) :: &quot;memory&quot;);
multiline_comment|/*&n; * Insert a translation into an instruction and/or data translation&n; * register.&n; */
r_static
r_inline
r_void
DECL|function|ia64_itr
id|ia64_itr
(paren
id|__u64
id|target_mask
comma
id|__u64
id|tr_num
comma
id|__u64
id|vmaddr
comma
id|__u64
id|pte
comma
id|__u64
id|log_page_size
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov cr.itir=%0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|log_page_size
op_lshift
l_int|2
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov cr.ifa=%0;;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|vmaddr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|target_mask
op_amp
l_int|0x1
)paren
id|__asm__
id|__volatile__
(paren
l_string|&quot;itr.i itr[%0]=%1&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|tr_num
)paren
comma
l_string|&quot;r&quot;
(paren
id|pte
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|target_mask
op_amp
l_int|0x2
)paren
id|__asm__
id|__volatile__
(paren
l_string|&quot;;;itr.d dtr[%0]=%1&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|tr_num
)paren
comma
l_string|&quot;r&quot;
(paren
id|pte
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Insert a translation into the instruction and/or data translation&n; * cache.&n; */
r_static
r_inline
r_void
DECL|function|ia64_itc
id|ia64_itc
(paren
id|__u64
id|target_mask
comma
id|__u64
id|vmaddr
comma
id|__u64
id|pte
comma
id|__u64
id|log_page_size
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov cr.itir=%0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|log_page_size
op_lshift
l_int|2
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov cr.ifa=%0;;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|vmaddr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
multiline_comment|/* as per EAS2.6, itc must be the last instruction in an instruction group */
r_if
c_cond
(paren
id|target_mask
op_amp
l_int|0x1
)paren
id|__asm__
id|__volatile__
(paren
l_string|&quot;itc.i %0;;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|pte
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|target_mask
op_amp
l_int|0x2
)paren
id|__asm__
id|__volatile__
(paren
l_string|&quot;;;itc.d %0;;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|pte
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Purge a range of addresses from instruction and/or data translation&n; * register(s).&n; */
r_static
r_inline
r_void
DECL|function|ia64_ptr
id|ia64_ptr
(paren
id|__u64
id|target_mask
comma
id|__u64
id|vmaddr
comma
id|__u64
id|log_size
)paren
(brace
r_if
c_cond
(paren
id|target_mask
op_amp
l_int|0x1
)paren
id|__asm__
id|__volatile__
(paren
l_string|&quot;ptr.i %0,%1&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|vmaddr
)paren
comma
l_string|&quot;r&quot;
(paren
id|log_size
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|target_mask
op_amp
l_int|0x2
)paren
id|__asm__
id|__volatile__
(paren
l_string|&quot;ptr.d %0,%1&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|vmaddr
)paren
comma
l_string|&quot;r&quot;
(paren
id|log_size
op_lshift
l_int|2
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Set the interrupt vector address.  The address must be suitably aligned (32KB).  */
r_static
r_inline
r_void
DECL|function|ia64_set_iva
id|ia64_set_iva
(paren
r_void
op_star
id|ivt_addr
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov cr.iva=%0;; srlz.i;;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|ivt_addr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Set the page table address and control bits.  */
r_static
r_inline
r_void
DECL|function|ia64_set_pta
id|ia64_set_pta
(paren
id|__u64
id|pta
)paren
(brace
multiline_comment|/* Note: srlz.i implies srlz.d */
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov cr.pta=%0;; srlz.i;;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|pta
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_static
r_inline
id|__u64
DECL|function|ia64_get_cpuid
id|ia64_get_cpuid
(paren
id|__u64
id|regnum
)paren
(brace
id|__u64
id|r
suffix:semicolon
id|__asm__
(paren
l_string|&quot;mov %0=cpuid[%r1]&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|r
)paren
suffix:colon
l_string|&quot;rO&quot;
(paren
id|regnum
)paren
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_eoi
id|ia64_eoi
(paren
r_void
)paren
(brace
id|__asm__
(paren
l_string|&quot;mov cr.eoi=r0;; srlz.d;;&quot;
op_scope_resolution
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_set_lrr0
id|ia64_set_lrr0
(paren
id|__u8
id|vector
comma
id|__u8
id|masked
)paren
(brace
r_if
c_cond
(paren
id|masked
OG
l_int|1
)paren
id|masked
op_assign
l_int|1
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov cr.lrr0=%0;; srlz.d&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
(paren
id|masked
op_lshift
l_int|16
)paren
op_or
id|vector
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_set_lrr1
id|ia64_set_lrr1
(paren
id|__u8
id|vector
comma
id|__u8
id|masked
)paren
(brace
r_if
c_cond
(paren
id|masked
OG
l_int|1
)paren
id|masked
op_assign
l_int|1
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov cr.lrr1=%0;; srlz.d&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
(paren
id|masked
op_lshift
l_int|16
)paren
op_or
id|vector
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_set_pmv
id|ia64_set_pmv
(paren
id|__u64
id|val
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov cr.pmv=%0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_static
r_inline
id|__u64
DECL|function|ia64_get_pmc
id|ia64_get_pmc
(paren
id|__u64
id|regnum
)paren
(brace
id|__u64
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov %0=pmc[%1]&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|regnum
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_set_pmc
id|ia64_set_pmc
(paren
id|__u64
id|regnum
comma
id|__u64
id|value
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov pmc[%0]=%1&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|regnum
)paren
comma
l_string|&quot;r&quot;
(paren
id|value
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
id|__u64
DECL|function|ia64_get_pmd
id|ia64_get_pmd
(paren
id|__u64
id|regnum
)paren
(brace
id|__u64
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov %0=pmd[%1]&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|regnum
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_set_pmd
id|ia64_set_pmd
(paren
id|__u64
id|regnum
comma
id|__u64
id|value
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov pmd[%0]=%1&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|regnum
)paren
comma
l_string|&quot;r&quot;
(paren
id|value
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Given the address to which a spill occurred, return the unat bit&n; * number that corresponds to this address.&n; */
r_static
r_inline
id|__u64
DECL|function|ia64_unat_pos
id|ia64_unat_pos
(paren
r_void
op_star
id|spill_addr
)paren
(brace
r_return
(paren
(paren
id|__u64
)paren
id|spill_addr
op_rshift
l_int|3
)paren
op_amp
l_int|0x3f
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the NaT bit of an integer register which was spilled at address&n; * SPILL_ADDR.  UNAT is the mask to be updated.&n; */
r_static
r_inline
r_void
DECL|function|ia64_set_unat
id|ia64_set_unat
(paren
id|__u64
op_star
id|unat
comma
r_void
op_star
id|spill_addr
comma
r_int
r_int
id|nat
)paren
(brace
id|__u64
id|bit
op_assign
id|ia64_unat_pos
c_func
(paren
id|spill_addr
)paren
suffix:semicolon
id|__u64
id|mask
op_assign
l_int|1UL
op_lshift
id|bit
suffix:semicolon
op_star
id|unat
op_assign
(paren
op_star
id|unat
op_amp
op_complement
id|mask
)paren
op_or
(paren
id|nat
op_lshift
id|bit
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Return saved PC of a blocked thread.&n; * Note that the only way T can block is through a call to schedule() -&gt; switch_to().&n; */
r_static
r_inline
r_int
r_int
DECL|function|thread_saved_pc
id|thread_saved_pc
(paren
r_struct
id|thread_struct
op_star
id|t
)paren
(brace
r_struct
id|unw_frame_info
id|info
suffix:semicolon
r_int
r_int
id|ip
suffix:semicolon
multiline_comment|/* XXX ouch: Linus, please pass the task pointer to thread_saved_pc() instead! */
r_struct
id|task_struct
op_star
id|p
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|t
op_minus
id|IA64_TASK_THREAD_OFFSET
)paren
suffix:semicolon
id|unw_init_from_blocked_task
c_func
(paren
op_amp
id|info
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unw_unwind
c_func
(paren
op_amp
id|info
)paren
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|unw_get_ip
c_func
(paren
op_amp
id|info
comma
op_amp
id|ip
)paren
suffix:semicolon
r_return
id|ip
suffix:semicolon
)brace
multiline_comment|/*&n; * Get the current instruction/program counter value.&n; */
DECL|macro|current_text_addr
mdefine_line|#define current_text_addr() &bslash;&n;&t;({ void *_pc; __asm__ (&quot;mov %0=ip&quot; : &quot;=r&quot; (_pc)); _pc; })
DECL|macro|THREAD_SIZE
mdefine_line|#define THREAD_SIZE&t;IA64_STK_OFFSET
multiline_comment|/* NOTE: The task struct and the stacks are allocated together.  */
DECL|macro|alloc_task_struct
mdefine_line|#define alloc_task_struct() &bslash;&n;        ((struct task_struct *) __get_free_pages(GFP_KERNEL, IA64_TASK_STRUCT_LOG_NUM_PAGES))
DECL|macro|free_task_struct
mdefine_line|#define free_task_struct(p)     free_pages((unsigned long)(p), IA64_TASK_STRUCT_LOG_NUM_PAGES)
DECL|macro|get_task_struct
mdefine_line|#define get_task_struct(tsk)&t;atomic_inc(&amp;virt_to_page(tsk)-&gt;count)
DECL|macro|init_task
mdefine_line|#define init_task&t;(init_task_union.task)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;(init_task_union.stack)
multiline_comment|/*&n; * Set the correctable machine check vector register&n; */
r_static
r_inline
r_void
DECL|function|ia64_set_cmcv
id|ia64_set_cmcv
(paren
id|__u64
id|val
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov cr.cmcv=%0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read the correctable machine check vector register&n; */
r_static
r_inline
id|__u64
DECL|function|ia64_get_cmcv
id|ia64_get_cmcv
(paren
r_void
)paren
(brace
id|__u64
id|val
suffix:semicolon
id|__asm__
(paren
l_string|&quot;mov %0=cr.cmcv&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
op_scope_resolution
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
r_static
r_inline
id|__u64
DECL|function|ia64_get_ivr
id|ia64_get_ivr
(paren
r_void
)paren
(brace
id|__u64
id|r
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;srlz.d;; mov %0=cr.ivr;; srlz.d;;&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_set_tpr
id|ia64_set_tpr
(paren
id|__u64
id|val
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;mov cr.tpr=%0&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
id|__u64
DECL|function|ia64_get_tpr
id|ia64_get_tpr
(paren
r_void
)paren
(brace
id|__u64
id|r
suffix:semicolon
id|__asm__
(paren
l_string|&quot;mov %0=cr.tpr&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|r
)paren
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_set_irr0
id|ia64_set_irr0
(paren
id|__u64
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov cr.irr0=%0;;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
id|__u64
DECL|function|ia64_get_irr0
id|ia64_get_irr0
(paren
r_void
)paren
(brace
id|__u64
id|val
suffix:semicolon
multiline_comment|/* this is volatile because irr may change unbeknownst to gcc... */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov %0=cr.irr0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_set_irr1
id|ia64_set_irr1
(paren
id|__u64
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov cr.irr1=%0;;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
id|__u64
DECL|function|ia64_get_irr1
id|ia64_get_irr1
(paren
r_void
)paren
(brace
id|__u64
id|val
suffix:semicolon
multiline_comment|/* this is volatile because irr may change unbeknownst to gcc... */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov %0=cr.irr1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_set_irr2
id|ia64_set_irr2
(paren
id|__u64
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov cr.irr2=%0;;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
id|__u64
DECL|function|ia64_get_irr2
id|ia64_get_irr2
(paren
r_void
)paren
(brace
id|__u64
id|val
suffix:semicolon
multiline_comment|/* this is volatile because irr may change unbeknownst to gcc... */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov %0=cr.irr2&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ia64_set_irr3
id|ia64_set_irr3
(paren
id|__u64
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov cr.irr3=%0;;&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|val
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|ia64_srlz_d
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
id|__u64
DECL|function|ia64_get_irr3
id|ia64_get_irr3
(paren
r_void
)paren
(brace
id|__u64
id|val
suffix:semicolon
multiline_comment|/* this is volatile because irr may change unbeknownst to gcc... */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;mov %0=cr.irr3&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
r_static
r_inline
id|__u64
DECL|function|ia64_get_gp
id|ia64_get_gp
c_func
(paren
r_void
)paren
(brace
id|__u64
id|val
suffix:semicolon
id|__asm__
(paren
l_string|&quot;mov %0=gp&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/* XXX remove the handcoded version once we have a sufficiently clever compiler... */
macro_line|#ifdef SMART_COMPILER
DECL|macro|ia64_rotr
macro_line|# define ia64_rotr(w,n)&t;&t;&t;&t;&bslash;&n;  ({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 _w = (w), _n = (n);&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(_w &gt;&gt; _n) | (_w &lt;&lt; (64 - _n));&t;&t;&bslash;&n;  })
macro_line|#else
DECL|macro|ia64_rotr
macro_line|# define ia64_rotr(w,n)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  ({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__u64 result;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;asm (&quot;shrp %0=%1,%1,%2&quot; : &quot;=r&quot;(result) : &quot;r&quot;(w), &quot;i&quot;(n));&t;&bslash;&n;&t;result;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;  })
macro_line|#endif
DECL|macro|ia64_rotl
mdefine_line|#define ia64_rotl(w,n)&t;ia64_rotr((w),(64)-(n))
r_static
r_inline
id|__u64
DECL|function|ia64_thash
id|ia64_thash
(paren
id|__u64
id|addr
)paren
(brace
id|__u64
id|result
suffix:semicolon
id|asm
(paren
l_string|&quot;thash %0=%1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|result
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_IA64_PROCESSOR_H */
eof
