multiline_comment|/* NCR53C9x.c:  Defines and structures for the NCR53C9x generic driver.&n; *&n; * Originaly esp.h:  Defines and structures for the Sparc ESP &n; *                   (Enhanced SCSI Processor) driver under Linux.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; *&n; * Generalization by Jesper Skov (jskov@cygnus.co.uk)&n; */
macro_line|#ifndef NCR53C9X_H
DECL|macro|NCR53C9X_H
mdefine_line|#define NCR53C9X_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Macros for debugging messages */
multiline_comment|/* #define DEBUG_ESP */
multiline_comment|/* #define DEBUG_ESP_HME */
multiline_comment|/* #define DEBUG_ESP_DATA */
multiline_comment|/* #define DEBUG_ESP_QUEUE */
multiline_comment|/* #define DEBUG_ESP_DISCONNECT */
multiline_comment|/* #define DEBUG_ESP_STATUS */
multiline_comment|/* #define DEBUG_ESP_PHASES */
multiline_comment|/* #define DEBUG_ESP_WORKBUS */
multiline_comment|/* #define DEBUG_STATE_MACHINE */
multiline_comment|/* #define DEBUG_ESP_CMDS */
multiline_comment|/* #define DEBUG_ESP_IRQS */
multiline_comment|/* #define DEBUG_SDTR */
multiline_comment|/* #define DEBUG_ESP_SG */
multiline_comment|/* Use the following to sprinkle debugging messages in a way which&n; * suits you if combinations of the above become too verbose when&n; * trying to track down a specific problem.&n; */
multiline_comment|/* #define DEBUG_ESP_MISC */
macro_line|#if defined(DEBUG_ESP)
DECL|macro|ESPLOG
mdefine_line|#define ESPLOG(foo)  printk foo
macro_line|#else
DECL|macro|ESPLOG
mdefine_line|#define ESPLOG(foo)
macro_line|#endif /* (DEBUG_ESP) */
macro_line|#if defined(DEBUG_ESP_HME)
DECL|macro|ESPHME
mdefine_line|#define ESPHME(foo)  printk foo
macro_line|#else
DECL|macro|ESPHME
mdefine_line|#define ESPHME(foo)
macro_line|#endif
macro_line|#if defined(DEBUG_ESP_DATA)
DECL|macro|ESPDATA
mdefine_line|#define ESPDATA(foo)  printk foo
macro_line|#else
DECL|macro|ESPDATA
mdefine_line|#define ESPDATA(foo)
macro_line|#endif
macro_line|#if defined(DEBUG_ESP_QUEUE)
DECL|macro|ESPQUEUE
mdefine_line|#define ESPQUEUE(foo)  printk foo
macro_line|#else
DECL|macro|ESPQUEUE
mdefine_line|#define ESPQUEUE(foo)
macro_line|#endif
macro_line|#if defined(DEBUG_ESP_DISCONNECT)
DECL|macro|ESPDISC
mdefine_line|#define ESPDISC(foo)  printk foo
macro_line|#else
DECL|macro|ESPDISC
mdefine_line|#define ESPDISC(foo)
macro_line|#endif
macro_line|#if defined(DEBUG_ESP_STATUS)
DECL|macro|ESPSTAT
mdefine_line|#define ESPSTAT(foo)  printk foo
macro_line|#else
DECL|macro|ESPSTAT
mdefine_line|#define ESPSTAT(foo)
macro_line|#endif
macro_line|#if defined(DEBUG_ESP_PHASES)
DECL|macro|ESPPHASE
mdefine_line|#define ESPPHASE(foo)  printk foo
macro_line|#else
DECL|macro|ESPPHASE
mdefine_line|#define ESPPHASE(foo)
macro_line|#endif
macro_line|#if defined(DEBUG_ESP_WORKBUS)
DECL|macro|ESPBUS
mdefine_line|#define ESPBUS(foo)  printk foo
macro_line|#else
DECL|macro|ESPBUS
mdefine_line|#define ESPBUS(foo)
macro_line|#endif
macro_line|#if defined(DEBUG_ESP_IRQS)
DECL|macro|ESPIRQ
mdefine_line|#define ESPIRQ(foo)  printk foo
macro_line|#else
DECL|macro|ESPIRQ
mdefine_line|#define ESPIRQ(foo)
macro_line|#endif
macro_line|#if defined(DEBUG_SDTR)
DECL|macro|ESPSDTR
mdefine_line|#define ESPSDTR(foo)  printk foo
macro_line|#else
DECL|macro|ESPSDTR
mdefine_line|#define ESPSDTR(foo)
macro_line|#endif
macro_line|#if defined(DEBUG_ESP_MISC)
DECL|macro|ESPMISC
mdefine_line|#define ESPMISC(foo)  printk foo
macro_line|#else
DECL|macro|ESPMISC
mdefine_line|#define ESPMISC(foo)
macro_line|#endif
DECL|macro|INTERNAL_ESP_ERROR
mdefine_line|#define INTERNAL_ESP_ERROR &bslash;&n;        (panic (&quot;Internal ESP driver error in file %s, line %d&bslash;n&quot;, &bslash;&n;&t;&t;__FILE__, __LINE__))
DECL|macro|INTERNAL_ESP_ERROR_NOPANIC
mdefine_line|#define INTERNAL_ESP_ERROR_NOPANIC &bslash;&n;        (printk (&quot;Internal ESP driver error in file %s, line %d&bslash;n&quot;, &bslash;&n;&t;&t; __FILE__, __LINE__))
multiline_comment|/*&n; * padding for register structure&n; */
macro_line|#ifdef CONFIG_JAZZ_ESP
DECL|macro|EREGS_PAD
mdefine_line|#define EREGS_PAD(n)
macro_line|#else
DECL|macro|EREGS_PAD
mdefine_line|#define EREGS_PAD(n)    unchar n[3];
macro_line|#endif
multiline_comment|/* The ESP SCSI controllers have their register sets in three&n; * &quot;classes&quot;:&n; *&n; * 1) Registers which are both read and write.&n; * 2) Registers which are read only.&n; * 3) Registers which are write only.&n; *&n; * Yet, they all live within the same IO space.&n; */
multiline_comment|/* All the ESP registers are one byte each and are accessed longwords&n; * apart with a big-endian ordering to the bytes.&n; */
DECL|struct|ESP_regs
r_struct
id|ESP_regs
(brace
multiline_comment|/* Access    Description              Offset */
DECL|member|esp_tclow
r_volatile
id|unchar
id|esp_tclow
suffix:semicolon
multiline_comment|/* rw  Low bits of the transfer count 0x00   */
id|EREGS_PAD
c_func
(paren
id|tlpad1
)paren
suffix:semicolon
DECL|member|esp_tcmed
r_volatile
id|unchar
id|esp_tcmed
suffix:semicolon
multiline_comment|/* rw  Mid bits of the transfer count 0x04   */
id|EREGS_PAD
c_func
(paren
id|fdpad
)paren
suffix:semicolon
DECL|member|esp_fdata
r_volatile
id|unchar
id|esp_fdata
suffix:semicolon
multiline_comment|/* rw  FIFO data bits                 0x08   */
id|EREGS_PAD
c_func
(paren
id|cbpad
)paren
suffix:semicolon
DECL|member|esp_cmd
r_volatile
id|unchar
id|esp_cmd
suffix:semicolon
multiline_comment|/* rw  SCSI command bits              0x0c   */
id|EREGS_PAD
c_func
(paren
id|stpad
)paren
suffix:semicolon
DECL|member|esp_status
r_volatile
id|unchar
id|esp_status
suffix:semicolon
multiline_comment|/* ro  ESP status register            0x10   */
DECL|macro|esp_busid
mdefine_line|#define esp_busid   esp_status  /* wo  Bus ID for select/reselect     0x10   */
id|EREGS_PAD
c_func
(paren
id|irqpd
)paren
suffix:semicolon
DECL|member|esp_intrpt
r_volatile
id|unchar
id|esp_intrpt
suffix:semicolon
multiline_comment|/* ro  Kind of interrupt              0x14   */
DECL|macro|esp_timeo
mdefine_line|#define esp_timeo   esp_intrpt  /* wo  Timeout value for select/resel 0x14   */
id|EREGS_PAD
c_func
(paren
id|sspad
)paren
suffix:semicolon
DECL|member|esp_sstep
r_volatile
id|unchar
id|esp_sstep
suffix:semicolon
multiline_comment|/* ro  Sequence step register         0x18   */
DECL|macro|esp_stp
mdefine_line|#define esp_stp     esp_sstep   /* wo  Transfer period per sync       0x18   */
id|EREGS_PAD
c_func
(paren
id|ffpad
)paren
suffix:semicolon
DECL|member|esp_fflags
r_volatile
id|unchar
id|esp_fflags
suffix:semicolon
multiline_comment|/* ro  Bits of current FIFO info      0x1c   */
DECL|macro|esp_soff
mdefine_line|#define esp_soff    esp_fflags  /* wo  Sync offset                    0x1c   */
id|EREGS_PAD
c_func
(paren
id|cf1pd
)paren
suffix:semicolon
DECL|member|esp_cfg1
r_volatile
id|unchar
id|esp_cfg1
suffix:semicolon
multiline_comment|/* rw  First configuration register   0x20   */
id|EREGS_PAD
c_func
(paren
id|cfpad
)paren
suffix:semicolon
DECL|member|esp_cfact
r_volatile
id|unchar
id|esp_cfact
suffix:semicolon
multiline_comment|/* wo  Clock conversion factor        0x24   */
DECL|macro|esp_status2
mdefine_line|#define esp_status2 esp_cfact   /* ro  HME status2 register           0x24   */
id|EREGS_PAD
c_func
(paren
id|ctpad
)paren
suffix:semicolon
DECL|member|esp_ctest
r_volatile
id|unchar
id|esp_ctest
suffix:semicolon
multiline_comment|/* wo  Chip test register             0x28   */
id|EREGS_PAD
c_func
(paren
id|cf2pd
)paren
suffix:semicolon
DECL|member|esp_cfg2
r_volatile
id|unchar
id|esp_cfg2
suffix:semicolon
multiline_comment|/* rw  Second configuration register  0x2c   */
id|EREGS_PAD
c_func
(paren
id|cf3pd
)paren
suffix:semicolon
multiline_comment|/* The following is only found on the 53C9X series SCSI chips */
DECL|member|esp_cfg3
r_volatile
id|unchar
id|esp_cfg3
suffix:semicolon
multiline_comment|/* rw  Third configuration register   0x30  */
id|EREGS_PAD
c_func
(paren
id|holep
)paren
suffix:semicolon
DECL|member|esp_hole
r_volatile
id|unchar
id|esp_hole
suffix:semicolon
multiline_comment|/* hole in register map               0x34  */
id|EREGS_PAD
c_func
(paren
id|thpd
)paren
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
DECL|macro|fas_rlo
mdefine_line|#define fas_rlo     esp_tchi    /* rw  HME extended counter           0x38  */
id|EREGS_PAD
c_func
(paren
id|fgpad
)paren
suffix:semicolon
DECL|member|esp_fgrnd
r_volatile
id|unchar
id|esp_fgrnd
suffix:semicolon
multiline_comment|/* rw  Data base for fifo             0x3c  */
DECL|macro|fas_rhi
mdefine_line|#define fas_rhi     esp_fgrnd   /* rw  HME extended counter           0x3c  */
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
multiline_comment|/* NCR53C90 - very broken */
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
DECL|enumerator|fashme
id|fashme
op_assign
l_int|0x06
comma
DECL|enumerator|fas216
id|fas216
op_assign
l_int|0x07
comma
DECL|enumerator|espunknown
id|espunknown
op_assign
l_int|0x08
)brace
suffix:semicolon
multiline_comment|/* We get one of these for each ESP probed. */
DECL|struct|NCR_ESP
r_struct
id|NCR_ESP
(brace
DECL|member|next
r_struct
id|NCR_ESP
op_star
id|next
suffix:semicolon
multiline_comment|/* Next ESP on probed or NULL */
DECL|member|eregs
r_struct
id|ESP_regs
op_star
id|eregs
suffix:semicolon
multiline_comment|/* All esp registers */
DECL|member|dma
r_struct
id|Linux_DMA
op_star
id|dma
suffix:semicolon
multiline_comment|/* Who I do transfers with. */
DECL|member|dregs
r_void
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
r_void
op_star
id|edev
suffix:semicolon
multiline_comment|/* Pointer to controller base/SBus */
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
multiline_comment|/* Unique per-ESP ID number */
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
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Copy of the 3rd config register */
multiline_comment|/* The current command we are sending to the ESP chip.  This esp_command&n;   * ptr needs to be mapped in DVMA area so we can send commands and read&n;   * from the ESP fifo without burning precious CPU cycles.  Programmed I/O&n;   * sucks when we have the DVMA to do it for us.  The ESP is stupid and will&n;   * only send out 6, 10, and 12 byte SCSI commands, others we need to send&n;   * one byte at a time.  esp_slowcmd being set says that we are doing one&n;   * of the command types ESP doesn&squot;t understand, esp_scmdp keeps track of&n;   * which byte we are sending, esp_scmdleft says how many bytes to go.&n;   */
DECL|member|esp_command
r_volatile
id|unchar
op_star
id|esp_command
suffix:semicolon
multiline_comment|/* Location of command (CPU view)  */
DECL|member|esp_command_dvma
id|__u32
id|esp_command_dvma
suffix:semicolon
multiline_comment|/* Location of command (DVMA view) */
DECL|member|esp_clen
r_int
r_char
id|esp_clen
suffix:semicolon
multiline_comment|/* Length of this command */
DECL|member|esp_slowcmd
r_int
r_char
id|esp_slowcmd
suffix:semicolon
DECL|member|esp_scmdp
r_int
r_char
op_star
id|esp_scmdp
suffix:semicolon
DECL|member|esp_scmdleft
r_int
r_char
id|esp_scmdleft
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
DECL|member|sreg2
id|unchar
id|sreg2
suffix:semicolon
multiline_comment|/* Copy of HME status2 register */
multiline_comment|/* The HME is the biggest piece of shit I have ever seen. */
DECL|member|hme_fifo_workaround_buffer
id|unchar
id|hme_fifo_workaround_buffer
(braket
l_int|16
op_star
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 16-bit/entry fifo for wide scsi */
DECL|member|hme_fifo_workaround_count
id|unchar
id|hme_fifo_workaround_count
suffix:semicolon
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
DECL|member|radelay
r_int
r_int
id|radelay
suffix:semicolon
multiline_comment|/* FAST chip req/ack delay */
DECL|member|neg_defp
r_int
r_int
id|neg_defp
suffix:semicolon
multiline_comment|/* Default negotiation period */
DECL|member|sync_defp
r_int
r_int
id|sync_defp
suffix:semicolon
multiline_comment|/* Default sync transfer period */
DECL|member|max_period
r_int
r_int
id|max_period
suffix:semicolon
multiline_comment|/* longest our period can be */
DECL|member|min_period
r_int
r_int
id|min_period
suffix:semicolon
multiline_comment|/* shortest period we can withstand */
DECL|member|ccf
r_int
r_char
id|ccf
suffix:semicolon
multiline_comment|/* Clock conversion factor */
multiline_comment|/* For slow to medium speed input clock rates we shoot for 5mb/s,&n;   * but for high input clock rates we try to do 10mb/s although I&n;   * don&squot;t think a transfer can even run that fast with an ESP even&n;   * with DMA2 scatter gather pipelining.&n;   */
DECL|macro|SYNC_DEFP_SLOW
mdefine_line|#define SYNC_DEFP_SLOW            0x32   /* 5mb/s  */
DECL|macro|SYNC_DEFP_FAST
mdefine_line|#define SYNC_DEFP_FAST            0x19   /* 10mb/s */
DECL|member|snip
r_int
r_int
id|snip
suffix:semicolon
multiline_comment|/* Sync. negotiation in progress */
DECL|member|wnip
r_int
r_int
id|wnip
suffix:semicolon
multiline_comment|/* WIDE negotiation in progress */
DECL|member|targets_present
r_int
r_int
id|targets_present
suffix:semicolon
multiline_comment|/* targets spoken to before */
DECL|member|current_transfer_size
r_int
id|current_transfer_size
suffix:semicolon
multiline_comment|/* Set at beginning of data dma */
DECL|member|espcmdlog
id|unchar
id|espcmdlog
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Log of current esp cmds sent. */
DECL|member|espcmdent
id|unchar
id|espcmdent
suffix:semicolon
multiline_comment|/* Current entry in esp cmd log. */
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
multiline_comment|/* Differential SCSI bus? */
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
multiline_comment|/* Message goo */
DECL|member|cur_msgout
id|unchar
id|cur_msgout
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|cur_msgin
id|unchar
id|cur_msgin
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|prevmsgout
DECL|member|prevmsgin
id|unchar
id|prevmsgout
comma
id|prevmsgin
suffix:semicolon
DECL|member|msgout_len
DECL|member|msgin_len
id|unchar
id|msgout_len
comma
id|msgin_len
suffix:semicolon
DECL|member|msgout_ctr
DECL|member|msgin_ctr
id|unchar
id|msgout_ctr
comma
id|msgin_ctr
suffix:semicolon
multiline_comment|/* States that we cannot keep in the per cmd structure because they&n;   * cannot be assosciated with any specific command.&n;   */
DECL|member|resetting_bus
id|unchar
id|resetting_bus
suffix:semicolon
DECL|member|do_pio_cmds
id|unchar
id|do_pio_cmds
suffix:semicolon
multiline_comment|/* Do command transfer with pio */
multiline_comment|/* Functions handling DMA&n;   */
multiline_comment|/* Required functions */
DECL|member|dma_bytes_sent
r_int
(paren
op_star
id|dma_bytes_sent
)paren
(paren
r_struct
id|NCR_ESP
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|dma_can_transfer
r_int
(paren
op_star
id|dma_can_transfer
)paren
(paren
r_struct
id|NCR_ESP
op_star
comma
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
DECL|member|dma_dump_state
r_void
(paren
op_star
id|dma_dump_state
)paren
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
DECL|member|dma_init_read
r_void
(paren
op_star
id|dma_init_read
)paren
(paren
r_struct
id|NCR_ESP
op_star
comma
id|__u32
comma
r_int
)paren
suffix:semicolon
DECL|member|dma_init_write
r_void
(paren
op_star
id|dma_init_write
)paren
(paren
r_struct
id|NCR_ESP
op_star
comma
id|__u32
comma
r_int
)paren
suffix:semicolon
DECL|member|dma_ints_off
r_void
(paren
op_star
id|dma_ints_off
)paren
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
DECL|member|dma_ints_on
r_void
(paren
op_star
id|dma_ints_on
)paren
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
DECL|member|dma_irq_p
r_int
(paren
op_star
id|dma_irq_p
)paren
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
DECL|member|dma_ports_p
r_int
(paren
op_star
id|dma_ports_p
)paren
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
DECL|member|dma_setup
r_void
(paren
op_star
id|dma_setup
)paren
(paren
r_struct
id|NCR_ESP
op_star
comma
id|__u32
comma
r_int
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* Optional functions (i.e. may be initialized to 0) */
DECL|member|dma_barrier
r_void
(paren
op_star
id|dma_barrier
)paren
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
DECL|member|dma_drain
r_void
(paren
op_star
id|dma_drain
)paren
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
DECL|member|dma_invalidate
r_void
(paren
op_star
id|dma_invalidate
)paren
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
DECL|member|dma_irq_entry
r_void
(paren
op_star
id|dma_irq_entry
)paren
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
DECL|member|dma_irq_exit
r_void
(paren
op_star
id|dma_irq_exit
)paren
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
DECL|member|dma_led_off
r_void
(paren
op_star
id|dma_led_off
)paren
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
DECL|member|dma_led_on
r_void
(paren
op_star
id|dma_led_on
)paren
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
DECL|member|dma_poll
r_void
(paren
op_star
id|dma_poll
)paren
(paren
r_struct
id|NCR_ESP
op_star
comma
r_int
r_char
op_star
)paren
suffix:semicolon
DECL|member|dma_reset
r_void
(paren
op_star
id|dma_reset
)paren
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
multiline_comment|/* Optional virtual DMA functions */
DECL|member|dma_mmu_get_scsi_one
r_void
(paren
op_star
id|dma_mmu_get_scsi_one
)paren
(paren
r_struct
id|NCR_ESP
op_star
comma
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
DECL|member|dma_mmu_get_scsi_sgl
r_void
(paren
op_star
id|dma_mmu_get_scsi_sgl
)paren
(paren
r_struct
id|NCR_ESP
op_star
comma
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
DECL|member|dma_mmu_release_scsi_one
r_void
(paren
op_star
id|dma_mmu_release_scsi_one
)paren
(paren
r_struct
id|NCR_ESP
op_star
comma
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
DECL|member|dma_mmu_release_scsi_sgl
r_void
(paren
op_star
id|dma_mmu_release_scsi_sgl
)paren
(paren
r_struct
id|NCR_ESP
op_star
comma
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
DECL|member|dma_advance_sg
r_void
(paren
op_star
id|dma_advance_sg
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
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
mdefine_line|#define ESP_CONFIG2_DMAPARITY 0x01             /* enable DMA Parity (200,236) */
DECL|macro|ESP_CONFIG2_REGPARITY
mdefine_line|#define ESP_CONFIG2_REGPARITY 0x02             /* enable reg Parity (200,236) */
DECL|macro|ESP_CONFIG2_BADPARITY
mdefine_line|#define ESP_CONFIG2_BADPARITY 0x04             /* Bad parity target abort  */
DECL|macro|ESP_CONFIG2_SCSI2ENAB
mdefine_line|#define ESP_CONFIG2_SCSI2ENAB 0x08             /* Enable SCSI-2 features (tmode only) */
DECL|macro|ESP_CONFIG2_HI
mdefine_line|#define ESP_CONFIG2_HI        0x10             /* High Impedance DREQ ???  */
DECL|macro|ESP_CONFIG2_HMEFENAB
mdefine_line|#define ESP_CONFIG2_HMEFENAB  0x10             /* HME features enable */
DECL|macro|ESP_CONFIG2_BCM
mdefine_line|#define ESP_CONFIG2_BCM       0x20             /* Enable byte-ctrl (236)   */
DECL|macro|ESP_CONFIG2_DISPINT
mdefine_line|#define ESP_CONFIG2_DISPINT   0x20             /* Disable pause irq (hme) */
DECL|macro|ESP_CONFIG2_FENAB
mdefine_line|#define ESP_CONFIG2_FENAB     0x40             /* Enable features (fas100,esp216)      */
DECL|macro|ESP_CONFIG2_SPL
mdefine_line|#define ESP_CONFIG2_SPL       0x40             /* Enable status-phase latch (esp236)   */
DECL|macro|ESP_CONFIG2_MKDONE
mdefine_line|#define ESP_CONFIG2_MKDONE    0x40             /* HME magic feature */
DECL|macro|ESP_CONFIG2_HME32
mdefine_line|#define ESP_CONFIG2_HME32     0x80             /* HME 32 extended */
DECL|macro|ESP_CONFIG2_MAGIC
mdefine_line|#define ESP_CONFIG2_MAGIC     0xe0             /* Invalid bits... */
multiline_comment|/* ESP config register 3 read-write, found only esp236+fas236+fas100a+hme chips */
DECL|macro|ESP_CONFIG3_FCLOCK
mdefine_line|#define ESP_CONFIG3_FCLOCK    0x01             /* FAST SCSI clock rate (esp100a/hme) */
DECL|macro|ESP_CONFIG3_TEM
mdefine_line|#define ESP_CONFIG3_TEM       0x01             /* Enable thresh-8 mode (esp/fas236)  */
DECL|macro|ESP_CONFIG3_FAST
mdefine_line|#define ESP_CONFIG3_FAST      0x02             /* Enable FAST SCSI     (esp100a/hme) */
DECL|macro|ESP_CONFIG3_ADMA
mdefine_line|#define ESP_CONFIG3_ADMA      0x02             /* Enable alternate-dma (esp/fas236)  */
DECL|macro|ESP_CONFIG3_TENB
mdefine_line|#define ESP_CONFIG3_TENB      0x04             /* group2 SCSI2 support (esp100a/hme) */
DECL|macro|ESP_CONFIG3_SRB
mdefine_line|#define ESP_CONFIG3_SRB       0x04             /* Save residual byte   (esp/fas236)  */
DECL|macro|ESP_CONFIG3_TMS
mdefine_line|#define ESP_CONFIG3_TMS       0x08             /* Three-byte msg&squot;s ok  (esp100a/hme) */
DECL|macro|ESP_CONFIG3_FCLK
mdefine_line|#define ESP_CONFIG3_FCLK      0x08             /* Fast SCSI clock rate (esp/fas236)  */
DECL|macro|ESP_CONFIG3_IDMSG
mdefine_line|#define ESP_CONFIG3_IDMSG     0x10             /* ID message checking  (esp100a/hme) */
DECL|macro|ESP_CONFIG3_FSCSI
mdefine_line|#define ESP_CONFIG3_FSCSI     0x10             /* Enable FAST SCSI     (esp/fas236)  */
DECL|macro|ESP_CONFIG3_GTM
mdefine_line|#define ESP_CONFIG3_GTM       0x20             /* group2 SCSI2 support (esp/fas236)  */
DECL|macro|ESP_CONFIG3_BIGID
mdefine_line|#define ESP_CONFIG3_BIGID     0x20             /* SCSI-ID&squot;s are 4bits  (hme)         */
DECL|macro|ESP_CONFIG3_TBMS
mdefine_line|#define ESP_CONFIG3_TBMS      0x40             /* Three-byte msg&squot;s ok  (esp/fas236)  */
DECL|macro|ESP_CONFIG3_EWIDE
mdefine_line|#define ESP_CONFIG3_EWIDE     0x40             /* Enable Wide-SCSI     (hme)         */
DECL|macro|ESP_CONFIG3_IMS
mdefine_line|#define ESP_CONFIG3_IMS       0x80             /* ID msg chk&squot;ng        (esp/fas236)  */
DECL|macro|ESP_CONFIG3_OBPUSH
mdefine_line|#define ESP_CONFIG3_OBPUSH    0x80             /* Push odd-byte to dma (hme)         */
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
multiline_comment|/* HME only: status 2 register */
DECL|macro|ESP_STAT2_SCHBIT
mdefine_line|#define ESP_STAT2_SCHBIT      0x01 /* Upper bits 3-7 of sstep enabled */
DECL|macro|ESP_STAT2_FFLAGS
mdefine_line|#define ESP_STAT2_FFLAGS      0x02 /* The fifo flags are now latched */
DECL|macro|ESP_STAT2_XCNT
mdefine_line|#define ESP_STAT2_XCNT        0x04 /* The transfer counter is latched */
DECL|macro|ESP_STAT2_CREGA
mdefine_line|#define ESP_STAT2_CREGA       0x08 /* The command reg is active now */
DECL|macro|ESP_STAT2_WIDE
mdefine_line|#define ESP_STAT2_WIDE        0x10 /* Interface on this adapter is wide */
DECL|macro|ESP_STAT2_F1BYTE
mdefine_line|#define ESP_STAT2_F1BYTE      0x20 /* There is one byte at top of fifo */
DECL|macro|ESP_STAT2_FMSB
mdefine_line|#define ESP_STAT2_FMSB        0x40 /* Next byte in fifo is most significant */
DECL|macro|ESP_STAT2_FEMPTY
mdefine_line|#define ESP_STAT2_FEMPTY      0x80 /* FIFO is empty */
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
DECL|macro|ESP_STEP_FINI4
mdefine_line|#define ESP_STEP_FINI4        0x04             /* Command was sent ok */
multiline_comment|/* Ho hum, some ESP&squot;s set the step register to this as well... */
DECL|macro|ESP_STEP_FINI5
mdefine_line|#define ESP_STEP_FINI5        0x05
DECL|macro|ESP_STEP_FINI6
mdefine_line|#define ESP_STEP_FINI6        0x06
DECL|macro|ESP_STEP_FINI7
mdefine_line|#define ESP_STEP_FINI7        0x07
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
DECL|macro|ESP_FF_ONOTZERO
mdefine_line|#define ESP_FF_ONOTZERO       0x20             /* offset ctr not zero (esp100) */
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
multiline_comment|/* HME only... */
DECL|macro|ESP_BUSID_RESELID
mdefine_line|#define ESP_BUSID_RESELID     0x10
DECL|macro|ESP_BUSID_CTR32BIT
mdefine_line|#define ESP_BUSID_CTR32BIT    0x40
DECL|macro|ESP_BUS_TIMEOUT
mdefine_line|#define ESP_BUS_TIMEOUT        275             /* In milli-seconds */
DECL|macro|ESP_TIMEO_CONST
mdefine_line|#define ESP_TIMEO_CONST       8192
DECL|macro|ESP_NEG_DEFP
mdefine_line|#define ESP_NEG_DEFP(mhz, cfact) &bslash;&n;        ((ESP_BUS_TIMEOUT * ((mhz) / 1000)) / (8192 * (cfact)))
DECL|macro|ESP_MHZ_TO_CYCLE
mdefine_line|#define ESP_MHZ_TO_CYCLE(mhertz)  ((1000000000) / ((mhertz) / 1000))
DECL|macro|ESP_TICK
mdefine_line|#define ESP_TICK(ccf, cycle)  ((7682 * (ccf) * (cycle) / 1000))
r_extern
r_struct
id|proc_dir_entry
id|proc_scsi_esp
suffix:semicolon
multiline_comment|/* UGLY, UGLY, UGLY! */
r_extern
r_int
id|nesps
comma
id|esps_in_use
comma
id|esps_running
suffix:semicolon
multiline_comment|/* For our interrupt engine. */
DECL|macro|for_each_esp
mdefine_line|#define for_each_esp(esp) &bslash;&n;        for((esp) = espchain; (esp); (esp) = (esp)-&gt;next)
multiline_comment|/* External functions */
r_extern
r_inline
r_void
id|esp_cmd
c_func
(paren
r_struct
id|NCR_ESP
op_star
id|esp
comma
r_struct
id|ESP_regs
op_star
id|eregs
comma
id|unchar
id|cmd
)paren
suffix:semicolon
r_extern
r_struct
id|NCR_ESP
op_star
id|esp_allocate
c_func
(paren
id|Scsi_Host_Template
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|esp_initialize
c_func
(paren
r_struct
id|NCR_ESP
op_star
)paren
suffix:semicolon
r_extern
r_void
id|esp_intr
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
macro_line|#endif /* !(NCR53C9X_H) */
eof
