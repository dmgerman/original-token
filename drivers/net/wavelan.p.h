multiline_comment|/*&n; *&t;Wavelan ISA driver&n; *&n; *&t;&t;Jean II - HPLB &squot;96&n; *&n; * Reorganisation and extension of the driver.&n; *&n; * This file contain all definition and declarations necessary for the&n; * wavelan isa driver. This file is a private header, so it should&n; * be included only on wavelan.c !!!&n; */
macro_line|#ifndef WAVELAN_P_H
DECL|macro|WAVELAN_P_H
mdefine_line|#define WAVELAN_P_H
multiline_comment|/************************** DOCUMENTATION **************************/
multiline_comment|/*&n; * This driver provide a Linux interface to the Wavelan ISA hardware&n; * The Wavelan is a product of Lucent (&quot;http://wavelan.netland.nl/&quot;).&n; * This division was formerly part of NCR and then AT&amp;T.&n; * Wavelan are also distributed by DEC (RoamAbout), Digital Ocean and&n; * Aironet (Arlan). If you have one of those product, you will need to&n; * make some changes below...&n; *&n; * This driver is still a beta software. A lot of bugs have been corrected,&n; * a lot of functionalities are implemented, the whole appear pretty stable,&n; * but there is still some area of improvement (encryption, performance...).&n; *&n; * To know how to use this driver, read the NET3 HOWTO.&n; * If you want to exploit the many other fonctionalities, look comments&n; * in the code...&n; *&n; * This driver is the result of the effort of many peoples (see below).&n; */
multiline_comment|/* ------------------------ SPECIFIC NOTES ------------------------ */
multiline_comment|/*&n; * MAC address and hardware detection :&n; * ----------------------------------&n; *&t;The detection code of the wavelan chech that the first 3&n; *&t;octets of the MAC address fit the company code. This type of&n; *&t;detection work well for AT&amp;T cards (because the AT&amp;T code is&n; *&t;hardcoded in wavelan.h), but of course will fail for other&n; *&t;manufacturer.&n; *&n; *&t;If you are sure that your card is derived from the wavelan,&n; *&t;here is the way to configure it :&n; *&t;1) Get your MAC address&n; *&t;&t;a) With your card utilities (wfreqsel, instconf, ...)&n; *&t;&t;b) With the driver :&n; *&t;&t;&t;o compile the kernel with DEBUG_CONFIG_INFO enabled&n; *&t;&t;&t;o Boot and look the card messages&n; *&t;2) Set your MAC code (3 octets) in MAC_ADDRESSES[][3] (wavelan.h)&n; *&t;3) Compile &amp; verify&n; *&t;4) Send me the MAC code - I will include it in the next version...&n; *&n; * &quot;CU Inactive&quot; message at boot up :&n; * -----------------------------------&n; *&t;It seem that there is some weird timings problems with the&n; *&t;Intel microcontroler. In fact, this message is triggered by a&n; *&t;bad reading of the on board ram the first time we read the&n; *&t;control block. If you ignore this message, all is ok (but in&n; *&t;fact, currently, it reset the wavelan hardware).&n; *&n; *&t;To get rid of that problem, there is two solution. The first&n; *&t;is to add a dummy read of the scb at the end of&n; *&t;wv_82586_config. The second is to add the timers&n; *&t;wv_synchronous_cmd and wv_ack (the udelay just after the&n; *&t;waiting loops - seem that the controler is not totally ready&n; *&t;when it say it is !).&n; *&n; *&t;In the current code, I use the second solution (to be&n; *&t;consistent with the original solution of Bruce Janson).&n; */
multiline_comment|/* --------------------- WIRELESS EXTENSIONS --------------------- */
multiline_comment|/*&n; * This driver is the first one to support &quot;wireless extensions&quot;.&n; * This set of extensions provide you some way to control the wireless&n; * caracteristics of the hardware in a standard way and support for&n; * applications for taking advantage of it (like Mobile IP).&n; *&n; * By default, these wireless extensions are disabled, because they&n; * need a patch to the Linux Kernel. This simple patch may be found&n; * with the driver + some utilities to access those wireless&n; * extensions (iwconfig...). Hopefully, those wireless extensions will&n; * make their way in the kernel someday.&n; *&n; * You also will need to enable the CONFIG_NET_RADIO in the kernel&n; * configuration to enable the wireless extensions.&n; */
multiline_comment|/* ---------------------------- FILES ---------------------------- */
multiline_comment|/*&n; * wavelan.c :&t;&t;The actual code for the driver - C functions&n; *&n; * wavelan.p.h :&t;Private header : local types / vars for the driver&n; *&n; * wavelan.h :&t;&t;Description of the hardware interface &amp; structs&n; *&n; * i82586.h :&t;&t;Description if the Ethernet controler&n; */
multiline_comment|/* --------------------------- HISTORY --------------------------- */
multiline_comment|/*&n; * (Made with information in drivers headers. It may not be accurate,&n; * and I garantee nothing except my best effort...)&n; *&n; * The history of the Wavelan drivers is as complicated as history of&n; * the Wavelan itself (NCR -&gt; AT&amp;T -&gt; Lucent).&n; *&n; * All started with Anders Klemets &lt;klemets@paul.rutgers.edu&gt;,&n; * writting a Wavelan ISA driver for the MACH microkernel. Girish&n; * Welling &lt;welling@paul.rutgers.edu&gt; had also worked on it.&n; * Keith Moore modify this for the Pcmcia hardware.&n; * &n; * Robert Morris &lt;rtm@das.harvard.edu&gt; port these two drivers to BSDI&n; * and add specific Pcmcia support (there is currently no equivalent&n; * of the PCMCIA package under BSD...).&n; *&n; * Jim Binkley &lt;jrb@cs.pdx.edu&gt; port both BSDI drivers to freeBSD.&n; *&n; * Bruce Janson &lt;bruce@cs.usyd.edu.au&gt; port the BSDI ISA driver to Linux.&n; *&n; * Anthony D. Joseph &lt;adj@lcs.mit.edu&gt; started modify Bruce driver&n; * (with help of the BSDI PCMCIA driver) for PCMCIA.&n; * Yunzhou Li &lt;yunzhou@strat.iol.unh.edu&gt; finished is work.&n; * Joe Finney &lt;joe@comp.lancs.ac.uk&gt; patched the driver to start&n; * correctly 2.00 cards (2.4 GHz with frequency selection).&n; * David Hinds &lt;dhinds@hyper.stanford.edu&gt; integrated the whole in his&n; * Pcmcia package (+ bug corrections).&n; *&n; * I (Jean Tourrilhes - jt@hplb.hpl.hp.com) then started to make some&n; * patchs to the Pcmcia driver. After, I added code in the ISA driver&n; * for Wireless Extensions and full support of frequency selection&n; * cards. Then, I&squot;ve done the same to the Pcmcia driver + some&n; * reorganisation. Finally, I came back to the ISA driver to&n; * upgrade it at the same level as the Pcmcia one and reorganise&n; * the code&n; * Loeke Brederveld &lt;lbrederv@wavelan.com&gt; from Lucent has given me&n; * much needed informations on the Wavelan hardware.&n; *&n; * Yongguang Zhang &lt;ygz@isl.hrl.hac.com&gt; send me a patch for enabling&n; * multicast in the old pcmcia driver. I tried to do the same (with&n; * some minor changes) in this driver, but without any luck (I don&squot;t&n; * know how to enable multicast in the chip...).&n; */
multiline_comment|/* The original copyrights and litteratures mention others names and&n; * credits. I don&squot;t know what there part in this development was...&n; */
multiline_comment|/* By the way : for the copyright &amp; legal stuff :&n; * Almost everybody wrote code under GNU or BSD license (or alike),&n; * and want that their original copyright remain somewhere in the&n; * code (for myself, I go with the GPL).&n; * Nobody want to take responsibility for anything, except the fame...&n; */
multiline_comment|/* --------------------------- CREDITS --------------------------- */
multiline_comment|/*&n; * This software was developed as a component of the&n; * Linux operating system.&n; * It is based on other device drivers and information&n; * either written or supplied by:&n; *&t;Ajay Bakre (bakre@paul.rutgers.edu),&n; *&t;Donald Becker (becker@cesdis.gsfc.nasa.gov),&n; *&t;Loeke Brederveld (Loeke.Brederveld@Utrecht.NCR.com),&n; *&t;Anders Klemets (klemets@it.kth.se),&n; *&t;Vladimir V. Kolpakov (w@stier.koenig.ru),&n; *&t;Marc Meertens (Marc.Meertens@Utrecht.NCR.com),&n; *&t;Pauline Middelink (middelin@polyware.iaf.nl),&n; *&t;Robert Morris (rtm@das.harvard.edu),&n; *&t;Jean Tourrilhes (jt@hplb.hpl.hp.com),&n; *&t;Girish Welling (welling@paul.rutgers.edu),&n; *&t;Yongguang Zhang &lt;ygz@isl.hrl.hac.com&gt;...&n; *&n; * Thanks go also to:&n; *&t;James Ashton (jaa101@syseng.anu.edu.au),&n; *&t;Alan Cox (iialan@iiit.swan.ac.uk),&n; *&t;Allan Creighton (allanc@cs.usyd.edu.au),&n; *&t;Matthew Geier (matthew@cs.usyd.edu.au),&n; *&t;Remo di Giovanni (remo@cs.usyd.edu.au),&n; *&t;Eckhard Grah (grah@wrcs1.urz.uni-wuppertal.de),&n; *&t;Vipul Gupta (vgupta@cs.binghamton.edu),&n; *&t;Mark Hagan (mhagan@wtcpost.daytonoh.NCR.COM),&n; *&t;Tim Nicholson (tim@cs.usyd.edu.au),&n; *&t;Ian Parkin (ian@cs.usyd.edu.au),&n; *&t;John Rosenberg (johnr@cs.usyd.edu.au),&n; *&t;George Rossi (george@phm.gov.au),&n; *&t;Arthur Scott (arthur@cs.usyd.edu.au),&n; *&t;Peter Storey,&n; * for their assistance and advice.&n; *&n; * Additional Credits:&n; *&n; * My developpement has been done under Linux 2.0.x (Debian 1.1) with&n; *&t;an HP Vectra XP/60.&n; *&n; */
multiline_comment|/* ------------------------- IMPROVEMENTS ------------------------- */
multiline_comment|/*&n; * I proudly present :&n; *&n; * Changes mades in first pre-release :&n; * ----------------------------------&n; *&t;- Reorganisation of the code, function name change&n; *&t;- Creation of private header (wavelan.p.h)&n; *&t;- Reorganised debug messages&n; *&t;- More comments, history, ...&n; *&t;- mmc_init : configure the PSA if not done&n; *&t;- mmc_init : correct default value of level threshold for pcmcia&n; *&t;- mmc_init : 2.00 detection better code for 2.00 init&n; *&t;- better info at startup&n; *&t;- irq setting (note : this setting is permanent...)&n; *&t;- Watchdog : change strategy (+ solve module removal problems)&n; *&t;- add wireless extensions (ioctl &amp; get_wireless_stats)&n; *&t;  get/set nwid/frequency on fly, info for /proc/net/wireless&n; *&t;- More wireless extension : SETSPY and GETSPY&n; *&t;- Make wireless extensions optional&n; *&t;- Private ioctl to set/get quality &amp; level threshold, histogram&n; *&t;- Remove /proc/net/wavelan&n; *&t;- Supress useless stuff from lp (net_local)&n; *&t;- kernel 2.1 support (copy_to/from_user instead of memcpy_to/fromfs)&n; *&t;- Add message level (debug stuff in /var/adm/debug &amp; errors not&n; *&t;  displayed at console and still in /var/adm/messages)&n; *&t;- multi device support&n; *&t;- Start fixing the probe (init code)&n; *&t;- More inlines&n; *&t;- man page&n; *&t;- Lot of others minor details &amp; cleanups&n; *&n; * Changes made in second pre-release :&n; * ----------------------------------&n; *&t;- Cleanup init code (probe &amp; module init)&n; *&t;- Better multi device support (module)&n; *&t;- name assignement (module)&n; *&n; * Changes made in third pre-release :&n; * ---------------------------------&n; *&t;- Be more conservative on timers&n; *&t;- Preliminary support for multicast (I still lack some details...)&n; *&n; * Changes made in fourth pre-release :&n; * ----------------------------------&n; *&t;- multicast (revisited and finished)&n; *&t;- Avoid reset in set_multicast_list (a really big hack)&n; *&t;  if somebody could apply this code for other i82586 based driver...&n; *&t;- Share on board memory 75% RU / 25% CU (instead of 50/50)&n; *&n; * Changes made for release in 2.1.15 :&n; * ----------------------------------&n; *&t;- Change the detection code for multi manufacturer code support&n; *&n; * Changes made for release in 2.1.17 :&n; * ----------------------------------&n; *&t;- Update to wireless extensions changes&n; *&t;- Silly bug in card initial configuration (psa_conf_status)&n; *&n; * Wishes &amp; dreams :&n; * ---------------&n; *&t;- Encryption stuff&n; *&t;- Roaming&n; */
multiline_comment|/***************************** INCLUDES *****************************/
macro_line|#include&t;&lt;linux/module.h&gt;
macro_line|#include&t;&lt;linux/kernel.h&gt;
macro_line|#include&t;&lt;linux/sched.h&gt;
macro_line|#include&t;&lt;linux/types.h&gt;
macro_line|#include&t;&lt;linux/fcntl.h&gt;
macro_line|#include&t;&lt;linux/interrupt.h&gt;
macro_line|#include&t;&lt;linux/stat.h&gt;
macro_line|#include&t;&lt;linux/ptrace.h&gt;
macro_line|#include&t;&lt;linux/ioport.h&gt;
macro_line|#include&t;&lt;linux/in.h&gt;
macro_line|#include&t;&lt;linux/string.h&gt;
macro_line|#include&t;&lt;linux/delay.h&gt;
macro_line|#include&t;&lt;asm/system.h&gt;
macro_line|#include&t;&lt;asm/bitops.h&gt;
macro_line|#include&t;&lt;asm/io.h&gt;
macro_line|#include&t;&lt;asm/dma.h&gt;
macro_line|#include&t;&lt;asm/uaccess.h&gt;
macro_line|#include&t;&lt;linux/errno.h&gt;
macro_line|#include&t;&lt;linux/netdevice.h&gt;
macro_line|#include&t;&lt;linux/etherdevice.h&gt;
macro_line|#include&t;&lt;linux/skbuff.h&gt;
macro_line|#include&t;&lt;linux/malloc.h&gt;
macro_line|#include&t;&lt;linux/timer.h&gt;
macro_line|#include &lt;linux/wireless.h&gt;&t;&t;/* Wireless extensions */
multiline_comment|/* Wavelan declarations */
macro_line|#include&t;&quot;i82586.h&quot;
macro_line|#include&t;&quot;wavelan.h&quot;
multiline_comment|/****************************** DEBUG ******************************/
DECL|macro|DEBUG_MODULE_TRACE
macro_line|#undef DEBUG_MODULE_TRACE&t;/* Module insertion/removal */
DECL|macro|DEBUG_CALLBACK_TRACE
macro_line|#undef DEBUG_CALLBACK_TRACE&t;/* Calls made by Linux */
DECL|macro|DEBUG_INTERRUPT_TRACE
macro_line|#undef DEBUG_INTERRUPT_TRACE&t;/* Calls to handler */
DECL|macro|DEBUG_INTERRUPT_INFO
macro_line|#undef DEBUG_INTERRUPT_INFO&t;/* type of interrupt &amp; so on */
DECL|macro|DEBUG_INTERRUPT_ERROR
mdefine_line|#define DEBUG_INTERRUPT_ERROR&t;/* problems */
DECL|macro|DEBUG_CONFIG_TRACE
macro_line|#undef DEBUG_CONFIG_TRACE&t;/* Trace the config functions */
DECL|macro|DEBUG_CONFIG_INFO
macro_line|#undef DEBUG_CONFIG_INFO&t;/* What&squot;s going on... */
DECL|macro|DEBUG_CONFIG_ERRORS
mdefine_line|#define DEBUG_CONFIG_ERRORS&t;/* Errors on configuration */
DECL|macro|DEBUG_TX_TRACE
macro_line|#undef DEBUG_TX_TRACE&t;&t;/* Transmission calls */
DECL|macro|DEBUG_TX_INFO
macro_line|#undef DEBUG_TX_INFO&t;&t;/* Header of the transmited packet */
DECL|macro|DEBUG_TX_ERROR
mdefine_line|#define DEBUG_TX_ERROR&t;&t;/* unexpected conditions */
DECL|macro|DEBUG_RX_TRACE
macro_line|#undef DEBUG_RX_TRACE&t;&t;/* Transmission calls */
DECL|macro|DEBUG_RX_INFO
macro_line|#undef DEBUG_RX_INFO&t;&t;/* Header of the transmited packet */
DECL|macro|DEBUG_RX_ERROR
mdefine_line|#define DEBUG_RX_ERROR&t;&t;/* unexpected conditions */
DECL|macro|DEBUG_PACKET_DUMP
macro_line|#undef DEBUG_PACKET_DUMP&t;16&t;/* Dump packet on the screen */
DECL|macro|DEBUG_IOCTL_TRACE
macro_line|#undef DEBUG_IOCTL_TRACE&t;/* Misc call by Linux */
DECL|macro|DEBUG_IOCTL_INFO
macro_line|#undef DEBUG_IOCTL_INFO&t;&t;/* Various debug info */
DECL|macro|DEBUG_IOCTL_ERROR
mdefine_line|#define DEBUG_IOCTL_ERROR&t;/* What&squot;s going wrong */
DECL|macro|DEBUG_BASIC_SHOW
mdefine_line|#define DEBUG_BASIC_SHOW&t;/* Show basic startup info */
DECL|macro|DEBUG_VERSION_SHOW
macro_line|#undef DEBUG_VERSION_SHOW&t;/* Print version info */
DECL|macro|DEBUG_PSA_SHOW
macro_line|#undef DEBUG_PSA_SHOW&t;&t;/* Dump psa to screen */
DECL|macro|DEBUG_MMC_SHOW
macro_line|#undef DEBUG_MMC_SHOW&t;&t;/* Dump mmc to screen */
DECL|macro|DEBUG_SHOW_UNUSED
macro_line|#undef DEBUG_SHOW_UNUSED&t;/* Show also unused fields */
DECL|macro|DEBUG_I82586_SHOW
macro_line|#undef DEBUG_I82586_SHOW&t;/* Show i82586 status */
DECL|macro|DEBUG_DEVICE_SHOW
macro_line|#undef DEBUG_DEVICE_SHOW&t;/* Show device parameters */
multiline_comment|/* Options : */
DECL|macro|USE_PSA_CONFIG
mdefine_line|#define USE_PSA_CONFIG&t;&t;/* Use info from the PSA */
DECL|macro|IGNORE_NORMAL_XMIT_ERRS
mdefine_line|#define IGNORE_NORMAL_XMIT_ERRS&t;/* Don&squot;t bother with normal conditions */
DECL|macro|STRUCT_CHECK
macro_line|#undef STRUCT_CHECK&t;&t;/* Verify padding of structures */
DECL|macro|PSA_CRC
macro_line|#undef PSA_CRC&t;&t;&t;/* Check CRC in PSA */
DECL|macro|OLDIES
macro_line|#undef OLDIES&t;&t;&t;/* Old code (to redo) */
DECL|macro|RECORD_SNR
macro_line|#undef RECORD_SNR&t;&t;/* To redo */
DECL|macro|EEPROM_IS_PROTECTED
macro_line|#undef EEPROM_IS_PROTECTED&t;/* Doesn&squot;t seem to be necessary */
DECL|macro|MULTICAST_AVOID
mdefine_line|#define MULTICAST_AVOID&t;&t;/* Avoid extra multicast (I&squot;m sceptical) */
macro_line|#ifdef WIRELESS_EXT&t;/* If wireless extension exist in the kernel */
multiline_comment|/* Warning : these stuff will slow down the driver... */
DECL|macro|WIRELESS_SPY
mdefine_line|#define WIRELESS_SPY&t;&t;/* Enable spying addresses */
DECL|macro|HISTOGRAM
macro_line|#undef HISTOGRAM&t;&t;/* Enable histogram of sig level... */
macro_line|#endif
multiline_comment|/************************ CONSTANTS &amp; MACROS ************************/
macro_line|#ifdef DEBUG_VERSION_SHOW
DECL|variable|version
r_static
r_const
r_char
op_star
id|version
op_assign
l_string|&quot;wavelan.c : v12 (wireless extensions) 1/12/96&bslash;n&quot;
suffix:semicolon
macro_line|#endif
multiline_comment|/* Watchdog temporisation */
DECL|macro|WATCHDOG_JIFFIES
mdefine_line|#define&t;WATCHDOG_JIFFIES&t;32&t;/* TODO: express in HZ. */
multiline_comment|/* Macro to get the number of elements in an array */
DECL|macro|NELS
mdefine_line|#define&t;NELS(a)&t;&t;&t;&t;(sizeof(a) / sizeof(a[0]))
multiline_comment|/* ------------------------ PRIVATE IOCTL ------------------------ */
DECL|macro|SIOCSIPQTHR
mdefine_line|#define SIOCSIPQTHR&t;SIOCDEVPRIVATE&t;&t;/* Set quality threshold */
DECL|macro|SIOCGIPQTHR
mdefine_line|#define SIOCGIPQTHR&t;SIOCDEVPRIVATE + 1&t;/* Get quality threshold */
DECL|macro|SIOCSIPLTHR
mdefine_line|#define SIOCSIPLTHR&t;SIOCDEVPRIVATE + 2&t;/* Set level threshold */
DECL|macro|SIOCGIPLTHR
mdefine_line|#define SIOCGIPLTHR&t;SIOCDEVPRIVATE + 3&t;/* Get level threshold */
DECL|macro|SIOCSIPHISTO
mdefine_line|#define SIOCSIPHISTO&t;SIOCDEVPRIVATE + 6&t;/* Set histogram ranges */
DECL|macro|SIOCGIPHISTO
mdefine_line|#define SIOCGIPHISTO&t;SIOCDEVPRIVATE + 7&t;/* Get histogram values */
multiline_comment|/****************************** TYPES ******************************/
multiline_comment|/* Shortcuts */
DECL|typedef|device
r_typedef
r_struct
id|device
id|device
suffix:semicolon
DECL|typedef|en_stats
r_typedef
r_struct
id|net_device_stats
id|en_stats
suffix:semicolon
DECL|typedef|iw_stats
r_typedef
r_struct
id|iw_statistics
id|iw_stats
suffix:semicolon
DECL|typedef|iw_qual
r_typedef
r_struct
id|iw_quality
id|iw_qual
suffix:semicolon
DECL|typedef|iw_freq
r_typedef
r_struct
id|iw_freq
id|iw_freq
suffix:semicolon
DECL|typedef|net_local
r_typedef
r_struct
id|net_local
id|net_local
suffix:semicolon
DECL|typedef|timer_list
r_typedef
r_struct
id|timer_list
id|timer_list
suffix:semicolon
multiline_comment|/* Basic types */
DECL|typedef|mac_addr
r_typedef
id|u_char
id|mac_addr
(braket
id|WAVELAN_ADDR_SIZE
)braket
suffix:semicolon
multiline_comment|/* Hardware address */
multiline_comment|/*&n; * Static specific data for the interface.&n; *&n; * For each network interface, Linux keep data in two structure. &quot;device&quot;&n; * keep the generic data (same format for everybody) and &quot;net_local&quot; keep&n; * the additional specific data.&n; * Note that some of this specific data is in fact generic (en_stats, for&n; * example).&n; */
DECL|struct|net_local
r_struct
id|net_local
(brace
DECL|member|next
id|net_local
op_star
id|next
suffix:semicolon
multiline_comment|/* Linked list of the devices */
DECL|member|dev
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* Reverse link... */
DECL|member|stats
id|en_stats
id|stats
suffix:semicolon
multiline_comment|/* Ethernet interface statistics */
DECL|member|nresets
r_int
id|nresets
suffix:semicolon
multiline_comment|/* Number of hw resets */
DECL|member|reconfig_82586
id|u_char
id|reconfig_82586
suffix:semicolon
multiline_comment|/* Need to reconfigure the controler */
DECL|member|promiscuous
id|u_char
id|promiscuous
suffix:semicolon
multiline_comment|/* Promiscuous mode */
DECL|member|mc_count
r_int
id|mc_count
suffix:semicolon
multiline_comment|/* Number of multicast addresses */
DECL|member|watchdog
id|timer_list
id|watchdog
suffix:semicolon
multiline_comment|/* To avoid blocking state */
DECL|member|hacr
id|u_short
id|hacr
suffix:semicolon
multiline_comment|/* Current host interface state */
DECL|member|tx_n_in_use
r_int
id|tx_n_in_use
suffix:semicolon
DECL|member|rx_head
id|u_short
id|rx_head
suffix:semicolon
DECL|member|rx_last
id|u_short
id|rx_last
suffix:semicolon
DECL|member|tx_first_free
id|u_short
id|tx_first_free
suffix:semicolon
DECL|member|tx_first_in_use
id|u_short
id|tx_first_in_use
suffix:semicolon
macro_line|#ifdef WIRELESS_EXT
DECL|member|wstats
id|iw_stats
id|wstats
suffix:semicolon
multiline_comment|/* Wireless specific stats */
macro_line|#endif
macro_line|#ifdef WIRELESS_SPY
DECL|member|spy_number
r_int
id|spy_number
suffix:semicolon
multiline_comment|/* Number of addresses to spy */
DECL|member|spy_address
id|mac_addr
id|spy_address
(braket
id|IW_MAX_SPY
)braket
suffix:semicolon
multiline_comment|/* The addresses to spy */
DECL|member|spy_stat
id|iw_qual
id|spy_stat
(braket
id|IW_MAX_SPY
)braket
suffix:semicolon
multiline_comment|/* Statistics gathered */
macro_line|#endif&t;/* WIRELESS_SPY */
macro_line|#ifdef HISTOGRAM
DECL|member|his_number
r_int
id|his_number
suffix:semicolon
multiline_comment|/* Number of intervals */
DECL|member|his_range
id|u_char
id|his_range
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Boundaries of interval ]n-1; n] */
DECL|member|his_sum
id|u_long
id|his_sum
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* Sum in interval */
macro_line|#endif&t;/* HISTOGRAM */
)brace
suffix:semicolon
multiline_comment|/**************************** PROTOTYPES ****************************/
multiline_comment|/* ----------------------- MISC SUBROUTINES ------------------------ */
r_static
r_inline
r_int
r_int
multiline_comment|/* flags */
id|wv_splhi
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Disable interrupts */
r_static
r_inline
r_void
id|wv_splx
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* ReEnable interrupts : flags */
r_static
id|u_char
id|wv_irq_to_psa
c_func
(paren
r_int
)paren
suffix:semicolon
r_static
r_int
id|wv_psa_to_irq
c_func
(paren
id|u_char
)paren
suffix:semicolon
multiline_comment|/* ------------------- HOST ADAPTER SUBROUTINES ------------------- */
r_static
r_inline
id|u_short
multiline_comment|/* data */
id|hasr_read
c_func
(paren
id|u_short
)paren
suffix:semicolon
multiline_comment|/* Read the host interface : base address */
r_static
r_inline
r_void
id|hacr_write
c_func
(paren
id|u_short
comma
multiline_comment|/* Write to host interface : base address */
id|u_short
)paren
comma
multiline_comment|/* data */
id|hacr_write_slow
c_func
(paren
id|u_short
comma
id|u_short
)paren
comma
id|set_chan_attn
c_func
(paren
id|u_short
comma
multiline_comment|/* ioaddr */
id|u_short
)paren
comma
multiline_comment|/* hacr */
id|wv_hacr_reset
c_func
(paren
id|u_short
)paren
comma
multiline_comment|/* ioaddr */
id|wv_16_off
c_func
(paren
id|u_short
comma
multiline_comment|/* ioaddr */
id|u_short
)paren
comma
multiline_comment|/* hacr */
id|wv_16_on
c_func
(paren
id|u_short
comma
multiline_comment|/* ioaddr */
id|u_short
)paren
comma
multiline_comment|/* hacr */
id|wv_ints_off
c_func
(paren
id|device
op_star
)paren
comma
id|wv_ints_on
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* ----------------- MODEM MANAGEMENT SUBROUTINES ----------------- */
r_static
r_void
id|psa_read
c_func
(paren
id|u_short
comma
multiline_comment|/* Read the Parameter Storage Area */
id|u_short
comma
multiline_comment|/* hacr */
r_int
comma
multiline_comment|/* offset in PSA */
id|u_char
op_star
comma
multiline_comment|/* buffer to fill */
r_int
)paren
comma
multiline_comment|/* size to read */
id|psa_write
c_func
(paren
id|u_short
comma
multiline_comment|/* Write to the PSA */
id|u_short
comma
multiline_comment|/* hacr */
r_int
comma
multiline_comment|/* Offset in psa */
id|u_char
op_star
comma
multiline_comment|/* Buffer in memory */
r_int
)paren
suffix:semicolon
multiline_comment|/* Length of buffer */
r_static
r_inline
r_void
id|mmc_out
c_func
(paren
id|u_short
comma
multiline_comment|/* Write 1 byte to the Modem Manag Control */
id|u_short
comma
id|u_char
)paren
comma
id|mmc_write
c_func
(paren
id|u_short
comma
multiline_comment|/* Write n bytes to the MMC */
id|u_char
comma
id|u_char
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_inline
id|u_char
multiline_comment|/* Read 1 byte from the MMC */
id|mmc_in
c_func
(paren
id|u_short
comma
id|u_short
)paren
suffix:semicolon
r_static
r_inline
r_void
id|mmc_read
c_func
(paren
id|u_short
comma
multiline_comment|/* Read n bytes from the MMC */
id|u_char
comma
id|u_char
op_star
comma
r_int
)paren
comma
id|fee_wait
c_func
(paren
id|u_short
comma
multiline_comment|/* Wait for frequency EEprom : base address */
r_int
comma
multiline_comment|/* Base delay to wait for */
r_int
)paren
suffix:semicolon
multiline_comment|/* Number of time to wait */
r_static
r_void
id|fee_read
c_func
(paren
id|u_short
comma
multiline_comment|/* Read the frequency EEprom : base address */
id|u_short
comma
multiline_comment|/* destination offset */
id|u_short
op_star
comma
multiline_comment|/* data buffer */
r_int
)paren
comma
multiline_comment|/* number of registers */
id|fee_write
c_func
(paren
id|u_short
comma
multiline_comment|/* Write to frequency EEprom : base address */
id|u_short
comma
multiline_comment|/* destination offset */
id|u_short
op_star
comma
multiline_comment|/* data buffer */
r_int
)paren
suffix:semicolon
multiline_comment|/* number of registers */
multiline_comment|/* ---------------------- I82586 SUBROUTINES ----------------------- */
r_static
multiline_comment|/*inline*/
r_void
id|obram_read
c_func
(paren
id|u_short
comma
multiline_comment|/* ioaddr */
id|u_short
comma
multiline_comment|/* o */
id|u_char
op_star
comma
multiline_comment|/* b */
r_int
)paren
suffix:semicolon
multiline_comment|/* n */
r_static
r_inline
r_void
id|obram_write
c_func
(paren
id|u_short
comma
multiline_comment|/* ioaddr */
id|u_short
comma
multiline_comment|/* o */
id|u_char
op_star
comma
multiline_comment|/* b */
r_int
)paren
suffix:semicolon
multiline_comment|/* n */
r_static
r_void
id|wv_ack
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
r_static
r_inline
r_int
id|wv_synchronous_cmd
c_func
(paren
id|device
op_star
comma
r_const
r_char
op_star
)paren
comma
id|wv_config_complete
c_func
(paren
id|device
op_star
comma
id|u_short
comma
id|net_local
op_star
)paren
suffix:semicolon
r_static
r_int
id|wv_complete
c_func
(paren
id|device
op_star
comma
id|u_short
comma
id|net_local
op_star
)paren
suffix:semicolon
r_static
r_inline
r_void
id|wv_82586_reconfig
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* ------------------- DEBUG &amp; INFO SUBROUTINES ------------------- */
macro_line|#ifdef DEBUG_I82586_SHOW
r_static
r_void
id|wv_scb_show
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif
r_static
r_inline
r_void
id|wv_init_info
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* display startup info */
multiline_comment|/* ------------------- IOCTL, STATS &amp; RECONFIG ------------------- */
r_static
id|en_stats
op_star
id|wavelan_get_stats
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Give stats /proc/net/dev */
r_static
r_void
id|wavelan_set_multicast_list
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* ----------------------- PACKET RECEPTION ----------------------- */
r_static
r_inline
r_void
id|wv_packet_read
c_func
(paren
id|device
op_star
comma
multiline_comment|/* Read a packet from a frame */
id|u_short
comma
r_int
)paren
comma
id|wv_receive
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Read all packets waiting */
multiline_comment|/* --------------------- PACKET TRANSMISSION --------------------- */
r_static
r_inline
r_void
id|wv_packet_write
c_func
(paren
id|device
op_star
comma
multiline_comment|/* Write a packet to the Tx buffer */
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|wavelan_packet_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
comma
multiline_comment|/* Send a packet */
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* -------------------- HARDWARE CONFIGURATION -------------------- */
r_static
r_inline
r_int
id|wv_mmc_init
c_func
(paren
id|device
op_star
)paren
comma
multiline_comment|/* Initialize the modem */
id|wv_ru_start
c_func
(paren
id|device
op_star
)paren
comma
multiline_comment|/* Start the i82586 receiver unit */
id|wv_cu_start
c_func
(paren
id|device
op_star
)paren
comma
multiline_comment|/* Start the i82586 command unit */
id|wv_82586_start
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Start the i82586 */
r_static
r_void
id|wv_82586_config
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Configure the i82586 */
r_static
r_inline
r_void
id|wv_82586_stop
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
r_static
r_int
id|wv_hw_reset
c_func
(paren
id|device
op_star
)paren
comma
multiline_comment|/* Reset the wavelan hardware */
id|wv_check_ioaddr
c_func
(paren
id|u_short
comma
multiline_comment|/* ioaddr */
id|u_char
op_star
)paren
suffix:semicolon
multiline_comment|/* mac address (read) */
multiline_comment|/* ---------------------- INTERRUPT HANDLING ---------------------- */
r_static
r_void
id|wavelan_interrupt
c_func
(paren
r_int
comma
multiline_comment|/* Interrupt handler */
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_static
r_void
id|wavelan_watchdog
c_func
(paren
id|u_long
)paren
suffix:semicolon
multiline_comment|/* Transmission watchdog */
multiline_comment|/* ------------------- CONFIGURATION CALLBACKS ------------------- */
r_static
r_int
id|wavelan_open
c_func
(paren
id|device
op_star
)paren
comma
multiline_comment|/* Open the device */
id|wavelan_close
c_func
(paren
id|device
op_star
)paren
comma
multiline_comment|/* Close the device */
id|wavelan_config
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* Configure one device */
r_extern
r_int
id|wavelan_probe
c_func
(paren
id|device
op_star
)paren
suffix:semicolon
multiline_comment|/* See Space.c */
multiline_comment|/**************************** VARIABLES ****************************/
multiline_comment|/*&n; * This is the root of the linked list of wavelan drivers&n; * It is use to verify that we don&squot;t reuse the same base address&n; * for two differents drivers and to make the cleanup when&n; * removing the module.&n; */
DECL|variable|wavelan_list
r_static
id|net_local
op_star
id|wavelan_list
op_assign
(paren
id|net_local
op_star
)paren
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * This table is used to translate the psa value to irq number&n; * and vice versa...&n; */
DECL|variable|irqvals
r_static
id|u_char
id|irqvals
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0x01
comma
l_int|0x02
comma
l_int|0x04
comma
l_int|0
comma
l_int|0x08
comma
l_int|0
comma
l_int|0
comma
l_int|0x10
comma
l_int|0x20
comma
l_int|0x40
comma
l_int|0
comma
l_int|0
comma
l_int|0x80
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Table of the available i/o address (base address) for wavelan&n; */
DECL|variable|iobase
r_static
r_int
r_int
id|iobase
(braket
)braket
op_assign
(brace
macro_line|#if&t;0
multiline_comment|/* Leave out 0x3C0 for now -- seems to clash with some video&n;   * controllers.&n;   * Leave out the others too -- we will always use 0x390 and leave&n;   * 0x300 for the Ethernet device.&n;   * Jean II : 0x3E0 is really fine as well...&n;   */
l_int|0x300
comma
l_int|0x390
comma
l_int|0x3E0
comma
l_int|0x3C0
macro_line|#endif&t;/* 0 */
l_int|0x390
comma
l_int|0x3E0
)brace
suffix:semicolon
macro_line|#ifdef&t;MODULE
multiline_comment|/* Name of the devices (memory allocation) */
DECL|variable|devname
r_static
r_char
id|devname
(braket
l_int|4
)braket
(braket
id|IFNAMSIZ
)braket
op_assign
(brace
l_string|&quot;&quot;
comma
l_string|&quot;&quot;
comma
l_string|&quot;&quot;
comma
l_string|&quot;&quot;
)brace
suffix:semicolon
multiline_comment|/* Parameters set by insmod */
DECL|variable|io
r_static
r_int
id|io
(braket
l_int|4
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
(braket
l_int|4
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|name
r_static
r_char
op_star
id|name
(braket
l_int|4
)braket
op_assign
(brace
id|devname
(braket
l_int|0
)braket
comma
id|devname
(braket
l_int|1
)braket
comma
id|devname
(braket
l_int|2
)braket
comma
id|devname
(braket
l_int|3
)braket
)brace
suffix:semicolon
macro_line|#endif&t;/* MODULE */
macro_line|#endif&t;/* WAVELAN_P_H */
eof
