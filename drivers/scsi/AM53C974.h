multiline_comment|/* AM53/79C974 (PCscsi) driver release 0.5&n; *&n; * The architecture and much of the code of this device&n; * driver was originally developed by Drew Eckhardt for&n; * the NCR5380. The following copyrights apply:&n; *  For the architecture and all parts similar to the NCR5380:&n; *    Copyright 1993, Drew Eckhardt&n; *&t;Visionary Computing &n; *&t;(Unix and Linux consulting and custom programming)&n; * &t;drew@colorado.edu&n; *&t;+1 (303) 666-5836&n; *&n; *  The AM53C974_nobios_detect code was originally developed by&n; *   Robin Cutshaw (robin@xfree86.org) and is used here in a &n; *   modified form.&n; *&n; *  For the other parts:&n; *    Copyright 1994, D. Frieauff&n; *    EMail: fri@rsx42sun0.dofn.de&n; *    Phone: x49-7545-8-2256 , x49-7541-42305&n; */
multiline_comment|/*&n; * $Log: AM53C974.h,v $&n; */
macro_line|#ifndef AM53C974_H
DECL|macro|AM53C974_H
mdefine_line|#define AM53C974_H
macro_line|#include &lt;scsi/scsicam.h&gt;
multiline_comment|/***************************************************************************************&n;* Default setting of the controller&squot;s SCSI id. Edit and uncomment this only if your    *&n;* BIOS does not correctly initialize the controller&squot;s SCSI id.                         *&n;* If you don&squot;t get a warning during boot, it is correctly initialized.                 *&n;****************************************************************************************/
multiline_comment|/* #define AM53C974_SCSI_ID 7 */
multiline_comment|/***************************************************************************************&n;* Default settings for sync. negotiation enable, transfer rate and sync. offset.       *&n;* These settings can be replaced by LILO overrides (append) with the following syntax:          *&n;* AM53C974=host-scsi-id, target-scsi-id, max-rate, max-offset                          *&n;* Sync. negotiation is disabled by default and will be enabled for those targets which *&n;* are specified in the LILO override                                                   *&n;****************************************************************************************/
DECL|macro|DEFAULT_SYNC_NEGOTIATION_ENABLED
mdefine_line|#define DEFAULT_SYNC_NEGOTIATION_ENABLED 0 /* 0 or 1 */
DECL|macro|DEFAULT_RATE
mdefine_line|#define DEFAULT_RATE&t;&t;&t; 5 /* MHz, min: 3; max: 10 */
DECL|macro|DEFAULT_SYNC_OFFSET
mdefine_line|#define DEFAULT_SYNC_OFFSET&t;&t; 0 /* bytes, min: 0; max: 15; use 0 for async. mode */
multiline_comment|/* --------------------- don&squot;t edit below here  --------------------- */
DECL|macro|AM53C974_DRIVER_REVISION_MAJOR
mdefine_line|#define AM53C974_DRIVER_REVISION_MAJOR 0
DECL|macro|AM53C974_DRIVER_REVISION_MINOR
mdefine_line|#define AM53C974_DRIVER_REVISION_MINOR 5
DECL|macro|SEPARATOR_LINE
mdefine_line|#define SEPARATOR_LINE  &bslash;&n;&quot;--------------------------------------------------------------------------&bslash;n&quot;
multiline_comment|/* debug control */
multiline_comment|/* #define AM53C974_DEBUG */
multiline_comment|/* #define AM53C974_DEBUG_MSG */
multiline_comment|/* #define AM53C974_DEBUG_KEYWAIT */
multiline_comment|/* #define AM53C974_DEBUG_INIT */
multiline_comment|/* #define AM53C974_DEBUG_QUEUE */
multiline_comment|/* #define AM53C974_DEBUG_INFO */
multiline_comment|/* #define AM53C974_DEBUG_LINKED */
multiline_comment|/* #define VERBOSE_AM53C974_DEBUG */
multiline_comment|/* #define AM53C974_DEBUG_INTR */
multiline_comment|/* #define AM53C974_DEB_RESEL */
DECL|macro|AM53C974_DEBUG_ABORT
mdefine_line|#define AM53C974_DEBUG_ABORT
multiline_comment|/* #define AM53C974_OPTION_DEBUG_PROBE_ONLY */
multiline_comment|/* special options/constants */
DECL|macro|DEF_CLK
mdefine_line|#define DEF_CLK                 40   /* chip clock freq. in MHz */
DECL|macro|MIN_PERIOD
mdefine_line|#define MIN_PERIOD               4   /* for negotiation: min. number of clocks per cycle */
DECL|macro|MAX_PERIOD
mdefine_line|#define MAX_PERIOD              13   /* for negotiation: max. number of clocks per cycle */
DECL|macro|MAX_OFFSET
mdefine_line|#define MAX_OFFSET              15   /* for negotiation: max. offset (0=async) */
DECL|macro|DEF_SCSI_TIMEOUT
mdefine_line|#define DEF_SCSI_TIMEOUT        245  /* STIMREG value, 40 Mhz */
DECL|macro|DEF_STP
mdefine_line|#define DEF_STP                 8    /* STPREG value assuming 5.0 MB/sec, FASTCLK, FASTSCSI */
DECL|macro|DEF_SOF_RAD
mdefine_line|#define DEF_SOF_RAD             0    /* REQ/ACK deassertion delay */
DECL|macro|DEF_SOF_RAA
mdefine_line|#define DEF_SOF_RAA             0    /* REQ/ACK assertion delay */
DECL|macro|DEF_ETM
mdefine_line|#define DEF_ETM                 0    /* CNTLREG1, ext. timing mode */
DECL|macro|DEF_PERE
mdefine_line|#define DEF_PERE                1    /* CNTLREG1, parity error reporting */
DECL|macro|DEF_CLKF
mdefine_line|#define DEF_CLKF                0    /* CLKFREG,  0=40 Mhz */
DECL|macro|DEF_ENF
mdefine_line|#define DEF_ENF                 1    /* CNTLREG2, enable features */
DECL|macro|DEF_ADIDCHK
mdefine_line|#define DEF_ADIDCHK             0    /* CNTLREG3, additional ID check */
DECL|macro|DEF_FASTSCSI
mdefine_line|#define DEF_FASTSCSI            1    /* CNTLREG3, fast SCSI */
DECL|macro|DEF_FASTCLK
mdefine_line|#define DEF_FASTCLK             1    /* CNTLREG3, fast clocking, 5 MB/sec at 40MHz chip clk */
DECL|macro|DEF_GLITCH
mdefine_line|#define DEF_GLITCH              1    /* CNTLREG4, glitch eater, 0=12ns, 1=35ns, 2=25ns, 3=off */
DECL|macro|DEF_PWD
mdefine_line|#define DEF_PWD                 0    /* CNTLREG4, reduced power feature */
DECL|macro|DEF_RAE
mdefine_line|#define DEF_RAE                 0    /* CNTLREG4, RAE active negation on REQ, ACK only */
DECL|macro|DEF_RADE
mdefine_line|#define DEF_RADE                1    /* 1CNTLREG4, active negation on REQ, ACK and data */
multiline_comment|/*** PCI block ***/
multiline_comment|/* standard registers are defined in &lt;linux/pci.h&gt; */
macro_line|#ifndef PCI_VENDOR_ID_AMD
DECL|macro|PCI_VENDOR_ID_AMD
mdefine_line|#define PCI_VENDOR_ID_AMD&t;0x1022
DECL|macro|PCI_DEVICE_ID_AMD_SCSI
mdefine_line|#define PCI_DEVICE_ID_AMD_SCSI  0x2020
macro_line|#endif
DECL|macro|PCI_BASE_MASK
mdefine_line|#define PCI_BASE_MASK           0xFFFFFFE0
DECL|macro|PCI_COMMAND_PERREN
mdefine_line|#define PCI_COMMAND_PERREN      0x40
DECL|macro|PCI_SCRATCH_REG_0
mdefine_line|#define PCI_SCRATCH_REG_0&t;0x40&t;/* 16 bits */
DECL|macro|PCI_SCRATCH_REG_1
mdefine_line|#define PCI_SCRATCH_REG_1&t;0x42&t;/* 16 bits */
DECL|macro|PCI_SCRATCH_REG_2
mdefine_line|#define PCI_SCRATCH_REG_2&t;0x44&t;/* 16 bits */
DECL|macro|PCI_SCRATCH_REG_3
mdefine_line|#define PCI_SCRATCH_REG_3&t;0x46&t;/* 16 bits */
DECL|macro|PCI_SCRATCH_REG_4
mdefine_line|#define PCI_SCRATCH_REG_4&t;0x48&t;/* 16 bits */
DECL|macro|PCI_SCRATCH_REG_5
mdefine_line|#define PCI_SCRATCH_REG_5&t;0x4A&t;/* 16 bits */
DECL|macro|PCI_SCRATCH_REG_6
mdefine_line|#define PCI_SCRATCH_REG_6&t;0x4C&t;/* 16 bits */
DECL|macro|PCI_SCRATCH_REG_7
mdefine_line|#define PCI_SCRATCH_REG_7&t;0x4E&t;/* 16 bits */
multiline_comment|/*** SCSI block ***/
DECL|macro|CTCLREG
mdefine_line|#define CTCLREG&t;&t;    &t;0x00&t;/* r&t;current transf. count, low byte    */
DECL|macro|CTCMREG
mdefine_line|#define CTCMREG&t;&t;   &t;0x04&t;/* r &t;current transf. count, middle byte */
DECL|macro|CTCHREG
mdefine_line|#define CTCHREG&t;&t;    &t;0x38&t;/* r&t;current transf. count, high byte   */
DECL|macro|STCLREG
mdefine_line|#define STCLREG&t;&t;    &t;0x00&t;/* w&t;start transf. count, low byte      */
DECL|macro|STCMREG
mdefine_line|#define STCMREG&t;&t;    &t;0x04&t;/* w&t;start transf. count, middle byte   */
DECL|macro|STCHREG
mdefine_line|#define STCHREG&t;&t;    &t;0x38&t;/* w &t;start transf. count, high byte     */
DECL|macro|FFREG
mdefine_line|#define FFREG&t;&t;    &t;0x08&t;/* rw&t;SCSI FIFO reg.&t;&t;&t;   */
DECL|macro|STIMREG
mdefine_line|#define STIMREG&t;&t;    &t;0x14&t;/* w&t;SCSI timeout reg.&t;&t;   */
DECL|macro|SDIDREG
mdefine_line|#define SDIDREG&t;&t;    &t;0x10&t;/* w&t;SCSI destination ID reg.&t;   */
DECL|macro|SDIREG_MASK
mdefine_line|#define SDIREG_MASK&t;&t;0x07&t;/* mask&t;&t;&t;&t;&t;   */
DECL|macro|STPREG
mdefine_line|#define STPREG&t;&t;    &t;0x18&t;/* w&t;synchronous transf. period reg.&t;   */
DECL|macro|STPREG_STP
mdefine_line|#define STPREG_STP&t;&t;0x1F&t;/* synchr. transfer period&t;&t;   */
DECL|macro|CLKFREG
mdefine_line|#define CLKFREG&t;&t;    &t;0x24&t;/* w&t;clock factor reg.&t;&t;   */
DECL|macro|CLKFREG_MASK
mdefine_line|#define CLKFREG_MASK&t;&t;0x07&t;/* mask&t;&t;&t;&t;&t;   */
DECL|macro|CMDREG
mdefine_line|#define CMDREG&t;&t;    &t;0x0C&t;/* rw&t;SCSI command reg.&t;&t;   */
DECL|macro|CMDREG_DMA
mdefine_line|#define CMDREG_DMA         &t;0x80    /* set DMA mode (set together with opcodes below) */
DECL|macro|CMDREG_IT
mdefine_line|#define CMDREG_IT          &t;0x10    /* information transfer &t;&t;   */
DECL|macro|CMDREG_ICCS
mdefine_line|#define CMDREG_ICCS&t;&t;0x11&t;/* initiator command complete steps &t;   */
DECL|macro|CMDREG_MA
mdefine_line|#define CMDREG_MA&t;&t;0x12&t;/* message accepted &t;&t;&t;   */
DECL|macro|CMDREG_TPB
mdefine_line|#define CMDREG_TPB&t;&t;0x98&t;/* transfer pad bytes, DMA mode only &t;   */
DECL|macro|CMDREG_SATN
mdefine_line|#define CMDREG_SATN&t;&t;0x1A&t;/* set ATN &t;&t;&t;&t;   */
DECL|macro|CMDREG_RATN
mdefine_line|#define CMDREG_RATN&t;&t;0x1B&t;/* reset ATN &t;&t;&t;&t;   */
DECL|macro|CMDREG_SOAS
mdefine_line|#define CMDREG_SOAS&t;&t;0x41&t;/* select without ATN steps &t;&t;   */
DECL|macro|CMDREG_SAS
mdefine_line|#define CMDREG_SAS&t;&t;0x42&t;/* select with ATN steps (1 msg byte)&t;   */
DECL|macro|CMDREG_SASS
mdefine_line|#define CMDREG_SASS&t;&t;0x43&t;/* select with ATN and stop steps &t;   */
DECL|macro|CMDREG_ESR
mdefine_line|#define CMDREG_ESR&t;&t;0x44&t;/* enable selection/reselection &t;   */
DECL|macro|CMDREG_DSR
mdefine_line|#define CMDREG_DSR&t;&t;0x45&t;/* disable selection/reselection &t;   */
DECL|macro|CMDREG_SA3S
mdefine_line|#define CMDREG_SA3S&t;&t;0x46&t;/* select with ATN 3 steps  (3 msg bytes)  */
DECL|macro|CMDREG_NOP
mdefine_line|#define CMDREG_NOP&t;&t;0x00&t;/* no operation &t;&t;&t;   */
DECL|macro|CMDREG_CFIFO
mdefine_line|#define CMDREG_CFIFO&t;&t;0x01&t;/* clear FIFO &t;&t;&t;&t;   */
DECL|macro|CMDREG_RDEV
mdefine_line|#define CMDREG_RDEV&t;&t;0x02&t;/* reset device &t;&t;&t;   */
DECL|macro|CMDREG_RBUS
mdefine_line|#define CMDREG_RBUS&t;&t;0x03&t;/* reset SCSI bus &t;&t;&t;   */
DECL|macro|STATREG
mdefine_line|#define STATREG&t;&t;    &t;0x10&t;/* r &t;SCSI status reg.&t;&t;   */
DECL|macro|STATREG_INT
mdefine_line|#define STATREG_INT&t;&t;0x80&t;/* SCSI interrupt condition detected&t;   */
DECL|macro|STATREG_IOE
mdefine_line|#define STATREG_IOE&t;&t;0x40&t;/* SCSI illegal operation error detected   */
DECL|macro|STATREG_PE
mdefine_line|#define STATREG_PE&t;&t;0x20&t;/* SCSI parity error detected&t;&t;   */
DECL|macro|STATREG_CTZ
mdefine_line|#define STATREG_CTZ&t;&t;0x10&t;/* CTC reg decremented to zero&t;&t;   */
DECL|macro|STATREG_MSG
mdefine_line|#define STATREG_MSG&t;&t;0x04&t;/* SCSI MSG phase (latched?)&t;&t;   */
DECL|macro|STATREG_CD
mdefine_line|#define STATREG_CD&t;&t;0x02&t;/* SCSI C/D phase (latched?)&t;&t;   */
DECL|macro|STATREG_IO
mdefine_line|#define STATREG_IO&t;&t;0x01&t;/* SCSI I/O phase (latched?)&t;&t;   */
DECL|macro|STATREG_PHASE
mdefine_line|#define STATREG_PHASE           0x07    /* SCSI phase mask &t;&t;&t;   */
DECL|macro|INSTREG
mdefine_line|#define INSTREG&t;&t;    &t;0x14&t;/* r&t;interrupt status reg.&t;&t;   */
DECL|macro|INSTREG_SRST
mdefine_line|#define INSTREG_SRST&t;&t;0x80&t;/* SCSI reset detected&t;&t;&t;   */
DECL|macro|INSTREG_ICMD
mdefine_line|#define INSTREG_ICMD&t;&t;0x40&t;/* SCSI invalid command detected&t;   */
DECL|macro|INSTREG_DIS
mdefine_line|#define INSTREG_DIS&t;&t;0x20&t;/* target disconnected or sel/resel timeout*/
DECL|macro|INSTREG_SR
mdefine_line|#define INSTREG_SR&t;&t;0x10&t;/* device on bus has service request       */
DECL|macro|INSTREG_SO
mdefine_line|#define INSTREG_SO&t;&t;0x08&t;/* successful operation&t;&t;&t;   */
DECL|macro|INSTREG_RESEL
mdefine_line|#define INSTREG_RESEL&t;&t;0x04&t;/* device reselected as initiator&t;   */
DECL|macro|ISREG
mdefine_line|#define ISREG&t;&t;    &t;0x18&t;/* r&t;internal state reg.&t;&t;   */
DECL|macro|ISREG_SOF
mdefine_line|#define ISREG_SOF&t;&t;0x08&t;/* synchronous offset flag (act. low)&t;   */
DECL|macro|ISREG_IS
mdefine_line|#define ISREG_IS&t;&t;0x07&t;/* status of intermediate op.&t;&t;   */
DECL|macro|ISREG_OK_NO_STOP
mdefine_line|#define ISREG_OK_NO_STOP        0x04    /* selection successful                    */
DECL|macro|ISREG_OK_STOP
mdefine_line|#define ISREG_OK_STOP           0x01    /* selection successful                    */
DECL|macro|CFIREG
mdefine_line|#define CFIREG&t;&t;    &t;0x1C&t;/* r&t;current FIFO/internal state reg.   */
DECL|macro|CFIREG_IS
mdefine_line|#define CFIREG_IS&t;&t;0xE0&t;/* status of intermediate op.&t;&t;   */
DECL|macro|CFIREG_CF
mdefine_line|#define CFIREG_CF&t;&t;0x1F&t;/* number of bytes in SCSI FIFO&t;&t;   */
DECL|macro|SOFREG
mdefine_line|#define SOFREG&t;&t;    &t;0x1C&t;/* w&t;synchr. offset reg.&t;&t;   */
DECL|macro|SOFREG_RAD
mdefine_line|#define SOFREG_RAD&t;&t;0xC0&t;/* REQ/ACK deassertion delay (sync.)&t;   */
DECL|macro|SOFREG_RAA
mdefine_line|#define SOFREG_RAA&t;&t;0x30&t;/* REQ/ACK assertion delay (sync.)&t;   */
DECL|macro|SOFREG_SO
mdefine_line|#define SOFREG_SO&t;&t;0x0F&t;/* synch. offset (sync.)&t;&t;   */
DECL|macro|CNTLREG1
mdefine_line|#define CNTLREG1&t;    &t;0x20&t;/* rw&t;control register one&t;&t;   */
DECL|macro|CNTLREG1_ETM
mdefine_line|#define CNTLREG1_ETM&t;&t;0x80&t;/* set extended timing mode&t;&t;   */
DECL|macro|CNTLREG1_DISR
mdefine_line|#define CNTLREG1_DISR&t;&t;0x40&t;/* disable interrupt on SCSI reset&t;   */
DECL|macro|CNTLREG1_PERE
mdefine_line|#define CNTLREG1_PERE&t;&t;0x10&t;/* enable parity error reporting&t;   */
DECL|macro|CNTLREG1_SID
mdefine_line|#define CNTLREG1_SID&t;&t;0x07&t;/* host adapter SCSI ID&t;&t;&t;   */
DECL|macro|CNTLREG2
mdefine_line|#define CNTLREG2&t;    &t;0x2C&t;/* rw&t;control register two&t;&t;   */
DECL|macro|CNTLREG2_ENF
mdefine_line|#define CNTLREG2_ENF&t;&t;0x40&t;/* enable features&t;&t;&t;   */
DECL|macro|CNTLREG3
mdefine_line|#define CNTLREG3&t;    &t;0x30&t;/* rw&t;control register three&t;&t;   */ 
DECL|macro|CNTLREG3_ADIDCHK
mdefine_line|#define CNTLREG3_ADIDCHK&t;0x80&t;/* additional ID check&t;&t;&t;   */
DECL|macro|CNTLREG3_FASTSCSI
mdefine_line|#define CNTLREG3_FASTSCSI&t;0x10&t;/* fast SCSI&t;&t;&t;&t;   */
DECL|macro|CNTLREG3_FASTCLK
mdefine_line|#define CNTLREG3_FASTCLK&t;0x08&t;/* fast SCSI clocking&t;&t;&t;   */
DECL|macro|CNTLREG4
mdefine_line|#define CNTLREG4&t;    &t;0x34&t;/* rw&t;control register four&t;&t;   */ 
DECL|macro|CNTLREG4_GLITCH
mdefine_line|#define CNTLREG4_GLITCH&t;&t;0xC0&t;/* glitch eater&t;&t;&t;&t;   */
DECL|macro|CNTLREG4_PWD
mdefine_line|#define CNTLREG4_PWD&t;&t;0x20&t;/* reduced power feature&t;&t;   */
DECL|macro|CNTLREG4_RAE
mdefine_line|#define CNTLREG4_RAE&t;&t;0x08&t;/* write only, active negot. ctrl.&t;   */
DECL|macro|CNTLREG4_RADE
mdefine_line|#define CNTLREG4_RADE&t;&t;0x04&t;/* active negot. ctrl.&t;&t;&t;   */
DECL|macro|CNTLREG4_RES
mdefine_line|#define CNTLREG4_RES&t;&t;0x10&t;/* reserved bit, must be 1&t;&t;   */
multiline_comment|/*** DMA block ***/
DECL|macro|DMACMD
mdefine_line|#define DMACMD&t;&t;    &t;0x40&t;/* rw&t;command&t;&t;&t;&t;   */
DECL|macro|DMACMD_DIR
mdefine_line|#define DMACMD_DIR&t;&t;0x80&t;/* transfer direction (1=read from device) */
DECL|macro|DMACMD_INTE_D
mdefine_line|#define DMACMD_INTE_D&t;&t;0x40&t;/* DMA transfer interrupt enable &t;   */
DECL|macro|DMACMD_INTE_P
mdefine_line|#define DMACMD_INTE_P&t;&t;0x20&t;/* page transfer interrupt enable &t;   */
DECL|macro|DMACMD_MDL
mdefine_line|#define DMACMD_MDL&t;&t;0x10&t;/* map to memory descriptor list &t;   */
DECL|macro|DMACMD_DIAG
mdefine_line|#define DMACMD_DIAG&t;&t;0x04&t;/* diagnostics, set to 0&t;&t;   */
DECL|macro|DMACMD_IDLE
mdefine_line|#define DMACMD_IDLE &t;&t;0x00&t;/* idle cmd&t;&t;&t; &t;   */
DECL|macro|DMACMD_BLAST
mdefine_line|#define DMACMD_BLAST&t;&t;0x01&t;/* flush FIFO to memory&t;&t; &t;   */
DECL|macro|DMACMD_ABORT
mdefine_line|#define DMACMD_ABORT&t;&t;0x02&t;/* terminate DMA&t;&t; &t;   */
DECL|macro|DMACMD_START
mdefine_line|#define DMACMD_START&t;&t;0x03&t;/* start DMA&t;&t;&t; &t;   */
DECL|macro|DMASTATUS
mdefine_line|#define DMASTATUS&t;      &t;0x54&t;/* r&t;status register&t;&t;&t;   */
DECL|macro|DMASTATUS_BCMPLT
mdefine_line|#define DMASTATUS_BCMPLT&t;0x20&t;/* BLAST complete&t;&t;&t;   */
DECL|macro|DMASTATUS_SCSIINT
mdefine_line|#define DMASTATUS_SCSIINT&t;0x10&t;/* SCSI interrupt pending&t;&t;   */
DECL|macro|DMASTATUS_DONE
mdefine_line|#define DMASTATUS_DONE&t;&t;0x08&t;/* DMA transfer terminated&t;&t;   */
DECL|macro|DMASTATUS_ABORT
mdefine_line|#define DMASTATUS_ABORT&t;&t;0x04&t;/* DMA transfer aborted&t;&t;&t;   */
DECL|macro|DMASTATUS_ERROR
mdefine_line|#define DMASTATUS_ERROR&t;&t;0x02&t;/* DMA transfer error&t;&t;&t;   */
DECL|macro|DMASTATUS_PWDN
mdefine_line|#define DMASTATUS_PWDN&t;&t;0x02&t;/* power down indicator&t;&t;&t;   */
DECL|macro|DMASTC
mdefine_line|#define DMASTC&t;&t;    &t;0x44&t;/* rw&t;starting transfer count&t;&t;   */
DECL|macro|DMASPA
mdefine_line|#define DMASPA&t;&t;    &t;0x48&t;/* rw&t;starting physical address&t;   */
DECL|macro|DMAWBC
mdefine_line|#define DMAWBC&t;&t;    &t;0x4C&t;/* r&t;working byte counter&t;&t;   */
DECL|macro|DMAWAC
mdefine_line|#define DMAWAC&t;&t;    &t;0x50&t;/* r&t;working address counter&t;&t;   */
DECL|macro|DMASMDLA
mdefine_line|#define DMASMDLA&t;    &t;0x58&t;/* rw&t;starting MDL address&t;&t;   */
DECL|macro|DMAWMAC
mdefine_line|#define DMAWMAC&t;&t;    &t;0x5C&t;/* r&t;working MDL counter&t;&t;   */
multiline_comment|/*** SCSI phases ***/
DECL|macro|PHASE_MSGIN
mdefine_line|#define PHASE_MSGIN             0x07
DECL|macro|PHASE_MSGOUT
mdefine_line|#define PHASE_MSGOUT            0x06
DECL|macro|PHASE_RES_1
mdefine_line|#define PHASE_RES_1             0x05
DECL|macro|PHASE_RES_0
mdefine_line|#define PHASE_RES_0             0x04
DECL|macro|PHASE_STATIN
mdefine_line|#define PHASE_STATIN            0x03
DECL|macro|PHASE_CMDOUT
mdefine_line|#define PHASE_CMDOUT            0x02
DECL|macro|PHASE_DATAIN
mdefine_line|#define PHASE_DATAIN            0x01
DECL|macro|PHASE_DATAOUT
mdefine_line|#define PHASE_DATAOUT           0x00
DECL|struct|AM53C974_hostdata
r_struct
id|AM53C974_hostdata
(brace
DECL|member|in_reset
r_volatile
r_int
id|in_reset
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag, says bus reset pending */
DECL|member|aborted
r_volatile
r_int
id|aborted
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* flag, says aborted */
DECL|member|selecting
r_volatile
r_int
id|selecting
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* selection started, but not yet finished */
DECL|member|disconnecting
r_volatile
r_int
id|disconnecting
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* disconnection started, but not yet finished */
DECL|member|dma_busy
r_volatile
r_int
id|dma_busy
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* dma busy when service request for info transfer received */
DECL|member|msgout
r_volatile
r_int
r_char
id|msgout
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* message to output in MSGOUT_PHASE */
DECL|member|last_message
r_volatile
r_int
r_char
id|last_message
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* last message OUT */
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
DECL|member|sel_cmd
r_volatile
id|Scsi_Cmnd
op_star
id|sel_cmd
suffix:semicolon
multiline_comment|/* command for selection */
DECL|member|connected
r_volatile
id|Scsi_Cmnd
op_star
id|connected
suffix:semicolon
multiline_comment|/* currently connected command */
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
DECL|member|sync_per
r_int
r_char
id|sync_per
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* synchronous transfer period (in effect) */
DECL|member|sync_off
r_int
r_char
id|sync_off
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* synchronous offset (in effect) */
DECL|member|sync_neg
r_int
r_char
id|sync_neg
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* sync. negotiation performed (in effect) */
DECL|member|sync_en
r_int
r_char
id|sync_en
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* sync. negotiation performed (in effect) */
DECL|member|max_rate
r_int
r_char
id|max_rate
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* max. transfer rate (setup) */
DECL|member|max_offset
r_int
r_char
id|max_offset
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* max. sync. offset (setup), only valid if corresponding sync_en is nonzero */
)brace
suffix:semicolon
DECL|macro|AM53C974
mdefine_line|#define AM53C974 { &bslash;&n;    NULL,              &t;&t;/* pointer to next in list                      */  &bslash;&n;    NULL,&t;&t;&t;/* long * usage_count&t;&t;&t;&t;*/  &bslash;&n;    NULL,                       /* struct proc_dir_entry *proc_dir              */ &bslash;&n;    NULL,                       /* int (*proc_info)(char *, char **, off_t, int, int, int); */ &bslash;&n;    &quot;AM53C974&quot;,        &t;&t;/* name                                         */  &bslash;&n;    AM53C974_detect,   &t;&t;/* int (* detect)(struct SHT *)                 */  &bslash;&n;    NULL,              &t;&t;/* int (*release)(struct Scsi_Host *)           */  &bslash;&n;    AM53C974_info,     &t;&t;/* const char *(* info)(struct Scsi_Host *)     */  &bslash;&n;    AM53C974_command,  &t;&t;/* int (* command)(Scsi_Cmnd *)                 */  &bslash;&n;    AM53C974_queue_command,&t;/* int (* queuecommand)(Scsi_Cmnd *,                &bslash;&n;                                           void (*done)(Scsi_Cmnd *))           */  &bslash;&n;    AM53C974_abort,    &t;&t;/* int (* abort)(Scsi_Cmnd *)                   */  &bslash;&n;    AM53C974_reset,    &t;&t;/* int (* reset)(Scsi_Cmnd *)                   */  &bslash;&n;    NULL,                 &t;/* int (* slave_attach)(int, int)               */  &bslash;&n;    scsicam_bios_param,&t;&t;/* int (* bios_param)(Disk *, int, int[])       */  &bslash;&n;    12,                 &t;/* can_queue                                    */  &bslash;&n;    -1,                         /* this_id                                      */  &bslash;&n;    SG_ALL,            &t;&t;/* sg_tablesize                                 */  &bslash;&n;    1,                 &t;&t;/* cmd_per_lun                                  */  &bslash;&n;    0,                 &t;&t;/* present, i.e. how many adapters of this kind */  &bslash;&n;    0,                 &t;&t;/* unchecked_isa_dma                            */  &bslash;&n;    DISABLE_CLUSTERING &t;&t;/* use_clustering                               */  &bslash;&n;    }
r_void
id|AM53C974_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
r_int
id|AM53C974_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
suffix:semicolon
r_int
id|AM53C974_biosparm
c_func
(paren
id|Disk
op_star
id|disk
comma
r_int
id|dev
comma
r_int
op_star
id|info_array
)paren
suffix:semicolon
r_const
r_char
op_star
id|AM53C974_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|AM53C974_command
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
suffix:semicolon
r_int
id|AM53C974_queue_command
c_func
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
r_int
id|AM53C974_abort
c_func
(paren
id|Scsi_Cmnd
op_star
id|cmd
)paren
suffix:semicolon
r_int
id|AM53C974_reset
(paren
id|Scsi_Cmnd
op_star
id|cmd
)paren
suffix:semicolon
DECL|macro|AM53C974_local_declare
mdefine_line|#define AM53C974_local_declare()&t;unsigned long io_port
DECL|macro|AM53C974_setio
mdefine_line|#define AM53C974_setio(instance)&t;io_port = instance-&gt;io_port
DECL|macro|AM53C974_read_8
mdefine_line|#define AM53C974_read_8(addr)           inb(io_port + (addr))
DECL|macro|AM53C974_write_8
mdefine_line|#define AM53C974_write_8(addr,x)        outb((x), io_port + (addr))
DECL|macro|AM53C974_read_16
mdefine_line|#define AM53C974_read_16(addr)          inw(io_port + (addr))
DECL|macro|AM53C974_write_16
mdefine_line|#define AM53C974_write_16(addr,x)       outw((x), io_port + (addr))
DECL|macro|AM53C974_read_32
mdefine_line|#define AM53C974_read_32(addr)          inl(io_port + (addr))
DECL|macro|AM53C974_write_32
mdefine_line|#define AM53C974_write_32(addr,x)       outl((x), io_port + (addr))
DECL|macro|AM53C974_poll_int
mdefine_line|#define AM53C974_poll_int()             { do { statreg = AM53C974_read_8(STATREG); } &bslash;&n;                                             while (!(statreg &amp; STATREG_INT)) ; &bslash;&n;                                          AM53C974_read_8(INSTREG) ; } /* clear int */
DECL|macro|AM53C974_cfifo
mdefine_line|#define AM53C974_cfifo()&t;&t;(AM53C974_read_8(CFIREG) &amp; CFIREG_CF)
multiline_comment|/* These are &quot;special&quot; values for the tag parameter passed to AM53C974_select. */
DECL|macro|TAG_NEXT
mdefine_line|#define TAG_NEXT&t;-1 &t;/* Use next free tag */
DECL|macro|TAG_NONE
mdefine_line|#define TAG_NONE&t;-2&t;/* Establish I_T_L nexus instead of I_T_L_Q&n;&t;&t;&t;&t; * even on SCSI-II devices */
multiline_comment|/************ LILO overrides *************/
DECL|struct|_override_t
r_typedef
r_struct
id|_override_t
(brace
DECL|member|host_scsi_id
r_int
id|host_scsi_id
suffix:semicolon
multiline_comment|/* SCSI id of the bus controller */
DECL|member|target_scsi_id
r_int
id|target_scsi_id
suffix:semicolon
multiline_comment|/* SCSI id of target */
DECL|member|max_rate
r_int
id|max_rate
suffix:semicolon
multiline_comment|/* max. transfer rate */
DECL|member|max_offset
r_int
id|max_offset
suffix:semicolon
multiline_comment|/* max. sync. offset, 0 = asynchronous */
DECL|typedef|override_t
)brace
id|override_t
suffix:semicolon
multiline_comment|/************ PCI stuff *************/
DECL|macro|AM53C974_PCIREG_OPEN
mdefine_line|#define AM53C974_PCIREG_OPEN()                    outb(0xF1, 0xCF8); outb(0, 0xCFA)
DECL|macro|AM53C974_PCIREG_CLOSE
mdefine_line|#define AM53C974_PCIREG_CLOSE()                   outb(0, 0xCF8)
DECL|macro|AM53C974_PCIREG_READ_BYTE
mdefine_line|#define AM53C974_PCIREG_READ_BYTE(instance,a)     ( inb((a) + (instance)-&gt;io_port) )
DECL|macro|AM53C974_PCIREG_READ_WORD
mdefine_line|#define AM53C974_PCIREG_READ_WORD(instance,a)     ( inw((a) + (instance)-&gt;io_port) )
DECL|macro|AM53C974_PCIREG_READ_DWORD
mdefine_line|#define AM53C974_PCIREG_READ_DWORD(instance,a)    ( inl((a) + (instance)-&gt;io_port) )
DECL|macro|AM53C974_PCIREG_WRITE_BYTE
mdefine_line|#define AM53C974_PCIREG_WRITE_BYTE(instance,x,a)  ( outb((x), (a) + (instance)-&gt;io_port) )
DECL|macro|AM53C974_PCIREG_WRITE_WORD
mdefine_line|#define AM53C974_PCIREG_WRITE_WORD(instance,x,a)  ( outw((x), (a) + (instance)-&gt;io_port) )
DECL|macro|AM53C974_PCIREG_WRITE_DWORD
mdefine_line|#define AM53C974_PCIREG_WRITE_DWORD(instance,x,a) ( outl((x), (a) + (instance)-&gt;io_port) )
DECL|struct|_pci_config_t
r_typedef
r_struct
id|_pci_config_t
(brace
multiline_comment|/* start of official PCI config space header */
r_union
(brace
DECL|member|device_vendor
r_int
r_int
id|device_vendor
suffix:semicolon
r_struct
(brace
DECL|member|vendor
r_int
r_int
id|vendor
suffix:semicolon
DECL|member|device
r_int
r_int
id|device
suffix:semicolon
DECL|member|dv
)brace
id|dv
suffix:semicolon
DECL|member|dv_id
)brace
id|dv_id
suffix:semicolon
DECL|macro|_device_vendor
mdefine_line|#define _device_vendor dv_id.device_vendor
DECL|macro|_vendor
mdefine_line|#define _vendor dv_id.dv.vendor
DECL|macro|_device
mdefine_line|#define _device dv_id.dv.device
r_union
(brace
DECL|member|status_command
r_int
r_int
id|status_command
suffix:semicolon
r_struct
(brace
DECL|member|command
r_int
r_int
id|command
suffix:semicolon
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
DECL|member|sc
)brace
id|sc
suffix:semicolon
DECL|member|stat_cmd
)brace
id|stat_cmd
suffix:semicolon
DECL|macro|_status_command
mdefine_line|#define _status_command stat_cmd.status_command
DECL|macro|_command
mdefine_line|#define _command stat_cmd.sc.command
DECL|macro|_status
mdefine_line|#define _status  stat_cmd.sc.status
r_union
(brace
DECL|member|class_revision
r_int
r_int
id|class_revision
suffix:semicolon
r_struct
(brace
DECL|member|rev_id
r_int
r_char
id|rev_id
suffix:semicolon
DECL|member|prog_if
r_int
r_char
id|prog_if
suffix:semicolon
DECL|member|sub_class
r_int
r_char
id|sub_class
suffix:semicolon
DECL|member|base_class
r_int
r_char
id|base_class
suffix:semicolon
DECL|member|cr
)brace
id|cr
suffix:semicolon
DECL|member|class_rev
)brace
id|class_rev
suffix:semicolon
DECL|macro|_class_revision
mdefine_line|#define _class_revision class_rev.class_revision
DECL|macro|_rev_id
mdefine_line|#define _rev_id     class_rev.cr.rev_id
DECL|macro|_prog_if
mdefine_line|#define _prog_if    class_rev.cr.prog_if
DECL|macro|_sub_class
mdefine_line|#define _sub_class  class_rev.cr.sub_class
DECL|macro|_base_class
mdefine_line|#define _base_class class_rev.cr.base_class
r_union
(brace
DECL|member|bist_header_latency_cache
r_int
r_int
id|bist_header_latency_cache
suffix:semicolon
r_struct
(brace
DECL|member|cache_line_size
r_int
r_char
id|cache_line_size
suffix:semicolon
DECL|member|latency_timer
r_int
r_char
id|latency_timer
suffix:semicolon
DECL|member|header_type
r_int
r_char
id|header_type
suffix:semicolon
DECL|member|bist
r_int
r_char
id|bist
suffix:semicolon
DECL|member|bhlc
)brace
id|bhlc
suffix:semicolon
DECL|member|bhlc
)brace
id|bhlc
suffix:semicolon
DECL|macro|_bist_header_latency_cache
mdefine_line|#define _bist_header_latency_cache bhlc.bist_header_latency_cache
DECL|macro|_cache_line_size
mdefine_line|#define _cache_line_size bhlc.bhlc.cache_line_size
DECL|macro|_latency_timer
mdefine_line|#define _latency_timer   bhlc.bhlc.latency_timer
DECL|macro|_header_type
mdefine_line|#define _header_type     bhlc.bhlc.header_type
DECL|macro|_bist
mdefine_line|#define _bist            bhlc.bhlc.bist
DECL|member|_base0
r_int
r_int
id|_base0
suffix:semicolon
DECL|member|_base1
r_int
r_int
id|_base1
suffix:semicolon
DECL|member|_base2
r_int
r_int
id|_base2
suffix:semicolon
DECL|member|_base3
r_int
r_int
id|_base3
suffix:semicolon
DECL|member|_base4
r_int
r_int
id|_base4
suffix:semicolon
DECL|member|_base5
r_int
r_int
id|_base5
suffix:semicolon
DECL|member|rsvd1
r_int
r_int
id|rsvd1
suffix:semicolon
DECL|member|rsvd2
r_int
r_int
id|rsvd2
suffix:semicolon
DECL|member|_baserom
r_int
r_int
id|_baserom
suffix:semicolon
DECL|member|rsvd3
r_int
r_int
id|rsvd3
suffix:semicolon
DECL|member|rsvd4
r_int
r_int
id|rsvd4
suffix:semicolon
r_union
(brace
DECL|member|max_min_ipin_iline
r_int
r_int
id|max_min_ipin_iline
suffix:semicolon
r_struct
(brace
DECL|member|int_line
r_int
r_char
id|int_line
suffix:semicolon
DECL|member|int_pin
r_int
r_char
id|int_pin
suffix:semicolon
DECL|member|min_gnt
r_int
r_char
id|min_gnt
suffix:semicolon
DECL|member|max_lat
r_int
r_char
id|max_lat
suffix:semicolon
DECL|member|mmii
)brace
id|mmii
suffix:semicolon
DECL|member|mmii
)brace
id|mmii
suffix:semicolon
DECL|macro|_max_min_ipin_iline
mdefine_line|#define _max_min_ipin_iline mmii.max_min_ipin_iline
DECL|macro|_int_line
mdefine_line|#define _int_line mmii.mmii.int_line
DECL|macro|_int_pin
mdefine_line|#define _int_pin  mmii.mmii.int_pin
DECL|macro|_min_gnt
mdefine_line|#define _min_gnt  mmii.mmii.min_gnt
DECL|macro|_max_lat
mdefine_line|#define _max_lat  mmii.mmii.max_lat
multiline_comment|/* end of official PCI config space header */
DECL|member|_ioaddr
r_int
r_int
id|_ioaddr
suffix:semicolon
multiline_comment|/* config type 1 - private I/O addr    */
DECL|member|_pcibus
r_int
r_int
id|_pcibus
suffix:semicolon
multiline_comment|/* config type 2 - private bus id      */
DECL|member|_cardnum
r_int
r_int
id|_cardnum
suffix:semicolon
multiline_comment|/* config type 2 - private card number */
DECL|typedef|pci_config_t
)brace
id|pci_config_t
suffix:semicolon
macro_line|#endif /* AM53C974_H */
eof
