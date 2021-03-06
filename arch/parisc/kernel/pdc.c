multiline_comment|/* arch/parisc/kernel/pdc.c  - safe pdc access routines&n; *&n; * Copyright 1999 SuSE GmbH Nuernberg (Philipp Rumpf, prumpf@tux.org)&n; * portions Copyright 1999 The Puffin Group, (Alex deVries, David Kennedy)&n; *&n; * only these routines should be used out of the real kernel (i.e. everything&n; * using virtual addresses) for obvious reasons */
multiline_comment|/*&t;I think it would be in everyone&squot;s best interest to follow this&n; *&t;guidelines when writing PDC wrappers:&n; *&n; *&t; - the name of the pdc wrapper should match one of the macros&n; *&t;   used for the first two arguments&n; *&t; - don&squot;t use caps for random parts of the name&n; *&t; - use ASSERT_ALIGN to ensure the aligment of the arguments is&n; *&t;   correct&n; *&t; - use __pa() to convert virtual (kernel) pointers to physical&n; *&t;   ones.&n; *&t; - the name of the struct used for pdc return values should equal&n; *&t;   one of the macros used for the first two arguments to the&n; *&t;   corresponding PDC call&n; *&t; - keep the order of arguments&n; *&t; - don&squot;t be smart (setting trailing NUL bytes for strings, return&n; *&t;   something useful even if the call failed) unless you are sure&n; *&t;   it&squot;s not going to affect functionality or performance&n; *&n; *&t;Example:&n; *&t;int pdc_cache_info(struct pdc_cache_info *cache_info )&n; *&t;{&n; *&t;&t;ASSERT_ALIGN(cache_info, 8);&n; *&t;&n; *&t;&t;return mem_pdc_call(PDC_CACHE,PDC_CACHE_INFO,__pa(cache_info),0);&n; *&t;}&n; *&t;&t;&t;&t;&t;prumpf&t;991016&t;&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pdc.h&gt;
macro_line|#include &lt;asm/real.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|ASSERT_ALIGN
mdefine_line|#define ASSERT_ALIGN(ptr, align)&t;&t;&t;&t;&t;&bslash;&n;&t;do { if(((unsigned long)(ptr)) &amp; (align-1)) {&t;&t;&t;&bslash;&n;&t;&t;printk(&quot;PDC: %s:%d  %s() called with &quot;&t;&bslash;&n;&t;&t;&t;&quot;unaligned argument from %p&quot;, __FILE__, __LINE__, &bslash;&n;&t;&t;&t;__FUNCTION__, __builtin_return_address(0));&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;return -1;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} } while(0)
multiline_comment|/* verify address can be accessed without an HPMC */
DECL|function|pdc_add_valid
r_int
id|pdc_add_valid
c_func
(paren
r_void
op_star
id|address
)paren
(brace
id|ASSERT_ALIGN
c_func
(paren
id|address
comma
l_int|4
)paren
suffix:semicolon
r_return
id|mem_pdc_call
c_func
(paren
id|PDC_ADD_VALID
comma
id|PDC_ADD_VALID_VERIFY
comma
(paren
r_int
r_int
)paren
id|address
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_int
id|pdc_chassis_warn
c_func
(paren
r_struct
id|pdc_chassis_warn
op_star
id|address
)paren
(brace
id|ASSERT_ALIGN
c_func
(paren
id|address
comma
l_int|4
)paren
suffix:semicolon
r_return
id|mem_pdc_call
c_func
(paren
id|PDC_CHASSIS
comma
id|PDC_CHASSIS_WARN
comma
id|__pa
c_func
(paren
id|address
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|pdc_chassis_disp
r_int
id|pdc_chassis_disp
c_func
(paren
r_int
r_int
id|disp
)paren
(brace
r_return
id|mem_pdc_call
c_func
(paren
id|PDC_CHASSIS
comma
id|PDC_CHASSIS_DISP
comma
id|disp
)paren
suffix:semicolon
)brace
DECL|function|pdc_chassis_info
r_int
id|pdc_chassis_info
c_func
(paren
r_void
op_star
id|pdc_result
comma
r_void
op_star
id|chassis_info
comma
r_int
r_int
id|len
)paren
(brace
id|ASSERT_ALIGN
c_func
(paren
id|pdc_result
comma
l_int|4
)paren
suffix:semicolon
id|ASSERT_ALIGN
c_func
(paren
id|chassis_info
comma
l_int|4
)paren
suffix:semicolon
r_return
id|mem_pdc_call
c_func
(paren
id|PDC_CHASSIS
comma
id|PDC_RETURN_CHASSIS_INFO
comma
id|__pa
c_func
(paren
id|pdc_result
)paren
comma
id|__pa
c_func
(paren
id|chassis_info
)paren
comma
id|len
)paren
suffix:semicolon
)brace
DECL|function|pdc_hpa_processor
r_int
id|pdc_hpa_processor
c_func
(paren
r_void
op_star
id|address
)paren
(brace
multiline_comment|/* We&squot;re using 0 for the last parameter just to make sure.&n;&t;   It&squot;s actually HVERSION dependant.  And remember, life is&n;&t;   hard without a backspace. */
id|ASSERT_ALIGN
c_func
(paren
id|address
comma
l_int|4
)paren
suffix:semicolon
r_return
id|mem_pdc_call
c_func
(paren
id|PDC_HPA
comma
id|PDC_HPA_PROCESSOR
comma
id|__pa
c_func
(paren
id|address
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_int
id|pdc_hpa_modules
c_func
(paren
r_void
op_star
id|address
)paren
(brace
r_return
id|mem_pdc_call
c_func
(paren
id|PDC_HPA
comma
id|PDC_HPA_MODULES
comma
id|address
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|pdc_iodc_read
r_int
id|pdc_iodc_read
c_func
(paren
r_void
op_star
id|address
comma
r_void
op_star
id|hpa
comma
r_int
r_int
id|index
comma
r_void
op_star
id|iodc_data
comma
r_int
r_int
id|iodc_data_size
)paren
(brace
id|ASSERT_ALIGN
c_func
(paren
id|address
comma
l_int|4
)paren
suffix:semicolon
id|ASSERT_ALIGN
c_func
(paren
id|iodc_data
comma
l_int|8
)paren
suffix:semicolon
r_return
id|mem_pdc_call
c_func
(paren
id|PDC_IODC
comma
id|PDC_IODC_READ
comma
id|__pa
c_func
(paren
id|address
)paren
comma
id|hpa
comma
id|index
comma
id|__pa
c_func
(paren
id|iodc_data
)paren
comma
id|iodc_data_size
)paren
suffix:semicolon
)brace
DECL|function|pdc_system_map_find_mods
r_int
id|pdc_system_map_find_mods
c_func
(paren
r_void
op_star
id|pdc_mod_info
comma
r_void
op_star
id|mod_path
comma
r_int
id|index
)paren
(brace
r_return
id|mem_pdc_call
c_func
(paren
id|PDC_SYSTEM_MAP
comma
id|PDC_FIND_MODULE
comma
id|__pa
c_func
(paren
id|pdc_mod_info
)paren
comma
id|__pa
c_func
(paren
id|mod_path
)paren
comma
(paren
r_int
)paren
id|index
)paren
suffix:semicolon
)brace
DECL|function|pdc_model_info
r_int
id|pdc_model_info
c_func
(paren
r_struct
id|pdc_model
op_star
id|model
)paren
(brace
id|ASSERT_ALIGN
c_func
(paren
id|model
comma
l_int|8
)paren
suffix:semicolon
r_return
id|mem_pdc_call
c_func
(paren
id|PDC_MODEL
comma
id|PDC_MODEL_INFO
comma
id|__pa
c_func
(paren
id|model
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* get system model name from PDC ROM (e.g. 9000/715 or 9000/778/B160L) */
DECL|function|pdc_model_sysmodel
r_int
id|pdc_model_sysmodel
c_func
(paren
r_char
op_star
id|name
)paren
(brace
r_struct
id|pdc_model_sysmodel
id|sys_model
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|ASSERT_ALIGN
c_func
(paren
op_amp
id|sys_model
comma
l_int|8
)paren
suffix:semicolon
id|ASSERT_ALIGN
c_func
(paren
id|name
comma
l_int|4
)paren
suffix:semicolon
id|sys_model.mod_len
op_assign
l_int|0
suffix:semicolon
id|retval
op_assign
id|mem_pdc_call
c_func
(paren
id|PDC_MODEL
comma
id|PDC_MODEL_SYSMODEL
comma
id|__pa
c_func
(paren
op_amp
id|sys_model
)paren
comma
id|OS_ID_HPUX
comma
id|__pa
c_func
(paren
id|name
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_eq
id|PDC_RET_OK
)paren
id|name
(braket
id|sys_model.mod_len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* add trailing &squot;&bslash;0&squot; */
r_else
id|name
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* id: 0 = cpu revision, 1 = boot-rom-version */
DECL|function|pdc_model_versions
r_int
id|pdc_model_versions
c_func
(paren
r_struct
id|pdc_model_cpuid
op_star
id|cpu_id
comma
r_int
id|id
)paren
(brace
r_return
id|mem_pdc_call
c_func
(paren
id|PDC_MODEL
comma
id|PDC_MODEL_VERSIONS
comma
id|__pa
c_func
(paren
id|cpu_id
)paren
comma
id|id
)paren
suffix:semicolon
)brace
DECL|function|pdc_model_cpuid
r_int
id|pdc_model_cpuid
c_func
(paren
r_struct
id|pdc_model_cpuid
op_star
id|cpu_id
)paren
(brace
id|cpu_id-&gt;cpuid
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* preset zero (call maybe not implemented!) */
r_return
id|mem_pdc_call
c_func
(paren
id|PDC_MODEL
comma
l_int|6
comma
id|__pa
c_func
(paren
id|cpu_id
)paren
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* 6=&quot;return CPU ID&quot; */
)brace
DECL|function|pdc_cache_info
r_int
id|pdc_cache_info
c_func
(paren
r_struct
id|pdc_cache_info
op_star
id|cache_info
)paren
(brace
id|ASSERT_ALIGN
c_func
(paren
id|cache_info
comma
l_int|8
)paren
suffix:semicolon
r_return
id|mem_pdc_call
c_func
(paren
id|PDC_CACHE
comma
id|PDC_CACHE_INFO
comma
id|__pa
c_func
(paren
id|cache_info
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#ifndef __LP64__
DECL|function|pdc_btlb_info
r_int
id|pdc_btlb_info
c_func
(paren
r_struct
id|pdc_btlb_info
op_star
id|btlb
)paren
(brace
r_int
id|status
suffix:semicolon
id|status
op_assign
id|mem_pdc_call
c_func
(paren
id|PDC_BLOCK_TLB
comma
id|PDC_BTLB_INFO
comma
id|__pa
c_func
(paren
id|btlb
)paren
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
id|btlb-&gt;max_size
op_assign
l_int|0
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|pdc_mem_map_hpa
r_int
id|pdc_mem_map_hpa
c_func
(paren
r_void
op_star
id|r_addr
comma
r_void
op_star
id|mod_path
)paren
(brace
r_return
id|mem_pdc_call
c_func
(paren
id|PDC_MEM_MAP
comma
id|PDC_MEM_MAP_HPA
comma
id|__pa
c_func
(paren
id|r_addr
)paren
comma
id|__pa
c_func
(paren
id|mod_path
)paren
)paren
suffix:semicolon
)brace
DECL|function|pdc_lan_station_id
r_int
id|pdc_lan_station_id
c_func
(paren
r_char
op_star
id|lan_addr
comma
r_void
op_star
id|net_hpa
)paren
(brace
r_struct
id|pdc_lan_station_id
id|id
suffix:semicolon
r_int
r_char
op_star
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|mem_pdc_call
c_func
(paren
id|PDC_LAN_STATION_ID
comma
id|PDC_LAN_STATION_ID_READ
comma
id|__pa
c_func
(paren
op_amp
id|id
)paren
comma
id|net_hpa
)paren
OL
l_int|0
)paren
id|addr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* FIXME: else read MAC from NVRAM */
r_else
id|addr
op_assign
id|id.addr
suffix:semicolon
r_if
c_cond
(paren
id|addr
)paren
id|memmove
c_func
(paren
id|lan_addr
comma
id|addr
comma
id|PDC_LAN_STATION_ID_SIZE
)paren
suffix:semicolon
r_else
id|memset
c_func
(paren
id|lan_addr
comma
l_int|0
comma
id|PDC_LAN_STATION_ID_SIZE
)paren
suffix:semicolon
r_return
(paren
id|addr
op_ne
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Similar to PDC_PAT stuff in pdcpat.c - but added for Forte/Allegro boxes */
DECL|function|pdc_pci_irt_size
r_int
id|pdc_pci_irt_size
c_func
(paren
r_void
op_star
id|r_addr
comma
r_void
op_star
id|hpa
)paren
(brace
r_return
id|mem_pdc_call
c_func
(paren
id|PDC_PCI_INDEX
comma
id|PDC_PCI_GET_INT_TBL_SIZE
comma
id|__pa
c_func
(paren
id|r_addr
)paren
comma
id|hpa
)paren
suffix:semicolon
)brace
DECL|function|pdc_pci_irt
r_int
id|pdc_pci_irt
c_func
(paren
r_void
op_star
id|r_addr
comma
r_void
op_star
id|hpa
comma
r_void
op_star
id|tbl
)paren
(brace
r_return
id|mem_pdc_call
c_func
(paren
id|PDC_PCI_INDEX
comma
id|PDC_PCI_GET_INT_TBL
comma
id|__pa
c_func
(paren
id|r_addr
)paren
comma
id|hpa
comma
id|__pa
c_func
(paren
id|tbl
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* access the TOD clock */
DECL|function|pdc_tod_read
r_int
id|pdc_tod_read
c_func
(paren
r_struct
id|pdc_tod
op_star
id|tod
)paren
(brace
id|ASSERT_ALIGN
c_func
(paren
id|tod
comma
l_int|8
)paren
suffix:semicolon
r_return
id|mem_pdc_call
c_func
(paren
id|PDC_TOD
comma
id|PDC_TOD_READ
comma
id|__pa
c_func
(paren
id|tod
)paren
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|pdc_tod_set
r_int
id|pdc_tod_set
c_func
(paren
r_int
r_int
id|sec
comma
r_int
r_int
id|usec
)paren
(brace
r_return
id|mem_pdc_call
c_func
(paren
id|PDC_TOD
comma
id|PDC_TOD_WRITE
comma
id|sec
comma
id|usec
)paren
suffix:semicolon
)brace
eof
