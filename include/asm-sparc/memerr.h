macro_line|#ifndef _SPARC_MEMERR_H
DECL|macro|_SPARC_MEMERR_H
mdefine_line|#define _SPARC_MEMERR_H
multiline_comment|/* memerr.h:  Bit fields in the asynchronous and synchronous memory error&n; *            registers used to determine what &squot;type&squot; of error has just&n; *&t;      induced a trap.&n; *&n; * Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)&n; */
multiline_comment|/* synchronous error register fields come first... */
DECL|macro|SYNCER_WRITE
mdefine_line|#define SYNCER_WRITE    0x8000        /* write error...                               */
DECL|macro|SYNCER_INVAL
mdefine_line|#define SYNCER_INVAL    0x0080        /* invalid page access was attempted            */
DECL|macro|SYNCER_PROT
mdefine_line|#define SYNCER_PROT     0x0040        /* protection violation                         */
DECL|macro|SYNCER_TIMEOUT
mdefine_line|#define SYNCER_TIMEOUT  0x0020        /* mem-bus access timeout (mem does not exist). */
DECL|macro|SYNCER_SBUSERR
mdefine_line|#define SYNCER_SBUSERR  0x0010        /* same as above, but for an SBUS access        */
DECL|macro|SYNCER_MEMERR
mdefine_line|#define SYNCER_MEMERR   0x0008        /* Bus parity error, lose lose... panic time    */
DECL|macro|SYNCER_SZERR
mdefine_line|#define SYNCER_SZERR    0x0002        /* an attempted access was of BAD size, whoops  */
DECL|macro|SYNCER_WATCHDOG
mdefine_line|#define SYNCER_WATCHDOG 0x0001        /* although we never see these, the prom will.. */
multiline_comment|/* asynchronous error bits go here */
DECL|macro|ASYNCER_WBINVAL
mdefine_line|#define ASYNCER_WBINVAL   0x80        /* situation arose where the cache tried to write&n;                                       * back a page for which the valid bit was not set&n;&t;&t;&t;&t;       * within the mmu. This is due to bad mm kernel bugs.&n;&t;&t;&t;&t;       */
DECL|macro|ASYNCER_TIMEOUT
mdefine_line|#define ASYNCER_TIMEOUT   0x20        /* mem-access bus timeout... */
DECL|macro|ASYNCER_DVMAERR
mdefine_line|#define ASYNCER_DVMAERR   0x10        /* dvma transfer to/from memory bombed... */
macro_line|#endif /* _SPARC_MEMERR_H */
eof
