macro_line|#ifndef _CONFIG_H
DECL|macro|_CONFIG_H
mdefine_line|#define _CONFIG_H
multiline_comment|/* #define LASU_HD */
DECL|macro|LINUS_HD
mdefine_line|#define LINUS_HD
multiline_comment|/*&n; * Amount of ram memory (in bytes, 640k-1M not discounted). Currently 8Mb.&n; * Don&squot;t make this bigger without making sure that there are enough page&n; * directory entries (boot/head.s)&n; */
macro_line|#if&t;defined(LINUS_HD)
DECL|macro|HIGH_MEMORY
mdefine_line|#define HIGH_MEMORY (0x800000)
macro_line|#elif&t;defined(LASU_HD)
DECL|macro|HIGH_MEMORY
mdefine_line|#define HIGH_MEMORY (0x400000)
macro_line|#else
macro_line|#error &quot;must define hd&quot;
macro_line|#endif
multiline_comment|/* End of buffer memory. Must be 0xA0000, or &gt; 0x100000, 4096-byte aligned */
macro_line|#if (HIGH_MEMORY&gt;=0x600000)
DECL|macro|BUFFER_END
mdefine_line|#define BUFFER_END 0x200000
macro_line|#else
DECL|macro|BUFFER_END
mdefine_line|#define BUFFER_END 0xA0000
macro_line|#endif
multiline_comment|/* Root device at bootup. */
macro_line|#if&t;defined(LINUS_HD)
DECL|macro|ROOT_DEV
mdefine_line|#define ROOT_DEV 0x306
macro_line|#elif&t;defined(LASU_HD)
DECL|macro|ROOT_DEV
mdefine_line|#define ROOT_DEV 0x302
macro_line|#else
macro_line|#error &quot;must define HD&quot;
macro_line|#endif
multiline_comment|/*&n; * HD type. If 2, put 2 structures with a comma. If just 1, put&n; * only 1 struct. The structs are { HEAD, SECTOR, TRACKS, WPCOM, LZONE, CTL }&n; *&n; * NOTE. CTL is supposed to be 0 for drives with less than 8 heads, and&n; * 8 if heads &gt;= 8. Don&squot;t know why, and I haven&squot;t tested it on a drive with&n; * more than 8 heads, but that is what the bios-listings seem to imply. I&n; * just love not having a manual.&n; */
macro_line|#if&t;defined(LASU_HD)
DECL|macro|HD_TYPE
mdefine_line|#define HD_TYPE { 7,35,915,65536,920,0 }
macro_line|#elif&t;defined(LINUS_HD)
DECL|macro|HD_TYPE
mdefine_line|#define HD_TYPE { 5,17,980,300,980,0 },{ 5,17,980,300,980,0 }
macro_line|#else
macro_line|#error &quot;must define a hard-disk type&quot;
macro_line|#endif
macro_line|#endif
eof
