macro_line|#ifndef __ALPHA_MMAN_H__
DECL|macro|__ALPHA_MMAN_H__
mdefine_line|#define __ALPHA_MMAN_H__
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
mdefine_line|#define MAP_TYPE&t;0x0f&t;&t;/* Mask for type of mapping (OSF/1 is _wrong_) */
DECL|macro|MAP_FIXED
mdefine_line|#define MAP_FIXED&t;0x100&t;&t;/* Interpret addr exactly */
DECL|macro|MAP_ANONYMOUS
mdefine_line|#define MAP_ANONYMOUS&t;0x10&t;&t;/* don&squot;t use a file */
multiline_comment|/* not used by linux, but here to make sure we don&squot;t clash with OSF/1 defines */
DECL|macro|MAP_HASSEMAPHORE
mdefine_line|#define MAP_HASSEMAPHORE 0x0200
DECL|macro|MAP_INHERIT
mdefine_line|#define MAP_INHERIT&t;0x0400
DECL|macro|MAP_UNALIGNED
mdefine_line|#define MAP_UNALIGNED&t;0x0800
multiline_comment|/* These are linux-specific */
DECL|macro|MAP_GROWSDOWN
mdefine_line|#define MAP_GROWSDOWN&t;0x1000&t;&t;/* stack-like segment */
DECL|macro|MAP_DENYWRITE
mdefine_line|#define MAP_DENYWRITE&t;0x2000&t;&t;/* ETXTBSY */
DECL|macro|MAP_EXECUTABLE
mdefine_line|#define MAP_EXECUTABLE&t;0x4000&t;&t;/* mark it as a executable */
DECL|macro|MS_ASYNC
mdefine_line|#define MS_ASYNC&t;1&t;&t;/* sync memory asynchronously */
DECL|macro|MS_SYNC
mdefine_line|#define MS_SYNC&t;&t;2&t;&t;/* synchronous memory sync */
DECL|macro|MS_INVALIDATE
mdefine_line|#define MS_INVALIDATE&t;4&t;&t;/* invalidate the caches */
macro_line|#endif /* __ALPHA_MMAN_H__ */
eof