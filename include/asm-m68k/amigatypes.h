multiline_comment|/*&n;** linux/amigatypes.h -- Types used in Amiga Linux kernel source&n;**&n;** Copyright 1992 by Greg Harp&n;**&n;** This file is subject to the terms and conditions of the GNU General Public&n;** License.  See the file README.legal in the main directory of this archive&n;** for more details.&n;**&n;** Created 09/29/92 by Greg Harp&n;**&n;** Moved all Zorro definitions to asm/zorro.h which is where they&n;** really belong - 24/11/95 Jes Sorensen&n;*/
macro_line|#ifndef _LINUX_AMIGATYPES_H_
DECL|macro|_LINUX_AMIGATYPES_H_
mdefine_line|#define _LINUX_AMIGATYPES_H_
macro_line|#ifdef __KERNEL__ /* only if compiling the kernel */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#endif
multiline_comment|/*&n; * Different models of Amiga&n; */
DECL|macro|AMI_UNKNOWN
mdefine_line|#define AMI_UNKNOWN&t;(0)
DECL|macro|AMI_500
mdefine_line|#define AMI_500&t;&t;(1)
DECL|macro|AMI_500PLUS
mdefine_line|#define AMI_500PLUS&t;(2)
DECL|macro|AMI_600
mdefine_line|#define AMI_600&t;&t;(3)
DECL|macro|AMI_1000
mdefine_line|#define AMI_1000&t;(4)
DECL|macro|AMI_1200
mdefine_line|#define AMI_1200&t;(5)
DECL|macro|AMI_2000
mdefine_line|#define AMI_2000&t;(6)
DECL|macro|AMI_2500
mdefine_line|#define AMI_2500&t;(7)
DECL|macro|AMI_3000
mdefine_line|#define AMI_3000&t;(8)
DECL|macro|AMI_3000T
mdefine_line|#define AMI_3000T&t;(9)
DECL|macro|AMI_3000PLUS
mdefine_line|#define AMI_3000PLUS&t;(10)
DECL|macro|AMI_4000
mdefine_line|#define AMI_4000&t;(11)
DECL|macro|AMI_4000T
mdefine_line|#define AMI_4000T&t;(12)
DECL|macro|AMI_CDTV
mdefine_line|#define AMI_CDTV&t;(13)
DECL|macro|AMI_CD32
mdefine_line|#define AMI_CD32&t;(14)
DECL|macro|AMI_DRACO
mdefine_line|#define AMI_DRACO&t;(15)
multiline_comment|/*&n; * chipsets&n; */
DECL|macro|CS_STONEAGE
mdefine_line|#define CS_STONEAGE (0)
DECL|macro|CS_OCS
mdefine_line|#define CS_OCS&t;    (1)
DECL|macro|CS_ECS
mdefine_line|#define CS_ECS&t;    (2)
DECL|macro|CS_AGA
mdefine_line|#define CS_AGA&t;    (3)
multiline_comment|/*&n; * Amiga clocks&n; */
r_extern
id|u_long
id|amiga_masterclock
suffix:semicolon
multiline_comment|/* 28 MHz */
r_extern
id|u_long
id|amiga_colorclock
suffix:semicolon
multiline_comment|/* 3.5 MHz */
DECL|macro|amiga_eclock
mdefine_line|#define amiga_eclock&t;boot_info.bi_amiga.eclock&t;/* 700 kHz */
macro_line|#endif /* asm-m68k/amigatypes.h */
eof
