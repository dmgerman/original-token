multiline_comment|/* net/atm/tunable.h - Tunable parameters of ATM support */
multiline_comment|/* Written 1995-1999 by Werner Almesberger, EPFL LRC/ICA */
macro_line|#ifndef NET_ATM_TUNABLE_H
DECL|macro|NET_ATM_TUNABLE_H
mdefine_line|#define NET_ATM_TUNABLE_H
DECL|macro|ATM_RXBQ_DEF
mdefine_line|#define ATM_RXBQ_DEF&t;(  64*1024)  /* default RX buffer quota, in bytes */
DECL|macro|ATM_TXBQ_DEF
mdefine_line|#define ATM_TXBQ_DEF&t;(  64*1024)  /* default TX buffer quota, in bytes */
DECL|macro|ATM_RXBQ_MIN
mdefine_line|#define ATM_RXBQ_MIN&t;(   1*1024)  /* RX buffer minimum, in bytes */
DECL|macro|ATM_TXBQ_MIN
mdefine_line|#define ATM_TXBQ_MIN&t;(   1*1024)  /* TX buffer minimum, in bytes */
DECL|macro|ATM_RXBQ_MAX
mdefine_line|#define ATM_RXBQ_MAX&t;(1024*1024)  /* RX buffer quota limit, in bytes */
DECL|macro|ATM_TXBQ_MAX
mdefine_line|#define ATM_TXBQ_MAX&t;(1024*1024)  /* TX buffer quota limit, in bytes */
macro_line|#endif
eof
