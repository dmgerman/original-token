multiline_comment|/* Coda filesystem -- Linux Minicache&n; *&n; * Copyright (C) 1989 - 1997 Carnegie Mellon University&n; *&n; * Carnegie Mellon University encourages users of this software to&n; * contribute improvements to the Coda project. Contact Peter Braam&n; * &lt;coda@cs.cmu.edu&gt;&n; */
macro_line|#ifndef _CFSNC_HEADER_
DECL|macro|_CFSNC_HEADER_
mdefine_line|#define _CFSNC_HEADER_
multiline_comment|/*&n; * Structure for an element in the Coda Credential Cache.&n; */
DECL|struct|coda_cache
r_struct
id|coda_cache
(brace
DECL|member|cc_cclist
r_struct
id|list_head
id|cc_cclist
suffix:semicolon
multiline_comment|/* list of all cache entries */
DECL|member|cc_cnlist
r_struct
id|list_head
id|cc_cnlist
suffix:semicolon
multiline_comment|/* list of cache entries/cnode */
DECL|member|cc_mask
r_int
id|cc_mask
suffix:semicolon
DECL|member|cc_cred
r_struct
id|coda_cred
id|cc_cred
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* credential cache */
r_void
id|coda_cache_enter
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mask
)paren
suffix:semicolon
r_void
id|coda_cache_clear_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_void
id|coda_cache_clear_all
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_void
id|coda_cache_clear_cred
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|coda_cred
op_star
id|cred
)paren
suffix:semicolon
r_int
id|coda_cache_check
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mask
)paren
suffix:semicolon
multiline_comment|/* for downcalls and attributes and lookups */
r_void
id|coda_flag_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|flag
)paren
suffix:semicolon
r_void
id|coda_flag_inode_children
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|flag
)paren
suffix:semicolon
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
mdefine_line|#define CFSNC_PURGEUSER&t;((u_long) 10)
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
