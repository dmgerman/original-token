multiline_comment|/*&n; * linux/kernel/chr_drv/sound/soundcard.c&n; *&n; * Soundcard driver for Linux&n; */
multiline_comment|/*&n; * Copyright by Hannu Savolainen 1993-1996&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions are&n; * met: 1. Redistributions of source code must retain the above copyright&n; * notice, this list of conditions and the following disclaimer. 2.&n; * Redistributions in binary form must reproduce the above copyright notice,&n; * this list of conditions and the following disclaimer in the documentation&n; * and/or other materials provided with the distribution.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND ANY&n; * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED&n; * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR&n; * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER&n; * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;sound_config.h&quot;
macro_line|#include &lt;linux/major.h&gt;
DECL|variable|chrdev_registered
r_static
r_int
id|chrdev_registered
op_assign
l_int|0
suffix:semicolon
DECL|variable|sound_major
r_static
r_int
id|sound_major
op_assign
id|SOUND_MAJOR
suffix:semicolon
DECL|variable|is_unloading
r_static
r_int
id|is_unloading
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Table for permanently allocated memory (used when unloading the module)&n; */
DECL|variable|sound_mem_blocks
id|caddr_t
id|sound_mem_blocks
(braket
l_int|1024
)braket
suffix:semicolon
DECL|variable|sound_num_blocks
r_int
id|sound_num_blocks
op_assign
l_int|0
suffix:semicolon
DECL|variable|soundcard_configured
r_static
r_int
id|soundcard_configured
op_assign
l_int|0
suffix:semicolon
DECL|variable|files
r_static
r_struct
id|fileinfo
id|files
(braket
id|SND_NDEVS
)braket
suffix:semicolon
DECL|variable|dma_alloc_map
r_static
r_char
id|dma_alloc_map
(braket
l_int|8
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
DECL|macro|DMA_MAP_UNAVAIL
mdefine_line|#define DMA_MAP_UNAVAIL&t;&t;0
DECL|macro|DMA_MAP_FREE
mdefine_line|#define DMA_MAP_FREE&t;&t;1
DECL|macro|DMA_MAP_BUSY
mdefine_line|#define DMA_MAP_BUSY&t;&t;2
r_int
DECL|function|snd_ioctl_return
id|snd_ioctl_return
(paren
r_int
op_star
id|addr
comma
r_int
id|value
)paren
(brace
r_if
c_cond
(paren
id|value
OL
l_int|0
)paren
r_return
id|value
suffix:semicolon
id|put_fs_long
(paren
id|value
comma
(paren
r_int
op_star
)paren
op_amp
(paren
(paren
id|addr
)paren
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|sound_read
id|sound_read
(paren
id|inode_handle
op_star
id|inode
comma
id|file_handle
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|dev
suffix:semicolon
id|dev
op_assign
id|MINOR
(paren
id|inode_get_rdev
(paren
id|inode
)paren
)paren
suffix:semicolon
id|files
(braket
id|dev
)braket
dot
id|flags
op_assign
id|file_get_flags
(paren
id|file
)paren
suffix:semicolon
r_return
id|sound_read_sw
(paren
id|dev
comma
op_amp
id|files
(braket
id|dev
)braket
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|sound_write
id|sound_write
(paren
id|inode_handle
op_star
id|inode
comma
id|file_handle
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
)paren
(brace
r_int
id|dev
suffix:semicolon
id|dev
op_assign
id|MINOR
(paren
id|inode_get_rdev
(paren
id|inode
)paren
)paren
suffix:semicolon
id|files
(braket
id|dev
)braket
dot
id|flags
op_assign
id|file_get_flags
(paren
id|file
)paren
suffix:semicolon
r_return
id|sound_write_sw
(paren
id|dev
comma
op_amp
id|files
(braket
id|dev
)braket
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|sound_lseek
id|sound_lseek
(paren
id|inode_handle
op_star
id|inode
comma
id|file_handle
op_star
id|file
comma
id|off_t
id|offset
comma
r_int
id|orig
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_static
r_int
DECL|function|sound_open
id|sound_open
(paren
id|inode_handle
op_star
id|inode
comma
id|file_handle
op_star
id|file
)paren
(brace
r_int
id|dev
comma
id|retval
suffix:semicolon
r_struct
id|fileinfo
id|tmp_file
suffix:semicolon
r_if
c_cond
(paren
id|is_unloading
)paren
(brace
id|printk
(paren
l_string|&quot;Sound: Driver partially removed. Can&squot;t open device&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|dev
op_assign
id|MINOR
(paren
id|inode_get_rdev
(paren
id|inode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|soundcard_configured
op_logical_and
id|dev
op_ne
id|SND_DEV_CTL
op_logical_and
id|dev
op_ne
id|SND_DEV_STATUS
)paren
(brace
id|printk
(paren
l_string|&quot;SoundCard Error: The soundcard system has not been configured&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|tmp_file.mode
op_assign
l_int|0
suffix:semicolon
id|tmp_file.flags
op_assign
id|file_get_flags
(paren
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tmp_file.flags
op_amp
id|O_ACCMODE
)paren
op_eq
id|O_RDWR
)paren
id|tmp_file.mode
op_assign
id|OPEN_READWRITE
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tmp_file.flags
op_amp
id|O_ACCMODE
)paren
op_eq
id|O_RDONLY
)paren
id|tmp_file.mode
op_assign
id|OPEN_READ
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tmp_file.flags
op_amp
id|O_ACCMODE
)paren
op_eq
id|O_WRONLY
)paren
id|tmp_file.mode
op_assign
id|OPEN_WRITE
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|sound_open_sw
(paren
id|dev
comma
op_amp
id|tmp_file
)paren
)paren
OL
l_int|0
)paren
r_return
id|retval
suffix:semicolon
macro_line|#ifdef MODULE
id|MOD_INC_USE_COUNT
suffix:semicolon
macro_line|#endif
id|memcpy
(paren
(paren
r_char
op_star
)paren
op_amp
id|files
(braket
id|dev
)braket
comma
(paren
r_char
op_star
)paren
op_amp
id|tmp_file
comma
r_sizeof
(paren
id|tmp_file
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_static
r_void
DECL|function|sound_release
id|sound_release
(paren
id|inode_handle
op_star
id|inode
comma
id|file_handle
op_star
id|file
)paren
(brace
r_int
id|dev
suffix:semicolon
id|dev
op_assign
id|MINOR
(paren
id|inode_get_rdev
(paren
id|inode
)paren
)paren
suffix:semicolon
id|files
(braket
id|dev
)braket
dot
id|flags
op_assign
id|file_get_flags
(paren
id|file
)paren
suffix:semicolon
id|sound_release_sw
(paren
id|dev
comma
op_amp
id|files
(braket
id|dev
)braket
)paren
suffix:semicolon
macro_line|#ifdef MODULE
id|MOD_DEC_USE_COUNT
suffix:semicolon
macro_line|#endif
)brace
r_static
r_int
DECL|function|sound_ioctl
id|sound_ioctl
(paren
id|inode_handle
op_star
id|inode
comma
id|file_handle
op_star
id|file
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
id|dev
comma
id|err
suffix:semicolon
id|dev
op_assign
id|MINOR
(paren
id|inode_get_rdev
(paren
id|inode
)paren
)paren
suffix:semicolon
id|files
(braket
id|dev
)braket
dot
id|flags
op_assign
id|file_get_flags
(paren
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_IOC_DIR
(paren
id|cmd
)paren
op_ne
id|_IOC_NONE
)paren
(brace
multiline_comment|/*&n;         * Have to validate the address given by the process.&n;       */
r_int
id|len
suffix:semicolon
id|len
op_assign
id|_IOC_SIZE
(paren
id|cmd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_IOC_DIR
(paren
id|cmd
)paren
op_amp
id|_IOC_WRITE
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
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
id|len
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|_IOC_DIR
(paren
id|cmd
)paren
op_amp
id|_IOC_READ
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|verify_area
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
id|len
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
)brace
)brace
id|err
op_assign
id|sound_ioctl_sw
(paren
id|dev
comma
op_amp
id|files
(braket
id|dev
)braket
comma
id|cmd
comma
(paren
id|caddr_t
)paren
id|arg
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_static
r_int
DECL|function|sound_select
id|sound_select
(paren
id|inode_handle
op_star
id|inode
comma
id|file_handle
op_star
id|file
comma
r_int
id|sel_type
comma
id|select_table_handle
op_star
id|wait
)paren
(brace
r_int
id|dev
suffix:semicolon
id|dev
op_assign
id|MINOR
(paren
id|inode_get_rdev
(paren
id|inode
)paren
)paren
suffix:semicolon
id|files
(braket
id|dev
)braket
dot
id|flags
op_assign
id|file_get_flags
(paren
id|file
)paren
suffix:semicolon
id|DEB
(paren
id|printk
(paren
l_string|&quot;sound_select(dev=%d, type=0x%x)&bslash;n&quot;
comma
id|dev
comma
id|sel_type
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|dev
op_amp
l_int|0x0f
)paren
(brace
macro_line|#ifdef CONFIG_SEQUENCER
r_case
id|SND_DEV_SEQ
suffix:colon
r_case
id|SND_DEV_SEQ2
suffix:colon
r_return
id|sequencer_select
(paren
id|dev
comma
op_amp
id|files
(braket
id|dev
)braket
comma
id|sel_type
comma
id|wait
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIDI
r_case
id|SND_DEV_MIDIN
suffix:colon
r_return
id|MIDIbuf_select
(paren
id|dev
comma
op_amp
id|files
(braket
id|dev
)braket
comma
id|sel_type
comma
id|wait
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_AUDIO
r_case
id|SND_DEV_DSP
suffix:colon
r_case
id|SND_DEV_DSP16
suffix:colon
r_case
id|SND_DEV_AUDIO
suffix:colon
r_return
id|audio_select
(paren
id|dev
comma
op_amp
id|files
(braket
id|dev
)braket
comma
id|sel_type
comma
id|wait
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|sound_mmap
id|sound_mmap
(paren
id|inode_handle
op_star
id|inode
comma
id|file_handle
op_star
id|file
comma
id|vm_area_handle
op_star
id|vma
)paren
(brace
r_int
id|dev
comma
id|dev_class
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
r_struct
id|dma_buffparms
op_star
id|dmap
op_assign
l_int|NULL
suffix:semicolon
id|dev
op_assign
id|MINOR
(paren
id|inode_get_rdev
(paren
id|inode
)paren
)paren
suffix:semicolon
id|files
(braket
id|dev
)braket
dot
id|flags
op_assign
id|file_get_flags
(paren
id|file
)paren
suffix:semicolon
id|dev_class
op_assign
id|dev
op_amp
l_int|0x0f
suffix:semicolon
id|dev
op_rshift_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|dev_class
op_ne
id|SND_DEV_DSP
op_logical_and
id|dev_class
op_ne
id|SND_DEV_DSP16
op_logical_and
id|dev_class
op_ne
id|SND_DEV_AUDIO
)paren
(brace
id|printk
(paren
l_string|&quot;Sound: mmap() not supported for other than audio devices&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|vma_get_flags
(paren
id|vma
)paren
op_amp
(paren
id|VM_READ
op_or
id|VM_WRITE
)paren
)paren
op_eq
(paren
id|VM_READ
op_or
id|VM_WRITE
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;Sound: Cannot do read/write mmap()&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vma_get_flags
(paren
id|vma
)paren
op_amp
id|VM_READ
)paren
(brace
id|dmap
op_assign
id|audio_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|dmap_in
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|vma_get_flags
(paren
id|vma
)paren
op_amp
id|VM_WRITE
)paren
(brace
id|dmap
op_assign
id|audio_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|dmap_out
suffix:semicolon
)brace
r_else
(brace
id|printk
(paren
l_string|&quot;Sound: Undefined mmap() access&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dmap
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
l_string|&quot;Sound: mmap() error. dmap == NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dmap-&gt;raw_buf
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
l_string|&quot;Sound: mmap() called when raw_buf == NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dmap-&gt;mapping_flags
)paren
(brace
id|printk
(paren
l_string|&quot;Sound: mmap() called twice for the same DMA buffer&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vma_get_offset
(paren
id|vma
)paren
op_ne
l_int|0
)paren
(brace
id|printk
(paren
l_string|&quot;Sound: mmap() offset must be 0.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|size
op_assign
id|vma_get_end
(paren
id|vma
)paren
op_minus
id|vma_get_start
(paren
id|vma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_ne
id|dmap-&gt;bytes_in_use
)paren
(brace
id|printk
(paren
l_string|&quot;Sound: mmap() size = %ld. Should be %d&bslash;n&quot;
comma
id|size
comma
id|dmap-&gt;bytes_in_use
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|remap_page_range
(paren
id|vma_get_start
(paren
id|vma
)paren
comma
id|dmap-&gt;raw_buf_phys
comma
id|vma_get_end
(paren
id|vma
)paren
op_minus
id|vma_get_start
(paren
id|vma
)paren
comma
id|vma_get_page_prot
(paren
id|vma
)paren
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|vma_set_inode
(paren
id|vma
comma
id|inode
)paren
suffix:semicolon
id|inode_inc_count
(paren
id|inode
)paren
suffix:semicolon
id|dmap-&gt;mapping_flags
op_or_assign
id|DMA_MAP_MAPPED
suffix:semicolon
id|memset
(paren
id|dmap-&gt;raw_buf
comma
id|dmap-&gt;neutral_byte
comma
id|dmap-&gt;bytes_in_use
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|sound_fops
r_static
r_struct
id|file_operation_handle
id|sound_fops
op_assign
(brace
id|sound_lseek
comma
id|sound_read
comma
id|sound_write
comma
l_int|NULL
comma
multiline_comment|/* sound_readdir */
id|sound_select
comma
id|sound_ioctl
comma
id|sound_mmap
comma
id|sound_open
comma
id|sound_release
)brace
suffix:semicolon
r_void
DECL|function|soundcard_init
id|soundcard_init
(paren
r_void
)paren
(brace
macro_line|#ifndef MODULE
id|module_register_chrdev
(paren
id|sound_major
comma
l_string|&quot;sound&quot;
comma
op_amp
id|sound_fops
)paren
suffix:semicolon
id|chrdev_registered
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
id|soundcard_configured
op_assign
l_int|1
suffix:semicolon
id|sndtable_init
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Initialize call tables and&n;&t;&t;&t;&t;   * detect cards */
r_if
c_cond
(paren
id|sndtable_get_cardcount
(paren
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
multiline_comment|/* No cards detected */
macro_line|#ifdef CONFIG_AUDIO
r_if
c_cond
(paren
id|num_audiodevs
)paren
multiline_comment|/* Audio devices present */
(brace
id|DMAbuf_init
(paren
l_int|0
)paren
suffix:semicolon
id|audio_init
(paren
l_int|0
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_MIDI
r_if
c_cond
(paren
id|num_midis
)paren
id|MIDIbuf_init
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SEQUENCER
r_if
c_cond
(paren
id|num_midis
op_plus
id|num_synths
)paren
id|sequencer_init
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|irqs
r_static
r_int
r_int
id|irqs
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef MODULE
r_static
r_void
DECL|function|free_all_irqs
id|free_all_irqs
(paren
r_void
)paren
(brace
r_int
id|i
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
l_int|31
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|irqs
op_amp
(paren
l_int|1ul
op_lshift
id|i
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;Sound warning: IRQ%d was left allocated - fixed.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|snd_release_irq
(paren
id|i
)paren
suffix:semicolon
)brace
id|irqs
op_assign
l_int|0
suffix:semicolon
)brace
DECL|variable|kernel_version
r_char
id|kernel_version
(braket
)braket
op_assign
id|UTS_RELEASE
suffix:semicolon
macro_line|#endif
DECL|variable|sound
r_static
r_int
id|sound
(braket
l_int|20
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
r_int
DECL|function|init_module
id|init_module
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
r_int
id|ints
(braket
l_int|21
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|connect_wrapper
(paren
id|WRAPPER_VERSION
)paren
OL
l_int|0
)paren
(brace
id|printk
(paren
l_string|&quot;Sound: Incompatible kernel (wrapper) version&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;     * &quot;sound=&quot; command line handling by Harald Milz.&n;   */
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
l_int|20
op_logical_and
id|sound
(braket
id|i
)braket
)paren
id|ints
(braket
id|i
op_plus
l_int|1
)braket
op_assign
id|sound
(braket
id|i
op_increment
)braket
suffix:semicolon
id|ints
(braket
l_int|0
)braket
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
id|sound_setup
(paren
l_string|&quot;sound=&quot;
comma
id|ints
)paren
suffix:semicolon
id|err
op_assign
id|module_register_chrdev
(paren
id|sound_major
comma
l_string|&quot;sound&quot;
comma
op_amp
id|sound_fops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
(paren
l_string|&quot;sound: driver already loaded/included in kernel&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
id|chrdev_registered
op_assign
l_int|1
suffix:semicolon
id|soundcard_init
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sound_num_blocks
op_ge
l_int|1024
)paren
id|printk
(paren
l_string|&quot;Sound warning: Deallocation table was too small.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
r_void
DECL|function|cleanup_module
id|cleanup_module
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|MOD_IN_USE
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chrdev_registered
)paren
id|module_unregister_chrdev
(paren
id|sound_major
comma
l_string|&quot;sound&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SEQUENCER
id|sound_stop_timer
(paren
)paren
suffix:semicolon
macro_line|#endif
id|sound_unload_drivers
(paren
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
id|sound_num_blocks
suffix:semicolon
id|i
op_increment
)paren
id|kfree
(paren
id|sound_mem_blocks
(braket
id|i
)braket
)paren
suffix:semicolon
id|free_all_irqs
(paren
)paren
suffix:semicolon
multiline_comment|/* If something was left allocated by accident */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|dma_alloc_map
(braket
id|i
)braket
op_ne
id|DMA_MAP_UNAVAIL
)paren
(brace
id|printk
(paren
l_string|&quot;Sound: Hmm, DMA%d was left allocated - fixed&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|sound_free_dma
(paren
id|i
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
r_void
DECL|function|tenmicrosec
id|tenmicrosec
(paren
r_int
op_star
id|osp
)paren
(brace
r_int
id|i
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|inb
(paren
l_int|0x80
)paren
suffix:semicolon
)brace
r_int
DECL|function|snd_set_irq_handler
id|snd_set_irq_handler
(paren
r_int
id|interrupt_level
comma
r_void
(paren
op_star
id|hndlr
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_char
op_star
id|name
comma
r_int
op_star
id|osp
)paren
(brace
r_int
id|retcode
suffix:semicolon
id|retcode
op_assign
id|request_irq
(paren
id|interrupt_level
comma
id|hndlr
comma
l_int|0
multiline_comment|/* SA_INTERRUPT */
comma
id|name
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retcode
OL
l_int|0
)paren
(brace
id|printk
(paren
l_string|&quot;Sound: IRQ%d already in use&bslash;n&quot;
comma
id|interrupt_level
)paren
suffix:semicolon
)brace
r_else
id|irqs
op_or_assign
(paren
l_int|1ul
op_lshift
id|interrupt_level
)paren
suffix:semicolon
r_return
id|retcode
suffix:semicolon
)brace
r_void
DECL|function|snd_release_irq
id|snd_release_irq
(paren
r_int
id|vect
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irqs
op_amp
(paren
l_int|1ul
op_lshift
id|vect
)paren
)paren
)paren
r_return
suffix:semicolon
id|irqs
op_and_assign
op_complement
(paren
l_int|1ul
op_lshift
id|vect
)paren
suffix:semicolon
id|free_irq
(paren
id|vect
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_int
DECL|function|sound_alloc_dma
id|sound_alloc_dma
(paren
r_int
id|chn
comma
r_char
op_star
id|deviceID
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|request_dma
(paren
id|chn
comma
id|deviceID
)paren
)paren
op_ne
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|dma_alloc_map
(braket
id|chn
)braket
op_assign
id|DMA_MAP_FREE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|sound_open_dma
id|sound_open_dma
(paren
r_int
id|chn
comma
r_char
op_star
id|deviceID
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
(paren
id|flags
)paren
suffix:semicolon
id|cli
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma_alloc_map
(braket
id|chn
)braket
op_ne
id|DMA_MAP_FREE
)paren
(brace
id|printk
(paren
l_string|&quot;sound_open_dma: DMA channel %d busy or not allocated&bslash;n&quot;
comma
id|chn
)paren
suffix:semicolon
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|dma_alloc_map
(braket
id|chn
)braket
op_assign
id|DMA_MAP_BUSY
suffix:semicolon
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|sound_free_dma
id|sound_free_dma
(paren
r_int
id|chn
)paren
(brace
r_if
c_cond
(paren
id|dma_alloc_map
(braket
id|chn
)braket
op_ne
id|DMA_MAP_FREE
)paren
(brace
multiline_comment|/* printk (&quot;sound_free_dma: Bad access to DMA channel %d&bslash;n&quot;, chn); */
r_return
suffix:semicolon
)brace
id|free_dma
(paren
id|chn
)paren
suffix:semicolon
id|dma_alloc_map
(braket
id|chn
)braket
op_assign
id|DMA_MAP_UNAVAIL
suffix:semicolon
)brace
r_void
DECL|function|sound_close_dma
id|sound_close_dma
(paren
r_int
id|chn
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
(paren
id|flags
)paren
suffix:semicolon
id|cli
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma_alloc_map
(braket
id|chn
)braket
op_ne
id|DMA_MAP_BUSY
)paren
(brace
id|printk
(paren
l_string|&quot;sound_close_dma: Bad access to DMA channel %d&bslash;n&quot;
comma
id|chn
)paren
suffix:semicolon
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|dma_alloc_map
(braket
id|chn
)braket
op_assign
id|DMA_MAP_FREE
suffix:semicolon
id|restore_flags
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SEQUENCER
DECL|variable|seq_timer
r_static
r_struct
id|timer_list
id|seq_timer
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
id|sequencer_timer
)brace
suffix:semicolon
r_void
DECL|function|request_sound_timer
id|request_sound_timer
(paren
r_int
id|count
)paren
(brace
r_extern
r_int
r_int
id|seq_time
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
id|count
op_assign
id|jiffies
op_plus
(paren
op_minus
id|count
)paren
suffix:semicolon
r_else
id|count
op_add_assign
id|seq_time
suffix:semicolon
suffix:semicolon
(brace
id|seq_timer.expires
op_assign
(paren
(paren
id|count
op_minus
id|jiffies
)paren
)paren
op_plus
id|jiffies
suffix:semicolon
id|add_timer
(paren
op_amp
id|seq_timer
)paren
suffix:semicolon
)brace
suffix:semicolon
)brace
r_void
DECL|function|sound_stop_timer
id|sound_stop_timer
(paren
r_void
)paren
(brace
id|del_timer
(paren
op_amp
id|seq_timer
)paren
suffix:semicolon
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_AUDIO
macro_line|#ifdef KMALLOC_DMA_BROKEN
id|fatal_error__This_version_is_not_compatible_with_this_kernel
suffix:semicolon
macro_line|#endif
DECL|variable|debugmem
r_static
r_int
id|debugmem
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* switched off by default */
DECL|variable|dma_buffsize
r_static
r_int
id|dma_buffsize
op_assign
id|DSP_BUFFSIZE
suffix:semicolon
r_int
DECL|function|sound_alloc_dmap
id|sound_alloc_dmap
(paren
r_int
id|dev
comma
r_struct
id|dma_buffparms
op_star
id|dmap
comma
r_int
id|chan
)paren
(brace
r_char
op_star
id|start_addr
comma
op_star
id|end_addr
suffix:semicolon
r_int
id|i
comma
id|dma_pagesize
suffix:semicolon
id|dmap-&gt;mapping_flags
op_and_assign
op_complement
id|DMA_MAP_MAPPED
suffix:semicolon
r_if
c_cond
(paren
id|dmap-&gt;raw_buf
op_ne
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Already done */
r_if
c_cond
(paren
id|dma_buffsize
OL
l_int|4096
)paren
id|dma_buffsize
op_assign
l_int|4096
suffix:semicolon
r_if
c_cond
(paren
id|chan
OL
l_int|4
)paren
id|dma_pagesize
op_assign
l_int|64
op_star
l_int|1024
suffix:semicolon
r_else
id|dma_pagesize
op_assign
l_int|128
op_star
l_int|1024
suffix:semicolon
id|dmap-&gt;raw_buf
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|debugmem
)paren
id|printk
(paren
l_string|&quot;sound: buffsize[%d] = %lu&bslash;n&quot;
comma
id|dev
comma
id|audio_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|buffsize
)paren
suffix:semicolon
id|audio_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|buffsize
op_assign
id|dma_buffsize
suffix:semicolon
r_if
c_cond
(paren
id|audio_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|buffsize
OG
id|dma_pagesize
)paren
id|audio_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|buffsize
op_assign
id|dma_pagesize
suffix:semicolon
id|start_addr
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * Now loop until we get a free buffer. Try to get smaller buffer if&n; * it fails.&n; */
r_while
c_loop
(paren
id|start_addr
op_eq
l_int|NULL
op_logical_and
id|audio_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|buffsize
OG
id|PAGE_SIZE
)paren
(brace
r_int
id|sz
comma
id|size
suffix:semicolon
r_for
c_loop
(paren
id|sz
op_assign
l_int|0
comma
id|size
op_assign
id|PAGE_SIZE
suffix:semicolon
id|size
OL
id|audio_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|buffsize
suffix:semicolon
id|sz
op_increment
comma
id|size
op_lshift_assign
l_int|1
)paren
suffix:semicolon
id|audio_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|buffsize
op_assign
id|PAGE_SIZE
op_star
(paren
l_int|1
op_lshift
id|sz
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|start_addr
op_assign
(paren
r_char
op_star
)paren
id|__get_free_pages
(paren
id|GFP_ATOMIC
comma
id|sz
comma
id|MAX_DMA_ADDRESS
)paren
)paren
op_eq
l_int|NULL
)paren
id|audio_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|buffsize
op_div_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|start_addr
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
l_string|&quot;Sound error: Couldn&squot;t allocate DMA buffer&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* make some checks */
id|end_addr
op_assign
id|start_addr
op_plus
id|audio_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|buffsize
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|debugmem
)paren
id|printk
(paren
l_string|&quot;sound: start 0x%lx, end 0x%lx&bslash;n&quot;
comma
(paren
r_int
)paren
id|start_addr
comma
(paren
r_int
)paren
id|end_addr
)paren
suffix:semicolon
multiline_comment|/* now check if it fits into the same dma-pagesize */
r_if
c_cond
(paren
(paren
(paren
r_int
)paren
id|start_addr
op_amp
op_complement
(paren
id|dma_pagesize
op_minus
l_int|1
)paren
)paren
op_ne
(paren
(paren
r_int
)paren
id|end_addr
op_amp
op_complement
(paren
id|dma_pagesize
op_minus
l_int|1
)paren
)paren
op_logical_or
id|end_addr
op_ge
(paren
r_char
op_star
)paren
(paren
id|MAX_DMA_ADDRESS
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;sound: kmalloc returned invalid address 0x%lx for %ld Bytes DMA-buffer&bslash;n&quot;
comma
(paren
r_int
)paren
id|start_addr
comma
id|audio_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|buffsize
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
)brace
id|dmap-&gt;raw_buf
op_assign
id|start_addr
suffix:semicolon
id|dmap-&gt;raw_buf_phys
op_assign
id|virt_to_bus
(paren
id|start_addr
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|MAP_NR
(paren
id|start_addr
)paren
suffix:semicolon
id|i
op_le
id|MAP_NR
(paren
id|end_addr
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mem_map_reserve
(paren
id|i
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|sound_free_dmap
id|sound_free_dmap
(paren
r_int
id|dev
comma
r_struct
id|dma_buffparms
op_star
id|dmap
)paren
(brace
r_if
c_cond
(paren
id|dmap-&gt;raw_buf
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|dmap-&gt;mapping_flags
op_amp
id|DMA_MAP_MAPPED
)paren
r_return
suffix:semicolon
multiline_comment|/* Don&squot;t free mmapped buffer. Will use it next time */
(brace
r_int
id|sz
comma
id|size
comma
id|i
suffix:semicolon
r_int
r_int
id|start_addr
comma
id|end_addr
suffix:semicolon
r_for
c_loop
(paren
id|sz
op_assign
l_int|0
comma
id|size
op_assign
id|PAGE_SIZE
suffix:semicolon
id|size
OL
id|audio_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|buffsize
suffix:semicolon
id|sz
op_increment
comma
id|size
op_lshift_assign
l_int|1
)paren
suffix:semicolon
id|start_addr
op_assign
(paren
r_int
r_int
)paren
id|dmap-&gt;raw_buf
suffix:semicolon
id|end_addr
op_assign
id|start_addr
op_plus
id|audio_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|buffsize
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|MAP_NR
(paren
id|start_addr
)paren
suffix:semicolon
id|i
op_le
id|MAP_NR
(paren
id|end_addr
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|mem_map_unreserve
(paren
id|i
)paren
suffix:semicolon
)brace
id|free_pages
(paren
(paren
r_int
r_int
)paren
id|dmap-&gt;raw_buf
comma
id|sz
)paren
suffix:semicolon
)brace
id|dmap-&gt;raw_buf
op_assign
l_int|NULL
suffix:semicolon
)brace
r_int
DECL|function|sound_map_buffer
id|sound_map_buffer
(paren
r_int
id|dev
comma
r_struct
id|dma_buffparms
op_star
id|dmap
comma
id|buffmem_desc
op_star
id|info
)paren
(brace
id|printk
(paren
l_string|&quot;Entered sound_map_buffer()&bslash;n&quot;
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;Exited sound_map_buffer()&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#endif
r_void
DECL|function|conf_printf
id|conf_printf
(paren
r_char
op_star
id|name
comma
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|trace_init
)paren
r_return
suffix:semicolon
id|printk
(paren
l_string|&quot;&lt;%s&gt; at 0x%03x&quot;
comma
id|name
comma
id|hw_config-&gt;io_base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hw_config-&gt;irq
)paren
id|printk
(paren
l_string|&quot; irq %d&quot;
comma
(paren
id|hw_config-&gt;irq
OG
l_int|0
)paren
ques
c_cond
id|hw_config-&gt;irq
suffix:colon
op_minus
id|hw_config-&gt;irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hw_config-&gt;dma
op_ne
op_minus
l_int|1
op_logical_or
id|hw_config-&gt;dma2
op_ne
op_minus
l_int|1
)paren
(brace
id|printk
(paren
l_string|&quot; dma %d&quot;
comma
id|hw_config-&gt;dma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hw_config-&gt;dma2
op_ne
op_minus
l_int|1
)paren
id|printk
(paren
l_string|&quot;,%d&quot;
comma
id|hw_config-&gt;dma2
)paren
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_void
DECL|function|conf_printf2
id|conf_printf2
(paren
r_char
op_star
id|name
comma
r_int
id|base
comma
r_int
id|irq
comma
r_int
id|dma
comma
r_int
id|dma2
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|trace_init
)paren
r_return
suffix:semicolon
id|printk
(paren
l_string|&quot;&lt;%s&gt; at 0x%03x&quot;
comma
id|name
comma
id|base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
)paren
id|printk
(paren
l_string|&quot; irq %d&quot;
comma
(paren
id|irq
OG
l_int|0
)paren
ques
c_cond
id|irq
suffix:colon
op_minus
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma
op_ne
op_minus
l_int|1
op_logical_or
id|dma2
op_ne
op_minus
l_int|1
)paren
(brace
id|printk
(paren
l_string|&quot; dma %d&quot;
comma
id|dma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma2
op_ne
op_minus
l_int|1
)paren
id|printk
(paren
l_string|&quot;,%d&quot;
comma
id|dma2
)paren
suffix:semicolon
)brace
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
