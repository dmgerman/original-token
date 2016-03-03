macro_line|#ifndef __LINUX_UDF_SB_H
DECL|macro|__LINUX_UDF_SB_H
mdefine_line|#define __LINUX_UDF_SB_H
multiline_comment|/* Since UDF 1.50 is ISO 13346 based... */
DECL|macro|UDF_SUPER_MAGIC
mdefine_line|#define UDF_SUPER_MAGIC&t;&t;&t;&t;0x15013346
DECL|macro|UDF_MAX_READ_VERSION
mdefine_line|#define UDF_MAX_READ_VERSION&t;&t;0x0200
DECL|macro|UDF_MAX_WRITE_VERSION
mdefine_line|#define UDF_MAX_WRITE_VERSION&t;&t;0x0200
DECL|macro|UDF_FLAG_USE_EXTENDED_FE
mdefine_line|#define UDF_FLAG_USE_EXTENDED_FE&t;0
DECL|macro|UDF_VERS_USE_EXTENDED_FE
mdefine_line|#define UDF_VERS_USE_EXTENDED_FE&t;0x0200
DECL|macro|UDF_FLAG_USE_STREAMS
mdefine_line|#define UDF_FLAG_USE_STREAMS&t;&t;1
DECL|macro|UDF_VERS_USE_STREAMS
mdefine_line|#define UDF_VERS_USE_STREAMS&t;&t;0x0200
DECL|macro|UDF_FLAG_USE_SHORT_AD
mdefine_line|#define UDF_FLAG_USE_SHORT_AD&t;&t;2
DECL|macro|UDF_FLAG_USE_AD_IN_ICB
mdefine_line|#define UDF_FLAG_USE_AD_IN_ICB&t;&t;3
DECL|macro|UDF_FLAG_USE_FILE_CTIME_EA
mdefine_line|#define UDF_FLAG_USE_FILE_CTIME_EA&t;4
DECL|macro|UDF_FLAG_STRICT
mdefine_line|#define UDF_FLAG_STRICT&t;&t;&t;&t;5
DECL|macro|UDF_FLAG_UNDELETE
mdefine_line|#define UDF_FLAG_UNDELETE&t;&t;&t;6
DECL|macro|UDF_FLAG_UNHIDE
mdefine_line|#define UDF_FLAG_UNHIDE&t;&t;&t;&t;7
DECL|macro|UDF_FLAG_VARCONV
mdefine_line|#define UDF_FLAG_VARCONV&t;&t;&t;8
DECL|macro|UDF_PART_FLAG_UNALLOC_BITMAP
mdefine_line|#define UDF_PART_FLAG_UNALLOC_BITMAP&t;&t;0x0001
DECL|macro|UDF_PART_FLAG_UNALLOC_TABLE
mdefine_line|#define UDF_PART_FLAG_UNALLOC_TABLE&t;&t;&t;0x0002
DECL|macro|UDF_PART_FLAG_FREED_BITMAP
mdefine_line|#define UDF_PART_FLAG_FREED_BITMAP&t;&t;&t;0x0004
DECL|macro|UDF_PART_FLAG_FREED_TABLE
mdefine_line|#define UDF_PART_FLAG_FREED_TABLE&t;&t;&t;0x0008
DECL|macro|UDF_SB_FREE
mdefine_line|#define UDF_SB_FREE(X)&bslash;&n;{&bslash;&n;&t;if (UDF_SB(X))&bslash;&n;&t;{&bslash;&n;&t;&t;if (UDF_SB_PARTMAPS(X))&bslash;&n;&t;&t;&t;kfree(UDF_SB_PARTMAPS(X));&bslash;&n;&t;&t;UDF_SB_PARTMAPS(X) = NULL;&bslash;&n;&t;}&bslash;&n;}
DECL|macro|UDF_SB
mdefine_line|#define UDF_SB(X)&t;(&amp;((X)-&gt;u.udf_sb))
DECL|macro|UDF_SB_ALLOC_PARTMAPS
mdefine_line|#define UDF_SB_ALLOC_PARTMAPS(X,Y)&bslash;&n;{&bslash;&n;&t;UDF_SB_NUMPARTS(X) = Y;&bslash;&n;&t;UDF_SB_PARTMAPS(X) = kmalloc(sizeof(struct udf_part_map) * Y, GFP_KERNEL);&bslash;&n;&t;memset(UDF_SB_PARTMAPS(X), 0x00, sizeof(struct udf_part_map) * Y);&bslash;&n;}
DECL|macro|UDF_QUERY_FLAG
mdefine_line|#define UDF_QUERY_FLAG(X,Y)&t;&t;&t;&t;( UDF_SB(X)-&gt;s_flags &amp; ( 1 &lt;&lt; (Y) ) )
DECL|macro|UDF_SET_FLAG
mdefine_line|#define UDF_SET_FLAG(X,Y)&t;&t;&t;&t;( UDF_SB(X)-&gt;s_flags |= ( 1 &lt;&lt; (Y) ) )
DECL|macro|UDF_CLEAR_FLAG
mdefine_line|#define UDF_CLEAR_FLAG(X,Y)&t;&t;&t;&t;( UDF_SB(X)-&gt;s_flags &amp;= ~( 1 &lt;&lt; (Y) ) )
DECL|macro|UDF_UPDATE_UDFREV
mdefine_line|#define UDF_UPDATE_UDFREV(X,Y)&t;&t;&t;( ((Y) &gt; UDF_SB_UDFREV(X)) ? UDF_SB_UDFREV(X) = (Y) : UDF_SB_UDFREV(X) )
DECL|macro|UDF_SB_PARTMAPS
mdefine_line|#define UDF_SB_PARTMAPS(X)&t;&t;&t;&t;( UDF_SB(X)-&gt;s_partmaps )
DECL|macro|UDF_SB_PARTTYPE
mdefine_line|#define UDF_SB_PARTTYPE(X,Y)&t;&t;&t;( UDF_SB_PARTMAPS(X)[(Y)].s_partition_type )
DECL|macro|UDF_SB_PARTROOT
mdefine_line|#define UDF_SB_PARTROOT(X,Y)&t;&t;&t;( UDF_SB_PARTMAPS(X)[(Y)].s_partition_root )
DECL|macro|UDF_SB_PARTLEN
mdefine_line|#define UDF_SB_PARTLEN(X,Y)&t;&t;&t;&t;( UDF_SB_PARTMAPS(X)[(Y)].s_partition_len )
DECL|macro|UDF_SB_PARTVSN
mdefine_line|#define UDF_SB_PARTVSN(X,Y)&t;&t;&t;&t;( UDF_SB_PARTMAPS(X)[(Y)].s_volumeseqnum )
DECL|macro|UDF_SB_PARTNUM
mdefine_line|#define UDF_SB_PARTNUM(X,Y)&t;&t;&t;&t;( UDF_SB_PARTMAPS(X)[(Y)].s_partition_num )
DECL|macro|UDF_SB_TYPESPAR
mdefine_line|#define UDF_SB_TYPESPAR(X,Y)&t;&t;&t;( UDF_SB_PARTMAPS(X)[(Y)].s_type_specific.s_sparing )
DECL|macro|UDF_SB_TYPEVIRT
mdefine_line|#define UDF_SB_TYPEVIRT(X,Y)&t;&t;&t;( UDF_SB_PARTMAPS(X)[(Y)].s_type_specific.s_virtual )
DECL|macro|UDF_SB_PARTFUNC
mdefine_line|#define UDF_SB_PARTFUNC(X,Y)&t;&t;&t;( UDF_SB_PARTMAPS(X)[(Y)].s_partition_func )
DECL|macro|UDF_SB_PARTFLAGS
mdefine_line|#define UDF_SB_PARTFLAGS(X,Y)&t;&t;&t;( UDF_SB_PARTMAPS(X)[(Y)].s_partition_flags )
DECL|macro|UDF_SB_VOLIDENT
mdefine_line|#define UDF_SB_VOLIDENT(X)&t;&t;&t;&t;( UDF_SB(X)-&gt;s_volident )
DECL|macro|UDF_SB_NUMPARTS
mdefine_line|#define UDF_SB_NUMPARTS(X)&t;&t;&t;&t;( UDF_SB(X)-&gt;s_partitions )
DECL|macro|UDF_SB_PARTITION
mdefine_line|#define UDF_SB_PARTITION(X)&t;&t;&t;&t;( UDF_SB(X)-&gt;s_partition )
DECL|macro|UDF_SB_SESSION
mdefine_line|#define UDF_SB_SESSION(X)&t;&t;&t;&t;( UDF_SB(X)-&gt;s_session )
DECL|macro|UDF_SB_ANCHOR
mdefine_line|#define UDF_SB_ANCHOR(X)&t;&t;&t;&t;( UDF_SB(X)-&gt;s_anchor )
DECL|macro|UDF_SB_LASTBLOCK
mdefine_line|#define UDF_SB_LASTBLOCK(X)&t;&t;&t;&t;( UDF_SB(X)-&gt;s_lastblock )
DECL|macro|UDF_SB_LVIDBH
mdefine_line|#define UDF_SB_LVIDBH(X)&t;&t;&t;&t;( UDF_SB(X)-&gt;s_lvidbh )
DECL|macro|UDF_SB_LVID
mdefine_line|#define UDF_SB_LVID(X)&t;&t;&t;&t;&t;( (struct LogicalVolIntegrityDesc *)UDF_SB_LVIDBH(X)-&gt;b_data )
DECL|macro|UDF_SB_LVIDIU
mdefine_line|#define UDF_SB_LVIDIU(X)&t;&t;&t;&t;( (struct LogicalVolIntegrityDescImpUse *)&amp;(UDF_SB_LVID(X)-&gt;impUse[UDF_SB_LVID(X)-&gt;numOfPartitions * 2 * sizeof(Uint32)/sizeof(Uint8)]) )
DECL|macro|UDF_SB_LOADED_BLOCK_BITMAPS
mdefine_line|#define UDF_SB_LOADED_BLOCK_BITMAPS(X)&t;( UDF_SB(X)-&gt;s_loaded_block_bitmaps )
DECL|macro|UDF_SB_BLOCK_BITMAP_NUMBER
mdefine_line|#define UDF_SB_BLOCK_BITMAP_NUMBER(X,Y) ( UDF_SB(X)-&gt;s_block_bitmap_number[(Y)] )
DECL|macro|UDF_SB_BLOCK_BITMAP
mdefine_line|#define UDF_SB_BLOCK_BITMAP(X,Y)&t;&t;( UDF_SB(X)-&gt;s_block_bitmap[(Y)] )
DECL|macro|UDF_SB_UMASK
mdefine_line|#define UDF_SB_UMASK(X)&t;&t;&t;&t;&t;( UDF_SB(X)-&gt;s_umask )
DECL|macro|UDF_SB_GID
mdefine_line|#define UDF_SB_GID(X)&t;&t;&t;&t;&t;( UDF_SB(X)-&gt;s_gid )
DECL|macro|UDF_SB_UID
mdefine_line|#define UDF_SB_UID(X)&t;&t;&t;&t;&t;( UDF_SB(X)-&gt;s_uid )
DECL|macro|UDF_SB_RECORDTIME
mdefine_line|#define UDF_SB_RECORDTIME(X)&t;&t;&t;( UDF_SB(X)-&gt;s_recordtime )
DECL|macro|UDF_SB_SERIALNUM
mdefine_line|#define UDF_SB_SERIALNUM(X)&t;&t;&t;&t;( UDF_SB(X)-&gt;s_serialnum )
DECL|macro|UDF_SB_UDFREV
mdefine_line|#define UDF_SB_UDFREV(X)&t;&t;&t;&t;( UDF_SB(X)-&gt;s_udfrev )
DECL|macro|UDF_SB_FLAGS
mdefine_line|#define UDF_SB_FLAGS(X)&t;&t;&t;&t;&t;( UDF_SB(X)-&gt;s_flags )
DECL|macro|UDF_SB_VAT
mdefine_line|#define UDF_SB_VAT(X)&t;&t;&t;&t;&t;( UDF_SB(X)-&gt;s_vat )
macro_line|#endif /* __LINUX_UDF_SB_H */
eof
