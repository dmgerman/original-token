multiline_comment|/*****************************************************************&n; *&n; *  defines for 3Com Etherlink Plus adapter&n; *&n; *****************************************************************/
multiline_comment|/*&n; * I/O register offsets&n; */
DECL|macro|PORT_COMMAND
mdefine_line|#define&t;PORT_COMMAND&t;0x00&t;/* read/write */
DECL|macro|PORT_STATUS
mdefine_line|#define&t;PORT_STATUS&t;0x02&t;/* read only */
DECL|macro|PORT_AUXDMA
mdefine_line|#define&t;PORT_AUXDMA&t;0x02&t;/* write only */
DECL|macro|PORT_DATA
mdefine_line|#define&t;PORT_DATA&t;0x04&t;/* read/write */
DECL|macro|PORT_CONTROL
mdefine_line|#define&t;PORT_CONTROL&t;0x06&t;/* read/write */
multiline_comment|/*&n; * host control registers bits&n; */
DECL|macro|CONTROL_ATTN
mdefine_line|#define&t;CONTROL_ATTN&t;0x80&t;/* attention */
DECL|macro|CONTROL_FLSH
mdefine_line|#define&t;CONTROL_FLSH&t;0x40&t;/* flush data register */
DECL|macro|CONTROL_DMAE
mdefine_line|#define CONTROL_DMAE&t;0x20&t;/* DMA enable */
DECL|macro|CONTROL_DIR
mdefine_line|#define CONTROL_DIR&t;0x10&t;/* direction */
DECL|macro|CONTROL_TCEN
mdefine_line|#define&t;CONTROL_TCEN&t;0x08&t;/* terminal count interrupt enable */
DECL|macro|CONTROL_CMDE
mdefine_line|#define&t;CONTROL_CMDE&t;0x04&t;/* command register interrupt enable */
DECL|macro|CONTROL_HSF2
mdefine_line|#define&t;CONTROL_HSF2&t;0x02&t;/* host status flag 2 */
DECL|macro|CONTROL_HSF1
mdefine_line|#define&t;CONTROL_HSF1&t;0x01&t;/* host status flag 1 */
multiline_comment|/*&n; * combinations of HSF flags used for PCB transmission&n; */
DECL|macro|HSF_PCB_ACK
mdefine_line|#define&t;HSF_PCB_ACK&t;(CONTROL_HSF1)
DECL|macro|HSF_PCB_NAK
mdefine_line|#define&t;HSF_PCB_NAK&t;(CONTROL_HSF2)
DECL|macro|HSF_PCB_END
mdefine_line|#define&t;HSF_PCB_END&t;(CONTROL_HSF2|CONTROL_HSF1)
DECL|macro|HSF_PCB_MASK
mdefine_line|#define&t;HSF_PCB_MASK&t;(CONTROL_HSF2|CONTROL_HSF1)
multiline_comment|/*&n; * host status register bits&n; */
DECL|macro|STATUS_HRDY
mdefine_line|#define&t;STATUS_HRDY&t;0x80&t;/* data register ready */
DECL|macro|STATUS_HCRE
mdefine_line|#define&t;STATUS_HCRE&t;0x40&t;/* command register empty */
DECL|macro|STATUS_ACRF
mdefine_line|#define&t;STATUS_ACRF&t;0x20&t;/* adapter command register full */
DECL|macro|STATUS_DIR
mdefine_line|#define&t;STATUS_DIR &t;0x10&t;/* direction */
DECL|macro|STATUS_DONE
mdefine_line|#define&t;STATUS_DONE&t;0x08&t;/* DMA done */
DECL|macro|STATUS_ASF3
mdefine_line|#define&t;STATUS_ASF3&t;0x04&t;/* adapter status flag 3 */
DECL|macro|STATUS_ASF2
mdefine_line|#define&t;STATUS_ASF2&t;0x02&t;/* adapter status flag 2 */
DECL|macro|STATUS_ASF1
mdefine_line|#define&t;STATUS_ASF1&t;0x01&t;/* adapter status flag 1 */
multiline_comment|/*&n; * combinations of ASF flags used for PCB reception&n; */
DECL|macro|ASF_PCB_ACK
mdefine_line|#define&t;ASF_PCB_ACK&t;(STATUS_ASF1)
DECL|macro|ASF_PCB_NAK
mdefine_line|#define&t;ASF_PCB_NAK&t;(STATUS_ASF2)
DECL|macro|ASF_PCB_END
mdefine_line|#define&t;ASF_PCB_END&t;(STATUS_ASF2|STATUS_ASF1)
DECL|macro|ASF_PCB_MASK
mdefine_line|#define&t;ASF_PCB_MASK&t;(STATUS_ASF2|STATUS_ASF1)
multiline_comment|/*&n; * host aux DMA register bits&n; */
DECL|macro|AUXDMA_BRST
mdefine_line|#define&t;AUXDMA_BRST&t;0x01&t;/* DMA burst */
multiline_comment|/*&n; * maximum amount of data data allowed in a PCB&n; */
DECL|macro|MAX_PCB_DATA
mdefine_line|#define&t;MAX_PCB_DATA&t;62
multiline_comment|/*****************************************************************&n; *&n; *  timeout value&n; *&t;this is a rough value used for loops to stop them from &n; *&t;locking up the whole machine in the case of failure or&n; *&t;error conditions&n; *&n; *****************************************************************/
DECL|macro|TIMEOUT
mdefine_line|#define&t;TIMEOUT&t;300
multiline_comment|/*****************************************************************&n; *&n; * PCB commands&n; *&n; *****************************************************************/
r_enum
(brace
multiline_comment|/*&n;   * host PCB commands&n;   */
DECL|enumerator|CMD_CONFIGURE_ADAPTER_MEMORY
id|CMD_CONFIGURE_ADAPTER_MEMORY
op_assign
l_int|0x01
comma
DECL|enumerator|CMD_CONFIGURE_82586
id|CMD_CONFIGURE_82586
op_assign
l_int|0x02
comma
DECL|enumerator|CMD_STATION_ADDRESS
id|CMD_STATION_ADDRESS
op_assign
l_int|0x03
comma
DECL|enumerator|CMD_DMA_DOWNLOAD
id|CMD_DMA_DOWNLOAD
op_assign
l_int|0x04
comma
DECL|enumerator|CMD_DMA_UPLOAD
id|CMD_DMA_UPLOAD
op_assign
l_int|0x05
comma
DECL|enumerator|CMD_PIO_DOWNLOAD
id|CMD_PIO_DOWNLOAD
op_assign
l_int|0x06
comma
DECL|enumerator|CMD_PIO_UPLOAD
id|CMD_PIO_UPLOAD
op_assign
l_int|0x07
comma
DECL|enumerator|CMD_RECEIVE_PACKET
id|CMD_RECEIVE_PACKET
op_assign
l_int|0x08
comma
DECL|enumerator|CMD_TRANSMIT_PACKET
id|CMD_TRANSMIT_PACKET
op_assign
l_int|0x09
comma
DECL|enumerator|CMD_NETWORK_STATISTICS
id|CMD_NETWORK_STATISTICS
op_assign
l_int|0x0a
comma
DECL|enumerator|CMD_LOAD_MULTICAST_LIST
id|CMD_LOAD_MULTICAST_LIST
op_assign
l_int|0x0b
comma
DECL|enumerator|CMD_CLEAR_PROGRAM
id|CMD_CLEAR_PROGRAM
op_assign
l_int|0x0c
comma
DECL|enumerator|CMD_DOWNLOAD_PROGRAM
id|CMD_DOWNLOAD_PROGRAM
op_assign
l_int|0x0d
comma
DECL|enumerator|CMD_EXECUTE_PROGRAM
id|CMD_EXECUTE_PROGRAM
op_assign
l_int|0x0e
comma
DECL|enumerator|CMD_SELF_TEST
id|CMD_SELF_TEST
op_assign
l_int|0x0f
comma
DECL|enumerator|CMD_SET_STATION_ADDRESS
id|CMD_SET_STATION_ADDRESS
op_assign
l_int|0x10
comma
DECL|enumerator|CMD_ADAPTER_INFO
id|CMD_ADAPTER_INFO
op_assign
l_int|0x11
comma
DECL|enumerator|NUM_TRANSMIT_CMDS
id|NUM_TRANSMIT_CMDS
comma
multiline_comment|/*&n;   * adapter PCB commands&n;   */
DECL|enumerator|CMD_CONFIGURE_ADAPTER_RESPONSE
id|CMD_CONFIGURE_ADAPTER_RESPONSE
op_assign
l_int|0x31
comma
DECL|enumerator|CMD_CONFIGURE_82586_RESPONSE
id|CMD_CONFIGURE_82586_RESPONSE
op_assign
l_int|0x32
comma
DECL|enumerator|CMD_ADDRESS_RESPONSE
id|CMD_ADDRESS_RESPONSE
op_assign
l_int|0x33
comma
DECL|enumerator|CMD_DOWNLOAD_DATA_REQUEST
id|CMD_DOWNLOAD_DATA_REQUEST
op_assign
l_int|0x34
comma
DECL|enumerator|CMD_UPLOAD_DATA_REQUEST
id|CMD_UPLOAD_DATA_REQUEST
op_assign
l_int|0x35
comma
DECL|enumerator|CMD_RECEIVE_PACKET_COMPLETE
id|CMD_RECEIVE_PACKET_COMPLETE
op_assign
l_int|0x38
comma
DECL|enumerator|CMD_TRANSMIT_PACKET_COMPLETE
id|CMD_TRANSMIT_PACKET_COMPLETE
op_assign
l_int|0x39
comma
DECL|enumerator|CMD_NETWORK_STATISTICS_RESPONSE
id|CMD_NETWORK_STATISTICS_RESPONSE
op_assign
l_int|0x3a
comma
DECL|enumerator|CMD_LOAD_MULTICAST_RESPONSE
id|CMD_LOAD_MULTICAST_RESPONSE
op_assign
l_int|0x3b
comma
DECL|enumerator|CMD_CLEAR_PROGRAM_RESPONSE
id|CMD_CLEAR_PROGRAM_RESPONSE
op_assign
l_int|0x3c
comma
DECL|enumerator|CMD_DOWNLOAD_PROGRAM_RESPONSE
id|CMD_DOWNLOAD_PROGRAM_RESPONSE
op_assign
l_int|0x3d
comma
DECL|enumerator|CMD_EXECUTE_RESPONSE
id|CMD_EXECUTE_RESPONSE
op_assign
l_int|0x3e
comma
DECL|enumerator|CMD_SELF_TEST_RESPONSE
id|CMD_SELF_TEST_RESPONSE
op_assign
l_int|0x3f
comma
DECL|enumerator|CMD_SET_ADDRESS_RESPONSE
id|CMD_SET_ADDRESS_RESPONSE
op_assign
l_int|0x40
comma
DECL|enumerator|CMD_ADAPTER_INFO_RESPONSE
id|CMD_ADAPTER_INFO_RESPONSE
op_assign
l_int|0x41
)brace
suffix:semicolon
eof
