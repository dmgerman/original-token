multiline_comment|/*****************************************************************************/
multiline_comment|/* ips.h -- driver for the IBM ServeRAID adapter                             */
multiline_comment|/*                                                                           */
multiline_comment|/* Written By: Keith Mitchell, IBM Corporation                               */
multiline_comment|/*                                                                           */
multiline_comment|/* Copyright (C) 1999 IBM Corporation                                        */
multiline_comment|/*                                                                           */
multiline_comment|/* This program is free software; you can redistribute it and/or modify      */
multiline_comment|/* it under the terms of the GNU General Public License as published by      */
multiline_comment|/* the Free Software Foundation; either version 2 of the License, or         */
multiline_comment|/* (at your option) any later version.                                       */
multiline_comment|/*                                                                           */
multiline_comment|/* This program is distributed in the hope that it will be useful,           */
multiline_comment|/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
multiline_comment|/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
multiline_comment|/* GNU General Public License for more details.                              */
multiline_comment|/*                                                                           */
multiline_comment|/* NO WARRANTY                                                               */
multiline_comment|/* THE PROGRAM IS PROVIDED ON AN &quot;AS IS&quot; BASIS, WITHOUT WARRANTIES OR        */
multiline_comment|/* CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT      */
multiline_comment|/* LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,      */
multiline_comment|/* MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is    */
multiline_comment|/* solely responsible for determining the appropriateness of using and       */
multiline_comment|/* distributing the Program and assumes all risks associated with its        */
multiline_comment|/* exercise of rights under this Agreement, including but not limited to     */
multiline_comment|/* the risks and costs of program errors, damage to or loss of data,         */
multiline_comment|/* programs or equipment, and unavailability or interruption of operations.  */
multiline_comment|/*                                                                           */
multiline_comment|/* DISCLAIMER OF LIABILITY                                                   */
multiline_comment|/* NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY   */
multiline_comment|/* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL        */
multiline_comment|/* DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND   */
multiline_comment|/* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR     */
multiline_comment|/* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE    */
multiline_comment|/* USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED  */
multiline_comment|/* HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES             */
multiline_comment|/*                                                                           */
multiline_comment|/* You should have received a copy of the GNU General Public License         */
multiline_comment|/* along with this program; if not, write to the Free Software               */
multiline_comment|/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */
multiline_comment|/*                                                                           */
multiline_comment|/* Bugs/Comments/Suggestions should be mailed to:                            */
multiline_comment|/*      ipslinux@us.ibm.com                                                  */
multiline_comment|/*                                                                           */
multiline_comment|/*****************************************************************************/
macro_line|#ifndef _IPS_H_
DECL|macro|_IPS_H_
mdefine_line|#define _IPS_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* Prototypes */
r_extern
r_int
id|ips_detect
c_func
(paren
id|Scsi_Host_Template
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ips_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ips_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ips_reset
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
r_int
id|ips_eh_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ips_eh_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|ips_queue
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_extern
r_int
id|ips_biosparam
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
r_const
r_char
op_star
id|ips_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_void
id|do_ipsintr
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
multiline_comment|/*&n;    * Some handy macros&n;    */
macro_line|#ifndef LinuxVersionCode
DECL|macro|LinuxVersionCode
mdefine_line|#define LinuxVersionCode(x,y,z)   (((x)&lt;&lt;16)+((y)&lt;&lt;8)+(z))
macro_line|#endif
DECL|macro|HA
mdefine_line|#define HA(x)                       ((ips_ha_t *) x-&gt;hostdata)
DECL|macro|IPS_COMMAND_ID
mdefine_line|#define IPS_COMMAND_ID(ha, scb)     (int) (scb - ha-&gt;scbs)
DECL|macro|VIRT_TO_BUS
mdefine_line|#define VIRT_TO_BUS(x)              (unsigned int)virt_to_bus((void *) x)
DECL|macro|UDELAY
mdefine_line|#define UDELAY udelay
DECL|macro|MDELAY
mdefine_line|#define MDELAY mdelay
DECL|macro|verify_area_20
mdefine_line|#define verify_area_20(t,a,sz)               (0) /* success */
DECL|macro|PUT_USER
mdefine_line|#define PUT_USER                             put_user
DECL|macro|__PUT_USER
mdefine_line|#define __PUT_USER                           __put_user
DECL|macro|PUT_USER_RET
mdefine_line|#define PUT_USER_RET                         put_user_ret
DECL|macro|GET_USER
mdefine_line|#define GET_USER                             get_user
DECL|macro|__GET_USER
mdefine_line|#define __GET_USER                           __get_user
DECL|macro|GET_USER_RET
mdefine_line|#define GET_USER_RET                         get_user_ret
multiline_comment|/*&n; * Adapter address map equates&n; */
DECL|macro|HISR
mdefine_line|#define HISR                 0x08    /* Host Interrupt Status Reg   */
DECL|macro|CCSAR
mdefine_line|#define CCSAR                0x10    /* Cmd Channel System Addr Reg */
DECL|macro|CCCR
mdefine_line|#define CCCR                 0x14    /* Cmd Channel Control Reg     */
DECL|macro|SQHR
mdefine_line|#define SQHR                 0x20    /* Status Q Head Reg           */
DECL|macro|SQTR
mdefine_line|#define SQTR                 0x24    /* Status Q Tail Reg           */
DECL|macro|SQER
mdefine_line|#define SQER                 0x28    /* Status Q End Reg            */
DECL|macro|SQSR
mdefine_line|#define SQSR                 0x2C    /* Status Q Start Reg          */
DECL|macro|SCPR
mdefine_line|#define SCPR                 0x05    /* Subsystem control port reg  */
DECL|macro|ISPR
mdefine_line|#define ISPR                 0x06    /* interrupt status port reg   */
DECL|macro|CBSP
mdefine_line|#define CBSP                 0x07    /* CBSP register               */
multiline_comment|/*&n; * Adapter register bit equates&n; */
DECL|macro|GHI
mdefine_line|#define GHI                  0x04    /* HISR General Host Interrupt */
DECL|macro|SQO
mdefine_line|#define SQO                  0x02    /* HISR Status Q Overflow      */
DECL|macro|SCE
mdefine_line|#define SCE                  0x01    /* HISR Status Channel Enqueue */
DECL|macro|SEMAPHORE
mdefine_line|#define SEMAPHORE            0x08    /* CCCR Semaphore Bit          */
DECL|macro|ILE
mdefine_line|#define ILE                  0x10    /* CCCR ILE Bit                */
DECL|macro|START_COMMAND
mdefine_line|#define START_COMMAND        0x101A  /* CCCR Start Command Channel  */
DECL|macro|START_STOP_BIT
mdefine_line|#define START_STOP_BIT       0x0002  /* CCCR Start/Stop Bit         */
DECL|macro|RST
mdefine_line|#define RST                  0x80    /* SCPR Reset Bit              */
DECL|macro|EBM
mdefine_line|#define EBM                  0x02    /* SCPR Enable Bus Master      */
DECL|macro|EI
mdefine_line|#define EI                   0x80    /* HISR Enable Interrupts      */
DECL|macro|OP
mdefine_line|#define OP                   0x01    /* OP bit in CBSP              */
multiline_comment|/*&n; * Adapter Command ID Equates&n; */
DECL|macro|GET_LOGICAL_DRIVE_INFO
mdefine_line|#define GET_LOGICAL_DRIVE_INFO               0x19
DECL|macro|GET_SUBSYS_PARAM
mdefine_line|#define GET_SUBSYS_PARAM                     0x40
DECL|macro|READ_NVRAM_CONFIGURATION
mdefine_line|#define READ_NVRAM_CONFIGURATION             0x38
DECL|macro|RW_NVRAM_PAGE
mdefine_line|#define RW_NVRAM_PAGE                        0xBC
DECL|macro|IPS_READ
mdefine_line|#define IPS_READ                             0x02
DECL|macro|IPS_WRITE
mdefine_line|#define IPS_WRITE                            0x03
DECL|macro|ENQUIRY
mdefine_line|#define ENQUIRY                              0x05
DECL|macro|FLUSH_CACHE
mdefine_line|#define FLUSH_CACHE                          0x0A
DECL|macro|NORM_STATE
mdefine_line|#define NORM_STATE                           0x00
DECL|macro|READ_SCATTER_GATHER
mdefine_line|#define READ_SCATTER_GATHER                  0x82
DECL|macro|WRITE_SCATTER_GATHER
mdefine_line|#define WRITE_SCATTER_GATHER                 0x83
DECL|macro|DIRECT_CDB
mdefine_line|#define DIRECT_CDB                           0x04
DECL|macro|DIRECT_CDB_SCATTER_GATHER
mdefine_line|#define DIRECT_CDB_SCATTER_GATHER            0x84
DECL|macro|CONFIG_SYNC
mdefine_line|#define CONFIG_SYNC                          0x58
DECL|macro|POCL
mdefine_line|#define POCL                                 0x30
DECL|macro|GET_ERASE_ERROR_TABLE
mdefine_line|#define GET_ERASE_ERROR_TABLE                0x17
DECL|macro|RESET_CHANNEL
mdefine_line|#define RESET_CHANNEL                        0x1A
DECL|macro|CSL
mdefine_line|#define CSL                                  0xFF
DECL|macro|ADAPT_RESET
mdefine_line|#define ADAPT_RESET                          0xFF
multiline_comment|/*&n; * Adapter Equates&n; */
DECL|macro|IPS_MAX_ADAPTERS
mdefine_line|#define IPS_MAX_ADAPTERS                     16
DECL|macro|IPS_MAX_IOCTL
mdefine_line|#define IPS_MAX_IOCTL                        1
DECL|macro|IPS_MAX_IOCTL_QUEUE
mdefine_line|#define IPS_MAX_IOCTL_QUEUE                  8
DECL|macro|IPS_MAX_QUEUE
mdefine_line|#define IPS_MAX_QUEUE                        128
DECL|macro|IPS_BLKSIZE
mdefine_line|#define IPS_BLKSIZE                          512
DECL|macro|MAX_SG_ELEMENTS
mdefine_line|#define MAX_SG_ELEMENTS                      17
DECL|macro|MAX_LOGICAL_DRIVES
mdefine_line|#define MAX_LOGICAL_DRIVES                   8
DECL|macro|MAX_CHANNELS
mdefine_line|#define MAX_CHANNELS                         3
DECL|macro|MAX_TARGETS
mdefine_line|#define MAX_TARGETS                          15
DECL|macro|MAX_CHUNKS
mdefine_line|#define MAX_CHUNKS                           16
DECL|macro|MAX_CMDS
mdefine_line|#define MAX_CMDS                             64
DECL|macro|IPS_MAX_XFER
mdefine_line|#define IPS_MAX_XFER                         0x10000
DECL|macro|COMP_MODE_HEADS
mdefine_line|#define COMP_MODE_HEADS                      128
DECL|macro|COMP_MODE_SECTORS
mdefine_line|#define COMP_MODE_SECTORS                    32
DECL|macro|NORM_MODE_HEADS
mdefine_line|#define NORM_MODE_HEADS                      254
DECL|macro|NORM_MODE_SECTORS
mdefine_line|#define NORM_MODE_SECTORS                    63
DECL|macro|NVRAM_PAGE5_SIGNATURE
mdefine_line|#define NVRAM_PAGE5_SIGNATURE                0xFFDDBB99
DECL|macro|MAX_POST_BYTES
mdefine_line|#define MAX_POST_BYTES                       0x02
DECL|macro|MAX_CONFIG_BYTES
mdefine_line|#define MAX_CONFIG_BYTES                     0x02
DECL|macro|GOOD_POST_BASIC_STATUS
mdefine_line|#define GOOD_POST_BASIC_STATUS               0x80
DECL|macro|SEMAPHORE_TIMEOUT
mdefine_line|#define SEMAPHORE_TIMEOUT                    2000
DECL|macro|IPS_INTR_OFF
mdefine_line|#define IPS_INTR_OFF                         0
DECL|macro|IPS_INTR_ON
mdefine_line|#define IPS_INTR_ON                          1
DECL|macro|IPS_ADAPTER_ID
mdefine_line|#define IPS_ADAPTER_ID                       0xF
DECL|macro|IPS_VENDORID
mdefine_line|#define IPS_VENDORID                         0x1014
DECL|macro|IPS_DEVICEID
mdefine_line|#define IPS_DEVICEID                         0x002E
DECL|macro|TIMEOUT_10
mdefine_line|#define TIMEOUT_10                           0x10
DECL|macro|TIMEOUT_60
mdefine_line|#define TIMEOUT_60                           0x20
DECL|macro|TIMEOUT_20M
mdefine_line|#define TIMEOUT_20M                          0x30
DECL|macro|STATUS_SIZE
mdefine_line|#define STATUS_SIZE                          4
DECL|macro|STATUS_Q_SIZE
mdefine_line|#define STATUS_Q_SIZE                        (MAX_CMDS+1) * STATUS_SIZE
DECL|macro|ONE_MSEC
mdefine_line|#define ONE_MSEC                             1
DECL|macro|ONE_SEC
mdefine_line|#define ONE_SEC                              1000
multiline_comment|/*&n; * Adapter Basic Status Codes&n; */
DECL|macro|BASIC_STATUS_MASK
mdefine_line|#define BASIC_STATUS_MASK            0xFF
DECL|macro|GSC_STATUS_MASK
mdefine_line|#define GSC_STATUS_MASK              0x0F
DECL|macro|SSUCCESS
mdefine_line|#define SSUCCESS                     0x00
DECL|macro|RECOVERED_ERROR
mdefine_line|#define RECOVERED_ERROR              0x01
DECL|macro|IPS_CHECK_CONDITION
mdefine_line|#define IPS_CHECK_CONDITION          0x02
DECL|macro|INVAL_OPCO
mdefine_line|#define INVAL_OPCO                   0x03
DECL|macro|INVAL_CMD_BLK
mdefine_line|#define INVAL_CMD_BLK                0x04
DECL|macro|INVAL_PARM_BLK
mdefine_line|#define INVAL_PARM_BLK               0x05
DECL|macro|IPS_BUSY
mdefine_line|#define IPS_BUSY                     0x08
DECL|macro|ADAPT_HARDWARE_ERROR
mdefine_line|#define ADAPT_HARDWARE_ERROR         0x09
DECL|macro|ADAPT_FIRMWARE_ERROR
mdefine_line|#define ADAPT_FIRMWARE_ERROR         0x0A
DECL|macro|CMD_CMPLT_WERROR
mdefine_line|#define CMD_CMPLT_WERROR             0x0C
DECL|macro|LOG_DRV_ERROR
mdefine_line|#define LOG_DRV_ERROR                0x0D
DECL|macro|CMD_TIMEOUT
mdefine_line|#define CMD_TIMEOUT                  0x0E
DECL|macro|PHYS_DRV_ERROR
mdefine_line|#define PHYS_DRV_ERROR               0x0F
multiline_comment|/*&n; * Adapter Extended Status Equates&n; */
DECL|macro|SELECTION_TIMEOUT
mdefine_line|#define SELECTION_TIMEOUT                    0xF0
DECL|macro|DATA_OVER_UNDER_RUN
mdefine_line|#define DATA_OVER_UNDER_RUN                  0xF2
DECL|macro|EXT_HOST_RESET
mdefine_line|#define EXT_HOST_RESET                       0xF7
DECL|macro|EXT_DEVICE_RESET
mdefine_line|#define EXT_DEVICE_RESET                     0xF8
DECL|macro|EXT_RECOVERY
mdefine_line|#define EXT_RECOVERY                         0xFC
DECL|macro|EXT_CHECK_CONDITION
mdefine_line|#define EXT_CHECK_CONDITION                  0xFF
multiline_comment|/*&n; * Operating System Defines&n; */
DECL|macro|OS_WINDOWS_NT
mdefine_line|#define OS_WINDOWS_NT                        0x01
DECL|macro|OS_NETWARE
mdefine_line|#define OS_NETWARE                           0x02
DECL|macro|OS_OPENSERVER
mdefine_line|#define OS_OPENSERVER                        0x03
DECL|macro|OS_UNIXWARE
mdefine_line|#define OS_UNIXWARE                          0x04
DECL|macro|OS_SOLARIS
mdefine_line|#define OS_SOLARIS                           0x05
DECL|macro|OS_OS2
mdefine_line|#define OS_OS2                               0x06
DECL|macro|OS_LINUX
mdefine_line|#define OS_LINUX                             0x07
DECL|macro|OS_FREEBSD
mdefine_line|#define OS_FREEBSD                           0x08
multiline_comment|/*&n; * Adapter Command/Status Packet Definitions&n; */
DECL|macro|IPS_SUCCESS
mdefine_line|#define IPS_SUCCESS                  0x01 /* Successfully completed       */
DECL|macro|IPS_SUCCESS_IMM
mdefine_line|#define IPS_SUCCESS_IMM              0x02 /* Success - Immediately        */
DECL|macro|IPS_FAILURE
mdefine_line|#define IPS_FAILURE                  0x04 /* Completed with Error         */
multiline_comment|/*&n; * Logical Drive Equates&n; */
DECL|macro|OFF_LINE
mdefine_line|#define OFF_LINE             0x02
DECL|macro|OKAY
mdefine_line|#define OKAY                 0x03
DECL|macro|FREE
mdefine_line|#define FREE                 0x00
DECL|macro|SYS
mdefine_line|#define SYS                  0x06
DECL|macro|CRS
mdefine_line|#define CRS                  0x24
multiline_comment|/*&n; * DCDB Table Equates&n; */
DECL|macro|NO_DISCONNECT
mdefine_line|#define NO_DISCONNECT                0x00
DECL|macro|DISCONNECT_ALLOWED
mdefine_line|#define DISCONNECT_ALLOWED           0x80
DECL|macro|NO_AUTO_REQUEST_SENSE
mdefine_line|#define NO_AUTO_REQUEST_SENSE        0x40
DECL|macro|DATA_IN
mdefine_line|#define DATA_IN                      0x01
DECL|macro|DATA_OUT
mdefine_line|#define DATA_OUT                     0x02
DECL|macro|TRANSFER_64K
mdefine_line|#define TRANSFER_64K                 0x08
DECL|macro|NOTIMEOUT
mdefine_line|#define NOTIMEOUT                    0x00
DECL|macro|TIMEOUT10
mdefine_line|#define TIMEOUT10                    0x10
DECL|macro|TIMEOUT60
mdefine_line|#define TIMEOUT60                    0x20
DECL|macro|TIMEOUT20M
mdefine_line|#define TIMEOUT20M                   0x30
multiline_comment|/*&n; * Host adapter Flags (bit numbers)&n; */
DECL|macro|IPS_IN_INTR
mdefine_line|#define IPS_IN_INTR                  0
DECL|macro|IPS_IN_ABORT
mdefine_line|#define IPS_IN_ABORT                 1
DECL|macro|IPS_IN_RESET
mdefine_line|#define IPS_IN_RESET                 2
multiline_comment|/*&n; * SCB Flags&n; */
DECL|macro|SCB_ACTIVE
mdefine_line|#define SCB_ACTIVE                   0x00001
DECL|macro|SCB_WAITING
mdefine_line|#define SCB_WAITING                  0x00002
multiline_comment|/*&n; * Passthru stuff&n; */
DECL|macro|COPPUSRCMD
mdefine_line|#define COPPUSRCMD                  ((&squot;C&squot;&lt;&lt;8) | 65)
DECL|macro|IPS_NUMCTRLS
mdefine_line|#define IPS_NUMCTRLS                ((&squot;C&squot;&lt;&lt;8) | 68)
DECL|macro|IPS_CTRLINFO
mdefine_line|#define IPS_CTRLINFO                ((&squot;C&squot;&lt;&lt;8) | 69)
multiline_comment|/*&n; * Scsi_Host Template&n; */
DECL|macro|IPS
mdefine_line|#define IPS {                            &bslash;&n;    next : NULL,                          &bslash;&n;    module : NULL,                        &bslash;&n;    proc_dir : NULL,                      &bslash;&n;    proc_info : NULL,                     &bslash;&n;    name : NULL,                          &bslash;&n;    detect : ips_detect,                  &bslash;&n;    release : ips_release,                &bslash;&n;    info : ips_info,                      &bslash;&n;    command : NULL,                       &bslash;&n;    queuecommand : ips_queue,             &bslash;&n;    eh_strategy_handler : NULL,           &bslash;&n;    eh_abort_handler : ips_eh_abort,      &bslash;&n;    eh_device_reset_handler : NULL,       &bslash;&n;    eh_bus_reset_handler : NULL,          &bslash;&n;    eh_host_reset_handler : ips_eh_reset, &bslash;&n;    abort : ips_abort,                    &bslash;&n;    reset : ips_reset,                    &bslash;&n;    slave_attach : NULL,                  &bslash;&n;    bios_param : ips_biosparam,           &bslash;&n;    can_queue : 0,                        &bslash;&n;    this_id: -1,                          &bslash;&n;    sg_tablesize : MAX_SG_ELEMENTS,       &bslash;&n;    cmd_per_lun: 16,                      &bslash;&n;    present : 0,                          &bslash;&n;    unchecked_isa_dma : 0,                &bslash;&n;    use_clustering : ENABLE_CLUSTERING,   &bslash;&n;    use_new_eh_code : 1                   &bslash;&n; }
multiline_comment|/*&n; * IBM PCI Raid Command Formats&n; */
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|log_drv
id|u8
id|log_drv
suffix:semicolon
DECL|member|sg_count
id|u8
id|sg_count
suffix:semicolon
DECL|member|lba
id|u32
id|lba
suffix:semicolon
DECL|member|sg_addr
id|u32
id|sg_addr
suffix:semicolon
DECL|member|sector_count
id|u16
id|sector_count
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
DECL|member|ccsar
id|u32
id|ccsar
suffix:semicolon
DECL|member|cccr
id|u32
id|cccr
suffix:semicolon
DECL|typedef|BASIC_IO_CMD
DECL|typedef|PBASIC_IO_CMD
)brace
id|BASIC_IO_CMD
comma
op_star
id|PBASIC_IO_CMD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|buffer_addr
id|u32
id|buffer_addr
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|ccsar
id|u32
id|ccsar
suffix:semicolon
DECL|member|cccr
id|u32
id|cccr
suffix:semicolon
DECL|typedef|LOGICAL_INFO
DECL|typedef|PLOGICAL_INFO
)brace
id|LOGICAL_INFO
comma
op_star
id|PLOGICAL_INFO
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|reserved2
id|u8
id|reserved2
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|buffer_addr
id|u32
id|buffer_addr
suffix:semicolon
DECL|member|reserved4
id|u32
id|reserved4
suffix:semicolon
DECL|typedef|IOCTL_INFO
DECL|typedef|PIOCTL_INFO
)brace
id|IOCTL_INFO
comma
op_star
id|PIOCTL_INFO
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|dcdb_address
id|u32
id|dcdb_address
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|ccsar
id|u32
id|ccsar
suffix:semicolon
DECL|member|cccr
id|u32
id|cccr
suffix:semicolon
DECL|typedef|DCDB_CMD
DECL|typedef|PDCDB_CMD
)brace
id|DCDB_CMD
comma
op_star
id|PDCDB_CMD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|channel
id|u8
id|channel
suffix:semicolon
DECL|member|source_target
id|u8
id|source_target
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|ccsar
id|u32
id|ccsar
suffix:semicolon
DECL|member|cccr
id|u32
id|cccr
suffix:semicolon
DECL|typedef|CONFIG_SYNC_CMD
DECL|typedef|PCONFIG_SYNC_CMD
)brace
id|CONFIG_SYNC_CMD
comma
op_star
id|PCONFIG_SYNC_CMD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|log_drv
id|u8
id|log_drv
suffix:semicolon
DECL|member|control
id|u8
id|control
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|ccsar
id|u32
id|ccsar
suffix:semicolon
DECL|member|cccr
id|u32
id|cccr
suffix:semicolon
DECL|typedef|UNLOCK_STRIPE_CMD
DECL|typedef|PUNLOCK_STRIPE_CMD
)brace
id|UNLOCK_STRIPE_CMD
comma
op_star
id|PUNLOCK_STRIPE_CMD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|state
id|u8
id|state
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|reserved4
id|u32
id|reserved4
suffix:semicolon
DECL|member|ccsar
id|u32
id|ccsar
suffix:semicolon
DECL|member|cccr
id|u32
id|cccr
suffix:semicolon
DECL|typedef|FLUSH_CACHE_CMD
DECL|typedef|PFLUSH_CACHE_CMD
)brace
id|FLUSH_CACHE_CMD
comma
op_star
id|PFLUSH_CACHE_CMD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|desc
id|u8
id|desc
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|buffer_addr
id|u32
id|buffer_addr
suffix:semicolon
DECL|member|reserved3
id|u32
id|reserved3
suffix:semicolon
DECL|member|ccsar
id|u32
id|ccsar
suffix:semicolon
DECL|member|cccr
id|u32
id|cccr
suffix:semicolon
DECL|typedef|STATUS_CMD
DECL|typedef|PSTATUS_CMD
)brace
id|STATUS_CMD
comma
op_star
id|PSTATUS_CMD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|op_code
id|u8
id|op_code
suffix:semicolon
DECL|member|command_id
id|u8
id|command_id
suffix:semicolon
DECL|member|page
id|u8
id|page
suffix:semicolon
DECL|member|write
id|u8
id|write
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:semicolon
DECL|member|buffer_addr
id|u32
id|buffer_addr
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|ccsar
id|u32
id|ccsar
suffix:semicolon
DECL|member|cccr
id|u32
id|cccr
suffix:semicolon
DECL|typedef|NVRAM_CMD
DECL|typedef|PNVRAM_CMD
)brace
id|NVRAM_CMD
comma
op_star
id|PNVRAM_CMD
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|basic_io
id|BASIC_IO_CMD
id|basic_io
suffix:semicolon
DECL|member|logical_info
id|LOGICAL_INFO
id|logical_info
suffix:semicolon
DECL|member|ioctl_info
id|IOCTL_INFO
id|ioctl_info
suffix:semicolon
DECL|member|dcdb
id|DCDB_CMD
id|dcdb
suffix:semicolon
DECL|member|config_sync
id|CONFIG_SYNC_CMD
id|config_sync
suffix:semicolon
DECL|member|unlock_stripe
id|UNLOCK_STRIPE_CMD
id|unlock_stripe
suffix:semicolon
DECL|member|flush_cache
id|FLUSH_CACHE_CMD
id|flush_cache
suffix:semicolon
DECL|member|status
id|STATUS_CMD
id|status
suffix:semicolon
DECL|member|nvram
id|NVRAM_CMD
id|nvram
suffix:semicolon
DECL|typedef|HOST_COMMAND
DECL|typedef|PHOST_COMMAND
)brace
id|HOST_COMMAND
comma
op_star
id|PHOST_COMMAND
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|logical_id
id|u8
id|logical_id
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|raid_level
id|u8
id|raid_level
suffix:semicolon
DECL|member|state
id|u8
id|state
suffix:semicolon
DECL|member|sector_count
id|u32
id|sector_count
suffix:semicolon
DECL|typedef|DRIVE_INFO
DECL|typedef|PDRIVE_INFO
)brace
id|DRIVE_INFO
comma
op_star
id|PDRIVE_INFO
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|no_of_log_drive
id|u8
id|no_of_log_drive
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|drive_info
id|DRIVE_INFO
id|drive_info
(braket
id|MAX_LOGICAL_DRIVES
)braket
suffix:semicolon
DECL|typedef|LOGICAL_DRIVE_INFO
DECL|typedef|PLOGICAL_DRIVE_INFO
)brace
id|LOGICAL_DRIVE_INFO
comma
op_star
id|PLOGICAL_DRIVE_INFO
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ha_num
id|u8
id|ha_num
suffix:semicolon
DECL|member|bus_num
id|u8
id|bus_num
suffix:semicolon
DECL|member|id
id|u8
id|id
suffix:semicolon
DECL|member|device_type
id|u8
id|device_type
suffix:semicolon
DECL|member|data_len
id|u32
id|data_len
suffix:semicolon
DECL|member|data_ptr
id|u32
id|data_ptr
suffix:semicolon
DECL|member|scsi_cdb
id|u8
id|scsi_cdb
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|data_counter
id|u32
id|data_counter
suffix:semicolon
DECL|member|block_size
id|u32
id|block_size
suffix:semicolon
DECL|typedef|NON_DISK_DEVICE_INFO
DECL|typedef|PNON_DISK_DEVICE_INFO
)brace
id|NON_DISK_DEVICE_INFO
comma
op_star
id|PNON_DISK_DEVICE_INFO
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|device_address
id|u8
id|device_address
suffix:semicolon
DECL|member|cmd_attribute
id|u8
id|cmd_attribute
suffix:semicolon
DECL|member|transfer_length
id|u16
id|transfer_length
suffix:semicolon
DECL|member|buffer_pointer
id|u32
id|buffer_pointer
suffix:semicolon
DECL|member|cdb_length
id|u8
id|cdb_length
suffix:semicolon
DECL|member|sense_length
id|u8
id|sense_length
suffix:semicolon
DECL|member|sg_count
id|u8
id|sg_count
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|scsi_cdb
id|u8
id|scsi_cdb
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|sense_info
id|u8
id|sense_info
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|scsi_status
id|u8
id|scsi_status
suffix:semicolon
DECL|member|reserved2
id|u8
id|reserved2
(braket
l_int|3
)braket
suffix:semicolon
DECL|typedef|DCDB_TABLE
DECL|typedef|PDCDB_TABLE
)brace
id|DCDB_TABLE
comma
op_star
id|PDCDB_TABLE
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|reserved
r_volatile
id|u8
id|reserved
suffix:semicolon
DECL|member|command_id
r_volatile
id|u8
id|command_id
suffix:semicolon
DECL|member|basic_status
r_volatile
id|u8
id|basic_status
suffix:semicolon
DECL|member|extended_status
r_volatile
id|u8
id|extended_status
suffix:semicolon
DECL|typedef|STATUS
DECL|typedef|PSTATUS
)brace
id|STATUS
comma
op_star
id|PSTATUS
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|status
id|STATUS
id|status
(braket
id|MAX_CMDS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|p_status_start
r_volatile
id|PSTATUS
id|p_status_start
suffix:semicolon
DECL|member|p_status_end
r_volatile
id|PSTATUS
id|p_status_end
suffix:semicolon
DECL|member|p_status_tail
r_volatile
id|PSTATUS
id|p_status_tail
suffix:semicolon
DECL|member|hw_status_start
r_volatile
id|u32
id|hw_status_start
suffix:semicolon
DECL|member|hw_status_tail
r_volatile
id|u32
id|hw_status_tail
suffix:semicolon
DECL|member|logical_drive_info
id|LOGICAL_DRIVE_INFO
id|logical_drive_info
suffix:semicolon
DECL|typedef|ADAPTER_AREA
DECL|typedef|PADAPTER_AREA
)brace
id|ADAPTER_AREA
comma
op_star
id|PADAPTER_AREA
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ucLogDriveCount
id|u8
id|ucLogDriveCount
suffix:semicolon
DECL|member|ucMiscFlag
id|u8
id|ucMiscFlag
suffix:semicolon
DECL|member|ucSLTFlag
id|u8
id|ucSLTFlag
suffix:semicolon
DECL|member|ucBSTFlag
id|u8
id|ucBSTFlag
suffix:semicolon
DECL|member|ucPwrChgCnt
id|u8
id|ucPwrChgCnt
suffix:semicolon
DECL|member|ucWrongAdrCnt
id|u8
id|ucWrongAdrCnt
suffix:semicolon
DECL|member|ucUnidentCnt
id|u8
id|ucUnidentCnt
suffix:semicolon
DECL|member|ucNVramDevChgCnt
id|u8
id|ucNVramDevChgCnt
suffix:semicolon
DECL|member|CodeBlkVersion
id|u8
id|CodeBlkVersion
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|BootBlkVersion
id|u8
id|BootBlkVersion
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ulDriveSize
id|u32
id|ulDriveSize
(braket
id|MAX_LOGICAL_DRIVES
)braket
suffix:semicolon
DECL|member|ucConcurrentCmdCount
id|u8
id|ucConcurrentCmdCount
suffix:semicolon
DECL|member|ucMaxPhysicalDevices
id|u8
id|ucMaxPhysicalDevices
suffix:semicolon
DECL|member|usFlashRepgmCount
id|u16
id|usFlashRepgmCount
suffix:semicolon
DECL|member|ucDefunctDiskCount
id|u8
id|ucDefunctDiskCount
suffix:semicolon
DECL|member|ucRebuildFlag
id|u8
id|ucRebuildFlag
suffix:semicolon
DECL|member|ucOfflineLogDrvCount
id|u8
id|ucOfflineLogDrvCount
suffix:semicolon
DECL|member|ucCriticalDrvCount
id|u8
id|ucCriticalDrvCount
suffix:semicolon
DECL|member|usConfigUpdateCount
id|u16
id|usConfigUpdateCount
suffix:semicolon
DECL|member|ucBlkFlag
id|u8
id|ucBlkFlag
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|usAddrDeadDisk
id|u16
id|usAddrDeadDisk
(braket
id|MAX_CHANNELS
op_star
id|MAX_TARGETS
)braket
suffix:semicolon
DECL|typedef|ENQCMD
DECL|typedef|PENQCMD
)brace
id|ENQCMD
comma
op_star
id|PENQCMD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ucInitiator
id|u8
id|ucInitiator
suffix:semicolon
DECL|member|ucParameters
id|u8
id|ucParameters
suffix:semicolon
DECL|member|ucMiscFlag
id|u8
id|ucMiscFlag
suffix:semicolon
DECL|member|ucState
id|u8
id|ucState
suffix:semicolon
DECL|member|ulBlockCount
id|u32
id|ulBlockCount
suffix:semicolon
DECL|member|ucDeviceId
id|u8
id|ucDeviceId
(braket
l_int|28
)braket
suffix:semicolon
DECL|typedef|DEVSTATE
DECL|typedef|PDEVSTATE
)brace
id|DEVSTATE
comma
op_star
id|PDEVSTATE
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ucChn
id|u8
id|ucChn
suffix:semicolon
DECL|member|ucTgt
id|u8
id|ucTgt
suffix:semicolon
DECL|member|ucReserved
id|u16
id|ucReserved
suffix:semicolon
DECL|member|ulStartSect
id|u32
id|ulStartSect
suffix:semicolon
DECL|member|ulNoOfSects
id|u32
id|ulNoOfSects
suffix:semicolon
DECL|typedef|CHUNK
DECL|typedef|PCHUNK
)brace
id|CHUNK
comma
op_star
id|PCHUNK
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ucUserField
id|u16
id|ucUserField
suffix:semicolon
DECL|member|ucState
id|u8
id|ucState
suffix:semicolon
DECL|member|ucRaidCacheParam
id|u8
id|ucRaidCacheParam
suffix:semicolon
DECL|member|ucNoOfChunkUnits
id|u8
id|ucNoOfChunkUnits
suffix:semicolon
DECL|member|ucStripeSize
id|u8
id|ucStripeSize
suffix:semicolon
DECL|member|ucParams
id|u8
id|ucParams
suffix:semicolon
DECL|member|ucReserved
id|u8
id|ucReserved
suffix:semicolon
DECL|member|ulLogDrvSize
id|u32
id|ulLogDrvSize
suffix:semicolon
DECL|member|chunk
id|CHUNK
id|chunk
(braket
id|MAX_CHUNKS
)braket
suffix:semicolon
DECL|typedef|LOGICAL_DRIVE
DECL|typedef|PLOGICAL_DRIVE
)brace
id|LOGICAL_DRIVE
comma
op_star
id|PLOGICAL_DRIVE
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|board_disc
id|u8
id|board_disc
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|processor
id|u8
id|processor
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ucNoChanType
id|u8
id|ucNoChanType
suffix:semicolon
DECL|member|ucNoHostIntType
id|u8
id|ucNoHostIntType
suffix:semicolon
DECL|member|ucCompression
id|u8
id|ucCompression
suffix:semicolon
DECL|member|ucNvramType
id|u8
id|ucNvramType
suffix:semicolon
DECL|member|ulNvramSize
id|u32
id|ulNvramSize
suffix:semicolon
DECL|typedef|HARDWARE_DISC
DECL|typedef|PHARDWARE_DISC
)brace
id|HARDWARE_DISC
comma
op_star
id|PHARDWARE_DISC
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ucLogDriveCount
id|u8
id|ucLogDriveCount
suffix:semicolon
DECL|member|ucDateD
id|u8
id|ucDateD
suffix:semicolon
DECL|member|ucDateM
id|u8
id|ucDateM
suffix:semicolon
DECL|member|ucDateY
id|u8
id|ucDateY
suffix:semicolon
DECL|member|init_id
id|u8
id|init_id
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|host_id
id|u8
id|host_id
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|time_sign
id|u8
id|time_sign
(braket
l_int|8
)braket
suffix:semicolon
r_struct
(brace
DECL|member|usCfgDrvUpdateCnt
id|u32
id|usCfgDrvUpdateCnt
suffix:colon
l_int|16
suffix:semicolon
DECL|member|ConcurDrvStartCnt
id|u32
id|ConcurDrvStartCnt
suffix:colon
l_int|4
suffix:semicolon
DECL|member|StartupDelay
id|u32
id|StartupDelay
suffix:colon
l_int|4
suffix:semicolon
DECL|member|auto_rearrange
id|u32
id|auto_rearrange
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cd_boot
id|u32
id|cd_boot
suffix:colon
l_int|1
suffix:semicolon
DECL|member|cluster
id|u32
id|cluster
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:colon
l_int|5
suffix:semicolon
DECL|member|UserOpt
)brace
id|UserOpt
suffix:semicolon
DECL|member|user_field
id|u16
id|user_field
suffix:semicolon
DECL|member|ucRebuildRate
id|u8
id|ucRebuildRate
suffix:semicolon
DECL|member|ucReserve
id|u8
id|ucReserve
suffix:semicolon
DECL|member|hardware_disc
id|HARDWARE_DISC
id|hardware_disc
suffix:semicolon
DECL|member|logical_drive
id|LOGICAL_DRIVE
id|logical_drive
(braket
id|MAX_LOGICAL_DRIVES
)braket
suffix:semicolon
DECL|member|dev
id|DEVSTATE
id|dev
(braket
id|MAX_CHANNELS
)braket
(braket
id|MAX_TARGETS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|512
)braket
suffix:semicolon
DECL|typedef|CONFCMD
DECL|typedef|PCONFCMD
)brace
id|CONFCMD
comma
op_star
id|PCONFCMD
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|signature
id|u32
id|signature
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
DECL|member|adapter_slot
id|u8
id|adapter_slot
suffix:semicolon
DECL|member|adapter_type
id|u16
id|adapter_type
suffix:semicolon
DECL|member|bios_high
id|u8
id|bios_high
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|bios_low
id|u8
id|bios_low
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|reserved2
id|u16
id|reserved2
suffix:semicolon
DECL|member|reserved3
id|u8
id|reserved3
suffix:semicolon
DECL|member|operating_system
id|u8
id|operating_system
suffix:semicolon
DECL|member|driver_high
id|u8
id|driver_high
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|driver_low
id|u8
id|driver_low
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|reserved4
id|u8
id|reserved4
(braket
l_int|100
)braket
suffix:semicolon
DECL|typedef|NVRAM_PAGE5
DECL|typedef|PNVRAM_PAGE5
)brace
id|NVRAM_PAGE5
comma
op_star
id|PNVRAM_PAGE5
suffix:semicolon
DECL|struct|_SUBSYS_PARAM
r_typedef
r_struct
id|_SUBSYS_PARAM
(brace
DECL|member|param
id|u32
id|param
(braket
l_int|128
)braket
suffix:semicolon
DECL|typedef|SUBSYS_PARAM
DECL|typedef|PSUBSYS_PARAM
)brace
id|SUBSYS_PARAM
comma
op_star
id|PSUBSYS_PARAM
suffix:semicolon
multiline_comment|/*&n; * Inquiry Data Format&n; */
r_typedef
r_struct
(brace
DECL|member|DeviceType
id|u8
id|DeviceType
suffix:colon
l_int|5
suffix:semicolon
DECL|member|DeviceTypeQualifier
id|u8
id|DeviceTypeQualifier
suffix:colon
l_int|3
suffix:semicolon
DECL|member|DeviceTypeModifier
id|u8
id|DeviceTypeModifier
suffix:colon
l_int|7
suffix:semicolon
DECL|member|RemoveableMedia
id|u8
id|RemoveableMedia
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Versions
id|u8
id|Versions
suffix:semicolon
DECL|member|ResponseDataFormat
id|u8
id|ResponseDataFormat
suffix:semicolon
DECL|member|AdditionalLength
id|u8
id|AdditionalLength
suffix:semicolon
DECL|member|Reserved
id|u16
id|Reserved
suffix:semicolon
DECL|member|SoftReset
id|u8
id|SoftReset
suffix:colon
l_int|1
suffix:semicolon
DECL|member|CommandQueue
id|u8
id|CommandQueue
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Reserved2
id|u8
id|Reserved2
suffix:colon
l_int|1
suffix:semicolon
DECL|member|LinkedCommands
id|u8
id|LinkedCommands
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Synchronous
id|u8
id|Synchronous
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Wide16Bit
id|u8
id|Wide16Bit
suffix:colon
l_int|1
suffix:semicolon
DECL|member|Wide32Bit
id|u8
id|Wide32Bit
suffix:colon
l_int|1
suffix:semicolon
DECL|member|RelativeAddressing
id|u8
id|RelativeAddressing
suffix:colon
l_int|1
suffix:semicolon
DECL|member|VendorId
id|u8
id|VendorId
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ProductId
id|u8
id|ProductId
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|ProductRevisionLevel
id|u8
id|ProductRevisionLevel
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|VendorSpecific
id|u8
id|VendorSpecific
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|Reserved3
id|u8
id|Reserved3
(braket
l_int|40
)braket
suffix:semicolon
DECL|typedef|IPS_INQUIRYDATA
DECL|typedef|IPS_PINQUIRYDATA
)brace
id|IPS_INQUIRYDATA
comma
op_star
id|IPS_PINQUIRYDATA
suffix:semicolon
multiline_comment|/*&n; * Read Capacity Data Format&n; */
r_typedef
r_struct
(brace
DECL|member|lba
id|u32
id|lba
suffix:semicolon
DECL|member|len
id|u32
id|len
suffix:semicolon
DECL|typedef|CAPACITY_T
)brace
id|CAPACITY_T
suffix:semicolon
multiline_comment|/*&n; * Sense Data Format&n; */
r_typedef
r_struct
(brace
DECL|member|pg_pc
id|u8
id|pg_pc
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Page Code                    */
DECL|member|pg_res1
id|u8
id|pg_res1
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Reserved                     */
DECL|member|pg_len
id|u8
id|pg_len
suffix:semicolon
multiline_comment|/* Page Length                  */
DECL|member|pg_trk_z
id|u16
id|pg_trk_z
suffix:semicolon
multiline_comment|/* Tracks per zone              */
DECL|member|pg_asec_z
id|u16
id|pg_asec_z
suffix:semicolon
multiline_comment|/* Alternate sectors per zone   */
DECL|member|pg_atrk_z
id|u16
id|pg_atrk_z
suffix:semicolon
multiline_comment|/* Alternate tracks per zone    */
DECL|member|pg_atrk_v
id|u16
id|pg_atrk_v
suffix:semicolon
multiline_comment|/* Alternate tracks per volume  */
DECL|member|pg_sec_t
id|u16
id|pg_sec_t
suffix:semicolon
multiline_comment|/* Sectors per track            */
DECL|member|pg_bytes_s
id|u16
id|pg_bytes_s
suffix:semicolon
multiline_comment|/* Bytes per physical sectors   */
DECL|member|pg_intl
id|u16
id|pg_intl
suffix:semicolon
multiline_comment|/* Interleave                   */
DECL|member|pg_trkskew
id|u16
id|pg_trkskew
suffix:semicolon
multiline_comment|/* Track skew factor            */
DECL|member|pg_cylskew
id|u16
id|pg_cylskew
suffix:semicolon
multiline_comment|/* Cylinder Skew Factor         */
DECL|member|pg_res2
id|u32
id|pg_res2
suffix:colon
l_int|27
suffix:semicolon
multiline_comment|/* Reserved                     */
DECL|member|pg_ins
id|u32
id|pg_ins
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Inhibit Slave                */
DECL|member|pg_surf
id|u32
id|pg_surf
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Allocate Surface Sectors     */
DECL|member|pg_rmb
id|u32
id|pg_rmb
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Removeable                   */
DECL|member|pg_hsec
id|u32
id|pg_hsec
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Hard sector formatting       */
DECL|member|pg_ssec
id|u32
id|pg_ssec
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Soft sector formatting       */
DECL|typedef|DADF_T
)brace
id|DADF_T
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|pg_pc
id|u8
id|pg_pc
suffix:colon
l_int|6
suffix:semicolon
multiline_comment|/* Page Code                     */
DECL|member|pg_res1
id|u8
id|pg_res1
suffix:colon
l_int|2
suffix:semicolon
multiline_comment|/* Reserved                      */
DECL|member|pg_len
id|u8
id|pg_len
suffix:semicolon
multiline_comment|/* Page Length                   */
DECL|member|pg_cylu
id|u16
id|pg_cylu
suffix:semicolon
multiline_comment|/* Number of cylinders (upper)   */
DECL|member|pg_cyll
id|u8
id|pg_cyll
suffix:semicolon
multiline_comment|/* Number of cylinders (lower)   */
DECL|member|pg_head
id|u8
id|pg_head
suffix:semicolon
multiline_comment|/* Number of heads               */
DECL|member|pg_wrpcompu
id|u16
id|pg_wrpcompu
suffix:semicolon
multiline_comment|/* Write precomp (upper)         */
DECL|member|pg_wrpcompl
id|u32
id|pg_wrpcompl
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Write precomp (lower)         */
DECL|member|pg_redwrcur
id|u32
id|pg_redwrcur
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* Reduced write current         */
DECL|member|pg_drstep
id|u32
id|pg_drstep
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* Drive step rate               */
DECL|member|pg_landu
id|u32
id|pg_landu
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* Landing zone cylinder (upper) */
DECL|member|pg_landl
id|u32
id|pg_landl
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* Landing zone cylinder (lower) */
DECL|member|pg_res2
id|u32
id|pg_res2
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* Reserved                      */
DECL|typedef|RDDG_T
)brace
id|RDDG_T
suffix:semicolon
DECL|struct|blk_desc
r_struct
id|blk_desc
(brace
DECL|member|bd_dencode
id|u8
id|bd_dencode
suffix:semicolon
DECL|member|bd_nblks1
id|u8
id|bd_nblks1
suffix:semicolon
DECL|member|bd_nblks2
id|u8
id|bd_nblks2
suffix:semicolon
DECL|member|bd_nblks3
id|u8
id|bd_nblks3
suffix:semicolon
DECL|member|bd_res
id|u8
id|bd_res
suffix:semicolon
DECL|member|bd_blen1
id|u8
id|bd_blen1
suffix:semicolon
DECL|member|bd_blen2
id|u8
id|bd_blen2
suffix:semicolon
DECL|member|bd_blen3
id|u8
id|bd_blen3
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|plh_len
id|u8
id|plh_len
suffix:semicolon
multiline_comment|/* Data length             */
DECL|member|plh_type
id|u8
id|plh_type
suffix:semicolon
multiline_comment|/* Medium type             */
DECL|member|plh_res
id|u8
id|plh_res
suffix:colon
l_int|7
suffix:semicolon
multiline_comment|/* Reserved                */
DECL|member|plh_wp
id|u8
id|plh_wp
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Write protect           */
DECL|member|plh_bdl
id|u8
id|plh_bdl
suffix:semicolon
multiline_comment|/* Block descriptor length */
DECL|typedef|SENSE_PLH_T
)brace
id|SENSE_PLH_T
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|plh
id|SENSE_PLH_T
id|plh
suffix:semicolon
DECL|member|blk_desc
r_struct
id|blk_desc
id|blk_desc
suffix:semicolon
r_union
(brace
DECL|member|pg3
id|DADF_T
id|pg3
suffix:semicolon
DECL|member|pg4
id|RDDG_T
id|pg4
suffix:semicolon
DECL|member|pdata
)brace
id|pdata
suffix:semicolon
DECL|typedef|ips_mdata_t
)brace
id|ips_mdata_t
suffix:semicolon
multiline_comment|/*&n; * Scatter Gather list format&n; */
DECL|struct|ips_sglist
r_typedef
r_struct
id|ips_sglist
(brace
DECL|member|address
id|u32
id|address
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|typedef|SG_LIST
DECL|typedef|PSG_LIST
)brace
id|SG_LIST
comma
op_star
id|PSG_LIST
suffix:semicolon
DECL|struct|_INFOSTR
r_typedef
r_struct
id|_INFOSTR
(brace
DECL|member|buffer
r_char
op_star
id|buffer
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|offset
r_int
id|offset
suffix:semicolon
DECL|member|pos
r_int
id|pos
suffix:semicolon
DECL|typedef|INFOSTR
)brace
id|INFOSTR
suffix:semicolon
multiline_comment|/*&n; * Status Info&n; */
DECL|struct|ips_stat
r_typedef
r_struct
id|ips_stat
(brace
DECL|member|residue_len
id|u32
id|residue_len
suffix:semicolon
DECL|member|scb_addr
id|u32
id|scb_addr
suffix:semicolon
DECL|typedef|ips_stat_t
)brace
id|ips_stat_t
suffix:semicolon
multiline_comment|/*&n; * SCB Queue Format&n; */
DECL|struct|ips_scb_queue
r_typedef
r_struct
id|ips_scb_queue
(brace
DECL|member|head
r_struct
id|ips_scb
op_star
id|head
suffix:semicolon
DECL|member|tail
r_struct
id|ips_scb
op_star
id|tail
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|typedef|ips_scb_queue_t
)brace
id|ips_scb_queue_t
suffix:semicolon
multiline_comment|/*&n; * Wait queue_format&n; */
DECL|struct|ips_wait_queue
r_typedef
r_struct
id|ips_wait_queue
(brace
DECL|member|head
id|Scsi_Cmnd
op_star
id|head
suffix:semicolon
DECL|member|tail
id|Scsi_Cmnd
op_star
id|tail
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|typedef|ips_wait_queue_t
)brace
id|ips_wait_queue_t
suffix:semicolon
DECL|struct|ips_ha
r_typedef
r_struct
id|ips_ha
(brace
DECL|member|ha_id
id|u8
id|ha_id
(braket
id|MAX_CHANNELS
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|io_addr
id|u32
id|io_addr
suffix:semicolon
multiline_comment|/* Base I/O address           */
DECL|member|irq
id|u8
id|irq
suffix:semicolon
multiline_comment|/* IRQ for adapter            */
DECL|member|ntargets
id|u8
id|ntargets
suffix:semicolon
multiline_comment|/* Number of targets          */
DECL|member|nbus
id|u8
id|nbus
suffix:semicolon
multiline_comment|/* Number of buses            */
DECL|member|nlun
id|u8
id|nlun
suffix:semicolon
multiline_comment|/* Number of Luns             */
DECL|member|ad_type
id|u16
id|ad_type
suffix:semicolon
multiline_comment|/* Adapter type               */
DECL|member|host_num
id|u16
id|host_num
suffix:semicolon
multiline_comment|/* Adapter number             */
DECL|member|max_xfer
id|u32
id|max_xfer
suffix:semicolon
multiline_comment|/* Maximum Xfer size          */
DECL|member|max_cmds
id|u32
id|max_cmds
suffix:semicolon
multiline_comment|/* Max concurrent commands    */
DECL|member|num_ioctl
id|u32
id|num_ioctl
suffix:semicolon
multiline_comment|/* Number of Ioctls           */
DECL|member|sp
id|ips_stat_t
id|sp
suffix:semicolon
multiline_comment|/* Status packer pointer      */
DECL|member|scbs
r_struct
id|ips_scb
op_star
id|scbs
suffix:semicolon
multiline_comment|/* Array of all CCBS          */
DECL|member|scb_freelist
r_struct
id|ips_scb
op_star
id|scb_freelist
suffix:semicolon
multiline_comment|/* SCB free list              */
DECL|member|scb_waitlist
id|ips_wait_queue_t
id|scb_waitlist
suffix:semicolon
multiline_comment|/* Pending SCB list           */
DECL|member|copp_waitlist
id|ips_wait_queue_t
id|copp_waitlist
suffix:semicolon
multiline_comment|/* Pending PT list            */
DECL|member|scb_activelist
id|ips_scb_queue_t
id|scb_activelist
suffix:semicolon
multiline_comment|/* Active SCB list            */
DECL|member|dummy
id|BASIC_IO_CMD
op_star
id|dummy
suffix:semicolon
multiline_comment|/* dummy command              */
DECL|member|adapt
id|ADAPTER_AREA
op_star
id|adapt
suffix:semicolon
multiline_comment|/* Adapter status area        */
DECL|member|enq
id|ENQCMD
op_star
id|enq
suffix:semicolon
multiline_comment|/* Adapter Enquiry data       */
DECL|member|conf
id|CONFCMD
op_star
id|conf
suffix:semicolon
multiline_comment|/* Adapter config data        */
DECL|member|nvram
id|NVRAM_PAGE5
op_star
id|nvram
suffix:semicolon
multiline_comment|/* NVRAM page 5 data          */
DECL|member|subsys
id|SUBSYS_PARAM
op_star
id|subsys
suffix:semicolon
multiline_comment|/* Subsystem parameters       */
DECL|member|cmd_in_progress
id|u32
id|cmd_in_progress
suffix:semicolon
multiline_comment|/* Current command in progress*/
DECL|member|flags
id|u32
id|flags
suffix:semicolon
multiline_comment|/* HA flags                   */
DECL|member|waitflag
id|u8
id|waitflag
suffix:semicolon
multiline_comment|/* are we waiting for cmd     */
DECL|member|active
id|u8
id|active
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:colon
l_int|16
suffix:semicolon
multiline_comment|/* reserved space             */
DECL|member|copp_queue
id|wait_queue_head_t
id|copp_queue
suffix:semicolon
multiline_comment|/* passthru sync queue        */
macro_line|#if LINUX_VERSION_CODE &gt;= LinuxVersionCode(2,1,0)
DECL|member|scb_lock
id|spinlock_t
id|scb_lock
suffix:semicolon
DECL|member|copp_lock
id|spinlock_t
id|copp_lock
suffix:semicolon
macro_line|#endif
DECL|typedef|ips_ha_t
)brace
id|ips_ha_t
suffix:semicolon
DECL|typedef|scb_callback
r_typedef
r_void
(paren
op_star
id|scb_callback
)paren
(paren
id|ips_ha_t
op_star
comma
r_struct
id|ips_scb
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * SCB Format&n; */
DECL|struct|ips_scb
r_typedef
r_struct
id|ips_scb
(brace
DECL|member|cmd
id|HOST_COMMAND
id|cmd
suffix:semicolon
DECL|member|dcdb
id|DCDB_TABLE
id|dcdb
suffix:semicolon
DECL|member|target_id
id|u8
id|target_id
suffix:semicolon
DECL|member|bus
id|u8
id|bus
suffix:semicolon
DECL|member|lun
id|u8
id|lun
suffix:semicolon
DECL|member|cdb
id|u8
id|cdb
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|scb_busaddr
id|u32
id|scb_busaddr
suffix:semicolon
DECL|member|data_busaddr
id|u32
id|data_busaddr
suffix:semicolon
DECL|member|timeout
id|u32
id|timeout
suffix:semicolon
DECL|member|basic_status
id|u8
id|basic_status
suffix:semicolon
DECL|member|extended_status
id|u8
id|extended_status
suffix:semicolon
DECL|member|breakup
id|u16
id|breakup
suffix:semicolon
DECL|member|data_len
id|u32
id|data_len
suffix:semicolon
DECL|member|sg_len
id|u32
id|sg_len
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|op_code
id|u32
id|op_code
suffix:semicolon
DECL|member|sg_list
id|SG_LIST
op_star
id|sg_list
suffix:semicolon
DECL|member|scsi_cmd
id|Scsi_Cmnd
op_star
id|scsi_cmd
suffix:semicolon
DECL|member|q_next
r_struct
id|ips_scb
op_star
id|q_next
suffix:semicolon
DECL|member|callback
id|scb_callback
id|callback
suffix:semicolon
DECL|typedef|ips_scb_t
)brace
id|ips_scb_t
suffix:semicolon
multiline_comment|/*&n; * Passthru Command Format&n; */
r_typedef
r_struct
(brace
DECL|member|CoppID
id|u8
id|CoppID
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|CoppCmd
id|u32
id|CoppCmd
suffix:semicolon
DECL|member|PtBuffer
id|u32
id|PtBuffer
suffix:semicolon
DECL|member|CmdBuffer
id|u8
op_star
id|CmdBuffer
suffix:semicolon
DECL|member|CmdBSize
id|u32
id|CmdBSize
suffix:semicolon
DECL|member|CoppCP
id|ips_scb_t
id|CoppCP
suffix:semicolon
DECL|member|TimeOut
id|u32
id|TimeOut
suffix:semicolon
DECL|member|BasicStatus
id|u8
id|BasicStatus
suffix:semicolon
DECL|member|ExtendedStatus
id|u8
id|ExtendedStatus
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
DECL|typedef|ips_passthru_t
)brace
id|ips_passthru_t
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we almost follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 2&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -2&n; * c-argdecl-indent: 2&n; * c-label-offset: -2&n; * c-continued-statement-offset: 2&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
