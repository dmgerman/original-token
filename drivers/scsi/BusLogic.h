multiline_comment|/*&n;&n;  Linux Driver for BusLogic MultiMaster SCSI Host Adapters&n;&n;  Copyright 1995 by Leonard N. Zubkoff &lt;lnz@dandelion.com&gt;&n;&n;  This program is free software; you may redistribute and/or modify it under&n;  the terms of the GNU General Public License Version 2 as published by the&n;  Free Software Foundation, provided that none of the source code or runtime&n;  copyright notices are removed or modified.&n;&n;  This program is distributed in the hope that it will be useful, but&n;  WITHOUT ANY WARRANTY, without even the implied warranty of MERCHANTABILITY&n;  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License&n;  for complete details.&n;&n;  The author respectfully requests that any modifications to this software be&n;  sent directly to him for evaluation and testing.&n;&n;  Special thanks to Wayne Yen and Alex Win of BusLogic, whose advice has been&n;  invaluable, to David Gentzel, for writing the original Linux BusLogic driver,&n;  and to Paul Gortmaker, for being such a dedicated test site.&n;&n;*/
multiline_comment|/*&n;  Define types for some of the structures that interface with the rest&n;  of the Linux Kernel and SCSI Subsystem.&n;*/
DECL|typedef|Registers_T
r_typedef
r_struct
id|pt_regs
id|Registers_T
suffix:semicolon
DECL|typedef|SCSI_Host_Template_T
r_typedef
id|Scsi_Host_Template
id|SCSI_Host_Template_T
suffix:semicolon
DECL|typedef|SCSI_Host_T
r_typedef
r_struct
id|Scsi_Host
id|SCSI_Host_T
suffix:semicolon
DECL|typedef|SCSI_Device_T
r_typedef
r_struct
id|scsi_device
id|SCSI_Device_T
suffix:semicolon
DECL|typedef|SCSI_Disk_T
r_typedef
r_struct
id|scsi_disk
id|SCSI_Disk_T
suffix:semicolon
DECL|typedef|SCSI_Command_T
r_typedef
r_struct
id|scsi_cmnd
id|SCSI_Command_T
suffix:semicolon
DECL|typedef|SCSI_ScatterList_T
r_typedef
r_struct
id|scatterlist
id|SCSI_ScatterList_T
suffix:semicolon
DECL|typedef|KernelDevice_T
r_typedef
id|kdev_t
id|KernelDevice_T
suffix:semicolon
multiline_comment|/*&n;  Define prototypes for the BusLogic Driver Interface Functions.&n;*/
r_const
r_char
op_star
id|BusLogic_DriverInfo
c_func
(paren
id|SCSI_Host_T
op_star
)paren
suffix:semicolon
r_int
id|BusLogic_DetectHostAdapter
c_func
(paren
id|SCSI_Host_Template_T
op_star
)paren
suffix:semicolon
r_int
id|BusLogic_ReleaseHostAdapter
c_func
(paren
id|SCSI_Host_T
op_star
)paren
suffix:semicolon
r_int
id|BusLogic_QueueCommand
c_func
(paren
id|SCSI_Command_T
op_star
comma
r_void
(paren
op_star
id|CompletionRoutine
)paren
(paren
id|SCSI_Command_T
op_star
)paren
)paren
suffix:semicolon
r_int
id|BusLogic_AbortCommand
c_func
(paren
id|SCSI_Command_T
op_star
)paren
suffix:semicolon
r_int
id|BusLogic_ResetCommand
c_func
(paren
id|SCSI_Command_T
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|BusLogic_BIOSDiskParameters
c_func
(paren
id|SCSI_Disk_T
op_star
comma
id|KernelDevice_T
comma
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;  Define the BusLogic SCSI Host Template structure.&n;*/
DECL|macro|BUSLOGIC
mdefine_line|#define BUSLOGIC&t;&t;&t;&t;&t;&t;&t; &bslash;&n;  { NULL,&t;&t;&t;&t;/* Next&t;&t;&t;     */  &bslash;&n;    NULL,&t;&t;&t;&t;/* Usage Count Pointer&t;     */  &bslash;&n;    NULL,&t;&t;&t;&t;/* /proc Directory Entry     */&t; &bslash;&n;    NULL,&t;&t;&t;&t;/* /proc Info Function&t;     */&t; &bslash;&n;    &quot;BusLogic&quot;,&t;&t;&t;&t;/* Driver Name&t;&t;     */  &bslash;&n;    BusLogic_DetectHostAdapter,&t;&t;/* Detect Host Adapter&t;     */  &bslash;&n;    BusLogic_ReleaseHostAdapter,&t;/* Release Host Adapter&t;     */  &bslash;&n;    BusLogic_DriverInfo,&t;&t;/* Driver Info Function&t;     */  &bslash;&n;    NULL,&t;&t;&t;&t;/* Command Function&t;     */  &bslash;&n;    BusLogic_QueueCommand,&t;&t;/* Queue Command Function    */  &bslash;&n;    BusLogic_AbortCommand,&t;&t;/* Abort Command Function    */  &bslash;&n;    BusLogic_ResetCommand,&t;&t;/* Reset Command Function    */  &bslash;&n;    NULL,&t;&t;&t;&t;/* Slave Attach Function     */  &bslash;&n;    BusLogic_BIOSDiskParameters,&t;/* Disk BIOS Parameters&t;     */  &bslash;&n;    0,&t;&t;&t;&t;&t;/* Can Queue&t;&t;     */  &bslash;&n;    0,&t;&t;&t;&t;&t;/* This ID&t;&t;     */  &bslash;&n;    0,&t;&t;&t;&t;&t;/* Scatter/Gather Table Size */  &bslash;&n;    0,&t;&t;&t;&t;&t;/* SCSI Commands per LUN     */  &bslash;&n;    0,&t;&t;&t;&t;&t;/* Present&t;&t;     */  &bslash;&n;    1,&t;&t;&t;&t;&t;/* Default Unchecked ISA DMA */  &bslash;&n;    ENABLE_CLUSTERING }&t;&t;&t;/* Enable Clustering&t;     */
multiline_comment|/*&n;  BusLogic_DriverVersion protects the private portion of this file.&n;*/
macro_line|#ifdef BusLogic_DriverVersion
multiline_comment|/*&n;  Define the maximum number of BusLogic Host Adapters that are supported.&n;*/
DECL|macro|BusLogic_MaxHostAdapters
mdefine_line|#define BusLogic_MaxHostAdapters&t;&t;10
multiline_comment|/*&n;  Define the maximum number of I/O Addresses that may be probed.&n;*/
DECL|macro|BusLogic_IO_MaxProbeAddresses
mdefine_line|#define BusLogic_IO_MaxProbeAddresses&t;&t;16
multiline_comment|/*&n;  Define the maximum number of Target Devices supported by this driver.&n;*/
DECL|macro|BusLogic_MaxTargetDevices
mdefine_line|#define BusLogic_MaxTargetDevices&t;&t;16
multiline_comment|/*&n;  Define the maximum number of Scatter/Gather Segments used by this driver.&n;  For optimal performance, it is important that this limit be at least as&n;  large as the maximum single request generated by the I/O Subsystem.&n;*/
DECL|macro|BusLogic_ScatterGatherLimit
mdefine_line|#define BusLogic_ScatterGatherLimit&t;&t;128
multiline_comment|/*&n;  Define the maximum and default Queue Depth to allow for Target Devices&n;  depending on whether or not they support Tagged Queuing and whether or not&n;  ISA Bounce Buffers are required.&n;*/
DECL|macro|BusLogic_MaxTaggedQueueDepth
mdefine_line|#define BusLogic_MaxTaggedQueueDepth&t;&t;31
DECL|macro|BusLogic_TaggedQueueDepth_BB
mdefine_line|#define BusLogic_TaggedQueueDepth_BB&t;&t;2
DECL|macro|BusLogic_UntaggedQueueDepth
mdefine_line|#define BusLogic_UntaggedQueueDepth&t;&t;3
multiline_comment|/*&n;  Define the default amount of time in seconds to wait between a Host Adapter&n;  Hard Reset which initiates a SCSI Bus Reset and issuing any SCSI commands.&n;  Some SCSI devices get confused if they receive SCSI commands too soon after&n;  a SCSI Bus Reset.&n;*/
DECL|macro|BusLogic_DefaultBusSettleTime
mdefine_line|#define BusLogic_DefaultBusSettleTime&t;&t;2
multiline_comment|/*&n;  Define the possible Local Options.&n;*/
DECL|macro|BusLogic_InhibitTargetInquiry
mdefine_line|#define BusLogic_InhibitTargetInquiry&t;&t;1
multiline_comment|/*&n;  Define the possible Global Options.&n;*/
DECL|macro|BusLogic_TraceProbe
mdefine_line|#define BusLogic_TraceProbe&t;&t;&t;1
DECL|macro|BusLogic_TraceHardReset
mdefine_line|#define BusLogic_TraceHardReset&t;&t;&t;2
DECL|macro|BusLogic_TraceConfiguration
mdefine_line|#define BusLogic_TraceConfiguration&t;&t;4
DECL|macro|BusLogic_TraceErrors
mdefine_line|#define BusLogic_TraceErrors&t;&t;&t;8
DECL|macro|BusLogic_TraceQueueDepths
mdefine_line|#define BusLogic_TraceQueueDepths&t;&t;16
multiline_comment|/*&n;  Define the possible Error Recovery Strategy Options.&n;*/
DECL|macro|BusLogic_ErrorRecovery_Default
mdefine_line|#define BusLogic_ErrorRecovery_Default&t;&t;0
DECL|macro|BusLogic_ErrorRecovery_HardReset
mdefine_line|#define BusLogic_ErrorRecovery_HardReset&t;1
DECL|macro|BusLogic_ErrorRecovery_BusDeviceReset
mdefine_line|#define BusLogic_ErrorRecovery_BusDeviceReset&t;2
DECL|macro|BusLogic_ErrorRecovery_None
mdefine_line|#define BusLogic_ErrorRecovery_None&t;&t;3
r_static
r_char
DECL|variable|BusLogic_ErrorRecoveryStrategyNames
op_star
id|BusLogic_ErrorRecoveryStrategyNames
(braket
)braket
op_assign
(brace
l_string|&quot;Default&quot;
comma
l_string|&quot;Hard Reset&quot;
comma
l_string|&quot;Bus Device Reset&quot;
comma
l_string|&quot;None&quot;
)brace
comma
DECL|variable|BusLogic_ErrorRecoveryStrategyLetters
op_star
id|BusLogic_ErrorRecoveryStrategyLetters
(braket
)braket
op_assign
(brace
l_string|&quot;D&quot;
comma
l_string|&quot;H&quot;
comma
l_string|&quot;B&quot;
comma
l_string|&quot;N&quot;
)brace
suffix:semicolon
multiline_comment|/*&n;  Define a boolean data type.&n;*/
DECL|macro|false
mdefine_line|#define false 0
DECL|macro|true
mdefine_line|#define true  1
DECL|typedef|boolean
r_typedef
r_int
r_char
id|boolean
suffix:semicolon
multiline_comment|/*&n;  Define the BusLogic SCSI Host Adapter I/O Register Offsets.&n;*/
DECL|macro|BusLogic_IO_PortCount
mdefine_line|#define BusLogic_IO_PortCount&t;&t;&t;4&t;/* I/O Registers */
DECL|macro|BusLogic_ControlRegister
mdefine_line|#define BusLogic_ControlRegister&t;&t;0&t;/* WO register */
DECL|macro|BusLogic_StatusRegister
mdefine_line|#define BusLogic_StatusRegister&t;&t;&t;0&t;/* RO register */
DECL|macro|BusLogic_CommandParameterRegister
mdefine_line|#define BusLogic_CommandParameterRegister&t;1&t;/* WO register */
DECL|macro|BusLogic_DataInRegister
mdefine_line|#define BusLogic_DataInRegister&t;&t;&t;1&t;/* RO register */
DECL|macro|BusLogic_InterruptRegister
mdefine_line|#define BusLogic_InterruptRegister&t;&t;2&t;/* RO register */
DECL|macro|BusLogic_GeometryRegister
mdefine_line|#define BusLogic_GeometryRegister&t;&t;3&t;/* RO, undocumented */
multiline_comment|/*&n;  Define the bits in the write-only Control Register.&n;*/
DECL|macro|BusLogic_ReservedCR
mdefine_line|#define BusLogic_ReservedCR&t;&t;&t;0x0F
DECL|macro|BusLogic_SCSIBusReset
mdefine_line|#define BusLogic_SCSIBusReset&t;&t;&t;0x10
DECL|macro|BusLogic_InterruptReset
mdefine_line|#define BusLogic_InterruptReset&t;&t;&t;0x20
DECL|macro|BusLogic_SoftReset
mdefine_line|#define BusLogic_SoftReset&t;&t;&t;0x40
DECL|macro|BusLogic_HardReset
mdefine_line|#define BusLogic_HardReset&t;&t;&t;0x80
multiline_comment|/*&n;  Define the bits in the read-only Status Register.&n;*/
DECL|macro|BusLogic_CommandInvalid
mdefine_line|#define BusLogic_CommandInvalid&t;&t;&t;0x01
DECL|macro|BusLogic_ReservedSR
mdefine_line|#define BusLogic_ReservedSR&t;&t;&t;0x02
DECL|macro|BusLogic_DataInRegisterReady
mdefine_line|#define BusLogic_DataInRegisterReady&t;&t;0x04
DECL|macro|BusLogic_CommandParameterRegisterBusy
mdefine_line|#define BusLogic_CommandParameterRegisterBusy&t;0x08
DECL|macro|BusLogic_HostAdapterReady
mdefine_line|#define BusLogic_HostAdapterReady&t;&t;0x10
DECL|macro|BusLogic_InitializationRequired
mdefine_line|#define BusLogic_InitializationRequired&t;&t;0x20
DECL|macro|BusLogic_DiagnosticFailure
mdefine_line|#define BusLogic_DiagnosticFailure&t;&t;0x40
DECL|macro|BusLogic_DiagnosticActive
mdefine_line|#define BusLogic_DiagnosticActive&t;&t;0x80
multiline_comment|/*&n;  Define the bits in the read-only Interrupt Register.&n;*/
DECL|macro|BusLogic_IncomingMailboxLoaded
mdefine_line|#define BusLogic_IncomingMailboxLoaded&t;&t;0x01
DECL|macro|BusLogic_OutgoingMailboxAvailable
mdefine_line|#define BusLogic_OutgoingMailboxAvailable&t;0x02
DECL|macro|BusLogic_CommandComplete
mdefine_line|#define BusLogic_CommandComplete&t;&t;0x04
DECL|macro|BusLogic_SCSIResetState
mdefine_line|#define BusLogic_SCSIResetState&t;&t;&t;0x08
DECL|macro|BusLogic_ReservedIR
mdefine_line|#define BusLogic_ReservedIR&t;&t;&t;0x70
DECL|macro|BusLogic_InterruptValid
mdefine_line|#define BusLogic_InterruptValid&t;&t;&t;0x80
multiline_comment|/*&n;  Define the bits in the undocumented read-only Geometry Register.&n;*/
DECL|macro|BusLogic_Drive0Geometry
mdefine_line|#define BusLogic_Drive0Geometry&t;&t;&t;0x03
DECL|macro|BusLogic_Drive1Geometry
mdefine_line|#define BusLogic_Drive1Geometry&t;&t;&t;0x0C
DECL|macro|BusLogic_ReservedGR
mdefine_line|#define BusLogic_ReservedGR&t;&t;&t;0x70
DECL|macro|BusLogic_ExtendedTranslationEnabled
mdefine_line|#define BusLogic_ExtendedTranslationEnabled&t;0x80
multiline_comment|/*&n;  Define the BusLogic SCSI Host Adapter Command Register Operation Codes.&n;*/
r_typedef
r_enum
(brace
DECL|enumerator|BusLogic_TestCommandCompleteInterrupt
id|BusLogic_TestCommandCompleteInterrupt
op_assign
l_int|0x00
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_InitializeMailbox
id|BusLogic_InitializeMailbox
op_assign
l_int|0x01
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_ExecuteMailboxCommand
id|BusLogic_ExecuteMailboxCommand
op_assign
l_int|0x02
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_ExecuteBIOSCommand
id|BusLogic_ExecuteBIOSCommand
op_assign
l_int|0x03
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_InquireBoardID
id|BusLogic_InquireBoardID
op_assign
l_int|0x04
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_EnableOutgoingMailboxAvailableInt
id|BusLogic_EnableOutgoingMailboxAvailableInt
op_assign
l_int|0x05
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_SetSCSISelectionTimeout
id|BusLogic_SetSCSISelectionTimeout
op_assign
l_int|0x06
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_SetPreemptTimeOnBus
id|BusLogic_SetPreemptTimeOnBus
op_assign
l_int|0x07
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_SetTimeOffBus
id|BusLogic_SetTimeOffBus
op_assign
l_int|0x08
comma
multiline_comment|/* ISA Bus only */
DECL|enumerator|BusLogic_SetBusTransferRate
id|BusLogic_SetBusTransferRate
op_assign
l_int|0x09
comma
multiline_comment|/* ISA Bus only */
DECL|enumerator|BusLogic_InquireInstalledDevicesID0to7
id|BusLogic_InquireInstalledDevicesID0to7
op_assign
l_int|0x0A
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_InquireConfiguration
id|BusLogic_InquireConfiguration
op_assign
l_int|0x0B
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_SetTargetMode
id|BusLogic_SetTargetMode
op_assign
l_int|0x0C
comma
multiline_comment|/* now undocumented */
DECL|enumerator|BusLogic_InquireSetupInformation
id|BusLogic_InquireSetupInformation
op_assign
l_int|0x0D
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_WriteAdapterLocalRAM
id|BusLogic_WriteAdapterLocalRAM
op_assign
l_int|0x1A
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_ReadAdapterLocalRAM
id|BusLogic_ReadAdapterLocalRAM
op_assign
l_int|0x1B
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_WriteBusMasterChipFIFO
id|BusLogic_WriteBusMasterChipFIFO
op_assign
l_int|0x1C
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_ReadBusMasterChipFIFO
id|BusLogic_ReadBusMasterChipFIFO
op_assign
l_int|0x1D
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_EchoCommandData
id|BusLogic_EchoCommandData
op_assign
l_int|0x1F
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_HostAdapterDiagnostic
id|BusLogic_HostAdapterDiagnostic
op_assign
l_int|0x20
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_SetAdapterOptions
id|BusLogic_SetAdapterOptions
op_assign
l_int|0x21
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_InquireInstalledDevicesID8to15
id|BusLogic_InquireInstalledDevicesID8to15
op_assign
l_int|0x23
comma
multiline_comment|/* Wide only */
DECL|enumerator|BusLogic_InquireDevices
id|BusLogic_InquireDevices
op_assign
l_int|0x24
comma
multiline_comment|/* &quot;W&quot; and &quot;C&quot; only */
DECL|enumerator|BusLogic_InitializeExtendedMailbox
id|BusLogic_InitializeExtendedMailbox
op_assign
l_int|0x81
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_InquireFirmwareVersion3rdDigit
id|BusLogic_InquireFirmwareVersion3rdDigit
op_assign
l_int|0x84
comma
multiline_comment|/* undocumented */
DECL|enumerator|BusLogic_InquireFirmwareVersionLetter
id|BusLogic_InquireFirmwareVersionLetter
op_assign
l_int|0x85
comma
multiline_comment|/* undocumented */
DECL|enumerator|BusLogic_InquireGenericIOPortInformation
id|BusLogic_InquireGenericIOPortInformation
op_assign
l_int|0x86
comma
multiline_comment|/* PCI only */
DECL|enumerator|BusLogic_InquireBoardModelNumber
id|BusLogic_InquireBoardModelNumber
op_assign
l_int|0x8B
comma
multiline_comment|/* undocumented */
DECL|enumerator|BusLogic_InquireSynchronousPeriod
id|BusLogic_InquireSynchronousPeriod
op_assign
l_int|0x8C
comma
multiline_comment|/* undocumented */
DECL|enumerator|BusLogic_InquireExtendedSetupInformation
id|BusLogic_InquireExtendedSetupInformation
op_assign
l_int|0x8D
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_EnableStrictRoundRobinMode
id|BusLogic_EnableStrictRoundRobinMode
op_assign
l_int|0x8F
comma
multiline_comment|/* documented */
DECL|enumerator|BusLogic_FetchHostAdapterLocalRAM
id|BusLogic_FetchHostAdapterLocalRAM
op_assign
l_int|0x91
comma
multiline_comment|/* undocumented */
DECL|enumerator|BusLogic_ModifyIOAddress
id|BusLogic_ModifyIOAddress
op_assign
l_int|0x95
comma
multiline_comment|/* PCI only */
DECL|enumerator|BusLogic_EnableWideModeCCB
id|BusLogic_EnableWideModeCCB
op_assign
l_int|0x96
multiline_comment|/* Wide only */
)brace
DECL|typedef|BusLogic_OperationCode_T
id|BusLogic_OperationCode_T
suffix:semicolon
multiline_comment|/*&n;  Define the Inquire Board ID reply structure.&n;*/
DECL|struct|BusLogic_BoardID
r_typedef
r_struct
id|BusLogic_BoardID
(brace
DECL|member|BoardType
r_int
r_char
id|BoardType
suffix:semicolon
multiline_comment|/* Byte 0 */
DECL|member|CustomFeatures
r_int
r_char
id|CustomFeatures
suffix:semicolon
multiline_comment|/* Byte 1 */
DECL|member|FirmwareVersion1stDigit
r_int
r_char
id|FirmwareVersion1stDigit
suffix:semicolon
multiline_comment|/* Byte 2 */
DECL|member|FirmwareVersion2ndDigit
r_int
r_char
id|FirmwareVersion2ndDigit
suffix:semicolon
multiline_comment|/* Byte 3 */
)brace
DECL|typedef|BusLogic_BoardID_T
id|BusLogic_BoardID_T
suffix:semicolon
multiline_comment|/*&n;  Define the Inquire Installed Devices ID 0 to 7 and Inquire Installed&n;  Devices ID 8 to 15 reply type.  For each Target Device, a byte is returned&n;  where bit 0 set indicates that Logical Unit 0 exists, bit 1 set indicates&n;  that Logical Unit 1 exists, and so on.&n;*/
DECL|typedef|BusLogic_InstalledDevices8_T
r_typedef
r_int
r_char
id|BusLogic_InstalledDevices8_T
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/*&n;  Define the Inquire Devices reply type.  Inquire Devices only tests Logical&n;  Unit 0 of each Target Device unlike Inquire Installed Devices which tests&n;  Logical Units 0 - 7.  Two bytes are returned, where bit 0 set indicates&n;  that Target Device 0 exists, and so on.&n;*/
DECL|typedef|BusLogic_InstalledDevices_T
r_typedef
r_int
r_int
id|BusLogic_InstalledDevices_T
suffix:semicolon
multiline_comment|/*&n;  Define the Inquire Configuration reply structure.&n;*/
DECL|struct|BusLogic_Configuration
r_typedef
r_struct
id|BusLogic_Configuration
(brace
r_int
r_char
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* Byte 0 Bits 0-4 */
DECL|member|DMA_Channel5
id|boolean
id|DMA_Channel5
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 0 Bit 5 */
DECL|member|DMA_Channel6
id|boolean
id|DMA_Channel6
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 0 Bit 6 */
DECL|member|DMA_Channel7
id|boolean
id|DMA_Channel7
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 0 Bit 7 */
DECL|member|IRQ_Channel9
id|boolean
id|IRQ_Channel9
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 1 Bit 0 */
DECL|member|IRQ_Channel10
id|boolean
id|IRQ_Channel10
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 1 Bit 1 */
DECL|member|IRQ_Channel11
id|boolean
id|IRQ_Channel11
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 1 Bit 2 */
DECL|member|IRQ_Channel12
id|boolean
id|IRQ_Channel12
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 1 Bit 3 */
r_int
r_char
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 1 Bit 4 */
DECL|member|IRQ_Channel14
id|boolean
id|IRQ_Channel14
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 1 Bit 5 */
DECL|member|IRQ_Channel15
id|boolean
id|IRQ_Channel15
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 1 Bit 6 */
r_int
r_char
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 1 Bit 7 */
DECL|member|HostAdapterID
r_int
r_char
id|HostAdapterID
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Byte 2 Bits 0-3 */
r_int
r_char
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Byte 2 Bits 4-7 */
)brace
DECL|typedef|BusLogic_Configuration_T
id|BusLogic_Configuration_T
suffix:semicolon
multiline_comment|/*&n;  Define the Inquire Setup Information reply structure.&n;*/
DECL|struct|BusLogic_SynchronousValue
r_typedef
r_struct
id|BusLogic_SynchronousValue
(brace
DECL|member|Offset
r_int
r_char
id|Offset
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Bits 0-3 */
DECL|member|TransferPeriod
r_int
r_char
id|TransferPeriod
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Bits 4-6 */
DECL|member|Synchronous
id|boolean
id|Synchronous
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Bit 7 */
)brace
DECL|typedef|BusLogic_SynchronousValue_T
id|BusLogic_SynchronousValue_T
suffix:semicolon
r_typedef
id|BusLogic_SynchronousValue_T
DECL|typedef|BusLogic_SynchronousValues8_T
id|BusLogic_SynchronousValues8_T
(braket
l_int|8
)braket
suffix:semicolon
r_typedef
id|BusLogic_SynchronousValue_T
DECL|typedef|BusLogic_SynchronousValues_T
id|BusLogic_SynchronousValues_T
(braket
id|BusLogic_MaxTargetDevices
)braket
suffix:semicolon
DECL|struct|BusLogic_SetupInformation
r_typedef
r_struct
id|BusLogic_SetupInformation
(brace
DECL|member|SynchronousInitiationEnabled
id|boolean
id|SynchronousInitiationEnabled
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 0 Bit 0 */
DECL|member|ParityCheckEnabled
id|boolean
id|ParityCheckEnabled
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 0 Bit 1 */
r_int
r_char
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Byte 0 Bits 2-7 */
DECL|member|BusTransferRate
r_int
r_char
id|BusTransferRate
suffix:semicolon
multiline_comment|/* Byte 1 */
DECL|member|PreemptTimeOnBus
r_int
r_char
id|PreemptTimeOnBus
suffix:semicolon
multiline_comment|/* Byte 2 */
DECL|member|TimeOffBus
r_int
r_char
id|TimeOffBus
suffix:semicolon
multiline_comment|/* Byte 3 */
DECL|member|MailboxCount
r_int
r_char
id|MailboxCount
suffix:semicolon
multiline_comment|/* Byte 4 */
DECL|member|MailboxAddress
r_int
r_char
id|MailboxAddress
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Bytes 5-7 */
DECL|member|SynchronousValuesID0to7
id|BusLogic_SynchronousValues8_T
id|SynchronousValuesID0to7
suffix:semicolon
multiline_comment|/* Bytes 8-15 */
DECL|member|DisconnectPermittedID0to7
r_int
r_char
id|DisconnectPermittedID0to7
suffix:semicolon
multiline_comment|/* Byte 16 */
DECL|member|Signature
r_int
r_char
id|Signature
suffix:semicolon
multiline_comment|/* Byte 17 */
DECL|member|CharacterD
r_int
r_char
id|CharacterD
suffix:semicolon
multiline_comment|/* Byte 18 */
DECL|member|BusLetter
r_int
r_char
id|BusLetter
suffix:semicolon
multiline_comment|/* Byte 19 */
r_int
r_char
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Byte 20 */
r_int
r_char
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Byte 21 */
DECL|member|SynchronousValuesID8to15
id|BusLogic_SynchronousValues8_T
id|SynchronousValuesID8to15
suffix:semicolon
multiline_comment|/* Bytes 22-29 */
DECL|member|DisconnectPermittedID8to15
r_int
r_char
id|DisconnectPermittedID8to15
suffix:semicolon
multiline_comment|/* Byte 30 */
)brace
DECL|typedef|BusLogic_SetupInformation_T
id|BusLogic_SetupInformation_T
suffix:semicolon
multiline_comment|/*&n;  Define the Initialize Extended Mailbox request structure.&n;*/
DECL|struct|BusLogic_ExtendedMailboxRequest
r_typedef
r_struct
id|BusLogic_ExtendedMailboxRequest
(brace
DECL|member|MailboxCount
r_int
r_char
id|MailboxCount
suffix:semicolon
multiline_comment|/* Byte 0 */
DECL|member|BaseMailboxAddress
r_void
op_star
id|BaseMailboxAddress
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Bytes 1-4 */
)brace
DECL|typedef|BusLogic_ExtendedMailboxRequest_T
id|BusLogic_ExtendedMailboxRequest_T
suffix:semicolon
multiline_comment|/*&n;  Define the Inquire Firmware Version 3rd Digit reply type.&n;*/
DECL|typedef|BusLogic_FirmwareVersion3rdDigit_T
r_typedef
r_int
r_char
id|BusLogic_FirmwareVersion3rdDigit_T
suffix:semicolon
multiline_comment|/*&n;  Define the Inquire Firmware Version Letter reply type.&n;*/
DECL|typedef|BusLogic_FirmwareVersionLetter_T
r_typedef
r_int
r_char
id|BusLogic_FirmwareVersionLetter_T
suffix:semicolon
multiline_comment|/*&n;  Define the Inquire Generic I/O Port Information reply type.&n;*/
DECL|struct|BusLogic_GenericIOPortInformation
r_typedef
r_struct
id|BusLogic_GenericIOPortInformation
(brace
DECL|member|ISACompatibleIOPort
r_int
r_char
id|ISACompatibleIOPort
suffix:semicolon
multiline_comment|/* Byte 0 */
DECL|member|PCIAssignedIRQChannel
r_int
r_char
id|PCIAssignedIRQChannel
suffix:semicolon
multiline_comment|/* Byte 1 */
DECL|member|LowByteTerminated
id|boolean
id|LowByteTerminated
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 2 Bit 0 */
DECL|member|HighByteTerminated
id|boolean
id|HighByteTerminated
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 2 Bit 1 */
r_int
r_char
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Byte 2 Bits 2-3 */
DECL|member|JP1
id|boolean
id|JP1
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 2 Bit 4 */
DECL|member|JP2
id|boolean
id|JP2
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 2 Bit 5 */
DECL|member|JP3
id|boolean
id|JP3
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 2 Bit 6 */
DECL|member|Valid
id|boolean
id|Valid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 2 Bit 7 */
r_int
r_char
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Byte 3 */
)brace
DECL|typedef|BusLogic_GenericIOPortInformation_T
id|BusLogic_GenericIOPortInformation_T
suffix:semicolon
multiline_comment|/*&n;  Define the Inquire Board Model Number reply type.&n;*/
DECL|typedef|BusLogic_BoardModelNumber_T
r_typedef
r_int
r_char
id|BusLogic_BoardModelNumber_T
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/*&n;  Define the Inquire Synchronous Period reply type.  For each Target Device,&n;  a byte is returned which represents the Synchronous Transfer Period in units&n;  of 10 nanoseconds.&n;*/
DECL|typedef|BusLogic_SynchronousPeriod_T
r_typedef
r_int
r_char
id|BusLogic_SynchronousPeriod_T
(braket
id|BusLogic_MaxTargetDevices
)braket
suffix:semicolon
multiline_comment|/*&n;  Define the Inquire Extended Setup Information reply structure.&n;*/
DECL|struct|BusLogic_ExtendedSetupInformation
r_typedef
r_struct
id|BusLogic_ExtendedSetupInformation
(brace
DECL|member|BusType
r_int
r_char
id|BusType
suffix:semicolon
multiline_comment|/* Byte 0 */
DECL|member|BIOS_Address
r_int
r_char
id|BIOS_Address
suffix:semicolon
multiline_comment|/* Byte 1 */
DECL|member|ScatterGatherLimit
r_int
r_int
id|ScatterGatherLimit
suffix:semicolon
multiline_comment|/* Bytes 2-3 */
DECL|member|MailboxCount
r_int
r_char
id|MailboxCount
suffix:semicolon
multiline_comment|/* Byte 4 */
DECL|member|BaseMailboxAddress
r_void
op_star
id|BaseMailboxAddress
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* Bytes 5-8 */
r_struct
(brace
r_int
r_char
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Byte 9 Bits 0-5 */
DECL|member|LevelSensitiveInterrupts
id|boolean
id|LevelSensitiveInterrupts
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 9 Bit 6 */
DECL|member|Misc
r_int
r_char
suffix:colon
l_int|1
suffix:semicolon
)brace
id|Misc
suffix:semicolon
multiline_comment|/* Byte 9 Bit 7 */
DECL|member|FirmwareRevision
r_int
r_char
id|FirmwareRevision
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Bytes 10-12 */
DECL|member|HostWideSCSI
id|boolean
id|HostWideSCSI
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 13 Bit 0 */
DECL|member|HostDifferentialSCSI
id|boolean
id|HostDifferentialSCSI
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 13 Bit 1 */
DECL|member|HostAutomaticConfiguration
id|boolean
id|HostAutomaticConfiguration
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 13 Bit 2 */
DECL|member|HostUltraSCSI
id|boolean
id|HostUltraSCSI
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 13 Bit 3 */
r_int
r_char
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* Byte 13 Bits 4-7 */
)brace
DECL|typedef|BusLogic_ExtendedSetupInformation_T
id|BusLogic_ExtendedSetupInformation_T
suffix:semicolon
multiline_comment|/*&n;  Define the Enable Strict Round Robin Mode request type.&n;*/
DECL|macro|BusLogic_AggressiveRoundRobinMode
mdefine_line|#define BusLogic_AggressiveRoundRobinMode&t;0x00
DECL|macro|BusLogic_StrictRoundRobinMode
mdefine_line|#define BusLogic_StrictRoundRobinMode&t;&t;0x01
DECL|typedef|BusLogic_RoundRobinModeRequest_T
r_typedef
r_int
r_char
id|BusLogic_RoundRobinModeRequest_T
suffix:semicolon
multiline_comment|/*&n;  Define the Fetch Host Adapter Local RAM request type.&n;*/
DECL|macro|BusLogic_BIOS_BaseOffset
mdefine_line|#define BusLogic_BIOS_BaseOffset&t;&t;0
DECL|macro|BusLogic_AutoSCSI_BaseOffset
mdefine_line|#define BusLogic_AutoSCSI_BaseOffset&t;&t;64
DECL|struct|BusLogic_FetchHostAdapterLocalRAMRequest
r_typedef
r_struct
id|BusLogic_FetchHostAdapterLocalRAMRequest
(brace
DECL|member|ByteOffset
r_int
r_char
id|ByteOffset
suffix:semicolon
multiline_comment|/* Byte 0 */
DECL|member|ByteCount
r_int
r_char
id|ByteCount
suffix:semicolon
multiline_comment|/* Byte 1 */
)brace
DECL|typedef|BusLogic_FetchHostAdapterLocalRAMRequest_T
id|BusLogic_FetchHostAdapterLocalRAMRequest_T
suffix:semicolon
multiline_comment|/*&n;  Define the Host Adapter Local RAM Auto SCSI Byte 15 reply structure.&n;*/
DECL|struct|BusLogic_AutoSCSIByte15
r_typedef
r_struct
id|BusLogic_AutoSCSIByte15
(brace
DECL|member|LowByteTerminated
r_int
r_char
id|LowByteTerminated
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Bit 0 */
r_int
r_char
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Bit 1 */
DECL|member|HighByteTerminated
r_int
r_char
id|HighByteTerminated
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Bit 2 */
r_int
r_char
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* Bits 3-7 */
)brace
DECL|typedef|BusLogic_AutoSCSIByte15_T
id|BusLogic_AutoSCSIByte15_T
suffix:semicolon
multiline_comment|/*&n;  Define the Host Adapter Local RAM Auto SCSI Byte 45 reply structure.&n;*/
DECL|struct|BusLogic_AutoSCSIByte45
r_typedef
r_struct
id|BusLogic_AutoSCSIByte45
(brace
DECL|member|ForceBusDeviceScanningOrder
r_int
r_char
id|ForceBusDeviceScanningOrder
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Bit 0 */
r_int
r_char
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/* Bits 1-7 */
)brace
DECL|typedef|BusLogic_AutoSCSIByte45_T
id|BusLogic_AutoSCSIByte45_T
suffix:semicolon
multiline_comment|/*&n;  Define the Modify I/O Address request type.  On PCI Host Adapters, the&n;  Modify I/O Address command allows modification of the ISA compatible I/O&n;  Address that the Host Adapter responds to; it does not affect the PCI&n;  compliant I/O Address assigned at system initialization.&n;*/
DECL|macro|BusLogic_ModifyIO_330
mdefine_line|#define BusLogic_ModifyIO_330&t;&t;&t;0x00
DECL|macro|BusLogic_ModifyIO_334
mdefine_line|#define BusLogic_ModifyIO_334&t;&t;&t;0x01
DECL|macro|BusLogic_ModifyIO_230
mdefine_line|#define BusLogic_ModifyIO_230&t;&t;&t;0x02
DECL|macro|BusLogic_ModifyIO_234
mdefine_line|#define BusLogic_ModifyIO_234&t;&t;&t;0x03
DECL|macro|BusLogic_ModifyIO_130
mdefine_line|#define BusLogic_ModifyIO_130&t;&t;&t;0x04
DECL|macro|BusLogic_ModifyIO_134
mdefine_line|#define BusLogic_ModifyIO_134&t;&t;&t;0x05
DECL|macro|BusLogic_ModifyIO_Disable
mdefine_line|#define BusLogic_ModifyIO_Disable&t;&t;0x06
DECL|macro|BusLogic_ModifyIO_Disable2
mdefine_line|#define BusLogic_ModifyIO_Disable2&t;&t;0x07
DECL|typedef|BusLogic_ModifyIOAddressRequest_T
r_typedef
r_int
r_char
id|BusLogic_ModifyIOAddressRequest_T
suffix:semicolon
multiline_comment|/*&n;  Define the Enable Wide Mode SCSI CCB request type.  Wide Mode CCBs are&n;  necessary to support more than 8 Logical Units per Target Device.&n;*/
DECL|macro|BusLogic_NormalModeCCB
mdefine_line|#define BusLogic_NormalModeCCB&t;&t;&t;0x00
DECL|macro|BusLogic_WideModeCCB
mdefine_line|#define BusLogic_WideModeCCB&t;&t;&t;0x01
DECL|typedef|BusLogic_WideModeCCBRequest_T
r_typedef
r_int
r_char
id|BusLogic_WideModeCCBRequest_T
suffix:semicolon
multiline_comment|/*&n;  Define the Requested Reply Length type used by the Inquire Setup Information,&n;  Inquire Board Model Number, Inquire Synchronous Period, and Inquire Extended&n;  Setup Information commands.&n;*/
DECL|typedef|BusLogic_RequestedReplyLength_T
r_typedef
r_int
r_char
id|BusLogic_RequestedReplyLength_T
suffix:semicolon
multiline_comment|/*&n;  Define a Lock data structure.  Until a true symmetric multiprocessing kernel&n;  with fine grained locking is available, acquiring the lock is implemented as&n;  saving the processor flags and disabling interrupts, and releasing the lock&n;  restores the saved processor flags.&n;*/
DECL|typedef|BusLogic_Lock_T
r_typedef
r_int
r_int
id|BusLogic_Lock_T
suffix:semicolon
multiline_comment|/*&n;  Define the Outgoing Mailbox Action Codes.&n;*/
r_typedef
r_enum
(brace
DECL|enumerator|BusLogic_OutgoingMailboxFree
id|BusLogic_OutgoingMailboxFree
op_assign
l_int|0
comma
DECL|enumerator|BusLogic_MailboxStartCommand
id|BusLogic_MailboxStartCommand
op_assign
l_int|1
comma
DECL|enumerator|BusLogic_MailboxAbortCommand
id|BusLogic_MailboxAbortCommand
op_assign
l_int|2
)brace
DECL|typedef|BusLogic_ActionCode_T
id|BusLogic_ActionCode_T
suffix:semicolon
multiline_comment|/*&n;  Define the Incoming Mailbox Completion Codes.&n;*/
r_typedef
r_enum
(brace
DECL|enumerator|BusLogic_IncomingMailboxFree
id|BusLogic_IncomingMailboxFree
op_assign
l_int|0
comma
DECL|enumerator|BusLogic_CommandCompletedWithoutError
id|BusLogic_CommandCompletedWithoutError
op_assign
l_int|1
comma
DECL|enumerator|BusLogic_CommandAbortedAtHostRequest
id|BusLogic_CommandAbortedAtHostRequest
op_assign
l_int|2
comma
DECL|enumerator|BusLogic_AbortedCommandNotFound
id|BusLogic_AbortedCommandNotFound
op_assign
l_int|3
comma
DECL|enumerator|BusLogic_CommandCompletedWithError
id|BusLogic_CommandCompletedWithError
op_assign
l_int|4
)brace
DECL|typedef|BusLogic_CompletionCode_T
id|BusLogic_CompletionCode_T
suffix:semicolon
multiline_comment|/*&n;  Define the Command Control Block (CCB) Opcodes.&n;*/
r_typedef
r_enum
(brace
DECL|enumerator|BusLogic_InitiatorCCB
id|BusLogic_InitiatorCCB
op_assign
l_int|0x00
comma
DECL|enumerator|BusLogic_TargetCCB
id|BusLogic_TargetCCB
op_assign
l_int|0x01
comma
DECL|enumerator|BusLogic_InitiatorCCB_ScatterGather
id|BusLogic_InitiatorCCB_ScatterGather
op_assign
l_int|0x02
comma
DECL|enumerator|BusLogic_InitiatorCCB_ResidualDataLength
id|BusLogic_InitiatorCCB_ResidualDataLength
op_assign
l_int|0x03
comma
DECL|enumerator|BusLogic_InitiatorCCB_ScatterGatherResidual
id|BusLogic_InitiatorCCB_ScatterGatherResidual
op_assign
l_int|0x04
comma
DECL|enumerator|BusLogic_BusDeviceReset
id|BusLogic_BusDeviceReset
op_assign
l_int|0x81
)brace
DECL|typedef|BusLogic_CCB_Opcode_T
id|BusLogic_CCB_Opcode_T
suffix:semicolon
multiline_comment|/*&n;  Define the CCB Data Direction Codes.&n;*/
r_typedef
r_enum
(brace
DECL|enumerator|BusLogic_UncheckedDataTransfer
id|BusLogic_UncheckedDataTransfer
op_assign
l_int|0x00
comma
DECL|enumerator|BusLogic_DataInLengthChecked
id|BusLogic_DataInLengthChecked
op_assign
l_int|0x01
comma
DECL|enumerator|BusLogic_DataOutLengthChecked
id|BusLogic_DataOutLengthChecked
op_assign
l_int|0x02
comma
DECL|enumerator|BusLogic_NoDataTransfer
id|BusLogic_NoDataTransfer
op_assign
l_int|0x03
)brace
DECL|typedef|BusLogic_DataDirection_T
id|BusLogic_DataDirection_T
suffix:semicolon
multiline_comment|/*&n;  Define the Host Adapter Status Codes.&n;*/
r_typedef
r_enum
(brace
DECL|enumerator|BusLogic_CommandCompletedNormally
id|BusLogic_CommandCompletedNormally
op_assign
l_int|0x00
comma
DECL|enumerator|BusLogic_LinkedCommandCompleted
id|BusLogic_LinkedCommandCompleted
op_assign
l_int|0x0A
comma
DECL|enumerator|BusLogic_LinkedCommandCompletedWithFlag
id|BusLogic_LinkedCommandCompletedWithFlag
op_assign
l_int|0x0B
comma
DECL|enumerator|BusLogic_SCSISelectionTimeout
id|BusLogic_SCSISelectionTimeout
op_assign
l_int|0x11
comma
DECL|enumerator|BusLogic_DataOverUnderRun
id|BusLogic_DataOverUnderRun
op_assign
l_int|0x12
comma
DECL|enumerator|BusLogic_UnexpectedBusFree
id|BusLogic_UnexpectedBusFree
op_assign
l_int|0x13
comma
DECL|enumerator|BusLogic_InvalidBusPhaseRequested
id|BusLogic_InvalidBusPhaseRequested
op_assign
l_int|0x14
comma
DECL|enumerator|BusLogic_InvalidOutgoingMailboxActionCode
id|BusLogic_InvalidOutgoingMailboxActionCode
op_assign
l_int|0x15
comma
DECL|enumerator|BusLogic_InvalidCommandOperationCode
id|BusLogic_InvalidCommandOperationCode
op_assign
l_int|0x16
comma
DECL|enumerator|BusLogic_LinkedCCBhasInvalidLUN
id|BusLogic_LinkedCCBhasInvalidLUN
op_assign
l_int|0x17
comma
DECL|enumerator|BusLogic_InvalidCommandParameter
id|BusLogic_InvalidCommandParameter
op_assign
l_int|0x1A
comma
DECL|enumerator|BusLogic_AutoRequestSenseFailed
id|BusLogic_AutoRequestSenseFailed
op_assign
l_int|0x1B
comma
DECL|enumerator|BusLogic_TaggedQueuingMessageRejected
id|BusLogic_TaggedQueuingMessageRejected
op_assign
l_int|0x1C
comma
DECL|enumerator|BusLogic_UnsupportedMessageReceived
id|BusLogic_UnsupportedMessageReceived
op_assign
l_int|0x1D
comma
DECL|enumerator|BusLogic_HostAdapterHardwareFailed
id|BusLogic_HostAdapterHardwareFailed
op_assign
l_int|0x20
comma
DECL|enumerator|BusLogic_TargetFailedResponseToATN
id|BusLogic_TargetFailedResponseToATN
op_assign
l_int|0x21
comma
DECL|enumerator|BusLogic_HostAdapterAssertedRST
id|BusLogic_HostAdapterAssertedRST
op_assign
l_int|0x22
comma
DECL|enumerator|BusLogic_OtherDeviceAssertedRST
id|BusLogic_OtherDeviceAssertedRST
op_assign
l_int|0x23
comma
DECL|enumerator|BusLogic_TargetDeviceReconnectedImproperly
id|BusLogic_TargetDeviceReconnectedImproperly
op_assign
l_int|0x24
comma
DECL|enumerator|BusLogic_HostAdapterAssertedBusDeviceReset
id|BusLogic_HostAdapterAssertedBusDeviceReset
op_assign
l_int|0x25
comma
DECL|enumerator|BusLogic_AbortQueueGenerated
id|BusLogic_AbortQueueGenerated
op_assign
l_int|0x26
comma
DECL|enumerator|BusLogic_HostAdapterSoftwareError
id|BusLogic_HostAdapterSoftwareError
op_assign
l_int|0x27
comma
DECL|enumerator|BusLogic_HostAdapterHardwareTimeoutError
id|BusLogic_HostAdapterHardwareTimeoutError
op_assign
l_int|0x30
comma
DECL|enumerator|BusLogic_SCSIParityErrorDetected
id|BusLogic_SCSIParityErrorDetected
op_assign
l_int|0x34
)brace
DECL|typedef|BusLogic_HostAdapterStatus_T
id|BusLogic_HostAdapterStatus_T
suffix:semicolon
multiline_comment|/*&n;  Define the SCSI Target Device Status Codes.&n;*/
r_typedef
r_enum
(brace
DECL|enumerator|BusLogic_OperationGood
id|BusLogic_OperationGood
op_assign
l_int|0x00
comma
DECL|enumerator|BusLogic_CheckCondition
id|BusLogic_CheckCondition
op_assign
l_int|0x02
comma
DECL|enumerator|BusLogic_DeviceBusy
id|BusLogic_DeviceBusy
op_assign
l_int|0x08
)brace
DECL|typedef|BusLogic_TargetDeviceStatus_T
id|BusLogic_TargetDeviceStatus_T
suffix:semicolon
multiline_comment|/*&n;  Define the Queue Tag Codes.&n;*/
r_typedef
r_enum
(brace
DECL|enumerator|BusLogic_SimpleQueueTag
id|BusLogic_SimpleQueueTag
op_assign
l_int|0x00
comma
DECL|enumerator|BusLogic_HeadOfQueueTag
id|BusLogic_HeadOfQueueTag
op_assign
l_int|0x01
comma
DECL|enumerator|BusLogic_OrderedQueueTag
id|BusLogic_OrderedQueueTag
op_assign
l_int|0x02
comma
DECL|enumerator|BusLogic_ReservedQT
id|BusLogic_ReservedQT
op_assign
l_int|0x03
)brace
DECL|typedef|BusLogic_QueueTag_T
id|BusLogic_QueueTag_T
suffix:semicolon
multiline_comment|/*&n;  Define the SCSI Command Descriptor Block (CDB).&n;*/
DECL|macro|BusLogic_CDB_MaxLength
mdefine_line|#define BusLogic_CDB_MaxLength&t;&t;&t;12
DECL|typedef|SCSI_CDB_T
r_typedef
r_int
r_char
id|SCSI_CDB_T
(braket
id|BusLogic_CDB_MaxLength
)braket
suffix:semicolon
multiline_comment|/*&n;  Define the SCSI Sense Data.&n;*/
DECL|macro|BusLogic_SenseDataMaxLength
mdefine_line|#define BusLogic_SenseDataMaxLength&t;&t;255
DECL|typedef|SCSI_SenseData_T
r_typedef
r_int
r_char
id|SCSI_SenseData_T
(braket
id|BusLogic_SenseDataMaxLength
)braket
suffix:semicolon
multiline_comment|/*&n;  Define the Scatter/Gather Segment structure required by the Host Adapter&n;  Firmware Interface.&n;*/
DECL|struct|BusLogic_ScatterGatherSegment
r_typedef
r_struct
id|BusLogic_ScatterGatherSegment
(brace
DECL|member|SegmentByteCount
r_int
r_int
id|SegmentByteCount
suffix:semicolon
multiline_comment|/* Bytes 0-3 */
DECL|member|SegmentDataPointer
r_void
op_star
id|SegmentDataPointer
suffix:semicolon
multiline_comment|/* Bytes 4-7 */
)brace
DECL|typedef|BusLogic_ScatterGatherSegment_T
id|BusLogic_ScatterGatherSegment_T
suffix:semicolon
multiline_comment|/*&n;  Define the 32 Bit Mode Command Control Block (CCB) structure.  The first 40&n;  bytes are defined by the Host Adapter Firmware Interface.  The remaining&n;  components are defined by the Linux BusLogic Driver.  Wide Mode CCBs differ&n;  from standard 32 Bit Mode CCBs only in having the TagEnable and QueueTag&n;  fields moved from byte 17 to byte 1, and the Logical Unit field in byte 17&n;  expanded to 6 bits; unfortunately, using a union of structs containing&n;  enumeration type bitfields to provide both definitions leads to packing&n;  problems, so the following definition is used which requires setting&n;  TagEnable to Logical Unit bit 5 in Wide Mode CCBs.&n;*/
DECL|struct|BusLogic_CCB
r_typedef
r_struct
id|BusLogic_CCB
(brace
multiline_comment|/*&n;    BusLogic Host Adapter Firmware Portion.&n;  */
DECL|member|Opcode
id|BusLogic_CCB_Opcode_T
id|Opcode
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Byte 0 */
r_int
r_char
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Byte 1 Bits 0-2 */
DECL|member|DataDirection
id|BusLogic_DataDirection_T
id|DataDirection
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Byte 1 Bits 3-4 */
DECL|member|WideModeTagEnable
id|boolean
id|WideModeTagEnable
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 1 Bit 5 */
DECL|member|WideModeQueueTag
id|BusLogic_QueueTag_T
id|WideModeQueueTag
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Byte 1 Bits 6-7 */
DECL|member|CDB_Length
r_int
r_char
id|CDB_Length
suffix:semicolon
multiline_comment|/* Byte 2 */
DECL|member|SenseDataLength
r_int
r_char
id|SenseDataLength
suffix:semicolon
multiline_comment|/* Byte 3 */
DECL|member|DataLength
r_int
r_int
id|DataLength
suffix:semicolon
multiline_comment|/* Bytes 4-7 */
DECL|member|DataPointer
r_void
op_star
id|DataPointer
suffix:semicolon
multiline_comment|/* Bytes 8-11 */
r_int
r_char
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Byte 12 */
r_int
r_char
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Byte 13 */
DECL|member|HostAdapterStatus
id|BusLogic_HostAdapterStatus_T
id|HostAdapterStatus
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Byte 14 */
DECL|member|TargetDeviceStatus
id|BusLogic_TargetDeviceStatus_T
id|TargetDeviceStatus
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Byte 15 */
DECL|member|TargetID
r_int
r_char
id|TargetID
suffix:semicolon
multiline_comment|/* Byte 16 */
DECL|member|LogicalUnit
r_int
r_char
id|LogicalUnit
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* Byte 17 Bits 0-4 */
DECL|member|TagEnable
id|boolean
id|TagEnable
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Byte 17 Bit 5 */
DECL|member|QueueTag
id|BusLogic_QueueTag_T
id|QueueTag
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Byte 17 Bits 6-7 */
DECL|member|CDB
id|SCSI_CDB_T
id|CDB
suffix:semicolon
multiline_comment|/* Bytes 18-29 */
r_int
r_char
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Byte 30 */
r_int
r_char
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Byte 31 */
r_int
r_int
suffix:colon
l_int|32
suffix:semicolon
multiline_comment|/* Bytes 32-35 */
DECL|member|SenseDataPointer
id|SCSI_SenseData_T
op_star
id|SenseDataPointer
suffix:semicolon
multiline_comment|/* Bytes 36-39 */
multiline_comment|/*&n;    BusLogic Linux Driver Portion.&n;  */
DECL|member|HostAdapter
r_struct
id|BusLogic_HostAdapter
op_star
id|HostAdapter
suffix:semicolon
DECL|member|Command
id|SCSI_Command_T
op_star
id|Command
suffix:semicolon
DECL|enumerator|BusLogic_CCB_Free
r_enum
(brace
id|BusLogic_CCB_Free
op_assign
l_int|0
comma
DECL|enumerator|BusLogic_CCB_Active
id|BusLogic_CCB_Active
op_assign
l_int|1
comma
DECL|enumerator|BusLogic_CCB_Completed
id|BusLogic_CCB_Completed
op_assign
l_int|2
comma
DECL|enumerator|BusLogic_CCB_Reset
DECL|member|Status
id|BusLogic_CCB_Reset
op_assign
l_int|3
)brace
id|Status
suffix:semicolon
DECL|member|MailboxCompletionCode
id|BusLogic_CompletionCode_T
id|MailboxCompletionCode
suffix:semicolon
DECL|member|SerialNumber
r_int
r_int
id|SerialNumber
suffix:semicolon
DECL|member|Next
r_struct
id|BusLogic_CCB
op_star
id|Next
suffix:semicolon
DECL|member|NextAll
r_struct
id|BusLogic_CCB
op_star
id|NextAll
suffix:semicolon
id|BusLogic_ScatterGatherSegment_T
DECL|member|ScatterGatherList
id|ScatterGatherList
(braket
id|BusLogic_ScatterGatherLimit
)braket
suffix:semicolon
)brace
DECL|typedef|BusLogic_CCB_T
id|BusLogic_CCB_T
suffix:semicolon
multiline_comment|/*&n;  Define the 32 Bit Mode Outgoing Mailbox structure.&n;*/
DECL|struct|BusLogic_OutgoingMailbox
r_typedef
r_struct
id|BusLogic_OutgoingMailbox
(brace
DECL|member|CCB
id|BusLogic_CCB_T
op_star
id|CCB
suffix:semicolon
multiline_comment|/* Bytes 0-3 */
r_int
r_int
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* Byte 4 */
DECL|member|ActionCode
id|BusLogic_ActionCode_T
id|ActionCode
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Bytes 5-7 */
)brace
DECL|typedef|BusLogic_OutgoingMailbox_T
id|BusLogic_OutgoingMailbox_T
suffix:semicolon
multiline_comment|/*&n;  Define the 32 Bit Mode Incoming Mailbox structure.&n;*/
DECL|struct|BusLogic_IncomingMailbox
r_typedef
r_struct
id|BusLogic_IncomingMailbox
(brace
DECL|member|CCB
id|BusLogic_CCB_T
op_star
id|CCB
suffix:semicolon
multiline_comment|/* Bytes 0-3 */
DECL|member|HostAdapterStatus
id|BusLogic_HostAdapterStatus_T
id|HostAdapterStatus
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Byte 4 */
DECL|member|TargetDeviceStatus
id|BusLogic_TargetDeviceStatus_T
id|TargetDeviceStatus
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Byte 5 */
r_int
r_char
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Byte 6 */
DECL|member|CompletionCode
id|BusLogic_CompletionCode_T
id|CompletionCode
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Byte 7 */
)brace
DECL|typedef|BusLogic_IncomingMailbox_T
id|BusLogic_IncomingMailbox_T
suffix:semicolon
multiline_comment|/*&n;  Define the possible Bus Types.&n;*/
r_typedef
r_enum
(brace
DECL|enumerator|BusLogic_Unknown_Bus
id|BusLogic_Unknown_Bus
op_assign
l_int|0
comma
DECL|enumerator|BusLogic_ISA_Bus
id|BusLogic_ISA_Bus
op_assign
l_int|1
comma
DECL|enumerator|BusLogic_MCA_Bus
id|BusLogic_MCA_Bus
op_assign
l_int|2
comma
DECL|enumerator|BusLogic_EISA_Bus
id|BusLogic_EISA_Bus
op_assign
l_int|3
comma
DECL|enumerator|BusLogic_VESA_Bus
id|BusLogic_VESA_Bus
op_assign
l_int|4
comma
DECL|enumerator|BusLogic_PCI_Bus
id|BusLogic_PCI_Bus
op_assign
l_int|5
)brace
DECL|typedef|BusLogic_BusType_T
id|BusLogic_BusType_T
suffix:semicolon
r_static
r_char
DECL|variable|BusLogic_BusNames
op_star
id|BusLogic_BusNames
(braket
)braket
op_assign
(brace
l_string|&quot;Unknown&quot;
comma
l_string|&quot;ISA&quot;
comma
l_string|&quot;MCA&quot;
comma
l_string|&quot;EISA&quot;
comma
l_string|&quot;VESA&quot;
comma
l_string|&quot;PCI&quot;
)brace
suffix:semicolon
multiline_comment|/*&n;  Define the Linux BusLogic Driver Command Line Entry structure.&n;*/
DECL|struct|BusLogic_CommandLineEntry
r_typedef
r_struct
id|BusLogic_CommandLineEntry
(brace
DECL|member|IO_Address
r_int
r_int
id|IO_Address
suffix:semicolon
DECL|member|TaggedQueueDepth
r_int
r_int
id|TaggedQueueDepth
suffix:semicolon
DECL|member|BusSettleTime
r_int
r_int
id|BusSettleTime
suffix:semicolon
DECL|member|LocalOptions
r_int
r_int
id|LocalOptions
suffix:semicolon
DECL|member|TaggedQueuingPermitted
r_int
r_int
id|TaggedQueuingPermitted
suffix:semicolon
DECL|member|TaggedQueuingPermittedMask
r_int
r_int
id|TaggedQueuingPermittedMask
suffix:semicolon
DECL|member|ErrorRecoveryStrategy
r_int
r_char
id|ErrorRecoveryStrategy
(braket
id|BusLogic_MaxTargetDevices
)braket
suffix:semicolon
)brace
DECL|typedef|BusLogic_CommandLineEntry_T
id|BusLogic_CommandLineEntry_T
suffix:semicolon
multiline_comment|/*&n;  Define the Linux BusLogic Driver Host Adapter structure.&n;*/
DECL|struct|BusLogic_HostAdapter
r_typedef
r_struct
id|BusLogic_HostAdapter
(brace
DECL|member|SCSI_Host
id|SCSI_Host_T
op_star
id|SCSI_Host
suffix:semicolon
DECL|member|HostNumber
r_int
r_char
id|HostNumber
suffix:semicolon
DECL|member|ModelName
r_int
r_char
id|ModelName
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|FirmwareVersion
r_int
r_char
id|FirmwareVersion
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|BoardName
r_int
r_char
id|BoardName
(braket
l_int|18
)braket
suffix:semicolon
DECL|member|InterruptLabel
r_int
r_char
id|InterruptLabel
(braket
l_int|62
)braket
suffix:semicolon
DECL|member|IO_Address
r_int
r_int
id|IO_Address
suffix:semicolon
DECL|member|IRQ_Channel
r_int
r_char
id|IRQ_Channel
suffix:semicolon
DECL|member|DMA_Channel
r_int
r_char
id|DMA_Channel
suffix:semicolon
DECL|member|SCSI_ID
r_int
r_char
id|SCSI_ID
suffix:semicolon
DECL|member|BusType
id|BusLogic_BusType_T
id|BusType
suffix:colon
l_int|3
suffix:semicolon
DECL|member|IRQ_ChannelAcquired
id|boolean
id|IRQ_ChannelAcquired
suffix:colon
l_int|1
suffix:semicolon
DECL|member|DMA_ChannelAcquired
id|boolean
id|DMA_ChannelAcquired
suffix:colon
l_int|1
suffix:semicolon
DECL|member|SynchronousInitiation
id|boolean
id|SynchronousInitiation
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ParityChecking
id|boolean
id|ParityChecking
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ExtendedTranslation
id|boolean
id|ExtendedTranslation
suffix:colon
l_int|1
suffix:semicolon
DECL|member|LevelSensitiveInterrupts
id|boolean
id|LevelSensitiveInterrupts
suffix:colon
l_int|1
suffix:semicolon
DECL|member|HostWideSCSI
id|boolean
id|HostWideSCSI
suffix:colon
l_int|1
suffix:semicolon
DECL|member|HostDifferentialSCSI
id|boolean
id|HostDifferentialSCSI
suffix:colon
l_int|1
suffix:semicolon
DECL|member|HostAutomaticConfiguration
id|boolean
id|HostAutomaticConfiguration
suffix:colon
l_int|1
suffix:semicolon
DECL|member|HostUltraSCSI
id|boolean
id|HostUltraSCSI
suffix:colon
l_int|1
suffix:semicolon
DECL|member|TerminationInfoValid
id|boolean
id|TerminationInfoValid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|LowByteTerminated
id|boolean
id|LowByteTerminated
suffix:colon
l_int|1
suffix:semicolon
DECL|member|HighByteTerminated
id|boolean
id|HighByteTerminated
suffix:colon
l_int|1
suffix:semicolon
DECL|member|BounceBuffersRequired
id|boolean
id|BounceBuffersRequired
suffix:colon
l_int|1
suffix:semicolon
DECL|member|StrictRoundRobinModeSupported
id|boolean
id|StrictRoundRobinModeSupported
suffix:colon
l_int|1
suffix:semicolon
DECL|member|HostAdapterResetRequested
id|boolean
id|HostAdapterResetRequested
suffix:colon
l_int|1
suffix:semicolon
DECL|member|HostAdapterCommandCompleted
r_volatile
id|boolean
id|HostAdapterCommandCompleted
suffix:colon
l_int|1
suffix:semicolon
DECL|member|HostAdapterScatterGatherLimit
r_int
r_int
id|HostAdapterScatterGatherLimit
suffix:semicolon
DECL|member|DriverScatterGatherLimit
r_int
r_int
id|DriverScatterGatherLimit
suffix:semicolon
DECL|member|MaxTargetDevices
r_int
r_int
id|MaxTargetDevices
suffix:semicolon
DECL|member|MaxLogicalUnits
r_int
r_int
id|MaxLogicalUnits
suffix:semicolon
DECL|member|MailboxCount
r_int
r_int
id|MailboxCount
suffix:semicolon
DECL|member|InitialCCBs
r_int
r_int
id|InitialCCBs
suffix:semicolon
DECL|member|IncrementalCCBs
r_int
r_int
id|IncrementalCCBs
suffix:semicolon
DECL|member|TotalQueueDepth
r_int
r_int
id|TotalQueueDepth
suffix:semicolon
DECL|member|TaggedQueueDepth
r_int
r_int
id|TaggedQueueDepth
suffix:semicolon
DECL|member|UntaggedQueueDepth
r_int
r_int
id|UntaggedQueueDepth
suffix:semicolon
DECL|member|BusSettleTime
r_int
r_int
id|BusSettleTime
suffix:semicolon
DECL|member|LocalOptions
r_int
r_int
id|LocalOptions
suffix:semicolon
DECL|member|DisconnectPermitted
r_int
r_int
id|DisconnectPermitted
suffix:semicolon
DECL|member|TaggedQueuingPermitted
r_int
r_int
id|TaggedQueuingPermitted
suffix:semicolon
DECL|member|BIOS_Address
r_int
r_int
id|BIOS_Address
suffix:semicolon
DECL|member|InstalledDevices
id|BusLogic_InstalledDevices_T
id|InstalledDevices
suffix:semicolon
DECL|member|SynchronousValues
id|BusLogic_SynchronousValues_T
id|SynchronousValues
suffix:semicolon
DECL|member|SynchronousPeriod
id|BusLogic_SynchronousPeriod_T
id|SynchronousPeriod
suffix:semicolon
DECL|member|CommandLineEntry
id|BusLogic_CommandLineEntry_T
op_star
id|CommandLineEntry
suffix:semicolon
DECL|member|Next
r_struct
id|BusLogic_HostAdapter
op_star
id|Next
suffix:semicolon
DECL|member|All_CCBs
id|BusLogic_CCB_T
op_star
id|All_CCBs
suffix:semicolon
DECL|member|Free_CCBs
id|BusLogic_CCB_T
op_star
id|Free_CCBs
suffix:semicolon
DECL|member|BusDeviceResetPendingCCB
id|BusLogic_CCB_T
op_star
id|BusDeviceResetPendingCCB
(braket
id|BusLogic_MaxTargetDevices
)braket
suffix:semicolon
DECL|member|ErrorRecoveryStrategy
r_int
r_char
id|ErrorRecoveryStrategy
(braket
id|BusLogic_MaxTargetDevices
)braket
suffix:semicolon
DECL|member|TaggedQueuingActive
r_int
r_char
id|TaggedQueuingActive
(braket
id|BusLogic_MaxTargetDevices
)braket
suffix:semicolon
DECL|member|CommandSuccessfulFlag
r_int
r_char
id|CommandSuccessfulFlag
(braket
id|BusLogic_MaxTargetDevices
)braket
suffix:semicolon
DECL|member|ActiveCommandCount
r_int
r_char
id|ActiveCommandCount
(braket
id|BusLogic_MaxTargetDevices
)braket
suffix:semicolon
DECL|member|TotalCommandCount
r_int
r_int
id|TotalCommandCount
(braket
id|BusLogic_MaxTargetDevices
)braket
suffix:semicolon
DECL|member|LastSequencePoint
r_int
r_int
id|LastSequencePoint
(braket
id|BusLogic_MaxTargetDevices
)braket
suffix:semicolon
DECL|member|LastResetTime
r_int
r_int
id|LastResetTime
(braket
id|BusLogic_MaxTargetDevices
)braket
suffix:semicolon
DECL|member|FirstOutgoingMailbox
id|BusLogic_OutgoingMailbox_T
op_star
id|FirstOutgoingMailbox
suffix:semicolon
DECL|member|LastOutgoingMailbox
id|BusLogic_OutgoingMailbox_T
op_star
id|LastOutgoingMailbox
suffix:semicolon
DECL|member|NextOutgoingMailbox
id|BusLogic_OutgoingMailbox_T
op_star
id|NextOutgoingMailbox
suffix:semicolon
DECL|member|FirstIncomingMailbox
id|BusLogic_IncomingMailbox_T
op_star
id|FirstIncomingMailbox
suffix:semicolon
DECL|member|LastIncomingMailbox
id|BusLogic_IncomingMailbox_T
op_star
id|LastIncomingMailbox
suffix:semicolon
DECL|member|NextIncomingMailbox
id|BusLogic_IncomingMailbox_T
op_star
id|NextIncomingMailbox
suffix:semicolon
)brace
DECL|typedef|BusLogic_HostAdapter_T
id|BusLogic_HostAdapter_T
suffix:semicolon
multiline_comment|/*&n;  Define a structure for the BIOS Disk Parameters.&n;*/
DECL|struct|BIOS_DiskParameters
r_typedef
r_struct
id|BIOS_DiskParameters
(brace
DECL|member|Heads
r_int
id|Heads
suffix:semicolon
DECL|member|Sectors
r_int
id|Sectors
suffix:semicolon
DECL|member|Cylinders
r_int
id|Cylinders
suffix:semicolon
)brace
DECL|typedef|BIOS_DiskParameters_T
id|BIOS_DiskParameters_T
suffix:semicolon
multiline_comment|/*&n;  BusLogic_AcquireHostAdapterLock acquires exclusive access to Host Adapter.&n;*/
r_static
r_inline
DECL|function|BusLogic_AcquireHostAdapterLock
r_void
id|BusLogic_AcquireHostAdapterLock
c_func
(paren
id|BusLogic_HostAdapter_T
op_star
id|HostAdapter
comma
id|BusLogic_Lock_T
op_star
id|Lock
)paren
(brace
id|save_flags
c_func
(paren
op_star
id|Lock
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;  BusLogic_ReleaseHostAdapterLock releases exclusive access to Host Adapter.&n;*/
r_static
r_inline
DECL|function|BusLogic_ReleaseHostAdapterLock
r_void
id|BusLogic_ReleaseHostAdapterLock
c_func
(paren
id|BusLogic_HostAdapter_T
op_star
id|HostAdapter
comma
id|BusLogic_Lock_T
op_star
id|Lock
)paren
(brace
id|restore_flags
c_func
(paren
op_star
id|Lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;  BusLogic_AcquireHostAdapterLockID acquires exclusive access to Host Adapter,&n;  but is only called when interrupts are disabled.&n;*/
r_static
r_inline
DECL|function|BusLogic_AcquireHostAdapterLockID
r_void
id|BusLogic_AcquireHostAdapterLockID
c_func
(paren
id|BusLogic_HostAdapter_T
op_star
id|HostAdapter
comma
id|BusLogic_Lock_T
op_star
id|Lock
)paren
(brace
)brace
multiline_comment|/*&n;  BusLogic_ReleaseHostAdapterLockID releases exclusive access to Host Adapter,&n;  but is only called when interrupts are disabled.&n;*/
r_static
r_inline
DECL|function|BusLogic_ReleaseHostAdapterLockID
r_void
id|BusLogic_ReleaseHostAdapterLockID
c_func
(paren
id|BusLogic_HostAdapter_T
op_star
id|HostAdapter
comma
id|BusLogic_Lock_T
op_star
id|Lock
)paren
(brace
)brace
multiline_comment|/*&n;  Define functions to provide an abstraction for reading and writing the&n;  Host Adapter I/O Registers.&n;*/
r_static
r_inline
DECL|function|BusLogic_WriteControlRegister
r_void
id|BusLogic_WriteControlRegister
c_func
(paren
id|BusLogic_HostAdapter_T
op_star
id|HostAdapter
comma
r_int
r_char
id|Value
)paren
(brace
id|outb
c_func
(paren
id|Value
comma
id|HostAdapter-&gt;IO_Address
op_plus
id|BusLogic_ControlRegister
)paren
suffix:semicolon
)brace
r_static
r_inline
DECL|function|BusLogic_ReadStatusRegister
r_int
r_char
id|BusLogic_ReadStatusRegister
c_func
(paren
id|BusLogic_HostAdapter_T
op_star
id|HostAdapter
)paren
(brace
r_return
id|inb
c_func
(paren
id|HostAdapter-&gt;IO_Address
op_plus
id|BusLogic_StatusRegister
)paren
suffix:semicolon
)brace
r_static
r_inline
DECL|function|BusLogic_WriteCommandParameterRegister
r_void
id|BusLogic_WriteCommandParameterRegister
c_func
(paren
id|BusLogic_HostAdapter_T
op_star
id|HostAdapter
comma
r_int
r_char
id|Value
)paren
(brace
id|outb
c_func
(paren
id|Value
comma
id|HostAdapter-&gt;IO_Address
op_plus
id|BusLogic_CommandParameterRegister
)paren
suffix:semicolon
)brace
r_static
r_inline
DECL|function|BusLogic_ReadDataInRegister
r_int
r_char
id|BusLogic_ReadDataInRegister
c_func
(paren
id|BusLogic_HostAdapter_T
op_star
id|HostAdapter
)paren
(brace
r_return
id|inb
c_func
(paren
id|HostAdapter-&gt;IO_Address
op_plus
id|BusLogic_DataInRegister
)paren
suffix:semicolon
)brace
r_static
r_inline
DECL|function|BusLogic_ReadInterruptRegister
r_int
r_char
id|BusLogic_ReadInterruptRegister
c_func
(paren
id|BusLogic_HostAdapter_T
op_star
id|HostAdapter
)paren
(brace
r_return
id|inb
c_func
(paren
id|HostAdapter-&gt;IO_Address
op_plus
id|BusLogic_InterruptRegister
)paren
suffix:semicolon
)brace
r_static
r_inline
DECL|function|BusLogic_ReadGeometryRegister
r_int
r_char
id|BusLogic_ReadGeometryRegister
c_func
(paren
id|BusLogic_HostAdapter_T
op_star
id|HostAdapter
)paren
(brace
r_return
id|inb
c_func
(paren
id|HostAdapter-&gt;IO_Address
op_plus
id|BusLogic_GeometryRegister
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;  BusLogic_StartMailboxCommand issues an Execute Mailbox Command, which&n;  notifies the Host Adapter that an entry has been made in an Outgoing&n;  Mailbox.&n;*/
r_static
r_inline
DECL|function|BusLogic_StartMailboxCommand
r_void
id|BusLogic_StartMailboxCommand
c_func
(paren
id|BusLogic_HostAdapter_T
op_star
id|HostAdapter
)paren
(brace
id|BusLogic_WriteCommandParameterRegister
c_func
(paren
id|HostAdapter
comma
id|BusLogic_ExecuteMailboxCommand
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;  BusLogic_Delay waits for Seconds to elapse.&n;*/
DECL|function|BusLogic_Delay
r_static
r_inline
r_void
id|BusLogic_Delay
c_func
(paren
r_int
id|Seconds
)paren
(brace
r_int
r_int
id|TimeoutJiffies
op_assign
id|jiffies
op_plus
id|Seconds
op_star
id|HZ
suffix:semicolon
r_int
r_int
id|ProcessorFlags
suffix:semicolon
id|save_flags
c_func
(paren
id|ProcessorFlags
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|jiffies
OL
id|TimeoutJiffies
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|ProcessorFlags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;  Define prototypes for the forward referenced BusLogic Driver&n;  Internal Functions.&n;*/
r_static
r_void
id|BusLogic_InterruptHandler
c_func
(paren
r_int
comma
r_void
op_star
comma
id|Registers_T
op_star
)paren
suffix:semicolon
r_static
r_int
id|BusLogic_ResetHostAdapter
c_func
(paren
id|BusLogic_HostAdapter_T
op_star
comma
id|SCSI_Command_T
op_star
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif /* BusLogic_DriverVersion */
eof
