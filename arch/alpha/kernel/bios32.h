multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/bios32.h&n; *&n; * This file contains declarations and inline functions for interfacing&n; * with the PCI initialization routines in bios32.c.&n; */
DECL|macro|KB
mdefine_line|#define KB&t;&t;1024
DECL|macro|MB
mdefine_line|#define MB&t;&t;(1024*KB)
DECL|macro|GB
mdefine_line|#define GB&t;&t;(1024*MB)
multiline_comment|/*&n; * We can&squot;t just blindly use 64K for machines with EISA busses; they&n; * may also have PCI-PCI bridges present, and then we&squot;d configure the&n; * bridge incorrectly.&n; *&n; * Also, we start at 0x8000 or 0x9000, in hopes to get all devices&squot;&n; * IO space areas allocated *before* 0xC000; this is because certain&n; * BIOSes (Millennium for one) use PCI Config space &quot;mechanism #2&quot;&n; * accesses to probe the bus. If a device&squot;s registers appear at 0xC000,&n; * it may see an INx/OUTx at that address during BIOS emulation of the&n; * VGA BIOS, and some cards, notably Adaptec 2940UW, take mortal offense.&n; *&n; * Note that we may need this stuff for SRM_SETUP also, since certain&n; * SRM consoles screw up and allocate I/O space addresses &gt; 64K behind&n; * PCI-to_PCI bridges, which can&squot;t pass I/O addresses larger than 64K,&n; * AFAIK.&n; */
DECL|macro|EISA_DEFAULT_IO_BASE
mdefine_line|#define EISA_DEFAULT_IO_BASE 0x9000&t;/* start above 8th slot */
DECL|macro|DEFAULT_IO_BASE
mdefine_line|#define DEFAULT_IO_BASE 0x8000&t;&t;/* start at 8th slot */
multiline_comment|/*&n; * We try to make the DEFAULT_MEM_BASE addresses *always* have more than&n; * a single bit set. This is so that devices like the broken Myrinet card&n; * will always have a PCI memory address that will never match a IDSEL&n; * address in PCI Config space, which can cause problems with early rev cards.&n; */
multiline_comment|/*&n; * An XL is AVANTI (APECS) family, *but* it has only 27 bits of ISA address&n; * that get passed through the PCI&lt;-&gt;ISA bridge chip. Although this causes&n; * us to set the PCI-&gt;Mem window bases lower than normal, we still allocate&n; * PCI bus devices&squot; memory addresses *below* the low DMA mapping window,&n; * and hope they fit below 64Mb (to avoid conflicts), and so that they can&n; * be accessed via SPARSE space.&n; *&n; * We accept the risk that a broken Myrinet card will be put into a true XL&n; * and thus can more easily run into the problem described below.&n; */
DECL|macro|XL_DEFAULT_MEM_BASE
mdefine_line|#define XL_DEFAULT_MEM_BASE (16*MB + 2*MB) /* 16M to 64M-1 is avail */
multiline_comment|/*&n; * APECS and LCA have only 34 bits for physical addresses, thus limiting PCI&n; * bus memory addresses for SPARSE access to be less than 128Mb.&n; */
DECL|macro|APECS_AND_LCA_DEFAULT_MEM_BASE
mdefine_line|#define APECS_AND_LCA_DEFAULT_MEM_BASE (64*MB + 2*MB)
multiline_comment|/*&n; * Because the MCPCIA core logic supports more bits for physical addresses,&n; * it should allow an expanded range of SPARSE memory addresses.&n; * However, we do not use them all, in order to avoid the HAE manipulation&n; * that would be needed.&n; */
DECL|macro|RAWHIDE_DEFAULT_MEM_BASE
mdefine_line|#define RAWHIDE_DEFAULT_MEM_BASE (64*MB + 2*MB)
multiline_comment|/*&n; * Because CIA and PYXIS and T2 have more bits for physical addresses,&n; * they support an expanded range of SPARSE memory addresses.&n; */
DECL|macro|DEFAULT_MEM_BASE
mdefine_line|#define DEFAULT_MEM_BASE (128*MB + 16*MB)
multiline_comment|/*&n; * PCI_MODIFY&n; *&n; * If this 0, then do not write to any of the PCI registers, merely&n; * read them (i.e., use configuration as determined by SRM).  The SRM&n; * seem do be doing a less than perfect job in configuring PCI&n; * devices, so for now we do it ourselves.  Reconfiguring PCI devices&n; * breaks console (RPB) callbacks, but those don&squot;t work properly with&n; * 64 bit addresses anyways.&n; *&n; * The accepted convention seems to be that the console (POST&n; * software) should fully configure boot devices and configure the&n; * interrupt routing of *all* devices.  In particular, the base&n; * addresses of non-boot devices need not be initialized.  For&n; * example, on the AXPpci33 board, the base address a #9 GXE PCI&n; * graphics card reads as zero (this may, however, be due to a bug in&n; * the graphics card---there have been some rumor that the #9 BIOS&n; * incorrectly resets that address to 0...).&n; */
DECL|macro|PCI_MODIFY
mdefine_line|#define PCI_MODIFY&t;(!alpha_use_srm_setup)
multiline_comment|/* &n; * A small note about bridges and interrupts.  The DECchip 21050 (and&n; * later) adheres to the PCI-PCI bridge specification.  This says that&n; * the interrupts on the other side of a bridge are swizzled in the&n; * following manner:&n; *&n; * Dev    Interrupt   Interrupt &n; *        Pin on      Pin on &n; *        Device      Connector&n; *&n; *   4    A           A&n; *        B           B&n; *        C           C&n; *        D           D&n; * &n; *   5    A           B&n; *        B           C&n; *        C           D&n; *        D           A&n; *&n; *   6    A           C&n; *        B           D&n; *        C           A&n; *        D           B&n; *&n; *   7    A           D&n; *        B           A&n; *        C           B&n; *        D           C&n; *&n; *   Where A = pin 1, B = pin 2 and so on and pin=0 = default = A.&n; *   Thus, each swizzle is ((pin-1) + (device#-4)) % 4&n; *&n; *   The following code swizzles for exactly one bridge.  The routine&n; *   common_swizzle below handles multiple bridges.  But there are a&n; *   couple boards that do strange things, so we define this here.&n; */
r_static
r_inline
r_int
r_char
DECL|function|bridge_swizzle
id|bridge_swizzle
c_func
(paren
r_int
r_char
id|pin
comma
r_int
r_int
id|slot
)paren
(brace
r_return
(paren
(paren
(paren
id|pin
op_minus
l_int|1
)paren
op_plus
id|slot
)paren
op_mod
l_int|4
)paren
op_plus
l_int|1
suffix:semicolon
)brace
r_extern
r_void
id|layout_all_busses
c_func
(paren
r_int
r_int
id|io_base
comma
r_int
r_int
id|mem_base
)paren
suffix:semicolon
r_extern
r_void
id|enable_ide
c_func
(paren
r_int
id|ide_base
)paren
suffix:semicolon
r_struct
id|pci_dev
suffix:semicolon
r_extern
r_void
id|common_pci_fixup
c_func
(paren
r_int
(paren
op_star
id|map_irq
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|slot
comma
r_int
id|pin
)paren
comma
r_int
(paren
op_star
id|swizzle
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
op_star
id|pin
)paren
)paren
suffix:semicolon
r_extern
r_int
id|common_swizzle
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
op_star
id|pinp
)paren
suffix:semicolon
multiline_comment|/* The following macro is used to implement the table-based irq mapping&n;   function for all single-bus Alphas.  */
DECL|macro|COMMON_TABLE_LOOKUP
mdefine_line|#define COMMON_TABLE_LOOKUP&t;&t;&t;&t;&t;&t;&bslash;&n;({ long _ctl_ = -1; &t;&t;&t;&t;&t;&t;&t;&bslash;&n;   if (slot &gt;= min_idsel &amp;&amp; slot &lt;= max_idsel &amp;&amp; pin &lt; irqs_per_slot)&t;&bslash;&n;     _ctl_ = irq_tab[slot - min_idsel][pin];&t;&t;&t;&t;&bslash;&n;   _ctl_; })
multiline_comment|/* The hose list.  */
r_extern
r_struct
id|linux_hose_info
op_star
id|hose_head
comma
op_star
op_star
id|hose_tail
suffix:semicolon
r_extern
r_int
id|hose_count
suffix:semicolon
r_extern
r_int
id|pci_probe_enabled
suffix:semicolon
eof
