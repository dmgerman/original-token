multiline_comment|/*&n; *  $Id: build.c,v 1.5 1997/05/19 12:29:58 mj Exp $&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *  Copyright (C) 1997 Martin Mares&n; */
multiline_comment|/*&n; * This file builds a disk-image from three different files:&n; *&n; * - bootsect: exactly 512 bytes of 8086 machine code, loads the rest&n; * - setup: 8086 machine code, sets up system parm&n; * - system: 80386 code for actual system&n; *&n; * It does some checking that all files are of the correct type, and&n; * just writes the result to stdout, removing headers and padding to&n; * the right amount. It also writes some system data to stderr.&n; */
multiline_comment|/*&n; * Changes by tytso to allow root device specification&n; * High loaded stuff by Hans Lermen &amp; Werner Almesberger, Feb. 1996&n; * Cross compiling fixes by Gertjan van Wingerde, July 1996&n; * Rewritten by Martin Mares, April 1997&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
macro_line|#include &lt;sys/sysmacros.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;asm/boot.h&gt;
DECL|typedef|byte
r_typedef
r_int
r_char
id|byte
suffix:semicolon
DECL|typedef|word
r_typedef
r_int
r_int
id|word
suffix:semicolon
DECL|typedef|u32
r_typedef
r_int
r_int
id|u32
suffix:semicolon
DECL|macro|DEFAULT_MAJOR_ROOT
mdefine_line|#define DEFAULT_MAJOR_ROOT 0
DECL|macro|DEFAULT_MINOR_ROOT
mdefine_line|#define DEFAULT_MINOR_ROOT 0
multiline_comment|/* Minimal number of setup sectors (see also bootsect.S) */
DECL|macro|SETUP_SECTS
mdefine_line|#define SETUP_SECTS 4
DECL|variable|buf
id|byte
id|buf
(braket
l_int|1024
)braket
suffix:semicolon
DECL|variable|fd
r_int
id|fd
suffix:semicolon
DECL|variable|is_big_kernel
r_int
id|is_big_kernel
suffix:semicolon
DECL|function|die
r_void
id|die
c_func
(paren
r_const
r_char
op_star
id|str
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|str
)paren
suffix:semicolon
id|vfprintf
c_func
(paren
id|stderr
comma
id|str
comma
id|args
)paren
suffix:semicolon
id|fputc
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
id|stderr
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|file_open
r_void
id|file_open
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_if
c_cond
(paren
(paren
id|fd
op_assign
id|open
c_func
(paren
id|name
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
l_string|&quot;Unable to open `%s&squot;: %m&quot;
comma
id|name
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
l_string|&quot;Usage: build [-b] bootsect setup system [rootdev] [&gt; image]&quot;
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
r_int
id|i
comma
id|c
comma
id|sz
comma
id|setup_sectors
suffix:semicolon
id|u32
id|sys_size
suffix:semicolon
id|byte
id|major_root
comma
id|minor_root
suffix:semicolon
r_struct
id|stat
id|sb
suffix:semicolon
r_if
c_cond
(paren
id|argc
OG
l_int|2
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|argv
(braket
l_int|1
)braket
comma
l_string|&quot;-b&quot;
)paren
)paren
(brace
id|is_big_kernel
op_assign
l_int|1
suffix:semicolon
id|argc
op_decrement
comma
id|argv
op_increment
suffix:semicolon
)brace
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
id|file_open
c_func
(paren
id|argv
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|i
op_assign
id|read
c_func
(paren
id|fd
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
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
id|buf
(braket
l_int|510
)braket
op_ne
l_int|0x55
op_logical_or
id|buf
(braket
l_int|511
)braket
op_ne
l_int|0xaa
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
id|minor_root
suffix:semicolon
id|buf
(braket
l_int|509
)braket
op_assign
id|major_root
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
l_int|512
)paren
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
id|fd
)paren
suffix:semicolon
id|file_open
c_func
(paren
id|argv
(braket
l_int|2
)braket
)paren
suffix:semicolon
multiline_comment|/* Copy the setup code */
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
id|fd
comma
id|buf
comma
r_sizeof
(paren
id|buf
)paren
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
l_string|&quot;read-error on `setup&squot;&quot;
)paren
suffix:semicolon
id|close
(paren
id|fd
)paren
suffix:semicolon
id|setup_sectors
op_assign
(paren
id|i
op_plus
l_int|511
)paren
op_div
l_int|512
suffix:semicolon
multiline_comment|/* Pad unused space with zeros */
multiline_comment|/* for compatibility with ancient versions of LILO. */
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
id|memset
c_func
(paren
id|buf
comma
l_int|0
comma
r_sizeof
(paren
id|buf
)paren
)paren
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
id|file_open
c_func
(paren
id|argv
(braket
l_int|3
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fstat
(paren
id|fd
comma
op_amp
id|sb
)paren
)paren
id|die
c_func
(paren
l_string|&quot;Unable to stat `%s&squot;: %m&quot;
comma
id|argv
(braket
l_int|3
)braket
)paren
suffix:semicolon
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
multiline_comment|/* 0x28000*16 = 2.5 MB, conservative estimate for the current maximum */
r_if
c_cond
(paren
id|sys_size
OG
(paren
id|is_big_kernel
ques
c_cond
l_int|0x28000
suffix:colon
id|DEF_SYSSIZE
)paren
)paren
id|die
c_func
(paren
l_string|&quot;System is too big. Try using %smodules.&quot;
comma
id|is_big_kernel
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;bzImage or &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sys_size
OG
l_int|0xffff
)paren
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;warning: kernel is too big for standalone boot &quot;
l_string|&quot;from floppy&bslash;n&quot;
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
(paren
id|sz
OG
r_sizeof
(paren
id|buf
)paren
)paren
ques
c_cond
r_sizeof
(paren
id|buf
)paren
suffix:colon
id|sz
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
id|fd
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
OL
l_int|0
)paren
id|die
c_func
(paren
l_string|&quot;Error reading %s: %m&quot;
comma
id|argv
(braket
l_int|3
)braket
)paren
suffix:semicolon
r_else
id|die
c_func
(paren
l_string|&quot;%s: Unexpected EOF&quot;
comma
id|argv
(braket
l_int|3
)braket
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
id|fd
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
id|SEEK_SET
)paren
op_ne
l_int|497
)paren
multiline_comment|/* Write sizes to the bootsector */
id|die
c_func
(paren
l_string|&quot;Output: seek failed&quot;
)paren
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
id|setup_sectors
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
l_int|1
)paren
op_ne
l_int|1
)paren
id|die
c_func
(paren
l_string|&quot;Write of setup sector count failed&quot;
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
l_int|500
comma
id|SEEK_SET
)paren
op_ne
l_int|500
)paren
id|die
c_func
(paren
l_string|&quot;Output: seek failed&quot;
)paren
suffix:semicolon
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
l_string|&quot;Write of image length failed&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Everything is OK */
)brace
eof
