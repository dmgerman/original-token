multiline_comment|/*-&n; * Copyright (C) 1994 by PJD Weichmann &amp; SWS Bern, Switzerland&n; *&n; * This software may be used and distributed according to the terms&n; * of the GNU Public License, incorporated herein by reference.&n; *&n; * Module         : sk_g16.c&n; *&n; * Version        : $Revision: 1.1 $&n; *&n; * Author         : Patrick J.D. Weichmann&n; *&n; * Date Created   : 94/05/26&n; * Last Updated   : $Date: 1994/06/30 16:25:15 $&n; *&n; * Description    : Schneider &amp; Koch G16 Ethernet Device Driver for&n; *                  Linux Kernel &gt;= 1.1.22&n; * Update History :&n; *&n;-*/
DECL|variable|rcsid
r_static
r_char
op_star
id|rcsid
op_assign
l_string|&quot;$Id: sk_g16.c,v 1.1 1994/06/30 16:25:15 root Exp $&quot;
suffix:semicolon
multiline_comment|/*&n; * The Schneider &amp; Koch (SK) G16 Network device driver is based&n; * on the &squot;ni6510&squot; driver from Michael Hipp which can be found at&n; * ftp://sunsite.unc.edu/pub/Linux/system/Network/drivers/nidrivers.tar.gz&n; * &n; * Sources: 1) ni6510.c by M. Hipp&n; *          2) depca.c  by D.C. Davies&n; *          3) skeleton.c by D. Becker&n; *          4) Am7990 Local Area Network Controller for Ethernet (LANCE),&n; *             AMD, Pub. #05698, June 1989&n; *&n; * Many Thanks for helping me to get things working to: &n; *                 &n; *                 A. Cox (A.Cox@swansea.ac.uk)&n; *                 M. Hipp (mhipp@student.uni-tuebingen.de)&n; *                 R. Bolz (Schneider &amp; Koch, Germany)&n; *&n; * See README.sk_g16 for details about limitations and bugs for the&n; * current version.&n; *&n; * To Do: &n; *        - Support of SK_G8 and other SK Network Cards.&n; *        - Autoset memory mapped RAM. Check for free memory and then&n; *          configure RAM correctly. &n; *        - SK_close should really set card in to initial state.&n; *        - Test if IRQ 3 is not switched off. Use autoirq() functionality.&n; *          (as in /drivers/net/skeleton.c)&n; *        - Implement Multicast addressing. At minimum something like&n; *          in depca.c. &n; *        - Redo the statistics part.&n; *        - Try to find out if the board is in 8 Bit or 16 Bit slot.&n; *          If in 8 Bit mode don&squot;t use IRQ 11.&n; *        - (Try to make it slightly faster.) &n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/string.h&gt; 
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bitops.h&gt; 
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &quot;sk_g16.h&quot;
multiline_comment|/* &n; * Schneider &amp; Koch Card Definitions &n; * =================================&n; */
DECL|macro|SK_NAME
mdefine_line|#define SK_NAME   &quot;SK_G16&quot;
multiline_comment|/*&n; * SK_G16 Configuration&n; * --------------------&n; */
multiline_comment|/* &n; * Abbreviations&n; * -------------&n; *  &n; * RAM - used for the 16KB shared memory &n; * Boot_ROM, ROM - are used for referencing the BootEPROM&n; *&n; * SK_BOOT_ROM and SK_ADDR are symbolic constants used to configure&n; * the behaviour of the driver and the SK_G16.&n; *&n; * ! See sk_g16.install on how to install and configure the driver !   &n; *&n; * SK_BOOT_ROM defines if the Boot_ROM should be switched off or not.&n; *&n; * SK_ADDR defines the address where the RAM will be mapped into the real&n; *         host memory.&n; *         valid addresses are from 0xa0000 to 0xfc000 in 16Kbyte steps.&n; */
DECL|macro|SK_BOOT_ROM
mdefine_line|#define SK_BOOT_ROM     1              /* 1=BootROM on 0=off */
DECL|macro|SK_ADDR
mdefine_line|#define SK_ADDR         0xcc000
multiline_comment|/* &n; * In POS3 are bits A14-A19 of the address bus. These bits can be set&n; * to choose the RAM address. Thats why we only can choose the RAM address&n; * in 16KB steps.&n; */
DECL|macro|POS_ADDR
mdefine_line|#define POS_ADDR       (rom_addr&gt;&gt;14)  /* Do not change this line */
multiline_comment|/* &n; * SK_G16 I/O PORT&squot;s + IRQ&squot;s + Boot_ROM locations&n; * ----------------------------------------------&n; */
multiline_comment|/* &n; * As nearly every card has also SK_G16 a specified I/O Port region and&n; * only a few possible IRQ&squot;s.&n; * In the Installation Guide from Schneider &amp; Koch is listed a possible&n; * Interrupt IRQ2. IRQ2 is always IRQ9 in boards with two cascaded interrupt&n; * controllers. So we use in SK_IRQS IRQ9.&n; */
multiline_comment|/* Don&squot;t touch any of the following #defines. */
DECL|macro|SK_IO_PORTS
mdefine_line|#define SK_IO_PORTS     { 0x100, 0x180, 0x208, 0x220, 0x288, 0x320, 0x328, 0x390, 0 }
DECL|macro|SK_IRQS
mdefine_line|#define SK_IRQS         { 3, 5, 9, 11, 0 }
DECL|macro|SK_BOOT_ROM_LOCATIONS
mdefine_line|#define SK_BOOT_ROM_LOCATIONS { 0xc0000, 0xc4000, 0xc8000, 0xcc000, 0xd0000, 0xd4000, 0xd8000, 0xdc000, 0 }
DECL|macro|SK_BOOT_ROM_ID
mdefine_line|#define SK_BOOT_ROM_ID  { 0x55, 0xaa, 0x10, 0x50, 0x06, 0x33 }
multiline_comment|/* &n; * SK_G16 POS REGISTERS &n; * --------------------&n; */
multiline_comment|/*&n; * SK_G16 has a Programmable Option Select (POS) Register.&n; * The POS is composed of 8 separate registers (POS0-7) which &n; * are I/O mapped on an address set by the W1 switch.                    &n; *&n; */
DECL|macro|SK_POS_SIZE
mdefine_line|#define SK_POS_SIZE 8           /* 8 I/O Ports are used by SK_G16 */
DECL|macro|SK_POS0
mdefine_line|#define SK_POS0     ioaddr      /* Card-ID Low (R) */
DECL|macro|SK_POS1
mdefine_line|#define SK_POS1     ioaddr+1    /* Card-ID High (R) */
DECL|macro|SK_POS2
mdefine_line|#define SK_POS2     ioaddr+2    /* Card-Enable, Boot-ROM Disable (RW) */
DECL|macro|SK_POS3
mdefine_line|#define SK_POS3     ioaddr+3    /* Base address of RAM */
DECL|macro|SK_POS4
mdefine_line|#define SK_POS4     ioaddr+4    /* IRQ */
multiline_comment|/* POS5 - POS7 are unused */
multiline_comment|/* &n; * SK_G16 MAC PREFIX &n; * -----------------&n; */
multiline_comment|/* &n; * Scheider &amp; Koch manufacturer code (00:00:a5).&n; * This must be checked, that we are sure it is a SK card.&n; */
DECL|macro|SK_MAC0
mdefine_line|#define SK_MAC0         0x00
DECL|macro|SK_MAC1
mdefine_line|#define SK_MAC1         0x00
DECL|macro|SK_MAC2
mdefine_line|#define SK_MAC2         0x5a
multiline_comment|/* &n; * SK_G16 ID &n; * ---------&n; */
multiline_comment|/* &n; * If POS0,POS1 contain the following ID, then we know&n; * at which I/O Port Address we are. &n; */
DECL|macro|SK_IDLOW
mdefine_line|#define SK_IDLOW  0xfd 
DECL|macro|SK_IDHIGH
mdefine_line|#define SK_IDHIGH 0x6a
multiline_comment|/* &n; * LANCE POS Bit definitions &n; * -------------------------&n; */
DECL|macro|SK_ROM_RAM_ON
mdefine_line|#define SK_ROM_RAM_ON  (POS2_CARD)
DECL|macro|SK_ROM_RAM_OFF
mdefine_line|#define SK_ROM_RAM_OFF (POS2_EPROM)
DECL|macro|SK_ROM_ON
mdefine_line|#define SK_ROM_ON      (inb(SK_POS2) &amp; POS2_CARD)
DECL|macro|SK_ROM_OFF
mdefine_line|#define SK_ROM_OFF     (inb(SK_POS2) | POS2_EPROM)
DECL|macro|SK_RAM_ON
mdefine_line|#define SK_RAM_ON      (inb(SK_POS2) | POS2_CARD)
DECL|macro|SK_RAM_OFF
mdefine_line|#define SK_RAM_OFF     (inb(SK_POS2) &amp; POS2_EPROM) 
DECL|macro|POS2_CARD
mdefine_line|#define POS2_CARD  0x0001              /* 1 = SK_G16 on      0 = off */
DECL|macro|POS2_EPROM
mdefine_line|#define POS2_EPROM 0x0002              /* 1 = Boot EPROM off 0 = on */ 
multiline_comment|/* &n; * SK_G16 Memory mapped Registers&n; * ------------------------------&n; *&n; */
DECL|macro|SK_IOREG
mdefine_line|#define SK_IOREG        (board-&gt;ioreg) /* LANCE data registers.     */ 
DECL|macro|SK_PORT
mdefine_line|#define SK_PORT         (board-&gt;port)  /* Control, Status register  */
DECL|macro|SK_IOCOM
mdefine_line|#define SK_IOCOM        (board-&gt;iocom) /* I/O Command               */
multiline_comment|/* &n; * SK_G16 Status/Control Register bits&n; * -----------------------------------&n; *&n; * (C) Controlreg (S) Statusreg &n; */
multiline_comment|/* &n; * Register transfer: 0 = no transfer&n; *                    1 = transferring data between LANCE and I/O reg &n; */
DECL|macro|SK_IORUN
mdefine_line|#define SK_IORUN        0x20   
multiline_comment|/* &n; * LANCE interrupt: 0 = LANCE interrupt occurred&t;&n; *                  1 = no LANCE interrupt occurred&n; */
DECL|macro|SK_IRQ
mdefine_line|#define SK_IRQ          0x10   
DECL|macro|SK_RESET
mdefine_line|#define SK_RESET        0x08   /* Reset SK_CARD: 0 = RESET 1 = normal */
DECL|macro|SK_RW
mdefine_line|#define SK_RW           0x02   /* 0 = write to 1 = read from */
DECL|macro|SK_ADR
mdefine_line|#define SK_ADR          0x01   /* 0 = REG DataPort 1 = RAP Reg addr port */
DECL|macro|SK_RREG
mdefine_line|#define SK_RREG         SK_RW  /* Transferdirection to read from lance */
DECL|macro|SK_WREG
mdefine_line|#define SK_WREG         0      /* Transferdirection to write to lance */
DECL|macro|SK_RAP
mdefine_line|#define SK_RAP          SK_ADR /* Destination Register RAP */
DECL|macro|SK_RDATA
mdefine_line|#define SK_RDATA        0      /* Destination Register REG DataPort */
multiline_comment|/* &n; * SK_G16 I/O Command &n; * ------------------&n; */
multiline_comment|/* &n; * Any bitcombination sets the internal I/O bit (transfer will start) &n; * when written to I/O Command&n; */
DECL|macro|SK_DOIO
mdefine_line|#define SK_DOIO         0x80   /* Do Transfer */ 
multiline_comment|/* &n; * LANCE RAP (Register Address Port). &n; * ---------------------------------&n; */
multiline_comment|/*   &n; * The LANCE internal registers are selected through the RAP. &n; * The Registers are:&n; *&n; * CSR0 - Status and Control flags &n; * CSR1 - Low order bits of initialize block (bits 15:00)&n; * CSR2 - High order bits of initialize block (bits 07:00, 15:08 are reserved)&n; * CSR3 - Allows redefinition of the Bus Master Interface.&n; *        This register must be set to 0x0002, which means BSWAP = 0,&n; *        ACON = 1, BCON = 0;&n; *&n; */
DECL|macro|CSR0
mdefine_line|#define CSR0            0x00   
DECL|macro|CSR1
mdefine_line|#define CSR1            0x01  
DECL|macro|CSR2
mdefine_line|#define CSR2            0x02 
DECL|macro|CSR3
mdefine_line|#define CSR3            0x03
multiline_comment|/* &n; * General Definitions &n; * ===================&n; */
multiline_comment|/* &n; * Set the number of Tx and Rx buffers, using Log_2(# buffers).&n; * We have 16KB RAM which can be accessed by the LANCE. In the &n; * memory are not only the buffers but also the ring descriptors and&n; * the initialize block. &n; * Don&squot;t change anything unless you really know what you do.&n; */
DECL|macro|LC_LOG_TX_BUFFERS
mdefine_line|#define LC_LOG_TX_BUFFERS 1               /* (2 == 2^^1) 2 Transmit buffers */
DECL|macro|LC_LOG_RX_BUFFERS
mdefine_line|#define LC_LOG_RX_BUFFERS 3               /* (8 == 2^^3) 8 Receive buffers */
multiline_comment|/* Descriptor ring sizes */
DECL|macro|TMDNUM
mdefine_line|#define TMDNUM (1 &lt;&lt; (LC_LOG_TX_BUFFERS)) /* 2 Transmit descriptor rings */
DECL|macro|RMDNUM
mdefine_line|#define RMDNUM (1 &lt;&lt; (LC_LOG_RX_BUFFERS)) /* 8 Receive Buffers */
multiline_comment|/* Define Mask for setting RMD, TMD length in the LANCE init_block */
DECL|macro|TMDNUMMASK
mdefine_line|#define TMDNUMMASK (LC_LOG_TX_BUFFERS &lt;&lt; 29)
DECL|macro|RMDNUMMASK
mdefine_line|#define RMDNUMMASK (LC_LOG_RX_BUFFERS &lt;&lt; 29)
multiline_comment|/*&n; * Data Buffer size is set to maximum packet length.&n; */
DECL|macro|PKT_BUF_SZ
mdefine_line|#define PKT_BUF_SZ              1518 
multiline_comment|/* &n; * The number of low I/O ports used by the ethercard. &n; */
DECL|macro|ETHERCARD_TOTAL_SIZE
mdefine_line|#define ETHERCARD_TOTAL_SIZE    SK_POS_SIZE
multiline_comment|/* &n; * Portreserve is there to mark the Card I/O Port region as used. &n; * Check_region is to check if the region at ioaddr with the size &quot;size&quot; &n; * is free or not.&n; * Snarf_region allocates the I/O Port region.&n; */
macro_line|#ifndef HAVE_PORTRESERVE
DECL|macro|check_region
mdefine_line|#define check_region(ioaddr, size)              0
DECL|macro|snarf_region
mdefine_line|#define snarf_region(ioaddr, size);             do ; while (0)
macro_line|#endif
multiline_comment|/* &n; * SK_DEBUG&n; *&n; * Here you can choose what level of debugging wanted.&n; *&n; * If SK_DEBUG and SK_DEBUG2 are undefined, then only the&n; *  necessary messages will be printed.&n; *&n; * If SK_DEBUG is defined, there will be many debugging prints&n; *  which can help to find some mistakes in configuration or even&n; *  in the driver code.&n; *&n; * If SK_DEBUG2 is defined, many many messages will be printed &n; *  which normally you don&squot;t need. I used this to check the interrupt&n; *  routine. &n; *&n; * (If you define only SK_DEBUG2 then only the messages for &n; *  checking interrupts will be printed!)&n; *&n; * Normal way of live is: &n; *&n; * For the whole thing get going let both symbolic constants&n; * undefined. If you face any problems and you know what&squot;s going&n; * on (you know something about the card and you can interpret some&n; * hex LANCE register output) then define SK_DEBUG&n; * &n; */
DECL|macro|SK_DEBUG
macro_line|#undef  SK_DEBUG&t;/* debugging */
DECL|macro|SK_DEBUG2
macro_line|#undef  SK_DEBUG2&t;/* debugging with more verbose report */
macro_line|#ifdef SK_DEBUG
DECL|macro|PRINTK
mdefine_line|#define PRINTK(x) printk x
macro_line|#else
DECL|macro|PRINTK
mdefine_line|#define PRINTK(x) /**/
macro_line|#endif
macro_line|#ifdef SK_DEBUG2
DECL|macro|PRINTK2
mdefine_line|#define PRINTK2(x) printk x
macro_line|#else
DECL|macro|PRINTK2
mdefine_line|#define PRINTK2(x) /**/
macro_line|#endif
multiline_comment|/* &n; * SK_G16 RAM&n; *&n; * The components are memory mapped and can be set in a region from&n; * 0x00000 through 0xfc000 in 16KB steps. &n; *&n; * The Network components are: dual ported RAM, Prom, I/O Reg, Status-,&n; * Controlregister and I/O Command.&n; *&n; * dual ported RAM: This is the only memory region which the LANCE chip&n; *      has access to. From the Lance it is addressed from 0x0000 to&n; *      0x3fbf. The host accesses it normally.&n; *&n; * PROM: The PROM obtains the ETHERNET-MAC-Address. It is realised as a&n; *       8-Bit PROM, this means only the 16 even addresses are used of the&n; *       32 Byte Address region. Access to a odd address results in invalid&n; *       data.&n; * &n; * LANCE I/O Reg: The I/O Reg is build of 4 single Registers, Low-Byte Write,&n; *       Hi-Byte Write, Low-Byte Read, Hi-Byte Read.&n; *       Transfer from or to the LANCE is always in 16Bit so Low and High&n; *       registers are always relevant.&n; *&n; *       The Data from the Readregister is not the data in the Writeregister!!&n; *       &n; * Port: Status- and Controlregister. &n; *       Two different registers which share the same address, Status is &n; *       read-only, Control is write-only.&n; *    &n; * I/O Command: &n; *       Any bitcombination written in here starts the transmission between&n; *       Host and LANCE.&n; */
r_typedef
r_struct
(brace
DECL|member|ram
r_int
r_char
id|ram
(braket
l_int|0x3fc0
)braket
suffix:semicolon
multiline_comment|/* 16KB dual ported ram */
DECL|member|rom
r_int
r_char
id|rom
(braket
l_int|0x0020
)braket
suffix:semicolon
multiline_comment|/* 32Byte PROM containing 6Byte MAC */
DECL|member|res1
r_int
r_char
id|res1
(braket
l_int|0x0010
)braket
suffix:semicolon
multiline_comment|/* reserved */
DECL|member|ioreg
r_int
r_volatile
r_int
id|ioreg
suffix:semicolon
multiline_comment|/* LANCE I/O Register */
DECL|member|port
r_int
r_volatile
r_char
id|port
suffix:semicolon
multiline_comment|/* Statusregister and Controlregister */
DECL|member|iocom
r_int
r_char
id|iocom
suffix:semicolon
multiline_comment|/* I/O Command Register */
DECL|typedef|SK_RAM
)brace
id|SK_RAM
suffix:semicolon
multiline_comment|/* struct  */
multiline_comment|/* &n; * This is the structure for the dual ported ram. We&n; * have exactly 16 320 Bytes. In here there must be:&n; *&n; *     - Initialize Block   (starting at a word boundary)&n; *     - Receive and Transmit Descriptor Rings (quadword boundary)&n; *     - Data Buffers (arbitrary boundary)&n; *&n; * This is because LANCE has on SK_G16 only access to the dual ported&n; * RAM and nowhere else.&n; */
DECL|struct|SK_ram
r_struct
id|SK_ram
(brace
DECL|member|ib
r_struct
id|init_block
id|ib
suffix:semicolon
DECL|member|tmde
r_struct
id|tmd
id|tmde
(braket
id|TMDNUM
)braket
suffix:semicolon
DECL|member|rmde
r_struct
id|rmd
id|rmde
(braket
id|RMDNUM
)braket
suffix:semicolon
DECL|member|tmdbuf
r_char
id|tmdbuf
(braket
id|TMDNUM
)braket
(braket
id|PKT_BUF_SZ
)braket
suffix:semicolon
DECL|member|rmdbuf
r_char
id|rmdbuf
(braket
id|RMDNUM
)braket
(braket
id|PKT_BUF_SZ
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * Structure where all necessary information is for ring buffer &n; * management and statistics.&n; */
DECL|struct|priv
r_struct
id|priv
(brace
DECL|member|ram
r_struct
id|SK_ram
op_star
id|ram
suffix:semicolon
multiline_comment|/* dual ported ram structure */
DECL|member|rmdhead
r_struct
id|rmd
op_star
id|rmdhead
suffix:semicolon
multiline_comment|/* start of receive ring descriptors */
DECL|member|tmdhead
r_struct
id|tmd
op_star
id|tmdhead
suffix:semicolon
multiline_comment|/* start of transmit ring descriptors */
DECL|member|rmdnum
r_int
id|rmdnum
suffix:semicolon
multiline_comment|/* actual used ring descriptor */
DECL|member|tmdnum
r_int
id|tmdnum
suffix:semicolon
multiline_comment|/* actual transmit descriptor for transmitting data */
DECL|member|tmdlast
r_int
id|tmdlast
suffix:semicolon
multiline_comment|/* last sent descriptor used for error handling, etc */
DECL|member|rmdbufs
r_void
op_star
id|rmdbufs
(braket
id|RMDNUM
)braket
suffix:semicolon
multiline_comment|/* pointer to the receive buffers */
DECL|member|tmdbufs
r_void
op_star
id|tmdbufs
(braket
id|TMDNUM
)braket
suffix:semicolon
multiline_comment|/* pointer to the transmit buffers */
DECL|member|stats
r_struct
id|enet_statistics
id|stats
suffix:semicolon
multiline_comment|/* Device driver statistics */
)brace
suffix:semicolon
multiline_comment|/* global variable declaration */
multiline_comment|/* IRQ map used to reserve a IRQ (see SK_open()) */
r_extern
r_void
op_star
id|irq2dev_map
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* static variables */
DECL|variable|board
r_static
id|SK_RAM
op_star
id|board
suffix:semicolon
multiline_comment|/* pointer to our memory mapped board components */
multiline_comment|/* Macros */
"&f;"
multiline_comment|/* Function Prototypes */
multiline_comment|/*&n; * Device Driver functions&n; * -----------------------&n; * See for short explanation of each function its definitions header.&n; */
r_int
id|SK_init
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|SK_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|ioaddr
)paren
suffix:semicolon
r_static
r_int
id|SK_open
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|SK_send_packet
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|SK_interrupt
c_func
(paren
r_int
id|reg_ptr
)paren
suffix:semicolon
r_static
r_void
id|SK_rxintr
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|SK_txintr
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|SK_close
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_struct
id|enet_statistics
op_star
id|SK_get_stats
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_int
r_int
id|SK_rom_addr
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef HAVE_MULTICAST
r_static
r_void
id|set_multicast_list
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|num_addrs
comma
r_void
op_star
id|addrs
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * LANCE Functions&n; * ---------------&n; */
r_static
r_int
id|SK_lance_init
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|mode
)paren
suffix:semicolon
r_void
id|SK_reset_board
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|SK_set_RAP
c_func
(paren
r_int
id|reg_number
)paren
suffix:semicolon
r_int
id|SK_read_reg
c_func
(paren
r_int
id|reg_number
)paren
suffix:semicolon
r_int
id|SK_rread_reg
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|SK_write_reg
c_func
(paren
r_int
id|reg_number
comma
r_int
id|value
)paren
suffix:semicolon
multiline_comment|/* &n; * Debugging functions&n; * -------------------&n; */
r_void
id|SK_print_pos
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|text
)paren
suffix:semicolon
r_void
id|SK_print_dev
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|text
)paren
suffix:semicolon
r_void
id|SK_print_ram
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
"&f;"
multiline_comment|/*-&n; * Function       : SK_init&n; * Author         : Patrick J.D. Weichmann&n; * Date Created   : 94/05/26&n; *&n; * Description    : Check for a SK_G16 network adaptor and initialize it.&n; *                  This function gets called by dev_init which initializes&n; *                  all Network devices.&n; *&n; * Parameters     : I : struct device *dev - structure preconfigured &n; *                                           from Space.c&n; * Return Value   : 0 = Driver Found and initialized &n; * Errors         : ENODEV - no device found&n; *                  ENXIO  - not probed&n; * Globals        : None&n; * Update History :&n; *     YY/MM/DD  uid  Description&n;-*/
multiline_comment|/* &n; * Check for a network adaptor of this type, and return &squot;0&squot; if one exists.&n; * If dev-&gt;base_addr == 0, probe all likely locations.&n; * If dev-&gt;base_addr == 1, always return failure.&n; * If dev-&gt;base_addr == 2, allocate space for the device and return success&n; *                         (detachable devices only).&n; */
DECL|function|SK_init
r_int
id|SK_init
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|ioaddr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* I/O port address used for POS regs */
r_int
op_star
id|port
comma
id|ports
(braket
)braket
op_assign
id|SK_IO_PORTS
suffix:semicolon
multiline_comment|/* SK_G16 supported ports */
multiline_comment|/* get preconfigured base_addr from dev which is done in Space.c */
r_int
id|base_addr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|PRINTK
c_func
(paren
(paren
l_string|&quot;%s: %s&quot;
comma
id|SK_NAME
comma
id|rcsid
)paren
)paren
suffix:semicolon
id|rcsid
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* We do not want to use this further */
r_if
c_cond
(paren
id|base_addr
OG
l_int|0x0ff
)paren
multiline_comment|/* Check a single specified address */
(brace
multiline_comment|/* Check if on specified address is a SK_G16 */
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|SK_POS0
)paren
op_eq
id|SK_IDLOW
)paren
op_logical_or
(paren
id|inb
c_func
(paren
id|SK_POS1
)paren
op_eq
id|SK_IDHIGH
)paren
)paren
(brace
r_return
id|SK_probe
c_func
(paren
id|dev
comma
id|base_addr
)paren
suffix:semicolon
)brace
r_return
id|ENODEV
suffix:semicolon
multiline_comment|/* Sorry, but on specified address NO SK_G16 */
)brace
r_else
r_if
c_cond
(paren
id|base_addr
OG
l_int|0
)paren
multiline_comment|/* Don&squot;t probe at all */
(brace
r_return
id|ENXIO
suffix:semicolon
)brace
multiline_comment|/* Autoprobe base_addr */
r_for
c_loop
(paren
id|port
op_assign
op_amp
id|ports
(braket
l_int|0
)braket
suffix:semicolon
op_star
id|port
suffix:semicolon
id|port
op_increment
)paren
(brace
id|ioaddr
op_assign
op_star
id|port
suffix:semicolon
multiline_comment|/* we need ioaddr for accessing POS regs */
multiline_comment|/* Check if I/O Port region is used by another board */
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|ioaddr
comma
id|ETHERCARD_TOTAL_SIZE
)paren
)paren
(brace
r_continue
suffix:semicolon
multiline_comment|/* Try next Port address */
)brace
multiline_comment|/* Check if at ioaddr is a SK_G16 */
r_if
c_cond
(paren
op_logical_neg
(paren
id|inb
c_func
(paren
id|SK_POS0
)paren
op_eq
id|SK_IDLOW
)paren
op_logical_or
op_logical_neg
(paren
id|inb
c_func
(paren
id|SK_POS1
)paren
op_eq
id|SK_IDHIGH
)paren
)paren
(brace
r_continue
suffix:semicolon
multiline_comment|/* Try next Port address */
)brace
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
multiline_comment|/* Set I/O Port Address */
r_if
c_cond
(paren
id|SK_probe
c_func
(paren
id|dev
comma
id|ioaddr
)paren
op_eq
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Card found and initialized */
)brace
)brace
id|dev-&gt;base_addr
op_assign
id|base_addr
suffix:semicolon
multiline_comment|/* Write back original base_addr */
r_return
id|ENODEV
suffix:semicolon
multiline_comment|/* Failed to find or init driver */
)brace
multiline_comment|/* End of SK_init */
"&f;"
multiline_comment|/*-&n; * Function       : SK_probe&n; * Author         : Patrick J.D. Weichmann&n; * Date Created   : 94/05/26&n; *&n; * Description    : This function is called by SK_init and &n; *                  does the main part of initialization.&n; *                  &n; * Parameters     : I : struct device *dev - SK_G16 device structure&n; *                  I : short ioaddr       - I/O Port address where POS is.&n; * Return Value   : 0 = Initialization done             &n; * Errors         : ENODEV - No SK_G16 found&n; *                  -1     - Configuration problem&n; * Globals        : irq2dev_map - Which device uses which IRQ&n; *                : board       - pointer to SK_RAM&n; * Update History :&n; *     YY/MM/DD  uid  Description&n; *     94/06/30  pwe  SK_ADDR now checked and at the correct place&n;-*/
DECL|function|SK_probe
r_int
id|SK_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|ioaddr
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
multiline_comment|/* Counters */
r_int
id|sk_addr_flag
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* SK ADDR correct? 1 - no, 0 - yes */
r_int
r_int
id|rom_addr
suffix:semicolon
multiline_comment|/* used to store RAM address used for POS_ADDR */
r_struct
id|priv
op_star
id|p
suffix:semicolon
multiline_comment|/* SK_G16 private structure */
r_if
c_cond
(paren
id|SK_ADDR
op_amp
l_int|0x3fff
op_logical_or
id|SK_ADDR
OL
l_int|0xa0000
)paren
(brace
id|sk_addr_flag
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* &n;        * Now here we could use a routine which searches for a free&n;        * place in the ram and set SK_ADDR if found. TODO. &n;        */
)brace
r_if
c_cond
(paren
id|SK_BOOT_ROM
)paren
multiline_comment|/* Shall we keep Boot_ROM on ? */
(brace
id|PRINTK
c_func
(paren
(paren
l_string|&quot;## %s: SK_BOOT_ROM is set.&bslash;n&quot;
comma
id|SK_NAME
)paren
)paren
suffix:semicolon
id|rom_addr
op_assign
id|SK_rom_addr
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rom_addr
op_eq
l_int|0
)paren
multiline_comment|/* No Boot_ROM found */
(brace
r_if
c_cond
(paren
id|sk_addr_flag
)paren
multiline_comment|/* No or Invalid SK_ADDR is defined */
(brace
id|printk
c_func
(paren
l_string|&quot;%s: SK_ADDR %#08x is not valid. Check configuration.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|SK_ADDR
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|rom_addr
op_assign
id|SK_ADDR
suffix:semicolon
multiline_comment|/* assign predefined address */
id|PRINTK
c_func
(paren
(paren
l_string|&quot;## %s: NO Bootrom found &bslash;n&quot;
comma
id|SK_NAME
)paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|SK_ROM_RAM_OFF
comma
id|SK_POS2
)paren
suffix:semicolon
multiline_comment|/* Boot_ROM + RAM off */
id|outb
c_func
(paren
id|POS_ADDR
comma
id|SK_POS3
)paren
suffix:semicolon
multiline_comment|/* Set RAM address */
id|outb
c_func
(paren
id|SK_RAM_ON
comma
id|SK_POS2
)paren
suffix:semicolon
multiline_comment|/* enable RAM */
)brace
r_else
r_if
c_cond
(paren
id|rom_addr
op_eq
id|SK_ADDR
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: RAM + ROM are set to the same address %#08x&bslash;n&quot;
l_string|&quot;   Check configuration. Now switching off Boot_ROM&bslash;n&quot;
comma
id|SK_NAME
comma
id|rom_addr
)paren
suffix:semicolon
id|outb
c_func
(paren
id|SK_ROM_RAM_OFF
comma
id|SK_POS2
)paren
suffix:semicolon
multiline_comment|/* Boot_ROM + RAM off*/
id|outb
c_func
(paren
id|POS_ADDR
comma
id|SK_POS3
)paren
suffix:semicolon
multiline_comment|/* Set RAM address */
id|outb
c_func
(paren
id|SK_RAM_ON
comma
id|SK_POS2
)paren
suffix:semicolon
multiline_comment|/* enable RAM */
)brace
r_else
(brace
id|PRINTK
c_func
(paren
(paren
l_string|&quot;## %s: Found ROM at %#08x&bslash;n&quot;
comma
id|SK_NAME
comma
id|rom_addr
)paren
)paren
suffix:semicolon
id|PRINTK
c_func
(paren
(paren
l_string|&quot;## %s: Keeping Boot_ROM on&bslash;n&quot;
comma
id|SK_NAME
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk_addr_flag
)paren
multiline_comment|/* No or Invalid SK_ADDR is defined */
(brace
id|printk
c_func
(paren
l_string|&quot;%s: SK_ADDR %#08x is not valid. Check configuration.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|SK_ADDR
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|rom_addr
op_assign
id|SK_ADDR
suffix:semicolon
id|outb
c_func
(paren
id|SK_ROM_RAM_OFF
comma
id|SK_POS2
)paren
suffix:semicolon
multiline_comment|/* Boot_ROM + RAM off */
id|outb
c_func
(paren
id|POS_ADDR
comma
id|SK_POS3
)paren
suffix:semicolon
multiline_comment|/* Set RAM address */
id|outb
c_func
(paren
id|SK_ROM_RAM_ON
comma
id|SK_POS2
)paren
suffix:semicolon
multiline_comment|/* RAM on, BOOT_ROM on */
)brace
)brace
r_else
multiline_comment|/* Don&squot;t keep Boot_ROM */
(brace
id|PRINTK
c_func
(paren
(paren
l_string|&quot;## %s: SK_BOOT_ROM is not set.&bslash;n&quot;
comma
id|SK_NAME
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sk_addr_flag
)paren
multiline_comment|/* No or Invalid SK_ADDR is defined */
(brace
id|printk
c_func
(paren
l_string|&quot;%s: SK_ADDR %#08x is not valid. Check configuration.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|SK_ADDR
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|rom_addr
op_assign
id|SK_rom_addr
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Try to find a Boot_ROM */
multiline_comment|/* IF we find a Boot_ROM disable it */
id|outb
c_func
(paren
id|SK_ROM_RAM_OFF
comma
id|SK_POS2
)paren
suffix:semicolon
multiline_comment|/* Boot_ROM + RAM off */
multiline_comment|/* We found a Boot_ROM and its gone. Set RAM address on&n;         * Boot_ROM address. &n;         */
r_if
c_cond
(paren
id|rom_addr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: We found Boot_ROM at %#08x. Now setting RAM on&quot;
l_string|&quot;that address&bslash;n&quot;
comma
id|SK_NAME
comma
id|rom_addr
)paren
suffix:semicolon
id|outb
c_func
(paren
id|POS_ADDR
comma
id|SK_POS3
)paren
suffix:semicolon
multiline_comment|/* Set RAM on Boot_ROM address */
)brace
r_else
multiline_comment|/* We did not find a Boot_ROM, use predefined SK_ADDR for ram */
(brace
r_if
c_cond
(paren
id|sk_addr_flag
)paren
multiline_comment|/* No or Invalid SK_ADDR is defined */
(brace
id|printk
c_func
(paren
l_string|&quot;%s: SK_ADDR %#08x is not valid. Check configuration.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|SK_ADDR
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|rom_addr
op_assign
id|SK_ADDR
suffix:semicolon
id|outb
c_func
(paren
id|POS_ADDR
comma
id|SK_POS3
)paren
suffix:semicolon
multiline_comment|/* Set RAM address */
)brace
id|outb
c_func
(paren
id|SK_RAM_ON
comma
id|SK_POS2
)paren
suffix:semicolon
multiline_comment|/* enable RAM */
)brace
macro_line|#ifdef SK_DEBUG
id|SK_print_pos
c_func
(paren
id|dev
comma
l_string|&quot;POS registers after ROM, RAM config&quot;
)paren
suffix:semicolon
macro_line|#endif
id|board
op_assign
(paren
id|SK_RAM
op_star
)paren
id|rom_addr
suffix:semicolon
multiline_comment|/* Read in station address */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|j
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ETH_ALEN
suffix:semicolon
id|i
op_increment
comma
id|j
op_add_assign
l_int|2
)paren
(brace
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
id|board-&gt;rom
(braket
id|j
)braket
suffix:semicolon
)brace
multiline_comment|/* Check for manufacturer code */
r_if
c_cond
(paren
op_logical_neg
(paren
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
op_eq
id|SK_MAC0
op_logical_and
id|dev-&gt;dev_addr
(braket
l_int|1
)braket
op_eq
id|SK_MAC1
op_logical_and
id|dev-&gt;dev_addr
(braket
l_int|2
)braket
op_eq
id|SK_MAC2
)paren
)paren
(brace
id|PRINTK
c_func
(paren
(paren
l_string|&quot;## %s: We did not find SK_G16 at RAM location.&bslash;n&quot;
comma
id|SK_NAME
)paren
)paren
suffix:semicolon
r_return
id|ENODEV
suffix:semicolon
multiline_comment|/* NO SK_G16 found */
)brace
id|printk
c_func
(paren
l_string|&quot;%s: %s found at %#3x, HW addr: %#04x:%02x:%02x:%02x:%02x:%02x&bslash;n&quot;
comma
id|dev-&gt;name
comma
l_string|&quot;Schneider &amp; Koch Netcard&quot;
comma
(paren
r_int
r_int
)paren
id|dev-&gt;base_addr
comma
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
comma
id|dev-&gt;dev_addr
(braket
l_int|1
)braket
comma
id|dev-&gt;dev_addr
(braket
l_int|2
)braket
comma
id|dev-&gt;dev_addr
(braket
l_int|3
)braket
comma
id|dev-&gt;dev_addr
(braket
l_int|4
)braket
comma
id|dev-&gt;dev_addr
(braket
l_int|5
)braket
)paren
suffix:semicolon
multiline_comment|/* Grab the I/O Port region */
id|snarf_region
c_func
(paren
id|ioaddr
comma
id|ETHERCARD_TOTAL_SIZE
)paren
suffix:semicolon
multiline_comment|/* Initialize device structure */
multiline_comment|/* Allocate memory for private structure */
id|p
op_assign
id|dev-&gt;priv
op_assign
(paren
r_void
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|priv
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
id|dev-&gt;priv
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|priv
)paren
)paren
suffix:semicolon
multiline_comment|/* clear memory */
multiline_comment|/* Assign our Device Driver functions */
id|dev-&gt;open
op_assign
op_amp
id|SK_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|SK_close
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
op_amp
id|SK_send_packet
suffix:semicolon
id|dev-&gt;get_stats
op_assign
op_amp
id|SK_get_stats
suffix:semicolon
macro_line|#ifdef HAVE_MULTICAST
id|dev-&gt;set_multicast_list
op_assign
op_amp
id|set_multicast_list
suffix:semicolon
macro_line|#endif
multiline_comment|/* Set the generic fields of the device structure */
id|ether_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Initialize private structure */
id|p-&gt;ram
op_assign
(paren
r_struct
id|SK_ram
op_star
)paren
id|rom_addr
suffix:semicolon
multiline_comment|/* Set dual ported RAM addr */
id|p-&gt;tmdhead
op_assign
op_amp
(paren
id|p-&gt;ram
)paren
op_member_access_from_pointer
id|tmde
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Set TMD head */
id|p-&gt;rmdhead
op_assign
op_amp
(paren
id|p-&gt;ram
)paren
op_member_access_from_pointer
id|rmde
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Set RMD head */
multiline_comment|/* Initialize buffer pointers */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|TMDNUM
suffix:semicolon
id|i
op_increment
)paren
(brace
id|p-&gt;tmdbufs
(braket
id|i
)braket
op_assign
op_amp
(paren
id|p-&gt;ram
)paren
op_member_access_from_pointer
id|tmdbuf
(braket
id|i
)braket
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|RMDNUM
suffix:semicolon
id|i
op_increment
)paren
(brace
id|p-&gt;rmdbufs
(braket
id|i
)braket
op_assign
op_amp
(paren
id|p-&gt;ram
)paren
op_member_access_from_pointer
id|rmdbuf
(braket
id|i
)braket
suffix:semicolon
)brace
macro_line|#ifdef SK_DEBUG
id|SK_print_pos
c_func
(paren
id|dev
comma
l_string|&quot;End of SK_probe&quot;
)paren
suffix:semicolon
id|SK_print_ram
c_func
(paren
id|dev
)paren
suffix:semicolon
macro_line|#endif 
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Initialization done */
)brace
multiline_comment|/* End of SK_probe() */
"&f;"
multiline_comment|/*- &n; * Function       : SK_open&n; * Author         : Patrick J.D. Weichmann&n; * Date Created   : 94/05/26&n; *&n; * Description    : This function is called sometimes after booting &n; *                  when ifconfig program is run.&n; *&n; *                  This function requests an IRQ, sets the correct&n; *                  IRQ in the card. Then calls SK_lance_init() to &n; *                  init and start the LANCE chip. Then if everything is &n; *                  ok returns with 0 (OK), which means SK_G16 is now&n; *                  opened and operational.&n; *&n; *                  (Called by dev_open() /net/inet/dev.c)&n; *&n; * Parameters     : I : struct device *dev - SK_G16 device structure&n; * Return Value   : 0 - Device opened&n; * Errors         : -EAGAIN - Open failed&n; * Globals        : irq2dev_map - which device uses which irq&n; * Side Effects   : None&n; * Update History :&n; *     YY/MM/DD  uid  Description&n;-*/
DECL|function|SK_open
r_static
r_int
id|SK_open
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|irqval
op_assign
l_int|0
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
id|irqtab
(braket
)braket
op_assign
id|SK_IRQS
suffix:semicolon
r_struct
id|priv
op_star
id|p
op_assign
(paren
r_struct
id|priv
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|PRINTK
c_func
(paren
(paren
l_string|&quot;## %s: At beginning of SK_open(). CSR0: %#06x&bslash;n&quot;
comma
id|SK_NAME
comma
id|SK_read_reg
c_func
(paren
id|CSR0
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
op_eq
l_int|0
)paren
multiline_comment|/* Autoirq */
(brace
id|i
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* &n;         * Check if one IRQ out of SK_IRQS is free and install &n;&t; * interrupt handler.&n;&t; * Most done by request_irq(). &n;&t; * irqval: 0       - interrupt handler installed for IRQ irqtab[i]&n;&t; *         -EBUSY  - interrupt busy &n;         *         -EINVAL - irq &gt; 15 or handler = NULL&n;&t; */
r_do
(brace
id|irqval
op_assign
id|request_irq
c_func
(paren
id|irqtab
(braket
id|i
)braket
comma
op_amp
id|SK_interrupt
comma
l_int|0
comma
l_string|&quot;sk_g16&quot;
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|irqval
op_logical_and
id|irqtab
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irqval
)paren
multiline_comment|/* We tried every possible IRQ but no success */
(brace
id|printk
c_func
(paren
l_string|&quot;%s: unable to get an IRQ&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|dev-&gt;irq
op_assign
id|irqtab
(braket
op_decrement
id|i
)braket
suffix:semicolon
id|outb
c_func
(paren
id|i
op_lshift
l_int|2
comma
id|SK_POS4
)paren
suffix:semicolon
multiline_comment|/* Set Card on probed IRQ */
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;irq
op_eq
l_int|2
)paren
multiline_comment|/* IRQ2 is always IRQ9 */
(brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
l_int|9
comma
op_amp
id|SK_interrupt
comma
l_int|0
comma
l_string|&quot;sk_g16&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: unable to get IRQ 9&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|dev-&gt;irq
op_assign
l_int|9
suffix:semicolon
multiline_comment|/* &n;         * Now we set card on IRQ2.&n;         * This can be confusing, but remember that IRQ2 on the network&n;         * card is in reality IRQ9&n;         */
id|outb
c_func
(paren
l_int|0x08
comma
id|SK_POS4
)paren
suffix:semicolon
multiline_comment|/* set card to IRQ2 */
)brace
r_else
multiline_comment|/* Check IRQ as defined in Space.c */
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* check if IRQ free and valid. Then install Interrupt handler */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
op_amp
id|SK_interrupt
comma
l_int|0
comma
l_string|&quot;sk_g16&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: unable to get selected IRQ&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|dev-&gt;irq
)paren
(brace
r_case
l_int|3
suffix:colon
id|i
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|i
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|i
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|11
suffix:colon
id|i
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;%s: Preselected IRQ %d is invalid for %s boards&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;irq
comma
id|SK_NAME
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|outb
c_func
(paren
id|i
op_lshift
l_int|2
comma
id|SK_POS4
)paren
suffix:semicolon
multiline_comment|/* Set IRQ on card */
)brace
id|irq2dev_map
(braket
id|dev-&gt;irq
)braket
op_assign
id|dev
suffix:semicolon
multiline_comment|/* Set IRQ as used by us */
id|printk
c_func
(paren
l_string|&quot;%s: Schneider &amp; Koch G16 at %#3x, IRQ %d, shared mem at %#08x&bslash;n&quot;
comma
id|dev-&gt;name
comma
(paren
r_int
r_int
)paren
id|dev-&gt;base_addr
comma
(paren
r_int
)paren
id|dev-&gt;irq
comma
(paren
r_int
r_int
)paren
id|p-&gt;ram
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|i
op_assign
id|SK_lance_init
c_func
(paren
id|dev
comma
l_int|0
)paren
)paren
)paren
multiline_comment|/* LANCE init OK? */
(brace
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;interrupt
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;start
op_assign
l_int|1
suffix:semicolon
macro_line|#ifdef SK_DEBUG
multiline_comment|/* &n;         * This debug block tries to stop LANCE,&n;         * reinit LANCE with transmitter and receiver disabled,&n;         * then stop again and reinit with NORMAL_MODE&n;         */
id|printk
c_func
(paren
l_string|&quot;## %s: After lance init. CSR0: %#06x&bslash;n&quot;
comma
id|SK_NAME
comma
id|SK_read_reg
c_func
(paren
id|CSR0
)paren
)paren
suffix:semicolon
id|SK_write_reg
c_func
(paren
id|CSR0
comma
id|CSR0_STOP
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;## %s: LANCE stopped. CSR0: %#06x&bslash;n&quot;
comma
id|SK_NAME
comma
id|SK_read_reg
c_func
(paren
id|CSR0
)paren
)paren
suffix:semicolon
id|SK_lance_init
c_func
(paren
id|dev
comma
id|MODE_DTX
op_or
id|MODE_DRX
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;## %s: Reinit with DTX + DRX off. CSR0: %#06x&bslash;n&quot;
comma
id|SK_NAME
comma
id|SK_read_reg
c_func
(paren
id|CSR0
)paren
)paren
suffix:semicolon
id|SK_write_reg
c_func
(paren
id|CSR0
comma
id|CSR0_STOP
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;## %s: LANCE stopped. CSR0: %#06x&bslash;n&quot;
comma
id|SK_NAME
comma
id|SK_read_reg
c_func
(paren
id|CSR0
)paren
)paren
suffix:semicolon
id|SK_lance_init
c_func
(paren
id|dev
comma
id|MODE_NORMAL
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;## %s: LANCE back to normal mode. CSR0: %#06x&bslash;n&quot;
comma
id|SK_NAME
comma
id|SK_read_reg
c_func
(paren
id|CSR0
)paren
)paren
suffix:semicolon
id|SK_print_pos
c_func
(paren
id|dev
comma
l_string|&quot;POS regs before returning OK&quot;
)paren
suffix:semicolon
macro_line|#endif /* SK_DEBUG */
r_return
l_int|0
suffix:semicolon
multiline_comment|/* SK_open() is successful */
)brace
r_else
multiline_comment|/* LANCE init failed */
(brace
id|PRINTK
c_func
(paren
(paren
l_string|&quot;## %s: LANCE init failed: CSR0: %#06x&bslash;n&quot;
comma
id|SK_NAME
comma
id|SK_read_reg
c_func
(paren
id|CSR0
)paren
)paren
)paren
suffix:semicolon
id|dev-&gt;start
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Device not ready */
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
)brace
multiline_comment|/* End of SK_open() */
"&f;"
multiline_comment|/*-&n; * Function       : SK_lance_init&n; * Author         : Patrick J.D. Weichmann&n; * Date Created   : 94/05/26&n; *&n; * Description    : Reset LANCE chip, fill RMD, TMD structures with&n; *                  start values and Start LANCE.&n; *&n; * Parameters     : I : struct device *dev - SK_G16 device structure&n; *                  I : int mode - put LANCE into &quot;mode&quot; see data-sheet for&n; *                                 more info.&n; * Return Value   : 0  - Init done&n; * Errors         : -1 - Init failed&n; * Update History :&n; *     YY/MM/DD  uid  Description&n;-*/
DECL|function|SK_lance_init
r_static
r_int
id|SK_lance_init
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
r_int
id|mode
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|priv
op_star
id|p
op_assign
(paren
r_struct
id|priv
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_struct
id|tmd
op_star
id|tmdp
suffix:semicolon
r_struct
id|rmd
op_star
id|rmdp
suffix:semicolon
id|PRINTK
c_func
(paren
(paren
l_string|&quot;## %s: At beginning of LANCE init. CSR0: %#06x&bslash;n&quot;
comma
id|SK_NAME
comma
id|SK_read_reg
c_func
(paren
id|CSR0
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Reset LANCE */
id|SK_reset_board
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Initialize TMD&squot;s with start values */
id|p-&gt;tmdnum
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* First descriptor for transmitting */
id|p-&gt;tmdlast
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* First descriptor for reading stats */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|TMDNUM
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* Init all TMD&squot;s */
(brace
id|tmdp
op_assign
id|p-&gt;tmdhead
op_plus
id|i
suffix:semicolon
id|tmdp-&gt;u.buffer
op_assign
(paren
r_int
r_int
)paren
id|p-&gt;tmdbufs
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/* assign buffer */
multiline_comment|/* Mark TMD as start and end of packet */
id|tmdp-&gt;u.s.status
op_assign
id|TX_STP
op_or
id|TX_ENP
suffix:semicolon
)brace
multiline_comment|/* Initialize RMD&squot;s with start values */
id|p-&gt;rmdnum
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* First RMD which will be used */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|RMDNUM
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* Init all RMD&squot;s */
(brace
id|rmdp
op_assign
id|p-&gt;rmdhead
op_plus
id|i
suffix:semicolon
id|rmdp-&gt;u.buffer
op_assign
(paren
r_int
r_int
)paren
id|p-&gt;rmdbufs
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/* assign buffer */
multiline_comment|/* &n;         * LANCE must be owner at beginning so that he can fill in &n;&t; * receiving packets, set status and release RMD &n;&t; */
id|rmdp-&gt;u.s.status
op_assign
id|RX_OWN
suffix:semicolon
id|rmdp-&gt;blen
op_assign
op_minus
id|PKT_BUF_SZ
suffix:semicolon
multiline_comment|/* Buffer Size in a two&squot;s complement */
id|rmdp-&gt;mlen
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* init message length */
)brace
multiline_comment|/* Fill LANCE Initialize Block */
(paren
id|p-&gt;ram
)paren
op_member_access_from_pointer
id|ib.mode
op_assign
id|mode
suffix:semicolon
multiline_comment|/* Set operation mode */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ETH_ALEN
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* Set physical address */
(brace
(paren
id|p-&gt;ram
)paren
op_member_access_from_pointer
id|ib.paddr
(braket
id|i
)braket
op_assign
id|dev-&gt;dev_addr
(braket
id|i
)braket
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* Set multicast, logical address */
(brace
(paren
id|p-&gt;ram
)paren
op_member_access_from_pointer
id|ib.laddr
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* We do not use logical addressing */
)brace
multiline_comment|/* Set ring descriptor pointers and set number of descriptors */
(paren
id|p-&gt;ram
)paren
op_member_access_from_pointer
id|ib.rdrp
op_assign
(paren
r_int
)paren
id|p-&gt;rmdhead
op_or
id|RMDNUMMASK
suffix:semicolon
(paren
id|p-&gt;ram
)paren
op_member_access_from_pointer
id|ib.tdrp
op_assign
(paren
r_int
)paren
id|p-&gt;tmdhead
op_or
id|TMDNUMMASK
suffix:semicolon
multiline_comment|/* Prepare LANCE Control and Status Registers */
id|cli
c_func
(paren
)paren
suffix:semicolon
id|SK_write_reg
c_func
(paren
id|CSR3
comma
id|CSR3_ACON
)paren
suffix:semicolon
multiline_comment|/* Ale Control !!!THIS MUST BE SET!!!! */
multiline_comment|/* &n;     * LANCE addresses the RAM from 0x0000 to 0x3fbf and has no access to&n;     * PC Memory locations.&n;     *&n;     * In structure SK_ram is defined that the first thing in ram&n;     * is the initialization block. So his address is for LANCE always&n;     * 0x0000&n;     *&n;     * CSR1 contains low order bits 15:0 of initialization block address&n;     * CSR2 is built of: &n;     *    7:0  High order bits 23:16 of initialization block address&n;     *   15:8  reserved, must be 0&n;     */
multiline_comment|/* Set initialization block address (must be on word boundary) */
id|SK_write_reg
c_func
(paren
id|CSR1
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Set low order bits 15:0 */
id|SK_write_reg
c_func
(paren
id|CSR2
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Set high order bits 23:16 */
id|PRINTK
c_func
(paren
(paren
l_string|&quot;## %s: After setting CSR1-3. CSR0: %#06x&bslash;n&quot;
comma
id|SK_NAME
comma
id|SK_read_reg
c_func
(paren
id|CSR0
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Initialize LANCE */
multiline_comment|/* &n;     * INIT = Initialize, when set, causes the LANCE to begin the&n;     * initialization procedure and access the Init Block.&n;     */
id|SK_write_reg
c_func
(paren
id|CSR0
comma
id|CSR0_INIT
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Wait until LANCE finished initialization */
id|SK_set_RAP
c_func
(paren
id|CSR0
)paren
suffix:semicolon
multiline_comment|/* Register Address Pointer to CSR0 */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|i
OL
l_int|100
)paren
op_logical_and
op_logical_neg
(paren
id|SK_rread_reg
c_func
(paren
)paren
op_amp
id|CSR0_IDON
)paren
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
multiline_comment|/* Wait until init done or go ahead if problems (i&gt;=100) */
r_if
c_cond
(paren
id|i
op_ge
l_int|100
)paren
multiline_comment|/* Something is wrong ! */
(brace
id|printk
c_func
(paren
l_string|&quot;%s: can&squot;t init am7990, status: %04x &quot;
l_string|&quot;init_block: %#08x&bslash;n&quot;
comma
id|dev-&gt;name
comma
(paren
r_int
)paren
id|SK_read_reg
c_func
(paren
id|CSR0
)paren
comma
(paren
r_int
r_int
)paren
op_amp
(paren
id|p-&gt;ram
)paren
op_member_access_from_pointer
id|ib
)paren
suffix:semicolon
macro_line|#ifdef SK_DEBUG
id|SK_print_pos
c_func
(paren
id|dev
comma
l_string|&quot;LANCE INIT failed&quot;
)paren
suffix:semicolon
id|SK_print_dev
c_func
(paren
id|dev
comma
l_string|&quot;Device Structure:&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* LANCE init failed */
)brace
id|PRINTK
c_func
(paren
(paren
l_string|&quot;## %s: init done after %d ticks&bslash;n&quot;
comma
id|SK_NAME
comma
id|i
)paren
)paren
suffix:semicolon
multiline_comment|/* Clear Initialize done, enable Interrupts, start LANCE */
id|SK_write_reg
c_func
(paren
id|CSR0
comma
id|CSR0_IDON
op_or
id|CSR0_INEA
op_or
id|CSR0_STRT
)paren
suffix:semicolon
id|PRINTK
c_func
(paren
(paren
l_string|&quot;## %s: LANCE started. CSR0: %#06x&bslash;n&quot;
comma
id|SK_NAME
comma
id|SK_read_reg
c_func
(paren
id|CSR0
)paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* LANCE is up and running */
)brace
multiline_comment|/* End of SK_lance_init() */
"&f;"
multiline_comment|/*-&n; * Function       : SK_send_packet&n; * Author         : Patrick J.D. Weichmann&n; * Date Created   : 94/05/27&n; *&n; * Description    : Writes an socket buffer into a transmit descriptor&n; *                  and starts transmission.&n; *&n; * Parameters     : I : struct sk_buff *skb - packet to transfer&n; *                  I : struct device *dev  - SK_G16 device structure&n; * Return Value   : 0 - OK&n; *                  1 - Could not transmit (dev_queue_xmit will queue it)&n; *                      and try to sent it later&n; * Globals        : None&n; * Side Effects   : None&n; * Update History :&n; *     YY/MM/DD  uid  Description&n;-*/
DECL|function|SK_send_packet
r_static
r_int
id|SK_send_packet
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|priv
op_star
id|p
op_assign
(paren
r_struct
id|priv
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_struct
id|tmd
op_star
id|tmdp
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;tbusy
)paren
(brace
multiline_comment|/* if Transmitter more than 150ms busy -&gt; time_out */
r_int
id|tickssofar
op_assign
id|jiffies
op_minus
id|dev-&gt;trans_start
suffix:semicolon
r_if
c_cond
(paren
id|tickssofar
OL
l_int|15
)paren
(brace
r_return
l_int|1
suffix:semicolon
multiline_comment|/* We have to try transmit later */
)brace
id|printk
c_func
(paren
l_string|&quot;%s: xmitter timed out, try to restart!&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|SK_lance_init
c_func
(paren
id|dev
comma
id|MODE_NORMAL
)paren
suffix:semicolon
multiline_comment|/* Reinit LANCE */
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Clear Transmitter flag */
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/* Mark Start of transmission */
)brace
multiline_comment|/* &n;     * If some upper Layer thinks we missed a transmit done interrupt&n;     * we are passed NULL.&n;     * (dev_queue_xmit net/inet/dev.c &n;     */
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* &n;         * Dequeue packets from transmit queue and send them.&n;         */
id|dev_tint
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|PRINTK2
c_func
(paren
(paren
l_string|&quot;## %s: SK_send_packet() called, CSR0 %#04x.&bslash;n&quot;
comma
id|SK_NAME
comma
id|SK_read_reg
c_func
(paren
id|CSR0
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* &n;     * Block a timer-based transmit from overlapping. &n;     * This means check if we are already in. &n;     */
r_if
c_cond
(paren
id|set_bit
c_func
(paren
l_int|0
comma
(paren
r_void
op_star
)paren
op_amp
id|dev-&gt;tbusy
)paren
op_ne
l_int|0
)paren
multiline_comment|/* dev-&gt;tbusy already set ? */
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Transmitter access conflict.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Evaluate Packet length */
r_int
id|len
op_assign
id|ETH_ZLEN
OL
id|skb-&gt;len
ques
c_cond
id|skb-&gt;len
suffix:colon
id|ETH_ZLEN
suffix:semicolon
id|tmdp
op_assign
id|p-&gt;tmdhead
op_plus
id|p-&gt;tmdnum
suffix:semicolon
multiline_comment|/* Which descriptor for transmitting */
multiline_comment|/* Fill in Transmit Message Descriptor */
multiline_comment|/* Copy data into dual ported ram */
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
(paren
id|tmdp-&gt;u.buffer
op_amp
l_int|0x00ffffff
)paren
comma
(paren
r_char
op_star
)paren
id|skb-&gt;data
comma
id|skb-&gt;len
)paren
suffix:semicolon
id|tmdp-&gt;blen
op_assign
op_minus
id|len
suffix:semicolon
multiline_comment|/* set length to transmit */
multiline_comment|/* &n;&t; * Packet start and end is always set because we use the maximum&n;&t; * packet length as buffer length.&n;&t; * Relinquish ownership to LANCE&n;&t; */
id|tmdp-&gt;u.s.status
op_assign
id|TX_OWN
op_or
id|TX_STP
op_or
id|TX_ENP
suffix:semicolon
multiline_comment|/* Start Demand Transmission */
id|SK_write_reg
c_func
(paren
id|CSR0
comma
id|CSR0_TDMD
op_or
id|CSR0_INEA
)paren
suffix:semicolon
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/* Mark start of transmission */
multiline_comment|/* Set pointer to next transmit buffer */
id|p-&gt;tmdnum
op_increment
suffix:semicolon
id|p-&gt;tmdnum
op_and_assign
id|TMDNUM
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Do we own the next transmit buffer ? */
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|p-&gt;tmdhead
op_plus
id|p-&gt;tmdnum
)paren
op_member_access_from_pointer
id|u.s.status
op_amp
id|TX_OWN
)paren
)paren
(brace
multiline_comment|/* &n;&t;    * We own next buffer and are ready to transmit, so&n;&t;    * clear busy flag&n;&t;    */
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|dev_kfree_skb
c_func
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* End of SK_send_packet */
"&f;"
multiline_comment|/*-&n; * Function       : SK_interrupt&n; * Author         : Patrick J.D. Weichmann&n; * Date Created   : 94/05/27&n; *&n; * Description    : SK_G16 interrupt handler which checks for LANCE&n; *                  Errors, handles transmit and receive interrupts&n; *&n; * Parameters     : I : int reg_ptr -&n; * Return Value   : None&n; * Errors         : None&n; * Globals        : None&n; * Side Effects   : None&n; * Update History :&n; *     YY/MM/DD  uid  Description&n;-*/
DECL|function|SK_interrupt
r_static
r_void
id|SK_interrupt
c_func
(paren
r_int
id|reg_ptr
)paren
(brace
r_int
id|irq
op_assign
op_minus
(paren
(paren
(paren
r_struct
id|pt_regs
op_star
)paren
id|reg_ptr
)paren
op_member_access_from_pointer
id|orig_eax
op_plus
l_int|2
)paren
suffix:semicolon
r_int
id|csr0
suffix:semicolon
r_struct
id|device
op_star
id|dev
op_assign
(paren
r_struct
id|device
op_star
)paren
id|irq2dev_map
(braket
id|irq
)braket
suffix:semicolon
r_struct
id|priv
op_star
id|p
op_assign
(paren
r_struct
id|priv
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|PRINTK2
c_func
(paren
(paren
l_string|&quot;## %s: SK_interrupt(). status: %#06x&bslash;n&quot;
comma
id|SK_NAME
comma
id|SK_read_reg
c_func
(paren
id|CSR0
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SK_interrupt(): IRQ %d for unknown device.&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;interrupt
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Re-entering the interrupt handler.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
id|csr0
op_assign
id|SK_read_reg
c_func
(paren
id|CSR0
)paren
suffix:semicolon
multiline_comment|/* store register for checking */
id|dev-&gt;interrupt
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* We are handling an interrupt */
multiline_comment|/* &n;     * Acknowledge all of the current interrupt sources, disable      &n;     * Interrupts (INEA = 0) &n;     */
id|SK_write_reg
c_func
(paren
id|CSR0
comma
id|csr0
op_amp
id|CSR0_CLRALL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|csr0
op_amp
id|CSR0_ERR
)paren
multiline_comment|/* LANCE Error */
(brace
id|printk
c_func
(paren
l_string|&quot;%s: error: %04x&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|csr0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|csr0
op_amp
id|CSR0_MISS
)paren
multiline_comment|/* No place to store packet ? */
(brace
id|p-&gt;stats.rx_dropped
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|csr0
op_amp
id|CSR0_RINT
)paren
multiline_comment|/* Receive Interrupt (packet arrived) */
(brace
id|SK_rxintr
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|csr0
op_amp
id|CSR0_TINT
)paren
multiline_comment|/* Transmit interrupt (packet sent) */
(brace
id|SK_txintr
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|SK_write_reg
c_func
(paren
id|CSR0
comma
id|CSR0_INEA
)paren
suffix:semicolon
multiline_comment|/* Enable Interrupts */
id|dev-&gt;interrupt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* We are out */
)brace
multiline_comment|/* End of SK_interrupt() */
"&f;"
multiline_comment|/*-&n; * Function       : SK_txintr&n; * Author         : Patrick J.D. Weichmann&n; * Date Created   : 94/05/27&n; *&n; * Description    : After sending a packet we check status, update&n; *                  statistics and relinquish ownership of transmit &n; *                  descriptor ring.&n; *&n; * Parameters     : I : struct device *dev - SK_G16 device structure&n; * Return Value   : None&n; * Errors         : None&n; * Globals        : None&n; * Update History :&n; *     YY/MM/DD  uid  Description&n;-*/
DECL|function|SK_txintr
r_static
r_void
id|SK_txintr
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|tmdstat
suffix:semicolon
r_struct
id|tmd
op_star
id|tmdp
suffix:semicolon
r_struct
id|priv
op_star
id|p
op_assign
(paren
r_struct
id|priv
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|PRINTK2
c_func
(paren
(paren
l_string|&quot;## %s: SK_txintr() status: %#06x&bslash;n&quot;
comma
id|SK_NAME
comma
id|SK_read_reg
c_func
(paren
id|CSR0
)paren
)paren
)paren
suffix:semicolon
id|tmdp
op_assign
id|p-&gt;tmdhead
op_plus
id|p-&gt;tmdlast
suffix:semicolon
multiline_comment|/* Which buffer we sent at last ? */
multiline_comment|/* Set next buffer */
id|p-&gt;tmdlast
op_increment
suffix:semicolon
id|p-&gt;tmdlast
op_and_assign
id|TMDNUM
op_minus
l_int|1
suffix:semicolon
id|tmdstat
op_assign
id|tmdp-&gt;u.s.status
op_amp
l_int|0xff00
suffix:semicolon
multiline_comment|/* filter out status bits 15:08 */
multiline_comment|/* &n;     * We check status of transmitted packet.&n;     * see LANCE data-sheet for error explanation&n;     */
r_if
c_cond
(paren
id|tmdstat
op_amp
id|TX_ERR
)paren
multiline_comment|/* Error occurred */
(brace
id|printk
c_func
(paren
l_string|&quot;%s: TX error: %04x %04x&bslash;n&quot;
comma
id|dev-&gt;name
comma
(paren
r_int
)paren
id|tmdstat
comma
(paren
r_int
)paren
id|tmdp-&gt;status2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmdp-&gt;status2
op_amp
id|TX_TDR
)paren
multiline_comment|/* TDR problems? */
(brace
id|printk
c_func
(paren
l_string|&quot;%s: tdr-problems &bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tmdp-&gt;status2
op_amp
id|TX_RTRY
)paren
multiline_comment|/* Failed in 16 attempts to transmit ? */
id|p-&gt;stats.tx_aborted_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|tmdp-&gt;status2
op_amp
id|TX_LCOL
)paren
multiline_comment|/* Late collision ? */
id|p-&gt;stats.tx_window_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|tmdp-&gt;status2
op_amp
id|TX_LCAR
)paren
multiline_comment|/* Loss of Carrier ? */
id|p-&gt;stats.tx_carrier_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|tmdp-&gt;status2
op_amp
id|TX_UFLO
)paren
multiline_comment|/* Underflow error ? */
(brace
id|p-&gt;stats.tx_fifo_errors
op_increment
suffix:semicolon
multiline_comment|/* &n;             * If UFLO error occurs it will turn transmitter of.&n;             * So we must reinit LANCE&n;             */
id|SK_lance_init
c_func
(paren
id|dev
comma
id|MODE_NORMAL
)paren
suffix:semicolon
)brace
id|p-&gt;stats.tx_errors
op_increment
suffix:semicolon
id|tmdp-&gt;status2
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Clear error flags */
)brace
r_else
r_if
c_cond
(paren
id|tmdstat
op_amp
id|TX_MORE
)paren
multiline_comment|/* Collisions occurred ? */
(brace
multiline_comment|/* &n;         * Here I have a problem.&n;         * I only know that there must be one or up to 15 collisions.&n;         * Thats why TX_MORE is set, because after 16 attempts TX_RTRY&n;         * will be set which means couldn&squot;t send packet aborted transfer.&n;         *&n;         * First I did not have this in but then I thought at minimum&n;         * we see that something was not ok.&n;         * If anyone knows something better than this to handle this&n;         * please report it. (see Email addresses in the README file)&n;         */
id|p-&gt;stats.collisions
op_increment
suffix:semicolon
)brace
r_else
multiline_comment|/* Packet sent without any problems */
(brace
id|p-&gt;stats.tx_packets
op_increment
suffix:semicolon
)brace
multiline_comment|/* &n;     * We mark transmitter not busy anymore, because now we have a free&n;     * transmit descriptor which can be filled by SK_send_packet and&n;     * afterwards sent by the LANCE&n;     */
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* &n;     * mark_bh(NET_BH);&n;     * This will cause net_bh() to run after this interrupt handler.&n;     *&n;     * The function which do handle slow IRQ parts is do_bottom_half()&n;     * which runs at normal kernel priority, that means all interrupt are&n;     * enabled. (see kernel/irq.c)&n;     *  &n;     * net_bh does something like this:&n;     *  - check if already in net_bh&n;     *  - try to transmit something from the send queue&n;     *  - if something is in the receive queue send it up to higher &n;     *    levels if it is a known protocol&n;     *  - try to transmit something from the send queue&n;     */
id|mark_bh
c_func
(paren
id|NET_BH
)paren
suffix:semicolon
)brace
multiline_comment|/* End of SK_txintr() */
"&f;"
multiline_comment|/*-&n; * Function       : SK_rxintr&n; * Author         : Patrick J.D. Weichmann&n; * Date Created   : 94/05/27&n; *&n; * Description    : Buffer sent, check for errors, relinquish ownership&n; *                  of the receive message descriptor. &n; *&n; * Parameters     : I : SK_G16 device structure&n; * Return Value   : None&n; * Globals        : None&n; * Update History :&n; *     YY/MM/DD  uid  Description&n;-*/
DECL|function|SK_rxintr
r_static
r_void
id|SK_rxintr
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|rmd
op_star
id|rmdp
suffix:semicolon
r_int
id|rmdstat
suffix:semicolon
r_struct
id|priv
op_star
id|p
op_assign
(paren
r_struct
id|priv
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|PRINTK2
c_func
(paren
(paren
l_string|&quot;## %s: SK_rxintr(). CSR0: %#06x&bslash;n&quot;
comma
id|SK_NAME
comma
id|SK_read_reg
c_func
(paren
id|CSR0
)paren
)paren
)paren
suffix:semicolon
id|rmdp
op_assign
id|p-&gt;rmdhead
op_plus
id|p-&gt;rmdnum
suffix:semicolon
multiline_comment|/* As long as we own the next entry, check status and send&n;     * it up to higher layer &n;     */
r_while
c_loop
(paren
op_logical_neg
(paren
(paren
id|rmdstat
op_assign
id|rmdp-&gt;u.s.status
)paren
op_amp
id|RX_OWN
)paren
)paren
(brace
multiline_comment|/* &n;         * Start and end of packet must be set, because we use &n;&t; * the ethernet maximum packet length (1518) as buffer size.&n;&t; * &n;&t; * Because our buffers are at maximum OFLO and BUFF errors are&n;&t; * not to be concerned (see Data sheet)&n;&t; */
r_if
c_cond
(paren
id|rmdstat
op_amp
(paren
id|RX_STP
op_or
id|RX_ENP
)paren
op_ne
(paren
id|RX_STP
op_or
id|RX_ENP
)paren
)paren
(brace
multiline_comment|/* Start of a frame &gt; 1518 Bytes ? */
r_if
c_cond
(paren
id|rmdstat
op_amp
id|RX_STP
)paren
(brace
id|p-&gt;stats.rx_errors
op_increment
suffix:semicolon
multiline_comment|/* bad packet received */
id|p-&gt;stats.rx_length_errors
op_increment
suffix:semicolon
multiline_comment|/* packet to long */
id|printk
c_func
(paren
l_string|&quot;%s: packet too long&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
multiline_comment|/* &n;             * All other packets will be ignored until a new frame with&n;&t;     * start (RX_STP) set follows.&n;&t;     * &n;&t;     * What we do is just give descriptor free for new incoming&n;&t;     * packets. &n;&t;     */
id|rmdp-&gt;u.s.status
op_assign
id|RX_OWN
suffix:semicolon
multiline_comment|/* Relinquish ownership to LANCE */
)brace
r_else
r_if
c_cond
(paren
id|rmdstat
op_amp
id|RX_ERR
)paren
multiline_comment|/* Receive Error ? */
(brace
id|printk
c_func
(paren
l_string|&quot;%s: RX error: %04x&bslash;n&quot;
comma
id|dev-&gt;name
comma
(paren
r_int
)paren
id|rmdstat
)paren
suffix:semicolon
id|p-&gt;stats.rx_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|rmdstat
op_amp
id|RX_FRAM
)paren
id|p-&gt;stats.rx_frame_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|rmdstat
op_amp
id|RX_CRC
)paren
id|p-&gt;stats.rx_crc_errors
op_increment
suffix:semicolon
id|rmdp-&gt;u.s.status
op_assign
id|RX_OWN
suffix:semicolon
multiline_comment|/* Relinquish ownership to LANCE */
)brace
r_else
multiline_comment|/* We have a packet which can be queued for the upper layers */
(brace
r_int
id|len
op_assign
(paren
id|rmdp-&gt;mlen
op_amp
l_int|0x0fff
)paren
suffix:semicolon
multiline_comment|/* extract message length from receive buffer */
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|len
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
multiline_comment|/* allocate socket buffer */
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
multiline_comment|/* Could not get mem ? */
(brace
multiline_comment|/* &n;                 * Couldn&squot;t allocate sk_buffer so we give descriptor back&n;&t;&t; * to Lance, update statistics and go ahead.&n;&t;&t; */
id|rmdp-&gt;u.s.status
op_assign
id|RX_OWN
suffix:semicolon
multiline_comment|/* Relinquish ownership to LANCE */
id|printk
c_func
(paren
l_string|&quot;%s: Couldn&squot;t allocate sk_buff, deferring packet.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|p-&gt;stats.rx_dropped
op_increment
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Jump out */
)brace
multiline_comment|/* Prepare sk_buff to queue for upper layers */
id|skb-&gt;len
op_assign
id|len
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
multiline_comment|/* &n;             * Copy data out of our receive descriptor into sk_buff.&n;&t;     *&n;&t;     * (rmdp-&gt;u.buffer &amp; 0x00ffffff) -&gt; get address of buffer and &n;&t;     * ignore status fields) &n;&t;     */
id|memcpy
c_func
(paren
id|skb-&gt;data
comma
(paren
r_int
r_char
op_star
)paren
(paren
id|rmdp-&gt;u.buffer
op_amp
l_int|0x00ffffff
)paren
comma
id|len
)paren
suffix:semicolon
multiline_comment|/* &n;             * Notify the upper protocol layers that there is another packet&n;&t;     * to handle&n;&t;     *&n;&t;     * netif_rx() always succeeds. see /net/inet/dev.c for more.&n;&t;     */
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
multiline_comment|/* queue packet and mark it for processing */
multiline_comment|/* &n;             * Packet is queued and marked for processing so we&n;&t;     * free our descriptor and update statistics &n;&t;     */
id|rmdp-&gt;u.s.status
op_assign
id|RX_OWN
suffix:semicolon
id|p-&gt;stats.rx_packets
op_increment
suffix:semicolon
id|p-&gt;rmdnum
op_increment
suffix:semicolon
id|p-&gt;rmdnum
op_mod_assign
id|RMDNUM
suffix:semicolon
id|rmdp
op_assign
id|p-&gt;rmdhead
op_plus
id|p-&gt;rmdnum
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* End of SK_rxintr() */
"&f;"
multiline_comment|/*-&n; * Function       : SK_close&n; * Author         : Patrick J.D. Weichmann&n; * Date Created   : 94/05/26&n; *&n; * Description    : close gets called from dev_close() and should&n; *                  deinstall the card (free_irq, mem etc).&n; *&n; * Parameters     : I : struct device *dev - our device structure&n; * Return Value   : 0 - closed device driver&n; * Errors         : None&n; * Globals        : None&n; * Update History :&n; *     YY/MM/DD  uid  Description&n;-*/
multiline_comment|/* I have tried to set BOOT_ROM on and RAM off but then, after a &squot;ifconfig&n; * down&squot; the system stops. So I don&squot;t shut set card to init state.&n; */
DECL|function|SK_close
r_static
r_int
id|SK_close
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|PRINTK
c_func
(paren
(paren
l_string|&quot;## %s: SK_close(). CSR0: %#06x&bslash;n&quot;
comma
id|SK_NAME
comma
id|SK_read_reg
c_func
(paren
id|CSR0
)paren
)paren
)paren
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Transmitter busy */
id|dev-&gt;start
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Card down */
id|printk
c_func
(paren
l_string|&quot;%s: Shutting %s down CSR0 %#06x&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|SK_NAME
comma
(paren
r_int
)paren
id|SK_read_reg
c_func
(paren
id|CSR0
)paren
)paren
suffix:semicolon
id|SK_write_reg
c_func
(paren
id|CSR0
comma
id|CSR0_STOP
)paren
suffix:semicolon
multiline_comment|/* STOP the LANCE */
id|free_irq
c_func
(paren
id|dev-&gt;irq
)paren
suffix:semicolon
multiline_comment|/* Free IRQ */
id|irq2dev_map
(braket
id|dev-&gt;irq
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Mark IRQ as unused */
r_return
l_int|0
suffix:semicolon
multiline_comment|/* always succeed */
)brace
multiline_comment|/* End of SK_close() */
"&f;"
multiline_comment|/*-&n; * Function       : SK_get_stats&n; * Author         : Patrick J.D. Weichmann&n; * Date Created   : 94/05/26&n; *&n; * Description    : Return current status structure to upper layers.&n; *                  It is called by sprintf_stats (dev.c).&n; *&n; * Parameters     : I : struct device *dev   - our device structure&n; * Return Value   : struct enet_statistics * - our current statistics&n; * Errors         : None&n; * Side Effects   : None&n; * Update History :&n; *     YY/MM/DD  uid  Description&n;-*/
DECL|function|SK_get_stats
r_static
r_struct
id|enet_statistics
op_star
id|SK_get_stats
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|priv
op_star
id|p
op_assign
(paren
r_struct
id|priv
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|PRINTK
c_func
(paren
(paren
l_string|&quot;## %s: SK_get_stats(). CSR0: %#06x&bslash;n&quot;
comma
id|SK_NAME
comma
id|SK_read_reg
c_func
(paren
id|CSR0
)paren
)paren
)paren
suffix:semicolon
r_return
op_amp
id|p-&gt;stats
suffix:semicolon
multiline_comment|/* Return Device status */
)brace
multiline_comment|/* End of SK_get_stats() */
macro_line|#ifdef HAVE_MULTICAST
"&f;"
multiline_comment|/*-&n; * Function       : set_multicast_list&n; * Author         : Patrick J.D. Weichmann&n; * Date Created   : 94/05/26&n; *&n; * Description    : This function gets called when a program performs&n; *                  a SIOCSIFFLAGS call. Ifconfig does this if you call&n; *                  &squot;ifconfig [-]allmulti&squot; which enables or disables the&n; *                  Promiscuous mode.&n; *                  Promiscuous mode is when the Network card accepts all&n; *                  packets, not only the packets which match our MAC &n; *                  Address. It is useful for writing a network monitor,&n; *                  but it is also a security problem. You have to remember&n; *                  that all information on the net is not encrypted.&n; *&n; * Parameters     : I : struct device *dev - SK_G16 device Structure&n; *                  I : int num_addrs      - explanation further down&n; *                  I : void *addrs        - &n; * Return Value   : None&n; * Errors         : None&n; * Globals        : None&n; * Update History :&n; *     YY/MM/DD  uid  Description&n;-*/
multiline_comment|/* Set or clear the multicast filter for SK_G16.&n; *&n; * num_addrs == -1      Promiscuous mode, receive all packets&n; * num_addrs == 0       Normal mode, clear multicast list&n; * num_addrs &gt; 0        Multicast mode, receive normal and MC packets&n; */
DECL|function|set_multicast_list
r_static
r_void
id|set_multicast_list
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|num_addrs
comma
r_void
op_star
id|addrs
)paren
(brace
r_if
c_cond
(paren
id|num_addrs
op_eq
op_minus
l_int|1
)paren
(brace
multiline_comment|/* Reinitialize LANCE with MODE_PROM set */
id|SK_lance_init
c_func
(paren
id|dev
comma
id|MODE_PROM
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|num_addrs
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Reinitialize LANCE without MODE_PROM */
id|SK_lance_init
c_func
(paren
id|dev
comma
id|MODE_NORMAL
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Multicast with logical address filter on */
multiline_comment|/* Not implemented yet. */
)brace
)brace
multiline_comment|/* End of set_multicast_list() */
macro_line|#endif     
"&f;"
multiline_comment|/*-&n; * Function       : SK_rom_addr&n; * Author         : Patrick J.D. Weichmann&n; * Date Created   : 94/06/01&n; *&n; * Description    : Try to find a Boot_ROM at all possible locations&n; *&n; * Parameters     : None&n; * Return Value   : Address where Boot_ROM is&n; * Errors         : 0 - Did not find Boot_ROM&n; * Globals        : None&n; * Update History :&n; *     YY/MM/DD  uid  Description&n;-*/
DECL|function|SK_rom_addr
r_int
r_int
id|SK_rom_addr
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_int
id|rom_found
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|rom_location
(braket
)braket
op_assign
id|SK_BOOT_ROM_LOCATIONS
suffix:semicolon
r_int
r_char
id|rom_id
(braket
)braket
op_assign
id|SK_BOOT_ROM_ID
suffix:semicolon
r_int
r_char
op_star
id|test_byte
suffix:semicolon
multiline_comment|/* Autodetect Boot_ROM */
id|PRINTK
c_func
(paren
(paren
l_string|&quot;## %s: Autodetection of Boot_ROM&bslash;n&quot;
comma
id|SK_NAME
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|rom_location
(braket
id|i
)braket
op_ne
l_int|0
)paren
op_logical_and
(paren
id|rom_found
op_eq
l_int|0
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|PRINTK
c_func
(paren
(paren
l_string|&quot;##   Trying ROM location %#08x&quot;
comma
id|rom_location
(braket
id|i
)braket
)paren
)paren
suffix:semicolon
id|rom_found
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|6
suffix:semicolon
id|j
op_increment
)paren
(brace
id|test_byte
op_assign
(paren
r_int
r_char
op_star
)paren
(paren
id|rom_location
(braket
id|i
)braket
op_plus
id|j
)paren
suffix:semicolon
id|PRINTK
c_func
(paren
(paren
l_string|&quot; %02x &quot;
comma
op_star
id|test_byte
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|test_byte
op_eq
id|rom_id
(braket
id|j
)braket
)paren
)paren
(brace
id|rom_found
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|PRINTK
c_func
(paren
(paren
l_string|&quot;&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rom_found
op_eq
l_int|1
)paren
(brace
id|PRINTK
c_func
(paren
(paren
l_string|&quot;## %s: Boot_ROM found at %#08x&bslash;n&quot;
comma
id|SK_NAME
comma
id|rom_location
(braket
(paren
id|i
op_minus
l_int|1
)paren
)braket
)paren
)paren
suffix:semicolon
r_return
(paren
id|rom_location
(braket
op_decrement
id|i
)braket
)paren
suffix:semicolon
)brace
r_else
(brace
id|PRINTK
c_func
(paren
(paren
l_string|&quot;%s: No Boot_ROM found&bslash;n&quot;
comma
id|SK_NAME
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* End of SK_rom_addr() */
"&f;"
multiline_comment|/* LANCE access functions &n; *&n; * ! CSR1-3 can only be accessed when in CSR0 the STOP bit is set !&n; */
multiline_comment|/*-&n; * Function       : SK_reset_board&n; *&n; * Author         : Patrick J.D. Weichmann&n; *&n; * Date Created   : 94/05/25&n; *&n; * Description    : This function resets SK_G16 and all components, but&n; *                  POS registers are not changed&n; *&n; * Parameters     : None&n; * Return Value   : None&n; * Errors         : None&n; * Globals        : SK_RAM *board - SK_RAM structure pointer&n; *&n; * Update History :&n; *     YY/MM/DD  uid  Description&n;-*/
DECL|function|SK_reset_board
r_void
id|SK_reset_board
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|SK_PORT
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* Reset active */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|10
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* Delay min 5ms */
suffix:semicolon
id|SK_PORT
op_assign
id|SK_RESET
suffix:semicolon
multiline_comment|/* Set back to normal operation */
)brace
multiline_comment|/* End of SK_reset_board() */
"&f;"
multiline_comment|/*-&n; * Function       : SK_set_RAP&n; * Author         : Patrick J.D. Weichmann&n; * Date Created   : 94/05/25&n; *&n; * Description    : Set LANCE Register Address Port to register&n; *                  for later data transfer.&n; *&n; * Parameters     : I : reg_number - which CSR to read/write from/to&n; * Return Value   : None&n; * Errors         : None&n; * Globals        : SK_RAM *board - SK_RAM structure pointer&n; * Update History :&n; *     YY/MM/DD  uid  Description&n;-*/
DECL|function|SK_set_RAP
r_void
id|SK_set_RAP
c_func
(paren
r_int
id|reg_number
)paren
(brace
id|SK_IOREG
op_assign
id|reg_number
suffix:semicolon
id|SK_PORT
op_assign
id|SK_RESET
op_or
id|SK_RAP
op_or
id|SK_WREG
suffix:semicolon
id|SK_IOCOM
op_assign
id|SK_DOIO
suffix:semicolon
r_while
c_loop
(paren
id|SK_PORT
op_amp
id|SK_IORUN
)paren
suffix:semicolon
)brace
multiline_comment|/* End of SK_set_RAP() */
"&f;"
multiline_comment|/*-&n; * Function       : SK_read_reg&n; * Author         : Patrick J.D. Weichmann&n; * Date Created   : 94/05/25&n; *&n; * Description    : Set RAP and read data from a LANCE CSR register&n; *&n; * Parameters     : I : reg_number - which CSR to read from&n; * Return Value   : Register contents&n; * Errors         : None&n; * Globals        : SK_RAM *board - SK_RAM structure pointer&n; * Update History :&n; *     YY/MM/DD  uid  Description&n;-*/
DECL|function|SK_read_reg
r_int
id|SK_read_reg
c_func
(paren
r_int
id|reg_number
)paren
(brace
id|SK_set_RAP
c_func
(paren
id|reg_number
)paren
suffix:semicolon
id|SK_PORT
op_assign
id|SK_RESET
op_or
id|SK_RDATA
op_or
id|SK_RREG
suffix:semicolon
id|SK_IOCOM
op_assign
id|SK_DOIO
suffix:semicolon
r_while
c_loop
(paren
id|SK_PORT
op_amp
id|SK_IORUN
)paren
suffix:semicolon
r_return
(paren
id|SK_IOREG
)paren
suffix:semicolon
)brace
multiline_comment|/* End of SK_read_reg() */
"&f;"
multiline_comment|/*-&n; * Function       : SK_rread_reg&n; * Author         : Patrick J.D. Weichmann&n; * Date Created   : 94/05/28&n; *&n; * Description    : Read data from preseted register.&n; *                  This function requires that you know which&n; *                  Register is actually set. Be aware that CSR1-3&n; *                  can only be accessed when in CSR0 STOP is set.&n; *&n; * Return Value   : Register contents&n; * Errors         : None&n; * Globals        : SK_RAM *board - SK_RAM structure pointer&n; * Update History :&n; *     YY/MM/DD  uid  Description&n;-*/
DECL|function|SK_rread_reg
r_int
id|SK_rread_reg
c_func
(paren
r_void
)paren
(brace
id|SK_PORT
op_assign
id|SK_RESET
op_or
id|SK_RDATA
op_or
id|SK_RREG
suffix:semicolon
id|SK_IOCOM
op_assign
id|SK_DOIO
suffix:semicolon
r_while
c_loop
(paren
id|SK_PORT
op_amp
id|SK_IORUN
)paren
suffix:semicolon
r_return
(paren
id|SK_IOREG
)paren
suffix:semicolon
)brace
multiline_comment|/* End of SK_rread_reg() */
"&f;"
multiline_comment|/*-&n; * Function       : SK_write_reg&n; * Author         : Patrick J.D. Weichmann&n; * Date Created   : 94/05/25&n; *&n; * Description    : This function sets the RAP then fills in the&n; *                  LANCE I/O Reg and starts Transfer to LANCE.&n; *                  It waits until transfer has ended which is max. 7 ms&n; *                  and then it returns.&n; *&n; * Parameters     : I : reg_number - which CSR to write to&n; *                  I : value      - what value to fill into register &n; * Return Value   : None&n; * Errors         : None&n; * Globals        : SK_RAM *board - SK_RAM structure pointer&n; * Update History :&n; *     YY/MM/DD  uid  Description&n;-*/
DECL|function|SK_write_reg
r_void
id|SK_write_reg
c_func
(paren
r_int
id|reg_number
comma
r_int
id|value
)paren
(brace
id|SK_set_RAP
c_func
(paren
id|reg_number
)paren
suffix:semicolon
id|SK_IOREG
op_assign
id|value
suffix:semicolon
id|SK_PORT
op_assign
id|SK_RESET
op_or
id|SK_RDATA
op_or
id|SK_WREG
suffix:semicolon
id|SK_IOCOM
op_assign
id|SK_DOIO
suffix:semicolon
r_while
c_loop
(paren
id|SK_PORT
op_amp
id|SK_IORUN
)paren
suffix:semicolon
)brace
multiline_comment|/* End of SK_write_reg */
"&f;"
multiline_comment|/* &n; * Debugging functions&n; * -------------------&n; */
multiline_comment|/*-&n; * Function       : SK_print_pos&n; * Author         : Patrick J.D. Weichmann&n; * Date Created   : 94/05/25&n; *&n; * Description    : This function prints out the 4 POS (Programmable&n; *                  Option Select) Registers. Used mainly to debug operation.&n; *&n; * Parameters     : I : struct device *dev - SK_G16 device structure&n; *                  I : char * - Text which will be printed as title&n; * Return Value   : None&n; * Errors         : None&n; * Update History :&n; *     YY/MM/DD  uid  Description&n;-*/
DECL|function|SK_print_pos
r_void
id|SK_print_pos
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|text
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
r_char
id|pos0
op_assign
id|inb
c_func
(paren
id|SK_POS0
)paren
comma
id|pos1
op_assign
id|inb
c_func
(paren
id|SK_POS1
)paren
comma
id|pos2
op_assign
id|inb
c_func
(paren
id|SK_POS2
)paren
comma
id|pos3
op_assign
id|inb
c_func
(paren
id|SK_POS3
)paren
comma
id|pos4
op_assign
id|inb
c_func
(paren
id|SK_POS4
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;## %s: %s.&bslash;n&quot;
l_string|&quot;##   pos0=%#4x pos1=%#4x pos2=%#04x pos3=%#08x pos4=%#04x&bslash;n&quot;
comma
id|SK_NAME
comma
id|text
comma
id|pos0
comma
id|pos1
comma
id|pos2
comma
(paren
id|pos3
op_lshift
l_int|14
)paren
comma
id|pos4
)paren
suffix:semicolon
)brace
multiline_comment|/* End of SK_print_pos() */
"&f;"
multiline_comment|/*-&n; * Function       : SK_print_dev&n; * Author         : Patrick J.D. Weichmann&n; * Date Created   : 94/05/25&n; *&n; * Description    : This function simply prints out the important fields&n; *                  of the device structure.&n; *&n; * Parameters     : I : struct device *dev  - SK_G16 device structure&n; *                  I : char *text - Title for printing&n; * Return Value   : None&n; * Errors         : None&n; * Update History :&n; *     YY/MM/DD  uid  Description&n;-*/
DECL|function|SK_print_dev
r_void
id|SK_print_dev
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_char
op_star
id|text
)paren
(brace
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;## %s: Device Structure. %s&bslash;n&quot;
comma
id|SK_NAME
comma
id|text
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;## DEVICE == NULL&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;## %s: Device Structure. %s&bslash;n&quot;
comma
id|SK_NAME
comma
id|text
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;## Device Name: %s Base Address: %#06x IRQ: %d&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;base_addr
comma
id|dev-&gt;irq
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;##   FLAGS: start: %d tbusy: %d int: %d&bslash;n&quot;
comma
id|dev-&gt;start
comma
id|dev-&gt;tbusy
comma
id|dev-&gt;interrupt
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;## next device: %#08x init function: %#08x&bslash;n&quot;
comma
(paren
r_int
)paren
id|dev-&gt;next
comma
(paren
r_int
)paren
id|dev-&gt;init
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* End of SK_print_dev() */
"&f;"
multiline_comment|/*-&n; * Function       : SK_print_ram&n; * Author         : Patrick J.D. Weichmann&n; * Date Created   : 94/06/02&n; *&n; * Description    : This function is used to check how are things set up&n; *                  in the 16KB RAM. Also the pointers to the receive and &n; *                  transmit descriptor rings and rx and tx buffers locations.&n; *                  It contains a minor bug in printing, but has no effect to the values&n; *                  only newlines are not correct.&n; *&n; * Parameters     : I : struct device *dev - SK_G16 device structure&n; * Return Value   : None&n; * Errors         : None&n; * Globals        : None&n; * Update History :&n; *     YY/MM/DD  uid  Description&n;-*/
DECL|function|SK_print_ram
r_void
id|SK_print_ram
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|priv
op_star
id|p
op_assign
(paren
r_struct
id|priv
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;## %s: RAM Details.&bslash;n&quot;
l_string|&quot;##   RAM at %#08x tmdhead: %#08x rmdhead: %#08x initblock: %#08x&bslash;n&quot;
comma
id|SK_NAME
comma
(paren
r_int
r_int
)paren
id|p-&gt;ram
comma
(paren
r_int
r_int
)paren
id|p-&gt;tmdhead
comma
(paren
r_int
r_int
)paren
id|p-&gt;rmdhead
comma
(paren
r_int
r_int
)paren
op_amp
(paren
id|p-&gt;ram
)paren
op_member_access_from_pointer
id|ib
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;##   &quot;
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
id|TMDNUM
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|i
op_mod
l_int|3
)paren
)paren
multiline_comment|/* Every third line do a newline */
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n##   &quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;tmdbufs%d: %#08x &quot;
comma
(paren
id|i
op_plus
l_int|1
)paren
comma
(paren
r_int
)paren
id|p-&gt;tmdbufs
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;##   &quot;
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
id|RMDNUM
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|i
op_mod
l_int|3
)paren
)paren
multiline_comment|/* Every third line do a newline */
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n##   &quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;rmdbufs%d: %#08x &quot;
comma
(paren
id|i
op_plus
l_int|1
)paren
comma
(paren
r_int
)paren
id|p-&gt;rmdbufs
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* End of SK_print_ram() */
eof
