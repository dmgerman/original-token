macro_line|#ifndef __LINUX_UDF_SB_H
DECL|macro|__LINUX_UDF_SB_H
mdefine_line|#define __LINUX_UDF_SB_H
multiline_comment|/* Since UDF 1.50 is ISO 13346 based... */
DECL|macro|UDF_SUPER_MAGIC
mdefine_line|#define UDF_SUPER_MAGIC&t;0x15013346
DECL|macro|UDF_FLAG_STRICT
mdefine_line|#define UDF_FLAG_STRICT&t;&t;0x00000001U
DECL|macro|UDF_FLAG_UNDELETE
mdefine_line|#define UDF_FLAG_UNDELETE&t;0x00000002U
DECL|macro|UDF_FLAG_UNHIDE
mdefine_line|#define UDF_FLAG_UNHIDE&t;&t;0x00000004U
DECL|macro|UDF_FLAG_VARCONV
mdefine_line|#define UDF_FLAG_VARCONV&t;0x00000008U
DECL|macro|UDF_SB_FREE
mdefine_line|#define UDF_SB_FREE(X)&bslash;&n;{&bslash;&n;&t;if (UDF_SB(X))&bslash;&n;&t;{&bslash;&n;&t;&t;if (UDF_SB_PARTMAPS(X))&bslash;&n;&t;&t;&t;kfree(UDF_SB_PARTMAPS(X));&bslash;&n;&t;&t;UDF_SB_PARTMAPS(X) = NULL;&bslash;&n;&t;}&bslash;&n;}
DECL|macro|UDF_SB
mdefine_line|#define UDF_SB(X)&t;(&amp;((X)-&gt;u.udf_sb))
DECL|macro|UDF_SB_ALLOC_PARTMAPS
mdefine_line|#define UDF_SB_ALLOC_PARTMAPS(X,Y)&bslash;&n;{&bslash;&n;&t;UDF_SB_NUMPARTS(X) = Y;&bslash;&n;&t;UDF_SB_PARTMAPS(X) = kmalloc(sizeof(struct udf_part_map) * Y, GFP_KERNEL);&bslash;&n;&t;memset(UDF_SB_PARTMAPS(X), 0x00, sizeof(struct udf_part_map) * Y);&bslash;&n;}
DECL|macro|IS_STRICT
mdefine_line|#define IS_STRICT(X)&t;&t;&t;( UDF_SB(X)-&gt;s_flags &amp; UDF_FLAG_STRICT )
DECL|macro|IS_UNDELETE
mdefine_line|#define IS_UNDELETE(X)&t;&t;&t;( UDF_SB(X)-&gt;s_flags &amp; UDF_FLAG_UNDELETE )
DECL|macro|IS_UNHIDE
mdefine_line|#define IS_UNHIDE(X)&t;&t;&t;( UDF_SB(X)-&gt;s_flags &amp; UDF_FLAG_UNHIDE )
DECL|macro|UDF_SB_SESSION
mdefine_line|#define UDF_SB_SESSION(X)&t;&t;( UDF_SB(X)-&gt;s_session )
DECL|macro|UDF_SB_ANCHOR
mdefine_line|#define UDF_SB_ANCHOR(X)&t;&t;( UDF_SB(X)-&gt;s_anchor )
DECL|macro|UDF_SB_NUMPARTS
mdefine_line|#define UDF_SB_NUMPARTS(X)&t;&t;( UDF_SB(X)-&gt;s_partitions )
DECL|macro|UDF_SB_VOLUME
mdefine_line|#define UDF_SB_VOLUME(X)&t;&t;( UDF_SB(X)-&gt;s_thisvolume )
DECL|macro|UDF_SB_LASTBLOCK
mdefine_line|#define UDF_SB_LASTBLOCK(X)&t;&t;( UDF_SB(X)-&gt;s_lastblock )
DECL|macro|UDF_SB_VOLDESC
mdefine_line|#define UDF_SB_VOLDESC(X)&t;&t;( UDF_SB(X)-&gt;s_voldesc )
DECL|macro|UDF_SB_LVIDBH
mdefine_line|#define UDF_SB_LVIDBH(X)&t;&t;( UDF_SB(X)-&gt;s_lvidbh )
DECL|macro|UDF_SB_LVID
mdefine_line|#define UDF_SB_LVID(X)&t;&t;&t;( (struct LogicalVolIntegrityDesc *)UDF_SB_LVIDBH(X)-&gt;b_data )
DECL|macro|UDF_SB_LVIDIU
mdefine_line|#define UDF_SB_LVIDIU(X)&t;&t;( (struct LogicalVolIntegrityDescImpUse *)&amp;(UDF_SB_LVID(sb)-&gt;impUse[UDF_SB_LVID(sb)-&gt;numOfPartitions * 2 * sizeof(Uint32)/sizeof(Uint8)]) )
DECL|macro|UDF_SB_PARTITION
mdefine_line|#define UDF_SB_PARTITION(X)&t;&t;( UDF_SB(X)-&gt;s_partition )
DECL|macro|UDF_SB_RECORDTIME
mdefine_line|#define UDF_SB_RECORDTIME(X)&t;( UDF_SB(X)-&gt;s_recordtime )
DECL|macro|UDF_SB_VOLIDENT
mdefine_line|#define UDF_SB_VOLIDENT(X)&t;&t;( UDF_SB(X)-&gt;s_volident )
DECL|macro|UDF_SB_PARTMAPS
mdefine_line|#define UDF_SB_PARTMAPS(X)&t;&t;( UDF_SB(X)-&gt;s_partmaps )
DECL|macro|UDF_SB_SERIALNUM
mdefine_line|#define UDF_SB_SERIALNUM(X)&t;&t;( UDF_SB(X)-&gt;s_serialnum )
DECL|macro|UDF_SB_VAT
mdefine_line|#define UDF_SB_VAT(X)&t;&t;&t;( UDF_SB(X)-&gt;s_vat )
DECL|macro|UDF_SB_BLOCK_BITMAP_NUMBER
mdefine_line|#define UDF_SB_BLOCK_BITMAP_NUMBER(X,Y) ( UDF_SB(X)-&gt;s_block_bitmap_number[Y] )
DECL|macro|UDF_SB_BLOCK_BITMAP
mdefine_line|#define UDF_SB_BLOCK_BITMAP(X,Y)&t;&t;( UDF_SB(X)-&gt;s_block_bitmap[Y] )
DECL|macro|UDF_SB_LOADED_BLOCK_BITMAPS
mdefine_line|#define UDF_SB_LOADED_BLOCK_BITMAPS(X)&t;( UDF_SB(X)-&gt;s_loaded_block_bitmaps )
DECL|macro|UDF_SB_PARTTYPE
mdefine_line|#define UDF_SB_PARTTYPE(X,Y)&t;( UDF_SB_PARTMAPS(X)[Y].s_partition_type )
DECL|macro|UDF_SB_PARTROOT
mdefine_line|#define UDF_SB_PARTROOT(X,Y)&t;( UDF_SB_PARTMAPS(X)[Y].s_partition_root )
DECL|macro|UDF_SB_PARTLEN
mdefine_line|#define UDF_SB_PARTLEN(X,Y)&t;&t;( UDF_SB_PARTMAPS(X)[Y].s_partition_len )
DECL|macro|UDF_SB_PARTVSN
mdefine_line|#define UDF_SB_PARTVSN(X,Y)&t;&t;( UDF_SB_PARTMAPS(X)[Y].s_volumeseqnum )
DECL|macro|UDF_SB_PARTNUM
mdefine_line|#define UDF_SB_PARTNUM(X,Y)&t;&t;( UDF_SB_PARTMAPS(X)[Y].s_partition_num )
DECL|macro|UDF_SB_TYPESPAR
mdefine_line|#define UDF_SB_TYPESPAR(X,Y)&t;( UDF_SB_PARTMAPS(X)[Y].s_type_specific.s_sparing )
DECL|macro|UDF_SB_TYPEVIRT
mdefine_line|#define UDF_SB_TYPEVIRT(X,Y)&t;( UDF_SB_PARTMAPS(X)[Y].s_type_specific.s_virtual )
DECL|macro|UDF_SB_PARTFUNC
mdefine_line|#define UDF_SB_PARTFUNC(X,Y)&t;( UDF_SB_PARTMAPS(X)[Y].s_partition_func )
macro_line|#endif /* __LINUX_UDF_SB_H */
eof
