multiline_comment|/* gzip.h -- common declarations for all gzip modules&n; * Copyright (C) 1992-1993 Jean-loup Gailly.&n; * This is free software; you can redistribute it and/or modify it under the&n; * terms of the GNU General Public License, see the file COPYING.&n; */
macro_line|#if defined(__STDC__) || defined(PROTO)
DECL|macro|OF
macro_line|#  define OF(args)  args
macro_line|#else
DECL|macro|OF
macro_line|#  define OF(args)  ()
macro_line|#endif
macro_line|#ifdef __STDC__
DECL|typedef|voidp
r_typedef
r_void
op_star
id|voidp
suffix:semicolon
macro_line|#else
DECL|typedef|voidp
r_typedef
r_char
op_star
id|voidp
suffix:semicolon
macro_line|#endif
multiline_comment|/* I don&squot;t like nested includes, but the string functions are used too often */
macro_line|#if defined(HAVE_STRING_H) || defined(STDC_HEADERS)
macro_line|#  include &lt;string.h&gt;
DECL|macro|memzero
macro_line|#  define memzero(s, n)     memset ((s), 0, (n))
macro_line|#else
macro_line|#  include &lt;strings.h&gt;
DECL|macro|strchr
macro_line|#  define strchr            index 
DECL|macro|strrchr
macro_line|#  define strrchr           rindex
DECL|macro|memcpy
macro_line|#  define memcpy(d, s, n)   bcopy((s), (d), (n)) 
DECL|macro|memcmp
macro_line|#  define memcmp(s1, s2, n) bcmp((s1), (s2), (n)) 
DECL|macro|memzero
macro_line|#  define memzero(s, n)     bzero((s), (n))
macro_line|#endif
macro_line|#if !defined(STDC_HEADERS) &amp;&amp; defined(HAVE_MEMORY_H)
macro_line|#  include &lt;memory.h&gt;
macro_line|#endif
macro_line|#ifndef RETSIGTYPE
DECL|macro|RETSIGTYPE
macro_line|#  define RETSIGTYPE void
macro_line|#endif
DECL|macro|local
mdefine_line|#define local static
DECL|typedef|uch
r_typedef
r_int
r_char
id|uch
suffix:semicolon
DECL|typedef|ush
r_typedef
r_int
r_int
id|ush
suffix:semicolon
DECL|typedef|ulg
r_typedef
r_int
r_int
id|ulg
suffix:semicolon
multiline_comment|/* Return codes from gzip */
DECL|macro|OK
mdefine_line|#define OK      0
DECL|macro|ERROR
mdefine_line|#define ERROR   1
DECL|macro|WARNING
mdefine_line|#define WARNING 2
multiline_comment|/* Compression methods (see algorithm.doc) */
DECL|macro|STORED
mdefine_line|#define STORED     0
DECL|macro|COMPRESSED
mdefine_line|#define COMPRESSED 1
DECL|macro|PACKED
mdefine_line|#define PACKED     2
multiline_comment|/* methods 3 to 7 reserved */
DECL|macro|DEFLATED
mdefine_line|#define DEFLATED   8
r_extern
r_int
id|method
suffix:semicolon
multiline_comment|/* compression method */
multiline_comment|/* To save memory for 16 bit systems, some arrays are overlayed between&n; * the various modules:&n; * deflate:  prev+head   window      d_buf  l_buf  outbuf&n; * unlzw:    tab_prefix  tab_suffix  stack  inbuf  outbuf&n; * inflate:              window             inbuf&n; * unpack:               window             inbuf&n; * For compression, input is done in window[]. For decompression, output&n; * is done in window except for unlzw.&n; */
macro_line|#ifndef&t;INBUFSIZ
DECL|macro|INBUFSIZ
macro_line|#  define INBUFSIZ  0x8000  /* input buffer size */
macro_line|#endif
DECL|macro|INBUF_EXTRA
mdefine_line|#define INBUF_EXTRA  64     /* required by unlzw() */
macro_line|#ifndef&t;OUTBUFSIZ
DECL|macro|OUTBUFSIZ
macro_line|#  define OUTBUFSIZ  16384  /* output buffer size */
macro_line|#endif
DECL|macro|OUTBUF_EXTRA
mdefine_line|#define OUTBUF_EXTRA 2048   /* required by unlzw() */
DECL|macro|DIST_BUFSIZE
mdefine_line|#define DIST_BUFSIZE 0x8000 /* buffer for distances, see trees.c */
macro_line|#ifdef DYN_ALLOC
DECL|macro|EXTERN
macro_line|#  define EXTERN(type, array)  extern type * near array
DECL|macro|DECLARE
macro_line|#  define DECLARE(type, array, size)  type * near array
DECL|macro|ALLOC
macro_line|#  define ALLOC(type, array, size) { &bslash;&n;      array = (type*)fcalloc((unsigned)(((size)+1L)/2), 2*sizeof(type)); &bslash;&n;      if (array == NULL) error(&quot;insufficient memory&quot;); &bslash;&n;   }
DECL|macro|FREE
macro_line|#  define FREE(array) {if (array != NULL) fcfree(array), array=NULL;}
macro_line|#else
DECL|macro|EXTERN
macro_line|#  define EXTERN(type, array)  extern type array[]
DECL|macro|DECLARE
macro_line|#  define DECLARE(type, array, size)  type array[size]
DECL|macro|ALLOC
macro_line|#  define ALLOC(type, array, size)
DECL|macro|FREE
macro_line|#  define FREE(array)
macro_line|#endif
id|EXTERN
c_func
(paren
id|uch
comma
id|inbuf
)paren
suffix:semicolon
multiline_comment|/* input buffer */
id|EXTERN
c_func
(paren
id|uch
comma
id|outbuf
)paren
suffix:semicolon
multiline_comment|/* output buffer */
id|EXTERN
c_func
(paren
id|ush
comma
id|d_buf
)paren
suffix:semicolon
multiline_comment|/* buffer for distances, see trees.c */
id|EXTERN
c_func
(paren
id|uch
comma
id|window
)paren
suffix:semicolon
multiline_comment|/* Sliding window and suffix table (unlzw) */
DECL|macro|tab_suffix
mdefine_line|#define tab_suffix window
macro_line|#ifndef MAXSEG_64K
DECL|macro|tab_prefix
macro_line|#  define tab_prefix prev    /* hash link (see deflate.c) */
DECL|macro|head
macro_line|#  define head (prev+WSIZE)  /* hash head (see deflate.c) */
id|EXTERN
c_func
(paren
id|ush
comma
id|tab_prefix
)paren
suffix:semicolon
multiline_comment|/* prefix code (see unlzw.c) */
macro_line|#else
DECL|macro|tab_prefix0
macro_line|#  define tab_prefix0 prev
DECL|macro|head
macro_line|#  define head tab_prefix1
id|EXTERN
c_func
(paren
id|ush
comma
id|tab_prefix0
)paren
suffix:semicolon
multiline_comment|/* prefix for even codes */
id|EXTERN
c_func
(paren
id|ush
comma
id|tab_prefix1
)paren
suffix:semicolon
multiline_comment|/* prefix for odd  codes */
macro_line|#endif
r_extern
r_int
id|insize
suffix:semicolon
multiline_comment|/* valid bytes in inbuf */
r_extern
r_int
id|inptr
suffix:semicolon
multiline_comment|/* index of next byte to be processed in inbuf */
r_extern
r_int
id|outcnt
suffix:semicolon
multiline_comment|/* bytes in output buffer */
r_extern
r_int
id|bytes_in
suffix:semicolon
multiline_comment|/* number of input bytes */
r_extern
r_int
id|bytes_out
suffix:semicolon
multiline_comment|/* number of output bytes */
r_extern
r_int
id|overhead
suffix:semicolon
multiline_comment|/* number of bytes in gzip header */
DECL|macro|isize
mdefine_line|#define isize bytes_in
multiline_comment|/* for compatibility with old zip sources (to be cleaned) */
r_extern
r_int
id|ifd
suffix:semicolon
multiline_comment|/* input file descriptor */
r_extern
r_int
id|ofd
suffix:semicolon
multiline_comment|/* output file descriptor */
r_extern
r_char
id|ifname
(braket
)braket
suffix:semicolon
multiline_comment|/* input filename or &quot;stdin&quot; */
r_extern
r_char
id|ofname
(braket
)braket
suffix:semicolon
multiline_comment|/* output filename or &quot;stdout&quot; */
r_extern
id|ulg
id|time_stamp
suffix:semicolon
multiline_comment|/* original time stamp (modification time) */
r_extern
r_int
id|ifile_size
suffix:semicolon
multiline_comment|/* input file size, -1 for devices (debug only) */
r_extern
r_int
id|exit_code
suffix:semicolon
multiline_comment|/* program exit code */
DECL|typedef|file_t
r_typedef
r_int
id|file_t
suffix:semicolon
multiline_comment|/* Do not use stdio */
DECL|macro|NO_FILE
mdefine_line|#define NO_FILE  (-1)   /* in memory compression */
DECL|macro|GZIP_MAGIC
mdefine_line|#define&t;GZIP_MAGIC     &quot;&bslash;037&bslash;213&quot; /* Magic header for gzip files, 1F 8B */
DECL|macro|OLD_GZIP_MAGIC
mdefine_line|#define&t;OLD_GZIP_MAGIC &quot;&bslash;037&bslash;236&quot; /* Magic header for gzip 0.5 = freeze 1.x */
DECL|macro|PKZIP_MAGIC
mdefine_line|#define&t;PKZIP_MAGIC  &quot;PK&bslash;003&bslash;004&quot; /* Magic header for pkzip files */
DECL|macro|PACK_MAGIC
mdefine_line|#define&t;PACK_MAGIC     &quot;&bslash;037&bslash;036&quot; /* Magic header for packed files */
multiline_comment|/* gzip flag byte */
DECL|macro|ASCII_FLAG
mdefine_line|#define ASCII_FLAG   0x01 /* bit 0 set: file probably ascii text */
DECL|macro|CONTINUATION
mdefine_line|#define CONTINUATION 0x02 /* bit 1 set: continuation of multi-part gzip file */
DECL|macro|EXTRA_FIELD
mdefine_line|#define EXTRA_FIELD  0x04 /* bit 2 set: extra field present */
DECL|macro|ORIG_NAME
mdefine_line|#define ORIG_NAME    0x08 /* bit 3 set: original file name present */
DECL|macro|COMMENT
mdefine_line|#define COMMENT      0x10 /* bit 4 set: file comment present */
DECL|macro|ENCRYPTED
mdefine_line|#define ENCRYPTED    0x20 /* bit 5 set: file is encrypted */
DECL|macro|RESERVED
mdefine_line|#define RESERVED     0xC0 /* bit 6,7:   reserved */
multiline_comment|/* internal file attribute */
DECL|macro|UNKNOWN
mdefine_line|#define UNKNOWN (-1)
DECL|macro|BINARY
mdefine_line|#define BINARY  0
DECL|macro|ASCII
mdefine_line|#define ASCII   1
macro_line|#ifndef WSIZE
DECL|macro|WSIZE
macro_line|#  define WSIZE 0x8000     /* window size--must be a power of two, and */
macro_line|#endif                     /*  at least 32K for zip&squot;s deflate method */
DECL|macro|MIN_MATCH
mdefine_line|#define MIN_MATCH  3
DECL|macro|MAX_MATCH
mdefine_line|#define MAX_MATCH  258
multiline_comment|/* The minimum and maximum match lengths */
DECL|macro|MIN_LOOKAHEAD
mdefine_line|#define MIN_LOOKAHEAD (MAX_MATCH+MIN_MATCH+1)
multiline_comment|/* Minimum amount of lookahead, except at the end of the input file.&n; * See deflate.c for comments about the MIN_MATCH+1.&n; */
DECL|macro|MAX_DIST
mdefine_line|#define MAX_DIST  (WSIZE-MIN_LOOKAHEAD)
multiline_comment|/* In order to simplify the code, particularly on 16 bit machines, match&n; * distances are limited to MAX_DIST instead of WSIZE.&n; */
r_extern
r_int
id|decrypt
suffix:semicolon
multiline_comment|/* flag to turn on decryption */
r_extern
r_int
id|save_orig_name
suffix:semicolon
multiline_comment|/* set if original name must be saved */
r_extern
r_int
id|verbose
suffix:semicolon
multiline_comment|/* be verbose (-v) */
r_extern
r_int
id|level
suffix:semicolon
multiline_comment|/* compression level */
r_extern
r_int
id|test
suffix:semicolon
multiline_comment|/* check .z file integrity */
r_extern
r_int
id|to_stdout
suffix:semicolon
multiline_comment|/* output to stdout (-c) */
DECL|macro|get_byte
mdefine_line|#define get_byte()  (inptr &lt; insize ? inbuf[inptr++] : fill_inbuf())
multiline_comment|/* put_byte is used for the compressed output, put_char for the&n; * uncompressed output. However unlzw() uses window for its&n; * suffix table instead of its output buffer, so it does not use put_char.&n; * (to be cleaned up).&n; */
DECL|macro|put_byte
mdefine_line|#define put_byte(c) {outbuf[outcnt++]=(uch)(c); if (outcnt==OUTBUFSIZ)&bslash;&n;   flush_outbuf();}
DECL|macro|put_char
mdefine_line|#define put_char(c) {window[outcnt++]=(uch)(c); if (outcnt==WSIZE)&bslash;&n;   flush_window();}
multiline_comment|/* Output a 16 bit value, lsb first */
DECL|macro|put_short
mdefine_line|#define put_short(w) &bslash;&n;{ if (outcnt &lt; OUTBUFSIZ-2) { &bslash;&n;    outbuf[outcnt++] = (uch) ((w) &amp; 0xff); &bslash;&n;    outbuf[outcnt++] = (uch) ((ush)(w) &gt;&gt; 8); &bslash;&n;  } else { &bslash;&n;    put_byte((uch)((w) &amp; 0xff)); &bslash;&n;    put_byte((uch)((ush)(w) &gt;&gt; 8)); &bslash;&n;  } &bslash;&n;}
multiline_comment|/* Output a 32 bit value to the bit stream, lsb first */
DECL|macro|put_long
mdefine_line|#define put_long(n) { &bslash;&n;    put_short((n) &amp; 0xffff); &bslash;&n;    put_short(((ulg)(n)) &gt;&gt; 16); &bslash;&n;}
DECL|macro|seekable
mdefine_line|#define seekable()    0  /* force sequential output */
DECL|macro|translate_eol
mdefine_line|#define translate_eol 0  /* no option -a yet */
DECL|macro|tolow
mdefine_line|#define tolow(c)  (isupper(c) ? (c)-&squot;A&squot;+&squot;a&squot; : (c))    /* force to lower case */
multiline_comment|/* Macros for getting two-byte and four-byte header values */
DECL|macro|SH
mdefine_line|#define SH(p) ((ush)(uch)((p)[0]) | ((ush)(uch)((p)[1]) &lt;&lt; 8))
DECL|macro|LG
mdefine_line|#define LG(p) ((ulg)(SH(p)) | ((ulg)(SH((p)+2)) &lt;&lt; 16))
multiline_comment|/* Diagnostic functions */
macro_line|#ifdef DEBUG
DECL|macro|Assert
macro_line|#  define Assert(cond,msg) {if(!(cond)) error(msg);}
DECL|macro|Trace
macro_line|#  define Trace(x) fprintf x
DECL|macro|Tracev
macro_line|#  define Tracev(x) {if (verbose) fprintf x ;}
DECL|macro|Tracevv
macro_line|#  define Tracevv(x) {if (verbose&gt;1) fprintf x ;}
DECL|macro|Tracec
macro_line|#  define Tracec(c,x) {if (verbose &amp;&amp; (c)) fprintf x ;}
DECL|macro|Tracecv
macro_line|#  define Tracecv(c,x) {if (verbose&gt;1 &amp;&amp; (c)) fprintf x ;}
macro_line|#else
DECL|macro|Assert
macro_line|#  define Assert(cond,msg)
DECL|macro|Trace
macro_line|#  define Trace(x)
DECL|macro|Tracev
macro_line|#  define Tracev(x)
DECL|macro|Tracevv
macro_line|#  define Tracevv(x)
DECL|macro|Tracec
macro_line|#  define Tracec(c,x)
DECL|macro|Tracecv
macro_line|#  define Tracecv(c,x)
macro_line|#endif
multiline_comment|/* in zip.c: */
r_extern
r_void
id|zip
id|OF
c_func
(paren
(paren
r_int
id|in
comma
r_int
id|out
)paren
)paren
suffix:semicolon
r_extern
r_int
id|file_read
id|OF
c_func
(paren
(paren
r_char
op_star
id|buf
comma
r_int
id|size
)paren
)paren
suffix:semicolon
multiline_comment|/* in unzip.c */
r_extern
r_void
id|unzip
id|OF
c_func
(paren
(paren
r_int
id|in
comma
r_int
id|out
)paren
)paren
suffix:semicolon
r_extern
r_int
id|check_zipfile
id|OF
c_func
(paren
(paren
r_int
id|in
)paren
)paren
suffix:semicolon
multiline_comment|/* in unpack.c */
r_extern
r_void
id|unpack
id|OF
c_func
(paren
(paren
r_int
id|in
comma
r_int
id|out
)paren
)paren
suffix:semicolon
multiline_comment|/* in gzip.c */
id|RETSIGTYPE
id|abort_gzip
id|OF
c_func
(paren
(paren
r_void
)paren
)paren
suffix:semicolon
multiline_comment|/* in deflate.c */
r_void
id|lm_init
id|OF
c_func
(paren
(paren
r_int
id|pack_level
comma
id|ush
op_star
id|flags
)paren
)paren
suffix:semicolon
id|ulg
id|deflate
id|OF
c_func
(paren
(paren
r_void
)paren
)paren
suffix:semicolon
multiline_comment|/* in trees.c */
r_void
id|ct_init
id|OF
c_func
(paren
(paren
id|ush
op_star
id|attr
comma
r_int
op_star
id|method
)paren
)paren
suffix:semicolon
r_int
id|ct_tally
id|OF
c_func
(paren
(paren
r_int
id|dist
comma
r_int
id|lc
)paren
)paren
suffix:semicolon
id|ulg
id|flush_block
id|OF
c_func
(paren
(paren
r_char
op_star
id|buf
comma
id|ulg
id|stored_len
comma
r_int
id|eof
)paren
)paren
suffix:semicolon
multiline_comment|/* in bits.c */
r_void
id|bi_init
id|OF
c_func
(paren
(paren
id|file_t
id|zipfile
)paren
)paren
suffix:semicolon
r_void
id|send_bits
id|OF
c_func
(paren
(paren
r_int
id|value
comma
r_int
id|length
)paren
)paren
suffix:semicolon
r_int
id|bi_reverse
id|OF
c_func
(paren
(paren
r_int
id|value
comma
r_int
id|length
)paren
)paren
suffix:semicolon
r_void
id|bi_windup
id|OF
c_func
(paren
(paren
r_void
)paren
)paren
suffix:semicolon
r_void
id|copy_block
id|OF
c_func
(paren
(paren
r_char
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|header
)paren
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|read_buf
)paren
id|OF
c_func
(paren
(paren
r_char
op_star
id|buf
comma
r_int
id|size
)paren
)paren
suffix:semicolon
multiline_comment|/* in util.c: */
r_extern
id|ulg
id|updcrc
id|OF
c_func
(paren
(paren
id|uch
op_star
id|s
comma
r_int
id|n
)paren
)paren
suffix:semicolon
r_extern
r_void
id|clear_bufs
id|OF
c_func
(paren
(paren
r_void
)paren
)paren
suffix:semicolon
r_extern
r_int
id|fill_inbuf
id|OF
c_func
(paren
(paren
r_void
)paren
)paren
suffix:semicolon
r_extern
r_void
id|flush_outbuf
id|OF
c_func
(paren
(paren
r_void
)paren
)paren
suffix:semicolon
r_extern
r_void
id|flush_window
id|OF
c_func
(paren
(paren
r_void
)paren
)paren
suffix:semicolon
r_extern
r_char
op_star
id|strlwr
id|OF
c_func
(paren
(paren
r_char
op_star
id|s
)paren
)paren
suffix:semicolon
multiline_comment|/*extern char *basename     OF((char *fname));*/
r_extern
r_char
op_star
id|add_envopt
id|OF
c_func
(paren
(paren
r_int
op_star
id|argcp
comma
r_char
op_star
op_star
op_star
id|argvp
comma
r_char
op_star
id|env
)paren
)paren
suffix:semicolon
r_extern
r_void
id|error
id|OF
c_func
(paren
(paren
r_char
op_star
id|m
)paren
)paren
suffix:semicolon
r_extern
r_void
id|warn
id|OF
c_func
(paren
(paren
r_char
op_star
id|a
comma
r_char
op_star
id|b
)paren
)paren
suffix:semicolon
r_extern
r_void
id|read_error
id|OF
c_func
(paren
(paren
r_void
)paren
)paren
suffix:semicolon
r_extern
r_void
id|write_error
id|OF
c_func
(paren
(paren
r_void
)paren
)paren
suffix:semicolon
r_extern
r_void
id|display_ratio
id|OF
c_func
(paren
(paren
r_int
id|num
comma
r_int
id|den
)paren
)paren
suffix:semicolon
r_extern
id|voidp
id|xmalloc
id|OF
c_func
(paren
(paren
r_int
r_int
id|size
)paren
)paren
suffix:semicolon
multiline_comment|/* in inflate.c */
r_extern
r_int
id|inflate
id|OF
c_func
(paren
(paren
r_void
)paren
)paren
suffix:semicolon
eof
