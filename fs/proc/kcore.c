multiline_comment|/*&n; *&t;fs/proc/kcore.c kernel ELF/AOUT core dumper&n; *&n; *&t;Modelled on fs/exec.c:aout_core_dump()&n; *&t;Jeremy Fitzhardinge &lt;jeremy@sw.oz.au&gt;&n; *&t;ELF version written by David Howells &lt;David.Howells@nexor.co.uk&gt;&n; *&t;Modified and incorporated into 2.3.x by Tigran Aivazian &lt;tigran@veritas.com&gt;&n; *&t;Support to dump vmalloc&squot;d areas (ELF only), Tigran Aivazian &lt;tigran@veritas.com&gt;&n; *&t;Safe accesses to vmalloc/direct-mapped discontiguous areas, Kanoj Sarcar &lt;kanoj@sgi.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|function|open_kcore
r_static
r_int
id|open_kcore
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_return
id|capable
c_func
(paren
id|CAP_SYS_RAWIO
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|EPERM
suffix:semicolon
)brace
r_static
id|ssize_t
id|read_kcore
c_func
(paren
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
DECL|variable|proc_kcore_operations
r_struct
id|file_operations
id|proc_kcore_operations
op_assign
(brace
id|read
suffix:colon
id|read_kcore
comma
id|open
suffix:colon
id|open_kcore
comma
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_KCORE_AOUT
DECL|function|read_kcore
r_static
id|ssize_t
id|read_kcore
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_int
r_int
r_int
id|p
op_assign
op_star
id|ppos
comma
id|memsize
suffix:semicolon
id|ssize_t
id|read
suffix:semicolon
id|ssize_t
id|count1
suffix:semicolon
r_char
op_star
id|pnt
suffix:semicolon
r_struct
id|user
id|dump
suffix:semicolon
macro_line|#if defined (__i386__) || defined (__mc68000__)
DECL|macro|FIRST_MAPPED
macro_line|#&t;define FIRST_MAPPED&t;PAGE_SIZE&t;/* we don&squot;t have page 0 mapped on x86.. */
macro_line|#else
macro_line|#&t;define FIRST_MAPPED&t;0
macro_line|#endif
id|memset
c_func
(paren
op_amp
id|dump
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|user
)paren
)paren
suffix:semicolon
id|dump.magic
op_assign
id|CMAGIC
suffix:semicolon
id|dump.u_dsize
op_assign
(paren
id|virt_to_phys
c_func
(paren
id|high_memory
)paren
op_rshift
id|PAGE_SHIFT
)paren
suffix:semicolon
macro_line|#if defined (__i386__)
id|dump.start_code
op_assign
id|PAGE_OFFSET
suffix:semicolon
macro_line|#endif
macro_line|#ifdef __alpha__
id|dump.start_data
op_assign
id|PAGE_OFFSET
suffix:semicolon
macro_line|#endif
id|memsize
op_assign
id|virt_to_phys
c_func
(paren
id|high_memory
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ge
id|memsize
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|memsize
op_minus
id|p
)paren
id|count
op_assign
id|memsize
op_minus
id|p
suffix:semicolon
id|read
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|p
template_param
l_int|0
)paren
(brace
id|count1
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|p
op_plus
id|count1
OG
r_sizeof
(paren
r_struct
id|user
)paren
)paren
id|count1
op_assign
r_sizeof
(paren
r_struct
id|user
)paren
op_minus
id|p
suffix:semicolon
id|pnt
op_assign
(paren
r_char
op_star
)paren
op_amp
id|dump
op_plus
id|p
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
(paren
r_void
op_star
)paren
id|pnt
comma
id|count1
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|buf
op_add_assign
id|count1
suffix:semicolon
id|p
op_add_assign
id|count1
suffix:semicolon
id|count
op_sub_assign
id|count1
suffix:semicolon
id|read
op_add_assign
id|count1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OG
l_int|0
op_logical_and
id|p
OL
id|PAGE_SIZE
op_plus
id|FIRST_MAPPED
)paren
(brace
id|count1
op_assign
id|PAGE_SIZE
op_plus
id|FIRST_MAPPED
op_minus
id|p
suffix:semicolon
r_if
c_cond
(paren
id|count1
OG
id|count
)paren
id|count1
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|clear_user
c_func
(paren
id|buf
comma
id|count1
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|buf
op_add_assign
id|count1
suffix:semicolon
id|p
op_add_assign
id|count1
suffix:semicolon
id|count
op_sub_assign
id|count1
suffix:semicolon
id|read
op_add_assign
id|count1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
(paren
r_void
op_star
)paren
(paren
id|PAGE_OFFSET
op_plus
id|p
op_minus
id|PAGE_SIZE
)paren
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|read
op_add_assign
id|count
suffix:semicolon
)brace
op_star
id|ppos
op_add_assign
id|read
suffix:semicolon
r_return
id|read
suffix:semicolon
)brace
macro_line|#else /* CONFIG_KCORE_AOUT */
DECL|macro|roundup
mdefine_line|#define roundup(x, y)  ((((x)+((y)-1))/(y))*(y))
multiline_comment|/* An ELF note in memory */
DECL|struct|memelfnote
r_struct
id|memelfnote
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|datasz
r_int
r_int
id|datasz
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_char
id|saved_command_line
(braket
)braket
suffix:semicolon
DECL|function|get_kcore_size
r_static
r_int
id|get_kcore_size
c_func
(paren
r_int
op_star
id|num_vma
comma
r_int
op_star
id|elf_buflen
)paren
(brace
r_int
r_try
comma
id|size
suffix:semicolon
r_struct
id|vm_struct
op_star
id|m
suffix:semicolon
op_star
id|num_vma
op_assign
l_int|0
suffix:semicolon
id|size
op_assign
(paren
(paren
r_int
)paren
id|high_memory
op_minus
id|PAGE_OFFSET
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vmlist
)paren
(brace
op_star
id|elf_buflen
op_assign
id|PAGE_SIZE
suffix:semicolon
r_return
(paren
id|size
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|m
op_assign
id|vmlist
suffix:semicolon
id|m
suffix:semicolon
id|m
op_assign
id|m-&gt;next
)paren
(brace
r_try
op_assign
(paren
r_int
)paren
id|m-&gt;addr
op_plus
id|m-&gt;size
suffix:semicolon
r_if
c_cond
(paren
r_try
OG
id|size
)paren
id|size
op_assign
r_try
suffix:semicolon
op_star
id|num_vma
op_assign
op_star
id|num_vma
op_plus
l_int|1
suffix:semicolon
)brace
op_star
id|elf_buflen
op_assign
r_sizeof
(paren
r_struct
id|elfhdr
)paren
op_plus
(paren
op_star
id|num_vma
op_plus
l_int|2
)paren
op_star
r_sizeof
(paren
r_struct
id|elf_phdr
)paren
op_plus
l_int|3
op_star
r_sizeof
(paren
r_struct
id|memelfnote
)paren
suffix:semicolon
op_star
id|elf_buflen
op_assign
id|PAGE_ALIGN
c_func
(paren
op_star
id|elf_buflen
)paren
suffix:semicolon
r_return
(paren
id|size
op_minus
id|PAGE_OFFSET
op_plus
op_star
id|elf_buflen
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * determine size of ELF note&n; */
DECL|function|notesize
r_static
r_int
id|notesize
c_func
(paren
r_struct
id|memelfnote
op_star
id|en
)paren
(brace
r_int
id|sz
suffix:semicolon
id|sz
op_assign
r_sizeof
(paren
r_struct
id|elf_note
)paren
suffix:semicolon
id|sz
op_add_assign
id|roundup
c_func
(paren
id|strlen
c_func
(paren
id|en-&gt;name
)paren
comma
l_int|4
)paren
suffix:semicolon
id|sz
op_add_assign
id|roundup
c_func
(paren
id|en-&gt;datasz
comma
l_int|4
)paren
suffix:semicolon
r_return
id|sz
suffix:semicolon
)brace
multiline_comment|/* end notesize() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * store a note in the header buffer&n; */
DECL|function|storenote
r_static
r_char
op_star
id|storenote
c_func
(paren
r_struct
id|memelfnote
op_star
id|men
comma
r_char
op_star
id|bufp
)paren
(brace
r_struct
id|elf_note
id|en
suffix:semicolon
DECL|macro|DUMP_WRITE
mdefine_line|#define DUMP_WRITE(addr,nr) do { memcpy(bufp,addr,nr); bufp += nr; } while(0)
id|en.n_namesz
op_assign
id|strlen
c_func
(paren
id|men-&gt;name
)paren
suffix:semicolon
id|en.n_descsz
op_assign
id|men-&gt;datasz
suffix:semicolon
id|en.n_type
op_assign
id|men-&gt;type
suffix:semicolon
id|DUMP_WRITE
c_func
(paren
op_amp
id|en
comma
r_sizeof
(paren
id|en
)paren
)paren
suffix:semicolon
id|DUMP_WRITE
c_func
(paren
id|men-&gt;name
comma
id|en.n_namesz
)paren
suffix:semicolon
multiline_comment|/* XXX - cast from long long to long to avoid need for libgcc.a */
id|bufp
op_assign
(paren
r_char
op_star
)paren
id|roundup
c_func
(paren
(paren
r_int
r_int
)paren
id|bufp
comma
l_int|4
)paren
suffix:semicolon
id|DUMP_WRITE
c_func
(paren
id|men-&gt;data
comma
id|men-&gt;datasz
)paren
suffix:semicolon
id|bufp
op_assign
(paren
r_char
op_star
)paren
id|roundup
c_func
(paren
(paren
r_int
r_int
)paren
id|bufp
comma
l_int|4
)paren
suffix:semicolon
DECL|macro|DUMP_WRITE
macro_line|#undef DUMP_WRITE
r_return
id|bufp
suffix:semicolon
)brace
multiline_comment|/* end storenote() */
multiline_comment|/*&n; * store an ELF coredump header in the supplied buffer&n; * num_vma is the number of elements in vmlist&n; */
DECL|function|elf_kcore_store_hdr
r_static
r_void
id|elf_kcore_store_hdr
c_func
(paren
r_char
op_star
id|bufp
comma
r_int
id|num_vma
comma
r_int
id|dataoff
)paren
(brace
r_struct
id|elf_prstatus
id|prstatus
suffix:semicolon
multiline_comment|/* NT_PRSTATUS */
r_struct
id|elf_prpsinfo
id|prpsinfo
suffix:semicolon
multiline_comment|/* NT_PRPSINFO */
r_struct
id|elf_phdr
op_star
id|nhdr
comma
op_star
id|phdr
suffix:semicolon
r_struct
id|elfhdr
op_star
id|elf
suffix:semicolon
r_struct
id|memelfnote
id|notes
(braket
l_int|3
)braket
suffix:semicolon
id|off_t
id|offset
op_assign
l_int|0
suffix:semicolon
r_struct
id|vm_struct
op_star
id|m
suffix:semicolon
multiline_comment|/* setup ELF header */
id|elf
op_assign
(paren
r_struct
id|elfhdr
op_star
)paren
id|bufp
suffix:semicolon
id|bufp
op_add_assign
r_sizeof
(paren
r_struct
id|elfhdr
)paren
suffix:semicolon
id|offset
op_add_assign
r_sizeof
(paren
r_struct
id|elfhdr
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|elf-&gt;e_ident
comma
id|ELFMAG
comma
id|SELFMAG
)paren
suffix:semicolon
id|elf-&gt;e_ident
(braket
id|EI_CLASS
)braket
op_assign
id|ELF_CLASS
suffix:semicolon
id|elf-&gt;e_ident
(braket
id|EI_DATA
)braket
op_assign
id|ELF_DATA
suffix:semicolon
id|elf-&gt;e_ident
(braket
id|EI_VERSION
)braket
op_assign
id|EV_CURRENT
suffix:semicolon
id|memset
c_func
(paren
id|elf-&gt;e_ident
op_plus
id|EI_PAD
comma
l_int|0
comma
id|EI_NIDENT
op_minus
id|EI_PAD
)paren
suffix:semicolon
id|elf-&gt;e_type
op_assign
id|ET_CORE
suffix:semicolon
id|elf-&gt;e_machine
op_assign
id|ELF_ARCH
suffix:semicolon
id|elf-&gt;e_version
op_assign
id|EV_CURRENT
suffix:semicolon
id|elf-&gt;e_entry
op_assign
l_int|0
suffix:semicolon
id|elf-&gt;e_phoff
op_assign
r_sizeof
(paren
r_struct
id|elfhdr
)paren
suffix:semicolon
id|elf-&gt;e_shoff
op_assign
l_int|0
suffix:semicolon
id|elf-&gt;e_flags
op_assign
l_int|0
suffix:semicolon
id|elf-&gt;e_ehsize
op_assign
r_sizeof
(paren
r_struct
id|elfhdr
)paren
suffix:semicolon
id|elf-&gt;e_phentsize
op_assign
r_sizeof
(paren
r_struct
id|elf_phdr
)paren
suffix:semicolon
id|elf-&gt;e_phnum
op_assign
l_int|2
op_plus
id|num_vma
suffix:semicolon
id|elf-&gt;e_shentsize
op_assign
l_int|0
suffix:semicolon
id|elf-&gt;e_shnum
op_assign
l_int|0
suffix:semicolon
id|elf-&gt;e_shstrndx
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* setup ELF PT_NOTE program header */
id|nhdr
op_assign
(paren
r_struct
id|elf_phdr
op_star
)paren
id|bufp
suffix:semicolon
id|bufp
op_add_assign
r_sizeof
(paren
r_struct
id|elf_phdr
)paren
suffix:semicolon
id|offset
op_add_assign
r_sizeof
(paren
r_struct
id|elf_phdr
)paren
suffix:semicolon
id|nhdr-&gt;p_type
op_assign
id|PT_NOTE
suffix:semicolon
id|nhdr-&gt;p_offset
op_assign
l_int|0
suffix:semicolon
id|nhdr-&gt;p_vaddr
op_assign
l_int|0
suffix:semicolon
id|nhdr-&gt;p_paddr
op_assign
l_int|0
suffix:semicolon
id|nhdr-&gt;p_filesz
op_assign
l_int|0
suffix:semicolon
id|nhdr-&gt;p_memsz
op_assign
l_int|0
suffix:semicolon
id|nhdr-&gt;p_flags
op_assign
l_int|0
suffix:semicolon
id|nhdr-&gt;p_align
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* setup ELF PT_LOAD program header for the &n;&t; * virtual range 0xc0000000 -&gt; high_memory */
id|phdr
op_assign
(paren
r_struct
id|elf_phdr
op_star
)paren
id|bufp
suffix:semicolon
id|bufp
op_add_assign
r_sizeof
(paren
r_struct
id|elf_phdr
)paren
suffix:semicolon
id|offset
op_add_assign
r_sizeof
(paren
r_struct
id|elf_phdr
)paren
suffix:semicolon
id|phdr-&gt;p_type
op_assign
id|PT_LOAD
suffix:semicolon
id|phdr-&gt;p_flags
op_assign
id|PF_R
op_or
id|PF_W
op_or
id|PF_X
suffix:semicolon
id|phdr-&gt;p_offset
op_assign
id|dataoff
suffix:semicolon
id|phdr-&gt;p_vaddr
op_assign
id|PAGE_OFFSET
suffix:semicolon
id|phdr-&gt;p_paddr
op_assign
id|__pa
c_func
(paren
id|PAGE_OFFSET
)paren
suffix:semicolon
id|phdr-&gt;p_filesz
op_assign
id|phdr-&gt;p_memsz
op_assign
(paren
(paren
r_int
r_int
)paren
id|high_memory
op_minus
id|PAGE_OFFSET
)paren
suffix:semicolon
id|phdr-&gt;p_align
op_assign
id|PAGE_SIZE
suffix:semicolon
multiline_comment|/* setup ELF PT_LOAD program header for every vmalloc&squot;d area */
r_for
c_loop
(paren
id|m
op_assign
id|vmlist
suffix:semicolon
id|m
suffix:semicolon
id|m
op_assign
id|m-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|m-&gt;flags
op_amp
id|VM_IOREMAP
)paren
multiline_comment|/* don&squot;t dump ioremap&squot;d stuff! (TA) */
r_continue
suffix:semicolon
id|phdr
op_assign
(paren
r_struct
id|elf_phdr
op_star
)paren
id|bufp
suffix:semicolon
id|bufp
op_add_assign
r_sizeof
(paren
r_struct
id|elf_phdr
)paren
suffix:semicolon
id|offset
op_add_assign
r_sizeof
(paren
r_struct
id|elf_phdr
)paren
suffix:semicolon
id|phdr-&gt;p_type
op_assign
id|PT_LOAD
suffix:semicolon
id|phdr-&gt;p_flags
op_assign
id|PF_R
op_or
id|PF_W
op_or
id|PF_X
suffix:semicolon
id|phdr-&gt;p_offset
op_assign
(paren
r_int
)paren
id|m-&gt;addr
op_minus
id|PAGE_OFFSET
op_plus
id|dataoff
suffix:semicolon
id|phdr-&gt;p_vaddr
op_assign
(paren
r_int
)paren
id|m-&gt;addr
suffix:semicolon
id|phdr-&gt;p_paddr
op_assign
id|__pa
c_func
(paren
id|m-&gt;addr
)paren
suffix:semicolon
id|phdr-&gt;p_filesz
op_assign
id|phdr-&gt;p_memsz
op_assign
id|m-&gt;size
suffix:semicolon
id|phdr-&gt;p_align
op_assign
id|PAGE_SIZE
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Set up the notes in similar form to SVR4 core dumps made&n;&t; * with info from their /proc.&n;&t; */
id|nhdr-&gt;p_offset
op_assign
id|offset
suffix:semicolon
multiline_comment|/* set up the process status */
id|notes
(braket
l_int|0
)braket
dot
id|name
op_assign
l_string|&quot;CORE&quot;
suffix:semicolon
id|notes
(braket
l_int|0
)braket
dot
id|type
op_assign
id|NT_PRSTATUS
suffix:semicolon
id|notes
(braket
l_int|0
)braket
dot
id|datasz
op_assign
r_sizeof
(paren
r_struct
id|elf_prstatus
)paren
suffix:semicolon
id|notes
(braket
l_int|0
)braket
dot
id|data
op_assign
op_amp
id|prstatus
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|prstatus
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|elf_prstatus
)paren
)paren
suffix:semicolon
id|nhdr-&gt;p_filesz
op_assign
id|notesize
c_func
(paren
op_amp
id|notes
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|bufp
op_assign
id|storenote
c_func
(paren
op_amp
id|notes
(braket
l_int|0
)braket
comma
id|bufp
)paren
suffix:semicolon
multiline_comment|/* set up the process info */
id|notes
(braket
l_int|1
)braket
dot
id|name
op_assign
l_string|&quot;CORE&quot;
suffix:semicolon
id|notes
(braket
l_int|1
)braket
dot
id|type
op_assign
id|NT_PRPSINFO
suffix:semicolon
id|notes
(braket
l_int|1
)braket
dot
id|datasz
op_assign
r_sizeof
(paren
r_struct
id|elf_prpsinfo
)paren
suffix:semicolon
id|notes
(braket
l_int|1
)braket
dot
id|data
op_assign
op_amp
id|prpsinfo
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|prpsinfo
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|elf_prpsinfo
)paren
)paren
suffix:semicolon
id|prpsinfo.pr_state
op_assign
l_int|0
suffix:semicolon
id|prpsinfo.pr_sname
op_assign
l_char|&squot;R&squot;
suffix:semicolon
id|prpsinfo.pr_zomb
op_assign
l_int|0
suffix:semicolon
id|strcpy
c_func
(paren
id|prpsinfo.pr_fname
comma
l_string|&quot;vmlinux&quot;
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|prpsinfo.pr_psargs
comma
id|saved_command_line
comma
id|ELF_PRARGSZ
)paren
suffix:semicolon
id|nhdr-&gt;p_filesz
op_assign
id|notesize
c_func
(paren
op_amp
id|notes
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|bufp
op_assign
id|storenote
c_func
(paren
op_amp
id|notes
(braket
l_int|1
)braket
comma
id|bufp
)paren
suffix:semicolon
multiline_comment|/* set up the task structure */
id|notes
(braket
l_int|2
)braket
dot
id|name
op_assign
l_string|&quot;CORE&quot;
suffix:semicolon
id|notes
(braket
l_int|2
)braket
dot
id|type
op_assign
id|NT_TASKSTRUCT
suffix:semicolon
id|notes
(braket
l_int|2
)braket
dot
id|datasz
op_assign
r_sizeof
(paren
r_struct
id|task_struct
)paren
suffix:semicolon
id|notes
(braket
l_int|2
)braket
dot
id|data
op_assign
id|current
suffix:semicolon
id|nhdr-&gt;p_filesz
op_assign
id|notesize
c_func
(paren
op_amp
id|notes
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|bufp
op_assign
id|storenote
c_func
(paren
op_amp
id|notes
(braket
l_int|2
)braket
comma
id|bufp
)paren
suffix:semicolon
)brace
multiline_comment|/* end elf_kcore_store_hdr() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * read from the ELF header and then kernel memory&n; */
DECL|function|read_kcore
r_static
id|ssize_t
id|read_kcore
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buffer
comma
r_int
id|buflen
comma
id|loff_t
op_star
id|fpos
)paren
(brace
id|ssize_t
id|acc
op_assign
l_int|0
suffix:semicolon
r_int
id|size
comma
id|tsz
suffix:semicolon
r_int
id|elf_buflen
suffix:semicolon
r_int
id|num_vma
suffix:semicolon
r_int
r_int
id|start
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
id|proc_root_kcore-&gt;size
op_assign
id|size
op_assign
id|get_kcore_size
c_func
(paren
op_amp
id|num_vma
comma
op_amp
id|elf_buflen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buflen
op_eq
l_int|0
op_logical_or
op_star
id|fpos
op_ge
id|size
)paren
(brace
id|read_unlock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* trim buflen to not go beyond EOF */
r_if
c_cond
(paren
id|buflen
OG
id|size
op_minus
op_star
id|fpos
)paren
id|buflen
op_assign
id|size
op_minus
op_star
id|fpos
suffix:semicolon
multiline_comment|/* construct an ELF core header if we&squot;ll need some of it */
r_if
c_cond
(paren
op_star
id|fpos
OL
id|elf_buflen
)paren
(brace
r_char
op_star
id|elf_buf
suffix:semicolon
id|tsz
op_assign
id|elf_buflen
op_minus
op_star
id|fpos
suffix:semicolon
r_if
c_cond
(paren
id|buflen
OL
id|tsz
)paren
id|tsz
op_assign
id|buflen
suffix:semicolon
id|elf_buf
op_assign
id|kmalloc
c_func
(paren
id|elf_buflen
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|elf_buf
)paren
(brace
id|read_unlock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|elf_buf
comma
l_int|0
comma
id|elf_buflen
)paren
suffix:semicolon
id|elf_kcore_store_hdr
c_func
(paren
id|elf_buf
comma
id|num_vma
comma
id|elf_buflen
)paren
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buffer
comma
id|elf_buf
op_plus
op_star
id|fpos
comma
id|tsz
)paren
)paren
(brace
id|kfree
c_func
(paren
id|elf_buf
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|elf_buf
)paren
suffix:semicolon
id|buflen
op_sub_assign
id|tsz
suffix:semicolon
op_star
id|fpos
op_add_assign
id|tsz
suffix:semicolon
id|buffer
op_add_assign
id|tsz
suffix:semicolon
id|acc
op_add_assign
id|tsz
suffix:semicolon
multiline_comment|/* leave now if filled buffer already */
r_if
c_cond
(paren
id|buflen
op_eq
l_int|0
)paren
r_return
id|acc
suffix:semicolon
)brace
r_else
id|read_unlock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
multiline_comment|/* where page 0 not mapped, write zeros into buffer */
macro_line|#if defined (__i386__) || defined (__mc68000__)
r_if
c_cond
(paren
op_star
id|fpos
OL
id|PAGE_SIZE
op_plus
id|elf_buflen
)paren
(brace
multiline_comment|/* work out how much to clear */
id|tsz
op_assign
id|PAGE_SIZE
op_plus
id|elf_buflen
op_minus
op_star
id|fpos
suffix:semicolon
r_if
c_cond
(paren
id|buflen
OL
id|tsz
)paren
id|tsz
op_assign
id|buflen
suffix:semicolon
multiline_comment|/* write zeros to buffer */
r_if
c_cond
(paren
id|clear_user
c_func
(paren
id|buffer
comma
id|tsz
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|buflen
op_sub_assign
id|tsz
suffix:semicolon
op_star
id|fpos
op_add_assign
id|tsz
suffix:semicolon
id|buffer
op_add_assign
id|tsz
suffix:semicolon
id|acc
op_add_assign
id|tsz
suffix:semicolon
multiline_comment|/* leave now if filled buffer already */
r_if
c_cond
(paren
id|buflen
op_eq
l_int|0
)paren
r_return
id|tsz
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* fill the remainder of the buffer from kernel VM space */
id|start
op_assign
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
op_star
id|fpos
op_minus
id|elf_buflen
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tsz
op_assign
(paren
id|PAGE_SIZE
op_minus
(paren
id|start
op_amp
op_complement
id|PAGE_MASK
)paren
)paren
)paren
OG
id|buflen
)paren
id|tsz
op_assign
id|buflen
suffix:semicolon
r_while
c_loop
(paren
id|buflen
)paren
(brace
r_if
c_cond
(paren
(paren
id|start
op_ge
id|VMALLOC_START
)paren
op_logical_and
(paren
id|start
OL
id|VMALLOC_END
)paren
)paren
(brace
r_char
op_star
id|elf_buf
suffix:semicolon
r_struct
id|vm_struct
op_star
id|m
suffix:semicolon
r_int
r_int
id|curstart
op_assign
id|start
suffix:semicolon
r_int
r_int
id|cursize
op_assign
id|tsz
suffix:semicolon
id|elf_buf
op_assign
id|kmalloc
c_func
(paren
id|tsz
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|elf_buf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|elf_buf
comma
l_int|0
comma
id|tsz
)paren
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|m
op_assign
id|vmlist
suffix:semicolon
id|m
op_logical_and
id|cursize
suffix:semicolon
id|m
op_assign
id|m-&gt;next
)paren
(brace
r_int
r_int
id|vmstart
suffix:semicolon
r_int
r_int
id|vmsize
suffix:semicolon
r_int
r_int
id|msize
op_assign
id|m-&gt;size
op_minus
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|m-&gt;addr
op_plus
id|msize
)paren
OL
id|curstart
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|m-&gt;addr
OG
(paren
id|curstart
op_plus
id|cursize
)paren
)paren
r_break
suffix:semicolon
id|vmstart
op_assign
(paren
id|curstart
OL
(paren
r_int
r_int
)paren
id|m-&gt;addr
ques
c_cond
(paren
r_int
r_int
)paren
id|m-&gt;addr
suffix:colon
id|curstart
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|m-&gt;addr
op_plus
id|msize
)paren
OG
(paren
id|curstart
op_plus
id|cursize
)paren
)paren
id|vmsize
op_assign
id|curstart
op_plus
id|cursize
op_minus
id|vmstart
suffix:semicolon
r_else
id|vmsize
op_assign
(paren
r_int
r_int
)paren
id|m-&gt;addr
op_plus
id|msize
op_minus
id|vmstart
suffix:semicolon
id|curstart
op_assign
id|vmstart
op_plus
id|vmsize
suffix:semicolon
id|cursize
op_sub_assign
id|vmsize
suffix:semicolon
multiline_comment|/* don&squot;t dump ioremap&squot;d stuff! (TA) */
r_if
c_cond
(paren
id|m-&gt;flags
op_amp
id|VM_IOREMAP
)paren
r_continue
suffix:semicolon
id|memcpy
c_func
(paren
id|elf_buf
op_plus
(paren
id|vmstart
op_minus
id|start
)paren
comma
(paren
r_char
op_star
)paren
id|vmstart
comma
id|vmsize
)paren
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|vmlist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buffer
comma
id|elf_buf
comma
id|tsz
)paren
)paren
(brace
id|kfree
c_func
(paren
id|elf_buf
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|kfree
c_func
(paren
id|elf_buf
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|start
OG
id|PAGE_OFFSET
)paren
op_logical_and
(paren
id|start
OL
(paren
r_int
r_int
)paren
id|high_memory
)paren
)paren
(brace
r_if
c_cond
(paren
id|kern_addr_valid
c_func
(paren
id|start
)paren
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buffer
comma
(paren
r_char
op_star
)paren
id|start
comma
id|tsz
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|clear_user
c_func
(paren
id|buffer
comma
id|tsz
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|clear_user
c_func
(paren
id|buffer
comma
id|tsz
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|buflen
op_sub_assign
id|tsz
suffix:semicolon
op_star
id|fpos
op_add_assign
id|tsz
suffix:semicolon
id|buffer
op_add_assign
id|tsz
suffix:semicolon
id|acc
op_add_assign
id|tsz
suffix:semicolon
id|start
op_add_assign
id|tsz
suffix:semicolon
id|tsz
op_assign
(paren
id|buflen
OG
id|PAGE_SIZE
ques
c_cond
id|PAGE_SIZE
suffix:colon
id|buflen
)paren
suffix:semicolon
)brace
r_return
id|acc
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_KCORE_AOUT */
eof
