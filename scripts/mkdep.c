macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;sys/fcntl.h&gt;
macro_line|#include &lt;sys/mman.h&gt;
DECL|variable|filename
DECL|variable|command
DECL|variable|__depname
r_char
op_star
id|filename
comma
op_star
id|command
comma
id|__depname
(braket
l_int|256
)braket
op_assign
l_string|&quot;&bslash;n&bslash;t@touch &quot;
suffix:semicolon
DECL|variable|needsconfig
DECL|variable|hasconfig
DECL|variable|hasdep
r_int
id|needsconfig
comma
id|hasconfig
comma
id|hasdep
suffix:semicolon
DECL|macro|depname
mdefine_line|#define depname (__depname+9)
DECL|struct|path_struct
r_struct
id|path_struct
(brace
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|buffer
r_char
id|buffer
(braket
l_int|256
op_minus
r_sizeof
(paren
r_int
)paren
)braket
suffix:semicolon
DECL|variable|path_array
)brace
id|path_array
(braket
l_int|2
)braket
op_assign
(brace
(brace
l_int|23
comma
l_string|&quot;/usr/src/linux/include/&quot;
)brace
comma
(brace
l_int|0
comma
l_string|&quot;&quot;
)brace
)brace
suffix:semicolon
DECL|function|handle_include
r_static
r_void
id|handle_include
c_func
(paren
r_int
id|type
comma
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_int
id|plen
suffix:semicolon
r_struct
id|path_struct
op_star
id|path
op_assign
id|path_array
op_plus
id|type
suffix:semicolon
r_if
c_cond
(paren
id|len
op_eq
l_int|14
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|name
comma
l_string|&quot;linux/config.h&quot;
comma
id|len
)paren
)paren
id|hasconfig
op_assign
l_int|1
suffix:semicolon
id|plen
op_assign
id|path-&gt;len
suffix:semicolon
id|memcpy
c_func
(paren
id|path-&gt;buffer
op_plus
id|plen
comma
id|name
comma
id|len
)paren
suffix:semicolon
id|len
op_add_assign
id|plen
suffix:semicolon
id|path-&gt;buffer
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|access
c_func
(paren
id|path-&gt;buffer
comma
id|F_OK
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hasdep
)paren
(brace
id|hasdep
op_assign
l_int|1
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;%s:&quot;
comma
id|depname
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot; &bslash;&bslash;&bslash;n   %s&quot;
comma
id|path-&gt;buffer
)paren
suffix:semicolon
)brace
DECL|function|handle_config
r_static
r_void
id|handle_config
c_func
(paren
r_void
)paren
(brace
id|needsconfig
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hasconfig
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s needs config but has not included config file&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
)brace
macro_line|#if defined(__alpha__) || defined(__i386__)
DECL|macro|LE_MACHINE
mdefine_line|#define LE_MACHINE
macro_line|#endif
macro_line|#ifdef LE_MACHINE
DECL|macro|next_byte
mdefine_line|#define next_byte(x) (x &gt;&gt;= 8)
DECL|macro|current
mdefine_line|#define current ((unsigned char) __buf)
macro_line|#else
DECL|macro|next_byte
mdefine_line|#define next_byte(x) (x &lt;&lt;= 8)
DECL|macro|current
mdefine_line|#define current (__buf &gt;&gt; 8*(sizeof(unsigned long)-1))
macro_line|#endif
DECL|macro|GETNEXT
mdefine_line|#define GETNEXT { &bslash;&n;next_byte(__buf); &bslash;&n;if (!__nrbuf) { &bslash;&n;&t;__buf = *(unsigned long *) next; &bslash;&n;&t;__nrbuf = sizeof(unsigned long); &bslash;&n;&t;if (!__buf) &bslash;&n;&t;&t;break; &bslash;&n;} next++; __nrbuf--; }
DECL|macro|CASE
mdefine_line|#define CASE(c,label) if (current == c) goto label
DECL|macro|NOTCASE
mdefine_line|#define NOTCASE(c,label) if (current != c) goto label
DECL|function|state_machine
r_static
r_void
id|state_machine
c_func
(paren
r_register
r_char
op_star
id|next
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_register
r_int
r_int
id|__buf
op_assign
l_int|0
suffix:semicolon
r_register
r_int
r_int
id|__nrbuf
op_assign
l_int|0
suffix:semicolon
id|normal
suffix:colon
id|GETNEXT
id|__normal
suffix:colon
id|CASE
c_func
(paren
l_char|&squot;/&squot;
comma
id|slash
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;&quot;&squot;
comma
id|string
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;&bslash;&squot;&squot;
comma
id|char_const
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;#&squot;
comma
id|preproc
)paren
suffix:semicolon
r_goto
id|normal
suffix:semicolon
id|slash
suffix:colon
id|GETNEXT
id|CASE
c_func
(paren
l_char|&squot;*&squot;
comma
id|comment
)paren
suffix:semicolon
r_goto
id|__normal
suffix:semicolon
id|string
suffix:colon
id|GETNEXT
id|CASE
c_func
(paren
l_char|&squot;&quot;&squot;
comma
id|normal
)paren
suffix:semicolon
id|NOTCASE
c_func
(paren
l_char|&squot;&bslash;&bslash;&squot;
comma
id|string
)paren
suffix:semicolon
id|GETNEXT
r_goto
id|string
suffix:semicolon
id|char_const
suffix:colon
id|GETNEXT
id|CASE
c_func
(paren
l_char|&squot;&bslash;&squot;&squot;
comma
id|normal
)paren
suffix:semicolon
id|NOTCASE
c_func
(paren
l_char|&squot;&bslash;&bslash;&squot;
comma
id|char_const
)paren
suffix:semicolon
id|GETNEXT
r_goto
id|char_const
suffix:semicolon
id|comment
suffix:colon
id|GETNEXT
id|__comment
suffix:colon
id|NOTCASE
c_func
(paren
l_char|&squot;*&squot;
comma
id|comment
)paren
suffix:semicolon
id|GETNEXT
id|CASE
c_func
(paren
l_char|&squot;/&squot;
comma
id|normal
)paren
suffix:semicolon
r_goto
id|__comment
suffix:semicolon
id|preproc
suffix:colon
id|GETNEXT
id|CASE
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|normal
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot; &squot;
comma
id|preproc
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;&bslash;t&squot;
comma
id|preproc
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;i&squot;
comma
id|i_preproc
)paren
suffix:semicolon
id|GETNEXT
id|skippreproc
suffix:colon
id|CASE
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|normal
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;&bslash;&bslash;&squot;
comma
id|skippreprocslash
)paren
suffix:semicolon
id|GETNEXT
r_goto
id|skippreproc
suffix:semicolon
id|skippreprocslash
suffix:colon
id|GETNEXT
suffix:semicolon
id|GETNEXT
suffix:semicolon
r_goto
id|skippreproc
suffix:semicolon
id|i_preproc
suffix:colon
id|GETNEXT
id|CASE
c_func
(paren
l_char|&squot;f&squot;
comma
id|if_line
)paren
suffix:semicolon
id|NOTCASE
c_func
(paren
l_char|&squot;n&squot;
comma
id|skippreproc
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;c&squot;
comma
id|skippreproc
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;l&squot;
comma
id|skippreproc
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;u&squot;
comma
id|skippreproc
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;d&squot;
comma
id|skippreproc
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;e&squot;
comma
id|skippreproc
)paren
suffix:semicolon
multiline_comment|/* &quot;# include&quot; found */
id|include_line
suffix:colon
id|GETNEXT
id|CASE
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|normal
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;&lt;&squot;
comma
id|std_include_file
)paren
suffix:semicolon
id|NOTCASE
c_func
(paren
l_char|&squot;&quot;&squot;
comma
id|include_line
)paren
suffix:semicolon
multiline_comment|/* &quot;local&quot; include file */
(brace
r_char
op_star
id|incname
op_assign
id|next
suffix:semicolon
id|local_include_name
suffix:colon
id|GETNEXT
id|CASE
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|normal
)paren
suffix:semicolon
id|NOTCASE
c_func
(paren
l_char|&squot;&quot;&squot;
comma
id|local_include_name
)paren
suffix:semicolon
id|handle_include
c_func
(paren
l_int|1
comma
id|incname
comma
id|next
op_minus
id|incname
op_minus
l_int|1
)paren
suffix:semicolon
r_goto
id|skippreproc
suffix:semicolon
)brace
multiline_comment|/* &lt;std&gt; include file */
id|std_include_file
suffix:colon
(brace
r_char
op_star
id|incname
op_assign
id|next
suffix:semicolon
id|std_include_name
suffix:colon
id|GETNEXT
id|CASE
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|normal
)paren
suffix:semicolon
id|NOTCASE
c_func
(paren
l_char|&squot;&gt;&squot;
comma
id|std_include_name
)paren
suffix:semicolon
id|handle_include
c_func
(paren
l_int|0
comma
id|incname
comma
id|next
op_minus
id|incname
op_minus
l_int|1
)paren
suffix:semicolon
r_goto
id|skippreproc
suffix:semicolon
)brace
id|if_line
suffix:colon
r_if
c_cond
(paren
id|needsconfig
)paren
r_goto
id|skippreproc
suffix:semicolon
id|if_start
suffix:colon
id|GETNEXT
id|CASE
c_func
(paren
l_char|&squot;C&squot;
comma
id|config
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|normal
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;_&squot;
comma
id|if_middle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current
op_ge
l_char|&squot;a&squot;
op_logical_and
id|current
op_le
l_char|&squot;z&squot;
)paren
r_goto
id|if_middle
suffix:semicolon
r_if
c_cond
(paren
id|current
template_param
l_char|&squot;Z&squot;
)paren
r_goto
id|if_start
suffix:semicolon
id|config
suffix:colon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;O&squot;
comma
id|__if_middle
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;N&squot;
comma
id|__if_middle
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;F&squot;
comma
id|__if_middle
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;I&squot;
comma
id|__if_middle
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;G&squot;
comma
id|__if_middle
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;_&squot;
comma
id|__if_middle
)paren
suffix:semicolon
id|handle_config
c_func
(paren
)paren
suffix:semicolon
r_goto
id|skippreproc
suffix:semicolon
id|if_middle
suffix:colon
id|GETNEXT
id|__if_middle
suffix:colon
id|CASE
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|normal
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;_&squot;
comma
id|if_middle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current
op_ge
l_char|&squot;a&squot;
op_logical_and
id|current
op_le
l_char|&squot;z&squot;
)paren
r_goto
id|if_middle
suffix:semicolon
r_if
c_cond
(paren
id|current
template_param
l_char|&squot;Z&squot;
)paren
r_goto
id|if_start
suffix:semicolon
r_goto
id|if_middle
suffix:semicolon
)brace
)brace
DECL|function|do_depend
r_static
r_void
id|do_depend
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|map
suffix:semicolon
r_int
id|mapsize
suffix:semicolon
r_int
id|pagesizem1
op_assign
id|getpagesize
c_func
(paren
)paren
op_minus
l_int|1
suffix:semicolon
r_int
id|fd
op_assign
id|open
c_func
(paren
id|filename
comma
id|O_RDONLY
)paren
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;mkdep: open&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|fstat
c_func
(paren
id|fd
comma
op_amp
id|st
)paren
suffix:semicolon
r_if
c_cond
(paren
id|st.st_size
op_eq
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s is empty&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|mapsize
op_assign
id|st.st_size
op_plus
l_int|2
op_star
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|mapsize
op_assign
(paren
id|mapsize
op_plus
id|pagesizem1
)paren
op_amp
op_complement
id|pagesizem1
suffix:semicolon
id|map
op_assign
id|mmap
c_func
(paren
l_int|NULL
comma
id|mapsize
comma
id|PROT_READ
comma
id|MAP_PRIVATE
comma
id|fd
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_minus
l_int|1
op_eq
(paren
r_int
)paren
id|map
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;mkdep: mmap&quot;
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|state_machine
c_func
(paren
id|map
)paren
suffix:semicolon
id|munmap
c_func
(paren
id|map
comma
id|mapsize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hasdep
)paren
id|puts
c_func
(paren
id|command
)paren
suffix:semicolon
)brace
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
id|len
suffix:semicolon
r_char
op_star
id|hpath
suffix:semicolon
id|hpath
op_assign
id|getenv
c_func
(paren
l_string|&quot;HPATH&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hpath
)paren
id|hpath
op_assign
l_string|&quot;/usr/src/linux/include&quot;
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|hpath
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|path_array
(braket
l_int|0
)braket
dot
id|buffer
comma
id|hpath
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_logical_and
id|hpath
(braket
id|len
op_minus
l_int|1
)braket
op_ne
l_char|&squot;/&squot;
)paren
(brace
id|path_array
(braket
l_int|0
)braket
dot
id|buffer
(braket
id|len
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|len
op_increment
suffix:semicolon
)brace
id|path_array
(braket
l_int|0
)braket
dot
id|buffer
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|path_array
(braket
l_int|0
)braket
dot
id|len
op_assign
id|len
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|argc
OG
l_int|0
)paren
(brace
r_int
id|len
suffix:semicolon
r_char
op_star
id|name
op_assign
op_star
op_increment
id|argv
suffix:semicolon
id|filename
op_assign
id|name
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|name
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|depname
comma
id|name
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|command
op_assign
id|__depname
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|2
op_logical_and
id|name
(braket
id|len
op_minus
l_int|2
)braket
op_eq
l_char|&squot;.&squot;
)paren
(brace
r_switch
c_cond
(paren
id|name
(braket
id|len
op_minus
l_int|1
)braket
)paren
(brace
r_case
l_char|&squot;c&squot;
suffix:colon
r_case
l_char|&squot;S&squot;
suffix:colon
id|depname
(braket
id|len
op_minus
l_int|1
)braket
op_assign
l_char|&squot;o&squot;
suffix:semicolon
id|command
op_assign
l_string|&quot;&quot;
suffix:semicolon
)brace
)brace
id|needsconfig
op_assign
id|hasconfig
op_assign
id|hasdep
op_assign
l_int|0
suffix:semicolon
id|do_depend
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hasconfig
op_logical_and
op_logical_neg
id|needsconfig
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s doesn&squot;t need config&bslash;n&quot;
comma
id|filename
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
