multiline_comment|/* ne2k-pci.c: A NE2000 clone on PCI bus driver for Linux. */
multiline_comment|/*&n;&t;A Linux device driver for PCI NE2000 clones.&n;&n;&t;Authorship and other copyrights:&n;&t;1992-1998 by Donald Becker, NE2000 core and various modifications.&n;&t;1995-1998 by Paul Gortmaker, core modifications and PCI support.&n;&n;&t;Copyright 1993 assigned to the United States Government as represented&n;&t;by the Director, National Security Agency.&n;&n;&t;This software may be used and distributed according to the terms&n;&t;of the GNU Public License, incorporated herein by reference.&n;&n;&t;The author may be reached as becker@CESDIS.gsfc.nasa.gov, or C/O&n;&t;Center of Excellence in Space Data and Information Sciences&n;&t;Code 930.5, Goddard Space Flight Center, Greenbelt MD 20771&n;&n;&t;People are making PCI ne2000 clones! Oh the horror, the horror...&n;&n;&t;Issues remaining:&n;&t;No full-duplex support.&n;*/
multiline_comment|/* Our copyright info must remain in the binary. */
DECL|variable|version
r_static
r_const
r_char
op_star
id|version
op_assign
l_string|&quot;ne2k-pci.c:vpre-1.00e 5/27/99 D. Becker/P. Gortmaker http://cesdis.gsfc.nasa.gov/linux/drivers/ne2k-pci.html&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &quot;8390.h&quot;
macro_line|#if defined(__powerpc__)
DECL|macro|inl_le
mdefine_line|#define inl_le(addr)  le32_to_cpu(inl(addr))
DECL|macro|inw_le
mdefine_line|#define inw_le(addr)  le16_to_cpu(inw(addr))
DECL|macro|insl
mdefine_line|#define insl insl_ns
DECL|macro|outsl
mdefine_line|#define outsl outsl_ns
macro_line|#endif
multiline_comment|/* Set statically or when loading the driver module. */
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Some defines that people can play with if so inclined. */
multiline_comment|/* Use 32 bit data-movement operations instead of 16 bit. */
DECL|macro|USE_LONGIO
mdefine_line|#define USE_LONGIO
multiline_comment|/* Do we implement the read before write bugfix ? */
multiline_comment|/* #define NE_RW_BUGFIX */
multiline_comment|/* Do we have a non std. amount of memory? (in units of 256 byte pages) */
multiline_comment|/* #define PACKETBUF_MEMSIZE&t;0x40 */
DECL|macro|ne2k_flags
mdefine_line|#define ne2k_flags reg0&t;&t;&t;/* Rename an existing field to store flags! */
multiline_comment|/* Only the low 8 bits are usable for non-init-time flags! */
r_enum
(brace
DECL|enumerator|HOLTEK_FDX
id|HOLTEK_FDX
op_assign
l_int|1
comma
multiline_comment|/* Full duplex -&gt; set 0x80 at offset 0x20. */
DECL|enumerator|ONLY_16BIT_IO
DECL|enumerator|ONLY_32BIT_IO
id|ONLY_16BIT_IO
op_assign
l_int|2
comma
id|ONLY_32BIT_IO
op_assign
l_int|4
comma
multiline_comment|/* Chip can do only 16/32-bit xfers. */
DECL|enumerator|STOP_PG_0x60
id|STOP_PG_0x60
op_assign
l_int|0x100
comma
)brace
suffix:semicolon
DECL|enum|ne2k_pci_chipsets
r_enum
id|ne2k_pci_chipsets
(brace
DECL|enumerator|CH_RealTek_RTL_8029
id|CH_RealTek_RTL_8029
op_assign
l_int|0
comma
DECL|enumerator|CH_Winbond_89C940
id|CH_Winbond_89C940
comma
DECL|enumerator|CH_Compex_RL2000
id|CH_Compex_RL2000
comma
DECL|enumerator|CH_KTI_ET32P2
id|CH_KTI_ET32P2
comma
DECL|enumerator|CH_NetVin_NV5000SC
id|CH_NetVin_NV5000SC
comma
DECL|enumerator|CH_Via_86C926
id|CH_Via_86C926
comma
DECL|enumerator|CH_SureCom_NE34
id|CH_SureCom_NE34
comma
DECL|enumerator|CH_Winbond_W89C940F
id|CH_Winbond_W89C940F
comma
DECL|enumerator|CH_Holtek_HT80232
id|CH_Holtek_HT80232
comma
DECL|enumerator|CH_Holtek_HT80229
id|CH_Holtek_HT80229
comma
)brace
suffix:semicolon
r_static
r_struct
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|variable|__devinitdata
)brace
id|pci_clone_list
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
l_string|&quot;RealTek RTL-8029&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;Winbond 89C940&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;Compex RL2000&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;KTI ET32P2&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;NetVin NV5000SC&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;Via 86C926&quot;
comma
id|ONLY_16BIT_IO
)brace
comma
(brace
l_string|&quot;SureCom NE34&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;Winbond W89C940F&quot;
comma
l_int|0
)brace
comma
(brace
l_string|&quot;Holtek HT80232&quot;
comma
id|ONLY_16BIT_IO
op_or
id|HOLTEK_FDX
)brace
comma
(brace
l_string|&quot;Holtek HT80229&quot;
comma
id|ONLY_32BIT_IO
op_or
id|HOLTEK_FDX
op_or
id|STOP_PG_0x60
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|variable|__devinitdata
r_static
r_struct
id|pci_device_id
id|ne2k_pci_tbl
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
l_int|0x10ec
comma
l_int|0x8029
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|CH_RealTek_RTL_8029
)brace
comma
(brace
l_int|0x1050
comma
l_int|0x0940
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|CH_Winbond_89C940
)brace
comma
(brace
l_int|0x11f6
comma
l_int|0x1401
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|CH_Compex_RL2000
)brace
comma
(brace
l_int|0x8e2e
comma
l_int|0x3000
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|CH_KTI_ET32P2
)brace
comma
(brace
l_int|0x4a14
comma
l_int|0x5000
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|CH_NetVin_NV5000SC
)brace
comma
(brace
l_int|0x1106
comma
l_int|0x0926
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|CH_Via_86C926
)brace
comma
(brace
l_int|0x10bd
comma
l_int|0x0e34
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|CH_SureCom_NE34
)brace
comma
(brace
l_int|0x1050
comma
l_int|0x5a5a
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|CH_Winbond_W89C940F
)brace
comma
(brace
l_int|0x12c3
comma
l_int|0x0058
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|CH_Holtek_HT80232
)brace
comma
(brace
l_int|0x12c3
comma
l_int|0x5598
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|CH_Holtek_HT80229
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|ne2k_pci_tbl
)paren
suffix:semicolon
multiline_comment|/* ---- No user-serviceable parts below ---- */
DECL|macro|NE_BASE
mdefine_line|#define NE_BASE&t; (dev-&gt;base_addr)
DECL|macro|NE_CMD
mdefine_line|#define NE_CMD&t; &t;0x00
DECL|macro|NE_DATAPORT
mdefine_line|#define NE_DATAPORT&t;0x10&t;/* NatSemi-defined port window offset. */
DECL|macro|NE_RESET
mdefine_line|#define NE_RESET&t;0x1f&t;/* Issue a read to reset, a write to clear. */
DECL|macro|NE_IO_EXTENT
mdefine_line|#define NE_IO_EXTENT&t;0x20
DECL|macro|NESM_START_PG
mdefine_line|#define NESM_START_PG&t;0x40&t;/* First page of TX buffer */
DECL|macro|NESM_STOP_PG
mdefine_line|#define NESM_STOP_PG&t;0x80&t;/* Last page +1 of RX ring */
r_static
r_int
id|ne2k_pci_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|ne2k_pci_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|ne2k_pci_reset_8390
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|ne2k_pci_get_8390_hdr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|e8390_pkt_hdr
op_star
id|hdr
comma
r_int
id|ring_page
)paren
suffix:semicolon
r_static
r_void
id|ne2k_pci_block_input
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|ring_offset
)paren
suffix:semicolon
r_static
r_void
id|ne2k_pci_block_output
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_const
r_int
id|count
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_const
r_int
id|start_page
)paren
suffix:semicolon
"&f;"
multiline_comment|/* No room in the standard 8390 structure for extra info we need. */
DECL|struct|ne2k_pci_card
r_struct
id|ne2k_pci_card
(brace
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
DECL|member|pci_dev
r_struct
id|pci_dev
op_star
id|pci_dev
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n;  NEx000-clone boards have a Station Address (SA) PROM (SAPROM) in the packet&n;  buffer memory space.  By-the-spec NE2000 clones have 0x57,0x57 in bytes&n;  0x0e,0x0f of the SAPROM, while other supposed NE2000 clones must be&n;  detected by their SA prefix.&n;&n;  Reading the SAPROM from a word-wide card with the 8390 set in byte-wide&n;  mode results in doubled values, which can be detected and compensated for.&n;&n;  The probe is also responsible for initializing the card and filling&n;  in the &squot;dev&squot; and &squot;ei_status&squot; structures.&n;*/
DECL|function|ne2k_pci_init_one
r_static
r_int
id|__devinit
id|ne2k_pci_init_one
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_int
id|i
comma
id|irq
comma
id|reg0
comma
id|start_page
comma
id|stop_page
suffix:semicolon
r_int
r_char
id|SA_prom
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|chip_idx
op_assign
id|ent-&gt;driver_data
suffix:semicolon
r_static
r_int
id|version_printed
op_assign
l_int|0
suffix:semicolon
r_int
id|ioaddr
suffix:semicolon
r_if
c_cond
(paren
id|version_printed
op_increment
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s&quot;
comma
id|version
)paren
suffix:semicolon
id|ioaddr
op_assign
id|pci_resource_start
(paren
id|pdev
comma
l_int|0
)paren
suffix:semicolon
id|irq
op_assign
id|pdev-&gt;irq
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ioaddr
op_logical_or
(paren
(paren
id|pci_resource_flags
(paren
id|pdev
comma
l_int|0
)paren
op_amp
id|IORESOURCE_IO
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;ne2k-pci: no I/O resource at PCI BAR #0&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|i
op_assign
id|pci_enable_device
(paren
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
r_if
c_cond
(paren
id|request_region
(paren
id|ioaddr
comma
id|NE_IO_EXTENT
comma
l_string|&quot;ne2k-pci&quot;
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;ne2k-pci: I/O resource 0x%x @ 0x%lx busy&bslash;n&quot;
comma
id|NE_IO_EXTENT
comma
id|ioaddr
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|reg0
op_assign
id|inb
c_func
(paren
id|ioaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg0
op_eq
l_int|0xFF
)paren
r_goto
id|err_out_free_res
suffix:semicolon
multiline_comment|/* Do a preliminary verification that we have a 8390. */
(brace
r_int
id|regd
suffix:semicolon
id|outb
c_func
(paren
id|E8390_NODMA
op_plus
id|E8390_PAGE1
op_plus
id|E8390_STOP
comma
id|ioaddr
op_plus
id|E8390_CMD
)paren
suffix:semicolon
id|regd
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|0x0d
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xff
comma
id|ioaddr
op_plus
l_int|0x0d
)paren
suffix:semicolon
id|outb
c_func
(paren
id|E8390_NODMA
op_plus
id|E8390_PAGE0
comma
id|ioaddr
op_plus
id|E8390_CMD
)paren
suffix:semicolon
id|inb
c_func
(paren
id|ioaddr
op_plus
id|EN0_COUNTER0
)paren
suffix:semicolon
multiline_comment|/* Clear the counter by reading. */
r_if
c_cond
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|EN0_COUNTER0
)paren
op_ne
l_int|0
)paren
(brace
id|outb
c_func
(paren
id|reg0
comma
id|ioaddr
)paren
suffix:semicolon
id|outb
c_func
(paren
id|regd
comma
id|ioaddr
op_plus
l_int|0x0d
)paren
suffix:semicolon
multiline_comment|/* Restore the old values. */
r_goto
id|err_out_free_res
suffix:semicolon
)brace
)brace
id|dev
op_assign
id|init_etherdev
c_func
(paren
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;ne2k-pci: cannot allocate ethernet device&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_out_free_res
suffix:semicolon
)brace
multiline_comment|/* Reset card. Who knows what dain-bramaged state it was left in. */
(brace
r_int
r_int
id|reset_start_time
op_assign
id|jiffies
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|NE_RESET
)paren
comma
id|ioaddr
op_plus
id|NE_RESET
)paren
suffix:semicolon
multiline_comment|/* This looks like a horrible timing loop, but it should never take&n;&t;&t;   more than a few cycles.&n;&t;&t;*/
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|EN0_ISR
)paren
op_amp
id|ENISR_RESET
)paren
op_eq
l_int|0
)paren
multiline_comment|/* Limit wait: &squot;2&squot; avoids jiffy roll-over. */
r_if
c_cond
(paren
id|jiffies
op_minus
id|reset_start_time
OG
l_int|2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ne2k-pci: Card failure (no reset ack).&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err_out_free_netdev
suffix:semicolon
)brace
id|outb
c_func
(paren
l_int|0xff
comma
id|ioaddr
op_plus
id|EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* Ack all intr. */
)brace
multiline_comment|/* Read the 16 bytes of station address PROM.&n;&t;   We must first initialize registers, similar to NS8390_init(eifdev, 0).&n;&t;   We can&squot;t reliably read the SAPROM address without this.&n;&t;   (I learned the hard way!). */
(brace
r_struct
(brace
r_int
r_char
id|value
comma
id|offset
suffix:semicolon
)brace
id|program_seq
(braket
)braket
op_assign
(brace
(brace
id|E8390_NODMA
op_plus
id|E8390_PAGE0
op_plus
id|E8390_STOP
comma
id|E8390_CMD
)brace
comma
multiline_comment|/* Select page 0*/
(brace
l_int|0x49
comma
id|EN0_DCFG
)brace
comma
multiline_comment|/* Set word-wide access. */
(brace
l_int|0x00
comma
id|EN0_RCNTLO
)brace
comma
multiline_comment|/* Clear the count regs. */
(brace
l_int|0x00
comma
id|EN0_RCNTHI
)brace
comma
(brace
l_int|0x00
comma
id|EN0_IMR
)brace
comma
multiline_comment|/* Mask completion irq. */
(brace
l_int|0xFF
comma
id|EN0_ISR
)brace
comma
(brace
id|E8390_RXOFF
comma
id|EN0_RXCR
)brace
comma
multiline_comment|/* 0x20  Set to monitor */
(brace
id|E8390_TXOFF
comma
id|EN0_TXCR
)brace
comma
multiline_comment|/* 0x02  and loopback mode. */
(brace
l_int|32
comma
id|EN0_RCNTLO
)brace
comma
(brace
l_int|0x00
comma
id|EN0_RCNTHI
)brace
comma
(brace
l_int|0x00
comma
id|EN0_RSARLO
)brace
comma
multiline_comment|/* DMA starting at 0x0000. */
(brace
l_int|0x00
comma
id|EN0_RSARHI
)brace
comma
(brace
id|E8390_RREAD
op_plus
id|E8390_START
comma
id|E8390_CMD
)brace
comma
)brace
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
r_sizeof
(paren
id|program_seq
)paren
op_div
r_sizeof
(paren
id|program_seq
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
id|outb
c_func
(paren
id|program_seq
(braket
id|i
)braket
dot
id|value
comma
id|ioaddr
op_plus
id|program_seq
(braket
id|i
)braket
dot
id|offset
)paren
suffix:semicolon
)brace
multiline_comment|/* Note: all PCI cards have at least 16 bit access, so we don&squot;t have&n;&t;   to check for 8 bit cards.  Most cards permit 32 bit access. */
r_if
c_cond
(paren
id|pci_clone_list
(braket
id|chip_idx
)braket
dot
id|flags
op_amp
id|ONLY_32BIT_IO
)paren
(brace
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
(paren
(paren
id|u32
op_star
)paren
id|SA_prom
)paren
(braket
id|i
)braket
op_assign
id|le32_to_cpu
c_func
(paren
id|inl
c_func
(paren
id|ioaddr
op_plus
id|NE_DATAPORT
)paren
)paren
suffix:semicolon
)brace
r_else
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32
multiline_comment|/*sizeof(SA_prom)*/
suffix:semicolon
id|i
op_increment
)paren
(brace
id|SA_prom
(braket
id|i
)braket
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|NE_DATAPORT
)paren
suffix:semicolon
)brace
multiline_comment|/* We always set the 8390 registers for word mode. */
id|outb
c_func
(paren
l_int|0x49
comma
id|ioaddr
op_plus
id|EN0_DCFG
)paren
suffix:semicolon
id|start_page
op_assign
id|NESM_START_PG
suffix:semicolon
id|stop_page
op_assign
id|pci_clone_list
(braket
id|chip_idx
)braket
dot
id|flags
op_amp
id|STOP_PG_0x60
ques
c_cond
l_int|0x60
suffix:colon
id|NESM_STOP_PG
suffix:semicolon
multiline_comment|/* Set up the rest of the parameters. */
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
id|pdev-&gt;driver_data
op_assign
id|dev
suffix:semicolon
multiline_comment|/* Allocate dev-&gt;priv and fill in 8390 specific dev fields. */
r_if
c_cond
(paren
id|ethdev_init
c_func
(paren
id|dev
)paren
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;%s: unable to get memory for dev-&gt;priv.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_goto
id|err_out_free_netdev
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%s: %s found at %#lx, IRQ %d, &quot;
comma
id|dev-&gt;name
comma
id|pci_clone_list
(braket
id|chip_idx
)braket
dot
id|name
comma
id|ioaddr
comma
id|dev-&gt;irq
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%2.2X%s&quot;
comma
id|SA_prom
(braket
id|i
)braket
comma
id|i
op_eq
l_int|5
ques
c_cond
l_string|&quot;.&bslash;n&quot;
suffix:colon
l_string|&quot;:&quot;
)paren
suffix:semicolon
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
id|SA_prom
(braket
id|i
)braket
suffix:semicolon
)brace
id|ei_status.name
op_assign
id|pci_clone_list
(braket
id|chip_idx
)braket
dot
id|name
suffix:semicolon
id|ei_status.tx_start_page
op_assign
id|start_page
suffix:semicolon
id|ei_status.stop_page
op_assign
id|stop_page
suffix:semicolon
id|ei_status.word16
op_assign
l_int|1
suffix:semicolon
id|ei_status.ne2k_flags
op_assign
id|pci_clone_list
(braket
id|chip_idx
)braket
dot
id|flags
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|start_page
op_plus
id|TX_PAGES
suffix:semicolon
macro_line|#ifdef PACKETBUF_MEMSIZE
multiline_comment|/* Allow the packet buffer size to be overridden by know-it-alls. */
id|ei_status.stop_page
op_assign
id|ei_status.tx_start_page
op_plus
id|PACKETBUF_MEMSIZE
suffix:semicolon
macro_line|#endif
id|ei_status.reset_8390
op_assign
op_amp
id|ne2k_pci_reset_8390
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|ne2k_pci_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|ne2k_pci_block_output
suffix:semicolon
id|ei_status.get_8390_hdr
op_assign
op_amp
id|ne2k_pci_get_8390_hdr
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|ne2k_pci_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|ne2k_pci_close
suffix:semicolon
id|NS8390_init
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err_out_free_netdev
suffix:colon
id|unregister_netdev
(paren
id|dev
)paren
suffix:semicolon
id|kfree
(paren
id|dev
)paren
suffix:semicolon
id|err_out_free_res
suffix:colon
id|release_region
(paren
id|ioaddr
comma
id|NE_IO_EXTENT
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_static
r_int
DECL|function|ne2k_pci_open
id|ne2k_pci_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
id|ei_interrupt
comma
id|SA_SHIRQ
comma
id|dev-&gt;name
comma
id|dev
)paren
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|ei_open
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|ne2k_pci_close
id|ne2k_pci_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|ei_close
c_func
(paren
id|dev
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Hard reset the card.  This used to pause for the same period that a&n;   8390 reset command required, but that shouldn&squot;t be necessary. */
r_static
r_void
DECL|function|ne2k_pci_reset_8390
id|ne2k_pci_reset_8390
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
r_int
id|reset_start_time
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|debug
OG
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Resetting the 8390 t=%ld...&quot;
comma
id|dev-&gt;name
comma
id|jiffies
)paren
suffix:semicolon
id|outb
c_func
(paren
id|inb
c_func
(paren
id|NE_BASE
op_plus
id|NE_RESET
)paren
comma
id|NE_BASE
op_plus
id|NE_RESET
)paren
suffix:semicolon
id|ei_status.txing
op_assign
l_int|0
suffix:semicolon
id|ei_status.dmaing
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* This check _should_not_ be necessary, omit eventually. */
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|NE_BASE
op_plus
id|EN0_ISR
)paren
op_amp
id|ENISR_RESET
)paren
op_eq
l_int|0
)paren
r_if
c_cond
(paren
id|jiffies
op_minus
id|reset_start_time
OG
l_int|2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: ne2k_pci_reset_8390() did not complete.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|outb
c_func
(paren
id|ENISR_RESET
comma
id|NE_BASE
op_plus
id|EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* Ack intr. */
)brace
multiline_comment|/* Grab the 8390 specific header. Similar to the block_input routine, but&n;   we don&squot;t need to be concerned with ring wrap as the header will be at&n;   the start of a page, so we optimize accordingly. */
r_static
r_void
DECL|function|ne2k_pci_get_8390_hdr
id|ne2k_pci_get_8390_hdr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|e8390_pkt_hdr
op_star
id|hdr
comma
r_int
id|ring_page
)paren
(brace
r_int
id|nic_base
op_assign
id|dev-&gt;base_addr
suffix:semicolon
multiline_comment|/* This *shouldn&squot;t* happen. If it does, it&squot;s the last thing you&squot;ll see */
r_if
c_cond
(paren
id|ei_status.dmaing
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: DMAing conflict in ne2k_pci_get_8390_hdr &quot;
l_string|&quot;[DMAstat:%d][irqlock:%d].&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ei_status.dmaing
comma
id|ei_status.irqlock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ei_status.dmaing
op_or_assign
l_int|0x01
suffix:semicolon
id|outb
c_func
(paren
id|E8390_NODMA
op_plus
id|E8390_PAGE0
op_plus
id|E8390_START
comma
id|nic_base
op_plus
id|NE_CMD
)paren
suffix:semicolon
id|outb
c_func
(paren
r_sizeof
(paren
r_struct
id|e8390_pkt_hdr
)paren
comma
id|nic_base
op_plus
id|EN0_RCNTLO
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|nic_base
op_plus
id|EN0_RCNTHI
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|nic_base
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
multiline_comment|/* On page boundary */
id|outb
c_func
(paren
id|ring_page
comma
id|nic_base
op_plus
id|EN0_RSARHI
)paren
suffix:semicolon
id|outb
c_func
(paren
id|E8390_RREAD
op_plus
id|E8390_START
comma
id|nic_base
op_plus
id|NE_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.ne2k_flags
op_amp
id|ONLY_16BIT_IO
)paren
(brace
id|insw
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
comma
id|hdr
comma
r_sizeof
(paren
r_struct
id|e8390_pkt_hdr
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
op_star
(paren
id|u32
op_star
)paren
id|hdr
op_assign
id|le32_to_cpu
c_func
(paren
id|inl
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
)paren
)paren
suffix:semicolon
id|le16_to_cpus
c_func
(paren
op_amp
id|hdr-&gt;count
)paren
suffix:semicolon
)brace
id|outb
c_func
(paren
id|ENISR_RDC
comma
id|nic_base
op_plus
id|EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* Ack intr. */
id|ei_status.dmaing
op_and_assign
op_complement
l_int|0x01
suffix:semicolon
)brace
multiline_comment|/* Block input and output, similar to the Crynwr packet driver.  If you&n;   are porting to a new ethercard, look at the packet driver source for hints.&n;   The NEx000 doesn&squot;t share the on-board packet memory -- you have to put&n;   the packet out through the &quot;remote DMA&quot; dataport using outb. */
r_static
r_void
DECL|function|ne2k_pci_block_input
id|ne2k_pci_block_input
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|ring_offset
)paren
(brace
r_int
id|nic_base
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|skb-&gt;data
suffix:semicolon
multiline_comment|/* This *shouldn&squot;t* happen. If it does, it&squot;s the last thing you&squot;ll see */
r_if
c_cond
(paren
id|ei_status.dmaing
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: DMAing conflict in ne2k_pci_block_input &quot;
l_string|&quot;[DMAstat:%d][irqlock:%d].&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ei_status.dmaing
comma
id|ei_status.irqlock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ei_status.dmaing
op_or_assign
l_int|0x01
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.ne2k_flags
op_amp
id|ONLY_32BIT_IO
)paren
id|count
op_assign
(paren
id|count
op_plus
l_int|3
)paren
op_amp
l_int|0xFFFC
suffix:semicolon
id|outb
c_func
(paren
id|E8390_NODMA
op_plus
id|E8390_PAGE0
op_plus
id|E8390_START
comma
id|nic_base
op_plus
id|NE_CMD
)paren
suffix:semicolon
id|outb
c_func
(paren
id|count
op_amp
l_int|0xff
comma
id|nic_base
op_plus
id|EN0_RCNTLO
)paren
suffix:semicolon
id|outb
c_func
(paren
id|count
op_rshift
l_int|8
comma
id|nic_base
op_plus
id|EN0_RCNTHI
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ring_offset
op_amp
l_int|0xff
comma
id|nic_base
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ring_offset
op_rshift
l_int|8
comma
id|nic_base
op_plus
id|EN0_RSARHI
)paren
suffix:semicolon
id|outb
c_func
(paren
id|E8390_RREAD
op_plus
id|E8390_START
comma
id|nic_base
op_plus
id|NE_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.ne2k_flags
op_amp
id|ONLY_16BIT_IO
)paren
(brace
id|insw
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
comma
id|buf
comma
id|count
op_rshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_amp
l_int|0x01
)paren
(brace
id|buf
(braket
id|count
op_minus
l_int|1
)braket
op_assign
id|inb
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|insl
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
comma
id|buf
comma
id|count
op_rshift
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_amp
l_int|3
)paren
(brace
id|buf
op_add_assign
id|count
op_amp
op_complement
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|count
op_amp
l_int|2
)paren
op_star
(paren
(paren
id|u16
op_star
)paren
id|buf
)paren
op_increment
op_assign
id|le16_to_cpu
c_func
(paren
id|inw
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_amp
l_int|1
)paren
op_star
id|buf
op_assign
id|inb
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
)paren
suffix:semicolon
)brace
)brace
id|outb
c_func
(paren
id|ENISR_RDC
comma
id|nic_base
op_plus
id|EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* Ack intr. */
id|ei_status.dmaing
op_and_assign
op_complement
l_int|0x01
suffix:semicolon
)brace
r_static
r_void
DECL|function|ne2k_pci_block_output
id|ne2k_pci_block_output
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_const
r_int
id|start_page
)paren
(brace
r_int
id|nic_base
op_assign
id|NE_BASE
suffix:semicolon
r_int
r_int
id|dma_start
suffix:semicolon
multiline_comment|/* On little-endian it&squot;s always safe to round the count up for&n;&t;   word writes. */
r_if
c_cond
(paren
id|ei_status.ne2k_flags
op_amp
id|ONLY_32BIT_IO
)paren
id|count
op_assign
(paren
id|count
op_plus
l_int|3
)paren
op_amp
l_int|0xFFFC
suffix:semicolon
r_else
r_if
c_cond
(paren
id|count
op_amp
l_int|0x01
)paren
id|count
op_increment
suffix:semicolon
multiline_comment|/* This *shouldn&squot;t* happen. If it does, it&squot;s the last thing you&squot;ll see */
r_if
c_cond
(paren
id|ei_status.dmaing
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: DMAing conflict in ne2k_pci_block_output.&quot;
l_string|&quot;[DMAstat:%d][irqlock:%d]&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ei_status.dmaing
comma
id|ei_status.irqlock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ei_status.dmaing
op_or_assign
l_int|0x01
suffix:semicolon
multiline_comment|/* We should already be in page 0, but to be safe... */
id|outb
c_func
(paren
id|E8390_PAGE0
op_plus
id|E8390_START
op_plus
id|E8390_NODMA
comma
id|nic_base
op_plus
id|NE_CMD
)paren
suffix:semicolon
macro_line|#ifdef NE8390_RW_BUGFIX
multiline_comment|/* Handle the read-before-write bug the same way as the&n;&t;   Crynwr packet driver -- the NatSemi method doesn&squot;t work.&n;&t;   Actually this doesn&squot;t always work either, but if you have&n;&t;   problems with your NEx000 this is better than nothing! */
id|outb
c_func
(paren
l_int|0x42
comma
id|nic_base
op_plus
id|EN0_RCNTLO
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|nic_base
op_plus
id|EN0_RCNTHI
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x42
comma
id|nic_base
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|nic_base
op_plus
id|EN0_RSARHI
)paren
suffix:semicolon
id|outb
c_func
(paren
id|E8390_RREAD
op_plus
id|E8390_START
comma
id|nic_base
op_plus
id|NE_CMD
)paren
suffix:semicolon
macro_line|#endif
id|outb
c_func
(paren
id|ENISR_RDC
comma
id|nic_base
op_plus
id|EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* Now the normal output. */
id|outb
c_func
(paren
id|count
op_amp
l_int|0xff
comma
id|nic_base
op_plus
id|EN0_RCNTLO
)paren
suffix:semicolon
id|outb
c_func
(paren
id|count
op_rshift
l_int|8
comma
id|nic_base
op_plus
id|EN0_RCNTHI
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|nic_base
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
id|outb
c_func
(paren
id|start_page
comma
id|nic_base
op_plus
id|EN0_RSARHI
)paren
suffix:semicolon
id|outb
c_func
(paren
id|E8390_RWRITE
op_plus
id|E8390_START
comma
id|nic_base
op_plus
id|NE_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.ne2k_flags
op_amp
id|ONLY_16BIT_IO
)paren
(brace
id|outsw
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
comma
id|buf
comma
id|count
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|outsl
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
comma
id|buf
comma
id|count
op_rshift
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_amp
l_int|3
)paren
(brace
id|buf
op_add_assign
id|count
op_amp
op_complement
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|count
op_amp
l_int|2
)paren
id|outw
c_func
(paren
id|cpu_to_le16
c_func
(paren
op_star
(paren
(paren
id|u16
op_star
)paren
id|buf
)paren
op_increment
)paren
comma
id|NE_BASE
op_plus
id|NE_DATAPORT
)paren
suffix:semicolon
)brace
)brace
id|dma_start
op_assign
id|jiffies
suffix:semicolon
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|nic_base
op_plus
id|EN0_ISR
)paren
op_amp
id|ENISR_RDC
)paren
op_eq
l_int|0
)paren
r_if
c_cond
(paren
id|jiffies
op_minus
id|dma_start
OG
l_int|2
)paren
(brace
multiline_comment|/* Avoid clock roll-over. */
id|printk
c_func
(paren
l_string|&quot;%s: timeout waiting for Tx RDC.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|ne2k_pci_reset_8390
c_func
(paren
id|dev
)paren
suffix:semicolon
id|NS8390_init
c_func
(paren
id|dev
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|outb
c_func
(paren
id|ENISR_RDC
comma
id|nic_base
op_plus
id|EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* Ack intr. */
id|ei_status.dmaing
op_and_assign
op_complement
l_int|0x01
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|ne2k_pci_remove_one
r_static
r_void
id|__devexit
id|ne2k_pci_remove_one
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|pdev-&gt;driver_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;bug! ne2k_pci_remove_one called w/o net_device&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|unregister_netdev
(paren
id|dev
)paren
suffix:semicolon
id|release_region
(paren
id|dev-&gt;base_addr
comma
id|NE_IO_EXTENT
)paren
suffix:semicolon
id|kfree
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|variable|ne2k_driver
r_static
r_struct
id|pci_driver
id|ne2k_driver
op_assign
(brace
id|name
suffix:colon
l_string|&quot;ne2k-pci&quot;
comma
id|probe
suffix:colon
id|ne2k_pci_init_one
comma
id|remove
suffix:colon
id|ne2k_pci_remove_one
comma
id|id_table
suffix:colon
id|ne2k_pci_tbl
comma
)brace
suffix:semicolon
DECL|function|ne2k_pci_init
r_static
r_int
id|__init
id|ne2k_pci_init
c_func
(paren
r_void
)paren
(brace
r_int
id|rc
suffix:semicolon
r_if
c_cond
(paren
id|load_8390_module
c_func
(paren
l_string|&quot;ne2k-pci.c&quot;
)paren
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
id|rc
op_assign
id|pci_module_init
(paren
op_amp
id|ne2k_driver
)paren
suffix:semicolon
multiline_comment|/* XXX should this test CONFIG_HOTPLUG like pci_module_init? */
multiline_comment|/* YYY No. If we&squot;re returning non-zero, we&squot;re being unloaded&n;&t; * &t;   immediately. dwmw2 &n;&t; */
r_if
c_cond
(paren
id|rc
op_le
l_int|0
)paren
id|unload_8390_module
c_func
(paren
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
DECL|function|ne2k_pci_cleanup
r_static
r_void
id|__exit
id|ne2k_pci_cleanup
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
(paren
op_amp
id|ne2k_driver
)paren
suffix:semicolon
id|unload_8390_module
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|ne2k_pci_init
id|module_init
c_func
(paren
id|ne2k_pci_init
)paren
suffix:semicolon
DECL|variable|ne2k_pci_cleanup
id|module_exit
c_func
(paren
id|ne2k_pci_cleanup
)paren
suffix:semicolon
"&f;"
multiline_comment|/*&n; * Local variables:&n; *  compile-command: &quot;gcc -DMODVERSIONS  -DMODULE -D__KERNEL__ -Wall -Wstrict-prototypes -O6 -fomit-frame-pointer -I/usr/src/linux/drivers/net/ -c ne2k-pci.c&quot;&n; *  alt-compile-command: &quot;gcc -DMODULE -D__KERNEL__ -Wall -Wstrict-prototypes -O6 -fomit-frame-pointer -I/usr/src/linux/drivers/net/ -c ne2k-pci.c&quot;&n; *  c-indent-level: 4&n; *  c-basic-offset: 4&n; *  tab-width: 4&n; *  version-control: t&n; *  kept-new-versions: 5&n; * End:&n; */
eof
