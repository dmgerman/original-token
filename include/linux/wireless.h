multiline_comment|/*&n; * This file define a set of standard wireless extensions&n; *&n; * Version :&t;7&t;23.4.99&n; *&n; * Authors :&t;Jean Tourrilhes - HPLB - &lt;jt@hplb.hpl.hp.com&gt;&n; */
macro_line|#ifndef _LINUX_WIRELESS_H
DECL|macro|_LINUX_WIRELESS_H
mdefine_line|#define _LINUX_WIRELESS_H
multiline_comment|/************************** DOCUMENTATION **************************/
multiline_comment|/*&n; * Basically, the wireless extensions are for now a set of standard ioctl&n; * call + /proc/net/wireless&n; *&n; * The entry /proc/net/wireless give statistics and information on the&n; * driver.&n; * This is better than having each driver having its entry because&n; * its centralised and we may remove the driver module safely.&n; *&n; * Ioctl are used to configure the driver and issue commands.  This is&n; * better than command line options of insmod because we may want to&n; * change dynamically (while the driver is running) some parameters.&n; *&n; * The ioctl mechanimsm are copied from standard devices ioctl.&n; * We have the list of command plus a structure descibing the&n; * data exchanged...&n; * Note that to add these ioctl, I was obliged to modify :&n; *&t;net/core/dev.c (two place + add include)&n; *&t;net/ipv4/af_inet.c (one place + add include)&n; *&n; * /proc/net/wireless is a copy of /proc/net/dev.&n; * We have a structure for data passed from the driver to /proc/net/wireless&n; * Too add this, I&squot;ve modified :&n; *&t;net/core/dev.c (two other places)&n; *&t;include/linux/netdevice.h (one place)&n; *&t;include/linux/proc_fs.h (one place)&n; *&n; * Do not add here things that are redundant with other mechanisms&n; * (drivers init, ifconfig, /proc/net/dev, ...) and with are not&n; * wireless specific.&n; *&n; * These wireless extensions are not magic : each driver has to provide&n; * support for them...&n; *&n; * IMPORTANT NOTE : As everything in the kernel, this is very much a&n; * work in progress. Contact me if you have ideas of improvements...&n; */
multiline_comment|/***************************** INCLUDES *****************************/
macro_line|#include &lt;linux/types.h&gt;&t;&t;/* for &quot;caddr_t&quot; et al&t;&t;*/
macro_line|#include &lt;linux/socket.h&gt;&t;&t;/* for &quot;struct sockaddr&quot; et al&t;*/
macro_line|#include &lt;linux/if.h&gt;&t;&t;&t;/* for IFNAMSIZ and co... */
multiline_comment|/**************************** CONSTANTS ****************************/
multiline_comment|/* --------------------------- VERSION --------------------------- */
multiline_comment|/*&n; * This constant is used to know the availability of the wireless&n; * extensions and to know which version of wireless extensions it is&n; * (there is some stuff that will be added in the future...)&n; * I just plan to increment with each new version.&n; */
DECL|macro|WIRELESS_EXT
mdefine_line|#define WIRELESS_EXT&t;6
multiline_comment|/*&n; * Changes :&n; *&n; * V2 to V3&n; * --------&n; *&t;Alan Cox start some incompatibles changes. I&squot;ve integrated a bit more.&n; *&t;- Encryption renamed to Encode to avoid US regulation problems&n; *&t;- Frequency changed from float to struct to avoid problems on old 386&n; *&n; * V3 to V4&n; * --------&n; *&t;- Add sensitivity&n; *&n; * V4 to V5&n; * --------&n; *&t;- Missing encoding definitions in range&n; *&t;- Access points stuff&n; *&n; * V5 to V6&n; * --------&n; *&t;- 802.11 support (ESSID ioctls)&n; *&n; * V6 to V7&n; * --------&n; *&t;- define IW_ESSID_MAX_SIZE and IW_MAX_AP&n; */
multiline_comment|/* -------------------------- IOCTL LIST -------------------------- */
multiline_comment|/* Basic operations */
DECL|macro|SIOCSIWNAME
mdefine_line|#define SIOCSIWNAME&t;0x8B00&t;&t;/* Unused ??? */
DECL|macro|SIOCGIWNAME
mdefine_line|#define SIOCGIWNAME&t;0x8B01&t;&t;/* get name */
DECL|macro|SIOCSIWNWID
mdefine_line|#define SIOCSIWNWID&t;0x8B02&t;&t;/* set network id */
DECL|macro|SIOCGIWNWID
mdefine_line|#define SIOCGIWNWID&t;0x8B03&t;&t;/* get network id */
DECL|macro|SIOCSIWFREQ
mdefine_line|#define SIOCSIWFREQ&t;0x8B04&t;&t;/* set channel/frequency */
DECL|macro|SIOCGIWFREQ
mdefine_line|#define SIOCGIWFREQ&t;0x8B05&t;&t;/* get channel/frequency */
DECL|macro|SIOCSIWENCODE
mdefine_line|#define SIOCSIWENCODE&t;0x8B06&t;&t;/* set encoding info */
DECL|macro|SIOCGIWENCODE
mdefine_line|#define SIOCGIWENCODE&t;0x8B07&t;&t;/* get encoding info */
DECL|macro|SIOCSIWSENS
mdefine_line|#define SIOCSIWSENS&t;0x8B08&t;&t;/* set sensitivity */
DECL|macro|SIOCGIWSENS
mdefine_line|#define SIOCGIWSENS&t;0x8B09&t;&t;/* get sensitivity */
multiline_comment|/* Informative stuff */
DECL|macro|SIOCSIWRANGE
mdefine_line|#define SIOCSIWRANGE&t;0x8B0A&t;&t;/* Unused ??? */
DECL|macro|SIOCGIWRANGE
mdefine_line|#define SIOCGIWRANGE&t;0x8B0B&t;&t;/* Get range of parameters */
DECL|macro|SIOCSIWPRIV
mdefine_line|#define SIOCSIWPRIV&t;0x8B0C&t;&t;/* Unused ??? */
DECL|macro|SIOCGIWPRIV
mdefine_line|#define SIOCGIWPRIV&t;0x8B0D&t;&t;/* get private ioctl interface info */
multiline_comment|/* Mobile IP support */
DECL|macro|SIOCSIWSPY
mdefine_line|#define SIOCSIWSPY&t;0x8B10&t;&t;/* set spy addresses */
DECL|macro|SIOCGIWSPY
mdefine_line|#define SIOCGIWSPY&t;0x8B11&t;&t;/* get spy info (quality of link) */
multiline_comment|/* Access Point manipulation */
DECL|macro|SIOCSIWAP
mdefine_line|#define SIOCSIWAP&t;0x8B14&t;&t;/* set access point hardware addresses */
DECL|macro|SIOCGIWAP
mdefine_line|#define SIOCGIWAP&t;0x8B15&t;&t;/* get access point hardware addresses */
DECL|macro|SIOCGIWAPLIST
mdefine_line|#define SIOCGIWAPLIST&t;0x8B17&t;&t;/* get list of access point in range */
multiline_comment|/* 802.11 specific support */
DECL|macro|SIOCSIWESSID
mdefine_line|#define SIOCSIWESSID&t;0x8B1A&t;&t;/* set ESSID (network name) */
DECL|macro|SIOCGIWESSID
mdefine_line|#define SIOCGIWESSID&t;0x8B1B&t;&t;/* get ESSID */
multiline_comment|/* As the ESSID is a string up to 32 bytes long, it doesn&squot;t fit within the&n; * &squot;iwreq&squot; structure, so we need to use the &squot;data&squot; member to point to a&n; * string in user space, like it is done for RANGE...&n; * The &quot;flags&quot; member indicate if the ESSID is active or not.&n; */
multiline_comment|/* ------------------------- IOCTL STUFF ------------------------- */
multiline_comment|/* The first and the last (range) */
DECL|macro|SIOCIWFIRST
mdefine_line|#define SIOCIWFIRST&t;0x8B00
DECL|macro|SIOCIWLAST
mdefine_line|#define SIOCIWLAST&t;0x8B1B
multiline_comment|/* Even : get (world access), odd : set (root access) */
DECL|macro|IW_IS_SET
mdefine_line|#define IW_IS_SET(cmd)&t;(!((cmd) &amp; 0x1))
DECL|macro|IW_IS_GET
mdefine_line|#define IW_IS_GET(cmd)&t;((cmd) &amp; 0x1)
multiline_comment|/* ------------------------- PRIVATE INFO ------------------------- */
multiline_comment|/*&n; * The following is used with SIOCGIWPRIV. It allow a driver to define&n; * the interface (name, type of data) for its private ioctl.&n; * Privates ioctl are SIOCDEVPRIVATE -&gt; SIOCDEVPRIVATE + 0xF&n; */
DECL|macro|IW_PRIV_TYPE_MASK
mdefine_line|#define IW_PRIV_TYPE_MASK&t;0x7000&t;/* Type of arguments */
DECL|macro|IW_PRIV_TYPE_NONE
mdefine_line|#define IW_PRIV_TYPE_NONE&t;0x0000
DECL|macro|IW_PRIV_TYPE_BYTE
mdefine_line|#define IW_PRIV_TYPE_BYTE&t;0x1000&t;/* Char as number */
DECL|macro|IW_PRIV_TYPE_CHAR
mdefine_line|#define IW_PRIV_TYPE_CHAR&t;0x2000&t;/* Char as character */
DECL|macro|IW_PRIV_TYPE_INT
mdefine_line|#define IW_PRIV_TYPE_INT&t;0x4000&t;/* 32 bits int */
DECL|macro|IW_PRIV_TYPE_FLOAT
mdefine_line|#define IW_PRIV_TYPE_FLOAT&t;0x5000
DECL|macro|IW_PRIV_SIZE_FIXED
mdefine_line|#define IW_PRIV_SIZE_FIXED&t;0x0800&t;/* Variable or fixed nuber of args */
DECL|macro|IW_PRIV_SIZE_MASK
mdefine_line|#define IW_PRIV_SIZE_MASK&t;0x07FF&t;/* Max number of those args */
multiline_comment|/*&n; * Note : if the number of args is fixed and the size &lt; 16 octets,&n; * instead of passing a pointer we will put args in the iwreq struct...&n; */
multiline_comment|/* ----------------------- OTHER CONSTANTS ----------------------- */
multiline_comment|/* Maximum frequencies in the range struct */
DECL|macro|IW_MAX_FREQUENCIES
mdefine_line|#define IW_MAX_FREQUENCIES&t;16
multiline_comment|/* Note : if you have something like 80 frequencies,&n; * don&squot;t increase this constant and don&squot;t fill the frequency list.&n; * The user will be able to set by channel anyway... */
multiline_comment|/* Maximum of address that you may set with SPY */
DECL|macro|IW_MAX_SPY
mdefine_line|#define IW_MAX_SPY&t;&t;8
multiline_comment|/* Maximum of address that you may get in the&n;   list of access points in range */
DECL|macro|IW_MAX_AP
mdefine_line|#define IW_MAX_AP&t;&t;8
multiline_comment|/* Maximum size of the ESSID string */
DECL|macro|IW_ESSID_MAX_SIZE
mdefine_line|#define IW_ESSID_MAX_SIZE&t;32
multiline_comment|/****************************** TYPES ******************************/
multiline_comment|/* --------------------------- SUBTYPES --------------------------- */
multiline_comment|/*&n; *&t;A frequency&n; *&t;For numbers lower than 10^9, we encode the number in &squot;mant&squot; and&n; *&t;set &squot;exp&squot; to 0&n; *&t;For number greater than 10^9, we divide it by a power of 10.&n; *&t;The power of 10 is in &squot;exp&squot;, the result is in &squot;mant&squot;.&n; */
DECL|struct|iw_freq
r_struct
id|iw_freq
(brace
DECL|member|m
id|__u32
id|m
suffix:semicolon
multiline_comment|/* Mantissa */
DECL|member|e
id|__u16
id|e
suffix:semicolon
multiline_comment|/* Exponent */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Quality of the link&n; */
DECL|struct|iw_quality
r_struct
id|iw_quality
(brace
DECL|member|qual
id|__u8
id|qual
suffix:semicolon
multiline_comment|/* link quality (SNR or better...) */
DECL|member|level
id|__u8
id|level
suffix:semicolon
multiline_comment|/* signal level */
DECL|member|noise
id|__u8
id|noise
suffix:semicolon
multiline_comment|/* noise level */
DECL|member|updated
id|__u8
id|updated
suffix:semicolon
multiline_comment|/* Flags to know if updated */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Packet discarded in the wireless adapter due to&n; *&t;&quot;wireless&quot; specific problems...&n; */
DECL|struct|iw_discarded
r_struct
id|iw_discarded
(brace
DECL|member|nwid
id|__u32
id|nwid
suffix:semicolon
multiline_comment|/* Wrong nwid */
DECL|member|code
id|__u32
id|code
suffix:semicolon
multiline_comment|/* Unable to code/decode */
DECL|member|misc
id|__u32
id|misc
suffix:semicolon
multiline_comment|/* Others cases */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Encoding information (setting and so on)&n; *&t;Encoding might be hardware encryption, scrambing or others&n; */
DECL|struct|iw_encoding
r_struct
id|iw_encoding
(brace
DECL|member|method
id|__u8
id|method
suffix:semicolon
multiline_comment|/* Algorithm number / key used */
DECL|member|code
id|__u64
id|code
suffix:semicolon
multiline_comment|/* Data/key used for algorithm */
)brace
suffix:semicolon
multiline_comment|/* ------------------------ WIRELESS STATS ------------------------ */
multiline_comment|/*&n; * Wireless statistics (used for /proc/net/wireless)&n; */
DECL|struct|iw_statistics
r_struct
id|iw_statistics
(brace
DECL|member|status
id|__u8
id|status
suffix:semicolon
multiline_comment|/* Status&n;&t;&t;&t;&t;&t; * - device dependent for now */
DECL|member|qual
r_struct
id|iw_quality
id|qual
suffix:semicolon
multiline_comment|/* Quality of the link&n;&t;&t;&t;&t;&t;&t; * (instant/mean/max) */
DECL|member|discard
r_struct
id|iw_discarded
id|discard
suffix:semicolon
multiline_comment|/* Packet discarded counts */
)brace
suffix:semicolon
multiline_comment|/* ------------------------ IOCTL REQUEST ------------------------ */
multiline_comment|/*&n; * The structure to exchange data for ioctl.&n; * This structure is the same as &squot;struct ifreq&squot;, but (re)defined for&n; * convenience...&n; *&n; * Note that it should fit on the same memory footprint !&n; * You should check this when increasing the above structures (16 octets)&n; * 16 octets = 128 bits. Warning, pointers might be 64 bits wide...&n; */
DECL|struct|iwreq
r_struct
id|iwreq
(brace
r_union
(brace
DECL|member|ifrn_name
r_char
id|ifrn_name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* if name, e.g. &quot;en0&quot; */
DECL|member|ifr_ifrn
)brace
id|ifr_ifrn
suffix:semicolon
multiline_comment|/* Data part */
r_union
(brace
multiline_comment|/* Config - generic */
DECL|member|name
r_char
id|name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* Name : used to verify the presence of  wireless extensions.&n;&t;&t; * Name of the protocol/provider... */
r_struct
multiline_comment|/* network id (or domain) : used to to */
(brace
multiline_comment|/* create logical channels on the air */
DECL|member|nwid
id|__u32
id|nwid
suffix:semicolon
multiline_comment|/* value */
DECL|member|on
id|__u8
id|on
suffix:semicolon
multiline_comment|/* active/unactive nwid */
DECL|member|nwid
)brace
id|nwid
suffix:semicolon
DECL|member|freq
r_struct
id|iw_freq
id|freq
suffix:semicolon
multiline_comment|/* frequency or channel :&n;&t;&t;&t;&t;&t; * 0-1000 = channel&n;&t;&t;&t;&t;&t; * &gt; 1000 = frequency in Hz */
DECL|member|encoding
r_struct
id|iw_encoding
id|encoding
suffix:semicolon
multiline_comment|/* Encoding stuff */
DECL|member|sensitivity
id|__u32
id|sensitivity
suffix:semicolon
multiline_comment|/* signal level threshold */
DECL|member|ap_addr
r_struct
id|sockaddr
id|ap_addr
suffix:semicolon
multiline_comment|/* Access point address */
r_struct
multiline_comment|/* For all data bigger than 16 octets */
(brace
DECL|member|pointer
id|caddr_t
id|pointer
suffix:semicolon
multiline_comment|/* Pointer to the data&n;&t;&t;&t;&t;&t;&t; * (in user space) */
DECL|member|length
id|__u16
id|length
suffix:semicolon
multiline_comment|/* fields or byte size */
DECL|member|flags
id|__u16
id|flags
suffix:semicolon
multiline_comment|/* Optional params */
DECL|member|data
)brace
id|data
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* -------------------------- IOCTL DATA -------------------------- */
multiline_comment|/*&n; *&t;For those ioctl which want to exchange mode data that what could&n; *&t;fit in the above structure...&n; */
multiline_comment|/*&n; *&t;Range of parameters&n; */
DECL|struct|iw_range
r_struct
id|iw_range
(brace
multiline_comment|/* Informative stuff (to choose between different interface) */
DECL|member|throughput
id|__u32
id|throughput
suffix:semicolon
multiline_comment|/* To give an idea... */
multiline_comment|/* NWID (or domain id) */
DECL|member|min_nwid
id|__u32
id|min_nwid
suffix:semicolon
multiline_comment|/* Minimal NWID we are able to set */
DECL|member|max_nwid
id|__u32
id|max_nwid
suffix:semicolon
multiline_comment|/* Maximal NWID we are able to set */
multiline_comment|/* Frequency */
DECL|member|num_channels
id|__u16
id|num_channels
suffix:semicolon
multiline_comment|/* Number of channels [0; num - 1] */
DECL|member|num_frequency
id|__u8
id|num_frequency
suffix:semicolon
multiline_comment|/* Number of entry in the list */
DECL|member|freq
r_struct
id|iw_freq
id|freq
(braket
id|IW_MAX_FREQUENCIES
)braket
suffix:semicolon
multiline_comment|/* list */
multiline_comment|/* Note : this frequency list doesn&squot;t need to fit channel numbers */
multiline_comment|/* signal level threshold range */
DECL|member|sensitivity
id|__u32
id|sensitivity
suffix:semicolon
multiline_comment|/* Quality of link &amp; SNR stuff */
DECL|member|max_qual
r_struct
id|iw_quality
id|max_qual
suffix:semicolon
multiline_comment|/* Quality of the link */
multiline_comment|/* Encoder stuff */
DECL|member|max_encoding
r_struct
id|iw_encoding
id|max_encoding
suffix:semicolon
multiline_comment|/* Encoding max range */
)brace
suffix:semicolon
multiline_comment|/*&n; * Private ioctl interface information&n; */
DECL|struct|iw_priv_args
r_struct
id|iw_priv_args
(brace
DECL|member|cmd
id|__u32
id|cmd
suffix:semicolon
multiline_comment|/* Number of the ioctl to issue */
DECL|member|set_args
id|__u16
id|set_args
suffix:semicolon
multiline_comment|/* Type and number of args */
DECL|member|get_args
id|__u16
id|get_args
suffix:semicolon
multiline_comment|/* Type and number of args */
DECL|member|name
r_char
id|name
(braket
id|IFNAMSIZ
)braket
suffix:semicolon
multiline_comment|/* Name of the extension */
)brace
suffix:semicolon
macro_line|#endif&t;/* _LINUX_WIRELESS_H */
eof
