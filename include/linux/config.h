macro_line|#ifndef _CONFIG_H
DECL|macro|_CONFIG_H
mdefine_line|#define _CONFIG_H
multiline_comment|/*&n; * Define this if you want the math-emulation code: if this is undefined,&n; * the kernel will be smaller, but you&squot;ll get FPU exceptions if you don&squot;t&n; * have a 387 and are trying to use math.&n; */
DECL|macro|KERNEL_MATH_EMULATION
mdefine_line|#define KERNEL_MATH_EMULATION
multiline_comment|/*&n; * Defines for what uname() should return &n; */
DECL|macro|UTS_SYSNAME
mdefine_line|#define UTS_SYSNAME &quot;Linux&quot;
DECL|macro|UTS_NODENAME
mdefine_line|#define UTS_NODENAME &quot;(none)&quot;&t;/* set by sethostname() */
DECL|macro|UTS_RELEASE
mdefine_line|#define UTS_RELEASE &quot;0&quot;&t;&t;/* patchlevel */
DECL|macro|UTS_VERSION
mdefine_line|#define UTS_VERSION &quot;0.95a&quot;
DECL|macro|UTS_MACHINE
mdefine_line|#define UTS_MACHINE &quot;i386&quot;&t;/* hardware type */
multiline_comment|/* Don&squot;t touch these, unless you really know what your doing. */
DECL|macro|DEF_INITSEG
mdefine_line|#define DEF_INITSEG&t;0x9000
DECL|macro|DEF_SYSSEG
mdefine_line|#define DEF_SYSSEG&t;0x1000
DECL|macro|DEF_SETUPSEG
mdefine_line|#define DEF_SETUPSEG&t;0x9020
DECL|macro|DEF_SYSSIZE
mdefine_line|#define DEF_SYSSIZE&t;0x4000
multiline_comment|/*&n; * The root-device is no longer hard-coded. You can change the default&n; * root-device by changing the line ROOT_DEV = XXX in boot/bootsect.s&n; */
multiline_comment|/*&n; * The keyboard is now defined in kernel/chr_dev/keyboard.S&n; */
multiline_comment|/*&n; * Normally, Linux can get the drive parameters from the BIOS at&n; * startup, but if this for some unfathomable reason fails, you&squot;d&n; * be left stranded. For this case, you can define HD_TYPE, which&n; * contains all necessary info on your harddisk.&n; *&n; * The HD_TYPE macro should look like this:&n; *&n; * #define HD_TYPE { head, sect, cyl, wpcom, lzone, ctl}&n; *&n; * In case of two harddisks, the info should be sepatated by&n; * commas:&n; *&n; * #define HD_TYPE { h,s,c,wpcom,lz,ctl },{ h,s,c,wpcom,lz,ctl }&n; */
multiline_comment|/*&n; This is an example, two drives, first is type 2, second is type 3:&n;&n;#define HD_TYPE { 4,17,615,300,615,8 }, { 6,17,615,300,615,0 }&n;&n; NOTE: ctl is 0 for all drives with heads&lt;=8, and ctl=8 for drives&n; with more than 8 heads.&n;&n; If you want the BIOS to tell what kind of drive you have, just&n; leave HD_TYPE undefined. This is the normal thing to do.&n;*/
macro_line|#endif
eof
