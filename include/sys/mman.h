macro_line|#ifndef _MMAN_H
DECL|macro|_MMAN_H
mdefine_line|#define _MMAN_H
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
r_extern
id|caddr_t
id|mmap
c_func
(paren
id|caddr_t
id|addr
comma
r_int
id|len
comma
r_int
id|prot
comma
r_int
id|flags
comma
r_int
id|fd
comma
id|off_t
id|off
)paren
suffix:semicolon
r_extern
r_int
id|munmap
c_func
(paren
id|caddr_t
id|addr
comma
r_int
id|len
)paren
suffix:semicolon
macro_line|#endif /* _MMAN_H */
eof
