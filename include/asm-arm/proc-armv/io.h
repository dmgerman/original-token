multiline_comment|/*&n; * linux/include/asm-arm/proc-armv/io.h&n; */
multiline_comment|/*&n; * The caches on some architectures aren&squot;t dma-coherent and have need to&n; * handle this in software.  There are two types of operations that&n; * can be applied to dma buffers.&n; *&n; *  - dma_cache_wback_inv(start, size) makes caches and RAM coherent by&n; *    writing the content of the caches back to memory, if necessary.&n; *    The function also invalidates the affected part of the caches as&n; *    necessary before DMA transfers from outside to memory.&n; *  - dma_cache_inv(start, size) invalidates the affected parts of the&n; *    caches.  Dirty lines of the caches may be written back or simply&n; *    be discarded.  This operation is necessary before dma operations&n; *    to the memory.&n; *  - dma_cache_wback(start, size) writes back any dirty lines but does&n; *    not invalidate the cache.  This can be used before DMA reads from&n; *    memory,&n; */
macro_line|#include &lt;asm/proc-fns.h&gt;
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(_start,_size)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;processor.u.armv3v4._cache_purge_area(_start,(_start+_size));&t;&bslash;&n;&t;} while (0)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(_start,_size)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;processor.u.armv3v4._cache_wback_area(_start,(_start+_size));&t;&bslash;&n;&t;} while (0)
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(_start,_size)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;processor.u.armv3v4._flush_cache_area(_start,(_start+_size),0);&t;&bslash;&n;&t;} while (0)
eof
