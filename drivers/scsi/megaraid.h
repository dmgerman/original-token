macro_line|#ifndef __MEGARAID_H__
DECL|macro|__MEGARAID_H__
mdefine_line|#define __MEGARAID_H__
DECL|macro|IN_ISR
mdefine_line|#define IN_ISR                  0x80000000L
DECL|macro|NO_INTR
mdefine_line|#define NO_INTR                 0x40000000L
DECL|macro|IN_TIMEOUT
mdefine_line|#define IN_TIMEOUT              0x20000000L
DECL|macro|PENDING
mdefine_line|#define PENDING                 0x10000000L
DECL|macro|BOARD_QUARTZ
mdefine_line|#define BOARD_QUARTZ            0x08000000L
DECL|macro|SCB_ACTIVE
mdefine_line|#define SCB_ACTIVE 0x1
DECL|macro|SCB_WAITQ
mdefine_line|#define SCB_WAITQ  0x2
DECL|macro|SCB_ISSUED
mdefine_line|#define SCB_ISSUED 0x4
DECL|macro|SCB_FREE
mdefine_line|#define SCB_FREE                -1
DECL|macro|SCB_RESET
mdefine_line|#define SCB_RESET               -2
DECL|macro|SCB_ABORT
mdefine_line|#define SCB_ABORT               -3
DECL|macro|SCB_LOCKED
mdefine_line|#define SCB_LOCKED              -4
DECL|macro|MEGA_CMD_TIMEOUT
mdefine_line|#define MEGA_CMD_TIMEOUT        10
DECL|macro|MAX_SGLIST
mdefine_line|#define MAX_SGLIST              20
DECL|macro|MAX_COMMANDS
mdefine_line|#define MAX_COMMANDS            254
DECL|macro|MAX_LOGICAL_DRIVES
mdefine_line|#define MAX_LOGICAL_DRIVES      8
DECL|macro|MAX_CHANNEL
mdefine_line|#define MAX_CHANNEL             5
DECL|macro|MAX_TARGET
mdefine_line|#define MAX_TARGET              15
DECL|macro|MAX_PHYSICAL_DRIVES
mdefine_line|#define MAX_PHYSICAL_DRIVES     MAX_CHANNEL*MAX_TARGET
DECL|macro|INQUIRY_DATA_SIZE
mdefine_line|#define INQUIRY_DATA_SIZE       0x24
DECL|macro|MAX_CDB_LEN
mdefine_line|#define MAX_CDB_LEN             0x0A
DECL|macro|MAX_REQ_SENSE_LEN
mdefine_line|#define MAX_REQ_SENSE_LEN       0x20
DECL|macro|INTR_VALID
mdefine_line|#define INTR_VALID              0x40
multiline_comment|/* Mailbox commands */
DECL|macro|MEGA_MBOXCMD_LREAD
mdefine_line|#define MEGA_MBOXCMD_LREAD      0x01
DECL|macro|MEGA_MBOXCMD_LWRITE
mdefine_line|#define MEGA_MBOXCMD_LWRITE     0x02
DECL|macro|MEGA_MBOXCMD_PASSTHRU
mdefine_line|#define MEGA_MBOXCMD_PASSTHRU   0x03
DECL|macro|MEGA_MBOXCMD_ADAPTERINQ
mdefine_line|#define MEGA_MBOXCMD_ADAPTERINQ 0x05
multiline_comment|/* Offsets into Mailbox */
DECL|macro|COMMAND_PORT
mdefine_line|#define COMMAND_PORT       0x00
DECL|macro|COMMAND_ID_PORT
mdefine_line|#define COMMAND_ID_PORT    0x01
DECL|macro|SG_LIST_PORT0
mdefine_line|#define SG_LIST_PORT0      0x08
DECL|macro|SG_LIST_PORT1
mdefine_line|#define SG_LIST_PORT1      0x09
DECL|macro|SG_LIST_PORT2
mdefine_line|#define SG_LIST_PORT2      0x0a
DECL|macro|SG_LIST_PORT3
mdefine_line|#define SG_LIST_PORT3      0x0b
DECL|macro|SG_ELEMENT_PORT
mdefine_line|#define SG_ELEMENT_PORT    0x0d
DECL|macro|NO_FIRED_PORT
mdefine_line|#define NO_FIRED_PORT      0x0f
multiline_comment|/* I/O Port offsets */
DECL|macro|I_CMD_PORT
mdefine_line|#define I_CMD_PORT         0x00
DECL|macro|I_ACK_PORT
mdefine_line|#define I_ACK_PORT         0x00
DECL|macro|I_TOGGLE_PORT
mdefine_line|#define I_TOGGLE_PORT      0x01
DECL|macro|INTR_PORT
mdefine_line|#define INTR_PORT          0x0a
DECL|macro|MAILBOX_SIZE
mdefine_line|#define MAILBOX_SIZE       70
DECL|macro|MBOX_BUSY_PORT
mdefine_line|#define MBOX_BUSY_PORT     0x00
DECL|macro|MBOX_PORT0
mdefine_line|#define MBOX_PORT0         0x04
DECL|macro|MBOX_PORT1
mdefine_line|#define MBOX_PORT1         0x05
DECL|macro|MBOX_PORT2
mdefine_line|#define MBOX_PORT2         0x06
DECL|macro|MBOX_PORT3
mdefine_line|#define MBOX_PORT3         0x07
DECL|macro|ENABLE_MBOX_REGION
mdefine_line|#define ENABLE_MBOX_REGION 0x0B
multiline_comment|/* I/O Port Values */
DECL|macro|ISSUE_BYTE
mdefine_line|#define ISSUE_BYTE         0x10
DECL|macro|ACK_BYTE
mdefine_line|#define ACK_BYTE           0x08
DECL|macro|ENABLE_INTR_BYTE
mdefine_line|#define ENABLE_INTR_BYTE   0xc0
DECL|macro|DISABLE_INTR_BYTE
mdefine_line|#define DISABLE_INTR_BYTE  0x00
DECL|macro|VALID_INTR_BYTE
mdefine_line|#define VALID_INTR_BYTE    0x40
DECL|macro|MBOX_BUSY_BYTE
mdefine_line|#define MBOX_BUSY_BYTE     0x10
DECL|macro|ENABLE_MBOX_BYTE
mdefine_line|#define ENABLE_MBOX_BYTE   0x00
multiline_comment|/* Setup some port macros here */
DECL|macro|WRITE_MAILBOX
mdefine_line|#define WRITE_MAILBOX(base,offset,value)   *(base+offset)=value
DECL|macro|READ_MAILBOX
mdefine_line|#define READ_MAILBOX(base,offset)          *(base+offset)
DECL|macro|WRITE_PORT
mdefine_line|#define WRITE_PORT(base,offset,value)      outb_p(value,base+offset)
DECL|macro|READ_PORT
mdefine_line|#define READ_PORT(base,offset)             inb_p(base+offset)
DECL|macro|ISSUE_COMMAND
mdefine_line|#define ISSUE_COMMAND(base)   WRITE_PORT(base,I_CMD_PORT,ISSUE_BYTE)
DECL|macro|CLEAR_INTR
mdefine_line|#define CLEAR_INTR(base)      WRITE_PORT(base,I_ACK_PORT,ACK_BYTE)
DECL|macro|ENABLE_INTR
mdefine_line|#define ENABLE_INTR(base)     WRITE_PORT(base,I_TOGGLE_PORT,ENABLE_INTR_BYTE)
DECL|macro|DISABLE_INTR
mdefine_line|#define DISABLE_INTR(base)    WRITE_PORT(base,I_TOGGLE_PORT,DISABLE_INTR_BYTE)
multiline_comment|/* Define AMI&squot;s PCI codes */
DECL|macro|PCI_VENDOR_ID_AMI
macro_line|#undef PCI_VENDOR_ID_AMI
DECL|macro|PCI_DEVICE_ID_AMI_MEGARAID
macro_line|#undef PCI_DEVICE_ID_AMI_MEGARAID
macro_line|#ifndef PCI_VENDOR_ID_AMI
DECL|macro|PCI_VENDOR_ID_AMI
mdefine_line|#define PCI_VENDOR_ID_AMI          0x101E
DECL|macro|PCI_DEVICE_ID_AMI_MEGARAID
mdefine_line|#define PCI_DEVICE_ID_AMI_MEGARAID 0x9010
macro_line|#endif
DECL|macro|PCI_CONF_BASE_ADDR_OFFSET
mdefine_line|#define PCI_CONF_BASE_ADDR_OFFSET  0x10
DECL|macro|PCI_CONF_IRQ_OFFSET
mdefine_line|#define PCI_CONF_IRQ_OFFSET        0x3c
macro_line|#if LINUX_VERSION_CODE &lt; 0x20100
DECL|macro|MEGARAID
mdefine_line|#define MEGARAID &bslash;&n;  { NULL,                               /* Next                      */&bslash;&n;    NULL,                               /* Usage Count Pointer       */&bslash;&n;    NULL,                               /* /proc Directory Entry     */&bslash;&n;    megaraid_proc_info,                 /* /proc Info Function       */&bslash;&n;    &quot;MegaRAID&quot;,                         /* Driver Name               */&bslash;&n;    megaraid_detect,                    /* Detect Host Adapter       */&bslash;&n;    megaraid_release,                   /* Release Host Adapter      */&bslash;&n;    megaraid_info,                      /* Driver Info Function      */&bslash;&n;    megaraid_command,                   /* Command Function          */&bslash;&n;    megaraid_queue,                     /* Queue Command Function    */&bslash;&n;    megaraid_abort,                     /* Abort Command Function    */&bslash;&n;    megaraid_reset,                     /* Reset Command Function    */&bslash;&n;    NULL,                               /* Slave Attach Function     */&bslash;&n;    megaraid_biosparam,                 /* Disk BIOS Parameters      */&bslash;&n;    1,                                  /* # of cmds that can be&bslash;&n;                                           outstanding at any time */&bslash;&n;    7,                                  /* HBA Target ID             */&bslash;&n;    MAX_SGLIST,                         /* Scatter/Gather Table Size */&bslash;&n;    1,                                  /* SCSI Commands per LUN     */&bslash;&n;    0,                                  /* Present                   */&bslash;&n;    0,                                  /* Default Unchecked ISA DMA */&bslash;&n;    ENABLE_CLUSTERING }                 /* Enable Clustering         */
macro_line|#else
DECL|macro|MEGARAID
mdefine_line|#define MEGARAID &bslash;&n;  {&bslash;&n;    name:            &quot;MegaRAID&quot;,               /* Driver Name               */&bslash;&n;    proc_info:        megaraid_proc_info,      /* /proc driver info         */&bslash;&n;    detect:           megaraid_detect,         /* Detect Host Adapter       */&bslash;&n;    release:          megaraid_release,        /* Release Host Adapter      */&bslash;&n;    info:             megaraid_info,           /* Driver Info Function      */&bslash;&n;    command:          megaraid_command,        /* Command Function          */&bslash;&n;    queuecommand:     megaraid_queue,          /* Queue Command Function    */&bslash;&n;    abort:            megaraid_abort,          /* Abort Command Function    */&bslash;&n;    reset:            megaraid_reset,          /* Reset Command Function    */&bslash;&n;    bios_param:       megaraid_biosparam,      /* Disk BIOS Parameters      */&bslash;&n;    can_queue:        255,                     /* Can Queue                 */&bslash;&n;    this_id:          7,                       /* HBA Target ID             */&bslash;&n;    sg_tablesize:     MAX_SGLIST,              /* Scatter/Gather Table Size */&bslash;&n;    cmd_per_lun:      1,                       /* SCSI Commands per LUN     */&bslash;&n;    present:          0,                       /* Present                   */&bslash;&n;    unchecked_isa_dma:0,                       /* Default Unchecked ISA DMA */&bslash;&n;    use_clustering:   ENABLE_CLUSTERING       /* Enable Clustering         */&bslash;&n;  }
macro_line|#endif
multiline_comment|/* Structures */
DECL|struct|_mega_ADP_INFO
r_typedef
r_struct
id|_mega_ADP_INFO
(brace
DECL|member|MaxConcCmds
id|u_char
id|MaxConcCmds
suffix:semicolon
DECL|member|RbldRate
id|u_char
id|RbldRate
suffix:semicolon
DECL|member|MaxTargPerChan
id|u_char
id|MaxTargPerChan
suffix:semicolon
DECL|member|ChanPresent
id|u_char
id|ChanPresent
suffix:semicolon
DECL|member|FwVer
id|u_char
id|FwVer
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|AgeOfFlash
id|u_short
id|AgeOfFlash
suffix:semicolon
DECL|member|ChipSet
id|u_char
id|ChipSet
suffix:semicolon
DECL|member|DRAMSize
id|u_char
id|DRAMSize
suffix:semicolon
DECL|member|CacheFlushInterval
id|u_char
id|CacheFlushInterval
suffix:semicolon
DECL|member|BiosVer
id|u_char
id|BiosVer
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|resvd
id|u_char
id|resvd
(braket
l_int|7
)braket
suffix:semicolon
DECL|typedef|mega_ADP_INFO
)brace
id|mega_ADP_INFO
suffix:semicolon
DECL|struct|_mega_LDRV_INFO
r_typedef
r_struct
id|_mega_LDRV_INFO
(brace
DECL|member|NumLDrv
id|u_char
id|NumLDrv
suffix:semicolon
DECL|member|resvd
id|u_char
id|resvd
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|LDrvSize
id|u_long
id|LDrvSize
(braket
id|MAX_LOGICAL_DRIVES
)braket
suffix:semicolon
DECL|member|LDrvProp
id|u_char
id|LDrvProp
(braket
id|MAX_LOGICAL_DRIVES
)braket
suffix:semicolon
DECL|member|LDrvState
id|u_char
id|LDrvState
(braket
id|MAX_LOGICAL_DRIVES
)braket
suffix:semicolon
DECL|typedef|mega_LDRV_INFO
)brace
id|mega_LDRV_INFO
suffix:semicolon
DECL|struct|_mega_PDRV_INFO
r_typedef
r_struct
id|_mega_PDRV_INFO
(brace
DECL|member|PDrvState
id|u_char
id|PDrvState
(braket
id|MAX_PHYSICAL_DRIVES
)braket
suffix:semicolon
DECL|member|resvd
id|u_char
id|resvd
suffix:semicolon
DECL|typedef|mega_PDRV_INFO
)brace
id|mega_PDRV_INFO
suffix:semicolon
singleline_comment|// RAID inquiry: Mailbox command 0x5
DECL|struct|_mega_RAIDINQ
r_typedef
r_struct
id|_mega_RAIDINQ
(brace
DECL|member|AdpInfo
id|mega_ADP_INFO
id|AdpInfo
suffix:semicolon
DECL|member|LogdrvInfo
id|mega_LDRV_INFO
id|LogdrvInfo
suffix:semicolon
DECL|member|PhysdrvInfo
id|mega_PDRV_INFO
id|PhysdrvInfo
suffix:semicolon
DECL|typedef|mega_RAIDINQ
)brace
id|mega_RAIDINQ
suffix:semicolon
singleline_comment|// Passthrough command: Mailbox command 0x3
DECL|struct|mega_passthru
r_typedef
r_struct
id|mega_passthru
(brace
DECL|member|timeout
id|u_char
id|timeout
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* 0=6sec/1=60sec/2=10min/3=3hrs */
DECL|member|ars
id|u_char
id|ars
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
id|u_char
id|reserved
suffix:colon
l_int|3
suffix:semicolon
DECL|member|islogical
id|u_char
id|islogical
suffix:colon
l_int|1
suffix:semicolon
DECL|member|logdrv
id|u_char
id|logdrv
suffix:semicolon
multiline_comment|/* if islogical == 1 */
DECL|member|channel
id|u_char
id|channel
suffix:semicolon
multiline_comment|/* if islogical == 0 */
DECL|member|target
id|u_char
id|target
suffix:semicolon
multiline_comment|/* if islogical == 0 */
DECL|member|queuetag
id|u_char
id|queuetag
suffix:semicolon
multiline_comment|/* unused */
DECL|member|queueaction
id|u_char
id|queueaction
suffix:semicolon
multiline_comment|/* unused */
DECL|member|cdb
id|u_char
id|cdb
(braket
id|MAX_CDB_LEN
)braket
suffix:semicolon
DECL|member|cdblen
id|u_char
id|cdblen
suffix:semicolon
DECL|member|reqsenselen
id|u_char
id|reqsenselen
suffix:semicolon
DECL|member|reqsensearea
id|u_char
id|reqsensearea
(braket
id|MAX_REQ_SENSE_LEN
)braket
suffix:semicolon
DECL|member|numsgelements
id|u_char
id|numsgelements
suffix:semicolon
DECL|member|scsistatus
id|u_char
id|scsistatus
suffix:semicolon
DECL|member|dataxferaddr
id|u_long
id|dataxferaddr
suffix:semicolon
DECL|member|dataxferlen
id|u_long
id|dataxferlen
suffix:semicolon
DECL|typedef|mega_passthru
)brace
id|mega_passthru
suffix:semicolon
DECL|struct|_mega_mailbox
r_typedef
r_struct
id|_mega_mailbox
(brace
DECL|member|cmd
multiline_comment|/* 0x0 */
id|u_char
id|cmd
suffix:semicolon
DECL|member|cmdid
multiline_comment|/* 0x1 */
id|u_char
id|cmdid
suffix:semicolon
DECL|member|numsectors
multiline_comment|/* 0x2 */
id|u_short
id|numsectors
suffix:semicolon
DECL|member|lba
multiline_comment|/* 0x4 */
id|u_long
id|lba
suffix:semicolon
DECL|member|xferaddr
multiline_comment|/* 0x8 */
id|u_long
id|xferaddr
suffix:semicolon
DECL|member|logdrv
multiline_comment|/* 0xC */
id|u_char
id|logdrv
suffix:semicolon
DECL|member|numsgelements
multiline_comment|/* 0xD */
id|u_char
id|numsgelements
suffix:semicolon
DECL|member|resvd
multiline_comment|/* 0xE */
id|u_char
id|resvd
suffix:semicolon
DECL|member|busy
multiline_comment|/* 0xF */
id|u_char
id|busy
suffix:semicolon
DECL|member|numstatus
multiline_comment|/* 0x10*/
id|u_char
id|numstatus
suffix:semicolon
DECL|member|status
multiline_comment|/* 0x11*/
id|u_char
id|status
suffix:semicolon
DECL|member|completed
multiline_comment|/* 0x12*/
id|u_char
id|completed
(braket
l_int|46
)braket
suffix:semicolon
DECL|member|mraid_poll
id|u_char
id|mraid_poll
suffix:semicolon
DECL|member|mraid_ack
id|u_char
id|mraid_ack
suffix:semicolon
DECL|member|pad
id|u_char
id|pad
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|mega_mailbox
)brace
id|mega_mailbox
suffix:semicolon
DECL|struct|_mega_sglist
r_typedef
r_struct
id|_mega_sglist
(brace
DECL|member|address
id|u_long
id|address
suffix:semicolon
DECL|member|length
id|u_long
id|length
suffix:semicolon
DECL|typedef|mega_sglist
)brace
id|mega_sglist
suffix:semicolon
multiline_comment|/* Queued command data */
DECL|typedef|mega_scb
r_typedef
r_struct
id|_mega_scb
id|mega_scb
suffix:semicolon
DECL|struct|_mega_scb
r_struct
id|_mega_scb
(brace
DECL|member|idx
r_int
id|idx
suffix:semicolon
DECL|member|flag
id|u_long
id|flag
suffix:semicolon
DECL|member|SCpnt
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
DECL|member|mboxData
id|u_char
id|mboxData
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|pthru
id|mega_passthru
id|pthru
suffix:semicolon
DECL|member|sgList
id|mega_sglist
op_star
id|sgList
suffix:semicolon
DECL|member|next
id|mega_scb
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Per-controller data */
DECL|struct|_mega_host_config
r_typedef
r_struct
id|_mega_host_config
(brace
DECL|member|numldrv
id|u_char
id|numldrv
suffix:semicolon
DECL|member|flag
id|u_long
id|flag
suffix:semicolon
DECL|member|base
id|u_long
id|base
suffix:semicolon
DECL|member|megaTq
r_struct
id|tq_struct
id|megaTq
suffix:semicolon
multiline_comment|/* Host adapter parameters */
DECL|member|fwVer
id|u_char
id|fwVer
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|biosVer
id|u_char
id|biosVer
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|host
r_struct
id|Scsi_Host
op_star
id|host
suffix:semicolon
multiline_comment|/* The following must be DMA-able!! */
DECL|member|mbox
r_volatile
id|mega_mailbox
op_star
id|mbox
suffix:semicolon
DECL|member|mailbox
r_volatile
id|mega_mailbox
id|mailbox
suffix:semicolon
DECL|member|mega_buffer
r_volatile
id|u_char
id|mega_buffer
(braket
l_int|2
op_star
l_int|1024L
)braket
suffix:semicolon
DECL|member|max_cmds
id|u_char
id|max_cmds
suffix:semicolon
DECL|member|scbList
id|mega_scb
id|scbList
(braket
id|MAX_COMMANDS
)braket
suffix:semicolon
DECL|typedef|mega_host_config
)brace
id|mega_host_config
suffix:semicolon
r_extern
r_struct
id|proc_dir_entry
id|proc_scsi_megaraid
suffix:semicolon
r_const
r_char
op_star
id|megaraid_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|megaraid_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|megaraid_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|megaraid_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|megaraid_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|megaraid_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|megaraid_queue
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
id|megaraid_biosparam
c_func
(paren
id|Disk
op_star
comma
id|kdev_t
comma
r_int
op_star
)paren
suffix:semicolon
r_int
id|megaraid_proc_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|hostno
comma
r_int
id|inout
)paren
suffix:semicolon
macro_line|#endif
eof
