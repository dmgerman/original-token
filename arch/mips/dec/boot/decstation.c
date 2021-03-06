multiline_comment|/*&n; * arch/mips/dec/decstation.c&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|RELOC
mdefine_line|#define RELOC
DECL|macro|INITRD
mdefine_line|#define INITRD
DECL|macro|DEBUG_BOOT
mdefine_line|#define DEBUG_BOOT
multiline_comment|/*&n; * Magic number indicating REX PROM available on DECSTATION.&n; */
DECL|macro|REX_PROM_MAGIC
mdefine_line|#define&t;REX_PROM_MAGIC&t;&t;0x30464354
DECL|macro|REX_PROM_CLEARCACHE
mdefine_line|#define REX_PROM_CLEARCACHE&t;0x7c/4
DECL|macro|REX_PROM_PRINTF
mdefine_line|#define REX_PROM_PRINTF&t;&t;0x30/4
DECL|macro|VEC_RESET
mdefine_line|#define VEC_RESET&t;&t;0xBFC00000&t;&t;/* Prom base address */
DECL|macro|PMAX_PROM_ENTRY
mdefine_line|#define&t;PMAX_PROM_ENTRY(x)&t;(VEC_RESET+((x)*8))&t;/* Prom jump table */
DECL|macro|PMAX_PROM_PRINTF
mdefine_line|#define&t;PMAX_PROM_PRINTF&t;PMAX_PROM_ENTRY(17)
DECL|macro|PARAM
mdefine_line|#define PARAM&t;(k_start + 0x2000)
DECL|macro|LOADER_TYPE
mdefine_line|#define LOADER_TYPE (*(unsigned char *) (PARAM+0x210))
DECL|macro|INITRD_START
mdefine_line|#define INITRD_START (*(unsigned long *) (PARAM+0x218))
DECL|macro|INITRD_SIZE
mdefine_line|#define INITRD_SIZE (*(unsigned long *) (PARAM+0x21c))
r_extern
r_int
id|_ftext
comma
id|_end
suffix:semicolon
multiline_comment|/* begin and end of kernel image */
r_extern
r_void
op_star
id|__rd_start
comma
op_star
id|__rd_end
suffix:semicolon
multiline_comment|/* begin and end of ramdisk image */
r_extern
r_void
id|kernel_entry
c_func
(paren
r_int
comma
r_char
op_star
op_star
comma
r_int
r_int
comma
r_int
op_star
)paren
suffix:semicolon
DECL|function|memcpy
r_void
op_star
id|memcpy
c_func
(paren
r_void
op_star
id|dest
comma
r_const
r_void
op_star
id|src
comma
r_int
r_int
id|count
)paren
(brace
r_int
r_int
op_star
id|tmp
op_assign
(paren
r_int
r_int
op_star
)paren
id|dest
comma
op_star
id|s
op_assign
(paren
r_int
r_int
op_star
)paren
id|src
suffix:semicolon
id|count
op_rshift_assign
l_int|2
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
op_star
id|tmp
op_increment
op_assign
op_star
id|s
op_increment
suffix:semicolon
r_return
id|dest
suffix:semicolon
)brace
DECL|function|dec_entry
r_void
id|dec_entry
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
comma
r_int
r_int
id|magic
comma
r_int
op_star
id|prom_vec
)paren
(brace
r_void
(paren
op_star
id|rex_clear_cache
)paren
(paren
r_void
)paren
suffix:semicolon
r_int
(paren
op_star
id|prom_printf
)paren
(paren
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
r_int
r_int
id|k_start
comma
id|len
suffix:semicolon
multiline_comment|/*&n;&t; * The DS5100 leaves cpu with BEV enabled, clear it.&n;&t; */
id|asm
c_func
(paren
l_string|&quot;lui&bslash;t$8,0x3000&bslash;n&bslash;t&quot;
l_string|&quot;mtc0&bslash;t$8,$12&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t.sdata&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t.sbss&bslash;n&bslash;t&quot;
l_string|&quot;.section&bslash;t.text&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;$8&quot;
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_BOOT
r_if
c_cond
(paren
id|magic
op_eq
id|REX_PROM_MAGIC
)paren
(brace
id|prom_printf
op_assign
(paren
r_int
(paren
op_star
)paren
(paren
r_char
op_star
comma
dot
dot
dot
)paren
)paren
op_star
(paren
id|prom_vec
op_plus
id|REX_PROM_PRINTF
)paren
suffix:semicolon
)brace
r_else
(brace
id|prom_printf
op_assign
(paren
r_int
(paren
op_star
)paren
(paren
r_char
op_star
comma
dot
dot
dot
)paren
)paren
id|PMAX_PROM_PRINTF
suffix:semicolon
)brace
id|prom_printf
c_func
(paren
l_string|&quot;Launching kernel...&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|k_start
op_assign
(paren
r_int
r_int
)paren
(paren
op_amp
id|kernel_entry
)paren
op_amp
l_int|0xffff0000
suffix:semicolon
macro_line|#ifdef RELOC
multiline_comment|/*&n;&t; * Now copy kernel image to it&squot;s destination.&n;&t; */
id|len
op_assign
(paren
(paren
r_int
r_int
)paren
(paren
op_amp
id|_end
)paren
op_minus
id|k_start
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
id|k_start
comma
op_amp
id|_ftext
comma
id|len
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|magic
op_eq
id|REX_PROM_MAGIC
)paren
(brace
id|rex_clear_cache
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
r_void
)paren
)paren
op_star
(paren
id|prom_vec
op_plus
id|REX_PROM_CLEARCACHE
)paren
suffix:semicolon
id|rex_clear_cache
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
id|LOADER_TYPE
op_assign
l_int|1
suffix:semicolon
id|INITRD_START
op_assign
(paren
r_int
)paren
op_amp
id|__rd_start
suffix:semicolon
id|INITRD_SIZE
op_assign
(paren
r_int
)paren
op_amp
id|__rd_end
op_minus
(paren
r_int
)paren
op_amp
id|__rd_start
suffix:semicolon
macro_line|#endif
id|kernel_entry
c_func
(paren
id|argc
comma
id|argv
comma
id|magic
comma
id|prom_vec
)paren
suffix:semicolon
)brace
eof
