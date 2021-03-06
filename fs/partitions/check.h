multiline_comment|/*&n; * add_partition adds a partitions details to the devices partition&n; * description.&n; */
r_void
id|add_gd_partition
c_func
(paren
r_struct
id|gendisk
op_star
id|hd
comma
r_int
id|minor
comma
r_int
id|start
comma
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/*&n; * Get the default block size for this device&n; */
r_int
r_int
id|get_ptable_blocksize
c_func
(paren
id|kdev_t
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|warn_no_part
suffix:semicolon
eof
