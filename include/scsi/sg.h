multiline_comment|/*&n;   History:&n;    Started: Aug 9 by Lawrence Foard (entropy@world.std.com), to allow user &n;     process control of SCSI devices.&n;    Development Sponsored by Killy Corp. NY NY&n;*/
macro_line|#ifndef _SCSI_GENERIC_H
DECL|macro|_SCSI_GENERIC_H
mdefine_line|#define _SCSI_GENERIC_H
multiline_comment|/* &n; An SG device is accessed by writing &quot;packets&quot; to it, the replies&n; are then read using the read call. The same header is used for &n; reply, just ignore reply_len field.&n;*/
DECL|struct|sg_header
r_struct
id|sg_header
(brace
DECL|member|pack_len
r_int
id|pack_len
suffix:semicolon
multiline_comment|/* length of incoming packet &lt;4096 (including header) */
DECL|member|reply_len
r_int
id|reply_len
suffix:semicolon
multiline_comment|/* maximum length &lt;4096 of expected reply */
DECL|member|pack_id
r_int
id|pack_id
suffix:semicolon
multiline_comment|/* id number of packet */
DECL|member|result
r_int
id|result
suffix:semicolon
multiline_comment|/* 0==ok, otherwise refer to errno codes */
DECL|member|twelve_byte
r_int
r_int
id|twelve_byte
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Force 12 byte command length for group 6 &amp; 7 commands  */
DECL|member|other_flags
r_int
r_int
id|other_flags
suffix:colon
l_int|31
suffix:semicolon
multiline_comment|/* for future use */
DECL|member|sense_buffer
r_int
r_char
id|sense_buffer
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* used only by reads */
multiline_comment|/* command follows then data for command */
)brace
suffix:semicolon
multiline_comment|/* ioctl&squot;s */
DECL|macro|SG_SET_TIMEOUT
mdefine_line|#define SG_SET_TIMEOUT 0x2201  /* set timeout *(int *)arg==timeout */
DECL|macro|SG_GET_TIMEOUT
mdefine_line|#define SG_GET_TIMEOUT 0x2202  /* get timeout return timeout */
DECL|macro|SG_DEFAULT_TIMEOUT
mdefine_line|#define SG_DEFAULT_TIMEOUT (60*HZ) /* 1 minute timeout */
DECL|macro|SG_DEFAULT_RETRIES
mdefine_line|#define SG_DEFAULT_RETRIES 1
DECL|macro|SG_MAX_QUEUE
mdefine_line|#define SG_MAX_QUEUE 4 /* maximum outstanding request, arbitrary, may be&n;&t;&t;&t;  changed if sufficient DMA buffer room available */
DECL|macro|SG_BIG_BUFF
mdefine_line|#define SG_BIG_BUFF 32768
macro_line|#endif
eof