multiline_comment|/*&n; * This file describes the structure passed from the BootX application&n; * (for MacOS) when it is used to boot Linux.&n; *&n; * Written by Benjamin Herrenschmidt.&n; */
macro_line|#ifndef __ASM_BOOTX_H__
DECL|macro|__ASM_BOOTX_H__
mdefine_line|#define __ASM_BOOTX_H__
macro_line|#ifdef macintosh
macro_line|#include &lt;Types.h&gt;
macro_line|#endif
macro_line|#ifdef macintosh
multiline_comment|/* All this requires PowerPC alignment */
macro_line|#pragma options align=power
macro_line|#endif
multiline_comment|/* On boostrap entry:&n; *&n; * r3 = 0x426f6f58&t;(&squot;BooX&squot;)&n; * r4 = pointer to boot_infos&n; * r5 = NULL&n; */
DECL|macro|BOOT_INFO_VERSION
mdefine_line|#define BOOT_INFO_VERSION&t;&t;2
DECL|macro|BOOT_INFO_COMPATIBLE_VERSION
mdefine_line|#define BOOT_INFO_COMPATIBLE_VERSION&t;1
multiline_comment|/* Here are the boot informations that are passed to the bootstrap&n; * Note that the kernel arguments and the device tree are appended&n; * at the end of this structure. */
DECL|struct|boot_infos
r_typedef
r_struct
id|boot_infos
(brace
multiline_comment|/* Version of this structure */
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
multiline_comment|/* backward compatible down to version: */
DECL|member|compatible_version
r_int
r_int
id|compatible_version
suffix:semicolon
multiline_comment|/* NEW (vers. 2) this holds the current _logical_ base addr of&n;&t;   the frame buffer (for use by early boot message) */
DECL|member|logicalDisplayBase
r_int
r_char
op_star
id|logicalDisplayBase
suffix:semicolon
multiline_comment|/* Set to 0 by current BootX */
DECL|member|unused
r_int
r_int
id|unused
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* The device tree (internal addresses relative to the beginning of the tree,&n;&t; * device tree offset relative to the beginning of this structure). */
DECL|member|deviceTreeOffset
r_int
r_int
id|deviceTreeOffset
suffix:semicolon
multiline_comment|/* Device tree offset */
DECL|member|deviceTreeSize
r_int
r_int
id|deviceTreeSize
suffix:semicolon
multiline_comment|/* Size of the device tree */
multiline_comment|/* Some infos about the current MacOS display */
DECL|member|dispDeviceRect
r_int
r_int
id|dispDeviceRect
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* left,top,right,bottom */
DECL|member|dispDeviceDepth
r_int
r_int
id|dispDeviceDepth
suffix:semicolon
multiline_comment|/* (8, 16 or 32) */
DECL|member|dispDeviceBase
r_int
r_char
op_star
id|dispDeviceBase
suffix:semicolon
multiline_comment|/* base address (physical) */
DECL|member|dispDeviceRowBytes
r_int
r_int
id|dispDeviceRowBytes
suffix:semicolon
multiline_comment|/* rowbytes (in bytes) */
DECL|member|dispDeviceColorsOffset
r_int
r_int
id|dispDeviceColorsOffset
suffix:semicolon
multiline_comment|/* Colormap (8 bits only) or 0 (*) */
multiline_comment|/* Optional offset in the registry to the current&n;&t; * MacOS display. (Can be 0 when not detected) */
DECL|member|dispDeviceRegEntryOffset
r_int
r_int
id|dispDeviceRegEntryOffset
suffix:semicolon
multiline_comment|/* Optional pointer to boot ramdisk (offset from this structure) */
DECL|member|ramDisk
r_int
r_int
id|ramDisk
suffix:semicolon
DECL|member|ramDiskSize
r_int
r_int
id|ramDiskSize
suffix:semicolon
multiline_comment|/* size of ramdisk image */
multiline_comment|/* Kernel command line arguments (offset from this structure) */
DECL|member|kernelParamsOffset
r_int
r_int
id|kernelParamsOffset
suffix:semicolon
DECL|typedef|boot_infos_t
)brace
id|boot_infos_t
suffix:semicolon
multiline_comment|/* (*) The format of the colormap is 256 * 3 * 2 bytes. Each color index is represented&n; * by 3 short words containing a 16 bits (unsigned) color component.&n; * Later versions may contain the gamma table for direct-color devices here.&n; */
DECL|macro|BOOTX_COLORTABLE_SIZE
mdefine_line|#define BOOTX_COLORTABLE_SIZE&t;(256UL*3UL*2UL)
macro_line|#ifdef macintosh
macro_line|#pragma options align=reset
macro_line|#endif
macro_line|#endif
eof
