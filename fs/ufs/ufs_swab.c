multiline_comment|/*&n; *  linux/fs/ufs/ufs_swab.c&n; *&n; * Copyright (C) 1997&n; * Francois-Rene Rideau &lt;rideau@ens.fr&gt;&n; *&n; */
multiline_comment|/*&n; * For inspiration, you might wanna check sys/ufs/ffs/fs.h from whateverBSD&n; *&n; * NOTES&n; * 19970406 - Fare &lt;rideau@ens.fr&gt;&n; *   1) I began from old very preliminary 2.0.x sources,&n; *&t;but it was underfeatured;&n; *&t;I later saw that 2.1.1 sources had a *global* UFS byteswap flag.&n; *&t;EVIL: imagine that a swabbed partition be mounted&n; *&t;while a non-swabbed partition are active (that sucks!)&n; *&t;I merged that source tree with mine.&n; *   2) I hope no one is using obNNUUXXIIous byteorder.&n; *&t;That&squot;s the only thing I might have broken,&n; *&t;though I rather think it&squot;s a fix:&n; *&t;instead of __u64 like BSD,&n; *&t;the former driver used an explicitly bigendian array of __u32!&n; *   3) I provide a few macros that use GCC C Extensions.&n; *&t;Port to other compilers would require avoiding them.&n; *&t;in any case, 64 bit (long long) support is required,&n; *&t;unless you&squot;re ready to workaround&n; *   4) the swab routines below depend on the precise name and order&n; *&t;of the structure elements. Watch out any modification in ufs_fs.h!!!&n; *   5) putting byteswapping stuff in ufs_swab* seems cleaner to me.&n; *   6) These sources should work with both 2.0 and 2.1 kernels...&n; *&n; * 19971013 - Fare &lt;rideaufr@issy.cnet.fr&gt;&n; *   1) Ported to 2.1.57&n; *   2) instead of byteswapping, use [bl]e_to_cpu:&n; *     it might be that we run on a VAX!&n; *&n; * HOWTO continue adding swab support:&n; *&t;basically, anywhere metadata is bread() (i.e. mapped to block device),&n; *      data should either be SWAB()ed on the fly,&n; *      or copied to a buffer and globally bswap_ufs_*() there.&n; *&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &quot;ufs_swab.h&quot;
DECL|function|n_be16_to_cpus
r_static
id|__inline__
r_void
id|n_be16_to_cpus
c_func
(paren
id|__u16
op_star
id|p
comma
r_int
id|n
)paren
(brace
macro_line|#ifndef __BIG_ENDIAN
r_int
id|i
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
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
id|be16_to_cpus
c_func
(paren
op_amp
id|p
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|n_be32_to_cpus
r_static
id|__inline__
r_void
id|n_be32_to_cpus
c_func
(paren
id|__u32
op_star
id|p
comma
r_int
id|n
)paren
(brace
macro_line|#ifndef __BIG_ENDIAN
r_int
id|i
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
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
id|be32_to_cpus
c_func
(paren
op_amp
id|p
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|n_le16_to_cpus
r_static
id|__inline__
r_void
id|n_le16_to_cpus
c_func
(paren
id|__u16
op_star
id|p
comma
r_int
id|n
)paren
(brace
macro_line|#ifndef __LITTLE_ENDIAN
r_int
id|i
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
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
id|le16_to_cpus
c_func
(paren
op_amp
id|p
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|n_le32_to_cpus
r_static
id|__inline__
r_void
id|n_le32_to_cpus
c_func
(paren
id|__u32
op_star
id|p
comma
r_int
id|n
)paren
(brace
macro_line|#ifndef __LITTLE_ENDIAN
r_int
id|i
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
id|n
suffix:semicolon
id|i
op_increment
)paren
(brace
id|le32_to_cpus
c_func
(paren
op_amp
id|p
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|macro|__length_before
mdefine_line|#define __length_before(p,member) &bslash;&n;        ((unsigned)(((char*)&amp;((p)-&gt;member))-(char*)(p)))
DECL|macro|__length_since
mdefine_line|#define __length_since(p,member) &bslash;&n;        ((unsigned)(sizeof(*p)-__length_before(p,member)))
DECL|macro|__length_between
mdefine_line|#define __length_between(p,begin,after_end) &bslash;&n;        ((unsigned)(__length_before(p,after_end)-__length_before(p,begin)))
DECL|macro|be32_to_cpus__between
mdefine_line|#define be32_to_cpus__between(s,begin,after_end) &bslash;&n;        n_be32_to_cpus((__u32*)&amp;((s).begin), &bslash;&n;                __length_between(&amp;s,begin,after_end)/4)
DECL|macro|le32_to_cpus__between
mdefine_line|#define le32_to_cpus__between(s,begin,after_end) &bslash;&n;        n_le32_to_cpus((__u32*)&amp;((s).begin), &bslash;&n;                __length_between(&amp;s,begin,after_end)/4)
DECL|macro|be32_to_cpus__since
mdefine_line|#define be32_to_cpus__since(s,begin) &bslash;&n;&t;n_be32_to_cpus((__u32*)&amp;((s).begin), &bslash;&n;                __length_since(&amp;s,begin)/4)
DECL|macro|le32_to_cpus__since
mdefine_line|#define le32_to_cpus__since(s,begin) &bslash;&n;&t;n_le32_to_cpus((__u32*)&amp;((s).begin), &bslash;&n;                __length_since(&amp;s,begin)/4)
DECL|macro|be16_to_cpus__between
mdefine_line|#define be16_to_cpus__between(s,begin,after_end) &bslash;&n;&t;n_be16_to_cpus((__u16*)&amp;((s).begin), &bslash;&n;                __length_between(&amp;s,begin,after_end)/2)
DECL|macro|le16_to_cpus__between
mdefine_line|#define le16_to_cpus__between(s,begin,after_end) &bslash;&n;&t;n_le16_to_cpus((__u16*)&amp;((s).begin), &bslash;&n;                __length_between(&amp;s,begin,after_end)/2)
multiline_comment|/*&n; * Here are the whole-structure swabping routines...&n; */
DECL|function|ufs_superblock_be_to_cpus
r_extern
r_void
id|ufs_superblock_be_to_cpus
c_func
(paren
r_struct
id|ufs_superblock
op_star
id|usb
)paren
(brace
macro_line|#ifndef __BIG_ENDIAN
id|be32_to_cpus__between
c_func
(paren
op_star
id|usb
comma
id|fs_link
comma
id|fs_fmod
)paren
suffix:semicolon
multiline_comment|/* XXX - I dunno what to do w/ fs_csp,&n;         * but it is unused by the current code, so that&squot;s ok for now.&n;         */
id|be32_to_cpus
c_func
(paren
op_amp
id|usb-&gt;fs_cpc
)paren
suffix:semicolon
id|be16_to_cpus__between
c_func
(paren
op_star
id|usb
comma
id|fs_opostbl
comma
id|fs_sparecon
)paren
suffix:semicolon
id|be32_to_cpus__between
c_func
(paren
op_star
id|usb
comma
id|fs_sparecon
comma
id|fs_qbmask
)paren
suffix:semicolon
id|be64_to_cpus
c_func
(paren
(paren
id|__u64
op_star
)paren
op_amp
id|usb-&gt;fs_qbmask
)paren
suffix:semicolon
id|be64_to_cpus
c_func
(paren
(paren
id|__u64
op_star
)paren
op_amp
id|usb-&gt;fs_qfmask
)paren
suffix:semicolon
id|be32_to_cpus__between
c_func
(paren
op_star
id|usb
comma
id|fs_postblformat
comma
id|fs_magic
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|ufs_superblock_le_to_cpus
r_extern
r_void
id|ufs_superblock_le_to_cpus
c_func
(paren
r_struct
id|ufs_superblock
op_star
id|usb
)paren
(brace
macro_line|#ifndef __LITTLE_ENDIAN
id|le32_to_cpus__between
c_func
(paren
op_star
id|usb
comma
id|fs_link
comma
id|fs_fmod
)paren
suffix:semicolon
multiline_comment|/* XXX - I dunno what to do w/ fs_csp,&n;         * but it is unused by the current code, so that&squot;s ok for now.&n;         */
id|le32_to_cpus
c_func
(paren
op_amp
id|usb-&gt;fs_cpc
)paren
suffix:semicolon
id|le16_to_cpus__between
c_func
(paren
op_star
id|usb
comma
id|fs_opostbl
comma
id|fs_sparecon
)paren
suffix:semicolon
id|le32_to_cpus__between
c_func
(paren
op_star
id|usb
comma
id|fs_sparecon
comma
id|fs_qbmask
)paren
suffix:semicolon
id|le64_to_cpus
c_func
(paren
op_amp
id|usb-&gt;fs_qbmask
)paren
suffix:semicolon
id|le64_to_cpus
c_func
(paren
op_amp
id|usb-&gt;fs_qfmask
)paren
suffix:semicolon
id|le32_to_cpus__between
c_func
(paren
op_star
id|usb
comma
id|fs_postblformat
comma
id|fs_magic
)paren
suffix:semicolon
macro_line|#endif
)brace
eof