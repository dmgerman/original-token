macro_line|#ifndef _PPC_SHMPARAM_H
DECL|macro|_PPC_SHMPARAM_H
mdefine_line|#define _PPC_SHMPARAM_H
multiline_comment|/* address range for shared memory attaches if no address passed to shmat() */
DECL|macro|SHM_RANGE_START
mdefine_line|#define SHM_RANGE_START&t;0x50000000
DECL|macro|SHM_RANGE_END
mdefine_line|#define SHM_RANGE_END&t;0x60000000
multiline_comment|/*&n; * Format of a swap-entry for shared memory pages currently out in&n; * swap space (see also mm/swap.c).&n; *&n; * SWP_TYPE = SHM_SWP_TYPE&n; * SWP_OFFSET is used as follows:&n; *&n; *  bits 0..6 : id of shared memory segment page belongs to (SHM_ID)&n; *  bits 7..21: index of page within shared memory segment (SHM_IDX)&n; *&t;&t;(actually fewer bits get used since SHMMAX is so low)&n; */
multiline_comment|/*&n; * Keep _SHM_ID_BITS as low as possible since SHMMNI depends on it and&n; * there is a static array of size SHMMNI.&n; */
DECL|macro|_SHM_ID_BITS
mdefine_line|#define _SHM_ID_BITS&t;7
DECL|macro|SHM_ID_MASK
mdefine_line|#define SHM_ID_MASK&t;((1&lt;&lt;_SHM_ID_BITS)-1)
DECL|macro|SHM_IDX_SHIFT
mdefine_line|#define SHM_IDX_SHIFT&t;(_SHM_ID_BITS)
DECL|macro|_SHM_IDX_BITS
mdefine_line|#define _SHM_IDX_BITS&t;15
DECL|macro|SHM_IDX_MASK
mdefine_line|#define SHM_IDX_MASK&t;((1&lt;&lt;_SHM_IDX_BITS)-1)
multiline_comment|/*&n; * _SHM_ID_BITS + _SHM_IDX_BITS must be &lt;= 24 on the i386 and&n; * SHMMAX &lt;= (PAGE_SIZE &lt;&lt; _SHM_IDX_BITS).&n; */
DECL|macro|SHMMAX
mdefine_line|#define SHMMAX 0x2000000&t;&t;/* max shared seg size (bytes) */
DECL|macro|SHMMIN
mdefine_line|#define SHMMIN 1 /* really PAGE_SIZE */&t;/* min shared seg size (bytes) */
DECL|macro|SHMMNI
mdefine_line|#define SHMMNI (1&lt;&lt;_SHM_ID_BITS)&t;/* max num of segs system wide */
DECL|macro|SHMALL
mdefine_line|#define SHMALL&t;&t;&t;&t;/* max shm system wide (pages) */ &bslash;&n;&t;(1&lt;&lt;(_SHM_IDX_BITS+_SHM_ID_BITS))
DECL|macro|SHMLBA
mdefine_line|#define&t;SHMLBA PAGE_SIZE&t;&t;/* attach addr a multiple of this */
DECL|macro|SHMSEG
mdefine_line|#define SHMSEG SHMMNI&t;&t;&t;/* max shared segs per process */
macro_line|#endif /* _PPC_SHMPARAM_H */
eof
