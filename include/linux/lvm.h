multiline_comment|/*&n; * include/linux/lvm.h&n; * kernel/lvm.h&n; * tools/lib/lvm.h&n; *&n; * Copyright (C) 1997 - 2000  Heinz Mauelshagen, Sistina Software&n; *&n; * February-November 1997&n; * May-July 1998&n; * January-March,July,September,October,Dezember 1999&n; * January,February,July,November 2000&n; *&n; * lvm is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; * &n; * lvm is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA. &n; *&n; */
multiline_comment|/*&n; * Changelog&n; *&n; *    10/10/1997 - beginning of new structure creation&n; *    12/05/1998 - incorporated structures from lvm_v1.h and deleted lvm_v1.h&n; *    07/06/1998 - avoided LVM_KMALLOC_MAX define by using vmalloc/vfree&n; *                 instead of kmalloc/kfree&n; *    01/07/1998 - fixed wrong LVM_MAX_SIZE&n; *    07/07/1998 - extended pe_t structure by ios member (for statistic)&n; *    02/08/1998 - changes for official char/block major numbers&n; *    07/08/1998 - avoided init_module() and cleanup_module() to be static&n; *    29/08/1998 - seprated core and disk structure type definitions&n; *    01/09/1998 - merged kernel integration version (mike)&n; *    20/01/1999 - added LVM_PE_DISK_OFFSET macro for use in&n; *                 vg_read_with_pv_and_lv(), pv_move_pe(), pv_show_pe_text()...&n; *    18/02/1999 - added definition of time_disk_t structure for;&n; *                 keeps time stamps on disk for nonatomic writes (future)&n; *    15/03/1999 - corrected LV() and VG() macro definition to use argument&n; *                 instead of minor&n; *    03/07/1999 - define for genhd.c name handling&n; *    23/07/1999 - implemented snapshot part&n; *    08/12/1999 - changed LVM_LV_SIZE_MAX macro to reflect current 1TB limit&n; *    01/01/2000 - extended lv_v2 core structure by wait_queue member&n; *    12/02/2000 - integrated Andrea Arcagnelli&squot;s snapshot work&n; *    18/02/2000 - seperated user and kernel space parts by &n; *                 #ifdef them with __KERNEL__&n; *    08/03/2000 - implemented cluster/shared bits for vg_access&n; *    26/06/2000 - implemented snapshot persistency and resizing support&n; *    02/11/2000 - added hash table size member to lv structure&n; *    12/11/2000 - removed unneeded timestamp definitions&n; *&n; */
macro_line|#ifndef _LVM_H_INCLUDE
DECL|macro|_LVM_H_INCLUDE
mdefine_line|#define _LVM_H_INCLUDE
DECL|macro|_LVM_KERNEL_H_VERSION
mdefine_line|#define&t;_LVM_KERNEL_H_VERSION&t;&quot;LVM 0.9 (13/11/2000)&quot;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;endian.h&gt;
multiline_comment|/*&n; * preprocessor definitions&n; */
multiline_comment|/* if you like emergency reset code in the driver */
DECL|macro|LVM_TOTAL_RESET
mdefine_line|#define&t;LVM_TOTAL_RESET
macro_line|#ifdef __KERNEL__
DECL|macro|LVM_GET_INODE
mdefine_line|#define LVM_GET_INODE
DECL|macro|LVM_HD_NAME
macro_line|#undef&t;LVM_HD_NAME /* display nice names in /proc/partitions */
multiline_comment|/* lots of debugging output (see driver source)&n;   #define DEBUG_LVM_GET_INFO&n;   #define DEBUG&n;   #define DEBUG_MAP&n;   #define DEBUG_MAP_SIZE&n;   #define DEBUG_IOCTL&n;   #define DEBUG_READ&n;   #define DEBUG_GENDISK&n;   #define DEBUG_VG_CREATE&n;   #define DEBUG_LVM_BLK_OPEN&n;   #define DEBUG_KFREE&n; */
macro_line|#endif&t;&t;&t;&t;/* #ifdef __KERNEL__ */
macro_line|#ifndef __KERNEL__
DECL|macro|__KERNEL__
mdefine_line|#define __KERNEL__
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/list.h&gt;
DECL|macro|__KERNEL__
macro_line|#undef __KERNEL__
macro_line|#else
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#endif&t;&t;&t;&t;/* #ifndef __KERNEL__ */
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#endif&t;&t;&t;&t;/* #ifdef __KERNEL__ */
macro_line|#include &lt;asm/page.h&gt;
macro_line|#if !defined ( LVM_BLK_MAJOR) || !defined ( LVM_CHAR_MAJOR)
macro_line|#error Bad include/linux/major.h - LVM MAJOR undefined
macro_line|#endif
macro_line|#ifdef&t;BLOCK_SIZE
DECL|macro|BLOCK_SIZE
macro_line|#undef&t;BLOCK_SIZE
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_S390 
DECL|macro|BLOCK_SIZE
mdefine_line|#define BLOCK_SIZE&t;4096
macro_line|#else
DECL|macro|BLOCK_SIZE
mdefine_line|#define BLOCK_SIZE&t;1024
macro_line|#endif
macro_line|#ifndef&t;SECTOR_SIZE
DECL|macro|SECTOR_SIZE
mdefine_line|#define SECTOR_SIZE&t;512
macro_line|#endif
DECL|macro|LVM_STRUCT_VERSION
mdefine_line|#define LVM_STRUCT_VERSION&t;1&t;/* structure version */
DECL|macro|LVM_DIR_PREFIX
mdefine_line|#define&t;LVM_DIR_PREFIX&t;&quot;/dev/&quot;
macro_line|#ifndef min
DECL|macro|min
mdefine_line|#define min(a,b) (((a)&lt;(b))?(a):(b))
macro_line|#endif
macro_line|#ifndef max
DECL|macro|max
mdefine_line|#define max(a,b) (((a)&gt;(b))?(a):(b))
macro_line|#endif
multiline_comment|/* set the default structure version */
macro_line|#if ( LVM_STRUCT_VERSION == 1)
DECL|macro|pv_t
mdefine_line|#define pv_t pv_v2_t
DECL|macro|lv_t
mdefine_line|#define lv_t lv_v4_t
DECL|macro|vg_t
mdefine_line|#define vg_t vg_v3_t
DECL|macro|pv_disk_t
mdefine_line|#define pv_disk_t pv_disk_v2_t
DECL|macro|lv_disk_t
mdefine_line|#define lv_disk_t lv_disk_v3_t
DECL|macro|vg_disk_t
mdefine_line|#define vg_disk_t vg_disk_v2_t
DECL|macro|lv_block_exception_t
mdefine_line|#define lv_block_exception_t lv_block_exception_v1_t
DECL|macro|lv_COW_table_disk_t
mdefine_line|#define lv_COW_table_disk_t lv_COW_table_disk_v1_t
macro_line|#endif
multiline_comment|/*&n; * i/o protocol version&n; *&n; * defined here for the driver and defined seperate in the&n; * user land tools/lib/liblvm.h&n; *&n; */
DECL|macro|LVM_DRIVER_IOP_VERSION
mdefine_line|#define&t;LVM_DRIVER_IOP_VERSION&t;        10
DECL|macro|LVM_NAME
mdefine_line|#define LVM_NAME        &quot;lvm&quot;
DECL|macro|LVM_GLOBAL
mdefine_line|#define LVM_GLOBAL&t;&quot;global&quot;
DECL|macro|LVM_DIR
mdefine_line|#define LVM_DIR&t;&t;&quot;lvm&quot;
DECL|macro|LVM_VG_SUBDIR
mdefine_line|#define LVM_VG_SUBDIR&t;&quot;VGs&quot;
DECL|macro|LVM_LV_SUBDIR
mdefine_line|#define LVM_LV_SUBDIR&t;&quot;LVs&quot;
DECL|macro|LVM_PV_SUBDIR
mdefine_line|#define LVM_PV_SUBDIR&t;&quot;PVs&quot;
multiline_comment|/*&n; * VG/LV indexing macros&n; */
multiline_comment|/* character minor maps directly to volume group */
DECL|macro|VG_CHR
mdefine_line|#define&t;VG_CHR(a) ( a)
multiline_comment|/* block minor indexes into a volume group/logical volume indirection table */
DECL|macro|VG_BLK
mdefine_line|#define&t;VG_BLK(a)&t;( vg_lv_map[a].vg_number)
DECL|macro|LV_BLK
mdefine_line|#define LV_BLK(a)&t;( vg_lv_map[a].lv_number)
multiline_comment|/*&n; * absolute limits for VGs, PVs per VG and LVs per VG&n; */
DECL|macro|ABS_MAX_VG
mdefine_line|#define ABS_MAX_VG&t;99
DECL|macro|ABS_MAX_PV
mdefine_line|#define ABS_MAX_PV&t;256
DECL|macro|ABS_MAX_LV
mdefine_line|#define ABS_MAX_LV&t;256&t;/* caused by 8 bit minor */
DECL|macro|MAX_VG
mdefine_line|#define MAX_VG  ABS_MAX_VG
DECL|macro|MAX_LV
mdefine_line|#define MAX_LV&t;ABS_MAX_LV
DECL|macro|MAX_PV
mdefine_line|#define&t;MAX_PV&t;ABS_MAX_PV
macro_line|#if ( MAX_VG &gt; ABS_MAX_VG)
DECL|macro|MAX_VG
macro_line|#undef MAX_VG
DECL|macro|MAX_VG
mdefine_line|#define MAX_VG ABS_MAX_VG
macro_line|#endif
macro_line|#if ( MAX_LV &gt; ABS_MAX_LV)
DECL|macro|MAX_LV
macro_line|#undef MAX_LV
DECL|macro|MAX_LV
mdefine_line|#define MAX_LV ABS_MAX_LV
macro_line|#endif
multiline_comment|/*&n; * VGDA: default disk spaces and offsets&n; *&n; *   there&squot;s space after the structures for later extensions.&n; *&n; *   offset            what                                size&n; *   ---------------   ----------------------------------  ------------&n; *   0                 physical volume structure           ~500 byte&n; *&n; *   1K                volume group structure              ~200 byte&n; *&n; *   5K                time stamp structure                ~&n; *&n; *   6K                namelist of physical volumes        128 byte each&n; *&n; *   6k + n * 128byte  n logical volume structures         ~300 byte each&n; *&n; *   + m * 328byte     m physical extent alloc. structs    4 byte each&n; *&n; *   End of disk -     first physical extent               typical 4 megabyte&n; *   PE total *&n; *   PE size&n; *&n; *&n; */
multiline_comment|/* DONT TOUCH THESE !!! */
multiline_comment|/* base of PV structure in disk partition */
DECL|macro|LVM_PV_DISK_BASE
mdefine_line|#define&t;LVM_PV_DISK_BASE  &t;0L
multiline_comment|/* size reserved for PV structure on disk */
DECL|macro|LVM_PV_DISK_SIZE
mdefine_line|#define&t;LVM_PV_DISK_SIZE  &t;1024L
multiline_comment|/* base of VG structure in disk partition */
DECL|macro|LVM_VG_DISK_BASE
mdefine_line|#define&t;LVM_VG_DISK_BASE  &t;LVM_PV_DISK_SIZE
multiline_comment|/* size reserved for VG structure */
DECL|macro|LVM_VG_DISK_SIZE
mdefine_line|#define&t;LVM_VG_DISK_SIZE  &t;( 9 * 512L)
multiline_comment|/* size reserved for timekeeping */
DECL|macro|LVM_TIMESTAMP_DISK_BASE
mdefine_line|#define&t;LVM_TIMESTAMP_DISK_BASE&t;( LVM_VG_DISK_BASE +  LVM_VG_DISK_SIZE)
DECL|macro|LVM_TIMESTAMP_DISK_SIZE
mdefine_line|#define&t;LVM_TIMESTAMP_DISK_SIZE&t;512L&t;/* reserved for timekeeping */
multiline_comment|/* name list of physical volumes on disk */
DECL|macro|LVM_PV_UUIDLIST_DISK_BASE
mdefine_line|#define&t;LVM_PV_UUIDLIST_DISK_BASE ( LVM_TIMESTAMP_DISK_BASE + &bslash;&n;                                    LVM_TIMESTAMP_DISK_SIZE)
multiline_comment|/* now for the dynamically calculated parts of the VGDA */
DECL|macro|LVM_LV_DISK_OFFSET
mdefine_line|#define&t;LVM_LV_DISK_OFFSET(a, b) ( (a)-&gt;lv_on_disk.base + &bslash;&n;                                   sizeof ( lv_disk_t) * b)
DECL|macro|LVM_DISK_SIZE
mdefine_line|#define&t;LVM_DISK_SIZE(pv) &t; ( (pv)-&gt;pe_on_disk.base + &bslash;&n;                                   (pv)-&gt;pe_on_disk.size)
DECL|macro|LVM_PE_DISK_OFFSET
mdefine_line|#define&t;LVM_PE_DISK_OFFSET(pe, pv)&t;( pe * pv-&gt;pe_size + &bslash;&n;&t;&t;&t;&t;&t;  ( LVM_DISK_SIZE ( pv) / SECTOR_SIZE))
DECL|macro|LVM_PE_ON_DISK_BASE
mdefine_line|#define&t;LVM_PE_ON_DISK_BASE(pv) &bslash;&n;   { int rest; &bslash;&n;     pv-&gt;pe_on_disk.base = pv-&gt;lv_on_disk.base + pv-&gt;lv_on_disk.size; &bslash;&n;     if ( ( rest = pv-&gt;pe_on_disk.base % SECTOR_SIZE) != 0) &bslash;&n;        pv-&gt;pe_on_disk.base += ( SECTOR_SIZE - rest); &bslash;&n;   }
multiline_comment|/* END default disk spaces and offsets for PVs */
multiline_comment|/*&n; * LVM_PE_T_MAX corresponds to:&n; *&n; * 8KB PE size can map a ~512 MB logical volume at the cost of 1MB memory,&n; *&n; * 128MB PE size can map a 8TB logical volume at the same cost of memory.&n; *&n; * Default PE size of 4 MB gives a maximum logical volume size of 256 GB.&n; *&n; * Maximum PE size of 16GB gives a maximum logical volume size of 1024 TB.&n; *&n; * AFAIK, the actual kernels limit this to 1 TB.&n; *&n; * Should be a sufficient spectrum ;*)&n; */
multiline_comment|/* This is the usable size of pe_disk_t.le_num !!!        v     v */
DECL|macro|LVM_PE_T_MAX
mdefine_line|#define&t;LVM_PE_T_MAX&t;&t;( ( 1 &lt;&lt; ( sizeof ( uint16_t) * 8)) - 2)
DECL|macro|LVM_LV_SIZE_MAX
mdefine_line|#define&t;LVM_LV_SIZE_MAX(a)&t;( ( long long) LVM_PE_T_MAX * (a)-&gt;pe_size &gt; ( long long) 1024*1024/SECTOR_SIZE*1024*1024 ? ( long long) 1024*1024/SECTOR_SIZE*1024*1024 : ( long long) LVM_PE_T_MAX * (a)-&gt;pe_size)
DECL|macro|LVM_MIN_PE_SIZE
mdefine_line|#define&t;LVM_MIN_PE_SIZE&t;&t;( 8192L / SECTOR_SIZE) /* 8 KB in sectors */
DECL|macro|LVM_MAX_PE_SIZE
mdefine_line|#define&t;LVM_MAX_PE_SIZE&t;&t;( 16L * 1024L * 1024L / SECTOR_SIZE * 1024)&t;/* 16GB in sectors */
DECL|macro|LVM_DEFAULT_PE_SIZE
mdefine_line|#define&t;LVM_DEFAULT_PE_SIZE&t;( 4096L * 1024 / SECTOR_SIZE)&t;/* 4 MB in sectors */
DECL|macro|LVM_DEFAULT_STRIPE_SIZE
mdefine_line|#define&t;LVM_DEFAULT_STRIPE_SIZE&t;16L&t;/* 16 KB  */
DECL|macro|LVM_MIN_STRIPE_SIZE
mdefine_line|#define&t;LVM_MIN_STRIPE_SIZE&t;( PAGE_SIZE&gt;&gt;9)&t;&t;/* PAGESIZE in sectors */
DECL|macro|LVM_MAX_STRIPE_SIZE
mdefine_line|#define&t;LVM_MAX_STRIPE_SIZE&t;( 512L * 1024 / SECTOR_SIZE)&t;/* 512 KB in sectors */
DECL|macro|LVM_MAX_STRIPES
mdefine_line|#define&t;LVM_MAX_STRIPES&t;&t;128&t;/* max # of stripes */
DECL|macro|LVM_MAX_SIZE
mdefine_line|#define&t;LVM_MAX_SIZE            ( 1024LU * 1024 / SECTOR_SIZE * 1024 * 1024)&t;/* 1TB[sectors] */
DECL|macro|LVM_MAX_MIRRORS
mdefine_line|#define&t;LVM_MAX_MIRRORS    &t;2&t;/* future use */
DECL|macro|LVM_MIN_READ_AHEAD
mdefine_line|#define&t;LVM_MIN_READ_AHEAD&t;2&t;/* minimum read ahead sectors */
DECL|macro|LVM_MAX_READ_AHEAD
mdefine_line|#define&t;LVM_MAX_READ_AHEAD&t;120&t;/* maximum read ahead sectors */
DECL|macro|LVM_MAX_LV_IO_TIMEOUT
mdefine_line|#define&t;LVM_MAX_LV_IO_TIMEOUT&t;60&t;/* seconds I/O timeout (future use) */
DECL|macro|LVM_PARTITION
mdefine_line|#define&t;LVM_PARTITION           0xfe&t;/* LVM partition id */
DECL|macro|LVM_NEW_PARTITION
mdefine_line|#define&t;LVM_NEW_PARTITION       0x8e&t;/* new LVM partition id (10/09/1999) */
DECL|macro|LVM_PE_SIZE_PV_SIZE_REL
mdefine_line|#define&t;LVM_PE_SIZE_PV_SIZE_REL&t;5&t;/* max relation PV size and PE size */
DECL|macro|LVM_SNAPSHOT_MAX_CHUNK
mdefine_line|#define&t;LVM_SNAPSHOT_MAX_CHUNK&t;1024&t;/* 1024 KB */
DECL|macro|LVM_SNAPSHOT_DEF_CHUNK
mdefine_line|#define&t;LVM_SNAPSHOT_DEF_CHUNK&t;64&t;/* 64  KB */
DECL|macro|LVM_SNAPSHOT_MIN_CHUNK
mdefine_line|#define&t;LVM_SNAPSHOT_MIN_CHUNK&t;1&t;/* 1   KB */
DECL|macro|UNDEF
mdefine_line|#define&t;UNDEF&t;-1
DECL|macro|FALSE
mdefine_line|#define FALSE&t;0
DECL|macro|TRUE
mdefine_line|#define TRUE&t;1
DECL|macro|LVM_GET_COW_TABLE_CHUNKS_PER_PE
mdefine_line|#define LVM_GET_COW_TABLE_CHUNKS_PER_PE(vg, lv) ( &bslash;&n;&t;vg-&gt;pe_size / lv-&gt;lv_chunk_size)
DECL|macro|LVM_GET_COW_TABLE_ENTRIES_PER_PE
mdefine_line|#define LVM_GET_COW_TABLE_ENTRIES_PER_PE(vg, lv) ( &bslash;&n;{ &bslash;&n;&t;int COW_table_entries_per_PE; &bslash;&n;&t;int COW_table_chunks_per_PE; &bslash;&n;&bslash;&n;&t;COW_table_entries_per_PE = LVM_GET_COW_TABLE_CHUNKS_PER_PE(vg, lv); &bslash;&n;&t;COW_table_chunks_per_PE = ( COW_table_entries_per_PE * sizeof(lv_COW_table_disk_t) / SECTOR_SIZE + lv-&gt;lv_chunk_size - 1) / lv-&gt;lv_chunk_size; &bslash;&n;&t;COW_table_entries_per_PE - COW_table_chunks_per_PE;})
multiline_comment|/* to disk and to core data conversion macros */
macro_line|#if __BYTE_ORDER == __BIG_ENDIAN
DECL|macro|LVM_TO_CORE16
mdefine_line|#define LVM_TO_CORE16(x) ( &bslash;&n;        ((uint16_t)((((uint16_t)(x) &amp; 0x00FFU) &lt;&lt; 8) | &bslash;&n;                    (((uint16_t)(x) &amp; 0xFF00U) &gt;&gt; 8))))
DECL|macro|LVM_TO_DISK16
mdefine_line|#define LVM_TO_DISK16(x) LVM_TO_CORE16(x)
DECL|macro|LVM_TO_CORE32
mdefine_line|#define LVM_TO_CORE32(x) ( &bslash;&n;        ((uint32_t)((((uint32_t)(x) &amp; 0x000000FFU) &lt;&lt; 24) | &bslash;&n;                    (((uint32_t)(x) &amp; 0x0000FF00U) &lt;&lt; 8))) &bslash;&n;                    (((uint32_t)(x) &amp; 0x00FF0000U) &gt;&gt; 8))) &bslash;&n;                    (((uint32_t)(x) &amp; 0xFF000000U) &gt;&gt; 24))))
DECL|macro|LVM_TO_DISK32
mdefine_line|#define LVM_TO_DISK32(x) LVM_TO_CORE32(x)
DECL|macro|LVM_TO_CORE64
mdefine_line|#define LVM_TO_CORE64(x) &bslash;&n;        ((uint64_t)((((uint64_t)(x) &amp; 0x00000000000000FFULL) &lt;&lt; 56) | &bslash;&n;                    (((uint64_t)(x) &amp; 0x000000000000FF00ULL) &lt;&lt; 40) | &bslash;&n;                    (((uint64_t)(x) &amp; 0x0000000000FF0000ULL) &lt;&lt; 24) | &bslash;&n;                    (((uint64_t)(x) &amp; 0x00000000FF000000ULL) &lt;&lt;  8) | &bslash;&n;                    (((uint64_t)(x) &amp; 0x000000FF00000000ULL) &gt;&gt;  8) | &bslash;&n;                    (((uint64_t)(x) &amp; 0x0000FF0000000000ULL) &gt;&gt; 24) | &bslash;&n;                    (((uint64_t)(x) &amp; 0x00FF000000000000ULL) &gt;&gt; 40) | &bslash;&n;                    (((uint64_t)(x) &amp; 0xFF00000000000000ULL) &gt;&gt; 56))) 
DECL|macro|LVM_TO_DISK64
mdefine_line|#define LVM_TO_DISK64(x) LVM_TO_CORE64(x)
macro_line|#elif __BYTE_ORDER == __LITTLE_ENDIAN
DECL|macro|LVM_TO_CORE16
mdefine_line|#define LVM_TO_CORE16(x) x
DECL|macro|LVM_TO_DISK16
mdefine_line|#define LVM_TO_DISK16(x) x
DECL|macro|LVM_TO_CORE32
mdefine_line|#define LVM_TO_CORE32(x) x
DECL|macro|LVM_TO_DISK32
mdefine_line|#define LVM_TO_DISK32(x) x
DECL|macro|LVM_TO_CORE64
mdefine_line|#define LVM_TO_CORE64(x) x
DECL|macro|LVM_TO_DISK64
mdefine_line|#define LVM_TO_DISK64(x) x
macro_line|#else
macro_line|#error &quot;__BYTE_ORDER must be defined as __LITTLE_ENDIAN or __BIG_ENDIAN&quot;
macro_line|#endif /* #if __BYTE_ORDER == __BIG_ENDIAN */
multiline_comment|/*&n; * ioctls&n; */
multiline_comment|/* volume group */
DECL|macro|VG_CREATE
mdefine_line|#define&t;VG_CREATE               _IOW ( 0xfe, 0x00, 1)
DECL|macro|VG_REMOVE
mdefine_line|#define&t;VG_REMOVE               _IOW ( 0xfe, 0x01, 1)
DECL|macro|VG_EXTEND
mdefine_line|#define&t;VG_EXTEND               _IOW ( 0xfe, 0x03, 1)
DECL|macro|VG_REDUCE
mdefine_line|#define&t;VG_REDUCE               _IOW ( 0xfe, 0x04, 1)
DECL|macro|VG_STATUS
mdefine_line|#define&t;VG_STATUS               _IOWR ( 0xfe, 0x05, 1)
DECL|macro|VG_STATUS_GET_COUNT
mdefine_line|#define&t;VG_STATUS_GET_COUNT     _IOWR ( 0xfe, 0x06, 1)
DECL|macro|VG_STATUS_GET_NAMELIST
mdefine_line|#define&t;VG_STATUS_GET_NAMELIST  _IOWR ( 0xfe, 0x07, 1)
DECL|macro|VG_SET_EXTENDABLE
mdefine_line|#define&t;VG_SET_EXTENDABLE       _IOW ( 0xfe, 0x08, 1)
DECL|macro|VG_RENAME
mdefine_line|#define&t;VG_RENAME&t;&t;_IOW ( 0xfe, 0x09, 1)
multiline_comment|/* logical volume */
DECL|macro|LV_CREATE
mdefine_line|#define&t;LV_CREATE               _IOW ( 0xfe, 0x20, 1)
DECL|macro|LV_REMOVE
mdefine_line|#define&t;LV_REMOVE               _IOW ( 0xfe, 0x21, 1)
DECL|macro|LV_ACTIVATE
mdefine_line|#define&t;LV_ACTIVATE             _IO ( 0xfe, 0x22)
DECL|macro|LV_DEACTIVATE
mdefine_line|#define&t;LV_DEACTIVATE           _IO ( 0xfe, 0x23)
DECL|macro|LV_EXTEND
mdefine_line|#define&t;LV_EXTEND               _IOW ( 0xfe, 0x24, 1)
DECL|macro|LV_REDUCE
mdefine_line|#define&t;LV_REDUCE               _IOW ( 0xfe, 0x25, 1)
DECL|macro|LV_STATUS_BYNAME
mdefine_line|#define&t;LV_STATUS_BYNAME        _IOWR ( 0xfe, 0x26, 1)
DECL|macro|LV_STATUS_BYINDEX
mdefine_line|#define&t;LV_STATUS_BYINDEX       _IOWR ( 0xfe, 0x27, 1)
DECL|macro|LV_SET_ACCESS
mdefine_line|#define LV_SET_ACCESS           _IOW ( 0xfe, 0x28, 1)
DECL|macro|LV_SET_ALLOCATION
mdefine_line|#define LV_SET_ALLOCATION       _IOW ( 0xfe, 0x29, 1)
DECL|macro|LV_SET_STATUS
mdefine_line|#define LV_SET_STATUS           _IOW ( 0xfe, 0x2a, 1)
DECL|macro|LE_REMAP
mdefine_line|#define LE_REMAP                _IOW ( 0xfe, 0x2b, 1)
DECL|macro|LV_SNAPSHOT_USE_RATE
mdefine_line|#define LV_SNAPSHOT_USE_RATE    _IOWR ( 0xfe, 0x2c, 1)
DECL|macro|LV_STATUS_BYDEV
mdefine_line|#define&t;LV_STATUS_BYDEV&t;&t;_IOWR ( 0xfe, 0x2e, 1)
DECL|macro|LV_RENAME
mdefine_line|#define&t;LV_RENAME&t;&t;_IOW ( 0xfe, 0x2f, 1)
DECL|macro|LV_BMAP
mdefine_line|#define&t;LV_BMAP&t;&t;&t;_IOWR ( 0xfe, 0x30, 1)
multiline_comment|/* physical volume */
DECL|macro|PV_STATUS
mdefine_line|#define&t;PV_STATUS               _IOWR ( 0xfe, 0x40, 1)
DECL|macro|PV_CHANGE
mdefine_line|#define&t;PV_CHANGE               _IOWR ( 0xfe, 0x41, 1)
DECL|macro|PV_FLUSH
mdefine_line|#define&t;PV_FLUSH                _IOW ( 0xfe, 0x42, 1)
multiline_comment|/* physical extent */
DECL|macro|PE_LOCK_UNLOCK
mdefine_line|#define&t;PE_LOCK_UNLOCK          _IOW ( 0xfe, 0x50, 1)
multiline_comment|/* i/o protocol version */
DECL|macro|LVM_GET_IOP_VERSION
mdefine_line|#define&t;LVM_GET_IOP_VERSION     _IOR ( 0xfe, 0x98, 1)
macro_line|#ifdef LVM_TOTAL_RESET
multiline_comment|/* special reset function for testing purposes */
DECL|macro|LVM_RESET
mdefine_line|#define&t;LVM_RESET               _IO ( 0xfe, 0x99)
macro_line|#endif
multiline_comment|/* lock the logical volume manager */
DECL|macro|LVM_LOCK_LVM
mdefine_line|#define&t;LVM_LOCK_LVM            _IO ( 0xfe, 0x100)
multiline_comment|/* END ioctls */
multiline_comment|/*&n; * Status flags&n; */
multiline_comment|/* volume group */
DECL|macro|VG_ACTIVE
mdefine_line|#define&t;VG_ACTIVE            0x01&t;/* vg_status */
DECL|macro|VG_EXPORTED
mdefine_line|#define&t;VG_EXPORTED          0x02&t;/*     &quot;     */
DECL|macro|VG_EXTENDABLE
mdefine_line|#define&t;VG_EXTENDABLE        0x04&t;/*     &quot;     */
DECL|macro|VG_READ
mdefine_line|#define&t;VG_READ              0x01&t;/* vg_access */
DECL|macro|VG_WRITE
mdefine_line|#define&t;VG_WRITE             0x02&t;/*     &quot;     */
DECL|macro|VG_CLUSTERED
mdefine_line|#define&t;VG_CLUSTERED         0x04&t;/*     &quot;     */
DECL|macro|VG_SHARED
mdefine_line|#define&t;VG_SHARED            0x08&t;/*     &quot;     */
multiline_comment|/* logical volume */
DECL|macro|LV_ACTIVE
mdefine_line|#define&t;LV_ACTIVE            0x01&t;/* lv_status */
DECL|macro|LV_SPINDOWN
mdefine_line|#define&t;LV_SPINDOWN          0x02&t;/*     &quot;     */
DECL|macro|LV_READ
mdefine_line|#define&t;LV_READ              0x01&t;/* lv_access */
DECL|macro|LV_WRITE
mdefine_line|#define&t;LV_WRITE             0x02&t;/*     &quot;     */
DECL|macro|LV_SNAPSHOT
mdefine_line|#define&t;LV_SNAPSHOT          0x04&t;/*     &quot;     */
DECL|macro|LV_SNAPSHOT_ORG
mdefine_line|#define&t;LV_SNAPSHOT_ORG      0x08&t;/*     &quot;     */
DECL|macro|LV_BADBLOCK_ON
mdefine_line|#define&t;LV_BADBLOCK_ON       0x01&t;/* lv_badblock */
DECL|macro|LV_STRICT
mdefine_line|#define&t;LV_STRICT            0x01&t;/* lv_allocation */
DECL|macro|LV_CONTIGUOUS
mdefine_line|#define&t;LV_CONTIGUOUS        0x02&t;/*       &quot;       */
multiline_comment|/* physical volume */
DECL|macro|PV_ACTIVE
mdefine_line|#define&t;PV_ACTIVE            0x01&t;/* pv_status */
DECL|macro|PV_ALLOCATABLE
mdefine_line|#define&t;PV_ALLOCATABLE       0x02&t;/* pv_allocatable */
multiline_comment|/*&n; * Structure definitions core/disk follow&n; *&n; * conditional conversion takes place on big endian architectures&n; * in functions * pv_copy_*(), vg_copy_*() and lv_copy_*()&n; *&n; */
DECL|macro|NAME_LEN
mdefine_line|#define&t;NAME_LEN&t;&t;128&t;/* don&squot;t change!!! */
DECL|macro|UUID_LEN
mdefine_line|#define&t;UUID_LEN&t;&t;32&t;/* don&squot;t change!!! */
multiline_comment|/* copy on write tables in disk format */
r_typedef
r_struct
(brace
DECL|member|pv_org_number
r_uint64
id|pv_org_number
suffix:semicolon
DECL|member|pv_org_rsector
r_uint64
id|pv_org_rsector
suffix:semicolon
DECL|member|pv_snap_number
r_uint64
id|pv_snap_number
suffix:semicolon
DECL|member|pv_snap_rsector
r_uint64
id|pv_snap_rsector
suffix:semicolon
DECL|typedef|lv_COW_table_disk_v1_t
)brace
id|lv_COW_table_disk_v1_t
suffix:semicolon
multiline_comment|/* remap physical sector/rdev pairs including hash */
r_typedef
r_struct
(brace
DECL|member|hash
r_struct
id|list_head
id|hash
suffix:semicolon
DECL|member|rsector_org
id|ulong
id|rsector_org
suffix:semicolon
DECL|member|rdev_org
id|kdev_t
id|rdev_org
suffix:semicolon
DECL|member|rsector_new
id|ulong
id|rsector_new
suffix:semicolon
DECL|member|rdev_new
id|kdev_t
id|rdev_new
suffix:semicolon
DECL|typedef|lv_block_exception_v1_t
)brace
id|lv_block_exception_v1_t
suffix:semicolon
multiline_comment|/* disk stored pe information */
r_typedef
r_struct
(brace
DECL|member|lv_num
r_uint16
id|lv_num
suffix:semicolon
DECL|member|le_num
r_uint16
id|le_num
suffix:semicolon
DECL|typedef|pe_disk_t
)brace
id|pe_disk_t
suffix:semicolon
multiline_comment|/* disk stored PV, VG, LV and PE size and offset information */
r_typedef
r_struct
(brace
DECL|member|base
r_uint32
id|base
suffix:semicolon
DECL|member|size
r_uint32
id|size
suffix:semicolon
DECL|typedef|lvm_disk_data_t
)brace
id|lvm_disk_data_t
suffix:semicolon
multiline_comment|/*&n; * Structure Physical Volume (PV) Version 1&n; */
multiline_comment|/* core */
r_typedef
r_struct
(brace
DECL|member|id
r_char
id|id
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Identifier */
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
multiline_comment|/* HM lvm version */
DECL|member|pv_on_disk
id|lvm_disk_data_t
id|pv_on_disk
suffix:semicolon
DECL|member|vg_on_disk
id|lvm_disk_data_t
id|vg_on_disk
suffix:semicolon
DECL|member|pv_namelist_on_disk
id|lvm_disk_data_t
id|pv_namelist_on_disk
suffix:semicolon
DECL|member|lv_on_disk
id|lvm_disk_data_t
id|lv_on_disk
suffix:semicolon
DECL|member|pe_on_disk
id|lvm_disk_data_t
id|pe_on_disk
suffix:semicolon
DECL|member|pv_name
r_char
id|pv_name
(braket
id|NAME_LEN
)braket
suffix:semicolon
DECL|member|vg_name
r_char
id|vg_name
(braket
id|NAME_LEN
)braket
suffix:semicolon
DECL|member|system_id
r_char
id|system_id
(braket
id|NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* for vgexport/vgimport */
DECL|member|pv_dev
id|kdev_t
id|pv_dev
suffix:semicolon
DECL|member|pv_number
id|uint
id|pv_number
suffix:semicolon
DECL|member|pv_status
id|uint
id|pv_status
suffix:semicolon
DECL|member|pv_allocatable
id|uint
id|pv_allocatable
suffix:semicolon
DECL|member|pv_size
id|uint
id|pv_size
suffix:semicolon
multiline_comment|/* HM */
DECL|member|lv_cur
id|uint
id|lv_cur
suffix:semicolon
DECL|member|pe_size
id|uint
id|pe_size
suffix:semicolon
DECL|member|pe_total
id|uint
id|pe_total
suffix:semicolon
DECL|member|pe_allocated
id|uint
id|pe_allocated
suffix:semicolon
DECL|member|pe_stale
id|uint
id|pe_stale
suffix:semicolon
multiline_comment|/* for future use */
DECL|member|pe
id|pe_disk_t
op_star
id|pe
suffix:semicolon
multiline_comment|/* HM */
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
multiline_comment|/* HM */
DECL|typedef|pv_v1_t
)brace
id|pv_v1_t
suffix:semicolon
multiline_comment|/* core */
r_typedef
r_struct
(brace
DECL|member|id
r_char
id|id
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Identifier */
DECL|member|version
r_int
r_int
id|version
suffix:semicolon
multiline_comment|/* HM lvm version */
DECL|member|pv_on_disk
id|lvm_disk_data_t
id|pv_on_disk
suffix:semicolon
DECL|member|vg_on_disk
id|lvm_disk_data_t
id|vg_on_disk
suffix:semicolon
DECL|member|pv_uuidlist_on_disk
id|lvm_disk_data_t
id|pv_uuidlist_on_disk
suffix:semicolon
DECL|member|lv_on_disk
id|lvm_disk_data_t
id|lv_on_disk
suffix:semicolon
DECL|member|pe_on_disk
id|lvm_disk_data_t
id|pe_on_disk
suffix:semicolon
DECL|member|pv_name
r_char
id|pv_name
(braket
id|NAME_LEN
)braket
suffix:semicolon
DECL|member|vg_name
r_char
id|vg_name
(braket
id|NAME_LEN
)braket
suffix:semicolon
DECL|member|system_id
r_char
id|system_id
(braket
id|NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* for vgexport/vgimport */
DECL|member|pv_dev
id|kdev_t
id|pv_dev
suffix:semicolon
DECL|member|pv_number
id|uint
id|pv_number
suffix:semicolon
DECL|member|pv_status
id|uint
id|pv_status
suffix:semicolon
DECL|member|pv_allocatable
id|uint
id|pv_allocatable
suffix:semicolon
DECL|member|pv_size
id|uint
id|pv_size
suffix:semicolon
multiline_comment|/* HM */
DECL|member|lv_cur
id|uint
id|lv_cur
suffix:semicolon
DECL|member|pe_size
id|uint
id|pe_size
suffix:semicolon
DECL|member|pe_total
id|uint
id|pe_total
suffix:semicolon
DECL|member|pe_allocated
id|uint
id|pe_allocated
suffix:semicolon
DECL|member|pe_stale
id|uint
id|pe_stale
suffix:semicolon
multiline_comment|/* for future use */
DECL|member|pe
id|pe_disk_t
op_star
id|pe
suffix:semicolon
multiline_comment|/* HM */
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
multiline_comment|/* HM */
DECL|member|pv_uuid
r_char
id|pv_uuid
(braket
id|UUID_LEN
op_plus
l_int|1
)braket
suffix:semicolon
DECL|typedef|pv_v2_t
)brace
id|pv_v2_t
suffix:semicolon
multiline_comment|/* disk */
r_typedef
r_struct
(brace
DECL|member|id
r_uint8
id|id
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Identifier */
DECL|member|version
r_uint16
id|version
suffix:semicolon
multiline_comment|/* HM lvm version */
DECL|member|pv_on_disk
id|lvm_disk_data_t
id|pv_on_disk
suffix:semicolon
DECL|member|vg_on_disk
id|lvm_disk_data_t
id|vg_on_disk
suffix:semicolon
DECL|member|pv_namelist_on_disk
id|lvm_disk_data_t
id|pv_namelist_on_disk
suffix:semicolon
DECL|member|lv_on_disk
id|lvm_disk_data_t
id|lv_on_disk
suffix:semicolon
DECL|member|pe_on_disk
id|lvm_disk_data_t
id|pe_on_disk
suffix:semicolon
DECL|member|pv_name
r_uint8
id|pv_name
(braket
id|NAME_LEN
)braket
suffix:semicolon
DECL|member|vg_name
r_uint8
id|vg_name
(braket
id|NAME_LEN
)braket
suffix:semicolon
DECL|member|system_id
r_uint8
id|system_id
(braket
id|NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* for vgexport/vgimport */
DECL|member|pv_major
r_uint32
id|pv_major
suffix:semicolon
DECL|member|pv_number
r_uint32
id|pv_number
suffix:semicolon
DECL|member|pv_status
r_uint32
id|pv_status
suffix:semicolon
DECL|member|pv_allocatable
r_uint32
id|pv_allocatable
suffix:semicolon
DECL|member|pv_size
r_uint32
id|pv_size
suffix:semicolon
multiline_comment|/* HM */
DECL|member|lv_cur
r_uint32
id|lv_cur
suffix:semicolon
DECL|member|pe_size
r_uint32
id|pe_size
suffix:semicolon
DECL|member|pe_total
r_uint32
id|pe_total
suffix:semicolon
DECL|member|pe_allocated
r_uint32
id|pe_allocated
suffix:semicolon
DECL|typedef|pv_disk_v1_t
)brace
id|pv_disk_v1_t
suffix:semicolon
multiline_comment|/* disk */
r_typedef
r_struct
(brace
DECL|member|id
r_uint8
id|id
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Identifier */
DECL|member|version
r_uint16
id|version
suffix:semicolon
multiline_comment|/* HM lvm version */
DECL|member|pv_on_disk
id|lvm_disk_data_t
id|pv_on_disk
suffix:semicolon
DECL|member|vg_on_disk
id|lvm_disk_data_t
id|vg_on_disk
suffix:semicolon
DECL|member|pv_uuidlist_on_disk
id|lvm_disk_data_t
id|pv_uuidlist_on_disk
suffix:semicolon
DECL|member|lv_on_disk
id|lvm_disk_data_t
id|lv_on_disk
suffix:semicolon
DECL|member|pe_on_disk
id|lvm_disk_data_t
id|pe_on_disk
suffix:semicolon
DECL|member|pv_uuid
r_uint8
id|pv_uuid
(braket
id|NAME_LEN
)braket
suffix:semicolon
DECL|member|vg_name
r_uint8
id|vg_name
(braket
id|NAME_LEN
)braket
suffix:semicolon
DECL|member|system_id
r_uint8
id|system_id
(braket
id|NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* for vgexport/vgimport */
DECL|member|pv_major
r_uint32
id|pv_major
suffix:semicolon
DECL|member|pv_number
r_uint32
id|pv_number
suffix:semicolon
DECL|member|pv_status
r_uint32
id|pv_status
suffix:semicolon
DECL|member|pv_allocatable
r_uint32
id|pv_allocatable
suffix:semicolon
DECL|member|pv_size
r_uint32
id|pv_size
suffix:semicolon
multiline_comment|/* HM */
DECL|member|lv_cur
r_uint32
id|lv_cur
suffix:semicolon
DECL|member|pe_size
r_uint32
id|pe_size
suffix:semicolon
DECL|member|pe_total
r_uint32
id|pe_total
suffix:semicolon
DECL|member|pe_allocated
r_uint32
id|pe_allocated
suffix:semicolon
DECL|typedef|pv_disk_v2_t
)brace
id|pv_disk_v2_t
suffix:semicolon
multiline_comment|/*&n; * Structures for Logical Volume (LV)&n; */
multiline_comment|/* core PE information */
r_typedef
r_struct
(brace
DECL|member|dev
id|kdev_t
id|dev
suffix:semicolon
DECL|member|pe
id|ulong
id|pe
suffix:semicolon
multiline_comment|/* to be changed if &gt; 2TB */
DECL|member|reads
id|ulong
id|reads
suffix:semicolon
DECL|member|writes
id|ulong
id|writes
suffix:semicolon
DECL|typedef|pe_t
)brace
id|pe_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|lv_name
r_char
id|lv_name
(braket
id|NAME_LEN
)braket
suffix:semicolon
DECL|member|old_dev
id|kdev_t
id|old_dev
suffix:semicolon
DECL|member|new_dev
id|kdev_t
id|new_dev
suffix:semicolon
DECL|member|old_pe
id|ulong
id|old_pe
suffix:semicolon
DECL|member|new_pe
id|ulong
id|new_pe
suffix:semicolon
DECL|typedef|le_remap_req_t
)brace
id|le_remap_req_t
suffix:semicolon
DECL|struct|lv_bmap
r_typedef
r_struct
id|lv_bmap
(brace
DECL|member|lv_block
id|ulong
id|lv_block
suffix:semicolon
DECL|member|lv_dev
id|dev_t
id|lv_dev
suffix:semicolon
DECL|typedef|lv_bmap_t
)brace
id|lv_bmap_t
suffix:semicolon
multiline_comment|/*&n; * Structure Logical Volume (LV) Version 3&n; */
multiline_comment|/* core */
DECL|struct|lv_v4
r_typedef
r_struct
id|lv_v4
(brace
DECL|member|lv_name
r_char
id|lv_name
(braket
id|NAME_LEN
)braket
suffix:semicolon
DECL|member|vg_name
r_char
id|vg_name
(braket
id|NAME_LEN
)braket
suffix:semicolon
DECL|member|lv_access
id|uint
id|lv_access
suffix:semicolon
DECL|member|lv_status
id|uint
id|lv_status
suffix:semicolon
DECL|member|lv_open
id|uint
id|lv_open
suffix:semicolon
multiline_comment|/* HM */
DECL|member|lv_dev
id|kdev_t
id|lv_dev
suffix:semicolon
multiline_comment|/* HM */
DECL|member|lv_number
id|uint
id|lv_number
suffix:semicolon
multiline_comment|/* HM */
DECL|member|lv_mirror_copies
id|uint
id|lv_mirror_copies
suffix:semicolon
multiline_comment|/* for future use */
DECL|member|lv_recovery
id|uint
id|lv_recovery
suffix:semicolon
multiline_comment|/*       &quot;        */
DECL|member|lv_schedule
id|uint
id|lv_schedule
suffix:semicolon
multiline_comment|/*       &quot;        */
DECL|member|lv_size
id|uint
id|lv_size
suffix:semicolon
DECL|member|lv_current_pe
id|pe_t
op_star
id|lv_current_pe
suffix:semicolon
multiline_comment|/* HM */
DECL|member|lv_current_le
id|uint
id|lv_current_le
suffix:semicolon
multiline_comment|/* for future use */
DECL|member|lv_allocated_le
id|uint
id|lv_allocated_le
suffix:semicolon
DECL|member|lv_stripes
id|uint
id|lv_stripes
suffix:semicolon
DECL|member|lv_stripesize
id|uint
id|lv_stripesize
suffix:semicolon
DECL|member|lv_badblock
id|uint
id|lv_badblock
suffix:semicolon
multiline_comment|/* for future use */
DECL|member|lv_allocation
id|uint
id|lv_allocation
suffix:semicolon
DECL|member|lv_io_timeout
id|uint
id|lv_io_timeout
suffix:semicolon
multiline_comment|/* for future use */
DECL|member|lv_read_ahead
id|uint
id|lv_read_ahead
suffix:semicolon
multiline_comment|/* delta to version 1 starts here */
DECL|member|lv_snapshot_org
r_struct
id|lv_v4
op_star
id|lv_snapshot_org
suffix:semicolon
DECL|member|lv_snapshot_prev
r_struct
id|lv_v4
op_star
id|lv_snapshot_prev
suffix:semicolon
DECL|member|lv_snapshot_next
r_struct
id|lv_v4
op_star
id|lv_snapshot_next
suffix:semicolon
DECL|member|lv_block_exception
id|lv_block_exception_t
op_star
id|lv_block_exception
suffix:semicolon
DECL|member|lv_remap_ptr
id|uint
id|lv_remap_ptr
suffix:semicolon
DECL|member|lv_remap_end
id|uint
id|lv_remap_end
suffix:semicolon
DECL|member|lv_chunk_size
id|uint
id|lv_chunk_size
suffix:semicolon
DECL|member|lv_snapshot_minor
id|uint
id|lv_snapshot_minor
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|member|lv_iobuf
r_struct
id|kiobuf
op_star
id|lv_iobuf
suffix:semicolon
DECL|member|lv_snapshot_sem
r_struct
id|semaphore
id|lv_snapshot_sem
suffix:semicolon
DECL|member|lv_snapshot_hash_table
r_struct
id|list_head
op_star
id|lv_snapshot_hash_table
suffix:semicolon
DECL|member|lv_snapshot_hash_table_size
id|ulong
id|lv_snapshot_hash_table_size
suffix:semicolon
DECL|member|lv_snapshot_hash_mask
id|ulong
id|lv_snapshot_hash_mask
suffix:semicolon
DECL|member|lv_COW_table_page
r_struct
id|page
op_star
id|lv_COW_table_page
suffix:semicolon
DECL|member|lv_snapshot_wait
id|wait_queue_head_t
id|lv_snapshot_wait
suffix:semicolon
DECL|member|lv_snapshot_use_rate
r_int
id|lv_snapshot_use_rate
suffix:semicolon
DECL|member|vg
r_void
op_star
id|vg
suffix:semicolon
macro_line|#else
DECL|member|dummy
r_char
id|dummy
(braket
l_int|200
)braket
suffix:semicolon
macro_line|#endif
DECL|typedef|lv_v4_t
)brace
id|lv_v4_t
suffix:semicolon
multiline_comment|/* disk */
r_typedef
r_struct
(brace
DECL|member|lv_name
r_uint8
id|lv_name
(braket
id|NAME_LEN
)braket
suffix:semicolon
DECL|member|vg_name
r_uint8
id|vg_name
(braket
id|NAME_LEN
)braket
suffix:semicolon
DECL|member|lv_access
r_uint32
id|lv_access
suffix:semicolon
DECL|member|lv_status
r_uint32
id|lv_status
suffix:semicolon
DECL|member|lv_open
r_uint32
id|lv_open
suffix:semicolon
multiline_comment|/* HM */
DECL|member|lv_dev
r_uint32
id|lv_dev
suffix:semicolon
multiline_comment|/* HM */
DECL|member|lv_number
r_uint32
id|lv_number
suffix:semicolon
multiline_comment|/* HM */
DECL|member|lv_mirror_copies
r_uint32
id|lv_mirror_copies
suffix:semicolon
multiline_comment|/* for future use */
DECL|member|lv_recovery
r_uint32
id|lv_recovery
suffix:semicolon
multiline_comment|/*       &quot;        */
DECL|member|lv_schedule
r_uint32
id|lv_schedule
suffix:semicolon
multiline_comment|/*       &quot;        */
DECL|member|lv_size
r_uint32
id|lv_size
suffix:semicolon
DECL|member|lv_snapshot_minor
r_uint32
id|lv_snapshot_minor
suffix:semicolon
multiline_comment|/* minor number of original */
DECL|member|lv_chunk_size
r_uint16
id|lv_chunk_size
suffix:semicolon
multiline_comment|/* chunk size of snapshot */
DECL|member|dummy
r_uint16
id|dummy
suffix:semicolon
DECL|member|lv_allocated_le
r_uint32
id|lv_allocated_le
suffix:semicolon
DECL|member|lv_stripes
r_uint32
id|lv_stripes
suffix:semicolon
DECL|member|lv_stripesize
r_uint32
id|lv_stripesize
suffix:semicolon
DECL|member|lv_badblock
r_uint32
id|lv_badblock
suffix:semicolon
multiline_comment|/* for future use */
DECL|member|lv_allocation
r_uint32
id|lv_allocation
suffix:semicolon
DECL|member|lv_io_timeout
r_uint32
id|lv_io_timeout
suffix:semicolon
multiline_comment|/* for future use */
DECL|member|lv_read_ahead
r_uint32
id|lv_read_ahead
suffix:semicolon
multiline_comment|/* HM */
DECL|typedef|lv_disk_v3_t
)brace
id|lv_disk_v3_t
suffix:semicolon
multiline_comment|/*&n; * Structure Volume Group (VG) Version 1&n; */
multiline_comment|/* core */
r_typedef
r_struct
(brace
DECL|member|vg_name
r_char
id|vg_name
(braket
id|NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* volume group name */
DECL|member|vg_number
id|uint
id|vg_number
suffix:semicolon
multiline_comment|/* volume group number */
DECL|member|vg_access
id|uint
id|vg_access
suffix:semicolon
multiline_comment|/* read/write */
DECL|member|vg_status
id|uint
id|vg_status
suffix:semicolon
multiline_comment|/* active or not */
DECL|member|lv_max
id|uint
id|lv_max
suffix:semicolon
multiline_comment|/* maximum logical volumes */
DECL|member|lv_cur
id|uint
id|lv_cur
suffix:semicolon
multiline_comment|/* current logical volumes */
DECL|member|lv_open
id|uint
id|lv_open
suffix:semicolon
multiline_comment|/* open    logical volumes */
DECL|member|pv_max
id|uint
id|pv_max
suffix:semicolon
multiline_comment|/* maximum physical volumes */
DECL|member|pv_cur
id|uint
id|pv_cur
suffix:semicolon
multiline_comment|/* current physical volumes FU */
DECL|member|pv_act
id|uint
id|pv_act
suffix:semicolon
multiline_comment|/* active physical volumes */
DECL|member|dummy
id|uint
id|dummy
suffix:semicolon
multiline_comment|/* was obsolete max_pe_per_pv */
DECL|member|vgda
id|uint
id|vgda
suffix:semicolon
multiline_comment|/* volume group descriptor arrays FU */
DECL|member|pe_size
id|uint
id|pe_size
suffix:semicolon
multiline_comment|/* physical extent size in sectors */
DECL|member|pe_total
id|uint
id|pe_total
suffix:semicolon
multiline_comment|/* total of physical extents */
DECL|member|pe_allocated
id|uint
id|pe_allocated
suffix:semicolon
multiline_comment|/* allocated physical extents */
DECL|member|pvg_total
id|uint
id|pvg_total
suffix:semicolon
multiline_comment|/* physical volume groups FU */
DECL|member|proc
r_struct
id|proc_dir_entry
op_star
id|proc
suffix:semicolon
DECL|member|pv
id|pv_t
op_star
id|pv
(braket
id|ABS_MAX_PV
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* physical volume struct pointers */
DECL|member|lv
id|lv_t
op_star
id|lv
(braket
id|ABS_MAX_LV
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* logical  volume struct pointers */
DECL|typedef|vg_v1_t
)brace
id|vg_v1_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|vg_name
r_char
id|vg_name
(braket
id|NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* volume group name */
DECL|member|vg_number
id|uint
id|vg_number
suffix:semicolon
multiline_comment|/* volume group number */
DECL|member|vg_access
id|uint
id|vg_access
suffix:semicolon
multiline_comment|/* read/write */
DECL|member|vg_status
id|uint
id|vg_status
suffix:semicolon
multiline_comment|/* active or not */
DECL|member|lv_max
id|uint
id|lv_max
suffix:semicolon
multiline_comment|/* maximum logical volumes */
DECL|member|lv_cur
id|uint
id|lv_cur
suffix:semicolon
multiline_comment|/* current logical volumes */
DECL|member|lv_open
id|uint
id|lv_open
suffix:semicolon
multiline_comment|/* open    logical volumes */
DECL|member|pv_max
id|uint
id|pv_max
suffix:semicolon
multiline_comment|/* maximum physical volumes */
DECL|member|pv_cur
id|uint
id|pv_cur
suffix:semicolon
multiline_comment|/* current physical volumes FU */
DECL|member|pv_act
id|uint
id|pv_act
suffix:semicolon
multiline_comment|/* active physical volumes */
DECL|member|dummy
id|uint
id|dummy
suffix:semicolon
multiline_comment|/* was obsolete max_pe_per_pv */
DECL|member|vgda
id|uint
id|vgda
suffix:semicolon
multiline_comment|/* volume group descriptor arrays FU */
DECL|member|pe_size
id|uint
id|pe_size
suffix:semicolon
multiline_comment|/* physical extent size in sectors */
DECL|member|pe_total
id|uint
id|pe_total
suffix:semicolon
multiline_comment|/* total of physical extents */
DECL|member|pe_allocated
id|uint
id|pe_allocated
suffix:semicolon
multiline_comment|/* allocated physical extents */
DECL|member|pvg_total
id|uint
id|pvg_total
suffix:semicolon
multiline_comment|/* physical volume groups FU */
DECL|member|proc
r_struct
id|proc_dir_entry
op_star
id|proc
suffix:semicolon
DECL|member|pv
id|pv_t
op_star
id|pv
(braket
id|ABS_MAX_PV
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* physical volume struct pointers */
DECL|member|lv
id|lv_t
op_star
id|lv
(braket
id|ABS_MAX_LV
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* logical  volume struct pointers */
DECL|member|vg_uuid
r_char
id|vg_uuid
(braket
id|UUID_LEN
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* volume group UUID */
macro_line|#ifdef __KERNEL__
DECL|member|vg_dir_pde
r_struct
id|proc_dir_entry
op_star
id|vg_dir_pde
suffix:semicolon
DECL|member|lv_subdir_pde
r_struct
id|proc_dir_entry
op_star
id|lv_subdir_pde
suffix:semicolon
DECL|member|pv_subdir_pde
r_struct
id|proc_dir_entry
op_star
id|pv_subdir_pde
suffix:semicolon
macro_line|#else
DECL|member|dummy1
r_char
id|dummy1
(braket
l_int|200
)braket
suffix:semicolon
macro_line|#endif
DECL|typedef|vg_v3_t
)brace
id|vg_v3_t
suffix:semicolon
multiline_comment|/* disk */
r_typedef
r_struct
(brace
DECL|member|vg_name
r_uint8
id|vg_name
(braket
id|NAME_LEN
)braket
suffix:semicolon
multiline_comment|/* volume group name */
DECL|member|vg_number
r_uint32
id|vg_number
suffix:semicolon
multiline_comment|/* volume group number */
DECL|member|vg_access
r_uint32
id|vg_access
suffix:semicolon
multiline_comment|/* read/write */
DECL|member|vg_status
r_uint32
id|vg_status
suffix:semicolon
multiline_comment|/* active or not */
DECL|member|lv_max
r_uint32
id|lv_max
suffix:semicolon
multiline_comment|/* maximum logical volumes */
DECL|member|lv_cur
r_uint32
id|lv_cur
suffix:semicolon
multiline_comment|/* current logical volumes */
DECL|member|lv_open
r_uint32
id|lv_open
suffix:semicolon
multiline_comment|/* open    logical volumes */
DECL|member|pv_max
r_uint32
id|pv_max
suffix:semicolon
multiline_comment|/* maximum physical volumes */
DECL|member|pv_cur
r_uint32
id|pv_cur
suffix:semicolon
multiline_comment|/* current physical volumes FU */
DECL|member|pv_act
r_uint32
id|pv_act
suffix:semicolon
multiline_comment|/* active physical volumes */
DECL|member|dummy
r_uint32
id|dummy
suffix:semicolon
DECL|member|vgda
r_uint32
id|vgda
suffix:semicolon
multiline_comment|/* volume group descriptor arrays FU */
DECL|member|pe_size
r_uint32
id|pe_size
suffix:semicolon
multiline_comment|/* physical extent size in sectors */
DECL|member|pe_total
r_uint32
id|pe_total
suffix:semicolon
multiline_comment|/* total of physical extents */
DECL|member|pe_allocated
r_uint32
id|pe_allocated
suffix:semicolon
multiline_comment|/* allocated physical extents */
DECL|member|pvg_total
r_uint32
id|pvg_total
suffix:semicolon
multiline_comment|/* physical volume groups FU */
DECL|typedef|vg_disk_v1_t
)brace
id|vg_disk_v1_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|vg_uuid
r_uint8
id|vg_uuid
(braket
id|UUID_LEN
)braket
suffix:semicolon
multiline_comment|/* volume group UUID */
DECL|member|vg_name_dummy
r_uint8
id|vg_name_dummy
(braket
id|NAME_LEN
op_minus
id|UUID_LEN
)braket
suffix:semicolon
multiline_comment|/* rest of v1 VG name */
DECL|member|vg_number
r_uint32
id|vg_number
suffix:semicolon
multiline_comment|/* volume group number */
DECL|member|vg_access
r_uint32
id|vg_access
suffix:semicolon
multiline_comment|/* read/write */
DECL|member|vg_status
r_uint32
id|vg_status
suffix:semicolon
multiline_comment|/* active or not */
DECL|member|lv_max
r_uint32
id|lv_max
suffix:semicolon
multiline_comment|/* maximum logical volumes */
DECL|member|lv_cur
r_uint32
id|lv_cur
suffix:semicolon
multiline_comment|/* current logical volumes */
DECL|member|lv_open
r_uint32
id|lv_open
suffix:semicolon
multiline_comment|/* open    logical volumes */
DECL|member|pv_max
r_uint32
id|pv_max
suffix:semicolon
multiline_comment|/* maximum physical volumes */
DECL|member|pv_cur
r_uint32
id|pv_cur
suffix:semicolon
multiline_comment|/* current physical volumes FU */
DECL|member|pv_act
r_uint32
id|pv_act
suffix:semicolon
multiline_comment|/* active physical volumes */
DECL|member|dummy
r_uint32
id|dummy
suffix:semicolon
DECL|member|vgda
r_uint32
id|vgda
suffix:semicolon
multiline_comment|/* volume group descriptor arrays FU */
DECL|member|pe_size
r_uint32
id|pe_size
suffix:semicolon
multiline_comment|/* physical extent size in sectors */
DECL|member|pe_total
r_uint32
id|pe_total
suffix:semicolon
multiline_comment|/* total of physical extents */
DECL|member|pe_allocated
r_uint32
id|pe_allocated
suffix:semicolon
multiline_comment|/* allocated physical extents */
DECL|member|pvg_total
r_uint32
id|pvg_total
suffix:semicolon
multiline_comment|/* physical volume groups FU */
DECL|typedef|vg_disk_v2_t
)brace
id|vg_disk_v2_t
suffix:semicolon
multiline_comment|/*&n; * Request structures for ioctls&n; */
multiline_comment|/* Request structure PV_STATUS_BY_NAME... */
r_typedef
r_struct
(brace
DECL|member|pv_name
r_char
id|pv_name
(braket
id|NAME_LEN
)braket
suffix:semicolon
DECL|member|pv
id|pv_t
op_star
id|pv
suffix:semicolon
DECL|typedef|pv_status_req_t
DECL|typedef|pv_change_req_t
)brace
id|pv_status_req_t
comma
id|pv_change_req_t
suffix:semicolon
multiline_comment|/* Request structure PV_FLUSH */
r_typedef
r_struct
(brace
DECL|member|pv_name
r_char
id|pv_name
(braket
id|NAME_LEN
)braket
suffix:semicolon
DECL|member|pv_dev
id|kdev_t
id|pv_dev
suffix:semicolon
DECL|typedef|pv_flush_req_t
)brace
id|pv_flush_req_t
suffix:semicolon
multiline_comment|/* Request structure PE_MOVE */
r_typedef
r_struct
(brace
r_enum
(brace
DECL|enumerator|LOCK_PE
DECL|enumerator|UNLOCK_PE
id|LOCK_PE
comma
id|UNLOCK_PE
DECL|member|lock
)brace
id|lock
suffix:semicolon
r_struct
(brace
DECL|member|lv_dev
id|kdev_t
id|lv_dev
suffix:semicolon
DECL|member|pv_dev
id|kdev_t
id|pv_dev
suffix:semicolon
DECL|member|pv_offset
id|ulong
id|pv_offset
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
DECL|typedef|pe_lock_req_t
)brace
id|pe_lock_req_t
suffix:semicolon
multiline_comment|/* Request structure LV_STATUS_BYNAME */
r_typedef
r_struct
(brace
DECL|member|lv_name
r_char
id|lv_name
(braket
id|NAME_LEN
)braket
suffix:semicolon
DECL|member|lv
id|lv_t
op_star
id|lv
suffix:semicolon
DECL|typedef|lv_status_byname_req_t
DECL|typedef|lv_req_t
)brace
id|lv_status_byname_req_t
comma
id|lv_req_t
suffix:semicolon
multiline_comment|/* Request structure LV_STATUS_BYINDEX */
r_typedef
r_struct
(brace
DECL|member|lv_index
id|ulong
id|lv_index
suffix:semicolon
DECL|member|lv
id|lv_t
op_star
id|lv
suffix:semicolon
multiline_comment|/* Transfer size because user space and kernel space differ */
DECL|member|size
id|ushort
id|size
suffix:semicolon
DECL|typedef|lv_status_byindex_req_t
)brace
id|lv_status_byindex_req_t
suffix:semicolon
multiline_comment|/* Request structure LV_STATUS_BYDEV... */
r_typedef
r_struct
(brace
DECL|member|dev
id|dev_t
id|dev
suffix:semicolon
DECL|member|lv
id|pv_t
op_star
id|lv
suffix:semicolon
DECL|typedef|lv_status_bydev_req_t
)brace
id|lv_status_bydev_req_t
suffix:semicolon
multiline_comment|/* Request structure LV_SNAPSHOT_USE_RATE */
r_typedef
r_struct
(brace
DECL|member|block
r_int
id|block
suffix:semicolon
DECL|member|rate
r_int
id|rate
suffix:semicolon
DECL|typedef|lv_snapshot_use_rate_req_t
)brace
id|lv_snapshot_use_rate_req_t
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* #ifndef _LVM_H_INCLUDE */
eof
