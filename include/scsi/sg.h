macro_line|#ifndef _SCSI_GENERIC_H
DECL|macro|_SCSI_GENERIC_H
mdefine_line|#define _SCSI_GENERIC_H
multiline_comment|/*&n;   History:&n;    Started: Aug 9 by Lawrence Foard (entropy@world.std.com), to allow user &n;     process control of SCSI devices. &n;    Development Sponsored by Killy Corp. NY NY&n;Original driver (sg.h):&n;*       Copyright (C) 1992 Lawrence Foard&n;2.x extensions to driver:&n;*       Copyright (C) 1998, 1999 Douglas Gilbert&n;&n;&n;    Version: 2.1.32 (990501)&n;    This version for later 2.1.x series and 2.2.x kernels&n;    D. P. Gilbert (dgilbert@interlog.com, dougg@triode.net.au)&n;&n;    Changes since 2.1.31 (990327)&n;        - add ioctls SG_GET_UNDERRUN_FLAG and _SET_. Change the default&n;          to _not_ flag underruns (affects aic7xxx driver)&n;        - clean up logging of pointers to use %p (for 64 bit architectures)&n;        - rework usage of get_user/copy_to_user family of kernel calls&n;        - &quot;disown&quot; scsi_command blocks before releasing them&n;    Changes since 2.1.30 (990320)&n;        - memory tweaks: change flags on kmalloc (GFP_KERNEL to GFP_ATOMIC)&n;        -                increase max allowable mid-level pool usage&n;    Changes since 2.1.21 (990315)&n;        - skipped to 2.1.30 indicating interface change (revert to 2.1.9)&n;        - remove attempt to accomodate cdrecord 1.8, will fix app&n;        - keep SG_?ET_RESERVED_SIZE naming for clarity&n;    Changes since 2.1.20 (990313)&n;        - ommission: left out logic for SG_?ET_ALT_INTERFACE, now added&n;    Changes since 2.1.9 (990309)&n;        - skipped to version 2.1.20 to indicate some interface changes&n;        - incorporate sg changes to make cdrecord 1.8 work (had its&n;          own patches that were different from the original)&n;        - change SG_?ET_BUFF_SIZE to SG_?ET_RESERVED_SIZE for clarity&n;    Changes since 2.1.8 (990303)&n;        - debug &quot;&gt;9&quot; option dumps debug for _all_ active sg devices&n;        - increase allowable dma pool usage + increase minimum threshhold&n;        - pad out sg_scsi_id structure&n;    Changes since 2.1.7 (990227)&n;        - command queuing now &quot;non-default&quot; [back. compat. with cdparanoia]&n;        - Tighten access on some ioctls&n;&n;&n;    New features and changes:&n;        - per file descriptor (fd) write-read sequencing and command queues.&n;        - command queuing supported (SG_MAX_QUEUE is maximum per fd).&n;        - scatter-gather supported (allowing potentially megabyte transfers).&n;        - the SCSI target, host and driver status are returned&n;          in unused fields of sg_header (maintaining its original size).&n;        - asynchronous notification support added (SIGPOLL, SIGIO) for&n;          read()s ( write()s should never block).&n;        - pack_id logic added so read() can be made to wait for a specific&n;          pack_id. &n;        - uses memory &gt; ISA_DMA_THRESHOLD if adapter allows it (e.g. a&n;          pci scsi adapter).&n;        - this driver no longer uses a single SG_BIG_BUFF sized buffer&n;          obtained at driver/module init time. Rather it obtains a &n;          SG_SCATTER_SZ buffer when a fd is open()ed and frees it at&n;          the corresponding release() (ie pr fd). Hence open() can return&n;          ENOMEM! If write() request &gt; SG_SCATTER_SZ bytes for data then&n;          it can fail with ENOMEM as well (if so, scale back).&n;        - adds several ioctl calls, see ioctl section below.&n;        - SG_SCATTER_SZ&squot;s presence indicates this version of &quot;sg&quot; driver.&n; &n; Good documentation on the original &quot;sg&quot; device interface and usage can be&n; found in the Linux HOWTO document: &quot;SCSI Programming HOWTO&quot; by Heiko&n; Eissfeldt; last updated 7 May 1996. I will add more info on using the&n; extensions in this driver as required. A quick summary:&n; An SG device is accessed by writing SCSI commands plus any associated &n; outgoing data to it; the resulting status codes and any incoming data&n; are then obtained by a read call. The device can be opened O_NONBLOCK&n; (non-blocking) and poll() used to monitor its progress. The device may be&n; opened O_EXCL which excludes other &quot;sg&quot; users from this device (but not &n; &quot;sd&quot;, &quot;st&quot; or &quot;sr&quot; users). The buffer given to the write() call is made&n; up as follows:&n;        - struct sg_header image (see below)&n;        - scsi command (6, 10 or 12 bytes long)&n;        - data to be written to the device (if any)&n;&n; The buffer received from the corresponding read() call contains:&n;        - struct sg_header image (check results + sense_buffer)&n;        - data read back from device (if any)&n;&n; The given SCSI command has its LUN field overwritten internally by the&n; value associated with the device that has been opened.&n;&n; Memory (RAM) is used within this driver for direct memory access (DMA)&n; in transferring data to and from the SCSI device. The dreaded ENOMEM&n; seems to be more prevalent under early 2.2.x kernels than under the&n; 2.0.x kernel series. For a given (large) transfer the memory obtained by&n; this driver must be contiguous or scatter-gather must be used (if&n; supported by the adapter). [Furthermore, ISA SCSI adapters can only use&n; memory below the 16MB level on a i386.]&n; This driver tries hard to find some suitable memory before admitting&n; defeat and returning ENOMEM. All is not lost if application writers&n; then back off the amount they are requesting. The value returned by&n; the SG_GET_RESERVED_SIZE ioctl is guaranteed to be available (one&n; per fd). This driver does the following:&n;   -  attempts to reserve a SG_SCATTER_SZ sized buffer on open(). The&n;      actual amount reserved is given by the SG_GET_RESERVED_SIZE ioctl().&n;   -  each write() needs to reserve a DMA buffer of the size of the&n;      data buffer indicated (excluding sg_header and command overhead).&n;      This buffer, depending on its size, adapter type (ISA or not) and&n;      the amount of memory available will be obtained from the kernel&n;      directly (get_free_pages or kmalloc) or the from the scsi mid-level&n;      dma pool (taking care not to exhaust it).&n;      If the buffer requested is &gt; SG_SCATTER_SZ or memory is tight then&n;      scatter-gather will be used if supported by the adapter.&n;  -   write() will also attempt to use the buffer reserved on open()&n;      if it is large enough.&n; The above strategy ensures that a write() can always depend on a buffer &n; of the size indicated by the SG_GET_RESERVED_SIZE ioctl() (which could be&n; 0, but at least the app knows things are tight in advance).&n; Hence application writers can adopt quite aggressive strategies (e.g. &n; requesting 512KB) and scale them back in the face of ENOMEM errors.&n; N.B. Queuing up commands also ties up kernel memory.&n;&n; More documentation can be found at www.torque.net/sg&n;*/
DECL|macro|SG_MAX_SENSE
mdefine_line|#define SG_MAX_SENSE 16   /* too little, unlikely to change in 2.2.x */
DECL|struct|sg_header
r_struct
id|sg_header
(brace
DECL|member|pack_len
r_int
id|pack_len
suffix:semicolon
multiline_comment|/* [o] reply_len (ie useless), ignored as input */
DECL|member|reply_len
r_int
id|reply_len
suffix:semicolon
multiline_comment|/* [i] max length of expected reply (inc. sg_header) */
DECL|member|pack_id
r_int
id|pack_id
suffix:semicolon
multiline_comment|/* [io] id number of packet (use ints &gt;= 0) */
DECL|member|result
r_int
id|result
suffix:semicolon
multiline_comment|/* [o] 0==ok, else (+ve) Unix errno code (e.g. EIO) */
DECL|member|twelve_byte
r_int
r_int
id|twelve_byte
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* [i] Force 12 byte command length for group 6 &amp; 7 commands  */
DECL|member|target_status
r_int
r_int
id|target_status
suffix:colon
l_int|5
suffix:semicolon
multiline_comment|/* [o] scsi status from target */
DECL|member|host_status
r_int
r_int
id|host_status
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* [o] host status (see &quot;DID&quot; codes) */
DECL|member|driver_status
r_int
r_int
id|driver_status
suffix:colon
l_int|8
suffix:semicolon
multiline_comment|/* [o] driver status+suggestion */
DECL|member|other_flags
r_int
r_int
id|other_flags
suffix:colon
l_int|10
suffix:semicolon
multiline_comment|/* unused */
DECL|member|sense_buffer
r_int
r_char
id|sense_buffer
(braket
id|SG_MAX_SENSE
)braket
suffix:semicolon
multiline_comment|/* [o] Output in 3 cases:&n;           when target_status is CHECK_CONDITION or &n;           when target_status is COMMAND_TERMINATED or&n;           when (driver_status &amp; DRIVER_SENSE) is true. */
)brace
suffix:semicolon
multiline_comment|/* This structure is 36 bytes long on i386 */
DECL|struct|sg_scsi_id
r_typedef
r_struct
id|sg_scsi_id
(brace
DECL|member|host_no
r_int
id|host_no
suffix:semicolon
multiline_comment|/* as in &quot;scsi&lt;n&gt;&quot; where &squot;n&squot; is one of 0, 1, 2 etc */
DECL|member|channel
r_int
id|channel
suffix:semicolon
DECL|member|scsi_id
r_int
id|scsi_id
suffix:semicolon
multiline_comment|/* scsi id of target device */
DECL|member|lun
r_int
id|lun
suffix:semicolon
DECL|member|scsi_type
r_int
id|scsi_type
suffix:semicolon
multiline_comment|/* TYPE_... defined in scsi/scsi.h */
DECL|member|unused1
r_int
id|unused1
suffix:semicolon
multiline_comment|/* probably find a good use, set 0 for now */
DECL|member|unused2
r_int
id|unused2
suffix:semicolon
multiline_comment|/* ditto */
DECL|member|unused3
r_int
id|unused3
suffix:semicolon
DECL|typedef|Sg_scsi_id
)brace
id|Sg_scsi_id
suffix:semicolon
multiline_comment|/* ioctls  ( _GET_s yield result via &squot;int *&squot; 3rd argument unless &n;            otherwise indicated */
DECL|macro|SG_SET_TIMEOUT
mdefine_line|#define SG_SET_TIMEOUT 0x2201  /* unit: jiffies, 10ms on i386 */
DECL|macro|SG_GET_TIMEOUT
mdefine_line|#define SG_GET_TIMEOUT 0x2202  /* yield timeout as _return_ value */
DECL|macro|SG_EMULATED_HOST
mdefine_line|#define SG_EMULATED_HOST 0x2203 /* true for emulated host adapter (ATAPI) */
multiline_comment|/* Used to configure SCSI command transformation layer for ATAPI devices */
DECL|macro|SG_SET_TRANSFORM
mdefine_line|#define SG_SET_TRANSFORM 0x2204
DECL|macro|SG_GET_TRANSFORM
mdefine_line|#define SG_GET_TRANSFORM 0x2205
DECL|macro|SG_SET_RESERVED_SIZE
mdefine_line|#define SG_SET_RESERVED_SIZE 0x2275  /* currently ignored, future addition */
multiline_comment|/* Following yields buffer reserved by open(): 0 &lt;= x &lt;= SG_SCATTER_SZ */
DECL|macro|SG_GET_RESERVED_SIZE
mdefine_line|#define SG_GET_RESERVED_SIZE 0x2272
multiline_comment|/* The following ioctl takes a &squot;Sg_scsi_id *&squot; object as its 3rd argument. */
DECL|macro|SG_GET_SCSI_ID
mdefine_line|#define SG_GET_SCSI_ID 0x2276   /* Yields fd&squot;s bus,chan,dev,lun+type */
multiline_comment|/* SCSI id information can also be obtained from SCSI_IOCTL_GET_IDLUN */
multiline_comment|/* Override adapter setting and always DMA using low memory ( &lt;16MB on i386).&n;   Default is 0 (off - use adapter setting) */
DECL|macro|SG_SET_FORCE_LOW_DMA
mdefine_line|#define SG_SET_FORCE_LOW_DMA 0x2279  /* 0-&gt; use adapter setting, 1-&gt; force */
DECL|macro|SG_GET_LOW_DMA
mdefine_line|#define SG_GET_LOW_DMA 0x227a   /* 0-&gt; use all ram for dma; 1-&gt; low dma ram */
multiline_comment|/* When SG_SET_FORCE_PACK_ID set to 1, pack_id is input to read() which&n;   will attempt to read that pack_id or block (or return EAGAIN). If &n;   pack_id is -1 then read oldest waiting. When ...FORCE_PACK_ID set to 0&n;   (default) then pack_id ignored by read() and oldest readable fetched. */
DECL|macro|SG_SET_FORCE_PACK_ID
mdefine_line|#define SG_SET_FORCE_PACK_ID 0x227b
DECL|macro|SG_GET_PACK_ID
mdefine_line|#define SG_GET_PACK_ID 0x227c /* Yields oldest readable pack_id (or -1) */
DECL|macro|SG_GET_NUM_WAITING
mdefine_line|#define SG_GET_NUM_WAITING 0x227d /* Number of commands awaiting read() */
multiline_comment|/* Turn on error sense trace (1..8), dump this device to log/console (9)&n;   or dump all sg device states ( &gt;9 ) to log/console */
DECL|macro|SG_SET_DEBUG
mdefine_line|#define SG_SET_DEBUG 0x227e    /* 0 -&gt; turn off debug */
multiline_comment|/* Yields max scatter gather tablesize allowed by current host adapter */
DECL|macro|SG_GET_SG_TABLESIZE
mdefine_line|#define SG_GET_SG_TABLESIZE 0x227F  /* 0 implies can&squot;t do scatter gather */
multiline_comment|/* Control whether sequencing per file descriptor (default) or per device */
DECL|macro|SG_GET_MERGE_FD
mdefine_line|#define SG_GET_MERGE_FD 0x2274   /* 0-&gt; per fd (default), 1-&gt; per device */
DECL|macro|SG_SET_MERGE_FD
mdefine_line|#define SG_SET_MERGE_FD 0x2273   /* Attempt to change sequencing state,&n;  if more than 1 fd open on device, will fail with EBUSY */
multiline_comment|/* Get/set command queuing state per fd (default is SG_DEF_COMMAND_Q) */
DECL|macro|SG_GET_COMMAND_Q
mdefine_line|#define SG_GET_COMMAND_Q 0x2270   /* Yields 0 (queuing off) or 1 (on) */
DECL|macro|SG_SET_COMMAND_Q
mdefine_line|#define SG_SET_COMMAND_Q 0x2271   /* Change queuing state with 0 or 1 */
multiline_comment|/* Get/set whether DMA underrun will cause an error (DID_ERROR) [this only&n;   currently applies to the [much-used] aic7xxx driver) */
DECL|macro|SG_GET_UNDERRUN_FLAG
mdefine_line|#define SG_GET_UNDERRUN_FLAG 0x2280 /* Yields 0 (don&squot;t flag) or 1 (flag) */
DECL|macro|SG_SET_UNDERRUN_FLAG
mdefine_line|#define SG_SET_UNDERRUN_FLAG 0x2281 /* Change flag underrun state */
DECL|macro|SG_DEFAULT_TIMEOUT
mdefine_line|#define SG_DEFAULT_TIMEOUT (60*HZ) /* HZ == &squot;jiffies in 1 second&squot; */
DECL|macro|SG_DEFAULT_RETRIES
mdefine_line|#define SG_DEFAULT_RETRIES 1
multiline_comment|/* Default modes, commented if they differ from original sg driver */
DECL|macro|SG_DEF_COMMAND_Q
mdefine_line|#define SG_DEF_COMMAND_Q 0
DECL|macro|SG_DEF_MERGE_FD
mdefine_line|#define SG_DEF_MERGE_FD 0       /* was 1 -&gt; per device sequencing */
DECL|macro|SG_DEF_FORCE_LOW_DMA
mdefine_line|#define SG_DEF_FORCE_LOW_DMA 0  /* was 1 -&gt; memory below 16MB on i386 */
DECL|macro|SG_DEF_FORCE_PACK_ID
mdefine_line|#define SG_DEF_FORCE_PACK_ID 0
DECL|macro|SG_DEF_UNDERRUN_FLAG
mdefine_line|#define SG_DEF_UNDERRUN_FLAG 0
multiline_comment|/* maximum outstanding requests, write() yields EDOM if exceeded */
DECL|macro|SG_MAX_QUEUE
mdefine_line|#define SG_MAX_QUEUE 16
DECL|macro|SG_SCATTER_SZ
mdefine_line|#define SG_SCATTER_SZ (8 * 4096)  /* PAGE_SIZE not available to user */
multiline_comment|/* Largest size (in bytes) a single scatter-gather list element can have.&n;   The value must be a power of 2 and &lt;= (PAGE_SIZE * 32) [131072 bytes on &n;   i386]. The minimum value is PAGE_SIZE. If scatter-gather not supported&n;   by adapter then this value is the largest data block that can be&n;   read/written by a single scsi command. Max number of scatter-gather&n;   list elements seems to be limited to 255. */
DECL|macro|SG_BIG_BUFF
mdefine_line|#define SG_BIG_BUFF SG_SCATTER_SZ       /* for backward compatibility */
multiline_comment|/* #define SG_BIG_BUFF (SG_SCATTER_SZ * 8) */
multiline_comment|/* =256KB, if you want */
macro_line|#endif
eof
