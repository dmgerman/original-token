macro_line|#ifndef _CONFIG_H
DECL|macro|_CONFIG_H
mdefine_line|#define _CONFIG_H
multiline_comment|/*&n; * The root-device is no longer hard-coded. You can change the default&n; * root-device by changing the line ROOT_DEV = XXX in boot/bootsect.s&n; */
multiline_comment|/* define your keyboard here - US (KBD_US) or Finnish (KBD_FINNISH) */
DECL|macro|KBD_US
mdefine_line|#define KBD_US
multiline_comment|/* #define KBD_FINNISH */
multiline_comment|/*&n; * Normally, Linux can get the drive parameters from the BIOS at&n; * startup, but if this for some unfathomable reason fails, you&squot;d&n; * be left stranded. For this case, you can define HD_TYPE, which&n; * contains all necessary info on your harddisk.&n; *&n; * The HD_TYPE macro should look like this:&n; *&n; * #define HD_TYPE { head, sect, cyl, wpcom, lzone, ctl}&n; *&n; * In case of two harddisks, the info should be sepatated by&n; * commas:&n; *&n; * #define HD_TYPE { h,s,c,wpcom,lz,ctl },{ h,s,c,wpcom,lz,ctl }&n; */
multiline_comment|/*&n; This is an example, two drives, first is type 2, second is type 3:&n;&n;#define HD_TYPE { 4,17,615,300,615,8 }, { 6,17,615,300,615,0 }&n;&n; NOTE: ctl is 0 for all drives with heads&lt;=8, and ctl=8 for drives&n; with more than 8 heads.&n;&n; If you want the BIOS to tell what kind of drive you have, just&n; leave HD_TYPE undefined.&n;*/
macro_line|#endif
eof
