multiline_comment|/*&n;** bootstrap.h -- This file is a part of the Atari bootloader.&n;**&n;** Copyright 1993 by Arjan Knor&n;**&n;** Modified by Andreas Schwab&n;** - clear transparent translation registers&n;**&n;** This file is subject to the terms and conditions of the GNU General Public&n;** License.  See the file README.legal in the main directory of this archive&n;** for more details.&n;**&n;*/
macro_line|#ifndef BOOTSTRAP_H
DECL|macro|BOOTSTRAP_H
mdefine_line|#define BOOTSTRAP_H
multiline_comment|/* _MCH cookie values */
DECL|macro|MACH_ST
mdefine_line|#define MACH_ST  0
DECL|macro|MACH_STE
mdefine_line|#define MACH_STE 1
DECL|macro|MACH_TT
mdefine_line|#define MACH_TT  2
DECL|macro|MACH_FALCON
mdefine_line|#define MACH_FALCON 3
multiline_comment|/* some constants for memory handling */
DECL|macro|ST_RAM
mdefine_line|#define ST_RAM 0
DECL|macro|TT_RAM
mdefine_line|#define TT_RAM 1
DECL|macro|TT_RAM_BASE
mdefine_line|#define TT_RAM_BASE  (u_long)(0x01000000)
DECL|macro|MB
mdefine_line|#define MB           (1024 * 1024)
DECL|macro|START_MEM
mdefine_line|#define START_MEM    (bi.memory[0].addr)
DECL|macro|MEM_SIZE
mdefine_line|#define MEM_SIZE     (bi.memory[0].size)
multiline_comment|/* the various CPU- and FPU-types */
DECL|macro|AFF_68000
mdefine_line|#define AFF_68000 (1)
DECL|macro|AFF_68020
mdefine_line|#define AFF_68020 (2)
DECL|macro|AFF_68030
mdefine_line|#define AFF_68030 (4)
DECL|macro|AFF_68040
mdefine_line|#define AFF_68040 (8)
DECL|macro|AFF_68881
mdefine_line|#define AFF_68881 (16)
DECL|macro|AFF_68882
mdefine_line|#define AFF_68882 (32)
multiline_comment|/* the possible OS-languages */
DECL|macro|USA
mdefine_line|#define USA 0
DECL|macro|FRG
mdefine_line|#define FRG 1
DECL|macro|FRA
mdefine_line|#define FRA 2
DECL|macro|UK
mdefine_line|#define UK  3
DECL|macro|SPA
mdefine_line|#define SPA 4
DECL|macro|ITA
mdefine_line|#define ITA 5
DECL|macro|SWE
mdefine_line|#define SWE 6
DECL|macro|SWF
mdefine_line|#define SWF 7
DECL|macro|SWG
mdefine_line|#define SWG 8
DECL|macro|TUR
mdefine_line|#define TUR 9
DECL|macro|FIN
mdefine_line|#define FIN 10
DECL|macro|NOR
mdefine_line|#define NOR 11
DECL|macro|DEN
mdefine_line|#define DEN 12
DECL|macro|SAU
mdefine_line|#define SAU 13
DECL|macro|HOL
mdefine_line|#define HOL 14
multiline_comment|/* some inline functions */
DECL|function|fpu_idle_frame_size
r_static
id|__inline
r_int
id|fpu_idle_frame_size
(paren
r_void
)paren
(brace
r_char
id|fpu_frame
(braket
l_int|216
)braket
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;fnop&quot;
op_scope_resolution
)paren
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;fsave %0@&quot;
suffix:colon
suffix:colon
l_string|&quot;a&quot;
(paren
id|fpu_frame
)paren
)paren
suffix:semicolon
r_return
id|fpu_frame
(braket
l_int|1
)braket
suffix:semicolon
)brace
DECL|function|change_stack
r_static
id|__inline
r_void
id|change_stack
(paren
id|u_long
op_star
id|stackp
)paren
(brace
id|__asm__
r_volatile
(paren
l_string|&quot;movel %0,sp&bslash;n&bslash;t&quot;
op_scope_resolution
l_string|&quot;g&quot;
(paren
id|stackp
)paren
suffix:colon
l_string|&quot;sp&quot;
)paren
suffix:semicolon
)brace
DECL|function|disable_interrupts
r_static
id|__inline
r_void
id|disable_interrupts
(paren
r_void
)paren
(brace
id|__asm__
r_volatile
(paren
l_string|&quot;orw #0x700,sr&quot;
suffix:colon
)paren
suffix:semicolon
)brace
r_extern
r_struct
id|bootinfo
id|bi
suffix:semicolon
DECL|function|disable_cache
r_static
id|__inline
r_void
id|disable_cache
(paren
r_void
)paren
(brace
id|__asm__
r_volatile
(paren
l_string|&quot;movec %0,cacr&quot;
op_scope_resolution
l_string|&quot;d&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bi.cputype
op_amp
id|CPU_68060
)paren
(brace
multiline_comment|/* &squot;060: clear branch cache after disabling it;&n;&t; * disable superscalar operation (and enable FPU) */
id|__asm__
r_volatile
(paren
l_string|&quot;movec %0,cacr&quot;
op_scope_resolution
l_string|&quot;d&quot;
(paren
l_int|0x00400000
)paren
)paren
suffix:semicolon
id|__asm__
r_volatile
(paren
l_string|&quot;moveq #0,d0;&quot;
l_string|&quot;.long 0x4e7b0808&quot;
multiline_comment|/* movec d0,pcr */
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
multiline_comment|/* no inputs */
suffix:colon
l_string|&quot;d0&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|disable_mmu
r_static
id|__inline
r_void
id|disable_mmu
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|bi.cputype
op_amp
(paren
id|CPU_68040
op_or
id|CPU_68060
)paren
)paren
(brace
id|__asm__
r_volatile
(paren
l_string|&quot;moveq #0,d0;&quot;
l_string|&quot;.long 0x4e7b0003;&quot;
multiline_comment|/* movec d0,tc */
l_string|&quot;.long 0x4e7b0004;&quot;
multiline_comment|/* movec d0,itt0 */
l_string|&quot;.long 0x4e7b0005;&quot;
multiline_comment|/* movec d0,itt1 */
l_string|&quot;.long 0x4e7b0006;&quot;
multiline_comment|/* movec d0,dtt0 */
l_string|&quot;.long 0x4e7b0007&quot;
multiline_comment|/* movec d0,dtt1 */
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
multiline_comment|/* no inputs */
suffix:colon
l_string|&quot;d0&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|__asm__
r_volatile
(paren
l_string|&quot;subl  #4,sp&bslash;n&bslash;t&quot;
l_string|&quot;pmove tc,sp@&bslash;n&bslash;t&quot;
l_string|&quot;bclr  #7,sp@&bslash;n&bslash;t&quot;
l_string|&quot;pmove sp@,tc&bslash;n&bslash;t&quot;
l_string|&quot;addl  #4,sp&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bi.cputype
op_amp
id|CPU_68030
)paren
(brace
id|__asm__
r_volatile
(paren
l_string|&quot;clrl sp@-&bslash;n&bslash;t&quot;
l_string|&quot;.long 0xf0170800&bslash;n&bslash;t&quot;
multiline_comment|/* pmove sp@,tt0 */
l_string|&quot;.long 0xf0170c00&bslash;n&bslash;t&quot;
multiline_comment|/* pmove sp@,tt1 */
l_string|&quot;addl  #4,sp&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
r_static
id|__inline
r_void
id|jump_to_mover
(paren
r_void
op_star
comma
r_void
op_star
comma
r_void
op_star
comma
r_void
op_star
comma
r_int
comma
r_int
comma
r_void
op_star
)paren
id|__attribute__
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
DECL|function|jump_to_mover
r_static
id|__inline
r_void
id|jump_to_mover
(paren
r_void
op_star
id|kernel_start
comma
r_void
op_star
id|mem_start
comma
r_void
op_star
id|ramdisk_end
comma
r_void
op_star
id|mem_end
comma
r_int
id|kernel_size
comma
r_int
id|ramdisk_size
comma
r_void
op_star
id|mover_addr
)paren
(brace
id|asm
r_volatile
(paren
l_string|&quot;movel %0,a0&bslash;n&bslash;t&quot;
l_string|&quot;movel %1,a1&bslash;n&bslash;t&quot;
l_string|&quot;movel %2,a2&bslash;n&bslash;t&quot;
l_string|&quot;movel %3,a3&bslash;n&bslash;t&quot;
l_string|&quot;movel %4,d0&bslash;n&bslash;t&quot;
l_string|&quot;movel %5,d1&bslash;n&bslash;t&quot;
l_string|&quot;jmp   %6@&bslash;n&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;g&quot;
(paren
id|kernel_start
)paren
comma
l_string|&quot;g&quot;
(paren
id|mem_start
)paren
comma
l_string|&quot;g&quot;
(paren
id|ramdisk_end
)paren
comma
l_string|&quot;g&quot;
(paren
id|mem_end
)paren
comma
l_string|&quot;g&quot;
(paren
id|kernel_size
)paren
comma
l_string|&quot;g&quot;
(paren
id|ramdisk_size
)paren
comma
l_string|&quot;a&quot;
(paren
id|mover_addr
)paren
suffix:colon
l_string|&quot;a0&quot;
comma
l_string|&quot;a1&quot;
comma
l_string|&quot;a2&quot;
comma
l_string|&quot;a3&quot;
comma
l_string|&quot;d0&quot;
comma
l_string|&quot;d1&quot;
)paren
suffix:semicolon
multiline_comment|/* Avoid warning that function may return */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
macro_line|#endif /* BOOTSTRAP_H */
eof
