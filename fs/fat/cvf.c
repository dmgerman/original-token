multiline_comment|/*&n; * CVF extensions for fat-based filesystems&n; *&n; * written 1997,1998 by Frank Gockel &lt;gockel@sent13.uni-duisburg.de&gt;&n; *&n; */
macro_line|#include&lt;linux/sched.h&gt;
macro_line|#include&lt;linux/fs.h&gt;
macro_line|#include&lt;linux/msdos_fs.h&gt;
macro_line|#include&lt;linux/msdos_fs_sb.h&gt;
macro_line|#include&lt;linux/string.h&gt;
macro_line|#include&lt;linux/fat_cvf.h&gt;
DECL|macro|MAX_CVF_FORMATS
mdefine_line|#define MAX_CVF_FORMATS 3
DECL|variable|cvf_formats
r_struct
id|cvf_format
op_star
id|cvf_formats
(braket
id|MAX_CVF_FORMATS
)braket
op_assign
initialization_block
suffix:semicolon
DECL|variable|cvf_format_use_count
r_int
id|cvf_format_use_count
(braket
id|MAX_CVF_FORMATS
)braket
op_assign
initialization_block
suffix:semicolon
DECL|function|register_cvf_format
r_int
id|register_cvf_format
c_func
(paren
r_struct
id|cvf_format
op_star
id|cvf_format
)paren
(brace
r_int
id|i
comma
id|j
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
id|MAX_CVF_FORMATS
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|cvf_formats
(braket
id|i
)braket
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* free slot found, now check version */
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|MAX_CVF_FORMATS
suffix:semicolon
op_increment
id|j
)paren
(brace
r_if
c_cond
(paren
id|cvf_formats
(braket
id|j
)braket
)paren
(brace
r_if
c_cond
(paren
id|cvf_formats
(braket
id|j
)braket
op_member_access_from_pointer
id|cvf_version
op_eq
id|cvf_format-&gt;cvf_version
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;register_cvf_format: version %d already registered&bslash;n&quot;
comma
id|cvf_format-&gt;cvf_version
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
)brace
id|cvf_formats
(braket
id|i
)braket
op_assign
id|cvf_format
suffix:semicolon
id|cvf_format_use_count
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CVF format %s (version id %d) successfully registered.&bslash;n&quot;
comma
id|cvf_format-&gt;cvf_version_text
comma
id|cvf_format-&gt;cvf_version
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;register_cvf_format: too many formats&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|unregister_cvf_format
r_int
id|unregister_cvf_format
c_func
(paren
r_struct
id|cvf_format
op_star
id|cvf_format
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
id|MAX_CVF_FORMATS
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|cvf_formats
(braket
id|i
)braket
)paren
(brace
r_if
c_cond
(paren
id|cvf_formats
(braket
id|i
)braket
op_member_access_from_pointer
id|cvf_version
op_eq
id|cvf_format-&gt;cvf_version
)paren
(brace
r_if
c_cond
(paren
id|cvf_format_use_count
(braket
id|i
)braket
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unregister_cvf_format: format %d in use, cannot remove!&bslash;n&quot;
comma
id|cvf_formats
(braket
id|i
)braket
op_member_access_from_pointer
id|cvf_version
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;CVF format %s (version id %d) successfully unregistered.&bslash;n&quot;
comma
id|cvf_formats
(braket
id|i
)braket
op_member_access_from_pointer
id|cvf_version_text
comma
id|cvf_formats
(braket
id|i
)braket
op_member_access_from_pointer
id|cvf_version
)paren
suffix:semicolon
id|cvf_formats
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;unregister_cvf_format: format %d is not registered&bslash;n&quot;
comma
id|cvf_format-&gt;cvf_version
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|dec_cvf_format_use_count_by_version
r_void
id|dec_cvf_format_use_count_by_version
c_func
(paren
r_int
id|version
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
id|MAX_CVF_FORMATS
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|cvf_formats
(braket
id|i
)braket
)paren
(brace
r_if
c_cond
(paren
id|cvf_formats
(braket
id|i
)braket
op_member_access_from_pointer
id|cvf_version
op_eq
id|version
)paren
(brace
op_decrement
id|cvf_format_use_count
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|cvf_format_use_count
(braket
id|i
)braket
OL
l_int|0
)paren
(brace
id|cvf_format_use_count
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;FAT FS/CVF: This is a bug in cvf_version_use_count&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;dec_cvf_format_use_count_by_version: version %d not found ???&bslash;n&quot;
comma
id|version
)paren
suffix:semicolon
)brace
DECL|function|detect_cvf
r_int
id|detect_cvf
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_char
op_star
id|force
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|found
op_assign
l_int|0
suffix:semicolon
r_int
id|found_i
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|force
)paren
(brace
r_if
c_cond
(paren
op_star
id|force
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_CVF_FORMATS
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|cvf_formats
(braket
id|i
)braket
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|cvf_formats
(braket
id|i
)braket
op_member_access_from_pointer
id|cvf_version_text
comma
id|force
)paren
)paren
(brace
r_return
id|i
suffix:semicolon
)brace
)brace
)brace
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_CVF_FORMATS
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|cvf_formats
(braket
id|i
)braket
)paren
(brace
r_if
c_cond
(paren
id|cvf_formats
(braket
id|i
)braket
op_member_access_from_pointer
id|detect_cvf
c_func
(paren
id|sb
)paren
)paren
(brace
op_increment
id|found
suffix:semicolon
id|found_i
op_assign
id|i
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|found
op_eq
l_int|1
)paren
(brace
r_return
id|found_i
suffix:semicolon
)brace
r_if
c_cond
(paren
id|found
OG
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;CVF detection ambiguous, use cvf_format=xxx option&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
eof