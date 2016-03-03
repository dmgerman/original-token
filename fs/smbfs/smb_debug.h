multiline_comment|/*&n; * Defines some debug macros for smbfs.&n; */
multiline_comment|/* This makes a dentry parent/child name pair. Useful for debugging printk&squot;s */
DECL|macro|DENTRY_PATH
mdefine_line|#define DENTRY_PATH(dentry) &bslash;&n;&t;(dentry)-&gt;d_parent-&gt;d_name.name,(dentry)-&gt;d_name.name
multiline_comment|/*&n; * safety checks that should never happen ??? &n; * these are normally enabled.&n; */
macro_line|#ifdef SMBFS_PARANOIA
DECL|macro|PARANOIA
mdefine_line|#define PARANOIA(x...) printk(KERN_NOTICE __FUNCTION__ &quot;: &quot; x)
macro_line|#else
DECL|macro|PARANOIA
mdefine_line|#define PARANOIA(x...) do { ; } while(0)
macro_line|#endif
multiline_comment|/* lots of debug messages */
macro_line|#ifdef SMBFS_DEBUG_VERBOSE
DECL|macro|VERBOSE
mdefine_line|#define VERBOSE(x...) printk(KERN_DEBUG __FUNCTION__ &quot;: &quot; x)
macro_line|#else
DECL|macro|VERBOSE
mdefine_line|#define VERBOSE(x...) do { ; } while(0)
macro_line|#endif
multiline_comment|/*&n; * &quot;normal&quot; debug messages, but not with a normal DEBUG define ... way&n; * too common name.&n; */
macro_line|#ifdef SMBFS_DEBUG
DECL|macro|DEBUG1
mdefine_line|#define DEBUG1(x...) printk(KERN_DEBUG __FUNCTION__ &quot;: &quot; x)
macro_line|#else
DECL|macro|DEBUG1
mdefine_line|#define DEBUG1(x...) do { ; } while(0)
macro_line|#endif
eof
