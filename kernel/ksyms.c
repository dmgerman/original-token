multiline_comment|/*&n; * Herein lies all the functions/variables that are &quot;exported&quot; for linkage&n; * with dynamically loaded kernel modules.&n; *&t;&t;&t;Jon.&n; *&n; * - Stacked module support and unified symbol table added (June 1994)&n; * - External symbol table support added (December 1994)&n; * - Versions on symbols added (December 1994)&n; *   by Bjorn Ekwall &lt;bj0rn@blox.se&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/cdrom.h&gt;
macro_line|#include &lt;linux/ucdrom.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/sys.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/binfmts.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/sem.h&gt;
macro_line|#include &lt;linux/minix_fs.h&gt;
macro_line|#include &lt;linux/ext2_fs.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/file.h&gt;
r_extern
r_int
r_char
id|aux_device_present
comma
id|kbd_read_mask
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
macro_line|#include &lt;linux/bios32.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#endif
macro_line|#if defined(CONFIG_PROC_FS)
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_KERNELD
macro_line|#include &lt;linux/kerneld.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#ifdef __SMP__
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#endif
r_extern
r_char
op_star
id|get_options
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
r_extern
r_void
id|set_device_ro
c_func
(paren
r_int
id|dev
comma
r_int
id|flag
)paren
suffix:semicolon
r_extern
r_struct
id|file_operations
op_star
id|get_blkfops
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|blkdev_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
macro_line|#if !defined(CONFIG_NFSD) &amp;&amp; defined(CONFIG_NFSD_MODULE)
r_extern
r_int
(paren
op_star
id|do_nfsservctl
)paren
(paren
r_int
comma
r_void
op_star
comma
r_void
op_star
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_void
op_star
id|sys_call_table
suffix:semicolon
r_extern
r_int
id|sys_tz
suffix:semicolon
r_extern
r_int
id|request_dma
c_func
(paren
r_int
r_int
id|dmanr
comma
r_char
op_star
id|deviceID
)paren
suffix:semicolon
r_extern
r_void
id|free_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
suffix:semicolon
macro_line|#ifdef MODVERSIONS
DECL|variable|__export_Using_Versions
r_const
r_struct
id|module_symbol
id|__export_Using_Versions
id|__attribute__
c_func
(paren
(paren
id|section
c_func
(paren
l_string|&quot;__ksymtab&quot;
)paren
)paren
)paren
op_assign
(brace
l_int|1
multiline_comment|/* Version version */
comma
l_string|&quot;Using_Versions&quot;
)brace
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MODULES
DECL|variable|get_module_symbol
id|EXPORT_SYMBOL
c_func
(paren
id|get_module_symbol
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_KERNELD
DECL|variable|kerneld_send
id|EXPORT_SYMBOL
c_func
(paren
id|kerneld_send
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|get_options
id|EXPORT_SYMBOL
c_func
(paren
id|get_options
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
multiline_comment|/* PCI BIOS support */
DECL|variable|pcibios_present
id|EXPORT_SYMBOL
c_func
(paren
id|pcibios_present
)paren
suffix:semicolon
DECL|variable|pcibios_find_class
id|EXPORT_SYMBOL
c_func
(paren
id|pcibios_find_class
)paren
suffix:semicolon
DECL|variable|pcibios_find_device
id|EXPORT_SYMBOL
c_func
(paren
id|pcibios_find_device
)paren
suffix:semicolon
DECL|variable|pcibios_read_config_byte
id|EXPORT_SYMBOL
c_func
(paren
id|pcibios_read_config_byte
)paren
suffix:semicolon
DECL|variable|pcibios_read_config_word
id|EXPORT_SYMBOL
c_func
(paren
id|pcibios_read_config_word
)paren
suffix:semicolon
DECL|variable|pcibios_read_config_dword
id|EXPORT_SYMBOL
c_func
(paren
id|pcibios_read_config_dword
)paren
suffix:semicolon
DECL|variable|pcibios_write_config_byte
id|EXPORT_SYMBOL
c_func
(paren
id|pcibios_write_config_byte
)paren
suffix:semicolon
DECL|variable|pcibios_write_config_word
id|EXPORT_SYMBOL
c_func
(paren
id|pcibios_write_config_word
)paren
suffix:semicolon
DECL|variable|pcibios_write_config_dword
id|EXPORT_SYMBOL
c_func
(paren
id|pcibios_write_config_dword
)paren
suffix:semicolon
DECL|variable|pcibios_strerror
id|EXPORT_SYMBOL
c_func
(paren
id|pcibios_strerror
)paren
suffix:semicolon
DECL|variable|pci_strvendor
id|EXPORT_SYMBOL
c_func
(paren
id|pci_strvendor
)paren
suffix:semicolon
DECL|variable|pci_strdev
id|EXPORT_SYMBOL
c_func
(paren
id|pci_strdev
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* process memory management */
DECL|variable|do_mmap
id|EXPORT_SYMBOL
c_func
(paren
id|do_mmap
)paren
suffix:semicolon
DECL|variable|do_munmap
id|EXPORT_SYMBOL
c_func
(paren
id|do_munmap
)paren
suffix:semicolon
DECL|variable|exit_mm
id|EXPORT_SYMBOL
c_func
(paren
id|exit_mm
)paren
suffix:semicolon
DECL|variable|exit_files
id|EXPORT_SYMBOL
c_func
(paren
id|exit_files
)paren
suffix:semicolon
multiline_comment|/* internal kernel memory management */
DECL|variable|__get_free_pages
id|EXPORT_SYMBOL
c_func
(paren
id|__get_free_pages
)paren
suffix:semicolon
DECL|variable|free_pages
id|EXPORT_SYMBOL
c_func
(paren
id|free_pages
)paren
suffix:semicolon
DECL|variable|__free_page
id|EXPORT_SYMBOL
c_func
(paren
id|__free_page
)paren
suffix:semicolon
DECL|variable|kmem_find_general_cachep
id|EXPORT_SYMBOL
c_func
(paren
id|kmem_find_general_cachep
)paren
suffix:semicolon
DECL|variable|kmem_cache_create
id|EXPORT_SYMBOL
c_func
(paren
id|kmem_cache_create
)paren
suffix:semicolon
DECL|variable|kmem_cache_shrink
id|EXPORT_SYMBOL
c_func
(paren
id|kmem_cache_shrink
)paren
suffix:semicolon
DECL|variable|kmem_cache_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|kmem_cache_alloc
)paren
suffix:semicolon
DECL|variable|kmem_cache_free
id|EXPORT_SYMBOL
c_func
(paren
id|kmem_cache_free
)paren
suffix:semicolon
DECL|variable|kmalloc
id|EXPORT_SYMBOL
c_func
(paren
id|kmalloc
)paren
suffix:semicolon
DECL|variable|kfree
id|EXPORT_SYMBOL
c_func
(paren
id|kfree
)paren
suffix:semicolon
DECL|variable|kfree_s
id|EXPORT_SYMBOL
c_func
(paren
id|kfree_s
)paren
suffix:semicolon
DECL|variable|vmalloc
id|EXPORT_SYMBOL
c_func
(paren
id|vmalloc
)paren
suffix:semicolon
DECL|variable|vfree
id|EXPORT_SYMBOL
c_func
(paren
id|vfree
)paren
suffix:semicolon
DECL|variable|mem_map
id|EXPORT_SYMBOL
c_func
(paren
id|mem_map
)paren
suffix:semicolon
DECL|variable|remap_page_range
id|EXPORT_SYMBOL
c_func
(paren
id|remap_page_range
)paren
suffix:semicolon
DECL|variable|max_mapnr
id|EXPORT_SYMBOL
c_func
(paren
id|max_mapnr
)paren
suffix:semicolon
DECL|variable|num_physpages
id|EXPORT_SYMBOL
c_func
(paren
id|num_physpages
)paren
suffix:semicolon
DECL|variable|high_memory
id|EXPORT_SYMBOL
c_func
(paren
id|high_memory
)paren
suffix:semicolon
DECL|variable|update_vm_cache
id|EXPORT_SYMBOL
c_func
(paren
id|update_vm_cache
)paren
suffix:semicolon
DECL|variable|vmtruncate
id|EXPORT_SYMBOL
c_func
(paren
id|vmtruncate
)paren
suffix:semicolon
multiline_comment|/* filesystem internal functions */
DECL|variable|get_super
id|EXPORT_SYMBOL
c_func
(paren
id|get_super
)paren
suffix:semicolon
DECL|variable|getname
id|EXPORT_SYMBOL
c_func
(paren
id|getname
)paren
suffix:semicolon
DECL|variable|putname
id|EXPORT_SYMBOL
c_func
(paren
id|putname
)paren
suffix:semicolon
DECL|variable|__fput
id|EXPORT_SYMBOL
c_func
(paren
id|__fput
)paren
suffix:semicolon
DECL|variable|iget
id|EXPORT_SYMBOL
c_func
(paren
id|iget
)paren
suffix:semicolon
DECL|variable|iput
id|EXPORT_SYMBOL
c_func
(paren
id|iput
)paren
suffix:semicolon
DECL|variable|__namei
id|EXPORT_SYMBOL
c_func
(paren
id|__namei
)paren
suffix:semicolon
DECL|variable|lookup_dentry
id|EXPORT_SYMBOL
c_func
(paren
id|lookup_dentry
)paren
suffix:semicolon
DECL|variable|open_namei
id|EXPORT_SYMBOL
c_func
(paren
id|open_namei
)paren
suffix:semicolon
DECL|variable|sys_close
id|EXPORT_SYMBOL
c_func
(paren
id|sys_close
)paren
suffix:semicolon
DECL|variable|close_fp
id|EXPORT_SYMBOL
c_func
(paren
id|close_fp
)paren
suffix:semicolon
DECL|variable|d_alloc_root
id|EXPORT_SYMBOL
c_func
(paren
id|d_alloc_root
)paren
suffix:semicolon
DECL|variable|d_delete
id|EXPORT_SYMBOL
c_func
(paren
id|d_delete
)paren
suffix:semicolon
DECL|variable|d_validate
id|EXPORT_SYMBOL
c_func
(paren
id|d_validate
)paren
suffix:semicolon
DECL|variable|d_add
id|EXPORT_SYMBOL
c_func
(paren
id|d_add
)paren
suffix:semicolon
DECL|variable|d_move
id|EXPORT_SYMBOL
c_func
(paren
id|d_move
)paren
suffix:semicolon
DECL|variable|d_instantiate
id|EXPORT_SYMBOL
c_func
(paren
id|d_instantiate
)paren
suffix:semicolon
DECL|variable|d_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|d_alloc
)paren
suffix:semicolon
DECL|variable|d_lookup
id|EXPORT_SYMBOL
c_func
(paren
id|d_lookup
)paren
suffix:semicolon
DECL|variable|__mark_inode_dirty
id|EXPORT_SYMBOL
c_func
(paren
id|__mark_inode_dirty
)paren
suffix:semicolon
DECL|variable|init_private_file
id|EXPORT_SYMBOL
c_func
(paren
id|init_private_file
)paren
suffix:semicolon
DECL|variable|insert_file_free
id|EXPORT_SYMBOL
c_func
(paren
id|insert_file_free
)paren
suffix:semicolon
DECL|variable|check_disk_change
id|EXPORT_SYMBOL
c_func
(paren
id|check_disk_change
)paren
suffix:semicolon
DECL|variable|invalidate_buffers
id|EXPORT_SYMBOL
c_func
(paren
id|invalidate_buffers
)paren
suffix:semicolon
DECL|variable|invalidate_inodes
id|EXPORT_SYMBOL
c_func
(paren
id|invalidate_inodes
)paren
suffix:semicolon
DECL|variable|invalidate_inode_pages
id|EXPORT_SYMBOL
c_func
(paren
id|invalidate_inode_pages
)paren
suffix:semicolon
DECL|variable|truncate_inode_pages
id|EXPORT_SYMBOL
c_func
(paren
id|truncate_inode_pages
)paren
suffix:semicolon
DECL|variable|fsync_dev
id|EXPORT_SYMBOL
c_func
(paren
id|fsync_dev
)paren
suffix:semicolon
DECL|variable|permission
id|EXPORT_SYMBOL
c_func
(paren
id|permission
)paren
suffix:semicolon
DECL|variable|inode_setattr
id|EXPORT_SYMBOL
c_func
(paren
id|inode_setattr
)paren
suffix:semicolon
DECL|variable|inode_change_ok
id|EXPORT_SYMBOL
c_func
(paren
id|inode_change_ok
)paren
suffix:semicolon
DECL|variable|write_inode_now
id|EXPORT_SYMBOL
c_func
(paren
id|write_inode_now
)paren
suffix:semicolon
DECL|variable|notify_change
id|EXPORT_SYMBOL
c_func
(paren
id|notify_change
)paren
suffix:semicolon
DECL|variable|get_hardblocksize
id|EXPORT_SYMBOL
c_func
(paren
id|get_hardblocksize
)paren
suffix:semicolon
DECL|variable|set_blocksize
id|EXPORT_SYMBOL
c_func
(paren
id|set_blocksize
)paren
suffix:semicolon
DECL|variable|getblk
id|EXPORT_SYMBOL
c_func
(paren
id|getblk
)paren
suffix:semicolon
DECL|variable|bread
id|EXPORT_SYMBOL
c_func
(paren
id|bread
)paren
suffix:semicolon
DECL|variable|breada
id|EXPORT_SYMBOL
c_func
(paren
id|breada
)paren
suffix:semicolon
DECL|variable|__brelse
id|EXPORT_SYMBOL
c_func
(paren
id|__brelse
)paren
suffix:semicolon
DECL|variable|__bforget
id|EXPORT_SYMBOL
c_func
(paren
id|__bforget
)paren
suffix:semicolon
DECL|variable|ll_rw_block
id|EXPORT_SYMBOL
c_func
(paren
id|ll_rw_block
)paren
suffix:semicolon
DECL|variable|__wait_on_buffer
id|EXPORT_SYMBOL
c_func
(paren
id|__wait_on_buffer
)paren
suffix:semicolon
DECL|variable|mark_buffer_uptodate
id|EXPORT_SYMBOL
c_func
(paren
id|mark_buffer_uptodate
)paren
suffix:semicolon
DECL|variable|add_blkdev_randomness
id|EXPORT_SYMBOL
c_func
(paren
id|add_blkdev_randomness
)paren
suffix:semicolon
DECL|variable|generic_file_read
id|EXPORT_SYMBOL
c_func
(paren
id|generic_file_read
)paren
suffix:semicolon
DECL|variable|generic_file_write
id|EXPORT_SYMBOL
c_func
(paren
id|generic_file_write
)paren
suffix:semicolon
DECL|variable|generic_file_mmap
id|EXPORT_SYMBOL
c_func
(paren
id|generic_file_mmap
)paren
suffix:semicolon
DECL|variable|generic_readpage
id|EXPORT_SYMBOL
c_func
(paren
id|generic_readpage
)paren
suffix:semicolon
DECL|variable|file_lock_table
id|EXPORT_SYMBOL
c_func
(paren
id|file_lock_table
)paren
suffix:semicolon
DECL|variable|posix_lock_file
id|EXPORT_SYMBOL
c_func
(paren
id|posix_lock_file
)paren
suffix:semicolon
DECL|variable|posix_test_lock
id|EXPORT_SYMBOL
c_func
(paren
id|posix_test_lock
)paren
suffix:semicolon
DECL|variable|posix_block_lock
id|EXPORT_SYMBOL
c_func
(paren
id|posix_block_lock
)paren
suffix:semicolon
DECL|variable|posix_unblock_lock
id|EXPORT_SYMBOL
c_func
(paren
id|posix_unblock_lock
)paren
suffix:semicolon
DECL|variable|dput
id|EXPORT_SYMBOL
c_func
(paren
id|dput
)paren
suffix:semicolon
DECL|variable|get_cached_page
id|EXPORT_SYMBOL
c_func
(paren
id|get_cached_page
)paren
suffix:semicolon
DECL|variable|put_cached_page
id|EXPORT_SYMBOL
c_func
(paren
id|put_cached_page
)paren
suffix:semicolon
DECL|variable|prune_dcache
id|EXPORT_SYMBOL
c_func
(paren
id|prune_dcache
)paren
suffix:semicolon
DECL|variable|shrink_dcache_sb
id|EXPORT_SYMBOL
c_func
(paren
id|shrink_dcache_sb
)paren
suffix:semicolon
DECL|variable|shrink_dcache_parent
id|EXPORT_SYMBOL
c_func
(paren
id|shrink_dcache_parent
)paren
suffix:semicolon
macro_line|#if !defined(CONFIG_NFSD) &amp;&amp; defined(CONFIG_NFSD_MODULE)
DECL|variable|do_nfsservctl
id|EXPORT_SYMBOL
c_func
(paren
id|do_nfsservctl
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* device registration */
DECL|variable|register_chrdev
id|EXPORT_SYMBOL
c_func
(paren
id|register_chrdev
)paren
suffix:semicolon
DECL|variable|unregister_chrdev
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_chrdev
)paren
suffix:semicolon
DECL|variable|register_blkdev
id|EXPORT_SYMBOL
c_func
(paren
id|register_blkdev
)paren
suffix:semicolon
DECL|variable|unregister_blkdev
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_blkdev
)paren
suffix:semicolon
DECL|variable|tty_register_driver
id|EXPORT_SYMBOL
c_func
(paren
id|tty_register_driver
)paren
suffix:semicolon
DECL|variable|tty_unregister_driver
id|EXPORT_SYMBOL
c_func
(paren
id|tty_unregister_driver
)paren
suffix:semicolon
DECL|variable|tty_std_termios
id|EXPORT_SYMBOL
c_func
(paren
id|tty_std_termios
)paren
suffix:semicolon
multiline_comment|/* block device driver support */
DECL|variable|block_read
id|EXPORT_SYMBOL
c_func
(paren
id|block_read
)paren
suffix:semicolon
DECL|variable|block_write
id|EXPORT_SYMBOL
c_func
(paren
id|block_write
)paren
suffix:semicolon
DECL|variable|block_fsync
id|EXPORT_SYMBOL
c_func
(paren
id|block_fsync
)paren
suffix:semicolon
DECL|variable|wait_for_request
id|EXPORT_SYMBOL
c_func
(paren
id|wait_for_request
)paren
suffix:semicolon
DECL|variable|blksize_size
id|EXPORT_SYMBOL
c_func
(paren
id|blksize_size
)paren
suffix:semicolon
DECL|variable|hardsect_size
id|EXPORT_SYMBOL
c_func
(paren
id|hardsect_size
)paren
suffix:semicolon
DECL|variable|blk_size
id|EXPORT_SYMBOL
c_func
(paren
id|blk_size
)paren
suffix:semicolon
DECL|variable|blk_dev
id|EXPORT_SYMBOL
c_func
(paren
id|blk_dev
)paren
suffix:semicolon
DECL|variable|is_read_only
id|EXPORT_SYMBOL
c_func
(paren
id|is_read_only
)paren
suffix:semicolon
DECL|variable|set_device_ro
id|EXPORT_SYMBOL
c_func
(paren
id|set_device_ro
)paren
suffix:semicolon
DECL|variable|bmap
id|EXPORT_SYMBOL
c_func
(paren
id|bmap
)paren
suffix:semicolon
DECL|variable|sync_dev
id|EXPORT_SYMBOL
c_func
(paren
id|sync_dev
)paren
suffix:semicolon
DECL|variable|get_blkfops
id|EXPORT_SYMBOL
c_func
(paren
id|get_blkfops
)paren
suffix:semicolon
DECL|variable|blkdev_open
id|EXPORT_SYMBOL
c_func
(paren
id|blkdev_open
)paren
suffix:semicolon
DECL|variable|blkdev_release
id|EXPORT_SYMBOL
c_func
(paren
id|blkdev_release
)paren
suffix:semicolon
DECL|variable|gendisk_head
id|EXPORT_SYMBOL
c_func
(paren
id|gendisk_head
)paren
suffix:semicolon
DECL|variable|resetup_one_dev
id|EXPORT_SYMBOL
c_func
(paren
id|resetup_one_dev
)paren
suffix:semicolon
DECL|variable|unplug_device
id|EXPORT_SYMBOL
c_func
(paren
id|unplug_device
)paren
suffix:semicolon
DECL|variable|make_request
id|EXPORT_SYMBOL
c_func
(paren
id|make_request
)paren
suffix:semicolon
DECL|variable|tq_disk
id|EXPORT_SYMBOL
c_func
(paren
id|tq_disk
)paren
suffix:semicolon
DECL|variable|efind_buffer
id|EXPORT_SYMBOL
c_func
(paren
id|efind_buffer
)paren
suffix:semicolon
DECL|variable|init_buffer
id|EXPORT_SYMBOL
c_func
(paren
id|init_buffer
)paren
suffix:semicolon
multiline_comment|/* tty routines */
DECL|variable|tty_hangup
id|EXPORT_SYMBOL
c_func
(paren
id|tty_hangup
)paren
suffix:semicolon
DECL|variable|tty_wait_until_sent
id|EXPORT_SYMBOL
c_func
(paren
id|tty_wait_until_sent
)paren
suffix:semicolon
DECL|variable|tty_check_change
id|EXPORT_SYMBOL
c_func
(paren
id|tty_check_change
)paren
suffix:semicolon
DECL|variable|tty_hung_up_p
id|EXPORT_SYMBOL
c_func
(paren
id|tty_hung_up_p
)paren
suffix:semicolon
DECL|variable|tty_flip_buffer_push
id|EXPORT_SYMBOL
c_func
(paren
id|tty_flip_buffer_push
)paren
suffix:semicolon
DECL|variable|tty_get_baud_rate
id|EXPORT_SYMBOL
c_func
(paren
id|tty_get_baud_rate
)paren
suffix:semicolon
DECL|variable|do_SAK
id|EXPORT_SYMBOL
c_func
(paren
id|do_SAK
)paren
suffix:semicolon
DECL|variable|console_print
id|EXPORT_SYMBOL
c_func
(paren
id|console_print
)paren
suffix:semicolon
multiline_comment|/* filesystem registration */
DECL|variable|register_filesystem
id|EXPORT_SYMBOL
c_func
(paren
id|register_filesystem
)paren
suffix:semicolon
DECL|variable|unregister_filesystem
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_filesystem
)paren
suffix:semicolon
multiline_comment|/* executable format registration */
DECL|variable|register_binfmt
id|EXPORT_SYMBOL
c_func
(paren
id|register_binfmt
)paren
suffix:semicolon
DECL|variable|unregister_binfmt
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_binfmt
)paren
suffix:semicolon
DECL|variable|search_binary_handler
id|EXPORT_SYMBOL
c_func
(paren
id|search_binary_handler
)paren
suffix:semicolon
DECL|variable|prepare_binprm
id|EXPORT_SYMBOL
c_func
(paren
id|prepare_binprm
)paren
suffix:semicolon
DECL|variable|remove_arg_zero
id|EXPORT_SYMBOL
c_func
(paren
id|remove_arg_zero
)paren
suffix:semicolon
multiline_comment|/* execution environment registration */
DECL|variable|lookup_exec_domain
id|EXPORT_SYMBOL
c_func
(paren
id|lookup_exec_domain
)paren
suffix:semicolon
DECL|variable|register_exec_domain
id|EXPORT_SYMBOL
c_func
(paren
id|register_exec_domain
)paren
suffix:semicolon
DECL|variable|unregister_exec_domain
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_exec_domain
)paren
suffix:semicolon
multiline_comment|/* sysctl table registration */
DECL|variable|register_sysctl_table
id|EXPORT_SYMBOL
c_func
(paren
id|register_sysctl_table
)paren
suffix:semicolon
DECL|variable|unregister_sysctl_table
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_sysctl_table
)paren
suffix:semicolon
DECL|variable|sysctl_string
id|EXPORT_SYMBOL
c_func
(paren
id|sysctl_string
)paren
suffix:semicolon
DECL|variable|sysctl_intvec
id|EXPORT_SYMBOL
c_func
(paren
id|sysctl_intvec
)paren
suffix:semicolon
DECL|variable|proc_dostring
id|EXPORT_SYMBOL
c_func
(paren
id|proc_dostring
)paren
suffix:semicolon
DECL|variable|proc_dointvec
id|EXPORT_SYMBOL
c_func
(paren
id|proc_dointvec
)paren
suffix:semicolon
DECL|variable|proc_dointvec_jiffies
id|EXPORT_SYMBOL
c_func
(paren
id|proc_dointvec_jiffies
)paren
suffix:semicolon
DECL|variable|proc_dointvec_minmax
id|EXPORT_SYMBOL
c_func
(paren
id|proc_dointvec_minmax
)paren
suffix:semicolon
multiline_comment|/* interrupt handling */
DECL|variable|request_irq
id|EXPORT_SYMBOL
c_func
(paren
id|request_irq
)paren
suffix:semicolon
DECL|variable|free_irq
id|EXPORT_SYMBOL
c_func
(paren
id|free_irq
)paren
suffix:semicolon
DECL|variable|enable_irq
id|EXPORT_SYMBOL
c_func
(paren
id|enable_irq
)paren
suffix:semicolon
DECL|variable|disable_irq
id|EXPORT_SYMBOL
c_func
(paren
id|disable_irq
)paren
suffix:semicolon
DECL|variable|probe_irq_on
id|EXPORT_SYMBOL
c_func
(paren
id|probe_irq_on
)paren
suffix:semicolon
DECL|variable|probe_irq_off
id|EXPORT_SYMBOL
c_func
(paren
id|probe_irq_off
)paren
suffix:semicolon
DECL|variable|bh_active
id|EXPORT_SYMBOL
c_func
(paren
id|bh_active
)paren
suffix:semicolon
DECL|variable|bh_mask
id|EXPORT_SYMBOL
c_func
(paren
id|bh_mask
)paren
suffix:semicolon
DECL|variable|bh_mask_count
id|EXPORT_SYMBOL
c_func
(paren
id|bh_mask_count
)paren
suffix:semicolon
DECL|variable|bh_base
id|EXPORT_SYMBOL
c_func
(paren
id|bh_base
)paren
suffix:semicolon
DECL|variable|add_timer
id|EXPORT_SYMBOL
c_func
(paren
id|add_timer
)paren
suffix:semicolon
DECL|variable|del_timer
id|EXPORT_SYMBOL
c_func
(paren
id|del_timer
)paren
suffix:semicolon
DECL|variable|tq_timer
id|EXPORT_SYMBOL
c_func
(paren
id|tq_timer
)paren
suffix:semicolon
DECL|variable|tq_immediate
id|EXPORT_SYMBOL
c_func
(paren
id|tq_immediate
)paren
suffix:semicolon
DECL|variable|tq_scheduler
id|EXPORT_SYMBOL
c_func
(paren
id|tq_scheduler
)paren
suffix:semicolon
DECL|variable|timer_active
id|EXPORT_SYMBOL
c_func
(paren
id|timer_active
)paren
suffix:semicolon
DECL|variable|timer_table
id|EXPORT_SYMBOL
c_func
(paren
id|timer_table
)paren
suffix:semicolon
macro_line|#ifdef __SMP__
multiline_comment|/* Various random spinlocks we want to export */
DECL|variable|tqueue_lock
id|EXPORT_SYMBOL
c_func
(paren
id|tqueue_lock
)paren
suffix:semicolon
DECL|variable|waitqueue_lock
id|EXPORT_SYMBOL
c_func
(paren
id|waitqueue_lock
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* autoirq from  drivers/net/auto_irq.c */
DECL|variable|autoirq_setup
id|EXPORT_SYMBOL
c_func
(paren
id|autoirq_setup
)paren
suffix:semicolon
DECL|variable|autoirq_report
id|EXPORT_SYMBOL
c_func
(paren
id|autoirq_report
)paren
suffix:semicolon
multiline_comment|/* dma handling */
DECL|variable|request_dma
id|EXPORT_SYMBOL
c_func
(paren
id|request_dma
)paren
suffix:semicolon
DECL|variable|free_dma
id|EXPORT_SYMBOL
c_func
(paren
id|free_dma
)paren
suffix:semicolon
macro_line|#ifdef HAVE_DISABLE_HLT
DECL|variable|disable_hlt
id|EXPORT_SYMBOL
c_func
(paren
id|disable_hlt
)paren
suffix:semicolon
DECL|variable|enable_hlt
id|EXPORT_SYMBOL
c_func
(paren
id|enable_hlt
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* IO port handling */
DECL|variable|check_region
id|EXPORT_SYMBOL
c_func
(paren
id|check_region
)paren
suffix:semicolon
DECL|variable|request_region
id|EXPORT_SYMBOL
c_func
(paren
id|request_region
)paren
suffix:semicolon
DECL|variable|release_region
id|EXPORT_SYMBOL
c_func
(paren
id|release_region
)paren
suffix:semicolon
multiline_comment|/* process management */
DECL|variable|wake_up
id|EXPORT_SYMBOL
c_func
(paren
id|wake_up
)paren
suffix:semicolon
DECL|variable|wake_up_interruptible
id|EXPORT_SYMBOL
c_func
(paren
id|wake_up_interruptible
)paren
suffix:semicolon
DECL|variable|sleep_on
id|EXPORT_SYMBOL
c_func
(paren
id|sleep_on
)paren
suffix:semicolon
DECL|variable|interruptible_sleep_on
id|EXPORT_SYMBOL
c_func
(paren
id|interruptible_sleep_on
)paren
suffix:semicolon
DECL|variable|schedule
id|EXPORT_SYMBOL
c_func
(paren
id|schedule
)paren
suffix:semicolon
DECL|variable|jiffies
id|EXPORT_SYMBOL
c_func
(paren
id|jiffies
)paren
suffix:semicolon
DECL|variable|xtime
id|EXPORT_SYMBOL
c_func
(paren
id|xtime
)paren
suffix:semicolon
DECL|variable|do_gettimeofday
id|EXPORT_SYMBOL
c_func
(paren
id|do_gettimeofday
)paren
suffix:semicolon
DECL|variable|loops_per_sec
id|EXPORT_SYMBOL
c_func
(paren
id|loops_per_sec
)paren
suffix:semicolon
DECL|variable|need_resched
id|EXPORT_SYMBOL
c_func
(paren
id|need_resched
)paren
suffix:semicolon
DECL|variable|kstat
id|EXPORT_SYMBOL
c_func
(paren
id|kstat
)paren
suffix:semicolon
DECL|variable|kill_proc
id|EXPORT_SYMBOL
c_func
(paren
id|kill_proc
)paren
suffix:semicolon
DECL|variable|kill_pg
id|EXPORT_SYMBOL
c_func
(paren
id|kill_pg
)paren
suffix:semicolon
DECL|variable|kill_sl
id|EXPORT_SYMBOL
c_func
(paren
id|kill_sl
)paren
suffix:semicolon
multiline_comment|/* misc */
DECL|variable|panic
id|EXPORT_SYMBOL
c_func
(paren
id|panic
)paren
suffix:semicolon
DECL|variable|printk
id|EXPORT_SYMBOL
c_func
(paren
id|printk
)paren
suffix:semicolon
DECL|variable|sprintf
id|EXPORT_SYMBOL
c_func
(paren
id|sprintf
)paren
suffix:semicolon
DECL|variable|vsprintf
id|EXPORT_SYMBOL
c_func
(paren
id|vsprintf
)paren
suffix:semicolon
DECL|variable|kdevname
id|EXPORT_SYMBOL
c_func
(paren
id|kdevname
)paren
suffix:semicolon
DECL|variable|simple_strtoul
id|EXPORT_SYMBOL
c_func
(paren
id|simple_strtoul
)paren
suffix:semicolon
DECL|variable|system_utsname
id|EXPORT_SYMBOL
c_func
(paren
id|system_utsname
)paren
suffix:semicolon
DECL|variable|sys_call_table
id|EXPORT_SYMBOL
c_func
(paren
id|sys_call_table
)paren
suffix:semicolon
DECL|variable|machine_restart
id|EXPORT_SYMBOL
c_func
(paren
id|machine_restart
)paren
suffix:semicolon
DECL|variable|machine_halt
id|EXPORT_SYMBOL
c_func
(paren
id|machine_halt
)paren
suffix:semicolon
DECL|variable|machine_power_off
id|EXPORT_SYMBOL
c_func
(paren
id|machine_power_off
)paren
suffix:semicolon
DECL|variable|register_reboot_notifier
id|EXPORT_SYMBOL
c_func
(paren
id|register_reboot_notifier
)paren
suffix:semicolon
DECL|variable|unregister_reboot_notifier
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_reboot_notifier
)paren
suffix:semicolon
DECL|variable|_ctype
id|EXPORT_SYMBOL
c_func
(paren
id|_ctype
)paren
suffix:semicolon
DECL|variable|secure_tcp_sequence_number
id|EXPORT_SYMBOL
c_func
(paren
id|secure_tcp_sequence_number
)paren
suffix:semicolon
DECL|variable|get_random_bytes
id|EXPORT_SYMBOL
c_func
(paren
id|get_random_bytes
)paren
suffix:semicolon
multiline_comment|/* Signal interfaces */
DECL|variable|send_sig
id|EXPORT_SYMBOL
c_func
(paren
id|send_sig
)paren
suffix:semicolon
multiline_comment|/* Program loader interfaces */
DECL|variable|setup_arg_pages
id|EXPORT_SYMBOL
c_func
(paren
id|setup_arg_pages
)paren
suffix:semicolon
DECL|variable|copy_strings
id|EXPORT_SYMBOL
c_func
(paren
id|copy_strings
)paren
suffix:semicolon
DECL|variable|do_execve
id|EXPORT_SYMBOL
c_func
(paren
id|do_execve
)paren
suffix:semicolon
DECL|variable|flush_old_exec
id|EXPORT_SYMBOL
c_func
(paren
id|flush_old_exec
)paren
suffix:semicolon
DECL|variable|open_dentry
id|EXPORT_SYMBOL
c_func
(paren
id|open_dentry
)paren
suffix:semicolon
DECL|variable|read_exec
id|EXPORT_SYMBOL
c_func
(paren
id|read_exec
)paren
suffix:semicolon
multiline_comment|/* Miscellaneous access points */
DECL|variable|si_meminfo
id|EXPORT_SYMBOL
c_func
(paren
id|si_meminfo
)paren
suffix:semicolon
multiline_comment|/* Added to make file system as module */
DECL|variable|set_writetime
id|EXPORT_SYMBOL
c_func
(paren
id|set_writetime
)paren
suffix:semicolon
DECL|variable|sys_tz
id|EXPORT_SYMBOL
c_func
(paren
id|sys_tz
)paren
suffix:semicolon
DECL|variable|__wait_on_super
id|EXPORT_SYMBOL
c_func
(paren
id|__wait_on_super
)paren
suffix:semicolon
DECL|variable|file_fsync
id|EXPORT_SYMBOL
c_func
(paren
id|file_fsync
)paren
suffix:semicolon
DECL|variable|clear_inode
id|EXPORT_SYMBOL
c_func
(paren
id|clear_inode
)paren
suffix:semicolon
DECL|variable|refile_buffer
id|EXPORT_SYMBOL
c_func
(paren
id|refile_buffer
)paren
suffix:semicolon
DECL|variable|nr_async_pages
id|EXPORT_SYMBOL
c_func
(paren
id|nr_async_pages
)paren
suffix:semicolon
DECL|variable|___strtok
id|EXPORT_SYMBOL
c_func
(paren
id|___strtok
)paren
suffix:semicolon
DECL|variable|init_fifo
id|EXPORT_SYMBOL
c_func
(paren
id|init_fifo
)paren
suffix:semicolon
DECL|variable|fifo_inode_operations
id|EXPORT_SYMBOL
c_func
(paren
id|fifo_inode_operations
)paren
suffix:semicolon
DECL|variable|chrdev_inode_operations
id|EXPORT_SYMBOL
c_func
(paren
id|chrdev_inode_operations
)paren
suffix:semicolon
DECL|variable|blkdev_inode_operations
id|EXPORT_SYMBOL
c_func
(paren
id|blkdev_inode_operations
)paren
suffix:semicolon
DECL|variable|read_ahead
id|EXPORT_SYMBOL
c_func
(paren
id|read_ahead
)paren
suffix:semicolon
DECL|variable|get_hash_table
id|EXPORT_SYMBOL
c_func
(paren
id|get_hash_table
)paren
suffix:semicolon
DECL|variable|get_empty_inode
id|EXPORT_SYMBOL
c_func
(paren
id|get_empty_inode
)paren
suffix:semicolon
DECL|variable|insert_inode_hash
id|EXPORT_SYMBOL
c_func
(paren
id|insert_inode_hash
)paren
suffix:semicolon
DECL|variable|make_bad_inode
id|EXPORT_SYMBOL
c_func
(paren
id|make_bad_inode
)paren
suffix:semicolon
DECL|variable|is_bad_inode
id|EXPORT_SYMBOL
c_func
(paren
id|is_bad_inode
)paren
suffix:semicolon
DECL|variable|event
id|EXPORT_SYMBOL
c_func
(paren
id|event
)paren
suffix:semicolon
DECL|variable|__down
id|EXPORT_SYMBOL
c_func
(paren
id|__down
)paren
suffix:semicolon
DECL|variable|__up
id|EXPORT_SYMBOL
c_func
(paren
id|__up
)paren
suffix:semicolon
DECL|variable|securelevel
id|EXPORT_SYMBOL
c_func
(paren
id|securelevel
)paren
suffix:semicolon
multiline_comment|/* all busmice */
DECL|variable|add_mouse_randomness
id|EXPORT_SYMBOL
c_func
(paren
id|add_mouse_randomness
)paren
suffix:semicolon
DECL|variable|fasync_helper
id|EXPORT_SYMBOL
c_func
(paren
id|fasync_helper
)paren
suffix:semicolon
multiline_comment|/* psaux mouse */
DECL|variable|aux_device_present
id|EXPORT_SYMBOL
c_func
(paren
id|aux_device_present
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_VT
DECL|variable|kbd_read_mask
id|EXPORT_SYMBOL
c_func
(paren
id|kbd_read_mask
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_MD
DECL|variable|disk_name
id|EXPORT_SYMBOL
c_func
(paren
id|disk_name
)paren
suffix:semicolon
multiline_comment|/* for md.c */
macro_line|#endif
multiline_comment|/* binfmt_aout */
DECL|variable|get_write_access
id|EXPORT_SYMBOL
c_func
(paren
id|get_write_access
)paren
suffix:semicolon
DECL|variable|put_write_access
id|EXPORT_SYMBOL
c_func
(paren
id|put_write_access
)paren
suffix:semicolon
eof
