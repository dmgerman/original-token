multiline_comment|/*&n; *  linux/fs/isofs/rock.c&n; *&n; *  (C) 1992, 1993  Eric Youngdale&n; *&n; *  Rock Ridge Extensions to iso9660&n; */
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/iso_fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &quot;rock.h&quot;
multiline_comment|/* These functions are designed to read the system areas of a directory record&n; * and extract relevant information.  There are different functions provided&n; * depending upon what information we need at the time.  One function fills&n; * out an inode structure, a second one extracts a filename, a third one&n; * returns a symbolic link name, and a fourth one returns the extent number&n; * for the file. */
DECL|macro|SIG
mdefine_line|#define SIG(A,B) ((A &lt;&lt; 8) | B)
multiline_comment|/* This is a way of ensuring that we have something in the system&n;   use fields that is compatible with Rock Ridge */
DECL|macro|CHECK_SP
mdefine_line|#define CHECK_SP(FAIL)&t;       &t;&t;&t;&bslash;&n;      if(rr-&gt;u.SP.magic[0] != 0xbe) FAIL;&t;&bslash;&n;      if(rr-&gt;u.SP.magic[1] != 0xef) FAIL;
multiline_comment|/* We define a series of macros because each function must do exactly the&n;   same thing in certain places.  We use the macros to ensure that everything&n;   is done correctly */
DECL|macro|CONTINUE_DECLS
mdefine_line|#define CONTINUE_DECLS &bslash;&n;  int cont_extent = 0, cont_offset = 0, cont_size = 0;   &bslash;&n;  void * buffer = 0
DECL|macro|CHECK_CE
mdefine_line|#define CHECK_CE&t;       &t;&t;&t;&bslash;&n;      {cont_extent = isonum_733(rr-&gt;u.CE.extent); &bslash;&n;      cont_offset = isonum_733(rr-&gt;u.CE.offset); &bslash;&n;      cont_size = isonum_733(rr-&gt;u.CE.size);}
DECL|macro|SETUP_ROCK_RIDGE
mdefine_line|#define SETUP_ROCK_RIDGE(DE,CHR,LEN)&t;      &t;&t;      &t;&bslash;&n;  {LEN= sizeof(struct iso_directory_record) + DE-&gt;name_len[0];&t;&bslash;&n;  if(LEN &amp; 1) LEN++;&t;&t;&t;&t;&t;&t;&bslash;&n;  CHR = ((unsigned char *) DE) + LEN;&t;&t;&t;&t;&bslash;&n;  LEN = *((unsigned char *) DE) - LEN;}
DECL|macro|MAYBE_CONTINUE
mdefine_line|#define MAYBE_CONTINUE(LABEL,DEV) &bslash;&n;  {if (buffer) kfree(buffer); &bslash;&n;  if (cont_extent){ &bslash;&n;    int block, offset, offset1; &bslash;&n;    struct buffer_head * pbh; &bslash;&n;    buffer = kmalloc(cont_size,GFP_KERNEL); &bslash;&n;    if (!buffer) goto out; &bslash;&n;    block = cont_extent; &bslash;&n;    offset = cont_offset; &bslash;&n;    offset1 = 0; &bslash;&n;    pbh = bread(DEV-&gt;i_dev, block, ISOFS_BUFFER_SIZE(DEV)); &bslash;&n;    if(pbh){       &bslash;&n;      memcpy(buffer + offset1, pbh-&gt;b_data + offset, cont_size - offset1); &bslash;&n;      brelse(pbh); &bslash;&n;      chr = (unsigned char *) buffer; &bslash;&n;      len = cont_size; &bslash;&n;      cont_extent = 0; &bslash;&n;      cont_size = 0; &bslash;&n;      cont_offset = 0; &bslash;&n;      goto LABEL; &bslash;&n;    };    &bslash;&n;    printk(&quot;Unable to read rock-ridge attributes&bslash;n&quot;);    &bslash;&n;  }}
multiline_comment|/* This is the inner layer of the get filename routine, and is called&n;   for each system area and continuation record related to the file */
DECL|function|find_rock_ridge_relocation
r_int
id|find_rock_ridge_relocation
c_func
(paren
r_struct
id|iso_directory_record
op_star
id|de
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|flag
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_int
r_char
op_star
id|chr
suffix:semicolon
id|CONTINUE_DECLS
suffix:semicolon
id|flag
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* If this is a &squot;..&squot; then we are looking for the parent, otherwise we&n;     are looking for the child */
r_if
c_cond
(paren
id|de-&gt;name
(braket
l_int|0
)braket
op_eq
l_int|1
op_logical_and
id|de-&gt;name_len
(braket
l_int|0
)braket
op_eq
l_int|1
)paren
id|flag
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Return value if we do not find appropriate record. */
id|retval
op_assign
id|isonum_733
(paren
id|de-&gt;extent
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_sb-&gt;u.isofs_sb.s_rock
)paren
r_return
id|retval
suffix:semicolon
id|SETUP_ROCK_RIDGE
c_func
(paren
id|de
comma
id|chr
comma
id|len
)paren
suffix:semicolon
id|repeat
suffix:colon
(brace
r_int
id|rrflag
comma
id|sig
suffix:semicolon
r_struct
id|rock_ridge
op_star
id|rr
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|1
)paren
(brace
multiline_comment|/* There may be one byte for padding somewhere */
id|rr
op_assign
(paren
r_struct
id|rock_ridge
op_star
)paren
id|chr
suffix:semicolon
r_if
c_cond
(paren
id|rr-&gt;len
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Something got screwed up here */
id|sig
op_assign
(paren
id|chr
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
op_plus
id|chr
(braket
l_int|1
)braket
suffix:semicolon
id|chr
op_add_assign
id|rr-&gt;len
suffix:semicolon
id|len
op_sub_assign
id|rr-&gt;len
suffix:semicolon
r_switch
c_cond
(paren
id|sig
)paren
(brace
r_case
id|SIG
c_func
(paren
l_char|&squot;R&squot;
comma
l_char|&squot;R&squot;
)paren
suffix:colon
id|rrflag
op_assign
id|rr-&gt;u.RR.flags
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
id|flag
op_logical_and
op_logical_neg
(paren
id|rrflag
op_amp
id|RR_PL
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|flag
op_logical_and
op_logical_neg
(paren
id|rrflag
op_amp
id|RR_CL
)paren
)paren
r_goto
id|out
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIG
c_func
(paren
l_char|&squot;S&squot;
comma
l_char|&squot;P&squot;
)paren
suffix:colon
id|CHECK_SP
c_func
(paren
r_goto
id|out
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIG
c_func
(paren
l_char|&squot;C&squot;
comma
l_char|&squot;L&squot;
)paren
suffix:colon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;RR: CL&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|flag
op_eq
l_int|0
)paren
(brace
id|retval
op_assign
id|isonum_733
c_func
(paren
id|rr-&gt;u.CL.location
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIG
c_func
(paren
l_char|&squot;P&squot;
comma
l_char|&squot;L&squot;
)paren
suffix:colon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;RR: PL&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|flag
op_ne
l_int|0
)paren
(brace
id|retval
op_assign
id|isonum_733
c_func
(paren
id|rr-&gt;u.PL.location
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIG
c_func
(paren
l_char|&squot;C&squot;
comma
l_char|&squot;E&squot;
)paren
suffix:colon
id|CHECK_CE
suffix:semicolon
multiline_comment|/* This tells is if there is a continuation record */
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
suffix:semicolon
)brace
suffix:semicolon
id|MAYBE_CONTINUE
c_func
(paren
id|repeat
comma
id|inode
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|buffer
)paren
(brace
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
DECL|function|get_rock_ridge_filename
r_int
id|get_rock_ridge_filename
c_func
(paren
r_struct
id|iso_directory_record
op_star
id|de
comma
r_char
op_star
id|retname
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|len
suffix:semicolon
r_int
r_char
op_star
id|chr
suffix:semicolon
id|CONTINUE_DECLS
suffix:semicolon
r_int
id|retnamlen
op_assign
l_int|0
comma
id|truncate
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_sb-&gt;u.isofs_sb.s_rock
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|retname
op_assign
l_int|0
suffix:semicolon
id|SETUP_ROCK_RIDGE
c_func
(paren
id|de
comma
id|chr
comma
id|len
)paren
suffix:semicolon
id|repeat
suffix:colon
(brace
r_struct
id|rock_ridge
op_star
id|rr
suffix:semicolon
r_int
id|sig
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|1
)paren
(brace
multiline_comment|/* There may be one byte for padding somewhere */
id|rr
op_assign
(paren
r_struct
id|rock_ridge
op_star
)paren
id|chr
suffix:semicolon
r_if
c_cond
(paren
id|rr-&gt;len
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Something got screwed up here */
id|sig
op_assign
(paren
id|chr
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
op_plus
id|chr
(braket
l_int|1
)braket
suffix:semicolon
id|chr
op_add_assign
id|rr-&gt;len
suffix:semicolon
id|len
op_sub_assign
id|rr-&gt;len
suffix:semicolon
r_switch
c_cond
(paren
id|sig
)paren
(brace
r_case
id|SIG
c_func
(paren
l_char|&squot;R&squot;
comma
l_char|&squot;R&squot;
)paren
suffix:colon
r_if
c_cond
(paren
(paren
id|rr-&gt;u.RR.flags
(braket
l_int|0
)braket
op_amp
id|RR_NM
)paren
op_eq
l_int|0
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SIG
c_func
(paren
l_char|&squot;S&squot;
comma
l_char|&squot;P&squot;
)paren
suffix:colon
id|CHECK_SP
c_func
(paren
r_goto
id|out
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIG
c_func
(paren
l_char|&squot;C&squot;
comma
l_char|&squot;E&squot;
)paren
suffix:colon
id|CHECK_CE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIG
c_func
(paren
l_char|&squot;N&squot;
comma
l_char|&squot;M&squot;
)paren
suffix:colon
r_if
c_cond
(paren
id|truncate
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t; * If the flags are 2 or 4, this indicates &squot;.&squot; or &squot;..&squot;.&n;&t; * We don&squot;t want to do anything with this, because it&n;&t; * screws up the code that calls us.  We don&squot;t really&n;&t; * care anyways, since we can just use the non-RR&n;&t; * name.&n;&t; */
r_if
c_cond
(paren
id|rr-&gt;u.NM.flags
op_amp
l_int|6
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rr-&gt;u.NM.flags
op_amp
op_complement
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unsupported NM flag settings (%d)&bslash;n&quot;
comma
id|rr-&gt;u.NM.flags
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
(paren
id|strlen
c_func
(paren
id|retname
)paren
op_plus
id|rr-&gt;len
op_minus
l_int|5
)paren
op_ge
l_int|254
)paren
(brace
id|truncate
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
id|strncat
c_func
(paren
id|retname
comma
id|rr-&gt;u.NM.name
comma
id|rr-&gt;len
op_minus
l_int|5
)paren
suffix:semicolon
id|retnamlen
op_add_assign
id|rr-&gt;len
op_minus
l_int|5
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIG
c_func
(paren
l_char|&squot;R&squot;
comma
l_char|&squot;E&squot;
)paren
suffix:colon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;RR: RE (%x)&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|buffer
)paren
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
suffix:semicolon
)brace
id|MAYBE_CONTINUE
c_func
(paren
id|repeat
comma
id|inode
)paren
suffix:semicolon
r_return
id|retnamlen
suffix:semicolon
multiline_comment|/* If 0, this file did not have a NM field */
id|out
suffix:colon
r_if
c_cond
(paren
id|buffer
)paren
(brace
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parse_rock_ridge_inode
r_int
(def_block
id|parse_rock_ridge_inode
c_func
(paren
r_struct
id|iso_directory_record
op_star
id|de
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|len
suffix:semicolon
r_int
r_char
op_star
id|chr
suffix:semicolon
r_int
id|symlink_len
op_assign
l_int|0
suffix:semicolon
id|CONTINUE_DECLS
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_sb-&gt;u.isofs_sb.s_rock
)paren
r_return
l_int|0
suffix:semicolon
id|SETUP_ROCK_RIDGE
c_func
(paren
id|de
comma
id|chr
comma
id|len
)paren
suffix:semicolon
id|repeat
suffix:colon
(brace
r_int
id|cnt
comma
id|sig
suffix:semicolon
r_struct
id|inode
op_star
id|reloc
suffix:semicolon
r_struct
id|rock_ridge
op_star
id|rr
suffix:semicolon
r_int
id|rootflag
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|1
)paren
(brace
multiline_comment|/* There may be one byte for padding somewhere */
id|rr
op_assign
(paren
r_struct
id|rock_ridge
op_star
)paren
id|chr
suffix:semicolon
r_if
c_cond
(paren
id|rr-&gt;len
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Something got screwed up here */
id|sig
op_assign
(paren
id|chr
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
op_plus
id|chr
(braket
l_int|1
)braket
suffix:semicolon
id|chr
op_add_assign
id|rr-&gt;len
suffix:semicolon
id|len
op_sub_assign
id|rr-&gt;len
suffix:semicolon
r_switch
c_cond
(paren
id|sig
)paren
(brace
r_case
id|SIG
c_func
(paren
l_char|&squot;R&squot;
comma
l_char|&squot;R&squot;
)paren
suffix:colon
r_if
c_cond
(paren
(paren
id|rr-&gt;u.RR.flags
(braket
l_int|0
)braket
op_amp
(paren
id|RR_PX
op_or
id|RR_TF
op_or
id|RR_SL
op_or
id|RR_CL
)paren
)paren
op_eq
l_int|0
)paren
(brace
r_goto
id|out
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SIG
c_func
(paren
l_char|&squot;S&squot;
comma
l_char|&squot;P&squot;
)paren
suffix:colon
id|CHECK_SP
c_func
(paren
r_goto
id|out
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIG
c_func
(paren
l_char|&squot;C&squot;
comma
l_char|&squot;E&squot;
)paren
suffix:colon
id|CHECK_CE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIG
c_func
(paren
l_char|&squot;E&squot;
comma
l_char|&squot;R&squot;
)paren
suffix:colon
id|inode-&gt;i_sb-&gt;u.isofs_sb.s_rock
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ISO 9660 Extensions: &quot;
)paren
suffix:semicolon
(brace
r_int
id|p
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
l_int|0
suffix:semicolon
id|p
OL
id|rr-&gt;u.ER.len_id
suffix:semicolon
id|p
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%c&quot;
comma
id|rr-&gt;u.ER.data
(braket
id|p
)braket
)paren
suffix:semicolon
)brace
)brace
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIG
c_func
(paren
l_char|&squot;P&squot;
comma
l_char|&squot;X&squot;
)paren
suffix:colon
id|inode-&gt;i_mode
op_assign
id|isonum_733
c_func
(paren
id|rr-&gt;u.PX.mode
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|isonum_733
c_func
(paren
id|rr-&gt;u.PX.n_links
)paren
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|isonum_733
c_func
(paren
id|rr-&gt;u.PX.uid
)paren
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|isonum_733
c_func
(paren
id|rr-&gt;u.PX.gid
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIG
c_func
(paren
l_char|&squot;P&squot;
comma
l_char|&squot;N&squot;
)paren
suffix:colon
(brace
r_int
id|high
comma
id|low
suffix:semicolon
id|high
op_assign
id|isonum_733
c_func
(paren
id|rr-&gt;u.PN.dev_high
)paren
suffix:semicolon
id|low
op_assign
id|isonum_733
c_func
(paren
id|rr-&gt;u.PN.dev_low
)paren
suffix:semicolon
multiline_comment|/*&n;&t;   * The Rock Ridge standard specifies that if sizeof(dev_t) &lt;= 4,&n;&t;   * then the high field is unused, and the device number is completely&n;&t;   * stored in the low field.  Some writers may ignore this subtlety,&n;&t;   * and as a result we test to see if the entire device number is&n;&t;   * stored in the low field, and use that.&n;&t;   */
r_if
c_cond
(paren
(paren
id|low
op_amp
op_complement
l_int|0xff
)paren
op_logical_and
id|high
op_eq
l_int|0
)paren
(brace
id|inode-&gt;i_rdev
op_assign
id|MKDEV
c_func
(paren
id|low
op_rshift
l_int|8
comma
id|low
op_amp
l_int|0xff
)paren
suffix:semicolon
)brace
r_else
(brace
id|inode-&gt;i_rdev
op_assign
id|MKDEV
c_func
(paren
id|high
comma
id|low
)paren
suffix:semicolon
)brace
)brace
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIG
c_func
(paren
l_char|&squot;T&squot;
comma
l_char|&squot;F&squot;
)paren
suffix:colon
multiline_comment|/* Some RRIP writers incorrectly place ctime in the TF_CREATE field.&n;&t;   Try to handle this correctly for either case. */
id|cnt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Rock ridge never appears on a High Sierra disk */
r_if
c_cond
(paren
id|rr-&gt;u.TF.flags
op_amp
id|TF_CREATE
)paren
(brace
id|inode-&gt;i_ctime
op_assign
id|iso_date
c_func
(paren
id|rr-&gt;u.TF.times
(braket
id|cnt
op_increment
)braket
dot
id|time
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rr-&gt;u.TF.flags
op_amp
id|TF_MODIFY
)paren
(brace
id|inode-&gt;i_mtime
op_assign
id|iso_date
c_func
(paren
id|rr-&gt;u.TF.times
(braket
id|cnt
op_increment
)braket
dot
id|time
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rr-&gt;u.TF.flags
op_amp
id|TF_ACCESS
)paren
(brace
id|inode-&gt;i_atime
op_assign
id|iso_date
c_func
(paren
id|rr-&gt;u.TF.times
(braket
id|cnt
op_increment
)braket
dot
id|time
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rr-&gt;u.TF.flags
op_amp
id|TF_ATTRIBUTES
)paren
(brace
id|inode-&gt;i_ctime
op_assign
id|iso_date
c_func
(paren
id|rr-&gt;u.TF.times
(braket
id|cnt
op_increment
)braket
dot
id|time
comma
l_int|0
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SIG
c_func
(paren
l_char|&squot;S&squot;
comma
l_char|&squot;L&squot;
)paren
suffix:colon
(brace
r_int
id|slen
suffix:semicolon
r_struct
id|SL_component
op_star
id|slp
suffix:semicolon
r_struct
id|SL_component
op_star
id|oldslp
suffix:semicolon
id|slen
op_assign
id|rr-&gt;len
op_minus
l_int|5
suffix:semicolon
id|slp
op_assign
op_amp
id|rr-&gt;u.SL.link
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|symlink_len
suffix:semicolon
r_while
c_loop
(paren
id|slen
OG
l_int|1
)paren
(brace
id|rootflag
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|slp-&gt;flags
op_amp
op_complement
l_int|1
)paren
(brace
r_case
l_int|0
suffix:colon
id|inode-&gt;i_size
op_add_assign
id|slp-&gt;len
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|inode-&gt;i_size
op_add_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|inode-&gt;i_size
op_add_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|rootflag
op_assign
l_int|1
suffix:semicolon
id|inode-&gt;i_size
op_add_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Symlink component flag not implemented&bslash;n&quot;
)paren
suffix:semicolon
)brace
suffix:semicolon
id|slen
op_sub_assign
id|slp-&gt;len
op_plus
l_int|2
suffix:semicolon
id|oldslp
op_assign
id|slp
suffix:semicolon
id|slp
op_assign
(paren
r_struct
id|SL_component
op_star
)paren
(paren
(paren
(paren
r_char
op_star
)paren
id|slp
)paren
op_plus
id|slp-&gt;len
op_plus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slen
OL
l_int|2
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|rr-&gt;u.SL.flags
op_amp
l_int|1
)paren
op_ne
l_int|0
)paren
op_logical_and
(paren
(paren
id|oldslp-&gt;flags
op_amp
l_int|1
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|inode-&gt;i_size
op_add_assign
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;    * If this component record isn&squot;t continued, then append a &squot;/&squot;.&n;&t;    */
r_if
c_cond
(paren
(paren
op_logical_neg
id|rootflag
)paren
op_logical_and
(paren
(paren
id|oldslp-&gt;flags
op_amp
l_int|1
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|inode-&gt;i_size
op_add_assign
l_int|1
suffix:semicolon
)brace
)brace
)brace
id|symlink_len
op_assign
id|inode-&gt;i_size
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIG
c_func
(paren
l_char|&squot;R&squot;
comma
l_char|&squot;E&squot;
)paren
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Attempt to read inode for relocated directory&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
r_case
id|SIG
c_func
(paren
l_char|&squot;C&squot;
comma
l_char|&squot;L&squot;
)paren
suffix:colon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;RR CL (%x)&bslash;n&quot;
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
macro_line|#endif
id|inode-&gt;u.isofs_i.i_first_extent
op_assign
id|isonum_733
c_func
(paren
id|rr-&gt;u.CL.location
)paren
suffix:semicolon
id|reloc
op_assign
id|iget
c_func
(paren
id|inode-&gt;i_sb
comma
(paren
id|inode-&gt;u.isofs_i.i_first_extent
op_lshift
id|inode
op_member_access_from_pointer
id|i_sb
op_member_access_from_pointer
id|u.isofs_sb.s_log_zone_size
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|reloc
)paren
r_goto
id|out
suffix:semicolon
id|inode-&gt;i_mode
op_assign
id|reloc-&gt;i_mode
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
id|reloc-&gt;i_nlink
suffix:semicolon
id|inode-&gt;i_uid
op_assign
id|reloc-&gt;i_uid
suffix:semicolon
id|inode-&gt;i_gid
op_assign
id|reloc-&gt;i_gid
suffix:semicolon
id|inode-&gt;i_rdev
op_assign
id|reloc-&gt;i_rdev
suffix:semicolon
id|inode-&gt;i_size
op_assign
id|reloc-&gt;i_size
suffix:semicolon
id|inode-&gt;i_atime
op_assign
id|reloc-&gt;i_atime
suffix:semicolon
id|inode-&gt;i_ctime
op_assign
id|reloc-&gt;i_ctime
suffix:semicolon
id|inode-&gt;i_mtime
op_assign
id|reloc-&gt;i_mtime
suffix:semicolon
id|iput
c_func
(paren
id|reloc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
suffix:semicolon
)brace
id|MAYBE_CONTINUE
c_func
(paren
id|repeat
comma
id|inode
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out
suffix:colon
r_if
c_cond
(paren
id|buffer
)paren
(brace
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
)def_block
DECL|function|get_symlink_chunk
r_static
r_char
op_star
id|get_symlink_chunk
c_func
(paren
r_char
op_star
id|rpnt
comma
r_struct
id|rock_ridge
op_star
id|rr
)paren
(brace
r_int
id|slen
suffix:semicolon
r_int
id|rootflag
suffix:semicolon
r_struct
id|SL_component
op_star
id|oldslp
suffix:semicolon
r_struct
id|SL_component
op_star
id|slp
suffix:semicolon
id|slen
op_assign
id|rr-&gt;len
op_minus
l_int|5
suffix:semicolon
id|slp
op_assign
op_amp
id|rr-&gt;u.SL.link
suffix:semicolon
r_while
c_loop
(paren
id|slen
OG
l_int|1
)paren
(brace
id|rootflag
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|slp-&gt;flags
op_amp
op_complement
l_int|1
)paren
(brace
r_case
l_int|0
suffix:colon
id|memcpy
c_func
(paren
id|rpnt
comma
id|slp-&gt;text
comma
id|slp-&gt;len
)paren
suffix:semicolon
id|rpnt
op_add_assign
id|slp-&gt;len
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
op_star
id|rpnt
op_increment
op_assign
l_char|&squot;.&squot;
suffix:semicolon
multiline_comment|/* fallthru */
r_case
l_int|2
suffix:colon
op_star
id|rpnt
op_increment
op_assign
l_char|&squot;.&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|rootflag
op_assign
l_int|1
suffix:semicolon
op_star
id|rpnt
op_increment
op_assign
l_char|&squot;/&squot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Symlink component flag not implemented (%d)&bslash;n&quot;
comma
id|slp-&gt;flags
)paren
suffix:semicolon
)brace
id|slen
op_sub_assign
id|slp-&gt;len
op_plus
l_int|2
suffix:semicolon
id|oldslp
op_assign
id|slp
suffix:semicolon
id|slp
op_assign
(paren
r_struct
id|SL_component
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|slp
op_plus
id|slp-&gt;len
op_plus
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|slen
OL
l_int|2
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * If there is another SL record, and this component&n;&t;&t;&t; * record isn&squot;t continued, then add a slash.&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|rr-&gt;u.SL.flags
op_amp
l_int|1
)paren
op_logical_and
op_logical_neg
(paren
id|oldslp-&gt;flags
op_amp
l_int|1
)paren
)paren
op_star
id|rpnt
op_increment
op_assign
l_char|&squot;/&squot;
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * If this component record isn&squot;t continued, then append a &squot;/&squot;.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|rootflag
op_logical_and
op_logical_neg
(paren
id|oldslp-&gt;flags
op_amp
l_int|1
)paren
)paren
op_star
id|rpnt
op_increment
op_assign
l_char|&squot;/&squot;
suffix:semicolon
)brace
r_return
id|rpnt
suffix:semicolon
)brace
multiline_comment|/* readpage() for symlinks: reads symlink contents into the page and either&n;   makes it uptodate and returns 0 or returns error (-EIO) */
DECL|function|rock_ridge_symlink_readpage
r_int
id|rock_ridge_symlink_readpage
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_char
op_star
id|link
op_assign
(paren
r_char
op_star
)paren
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
r_int
r_int
id|bufsize
op_assign
id|ISOFS_BUFFER_SIZE
c_func
(paren
id|inode
)paren
suffix:semicolon
r_int
r_char
id|bufbits
op_assign
id|ISOFS_BUFFER_BITS
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_char
op_star
id|rpnt
op_assign
id|link
suffix:semicolon
r_int
r_char
op_star
id|pnt
suffix:semicolon
r_struct
id|iso_directory_record
op_star
id|raw_inode
suffix:semicolon
id|CONTINUE_DECLS
suffix:semicolon
r_int
id|block
suffix:semicolon
r_int
id|sig
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
r_char
op_star
id|chr
suffix:semicolon
r_struct
id|rock_ridge
op_star
id|rr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_sb-&gt;u.isofs_sb.s_rock
)paren
id|panic
(paren
l_string|&quot;Cannot have symlink with high sierra variant of iso filesystem&bslash;n&quot;
)paren
suffix:semicolon
id|block
op_assign
id|inode-&gt;i_ino
op_rshift
id|bufbits
suffix:semicolon
id|bh
op_assign
id|bread
c_func
(paren
id|inode-&gt;i_dev
comma
id|block
comma
id|bufsize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_goto
id|out_noread
suffix:semicolon
id|pnt
op_assign
(paren
r_int
r_char
op_star
)paren
id|bh-&gt;b_data
op_plus
(paren
id|inode-&gt;i_ino
op_amp
(paren
id|bufsize
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|raw_inode
op_assign
(paren
r_struct
id|iso_directory_record
op_star
)paren
id|pnt
suffix:semicolon
multiline_comment|/*&n;&t; * If we go past the end of the buffer, there is some sort of error.&n;&t; */
r_if
c_cond
(paren
(paren
id|inode-&gt;i_ino
op_amp
(paren
id|bufsize
op_minus
l_int|1
)paren
)paren
op_plus
op_star
id|pnt
OG
id|bufsize
)paren
r_goto
id|out_bad_span
suffix:semicolon
multiline_comment|/* Now test for possible Rock Ridge extensions which will override&n;&t;   some of these numbers in the inode structure. */
id|SETUP_ROCK_RIDGE
c_func
(paren
id|raw_inode
comma
id|chr
comma
id|len
)paren
suffix:semicolon
id|repeat
suffix:colon
r_while
c_loop
(paren
id|len
OG
l_int|1
)paren
(brace
multiline_comment|/* There may be one byte for padding somewhere */
id|rr
op_assign
(paren
r_struct
id|rock_ridge
op_star
)paren
id|chr
suffix:semicolon
r_if
c_cond
(paren
id|rr-&gt;len
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Something got screwed up here */
id|sig
op_assign
(paren
id|chr
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
op_plus
id|chr
(braket
l_int|1
)braket
suffix:semicolon
id|chr
op_add_assign
id|rr-&gt;len
suffix:semicolon
id|len
op_sub_assign
id|rr-&gt;len
suffix:semicolon
r_switch
c_cond
(paren
id|sig
)paren
(brace
r_case
id|SIG
c_func
(paren
l_char|&squot;R&squot;
comma
l_char|&squot;R&squot;
)paren
suffix:colon
r_if
c_cond
(paren
(paren
id|rr-&gt;u.RR.flags
(braket
l_int|0
)braket
op_amp
id|RR_SL
)paren
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIG
c_func
(paren
l_char|&squot;S&squot;
comma
l_char|&squot;P&squot;
)paren
suffix:colon
id|CHECK_SP
c_func
(paren
r_goto
id|out
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIG
c_func
(paren
l_char|&squot;S&squot;
comma
l_char|&squot;L&squot;
)paren
suffix:colon
id|rpnt
op_assign
id|get_symlink_chunk
c_func
(paren
id|rpnt
comma
id|rr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIG
c_func
(paren
l_char|&squot;C&squot;
comma
l_char|&squot;E&squot;
)paren
suffix:colon
multiline_comment|/* This tells is if there is a continuation record */
id|CHECK_CE
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
id|MAYBE_CONTINUE
c_func
(paren
id|repeat
comma
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rpnt
op_eq
id|link
)paren
r_goto
id|fail
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
op_star
id|rpnt
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* error exit from macro */
id|out
suffix:colon
r_if
c_cond
(paren
id|buffer
)paren
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
id|out_noread
suffix:colon
id|printk
c_func
(paren
l_string|&quot;unable to read i-node block&quot;
)paren
suffix:semicolon
r_goto
id|fail
suffix:semicolon
id|out_bad_span
suffix:colon
id|printk
c_func
(paren
l_string|&quot;symlink spans iso9660 blocks&bslash;n&quot;
)paren
suffix:semicolon
id|fail
suffix:colon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
eof
