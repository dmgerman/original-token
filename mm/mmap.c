multiline_comment|/*&n; *&t;linux/mm/mmap.c&n; *&n; * Written by obz.&n; */
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;sys/mman.h&gt;
multiline_comment|/*&n; * description of effects of mapping type and prot in current implementation.&n; * this is due to the current handling of page faults in memory.c. the expected&n; * behavior is in parens:&n; *&n; * map_type&t;prot&n; *&t;&t;PROT_NONE&t;PROT_READ&t;PROT_WRITE&t;PROT_EXEC&n; * MAP_SHARED&t;r: (no) yes&t;r: (yes) yes&t;r: (no) yes&t;r: (no) no&n; *&t;&t;w: (no) yes&t;w: (no) copy&t;w: (yes) yes&t;w: (no) no&n; *&t;&t;x: (no) no&t;x: (no) no&t;x: (no) no&t;x: (yes) no&n; *&t;&t;&n; * MAP_PRIVATE&t;r: (no) yes&t;r: (yes) yes&t;r: (no) yes&t;r: (no) no&n; *&t;&t;w: (no) copy&t;w: (no) copy&t;w: (copy) copy&t;w: (no) no&n; *&t;&t;x: (no) no&t;x: (no) no&t;x: (no) no&t;x: (yes) no&n; *&n; * the permissions are encoded as cxwr (copy,exec,write,read)&n; */
DECL|macro|MTYP
mdefine_line|#define MTYP(T) ((T) &amp; MAP_TYPE)
DECL|macro|PREAD
mdefine_line|#define PREAD(T,P) (((P) &amp; PROT_READ) ? 1 : 0)
DECL|macro|PWRITE
mdefine_line|#define PWRITE(T,P) (((P) &amp; PROT_WRITE) ? (MTYP(T) == MAP_SHARED ? 2 : 10) : 0)
DECL|macro|PEXEC
mdefine_line|#define PEXEC(T,P) (((P) &amp; PROT_EXEC) ? 4 : 0)
DECL|macro|PERMISS
mdefine_line|#define PERMISS(T,P) (PREAD(T,P)|PWRITE(T,P)|PEXEC(T,P))
DECL|macro|CODE_SPACE
mdefine_line|#define CODE_SPACE(addr) ((((addr)+4095)&amp;~4095) &lt; &bslash;&n;&t;&t;&t;  current-&gt;start_code + current-&gt;end_code)
r_static
id|caddr_t
DECL|function|mmap_chr
id|mmap_chr
c_func
(paren
r_int
r_int
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
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|off
)paren
(brace
r_int
id|major
comma
id|minor
suffix:semicolon
id|major
op_assign
id|MAJOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|minor
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * for character devices, only /dev/[k]mem may be mapped. when the&n;&t; * swapping code is modified to allow arbitrary sources of pages,&n;&t; * then we can open it up to regular files.&n;&t; */
r_if
c_cond
(paren
id|major
op_ne
l_int|1
op_logical_or
(paren
id|minor
op_ne
l_int|1
op_logical_and
id|minor
op_ne
l_int|2
)paren
)paren
r_return
(paren
id|caddr_t
)paren
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/*&n;&t; * we only allow mappings from address 0 to high_memory, since thats&n;&t; * the range of our memory [actually this is a lie. the buffer cache&n;&t; * and ramdisk occupy higher memory, but the paging stuff won&squot;t&n;&t; * let us map to it anyway, so we break it here].&n;&t; *&n;&t; * this call is very dangerous! because of the lack of adequate&n;&t; * tagging of frames, it is possible to mmap over a frame belonging&n;&t; * to another (innocent) process. with MAP_SHARED|MAP_WRITE, this&n;&t; * rogue process can trample over the other&squot;s data! we ignore this :{&n;&t; * for now, we hope people will malloc the required amount of space,&n;&t; * then mmap over it. the mm needs serious work before this can be&n;&t; * truly useful.&n;&t; */
r_if
c_cond
(paren
id|len
OG
id|high_memory
op_logical_or
id|off
OG
id|high_memory
op_minus
id|len
)paren
multiline_comment|/* avoid overflow */
r_return
(paren
id|caddr_t
)paren
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|remap_page_range
c_func
(paren
id|addr
comma
id|off
comma
id|len
comma
id|PERMISS
c_func
(paren
id|flags
comma
id|prot
)paren
)paren
)paren
r_return
(paren
id|caddr_t
)paren
op_minus
id|EAGAIN
suffix:semicolon
r_return
(paren
id|caddr_t
)paren
id|addr
suffix:semicolon
)brace
id|caddr_t
DECL|function|sys_mmap
id|sys_mmap
c_func
(paren
r_int
r_int
op_star
id|buffer
)paren
(brace
r_int
r_int
id|base
comma
id|addr
suffix:semicolon
r_int
r_int
id|len
comma
id|limit
comma
id|off
suffix:semicolon
r_int
id|prot
comma
id|flags
comma
id|fd
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|get_fs_long
c_func
(paren
id|buffer
)paren
suffix:semicolon
multiline_comment|/* user address space*/
id|len
op_assign
(paren
r_int
)paren
id|get_fs_long
c_func
(paren
id|buffer
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* nbytes of mapping */
id|prot
op_assign
(paren
r_int
)paren
id|get_fs_long
c_func
(paren
id|buffer
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/* protection */
id|flags
op_assign
(paren
r_int
)paren
id|get_fs_long
c_func
(paren
id|buffer
op_plus
l_int|3
)paren
suffix:semicolon
multiline_comment|/* mapping type */
id|fd
op_assign
(paren
r_int
)paren
id|get_fs_long
c_func
(paren
id|buffer
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/* object to map */
id|off
op_assign
(paren
r_int
r_int
)paren
id|get_fs_long
c_func
(paren
id|buffer
op_plus
l_int|5
)paren
suffix:semicolon
multiline_comment|/* offset in object */
r_if
c_cond
(paren
id|fd
op_ge
id|NR_OPEN
op_logical_or
id|fd
OL
l_int|0
op_logical_or
op_logical_neg
(paren
id|file
op_assign
id|current-&gt;filp
(braket
id|fd
)braket
)paren
)paren
r_return
(paren
id|caddr_t
)paren
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
id|addr
OG
id|TASK_SIZE
op_logical_or
(paren
id|addr
op_plus
(paren
r_int
r_int
)paren
id|len
)paren
OG
id|TASK_SIZE
)paren
r_return
(paren
id|caddr_t
)paren
op_minus
id|EINVAL
suffix:semicolon
id|inode
op_assign
id|file-&gt;f_inode
suffix:semicolon
multiline_comment|/*&n;&t; * do simple checking here so the lower-level routines won&squot;t have&n;&t; * to. we assume access permissions have been handled by the open&n;&t; * of the memory object, so we don&squot;t do any here.&n;&t; */
r_switch
c_cond
(paren
id|flags
op_amp
id|MAP_TYPE
)paren
(brace
r_case
id|MAP_SHARED
suffix:colon
r_if
c_cond
(paren
(paren
id|prot
op_amp
id|PROT_WRITE
)paren
op_logical_and
op_logical_neg
(paren
id|file-&gt;f_mode
op_amp
l_int|2
)paren
)paren
r_return
(paren
id|caddr_t
)paren
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* fall through */
r_case
id|MAP_PRIVATE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|file-&gt;f_mode
op_amp
l_int|1
)paren
)paren
r_return
(paren
id|caddr_t
)paren
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
(paren
id|caddr_t
)paren
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * obtain the address to map to. we verify (or select) it and ensure&n;&t; * that it represents a valid section of the address space. we assume&n;&t; * that if PROT_EXEC is specified this should be in the code segment.&n;&t; */
r_if
c_cond
(paren
id|prot
op_amp
id|PROT_EXEC
)paren
(brace
id|base
op_assign
id|get_base
c_func
(paren
id|current-&gt;ldt
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* cs */
id|limit
op_assign
id|get_limit
c_func
(paren
l_int|0x0f
)paren
suffix:semicolon
multiline_comment|/* cs limit */
)brace
r_else
(brace
id|base
op_assign
id|get_base
c_func
(paren
id|current-&gt;ldt
(braket
l_int|2
)braket
)paren
suffix:semicolon
multiline_comment|/* ds */
id|limit
op_assign
id|get_limit
c_func
(paren
l_int|0x17
)paren
suffix:semicolon
multiline_comment|/* ds limit */
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|MAP_FIXED
)paren
(brace
multiline_comment|/*&n;&t;&t; * if MAP_FIXED is specified, we have to map exactly at this&n;&t;&t; * address. it must be page aligned and not ambiguous.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|addr
op_amp
l_int|0xfff
)paren
op_logical_or
id|addr
OG
l_int|0x7fffffff
op_logical_or
id|addr
op_eq
l_int|0
op_logical_or
(paren
id|off
op_amp
l_int|0xfff
)paren
)paren
r_return
(paren
id|caddr_t
)paren
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|addr
op_plus
id|len
OG
id|limit
)paren
r_return
(paren
id|caddr_t
)paren
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * we&squot;re given a hint as to where to put the address.&n;&t;&t; * that we still need to search for a range of pages which&n;&t;&t; * are not mapped and which won&squot;t impact the stack or data&n;&t;&t; * segment.&n;&t;&t; * in linux, we only have a code segment and data segment.&n;&t;&t; * since data grows up and stack grows down, we&squot;re sort of&n;&t;&t; * stuck. placing above the data will break malloc, below&n;&t;&t; * the stack will cause stack overflow. because of this&n;&t;&t; * we don&squot;t allow nonspecified mappings...&n;&t;&t; */
r_return
(paren
id|caddr_t
)paren
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * determine the object being mapped and call the appropriate&n;&t; * specific mapper. the address has already been validated, but&n;&t; * not unmapped&n;&t; */
r_if
c_cond
(paren
id|S_ISCHR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|addr
op_assign
(paren
r_int
r_int
)paren
id|mmap_chr
c_func
(paren
id|base
op_plus
id|addr
comma
id|len
comma
id|prot
comma
id|flags
comma
id|inode
comma
id|off
)paren
suffix:semicolon
r_else
id|addr
op_assign
(paren
r_int
r_int
)paren
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|addr
OG
l_int|0
)paren
id|addr
op_sub_assign
id|base
suffix:semicolon
r_return
(paren
id|caddr_t
)paren
id|addr
suffix:semicolon
)brace
DECL|function|sys_munmap
r_int
id|sys_munmap
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|len
)paren
(brace
r_int
r_int
id|base
comma
id|limit
suffix:semicolon
id|base
op_assign
id|get_base
c_func
(paren
id|current-&gt;ldt
(braket
l_int|2
)braket
)paren
suffix:semicolon
multiline_comment|/* map into ds */
id|limit
op_assign
id|get_limit
c_func
(paren
l_int|0x17
)paren
suffix:semicolon
multiline_comment|/* ds limit */
r_if
c_cond
(paren
(paren
id|addr
op_amp
l_int|0xfff
)paren
op_logical_or
id|addr
OG
l_int|0x7fffffff
op_logical_or
id|addr
op_eq
l_int|0
op_logical_or
id|addr
op_plus
id|len
OG
id|limit
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|unmap_page_range
c_func
(paren
id|base
op_plus
id|addr
comma
id|len
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
multiline_comment|/* should never happen */
r_return
l_int|0
suffix:semicolon
)brace
eof
