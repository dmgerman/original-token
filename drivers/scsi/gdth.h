macro_line|#ifndef _GDTH_H
DECL|macro|_GDTH_H
mdefine_line|#define _GDTH_H
multiline_comment|/*&n; * Header file for the GDT ISA/EISA/PCI Disk Array Controller driver for Linux&n; * &n; * gdth.h Copyright (C) 1995-97 ICP vortex Computersysteme GmbH, Achim Leubner&n; * See gdth.c for further informations and &n; * below for supported controller types&n; *&n; * &lt;achim@vortex.de&gt;&n; *&n; * $Id: gdth.h,v 1.9 1997/11/04 09:55:42 achim Exp $&n; */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
macro_line|#ifndef TRUE
DECL|macro|TRUE
mdefine_line|#define TRUE 1
macro_line|#endif
macro_line|#ifndef FALSE
DECL|macro|FALSE
mdefine_line|#define FALSE 0
macro_line|#endif
multiline_comment|/* defines, macros */
multiline_comment|/* driver version */
DECL|macro|GDTH_VERSION_STR
mdefine_line|#define GDTH_VERSION_STR        &quot;1.02&quot;
DECL|macro|GDTH_VERSION
mdefine_line|#define GDTH_VERSION            1
DECL|macro|GDTH_SUBVERSION
mdefine_line|#define GDTH_SUBVERSION         2
multiline_comment|/* protocol version */
DECL|macro|PROTOCOL_VERSION
mdefine_line|#define PROTOCOL_VERSION        1
multiline_comment|/* controller classes */
DECL|macro|GDT_ISA
mdefine_line|#define GDT_ISA         0x01                    /* ISA controller */
DECL|macro|GDT_EISA
mdefine_line|#define GDT_EISA        0x02                    /* EISA controller */
DECL|macro|GDT_PCI
mdefine_line|#define GDT_PCI         0x03                    /* PCI controller */
DECL|macro|GDT_PCINEW
mdefine_line|#define GDT_PCINEW      0x04                    /* new PCI controller */
DECL|macro|GDT_PCIMPR
mdefine_line|#define GDT_PCIMPR      0x05                    /* PCI MPR controller */
multiline_comment|/* GDT_EISA, controller subtypes EISA */
DECL|macro|GDT3_ID
mdefine_line|#define GDT3_ID         0x0130941c              /* GDT3000/3020 */
DECL|macro|GDT3A_ID
mdefine_line|#define GDT3A_ID        0x0230941c              /* GDT3000A/3020A/3050A */
DECL|macro|GDT3B_ID
mdefine_line|#define GDT3B_ID        0x0330941c              /* GDT3000B/3010A */
multiline_comment|/* GDT_ISA */
DECL|macro|GDT2_ID
mdefine_line|#define GDT2_ID         0x0120941c              /* GDT2000/2020 */
multiline_comment|/* vendor ID, device IDs (PCI) */
multiline_comment|/* these defines should already exist in &lt;linux/pci.h&gt; */
macro_line|#ifndef PCI_VENDOR_ID_VORTEX
DECL|macro|PCI_VENDOR_ID_VORTEX
mdefine_line|#define PCI_VENDOR_ID_VORTEX            0x1119  /* PCI controller vendor ID */
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_VORTEX_GDT60x0
multiline_comment|/* GDT_PCI */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT60x0
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT60x0    0       /* GDT6000/6020/6050 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6000B
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6000B   1       /* GDT6000B/6010 */
multiline_comment|/* GDT_PCINEW */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x10
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x10    2       /* GDT6110/6510 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x20
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x20    3       /* GDT6120/6520 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6530
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6530    4       /* GDT6530 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6550
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6550    5       /* GDT6550 */
multiline_comment|/* GDT_PCINEW, wide/ultra SCSI controllers */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x17
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x17    6       /* GDT6117/6517 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x27
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x27    7       /* GDT6127/6527 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6537
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6537    8       /* GDT6537 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6557
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6557    9       /* GDT6557/6557-ECC */
multiline_comment|/* GDT_PCINEW, wide SCSI controllers */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x15
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x15    10      /* GDT6115/6515 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x25
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x25    11      /* GDT6125/6525 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6535
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6535    12      /* GDT6535 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6555
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6555    13      /* GDT6555/6555-ECC */
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_VORTEX_GDT6x17RP
multiline_comment|/* GDT_MPR, RP series, wide/ultra SCSI */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x17RP
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x17RP  0x100   /* GDT6117RP/GDT6517RP */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x27RP
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x27RP  0x101   /* GDT6127RP/GDT6527RP */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6537RP
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6537RP  0x102   /* GDT6537RP */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6557RP
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6557RP  0x103   /* GDT6557RP */
multiline_comment|/* GDT_MPR, RP series, narrow/ultra SCSI */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x11RP
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x11RP  0x104   /* GDT6111RP/GDT6511RP */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x21RP
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x21RP  0x105   /* GDT6121RP/GDT6521RP */
multiline_comment|/* GDT_MPR, RP1 series, wide/ultra SCSI */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x17RP1
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x17RP1 0x110   /* GDT6117RP1/GDT6517RP1 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x27RP1
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x27RP1 0x111   /* GDT6127RP1/GDT6527RP1 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6537RP1
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6537RP1 0x112   /* GDT6537RP1 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6557RP1
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6557RP1 0x113   /* GDT6557RP1 */
multiline_comment|/* GDT_MPR, RP1 series, narrow/ultra SCSI */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x11RP1
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x11RP1 0x114   /* GDT6111RP1/GDT6511RP1 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x21RP1
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x21RP1 0x115   /* GDT6121RP1/GDT6521RP1 */
multiline_comment|/* GDT_MPR, RP2 series, wide/ultra SCSI */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x17RP2
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x17RP2 0x120   /* GDT6117RP2/GDT6517RP2 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x27RP2
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x27RP2 0x121   /* GDT6127RP2/GDT6527RP2 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6537RP2
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6537RP2 0x122   /* GDT6537RP2 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6557RP2
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6557RP2 0x123   /* GDT6557RP2 */
multiline_comment|/* GDT_MPR, RP2 series, narrow/ultra SCSI */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x11RP2
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x11RP2 0x124   /* GDT6111RP2/GDT6511RP2 */
DECL|macro|PCI_DEVICE_ID_VORTEX_GDT6x21RP2
mdefine_line|#define PCI_DEVICE_ID_VORTEX_GDT6x21RP2 0x125   /* GDT6121RP2/GDT6521RP2 */
macro_line|#endif
multiline_comment|/* limits */
DECL|macro|GDTH_SCRATCH
mdefine_line|#define GDTH_SCRATCH    4096                    /* 4KB scratch buffer */
DECL|macro|GDTH_MAXCMDS
mdefine_line|#define GDTH_MAXCMDS    124
DECL|macro|GDTH_MAXC_P_L
mdefine_line|#define GDTH_MAXC_P_L   16                      /* max. cmds per lun */
DECL|macro|MAXOFFSETS
mdefine_line|#define MAXOFFSETS      128
DECL|macro|MAXHA
mdefine_line|#define MAXHA           8
DECL|macro|MAXID
mdefine_line|#define MAXID           8
DECL|macro|MAXLUN
mdefine_line|#define MAXLUN          8
DECL|macro|MAXBUS
mdefine_line|#define MAXBUS          5
DECL|macro|MAX_HDRIVES
mdefine_line|#define MAX_HDRIVES     35                      /* max. host drive count */
DECL|macro|MAX_EVENTS
mdefine_line|#define MAX_EVENTS      100                     /* event buffer count */
DECL|macro|MAXCYLS
mdefine_line|#define MAXCYLS         1024
DECL|macro|HEADS
mdefine_line|#define HEADS           64
DECL|macro|SECS
mdefine_line|#define SECS            32                      /* mapping 64*32 */
DECL|macro|MEDHEADS
mdefine_line|#define MEDHEADS        127
DECL|macro|MEDSECS
mdefine_line|#define MEDSECS         63                      /* mapping 127*63 */
DECL|macro|BIGHEADS
mdefine_line|#define BIGHEADS        255
DECL|macro|BIGSECS
mdefine_line|#define BIGSECS         63                      /* mapping 255*63 */
multiline_comment|/* special command ptr. */
DECL|macro|UNUSED_CMND
mdefine_line|#define UNUSED_CMND     ((Scsi_Cmnd *)-1)
DECL|macro|INTERNAL_CMND
mdefine_line|#define INTERNAL_CMND   ((Scsi_Cmnd *)-2)
DECL|macro|SCREEN_CMND
mdefine_line|#define SCREEN_CMND     ((Scsi_Cmnd *)-3)
DECL|macro|SPECIAL_SCP
mdefine_line|#define SPECIAL_SCP(p)  (p==UNUSED_CMND || p==INTERNAL_CMND || p==SCREEN_CMND)
multiline_comment|/* device types */
DECL|macro|EMPTY_DTYP
mdefine_line|#define EMPTY_DTYP      0
DECL|macro|CACHE_DTYP
mdefine_line|#define CACHE_DTYP      1
DECL|macro|RAW_DTYP
mdefine_line|#define RAW_DTYP        2
DECL|macro|SIOP_DTYP
mdefine_line|#define SIOP_DTYP       3                       /* the SCSI processor */
multiline_comment|/* controller services */
DECL|macro|SCSIRAWSERVICE
mdefine_line|#define SCSIRAWSERVICE  3
DECL|macro|CACHESERVICE
mdefine_line|#define CACHESERVICE    9
DECL|macro|SCREENSERVICE
mdefine_line|#define SCREENSERVICE   11
multiline_comment|/* screenservice defines */
DECL|macro|MSG_INV_HANDLE
mdefine_line|#define MSG_INV_HANDLE  -1                      /* special message handle */
DECL|macro|MSGLEN
mdefine_line|#define MSGLEN          16                      /* size of message text */
DECL|macro|MSG_SIZE
mdefine_line|#define MSG_SIZE        34                      /* size of message structure */
DECL|macro|MSG_REQUEST
mdefine_line|#define MSG_REQUEST     0                       /* async. event: message */
multiline_comment|/* cacheservice defines */
DECL|macro|SECTOR_SIZE
mdefine_line|#define SECTOR_SIZE     0x200                   /* always 512 bytes per sector */
multiline_comment|/* DPMEM constants */
DECL|macro|IC_HEADER_BYTES
mdefine_line|#define IC_HEADER_BYTES 48
DECL|macro|IC_QUEUE_BYTES
mdefine_line|#define IC_QUEUE_BYTES  4
DECL|macro|DPMEM_COMMAND_OFFSET
mdefine_line|#define DPMEM_COMMAND_OFFSET    IC_HEADER_BYTES+IC_QUEUE_BYTES*MAXOFFSETS
multiline_comment|/* service commands */
DECL|macro|GDT_INIT
mdefine_line|#define GDT_INIT        0                       /* service initialization */
DECL|macro|GDT_READ
mdefine_line|#define GDT_READ        1                       /* read command */
DECL|macro|GDT_WRITE
mdefine_line|#define GDT_WRITE       2                       /* write command */
DECL|macro|GDT_INFO
mdefine_line|#define GDT_INFO        3                       /* information about devices */
DECL|macro|GDT_FLUSH
mdefine_line|#define GDT_FLUSH       4                       /* flush dirty cache buffers */
DECL|macro|GDT_IOCTL
mdefine_line|#define GDT_IOCTL       5                       /* ioctl command */
DECL|macro|GDT_DEVTYPE
mdefine_line|#define GDT_DEVTYPE     9                       /* additional information */
DECL|macro|GDT_MOUNT
mdefine_line|#define GDT_MOUNT       10                      /* mount cache device */
DECL|macro|GDT_UNMOUNT
mdefine_line|#define GDT_UNMOUNT     11                      /* unmount cache device */
DECL|macro|GDT_SET_FEAT
mdefine_line|#define GDT_SET_FEAT    12                      /* set feat. (scatter/gather) */
DECL|macro|GDT_GET_FEAT
mdefine_line|#define GDT_GET_FEAT    13                      /* get features */
DECL|macro|GDT_RESERVE
mdefine_line|#define GDT_RESERVE     14                      /* reserve dev. to raw service */
DECL|macro|GDT_WRITE_THR
mdefine_line|#define GDT_WRITE_THR   16                      /* write through */
DECL|macro|GDT_EXT_INFO
mdefine_line|#define GDT_EXT_INFO    18                      /* extended info */
DECL|macro|GDT_RESET
mdefine_line|#define GDT_RESET       19                      /* controller reset */
multiline_comment|/* IOCTL command defines */
DECL|macro|SCSI_CHAN_CNT
mdefine_line|#define SCSI_CHAN_CNT   5                       /* subfunctions */
DECL|macro|L_CTRL_PATTERN
mdefine_line|#define L_CTRL_PATTERN  0x20000000L
DECL|macro|CACHE_INFO
mdefine_line|#define CACHE_INFO      4
DECL|macro|CACHE_CONFIG
mdefine_line|#define CACHE_CONFIG    5
DECL|macro|IO_CHANNEL
mdefine_line|#define IO_CHANNEL      0x00020000L             /* channels */
DECL|macro|INVALID_CHANNEL
mdefine_line|#define INVALID_CHANNEL 0x0000ffffL     
multiline_comment|/* IOCTLs */
DECL|macro|GDTIOCTL_MASK
mdefine_line|#define GDTIOCTL_MASK       (&squot;J&squot;&lt;&lt;8)
DECL|macro|GDTIOCTL_GENERAL
mdefine_line|#define GDTIOCTL_GENERAL    (GDTIOCTL_MASK | 0) /* general IOCTL */
DECL|macro|GDTIOCTL_DRVERS
mdefine_line|#define GDTIOCTL_DRVERS     (GDTIOCTL_MASK | 1) /* get driver version */
DECL|macro|GDTIOCTL_CTRTYPE
mdefine_line|#define GDTIOCTL_CTRTYPE    (GDTIOCTL_MASK | 2) /* get controller type */
DECL|macro|GDTIOCTL_CTRCNT
mdefine_line|#define GDTIOCTL_CTRCNT     (GDTIOCTL_MASK | 5) /* get controller count */
DECL|macro|GDTIOCTL_LOCKDRV
mdefine_line|#define GDTIOCTL_LOCKDRV    (GDTIOCTL_MASK | 6) /* lock host drive */
DECL|macro|GDTIOCTL_LOCKCHN
mdefine_line|#define GDTIOCTL_LOCKCHN    (GDTIOCTL_MASK | 7) /* lock channel */
DECL|macro|GDTIOCTL_EVENT
mdefine_line|#define GDTIOCTL_EVENT      (GDTIOCTL_MASK | 8) /* read controller events */
multiline_comment|/* service errors */
DECL|macro|S_OK
mdefine_line|#define S_OK            1                       /* no error */
DECL|macro|S_BSY
mdefine_line|#define S_BSY           7                       /* controller busy */
DECL|macro|S_RAW_SCSI
mdefine_line|#define S_RAW_SCSI      12                      /* raw serv.: target error */
DECL|macro|S_RAW_ILL
mdefine_line|#define S_RAW_ILL       0xff                    /* raw serv.: illegal */
multiline_comment|/* timeout values */
DECL|macro|INIT_RETRIES
mdefine_line|#define INIT_RETRIES    10000                   /* 10000 * 1ms = 10s */
DECL|macro|INIT_TIMEOUT
mdefine_line|#define INIT_TIMEOUT    100000                  /* 1000 * 1ms = 1s */
DECL|macro|POLL_TIMEOUT
mdefine_line|#define POLL_TIMEOUT    10000                   /* 10000 * 1ms = 10s */
multiline_comment|/* priorities */
DECL|macro|DEFAULT_PRI
mdefine_line|#define DEFAULT_PRI     0x20
DECL|macro|IOCTL_PRI
mdefine_line|#define IOCTL_PRI       0x10
multiline_comment|/* data directions */
DECL|macro|DATA_IN
mdefine_line|#define DATA_IN         0x01000000L             /* data from target */
DECL|macro|DATA_OUT
mdefine_line|#define DATA_OUT        0x00000000L             /* data to target */
multiline_comment|/* BMIC registers (EISA controllers) */
DECL|macro|ID0REG
mdefine_line|#define ID0REG          0x0c80                  /* board ID */
DECL|macro|EINTENABREG
mdefine_line|#define EINTENABREG     0x0c89                  /* interrupt enable */
DECL|macro|SEMA0REG
mdefine_line|#define SEMA0REG        0x0c8a                  /* command semaphore */
DECL|macro|SEMA1REG
mdefine_line|#define SEMA1REG        0x0c8b                  /* status semaphore */
DECL|macro|LDOORREG
mdefine_line|#define LDOORREG        0x0c8d                  /* local doorbell */
DECL|macro|EDENABREG
mdefine_line|#define EDENABREG       0x0c8e                  /* EISA system doorbell enable */
DECL|macro|EDOORREG
mdefine_line|#define EDOORREG        0x0c8f                  /* EISA system doorbell */
DECL|macro|MAILBOXREG
mdefine_line|#define MAILBOXREG      0x0c90                  /* mailbox reg. (16 bytes) */
DECL|macro|EISAREG
mdefine_line|#define EISAREG         0x0cc0                  /* EISA configuration */
multiline_comment|/* other defines */
DECL|macro|LINUX_OS
mdefine_line|#define LINUX_OS        8                       /* used for cache optim. */
DECL|macro|SCATTER_GATHER
mdefine_line|#define SCATTER_GATHER  1                       /* s/g feature */
DECL|macro|GDTH_MAXSG
mdefine_line|#define GDTH_MAXSG      32                      /* max. s/g elements */
DECL|macro|SECS32
mdefine_line|#define SECS32          0x1f                    /* round capacity */
DECL|macro|BIOS_ID_OFFS
mdefine_line|#define BIOS_ID_OFFS    0x10                    /* offset contr. ID in ISABIOS */
DECL|macro|LOCALBOARD
mdefine_line|#define LOCALBOARD      0                       /* board node always 0 */
DECL|macro|ASYNCINDEX
mdefine_line|#define ASYNCINDEX      0                       /* cmd index async. event */
DECL|macro|SPEZINDEX
mdefine_line|#define SPEZINDEX       1                       /* cmd index unknown service */
DECL|macro|GDT_WR_THROUGH
mdefine_line|#define GDT_WR_THROUGH  0x100                   /* WRITE_THROUGH supported */
multiline_comment|/* typedefs */
macro_line|#pragma pack(1)
r_typedef
r_struct
(brace
DECL|member|buffer
r_char
id|buffer
(braket
id|GDTH_SCRATCH
)braket
suffix:semicolon
multiline_comment|/* scratch buffer */
DECL|typedef|gdth_scratch_str
)brace
id|gdth_scratch_str
suffix:semicolon
multiline_comment|/* screenservice message */
r_typedef
r_struct
(brace
DECL|member|msg_handle
id|ulong
id|msg_handle
suffix:semicolon
multiline_comment|/* message handle */
DECL|member|msg_len
id|ulong
id|msg_len
suffix:semicolon
multiline_comment|/* size of message */
DECL|member|msg_alen
id|ulong
id|msg_alen
suffix:semicolon
multiline_comment|/* answer length */
DECL|member|msg_answer
id|unchar
id|msg_answer
suffix:semicolon
multiline_comment|/* answer flag */
DECL|member|msg_ext
id|unchar
id|msg_ext
suffix:semicolon
multiline_comment|/* more messages */
DECL|member|msg_reserved
id|unchar
id|msg_reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|msg_text
r_char
id|msg_text
(braket
id|MSGLEN
op_plus
l_int|2
)braket
suffix:semicolon
multiline_comment|/* the message text */
DECL|typedef|gdth_msg_str
)brace
id|gdth_msg_str
suffix:semicolon
multiline_comment|/* get channel count IOCTL */
r_typedef
r_struct
(brace
DECL|member|channel_no
id|ulong
id|channel_no
suffix:semicolon
multiline_comment|/* number of channel */
DECL|member|drive_cnt
id|ulong
id|drive_cnt
suffix:semicolon
multiline_comment|/* number of drives */
DECL|member|siop_id
id|unchar
id|siop_id
suffix:semicolon
multiline_comment|/* SCSI processor ID */
DECL|member|siop_state
id|unchar
id|siop_state
suffix:semicolon
multiline_comment|/* SCSI processor state */
DECL|typedef|gdth_getch_str
)brace
id|gdth_getch_str
suffix:semicolon
multiline_comment|/* cache info/config IOCTL */
r_typedef
r_struct
(brace
DECL|member|version
id|ulong
id|version
suffix:semicolon
multiline_comment|/* firmware version */
DECL|member|state
id|ushort
id|state
suffix:semicolon
multiline_comment|/* cache state (on/off) */
DECL|member|strategy
id|ushort
id|strategy
suffix:semicolon
multiline_comment|/* cache strategy */
DECL|member|write_back
id|ushort
id|write_back
suffix:semicolon
multiline_comment|/* write back state (on/off) */
DECL|member|block_size
id|ushort
id|block_size
suffix:semicolon
multiline_comment|/* cache block size */
DECL|typedef|gdth_cpar_str
)brace
id|gdth_cpar_str
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|csize
id|ulong
id|csize
suffix:semicolon
multiline_comment|/* cache size */
DECL|member|read_cnt
id|ulong
id|read_cnt
suffix:semicolon
multiline_comment|/* read/write counter */
DECL|member|write_cnt
id|ulong
id|write_cnt
suffix:semicolon
DECL|member|tr_hits
id|ulong
id|tr_hits
suffix:semicolon
multiline_comment|/* hits */
DECL|member|sec_hits
id|ulong
id|sec_hits
suffix:semicolon
DECL|member|sec_miss
id|ulong
id|sec_miss
suffix:semicolon
multiline_comment|/* misses */
DECL|typedef|gdth_cstat_str
)brace
id|gdth_cstat_str
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|cpar
id|gdth_cpar_str
id|cpar
suffix:semicolon
DECL|member|cstat
id|gdth_cstat_str
id|cstat
suffix:semicolon
DECL|typedef|gdth_cinfo_str
)brace
id|gdth_cinfo_str
suffix:semicolon
multiline_comment|/* scatter/gather element */
r_typedef
r_struct
(brace
DECL|member|sg_ptr
id|ulong
id|sg_ptr
suffix:semicolon
multiline_comment|/* address */
DECL|member|sg_len
id|ulong
id|sg_len
suffix:semicolon
multiline_comment|/* length */
DECL|typedef|gdth_sg_str
)brace
id|gdth_sg_str
suffix:semicolon
multiline_comment|/* command structure */
r_typedef
r_struct
(brace
DECL|member|BoardNode
id|ulong
id|BoardNode
suffix:semicolon
multiline_comment|/* board node (always 0) */
DECL|member|CommandIndex
id|ulong
id|CommandIndex
suffix:semicolon
multiline_comment|/* command number */
DECL|member|OpCode
id|ushort
id|OpCode
suffix:semicolon
multiline_comment|/* the command (READ,..) */
r_union
(brace
r_struct
(brace
DECL|member|DeviceNo
id|ushort
id|DeviceNo
suffix:semicolon
multiline_comment|/* number of cache drive */
DECL|member|BlockNo
id|ulong
id|BlockNo
suffix:semicolon
multiline_comment|/* block number */
DECL|member|BlockCnt
id|ulong
id|BlockCnt
suffix:semicolon
multiline_comment|/* block count */
DECL|member|DestAddr
id|ulong
id|DestAddr
suffix:semicolon
multiline_comment|/* dest. addr. (if s/g: -1) */
DECL|member|sg_canz
id|ulong
id|sg_canz
suffix:semicolon
multiline_comment|/* s/g element count */
DECL|member|sg_lst
id|gdth_sg_str
id|sg_lst
(braket
id|GDTH_MAXSG
)braket
suffix:semicolon
multiline_comment|/* s/g list */
DECL|member|cache
)brace
id|cache
suffix:semicolon
multiline_comment|/* cache service cmd. str. */
r_struct
(brace
DECL|member|param_size
id|ushort
id|param_size
suffix:semicolon
multiline_comment|/* size of p_param buffer */
DECL|member|subfunc
id|ulong
id|subfunc
suffix:semicolon
multiline_comment|/* IOCTL function */
DECL|member|channel
id|ulong
id|channel
suffix:semicolon
multiline_comment|/* device */
DECL|member|p_param
id|ulong
id|p_param
suffix:semicolon
multiline_comment|/* buffer */
DECL|member|ioctl
)brace
id|ioctl
suffix:semicolon
multiline_comment|/* IOCTL command structure */
r_struct
(brace
DECL|member|reserved
id|ushort
id|reserved
suffix:semicolon
DECL|member|msg_handle
id|ulong
id|msg_handle
suffix:semicolon
multiline_comment|/* message handle */
DECL|member|msg_addr
id|ulong
id|msg_addr
suffix:semicolon
multiline_comment|/* message buffer address */
DECL|member|screen
)brace
id|screen
suffix:semicolon
multiline_comment|/* screen service cmd. str. */
r_struct
(brace
DECL|member|reserved
id|ushort
id|reserved
suffix:semicolon
DECL|member|direction
id|ulong
id|direction
suffix:semicolon
multiline_comment|/* data direction */
DECL|member|mdisc_time
id|ulong
id|mdisc_time
suffix:semicolon
multiline_comment|/* disc. time (0: no timeout)*/
DECL|member|mcon_time
id|ulong
id|mcon_time
suffix:semicolon
multiline_comment|/* connect time(0: no to.) */
DECL|member|sdata
id|ulong
id|sdata
suffix:semicolon
multiline_comment|/* dest. addr. (if s/g: -1) */
DECL|member|sdlen
id|ulong
id|sdlen
suffix:semicolon
multiline_comment|/* data length (bytes) */
DECL|member|clen
id|ulong
id|clen
suffix:semicolon
multiline_comment|/* SCSI cmd. length(6,10,12) */
DECL|member|cmd
id|unchar
id|cmd
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* SCSI command */
DECL|member|target
id|unchar
id|target
suffix:semicolon
multiline_comment|/* target ID */
DECL|member|lun
id|unchar
id|lun
suffix:semicolon
multiline_comment|/* LUN */
DECL|member|bus
id|unchar
id|bus
suffix:semicolon
multiline_comment|/* SCSI bus number */
DECL|member|priority
id|unchar
id|priority
suffix:semicolon
multiline_comment|/* only 0 used */
DECL|member|sense_len
id|ulong
id|sense_len
suffix:semicolon
multiline_comment|/* sense data length */
DECL|member|sense_data
id|ulong
id|sense_data
suffix:semicolon
multiline_comment|/* sense data addr. */
DECL|member|link_p
r_struct
id|raw
op_star
id|link_p
suffix:semicolon
multiline_comment|/* linked cmds (not supp.) */
DECL|member|sg_ranz
id|ulong
id|sg_ranz
suffix:semicolon
multiline_comment|/* s/g element count */
DECL|member|sg_lst
id|gdth_sg_str
id|sg_lst
(braket
id|GDTH_MAXSG
)braket
suffix:semicolon
multiline_comment|/* s/g list */
DECL|member|raw
)brace
id|raw
suffix:semicolon
multiline_comment|/* raw service cmd. struct. */
DECL|member|u
)brace
id|u
suffix:semicolon
multiline_comment|/* additional variables */
DECL|member|Service
id|unchar
id|Service
suffix:semicolon
multiline_comment|/* controller service */
DECL|member|Status
id|ushort
id|Status
suffix:semicolon
multiline_comment|/* command result */
DECL|member|Info
id|ulong
id|Info
suffix:semicolon
multiline_comment|/* additional information */
DECL|member|RequestBuffer
id|Scsi_Cmnd
op_star
id|RequestBuffer
suffix:semicolon
multiline_comment|/* request buffer */
DECL|typedef|gdth_cmd_str
)brace
id|gdth_cmd_str
suffix:semicolon
multiline_comment|/* controller event structure */
DECL|macro|ES_ASYNC
mdefine_line|#define ES_ASYNC    1
DECL|macro|ES_DRIVER
mdefine_line|#define ES_DRIVER   2
DECL|macro|ES_TEST
mdefine_line|#define ES_TEST     3
DECL|macro|ES_SYNC
mdefine_line|#define ES_SYNC     4
r_typedef
r_struct
(brace
DECL|member|size
id|ushort
id|size
suffix:semicolon
multiline_comment|/* size of structure */
r_union
(brace
DECL|member|stream
r_char
id|stream
(braket
l_int|16
)braket
suffix:semicolon
r_struct
(brace
DECL|member|ionode
id|ushort
id|ionode
suffix:semicolon
DECL|member|service
id|ushort
id|service
suffix:semicolon
DECL|member|index
id|ulong
id|index
suffix:semicolon
DECL|member|driver
)brace
id|driver
suffix:semicolon
r_struct
(brace
DECL|member|ionode
id|ushort
id|ionode
suffix:semicolon
DECL|member|service
id|ushort
id|service
suffix:semicolon
DECL|member|status
id|ushort
id|status
suffix:semicolon
DECL|member|info
id|ulong
id|info
suffix:semicolon
DECL|member|scsi_coord
id|unchar
id|scsi_coord
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|async
)brace
id|async
suffix:semicolon
r_struct
(brace
DECL|member|ionode
id|ushort
id|ionode
suffix:semicolon
DECL|member|service
id|ushort
id|service
suffix:semicolon
DECL|member|status
id|ushort
id|status
suffix:semicolon
DECL|member|info
id|ulong
id|info
suffix:semicolon
DECL|member|hostdrive
id|ushort
id|hostdrive
suffix:semicolon
DECL|member|scsi_coord
id|unchar
id|scsi_coord
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|sense_key
id|unchar
id|sense_key
suffix:semicolon
DECL|member|sync
)brace
id|sync
suffix:semicolon
r_struct
(brace
DECL|member|l1
DECL|member|l2
DECL|member|l3
DECL|member|l4
id|ulong
id|l1
comma
id|l2
comma
id|l3
comma
id|l4
suffix:semicolon
DECL|member|test
)brace
id|test
suffix:semicolon
DECL|member|eu
)brace
id|eu
suffix:semicolon
DECL|typedef|gdth_evt_data
)brace
id|gdth_evt_data
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|first_stamp
id|ulong
id|first_stamp
suffix:semicolon
DECL|member|last_stamp
id|ulong
id|last_stamp
suffix:semicolon
DECL|member|same_count
id|ushort
id|same_count
suffix:semicolon
DECL|member|event_source
id|ushort
id|event_source
suffix:semicolon
DECL|member|event_idx
id|ushort
id|event_idx
suffix:semicolon
DECL|member|application
id|unchar
id|application
suffix:semicolon
DECL|member|reserved
id|unchar
id|reserved
suffix:semicolon
DECL|member|event_data
id|gdth_evt_data
id|event_data
suffix:semicolon
DECL|typedef|gdth_evt_str
)brace
id|gdth_evt_str
suffix:semicolon
multiline_comment|/* DPRAM structures */
multiline_comment|/* interface area ISA/PCI */
r_typedef
r_struct
(brace
DECL|member|S_Cmd_Indx
id|unchar
id|S_Cmd_Indx
suffix:semicolon
multiline_comment|/* special command */
DECL|member|S_Status
id|unchar
r_volatile
id|S_Status
suffix:semicolon
multiline_comment|/* status special command */
DECL|member|reserved1
id|ushort
id|reserved1
suffix:semicolon
DECL|member|S_Info
id|ulong
id|S_Info
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* add. info special command */
DECL|member|Sema0
id|unchar
r_volatile
id|Sema0
suffix:semicolon
multiline_comment|/* command semaphore */
DECL|member|reserved2
id|unchar
id|reserved2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|Cmd_Index
id|unchar
id|Cmd_Index
suffix:semicolon
multiline_comment|/* command number */
DECL|member|reserved3
id|unchar
id|reserved3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|Status
id|ushort
r_volatile
id|Status
suffix:semicolon
multiline_comment|/* command status */
DECL|member|Service
id|ushort
id|Service
suffix:semicolon
multiline_comment|/* service(for async.events) */
DECL|member|Info
id|ulong
id|Info
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* additional info */
r_struct
(brace
DECL|member|offset
id|ushort
id|offset
suffix:semicolon
multiline_comment|/* command offs. in the DPRAM*/
DECL|member|serv_id
id|ushort
id|serv_id
suffix:semicolon
multiline_comment|/* service */
DECL|member|comm_queue
)brace
id|comm_queue
(braket
id|MAXOFFSETS
)braket
suffix:semicolon
multiline_comment|/* command queue */
DECL|member|bios_reserved
id|ulong
id|bios_reserved
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|gdt_dpr_cmd
id|unchar
id|gdt_dpr_cmd
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* commands */
DECL|typedef|gdt_dpr_if
)brace
id|gdt_dpr_if
suffix:semicolon
multiline_comment|/* SRAM structure PCI controllers */
r_typedef
r_struct
(brace
DECL|member|magic
id|ulong
id|magic
suffix:semicolon
multiline_comment|/* controller ID from BIOS */
DECL|member|need_deinit
id|ushort
id|need_deinit
suffix:semicolon
multiline_comment|/* switch betw. BIOS/driver */
DECL|member|switch_support
id|unchar
id|switch_support
suffix:semicolon
multiline_comment|/* see need_deinit */
DECL|member|padding
id|unchar
id|padding
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|os_used
id|unchar
id|os_used
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* OS code per service */
DECL|member|unused
id|unchar
id|unused
(braket
l_int|28
)braket
suffix:semicolon
DECL|member|fw_magic
id|unchar
id|fw_magic
suffix:semicolon
multiline_comment|/* contr. ID from firmware */
DECL|typedef|gdt_pci_sram
)brace
id|gdt_pci_sram
suffix:semicolon
multiline_comment|/* SRAM structure EISA controllers (but NOT GDT3000/3020) */
r_typedef
r_struct
(brace
DECL|member|os_used
id|unchar
id|os_used
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* OS code per service */
DECL|member|need_deinit
id|ushort
id|need_deinit
suffix:semicolon
multiline_comment|/* switch betw. BIOS/driver */
DECL|member|switch_support
id|unchar
id|switch_support
suffix:semicolon
multiline_comment|/* see need_deinit */
DECL|member|padding
id|unchar
id|padding
suffix:semicolon
DECL|typedef|gdt_eisa_sram
)brace
id|gdt_eisa_sram
suffix:semicolon
multiline_comment|/* DPRAM ISA controllers */
r_typedef
r_struct
(brace
r_union
(brace
r_struct
(brace
DECL|member|bios_used
id|unchar
id|bios_used
(braket
l_int|0x3c00
op_minus
l_int|32
)braket
suffix:semicolon
multiline_comment|/* 15KB - 32Bytes BIOS */
DECL|member|magic
id|ulong
id|magic
suffix:semicolon
multiline_comment|/* controller (EISA) ID */
DECL|member|need_deinit
id|ushort
id|need_deinit
suffix:semicolon
multiline_comment|/* switch betw. BIOS/driver */
DECL|member|switch_support
id|unchar
id|switch_support
suffix:semicolon
multiline_comment|/* see need_deinit */
DECL|member|padding
id|unchar
id|padding
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|os_used
id|unchar
id|os_used
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* OS code per service */
DECL|member|dp_sram
)brace
id|dp_sram
suffix:semicolon
DECL|member|bios_area
id|unchar
id|bios_area
(braket
l_int|0x4000
)braket
suffix:semicolon
multiline_comment|/* 16KB reserved for BIOS */
DECL|member|bu
)brace
id|bu
suffix:semicolon
r_union
(brace
DECL|member|ic
id|gdt_dpr_if
id|ic
suffix:semicolon
multiline_comment|/* interface area */
DECL|member|if_area
id|unchar
id|if_area
(braket
l_int|0x3000
)braket
suffix:semicolon
multiline_comment|/* 12KB for interface */
DECL|member|u
)brace
id|u
suffix:semicolon
r_struct
(brace
DECL|member|memlock
id|unchar
id|memlock
suffix:semicolon
multiline_comment|/* write protection DPRAM */
DECL|member|event
id|unchar
id|event
suffix:semicolon
multiline_comment|/* release event */
DECL|member|irqen
id|unchar
id|irqen
suffix:semicolon
multiline_comment|/* board interrupts enable */
DECL|member|irqdel
id|unchar
id|irqdel
suffix:semicolon
multiline_comment|/* acknowledge board int. */
DECL|member|Sema1
id|unchar
r_volatile
id|Sema1
suffix:semicolon
multiline_comment|/* status semaphore */
DECL|member|rq
id|unchar
id|rq
suffix:semicolon
multiline_comment|/* IRQ/DRQ configuration */
DECL|member|io
)brace
id|io
suffix:semicolon
DECL|typedef|gdt2_dpram_str
)brace
id|gdt2_dpram_str
suffix:semicolon
multiline_comment|/* DPRAM PCI controllers */
r_typedef
r_struct
(brace
r_union
(brace
DECL|member|ic
id|gdt_dpr_if
id|ic
suffix:semicolon
multiline_comment|/* interface area */
DECL|member|if_area
id|unchar
id|if_area
(braket
l_int|0xff0
op_minus
r_sizeof
(paren
id|gdt_pci_sram
)paren
)braket
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|gdt6sr
id|gdt_pci_sram
id|gdt6sr
suffix:semicolon
multiline_comment|/* SRAM structure */
r_struct
(brace
DECL|member|unused0
id|unchar
id|unused0
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|Sema1
id|unchar
r_volatile
id|Sema1
suffix:semicolon
multiline_comment|/* command semaphore */
DECL|member|unused1
id|unchar
id|unused1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|irqen
id|unchar
id|irqen
suffix:semicolon
multiline_comment|/* board interrupts enable */
DECL|member|unused2
id|unchar
id|unused2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|event
id|unchar
id|event
suffix:semicolon
multiline_comment|/* release event */
DECL|member|unused3
id|unchar
id|unused3
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|irqdel
id|unchar
id|irqdel
suffix:semicolon
multiline_comment|/* acknowledge board int. */
DECL|member|unused4
id|unchar
id|unused4
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|io
)brace
id|io
suffix:semicolon
DECL|typedef|gdt6_dpram_str
)brace
id|gdt6_dpram_str
suffix:semicolon
multiline_comment|/* PLX register structure (new PCI controllers) */
r_typedef
r_struct
(brace
DECL|member|cfg_reg
id|unchar
id|cfg_reg
suffix:semicolon
multiline_comment|/* DPRAM cfg.(2:below 1MB,0:anywhere)*/
DECL|member|unused1
id|unchar
id|unused1
(braket
l_int|0x3f
)braket
suffix:semicolon
DECL|member|sema0_reg
id|unchar
r_volatile
id|sema0_reg
suffix:semicolon
multiline_comment|/* command semaphore */
DECL|member|sema1_reg
id|unchar
r_volatile
id|sema1_reg
suffix:semicolon
multiline_comment|/* status semaphore */
DECL|member|unused2
id|unchar
id|unused2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|status
id|ushort
r_volatile
id|status
suffix:semicolon
multiline_comment|/* command status */
DECL|member|service
id|ushort
id|service
suffix:semicolon
multiline_comment|/* service */
DECL|member|info
id|ulong
id|info
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* additional info */
DECL|member|unused3
id|unchar
id|unused3
(braket
l_int|0x10
)braket
suffix:semicolon
DECL|member|ldoor_reg
id|unchar
id|ldoor_reg
suffix:semicolon
multiline_comment|/* PCI to local doorbell */
DECL|member|unused4
id|unchar
id|unused4
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|edoor_reg
id|unchar
r_volatile
id|edoor_reg
suffix:semicolon
multiline_comment|/* local to PCI doorbell */
DECL|member|unused5
id|unchar
id|unused5
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|control0
id|unchar
id|control0
suffix:semicolon
multiline_comment|/* control0 register(unused) */
DECL|member|control1
id|unchar
id|control1
suffix:semicolon
multiline_comment|/* board interrupts enable */
DECL|member|unused6
id|unchar
id|unused6
(braket
l_int|0x16
)braket
suffix:semicolon
DECL|typedef|gdt6c_plx_regs
)brace
id|gdt6c_plx_regs
suffix:semicolon
multiline_comment|/* DPRAM new PCI controllers */
r_typedef
r_struct
(brace
r_union
(brace
DECL|member|ic
id|gdt_dpr_if
id|ic
suffix:semicolon
multiline_comment|/* interface area */
DECL|member|if_area
id|unchar
id|if_area
(braket
l_int|0x4000
op_minus
r_sizeof
(paren
id|gdt_pci_sram
)paren
)braket
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|gdt6sr
id|gdt_pci_sram
id|gdt6sr
suffix:semicolon
multiline_comment|/* SRAM structure */
DECL|typedef|gdt6c_dpram_str
)brace
id|gdt6c_dpram_str
suffix:semicolon
multiline_comment|/* i960 register structure (PCI MPR controllers) */
r_typedef
r_struct
(brace
DECL|member|unused1
id|unchar
id|unused1
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|sema0_reg
id|unchar
r_volatile
id|sema0_reg
suffix:semicolon
multiline_comment|/* command semaphore */
DECL|member|unused2
id|unchar
id|unused2
suffix:semicolon
DECL|member|sema1_reg
id|unchar
r_volatile
id|sema1_reg
suffix:semicolon
multiline_comment|/* status semaphore */
DECL|member|unused3
id|unchar
id|unused3
suffix:semicolon
DECL|member|status
id|ushort
r_volatile
id|status
suffix:semicolon
multiline_comment|/* command status */
DECL|member|service
id|ushort
id|service
suffix:semicolon
multiline_comment|/* service */
DECL|member|info
id|ulong
id|info
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* additional info */
DECL|member|ldoor_reg
id|unchar
id|ldoor_reg
suffix:semicolon
multiline_comment|/* PCI to local doorbell */
DECL|member|unused4
id|unchar
id|unused4
(braket
l_int|11
)braket
suffix:semicolon
DECL|member|edoor_reg
id|unchar
r_volatile
id|edoor_reg
suffix:semicolon
multiline_comment|/* local to PCI doorbell */
DECL|member|unused5
id|unchar
id|unused5
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|edoor_en_reg
id|unchar
id|edoor_en_reg
suffix:semicolon
multiline_comment|/* board interrupts enable */
DECL|member|unused6
id|unchar
id|unused6
(braket
l_int|27
)braket
suffix:semicolon
DECL|member|unused7
id|ulong
id|unused7
(braket
l_int|1004
)braket
suffix:semicolon
multiline_comment|/* size: 4 KB */
DECL|typedef|gdt6m_i960_regs
)brace
id|gdt6m_i960_regs
suffix:semicolon
multiline_comment|/* DPRAM PCI MPR controllers */
r_typedef
r_struct
(brace
DECL|member|i960r
id|gdt6m_i960_regs
id|i960r
suffix:semicolon
multiline_comment|/* 4KB i960 registers */
r_union
(brace
DECL|member|ic
id|gdt_dpr_if
id|ic
suffix:semicolon
multiline_comment|/* interface area */
DECL|member|if_area
id|unchar
id|if_area
(braket
l_int|0x3000
op_minus
r_sizeof
(paren
id|gdt_pci_sram
)paren
)braket
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
DECL|member|gdt6sr
id|gdt_pci_sram
id|gdt6sr
suffix:semicolon
multiline_comment|/* SRAM structure */
DECL|typedef|gdt6m_dpram_str
)brace
id|gdt6m_dpram_str
suffix:semicolon
multiline_comment|/* PCI resources */
r_typedef
r_struct
(brace
DECL|member|device_id
id|ushort
id|device_id
suffix:semicolon
multiline_comment|/* device ID (0,..,9) */
DECL|member|bus
id|unchar
id|bus
suffix:semicolon
multiline_comment|/* PCI bus */
DECL|member|device_fn
id|unchar
id|device_fn
suffix:semicolon
multiline_comment|/* PCI device/function no. */
DECL|member|dpmem
id|ulong
id|dpmem
suffix:semicolon
multiline_comment|/* DPRAM address */
DECL|member|io
id|ulong
id|io
suffix:semicolon
multiline_comment|/* IO address */
DECL|member|io_mm
id|ulong
id|io_mm
suffix:semicolon
multiline_comment|/* IO address mem. mapped */
DECL|member|bios
id|ulong
id|bios
suffix:semicolon
multiline_comment|/* BIOS address */
DECL|member|irq
id|unchar
id|irq
suffix:semicolon
multiline_comment|/* IRQ */
DECL|typedef|gdth_pci_str
)brace
id|gdth_pci_str
suffix:semicolon
multiline_comment|/* controller information structure */
r_typedef
r_struct
(brace
DECL|member|bus_cnt
id|unchar
id|bus_cnt
suffix:semicolon
multiline_comment|/* SCSI bus count */
DECL|member|type
id|unchar
id|type
suffix:semicolon
multiline_comment|/* controller class */
DECL|member|raw_feat
id|ushort
id|raw_feat
suffix:semicolon
multiline_comment|/* feat. raw service (s/g,..) */
DECL|member|stype
id|ulong
id|stype
suffix:semicolon
multiline_comment|/* controller subtype */
DECL|member|cache_feat
id|ushort
id|cache_feat
suffix:semicolon
multiline_comment|/* feat. cache serv. (s/g,..) */
DECL|member|bmic
id|ushort
id|bmic
suffix:semicolon
multiline_comment|/* BMIC address (EISA) */
DECL|member|brd
r_void
op_star
id|brd
suffix:semicolon
multiline_comment|/* DPRAM address */
DECL|member|brd_phys
id|ulong
id|brd_phys
suffix:semicolon
multiline_comment|/* slot number/BIOS address */
DECL|member|plx
id|gdt6c_plx_regs
op_star
id|plx
suffix:semicolon
multiline_comment|/* PLX regs (new PCI contr.) */
DECL|member|pccb
id|gdth_cmd_str
op_star
id|pccb
suffix:semicolon
multiline_comment|/* address command structure */
DECL|member|pscratch
id|gdth_scratch_str
op_star
id|pscratch
suffix:semicolon
DECL|member|irq
id|unchar
id|irq
suffix:semicolon
multiline_comment|/* IRQ */
DECL|member|drq
id|unchar
id|drq
suffix:semicolon
multiline_comment|/* DRQ (ISA controllers) */
DECL|member|status
id|ushort
id|status
suffix:semicolon
multiline_comment|/* command status */
DECL|member|info
id|ulong
id|info
suffix:semicolon
DECL|member|info2
id|ulong
id|info2
suffix:semicolon
multiline_comment|/* additional info */
DECL|member|req_first
id|Scsi_Cmnd
op_star
id|req_first
suffix:semicolon
multiline_comment|/* top of request queue */
r_struct
(brace
DECL|member|type
id|unchar
id|type
suffix:semicolon
multiline_comment|/* device type */
DECL|member|heads
id|unchar
id|heads
suffix:semicolon
multiline_comment|/* mapping */
DECL|member|secs
id|unchar
id|secs
suffix:semicolon
DECL|member|lock
id|unchar
id|lock
suffix:semicolon
multiline_comment|/* drive locked ? (hot plug) */
DECL|member|hostdrive
id|ushort
id|hostdrive
suffix:semicolon
multiline_comment|/* host drive number */
DECL|member|devtype
id|ushort
id|devtype
suffix:semicolon
multiline_comment|/* further information */
DECL|member|size
id|ulong
id|size
suffix:semicolon
multiline_comment|/* capacity */
DECL|member|id
)brace
id|id
(braket
id|MAXBUS
)braket
(braket
id|MAXID
)braket
suffix:semicolon
DECL|member|cmd_cnt
id|ushort
id|cmd_cnt
suffix:semicolon
multiline_comment|/* command count in DPRAM */
DECL|member|cmd_len
id|ushort
id|cmd_len
suffix:semicolon
multiline_comment|/* length of actual command */
DECL|member|cmd_offs_dpmem
id|ushort
id|cmd_offs_dpmem
suffix:semicolon
multiline_comment|/* actual offset in DPRAM */
DECL|member|ic_all_size
id|ushort
id|ic_all_size
suffix:semicolon
multiline_comment|/* sizeof DPRAM interf. area */
DECL|member|reserved
id|unchar
id|reserved
suffix:semicolon
DECL|member|mode
id|unchar
id|mode
suffix:semicolon
multiline_comment|/* information from /proc */
DECL|member|param_size
id|ushort
id|param_size
suffix:semicolon
DECL|member|cpar
id|gdth_cpar_str
id|cpar
suffix:semicolon
multiline_comment|/* controller cache par. */
DECL|typedef|gdth_ha_str
)brace
id|gdth_ha_str
suffix:semicolon
multiline_comment|/* structure for scsi_register(), SCSI bus != 0 */
r_typedef
r_struct
(brace
DECL|member|hanum
id|ushort
id|hanum
suffix:semicolon
DECL|member|busnum
id|ushort
id|busnum
suffix:semicolon
DECL|typedef|gdth_num_str
)brace
id|gdth_num_str
suffix:semicolon
multiline_comment|/* structure for scsi_register() */
r_typedef
r_struct
(brace
DECL|member|numext
id|gdth_num_str
id|numext
suffix:semicolon
multiline_comment|/* must be the first element */
DECL|member|haext
id|gdth_ha_str
id|haext
suffix:semicolon
DECL|member|cmdext
id|gdth_cmd_str
id|cmdext
suffix:semicolon
DECL|member|dmaext
id|gdth_scratch_str
id|dmaext
suffix:semicolon
DECL|typedef|gdth_ext_str
)brace
id|gdth_ext_str
suffix:semicolon
multiline_comment|/* INQUIRY data format */
r_typedef
r_struct
(brace
DECL|member|type_qual
id|unchar
id|type_qual
suffix:semicolon
DECL|member|modif_rmb
id|unchar
id|modif_rmb
suffix:semicolon
DECL|member|version
id|unchar
id|version
suffix:semicolon
DECL|member|resp_aenc
id|unchar
id|resp_aenc
suffix:semicolon
DECL|member|add_length
id|unchar
id|add_length
suffix:semicolon
DECL|member|reserved1
id|unchar
id|reserved1
suffix:semicolon
DECL|member|reserved2
id|unchar
id|reserved2
suffix:semicolon
DECL|member|misc
id|unchar
id|misc
suffix:semicolon
DECL|member|vendor
id|unchar
id|vendor
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|product
id|unchar
id|product
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|revision
id|unchar
id|revision
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|gdth_inq_data
)brace
id|gdth_inq_data
suffix:semicolon
multiline_comment|/* READ_CAPACITY data format */
r_typedef
r_struct
(brace
DECL|member|last_block_no
id|ulong
id|last_block_no
suffix:semicolon
DECL|member|block_length
id|ulong
id|block_length
suffix:semicolon
DECL|typedef|gdth_rdcap_data
)brace
id|gdth_rdcap_data
suffix:semicolon
multiline_comment|/* REQUEST_SENSE data format */
r_typedef
r_struct
(brace
DECL|member|errorcode
id|unchar
id|errorcode
suffix:semicolon
DECL|member|segno
id|unchar
id|segno
suffix:semicolon
DECL|member|key
id|unchar
id|key
suffix:semicolon
DECL|member|info
id|ulong
id|info
suffix:semicolon
DECL|member|add_length
id|unchar
id|add_length
suffix:semicolon
DECL|member|cmd_info
id|ulong
id|cmd_info
suffix:semicolon
DECL|member|adsc
id|unchar
id|adsc
suffix:semicolon
DECL|member|adsq
id|unchar
id|adsq
suffix:semicolon
DECL|member|fruc
id|unchar
id|fruc
suffix:semicolon
DECL|member|key_spec
id|unchar
id|key_spec
(braket
l_int|3
)braket
suffix:semicolon
DECL|typedef|gdth_sense_data
)brace
id|gdth_sense_data
suffix:semicolon
multiline_comment|/* MODE_SENSE data format */
r_typedef
r_struct
(brace
r_struct
(brace
DECL|member|data_length
id|unchar
id|data_length
suffix:semicolon
DECL|member|med_type
id|unchar
id|med_type
suffix:semicolon
DECL|member|dev_par
id|unchar
id|dev_par
suffix:semicolon
DECL|member|bd_length
id|unchar
id|bd_length
suffix:semicolon
DECL|member|hd
)brace
id|hd
suffix:semicolon
r_struct
(brace
DECL|member|dens_code
id|unchar
id|dens_code
suffix:semicolon
DECL|member|block_count
id|unchar
id|block_count
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|reserved
id|unchar
id|reserved
suffix:semicolon
DECL|member|block_length
id|unchar
id|block_length
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|bd
)brace
id|bd
suffix:semicolon
DECL|typedef|gdth_modep_data
)brace
id|gdth_modep_data
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|b
id|ulong
id|b
(braket
l_int|10
)braket
suffix:semicolon
multiline_comment|/* 32 bit compiler ! */
DECL|typedef|gdth_stackframe
)brace
id|gdth_stackframe
suffix:semicolon
macro_line|#pragma pack()
multiline_comment|/* function prototyping */
r_int
id|gdth_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_int
id|gdth_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|gdth_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|gdth_queuecommand
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
id|gdth_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x010346
r_int
id|gdth_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
id|reset_flags
)paren
suffix:semicolon
macro_line|#else
r_int
id|gdth_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
macro_line|#endif
r_const
r_char
op_star
id|gdth_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_int
id|gdth_bios_param
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
r_extern
r_struct
id|proc_dir_entry
id|proc_scsi_gdth
suffix:semicolon
r_int
id|gdth_proc_info
c_func
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|macro|GDTH
mdefine_line|#define GDTH { proc_dir:          &amp;proc_scsi_gdth,                     &bslash;&n;               proc_info:         gdth_proc_info,                      &bslash;&n;               name:              &quot;GDT SCSI Disk Array Controller&quot;,    &bslash;&n;               detect:            gdth_detect,                         &bslash;&n;               release:           gdth_release,                        &bslash;&n;               info:              gdth_info,                           &bslash;&n;               command:           gdth_command,                        &bslash;&n;               queuecommand:      gdth_queuecommand,                   &bslash;&n;               abort:             gdth_abort,                          &bslash;&n;               reset:             gdth_reset,                          &bslash;&n;               bios_param:        gdth_bios_param,                     &bslash;&n;               can_queue:         GDTH_MAXCMDS,                        &bslash;&n;               this_id:           -1,                                  &bslash;&n;               sg_tablesize:      GDTH_MAXSG,                          &bslash;&n;               cmd_per_lun:       GDTH_MAXC_P_L,                       &bslash;&n;               unchecked_isa_dma: 1,                                   &bslash;&n;               use_clustering:    ENABLE_CLUSTERING}
macro_line|#endif
eof