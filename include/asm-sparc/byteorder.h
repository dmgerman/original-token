multiline_comment|/* $Id: byteorder.h,v 1.9 1996/08/30 05:21:34 davem Exp $ */
macro_line|#ifndef _SPARC_BYTEORDER_H
DECL|macro|_SPARC_BYTEORDER_H
mdefine_line|#define _SPARC_BYTEORDER_H
DECL|macro|ntohl
mdefine_line|#define ntohl(x) x
DECL|macro|ntohs
mdefine_line|#define ntohs(x) x
DECL|macro|htonl
mdefine_line|#define htonl(x) x
DECL|macro|htons
mdefine_line|#define htons(x) x
multiline_comment|/* Some programs depend upon these being around. */
DECL|macro|__constant_ntohl
mdefine_line|#define __constant_ntohl(x) x
DECL|macro|__constant_ntohs
mdefine_line|#define __constant_ntohs(x) x
DECL|macro|__constant_htonl
mdefine_line|#define __constant_htonl(x) x
DECL|macro|__constant_htons
mdefine_line|#define __constant_htons(x) x
macro_line|#ifndef __BIG_ENDIAN
DECL|macro|__BIG_ENDIAN
mdefine_line|#define __BIG_ENDIAN 4321
macro_line|#endif
macro_line|#ifndef __BIG_ENDIAN_BITFIELD
DECL|macro|__BIG_ENDIAN_BITFIELD
mdefine_line|#define __BIG_ENDIAN_BITFIELD
macro_line|#endif
macro_line|#endif /* !(_SPARC_BYTEORDER_H) */
eof
