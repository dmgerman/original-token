macro_line|#ifndef _ISOFS_FS_H
DECL|macro|_ISOFS_FS_H
mdefine_line|#define _ISOFS_FS_H
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/*&n; * The isofs filesystem constants/structures&n; */
multiline_comment|/* This part borrowed from the bsd386 isofs */
DECL|macro|ISODCL
mdefine_line|#define ISODCL(from, to) (to - from + 1)
DECL|struct|iso_volume_descriptor
r_struct
id|iso_volume_descriptor
(brace
DECL|member|type
r_char
id|type
(braket
id|ISODCL
c_func
(paren
l_int|1
comma
l_int|1
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|id
r_char
id|id
(braket
id|ISODCL
c_func
(paren
l_int|2
comma
l_int|6
)paren
)braket
suffix:semicolon
DECL|member|version
r_char
id|version
(braket
id|ISODCL
c_func
(paren
l_int|7
comma
l_int|7
)paren
)braket
suffix:semicolon
DECL|member|data
r_char
id|data
(braket
id|ISODCL
c_func
(paren
l_int|8
comma
l_int|2048
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* volume descriptor types */
DECL|macro|ISO_VD_PRIMARY
mdefine_line|#define ISO_VD_PRIMARY 1
DECL|macro|ISO_VD_SUPPLEMENTARY
mdefine_line|#define ISO_VD_SUPPLEMENTARY 2
DECL|macro|ISO_VD_END
mdefine_line|#define ISO_VD_END 255
DECL|macro|ISO_STANDARD_ID
mdefine_line|#define ISO_STANDARD_ID &quot;CD001&quot;
DECL|struct|iso_primary_descriptor
r_struct
id|iso_primary_descriptor
(brace
DECL|member|type
r_char
id|type
(braket
id|ISODCL
(paren
l_int|1
comma
l_int|1
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|id
r_char
id|id
(braket
id|ISODCL
(paren
l_int|2
comma
l_int|6
)paren
)braket
suffix:semicolon
DECL|member|version
r_char
id|version
(braket
id|ISODCL
(paren
l_int|7
comma
l_int|7
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|unused1
r_char
id|unused1
(braket
id|ISODCL
(paren
l_int|8
comma
l_int|8
)paren
)braket
suffix:semicolon
DECL|member|system_id
r_char
id|system_id
(braket
id|ISODCL
(paren
l_int|9
comma
l_int|40
)paren
)braket
suffix:semicolon
multiline_comment|/* achars */
DECL|member|volume_id
r_char
id|volume_id
(braket
id|ISODCL
(paren
l_int|41
comma
l_int|72
)paren
)braket
suffix:semicolon
multiline_comment|/* dchars */
DECL|member|unused2
r_char
id|unused2
(braket
id|ISODCL
(paren
l_int|73
comma
l_int|80
)paren
)braket
suffix:semicolon
DECL|member|volume_space_size
r_char
id|volume_space_size
(braket
id|ISODCL
(paren
l_int|81
comma
l_int|88
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|unused3
r_char
id|unused3
(braket
id|ISODCL
(paren
l_int|89
comma
l_int|120
)paren
)braket
suffix:semicolon
DECL|member|volume_set_size
r_char
id|volume_set_size
(braket
id|ISODCL
(paren
l_int|121
comma
l_int|124
)paren
)braket
suffix:semicolon
multiline_comment|/* 723 */
DECL|member|volume_sequence_number
r_char
id|volume_sequence_number
(braket
id|ISODCL
(paren
l_int|125
comma
l_int|128
)paren
)braket
suffix:semicolon
multiline_comment|/* 723 */
DECL|member|logical_block_size
r_char
id|logical_block_size
(braket
id|ISODCL
(paren
l_int|129
comma
l_int|132
)paren
)braket
suffix:semicolon
multiline_comment|/* 723 */
DECL|member|path_table_size
r_char
id|path_table_size
(braket
id|ISODCL
(paren
l_int|133
comma
l_int|140
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|type_l_path_table
r_char
id|type_l_path_table
(braket
id|ISODCL
(paren
l_int|141
comma
l_int|144
)paren
)braket
suffix:semicolon
multiline_comment|/* 731 */
DECL|member|opt_type_l_path_table
r_char
id|opt_type_l_path_table
(braket
id|ISODCL
(paren
l_int|145
comma
l_int|148
)paren
)braket
suffix:semicolon
multiline_comment|/* 731 */
DECL|member|type_m_path_table
r_char
id|type_m_path_table
(braket
id|ISODCL
(paren
l_int|149
comma
l_int|152
)paren
)braket
suffix:semicolon
multiline_comment|/* 732 */
DECL|member|opt_type_m_path_table
r_char
id|opt_type_m_path_table
(braket
id|ISODCL
(paren
l_int|153
comma
l_int|156
)paren
)braket
suffix:semicolon
multiline_comment|/* 732 */
DECL|member|root_directory_record
r_char
id|root_directory_record
(braket
id|ISODCL
(paren
l_int|157
comma
l_int|190
)paren
)braket
suffix:semicolon
multiline_comment|/* 9.1 */
DECL|member|volume_set_id
r_char
id|volume_set_id
(braket
id|ISODCL
(paren
l_int|191
comma
l_int|318
)paren
)braket
suffix:semicolon
multiline_comment|/* dchars */
DECL|member|publisher_id
r_char
id|publisher_id
(braket
id|ISODCL
(paren
l_int|319
comma
l_int|446
)paren
)braket
suffix:semicolon
multiline_comment|/* achars */
DECL|member|preparer_id
r_char
id|preparer_id
(braket
id|ISODCL
(paren
l_int|447
comma
l_int|574
)paren
)braket
suffix:semicolon
multiline_comment|/* achars */
DECL|member|application_id
r_char
id|application_id
(braket
id|ISODCL
(paren
l_int|575
comma
l_int|702
)paren
)braket
suffix:semicolon
multiline_comment|/* achars */
DECL|member|copyright_file_id
r_char
id|copyright_file_id
(braket
id|ISODCL
(paren
l_int|703
comma
l_int|739
)paren
)braket
suffix:semicolon
multiline_comment|/* 7.5 dchars */
DECL|member|abstract_file_id
r_char
id|abstract_file_id
(braket
id|ISODCL
(paren
l_int|740
comma
l_int|776
)paren
)braket
suffix:semicolon
multiline_comment|/* 7.5 dchars */
DECL|member|bibliographic_file_id
r_char
id|bibliographic_file_id
(braket
id|ISODCL
(paren
l_int|777
comma
l_int|813
)paren
)braket
suffix:semicolon
multiline_comment|/* 7.5 dchars */
DECL|member|creation_date
r_char
id|creation_date
(braket
id|ISODCL
(paren
l_int|814
comma
l_int|830
)paren
)braket
suffix:semicolon
multiline_comment|/* 8.4.26.1 */
DECL|member|modification_date
r_char
id|modification_date
(braket
id|ISODCL
(paren
l_int|831
comma
l_int|847
)paren
)braket
suffix:semicolon
multiline_comment|/* 8.4.26.1 */
DECL|member|expiration_date
r_char
id|expiration_date
(braket
id|ISODCL
(paren
l_int|848
comma
l_int|864
)paren
)braket
suffix:semicolon
multiline_comment|/* 8.4.26.1 */
DECL|member|effective_date
r_char
id|effective_date
(braket
id|ISODCL
(paren
l_int|865
comma
l_int|881
)paren
)braket
suffix:semicolon
multiline_comment|/* 8.4.26.1 */
DECL|member|file_structure_version
r_char
id|file_structure_version
(braket
id|ISODCL
(paren
l_int|882
comma
l_int|882
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|unused4
r_char
id|unused4
(braket
id|ISODCL
(paren
l_int|883
comma
l_int|883
)paren
)braket
suffix:semicolon
DECL|member|application_data
r_char
id|application_data
(braket
id|ISODCL
(paren
l_int|884
comma
l_int|1395
)paren
)braket
suffix:semicolon
DECL|member|unused5
r_char
id|unused5
(braket
id|ISODCL
(paren
l_int|1396
comma
l_int|2048
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Almost the same as the primary descriptor but two fields are specified */
DECL|struct|iso_supplementary_descriptor
r_struct
id|iso_supplementary_descriptor
(brace
DECL|member|type
r_char
id|type
(braket
id|ISODCL
(paren
l_int|1
comma
l_int|1
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|id
r_char
id|id
(braket
id|ISODCL
(paren
l_int|2
comma
l_int|6
)paren
)braket
suffix:semicolon
DECL|member|version
r_char
id|version
(braket
id|ISODCL
(paren
l_int|7
comma
l_int|7
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|flags
r_char
id|flags
(braket
id|ISODCL
(paren
l_int|8
comma
l_int|8
)paren
)braket
suffix:semicolon
multiline_comment|/* 853 */
DECL|member|system_id
r_char
id|system_id
(braket
id|ISODCL
(paren
l_int|9
comma
l_int|40
)paren
)braket
suffix:semicolon
multiline_comment|/* achars */
DECL|member|volume_id
r_char
id|volume_id
(braket
id|ISODCL
(paren
l_int|41
comma
l_int|72
)paren
)braket
suffix:semicolon
multiline_comment|/* dchars */
DECL|member|unused2
r_char
id|unused2
(braket
id|ISODCL
(paren
l_int|73
comma
l_int|80
)paren
)braket
suffix:semicolon
DECL|member|volume_space_size
r_char
id|volume_space_size
(braket
id|ISODCL
(paren
l_int|81
comma
l_int|88
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|escape
r_char
id|escape
(braket
id|ISODCL
(paren
l_int|89
comma
l_int|120
)paren
)braket
suffix:semicolon
multiline_comment|/* 856 */
DECL|member|volume_set_size
r_char
id|volume_set_size
(braket
id|ISODCL
(paren
l_int|121
comma
l_int|124
)paren
)braket
suffix:semicolon
multiline_comment|/* 723 */
DECL|member|volume_sequence_number
r_char
id|volume_sequence_number
(braket
id|ISODCL
(paren
l_int|125
comma
l_int|128
)paren
)braket
suffix:semicolon
multiline_comment|/* 723 */
DECL|member|logical_block_size
r_char
id|logical_block_size
(braket
id|ISODCL
(paren
l_int|129
comma
l_int|132
)paren
)braket
suffix:semicolon
multiline_comment|/* 723 */
DECL|member|path_table_size
r_char
id|path_table_size
(braket
id|ISODCL
(paren
l_int|133
comma
l_int|140
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|type_l_path_table
r_char
id|type_l_path_table
(braket
id|ISODCL
(paren
l_int|141
comma
l_int|144
)paren
)braket
suffix:semicolon
multiline_comment|/* 731 */
DECL|member|opt_type_l_path_table
r_char
id|opt_type_l_path_table
(braket
id|ISODCL
(paren
l_int|145
comma
l_int|148
)paren
)braket
suffix:semicolon
multiline_comment|/* 731 */
DECL|member|type_m_path_table
r_char
id|type_m_path_table
(braket
id|ISODCL
(paren
l_int|149
comma
l_int|152
)paren
)braket
suffix:semicolon
multiline_comment|/* 732 */
DECL|member|opt_type_m_path_table
r_char
id|opt_type_m_path_table
(braket
id|ISODCL
(paren
l_int|153
comma
l_int|156
)paren
)braket
suffix:semicolon
multiline_comment|/* 732 */
DECL|member|root_directory_record
r_char
id|root_directory_record
(braket
id|ISODCL
(paren
l_int|157
comma
l_int|190
)paren
)braket
suffix:semicolon
multiline_comment|/* 9.1 */
DECL|member|volume_set_id
r_char
id|volume_set_id
(braket
id|ISODCL
(paren
l_int|191
comma
l_int|318
)paren
)braket
suffix:semicolon
multiline_comment|/* dchars */
DECL|member|publisher_id
r_char
id|publisher_id
(braket
id|ISODCL
(paren
l_int|319
comma
l_int|446
)paren
)braket
suffix:semicolon
multiline_comment|/* achars */
DECL|member|preparer_id
r_char
id|preparer_id
(braket
id|ISODCL
(paren
l_int|447
comma
l_int|574
)paren
)braket
suffix:semicolon
multiline_comment|/* achars */
DECL|member|application_id
r_char
id|application_id
(braket
id|ISODCL
(paren
l_int|575
comma
l_int|702
)paren
)braket
suffix:semicolon
multiline_comment|/* achars */
DECL|member|copyright_file_id
r_char
id|copyright_file_id
(braket
id|ISODCL
(paren
l_int|703
comma
l_int|739
)paren
)braket
suffix:semicolon
multiline_comment|/* 7.5 dchars */
DECL|member|abstract_file_id
r_char
id|abstract_file_id
(braket
id|ISODCL
(paren
l_int|740
comma
l_int|776
)paren
)braket
suffix:semicolon
multiline_comment|/* 7.5 dchars */
DECL|member|bibliographic_file_id
r_char
id|bibliographic_file_id
(braket
id|ISODCL
(paren
l_int|777
comma
l_int|813
)paren
)braket
suffix:semicolon
multiline_comment|/* 7.5 dchars */
DECL|member|creation_date
r_char
id|creation_date
(braket
id|ISODCL
(paren
l_int|814
comma
l_int|830
)paren
)braket
suffix:semicolon
multiline_comment|/* 8.4.26.1 */
DECL|member|modification_date
r_char
id|modification_date
(braket
id|ISODCL
(paren
l_int|831
comma
l_int|847
)paren
)braket
suffix:semicolon
multiline_comment|/* 8.4.26.1 */
DECL|member|expiration_date
r_char
id|expiration_date
(braket
id|ISODCL
(paren
l_int|848
comma
l_int|864
)paren
)braket
suffix:semicolon
multiline_comment|/* 8.4.26.1 */
DECL|member|effective_date
r_char
id|effective_date
(braket
id|ISODCL
(paren
l_int|865
comma
l_int|881
)paren
)braket
suffix:semicolon
multiline_comment|/* 8.4.26.1 */
DECL|member|file_structure_version
r_char
id|file_structure_version
(braket
id|ISODCL
(paren
l_int|882
comma
l_int|882
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|unused4
r_char
id|unused4
(braket
id|ISODCL
(paren
l_int|883
comma
l_int|883
)paren
)braket
suffix:semicolon
DECL|member|application_data
r_char
id|application_data
(braket
id|ISODCL
(paren
l_int|884
comma
l_int|1395
)paren
)braket
suffix:semicolon
DECL|member|unused5
r_char
id|unused5
(braket
id|ISODCL
(paren
l_int|1396
comma
l_int|2048
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|HS_STANDARD_ID
mdefine_line|#define HS_STANDARD_ID &quot;CDROM&quot;
DECL|struct|hs_volume_descriptor
r_struct
id|hs_volume_descriptor
(brace
DECL|member|foo
r_char
id|foo
(braket
id|ISODCL
(paren
l_int|1
comma
l_int|8
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|type
r_char
id|type
(braket
id|ISODCL
(paren
l_int|9
comma
l_int|9
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|id
r_char
id|id
(braket
id|ISODCL
(paren
l_int|10
comma
l_int|14
)paren
)braket
suffix:semicolon
DECL|member|version
r_char
id|version
(braket
id|ISODCL
(paren
l_int|15
comma
l_int|15
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|data
r_char
id|data
(braket
id|ISODCL
c_func
(paren
l_int|16
comma
l_int|2048
)paren
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hs_primary_descriptor
r_struct
id|hs_primary_descriptor
(brace
DECL|member|foo
r_char
id|foo
(braket
id|ISODCL
(paren
l_int|1
comma
l_int|8
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|type
r_char
id|type
(braket
id|ISODCL
(paren
l_int|9
comma
l_int|9
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|id
r_char
id|id
(braket
id|ISODCL
(paren
l_int|10
comma
l_int|14
)paren
)braket
suffix:semicolon
DECL|member|version
r_char
id|version
(braket
id|ISODCL
(paren
l_int|15
comma
l_int|15
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|unused1
r_char
id|unused1
(braket
id|ISODCL
(paren
l_int|16
comma
l_int|16
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|system_id
r_char
id|system_id
(braket
id|ISODCL
(paren
l_int|17
comma
l_int|48
)paren
)braket
suffix:semicolon
multiline_comment|/* achars */
DECL|member|volume_id
r_char
id|volume_id
(braket
id|ISODCL
(paren
l_int|49
comma
l_int|80
)paren
)braket
suffix:semicolon
multiline_comment|/* dchars */
DECL|member|unused2
r_char
id|unused2
(braket
id|ISODCL
(paren
l_int|81
comma
l_int|88
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|volume_space_size
r_char
id|volume_space_size
(braket
id|ISODCL
(paren
l_int|89
comma
l_int|96
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|unused3
r_char
id|unused3
(braket
id|ISODCL
(paren
l_int|97
comma
l_int|128
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|volume_set_size
r_char
id|volume_set_size
(braket
id|ISODCL
(paren
l_int|129
comma
l_int|132
)paren
)braket
suffix:semicolon
multiline_comment|/* 723 */
DECL|member|volume_sequence_number
r_char
id|volume_sequence_number
(braket
id|ISODCL
(paren
l_int|133
comma
l_int|136
)paren
)braket
suffix:semicolon
multiline_comment|/* 723 */
DECL|member|logical_block_size
r_char
id|logical_block_size
(braket
id|ISODCL
(paren
l_int|137
comma
l_int|140
)paren
)braket
suffix:semicolon
multiline_comment|/* 723 */
DECL|member|path_table_size
r_char
id|path_table_size
(braket
id|ISODCL
(paren
l_int|141
comma
l_int|148
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|type_l_path_table
r_char
id|type_l_path_table
(braket
id|ISODCL
(paren
l_int|149
comma
l_int|152
)paren
)braket
suffix:semicolon
multiline_comment|/* 731 */
DECL|member|unused4
r_char
id|unused4
(braket
id|ISODCL
(paren
l_int|153
comma
l_int|180
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|root_directory_record
r_char
id|root_directory_record
(braket
id|ISODCL
(paren
l_int|181
comma
l_int|214
)paren
)braket
suffix:semicolon
multiline_comment|/* 9.1 */
)brace
suffix:semicolon
multiline_comment|/* We use this to help us look up the parent inode numbers. */
DECL|struct|iso_path_table
r_struct
id|iso_path_table
(brace
DECL|member|name_len
r_int
r_char
id|name_len
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 721 */
DECL|member|extent
r_char
id|extent
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* 731 */
DECL|member|parent
r_char
id|parent
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* 721 */
DECL|member|name
r_char
id|name
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* high sierra is identical to iso, except that the date is only 6 bytes, and&n;   there is an extra reserved byte after the flags */
DECL|struct|iso_directory_record
r_struct
id|iso_directory_record
(brace
DECL|member|length
r_char
id|length
(braket
id|ISODCL
(paren
l_int|1
comma
l_int|1
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|ext_attr_length
r_char
id|ext_attr_length
(braket
id|ISODCL
(paren
l_int|2
comma
l_int|2
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|extent
r_char
id|extent
(braket
id|ISODCL
(paren
l_int|3
comma
l_int|10
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|size
r_char
id|size
(braket
id|ISODCL
(paren
l_int|11
comma
l_int|18
)paren
)braket
suffix:semicolon
multiline_comment|/* 733 */
DECL|member|date
r_char
id|date
(braket
id|ISODCL
(paren
l_int|19
comma
l_int|25
)paren
)braket
suffix:semicolon
multiline_comment|/* 7 by 711 */
DECL|member|flags
r_char
id|flags
(braket
id|ISODCL
(paren
l_int|26
comma
l_int|26
)paren
)braket
suffix:semicolon
DECL|member|file_unit_size
r_char
id|file_unit_size
(braket
id|ISODCL
(paren
l_int|27
comma
l_int|27
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|interleave
r_char
id|interleave
(braket
id|ISODCL
(paren
l_int|28
comma
l_int|28
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|volume_sequence_number
r_char
id|volume_sequence_number
(braket
id|ISODCL
(paren
l_int|29
comma
l_int|32
)paren
)braket
suffix:semicolon
multiline_comment|/* 723 */
DECL|member|name_len
r_int
r_char
id|name_len
(braket
id|ISODCL
(paren
l_int|33
comma
l_int|33
)paren
)braket
suffix:semicolon
multiline_comment|/* 711 */
DECL|member|name
r_char
id|name
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ISOFS_BLOCK_BITS
mdefine_line|#define ISOFS_BLOCK_BITS 11
DECL|macro|ISOFS_BLOCK_SIZE
mdefine_line|#define ISOFS_BLOCK_SIZE 2048
DECL|macro|ISOFS_BUFFER_SIZE
mdefine_line|#define ISOFS_BUFFER_SIZE(INODE) ((INODE)-&gt;i_sb-&gt;s_blocksize)
DECL|macro|ISOFS_BUFFER_BITS
mdefine_line|#define ISOFS_BUFFER_BITS(INODE) ((INODE)-&gt;i_sb-&gt;s_blocksize_bits)
DECL|macro|ISOFS_ZONE_BITS
mdefine_line|#define ISOFS_ZONE_BITS(INODE)   ((INODE)-&gt;i_sb-&gt;u.isofs_sb.s_log_zone_size)
DECL|macro|ISOFS_SUPER_MAGIC
mdefine_line|#define ISOFS_SUPER_MAGIC 0x9660
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|isonum_711
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isonum_712
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isonum_721
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isonum_722
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isonum_723
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isonum_731
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isonum_732
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isonum_733
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|iso_date
c_func
(paren
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|parse_rock_ridge_inode
c_func
(paren
r_struct
id|iso_directory_record
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|get_rock_ridge_filename
c_func
(paren
r_struct
id|iso_directory_record
op_star
comma
r_char
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|rock_ridge_symlink_readpage
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_int
id|find_rock_ridge_relocation
c_func
(paren
r_struct
id|iso_directory_record
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_int
id|get_joliet_filename
c_func
(paren
r_struct
id|iso_directory_record
op_star
comma
r_struct
id|inode
op_star
comma
r_int
r_char
op_star
)paren
suffix:semicolon
r_int
id|get_acorn_filename
c_func
(paren
r_struct
id|iso_directory_record
op_star
comma
r_char
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|dentry
op_star
id|isofs_lookup
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isofs_get_block
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
comma
r_struct
id|buffer_head
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|isofs_bmap
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|init_iso9660_fs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|isofs_lookup_grandparent
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|isofs_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|isofs_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|isofs_symlink_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|isofs_chrdev_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|isofs_blkdev_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|isofs_fifo_inode_operations
suffix:semicolon
multiline_comment|/* The following macros are used to check for memory leaks. */
macro_line|#ifdef LEAK_CHECK
DECL|macro|free_s
mdefine_line|#define free_s leak_check_free_s
DECL|macro|malloc
mdefine_line|#define malloc leak_check_malloc
DECL|macro|bread
mdefine_line|#define bread leak_check_bread
DECL|macro|brelse
mdefine_line|#define brelse leak_check_brelse
r_extern
r_void
op_star
id|leak_check_malloc
c_func
(paren
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|leak_check_free_s
c_func
(paren
r_void
op_star
id|obj
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_struct
id|buffer_head
op_star
id|leak_check_bread
c_func
(paren
r_int
id|dev
comma
r_int
id|block
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|leak_check_brelse
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
macro_line|#endif /* LEAK_CHECK */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
