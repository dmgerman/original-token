multiline_comment|/***********************************************************************&n;;*&t;File Name : TMSCSIM.H&t;&t;&t;&t;&t;       *&n;;*&t;&t;    TEKRAM DC-390(T) PCI SCSI Bus Master Host Adapter  *&n;;*&t;&t;    Device Driver&t;&t;&t;&t;       *&n;;***********************************************************************/
macro_line|#ifndef TMSCSIM_H
DECL|macro|TMSCSIM_H
mdefine_line|#define TMSCSIM_H
DECL|macro|IRQ_NONE
mdefine_line|#define IRQ_NONE 255
DECL|typedef|UCHAR
r_typedef
r_int
r_char
id|UCHAR
suffix:semicolon
DECL|typedef|USHORT
r_typedef
r_int
r_int
id|USHORT
suffix:semicolon
DECL|typedef|ULONG
r_typedef
r_int
r_int
id|ULONG
suffix:semicolon
DECL|typedef|UINT
r_typedef
r_int
r_int
id|UINT
suffix:semicolon
DECL|typedef|PUCHAR
r_typedef
id|UCHAR
op_star
id|PUCHAR
suffix:semicolon
DECL|typedef|PUSHORT
r_typedef
id|USHORT
op_star
id|PUSHORT
suffix:semicolon
DECL|typedef|PULONG
r_typedef
id|ULONG
op_star
id|PULONG
suffix:semicolon
DECL|typedef|PSHT
r_typedef
id|Scsi_Host_Template
op_star
id|PSHT
suffix:semicolon
DECL|typedef|PSH
r_typedef
r_struct
id|Scsi_Host
op_star
id|PSH
suffix:semicolon
DECL|typedef|PSCSIDEV
r_typedef
id|Scsi_Device
op_star
id|PSCSIDEV
suffix:semicolon
DECL|typedef|PSCSICMD
r_typedef
id|Scsi_Cmnd
op_star
id|PSCSICMD
suffix:semicolon
DECL|typedef|PVOID
r_typedef
r_void
op_star
id|PVOID
suffix:semicolon
DECL|typedef|PSGL
DECL|typedef|SGL
r_typedef
r_struct
id|scatterlist
op_star
id|PSGL
comma
id|SGL
suffix:semicolon
multiline_comment|/*;-----------------------------------------------------------------------*/
DECL|struct|_SyncMsg
r_typedef
r_struct
id|_SyncMsg
(brace
DECL|member|ExtendMsg
id|UCHAR
id|ExtendMsg
suffix:semicolon
DECL|member|ExtMsgLen
id|UCHAR
id|ExtMsgLen
suffix:semicolon
DECL|member|SyncXferReq
id|UCHAR
id|SyncXferReq
suffix:semicolon
DECL|member|Period
id|UCHAR
id|Period
suffix:semicolon
DECL|member|ReqOffset
id|UCHAR
id|ReqOffset
suffix:semicolon
DECL|typedef|SyncMsg
)brace
id|SyncMsg
suffix:semicolon
multiline_comment|/*;-----------------------------------------------------------------------*/
DECL|struct|_Capacity
r_typedef
r_struct
id|_Capacity
(brace
DECL|member|BlockCount
id|ULONG
id|BlockCount
suffix:semicolon
DECL|member|BlockLength
id|ULONG
id|BlockLength
suffix:semicolon
DECL|typedef|Capacity
)brace
id|Capacity
suffix:semicolon
multiline_comment|/*;-----------------------------------------------------------------------*/
DECL|struct|_SGentry
r_typedef
r_struct
id|_SGentry
(brace
DECL|member|SGXferDataPtr
id|ULONG
id|SGXferDataPtr
suffix:semicolon
DECL|member|SGXferDataLen
id|ULONG
id|SGXferDataLen
suffix:semicolon
DECL|typedef|SGentry
)brace
id|SGentry
suffix:semicolon
DECL|struct|_SGentry1
r_typedef
r_struct
id|_SGentry1
(brace
DECL|member|SGXLen
id|ULONG
id|SGXLen
suffix:semicolon
DECL|member|SGXPtr
id|ULONG
id|SGXPtr
suffix:semicolon
DECL|typedef|SGentry1
DECL|typedef|PSGE
)brace
id|SGentry1
comma
op_star
id|PSGE
suffix:semicolon
DECL|macro|MAX_ADAPTER_NUM
mdefine_line|#define MAX_ADAPTER_NUM &t;4
DECL|macro|MAX_DEVICES
mdefine_line|#define MAX_DEVICES&t;&t;10
DECL|macro|MAX_SG_LIST_BUF
mdefine_line|#define MAX_SG_LIST_BUF &t;16
DECL|macro|MAX_CMD_QUEUE
mdefine_line|#define MAX_CMD_QUEUE&t;&t;20
DECL|macro|MAX_CMD_PER_LUN
mdefine_line|#define MAX_CMD_PER_LUN &t;8
DECL|macro|MAX_SCSI_ID
mdefine_line|#define MAX_SCSI_ID&t;&t;8
DECL|macro|MAX_SRB_CNT
mdefine_line|#define MAX_SRB_CNT&t;&t;MAX_CMD_QUEUE+4
DECL|macro|END_SCAN
mdefine_line|#define END_SCAN&t;&t;2
DECL|macro|SEL_TIMEOUT
mdefine_line|#define SEL_TIMEOUT&t;&t;153&t;/* 250 ms selection timeout (@ 40 MHz) */
multiline_comment|/*&n;;-----------------------------------------------------------------------&n;; SCSI Request Block&n;;-----------------------------------------------------------------------&n;*/
DECL|struct|_SRB
r_struct
id|_SRB
(brace
DECL|member|CmdBlock
id|UCHAR
id|CmdBlock
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|pNextSRB
r_struct
id|_SRB
op_star
id|pNextSRB
suffix:semicolon
DECL|member|pSRBDCB
r_struct
id|_DCB
op_star
id|pSRBDCB
suffix:semicolon
DECL|member|pcmd
id|PSCSICMD
id|pcmd
suffix:semicolon
DECL|member|pSegmentList
id|PSGL
id|pSegmentList
suffix:semicolon
DECL|member|PhysSRB
id|ULONG
id|PhysSRB
suffix:semicolon
DECL|member|TotalXferredLen
id|ULONG
id|TotalXferredLen
suffix:semicolon
DECL|member|SGPhysAddr
id|ULONG
id|SGPhysAddr
suffix:semicolon
multiline_comment|/*;a segment starting address */
DECL|member|SGToBeXferLen
id|ULONG
id|SGToBeXferLen
suffix:semicolon
multiline_comment|/*; to be xfer length */
DECL|member|Segmentx
id|SGL
id|Segmentx
suffix:semicolon
multiline_comment|/* make a one entry of S/G list table */
DECL|member|pMsgPtr
id|PUCHAR
id|pMsgPtr
suffix:semicolon
DECL|member|SRBState
id|USHORT
id|SRBState
suffix:semicolon
DECL|member|Revxx2
id|USHORT
id|Revxx2
suffix:semicolon
multiline_comment|/* ??? */
DECL|member|MsgInBuf
id|UCHAR
id|MsgInBuf
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|MsgOutBuf
id|UCHAR
id|MsgOutBuf
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|AdaptStatus
id|UCHAR
id|AdaptStatus
suffix:semicolon
DECL|member|TargetStatus
id|UCHAR
id|TargetStatus
suffix:semicolon
DECL|member|MsgCnt
id|UCHAR
id|MsgCnt
suffix:semicolon
DECL|member|EndMessage
id|UCHAR
id|EndMessage
suffix:semicolon
DECL|member|TagNumber
id|UCHAR
id|TagNumber
suffix:semicolon
DECL|member|SGcount
id|UCHAR
id|SGcount
suffix:semicolon
DECL|member|SGIndex
id|UCHAR
id|SGIndex
suffix:semicolon
DECL|member|IORBFlag
id|UCHAR
id|IORBFlag
suffix:semicolon
multiline_comment|/*;81h-Reset, 2-retry */
DECL|member|SRBStatus
id|UCHAR
id|SRBStatus
suffix:semicolon
DECL|member|RetryCnt
id|UCHAR
id|RetryCnt
suffix:semicolon
DECL|member|SRBFlag
id|UCHAR
id|SRBFlag
suffix:semicolon
multiline_comment|/*; b0-AutoReqSense,b6-Read,b7-write */
multiline_comment|/*; b4-settimeout,b5-Residual valid */
DECL|member|ScsiCmdLen
id|UCHAR
id|ScsiCmdLen
suffix:semicolon
DECL|member|ScsiPhase
id|UCHAR
id|ScsiPhase
suffix:semicolon
DECL|member|Reserved3
id|UCHAR
id|Reserved3
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/*;for dword alignment */
DECL|member|Segment0
id|ULONG
id|Segment0
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|Segment1
id|ULONG
id|Segment1
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|DC390_SRB
DECL|typedef|PSRB
r_typedef
r_struct
id|_SRB
id|DC390_SRB
comma
op_star
id|PSRB
suffix:semicolon
multiline_comment|/*&n;;-----------------------------------------------------------------------&n;; Device Control Block&n;;-----------------------------------------------------------------------&n;*/
DECL|struct|_DCB
r_struct
id|_DCB
(brace
DECL|member|pNextDCB
r_struct
id|_DCB
op_star
id|pNextDCB
suffix:semicolon
DECL|member|pDCBACB
r_struct
id|_ACB
op_star
id|pDCBACB
suffix:semicolon
DECL|member|pQIORBhead
id|PSCSICMD
id|pQIORBhead
suffix:semicolon
DECL|member|pQIORBtail
id|PSCSICMD
id|pQIORBtail
suffix:semicolon
DECL|member|AboIORBhead
id|PSCSICMD
id|AboIORBhead
suffix:semicolon
DECL|member|AboIORBtail
id|PSCSICMD
id|AboIORBtail
suffix:semicolon
DECL|member|QIORBCnt
id|USHORT
id|QIORBCnt
suffix:semicolon
DECL|member|AboIORBcnt
id|USHORT
id|AboIORBcnt
suffix:semicolon
DECL|member|pWaitingSRB
id|PSRB
id|pWaitingSRB
suffix:semicolon
DECL|member|pWaitLast
id|PSRB
id|pWaitLast
suffix:semicolon
DECL|member|pGoingSRB
id|PSRB
id|pGoingSRB
suffix:semicolon
DECL|member|pGoingLast
id|PSRB
id|pGoingLast
suffix:semicolon
DECL|member|pActiveSRB
id|PSRB
id|pActiveSRB
suffix:semicolon
DECL|member|GoingSRBCnt
id|USHORT
id|GoingSRBCnt
suffix:semicolon
DECL|member|WaitSRBCnt
id|USHORT
id|WaitSRBCnt
suffix:semicolon
multiline_comment|/* ??? */
DECL|member|TagMask
id|ULONG
id|TagMask
suffix:semicolon
DECL|member|MaxCommand
id|USHORT
id|MaxCommand
suffix:semicolon
DECL|member|AdaptIndex
id|USHORT
id|AdaptIndex
suffix:semicolon
multiline_comment|/*; UnitInfo struc start */
DECL|member|UnitIndex
id|USHORT
id|UnitIndex
suffix:semicolon
multiline_comment|/*; nth Unit on this card */
DECL|member|UnitSCSIID
id|UCHAR
id|UnitSCSIID
suffix:semicolon
multiline_comment|/*; SCSI Target ID  (SCSI Only) */
DECL|member|UnitSCSILUN
id|UCHAR
id|UnitSCSILUN
suffix:semicolon
multiline_comment|/*; SCSI Log.  Unit (SCSI Only) */
DECL|member|IdentifyMsg
id|UCHAR
id|IdentifyMsg
suffix:semicolon
DECL|member|CtrlR1
id|UCHAR
id|CtrlR1
suffix:semicolon
DECL|member|CtrlR3
id|UCHAR
id|CtrlR3
suffix:semicolon
DECL|member|CtrlR4
id|UCHAR
id|CtrlR4
suffix:semicolon
DECL|member|InqDataBuf
id|UCHAR
id|InqDataBuf
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|CapacityBuf
id|UCHAR
id|CapacityBuf
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|DevMode
id|UCHAR
id|DevMode
suffix:semicolon
DECL|member|AdpMode
id|UCHAR
id|AdpMode
suffix:semicolon
DECL|member|SyncMode
id|UCHAR
id|SyncMode
suffix:semicolon
multiline_comment|/*; 0:async mode */
DECL|member|NegoPeriod
id|UCHAR
id|NegoPeriod
suffix:semicolon
multiline_comment|/*;for nego. */
DECL|member|SyncPeriod
id|UCHAR
id|SyncPeriod
suffix:semicolon
multiline_comment|/*;for reg. */
DECL|member|SyncOffset
id|UCHAR
id|SyncOffset
suffix:semicolon
multiline_comment|/*;for reg. and nego.(low nibble) */
DECL|member|UnitCtrlFlag
id|UCHAR
id|UnitCtrlFlag
suffix:semicolon
DECL|member|DCBFlag
id|UCHAR
id|DCBFlag
suffix:semicolon
DECL|member|DevType
id|UCHAR
id|DevType
suffix:semicolon
DECL|member|Reserved2
id|UCHAR
id|Reserved2
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/*;for dword alignment */
)brace
suffix:semicolon
DECL|typedef|DC390_DCB
DECL|typedef|PDCB
r_typedef
r_struct
id|_DCB
id|DC390_DCB
comma
op_star
id|PDCB
suffix:semicolon
multiline_comment|/*&n;;-----------------------------------------------------------------------&n;; Adapter Control Block&n;;-----------------------------------------------------------------------&n;*/
DECL|struct|_ACB
r_struct
id|_ACB
(brace
DECL|member|PhysACB
id|ULONG
id|PhysACB
suffix:semicolon
DECL|member|pScsiHost
id|PSH
id|pScsiHost
suffix:semicolon
DECL|member|pNextACB
r_struct
id|_ACB
op_star
id|pNextACB
suffix:semicolon
DECL|member|IOPortBase
id|USHORT
id|IOPortBase
suffix:semicolon
DECL|member|Revxx1
id|USHORT
id|Revxx1
suffix:semicolon
multiline_comment|/* ??? */
DECL|member|pLinkDCB
id|PDCB
id|pLinkDCB
suffix:semicolon
DECL|member|pDCBRunRobin
id|PDCB
id|pDCBRunRobin
suffix:semicolon
DECL|member|pActiveDCB
id|PDCB
id|pActiveDCB
suffix:semicolon
DECL|member|pDCB_free
id|PDCB
id|pDCB_free
suffix:semicolon
DECL|member|pFreeSRB
id|PSRB
id|pFreeSRB
suffix:semicolon
DECL|member|pTmpSRB
id|PSRB
id|pTmpSRB
suffix:semicolon
DECL|member|SRBCount
id|USHORT
id|SRBCount
suffix:semicolon
DECL|member|AdapterIndex
id|USHORT
id|AdapterIndex
suffix:semicolon
multiline_comment|/*; nth Adapter this driver */
DECL|member|max_id
id|USHORT
id|max_id
suffix:semicolon
DECL|member|max_lun
id|USHORT
id|max_lun
suffix:semicolon
DECL|member|msgin123
id|UCHAR
id|msgin123
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|status
id|UCHAR
id|status
suffix:semicolon
DECL|member|AdaptSCSIID
id|UCHAR
id|AdaptSCSIID
suffix:semicolon
multiline_comment|/*; Adapter SCSI Target ID */
DECL|member|AdaptSCSILUN
id|UCHAR
id|AdaptSCSILUN
suffix:semicolon
multiline_comment|/*; Adapter SCSI LUN */
DECL|member|DeviceCnt
id|UCHAR
id|DeviceCnt
suffix:semicolon
DECL|member|IRQLevel
id|UCHAR
id|IRQLevel
suffix:semicolon
DECL|member|TagMaxNum
id|UCHAR
id|TagMaxNum
suffix:semicolon
DECL|member|ACBFlag
id|UCHAR
id|ACBFlag
suffix:semicolon
DECL|member|Gmode2
id|UCHAR
id|Gmode2
suffix:semicolon
DECL|member|LUNchk
id|UCHAR
id|LUNchk
suffix:semicolon
DECL|member|scan_devices
id|UCHAR
id|scan_devices
suffix:semicolon
DECL|member|HostID_Bit
id|UCHAR
id|HostID_Bit
suffix:semicolon
DECL|member|Reserved1
id|UCHAR
id|Reserved1
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/*;for dword alignment */
DECL|member|DCBmap
id|UCHAR
id|DCBmap
(braket
id|MAX_SCSI_ID
)braket
suffix:semicolon
DECL|member|DCB_array
id|DC390_DCB
id|DCB_array
(braket
id|MAX_DEVICES
)braket
suffix:semicolon
multiline_comment|/* +74h,  Len=3E8 */
DECL|member|SRB_array
id|DC390_SRB
id|SRB_array
(braket
id|MAX_SRB_CNT
)braket
suffix:semicolon
multiline_comment|/* +45Ch, Len=&t;*/
DECL|member|TmpSRB
id|DC390_SRB
id|TmpSRB
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|DC390_ACB
DECL|typedef|PACB
r_typedef
r_struct
id|_ACB
id|DC390_ACB
comma
op_star
id|PACB
suffix:semicolon
multiline_comment|/*;-----------------------------------------------------------------------*/
DECL|macro|BIT31
mdefine_line|#define BIT31&t;0x80000000
DECL|macro|BIT30
mdefine_line|#define BIT30&t;0x40000000
DECL|macro|BIT29
mdefine_line|#define BIT29&t;0x20000000
DECL|macro|BIT28
mdefine_line|#define BIT28&t;0x10000000
DECL|macro|BIT27
mdefine_line|#define BIT27&t;0x08000000
DECL|macro|BIT26
mdefine_line|#define BIT26&t;0x04000000
DECL|macro|BIT25
mdefine_line|#define BIT25&t;0x02000000
DECL|macro|BIT24
mdefine_line|#define BIT24&t;0x01000000
DECL|macro|BIT23
mdefine_line|#define BIT23&t;0x00800000
DECL|macro|BIT22
mdefine_line|#define BIT22&t;0x00400000
DECL|macro|BIT21
mdefine_line|#define BIT21&t;0x00200000
DECL|macro|BIT20
mdefine_line|#define BIT20&t;0x00100000
DECL|macro|BIT19
mdefine_line|#define BIT19&t;0x00080000
DECL|macro|BIT18
mdefine_line|#define BIT18&t;0x00040000
DECL|macro|BIT17
mdefine_line|#define BIT17&t;0x00020000
DECL|macro|BIT16
mdefine_line|#define BIT16&t;0x00010000
DECL|macro|BIT15
mdefine_line|#define BIT15&t;0x00008000
DECL|macro|BIT14
mdefine_line|#define BIT14&t;0x00004000
DECL|macro|BIT13
mdefine_line|#define BIT13&t;0x00002000
DECL|macro|BIT12
mdefine_line|#define BIT12&t;0x00001000
DECL|macro|BIT11
mdefine_line|#define BIT11&t;0x00000800
DECL|macro|BIT10
mdefine_line|#define BIT10&t;0x00000400
DECL|macro|BIT9
mdefine_line|#define BIT9&t;0x00000200
DECL|macro|BIT8
mdefine_line|#define BIT8&t;0x00000100
DECL|macro|BIT7
mdefine_line|#define BIT7&t;0x00000080
DECL|macro|BIT6
mdefine_line|#define BIT6&t;0x00000040
DECL|macro|BIT5
mdefine_line|#define BIT5&t;0x00000020
DECL|macro|BIT4
mdefine_line|#define BIT4&t;0x00000010
DECL|macro|BIT3
mdefine_line|#define BIT3&t;0x00000008
DECL|macro|BIT2
mdefine_line|#define BIT2&t;0x00000004
DECL|macro|BIT1
mdefine_line|#define BIT1&t;0x00000002
DECL|macro|BIT0
mdefine_line|#define BIT0&t;0x00000001
multiline_comment|/*;---UnitCtrlFlag */
DECL|macro|UNIT_ALLOCATED
mdefine_line|#define UNIT_ALLOCATED&t;BIT0
DECL|macro|UNIT_INFO_CHANGED
mdefine_line|#define UNIT_INFO_CHANGED BIT1
DECL|macro|FORMATING_MEDIA
mdefine_line|#define FORMATING_MEDIA BIT2
DECL|macro|UNIT_RETRY
mdefine_line|#define UNIT_RETRY&t;BIT3
multiline_comment|/*;---UnitFlags */
DECL|macro|DASD_SUPPORT
mdefine_line|#define DASD_SUPPORT&t;BIT0
DECL|macro|SCSI_SUPPORT
mdefine_line|#define SCSI_SUPPORT&t;BIT1
DECL|macro|ASPI_SUPPORT
mdefine_line|#define ASPI_SUPPORT&t;BIT2
multiline_comment|/*;----SRBState machine definition */
DECL|macro|SRB_FREE
mdefine_line|#define SRB_FREE&t;0
DECL|macro|SRB_WAIT
mdefine_line|#define SRB_WAIT&t;BIT0
DECL|macro|SRB_READY
mdefine_line|#define SRB_READY&t;BIT1
DECL|macro|SRB_MSGOUT
mdefine_line|#define SRB_MSGOUT&t;BIT2&t;/*;arbitration+msg_out 1st byte*/
DECL|macro|SRB_MSGIN
mdefine_line|#define SRB_MSGIN&t;BIT3
DECL|macro|SRB_MSGIN_MULTI
mdefine_line|#define SRB_MSGIN_MULTI BIT4
DECL|macro|SRB_COMMAND
mdefine_line|#define SRB_COMMAND&t;BIT5
DECL|macro|SRB_START_
mdefine_line|#define SRB_START_&t;BIT6&t;/*;arbitration+msg_out+command_out*/
DECL|macro|SRB_DISCONNECT
mdefine_line|#define SRB_DISCONNECT&t;BIT7
DECL|macro|SRB_DATA_XFER
mdefine_line|#define SRB_DATA_XFER&t;BIT8
DECL|macro|SRB_XFERPAD
mdefine_line|#define SRB_XFERPAD&t;BIT9
DECL|macro|SRB_STATUS
mdefine_line|#define SRB_STATUS&t;BIT10
DECL|macro|SRB_COMPLETED
mdefine_line|#define SRB_COMPLETED&t;BIT11
DECL|macro|SRB_ABORT_SENT
mdefine_line|#define SRB_ABORT_SENT&t;BIT12
DECL|macro|DO_SYNC_NEGO
mdefine_line|#define DO_SYNC_NEGO&t;BIT13
DECL|macro|SRB_UNEXPECT_RESEL
mdefine_line|#define SRB_UNEXPECT_RESEL BIT14
multiline_comment|/*;---ACBFlag */
DECL|macro|RESET_DEV
mdefine_line|#define RESET_DEV&t;BIT0
DECL|macro|RESET_DETECT
mdefine_line|#define RESET_DETECT&t;BIT1
DECL|macro|RESET_DONE
mdefine_line|#define RESET_DONE&t;BIT2
multiline_comment|/*;---DCBFlag */
DECL|macro|ABORT_DEV_
mdefine_line|#define ABORT_DEV_&t;BIT0
multiline_comment|/*;---SRBstatus */
DECL|macro|SRB_OK
mdefine_line|#define SRB_OK&t;&t;BIT0
DECL|macro|ABORTION
mdefine_line|#define ABORTION&t;BIT1
DECL|macro|OVER_RUN
mdefine_line|#define OVER_RUN&t;BIT2
DECL|macro|UNDER_RUN
mdefine_line|#define UNDER_RUN&t;BIT3
DECL|macro|PARITY_ERROR
mdefine_line|#define PARITY_ERROR&t;BIT4
DECL|macro|SRB_ERROR
mdefine_line|#define SRB_ERROR&t;BIT5
multiline_comment|/*;---SRBFlag */
DECL|macro|DATAOUT
mdefine_line|#define DATAOUT &t;BIT7
DECL|macro|DATAIN
mdefine_line|#define DATAIN&t;&t;BIT6
DECL|macro|RESIDUAL_VALID
mdefine_line|#define RESIDUAL_VALID&t;BIT5
DECL|macro|ENABLE_TIMER
mdefine_line|#define ENABLE_TIMER&t;BIT4
DECL|macro|RESET_DEV0
mdefine_line|#define RESET_DEV0&t;BIT2
DECL|macro|ABORT_DEV
mdefine_line|#define ABORT_DEV&t;BIT1
DECL|macro|AUTO_REQSENSE
mdefine_line|#define AUTO_REQSENSE&t;BIT0
multiline_comment|/*;---Adapter status */
DECL|macro|H_STATUS_GOOD
mdefine_line|#define H_STATUS_GOOD&t; 0
DECL|macro|H_SEL_TIMEOUT
mdefine_line|#define H_SEL_TIMEOUT&t; 0x11
DECL|macro|H_OVER_UNDER_RUN
mdefine_line|#define H_OVER_UNDER_RUN 0x12
DECL|macro|H_UNEXP_BUS_FREE
mdefine_line|#define H_UNEXP_BUS_FREE 0x13
DECL|macro|H_TARGET_PHASE_F
mdefine_line|#define H_TARGET_PHASE_F 0x14
DECL|macro|H_INVALID_CCB_OP
mdefine_line|#define H_INVALID_CCB_OP 0x16
DECL|macro|H_LINK_CCB_BAD
mdefine_line|#define H_LINK_CCB_BAD&t; 0x17
DECL|macro|H_BAD_TARGET_DIR
mdefine_line|#define H_BAD_TARGET_DIR 0x18
DECL|macro|H_DUPLICATE_CCB
mdefine_line|#define H_DUPLICATE_CCB  0x19
DECL|macro|H_BAD_CCB_OR_SG
mdefine_line|#define H_BAD_CCB_OR_SG  0x1A
DECL|macro|H_ABORT
mdefine_line|#define H_ABORT &t; 0x0FF
multiline_comment|/*; SCSI Status byte codes*/
DECL|macro|SCSI_STAT_GOOD
mdefine_line|#define SCSI_STAT_GOOD&t;&t;0x0&t;/*;  Good status */
DECL|macro|SCSI_STAT_CHECKCOND
mdefine_line|#define SCSI_STAT_CHECKCOND&t;0x02&t;/*;  SCSI Check Condition */
DECL|macro|SCSI_STAT_CONDMET
mdefine_line|#define SCSI_STAT_CONDMET&t;0x04&t;/*;  Condition Met */
DECL|macro|SCSI_STAT_BUSY
mdefine_line|#define SCSI_STAT_BUSY&t;&t;0x08&t;/*;  Target busy status */
DECL|macro|SCSI_STAT_INTER
mdefine_line|#define SCSI_STAT_INTER &t;0x10&t;/*;  Intermediate status */
DECL|macro|SCSI_STAT_INTERCONDMET
mdefine_line|#define SCSI_STAT_INTERCONDMET&t;0x14&t;/*;  Intermediate condition met */
DECL|macro|SCSI_STAT_RESCONFLICT
mdefine_line|#define SCSI_STAT_RESCONFLICT&t;0x18&t;/*;  Reservation conflict */
DECL|macro|SCSI_STAT_CMDTERM
mdefine_line|#define SCSI_STAT_CMDTERM&t;0x22&t;/*;  Command Terminated */
DECL|macro|SCSI_STAT_QUEUEFULL
mdefine_line|#define SCSI_STAT_QUEUEFULL&t;0x28&t;/*;  Queue Full */
DECL|macro|SCSI_STAT_UNEXP_BUS_F
mdefine_line|#define SCSI_STAT_UNEXP_BUS_F&t;0xFD&t;/*;  Unexpect Bus Free */
DECL|macro|SCSI_STAT_BUS_RST_DETECT
mdefine_line|#define SCSI_STAT_BUS_RST_DETECT 0xFE&t;/*;  Scsi Bus Reset detected */
DECL|macro|SCSI_STAT_SEL_TIMEOUT
mdefine_line|#define SCSI_STAT_SEL_TIMEOUT&t;0xFF&t;/*;  Selection Time out */
multiline_comment|/*;---Sync_Mode */
DECL|macro|SYNC_DISABLE
mdefine_line|#define SYNC_DISABLE&t;0
DECL|macro|SYNC_ENABLE
mdefine_line|#define SYNC_ENABLE&t;BIT0
DECL|macro|SYNC_NEGO_DONE
mdefine_line|#define SYNC_NEGO_DONE&t;BIT1
DECL|macro|WIDE_ENABLE
mdefine_line|#define WIDE_ENABLE&t;BIT2
DECL|macro|WIDE_NEGO_DONE
mdefine_line|#define WIDE_NEGO_DONE&t;BIT3
DECL|macro|EN_TAG_QUEUING
mdefine_line|#define EN_TAG_QUEUING&t;BIT4
DECL|macro|EN_ATN_STOP
mdefine_line|#define EN_ATN_STOP&t;BIT5
DECL|macro|SYNC_NEGO_OFFSET
mdefine_line|#define SYNC_NEGO_OFFSET 15
multiline_comment|/*;---SCSI bus phase*/
DECL|macro|SCSI_DATA_OUT
mdefine_line|#define SCSI_DATA_OUT&t;0
DECL|macro|SCSI_DATA_IN
mdefine_line|#define SCSI_DATA_IN&t;1
DECL|macro|SCSI_COMMAND
mdefine_line|#define SCSI_COMMAND&t;2
DECL|macro|SCSI_STATUS_
mdefine_line|#define SCSI_STATUS_&t;3
DECL|macro|SCSI_NOP0
mdefine_line|#define SCSI_NOP0&t;4
DECL|macro|SCSI_NOP1
mdefine_line|#define SCSI_NOP1&t;5
DECL|macro|SCSI_MSG_OUT
mdefine_line|#define SCSI_MSG_OUT&t;6
DECL|macro|SCSI_MSG_IN
mdefine_line|#define SCSI_MSG_IN&t;7
multiline_comment|/*;----SCSI MSG BYTE*/
DECL|macro|MSG_COMPLETE
mdefine_line|#define MSG_COMPLETE&t;&t;0x00
DECL|macro|MSG_EXTENDED
mdefine_line|#define MSG_EXTENDED&t;&t;0x01
DECL|macro|MSG_SAVE_PTR
mdefine_line|#define MSG_SAVE_PTR&t;&t;0x02
DECL|macro|MSG_RESTORE_PTR
mdefine_line|#define MSG_RESTORE_PTR &t;0x03
DECL|macro|MSG_DISCONNECT
mdefine_line|#define MSG_DISCONNECT&t;&t;0x04
DECL|macro|MSG_INITIATOR_ERROR
mdefine_line|#define MSG_INITIATOR_ERROR&t;0x05
DECL|macro|MSG_ABORT
mdefine_line|#define MSG_ABORT&t;&t;0x06
DECL|macro|MSG_REJECT_
mdefine_line|#define MSG_REJECT_&t;&t;0x07
DECL|macro|MSG_NOP
mdefine_line|#define MSG_NOP &t;&t;0x08
DECL|macro|MSG_PARITY_ERROR
mdefine_line|#define MSG_PARITY_ERROR&t;0x09
DECL|macro|MSG_LINK_CMD_COMPL
mdefine_line|#define MSG_LINK_CMD_COMPL&t;0x0A
DECL|macro|MSG_LINK_CMD_COMPL_FLG
mdefine_line|#define MSG_LINK_CMD_COMPL_FLG&t;0x0B
DECL|macro|MSG_BUS_RESET
mdefine_line|#define MSG_BUS_RESET&t;&t;0x0C
DECL|macro|MSG_ABORT_TAG
mdefine_line|#define MSG_ABORT_TAG&t;&t;0x0D
DECL|macro|MSG_SIMPLE_QTAG
mdefine_line|#define MSG_SIMPLE_QTAG &t;0x20
DECL|macro|MSG_HEAD_QTAG
mdefine_line|#define MSG_HEAD_QTAG&t;&t;0x21
DECL|macro|MSG_ORDER_QTAG
mdefine_line|#define MSG_ORDER_QTAG&t;&t;0x22
DECL|macro|MSG_IDENTIFY
mdefine_line|#define MSG_IDENTIFY&t;&t;0x80
DECL|macro|MSG_HOST_ID
mdefine_line|#define MSG_HOST_ID&t;&t;0x0C0
multiline_comment|/*;----SCSI STATUS BYTE*/
DECL|macro|STATUS_GOOD
mdefine_line|#define STATUS_GOOD&t;&t;0x00
DECL|macro|CHECK_CONDITION_
mdefine_line|#define CHECK_CONDITION_&t;0x02
DECL|macro|STATUS_BUSY
mdefine_line|#define STATUS_BUSY&t;&t;0x08
DECL|macro|STATUS_INTERMEDIATE
mdefine_line|#define STATUS_INTERMEDIATE&t;0x10
DECL|macro|RESERVE_CONFLICT
mdefine_line|#define RESERVE_CONFLICT&t;0x18
multiline_comment|/* cmd-&gt;result */
DECL|macro|STATUS_MASK_
mdefine_line|#define STATUS_MASK_&t;&t;0xFF
DECL|macro|MSG_MASK
mdefine_line|#define MSG_MASK&t;&t;0xFF00
DECL|macro|RETURN_MASK
mdefine_line|#define RETURN_MASK&t;&t;0xFF0000
multiline_comment|/*&n;**  Inquiry Data format&n;*/
DECL|struct|_SCSIInqData
r_typedef
r_struct
id|_SCSIInqData
(brace
multiline_comment|/* INQ */
DECL|member|DevType
id|UCHAR
id|DevType
suffix:semicolon
multiline_comment|/* Periph Qualifier &amp; Periph Dev Type*/
DECL|member|RMB_TypeMod
id|UCHAR
id|RMB_TypeMod
suffix:semicolon
multiline_comment|/* rem media bit &amp; Dev Type Modifier */
DECL|member|Vers
id|UCHAR
id|Vers
suffix:semicolon
multiline_comment|/* ISO, ECMA, &amp; ANSI versions&t;     */
DECL|member|RDF
id|UCHAR
id|RDF
suffix:semicolon
multiline_comment|/* AEN, TRMIOP, &amp; response data format*/
DECL|member|AddLen
id|UCHAR
id|AddLen
suffix:semicolon
multiline_comment|/* length of additional data&t;     */
DECL|member|Res1
id|UCHAR
id|Res1
suffix:semicolon
multiline_comment|/* reserved&t;&t;&t;     */
DECL|member|Res2
id|UCHAR
id|Res2
suffix:semicolon
multiline_comment|/* reserved&t;&t;&t;     */
DECL|member|Flags
id|UCHAR
id|Flags
suffix:semicolon
multiline_comment|/* RelADr,Wbus32,Wbus16,Sync,etc.    */
DECL|member|VendorID
id|UCHAR
id|VendorID
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Vendor Identification&t;     */
DECL|member|ProductID
id|UCHAR
id|ProductID
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Product Identification&t;     */
DECL|member|ProductRev
id|UCHAR
id|ProductRev
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Product Revision&t;&t;     */
DECL|typedef|SCSI_INQDATA
DECL|typedef|PSCSI_INQDATA
)brace
id|SCSI_INQDATA
comma
op_star
id|PSCSI_INQDATA
suffix:semicolon
multiline_comment|/*  Inquiry byte 0 masks */
DECL|macro|SCSI_DEVTYPE
mdefine_line|#define SCSI_DEVTYPE&t;    0x1F      /* Peripheral Device Type &t;    */
DECL|macro|SCSI_PERIPHQUAL
mdefine_line|#define SCSI_PERIPHQUAL     0xE0      /* Peripheral Qualifier&t;&t;    */
multiline_comment|/*  Inquiry byte 1 mask */
DECL|macro|SCSI_REMOVABLE_MEDIA
mdefine_line|#define SCSI_REMOVABLE_MEDIA  0x80    /* Removable Media bit (1=removable)  */
multiline_comment|/*  Peripheral Device Type definitions */
DECL|macro|SCSI_DASD
mdefine_line|#define SCSI_DASD&t;&t; 0x00&t;   /* Direct-access Device&t;   */
DECL|macro|SCSI_SEQACESS
mdefine_line|#define SCSI_SEQACESS&t;&t; 0x01&t;   /* Sequential-access device&t;   */
DECL|macro|SCSI_PRINTER
mdefine_line|#define SCSI_PRINTER&t;&t; 0x02&t;   /* Printer device&t;&t;   */
DECL|macro|SCSI_PROCESSOR
mdefine_line|#define SCSI_PROCESSOR&t;&t; 0x03&t;   /* Processor device&t;&t;   */
DECL|macro|SCSI_WRITEONCE
mdefine_line|#define SCSI_WRITEONCE&t;&t; 0x04&t;   /* Write-once device &t;   */
DECL|macro|SCSI_CDROM
mdefine_line|#define SCSI_CDROM&t;&t; 0x05&t;   /* CD-ROM device&t;&t;   */
DECL|macro|SCSI_SCANNER
mdefine_line|#define SCSI_SCANNER&t;&t; 0x06&t;   /* Scanner device&t;&t;   */
DECL|macro|SCSI_OPTICAL
mdefine_line|#define SCSI_OPTICAL&t;&t; 0x07&t;   /* Optical memory device&t;   */
DECL|macro|SCSI_MEDCHGR
mdefine_line|#define SCSI_MEDCHGR&t;&t; 0x08&t;   /* Medium changer device&t;   */
DECL|macro|SCSI_COMM
mdefine_line|#define SCSI_COMM&t;&t; 0x09&t;   /* Communications device&t;   */
DECL|macro|SCSI_NODEV
mdefine_line|#define SCSI_NODEV&t;&t; 0x1F&t;   /* Unknown or no device type    */
multiline_comment|/*&n;** Inquiry flag definitions (Inq data byte 7)&n;*/
DECL|macro|SCSI_INQ_RELADR
mdefine_line|#define SCSI_INQ_RELADR       0x80    /* device supports relative addressing*/
DECL|macro|SCSI_INQ_WBUS32
mdefine_line|#define SCSI_INQ_WBUS32       0x40    /* device supports 32 bit data xfers  */
DECL|macro|SCSI_INQ_WBUS16
mdefine_line|#define SCSI_INQ_WBUS16       0x20    /* device supports 16 bit data xfers  */
DECL|macro|SCSI_INQ_SYNC
mdefine_line|#define SCSI_INQ_SYNC&t;      0x10    /* device supports synchronous xfer   */
DECL|macro|SCSI_INQ_LINKED
mdefine_line|#define SCSI_INQ_LINKED       0x08    /* device supports linked commands    */
DECL|macro|SCSI_INQ_CMDQUEUE
mdefine_line|#define SCSI_INQ_CMDQUEUE     0x02    /* device supports command queueing   */
DECL|macro|SCSI_INQ_SFTRE
mdefine_line|#define SCSI_INQ_SFTRE&t;      0x01    /* device supports soft resets */
multiline_comment|/*&n;;==========================================================&n;; EEPROM byte offset&n;;==========================================================&n;*/
DECL|struct|_EEprom
r_typedef
r_struct
id|_EEprom
(brace
DECL|member|EE_MODE1
id|UCHAR
id|EE_MODE1
suffix:semicolon
DECL|member|EE_SPEED
id|UCHAR
id|EE_SPEED
suffix:semicolon
DECL|member|xx1
id|UCHAR
id|xx1
suffix:semicolon
DECL|member|xx2
id|UCHAR
id|xx2
suffix:semicolon
DECL|typedef|EEprom
DECL|typedef|PEEprom
)brace
id|EEprom
comma
op_star
id|PEEprom
suffix:semicolon
DECL|macro|EE_ADAPT_SCSI_ID
mdefine_line|#define EE_ADAPT_SCSI_ID 64
DECL|macro|EE_MODE2
mdefine_line|#define EE_MODE2&t;65
DECL|macro|EE_DELAY
mdefine_line|#define EE_DELAY&t;66
DECL|macro|EE_TAG_CMD_NUM
mdefine_line|#define EE_TAG_CMD_NUM&t;67
multiline_comment|/*; EE_MODE1 bits definition*/
DECL|macro|PARITY_CHK_
mdefine_line|#define PARITY_CHK_&t;BIT0
DECL|macro|SYNC_NEGO_
mdefine_line|#define SYNC_NEGO_&t;BIT1
DECL|macro|EN_DISCONNECT_
mdefine_line|#define EN_DISCONNECT_&t;BIT2
DECL|macro|SEND_START_
mdefine_line|#define SEND_START_&t;BIT3
DECL|macro|TAG_QUEUING_
mdefine_line|#define TAG_QUEUING_&t;BIT4
multiline_comment|/*; EE_MODE2 bits definition*/
DECL|macro|MORE2_DRV
mdefine_line|#define MORE2_DRV&t;BIT0
DECL|macro|GREATER_1G
mdefine_line|#define GREATER_1G&t;BIT1
DECL|macro|RST_SCSI_BUS
mdefine_line|#define RST_SCSI_BUS&t;BIT2
DECL|macro|ACTIVE_NEGATION
mdefine_line|#define ACTIVE_NEGATION BIT3
DECL|macro|NO_SEEK
mdefine_line|#define NO_SEEK &t;BIT4
DECL|macro|LUN_CHECK
mdefine_line|#define LUN_CHECK&t;BIT5
DECL|macro|ENABLE_CE
mdefine_line|#define ENABLE_CE&t;1
DECL|macro|DISABLE_CE
mdefine_line|#define DISABLE_CE&t;0
DECL|macro|EEPROM_READ
mdefine_line|#define EEPROM_READ&t;0x80
multiline_comment|/*&n;;==========================================================&n;;&t;AMD 53C974 Registers bit Definition&n;;==========================================================&n;*/
multiline_comment|/*&n;;====================&n;; SCSI Register&n;;====================&n;*/
multiline_comment|/*; Command Reg.(+0CH) */
DECL|macro|DMA_COMMAND
mdefine_line|#define DMA_COMMAND&t;&t;BIT7
DECL|macro|NOP_CMD
mdefine_line|#define NOP_CMD &t;&t;0
DECL|macro|CLEAR_FIFO_CMD
mdefine_line|#define CLEAR_FIFO_CMD&t;&t;1
DECL|macro|RST_DEVICE_CMD
mdefine_line|#define RST_DEVICE_CMD&t;&t;2
DECL|macro|RST_SCSI_BUS_CMD
mdefine_line|#define RST_SCSI_BUS_CMD&t;3
DECL|macro|INFO_XFER_CMD
mdefine_line|#define INFO_XFER_CMD&t;&t;0x10
DECL|macro|INITIATOR_CMD_CMPLTE
mdefine_line|#define INITIATOR_CMD_CMPLTE&t;0x11
DECL|macro|MSG_ACCEPTED_CMD
mdefine_line|#define MSG_ACCEPTED_CMD&t;0x12
DECL|macro|XFER_PAD_BYTE
mdefine_line|#define XFER_PAD_BYTE&t;&t;0x18
DECL|macro|SET_ATN_CMD
mdefine_line|#define SET_ATN_CMD&t;&t;0x1A
DECL|macro|RESET_ATN_CMD
mdefine_line|#define RESET_ATN_CMD&t;&t;0x1B
DECL|macro|SELECT_W_ATN
mdefine_line|#define SELECT_W_ATN&t;&t;0x42
DECL|macro|SEL_W_ATN_STOP
mdefine_line|#define SEL_W_ATN_STOP&t;&t;0x43
DECL|macro|EN_SEL_RESEL
mdefine_line|#define EN_SEL_RESEL&t;&t;0x44
DECL|macro|SEL_W_ATN2
mdefine_line|#define SEL_W_ATN2&t;&t;0x46
DECL|macro|DATA_XFER_CMD
mdefine_line|#define DATA_XFER_CMD&t;&t;INFO_XFER_CMD
multiline_comment|/*; SCSI Status Reg.(+10H) */
DECL|macro|INTERRUPT
mdefine_line|#define INTERRUPT&t;&t;BIT7
DECL|macro|ILLEGAL_OP_ERR
mdefine_line|#define ILLEGAL_OP_ERR&t;&t;BIT6
DECL|macro|PARITY_ERR
mdefine_line|#define PARITY_ERR&t;&t;BIT5
DECL|macro|COUNT_2_ZERO
mdefine_line|#define COUNT_2_ZERO&t;&t;BIT4
DECL|macro|GROUP_CODE_VALID
mdefine_line|#define GROUP_CODE_VALID&t;BIT3
DECL|macro|SCSI_PHASE_MASK
mdefine_line|#define SCSI_PHASE_MASK &t;(BIT2+BIT1+BIT0)
multiline_comment|/*; Interrupt Status Reg.(+14H) */
DECL|macro|SCSI_RESET
mdefine_line|#define SCSI_RESET&t;&t;BIT7
DECL|macro|INVALID_CMD
mdefine_line|#define INVALID_CMD&t;&t;BIT6
DECL|macro|DISCONNECTED
mdefine_line|#define DISCONNECTED&t;&t;BIT5
DECL|macro|SERVICE_REQUEST
mdefine_line|#define SERVICE_REQUEST &t;BIT4
DECL|macro|SUCCESSFUL_OP
mdefine_line|#define SUCCESSFUL_OP&t;&t;BIT3
DECL|macro|RESELECTED
mdefine_line|#define RESELECTED&t;&t;BIT2
DECL|macro|SEL_ATTENTION
mdefine_line|#define SEL_ATTENTION&t;&t;BIT1
DECL|macro|SELECTED
mdefine_line|#define SELECTED&t;&t;BIT0
multiline_comment|/*; Internal State Reg.(+18H) */
DECL|macro|SYNC_OFFSET_FLAG
mdefine_line|#define SYNC_OFFSET_FLAG&t;BIT3
DECL|macro|INTRN_STATE_MASK
mdefine_line|#define INTRN_STATE_MASK&t;(BIT2+BIT1+BIT0)
multiline_comment|/*; Clock Factor Reg.(+24H) */
DECL|macro|CLK_FREQ_40MHZ
mdefine_line|#define CLK_FREQ_40MHZ&t;&t;0
DECL|macro|CLK_FREQ_35MHZ
mdefine_line|#define CLK_FREQ_35MHZ&t;&t;(BIT2+BIT1+BIT0)
DECL|macro|CLK_FREQ_30MHZ
mdefine_line|#define CLK_FREQ_30MHZ&t;&t;(BIT2+BIT1)
DECL|macro|CLK_FREQ_25MHZ
mdefine_line|#define CLK_FREQ_25MHZ&t;&t;(BIT2+BIT0)
DECL|macro|CLK_FREQ_20MHZ
mdefine_line|#define CLK_FREQ_20MHZ&t;&t;BIT2
DECL|macro|CLK_FREQ_15MHZ
mdefine_line|#define CLK_FREQ_15MHZ&t;&t;(BIT1+BIT0)
DECL|macro|CLK_FREQ_10MHZ
mdefine_line|#define CLK_FREQ_10MHZ&t;&t;BIT1
multiline_comment|/*; Control Reg. 1(+20H) */
DECL|macro|EXTENDED_TIMING
mdefine_line|#define EXTENDED_TIMING &t;BIT7
DECL|macro|DIS_INT_ON_SCSI_RST
mdefine_line|#define DIS_INT_ON_SCSI_RST&t;BIT6
DECL|macro|PARITY_ERR_REPO
mdefine_line|#define PARITY_ERR_REPO &t;BIT4
DECL|macro|SCSI_ID_ON_BUS
mdefine_line|#define SCSI_ID_ON_BUS&t;&t;(BIT2+BIT1+BIT0)
multiline_comment|/*; Control Reg. 2(+2CH) */
DECL|macro|EN_FEATURE
mdefine_line|#define EN_FEATURE&t;&t;BIT6
DECL|macro|EN_SCSI2_CMD
mdefine_line|#define EN_SCSI2_CMD&t;&t;BIT3
multiline_comment|/*; Control Reg. 3(+30H) */
DECL|macro|ID_MSG_CHECK
mdefine_line|#define ID_MSG_CHECK&t;&t;BIT7
DECL|macro|EN_QTAG_MSG
mdefine_line|#define EN_QTAG_MSG&t;&t;BIT6
DECL|macro|EN_GRP2_CMD
mdefine_line|#define EN_GRP2_CMD&t;&t;BIT5
DECL|macro|FAST_SCSI
mdefine_line|#define FAST_SCSI&t;&t;BIT4&t;/* ;10MB/SEC */
DECL|macro|FAST_CLK
mdefine_line|#define FAST_CLK&t;&t;BIT3&t;/* ;25 - 40 MHZ */
multiline_comment|/*; Control Reg. 4(+34H) */
DECL|macro|EATER_12NS
mdefine_line|#define EATER_12NS&t;&t;0
DECL|macro|EATER_25NS
mdefine_line|#define EATER_25NS&t;&t;BIT7
DECL|macro|EATER_35NS
mdefine_line|#define EATER_35NS&t;&t;BIT6
DECL|macro|EATER_0NS
mdefine_line|#define EATER_0NS&t;&t;(BIT7+BIT6)
DECL|macro|NEGATE_REQACKDATA
mdefine_line|#define NEGATE_REQACKDATA&t;BIT2
DECL|macro|NEGATE_REQACK
mdefine_line|#define NEGATE_REQACK&t;&t;BIT3
multiline_comment|/*&n;;====================&n;; DMA Register&n;;====================&n;*/
multiline_comment|/*; DMA Command Reg.(+40H) */
DECL|macro|READ_DIRECTION
mdefine_line|#define READ_DIRECTION&t;&t;BIT7
DECL|macro|WRITE_DIRECTION
mdefine_line|#define WRITE_DIRECTION &t;0
DECL|macro|EN_DMA_INT
mdefine_line|#define EN_DMA_INT&t;&t;BIT6
DECL|macro|MAP_TO_MDL
mdefine_line|#define MAP_TO_MDL&t;&t;BIT5
DECL|macro|DIAGNOSTIC
mdefine_line|#define DIAGNOSTIC&t;&t;BIT4
DECL|macro|DMA_IDLE_CMD
mdefine_line|#define DMA_IDLE_CMD&t;&t;0
DECL|macro|DMA_BLAST_CMD
mdefine_line|#define DMA_BLAST_CMD&t;&t;BIT0
DECL|macro|DMA_ABORT_CMD
mdefine_line|#define DMA_ABORT_CMD&t;&t;BIT1
DECL|macro|DMA_START_CMD
mdefine_line|#define DMA_START_CMD&t;&t;(BIT1+BIT0)
multiline_comment|/*; DMA Status Reg.(+54H) */
DECL|macro|PCI_MS_ABORT
mdefine_line|#define PCI_MS_ABORT&t;&t;BIT6
DECL|macro|BLAST_COMPLETE
mdefine_line|#define BLAST_COMPLETE&t;&t;BIT5
DECL|macro|SCSI_INTERRUPT
mdefine_line|#define SCSI_INTERRUPT&t;&t;BIT4
DECL|macro|DMA_XFER_DONE
mdefine_line|#define DMA_XFER_DONE&t;&t;BIT3
DECL|macro|DMA_XFER_ABORT
mdefine_line|#define DMA_XFER_ABORT&t;&t;BIT2
DECL|macro|DMA_XFER_ERROR
mdefine_line|#define DMA_XFER_ERROR&t;&t;BIT1
DECL|macro|POWER_DOWN
mdefine_line|#define POWER_DOWN&t;&t;BIT0
multiline_comment|/*&n;; DMA SCSI Bus and Ctrl.(+70H)&n;;EN_INT_ON_PCI_ABORT&n;*/
multiline_comment|/*&n;;==========================================================&n;; SCSI Chip register address offset&n;;==========================================================&n;*/
DECL|macro|CtcReg_Low
mdefine_line|#define CtcReg_Low&t;0x00
DECL|macro|CtcReg_Mid
mdefine_line|#define CtcReg_Mid&t;0x04
DECL|macro|ScsiFifo
mdefine_line|#define ScsiFifo&t;0x08
DECL|macro|ScsiCmd
mdefine_line|#define ScsiCmd &t;0x0C
DECL|macro|Scsi_Status
mdefine_line|#define Scsi_Status&t;0x10
DECL|macro|INT_Status
mdefine_line|#define INT_Status&t;0x14
DECL|macro|Sync_Period
mdefine_line|#define Sync_Period&t;0x18
DECL|macro|Sync_Offset
mdefine_line|#define Sync_Offset&t;0x1C
DECL|macro|CtrlReg1
mdefine_line|#define CtrlReg1&t;0x20
DECL|macro|Clk_Factor
mdefine_line|#define Clk_Factor&t;0x24
DECL|macro|CtrlReg2
mdefine_line|#define CtrlReg2&t;0x2C
DECL|macro|CtrlReg3
mdefine_line|#define CtrlReg3&t;0x30
DECL|macro|CtrlReg4
mdefine_line|#define CtrlReg4&t;0x34
DECL|macro|CtcReg_High
mdefine_line|#define CtcReg_High&t;0x38
DECL|macro|DMA_Cmd
mdefine_line|#define DMA_Cmd &t;0x40
DECL|macro|DMA_XferCnt
mdefine_line|#define DMA_XferCnt&t;0x44
DECL|macro|DMA_XferAddr
mdefine_line|#define DMA_XferAddr&t;0x48
DECL|macro|DMA_Wk_ByteCntr
mdefine_line|#define DMA_Wk_ByteCntr 0x4C
DECL|macro|DMA_Wk_AddrCntr
mdefine_line|#define DMA_Wk_AddrCntr 0x50
DECL|macro|DMA_Status
mdefine_line|#define DMA_Status&t;0x54
DECL|macro|DMA_MDL_Addr
mdefine_line|#define DMA_MDL_Addr&t;0x58
DECL|macro|DMA_Wk_MDL_Cntr
mdefine_line|#define DMA_Wk_MDL_Cntr 0x5C
DECL|macro|DMA_ScsiBusCtrl
mdefine_line|#define DMA_ScsiBusCtrl 0x70
DECL|macro|StcReg_Low
mdefine_line|#define StcReg_Low&t;CtcReg_Low
DECL|macro|StcReg_Mid
mdefine_line|#define StcReg_Mid&t;CtcReg_Mid
DECL|macro|Scsi_Dest_ID
mdefine_line|#define Scsi_Dest_ID&t;Scsi_Status
DECL|macro|Scsi_TimeOut
mdefine_line|#define Scsi_TimeOut&t;INT_Status
DECL|macro|Intern_State
mdefine_line|#define Intern_State&t;Sync_Period
DECL|macro|Current_Fifo
mdefine_line|#define Current_Fifo&t;Sync_Offset
DECL|macro|StcReg_High
mdefine_line|#define StcReg_High&t;CtcReg_High
DECL|macro|am_target
mdefine_line|#define am_target&t;Scsi_Status
DECL|macro|am_timeout
mdefine_line|#define am_timeout&t;INT_Status
DECL|macro|am_seq_step
mdefine_line|#define am_seq_step&t;Sync_Period
DECL|macro|am_fifo_count
mdefine_line|#define am_fifo_count&t;Sync_Offset
DECL|macro|DC390_read8
mdefine_line|#define DC390_read8(address)&t;&t;&t;       &bslash;&n;&t;inb(DC390_ioport + (address)))
DECL|macro|DC390_read16
mdefine_line|#define DC390_read16(address)&t;&t;&t;       &bslash;&n;&t;inw(DC390_ioport + (address)))
DECL|macro|DC390_read32
mdefine_line|#define DC390_read32(address)&t;&t;&t;       &bslash;&n;&t;inl(DC390_ioport + (address)))
DECL|macro|DC390_write8
mdefine_line|#define DC390_write8(address,value)&t;&t;       &bslash;&n;&t;outb((value), DC390_ioport + (address)))
DECL|macro|DC390_write16
mdefine_line|#define DC390_write16(address,value)&t;&t;       &bslash;&n;&t;outw((value), DC390_ioport + (address)))
DECL|macro|DC390_write32
mdefine_line|#define DC390_write32(address,value)&t;&t;       &bslash;&n;&t;outl((value), DC390_ioport + (address)))
multiline_comment|/* Configuration method #1 */
DECL|macro|PCI_CFG1_ADDRESS_REG
mdefine_line|#define PCI_CFG1_ADDRESS_REG&t;&t;0xcf8
DECL|macro|PCI_CFG1_DATA_REG
mdefine_line|#define PCI_CFG1_DATA_REG&t;&t;0xcfc
DECL|macro|PCI_CFG1_ENABLE
mdefine_line|#define PCI_CFG1_ENABLE &t;&t;0x80000000
DECL|macro|PCI_CFG1_TUPPLE
mdefine_line|#define PCI_CFG1_TUPPLE(bus, device, function, register)&t;&t;&bslash;&n;&t;(PCI_CFG1_ENABLE | (((bus) &lt;&lt; 16) &amp; 0xff0000) | &t;&t;&bslash;&n;&t;(((device) &lt;&lt; 11) &amp; 0xf800) | (((function) &lt;&lt; 8) &amp; 0x700)|&t;&bslash;&n;&t;(((register) &lt;&lt; 2) &amp; 0xfc))
multiline_comment|/* Configuration method #2 */
DECL|macro|PCI_CFG2_ENABLE_REG
mdefine_line|#define PCI_CFG2_ENABLE_REG&t;&t;0xcf8
DECL|macro|PCI_CFG2_FORWARD_REG
mdefine_line|#define PCI_CFG2_FORWARD_REG&t;&t;0xcfa
DECL|macro|PCI_CFG2_ENABLE
mdefine_line|#define PCI_CFG2_ENABLE &t;&t;0x0f0
DECL|macro|PCI_CFG2_TUPPLE
mdefine_line|#define PCI_CFG2_TUPPLE(function)&t;&t;&t;&t;&t;&bslash;&n;&t;(PCI_CFG2_ENABLE | (((function) &lt;&lt; 1) &amp; 0xe))
macro_line|#endif /* TMSCSIM_H */
eof