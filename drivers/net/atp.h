multiline_comment|/* Linux header file for the ATP pocket ethernet adapter. */
multiline_comment|/* v1.09 8/9/2000 becker@scyld.com. */
macro_line|#include &lt;linux/if_ether.h&gt;
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* The header prepended to received packets. */
DECL|struct|rx_header
r_struct
id|rx_header
(brace
DECL|member|pad
id|ushort
id|pad
suffix:semicolon
multiline_comment|/* Pad. */
DECL|member|rx_count
id|ushort
id|rx_count
suffix:semicolon
DECL|member|rx_status
id|ushort
id|rx_status
suffix:semicolon
multiline_comment|/* Unknown bit assignments :-&lt;.  */
DECL|member|cur_addr
id|ushort
id|cur_addr
suffix:semicolon
multiline_comment|/* Apparently the current buffer address(?) */
)brace
suffix:semicolon
DECL|macro|PAR_DATA
mdefine_line|#define PAR_DATA&t;0
DECL|macro|PAR_STATUS
mdefine_line|#define PAR_STATUS&t;1
DECL|macro|PAR_CONTROL
mdefine_line|#define PAR_CONTROL 2
DECL|enum|chip_type
DECL|enumerator|RTL8002
DECL|enumerator|RTL8012
r_enum
id|chip_type
(brace
id|RTL8002
comma
id|RTL8012
)brace
suffix:semicolon
DECL|macro|Ctrl_LNibRead
mdefine_line|#define Ctrl_LNibRead&t;0x08&t;/* LP_PSELECP */
DECL|macro|Ctrl_HNibRead
mdefine_line|#define Ctrl_HNibRead&t;0
DECL|macro|Ctrl_LNibWrite
mdefine_line|#define Ctrl_LNibWrite&t;0x08&t;/* LP_PSELECP */
DECL|macro|Ctrl_HNibWrite
mdefine_line|#define Ctrl_HNibWrite&t;0
DECL|macro|Ctrl_SelData
mdefine_line|#define Ctrl_SelData&t;0x04&t;/* LP_PINITP */
DECL|macro|Ctrl_IRQEN
mdefine_line|#define Ctrl_IRQEN&t;0x10&t;/* LP_PINTEN */
DECL|macro|EOW
mdefine_line|#define EOW&t;0xE0
DECL|macro|EOC
mdefine_line|#define EOC&t;0xE0
DECL|macro|WrAddr
mdefine_line|#define WrAddr&t;0x40&t;/* Set address of EPLC read, write register. */
DECL|macro|RdAddr
mdefine_line|#define RdAddr&t;0xC0
DECL|macro|HNib
mdefine_line|#define HNib&t;0x10
DECL|enum|page0_regs
r_enum
id|page0_regs
(brace
multiline_comment|/* The first six registers hold the ethernet physical station address. */
DECL|enumerator|PAR0
DECL|enumerator|PAR1
DECL|enumerator|PAR2
DECL|enumerator|PAR3
DECL|enumerator|PAR4
DECL|enumerator|PAR5
id|PAR0
op_assign
l_int|0
comma
id|PAR1
op_assign
l_int|1
comma
id|PAR2
op_assign
l_int|2
comma
id|PAR3
op_assign
l_int|3
comma
id|PAR4
op_assign
l_int|4
comma
id|PAR5
op_assign
l_int|5
comma
DECL|enumerator|TxCNT0
DECL|enumerator|TxCNT1
id|TxCNT0
op_assign
l_int|6
comma
id|TxCNT1
op_assign
l_int|7
comma
multiline_comment|/* The transmit byte count. */
DECL|enumerator|TxSTAT
DECL|enumerator|RxSTAT
id|TxSTAT
op_assign
l_int|8
comma
id|RxSTAT
op_assign
l_int|9
comma
multiline_comment|/* Tx and Rx status. */
DECL|enumerator|ISR
DECL|enumerator|IMR
id|ISR
op_assign
l_int|10
comma
id|IMR
op_assign
l_int|11
comma
multiline_comment|/* Interrupt status and mask. */
DECL|enumerator|CMR1
id|CMR1
op_assign
l_int|12
comma
multiline_comment|/* Command register 1. */
DECL|enumerator|CMR2
id|CMR2
op_assign
l_int|13
comma
multiline_comment|/* Command register 2. */
DECL|enumerator|MODSEL
id|MODSEL
op_assign
l_int|14
comma
multiline_comment|/* Mode select register. */
DECL|enumerator|MAR
id|MAR
op_assign
l_int|14
comma
multiline_comment|/* Memory address register (?). */
DECL|enumerator|CMR2_h
id|CMR2_h
op_assign
l_int|0x1d
comma
)brace
suffix:semicolon
DECL|enum|eepage_regs
r_enum
id|eepage_regs
DECL|enumerator|PROM_CMD
DECL|enumerator|PROM_DATA
(brace
id|PROM_CMD
op_assign
l_int|6
comma
id|PROM_DATA
op_assign
l_int|7
)brace
suffix:semicolon
multiline_comment|/* Note that PROM_CMD is in the &quot;high&quot; bits. */
DECL|macro|ISR_TxOK
mdefine_line|#define ISR_TxOK&t;0x01
DECL|macro|ISR_RxOK
mdefine_line|#define ISR_RxOK&t;0x04
DECL|macro|ISR_TxErr
mdefine_line|#define ISR_TxErr&t;0x02
DECL|macro|ISRh_RxErr
mdefine_line|#define ISRh_RxErr&t;0x11&t;/* ISR, high nibble */
DECL|macro|CMR1h_MUX
mdefine_line|#define CMR1h_MUX&t;0x08&t;/* Select printer multiplexor on 8012. */
DECL|macro|CMR1h_RESET
mdefine_line|#define CMR1h_RESET&t;0x04&t;/* Reset. */
DECL|macro|CMR1h_RxENABLE
mdefine_line|#define CMR1h_RxENABLE&t;0x02&t;/* Rx unit enable.  */
DECL|macro|CMR1h_TxENABLE
mdefine_line|#define CMR1h_TxENABLE&t;0x01&t;/* Tx unit enable.  */
DECL|macro|CMR1h_TxRxOFF
mdefine_line|#define CMR1h_TxRxOFF&t;0x00
DECL|macro|CMR1_ReXmit
mdefine_line|#define CMR1_ReXmit&t;0x08&t;/* Trigger a retransmit. */
DECL|macro|CMR1_Xmit
mdefine_line|#define CMR1_Xmit&t;0x04&t;/* Trigger a transmit. */
DECL|macro|CMR1_IRQ
mdefine_line|#define&t;CMR1_IRQ&t;0x02&t;/* Interrupt active. */
DECL|macro|CMR1_BufEnb
mdefine_line|#define&t;CMR1_BufEnb&t;0x01&t;/* Enable the buffer(?). */
DECL|macro|CMR1_NextPkt
mdefine_line|#define&t;CMR1_NextPkt&t;0x01&t;/* Enable the buffer(?). */
DECL|macro|CMR2_NULL
mdefine_line|#define CMR2_NULL&t;8
DECL|macro|CMR2_IRQOUT
mdefine_line|#define CMR2_IRQOUT&t;9
DECL|macro|CMR2_RAMTEST
mdefine_line|#define CMR2_RAMTEST&t;10
DECL|macro|CMR2_EEPROM
mdefine_line|#define CMR2_EEPROM&t;12&t;/* Set to page 1, for reading the EEPROM. */
DECL|macro|CMR2h_OFF
mdefine_line|#define CMR2h_OFF&t;0&t;/* No accept mode. */
DECL|macro|CMR2h_Physical
mdefine_line|#define CMR2h_Physical&t;1&t;/* Accept a physical address match only. */
DECL|macro|CMR2h_Normal
mdefine_line|#define CMR2h_Normal&t;2&t;/* Accept physical and broadcast address. */
DECL|macro|CMR2h_PROMISC
mdefine_line|#define CMR2h_PROMISC&t;3&t;/* Promiscuous mode. */
multiline_comment|/* An inline function used below: it differs from inb() by explicitly return an unsigned&n;   char, saving a truncation. */
DECL|function|inbyte
r_static
r_inline
r_int
r_char
id|inbyte
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_int
r_char
id|_v
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;inb %w1,%b0&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|_v
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|port
)paren
)paren
suffix:semicolon
r_return
id|_v
suffix:semicolon
)brace
multiline_comment|/* Read register OFFSET.&n;   This command should always be terminated with read_end(). */
DECL|function|read_nibble
r_static
r_inline
r_int
r_char
id|read_nibble
c_func
(paren
r_int
id|port
comma
r_int
r_char
id|offset
)paren
(brace
r_int
r_char
id|retval
suffix:semicolon
id|outb
c_func
(paren
id|EOC
op_plus
id|offset
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|outb
c_func
(paren
id|RdAddr
op_plus
id|offset
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|inbyte
c_func
(paren
id|port
op_plus
id|PAR_STATUS
)paren
suffix:semicolon
multiline_comment|/* Settling time delay */
id|retval
op_assign
id|inbyte
c_func
(paren
id|port
op_plus
id|PAR_STATUS
)paren
suffix:semicolon
id|outb
c_func
(paren
id|EOC
op_plus
id|offset
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Functions for bulk data read.  The interrupt line is always disabled. */
multiline_comment|/* Get a byte using read mode 0, reading data from the control lines. */
DECL|function|read_byte_mode0
r_static
r_inline
r_int
r_char
id|read_byte_mode0
c_func
(paren
r_int
id|ioaddr
)paren
(brace
r_int
r_char
id|low_nib
suffix:semicolon
id|outb
c_func
(paren
id|Ctrl_LNibRead
comma
id|ioaddr
op_plus
id|PAR_CONTROL
)paren
suffix:semicolon
id|inbyte
c_func
(paren
id|ioaddr
op_plus
id|PAR_STATUS
)paren
suffix:semicolon
id|low_nib
op_assign
(paren
id|inbyte
c_func
(paren
id|ioaddr
op_plus
id|PAR_STATUS
)paren
op_rshift
l_int|3
)paren
op_amp
l_int|0x0f
suffix:semicolon
id|outb
c_func
(paren
id|Ctrl_HNibRead
comma
id|ioaddr
op_plus
id|PAR_CONTROL
)paren
suffix:semicolon
id|inbyte
c_func
(paren
id|ioaddr
op_plus
id|PAR_STATUS
)paren
suffix:semicolon
multiline_comment|/* Settling time delay -- needed!  */
id|inbyte
c_func
(paren
id|ioaddr
op_plus
id|PAR_STATUS
)paren
suffix:semicolon
multiline_comment|/* Settling time delay -- needed!  */
r_return
id|low_nib
op_or
(paren
(paren
id|inbyte
c_func
(paren
id|ioaddr
op_plus
id|PAR_STATUS
)paren
op_lshift
l_int|1
)paren
op_amp
l_int|0xf0
)paren
suffix:semicolon
)brace
multiline_comment|/* The same as read_byte_mode0(), but does multiple inb()s for stability. */
DECL|function|read_byte_mode2
r_static
r_inline
r_int
r_char
id|read_byte_mode2
c_func
(paren
r_int
id|ioaddr
)paren
(brace
r_int
r_char
id|low_nib
suffix:semicolon
id|outb
c_func
(paren
id|Ctrl_LNibRead
comma
id|ioaddr
op_plus
id|PAR_CONTROL
)paren
suffix:semicolon
id|inbyte
c_func
(paren
id|ioaddr
op_plus
id|PAR_STATUS
)paren
suffix:semicolon
id|low_nib
op_assign
(paren
id|inbyte
c_func
(paren
id|ioaddr
op_plus
id|PAR_STATUS
)paren
op_rshift
l_int|3
)paren
op_amp
l_int|0x0f
suffix:semicolon
id|outb
c_func
(paren
id|Ctrl_HNibRead
comma
id|ioaddr
op_plus
id|PAR_CONTROL
)paren
suffix:semicolon
id|inbyte
c_func
(paren
id|ioaddr
op_plus
id|PAR_STATUS
)paren
suffix:semicolon
multiline_comment|/* Settling time delay -- needed!  */
r_return
id|low_nib
op_or
(paren
(paren
id|inbyte
c_func
(paren
id|ioaddr
op_plus
id|PAR_STATUS
)paren
op_lshift
l_int|1
)paren
op_amp
l_int|0xf0
)paren
suffix:semicolon
)brace
multiline_comment|/* Read a byte through the data register. */
DECL|function|read_byte_mode4
r_static
r_inline
r_int
r_char
id|read_byte_mode4
c_func
(paren
r_int
id|ioaddr
)paren
(brace
r_int
r_char
id|low_nib
suffix:semicolon
id|outb
c_func
(paren
id|RdAddr
op_or
id|MAR
comma
id|ioaddr
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|low_nib
op_assign
(paren
id|inbyte
c_func
(paren
id|ioaddr
op_plus
id|PAR_STATUS
)paren
op_rshift
l_int|3
)paren
op_amp
l_int|0x0f
suffix:semicolon
id|outb
c_func
(paren
id|RdAddr
op_or
id|HNib
op_or
id|MAR
comma
id|ioaddr
op_plus
id|PAR_DATA
)paren
suffix:semicolon
r_return
id|low_nib
op_or
(paren
(paren
id|inbyte
c_func
(paren
id|ioaddr
op_plus
id|PAR_STATUS
)paren
op_lshift
l_int|1
)paren
op_amp
l_int|0xf0
)paren
suffix:semicolon
)brace
multiline_comment|/* Read a byte through the data register, double reading to allow settling. */
DECL|function|read_byte_mode6
r_static
r_inline
r_int
r_char
id|read_byte_mode6
c_func
(paren
r_int
id|ioaddr
)paren
(brace
r_int
r_char
id|low_nib
suffix:semicolon
id|outb
c_func
(paren
id|RdAddr
op_or
id|MAR
comma
id|ioaddr
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|inbyte
c_func
(paren
id|ioaddr
op_plus
id|PAR_STATUS
)paren
suffix:semicolon
id|low_nib
op_assign
(paren
id|inbyte
c_func
(paren
id|ioaddr
op_plus
id|PAR_STATUS
)paren
op_rshift
l_int|3
)paren
op_amp
l_int|0x0f
suffix:semicolon
id|outb
c_func
(paren
id|RdAddr
op_or
id|HNib
op_or
id|MAR
comma
id|ioaddr
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|inbyte
c_func
(paren
id|ioaddr
op_plus
id|PAR_STATUS
)paren
suffix:semicolon
r_return
id|low_nib
op_or
(paren
(paren
id|inbyte
c_func
(paren
id|ioaddr
op_plus
id|PAR_STATUS
)paren
op_lshift
l_int|1
)paren
op_amp
l_int|0xf0
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|write_reg
id|write_reg
c_func
(paren
r_int
id|port
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|value
)paren
(brace
r_int
r_char
id|outval
suffix:semicolon
id|outb
c_func
(paren
id|EOC
op_or
id|reg
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|outval
op_assign
id|WrAddr
op_or
id|reg
suffix:semicolon
id|outb
c_func
(paren
id|outval
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|outb
c_func
(paren
id|outval
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
multiline_comment|/* Double write for PS/2. */
id|outval
op_and_assign
l_int|0xf0
suffix:semicolon
id|outval
op_or_assign
id|value
suffix:semicolon
id|outb
c_func
(paren
id|outval
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|outval
op_and_assign
l_int|0x1f
suffix:semicolon
id|outb
c_func
(paren
id|outval
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|outb
c_func
(paren
id|outval
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|outb
c_func
(paren
id|EOC
op_or
id|outval
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|write_reg_high
id|write_reg_high
c_func
(paren
r_int
id|port
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|value
)paren
(brace
r_int
r_char
id|outval
op_assign
id|EOC
op_or
id|HNib
op_or
id|reg
suffix:semicolon
id|outb
c_func
(paren
id|outval
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|outval
op_and_assign
id|WrAddr
op_or
id|HNib
op_or
l_int|0x0f
suffix:semicolon
id|outb
c_func
(paren
id|outval
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|outb
c_func
(paren
id|outval
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
multiline_comment|/* Double write for PS/2. */
id|outval
op_assign
id|WrAddr
op_or
id|HNib
op_or
id|value
suffix:semicolon
id|outb
c_func
(paren
id|outval
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|outval
op_and_assign
id|HNib
op_or
l_int|0x0f
suffix:semicolon
multiline_comment|/* HNib | value */
id|outb
c_func
(paren
id|outval
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|outb
c_func
(paren
id|outval
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|outb
c_func
(paren
id|EOC
op_or
id|HNib
op_or
id|outval
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
)brace
multiline_comment|/* Write a byte out using nibble mode.  The low nibble is written first. */
r_static
r_inline
r_void
DECL|function|write_reg_byte
id|write_reg_byte
c_func
(paren
r_int
id|port
comma
r_int
r_char
id|reg
comma
r_int
r_char
id|value
)paren
(brace
r_int
r_char
id|outval
suffix:semicolon
id|outb
c_func
(paren
id|EOC
op_or
id|reg
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
multiline_comment|/* Reset the address register. */
id|outval
op_assign
id|WrAddr
op_or
id|reg
suffix:semicolon
id|outb
c_func
(paren
id|outval
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|outb
c_func
(paren
id|outval
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
multiline_comment|/* Double write for PS/2. */
id|outb
c_func
(paren
(paren
id|outval
op_amp
l_int|0xf0
)paren
op_or
(paren
id|value
op_amp
l_int|0x0f
)paren
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|outb
c_func
(paren
id|value
op_amp
l_int|0x0f
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|value
op_rshift_assign
l_int|4
suffix:semicolon
id|outb
c_func
(paren
id|value
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x10
op_or
id|value
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x10
op_or
id|value
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|outb
c_func
(paren
id|EOC
op_or
id|value
comma
id|port
op_plus
id|PAR_DATA
)paren
suffix:semicolon
multiline_comment|/* Reset the address register. */
)brace
multiline_comment|/*&n; * Bulk data writes to the packet buffer.  The interrupt line remains enabled.&n; * The first, faster method uses only the dataport (data modes 0, 2 &amp; 4).&n; * The second (backup) method uses data and control regs (modes 1, 3 &amp; 5).&n; * It should only be needed when there is skew between the individual data&n; * lines.&n; */
DECL|function|write_byte_mode0
r_static
r_inline
r_void
id|write_byte_mode0
c_func
(paren
r_int
id|ioaddr
comma
r_int
r_char
id|value
)paren
(brace
id|outb
c_func
(paren
id|value
op_amp
l_int|0x0f
comma
id|ioaddr
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|value
op_rshift
l_int|4
)paren
op_or
l_int|0x10
comma
id|ioaddr
op_plus
id|PAR_DATA
)paren
suffix:semicolon
)brace
DECL|function|write_byte_mode1
r_static
r_inline
r_void
id|write_byte_mode1
c_func
(paren
r_int
id|ioaddr
comma
r_int
r_char
id|value
)paren
(brace
id|outb
c_func
(paren
id|value
op_amp
l_int|0x0f
comma
id|ioaddr
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|outb
c_func
(paren
id|Ctrl_IRQEN
op_or
id|Ctrl_LNibWrite
comma
id|ioaddr
op_plus
id|PAR_CONTROL
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|value
op_rshift
l_int|4
)paren
op_or
l_int|0x10
comma
id|ioaddr
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|outb
c_func
(paren
id|Ctrl_IRQEN
op_or
id|Ctrl_HNibWrite
comma
id|ioaddr
op_plus
id|PAR_CONTROL
)paren
suffix:semicolon
)brace
multiline_comment|/* Write 16bit VALUE to the packet buffer: the same as above just doubled. */
DECL|function|write_word_mode0
r_static
r_inline
r_void
id|write_word_mode0
c_func
(paren
r_int
id|ioaddr
comma
r_int
r_int
id|value
)paren
(brace
id|outb
c_func
(paren
id|value
op_amp
l_int|0x0f
comma
id|ioaddr
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|value
op_rshift_assign
l_int|4
suffix:semicolon
id|outb
c_func
(paren
(paren
id|value
op_amp
l_int|0x0f
)paren
op_or
l_int|0x10
comma
id|ioaddr
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|value
op_rshift_assign
l_int|4
suffix:semicolon
id|outb
c_func
(paren
id|value
op_amp
l_int|0x0f
comma
id|ioaddr
op_plus
id|PAR_DATA
)paren
suffix:semicolon
id|value
op_rshift_assign
l_int|4
suffix:semicolon
id|outb
c_func
(paren
(paren
id|value
op_amp
l_int|0x0f
)paren
op_or
l_int|0x10
comma
id|ioaddr
op_plus
id|PAR_DATA
)paren
suffix:semicolon
)brace
multiline_comment|/*  EEPROM_Ctrl bits. */
DECL|macro|EE_SHIFT_CLK
mdefine_line|#define EE_SHIFT_CLK&t;0x04&t;/* EEPROM shift clock. */
DECL|macro|EE_CS
mdefine_line|#define EE_CS&t;&t;0x02&t;/* EEPROM chip select. */
DECL|macro|EE_CLK_HIGH
mdefine_line|#define EE_CLK_HIGH&t;0x12
DECL|macro|EE_CLK_LOW
mdefine_line|#define EE_CLK_LOW&t;0x16
DECL|macro|EE_DATA_WRITE
mdefine_line|#define EE_DATA_WRITE&t;0x01&t;/* EEPROM chip data in. */
DECL|macro|EE_DATA_READ
mdefine_line|#define EE_DATA_READ&t;0x08&t;/* EEPROM chip data out. */
multiline_comment|/* Delay between EEPROM clock transitions. */
DECL|macro|eeprom_delay
mdefine_line|#define eeprom_delay(ticks) &bslash;&n;do { int _i = 40; while (--_i &gt; 0) { __SLOW_DOWN_IO; }} while (0)
multiline_comment|/* The EEPROM commands include the alway-set leading bit. */
DECL|macro|EE_WRITE_CMD
mdefine_line|#define EE_WRITE_CMD(offset)&t;(((5 &lt;&lt; 6) + (offset)) &lt;&lt; 17)
DECL|macro|EE_READ
mdefine_line|#define EE_READ(offset) &t;(((6 &lt;&lt; 6) + (offset)) &lt;&lt; 17)
DECL|macro|EE_ERASE
mdefine_line|#define EE_ERASE(offset)&t;(((7 &lt;&lt; 6) + (offset)) &lt;&lt; 17)
DECL|macro|EE_CMD_SIZE
mdefine_line|#define EE_CMD_SIZE&t;27&t;/* The command+address+data size. */
eof
