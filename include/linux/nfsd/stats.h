multiline_comment|/*&n; * linux/include/nfsd/stats.h&n; *&n; * Statistics for NFS server.&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef LINUX_NFSD_STATS_H
DECL|macro|LINUX_NFSD_STATS_H
mdefine_line|#define LINUX_NFSD_STATS_H
DECL|struct|nfsd_stats
r_struct
id|nfsd_stats
(brace
DECL|member|rchits
r_int
r_int
id|rchits
suffix:semicolon
multiline_comment|/* repcache hits */
DECL|member|rcmisses
r_int
r_int
id|rcmisses
suffix:semicolon
multiline_comment|/* repcache hits */
DECL|member|rcnocache
r_int
r_int
id|rcnocache
suffix:semicolon
multiline_comment|/* uncached reqs */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_extern
r_struct
id|nfsd_stats
id|nfsdstats
suffix:semicolon
r_extern
r_struct
id|svc_stat
id|nfsd_svcstats
suffix:semicolon
r_void
id|nfsd_stat_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|nfsd_stat_shutdown
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* LINUX_NFSD_STATS_H */
eof
