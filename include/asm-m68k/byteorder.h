macro_line|#ifndef _M68K_BYTEORDER_H
DECL|macro|_M68K_BYTEORDER_H
mdefine_line|#define _M68K_BYTEORDER_H
macro_line|#ifdef __KERNEL__
DECL|macro|__BIG_ENDIAN
mdefine_line|#define __BIG_ENDIAN
macro_line|#endif
DECL|macro|__BIG_ENDIAN_BITFIELD
mdefine_line|#define __BIG_ENDIAN_BITFIELD
DECL|macro|ntohl
mdefine_line|#define ntohl(x) x
DECL|macro|ntohs
mdefine_line|#define ntohs(x) x
DECL|macro|htonl
mdefine_line|#define htonl(x) x
DECL|macro|htons
mdefine_line|#define htons(x) x
macro_line|#endif
eof
