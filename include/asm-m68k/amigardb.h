macro_line|#ifndef _LINUX_AMIGARDB_H
DECL|macro|_LINUX_AMIGARDB_H
mdefine_line|#define _LINUX_AMIGARDB_H 1
DECL|macro|ULONG
mdefine_line|#define ULONG&t;u_long
DECL|macro|LONG
mdefine_line|#define LONG&t;long
DECL|macro|UBYTE
mdefine_line|#define UBYTE&t;u_char
multiline_comment|/* definitions for the Amiga RigidDiskBlock layout, which always starts in &n;   cylinder 0 of a medium. Taken from page 254f of the RKM: Devices */
DECL|struct|RigidDiskBlock
r_struct
id|RigidDiskBlock
(brace
DECL|member|rdb_ID
id|ULONG
id|rdb_ID
suffix:semicolon
multiline_comment|/* 4 character identifier */
DECL|member|rdb_SummedLongs
id|ULONG
id|rdb_SummedLongs
suffix:semicolon
multiline_comment|/* size of this checksummed structure */
DECL|member|rdb_ChkSum
id|LONG
id|rdb_ChkSum
suffix:semicolon
multiline_comment|/* block checksum (longword sum to zero) */
DECL|member|rdb_HostID
id|ULONG
id|rdb_HostID
suffix:semicolon
multiline_comment|/* SCSI Target ID of host */
DECL|member|rdb_BlockBytes
id|ULONG
id|rdb_BlockBytes
suffix:semicolon
multiline_comment|/* size of disk blocks */
DECL|member|rdb_Flags
id|ULONG
id|rdb_Flags
suffix:semicolon
multiline_comment|/* see below for defines */
multiline_comment|/* block list heads */
DECL|member|rdb_BadBlockList
id|ULONG
id|rdb_BadBlockList
suffix:semicolon
multiline_comment|/* optional bad block list */
DECL|member|rdb_PartitionList
id|ULONG
id|rdb_PartitionList
suffix:semicolon
multiline_comment|/* optional first partition block */
DECL|member|rdb_FileSysHeaderList
id|ULONG
id|rdb_FileSysHeaderList
suffix:semicolon
multiline_comment|/* optional file system header block */
DECL|member|rdb_DriveInit
id|ULONG
id|rdb_DriveInit
suffix:semicolon
multiline_comment|/* optional drive-specific init code */
multiline_comment|/* DriveInit(lun,rdb,ior): &quot;C&quot; stk &amp; d0/a0/a1 */
DECL|member|rdb_Reserved1
id|ULONG
id|rdb_Reserved1
(braket
l_int|6
)braket
suffix:semicolon
multiline_comment|/* set to $ffffffff */
multiline_comment|/* physical drive characteristics */
DECL|member|rdb_Cylinders
id|ULONG
id|rdb_Cylinders
suffix:semicolon
multiline_comment|/* number of drive cylinders */
DECL|member|rdb_Sectors
id|ULONG
id|rdb_Sectors
suffix:semicolon
multiline_comment|/* sectors per track */
DECL|member|rdb_Heads
id|ULONG
id|rdb_Heads
suffix:semicolon
multiline_comment|/* number of drive heads */
DECL|member|rdb_Interleave
id|ULONG
id|rdb_Interleave
suffix:semicolon
multiline_comment|/* interleave */
DECL|member|rdb_Park
id|ULONG
id|rdb_Park
suffix:semicolon
multiline_comment|/* landing zone cylinder */
DECL|member|rdb_Reserved2
id|ULONG
id|rdb_Reserved2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|rdb_WritePreComp
id|ULONG
id|rdb_WritePreComp
suffix:semicolon
multiline_comment|/* starting cylinder: write precompensation */
DECL|member|rdb_ReducedWrite
id|ULONG
id|rdb_ReducedWrite
suffix:semicolon
multiline_comment|/* starting cylinder: reduced write current */
DECL|member|rdb_StepRate
id|ULONG
id|rdb_StepRate
suffix:semicolon
multiline_comment|/* drive step rate */
DECL|member|rdb_Reserved3
id|ULONG
id|rdb_Reserved3
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* logical drive characteristics */
DECL|member|rdb_RDBBlocksLo
id|ULONG
id|rdb_RDBBlocksLo
suffix:semicolon
multiline_comment|/* low block of range reserved for hardblocks */
DECL|member|rdb_RDBBlocksHi
id|ULONG
id|rdb_RDBBlocksHi
suffix:semicolon
multiline_comment|/* high block of range for these hardblocks */
DECL|member|rdb_LoCylinder
id|ULONG
id|rdb_LoCylinder
suffix:semicolon
multiline_comment|/* low cylinder of partitionable disk area */
DECL|member|rdb_HiCylinder
id|ULONG
id|rdb_HiCylinder
suffix:semicolon
multiline_comment|/* high cylinder of partitionable data area */
DECL|member|rdb_CylBlocks
id|ULONG
id|rdb_CylBlocks
suffix:semicolon
multiline_comment|/* number of blocks available per cylinder */
DECL|member|rdb_AutoParkSeconds
id|ULONG
id|rdb_AutoParkSeconds
suffix:semicolon
multiline_comment|/* zero for no auto park */
DECL|member|rdb_HighRDSKBlock
id|ULONG
id|rdb_HighRDSKBlock
suffix:semicolon
multiline_comment|/* highest block used by RDSK */
multiline_comment|/* (not including replacement bad blocks) */
DECL|member|rdb_Reserved4
id|ULONG
id|rdb_Reserved4
suffix:semicolon
multiline_comment|/* drive identification */
DECL|member|rdb_DiskVendor
r_char
id|rdb_DiskVendor
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|rdb_DiskProduct
r_char
id|rdb_DiskProduct
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|rdb_DiskRevision
r_char
id|rdb_DiskRevision
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|rdb_ControllerVendor
r_char
id|rdb_ControllerVendor
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|rdb_ControllerProduct
r_char
id|rdb_ControllerProduct
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|rdb_ControllerRevision
r_char
id|rdb_ControllerRevision
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|rdb_Reserved5
id|ULONG
id|rdb_Reserved5
(braket
l_int|10
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IDNAME_RIGIDDISK
mdefine_line|#define&t;IDNAME_RIGIDDISK&t;0x5244534B&t;/* &squot;RDSK&squot; */
DECL|macro|RDB_LOCATION_LIMIT
mdefine_line|#define&t;RDB_LOCATION_LIMIT&t;16
DECL|macro|RDBFB_LAST
mdefine_line|#define&t;RDBFB_LAST&t;0&t;/* no disks exist to be configured after */
DECL|macro|RDBFF_LAST
mdefine_line|#define&t;RDBFF_LAST&t;0x01L&t;/*   this one on this controller */
DECL|macro|RDBFB_LASTLUN
mdefine_line|#define&t;RDBFB_LASTLUN&t;1&t;/* no LUNs exist to be configured greater */
DECL|macro|RDBFF_LASTLUN
mdefine_line|#define&t;RDBFF_LASTLUN&t;0x02L&t;/*   than this one at this SCSI Target ID */
DECL|macro|RDBFB_LASTTID
mdefine_line|#define&t;RDBFB_LASTTID&t;2&t;/* no Target IDs exist to be configured */
DECL|macro|RDBFF_LASTTID
mdefine_line|#define&t;RDBFF_LASTTID&t;0x04L&t;/*   greater than this one on this SCSI bus */
DECL|macro|RDBFB_NORESELECT
mdefine_line|#define&t;RDBFB_NORESELECT 3&t;/* don&squot;t bother trying to perform reselection */
DECL|macro|RDBFF_NORESELECT
mdefine_line|#define&t;RDBFF_NORESELECT 0x08L&t;/*   when talking to this drive */
DECL|macro|RDBFB_DISKID
mdefine_line|#define&t;RDBFB_DISKID&t;4&t;/* rdb_Disk... identification valid */
DECL|macro|RDBFF_DISKID
mdefine_line|#define&t;RDBFF_DISKID&t;0x10L
DECL|macro|RDBFB_CTRLRID
mdefine_line|#define&t;RDBFB_CTRLRID&t;5&t;/* rdb_Controller... identification valid */
DECL|macro|RDBFF_CTRLRID
mdefine_line|#define&t;RDBFF_CTRLRID&t;0x20L
multiline_comment|/* added 7/20/89 by commodore: */
DECL|macro|RDBFB_SYNCH
mdefine_line|#define RDBFB_SYNCH&t;6&t;/* drive supports scsi synchronous mode */
DECL|macro|RDBFF_SYNCH
mdefine_line|#define RDBFF_SYNCH&t;0x40L&t;/* CAN BE DANGEROUS TO USE IF IT DOESN&squot;T! */
DECL|struct|PartitionBlock
r_struct
id|PartitionBlock
(brace
DECL|member|pb_ID
id|ULONG
id|pb_ID
suffix:semicolon
multiline_comment|/* 4 character identifier */
DECL|member|pb_SummedLongs
id|ULONG
id|pb_SummedLongs
suffix:semicolon
multiline_comment|/* size of this checksummed structure */
DECL|member|pb_ChkSum
id|LONG
id|pb_ChkSum
suffix:semicolon
multiline_comment|/* block checksum (longword sum to zero) */
DECL|member|pb_HostID
id|ULONG
id|pb_HostID
suffix:semicolon
multiline_comment|/* SCSI Target ID of host */
DECL|member|pb_Next
id|ULONG
id|pb_Next
suffix:semicolon
multiline_comment|/* block number of the next PartitionBlock */
DECL|member|pb_Flags
id|ULONG
id|pb_Flags
suffix:semicolon
multiline_comment|/* see below for defines */
DECL|member|pb_Reserved1
id|ULONG
id|pb_Reserved1
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|pb_DevFlags
id|ULONG
id|pb_DevFlags
suffix:semicolon
multiline_comment|/* preferred flags for OpenDevice */
DECL|member|pb_DriveName
id|UBYTE
id|pb_DriveName
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* preferred DOS device name: BSTR form */
multiline_comment|/* (not used if this name is in use) */
DECL|member|pb_Reserved2
id|ULONG
id|pb_Reserved2
(braket
l_int|15
)braket
suffix:semicolon
multiline_comment|/* filler to 32 longwords */
DECL|member|pb_Environment
id|ULONG
id|pb_Environment
(braket
l_int|17
)braket
suffix:semicolon
multiline_comment|/* environment vector for this partition */
DECL|member|pb_EReserved
id|ULONG
id|pb_EReserved
(braket
l_int|15
)braket
suffix:semicolon
multiline_comment|/* reserved for future environment vector */
)brace
suffix:semicolon
DECL|macro|IDNAME_PARTITION
mdefine_line|#define&t;IDNAME_PARTITION&t;0x50415254&t;/* &squot;PART&squot; */
DECL|macro|PBFB_BOOTABLE
mdefine_line|#define&t;PBFB_BOOTABLE&t;0&t;/* this partition is intended to be bootable */
DECL|macro|PBFF_BOOTABLE
mdefine_line|#define&t;PBFF_BOOTABLE&t;1L&t;/*   (expected directories and files exist) */
DECL|macro|PBFB_NOMOUNT
mdefine_line|#define&t;PBFB_NOMOUNT&t;1&t;/* do not mount this partition (e.g. manually */
DECL|macro|PBFF_NOMOUNT
mdefine_line|#define&t;PBFF_NOMOUNT&t;2L&t;/*   mounted, but space reserved here) */
multiline_comment|/* this is from &lt;dos/filehandler.h&gt; */
DECL|macro|DE_TABLESIZE
mdefine_line|#define DE_TABLESIZE&t;0&t;/* minimum value is 11 (includes NumBuffers) */
DECL|macro|DE_SIZEBLOCK
mdefine_line|#define DE_SIZEBLOCK&t;1&t;/* in longwords: standard value is 128 */
DECL|macro|DE_SECORG
mdefine_line|#define DE_SECORG&t;2&t;/* not used; must be 0 */
DECL|macro|DE_NUMHEADS
mdefine_line|#define DE_NUMHEADS&t;3&t;/* # of heads (surfaces). drive specific */
DECL|macro|DE_SECSPERBLK
mdefine_line|#define DE_SECSPERBLK&t;4&t;/* not used; must be 1 */
DECL|macro|DE_BLKSPERTRACK
mdefine_line|#define DE_BLKSPERTRACK 5&t;/* blocks per track. drive specific */
DECL|macro|DE_RESERVEDBLKS
mdefine_line|#define DE_RESERVEDBLKS 6&t;/* unavailable blocks at start.&t; usually 2 */
DECL|macro|DE_PREFAC
mdefine_line|#define DE_PREFAC&t;7&t;/* not used; must be 0 */
DECL|macro|DE_INTERLEAVE
mdefine_line|#define DE_INTERLEAVE&t;8&t;/* usually 0 */
DECL|macro|DE_LOWCYL
mdefine_line|#define DE_LOWCYL&t;9&t;/* starting cylinder. typically 0 */
DECL|macro|DE_UPPERCYL
mdefine_line|#define DE_UPPERCYL&t;10&t;/* max cylinder.  drive specific */
DECL|macro|DE_NUMBUFFERS
mdefine_line|#define DE_NUMBUFFERS&t;11&t;/* starting # of buffers.  typically 5 */
DECL|macro|DE_MEMBUFTYPE
mdefine_line|#define DE_MEMBUFTYPE&t;12&t;/* type of mem to allocate for buffers. */
DECL|macro|DE_BUFMEMTYPE
mdefine_line|#define DE_BUFMEMTYPE&t;12&t;/* same as above, better name&n;&t;&t;&t;&t; * 1 is public, 3 is chip, 5 is fast */
DECL|macro|DE_MAXTRANSFER
mdefine_line|#define DE_MAXTRANSFER&t;13&t;/* Max number bytes to transfer at a time */
DECL|macro|DE_MASK
mdefine_line|#define DE_MASK&t;&t;14&t;/* Address Mask to block out certain memory */
DECL|macro|DE_BOOTPRI
mdefine_line|#define DE_BOOTPRI&t;15&t;/* Boot priority for autoboot */
DECL|macro|DE_DOSTYPE
mdefine_line|#define DE_DOSTYPE&t;16&t;/* ASCII (HEX) string showing filesystem type;&n;&t;&t;&t;&t; * 0X444F5300 is old filesystem,&n;&t;&t;&t;&t; * 0X444F5301 is fast file system */
DECL|macro|DE_BAUD
mdefine_line|#define DE_BAUD&t;&t;17&t;/* Baud rate for serial handler */
DECL|macro|DE_CONTROL
mdefine_line|#define DE_CONTROL&t;18&t;/* Control word for handler/filesystem */
DECL|macro|DE_BOOTBLOCKS
mdefine_line|#define DE_BOOTBLOCKS&t;19&t;/* Number of blocks containing boot code */
macro_line|#endif /* _LINUX_AMIGARDB_H */
eof
