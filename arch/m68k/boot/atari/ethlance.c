macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &quot;bootp.h&quot;
macro_line|#include &quot;ethlance.h&quot;
r_struct
(brace
DECL|member|memaddr
r_volatile
r_int
r_int
op_star
id|memaddr
suffix:semicolon
DECL|member|ioaddr
r_volatile
r_int
r_int
op_star
id|ioaddr
suffix:semicolon
DECL|variable|lance_addr_list
)brace
id|lance_addr_list
(braket
)braket
op_assign
(brace
(brace
(paren
r_void
op_star
)paren
l_int|0xfe010000
comma
(paren
r_void
op_star
)paren
l_int|0xfe00fff0
)brace
comma
multiline_comment|/* RieblCard VME in TT */
(brace
(paren
r_void
op_star
)paren
l_int|0xfec10000
comma
(paren
r_void
op_star
)paren
l_int|0xfec0fff0
)brace
comma
multiline_comment|/* RieblCard VME in MegaSTE&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;   (highest byte stripped) */
(brace
(paren
r_void
op_star
)paren
l_int|0xfee00000
comma
(paren
r_void
op_star
)paren
l_int|0xfeff7000
)brace
comma
multiline_comment|/* RieblCard in ST&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;   (highest byte stripped) */
(brace
(paren
r_void
op_star
)paren
l_int|0xfecf0000
comma
(paren
r_void
op_star
)paren
l_int|0xfecffff0
)brace
comma
multiline_comment|/* PAMCard VME in TT and MSTE&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;   (highest byte stripped) */
)brace
suffix:semicolon
DECL|macro|N_LANCE_ADDR
mdefine_line|#define&t;N_LANCE_ADDR&t;(sizeof(lance_addr_list)/sizeof(*lance_addr_list))
DECL|macro|TX_RING_SIZE
mdefine_line|#define TX_RING_SIZE&t;&t;&t;1
DECL|macro|TX_RING_LEN_BITS
mdefine_line|#define TX_RING_LEN_BITS&t;&t;0
DECL|macro|RX_RING_SIZE
mdefine_line|#define RX_RING_SIZE&t;&t;&t;16
DECL|macro|RX_RING_LEN_BITS
mdefine_line|#define RX_RING_LEN_BITS&t;&t;(4 &lt;&lt; 5)
DECL|macro|offsetof
mdefine_line|#define&t;offsetof(type,elt)&t;((unsigned long)(&amp;(((type *)0)-&gt;elt)))
multiline_comment|/* The LANCE Rx and Tx ring descriptors. */
DECL|struct|lance_rx_head
r_struct
id|lance_rx_head
(brace
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
multiline_comment|/* Low word of base addr */
DECL|member|flag
r_volatile
r_int
r_char
id|flag
suffix:semicolon
DECL|member|base_hi
r_int
r_char
id|base_hi
suffix:semicolon
multiline_comment|/* High word of base addr (unused) */
DECL|member|buf_length
r_int
id|buf_length
suffix:semicolon
multiline_comment|/* This length is 2s complement! */
DECL|member|msg_length
r_int
id|msg_length
suffix:semicolon
multiline_comment|/* This length is &quot;normal&quot;. */
)brace
suffix:semicolon
DECL|struct|lance_tx_head
r_struct
id|lance_tx_head
(brace
DECL|member|base
r_int
r_int
id|base
suffix:semicolon
multiline_comment|/* Low word of base addr */
DECL|member|flag
r_volatile
r_int
r_char
id|flag
suffix:semicolon
DECL|member|base_hi
r_int
r_char
id|base_hi
suffix:semicolon
multiline_comment|/* High word of base addr (unused) */
DECL|member|length
r_int
id|length
suffix:semicolon
multiline_comment|/* Length is 2s complement! */
DECL|member|misc
r_volatile
r_int
id|misc
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ringdesc
r_struct
id|ringdesc
(brace
DECL|member|adr_lo
r_int
r_int
id|adr_lo
suffix:semicolon
multiline_comment|/* Low 16 bits of address */
DECL|member|len
r_int
r_char
id|len
suffix:semicolon
multiline_comment|/* Length bits */
DECL|member|adr_hi
r_int
r_char
id|adr_hi
suffix:semicolon
multiline_comment|/* High 8 bits of address (unused) */
)brace
suffix:semicolon
DECL|struct|lance_packet
r_struct
id|lance_packet
(brace
DECL|member|data
r_volatile
r_int
r_char
id|data
(braket
id|PKTLEN
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The LANCE initialization block, described in databook. */
DECL|struct|lance_init_block
r_struct
id|lance_init_block
(brace
DECL|member|mode
r_int
r_int
id|mode
suffix:semicolon
multiline_comment|/* Pre-set mode */
DECL|member|hwaddr
r_int
r_char
id|hwaddr
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* Physical ethernet address */
DECL|member|filter
r_int
id|filter
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Multicast filter (unused). */
multiline_comment|/* Receive and transmit ring base, along with length bits. */
DECL|member|rx_ring
r_struct
id|ringdesc
id|rx_ring
suffix:semicolon
DECL|member|tx_ring
r_struct
id|ringdesc
id|tx_ring
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The whole layout of the Lance shared memory */
DECL|struct|lance_memory
r_struct
id|lance_memory
(brace
DECL|member|init
r_struct
id|lance_init_block
id|init
suffix:semicolon
DECL|member|tx_head
r_struct
id|lance_tx_head
id|tx_head
(braket
id|TX_RING_SIZE
)braket
suffix:semicolon
DECL|member|rx_head
r_struct
id|lance_rx_head
id|rx_head
(braket
id|RX_RING_SIZE
)braket
suffix:semicolon
DECL|member|tx_packet
r_struct
id|lance_packet
id|tx_packet
(braket
id|TX_RING_SIZE
)braket
suffix:semicolon
DECL|member|rx_packet
r_struct
id|lance_packet
id|rx_packet
(braket
id|TX_RING_SIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|RIEBL_MAGIC
mdefine_line|#define RIEBL_MAGIC&t;&t;&t;0x09051990
DECL|macro|RIEBL_MAGIC_ADDR
mdefine_line|#define RIEBL_MAGIC_ADDR&t;((unsigned long *)(((char *)MEM) + 0xee8a))
DECL|macro|RIEBL_HWADDR_ADDR
mdefine_line|#define RIEBL_HWADDR_ADDR&t;((unsigned char *)(((char *)MEM) + 0xee8e))
DECL|macro|RIEBL_IVEC_ADDR
mdefine_line|#define RIEBL_IVEC_ADDR&t;&t;((unsigned short *)(((char *)MEM) + 0xfffe))
DECL|struct|lance_ioreg
r_struct
id|lance_ioreg
(brace
DECL|member|data
multiline_comment|/* base+0x0 */
r_volatile
r_int
r_int
id|data
suffix:semicolon
DECL|member|addr
multiline_comment|/* base+0x2 */
r_volatile
r_int
r_int
id|addr
suffix:semicolon
DECL|member|_dummy1
r_int
r_char
id|_dummy1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|ivec
multiline_comment|/* base+0x7 */
r_volatile
r_int
r_char
id|ivec
suffix:semicolon
DECL|member|_dummy2
r_int
r_char
id|_dummy2
(braket
l_int|5
)braket
suffix:semicolon
DECL|member|eeprom
multiline_comment|/* base+0xd */
r_volatile
r_int
r_char
id|eeprom
suffix:semicolon
DECL|member|_dummy3
r_int
r_char
id|_dummy3
suffix:semicolon
DECL|member|mem
multiline_comment|/* base+0xf */
r_volatile
r_int
r_char
id|mem
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|lance_type
r_enum
id|lance_type
(brace
DECL|enumerator|OLD_RIEBL
id|OLD_RIEBL
comma
multiline_comment|/* old Riebl card without battery */
DECL|enumerator|NEW_RIEBL
id|NEW_RIEBL
comma
multiline_comment|/* new Riebl card with battery */
DECL|enumerator|PAM_CARD
id|PAM_CARD
multiline_comment|/* PAM card with EEPROM */
DECL|variable|CardType
)brace
id|CardType
suffix:semicolon
DECL|variable|dev_addr
id|HWADDR
id|dev_addr
suffix:semicolon
multiline_comment|/* This is a default address for the old RieblCards without a battery&n; * that have no ethernet address at boot time. 00:00:36:04 is the&n; * prefix for Riebl cards, the 00:00 at the end is arbitrary.&n; */
DECL|variable|OldRieblDefHwaddr
id|HWADDR
id|OldRieblDefHwaddr
op_assign
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x36
comma
l_int|0x04
comma
l_int|0x00
comma
l_int|0x00
)brace
suffix:semicolon
DECL|variable|IO
r_struct
id|lance_ioreg
op_star
id|IO
suffix:semicolon
DECL|variable|MEM
r_struct
id|lance_memory
op_star
id|MEM
suffix:semicolon
DECL|macro|DREG
mdefine_line|#define&t;DREG&t;IO-&gt;data
DECL|macro|AREG
mdefine_line|#define&t;AREG&t;IO-&gt;addr
DECL|macro|REGA
mdefine_line|#define&t;REGA(a)&t;( AREG = (a), DREG )
DECL|variable|CurRx
r_int
id|CurRx
suffix:semicolon
multiline_comment|/* Definitions for the Lance */
multiline_comment|/* tx_head flags */
DECL|macro|TMD1_ENP
mdefine_line|#define&t;TMD1_ENP&t;&t;0x01
DECL|macro|TMD1_STP
mdefine_line|#define TMD1_STP&t;&t;0x02
DECL|macro|TMD1_DEF
mdefine_line|#define&t;TMD1_DEF&t;&t;0x04
DECL|macro|TMD1_ONE
mdefine_line|#define TMD1_ONE&t;&t;0x08
DECL|macro|TMD1_MORE
mdefine_line|#define&t;TMD1_MORE&t;&t;0x10
DECL|macro|TMD1_ERR
mdefine_line|#define&t;TMD1_ERR&t;&t;0x40
DECL|macro|TMD1_OWN
mdefine_line|#define TMD1_OWN &t;&t;0x80
DECL|macro|TMD1_OWN_CHIP
mdefine_line|#define TMD1_OWN_CHIP&t;TMD1_OWN
DECL|macro|TMD1_OWN_HOST
mdefine_line|#define TMD1_OWN_HOST&t;0
multiline_comment|/* tx_head misc field */
DECL|macro|TMD3_TDR
mdefine_line|#define TMD3_TDR&t;&t;0x03FF
DECL|macro|TMD3_RTRY
mdefine_line|#define TMD3_RTRY&t;&t;0x0400
DECL|macro|TMD3_LCAR
mdefine_line|#define TMD3_LCAR&t;&t;0x0800
DECL|macro|TMD3_LCOL
mdefine_line|#define TMD3_LCOL&t;&t;0x1000
DECL|macro|TMD3_UFLO
mdefine_line|#define TMD3_UFLO&t;&t;0x4000
DECL|macro|TMD3_BUFF3
mdefine_line|#define TMD3_BUFF3&t;&t;0x8000
multiline_comment|/* rx_head flags */
DECL|macro|RMD1_ENP
mdefine_line|#define&t;RMD1_ENP&t;&t;0x01
DECL|macro|RMD1_STP
mdefine_line|#define RMD1_STP&t;&t;0x02
DECL|macro|RMD1_BUFF
mdefine_line|#define RMD1_BUFF&t;&t;0x04
DECL|macro|RMD1_CRC
mdefine_line|#define RMD1_CRC&t;&t;0x08
DECL|macro|RMD1_OFLO
mdefine_line|#define RMD1_OFLO&t;&t;0x10
DECL|macro|RMD1_FRAM
mdefine_line|#define RMD1_FRAM&t;&t;0x20
DECL|macro|RMD1_ERR
mdefine_line|#define&t;RMD1_ERR&t;&t;0x40
DECL|macro|RMD1_OWN
mdefine_line|#define RMD1_OWN &t;&t;0x80
DECL|macro|RMD1_OWN_CHIP
mdefine_line|#define RMD1_OWN_CHIP&t;RMD1_OWN
DECL|macro|RMD1_OWN_HOST
mdefine_line|#define RMD1_OWN_HOST&t;0
multiline_comment|/* register names */
DECL|macro|CSR0
mdefine_line|#define CSR0&t;0
DECL|macro|CSR1
mdefine_line|#define CSR1&t;1
DECL|macro|CSR2
mdefine_line|#define CSR2&t;2
DECL|macro|CSR3
mdefine_line|#define CSR3&t;3
multiline_comment|/* CSR0 */
DECL|macro|CSR0_INIT
mdefine_line|#define CSR0_INIT&t;0x0001&t;&t;/* initialize */
DECL|macro|CSR0_STRT
mdefine_line|#define CSR0_STRT&t;0x0002&t;&t;/* start */
DECL|macro|CSR0_STOP
mdefine_line|#define CSR0_STOP&t;0x0004&t;&t;/* stop */
DECL|macro|CSR0_TDMD
mdefine_line|#define CSR0_TDMD&t;0x0008&t;&t;/* transmit demand */
DECL|macro|CSR0_TXON
mdefine_line|#define CSR0_TXON&t;0x0010&t;&t;/* transmitter on */
DECL|macro|CSR0_RXON
mdefine_line|#define CSR0_RXON&t;0x0020&t;&t;/* receiver on */
DECL|macro|CSR0_INEA
mdefine_line|#define CSR0_INEA&t;0x0040&t;&t;/* interrupt enable */
DECL|macro|CSR0_INTR
mdefine_line|#define CSR0_INTR&t;0x0080&t;&t;/* interrupt active */
DECL|macro|CSR0_IDON
mdefine_line|#define CSR0_IDON&t;0x0100&t;&t;/* initialization done */
DECL|macro|CSR0_TINT
mdefine_line|#define CSR0_TINT&t;0x0200&t;&t;/* transmitter interrupt */
DECL|macro|CSR0_RINT
mdefine_line|#define CSR0_RINT&t;0x0400&t;&t;/* receiver interrupt */
DECL|macro|CSR0_MERR
mdefine_line|#define CSR0_MERR&t;0x0800&t;&t;/* memory error */
DECL|macro|CSR0_MISS
mdefine_line|#define CSR0_MISS&t;0x1000&t;&t;/* missed frame */
DECL|macro|CSR0_CERR
mdefine_line|#define CSR0_CERR&t;0x2000&t;&t;/* carrier error (no heartbeat :-) */
DECL|macro|CSR0_BABL
mdefine_line|#define CSR0_BABL&t;0x4000&t;&t;/* babble: tx-ed too many bits */
DECL|macro|CSR0_ERR
mdefine_line|#define CSR0_ERR&t;0x8000&t;&t;/* error */
multiline_comment|/* CSR3 */
DECL|macro|CSR3_BCON
mdefine_line|#define CSR3_BCON&t;0x0001
DECL|macro|CSR3_ACON
mdefine_line|#define CSR3_ACON&t;0x0002
DECL|macro|CSR3_BSWP
mdefine_line|#define CSR3_BSWP&t;0x0004
DECL|macro|HZ
mdefine_line|#define&t;HZ&t;200
DECL|macro|_hz_200
mdefine_line|#define&t;_hz_200&t;(*(volatile unsigned long *)0x4ba)
multiline_comment|/***************************** Prototypes *****************************/
r_static
r_int
id|lance_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|addr_readable
c_func
(paren
r_volatile
r_void
op_star
id|regp
comma
r_int
id|wordflag
)paren
suffix:semicolon
r_static
r_int
id|lance_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|lance_get_hwaddr
c_func
(paren
id|HWADDR
op_star
id|addr
)paren
suffix:semicolon
r_static
r_int
id|lance_snd
c_func
(paren
id|Packet
op_star
id|pkt
comma
r_int
id|len
)paren
suffix:semicolon
r_static
r_int
id|lance_rcv
c_func
(paren
id|Packet
op_star
id|pkt
comma
r_int
op_star
id|len
)paren
suffix:semicolon
multiline_comment|/************************* End of Prototypes **************************/
DECL|variable|LanceSwitch
id|ETHIF_SWITCH
id|LanceSwitch
op_assign
(brace
id|lance_probe
comma
id|lance_init
comma
id|lance_get_hwaddr
comma
id|lance_snd
comma
id|lance_rcv
)brace
suffix:semicolon
DECL|function|lance_probe
r_static
r_int
id|lance_probe
c_func
(paren
r_void
)paren
(brace
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
id|N_LANCE_ADDR
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|addr_readable
c_func
(paren
id|lance_addr_list
(braket
id|i
)braket
dot
id|memaddr
comma
l_int|1
)paren
op_logical_and
(paren
id|lance_addr_list
(braket
id|i
)braket
dot
id|memaddr
(braket
l_int|0
)braket
op_assign
l_int|1
comma
id|lance_addr_list
(braket
id|i
)braket
dot
id|memaddr
(braket
l_int|0
)braket
op_eq
l_int|1
)paren
op_logical_and
(paren
id|lance_addr_list
(braket
id|i
)braket
dot
id|memaddr
(braket
l_int|0
)braket
op_assign
l_int|0
comma
id|lance_addr_list
(braket
id|i
)braket
dot
id|memaddr
(braket
l_int|0
)braket
op_eq
l_int|0
)paren
op_logical_and
id|addr_readable
c_func
(paren
id|lance_addr_list
(braket
id|i
)braket
dot
id|ioaddr
comma
l_int|1
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|i
op_eq
id|N_LANCE_ADDR
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|IO
op_assign
(paren
r_struct
id|lance_ioreg
op_star
)paren
id|lance_addr_list
(braket
id|i
)braket
dot
id|ioaddr
suffix:semicolon
id|MEM
op_assign
(paren
r_struct
id|lance_memory
op_star
)paren
id|lance_addr_list
(braket
id|i
)braket
dot
id|memaddr
suffix:semicolon
id|REGA
c_func
(paren
id|CSR0
)paren
op_assign
id|CSR0_STOP
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|addr_readable
r_static
r_int
id|addr_readable
c_func
(paren
r_volatile
r_void
op_star
id|regp
comma
r_int
id|wordflag
)paren
(brace
r_int
id|ret
suffix:semicolon
r_int
op_star
id|vbr
comma
id|save_berr
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;movec&t;%/vbr,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|vbr
)paren
suffix:colon
)paren
suffix:semicolon
id|save_berr
op_assign
id|vbr
(braket
l_int|2
)braket
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;movel&t;%/sp,%/d1&bslash;n&bslash;t&quot;
l_string|&quot;movel&t;#Lberr,%2@&bslash;n&bslash;t&quot;
l_string|&quot;moveq&t;#0,%0&bslash;n&bslash;t&quot;
l_string|&quot;tstl   %3&bslash;n&bslash;t&quot;
l_string|&quot;bne&t;1f&bslash;n&bslash;t&quot;
l_string|&quot;tstb&t;%1@&bslash;n&bslash;t&quot;
l_string|&quot;bra&t;2f&bslash;n&quot;
l_string|&quot;1:&t;&t; tstw&t;%1@&bslash;n&quot;
l_string|&quot;2:&t;&t; moveq&t;#1,%0&bslash;n&quot;
l_string|&quot;Lberr:&t; movel&t;%/d1,%/sp&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|regp
)paren
comma
l_string|&quot;a&quot;
(paren
op_amp
id|vbr
(braket
l_int|2
)braket
)paren
comma
l_string|&quot;rm&quot;
(paren
id|wordflag
)paren
suffix:colon
l_string|&quot;d1&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|vbr
(braket
l_int|2
)braket
op_assign
id|save_berr
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|lance_init
r_static
r_int
id|lance_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Now test for type: If the eeprom I/O port is readable, it is a&n;&t; * PAM card */
r_if
c_cond
(paren
id|addr_readable
c_func
(paren
op_amp
(paren
id|IO-&gt;eeprom
)paren
comma
l_int|0
)paren
)paren
(brace
multiline_comment|/* Switch back to Ram */
id|i
op_assign
id|IO-&gt;mem
suffix:semicolon
id|CardType
op_assign
id|PAM_CARD
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|RIEBL_MAGIC_ADDR
op_eq
id|RIEBL_MAGIC
)paren
(brace
id|CardType
op_assign
id|NEW_RIEBL
suffix:semicolon
)brace
r_else
id|CardType
op_assign
id|OLD_RIEBL
suffix:semicolon
multiline_comment|/* Get the ethernet address */
r_switch
c_cond
(paren
id|CardType
)paren
(brace
r_case
id|OLD_RIEBL
suffix:colon
multiline_comment|/* No ethernet address! (Set some default address) */
id|memcpy
c_func
(paren
id|dev_addr
comma
id|OldRieblDefHwaddr
comma
id|ETHADDRLEN
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NEW_RIEBL
suffix:colon
id|memcpy
c_func
(paren
id|dev_addr
comma
id|RIEBL_HWADDR_ADDR
comma
id|ETHADDRLEN
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PAM_CARD
suffix:colon
id|i
op_assign
id|IO-&gt;eeprom
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
id|ETHADDRLEN
suffix:semicolon
op_increment
id|i
)paren
(brace
id|dev_addr
(braket
id|i
)braket
op_assign
(paren
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|MEM
)paren
(braket
id|i
op_star
l_int|2
)braket
op_amp
l_int|0x0f
)paren
op_lshift
l_int|4
)paren
op_or
(paren
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|MEM
)paren
(braket
id|i
op_star
l_int|2
op_plus
l_int|1
)braket
op_amp
l_int|0x0f
)paren
)paren
suffix:semicolon
)brace
id|i
op_assign
id|IO-&gt;mem
suffix:semicolon
r_break
suffix:semicolon
)brace
id|MEM-&gt;init.mode
op_assign
l_int|0x0000
suffix:semicolon
multiline_comment|/* Disable Rx and Tx. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ETHADDRLEN
suffix:semicolon
id|i
op_increment
)paren
(brace
id|MEM-&gt;init.hwaddr
(braket
id|i
)braket
op_assign
id|dev_addr
(braket
id|i
op_xor
l_int|1
)braket
suffix:semicolon
)brace
multiline_comment|/* &lt;- 16 bit swap! */
id|MEM-&gt;init.filter
(braket
l_int|0
)braket
op_assign
l_int|0x00000000
suffix:semicolon
id|MEM-&gt;init.filter
(braket
l_int|1
)braket
op_assign
l_int|0x00000000
suffix:semicolon
id|MEM-&gt;init.rx_ring.adr_lo
op_assign
m_offsetof
(paren
r_struct
id|lance_memory
comma
id|rx_head
)paren
suffix:semicolon
id|MEM-&gt;init.rx_ring.adr_hi
op_assign
l_int|0
suffix:semicolon
id|MEM-&gt;init.rx_ring.len
op_assign
id|RX_RING_LEN_BITS
suffix:semicolon
id|MEM-&gt;init.tx_ring.adr_lo
op_assign
m_offsetof
(paren
r_struct
id|lance_memory
comma
id|tx_head
)paren
suffix:semicolon
id|MEM-&gt;init.tx_ring.adr_hi
op_assign
l_int|0
suffix:semicolon
id|MEM-&gt;init.tx_ring.len
op_assign
id|TX_RING_LEN_BITS
suffix:semicolon
id|REGA
c_func
(paren
id|CSR3
)paren
op_assign
id|CSR3_BSWP
op_or
(paren
id|CardType
op_eq
id|PAM_CARD
ques
c_cond
id|CSR3_ACON
suffix:colon
l_int|0
)paren
suffix:semicolon
id|REGA
c_func
(paren
id|CSR2
)paren
op_assign
l_int|0
suffix:semicolon
id|REGA
c_func
(paren
id|CSR1
)paren
op_assign
l_int|0
suffix:semicolon
id|REGA
c_func
(paren
id|CSR0
)paren
op_assign
id|CSR0_INIT
op_or
id|CSR0_STRT
suffix:semicolon
id|i
op_assign
l_int|1000000
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
OG
l_int|0
)paren
r_if
c_cond
(paren
id|DREG
op_amp
id|CSR0_IDON
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
op_logical_or
(paren
id|DREG
op_amp
id|CSR0_ERR
)paren
)paren
(brace
id|DREG
op_assign
id|CSR0_STOP
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|DREG
op_assign
id|CSR0_IDON
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
id|TX_RING_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|MEM-&gt;tx_head
(braket
id|i
)braket
dot
id|base
op_assign
m_offsetof
(paren
r_struct
id|lance_memory
comma
id|tx_packet
(braket
id|i
)braket
)paren
suffix:semicolon
id|MEM-&gt;tx_head
(braket
id|i
)braket
dot
id|flag
op_assign
id|TMD1_OWN_HOST
suffix:semicolon
id|MEM-&gt;tx_head
(braket
id|i
)braket
dot
id|base_hi
op_assign
l_int|0
suffix:semicolon
id|MEM-&gt;tx_head
(braket
id|i
)braket
dot
id|length
op_assign
l_int|0
suffix:semicolon
id|MEM-&gt;tx_head
(braket
id|i
)braket
dot
id|misc
op_assign
l_int|0
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
id|RX_RING_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|MEM-&gt;rx_head
(braket
id|i
)braket
dot
id|base
op_assign
m_offsetof
(paren
r_struct
id|lance_memory
comma
id|rx_packet
(braket
id|i
)braket
)paren
suffix:semicolon
id|MEM-&gt;rx_head
(braket
id|i
)braket
dot
id|flag
op_assign
id|TMD1_OWN_CHIP
suffix:semicolon
id|MEM-&gt;rx_head
(braket
id|i
)braket
dot
id|base_hi
op_assign
l_int|0
suffix:semicolon
id|MEM-&gt;rx_head
(braket
id|i
)braket
dot
id|buf_length
op_assign
op_minus
id|PKTLEN
suffix:semicolon
id|MEM-&gt;rx_head
(braket
id|i
)braket
dot
id|msg_length
op_assign
l_int|0
suffix:semicolon
)brace
id|CurRx
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lance_get_hwaddr
r_static
r_void
id|lance_get_hwaddr
c_func
(paren
id|HWADDR
op_star
id|addr
)paren
(brace
id|memcpy
c_func
(paren
id|addr
comma
id|dev_addr
comma
id|ETHADDRLEN
)paren
suffix:semicolon
)brace
DECL|function|lance_snd
r_static
r_int
id|lance_snd
c_func
(paren
id|Packet
op_star
id|pkt
comma
r_int
id|len
)paren
(brace
r_int
r_int
id|timeout
suffix:semicolon
multiline_comment|/* The old LANCE chips doesn&squot;t automatically pad buffers to min. size. */
id|len
op_assign
(paren
id|len
OL
l_int|60
)paren
ques
c_cond
l_int|60
suffix:colon
id|len
suffix:semicolon
multiline_comment|/* PAM-Card has a bug: Can only send packets with even number of bytes! */
r_if
c_cond
(paren
id|CardType
op_eq
id|PAM_CARD
op_logical_and
(paren
id|len
op_amp
l_int|1
)paren
)paren
op_increment
id|len
suffix:semicolon
id|MEM-&gt;tx_head
(braket
l_int|0
)braket
dot
id|length
op_assign
op_minus
id|len
suffix:semicolon
id|MEM-&gt;tx_head
(braket
l_int|0
)braket
dot
id|misc
op_assign
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
id|MEM-&gt;tx_packet
(braket
l_int|0
)braket
dot
id|data
comma
id|pkt
comma
id|len
)paren
suffix:semicolon
id|MEM-&gt;tx_head
(braket
l_int|0
)braket
dot
id|base
op_assign
m_offsetof
(paren
r_struct
id|lance_memory
comma
id|tx_packet
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|MEM-&gt;tx_head
(braket
l_int|0
)braket
dot
id|base_hi
op_assign
l_int|0
suffix:semicolon
id|MEM-&gt;tx_head
(braket
l_int|0
)braket
dot
id|flag
op_assign
id|TMD1_OWN_CHIP
op_or
id|TMD1_ENP
op_or
id|TMD1_STP
suffix:semicolon
multiline_comment|/* Trigger an immediate send poll. */
id|REGA
c_func
(paren
id|CSR0
)paren
op_assign
id|CSR0_TDMD
suffix:semicolon
multiline_comment|/* Wait for packet being sent */
id|timeout
op_assign
id|_hz_200
op_plus
l_int|3
op_star
id|HZ
suffix:semicolon
r_while
c_loop
(paren
(paren
id|MEM-&gt;tx_head
(braket
l_int|0
)braket
dot
id|flag
op_amp
id|TMD1_OWN_CHIP
)paren
op_logical_and
op_logical_neg
id|MEM-&gt;tx_head
(braket
l_int|0
)braket
dot
id|misc
op_logical_and
id|_hz_200
OL
id|timeout
)paren
(brace
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|MEM-&gt;tx_head
(braket
l_int|0
)braket
dot
id|flag
op_amp
id|TMD1_OWN
)paren
op_eq
id|TMD1_OWN_HOST
op_logical_and
op_logical_neg
(paren
id|MEM-&gt;tx_head
(braket
l_int|0
)braket
dot
id|misc
op_amp
id|TMD1_ERR
)paren
)paren
multiline_comment|/* sent ok */
r_return
l_int|0
suffix:semicolon
multiline_comment|/* failure */
r_if
c_cond
(paren
id|_hz_200
op_ge
id|timeout
)paren
r_return
id|ETIMEO
suffix:semicolon
r_if
c_cond
(paren
id|MEM-&gt;tx_head
(braket
l_int|0
)braket
dot
id|misc
op_amp
id|TMD3_UFLO
)paren
(brace
multiline_comment|/* On FIFO errors, must re-turn on TX! */
id|DREG
op_assign
id|CSR0_STRT
suffix:semicolon
)brace
r_return
id|ESEND
suffix:semicolon
)brace
DECL|function|lance_rcv
r_static
r_int
id|lance_rcv
c_func
(paren
id|Packet
op_star
id|pkt
comma
r_int
op_star
id|len
)paren
(brace
r_int
r_int
id|timeout
suffix:semicolon
r_int
id|stat
suffix:semicolon
multiline_comment|/* Wait for a packet */
id|timeout
op_assign
id|_hz_200
op_plus
l_int|4
op_star
id|HZ
suffix:semicolon
r_while
c_loop
(paren
(paren
id|MEM-&gt;rx_head
(braket
id|CurRx
)braket
dot
id|flag
op_amp
id|TMD1_OWN_CHIP
)paren
op_logical_and
id|_hz_200
OL
id|timeout
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* Not ours -&gt; was a timeout */
r_if
c_cond
(paren
(paren
(paren
id|stat
op_assign
id|MEM-&gt;rx_head
(braket
id|CurRx
)braket
dot
id|flag
)paren
op_amp
id|TMD1_OWN
)paren
op_eq
id|TMD1_OWN_CHIP
)paren
r_return
id|ETIMEO
suffix:semicolon
multiline_comment|/* Check for errors */
r_if
c_cond
(paren
id|stat
op_ne
(paren
id|RMD1_ENP
op_or
id|RMD1_STP
)paren
)paren
(brace
id|MEM-&gt;rx_head
(braket
id|CurRx
)braket
dot
id|flag
op_and_assign
(paren
id|RMD1_ENP
op_or
id|RMD1_STP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|RMD1_FRAM
)paren
r_return
id|EFRAM
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|RMD1_OFLO
)paren
r_return
id|EOVERFL
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|RMD1_CRC
)paren
r_return
id|ECRC
suffix:semicolon
r_return
id|ERCV
suffix:semicolon
)brace
multiline_comment|/* Get the packet */
op_star
id|len
op_assign
id|MEM-&gt;rx_head
(braket
id|CurRx
)braket
dot
id|msg_length
op_amp
l_int|0xfff
suffix:semicolon
id|memcpy
c_func
(paren
id|pkt
comma
(paren
r_void
op_star
)paren
op_amp
id|MEM-&gt;rx_packet
(braket
id|CurRx
)braket
dot
id|data
comma
op_star
id|len
)paren
suffix:semicolon
multiline_comment|/* Give the buffer back to the chip */
id|MEM-&gt;rx_head
(braket
id|CurRx
)braket
dot
id|buf_length
op_assign
op_minus
id|PKTLEN
suffix:semicolon
id|MEM-&gt;rx_head
(braket
id|CurRx
)braket
dot
id|flag
op_or_assign
id|RMD1_OWN_CHIP
suffix:semicolon
id|CurRx
op_assign
(paren
id|CurRx
op_plus
l_int|1
)paren
op_mod
id|RX_RING_SIZE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof