multiline_comment|/*&n; *  linux/tools/build.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
multiline_comment|/*&n; * This file builds a disk-image from three different files:&n; *&n; * - bootsect: exactly 512 bytes of 8086 machine code, loads the rest&n; * - setup: 8086 machine code, sets up system parm&n; * - system: 80386 code for actual system&n; *&n; * It does some checking that all files are of the correct type, and&n; * just writes the result to stdout, removing headers and padding to&n; * the right amount. It also writes some system data to stderr.&n; */
multiline_comment|/*&n; * Changes by tytso to allow root device specification&n; */
macro_line|#include &lt;stdio.h&gt;&t;/* fprintf */
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;stdlib.h&gt;&t;/* contains exit */
macro_line|#include &lt;sys/types.h&gt;&t;/* unistd.h needs this */
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;sys/sysmacros.h&gt;
macro_line|#include &lt;unistd.h&gt;&t;/* contains read/write */
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;errno.h&gt;
DECL|macro|MINIX_HEADER
mdefine_line|#define MINIX_HEADER 32
DECL|macro|N_MAGIC_OFFSET
mdefine_line|#define N_MAGIC_OFFSET 1024
macro_line|#ifndef __BFD__
DECL|variable|GCC_HEADER
r_static
r_int
id|GCC_HEADER
op_assign
r_sizeof
(paren
r_struct
id|exec
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|SYS_SIZE
mdefine_line|#define SYS_SIZE DEF_SYSSIZE
DECL|macro|DEFAULT_MAJOR_ROOT
mdefine_line|#define DEFAULT_MAJOR_ROOT 0
DECL|macro|DEFAULT_MINOR_ROOT
mdefine_line|#define DEFAULT_MINOR_ROOT 0
multiline_comment|/* max nr of sectors of setup: don&squot;t change unless you also change&n; * bootsect etc */
DECL|macro|SETUP_SECTS
mdefine_line|#define SETUP_SECTS 4
DECL|macro|STRINGIFY
mdefine_line|#define STRINGIFY(x) #x
r_typedef
r_union
(brace
DECL|member|l
r_int
id|l
suffix:semicolon
DECL|member|s
r_int
id|s
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|b
r_char
id|b
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|conv
)brace
id|conv
suffix:semicolon
DECL|function|intel_long
r_int
id|intel_long
c_func
(paren
r_int
id|l
)paren
(brace
id|conv
id|t
suffix:semicolon
id|t.b
(braket
l_int|0
)braket
op_assign
id|l
op_amp
l_int|0xff
suffix:semicolon
id|l
op_rshift_assign
l_int|8
suffix:semicolon
id|t.b
(braket
l_int|1
)braket
op_assign
id|l
op_amp
l_int|0xff
suffix:semicolon
id|l
op_rshift_assign
l_int|8
suffix:semicolon
id|t.b
(braket
l_int|2
)braket
op_assign
id|l
op_amp
l_int|0xff
suffix:semicolon
id|l
op_rshift_assign
l_int|8
suffix:semicolon
id|t.b
(braket
l_int|3
)braket
op_assign
id|l
op_amp
l_int|0xff
suffix:semicolon
id|l
op_rshift_assign
l_int|8
suffix:semicolon
r_return
id|t.l
suffix:semicolon
)brace
DECL|function|intel_short
r_int
id|intel_short
c_func
(paren
r_int
id|l
)paren
(brace
id|conv
id|t
suffix:semicolon
id|t.b
(braket
l_int|0
)braket
op_assign
id|l
op_amp
l_int|0xff
suffix:semicolon
id|l
op_rshift_assign
l_int|8
suffix:semicolon
id|t.b
(braket
l_int|1
)braket
op_assign
id|l
op_amp
l_int|0xff
suffix:semicolon
id|l
op_rshift_assign
l_int|8
suffix:semicolon
r_return
id|t.s
(braket
l_int|0
)braket
suffix:semicolon
)brace
DECL|function|die
r_void
id|die
c_func
(paren
r_const
r_char
op_star
id|str
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|str
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|usage
r_void
id|usage
c_func
(paren
r_void
)paren
(brace
id|die
c_func
(paren
l_string|&quot;Usage: build bootsect setup system [rootdev] [&gt; image]&quot;
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
id|i
comma
id|c
comma
id|id
comma
id|sz
suffix:semicolon
r_int
r_int
id|sys_size
suffix:semicolon
r_char
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
macro_line|#ifndef __BFD__
r_struct
id|exec
op_star
id|ex
op_assign
(paren
r_struct
id|exec
op_star
)paren
id|buf
suffix:semicolon
macro_line|#endif
r_char
id|major_root
comma
id|minor_root
suffix:semicolon
r_struct
id|stat
id|sb
suffix:semicolon
r_int
r_char
id|setup_sectors
suffix:semicolon
r_if
c_cond
(paren
(paren
id|argc
OL
l_int|4
)paren
op_logical_or
(paren
id|argc
OG
l_int|5
)paren
)paren
id|usage
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|4
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|4
)braket
comma
l_string|&quot;CURRENT&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|stat
c_func
(paren
l_string|&quot;/&quot;
comma
op_amp
id|sb
)paren
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;/&quot;
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Couldn&squot;t stat /&quot;
)paren
suffix:semicolon
)brace
id|major_root
op_assign
id|major
c_func
(paren
id|sb.st_dev
)paren
suffix:semicolon
id|minor_root
op_assign
id|minor
c_func
(paren
id|sb.st_dev
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|argv
(braket
l_int|4
)braket
comma
l_string|&quot;FLOPPY&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|stat
c_func
(paren
id|argv
(braket
l_int|4
)braket
comma
op_amp
id|sb
)paren
)paren
(brace
id|perror
c_func
(paren
id|argv
(braket
l_int|4
)braket
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Couldn&squot;t stat root device.&quot;
)paren
suffix:semicolon
)brace
id|major_root
op_assign
id|major
c_func
(paren
id|sb.st_rdev
)paren
suffix:semicolon
id|minor_root
op_assign
id|minor
c_func
(paren
id|sb.st_rdev
)paren
suffix:semicolon
)brace
r_else
(brace
id|major_root
op_assign
l_int|0
suffix:semicolon
id|minor_root
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|major_root
op_assign
id|DEFAULT_MAJOR_ROOT
suffix:semicolon
id|minor_root
op_assign
id|DEFAULT_MINOR_ROOT
suffix:semicolon
)brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Root device is (%d, %d)&bslash;n&quot;
comma
id|major_root
comma
id|minor_root
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
r_sizeof
id|buf
suffix:semicolon
id|i
op_increment
)paren
id|buf
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|id
op_assign
id|open
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
id|O_RDONLY
comma
l_int|0
)paren
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Unable to open &squot;boot&squot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read
c_func
(paren
id|id
comma
id|buf
comma
id|MINIX_HEADER
)paren
op_ne
id|MINIX_HEADER
)paren
id|die
c_func
(paren
l_string|&quot;Unable to read header of &squot;boot&squot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
op_star
)paren
id|buf
)paren
(braket
l_int|0
)braket
op_ne
id|intel_long
c_func
(paren
l_int|0x04100301
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Non-Minix header of &squot;boot&squot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
op_star
)paren
id|buf
)paren
(braket
l_int|1
)braket
op_ne
id|intel_long
c_func
(paren
id|MINIX_HEADER
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Non-Minix header of &squot;boot&squot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
op_star
)paren
id|buf
)paren
(braket
l_int|3
)braket
op_ne
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Illegal data segment in &squot;boot&squot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
op_star
)paren
id|buf
)paren
(braket
l_int|4
)braket
op_ne
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Illegal bss in &squot;boot&squot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
op_star
)paren
id|buf
)paren
(braket
l_int|5
)braket
op_ne
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Non-Minix header of &squot;boot&squot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
op_star
)paren
id|buf
)paren
(braket
l_int|7
)braket
op_ne
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Illegal symbol table in &squot;boot&squot;&quot;
)paren
suffix:semicolon
id|i
op_assign
id|read
c_func
(paren
id|id
comma
id|buf
comma
r_sizeof
id|buf
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Boot sector %d bytes.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
l_int|512
)paren
id|die
c_func
(paren
l_string|&quot;Boot block must be exactly 512 bytes&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|buf
op_plus
l_int|510
)paren
)paren
op_ne
(paren
r_int
r_int
)paren
id|intel_short
c_func
(paren
l_int|0xAA55
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Boot block hasn&squot;t got boot flag (0xAA55)&quot;
)paren
suffix:semicolon
id|buf
(braket
l_int|508
)braket
op_assign
(paren
r_char
)paren
id|minor_root
suffix:semicolon
id|buf
(braket
l_int|509
)braket
op_assign
(paren
r_char
)paren
id|major_root
suffix:semicolon
id|i
op_assign
id|write
c_func
(paren
l_int|1
comma
id|buf
comma
l_int|512
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
l_int|512
)paren
id|die
c_func
(paren
l_string|&quot;Write call failed&quot;
)paren
suffix:semicolon
id|close
(paren
id|id
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|id
op_assign
id|open
c_func
(paren
id|argv
(braket
l_int|2
)braket
comma
id|O_RDONLY
comma
l_int|0
)paren
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Unable to open &squot;setup&squot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read
c_func
(paren
id|id
comma
id|buf
comma
id|MINIX_HEADER
)paren
op_ne
id|MINIX_HEADER
)paren
id|die
c_func
(paren
l_string|&quot;Unable to read header of &squot;setup&squot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
op_star
)paren
id|buf
)paren
(braket
l_int|0
)braket
op_ne
id|intel_long
c_func
(paren
l_int|0x04100301
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Non-Minix header of &squot;setup&squot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
op_star
)paren
id|buf
)paren
(braket
l_int|1
)braket
op_ne
id|intel_long
c_func
(paren
id|MINIX_HEADER
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Non-Minix header of &squot;setup&squot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
op_star
)paren
id|buf
)paren
(braket
l_int|3
)braket
op_ne
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Illegal data segment in &squot;setup&squot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
op_star
)paren
id|buf
)paren
(braket
l_int|4
)braket
op_ne
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Illegal bss in &squot;setup&squot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
op_star
)paren
id|buf
)paren
(braket
l_int|5
)braket
op_ne
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Non-Minix header of &squot;setup&squot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
op_star
)paren
id|buf
)paren
(braket
l_int|7
)braket
op_ne
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Illegal symbol table in &squot;setup&squot;&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|c
op_assign
id|read
c_func
(paren
id|id
comma
id|buf
comma
r_sizeof
id|buf
)paren
)paren
OG
l_int|0
suffix:semicolon
id|i
op_add_assign
id|c
)paren
r_if
c_cond
(paren
id|write
c_func
(paren
l_int|1
comma
id|buf
comma
id|c
)paren
op_ne
id|c
)paren
id|die
c_func
(paren
l_string|&quot;Write call failed&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ne
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;read-error on &squot;setup&squot;&quot;
)paren
suffix:semicolon
id|close
(paren
id|id
)paren
suffix:semicolon
id|setup_sectors
op_assign
(paren
r_int
r_char
)paren
(paren
(paren
id|i
op_plus
l_int|511
)paren
op_div
l_int|512
)paren
suffix:semicolon
multiline_comment|/* for compatibility with LILO */
r_if
c_cond
(paren
id|setup_sectors
OL
id|SETUP_SECTS
)paren
id|setup_sectors
op_assign
id|SETUP_SECTS
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Setup is %d bytes.&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_for
c_loop
(paren
id|c
op_assign
l_int|0
suffix:semicolon
id|c
OL
r_sizeof
(paren
id|buf
)paren
suffix:semicolon
id|c
op_increment
)paren
id|buf
(braket
id|c
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|setup_sectors
op_star
l_int|512
)paren
(brace
id|c
op_assign
id|setup_sectors
op_star
l_int|512
op_minus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|c
OG
r_sizeof
(paren
id|buf
)paren
)paren
id|c
op_assign
r_sizeof
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
l_int|1
comma
id|buf
comma
id|c
)paren
op_ne
id|c
)paren
id|die
c_func
(paren
l_string|&quot;Write call failed&quot;
)paren
suffix:semicolon
id|i
op_add_assign
id|c
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|id
op_assign
id|open
c_func
(paren
id|argv
(braket
l_int|3
)braket
comma
id|O_RDONLY
comma
l_int|0
)paren
)paren
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Unable to open &squot;system&squot;&quot;
)paren
suffix:semicolon
macro_line|#ifndef __BFD__
r_if
c_cond
(paren
id|read
c_func
(paren
id|id
comma
id|buf
comma
id|GCC_HEADER
)paren
op_ne
id|GCC_HEADER
)paren
id|die
c_func
(paren
l_string|&quot;Unable to read header of &squot;system&squot;&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|N_MAGIC
c_func
(paren
op_star
id|ex
)paren
op_eq
id|ZMAGIC
)paren
(brace
id|GCC_HEADER
op_assign
id|N_MAGIC_OFFSET
suffix:semicolon
id|lseek
c_func
(paren
id|id
comma
id|GCC_HEADER
comma
id|SEEK_SET
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|N_MAGIC
c_func
(paren
op_star
id|ex
)paren
op_ne
id|QMAGIC
)paren
id|die
c_func
(paren
l_string|&quot;Non-GCC header of &squot;system&squot;&quot;
)paren
suffix:semicolon
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;System is %d kB (%d kB code, %d kB data and %d kB bss)&bslash;n&quot;
comma
(paren
id|ex-&gt;a_text
op_plus
id|ex-&gt;a_data
op_plus
id|ex-&gt;a_bss
)paren
op_div
l_int|1024
comma
id|ex-&gt;a_text
op_div
l_int|1024
comma
id|ex-&gt;a_data
op_div
l_int|1024
comma
id|ex-&gt;a_bss
op_div
l_int|1024
)paren
suffix:semicolon
id|sz
op_assign
id|N_SYMOFF
c_func
(paren
op_star
id|ex
)paren
op_minus
id|GCC_HEADER
op_plus
l_int|4
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|fstat
(paren
id|id
comma
op_amp
id|sb
)paren
)paren
(brace
id|perror
(paren
l_string|&quot;fstat&quot;
)paren
suffix:semicolon
id|die
(paren
l_string|&quot;Unable to stat &squot;system&squot;&quot;
)paren
suffix:semicolon
)brace
id|sz
op_assign
id|sb.st_size
suffix:semicolon
id|fprintf
(paren
id|stderr
comma
l_string|&quot;System is %d kB&bslash;n&quot;
comma
id|sz
op_div
l_int|1024
)paren
suffix:semicolon
macro_line|#endif
id|sys_size
op_assign
(paren
id|sz
op_plus
l_int|15
)paren
op_div
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|sys_size
OG
id|SYS_SIZE
)paren
id|die
c_func
(paren
l_string|&quot;System is too big&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|sz
OG
l_int|0
)paren
(brace
r_int
id|l
comma
id|n
suffix:semicolon
id|l
op_assign
id|sz
suffix:semicolon
r_if
c_cond
(paren
id|l
OG
r_sizeof
(paren
id|buf
)paren
)paren
id|l
op_assign
r_sizeof
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|n
op_assign
id|read
c_func
(paren
id|id
comma
id|buf
comma
id|l
)paren
)paren
op_ne
id|l
)paren
(brace
r_if
c_cond
(paren
id|n
op_eq
op_minus
l_int|1
)paren
id|perror
c_func
(paren
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_else
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Unexpected EOF&bslash;n&quot;
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Can&squot;t read &squot;system&squot;&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write
c_func
(paren
l_int|1
comma
id|buf
comma
id|l
)paren
op_ne
id|l
)paren
id|die
c_func
(paren
l_string|&quot;Write failed&quot;
)paren
suffix:semicolon
id|sz
op_sub_assign
id|l
suffix:semicolon
)brace
id|close
c_func
(paren
id|id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lseek
c_func
(paren
l_int|1
comma
l_int|497
comma
l_int|0
)paren
op_eq
l_int|497
)paren
(brace
r_if
c_cond
(paren
id|write
c_func
(paren
l_int|1
comma
op_amp
id|setup_sectors
comma
l_int|1
)paren
op_ne
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;Write of setup sectors failed&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lseek
c_func
(paren
l_int|1
comma
l_int|500
comma
l_int|0
)paren
op_eq
l_int|500
)paren
(brace
id|buf
(braket
l_int|0
)braket
op_assign
(paren
id|sys_size
op_amp
l_int|0xff
)paren
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
(paren
(paren
id|sys_size
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
c_func
(paren
l_int|1
comma
id|buf
comma
l_int|2
)paren
op_ne
l_int|2
)paren
id|die
c_func
(paren
l_string|&quot;Write failed&quot;
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof