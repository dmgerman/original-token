multiline_comment|/*&n; * These are the functions used to load COFF IBSC style executables.&n; * Information on COFF format may be obtained in either the Intel Binary&n; * Compatibility Specification 2 or O&squot;Rilley&squot;s book on COFF. The shared&n; * libraries are defined only the in the Intel book.&n; *&n; * This file is based upon code written by Eric Youndale for the ELF object&n; * file format.&n; *&n; * Author: Al Longyear (longyear@sii.com)&n; *&n; * Latest Revision:&n; *    3 Feburary 1994&n; *      Al Longyear (longyear@sii.com)&n; *      Cleared first page of bss section using put_fs_byte.&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/binfmts.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/coff.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
id|asmlinkage
r_int
id|sys_exit
(paren
r_int
id|exit_code
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_close
(paren
r_int
id|fd
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_open
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
id|sys_uselib
c_func
(paren
r_const
r_char
op_star
id|library
)paren
suffix:semicolon
r_static
r_int
id|preload_library
(paren
r_struct
id|linux_binprm
op_star
id|exe_bprm
comma
id|COFF_SCNHDR
op_star
id|sect
comma
r_struct
id|file
op_star
id|fp
)paren
suffix:semicolon
r_static
r_int
id|load_object
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
comma
r_int
id|lib_ok
)paren
suffix:semicolon
multiline_comment|/*&n; *  Small procedure to test for the proper file alignment.&n; */
r_static
r_inline
r_int
DECL|function|is_properly_aligned
id|is_properly_aligned
(paren
id|COFF_SCNHDR
op_star
id|sect
)paren
(brace
r_int
id|scnptr
op_assign
id|COFF_LONG
(paren
id|sect-&gt;s_scnptr
)paren
suffix:semicolon
r_int
id|vaddr
op_assign
id|COFF_LONG
(paren
id|sect-&gt;s_vaddr
)paren
suffix:semicolon
multiline_comment|/*&n; *  Print the section information if needed&n; */
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;%s, scnptr = %d, vaddr = %d&bslash;n&quot;
comma
id|sect-&gt;s_name
comma
id|scnptr
comma
id|vaddr
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *  Return the error code if the section is not properly aligned.&n; */
macro_line|#ifdef COFF_DEBUG
r_if
c_cond
(paren
(paren
(paren
id|vaddr
op_minus
id|scnptr
)paren
op_amp
op_complement
id|PAGE_MASK
)paren
op_ne
l_int|0
)paren
id|printk
(paren
l_string|&quot;bad alignment in %s&bslash;n&quot;
comma
id|sect-&gt;s_name
)paren
suffix:semicolon
macro_line|#endif
r_return
(paren
(paren
(paren
(paren
id|vaddr
op_minus
id|scnptr
)paren
op_amp
op_complement
id|PAGE_MASK
)paren
op_ne
l_int|0
)paren
ques
c_cond
op_minus
id|ENOEXEC
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *    Clear the bytes in the last page of data.&n; */
r_static
DECL|function|clear_memory
r_int
id|clear_memory
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_int
id|status
suffix:semicolon
id|size
op_assign
(paren
id|PAGE_SIZE
op_minus
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
)paren
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|0
)paren
id|status
op_assign
l_int|0
suffix:semicolon
r_else
(brace
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;un-initialized storage in last page %d&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
macro_line|#endif
id|status
op_assign
id|verify_area
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|addr
comma
id|size
)paren
suffix:semicolon
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;result from verify_area = %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|status
op_ge
l_int|0
)paren
r_while
c_loop
(paren
id|size
op_decrement
op_ne
l_int|0
)paren
id|put_fs_byte
(paren
l_int|0
comma
id|addr
op_increment
)paren
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; *  Helper function to process the load operation.&n; */
r_static
r_int
DECL|function|load_object
id|load_object
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
comma
r_int
id|lib_ok
)paren
(brace
id|COFF_FILHDR
op_star
id|coff_hdr
op_assign
(paren
id|COFF_FILHDR
op_star
)paren
id|bprm-&gt;buf
suffix:semicolon
multiline_comment|/* COFF Header */
id|COFF_SCNHDR
op_star
id|sect_bufr
suffix:semicolon
multiline_comment|/* Pointer to section table            */
id|COFF_SCNHDR
op_star
id|text_sect
suffix:semicolon
multiline_comment|/* Pointer to the text section         */
id|COFF_SCNHDR
op_star
id|data_sect
suffix:semicolon
multiline_comment|/* Pointer to the data section         */
id|COFF_SCNHDR
op_star
id|bss_sect
suffix:semicolon
multiline_comment|/* Pointer to the bss section          */
r_int
id|text_count
suffix:semicolon
multiline_comment|/* Number of text sections             */
r_int
id|data_count
suffix:semicolon
multiline_comment|/* Number of data sections             */
r_int
id|bss_count
suffix:semicolon
multiline_comment|/* Number of bss sections              */
r_int
id|lib_count
suffix:semicolon
multiline_comment|/* Number of lib sections              */
r_int
r_int
id|start_addr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Starting location for program       */
r_int
id|status
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Result status register              */
r_int
id|fd
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Open file descriptor                */
r_struct
id|file
op_star
id|fp
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Pointer to the file at &quot;fd&quot;         */
r_int
r_int
id|sections
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Number of sections in the file      */
r_int
r_int
id|aout_size
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Size of the a.out header area       */
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Flag bits from the COFF header      */
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;binfmt_coff entry: %s&bslash;n&quot;
comma
id|bprm-&gt;filename
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *  Validate the magic value for the object file.&n; */
r_do
(brace
r_if
c_cond
(paren
id|COFF_I386BADMAG
(paren
op_star
id|coff_hdr
)paren
)paren
(brace
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;bad filehdr magic&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|status
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n; *  The object file should have 32 BIT little endian format. Do not allow&n; *  it to have the 16 bit object file flag set as Linux is not able to run&n; *  on the 80286/80186/8086.&n; */
id|flags
op_assign
id|COFF_SHORT
(paren
id|coff_hdr-&gt;f_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
(paren
id|COFF_F_AR32WR
op_or
id|COFF_F_AR16WR
)paren
)paren
op_ne
id|COFF_F_AR32WR
)paren
(brace
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;invalid f_flags bits&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|status
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n; *  Extract the header information which we need.&n; */
id|sections
op_assign
id|COFF_SHORT
(paren
id|coff_hdr-&gt;f_nscns
)paren
suffix:semicolon
multiline_comment|/* Number of sections */
id|aout_size
op_assign
id|COFF_SHORT
(paren
id|coff_hdr-&gt;f_opthdr
)paren
suffix:semicolon
multiline_comment|/* Size of opt. headr */
multiline_comment|/*&n; *  If the file is not executable then reject the exectution. This means&n; *  that there must not be external references.&n; */
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|COFF_F_EXEC
)paren
op_eq
l_int|0
)paren
(brace
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;not executable bit&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|status
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n; *  There must be atleast one section.&n; */
r_if
c_cond
(paren
id|sections
op_eq
l_int|0
)paren
(brace
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;no sections&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|status
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n; *  Do some additional consistency checks.&n; *  The system requires mapping for this loader. If you try&n; *  to use a file system with no mapping, the format is not valid.&n; */
r_if
c_cond
(paren
op_logical_neg
id|bprm-&gt;inode-&gt;i_op
op_logical_or
op_logical_neg
id|bprm-&gt;inode-&gt;i_op-&gt;default_file_ops-&gt;mmap
)paren
(brace
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;no mmap in fs&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|status
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n; *  Allocate a buffer to hold the entire coff section list.&n; */
r_if
c_cond
(paren
id|status
op_ge
l_int|0
)paren
(brace
r_int
id|nbytes
op_assign
id|sections
op_star
id|COFF_SCNHSZ
suffix:semicolon
id|sect_bufr
op_assign
(paren
id|COFF_SCNHDR
op_star
)paren
id|kmalloc
(paren
id|nbytes
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_eq
id|sect_bufr
)paren
(brace
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;kmalloc failed&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|status
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
)brace
multiline_comment|/*&n; *  Read the section list from the disk file.&n; */
r_else
(brace
r_int
id|old_fs
op_assign
id|get_fs
(paren
)paren
suffix:semicolon
id|set_fs
(paren
id|get_ds
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Make it point to the proper location    */
id|status
op_assign
id|read_exec
(paren
id|bprm-&gt;inode
comma
multiline_comment|/* INODE for file       */
id|aout_size
op_plus
id|COFF_FILHSZ
comma
multiline_comment|/* Offset in the file   */
(paren
r_char
op_star
)paren
id|sect_bufr
comma
multiline_comment|/* Buffer for read      */
id|nbytes
)paren
suffix:semicolon
multiline_comment|/* Byte count reqd.     */
id|set_fs
(paren
id|old_fs
)paren
suffix:semicolon
multiline_comment|/* Restore the selector */
macro_line|#ifdef COFF_DEBUG
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
id|printk
(paren
l_string|&quot;read aout hdr, status = %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
r_else
id|sect_bufr
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Errors do not have a section buffer */
multiline_comment|/*&n; *  Count the number of sections for the required types and store the location&n; *  of the last section for the three primary types.&n; */
id|text_count
op_assign
l_int|0
suffix:semicolon
id|data_count
op_assign
l_int|0
suffix:semicolon
id|bss_count
op_assign
l_int|0
suffix:semicolon
id|lib_count
op_assign
l_int|0
suffix:semicolon
id|text_sect
op_assign
l_int|NULL
suffix:semicolon
id|data_sect
op_assign
l_int|NULL
suffix:semicolon
id|bss_sect
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; *  Loop through the sections and find the various types&n; */
r_if
c_cond
(paren
id|status
op_ge
l_int|0
)paren
(brace
r_int
id|nIndex
suffix:semicolon
id|COFF_SCNHDR
op_star
id|sect_ptr
op_assign
id|sect_bufr
suffix:semicolon
r_for
c_loop
(paren
id|nIndex
op_assign
l_int|0
suffix:semicolon
id|nIndex
OL
id|sections
suffix:semicolon
op_increment
id|nIndex
)paren
(brace
r_int
r_int
id|sect_flags
op_assign
id|COFF_LONG
(paren
id|sect_ptr-&gt;s_flags
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|sect_flags
)paren
(brace
r_case
id|COFF_STYP_TEXT
suffix:colon
id|text_sect
op_assign
id|sect_ptr
suffix:semicolon
op_increment
id|text_count
suffix:semicolon
id|status
op_assign
id|is_properly_aligned
(paren
id|sect_ptr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|COFF_STYP_DATA
suffix:colon
id|data_sect
op_assign
id|sect_ptr
suffix:semicolon
op_increment
id|data_count
suffix:semicolon
id|status
op_assign
id|is_properly_aligned
(paren
id|sect_ptr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|COFF_STYP_BSS
suffix:colon
id|bss_sect
op_assign
id|sect_ptr
suffix:semicolon
op_increment
id|bss_count
suffix:semicolon
r_break
suffix:semicolon
r_case
id|COFF_STYP_LIB
suffix:colon
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;.lib section found&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
op_increment
id|lib_count
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|sect_ptr
op_assign
(paren
id|COFF_SCNHDR
op_star
)paren
op_amp
(paren
(paren
r_char
op_star
)paren
id|sect_ptr
)paren
(braket
id|COFF_SCNHSZ
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; *  Ensure that there are the required sections. There must be one text&n; *  sections and one each of the data and bss sections for an executable.&n; *  A library may or may not have a data / bss section.&n; */
r_if
c_cond
(paren
id|text_count
op_ne
l_int|1
)paren
(brace
id|status
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;no text sections&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
r_if
c_cond
(paren
id|lib_ok
)paren
(brace
r_if
c_cond
(paren
id|data_count
op_ne
l_int|1
op_logical_or
id|bss_count
op_ne
l_int|1
)paren
(brace
id|status
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;no .data nor .bss sections&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
)brace
)brace
multiline_comment|/*&n; *  If there is no additional header then assume the file starts at&n; *  the first byte of the text section. This may not be the proper place,&n; *  so the best solution is to include the optional header. A shared library&n; *  __MUST__ have an optional header to indicate that it is a shared library.&n; */
r_if
c_cond
(paren
id|status
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|aout_size
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|lib_ok
)paren
(brace
id|status
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;no header in library&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
id|start_addr
op_assign
id|COFF_LONG
(paren
id|text_sect-&gt;s_vaddr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  There is some header. Ensure that it is sufficient.&n; */
r_else
(brace
r_if
c_cond
(paren
id|aout_size
OL
id|COFF_AOUTSZ
)paren
(brace
id|status
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;header too small&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
id|COFF_AOUTHDR
op_star
id|aout_hdr
op_assign
multiline_comment|/* Pointer to a.out header */
(paren
id|COFF_AOUTHDR
op_star
)paren
op_amp
(paren
(paren
r_char
op_star
)paren
id|coff_hdr
)paren
(braket
id|COFF_FILHSZ
)braket
suffix:semicolon
r_int
r_int
id|aout_magic
op_assign
id|COFF_SHORT
(paren
id|aout_hdr-&gt;magic
)paren
suffix:semicolon
multiline_comment|/* id */
multiline_comment|/*&n; *  Validate the magic number in the a.out header. If it is valid then&n; *  update the starting symbol location. Do not accept these file formats&n; *  when loading a shared library.&n; */
r_switch
c_cond
(paren
id|aout_magic
)paren
(brace
r_case
id|COFF_OMAGIC
suffix:colon
r_case
id|COFF_ZMAGIC
suffix:colon
r_case
id|COFF_STMAGIC
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|lib_ok
)paren
(brace
id|status
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;wrong a.out header magic&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
id|start_addr
op_assign
(paren
r_int
r_int
)paren
id|COFF_LONG
(paren
id|aout_hdr-&gt;entry
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n; *  Magic value for a shared library. This is valid only when loading a&n; *  shared library. (There is no need for a start_addr. It won&squot;t be used.)&n; */
r_case
id|COFF_SHMAGIC
suffix:colon
r_if
c_cond
(paren
id|lib_ok
)paren
(brace
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;wrong a.out header magic&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|status
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;wrong a.out header magic&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|status
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
)brace
multiline_comment|/*&n; *  Fetch a file pointer to the executable.&n; */
r_if
c_cond
(paren
id|status
op_ge
l_int|0
)paren
(brace
id|fd
op_assign
id|open_inode
(paren
id|bprm-&gt;inode
comma
id|O_RDONLY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;can not open inode, result = %d&bslash;n&quot;
comma
id|fd
)paren
suffix:semicolon
macro_line|#endif
id|status
op_assign
id|fd
suffix:semicolon
)brace
r_else
id|fp
op_assign
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
suffix:semicolon
)brace
r_else
id|fd
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Invalidate the open file descriptor */
multiline_comment|/*&n; *  Generate the proper values for the text fields&n; *&n; *  THIS IS THE POINT OF NO RETURN. THE NEW PROCESS WILL TRAP OUT SHOULD&n; *  SOMETHING FAIL IN THE LOAD SEQUENCE FROM THIS POINT ONWARD.&n; */
r_if
c_cond
(paren
id|status
op_ge
l_int|0
)paren
(brace
r_int
id|text_scnptr
op_assign
id|COFF_LONG
(paren
id|text_sect-&gt;s_scnptr
)paren
suffix:semicolon
r_int
id|text_size
op_assign
id|COFF_LONG
(paren
id|text_sect-&gt;s_size
)paren
suffix:semicolon
r_int
id|text_vaddr
op_assign
id|COFF_LONG
(paren
id|text_sect-&gt;s_vaddr
)paren
suffix:semicolon
r_int
id|data_scnptr
suffix:semicolon
r_int
id|data_size
suffix:semicolon
r_int
id|data_vaddr
suffix:semicolon
r_int
id|bss_size
suffix:semicolon
r_int
id|bss_vaddr
suffix:semicolon
multiline_comment|/*&n; *  Generate the proper values for the data fields&n; */
r_if
c_cond
(paren
id|data_sect
op_ne
l_int|NULL
)paren
(brace
id|data_scnptr
op_assign
id|COFF_LONG
(paren
id|data_sect-&gt;s_scnptr
)paren
suffix:semicolon
id|data_size
op_assign
id|COFF_LONG
(paren
id|data_sect-&gt;s_size
)paren
suffix:semicolon
id|data_vaddr
op_assign
id|COFF_LONG
(paren
id|data_sect-&gt;s_vaddr
)paren
suffix:semicolon
)brace
r_else
(brace
id|data_scnptr
op_assign
l_int|0
suffix:semicolon
id|data_size
op_assign
l_int|0
suffix:semicolon
id|data_vaddr
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Generate the proper values for the bss fields&n; */
r_if
c_cond
(paren
id|bss_sect
op_ne
l_int|NULL
)paren
(brace
id|bss_size
op_assign
id|COFF_LONG
(paren
id|bss_sect-&gt;s_size
)paren
suffix:semicolon
id|bss_vaddr
op_assign
id|COFF_LONG
(paren
id|bss_sect-&gt;s_vaddr
)paren
suffix:semicolon
)brace
r_else
(brace
id|bss_size
op_assign
l_int|0
suffix:semicolon
id|bss_vaddr
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Flush the executable from memory. At this point the executable is&n; *  committed to being defined or a segmentation violation will occur.&n; */
r_if
c_cond
(paren
id|lib_ok
)paren
(brace
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;flushing executable&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|flush_old_exec
(paren
id|bprm
)paren
suffix:semicolon
multiline_comment|/*&n; *  Define the initial locations for the various items in the new process&n; */
id|current-&gt;mm-&gt;mmap
op_assign
l_int|NULL
suffix:semicolon
id|current-&gt;mm-&gt;rss
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; *  Construct the parameter and environment string table entries.&n; */
id|bprm-&gt;p
op_add_assign
id|change_ldt
(paren
l_int|0
comma
id|bprm-&gt;page
)paren
suffix:semicolon
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
id|create_tables
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
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n; *  Do the end processing once the stack has been constructed&n; */
id|current-&gt;mm-&gt;start_code
op_assign
id|text_vaddr
op_amp
id|PAGE_MASK
suffix:semicolon
id|current-&gt;mm-&gt;end_code
op_assign
id|text_vaddr
op_plus
id|text_size
suffix:semicolon
id|current-&gt;mm-&gt;end_data
op_assign
id|data_vaddr
op_plus
id|data_size
suffix:semicolon
id|current-&gt;mm-&gt;start_brk
op_assign
id|current-&gt;mm-&gt;brk
op_assign
id|bss_vaddr
op_plus
id|bss_size
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
id|current-&gt;executable
op_assign
id|bprm-&gt;inode
suffix:semicolon
multiline_comment|/* Store inode for file  */
op_increment
id|bprm-&gt;inode-&gt;i_count
suffix:semicolon
multiline_comment|/* Count the open inode  */
id|regs-&gt;eip
op_assign
id|start_addr
suffix:semicolon
multiline_comment|/* Current EIP register  */
id|regs-&gt;esp
op_assign
id|current-&gt;mm-&gt;start_stack
op_assign
id|bprm-&gt;p
suffix:semicolon
)brace
multiline_comment|/*&n; *   Map the text pages&n; */
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;.text: vaddr = %d, size = %d, scnptr = %d&bslash;n&quot;
comma
id|text_vaddr
comma
id|text_size
comma
id|text_scnptr
)paren
suffix:semicolon
macro_line|#endif
id|status
op_assign
id|do_mmap
(paren
id|fp
comma
id|text_vaddr
op_amp
id|PAGE_MASK
comma
id|text_size
op_plus
(paren
id|text_vaddr
op_amp
op_complement
id|PAGE_MASK
)paren
comma
id|PROT_READ
op_or
id|PROT_EXEC
comma
id|MAP_FIXED
op_or
id|MAP_SHARED
comma
id|text_scnptr
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
id|status
op_assign
(paren
id|status
op_eq
(paren
id|text_vaddr
op_amp
id|PAGE_MASK
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENOEXEC
suffix:semicolon
multiline_comment|/*&n; *   Map the data pages&n; */
r_if
c_cond
(paren
id|status
op_ge
l_int|0
op_logical_and
id|data_size
op_ne
l_int|0
)paren
(brace
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;.data: vaddr = %d, size = %d, scnptr = %d&bslash;n&quot;
comma
id|data_vaddr
comma
id|data_size
comma
id|data_scnptr
)paren
suffix:semicolon
macro_line|#endif
id|status
op_assign
id|do_mmap
(paren
id|fp
comma
id|data_vaddr
op_amp
id|PAGE_MASK
comma
id|data_size
op_plus
(paren
id|data_vaddr
op_amp
op_complement
id|PAGE_MASK
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
id|data_scnptr
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
id|status
op_assign
(paren
id|status
op_eq
(paren
id|data_vaddr
op_amp
id|PAGE_MASK
)paren
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENOEXEC
suffix:semicolon
)brace
multiline_comment|/*&n; *   Construct the bss data for the process. The bss ranges from the&n; *   end of the data (which may not be on a page boundry) to the end&n; *   of the bss section. Allocate any necessary pages for the data.&n; */
r_if
c_cond
(paren
id|status
op_ge
l_int|0
op_logical_and
id|bss_size
op_ne
l_int|0
)paren
(brace
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;.bss: vaddr = %d, size = %d&bslash;n&quot;
comma
id|bss_vaddr
comma
id|bss_size
)paren
suffix:semicolon
macro_line|#endif
id|zeromap_page_range
(paren
id|PAGE_ALIGN
(paren
id|bss_vaddr
)paren
comma
id|PAGE_ALIGN
(paren
id|bss_size
)paren
comma
id|PAGE_COPY
)paren
suffix:semicolon
id|status
op_assign
id|clear_memory
(paren
id|bss_vaddr
comma
id|bss_size
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Load any shared library for the executable.&n; */
r_if
c_cond
(paren
id|status
op_ge
l_int|0
op_logical_and
id|lib_ok
op_logical_and
id|lib_count
op_ne
l_int|0
)paren
(brace
r_int
id|nIndex
suffix:semicolon
id|COFF_SCNHDR
op_star
id|sect_ptr
op_assign
id|sect_bufr
suffix:semicolon
multiline_comment|/*&n; *  Find the library sections. (There should be atleast one. It was counted&n; *  earlier.) This will evenutally recurse to our code and load the shared&n; *  library with our own procedures.&n; */
r_for
c_loop
(paren
id|nIndex
op_assign
l_int|0
suffix:semicolon
id|nIndex
OL
id|sections
suffix:semicolon
op_increment
id|nIndex
)paren
(brace
r_int
r_int
id|sect_flags
op_assign
id|COFF_LONG
(paren
id|sect_ptr-&gt;s_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sect_flags
op_eq
id|COFF_STYP_LIB
)paren
(brace
id|status
op_assign
id|preload_library
(paren
id|bprm
comma
id|sect_ptr
comma
id|fp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|sect_ptr
op_assign
(paren
id|COFF_SCNHDR
op_star
)paren
op_amp
(paren
(paren
r_char
op_star
)paren
id|sect_ptr
)paren
(braket
id|COFF_SCNHSZ
)braket
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *   Generate any needed trap for this process. If an error occured then&n; *   generate a segmentation violation. If the process is being debugged&n; *   then generate the load trap. (Note: If this is a library load then&n; *   do not generate the trap here. Pass the error to the caller who&n; *   will do it for the process in the outer lay of this procedure call.)&n; */
r_if
c_cond
(paren
id|lib_ok
)paren
(brace
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
id|send_sig
(paren
id|SIGSEGV
comma
id|current
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Generate the error trap  */
r_else
(brace
r_if
c_cond
(paren
id|current-&gt;flags
op_amp
id|PF_PTRACED
)paren
id|send_sig
(paren
id|SIGTRAP
comma
id|current
comma
l_int|0
)paren
suffix:semicolon
)brace
id|status
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* We are committed. It can&squot;t fail */
)brace
)brace
multiline_comment|/*&n; *  Do any cleanup processing&n; */
r_if
c_cond
(paren
id|fd
op_ge
l_int|0
)paren
id|sys_close
(paren
id|fd
)paren
suffix:semicolon
multiline_comment|/* Close unused code file      */
r_if
c_cond
(paren
id|sect_bufr
op_ne
l_int|NULL
)paren
id|kfree
(paren
id|sect_bufr
)paren
suffix:semicolon
multiline_comment|/* Release section list buffer */
multiline_comment|/*&n; *  Return the completion status.&n; */
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;binfmt_coff: result = %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
macro_line|#endif
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  This procedure will load the library listed in the file name given&n; *  as the paramter. The result will be non-zero should something fail&n; *  to load.&n; */
r_static
r_int
DECL|function|preload_this_library
id|preload_this_library
(paren
r_struct
id|linux_binprm
op_star
id|exe_bprm
comma
r_char
op_star
id|lib_name
)paren
(brace
r_int
id|status
suffix:semicolon
r_int
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n; *  If debugging then print &quot;we have arrived&quot;&n; */
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;%s loading shared library %s&bslash;n&quot;
comma
id|exe_bprm-&gt;filename
comma
id|lib_name
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *  Change the FS register to the proper kernel address space and attempt&n; *  to load the library. The library name is allocated from the kernel&n; *  pool.&n; */
id|set_fs
(paren
id|get_ds
(paren
)paren
)paren
suffix:semicolon
id|status
op_assign
id|sys_uselib
(paren
id|lib_name
)paren
suffix:semicolon
id|set_fs
(paren
id|old_fs
)paren
suffix:semicolon
multiline_comment|/*&n; *  Return the success/failure to the caller.&n; */
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  This procedure is called to load a library section. The various&n; *  libraries are loaded from the list given in the section data.&n; */
r_static
r_int
DECL|function|preload_library
id|preload_library
(paren
r_struct
id|linux_binprm
op_star
id|exe_bprm
comma
id|COFF_SCNHDR
op_star
id|sect
comma
r_struct
id|file
op_star
id|fp
)paren
(brace
r_int
id|status
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Completion status                  */
r_int
id|nbytes
suffix:semicolon
multiline_comment|/* Count of bytes in the header area  */
multiline_comment|/*&n; *  Fetch the size of the section. There must be enough room for atleast&n; *  one entry.&n; */
id|nbytes
op_assign
id|COFF_LONG
(paren
id|sect-&gt;s_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
OL
id|COFF_SLIBSZ
)paren
(brace
id|status
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;library section too small&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; *  Allocate a buffer to hold the section data&n; */
r_else
(brace
id|COFF_SLIBHD
op_star
id|phdr
suffix:semicolon
r_char
op_star
id|buffer
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
(paren
id|nbytes
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_eq
id|buffer
)paren
(brace
id|status
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;kmalloc failed&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
r_int
id|old_fs
op_assign
id|get_fs
(paren
)paren
suffix:semicolon
multiline_comment|/*&n; *  Read the section data from the disk file.&n; */
id|set_fs
(paren
id|get_ds
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Make it point to the proper location    */
id|status
op_assign
id|read_exec
(paren
id|exe_bprm-&gt;inode
comma
multiline_comment|/* INODE for file       */
id|COFF_LONG
(paren
id|sect-&gt;s_scnptr
)paren
comma
multiline_comment|/* Disk location     */
id|buffer
comma
multiline_comment|/* Buffer for read   */
id|nbytes
)paren
suffix:semicolon
multiline_comment|/* Byte count reqd.  */
id|set_fs
(paren
id|old_fs
)paren
suffix:semicolon
multiline_comment|/* Restore the selector */
multiline_comment|/*&n; *  Check the result. The value returned is the byte count actaully read.&n; */
r_if
c_cond
(paren
id|status
op_ge
l_int|0
op_logical_and
id|status
op_ne
id|nbytes
)paren
(brace
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;read of lib section was short&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|status
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *  At this point, go through the list of libraries in the data area.&n; */
id|phdr
op_assign
(paren
id|COFF_SLIBHD
op_star
)paren
id|buffer
suffix:semicolon
r_while
c_loop
(paren
id|status
op_ge
l_int|0
op_logical_and
id|nbytes
OG
id|COFF_SLIBSZ
)paren
(brace
r_int
id|entry_size
op_assign
id|COFF_LONG
(paren
id|phdr-&gt;sl_entsz
)paren
op_star
r_sizeof
(paren
r_int
)paren
suffix:semicolon
r_int
id|header_size
op_assign
id|COFF_LONG
(paren
id|phdr-&gt;sl_pathndx
)paren
op_star
r_sizeof
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; *  Validate the sizes of the various items. I don&squot;t trust the linker!!&n; */
r_if
c_cond
(paren
(paren
r_int
)paren
id|header_size
op_ge
(paren
r_int
)paren
id|nbytes
op_logical_or
id|entry_size
op_le
l_int|0
op_logical_or
(paren
r_int
)paren
id|entry_size
op_le
(paren
r_int
)paren
id|header_size
)paren
(brace
id|status
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;header count is invalid&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; *  Load the library. Stop the load process on the first error.&n; */
r_else
(brace
id|status
op_assign
id|preload_this_library
(paren
id|exe_bprm
comma
op_amp
(paren
(paren
r_char
op_star
)paren
id|phdr
)paren
(braket
id|header_size
)braket
)paren
suffix:semicolon
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;preload_this_library result = %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; *  Point to the next library in the section data.&n; */
id|nbytes
op_sub_assign
id|entry_size
suffix:semicolon
id|phdr
op_assign
(paren
id|COFF_SLIBHD
op_star
)paren
op_amp
(paren
(paren
r_char
op_star
)paren
id|phdr
)paren
(braket
id|entry_size
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; *  Release the space for the library list.&n; */
r_if
c_cond
(paren
id|buffer
op_ne
l_int|NULL
)paren
id|kfree
(paren
id|buffer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  Return the resulting status to the caller.&n; */
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *  This procedure is called by the main load sequence. It will load&n; *  the executable and prepare it for execution. It provides the additional&n; *  parameters used by the recursive coff loader and tells the loader that&n; *  this is the main executable. How simple it is . . . .&n; */
r_int
DECL|function|load_coff_binary
id|load_coff_binary
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
r_return
(paren
id|load_object
(paren
id|bprm
comma
id|regs
comma
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *   Load the image for any shared library.&n; *&n; *   This is called when we need to load a library based upon a file name.&n; */
r_int
DECL|function|load_coff_library
id|load_coff_library
(paren
r_int
id|fd
)paren
(brace
r_struct
id|linux_binprm
op_star
id|bprm
suffix:semicolon
multiline_comment|/* Parameters for the load operation   */
r_int
id|status
suffix:semicolon
multiline_comment|/* Status of the request               */
multiline_comment|/*&n; *  Read the first portion of the file.&n; */
id|bprm
op_assign
(paren
r_struct
id|linux_binprm
op_star
)paren
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|linux_binprm
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_eq
id|bprm
)paren
(brace
macro_line|#ifdef COFF_DEBUG
id|printk
(paren
l_string|&quot;kmalloc failed&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|status
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
)brace
r_else
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
multiline_comment|/* Pointer to the file table           */
r_struct
id|pt_regs
id|regs
suffix:semicolon
multiline_comment|/* Register work area                  */
r_int
id|old_fs
op_assign
id|get_fs
(paren
)paren
suffix:semicolon
multiline_comment|/* Previous FS register value          */
id|memset
(paren
id|bprm
comma
l_char|&squot;&bslash;0&squot;
comma
r_sizeof
(paren
r_struct
id|linux_binprm
)paren
)paren
suffix:semicolon
id|file
op_assign
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
suffix:semicolon
id|bprm-&gt;inode
op_assign
id|file-&gt;f_inode
suffix:semicolon
multiline_comment|/* The only item _really_ needed */
id|bprm-&gt;filename
op_assign
l_string|&quot;&quot;
suffix:semicolon
multiline_comment|/* Make it a legal string        */
multiline_comment|/*&n; *  Read the section list from the disk file.&n; */
id|set_fs
(paren
id|get_ds
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Make it point to the proper location    */
id|status
op_assign
id|read_exec
(paren
id|bprm-&gt;inode
comma
multiline_comment|/* INODE for file       */
l_int|0L
comma
multiline_comment|/* Offset in the file   */
id|bprm-&gt;buf
comma
multiline_comment|/* Buffer for read      */
r_sizeof
(paren
id|bprm-&gt;buf
)paren
)paren
suffix:semicolon
multiline_comment|/* Size of the buffer   */
id|set_fs
(paren
id|old_fs
)paren
suffix:semicolon
multiline_comment|/* Restore the selector */
multiline_comment|/*&n; *  Try to load the library.&n; */
id|status
op_assign
id|load_object
(paren
id|bprm
comma
op_amp
id|regs
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n; *  Release the work buffer and return the result.&n; */
id|kfree
(paren
id|bprm
)paren
suffix:semicolon
multiline_comment|/* Release the buffer area */
)brace
multiline_comment|/*&n; *  Return the result of the load operation&n; */
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
eof
