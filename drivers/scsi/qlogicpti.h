multiline_comment|/* qlogicpti.h: Performance Technologies QlogicISP sbus card defines.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caipfs.rutgers.edu)&n; */
macro_line|#ifndef _QLOGICPTI_H
DECL|macro|_QLOGICPTI_H
mdefine_line|#define _QLOGICPTI_H
DECL|struct|qlogicpti_regs
r_struct
id|qlogicpti_regs
(brace
multiline_comment|/* SBUS control registers. */
DECL|member|sbus_idlow
r_volatile
r_int
r_int
id|sbus_idlow
suffix:semicolon
multiline_comment|/* SBUS ID, low bytes             */
DECL|member|sbus_idhi
r_volatile
r_int
r_int
id|sbus_idhi
suffix:semicolon
multiline_comment|/* SBUS ID, high bytes            */
DECL|member|sbus_cfg0
r_volatile
r_int
r_int
id|sbus_cfg0
suffix:semicolon
multiline_comment|/* SBUS Config reg zero           */
DECL|member|sbus_cfg1
r_volatile
r_int
r_int
id|sbus_cfg1
suffix:semicolon
multiline_comment|/* SBUS Config reg one            */
DECL|member|sbus_ctrl
r_volatile
r_int
r_int
id|sbus_ctrl
suffix:semicolon
multiline_comment|/* SBUS Control reg               */
DECL|member|sbus_stat
r_volatile
r_int
r_int
id|sbus_stat
suffix:semicolon
multiline_comment|/* SBUS Status reg                */
DECL|member|sbus_semaphore
r_volatile
r_int
r_int
id|sbus_semaphore
suffix:semicolon
multiline_comment|/* SBUS Semaphore, p/v this...    */
DECL|member|_unused0
r_int
r_char
id|_unused0
(braket
l_int|18
)braket
suffix:semicolon
multiline_comment|/* Reserved...                    */
multiline_comment|/* Command DVMA control registers. */
DECL|member|cmd_dma_cfg
r_volatile
r_int
r_int
id|cmd_dma_cfg
suffix:semicolon
multiline_comment|/* CMD DVMA Config reg            */
DECL|member|cmd_dma_ctrl
r_volatile
r_int
r_int
id|cmd_dma_ctrl
suffix:semicolon
multiline_comment|/* CMD DVMA Control reg           */
DECL|member|cmd_dma_stat
r_volatile
r_int
r_int
id|cmd_dma_stat
suffix:semicolon
multiline_comment|/* CMD DVMA Status reg            */
DECL|member|cmd_dma_fstat
r_volatile
r_int
r_int
id|cmd_dma_fstat
suffix:semicolon
multiline_comment|/* CMD DVMA FIFO Status reg       */
DECL|member|cmd_dma_cnt
r_volatile
r_int
r_int
id|cmd_dma_cnt
suffix:semicolon
multiline_comment|/* CMD DVMA Counter reg           */
DECL|member|_unused1
r_int
r_int
id|_unused1
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|cmd_dma_alow
r_volatile
r_int
r_int
id|cmd_dma_alow
suffix:semicolon
multiline_comment|/* CMD DVMA Address low bytes     */
DECL|member|cmd_dma_ahi
r_volatile
r_int
r_int
id|cmd_dma_ahi
suffix:semicolon
multiline_comment|/* CMD DVMA Address high bytes    */
DECL|member|_unused2
r_int
r_char
id|_unused2
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Reserved...                    */
multiline_comment|/* Data DVMA control registers. */
DECL|member|data_dma_cfg
r_volatile
r_int
r_int
id|data_dma_cfg
suffix:semicolon
multiline_comment|/* DATA DVMA Config reg           */
DECL|member|data_dma_ctrl
r_volatile
r_int
r_int
id|data_dma_ctrl
suffix:semicolon
multiline_comment|/* DATA DVMA Control reg          */
DECL|member|data_dma_stat
r_volatile
r_int
r_int
id|data_dma_stat
suffix:semicolon
multiline_comment|/* DATA DVMA Status reg           */
DECL|member|data_dma_fstat
r_volatile
r_int
r_int
id|data_dma_fstat
suffix:semicolon
multiline_comment|/* DATA DVMA FIFO Status reg      */
DECL|member|data_dma_clo
r_volatile
r_int
r_int
id|data_dma_clo
suffix:semicolon
multiline_comment|/* DATA DVMA Counter low bytes    */
DECL|member|data_dma_chi
r_volatile
r_int
r_int
id|data_dma_chi
suffix:semicolon
multiline_comment|/* DATA DVMA Counter high bytes   */
DECL|member|data_dma_alow
r_volatile
r_int
r_int
id|data_dma_alow
suffix:semicolon
multiline_comment|/* DATA DVMA Address low bytes    */
DECL|member|data_dma_ahi
r_volatile
r_int
r_int
id|data_dma_ahi
suffix:semicolon
multiline_comment|/* DATA DVMA Address high bytes   */
DECL|member|_unused3
r_int
r_char
id|_unused3
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Reserved...                    */
multiline_comment|/* Data FIFO registers. */
DECL|member|fcmd
r_volatile
r_int
r_int
id|fcmd
suffix:semicolon
multiline_comment|/* FIFO Command port              */
DECL|member|fdata
r_volatile
r_int
r_int
id|fdata
suffix:semicolon
multiline_comment|/* FIFO Data port                 */
DECL|member|_unused4
r_int
r_char
id|_unused4
(braket
l_int|28
)braket
suffix:semicolon
multiline_comment|/* Reserved...                    */
multiline_comment|/* Mailboxen. */
DECL|member|mbox0
r_volatile
r_int
r_int
id|mbox0
suffix:semicolon
multiline_comment|/* MailBOX 0                      */
DECL|member|mbox1
r_volatile
r_int
r_int
id|mbox1
suffix:semicolon
multiline_comment|/* MailBOX 1                      */
DECL|member|mbox2
r_volatile
r_int
r_int
id|mbox2
suffix:semicolon
multiline_comment|/* MailBOX 2                      */
DECL|member|mbox3
r_volatile
r_int
r_int
id|mbox3
suffix:semicolon
multiline_comment|/* MailBOX 3                      */
DECL|member|mbox4
r_volatile
r_int
r_int
id|mbox4
suffix:semicolon
multiline_comment|/* MailBOX 4                      */
DECL|member|mbox5
r_volatile
r_int
r_int
id|mbox5
suffix:semicolon
multiline_comment|/* MailBOX 5                      */
DECL|member|_unused5
r_int
r_char
id|_unused5
(braket
l_int|372
)braket
suffix:semicolon
multiline_comment|/* Reserved...                    */
multiline_comment|/* Scsi processor registers. */
DECL|member|cpu_id
r_volatile
r_int
r_int
id|cpu_id
suffix:semicolon
multiline_comment|/* PART ID                        */
DECL|member|cpu_cfg1
r_volatile
r_int
r_int
id|cpu_cfg1
suffix:semicolon
multiline_comment|/* Config reg 1                   */
DECL|member|cpu_cfg2
r_volatile
r_int
r_int
id|cpu_cfg2
suffix:semicolon
multiline_comment|/* Config reg 2                   */
DECL|member|cpu_cfg3
r_volatile
r_int
r_int
id|cpu_cfg3
suffix:semicolon
multiline_comment|/* Config reg 3                   */
DECL|member|_unused6
r_int
r_char
id|_unused6
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|cpu_pc
r_volatile
r_int
r_int
id|cpu_pc
suffix:semicolon
multiline_comment|/* Program Counter                */
DECL|member|_unused7
r_int
r_int
id|_unused7
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|cpu_rpc
r_volatile
r_int
r_int
id|cpu_rpc
suffix:semicolon
multiline_comment|/* Return Program Counter         */
DECL|member|_unused8
r_int
r_int
id|_unused8
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|cpu_cmd
r_volatile
r_int
r_int
id|cpu_cmd
suffix:semicolon
multiline_comment|/* Command                        */
DECL|member|_unused9
r_int
r_int
id|_unused9
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|cpu_irq
r_volatile
r_int
r_int
id|cpu_irq
suffix:semicolon
multiline_comment|/* IRQ status                     */
DECL|member|_unused10
r_int
r_int
id|_unused10
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|cpu_seq
r_volatile
r_int
r_int
id|cpu_seq
suffix:semicolon
multiline_comment|/* Sequence reg                   */
DECL|member|cpu_gerr
r_volatile
r_int
r_int
id|cpu_gerr
suffix:semicolon
multiline_comment|/* Gross Error reg (ESP lineage?) */
DECL|member|cpu_exc
r_volatile
r_int
r_int
id|cpu_exc
suffix:semicolon
multiline_comment|/* Enable Exception reg           */
DECL|member|_unused11
r_int
r_int
id|_unused11
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|cpu_oride
r_volatile
r_int
r_int
id|cpu_oride
suffix:semicolon
multiline_comment|/* Override reg                   */
DECL|member|_unused12
r_int
r_int
id|_unused12
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|cpu_lbase
r_volatile
r_int
r_int
id|cpu_lbase
suffix:semicolon
multiline_comment|/* Literal Base reg               */
DECL|member|_unused13
r_int
r_int
id|_unused13
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|cpu_uflags
r_volatile
r_int
r_int
id|cpu_uflags
suffix:semicolon
multiline_comment|/* User Flags reg                 */
DECL|member|_unused14
r_int
r_int
id|_unused14
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|cpu_uexc
r_volatile
r_int
r_int
id|cpu_uexc
suffix:semicolon
multiline_comment|/* User Exception reg             */
DECL|member|_unused15
r_int
r_int
id|_unused15
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|cpu_bkpt
r_volatile
r_int
r_int
id|cpu_bkpt
suffix:semicolon
multiline_comment|/* Breakpoint reg                 */
DECL|member|_unused16
r_int
r_int
id|_unused16
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|cpu_sid
r_volatile
r_int
r_int
id|cpu_sid
suffix:semicolon
multiline_comment|/* SCSI ID reg                    */
DECL|member|cpu_dcfg1
r_volatile
r_int
r_int
id|cpu_dcfg1
suffix:semicolon
multiline_comment|/* Device Config 1                */
DECL|member|cpu_dcfg2
r_volatile
r_int
r_int
id|cpu_dcfg2
suffix:semicolon
multiline_comment|/* Device Config 2                */
DECL|member|_unused17
r_int
r_int
id|_unused17
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|cpu_pptr
r_volatile
r_int
r_int
id|cpu_pptr
suffix:semicolon
multiline_comment|/* Phase Pointer                  */
DECL|member|_unused18
r_int
r_int
id|_unused18
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|cpu_bptr
r_volatile
r_int
r_int
id|cpu_bptr
suffix:semicolon
multiline_comment|/* Buffer Pointer                 */
DECL|member|_unused19
r_int
r_int
id|_unused19
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|cpu_bcnt
r_volatile
r_int
r_int
id|cpu_bcnt
suffix:semicolon
multiline_comment|/* Buffer Counter                 */
DECL|member|cpu_buf
r_volatile
r_int
r_int
id|cpu_buf
suffix:semicolon
multiline_comment|/* Buffer itself                  */
DECL|member|cpu_bbyte
r_volatile
r_int
r_int
id|cpu_bbyte
suffix:semicolon
multiline_comment|/* Buffer Byte                    */
DECL|member|cpu_bword
r_volatile
r_int
r_int
id|cpu_bword
suffix:semicolon
multiline_comment|/* Buffer Word                    */
DECL|member|_unused20
r_int
r_int
id|_unused20
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|cpu_fifo
r_volatile
r_int
r_int
id|cpu_fifo
suffix:semicolon
multiline_comment|/* FIFO                           */
DECL|member|cpu_fstat
r_volatile
r_int
r_int
id|cpu_fstat
suffix:semicolon
multiline_comment|/* FIFO Status                    */
DECL|member|cpu_ftop
r_volatile
r_int
r_int
id|cpu_ftop
suffix:semicolon
multiline_comment|/* Top of FIFO                    */
DECL|member|cpu_fbottom
r_volatile
r_int
r_int
id|cpu_fbottom
suffix:semicolon
multiline_comment|/* Bottom of FIFO                 */
DECL|member|_unused21
r_int
r_int
id|_unused21
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|cpu_treg
r_volatile
r_int
r_int
id|cpu_treg
suffix:semicolon
multiline_comment|/* Transfer reg                   */
DECL|member|_unused22
r_int
r_int
id|_unused22
suffix:semicolon
multiline_comment|/* Reserved...                    */
DECL|member|cpu_clo
r_volatile
r_int
r_int
id|cpu_clo
suffix:semicolon
multiline_comment|/* Transfer Count low bytes       */
DECL|member|cpu_chi
r_volatile
r_int
r_int
id|cpu_chi
suffix:semicolon
multiline_comment|/* Transfer Count high bytes      */
DECL|member|cpu_cntlo
r_volatile
r_int
r_int
id|cpu_cntlo
suffix:semicolon
multiline_comment|/* Transfer Counter low bytes     */
DECL|member|cpu_cnthi
r_volatile
r_int
r_int
id|cpu_cnthi
suffix:semicolon
multiline_comment|/* Transfer Counter low bytes     */
DECL|member|cpu_adata
r_volatile
r_int
r_int
id|cpu_adata
suffix:semicolon
multiline_comment|/* Arbitration Data               */
DECL|member|cpu_pctrl
r_volatile
r_int
r_int
id|cpu_pctrl
suffix:semicolon
multiline_comment|/* Pin Control                    */
DECL|member|cpu_pdata
r_volatile
r_int
r_int
id|cpu_pdata
suffix:semicolon
multiline_comment|/* Pin Data                       */
DECL|member|cpu_pdiff
r_volatile
r_int
r_int
id|cpu_pdiff
suffix:semicolon
multiline_comment|/* Differential Pins              */
DECL|member|_unused23
r_int
r_char
id|_unused23
(braket
l_int|392
)braket
suffix:semicolon
multiline_comment|/* Reserved...                    */
multiline_comment|/* RISC processor registers. */
DECL|member|risc_a
r_volatile
r_int
r_int
id|risc_a
suffix:semicolon
multiline_comment|/* Accumulator                    */
DECL|member|risc_r
r_volatile
r_int
r_int
id|risc_r
(braket
l_int|15
)braket
suffix:semicolon
multiline_comment|/* General Purpose Registers      */
DECL|member|risc_psr
r_volatile
r_int
r_int
id|risc_psr
suffix:semicolon
multiline_comment|/* Processor Status Register      */
DECL|member|risc_ivec
r_volatile
r_int
r_int
id|risc_ivec
suffix:semicolon
multiline_comment|/* Interrupt Vector               */
DECL|member|risc_pcr
r_volatile
r_int
r_int
id|risc_pcr
suffix:semicolon
multiline_comment|/* Processor Control Register     */
DECL|member|risc_raddr0
r_volatile
r_int
r_int
id|risc_raddr0
suffix:semicolon
multiline_comment|/* RAM Addr reg 0                 */
DECL|member|risc_raddr1
r_volatile
r_int
r_int
id|risc_raddr1
suffix:semicolon
multiline_comment|/* RAM Addr reg 1                 */
DECL|member|risc_lcr
r_volatile
r_int
r_int
id|risc_lcr
suffix:semicolon
multiline_comment|/* Loop Counter reg               */
DECL|member|risc_pc
r_volatile
r_int
r_int
id|risc_pc
suffix:semicolon
multiline_comment|/* Program Counter                */
DECL|member|risc_mtreg
r_volatile
r_int
r_int
id|risc_mtreg
suffix:semicolon
multiline_comment|/* Memory Timing reg              */
DECL|member|risc_embreg
r_volatile
r_int
r_int
id|risc_embreg
suffix:semicolon
multiline_comment|/* External Memory Boundry reg    */
DECL|member|risc_sp
r_volatile
r_int
r_int
id|risc_sp
suffix:semicolon
multiline_comment|/* Stack Pointer                  */
DECL|member|risc_hrev
r_volatile
r_int
r_int
id|risc_hrev
suffix:semicolon
multiline_comment|/* Hardware Revision              */
DECL|member|_unused24
r_int
r_char
id|_unused24
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* Reserved...                    */
multiline_comment|/* Generic control/command registers. */
DECL|member|hcctrl
r_volatile
r_int
r_int
id|hcctrl
suffix:semicolon
multiline_comment|/* Host cmd/control reg           */
DECL|member|pbkpt0
r_volatile
r_int
r_int
id|pbkpt0
suffix:semicolon
multiline_comment|/* Processor Breakpoint 0         */
DECL|member|pbkpt1
r_volatile
r_int
r_int
id|pbkpt1
suffix:semicolon
multiline_comment|/* Processor Breakpoint 1         */
DECL|member|tcntrl
r_volatile
r_int
r_int
id|tcntrl
suffix:semicolon
multiline_comment|/* Test Control reg               */
DECL|member|tmreg
r_volatile
r_int
r_int
id|tmreg
suffix:semicolon
multiline_comment|/* Test Mode reg                  */
)brace
suffix:semicolon
DECL|macro|MAX_TARGETS
mdefine_line|#define MAX_TARGETS&t;16
DECL|macro|MAX_LUNS
mdefine_line|#define MAX_LUNS&t;8
multiline_comment|/* With the qlogic interface, every queue slot can hold a SCSI&n; * command with up to 4 scatter/gather entries.  If we need more&n; * than 4 entries, continuation entries can be used that hold&n; * another 7 entries each.  Unlike for other drivers, this means&n; * that the maximum number of scatter/gather entries we can&n; * support at any given time is a function of the number of queue&n; * slots available.  That is, host-&gt;can_queue and host-&gt;sg_tablesize&n; * are dynamic and _not_ independent.  This all works fine because&n; * requests are queued serially and the scatter/gather limit is&n; * determined for each queue request anew.&n; */
DECL|macro|QLOGICISP_REQ_QUEUE_LEN
mdefine_line|#define QLOGICISP_REQ_QUEUE_LEN&t;255&t;/* must be power of two - 1 */
DECL|macro|QLOGICISP_MAX_SG
mdefine_line|#define QLOGICISP_MAX_SG(ql)&t;(4 + ((ql) &gt; 0) ? 7*((ql) - 1) : 0)
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL (0)
macro_line|#endif
r_int
id|qlogicpti_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|qlogicpti_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|qlogicpti_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|qlogicpti_queuecommand
c_func
(paren
id|Scsi_Cmnd
op_star
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
r_int
id|qlogicpti_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|qlogicpti_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
id|proc_scsi_qlogicpti
suffix:semicolon
multiline_comment|/* mailbox command complete status codes */
DECL|macro|MBOX_COMMAND_COMPLETE
mdefine_line|#define MBOX_COMMAND_COMPLETE&t;&t;0x4000
DECL|macro|INVALID_COMMAND
mdefine_line|#define INVALID_COMMAND&t;&t;&t;0x4001
DECL|macro|HOST_INTERFACE_ERROR
mdefine_line|#define HOST_INTERFACE_ERROR&t;&t;0x4002
DECL|macro|TEST_FAILED
mdefine_line|#define TEST_FAILED&t;&t;&t;0x4003
DECL|macro|COMMAND_ERROR
mdefine_line|#define COMMAND_ERROR&t;&t;&t;0x4005
DECL|macro|COMMAND_PARAM_ERROR
mdefine_line|#define COMMAND_PARAM_ERROR&t;&t;0x4006
multiline_comment|/* async event status codes */
DECL|macro|ASYNC_SCSI_BUS_RESET
mdefine_line|#define ASYNC_SCSI_BUS_RESET&t;&t;0x8001
DECL|macro|SYSTEM_ERROR
mdefine_line|#define SYSTEM_ERROR&t;&t;&t;0x8002
DECL|macro|REQUEST_TRANSFER_ERROR
mdefine_line|#define REQUEST_TRANSFER_ERROR&t;&t;0x8003
DECL|macro|RESPONSE_TRANSFER_ERROR
mdefine_line|#define RESPONSE_TRANSFER_ERROR&t;&t;0x8004
DECL|macro|REQUEST_QUEUE_WAKEUP
mdefine_line|#define REQUEST_QUEUE_WAKEUP&t;&t;0x8005
DECL|macro|EXECUTION_TIMEOUT_RESET
mdefine_line|#define EXECUTION_TIMEOUT_RESET&t;&t;0x8006
multiline_comment|/* Am I fucking pedantic or what? */
DECL|struct|Entry_header
r_struct
id|Entry_header
(brace
macro_line|#ifdef __BIG_ENDIAN
DECL|member|entry_cnt
id|u_char
id|entry_cnt
suffix:semicolon
DECL|member|entry_type
id|u_char
id|entry_type
suffix:semicolon
DECL|member|flags
id|u_char
id|flags
suffix:semicolon
DECL|member|sys_def_1
id|u_char
id|sys_def_1
suffix:semicolon
macro_line|#else /* __LITTLE_ENDIAN */
id|u_char
id|entry_type
suffix:semicolon
id|u_char
id|entry_cnt
suffix:semicolon
id|u_char
id|sys_def_1
suffix:semicolon
id|u_char
id|flags
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* entry header type commands */
DECL|macro|ENTRY_COMMAND
mdefine_line|#define ENTRY_COMMAND&t;&t;1
DECL|macro|ENTRY_CONTINUATION
mdefine_line|#define ENTRY_CONTINUATION&t;2
DECL|macro|ENTRY_STATUS
mdefine_line|#define ENTRY_STATUS&t;&t;3
DECL|macro|ENTRY_MARKER
mdefine_line|#define ENTRY_MARKER&t;&t;4
DECL|macro|ENTRY_EXTENDED_COMMAND
mdefine_line|#define ENTRY_EXTENDED_COMMAND&t;5
multiline_comment|/* entry header flag definitions */
DECL|macro|EFLAG_CONTINUATION
mdefine_line|#define EFLAG_CONTINUATION&t;1
DECL|macro|EFLAG_BUSY
mdefine_line|#define EFLAG_BUSY&t;&t;2
DECL|macro|EFLAG_BAD_HEADER
mdefine_line|#define EFLAG_BAD_HEADER&t;4
DECL|macro|EFLAG_BAD_PAYLOAD
mdefine_line|#define EFLAG_BAD_PAYLOAD&t;8
DECL|struct|dataseg
r_struct
id|dataseg
(brace
DECL|member|d_base
id|u_int
id|d_base
suffix:semicolon
DECL|member|d_count
id|u_int
id|d_count
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|Command_Entry
r_struct
id|Command_Entry
(brace
DECL|member|hdr
r_struct
id|Entry_header
id|hdr
suffix:semicolon
DECL|member|handle
id|u_int
id|handle
suffix:semicolon
macro_line|#ifdef __BIG_ENDIAN
DECL|member|target_id
id|u_char
id|target_id
suffix:semicolon
DECL|member|target_lun
id|u_char
id|target_lun
suffix:semicolon
macro_line|#else /* __LITTLE_ENDIAN */
DECL|member|target_lun
id|u_char
id|target_lun
suffix:semicolon
DECL|member|target_id
id|u_char
id|target_id
suffix:semicolon
macro_line|#endif
DECL|member|cdb_length
id|u_short
id|cdb_length
suffix:semicolon
DECL|member|control_flags
id|u_short
id|control_flags
suffix:semicolon
DECL|member|rsvd
id|u_short
id|rsvd
suffix:semicolon
DECL|member|time_out
id|u_short
id|time_out
suffix:semicolon
DECL|member|segment_cnt
id|u_short
id|segment_cnt
suffix:semicolon
DECL|member|cdb
id|u_char
id|cdb
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|dataseg
r_struct
id|dataseg
id|dataseg
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* command entry control flag definitions */
DECL|macro|CFLAG_NODISC
mdefine_line|#define CFLAG_NODISC&t;&t;0x01
DECL|macro|CFLAG_HEAD_TAG
mdefine_line|#define CFLAG_HEAD_TAG&t;&t;0x02
DECL|macro|CFLAG_ORDERED_TAG
mdefine_line|#define CFLAG_ORDERED_TAG&t;0x04
DECL|macro|CFLAG_SIMPLE_TAG
mdefine_line|#define CFLAG_SIMPLE_TAG&t;0x08
DECL|macro|CFLAG_TAR_RTN
mdefine_line|#define CFLAG_TAR_RTN&t;&t;0x10
DECL|macro|CFLAG_READ
mdefine_line|#define CFLAG_READ&t;&t;0x20
DECL|macro|CFLAG_WRITE
mdefine_line|#define CFLAG_WRITE&t;&t;0x40
DECL|struct|Ext_Command_Entry
r_struct
id|Ext_Command_Entry
(brace
DECL|member|hdr
r_struct
id|Entry_header
id|hdr
suffix:semicolon
DECL|member|handle
id|u_int
id|handle
suffix:semicolon
macro_line|#ifdef __BIG_ENDIAN
DECL|member|target_id
id|u_char
id|target_id
suffix:semicolon
DECL|member|target_lun
id|u_char
id|target_lun
suffix:semicolon
macro_line|#else /* __LITTLE_ENDIAN */
DECL|member|target_lun
id|u_char
id|target_lun
suffix:semicolon
DECL|member|target_id
id|u_char
id|target_id
suffix:semicolon
macro_line|#endif
DECL|member|cdb_length
id|u_short
id|cdb_length
suffix:semicolon
DECL|member|control_flags
id|u_short
id|control_flags
suffix:semicolon
DECL|member|rsvd
id|u_short
id|rsvd
suffix:semicolon
DECL|member|time_out
id|u_short
id|time_out
suffix:semicolon
DECL|member|segment_cnt
id|u_short
id|segment_cnt
suffix:semicolon
DECL|member|cdb
id|u_char
id|cdb
(braket
l_int|44
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|Continuation_Entry
r_struct
id|Continuation_Entry
(brace
DECL|member|hdr
r_struct
id|Entry_header
id|hdr
suffix:semicolon
DECL|member|reserved
id|u_int
id|reserved
suffix:semicolon
DECL|member|dataseg
r_struct
id|dataseg
id|dataseg
(braket
l_int|7
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|Marker_Entry
r_struct
id|Marker_Entry
(brace
DECL|member|hdr
r_struct
id|Entry_header
id|hdr
suffix:semicolon
DECL|member|reserved
id|u_int
id|reserved
suffix:semicolon
macro_line|#ifdef __BIG_ENDIAN
DECL|member|target_id
id|u_char
id|target_id
suffix:semicolon
DECL|member|target_lun
id|u_char
id|target_lun
suffix:semicolon
macro_line|#else /* __LITTLE_ENDIAN */
DECL|member|target_lun
id|u_char
id|target_lun
suffix:semicolon
DECL|member|target_id
id|u_char
id|target_id
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __BIG_ENDIAN
DECL|member|rsvd
id|u_char
id|rsvd
suffix:semicolon
DECL|member|modifier
id|u_char
id|modifier
suffix:semicolon
macro_line|#else /* __LITTLE_ENDIAN */
DECL|member|modifier
id|u_char
id|modifier
suffix:semicolon
DECL|member|rsvd
id|u_char
id|rsvd
suffix:semicolon
macro_line|#endif
DECL|member|rsvds
id|u_char
id|rsvds
(braket
l_int|52
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* marker entry modifier definitions */
DECL|macro|SYNC_DEVICE
mdefine_line|#define SYNC_DEVICE&t;0
DECL|macro|SYNC_TARGET
mdefine_line|#define SYNC_TARGET&t;1
DECL|macro|SYNC_ALL
mdefine_line|#define SYNC_ALL&t;2
DECL|struct|Status_Entry
r_struct
id|Status_Entry
(brace
DECL|member|hdr
r_struct
id|Entry_header
id|hdr
suffix:semicolon
DECL|member|handle
id|u_int
id|handle
suffix:semicolon
DECL|member|scsi_status
id|u_short
id|scsi_status
suffix:semicolon
DECL|member|completion_status
id|u_short
id|completion_status
suffix:semicolon
DECL|member|state_flags
id|u_short
id|state_flags
suffix:semicolon
DECL|member|status_flags
id|u_short
id|status_flags
suffix:semicolon
DECL|member|time
id|u_short
id|time
suffix:semicolon
DECL|member|req_sense_len
id|u_short
id|req_sense_len
suffix:semicolon
DECL|member|residual
id|u_int
id|residual
suffix:semicolon
DECL|member|rsvd
id|u_char
id|rsvd
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|req_sense_data
id|u_char
id|req_sense_data
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* status entry completion status definitions */
DECL|macro|CS_COMPLETE
mdefine_line|#define CS_COMPLETE&t;&t;&t;0x0000
DECL|macro|CS_INCOMPLETE
mdefine_line|#define CS_INCOMPLETE&t;&t;&t;0x0001
DECL|macro|CS_DMA_ERROR
mdefine_line|#define CS_DMA_ERROR&t;&t;&t;0x0002
DECL|macro|CS_TRANSPORT_ERROR
mdefine_line|#define CS_TRANSPORT_ERROR&t;&t;0x0003
DECL|macro|CS_RESET_OCCURRED
mdefine_line|#define CS_RESET_OCCURRED&t;&t;0x0004
DECL|macro|CS_ABORTED
mdefine_line|#define CS_ABORTED&t;&t;&t;0x0005
DECL|macro|CS_TIMEOUT
mdefine_line|#define CS_TIMEOUT&t;&t;&t;0x0006
DECL|macro|CS_DATA_OVERRUN
mdefine_line|#define CS_DATA_OVERRUN&t;&t;&t;0x0007
DECL|macro|CS_COMMAND_OVERRUN
mdefine_line|#define CS_COMMAND_OVERRUN&t;&t;0x0008
DECL|macro|CS_STATUS_OVERRUN
mdefine_line|#define CS_STATUS_OVERRUN&t;&t;0x0009
DECL|macro|CS_BAD_MESSAGE
mdefine_line|#define CS_BAD_MESSAGE&t;&t;&t;0x000a
DECL|macro|CS_NO_MESSAGE_OUT
mdefine_line|#define CS_NO_MESSAGE_OUT&t;&t;0x000b
DECL|macro|CS_EXT_ID_FAILED
mdefine_line|#define CS_EXT_ID_FAILED&t;&t;0x000c
DECL|macro|CS_IDE_MSG_FAILED
mdefine_line|#define CS_IDE_MSG_FAILED&t;&t;0x000d
DECL|macro|CS_ABORT_MSG_FAILED
mdefine_line|#define CS_ABORT_MSG_FAILED&t;&t;0x000e
DECL|macro|CS_REJECT_MSG_FAILED
mdefine_line|#define CS_REJECT_MSG_FAILED&t;&t;0x000f
DECL|macro|CS_NOP_MSG_FAILED
mdefine_line|#define CS_NOP_MSG_FAILED&t;&t;0x0010
DECL|macro|CS_PARITY_ERROR_MSG_FAILED
mdefine_line|#define CS_PARITY_ERROR_MSG_FAILED&t;0x0011
DECL|macro|CS_DEVICE_RESET_MSG_FAILED
mdefine_line|#define CS_DEVICE_RESET_MSG_FAILED&t;0x0012
DECL|macro|CS_ID_MSG_FAILED
mdefine_line|#define CS_ID_MSG_FAILED&t;&t;0x0013
DECL|macro|CS_UNEXP_BUS_FREE
mdefine_line|#define CS_UNEXP_BUS_FREE&t;&t;0x0014
DECL|macro|CS_DATA_UNDERRUN
mdefine_line|#define CS_DATA_UNDERRUN&t;&t;0x0015
multiline_comment|/* status entry state flag definitions */
DECL|macro|SF_GOT_BUS
mdefine_line|#define SF_GOT_BUS&t;&t;&t;0x0100
DECL|macro|SF_GOT_TARGET
mdefine_line|#define SF_GOT_TARGET&t;&t;&t;0x0200
DECL|macro|SF_SENT_CDB
mdefine_line|#define SF_SENT_CDB&t;&t;&t;0x0400
DECL|macro|SF_TRANSFERRED_DATA
mdefine_line|#define SF_TRANSFERRED_DATA&t;&t;0x0800
DECL|macro|SF_GOT_STATUS
mdefine_line|#define SF_GOT_STATUS&t;&t;&t;0x1000
DECL|macro|SF_GOT_SENSE
mdefine_line|#define SF_GOT_SENSE&t;&t;&t;0x2000
multiline_comment|/* status entry status flag definitions */
DECL|macro|STF_DISCONNECT
mdefine_line|#define STF_DISCONNECT&t;&t;&t;0x0001
DECL|macro|STF_SYNCHRONOUS
mdefine_line|#define STF_SYNCHRONOUS&t;&t;&t;0x0002
DECL|macro|STF_PARITY_ERROR
mdefine_line|#define STF_PARITY_ERROR&t;&t;0x0004
DECL|macro|STF_BUS_RESET
mdefine_line|#define STF_BUS_RESET&t;&t;&t;0x0008
DECL|macro|STF_DEVICE_RESET
mdefine_line|#define STF_DEVICE_RESET&t;&t;0x0010
DECL|macro|STF_ABORTED
mdefine_line|#define STF_ABORTED&t;&t;&t;0x0020
DECL|macro|STF_TIMEOUT
mdefine_line|#define STF_TIMEOUT&t;&t;&t;0x0040
DECL|macro|STF_NEGOTIATION
mdefine_line|#define STF_NEGOTIATION&t;&t;&t;0x0080
multiline_comment|/* mailbox commands */
DECL|macro|MBOX_NO_OP
mdefine_line|#define MBOX_NO_OP&t;&t;&t;0x0000
DECL|macro|MBOX_LOAD_RAM
mdefine_line|#define MBOX_LOAD_RAM&t;&t;&t;0x0001
DECL|macro|MBOX_EXEC_FIRMWARE
mdefine_line|#define MBOX_EXEC_FIRMWARE&t;&t;0x0002
DECL|macro|MBOX_DUMP_RAM
mdefine_line|#define MBOX_DUMP_RAM&t;&t;&t;0x0003
DECL|macro|MBOX_WRITE_RAM_WORD
mdefine_line|#define MBOX_WRITE_RAM_WORD&t;&t;0x0004
DECL|macro|MBOX_READ_RAM_WORD
mdefine_line|#define MBOX_READ_RAM_WORD&t;&t;0x0005
DECL|macro|MBOX_MAILBOX_REG_TEST
mdefine_line|#define MBOX_MAILBOX_REG_TEST&t;&t;0x0006
DECL|macro|MBOX_VERIFY_CHECKSUM
mdefine_line|#define MBOX_VERIFY_CHECKSUM&t;&t;0x0007
DECL|macro|MBOX_ABOUT_FIRMWARE
mdefine_line|#define MBOX_ABOUT_FIRMWARE&t;&t;0x0008
DECL|macro|MBOX_CHECK_FIRMWARE
mdefine_line|#define MBOX_CHECK_FIRMWARE&t;&t;0x000e
DECL|macro|MBOX_INIT_REQ_QUEUE
mdefine_line|#define MBOX_INIT_REQ_QUEUE&t;&t;0x0010
DECL|macro|MBOX_INIT_RES_QUEUE
mdefine_line|#define MBOX_INIT_RES_QUEUE&t;&t;0x0011
DECL|macro|MBOX_EXECUTE_IOCB
mdefine_line|#define MBOX_EXECUTE_IOCB&t;&t;0x0012
DECL|macro|MBOX_WAKE_UP
mdefine_line|#define MBOX_WAKE_UP&t;&t;&t;0x0013
DECL|macro|MBOX_STOP_FIRMWARE
mdefine_line|#define MBOX_STOP_FIRMWARE&t;&t;0x0014
DECL|macro|MBOX_ABORT
mdefine_line|#define MBOX_ABORT&t;&t;&t;0x0015
DECL|macro|MBOX_ABORT_DEVICE
mdefine_line|#define MBOX_ABORT_DEVICE&t;&t;0x0016
DECL|macro|MBOX_ABORT_TARGET
mdefine_line|#define MBOX_ABORT_TARGET&t;&t;0x0017
DECL|macro|MBOX_BUS_RESET
mdefine_line|#define MBOX_BUS_RESET&t;&t;&t;0x0018
DECL|macro|MBOX_STOP_QUEUE
mdefine_line|#define MBOX_STOP_QUEUE&t;&t;&t;0x0019
DECL|macro|MBOX_START_QUEUE
mdefine_line|#define MBOX_START_QUEUE&t;&t;0x001a
DECL|macro|MBOX_SINGLE_STEP_QUEUE
mdefine_line|#define MBOX_SINGLE_STEP_QUEUE&t;&t;0x001b
DECL|macro|MBOX_ABORT_QUEUE
mdefine_line|#define MBOX_ABORT_QUEUE&t;&t;0x001c
DECL|macro|MBOX_GET_DEV_QUEUE_STATUS
mdefine_line|#define MBOX_GET_DEV_QUEUE_STATUS&t;0x001d
DECL|macro|MBOX_GET_FIRMWARE_STATUS
mdefine_line|#define MBOX_GET_FIRMWARE_STATUS&t;0x001f
DECL|macro|MBOX_GET_INIT_SCSI_ID
mdefine_line|#define MBOX_GET_INIT_SCSI_ID&t;&t;0x0020
DECL|macro|MBOX_GET_SELECT_TIMEOUT
mdefine_line|#define MBOX_GET_SELECT_TIMEOUT&t;&t;0x0021
DECL|macro|MBOX_GET_RETRY_COUNT
mdefine_line|#define MBOX_GET_RETRY_COUNT&t;&t;0x0022
DECL|macro|MBOX_GET_TAG_AGE_LIMIT
mdefine_line|#define MBOX_GET_TAG_AGE_LIMIT&t;&t;0x0023
DECL|macro|MBOX_GET_CLOCK_RATE
mdefine_line|#define MBOX_GET_CLOCK_RATE&t;&t;0x0024
DECL|macro|MBOX_GET_ACT_NEG_STATE
mdefine_line|#define MBOX_GET_ACT_NEG_STATE&t;&t;0x0025
DECL|macro|MBOX_GET_ASYNC_DATA_SETUP_TIME
mdefine_line|#define MBOX_GET_ASYNC_DATA_SETUP_TIME&t;0x0026
DECL|macro|MBOX_GET_SBUS_PARAMS
mdefine_line|#define MBOX_GET_SBUS_PARAMS&t;&t;0x0027
DECL|macro|MBOX_GET_TARGET_PARAMS
mdefine_line|#define MBOX_GET_TARGET_PARAMS&t;&t;0x0028
DECL|macro|MBOX_GET_DEV_QUEUE_PARAMS
mdefine_line|#define MBOX_GET_DEV_QUEUE_PARAMS&t;0x0029
DECL|macro|MBOX_SET_INIT_SCSI_ID
mdefine_line|#define MBOX_SET_INIT_SCSI_ID&t;&t;0x0030
DECL|macro|MBOX_SET_SELECT_TIMEOUT
mdefine_line|#define MBOX_SET_SELECT_TIMEOUT&t;&t;0x0031
DECL|macro|MBOX_SET_RETRY_COUNT
mdefine_line|#define MBOX_SET_RETRY_COUNT&t;&t;0x0032
DECL|macro|MBOX_SET_TAG_AGE_LIMIT
mdefine_line|#define MBOX_SET_TAG_AGE_LIMIT&t;&t;0x0033
DECL|macro|MBOX_SET_CLOCK_RATE
mdefine_line|#define MBOX_SET_CLOCK_RATE&t;&t;0x0034
DECL|macro|MBOX_SET_ACTIVE_NEG_STATE
mdefine_line|#define MBOX_SET_ACTIVE_NEG_STATE&t;0x0035
DECL|macro|MBOX_SET_ASYNC_DATA_SETUP_TIME
mdefine_line|#define MBOX_SET_ASYNC_DATA_SETUP_TIME&t;0x0036
DECL|macro|MBOX_SET_SBUS_CONTROL_PARAMS
mdefine_line|#define MBOX_SET_SBUS_CONTROL_PARAMS&t;0x0037
DECL|macro|MBOX_SET_TARGET_PARAMS
mdefine_line|#define MBOX_SET_TARGET_PARAMS&t;&t;0x0038
DECL|macro|MBOX_SET_DEV_QUEUE_PARAMS
mdefine_line|#define MBOX_SET_DEV_QUEUE_PARAMS&t;0x0039
DECL|struct|host_param
r_struct
id|host_param
(brace
DECL|member|initiator_scsi_id
id|u_short
id|initiator_scsi_id
suffix:semicolon
DECL|member|bus_reset_delay
id|u_short
id|bus_reset_delay
suffix:semicolon
DECL|member|retry_count
id|u_short
id|retry_count
suffix:semicolon
DECL|member|retry_delay
id|u_short
id|retry_delay
suffix:semicolon
DECL|member|async_data_setup_time
id|u_short
id|async_data_setup_time
suffix:semicolon
DECL|member|req_ack_active_negation
id|u_short
id|req_ack_active_negation
suffix:semicolon
DECL|member|data_line_active_negation
id|u_short
id|data_line_active_negation
suffix:semicolon
DECL|member|data_dma_burst_enable
id|u_short
id|data_dma_burst_enable
suffix:semicolon
DECL|member|command_dma_burst_enable
id|u_short
id|command_dma_burst_enable
suffix:semicolon
DECL|member|tag_aging
id|u_short
id|tag_aging
suffix:semicolon
DECL|member|selection_timeout
id|u_short
id|selection_timeout
suffix:semicolon
DECL|member|max_queue_depth
id|u_short
id|max_queue_depth
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Device Flags:&n; *&n; * Bit  Name&n; * ---------&n; *  7   Disconnect Privilege&n; *  6   Parity Checking&n; *  5   Wide Data Transfers&n; *  4   Synchronous Data Transfers&n; *  3   Tagged Queuing&n; *  2   Automatic Request Sense&n; *  1   Stop Queue on Check Condition&n; *  0   Renegotiate on Error&n; */
DECL|struct|dev_param
r_struct
id|dev_param
(brace
DECL|member|device_flags
id|u_short
id|device_flags
suffix:semicolon
DECL|member|execution_throttle
id|u_short
id|execution_throttle
suffix:semicolon
DECL|member|synchronous_period
id|u_short
id|synchronous_period
suffix:semicolon
DECL|member|synchronous_offset
id|u_short
id|synchronous_offset
suffix:semicolon
DECL|member|device_enable
id|u_short
id|device_enable
suffix:semicolon
DECL|member|reserved
id|u_short
id|reserved
suffix:semicolon
multiline_comment|/* pad */
)brace
suffix:semicolon
multiline_comment|/*&n; * The result queue can be quite a bit smaller since continuation entries&n; * do not show up there:&n; */
DECL|macro|RES_QUEUE_LEN
mdefine_line|#define RES_QUEUE_LEN&t;&t;255&t;/* Must be power of two - 1 */
DECL|macro|QUEUE_ENTRY_LEN
mdefine_line|#define QUEUE_ENTRY_LEN&t;&t;64
DECL|macro|NEXT_REQ_PTR
mdefine_line|#define NEXT_REQ_PTR(wheee)   (((wheee) + 1) &amp; QLOGICISP_REQ_QUEUE_LEN)
DECL|macro|NEXT_RES_PTR
mdefine_line|#define NEXT_RES_PTR(wheee)   (((wheee) + 1) &amp; RES_QUEUE_LEN)
DECL|macro|PREV_REQ_PTR
mdefine_line|#define PREV_REQ_PTR(wheee)   (((wheee) - 1) &amp; QLOGICISP_REQ_QUEUE_LEN)
DECL|macro|PREV_RES_PTR
mdefine_line|#define PREV_RES_PTR(wheee)   (((wheee) - 1) &amp; RES_QUEUE_LEN)
DECL|struct|pti_queue_entry
r_struct
id|pti_queue_entry
(brace
DECL|member|__opaque
r_char
id|__opaque
(braket
id|QUEUE_ENTRY_LEN
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Software state for the driver. */
DECL|struct|qlogicpti
r_struct
id|qlogicpti
(brace
multiline_comment|/* These are the hot elements in the cache, so they come first. */
DECL|member|next
r_struct
id|qlogicpti
op_star
id|next
suffix:semicolon
multiline_comment|/* Next active adapter        */
DECL|member|qregs
r_struct
id|qlogicpti_regs
op_star
id|qregs
suffix:semicolon
multiline_comment|/* Adapter registers          */
DECL|member|req_in_ptr
id|u_int
id|req_in_ptr
suffix:semicolon
multiline_comment|/* index of next request slot */
DECL|member|res_out_ptr
id|u_int
id|res_out_ptr
suffix:semicolon
multiline_comment|/* index of next result slot  */
DECL|member|res
r_struct
id|pti_queue_entry
op_star
id|res
suffix:semicolon
multiline_comment|/* Pointer to RESPONSE dvma   */
DECL|member|req
r_struct
id|pti_queue_entry
op_star
id|req
suffix:semicolon
multiline_comment|/* Pointer to REQUEST dvma    */
DECL|member|cmd_count
r_int
id|cmd_count
(braket
id|MAX_TARGETS
)braket
suffix:semicolon
DECL|member|tag_ages
r_int
r_int
id|tag_ages
(braket
id|MAX_TARGETS
)braket
suffix:semicolon
DECL|member|send_marker
r_int
id|send_marker
suffix:semicolon
multiline_comment|/* must we send a marker?     */
multiline_comment|/* The rest of the elements are unimportant for performance. */
DECL|member|fware_majrev
DECL|member|fware_minrev
id|u_char
id|fware_majrev
comma
id|fware_minrev
suffix:semicolon
DECL|member|qhost
r_struct
id|Scsi_Host
op_star
id|qhost
suffix:semicolon
DECL|member|qdev
r_struct
id|linux_sbus_device
op_star
id|qdev
suffix:semicolon
DECL|member|qpti_id
r_int
id|qpti_id
suffix:semicolon
DECL|member|scsi_id
r_int
id|scsi_id
suffix:semicolon
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
DECL|member|prom_name
r_char
id|prom_name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|differential
DECL|member|ultra
r_char
id|differential
comma
id|ultra
suffix:semicolon
DECL|member|bursts
r_int
r_char
id|bursts
suffix:semicolon
DECL|member|host_param
r_struct
id|host_param
id|host_param
suffix:semicolon
DECL|member|dev_param
r_struct
id|dev_param
id|dev_param
(braket
id|MAX_TARGETS
)braket
suffix:semicolon
DECL|member|sreg
r_volatile
r_int
r_char
op_star
id|sreg
suffix:semicolon
DECL|macro|SREG_TPOWER
mdefine_line|#define SREG_TPOWER               0x80   /* State of termpwr           */
DECL|macro|SREG_FUSE
mdefine_line|#define SREG_FUSE                 0x40   /* State of on board fuse     */
DECL|macro|SREG_PDISAB
mdefine_line|#define SREG_PDISAB               0x20   /* Disable state for power on */
DECL|macro|SREG_DSENSE
mdefine_line|#define SREG_DSENSE               0x10   /* Sense for differential     */
DECL|macro|SREG_IMASK
mdefine_line|#define SREG_IMASK                0x0c   /* Interrupt level            */
DECL|macro|SREG_SPMASK
mdefine_line|#define SREG_SPMASK               0x03   /* Mask for switch pack       */
DECL|member|swsreg
r_int
r_char
id|swsreg
suffix:semicolon
macro_line|#if 0
r_char
id|res
(braket
id|RES_QUEUE_LEN
op_plus
l_int|1
)braket
(braket
id|QUEUE_ENTRY_LEN
)braket
suffix:semicolon
r_char
id|req
(braket
id|QLOGICISP_REQ_QUEUE_LEN
op_plus
l_int|1
)braket
(braket
id|QUEUE_ENTRY_LEN
)braket
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* How to twiddle them bits... */
multiline_comment|/* SBUS config register zero. */
DECL|macro|SBUS_CFG0_HREVMASK
mdefine_line|#define SBUS_CFG0_HREVMASK      0x000f      /* To get the revision              */
multiline_comment|/* SBUS config register one. */
DECL|macro|SBUS_CFG1_EPAR
mdefine_line|#define SBUS_CFG1_EPAR          0x0100      /* Enable parity checking           */
DECL|macro|SBUS_CFG1_FMASK
mdefine_line|#define SBUS_CFG1_FMASK         0x00f0      /* Forth code cycle mask            */
DECL|macro|SBUS_CFG1_BENAB
mdefine_line|#define SBUS_CFG1_BENAB         0x0004      /* Burst dvma enable                */
DECL|macro|SBUS_CFG1_B64
mdefine_line|#define SBUS_CFG1_B64           0x0003      /* Enable 64byte bursts             */
DECL|macro|SBUS_CFG1_B32
mdefine_line|#define SBUS_CFG1_B32           0x0002      /* Enable 32byte bursts             */
DECL|macro|SBUS_CFG1_B16
mdefine_line|#define SBUS_CFG1_B16           0x0001      /* Enable 16byte bursts             */
DECL|macro|SBUS_CFG1_B8
mdefine_line|#define SBUS_CFG1_B8            0x0008      /* Enable 8byte bursts              */
multiline_comment|/* SBUS control register */
DECL|macro|SBUS_CTRL_EDIRQ
mdefine_line|#define SBUS_CTRL_EDIRQ         0x0020      /* Enable Data DVMA Interrupts      */
DECL|macro|SBUS_CTRL_ECIRQ
mdefine_line|#define SBUS_CTRL_ECIRQ         0x0010      /* Enable Command DVMA Interrupts   */
DECL|macro|SBUS_CTRL_ESIRQ
mdefine_line|#define SBUS_CTRL_ESIRQ         0x0008      /* Enable SCSI Processor Interrupts */
DECL|macro|SBUS_CTRL_ERIRQ
mdefine_line|#define SBUS_CTRL_ERIRQ         0x0004      /* Enable RISC Processor Interrupts */
DECL|macro|SBUS_CTRL_GENAB
mdefine_line|#define SBUS_CTRL_GENAB         0x0002      /* Global Interrupt Enable          */
DECL|macro|SBUS_CTRL_RESET
mdefine_line|#define SBUS_CTRL_RESET         0x0001      /* Soft Reset                       */
multiline_comment|/* SBUS status register */
DECL|macro|SBUS_STAT_DINT
mdefine_line|#define SBUS_STAT_DINT          0x0020      /* Data DVMA IRQ pending            */
DECL|macro|SBUS_STAT_CINT
mdefine_line|#define SBUS_STAT_CINT          0x0010      /* Command DVMA IRQ pending         */
DECL|macro|SBUS_STAT_SINT
mdefine_line|#define SBUS_STAT_SINT          0x0008      /* SCSI Processor IRQ pending       */
DECL|macro|SBUS_STAT_RINT
mdefine_line|#define SBUS_STAT_RINT          0x0004      /* RISC Processor IRQ pending       */
DECL|macro|SBUS_STAT_GINT
mdefine_line|#define SBUS_STAT_GINT          0x0002      /* Global IRQ pending               */
multiline_comment|/* SBUS semaphore register */
DECL|macro|SBUS_SEMAPHORE_STAT
mdefine_line|#define SBUS_SEMAPHORE_STAT     0x0002      /* Semaphore status bit             */
DECL|macro|SBUS_SEMAPHORE_LCK
mdefine_line|#define SBUS_SEMAPHORE_LCK      0x0001      /* Semaphore lock bit               */
multiline_comment|/* DVMA config register */
DECL|macro|DMA_CFG_DVMAENAB
mdefine_line|#define DMA_CFG_DVMAENAB        0x0008      /* Enable scsi cpu --&gt; dma data     */
DECL|macro|DMA_CFG_EIRQ
mdefine_line|#define DMA_CFG_EIRQ            0x0004      /* Enable interrupts to risc cpu    */
DECL|macro|DMA_CFG_EBURST
mdefine_line|#define DMA_CFG_EBURST          0x0002      /* Enable sbus dvma bursts          */
DECL|macro|DMA_CFG_DIRECTION
mdefine_line|#define DMA_CFG_DIRECTION       0x0001      /* DMA direction (0=fifo-&gt;ram)      */
multiline_comment|/* DVMA control register */
DECL|macro|DMA_CTRL_CSUSPEND
mdefine_line|#define DMA_CTRL_CSUSPEND       0x0010      /* DMA channel suspend              */
DECL|macro|DMA_CTRL_CCLEAR
mdefine_line|#define DMA_CTRL_CCLEAR         0x0008      /* DMA channel clear and reset      */
DECL|macro|DMA_CTRL_FCLEAR
mdefine_line|#define DMA_CTRL_FCLEAR         0x0004      /* DMA fifo clear                   */
DECL|macro|DMA_CTRL_CIRQ
mdefine_line|#define DMA_CTRL_CIRQ           0x0002      /* DMA irq clear                    */
DECL|macro|DMA_CTRL_DMASTART
mdefine_line|#define DMA_CTRL_DMASTART       0x0001      /* DMA transfer start               */
multiline_comment|/* DVMA status register */
DECL|macro|DMA_STAT_PFULL
mdefine_line|#define DMA_STAT_PFULL          0x00c0      /* Pipe full                        */
DECL|macro|DMA_STAT_PORUN
mdefine_line|#define DMA_STAT_PORUN          0x0080      /* Pipe overrun                     */
DECL|macro|DMA_STAT_PSTG1
mdefine_line|#define DMA_STAT_PSTG1          0x0040      /* Pipe has stage 1 loaded          */
DECL|macro|DMA_STAT_PEMPTY
mdefine_line|#define DMA_STAT_PEMPTY         0x0000      /* Pipe is empty                    */
DECL|macro|DMA_STAT_CSUSP
mdefine_line|#define DMA_STAT_CSUSP          0x0030      /* Channel suspended                */
DECL|macro|DMA_STAT_CTRAN
mdefine_line|#define DMA_STAT_CTRAN          0x0020      /* Channel transfer in progress     */
DECL|macro|DMA_STAT_CACTIVE
mdefine_line|#define DMA_STAT_CACTIVE        0x0010      /* Channel active                   */
DECL|macro|DMA_STAT_CIDLE
mdefine_line|#define DMA_STAT_CIDLE          0x0000      /* Channel idle                     */
DECL|macro|DMA_STAT_SPAR
mdefine_line|#define DMA_STAT_SPAR           0x0008      /* SBUS parity error                */
DECL|macro|DMA_STAT_SERR
mdefine_line|#define DMA_STAT_SERR           0x0004      /* SBUS dma error                   */
DECL|macro|DMA_STAT_TCNT
mdefine_line|#define DMA_STAT_TCNT           0x0002      /* Terminal count expired           */
DECL|macro|DMA_STAT_IRQ
mdefine_line|#define DMA_STAT_IRQ            0x0001      /* DMA interrupt                    */
multiline_comment|/* DVMA FIFO status register */
DECL|macro|DMA_FSTAT_ORUN
mdefine_line|#define DMA_FSTAT_ORUN          0x0200      /* FIFO overrun                     */
DECL|macro|DMA_FSTAT_URUN
mdefine_line|#define DMA_FSTAT_URUN          0x0100      /* FIFO underrun                    */
DECL|macro|DMA_FSTAT_CMASK
mdefine_line|#define DMA_FSTAT_CMASK         0x007f      /* FIFO count mask                  */
multiline_comment|/* SCSI processor config 1 register */
DECL|macro|CPU_CFG1_ASTIME
mdefine_line|#define CPU_CFG1_ASTIME         0xf000      /* Asynchronous setup time mask     */
DECL|macro|CPU_CFG1_STUNIT
mdefine_line|#define CPU_CFG1_STUNIT         0x0000      /* Selection time unit              */
DECL|macro|CPU_CFG1_STIMEO
mdefine_line|#define CPU_CFG1_STIMEO         0x0600      /* Selection timeout value          */
DECL|macro|CPU_CFG1_CFACT
mdefine_line|#define CPU_CFG1_CFACT          0x00e0      /* Clock factor                     */
DECL|macro|CPU_CFG1_SID
mdefine_line|#define CPU_CFG1_SID            0x000f      /* SCSI ID                          */
multiline_comment|/* SCSI processor config 2 register */
DECL|macro|CPU_CFG2_FDISAB
mdefine_line|#define CPU_CFG2_FDISAB         0x0040      /* SCSI filter disable              */
DECL|macro|CPU_CFG2_ERAPUPS
mdefine_line|#define CPU_CFG2_ERAPUPS        0x0020      /* Req/Ack pullup enable            */
DECL|macro|CPU_CFG2_EDPUPS
mdefine_line|#define CPU_CFG2_EDPUPS         0x0010      /* Data active pullup enable        */
DECL|macro|CPU_CFG2_ECAUTO
mdefine_line|#define CPU_CFG2_ECAUTO         0x0008      /* Autoload device config enable    */
DECL|macro|CPU_CFG2_ERESEL
mdefine_line|#define CPU_CFG2_ERESEL         0x0002      /* Enable reselections              */
DECL|macro|CPU_CFG2_ESEL
mdefine_line|#define CPU_CFG2_ESEL           0x0001      /* Enable selections                */
multiline_comment|/* SCSI processor interrupt register */
DECL|macro|CPU_IRQ_PERR
mdefine_line|#define CPU_IRQ_PERR            0x8000      /* Parity error                     */
DECL|macro|CPU_IRQ_GERR
mdefine_line|#define CPU_IRQ_GERR            0x4000      /* Gross error                      */
DECL|macro|CPU_IRQ_FABORT
mdefine_line|#define CPU_IRQ_FABORT          0x2000      /* Function abort                   */
DECL|macro|CPU_IRQ_CFAIL
mdefine_line|#define CPU_IRQ_CFAIL           0x1000      /* Condition failed                 */
DECL|macro|CPU_IRQ_FEMPTY
mdefine_line|#define CPU_IRQ_FEMPTY          0x0800      /* FIFO empty                       */
DECL|macro|CPU_IRQ_BCZ
mdefine_line|#define CPU_IRQ_BCZ             0x0400      /* Byte counter is zero             */
DECL|macro|CPU_IRQ_XZ
mdefine_line|#define CPU_IRQ_XZ              0x0200      /* Transfer counter is zero         */
DECL|macro|CPU_IRQ_IRQ
mdefine_line|#define CPU_IRQ_IRQ             0x0080      /* SCSI processor interrupt pending */
DECL|macro|CPU_IRQ_CRUN
mdefine_line|#define CPU_IRQ_CRUN            0x0040      /* Command is running               */
DECL|macro|CPU_IRQ_RCODE
mdefine_line|#define CPU_IRQ_RCODE           0x000f      /* Return code for interrupt        */
multiline_comment|/* SCSI processor gross error register */
DECL|macro|CPU_GERR_ONZ
mdefine_line|#define CPU_GERR_ONZ            0x0040      /* Offset not zero                  */
DECL|macro|CPU_GERR_OUF
mdefine_line|#define CPU_GERR_OUF            0x0020      /* Offset underflowed               */
DECL|macro|CPU_GERR_OOF
mdefine_line|#define CPU_GERR_OOF            0x0010      /* Offset overflowed                */
DECL|macro|CPU_GERR_FUF
mdefine_line|#define CPU_GERR_FUF            0x0008      /* FIFO underflowed                 */
DECL|macro|CPU_GERR_FOF
mdefine_line|#define CPU_GERR_FOF            0x0004      /* FIFO overflowed                  */
DECL|macro|CPU_GERR_WERR
mdefine_line|#define CPU_GERR_WERR           0x0002      /* Error on write                   */
DECL|macro|CPU_GERR_ILL
mdefine_line|#define CPU_GERR_ILL            0x0001      /* Instruction was illegal          */
multiline_comment|/* SCSI processor exception register */
DECL|macro|CPU_EXC_UZERO
mdefine_line|#define CPU_EXC_UZERO           0x8000      /* User exception zero              */
DECL|macro|CPU_EXC_UONE
mdefine_line|#define CPU_EXC_UONE            0x4000      /* User exception one               */
DECL|macro|CPU_EXC_BFREE
mdefine_line|#define CPU_EXC_BFREE           0x0200      /* Bus free                         */
DECL|macro|CPU_EXC_TATN
mdefine_line|#define CPU_EXC_TATN            0x0100      /* ATN in target mode               */
DECL|macro|CPU_EXC_RESEL
mdefine_line|#define CPU_EXC_RESEL           0x0080      /* Reselect exception               */
DECL|macro|CPU_EXC_SEL
mdefine_line|#define CPU_EXC_SEL             0x0040      /* Selection exception              */
DECL|macro|CPU_EXC_ARB
mdefine_line|#define CPU_EXC_ARB             0x0020      /* Arbitration exception            */
DECL|macro|CPU_EXC_GERR
mdefine_line|#define CPU_EXC_GERR            0x0010      /* Gross error exception            */
DECL|macro|CPU_EXC_RESET
mdefine_line|#define CPU_EXC_RESET           0x0008      /* Bus reset exception              */
multiline_comment|/* SCSI processor override register */
DECL|macro|CPU_ORIDE_ETRIG
mdefine_line|#define CPU_ORIDE_ETRIG         0x8000      /* External trigger enable          */
DECL|macro|CPU_ORIDE_STEP
mdefine_line|#define CPU_ORIDE_STEP          0x4000      /* Single step mode enable          */
DECL|macro|CPU_ORIDE_BKPT
mdefine_line|#define CPU_ORIDE_BKPT          0x2000      /* Breakpoint reg enable            */
DECL|macro|CPU_ORIDE_PWRITE
mdefine_line|#define CPU_ORIDE_PWRITE        0x1000      /* SCSI pin write enable            */
DECL|macro|CPU_ORIDE_OFORCE
mdefine_line|#define CPU_ORIDE_OFORCE        0x0800      /* Force outputs on                 */
DECL|macro|CPU_ORIDE_LBACK
mdefine_line|#define CPU_ORIDE_LBACK         0x0400      /* SCSI loopback enable             */
DECL|macro|CPU_ORIDE_PTEST
mdefine_line|#define CPU_ORIDE_PTEST         0x0200      /* Parity test enable               */
DECL|macro|CPU_ORIDE_TENAB
mdefine_line|#define CPU_ORIDE_TENAB         0x0100      /* SCSI pins tristate enable        */
DECL|macro|CPU_ORIDE_TPINS
mdefine_line|#define CPU_ORIDE_TPINS         0x0080      /* SCSI pins enable                 */
DECL|macro|CPU_ORIDE_FRESET
mdefine_line|#define CPU_ORIDE_FRESET        0x0008      /* FIFO reset                       */
DECL|macro|CPU_ORIDE_CTERM
mdefine_line|#define CPU_ORIDE_CTERM         0x0004      /* Command terminate                */
DECL|macro|CPU_ORIDE_RREG
mdefine_line|#define CPU_ORIDE_RREG          0x0002      /* Reset SCSI processor regs        */
DECL|macro|CPU_ORIDE_RMOD
mdefine_line|#define CPU_ORIDE_RMOD          0x0001      /* Reset SCSI processor module      */
multiline_comment|/* SCSI processor commands */
DECL|macro|CPU_CMD_BRESET
mdefine_line|#define CPU_CMD_BRESET          0x300b      /* Reset SCSI bus                   */
multiline_comment|/* SCSI processor user exception register */
DECL|macro|CPU_UEXC_ONE
mdefine_line|#define CPU_UEXC_ONE            0x0002      /* User exception one               */
DECL|macro|CPU_UEXC_ZERO
mdefine_line|#define CPU_UEXC_ZERO           0x0001      /* User exception zero              */
multiline_comment|/* SCSI processor SCSI id register */
DECL|macro|CPU_SID_RSEID
mdefine_line|#define CPU_SID_RSEID           0x0f00      /* Who is sel/resel&squot;ing us          */
DECL|macro|CPU_SID_SID
mdefine_line|#define CPU_SID_SID             0x000f      /* Selection ID                     */
multiline_comment|/* SCSI processor device config 1 */
DECL|macro|CPU_DCFG1_SHOLD
mdefine_line|#define CPU_DCFG1_SHOLD         0x7000      /* Sync data hold                   */
DECL|macro|CPU_DCFG1_SSETUP
mdefine_line|#define CPU_DCFG1_SSETUP        0x0f00      /* Sync data setup                  */
DECL|macro|CPU_DCFG1_SOFF
mdefine_line|#define CPU_DCFG1_SOFF          0x000f      /* Sync data offset                 */
multiline_comment|/* SCSI processor device config 2 */
DECL|macro|CPU_DCFG2_FMASK
mdefine_line|#define CPU_DCFG2_FMASK         0xf000      /* Device flags                     */
DECL|macro|CPU_DCFG2_EWIDE
mdefine_line|#define CPU_DCFG2_EWIDE         0x0400      /* WIDE enable                      */
DECL|macro|CPU_DCFG2_EPAR
mdefine_line|#define CPU_DCFG2_EPAR          0x0200      /* Parity enable                    */
DECL|macro|CPU_DCFG2_EBLK
mdefine_line|#define CPU_DCFG2_EBLK          0x0100      /* Block mode transfer enable       */
DECL|macro|CPU_DCFG2_AMASK
mdefine_line|#define CPU_DCFG2_AMASK         0x0007      /* Assertion period mask            */
multiline_comment|/* SCSI processor phase pointer register */
DECL|macro|CPU_PPTR_STAT
mdefine_line|#define CPU_PPTR_STAT           0x1000      /* Status buf offset                */
DECL|macro|CPU_PPTR_MSGIN
mdefine_line|#define CPU_PPTR_MSGIN          0x0700      /* Msg-in buf offset                */
DECL|macro|CPU_PPTR_COM
mdefine_line|#define CPU_PPTR_COM            0x00f0      /* Cmd buf offset                   */
DECL|macro|CPU_PPTR_MSGOUT
mdefine_line|#define CPU_PPTR_MSGOUT         0x0007      /* Msg-out buf offset               */
multiline_comment|/* SCSI processor fifo status register */
DECL|macro|CPU_FSTAT_TFULL
mdefine_line|#define CPU_FSTAT_TFULL         0x8000      /* Top residue full                 */
DECL|macro|CPU_FSTAT_ARES
mdefine_line|#define CPU_FSTAT_ARES          0x4000      /* Odd residue for wide transfer    */
DECL|macro|CPU_FSTAT_CMSK
mdefine_line|#define CPU_FSTAT_CMSK          0x001c      /* FIFO count mask                  */
DECL|macro|CPU_FSTAT_BRES
mdefine_line|#define CPU_FSTAT_BRES          0x0001      /* Bottom residue full              */
multiline_comment|/* SCSI processor pin control register */
DECL|macro|CPU_PCTRL_PVALID
mdefine_line|#define CPU_PCTRL_PVALID        0x8000      /* Phase bits are valid             */
DECL|macro|CPU_PCTRL_PHI
mdefine_line|#define CPU_PCTRL_PHI           0x0400      /* Parity bit high                  */
DECL|macro|CPU_PCTRL_PLO
mdefine_line|#define CPU_PCTRL_PLO           0x0200      /* Parity bit low                   */
DECL|macro|CPU_PCTRL_REQ
mdefine_line|#define CPU_PCTRL_REQ           0x0100      /* REQ bus signal                   */
DECL|macro|CPU_PCTRL_ACK
mdefine_line|#define CPU_PCTRL_ACK           0x0080      /* ACK bus signal                   */
DECL|macro|CPU_PCTRL_RST
mdefine_line|#define CPU_PCTRL_RST           0x0040      /* RST bus signal                   */
DECL|macro|CPU_PCTRL_BSY
mdefine_line|#define CPU_PCTRL_BSY           0x0020      /* BSY bus signal                   */
DECL|macro|CPU_PCTRL_SEL
mdefine_line|#define CPU_PCTRL_SEL           0x0010      /* SEL bus signal                   */
DECL|macro|CPU_PCTRL_ATN
mdefine_line|#define CPU_PCTRL_ATN           0x0008      /* ATN bus signal                   */
DECL|macro|CPU_PCTRL_MSG
mdefine_line|#define CPU_PCTRL_MSG           0x0004      /* MSG bus signal                   */
DECL|macro|CPU_PCTRL_CD
mdefine_line|#define CPU_PCTRL_CD            0x0002      /* CD bus signal                    */
DECL|macro|CPU_PCTRL_IO
mdefine_line|#define CPU_PCTRL_IO            0x0001      /* IO bus signal                    */
multiline_comment|/* SCSI processor differential pins register */
DECL|macro|CPU_PDIFF_SENSE
mdefine_line|#define CPU_PDIFF_SENSE         0x0200      /* Differential sense               */
DECL|macro|CPU_PDIFF_MODE
mdefine_line|#define CPU_PDIFF_MODE          0x0100      /* Differential mode                */
DECL|macro|CPU_PDIFF_OENAB
mdefine_line|#define CPU_PDIFF_OENAB         0x0080      /* Outputs enable                   */
DECL|macro|CPU_PDIFF_PMASK
mdefine_line|#define CPU_PDIFF_PMASK         0x007c      /* Differential control pins        */
DECL|macro|CPU_PDIFF_TGT
mdefine_line|#define CPU_PDIFF_TGT           0x0002      /* Target mode enable               */
DECL|macro|CPU_PDIFF_INIT
mdefine_line|#define CPU_PDIFF_INIT          0x0001      /* Initiator mode enable            */
multiline_comment|/* RISC processor status register */
DECL|macro|RISC_PSR_FTRUE
mdefine_line|#define RISC_PSR_FTRUE          0x8000      /* Force true                       */
DECL|macro|RISC_PSR_LCD
mdefine_line|#define RISC_PSR_LCD            0x4000      /* Loop counter shows done status   */
DECL|macro|RISC_PSR_RIRQ
mdefine_line|#define RISC_PSR_RIRQ           0x2000      /* RISC irq status                  */
DECL|macro|RISC_PSR_TOFLOW
mdefine_line|#define RISC_PSR_TOFLOW         0x1000      /* Timer overflow (rollover)        */
DECL|macro|RISC_PSR_AOFLOW
mdefine_line|#define RISC_PSR_AOFLOW         0x0800      /* Arithmetic overflow              */
DECL|macro|RISC_PSR_AMSB
mdefine_line|#define RISC_PSR_AMSB           0x0400      /* Arithmetic big endian            */
DECL|macro|RISC_PSR_ACARRY
mdefine_line|#define RISC_PSR_ACARRY         0x0200      /* Arithmetic carry                 */
DECL|macro|RISC_PSR_AZERO
mdefine_line|#define RISC_PSR_AZERO          0x0100      /* Arithmetic zero                  */
DECL|macro|RISC_PSR_ULTRA
mdefine_line|#define RISC_PSR_ULTRA          0x0020      /* Ultra mode                       */
DECL|macro|RISC_PSR_DIRQ
mdefine_line|#define RISC_PSR_DIRQ           0x0010      /* DVMA interrupt                   */
DECL|macro|RISC_PSR_SIRQ
mdefine_line|#define RISC_PSR_SIRQ           0x0008      /* SCSI processor interrupt         */
DECL|macro|RISC_PSR_HIRQ
mdefine_line|#define RISC_PSR_HIRQ           0x0004      /* Host interrupt                   */
DECL|macro|RISC_PSR_IPEND
mdefine_line|#define RISC_PSR_IPEND          0x0002      /* Interrupt pending                */
DECL|macro|RISC_PSR_FFALSE
mdefine_line|#define RISC_PSR_FFALSE         0x0001      /* Force false                      */
multiline_comment|/* RISC processor memory timing register */
DECL|macro|RISC_MTREG_P1DFLT
mdefine_line|#define RISC_MTREG_P1DFLT       0x1200      /* Default read/write timing, pg1   */
DECL|macro|RISC_MTREG_P0DFLT
mdefine_line|#define RISC_MTREG_P0DFLT       0x0012      /* Default read/write timing, pg0   */
DECL|macro|RISC_MTREG_P1ULTRA
mdefine_line|#define RISC_MTREG_P1ULTRA      0x2300      /* Ultra-mode rw timing, pg1        */
DECL|macro|RISC_MTREG_P0ULTRA
mdefine_line|#define RISC_MTREG_P0ULTRA      0x0023      /* Ultra-mode rw timing, pg0        */
multiline_comment|/* Host command/ctrl register */
DECL|macro|HCCTRL_NOP
mdefine_line|#define HCCTRL_NOP              0x0000      /* CMD: No operation                */
DECL|macro|HCCTRL_RESET
mdefine_line|#define HCCTRL_RESET            0x1000      /* CMD: Reset RISC cpu              */
DECL|macro|HCCTRL_PAUSE
mdefine_line|#define HCCTRL_PAUSE            0x2000      /* CMD: Pause RISC cpu              */
DECL|macro|HCCTRL_REL
mdefine_line|#define HCCTRL_REL              0x3000      /* CMD: Release paused RISC cpu     */
DECL|macro|HCCTRL_STEP
mdefine_line|#define HCCTRL_STEP             0x4000      /* CMD: Single step RISC cpu        */
DECL|macro|HCCTRL_SHIRQ
mdefine_line|#define HCCTRL_SHIRQ            0x5000      /* CMD: Set host irq                */
DECL|macro|HCCTRL_CHIRQ
mdefine_line|#define HCCTRL_CHIRQ            0x6000      /* CMD: Clear host irq              */
DECL|macro|HCCTRL_CRIRQ
mdefine_line|#define HCCTRL_CRIRQ            0x7000      /* CMD: Clear RISC cpu irq          */
DECL|macro|HCCTRL_BKPT
mdefine_line|#define HCCTRL_BKPT             0x8000      /* CMD: Breakpoint enables change   */
DECL|macro|HCCTRL_TMODE
mdefine_line|#define HCCTRL_TMODE            0xf000      /* CMD: Enable test mode            */
DECL|macro|HCCTRL_HIRQ
mdefine_line|#define HCCTRL_HIRQ             0x0080      /* Host IRQ pending                 */
DECL|macro|HCCTRL_RRIP
mdefine_line|#define HCCTRL_RRIP             0x0040      /* RISC cpu reset in happening now  */
DECL|macro|HCCTRL_RPAUSED
mdefine_line|#define HCCTRL_RPAUSED          0x0020      /* RISC cpu is paused now           */
DECL|macro|HCCTRL_EBENAB
mdefine_line|#define HCCTRL_EBENAB           0x0010      /* External breakpoint enable       */
DECL|macro|HCCTRL_B1ENAB
mdefine_line|#define HCCTRL_B1ENAB           0x0008      /* Breakpoint 1 enable              */
DECL|macro|HCCTRL_B0ENAB
mdefine_line|#define HCCTRL_B0ENAB           0x0004      /* Breakpoint 0 enable              */
DECL|macro|QLOGICPTI
mdefine_line|#define QLOGICPTI {&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;/* next */&t;&t;NULL,&t;&t;&t;&t;&t;   &bslash;&n;&t;/* usage_count */&t;NULL,&t;&t;&t;&t;&t;   &bslash;&n;&t;/* proc dir */&t;&t;NULL,&t;&t;&t;&t;&t;   &bslash;&n;&t;/* procfs info */&t;NULL,&t;&t;&t;&t;&t;   &bslash;&n;&t;/* name */&t;&t;NULL,&t;&t;&t;&t;&t;   &bslash;&n;&t;/* detect */&t;&t;qlogicpti_detect,&t;&t;&t;   &bslash;&n;&t;/* release */&t;&t;qlogicpti_release,&t;&t;&t;   &bslash;&n;&t;/* info */&t;&t;qlogicpti_info,&t;&t;&t;&t;   &bslash;&n;&t;/* command */&t;&t;NULL,&t;&t;&t;&t;&t;   &bslash;&n;&t;/* queuecommand */&t;qlogicpti_queuecommand,&t;&t;&t;   &bslash;&n;&t;/* abort */&t;&t;qlogicpti_abort,&t;&t;&t;   &bslash;&n;&t;/* reset */&t;&t;qlogicpti_reset,&t;&t;&t;   &bslash;&n;&t;/* slave_attach */&t;NULL,&t;&t;&t;&t;&t;   &bslash;&n;&t;/* bios_param */&t;NULL,&t;&t;&t;   &t;&t;   &bslash;&n;&t;/* can_queue */&t;&t;QLOGICISP_REQ_QUEUE_LEN,&t;&t;   &bslash;&n;&t;/* this_id */&t;&t;7,&t;&t;&t;&t;&t;   &bslash;&n;&t;/* sg_tablesize */&t;QLOGICISP_MAX_SG(QLOGICISP_REQ_QUEUE_LEN), &bslash;&n;&t;/* cmd_per_lun */&t;1,&t;&t;&t;&t;&t;   &bslash;&n;&t;/* present */&t;&t;0,&t;&t;&t;&t;&t;   &bslash;&n;&t;/* unchecked_isa_dma */&t;0,&t;&t;&t;&t;&t;   &bslash;&n;&t;/* use_clustering */&t;DISABLE_CLUSTERING&t;&t;&t;   &bslash;&n;}
multiline_comment|/* For our interrupt engine. */
DECL|macro|for_each_qlogicpti
mdefine_line|#define for_each_qlogicpti(qp) &bslash;&n;        for((qp) = qptichain; (qp); (qp) = (qp)-&gt;next)
macro_line|#endif /* !(_QLOGICPTI_H) */
eof
