multiline_comment|/*&n; * Originally by Linus Torvalds.&n; * Smart CONFIG_* processing by Werner Almesberger, Michael Chastain.&n; *&n; * Usage: mkdep file ...&n; * &n; * Read source files and output makefile dependency lines for them.&n; * I make simple dependency lines for #include &lt;*.h&gt; and #include &quot;*.h&quot;.&n; * I also find instances of CONFIG_FOO and generate dependencies&n; *    like include/config/foo.h.&n; *&n; * 1 August 1999, Michael Elizabeth Chastain, &lt;mec@shout.net&gt;&n; * - Keith Owens reported a bug in smart config processing.  There used&n; *   to be an optimization for &quot;#define CONFIG_FOO ... #ifdef CONFIG_FOO&quot;,&n; *   so that the file would not depend on CONFIG_FOO because the file defines&n; *   this symbol itself.  But this optimization is bogus!  Consider this code:&n; *   &quot;#if 0 &bslash;n #define CONFIG_FOO &bslash;n #endif ... #ifdef CONFIG_FOO&quot;.  Here&n; *   the definition is inactivated, but I still used it.  It turns out this&n; *   actually happens a few times in the kernel source.  The simple way to&n; *   fix this problem is to remove this particular optimization.&n; *&n; * 2.3.99-pre1, Andrew Morton &lt;andrewm@uow.edu.au&gt;&n; * - Changed so that &squot;filename.o&squot; depends upon &squot;filename.[cS]&squot;.  This is so that&n; *   missing source files are noticed, rather than silently ignored.&n; */
macro_line|#include &lt;ctype.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;sys/fcntl.h&gt;
macro_line|#include &lt;sys/mman.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;sys/types.h&gt;
DECL|variable|__depname
r_char
id|__depname
(braket
l_int|512
)braket
op_assign
l_string|&quot;&bslash;n&bslash;t@touch &quot;
suffix:semicolon
DECL|macro|depname
mdefine_line|#define depname (__depname+9)
DECL|variable|hasdep
r_int
id|hasdep
suffix:semicolon
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
l_int|0
comma
l_string|&quot;&quot;
)brace
comma
(brace
l_int|0
comma
l_string|&quot;&quot;
)brace
)brace
suffix:semicolon
multiline_comment|/* Current input file */
DECL|variable|g_filename
r_static
r_const
r_char
op_star
id|g_filename
suffix:semicolon
multiline_comment|/*&n; * This records all the configuration options seen.&n; * In perl this would be a hash, but here it&squot;s a long string&n; * of values separated by newlines.  This is simple and&n; * extremely fast.&n; */
DECL|variable|str_config
r_char
op_star
id|str_config
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|size_config
r_int
id|size_config
op_assign
l_int|0
suffix:semicolon
DECL|variable|len_config
r_int
id|len_config
op_assign
l_int|0
suffix:semicolon
r_static
r_void
DECL|function|do_depname
id|do_depname
c_func
(paren
r_void
)paren
(brace
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
r_if
c_cond
(paren
id|g_filename
)paren
id|printf
c_func
(paren
l_string|&quot; %s&quot;
comma
id|g_filename
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Grow the configuration string to a desired length.&n; * Usually the first growth is plenty.&n; */
DECL|function|grow_config
r_void
id|grow_config
c_func
(paren
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|str_config
op_eq
l_int|NULL
)paren
(brace
id|len_config
op_assign
l_int|0
suffix:semicolon
id|size_config
op_assign
l_int|4096
suffix:semicolon
id|str_config
op_assign
id|malloc
c_func
(paren
l_int|4096
)paren
suffix:semicolon
r_if
c_cond
(paren
id|str_config
op_eq
l_int|NULL
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;malloc&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|len_config
op_plus
id|len
OG
id|size_config
)paren
(brace
id|str_config
op_assign
id|realloc
c_func
(paren
id|str_config
comma
id|size_config
op_mul_assign
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|str_config
op_eq
l_int|NULL
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;malloc config&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Lookup a value in the configuration string.&n; */
DECL|function|is_defined_config
r_int
id|is_defined_config
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_const
r_char
op_star
id|pconfig
suffix:semicolon
r_const
r_char
op_star
id|plast
op_assign
id|str_config
op_plus
id|len_config
op_minus
id|len
suffix:semicolon
r_for
c_loop
(paren
id|pconfig
op_assign
id|str_config
op_plus
l_int|1
suffix:semicolon
id|pconfig
OL
id|plast
suffix:semicolon
id|pconfig
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pconfig
(braket
op_minus
l_int|1
)braket
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_and
id|pconfig
(braket
id|len
)braket
op_eq
l_char|&squot;&bslash;n&squot;
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|pconfig
comma
id|name
comma
id|len
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Add a new value to the configuration string.&n; */
DECL|function|define_config
r_void
id|define_config
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
id|grow_config
c_func
(paren
id|len
op_plus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|str_config
op_plus
id|len_config
comma
id|name
comma
id|len
)paren
suffix:semicolon
id|len_config
op_add_assign
id|len
suffix:semicolon
id|str_config
(braket
id|len_config
op_increment
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
)brace
multiline_comment|/*&n; * Clear the set of configuration strings.&n; */
DECL|function|clear_config
r_void
id|clear_config
c_func
(paren
r_void
)paren
(brace
id|len_config
op_assign
l_int|0
suffix:semicolon
id|define_config
c_func
(paren
l_string|&quot;&quot;
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This records all the precious .h filenames.  No need for a hash,&n; * it&squot;s a long string of values enclosed in tab and newline.&n; */
DECL|variable|str_precious
r_char
op_star
id|str_precious
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|size_precious
r_int
id|size_precious
op_assign
l_int|0
suffix:semicolon
DECL|variable|len_precious
r_int
id|len_precious
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Grow the precious string to a desired length.&n; * Usually the first growth is plenty.&n; */
DECL|function|grow_precious
r_void
id|grow_precious
c_func
(paren
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|str_precious
op_eq
l_int|NULL
)paren
(brace
id|len_precious
op_assign
l_int|0
suffix:semicolon
id|size_precious
op_assign
l_int|4096
suffix:semicolon
id|str_precious
op_assign
id|malloc
c_func
(paren
l_int|4096
)paren
suffix:semicolon
r_if
c_cond
(paren
id|str_precious
op_eq
l_int|NULL
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;malloc precious&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|len_precious
op_plus
id|len
OG
id|size_precious
)paren
(brace
id|str_precious
op_assign
id|realloc
c_func
(paren
id|str_precious
comma
id|size_precious
op_mul_assign
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|str_precious
op_eq
l_int|NULL
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;malloc&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Add a new value to the precious string.&n; */
DECL|function|define_precious
r_void
id|define_precious
c_func
(paren
r_const
r_char
op_star
id|filename
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|filename
)paren
suffix:semicolon
id|grow_precious
c_func
(paren
id|len
op_plus
l_int|4
)paren
suffix:semicolon
op_star
(paren
id|str_precious
op_plus
id|len_precious
op_increment
)paren
op_assign
l_char|&squot;&bslash;t&squot;
suffix:semicolon
id|memcpy
c_func
(paren
id|str_precious
op_plus
id|len_precious
comma
id|filename
comma
id|len
)paren
suffix:semicolon
id|len_precious
op_add_assign
id|len
suffix:semicolon
id|memcpy
c_func
(paren
id|str_precious
op_plus
id|len_precious
comma
l_string|&quot; &bslash;&bslash;&bslash;n&quot;
comma
l_int|3
)paren
suffix:semicolon
id|len_precious
op_add_assign
l_int|3
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle an #include line.&n; */
DECL|function|handle_include
r_void
id|handle_include
c_func
(paren
r_int
id|type
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
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
r_return
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
l_int|7
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|name
comma
l_string|&quot;config/&quot;
comma
l_int|7
)paren
)paren
id|define_config
c_func
(paren
id|name
op_plus
l_int|7
comma
id|len
op_minus
l_int|7
op_minus
l_int|2
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|path-&gt;buffer
op_plus
id|path-&gt;len
comma
id|name
comma
id|len
)paren
suffix:semicolon
id|path-&gt;buffer
(braket
id|path-&gt;len
op_plus
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
op_ne
l_int|0
)paren
r_return
suffix:semicolon
id|do_depname
c_func
(paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot; &bslash;&bslash;&bslash;n   %s&quot;
comma
id|path-&gt;buffer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Record the use of a CONFIG_* word.&n; */
DECL|function|use_config
r_void
id|use_config
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
(brace
r_char
op_star
id|pc
suffix:semicolon
r_int
id|i
suffix:semicolon
id|pc
op_assign
id|path_array
(braket
l_int|0
)braket
dot
id|buffer
op_plus
id|path_array
(braket
l_int|0
)braket
dot
id|len
suffix:semicolon
id|memcpy
c_func
(paren
id|pc
comma
l_string|&quot;config/&quot;
comma
l_int|7
)paren
suffix:semicolon
id|pc
op_add_assign
l_int|7
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
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
id|c
op_assign
id|name
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|isupper
c_func
(paren
id|c
)paren
)paren
id|c
op_assign
id|tolower
c_func
(paren
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;_&squot;
)paren
id|c
op_assign
l_char|&squot;/&squot;
suffix:semicolon
id|pc
(braket
id|i
)braket
op_assign
id|c
suffix:semicolon
)brace
id|pc
(braket
id|len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|is_defined_config
c_func
(paren
id|pc
comma
id|len
)paren
)paren
r_return
suffix:semicolon
id|define_config
c_func
(paren
id|pc
comma
id|len
)paren
suffix:semicolon
id|do_depname
c_func
(paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot; &bslash;&bslash;&bslash;n   $(wildcard %s.h)&quot;
comma
id|path_array
(braket
l_int|0
)braket
dot
id|buffer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Macros for stunningly fast map-based character access.&n; * __buf is a register which holds the current word of the input.&n; * Thus, there is one memory access per sizeof(unsigned long) characters.&n; */
macro_line|#if defined(__alpha__) || defined(__i386__) || defined(__ia64__) || defined(__MIPSEL__)&t;&bslash;&n;    || defined(__arm__)
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
mdefine_line|#define GETNEXT { &bslash;&n;&t;next_byte(__buf); &bslash;&n;&t;if ((unsigned long) next % sizeof(unsigned long) == 0) { &bslash;&n;&t;&t;if (next &gt;= end) &bslash;&n;&t;&t;&t;break; &bslash;&n;&t;&t;__buf = * (unsigned long *) next; &bslash;&n;&t;} &bslash;&n;&t;next++; &bslash;&n;}
multiline_comment|/*&n; * State machine macros.&n; */
DECL|macro|CASE
mdefine_line|#define CASE(c,label) if (current == c) goto label
DECL|macro|NOTCASE
mdefine_line|#define NOTCASE(c,label) if (current != c) goto label
multiline_comment|/*&n; * Yet another state machine speedup.&n; */
DECL|macro|MAX2
mdefine_line|#define MAX2(a,b) ((a)&gt;(b)?(a):(b))
DECL|macro|MIN2
mdefine_line|#define MIN2(a,b) ((a)&lt;(b)?(a):(b))
DECL|macro|MAX5
mdefine_line|#define MAX5(a,b,c,d,e) (MAX2(a,MAX2(b,MAX2(c,MAX2(d,e)))))
DECL|macro|MIN5
mdefine_line|#define MIN5(a,b,c,d,e) (MIN2(a,MIN2(b,MIN2(c,MIN2(d,e)))))
multiline_comment|/*&n; * The state machine looks for (approximately) these Perl regular expressions:&n; *&n; *    m|&bslash;/&bslash;*.*?&bslash;*&bslash;/|&n; *    m|&bslash;/&bslash;/.*|&n; *    m|&squot;.*?&squot;|&n; *    m|&quot;.*?&quot;|&n; *    m|#&bslash;s*include&bslash;s*&quot;(.*?)&quot;|&n; *    m|#&bslash;s*include&bslash;s*&lt;(.*?&gt;&quot;|&n; *    m|#&bslash;s*(?define|undef)&bslash;s*CONFIG_(&bslash;w*)|&n; *    m|(?!&bslash;w)CONFIG_|&n; *&n; * About 98% of the CPU time is spent here, and most of that is in&n; * the &squot;start&squot; paragraph.  Because the current characters are&n; * in a register, the start loop usually eats 4 or 8 characters&n; * per memory read.  The MAX5 and MIN5 tests dispose of most&n; * input characters with 1 or 2 comparisons.&n; */
DECL|function|state_machine
r_void
id|state_machine
c_func
(paren
r_const
r_char
op_star
id|map
comma
r_const
r_char
op_star
id|end
)paren
(brace
r_const
r_char
op_star
id|next
op_assign
id|map
suffix:semicolon
r_const
r_char
op_star
id|map_dot
suffix:semicolon
r_int
r_int
id|__buf
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|start
suffix:colon
id|GETNEXT
id|__start
suffix:colon
r_if
c_cond
(paren
id|current
OG
id|MAX5
c_func
(paren
l_char|&squot;/&squot;
comma
l_char|&squot;&bslash;&squot;&squot;
comma
l_char|&squot;&quot;&squot;
comma
l_char|&squot;#&squot;
comma
l_char|&squot;C&squot;
)paren
)paren
r_goto
id|start
suffix:semicolon
r_if
c_cond
(paren
id|current
OL
id|MIN5
c_func
(paren
l_char|&squot;/&squot;
comma
l_char|&squot;&bslash;&squot;&squot;
comma
l_char|&squot;&quot;&squot;
comma
l_char|&squot;#&squot;
comma
l_char|&squot;C&squot;
)paren
)paren
r_goto
id|start
suffix:semicolon
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
l_char|&squot;&bslash;&squot;&squot;
comma
id|squote
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;&quot;&squot;
comma
id|dquote
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;#&squot;
comma
id|pound
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;C&squot;
comma
id|cee
)paren
suffix:semicolon
r_goto
id|start
suffix:semicolon
multiline_comment|/* // */
id|slash_slash
suffix:colon
id|GETNEXT
id|CASE
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|start
)paren
suffix:semicolon
id|NOTCASE
c_func
(paren
l_char|&squot;&bslash;&bslash;&squot;
comma
id|slash_slash
)paren
suffix:semicolon
id|GETNEXT
r_goto
id|slash_slash
suffix:semicolon
multiline_comment|/* / */
id|slash
suffix:colon
id|GETNEXT
id|CASE
c_func
(paren
l_char|&squot;/&squot;
comma
id|slash_slash
)paren
suffix:semicolon
id|NOTCASE
c_func
(paren
l_char|&squot;*&squot;
comma
id|__start
)paren
suffix:semicolon
id|slash_star_dot_star
suffix:colon
id|GETNEXT
id|__slash_star_dot_star
suffix:colon
id|NOTCASE
c_func
(paren
l_char|&squot;*&squot;
comma
id|slash_star_dot_star
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;/&squot;
comma
id|__slash_star_dot_star
)paren
suffix:semicolon
r_goto
id|start
suffix:semicolon
multiline_comment|/* &squot;.*?&squot; */
id|squote
suffix:colon
id|GETNEXT
id|CASE
c_func
(paren
l_char|&squot;&bslash;&squot;&squot;
comma
id|start
)paren
suffix:semicolon
id|NOTCASE
c_func
(paren
l_char|&squot;&bslash;&bslash;&squot;
comma
id|squote
)paren
suffix:semicolon
id|GETNEXT
r_goto
id|squote
suffix:semicolon
multiline_comment|/* &quot;.*?&quot; */
id|dquote
suffix:colon
id|GETNEXT
id|CASE
c_func
(paren
l_char|&squot;&quot;&squot;
comma
id|start
)paren
suffix:semicolon
id|NOTCASE
c_func
(paren
l_char|&squot;&bslash;&bslash;&squot;
comma
id|dquote
)paren
suffix:semicolon
id|GETNEXT
r_goto
id|dquote
suffix:semicolon
multiline_comment|/* #&bslash;s* */
id|pound
suffix:colon
id|GETNEXT
id|CASE
c_func
(paren
l_char|&squot; &squot;
comma
id|pound
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;&bslash;t&squot;
comma
id|pound
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;i&squot;
comma
id|pound_i
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;d&squot;
comma
id|pound_d
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;u&squot;
comma
id|pound_u
)paren
suffix:semicolon
r_goto
id|__start
suffix:semicolon
multiline_comment|/* #&bslash;s*i */
id|pound_i
suffix:colon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;n&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;c&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;l&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;u&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;d&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;e&squot;
comma
id|__start
)paren
suffix:semicolon
r_goto
id|pound_include
suffix:semicolon
multiline_comment|/* #&bslash;s*include&bslash;s* */
id|pound_include
suffix:colon
id|GETNEXT
id|CASE
c_func
(paren
l_char|&squot; &squot;
comma
id|pound_include
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;&bslash;t&squot;
comma
id|pound_include
)paren
suffix:semicolon
id|map_dot
op_assign
id|next
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;&quot;&squot;
comma
id|pound_include_dquote
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;&lt;&squot;
comma
id|pound_include_langle
)paren
suffix:semicolon
r_goto
id|__start
suffix:semicolon
multiline_comment|/* #&bslash;s*include&bslash;s*&quot;(.*)&quot; */
id|pound_include_dquote
suffix:colon
id|GETNEXT
id|CASE
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|start
)paren
suffix:semicolon
id|NOTCASE
c_func
(paren
l_char|&squot;&quot;&squot;
comma
id|pound_include_dquote
)paren
suffix:semicolon
id|handle_include
c_func
(paren
l_int|1
comma
id|map_dot
comma
id|next
op_minus
id|map_dot
op_minus
l_int|1
)paren
suffix:semicolon
r_goto
id|start
suffix:semicolon
multiline_comment|/* #&bslash;s*include&bslash;s*&lt;(.*)&gt; */
id|pound_include_langle
suffix:colon
id|GETNEXT
id|CASE
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|start
)paren
suffix:semicolon
id|NOTCASE
c_func
(paren
l_char|&squot;&gt;&squot;
comma
id|pound_include_langle
)paren
suffix:semicolon
id|handle_include
c_func
(paren
l_int|0
comma
id|map_dot
comma
id|next
op_minus
id|map_dot
op_minus
l_int|1
)paren
suffix:semicolon
r_goto
id|start
suffix:semicolon
multiline_comment|/* #&bslash;s*d */
id|pound_d
suffix:colon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;e&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;f&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;i&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;n&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;e&squot;
comma
id|__start
)paren
suffix:semicolon
r_goto
id|pound_define_undef
suffix:semicolon
multiline_comment|/* #&bslash;s*u */
id|pound_u
suffix:colon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;n&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;d&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;e&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;f&squot;
comma
id|__start
)paren
suffix:semicolon
r_goto
id|pound_define_undef
suffix:semicolon
multiline_comment|/*&n; * #&bslash;s*(define|undef)&bslash;s*CONFIG_(&bslash;w*)&n; *&n; * this does not define the word, because it could be inside another&n; * conditional (#if 0).  But I do parse the word so that this instance&n; * does not count as a use.  -- mec&n; */
id|pound_define_undef
suffix:colon
id|GETNEXT
id|CASE
c_func
(paren
l_char|&squot; &squot;
comma
id|pound_define_undef
)paren
suffix:semicolon
id|CASE
c_func
(paren
l_char|&squot;&bslash;t&squot;
comma
id|pound_define_undef
)paren
suffix:semicolon
id|NOTCASE
c_func
(paren
l_char|&squot;C&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;O&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;N&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;F&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;I&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;G&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;_&squot;
comma
id|__start
)paren
suffix:semicolon
id|map_dot
op_assign
id|next
suffix:semicolon
id|pound_define_undef_CONFIG_word
suffix:colon
id|GETNEXT
r_if
c_cond
(paren
id|isalnum
c_func
(paren
id|current
)paren
op_logical_or
id|current
op_eq
l_char|&squot;_&squot;
)paren
r_goto
id|pound_define_undef_CONFIG_word
suffix:semicolon
r_goto
id|__start
suffix:semicolon
multiline_comment|/* &bslash;&lt;CONFIG_(&bslash;w*) */
id|cee
suffix:colon
r_if
c_cond
(paren
id|next
op_ge
id|map
op_plus
l_int|2
op_logical_and
(paren
id|isalnum
c_func
(paren
id|next
(braket
op_minus
l_int|2
)braket
)paren
op_logical_or
id|next
(braket
op_minus
l_int|2
)braket
op_eq
l_char|&squot;_&squot;
)paren
)paren
r_goto
id|start
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;O&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;N&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;F&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;I&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;G&squot;
comma
id|__start
)paren
suffix:semicolon
id|GETNEXT
id|NOTCASE
c_func
(paren
l_char|&squot;_&squot;
comma
id|__start
)paren
suffix:semicolon
id|map_dot
op_assign
id|next
suffix:semicolon
id|cee_CONFIG_word
suffix:colon
id|GETNEXT
r_if
c_cond
(paren
id|isalnum
c_func
(paren
id|current
)paren
op_logical_or
id|current
op_eq
l_char|&squot;_&squot;
)paren
r_goto
id|cee_CONFIG_word
suffix:semicolon
id|use_config
c_func
(paren
id|map_dot
comma
id|next
op_minus
id|map_dot
op_minus
l_int|1
)paren
suffix:semicolon
r_goto
id|__start
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Generate dependencies for one file.&n; */
DECL|function|do_depend
r_void
id|do_depend
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_const
r_char
op_star
id|command
)paren
(brace
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
suffix:semicolon
r_struct
id|stat
id|st
suffix:semicolon
r_char
op_star
id|map
suffix:semicolon
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
id|filename
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
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|mapsize
op_assign
id|st.st_size
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
(paren
r_int
)paren
id|map
op_eq
op_minus
l_int|1
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
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|map
op_mod
r_sizeof
(paren
r_int
r_int
)paren
op_ne
l_int|0
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;do_depend: map not aligned&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|hasdep
op_assign
l_int|0
suffix:semicolon
id|clear_config
c_func
(paren
)paren
suffix:semicolon
id|state_machine
c_func
(paren
id|map
comma
id|map
op_plus
id|st.st_size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hasdep
)paren
(brace
id|puts
c_func
(paren
id|command
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|command
)paren
id|define_precious
c_func
(paren
id|filename
)paren
suffix:semicolon
)brace
id|munmap
c_func
(paren
id|map
comma
id|mapsize
)paren
suffix:semicolon
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Generate dependencies for all files.&n; */
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
(brace
id|fputs
c_func
(paren
l_string|&quot;mkdep: HPATH not set in environment.  &quot;
l_string|&quot;Don&squot;t bypass the top level Makefile.&bslash;n&quot;
comma
id|stderr
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
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
id|path_array
(braket
l_int|0
)braket
dot
id|buffer
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;/&squot;
suffix:semicolon
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
r_const
r_char
op_star
id|filename
op_assign
op_star
op_increment
id|argv
suffix:semicolon
r_const
r_char
op_star
id|command
op_assign
id|__depname
suffix:semicolon
id|g_filename
op_assign
l_int|0
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|filename
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|depname
comma
id|filename
comma
id|len
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
l_int|2
op_logical_and
id|filename
(braket
id|len
op_minus
l_int|2
)braket
op_eq
l_char|&squot;.&squot;
)paren
(brace
r_if
c_cond
(paren
id|filename
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;c&squot;
op_logical_or
id|filename
(braket
id|len
op_minus
l_int|1
)braket
op_eq
l_char|&squot;S&squot;
)paren
(brace
id|depname
(braket
id|len
op_minus
l_int|1
)braket
op_assign
l_char|&squot;o&squot;
suffix:semicolon
id|g_filename
op_assign
id|filename
suffix:semicolon
id|command
op_assign
l_string|&quot;&quot;
suffix:semicolon
)brace
)brace
id|do_depend
c_func
(paren
id|filename
comma
id|command
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len_precious
)paren
(brace
op_star
(paren
id|str_precious
op_plus
id|len_precious
)paren
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;.PRECIOUS:%s&bslash;n&quot;
comma
id|str_precious
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
