multiline_comment|/*&n; * drivers/sbus/audio/amd7930.c&n; *&n; * Copyright (C) 1996 Thomas K. Dyas (tdyas@noc.rutgers.edu)&n; *&n; * This is the lowlevel driver for the AMD7930 audio chip found on all&n; * sun4c machines and some sun4m machines.&n; *&n; * XXX Add note about the fun of getting the docs.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &quot;audio.h&quot;
macro_line|#include &quot;amd7930.h&quot;
DECL|macro|MAX_DRIVERS
mdefine_line|#define MAX_DRIVERS 1
multiline_comment|/* Private information we store for each amd7930 chip. */
DECL|struct|amd7930_info
r_struct
id|amd7930_info
(brace
multiline_comment|/* Current buffer that the driver is playing. */
DECL|member|output_ptr
r_volatile
id|__u8
op_star
id|output_ptr
suffix:semicolon
DECL|member|output_count
r_volatile
r_int
r_int
id|output_count
suffix:semicolon
multiline_comment|/* Current record buffer. */
DECL|member|input_ptr
r_volatile
id|__u8
op_star
id|input_ptr
suffix:semicolon
DECL|member|input_count
r_volatile
r_int
r_int
id|input_count
suffix:semicolon
multiline_comment|/* Device registers information. */
DECL|member|regs
r_struct
id|amd7930
op_star
id|regs
suffix:semicolon
DECL|member|regs_size
r_int
r_int
id|regs_size
suffix:semicolon
DECL|member|map
r_struct
id|amd7930_map
id|map
suffix:semicolon
multiline_comment|/* Device interrupt information. */
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|ints_on
r_volatile
r_int
id|ints_on
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Output a 16-bit quantity in the order that the amd7930 expects. */
DECL|macro|amd7930_out16
mdefine_line|#define amd7930_out16(regs,v) ({ regs-&gt;dr = v &amp; 0xFF; regs-&gt;dr = (v &gt;&gt; 8) &amp; 0xFF; })
multiline_comment|/*&n; * gx, gr &amp; stg gains.  this table must contain 256 elements with&n; * the 0th being &quot;infinity&quot; (the magic value 9008).  The remaining&n; * elements match sun&squot;s gain curve (but with higher resolution):&n; * -18 to 0dB in .16dB steps then 0 to 12dB in .08dB steps.&n; */
DECL|variable|gx_coeff
r_static
id|__const__
id|__u16
id|gx_coeff
(braket
l_int|256
)braket
op_assign
(brace
l_int|0x9008
comma
l_int|0x8b7c
comma
l_int|0x8b51
comma
l_int|0x8b45
comma
l_int|0x8b42
comma
l_int|0x8b3b
comma
l_int|0x8b36
comma
l_int|0x8b33
comma
l_int|0x8b32
comma
l_int|0x8b2a
comma
l_int|0x8b2b
comma
l_int|0x8b2c
comma
l_int|0x8b25
comma
l_int|0x8b23
comma
l_int|0x8b22
comma
l_int|0x8b22
comma
l_int|0x9122
comma
l_int|0x8b1a
comma
l_int|0x8aa3
comma
l_int|0x8aa3
comma
l_int|0x8b1c
comma
l_int|0x8aa6
comma
l_int|0x912d
comma
l_int|0x912b
comma
l_int|0x8aab
comma
l_int|0x8b12
comma
l_int|0x8aaa
comma
l_int|0x8ab2
comma
l_int|0x9132
comma
l_int|0x8ab4
comma
l_int|0x913c
comma
l_int|0x8abb
comma
l_int|0x9142
comma
l_int|0x9144
comma
l_int|0x9151
comma
l_int|0x8ad5
comma
l_int|0x8aeb
comma
l_int|0x8a79
comma
l_int|0x8a5a
comma
l_int|0x8a4a
comma
l_int|0x8b03
comma
l_int|0x91c2
comma
l_int|0x91bb
comma
l_int|0x8a3f
comma
l_int|0x8a33
comma
l_int|0x91b2
comma
l_int|0x9212
comma
l_int|0x9213
comma
l_int|0x8a2c
comma
l_int|0x921d
comma
l_int|0x8a23
comma
l_int|0x921a
comma
l_int|0x9222
comma
l_int|0x9223
comma
l_int|0x922d
comma
l_int|0x9231
comma
l_int|0x9234
comma
l_int|0x9242
comma
l_int|0x925b
comma
l_int|0x92dd
comma
l_int|0x92c1
comma
l_int|0x92b3
comma
l_int|0x92ab
comma
l_int|0x92a4
comma
l_int|0x92a2
comma
l_int|0x932b
comma
l_int|0x9341
comma
l_int|0x93d3
comma
l_int|0x93b2
comma
l_int|0x93a2
comma
l_int|0x943c
comma
l_int|0x94b2
comma
l_int|0x953a
comma
l_int|0x9653
comma
l_int|0x9782
comma
l_int|0x9e21
comma
l_int|0x9d23
comma
l_int|0x9cd2
comma
l_int|0x9c23
comma
l_int|0x9baa
comma
l_int|0x9bde
comma
l_int|0x9b33
comma
l_int|0x9b22
comma
l_int|0x9b1d
comma
l_int|0x9ab2
comma
l_int|0xa142
comma
l_int|0xa1e5
comma
l_int|0x9a3b
comma
l_int|0xa213
comma
l_int|0xa1a2
comma
l_int|0xa231
comma
l_int|0xa2eb
comma
l_int|0xa313
comma
l_int|0xa334
comma
l_int|0xa421
comma
l_int|0xa54b
comma
l_int|0xada4
comma
l_int|0xac23
comma
l_int|0xab3b
comma
l_int|0xaaab
comma
l_int|0xaa5c
comma
l_int|0xb1a3
comma
l_int|0xb2ca
comma
l_int|0xb3bd
comma
l_int|0xbe24
comma
l_int|0xbb2b
comma
l_int|0xba33
comma
l_int|0xc32b
comma
l_int|0xcb5a
comma
l_int|0xd2a2
comma
l_int|0xe31d
comma
l_int|0x0808
comma
l_int|0x72ba
comma
l_int|0x62c2
comma
l_int|0x5c32
comma
l_int|0x52db
comma
l_int|0x513e
comma
l_int|0x4cce
comma
l_int|0x43b2
comma
l_int|0x4243
comma
l_int|0x41b4
comma
l_int|0x3b12
comma
l_int|0x3bc3
comma
l_int|0x3df2
comma
l_int|0x34bd
comma
l_int|0x3334
comma
l_int|0x32c2
comma
l_int|0x3224
comma
l_int|0x31aa
comma
l_int|0x2a7b
comma
l_int|0x2aaa
comma
l_int|0x2b23
comma
l_int|0x2bba
comma
l_int|0x2c42
comma
l_int|0x2e23
comma
l_int|0x25bb
comma
l_int|0x242b
comma
l_int|0x240f
comma
l_int|0x231a
comma
l_int|0x22bb
comma
l_int|0x2241
comma
l_int|0x2223
comma
l_int|0x221f
comma
l_int|0x1a33
comma
l_int|0x1a4a
comma
l_int|0x1acd
comma
l_int|0x2132
comma
l_int|0x1b1b
comma
l_int|0x1b2c
comma
l_int|0x1b62
comma
l_int|0x1c12
comma
l_int|0x1c32
comma
l_int|0x1d1b
comma
l_int|0x1e71
comma
l_int|0x16b1
comma
l_int|0x1522
comma
l_int|0x1434
comma
l_int|0x1412
comma
l_int|0x1352
comma
l_int|0x1323
comma
l_int|0x1315
comma
l_int|0x12bc
comma
l_int|0x127a
comma
l_int|0x1235
comma
l_int|0x1226
comma
l_int|0x11a2
comma
l_int|0x1216
comma
l_int|0x0a2a
comma
l_int|0x11bc
comma
l_int|0x11d1
comma
l_int|0x1163
comma
l_int|0x0ac2
comma
l_int|0x0ab2
comma
l_int|0x0aab
comma
l_int|0x0b1b
comma
l_int|0x0b23
comma
l_int|0x0b33
comma
l_int|0x0c0f
comma
l_int|0x0bb3
comma
l_int|0x0c1b
comma
l_int|0x0c3e
comma
l_int|0x0cb1
comma
l_int|0x0d4c
comma
l_int|0x0ec1
comma
l_int|0x079a
comma
l_int|0x0614
comma
l_int|0x0521
comma
l_int|0x047c
comma
l_int|0x0422
comma
l_int|0x03b1
comma
l_int|0x03e3
comma
l_int|0x0333
comma
l_int|0x0322
comma
l_int|0x031c
comma
l_int|0x02aa
comma
l_int|0x02ba
comma
l_int|0x02f2
comma
l_int|0x0242
comma
l_int|0x0232
comma
l_int|0x0227
comma
l_int|0x0222
comma
l_int|0x021b
comma
l_int|0x01ad
comma
l_int|0x0212
comma
l_int|0x01b2
comma
l_int|0x01bb
comma
l_int|0x01cb
comma
l_int|0x01f6
comma
l_int|0x0152
comma
l_int|0x013a
comma
l_int|0x0133
comma
l_int|0x0131
comma
l_int|0x012c
comma
l_int|0x0123
comma
l_int|0x0122
comma
l_int|0x00a2
comma
l_int|0x011b
comma
l_int|0x011e
comma
l_int|0x0114
comma
l_int|0x00b1
comma
l_int|0x00aa
comma
l_int|0x00b3
comma
l_int|0x00bd
comma
l_int|0x00ba
comma
l_int|0x00c5
comma
l_int|0x00d3
comma
l_int|0x00f3
comma
l_int|0x0062
comma
l_int|0x0051
comma
l_int|0x0042
comma
l_int|0x003b
comma
l_int|0x0033
comma
l_int|0x0032
comma
l_int|0x002a
comma
l_int|0x002c
comma
l_int|0x0025
comma
l_int|0x0023
comma
l_int|0x0022
comma
l_int|0x001a
comma
l_int|0x0021
comma
l_int|0x001b
comma
l_int|0x001b
comma
l_int|0x001d
comma
l_int|0x0015
comma
l_int|0x0013
comma
l_int|0x0013
comma
l_int|0x0012
comma
l_int|0x0012
comma
l_int|0x000a
comma
l_int|0x000a
comma
l_int|0x0011
comma
l_int|0x0011
comma
l_int|0x000b
comma
l_int|0x000b
comma
l_int|0x000c
comma
l_int|0x000e
comma
)brace
suffix:semicolon
DECL|variable|ger_coeff
r_static
id|__const__
id|__u16
id|ger_coeff
(braket
)braket
op_assign
(brace
l_int|0x431f
comma
multiline_comment|/* 5. dB */
l_int|0x331f
comma
multiline_comment|/* 5.5 dB */
l_int|0x40dd
comma
multiline_comment|/* 6. dB */
l_int|0x11dd
comma
multiline_comment|/* 6.5 dB */
l_int|0x440f
comma
multiline_comment|/* 7. dB */
l_int|0x411f
comma
multiline_comment|/* 7.5 dB */
l_int|0x311f
comma
multiline_comment|/* 8. dB */
l_int|0x5520
comma
multiline_comment|/* 8.5 dB */
l_int|0x10dd
comma
multiline_comment|/* 9. dB */
l_int|0x4211
comma
multiline_comment|/* 9.5 dB */
l_int|0x410f
comma
multiline_comment|/* 10. dB */
l_int|0x111f
comma
multiline_comment|/* 10.5 dB */
l_int|0x600b
comma
multiline_comment|/* 11. dB */
l_int|0x00dd
comma
multiline_comment|/* 11.5 dB */
l_int|0x4210
comma
multiline_comment|/* 12. dB */
l_int|0x110f
comma
multiline_comment|/* 13. dB */
l_int|0x7200
comma
multiline_comment|/* 14. dB */
l_int|0x2110
comma
multiline_comment|/* 15. dB */
l_int|0x2200
comma
multiline_comment|/* 15.9 dB */
l_int|0x000b
comma
multiline_comment|/* 16.9 dB */
l_int|0x000f
multiline_comment|/* 18. dB */
)brace
suffix:semicolon
DECL|macro|NR_GER_COEFFS
mdefine_line|#define NR_GER_COEFFS (sizeof(ger_coeff) / sizeof(ger_coeff[0]))
multiline_comment|/* Enable amd7930 interrupts atomically. */
DECL|function|amd7930_enable_ints
r_static
id|__inline__
r_void
id|amd7930_enable_ints
c_func
(paren
r_struct
id|sparcaudio_driver
op_star
id|drv
)paren
(brace
r_struct
id|amd7930_info
op_star
id|info
op_assign
(paren
r_struct
id|amd7930_info
op_star
)paren
id|drv
op_member_access_from_pointer
r_private
suffix:semicolon
r_register
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;ints_on
)paren
r_return
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|info-&gt;regs-&gt;cr
op_assign
id|AMR_INIT
suffix:semicolon
id|info-&gt;regs-&gt;dr
op_assign
id|AM_INIT_ACTIVE
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|info-&gt;ints_on
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Disable amd7930 interrupts atomically. */
DECL|function|amd7930_disable_ints
r_static
id|__inline__
r_void
id|amd7930_disable_ints
c_func
(paren
r_struct
id|sparcaudio_driver
op_star
id|drv
)paren
(brace
r_struct
id|amd7930_info
op_star
id|info
op_assign
(paren
r_struct
id|amd7930_info
op_star
)paren
id|drv
op_member_access_from_pointer
r_private
suffix:semicolon
r_register
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;ints_on
)paren
r_return
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|info-&gt;regs-&gt;cr
op_assign
id|AMR_INIT
suffix:semicolon
id|info-&gt;regs-&gt;dr
op_assign
id|AM_INIT_ACTIVE
op_or
id|AM_INIT_DISABLE_INTS
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|info-&gt;ints_on
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Commit the local copy of the MAP registers to the amd7930. */
DECL|function|amd7930_commit_map
r_static
r_void
id|amd7930_commit_map
c_func
(paren
r_struct
id|sparcaudio_driver
op_star
id|drv
)paren
(brace
r_struct
id|amd7930_info
op_star
id|info
op_assign
(paren
r_struct
id|amd7930_info
op_star
)paren
id|drv
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|amd7930
op_star
id|regs
op_assign
id|info-&gt;regs
suffix:semicolon
r_struct
id|amd7930_map
op_star
id|map
op_assign
op_amp
id|info-&gt;map
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|regs-&gt;cr
op_assign
id|AMR_MAP_GX
suffix:semicolon
id|amd7930_out16
c_func
(paren
id|regs
comma
id|map-&gt;gx
)paren
suffix:semicolon
id|regs-&gt;cr
op_assign
id|AMR_MAP_GR
suffix:semicolon
id|amd7930_out16
c_func
(paren
id|regs
comma
id|map-&gt;gr
)paren
suffix:semicolon
id|regs-&gt;cr
op_assign
id|AMR_MAP_STGR
suffix:semicolon
id|amd7930_out16
c_func
(paren
id|regs
comma
id|map-&gt;stgr
)paren
suffix:semicolon
id|regs-&gt;cr
op_assign
id|AMR_MAP_GER
suffix:semicolon
id|amd7930_out16
c_func
(paren
id|regs
comma
id|map-&gt;ger
)paren
suffix:semicolon
id|regs-&gt;cr
op_assign
id|AMR_MAP_MMR1
suffix:semicolon
id|regs-&gt;dr
op_assign
id|map-&gt;mmr1
suffix:semicolon
id|regs-&gt;cr
op_assign
id|AMR_MAP_MMR2
suffix:semicolon
id|regs-&gt;dr
op_assign
id|map-&gt;mmr2
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Interrupt handler (The chip takes only one byte per interrupt. Grrr!) */
DECL|function|amd7930_interrupt
r_static
r_void
id|amd7930_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|intr_regs
)paren
(brace
r_struct
id|sparcaudio_driver
op_star
id|drv
op_assign
(paren
r_struct
id|sparcaudio_driver
op_star
)paren
id|dev_id
suffix:semicolon
r_struct
id|amd7930_info
op_star
id|info
op_assign
(paren
r_struct
id|amd7930_info
op_star
)paren
id|drv
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|amd7930
op_star
id|regs
op_assign
id|info-&gt;regs
suffix:semicolon
id|__u8
id|dummy
suffix:semicolon
multiline_comment|/* Clear the interrupt. */
id|dummy
op_assign
id|regs-&gt;ir
suffix:semicolon
multiline_comment|/* Send the next byte of outgoing data. */
r_if
c_cond
(paren
id|info-&gt;output_ptr
op_logical_and
id|info-&gt;output_count
OG
l_int|0
)paren
(brace
multiline_comment|/* Send the next byte and advance buffer pointer. */
id|regs-&gt;bbtb
op_assign
op_star
(paren
id|info-&gt;output_ptr
)paren
suffix:semicolon
id|info-&gt;output_ptr
op_increment
suffix:semicolon
id|info-&gt;output_count
op_decrement
suffix:semicolon
multiline_comment|/* Done with the buffer? Notify the midlevel driver. */
r_if
c_cond
(paren
id|info-&gt;output_count
op_eq
l_int|0
)paren
(brace
id|info-&gt;output_ptr
op_assign
l_int|NULL
suffix:semicolon
id|info-&gt;output_count
op_assign
l_int|0
suffix:semicolon
id|sparcaudio_output_done
c_func
(paren
id|drv
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Read the next byte of incoming data. */
r_if
c_cond
(paren
id|info-&gt;input_ptr
op_logical_and
id|info-&gt;input_count
OG
l_int|0
)paren
(brace
multiline_comment|/* Get the next byte and advance buffer pointer. */
op_star
(paren
id|info-&gt;input_ptr
)paren
op_assign
id|regs-&gt;bbrb
suffix:semicolon
id|info-&gt;input_ptr
op_increment
suffix:semicolon
id|info-&gt;input_count
op_decrement
suffix:semicolon
multiline_comment|/* Done with the buffer? Notify the midlevel driver. */
r_if
c_cond
(paren
id|info-&gt;input_count
op_eq
l_int|0
)paren
(brace
id|info-&gt;input_ptr
op_assign
l_int|NULL
suffix:semicolon
id|info-&gt;input_count
op_assign
l_int|0
suffix:semicolon
id|sparcaudio_input_done
c_func
(paren
id|drv
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|amd7930_open
r_static
r_int
id|amd7930_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_struct
id|sparcaudio_driver
op_star
id|drv
)paren
(brace
r_struct
id|amd7930_info
op_star
id|info
op_assign
(paren
r_struct
id|amd7930_info
op_star
)paren
id|drv
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
id|level
suffix:semicolon
multiline_comment|/* Set the default audio parameters. */
id|info-&gt;map.gx
op_assign
id|gx_coeff
(braket
l_int|128
)braket
suffix:semicolon
id|info-&gt;map.stgr
op_assign
id|gx_coeff
(braket
l_int|0
)braket
suffix:semicolon
id|level
op_assign
(paren
l_int|128
op_star
(paren
l_int|256
op_plus
id|NR_GER_COEFFS
)paren
)paren
op_rshift
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|level
op_ge
l_int|256
)paren
(brace
id|info-&gt;map.ger
op_assign
id|ger_coeff
(braket
id|level
op_minus
l_int|256
)braket
suffix:semicolon
id|info-&gt;map.gr
op_assign
id|gx_coeff
(braket
l_int|255
)braket
suffix:semicolon
)brace
r_else
(brace
id|info-&gt;map.ger
op_assign
id|ger_coeff
(braket
l_int|0
)braket
suffix:semicolon
id|info-&gt;map.gr
op_assign
id|gx_coeff
(braket
id|level
)braket
suffix:semicolon
)brace
id|info-&gt;map.mmr2
op_or_assign
id|AM_MAP_MMR2_LS
suffix:semicolon
id|amd7930_commit_map
c_func
(paren
id|drv
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amd7930_release
r_static
r_void
id|amd7930_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_struct
id|sparcaudio_driver
op_star
id|drv
)paren
(brace
id|amd7930_disable_ints
c_func
(paren
id|drv
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|amd7930_start_output
r_static
r_void
id|amd7930_start_output
c_func
(paren
r_struct
id|sparcaudio_driver
op_star
id|drv
comma
id|__u8
op_star
id|buffer
comma
r_int
r_int
id|count
)paren
(brace
r_struct
id|amd7930_info
op_star
id|info
op_assign
(paren
r_struct
id|amd7930_info
op_star
)paren
id|drv
op_member_access_from_pointer
r_private
suffix:semicolon
id|info-&gt;output_ptr
op_assign
id|buffer
suffix:semicolon
id|info-&gt;output_count
op_assign
id|count
suffix:semicolon
id|amd7930_enable_ints
c_func
(paren
id|drv
)paren
suffix:semicolon
)brace
DECL|function|amd7930_stop_output
r_static
r_void
id|amd7930_stop_output
c_func
(paren
r_struct
id|sparcaudio_driver
op_star
id|drv
)paren
(brace
r_struct
id|amd7930_info
op_star
id|info
op_assign
(paren
r_struct
id|amd7930_info
op_star
)paren
id|drv
op_member_access_from_pointer
r_private
suffix:semicolon
id|info-&gt;output_ptr
op_assign
l_int|NULL
suffix:semicolon
id|info-&gt;output_count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;input_ptr
)paren
id|amd7930_disable_ints
c_func
(paren
id|drv
)paren
suffix:semicolon
)brace
DECL|function|amd7930_start_input
r_static
r_void
id|amd7930_start_input
c_func
(paren
r_struct
id|sparcaudio_driver
op_star
id|drv
comma
id|__u8
op_star
id|buffer
comma
r_int
r_int
id|count
)paren
(brace
r_struct
id|amd7930_info
op_star
id|info
op_assign
(paren
r_struct
id|amd7930_info
op_star
)paren
id|drv
op_member_access_from_pointer
r_private
suffix:semicolon
id|info-&gt;input_ptr
op_assign
id|buffer
suffix:semicolon
id|info-&gt;input_count
op_assign
id|count
suffix:semicolon
id|amd7930_enable_ints
c_func
(paren
id|drv
)paren
suffix:semicolon
)brace
DECL|function|amd7930_stop_input
r_static
r_void
id|amd7930_stop_input
c_func
(paren
r_struct
id|sparcaudio_driver
op_star
id|drv
)paren
(brace
r_struct
id|amd7930_info
op_star
id|info
op_assign
(paren
r_struct
id|amd7930_info
op_star
)paren
id|drv
op_member_access_from_pointer
r_private
suffix:semicolon
id|info-&gt;input_ptr
op_assign
l_int|NULL
suffix:semicolon
id|info-&gt;input_count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;output_ptr
)paren
id|amd7930_disable_ints
c_func
(paren
id|drv
)paren
suffix:semicolon
)brace
DECL|function|amd7930_sunaudio_getdev
r_static
r_void
id|amd7930_sunaudio_getdev
c_func
(paren
r_struct
id|sparcaudio_driver
op_star
id|drv
comma
id|audio_device_t
op_star
id|audinfo
)paren
(brace
id|strncpy
c_func
(paren
id|audinfo-&gt;name
comma
l_string|&quot;amd7930&quot;
comma
r_sizeof
(paren
id|audinfo-&gt;name
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|audinfo-&gt;version
comma
l_string|&quot;x&quot;
comma
r_sizeof
(paren
id|audinfo-&gt;version
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|audinfo-&gt;config
comma
l_string|&quot;audio&quot;
comma
r_sizeof
(paren
id|audinfo-&gt;config
)paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Device detection and initialization.&n; */
DECL|variable|drivers
r_static
r_struct
id|sparcaudio_driver
id|drivers
(braket
id|MAX_DRIVERS
)braket
suffix:semicolon
DECL|variable|num_drivers
r_static
r_int
id|num_drivers
suffix:semicolon
DECL|variable|amd7930_ops
r_static
r_struct
id|sparcaudio_operations
id|amd7930_ops
op_assign
(brace
id|amd7930_open
comma
id|amd7930_release
comma
l_int|NULL
comma
multiline_comment|/* amd7930_ioctl */
id|amd7930_start_output
comma
id|amd7930_stop_output
comma
id|amd7930_start_input
comma
id|amd7930_stop_input
comma
id|amd7930_sunaudio_getdev
comma
)brace
suffix:semicolon
multiline_comment|/* Attach to an amd7930 chip given its PROM node. */
DECL|function|amd7930_attach
r_static
r_int
id|amd7930_attach
c_func
(paren
r_struct
id|sparcaudio_driver
op_star
id|drv
comma
r_int
id|node
comma
r_struct
id|linux_sbus
op_star
id|sbus
comma
r_struct
id|linux_sbus_device
op_star
id|sdev
)paren
(brace
r_struct
id|linux_prom_registers
id|regs
suffix:semicolon
r_struct
id|linux_prom_irqs
id|irq
suffix:semicolon
r_struct
id|amd7930_info
op_star
id|info
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/* Allocate our private information structure. */
id|drv
op_member_access_from_pointer
r_private
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|amd7930_info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|drv
op_member_access_from_pointer
r_private
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* Point at the information structure and initialize it. */
id|drv-&gt;ops
op_assign
op_amp
id|amd7930_ops
suffix:semicolon
id|info
op_assign
(paren
r_struct
id|amd7930_info
op_star
)paren
id|drv
op_member_access_from_pointer
r_private
suffix:semicolon
id|info-&gt;output_ptr
op_assign
id|info-&gt;input_ptr
op_assign
l_int|NULL
suffix:semicolon
id|info-&gt;output_count
op_assign
id|info-&gt;input_count
op_assign
l_int|0
suffix:semicolon
id|info-&gt;ints_on
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* force disable below */
multiline_comment|/* Map the registers into memory. */
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;reg&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|regs
comma
r_sizeof
(paren
id|regs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sbus
op_logical_and
id|sdev
)paren
id|prom_apply_sbus_ranges
c_func
(paren
id|sbus
comma
op_amp
id|regs
comma
l_int|1
comma
id|sdev
)paren
suffix:semicolon
id|info-&gt;regs_size
op_assign
id|regs.reg_size
suffix:semicolon
id|info-&gt;regs
op_assign
id|sparc_alloc_io
c_func
(paren
id|regs.phys_addr
comma
l_int|0
comma
id|regs.reg_size
comma
l_string|&quot;amd7930&quot;
comma
id|regs.which_io
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info-&gt;regs
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;amd7930: could not allocate registers&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|drv
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* Disable amd7930 interrupt generation. */
id|amd7930_disable_ints
c_func
(paren
id|drv
)paren
suffix:semicolon
multiline_comment|/* Initialize the MUX unit to connect the MAP to the CPU. */
id|info-&gt;regs-&gt;cr
op_assign
id|AMR_MUX_1_4
suffix:semicolon
id|info-&gt;regs-&gt;dr
op_assign
(paren
id|AM_MUX_CHANNEL_Bb
op_lshift
l_int|4
)paren
op_or
id|AM_MUX_CHANNEL_Ba
suffix:semicolon
id|info-&gt;regs-&gt;dr
op_assign
l_int|0
suffix:semicolon
id|info-&gt;regs-&gt;dr
op_assign
l_int|0
suffix:semicolon
id|info-&gt;regs-&gt;dr
op_assign
id|AM_MUX_MCR4_ENABLE_INTS
suffix:semicolon
multiline_comment|/* Attach the interrupt handler to the audio interrupt. */
id|prom_getproperty
c_func
(paren
id|node
comma
l_string|&quot;intr&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|irq
comma
r_sizeof
(paren
id|irq
)paren
)paren
suffix:semicolon
id|info-&gt;irq
op_assign
id|irq.pri
suffix:semicolon
id|request_irq
c_func
(paren
id|info-&gt;irq
comma
id|amd7930_interrupt
comma
id|SA_INTERRUPT
comma
l_string|&quot;amd7930&quot;
comma
id|drv
)paren
suffix:semicolon
id|enable_irq
c_func
(paren
id|info-&gt;irq
)paren
suffix:semicolon
multiline_comment|/* Initalize the local copy of the MAP registers. */
id|memset
c_func
(paren
op_amp
id|info-&gt;map
comma
l_int|0
comma
r_sizeof
(paren
id|info-&gt;map
)paren
)paren
suffix:semicolon
id|info-&gt;map.mmr1
op_assign
id|AM_MAP_MMR1_GX
op_or
id|AM_MAP_MMR1_GER
op_or
id|AM_MAP_MMR1_GR
op_or
id|AM_MAP_MMR1_STG
suffix:semicolon
multiline_comment|/* Register the amd7930 with the midlevel audio driver. */
id|err
op_assign
id|register_sparcaudio_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;amd7930: unable to register&bslash;n&quot;
)paren
suffix:semicolon
id|disable_irq
c_func
(paren
id|info-&gt;irq
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|info-&gt;irq
comma
id|drv
)paren
suffix:semicolon
id|sparc_free_io
c_func
(paren
id|info-&gt;regs
comma
id|info-&gt;regs_size
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|drv
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* Announce the hardware to the user. */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;amd7930 at 0x%lx irq %d&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|info-&gt;regs
comma
id|info-&gt;irq
)paren
suffix:semicolon
multiline_comment|/* Success! */
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
multiline_comment|/* Detach from an amd7930 chip given the device structure. */
DECL|function|amd7930_detach
r_static
r_void
id|amd7930_detach
c_func
(paren
r_struct
id|sparcaudio_driver
op_star
id|drv
)paren
(brace
r_struct
id|amd7930_info
op_star
id|info
op_assign
(paren
r_struct
id|amd7930_info
op_star
)paren
id|drv
op_member_access_from_pointer
r_private
suffix:semicolon
id|unregister_sparcaudio_driver
c_func
(paren
id|drv
)paren
suffix:semicolon
id|amd7930_disable_ints
c_func
(paren
id|drv
)paren
suffix:semicolon
id|disable_irq
c_func
(paren
id|info-&gt;irq
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|info-&gt;irq
comma
id|drv
)paren
suffix:semicolon
id|sparc_free_io
c_func
(paren
id|info-&gt;regs
comma
id|info-&gt;regs_size
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|drv
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Probe for the amd7930 chip and then attach the driver. */
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
macro_line|#else
id|__initfunc
c_func
(paren
r_int
id|amd7930_init
c_func
(paren
r_void
)paren
)paren
macro_line|#endif
(brace
r_struct
id|linux_sbus
op_star
id|bus
suffix:semicolon
r_struct
id|linux_sbus_device
op_star
id|sdev
suffix:semicolon
r_int
id|node
suffix:semicolon
macro_line|#if 0
macro_line|#ifdef MODULE
id|register_symtab
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/* Try to find the sun4c &quot;audio&quot; node first. */
id|node
op_assign
id|prom_getchild
c_func
(paren
id|prom_root_node
)paren
suffix:semicolon
id|node
op_assign
id|prom_searchsiblings
c_func
(paren
id|node
comma
l_string|&quot;audio&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|node
op_logical_and
id|amd7930_attach
c_func
(paren
op_amp
id|drivers
(braket
l_int|0
)braket
comma
id|node
comma
l_int|NULL
comma
l_int|NULL
)paren
op_eq
l_int|0
)paren
id|num_drivers
op_assign
l_int|1
suffix:semicolon
r_else
id|num_drivers
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Probe each SBUS for amd7930 chips. */
id|for_all_sbusdev
c_func
(paren
id|sdev
comma
id|bus
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|sdev-&gt;prom_name
comma
l_string|&quot;audio&quot;
)paren
)paren
(brace
multiline_comment|/* Don&squot;t go over the max number of drivers. */
r_if
c_cond
(paren
id|num_drivers
op_ge
id|MAX_DRIVERS
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|amd7930_attach
c_func
(paren
op_amp
id|drivers
(braket
id|num_drivers
)braket
comma
id|sdev-&gt;prom_node
comma
id|sdev-&gt;my_bus
comma
id|sdev
)paren
op_eq
l_int|0
)paren
id|num_drivers
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/* Only return success if we found some amd7930 chips. */
r_return
(paren
id|num_drivers
OG
l_int|0
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EIO
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_register
r_int
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
id|num_drivers
suffix:semicolon
id|i
op_increment
)paren
(brace
id|amd7930_detach
c_func
(paren
op_amp
id|drivers
(braket
id|i
)braket
)paren
suffix:semicolon
id|num_drivers
op_decrement
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
