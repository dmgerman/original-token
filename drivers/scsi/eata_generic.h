multiline_comment|/********************************************************&n;* Header file for eata_dma.c and eata_pio.c             *&n;* Linux EATA SCSI drivers                               *&n;* (c) 1993,94,95 Michael Neuffer                        *&n;*********************************************************&n;* last change: 95/06/20                                 *&n;********************************************************/
macro_line|#ifndef _EATA_GENERIC_H
DECL|macro|_EATA_GENERIC_H
mdefine_line|#define _EATA_GENERIC_H
multiline_comment|/*********************************************&n; * Misc. definitions                         *&n; *********************************************/
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE 1
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
DECL|macro|min
mdefine_line|#define min(a,b) ((a&lt;b)?(a):(b))
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
mdefine_line|#define MAXTARGET 16
DECL|macro|MAXCHANNEL
mdefine_line|#define MAXCHANNEL 3
DECL|macro|IS_ISA
mdefine_line|#define IS_ISA     &squot;I&squot;
DECL|macro|IS_EISA
mdefine_line|#define IS_EISA    &squot;E&squot;
DECL|macro|IS_PCI
mdefine_line|#define IS_PCI     &squot;P&squot;
DECL|macro|BROKEN_INQUIRY
mdefine_line|#define BROKEN_INQUIRY  1
DECL|macro|EATA_SIGNATURE
mdefine_line|#define EATA_SIGNATURE  0x45415441     /* BIG ENDIAN coded &quot;EATA&quot; sig.   */
DECL|macro|EATA_CP_SIZE
mdefine_line|#define EATA_CP_SIZE    44
DECL|macro|MAX_PCI_DEVICES
mdefine_line|#define MAX_PCI_DEVICES 32             /* Maximum # Of Devices Per Bus   */
DECL|macro|MAX_METHOD_2
mdefine_line|#define MAX_METHOD_2    16             /* Max Devices For Method 2       */
DECL|macro|MAX_PCI_BUS
mdefine_line|#define MAX_PCI_BUS     16             /* Maximum # Of Busses Allowed    */
DECL|macro|SG_SIZE
mdefine_line|#define SG_SIZE         64 
DECL|macro|SG_SIZE_BIG
mdefine_line|#define SG_SIZE_BIG     509            /* max. 509 */
DECL|macro|C_P_L_DIV
mdefine_line|#define C_P_L_DIV       2 /* 1 &lt;= C_P_L_DIV &lt;= 8            &n;&t;&t;&t;   * You can use this parameter to fine-tune&n;&t;&t;&t;   * the driver. Depending on the number of &n;&t;&t;&t;   * devices and their speed and ability to queue &n;&t;&t;&t;   * commands, you will get the best results with a&n;&t;&t;&t;   * value&n;&t;&t;&t;   * ~= numdevices-(devices_unable_to_queue_commands/2)&n;&t;&t;&t;   * The reason for this is that the disk driver &n;&t;&t;&t;   * tends to flood the queue, so that other &n;&t;&t;&t;   * drivers have problems to queue commands &n;&t;&t;&t;   * themselves. This can for example result in &n;&t;&t;&t;   * the effect that the tape stops during disk &n;&t;&t;&t;   * accesses. &n;&t;&t;&t;   */
DECL|macro|FREE
mdefine_line|#define FREE       0
DECL|macro|OK
mdefine_line|#define OK         0
DECL|macro|NO_TIMEOUT
mdefine_line|#define NO_TIMEOUT 0
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
mdefine_line|#define DELAY(x) { __u32 i; i = jiffies + x; while (jiffies &lt; i); }
DECL|macro|DEL2
mdefine_line|#define DEL2(x)  { __u32 i; for (i = 0; i &lt; 0xffff * x; i++); }
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
DECL|macro|EATA_CMD_PIO_SETUPTEST
mdefine_line|#define EATA_CMD_PIO_SETUPTEST   0xc6
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
DECL|macro|EATA_CMD_IMMEDIATE
mdefine_line|#define EATA_CMD_IMMEDIATE       0xfa
DECL|macro|EATA_CMD_DMA_READ_CONFIG
mdefine_line|#define EATA_CMD_DMA_READ_CONFIG 0xfd
DECL|macro|EATA_CMD_DMA_SET_CONFIG
mdefine_line|#define EATA_CMD_DMA_SET_CONFIG  0xfe
DECL|macro|EATA_CMD_DMA_SEND_CP
mdefine_line|#define EATA_CMD_DMA_SEND_CP     0xff
DECL|macro|ECS_EMULATE_SENSE
mdefine_line|#define ECS_EMULATE_SENSE        0xd4
DECL|macro|GENERIC_ABORT
mdefine_line|#define GENERIC_ABORT  0x00 
DECL|macro|SPECIFIC_RESET
mdefine_line|#define SPECIFIC_RESET 0x01
DECL|macro|BUS_RESET
mdefine_line|#define BUS_RESET      0x02
DECL|macro|SPECIFIC_ABORT
mdefine_line|#define SPECIFIC_ABORT 0x03
DECL|macro|QUIET_INTR
mdefine_line|#define QUIET_INTR     0x04
DECL|macro|COLD_BOOT_HBA
mdefine_line|#define COLD_BOOT_HBA  0x06        /* Only as a last resort     */
DECL|macro|FORCE_IO
mdefine_line|#define FORCE_IO       0x07
DECL|macro|HA_WCOMMAND
mdefine_line|#define HA_WCOMMAND    0x07        /* command register offset   */
DECL|macro|HA_WCOMMAND2
mdefine_line|#define HA_WCOMMAND2   0x06        /* immediate command offset  */
DECL|macro|HA_WSUBCODE
mdefine_line|#define HA_WSUBCODE    0x05 
DECL|macro|HA_WSUBLUN
mdefine_line|#define HA_WSUBLUN     0x04 
DECL|macro|HA_WDMAADDR
mdefine_line|#define HA_WDMAADDR    0x02        /* DMA address LSB offset    */  
DECL|macro|HA_RAUXSTAT
mdefine_line|#define HA_RAUXSTAT    0x08        /* aux status register offset*/
DECL|macro|HA_RSTATUS
mdefine_line|#define HA_RSTATUS     0x07        /* status register offset    */
DECL|macro|HA_RDATA
mdefine_line|#define HA_RDATA       0x00        /* data register (16bit)     */
DECL|macro|HA_ABUSY
mdefine_line|#define HA_ABUSY       0x01        /* aux busy bit              */
DECL|macro|HA_AIRQ
mdefine_line|#define HA_AIRQ        0x02        /* aux IRQ pending bit       */
DECL|macro|HA_SERROR
mdefine_line|#define HA_SERROR      0x01        /* pr. command ended in error*/
DECL|macro|HA_SMORE
mdefine_line|#define HA_SMORE       0x02        /* more data soon to come    */
DECL|macro|HA_SCORR
mdefine_line|#define HA_SCORR       0x04        /* data corrected            */
DECL|macro|HA_SDRQ
mdefine_line|#define HA_SDRQ        0x08        /* data request active       */
DECL|macro|HA_SSC
mdefine_line|#define HA_SSC         0x10        /* seek complete             */
DECL|macro|HA_SFAULT
mdefine_line|#define HA_SFAULT      0x20        /* write fault               */
DECL|macro|HA_SREADY
mdefine_line|#define HA_SREADY      0x40        /* drive ready               */
DECL|macro|HA_SBUSY
mdefine_line|#define HA_SBUSY       0x80        /* drive busy                */
DECL|macro|HA_SDRDY
mdefine_line|#define HA_SDRDY       HA_SSC+HA_SREADY+HA_SDRQ 
multiline_comment|/**********************************************&n; * Message definitions                        *&n; **********************************************/
DECL|macro|HA_NO_ERROR
mdefine_line|#define HA_NO_ERROR      0x00   /* No Error                             */
DECL|macro|HA_ERR_SEL_TO
mdefine_line|#define HA_ERR_SEL_TO    0x01   /* Selection Timeout                    */
DECL|macro|HA_ERR_CMD_TO
mdefine_line|#define HA_ERR_CMD_TO    0x02   /* Command Timeout                      */
DECL|macro|HA_ERR_RESET
mdefine_line|#define HA_ERR_RESET     0x03   /* SCSI Bus Reset Received              */
DECL|macro|HA_INIT_POWERUP
mdefine_line|#define HA_INIT_POWERUP  0x04   /* Initial Controller Power-up          */
DECL|macro|HA_UNX_BUSPHASE
mdefine_line|#define HA_UNX_BUSPHASE  0x05   /* Unexpected Bus Phase                 */
DECL|macro|HA_UNX_BUS_FREE
mdefine_line|#define HA_UNX_BUS_FREE  0x06   /* Unexpected Bus Free                  */
DECL|macro|HA_BUS_PARITY
mdefine_line|#define HA_BUS_PARITY    0x07   /* Bus Parity Error                     */
DECL|macro|HA_SCSI_HUNG
mdefine_line|#define HA_SCSI_HUNG     0x08   /* SCSI Hung                            */
DECL|macro|HA_UNX_MSGRJCT
mdefine_line|#define HA_UNX_MSGRJCT   0x09   /* Unexpected Message Rejected          */
DECL|macro|HA_RESET_STUCK
mdefine_line|#define HA_RESET_STUCK   0x0a   /* SCSI Bus Reset Stuck                 */
DECL|macro|HA_RSENSE_FAIL
mdefine_line|#define HA_RSENSE_FAIL   0x0b   /* Auto Request-Sense Failed            */
DECL|macro|HA_PARITY_ERR
mdefine_line|#define HA_PARITY_ERR    0x0c   /* Controller Ram Parity Error          */
DECL|macro|HA_CP_ABORT_NA
mdefine_line|#define HA_CP_ABORT_NA   0x0d   /* Abort Message sent to non-active cmd */
DECL|macro|HA_CP_ABORTED
mdefine_line|#define HA_CP_ABORTED    0x0e   /* Abort Message sent to active cmd     */
DECL|macro|HA_CP_RESET_NA
mdefine_line|#define HA_CP_RESET_NA   0x0f   /* Reset Message sent to non-active cmd */
DECL|macro|HA_CP_RESET
mdefine_line|#define HA_CP_RESET      0x10   /* Reset Message sent to active cmd     */
DECL|macro|HA_ECC_ERR
mdefine_line|#define HA_ECC_ERR       0x11   /* Controller Ram ECC Error             */
DECL|macro|HA_PCI_PARITY
mdefine_line|#define HA_PCI_PARITY    0x12   /* PCI Parity Error                     */
DECL|macro|HA_PCI_MABORT
mdefine_line|#define HA_PCI_MABORT    0x13   /* PCI Master Abort                     */
DECL|macro|HA_PCI_TABORT
mdefine_line|#define HA_PCI_TABORT    0x14   /* PCI Target Abort                     */
DECL|macro|HA_PCI_STABORT
mdefine_line|#define HA_PCI_STABORT   0x15   /* PCI Signaled Target Abort            */
multiline_comment|/**********************************************&n; *  Other  definitions                        *&n; **********************************************/
DECL|struct|reg_bit
r_struct
id|reg_bit
(brace
multiline_comment|/* reading this one will clear the interrupt    */
DECL|member|error
id|__u8
id|error
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* previous command ended in an error           */
DECL|member|more
id|__u8
id|more
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* more DATA coming soon, poll BSY &amp; DRQ (PIO)  */
DECL|member|corr
id|__u8
id|corr
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* data read was successfully corrected with ECC*/
DECL|member|drq
id|__u8
id|drq
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* data request active  */
DECL|member|sc
id|__u8
id|sc
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* seek complete        */
DECL|member|fault
id|__u8
id|fault
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* write fault          */
DECL|member|ready
id|__u8
id|ready
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* drive ready          */
DECL|member|busy
id|__u8
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
id|__u8
id|abusy
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* auxiliary busy                         */
DECL|member|irq
id|__u8
id|irq
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* set when drive interrupt is asserted   */
DECL|member|dummy
id|__u8
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
id|__u8
id|data_reg
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* R, couldn&squot;t figure this one out          */
DECL|member|cp_addr
id|__u8
id|cp_addr
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* W, CP address register                   */
r_union
(brace
DECL|member|command
id|__u8
id|command
suffix:semicolon
multiline_comment|/* W, command code: [read|set] conf, send CP*/
DECL|member|status
r_struct
id|reg_bit
id|status
suffix:semicolon
multiline_comment|/* R, see register_bit1                 */
DECL|member|statusbyte
id|__u8
id|statusbyte
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
multiline_comment|/* R, see register_bit2                   */
)brace
suffix:semicolon
DECL|struct|get_conf
r_struct
id|get_conf
(brace
multiline_comment|/* Read Configuration Array               */
DECL|member|len
id|__u32
id|len
suffix:semicolon
multiline_comment|/* Should return 0x22, 0x24, etc          */
DECL|member|signature
id|__u32
id|signature
suffix:semicolon
multiline_comment|/* Signature MUST be &quot;EATA&quot;               */
DECL|member|version2
id|__u8
id|version2
suffix:colon
l_int|4
comma
DECL|member|version
id|version
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* EATA Version level                     */
DECL|member|OCS_enabled
id|__u8
id|OCS_enabled
suffix:colon
l_int|1
comma
multiline_comment|/* Overlap Command Support enabled        */
DECL|member|TAR_support
id|TAR_support
suffix:colon
l_int|1
comma
multiline_comment|/* SCSI Target Mode supported             */
DECL|member|TRNXFR
id|TRNXFR
suffix:colon
l_int|1
comma
multiline_comment|/* Truncate Transfer Cmd not necessary    */
multiline_comment|/* Only used in PIO Mode                  */
DECL|member|MORE_support
id|MORE_support
suffix:colon
l_int|1
comma
multiline_comment|/* MORE supported (only PIO Mode)         */
DECL|member|DMA_support
id|DMA_support
suffix:colon
l_int|1
comma
multiline_comment|/* DMA supported Driver uses only         */
multiline_comment|/* this mode                              */
DECL|member|DMA_valid
id|DMA_valid
suffix:colon
l_int|1
comma
multiline_comment|/* DRQ value in Byte 30 is valid          */
DECL|member|ATA
id|ATA
suffix:colon
l_int|1
comma
multiline_comment|/* ATA device connected (not supported)   */
DECL|member|HAA_valid
id|HAA_valid
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Hostadapter Address is valid           */
DECL|member|cppadlen
id|__u16
id|cppadlen
suffix:semicolon
multiline_comment|/* Number of pad bytes send after CD data */
multiline_comment|/* set to zero for DMA commands           */
DECL|member|scsi_id
id|__u8
id|scsi_id
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* SCSI ID of controller 2-0 Byte 0 res.  */
multiline_comment|/* if not, zero is returned               */
DECL|member|cplen
id|__u32
id|cplen
suffix:semicolon
multiline_comment|/* CP length: number of valid cp bytes    */
DECL|member|splen
id|__u32
id|splen
suffix:semicolon
multiline_comment|/* Number of bytes returned after         */
multiline_comment|/* Receive SP command                     */
DECL|member|queuesiz
id|__u16
id|queuesiz
suffix:semicolon
multiline_comment|/* max number of queueable CPs            */
DECL|member|dummy
id|__u16
id|dummy
suffix:semicolon
DECL|member|SGsiz
id|__u16
id|SGsiz
suffix:semicolon
multiline_comment|/* max number of SG table entries         */
DECL|member|IRQ
id|__u8
id|IRQ
suffix:colon
l_int|4
comma
multiline_comment|/* IRQ used this HA                       */
DECL|member|IRQ_TR
id|IRQ_TR
suffix:colon
l_int|1
comma
multiline_comment|/* IRQ Trigger: 0=edge, 1=level           */
DECL|member|SECOND
id|SECOND
suffix:colon
l_int|1
comma
multiline_comment|/* This is a secondary controller         */
DECL|member|DMA_channel
id|DMA_channel
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* DRQ index, DRQ is 2comp of DRQX        */
DECL|member|sync
id|__u8
id|sync
suffix:semicolon
multiline_comment|/* device at ID 7 tru 0 is running in     */
multiline_comment|/* synchronous mode, this will disappear  */
DECL|member|DSBLE
id|__u8
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
DECL|member|SG_64K
id|SG_64K
suffix:colon
l_int|1
comma
DECL|member|SG_UAE
id|SG_UAE
suffix:colon
l_int|1
comma
suffix:colon
l_int|4
suffix:semicolon
DECL|member|MAX_ID
id|__u8
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
id|__u8
id|MAX_LUN
suffix:semicolon
multiline_comment|/* Max number of LUNs                     */
DECL|member|__u8
id|__u8
suffix:colon
l_int|3
comma
DECL|member|AUTOTRM
id|AUTOTRM
suffix:colon
l_int|1
comma
DECL|member|M1_inst
id|M1_inst
suffix:colon
l_int|1
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
id|__u8
id|unused
(braket
l_int|478
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|eata_sg_list
r_struct
id|eata_sg_list
(brace
DECL|member|data
id|__u32
id|data
suffix:semicolon
DECL|member|len
id|__u32
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|eata_ccb
r_struct
id|eata_ccb
(brace
multiline_comment|/* Send Command Packet structure      */
DECL|member|SCSI_Reset
id|__u8
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
id|__u8
id|reqlen
suffix:semicolon
multiline_comment|/* Request Sense Length               */
multiline_comment|/* Valid if Auto_Req_Sen=1            */
DECL|member|unused
id|__u8
id|unused
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|FWNEST
id|__u8
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
id|__u8
id|Phsunit
suffix:colon
l_int|1
comma
multiline_comment|/* physical unit on mirrored pair */
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
multiline_comment|/* HBA inhibit caching            */
DECL|member|unused3
id|unused3
suffix:colon
l_int|5
suffix:semicolon
DECL|member|cp_id
id|__u8
id|cp_id
suffix:colon
l_int|5
comma
multiline_comment|/* SCSI Device ID of target       */
DECL|member|cp_channel
id|cp_channel
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* SCSI Channel # of HBA          */
DECL|member|cp_lun
id|__u8
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
id|__u8
id|cp_msg1
suffix:semicolon
multiline_comment|/* Message bytes 0-3              */
DECL|member|cp_msg2
id|__u8
id|cp_msg2
suffix:semicolon
DECL|member|cp_msg3
id|__u8
id|cp_msg3
suffix:semicolon
DECL|member|cp_cdb
id|__u8
id|cp_cdb
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* Command Descriptor Block       */
DECL|member|cp_datalen
id|__u32
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
id|__u32
id|cp_dataDMA
suffix:semicolon
multiline_comment|/* Data Address, if scatter=1     *&n;&t;&t;&t;       * address of scatter packet      */
DECL|member|cp_statDMA
id|__u32
id|cp_statDMA
suffix:semicolon
multiline_comment|/* address for Status Packet      */
DECL|member|cp_reqDMA
id|__u32
id|cp_reqDMA
suffix:semicolon
multiline_comment|/* Request Sense Address, used if */
multiline_comment|/* CP command ends with error     */
multiline_comment|/* Additional CP info begins here */
DECL|member|timeout
id|__u32
id|timeout
suffix:semicolon
DECL|member|retries
id|__u8
id|retries
suffix:semicolon
DECL|member|status
id|__u8
id|status
suffix:semicolon
multiline_comment|/* status of this queueslot       */
DECL|member|cmd
id|Scsi_Cmnd
op_star
id|cmd
suffix:semicolon
multiline_comment|/* address of cmd                 */
DECL|member|sg_list
r_struct
id|eata_sg_list
op_star
id|sg_list
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|eata_sp
r_struct
id|eata_sp
(brace
DECL|member|hba_stat
id|__u8
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
id|__u8
id|scsi_stat
suffix:semicolon
multiline_comment|/* Target SCSI status             */
DECL|member|reserved
id|__u8
id|reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|residue_len
id|__u32
id|residue_len
suffix:semicolon
multiline_comment|/* Number of bytes not transferred */
DECL|member|ccb
r_struct
id|eata_ccb
op_star
id|ccb
suffix:semicolon
multiline_comment|/* Address set in COMMAND PACKET  */
DECL|member|msg
id|__u8
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
id|__u8
id|vendor
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|name
id|__u8
id|name
(braket
l_int|18
)braket
suffix:semicolon
DECL|member|revision
id|__u8
id|revision
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|EATA_revision
id|__u8
id|EATA_revision
suffix:semicolon
DECL|member|bustype
id|__u8
id|bustype
suffix:semicolon
multiline_comment|/* bustype of HBA             */
DECL|member|channel
id|__u8
id|channel
suffix:semicolon
multiline_comment|/* # of avail. scsi channels  */
DECL|member|state
id|__u8
id|state
suffix:semicolon
multiline_comment|/* state of HBA               */
DECL|member|primary
id|__u8
id|primary
suffix:semicolon
multiline_comment|/* true if primary            */
DECL|member|broken_INQUIRY
id|__u8
id|broken_INQUIRY
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* This is an EISA HBA with   *&n;&t;&t;&t;&t;  * broken INQUIRY             */
DECL|member|reads
id|__u32
id|reads
(braket
l_int|13
)braket
suffix:semicolon
DECL|member|writes
id|__u32
id|writes
(braket
l_int|13
)braket
suffix:semicolon
multiline_comment|/* state of Target (RESET,..) */
DECL|member|t_state
id|__u8
id|t_state
(braket
id|MAXCHANNEL
)braket
(braket
id|MAXTARGET
)braket
suffix:semicolon
multiline_comment|/* timeouts on target         */
DECL|member|t_timeout
id|__u32
id|t_timeout
(braket
id|MAXCHANNEL
)braket
(braket
id|MAXTARGET
)braket
suffix:semicolon
DECL|member|last_ccb
id|__u32
id|last_ccb
suffix:semicolon
multiline_comment|/* Last used ccb              */
DECL|member|cplen
id|__u32
id|cplen
suffix:semicolon
multiline_comment|/* size of CP in words        */
DECL|member|cppadlen
id|__u16
id|cppadlen
suffix:semicolon
multiline_comment|/* pad length of cp in words  */
DECL|member|hostid
id|__u8
id|hostid
suffix:semicolon
multiline_comment|/* SCSI ID of HBA             */
DECL|member|devflags
id|__u8
id|devflags
suffix:semicolon
multiline_comment|/* bits set for detected devices */
DECL|member|moresupport
id|__u8
id|moresupport
suffix:semicolon
multiline_comment|/* HBA supports MORE flag     */
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
id|__u8
id|trans
suffix:semicolon
multiline_comment|/* translation flag 1=transl */
DECL|member|channel
id|__u8
id|channel
suffix:semicolon
multiline_comment|/* SCSI channel number       */
DECL|member|HBA
id|__u8
id|HBA
suffix:semicolon
multiline_comment|/* HBA number (prim/sec)     */
DECL|member|id
id|__u8
id|id
suffix:semicolon
multiline_comment|/* drive id                  */
DECL|member|lun
id|__u8
id|lun
suffix:semicolon
multiline_comment|/* drive lun                 */
DECL|member|heads
id|__u32
id|heads
suffix:semicolon
multiline_comment|/* number of heads           */
DECL|member|sectors
id|__u32
id|sectors
suffix:semicolon
multiline_comment|/* number of sectors         */
DECL|member|cylinder
id|__u32
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
id|__u8
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
multiline_comment|/* drive structures        */
)brace
suffix:semicolon
macro_line|#endif /* _EATA_GENERIC_H */
multiline_comment|/*&n; * Overrides for Emacs so that we almost follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 4&n; * End:&n; */
eof
