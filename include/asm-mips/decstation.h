multiline_comment|/*&n; * Hardware info about DEC Personal DECStation systems (otherwise known&n; * as maxine or pmax (internal DEC codenames).&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995 by Paul M. Antoine, some code and definitions are&n; * by curteousy of Chris Fraser.&n; *&n; * This file is under construction - you were warned!&n; */
macro_line|#ifndef __ASM_MIPS_PMAX_H 
DECL|macro|__ASM_MIPS_PMAX_H
mdefine_line|#define __ASM_MIPS_PMAX_H 
multiline_comment|/*&n; * The addresses below are virtual address. The mappings are&n; * created on startup via wired entries in the tlb.&n; */
DECL|macro|PMAX_LOCAL_IO_SPACE
mdefine_line|#define PMAX_LOCAL_IO_SPACE     0xe0000000
multiline_comment|/*&n; * Motherboard regs (kseg1 addresses)&n; */
DECL|macro|PMAX_SSR_ADDR
mdefine_line|#define PMAX_SSR_ADDR&t;&t;0xbc040100&t;&t;/* system support reg */
multiline_comment|/*&n; * SSR defines&n; */
DECL|macro|PMAX_SSR_LEDMASK
mdefine_line|#define PMAX_SSR_LEDMASK&t;0x00000001&t;&t;/* power LED */
multiline_comment|/*&n; * REX functions -- these are for the new TURBOchannel style ROMs&n; */
DECL|macro|REX_PROM_MAGIC
mdefine_line|#define REX_PROM_MAGIC  0x30464354&t;&t;&t;/* passed in a2 */
DECL|macro|REX_GETBITMAP
mdefine_line|#define REX_GETBITMAP&t;&t;0x84&t;&t;&t;/* get mem bitmap */
DECL|macro|REX_GETCHAR
mdefine_line|#define REX_GETCHAR&t;&t;0x24&t;&t;&t;/* getch() */
DECL|macro|REX_PUTCHAR
mdefine_line|#define REX_PUTCHAR&t;&t;0x13&t;&t;&t;/* putch() */
DECL|macro|REX_HALT
mdefine_line|#define REX_HALT&t;&t;0x9c&t;&t;&t;/* halt the system */
DECL|macro|REX_PRINTF
mdefine_line|#define REX_PRINTF&t;&t;0x30&t;&t;&t;/* printf() */
DECL|macro|REX_PUTS
mdefine_line|#define REX_PUTS&t;&t;0x2c&t;&t;&t;/* puts() */
DECL|macro|REX_SLOTADDR
mdefine_line|#define REX_SLOTADDR&t;&t;0x6c&t;&t;&t;/* slotaddr */
macro_line|#ifndef __LANGUAGE_ASSEMBLY__
DECL|function|pmax_set_led
r_extern
id|__inline__
r_void
id|pmax_set_led
c_func
(paren
r_int
r_int
id|bits
)paren
(brace
r_volatile
r_int
r_int
op_star
id|led_register
op_assign
(paren
r_int
r_int
op_star
)paren
id|PMAX_SSR_ADDR
suffix:semicolon
op_star
id|led_register
op_assign
id|bits
op_amp
id|PMAX_SSR_LEDMASK
suffix:semicolon
)brace
multiline_comment|/*&n; * Glue code to call the PMAX boot proms.&n; */
r_extern
id|asmlinkage
r_void
id|pmax_printf
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * These are just hacked out of the JAZZ ones, no ideas really.&n; */
DECL|macro|PMAX_KEYBOARD_ADDRESS
mdefine_line|#define PMAX_KEYBOARD_ADDRESS   0xe0005000
DECL|macro|PMAX_KEYBOARD_DATA
mdefine_line|#define PMAX_KEYBOARD_DATA      0xe0005000
DECL|macro|PMAX_KEYBOARD_COMMAND
mdefine_line|#define PMAX_KEYBOARD_COMMAND   0xe0005001
macro_line|#ifndef __LANGUAGE_ASSEMBLY__
r_typedef
r_struct
(brace
DECL|member|data
r_int
r_char
id|data
suffix:semicolon
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|typedef|pmax_keyboard_hardware
)brace
id|pmax_keyboard_hardware
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|pad0
r_int
r_char
id|pad0
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
suffix:semicolon
DECL|member|pad1
r_int
r_char
id|pad1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|command
r_int
r_char
id|command
suffix:semicolon
DECL|typedef|mips_keyboard_hardware
)brace
id|mips_keyboard_hardware
suffix:semicolon
multiline_comment|/*&n; * For now.&n; */
DECL|macro|keyboard_hardware
mdefine_line|#define keyboard_hardware       pmax_keyboard_hardware
macro_line|#endif
multiline_comment|/*&n; * Serial ports on DEC - maybe!&n; */
DECL|macro|PMAX_SERIAL1_BASE
mdefine_line|#define PMAX_SERIAL1_BASE       (unsigned int)0xe0006000
DECL|macro|PMAX_SERIAL2_BASE
mdefine_line|#define PMAX_SERIAL2_BASE       (unsigned int)0xe0007000
multiline_comment|/*&n; * Dummy Device Address. Used in pmaxdma.c&n; */
DECL|macro|PMAX_DUMMY_DEVICE
mdefine_line|#define PMAX_DUMMY_DEVICE       0xe000d000
multiline_comment|/*&n; * PMAX timer registers and interrupt no.&n; * Note that the hardware timer interrupt is actually on&n; * cpu level 6, but to keep compatibility with PC stuff&n; * it is remapped to vector 0. See arch/mips/kernel/entry.S.&n; */
DECL|macro|PMAX_TIMER_INTERVAL
mdefine_line|#define PMAX_TIMER_INTERVAL     0xe0000228
DECL|macro|PMAX_TIMER_REGISTER
mdefine_line|#define PMAX_TIMER_REGISTER     0xe0000230
multiline_comment|/*&n; * DRAM configuration register&n; */
macro_line|#ifndef __LANGUAGE_ASSEMBLY__
macro_line|#ifdef __MIPSEL__
r_typedef
r_struct
(brace
DECL|member|bank2
r_int
r_int
id|bank2
suffix:colon
l_int|3
suffix:semicolon
DECL|member|bank1
r_int
r_int
id|bank1
suffix:colon
l_int|3
suffix:semicolon
DECL|member|mem_bus_width
r_int
r_int
id|mem_bus_width
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
r_int
r_int
id|reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|page_mode
r_int
r_int
id|page_mode
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved1
r_int
r_int
id|reserved1
suffix:colon
l_int|23
suffix:semicolon
DECL|typedef|dram_configuration
)brace
id|dram_configuration
suffix:semicolon
macro_line|#else /* defined (__MIPSEB__) */
r_typedef
r_struct
(brace
DECL|member|reserved1
r_int
r_int
id|reserved1
suffix:colon
l_int|23
suffix:semicolon
DECL|member|page_mode
r_int
r_int
id|page_mode
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved2
r_int
r_int
id|reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|mem_bus_width
r_int
r_int
id|mem_bus_width
suffix:colon
l_int|1
suffix:semicolon
DECL|member|bank1
r_int
r_int
id|bank1
suffix:colon
l_int|3
suffix:semicolon
DECL|member|bank2
r_int
r_int
id|bank2
suffix:colon
l_int|3
suffix:semicolon
DECL|typedef|dram_configuration
)brace
id|dram_configuration
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __LANGUAGE_ASSEMBLY__ */
DECL|macro|PMAX_DRAM_CONFIG
mdefine_line|#define PMAX_DRAM_CONFIG        0xe00fffe0
multiline_comment|/*&n; * PMAX interrupt control registers&n; */
DECL|macro|PMAX_IO_IRQ_SOURCE
mdefine_line|#define PMAX_IO_IRQ_SOURCE      0xe0100000
DECL|macro|PMAX_IO_IRQ_ENABLE
mdefine_line|#define PMAX_IO_IRQ_ENABLE      0xe0100002
multiline_comment|/*&n; * PMAX interrupt enable bits&n; */
DECL|macro|PMAX_IE_PARALLEL
mdefine_line|#define PMAX_IE_PARALLEL            (1 &lt;&lt; 0)
DECL|macro|PMAX_IE_FLOPPY
mdefine_line|#define PMAX_IE_FLOPPY              (1 &lt;&lt; 1)
DECL|macro|PMAX_IE_SOUND
mdefine_line|#define PMAX_IE_SOUND               (1 &lt;&lt; 2)
DECL|macro|PMAX_IE_VIDEO
mdefine_line|#define PMAX_IE_VIDEO               (1 &lt;&lt; 3)
DECL|macro|PMAX_IE_ETHERNET
mdefine_line|#define PMAX_IE_ETHERNET            (1 &lt;&lt; 4)
DECL|macro|PMAX_IE_SCSI
mdefine_line|#define PMAX_IE_SCSI                (1 &lt;&lt; 5)
DECL|macro|PMAX_IE_KEYBOARD
mdefine_line|#define PMAX_IE_KEYBOARD            (1 &lt;&lt; 6)
DECL|macro|PMAX_IE_MOUSE
mdefine_line|#define PMAX_IE_MOUSE               (1 &lt;&lt; 7)
DECL|macro|PMAX_IE_SERIAL1
mdefine_line|#define PMAX_IE_SERIAL1             (1 &lt;&lt; 8)
DECL|macro|PMAX_IE_SERIAL2
mdefine_line|#define PMAX_IE_SERIAL2             (1 &lt;&lt; 9)
multiline_comment|/*&n; * PMAX Interrupt Level definitions&n; */
DECL|macro|PMAX_TIMER_IRQ
mdefine_line|#define PMAX_TIMER_IRQ          0
DECL|macro|PMAX_KEYBOARD_IRQ
mdefine_line|#define PMAX_KEYBOARD_IRQ       1
DECL|macro|PMAX_ETHERNET_IRQ
mdefine_line|#define PMAX_ETHERNET_IRQ       2 /* 15 */
DECL|macro|PMAX_SERIAL1_IRQ
mdefine_line|#define PMAX_SERIAL1_IRQ        3
DECL|macro|PMAX_SERIAL2_IRQ
mdefine_line|#define PMAX_SERIAL2_IRQ        4
DECL|macro|PMAX_PARALLEL_IRQ
mdefine_line|#define PMAX_PARALLEL_IRQ       5
DECL|macro|PMAX_FLOPPY_IRQ
mdefine_line|#define PMAX_FLOPPY_IRQ         6 /* needs to be consistent with floppy driver! */
multiline_comment|/*&n; * PMAX DMA Channels&n; * Note: Channels 4...7 are not used with respect to the Acer PICA-61&n; * chipset which does not provide these DMA channels.&n; */
DECL|macro|PMAX_SCSI_DMA
mdefine_line|#define PMAX_SCSI_DMA           0              /* SCSI */
DECL|macro|PMAX_FLOPPY_DMA
mdefine_line|#define PMAX_FLOPPY_DMA         1              /* FLOPPY */
DECL|macro|PMAX_AUDIOL_DMA
mdefine_line|#define PMAX_AUDIOL_DMA         2              /* AUDIO L */
DECL|macro|PMAX_AUDIOR_DMA
mdefine_line|#define PMAX_AUDIOR_DMA         3              /* AUDIO R */
multiline_comment|/*&n; * PMAX R4030 MCT_ADR chip (DMA controller)&n; * Note: Virtual Addresses !&n; */
DECL|macro|PMAX_R4030_CONFIG
mdefine_line|#define PMAX_R4030_CONFIG&t;0xE0000000&t;/* R4030 config register */
DECL|macro|PMAX_R4030_REVISION
mdefine_line|#define PMAX_R4030_REVISION     0xE0000008&t;/* same as PICA_ASIC_REVISION */
DECL|macro|PMAX_R4030_INV_ADDR
mdefine_line|#define PMAX_R4030_INV_ADDR&t;0xE0000010&t;/* Invalid Address register */
DECL|macro|PMAX_R4030_TRSTBL_BASE
mdefine_line|#define PMAX_R4030_TRSTBL_BASE  0xE0000018&t;/* Translation Table Base */
DECL|macro|PMAX_R4030_TRSTBL_LIM
mdefine_line|#define PMAX_R4030_TRSTBL_LIM   0xE0000020&t;/* Translation Table Limit */
DECL|macro|PMAX_R4030_TRSTBL_INV
mdefine_line|#define PMAX_R4030_TRSTBL_INV   0xE0000028&t;/* Translation Table Invalidate */
DECL|macro|PMAX_R4030_CACHE_MTNC
mdefine_line|#define PMAX_R4030_CACHE_MTNC   0xE0000030&t;/* Cache Maintenance */
DECL|macro|PMAX_R4030_R_FAIL_ADDR
mdefine_line|#define PMAX_R4030_R_FAIL_ADDR  0xE0000038&t;/* Remote Failed Address */
DECL|macro|PMAX_R4030_M_FAIL_ADDR
mdefine_line|#define PMAX_R4030_M_FAIL_ADDR  0xE0000040&t;/* Memory Failed Adresss */
DECL|macro|PMAX_R4030_CACHE_PTAG
mdefine_line|#define PMAX_R4030_CACHE_PTAG   0xE0000048&t;/* I/O Cache Physical Tag */
DECL|macro|PMAX_R4030_CACHE_LTAG
mdefine_line|#define PMAX_R4030_CACHE_LTAG   0xE0000050&t;/* I/O Cache Logical Tag */
DECL|macro|PMAX_R4030_CACHE_BMASK
mdefine_line|#define PMAX_R4030_CACHE_BMASK  0xE0000058&t;/* I/O Cache Byte Mask */
DECL|macro|PMAX_R4030_CACHE_BWIN
mdefine_line|#define PMAX_R4030_CACHE_BWIN   0xE0000060&t;/* I/O Cache Buffer Window */
multiline_comment|/*&n; * Remote Speed Registers. &n; *&n; *  0: free,      1: Ethernet,  2: SCSI,      3: Floppy,&n; *  4: RTC,       5: Kb./Mouse  6: serial 1,  7: serial 2,&n; *  8: parallel,  9: NVRAM,    10: CPU,      11: PROM,&n; * 12: reserved, 13: free,     14: 7seg LED, 15: ???&n; */
DECL|macro|PMAX_R4030_REM_SPEED
mdefine_line|#define PMAX_R4030_REM_SPEED&t;0xE0000070&t;/* 16 Remote Speed Registers */
multiline_comment|/* 0xE0000070,78,80... 0xE00000E8 */
DECL|macro|PMAX_R4030_IRQ_ENABLE
mdefine_line|#define PMAX_R4030_IRQ_ENABLE   0xE00000E8&t;/* Internal Interrupt Enable */
DECL|macro|PMAX_R4030_IRQ_SOURCE
mdefine_line|#define PMAX_R4030_IRQ_SOURCE   0xE0000200&t;/* Interrupt Source Reg */
DECL|macro|PMAX_R4030_I386_ERROR
mdefine_line|#define PMAX_R4030_I386_ERROR   0xE0000208&t;/* i386/EISA Bus Error */
multiline_comment|/*&n; * Access the R4030 DMA and I/O Controller&n; */
macro_line|#ifndef __LANGUAGE_ASSEMBLY__
DECL|function|r4030_read_reg16
r_extern
r_inline
r_int
r_int
id|r4030_read_reg16
c_func
(paren
r_int
id|addr
)paren
(brace
r_int
r_int
id|ret
op_assign
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;nop; nop; nop; nop;&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|r4030_read_reg32
r_extern
r_inline
r_int
r_int
id|r4030_read_reg32
c_func
(paren
r_int
id|addr
)paren
(brace
r_int
r_int
id|ret
op_assign
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;nop; nop; nop; nop;&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|r4030_write_reg16
r_extern
r_inline
r_void
id|r4030_write_reg16
c_func
(paren
r_int
id|addr
comma
r_int
id|val
)paren
(brace
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
)paren
op_assign
id|val
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;nop; nop; nop; nop;&quot;
)paren
suffix:semicolon
)brace
DECL|function|r4030_write_reg32
r_extern
r_inline
r_int
r_int
id|r4030_write_reg32
c_func
(paren
r_int
id|addr
comma
r_int
id|val
)paren
(brace
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
id|addr
)paren
op_assign
id|val
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;nop; nop; nop; nop;&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* !LANGUAGE_ASSEMBLY__ */
macro_line|#endif /* __ASM_MIPS_PMAX_H */
eof
