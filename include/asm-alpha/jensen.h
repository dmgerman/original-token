macro_line|#ifndef __ALPHA_JENSEN_H
DECL|macro|__ALPHA_JENSEN_H
mdefine_line|#define __ALPHA_JENSEN_H
multiline_comment|/*&n; * Defines for the AlphaPC EISA IO and memory address space.&n; */
multiline_comment|/*&n; * NOTE! Currently it never uses the HAE register, so these work only&n; * for the low 25 bits of EISA addressing.  That covers all of the IO&n; * address space (16 bits), and most of the &quot;normal&quot; EISA memory space.&n; * I&squot;ll fix it eventually, but I&squot;ll need to come up with a clean way&n; * to handle races with interrupt services wanting to change HAE...&n; */
multiline_comment|/*&n; * NOTE 2! The memory operations do not set any memory barriers, as it&squot;s&n; * not needed for cases like a frame buffer that is essentially memory-like.&n; * You need to do them by hand if the operations depend on ordering.&n; *&n; * Similarly, the port IO operations do a &quot;mb&quot; only after a write operation:&n; * if an mb is needed before (as in the case of doing memory mapped IO&n; * first, and then a port IO operation to the same device), it needs to be&n; * done by hand.&n; *&n; * After the above has bitten me 100 times, I&squot;ll give up and just do the&n; * mb all the time, but right now I&squot;m hoping this will work out.  Avoiding&n; * mb&squot;s may potentially be a noticeable speed improvement, but I can&squot;t&n; * honestly say I&squot;ve tested it.&n; *&n; * Handling interrupts that need to do mb&squot;s to synchronize to non-interrupts&n; * is another fun race area.  Don&squot;t do it (because if you do, I&squot;ll have to&n; * do *everything* with interrupts disabled, ugh).&n; */
multiline_comment|/*&n; * Virtual -&gt; physical identity mapping starts at this offset&n; */
DECL|macro|IDENT_ADDR
mdefine_line|#define IDENT_ADDR&t;(0xfffffc0000000000UL)
multiline_comment|/*&n; * EISA Interrupt Acknowledge address&n; */
DECL|macro|EISA_INTA
mdefine_line|#define EISA_INTA&t;&t;(IDENT_ADDR + 0x100000000UL)
multiline_comment|/*&n; * FEPROM addresses&n; */
DECL|macro|EISA_FEPROM0
mdefine_line|#define EISA_FEPROM0&t;&t;(IDENT_ADDR + 0x180000000UL)
DECL|macro|EISA_FEPROM1
mdefine_line|#define EISA_FEPROM1&t;&t;(IDENT_ADDR + 0x1A0000000UL)
multiline_comment|/*&n; * VL82C106 base address&n; */
DECL|macro|EISA_VL82C106
mdefine_line|#define EISA_VL82C106&t;&t;(IDENT_ADDR + 0x1C0000000UL)
multiline_comment|/*&n; * EISA &quot;Host Address Extension&quot; address (bits 25-31 of the EISA address)&n; */
DECL|macro|EISA_HAE
mdefine_line|#define EISA_HAE&t;&t;(IDENT_ADDR + 0x1D0000000UL)
multiline_comment|/*&n; * &quot;SYSCTL&quot; register address&n; */
DECL|macro|EISA_SYSCTL
mdefine_line|#define EISA_SYSCTL&t;&t;(IDENT_ADDR + 0x1E0000000UL)
multiline_comment|/*&n; * &quot;spare&quot; register address&n; */
DECL|macro|EISA_SPARE
mdefine_line|#define EISA_SPARE&t;&t;(IDENT_ADDR + 0x1F0000000UL)
multiline_comment|/*&n; * EISA memory address offset&n; */
DECL|macro|EISA_MEM
mdefine_line|#define EISA_MEM&t;&t;(IDENT_ADDR + 0x200000000UL)
multiline_comment|/*&n; * EISA IO address offset&n; */
DECL|macro|EISA_IO
mdefine_line|#define EISA_IO&t;&t;&t;(IDENT_ADDR + 0x300000000UL)
multiline_comment|/*&n; * IO functions&n; *&n; * The &quot;local&quot; functions are those that don&squot;t go out to the EISA bus,&n; * but instead act on the VL82C106 chip directly.. This is mainly the&n; * keyboard, RTC,  printer and first two serial lines..&n; *&n; * The local stuff makes for some complications, but it seems to be&n; * gone in the PCI version. I hope I can get DEC suckered^H^H^H^H^H^H^H^H&n; * convinced that I need one of the newer machines.&n; */
DECL|function|__local_inb
r_extern
r_inline
r_int
r_int
id|__local_inb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
id|result
op_assign
op_star
(paren
r_volatile
r_int
op_star
)paren
(paren
(paren
id|addr
op_lshift
l_int|9
)paren
op_plus
id|EISA_VL82C106
)paren
suffix:semicolon
r_return
l_int|0xffUL
op_amp
id|result
suffix:semicolon
)brace
DECL|function|__local_outb
r_extern
r_inline
r_void
id|__local_outb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
(paren
id|addr
op_lshift
l_int|9
)paren
op_plus
id|EISA_VL82C106
)paren
op_assign
id|b
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|__inb
r_extern
r_inline
r_int
r_int
id|__inb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
id|result
op_assign
op_star
(paren
r_volatile
r_int
op_star
)paren
(paren
(paren
id|addr
op_lshift
l_int|7
)paren
op_plus
id|EISA_IO
op_plus
l_int|0x00
)paren
suffix:semicolon
id|result
op_rshift_assign
(paren
id|addr
op_amp
l_int|3
)paren
op_star
l_int|8
suffix:semicolon
r_return
l_int|0xffUL
op_amp
id|result
suffix:semicolon
)brace
DECL|function|__outb
r_extern
r_inline
r_void
id|__outb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
(paren
id|addr
op_lshift
l_int|7
)paren
op_plus
id|EISA_IO
op_plus
l_int|0x00
)paren
op_assign
id|b
op_star
l_int|0x01010101
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is a stupid one: I&squot;ll make it a bitmap soon, promise..&n; *&n; * On the other hand: this allows gcc to optimize. Hmm. I&squot;ll&n; * have to use the __constant_p() stuff here.&n; */
DECL|function|__is_local
r_extern
r_inline
r_int
id|__is_local
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
multiline_comment|/* keyboard */
r_if
c_cond
(paren
id|addr
op_eq
l_int|0x60
op_logical_or
id|addr
op_eq
l_int|0x64
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* RTC */
r_if
c_cond
(paren
id|addr
op_eq
l_int|0x170
op_logical_or
id|addr
op_eq
l_int|0x171
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* motherboard COM2 */
r_if
c_cond
(paren
id|addr
op_ge
l_int|0x2f8
op_logical_and
id|addr
op_le
l_int|0x2ff
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* motherboard LPT1 */
r_if
c_cond
(paren
id|addr
op_ge
l_int|0x3bc
op_logical_and
id|addr
op_le
l_int|0x3be
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* motherboard COM2 */
r_if
c_cond
(paren
id|addr
op_ge
l_int|0x3f8
op_logical_and
id|addr
op_le
l_int|0x3ff
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|inb
r_extern
r_inline
r_int
r_int
id|inb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|__is_local
c_func
(paren
id|addr
)paren
)paren
r_return
id|__local_inb
c_func
(paren
id|addr
)paren
suffix:semicolon
r_return
id|__inb
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|outb
r_extern
r_inline
r_void
id|outb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|__is_local
c_func
(paren
id|addr
)paren
)paren
id|__local_outb
c_func
(paren
id|b
comma
id|addr
)paren
suffix:semicolon
r_else
id|__outb
c_func
(paren
id|b
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|function|inw
r_extern
r_inline
r_int
r_int
id|inw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
id|result
op_assign
op_star
(paren
r_volatile
r_int
op_star
)paren
(paren
(paren
id|addr
op_lshift
l_int|7
)paren
op_plus
id|EISA_IO
op_plus
l_int|0x20
)paren
suffix:semicolon
id|result
op_rshift_assign
(paren
id|addr
op_amp
l_int|3
)paren
op_star
l_int|8
suffix:semicolon
r_return
l_int|0xffffUL
op_amp
id|result
suffix:semicolon
)brace
DECL|function|inl
r_extern
r_inline
r_int
r_int
id|inl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
(paren
id|addr
op_lshift
l_int|7
)paren
op_plus
id|EISA_IO
op_plus
l_int|0x60
)paren
suffix:semicolon
)brace
DECL|function|outw
r_extern
r_inline
r_void
id|outw
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
(paren
id|addr
op_lshift
l_int|7
)paren
op_plus
id|EISA_IO
op_plus
l_int|0x20
)paren
op_assign
id|b
op_star
l_int|0x00010001
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|outl
r_extern
r_inline
r_void
id|outl
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
(paren
id|addr
op_lshift
l_int|7
)paren
op_plus
id|EISA_IO
op_plus
l_int|0x60
)paren
op_assign
id|b
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Memory functions&n; */
DECL|function|readb
r_extern
r_inline
r_int
r_int
id|readb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
id|result
op_assign
op_star
(paren
r_volatile
r_int
op_star
)paren
(paren
(paren
id|addr
op_lshift
l_int|7
)paren
op_plus
id|EISA_MEM
op_plus
l_int|0x00
)paren
suffix:semicolon
id|result
op_rshift_assign
(paren
id|addr
op_amp
l_int|3
)paren
op_star
l_int|8
suffix:semicolon
r_return
l_int|0xffUL
op_amp
id|result
suffix:semicolon
)brace
DECL|function|readw
r_extern
r_inline
r_int
r_int
id|readw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
id|result
op_assign
op_star
(paren
r_volatile
r_int
op_star
)paren
(paren
(paren
id|addr
op_lshift
l_int|7
)paren
op_plus
id|EISA_MEM
op_plus
l_int|0x20
)paren
suffix:semicolon
id|result
op_rshift_assign
(paren
id|addr
op_amp
l_int|3
)paren
op_star
l_int|8
suffix:semicolon
r_return
l_int|0xffffUL
op_amp
id|result
suffix:semicolon
)brace
DECL|function|readl
r_extern
r_inline
r_int
r_int
id|readl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
(paren
id|addr
op_lshift
l_int|7
)paren
op_plus
id|EISA_MEM
op_plus
l_int|0x60
)paren
suffix:semicolon
)brace
DECL|function|writeb
r_extern
r_inline
r_void
id|writeb
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
(paren
id|addr
op_lshift
l_int|7
)paren
op_plus
id|EISA_MEM
op_plus
l_int|0x00
)paren
op_assign
id|b
op_star
l_int|0x01010101
suffix:semicolon
)brace
DECL|function|writew
r_extern
r_inline
r_void
id|writew
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
(paren
id|addr
op_lshift
l_int|7
)paren
op_plus
id|EISA_MEM
op_plus
l_int|0x20
)paren
op_assign
id|b
op_star
l_int|0x00010001
suffix:semicolon
)brace
DECL|function|writel
r_extern
r_inline
r_void
id|writel
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
(paren
id|addr
op_lshift
l_int|7
)paren
op_plus
id|EISA_MEM
op_plus
l_int|0x60
)paren
op_assign
id|b
suffix:semicolon
)brace
DECL|macro|inb_p
mdefine_line|#define inb_p inb
DECL|macro|outb_p
mdefine_line|#define outb_p outb
multiline_comment|/*&n; * The Alpha Jensen hardware for some rather strange reason puts&n; * the RTC clock at 0x170 instead of 0x70. Probably due to some&n; * misguided idea about using 0x70 for NMI stuff.&n; *&n; * These defines will override the defaults when doing RTC queries&n; */
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)&t;(0x170+(x))
DECL|macro|RTC_ADDR
mdefine_line|#define RTC_ADDR(x)&t;(x)
DECL|macro|RTC_ALWAYS_BCD
mdefine_line|#define RTC_ALWAYS_BCD&t;0
macro_line|#endif
eof
