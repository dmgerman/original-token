multiline_comment|/* $Id */
macro_line|#ifndef _SPARC64_UPA_H
DECL|macro|_SPARC64_UPA_H
mdefine_line|#define _SPARC64_UPA_H
multiline_comment|/* UPA level registers and defines. */
multiline_comment|/* UPA Config Register */
DECL|macro|UPA_CONFIG_RESV
mdefine_line|#define UPA_CONFIG_RESV&t;&t;0xffffffffc0000000 /* Reserved.                    */
DECL|macro|UPA_CONFIG_PCON
mdefine_line|#define UPA_CONFIG_PCON&t;&t;0x000000003fc00000 /* Depth of various sys queues. */
DECL|macro|UPA_CONFIG_MID
mdefine_line|#define UPA_CONFIG_MID&t;&t;0x00000000003e0000 /* Module ID.                   */
DECL|macro|UPA_CONFIG_PCAP
mdefine_line|#define UPA_CONFIG_PCAP&t;&t;0x000000000001ffff /* Port Capabilities.           */
multiline_comment|/* UPA Port ID Register */
DECL|macro|UPA_PORTID_FNP
mdefine_line|#define UPA_PORTID_FNP&t;&t;0xff00000000000000 /* Hardcoded to 0xfc on ultra.  */
DECL|macro|UPA_PORTID_RESV
mdefine_line|#define UPA_PORTID_RESV&t;&t;0x00fffff800000000 /* Reserved.                    */
DECL|macro|UPA_PORTID_ECCVALID
mdefine_line|#define UPA_PORTID_ECCVALID     0x0000000400000000 /* Zero if mod can generate ECC */
DECL|macro|UPA_PORTID_ONEREAD
mdefine_line|#define UPA_PORTID_ONEREAD      0x0000000200000000 /* Set if mod generates P_RASB  */
DECL|macro|UPA_PORTID_PINTRDQ
mdefine_line|#define UPA_PORTID_PINTRDQ      0x0000000180000000 /* # outstanding P_INT_REQ&squot;s    */
DECL|macro|UPA_PORTID_PREQDQ
mdefine_line|#define UPA_PORTID_PREQDQ       0x000000007e000000 /* slave-wr&squot;s to mod supported  */
DECL|macro|UPA_PORTID_PREQRD
mdefine_line|#define UPA_PORTID_PREQRD       0x0000000001e00000 /* # incoming P_REQ&squot;s supported */
DECL|macro|UPA_PORTID_UPACAP
mdefine_line|#define UPA_PORTID_UPACAP       0x00000000001f0000 /* UPA capabilities of mod      */
DECL|macro|UPA_PORTID_ID
mdefine_line|#define UPA_PORTID_ID           0x000000000000ffff /* Module Indentification bits  */
macro_line|#endif /* !(_SPARC64_UPA_H) */
eof
