multiline_comment|/*&n; * arch/arm/mm/mm-footbridge.c&n; *&n; * Extra MM routines for the EBSA285 architecture&n; *&n; * Copyright (C) 1998-1999 Russell King, Dave Gilbert.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dec21285.h&gt;
macro_line|#include &quot;map.h&quot;
DECL|macro|SIZE
mdefine_line|#define SIZE(x) (sizeof(x) / sizeof(x[0]))
multiline_comment|/*&n; * The first entry allows us to fiddle with the EEPROM from user-space.&n; *  This entry will go away in time, once the fmu32 can mmap() the&n; *  flash.  It can&squot;t at the moment.&n; *&n; * If you want to fiddle with PCI VGA cards from user space, then&n; * change the &squot;0, 1 }&squot; for the PCI MEM and PCI IO to &squot;1, 1 }&squot;&n; * You can then access the PCI bus at 0xe0000000 and 0xffe00000.&n; */
macro_line|#ifdef CONFIG_FOOTBRIDGE_HOST
multiline_comment|/*&n; * The mapping when the footbridge is in host mode.&n; */
DECL|macro|MAPPING
mdefine_line|#define MAPPING &bslash;&n; { FLASH_BASE,   DC21285_FLASH,&t;&t;&t;FLASH_SIZE,&t;DOMAIN_IO, 0, 1, 0, 0 }, &bslash;&n; { PCIMEM_BASE,  DC21285_PCI_MEM,&t;&t;PCIMEM_SIZE,&t;DOMAIN_IO, 0, 1, 0, 0 }, &bslash;&n; { PCICFG0_BASE, DC21285_PCI_TYPE_0_CONFIG,&t;PCICFG0_SIZE,&t;DOMAIN_IO, 0, 1, 0, 0 }, &bslash;&n; { PCICFG1_BASE, DC21285_PCI_TYPE_1_CONFIG,&t;PCICFG1_SIZE,&t;DOMAIN_IO, 0, 1, 0, 0 }, &bslash;&n; { PCIIACK_BASE, DC21285_PCI_IACK,&t;&t;PCIIACK_SIZE,&t;DOMAIN_IO, 0, 1, 0, 0 }, &bslash;&n; { WFLUSH_BASE,  DC21285_OUTBOUND_WRITE_FLUSH,&t;WFLUSH_SIZE,&t;DOMAIN_IO, 0, 1, 0, 0 }, &bslash;&n; { ARMCSR_BASE,  DC21285_ARMCSR_BASE,&t;&t;ARMCSR_SIZE,&t;DOMAIN_IO, 0, 1, 0, 0 }, &bslash;&n; { PCIO_BASE,    DC21285_PCI_IO,&t;&t;PCIO_SIZE,&t;DOMAIN_IO, 0, 1, 0, 0 }, &bslash;&n; { XBUS_BASE,    0x40000000,&t;&t;&t;XBUS_SIZE,&t;DOMAIN_IO, 0, 1, 0, 0 }
macro_line|#else
multiline_comment|/*&n; * These two functions convert virtual addresses to PCI addresses&n; * and PCI addresses to virtual addresses.  Note that it is only&n; * legal to use these on memory obtained via get_free_page or&n; * kmalloc.&n; */
DECL|function|__virt_to_bus
r_int
r_int
id|__virt_to_bus
c_func
(paren
r_int
r_int
id|res
)paren
(brace
macro_line|#ifdef CONFIG_DEBUG_ERRORS
r_if
c_cond
(paren
id|res
OL
id|PAGE_OFFSET
op_logical_or
id|res
op_ge
(paren
r_int
r_int
)paren
id|high_memory
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;__virt_to_phys: invalid virtual address 0x%08lx&bslash;n&quot;
comma
id|res
)paren
suffix:semicolon
id|__backtrace
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
(paren
id|res
op_minus
id|PAGE_OFFSET
)paren
op_plus
(paren
op_star
id|CSR_PCISDRAMBASE
op_amp
l_int|0xfffffff0
)paren
suffix:semicolon
)brace
DECL|function|__bus_to_virt
r_int
r_int
id|__bus_to_virt
c_func
(paren
r_int
r_int
id|res
)paren
(brace
id|res
op_sub_assign
(paren
op_star
id|CSR_PCISDRAMBASE
op_amp
l_int|0xfffffff0
)paren
suffix:semicolon
id|res
op_add_assign
id|PAGE_OFFSET
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_ERRORS
r_if
c_cond
(paren
id|res
OL
id|PAGE_OFFSET
op_logical_or
id|res
op_ge
(paren
r_int
r_int
)paren
id|high_memory
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;__phys_to_virt: invalid virtual address 0x%08lx&bslash;n&quot;
comma
id|res
)paren
suffix:semicolon
id|__backtrace
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
id|res
suffix:semicolon
)brace
multiline_comment|/*&n; * The mapping when the footbridge is in add-in mode.&n; */
DECL|macro|MAPPING
mdefine_line|#define MAPPING &bslash;&n; { PCIO_BASE,&t; DC21285_PCI_IO,&t;&t;PCIO_SIZE,&t;DOMAIN_IO, 0, 1, 0, 0 }, &bslash;&n; { XBUS_BASE,&t; 0x40000000,&t;&t;&t;XBUS_SIZE,&t;DOMAIN_IO, 0, 1, 0, 0 }, &bslash;&n; { ARMCSR_BASE,  DC21285_ARMCSR_BASE,&t;&t;ARMCSR_SIZE,&t;DOMAIN_IO, 0, 1, 0, 0 }, &bslash;&n; { WFLUSH_BASE,&t; DC21285_OUTBOUND_WRITE_FLUSH,&t;WFLUSH_SIZE,&t;DOMAIN_IO, 0, 1, 0, 0 }, &bslash;&n; { FLASH_BASE,&t; DC21285_FLASH,&t;&t;&t;FLASH_SIZE,&t;DOMAIN_IO, 0, 1, 0, 0 }, &bslash;&n; { PCIMEM_BASE,&t; DC21285_PCI_MEM,&t;&t;PCIMEM_SIZE,&t;DOMAIN_IO, 0, 1, 0, 0 }
macro_line|#endif
DECL|variable|__initdata
r_struct
id|map_desc
id|io_desc
(braket
)braket
id|__initdata
op_assign
(brace
id|MAPPING
)brace
suffix:semicolon
DECL|variable|io_desc_size
r_int
r_int
id|__initdata
id|io_desc_size
op_assign
id|SIZE
c_func
(paren
id|io_desc
)paren
suffix:semicolon
eof
