macro_line|#ifndef _LINUX_CONFIG_H
DECL|macro|_LINUX_CONFIG_H
mdefine_line|#define _LINUX_CONFIG_H
macro_line|#include &lt;linux/autoconf.h&gt;
multiline_comment|/*&n; * Defines for what uname() should return &n; */
macro_line|#ifndef UTS_SYSNAME
DECL|macro|UTS_SYSNAME
mdefine_line|#define UTS_SYSNAME &quot;Linux&quot;
macro_line|#endif
macro_line|#ifndef UTS_NODENAME
DECL|macro|UTS_NODENAME
mdefine_line|#define UTS_NODENAME &quot;(none)&quot;&t;/* set by sethostname() */
macro_line|#endif
macro_line|#ifdef CONFIG_M486
DECL|macro|UTS_MACHINE
mdefine_line|#define UTS_MACHINE &quot;i486&quot;&t;/* hardware type */
macro_line|#else
DECL|macro|UTS_MACHINE
mdefine_line|#define UTS_MACHINE &quot;i386&quot;&t;/* hardware type */
macro_line|#endif
multiline_comment|/*&n; * The definitions for UTS_RELEASE and UTS_VERSION are now defined&n; * in linux/version.h, and should only be used by linux/version.c&n; */
multiline_comment|/* Don&squot;t touch these, unless you really know what your doing. */
DECL|macro|DEF_INITSEG
mdefine_line|#define DEF_INITSEG&t;0x9000
DECL|macro|DEF_SYSSEG
mdefine_line|#define DEF_SYSSEG&t;0x1000
DECL|macro|DEF_SETUPSEG
mdefine_line|#define DEF_SETUPSEG&t;0x9020
DECL|macro|DEF_SYSSIZE
mdefine_line|#define DEF_SYSSIZE&t;0x8000
multiline_comment|/* internal svga startup constants */
DECL|macro|NORMAL_VGA
mdefine_line|#define NORMAL_VGA&t;0xffff&t;&t;/* 80x25 mode */
DECL|macro|EXTENDED_VGA
mdefine_line|#define EXTENDED_VGA&t;0xfffe&t;&t;/* 80x50 mode */
DECL|macro|ASK_VGA
mdefine_line|#define ASK_VGA&t;&t;0xfffd&t;&t;/* ask for it at bootup */
multiline_comment|/*&n; * The root-device is no longer hard-coded. You can change the default&n; * root-device by changing the line ROOT_DEV = XXX in boot/bootsect.s&n; */
multiline_comment|/*&n; * The keyboard is now defined in kernel/chr_dev/keyboard.S&n; */
multiline_comment|/*&n; * Normally, Linux can get the drive parameters from the BIOS at&n; * startup, but if this for some unfathomable reason fails, you&squot;d&n; * be left stranded. For this case, you can define HD_TYPE, which&n; * contains all necessary info on your harddisk.&n; *&n; * The HD_TYPE macro should look like this:&n; *&n; * #define HD_TYPE { head, sect, cyl, wpcom, lzone, ctl}&n; *&n; * In case of two harddisks, the info should be sepatated by&n; * commas:&n; *&n; * #define HD_TYPE { h,s,c,wpcom,lz,ctl },{ h,s,c,wpcom,lz,ctl }&n; */
multiline_comment|/*&n; This is an example, two drives, first is type 2, second is type 3:&n;&n;#define HD_TYPE { 4,17,615,300,615,8 }, { 6,17,615,300,615,0 }&n;&n; NOTE: ctl is 0 for all drives with heads&lt;=8, and ctl=8 for drives&n; with more than 8 heads.&n;&n; If you want the BIOS to tell what kind of drive you have, just&n; leave HD_TYPE undefined. This is the normal thing to do.&n;*/
DECL|macro|HD_TYPE
macro_line|#undef HD_TYPE
multiline_comment|/*&n;&t;File type specific stuff goes into this.&n;*/
macro_line|#ifdef ASM_SRC
macro_line|#endif
macro_line|#ifdef C_SRC
macro_line|#endif
macro_line|#ifdef MAKE
macro_line|#endif
macro_line|#endif
eof
