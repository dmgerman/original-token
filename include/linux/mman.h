macro_line|#ifndef _LINUX_MMAN_H
DECL|macro|_LINUX_MMAN_H
mdefine_line|#define _LINUX_MMAN_H
DECL|macro|PROT_READ
mdefine_line|#define PROT_READ        0x1       /* page can be read */
DECL|macro|PROT_WRITE
mdefine_line|#define PROT_WRITE       0x2       /* page can be written */
DECL|macro|PROT_EXEC
mdefine_line|#define PROT_EXEC        0x4       /* page can be executed */
DECL|macro|PROT_NONE
mdefine_line|#define PROT_NONE        0x0       /* page can not be accessed */
DECL|macro|MAP_SHARED
mdefine_line|#define MAP_SHARED       1         /* Share changes */
DECL|macro|MAP_PRIVATE
mdefine_line|#define MAP_PRIVATE      2         /* Changes are private */
DECL|macro|MAP_TYPE
mdefine_line|#define MAP_TYPE         0xf       /* Mask for type of mapping */
DECL|macro|MAP_FIXED
mdefine_line|#define MAP_FIXED        0x10      /* Interpret addr exactly */
DECL|macro|MAP_ANONYMOUS
mdefine_line|#define MAP_ANONYMOUS    0x20      /* don&squot;t use a file */
DECL|macro|MAP_GROWSDOWN
mdefine_line|#define MAP_GROWSDOWN&t;0x0100&t;&t;/* stack-like segment */
DECL|macro|MAP_DENYWRITE
mdefine_line|#define MAP_DENYWRITE&t;0x0800&t;&t;/* ETXTBSY */
DECL|macro|MAP_EXECUTABLE
mdefine_line|#define MAP_EXECUTABLE&t;0x1000&t;&t;/* mark it as a executable */
DECL|macro|MS_ASYNC
mdefine_line|#define MS_ASYNC&t;1&t;/* sync memory asynchronously */
DECL|macro|MS_INVALIDATE
mdefine_line|#define MS_INVALIDATE&t;2&t;/* invalidate the caches */
DECL|macro|MS_SYNC
mdefine_line|#define MS_SYNC&t;&t;4&t;/* synchronous memory sync */
macro_line|#endif /* _LINUX_MMAN_H */
eof
