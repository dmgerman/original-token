multiline_comment|/* &n; * Mach Operating System&n; * Copyright (c) 1990 Carnegie-Mellon University&n; * Copyright (c) 1989 Carnegie-Mellon University&n; * All rights reserved.  The CMU software License Agreement specifies&n; * the terms and conditions for use and redistribution.&n; */
multiline_comment|/*&n; * This code was written for the Coda file system at Carnegie Mellon University.&n; * Contributers include David Steere, James Kistler, and M. Satyanarayanan.&n; */
multiline_comment|/* &n; * HISTORY&n; * cfsnc.h,v&n; * Revision 1.2  1996/01/02 16:57:19  bnoble&n; * Added support for Coda MiniCache and raw inode calls (final commit)&n; *&n; * Revision 1.1.2.1  1995/12/20 01:57:45  bnoble&n; * Added CFS-specific files&n; *&n; * Revision 3.1.1.1  1995/03/04  19:08:22  bnoble&n; * Branch for NetBSD port revisions&n; *&n; * Revision 3.1  1995/03/04  19:08:21  bnoble&n; * Bump to major revision 3 to prepare for NetBSD port&n; *&n; * Revision 2.2  1994/08/28  19:37:39  luqi&n; * Add a new CFS_REPLACE call to allow venus to replace a ViceFid in the&n; * mini-cache.&n; *&n; * In &quot;cfs.h&quot;:&n; * Add CFS_REPLACE decl.&n; *&n; * In &quot;cfs_namecache.c&quot;:&n; * Add routine cfsnc_replace.&n; *&n; * In &quot;cfs_subr.c&quot;:&n; * Add case-statement to process CFS_REPLACE.&n; *&n; * In &quot;cfsnc.h&quot;:&n; * Add decl for CFSNC_REPLACE.&n; *&n; * Revision 2.1  94/07/21  16:25:27  satya&n; * Conversion to C++ 3.0; start of Coda Release 2.0&n; *&n; * Revision 1.2  92/10/27  17:58:34  lily&n; * merge kernel/latest and alpha/src/cfs&n; * &n; * Revision 2.2  90/07/05  11:27:04  mrt&n; * &t;Created for the Coda File System.&n; * &t;[90/05/23            dcs]&n; * &n; * Revision 1.4  90/05/31  17:02:12  dcs&n; * Prepare for merge with facilities kernel.&n; * &n; * &n; */
macro_line|#ifndef _CFSNC_HEADER_
DECL|macro|_CFSNC_HEADER_
mdefine_line|#define _CFSNC_HEADER_
macro_line|#include &quot;coda.h&quot;
macro_line|#include &quot;coda_cnode.h&quot;
multiline_comment|/*&n; * Cfs constants&n; */
DECL|macro|CFSNC_NAMELEN
mdefine_line|#define CFSNC_NAMELEN&t;15&t;&t;/* longest name stored in cache */
DECL|macro|CFSNC_CACHESIZE
mdefine_line|#define CFSNC_CACHESIZE 256&t;&t;/* Default cache size */
DECL|macro|CFSNC_HASHSIZE
mdefine_line|#define CFSNC_HASHSIZE&t;64&t;&t;/* Must be multiple of 2 */
multiline_comment|/*&n; * Structure for an element in the CFS Name Cache.&n; */
multiline_comment|/* roughly 50 bytes per entry */
DECL|struct|cfscache
r_struct
id|cfscache
(brace
DECL|member|hash_next
DECL|member|hash_prev
r_struct
id|cfscache
op_star
id|hash_next
comma
op_star
id|hash_prev
suffix:semicolon
multiline_comment|/* Hash list */
DECL|member|lru_next
DECL|member|lru_prev
r_struct
id|cfscache
op_star
id|lru_next
comma
op_star
id|lru_prev
suffix:semicolon
multiline_comment|/* LRU list */
DECL|member|cp
r_struct
id|cnode
op_star
id|cp
suffix:semicolon
multiline_comment|/* vnode of the file */
DECL|member|dcp
r_struct
id|cnode
op_star
id|dcp
suffix:semicolon
multiline_comment|/* parent&squot;s cnode */
DECL|member|cred
r_struct
id|CodaCred
op_star
id|cred
suffix:semicolon
multiline_comment|/* user credentials */
DECL|member|name
r_char
id|name
(braket
id|CFSNC_NAMELEN
)braket
suffix:semicolon
multiline_comment|/* segment name */
DECL|member|namelen
r_int
id|namelen
suffix:semicolon
multiline_comment|/* length of name */
)brace
suffix:semicolon
multiline_comment|/* exported */
r_void
id|cfsnc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|cfsnc_enter
c_func
(paren
r_struct
id|cnode
op_star
id|dcp
comma
r_register
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
comma
r_struct
id|cnode
op_star
id|cp
)paren
suffix:semicolon
r_struct
id|cnode
op_star
id|cfsnc_lookup
c_func
(paren
r_struct
id|cnode
op_star
id|dcp
comma
r_register
r_const
r_char
op_star
id|name
comma
r_int
id|namelen
)paren
suffix:semicolon
r_void
id|cfsnc_zapParentfid
c_func
(paren
id|ViceFid
op_star
id|fid
)paren
suffix:semicolon
r_void
id|cfsnc_zapfid
c_func
(paren
id|ViceFid
op_star
id|fid
)paren
suffix:semicolon
r_void
id|cfsnc_zapfile
c_func
(paren
r_struct
id|cnode
op_star
id|dcp
comma
r_register
r_const
r_char
op_star
id|name
comma
r_int
id|length
)paren
suffix:semicolon
r_void
id|cfsnc_purge_user
c_func
(paren
r_struct
id|CodaCred
op_star
id|cred
)paren
suffix:semicolon
r_void
id|cfsnc_flush
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|cfsnc_replace
c_func
(paren
id|ViceFid
op_star
id|f1
comma
id|ViceFid
op_star
id|f2
)paren
suffix:semicolon
r_void
id|print_cfsnc
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|coda_print_ce
c_func
(paren
r_struct
id|cfscache
op_star
)paren
suffix:semicolon
r_int
id|cfsnc_resize
c_func
(paren
r_int
id|hashsize
comma
r_int
id|heapsize
)paren
suffix:semicolon
multiline_comment|/* #define CFSNC_VALID(cncp)&t;( (cncp-&gt;dcp != (struct cnode *)0) &amp;&amp; (cncp-&gt;cp-&gt;c_flags &amp; C_VATTR) ) */
DECL|macro|CFSNC_VALID
mdefine_line|#define CFSNC_VALID(cncp)&t;    (cncp-&gt;dcp != (struct cnode *)0) 
DECL|macro|DATA_PART
mdefine_line|#define DATA_PART(cncp)&t;&t;&t;&t;(struct cfscache *) &bslash;&n;&t;&t;&t;((char *)cncp + (4*sizeof(struct cfscache *)))
DECL|macro|DATA_SIZE
mdefine_line|#define DATA_SIZE&t;(sizeof(struct cfscache)-(4*sizeof(struct cfscache *)))
multiline_comment|/*&n; * Structure to contain statistics on the cache usage&n; */
DECL|struct|cfsnc_statistics
r_struct
id|cfsnc_statistics
(brace
DECL|member|hits
r_int
id|hits
suffix:semicolon
DECL|member|misses
r_int
id|misses
suffix:semicolon
DECL|member|enters
r_int
id|enters
suffix:semicolon
DECL|member|dbl_enters
r_int
id|dbl_enters
suffix:semicolon
DECL|member|long_name_enters
r_int
id|long_name_enters
suffix:semicolon
DECL|member|long_name_lookups
r_int
id|long_name_lookups
suffix:semicolon
DECL|member|long_remove
r_int
id|long_remove
suffix:semicolon
DECL|member|lru_rm
r_int
id|lru_rm
suffix:semicolon
DECL|member|zapPfids
r_int
id|zapPfids
suffix:semicolon
DECL|member|zapFids
r_int
id|zapFids
suffix:semicolon
DECL|member|zapFile
r_int
id|zapFile
suffix:semicolon
DECL|member|zapUsers
r_int
id|zapUsers
suffix:semicolon
DECL|member|Flushes
r_int
id|Flushes
suffix:semicolon
DECL|member|Sum_bucket_len
r_int
id|Sum_bucket_len
suffix:semicolon
DECL|member|Sum2_bucket_len
r_int
id|Sum2_bucket_len
suffix:semicolon
DECL|member|Max_bucket_len
r_int
id|Max_bucket_len
suffix:semicolon
DECL|member|Num_zero_len
r_int
id|Num_zero_len
suffix:semicolon
DECL|member|Search_len
r_int
id|Search_len
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* &n; * Symbols to aid in debugging the namecache code. Assumes the existence&n; * of the variable cfsnc_debug, which is defined in cfs_namecache.c&n; */
r_extern
r_int
id|cfsnc_debug
suffix:semicolon
DECL|macro|CFSNC_DEBUG
mdefine_line|#define CFSNC_DEBUG(N, STMT)     { if (cfsnc_debug &amp; (1 &lt;&lt;N)) { STMT } }
DECL|macro|CFSNC_FIND
mdefine_line|#define CFSNC_FIND&t;&t;((u_long) 1)
DECL|macro|CFSNC_REMOVE
mdefine_line|#define CFSNC_REMOVE&t;&t;((u_long) 2)
DECL|macro|CFSNC_INIT
mdefine_line|#define CFSNC_INIT&t;&t;((u_long) 3)
DECL|macro|CFSNC_ENTER
mdefine_line|#define CFSNC_ENTER&t;&t;((u_long) 4)
DECL|macro|CFSNC_LOOKUP
mdefine_line|#define CFSNC_LOOKUP&t;&t;((u_long) 5)
DECL|macro|CFSNC_ZAPPFID
mdefine_line|#define CFSNC_ZAPPFID&t;&t;((u_long) 6)
DECL|macro|CFSNC_ZAPFID
mdefine_line|#define CFSNC_ZAPFID&t;&t;((u_long) 7)
DECL|macro|CFSNC_ZAPVNODE
mdefine_line|#define CFSNC_ZAPVNODE&t;&t;((u_long) 8)
DECL|macro|CFSNC_ZAPFILE
mdefine_line|#define CFSNC_ZAPFILE&t;&t;((u_long) 9)
DECL|macro|CFSNC_PURGEUSER
mdefine_line|#define CFSNC_PURGEUSER&t;&t;((u_long) 10)
DECL|macro|CFSNC_FLUSH
mdefine_line|#define CFSNC_FLUSH&t;&t;((u_long) 11)
DECL|macro|CFSNC_PRINTCFSNC
mdefine_line|#define CFSNC_PRINTCFSNC&t;((u_long) 12)
DECL|macro|CFSNC_PRINTSTATS
mdefine_line|#define CFSNC_PRINTSTATS&t;((u_long) 13)
DECL|macro|CFSNC_REPLACE
mdefine_line|#define CFSNC_REPLACE&t;&t;((u_long) 14)
macro_line|#endif _CFSNC_HEADER_
eof
