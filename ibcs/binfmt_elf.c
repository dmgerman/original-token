multiline_comment|/*&n; * linux/fs/binfmt_elf.c&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/binfmts.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/shm.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
id|asmlinkage
r_int
id|sys_exit
c_func
(paren
r_int
id|exit_code
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_close
c_func
(paren
r_int
id|fd
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_open
c_func
(paren
r_const
r_char
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_brk
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|DLINFO_ITEMS
mdefine_line|#define DLINFO_ITEMS 8
macro_line|#include &lt;linux/elf.h&gt;
multiline_comment|/* We need to explicitly zero any fractional pages&n;   after the data section (i.e. bss).  This would&n;   contain the junk from the file that should not&n;   be in memory */
DECL|function|padzero
r_static
r_void
(def_block
id|padzero
c_func
(paren
r_int
id|elf_bss
)paren
(brace
r_int
r_int
id|fpnt
comma
id|nbyte
suffix:semicolon
r_if
c_cond
(paren
id|elf_bss
op_amp
l_int|0xfff
)paren
(brace
id|nbyte
op_assign
(paren
id|PAGE_SIZE
op_minus
(paren
id|elf_bss
op_amp
l_int|0xfff
)paren
)paren
op_amp
l_int|0xfff
suffix:semicolon
r_if
c_cond
(paren
id|nbyte
)paren
(brace
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|elf_bss
comma
id|nbyte
)paren
suffix:semicolon
id|fpnt
op_assign
id|elf_bss
suffix:semicolon
r_while
c_loop
(paren
id|fpnt
op_amp
l_int|0xfff
)paren
(brace
id|put_fs_byte
c_func
(paren
l_int|0
comma
id|fpnt
op_increment
)paren
suffix:semicolon
)brace
)brace
suffix:semicolon
)brace
suffix:semicolon
)brace
)def_block
DECL|function|create_elf_tables
r_int
r_int
op_star
id|create_elf_tables
c_func
(paren
r_char
op_star
id|p
comma
r_int
id|argc
comma
r_int
id|envc
comma
r_struct
id|elfhdr
op_star
id|exec
comma
r_int
r_int
id|load_addr
comma
r_int
id|ibcs
)paren
(brace
r_int
r_int
op_star
id|argv
comma
op_star
id|envp
comma
op_star
id|dlinfo
suffix:semicolon
r_int
r_int
op_star
id|sp
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|mpnt
suffix:semicolon
id|mpnt
op_assign
(paren
r_struct
id|vm_area_struct
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|mpnt
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mpnt
)paren
(brace
id|mpnt-&gt;vm_task
op_assign
id|current
suffix:semicolon
id|mpnt-&gt;vm_start
op_assign
id|PAGE_MASK
op_amp
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|mpnt-&gt;vm_end
op_assign
id|TASK_SIZE
suffix:semicolon
id|mpnt-&gt;vm_page_prot
op_assign
id|PAGE_PRIVATE
op_or
id|PAGE_DIRTY
suffix:semicolon
id|mpnt-&gt;vm_share
op_assign
l_int|NULL
suffix:semicolon
id|mpnt-&gt;vm_inode
op_assign
l_int|NULL
suffix:semicolon
id|mpnt-&gt;vm_offset
op_assign
l_int|0
suffix:semicolon
id|mpnt-&gt;vm_ops
op_assign
l_int|NULL
suffix:semicolon
id|insert_vm_struct
c_func
(paren
id|current
comma
id|mpnt
)paren
suffix:semicolon
id|current-&gt;mm-&gt;stk_vma
op_assign
id|mpnt
suffix:semicolon
)brace
id|sp
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
l_int|0xfffffffc
op_amp
(paren
r_int
r_int
)paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exec
)paren
(brace
id|sp
op_sub_assign
id|DLINFO_ITEMS
op_star
l_int|2
suffix:semicolon
)brace
id|dlinfo
op_assign
id|sp
suffix:semicolon
id|sp
op_sub_assign
id|envc
op_plus
l_int|1
suffix:semicolon
id|envp
op_assign
id|sp
suffix:semicolon
id|sp
op_sub_assign
id|argc
op_plus
l_int|1
suffix:semicolon
id|argv
op_assign
id|sp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ibcs
)paren
(brace
id|put_fs_long
c_func
(paren
(paren
r_int
r_int
)paren
id|envp
comma
op_decrement
id|sp
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
(paren
r_int
r_int
)paren
id|argv
comma
op_decrement
id|sp
)paren
suffix:semicolon
)brace
multiline_comment|/* The constant numbers (0-9) that we are writing here are&n;&t;   described in the header file sys/auxv.h on at least&n;&t;   some versions of SVr4 */
r_if
c_cond
(paren
id|exec
)paren
(brace
multiline_comment|/* Put this here for an ELF program interpreter */
r_struct
id|elf_phdr
op_star
id|eppnt
suffix:semicolon
id|eppnt
op_assign
(paren
r_struct
id|elf_phdr
op_star
)paren
id|exec-&gt;e_phoff
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|3
comma
id|dlinfo
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|load_addr
op_plus
id|exec-&gt;e_phoff
comma
id|dlinfo
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|4
comma
id|dlinfo
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
r_sizeof
(paren
r_struct
id|elf_phdr
)paren
comma
id|dlinfo
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|5
comma
id|dlinfo
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|exec-&gt;e_phnum
comma
id|dlinfo
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|9
comma
id|dlinfo
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
(paren
r_int
r_int
)paren
id|exec-&gt;e_entry
comma
id|dlinfo
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|7
comma
id|dlinfo
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|SHM_RANGE_START
comma
id|dlinfo
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|8
comma
id|dlinfo
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|0
comma
id|dlinfo
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|6
comma
id|dlinfo
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|PAGE_SIZE
comma
id|dlinfo
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|0
comma
id|dlinfo
op_increment
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
l_int|0
comma
id|dlinfo
op_increment
)paren
suffix:semicolon
)brace
suffix:semicolon
id|put_fs_long
c_func
(paren
(paren
r_int
r_int
)paren
id|argc
comma
op_decrement
id|sp
)paren
suffix:semicolon
id|current-&gt;mm-&gt;arg_start
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
r_while
c_loop
(paren
id|argc
op_decrement
OG
l_int|0
)paren
(brace
id|put_fs_long
c_func
(paren
(paren
r_int
r_int
)paren
id|p
comma
id|argv
op_increment
)paren
suffix:semicolon
r_while
c_loop
(paren
id|get_fs_byte
c_func
(paren
id|p
op_increment
)paren
)paren
multiline_comment|/* nothing */
suffix:semicolon
)brace
id|put_fs_long
c_func
(paren
l_int|0
comma
id|argv
)paren
suffix:semicolon
id|current-&gt;mm-&gt;arg_end
op_assign
id|current-&gt;mm-&gt;env_start
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
r_while
c_loop
(paren
id|envc
op_decrement
OG
l_int|0
)paren
(brace
id|put_fs_long
c_func
(paren
(paren
r_int
r_int
)paren
id|p
comma
id|envp
op_increment
)paren
suffix:semicolon
r_while
c_loop
(paren
id|get_fs_byte
c_func
(paren
id|p
op_increment
)paren
)paren
multiline_comment|/* nothing */
suffix:semicolon
)brace
id|put_fs_long
c_func
(paren
l_int|0
comma
id|envp
)paren
suffix:semicolon
id|current-&gt;mm-&gt;env_end
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
r_return
id|sp
suffix:semicolon
)brace
multiline_comment|/* This is much more generalized than the library routine read function,&n;   so we keep this separate.  Techincally the library read function&n;   is only provided so that we can read a.out libraries that have&n;   an ELF header */
DECL|function|load_elf_interp
r_static
r_int
r_int
id|load_elf_interp
c_func
(paren
r_struct
id|elfhdr
op_star
id|interp_elf_ex
comma
r_struct
id|inode
op_star
id|interpreter_inode
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|elf_phdr
op_star
id|elf_phdata
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|elf_phdr
op_star
id|eppnt
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
r_int
r_int
id|load_addr
suffix:semicolon
r_int
id|elf_exec_fileno
suffix:semicolon
r_int
id|elf_bss
suffix:semicolon
r_int
id|old_fs
comma
id|retval
suffix:semicolon
r_int
r_int
id|last_bss
suffix:semicolon
r_int
id|error
suffix:semicolon
r_int
id|i
comma
id|k
suffix:semicolon
id|elf_bss
op_assign
l_int|0
suffix:semicolon
id|last_bss
op_assign
l_int|0
suffix:semicolon
id|error
op_assign
id|load_addr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* First of all, some simple consistency checks */
r_if
c_cond
(paren
(paren
id|interp_elf_ex-&gt;e_type
op_ne
id|ET_EXEC
op_logical_and
id|interp_elf_ex-&gt;e_type
op_ne
id|ET_DYN
)paren
op_logical_or
(paren
id|interp_elf_ex-&gt;e_machine
op_ne
id|EM_386
op_logical_and
id|interp_elf_ex-&gt;e_machine
op_ne
id|EM_486
)paren
op_logical_or
(paren
op_logical_neg
id|interpreter_inode-&gt;i_op
op_logical_or
op_logical_neg
id|interpreter_inode-&gt;i_op-&gt;bmap
op_logical_or
op_logical_neg
id|interpreter_inode-&gt;i_op-&gt;default_file_ops-&gt;mmap
)paren
)paren
(brace
r_return
l_int|0xffffffff
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Now read in all of the header information */
r_if
c_cond
(paren
r_sizeof
(paren
r_struct
id|elf_phdr
)paren
op_star
id|interp_elf_ex-&gt;e_phnum
OG
id|PAGE_SIZE
)paren
(brace
r_return
l_int|0xffffffff
suffix:semicolon
)brace
id|elf_phdata
op_assign
(paren
r_struct
id|elf_phdr
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|elf_phdr
)paren
op_star
id|interp_elf_ex-&gt;e_phnum
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|elf_phdata
)paren
(brace
r_return
l_int|0xffffffff
suffix:semicolon
)brace
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
id|retval
op_assign
id|read_exec
c_func
(paren
id|interpreter_inode
comma
id|interp_elf_ex-&gt;e_phoff
comma
(paren
r_char
op_star
)paren
id|elf_phdata
comma
r_sizeof
(paren
r_struct
id|elf_phdr
)paren
op_star
id|interp_elf_ex-&gt;e_phnum
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
id|elf_exec_fileno
op_assign
id|open_inode
c_func
(paren
id|interpreter_inode
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|elf_exec_fileno
OL
l_int|0
)paren
r_return
l_int|0xffffffff
suffix:semicolon
id|file
op_assign
id|current-&gt;files-&gt;fd
(braket
id|elf_exec_fileno
)braket
suffix:semicolon
id|eppnt
op_assign
id|elf_phdata
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|interp_elf_ex-&gt;e_phnum
suffix:semicolon
id|i
op_increment
comma
id|eppnt
op_increment
)paren
r_if
c_cond
(paren
id|eppnt-&gt;p_type
op_eq
id|PT_LOAD
)paren
(brace
id|error
op_assign
id|do_mmap
c_func
(paren
id|file
comma
id|eppnt-&gt;p_vaddr
op_amp
l_int|0xfffff000
comma
id|eppnt-&gt;p_filesz
op_plus
(paren
id|eppnt-&gt;p_vaddr
op_amp
l_int|0xfff
)paren
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_PRIVATE
op_or
(paren
id|interp_elf_ex-&gt;e_type
op_eq
id|ET_EXEC
ques
c_cond
id|MAP_FIXED
suffix:colon
l_int|0
)paren
comma
id|eppnt-&gt;p_offset
op_amp
l_int|0xfffff000
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|load_addr
op_logical_and
id|interp_elf_ex-&gt;e_type
op_eq
id|ET_DYN
)paren
(brace
id|load_addr
op_assign
id|error
suffix:semicolon
)brace
id|k
op_assign
id|load_addr
op_plus
id|eppnt-&gt;p_vaddr
op_plus
id|eppnt-&gt;p_filesz
suffix:semicolon
r_if
c_cond
(paren
id|k
OG
id|elf_bss
)paren
(brace
id|elf_bss
op_assign
id|k
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error
template_param
op_minus
l_int|1024
)paren
(brace
r_break
suffix:semicolon
)brace
multiline_comment|/* Real error */
id|k
op_assign
id|load_addr
op_plus
id|eppnt-&gt;p_memsz
op_plus
id|eppnt-&gt;p_vaddr
suffix:semicolon
r_if
c_cond
(paren
id|k
OG
id|last_bss
)paren
(brace
id|last_bss
op_assign
id|k
suffix:semicolon
)brace
)brace
multiline_comment|/* Now use mmap to map the library into memory. */
id|sys_close
c_func
(paren
id|elf_exec_fileno
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
template_param
op_minus
l_int|1024
)paren
(brace
id|kfree
c_func
(paren
id|elf_phdata
)paren
suffix:semicolon
r_return
l_int|0xffffffff
suffix:semicolon
)brace
id|padzero
c_func
(paren
id|elf_bss
)paren
suffix:semicolon
id|len
op_assign
(paren
id|elf_bss
op_plus
l_int|0xfff
)paren
op_amp
l_int|0xfffff000
suffix:semicolon
multiline_comment|/* What we have mapped so far */
multiline_comment|/* Map the last of the bss segment */
r_if
c_cond
(paren
id|last_bss
OG
id|len
)paren
id|do_mmap
c_func
(paren
l_int|NULL
comma
id|len
comma
id|last_bss
op_minus
id|len
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
comma
l_int|0
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|elf_phdata
)paren
suffix:semicolon
r_return
(paren
(paren
r_int
r_int
)paren
id|interp_elf_ex-&gt;e_entry
)paren
op_plus
id|load_addr
suffix:semicolon
)brace
DECL|function|load_aout_interp
r_static
r_int
r_int
id|load_aout_interp
c_func
(paren
r_struct
id|exec
op_star
id|interp_ex
comma
r_struct
id|inode
op_star
id|interpreter_inode
)paren
(brace
r_int
id|retval
suffix:semicolon
r_int
r_int
id|elf_entry
suffix:semicolon
id|current-&gt;mm-&gt;brk
op_assign
id|interp_ex-&gt;a_bss
op_plus
(paren
id|current-&gt;mm-&gt;end_data
op_assign
id|interp_ex-&gt;a_data
op_plus
(paren
id|current-&gt;mm-&gt;end_code
op_assign
id|interp_ex-&gt;a_text
)paren
)paren
suffix:semicolon
id|elf_entry
op_assign
id|interp_ex-&gt;a_entry
suffix:semicolon
r_if
c_cond
(paren
id|N_MAGIC
c_func
(paren
op_star
id|interp_ex
)paren
op_eq
id|OMAGIC
)paren
(brace
id|do_mmap
c_func
(paren
l_int|NULL
comma
l_int|0
comma
id|interp_ex-&gt;a_text
op_plus
id|interp_ex-&gt;a_data
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
comma
l_int|0
)paren
suffix:semicolon
id|retval
op_assign
id|read_exec
c_func
(paren
id|interpreter_inode
comma
l_int|32
comma
(paren
r_char
op_star
)paren
l_int|0
comma
id|interp_ex-&gt;a_text
op_plus
id|interp_ex-&gt;a_data
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|N_MAGIC
c_func
(paren
op_star
id|interp_ex
)paren
op_eq
id|ZMAGIC
op_logical_or
id|N_MAGIC
c_func
(paren
op_star
id|interp_ex
)paren
op_eq
id|QMAGIC
)paren
(brace
id|do_mmap
c_func
(paren
l_int|NULL
comma
l_int|0
comma
id|interp_ex-&gt;a_text
op_plus
id|interp_ex-&gt;a_data
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
comma
l_int|0
)paren
suffix:semicolon
id|retval
op_assign
id|read_exec
c_func
(paren
id|interpreter_inode
comma
id|N_TXTOFF
c_func
(paren
op_star
id|interp_ex
)paren
comma
(paren
r_char
op_star
)paren
id|N_TXTADDR
c_func
(paren
op_star
id|interp_ex
)paren
comma
id|interp_ex-&gt;a_text
op_plus
id|interp_ex-&gt;a_data
)paren
suffix:semicolon
)brace
r_else
id|retval
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ge
l_int|0
)paren
(brace
id|do_mmap
c_func
(paren
l_int|NULL
comma
(paren
id|interp_ex-&gt;a_text
op_plus
id|interp_ex-&gt;a_data
op_plus
l_int|0xfff
)paren
op_amp
l_int|0xfffff000
comma
id|interp_ex-&gt;a_bss
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
(brace
r_return
l_int|0xffffffff
suffix:semicolon
)brace
r_return
id|elf_entry
suffix:semicolon
)brace
multiline_comment|/*&n; * These are the functions used to load ELF style executables and shared&n; * libraries.  There is no binary dependent code anywhere else.&n; */
DECL|macro|INTERPRETER_NONE
mdefine_line|#define INTERPRETER_NONE 0
DECL|macro|INTERPRETER_AOUT
mdefine_line|#define INTERPRETER_AOUT 1
DECL|macro|INTERPRETER_ELF
mdefine_line|#define INTERPRETER_ELF 2
DECL|function|load_elf_binary
r_int
id|load_elf_binary
c_func
(paren
r_struct
id|linux_binprm
op_star
id|bprm
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|elfhdr
id|elf_ex
suffix:semicolon
r_struct
id|elfhdr
id|interp_elf_ex
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|exec
id|interp_ex
suffix:semicolon
r_struct
id|inode
op_star
id|interpreter_inode
suffix:semicolon
r_int
r_int
id|load_addr
suffix:semicolon
r_int
r_int
id|interpreter_type
op_assign
id|INTERPRETER_NONE
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|old_fs
suffix:semicolon
r_int
id|error
suffix:semicolon
r_struct
id|elf_phdr
op_star
id|elf_ppnt
comma
op_star
id|elf_phdata
suffix:semicolon
r_int
id|elf_exec_fileno
suffix:semicolon
r_int
r_int
id|elf_bss
comma
id|k
comma
id|elf_brk
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_char
op_star
id|elf_interpreter
suffix:semicolon
r_int
r_int
id|elf_entry
suffix:semicolon
r_int
id|status
suffix:semicolon
r_int
r_int
id|start_code
comma
id|end_code
comma
id|end_data
suffix:semicolon
r_int
r_int
id|elf_stack
suffix:semicolon
r_char
id|passed_fileno
(braket
l_int|6
)braket
suffix:semicolon
id|status
op_assign
l_int|0
suffix:semicolon
id|load_addr
op_assign
l_int|0
suffix:semicolon
id|elf_ex
op_assign
op_star
(paren
(paren
r_struct
id|elfhdr
op_star
)paren
id|bprm-&gt;buf
)paren
suffix:semicolon
multiline_comment|/* exec-header */
r_if
c_cond
(paren
id|elf_ex.e_ident
(braket
l_int|0
)braket
op_ne
l_int|0x7f
op_logical_or
id|strncmp
c_func
(paren
op_amp
id|elf_ex.e_ident
(braket
l_int|1
)braket
comma
l_string|&quot;ELF&quot;
comma
l_int|3
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|ENOEXEC
suffix:semicolon
multiline_comment|/* First of all, some simple consistency checks */
r_if
c_cond
(paren
id|elf_ex.e_type
op_ne
id|ET_EXEC
op_logical_or
(paren
id|elf_ex.e_machine
op_ne
id|EM_386
op_logical_and
id|elf_ex.e_machine
op_ne
id|EM_486
)paren
op_logical_or
(paren
op_logical_neg
id|bprm-&gt;inode-&gt;i_op
op_logical_or
op_logical_neg
id|bprm-&gt;inode-&gt;i_op-&gt;default_file_ops
op_logical_or
op_logical_neg
id|bprm-&gt;inode-&gt;i_op-&gt;default_file_ops-&gt;mmap
)paren
)paren
(brace
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Now read in all of the header information */
id|elf_phdata
op_assign
(paren
r_struct
id|elf_phdr
op_star
)paren
id|kmalloc
c_func
(paren
id|elf_ex.e_phentsize
op_star
id|elf_ex.e_phnum
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
id|retval
op_assign
id|read_exec
c_func
(paren
id|bprm-&gt;inode
comma
id|elf_ex.e_phoff
comma
(paren
r_char
op_star
)paren
id|elf_phdata
comma
id|elf_ex.e_phentsize
op_star
id|elf_ex.e_phnum
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
(brace
id|kfree
(paren
id|elf_phdata
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
id|elf_ppnt
op_assign
id|elf_phdata
suffix:semicolon
id|elf_bss
op_assign
l_int|0
suffix:semicolon
id|elf_brk
op_assign
l_int|0
suffix:semicolon
id|elf_exec_fileno
op_assign
id|open_inode
c_func
(paren
id|bprm-&gt;inode
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|elf_exec_fileno
OL
l_int|0
)paren
(brace
id|kfree
(paren
id|elf_phdata
)paren
suffix:semicolon
r_return
id|elf_exec_fileno
suffix:semicolon
)brace
id|file
op_assign
id|current-&gt;files-&gt;fd
(braket
id|elf_exec_fileno
)braket
suffix:semicolon
id|elf_stack
op_assign
l_int|0xffffffff
suffix:semicolon
id|elf_interpreter
op_assign
l_int|NULL
suffix:semicolon
id|start_code
op_assign
l_int|0
suffix:semicolon
id|end_code
op_assign
l_int|0
suffix:semicolon
id|end_data
op_assign
l_int|0
suffix:semicolon
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|elf_ex.e_phnum
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|elf_ppnt-&gt;p_type
op_eq
id|PT_INTERP
)paren
(brace
multiline_comment|/* This is the program interpreter used for shared libraries - &n;&t;&t;&t;   for now assume that this is an a.out format binary */
id|elf_interpreter
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|elf_ppnt-&gt;p_filesz
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|retval
op_assign
id|read_exec
c_func
(paren
id|bprm-&gt;inode
comma
id|elf_ppnt-&gt;p_offset
comma
id|elf_interpreter
comma
id|elf_ppnt-&gt;p_filesz
)paren
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;Using ELF interpreter %s&bslash;n&quot;
comma
id|elf_interpreter
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|retval
op_ge
l_int|0
)paren
(brace
id|retval
op_assign
id|namei
c_func
(paren
id|elf_interpreter
comma
op_amp
id|interpreter_inode
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retval
op_ge
l_int|0
)paren
(brace
id|retval
op_assign
id|read_exec
c_func
(paren
id|interpreter_inode
comma
l_int|0
comma
id|bprm-&gt;buf
comma
l_int|128
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retval
op_ge
l_int|0
)paren
(brace
id|interp_ex
op_assign
op_star
(paren
(paren
r_struct
id|exec
op_star
)paren
id|bprm-&gt;buf
)paren
suffix:semicolon
multiline_comment|/* exec-header */
id|interp_elf_ex
op_assign
op_star
(paren
(paren
r_struct
id|elfhdr
op_star
)paren
id|bprm-&gt;buf
)paren
suffix:semicolon
multiline_comment|/* exec-header */
)brace
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
(brace
id|kfree
(paren
id|elf_phdata
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|elf_interpreter
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
suffix:semicolon
)brace
suffix:semicolon
id|elf_ppnt
op_increment
suffix:semicolon
)brace
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
multiline_comment|/* Some simple consistency checks for the interpreter */
r_if
c_cond
(paren
id|elf_interpreter
)paren
(brace
id|interpreter_type
op_assign
id|INTERPRETER_ELF
op_or
id|INTERPRETER_AOUT
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|elf_interpreter
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|elf_phdata
)paren
suffix:semicolon
r_return
op_minus
id|ELIBACC
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Now figure out which format our binary is */
r_if
c_cond
(paren
(paren
id|N_MAGIC
c_func
(paren
id|interp_ex
)paren
op_ne
id|OMAGIC
)paren
op_logical_and
(paren
id|N_MAGIC
c_func
(paren
id|interp_ex
)paren
op_ne
id|ZMAGIC
)paren
op_logical_and
(paren
id|N_MAGIC
c_func
(paren
id|interp_ex
)paren
op_ne
id|QMAGIC
)paren
)paren
(brace
id|interpreter_type
op_assign
id|INTERPRETER_ELF
suffix:semicolon
)brace
r_if
c_cond
(paren
id|interp_elf_ex.e_ident
(braket
l_int|0
)braket
op_ne
l_int|0x7f
op_logical_or
id|strncmp
c_func
(paren
op_amp
id|interp_elf_ex.e_ident
(braket
l_int|1
)braket
comma
l_string|&quot;ELF&quot;
comma
l_int|3
)paren
op_ne
l_int|0
)paren
id|interpreter_type
op_and_assign
op_complement
id|INTERPRETER_ELF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|interpreter_type
)paren
(brace
id|kfree
c_func
(paren
id|elf_interpreter
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|elf_phdata
)paren
suffix:semicolon
r_return
op_minus
id|ELIBBAD
suffix:semicolon
)brace
suffix:semicolon
)brace
multiline_comment|/* OK, we are done with that, now set up the arg stuff,&n;&t;   and then start this sucker up */
r_if
c_cond
(paren
op_logical_neg
id|bprm-&gt;sh_bang
)paren
(brace
r_char
op_star
id|passed_p
suffix:semicolon
r_if
c_cond
(paren
id|interpreter_type
op_eq
id|INTERPRETER_AOUT
)paren
(brace
id|sprintf
c_func
(paren
id|passed_fileno
comma
l_string|&quot;%d&quot;
comma
id|elf_exec_fileno
)paren
suffix:semicolon
id|passed_p
op_assign
id|passed_fileno
suffix:semicolon
r_if
c_cond
(paren
id|elf_interpreter
)paren
(brace
id|bprm-&gt;p
op_assign
id|copy_strings
c_func
(paren
l_int|1
comma
op_amp
id|passed_p
comma
id|bprm-&gt;page
comma
id|bprm-&gt;p
comma
l_int|2
)paren
suffix:semicolon
id|bprm-&gt;argc
op_increment
suffix:semicolon
)brace
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bprm-&gt;p
)paren
(brace
r_if
c_cond
(paren
id|elf_interpreter
)paren
(brace
id|kfree
c_func
(paren
id|elf_interpreter
)paren
suffix:semicolon
)brace
id|kfree
(paren
id|elf_phdata
)paren
suffix:semicolon
r_return
op_minus
id|E2BIG
suffix:semicolon
)brace
)brace
multiline_comment|/* OK, This is the point of no return */
id|flush_old_exec
c_func
(paren
id|bprm
)paren
suffix:semicolon
id|current-&gt;mm-&gt;end_data
op_assign
l_int|0
suffix:semicolon
id|current-&gt;mm-&gt;end_code
op_assign
l_int|0
suffix:semicolon
id|current-&gt;mm-&gt;start_mmap
op_assign
id|ELF_START_MMAP
suffix:semicolon
id|current-&gt;mm-&gt;mmap
op_assign
l_int|NULL
suffix:semicolon
id|elf_entry
op_assign
(paren
r_int
r_int
)paren
id|elf_ex.e_entry
suffix:semicolon
multiline_comment|/* Do this so that we can load the interpreter, if need be.  We will&n;&t;   change some of these later */
id|current-&gt;mm-&gt;rss
op_assign
l_int|0
suffix:semicolon
id|bprm-&gt;p
op_add_assign
id|change_ldt
c_func
(paren
l_int|0
comma
id|bprm-&gt;page
)paren
suffix:semicolon
id|current-&gt;mm-&gt;start_stack
op_assign
id|bprm-&gt;p
suffix:semicolon
multiline_comment|/* Now we do a little grungy work by mmaping the ELF image into&n;&t;   the correct location in memory.  At this point, we assume that&n;&t;   the image should be loaded at fixed address, not at a variable&n;&t;   address. */
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
id|elf_ppnt
op_assign
id|elf_phdata
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|elf_ex.e_phnum
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|elf_ppnt-&gt;p_type
op_eq
id|PT_INTERP
)paren
(brace
multiline_comment|/* Set these up so that we are able to load the interpreter */
multiline_comment|/* Now load the interpreter into user address space */
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|interpreter_type
op_amp
l_int|1
)paren
(brace
id|elf_entry
op_assign
id|load_aout_interp
c_func
(paren
op_amp
id|interp_ex
comma
id|interpreter_inode
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|interpreter_type
op_amp
l_int|2
)paren
(brace
id|elf_entry
op_assign
id|load_elf_interp
c_func
(paren
op_amp
id|interp_elf_ex
comma
id|interpreter_inode
)paren
suffix:semicolon
)brace
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
id|iput
c_func
(paren
id|interpreter_inode
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|elf_interpreter
)paren
suffix:semicolon
r_if
c_cond
(paren
id|elf_entry
op_eq
l_int|0xffffffff
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to load interpreter&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|elf_phdata
)paren
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGSEGV
comma
id|current
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
id|elf_ppnt-&gt;p_type
op_eq
id|PT_LOAD
)paren
(brace
id|error
op_assign
id|do_mmap
c_func
(paren
id|file
comma
id|elf_ppnt-&gt;p_vaddr
op_amp
l_int|0xfffff000
comma
id|elf_ppnt-&gt;p_filesz
op_plus
(paren
id|elf_ppnt-&gt;p_vaddr
op_amp
l_int|0xfff
)paren
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
comma
id|elf_ppnt-&gt;p_offset
op_amp
l_int|0xfffff000
)paren
suffix:semicolon
macro_line|#ifdef LOW_ELF_STACK
r_if
c_cond
(paren
id|elf_ppnt-&gt;p_vaddr
op_amp
l_int|0xfffff000
OL
id|elf_stack
)paren
(brace
id|elf_stack
op_assign
id|elf_ppnt-&gt;p_vaddr
op_amp
l_int|0xfffff000
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|load_addr
)paren
(brace
id|load_addr
op_assign
id|elf_ppnt-&gt;p_vaddr
op_minus
id|elf_ppnt-&gt;p_offset
suffix:semicolon
)brace
id|k
op_assign
id|elf_ppnt-&gt;p_vaddr
suffix:semicolon
r_if
c_cond
(paren
id|k
OG
id|start_code
)paren
(brace
id|start_code
op_assign
id|k
suffix:semicolon
)brace
id|k
op_assign
id|elf_ppnt-&gt;p_vaddr
op_plus
id|elf_ppnt-&gt;p_filesz
suffix:semicolon
r_if
c_cond
(paren
id|k
OG
id|elf_bss
)paren
(brace
id|elf_bss
op_assign
id|k
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|elf_ppnt-&gt;p_flags
op_or
id|PROT_WRITE
)paren
op_logical_and
id|end_code
OL
id|k
)paren
(brace
id|end_code
op_assign
id|k
suffix:semicolon
)brace
r_if
c_cond
(paren
id|end_data
OL
id|k
)paren
(brace
id|end_data
op_assign
id|k
suffix:semicolon
)brace
id|k
op_assign
id|elf_ppnt-&gt;p_vaddr
op_plus
id|elf_ppnt-&gt;p_memsz
suffix:semicolon
r_if
c_cond
(paren
id|k
OG
id|elf_brk
)paren
(brace
id|elf_brk
op_assign
id|k
suffix:semicolon
)brace
)brace
suffix:semicolon
id|elf_ppnt
op_increment
suffix:semicolon
)brace
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|elf_phdata
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|elf_interpreter
)paren
(brace
id|sys_close
c_func
(paren
id|elf_exec_fileno
)paren
suffix:semicolon
)brace
id|current-&gt;elf_executable
op_assign
l_int|1
suffix:semicolon
id|current-&gt;executable
op_assign
id|bprm-&gt;inode
suffix:semicolon
id|bprm-&gt;inode-&gt;i_count
op_increment
suffix:semicolon
macro_line|#ifdef LOW_ELF_STACK
id|current-&gt;start_stack
op_assign
id|p
op_assign
id|elf_stack
op_minus
l_int|4
suffix:semicolon
macro_line|#endif
id|bprm-&gt;p
op_sub_assign
id|MAX_ARG_PAGES
op_star
id|PAGE_SIZE
suffix:semicolon
id|bprm-&gt;p
op_assign
(paren
r_int
r_int
)paren
id|create_elf_tables
c_func
(paren
(paren
r_char
op_star
)paren
id|bprm-&gt;p
comma
id|bprm-&gt;argc
comma
id|bprm-&gt;envc
comma
(paren
id|interpreter_type
op_eq
id|INTERPRETER_ELF
ques
c_cond
op_amp
id|elf_ex
suffix:colon
l_int|NULL
)paren
comma
id|load_addr
comma
(paren
id|interpreter_type
op_eq
id|INTERPRETER_AOUT
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|interpreter_type
op_eq
id|INTERPRETER_AOUT
)paren
(brace
id|current-&gt;mm-&gt;arg_start
op_add_assign
id|strlen
c_func
(paren
id|passed_fileno
)paren
op_plus
l_int|1
suffix:semicolon
)brace
id|current-&gt;mm-&gt;start_brk
op_assign
id|current-&gt;mm-&gt;brk
op_assign
id|elf_brk
suffix:semicolon
id|current-&gt;mm-&gt;end_code
op_assign
id|end_code
suffix:semicolon
id|current-&gt;mm-&gt;start_code
op_assign
id|start_code
suffix:semicolon
id|current-&gt;mm-&gt;end_data
op_assign
id|end_data
suffix:semicolon
id|current-&gt;mm-&gt;start_stack
op_assign
id|bprm-&gt;p
suffix:semicolon
id|current-&gt;suid
op_assign
id|current-&gt;euid
op_assign
id|bprm-&gt;e_uid
suffix:semicolon
id|current-&gt;sgid
op_assign
id|current-&gt;egid
op_assign
id|bprm-&gt;e_gid
suffix:semicolon
multiline_comment|/* Calling sys_brk effectively mmaps the pages that we need for the bss and break&n;&t;   sections */
id|current-&gt;mm-&gt;brk
op_assign
(paren
id|elf_bss
op_plus
l_int|0xfff
)paren
op_amp
l_int|0xfffff000
suffix:semicolon
id|sys_brk
c_func
(paren
(paren
id|elf_brk
op_plus
l_int|0xfff
)paren
op_amp
l_int|0xfffff000
)paren
suffix:semicolon
id|padzero
c_func
(paren
id|elf_bss
)paren
suffix:semicolon
multiline_comment|/* Why this, you ask???  Well SVr4 maps page 0 as read-only,&n;&t;   and some applications &quot;depend&quot; upon this behavior.&n;&t;   Since we do not have the power to recompile these, we&n;&t;   emulate the SVr4 behavior.  Sigh.  */
id|error
op_assign
id|do_mmap
c_func
(paren
l_int|NULL
comma
l_int|0
comma
l_int|4096
comma
id|PROT_READ
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
comma
l_int|0
)paren
suffix:semicolon
id|regs-&gt;eip
op_assign
id|elf_entry
suffix:semicolon
multiline_comment|/* eip, magic happens :-) */
id|regs-&gt;esp
op_assign
id|bprm-&gt;p
suffix:semicolon
multiline_comment|/* stack pointer */
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_PTRACED
)paren
id|send_sig
c_func
(paren
id|SIGTRAP
comma
id|current
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* This is really simpleminded and specialized - we are loading an&n;   a.out library that is given an ELF header. */
DECL|function|load_elf_library
r_int
(def_block
id|load_elf_library
c_func
(paren
r_int
id|fd
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|elfhdr
id|elf_ex
suffix:semicolon
r_struct
id|elf_phdr
op_star
id|elf_phdata
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
r_int
id|elf_bss
suffix:semicolon
r_int
id|old_fs
comma
id|retval
suffix:semicolon
r_int
r_int
id|bss
suffix:semicolon
r_int
id|error
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|k
suffix:semicolon
id|len
op_assign
l_int|0
suffix:semicolon
id|file
op_assign
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
suffix:semicolon
id|inode
op_assign
id|file-&gt;f_inode
suffix:semicolon
id|elf_bss
op_assign
l_int|0
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_op
op_member_access_from_pointer
id|read
c_func
(paren
id|inode
comma
id|file
comma
(paren
r_char
op_star
)paren
op_amp
id|elf_ex
comma
r_sizeof
(paren
id|elf_ex
)paren
)paren
op_ne
r_sizeof
(paren
id|elf_ex
)paren
)paren
(brace
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|elf_ex.e_ident
(braket
l_int|0
)braket
op_ne
l_int|0x7f
op_logical_or
id|strncmp
c_func
(paren
op_amp
id|elf_ex.e_ident
(braket
l_int|1
)braket
comma
l_string|&quot;ELF&quot;
comma
l_int|3
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|ENOEXEC
suffix:semicolon
multiline_comment|/* First of all, some simple consistency checks */
r_if
c_cond
(paren
id|elf_ex.e_type
op_ne
id|ET_EXEC
op_logical_or
id|elf_ex.e_phnum
OG
l_int|2
op_logical_or
(paren
id|elf_ex.e_machine
op_ne
id|EM_386
op_logical_and
id|elf_ex.e_machine
op_ne
id|EM_486
)paren
op_logical_or
(paren
op_logical_neg
id|inode-&gt;i_op
op_logical_or
op_logical_neg
id|inode-&gt;i_op-&gt;bmap
op_logical_or
op_logical_neg
id|inode-&gt;i_op-&gt;default_file_ops-&gt;mmap
)paren
)paren
(brace
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Now read in all of the header information */
r_if
c_cond
(paren
r_sizeof
(paren
r_struct
id|elf_phdr
)paren
op_star
id|elf_ex.e_phnum
OG
id|PAGE_SIZE
)paren
(brace
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
id|elf_phdata
op_assign
(paren
r_struct
id|elf_phdr
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|elf_phdr
)paren
op_star
id|elf_ex.e_phnum
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
id|retval
op_assign
id|read_exec
c_func
(paren
id|inode
comma
id|elf_ex.e_phoff
comma
(paren
r_char
op_star
)paren
id|elf_phdata
comma
r_sizeof
(paren
r_struct
id|elf_phdr
)paren
op_star
id|elf_ex.e_phnum
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
id|j
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|elf_ex.e_phnum
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|elf_phdata
op_plus
id|i
)paren
op_member_access_from_pointer
id|p_type
op_eq
id|PT_LOAD
)paren
(brace
id|j
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|j
op_ne
l_int|1
)paren
(brace
id|kfree
c_func
(paren
id|elf_phdata
)paren
suffix:semicolon
r_return
op_minus
id|ENOEXEC
suffix:semicolon
)brace
suffix:semicolon
r_while
c_loop
(paren
id|elf_phdata-&gt;p_type
op_ne
id|PT_LOAD
)paren
(brace
id|elf_phdata
op_increment
suffix:semicolon
)brace
multiline_comment|/* Now use mmap to map the library into memory. */
id|error
op_assign
id|do_mmap
c_func
(paren
id|file
comma
id|elf_phdata-&gt;p_vaddr
op_amp
l_int|0xfffff000
comma
id|elf_phdata-&gt;p_filesz
op_plus
(paren
id|elf_phdata-&gt;p_vaddr
op_amp
l_int|0xfff
)paren
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
comma
id|elf_phdata-&gt;p_offset
op_amp
l_int|0xfffff000
)paren
suffix:semicolon
id|k
op_assign
id|elf_phdata-&gt;p_vaddr
op_plus
id|elf_phdata-&gt;p_filesz
suffix:semicolon
r_if
c_cond
(paren
id|k
OG
id|elf_bss
)paren
(brace
id|elf_bss
op_assign
id|k
suffix:semicolon
)brace
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ne
id|elf_phdata-&gt;p_vaddr
op_amp
l_int|0xfffff000
)paren
(brace
id|kfree
c_func
(paren
id|elf_phdata
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|padzero
c_func
(paren
id|elf_bss
)paren
suffix:semicolon
id|len
op_assign
(paren
id|elf_phdata-&gt;p_filesz
op_plus
id|elf_phdata-&gt;p_vaddr
op_plus
l_int|0xfff
)paren
op_amp
l_int|0xfffff000
suffix:semicolon
id|bss
op_assign
id|elf_phdata-&gt;p_memsz
op_plus
id|elf_phdata-&gt;p_vaddr
suffix:semicolon
r_if
c_cond
(paren
id|bss
OG
id|len
)paren
id|do_mmap
c_func
(paren
l_int|NULL
comma
id|len
comma
id|bss
op_minus
id|len
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_PRIVATE
comma
l_int|0
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|elf_phdata
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)def_block
eof
