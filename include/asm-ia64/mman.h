macro_line|#ifndef _ASM_IA64_MMAN_H
DECL|macro|_ASM_IA64_MMAN_H
mdefine_line|#define _ASM_IA64_MMAN_H
multiline_comment|/*&n; * Copyright (C) 1998, 1999 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
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
DECL|macro|MAP_GROWSDOWN
mdefine_line|#define MAP_GROWSDOWN&t;0x0100&t;&t;/* stack-like segment */
DECL|macro|MAP_GROWSUP
mdefine_line|#define MAP_GROWSUP&t;0x0200&t;&t;/* register stack-like segment */
DECL|macro|MAP_DENYWRITE
mdefine_line|#define MAP_DENYWRITE&t;0x0800&t;&t;/* ETXTBSY */
DECL|macro|MAP_EXECUTABLE
mdefine_line|#define MAP_EXECUTABLE&t;0x1000&t;&t;/* mark it as an executable */
DECL|macro|MAP_LOCKED
mdefine_line|#define MAP_LOCKED&t;0x2000&t;&t;/* pages are locked */
DECL|macro|MAP_NORESERVE
mdefine_line|#define MAP_NORESERVE&t;0x4000&t;&t;/* don&squot;t check for reservations */
DECL|macro|MS_ASYNC
mdefine_line|#define MS_ASYNC&t;1&t;&t;/* sync memory asynchronously */
DECL|macro|MS_INVALIDATE
mdefine_line|#define MS_INVALIDATE&t;2&t;&t;/* invalidate the caches */
DECL|macro|MS_SYNC
mdefine_line|#define MS_SYNC&t;&t;4&t;&t;/* synchronous memory sync */
DECL|macro|MCL_CURRENT
mdefine_line|#define MCL_CURRENT&t;1&t;&t;/* lock all current mappings */
DECL|macro|MCL_FUTURE
mdefine_line|#define MCL_FUTURE&t;2&t;&t;/* lock all future mappings */
multiline_comment|/* compatibility flags */
DECL|macro|MAP_ANON
mdefine_line|#define MAP_ANON&t;MAP_ANONYMOUS
DECL|macro|MAP_FILE
mdefine_line|#define MAP_FILE&t;0
macro_line|#endif /* _ASM_IA64_MMAN_H */
eof
