multiline_comment|/********************************************************&n;* Header file for eata_dma.c Linux EATA-DMA SCSI driver *&n;* (c) 1993,94,95 Michael Neuffer                        *&n;*********************************************************&n;* last change: 95/01/30                                 *&n;********************************************************/
macro_line|#ifndef _EATA_DMA_H
DECL|macro|_EATA_DMA_H
mdefine_line|#define _EATA_DMA_H
macro_line|#include &quot;../block/blk.h&quot;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &lt;linux/scsicam.h&gt;
DECL|macro|VER_MAJOR
mdefine_line|#define VER_MAJOR 2
DECL|macro|VER_MINOR
mdefine_line|#define VER_MINOR 3
DECL|macro|VER_SUB
mdefine_line|#define VER_SUB   &quot;0a&quot;
multiline_comment|/************************************************************************&n; * Here you can configure your drives that are using a non-standard     *&n; * geometry.                                                            *&n; * To enable this set HARDCODED to 1                                    *&n; * If you have only one drive that need reconfiguration, set ID1 to -1  *&n; ************************************************************************/
DECL|macro|HARDCODED
mdefine_line|#define HARDCODED     0          /* Here are drives running in emu. mode   */
DECL|macro|ID0
mdefine_line|#define ID0           0          /* SCSI ID of &quot;IDE&quot; drive mapped to C:    &n;                                  * If you&squot;re not sure check your config&n;&t;&t;&t;&t;  * utility that came with your controller&n;&t;&t;&t;&t;  */
DECL|macro|HEADS0
mdefine_line|#define HEADS0       13          /* Number of emulated heads of this drive */  
DECL|macro|SECTORS0
mdefine_line|#define SECTORS0     38          /* Number of emulated sectors             */ 
DECL|macro|CYLINDER0
mdefine_line|#define CYLINDER0   719          /* Number of emulated cylinders           */
DECL|macro|ID1
mdefine_line|#define ID1           1          /* SCSI ID of &quot;IDE&quot; drive mapped to D:    */
DECL|macro|HEADS1
mdefine_line|#define HEADS1       16          /* Number of emulated heads of this drive */ 
DECL|macro|SECTORS1
mdefine_line|#define SECTORS1     62          /* Number of emulated sectors             */
DECL|macro|CYLINDER1
mdefine_line|#define CYLINDER1  1024          /* Number of emulated cylinders           */
multiline_comment|/************************************************************************&n; * Here you can switch parts of the code on and of                      *&n; ************************************************************************/
DECL|macro|CHECKPAL
mdefine_line|#define CHECKPAL        0        /* EISA pal checking on/off            */
multiline_comment|/************************************************************************&n; * Debug options.                                                       * &n; * Enable DEBUG and whichever options you require.                      *&n; ************************************************************************/
DECL|macro|DEBUG_EATA
mdefine_line|#define DEBUG_EATA&t;1&t;/* Enable debug code. &t;&t;&t;*/
DECL|macro|DPT_DEBUG
mdefine_line|#define DPT_DEBUG       0       /* Bobs special                         */
DECL|macro|DBG_DELAY
mdefine_line|#define DBG_DELAY       0&t;/* Build in delays so debug messages can be&n;&t;&t;&t;&t; * be read before they vanish of the top of&n;&t;&t;&t;&t; * the screen!&n;&t;&t;&t;&t; */
DECL|macro|DBG_PROBE
mdefine_line|#define DBG_PROBE&t;0&t;/* Debug probe routines. &t;&t;*/
DECL|macro|DBG_PCI
mdefine_line|#define DBG_PCI         0       /* Trace PCI routines                   */
DECL|macro|DBG_EISA
mdefine_line|#define DBG_EISA        0       /* Trace EISA routines                  */
DECL|macro|DBG_ISA
mdefine_line|#define DBG_ISA         0       /* Trace ISA routines                   */ 
DECL|macro|DBG_BLINK
mdefine_line|#define DBG_BLINK       0       /* Trace Blink check                    */
DECL|macro|DBG_PIO
mdefine_line|#define DBG_PIO         0       /* Trace get_config_PIO                 */
DECL|macro|DBG_COM
mdefine_line|#define DBG_COM &t;0&t;/* Trace command call   &t;&t;*/
DECL|macro|DBG_QUEUE
mdefine_line|#define DBG_QUEUE&t;0&t;/* Trace command queueing. &t;&t;*/
DECL|macro|DBG_INTR
mdefine_line|#define DBG_INTR&t;0       /* Trace interrupt service routine. &t;*/
DECL|macro|DBG_INTR2
mdefine_line|#define DBG_INTR2&t;0       /* Trace interrupt service routine. &t;*/
DECL|macro|DBG_PROC
mdefine_line|#define DBG_PROC        0       /* Debug proc-fs related statistics     */
DECL|macro|DBG_REGISTER
mdefine_line|#define DBG_REGISTER    0       /* */
DECL|macro|DBG_ABNORM
mdefine_line|#define DBG_ABNORM&t;1&t;/* Debug abnormal actions (reset, abort)*/
macro_line|#if DEBUG_EATA 
DECL|macro|DBG
mdefine_line|#define DBG(x, y)&t;if ((x)) {y;} 
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x, y)
macro_line|#endif
DECL|macro|EATA_DMA
mdefine_line|#define EATA_DMA {                   &bslash;&n;&t;NULL, NULL,                  &bslash;&n;        &quot;EATA (Extended Attachment) driver&quot;, &bslash;&n;        eata_detect,                 &bslash;&n;        eata_release,                &bslash;&n;        eata_info,                   &bslash;&n;        eata_command,                &bslash;&n;        eata_queue,                  &bslash;&n;        eata_abort,                  &bslash;&n;        eata_reset,                  &bslash;&n;        NULL, /* Slave attach */     &bslash;&n;&t;scsicam_bios_param,          &bslash;&n;        0,      /* Canqueue     */   &bslash;&n;        0,      /* this_id      */   &bslash;&n;        0,      /* sg_tablesize */   &bslash;&n;        0,      /* cmd_per_lun  */   &bslash;&n;        0,      /* present      */   &bslash;&n;        1,      /* True if ISA  */   &bslash;&n;&t;ENABLE_CLUSTERING }
r_int
id|eata_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_const
r_char
op_star
id|eata_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|eata_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|eata_queue
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_void
op_star
(paren
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_int
id|eata_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|eata_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|eata_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
multiline_comment|/*********************************************&n; * Misc. definitions                         *&n; *********************************************/
macro_line|#ifndef TRUE
DECL|macro|TRUE
macro_line|# define TRUE 1
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
macro_line|# define FALSE 0
macro_line|#endif
DECL|macro|R_LIMIT
mdefine_line|#define R_LIMIT 0x20000
DECL|macro|MAXISA
mdefine_line|#define MAXISA     4
DECL|macro|MAXEISA
mdefine_line|#define MAXEISA   16  
DECL|macro|MAXPCI
mdefine_line|#define MAXPCI    16
DECL|macro|MAXIRQ
mdefine_line|#define MAXIRQ    16 
DECL|macro|MAXTARGET
mdefine_line|#define MAXTARGET  8
DECL|macro|MAX_PCI_DEVICES
mdefine_line|#define MAX_PCI_DEVICES   32             /* Maximum # Of Devices Per Bus   */
DECL|macro|MAX_METHOD_2
mdefine_line|#define MAX_METHOD_2      16             /* Max Devices For Method 2       */
DECL|macro|MAX_PCI_BUS
mdefine_line|#define MAX_PCI_BUS       16             /* Maximum # Of Busses Allowed    */
DECL|macro|SG_SIZE
mdefine_line|#define SG_SIZE           64 
DECL|macro|C_P_L_CURRENT_MAX
mdefine_line|#define C_P_L_CURRENT_MAX 10  /* Until this limit in the mm is removed    &n;&t;&t;&t;       * Kernels &lt; 1.1.86 died horrible deaths&n;&t;&t;&t;       * if you used values &gt;2. The memory management&n;&t;&t;&t;       * of pl.86 seems to cope with 10. &n;&t;&t;&t;       */
DECL|macro|C_P_L_DIV
mdefine_line|#define C_P_L_DIV          4  /* 1 &lt;= C_P_L_DIV &lt;= 8            &n;&t;&t;&t;       * You can use this parameter to fine-tune&n;&t;&t;&t;       * the driver. Depending on the number of &n;&t;&t;&t;       * devices and their ability to queue commands&n;&t;&t;&t;       * you will get the best results with a value&n;&t;&t;&t;       * ~= numdevices-(devices_unable_to_queue_commands/2)&n;&t;&t;&t;       * The reason for this is that the disk driver tents &n;&t;&t;&t;       * to flood the queue, so that other drivers have &n;&t;&t;&t;       * problems to queue commands themselves. This can &n;&t;&t;&t;       * for example result in the effect that the tape&n;&t;&t;&t;       * stops during disk accesses. &n;&t;&t;&t;       */
DECL|macro|FREE
mdefine_line|#define FREE       0
DECL|macro|USED
mdefine_line|#define USED       1
DECL|macro|TIMEOUT
mdefine_line|#define TIMEOUT    2
DECL|macro|RESET
mdefine_line|#define RESET      4
DECL|macro|LOCKED
mdefine_line|#define LOCKED     8
DECL|macro|HD
mdefine_line|#define HD(cmd)  ((hostdata *)&amp;(cmd-&gt;host-&gt;hostdata))
DECL|macro|CD
mdefine_line|#define CD(cmd)  ((struct eata_ccb *)(cmd-&gt;host_scribble))
DECL|macro|SD
mdefine_line|#define SD(host) ((hostdata *)&amp;(host-&gt;hostdata))
DECL|macro|DELAY
mdefine_line|#define DELAY(x) { int i; i = jiffies + x; while (jiffies &lt; i); }
DECL|macro|DEL2
mdefine_line|#define DEL2(x)  { ulong i; for (i = 0; i &lt; 0xffff*x; i++); }
multiline_comment|/***********************************************&n; *    EATA Command &amp; Register definitions      *&n; ***********************************************/
DECL|macro|PCI_REG_DPTconfig
mdefine_line|#define PCI_REG_DPTconfig        0x40    
DECL|macro|PCI_REG_PumpModeAddress
mdefine_line|#define PCI_REG_PumpModeAddress  0x44    
DECL|macro|PCI_REG_PumpModeData
mdefine_line|#define PCI_REG_PumpModeData     0x48    
DECL|macro|PCI_REG_ConfigParam1
mdefine_line|#define PCI_REG_ConfigParam1     0x50    
DECL|macro|PCI_REG_ConfigParam2
mdefine_line|#define PCI_REG_ConfigParam2     0x54    
DECL|macro|EATA_CMD_PIO_READ_CONFIG
mdefine_line|#define EATA_CMD_PIO_READ_CONFIG 0xf0
DECL|macro|EATA_CMD_PIO_SET_CONFIG
mdefine_line|#define EATA_CMD_PIO_SET_CONFIG  0xf1
DECL|macro|EATA_CMD_PIO_SEND_CP
mdefine_line|#define EATA_CMD_PIO_SEND_CP     0xf2
DECL|macro|EATA_CMD_PIO_RECEIVE_SP
mdefine_line|#define EATA_CMD_PIO_RECEIVE_SP  0xf3
DECL|macro|EATA_CMD_PIO_TRUNC
mdefine_line|#define EATA_CMD_PIO_TRUNC       0xf4
DECL|macro|EATA_CMD_RESET
mdefine_line|#define EATA_CMD_RESET           0xf9
DECL|macro|EATA_CMD_DMA_READ_CONFIG
mdefine_line|#define EATA_CMD_DMA_READ_CONFIG 0xfd
DECL|macro|EATA_CMD_DMA_SET_CONFIG
mdefine_line|#define EATA_CMD_DMA_SET_CONFIG  0xfe
DECL|macro|EATA_CMD_DMA_SEND_CP
mdefine_line|#define EATA_CMD_DMA_SEND_CP     0xff
DECL|macro|ECS_EMULATE_SENSE
mdefine_line|#define ECS_EMULATE_SENSE        0xd4
DECL|macro|HA_WCOMMAND
mdefine_line|#define HA_WCOMMAND 0x07        /* command register offset   */
DECL|macro|HA_WDMAADDR
mdefine_line|#define HA_WDMAADDR 0x02        /* DMA address LSB offset    */  
DECL|macro|HA_RAUXSTAT
mdefine_line|#define HA_RAUXSTAT 0x08        /* aux status register offset*/
DECL|macro|HA_RSTATUS
mdefine_line|#define HA_RSTATUS  0x07        /* status register offset    */
DECL|macro|HA_RDATA
mdefine_line|#define HA_RDATA    0x00        /* data register (16bit)     */
DECL|macro|HA_ABUSY
mdefine_line|#define HA_ABUSY    0x01        /* aux busy bit              */
DECL|macro|HA_AIRQ
mdefine_line|#define HA_AIRQ     0x02        /* aux IRQ pending bit       */
DECL|macro|HA_SERROR
mdefine_line|#define HA_SERROR   0x01        /* pr. command ended in error*/
DECL|macro|HA_SMORE
mdefine_line|#define HA_SMORE    0x02        /* more data soon to come    */
DECL|macro|HA_SCORR
mdefine_line|#define HA_SCORR    0x04        /* data corrected            */
DECL|macro|HA_SDRQ
mdefine_line|#define HA_SDRQ     0x08        /* data request active       */
DECL|macro|HA_SSC
mdefine_line|#define HA_SSC      0x10        /* seek complete             */
DECL|macro|HA_SFAULT
mdefine_line|#define HA_SFAULT   0x20        /* write fault               */
DECL|macro|HA_SREADY
mdefine_line|#define HA_SREADY   0x40        /* drive ready               */
DECL|macro|HA_SBUSY
mdefine_line|#define HA_SBUSY    0x80        /* drive busy                */
DECL|macro|HA_SDRDY
mdefine_line|#define HA_SDRDY    HA_SSC+HA_SREADY+HA_SDRQ 
multiline_comment|/**********************************************&n; * Message definitions                        *&n; **********************************************/
DECL|struct|reg_bit
r_struct
id|reg_bit
(brace
multiline_comment|/* reading this one will clear the interrupt &t;*/
DECL|member|error
id|unchar
id|error
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* previous command ended in an error           */
DECL|member|more
id|unchar
id|more
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* more DATA coming soon, poll BSY &amp; DRQ (PIO) */
DECL|member|corr
id|unchar
id|corr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* data read was successfully corrected with ECC*/
DECL|member|drq
id|unchar
id|drq
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* data request active  */
DECL|member|sc
id|unchar
id|sc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* seek complete        */
DECL|member|fault
id|unchar
id|fault
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* write fault          */
DECL|member|ready
id|unchar
id|ready
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* drive ready          */
DECL|member|busy
id|unchar
id|busy
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* controller busy      */
)brace
suffix:semicolon
DECL|struct|reg_abit
r_struct
id|reg_abit
(brace
multiline_comment|/* reading this won&squot;t clear the interrupt */
DECL|member|abusy
id|unchar
id|abusy
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* auxiliary busy                         */
DECL|member|irq
id|unchar
id|irq
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* set when drive interrupt is asserted   */
DECL|member|dummy
id|unchar
id|dummy
suffix:colon
l_int|6
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|eata_register
r_struct
id|eata_register
(brace
multiline_comment|/* EATA register set */
DECL|member|data_reg
id|unchar
id|data_reg
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* R, couldn&squot;t figure this one out          */
DECL|member|cp_addr
id|unchar
id|cp_addr
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* W, CP address register                   */
r_union
(brace
DECL|member|command
id|unchar
id|command
suffix:semicolon
multiline_comment|/* W, command code: [read|set] conf, send CP*/
DECL|member|status
r_struct
id|reg_bit
id|status
suffix:semicolon
multiline_comment|/* R, see register_bit1                     */
DECL|member|statusunchar
id|unchar
id|statusunchar
suffix:semicolon
DECL|member|ovr
)brace
id|ovr
suffix:semicolon
DECL|member|aux_stat
r_struct
id|reg_abit
id|aux_stat
suffix:semicolon
multiline_comment|/* R, see register_bit2               &t;    */
)brace
suffix:semicolon
multiline_comment|/**********************************************&n; *  Other  definitions                        *&n; **********************************************/
DECL|struct|eata_sg_list
r_struct
id|eata_sg_list
(brace
DECL|member|data
id|ulong
id|data
suffix:semicolon
DECL|member|len
id|ulong
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|get_conf
r_struct
id|get_conf
(brace
multiline_comment|/* Read Configuration Array  */
DECL|member|len
id|ulong
id|len
suffix:semicolon
multiline_comment|/* Should return 0x22 &t;&t;&t;*/
DECL|member|sig
id|unchar
id|sig
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Signature MUST be &quot;EATA&quot; &t;&t;*/
DECL|member|version2
id|unchar
id|version2
suffix:colon
l_int|4
comma
DECL|member|version
id|version
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* EATA Version level          &t;        */
DECL|member|OCS_enabled
id|unchar
id|OCS_enabled
suffix:colon
l_int|1
comma
multiline_comment|/* Overlap Command Support enabled  &t;*/
DECL|member|TAR_support
id|TAR_support
suffix:colon
l_int|1
comma
multiline_comment|/* SCSI Target Mode supported&t;&t;*/
DECL|member|TRNXFR
id|TRNXFR
suffix:colon
l_int|1
comma
multiline_comment|/* Truncate Transfer Cmd not necessary&t;*/
multiline_comment|/* Only used in PIO Mode &t;&t;        */
DECL|member|MORE_support
id|MORE_support
suffix:colon
l_int|1
comma
multiline_comment|/* MORE supported (only PIO Mode) &t;*/
DECL|member|DMA_support
id|DMA_support
suffix:colon
l_int|1
comma
multiline_comment|/* DMA supported Driver uses only &t;*/
multiline_comment|/* this mode&t;&t;&t;&t;*/
DECL|member|DMA_valid
id|DMA_valid
suffix:colon
l_int|1
comma
multiline_comment|/* DRQ value in Byte 30 is valid&t;        */
DECL|member|ATA
id|ATA
suffix:colon
l_int|1
comma
multiline_comment|/* ATA device connected (not supported)&t;*/
DECL|member|HAA_valid
id|HAA_valid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Hostadapter Address is valid     &t;*/
DECL|member|cppadlen
id|ushort
id|cppadlen
suffix:semicolon
multiline_comment|/* Number of pad unchars send after CD data */
multiline_comment|/* set to zero for DMA commands&t;&t;*/
DECL|member|scsi_id
id|unchar
id|scsi_id
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* SCSI ID of controller 2-0 Byte 0 res.  */
multiline_comment|/* if not, zero is returned &t;&t;*/
DECL|member|cplen
id|ulong
id|cplen
suffix:semicolon
multiline_comment|/* CP length: number of valid cp unchars &t;*/
DECL|member|splen
id|ulong
id|splen
suffix:semicolon
multiline_comment|/* Number of unchars returned after&t;*/
multiline_comment|/* Receive SP command&t;&t;&t;*/
DECL|member|queuesiz
id|ushort
id|queuesiz
suffix:semicolon
multiline_comment|/* max number of queueable CPs&t;&t;*/
DECL|member|dummy
id|ushort
id|dummy
suffix:semicolon
DECL|member|SGsiz
id|ushort
id|SGsiz
suffix:semicolon
multiline_comment|/* max number of SG table entries&t;        */
DECL|member|IRQ
id|unchar
id|IRQ
suffix:colon
l_int|4
comma
multiline_comment|/* IRQ used this HA&t;&t;&t;*/
DECL|member|IRQ_TR
id|IRQ_TR
suffix:colon
l_int|1
comma
multiline_comment|/* IRQ Trigger: 0=edge, 1=level&t;        */
DECL|member|SECOND
id|SECOND
suffix:colon
l_int|1
comma
multiline_comment|/* This is a secondary controller&t;        */
DECL|member|DMA_channel
id|DMA_channel
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* DRQ index, DRQ is 2comp of DRQX&t;*/
DECL|member|sync
id|unchar
id|sync
suffix:semicolon
multiline_comment|/* device at ID 7 tru 0 is running in &t;*/
multiline_comment|/* synchronous mode, this will disappear  */
DECL|member|DSBLE
id|unchar
id|DSBLE
suffix:colon
l_int|1
comma
multiline_comment|/* ISA i/o addressing is disabled         */
DECL|member|FORCADR
id|FORCADR
suffix:colon
l_int|1
comma
multiline_comment|/* i/o address has been forced            */
suffix:colon
l_int|6
suffix:semicolon
DECL|member|MAX_ID
id|unchar
id|MAX_ID
suffix:colon
l_int|5
comma
multiline_comment|/* Max number of SCSI target IDs          */
DECL|member|MAX_CHAN
id|MAX_CHAN
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* Number of SCSI busses on HBA           */
DECL|member|MAX_LUN
id|unchar
id|MAX_LUN
suffix:semicolon
multiline_comment|/* Max number of LUNs                     */
DECL|member|unchar
id|unchar
suffix:colon
l_int|5
comma
DECL|member|ID_qest
id|ID_qest
suffix:colon
l_int|1
comma
multiline_comment|/* Raidnum ID is questionable             */
DECL|member|is_PCI
id|is_PCI
suffix:colon
l_int|1
comma
multiline_comment|/* HBA is PCI                             */
DECL|member|is_EISA
id|is_EISA
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* HBA is EISA                            */
DECL|member|unused
id|unchar
id|unused
(braket
l_int|478
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|eata_ccb
r_struct
id|eata_ccb
(brace
multiline_comment|/* Send Command Packet structure      */
DECL|member|SCSI_Reset
id|unchar
id|SCSI_Reset
suffix:colon
l_int|1
comma
multiline_comment|/* Cause a SCSI Bus reset on the cmd  */
DECL|member|HBA_Init
id|HBA_Init
suffix:colon
l_int|1
comma
multiline_comment|/* Cause Controller to reinitialize   */
DECL|member|Auto_Req_Sen
id|Auto_Req_Sen
suffix:colon
l_int|1
comma
multiline_comment|/* Do Auto Request Sense on errors    */
DECL|member|scatter
id|scatter
suffix:colon
l_int|1
comma
multiline_comment|/* Data Ptr points to a SG Packet     */
DECL|member|Resrvd
id|Resrvd
suffix:colon
l_int|1
comma
multiline_comment|/* RFU                                */
DECL|member|Interpret
id|Interpret
suffix:colon
l_int|1
comma
multiline_comment|/* Interpret the SCSI cdb of own use  */
DECL|member|DataOut
id|DataOut
suffix:colon
l_int|1
comma
multiline_comment|/* Data Out phase with command        */
DECL|member|DataIn
id|DataIn
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Data In phase with command         */
DECL|member|reqlen
id|unchar
id|reqlen
suffix:semicolon
multiline_comment|/* Request Sense Length               */
multiline_comment|/* Valid if Auto_Req_Sen=1            */
DECL|member|unused
id|unchar
id|unused
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|FWNEST
id|unchar
id|FWNEST
suffix:colon
l_int|1
comma
multiline_comment|/* send cmd to phys RAID component*/
DECL|member|unused2
id|unused2
suffix:colon
l_int|7
suffix:semicolon
DECL|member|Phsunit
id|unchar
id|Phsunit
suffix:colon
l_int|1
comma
multiline_comment|/* physical unit on mirrored pair&t;*/
DECL|member|I_AT
id|I_AT
suffix:colon
l_int|1
comma
multiline_comment|/* inhibit address translation    */
DECL|member|I_HBA_C
id|I_HBA_C
suffix:colon
l_int|1
comma
multiline_comment|/* HBA Inhibit caching            */
DECL|member|unused3
id|unused3
suffix:colon
l_int|5
suffix:semicolon
DECL|member|cp_id
id|unchar
id|cp_id
suffix:semicolon
multiline_comment|/* SCSI Device ID of target       */
DECL|member|cp_lun
id|unchar
id|cp_lun
suffix:colon
l_int|3
comma
suffix:colon
l_int|2
comma
DECL|member|cp_luntar
id|cp_luntar
suffix:colon
l_int|1
comma
multiline_comment|/* CP is for target ROUTINE       */
DECL|member|cp_dispri
id|cp_dispri
suffix:colon
l_int|1
comma
multiline_comment|/* Grant disconnect privilege     */
DECL|member|cp_identify
id|cp_identify
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Always TRUE                    */
DECL|member|cp_msg1
id|unchar
id|cp_msg1
suffix:semicolon
multiline_comment|/* Message bytes 0-3              */
DECL|member|cp_msg2
id|unchar
id|cp_msg2
suffix:semicolon
DECL|member|cp_msg3
id|unchar
id|cp_msg3
suffix:semicolon
DECL|member|cp_cdb
id|unchar
id|cp_cdb
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* Command Descriptor Block       */
DECL|member|cp_datalen
id|ulong
id|cp_datalen
suffix:semicolon
multiline_comment|/* Data Transfer Length           */
multiline_comment|/* If scatter=1 len of sg package */
DECL|member|cp_viraddr
r_void
op_star
id|cp_viraddr
suffix:semicolon
multiline_comment|/* address of this ccb            */
DECL|member|cp_dataDMA
id|ulong
id|cp_dataDMA
suffix:semicolon
multiline_comment|/* Data Address, if scatter=1     */
multiline_comment|/* address of scatter packet      */
DECL|member|cp_statDMA
id|ulong
id|cp_statDMA
suffix:semicolon
multiline_comment|/* address for Status Packet      */
DECL|member|cp_reqDMA
id|ulong
id|cp_reqDMA
suffix:semicolon
multiline_comment|/* Request Sense Address, used if */
multiline_comment|/* CP command ends with error     */
DECL|member|timeout
id|ulong
id|timeout
suffix:semicolon
DECL|member|retries
id|unchar
id|retries
suffix:semicolon
DECL|member|status
id|unchar
id|status
suffix:semicolon
multiline_comment|/* status of this queueslot       */
DECL|member|sg_list
r_struct
id|eata_sg_list
id|sg_list
(braket
id|SG_SIZE
)braket
suffix:semicolon
DECL|member|cmd
id|Scsi_Cmnd
op_star
id|cmd
suffix:semicolon
multiline_comment|/* address of cmd                 */
)brace
suffix:semicolon
DECL|struct|eata_sp
r_struct
id|eata_sp
(brace
DECL|member|hba_stat
id|unchar
id|hba_stat
suffix:colon
l_int|7
comma
multiline_comment|/* HBA status                     */
DECL|member|EOC
id|EOC
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* True if command finished       */
DECL|member|scsi_stat
id|unchar
id|scsi_stat
suffix:semicolon
multiline_comment|/* Target SCSI status             */
DECL|member|reserved
id|unchar
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|residue_len
id|ulong
id|residue_len
suffix:semicolon
multiline_comment|/* Number of unchars not transferred */
DECL|member|ccb
r_struct
id|eata_ccb
op_star
id|ccb
suffix:semicolon
multiline_comment|/* Address set in COMMAND PACKET  */
DECL|member|msg
id|unchar
id|msg
(braket
l_int|12
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hstd
r_typedef
r_struct
id|hstd
(brace
DECL|member|vendor
r_char
id|vendor
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|18
)braket
suffix:semicolon
DECL|member|revision
r_char
id|revision
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|EATA_revision
r_char
id|EATA_revision
suffix:semicolon
DECL|member|bustype
id|unchar
id|bustype
suffix:semicolon
multiline_comment|/* bustype of HBA             */
DECL|member|channel
id|unchar
id|channel
suffix:semicolon
multiline_comment|/* no. of scsi channel        */
DECL|member|state
id|unchar
id|state
suffix:semicolon
multiline_comment|/* state of HBA               */
DECL|member|primary
id|unchar
id|primary
suffix:semicolon
multiline_comment|/* true if primary            */
DECL|member|reads
id|ulong
id|reads
(braket
l_int|13
)braket
suffix:semicolon
DECL|member|writes
id|ulong
id|writes
(braket
l_int|13
)braket
suffix:semicolon
DECL|member|t_state
id|unchar
id|t_state
(braket
id|MAXTARGET
)braket
suffix:semicolon
multiline_comment|/* state of Target (RESET,..) */
DECL|member|t_timeout
id|uint
id|t_timeout
(braket
id|MAXTARGET
)braket
suffix:semicolon
multiline_comment|/* timeouts on target         */
DECL|member|last_ccb
id|uint
id|last_ccb
suffix:semicolon
multiline_comment|/* Last used ccb              */
DECL|member|next
r_struct
id|Scsi_Host
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|Scsi_Host
op_star
id|prev
suffix:semicolon
DECL|member|sp
r_struct
id|eata_sp
id|sp
suffix:semicolon
multiline_comment|/* status packet              */
DECL|member|ccb
r_struct
id|eata_ccb
id|ccb
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* ccb array begins here      */
DECL|typedef|hostdata
)brace
id|hostdata
suffix:semicolon
multiline_comment|/* structure for max. 2 emulated drives */
DECL|struct|drive_geom_emul
r_struct
id|drive_geom_emul
(brace
DECL|member|trans
id|unchar
id|trans
suffix:semicolon
multiline_comment|/* translation flag 1=transl */
DECL|member|channel
id|unchar
id|channel
suffix:semicolon
multiline_comment|/* SCSI channel number       */
DECL|member|HBA
id|unchar
id|HBA
suffix:semicolon
multiline_comment|/* HBA number (prim/sec)     */
DECL|member|id
id|unchar
id|id
suffix:semicolon
multiline_comment|/* drive id                  */
DECL|member|lun
id|unchar
id|lun
suffix:semicolon
multiline_comment|/* drive lun                 */
DECL|member|heads
id|uint
id|heads
suffix:semicolon
multiline_comment|/* number of heads           */
DECL|member|sectors
id|uint
id|sectors
suffix:semicolon
multiline_comment|/* number of sectors         */
DECL|member|cylinder
id|uint
id|cylinder
suffix:semicolon
multiline_comment|/* number of cylinders       */
)brace
suffix:semicolon
DECL|struct|geom_emul
r_struct
id|geom_emul
(brace
DECL|member|bios_drives
r_int
id|bios_drives
suffix:semicolon
multiline_comment|/* number of emulated drives */
DECL|member|drv
r_struct
id|drive_geom_emul
id|drv
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* drive structures          */
)brace
suffix:semicolon
macro_line|#endif /* _EATA_H */
eof
