multiline_comment|/* bitmap.c contains the code that handles the inode and block bitmaps */
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
DECL|macro|clear_block
mdefine_line|#define clear_block(addr) &bslash;&n;__asm__(&quot;cld&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rep&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;stosl&quot; &bslash;&n;&t;::&quot;a&quot; (0),&quot;c&quot; (BLOCK_SIZE/4),&quot;D&quot; ((long) (addr)):&quot;cx&quot;,&quot;di&quot;)
DECL|macro|set_bit
mdefine_line|#define set_bit(nr,addr) ({&bslash;&n;register int res __asm__(&quot;ax&quot;); &bslash;&n;__asm__(&quot;btsl %2,%3&bslash;n&bslash;tsetb %%al&quot;:&quot;=a&quot; (res):&quot;0&quot; (0),&quot;r&quot; (nr),&quot;m&quot; (*(addr))); &bslash;&n;res;})
DECL|macro|clear_bit
mdefine_line|#define clear_bit(nr,addr) ({&bslash;&n;register int res __asm__(&quot;ax&quot;); &bslash;&n;__asm__(&quot;btrl %2,%3&bslash;n&bslash;tsetnb %%al&quot;:&quot;=a&quot; (res):&quot;0&quot; (0),&quot;r&quot; (nr),&quot;m&quot; (*(addr))); &bslash;&n;res;})
DECL|macro|find_first_zero
mdefine_line|#define find_first_zero(addr) ({ &bslash;&n;int __res; &bslash;&n;__asm__(&quot;cld&bslash;n&quot; &bslash;&n;&t;&quot;1:&bslash;tlodsl&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;notl %%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;bsfl %%eax,%%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;je 2f&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;addl %%edx,%%ecx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jmp 3f&bslash;n&quot; &bslash;&n;&t;&quot;2:&bslash;taddl $32,%%ecx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;cmpl $8192,%%ecx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jl 1b&bslash;n&quot; &bslash;&n;&t;&quot;3:&quot; &bslash;&n;&t;:&quot;=c&quot; (__res):&quot;c&quot; (0),&quot;S&quot; (addr):&quot;ax&quot;,&quot;dx&quot;,&quot;si&quot;); &bslash;&n;__res;})
DECL|function|free_block
r_void
id|free_block
c_func
(paren
r_int
id|dev
comma
r_int
id|block
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb
op_assign
id|get_super
c_func
(paren
id|dev
)paren
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;trying to free block on nonexistent device&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
OL
id|sb-&gt;s_firstdatazone
op_logical_or
id|block
op_ge
id|sb-&gt;s_nzones
)paren
id|panic
c_func
(paren
l_string|&quot;trying to free block not in datazone&quot;
)paren
suffix:semicolon
id|bh
op_assign
id|get_hash_table
c_func
(paren
id|dev
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
(brace
r_if
c_cond
(paren
id|bh-&gt;b_count
op_ne
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;trying to free block (%04x:%d), count=%d&bslash;n&quot;
comma
id|dev
comma
id|block
comma
id|bh-&gt;b_count
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|bh-&gt;b_dirt
op_assign
l_int|0
suffix:semicolon
id|bh-&gt;b_uptodate
op_assign
l_int|0
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
id|block
op_sub_assign
id|sb-&gt;s_firstdatazone
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|clear_bit
c_func
(paren
id|block
op_amp
l_int|8191
comma
id|sb-&gt;s_zmap
(braket
id|block
op_div
l_int|8192
)braket
op_member_access_from_pointer
id|b_data
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;block (%04x:%d) &quot;
comma
id|dev
comma
id|block
op_plus
id|sb-&gt;s_firstdatazone
op_minus
l_int|1
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;free_block: bit already cleared&quot;
)paren
suffix:semicolon
)brace
id|sb-&gt;s_zmap
(braket
id|block
op_div
l_int|8192
)braket
op_member_access_from_pointer
id|b_dirt
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|new_block
r_int
id|new_block
c_func
(paren
r_int
id|dev
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb
op_assign
id|get_super
c_func
(paren
id|dev
)paren
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;trying to get new block from nonexistant device&quot;
)paren
suffix:semicolon
id|j
op_assign
l_int|8192
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|bh
op_assign
id|sb-&gt;s_zmap
(braket
id|i
)braket
)paren
r_if
c_cond
(paren
(paren
id|j
op_assign
id|find_first_zero
c_func
(paren
id|bh-&gt;b_data
)paren
)paren
OL
l_int|8192
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
l_int|8
op_logical_or
op_logical_neg
id|bh
op_logical_or
id|j
op_ge
l_int|8192
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|set_bit
c_func
(paren
id|j
comma
id|bh-&gt;b_data
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;new_block: bit already set&quot;
)paren
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|j
op_add_assign
id|i
op_star
l_int|8192
op_plus
id|sb-&gt;s_firstdatazone
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|j
op_ge
id|sb-&gt;s_nzones
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|getblk
c_func
(paren
id|dev
comma
id|j
)paren
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;new_block: cannot get block&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh-&gt;b_count
op_ne
l_int|1
)paren
id|panic
c_func
(paren
l_string|&quot;new block: count is != 1&quot;
)paren
suffix:semicolon
id|clear_block
c_func
(paren
id|bh-&gt;b_data
)paren
suffix:semicolon
id|bh-&gt;b_uptodate
op_assign
l_int|1
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|j
suffix:semicolon
)brace
DECL|function|free_inode
r_void
id|free_inode
c_func
(paren
r_struct
id|m_inode
op_star
id|inode
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_dev
)paren
(brace
id|memset
c_func
(paren
id|inode
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_count
OG
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;trying to free inode with count=%d&bslash;n&quot;
comma
id|inode-&gt;i_count
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;free_inode&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_nlinks
)paren
id|panic
c_func
(paren
l_string|&quot;trying to free inode with links&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb
op_assign
id|get_super
c_func
(paren
id|inode-&gt;i_dev
)paren
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;trying to free inode on nonexistent device&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_num
template_param
id|sb-&gt;s_ninodes
)paren
id|panic
c_func
(paren
l_string|&quot;trying to free inode 0 or nonexistant inode&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|sb-&gt;s_imap
(braket
id|inode-&gt;i_num
op_rshift
l_int|13
)braket
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;nonexistent imap in superblock&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|clear_bit
c_func
(paren
id|inode-&gt;i_num
op_amp
l_int|8191
comma
id|bh-&gt;b_data
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;free_inode: bit already cleared&quot;
)paren
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|memset
c_func
(paren
id|inode
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|inode
)paren
)paren
suffix:semicolon
)brace
DECL|function|new_inode
r_struct
id|m_inode
op_star
id|new_inode
c_func
(paren
r_int
id|dev
)paren
(brace
r_struct
id|m_inode
op_star
id|inode
suffix:semicolon
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|get_empty_inode
c_func
(paren
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb
op_assign
id|get_super
c_func
(paren
id|dev
)paren
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;new_inode with unknown device&quot;
)paren
suffix:semicolon
id|j
op_assign
l_int|8192
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|bh
op_assign
id|sb-&gt;s_imap
(braket
id|i
)braket
)paren
r_if
c_cond
(paren
(paren
id|j
op_assign
id|find_first_zero
c_func
(paren
id|bh-&gt;b_data
)paren
)paren
OL
l_int|8192
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
op_logical_or
id|j
op_ge
l_int|8192
op_logical_or
id|j
op_plus
id|i
op_star
l_int|8192
OG
id|sb-&gt;s_ninodes
)paren
(brace
id|iput
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|set_bit
c_func
(paren
id|j
comma
id|bh-&gt;b_data
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;new_inode: bit already set&quot;
)paren
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_count
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_nlinks
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_dev
op_assign
id|dev
suffix:semicolon
id|inode-&gt;i_dirt
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_num
op_assign
id|j
op_plus
id|i
op_star
l_int|8192
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|inode-&gt;i_atime
op_assign
id|inode-&gt;i_ctime
op_assign
id|CURRENT_TIME
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
eof
