multiline_comment|/*&n; * sound/awe_compat.h&n; *&n; * Compat defines for the AWE32/SB32/AWE64 wave table synth driver.&n; *   version 0.4.3; Nov. 1, 1998&n; *&n; * Copyright (C) 1996-1998 Takashi Iwai&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#ifndef AWE_COMPAT_H_DEF
DECL|macro|AWE_COMPAT_H_DEF
mdefine_line|#define AWE_COMPAT_H_DEF
multiline_comment|/*================================================================&n; * version check&n; *================================================================*/
multiline_comment|/* FreeBSD version check */
macro_line|#include &lt;i386/isa/sound/awe_config.h&gt;
DECL|macro|AWE_OBSOLETE_VOXWARE
mdefine_line|#define AWE_OBSOLETE_VOXWARE
macro_line|#if __FreeBSD__ &gt;= 2
macro_line|#  include &lt;osreldate.h&gt;
macro_line|#  if __FreeBSD_version &gt;= 300000
DECL|macro|AWE_OBSOLETE_VOXWARE
macro_line|#    undef AWE_OBSOLETE_VOXWARE
macro_line|#  endif
macro_line|#endif
macro_line|#ifdef __linux__
macro_line|#  include &lt;linux/config.h&gt;
macro_line|#endif
multiline_comment|/*================================================================&n; * INCLUDE OTHER HEADER FILES&n; *================================================================*/
multiline_comment|/* reading configuration of sound driver */
macro_line|#ifdef AWE_OBSOLETE_VOXWARE
macro_line|#include &lt;i386/isa/sound/sound_config.h&gt;
macro_line|#if defined(CONFIGURE_SOUNDCARD) &amp;&amp; !defined(EXCLUDE_AWE32)
DECL|macro|CONFIG_AWE32_SYNTH
mdefine_line|#define CONFIG_AWE32_SYNTH
macro_line|#endif
macro_line|#else /* AWE_OBSOLETE_VOXWARE */
macro_line|#ifdef HAS_LOWLEVEL_H
macro_line|#include &quot;lowlevel.h&quot;
macro_line|#endif
macro_line|#include &lt;i386/isa/sound/sound_config.h&gt;
macro_line|#if defined(CONFIGURE_SOUNDCARD) &amp;&amp; defined(CONFIG_AWE32)
DECL|macro|CONFIG_AWE32_SYNTH
macro_line|#  define CONFIG_AWE32_SYNTH
macro_line|#endif
macro_line|#endif /* AWE_OBSOLETE_VOXWARE */
multiline_comment|/*================================================================&n; * include AWE header files&n; *================================================================*/
macro_line|#if defined(CONFIG_AWE32_SYNTH) || defined(CONFIG_AWE32_SYNTH_MODULE)
macro_line|#include &lt;i386/isa/sound/awe_hw.h&gt;
macro_line|#include &lt;i386/isa/sound/awe_version.h&gt;
macro_line|#include &lt;i386/isa/sound/awe_voice.h&gt;
macro_line|#ifdef AWE_HAS_GUS_COMPATIBILITY
multiline_comment|/* include finetune table */
macro_line|#ifdef AWE_OBSOLETE_VOXWARE
DECL|macro|SEQUENCER_C
macro_line|#  define SEQUENCER_C
macro_line|#endif
macro_line|#include &lt;i386/isa/sound/tuning.h&gt;
macro_line|#include &lt;machine/ultrasound.h&gt;
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
multiline_comment|/* inline is not checked yet.. maybe it&squot;ll work */
DECL|macro|INLINE
mdefine_line|#define INLINE&t;/*inline*/
DECL|macro|KERN_WARNING
mdefine_line|#define KERN_WARNING /**/
multiline_comment|/*----------------------------------------------------------------&n; * memory management for freebsd&n; *----------------------------------------------------------------*/
multiline_comment|/* i/o requests; nothing */
DECL|macro|awe_check_port
mdefine_line|#define awe_check_port()&t;0&t;/* always false */
DECL|macro|awe_request_region
mdefine_line|#define awe_request_region()&t;/* nothing */
DECL|macro|awe_release_region
mdefine_line|#define awe_release_region()&t;/* nothing */
DECL|macro|AWE_DYNAMIC_BUFFER
mdefine_line|#define AWE_DYNAMIC_BUFFER
DECL|macro|my_malloc_init
mdefine_line|#define my_malloc_init(ptr)&t;/* nothing */
DECL|macro|my_malloc_memptr
mdefine_line|#define my_malloc_memptr()&t;0
DECL|macro|my_malloc
mdefine_line|#define my_malloc(size)&t;&t;malloc(size, M_TEMP, M_WAITOK)
DECL|macro|my_free
mdefine_line|#define my_free(ptr)&t;&t;if (ptr) {free(ptr, M_TEMP);}
DECL|macro|INIT_TABLE
mdefine_line|#define INIT_TABLE(buffer,index,nums,type) {buffer=NULL; index=0;}
multiline_comment|/*----------------------------------------------------------------&n; * i/o interfaces for freebsd&n; *----------------------------------------------------------------*/
multiline_comment|/* according to linux rule; the arguments are swapped */
DECL|macro|OUTW
mdefine_line|#define OUTW(data,addr)&t;&t;outw(addr, data)
DECL|macro|COPY_FROM_USER
mdefine_line|#define COPY_FROM_USER(target,source,offs,count) &bslash;&n;&t;uiomove(((caddr_t)(target)),(count),((struct uio *)(source)))
DECL|macro|COPY_TO_USER
mdefine_line|#define COPY_TO_USER(target,source,offs,count) &bslash;&n;&t;uiomove(((caddr_t)(source)),(count),((struct uio *)(target)))
DECL|macro|GET_BYTE_FROM_USER
mdefine_line|#define GET_BYTE_FROM_USER(target,addr,offs) &bslash;&n;&t;uiomove(((char*)&amp;(target)), 1, ((struct uio *)(addr)))
DECL|macro|GET_SHORT_FROM_USER
mdefine_line|#define GET_SHORT_FROM_USER(target,addr,offs) &bslash;&n;&t;uiomove(((char*)&amp;(target)), 2, ((struct uio *)(addr)))
DECL|macro|IOCTL_TO_USER
mdefine_line|#define IOCTL_TO_USER(target,offs,source,count) &bslash;&n;&t;memcpy(&amp;((target)[offs]), (source), (count))
DECL|macro|IO_WRITE_CHECK
mdefine_line|#define IO_WRITE_CHECK(cmd)&t;(cmd &amp; IOC_IN)
DECL|macro|IOCTL_IN
mdefine_line|#define IOCTL_IN(arg)&t;&t;(*(int*)(arg))
DECL|macro|IOCTL_OUT
mdefine_line|#define IOCTL_OUT(arg,val)&t;(*(int*)(arg) = (val))
DECL|macro|BZERO
mdefine_line|#define BZERO(target,len)&t;bzero((caddr_t)target, len)
DECL|macro|MEMCPY
mdefine_line|#define MEMCPY(dst,src,len)&t;bcopy((caddr_t)src, (caddr_t)dst, len)
macro_line|#ifndef AWE_OBSOLETE_VOXWARE
DECL|macro|printk
macro_line|#  define printk printf
DECL|macro|RET_ERROR
macro_line|#  define RET_ERROR(err)&t;&t;-err
macro_line|#endif
multiline_comment|/* old style device tables (not modulized) */
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
macro_line|#endif /* CONFIG_AWE32_SYNTH */
macro_line|#endif /* AWE_COMPAT_H_DEF */
eof
