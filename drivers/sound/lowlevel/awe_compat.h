multiline_comment|/*&n; * sound/awe_compat.h&n; *&n; * Compat defines for the AWE32/SB32/AWE64 wave table synth driver.&n; *   version 0.4.3; Oct. 1, 1998&n; *&n; * Copyright (C) 1996-1998 Takashi Iwai&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef AWE_COMPAT_H_DEF
DECL|macro|AWE_COMPAT_H_DEF
mdefine_line|#define AWE_COMPAT_H_DEF
multiline_comment|/*================================================================&n; * version check&n; *================================================================*/
macro_line|#include &quot;awe_config.h&quot;
DECL|macro|ASC_LINUX_VERSION
mdefine_line|#define ASC_LINUX_VERSION(V,P,S)    (((V) * 65536) + ((P) * 256) + (S))
macro_line|#ifndef LINUX_VERSION_CODE
macro_line|#include &lt;linux/version.h&gt;
macro_line|#endif
multiline_comment|/* linux version check */
macro_line|#if LINUX_VERSION_CODE &lt; ASC_LINUX_VERSION(2,0,0)
DECL|macro|AWE_OBSOLETE_VOXWARE
mdefine_line|#define AWE_OBSOLETE_VOXWARE
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt;= ASC_LINUX_VERSION(2,1,0)
DECL|macro|AWE_NEW_KERNEL_INTERFACE
mdefine_line|#define AWE_NEW_KERNEL_INTERFACE
macro_line|#if LINUX_VERSION_CODE &gt;= ASC_LINUX_VERSION(2,1,80)
DECL|macro|AWE_MODULE_SUPPORT
mdefine_line|#define AWE_MODULE_SUPPORT
macro_line|#endif
macro_line|#endif
macro_line|#ifdef AWE_OBSOLETE_VOXWARE
macro_line|#include &quot;soundvers.h&quot;
macro_line|#else
macro_line|#include &quot;../soundvers.h&quot;
macro_line|#endif
macro_line|#if SOUND_INTERNAL_VERSION &gt;= 0x30803
multiline_comment|/* OSS/Free-3.8 */
DECL|macro|AWE_NO_PATCHMGR
mdefine_line|#define AWE_NO_PATCHMGR
DECL|macro|AWE_OSS38
mdefine_line|#define AWE_OSS38
DECL|macro|HAS_LOWLEVEL_H
mdefine_line|#define HAS_LOWLEVEL_H
macro_line|#endif
multiline_comment|/*================================================================&n; * INCLUDE OTHER HEADER FILES&n; *================================================================*/
multiline_comment|/* set up module */
macro_line|#if defined(AWE_MODULE_SUPPORT) &amp;&amp; defined(MODULE)
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;../soundmodule.h&quot;
macro_line|#endif
multiline_comment|/* reading configuration of sound driver */
macro_line|#ifdef AWE_OBSOLETE_VOXWARE
macro_line|#include &quot;sound_config.h&quot;
macro_line|#if defined(CONFIGURE_SOUNDCARD) &amp;&amp; !defined(EXCLUDE_AWE32)
DECL|macro|CONFIG_AWE32_SYNTH
mdefine_line|#define CONFIG_AWE32_SYNTH
macro_line|#endif
macro_line|#else /* AWE_OBSOLETE_VOXWARE */
macro_line|#ifdef HAS_LOWLEVEL_H
macro_line|#include &quot;lowlevel.h&quot;
macro_line|#endif
macro_line|#include &quot;../sound_config.h&quot;
macro_line|#endif /* AWE_OBSOLETE_VOXWARE */
multiline_comment|/*================================================================&n; * include AWE header files&n; *================================================================*/
macro_line|#if defined(CONFIG_AWE32_SYNTH) || defined(CONFIG_AWE32_SYNTH_MODULE)
macro_line|#include &quot;awe_hw.h&quot;
macro_line|#include &quot;awe_version.h&quot;
macro_line|#include &lt;linux/awe_voice.h&gt;
macro_line|#ifdef AWE_HAS_GUS_COMPATIBILITY
multiline_comment|/* include finetune table */
macro_line|#ifdef AWE_OBSOLETE_VOXWARE
macro_line|#  include &quot;tuning.h&quot;
macro_line|#else
macro_line|#  include &quot;../tuning.h&quot;
macro_line|#endif
macro_line|#include &lt;linux/ultrasound.h&gt;
macro_line|#endif /* AWE_HAS_GUS_COMPATIBILITY */
multiline_comment|/*----------------------------------------------------------------&n; * compatibility macros for AWE32 driver&n; *----------------------------------------------------------------*/
multiline_comment|/* redefine following macros */
DECL|macro|IOCTL_IN
macro_line|#undef IOCTL_IN
DECL|macro|IOCTL_OUT
macro_line|#undef IOCTL_OUT
DECL|macro|OUTW
macro_line|#undef OUTW
DECL|macro|COPY_FROM_USER
macro_line|#undef COPY_FROM_USER
DECL|macro|COPY_TO_USER
macro_line|#undef COPY_TO_USER
DECL|macro|GET_BYTE_FROM_USER
macro_line|#undef GET_BYTE_FROM_USER
DECL|macro|GET_SHORT_FROM_USER
macro_line|#undef GET_SHORT_FROM_USER
DECL|macro|IOCTL_TO_USER
macro_line|#undef IOCTL_TO_USER
multiline_comment|/* use inline prefix */
DECL|macro|INLINE
mdefine_line|#define INLINE&t;/*inline*/
multiline_comment|/*----------------------------------------------------------------&n; * memory management for linux&n; *----------------------------------------------------------------*/
macro_line|#ifdef AWE_OBSOLETE_VOXWARE
multiline_comment|/* old type linux system */
multiline_comment|/* i/o requests; nothing */
DECL|macro|awe_check_port
mdefine_line|#define awe_check_port()&t;0&t;/* always false */
DECL|macro|awe_request_region
mdefine_line|#define awe_request_region()&t;/* nothing */
DECL|macro|awe_release_region
mdefine_line|#define awe_release_region()&t;/* nothing */
DECL|variable|_mem_start
r_static
r_int
id|_mem_start
suffix:semicolon
multiline_comment|/* memory pointer for permanent buffers */
DECL|macro|my_malloc_init
mdefine_line|#define my_malloc_init(memptr)&t;_mem_start = (memptr)
DECL|macro|my_malloc_memptr
mdefine_line|#define my_malloc_memptr()&t;_mem_start
DECL|macro|my_free
mdefine_line|#define my_free(ptr)&t;/* do nothing */
DECL|function|my_malloc
r_static
r_void
op_star
id|my_malloc
c_func
(paren
r_int
id|size
)paren
(brace
r_char
op_star
id|ptr
suffix:semicolon
id|PERMANENT_MALLOC
c_func
(paren
id|ptr
comma
r_char
op_star
comma
id|size
comma
id|_mem_start
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|ptr
suffix:semicolon
)brace
DECL|macro|my_kmalloc
mdefine_line|#define my_kmalloc(size) my_malloc(size)
DECL|macro|kfree
mdefine_line|#define kfree(ptr)&t;/* do nothing */
multiline_comment|/* allocate buffer only once */
DECL|macro|INIT_TABLE
mdefine_line|#define INIT_TABLE(buffer,index,nums,type) {&bslash;&n;buffer = my_malloc(sizeof(type) * (nums)); index = (nums);&bslash;&n;}
macro_line|#else
DECL|macro|AWE_DYNAMIC_BUFFER
mdefine_line|#define AWE_DYNAMIC_BUFFER
DECL|macro|my_malloc_init
mdefine_line|#define my_malloc_init(ptr)&t;/* nothing */
DECL|macro|my_malloc_memptr
mdefine_line|#define my_malloc_memptr()&t;0
DECL|macro|my_malloc
mdefine_line|#define my_malloc(size)&t;&t;vmalloc(size)
DECL|macro|my_free
mdefine_line|#define my_free(ptr)&t;&t;if (ptr) {vfree(ptr);}
DECL|macro|my_kmalloc
mdefine_line|#define my_kmalloc(size)&t;kmalloc(size,GFP_KERNEL)
DECL|macro|my_kfree
mdefine_line|#define my_kfree(ptr)&t;&t;kfree(ptr)
multiline_comment|/* do not allocate buffer at beginning */
DECL|macro|INIT_TABLE
mdefine_line|#define INIT_TABLE(buffer,index,nums,type) {buffer=NULL; index=0;}
multiline_comment|/* old type macro */
DECL|macro|RET_ERROR
mdefine_line|#define RET_ERROR(err)&t;&t;-err
macro_line|#endif
multiline_comment|/*----------------------------------------------------------------&n; * i/o interfaces for linux&n; *----------------------------------------------------------------*/
DECL|macro|OUTW
mdefine_line|#define OUTW(data,addr)&t;&t;outw(data, addr)
macro_line|#ifdef AWE_NEW_KERNEL_INTERFACE
DECL|macro|COPY_FROM_USER
mdefine_line|#define COPY_FROM_USER(target,source,offs,count) &bslash;&n;&t;copy_from_user(target, (source)+(offs), count)
DECL|macro|GET_BYTE_FROM_USER
mdefine_line|#define GET_BYTE_FROM_USER(target,addr,offs) &bslash;&n;&t;get_user(target, (unsigned char*)&amp;((addr)[offs]))
DECL|macro|GET_SHORT_FROM_USER
mdefine_line|#define GET_SHORT_FROM_USER(target,addr,offs) &bslash;&n;&t;get_user(target, (unsigned short*)&amp;((addr)[offs]))
macro_line|#ifdef AWE_OSS38
DECL|macro|IOCTL_TO_USER
mdefine_line|#define IOCTL_TO_USER(target,offs,source,count) &bslash;&n;&t;memcpy(target, (source)+(offs), count)
DECL|macro|IO_WRITE_CHECK
mdefine_line|#define IO_WRITE_CHECK(cmd)&t;(_SIOC_DIR(cmd) &amp; _IOC_WRITE)
macro_line|#else
DECL|macro|IOCTL_TO_USER
mdefine_line|#define IOCTL_TO_USER(target,offs,source,count) &bslash;&n;&t;copy_to_user(target, (source)+(offs), count)
DECL|macro|IO_WRITE_CHECK
mdefine_line|#define IO_WRITE_CHECK(cmd)&t;(_IOC_DIR(cmd) &amp; _IOC_WRITE)
macro_line|#endif /* AWE_OSS38 */
DECL|macro|COPY_TO_USER
mdefine_line|#define COPY_TO_USER&t;IOCTL_TO_USER
DECL|macro|IOCTL_IN
mdefine_line|#define IOCTL_IN(arg)&t;(*(int*)(arg))
DECL|macro|IOCTL_OUT
mdefine_line|#define IOCTL_OUT(arg,val) (*(int*)(arg) = (val))
macro_line|#else /* old type i/o */
DECL|macro|COPY_FROM_USER
mdefine_line|#define COPY_FROM_USER(target,source,offs,count) &bslash;&n;&t;memcpy_fromfs(target, (source)+(offs), (count))
DECL|macro|GET_BYTE_FROM_USER
mdefine_line|#define GET_BYTE_FROM_USER(target,addr,offs) &bslash;&n;&t;*((char  *)&amp;(target)) = get_fs_byte((addr)+(offs))
DECL|macro|GET_SHORT_FROM_USER
mdefine_line|#define GET_SHORT_FROM_USER(target,addr,offs) &bslash;&n;&t;*((short *)&amp;(target)) = get_fs_word((addr)+(offs))
macro_line|#ifdef AWE_OSS38
DECL|macro|IOCTL_TO_USER
mdefine_line|#define IOCTL_TO_USER(target,offs,source,count) &bslash;&n;&t;memcpy(target, (source)+(offs), count)
DECL|macro|COPY_TO_USER
mdefine_line|#define COPY_TO_USER(target,offs,source,count)  &bslash;&n;&t;memcpy_tofs(target, (source)+(offs), (count))
DECL|macro|IOCTL_IN
mdefine_line|#define IOCTL_IN(arg)&t;(*(int*)(arg))
DECL|macro|IOCTL_OUT
mdefine_line|#define IOCTL_OUT(arg,val) (*(int*)(arg) = (val))
DECL|macro|IO_WRITE_CHECK
mdefine_line|#define IO_WRITE_CHECK(cmd)&t;(_SIOC_DIR(cmd) &amp; _IOC_WRITE)
macro_line|#else /* AWE_OSS38 */
DECL|macro|IOCTL_TO_USER
mdefine_line|#define IOCTL_TO_USER(target,offs,source,count) &bslash;&n;&t;memcpy_tofs(target, (source)+(offs), (count))
DECL|macro|COPY_TO_USER
mdefine_line|#define COPY_TO_USER&t;IOCTL_TO_USER
DECL|macro|IOCTL_IN
mdefine_line|#define IOCTL_IN(arg)&t;&t;get_fs_long((long *)(arg))
DECL|macro|IOCTL_OUT
mdefine_line|#define IOCTL_OUT(arg,ret)&t;snd_ioctl_return((int *)arg, ret)
DECL|macro|IO_WRITE_CHECK
mdefine_line|#define IO_WRITE_CHECK(cmd)&t;(cmd &amp; IOC_IN)
macro_line|#endif /* AWE_OSS38 */
macro_line|#endif /* AWE_NEW_KERNEL_INTERFACE */
DECL|macro|BZERO
mdefine_line|#define BZERO(target,len)&t;memset(target, 0, len)
DECL|macro|MEMCPY
mdefine_line|#define MEMCPY(dst,src,len)&t;memcpy(dst, src, len)
DECL|macro|MEMCMP
mdefine_line|#define MEMCMP(p1,p2,len)&t;memcmp(p1, p2, len)
multiline_comment|/* old style device tables (not modulized) */
macro_line|#ifndef AWE_MODULE_SUPPORT
DECL|macro|sound_alloc_synthdev
mdefine_line|#define sound_alloc_synthdev() &bslash;&n;&t;(num_synths &gt;= MAX_SYNTH_DEV ? -1 : num_synths++)
DECL|macro|sound_alloc_mixerdev
mdefine_line|#define sound_alloc_mixerdev() &bslash;&n;&t;(num_mixers &gt;= MAX_MIXER_DEV ? -1 : num_mixers++)
DECL|macro|sound_alloc_mididev
mdefine_line|#define sound_alloc_mididev() &bslash;&n;&t;(num_midis &gt;= MAX_MIXER_DEV ? -1 : num_midis++)
DECL|macro|sound_unload_synthdev
mdefine_line|#define sound_unload_synthdev(dev)&t;/**/
DECL|macro|sound_unload_mixerdev
mdefine_line|#define sound_unload_mixerdev(dev)&t;/**/
DECL|macro|sound_unload_mididev
mdefine_line|#define sound_unload_mididev(dev)&t;/**/
macro_line|#endif /* AWE_MODULE_SUPPORT */
macro_line|#endif /* CONFIG_AWE32_SYNTH */
macro_line|#endif /* AWE_COMPAT_H_DEF */
eof
