multiline_comment|/* cpu.c: Dinky routines to look for the kind of Sparc cpu&n; *        we are on.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/head.h&gt;
macro_line|#include &lt;asm/psr.h&gt;
macro_line|#include &lt;asm/mbus.h&gt;
DECL|struct|cpu_iu_info
r_struct
id|cpu_iu_info
(brace
DECL|member|psr_impl
r_int
id|psr_impl
suffix:semicolon
DECL|member|psr_vers
r_int
id|psr_vers
suffix:semicolon
DECL|member|cpu_name
r_char
op_star
id|cpu_name
suffix:semicolon
multiline_comment|/* should be enough I hope... */
)brace
suffix:semicolon
DECL|struct|cpu_fp_info
r_struct
id|cpu_fp_info
(brace
DECL|member|psr_impl
r_int
id|psr_impl
suffix:semicolon
DECL|member|fp_vers
r_int
id|fp_vers
suffix:semicolon
DECL|member|fp_name
r_char
op_star
id|fp_name
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* In order to get the fpu type correct, you need to take the IDPROM&squot;s&n; * machine type value into consideration too.  I will fix this.&n; */
DECL|variable|linux_sparc_fpu
r_struct
id|cpu_fp_info
id|linux_sparc_fpu
(braket
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|0
comma
l_string|&quot;Fujitsu MB86910 or Weitek WTL1164/5&quot;
)brace
comma
(brace
l_int|0
comma
l_int|1
comma
l_string|&quot;Fujitsu MB86911 or Weitek WTL1164/5 or LSI L64831&quot;
)brace
comma
(brace
l_int|0
comma
l_int|2
comma
l_string|&quot;LSI Logic L64802 or Texas Instruments ACT8847&quot;
)brace
comma
multiline_comment|/* SparcStation SLC, SparcStation1 */
(brace
l_int|0
comma
l_int|3
comma
l_string|&quot;Weitek WTL3170/2&quot;
)brace
comma
multiline_comment|/* SPARCstation-5 */
(brace
l_int|0
comma
l_int|4
comma
l_string|&quot;Lsi Logic/Meiko L64804 or compatible&quot;
)brace
comma
(brace
l_int|0
comma
l_int|5
comma
l_string|&quot;reserved&quot;
)brace
comma
(brace
l_int|0
comma
l_int|6
comma
l_string|&quot;reserved&quot;
)brace
comma
(brace
l_int|0
comma
l_int|7
comma
l_string|&quot;No FPU&quot;
)brace
comma
(brace
l_int|1
comma
l_int|0
comma
l_string|&quot;ROSS HyperSparc combined IU/FPU&quot;
)brace
comma
(brace
l_int|1
comma
l_int|1
comma
l_string|&quot;Lsi Logic L64814&quot;
)brace
comma
(brace
l_int|1
comma
l_int|2
comma
l_string|&quot;Texas Instruments TMS390-C602A&quot;
)brace
comma
(brace
l_int|1
comma
l_int|3
comma
l_string|&quot;Cypress CY7C602 FPU&quot;
)brace
comma
(brace
l_int|1
comma
l_int|4
comma
l_string|&quot;reserved&quot;
)brace
comma
(brace
l_int|1
comma
l_int|5
comma
l_string|&quot;reserved&quot;
)brace
comma
(brace
l_int|1
comma
l_int|6
comma
l_string|&quot;reserved&quot;
)brace
comma
(brace
l_int|1
comma
l_int|7
comma
l_string|&quot;No FPU&quot;
)brace
comma
(brace
l_int|2
comma
l_int|0
comma
l_string|&quot;BIT B5010 or B5110/20 or B5210&quot;
)brace
comma
(brace
l_int|2
comma
l_int|1
comma
l_string|&quot;reserved&quot;
)brace
comma
(brace
l_int|2
comma
l_int|2
comma
l_string|&quot;reserved&quot;
)brace
comma
(brace
l_int|2
comma
l_int|3
comma
l_string|&quot;reserved&quot;
)brace
comma
(brace
l_int|2
comma
l_int|4
comma
l_string|&quot;reserved&quot;
)brace
comma
(brace
l_int|2
comma
l_int|5
comma
l_string|&quot;reserved&quot;
)brace
comma
(brace
l_int|2
comma
l_int|6
comma
l_string|&quot;reserved&quot;
)brace
comma
(brace
l_int|2
comma
l_int|7
comma
l_string|&quot;No FPU&quot;
)brace
comma
multiline_comment|/* SuperSparc 50 module */
(brace
l_int|4
comma
l_int|0
comma
l_string|&quot;SuperSparc on-chip FPU&quot;
)brace
comma
multiline_comment|/* SparcClassic */
(brace
l_int|4
comma
l_int|4
comma
l_string|&quot;TI MicroSparc on chip FPU&quot;
)brace
comma
(brace
l_int|5
comma
l_int|0
comma
l_string|&quot;Matsushita MN10501&quot;
)brace
comma
(brace
l_int|5
comma
l_int|1
comma
l_string|&quot;reserved&quot;
)brace
comma
(brace
l_int|5
comma
l_int|2
comma
l_string|&quot;reserved&quot;
)brace
comma
(brace
l_int|5
comma
l_int|3
comma
l_string|&quot;reserved&quot;
)brace
comma
(brace
l_int|5
comma
l_int|4
comma
l_string|&quot;reserved&quot;
)brace
comma
(brace
l_int|5
comma
l_int|5
comma
l_string|&quot;reserved&quot;
)brace
comma
(brace
l_int|5
comma
l_int|6
comma
l_string|&quot;reserved&quot;
)brace
comma
(brace
l_int|5
comma
l_int|7
comma
l_string|&quot;No FPU&quot;
)brace
comma
(brace
l_int|9
comma
l_int|3
comma
l_string|&quot;Fujitsu or Weitek on-chip FPU&quot;
)brace
comma
)brace
suffix:semicolon
DECL|macro|NSPARCFPU
mdefine_line|#define NSPARCFPU  (sizeof(linux_sparc_fpu)/sizeof(struct cpu_fp_info))
DECL|variable|linux_sparc_chips
r_struct
id|cpu_iu_info
id|linux_sparc_chips
(braket
)braket
op_assign
(brace
multiline_comment|/* Sun4/100, 4/200, SLC */
(brace
l_int|0
comma
l_int|0
comma
l_string|&quot;Fujitsu  MB86900/1A or LSI L64831 SparcKIT-40&quot;
)brace
comma
multiline_comment|/* borned STP1012PGA */
(brace
l_int|0
comma
l_int|4
comma
l_string|&quot;Fujitsu  MB86904&quot;
)brace
comma
multiline_comment|/* SparcStation2, SparcServer 490 &amp; 690 */
(brace
l_int|1
comma
l_int|0
comma
l_string|&quot;LSI Logic Corporation - L64811&quot;
)brace
comma
multiline_comment|/* SparcStation2 */
(brace
l_int|1
comma
l_int|1
comma
l_string|&quot;Cypress/ROSS CY7C601&quot;
)brace
comma
multiline_comment|/* Embedded controller */
(brace
l_int|1
comma
l_int|3
comma
l_string|&quot;Cypress/ROSS CY7C611&quot;
)brace
comma
multiline_comment|/* Ross Technologies HyperSparc */
(brace
l_int|1
comma
l_int|0xf
comma
l_string|&quot;ROSS HyperSparc RT620&quot;
)brace
comma
(brace
l_int|1
comma
l_int|0xe
comma
l_string|&quot;ROSS HyperSparc RT625 or RT626&quot;
)brace
comma
multiline_comment|/* ECL Implementation, CRAY S-MP Supercomputer... AIEEE! */
multiline_comment|/* Someone please write the code to support this beast! ;) */
(brace
l_int|2
comma
l_int|0
comma
l_string|&quot;Bipolar Integrated Technology - B5010&quot;
)brace
comma
(brace
l_int|3
comma
l_int|0
comma
l_string|&quot;LSI Logic Corporation - unknown-type&quot;
)brace
comma
(brace
l_int|4
comma
l_int|0
comma
l_string|&quot;Texas Instruments, Inc. - SuperSparc 50&quot;
)brace
comma
multiline_comment|/* SparcClassic  --  borned STP1010TAB-50*/
(brace
l_int|4
comma
l_int|1
comma
l_string|&quot;Texas Instruments, Inc. - MicroSparc&quot;
)brace
comma
(brace
l_int|4
comma
l_int|2
comma
l_string|&quot;Texas Instruments, Inc. - MicroSparc II&quot;
)brace
comma
(brace
l_int|4
comma
l_int|3
comma
l_string|&quot;Texas Instruments, Inc. - SuperSparc 51&quot;
)brace
comma
(brace
l_int|4
comma
l_int|4
comma
l_string|&quot;Texas Instruments, Inc. - SuperSparc 61&quot;
)brace
comma
(brace
l_int|4
comma
l_int|5
comma
l_string|&quot;Texas Instruments, Inc. - unknown&quot;
)brace
comma
(brace
l_int|5
comma
l_int|0
comma
l_string|&quot;Matsushita - MN10501&quot;
)brace
comma
(brace
l_int|6
comma
l_int|0
comma
l_string|&quot;Philips Corporation - unknown&quot;
)brace
comma
(brace
l_int|7
comma
l_int|0
comma
l_string|&quot;Harvest VLSI Design Center, Inc. - unknown&quot;
)brace
comma
multiline_comment|/* Gallium arsenide 200MHz, BOOOOGOOOOMIPS!!! */
(brace
l_int|8
comma
l_int|0
comma
l_string|&quot;Systems and Processes Engineering Corporation (SPEC)&quot;
)brace
comma
(brace
l_int|9
comma
l_int|0
comma
l_string|&quot;Fujitsu or Weitek Power-UP&quot;
)brace
comma
(brace
l_int|9
comma
l_int|1
comma
l_string|&quot;Fujitsu or Weitek Power-UP&quot;
)brace
comma
(brace
l_int|9
comma
l_int|2
comma
l_string|&quot;Fujitsu or Weitek Power-UP&quot;
)brace
comma
(brace
l_int|9
comma
l_int|3
comma
l_string|&quot;Fujitsu or Weitek Power-UP&quot;
)brace
comma
(brace
l_int|0xa
comma
l_int|0
comma
l_string|&quot;UNKNOWN CPU-VENDOR/TYPE&quot;
)brace
comma
(brace
l_int|0xb
comma
l_int|0
comma
l_string|&quot;UNKNOWN CPU-VENDOR/TYPE&quot;
)brace
comma
(brace
l_int|0xc
comma
l_int|0
comma
l_string|&quot;UNKNOWN CPU-VENDOR/TYPE&quot;
)brace
comma
(brace
l_int|0xd
comma
l_int|0
comma
l_string|&quot;UNKNOWN CPU-VENDOR/TYPE&quot;
)brace
comma
(brace
l_int|0xe
comma
l_int|0
comma
l_string|&quot;UNKNOWN CPU-VENDOR/TYPE&quot;
)brace
comma
(brace
l_int|0xf
comma
l_int|0
comma
l_string|&quot;UNKNOWN CPU-VENDOR/TYPE&quot;
)brace
comma
)brace
suffix:semicolon
DECL|macro|NSPARCCHIPS
mdefine_line|#define NSPARCCHIPS  (sizeof(linux_sparc_chips)/sizeof(struct cpu_iu_info))
DECL|variable|sparc_cpu_type
r_char
op_star
id|sparc_cpu_type
(braket
id|NCPUS
)braket
op_assign
(brace
l_string|&quot;cpu-oops&quot;
comma
l_string|&quot;cpu-oops1&quot;
comma
l_string|&quot;cpu-oops2&quot;
comma
l_string|&quot;cpu-oops3&quot;
)brace
suffix:semicolon
DECL|variable|sparc_fpu_type
r_char
op_star
id|sparc_fpu_type
(braket
id|NCPUS
)braket
op_assign
(brace
l_string|&quot;fpu-oops&quot;
comma
l_string|&quot;fpu-oops1&quot;
comma
l_string|&quot;fpu-oops2&quot;
comma
l_string|&quot;fpu-oops3&quot;
)brace
suffix:semicolon
DECL|variable|fsr_storage
r_int
r_int
id|fsr_storage
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|cpu_probe
c_func
(paren
r_void
)paren
)paren
(brace
r_int
id|psr_impl
comma
id|psr_vers
comma
id|fpu_vers
suffix:semicolon
r_int
id|i
comma
id|cpuid
suffix:semicolon
id|cpuid
op_assign
id|get_cpuid
c_func
(paren
)paren
suffix:semicolon
id|psr_impl
op_assign
(paren
(paren
id|get_psr
c_func
(paren
)paren
op_rshift
l_int|28
)paren
op_amp
l_int|0xf
)paren
suffix:semicolon
id|psr_vers
op_assign
(paren
(paren
id|get_psr
c_func
(paren
)paren
op_rshift
l_int|24
)paren
op_amp
l_int|0xf
)paren
suffix:semicolon
id|fpu_vers
op_assign
(paren
(paren
id|get_fsr
c_func
(paren
)paren
op_rshift
l_int|17
)paren
op_amp
l_int|0x7
)paren
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
id|NSPARCCHIPS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|linux_sparc_chips
(braket
id|i
)braket
dot
id|psr_impl
op_eq
id|psr_impl
)paren
r_if
c_cond
(paren
id|linux_sparc_chips
(braket
id|i
)braket
dot
id|psr_vers
op_eq
id|psr_vers
)paren
(brace
id|sparc_cpu_type
(braket
id|cpuid
)braket
op_assign
id|linux_sparc_chips
(braket
id|i
)braket
dot
id|cpu_name
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
op_eq
id|NSPARCCHIPS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;DEBUG: psr.impl = 0x%x   psr.vers = 0x%x&bslash;n&quot;
comma
id|psr_impl
comma
id|psr_vers
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NSPARCFPU
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|linux_sparc_fpu
(braket
id|i
)braket
dot
id|psr_impl
op_eq
id|psr_impl
)paren
r_if
c_cond
(paren
id|linux_sparc_fpu
(braket
id|i
)braket
dot
id|fp_vers
op_eq
id|fpu_vers
)paren
(brace
id|sparc_fpu_type
(braket
id|cpuid
)braket
op_assign
id|linux_sparc_fpu
(braket
id|i
)braket
dot
id|fp_name
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
op_eq
id|NSPARCFPU
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;DEBUG: psr.impl = 0x%x  fsr.vers = 0x%x&bslash;n&quot;
comma
id|psr_impl
comma
id|fpu_vers
)paren
suffix:semicolon
id|sparc_fpu_type
(braket
id|cpuid
)braket
op_assign
id|linux_sparc_fpu
(braket
l_int|31
)braket
dot
id|fp_name
suffix:semicolon
)brace
)brace
eof
