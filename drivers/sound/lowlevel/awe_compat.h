multiline_comment|/*----------------------------------------------------------------&n; * compatibility macros for AWE32 driver&n; *----------------------------------------------------------------*/
multiline_comment|/* redefine following macros */
DECL|macro|IOCTL_IN
macro_line|#undef IOCTL_IN
DECL|macro|IOCTL_OUT
macro_line|#undef IOCTL_OUT
DECL|macro|OUTW
macro_line|#undef OUTW
DECL|macro|COPY_FROM_USER
macro_line|#undef COPY_FROM_USER
DECL|macro|COPY_TO_USER
macro_line|#undef COPY_TO_USER
DECL|macro|GET_BYTE_FROM_USER
macro_line|#undef GET_BYTE_FROM_USER
DECL|macro|GET_SHORT_FROM_USER
macro_line|#undef GET_SHORT_FROM_USER
DECL|macro|IOCTL_TO_USER
macro_line|#undef IOCTL_TO_USER
macro_line|#ifdef linux
multiline_comment|/*================================================================&n; * Linux macros&n; *================================================================*/
multiline_comment|/* use inline prefix */
DECL|macro|INLINE
mdefine_line|#define INLINE&t;inline
multiline_comment|/*----------------------------------------------------------------&n; * memory management for linux&n; *----------------------------------------------------------------*/
macro_line|#ifdef AWE_OBSOLETE_VOXWARE
multiline_comment|/* old type linux system */
multiline_comment|/* i/o requests; nothing */
DECL|macro|awe_check_port
mdefine_line|#define awe_check_port()&t;0&t;/* always false */
DECL|macro|awe_request_region
mdefine_line|#define awe_request_region()&t;/* nothing */
DECL|macro|awe_release_region
mdefine_line|#define awe_release_region()&t;/* nothing */
DECL|variable|_mem_start
r_static
r_int
id|_mem_start
suffix:semicolon
multiline_comment|/* memory pointer for permanent buffers */
DECL|macro|my_malloc_init
mdefine_line|#define my_malloc_init(memptr)&t;_mem_start = (memptr)
DECL|macro|my_malloc_memptr
mdefine_line|#define my_malloc_memptr()&t;_mem_start
DECL|macro|my_free
mdefine_line|#define my_free(ptr)&t;/* do nothing */
DECL|macro|my_realloc
mdefine_line|#define my_realloc(buf,oldsize,size)&t;NULL&t;/* no realloc */
DECL|function|my_malloc
r_static
r_void
op_star
id|my_malloc
c_func
(paren
r_int
id|size
)paren
(brace
r_char
op_star
id|ptr
suffix:semicolon
id|PERMANENT_MALLOC
c_func
(paren
id|ptr
comma
r_char
op_star
comma
id|size
comma
id|_mem_start
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|ptr
suffix:semicolon
)brace
multiline_comment|/* allocate buffer only once */
DECL|macro|INIT_TABLE
mdefine_line|#define INIT_TABLE(buffer,index,nums,type) {&bslash;&n;buffer = my_malloc(sizeof(type) * (nums)); index = (nums);&bslash;&n;}
macro_line|#else
DECL|macro|AWE_DYNAMIC_BUFFER
mdefine_line|#define AWE_DYNAMIC_BUFFER
DECL|macro|my_malloc_init
mdefine_line|#define my_malloc_init(ptr)&t;/* nothing */
DECL|macro|my_malloc_memptr
mdefine_line|#define my_malloc_memptr()&t;0
DECL|macro|my_malloc
mdefine_line|#define my_malloc(size)&t;&t;vmalloc(size)
DECL|macro|my_free
mdefine_line|#define my_free(ptr)&t;&t;if (ptr) {vfree(ptr);}
DECL|function|my_realloc
r_static
r_void
op_star
id|my_realloc
c_func
(paren
r_void
op_star
id|buf
comma
r_int
id|oldsize
comma
r_int
id|size
)paren
(brace
r_void
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ptr
op_assign
id|vmalloc
c_func
(paren
id|size
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|memcpy
c_func
(paren
id|ptr
comma
id|buf
comma
(paren
(paren
id|oldsize
OL
id|size
)paren
ques
c_cond
id|oldsize
suffix:colon
id|size
)paren
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|ptr
suffix:semicolon
)brace
multiline_comment|/* do not allocate buffer at beginning */
DECL|macro|INIT_TABLE
mdefine_line|#define INIT_TABLE(buffer,index,nums,type) {buffer=NULL; index=0;}
multiline_comment|/* old type macro */
DECL|macro|RET_ERROR
mdefine_line|#define RET_ERROR(err)&t;&t;-err
macro_line|#endif
multiline_comment|/*----------------------------------------------------------------&n; * i/o interfaces for linux&n; *----------------------------------------------------------------*/
DECL|macro|OUTW
mdefine_line|#define OUTW(data,addr)&t;&t;outw(data, addr)
macro_line|#ifdef AWE_NEW_KERNEL_INTERFACE
DECL|macro|COPY_FROM_USER
mdefine_line|#define COPY_FROM_USER(target,source,offs,count) &bslash;&n;&t;copy_from_user(target, (source)+(offs), count)
DECL|macro|GET_BYTE_FROM_USER
mdefine_line|#define GET_BYTE_FROM_USER(target,addr,offs) &bslash;&n;&t;get_user(target, (unsigned char*)&amp;((addr)[offs]))
DECL|macro|GET_SHORT_FROM_USER
mdefine_line|#define GET_SHORT_FROM_USER(target,addr,offs) &bslash;&n;&t;get_user(target, (unsigned short*)&amp;((addr)[offs]))
macro_line|#ifdef AWE_OSS38_AND_IM_A_BANANA
DECL|macro|IOCTL_TO_USER
mdefine_line|#define IOCTL_TO_USER(target,offs,source,count) &bslash;&n;&t;memcpy(target, (source)+(offs), count)
DECL|macro|IO_WRITE_CHECK
mdefine_line|#define IO_WRITE_CHECK(cmd)&t;(_SIOC_DIR(cmd) &amp; _IOC_WRITE)
macro_line|#else
DECL|macro|IOCTL_TO_USER
mdefine_line|#define IOCTL_TO_USER(target,offs,source,count) &bslash;&n;&t;copy_to_user(target, (source)+(offs), count)
DECL|macro|IO_WRITE_CHECK
mdefine_line|#define IO_WRITE_CHECK(cmd)&t;(_IOC_DIR(cmd) &amp; _IOC_WRITE)
macro_line|#endif /* AWE_OSS38 */
DECL|macro|COPY_TO_USER
mdefine_line|#define COPY_TO_USER&t;IOCTL_TO_USER
DECL|macro|IOCTL_IN
mdefine_line|#define IOCTL_IN(arg)&t;(*(int*)(arg))
DECL|macro|IOCTL_OUT
mdefine_line|#define IOCTL_OUT(arg,val) (*(int*)(arg) = (val))
macro_line|#else /* old type i/o */
DECL|macro|COPY_FROM_USER
mdefine_line|#define COPY_FROM_USER(target,source,offs,count) &bslash;&n;&t;memcpy_fromfs(target, (source)+(offs), (count))
DECL|macro|GET_BYTE_FROM_USER
mdefine_line|#define GET_BYTE_FROM_USER(target,addr,offs) &bslash;&n;&t;*((char  *)&amp;(target)) = get_fs_byte((addr)+(offs))
DECL|macro|GET_SHORT_FROM_USER
mdefine_line|#define GET_SHORT_FROM_USER(target,addr,offs) &bslash;&n;&t;*((short *)&amp;(target)) = get_fs_word((addr)+(offs))
DECL|macro|IOCTL_TO_USER
mdefine_line|#define IOCTL_TO_USER(target,offs,source,count) &bslash;&n;&t;memcpy_tofs(target, (source)+(offs), (count))
DECL|macro|COPY_TO_USER
mdefine_line|#define COPY_TO_USER&t;IOCTL_TO_USER
DECL|macro|IO_WRITE_CHECK
mdefine_line|#define IO_WRITE_CHECK(cmd)&t;(cmd &amp; IOC_IN)
DECL|macro|IOCTL_IN
mdefine_line|#define IOCTL_IN(arg)&t;&t;get_fs_long((long *)(arg))
DECL|macro|IOCTL_OUT
mdefine_line|#define IOCTL_OUT(arg,ret)&t;snd_ioctl_return((int *)arg, ret)
macro_line|#endif /* AWE_NEW_KERNEL_INTERFACE */
DECL|macro|BZERO
mdefine_line|#define BZERO(target,len)&t;memset(target, 0, len)
DECL|macro|MEMCPY
mdefine_line|#define MEMCPY(dst,src,len)&t;memcpy(dst, src, len)
macro_line|#elif defined(__FreeBSD__)
multiline_comment|/*================================================================&n; * FreeBSD macros&n; *================================================================*/
multiline_comment|/* inline is not checked yet.. maybe it&squot;ll work */
DECL|macro|INLINE
mdefine_line|#define INLINE&t;/*inline*/
multiline_comment|/*----------------------------------------------------------------&n; * memory management for freebsd&n; *----------------------------------------------------------------*/
multiline_comment|/* i/o requests; nothing */
DECL|macro|awe_check_port
mdefine_line|#define awe_check_port()&t;0&t;/* always false */
DECL|macro|awe_request_region
mdefine_line|#define awe_request_region()&t;/* nothing */
DECL|macro|awe_release_region
mdefine_line|#define awe_release_region()&t;/* nothing */
DECL|macro|AWE_DYNAMIC_BUFFER
mdefine_line|#define AWE_DYNAMIC_BUFFER
DECL|macro|my_malloc_init
mdefine_line|#define my_malloc_init(ptr)&t;/* nothing */
DECL|macro|my_malloc_memptr
mdefine_line|#define my_malloc_memptr()&t;0
DECL|macro|my_malloc
mdefine_line|#define my_malloc(size)&t;&t;malloc(size, M_TEMP, M_WAITOK)
DECL|macro|my_free
mdefine_line|#define my_free(ptr)&t;&t;if (ptr) {free(ptr, M_TEMP);}
DECL|macro|INIT_TABLE
mdefine_line|#define INIT_TABLE(buffer,index,nums,type) {buffer=NULL; index=0;}
multiline_comment|/* it should be realloc? */
DECL|function|my_realloc
r_static
r_void
op_star
id|my_realloc
c_func
(paren
r_void
op_star
id|buf
comma
r_int
id|oldsize
comma
r_int
id|size
)paren
(brace
r_void
op_star
id|ptr
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ptr
op_assign
id|my_malloc
c_func
(paren
id|size
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
id|memcpy
c_func
(paren
id|ptr
comma
id|buf
comma
(paren
(paren
id|oldsize
OL
id|size
)paren
ques
c_cond
id|oldsize
suffix:colon
id|size
)paren
)paren
suffix:semicolon
id|my_free
c_func
(paren
id|buf
)paren
suffix:semicolon
r_return
id|ptr
suffix:semicolon
)brace
multiline_comment|/*----------------------------------------------------------------&n; * i/o interfaces for freebsd&n; *----------------------------------------------------------------*/
multiline_comment|/* according to linux rule; the arguments are swapped */
DECL|macro|OUTW
mdefine_line|#define OUTW(data,addr)&t;&t;outw(addr, data)
DECL|macro|COPY_FROM_USER
mdefine_line|#define COPY_FROM_USER(target,source,offs,count) &bslash;&n;&t;uiomove(((caddr_t)(target)),(count),((struct uio *)(source)))
DECL|macro|COPY_TO_USER
mdefine_line|#define COPY_TO_USER(target,source,offs,count) &bslash;&n;&t;uiomove(((caddr_t)(source)),(count),((struct uio *)(target)))
DECL|macro|GET_BYTE_FROM_USER
mdefine_line|#define GET_BYTE_FROM_USER(target,addr,offs) &bslash;&n;&t;uiomove(((char*)&amp;(target)), 1, ((struct uio *)(addr)))
DECL|macro|GET_SHORT_FROM_USER
mdefine_line|#define GET_SHORT_FROM_USER(target,addr,offs) &bslash;&n;&t;uiomove(((char*)&amp;(target)), 2, ((struct uio *)(addr)))
DECL|macro|IOCTL_TO_USER
mdefine_line|#define IOCTL_TO_USER(target,offs,source,count) &bslash;&n;&t;memcpy(&amp;((target)[offs]), (source), (count))
DECL|macro|IO_WRITE_CHECK
mdefine_line|#define IO_WRITE_CHECK(cmd)&t;(cmd &amp; IOC_IN)
DECL|macro|IOCTL_IN
mdefine_line|#define IOCTL_IN(arg)&t;&t;(*(int*)(arg))
DECL|macro|IOCTL_OUT
mdefine_line|#define IOCTL_OUT(arg,val)&t;(*(int*)(arg) = (val))
DECL|macro|BZERO
mdefine_line|#define BZERO(target,len)&t;bzero((caddr_t)target, len)
DECL|macro|MEMCPY
mdefine_line|#define MEMCPY(dst,src,len)&t;bcopy((caddr_t)src, (caddr_t)dst, len)
macro_line|#endif
eof
