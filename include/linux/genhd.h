macro_line|#ifndef _GENHD_H
DECL|macro|_GENHD_H
mdefine_line|#define _GENHD_H
multiline_comment|/*&n; * &t;genhd.h Copyright (C) 1992 Drew Eckhardt&n; *&t;Generic hard disk header file by  &n; * &t;&t;Drew Eckhardt&n; *&n; *&t;&t;&lt;drew@colorado.edu&gt;&n; */
DECL|macro|EXTENDED_PARTITION
mdefine_line|#define EXTENDED_PARTITION 5
DECL|struct|partition
r_struct
id|partition
(brace
DECL|member|boot_ind
r_int
r_char
id|boot_ind
suffix:semicolon
multiline_comment|/* 0x80 - active */
DECL|member|head
r_int
r_char
id|head
suffix:semicolon
multiline_comment|/* starting head */
DECL|member|sector
r_int
r_char
id|sector
suffix:semicolon
multiline_comment|/* starting sector */
DECL|member|cyl
r_int
r_char
id|cyl
suffix:semicolon
multiline_comment|/* starting cylinder */
DECL|member|sys_ind
r_int
r_char
id|sys_ind
suffix:semicolon
multiline_comment|/* What partition type */
DECL|member|end_head
r_int
r_char
id|end_head
suffix:semicolon
multiline_comment|/* end head */
DECL|member|end_sector
r_int
r_char
id|end_sector
suffix:semicolon
multiline_comment|/* end sector */
DECL|member|end_cyl
r_int
r_char
id|end_cyl
suffix:semicolon
multiline_comment|/* end cylinder */
DECL|member|start_sect
r_int
r_int
id|start_sect
suffix:semicolon
multiline_comment|/* starting sector counting from 0 */
DECL|member|nr_sects
r_int
r_int
id|nr_sects
suffix:semicolon
multiline_comment|/* nr of sectors in partition */
)brace
suffix:semicolon
DECL|struct|hd_struct
r_struct
id|hd_struct
(brace
DECL|member|start_sect
r_int
id|start_sect
suffix:semicolon
DECL|member|nr_sects
r_int
id|nr_sects
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|gendisk
r_struct
id|gendisk
(brace
DECL|member|major
r_int
id|major
suffix:semicolon
multiline_comment|/* major number of driver */
DECL|member|major_name
r_char
op_star
id|major_name
suffix:semicolon
multiline_comment|/* name of major driver */
DECL|member|minor_shift
r_int
id|minor_shift
suffix:semicolon
multiline_comment|/* number of times minor is shifted to&n;&t;&t;&t;&t;&t;   get real minor */
DECL|member|max_p
r_int
id|max_p
suffix:semicolon
multiline_comment|/* maximum partitions per device */
DECL|member|max_nr
r_int
id|max_nr
suffix:semicolon
multiline_comment|/* maximum number of real devices */
DECL|member|init
r_void
(paren
op_star
id|init
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Initialization called before we do our thing */
DECL|member|part
r_struct
id|hd_struct
op_star
id|part
suffix:semicolon
multiline_comment|/* partition table */
DECL|member|sizes
r_int
op_star
id|sizes
suffix:semicolon
multiline_comment|/* block sizes */
DECL|member|nr_real
r_int
id|nr_real
suffix:semicolon
multiline_comment|/* number of real devices */
DECL|member|real_devices
r_void
op_star
id|real_devices
suffix:semicolon
multiline_comment|/* internal use */
DECL|member|next
r_struct
id|gendisk
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|NR_GENDISKS
suffix:semicolon
multiline_comment|/* total */
r_extern
r_struct
id|gendisk
op_star
id|gendisk_head
suffix:semicolon
multiline_comment|/* linked list of disks */
macro_line|#endif
eof
