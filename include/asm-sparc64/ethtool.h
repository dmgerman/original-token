multiline_comment|/* $Id: ethtool.h,v 1.1 1998/12/19 15:09:40 davem Exp $&n; * ethtool.h: Defines for SparcLinux ethtool.&n; *&n; * Copyright (C) 1998 David S. Miller (davem@dm.cobaltmicro.com)&n; */
macro_line|#ifndef _SPARC64_ETHTOOL_H
DECL|macro|_SPARC64_ETHTOOL_H
mdefine_line|#define _SPARC64_ETHTOOL_H
multiline_comment|/* We do things like this so it does not matter what kernel&n; * headers you have on your system etc.&n; */
DECL|macro|SIOCETHTOOL
macro_line|#undef SIOCETHTOOL
DECL|macro|SIOCETHTOOL
mdefine_line|#define SIOCETHTOOL&t;(SIOCDEVPRIVATE + 0x0f)
multiline_comment|/* This should work for both 32 and 64 bit userland. */
DECL|struct|ethtool_cmd
r_struct
id|ethtool_cmd
(brace
DECL|member|cmd
id|u32
id|cmd
suffix:semicolon
DECL|member|supported
id|u32
id|supported
suffix:semicolon
DECL|member|speed
id|u16
id|speed
suffix:semicolon
DECL|member|duplex
id|u8
id|duplex
suffix:semicolon
DECL|member|port
id|u8
id|port
suffix:semicolon
DECL|member|phy_address
id|u8
id|phy_address
suffix:semicolon
DECL|member|transceiver
id|u8
id|transceiver
suffix:semicolon
DECL|member|autoneg
id|u8
id|autoneg
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* CMDs currently supported */
DECL|macro|SPARC_ETH_GSET
mdefine_line|#define SPARC_ETH_GSET&t;&t;0x00000001&t;/* Get settings, non-privileged. */
DECL|macro|SPARC_ETH_SSET
mdefine_line|#define SPARC_ETH_SSET&t;&t;0x00000002&t;/* Set settings, privileged. */
multiline_comment|/* Indicates what features are supported by the interface. */
DECL|macro|SUPPORTED_10baseT_Half
mdefine_line|#define SUPPORTED_10baseT_Half&t;&t;0x00000001
DECL|macro|SUPPORTED_10baseT_Full
mdefine_line|#define SUPPORTED_10baseT_Full&t;&t;0x00000002
DECL|macro|SUPPORTED_100baseT_Half
mdefine_line|#define SUPPORTED_100baseT_Half&t;&t;0x00000004
DECL|macro|SUPPORTED_100baseT_Full
mdefine_line|#define SUPPORTED_100baseT_Full&t;&t;0x00000008
DECL|macro|SUPPORTED_1000baseT_Half
mdefine_line|#define SUPPORTED_1000baseT_Half&t;0x00000010
DECL|macro|SUPPORTED_1000baseT_Full
mdefine_line|#define SUPPORTED_1000baseT_Full&t;0x00000020
DECL|macro|SUPPORTED_Autoneg
mdefine_line|#define SUPPORTED_Autoneg&t;&t;0x00000040
DECL|macro|SUPPORTED_TP
mdefine_line|#define SUPPORTED_TP&t;&t;&t;0x00000080
DECL|macro|SUPPORTED_AUI
mdefine_line|#define SUPPORTED_AUI&t;&t;&t;0x00000100
DECL|macro|SUPPORTED_MII
mdefine_line|#define SUPPORTED_MII&t;&t;&t;0x00000200
DECL|macro|SUPPORTED_FIBRE
mdefine_line|#define SUPPORTED_FIBRE&t;&t;&t;0x00000400
multiline_comment|/* The following are all involved in forcing a particular link&n; * mode for the device for setting things.  When getting the&n; * devices settings, these indicate the current mode and whether&n; * it was foced up into this mode or autonegotiated.&n; */
multiline_comment|/* The forced speec, 10Mb, 100Mb, gigabit. */
DECL|macro|SPEED_10
mdefine_line|#define SPEED_10&t;&t;10
DECL|macro|SPEED_100
mdefine_line|#define SPEED_100&t;&t;100
DECL|macro|SPEED_1000
mdefine_line|#define SPEED_1000&t;&t;1000
multiline_comment|/* Duplex, half or full. */
DECL|macro|DUPLEX_HALF
mdefine_line|#define DUPLEX_HALF&t;&t;0x00
DECL|macro|DUPLEX_FULL
mdefine_line|#define DUPLEX_FULL&t;&t;0x01
multiline_comment|/* Which connector port. */
DECL|macro|PORT_TP
mdefine_line|#define PORT_TP&t;&t;&t;0x00
DECL|macro|PORT_AUI
mdefine_line|#define PORT_AUI&t;&t;0x01
DECL|macro|PORT_MII
mdefine_line|#define PORT_MII&t;&t;0x02
DECL|macro|PORT_FIBRE
mdefine_line|#define PORT_FIBRE&t;&t;0x03
multiline_comment|/* Which tranceiver to use. */
DECL|macro|XCVR_INTERNAL
mdefine_line|#define XCVR_INTERNAL&t;&t;0x00
DECL|macro|XCVR_EXTERNAL
mdefine_line|#define XCVR_EXTERNAL&t;&t;0x01
DECL|macro|XCVR_DUMMY1
mdefine_line|#define XCVR_DUMMY1&t;&t;0x02
DECL|macro|XCVR_DUMMY2
mdefine_line|#define XCVR_DUMMY2&t;&t;0x03
DECL|macro|XCVR_DUMMY3
mdefine_line|#define XCVR_DUMMY3&t;&t;0x04
multiline_comment|/* Enable or disable autonegotiation.  If this is set to enable,&n; * the forced link modes above are completely ignored.&n; */
DECL|macro|AUTONEG_DISABLE
mdefine_line|#define AUTONEG_DISABLE&t;&t;0x00
DECL|macro|AUTONEG_ENABLE
mdefine_line|#define AUTONEG_ENABLE&t;&t;0x01
macro_line|#endif /* _SPARC64_ETHTOOL_H */
eof
