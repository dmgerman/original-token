multiline_comment|/*&n; *  hosts.c Copyright (C) 1992 Drew Eckhardt&n; *          Copyright (C) 1993, 1994, 1995 Eric Youngdale&n; *&n; *  mid to lowlevel SCSI driver interface&n; *      Initial versions: Drew Eckhardt&n; *      Subsequent revisions: Eric Youngdale&n; *&n; *  &lt;drew@colorado.edu&gt;&n; *&n; *  Jiffies wrap fixes (host-&gt;resetting), 3 Dec 1998 Andrea Arcangeli&n; *  Added QLOGIC QLA1280 SCSI controller kernel host support. &n; *     August 4, 1999 Fred Lewis, Intel DuPont&n; */
multiline_comment|/*&n; *  This file contains the medium level SCSI&n; *  host interface initialization, as well as the scsi_hosts array of SCSI&n; *  hosts currently present in the system.&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0L
macro_line|#endif
DECL|macro|HOSTS_C
mdefine_line|#define HOSTS_C
macro_line|#include &quot;hosts.h&quot;
macro_line|#if defined(CONFIG_A4000T_SCSI) || &bslash;&n;    defined(CONFIG_WARPENGINE_SCSI) || &bslash;&n;    defined(CONFIG_A4091_SCSI) || &bslash;&n;    defined (CONFIG_GVP_TURBO_SCSI) || &bslash;&n;    defined (CONFIG_BLZ603EPLUS_SCSI)
DECL|macro|AMIGA7XXCONFIG
mdefine_line|#define AMIGA7XXCONFIG
macro_line|#endif
macro_line|#ifdef AMIGA7XXCONFIG
macro_line|#include &quot;amiga7xx.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_MVME16x_SCSI
macro_line|#include &quot;mvme16x.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_BVME6000_SCSI
macro_line|#include &quot;bvme6000.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_SIM710
macro_line|#include &quot;sim710.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_A3000_SCSI
macro_line|#include &quot;a3000.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_A2091_SCSI
macro_line|#include &quot;a2091.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_GVP11_SCSI
macro_line|#include &quot;gvp11.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_CYBERSTORM_SCSI
macro_line|#include &quot;cyberstorm.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_CYBERSTORMII_SCSI
macro_line|#include &quot;cyberstormII.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_BLZ2060_SCSI
macro_line|#include &quot;blz2060.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_BLZ1230_SCSI
macro_line|#include &quot;blz1230.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_FASTLANE_SCSI
macro_line|#include &quot;fastlane.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_OKTAGON_SCSI
macro_line|#include &quot;oktagon_esp.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_ATARI_SCSI
macro_line|#include &quot;atari_scsi.h&quot;
macro_line|#endif
macro_line|#if defined(CONFIG_MAC_SCSI) || defined(CONFIG_MAC_SCSI_OLD)
macro_line|#include &quot;mac_scsi.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SUN3_SCSI
macro_line|#include &quot;sun3_scsi.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_MAC_ESP
macro_line|#include &quot;mac_esp.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_ADVANSYS
macro_line|#include &quot;advansys.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_AHA152X
macro_line|#include &quot;aha152x.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_AHA1542
macro_line|#include &quot;aha1542.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_AHA1740
macro_line|#include &quot;aha1740.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_AIC7XXX
macro_line|#include &quot;aic7xxx.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_IPS
macro_line|#include &quot;ips.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_BUSLOGIC
macro_line|#include &quot;BusLogic.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_EATA_DMA
macro_line|#include &quot;eata_dma.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_EATA_PIO
macro_line|#include &quot;eata_pio.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_U14_34F
macro_line|#include &quot;u14-34f.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_FD_MCS
macro_line|#include &quot;fd_mcs.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_FUTURE_DOMAIN
macro_line|#include &quot;fdomain.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_GENERIC_NCR5380
macro_line|#include &quot;g_NCR5380.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_IN2000
macro_line|#include &quot;in2000.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_PAS16
macro_line|#include &quot;pas16.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_QLOGIC_FAS
macro_line|#include &quot;qlogicfas.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_QLOGIC_ISP
macro_line|#include &quot;qlogicisp.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_QLOGIC_FC
macro_line|#include &quot;qlogicfc.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_QLOGIC_1280
macro_line|#include &quot;qla1280.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_SEAGATE
macro_line|#include &quot;seagate.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_T128
macro_line|#include &quot;t128.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_DMX3191D
macro_line|#include &quot;dmx3191d.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_DTC3280
macro_line|#include &quot;dtc.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_NCR53C7xx
macro_line|#include &quot;53c7,8xx.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_SYM53C8XX
macro_line|#include &quot;sym53c8xx.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX
macro_line|#include &quot;ncr53c8xx.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_ULTRASTOR
macro_line|#include &quot;ultrastor.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_7000FASST
macro_line|#include &quot;wd7000.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_MCA_53C9X
macro_line|#include &quot;mca_53c9x.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_IBMMCA
macro_line|#include &quot;ibmmca.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_EATA
macro_line|#include &quot;eata.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_NCR53C406A
macro_line|#include &quot;NCR53c406a.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_SYM53C416 
macro_line|#include &quot;sym53c416.h&quot; 
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_DC390T
macro_line|#include &quot;dc390.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_AM53C974
macro_line|#include &quot;AM53C974.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_MEGARAID
macro_line|#include &quot;megaraid.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_ACARD
macro_line|#include &quot;atp870u.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_SUNESP
macro_line|#include &quot;esp.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_QLOGICPTI
macro_line|#include &quot;qlogicpti.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_IDESCSI
macro_line|#include &quot;ide-scsi.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_MESH
macro_line|#include &quot;mesh.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_MAC53C94
macro_line|#include &quot;mac53c94.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_GDTH
macro_line|#include &quot;gdth.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_PCI2000
macro_line|#include &quot;pci2000.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_PCI2220I
macro_line|#include &quot;pci2220i.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_PSI240I
macro_line|#include &quot;psi240i.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_PLUTO
macro_line|#include &quot;pluto.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_INITIO
macro_line|#include &quot;ini9100u.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_INIA100
macro_line|#include &quot;inia100.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_DEBUG
macro_line|#include &quot;scsi_debug.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_ACORNSCSI_3
macro_line|#include &quot;../acorn/scsi/acornscsi.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_CUMANA_1
macro_line|#include &quot;../acorn/scsi/cumana_1.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_CUMANA_2
macro_line|#include &quot;../acorn/scsi/cumana_2.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_ECOSCSI
macro_line|#include &quot;../acorn/scsi/ecoscsi.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_OAK1
macro_line|#include &quot;../acorn/scsi/oak.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_POWERTECSCSI
macro_line|#include &quot;../acorn/scsi/powertec.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_ARXESCSI
macro_line|#include &quot;../acorn/scsi/arxescsi.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_I2O_SCSI
macro_line|#include &quot;../i2o/i2o_scsi.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_JAZZ_ESP
macro_line|#include &quot;jazz_esp.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_DECNCR
macro_line|#include &quot;dec_esp.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SUN3X_ESP
macro_line|#include &quot;sun3x_esp.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_IPHASE5526
macro_line|#include &quot;../net/fc/iph5526_scsi.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_3W_XXXX_RAID
macro_line|#include &quot;3w-xxxx.h&quot;
macro_line|#endif
multiline_comment|/*&n; * Moved ppa driver to the end of the probe list&n; * since it is a removable host adapter.&n; * This means the parallel ZIP drive will not bump&n; * the order of the /dev/sd devices - campbell@torque.net&n; */
macro_line|#ifdef CONFIG_SCSI_PPA
macro_line|#include &quot;ppa.h&quot;
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_IMM
macro_line|#include &quot;imm.h&quot;
macro_line|#endif
multiline_comment|/*&n;static const char RCSid[] = &quot;$Header: /vger/u4/cvs/linux/drivers/scsi/hosts.c,v 1.20 1996/12/12 19:18:32 davem Exp $&quot;;&n;*/
multiline_comment|/*&n; *  The scsi host entries should be in the order you wish the&n; *  cards to be detected.  A driver may appear more than once IFF&n; *  it can deal with being detected (and therefore initialized)&n; *  with more than one simultaneous host number, can handle being&n; *  reentrant, etc.&n; *&n; *  They may appear in any order, as each SCSI host is told which host &n; *  number it is during detection.&n; */
multiline_comment|/* This is a placeholder for controllers that are not configured into&n; * the system - we do this to ensure that the controller numbering is&n; * always consistent, no matter how the kernel is configured. */
DECL|macro|NO_CONTROLLER
mdefine_line|#define NO_CONTROLLER {NULL, NULL, NULL, NULL, NULL, NULL, NULL, &bslash;&n;&t;&t;&t;   NULL, NULL, 0, 0, 0, 0, 0, 0}
multiline_comment|/*&n; *  When figure is run, we don&squot;t want to link to any object code.  Since&n; *  the macro for each host will contain function pointers, we cannot&n; *  use it and instead must use a &quot;blank&quot; that does no such&n; *  idiocy.&n; */
DECL|variable|scsi_hosts
id|Scsi_Host_Template
op_star
id|scsi_hosts
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|builtin_scsi_hosts
r_static
id|Scsi_Host_Template
id|builtin_scsi_hosts
(braket
)braket
op_assign
(brace
macro_line|#ifdef CONFIG_AMIGA
macro_line|#ifdef AMIGA7XXCONFIG
id|AMIGA7XX_SCSI
comma
macro_line|#endif
macro_line|#ifdef CONFIG_A3000_SCSI
id|A3000_SCSI
comma
macro_line|#endif
macro_line|#ifdef CONFIG_A2091_SCSI
id|A2091_SCSI
comma
macro_line|#endif
macro_line|#ifdef CONFIG_GVP11_SCSI
id|GVP11_SCSI
comma
macro_line|#endif
macro_line|#ifdef CONFIG_CYBERSTORM_SCSI
id|SCSI_CYBERSTORM
comma
macro_line|#endif
macro_line|#ifdef CONFIG_CYBERSTORMII_SCSI
id|SCSI_CYBERSTORMII
comma
macro_line|#endif
macro_line|#ifdef CONFIG_BLZ2060_SCSI
id|SCSI_BLZ2060
comma
macro_line|#endif
macro_line|#ifdef CONFIG_BLZ1230_SCSI
id|SCSI_BLZ1230
comma
macro_line|#endif
macro_line|#ifdef CONFIG_FASTLANE_SCSI
id|SCSI_FASTLANE
comma
macro_line|#endif
macro_line|#ifdef CONFIG_OKTAGON_SCSI
id|SCSI_OKTAGON_ESP
comma
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_ATARI
macro_line|#ifdef CONFIG_ATARI_SCSI
id|ATARI_SCSI
comma
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_MAC
macro_line|#ifdef CONFIG_MAC_SCSI_OLD
id|MAC_SCSI
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_MAC_ESP
id|SCSI_MAC_ESP
comma
macro_line|#endif
macro_line|#ifdef CONFIG_MAC_SCSI
id|MAC_NCR5380
comma
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_SUN3_SCSI
id|SUN3_NCR5380
comma
macro_line|#endif
macro_line|#ifdef CONFIG_MVME16x_SCSI
id|MVME16x_SCSI
comma
macro_line|#endif
macro_line|#ifdef CONFIG_BVME6000_SCSI
id|BVME6000_SCSI
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_SIM710
id|SIM710_SCSI
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_ADVANSYS
id|ADVANSYS
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_PCI2000
id|PCI2000
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_PCI2220I
id|PCI2220I
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_PSI240I
id|PSI240I
comma
macro_line|#endif
multiline_comment|/* BusLogic must come before aha1542.c */
macro_line|#ifdef CONFIG_SCSI_BUSLOGIC
id|BUSLOGIC
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_U14_34F
id|ULTRASTOR_14_34F
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_ULTRASTOR
id|ULTRASTOR_14F
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_AHA152X
id|AHA152X
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_AHA1542
id|AHA1542
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_AHA1740
id|AHA1740
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_AIC7XXX
id|AIC7XXX
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_IPS
id|IPS
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_FD_MCS
id|FD_MCS
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_FUTURE_DOMAIN
id|FDOMAIN_16X0
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_IN2000
id|IN2000
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_GENERIC_NCR5380
id|GENERIC_NCR5380
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_NCR53C406A&t;/* 53C406A should come before QLOGIC */
id|NCR53c406a
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_SYM53C416 
id|SYM53C416
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_QLOGIC_FAS
id|QLOGICFAS
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_QLOGIC_ISP
id|QLOGICISP
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_QLOGIC_FC
id|QLOGICFC
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_QLOGIC_1280
id|QLA1280_LINUX_TEMPLATE
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_PAS16
id|MV_PAS16
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_SEAGATE
id|SEAGATE_ST0X
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_T128
id|TRANTOR_T128
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_DMX3191D
id|DMX3191D
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_DTC3280
id|DTC3x80
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_NCR53C7xx
id|NCR53c7xx
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_SYM53C8XX
id|SYM53C8XX
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_NCR53C8XX
id|NCR53C8XX
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_EATA_DMA
id|EATA_DMA
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_EATA_PIO
id|EATA_PIO
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_7000FASST
id|WD7000
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_MCA_53C9X
id|MCA_53C9X
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_IBMMCA
id|IBMMCA
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_EATA
id|EATA
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_DC390T
id|DC390_T
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_AM53C974
id|AM53C974
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_MEGARAID
id|MEGARAID
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_ACARD
id|ATP870U
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_SUNESP
id|SCSI_SPARC_ESP
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_GDTH
id|GDTH
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_INITIO
id|INI9100U
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_INIA100
id|INIA100
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_QLOGICPTI
id|QLOGICPTI
comma
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_IDESCSI
id|IDESCSI
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_MESH
id|SCSI_MESH
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_MAC53C94
id|SCSI_MAC53C94
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_PLUTO
id|PLUTO
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_ACORN
macro_line|#ifdef CONFIG_SCSI_ACORNSCSI_3
id|ACORNSCSI_3
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_CUMANA_1
id|CUMANA_NCR5380
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_CUMANA_2
id|CUMANA_FAS216
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_ARXESCSI
id|ARXEScsi
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_ECOSCSI
id|ECOSCSI_NCR5380
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_OAK1
id|OAK_NCR5380
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_POWERTECSCSI
id|POWERTECSCSI
comma
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_IPHASE5526
id|IPH5526_SCSI_FC
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_DECNCR&t;
id|SCSI_DEC_ESP
comma
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_3W_XXXX_RAID
id|TWXXXX
comma
macro_line|#endif
multiline_comment|/* Put I2O last so that host specific controllers always win */
macro_line|#ifdef CONFIG_I2O_SCSI
id|I2OSCSI
comma
macro_line|#endif
multiline_comment|/* &quot;Removable host adapters&quot; below this line (Parallel Port/USB/other) */
macro_line|#ifdef CONFIG_SCSI_PPA
id|PPA
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_IMM
id|IMM
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SUN3X_ESP  
id|SCSI_SUN3X_ESP
comma
macro_line|#endif  
macro_line|#ifdef CONFIG_SCSI_DEBUG
id|SCSI_DEBUG
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|MAX_SCSI_HOSTS
mdefine_line|#define MAX_SCSI_HOSTS (sizeof(builtin_scsi_hosts) / sizeof(Scsi_Host_Template))
multiline_comment|/*&n; *  Our semaphores and timeout counters, where size depends on &n; *      MAX_SCSI_HOSTS here.&n; */
DECL|variable|scsi_host_no_list
id|Scsi_Host_Name
op_star
id|scsi_host_no_list
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|scsi_hostlist
r_struct
id|Scsi_Host
op_star
id|scsi_hostlist
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|scsi_devicelist
r_struct
id|Scsi_Device_Template
op_star
id|scsi_devicelist
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|max_scsi_hosts
r_int
id|max_scsi_hosts
op_assign
l_int|0
suffix:semicolon
DECL|variable|next_scsi_host
r_int
id|next_scsi_host
op_assign
l_int|0
suffix:semicolon
r_void
DECL|function|scsi_unregister
(def_block
id|scsi_unregister
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|sh
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|shpnt
suffix:semicolon
id|Scsi_Host_Name
op_star
id|shn
suffix:semicolon
r_if
c_cond
(paren
id|scsi_hostlist
op_eq
id|sh
)paren
(brace
id|scsi_hostlist
op_assign
id|sh-&gt;next
suffix:semicolon
)brace
r_else
(brace
id|shpnt
op_assign
id|scsi_hostlist
suffix:semicolon
r_while
c_loop
(paren
id|shpnt-&gt;next
op_ne
id|sh
)paren
(brace
id|shpnt
op_assign
id|shpnt-&gt;next
suffix:semicolon
)brace
id|shpnt-&gt;next
op_assign
id|shpnt-&gt;next-&gt;next
suffix:semicolon
)brace
multiline_comment|/*&n;     * We have to unregister the host from the scsi_host_no_list as well.&n;     * Decide by the host_no not by the name because most host drivers are&n;     * able to handle more than one adapters from the same kind (or family).&n;     */
r_for
c_loop
(paren
id|shn
op_assign
id|scsi_host_no_list
suffix:semicolon
id|shn
op_logical_and
(paren
id|sh-&gt;host_no
op_ne
id|shn-&gt;host_no
)paren
suffix:semicolon
id|shn
op_assign
id|shn-&gt;next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|shn
)paren
id|shn-&gt;host_registered
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* else {} : This should not happen, we should panic here... */
multiline_comment|/* If we are removing the last host registered, it is safe to reuse&n;     * its host number (this avoids &quot;holes&quot; at boot time) (DB) &n;     * It is also safe to reuse those of numbers directly below which have&n;     * been released earlier (to avoid some holes in numbering).&n;     */
r_if
c_cond
(paren
id|sh-&gt;host_no
op_eq
id|max_scsi_hosts
op_minus
l_int|1
)paren
(brace
r_while
c_loop
(paren
op_decrement
id|max_scsi_hosts
op_ge
id|next_scsi_host
)paren
(brace
id|shpnt
op_assign
id|scsi_hostlist
suffix:semicolon
r_while
c_loop
(paren
id|shpnt
op_logical_and
id|shpnt-&gt;host_no
op_ne
id|max_scsi_hosts
op_minus
l_int|1
)paren
(brace
id|shpnt
op_assign
id|shpnt-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|shpnt
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
)brace
id|next_scsi_host
op_decrement
suffix:semicolon
id|kfree
c_func
(paren
(paren
r_char
op_star
)paren
id|sh
)paren
suffix:semicolon
)brace
)def_block
multiline_comment|/* We call this when we come across a new host adapter. We only do this&n; * once we are 100% sure that we want to use this host adapter -  it is a&n; * pain to reverse this, so we try to avoid it &n; */
DECL|function|scsi_register
r_struct
id|Scsi_Host
op_star
(def_block
id|scsi_register
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
comma
r_int
id|j
)paren
(brace
r_struct
id|Scsi_Host
op_star
id|retval
comma
op_star
id|shpnt
comma
op_star
id|o_shp
suffix:semicolon
id|Scsi_Host_Name
op_star
id|shn
comma
op_star
id|shn2
suffix:semicolon
r_int
id|flag_new
op_assign
l_int|1
suffix:semicolon
r_const
r_char
op_star
id|hname
suffix:semicolon
r_int
id|hname_len
suffix:semicolon
id|retval
op_assign
(paren
r_struct
id|Scsi_Host
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|Scsi_Host
)paren
op_plus
id|j
comma
(paren
id|tpnt-&gt;unchecked_isa_dma
op_logical_and
id|j
ques
c_cond
id|GFP_DMA
suffix:colon
l_int|0
)paren
op_or
id|GFP_ATOMIC
)paren
suffix:semicolon
id|memset
c_func
(paren
id|retval
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|Scsi_Host
)paren
op_plus
id|j
)paren
suffix:semicolon
multiline_comment|/* trying to find a reserved entry (host_no) */
id|hname
op_assign
(paren
id|tpnt-&gt;proc_name
)paren
ques
c_cond
id|tpnt-&gt;proc_name
suffix:colon
l_string|&quot;&quot;
suffix:semicolon
id|hname_len
op_assign
id|strlen
c_func
(paren
id|hname
)paren
suffix:semicolon
r_for
c_loop
(paren
id|shn
op_assign
id|scsi_host_no_list
suffix:semicolon
id|shn
suffix:semicolon
id|shn
op_assign
id|shn-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|shn-&gt;host_registered
)paren
op_logical_and
id|shn-&gt;loaded_as_module
op_logical_and
(paren
id|hname_len
OG
l_int|0
)paren
op_logical_and
(paren
l_int|0
op_eq
id|strncmp
c_func
(paren
id|hname
comma
id|shn-&gt;name
comma
id|hname_len
)paren
)paren
)paren
(brace
id|flag_new
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;host_no
op_assign
id|shn-&gt;host_no
suffix:semicolon
id|shn-&gt;host_registered
op_assign
l_int|1
suffix:semicolon
id|shn-&gt;loaded_as_module
op_assign
id|scsi_loadable_module_flag
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|atomic_set
c_func
(paren
op_amp
id|retval-&gt;host_active
comma
l_int|0
)paren
suffix:semicolon
id|retval-&gt;host_busy
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;host_failed
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|j
OG
l_int|0xffff
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Too many extra bytes requested&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|retval-&gt;extra_bytes
op_assign
id|j
suffix:semicolon
id|retval-&gt;loaded_as_module
op_assign
id|scsi_loadable_module_flag
suffix:semicolon
r_if
c_cond
(paren
id|flag_new
)paren
(brace
id|shn
op_assign
(paren
id|Scsi_Host_Name
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|Scsi_Host_Name
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|shn-&gt;name
op_assign
id|kmalloc
c_func
(paren
id|hname_len
op_plus
l_int|1
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hname_len
OG
l_int|0
)paren
id|strncpy
c_func
(paren
id|shn-&gt;name
comma
id|hname
comma
id|hname_len
)paren
suffix:semicolon
id|shn-&gt;name
(braket
id|hname_len
)braket
op_assign
l_int|0
suffix:semicolon
id|shn-&gt;host_no
op_assign
id|max_scsi_hosts
op_increment
suffix:semicolon
id|shn-&gt;host_registered
op_assign
l_int|1
suffix:semicolon
id|shn-&gt;loaded_as_module
op_assign
id|scsi_loadable_module_flag
suffix:semicolon
id|shn-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|scsi_host_no_list
)paren
(brace
r_for
c_loop
(paren
id|shn2
op_assign
id|scsi_host_no_list
suffix:semicolon
id|shn2-&gt;next
suffix:semicolon
id|shn2
op_assign
id|shn2-&gt;next
)paren
suffix:semicolon
id|shn2-&gt;next
op_assign
id|shn
suffix:semicolon
)brace
r_else
id|scsi_host_no_list
op_assign
id|shn
suffix:semicolon
id|retval-&gt;host_no
op_assign
id|shn-&gt;host_no
suffix:semicolon
)brace
id|next_scsi_host
op_increment
suffix:semicolon
id|retval-&gt;host_queue
op_assign
l_int|NULL
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|retval-&gt;host_wait
)paren
suffix:semicolon
id|retval-&gt;resetting
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;last_reset
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;irq
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;dma_channel
op_assign
l_int|0xff
suffix:semicolon
multiline_comment|/* These three are default values which can be overridden */
id|retval-&gt;max_channel
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;max_id
op_assign
l_int|8
suffix:semicolon
id|retval-&gt;max_lun
op_assign
l_int|8
suffix:semicolon
multiline_comment|/*&n;     * All drivers right now should be able to handle 12 byte commands.&n;     * Every so often there are requests for 16 byte commands, but individual&n;     * low-level drivers need to certify that they actually do something&n;     * sensible with such commands.&n;     */
id|retval-&gt;max_cmd_len
op_assign
l_int|12
suffix:semicolon
id|retval-&gt;unique_id
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;io_port
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;hostt
op_assign
id|tpnt
suffix:semicolon
id|retval-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|retval-&gt;in_recovery
op_assign
l_int|0
suffix:semicolon
id|retval-&gt;ehandler
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Initial value until the thing starts up. */
id|retval-&gt;eh_notify
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Who we notify when we exit. */
id|retval-&gt;host_blocked
op_assign
id|FALSE
suffix:semicolon
id|retval-&gt;host_self_blocked
op_assign
id|FALSE
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;Register %x %x: %d&bslash;n&quot;
comma
(paren
r_int
)paren
id|retval
comma
(paren
r_int
)paren
id|retval-&gt;hostt
comma
id|j
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* The next six are the default values which can be overridden&n;     * if need be */
id|retval-&gt;this_id
op_assign
id|tpnt-&gt;this_id
suffix:semicolon
id|retval-&gt;can_queue
op_assign
id|tpnt-&gt;can_queue
suffix:semicolon
id|retval-&gt;sg_tablesize
op_assign
id|tpnt-&gt;sg_tablesize
suffix:semicolon
id|retval-&gt;cmd_per_lun
op_assign
id|tpnt-&gt;cmd_per_lun
suffix:semicolon
id|retval-&gt;unchecked_isa_dma
op_assign
id|tpnt-&gt;unchecked_isa_dma
suffix:semicolon
id|retval-&gt;use_clustering
op_assign
id|tpnt-&gt;use_clustering
suffix:semicolon
id|retval-&gt;select_queue_depths
op_assign
id|tpnt-&gt;select_queue_depths
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scsi_hostlist
)paren
(brace
id|scsi_hostlist
op_assign
id|retval
suffix:semicolon
)brace
r_else
(brace
id|shpnt
op_assign
id|scsi_hostlist
suffix:semicolon
r_if
c_cond
(paren
id|retval-&gt;host_no
OL
id|shpnt-&gt;host_no
)paren
(brace
id|retval-&gt;next
op_assign
id|shpnt
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* want all to see these writes in this order */
id|scsi_hostlist
op_assign
id|retval
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|o_shp
op_assign
id|shpnt
comma
id|shpnt
op_assign
id|shpnt-&gt;next
suffix:semicolon
id|shpnt
suffix:semicolon
id|o_shp
op_assign
id|shpnt
comma
id|shpnt
op_assign
id|shpnt-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|retval-&gt;host_no
OL
id|shpnt-&gt;host_no
)paren
(brace
id|retval-&gt;next
op_assign
id|shpnt
suffix:semicolon
id|wmb
c_func
(paren
)paren
suffix:semicolon
id|o_shp-&gt;next
op_assign
id|retval
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|shpnt
)paren
id|o_shp-&gt;next
op_assign
id|retval
suffix:semicolon
)brace
)brace
r_return
id|retval
suffix:semicolon
)brace
)def_block
r_int
DECL|function|scsi_register_device
id|scsi_register_device
c_func
(paren
r_struct
id|Scsi_Device_Template
op_star
id|sdpnt
)paren
(brace
r_if
c_cond
(paren
id|sdpnt-&gt;next
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Device already registered&quot;
)paren
suffix:semicolon
)brace
id|sdpnt-&gt;next
op_assign
id|scsi_devicelist
suffix:semicolon
id|scsi_devicelist
op_assign
id|sdpnt
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Why is this a separate function?  Because the kernel_thread code&n; * effectively does a fork, and there is a builtin exit() call when&n; * the child returns.   The difficulty is that scsi_init() is&n; * marked __init, which means the memory is unmapped after bootup&n; * is complete, which means that the thread&squot;s exit() call gets wiped.&n; *&n; * The lesson is to *NEVER*, *NEVER* call kernel_thread() from an&n; * __init function, if that function could ever return.&n; */
DECL|function|launch_error_handler_thread
r_static
r_void
id|launch_error_handler_thread
c_func
(paren
r_struct
id|Scsi_Host
op_star
id|shpnt
)paren
(brace
id|DECLARE_MUTEX_LOCKED
c_func
(paren
id|sem
)paren
suffix:semicolon
id|shpnt-&gt;eh_notify
op_assign
op_amp
id|sem
suffix:semicolon
id|kernel_thread
c_func
(paren
(paren
r_int
(paren
op_star
)paren
(paren
r_void
op_star
)paren
)paren
id|scsi_error_handler
comma
(paren
r_void
op_star
)paren
id|shpnt
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;             * Now wait for the kernel error thread to initialize itself&n;             * as it might be needed when we scan the bus.&n;             */
id|down
(paren
op_amp
id|sem
)paren
suffix:semicolon
id|shpnt-&gt;eh_notify
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|scsi_init
r_int
r_int
id|__init
id|scsi_init
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|called
op_assign
l_int|0
suffix:semicolon
r_int
id|i
comma
id|pcount
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|Scsi_Host_Template
op_star
id|tpnt
suffix:semicolon
r_struct
id|Scsi_Host
op_star
id|shpnt
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
r_if
c_cond
(paren
id|called
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|called
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|tpnt
op_assign
op_amp
id|builtin_scsi_hosts
(braket
l_int|0
)braket
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_SCSI_HOSTS
suffix:semicolon
op_increment
id|i
comma
id|tpnt
op_increment
)paren
(brace
multiline_comment|/*&n;&t; * Initialize our semaphores.  -1 is interpreted to mean&n;&t; * &quot;inactive&quot; - where as 0 will indicate a time out condition.&n;&t; */
id|pcount
op_assign
id|next_scsi_host
suffix:semicolon
r_if
c_cond
(paren
id|tpnt-&gt;detect
)paren
(brace
multiline_comment|/* The detect routine must carefully spinunlock/spinlock if &n;              it enables interrupts, since all interrupt handlers do &n;              spinlock as well.&n;              All lame drivers are going to fail due to the following &n;              spinlock. For the time beeing let&squot;s use it only for drivers &n;              using the new scsi code. NOTE: the detect routine could&n;              redefine the value tpnt-&gt;use_new_eh_code. (DB, 13 May 1998) */
r_if
c_cond
(paren
id|tpnt-&gt;use_new_eh_code
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|io_request_lock
comma
id|flags
)paren
suffix:semicolon
id|tpnt-&gt;present
op_assign
id|tpnt
op_member_access_from_pointer
id|detect
c_func
(paren
id|tpnt
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|io_request_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
id|tpnt-&gt;present
op_assign
id|tpnt
op_member_access_from_pointer
id|detect
c_func
(paren
id|tpnt
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tpnt-&gt;detect
op_logical_and
id|tpnt-&gt;present
)paren
(brace
multiline_comment|/* The only time this should come up is when people use&n;&t;     * some kind of patched driver of some kind or another. */
r_if
c_cond
(paren
id|pcount
op_eq
id|next_scsi_host
)paren
(brace
r_if
c_cond
(paren
id|tpnt-&gt;present
OG
l_int|1
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Failure to register low-level scsi driver&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* The low-level driver failed to register a driver.  We&n;&t;&t; * can do this now. */
id|scsi_register
c_func
(paren
id|tpnt
comma
l_int|0
)paren
suffix:semicolon
)brace
id|tpnt-&gt;next
op_assign
id|scsi_hosts
suffix:semicolon
id|scsi_hosts
op_assign
id|tpnt
suffix:semicolon
multiline_comment|/* Add the driver to /proc/scsi */
macro_line|#if CONFIG_PROC_FS 
id|build_proc_dir_entries
c_func
(paren
id|tpnt
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
r_for
c_loop
(paren
id|shpnt
op_assign
id|scsi_hostlist
suffix:semicolon
id|shpnt
suffix:semicolon
id|shpnt
op_assign
id|shpnt-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|shpnt-&gt;hostt-&gt;info
)paren
(brace
id|name
op_assign
id|shpnt-&gt;hostt
op_member_access_from_pointer
id|info
c_func
(paren
id|shpnt
)paren
suffix:semicolon
)brace
r_else
id|name
op_assign
id|shpnt-&gt;hostt-&gt;name
suffix:semicolon
id|printk
(paren
l_string|&quot;scsi%d : %s&bslash;n&quot;
comma
multiline_comment|/* And print a little message */
id|shpnt-&gt;host_no
comma
id|name
)paren
suffix:semicolon
multiline_comment|/*&n;         * Now start the error recovery thread for the host.&n;         */
r_if
c_cond
(paren
id|shpnt-&gt;hostt-&gt;use_new_eh_code
)paren
(brace
id|launch_error_handler_thread
c_func
(paren
id|shpnt
)paren
suffix:semicolon
)brace
)brace
id|printk
(paren
l_string|&quot;scsi : %d host%s.&bslash;n&quot;
comma
id|next_scsi_host
comma
(paren
id|next_scsi_host
op_eq
l_int|1
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;s&quot;
)paren
suffix:semicolon
multiline_comment|/* Now attach the high level drivers */
macro_line|#ifdef CONFIG_BLK_DEV_SD
id|scsi_register_device
c_func
(paren
op_amp
id|sd_template
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_SR
id|scsi_register_device
c_func
(paren
op_amp
id|sr_template
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_CHR_DEV_ST
id|scsi_register_device
c_func
(paren
op_amp
id|st_template
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_CHR_DEV_SG
id|scsi_register_device
c_func
(paren
op_amp
id|sg_template
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if 0      
id|max_scsi_hosts
op_assign
id|next_scsi_host
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
