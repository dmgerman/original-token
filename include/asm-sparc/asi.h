multiline_comment|/* $Id: asi.h,v 1.13 1996/03/01 07:20:51 davem Exp $ */
macro_line|#ifndef _SPARC_ASI_H
DECL|macro|_SPARC_ASI_H
mdefine_line|#define _SPARC_ASI_H
multiline_comment|/* asi.h:  Address Space Identifier values for the sparc.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; *&n; * Pioneer work for sun4m: Paul Hatchman (paul@sfe.com.au)&n; * Joint edition for sun4c+sun4m: Pete A. Zaitcev &lt;zaitcev@ipmce.su&gt;&n; */
multiline_comment|/* The first batch are for the sun4c. */
DECL|macro|ASI_NULL1
mdefine_line|#define ASI_NULL1           0x00
DECL|macro|ASI_NULL2
mdefine_line|#define ASI_NULL2           0x01
multiline_comment|/* sun4c and sun4 control registers and mmu/vac ops */
DECL|macro|ASI_CONTROL
mdefine_line|#define ASI_CONTROL         0x02
DECL|macro|ASI_SEGMAP
mdefine_line|#define ASI_SEGMAP          0x03
DECL|macro|ASI_PTE
mdefine_line|#define ASI_PTE             0x04
DECL|macro|ASI_HWFLUSHSEG
mdefine_line|#define ASI_HWFLUSHSEG      0x05
DECL|macro|ASI_HWFLUSHPAGE
mdefine_line|#define ASI_HWFLUSHPAGE     0x06
DECL|macro|ASI_REGMAP
mdefine_line|#define ASI_REGMAP          0x06
DECL|macro|ASI_HWFLUSHCONTEXT
mdefine_line|#define ASI_HWFLUSHCONTEXT  0x07
DECL|macro|ASI_USERTXT
mdefine_line|#define ASI_USERTXT         0x08
DECL|macro|ASI_KERNELTXT
mdefine_line|#define ASI_KERNELTXT       0x09
DECL|macro|ASI_USERDATA
mdefine_line|#define ASI_USERDATA        0x0a
DECL|macro|ASI_KERNELDATA
mdefine_line|#define ASI_KERNELDATA      0x0b
multiline_comment|/* VAC Cache flushing on sun4c and sun4 */
DECL|macro|ASI_FLUSHSEG
mdefine_line|#define ASI_FLUSHSEG        0x0c
DECL|macro|ASI_FLUSHPG
mdefine_line|#define ASI_FLUSHPG         0x0d
DECL|macro|ASI_FLUSHCTX
mdefine_line|#define ASI_FLUSHCTX        0x0e
multiline_comment|/* SPARCstation-5: only 6 bits are decoded. */
multiline_comment|/* wo = Write Only, rw = Read Write;        */
multiline_comment|/* ss = Single Size, as = All Sizes;        */
DECL|macro|ASI_M_RES00
mdefine_line|#define ASI_M_RES00         0x00   /* Don&squot;t touch... */
DECL|macro|ASI_M_UNA01
mdefine_line|#define ASI_M_UNA01         0x01   /* Same here... */
DECL|macro|ASI_M_MXCC
mdefine_line|#define ASI_M_MXCC          0x02   /* Access to TI VIKING MXCC registers */
DECL|macro|ASI_M_FLUSH_PROBE
mdefine_line|#define ASI_M_FLUSH_PROBE   0x03   /* Reference MMU Flush/Probe; rw, ss */
DECL|macro|ASI_M_MMUREGS
mdefine_line|#define ASI_M_MMUREGS       0x04   /* MMU Registers; rw, ss */
DECL|macro|ASI_M_TLBDIAG
mdefine_line|#define ASI_M_TLBDIAG       0x05   /* MMU TLB only Diagnostics */
DECL|macro|ASI_M_DIAGS
mdefine_line|#define ASI_M_DIAGS         0x06   /* Reference MMU Diagnostics */
DECL|macro|ASI_M_IODIAG
mdefine_line|#define ASI_M_IODIAG        0x07   /* MMU I/O TLB only Diagnostics */
DECL|macro|ASI_M_USERTXT
mdefine_line|#define ASI_M_USERTXT       0x08   /* Same as ASI_USERTXT; rw, as */
DECL|macro|ASI_M_KERNELTXT
mdefine_line|#define ASI_M_KERNELTXT     0x09   /* Same as ASI_KERNELTXT; rw, as */
DECL|macro|ASI_M_USERDATA
mdefine_line|#define ASI_M_USERDATA      0x0A   /* Same as ASI_USERDATA; rw, as */
DECL|macro|ASI_M_KERNELDATA
mdefine_line|#define ASI_M_KERNELDATA    0x0B   /* Same as ASI_KERNELDATA; rw, as */
DECL|macro|ASI_M_TXTC_TAG
mdefine_line|#define ASI_M_TXTC_TAG      0x0C   /* Instruction Cache Tag; rw, ss */
DECL|macro|ASI_M_TXTC_DATA
mdefine_line|#define ASI_M_TXTC_DATA     0x0D   /* Instruction Cache Data; rw, ss */
DECL|macro|ASI_M_DATAC_TAG
mdefine_line|#define ASI_M_DATAC_TAG     0x0E   /* Data Cache Tag; rw, ss */
DECL|macro|ASI_M_DATAC_DATA
mdefine_line|#define ASI_M_DATAC_DATA    0x0F   /* Data Cache Data; rw, ss */
multiline_comment|/* The following cache flushing ASIs work only with the &squot;sta&squot;&n; * instruction. Results are unpredictable for &squot;swap&squot; and &squot;ldstuba&squot;,&n; * so don&squot;t do it.&n; */
multiline_comment|/* These ASI flushes affect external caches too. */
DECL|macro|ASI_M_FLUSH_PAGE
mdefine_line|#define ASI_M_FLUSH_PAGE    0x10   /* Flush I&amp;D Cache Line (page); wo, ss */
DECL|macro|ASI_M_FLUSH_SEG
mdefine_line|#define ASI_M_FLUSH_SEG     0x11   /* Flush I&amp;D Cache Line (seg); wo, ss */
DECL|macro|ASI_M_FLUSH_REGION
mdefine_line|#define ASI_M_FLUSH_REGION  0x12   /* Flush I&amp;D Cache Line (region); wo, ss */
DECL|macro|ASI_M_FLUSH_CTX
mdefine_line|#define ASI_M_FLUSH_CTX     0x13   /* Flush I&amp;D Cache Line (context); wo, ss */
DECL|macro|ASI_M_FLUSH_USER
mdefine_line|#define ASI_M_FLUSH_USER    0x14   /* Flush I&amp;D Cache Line (user); wo, ss */
multiline_comment|/* Block-copy operations are available only on certain V8 cpus. */
DECL|macro|ASI_M_BCOPY
mdefine_line|#define ASI_M_BCOPY         0x17   /* Block copy */
multiline_comment|/* These affect only the ICACHE and are Ross HyperSparc specific. */
DECL|macro|ASI_M_IFLUSH_PAGE
mdefine_line|#define ASI_M_IFLUSH_PAGE   0x18   /* Flush I Cache Line (page); wo, ss */
DECL|macro|ASI_M_IFLUSH_SEG
mdefine_line|#define ASI_M_IFLUSH_SEG    0x19   /* Flush I Cache Line (seg); wo, ss */
DECL|macro|ASI_M_IFLUSH_REGION
mdefine_line|#define ASI_M_IFLUSH_REGION 0x1A   /* Flush I Cache Line (region); wo, ss */
DECL|macro|ASI_M_IFLUSH_CTX
mdefine_line|#define ASI_M_IFLUSH_CTX    0x1B   /* Flush I Cache Line (context); wo, ss */
DECL|macro|ASI_M_IFLUSH_USER
mdefine_line|#define ASI_M_IFLUSH_USER   0x1C   /* Flush I Cache Line (user); wo, ss */
multiline_comment|/* Block-fill operations are available on certain V8 cpus */
DECL|macro|ASI_M_BFILL
mdefine_line|#define ASI_M_BFILL         0x1F
multiline_comment|/* This allows direct access to main memory, actually 0x20 to 0x2f are&n; * the available ASI&squot;s for physical ram pass-through, but I don&squot;t have&n; * any idea what the other ones do....&n; */
DECL|macro|ASI_M_BYPASS
mdefine_line|#define ASI_M_BYPASS       0x20   /* Reference MMU bypass; rw, as */
DECL|macro|ASI_M_FBMEM
mdefine_line|#define ASI_M_FBMEM        0x29   /* Graphics card frame buffer access */
DECL|macro|ASI_M_VMEUS
mdefine_line|#define ASI_M_VMEUS        0x2A   /* VME user 16-bit access */
DECL|macro|ASI_M_VMEPS
mdefine_line|#define ASI_M_VMEPS        0x2B   /* VME priv 16-bit access */
DECL|macro|ASI_M_VMEUT
mdefine_line|#define ASI_M_VMEUT        0x2C   /* VME user 32-bit access */
DECL|macro|ASI_M_VMEPT
mdefine_line|#define ASI_M_VMEPT        0x2D   /* VME priv 32-bit access */
DECL|macro|ASI_M_SBUS
mdefine_line|#define ASI_M_SBUS         0x2E   /* Direct SBus access */
DECL|macro|ASI_M_CTL
mdefine_line|#define ASI_M_CTL          0x2F   /* Control Space (ECC and MXCC are here) */
multiline_comment|/* This is ROSS HyperSparc only. */
DECL|macro|ASI_M_FLUSH_IWHOLE
mdefine_line|#define ASI_M_FLUSH_IWHOLE 0x31   /* Flush entire ICACHE; wo, ss */
multiline_comment|/* Tsunami/Viking i/d cache flash clear. */
DECL|macro|ASI_M_IC_FLCLEAR
mdefine_line|#define ASI_M_IC_FLCLEAR   0x36
DECL|macro|ASI_M_DC_FLCLEAR
mdefine_line|#define ASI_M_DC_FLCLEAR   0x37
DECL|macro|ASI_M_DCDR
mdefine_line|#define ASI_M_DCDR         0x39   /* Data Cache Diagnostics Register rw, ss */
multiline_comment|/* Sparc V9 TI UltraSparc ASI&squot;s (V8 ploos ploos) */
multiline_comment|/* ASIs 0x0-0x7f are Supervisor Only.  0x80-0xff are for anyone. */
multiline_comment|/* You will notice that there are a lot of places where if a normal&n; * ASI is available on the V9, there is also a little-endian version.&n; */
DECL|macro|ASI_V9_RESV0
mdefine_line|#define ASI_V9_RESV0       0x00   /* Don&squot;t touch... */
DECL|macro|ASI_V9_RESV1
mdefine_line|#define ASI_V9_RESV1       0x01   /* Not here */
DECL|macro|ASI_V9_RESV2
mdefine_line|#define ASI_V9_RESV2       0x02   /* Or here */
DECL|macro|ASI_V9_RESV3
mdefine_line|#define ASI_V9_RESV3       0x03   /* nor here. */
DECL|macro|ASI_V9_NUCLEUS
mdefine_line|#define ASI_V9_NUCLEUS     0x04   /* Impl-dep extra virtual access context */
DECL|macro|ASI_V9_NUCLEUSL
mdefine_line|#define ASI_V9_NUCLEUSL    0x0C   /* Nucleus context, little-endian */
DECL|macro|ASI_V9_USER_PRIM
mdefine_line|#define ASI_V9_USER_PRIM   0x10   /* User primary address space */
DECL|macro|ASI_V9_USER_SEC
mdefine_line|#define ASI_V9_USER_SEC    0x11   /* User secondary address space */
DECL|macro|ASI_V9_MMUPASS
mdefine_line|#define ASI_V9_MMUPASS     0x14   /* OBMEM (external cache, no data cache) */
DECL|macro|ASI_V9_IOPASS
mdefine_line|#define ASI_V9_IOPASS      0x15   /* Like MMUPASS, for I/O areas (uncached) */
DECL|macro|ASI_V9_USER_PRIML
mdefine_line|#define ASI_V9_USER_PRIML  0x18   /* User primary addr space, lil-endian. */
DECL|macro|ASI_V9_USER_SECL
mdefine_line|#define ASI_V9_USER_SECL   0x19   /* User secondary addr space, lil-endian. */
DECL|macro|ASI_V9_MMUPASSL
mdefine_line|#define ASI_V9_MMUPASSL    0x1C   /* OBMEM little-endian */
DECL|macro|ASI_V9_IOPASSL
mdefine_line|#define ASI_V9_IOPASSL     0x1D   /* Like IOPASS but little-endian */
DECL|macro|ASI_V9_ATOMICQ
mdefine_line|#define ASI_V9_ATOMICQ     0x24   /* Atomic 128-bit load address space */
DECL|macro|ASI_V9_ATOMICQL
mdefine_line|#define ASI_V9_ATOMICQL    0x2C   /* Atomic 128-bit load little-endian */
DECL|macro|ASI_V9_LSTORECTL
mdefine_line|#define ASI_V9_LSTORECTL   0x45   /* ld/st control unit */
DECL|macro|ASI_V9_DCACHE_ENT
mdefine_line|#define ASI_V9_DCACHE_ENT  0x46   /* Data cache entries */
DECL|macro|ASI_V9_DCACHE_TAG
mdefine_line|#define ASI_V9_DCACHE_TAG  0x47   /* Data cache tags */
DECL|macro|ASI_V9_IRQDISPS
mdefine_line|#define ASI_V9_IRQDISPS    0x48   /* IRQ dispatch status registers */
DECL|macro|ASI_V9_IRQRECVS
mdefine_line|#define ASI_V9_IRQRECVS    0x49   /* IRQ receive status registers */
DECL|macro|ASI_V9_MMUREGS
mdefine_line|#define ASI_V9_MMUREGS     0x4A   /* Spitfire MMU control register */
DECL|macro|ASI_V9_ESTATE
mdefine_line|#define ASI_V9_ESTATE      0x4B   /* Error state enable register */
DECL|macro|ASI_V9_ASYNC_FSR
mdefine_line|#define ASI_V9_ASYNC_FSR   0x4C   /* Asynchronous Fault Status reg */
DECL|macro|ASI_V9_ASYNC_FAR
mdefine_line|#define ASI_V9_ASYNC_FAR   0x4D   /* Asynchronous Fault Address reg */
DECL|macro|ASI_V9_ECACHE_DIAG
mdefine_line|#define ASI_V9_ECACHE_DIAG 0x4E   /* External Cache diagnostics */
DECL|macro|ASI_V9_TXTMMU
mdefine_line|#define ASI_V9_TXTMMU      0x50   /* MMU for program text */
DECL|macro|ASI_V9_TXTMMU_D1
mdefine_line|#define ASI_V9_TXTMMU_D1   0x51   /* XXX */
DECL|macro|ASI_V9_TXTMMU_D2
mdefine_line|#define ASI_V9_TXTMMU_D2   0x52   /* XXX */
DECL|macro|ASI_V9_TXTMMU_TDI
mdefine_line|#define ASI_V9_TXTMMU_TDI  0x54   /* Text MMU TLB data in */
DECL|macro|ASI_V9_TXTMMU_TDA
mdefine_line|#define ASI_V9_TXTMMU_TDA  0x55   /* Text MMU TLB data access */
DECL|macro|ASI_V9_TXTMMU_TTR
mdefine_line|#define ASI_V9_TXTMMU_TTR  0x56   /* Text MMU TLB tag read */
DECL|macro|ASI_V9_TXTMMU_TDM
mdefine_line|#define ASI_V9_TXTMMU_TDM  0x57   /* Text MMU TLB de-map */
DECL|macro|ASI_V9_DATAMMU
mdefine_line|#define ASI_V9_DATAMMU     0x58   /* MMU for program data */
DECL|macro|ASI_V9_DATAMMU_D1
mdefine_line|#define ASI_V9_DATAMMU_D1  0x59   /* XXX */
DECL|macro|ASI_V9_DATAMMU_D2
mdefine_line|#define ASI_V9_DATAMMU_D2  0x5A   /* XXX */
DECL|macro|ASI_V9_DATAMMU_DD
mdefine_line|#define ASI_V9_DATAMMU_DD  0x5B   /* XXX */
DECL|macro|ASI_V9_DATAMMU_TDI
mdefine_line|#define ASI_V9_DATAMMU_TDI 0x5C   /* Data MMU TLB data in */
DECL|macro|ASI_V9_DATAMMU_TDA
mdefine_line|#define ASI_V9_DATAMMU_TDA 0x5D   /* Data MMU TLB data access */
DECL|macro|ASI_V9_DATAMMU_TTR
mdefine_line|#define ASI_V9_DATAMMU_TTR 0x5E   /* Data MMU TLB tag read */
DECL|macro|ASI_V9_DATAMMU_TDM
mdefine_line|#define ASI_V9_DATAMMU_TDM 0x5F   /* Data MMU TLB de-map */
DECL|macro|ASI_V9_ICACHE_D
mdefine_line|#define ASI_V9_ICACHE_D    0x66   /* Instruction cache data */
DECL|macro|ASI_V9_ICACHE_T
mdefine_line|#define ASI_V9_ICACHE_T    0x67   /* Instruction cache tags */
DECL|macro|ASI_V9_ICACHE_DEC
mdefine_line|#define ASI_V9_ICACHE_DEC  0x6E   /* Instruction cache decode */
DECL|macro|ASI_V9_ICACHE_NXT
mdefine_line|#define ASI_V9_ICACHE_NXT  0x6F   /* Instruction cache next ent */
DECL|macro|ASI_V9_HUH1
mdefine_line|#define ASI_V9_HUH1        0x70   /* XXX */
DECL|macro|ASI_V9_HUH2
mdefine_line|#define ASI_V9_HUH2        0x71   /* XXX */
DECL|macro|ASI_V9_ECACHE_ACC
mdefine_line|#define ASI_V9_ECACHE_ACC  0x76   /* External cache registers */
DECL|macro|ASI_V9_INTR_DISP
mdefine_line|#define ASI_V9_INTR_DISP   0x77   /* Interrupt dispatch registers */
DECL|macro|ASI_V9_HUH1L
mdefine_line|#define ASI_V9_HUH1L       0x78   /* XXX */
DECL|macro|ASI_V9_HUH2L
mdefine_line|#define ASI_V9_HUH2L       0x79   /* XXX */
DECL|macro|ASI_V9_INTR_RECV
mdefine_line|#define ASI_V9_INTR_RECV   0x7f   /* Interrupt Receive registers */
DECL|macro|ASI_V9_PRIMARY
mdefine_line|#define ASI_V9_PRIMARY      0x80   /* Primary address space */
DECL|macro|ASI_V9_SECONDARY
mdefine_line|#define ASI_V9_SECONDARY    0x81   /* Secondary address space */
DECL|macro|ASI_V9_PRIMARY_NF
mdefine_line|#define ASI_V9_PRIMARY_NF   0x82   /* Primary address space -- No Fault */
DECL|macro|ASI_V9_SECONDARY_NF
mdefine_line|#define ASI_V9_SECONDARY_NF 0x83   /* Secondary address space -- No Fault */
DECL|macro|ASI_V9_PRIMARYL
mdefine_line|#define ASI_V9_PRIMARYL      0x80   /* Primary address space, little-endian */
DECL|macro|ASI_V9_SECONDARYL
mdefine_line|#define ASI_V9_SECONDARYL    0x81   /* Secondary address space, little-endian  */
DECL|macro|ASI_V9_PRIMARY_NFL
mdefine_line|#define ASI_V9_PRIMARY_NFL   0x82   /* Primary address space, No Fault, l-endian  */
DECL|macro|ASI_V9_SECONDARY_NFL
mdefine_line|#define ASI_V9_SECONDARY_NFL 0x83   /* Secondary address space, No Fault, l-endian  */
DECL|macro|ASI_V9_XXX1
mdefine_line|#define ASI_V9_XXX1        0xC0   /* XXX */
DECL|macro|ASI_V9_XXX2
mdefine_line|#define ASI_V9_XXX2        0xC1   /* XXX */
DECL|macro|ASI_V9_XXX3
mdefine_line|#define ASI_V9_XXX3        0xC2   /* XXX */
DECL|macro|ASI_V9_XXX4
mdefine_line|#define ASI_V9_XXX4        0xC3   /* XXX */
DECL|macro|ASI_V9_XXX5
mdefine_line|#define ASI_V9_XXX5        0xC4   /* XXX */
DECL|macro|ASI_V9_XXX6
mdefine_line|#define ASI_V9_XXX6        0xC5   /* XXX */
DECL|macro|ASI_V9_XXX7
mdefine_line|#define ASI_V9_XXX7        0xC8   /* XXX */
DECL|macro|ASI_V9_XXX8
mdefine_line|#define ASI_V9_XXX8        0xC9   /* XXX */
DECL|macro|ASI_V9_XXX9
mdefine_line|#define ASI_V9_XXX9        0xCA   /* XXX */
DECL|macro|ASI_V9_XXX10
mdefine_line|#define ASI_V9_XXX10       0xCB   /* XXX */
DECL|macro|ASI_V9_XXX11
mdefine_line|#define ASI_V9_XXX11       0xCC   /* XXX */
DECL|macro|ASI_V9_XXX12
mdefine_line|#define ASI_V9_XXX12       0xCD   /* XXX */
DECL|macro|ASI_V9_XXX13
mdefine_line|#define ASI_V9_XXX13       0xD0   /* XXX */
DECL|macro|ASI_V9_XXX14
mdefine_line|#define ASI_V9_XXX14       0xD1   /* XXX */
DECL|macro|ASI_V9_XXX15
mdefine_line|#define ASI_V9_XXX15       0xD2   /* XXX */
DECL|macro|ASI_V9_XXX16
mdefine_line|#define ASI_V9_XXX16       0xD3   /* XXX */
DECL|macro|ASI_V9_XXX17
mdefine_line|#define ASI_V9_XXX17       0xD8   /* XXX */
DECL|macro|ASI_V9_XXX18
mdefine_line|#define ASI_V9_XXX18       0xD9   /* XXX */
DECL|macro|ASI_V9_XXX19
mdefine_line|#define ASI_V9_XXX19       0xDA   /* XXX */
DECL|macro|ASI_V9_XXX20
mdefine_line|#define ASI_V9_XXX20       0xDB   /* XXX */
DECL|macro|ASI_V9_XXX21
mdefine_line|#define ASI_V9_XXX21       0xE0   /* XXX */
DECL|macro|ASI_V9_XXX22
mdefine_line|#define ASI_V9_XXX22       0xE1   /* XXX */
DECL|macro|ASI_V9_XXX23
mdefine_line|#define ASI_V9_XXX23       0xF0   /* XXX */
DECL|macro|ASI_V9_XXX24
mdefine_line|#define ASI_V9_XXX24       0xF1   /* XXX */
DECL|macro|ASI_V9_XXX25
mdefine_line|#define ASI_V9_XXX25       0xF8   /* XXX */
DECL|macro|ASI_V9_XXX26
mdefine_line|#define ASI_V9_XXX26       0xF9   /* XXX */
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Better to do these inline with gcc __asm__ statements. */
multiline_comment|/* The following allow you to access physical memory directly without&n; * translation by the SRMMU.  The only other way to do this is to&n; * turn off the SRMMU completely, and well... thats not good.&n; *&n; * TODO: For non-MBus SRMMU units we have to perform the following&n; *       using this sequence.&n; * 1) Turn off traps&n; * 2) Turn on AC bit in SRMMU control register&n; * 3) Do our direct physical memory access&n; * 4) Restore old SRMMU control register value&n; * 5) Restore old %psr value &n; */
r_extern
id|__inline__
r_int
r_int
DECL|function|ldb_sun4m_bypass
id|ldb_sun4m_bypass
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|retval
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;lduba [%2] %1, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|ASI_M_BYPASS
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_extern
id|__inline__
r_int
r_int
DECL|function|ldw_sun4m_bypass
id|ldw_sun4m_bypass
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|retval
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;lda [%2] %1, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|ASI_M_BYPASS
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_extern
id|__inline__
r_void
DECL|function|stb_sun4m_bypass
id|stb_sun4m_bypass
c_func
(paren
r_int
r_char
id|value
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;stba %0, [%2] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_BYPASS
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
r_extern
id|__inline__
r_void
DECL|function|stw_sun4m_bypass
id|stw_sun4m_bypass
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|addr
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;sta %0, [%2] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_BYPASS
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* _SPARC_ASI_H */
eof
