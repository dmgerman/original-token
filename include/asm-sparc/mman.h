multiline_comment|/* $Id: mman.h,v 1.9 2000/03/15 02:44:23 davem Exp $ */
macro_line|#ifndef __SPARC_MMAN_H__
DECL|macro|__SPARC_MMAN_H__
mdefine_line|#define __SPARC_MMAN_H__
multiline_comment|/* SunOS&squot;ified... */
DECL|macro|PROT_READ
mdefine_line|#define PROT_READ&t;0x1&t;&t;/* page can be read */
DECL|macro|PROT_WRITE
mdefine_line|#define PROT_WRITE&t;0x2&t;&t;/* page can be written */
DECL|macro|PROT_EXEC
mdefine_line|#define PROT_EXEC&t;0x4&t;&t;/* page can be executed */
DECL|macro|PROT_NONE
mdefine_line|#define PROT_NONE&t;0x0&t;&t;/* page can not be accessed */
DECL|macro|MAP_SHARED
mdefine_line|#define MAP_SHARED&t;0x01&t;&t;/* Share changes */
DECL|macro|MAP_PRIVATE
mdefine_line|#define MAP_PRIVATE&t;0x02&t;&t;/* Changes are private */
DECL|macro|MAP_TYPE
mdefine_line|#define MAP_TYPE&t;0x0f&t;&t;/* Mask for type of mapping */
DECL|macro|MAP_FIXED
mdefine_line|#define MAP_FIXED&t;0x10&t;&t;/* Interpret addr exactly */
DECL|macro|MAP_ANONYMOUS
mdefine_line|#define MAP_ANONYMOUS&t;0x20&t;&t;/* don&squot;t use a file */
DECL|macro|MAP_RENAME
mdefine_line|#define MAP_RENAME      MAP_ANONYMOUS   /* In SunOS terminology */
DECL|macro|MAP_NORESERVE
mdefine_line|#define MAP_NORESERVE   0x40            /* don&squot;t reserve swap pages */
DECL|macro|MAP_INHERIT
mdefine_line|#define MAP_INHERIT     0x80            /* SunOS doesn&squot;t do this, but... */
DECL|macro|MAP_LOCKED
mdefine_line|#define MAP_LOCKED      0x100           /* lock the mapping */
DECL|macro|_MAP_NEW
mdefine_line|#define _MAP_NEW        0x80000000      /* Binary compatibility is fun... */
DECL|macro|MAP_GROWSDOWN
mdefine_line|#define MAP_GROWSDOWN&t;0x0100&t;&t;/* stack-like segment */
DECL|macro|MAP_DENYWRITE
mdefine_line|#define MAP_DENYWRITE&t;0x0800&t;&t;/* ETXTBSY */
DECL|macro|MAP_EXECUTABLE
mdefine_line|#define MAP_EXECUTABLE&t;0x1000&t;&t;/* mark it as an executable */
DECL|macro|MS_ASYNC
mdefine_line|#define MS_ASYNC&t;1&t;&t;/* sync memory asynchronously */
DECL|macro|MS_INVALIDATE
mdefine_line|#define MS_INVALIDATE&t;2&t;&t;/* invalidate the caches */
DECL|macro|MS_SYNC
mdefine_line|#define MS_SYNC&t;&t;4&t;&t;/* synchronous memory sync */
DECL|macro|MCL_CURRENT
mdefine_line|#define MCL_CURRENT     0x2000          /* lock all currently mapped pages */
DECL|macro|MCL_FUTURE
mdefine_line|#define MCL_FUTURE      0x4000          /* lock all additions to address space */
multiline_comment|/* XXX Need to add flags to SunOS&squot;s mctl, mlockall, and madvise system&n; * XXX calls.&n; */
multiline_comment|/* SunOS sys_mctl() stuff... */
DECL|macro|MC_SYNC
mdefine_line|#define MC_SYNC         1  /* Sync pages in memory with storage (usu. a file) */
DECL|macro|MC_LOCK
mdefine_line|#define MC_LOCK         2  /* Lock pages into core ram, do not allow swapping of them */
DECL|macro|MC_UNLOCK
mdefine_line|#define MC_UNLOCK       3  /* Unlock pages locked via previous mctl() with MC_LOCK arg */
DECL|macro|MC_LOCKAS
mdefine_line|#define MC_LOCKAS       5  /* Lock an entire address space of the calling process */
DECL|macro|MC_UNLOCKAS
mdefine_line|#define MC_UNLOCKAS     6  /* Unlock entire address space of calling process */
DECL|macro|MADV_NORMAL
mdefine_line|#define MADV_NORMAL&t;0x0&t;&t;/* default page-in behavior */
DECL|macro|MADV_RANDOM
mdefine_line|#define MADV_RANDOM&t;0x1&t;&t;/* page-in minimum required */
DECL|macro|MADV_SEQUENTIAL
mdefine_line|#define MADV_SEQUENTIAL&t;0x2&t;&t;/* read-ahead aggressively */
DECL|macro|MADV_WILLNEED
mdefine_line|#define MADV_WILLNEED&t;0x3&t;&t;/* pre-fault pages */
DECL|macro|MADV_DONTNEED
mdefine_line|#define MADV_DONTNEED&t;0x4&t;&t;/* discard these pages */
DECL|macro|MADV_FREE
mdefine_line|#define MADV_FREE&t;0x5&t;&t;/* (Solaris) contents can be freed */
multiline_comment|/* compatibility flags */
DECL|macro|MAP_ANON
mdefine_line|#define MAP_ANON&t;MAP_ANONYMOUS
DECL|macro|MAP_FILE
mdefine_line|#define MAP_FILE&t;0
macro_line|#endif /* __SPARC_MMAN_H__ */
eof
