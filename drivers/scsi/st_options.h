multiline_comment|/*&n;   The compile-time configurable defaults for the Linux SCSI tape driver.&n;&n;   Copyright 1995 Kai Makisara.&n;&n;   Last modified: Mon Sep 18 21:00:49 1995 by root@kai.makisara.fi&n;*/
macro_line|#ifndef _ST_OPTIONS_H
DECL|macro|_ST_OPTIONS_H
mdefine_line|#define _ST_OPTIONS_H
multiline_comment|/* The driver allocates the tape buffers when needed if ST_RUNTIME_BUFFERS&n;   is nonzero. Otherwise a number of buffers are allocated at initialization.&n;   The drawback of runtime allocation is that allocation may fail. In any&n;   case the driver tries to allocate a new tape buffer when none is free. */
DECL|macro|ST_RUNTIME_BUFFERS
mdefine_line|#define ST_RUNTIME_BUFFERS 0
multiline_comment|/* The driver does not wait for some operations to finish before returning&n;   to the user program if ST_NOWAIT is non-zero. This helps if the SCSI&n;   adapter does not support multiple outstanding commands. However, the user&n;   should not give a new tape command before the previous one has finished. */
DECL|macro|ST_NOWAIT
mdefine_line|#define ST_NOWAIT 0
multiline_comment|/* If ST_IN_FILE_POS is nonzero, the driver positions the tape after the&n;   record been read by the user program even if the tape has moved further&n;   because of buffered reads. Should be set to zero to support also drives&n;   that can&squot;t space backwards over records. NOTE: The tape will be&n;   spaced backwards over an &quot;accidentally&quot; crossed filemark in any case. */
DECL|macro|ST_IN_FILE_POS
mdefine_line|#define ST_IN_FILE_POS 0
multiline_comment|/* If ST_RECOVERED_WRITE_FATAL is non-zero, recovered errors while writing&n;   are considered &quot;hard errors&quot;. */
DECL|macro|ST_RECOVERED_WRITE_FATAL
mdefine_line|#define ST_RECOVERED_WRITE_FATAL 0
multiline_comment|/* The &quot;guess&quot; for the block size for devices that don&squot;t support MODE&n;   SENSE. */
DECL|macro|ST_DEFAULT_BLOCK
mdefine_line|#define ST_DEFAULT_BLOCK 0
multiline_comment|/* The tape driver buffer size in kilobytes. */
DECL|macro|ST_BUFFER_BLOCKS
mdefine_line|#define ST_BUFFER_BLOCKS 32
multiline_comment|/* The number of kilobytes of data in the buffer that triggers an&n;   asynchronous write in fixed block mode. See also ST_ASYNC_WRITES&n;   below. */
DECL|macro|ST_WRITE_THRESHOLD_BLOCKS
mdefine_line|#define ST_WRITE_THRESHOLD_BLOCKS 30
multiline_comment|/* The maximum number of tape buffers the driver allocates. The number&n;   is also constrained by the number of drives detected. Determines the&n;   maximum number of concurrently active tape drives. */
DECL|macro|ST_MAX_BUFFERS
mdefine_line|#define ST_MAX_BUFFERS (2 + ST_EXTRA_DEVS)
multiline_comment|/* The following lines define defaults for properties that can be set&n;   separately for each drive using the MTSTOPTIONS ioctl. */
multiline_comment|/* If ST_TWO_FM is non-zero, the driver writes two filemarks after a&n;   file being written. Some drives can&squot;t handle two filemarks at the&n;   end of data. */
DECL|macro|ST_TWO_FM
mdefine_line|#define ST_TWO_FM 0
multiline_comment|/* If ST_BUFFER_WRITES is non-zero, writes in fixed block mode are&n;   buffered until the driver buffer is full or asynchronous write is&n;   triggered. May make detection of End-Of-Medium early enough fail. */
DECL|macro|ST_BUFFER_WRITES
mdefine_line|#define ST_BUFFER_WRITES 1
multiline_comment|/* If ST_ASYNC_WRITES is non-zero, the SCSI write command may be started&n;   without waiting for it to finish. May cause problems in multiple&n;   tape backups. */
DECL|macro|ST_ASYNC_WRITES
mdefine_line|#define ST_ASYNC_WRITES 1
multiline_comment|/* If ST_READ_AHEAD is non-zero, blocks are read ahead in fixed block&n;   mode. */
DECL|macro|ST_READ_AHEAD
mdefine_line|#define ST_READ_AHEAD 1
multiline_comment|/* If ST_AUTO_LOCK is non-zero, the drive door is locked at the first&n;   read or write command after the device is opened. The door is opened&n;   when the device is closed. */
DECL|macro|ST_AUTO_LOCK
mdefine_line|#define ST_AUTO_LOCK 0
multiline_comment|/* If ST_FAST_MTEOM is non-zero, the MTEOM ioctl is done using the&n;   direct SCSI command. The file number status is lost but this method&n;   is fast with some drives. Otherwise MTEOM is done by spacing over&n;   files and the file number status is retained. */
DECL|macro|ST_FAST_MTEOM
mdefine_line|#define ST_FAST_MTEOM 0
macro_line|#endif
eof
