multiline_comment|/* $Id: byteorder.h,v 1.6 1995/11/25 02:31:20 davem Exp $ */
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
macro_line|#ifdef __KERNEL__
DECL|macro|__BIG_ENDIAN
mdefine_line|#define __BIG_ENDIAN
macro_line|#endif
DECL|macro|__BIG_ENDIAN_BITFIELD
mdefine_line|#define __BIG_ENDIAN_BITFIELD
macro_line|#endif /* !(_SPARC_BYTEORDER_H) */
eof
