multiline_comment|/******************************************************************************&n;**  Device driver for the PCI-SCSI NCR538XX controller family.&n;**&n;**  Copyright (C) 1994  Wolfgang Stanglmeier&n;**&n;**  This program is free software; you can redistribute it and/or modify&n;**  it under the terms of the GNU General Public License as published by&n;**  the Free Software Foundation; either version 2 of the License, or&n;**  (at your option) any later version.&n;**&n;**  This program is distributed in the hope that it will be useful,&n;**  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;**  GNU General Public License for more details.&n;**&n;**  You should have received a copy of the GNU General Public License&n;**  along with this program; if not, write to the Free Software&n;**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**-----------------------------------------------------------------------------&n;**&n;**  This driver has been ported to Linux from the FreeBSD NCR53C8XX driver&n;**  and is currently maintained by&n;**&n;**          Gerard Roudier              &lt;groudier@club-internet.fr&gt;&n;**&n;**  Being given that this driver originates from the FreeBSD version, and&n;**  in order to keep synergy on both, any suggested enhancements and corrections&n;**  received on Linux are automatically a potential candidate for the FreeBSD &n;**  version.&n;**&n;**  The original driver has been written for 386bsd and FreeBSD by&n;**          Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n;**          Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n;**&n;**  And has been ported to NetBSD by&n;**          Charles M. Hannum           &lt;mycroft@gnu.ai.mit.edu&gt;&n;**&n;*******************************************************************************&n;*/
macro_line|#ifndef NCR53C8XX_H
DECL|macro|NCR53C8XX_H
mdefine_line|#define NCR53C8XX_H
multiline_comment|/*&n;**&t;Name and revision of the driver&n;*/
DECL|macro|SCSI_NCR_DRIVER_NAME
mdefine_line|#define SCSI_NCR_DRIVER_NAME&t;&t;&quot;ncr53c8xx - revision 1.14c&quot;
multiline_comment|/*&n;**&t;If SCSI_NCR_SPECIAL_FEATURES is defined,&n;**&t;the driver enables or not the following features according to chip id &n;**&t;revision id:&n;**&t;DMODE   0xce&n;**&t;&t;0x02&t;burst op-code fetch&n;**&t;&t;0x04&t;enable read multiple&n;**&t;&t;0x08&t;enable read line&n;**&t;&t;0xc0&t;burst length 16/8/2&n;**&t;DCNTL   0xa0&n;**&t;&t;0x20&t;enable pre-fetch&n;**&t;&t;0x80&t;enable cache line size&n;**&t;CTEST3  0x01&n;**&t;&t;0x01&t;set write and invalidate&n;**&t;CTEST4  0x80&n;**&t;&t;0x80&t;burst disabled&n;**&n;**&t;If SCSI_NCR_TRUST_BIOS_SETTING is defined, the driver will use the &n;**&t;initial value of corresponding bit fields, assuming they have been &n;**&t;set by the SDMS BIOS.&n;**&t;When Linux is booted from another O/S, these assertion is false and &n;**&t;the driver will not be able to guess it. &n;*/
macro_line|#if 0
mdefine_line|#define SCSI_NCR_TRUST_BIOS_SETTING
macro_line|#endif
macro_line|#if 0
mdefine_line|#define SCSI_NCR_SPECIAL_FEATURES
macro_line|#endif
multiline_comment|/*********** LINUX SPECIFIC SECTION ******************/
multiline_comment|/*&n;**&t;Check supported Linux versions&n;*/
macro_line|#if !defined(LINUX_VERSION_CODE)
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n;**&t;During make dep of linux-1.2.13, LINUX_VERSION_CODE is undefined&n;**&t;Under linux-1.3.X, all seems to be OK.&n;**&t;So, we have only to define it under 1.2.13&n;*/
DECL|macro|LinuxVersionCode
mdefine_line|#define LinuxVersionCode(v, p, s) (((v)&lt;&lt;16)+((p)&lt;&lt;8)+(s))
macro_line|#if !defined(LINUX_VERSION_CODE)
DECL|macro|LINUX_VERSION_CODE
mdefine_line|#define LINUX_VERSION_CODE LinuxVersionCode(1,2,13)
macro_line|#endif
macro_line|#if !defined(VERSION)
DECL|macro|VERSION
mdefine_line|#define VERSION&t;&t;((LINUX_VERSION_CODE &gt;&gt; 16) &amp; 0xff)
DECL|macro|PATCHLEVEL
mdefine_line|#define PATCHLEVEL&t;((LINUX_VERSION_CODE &gt;&gt; 8)  &amp; 0xff)
DECL|macro|SUBLEVEL
mdefine_line|#define SUBLEVEL&t;((LINUX_VERSION_CODE &gt;&gt; 0)  &amp; 0xff)
macro_line|#endif
macro_line|#if&t;VERSION == 0 || VERSION &gt; 3
macro_line|#&t;error Only Linux version 1 and probable 2 or 3 supported.
macro_line|#endif
macro_line|#if&t;VERSION == 1 &amp;&amp; PATCHLEVEL == 2
macro_line|#&t;if&t;SUBLEVEL != 13
macro_line|#&t;&t;error Only sublevel 13 of Linux 1.2 is supported.
macro_line|#&t;endif
macro_line|#endif
macro_line|#if&t;VERSION == 1 &amp;&amp; PATCHLEVEL == 3
macro_line|#&t;if&t;SUBLEVEL &lt; 45
macro_line|#&t;&t;error Only sublevels &gt;=45 of Linux 1.3 are supported.
macro_line|#&t;endif
macro_line|#endif
multiline_comment|/*&n;**&t;Normal IO or memory mapped IO.&n;**&n;**&t;Memory mapped IO only works with linux-1.3.X&n;**&t;If your motherboard does not work with memory mapped IO,&n;**&t;define SCSI_NCR_IOMAPPED for PATCHLEVEL 3 too.&n;*/
macro_line|#if&t;LINUX_VERSION_CODE &lt; LinuxVersionCode(1,3,0)
DECL|macro|SCSI_NCR_IOMAPPED
macro_line|#&t;define&t;SCSI_NCR_IOMAPPED
macro_line|#endif
macro_line|#if&t;LINUX_VERSION_CODE &gt;= LinuxVersionCode(1,3,0)
DECL|macro|SCSI_NCR_PROC_INFO_SUPPORT
macro_line|#&t;define&t;SCSI_NCR_PROC_INFO_SUPPORT
macro_line|#endif
macro_line|#if&t;LINUX_VERSION_CODE &gt;= LinuxVersionCode(1,3,72)
DECL|macro|SCSI_NCR_SHARE_IRQ
macro_line|#&t;define SCSI_NCR_SHARE_IRQ
macro_line|#endif
multiline_comment|/*&n;**&t;Avoid to change these constants, unless you know what you are doing.&n;*/
macro_line|#ifdef&t;CONFIG_SCSI_NCR53C8XX_MAX_TAGS
macro_line|#if&t;CONFIG_SCSI_NCR53C8XX_MAX_TAGS &lt; 2
DECL|macro|SCSI_NCR_MAX_TAGS
mdefine_line|#define SCSI_NCR_MAX_TAGS&t;(2)
macro_line|#elif&t;CONFIG_SCSI_NCR53C8XX_MAX_TAGS &gt; 12
DECL|macro|SCSI_NCR_MAX_TAGS
mdefine_line|#define SCSI_NCR_MAX_TAGS&t;(12)
macro_line|#else
DECL|macro|SCSI_NCR_MAX_TAGS
mdefine_line|#define&t;SCSI_NCR_MAX_TAGS&t;CONFIG_SCSI_NCR53C8XX_MAX_TAGS
macro_line|#endif
macro_line|#else
DECL|macro|SCSI_NCR_MAX_TAGS
mdefine_line|#define SCSI_NCR_MAX_TAGS&t;(4)
macro_line|#endif
DECL|macro|SCSI_NCR_ALWAYS_SIMPLE_TAG
mdefine_line|#define SCSI_NCR_ALWAYS_SIMPLE_TAG
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX_TAGGED_QUEUE
DECL|macro|SCSI_NCR_DEFAULT_TAGS
mdefine_line|#define SCSI_NCR_DEFAULT_TAGS&t;SCSI_NCR_MAX_TAGS
macro_line|#else
DECL|macro|SCSI_NCR_DEFAULT_TAGS
mdefine_line|#define SCSI_NCR_DEFAULT_TAGS&t;(0)
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX_IOMAPPED
DECL|macro|SCSI_NCR_IOMAPPED
mdefine_line|#define&t;SCSI_NCR_IOMAPPED
macro_line|#endif
macro_line|#ifdef&t;CONFIG_SCSI_NCR53C8XX_SYNC
macro_line|#if&t;CONFIG_SCSI_NCR53C8XX_SYNC == 0
DECL|macro|SCSI_NCR_DEFAULT_SYNC
mdefine_line|#define&t;SCSI_NCR_DEFAULT_SYNC&t;(0)
macro_line|#elif&t;CONFIG_SCSI_NCR53C8XX_SYNC &lt; 5
DECL|macro|SCSI_NCR_DEFAULT_SYNC
mdefine_line|#define&t;SCSI_NCR_DEFAULT_SYNC&t;(5000)
macro_line|#elif&t;CONFIG_SCSI_NCR53C8XX_SYNC &gt; 10
DECL|macro|SCSI_NCR_DEFAULT_SYNC
mdefine_line|#define&t;SCSI_NCR_DEFAULT_SYNC&t;(10000)
macro_line|#else
DECL|macro|SCSI_NCR_DEFAULT_SYNC
mdefine_line|#define&t;SCSI_NCR_DEFAULT_SYNC&t;(CONFIG_SCSI_NCR53C8XX_SYNC * 1000)
macro_line|#endif
macro_line|#else
DECL|macro|SCSI_NCR_DEFAULT_SYNC
mdefine_line|#define&t;SCSI_NCR_DEFAULT_SYNC&t;(10000)
macro_line|#endif
macro_line|#ifdef&t;CONFIG_SCSI_FORCE_ASYNCHRONOUS
DECL|macro|SCSI_NCR_DEFAULT_SYNC
macro_line|#undef&t;SCSI_NCR_DEFAULT_SYNC
DECL|macro|SCSI_NCR_DEFAULT_SYNC
mdefine_line|#define SCSI_NCR_DEFAULT_SYNC&t;(0)
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX_NO_DISCONNECT
DECL|macro|SCSI_NCR_NO_DISCONNECT
mdefine_line|#define SCSI_NCR_NO_DISCONNECT
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX_FORCE_SYNC_NEGO
DECL|macro|SCSI_NCR_FORCE_SYNC_NEGO
mdefine_line|#define SCSI_NCR_FORCE_SYNC_NEGO
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX_DISABLE_MPARITY_CHECK
DECL|macro|SCSI_NCR_DISABLE_MPARITY_CHECK
mdefine_line|#define SCSI_NCR_DISABLE_MPARITY_CHECK
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX_DISABLE_PARITY_CHECK
DECL|macro|SCSI_NCR_DISABLE_PARITY_CHECK
mdefine_line|#define SCSI_NCR_DISABLE_PARITY_CHECK
macro_line|#endif
macro_line|#if 0
mdefine_line|#define SCSI_NCR_SEGMENT_SIZE&t;(512)
macro_line|#endif
DECL|macro|SCSI_NCR_MAX_SCATTER
mdefine_line|#define SCSI_NCR_MAX_SCATTER&t;(128)
DECL|macro|SCSI_NCR_MAX_TARGET
mdefine_line|#define SCSI_NCR_MAX_TARGET&t;(16)
DECL|macro|SCSI_NCR_MAX_HOST
mdefine_line|#define SCSI_NCR_MAX_HOST&t;(2)
DECL|macro|SCSI_NCR_SETTLE_TIME
mdefine_line|#define SCSI_NCR_SETTLE_TIME&t;(2)
DECL|macro|SCSI_NCR_TIMEOUT_ALERT
mdefine_line|#define SCSI_NCR_TIMEOUT_ALERT&t;(3*HZ)
DECL|macro|SCSI_NCR_CAN_QUEUE
mdefine_line|#define SCSI_NCR_CAN_QUEUE&t;(7*SCSI_NCR_MAX_TAGS)
DECL|macro|SCSI_NCR_CMD_PER_LUN
mdefine_line|#define SCSI_NCR_CMD_PER_LUN&t;(SCSI_NCR_MAX_TAGS)
DECL|macro|SCSI_NCR_SG_TABLESIZE
mdefine_line|#define SCSI_NCR_SG_TABLESIZE&t;(SCSI_NCR_MAX_SCATTER-1)
macro_line|#if 1 /* defined CONFIG_SCSI_MULTI_LUN */
DECL|macro|SCSI_NCR_MAX_LUN
mdefine_line|#define SCSI_NCR_MAX_LUN&t;(8)
macro_line|#else
DECL|macro|SCSI_NCR_MAX_LUN
mdefine_line|#define SCSI_NCR_MAX_LUN&t;(1)
macro_line|#endif
DECL|macro|SCSI_NCR_TIMER_INTERVAL
mdefine_line|#define SCSI_NCR_TIMER_INTERVAL&t;((HZ+5-1)/5)
multiline_comment|/*&n;**&t;Define Scsi_Host_Template parameters&n;**&n;**&t;Used by hosts.c and ncr53c8xx.c with module configuration.&n;*/
macro_line|#if defined(HOSTS_C) || defined(MODULE)
macro_line|#if&t;LINUX_VERSION_CODE &gt;= LinuxVersionCode(1,3,98)
macro_line|#include &lt;scsi/scsicam.h&gt;
macro_line|#else
macro_line|#include &lt;linux/scsicam.h&gt;
macro_line|#endif
r_int
id|ncr53c8xx_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_int
id|ncr53c8xx_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
suffix:semicolon
r_int
id|ncr53c8xx_queue_command
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
macro_line|#if&t;LINUX_VERSION_CODE &gt;= LinuxVersionCode(1,3,98)
r_int
id|ncr53c8xx_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#else
r_int
id|ncr53c8xx_reset
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef MODULE
r_int
id|ncr53c8xx_release
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
macro_line|#else
DECL|macro|ncr53c8xx_release
mdefine_line|#define ncr53c8xx_release NULL
macro_line|#endif
macro_line|#if&t;LINUX_VERSION_CODE &gt;= LinuxVersionCode(1,3,0)
DECL|macro|NCR53C8XX
mdefine_line|#define NCR53C8XX {NULL,NULL,NULL,NULL,SCSI_NCR_DRIVER_NAME, ncr53c8xx_detect,&bslash;&n;    &t;ncr53c8xx_release, /* info */ NULL, /* command, deprecated */ NULL, &t;&t;&bslash;&n;&t;ncr53c8xx_queue_command, ncr53c8xx_abort, ncr53c8xx_reset,&t;&bslash;&n;        NULL /* slave attach */, scsicam_bios_param, /* can queue */ SCSI_NCR_CAN_QUEUE,&bslash;&n;&t;/* id */ 7, SCSI_NCR_SG_TABLESIZE /* SG */, /* cmd per lun */ SCSI_NCR_CMD_PER_LUN, &t;&t;&bslash;&n;        /* present */ 0, /* unchecked isa dma */ 0, DISABLE_CLUSTERING} 
macro_line|#else
DECL|macro|NCR53C8XX
mdefine_line|#define NCR53C8XX {NULL, NULL, SCSI_NCR_DRIVER_NAME, ncr53c8xx_detect,&bslash;&n;    &t;ncr53c8xx_release, /* info */ NULL, /* command, deprecated */ NULL, &t;&t;&bslash;&n;&t;ncr53c8xx_queue_command, ncr53c8xx_abort, ncr53c8xx_reset,&t;&bslash;&n;        NULL /* slave attach */, scsicam_bios_param, /* can queue */ SCSI_NCR_CAN_QUEUE,&bslash;&n;&t;/* id */ 7, SCSI_NCR_SG_TABLESIZE /* SG */, /* cmd per lun */ SCSI_NCR_CMD_PER_LUN, &t;&t;&bslash;&n;        /* present */ 0, /* unchecked isa dma */ 0, DISABLE_CLUSTERING} 
macro_line|#endif /* LINUX_VERSION_CODE &gt;= LinuxVersionCode(1,3,0) */
macro_line|#endif /* defined(HOSTS_C) || defined(MODULE) */ 
macro_line|#ifndef HOSTS_C
multiline_comment|/*&n;**&t;Define the table of target capabilities by host and target&n;**&n;**&t;If you have problems with a scsi device, note the host unit and the&n;**&t;corresponding target number.&n;**&n;**&t;Edit the corresponding entry of the table below and try successively:&n;**&t;&t;NQ7_Questionnable&n;**&t;&t;NQ7_IdeLike&n;**&n;**&t;This bitmap is anded with the byte 7 of inquiry data on completion of&n;**&t;INQUIRY command.&n;**&t;The driver never see the zeroed bits and will ignore the corresponding&n;**&t;capabilities of the target.&n;*/
DECL|macro|INQ7_SftRe
mdefine_line|#define INQ7_SftRe&t;1
DECL|macro|INQ7_CmdQueue
mdefine_line|#define INQ7_CmdQueue&t;(1&lt;&lt;1)&t;&t;/* Tagged Command */
DECL|macro|INQ7_Reserved
mdefine_line|#define INQ7_Reserved&t;(1&lt;&lt;2)
DECL|macro|INQ7_Linked
mdefine_line|#define INQ7_Linked&t;(1&lt;&lt;3)
DECL|macro|INQ7_Sync
mdefine_line|#define INQ7_Sync&t;(1&lt;&lt;4)&t;&t;/* Synchronous Negotiation */
DECL|macro|INQ7_WBus16
mdefine_line|#define INQ7_WBus16&t;(1&lt;&lt;5)
DECL|macro|INQ7_WBus32
mdefine_line|#define INQ7_WBus32&t;(1&lt;&lt;6)
DECL|macro|INQ7_RelAdr
mdefine_line|#define INQ7_RelAdr&t;(1&lt;&lt;7)
DECL|macro|INQ7_IdeLike
mdefine_line|#define INQ7_IdeLike&t;&t;0
DECL|macro|INQ7_Scsi1Like
mdefine_line|#define INQ7_Scsi1Like&t;&t;INQ7_IdeLike
DECL|macro|INQ7_Perfect
mdefine_line|#define INQ7_Perfect&t;&t;0xff
DECL|macro|INQ7_Questionnable
mdefine_line|#define INQ7_Questionnable&t;~(INQ7_CmdQueue|INQ7_Sync)
DECL|macro|INQ7_VeryQuestionnable
mdefine_line|#define INQ7_VeryQuestionnable&t;&bslash;&n;&t;&t;&t;~(INQ7_CmdQueue|INQ7_Sync|INQ7_WBus16|INQ7_WBus32)
DECL|macro|INQ7_Default
mdefine_line|#define INQ7_Default&t;&t;INQ7_Perfect
DECL|macro|NCR53C8XX_TARGET_CAPABILITIES
mdefine_line|#define NCR53C8XX_TARGET_CAPABILITIES&t;&t;&t;&t;&t;&bslash;&n;/* Host 0 */&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* Target  0 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target  1 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target  2 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target  3 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target  4 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target  5 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target  6 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target  7 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target  8 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target  9 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target 10 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target 11 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target 12 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target 13 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target 14 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target 15 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;},&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;/* Host 1 */&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;/* Target  0 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target  1 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target  2 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target  3 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target  4 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target  5 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target  6 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target  7 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target  8 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target  9 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target 10 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target 11 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target 12 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target 13 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target 14 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;/* Target 15 */&t;&t;INQ7_Default,&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n;**&t;Replace the proc_dir_entry of the standard ncr driver.&n;*/
macro_line|#if&t;LINUX_VERSION_CODE &gt;= LinuxVersionCode(1,3,0)
macro_line|#if&t;defined(CONFIG_SCSI_NCR53C7xx) || !defined(CONFIG_SCSI_NCR53C8XX)
DECL|macro|PROC_SCSI_NCR53C8XX
mdefine_line|#define PROC_SCSI_NCR53C8XX&t;PROC_SCSI_NCR53C7xx
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n;**&t;NCR53C8XX Device Ids&n;*/
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C810
DECL|macro|PCI_DEVICE_ID_NCR_53C810
mdefine_line|#define PCI_DEVICE_ID_NCR_53C810 1
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C810AP
DECL|macro|PCI_DEVICE_ID_NCR_53C810AP
mdefine_line|#define PCI_DEVICE_ID_NCR_53C810AP 5
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C815
DECL|macro|PCI_DEVICE_ID_NCR_53C815
mdefine_line|#define PCI_DEVICE_ID_NCR_53C815 4
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C820
DECL|macro|PCI_DEVICE_ID_NCR_53C820
mdefine_line|#define PCI_DEVICE_ID_NCR_53C820 2
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C825
DECL|macro|PCI_DEVICE_ID_NCR_53C825
mdefine_line|#define PCI_DEVICE_ID_NCR_53C825 3
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C860
DECL|macro|PCI_DEVICE_ID_NCR_53C860
mdefine_line|#define PCI_DEVICE_ID_NCR_53C860 6
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C875
DECL|macro|PCI_DEVICE_ID_NCR_53C875
mdefine_line|#define PCI_DEVICE_ID_NCR_53C875 0xf
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C885
DECL|macro|PCI_DEVICE_ID_NCR_53C885
mdefine_line|#define PCI_DEVICE_ID_NCR_53C885 0xd
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C895
DECL|macro|PCI_DEVICE_ID_NCR_53C895
mdefine_line|#define PCI_DEVICE_ID_NCR_53C895 0xc
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C896
DECL|macro|PCI_DEVICE_ID_NCR_53C896
mdefine_line|#define PCI_DEVICE_ID_NCR_53C896 0xb
macro_line|#endif
multiline_comment|/**************** ORIGINAL CONTENT of ncrreg.h from FreeBSD ******************/
multiline_comment|/*-----------------------------------------------------------------&n;**&n;**&t;The ncr 53c810 register structure.&n;**&n;**-----------------------------------------------------------------&n;*/
DECL|struct|ncr_reg
r_struct
id|ncr_reg
(brace
DECL|member|nc_scntl0
multiline_comment|/*00*/
id|u_char
id|nc_scntl0
suffix:semicolon
multiline_comment|/* full arb., ena parity, par-&gt;ATN  */
DECL|member|nc_scntl1
multiline_comment|/*01*/
id|u_char
id|nc_scntl1
suffix:semicolon
multiline_comment|/* no reset                         */
DECL|macro|ISCON
mdefine_line|#define   ISCON   0x10  /* connected to scsi&t;&t;    */
DECL|macro|CRST
mdefine_line|#define   CRST    0x08  /* force reset                      */
DECL|member|nc_scntl2
multiline_comment|/*02*/
id|u_char
id|nc_scntl2
suffix:semicolon
multiline_comment|/* no disconnect expected           */
DECL|macro|SDU
mdefine_line|#define   SDU     0x80  /* cmd: disconnect will raise error */
DECL|macro|CHM
mdefine_line|#define   CHM     0x40  /* sta: chained mode                */
DECL|macro|WSS
mdefine_line|#define   WSS     0x08  /* sta: wide scsi send           [W]*/
DECL|macro|WSR
mdefine_line|#define   WSR     0x01  /* sta: wide scsi received       [W]*/
DECL|member|nc_scntl3
multiline_comment|/*03*/
id|u_char
id|nc_scntl3
suffix:semicolon
multiline_comment|/* cnf system clock dependent       */
DECL|macro|EWS
mdefine_line|#define   EWS     0x08  /* cmd: enable wide scsi         [W]*/
DECL|member|nc_scid
multiline_comment|/*04*/
id|u_char
id|nc_scid
suffix:semicolon
multiline_comment|/* cnf host adapter scsi address    */
DECL|macro|RRE
mdefine_line|#define   RRE     0x40  /* r/w:e enable response to resel.  */
DECL|macro|SRE
mdefine_line|#define   SRE     0x20  /* r/w:e enable response to select  */
DECL|member|nc_sxfer
multiline_comment|/*05*/
id|u_char
id|nc_sxfer
suffix:semicolon
multiline_comment|/* ### Sync speed and count         */
DECL|member|nc_sdid
multiline_comment|/*06*/
id|u_char
id|nc_sdid
suffix:semicolon
multiline_comment|/* ### Destination-ID               */
DECL|member|nc_gpreg
multiline_comment|/*07*/
id|u_char
id|nc_gpreg
suffix:semicolon
multiline_comment|/* ??? IO-Pins                      */
DECL|member|nc_sfbr
multiline_comment|/*08*/
id|u_char
id|nc_sfbr
suffix:semicolon
multiline_comment|/* ### First byte in phase          */
DECL|member|nc_socl
multiline_comment|/*09*/
id|u_char
id|nc_socl
suffix:semicolon
DECL|macro|CREQ
mdefine_line|#define   CREQ&t;  0x80&t;/* r/w: SCSI-REQ                    */
DECL|macro|CACK
mdefine_line|#define   CACK&t;  0x40&t;/* r/w: SCSI-ACK                    */
DECL|macro|CBSY
mdefine_line|#define   CBSY&t;  0x20&t;/* r/w: SCSI-BSY                    */
DECL|macro|CSEL
mdefine_line|#define   CSEL&t;  0x10&t;/* r/w: SCSI-SEL                    */
DECL|macro|CATN
mdefine_line|#define   CATN&t;  0x08&t;/* r/w: SCSI-ATN                    */
DECL|macro|CMSG
mdefine_line|#define   CMSG&t;  0x04&t;/* r/w: SCSI-MSG                    */
DECL|macro|CC_D
mdefine_line|#define   CC_D&t;  0x02&t;/* r/w: SCSI-C_D                    */
DECL|macro|CI_O
mdefine_line|#define   CI_O&t;  0x01&t;/* r/w: SCSI-I_O                    */
DECL|member|nc_ssid
multiline_comment|/*0a*/
id|u_char
id|nc_ssid
suffix:semicolon
DECL|member|nc_sbcl
multiline_comment|/*0b*/
id|u_char
id|nc_sbcl
suffix:semicolon
DECL|member|nc_dstat
multiline_comment|/*0c*/
id|u_char
id|nc_dstat
suffix:semicolon
DECL|macro|DFE
mdefine_line|#define   DFE     0x80  /* sta: dma fifo empty              */
DECL|macro|MDPE
mdefine_line|#define   MDPE    0x40  /* int: master data parity error    */
DECL|macro|BF
mdefine_line|#define   BF      0x20  /* int: script: bus fault           */
DECL|macro|ABRT
mdefine_line|#define   ABRT    0x10  /* int: script: command aborted     */
DECL|macro|SSI
mdefine_line|#define   SSI     0x08  /* int: script: single step         */
DECL|macro|SIR
mdefine_line|#define   SIR     0x04  /* int: script: interrupt instruct. */
DECL|macro|IID
mdefine_line|#define   IID     0x01  /* int: script: illegal instruct.   */
DECL|member|nc_sstat0
multiline_comment|/*0d*/
id|u_char
id|nc_sstat0
suffix:semicolon
DECL|macro|ILF
mdefine_line|#define   ILF     0x80  /* sta: data in SIDL register lsb   */
DECL|macro|ORF
mdefine_line|#define   ORF     0x40  /* sta: data in SODR register lsb   */
DECL|macro|OLF
mdefine_line|#define   OLF     0x20  /* sta: data in SODL register lsb   */
DECL|macro|AIP
mdefine_line|#define   AIP     0x10  /* sta: arbitration in progress     */
DECL|macro|LOA
mdefine_line|#define   LOA     0x08  /* sta: arbitration lost            */
DECL|macro|WOA
mdefine_line|#define   WOA     0x04  /* sta: arbitration won             */
DECL|macro|IRST
mdefine_line|#define   IRST    0x02  /* sta: scsi reset signal           */
DECL|macro|SDP
mdefine_line|#define   SDP     0x01  /* sta: scsi parity signal          */
DECL|member|nc_sstat1
multiline_comment|/*0e*/
id|u_char
id|nc_sstat1
suffix:semicolon
DECL|macro|FF3210
mdefine_line|#define   FF3210  0xf0&t;/* sta: bytes in the scsi fifo      */
DECL|member|nc_sstat2
multiline_comment|/*0f*/
id|u_char
id|nc_sstat2
suffix:semicolon
DECL|macro|ILF1
mdefine_line|#define   ILF1    0x80  /* sta: data in SIDL register msb[W]*/
DECL|macro|ORF1
mdefine_line|#define   ORF1    0x40  /* sta: data in SODR register msb[W]*/
DECL|macro|OLF1
mdefine_line|#define   OLF1    0x20  /* sta: data in SODL register msb[W]*/
DECL|macro|LDSC
mdefine_line|#define   LDSC    0x02  /* sta: disconnect &amp; reconnect      */
DECL|member|nc_dsa
multiline_comment|/*10*/
id|u_int32
id|nc_dsa
suffix:semicolon
multiline_comment|/* --&gt; Base page                    */
DECL|member|nc_istat
multiline_comment|/*14*/
id|u_char
id|nc_istat
suffix:semicolon
multiline_comment|/* --&gt; Main Command and status      */
DECL|macro|CABRT
mdefine_line|#define   CABRT   0x80  /* cmd: abort current operation     */
DECL|macro|SRST
mdefine_line|#define   SRST    0x40  /* mod: reset chip                  */
DECL|macro|SIGP
mdefine_line|#define   SIGP    0x20  /* r/w: message from host to ncr    */
DECL|macro|SEM
mdefine_line|#define   SEM     0x10  /* r/w: message between host + ncr  */
DECL|macro|CON
mdefine_line|#define   CON     0x08  /* sta: connected to scsi           */
DECL|macro|INTF
mdefine_line|#define   INTF    0x04  /* sta: int on the fly (reset by wr)*/
DECL|macro|SIP
mdefine_line|#define   SIP     0x02  /* sta: scsi-interrupt              */
DECL|macro|DIP
mdefine_line|#define   DIP     0x01  /* sta: host/script interrupt       */
DECL|member|nc_15_
multiline_comment|/*15*/
id|u_char
id|nc_15_
suffix:semicolon
DECL|member|nc_16_
multiline_comment|/*16*/
id|u_char
id|nc_16_
suffix:semicolon
DECL|member|nc_17_
multiline_comment|/*17*/
id|u_char
id|nc_17_
suffix:semicolon
DECL|member|nc_ctest0
multiline_comment|/*18*/
id|u_char
id|nc_ctest0
suffix:semicolon
DECL|member|nc_ctest1
multiline_comment|/*19*/
id|u_char
id|nc_ctest1
suffix:semicolon
DECL|member|nc_ctest2
multiline_comment|/*1a*/
id|u_char
id|nc_ctest2
suffix:semicolon
DECL|macro|CSIGP
mdefine_line|#define   CSIGP   0x40
DECL|member|nc_ctest3
multiline_comment|/*1b*/
id|u_char
id|nc_ctest3
suffix:semicolon
DECL|macro|CLF
mdefine_line|#define   CLF&t;  0x04&t;/* clear scsi fifo&t;&t;    */
DECL|member|nc_temp
multiline_comment|/*1c*/
id|u_int32
id|nc_temp
suffix:semicolon
multiline_comment|/* ### Temporary stack              */
DECL|member|nc_dfifo
multiline_comment|/*20*/
id|u_char
id|nc_dfifo
suffix:semicolon
DECL|member|nc_ctest4
multiline_comment|/*21*/
id|u_char
id|nc_ctest4
suffix:semicolon
DECL|member|nc_ctest5
multiline_comment|/*22*/
id|u_char
id|nc_ctest5
suffix:semicolon
DECL|member|nc_ctest6
multiline_comment|/*23*/
id|u_char
id|nc_ctest6
suffix:semicolon
DECL|member|nc_dbc
multiline_comment|/*24*/
id|u_int32
id|nc_dbc
suffix:semicolon
multiline_comment|/* ### Byte count and command       */
DECL|member|nc_dnad
multiline_comment|/*28*/
id|u_int32
id|nc_dnad
suffix:semicolon
multiline_comment|/* ### Next command register        */
DECL|member|nc_dsp
multiline_comment|/*2c*/
id|u_int32
id|nc_dsp
suffix:semicolon
multiline_comment|/* --&gt; Script Pointer               */
DECL|member|nc_dsps
multiline_comment|/*30*/
id|u_int32
id|nc_dsps
suffix:semicolon
multiline_comment|/* --&gt; Script pointer save/opcode#2 */
DECL|member|nc_scratcha
multiline_comment|/*34*/
id|u_int32
id|nc_scratcha
suffix:semicolon
multiline_comment|/* ??? Temporary register a         */
DECL|member|nc_dmode
multiline_comment|/*38*/
id|u_char
id|nc_dmode
suffix:semicolon
DECL|member|nc_dien
multiline_comment|/*39*/
id|u_char
id|nc_dien
suffix:semicolon
DECL|member|nc_dwt
multiline_comment|/*3a*/
id|u_char
id|nc_dwt
suffix:semicolon
DECL|member|nc_dcntl
multiline_comment|/*3b*/
id|u_char
id|nc_dcntl
suffix:semicolon
multiline_comment|/* --&gt; Script execution control     */
DECL|macro|SSM
mdefine_line|#define   SSM     0x10  /* mod: single step mode            */
DECL|macro|STD
mdefine_line|#define   STD     0x04  /* cmd: start dma mode              */
DECL|macro|NOCOM
mdefine_line|#define&t;  NOCOM   0x01&t;/* cmd: protect sfbr while reselect */
DECL|member|nc_adder
multiline_comment|/*3c*/
id|u_int32
id|nc_adder
suffix:semicolon
DECL|member|nc_sien
multiline_comment|/*40*/
id|u_short
id|nc_sien
suffix:semicolon
multiline_comment|/* --&gt;: interrupt enable            */
DECL|member|nc_sist
multiline_comment|/*42*/
id|u_short
id|nc_sist
suffix:semicolon
multiline_comment|/* &lt;--: interrupt status            */
DECL|macro|STO
mdefine_line|#define   STO     0x0400/* sta: timeout (select)            */
DECL|macro|GEN
mdefine_line|#define   GEN     0x0200/* sta: timeout (general)           */
DECL|macro|HTH
mdefine_line|#define   HTH     0x0100/* sta: timeout (handshake)         */
DECL|macro|MA
mdefine_line|#define   MA      0x80  /* sta: phase mismatch              */
DECL|macro|CMP
mdefine_line|#define   CMP     0x40  /* sta: arbitration complete        */
DECL|macro|SEL
mdefine_line|#define   SEL     0x20  /* sta: selected by another device  */
DECL|macro|RSL
mdefine_line|#define   RSL     0x10  /* sta: reselected by another device*/
DECL|macro|SGE
mdefine_line|#define   SGE     0x08  /* sta: gross error (over/underflow)*/
DECL|macro|UDC
mdefine_line|#define   UDC     0x04  /* sta: unexpected disconnect       */
DECL|macro|RST
mdefine_line|#define   RST     0x02  /* sta: scsi bus reset detected     */
DECL|macro|PAR
mdefine_line|#define   PAR     0x01  /* sta: scsi parity error           */
DECL|member|nc_slpar
multiline_comment|/*44*/
id|u_char
id|nc_slpar
suffix:semicolon
DECL|member|nc_swide
multiline_comment|/*45*/
id|u_char
id|nc_swide
suffix:semicolon
DECL|member|nc_macntl
multiline_comment|/*46*/
id|u_char
id|nc_macntl
suffix:semicolon
DECL|member|nc_gpcntl
multiline_comment|/*47*/
id|u_char
id|nc_gpcntl
suffix:semicolon
DECL|member|nc_stime0
multiline_comment|/*48*/
id|u_char
id|nc_stime0
suffix:semicolon
multiline_comment|/* cmd: timeout for select&amp;handshake*/
DECL|member|nc_stime1
multiline_comment|/*49*/
id|u_char
id|nc_stime1
suffix:semicolon
multiline_comment|/* cmd: timeout user defined        */
DECL|member|nc_respid
multiline_comment|/*4a*/
id|u_short
id|nc_respid
suffix:semicolon
multiline_comment|/* sta: Reselect-IDs                */
DECL|member|nc_stest0
multiline_comment|/*4c*/
id|u_char
id|nc_stest0
suffix:semicolon
DECL|member|nc_stest1
multiline_comment|/*4d*/
id|u_char
id|nc_stest1
suffix:semicolon
DECL|macro|DBLEN
mdefine_line|#define   DBLEN   0x08&t;/* clock doubler running&t;&t;*/
DECL|macro|DBLSEL
mdefine_line|#define   DBLSEL  0x04&t;/* clock doubler selected&t;&t;*/
DECL|member|nc_stest2
multiline_comment|/*4e*/
id|u_char
id|nc_stest2
suffix:semicolon
DECL|macro|ROF
mdefine_line|#define   ROF     0x40&t;/* reset scsi offset (after gross error!) */
DECL|macro|EXT
mdefine_line|#define   EXT     0x02  /* extended filtering                     */
DECL|member|nc_stest3
multiline_comment|/*4f*/
id|u_char
id|nc_stest3
suffix:semicolon
DECL|macro|TE
mdefine_line|#define   TE     0x80&t;/* c: tolerAnt enable */
DECL|macro|CSF
mdefine_line|#define   CSF    0x02&t;/* c: clear scsi fifo */
DECL|member|nc_sidl
multiline_comment|/*50*/
id|u_short
id|nc_sidl
suffix:semicolon
multiline_comment|/* Lowlevel: latched from scsi data */
DECL|member|nc_52_
multiline_comment|/*52*/
id|u_short
id|nc_52_
suffix:semicolon
DECL|member|nc_sodl
multiline_comment|/*54*/
id|u_short
id|nc_sodl
suffix:semicolon
multiline_comment|/* Lowlevel: data out to scsi data  */
DECL|member|nc_56_
multiline_comment|/*56*/
id|u_short
id|nc_56_
suffix:semicolon
DECL|member|nc_sbdl
multiline_comment|/*58*/
id|u_short
id|nc_sbdl
suffix:semicolon
multiline_comment|/* Lowlevel: data from scsi data    */
DECL|member|nc_5a_
multiline_comment|/*5a*/
id|u_short
id|nc_5a_
suffix:semicolon
DECL|member|nc_scr0
multiline_comment|/*5c*/
id|u_char
id|nc_scr0
suffix:semicolon
multiline_comment|/* Working register B               */
DECL|member|nc_scr1
multiline_comment|/*5d*/
id|u_char
id|nc_scr1
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|nc_scr2
multiline_comment|/*5e*/
id|u_char
id|nc_scr2
suffix:semicolon
multiline_comment|/*                                  */
DECL|member|nc_scr3
multiline_comment|/*5f*/
id|u_char
id|nc_scr3
suffix:semicolon
multiline_comment|/*                                  */
multiline_comment|/*60*/
)brace
suffix:semicolon
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;Utility macros for the script.&n;**&n;**-----------------------------------------------------------&n;*/
DECL|macro|REGJ
mdefine_line|#define REGJ(p,r) (offsetof(struct ncr_reg, p ## r))
DECL|macro|REG
mdefine_line|#define REG(r) REGJ (nc_, r)
macro_line|#ifndef TARGET_MODE
DECL|macro|TARGET_MODE
mdefine_line|#define TARGET_MODE 0
macro_line|#endif
DECL|typedef|ncrcmd
r_typedef
id|u_int32
id|ncrcmd
suffix:semicolon
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;SCSI phases&n;**&n;**-----------------------------------------------------------&n;*/
DECL|macro|SCR_DATA_OUT
mdefine_line|#define&t;SCR_DATA_OUT&t;0x00000000
DECL|macro|SCR_DATA_IN
mdefine_line|#define&t;SCR_DATA_IN&t;0x01000000
DECL|macro|SCR_COMMAND
mdefine_line|#define&t;SCR_COMMAND&t;0x02000000
DECL|macro|SCR_STATUS
mdefine_line|#define&t;SCR_STATUS&t;0x03000000
DECL|macro|SCR_ILG_OUT
mdefine_line|#define SCR_ILG_OUT&t;0x04000000
DECL|macro|SCR_ILG_IN
mdefine_line|#define SCR_ILG_IN&t;0x05000000
DECL|macro|SCR_MSG_OUT
mdefine_line|#define SCR_MSG_OUT&t;0x06000000
DECL|macro|SCR_MSG_IN
mdefine_line|#define SCR_MSG_IN      0x07000000
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;Data transfer via SCSI.&n;**&n;**-----------------------------------------------------------&n;**&n;**&t;MOVE_ABS (LEN)&n;**&t;&lt;&lt;start address&gt;&gt;&n;**&n;**&t;MOVE_IND (LEN)&n;**&t;&lt;&lt;dnad_offset&gt;&gt;&n;**&n;**&t;MOVE_TBL&n;**&t;&lt;&lt;dnad_offset&gt;&gt;&n;**&n;**-----------------------------------------------------------&n;*/
DECL|macro|SCR_MOVE_ABS
mdefine_line|#define SCR_MOVE_ABS(l) ((0x08000000 ^ (TARGET_MODE &lt;&lt; 1ul)) | (l))
DECL|macro|SCR_MOVE_IND
mdefine_line|#define SCR_MOVE_IND(l) ((0x28000000 ^ (TARGET_MODE &lt;&lt; 1ul)) | (l))
DECL|macro|SCR_MOVE_TBL
mdefine_line|#define SCR_MOVE_TBL     (0x18000000 ^ (TARGET_MODE &lt;&lt; 1ul))
DECL|struct|scr_tblmove
r_struct
id|scr_tblmove
(brace
DECL|member|size
id|u_int32
id|size
suffix:semicolon
DECL|member|addr
id|u_int32
id|addr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;Selection&n;**&n;**-----------------------------------------------------------&n;**&n;**&t;SEL_ABS | SCR_ID (0..7)     [ | REL_JMP]&n;**&t;&lt;&lt;alternate_address&gt;&gt;&n;**&n;**&t;SEL_TBL | &lt;&lt; dnad_offset&gt;&gt;  [ | REL_JMP]&n;**&t;&lt;&lt;alternate_address&gt;&gt;&n;**&n;**-----------------------------------------------------------&n;*/
DECL|macro|SCR_SEL_ABS
mdefine_line|#define&t;SCR_SEL_ABS&t;0x40000000
DECL|macro|SCR_SEL_ABS_ATN
mdefine_line|#define&t;SCR_SEL_ABS_ATN&t;0x41000000
DECL|macro|SCR_SEL_TBL
mdefine_line|#define&t;SCR_SEL_TBL&t;0x42000000
DECL|macro|SCR_SEL_TBL_ATN
mdefine_line|#define&t;SCR_SEL_TBL_ATN&t;0x43000000
DECL|struct|scr_tblsel
r_struct
id|scr_tblsel
(brace
DECL|member|sel_0
id|u_char
id|sel_0
suffix:semicolon
DECL|member|sel_sxfer
id|u_char
id|sel_sxfer
suffix:semicolon
DECL|member|sel_id
id|u_char
id|sel_id
suffix:semicolon
DECL|member|sel_scntl3
id|u_char
id|sel_scntl3
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SCR_JMP_REL
mdefine_line|#define SCR_JMP_REL     0x04000000
DECL|macro|SCR_ID
mdefine_line|#define SCR_ID(id)&t;(((u_int32)(id)) &lt;&lt; 16)
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;Waiting for Disconnect or Reselect&n;**&n;**-----------------------------------------------------------&n;**&n;**&t;WAIT_DISC&n;**&t;dummy: &lt;&lt;alternate_address&gt;&gt;&n;**&n;**&t;WAIT_RESEL&n;**&t;&lt;&lt;alternate_address&gt;&gt;&n;**&n;**-----------------------------------------------------------&n;*/
DECL|macro|SCR_WAIT_DISC
mdefine_line|#define&t;SCR_WAIT_DISC&t;0x48000000
DECL|macro|SCR_WAIT_RESEL
mdefine_line|#define SCR_WAIT_RESEL  0x50000000
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;Bit Set / Reset&n;**&n;**-----------------------------------------------------------&n;**&n;**&t;SET (flags {|.. })&n;**&n;**&t;CLR (flags {|.. })&n;**&n;**-----------------------------------------------------------&n;*/
DECL|macro|SCR_SET
mdefine_line|#define SCR_SET(f)     (0x58000000 | (f))
DECL|macro|SCR_CLR
mdefine_line|#define SCR_CLR(f)     (0x60000000 | (f))
DECL|macro|SCR_CARRY
mdefine_line|#define&t;SCR_CARRY&t;0x00000400
DECL|macro|SCR_TRG
mdefine_line|#define&t;SCR_TRG&t;&t;0x00000200
DECL|macro|SCR_ACK
mdefine_line|#define&t;SCR_ACK&t;&t;0x00000040
DECL|macro|SCR_ATN
mdefine_line|#define&t;SCR_ATN&t;&t;0x00000008
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;Memory to memory move&n;**&n;**-----------------------------------------------------------&n;**&n;**&t;COPY (bytecount)&n;**&t;&lt;&lt; source_address &gt;&gt;&n;**&t;&lt;&lt; destination_address &gt;&gt;&n;**&n;**-----------------------------------------------------------&n;*/
DECL|macro|SCR_COPY
mdefine_line|#define SCR_COPY(n) (0xc0000000 | (n))
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;Register move and binary operations&n;**&n;**-----------------------------------------------------------&n;**&n;**&t;SFBR_REG (reg, op, data)        reg  = SFBR op data&n;**&t;&lt;&lt; 0 &gt;&gt;&n;**&n;**&t;REG_SFBR (reg, op, data)        SFBR = reg op data&n;**&t;&lt;&lt; 0 &gt;&gt;&n;**&n;**&t;REG_REG  (reg, op, data)        reg  = reg op data&n;**&t;&lt;&lt; 0 &gt;&gt;&n;**&n;**-----------------------------------------------------------&n;*/
DECL|macro|SCR_REG_OFS
mdefine_line|#define SCR_REG_OFS(ofs) ((ofs) &lt;&lt; 16ul)
DECL|macro|SCR_SFBR_REG
mdefine_line|#define SCR_SFBR_REG(reg,op,data) &bslash;&n;        (0x68000000 | (SCR_REG_OFS(REG(reg))) | (op) | ((data)&lt;&lt;8ul))
DECL|macro|SCR_REG_SFBR
mdefine_line|#define SCR_REG_SFBR(reg,op,data) &bslash;&n;        (0x70000000 | (SCR_REG_OFS(REG(reg))) | (op) | ((data)&lt;&lt;8ul))
DECL|macro|SCR_REG_REG
mdefine_line|#define SCR_REG_REG(reg,op,data) &bslash;&n;        (0x78000000 | (SCR_REG_OFS(REG(reg))) | (op) | ((data)&lt;&lt;8ul))
DECL|macro|SCR_LOAD
mdefine_line|#define      SCR_LOAD   0x00000000
DECL|macro|SCR_SHL
mdefine_line|#define      SCR_SHL    0x01000000
DECL|macro|SCR_OR
mdefine_line|#define      SCR_OR     0x02000000
DECL|macro|SCR_XOR
mdefine_line|#define      SCR_XOR    0x03000000
DECL|macro|SCR_AND
mdefine_line|#define      SCR_AND    0x04000000
DECL|macro|SCR_SHR
mdefine_line|#define      SCR_SHR    0x05000000
DECL|macro|SCR_ADD
mdefine_line|#define      SCR_ADD    0x06000000
DECL|macro|SCR_ADDC
mdefine_line|#define      SCR_ADDC   0x07000000
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;FROM_REG (reg)&t;&t;  reg  = SFBR&n;**&t;&lt;&lt; 0 &gt;&gt;&n;**&n;**&t;TO_REG&t; (reg)&t;&t;  SFBR = reg&n;**&t;&lt;&lt; 0 &gt;&gt;&n;**&n;**&t;LOAD_REG (reg, data)&t;  reg  = &lt;data&gt;&n;**&t;&lt;&lt; 0 &gt;&gt;&n;**&n;**&t;LOAD_SFBR(data) &t;  SFBR = &lt;data&gt;&n;**&t;&lt;&lt; 0 &gt;&gt;&n;**&n;**-----------------------------------------------------------&n;*/
DECL|macro|SCR_FROM_REG
mdefine_line|#define&t;SCR_FROM_REG(reg) &bslash;&n;&t;SCR_REG_SFBR(reg,SCR_OR,0)
DECL|macro|SCR_TO_REG
mdefine_line|#define&t;SCR_TO_REG(reg) &bslash;&n;&t;SCR_SFBR_REG(reg,SCR_OR,0)
DECL|macro|SCR_LOAD_REG
mdefine_line|#define&t;SCR_LOAD_REG(reg,data) &bslash;&n;&t;SCR_REG_REG(reg,SCR_LOAD,data)
DECL|macro|SCR_LOAD_SFBR
mdefine_line|#define SCR_LOAD_SFBR(data) &bslash;&n;        (SCR_REG_SFBR (gpreg, SCR_LOAD, data))
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;Waiting for Disconnect or Reselect&n;**&n;**-----------------------------------------------------------&n;**&n;**&t;JUMP            [ | IFTRUE/IFFALSE ( ... ) ]&n;**&t;&lt;&lt;address&gt;&gt;&n;**&n;**&t;JUMPR           [ | IFTRUE/IFFALSE ( ... ) ]&n;**&t;&lt;&lt;distance&gt;&gt;&n;**&n;**&t;CALL            [ | IFTRUE/IFFALSE ( ... ) ]&n;**&t;&lt;&lt;address&gt;&gt;&n;**&n;**&t;CALLR           [ | IFTRUE/IFFALSE ( ... ) ]&n;**&t;&lt;&lt;distance&gt;&gt;&n;**&n;**&t;RETURN          [ | IFTRUE/IFFALSE ( ... ) ]&n;**&t;&lt;&lt;dummy&gt;&gt;&n;**&n;**&t;INT             [ | IFTRUE/IFFALSE ( ... ) ]&n;**&t;&lt;&lt;ident&gt;&gt;&n;**&n;**&t;INT_FLY         [ | IFTRUE/IFFALSE ( ... ) ]&n;**&t;&lt;&lt;ident&gt;&gt;&n;**&n;**&t;Conditions:&n;**&t;     WHEN (phase)&n;**&t;     IF   (phase)&n;**&t;     CARRY&n;**&t;     DATA (data, mask)&n;**&n;**-----------------------------------------------------------&n;*/
DECL|macro|SCR_JUMP
mdefine_line|#define SCR_JUMP        0x80080000
DECL|macro|SCR_JUMPR
mdefine_line|#define SCR_JUMPR       0x80880000
DECL|macro|SCR_CALL
mdefine_line|#define SCR_CALL        0x88080000
DECL|macro|SCR_CALLR
mdefine_line|#define SCR_CALLR       0x88880000
DECL|macro|SCR_RETURN
mdefine_line|#define SCR_RETURN      0x90080000
DECL|macro|SCR_INT
mdefine_line|#define SCR_INT         0x98080000
DECL|macro|SCR_INT_FLY
mdefine_line|#define SCR_INT_FLY     0x98180000
DECL|macro|IFFALSE
mdefine_line|#define IFFALSE(arg)   (0x00080000 | (arg))
DECL|macro|IFTRUE
mdefine_line|#define IFTRUE(arg)    (0x00000000 | (arg))
DECL|macro|WHEN
mdefine_line|#define WHEN(phase)    (0x00030000 | (phase))
DECL|macro|IF
mdefine_line|#define IF(phase)      (0x00020000 | (phase))
DECL|macro|DATA
mdefine_line|#define DATA(D)        (0x00040000 | ((D) &amp; 0xff))
DECL|macro|MASK
mdefine_line|#define MASK(D,M)      (0x00040000 | (((M ^ 0xff) &amp; 0xff) &lt;&lt; 8ul)|((D) &amp; 0xff))
DECL|macro|CARRYSET
mdefine_line|#define CARRYSET       (0x00200000)
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;SCSI  constants.&n;**&n;**-----------------------------------------------------------&n;*/
multiline_comment|/*&n;**&t;Messages&n;*/
DECL|macro|M_COMPLETE
mdefine_line|#define&t;M_COMPLETE&t;(0x00)
DECL|macro|M_EXTENDED
mdefine_line|#define&t;M_EXTENDED&t;(0x01)
DECL|macro|M_SAVE_DP
mdefine_line|#define&t;M_SAVE_DP&t;(0x02)
DECL|macro|M_RESTORE_DP
mdefine_line|#define&t;M_RESTORE_DP&t;(0x03)
DECL|macro|M_DISCONNECT
mdefine_line|#define&t;M_DISCONNECT&t;(0x04)
DECL|macro|M_ID_ERROR
mdefine_line|#define&t;M_ID_ERROR&t;(0x05)
DECL|macro|M_ABORT
mdefine_line|#define&t;M_ABORT&t;&t;(0x06)
DECL|macro|M_REJECT
mdefine_line|#define&t;M_REJECT&t;(0x07)
DECL|macro|M_NOOP
mdefine_line|#define&t;M_NOOP&t;&t;(0x08)
DECL|macro|M_PARITY
mdefine_line|#define&t;M_PARITY&t;(0x09)
DECL|macro|M_LCOMPLETE
mdefine_line|#define&t;M_LCOMPLETE&t;(0x0a)
DECL|macro|M_FCOMPLETE
mdefine_line|#define&t;M_FCOMPLETE&t;(0x0b)
DECL|macro|M_RESET
mdefine_line|#define&t;M_RESET&t;&t;(0x0c)
DECL|macro|M_ABORT_TAG
mdefine_line|#define&t;M_ABORT_TAG&t;(0x0d)
DECL|macro|M_CLEAR_QUEUE
mdefine_line|#define&t;M_CLEAR_QUEUE&t;(0x0e)
DECL|macro|M_INIT_REC
mdefine_line|#define&t;M_INIT_REC&t;(0x0f)
DECL|macro|M_REL_REC
mdefine_line|#define&t;M_REL_REC&t;(0x10)
DECL|macro|M_TERMINATE
mdefine_line|#define&t;M_TERMINATE&t;(0x11)
DECL|macro|M_SIMPLE_TAG
mdefine_line|#define&t;M_SIMPLE_TAG&t;(0x20)
DECL|macro|M_HEAD_TAG
mdefine_line|#define&t;M_HEAD_TAG&t;(0x21)
DECL|macro|M_ORDERED_TAG
mdefine_line|#define&t;M_ORDERED_TAG&t;(0x22)
DECL|macro|M_IGN_RESIDUE
mdefine_line|#define&t;M_IGN_RESIDUE&t;(0x23)
DECL|macro|M_IDENTIFY
mdefine_line|#define&t;M_IDENTIFY   &t;(0x80)
DECL|macro|M_X_MODIFY_DP
mdefine_line|#define&t;M_X_MODIFY_DP&t;(0x00)
DECL|macro|M_X_SYNC_REQ
mdefine_line|#define&t;M_X_SYNC_REQ&t;(0x01)
DECL|macro|M_X_WIDE_REQ
mdefine_line|#define&t;M_X_WIDE_REQ&t;(0x03)
multiline_comment|/*&n;**&t;Status&n;*/
DECL|macro|S_GOOD
mdefine_line|#define&t;S_GOOD&t;&t;(0x00)
DECL|macro|S_CHECK_COND
mdefine_line|#define&t;S_CHECK_COND&t;(0x02)
DECL|macro|S_COND_MET
mdefine_line|#define&t;S_COND_MET&t;(0x04)
DECL|macro|S_BUSY
mdefine_line|#define&t;S_BUSY&t;&t;(0x08)
DECL|macro|S_INT
mdefine_line|#define&t;S_INT&t;&t;(0x10)
DECL|macro|S_INT_COND_MET
mdefine_line|#define&t;S_INT_COND_MET&t;(0x14)
DECL|macro|S_CONFLICT
mdefine_line|#define&t;S_CONFLICT&t;(0x18)
DECL|macro|S_TERMINATED
mdefine_line|#define&t;S_TERMINATED&t;(0x20)
DECL|macro|S_QUEUE_FULL
mdefine_line|#define&t;S_QUEUE_FULL&t;(0x28)
DECL|macro|S_ILLEGAL
mdefine_line|#define&t;S_ILLEGAL&t;(0xff)
DECL|macro|S_SENSE
mdefine_line|#define&t;S_SENSE&t;&t;(0x80)
multiline_comment|/*&n; * End of ncrreg from FreeBSD&n; */
macro_line|#endif /* !defined HOSTS_C */
macro_line|#endif /* defined NCR53C8XX_H */
eof
