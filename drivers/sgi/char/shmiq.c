multiline_comment|/* $Id: shmiq.c,v 1.19 2000/02/23 00:41:21 ralf Exp $&n; *&n; * shmiq.c: shared memory input queue driver&n; * written 1997 Miguel de Icaza (miguel@nuclecu.unam.mx)&n; *&n; * We implement /dev/shmiq, /dev/qcntlN here&n; * this is different from IRIX that has shmiq as a misc&n; * streams device and the and qcntl devices as a major device.&n; *&n; * minor number 0 implements /dev/shmiq,&n; * any other number implements /dev/qcntl${minor-1}&n; *&n; * /dev/shmiq is used by the X server for two things:&n; * &n; *    1. for I_LINK()ing trough ioctl the file handle of a&n; *       STREAMS device.&n; *&n; *    2. To send STREAMS-commands to the devices with the&n; *       QIO ioctl interface.&n; *&n; * I have not yet figured how to make multiple X servers share&n; * /dev/shmiq for having different servers running.  So, for now&n; * I keep a kernel-global array of inodes that are pushed into&n; * /dev/shmiq.&n; *&n; * /dev/qcntlN is used by the X server for two things:&n; *&n; *    1. Issuing the QIOCATTACH for mapping the shared input&n; *       queue into the address space of the X server (yeah, yeah,&n; *       I did not invent this interface).&n; *&n; *    2. used by select.  I bet it is used for checking for events on&n; *       the queue.&n; *&n; * Now the problem is that there does not seem anything that&n; * establishes a connection between /dev/shmiq and the qcntlN file.  I&n; * need an strace from an X server that runs on a machine with more&n; * than one keyboard.  And this is a problem since the file handles&n; * are pushed in /dev/shmiq, while the events should be dispatched to&n; * the /dev/qcntlN device. &n; *&n; * Until then, I just allow for 1 qcntl device.&n; *&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;asm/shmiq.h&gt;
macro_line|#include &lt;asm/gfx.h&gt;
macro_line|#include &lt;asm/mman.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/poll.h&gt;
macro_line|#include &quot;graphics.h&quot;
multiline_comment|/* we are not really getting any more than a few files in the shmiq */
DECL|macro|MAX_SHMIQ_DEVS
mdefine_line|#define MAX_SHMIQ_DEVS 10
multiline_comment|/*&n; * One per X server running, not going to get very big.&n; * Even if we have this we now assume just 1 /dev/qcntl can be&n; * active, I need to find how this works on multi-headed machines.&n; */
DECL|macro|MAX_SHMI_QUEUES
mdefine_line|#define MAX_SHMI_QUEUES 4
r_static
r_struct
(brace
DECL|member|used
r_int
id|used
suffix:semicolon
DECL|member|filp
r_struct
id|file
op_star
id|filp
suffix:semicolon
DECL|member|cpos
r_struct
id|shmiqsetcpos
id|cpos
suffix:semicolon
DECL|variable|shmiq_pushed_devices
)brace
id|shmiq_pushed_devices
(braket
id|MAX_SHMIQ_DEVS
)braket
suffix:semicolon
multiline_comment|/* /dev/qcntlN attached memory regions, location and size of the event queue */
r_static
r_struct
(brace
DECL|member|opened
r_int
id|opened
suffix:semicolon
multiline_comment|/* if this device has been opened */
DECL|member|shmiq_vaddr
r_void
op_star
id|shmiq_vaddr
suffix:semicolon
multiline_comment|/* mapping in kernel-land */
DECL|member|tail
r_int
id|tail
suffix:semicolon
multiline_comment|/* our copy of the shmiq-&gt;tail */
DECL|member|events
r_int
id|events
suffix:semicolon
DECL|member|mapped
r_int
id|mapped
suffix:semicolon
DECL|member|proc_list
id|wait_queue_head_t
id|proc_list
suffix:semicolon
DECL|member|fasync
r_struct
id|fasync_struct
op_star
id|fasync
suffix:semicolon
DECL|variable|shmiqs
)brace
id|shmiqs
(braket
id|MAX_SHMI_QUEUES
)braket
suffix:semicolon
r_void
DECL|function|shmiq_push_event
id|shmiq_push_event
(paren
r_struct
id|shmqevent
op_star
id|e
)paren
(brace
r_struct
id|sharedMemoryInputQueue
op_star
id|s
suffix:semicolon
r_int
id|device
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* FIXME: here is the assumption /dev/shmiq == /dev/qcntl0 */
r_int
id|tail_next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shmiqs
(braket
id|device
)braket
dot
id|mapped
)paren
r_return
suffix:semicolon
id|s
op_assign
id|shmiqs
(braket
id|device
)braket
dot
id|shmiq_vaddr
suffix:semicolon
id|s-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;tail
op_ne
id|shmiqs
(braket
id|device
)braket
dot
id|tail
)paren
(brace
id|s-&gt;flags
op_or_assign
id|SHMIQ_CORRUPTED
suffix:semicolon
r_return
suffix:semicolon
)brace
id|tail_next
op_assign
(paren
id|s-&gt;tail
op_plus
l_int|1
)paren
op_mod
(paren
id|shmiqs
(braket
id|device
)braket
dot
id|events
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tail_next
op_eq
id|s-&gt;head
)paren
(brace
id|s-&gt;flags
op_or_assign
id|SHMIQ_OVERFLOW
suffix:semicolon
r_return
suffix:semicolon
)brace
id|e-&gt;un.time
op_assign
id|jiffies
suffix:semicolon
id|s-&gt;events
(braket
id|s-&gt;tail
)braket
op_assign
op_star
id|e
suffix:semicolon
id|printk
(paren
l_string|&quot;KERNEL: dev=%d which=%d type=%d flags=%d&bslash;n&quot;
comma
id|e-&gt;data.device
comma
id|e-&gt;data.which
comma
id|e-&gt;data.type
comma
id|e-&gt;data.flags
)paren
suffix:semicolon
id|s-&gt;tail
op_assign
id|tail_next
suffix:semicolon
id|shmiqs
(braket
id|device
)braket
dot
id|tail
op_assign
id|tail_next
suffix:semicolon
id|kill_fasync
(paren
op_amp
id|shmiqs
(braket
id|device
)braket
dot
id|fasync
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
id|wake_up_interruptible
(paren
op_amp
id|shmiqs
(braket
id|device
)braket
dot
id|proc_list
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|shmiq_manage_file
id|shmiq_manage_file
(paren
r_struct
id|file
op_star
id|filp
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|filp-&gt;f_op
op_logical_or
op_logical_neg
id|filp-&gt;f_op-&gt;ioctl
)paren
r_return
op_minus
id|ENOSR
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
id|MAX_SHMIQ_DEVS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|shmiq_pushed_devices
(braket
id|i
)braket
dot
id|used
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|filp-&gt;f_op-&gt;ioctl
)paren
(paren
id|filp-&gt;f_dentry-&gt;d_inode
comma
id|filp
comma
id|SHMIQ_ON
comma
id|i
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|ENOSR
suffix:semicolon
id|shmiq_pushed_devices
(braket
id|i
)braket
dot
id|used
op_assign
l_int|1
suffix:semicolon
id|shmiq_pushed_devices
(braket
id|i
)braket
dot
id|filp
op_assign
id|filp
suffix:semicolon
id|shmiq_pushed_devices
(braket
id|i
)braket
dot
id|cpos.x
op_assign
l_int|0
suffix:semicolon
id|shmiq_pushed_devices
(braket
id|i
)braket
dot
id|cpos.y
op_assign
l_int|0
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
r_return
op_minus
id|ENOSR
suffix:semicolon
)brace
r_static
r_int
DECL|function|shmiq_forget_file
id|shmiq_forget_file
(paren
r_int
r_int
id|fdes
)paren
(brace
r_struct
id|file
op_star
id|filp
suffix:semicolon
r_if
c_cond
(paren
id|fdes
OG
id|MAX_SHMIQ_DEVS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shmiq_pushed_devices
(braket
id|fdes
)braket
dot
id|used
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|filp
op_assign
id|shmiq_pushed_devices
(braket
id|fdes
)braket
dot
id|filp
suffix:semicolon
r_if
c_cond
(paren
id|filp
)paren
(brace
(paren
op_star
id|filp-&gt;f_op-&gt;ioctl
)paren
(paren
id|filp-&gt;f_dentry-&gt;d_inode
comma
id|filp
comma
id|SHMIQ_OFF
comma
l_int|0
)paren
suffix:semicolon
id|shmiq_pushed_devices
(braket
id|fdes
)braket
dot
id|filp
op_assign
l_int|0
suffix:semicolon
id|fput
(paren
id|filp
)paren
suffix:semicolon
)brace
id|shmiq_pushed_devices
(braket
id|fdes
)braket
dot
id|used
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|shmiq_sioc
id|shmiq_sioc
(paren
r_int
id|device
comma
r_int
id|cmd
comma
r_struct
id|strioctl
op_star
id|s
)paren
(brace
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|QIOCGETINDX
suffix:colon
multiline_comment|/*&n;&t;&t; * Ok, we just return the index they are providing us&n;&t;&t; */
id|printk
(paren
l_string|&quot;QIOCGETINDX: returning %d&bslash;n&quot;
comma
op_star
(paren
r_int
op_star
)paren
id|s-&gt;ic_dp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|QIOCIISTR
suffix:colon
(brace
r_struct
id|muxioctl
op_star
id|mux
op_assign
(paren
r_struct
id|muxioctl
op_star
)paren
id|s-&gt;ic_dp
suffix:semicolon
id|printk
(paren
l_string|&quot;Double indirect ioctl: [%d, %x&bslash;n&quot;
comma
id|mux-&gt;index
comma
id|mux-&gt;realcmd
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_case
id|QIOCSETCPOS
suffix:colon
(brace
r_if
c_cond
(paren
id|copy_from_user
(paren
op_amp
id|shmiq_pushed_devices
(braket
id|device
)braket
dot
id|cpos
comma
id|s-&gt;ic_dp
comma
r_sizeof
(paren
r_struct
id|shmiqsetcpos
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|printk
(paren
l_string|&quot;Unknown I_STR request for shmiq device: 0x%x&bslash;n&quot;
comma
id|cmd
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_static
r_int
DECL|function|shmiq_ioctl
id|shmiq_ioctl
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|f
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|strioctl
id|sioc
suffix:semicolon
r_int
id|v
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
multiline_comment|/*&n;&t;&t; * They are giving us the file descriptor for one&n;&t;&t; * of their streams devices&n;&t;&t; */
r_case
id|I_LINK
suffix:colon
id|file
op_assign
id|fget
(paren
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
r_goto
id|bad_file
suffix:semicolon
id|v
op_assign
id|shmiq_manage_file
(paren
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|v
OL
l_int|0
)paren
id|fput
c_func
(paren
id|file
)paren
suffix:semicolon
r_return
id|v
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Remove a device from our list of managed&n;&t;&t; * stream devices&n;&t;&t; */
r_case
id|I_UNLINK
suffix:colon
id|v
op_assign
id|shmiq_forget_file
(paren
id|arg
)paren
suffix:semicolon
r_return
id|v
suffix:semicolon
r_case
id|I_STR
suffix:colon
id|v
op_assign
id|get_sioc
(paren
op_amp
id|sioc
comma
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|v
)paren
r_return
id|v
suffix:semicolon
multiline_comment|/* FIXME: This forces device = 0 */
r_return
id|shmiq_sioc
(paren
l_int|0
comma
id|sioc.ic_cmd
comma
op_amp
id|sioc
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
id|bad_file
suffix:colon
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
r_extern
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
suffix:semicolon
r_static
r_int
DECL|function|qcntl_ioctl
id|qcntl_ioctl
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
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
comma
r_int
id|minor
)paren
(brace
r_struct
id|shmiqreq
id|req
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
id|v
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
multiline_comment|/*&n;&t;&t; * The address space is already mapped as a /dev/zero&n;&t;&t; * mapping.  FIXME: check that /dev/zero is what the user&n;&t;&t; * had mapped before :-)&n;&t;&t; */
r_case
id|QIOCATTACH
suffix:colon
(brace
r_int
r_int
id|vaddr
suffix:semicolon
r_int
id|s
suffix:semicolon
id|v
op_assign
id|verify_area
(paren
id|VERIFY_READ
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|shmiqreq
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|v
)paren
r_return
id|v
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|req
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|req
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * Do not allow to attach to another region if it has&n;&t;&t;&t; * already been attached&n;&t;&t;&t; */
r_if
c_cond
(paren
id|shmiqs
(braket
id|minor
)braket
dot
id|mapped
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SHMIQ:The thingie is already mapped&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|vaddr
op_assign
(paren
r_int
r_int
)paren
id|req.user_vaddr
suffix:semicolon
id|vma
op_assign
id|find_vma
(paren
id|current-&gt;mm
comma
id|vaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
)paren
(brace
id|printk
(paren
l_string|&quot;SHMIQ: could not find %lx the vma&bslash;n&quot;
comma
id|vaddr
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|s
op_assign
id|req.arg
op_star
r_sizeof
(paren
r_struct
id|shmqevent
)paren
op_plus
r_sizeof
(paren
r_struct
id|sharedMemoryInputQueue
)paren
suffix:semicolon
id|v
op_assign
id|sys_munmap
(paren
id|vaddr
comma
id|s
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|do_munmap
c_func
(paren
id|current-&gt;mm
comma
id|vaddr
comma
id|s
)paren
suffix:semicolon
id|do_mmap
c_func
(paren
id|filp
comma
id|vaddr
comma
id|s
comma
id|PROT_READ
op_or
id|PROT_WRITE
comma
id|MAP_PRIVATE
op_or
id|MAP_FIXED
comma
l_int|0
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|shmiqs
(braket
id|minor
)braket
dot
id|events
op_assign
id|req.arg
suffix:semicolon
id|shmiqs
(braket
id|minor
)braket
dot
id|mapped
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_struct
id|page
op_star
DECL|function|shmiq_nopage
id|shmiq_nopage
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
r_int
id|write_access
)paren
(brace
multiline_comment|/* Do not allow for mremap to expand us */
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|variable|qcntl_mmap
r_static
r_struct
id|vm_operations_struct
id|qcntl_mmap
op_assign
(brace
id|nopage
suffix:colon
id|shmiq_nopage
comma
multiline_comment|/* our magic no-page fault handler */
)brace
suffix:semicolon
r_static
r_int
DECL|function|shmiq_qcntl_mmap
id|shmiq_qcntl_mmap
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
id|minor
op_assign
id|MINOR
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
comma
id|error
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_int
r_int
id|mem
comma
id|start
suffix:semicolon
multiline_comment|/* mmap is only supported on the qcntl devices */
r_if
c_cond
(paren
id|minor
op_decrement
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_pgoff
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|size
op_assign
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
suffix:semicolon
id|start
op_assign
id|vma-&gt;vm_start
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|mem
op_assign
(paren
r_int
r_int
)paren
id|shmiqs
(braket
id|minor
)braket
dot
id|shmiq_vaddr
op_assign
id|vmalloc_uncached
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mem
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Prevent the swapper from considering these pages for swap and touching them */
id|vma-&gt;vm_flags
op_or_assign
(paren
id|VM_SHM
op_or
id|VM_LOCKED
op_or
id|VM_IO
)paren
suffix:semicolon
id|vma-&gt;vm_ops
op_assign
op_amp
id|qcntl_mmap
suffix:semicolon
multiline_comment|/* Uncache the pages */
id|vma-&gt;vm_page_prot
op_assign
id|PAGE_USERIO
suffix:semicolon
id|error
op_assign
id|vmap_page_range
(paren
id|vma-&gt;vm_start
comma
id|size
comma
id|mem
)paren
suffix:semicolon
id|shmiqs
(braket
id|minor
)braket
dot
id|tail
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Init the shared memory input queue */
id|memset
(paren
id|shmiqs
(braket
id|minor
)braket
dot
id|shmiq_vaddr
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_static
r_int
DECL|function|shmiq_qcntl_ioctl
id|shmiq_qcntl_ioctl
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
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|minor
op_assign
id|MINOR
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_decrement
op_eq
l_int|0
)paren
r_return
id|shmiq_ioctl
(paren
id|inode
comma
id|filp
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_return
id|qcntl_ioctl
(paren
id|inode
comma
id|filp
comma
id|cmd
comma
id|arg
comma
id|minor
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|shmiq_qcntl_poll
id|shmiq_qcntl_poll
(paren
r_struct
id|file
op_star
id|filp
comma
id|poll_table
op_star
id|wait
)paren
(brace
r_struct
id|sharedMemoryInputQueue
op_star
id|s
suffix:semicolon
r_int
id|minor
op_assign
id|MINOR
(paren
id|filp-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_decrement
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shmiqs
(braket
id|minor
)braket
dot
id|mapped
)paren
r_return
l_int|0
suffix:semicolon
id|poll_wait
(paren
id|filp
comma
op_amp
id|shmiqs
(braket
id|minor
)braket
dot
id|proc_list
comma
id|wait
)paren
suffix:semicolon
id|s
op_assign
id|shmiqs
(braket
id|minor
)braket
dot
id|shmiq_vaddr
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;head
op_ne
id|s-&gt;tail
)paren
r_return
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|shmiq_qcntl_open
id|shmiq_qcntl_open
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
r_int
id|minor
op_assign
id|MINOR
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|minor
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|minor
OG
id|MAX_SHMI_QUEUES
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|shmiqs
(braket
id|minor
)braket
dot
id|opened
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|lock_kernel
(paren
)paren
suffix:semicolon
id|shmiqs
(braket
id|minor
)braket
dot
id|opened
op_assign
l_int|1
suffix:semicolon
id|shmiqs
(braket
id|minor
)braket
dot
id|shmiq_vaddr
op_assign
l_int|0
suffix:semicolon
id|unlock_kernel
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|shmiq_qcntl_fasync
id|shmiq_qcntl_fasync
(paren
r_int
id|fd
comma
r_struct
id|file
op_star
id|file
comma
r_int
id|on
)paren
(brace
r_int
id|retval
suffix:semicolon
r_int
id|minor
op_assign
id|MINOR
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
suffix:semicolon
id|retval
op_assign
id|fasync_helper
(paren
id|fd
comma
id|file
comma
id|on
comma
op_amp
id|shmiqs
(braket
id|minor
)braket
dot
id|fasync
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_return
id|retval
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|shmiq_qcntl_close
id|shmiq_qcntl_close
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
r_int
id|minor
op_assign
id|MINOR
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_int
id|j
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_decrement
op_eq
l_int|0
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|MAX_SHMIQ_DEVS
suffix:semicolon
id|j
op_increment
)paren
id|shmiq_forget_file
(paren
id|j
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|minor
OG
id|MAX_SHMI_QUEUES
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|shmiqs
(braket
id|minor
)braket
dot
id|opened
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|lock_kernel
(paren
)paren
suffix:semicolon
id|shmiq_qcntl_fasync
(paren
op_minus
l_int|1
comma
id|filp
comma
l_int|0
)paren
suffix:semicolon
id|shmiqs
(braket
id|minor
)braket
dot
id|opened
op_assign
l_int|0
suffix:semicolon
id|shmiqs
(braket
id|minor
)braket
dot
id|mapped
op_assign
l_int|0
suffix:semicolon
id|shmiqs
(braket
id|minor
)braket
dot
id|events
op_assign
l_int|0
suffix:semicolon
id|shmiqs
(braket
id|minor
)braket
dot
id|fasync
op_assign
l_int|0
suffix:semicolon
id|vfree
(paren
id|shmiqs
(braket
id|minor
)braket
dot
id|shmiq_vaddr
)paren
suffix:semicolon
id|shmiqs
(braket
id|minor
)braket
dot
id|shmiq_vaddr
op_assign
l_int|0
suffix:semicolon
id|unlock_kernel
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|shmiq_fops
r_static
r_struct
id|file_operations
id|shmiq_fops
op_assign
(brace
id|poll
suffix:colon
id|shmiq_qcntl_poll
comma
id|ioctl
suffix:colon
id|shmiq_qcntl_ioctl
comma
id|mmap
suffix:colon
id|shmiq_qcntl_mmap
comma
id|open
suffix:colon
id|shmiq_qcntl_open
comma
id|release
suffix:colon
id|shmiq_qcntl_close
comma
id|fasync
suffix:colon
id|shmiq_qcntl_fasync
comma
)brace
suffix:semicolon
r_void
DECL|function|shmiq_init
id|shmiq_init
(paren
r_void
)paren
(brace
id|printk
(paren
l_string|&quot;SHMIQ setup&bslash;n&quot;
)paren
suffix:semicolon
id|devfs_register_chrdev
c_func
(paren
id|SHMIQ_MAJOR
comma
l_string|&quot;shmiq&quot;
comma
op_amp
id|shmiq_fops
)paren
suffix:semicolon
id|devfs_register
(paren
l_int|NULL
comma
l_string|&quot;shmiq&quot;
comma
id|DEVFS_FL_DEFAULT
comma
id|SHMIQ_MAJOR
comma
l_int|0
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
op_amp
id|shmiq_fops
comma
l_int|NULL
)paren
suffix:semicolon
id|devfs_register_series
(paren
l_int|NULL
comma
l_string|&quot;qcntl%u&quot;
comma
l_int|2
comma
id|DEVFS_FL_DEFAULT
comma
id|SHMIQ_MAJOR
comma
l_int|1
comma
id|S_IFCHR
op_or
id|S_IRUSR
op_or
id|S_IWUSR
comma
op_amp
id|shmiq_fops
comma
l_int|NULL
)paren
suffix:semicolon
)brace
eof
