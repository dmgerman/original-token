multiline_comment|/******************************************************************************&n;**  Device driver for the PCI-SCSI NCR538XX controller family.&n;**&n;**  Copyright (C) 1994  Wolfgang Stanglmeier&n;**&n;**  This program is free software; you can redistribute it and/or modify&n;**  it under the terms of the GNU General Public License as published by&n;**  the Free Software Foundation; either version 2 of the License, or&n;**  (at your option) any later version.&n;**&n;**  This program is distributed in the hope that it will be useful,&n;**  but WITHOUT ANY WARRANTY; without even the implied warranty of&n;**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;**  GNU General Public License for more details.&n;**&n;**  You should have received a copy of the GNU General Public License&n;**  along with this program; if not, write to the Free Software&n;**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;**&n;**-----------------------------------------------------------------------------&n;**&n;**  This driver has been ported to Linux from the FreeBSD NCR53C8XX driver&n;**  and is currently maintained by&n;**&n;**          Gerard Roudier              &lt;groudier@club-internet.fr&gt;&n;**&n;**  Being given that this driver originates from the FreeBSD version, and&n;**  in order to keep synergy on both, any suggested enhancements and corrections&n;**  received on Linux are automatically a potential candidate for the FreeBSD &n;**  version.&n;**&n;**  The original driver has been written for 386bsd and FreeBSD by&n;**          Wolfgang Stanglmeier        &lt;wolf@cologne.de&gt;&n;**          Stefan Esser                &lt;se@mi.Uni-Koeln.de&gt;&n;**&n;**  And has been ported to NetBSD by&n;**          Charles M. Hannum           &lt;mycroft@gnu.ai.mit.edu&gt;&n;**&n;*******************************************************************************&n;*/
macro_line|#ifndef NCR53C8XX_H
DECL|macro|NCR53C8XX_H
mdefine_line|#define NCR53C8XX_H
multiline_comment|/*&n;**&t;Name and revision of the driver&n;*/
DECL|macro|SCSI_NCR_DRIVER_NAME
mdefine_line|#define SCSI_NCR_DRIVER_NAME&t;&t;&quot;ncr53c8xx - revision 2.5f&quot;
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
multiline_comment|/*&n;**&t;If you want a driver as small as possible, donnot define the &n;**&t;following options.&n;*/
DECL|macro|SCSI_NCR_BOOT_COMMAND_LINE_SUPPORT
mdefine_line|#define SCSI_NCR_BOOT_COMMAND_LINE_SUPPORT
DECL|macro|SCSI_NCR_DEBUG_INFO_SUPPORT
mdefine_line|#define SCSI_NCR_DEBUG_INFO_SUPPORT
DECL|macro|SCSI_NCR_PCI_FIX_UP_SUPPORT
mdefine_line|#define SCSI_NCR_PCI_FIX_UP_SUPPORT
macro_line|#ifdef&t;SCSI_NCR_PROC_INFO_SUPPORT
DECL|macro|SCSI_NCR_PROFILE_SUPPORT
macro_line|#&t;define&t;SCSI_NCR_PROFILE_SUPPORT
DECL|macro|SCSI_NCR_USER_COMMAND_SUPPORT
macro_line|#&t;define&t;SCSI_NCR_USER_COMMAND_SUPPORT
DECL|macro|SCSI_NCR_USER_INFO_SUPPORT
macro_line|#&t;define&t;SCSI_NCR_USER_INFO_SUPPORT
multiline_comment|/* #&t;define&t;SCSI_NCR_DEBUG_ERROR_RECOVERY_SUPPORT */
macro_line|#endif
multiline_comment|/*==========================================================&n;**&n;** nvram settings - #define SCSI_NCR_NVRAM_SUPPORT to enable&n;**&n;**==========================================================&n;*/
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX_NVRAM_DETECT
DECL|macro|SCSI_NCR_NVRAM_SUPPORT
mdefine_line|#define SCSI_NCR_NVRAM_SUPPORT
multiline_comment|/* #define SCSI_NCR_DEBUG_NVRAM */
macro_line|#endif
multiline_comment|/* ---------------------------------------------------------------------&n;** Take into account kernel configured parameters.&n;** Most of these options can be overridden at startup by a command line.&n;** ---------------------------------------------------------------------&n;*/
multiline_comment|/*&n; * For Ultra2 SCSI support option, use special features and allow 40Mhz &n; * synchronous data transfers.&n; */
DECL|macro|SCSI_NCR_SETUP_SPECIAL_FEATURES
mdefine_line|#define&t;SCSI_NCR_SETUP_SPECIAL_FEATURES&t;&t;(3)
DECL|macro|SCSI_NCR_SETUP_ULTRA_SCSI
mdefine_line|#define SCSI_NCR_SETUP_ULTRA_SCSI&t;&t;(2)
DECL|macro|SCSI_NCR_MAX_SYNC
mdefine_line|#define SCSI_NCR_MAX_SYNC&t;&t;&t;(40)
multiline_comment|/*&n; * Allow tags from 2 to 12, default 4&n; */
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
multiline_comment|/*&n; * Allow tagged command queuing support if configured with default number &n; * of tags set to max (see above).&n; */
macro_line|#ifdef&t;CONFIG_SCSI_NCR53C8XX_TAGGED_QUEUE
DECL|macro|SCSI_NCR_SETUP_DEFAULT_TAGS
mdefine_line|#define&t;SCSI_NCR_SETUP_DEFAULT_TAGS&t;SCSI_NCR_MAX_TAGS
macro_line|#else
DECL|macro|SCSI_NCR_SETUP_DEFAULT_TAGS
mdefine_line|#define&t;SCSI_NCR_SETUP_DEFAULT_TAGS&t;(0)
macro_line|#endif
multiline_comment|/*&n; * Use normal IO if configured. Forced for alpha and ppc.&n; */
macro_line|#if defined(CONFIG_SCSI_NCR53C8XX_IOMAPPED)
DECL|macro|SCSI_NCR_IOMAPPED
mdefine_line|#define&t;SCSI_NCR_IOMAPPED
macro_line|#elif defined(__alpha__) || defined(__powerpc__)
DECL|macro|SCSI_NCR_IOMAPPED
mdefine_line|#define&t;SCSI_NCR_IOMAPPED
macro_line|#elif defined(__sparc__)
DECL|macro|SCSI_NCR_IOMAPPED
macro_line|#undef SCSI_NCR_IOMAPPED
macro_line|#endif
multiline_comment|/*&n; * Sync transfer frequency at startup.&n; * Allow from 5Mhz to 40Mhz default 10 Mhz.&n; */
macro_line|#ifndef&t;CONFIG_SCSI_NCR53C8XX_SYNC
DECL|macro|CONFIG_SCSI_NCR53C8XX_SYNC
mdefine_line|#define&t;CONFIG_SCSI_NCR53C8XX_SYNC&t;(5)
macro_line|#elif&t;CONFIG_SCSI_NCR53C8XX_SYNC &gt; SCSI_NCR_MAX_SYNC
DECL|macro|SCSI_NCR_SETUP_DEFAULT_SYNC
mdefine_line|#define&t;SCSI_NCR_SETUP_DEFAULT_SYNC&t;SCSI_NCR_MAX_SYNC
macro_line|#endif
macro_line|#if&t;CONFIG_SCSI_NCR53C8XX_SYNC == 0
DECL|macro|SCSI_NCR_SETUP_DEFAULT_SYNC
mdefine_line|#define&t;SCSI_NCR_SETUP_DEFAULT_SYNC&t;(255)
macro_line|#elif&t;CONFIG_SCSI_NCR53C8XX_SYNC &lt;= 5
DECL|macro|SCSI_NCR_SETUP_DEFAULT_SYNC
mdefine_line|#define&t;SCSI_NCR_SETUP_DEFAULT_SYNC&t;(50)
macro_line|#elif&t;CONFIG_SCSI_NCR53C8XX_SYNC &lt;= 20
DECL|macro|SCSI_NCR_SETUP_DEFAULT_SYNC
mdefine_line|#define&t;SCSI_NCR_SETUP_DEFAULT_SYNC&t;(250/(CONFIG_SCSI_NCR53C8XX_SYNC))
macro_line|#elif&t;CONFIG_SCSI_NCR53C8XX_SYNC &lt;= 33
DECL|macro|SCSI_NCR_SETUP_DEFAULT_SYNC
mdefine_line|#define&t;SCSI_NCR_SETUP_DEFAULT_SYNC&t;(11)
macro_line|#else
DECL|macro|SCSI_NCR_SETUP_DEFAULT_SYNC
mdefine_line|#define&t;SCSI_NCR_SETUP_DEFAULT_SYNC&t;(10)
macro_line|#endif
multiline_comment|/*&n; * Disallow disconnections at boot-up&n; */
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX_NO_DISCONNECT
DECL|macro|SCSI_NCR_SETUP_DISCONNECTION
mdefine_line|#define SCSI_NCR_SETUP_DISCONNECTION&t;(0)
macro_line|#else
DECL|macro|SCSI_NCR_SETUP_DISCONNECTION
mdefine_line|#define SCSI_NCR_SETUP_DISCONNECTION&t;(1)
macro_line|#endif
multiline_comment|/*&n; * Force synchronous negotiation for all targets&n; */
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX_FORCE_SYNC_NEGO
DECL|macro|SCSI_NCR_SETUP_FORCE_SYNC_NEGO
mdefine_line|#define SCSI_NCR_SETUP_FORCE_SYNC_NEGO&t;(1)
macro_line|#else
DECL|macro|SCSI_NCR_SETUP_FORCE_SYNC_NEGO
mdefine_line|#define SCSI_NCR_SETUP_FORCE_SYNC_NEGO&t;(0)
macro_line|#endif
multiline_comment|/*&n; * Disable master parity checking (flawed hardwares need that)&n; */
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX_DISABLE_MPARITY_CHECK
DECL|macro|SCSI_NCR_SETUP_MASTER_PARITY
mdefine_line|#define SCSI_NCR_SETUP_MASTER_PARITY&t;(0)
macro_line|#else
DECL|macro|SCSI_NCR_SETUP_MASTER_PARITY
mdefine_line|#define SCSI_NCR_SETUP_MASTER_PARITY&t;(1)
macro_line|#endif
multiline_comment|/*&n; * Disable scsi parity checking (flawed devices may need that)&n; */
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX_DISABLE_PARITY_CHECK
DECL|macro|SCSI_NCR_SETUP_SCSI_PARITY
mdefine_line|#define SCSI_NCR_SETUP_SCSI_PARITY&t;(0)
macro_line|#else
DECL|macro|SCSI_NCR_SETUP_SCSI_PARITY
mdefine_line|#define SCSI_NCR_SETUP_SCSI_PARITY&t;(1)
macro_line|#endif
multiline_comment|/*&n; * Vendor specific stuff&n; */
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX_SYMBIOS_COMPAT
DECL|macro|SCSI_NCR_SETUP_LED_PIN
mdefine_line|#define SCSI_NCR_SETUP_LED_PIN&t;&t;(1)
DECL|macro|SCSI_NCR_SETUP_DIFF_SUPPORT
mdefine_line|#define SCSI_NCR_SETUP_DIFF_SUPPORT&t;(3)
macro_line|#else
DECL|macro|SCSI_NCR_SETUP_LED_PIN
mdefine_line|#define SCSI_NCR_SETUP_LED_PIN&t;&t;(0)
DECL|macro|SCSI_NCR_SETUP_DIFF_SUPPORT
mdefine_line|#define SCSI_NCR_SETUP_DIFF_SUPPORT&t;(0)
macro_line|#endif
multiline_comment|/*&n; * Settle time after reset at boot-up&n; */
DECL|macro|SCSI_NCR_SETUP_SETTLE_TIME
mdefine_line|#define SCSI_NCR_SETUP_SETTLE_TIME&t;(2)
multiline_comment|/*&n;**&t;Other parameters not configurable with &quot;make config&quot;&n;**&t;Avoid to change these constants, unless you know what you are doing.&n;*/
DECL|macro|SCSI_NCR_ALWAYS_SIMPLE_TAG
mdefine_line|#define SCSI_NCR_ALWAYS_SIMPLE_TAG
DECL|macro|SCSI_NCR_MAX_SCATTER
mdefine_line|#define SCSI_NCR_MAX_SCATTER&t;(127)
DECL|macro|SCSI_NCR_MAX_TARGET
mdefine_line|#define SCSI_NCR_MAX_TARGET&t;(16)
DECL|macro|SCSI_NCR_MAX_HOST
mdefine_line|#define SCSI_NCR_MAX_HOST&t;(2)
DECL|macro|SCSI_NCR_TIMEOUT_ALERT
mdefine_line|#define SCSI_NCR_TIMEOUT_ALERT&t;(3*HZ)
DECL|macro|SCSI_NCR_CAN_QUEUE
mdefine_line|#define SCSI_NCR_CAN_QUEUE&t;(7*SCSI_NCR_MAX_TAGS)
DECL|macro|SCSI_NCR_CMD_PER_LUN
mdefine_line|#define SCSI_NCR_CMD_PER_LUN&t;(SCSI_NCR_MAX_TAGS)
DECL|macro|SCSI_NCR_SG_TABLESIZE
mdefine_line|#define SCSI_NCR_SG_TABLESIZE&t;(SCSI_NCR_MAX_SCATTER)
DECL|macro|SCSI_NCR_TIMER_INTERVAL
mdefine_line|#define SCSI_NCR_TIMER_INTERVAL&t;((HZ+5-1)/5)
macro_line|#if 1 /* defined CONFIG_SCSI_MULTI_LUN */
DECL|macro|SCSI_NCR_MAX_LUN
mdefine_line|#define SCSI_NCR_MAX_LUN&t;(8)
macro_line|#else
DECL|macro|SCSI_NCR_MAX_LUN
mdefine_line|#define SCSI_NCR_MAX_LUN&t;(1)
macro_line|#endif
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
macro_line|#if&t;LINUX_VERSION_CODE &gt;= LinuxVersionCode(2,1,75)
DECL|macro|NCR53C8XX
mdefine_line|#define NCR53C8XX {     name:           SCSI_NCR_DRIVER_NAME,&t;&bslash;&n;&t;&t;&t;detect:         ncr53c8xx_detect,&t;&bslash;&n;&t;&t;&t;release:        ncr53c8xx_release,&t;&bslash;&n;&t;&t;&t;queuecommand:   ncr53c8xx_queue_command,&bslash;&n;&t;&t;&t;abort:          ncr53c8xx_abort,&t;&bslash;&n;&t;&t;&t;reset:          ncr53c8xx_reset,&t;&bslash;&n;&t;&t;&t;bios_param:     scsicam_bios_param,&t;&bslash;&n;&t;&t;&t;can_queue:      SCSI_NCR_CAN_QUEUE,&t;&bslash;&n;&t;&t;&t;this_id:        7,&t;&t;&t;&bslash;&n;&t;&t;&t;sg_tablesize:   SCSI_NCR_SG_TABLESIZE,&t;&bslash;&n;&t;&t;&t;cmd_per_lun:    SCSI_NCR_CMD_PER_LUN,&t;&bslash;&n;&t;&t;&t;use_clustering: DISABLE_CLUSTERING} 
macro_line|#elif&t;LINUX_VERSION_CODE &gt;= LinuxVersionCode(1,3,0)
DECL|macro|NCR53C8XX
mdefine_line|#define NCR53C8XX {&t;NULL, NULL, NULL, NULL,&t;&t;&t;&t;&bslash;&n;&t;&t;&t;SCSI_NCR_DRIVER_NAME,&t;ncr53c8xx_detect,&t;&bslash;&n;    &t;&t;&t;ncr53c8xx_release,&t;NULL,&t;NULL,&t;&t;&bslash;&n;&t;&t;&t;ncr53c8xx_queue_command,ncr53c8xx_abort,&t;&bslash;&n;&t;&t;&t;ncr53c8xx_reset, NULL,&t;scsicam_bios_param,&t;&bslash;&n;&t;&t;&t;SCSI_NCR_CAN_QUEUE,&t;7,&t;&t;&t;&bslash;&n;&t;&t;&t;SCSI_NCR_SG_TABLESIZE,&t;SCSI_NCR_CMD_PER_LUN,&t;&bslash;&n;&t;&t;&t;0,&t;0,&t;DISABLE_CLUSTERING} 
macro_line|#else
DECL|macro|NCR53C8XX
mdefine_line|#define NCR53C8XX {&t;NULL, NULL,&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;SCSI_NCR_DRIVER_NAME,&t;ncr53c8xx_detect,&t;&bslash;&n;&t;&t;&t;ncr53c8xx_release,&t;NULL, &t;NULL, &t;&t;&bslash;&n;&t;&t;&t;ncr53c8xx_queue_command,ncr53c8xx_abort,&t;&bslash;&n;&t;&t;&t;ncr53c8xx_reset, NULL,&t;scsicam_bios_param,&t;&bslash;&n;&t;&t;&t;SCSI_NCR_CAN_QUEUE,&t;7,&t;&t;&t;&bslash;&n;&t;&t;&t;SCSI_NCR_SG_TABLESIZE,&t;SCSI_NCR_CMD_PER_LUN,&t;&bslash;&n;&t;&t;&t;0,&t;0,&t;DISABLE_CLUSTERING} 
macro_line|#endif /* LINUX_VERSION_CODE */
macro_line|#endif /* defined(HOSTS_C) || defined(MODULE) */ 
macro_line|#ifndef HOSTS_C
multiline_comment|/*&n;**&t;IO functions definition for big/little endian support.&n;**&t;For now, the NCR is only supported in little endian addressing mode, &n;**&t;and big endian byte ordering is only supported for the PPC.&n;**&t;MMIO is not used on PPC.&n;*/
macro_line|#ifdef&t;__BIG_ENDIAN
macro_line|#if&t;LINUX_VERSION_CODE &lt; LinuxVersionCode(2,1,0)
macro_line|#error&t;&quot;BIG ENDIAN byte ordering needs kernel version &gt;= 2.1.0&quot;
macro_line|#endif
macro_line|#if defined(__powerpc__)
DECL|macro|inw_l2b
mdefine_line|#define&t;inw_l2b&t;&t;inw
DECL|macro|inl_l2b
mdefine_line|#define&t;inl_l2b&t;&t;inl
DECL|macro|outw_b2l
mdefine_line|#define&t;outw_b2l&t;outw
DECL|macro|outl_b2l
mdefine_line|#define&t;outl_b2l&t;outl
macro_line|#elif defined(__sparc__)
DECL|macro|readw_l2b
mdefine_line|#define&t;readw_l2b&t;readw
DECL|macro|readl_l2b
mdefine_line|#define&t;readl_l2b&t;readl
DECL|macro|writew_b2l
mdefine_line|#define&t;writew_b2l&t;writew
DECL|macro|writel_b2l
mdefine_line|#define&t;writel_b2l&t;writel
macro_line|#else
macro_line|#error&t;&quot;Support for BIG ENDIAN is only available for PowerPC and SPARC&quot;
macro_line|#endif
macro_line|#else&t;/* Assumed x86 or alpha */
DECL|macro|inw_raw
mdefine_line|#define&t;inw_raw&t;&t;inw
DECL|macro|inl_raw
mdefine_line|#define&t;inl_raw&t;&t;inl
DECL|macro|outw_raw
mdefine_line|#define&t;outw_raw&t;outw
DECL|macro|outl_raw
mdefine_line|#define&t;outl_raw&t;outl
DECL|macro|readw_raw
mdefine_line|#define&t;readw_raw&t;readw
DECL|macro|readl_raw
mdefine_line|#define&t;readl_raw&t;readl
DECL|macro|writew_raw
mdefine_line|#define&t;writew_raw&t;writew
DECL|macro|writel_raw
mdefine_line|#define&t;writel_raw&t;writel
macro_line|#endif
macro_line|#ifdef&t;SCSI_NCR_BIG_ENDIAN
macro_line|#error&t;&quot;The NCR in BIG ENDIAN adressing mode is not (yet) supported&quot;
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
macro_line|#ifndef PCI_DEVICE_ID_NCR_53C875J
DECL|macro|PCI_DEVICE_ID_NCR_53C875J
mdefine_line|#define PCI_DEVICE_ID_NCR_53C875J 0x8f
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
multiline_comment|/*&n;**   NCR53C8XX devices features table.&n;*/
r_typedef
r_struct
(brace
DECL|member|device_id
r_int
r_int
id|device_id
suffix:semicolon
DECL|member|revision_id
r_int
r_int
id|revision_id
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|burst_max
r_int
r_char
id|burst_max
suffix:semicolon
DECL|member|offset_max
r_int
r_char
id|offset_max
suffix:semicolon
DECL|member|nr_divisor
r_int
r_char
id|nr_divisor
suffix:semicolon
DECL|member|features
r_int
r_int
id|features
suffix:semicolon
DECL|macro|FE_LED0
mdefine_line|#define FE_LED0&t;&t;(1&lt;&lt;0)
DECL|macro|FE_WIDE
mdefine_line|#define FE_WIDE&t;&t;(1&lt;&lt;1)
DECL|macro|FE_ULTRA
mdefine_line|#define FE_ULTRA&t;(1&lt;&lt;2)
DECL|macro|FE_ULTRA2
mdefine_line|#define FE_ULTRA2&t;(1&lt;&lt;3)
DECL|macro|FE_DBLR
mdefine_line|#define FE_DBLR&t;&t;(1&lt;&lt;4)
DECL|macro|FE_QUAD
mdefine_line|#define FE_QUAD&t;&t;(1&lt;&lt;5)
DECL|macro|FE_ERL
mdefine_line|#define FE_ERL&t;&t;(1&lt;&lt;6)
DECL|macro|FE_CLSE
mdefine_line|#define FE_CLSE&t;&t;(1&lt;&lt;7)
DECL|macro|FE_WRIE
mdefine_line|#define FE_WRIE&t;&t;(1&lt;&lt;8)
DECL|macro|FE_ERMP
mdefine_line|#define FE_ERMP&t;&t;(1&lt;&lt;9)
DECL|macro|FE_BOF
mdefine_line|#define FE_BOF&t;&t;(1&lt;&lt;10)
DECL|macro|FE_DFS
mdefine_line|#define FE_DFS&t;&t;(1&lt;&lt;11)
DECL|macro|FE_PFEN
mdefine_line|#define FE_PFEN&t;&t;(1&lt;&lt;12)
DECL|macro|FE_LDSTR
mdefine_line|#define FE_LDSTR&t;(1&lt;&lt;13)
DECL|macro|FE_RAM
mdefine_line|#define FE_RAM&t;&t;(1&lt;&lt;14)
DECL|macro|FE_CLK80
mdefine_line|#define FE_CLK80&t;(1&lt;&lt;15)
DECL|macro|FE_CACHE_SET
mdefine_line|#define FE_CACHE_SET&t;(FE_ERL|FE_CLSE|FE_WRIE|FE_ERMP)
DECL|macro|FE_SCSI_SET
mdefine_line|#define FE_SCSI_SET&t;(FE_WIDE|FE_ULTRA|FE_ULTRA2|FE_DBLR|FE_QUAD|F_CLK80)
DECL|macro|FE_SPECIAL_SET
mdefine_line|#define FE_SPECIAL_SET&t;(FE_CACHE_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|FE_RAM)
DECL|typedef|ncr_chip
)brace
id|ncr_chip
suffix:semicolon
multiline_comment|/*&n;**&t;DEL 397 - 53C875 Rev 3 - Part Number 609-0392410 - ITEM 3.&n;**&t;Memory Read transaction terminated by a retry followed by &n;**&t;Memory Read Line command.&n;*/
DECL|macro|FE_CACHE0_SET
mdefine_line|#define FE_CACHE0_SET&t;(FE_CACHE_SET &amp; ~FE_ERL)
multiline_comment|/*&n;**&t;DEL 397 - 53C875 Rev 3 - Part Number 609-0392410 - ITEM 5.&n;**&t;On paper, this errata is harmless. But it is a good reason for &n;**&t;using a shorter programmed burst length (64 DWORDS instead of 128).&n;*/
DECL|macro|SCSI_NCR_CHIP_TABLE
mdefine_line|#define SCSI_NCR_CHIP_TABLE&t;&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C810, 0x0f, &quot;810&quot;,  4,  8, 4,&t;&t;&t;&bslash;&n; FE_ERL}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C810, 0xff, &quot;810a&quot;, 4,  8, 4,&t;&t;&t;&bslash;&n; FE_CACHE_SET|FE_LDSTR|FE_PFEN|FE_BOF}&t;&t;&t;&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C815, 0xff, &quot;815&quot;,  4,  8, 4,&t;&t;&t;&bslash;&n; FE_ERL|FE_BOF}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C820, 0xff, &quot;820&quot;,  4,  8, 4,&t;&t;&t;&bslash;&n; FE_WIDE|FE_ERL}&t;&t;&t;&t;&t;&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C825, 0x0f, &quot;825&quot;,  4,  8, 4,&t;&t;&t;&bslash;&n; FE_WIDE|FE_ERL|FE_BOF}&t;&t;&t;&t;&t;&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C825, 0xff, &quot;825a&quot;, 6,  8, 4,&t;&t;&t;&bslash;&n; FE_WIDE|FE_CACHE0_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|FE_RAM}&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C860, 0xff, &quot;860&quot;,  4,  8, 5,&t;&t;&t;&bslash;&n; FE_ULTRA|FE_CLK80|FE_CACHE_SET|FE_BOF|FE_LDSTR|FE_PFEN}&t;&t;&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C875, 0x01, &quot;875&quot;,  6, 16, 5,&t;&t;&t;&bslash;&n; FE_WIDE|FE_ULTRA|FE_CLK80|FE_CACHE0_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|FE_RAM}&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C875, 0xff, &quot;875&quot;,  6, 16, 5,&t;&t;&t;&bslash;&n; FE_WIDE|FE_ULTRA|FE_DBLR|FE_CACHE0_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|FE_RAM}&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C875J,0xff, &quot;875J&quot;, 6, 16, 5,&t;&t;&t;&bslash;&n; FE_WIDE|FE_ULTRA|FE_DBLR|FE_CACHE0_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|FE_RAM}&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C885, 0xff, &quot;885&quot;,  6, 16, 5,&t;&t;&t;&bslash;&n; FE_WIDE|FE_ULTRA|FE_DBLR|FE_CACHE0_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|FE_RAM}&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C895, 0xff, &quot;895&quot;,  7, 31, 7,&t;&t;&t;&bslash;&n; FE_WIDE|FE_ULTRA2|FE_QUAD|FE_CACHE_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|FE_RAM}&bslash;&n; ,&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n; {PCI_DEVICE_ID_NCR_53C896, 0xff, &quot;896&quot;,  7, 31, 7,&t;&t;&t;&bslash;&n; FE_WIDE|FE_ULTRA2|FE_QUAD|FE_CACHE_SET|FE_BOF|FE_DFS|FE_LDSTR|FE_PFEN|FE_RAM}&bslash;&n;}
multiline_comment|/*&n; * List of supported NCR chip ids&n; */
DECL|macro|SCSI_NCR_CHIP_IDS
mdefine_line|#define SCSI_NCR_CHIP_IDS&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C810,&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C815,&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C820,&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C825,&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C860,&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C875,&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C875J,&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C885,&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C895,&t;&bslash;&n;&t;PCI_DEVICE_ID_NCR_53C896&t;&bslash;&n;}
multiline_comment|/*&n;**&t;Initial setup.&n;**&t;Can be overriden at startup by a command line.&n;*/
DECL|macro|SCSI_NCR_DRIVER_SETUP
mdefine_line|#define SCSI_NCR_DRIVER_SETUP&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;SCSI_NCR_SETUP_MASTER_PARITY,&t;&t;&bslash;&n;&t;SCSI_NCR_SETUP_SCSI_PARITY,&t;&t;&bslash;&n;&t;SCSI_NCR_SETUP_DISCONNECTION,&t;&t;&bslash;&n;&t;SCSI_NCR_SETUP_SPECIAL_FEATURES,&t;&bslash;&n;&t;SCSI_NCR_SETUP_ULTRA_SCSI,&t;&t;&bslash;&n;&t;SCSI_NCR_SETUP_FORCE_SYNC_NEGO,&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;1,&t;&t;&t;&t;&t;&bslash;&n;&t;1,&t;&t;&t;&t;&t;&bslash;&n;&t;SCSI_NCR_SETUP_DEFAULT_TAGS,&t;&t;&bslash;&n;&t;SCSI_NCR_SETUP_DEFAULT_SYNC,&t;&t;&bslash;&n;&t;0x00,&t;&t;&t;&t;&t;&bslash;&n;&t;7,&t;&t;&t;&t;&t;&bslash;&n;&t;SCSI_NCR_SETUP_LED_PIN,&t;&t;&t;&bslash;&n;&t;1,&t;&t;&t;&t;&t;&bslash;&n;&t;SCSI_NCR_SETUP_SETTLE_TIME,&t;&t;&bslash;&n;&t;SCSI_NCR_SETUP_DIFF_SUPPORT,&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;1&t;&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n;**&t;Boot fail safe setup.&n;**&t;Override initial setup from boot command line:&n;**&t;ncr53c8xx=safe:y&n;*/
DECL|macro|SCSI_NCR_DRIVER_SAFE_SETUP
mdefine_line|#define SCSI_NCR_DRIVER_SAFE_SETUP&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;1,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;1,&t;&t;&t;&t;&t;&bslash;&n;&t;2,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;255,&t;&t;&t;&t;&t;&bslash;&n;&t;0x00,&t;&t;&t;&t;&t;&bslash;&n;&t;255,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;0,&t;&t;&t;&t;&t;&bslash;&n;&t;10,&t;&t;&t;&t;&t;&bslash;&n;&t;1,&t;&t;&t;&t;&t;&bslash;&n;&t;1,&t;&t;&t;&t;&t;&bslash;&n;&t;1&t;&t;&t;&t;&t;&bslash;&n;}
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
DECL|macro|ULTRA
mdefine_line|#define   ULTRA   0x80  /* cmd: ULTRA enable                */
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
DECL|macro|DM
mdefine_line|#define   DM      0x04  /* sta: DIFFSENS mismatch (895/6 only) */
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
DECL|macro|FLF
mdefine_line|#define   FLF     0x08  /* cmd: flush dma fifo              */
DECL|macro|CLF
mdefine_line|#define   CLF&t;  0x04&t;/* cmd: clear dma fifo&t;&t;    */
DECL|macro|FM
mdefine_line|#define   FM      0x02  /* mod: fetch pin mode              */
DECL|macro|WRIE
mdefine_line|#define   WRIE    0x01  /* mod: write and invalidate enable */
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
DECL|macro|BDIS
mdefine_line|#define   BDIS    0x80  /* mod: burst disable               */
DECL|macro|MPEE
mdefine_line|#define   MPEE    0x08  /* mod: master parity error enable  */
DECL|member|nc_ctest5
multiline_comment|/*22*/
id|u_char
id|nc_ctest5
suffix:semicolon
DECL|macro|DFS
mdefine_line|#define   DFS     0x20  /* mod: dma fifo size               */
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
DECL|macro|BL_2
mdefine_line|#define   BL_2    0x80  /* mod: burst length shift value +2 */
DECL|macro|BL_1
mdefine_line|#define   BL_1    0x40  /* mod: burst length shift value +1 */
DECL|macro|ERL
mdefine_line|#define   ERL     0x08  /* mod: enable read line            */
DECL|macro|ERMP
mdefine_line|#define   ERMP    0x04  /* mod: enable read multiple        */
DECL|macro|BOF
mdefine_line|#define   BOF     0x02  /* mod: burst op code fetch         */
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
DECL|macro|CLSE
mdefine_line|#define   CLSE    0x80  /* mod: cache line size enable      */
DECL|macro|PFF
mdefine_line|#define   PFF     0x40  /* cmd: pre-fetch flush             */
DECL|macro|PFEN
mdefine_line|#define   PFEN    0x20  /* mod: pre-fetch enable            */
DECL|macro|SSM
mdefine_line|#define   SSM     0x10  /* mod: single step mode            */
DECL|macro|IRQM
mdefine_line|#define   IRQM    0x08  /* mod: irq mode (1 = totem pole !) */
DECL|macro|STD
mdefine_line|#define   STD     0x04  /* cmd: start dma mode              */
DECL|macro|IRQD
mdefine_line|#define   IRQD    0x02  /* mod: irq disable                 */
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
DECL|macro|SBMC
mdefine_line|#define   SBMC    0x1000/* sta: SCSI Bus Mode Change (895/6 only) */
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
DECL|macro|HSC
mdefine_line|#define   HSC    0x20&t;/* c: Halt SCSI Clock */
DECL|macro|CSF
mdefine_line|#define   CSF    0x02&t;/* c: clear scsi fifo */
DECL|member|nc_sidl
multiline_comment|/*50*/
id|u_short
id|nc_sidl
suffix:semicolon
multiline_comment|/* Lowlevel: latched from scsi data */
DECL|member|nc_stest4
multiline_comment|/*52*/
id|u_char
id|nc_stest4
suffix:semicolon
DECL|macro|SMODE
mdefine_line|#define   SMODE  0xc0&t;/* SCSI bus mode      (895/6 only) */
DECL|macro|SMODE_HVD
mdefine_line|#define    SMODE_HVD 0x40&t;/* High Voltage Differential       */
DECL|macro|SMODE_SE
mdefine_line|#define    SMODE_SE  0x80&t;/* Single Ended                    */
DECL|macro|SMODE_LVD
mdefine_line|#define    SMODE_LVD 0xc0&t;/* Low Voltage Differential        */
DECL|macro|LCKFRQ
mdefine_line|#define   LCKFRQ 0x20&t;/* Frequency Lock (895/6 only)     */
DECL|member|nc_53_
multiline_comment|/*53*/
id|u_char
id|nc_53_
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
multiline_comment|/*-----------------------------------------------------------&n;**&n;**&t;Memory to memory move&n;**&n;**-----------------------------------------------------------&n;**&n;**&t;COPY (bytecount)&n;**&t;&lt;&lt; source_address &gt;&gt;&n;**&t;&lt;&lt; destination_address &gt;&gt;&n;**&n;**&t;SCR_COPY   sets the NO FLUSH option by default.&n;**&t;SCR_COPY_F does not set this option.&n;**&n;**&t;For chips which do not support this option,&n;**&t;ncr_copy_and_bind() will remove this bit.&n;**-----------------------------------------------------------&n;*/
DECL|macro|SCR_NO_FLUSH
mdefine_line|#define SCR_NO_FLUSH 0x01000000
DECL|macro|SCR_COPY
mdefine_line|#define SCR_COPY(n) (0xc0000000 | SCR_NO_FLUSH | (n))
DECL|macro|SCR_COPY_F
mdefine_line|#define SCR_COPY_F(n) (0xc0000000 | (n))
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
DECL|macro|SCR_NO_OP
mdefine_line|#define SCR_NO_OP        0x80000000
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
