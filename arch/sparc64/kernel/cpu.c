multiline_comment|/* cpu.c: Dinky routines to look for the kind of Sparc cpu&n; *        we are on.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/fpumacro.h&gt;
DECL|struct|cpu_iu_info
r_struct
id|cpu_iu_info
(brace
DECL|member|manuf
r_int
id|manuf
suffix:semicolon
DECL|member|impl
r_int
id|impl
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
DECL|member|manuf
r_int
id|manuf
suffix:semicolon
DECL|member|impl
r_int
id|impl
suffix:semicolon
DECL|member|fpu_vers
r_char
id|fpu_vers
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
l_int|0x17
comma
l_int|0x10
comma
l_int|0
comma
l_string|&quot;UltraSparc I integrated FPU&quot;
)brace
comma
(brace
l_int|0x22
comma
l_int|0x10
comma
l_int|0
comma
l_string|&quot;UltraSparc II integrated FPU&quot;
)brace
comma
(brace
l_int|0x17
comma
l_int|0x11
comma
l_int|0
comma
l_string|&quot;UltraSparc II integrated FPU&quot;
)brace
comma
(brace
l_int|0x17
comma
l_int|0x12
comma
l_int|0
comma
l_string|&quot;UltraSparc III integrated FPU&quot;
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
(brace
l_int|0x17
comma
l_int|0x10
comma
l_string|&quot;TI UltraSparc I   (SpitFire)&quot;
)brace
comma
(brace
l_int|0x22
comma
l_int|0x10
comma
l_string|&quot;TI UltraSparc II  (BlackBird)&quot;
)brace
comma
(brace
l_int|0x17
comma
l_int|0x11
comma
l_string|&quot;TI UltraSparc II  (BlackBird)&quot;
)brace
comma
(brace
l_int|0x17
comma
l_int|0x12
comma
l_string|&quot;TI UltraSparc III (Cheetah)&quot;
)brace
comma
multiline_comment|/* A guess... */
)brace
suffix:semicolon
DECL|macro|NSPARCCHIPS
mdefine_line|#define NSPARCCHIPS  (sizeof(linux_sparc_chips)/sizeof(struct cpu_iu_info))
macro_line|#ifdef __SMP__
DECL|variable|sparc_cpu_type
r_char
op_star
id|sparc_cpu_type
(braket
id|NR_CPUS
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
id|NR_CPUS
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
macro_line|#else
DECL|variable|sparc_cpu_type
r_char
op_star
id|sparc_cpu_type
(braket
id|NR_CPUS
)braket
op_assign
(brace
l_string|&quot;cpu-oops&quot;
comma
)brace
suffix:semicolon
DECL|variable|sparc_fpu_type
r_char
op_star
id|sparc_fpu_type
(braket
id|NR_CPUS
)braket
op_assign
(brace
l_string|&quot;fpu-oops&quot;
comma
)brace
suffix:semicolon
macro_line|#endif
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
id|manuf
comma
id|impl
suffix:semicolon
r_int
id|i
comma
id|cpuid
suffix:semicolon
r_int
id|ver
comma
id|fpu_vers
suffix:semicolon
r_int
id|fprs
suffix:semicolon
id|cpuid
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|fprs
op_assign
id|fprs_read
(paren
)paren
suffix:semicolon
id|fprs_write
(paren
id|FPRS_FEF
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;rdpr %%ver, %0; stx %%fsr, [%1]&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ver
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|fpu_vers
)paren
)paren
suffix:semicolon
id|fprs_write
(paren
id|fprs
)paren
suffix:semicolon
id|manuf
op_assign
(paren
(paren
id|ver
op_rshift
l_int|48
)paren
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|impl
op_assign
(paren
(paren
id|ver
op_rshift
l_int|32
)paren
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|fpu_vers
op_assign
(paren
(paren
id|fpu_vers
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
id|manuf
op_eq
id|manuf
)paren
r_if
c_cond
(paren
id|linux_sparc_chips
(braket
id|i
)braket
dot
id|impl
op_eq
id|impl
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
l_string|&quot;DEBUG: manuf = 0x%x   impl = 0x%x&bslash;n&quot;
comma
id|manuf
comma
id|impl
)paren
suffix:semicolon
id|sparc_cpu_type
(braket
id|cpuid
)braket
op_assign
l_string|&quot;Unknow CPU&quot;
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
id|manuf
op_eq
id|manuf
op_logical_and
id|linux_sparc_fpu
(braket
id|i
)braket
dot
id|impl
op_eq
id|impl
)paren
r_if
c_cond
(paren
id|linux_sparc_fpu
(braket
id|i
)braket
dot
id|fpu_vers
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
l_string|&quot;DEBUG: manuf = 0x%x  impl = 0x%x fsr.vers = 0x%x&bslash;n&quot;
comma
id|manuf
comma
id|impl
comma
(paren
r_int
)paren
id|fpu_vers
)paren
suffix:semicolon
id|sparc_fpu_type
(braket
id|cpuid
)braket
op_assign
l_string|&quot;Unknown FPU&quot;
suffix:semicolon
)brace
)brace
eof
