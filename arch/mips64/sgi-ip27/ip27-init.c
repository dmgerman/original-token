macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;&t;/* for numnodes */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/sn0/addrs.h&gt;
macro_line|#include &lt;asm/sn/sn0/hubni.h&gt;
macro_line|#include &lt;asm/sn/sn0/hubio.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/ioc3.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/sn/gda.h&gt;
macro_line|#include &lt;asm/sn/intr.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/sn/launch.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
macro_line|#include &lt;asm/sn/sn0/ip27.h&gt;
DECL|macro|CPU_NONE
mdefine_line|#define CPU_NONE&t;&t;(cpuid_t)-1
DECL|macro|CPUMASK_CLRALL
mdefine_line|#define&t;CPUMASK_CLRALL(p)&t;(p) = 0
DECL|macro|CPUMASK_SETB
mdefine_line|#define CPUMASK_SETB(p, bit)&t;(p) |= 1 &lt;&lt; (bit)
DECL|macro|CPUMASK_CLRB
mdefine_line|#define CPUMASK_CLRB(p, bit)&t;(p) &amp;= ~(1ULL &lt;&lt; (bit))
DECL|macro|CPUMASK_TSTB
mdefine_line|#define CPUMASK_TSTB(p, bit)&t;((p) &amp; (1ULL &lt;&lt; (bit)))
DECL|macro|CNODEMASK_CLRALL
mdefine_line|#define CNODEMASK_CLRALL(p)&t;(p) = 0
DECL|macro|CNODEMASK_TSTB
mdefine_line|#define CNODEMASK_TSTB(p, bit)&t;((p) &amp; (1ULL &lt;&lt; (bit)))
DECL|macro|CNODEMASK_SETB
mdefine_line|#define CNODEMASK_SETB(p, bit)&t;((p) |= 1ULL &lt;&lt; (bit))
DECL|variable|boot_cpumask
id|cpumask_t
id|boot_cpumask
suffix:semicolon
DECL|variable|boot_barrier
r_static
r_volatile
id|cpumask_t
id|boot_barrier
suffix:semicolon
DECL|variable|region_mask
id|hubreg_t
id|region_mask
op_assign
l_int|0
suffix:semicolon
DECL|variable|fine_mode
r_static
r_int
id|fine_mode
op_assign
l_int|0
suffix:semicolon
DECL|variable|maxcpus
r_int
id|maxcpus
suffix:semicolon
DECL|variable|hub_mask_lock
r_static
id|spinlock_t
id|hub_mask_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|hub_init_mask
r_static
id|cnodemask_t
id|hub_init_mask
suffix:semicolon
DECL|variable|nasid_to_compact_node
id|cnodeid_t
id|nasid_to_compact_node
(braket
id|MAX_NASIDS
)braket
suffix:semicolon
DECL|variable|compact_to_nasid_node
id|nasid_t
id|compact_to_nasid_node
(braket
id|MAX_COMPACT_NODES
)braket
suffix:semicolon
DECL|variable|cpuid_to_compact_node
id|cnodeid_t
id|cpuid_to_compact_node
(braket
id|MAXCPUS
)braket
suffix:semicolon
DECL|function|get_region
id|hubreg_t
id|get_region
c_func
(paren
id|cnodeid_t
id|cnode
)paren
(brace
r_if
c_cond
(paren
id|fine_mode
)paren
r_return
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|cnode
)paren
op_rshift
id|NASID_TO_FINEREG_SHFT
suffix:semicolon
r_else
r_return
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|cnode
)paren
op_rshift
id|NASID_TO_COARSEREG_SHFT
suffix:semicolon
)brace
DECL|function|gen_region_mask
r_static
r_void
id|gen_region_mask
c_func
(paren
id|hubreg_t
op_star
id|region_mask
comma
r_int
id|maxnodes
)paren
(brace
id|cnodeid_t
id|cnode
suffix:semicolon
(paren
op_star
id|region_mask
)paren
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|cnode
op_assign
l_int|0
suffix:semicolon
id|cnode
OL
id|maxnodes
suffix:semicolon
id|cnode
op_increment
)paren
(brace
(paren
op_star
id|region_mask
)paren
op_or_assign
l_int|1ULL
op_lshift
id|get_region
c_func
(paren
id|cnode
)paren
suffix:semicolon
)brace
)brace
DECL|function|is_fine_dirmode
r_int
id|is_fine_dirmode
c_func
(paren
r_void
)paren
(brace
r_return
(paren
(paren
(paren
id|LOCAL_HUB_L
c_func
(paren
id|NI_STATUS_REV_ID
)paren
op_amp
id|NSRI_REGIONSIZE_MASK
)paren
op_rshift
id|NSRI_REGIONSIZE_SHFT
)paren
op_amp
id|REGIONSIZE_FINE
)paren
suffix:semicolon
)brace
DECL|function|get_actual_nasid
id|nasid_t
id|get_actual_nasid
c_func
(paren
id|lboard_t
op_star
id|brd
)paren
(brace
id|klhub_t
op_star
id|hub
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|brd
)paren
r_return
id|INVALID_NASID
suffix:semicolon
multiline_comment|/* find out if we are a completely disabled brd. */
id|hub
op_assign
(paren
id|klhub_t
op_star
)paren
id|find_first_component
c_func
(paren
id|brd
comma
id|KLSTRUCT_HUB
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hub
)paren
r_return
id|INVALID_NASID
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|hub-&gt;hub_info.flags
op_amp
id|KLINFO_ENABLE
)paren
)paren
multiline_comment|/* disabled node brd */
r_return
id|hub-&gt;hub_info.physid
suffix:semicolon
r_else
r_return
id|brd-&gt;brd_nasid
suffix:semicolon
)brace
DECL|function|do_cpumask
r_int
id|do_cpumask
c_func
(paren
id|cnodeid_t
id|cnode
comma
id|nasid_t
id|nasid
comma
id|cpumask_t
op_star
id|boot_cpumask
comma
r_int
op_star
id|highest
)paren
(brace
id|lboard_t
op_star
id|brd
suffix:semicolon
id|klcpu_t
op_star
id|acpu
suffix:semicolon
r_int
id|cpus_found
op_assign
l_int|0
suffix:semicolon
id|cpuid_t
id|cpuid
suffix:semicolon
id|brd
op_assign
id|find_lboard
c_func
(paren
(paren
id|lboard_t
op_star
)paren
id|KL_CONFIG_INFO
c_func
(paren
id|nasid
)paren
comma
id|KLTYPE_IP27
)paren
suffix:semicolon
r_do
(brace
id|acpu
op_assign
(paren
id|klcpu_t
op_star
)paren
id|find_first_component
c_func
(paren
id|brd
comma
id|KLSTRUCT_CPU
)paren
suffix:semicolon
r_while
c_loop
(paren
id|acpu
)paren
(brace
id|cpuid
op_assign
id|acpu-&gt;cpu_info.virtid
suffix:semicolon
multiline_comment|/* cnode is not valid for completely disabled brds */
r_if
c_cond
(paren
id|get_actual_nasid
c_func
(paren
id|brd
)paren
op_eq
id|brd-&gt;brd_nasid
)paren
id|cpuid_to_compact_node
(braket
id|cpuid
)braket
op_assign
id|cnode
suffix:semicolon
r_if
c_cond
(paren
id|cpuid
OG
op_star
id|highest
)paren
op_star
id|highest
op_assign
id|cpuid
suffix:semicolon
multiline_comment|/* Only let it join in if it&squot;s marked enabled */
r_if
c_cond
(paren
id|acpu-&gt;cpu_info.flags
op_amp
id|KLINFO_ENABLE
)paren
(brace
id|CPUMASK_SETB
c_func
(paren
op_star
id|boot_cpumask
comma
id|cpuid
)paren
suffix:semicolon
id|cpus_found
op_increment
suffix:semicolon
)brace
id|acpu
op_assign
(paren
id|klcpu_t
op_star
)paren
id|find_component
c_func
(paren
id|brd
comma
(paren
id|klinfo_t
op_star
)paren
id|acpu
comma
id|KLSTRUCT_CPU
)paren
suffix:semicolon
)brace
id|brd
op_assign
id|KLCF_NEXT
c_func
(paren
id|brd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|brd
)paren
id|brd
op_assign
id|find_lboard
c_func
(paren
id|brd
comma
id|KLTYPE_IP27
)paren
suffix:semicolon
r_else
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
id|brd
)paren
suffix:semicolon
r_return
id|cpus_found
suffix:semicolon
)brace
DECL|function|cpu_node_probe
id|cpuid_t
id|cpu_node_probe
c_func
(paren
id|cpumask_t
op_star
id|boot_cpumask
comma
r_int
op_star
id|numnodes
)paren
(brace
r_int
id|i
comma
id|cpus
op_assign
l_int|0
comma
id|highest
op_assign
l_int|0
suffix:semicolon
id|gda_t
op_star
id|gdap
op_assign
id|GDA
suffix:semicolon
id|nasid_t
id|nasid
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize the arrays to invalid nodeid (-1)&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_COMPACT_NODES
suffix:semicolon
id|i
op_increment
)paren
id|compact_to_nasid_node
(braket
id|i
)braket
op_assign
id|INVALID_NASID
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_NASIDS
suffix:semicolon
id|i
op_increment
)paren
id|nasid_to_compact_node
(braket
id|i
)braket
op_assign
id|INVALID_CNODEID
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAXCPUS
suffix:semicolon
id|i
op_increment
)paren
id|cpuid_to_compact_node
(braket
id|i
)braket
op_assign
id|INVALID_CNODEID
suffix:semicolon
op_star
id|numnodes
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_COMPACT_NODES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|nasid
op_assign
id|gdap-&gt;g_nasidtable
(braket
id|i
)braket
)paren
op_eq
id|INVALID_NASID
)paren
(brace
r_break
suffix:semicolon
)brace
r_else
(brace
id|compact_to_nasid_node
(braket
id|i
)braket
op_assign
id|nasid
suffix:semicolon
id|nasid_to_compact_node
(braket
id|nasid
)braket
op_assign
id|i
suffix:semicolon
(paren
op_star
id|numnodes
)paren
op_increment
suffix:semicolon
id|cpus
op_add_assign
id|do_cpumask
c_func
(paren
id|i
comma
id|nasid
comma
id|boot_cpumask
comma
op_amp
id|highest
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Cpus are numbered in order of cnodes. Currently, disabled&n;&t; * cpus are not numbered.&n;&t; */
r_return
id|highest
op_plus
l_int|1
suffix:semicolon
)brace
DECL|function|alloc_cpupda
r_void
id|alloc_cpupda
c_func
(paren
r_int
id|i
)paren
(brace
id|cnodeid_t
id|node
suffix:semicolon
id|nasid_t
id|nasid
suffix:semicolon
id|node
op_assign
id|get_cpu_cnode
c_func
(paren
id|i
)paren
suffix:semicolon
id|nasid
op_assign
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|node
)paren
suffix:semicolon
id|cputonasid
c_func
(paren
id|i
)paren
op_assign
id|nasid
suffix:semicolon
id|cputocnode
c_func
(paren
id|i
)paren
op_assign
id|node
suffix:semicolon
id|cputoslice
c_func
(paren
id|i
)paren
op_assign
id|get_cpu_slice
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
DECL|function|cpu_enabled
r_int
id|cpu_enabled
c_func
(paren
id|cpuid_t
id|cpu
)paren
(brace
r_if
c_cond
(paren
id|cpu
op_eq
id|CPU_NONE
)paren
r_return
l_int|0
suffix:semicolon
r_return
(paren
id|CPUMASK_TSTB
c_func
(paren
id|boot_cpumask
comma
id|cpu
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|initpdas
r_void
id|initpdas
c_func
(paren
r_void
)paren
(brace
id|cpuid_t
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|maxcpus
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|cpu_enabled
c_func
(paren
id|i
)paren
)paren
id|alloc_cpupda
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
DECL|function|mlreset
r_void
id|mlreset
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|fine_mode
op_assign
id|is_fine_dirmode
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Probe for all CPUs - this creates the cpumask and&n;&t; * sets up the mapping tables.&n;&t; */
id|CPUMASK_CLRALL
c_func
(paren
id|boot_cpumask
)paren
suffix:semicolon
id|maxcpus
op_assign
id|cpu_node_probe
c_func
(paren
op_amp
id|boot_cpumask
comma
op_amp
id|numnodes
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Discovered %d cpus on %d nodes&bslash;n&quot;
comma
id|maxcpus
comma
id|numnodes
)paren
suffix:semicolon
id|initpdas
c_func
(paren
)paren
suffix:semicolon
id|gen_region_mask
c_func
(paren
op_amp
id|region_mask
comma
id|numnodes
)paren
suffix:semicolon
id|CNODEMASK_CLRALL
c_func
(paren
id|hub_init_mask
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Set all nodes&squot; calias sizes to 8k&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|numnodes
suffix:semicolon
id|i
op_increment
)paren
(brace
id|nasid_t
id|nasid
suffix:semicolon
id|nasid
op_assign
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|i
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Always have node 0 in the region mask, otherwise&n;&t;&t; * CALIAS accesses get exceptions since the hub&n;&t;&t; * thinks it is a node 0 address.&n;&t;&t; */
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|PI_REGION_PRESENT
comma
(paren
id|region_mask
op_or
l_int|1
)paren
)paren
suffix:semicolon
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|PI_CALIAS_SIZE
comma
id|PI_CALIAS_SIZE_0
)paren
suffix:semicolon
macro_line|#ifdef LATER
multiline_comment|/*&n;&t;&t; * Set up all hubs to have a big window pointing at&n;&t;&t; * widget 0. Memory mode, widget 0, offset 0&n;&t;&t; */
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|IIO_ITTE
c_func
(paren
id|SWIN0_BIGWIN
)paren
comma
(paren
(paren
id|HUB_PIO_MAP_TO_MEM
op_lshift
id|IIO_ITTE_IOSP_SHIFT
)paren
op_or
(paren
l_int|0
op_lshift
id|IIO_ITTE_WIDGET_SHIFT
)paren
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
DECL|function|intr_clear_bits
r_void
id|intr_clear_bits
c_func
(paren
id|nasid_t
id|nasid
comma
r_volatile
id|hubreg_t
op_star
id|pend
comma
r_int
id|base_level
comma
r_char
op_star
id|name
)paren
(brace
r_volatile
id|hubreg_t
id|bits
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Check pending interrupts */
r_if
c_cond
(paren
(paren
id|bits
op_assign
id|HUB_L
c_func
(paren
id|pend
)paren
)paren
op_ne
l_int|0
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|N_INTPEND_BITS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|bits
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
id|LOCAL_HUB_CLR_INTR
c_func
(paren
id|base_level
op_plus
id|i
)paren
suffix:semicolon
)brace
DECL|function|intr_clear_all
r_void
id|intr_clear_all
c_func
(paren
id|nasid_t
id|nasid
)paren
(brace
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|PI_INT_MASK0_A
comma
l_int|0
)paren
suffix:semicolon
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|PI_INT_MASK0_B
comma
l_int|0
)paren
suffix:semicolon
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|PI_INT_MASK1_A
comma
l_int|0
)paren
suffix:semicolon
id|REMOTE_HUB_S
c_func
(paren
id|nasid
comma
id|PI_INT_MASK1_B
comma
l_int|0
)paren
suffix:semicolon
id|intr_clear_bits
c_func
(paren
id|nasid
comma
id|REMOTE_HUB_ADDR
c_func
(paren
id|nasid
comma
id|PI_INT_PEND0
)paren
comma
id|INT_PEND0_BASELVL
comma
l_string|&quot;INT_PEND0&quot;
)paren
suffix:semicolon
id|intr_clear_bits
c_func
(paren
id|nasid
comma
id|REMOTE_HUB_ADDR
c_func
(paren
id|nasid
comma
id|PI_INT_PEND1
)paren
comma
id|INT_PEND1_BASELVL
comma
l_string|&quot;INT_PEND1&quot;
)paren
suffix:semicolon
)brace
DECL|function|sn_mp_setup
r_void
id|sn_mp_setup
c_func
(paren
r_void
)paren
(brace
id|cnodeid_t
id|cnode
suffix:semicolon
macro_line|#if 0
id|cpuid_t
id|cpu
suffix:semicolon
macro_line|#endif
r_for
c_loop
(paren
id|cnode
op_assign
l_int|0
suffix:semicolon
id|cnode
OL
id|numnodes
suffix:semicolon
id|cnode
op_increment
)paren
(brace
macro_line|#if 0
id|init_platform_nodepda
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|intr_clear_all
c_func
(paren
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|cnode
)paren
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|maxcpus
suffix:semicolon
id|cpu
op_increment
)paren
(brace
id|init_platform_pda
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|per_hub_init
r_void
id|per_hub_init
c_func
(paren
id|cnodeid_t
id|cnode
)paren
(brace
id|cnodemask_t
id|done
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|hub_mask_lock
)paren
suffix:semicolon
multiline_comment|/* Test our bit. */
r_if
c_cond
(paren
op_logical_neg
(paren
id|done
op_assign
id|CNODEMASK_TSTB
c_func
(paren
id|hub_init_mask
comma
id|cnode
)paren
)paren
)paren
(brace
multiline_comment|/* Turn our bit on in the mask. */
id|CNODEMASK_SETB
c_func
(paren
id|hub_init_mask
comma
id|cnode
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|hub_mask_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Do the actual initialization if it hasn&squot;t been done yet.&n;&t; * We don&squot;t need to hold a lock for this work.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|done
)paren
(brace
id|hub_rtc_init
c_func
(paren
id|cnode
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This is similar to hard_smp_processor_id().&n; */
DECL|function|getcpuid
id|cpuid_t
id|getcpuid
c_func
(paren
r_void
)paren
(brace
id|klcpu_t
op_star
id|klcpu
suffix:semicolon
id|klcpu
op_assign
id|nasid_slice_to_cpuinfo
c_func
(paren
id|get_nasid
c_func
(paren
)paren
comma
id|LOCAL_HUB_L
c_func
(paren
id|PI_CPU_NUM
)paren
)paren
suffix:semicolon
r_return
id|klcpu-&gt;cpu_info.virtid
suffix:semicolon
)brace
DECL|function|per_cpu_init
r_void
id|per_cpu_init
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|install_cpu_nmi_handler
c_func
(paren
r_int
id|slice
)paren
suffix:semicolon
r_extern
r_void
id|load_mmu
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|is_slave
op_assign
l_int|0
suffix:semicolon
id|cpuid_t
id|cpu
op_assign
id|getcpuid
c_func
(paren
)paren
suffix:semicolon
id|cnodeid_t
id|cnode
op_assign
id|get_compact_nodeid
c_func
(paren
)paren
suffix:semicolon
id|current_cpu_data.asid_cache
op_assign
id|ASID_FIRST_VERSION
suffix:semicolon
macro_line|#if 0
id|intr_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|set_cp0_status
c_func
(paren
id|ST0_IM
comma
l_int|0
)paren
suffix:semicolon
id|per_hub_init
c_func
(paren
id|cnode
)paren
suffix:semicolon
id|cpu_time_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
multiline_comment|/* master can&squot;t do this early, no kmalloc */
id|install_cpuintr
c_func
(paren
id|cpu
)paren
suffix:semicolon
multiline_comment|/* Install our NMI handler if symmon hasn&squot;t installed one. */
id|install_cpu_nmi_handler
c_func
(paren
id|cputoslice
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
macro_line|#if 0
id|install_tlbintr
c_func
(paren
id|cpu
)paren
suffix:semicolon
macro_line|#endif
id|set_cp0_status
c_func
(paren
id|SRB_DEV0
op_or
id|SRB_DEV1
comma
id|SRB_DEV0
op_or
id|SRB_DEV1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|is_slave
)paren
(brace
id|set_cp0_status
c_func
(paren
id|ST0_BEV
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mips4_available
)paren
id|set_cp0_status
c_func
(paren
id|ST0_XX
comma
id|ST0_XX
)paren
suffix:semicolon
id|set_cp0_status
c_func
(paren
id|ST0_KX
op_or
id|ST0_SX
op_or
id|ST0_UX
comma
id|ST0_KX
op_or
id|ST0_SX
op_or
id|ST0_UX
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
id|load_mmu
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|is_slave
op_eq
l_int|0
)paren
id|is_slave
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|get_compact_nodeid
id|cnodeid_t
id|get_compact_nodeid
c_func
(paren
r_void
)paren
(brace
id|nasid_t
id|nasid
suffix:semicolon
id|nasid
op_assign
id|get_nasid
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Map the physical node id to a virtual node id (virtual node ids&n;&t; * are contiguous).&n;&t; */
r_return
id|NASID_TO_COMPACT_NODEID
c_func
(paren
id|nasid
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
DECL|function|smp_callin
r_void
id|__init
id|smp_callin
c_func
(paren
r_void
)paren
(brace
macro_line|#if 0
id|calibrate_delay
c_func
(paren
)paren
suffix:semicolon
id|smp_store_cpu_info
c_func
(paren
id|cpuid
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|start_secondary
r_int
id|__init
id|start_secondary
c_func
(paren
r_void
)paren
(brace
r_extern
r_int
id|cpu_idle
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|atomic_t
id|smp_commenced
suffix:semicolon
id|smp_callin
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|atomic_read
c_func
(paren
op_amp
id|smp_commenced
)paren
)paren
suffix:semicolon
r_return
id|cpu_idle
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|numstarted
r_static
id|atomic_t
id|numstarted
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|0
)paren
suffix:semicolon
DECL|function|cboot
r_void
id|cboot
c_func
(paren
r_void
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|numstarted
)paren
suffix:semicolon
id|CPUMASK_CLRB
c_func
(paren
id|boot_barrier
comma
id|getcpuid
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* needs atomicity */
id|per_cpu_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#if 0
id|ecc_init
c_func
(paren
)paren
suffix:semicolon
id|bte_lateinit
c_func
(paren
)paren
suffix:semicolon
id|init_mfhi_war
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|_flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|start_secondary
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|allowboot
r_void
id|allowboot
c_func
(paren
r_void
)paren
(brace
r_int
id|num_cpus
op_assign
l_int|0
suffix:semicolon
id|cpuid_t
id|cpu
suffix:semicolon
id|cnodeid_t
id|cnode
suffix:semicolon
r_extern
r_void
id|bootstrap
c_func
(paren
r_void
)paren
suffix:semicolon
id|sn_mp_setup
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Master has already done per_cpu_init() */
id|install_cpuintr
c_func
(paren
id|getcpuid
c_func
(paren
)paren
)paren
suffix:semicolon
macro_line|#if 0
id|bte_lateinit
c_func
(paren
)paren
suffix:semicolon
id|ecc_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|boot_barrier
op_assign
id|boot_cpumask
suffix:semicolon
multiline_comment|/* Launch slaves. */
r_for
c_loop
(paren
id|cpu
op_assign
l_int|0
suffix:semicolon
id|cpu
OL
id|maxcpus
suffix:semicolon
id|cpu
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cpu
op_eq
id|smp_processor_id
c_func
(paren
)paren
)paren
(brace
id|num_cpus
op_increment
suffix:semicolon
multiline_comment|/* We&squot;re already started, clear our bit */
id|CPUMASK_CLRB
c_func
(paren
id|boot_barrier
comma
id|cpu
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* Skip holes in CPU space */
r_if
c_cond
(paren
id|CPUMASK_TSTB
c_func
(paren
id|boot_cpumask
comma
id|cpu
)paren
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * The following code is purely to make sure&n;&t;&t;&t; * Linux can schedule processes on this slave.&n;&t;&t;&t; */
id|kernel_thread
c_func
(paren
l_int|0
comma
l_int|NULL
comma
id|CLONE_PID
)paren
suffix:semicolon
id|p
op_assign
id|init_task.prev_task
suffix:semicolon
id|sprintf
c_func
(paren
id|p-&gt;comm
comma
l_string|&quot;%s%d&quot;
comma
l_string|&quot;Idle&quot;
comma
id|num_cpus
)paren
suffix:semicolon
id|init_tasks
(braket
id|num_cpus
)braket
op_assign
id|p
suffix:semicolon
id|p-&gt;processor
op_assign
id|num_cpus
suffix:semicolon
id|p-&gt;has_cpu
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* we schedule the first task manually */
id|del_from_runqueue
c_func
(paren
id|p
)paren
suffix:semicolon
id|unhash_process
c_func
(paren
id|p
)paren
suffix:semicolon
multiline_comment|/* Attach to the address space of init_task. */
id|atomic_inc
c_func
(paren
op_amp
id|init_mm.mm_count
)paren
suffix:semicolon
id|p-&gt;active_mm
op_assign
op_amp
id|init_mm
suffix:semicolon
multiline_comment|/*&n;&t;&t; &t; * Launch a slave into bootstrap().&n;&t;&t; &t; * It doesn&squot;t take an argument, and we&n;&t;&t;&t; * set sp to the kernel stack of the newly &n;&t;&t;&t; * created idle process, gp to the proc struct&n;&t;&t;&t; * (so that current-&gt; works).&n;&t;&t; &t; */
id|LAUNCH_SLAVE
c_func
(paren
id|cputonasid
c_func
(paren
id|cpu
)paren
comma
id|cputoslice
c_func
(paren
id|cpu
)paren
comma
(paren
id|launch_proc_t
)paren
id|bootstrap
comma
l_int|0
comma
(paren
r_void
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|p
op_plus
id|KERNEL_STACK_SIZE
op_minus
l_int|32
)paren
comma
(paren
r_void
op_star
)paren
id|p
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Now optimistically set the mapping arrays. We&n;&t;&t;&t; * need to wait here, verify the cpu booted up, then&n;&t;&t;&t; * fire up the next cpu.&n;&t;&t;&t; */
id|__cpu_number_map
(braket
id|cpu
)braket
op_assign
id|num_cpus
suffix:semicolon
id|__cpu_logical_map
(braket
id|num_cpus
)braket
op_assign
id|cpu
suffix:semicolon
id|num_cpus
op_increment
suffix:semicolon
multiline_comment|/* smp_num_cpus++; Do after smp_send_reschedule works */
)brace
)brace
multiline_comment|/* while(atomic_read(&amp;numstarted) != (maxcpus - num_cpus)) */
r_if
c_cond
(paren
id|maxcpus
OG
l_int|1
)paren
r_while
c_loop
(paren
id|atomic_read
c_func
(paren
op_amp
id|numstarted
)paren
op_eq
l_int|0
)paren
(brace
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Holding %d cpus slave&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|numstarted
)paren
)paren
suffix:semicolon
macro_line|#ifdef LATER
id|Wait
id|logic
id|goes
id|here
dot
macro_line|#endif
r_for
c_loop
(paren
id|cnode
op_assign
l_int|0
suffix:semicolon
id|cnode
OL
id|numnodes
suffix:semicolon
id|cnode
op_increment
)paren
(brace
macro_line|#if 0
r_if
c_cond
(paren
id|cnodetocpu
c_func
(paren
id|cnode
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Initializing headless hub,cnode %d&quot;
comma
id|cnode
)paren
suffix:semicolon
id|per_hub_init
c_func
(paren
id|cnode
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
macro_line|#if 0
id|cpu_io_setup
c_func
(paren
)paren
suffix:semicolon
id|init_mfhi_war
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#else /* CONFIG_SMP */
DECL|function|cboot
r_void
id|cboot
c_func
(paren
r_void
)paren
(brace
)brace
macro_line|#endif /* CONFIG_SMP */
eof
