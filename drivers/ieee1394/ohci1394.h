macro_line|#ifndef _OHCI1394_H
DECL|macro|_OHCI1394_H
mdefine_line|#define _OHCI1394_H
macro_line|#include &quot;ieee1394_types.h&quot;
DECL|macro|OHCI1394_DRIVER_NAME
mdefine_line|#define OHCI1394_DRIVER_NAME      &quot;ohci1394&quot;
macro_line|#ifndef PCI_DEVICE_ID_TI_OHCI1394
DECL|macro|PCI_DEVICE_ID_TI_OHCI1394
mdefine_line|#define PCI_DEVICE_ID_TI_OHCI1394 0x8009
macro_line|#endif 
macro_line|#ifndef PCI_DEVICE_ID_TI_OHCI1394_2
DECL|macro|PCI_DEVICE_ID_TI_OHCI1394_2
mdefine_line|#define PCI_DEVICE_ID_TI_OHCI1394_2 0x8019
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_VIA_OHCI1394
DECL|macro|PCI_DEVICE_ID_VIA_OHCI1394
mdefine_line|#define PCI_DEVICE_ID_VIA_OHCI1394 0x3044
macro_line|#endif
DECL|macro|MAX_OHCI1394_CARDS
mdefine_line|#define MAX_OHCI1394_CARDS        4
DECL|macro|OHCI1394_MAX_AT_REQ_RETRIES
mdefine_line|#define OHCI1394_MAX_AT_REQ_RETRIES       1
DECL|macro|OHCI1394_MAX_AT_RESP_RETRIES
mdefine_line|#define OHCI1394_MAX_AT_RESP_RETRIES      1
DECL|macro|OHCI1394_MAX_PHYS_RESP_RETRIES
mdefine_line|#define OHCI1394_MAX_PHYS_RESP_RETRIES    4
DECL|macro|AR_RESP_NUM_DESC
mdefine_line|#define AR_RESP_NUM_DESC                  4 /* number of AR resp descriptors */
DECL|macro|AR_RESP_BUF_SIZE
mdefine_line|#define AR_RESP_BUF_SIZE               4096 /* size of AR resp buffers */
DECL|macro|AR_RESP_SPLIT_PACKET_BUF_SIZE
mdefine_line|#define AR_RESP_SPLIT_PACKET_BUF_SIZE   256 /* split packet buffer */
DECL|macro|AR_RESP_TOTAL_BUF_SIZE
mdefine_line|#define AR_RESP_TOTAL_BUF_SIZE         (AR_RESP_BUF_SIZE * AR_RESP_NUM_DESC)
DECL|macro|AT_REQ_PRG_SIZE
mdefine_line|#define AT_REQ_PRG_SIZE                256
DECL|macro|IR_RECV_BUF_SIZE
mdefine_line|#define IR_RECV_BUF_SIZE          4096 /* 4096 bytes/buffer */
DECL|macro|IR_SPLIT_PACKET_BUF_SIZE
mdefine_line|#define IR_SPLIT_PACKET_BUF_SIZE  8192 /* size of buffer for split packets */
DECL|macro|IR_NUM_DESC
mdefine_line|#define IR_NUM_DESC               16   /* number of ISO recv descriptors */
DECL|struct|dma_cmd
r_struct
id|dma_cmd
(brace
DECL|member|control
id|u32
id|control
suffix:semicolon
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|member|branchAddress
id|u32
id|branchAddress
suffix:semicolon
DECL|member|status
id|u32
id|status
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ti_ohci
r_struct
id|ti_ohci
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
multiline_comment|/* sequential card number */
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
DECL|member|state
id|u32
id|state
suffix:semicolon
multiline_comment|/* remapped memory spaces */
DECL|member|registers
r_void
op_star
id|registers
suffix:semicolon
DECL|member|self_id_buffer
id|quadlet_t
op_star
id|self_id_buffer
suffix:semicolon
multiline_comment|/* dma buffer for self-id packets */
DECL|member|csr_config_rom
id|quadlet_t
op_star
id|csr_config_rom
suffix:semicolon
multiline_comment|/* buffer for csr config rom */
multiline_comment|/* asynchronous receive */
DECL|member|AR_resp_prg
r_struct
id|dma_cmd
op_star
op_star
id|AR_resp_prg
suffix:semicolon
DECL|member|AR_resp_buf
id|quadlet_t
op_star
op_star
id|AR_resp_buf
suffix:semicolon
DECL|member|AR_resp_buf_bh_ind
r_int
r_int
id|AR_resp_buf_bh_ind
suffix:semicolon
DECL|member|AR_resp_buf_bh_offset
r_int
r_int
id|AR_resp_buf_bh_offset
suffix:semicolon
DECL|member|AR_resp_buf_th_ind
r_int
r_int
id|AR_resp_buf_th_ind
suffix:semicolon
DECL|member|AR_resp_buf_th_offset
r_int
r_int
id|AR_resp_buf_th_offset
suffix:semicolon
DECL|member|AR_resp_bytes_left
r_int
id|AR_resp_bytes_left
suffix:semicolon
DECL|member|AR_resp_spb
id|quadlet_t
op_star
id|AR_resp_spb
suffix:semicolon
DECL|member|AR_resp_lock
id|spinlock_t
id|AR_resp_lock
suffix:semicolon
multiline_comment|/* async receive task */
DECL|member|AR_resp_pdl_task
r_struct
id|tq_struct
id|AR_resp_pdl_task
suffix:semicolon
multiline_comment|/* asynchronous transmit */
DECL|member|AT_req_prg
r_struct
id|dma_cmd
op_star
id|AT_req_prg
suffix:semicolon
multiline_comment|/* isochronous receive */
DECL|member|IR_recv_prg
r_struct
id|dma_cmd
op_star
op_star
id|IR_recv_prg
suffix:semicolon
DECL|member|IR_recv_buf
id|quadlet_t
op_star
op_star
id|IR_recv_buf
suffix:semicolon
DECL|member|IR_buf_used
r_int
r_int
id|IR_buf_used
suffix:semicolon
DECL|member|IR_buf_last_ind
r_int
r_int
id|IR_buf_last_ind
suffix:semicolon
DECL|member|IR_buf_next_ind
r_int
r_int
id|IR_buf_next_ind
suffix:semicolon
DECL|member|IR_recv_lock
id|spinlock_t
id|IR_recv_lock
suffix:semicolon
multiline_comment|/* iso recv split packet handling */
DECL|member|IR_spb
id|quadlet_t
op_star
id|IR_spb
suffix:semicolon
DECL|member|IR_sp_bytes_left
r_int
r_int
id|IR_sp_bytes_left
suffix:semicolon
DECL|member|IR_spb_bytes_used
r_int
r_int
id|IR_spb_bytes_used
suffix:semicolon
multiline_comment|/* iso receive channel usage */
DECL|member|IR_channel_lock
id|spinlock_t
id|IR_channel_lock
suffix:semicolon
DECL|member|IR_channel_usage
id|u64
id|IR_channel_usage
suffix:semicolon
multiline_comment|/* iso receive task */
DECL|member|IR_pdl_task
r_struct
id|tq_struct
id|IR_pdl_task
suffix:semicolon
multiline_comment|/* IEEE-1394 part follows */
DECL|member|host
r_struct
id|hpsb_host
op_star
id|host
suffix:semicolon
DECL|member|phyid
DECL|member|isroot
r_int
id|phyid
comma
id|isroot
suffix:semicolon
DECL|member|phy_reg_lock
id|spinlock_t
id|phy_reg_lock
suffix:semicolon
DECL|member|async_queue
r_struct
id|hpsb_packet
op_star
id|async_queue
suffix:semicolon
DECL|member|async_queue_lock
id|spinlock_t
id|async_queue_lock
suffix:semicolon
DECL|member|AR_resp_active
r_int
id|AR_resp_active
suffix:semicolon
DECL|member|NumBusResets
r_int
id|NumBusResets
suffix:semicolon
DECL|member|TxRdy
r_int
id|TxRdy
suffix:semicolon
DECL|member|NumInterrupts
r_int
id|NumInterrupts
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Register read and write helper functions.&n; */
DECL|function|reg_write
r_inline
r_static
r_void
id|reg_write
c_func
(paren
r_const
r_struct
id|ti_ohci
op_star
id|ohci
comma
r_int
id|offset
comma
id|u32
id|data
)paren
(brace
id|writel
c_func
(paren
id|data
comma
id|ohci-&gt;registers
op_plus
id|offset
)paren
suffix:semicolon
)brace
DECL|function|reg_read
r_inline
r_static
id|u32
id|reg_read
c_func
(paren
r_const
r_struct
id|ti_ohci
op_star
id|ohci
comma
r_int
id|offset
)paren
(brace
r_return
id|readl
c_func
(paren
id|ohci-&gt;registers
op_plus
id|offset
)paren
suffix:semicolon
)brace
multiline_comment|/* This structure is not properly initialized ... it is taken from&n;   the lynx_csr_rom written by Andreas ... Some fields in the root&n;   directory and the module dependent info needs to be modified&n;   I do not have the proper doc */
DECL|variable|ohci_csr_rom
id|quadlet_t
id|ohci_csr_rom
(braket
)braket
op_assign
(brace
multiline_comment|/* bus info block */
l_int|0x04040000
comma
multiline_comment|/* info/CRC length, CRC */
l_int|0x31333934
comma
multiline_comment|/* 1394 magic number */
l_int|0xf064a000
comma
multiline_comment|/* misc. settings - FIXME */
l_int|0x08002856
comma
multiline_comment|/* vendor ID, chip ID high */
l_int|0x0000083E
comma
multiline_comment|/* chip ID low */
multiline_comment|/* root directory - FIXME */
l_int|0x00090000
comma
multiline_comment|/* CRC length, CRC */
l_int|0x03080028
comma
multiline_comment|/* vendor ID (Texas Instr.) */
l_int|0x81000009
comma
multiline_comment|/* offset to textual ID */
l_int|0x0c000200
comma
multiline_comment|/* node capabilities */
l_int|0x8d00000e
comma
multiline_comment|/* offset to unique ID */
l_int|0xc7000010
comma
multiline_comment|/* offset to module independent info */
l_int|0x04000000
comma
multiline_comment|/* module hardware version */
l_int|0x81000026
comma
multiline_comment|/* offset to textual ID */
l_int|0x09000000
comma
multiline_comment|/* node hardware version */
l_int|0x81000026
comma
multiline_comment|/* offset to textual ID */
multiline_comment|/* module vendor ID textual */
l_int|0x00080000
comma
multiline_comment|/* CRC length, CRC */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x54455841
comma
multiline_comment|/* &quot;Texas Instruments&quot; */
l_int|0x5320494e
comma
l_int|0x53545255
comma
l_int|0x4d454e54
comma
l_int|0x53000000
comma
multiline_comment|/* node unique ID leaf */
l_int|0x00020000
comma
multiline_comment|/* CRC length, CRC */
l_int|0x08002856
comma
multiline_comment|/* vendor ID, chip ID high */
l_int|0x0000083E
comma
multiline_comment|/* chip ID low */
multiline_comment|/* module dependent info - FIXME */
l_int|0x00060000
comma
multiline_comment|/* CRC length, CRC */
l_int|0xb8000006
comma
multiline_comment|/* ??? offset to module textual ID */
l_int|0x81000004
comma
multiline_comment|/* ??? textual descriptor */
l_int|0x00000000
comma
multiline_comment|/* SRAM size */
l_int|0x00000000
comma
multiline_comment|/* AUXRAM size */
l_int|0x00000000
comma
multiline_comment|/* AUX device */
multiline_comment|/* module textual ID */
l_int|0x00050000
comma
multiline_comment|/* CRC length, CRC */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x54534231
comma
multiline_comment|/* &quot;TSB12LV22&quot; */
l_int|0x324c5632
comma
l_int|0x32000000
comma
multiline_comment|/* part number */
l_int|0x00060000
comma
multiline_comment|/* CRC length, CRC */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x39383036
comma
multiline_comment|/* &quot;9806000-0001&quot; */
l_int|0x3030342d
comma
l_int|0x30303431
comma
l_int|0x20000001
comma
multiline_comment|/* module hardware version textual */
l_int|0x00050000
comma
multiline_comment|/* CRC length, CRC */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x5453424b
comma
multiline_comment|/* &quot;TSBKOHCI403&quot; */
l_int|0x4f484349
comma
l_int|0x34303300
comma
multiline_comment|/* node hardware version textual */
l_int|0x00050000
comma
multiline_comment|/* CRC length, CRC */
l_int|0x00000000
comma
l_int|0x00000000
comma
l_int|0x54534234
comma
multiline_comment|/* &quot;TSB41LV03&quot; */
l_int|0x314c5630
comma
l_int|0x33000000
)brace
suffix:semicolon
multiline_comment|/* 2 KiloBytes of register space */
DECL|macro|OHCI1394_REGISTER_SIZE
mdefine_line|#define OHCI1394_REGISTER_SIZE                0x800       
multiline_comment|/* register map */
DECL|macro|OHCI1394_Version
mdefine_line|#define OHCI1394_Version                      0x000
DECL|macro|OHCI1394_GUID_ROM
mdefine_line|#define OHCI1394_GUID_ROM                     0x004
DECL|macro|OHCI1394_ATRetries
mdefine_line|#define OHCI1394_ATRetries                    0x008
DECL|macro|OHCI1394_CSRReadData
mdefine_line|#define OHCI1394_CSRReadData                  0x00C
DECL|macro|OHCI1394_CSRCompareData
mdefine_line|#define OHCI1394_CSRCompareData               0x010
DECL|macro|OHCI1394_CSRControl
mdefine_line|#define OHCI1394_CSRControl                   0x014
DECL|macro|OHCI1394_ConfigROMhdr
mdefine_line|#define OHCI1394_ConfigROMhdr                 0x018
DECL|macro|OHCI1394_BusID
mdefine_line|#define OHCI1394_BusID                        0x01C
DECL|macro|OHCI1394_BusOptions
mdefine_line|#define OHCI1394_BusOptions                   0x020
DECL|macro|OHCI1394_GUIDHi
mdefine_line|#define OHCI1394_GUIDHi                       0x024
DECL|macro|OHCI1394_GUIDLo
mdefine_line|#define OHCI1394_GUIDLo                       0x028
DECL|macro|OHCI1394_ConfigROMmap
mdefine_line|#define OHCI1394_ConfigROMmap                 0x034
DECL|macro|OHCI1394_PostedWriteAddressLo
mdefine_line|#define OHCI1394_PostedWriteAddressLo         0x038
DECL|macro|OHCI1394_PostedWriteAddressHi
mdefine_line|#define OHCI1394_PostedWriteAddressHi         0x03C
DECL|macro|OHCI1394_VendorID
mdefine_line|#define OHCI1394_VendorID                     0x040
DECL|macro|OHCI1394_HCControlSet
mdefine_line|#define OHCI1394_HCControlSet                 0x050
DECL|macro|OHCI1394_HCControlClear
mdefine_line|#define OHCI1394_HCControlClear               0x054
DECL|macro|OHCI1394_SelfIDBuffer
mdefine_line|#define OHCI1394_SelfIDBuffer                 0x064
DECL|macro|OHCI1394_SelfIDCount
mdefine_line|#define OHCI1394_SelfIDCount                  0x068
DECL|macro|OHCI1394_IRMultiChanMaskHiSet
mdefine_line|#define OHCI1394_IRMultiChanMaskHiSet         0x070
DECL|macro|OHCI1394_IRMultiChanMaskHiClear
mdefine_line|#define OHCI1394_IRMultiChanMaskHiClear       0x074
DECL|macro|OHCI1394_IRMultiChanMaskLoSet
mdefine_line|#define OHCI1394_IRMultiChanMaskLoSet         0x078
DECL|macro|OHCI1394_IRMultiChanMaskLoClear
mdefine_line|#define OHCI1394_IRMultiChanMaskLoClear       0x07C
DECL|macro|OHCI1394_IntEventSet
mdefine_line|#define OHCI1394_IntEventSet                  0x080
DECL|macro|OHCI1394_IntEventClear
mdefine_line|#define OHCI1394_IntEventClear                0x084
DECL|macro|OHCI1394_IntMaskSet
mdefine_line|#define OHCI1394_IntMaskSet                   0x088
DECL|macro|OHCI1394_IntMaskClear
mdefine_line|#define OHCI1394_IntMaskClear                 0x08C
DECL|macro|OHCI1394_IsoXmitIntEventSet
mdefine_line|#define OHCI1394_IsoXmitIntEventSet           0x090
DECL|macro|OHCI1394_IsoXmitIntEventClear
mdefine_line|#define OHCI1394_IsoXmitIntEventClear         0x094
DECL|macro|OHCI1394_IsoXmitIntMaskSet
mdefine_line|#define OHCI1394_IsoXmitIntMaskSet            0x098
DECL|macro|OHCI1394_IsoXmitIntMaskClear
mdefine_line|#define OHCI1394_IsoXmitIntMaskClear          0x09C
DECL|macro|OHCI1394_IsoRecvIntEventSet
mdefine_line|#define OHCI1394_IsoRecvIntEventSet           0x0A0
DECL|macro|OHCI1394_IsoRecvIntEventClear
mdefine_line|#define OHCI1394_IsoRecvIntEventClear         0x0A4
DECL|macro|OHCI1394_IsoRecvIntMaskSet
mdefine_line|#define OHCI1394_IsoRecvIntMaskSet            0x0A8
DECL|macro|OHCI1394_IsoRecvIntMaskClear
mdefine_line|#define OHCI1394_IsoRecvIntMaskClear          0x0AC
DECL|macro|OHCI1394_FairnessControl
mdefine_line|#define OHCI1394_FairnessControl              0x0DC
DECL|macro|OHCI1394_LinkControlSet
mdefine_line|#define OHCI1394_LinkControlSet               0x0E0
DECL|macro|OHCI1394_LinkControlClear
mdefine_line|#define OHCI1394_LinkControlClear             0x0E4
DECL|macro|OHCI1394_NodeID
mdefine_line|#define OHCI1394_NodeID                       0x0E8
DECL|macro|OHCI1394_PhyControl
mdefine_line|#define OHCI1394_PhyControl                   0x0EC
DECL|macro|OHCI1394_IsochronousCycleTimer
mdefine_line|#define OHCI1394_IsochronousCycleTimer        0x0F0
DECL|macro|OHCI1394_AsReqFilterHiSet
mdefine_line|#define OHCI1394_AsReqFilterHiSet             0x100
DECL|macro|OHCI1394_AsReqFilterHiClear
mdefine_line|#define OHCI1394_AsReqFilterHiClear           0x104
DECL|macro|OHCI1394_AsReqFilterLoSet
mdefine_line|#define OHCI1394_AsReqFilterLoSet             0x108
DECL|macro|OHCI1394_AsReqFilterLoClear
mdefine_line|#define OHCI1394_AsReqFilterLoClear           0x10C
DECL|macro|OHCI1394_PhyReqFilterHiSet
mdefine_line|#define OHCI1394_PhyReqFilterHiSet            0x110
DECL|macro|OHCI1394_PhyReqFilterHiClear
mdefine_line|#define OHCI1394_PhyReqFilterHiClear          0x114
DECL|macro|OHCI1394_PhyReqFilterLoSet
mdefine_line|#define OHCI1394_PhyReqFilterLoSet            0x118
DECL|macro|OHCI1394_PhyReqFilterLoClear
mdefine_line|#define OHCI1394_PhyReqFilterLoClear          0x11C
DECL|macro|OHCI1394_PhyUpperBound
mdefine_line|#define OHCI1394_PhyUpperBound                0x120
DECL|macro|OHCI1394_AsReqTrContextControlSet
mdefine_line|#define OHCI1394_AsReqTrContextControlSet     0x180
DECL|macro|OHCI1394_AsReqTrContextControlClear
mdefine_line|#define OHCI1394_AsReqTrContextControlClear   0x184
DECL|macro|OHCI1394_AsReqTrCommandPtr
mdefine_line|#define OHCI1394_AsReqTrCommandPtr            0x18C
DECL|macro|OHCI1394_AsRspTrContextControlSet
mdefine_line|#define OHCI1394_AsRspTrContextControlSet     0x1A0
DECL|macro|OHCI1394_AsRspTrContextControlClear
mdefine_line|#define OHCI1394_AsRspTrContextControlClear   0x1A4
DECL|macro|OHCI1394_AsRspTrCommandPtr
mdefine_line|#define OHCI1394_AsRspTrCommandPtr            0x1AC
DECL|macro|OHCI1394_AsReqRcvContextControlSet
mdefine_line|#define OHCI1394_AsReqRcvContextControlSet    0x1C0
DECL|macro|OHCI1394_AsReqRcvContextControlClear
mdefine_line|#define OHCI1394_AsReqRcvContextControlClear  0x1C4
DECL|macro|OHCI1394_AsReqRcvCommandPtr
mdefine_line|#define OHCI1394_AsReqRcvCommandPtr           0x1CC
DECL|macro|OHCI1394_AsRspRcvContextControlSet
mdefine_line|#define OHCI1394_AsRspRcvContextControlSet    0x1E0
DECL|macro|OHCI1394_AsRspRcvContextControlClear
mdefine_line|#define OHCI1394_AsRspRcvContextControlClear  0x1E4
DECL|macro|OHCI1394_AsRspRcvCommandPtr
mdefine_line|#define OHCI1394_AsRspRcvCommandPtr           0x1EC
multiline_comment|/* Isochronous receive registers */
multiline_comment|/* Add (32 * n) for context n */
DECL|macro|OHCI1394_IrRcvContextControlSet
mdefine_line|#define OHCI1394_IrRcvContextControlSet       0x400
DECL|macro|OHCI1394_IrRcvContextControlClear
mdefine_line|#define OHCI1394_IrRcvContextControlClear     0x404
DECL|macro|OHCI1394_IrRcvCommandPtr
mdefine_line|#define OHCI1394_IrRcvCommandPtr              0x40C
DECL|macro|OHCI1394_IrRcvContextMatch
mdefine_line|#define OHCI1394_IrRcvContextMatch            0x410
multiline_comment|/* Interrupts Mask/Events */
DECL|macro|OHCI1394_reqTxComplete
mdefine_line|#define OHCI1394_reqTxComplete           0x00000001
DECL|macro|OHCI1394_respTxComplete
mdefine_line|#define OHCI1394_respTxComplete          0x00000002
DECL|macro|OHCI1394_ARRQ
mdefine_line|#define OHCI1394_ARRQ                    0x00000004
DECL|macro|OHCI1394_ARRS
mdefine_line|#define OHCI1394_ARRS                    0x00000008
DECL|macro|OHCI1394_RQPkt
mdefine_line|#define OHCI1394_RQPkt                   0x00000010
DECL|macro|OHCI1394_RSPkt
mdefine_line|#define OHCI1394_RSPkt                   0x00000020
DECL|macro|OHCI1394_isochTx
mdefine_line|#define OHCI1394_isochTx                 0x00000040
DECL|macro|OHCI1394_isochRx
mdefine_line|#define OHCI1394_isochRx                 0x00000080
DECL|macro|OHCI1394_postedWriteErr
mdefine_line|#define OHCI1394_postedWriteErr          0x00001000
DECL|macro|OHCI1394_lockRespErr
mdefine_line|#define OHCI1394_lockRespErr             0x00002000
DECL|macro|OHCI1394_selfIDComplete
mdefine_line|#define OHCI1394_selfIDComplete          0x00010000
DECL|macro|OHCI1394_busReset
mdefine_line|#define OHCI1394_busReset                0x00020000
DECL|macro|OHCI1394_phy
mdefine_line|#define OHCI1394_phy                     0x00080000
DECL|macro|OHCI1394_cycleSynch
mdefine_line|#define OHCI1394_cycleSynch              0x00100000
DECL|macro|OHCI1394_cycle64Seconds
mdefine_line|#define OHCI1394_cycle64Seconds          0x00200000
DECL|macro|OHCI1394_cycleLost
mdefine_line|#define OHCI1394_cycleLost               0x00400000
DECL|macro|OHCI1394_cycleInconsistent
mdefine_line|#define OHCI1394_cycleInconsistent       0x00800000
DECL|macro|OHCI1394_unrecoverableError
mdefine_line|#define OHCI1394_unrecoverableError      0x01000000
DECL|macro|OHCI1394_cycleTooLong
mdefine_line|#define OHCI1394_cycleTooLong            0x02000000
DECL|macro|OHCI1394_phyRegRcvd
mdefine_line|#define OHCI1394_phyRegRcvd              0x04000000
DECL|macro|OHCI1394_masterIntEnable
mdefine_line|#define OHCI1394_masterIntEnable         0x80000000
DECL|macro|OUTPUT_MORE
mdefine_line|#define OUTPUT_MORE                      0x00000000
DECL|macro|OUTPUT_MORE_IMMEDIATE
mdefine_line|#define OUTPUT_MORE_IMMEDIATE            0x02000000
DECL|macro|OUTPUT_LAST
mdefine_line|#define OUTPUT_LAST                      0x103c0000
DECL|macro|OUTPUT_LAST_IMMEDIATE
mdefine_line|#define OUTPUT_LAST_IMMEDIATE            0x123c0000
DECL|macro|DMA_SPEED_100
mdefine_line|#define DMA_SPEED_100                    0x0
DECL|macro|DMA_SPEED_200
mdefine_line|#define DMA_SPEED_200                    0x1
DECL|macro|DMA_SPEED_400
mdefine_line|#define DMA_SPEED_400                    0x2
macro_line|#endif
eof
