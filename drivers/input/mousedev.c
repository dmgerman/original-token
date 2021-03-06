multiline_comment|/*&n; * $Id: mousedev.c,v 1.15 2000/08/14 21:05:26 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2000 Vojtech Pavlik&n; *&n; *  Input driver to PS/2 or ImPS/2 device driver module.&n; *&n; *  Sponsored by SuSE&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@suse.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
DECL|macro|MOUSEDEV_MINOR_BASE
mdefine_line|#define MOUSEDEV_MINOR_BASE &t;32
DECL|macro|MOUSEDEV_MINORS
mdefine_line|#define MOUSEDEV_MINORS&t;&t;32
DECL|macro|MOUSEDEV_MIX
mdefine_line|#define MOUSEDEV_MIX&t;&t;31
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#ifndef CONFIG_INPUT_MOUSEDEV_SCREEN_X
DECL|macro|CONFIG_INPUT_MOUSEDEV_SCREEN_X
mdefine_line|#define CONFIG_INPUT_MOUSEDEV_SCREEN_X&t;1024
macro_line|#endif
macro_line|#ifndef CONFIG_INPUT_MOUSEDEV_SCREEN_Y
DECL|macro|CONFIG_INPUT_MOUSEDEV_SCREEN_Y
mdefine_line|#define CONFIG_INPUT_MOUSEDEV_SCREEN_Y&t;768
macro_line|#endif
DECL|struct|mousedev
r_struct
id|mousedev
(brace
DECL|member|exist
r_int
id|exist
suffix:semicolon
DECL|member|open
r_int
id|open
suffix:semicolon
DECL|member|minor
r_int
id|minor
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|list
r_struct
id|mousedev_list
op_star
id|list
suffix:semicolon
DECL|member|handle
r_struct
id|input_handle
id|handle
suffix:semicolon
DECL|member|devfs
id|devfs_handle_t
id|devfs
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mousedev_list
r_struct
id|mousedev_list
(brace
DECL|member|fasync
r_struct
id|fasync_struct
op_star
id|fasync
suffix:semicolon
DECL|member|mousedev
r_struct
id|mousedev
op_star
id|mousedev
suffix:semicolon
DECL|member|next
r_struct
id|mousedev_list
op_star
id|next
suffix:semicolon
DECL|member|dx
DECL|member|dy
DECL|member|dz
DECL|member|oldx
DECL|member|oldy
r_int
id|dx
comma
id|dy
comma
id|dz
comma
id|oldx
comma
id|oldy
suffix:semicolon
DECL|member|ps2
r_int
r_char
id|ps2
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|buttons
r_int
r_int
id|buttons
suffix:semicolon
DECL|member|ready
DECL|member|buffer
DECL|member|bufsiz
r_int
r_char
id|ready
comma
id|buffer
comma
id|bufsiz
suffix:semicolon
DECL|member|mode
DECL|member|genseq
DECL|member|impseq
r_int
r_char
id|mode
comma
id|genseq
comma
id|impseq
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MOUSEDEV_GENIUS_LEN
mdefine_line|#define MOUSEDEV_GENIUS_LEN&t;5
DECL|macro|MOUSEDEV_IMPS_LEN
mdefine_line|#define MOUSEDEV_IMPS_LEN&t;6
DECL|variable|mousedev_genius_seq
r_static
r_int
r_char
id|mousedev_genius_seq
(braket
)braket
op_assign
(brace
l_int|0xe8
comma
l_int|3
comma
l_int|0xe6
comma
l_int|0xe6
comma
l_int|0xe6
)brace
suffix:semicolon
DECL|variable|mousedev_imps_seq
r_static
r_int
r_char
id|mousedev_imps_seq
(braket
)braket
op_assign
(brace
l_int|0xf3
comma
l_int|200
comma
l_int|0xf3
comma
l_int|100
comma
l_int|0xf3
comma
l_int|80
)brace
suffix:semicolon
DECL|variable|mousedev_handler
r_static
r_struct
id|input_handler
id|mousedev_handler
suffix:semicolon
DECL|variable|mousedev_table
r_static
r_struct
id|mousedev
op_star
id|mousedev_table
(braket
id|MOUSEDEV_MINORS
)braket
suffix:semicolon
DECL|variable|mousedev_mix
r_static
r_struct
id|mousedev
id|mousedev_mix
suffix:semicolon
DECL|function|mousedev_event
r_static
r_void
id|mousedev_event
c_func
(paren
r_struct
id|input_handle
op_star
id|handle
comma
r_int
r_int
id|type
comma
r_int
r_int
id|code
comma
r_int
id|value
)paren
(brace
r_struct
id|mousedev
op_star
id|mousedevs
(braket
l_int|3
)braket
op_assign
(brace
id|handle
op_member_access_from_pointer
r_private
comma
op_amp
id|mousedev_mix
comma
l_int|NULL
)brace
suffix:semicolon
r_struct
id|mousedev
op_star
op_star
id|mousedev
op_assign
id|mousedevs
suffix:semicolon
r_struct
id|mousedev_list
op_star
id|list
suffix:semicolon
r_int
id|index
comma
id|size
suffix:semicolon
id|add_mouse_randomness
c_func
(paren
(paren
id|type
op_lshift
l_int|4
)paren
op_xor
id|code
op_xor
(paren
id|code
op_rshift
l_int|4
)paren
op_xor
id|value
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|mousedev
)paren
(brace
id|list
op_assign
(paren
op_star
id|mousedev
)paren
op_member_access_from_pointer
id|list
suffix:semicolon
r_while
c_loop
(paren
id|list
)paren
(brace
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|EV_ABS
suffix:colon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|BTN_TRIGGER
comma
id|handle-&gt;dev-&gt;keybit
)paren
)paren
r_break
suffix:semicolon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|ABS_X
suffix:colon
id|size
op_assign
id|handle-&gt;dev-&gt;absmax
(braket
id|ABS_X
)braket
op_minus
id|handle-&gt;dev-&gt;absmin
(braket
id|ABS_X
)braket
suffix:semicolon
id|list-&gt;dx
op_add_assign
(paren
id|value
op_star
id|CONFIG_INPUT_MOUSEDEV_SCREEN_X
op_minus
id|list-&gt;oldx
)paren
op_div
id|size
suffix:semicolon
id|list-&gt;oldx
op_add_assign
id|list-&gt;dx
op_star
id|size
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ABS_Y
suffix:colon
id|size
op_assign
id|handle-&gt;dev-&gt;absmax
(braket
id|ABS_Y
)braket
op_minus
id|handle-&gt;dev-&gt;absmin
(braket
id|ABS_Y
)braket
suffix:semicolon
id|list-&gt;dy
op_sub_assign
(paren
id|value
op_star
id|CONFIG_INPUT_MOUSEDEV_SCREEN_Y
op_minus
id|list-&gt;oldy
)paren
op_div
id|size
suffix:semicolon
id|list-&gt;oldy
op_sub_assign
id|list-&gt;dy
op_star
id|size
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|EV_REL
suffix:colon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|REL_X
suffix:colon
id|list-&gt;dx
op_add_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REL_Y
suffix:colon
id|list-&gt;dy
op_sub_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REL_WHEEL
suffix:colon
r_if
c_cond
(paren
id|list-&gt;mode
)paren
id|list-&gt;dz
op_sub_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|EV_KEY
suffix:colon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|BTN_0
suffix:colon
r_case
id|BTN_TOUCH
suffix:colon
r_case
id|BTN_LEFT
suffix:colon
id|index
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BTN_4
suffix:colon
r_case
id|BTN_EXTRA
suffix:colon
r_if
c_cond
(paren
id|list-&gt;mode
OG
l_int|1
)paren
(brace
id|index
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|BTN_STYLUS
suffix:colon
r_case
id|BTN_1
suffix:colon
r_case
id|BTN_RIGHT
suffix:colon
id|index
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BTN_3
suffix:colon
r_case
id|BTN_SIDE
suffix:colon
r_if
c_cond
(paren
id|list-&gt;mode
OG
l_int|1
)paren
(brace
id|index
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|BTN_2
suffix:colon
r_case
id|BTN_STYLUS2
suffix:colon
r_case
id|BTN_MIDDLE
suffix:colon
id|index
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|value
)paren
(brace
r_case
l_int|0
suffix:colon
id|clear_bit
c_func
(paren
id|index
comma
op_amp
id|list-&gt;buttons
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|set_bit
c_func
(paren
id|index
comma
op_amp
id|list-&gt;buttons
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_return
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|list-&gt;ready
op_assign
l_int|1
suffix:semicolon
id|kill_fasync
c_func
(paren
op_amp
id|list-&gt;fasync
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
id|list
op_assign
id|list-&gt;next
suffix:semicolon
)brace
id|wake_up_interruptible
c_func
(paren
op_amp
(paren
(paren
op_star
id|mousedev
)paren
op_member_access_from_pointer
id|wait
)paren
)paren
suffix:semicolon
id|mousedev
op_increment
suffix:semicolon
)brace
)brace
DECL|function|mousedev_fasync
r_static
r_int
id|mousedev_fasync
c_func
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
r_struct
id|mousedev_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
id|retval
op_assign
id|fasync_helper
c_func
(paren
id|fd
comma
id|file
comma
id|on
comma
op_amp
id|list-&gt;fasync
)paren
suffix:semicolon
r_return
id|retval
OL
l_int|0
ques
c_cond
id|retval
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|mousedev_release
r_static
r_int
id|mousedev_release
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
id|file
)paren
(brace
r_struct
id|mousedev_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
r_struct
id|mousedev_list
op_star
op_star
id|listptr
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|listptr
op_assign
op_amp
id|list-&gt;mousedev-&gt;list
suffix:semicolon
id|mousedev_fasync
c_func
(paren
op_minus
l_int|1
comma
id|file
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
op_star
id|listptr
op_logical_and
(paren
op_star
id|listptr
op_ne
id|list
)paren
)paren
id|listptr
op_assign
op_amp
(paren
(paren
op_star
id|listptr
)paren
op_member_access_from_pointer
id|next
)paren
suffix:semicolon
op_star
id|listptr
op_assign
(paren
op_star
id|listptr
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|list-&gt;mousedev-&gt;open
)paren
(brace
r_if
c_cond
(paren
id|list-&gt;mousedev-&gt;minor
op_eq
id|MOUSEDEV_MIX
)paren
(brace
r_struct
id|input_handle
op_star
id|handle
op_assign
id|mousedev_handler.handle
suffix:semicolon
r_while
c_loop
(paren
id|handle
)paren
(brace
r_struct
id|mousedev
op_star
id|mousedev
op_assign
id|handle
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mousedev-&gt;open
)paren
(brace
r_if
c_cond
(paren
id|mousedev-&gt;exist
)paren
(brace
id|input_close_device
c_func
(paren
op_amp
id|mousedev-&gt;handle
)paren
suffix:semicolon
)brace
r_else
(brace
id|input_unregister_minor
c_func
(paren
id|mousedev-&gt;devfs
)paren
suffix:semicolon
id|mousedev_table
(braket
id|mousedev-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|mousedev
)paren
suffix:semicolon
)brace
)brace
id|handle
op_assign
id|handle-&gt;hnext
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|mousedev_mix.open
)paren
(brace
r_if
c_cond
(paren
id|list-&gt;mousedev-&gt;exist
)paren
(brace
id|input_close_device
c_func
(paren
op_amp
id|list-&gt;mousedev-&gt;handle
)paren
suffix:semicolon
)brace
r_else
(brace
id|input_unregister_minor
c_func
(paren
id|list-&gt;mousedev-&gt;devfs
)paren
suffix:semicolon
id|mousedev_table
(braket
id|list-&gt;mousedev-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|list-&gt;mousedev
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
id|kfree
c_func
(paren
id|list
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mousedev_open
r_static
r_int
id|mousedev_open
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
id|file
)paren
(brace
r_struct
id|mousedev_list
op_star
id|list
suffix:semicolon
r_int
id|i
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_minus
id|MOUSEDEV_MINOR_BASE
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|MOUSEDEV_MINORS
op_logical_or
op_logical_neg
id|mousedev_table
(braket
id|i
)braket
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|list
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|mousedev_list
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|list
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mousedev_list
)paren
)paren
suffix:semicolon
id|list-&gt;mousedev
op_assign
id|mousedev_table
(braket
id|i
)braket
suffix:semicolon
id|list-&gt;next
op_assign
id|mousedev_table
(braket
id|i
)braket
op_member_access_from_pointer
id|list
suffix:semicolon
id|mousedev_table
(braket
id|i
)braket
op_member_access_from_pointer
id|list
op_assign
id|list
suffix:semicolon
id|file-&gt;private_data
op_assign
id|list
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list-&gt;mousedev-&gt;open
op_increment
)paren
(brace
r_if
c_cond
(paren
id|list-&gt;mousedev-&gt;minor
op_eq
id|MOUSEDEV_MIX
)paren
(brace
r_struct
id|input_handle
op_star
id|handle
op_assign
id|mousedev_handler.handle
suffix:semicolon
r_while
c_loop
(paren
id|handle
)paren
(brace
r_struct
id|mousedev
op_star
id|mousedev
op_assign
id|handle
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mousedev-&gt;open
)paren
r_if
c_cond
(paren
id|mousedev-&gt;exist
)paren
id|input_open_device
c_func
(paren
id|handle
)paren
suffix:semicolon
id|handle
op_assign
id|handle-&gt;hnext
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|mousedev_mix.open
)paren
r_if
c_cond
(paren
id|list-&gt;mousedev-&gt;exist
)paren
id|input_open_device
c_func
(paren
op_amp
id|list-&gt;mousedev-&gt;handle
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mousedev_packet
r_static
r_void
id|mousedev_packet
c_func
(paren
r_struct
id|mousedev_list
op_star
id|list
comma
r_int
r_char
id|off
)paren
(brace
id|list-&gt;ps2
(braket
id|off
)braket
op_assign
l_int|0x08
op_or
(paren
(paren
id|list-&gt;dx
OL
l_int|0
)paren
op_lshift
l_int|4
)paren
op_or
(paren
(paren
id|list-&gt;dy
OL
l_int|0
)paren
op_lshift
l_int|5
)paren
op_or
(paren
id|list-&gt;buttons
op_amp
l_int|0x07
)paren
suffix:semicolon
id|list-&gt;ps2
(braket
id|off
op_plus
l_int|1
)braket
op_assign
(paren
id|list-&gt;dx
OG
l_int|127
ques
c_cond
l_int|127
suffix:colon
(paren
id|list-&gt;dx
OL
op_minus
l_int|127
ques
c_cond
op_minus
l_int|127
suffix:colon
id|list-&gt;dx
)paren
)paren
suffix:semicolon
id|list-&gt;ps2
(braket
id|off
op_plus
l_int|2
)braket
op_assign
(paren
id|list-&gt;dy
OG
l_int|127
ques
c_cond
l_int|127
suffix:colon
(paren
id|list-&gt;dy
OL
op_minus
l_int|127
ques
c_cond
op_minus
l_int|127
suffix:colon
id|list-&gt;dy
)paren
)paren
suffix:semicolon
id|list-&gt;dx
op_sub_assign
id|list-&gt;ps2
(braket
id|off
op_plus
l_int|1
)braket
suffix:semicolon
id|list-&gt;dy
op_sub_assign
id|list-&gt;ps2
(braket
id|off
op_plus
l_int|2
)braket
suffix:semicolon
id|list-&gt;bufsiz
op_assign
id|off
op_plus
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;mode
OG
l_int|1
)paren
id|list-&gt;ps2
(braket
id|off
)braket
op_or_assign
(paren
(paren
id|list-&gt;buttons
op_amp
l_int|0x18
)paren
op_lshift
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;mode
)paren
(brace
id|list-&gt;ps2
(braket
id|off
op_plus
l_int|3
)braket
op_assign
(paren
id|list-&gt;dz
OG
l_int|127
ques
c_cond
l_int|127
suffix:colon
(paren
id|list-&gt;dz
OL
op_minus
l_int|127
ques
c_cond
op_minus
l_int|127
suffix:colon
id|list-&gt;dz
)paren
)paren
suffix:semicolon
id|list-&gt;bufsiz
op_increment
suffix:semicolon
id|list-&gt;dz
op_sub_assign
id|list-&gt;ps2
(braket
id|off
op_plus
l_int|3
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|list-&gt;dx
op_logical_and
op_logical_neg
id|list-&gt;dy
op_logical_and
(paren
op_logical_neg
id|list-&gt;mode
op_logical_or
op_logical_neg
id|list-&gt;dz
)paren
)paren
id|list-&gt;ready
op_assign
l_int|0
suffix:semicolon
id|list-&gt;buffer
op_assign
id|list-&gt;bufsiz
suffix:semicolon
)brace
DECL|function|mousedev_write
r_static
id|ssize_t
id|mousedev_write
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
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|mousedev_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
r_int
r_char
id|c
suffix:semicolon
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|c
op_assign
id|buffer
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
id|mousedev_genius_seq
(braket
id|list-&gt;genseq
)braket
)paren
(brace
r_if
c_cond
(paren
op_increment
id|list-&gt;genseq
op_eq
id|MOUSEDEV_GENIUS_LEN
)paren
(brace
id|list-&gt;genseq
op_assign
l_int|0
suffix:semicolon
id|list-&gt;ready
op_assign
l_int|1
suffix:semicolon
id|list-&gt;mode
op_assign
l_int|2
suffix:semicolon
)brace
)brace
r_else
id|list-&gt;genseq
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
id|mousedev_imps_seq
(braket
id|list-&gt;impseq
)braket
)paren
(brace
r_if
c_cond
(paren
op_increment
id|list-&gt;impseq
op_eq
id|MOUSEDEV_IMPS_LEN
)paren
(brace
id|list-&gt;impseq
op_assign
l_int|0
suffix:semicolon
id|list-&gt;ready
op_assign
l_int|1
suffix:semicolon
id|list-&gt;mode
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
id|list-&gt;impseq
op_assign
l_int|0
suffix:semicolon
id|list-&gt;ps2
(braket
l_int|0
)braket
op_assign
l_int|0xfa
suffix:semicolon
id|list-&gt;bufsiz
op_assign
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_int|0xeb
suffix:colon
multiline_comment|/* Poll */
id|mousedev_packet
c_func
(paren
id|list
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xf2
suffix:colon
multiline_comment|/* Get ID */
id|list-&gt;ps2
(braket
l_int|1
)braket
op_assign
(paren
id|list-&gt;mode
op_eq
l_int|1
)paren
ques
c_cond
l_int|3
suffix:colon
l_int|0
suffix:semicolon
id|list-&gt;bufsiz
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xe9
suffix:colon
multiline_comment|/* Get info */
r_if
c_cond
(paren
id|list-&gt;mode
op_eq
l_int|2
)paren
(brace
id|list-&gt;ps2
(braket
l_int|1
)braket
op_assign
l_int|0x00
suffix:semicolon
id|list-&gt;ps2
(braket
l_int|2
)braket
op_assign
l_int|0x33
suffix:semicolon
id|list-&gt;ps2
(braket
l_int|3
)braket
op_assign
l_int|0x55
suffix:semicolon
)brace
r_else
(brace
id|list-&gt;ps2
(braket
l_int|1
)braket
op_assign
l_int|0x60
suffix:semicolon
id|list-&gt;ps2
(braket
l_int|2
)braket
op_assign
l_int|3
suffix:semicolon
id|list-&gt;ps2
(braket
l_int|3
)braket
op_assign
l_int|200
suffix:semicolon
)brace
id|list-&gt;bufsiz
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
)brace
id|list-&gt;buffer
op_assign
id|list-&gt;bufsiz
suffix:semicolon
)brace
id|kill_fasync
c_func
(paren
op_amp
id|list-&gt;fasync
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|list-&gt;mousedev-&gt;wait
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|mousedev_read
r_static
id|ssize_t
id|mousedev_read
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
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
id|DECLARE_WAITQUEUE
c_func
(paren
id|wait
comma
id|current
)paren
suffix:semicolon
r_struct
id|mousedev_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list-&gt;ready
op_logical_and
op_logical_neg
id|list-&gt;buffer
)paren
(brace
id|add_wait_queue
c_func
(paren
op_amp
id|list-&gt;mousedev-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list-&gt;ready
)paren
(brace
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
(brace
id|retval
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
(brace
id|retval
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|list-&gt;mousedev-&gt;wait
comma
op_amp
id|wait
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retval
)paren
r_return
id|retval
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list-&gt;buffer
)paren
id|mousedev_packet
c_func
(paren
id|list
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|list-&gt;buffer
)paren
id|count
op_assign
id|list-&gt;buffer
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buffer
comma
id|list-&gt;ps2
op_plus
id|list-&gt;bufsiz
op_minus
id|list-&gt;buffer
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|list-&gt;buffer
op_sub_assign
id|count
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/* No kernel lock - fine */
DECL|function|mousedev_poll
r_static
r_int
r_int
id|mousedev_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
(brace
r_struct
id|mousedev_list
op_star
id|list
op_assign
id|file-&gt;private_data
suffix:semicolon
id|poll_wait
c_func
(paren
id|file
comma
op_amp
id|list-&gt;mousedev-&gt;wait
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;ready
op_logical_or
id|list-&gt;buffer
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
DECL|variable|mousedev_fops
r_struct
id|file_operations
id|mousedev_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|read
suffix:colon
id|mousedev_read
comma
id|write
suffix:colon
id|mousedev_write
comma
id|poll
suffix:colon
id|mousedev_poll
comma
id|open
suffix:colon
id|mousedev_open
comma
id|release
suffix:colon
id|mousedev_release
comma
id|fasync
suffix:colon
id|mousedev_fasync
comma
)brace
suffix:semicolon
DECL|function|mousedev_connect
r_static
r_struct
id|input_handle
op_star
id|mousedev_connect
c_func
(paren
r_struct
id|input_handler
op_star
id|handler
comma
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|mousedev
op_star
id|mousedev
suffix:semicolon
r_int
id|minor
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|EV_KEY
comma
id|dev-&gt;evbit
)paren
op_logical_or
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|BTN_LEFT
comma
id|dev-&gt;keybit
)paren
op_logical_and
op_logical_neg
id|test_bit
c_func
(paren
id|BTN_TOUCH
comma
id|dev-&gt;keybit
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|EV_REL
comma
id|dev-&gt;evbit
)paren
op_logical_or
op_logical_neg
id|test_bit
c_func
(paren
id|REL_X
comma
id|dev-&gt;relbit
)paren
)paren
op_logical_and
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|EV_ABS
comma
id|dev-&gt;evbit
)paren
op_logical_or
op_logical_neg
id|test_bit
c_func
(paren
id|ABS_X
comma
id|dev-&gt;absbit
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|minor
op_assign
l_int|0
suffix:semicolon
id|minor
OL
id|MOUSEDEV_MINORS
op_logical_and
id|mousedev_table
(braket
id|minor
)braket
suffix:semicolon
id|minor
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_eq
id|MOUSEDEV_MINORS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;mousedev: no more free mousedev devices&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|mousedev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|mousedev
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|mousedev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mousedev
)paren
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|mousedev-&gt;wait
)paren
suffix:semicolon
id|mousedev-&gt;exist
op_assign
l_int|1
suffix:semicolon
id|mousedev-&gt;minor
op_assign
id|minor
suffix:semicolon
id|mousedev_table
(braket
id|minor
)braket
op_assign
id|mousedev
suffix:semicolon
id|mousedev-&gt;handle.dev
op_assign
id|dev
suffix:semicolon
id|mousedev-&gt;handle.handler
op_assign
id|handler
suffix:semicolon
id|mousedev-&gt;handle
dot
r_private
op_assign
id|mousedev
suffix:semicolon
id|mousedev-&gt;devfs
op_assign
id|input_register_minor
c_func
(paren
l_string|&quot;mouse%d&quot;
comma
id|minor
comma
id|MOUSEDEV_MINOR_BASE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mousedev_mix.open
)paren
id|input_open_device
c_func
(paren
op_amp
id|mousedev-&gt;handle
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;mouse%d: PS/2 mouse device for input%d&bslash;n&quot;
comma
id|minor
comma
id|dev-&gt;number
)paren
suffix:semicolon
r_return
op_amp
id|mousedev-&gt;handle
suffix:semicolon
)brace
DECL|function|mousedev_disconnect
r_static
r_void
id|mousedev_disconnect
c_func
(paren
r_struct
id|input_handle
op_star
id|handle
)paren
(brace
r_struct
id|mousedev
op_star
id|mousedev
op_assign
id|handle
op_member_access_from_pointer
r_private
suffix:semicolon
id|mousedev-&gt;exist
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mousedev-&gt;open
)paren
(brace
id|input_close_device
c_func
(paren
id|handle
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|mousedev_mix.open
)paren
id|input_close_device
c_func
(paren
id|handle
)paren
suffix:semicolon
id|input_unregister_minor
c_func
(paren
id|mousedev-&gt;devfs
)paren
suffix:semicolon
id|mousedev_table
(braket
id|mousedev-&gt;minor
)braket
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|mousedev
)paren
suffix:semicolon
)brace
)brace
DECL|variable|mousedev_handler
r_static
r_struct
id|input_handler
id|mousedev_handler
op_assign
(brace
id|event
suffix:colon
id|mousedev_event
comma
id|connect
suffix:colon
id|mousedev_connect
comma
id|disconnect
suffix:colon
id|mousedev_disconnect
comma
id|fops
suffix:colon
op_amp
id|mousedev_fops
comma
id|minor
suffix:colon
id|MOUSEDEV_MINOR_BASE
comma
)brace
suffix:semicolon
DECL|function|mousedev_init
r_static
r_int
id|__init
id|mousedev_init
c_func
(paren
r_void
)paren
(brace
id|input_register_handler
c_func
(paren
op_amp
id|mousedev_handler
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|mousedev_mix
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|mousedev
)paren
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|mousedev_mix.wait
)paren
suffix:semicolon
id|mousedev_table
(braket
id|MOUSEDEV_MIX
)braket
op_assign
op_amp
id|mousedev_mix
suffix:semicolon
id|mousedev_mix.exist
op_assign
l_int|1
suffix:semicolon
id|mousedev_mix.minor
op_assign
id|MOUSEDEV_MIX
suffix:semicolon
id|mousedev_mix.devfs
op_assign
id|input_register_minor
c_func
(paren
l_string|&quot;mice&quot;
comma
id|MOUSEDEV_MIX
comma
id|MOUSEDEV_MINOR_BASE
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;mice: PS/2 mouse device common for all mice&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mousedev_exit
r_static
r_void
id|__exit
id|mousedev_exit
c_func
(paren
r_void
)paren
(brace
id|input_unregister_minor
c_func
(paren
id|mousedev_mix.devfs
)paren
suffix:semicolon
id|input_unregister_handler
c_func
(paren
op_amp
id|mousedev_handler
)paren
suffix:semicolon
)brace
DECL|variable|mousedev_init
id|module_init
c_func
(paren
id|mousedev_init
)paren
suffix:semicolon
DECL|variable|mousedev_exit
id|module_exit
c_func
(paren
id|mousedev_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@suse.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Input driver to PS/2 or ImPS/2 device driver&quot;
)paren
suffix:semicolon
eof
