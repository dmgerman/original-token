macro_line|#ifndef __ALPHA_APECS__H__
DECL|macro|__ALPHA_APECS__H__
mdefine_line|#define __ALPHA_APECS__H__
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * APECS is the internal name for the 2107x chipset which provides&n; * memory controller and PCI access for the 21064 chip based systems.&n; *&n; * This file is based on:&n; *&n; * DECchip 21071-AA and DECchip 21072-AA Core Logic Chipsets&n; * Data Sheet&n; *&n; * EC-N0648-72&n; *&n; *&n; * david.rusling@reo.mts.dec.com Initial Version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_ALPHA_XL
multiline_comment|/*&n;   An AVANTI *might* be an XL, and an XL has only 27 bits of ISA address&n;   that get passed through the PCI&lt;-&gt;ISA bridge chip. So we&squot;ve gotta use&n;   both windows to max out the physical memory we can DMA to. Sigh...&n;&n;   If we try a window at 0 for 1GB as a work-around, we run into conflicts&n;   with ISA/PCI bus memory which can&squot;t be relocated, like VGA aperture and&n;   BIOS ROMs. So we must put the windows high enough to avoid these areas.&n;&n;   We put window 1 at BUS 64Mb for 64Mb, mapping physical 0 to 64Mb-1,&n;   and window 2 at BUS 1Gb for 1Gb, mapping physical 0 to 1Gb-1.&n;   Yes, this does map 0 to 64Mb-1 twice, but only window 1 will actually&n;   be used for that range (via virt_to_bus()).&n;&n;   Note that we actually fudge the window 1 maximum as 48Mb instead of 64Mb,&n;   to keep virt_to_bus() from returning an address in the first window, for&n;   a data area that goes beyond the 64Mb first DMA window.  Sigh...&n;   The fudge factor MUST match with &lt;asm/dma.h&gt; MAX_DMA_ADDRESS, but&n;   we can&squot;t just use that here, because of header file looping... :-(&n;&n;   Window 1 will be used for all DMA from the ISA bus; yes, that does&n;   limit what memory an ISA floppy or sound card or Ethernet can touch, but&n;   it&squot;s also a known limitation on other platforms as well. We use the&n;   same technique that is used on INTEL platforms with similar limitation:&n;   set MAX_DMA_ADDRESS and clear some pages&squot; DMAable flags during mem_init().&n;   We trust that any ISA bus device drivers will *always* ask for DMAable&n;   memory explicitly via kmalloc()/get_free_pages() flags arguments.&n;&n;   Note that most PCI bus devices&squot; drivers do *not* explicitly ask for&n;   DMAable memory; they count on being able to DMA to any memory they&n;   get from kmalloc()/get_free_pages(). They will also use window 1 for&n;   any physical memory accesses below 64Mb; the rest will be handled by&n;   window 2, maxing out at 1Gb of memory. I trust this is enough... :-)&n;&n;   We hope that the area before the first window is large enough so that&n;   there will be no overlap at the top end (64Mb). We *must* locate the&n;   PCI cards&squot; memory just below window 1, so that there&squot;s still the&n;   possibility of being able to access it via SPARSE space. This is&n;   important for cards such as the Matrox Millennium, whose Xserver&n;   wants to access memory-mapped registers in byte and short lengths.&n;&n;   Note that the XL is treated differently from the AVANTI, even though&n;   for most other things they are identical. It didn&squot;t seem reasonable to&n;   make the AVANTI support pay for the limitations of the XL. It is true,&n;   however, that an XL kernel will run on an AVANTI without problems.&n;&n;*/
DECL|macro|APECS_XL_DMA_WIN1_BASE
mdefine_line|#define APECS_XL_DMA_WIN1_BASE&t;&t;(64*1024*1024)
DECL|macro|APECS_XL_DMA_WIN1_SIZE
mdefine_line|#define APECS_XL_DMA_WIN1_SIZE&t;&t;(64*1024*1024)
DECL|macro|APECS_XL_DMA_WIN1_SIZE_PARANOID
mdefine_line|#define APECS_XL_DMA_WIN1_SIZE_PARANOID&t;(48*1024*1024)
DECL|macro|APECS_XL_DMA_WIN2_BASE
mdefine_line|#define APECS_XL_DMA_WIN2_BASE&t;&t;(1024*1024*1024)
DECL|macro|APECS_XL_DMA_WIN2_SIZE
mdefine_line|#define APECS_XL_DMA_WIN2_SIZE&t;&t;(1024*1024*1024)
macro_line|#else /* CONFIG_ALPHA_XL */
multiline_comment|/* these are for normal APECS family machines, AVANTI/MUSTANG/EB64/PC64 */
macro_line|#ifdef CONFIG_ALPHA_SRM_SETUP
multiline_comment|/* if we are using the SRM PCI setup, we&squot;ll need to use variables instead */
DECL|macro|APECS_DMA_WIN_BASE_DEFAULT
mdefine_line|#define APECS_DMA_WIN_BASE_DEFAULT&t;(1024*1024*1024)
DECL|macro|APECS_DMA_WIN_SIZE_DEFAULT
mdefine_line|#define APECS_DMA_WIN_SIZE_DEFAULT&t;(1024*1024*1024)
r_extern
r_int
r_int
id|APECS_DMA_WIN_BASE
suffix:semicolon
r_extern
r_int
r_int
id|APECS_DMA_WIN_SIZE
suffix:semicolon
macro_line|#else /* SRM_SETUP */
DECL|macro|APECS_DMA_WIN_BASE
mdefine_line|#define APECS_DMA_WIN_BASE&t;(1024*1024*1024)
DECL|macro|APECS_DMA_WIN_SIZE
mdefine_line|#define APECS_DMA_WIN_SIZE&t;(1024*1024*1024)
macro_line|#endif /* SRM_SETUP */
macro_line|#endif /* CONFIG_ALPHA_XL */
multiline_comment|/*&n; * 21071-DA Control and Status registers.&n; * These are used for PCI memory access.&n; */
DECL|macro|APECS_IOC_DCSR
mdefine_line|#define APECS_IOC_DCSR                  (IDENT_ADDR + 0x1A0000000UL)
DECL|macro|APECS_IOC_PEAR
mdefine_line|#define APECS_IOC_PEAR                  (IDENT_ADDR + 0x1A0000020UL)
DECL|macro|APECS_IOC_SEAR
mdefine_line|#define APECS_IOC_SEAR                  (IDENT_ADDR + 0x1A0000040UL)
DECL|macro|APECS_IOC_DR1
mdefine_line|#define APECS_IOC_DR1                   (IDENT_ADDR + 0x1A0000060UL)
DECL|macro|APECS_IOC_DR2
mdefine_line|#define APECS_IOC_DR2                   (IDENT_ADDR + 0x1A0000080UL)
DECL|macro|APECS_IOC_DR3
mdefine_line|#define APECS_IOC_DR3                   (IDENT_ADDR + 0x1A00000A0UL)
DECL|macro|APECS_IOC_TB1R
mdefine_line|#define APECS_IOC_TB1R                  (IDENT_ADDR + 0x1A00000C0UL)
DECL|macro|APECS_IOC_TB2R
mdefine_line|#define APECS_IOC_TB2R                  (IDENT_ADDR + 0x1A00000E0UL)
DECL|macro|APECS_IOC_PB1R
mdefine_line|#define APECS_IOC_PB1R                  (IDENT_ADDR + 0x1A0000100UL)
DECL|macro|APECS_IOC_PB2R
mdefine_line|#define APECS_IOC_PB2R                  (IDENT_ADDR + 0x1A0000120UL)
DECL|macro|APECS_IOC_PM1R
mdefine_line|#define APECS_IOC_PM1R                  (IDENT_ADDR + 0x1A0000140UL)
DECL|macro|APECS_IOC_PM2R
mdefine_line|#define APECS_IOC_PM2R                  (IDENT_ADDR + 0x1A0000160UL)
DECL|macro|APECS_IOC_HAXR0
mdefine_line|#define APECS_IOC_HAXR0                 (IDENT_ADDR + 0x1A0000180UL)
DECL|macro|APECS_IOC_HAXR1
mdefine_line|#define APECS_IOC_HAXR1                 (IDENT_ADDR + 0x1A00001A0UL)
DECL|macro|APECS_IOC_HAXR2
mdefine_line|#define APECS_IOC_HAXR2                 (IDENT_ADDR + 0x1A00001C0UL)
DECL|macro|APECS_IOC_PMLT
mdefine_line|#define APECS_IOC_PMLT                  (IDENT_ADDR + 0x1A00001E0UL)
DECL|macro|APECS_IOC_TLBTAG0
mdefine_line|#define APECS_IOC_TLBTAG0               (IDENT_ADDR + 0x1A0000200UL)
DECL|macro|APECS_IOC_TLBTAG1
mdefine_line|#define APECS_IOC_TLBTAG1               (IDENT_ADDR + 0x1A0000220UL)
DECL|macro|APECS_IOC_TLBTAG2
mdefine_line|#define APECS_IOC_TLBTAG2               (IDENT_ADDR + 0x1A0000240UL)
DECL|macro|APECS_IOC_TLBTAG3
mdefine_line|#define APECS_IOC_TLBTAG3               (IDENT_ADDR + 0x1A0000260UL)
DECL|macro|APECS_IOC_TLBTAG4
mdefine_line|#define APECS_IOC_TLBTAG4               (IDENT_ADDR + 0x1A0000280UL)
DECL|macro|APECS_IOC_TLBTAG5
mdefine_line|#define APECS_IOC_TLBTAG5               (IDENT_ADDR + 0x1A00002A0UL)
DECL|macro|APECS_IOC_TLBTAG6
mdefine_line|#define APECS_IOC_TLBTAG6               (IDENT_ADDR + 0x1A00002C0UL)
DECL|macro|APECS_IOC_TLBTAG7
mdefine_line|#define APECS_IOC_TLBTAG7               (IDENT_ADDR + 0x1A00002E0UL)
DECL|macro|APECS_IOC_TLBDATA0
mdefine_line|#define APECS_IOC_TLBDATA0              (IDENT_ADDR + 0x1A0000300UL)
DECL|macro|APECS_IOC_TLBDATA1
mdefine_line|#define APECS_IOC_TLBDATA1              (IDENT_ADDR + 0x1A0000320UL)
DECL|macro|APECS_IOC_TLBDATA2
mdefine_line|#define APECS_IOC_TLBDATA2              (IDENT_ADDR + 0x1A0000340UL)
DECL|macro|APECS_IOC_TLBDATA3
mdefine_line|#define APECS_IOC_TLBDATA3              (IDENT_ADDR + 0x1A0000360UL)
DECL|macro|APECS_IOC_TLBDATA4
mdefine_line|#define APECS_IOC_TLBDATA4              (IDENT_ADDR + 0x1A0000380UL)
DECL|macro|APECS_IOC_TLBDATA5
mdefine_line|#define APECS_IOC_TLBDATA5              (IDENT_ADDR + 0x1A00003A0UL)
DECL|macro|APECS_IOC_TLBDATA6
mdefine_line|#define APECS_IOC_TLBDATA6              (IDENT_ADDR + 0x1A00003C0UL)
DECL|macro|APECS_IOC_TLBDATA7
mdefine_line|#define APECS_IOC_TLBDATA7              (IDENT_ADDR + 0x1A00003E0UL)
DECL|macro|APECS_IOC_TBIA
mdefine_line|#define APECS_IOC_TBIA                  (IDENT_ADDR + 0x1A0000400UL)
multiline_comment|/*&n; * 21071-CA Control and Status registers.&n; * These are used to program memory timing,&n; *  configure memory and initialise the B-Cache.&n; */
DECL|macro|APECS_MEM_GCR
mdefine_line|#define APECS_MEM_GCR&t;&t;        (IDENT_ADDR + 0x180000000UL)
DECL|macro|APECS_MEM_EDSR
mdefine_line|#define APECS_MEM_EDSR&t;&t;        (IDENT_ADDR + 0x180000040UL)
DECL|macro|APECS_MEM_TAR
mdefine_line|#define APECS_MEM_TAR  &t;&t;        (IDENT_ADDR + 0x180000060UL)
DECL|macro|APECS_MEM_ELAR
mdefine_line|#define APECS_MEM_ELAR&t;&t;        (IDENT_ADDR + 0x180000080UL)
DECL|macro|APECS_MEM_EHAR
mdefine_line|#define APECS_MEM_EHAR  &t;&t;(IDENT_ADDR + 0x1800000a0UL)
DECL|macro|APECS_MEM_SFT_RST
mdefine_line|#define APECS_MEM_SFT_RST&t;&t;(IDENT_ADDR + 0x1800000c0UL)
DECL|macro|APECS_MEM_LDxLAR
mdefine_line|#define APECS_MEM_LDxLAR &t;&t;(IDENT_ADDR + 0x1800000e0UL)
DECL|macro|APECS_MEM_LDxHAR
mdefine_line|#define APECS_MEM_LDxHAR &t;&t;(IDENT_ADDR + 0x180000100UL)
DECL|macro|APECS_MEM_GTR
mdefine_line|#define APECS_MEM_GTR    &t;&t;(IDENT_ADDR + 0x180000200UL)
DECL|macro|APECS_MEM_RTR
mdefine_line|#define APECS_MEM_RTR    &t;&t;(IDENT_ADDR + 0x180000220UL)
DECL|macro|APECS_MEM_VFPR
mdefine_line|#define APECS_MEM_VFPR   &t;&t;(IDENT_ADDR + 0x180000240UL)
DECL|macro|APECS_MEM_PDLDR
mdefine_line|#define APECS_MEM_PDLDR  &t;&t;(IDENT_ADDR + 0x180000260UL)
DECL|macro|APECS_MEM_PDhDR
mdefine_line|#define APECS_MEM_PDhDR  &t;&t;(IDENT_ADDR + 0x180000280UL)
multiline_comment|/* Bank x Base Address Register */
DECL|macro|APECS_MEM_B0BAR
mdefine_line|#define APECS_MEM_B0BAR  &t;&t;(IDENT_ADDR + 0x180000800UL)
DECL|macro|APECS_MEM_B1BAR
mdefine_line|#define APECS_MEM_B1BAR  &t;&t;(IDENT_ADDR + 0x180000820UL)
DECL|macro|APECS_MEM_B2BAR
mdefine_line|#define APECS_MEM_B2BAR  &t;&t;(IDENT_ADDR + 0x180000840UL)
DECL|macro|APECS_MEM_B3BAR
mdefine_line|#define APECS_MEM_B3BAR  &t;&t;(IDENT_ADDR + 0x180000860UL)
DECL|macro|APECS_MEM_B4BAR
mdefine_line|#define APECS_MEM_B4BAR  &t;&t;(IDENT_ADDR + 0x180000880UL)
DECL|macro|APECS_MEM_B5BAR
mdefine_line|#define APECS_MEM_B5BAR  &t;&t;(IDENT_ADDR + 0x1800008A0UL)
DECL|macro|APECS_MEM_B6BAR
mdefine_line|#define APECS_MEM_B6BAR  &t;&t;(IDENT_ADDR + 0x1800008C0UL)
DECL|macro|APECS_MEM_B7BAR
mdefine_line|#define APECS_MEM_B7BAR  &t;&t;(IDENT_ADDR + 0x1800008E0UL)
DECL|macro|APECS_MEM_B8BAR
mdefine_line|#define APECS_MEM_B8BAR  &t;&t;(IDENT_ADDR + 0x180000900UL)
multiline_comment|/* Bank x Configuration Register */
DECL|macro|APECS_MEM_B0BCR
mdefine_line|#define APECS_MEM_B0BCR  &t;&t;(IDENT_ADDR + 0x180000A00UL)
DECL|macro|APECS_MEM_B1BCR
mdefine_line|#define APECS_MEM_B1BCR  &t;&t;(IDENT_ADDR + 0x180000A20UL)
DECL|macro|APECS_MEM_B2BCR
mdefine_line|#define APECS_MEM_B2BCR  &t;&t;(IDENT_ADDR + 0x180000A40UL)
DECL|macro|APECS_MEM_B3BCR
mdefine_line|#define APECS_MEM_B3BCR  &t;&t;(IDENT_ADDR + 0x180000A60UL)
DECL|macro|APECS_MEM_B4BCR
mdefine_line|#define APECS_MEM_B4BCR  &t;&t;(IDENT_ADDR + 0x180000A80UL)
DECL|macro|APECS_MEM_B5BCR
mdefine_line|#define APECS_MEM_B5BCR  &t;&t;(IDENT_ADDR + 0x180000AA0UL)
DECL|macro|APECS_MEM_B6BCR
mdefine_line|#define APECS_MEM_B6BCR  &t;&t;(IDENT_ADDR + 0x180000AC0UL)
DECL|macro|APECS_MEM_B7BCR
mdefine_line|#define APECS_MEM_B7BCR  &t;&t;(IDENT_ADDR + 0x180000AE0UL)
DECL|macro|APECS_MEM_B8BCR
mdefine_line|#define APECS_MEM_B8BCR  &t;&t;(IDENT_ADDR + 0x180000B00UL)
multiline_comment|/* Bank x Timing Register A */
DECL|macro|APECS_MEM_B0TRA
mdefine_line|#define APECS_MEM_B0TRA  &t;&t;(IDENT_ADDR + 0x180000C00UL)
DECL|macro|APECS_MEM_B1TRA
mdefine_line|#define APECS_MEM_B1TRA  &t;&t;(IDENT_ADDR + 0x180000C20UL)
DECL|macro|APECS_MEM_B2TRA
mdefine_line|#define APECS_MEM_B2TRA  &t;&t;(IDENT_ADDR + 0x180000C40UL)
DECL|macro|APECS_MEM_B3TRA
mdefine_line|#define APECS_MEM_B3TRA  &t;&t;(IDENT_ADDR + 0x180000C60UL)
DECL|macro|APECS_MEM_B4TRA
mdefine_line|#define APECS_MEM_B4TRA  &t;&t;(IDENT_ADDR + 0x180000C80UL)
DECL|macro|APECS_MEM_B5TRA
mdefine_line|#define APECS_MEM_B5TRA  &t;&t;(IDENT_ADDR + 0x180000CA0UL)
DECL|macro|APECS_MEM_B6TRA
mdefine_line|#define APECS_MEM_B6TRA  &t;&t;(IDENT_ADDR + 0x180000CC0UL)
DECL|macro|APECS_MEM_B7TRA
mdefine_line|#define APECS_MEM_B7TRA  &t;&t;(IDENT_ADDR + 0x180000CE0UL)
DECL|macro|APECS_MEM_B8TRA
mdefine_line|#define APECS_MEM_B8TRA  &t;&t;(IDENT_ADDR + 0x180000D00UL)
multiline_comment|/* Bank x Timing Register B */
DECL|macro|APECS_MEM_B0TRB
mdefine_line|#define APECS_MEM_B0TRB                 (IDENT_ADDR + 0x180000E00UL)
DECL|macro|APECS_MEM_B1TRB
mdefine_line|#define APECS_MEM_B1TRB  &t;&t;(IDENT_ADDR + 0x180000E20UL)
DECL|macro|APECS_MEM_B2TRB
mdefine_line|#define APECS_MEM_B2TRB  &t;&t;(IDENT_ADDR + 0x180000E40UL)
DECL|macro|APECS_MEM_B3TRB
mdefine_line|#define APECS_MEM_B3TRB  &t;&t;(IDENT_ADDR + 0x180000E60UL)
DECL|macro|APECS_MEM_B4TRB
mdefine_line|#define APECS_MEM_B4TRB  &t;&t;(IDENT_ADDR + 0x180000E80UL)
DECL|macro|APECS_MEM_B5TRB
mdefine_line|#define APECS_MEM_B5TRB  &t;&t;(IDENT_ADDR + 0x180000EA0UL)
DECL|macro|APECS_MEM_B6TRB
mdefine_line|#define APECS_MEM_B6TRB  &t;&t;(IDENT_ADDR + 0x180000EC0UL)
DECL|macro|APECS_MEM_B7TRB
mdefine_line|#define APECS_MEM_B7TRB  &t;&t;(IDENT_ADDR + 0x180000EE0UL)
DECL|macro|APECS_MEM_B8TRB
mdefine_line|#define APECS_MEM_B8TRB  &t;&t;(IDENT_ADDR + 0x180000F00UL)
multiline_comment|/*&n; * Memory spaces:&n; */
DECL|macro|APECS_IACK_SC
mdefine_line|#define APECS_IACK_SC&t;&t;        (IDENT_ADDR + 0x1b0000000UL)
DECL|macro|APECS_CONF
mdefine_line|#define APECS_CONF&t;&t;        (IDENT_ADDR + 0x1e0000000UL)
DECL|macro|APECS_IO
mdefine_line|#define APECS_IO&t;&t;&t;(IDENT_ADDR + 0x1c0000000UL)
DECL|macro|APECS_SPARSE_MEM
mdefine_line|#define APECS_SPARSE_MEM&t;&t;(IDENT_ADDR + 0x200000000UL)
DECL|macro|APECS_DENSE_MEM
mdefine_line|#define APECS_DENSE_MEM&t;&t;        (IDENT_ADDR + 0x300000000UL)
multiline_comment|/*&n; * Bit definitions for I/O Controller status register 0:&n; */
DECL|macro|APECS_IOC_STAT0_CMD
mdefine_line|#define APECS_IOC_STAT0_CMD&t;&t;0xf
DECL|macro|APECS_IOC_STAT0_ERR
mdefine_line|#define APECS_IOC_STAT0_ERR&t;&t;(1&lt;&lt;4)
DECL|macro|APECS_IOC_STAT0_LOST
mdefine_line|#define APECS_IOC_STAT0_LOST&t;&t;(1&lt;&lt;5)
DECL|macro|APECS_IOC_STAT0_THIT
mdefine_line|#define APECS_IOC_STAT0_THIT&t;&t;(1&lt;&lt;6)
DECL|macro|APECS_IOC_STAT0_TREF
mdefine_line|#define APECS_IOC_STAT0_TREF&t;&t;(1&lt;&lt;7)
DECL|macro|APECS_IOC_STAT0_CODE_SHIFT
mdefine_line|#define APECS_IOC_STAT0_CODE_SHIFT&t;8
DECL|macro|APECS_IOC_STAT0_CODE_MASK
mdefine_line|#define APECS_IOC_STAT0_CODE_MASK&t;0x7
DECL|macro|APECS_IOC_STAT0_P_NBR_SHIFT
mdefine_line|#define APECS_IOC_STAT0_P_NBR_SHIFT&t;13
DECL|macro|APECS_IOC_STAT0_P_NBR_MASK
mdefine_line|#define APECS_IOC_STAT0_P_NBR_MASK&t;0x7ffff
DECL|macro|HAE_ADDRESS
mdefine_line|#define HAE_ADDRESS&t;APECS_IOC_HAXR1
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Translate physical memory address as seen on (PCI) bus into&n; * a kernel virtual address and vv.&n; */
multiline_comment|/* NOTE: we fudge the window 1 maximum as 48Mb instead of 64Mb, to prevent &n;   virt_to_bus() from returning an address in the first window, for a&n;   data area that goes beyond the 64Mb first DMA window. Sigh...&n;   This MUST match with &lt;asm/dma.h&gt; MAX_DMA_ADDRESS for consistency, but&n;   we can&squot;t just use that here, because of header file looping... :-(&n;*/
DECL|function|virt_to_bus
r_extern
r_inline
r_int
r_int
id|virt_to_bus
c_func
(paren
r_void
op_star
id|address
)paren
(brace
r_int
r_int
id|paddr
op_assign
id|virt_to_phys
c_func
(paren
id|address
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ALPHA_XL
r_if
c_cond
(paren
id|paddr
OL
id|APECS_XL_DMA_WIN1_SIZE_PARANOID
)paren
r_return
id|paddr
op_plus
id|APECS_XL_DMA_WIN1_BASE
suffix:semicolon
r_else
r_return
id|paddr
op_plus
id|APECS_XL_DMA_WIN2_BASE
suffix:semicolon
multiline_comment|/* win 2 xlates to 0 also */
macro_line|#else /* CONFIG_ALPHA_XL */
r_return
id|paddr
op_plus
id|APECS_DMA_WIN_BASE
suffix:semicolon
macro_line|#endif /* CONFIG_ALPHA_XL */
)brace
DECL|function|bus_to_virt
r_extern
r_inline
r_void
op_star
id|bus_to_virt
c_func
(paren
r_int
r_int
id|address
)paren
(brace
multiline_comment|/*&n;&t; * This check is a sanity check but also ensures that bus&n;&t; * address 0 maps to virtual address 0 which is useful to&n;&t; * detect null &quot;pointers&quot; (the NCR driver is much simpler if&n;&t; * NULL pointers are preserved).&n;&t; */
macro_line|#ifdef CONFIG_ALPHA_XL
r_if
c_cond
(paren
id|address
OL
id|APECS_XL_DMA_WIN1_BASE
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|address
OL
(paren
id|APECS_XL_DMA_WIN1_BASE
op_plus
id|APECS_XL_DMA_WIN1_SIZE
)paren
)paren
r_return
id|phys_to_virt
c_func
(paren
id|address
op_minus
id|APECS_XL_DMA_WIN1_BASE
)paren
suffix:semicolon
r_else
multiline_comment|/* should be more checking here, maybe? */
r_return
id|phys_to_virt
c_func
(paren
id|address
op_minus
id|APECS_XL_DMA_WIN2_BASE
)paren
suffix:semicolon
macro_line|#else /* CONFIG_ALPHA_XL */
r_if
c_cond
(paren
id|address
OL
id|APECS_DMA_WIN_BASE
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|phys_to_virt
c_func
(paren
id|address
op_minus
id|APECS_DMA_WIN_BASE
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ALPHA_XL */
)brace
multiline_comment|/*&n; * I/O functions:&n; *&n; * Unlike Jensen, the APECS machines have no concept of local&n; * I/O---everything goes over the PCI bus.&n; *&n; * There is plenty room for optimization here.  In particular,&n; * the Alpha&squot;s insb/insw/extb/extw should be useful in moving&n; * data to/from the right byte-lanes.&n; */
DECL|macro|vuip
mdefine_line|#define vuip&t;volatile unsigned int *
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
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|APECS_IO
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
r_int
r_int
id|w
suffix:semicolon
id|w
op_assign
id|__kernel_insbl
c_func
(paren
id|b
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|APECS_IO
op_plus
l_int|0x00
)paren
op_assign
id|w
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|__inw
r_extern
r_inline
r_int
r_int
id|__inw
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
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|APECS_IO
op_plus
l_int|0x08
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
DECL|function|__outw
r_extern
r_inline
r_void
id|__outw
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
r_int
r_int
id|w
suffix:semicolon
id|w
op_assign
id|__kernel_inswl
c_func
(paren
id|b
comma
id|addr
op_amp
l_int|3
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|APECS_IO
op_plus
l_int|0x08
)paren
op_assign
id|w
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|__inl
r_extern
r_inline
r_int
r_int
id|__inl
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
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|APECS_IO
op_plus
l_int|0x18
)paren
suffix:semicolon
)brace
DECL|function|__outl
r_extern
r_inline
r_void
id|__outl
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
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|APECS_IO
op_plus
l_int|0x18
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
multiline_comment|/*&n; * Memory functions.  64-bit and 32-bit accesses are done through&n; * dense memory space, everything else through sparse space.&n; */
DECL|function|__readb
r_extern
r_inline
r_int
r_int
id|__readb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|result
comma
id|shift
comma
id|msb
suffix:semicolon
id|shift
op_assign
(paren
id|addr
op_amp
l_int|0x3
)paren
op_star
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
(paren
l_int|1UL
op_lshift
l_int|24
)paren
)paren
(brace
id|msb
op_assign
id|addr
op_amp
l_int|0xf8000000
suffix:semicolon
id|addr
op_sub_assign
id|msb
suffix:semicolon
r_if
c_cond
(paren
id|msb
op_ne
id|hae.cache
)paren
(brace
id|set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
)brace
)brace
id|result
op_assign
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|APECS_SPARSE_MEM
op_plus
l_int|0x00
)paren
suffix:semicolon
id|result
op_rshift_assign
id|shift
suffix:semicolon
r_return
l_int|0xffUL
op_amp
id|result
suffix:semicolon
)brace
DECL|function|__readw
r_extern
r_inline
r_int
r_int
id|__readw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|result
comma
id|shift
comma
id|msb
suffix:semicolon
id|shift
op_assign
(paren
id|addr
op_amp
l_int|0x3
)paren
op_star
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
(paren
l_int|1UL
op_lshift
l_int|24
)paren
)paren
(brace
id|msb
op_assign
id|addr
op_amp
l_int|0xf8000000
suffix:semicolon
id|addr
op_sub_assign
id|msb
suffix:semicolon
r_if
c_cond
(paren
id|msb
op_ne
id|hae.cache
)paren
(brace
id|set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
)brace
)brace
id|result
op_assign
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|APECS_SPARSE_MEM
op_plus
l_int|0x08
)paren
suffix:semicolon
id|result
op_rshift_assign
id|shift
suffix:semicolon
r_return
l_int|0xffffUL
op_amp
id|result
suffix:semicolon
)brace
DECL|function|__readl
r_extern
r_inline
r_int
r_int
id|__readl
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
id|vuip
)paren
(paren
id|addr
op_plus
id|APECS_DENSE_MEM
)paren
suffix:semicolon
)brace
DECL|function|__writeb
r_extern
r_inline
r_void
id|__writeb
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
r_int
r_int
id|msb
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
(paren
l_int|1UL
op_lshift
l_int|24
)paren
)paren
(brace
id|msb
op_assign
id|addr
op_amp
l_int|0xf8000000
suffix:semicolon
id|addr
op_sub_assign
id|msb
suffix:semicolon
r_if
c_cond
(paren
id|msb
op_ne
id|hae.cache
)paren
(brace
id|set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
)brace
)brace
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|APECS_SPARSE_MEM
op_plus
l_int|0x00
)paren
op_assign
id|b
op_star
l_int|0x01010101
suffix:semicolon
)brace
DECL|function|__writew
r_extern
r_inline
r_void
id|__writew
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
r_int
r_int
id|msb
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_ge
(paren
l_int|1UL
op_lshift
l_int|24
)paren
)paren
(brace
id|msb
op_assign
id|addr
op_amp
l_int|0xf8000000
suffix:semicolon
id|addr
op_sub_assign
id|msb
suffix:semicolon
r_if
c_cond
(paren
id|msb
op_ne
id|hae.cache
)paren
(brace
id|set_hae
c_func
(paren
id|msb
)paren
suffix:semicolon
)brace
)brace
op_star
(paren
id|vuip
)paren
(paren
(paren
id|addr
op_lshift
l_int|5
)paren
op_plus
id|APECS_SPARSE_MEM
op_plus
l_int|0x08
)paren
op_assign
id|b
op_star
l_int|0x00010001
suffix:semicolon
)brace
DECL|function|__writel
r_extern
r_inline
r_void
id|__writel
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
id|vuip
)paren
(paren
id|addr
op_plus
id|APECS_DENSE_MEM
)paren
op_assign
id|b
suffix:semicolon
)brace
DECL|macro|inb
mdefine_line|#define inb(port) &bslash;&n;(__builtin_constant_p((port))?__inb(port):_inb(port))
DECL|macro|outb
mdefine_line|#define outb(x, port) &bslash;&n;(__builtin_constant_p((port))?__outb((x),(port)):_outb((x),(port)))
DECL|macro|readl
mdefine_line|#define readl(a)&t;__readl((unsigned long)(a))
DECL|macro|writel
mdefine_line|#define writel(v,a)&t;__writel((v),(unsigned long)(a))
DECL|macro|vuip
macro_line|#undef vuip
r_extern
r_int
r_int
id|apecs_init
(paren
r_int
r_int
id|mem_start
comma
r_int
r_int
id|mem_end
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * Data structure for handling APECS machine checks:&n; */
macro_line|#ifdef CONFIG_ALPHA_MIKASA
DECL|struct|el_apecs_sysdata_mcheck
r_struct
id|el_apecs_sysdata_mcheck
(brace
DECL|member|coma_gcr
r_int
r_int
id|coma_gcr
suffix:semicolon
DECL|member|coma_edsr
r_int
r_int
id|coma_edsr
suffix:semicolon
DECL|member|coma_ter
r_int
r_int
id|coma_ter
suffix:semicolon
DECL|member|coma_elar
r_int
r_int
id|coma_elar
suffix:semicolon
DECL|member|coma_ehar
r_int
r_int
id|coma_ehar
suffix:semicolon
DECL|member|coma_ldlr
r_int
r_int
id|coma_ldlr
suffix:semicolon
DECL|member|coma_ldhr
r_int
r_int
id|coma_ldhr
suffix:semicolon
DECL|member|coma_base0
r_int
r_int
id|coma_base0
suffix:semicolon
DECL|member|coma_base1
r_int
r_int
id|coma_base1
suffix:semicolon
DECL|member|coma_base2
r_int
r_int
id|coma_base2
suffix:semicolon
DECL|member|coma_base3
r_int
r_int
id|coma_base3
suffix:semicolon
DECL|member|coma_cnfg0
r_int
r_int
id|coma_cnfg0
suffix:semicolon
DECL|member|coma_cnfg1
r_int
r_int
id|coma_cnfg1
suffix:semicolon
DECL|member|coma_cnfg2
r_int
r_int
id|coma_cnfg2
suffix:semicolon
DECL|member|coma_cnfg3
r_int
r_int
id|coma_cnfg3
suffix:semicolon
DECL|member|epic_dcsr
r_int
r_int
id|epic_dcsr
suffix:semicolon
DECL|member|epic_pear
r_int
r_int
id|epic_pear
suffix:semicolon
DECL|member|epic_sear
r_int
r_int
id|epic_sear
suffix:semicolon
DECL|member|epic_tbr1
r_int
r_int
id|epic_tbr1
suffix:semicolon
DECL|member|epic_tbr2
r_int
r_int
id|epic_tbr2
suffix:semicolon
DECL|member|epic_pbr1
r_int
r_int
id|epic_pbr1
suffix:semicolon
DECL|member|epic_pbr2
r_int
r_int
id|epic_pbr2
suffix:semicolon
DECL|member|epic_pmr1
r_int
r_int
id|epic_pmr1
suffix:semicolon
DECL|member|epic_pmr2
r_int
r_int
id|epic_pmr2
suffix:semicolon
DECL|member|epic_harx1
r_int
r_int
id|epic_harx1
suffix:semicolon
DECL|member|epic_harx2
r_int
r_int
id|epic_harx2
suffix:semicolon
DECL|member|epic_pmlt
r_int
r_int
id|epic_pmlt
suffix:semicolon
DECL|member|epic_tag0
r_int
r_int
id|epic_tag0
suffix:semicolon
DECL|member|epic_tag1
r_int
r_int
id|epic_tag1
suffix:semicolon
DECL|member|epic_tag2
r_int
r_int
id|epic_tag2
suffix:semicolon
DECL|member|epic_tag3
r_int
r_int
id|epic_tag3
suffix:semicolon
DECL|member|epic_tag4
r_int
r_int
id|epic_tag4
suffix:semicolon
DECL|member|epic_tag5
r_int
r_int
id|epic_tag5
suffix:semicolon
DECL|member|epic_tag6
r_int
r_int
id|epic_tag6
suffix:semicolon
DECL|member|epic_tag7
r_int
r_int
id|epic_tag7
suffix:semicolon
DECL|member|epic_data0
r_int
r_int
id|epic_data0
suffix:semicolon
DECL|member|epic_data1
r_int
r_int
id|epic_data1
suffix:semicolon
DECL|member|epic_data2
r_int
r_int
id|epic_data2
suffix:semicolon
DECL|member|epic_data3
r_int
r_int
id|epic_data3
suffix:semicolon
DECL|member|epic_data4
r_int
r_int
id|epic_data4
suffix:semicolon
DECL|member|epic_data5
r_int
r_int
id|epic_data5
suffix:semicolon
DECL|member|epic_data6
r_int
r_int
id|epic_data6
suffix:semicolon
DECL|member|epic_data7
r_int
r_int
id|epic_data7
suffix:semicolon
DECL|member|pceb_vid
r_int
r_int
id|pceb_vid
suffix:semicolon
DECL|member|pceb_did
r_int
r_int
id|pceb_did
suffix:semicolon
DECL|member|pceb_revision
r_int
r_int
id|pceb_revision
suffix:semicolon
DECL|member|pceb_command
r_int
r_int
id|pceb_command
suffix:semicolon
DECL|member|pceb_status
r_int
r_int
id|pceb_status
suffix:semicolon
DECL|member|pceb_latency
r_int
r_int
id|pceb_latency
suffix:semicolon
DECL|member|pceb_control
r_int
r_int
id|pceb_control
suffix:semicolon
DECL|member|pceb_arbcon
r_int
r_int
id|pceb_arbcon
suffix:semicolon
DECL|member|pceb_arbpri
r_int
r_int
id|pceb_arbpri
suffix:semicolon
DECL|member|esc_id
r_int
r_int
id|esc_id
suffix:semicolon
DECL|member|esc_revision
r_int
r_int
id|esc_revision
suffix:semicolon
DECL|member|esc_int0
r_int
r_int
id|esc_int0
suffix:semicolon
DECL|member|esc_int1
r_int
r_int
id|esc_int1
suffix:semicolon
DECL|member|esc_elcr0
r_int
r_int
id|esc_elcr0
suffix:semicolon
DECL|member|esc_elcr1
r_int
r_int
id|esc_elcr1
suffix:semicolon
DECL|member|esc_last_eisa
r_int
r_int
id|esc_last_eisa
suffix:semicolon
DECL|member|esc_nmi_stat
r_int
r_int
id|esc_nmi_stat
suffix:semicolon
DECL|member|pci_ir
r_int
r_int
id|pci_ir
suffix:semicolon
DECL|member|pci_imr
r_int
r_int
id|pci_imr
suffix:semicolon
DECL|member|svr_mgr
r_int
r_int
id|svr_mgr
suffix:semicolon
)brace
suffix:semicolon
macro_line|#else /* CONFIG_ALPHA_MIKASA */
multiline_comment|/* this for the normal APECS machines */
DECL|struct|el_apecs_sysdata_mcheck
r_struct
id|el_apecs_sysdata_mcheck
(brace
DECL|member|coma_gcr
r_int
r_int
id|coma_gcr
suffix:semicolon
DECL|member|coma_edsr
r_int
r_int
id|coma_edsr
suffix:semicolon
DECL|member|coma_ter
r_int
r_int
id|coma_ter
suffix:semicolon
DECL|member|coma_elar
r_int
r_int
id|coma_elar
suffix:semicolon
DECL|member|coma_ehar
r_int
r_int
id|coma_ehar
suffix:semicolon
DECL|member|coma_ldlr
r_int
r_int
id|coma_ldlr
suffix:semicolon
DECL|member|coma_ldhr
r_int
r_int
id|coma_ldhr
suffix:semicolon
DECL|member|coma_base0
r_int
r_int
id|coma_base0
suffix:semicolon
DECL|member|coma_base1
r_int
r_int
id|coma_base1
suffix:semicolon
DECL|member|coma_base2
r_int
r_int
id|coma_base2
suffix:semicolon
DECL|member|coma_cnfg0
r_int
r_int
id|coma_cnfg0
suffix:semicolon
DECL|member|coma_cnfg1
r_int
r_int
id|coma_cnfg1
suffix:semicolon
DECL|member|coma_cnfg2
r_int
r_int
id|coma_cnfg2
suffix:semicolon
DECL|member|epic_dcsr
r_int
r_int
id|epic_dcsr
suffix:semicolon
DECL|member|epic_pear
r_int
r_int
id|epic_pear
suffix:semicolon
DECL|member|epic_sear
r_int
r_int
id|epic_sear
suffix:semicolon
DECL|member|epic_tbr1
r_int
r_int
id|epic_tbr1
suffix:semicolon
DECL|member|epic_tbr2
r_int
r_int
id|epic_tbr2
suffix:semicolon
DECL|member|epic_pbr1
r_int
r_int
id|epic_pbr1
suffix:semicolon
DECL|member|epic_pbr2
r_int
r_int
id|epic_pbr2
suffix:semicolon
DECL|member|epic_pmr1
r_int
r_int
id|epic_pmr1
suffix:semicolon
DECL|member|epic_pmr2
r_int
r_int
id|epic_pmr2
suffix:semicolon
DECL|member|epic_harx1
r_int
r_int
id|epic_harx1
suffix:semicolon
DECL|member|epic_harx2
r_int
r_int
id|epic_harx2
suffix:semicolon
DECL|member|epic_pmlt
r_int
r_int
id|epic_pmlt
suffix:semicolon
DECL|member|epic_tag0
r_int
r_int
id|epic_tag0
suffix:semicolon
DECL|member|epic_tag1
r_int
r_int
id|epic_tag1
suffix:semicolon
DECL|member|epic_tag2
r_int
r_int
id|epic_tag2
suffix:semicolon
DECL|member|epic_tag3
r_int
r_int
id|epic_tag3
suffix:semicolon
DECL|member|epic_tag4
r_int
r_int
id|epic_tag4
suffix:semicolon
DECL|member|epic_tag5
r_int
r_int
id|epic_tag5
suffix:semicolon
DECL|member|epic_tag6
r_int
r_int
id|epic_tag6
suffix:semicolon
DECL|member|epic_tag7
r_int
r_int
id|epic_tag7
suffix:semicolon
DECL|member|epic_data0
r_int
r_int
id|epic_data0
suffix:semicolon
DECL|member|epic_data1
r_int
r_int
id|epic_data1
suffix:semicolon
DECL|member|epic_data2
r_int
r_int
id|epic_data2
suffix:semicolon
DECL|member|epic_data3
r_int
r_int
id|epic_data3
suffix:semicolon
DECL|member|epic_data4
r_int
r_int
id|epic_data4
suffix:semicolon
DECL|member|epic_data5
r_int
r_int
id|epic_data5
suffix:semicolon
DECL|member|epic_data6
r_int
r_int
id|epic_data6
suffix:semicolon
DECL|member|epic_data7
r_int
r_int
id|epic_data7
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* CONFIG_ALPHA_MIKASA */
DECL|struct|el_procdata
r_struct
id|el_procdata
(brace
DECL|member|paltemp
r_int
r_int
id|paltemp
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* PAL TEMP REGS. */
multiline_comment|/* EV4-specific fields */
DECL|member|exc_addr
r_int
r_int
id|exc_addr
suffix:semicolon
multiline_comment|/* Address of excepting instruction. */
DECL|member|exc_sum
r_int
r_int
id|exc_sum
suffix:semicolon
multiline_comment|/* Summary of arithmetic traps. */
DECL|member|exc_mask
r_int
r_int
id|exc_mask
suffix:semicolon
multiline_comment|/* Exception mask (from exc_sum). */
DECL|member|iccsr
r_int
r_int
id|iccsr
suffix:semicolon
multiline_comment|/* IBox hardware enables. */
DECL|member|pal_base
r_int
r_int
id|pal_base
suffix:semicolon
multiline_comment|/* Base address for PALcode. */
DECL|member|hier
r_int
r_int
id|hier
suffix:semicolon
multiline_comment|/* Hardware Interrupt Enable. */
DECL|member|hirr
r_int
r_int
id|hirr
suffix:semicolon
multiline_comment|/* Hardware Interrupt Request. */
DECL|member|csr
r_int
r_int
id|csr
suffix:semicolon
multiline_comment|/* D-stream fault info. */
DECL|member|dc_stat
r_int
r_int
id|dc_stat
suffix:semicolon
multiline_comment|/* D-cache status (ECC/Parity Err). */
DECL|member|dc_addr
r_int
r_int
id|dc_addr
suffix:semicolon
multiline_comment|/* EV3 Phys Addr for ECC/DPERR. */
DECL|member|abox_ctl
r_int
r_int
id|abox_ctl
suffix:semicolon
multiline_comment|/* ABox Control Register. */
DECL|member|biu_stat
r_int
r_int
id|biu_stat
suffix:semicolon
multiline_comment|/* BIU Status. */
DECL|member|biu_addr
r_int
r_int
id|biu_addr
suffix:semicolon
multiline_comment|/* BUI Address. */
DECL|member|biu_ctl
r_int
r_int
id|biu_ctl
suffix:semicolon
multiline_comment|/* BIU Control. */
DECL|member|fill_syndrome
r_int
r_int
id|fill_syndrome
suffix:semicolon
multiline_comment|/* For correcting ECC errors. */
DECL|member|fill_addr
r_int
r_int
id|fill_addr
suffix:semicolon
multiline_comment|/* Cache block which was being read */
DECL|member|va
r_int
r_int
id|va
suffix:semicolon
multiline_comment|/* Effective VA of fault or miss. */
DECL|member|bc_tag
r_int
r_int
id|bc_tag
suffix:semicolon
multiline_comment|/* Backup Cache Tag Probe Results.*/
)brace
suffix:semicolon
DECL|macro|RTC_PORT
mdefine_line|#define RTC_PORT(x)&t;(0x70 + (x))
DECL|macro|RTC_ADDR
mdefine_line|#define RTC_ADDR(x)&t;(0x80 | (x))
DECL|macro|RTC_ALWAYS_BCD
mdefine_line|#define RTC_ALWAYS_BCD&t;0
macro_line|#endif /* __ALPHA_APECS__H__ */
eof
