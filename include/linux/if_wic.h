macro_line|#ifndef _LINUX_IF_WIC_H
DECL|macro|_LINUX_IF_WIC_H
mdefine_line|#define _LINUX_IF_WIC_H
macro_line|#include &lt;linux/sockios.h&gt;
DECL|macro|SIOCDEVWIC
mdefine_line|#define&t;SIOCDEVWIC&t;SIOCDEVPRIVATE
DECL|struct|wicconf
r_struct
id|wicconf
(brace
DECL|member|pcmd
r_int
r_char
id|pcmd
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
l_int|120
)braket
suffix:semicolon
DECL|member|len
r_int
r_char
id|len
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* WIC host to controller commands */
DECL|macro|WIC_AYT
mdefine_line|#define WIC_AYT&t;&t;0x10&t;/* test dki */
DECL|macro|WIC_RESET
mdefine_line|#define WIC_RESET&t;0x11&t;/* reset controller */
DECL|macro|WIC_SETSN
mdefine_line|#define WIC_SETSN&t;0x21&t;/* set station name */
DECL|macro|WIC_SETPS
mdefine_line|#define WIC_SETPS&t;0x22&t;/* set power saving mode */
DECL|macro|WIC_SETAF
mdefine_line|#define WIC_SETAF&t;0x23&t;/* set announce filter */
DECL|macro|WIC_SETGPF
mdefine_line|#define WIC_SETGPF&t;0x24&t;/* set GPSP filter */
DECL|macro|WIC_GETVERH
mdefine_line|#define WIC_GETVERH&t;0x61&t;/* get interface controller version */
DECL|macro|WIC_GETNL
mdefine_line|#define WIC_GETNL&t;0x62&t;/* get neighbor list */
DECL|macro|WIC_GETSN
mdefine_line|#define WIC_GETSN&t;0x65&t;/* get station name */
DECL|macro|WIC_CLRSTATS
mdefine_line|#define WIC_CLRSTATS&t;0x83&t;/* clear controller statistics */
DECL|macro|WIC_SETNET
mdefine_line|#define WIC_SETNET&t;0x84&t;/* set network configuration */
DECL|macro|WIC_SETSYS
mdefine_line|#define WIC_SETSYS&t;0x85&t;/* set system configuration */
DECL|macro|WIC_GETSTATS
mdefine_line|#define WIC_GETSTATS&t;0xc1&t;/* get statistics */
DECL|macro|WIC_GETVERM
mdefine_line|#define WIC_GETVERM&t;0xc3&t;/* get MAC version */
DECL|macro|WIC_GETNET
mdefine_line|#define WIC_GETNET&t;0xc4&t;/* get network configuration */
DECL|macro|WIC_GETSYS
mdefine_line|#define WIC_GETSYS&t;0xc5&t;/* get system configuration */
multiline_comment|/*&n; * structure used for the GETNET/SETNET command&n; */
DECL|struct|wic_net
r_struct
id|wic_net
(brace
DECL|member|ula
r_int
r_char
id|ula
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* ula of interface */
DECL|member|mode
r_int
r_char
id|mode
suffix:semicolon
multiline_comment|/* operating mode */
DECL|macro|NET_MODE_ME
mdefine_line|#define NET_MODE_ME&t;&t;0x01&t;/* receive my ula */
DECL|macro|NET_MODE_BCAST
mdefine_line|#define NET_MODE_BCAST&t;&t;0x02&t;/* receive bcasts */
DECL|macro|NET_MODE_MCAST
mdefine_line|#define NET_MODE_MCAST&t;&t;0x04&t;/* receive mcasts */
DECL|macro|NET_MODE_PROM
mdefine_line|#define NET_MODE_PROM&t;&t;0x08&t;/* promiscuous */
DECL|macro|NET_MODE_HC
mdefine_line|#define NET_MODE_HC&t;&t;0x10&t;/* is a hop coordinator */
DECL|macro|NET_MODE_HC_VALID
mdefine_line|#define NET_MODE_HC_VALID&t;0x20&t;/* hc address is valid */
DECL|macro|NET_MODE_HCAP
mdefine_line|#define NET_MODE_HCAP&t;&t;0x40&t;/* hc is also ap */
DECL|macro|NET_MODE_HC_KNOWN
mdefine_line|#define NET_MODE_HC_KNOWN&t;0x80&t;/* hc is known */
DECL|member|rts_lo
r_int
r_char
id|rts_lo
suffix:semicolon
multiline_comment|/* rts threshold */
DECL|member|rts_hi
r_int
r_char
id|rts_hi
suffix:semicolon
multiline_comment|/* rts threshold */
DECL|member|retry
r_int
r_char
id|retry
suffix:semicolon
multiline_comment|/* retry limit */
DECL|member|hc_ula
r_int
r_char
id|hc_ula
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* ula of hc */
DECL|member|key
r_int
r_char
id|key
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* network key */
DECL|member|dsl
r_int
r_char
id|dsl
suffix:semicolon
multiline_comment|/* direct send limit */
DECL|member|res1
r_int
r_char
id|res1
suffix:semicolon
multiline_comment|/* reserved */
)brace
suffix:semicolon
multiline_comment|/*&n; * structure used for the GETSYS/SETSYS command &n; */
DECL|struct|wic_sys
r_struct
id|wic_sys
(brace
DECL|member|mode
r_int
r_char
id|mode
suffix:semicolon
multiline_comment|/* set operating mode */
DECL|macro|SYS_MODE_ANT_DIV
mdefine_line|#define SYS_MODE_ANT_DIV&t;0x00&t;/* use antenna diversity */
DECL|macro|SYS_MODE_ANT_1
mdefine_line|#define SYS_MODE_ANT_1&t;&t;0x01&t;/* use ant 1 for tx */
DECL|macro|SYS_MODE_ANT_2
mdefine_line|#define SYS_MODE_ANT_2&t;&t;0x02&t;/* use ant 2 for tx */
DECL|macro|SYS_MODE_HC_LOCK
mdefine_line|#define SYS_MODE_HC_LOCK&t;0x04&t;/* lock onto current hc */
DECL|macro|SYS_MODE_DEBUG
mdefine_line|#define SYS_MODE_DEBUG&t;&t;0x08&t;/* upload failed frames */
DECL|macro|SYS_MODE_IAM_AP
mdefine_line|#define SYS_MODE_IAM_AP&t;&t;0x10&t;/* I am AP */
DECL|macro|SYS_MODE_IAM_HC
mdefine_line|#define SYS_MODE_IAM_HC&t;&t;0x20&t;/* I am HC */
DECL|macro|SYS_MODE_USE_SKIP
mdefine_line|#define SYS_MODE_USE_SKIP&t;0x40&t;/* use skipping mechanism */
DECL|macro|SYS_MODE_AUTO
mdefine_line|#define SYS_MODE_AUTO&t;&t;0x80&t;/* station is in auto mode */
DECL|member|switches
r_int
r_char
id|switches
suffix:semicolon
multiline_comment|/* radio/controller switches */
DECL|macro|SYS_SWITCH_STDBY
mdefine_line|#define SYS_SWITCH_STDBY&t;0x01&t;/* switch radio to standby */
DECL|macro|SYS_SWITCH_TXRX
mdefine_line|#define SYS_SWITCH_TXRX&t;&t;0x02&t;/* 1 = tx, manual mode only */
DECL|macro|SYS_SWITCH_PA
mdefine_line|#define SYS_SWITCH_PA&t;&t;0x04&t;/* 1 = enable PA on radio */
DECL|macro|SYS_SWITCH_PWR
mdefine_line|#define SYS_SWITCH_PWR&t;&t;0x10&t;/* 1 = hi, 0 = lo power output */
DECL|macro|SYS_SWITCH_RES1
mdefine_line|#define SYS_SWITCH_RES1&t;&t;0x20&t;/* reserved, must be 0 */
DECL|macro|SYS_SWITCH_LIGHTS
mdefine_line|#define SYS_SWITCH_LIGHTS&t;0x40&t;/* light for tx &amp; rx */
DECL|macro|SYS_SWITCH_LIGHTS_HC
mdefine_line|#define SYS_SWITCH_LIGHTS_HC&t;0x80&t;/* light for rx while coordinated */
DECL|member|hop_min
r_int
r_char
id|hop_min
suffix:semicolon
multiline_comment|/* hop range */
DECL|member|hop_max
r_int
r_char
id|hop_max
suffix:semicolon
multiline_comment|/* hop range */
DECL|member|pre_len
r_int
r_char
id|pre_len
suffix:semicolon
multiline_comment|/* preamble length (bytes) */
DECL|member|pre_match
r_int
r_char
id|pre_match
suffix:semicolon
multiline_comment|/* valid preamble match (bytes) */
DECL|member|mod
r_int
r_char
id|mod
suffix:semicolon
multiline_comment|/* data mod: 1 = 8:1, 0 = none */
DECL|member|cca_mode
r_int
r_char
id|cca_mode
suffix:semicolon
multiline_comment|/* cca flags */
DECL|macro|CCA_PKT_DET_BSY
mdefine_line|#define CCA_PKT_DET_BSY&t;&t;0x01&t;/* busy if packet is detected */
DECL|macro|CCA_VIRT_CARR
mdefine_line|#define CCA_VIRT_CARR&t;&t;0x02&t;/* use virtual carrier */
DECL|macro|CCA_RSSI_BSY
mdefine_line|#define CCA_RSSI_BSY&t;&t;0x04&t;/* busy if rssi &gt; threshold */
DECL|macro|CCA_DATA_BSY
mdefine_line|#define CCA_DATA_BSY&t;&t;0x08&t;/* busy if valid data &gt; XXX usec */
DECL|member|dwell_hi
r_int
r_char
id|dwell_hi
suffix:semicolon
multiline_comment|/* dwell time */
DECL|member|dwell_lo
r_int
r_char
id|dwell_lo
suffix:semicolon
multiline_comment|/* dwell time */
DECL|member|hc_timeout
r_int
r_char
id|hc_timeout
suffix:semicolon
multiline_comment|/* HC timeout */
DECL|member|rssi
r_int
r_char
id|rssi
suffix:semicolon
multiline_comment|/* rssi threshold */
DECL|member|hc_rssi
r_int
r_char
id|hc_rssi
suffix:semicolon
multiline_comment|/* rssi of last hc frame */
DECL|member|hc_rssi_chan
r_int
r_char
id|hc_rssi_chan
suffix:semicolon
multiline_comment|/* channel of hc rssi value */
)brace
suffix:semicolon
macro_line|#endif /* _LINUX_IF_WIC_H */
eof
