multiline_comment|/*  devfs (Device FileSystem) utilities.&n;&n;    Copyright (C) 1999-2000  Richard Gooch&n;&n;    This library is free software; you can redistribute it and/or&n;    modify it under the terms of the GNU Library General Public&n;    License as published by the Free Software Foundation; either&n;    version 2 of the License, or (at your option) any later version.&n;&n;    This library is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n;    Library General Public License for more details.&n;&n;    You should have received a copy of the GNU Library General Public&n;    License along with this library; if not, write to the Free&n;    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n;    Richard Gooch may be reached by email at  rgooch@atnf.csiro.au&n;    The postal address is:&n;      Richard Gooch, c/o ATNF, P. O. Box 76, Epping, N.S.W., 2121, Australia.&n;&n;    ChangeLog&n;&n;    19991031   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Created.&n;    19991103   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Created &lt;_devfs_convert_name&gt; and supported SCSI and IDE CD-ROMs&n;    20000203   Richard Gooch &lt;rgooch@atnf.csiro.au&gt;&n;               Changed operations pointer type to void *.&n;*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
multiline_comment|/*  Private functions follow  */
DECL|function|_devfs_convert_name
r_static
r_void
id|__init
id|_devfs_convert_name
(paren
r_char
op_star
r_new
comma
r_const
r_char
op_star
id|old
comma
r_int
id|disc
)paren
multiline_comment|/*  [SUMMARY] Convert from an old style location-based name to new style.&n;    &lt;new&gt; The new name will be written here.&n;    &lt;old&gt; The old name.&n;    &lt;disc&gt; If true, disc partitioning information should be processed.&n;    [RETURNS] Nothing.&n;*/
(brace
r_int
id|host
comma
id|bus
comma
id|target
comma
id|lun
suffix:semicolon
r_char
op_star
id|ptr
suffix:semicolon
r_char
id|part
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/*  Decode &quot;c#b#t#u#&quot;  */
r_if
c_cond
(paren
id|old
(braket
l_int|0
)braket
op_ne
l_char|&squot;c&squot;
)paren
r_return
suffix:semicolon
id|host
op_assign
id|simple_strtol
(paren
id|old
op_plus
l_int|1
comma
op_amp
id|ptr
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
(braket
l_int|0
)braket
op_ne
l_char|&squot;b&squot;
)paren
r_return
suffix:semicolon
id|bus
op_assign
id|simple_strtol
(paren
id|ptr
op_plus
l_int|1
comma
op_amp
id|ptr
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
(braket
l_int|0
)braket
op_ne
l_char|&squot;t&squot;
)paren
r_return
suffix:semicolon
id|target
op_assign
id|simple_strtol
(paren
id|ptr
op_plus
l_int|1
comma
op_amp
id|ptr
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptr
(braket
l_int|0
)braket
op_ne
l_char|&squot;u&squot;
)paren
r_return
suffix:semicolon
id|lun
op_assign
id|simple_strtol
(paren
id|ptr
op_plus
l_int|1
comma
op_amp
id|ptr
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|disc
)paren
(brace
multiline_comment|/*  Decode &quot;p#&quot;  */
r_if
c_cond
(paren
id|ptr
(braket
l_int|0
)braket
op_eq
l_char|&squot;p&squot;
)paren
id|sprintf
(paren
id|part
comma
l_string|&quot;part%s&quot;
comma
id|ptr
op_plus
l_int|1
)paren
suffix:semicolon
r_else
id|strcpy
(paren
id|part
comma
l_string|&quot;disc&quot;
)paren
suffix:semicolon
)brace
r_else
id|part
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|sprintf
(paren
r_new
comma
l_string|&quot;/host%d/bus%d/target%d/lun%d/%s&quot;
comma
id|host
comma
id|bus
comma
id|target
comma
id|lun
comma
id|part
)paren
suffix:semicolon
)brace
multiline_comment|/*  End Function _devfs_convert_name  */
multiline_comment|/*  Public functions follow  */
multiline_comment|/*PUBLIC_FUNCTION*/
DECL|function|devfs_make_root
r_void
id|__init
id|devfs_make_root
(paren
r_const
r_char
op_star
id|name
)paren
multiline_comment|/*  [SUMMARY] Create the root FS device entry if required.&n;    &lt;name&gt; The name of the root FS device, as passed by &quot;root=&quot;.&n;    [RETURNS] Nothing.&n;*/
(brace
r_char
id|dest
(braket
l_int|64
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|strncmp
(paren
id|name
comma
l_string|&quot;sd/&quot;
comma
l_int|3
)paren
op_eq
l_int|0
)paren
op_logical_or
(paren
id|strncmp
(paren
id|name
comma
l_string|&quot;sr/&quot;
comma
l_int|3
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|strcpy
(paren
id|dest
comma
l_string|&quot;../scsi&quot;
)paren
suffix:semicolon
id|_devfs_convert_name
(paren
id|dest
op_plus
l_int|7
comma
id|name
op_plus
l_int|3
comma
(paren
id|name
(braket
l_int|1
)braket
op_eq
l_char|&squot;d&squot;
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|strncmp
(paren
id|name
comma
l_string|&quot;ide/hd/&quot;
comma
l_int|7
)paren
op_eq
l_int|0
)paren
op_logical_or
(paren
id|strncmp
(paren
id|name
comma
l_string|&quot;ide/cd/&quot;
comma
l_int|7
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|strcpy
(paren
id|dest
comma
l_string|&quot;..&quot;
)paren
suffix:semicolon
id|_devfs_convert_name
(paren
id|dest
op_plus
l_int|2
comma
id|name
op_plus
l_int|7
comma
(paren
id|name
(braket
l_int|4
)braket
op_eq
l_char|&squot;h&squot;
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
r_else
r_return
suffix:semicolon
id|devfs_mk_symlink
(paren
l_int|NULL
comma
id|name
comma
l_int|0
comma
id|DEVFS_FL_DEFAULT
comma
id|dest
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*  End Function devfs_make_root  */
multiline_comment|/*PUBLIC_FUNCTION*/
DECL|function|devfs_register_tape
r_void
id|devfs_register_tape
(paren
id|devfs_handle_t
id|de
)paren
multiline_comment|/*  [SUMMARY] Register a tape device in the &quot;/dev/tapes&quot; hierarchy.&n;    &lt;de&gt; Any tape device entry in the device directory.&n;    [RETURNS] Nothing.&n;*/
(brace
r_int
id|pos
suffix:semicolon
id|devfs_handle_t
id|parent
comma
id|slave
suffix:semicolon
r_char
id|name
(braket
l_int|16
)braket
comma
id|dest
(braket
l_int|64
)braket
suffix:semicolon
r_static
r_int
r_int
id|tape_counter
op_assign
l_int|0
suffix:semicolon
r_static
id|devfs_handle_t
id|tape_dir
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|tape_dir
op_eq
l_int|NULL
)paren
id|tape_dir
op_assign
id|devfs_mk_dir
(paren
l_int|NULL
comma
l_string|&quot;tapes&quot;
comma
l_int|5
comma
l_int|NULL
)paren
suffix:semicolon
id|parent
op_assign
id|devfs_get_parent
(paren
id|de
)paren
suffix:semicolon
id|pos
op_assign
id|devfs_generate_path
(paren
id|parent
comma
id|dest
op_plus
l_int|3
comma
r_sizeof
id|dest
op_minus
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
l_int|0
)paren
r_return
suffix:semicolon
id|strncpy
(paren
id|dest
op_plus
id|pos
comma
l_string|&quot;../&quot;
comma
l_int|3
)paren
suffix:semicolon
id|sprintf
(paren
id|name
comma
l_string|&quot;tape%u&quot;
comma
id|tape_counter
op_increment
)paren
suffix:semicolon
id|devfs_mk_symlink
(paren
id|tape_dir
comma
id|name
comma
l_int|0
comma
id|DEVFS_FL_DEFAULT
comma
id|dest
op_plus
id|pos
comma
l_int|0
comma
op_amp
id|slave
comma
l_int|NULL
)paren
suffix:semicolon
id|devfs_auto_unregister
(paren
id|de
comma
id|slave
)paren
suffix:semicolon
)brace
multiline_comment|/*  End Function devfs_register_tape  */
DECL|variable|devfs_register_tape
id|EXPORT_SYMBOL
c_func
(paren
id|devfs_register_tape
)paren
suffix:semicolon
multiline_comment|/*PUBLIC_FUNCTION*/
DECL|function|devfs_register_series
r_void
id|devfs_register_series
(paren
id|devfs_handle_t
id|dir
comma
r_const
r_char
op_star
id|format
comma
r_int
r_int
id|num_entries
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|major
comma
r_int
r_int
id|minor_start
comma
id|umode_t
id|mode
comma
id|uid_t
id|uid
comma
id|gid_t
id|gid
comma
r_void
op_star
id|ops
comma
r_void
op_star
id|info
)paren
multiline_comment|/*  [SUMMARY] Register a sequence of device entries.&n;    &lt;dir&gt; The handle to the parent devfs directory entry. If this is NULL the&n;    new names are relative to the root of the devfs.&n;    &lt;format&gt; The printf-style format string. A single &quot;%u&quot; is allowed.&n;    &lt;flags&gt; A set of bitwise-ORed flags (DEVFS_FL_*).&n;    &lt;major&gt; The major number. Not needed for regular files.&n;    &lt;minor_start&gt; The starting minor number. Not needed for regular files.&n;    &lt;mode&gt; The default file mode.&n;    &lt;uid&gt; The default UID of the file.&n;    &lt;guid&gt; The default GID of the file.&n;    &lt;ops&gt; The &lt;&lt;file_operations&gt;&gt; or &lt;&lt;block_device_operations&gt;&gt; structure.&n;    This must not be externally deallocated.&n;    &lt;info&gt; An arbitrary pointer which will be written to the &lt;&lt;private_data&gt;&gt;&n;    field of the &lt;&lt;file&gt;&gt; structure passed to the device driver. You can set&n;    this to whatever you like, and change it once the file is opened (the next&n;    file opened will not see this change).&n;    [RETURNS] Nothing.&n;*/
(brace
r_int
r_int
id|count
suffix:semicolon
r_char
id|devname
(braket
l_int|128
)braket
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
id|num_entries
suffix:semicolon
op_increment
id|count
)paren
(brace
id|sprintf
(paren
id|devname
comma
id|format
comma
id|count
)paren
suffix:semicolon
id|devfs_register
(paren
id|dir
comma
id|devname
comma
l_int|0
comma
id|flags
comma
id|major
comma
id|minor_start
op_plus
id|count
comma
id|mode
comma
id|uid
comma
id|gid
comma
id|ops
comma
id|info
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*  End Function devfs_register_series  */
DECL|variable|devfs_register_series
id|EXPORT_SYMBOL
c_func
(paren
id|devfs_register_series
)paren
suffix:semicolon
eof
