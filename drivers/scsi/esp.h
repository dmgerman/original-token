multiline_comment|/* esp.h:  Defines and structures for the Sparc ESP (Enhanced SCSI&n; *         Processor) driver under Linux.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_ESP_H
DECL|macro|_SPARC_ESP_H
mdefine_line|#define _SPARC_ESP_H
multiline_comment|/* For dvma controller register definitions. */
macro_line|#include &lt;asm/dma.h&gt;
multiline_comment|/* The ESP SCSI controllers have their register sets in three&n; * &quot;classes&quot;:&n; *&n; * 1) Registers which are both read and write.&n; * 2) Registers which are read only.&n; * 3) Registers which are write only.&n; *&n; * Yet, they all live within the same IO space.&n; */
multiline_comment|/* All the ESP registers are one byte each and are accessed longwords&n; * apart with a big-endian ordering to the bytes.&n; */
DECL|struct|Sparc_ESP_regs
r_struct
id|Sparc_ESP_regs
(brace
multiline_comment|/* Access    Description              Offset */
DECL|member|esp_tclow
r_volatile
id|unchar
id|esp_tclow
suffix:semicolon
multiline_comment|/* rw  Low bits of the transfer count 0x00   */
DECL|member|tlpad1
id|unchar
id|tlpad1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|esp_tcmed
r_volatile
id|unchar
id|esp_tcmed
suffix:semicolon
multiline_comment|/* rw  Mid bits of the transfer count 0x04   */
DECL|member|fdpad
id|unchar
id|fdpad
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|esp_fdata
r_volatile
id|unchar
id|esp_fdata
suffix:semicolon
multiline_comment|/* rw  FIFO data bits                 0x08   */
DECL|member|cbpad
id|unchar
id|cbpad
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|esp_cmd
r_volatile
id|unchar
id|esp_cmd
suffix:semicolon
multiline_comment|/* rw  SCSI command bits              0x0c   */
DECL|member|stpad
id|unchar
id|stpad
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|esp_status
r_volatile
id|unchar
id|esp_status
suffix:semicolon
multiline_comment|/* ro  ESP status register            0x10   */
DECL|macro|esp_busid
mdefine_line|#define esp_busid   esp_status  /* wo  Bus ID for select/reselect     0x10   */
DECL|member|irqpd
id|unchar
id|irqpd
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|esp_intrpt
r_volatile
id|unchar
id|esp_intrpt
suffix:semicolon
multiline_comment|/* ro  Kind of interrupt              0x14   */
DECL|macro|esp_timeo
mdefine_line|#define esp_timeo   esp_intrpt  /* wo  Timeout value for select/resel 0x14   */
DECL|member|sspad
id|unchar
id|sspad
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|esp_sstep
r_volatile
id|unchar
id|esp_sstep
suffix:semicolon
multiline_comment|/* ro  Sequence step register         0x18   */
DECL|macro|esp_stp
mdefine_line|#define esp_stp     esp_sstep   /* wo  Transfer period per sync       0x18   */
DECL|member|ffpad
id|unchar
id|ffpad
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|esp_fflags
r_volatile
id|unchar
id|esp_fflags
suffix:semicolon
multiline_comment|/* ro  Bits of current FIFO info      0x1c   */
DECL|macro|esp_soff
mdefine_line|#define esp_soff    esp_fflags  /* wo  Sync offset                    0x1c   */
DECL|member|cf1pd
id|unchar
id|cf1pd
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|esp_cfg1
r_volatile
id|unchar
id|esp_cfg1
suffix:semicolon
multiline_comment|/* rw  First configuration register   0x20   */
DECL|member|cfpad
id|unchar
id|cfpad
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|esp_cfact
r_volatile
id|unchar
id|esp_cfact
suffix:semicolon
multiline_comment|/* wo  Clock conversion factor        0x24   */
DECL|member|ctpad
id|unchar
id|ctpad
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|esp_ctest
r_volatile
id|unchar
id|esp_ctest
suffix:semicolon
multiline_comment|/* wo  Chip test register             0x28   */
DECL|member|cf2pd
id|unchar
id|cf2pd
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|esp_cfg2
r_volatile
id|unchar
id|esp_cfg2
suffix:semicolon
multiline_comment|/* rw  Second configuration register  0x2c   */
DECL|member|cf3pd
id|unchar
id|cf3pd
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* The following is only found on the 53C9X series SCSI chips */
DECL|member|esp_cfg3
r_volatile
id|unchar
id|esp_cfg3
suffix:semicolon
multiline_comment|/* rw  Third configuration register   0x30  */
DECL|member|thpd
id|unchar
id|thpd
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* The following is found on all chips except the NCR53C90 (ESP100) */
DECL|member|esp_tchi
r_volatile
id|unchar
id|esp_tchi
suffix:semicolon
multiline_comment|/* rw  High bits of transfer count    0x38  */
DECL|macro|esp_uid
mdefine_line|#define esp_uid     esp_tchi    /* ro  Unique ID code                 0x38  */
DECL|member|fgpad
id|unchar
id|fgpad
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|esp_fgrnd
r_volatile
id|unchar
id|esp_fgrnd
suffix:semicolon
multiline_comment|/* rw  Data base for fifo             0x3c  */
)brace
suffix:semicolon
multiline_comment|/* Various revisions of the ESP board. */
DECL|enum|esp_rev
r_enum
id|esp_rev
(brace
DECL|enumerator|esp100
id|esp100
op_assign
l_int|0x00
comma
multiline_comment|/* NCR53C90  */
DECL|enumerator|esp100a
id|esp100a
op_assign
l_int|0x01
comma
multiline_comment|/* NCR53C90A */
DECL|enumerator|esp236
id|esp236
op_assign
l_int|0x02
comma
DECL|enumerator|fas236
id|fas236
op_assign
l_int|0x03
comma
DECL|enumerator|fas100a
id|fas100a
op_assign
l_int|0x04
comma
DECL|enumerator|fast
id|fast
op_assign
l_int|0x05
comma
DECL|enumerator|espunknown
id|espunknown
op_assign
l_int|0x06
)brace
suffix:semicolon
multiline_comment|/* We get one of these for each ESP probed. */
DECL|struct|Sparc_ESP
r_struct
id|Sparc_ESP
(brace
DECL|member|next
r_struct
id|Sparc_ESP
op_star
id|next
suffix:semicolon
multiline_comment|/* Next ESP on probed or NULL */
DECL|member|eregs
r_struct
id|Sparc_ESP_regs
op_star
id|eregs
suffix:semicolon
multiline_comment|/* All esp registers */
DECL|member|dma
r_struct
id|Linux_SBus_DMA
op_star
id|dma
suffix:semicolon
multiline_comment|/* Who I do transfers with. */
DECL|member|dregs
r_struct
id|sparc_dma_registers
op_star
id|dregs
suffix:semicolon
multiline_comment|/* And his registers. */
DECL|member|ehost
r_struct
id|Scsi_Host
op_star
id|ehost
suffix:semicolon
multiline_comment|/* Backpointer to SCSI Host */
DECL|member|edev
r_struct
id|linux_sbus_device
op_star
id|edev
suffix:semicolon
multiline_comment|/* Pointer to SBus entry */
DECL|member|prom_name
r_char
id|prom_name
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* Name of ESP device from prom */
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
multiline_comment|/* Prom node where ESP found */
DECL|member|esp_id
r_int
id|esp_id
suffix:semicolon
multiline_comment|/* Same as esphost-&gt;host_id */
multiline_comment|/* ESP Configuration Registers */
DECL|member|config1
r_int
r_char
id|config1
suffix:semicolon
multiline_comment|/* Copy of the 1st config register */
DECL|member|config2
r_int
r_char
id|config2
suffix:semicolon
multiline_comment|/* Copy of the 2nd config register */
DECL|member|config3
r_int
r_char
id|config3
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Copy of the 3rd config register */
multiline_comment|/* The current command we are sending to the ESP chip.  This esp_command&n;   * ptr needs to be mapped in DVMA area so we can send commands and read&n;   * from the ESP fifo without burning precious CPU cycles.  Programmed I/O&n;   * sucks when we have the DVMA to do it for us.&n;   */
DECL|member|esp_command
r_volatile
id|unchar
op_star
id|esp_command
suffix:semicolon
multiline_comment|/* Location of command */
DECL|member|esp_clen
r_int
id|esp_clen
suffix:semicolon
multiline_comment|/* Length of this command */
multiline_comment|/* To hold onto the dvma buffer ptr. */
DECL|member|dvma_hold
r_char
op_star
id|dvma_hold
suffix:semicolon
multiline_comment|/* The following are used to determine the cause of an IRQ. Upon every&n;   * IRQ entry we synchronize these with the hardware registers.&n;   */
DECL|member|ireg
id|unchar
id|ireg
suffix:semicolon
multiline_comment|/* Copy of ESP interrupt register */
DECL|member|sreg
id|unchar
id|sreg
suffix:semicolon
multiline_comment|/* Same for ESP status register */
DECL|member|seqreg
id|unchar
id|seqreg
suffix:semicolon
multiline_comment|/* The ESP sequence register */
multiline_comment|/* Clock periods, frequencies, synchronization, etc. */
DECL|member|cfreq
r_int
r_int
id|cfreq
suffix:semicolon
multiline_comment|/* Clock frequency in HZ */
DECL|member|cfact
r_int
r_int
id|cfact
suffix:semicolon
multiline_comment|/* Clock conversion factor */
DECL|member|ccycle
r_int
r_int
id|ccycle
suffix:semicolon
multiline_comment|/* One ESP clock cycle */
DECL|member|ctick
r_int
r_int
id|ctick
suffix:semicolon
multiline_comment|/* One ESP clock time */
DECL|member|sync_defp
r_int
r_int
id|sync_defp
suffix:semicolon
multiline_comment|/* Default negotiation period */
multiline_comment|/* Misc. info about this ESP */
DECL|member|erev
r_enum
id|esp_rev
id|erev
suffix:semicolon
multiline_comment|/* ESP revision */
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* SBus IRQ for this ESP */
DECL|member|scsi_id
r_int
id|scsi_id
suffix:semicolon
multiline_comment|/* Who am I as initiator? */
DECL|member|scsi_id_mask
r_int
id|scsi_id_mask
suffix:semicolon
multiline_comment|/* Bitmask of &squot;me&squot;. */
DECL|member|diff
r_int
id|diff
suffix:semicolon
multiline_comment|/* Differential SCSI? */
DECL|member|bursts
r_int
id|bursts
suffix:semicolon
multiline_comment|/* Burst sizes our DVMA supports */
multiline_comment|/* Our command queues, only one cmd lives in the current_SC queue. */
DECL|member|issue_SC
id|Scsi_Cmnd
op_star
id|issue_SC
suffix:semicolon
multiline_comment|/* Commands to be issued */
DECL|member|current_SC
id|Scsi_Cmnd
op_star
id|current_SC
suffix:semicolon
multiline_comment|/* Who is currently working the bus */
DECL|member|disconnected_SC
id|Scsi_Cmnd
op_star
id|disconnected_SC
suffix:semicolon
multiline_comment|/* Commands disconnected from the bus */
macro_line|#ifdef THREADED_ESP_DRIVER
DECL|member|eatme_SC
id|Scsi_Cmnd
op_star
id|eatme_SC
suffix:semicolon
multiline_comment|/* Cmds waiting for esp thread to process. */
macro_line|#endif
multiline_comment|/* Abortion status */
DECL|member|aborting
DECL|member|abortion_complete
DECL|member|abort_result
r_int
id|aborting
comma
id|abortion_complete
comma
id|abort_result
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Bitfield meanings for the above registers. */
multiline_comment|/* ESP config reg 1, read-write, found on all ESP chips */
DECL|macro|ESP_CONFIG1_ID
mdefine_line|#define ESP_CONFIG1_ID        0x07             /* My BUS ID bits */
DECL|macro|ESP_CONFIG1_CHTEST
mdefine_line|#define ESP_CONFIG1_CHTEST    0x08             /* Enable ESP chip tests */
DECL|macro|ESP_CONFIG1_PENABLE
mdefine_line|#define ESP_CONFIG1_PENABLE   0x10             /* Enable parity checks */
DECL|macro|ESP_CONFIG1_PARTEST
mdefine_line|#define ESP_CONFIG1_PARTEST   0x20             /* Parity test mode enabled? */
DECL|macro|ESP_CONFIG1_SRRDISAB
mdefine_line|#define ESP_CONFIG1_SRRDISAB  0x40             /* Disable SCSI reset reports */
DECL|macro|ESP_CONFIG1_SLCABLE
mdefine_line|#define ESP_CONFIG1_SLCABLE   0x80             /* Enable slow cable mode */
multiline_comment|/* ESP config reg 2, read-write, found only on esp100a+esp200+esp236 chips */
DECL|macro|ESP_CONFIG2_DMAPARITY
mdefine_line|#define ESP_CONFIG2_DMAPARITY 0x01             /* Parity DMA err (200,236) */
DECL|macro|ESP_CONFIG2_REGPARITY
mdefine_line|#define ESP_CONFIG2_REGPARITY 0x02             /* Parity reg err (200,236) */
DECL|macro|ESP_CONFIG2_BADPARITY
mdefine_line|#define ESP_CONFIG2_BADPARITY 0x04             /* Bad parity target abort  */
DECL|macro|ESP_CONFIG2_SCSI2ENAB
mdefine_line|#define ESP_CONFIG2_SCSI2ENAB 0x08             /* Enable SCSI-2 features   */
DECL|macro|ESP_CONFIG2_HI
mdefine_line|#define ESP_CONFIG2_HI        0x10             /* High Impedance DREQ ???  */
DECL|macro|ESP_CONFIG2_BCM
mdefine_line|#define ESP_CONFIG2_BCM       0x20             /* Enable byte-ctrl (236)   */
DECL|macro|ESP_CONFIG2_FENAB
mdefine_line|#define ESP_CONFIG2_FENAB     0x40             /* Enable features (fas100,esp216)      */
DECL|macro|ESP_CONFIG2_SPL
mdefine_line|#define ESP_CONFIG2_SPL       0x40             /* Enable status-phase latch (esp236)   */
DECL|macro|ESP_CONFIG2_MAGIC
mdefine_line|#define ESP_CONFIG2_MAGIC     0xe0             /* Invalid bits... */
multiline_comment|/* ESP config register 3 read-write, found only esp236+fas236+fas100a chips */
DECL|macro|ESP_CONFIG3_FCLOCK
mdefine_line|#define ESP_CONFIG3_FCLOCK    0x01             /* FAST SCSI clock rate (esp100a)     */
DECL|macro|ESP_CONFIG3_TEM
mdefine_line|#define ESP_CONFIG3_TEM       0x01             /* Enable thresh-8 mode (esp/fas236)  */
DECL|macro|ESP_CONFIG3_FAST
mdefine_line|#define ESP_CONFIG3_FAST      0x02             /* Enable FAST SCSI     (esp100a)     */
DECL|macro|ESP_CONFIG3_ADMA
mdefine_line|#define ESP_CONFIG3_ADMA      0x02             /* Enable alternate-dma (esp/fas236)  */
DECL|macro|ESP_CONFIG3_TENB
mdefine_line|#define ESP_CONFIG3_TENB      0x04             /* group2 SCSI2 support (esp100a)     */
DECL|macro|ESP_CONFIG3_SRB
mdefine_line|#define ESP_CONFIG3_SRB       0x04             /* Save residual byte   (esp/fas236)  */
DECL|macro|ESP_CONFIG3_TMS
mdefine_line|#define ESP_CONFIG3_TMS       0x08             /* Three-byte msg&squot;s ok  (esp100a)     */
DECL|macro|ESP_CONFIG3_FCLK
mdefine_line|#define ESP_CONFIG3_FCLK      0x08             /* Fast SCSI clock rate (esp/fas236)  */
DECL|macro|ESP_CONFIG3_IDMSG
mdefine_line|#define ESP_CONFIG3_IDMSG     0x10             /* ID message checking  (esp100a)     */
DECL|macro|ESP_CONFIG3_FSCSI
mdefine_line|#define ESP_CONFIG3_FSCSI     0x10             /* Enable FAST SCSI     (esp/fas236)  */
DECL|macro|ESP_CONFIG3_GTM
mdefine_line|#define ESP_CONFIG3_GTM       0x20             /* group2 SCSI2 support (esp/fas236)  */
DECL|macro|ESP_CONFIG3_TBMS
mdefine_line|#define ESP_CONFIG3_TBMS      0x40             /* Three-byte msg&squot;s ok  (esp/fas236)  */
DECL|macro|ESP_CONFIG3_IMS
mdefine_line|#define ESP_CONFIG3_IMS       0x80             /* ID msg chk&squot;ng        (esp/fas236)  */
multiline_comment|/* ESP command register read-write */
multiline_comment|/* Group 1 commands:  These may be sent at any point in time to the ESP&n; *                    chip.  None of them can generate interrupts &squot;cept&n; *                    the &quot;SCSI bus reset&quot; command if you have not disabled&n; *                    SCSI reset interrupts in the config1 ESP register.&n; */
DECL|macro|ESP_CMD_NULL
mdefine_line|#define ESP_CMD_NULL          0x00             /* Null command, ie. a nop */
DECL|macro|ESP_CMD_FLUSH
mdefine_line|#define ESP_CMD_FLUSH         0x01             /* FIFO Flush */
DECL|macro|ESP_CMD_RC
mdefine_line|#define ESP_CMD_RC            0x02             /* Chip reset */
DECL|macro|ESP_CMD_RS
mdefine_line|#define ESP_CMD_RS            0x03             /* SCSI bus reset */
multiline_comment|/* Group 2 commands:  ESP must be an initiator and connected to a target&n; *                    for these commands to work.&n; */
DECL|macro|ESP_CMD_TI
mdefine_line|#define ESP_CMD_TI            0x10             /* Transfer Information */
DECL|macro|ESP_CMD_ICCSEQ
mdefine_line|#define ESP_CMD_ICCSEQ        0x11             /* Initiator cmd complete sequence */
DECL|macro|ESP_CMD_MOK
mdefine_line|#define ESP_CMD_MOK           0x12             /* Message okie-dokie */
DECL|macro|ESP_CMD_TPAD
mdefine_line|#define ESP_CMD_TPAD          0x18             /* Transfer Pad */
DECL|macro|ESP_CMD_SATN
mdefine_line|#define ESP_CMD_SATN          0x1a             /* Set ATN */
DECL|macro|ESP_CMD_RATN
mdefine_line|#define ESP_CMD_RATN          0x1b             /* De-assert ATN */
multiline_comment|/* Group 3 commands:  ESP must be in the MSGOUT or MSGIN state and be connected&n; *                    to a target as the initiator for these commands to work.&n; */
DECL|macro|ESP_CMD_SMSG
mdefine_line|#define ESP_CMD_SMSG          0x20             /* Send message */
DECL|macro|ESP_CMD_SSTAT
mdefine_line|#define ESP_CMD_SSTAT         0x21             /* Send status */
DECL|macro|ESP_CMD_SDATA
mdefine_line|#define ESP_CMD_SDATA         0x22             /* Send data */
DECL|macro|ESP_CMD_DSEQ
mdefine_line|#define ESP_CMD_DSEQ          0x23             /* Discontinue Sequence */
DECL|macro|ESP_CMD_TSEQ
mdefine_line|#define ESP_CMD_TSEQ          0x24             /* Terminate Sequence */
DECL|macro|ESP_CMD_TCCSEQ
mdefine_line|#define ESP_CMD_TCCSEQ        0x25             /* Target cmd cmplt sequence */
DECL|macro|ESP_CMD_DCNCT
mdefine_line|#define ESP_CMD_DCNCT         0x27             /* Disconnect */
DECL|macro|ESP_CMD_RMSG
mdefine_line|#define ESP_CMD_RMSG          0x28             /* Receive Message */
DECL|macro|ESP_CMD_RCMD
mdefine_line|#define ESP_CMD_RCMD          0x29             /* Receive Command */
DECL|macro|ESP_CMD_RDATA
mdefine_line|#define ESP_CMD_RDATA         0x2a             /* Receive Data */
DECL|macro|ESP_CMD_RCSEQ
mdefine_line|#define ESP_CMD_RCSEQ         0x2b             /* Receive cmd sequence */
multiline_comment|/* Group 4 commands:  The ESP must be in the disconnected state and must&n; *                    not be connected to any targets as initiator for&n; *                    these commands to work.&n; */
DECL|macro|ESP_CMD_RSEL
mdefine_line|#define ESP_CMD_RSEL          0x40             /* Reselect */
DECL|macro|ESP_CMD_SEL
mdefine_line|#define ESP_CMD_SEL           0x41             /* Select w/o ATN */
DECL|macro|ESP_CMD_SELA
mdefine_line|#define ESP_CMD_SELA          0x42             /* Select w/ATN */
DECL|macro|ESP_CMD_SELAS
mdefine_line|#define ESP_CMD_SELAS         0x43             /* Select w/ATN &amp; STOP */
DECL|macro|ESP_CMD_ESEL
mdefine_line|#define ESP_CMD_ESEL          0x44             /* Enable selection */
DECL|macro|ESP_CMD_DSEL
mdefine_line|#define ESP_CMD_DSEL          0x45             /* Disable selections */
DECL|macro|ESP_CMD_SA3
mdefine_line|#define ESP_CMD_SA3           0x46             /* Select w/ATN3 */
DECL|macro|ESP_CMD_RSEL3
mdefine_line|#define ESP_CMD_RSEL3         0x47             /* Reselect3 */
multiline_comment|/* This bit enables the ESP&squot;s DMA on the SBus */
DECL|macro|ESP_CMD_DMA
mdefine_line|#define ESP_CMD_DMA           0x80             /* Do DMA? */
multiline_comment|/* ESP status register read-only */
DECL|macro|ESP_STAT_PIO
mdefine_line|#define ESP_STAT_PIO          0x01             /* IO phase bit */
DECL|macro|ESP_STAT_PCD
mdefine_line|#define ESP_STAT_PCD          0x02             /* CD phase bit */
DECL|macro|ESP_STAT_PMSG
mdefine_line|#define ESP_STAT_PMSG         0x04             /* MSG phase bit */
DECL|macro|ESP_STAT_PMASK
mdefine_line|#define ESP_STAT_PMASK        0x07             /* Mask of phase bits */
DECL|macro|ESP_STAT_TDONE
mdefine_line|#define ESP_STAT_TDONE        0x08             /* Transfer Completed */
DECL|macro|ESP_STAT_TCNT
mdefine_line|#define ESP_STAT_TCNT         0x10             /* Transfer Counter Is Zero */
DECL|macro|ESP_STAT_PERR
mdefine_line|#define ESP_STAT_PERR         0x20             /* Parity error */
DECL|macro|ESP_STAT_SPAM
mdefine_line|#define ESP_STAT_SPAM         0x40             /* Real bad error */
multiline_comment|/* This indicates the &squot;interrupt pending&squot; condition on esp236, it is a reserved&n; * bit on other revs of the ESP.&n; */
DECL|macro|ESP_STAT_INTR
mdefine_line|#define ESP_STAT_INTR         0x80             /* Interrupt */
multiline_comment|/* The status register can be masked with ESP_STAT_PMASK and compared&n; * with the following values to determine the current phase the ESP&n; * (at least thinks it) is in.  For our purposes we also add our own&n; * software &squot;done&squot; bit for our phase management engine.&n; */
DECL|macro|ESP_DOP
mdefine_line|#define ESP_DOP   (0)                                       /* Data Out  */
DECL|macro|ESP_DIP
mdefine_line|#define ESP_DIP   (ESP_STAT_PIO)                            /* Data In   */
DECL|macro|ESP_CMDP
mdefine_line|#define ESP_CMDP  (ESP_STAT_PCD)                            /* Command   */
DECL|macro|ESP_STATP
mdefine_line|#define ESP_STATP (ESP_STAT_PCD|ESP_STAT_PIO)               /* Status    */
DECL|macro|ESP_MOP
mdefine_line|#define ESP_MOP   (ESP_STAT_PMSG|ESP_STAT_PCD)              /* Message Out */
DECL|macro|ESP_MIP
mdefine_line|#define ESP_MIP   (ESP_STAT_PMSG|ESP_STAT_PCD|ESP_STAT_PIO) /* Message In */
multiline_comment|/* ESP interrupt register read-only */
DECL|macro|ESP_INTR_S
mdefine_line|#define ESP_INTR_S            0x01             /* Select w/o ATN */
DECL|macro|ESP_INTR_SATN
mdefine_line|#define ESP_INTR_SATN         0x02             /* Select w/ATN */
DECL|macro|ESP_INTR_RSEL
mdefine_line|#define ESP_INTR_RSEL         0x04             /* Reselected */
DECL|macro|ESP_INTR_FDONE
mdefine_line|#define ESP_INTR_FDONE        0x08             /* Function done */
DECL|macro|ESP_INTR_BSERV
mdefine_line|#define ESP_INTR_BSERV        0x10             /* Bus service */
DECL|macro|ESP_INTR_DC
mdefine_line|#define ESP_INTR_DC           0x20             /* Disconnect */
DECL|macro|ESP_INTR_IC
mdefine_line|#define ESP_INTR_IC           0x40             /* Illegal command given */
DECL|macro|ESP_INTR_SR
mdefine_line|#define ESP_INTR_SR           0x80             /* SCSI bus reset detected */
multiline_comment|/* Interrupt status macros */
DECL|macro|ESP_SRESET_IRQ
mdefine_line|#define ESP_SRESET_IRQ(esp)  ((esp)-&gt;intreg &amp; (ESP_INTR_SR))
DECL|macro|ESP_ILLCMD_IRQ
mdefine_line|#define ESP_ILLCMD_IRQ(esp)  ((esp)-&gt;intreg &amp; (ESP_INTR_IC))
DECL|macro|ESP_SELECT_WITH_ATN_IRQ
mdefine_line|#define ESP_SELECT_WITH_ATN_IRQ(esp)     ((esp)-&gt;intreg &amp; (ESP_INTR_SATN))
DECL|macro|ESP_SELECT_WITHOUT_ATN_IRQ
mdefine_line|#define ESP_SELECT_WITHOUT_ATN_IRQ(esp)  ((esp)-&gt;intreg &amp; (ESP_INTR_S))
DECL|macro|ESP_SELECTION_IRQ
mdefine_line|#define ESP_SELECTION_IRQ(esp)  ((ESP_SELECT_WITH_ATN_IRQ(esp)) ||         &bslash;&n;&t;&t;&t;&t; (ESP_SELECT_WITHOUT_ATN_IRQ(esp)))
DECL|macro|ESP_RESELECTION_IRQ
mdefine_line|#define ESP_RESELECTION_IRQ(esp)         ((esp)-&gt;intreg &amp; (ESP_INTR_RSEL))
multiline_comment|/* ESP sequence step register read-only */
DECL|macro|ESP_STEP_VBITS
mdefine_line|#define ESP_STEP_VBITS        0x07             /* Valid bits */
DECL|macro|ESP_STEP_ASEL
mdefine_line|#define ESP_STEP_ASEL         0x00             /* Selection&amp;Arbitrate cmplt */
DECL|macro|ESP_STEP_SID
mdefine_line|#define ESP_STEP_SID          0x01             /* One msg byte sent */
DECL|macro|ESP_STEP_NCMD
mdefine_line|#define ESP_STEP_NCMD         0x02             /* Was not in command phase */
DECL|macro|ESP_STEP_PPC
mdefine_line|#define ESP_STEP_PPC          0x03             /* Early phase chg caused cmnd&n;                                                * bytes to be lost&n;                                                */
DECL|macro|ESP_STEP_FINI
mdefine_line|#define ESP_STEP_FINI         0x04             /* Command was sent ok */
multiline_comment|/* ESP chip-test register read-write */
DECL|macro|ESP_TEST_TARG
mdefine_line|#define ESP_TEST_TARG         0x01             /* Target test mode */
DECL|macro|ESP_TEST_INI
mdefine_line|#define ESP_TEST_INI          0x02             /* Initiator test mode */
DECL|macro|ESP_TEST_TS
mdefine_line|#define ESP_TEST_TS           0x04             /* Tristate test mode */
multiline_comment|/* ESP unique ID register read-only, found on fas236+fas100a only */
DECL|macro|ESP_UID_F100A
mdefine_line|#define ESP_UID_F100A         0x00             /* ESP FAS100A  */
DECL|macro|ESP_UID_F236
mdefine_line|#define ESP_UID_F236          0x02             /* ESP FAS236   */
DECL|macro|ESP_UID_REV
mdefine_line|#define ESP_UID_REV           0x07             /* ESP revision */
DECL|macro|ESP_UID_FAM
mdefine_line|#define ESP_UID_FAM           0xf8             /* ESP family   */
multiline_comment|/* ESP fifo flags register read-only */
multiline_comment|/* Note that the following implies a 16 byte FIFO on the ESP. */
DECL|macro|ESP_FF_FBYTES
mdefine_line|#define ESP_FF_FBYTES         0x1f             /* Num bytes in FIFO */
DECL|macro|ESP_FF_SSTEP
mdefine_line|#define ESP_FF_SSTEP          0xe0             /* Sequence step */
multiline_comment|/* ESP clock conversion factor register write-only */
DECL|macro|ESP_CCF_F0
mdefine_line|#define ESP_CCF_F0            0x00             /* 35.01MHz - 40MHz */
DECL|macro|ESP_CCF_NEVER
mdefine_line|#define ESP_CCF_NEVER         0x01             /* Set it to this and die */
DECL|macro|ESP_CCF_F2
mdefine_line|#define ESP_CCF_F2            0x02             /* 10MHz */
DECL|macro|ESP_CCF_F3
mdefine_line|#define ESP_CCF_F3            0x03             /* 10.01MHz - 15MHz */
DECL|macro|ESP_CCF_F4
mdefine_line|#define ESP_CCF_F4            0x04             /* 15.01MHz - 20MHz */
DECL|macro|ESP_CCF_F5
mdefine_line|#define ESP_CCF_F5            0x05             /* 20.01MHz - 25MHz */
DECL|macro|ESP_CCF_F6
mdefine_line|#define ESP_CCF_F6            0x06             /* 25.01MHz - 30MHz */
DECL|macro|ESP_CCF_F7
mdefine_line|#define ESP_CCF_F7            0x07             /* 30.01MHz - 35MHz */
r_extern
r_int
id|esp_detect
c_func
(paren
r_struct
id|SHT
op_star
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|esp_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_int
id|esp_queue
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
r_extern
r_int
id|esp_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|esp_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|esp_reset
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
id|proc_scsi_esp
suffix:semicolon
DECL|macro|SCSI_SPARC_ESP
mdefine_line|#define SCSI_SPARC_ESP {                                                               &bslash;&n;/* struct SHT *next */                                         NULL,                   &bslash;&n;/* long *usage_count */                                        NULL,                   &bslash;&n;/* struct proc_dir_entry *proc_dir */                          &amp;proc_scsi_esp,         &bslash;&n;/* int (*proc_info)(char *, char **, off_t, int, int, int) */  NULL,                   &bslash;&n;/* const char *name */                                         &quot;Sun ESP 100/100a/200&quot;, &bslash;&n;/* int detect(struct SHT *) */                                 esp_detect,             &bslash;&n;/* int release(struct Scsi_Host *) */                          NULL,                   &bslash;&n;/* const char *info(struct Scsi_Host *) */                     esp_info,               &bslash;&n;/* int command(Scsi_Cmnd *) */                                 esp_command,            &bslash;&n;/* int queuecommand(Scsi_Cmnd *, void (*done)(Scsi_Cmnd *)) */ esp_queue,              &bslash;&n;/* int abort(Scsi_Cmnd *) */                                   esp_abort,              &bslash;&n;/* int reset(Scsi_Cmnd *, int) */                              esp_reset,              &bslash;&n;/* int slave_attach(int, int) */                               NULL,                   &bslash;&n;/* int bios_param(Disk *, kdev_t, int[]) */                    NULL,                   &bslash;&n;/* int can_queue */                                            10,                     &bslash;&n;/* int this_id */                                              7,                      &bslash;&n;/* short unsigned int sg_tablesize */                          SG_ALL,                 &bslash;&n;/* short cmd_per_lun */                                        1,                      &bslash;&n;/* unsigned char present */                                    0,                      &bslash;&n;/* unsigned unchecked_isa_dma:1 */                             0,                      &bslash;&n;/* unsigned use_clustering:1 */                                DISABLE_CLUSTERING, }
multiline_comment|/* For our interrupt engine. */
DECL|macro|for_each_esp
mdefine_line|#define for_each_esp(esp) &bslash;&n;        for((esp) = espchain; (esp); (esp) = (esp)-&gt;next)
macro_line|#endif /* !(_SPARC_ESP_H) */
eof
