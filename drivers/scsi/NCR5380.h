multiline_comment|/* &n; * NCR 5380 defines&n; *&n; * Copyright 1993, Drew Eckhardt&n; *&t;Visionary Computing&n; *&t;(Unix consulting and custom programming)&n; * &t;drew@colorado.edu&n; *      +1 (303) 440-4894&n; *&n; * DISTRIBUTION RELEASE 3&n; *&n; * For more information, please consult &n; *&n; * NCR 5380 Family&n; * SCSI Protocol Controller&n; * Databook&n; * NCR Microelectronics&n; * 1635 Aeroplaza Drive&n; * Colorado Springs, CO 80916&n; * 1+ (719) 578-3400&n; * 1+ (800) 334-5454&n; */
multiline_comment|/*&n; * $Log: NCR5380.h,v $&n; */
macro_line|#ifndef NCR5380_H
DECL|macro|NCR5380_H
mdefine_line|#define NCR5380_H
DECL|macro|NCR5380_PUBLIC_RELEASE
mdefine_line|#define NCR5380_PUBLIC_RELEASE 3
DECL|macro|NDEBUG_ARBITRATION
mdefine_line|#define NDEBUG_ARBITRATION&t;0x1
DECL|macro|NDEBUG_AUTOSENSE
mdefine_line|#define NDEBUG_AUTOSENSE&t;0x2
DECL|macro|NDEBUG_DMA
mdefine_line|#define NDEBUG_DMA&t;&t;0x4
DECL|macro|NDEBUG_HANDSHAKE
mdefine_line|#define NDEBUG_HANDSHAKE&t;0x8
DECL|macro|NDEBUG_INFORMATION
mdefine_line|#define NDEBUG_INFORMATION&t;0x10
DECL|macro|NDEBUG_INIT
mdefine_line|#define NDEBUG_INIT&t;&t;0x20
DECL|macro|NDEBUG_INTR
mdefine_line|#define NDEBUG_INTR&t;&t;0x40
DECL|macro|NDEBUG_LINKED
mdefine_line|#define NDEBUG_LINKED&t;&t;0x80
DECL|macro|NDEBUG_MAIN
mdefine_line|#define NDEBUG_MAIN&t;&t;0x100
DECL|macro|NDEBUG_NO_DATAOUT
mdefine_line|#define NDEBUG_NO_DATAOUT&t;0x200
DECL|macro|NDEBUG_NO_WRITE
mdefine_line|#define NDEBUG_NO_WRITE&t;&t;0x400
DECL|macro|NDEBUG_PIO
mdefine_line|#define NDEBUG_PIO&t;&t;0x800
DECL|macro|NDEBUG_PSEUDO_DMA
mdefine_line|#define NDEBUG_PSEUDO_DMA&t;0x1000
DECL|macro|NDEBUG_QUEUES
mdefine_line|#define NDEBUG_QUEUES&t;&t;0x2000
DECL|macro|NDEBUG_RESELECTION
mdefine_line|#define NDEBUG_RESELECTION&t;0x4000
DECL|macro|NDEBUG_SELECTION
mdefine_line|#define NDEBUG_SELECTION&t;0x8000
DECL|macro|NDEBUG_USLEEP
mdefine_line|#define NDEBUG_USLEEP&t;&t;0x10000
multiline_comment|/* &n; * The contents of the OUTPUT DATA register are asserted on the bus when&n; * either arbitration is occuring or the phase-indicating signals (&n; * IO, CD, MSG) in the TARGET COMMAND register and the ASSERT DATA&n; * bit in the INTITIATOR COMMAND register is set.&n; */
DECL|macro|OUTPUT_DATA_REG
mdefine_line|#define OUTPUT_DATA_REG         0       /* wo DATA lines on SCSI bus */
DECL|macro|CURRENT_SCSI_DATA_REG
mdefine_line|#define CURRENT_SCSI_DATA_REG   0       /* ro same */
DECL|macro|INITIATOR_COMMAND_REG
mdefine_line|#define INITIATOR_COMMAND_REG&t;1&t;/* rw */
DECL|macro|ICR_ASSERT_RST
mdefine_line|#define ICR_ASSERT_RST&t;&t;0x80&t;/* rw Set to assert RST  */
DECL|macro|ICR_ARBITRATION_PROGRESS
mdefine_line|#define ICR_ARBITRATION_PROGRESS 0x40&t;/* ro Indicates arbitration complete */
DECL|macro|ICR_TRI_STATE
mdefine_line|#define ICR_TRI_STATE&t;&t;0x40&t;/* wo Set to tri-state drivers */
DECL|macro|ICR_ARBITRATION_LOST
mdefine_line|#define ICR_ARBITRATION_LOST&t;0x20&t;/* ro Indicates arbitration lost */
DECL|macro|ICR_DIFF_ENABLE
mdefine_line|#define ICR_DIFF_ENABLE&t;&t;0x20&t;/* wo Set to enable diff. drivers */
DECL|macro|ICR_ASSERT_ACK
mdefine_line|#define ICR_ASSERT_ACK&t;&t;0x10&t;/* rw ini Set to assert ACK */
DECL|macro|ICR_ASSERT_BSY
mdefine_line|#define ICR_ASSERT_BSY&t;&t;0x08&t;/* rw Set to assert BSY */
DECL|macro|ICR_ASSERT_SEL
mdefine_line|#define ICR_ASSERT_SEL &t;&t;0x04&t;/* rw Set to assert SEL */
DECL|macro|ICR_ASSERT_ATN
mdefine_line|#define ICR_ASSERT_ATN&t;&t;0x02&t;/* rw Set to assert ATN */
DECL|macro|ICR_ASSERT_DATA
mdefine_line|#define ICR_ASSERT_DATA&t;&t;0x01&t;/* rw SCSI_DATA_REG is asserted */
macro_line|#ifdef DIFFERENTIAL
DECL|macro|ICR_BASE
mdefine_line|#define ICR_BASE&t;&t;ICR_DIFF_ENABLE
macro_line|#else
DECL|macro|ICR_BASE
mdefine_line|#define ICR_BASE&t;&t;0
macro_line|#endif
DECL|macro|MODE_REG
mdefine_line|#define MODE_REG&t;&t;2
multiline_comment|/*&n; * Note : BLOCK_DMA code will keep DRQ asserted for the duration of the &n; * transfer, causing the chip to hog the bus.  You probably don&squot;t want &n; * this.&n; */
DECL|macro|MR_BLOCK_DMA_MODE
mdefine_line|#define MR_BLOCK_DMA_MODE&t;0x80&t;/* rw block mode DMA */
DECL|macro|MR_TARGET
mdefine_line|#define MR_TARGET&t;&t;0x40&t;/* rw target mode */
DECL|macro|MR_ENABLE_PAR_CHECK
mdefine_line|#define MR_ENABLE_PAR_CHECK   0x20&t;/* rw enable parity checking */
DECL|macro|MR_ENABLE_PAR_INTR
mdefine_line|#define MR_ENABLE_PAR_INTR&t;0x10&t;/* rw enable bad parity interrupt */
DECL|macro|MR_ENABLE_EOP_INTR
mdefine_line|#define MR_ENABLE_EOP_INTR&t;0x08&t;/* rw enabble eop interrupt */
DECL|macro|MR_MONITOR_BSY
mdefine_line|#define MR_MONITOR_BSY&t;0x04&t;/* rw enable int on unexpected bsy fail */
DECL|macro|MR_DMA_MODE
mdefine_line|#define MR_DMA_MODE&t;&t;0x02&t;/* rw DMA / pseudo DMA mode */
DECL|macro|MR_ARBITRATE
mdefine_line|#define MR_ARBITRATE&t;&t;0x01&t;/* rw start arbitration */
macro_line|#ifdef PARITY
DECL|macro|MR_BASE
mdefine_line|#define MR_BASE&t;&t;&t;MR_ENABLE_PAR_CHECK
macro_line|#else
DECL|macro|MR_BASE
mdefine_line|#define MR_BASE&t;&t;&t;0
macro_line|#endif
DECL|macro|TARGET_COMMAND_REG
mdefine_line|#define TARGET_COMMAND_REG&t;3
DECL|macro|TCR_LAST_BYTE_SENT
mdefine_line|#define TCR_LAST_BYTE_SENT&t;0x80&t;/* ro DMA done */
DECL|macro|TCR_ASSERT_REQ
mdefine_line|#define TCR_ASSERT_REQ&t;&t;0x08&t;/* tgt rw assert REQ */
DECL|macro|TCR_ASSERT_MSG
mdefine_line|#define TCR_ASSERT_MSG&t;&t;0x04&t;/* tgt rw assert MSG */
DECL|macro|TCR_ASSERT_CD
mdefine_line|#define TCR_ASSERT_CD&t;&t;0x02&t;/* tgt rw assert CD */
DECL|macro|TCR_ASSERT_IO
mdefine_line|#define TCR_ASSERT_IO&t;&t;0x01&t;/* tgt rw assert IO */
DECL|macro|STATUS_REG
mdefine_line|#define STATUS_REG&t;&t;4&t;/* ro */
multiline_comment|/*&n; * Note : a set bit indicates an active signal, driven by us or another &n; * device.&n; */
DECL|macro|SR_RST
mdefine_line|#define SR_RST&t;&t;&t;0x80&t;
DECL|macro|SR_BSY
mdefine_line|#define SR_BSY&t;&t;&t;0x40
DECL|macro|SR_REQ
mdefine_line|#define SR_REQ&t;&t;&t;0x20
DECL|macro|SR_MSG
mdefine_line|#define SR_MSG&t;&t;&t;0x10
DECL|macro|SR_CD
mdefine_line|#define SR_CD&t;&t;&t;0x08
DECL|macro|SR_IO
mdefine_line|#define SR_IO&t;&t;&t;0x04
DECL|macro|SR_SEL
mdefine_line|#define SR_SEL&t;&t;&t;0x02
DECL|macro|SR_DBP
mdefine_line|#define SR_DBP&t;&t;&t;0x01
multiline_comment|/*&n; * Setting a bit in this register will cause an interrupt to be generated when &n; * BSY is false and SEL true and this bit is asserted  on the bus.&n; */
DECL|macro|SELECT_ENABLE_REG
mdefine_line|#define SELECT_ENABLE_REG&t;4&t;/* wo */
DECL|macro|BUS_AND_STATUS_REG
mdefine_line|#define BUS_AND_STATUS_REG&t;5&t;/* ro */
DECL|macro|BASR_END_DMA_TRANSFER
mdefine_line|#define BASR_END_DMA_TRANSFER&t;0x80&t;/* ro set on end of transfer */
DECL|macro|BASR_DRQ
mdefine_line|#define BASR_DRQ&t;&t;0x40&t;/* ro mirror of DRQ pin */
DECL|macro|BASR_PARITY_ERROR
mdefine_line|#define BASR_PARITY_ERROR&t;0x20&t;/* ro parity error detected */
DECL|macro|BASR_IRQ
mdefine_line|#define BASR_IRQ&t;&t;0x10&t;/* ro mirror of IRQ pin */
DECL|macro|BASR_PHASE_MATCH
mdefine_line|#define BASR_PHASE_MATCH&t;0x08&t;/* ro Set when MSG CD IO match TCR */
DECL|macro|BASR_BUSY_ERROR
mdefine_line|#define BASR_BUSY_ERROR&t;&t;0x04&t;/* ro Unexpected change to inactive state */
DECL|macro|BASR_ATN
mdefine_line|#define BASR_ATN &t;&t;0x02&t;/* ro BUS status */
DECL|macro|BASR_ACK
mdefine_line|#define BASR_ACK&t;&t;0x01&t;/* ro BUS status */
multiline_comment|/* Write any value to this register to start a DMA send */
DECL|macro|START_DMA_SEND_REG
mdefine_line|#define START_DMA_SEND_REG&t;5&t;/* wo */
multiline_comment|/* &n; * Used in DMA transfer mode, data is latched from the SCSI bus on&n; * the falling edge of REQ (ini) or ACK (tgt)&n; */
DECL|macro|INPUT_DATA_REGISTER
mdefine_line|#define INPUT_DATA_REGISTER&t;6&t;/* ro */
multiline_comment|/* Write any value to this register to start a DMA recieve */
DECL|macro|START_DMA_TARGET_RECIEVE_REG
mdefine_line|#define START_DMA_TARGET_RECIEVE_REG&t;6&t;/* wo */
multiline_comment|/* Read this register to clear interrupt conditions */
DECL|macro|RESET_PARITY_INTERRUPT_REG
mdefine_line|#define RESET_PARITY_INTERRUPT_REG&t;7&t;/* ro */
multiline_comment|/* Write any value to this register to start an ini mode DMA recieve */
DECL|macro|START_DMA_INITIATOR_RECIEVE_REG
mdefine_line|#define START_DMA_INITIATOR_RECIEVE_REG 7&t;/* wo */
multiline_comment|/* Note : PHASE_* macros are based on the values of the STATUS register */
DECL|macro|PHASE_MASK
mdefine_line|#define PHASE_MASK &t;(SR_MSG | SR_CD | SR_IO)
DECL|macro|PHASE_DATAOUT
mdefine_line|#define PHASE_DATAOUT&t;0
DECL|macro|PHASE_DATAIN
mdefine_line|#define PHASE_DATAIN&t;SR_IO
DECL|macro|PHASE_CMDOUT
mdefine_line|#define PHASE_CMDOUT&t;SR_CD
DECL|macro|PHASE_STATIN
mdefine_line|#define PHASE_STATIN&t;(SR_CD | SR_IO)
DECL|macro|PHASE_MSGOUT
mdefine_line|#define PHASE_MSGOUT&t;(SR_MSG | SR_CD)
DECL|macro|PHASE_MSGIN
mdefine_line|#define PHASE_MSGIN&t;(SR_MSG | SR_CD | SR_IO)
DECL|macro|PHASE_UNKNOWN
mdefine_line|#define PHASE_UNKNOWN&t;0xff
multiline_comment|/* &n; * Convert status register phase to something we can use to set phase in &n; * the target register so we can get phase mismatch interrupts on DMA &n; * transfers.&n; */
DECL|macro|PHASE_SR_TO_TCR
mdefine_line|#define PHASE_SR_TO_TCR(phase) ((phase) &gt;&gt; 2)&t;
multiline_comment|/*&n; * The internal should_disconnect() function returns these based on the &n; * expected length of a disconnect if a device supports disconnect/&n; * reconnect.&n; */
DECL|macro|DISCONNECT_NONE
mdefine_line|#define DISCONNECT_NONE&t;&t;0
DECL|macro|DISCONNECT_TIME_TO_DATA
mdefine_line|#define DISCONNECT_TIME_TO_DATA&t;1
DECL|macro|DISCONNECT_LONG
mdefine_line|#define DISCONNECT_LONG&t;&t;2
multiline_comment|/* &n; * These are &quot;special&quot; values for the tag parameter passed to NCR5380_select.&n; */
DECL|macro|TAG_NEXT
mdefine_line|#define TAG_NEXT&t;-1 &t;/* Use next free tag */
DECL|macro|TAG_NONE
mdefine_line|#define TAG_NONE&t;-2&t;/* &n;&t;&t;&t;&t; * Establish I_T_L nexus instead of I_T_L_Q&n;&t;&t;&t;&t; * even on SCSI-II devices.&n;&t;&t;&t;&t; */
multiline_comment|/*&n; * These are &quot;special&quot; values for the irq field of the instance structure&n; * and returns from NCR5380_probe_irq.&n; */
DECL|macro|IRQ_NONE
mdefine_line|#define IRQ_NONE&t;255
DECL|macro|IRQ_AUTO
mdefine_line|#define IRQ_AUTO&t;254
macro_line|#ifndef ASM
DECL|struct|NCR5380_hostdata
r_struct
id|NCR5380_hostdata
(brace
DECL|member|NCR5380_implementation_fields
id|NCR5380_implementation_fields
suffix:semicolon
multiline_comment|/* implmenentation specific */
DECL|member|id_mask
DECL|member|id_higher_mask
r_int
r_char
id|id_mask
comma
id|id_higher_mask
suffix:semicolon
multiline_comment|/* 1 &lt;&lt; id, all bits greater */
DECL|member|busy
r_volatile
r_int
r_char
id|busy
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* index = target, bit = lun */
macro_line|#ifdef REAL_DMA
DECL|member|dma_len
r_volatile
r_int
id|dma_len
suffix:semicolon
multiline_comment|/* requested length of DMA */
macro_line|#endif
DECL|member|last_message
r_volatile
r_int
r_char
id|last_message
suffix:semicolon
multiline_comment|/* last message OUT */
DECL|member|connected
r_volatile
id|Scsi_Cmnd
op_star
id|connected
suffix:semicolon
multiline_comment|/* currently connected command */
DECL|member|issue_queue
r_volatile
id|Scsi_Cmnd
op_star
id|issue_queue
suffix:semicolon
multiline_comment|/* waiting to be issued */
DECL|member|disconnected_queue
r_volatile
id|Scsi_Cmnd
op_star
id|disconnected_queue
suffix:semicolon
multiline_comment|/* waiting for reconnect */
macro_line|#ifdef USLEEP
DECL|member|time_expires
r_int
r_int
id|time_expires
suffix:semicolon
multiline_comment|/* in jiffies, set prior to sleeping */
DECL|member|next_timer
r_struct
id|Scsi_Host
op_star
id|next_timer
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|variable|first_instance
r_static
r_struct
id|Scsi_Host
op_star
id|first_instance
suffix:semicolon
multiline_comment|/* linked list of 5380&squot;s */
macro_line|#if defined(AUTOPROBE_IRQ)
r_static
r_int
id|NCR5380_probe_irq
(paren
r_struct
id|Scsi_Host
op_star
id|instance
comma
r_int
id|possible
)paren
suffix:semicolon
macro_line|#endif
r_static
r_void
id|NCR5380_init
(paren
r_struct
id|Scsi_Host
op_star
id|instance
)paren
suffix:semicolon
r_static
r_void
id|NCR5380_information_transfer
(paren
r_struct
id|Scsi_Host
op_star
id|instance
)paren
suffix:semicolon
r_static
r_void
id|NCR5380_intr
(paren
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|NCR5380_main
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|NCR5380_print_options
(paren
r_struct
id|Scsi_Host
op_star
id|instance
)paren
suffix:semicolon
macro_line|#ifndef NCR5380_abort
r_static
macro_line|#endif
r_int
id|NCR5380_abort
(paren
id|Scsi_Cmnd
op_star
id|cmd
comma
r_int
id|code
)paren
suffix:semicolon
macro_line|#ifndef NCR5380_reset
r_static
macro_line|#endif
r_int
id|NCR5380_reset
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifndef NCR5380_queue_command
r_static
macro_line|#endif
r_int
id|NCR5380_queue_command
(paren
id|Scsi_Cmnd
op_star
id|cmd
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_static
r_void
id|NCR5380_reselect
(paren
r_struct
id|Scsi_Host
op_star
id|instance
)paren
suffix:semicolon
r_static
r_int
id|NCR5380_select
(paren
r_struct
id|Scsi_Host
op_star
id|instance
comma
id|Scsi_Cmnd
op_star
id|cmd
comma
r_int
id|tag
)paren
suffix:semicolon
macro_line|#if defined(PSEUDO_DMA) || defined(REAL_DMA)
r_static
r_int
id|NCR5380_transfer_dma
(paren
r_struct
id|Scsi_Host
op_star
id|instance
comma
r_int
r_char
op_star
id|phase
comma
r_int
op_star
id|count
comma
r_int
r_char
op_star
op_star
id|data
)paren
suffix:semicolon
macro_line|#endif
r_static
r_int
id|NCR5380_transfer_pio
(paren
r_struct
id|Scsi_Host
op_star
id|instance
comma
r_int
r_char
op_star
id|phase
comma
r_int
op_star
id|count
comma
r_int
r_char
op_star
op_star
id|data
)paren
suffix:semicolon
macro_line|#endif __KERNEL_
macro_line|#endif /* ndef ASM */
macro_line|#endif /* NCR5380_H */
eof
