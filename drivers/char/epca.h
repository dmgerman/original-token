DECL|macro|XEMPORTS
mdefine_line|#define XEMPORTS    0xC02
DECL|macro|XEPORTS
mdefine_line|#define XEPORTS     0xC22
DECL|macro|MAX_ALLOC
mdefine_line|#define MAX_ALLOC   0x100
DECL|macro|MAXBOARDS
mdefine_line|#define MAXBOARDS   12
DECL|macro|FEPCODESEG
mdefine_line|#define FEPCODESEG  0x0200L
DECL|macro|FEPCODE
mdefine_line|#define FEPCODE     0x2000L
DECL|macro|BIOSCODE
mdefine_line|#define BIOSCODE    0xf800L
DECL|macro|MISCGLOBAL
mdefine_line|#define MISCGLOBAL  0x0C00L
DECL|macro|NPORT
mdefine_line|#define NPORT       0x0C22L
DECL|macro|MBOX
mdefine_line|#define MBOX        0x0C40L
DECL|macro|PORTBASE
mdefine_line|#define PORTBASE    0x0C90L
multiline_comment|/* Begin code defines used for epca_setup */
DECL|macro|INVALID_BOARD_TYPE
mdefine_line|#define INVALID_BOARD_TYPE   0x1
DECL|macro|INVALID_NUM_PORTS
mdefine_line|#define INVALID_NUM_PORTS    0x2
DECL|macro|INVALID_MEM_BASE
mdefine_line|#define INVALID_MEM_BASE     0x4
DECL|macro|INVALID_PORT_BASE
mdefine_line|#define INVALID_PORT_BASE    0x8
DECL|macro|INVALID_BOARD_STATUS
mdefine_line|#define INVALID_BOARD_STATUS 0x10
DECL|macro|INVALID_ALTPIN
mdefine_line|#define INVALID_ALTPIN       0x20
multiline_comment|/* End code defines used for epca_setup */
DECL|macro|FEPCLR
mdefine_line|#define FEPCLR      0x00
DECL|macro|FEPMEM
mdefine_line|#define FEPMEM      0x02
DECL|macro|FEPRST
mdefine_line|#define FEPRST      0x04
DECL|macro|FEPINT
mdefine_line|#define FEPINT      0x08
DECL|macro|FEPMASK
mdefine_line|#define&t;FEPMASK     0x0e
DECL|macro|FEPWIN
mdefine_line|#define&t;FEPWIN      0x80
DECL|macro|PCXE
mdefine_line|#define PCXE    0
DECL|macro|PCXEVE
mdefine_line|#define PCXEVE  1
DECL|macro|PCXEM
mdefine_line|#define PCXEM   2   
DECL|macro|EISAXEM
mdefine_line|#define EISAXEM 3
DECL|macro|PC64XE
mdefine_line|#define PC64XE  4
DECL|macro|PCXI
mdefine_line|#define PCXI    5
DECL|macro|PCIXEM
mdefine_line|#define PCIXEM  7
DECL|macro|PCICX
mdefine_line|#define PCICX   8
DECL|macro|PCIXR
mdefine_line|#define PCIXR   9
DECL|macro|PCIXRJ
mdefine_line|#define PCIXRJ  10
DECL|macro|EPCA_NUM_TYPES
mdefine_line|#define EPCA_NUM_TYPES 6
DECL|variable|board_desc
r_static
r_char
op_star
id|board_desc
(braket
)braket
op_assign
(brace
l_string|&quot;PC/Xe&quot;
comma
l_string|&quot;PC/Xeve&quot;
comma
l_string|&quot;PC/Xem&quot;
comma
l_string|&quot;EISA/Xem&quot;
comma
l_string|&quot;PC/64Xe&quot;
comma
l_string|&quot;PC/Xi&quot;
comma
l_string|&quot;unknown&quot;
comma
l_string|&quot;PCI/Xem&quot;
comma
l_string|&quot;PCI/CX&quot;
comma
l_string|&quot;PCI/Xr&quot;
comma
l_string|&quot;PCI/Xrj&quot;
comma
)brace
suffix:semicolon
DECL|macro|STARTC
mdefine_line|#define STARTC      021
DECL|macro|STOPC
mdefine_line|#define STOPC       023
DECL|macro|IAIXON
mdefine_line|#define IAIXON      0x2000
DECL|macro|TXSTOPPED
mdefine_line|#define TXSTOPPED  0x1
DECL|macro|LOWWAIT
mdefine_line|#define LOWWAIT    0x2
DECL|macro|EMPTYWAIT
mdefine_line|#define EMPTYWAIT  0x4
DECL|macro|RXSTOPPED
mdefine_line|#define RXSTOPPED  0x8
DECL|macro|TXBUSY
mdefine_line|#define TXBUSY     0x10
DECL|macro|DISABLED
mdefine_line|#define DISABLED   0
DECL|macro|ENABLED
mdefine_line|#define ENABLED    1
DECL|macro|OFF
mdefine_line|#define OFF        0
DECL|macro|ON
mdefine_line|#define ON         1
DECL|macro|FEPTIMEOUT
mdefine_line|#define FEPTIMEOUT 200000  
DECL|macro|SERIAL_TYPE_NORMAL
mdefine_line|#define SERIAL_TYPE_NORMAL  1
DECL|macro|SERIAL_TYPE_CALLOUT
mdefine_line|#define SERIAL_TYPE_CALLOUT 2
DECL|macro|SERIAL_TYPE_INFO
mdefine_line|#define SERIAL_TYPE_INFO    3
DECL|macro|EPCA_EVENT_HANGUP
mdefine_line|#define EPCA_EVENT_HANGUP   1
DECL|macro|EPCA_MAGIC
mdefine_line|#define EPCA_MAGIC          0x5c6df104L
DECL|struct|channel
r_struct
id|channel
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|boardnum
id|unchar
id|boardnum
suffix:semicolon
DECL|member|channelnum
id|unchar
id|channelnum
suffix:semicolon
DECL|member|omodem
id|unchar
id|omodem
suffix:semicolon
multiline_comment|/* FEP output modem status     */
DECL|member|imodem
id|unchar
id|imodem
suffix:semicolon
multiline_comment|/* FEP input modem status      */
DECL|member|modemfake
id|unchar
id|modemfake
suffix:semicolon
multiline_comment|/* Modem values to be forced   */
DECL|member|modem
id|unchar
id|modem
suffix:semicolon
multiline_comment|/* Force values                */
DECL|member|hflow
id|unchar
id|hflow
suffix:semicolon
DECL|member|dsr
id|unchar
id|dsr
suffix:semicolon
DECL|member|dcd
id|unchar
id|dcd
suffix:semicolon
DECL|member|m_rts
id|unchar
id|m_rts
suffix:semicolon
multiline_comment|/* The bits used in whatever FEP */
DECL|member|m_dcd
id|unchar
id|m_dcd
suffix:semicolon
multiline_comment|/* is indiginous to this board to */
DECL|member|m_dsr
id|unchar
id|m_dsr
suffix:semicolon
multiline_comment|/* represent each of the physical */
DECL|member|m_cts
id|unchar
id|m_cts
suffix:semicolon
multiline_comment|/* handshake lines */
DECL|member|m_ri
id|unchar
id|m_ri
suffix:semicolon
DECL|member|m_dtr
id|unchar
id|m_dtr
suffix:semicolon
DECL|member|stopc
id|unchar
id|stopc
suffix:semicolon
DECL|member|startc
id|unchar
id|startc
suffix:semicolon
DECL|member|stopca
id|unchar
id|stopca
suffix:semicolon
DECL|member|startca
id|unchar
id|startca
suffix:semicolon
DECL|member|fepstopc
id|unchar
id|fepstopc
suffix:semicolon
DECL|member|fepstartc
id|unchar
id|fepstartc
suffix:semicolon
DECL|member|fepstopca
id|unchar
id|fepstopca
suffix:semicolon
DECL|member|fepstartca
id|unchar
id|fepstartca
suffix:semicolon
DECL|member|txwin
id|unchar
id|txwin
suffix:semicolon
DECL|member|rxwin
id|unchar
id|rxwin
suffix:semicolon
DECL|member|fepiflag
id|ushort
id|fepiflag
suffix:semicolon
DECL|member|fepcflag
id|ushort
id|fepcflag
suffix:semicolon
DECL|member|fepoflag
id|ushort
id|fepoflag
suffix:semicolon
DECL|member|txbufhead
id|ushort
id|txbufhead
suffix:semicolon
DECL|member|txbufsize
id|ushort
id|txbufsize
suffix:semicolon
DECL|member|rxbufhead
id|ushort
id|rxbufhead
suffix:semicolon
DECL|member|rxbufsize
id|ushort
id|rxbufsize
suffix:semicolon
DECL|member|close_delay
r_int
id|close_delay
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|blocked_open
r_int
id|blocked_open
suffix:semicolon
DECL|member|event
r_int
id|event
suffix:semicolon
DECL|member|asyncflags
r_int
id|asyncflags
suffix:semicolon
DECL|member|dev
id|uint
id|dev
suffix:semicolon
DECL|member|session
r_int
id|session
suffix:semicolon
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
DECL|member|statusflags
id|ulong
id|statusflags
suffix:semicolon
DECL|member|c_iflag
id|ulong
id|c_iflag
suffix:semicolon
DECL|member|c_cflag
id|ulong
id|c_cflag
suffix:semicolon
DECL|member|c_lflag
id|ulong
id|c_lflag
suffix:semicolon
DECL|member|c_oflag
id|ulong
id|c_oflag
suffix:semicolon
DECL|member|txptr
id|unchar
op_star
id|txptr
suffix:semicolon
DECL|member|rxptr
id|unchar
op_star
id|rxptr
suffix:semicolon
DECL|member|tmp_buf
id|unchar
op_star
id|tmp_buf
suffix:semicolon
DECL|member|board
r_struct
id|board_info
op_star
id|board
suffix:semicolon
DECL|member|brdchan
r_volatile
r_struct
id|board_chan
op_star
id|brdchan
suffix:semicolon
DECL|member|digiext
r_struct
id|digi_struct
id|digiext
suffix:semicolon
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|normal_termios
r_struct
id|termios
id|normal_termios
suffix:semicolon
DECL|member|callout_termios
r_struct
id|termios
id|callout_termios
suffix:semicolon
DECL|member|open_wait
id|wait_queue_head_t
id|open_wait
suffix:semicolon
DECL|member|close_wait
id|wait_queue_head_t
id|close_wait
suffix:semicolon
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
suffix:semicolon
DECL|member|mailbox
r_volatile
r_struct
id|global_data
op_star
id|mailbox
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|board_info
r_struct
id|board_info
(brace
DECL|member|status
id|unchar
id|status
suffix:semicolon
DECL|member|type
id|unchar
id|type
suffix:semicolon
DECL|member|altpin
id|unchar
id|altpin
suffix:semicolon
DECL|member|numports
id|ushort
id|numports
suffix:semicolon
DECL|member|port
id|unchar
op_star
id|port
suffix:semicolon
DECL|member|membase
id|unchar
op_star
id|membase
suffix:semicolon
DECL|member|re_map_port
id|unchar
op_star
id|re_map_port
suffix:semicolon
DECL|member|re_map_membase
id|unchar
op_star
id|re_map_membase
suffix:semicolon
DECL|member|memory_seg
id|ulong
id|memory_seg
suffix:semicolon
DECL|member|memwinon
r_void
(paren
op_star
id|memwinon
)paren
(paren
r_struct
id|board_info
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|memwinoff
r_void
(paren
op_star
id|memwinoff
)paren
(paren
r_struct
id|board_info
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|globalwinon
r_void
(paren
op_star
id|globalwinon
)paren
(paren
r_struct
id|channel
op_star
)paren
suffix:semicolon
DECL|member|txwinon
r_void
(paren
op_star
id|txwinon
)paren
(paren
r_struct
id|channel
op_star
)paren
suffix:semicolon
DECL|member|rxwinon
r_void
(paren
op_star
id|rxwinon
)paren
(paren
r_struct
id|channel
op_star
)paren
suffix:semicolon
DECL|member|memoff
r_void
(paren
op_star
id|memoff
)paren
(paren
r_struct
id|channel
op_star
)paren
suffix:semicolon
DECL|member|assertgwinon
r_void
(paren
op_star
id|assertgwinon
)paren
(paren
r_struct
id|channel
op_star
)paren
suffix:semicolon
DECL|member|assertmemoff
r_void
(paren
op_star
id|assertmemoff
)paren
(paren
r_struct
id|channel
op_star
)paren
suffix:semicolon
DECL|member|poller_inhibited
id|unchar
id|poller_inhibited
suffix:semicolon
)brace
suffix:semicolon
eof
