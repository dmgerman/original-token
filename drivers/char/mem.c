multiline_comment|/*&n; *  linux/drivers/char/mem.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/tpqic02.h&gt;
macro_line|#include &lt;linux/ftape.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/joystick.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#ifdef CONFIG_SOUND
r_void
id|soundcore_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SOUND_OSS
r_void
id|soundcard_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DMASOUND
r_void
id|dmasound_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#ifdef CONFIG_SPARCAUDIO
r_extern
r_int
id|sparcaudio_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ISDN
r_int
id|isdn_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VIDEO_DEV
r_extern
r_int
id|videodev_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_FB
r_extern
r_void
id|fbmem_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PROM_CONSOLE
r_extern
r_void
id|prom_con_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MDA_CONSOLE
r_extern
r_void
id|mda_console_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_PPC) || defined(CONFIG_MAC)
r_extern
r_void
id|adbdev_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_USB_UHCI
r_int
id|uhci_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_USB_OHCI
r_int
id|ohci_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_USB_OHCI_HCD
r_int
id|ohci_hcd_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|function|do_write_mem
r_static
id|ssize_t
id|do_write_mem
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_void
op_star
id|p
comma
r_int
r_int
id|realp
comma
r_const
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
id|ssize_t
id|written
suffix:semicolon
id|written
op_assign
l_int|0
suffix:semicolon
macro_line|#if defined(__sparc__) || defined(__mc68000__)
multiline_comment|/* we don&squot;t have page 0 mapped on sparc and m68k.. */
r_if
c_cond
(paren
id|realp
OL
id|PAGE_SIZE
)paren
(brace
r_int
r_int
id|sz
op_assign
id|PAGE_SIZE
op_minus
id|realp
suffix:semicolon
r_if
c_cond
(paren
id|sz
OG
id|count
)paren
id|sz
op_assign
id|count
suffix:semicolon
multiline_comment|/* Hmm. Do something? */
id|buf
op_add_assign
id|sz
suffix:semicolon
id|p
op_add_assign
id|sz
suffix:semicolon
id|count
op_sub_assign
id|sz
suffix:semicolon
id|written
op_add_assign
id|sz
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|p
comma
id|buf
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|written
op_add_assign
id|count
suffix:semicolon
op_star
id|ppos
op_add_assign
id|written
suffix:semicolon
r_return
id|written
suffix:semicolon
)brace
multiline_comment|/*&n; * This funcion reads the *physical* memory. The f_pos points directly to the &n; * memory location. &n; */
DECL|function|read_mem
r_static
id|ssize_t
id|read_mem
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
id|p
op_assign
op_star
id|ppos
suffix:semicolon
r_int
r_int
id|end_mem
suffix:semicolon
id|ssize_t
id|read
suffix:semicolon
id|end_mem
op_assign
id|__pa
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
id|end_mem
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|end_mem
op_minus
id|p
)paren
id|count
op_assign
id|end_mem
op_minus
id|p
suffix:semicolon
id|read
op_assign
l_int|0
suffix:semicolon
macro_line|#if defined(__sparc__) || defined(__mc68000__)
multiline_comment|/* we don&squot;t have page 0 mapped on sparc and m68k.. */
r_if
c_cond
(paren
id|p
OL
id|PAGE_SIZE
)paren
(brace
r_int
r_int
id|sz
op_assign
id|PAGE_SIZE
op_minus
id|p
suffix:semicolon
r_if
c_cond
(paren
id|sz
OG
id|count
)paren
id|sz
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|sz
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|clear_user
c_func
(paren
id|buf
comma
id|sz
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|buf
op_add_assign
id|sz
suffix:semicolon
id|p
op_add_assign
id|sz
suffix:semicolon
id|count
op_sub_assign
id|sz
suffix:semicolon
id|read
op_add_assign
id|sz
suffix:semicolon
)brace
)brace
macro_line|#endif
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|__va
c_func
(paren
id|p
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
op_star
id|ppos
op_add_assign
id|read
suffix:semicolon
r_return
id|read
suffix:semicolon
)brace
DECL|function|write_mem
r_static
id|ssize_t
id|write_mem
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
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
id|p
op_assign
op_star
id|ppos
suffix:semicolon
r_int
r_int
id|end_mem
suffix:semicolon
id|end_mem
op_assign
id|__pa
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
id|end_mem
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|end_mem
op_minus
id|p
)paren
id|count
op_assign
id|end_mem
op_minus
id|p
suffix:semicolon
r_return
id|do_write_mem
c_func
(paren
id|file
comma
id|__va
c_func
(paren
id|p
)paren
comma
id|p
comma
id|buf
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This should probably be per-architecture in &lt;asm/pgtable.h&gt;&n; */
DECL|function|pgprot_noncached
r_static
r_inline
r_int
r_int
id|pgprot_noncached
c_func
(paren
r_int
r_int
id|prot
)paren
(brace
macro_line|#if defined(__i386__)
multiline_comment|/* On PPro and successors, PCD alone doesn&squot;t always mean &n;&t;    uncached because of interactions with the MTRRs. PCD | PWT&n;&t;    means definitely uncached. */
r_if
c_cond
(paren
id|boot_cpu_data.x86
OG
l_int|3
)paren
id|prot
op_or_assign
id|_PAGE_PCD
op_or
id|_PAGE_PWT
suffix:semicolon
macro_line|#elif defined(__powerpc__)
id|prot
op_or_assign
id|_PAGE_NO_CACHE
op_or
id|_PAGE_GUARDED
suffix:semicolon
macro_line|#elif defined(__mc68000__)
r_if
c_cond
(paren
id|CPU_IS_020_OR_030
)paren
id|prot
op_or_assign
id|_PAGE_NOCACHE030
suffix:semicolon
multiline_comment|/* Use no-cache mode, serialized */
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
id|prot
op_assign
(paren
id|prot
op_amp
id|_CACHEMASK040
)paren
op_or
id|_PAGE_NOCACHE_S
suffix:semicolon
macro_line|#elif defined(__mips__)
id|prot
op_assign
(paren
id|prot
op_amp
op_complement
id|_CACHE_MASK
)paren
op_or
id|_CACHE_UNCACHED
suffix:semicolon
macro_line|#endif
r_return
id|prot
suffix:semicolon
)brace
multiline_comment|/*&n; * Architectures vary in how they handle caching for addresses &n; * outside of main memory.&n; */
DECL|function|noncached_address
r_static
r_inline
r_int
id|noncached_address
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
macro_line|#if defined(__i386__)
multiline_comment|/* &n;&t; * On the PPro and successors, the MTRRs are used to set&n;&t; * memory types for physical addresses outside main memory, &n;&t; * so blindly setting PCD or PWT on those pages is wrong.&n;&t; * For Pentiums and earlier, the surround logic should disable &n;&t; * caching for the high addresses through the KEN pin, but&n;&t; * we maintain the tradition of paranoia in this code.&n;&t; */
r_return
op_logical_neg
(paren
id|boot_cpu_data.x86_capability
op_amp
id|X86_FEATURE_MTRR
)paren
op_logical_and
id|addr
op_ge
id|__pa
c_func
(paren
id|high_memory
)paren
suffix:semicolon
macro_line|#else
r_return
id|addr
op_ge
id|__pa
c_func
(paren
id|high_memory
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|mmap_mem
r_static
r_int
id|mmap_mem
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_int
r_int
id|offset
op_assign
id|vma-&gt;vm_offset
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_amp
op_complement
id|PAGE_MASK
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/*&n;&t; * Accessing memory above the top the kernel knows about or&n;&t; * through a file pointer that was marked O_SYNC will be&n;&t; * done non-cached.&n;&t; */
r_if
c_cond
(paren
id|noncached_address
c_func
(paren
id|offset
)paren
op_logical_or
(paren
id|file-&gt;f_flags
op_amp
id|O_SYNC
)paren
)paren
id|pgprot_val
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
op_assign
id|pgprot_noncached
c_func
(paren
id|pgprot_val
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t dump addresses that are not real memory to a core file.&n;&t; */
r_if
c_cond
(paren
id|offset
op_ge
id|__pa
c_func
(paren
id|high_memory
)paren
op_logical_or
(paren
id|file-&gt;f_flags
op_amp
id|O_SYNC
)paren
)paren
id|vma-&gt;vm_flags
op_or_assign
id|VM_IO
suffix:semicolon
r_if
c_cond
(paren
id|remap_page_range
c_func
(paren
id|vma-&gt;vm_start
comma
id|offset
comma
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_page_prot
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This function reads the *virtual* memory as seen by the kernel.&n; */
DECL|function|read_kmem
r_static
id|ssize_t
id|read_kmem
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
id|p
op_assign
op_star
id|ppos
suffix:semicolon
id|ssize_t
id|read
op_assign
l_int|0
suffix:semicolon
id|ssize_t
id|virtr
suffix:semicolon
r_if
c_cond
(paren
id|p
OL
(paren
r_int
r_int
)paren
id|high_memory
)paren
(brace
id|read
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
(paren
r_int
r_int
)paren
id|high_memory
op_minus
id|p
)paren
id|read
op_assign
(paren
r_int
r_int
)paren
id|high_memory
op_minus
id|p
suffix:semicolon
macro_line|#if defined(__sparc__) || defined(__mc68000__)
multiline_comment|/* we don&squot;t have page 0 mapped on sparc and m68k.. */
r_if
c_cond
(paren
id|p
template_param
l_int|0
)paren
(brace
r_int
id|tmp
op_assign
id|PAGE_SIZE
op_minus
id|p
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OG
id|read
)paren
id|tmp
op_assign
id|read
suffix:semicolon
id|clear_user
c_func
(paren
id|buf
comma
id|tmp
)paren
suffix:semicolon
id|buf
op_add_assign
id|tmp
suffix:semicolon
id|p
op_add_assign
id|tmp
suffix:semicolon
id|read
op_sub_assign
id|tmp
suffix:semicolon
id|count
op_sub_assign
id|tmp
suffix:semicolon
)brace
macro_line|#endif
id|copy_to_user
c_func
(paren
id|buf
comma
(paren
r_char
op_star
)paren
id|p
comma
id|read
)paren
suffix:semicolon
id|p
op_add_assign
id|read
suffix:semicolon
id|buf
op_add_assign
id|read
suffix:semicolon
id|count
op_sub_assign
id|read
suffix:semicolon
)brace
id|virtr
op_assign
id|vread
c_func
(paren
id|buf
comma
(paren
r_char
op_star
)paren
id|p
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|virtr
OL
l_int|0
)paren
r_return
id|virtr
suffix:semicolon
op_star
id|ppos
op_add_assign
id|p
op_plus
id|virtr
suffix:semicolon
r_return
id|virtr
op_plus
id|read
suffix:semicolon
)brace
multiline_comment|/*&n; * This function writes to the *virtual* memory as seen by the kernel.&n; */
DECL|function|write_kmem
r_static
id|ssize_t
id|write_kmem
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
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
id|p
op_assign
op_star
id|ppos
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ge
(paren
r_int
r_int
)paren
id|high_memory
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
(paren
r_int
r_int
)paren
id|high_memory
op_minus
id|p
)paren
id|count
op_assign
(paren
r_int
r_int
)paren
id|high_memory
op_minus
id|p
suffix:semicolon
r_return
id|do_write_mem
c_func
(paren
id|file
comma
(paren
r_void
op_star
)paren
id|p
comma
id|p
comma
id|buf
comma
id|count
comma
id|ppos
)paren
suffix:semicolon
)brace
DECL|function|read_port
r_static
id|ssize_t
id|read_port
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
id|i
op_assign
op_star
id|ppos
suffix:semicolon
r_char
op_star
id|tmp
op_assign
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
OG
l_int|0
op_logical_and
id|i
OL
l_int|65536
)paren
(brace
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|inb
c_func
(paren
id|i
)paren
comma
id|tmp
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|tmp
op_increment
suffix:semicolon
)brace
op_star
id|ppos
op_assign
id|i
suffix:semicolon
r_return
id|tmp
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|write_port
r_static
id|ssize_t
id|write_port
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
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
id|i
op_assign
op_star
id|ppos
suffix:semicolon
r_const
r_char
op_star
id|tmp
op_assign
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|buf
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
OG
l_int|0
op_logical_and
id|i
OL
l_int|65536
)paren
(brace
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|c
comma
id|tmp
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|outb
c_func
(paren
id|c
comma
id|i
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|tmp
op_increment
suffix:semicolon
)brace
op_star
id|ppos
op_assign
id|i
suffix:semicolon
r_return
id|tmp
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|read_null
r_static
id|ssize_t
id|read_null
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_null
r_static
id|ssize_t
id|write_null
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
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
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * For fun, we are using the MMU for this.&n; */
DECL|function|read_zero_pagealigned
r_static
r_inline
r_int
id|read_zero_pagealigned
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|size
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|buf
suffix:semicolon
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
multiline_comment|/* Oops, this was forgotten before. -ben */
id|down
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
multiline_comment|/* For private mappings, just map in zero pages. */
r_for
c_loop
(paren
id|vma
op_assign
id|find_vma
c_func
(paren
id|mm
comma
id|addr
)paren
suffix:semicolon
id|vma
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
)paren
(brace
r_int
r_int
id|count
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_start
OG
id|addr
op_logical_or
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_WRITE
)paren
op_eq
l_int|0
)paren
r_goto
id|out_up
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_SHARED
)paren
r_break
suffix:semicolon
id|count
op_assign
id|vma-&gt;vm_end
op_minus
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|size
)paren
id|count
op_assign
id|size
suffix:semicolon
id|flush_cache_range
c_func
(paren
id|mm
comma
id|addr
comma
id|addr
op_plus
id|count
)paren
suffix:semicolon
id|zap_page_range
c_func
(paren
id|mm
comma
id|addr
comma
id|count
)paren
suffix:semicolon
id|zeromap_page_range
c_func
(paren
id|addr
comma
id|count
comma
id|PAGE_COPY
)paren
suffix:semicolon
id|flush_tlb_range
c_func
(paren
id|mm
comma
id|addr
comma
id|addr
op_plus
id|count
)paren
suffix:semicolon
id|size
op_sub_assign
id|count
suffix:semicolon
id|buf
op_add_assign
id|count
suffix:semicolon
id|addr
op_add_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|size
op_eq
l_int|0
)paren
r_goto
id|out_up
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
multiline_comment|/* The shared case is hard. Let&squot;s do the conventional zeroing. */
r_do
(brace
r_int
r_int
id|unwritten
op_assign
id|clear_user
c_func
(paren
id|buf
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unwritten
)paren
r_return
id|size
op_plus
id|unwritten
op_minus
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;need_resched
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|buf
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|size
op_sub_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
)paren
suffix:semicolon
r_return
id|size
suffix:semicolon
id|out_up
suffix:colon
id|up
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
r_return
id|size
suffix:semicolon
)brace
DECL|function|read_zero
r_static
id|ssize_t
id|read_zero
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
id|left
comma
id|unwritten
comma
id|written
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|left
op_assign
id|count
suffix:semicolon
multiline_comment|/* do we want to be clever? Arbitrary cut-off */
r_if
c_cond
(paren
id|count
op_ge
id|PAGE_SIZE
op_star
l_int|4
)paren
(brace
r_int
r_int
id|partial
suffix:semicolon
multiline_comment|/* How much left of the page? */
id|partial
op_assign
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
op_minus
(paren
r_int
r_int
)paren
id|buf
suffix:semicolon
id|unwritten
op_assign
id|clear_user
c_func
(paren
id|buf
comma
id|partial
)paren
suffix:semicolon
id|written
op_assign
id|partial
op_minus
id|unwritten
suffix:semicolon
r_if
c_cond
(paren
id|unwritten
)paren
r_goto
id|out
suffix:semicolon
id|left
op_sub_assign
id|partial
suffix:semicolon
id|buf
op_add_assign
id|partial
suffix:semicolon
id|unwritten
op_assign
id|read_zero_pagealigned
c_func
(paren
id|buf
comma
id|left
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
id|written
op_add_assign
(paren
id|left
op_amp
id|PAGE_MASK
)paren
op_minus
id|unwritten
suffix:semicolon
r_if
c_cond
(paren
id|unwritten
)paren
r_goto
id|out
suffix:semicolon
id|buf
op_add_assign
id|left
op_amp
id|PAGE_MASK
suffix:semicolon
id|left
op_and_assign
op_complement
id|PAGE_MASK
suffix:semicolon
)brace
id|unwritten
op_assign
id|clear_user
c_func
(paren
id|buf
comma
id|left
)paren
suffix:semicolon
id|written
op_add_assign
id|left
op_minus
id|unwritten
suffix:semicolon
id|out
suffix:colon
r_return
id|written
ques
c_cond
id|written
suffix:colon
op_minus
id|EFAULT
suffix:semicolon
)brace
DECL|function|mmap_zero
r_static
r_int
id|mmap_zero
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_SHARED
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|zeromap_page_range
c_func
(paren
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_page_prot
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_full
r_static
id|ssize_t
id|write_full
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
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
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
multiline_comment|/*&n; * Special lseek() function for /dev/null and /dev/zero.  Most notably, you&n; * can fopen() both devices with &quot;a&quot; now.  This was previously impossible.&n; * -- SRB.&n; */
DECL|function|null_lseek
r_static
id|loff_t
id|null_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|orig
)paren
(brace
r_return
id|file-&gt;f_pos
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The memory devices use the full 32/64 bits of the offset, and so we cannot&n; * check against negative addresses: they are ok. The return value is weird,&n; * though, in that case (0).&n; *&n; * also note that seeking relative to the &quot;end of file&quot; isn&squot;t supported:&n; * it has no meaning, so it returns -EINVAL.&n; */
DECL|function|memory_lseek
r_static
id|loff_t
id|memory_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|offset
comma
r_int
id|orig
)paren
(brace
r_switch
c_cond
(paren
id|orig
)paren
(brace
r_case
l_int|0
suffix:colon
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
r_return
id|file-&gt;f_pos
suffix:semicolon
r_case
l_int|1
suffix:colon
id|file-&gt;f_pos
op_add_assign
id|offset
suffix:semicolon
r_return
id|file-&gt;f_pos
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|macro|mmap_kmem
mdefine_line|#define mmap_kmem&t;mmap_mem
DECL|macro|zero_lseek
mdefine_line|#define zero_lseek&t;null_lseek
DECL|macro|full_lseek
mdefine_line|#define full_lseek      null_lseek
DECL|macro|write_zero
mdefine_line|#define write_zero&t;write_null
DECL|macro|read_full
mdefine_line|#define read_full       read_zero
DECL|variable|mem_fops
r_static
r_struct
id|file_operations
id|mem_fops
op_assign
(brace
id|memory_lseek
comma
id|read_mem
comma
id|write_mem
comma
l_int|NULL
comma
multiline_comment|/* mem_readdir */
l_int|NULL
comma
multiline_comment|/* mem_poll */
l_int|NULL
comma
multiline_comment|/* mem_ioctl */
id|mmap_mem
comma
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
comma
multiline_comment|/* flush */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|kmem_fops
r_static
r_struct
id|file_operations
id|kmem_fops
op_assign
(brace
id|memory_lseek
comma
id|read_kmem
comma
id|write_kmem
comma
l_int|NULL
comma
multiline_comment|/* kmem_readdir */
l_int|NULL
comma
multiline_comment|/* kmem_poll */
l_int|NULL
comma
multiline_comment|/* kmem_ioctl */
id|mmap_kmem
comma
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
comma
multiline_comment|/* flush */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|null_fops
r_static
r_struct
id|file_operations
id|null_fops
op_assign
(brace
id|null_lseek
comma
id|read_null
comma
id|write_null
comma
l_int|NULL
comma
multiline_comment|/* null_readdir */
l_int|NULL
comma
multiline_comment|/* null_poll */
l_int|NULL
comma
multiline_comment|/* null_ioctl */
l_int|NULL
comma
multiline_comment|/* null_mmap */
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
comma
multiline_comment|/* flush */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|port_fops
r_static
r_struct
id|file_operations
id|port_fops
op_assign
(brace
id|memory_lseek
comma
id|read_port
comma
id|write_port
comma
l_int|NULL
comma
multiline_comment|/* port_readdir */
l_int|NULL
comma
multiline_comment|/* port_poll */
l_int|NULL
comma
multiline_comment|/* port_ioctl */
l_int|NULL
comma
multiline_comment|/* port_mmap */
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
comma
multiline_comment|/* flush */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|zero_fops
r_static
r_struct
id|file_operations
id|zero_fops
op_assign
(brace
id|zero_lseek
comma
id|read_zero
comma
id|write_zero
comma
l_int|NULL
comma
multiline_comment|/* zero_readdir */
l_int|NULL
comma
multiline_comment|/* zero_poll */
l_int|NULL
comma
multiline_comment|/* zero_ioctl */
id|mmap_zero
comma
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
comma
multiline_comment|/* flush */
l_int|NULL
multiline_comment|/* no special release code */
)brace
suffix:semicolon
DECL|variable|full_fops
r_static
r_struct
id|file_operations
id|full_fops
op_assign
(brace
id|full_lseek
comma
id|read_full
comma
id|write_full
comma
l_int|NULL
comma
multiline_comment|/* full_readdir */
l_int|NULL
comma
multiline_comment|/* full_poll */
l_int|NULL
comma
multiline_comment|/* full_ioctl */
l_int|NULL
comma
multiline_comment|/* full_mmap */
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
comma
multiline_comment|/* flush */
l_int|NULL
multiline_comment|/* no special release code */
)brace
suffix:semicolon
DECL|function|memory_open
r_static
r_int
id|memory_open
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
r_switch
c_cond
(paren
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
(brace
r_case
l_int|1
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|mem_fops
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|kmem_fops
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|null_fops
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if !defined(CONFIG_PPC) &amp;&amp; !defined(__mc68000__)
r_case
l_int|4
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|port_fops
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
l_int|5
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|zero_fops
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|full_fops
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|random_fops
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|urandom_fops
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filp-&gt;f_op
op_logical_and
id|filp-&gt;f_op-&gt;open
)paren
r_return
id|filp-&gt;f_op
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|filp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|memory_fops
r_static
r_struct
id|file_operations
id|memory_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek */
l_int|NULL
comma
multiline_comment|/* read */
l_int|NULL
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* poll */
l_int|NULL
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
id|memory_open
comma
multiline_comment|/* just a selector for the real open */
l_int|NULL
comma
multiline_comment|/* flush */
l_int|NULL
comma
multiline_comment|/* release */
l_int|NULL
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|chr_dev_init
c_func
(paren
r_void
)paren
)paren
(brace
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|MEM_MAJOR
comma
l_string|&quot;mem&quot;
comma
op_amp
id|memory_fops
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;unable to get major %d for memory devs&bslash;n&quot;
comma
id|MEM_MAJOR
)paren
suffix:semicolon
id|rand_initialize
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_USB
macro_line|#ifdef CONFIG_USB_UHCI
id|uhci_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_USB_OHCI
id|ohci_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_USB_OHCI_HCD
id|ohci_hcd_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#if defined (CONFIG_FB)
id|fbmem_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined (CONFIG_PROM_CONSOLE)
id|prom_con_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined (CONFIG_MDA_CONSOLE)
id|mda_console_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|tty_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PRINTER
id|lp_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_M68K_PRINTER
id|lp_m68k_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|misc_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SOUND
id|soundcore_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SOUND_OSS&t;
id|soundcard_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;
macro_line|#ifdef CONFIG_DMASOUND
id|dmasound_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;
macro_line|#endif
macro_line|#ifdef CONFIG_SPARCAUDIO
id|sparcaudio_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_JOYSTICK
multiline_comment|/*&n;&t; *&t;Some joysticks only appear when the sound card they are&n;&t; *&t;connected to is configured. Keep the sound/joystick ordering.&n;&t; */
id|js_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;
macro_line|#if CONFIG_QIC02_TAPE
id|qic02_tape_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if CONFIG_ISDN
id|isdn_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_FTAPE
id|ftape_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VIDEO_BT848
id|i2c_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_PPC) || defined(CONFIG_MAC)
id|adbdev_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VIDEO_DEV
id|videodev_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
eof
