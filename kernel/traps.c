multiline_comment|/*&n; *  linux/kernel/traps.c&n; *&n; *  (C) 1991  Linus Torvalds&n; */
multiline_comment|/*&n; * &squot;Traps.c&squot; handles hardware traps and faults after we have saved some&n; * state in &squot;asm.s&squot;. Currently mostly a debugging-aid, will be extended&n; * to mainly kill the offending process (probably by giving it a signal,&n; * but possibly by killing it outright if necessary).&n; */
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|get_seg_byte
mdefine_line|#define get_seg_byte(seg,addr) ({ &bslash;&n;register char __res; &bslash;&n;__asm__(&quot;push %%fs;mov %%ax,%%fs;movb %%fs:%2,%%al;pop %%fs&quot; &bslash;&n;&t;:&quot;=a&quot; (__res):&quot;0&quot; (seg),&quot;m&quot; (*(addr))); &bslash;&n;__res;})
DECL|macro|get_seg_long
mdefine_line|#define get_seg_long(seg,addr) ({ &bslash;&n;register unsigned long __res; &bslash;&n;__asm__(&quot;push %%fs;mov %%ax,%%fs;movl %%fs:%2,%%eax;pop %%fs&quot; &bslash;&n;&t;:&quot;=a&quot; (__res):&quot;0&quot; (seg),&quot;m&quot; (*(addr))); &bslash;&n;__res;})
DECL|macro|_fs
mdefine_line|#define _fs() ({ &bslash;&n;register unsigned short __res; &bslash;&n;__asm__(&quot;mov %%fs,%%ax&quot;:&quot;=a&quot; (__res):); &bslash;&n;__res;})
r_int
id|do_exit
c_func
(paren
r_int
id|code
)paren
suffix:semicolon
r_void
id|page_exception
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|divide_error
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|debug
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|nmi
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|int3
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|overflow
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|bounds
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|invalid_op
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|device_not_available
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|double_fault
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|coprocessor_segment_overrun
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|invalid_TSS
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|segment_not_present
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|stack_segment
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|general_protection
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|page_fault
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|coprocessor_error
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|reserved
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|parallel_interrupt
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|irq13
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|die
r_static
r_void
id|die
c_func
(paren
r_char
op_star
id|str
comma
r_int
id|esp_ptr
comma
r_int
id|nr
)paren
(brace
r_int
op_star
id|esp
op_assign
(paren
r_int
op_star
)paren
id|esp_ptr
suffix:semicolon
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: %04x&bslash;n&bslash;r&quot;
comma
id|str
comma
id|nr
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;EIP:&bslash;t%04x:%p&bslash;nEFLAGS:&bslash;t%p&bslash;nESP:&bslash;t%04x:%p&bslash;n&quot;
comma
id|esp
(braket
l_int|1
)braket
comma
id|esp
(braket
l_int|0
)braket
comma
id|esp
(braket
l_int|2
)braket
comma
id|esp
(braket
l_int|4
)braket
comma
id|esp
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fs: %04x&bslash;n&quot;
comma
id|_fs
c_func
(paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;base: %p, limit: %p&bslash;n&quot;
comma
id|get_base
c_func
(paren
id|current-&gt;ldt
(braket
l_int|1
)braket
)paren
comma
id|get_limit
c_func
(paren
l_int|0x17
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|esp
(braket
l_int|4
)braket
op_eq
l_int|0x17
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Stack: &quot;
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%p &quot;
comma
id|get_seg_long
c_func
(paren
l_int|0x17
comma
id|i
op_plus
(paren
r_int
op_star
)paren
id|esp
(braket
l_int|3
)braket
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|str
c_func
(paren
id|i
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Pid: %d, process nr: %d&bslash;n&bslash;r&quot;
comma
id|current-&gt;pid
comma
l_int|0xffff
op_amp
id|i
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
l_int|10
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
l_int|0xff
op_amp
id|get_seg_byte
c_func
(paren
id|esp
(braket
l_int|1
)braket
comma
(paren
id|i
op_plus
(paren
r_char
op_star
)paren
id|esp
(braket
l_int|0
)braket
)paren
)paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
id|do_exit
c_func
(paren
l_int|11
)paren
suffix:semicolon
multiline_comment|/* play segment exception */
)brace
DECL|function|do_double_fault
r_void
id|do_double_fault
c_func
(paren
r_int
id|esp
comma
r_int
id|error_code
)paren
(brace
id|die
c_func
(paren
l_string|&quot;double fault&quot;
comma
id|esp
comma
id|error_code
)paren
suffix:semicolon
)brace
DECL|function|do_general_protection
r_void
id|do_general_protection
c_func
(paren
r_int
id|esp
comma
r_int
id|error_code
)paren
(brace
id|die
c_func
(paren
l_string|&quot;general protection&quot;
comma
id|esp
comma
id|error_code
)paren
suffix:semicolon
)brace
DECL|function|do_divide_error
r_void
id|do_divide_error
c_func
(paren
r_int
id|esp
comma
r_int
id|error_code
)paren
(brace
id|die
c_func
(paren
l_string|&quot;divide error&quot;
comma
id|esp
comma
id|error_code
)paren
suffix:semicolon
)brace
DECL|function|do_int3
r_void
id|do_int3
c_func
(paren
r_int
op_star
id|esp
comma
r_int
id|error_code
comma
r_int
id|fs
comma
r_int
id|es
comma
r_int
id|ds
comma
r_int
id|ebp
comma
r_int
id|esi
comma
r_int
id|edi
comma
r_int
id|edx
comma
r_int
id|ecx
comma
r_int
id|ebx
comma
r_int
id|eax
)paren
(brace
r_int
id|tr
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;str %%ax&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|tr
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;eax&bslash;t&bslash;tebx&bslash;t&bslash;tecx&bslash;t&bslash;tedx&bslash;n&bslash;r%8x&bslash;t%8x&bslash;t%8x&bslash;t%8x&bslash;n&bslash;r&quot;
comma
id|eax
comma
id|ebx
comma
id|ecx
comma
id|edx
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;esi&bslash;t&bslash;tedi&bslash;t&bslash;tebp&bslash;t&bslash;tesp&bslash;n&bslash;r%8x&bslash;t%8x&bslash;t%8x&bslash;t%8x&bslash;n&bslash;r&quot;
comma
id|esi
comma
id|edi
comma
id|ebp
comma
(paren
r_int
)paren
id|esp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&bslash;rds&bslash;tes&bslash;tfs&bslash;ttr&bslash;n&bslash;r%4x&bslash;t%4x&bslash;t%4x&bslash;t%4x&bslash;n&bslash;r&quot;
comma
id|ds
comma
id|es
comma
id|fs
comma
id|tr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;EIP: %8x   CS: %4x  EFLAGS: %8x&bslash;n&bslash;r&quot;
comma
id|esp
(braket
l_int|0
)braket
comma
id|esp
(braket
l_int|1
)braket
comma
id|esp
(braket
l_int|2
)braket
)paren
suffix:semicolon
)brace
DECL|function|do_nmi
r_void
id|do_nmi
c_func
(paren
r_int
id|esp
comma
r_int
id|error_code
)paren
(brace
id|die
c_func
(paren
l_string|&quot;nmi&quot;
comma
id|esp
comma
id|error_code
)paren
suffix:semicolon
)brace
DECL|function|do_debug
r_void
id|do_debug
c_func
(paren
r_int
id|esp
comma
r_int
id|error_code
)paren
(brace
id|die
c_func
(paren
l_string|&quot;debug&quot;
comma
id|esp
comma
id|error_code
)paren
suffix:semicolon
)brace
DECL|function|do_overflow
r_void
id|do_overflow
c_func
(paren
r_int
id|esp
comma
r_int
id|error_code
)paren
(brace
id|die
c_func
(paren
l_string|&quot;overflow&quot;
comma
id|esp
comma
id|error_code
)paren
suffix:semicolon
)brace
DECL|function|do_bounds
r_void
id|do_bounds
c_func
(paren
r_int
id|esp
comma
r_int
id|error_code
)paren
(brace
id|die
c_func
(paren
l_string|&quot;bounds&quot;
comma
id|esp
comma
id|error_code
)paren
suffix:semicolon
)brace
DECL|function|do_invalid_op
r_void
id|do_invalid_op
c_func
(paren
r_int
id|esp
comma
r_int
id|error_code
)paren
(brace
id|die
c_func
(paren
l_string|&quot;invalid operand&quot;
comma
id|esp
comma
id|error_code
)paren
suffix:semicolon
)brace
DECL|function|do_device_not_available
r_void
id|do_device_not_available
c_func
(paren
r_int
id|esp
comma
r_int
id|error_code
)paren
(brace
id|die
c_func
(paren
l_string|&quot;device not available&quot;
comma
id|esp
comma
id|error_code
)paren
suffix:semicolon
)brace
DECL|function|do_coprocessor_segment_overrun
r_void
id|do_coprocessor_segment_overrun
c_func
(paren
r_int
id|esp
comma
r_int
id|error_code
)paren
(brace
id|die
c_func
(paren
l_string|&quot;coprocessor segment overrun&quot;
comma
id|esp
comma
id|error_code
)paren
suffix:semicolon
)brace
DECL|function|do_invalid_TSS
r_void
id|do_invalid_TSS
c_func
(paren
r_int
id|esp
comma
r_int
id|error_code
)paren
(brace
id|die
c_func
(paren
l_string|&quot;invalid TSS&quot;
comma
id|esp
comma
id|error_code
)paren
suffix:semicolon
)brace
DECL|function|do_segment_not_present
r_void
id|do_segment_not_present
c_func
(paren
r_int
id|esp
comma
r_int
id|error_code
)paren
(brace
id|die
c_func
(paren
l_string|&quot;segment not present&quot;
comma
id|esp
comma
id|error_code
)paren
suffix:semicolon
)brace
DECL|function|do_stack_segment
r_void
id|do_stack_segment
c_func
(paren
r_int
id|esp
comma
r_int
id|error_code
)paren
(brace
id|die
c_func
(paren
l_string|&quot;stack segment&quot;
comma
id|esp
comma
id|error_code
)paren
suffix:semicolon
)brace
DECL|function|do_coprocessor_error
r_void
id|do_coprocessor_error
c_func
(paren
r_int
id|esp
comma
r_int
id|error_code
)paren
(brace
r_if
c_cond
(paren
id|last_task_used_math
op_ne
id|current
)paren
r_return
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;coprocessor error&quot;
comma
id|esp
comma
id|error_code
)paren
suffix:semicolon
)brace
DECL|function|do_reserved
r_void
id|do_reserved
c_func
(paren
r_int
id|esp
comma
r_int
id|error_code
)paren
(brace
id|die
c_func
(paren
l_string|&quot;reserved (15,17-47) error&quot;
comma
id|esp
comma
id|error_code
)paren
suffix:semicolon
)brace
DECL|function|trap_init
r_void
id|trap_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|0
comma
op_amp
id|divide_error
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|1
comma
op_amp
id|debug
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|2
comma
op_amp
id|nmi
)paren
suffix:semicolon
id|set_system_gate
c_func
(paren
l_int|3
comma
op_amp
id|int3
)paren
suffix:semicolon
multiline_comment|/* int3-5 can be called from all */
id|set_system_gate
c_func
(paren
l_int|4
comma
op_amp
id|overflow
)paren
suffix:semicolon
id|set_system_gate
c_func
(paren
l_int|5
comma
op_amp
id|bounds
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|6
comma
op_amp
id|invalid_op
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|7
comma
op_amp
id|device_not_available
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|8
comma
op_amp
id|double_fault
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|9
comma
op_amp
id|coprocessor_segment_overrun
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|10
comma
op_amp
id|invalid_TSS
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|11
comma
op_amp
id|segment_not_present
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|12
comma
op_amp
id|stack_segment
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|13
comma
op_amp
id|general_protection
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|14
comma
op_amp
id|page_fault
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|15
comma
op_amp
id|reserved
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|16
comma
op_amp
id|coprocessor_error
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|17
suffix:semicolon
id|i
OL
l_int|48
suffix:semicolon
id|i
op_increment
)paren
id|set_trap_gate
c_func
(paren
id|i
comma
op_amp
id|reserved
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|45
comma
op_amp
id|irq13
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|inb_p
c_func
(paren
l_int|0x21
)paren
op_amp
l_int|0xfb
comma
l_int|0x21
)paren
suffix:semicolon
id|outb
c_func
(paren
id|inb_p
c_func
(paren
l_int|0xA1
)paren
op_amp
l_int|0xdf
comma
l_int|0xA1
)paren
suffix:semicolon
id|set_trap_gate
c_func
(paren
l_int|39
comma
op_amp
id|parallel_interrupt
)paren
suffix:semicolon
)brace
eof
