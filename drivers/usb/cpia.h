macro_line|#ifndef __LINUX_CPIA_H
DECL|macro|__LINUX_CPIA_H
mdefine_line|#define __LINUX_CPIA_H
macro_line|#include &lt;linux/list.h&gt;
DECL|macro|USB_REQ_CPIA_GET_VERSION
mdefine_line|#define USB_REQ_CPIA_GET_VERSION&t;&t;0x01
DECL|macro|USB_REQ_CPIA_GET_PNP_ID
mdefine_line|#define USB_REQ_CPIA_GET_PNP_ID&t;&t;&t;0x02
DECL|macro|USB_REQ_CPIA_GET_CAMERA_STATUS
mdefine_line|#define USB_REQ_CPIA_GET_CAMERA_STATUS&t;&t;0x03
DECL|macro|USB_REQ_CPIA_GOTO_HI_POWER
mdefine_line|#define USB_REQ_CPIA_GOTO_HI_POWER&t;&t;0x04
DECL|macro|USB_REQ_CPIA_GOTO_LO_POWER
mdefine_line|#define USB_REQ_CPIA_GOTO_LO_POWER&t;&t;0x05
multiline_comment|/* No 0x06 */
DECL|macro|USB_REQ_CPIA_GOTO_SUSPEND
mdefine_line|#define USB_REQ_CPIA_GOTO_SUSPEND&t;&t;0x07
DECL|macro|USB_REQ_CPIA_GOTO_PASS_THROUGH
mdefine_line|#define USB_REQ_CPIA_GOTO_PASS_THROUGH&t;&t;0x08
multiline_comment|/* No 0x09 */
DECL|macro|USB_REQ_CPIA_MODIFY_CAMERA_STATUS
mdefine_line|#define USB_REQ_CPIA_MODIFY_CAMERA_STATUS&t;0x0A
DECL|macro|USB_REQ_CPIA_READ_VC_REGS
mdefine_line|#define USB_REQ_CPIA_READ_VC_REGS&t;&t;0x21
DECL|macro|USB_REQ_CPIA_WRITE_BC_REG
mdefine_line|#define USB_REQ_CPIA_WRITE_BC_REG&t;&t;0x22
DECL|macro|USB_REQ_CPIA_READ_MC_PORTS
mdefine_line|#define USB_REQ_CPIA_READ_MC_PORTS&t;&t;0x23
DECL|macro|USB_REQ_CPIA_WRITE_MC_PORT
mdefine_line|#define USB_REQ_CPIA_WRITE_MC_PORT&t;&t;0x24
DECL|macro|USB_REQ_CPIA_SET_BAUD_RATE
mdefine_line|#define USB_REQ_CPIA_SET_BAUD_RATE&t;&t;0x25
DECL|macro|USB_REQ_CPIA_SET_ECP_TIMING
mdefine_line|#define USB_REQ_CPIA_SET_ECP_TIMING&t;&t;0x26
DECL|macro|USB_REQ_CPIA_READ_IDATA
mdefine_line|#define USB_REQ_CPIA_READ_IDATA&t;&t;&t;0x27
DECL|macro|USB_REQ_CPIA_WRITE_IDATA
mdefine_line|#define USB_REQ_CPIA_WRITE_IDATA&t;&t;0x28
DECL|macro|USB_REQ_CPIA_GENERIC_CALL
mdefine_line|#define USB_REQ_CPIA_GENERIC_CALL&t;&t;0x29
DECL|macro|USB_REQ_CPIA_I2CSTART
mdefine_line|#define USB_REQ_CPIA_I2CSTART&t;&t;&t;0x2A
DECL|macro|USB_REQ_CPIA_I2CSTOP
mdefine_line|#define USB_REQ_CPIA_I2CSTOP&t;&t;&t;0x2B
DECL|macro|USB_REQ_CPIA_I2CWRITE
mdefine_line|#define USB_REQ_CPIA_I2CWRITE&t;&t;&t;0x2C
DECL|macro|USB_REQ_CPIA_I2CREAD
mdefine_line|#define USB_REQ_CPIA_I2CREAD&t;&t;&t;0x2D
DECL|macro|USB_REQ_CPIA_GET_VP_VERSION
mdefine_line|#define USB_REQ_CPIA_GET_VP_VERSION&t;&t;0xA1
DECL|macro|USB_REQ_CPIA_SET_COLOUR_PARAMS
mdefine_line|#define USB_REQ_CPIA_SET_COLOUR_PARAMS&t;&t;0xA3
DECL|macro|USB_REQ_CPIA_SET_EXPOSURE
mdefine_line|#define USB_REQ_CPIA_SET_EXPOSURE&t;&t;0xA4
multiline_comment|/* No 0xA5 */
DECL|macro|USB_REQ_CPIA_SET_COLOUR_BALANCE
mdefine_line|#define USB_REQ_CPIA_SET_COLOUR_BALANCE&t;&t;0xA6
DECL|macro|USB_REQ_CPIA_SET_SENSOR_FPS
mdefine_line|#define USB_REQ_CPIA_SET_SENSOR_FPS&t;&t;0xA7
DECL|macro|USB_REQ_CPIA_SET_VP_DEFAULTS
mdefine_line|#define USB_REQ_CPIA_SET_VP_DEFAULTS&t;&t;0xA8
DECL|macro|USB_REQ_CPIA_SET_APCOR
mdefine_line|#define USB_REQ_CPIA_SET_APCOR&t;&t;&t;0xA9
DECL|macro|USB_REQ_CPIA_SET_FLICKER_CTRL
mdefine_line|#define USB_REQ_CPIA_SET_FLICKER_CTRL&t;&t;0xAA
DECL|macro|USB_REQ_CPIA_SET_VL_OFFSET
mdefine_line|#define USB_REQ_CPIA_SET_VL_OFFSET&t;&t;0xAB
DECL|macro|USB_REQ_CPIA_GET_COLOUR_PARAMETERS
mdefine_line|#define USB_REQ_CPIA_GET_COLOUR_PARAMETERS&t;0xB0
DECL|macro|USB_REQ_CPIA_GET_COLOUR_BALANCE
mdefine_line|#define USB_REQ_CPIA_GET_COLOUR_BALANCE&t;&t;0xB1
DECL|macro|USB_REQ_CPIA_GET_EXPOSURE
mdefine_line|#define USB_REQ_CPIA_GET_EXPOSURE&t;&t;0xB2
DECL|macro|USB_REQ_CPIA_SET_SENSOR_MATRIX
mdefine_line|#define USB_REQ_CPIA_SET_SENSOR_MATRIX&t;&t;0xB3
DECL|macro|USB_REQ_CPIA_COLOUR_BARS
mdefine_line|#define USB_REQ_CPIA_COLOUR_BARS&t;&t;0xBD
DECL|macro|USB_REQ_CPIA_READ_VP_REGS
mdefine_line|#define USB_REQ_CPIA_READ_VP_REGS&t;&t;0xBE
DECL|macro|USB_REQ_CPIA_WRITE_VP_REGS
mdefine_line|#define USB_REQ_CPIA_WRITE_VP_REGS&t;&t;0xBF
DECL|macro|USB_REQ_CPIA_GRAB_FRAME
mdefine_line|#define USB_REQ_CPIA_GRAB_FRAME&t;&t;&t;0xC1
DECL|macro|USB_REQ_CPIA_UPLOAD_FRAME
mdefine_line|#define USB_REQ_CPIA_UPLOAD_FRAME&t;&t;0xC2
DECL|macro|WAIT_FOR_NEXT_FRAME
mdefine_line|#define  WAIT_FOR_NEXT_FRAME&t;&t;&t;0
DECL|macro|FORCE_FRAME_UPLOAD
mdefine_line|#define  FORCE_FRAME_UPLOAD&t;&t;&t;1
DECL|macro|USB_REQ_CPIA_SET_GRAB_MODE
mdefine_line|#define USB_REQ_CPIA_SET_GRAB_MODE&t;&t;0xC3
DECL|macro|USB_REQ_CPIA_INIT_STREAM_CAP
mdefine_line|#define USB_REQ_CPIA_INIT_STREAM_CAP&t;&t;0xC4
DECL|macro|USB_REQ_CPIA_FINI_STREAM_CAP
mdefine_line|#define USB_REQ_CPIA_FINI_STREAM_CAP&t;&t;0xC5
DECL|macro|USB_REQ_CPIA_START_STREAM_CAP
mdefine_line|#define USB_REQ_CPIA_START_STREAM_CAP&t;&t;0xC6
DECL|macro|USB_REQ_CPIA_END_STREAM_CAP
mdefine_line|#define USB_REQ_CPIA_END_STREAM_CAP&t;&t;0xC7
DECL|macro|USB_REQ_CPIA_SET_FORMAT
mdefine_line|#define USB_REQ_CPIA_SET_FORMAT&t;&t;&t;0xC8
DECL|macro|FORMAT_QCIF
mdefine_line|#define  FORMAT_QCIF&t;0
DECL|macro|FORMAT_CIF
mdefine_line|#define  FORMAT_CIF&t;1
DECL|macro|FORMAT_YUYV
mdefine_line|#define  FORMAT_YUYV&t;0
DECL|macro|FORMAT_UYVY
mdefine_line|#define  FORMAT_UYVY&t;1
DECL|macro|FORMAT_420
mdefine_line|#define  FORMAT_420&t;0
DECL|macro|FORMAT_422
mdefine_line|#define  FORMAT_422&t;1
DECL|macro|USB_REQ_CPIA_SET_ROI
mdefine_line|#define USB_REQ_CPIA_SET_ROI&t;&t;&t;0xC9
DECL|macro|USB_REQ_CPIA_SET_COMPRESSION
mdefine_line|#define USB_REQ_CPIA_SET_COMPRESSION&t;&t;0xCA
DECL|macro|COMP_DISABLED
mdefine_line|#define  COMP_DISABLED&t;0
DECL|macro|COMP_AUTO
mdefine_line|#define  COMP_AUTO&t;1
DECL|macro|COMP_MANUAL
mdefine_line|#define  COMP_MANUAL&t;2
DECL|macro|DONT_DECIMATE
mdefine_line|#define  DONT_DECIMATE&t;0
DECL|macro|DECIMATE
mdefine_line|#define  DECIMATE&t;1
DECL|macro|USB_REQ_CPIA_SET_COMPRESSION_TARGET
mdefine_line|#define USB_REQ_CPIA_SET_COMPRESSION_TARGET&t;0xCB
DECL|macro|TARGET_QUALITY
mdefine_line|#define  TARGET_QUALITY&t;&t;0
DECL|macro|TARGET_FRAMERATE
mdefine_line|#define  TARGET_FRAMERATE&t;1
DECL|macro|USB_REQ_CPIA_SET_YUV_THRESH
mdefine_line|#define USB_REQ_CPIA_SET_YUV_THRESH&t;&t;0xCC
DECL|macro|USB_REQ_CPIA_SET_COMPRESSION_PARAMS
mdefine_line|#define USB_REQ_CPIA_SET_COMPRESSION_PARAMS&t;0xCD
DECL|macro|USB_REQ_CPIA_DISCARD_FRAME
mdefine_line|#define USB_REQ_CPIA_DISCARD_FRAME&t;&t;0xCE
DECL|macro|USB_REQ_CPIA_OUTPUT_RS232
mdefine_line|#define USB_REQ_CPIA_OUTPUT_RS232&t;&t;0xE1
DECL|macro|USB_REQ_CPIA_ABORT_PROCESS
mdefine_line|#define USB_REQ_CPIA_ABORT_PROCESS&t;&t;0xE4
DECL|macro|USB_REQ_CPIA_SET_DRAM_PAGE
mdefine_line|#define USB_REQ_CPIA_SET_DRAM_PAGE&t;&t;0xE5
DECL|macro|USB_REQ_CPIA_START_DRAM_UPLOAD
mdefine_line|#define USB_REQ_CPIA_START_DRAM_UPLOAD&t;&t;0xE6
DECL|macro|USB_REQ_CPIA_START_DUMMY_STREAM
mdefine_line|#define USB_REQ_CPIA_START_DUMMY_STREAM&t;&t;0xE8
DECL|macro|USB_REQ_CPIA_ABORT_STREAM
mdefine_line|#define USB_REQ_CPIA_ABORT_STREAM&t;&t;0xE9
DECL|macro|USB_REQ_CPIA_DOWNLOAD_DRAM
mdefine_line|#define USB_REQ_CPIA_DOWNLOAD_DRAM&t;&t;0xEA
multiline_comment|/* #define USB_REQ_CPIA_NULL_CMD&t;&t;0x?? */
DECL|macro|STREAM_BUF_SIZE
mdefine_line|#define STREAM_BUF_SIZE&t;&t;(PAGE_SIZE * 4)
multiline_comment|/* #define STREAM_BUF_SIZE&t;(FRAMES_PER_DESC * FRAME_SIZE_PER_DESC) */
DECL|macro|SCRATCH_BUF_SIZE
mdefine_line|#define SCRATCH_BUF_SIZE&t;(STREAM_BUF_SIZE * 2)
DECL|macro|FRAMES_PER_DESC
mdefine_line|#define FRAMES_PER_DESC&t;&t;10
DECL|macro|FRAME_SIZE_PER_DESC
mdefine_line|#define FRAME_SIZE_PER_DESC&t;960&t;/* Shouldn&squot;t be hardcoded */
r_enum
(brace
DECL|enumerator|STATE_SCANNING
id|STATE_SCANNING
comma
multiline_comment|/* Scanning for start */
DECL|enumerator|STATE_HEADER
id|STATE_HEADER
comma
multiline_comment|/* Parsing header */
DECL|enumerator|STATE_LINES
id|STATE_LINES
comma
multiline_comment|/* Parsing lines */
)brace
suffix:semicolon
DECL|macro|CPIA_MAGIC
mdefine_line|#define CPIA_MAGIC&t;0x1968
DECL|struct|cpia_frame_header
r_struct
id|cpia_frame_header
(brace
DECL|member|magic
id|__u16
id|magic
suffix:semicolon
multiline_comment|/* 0 - 1 */
DECL|member|timestamp
id|__u16
id|timestamp
suffix:semicolon
multiline_comment|/* 2 - 3 */
DECL|member|unused
id|__u16
id|unused
suffix:semicolon
multiline_comment|/* 4 - 5 */
DECL|member|timestamp1
id|__u16
id|timestamp1
suffix:semicolon
multiline_comment|/* 6 - 7 */
DECL|member|unused1
id|__u8
id|unused1
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 8 - 15 */
DECL|member|video_size
id|__u8
id|video_size
suffix:semicolon
multiline_comment|/* 16 0 = QCIF, 1 = CIF */
DECL|member|sub_sample
id|__u8
id|sub_sample
suffix:semicolon
multiline_comment|/* 17 0 = 4:2:0, 1 = 4:2:2 */
DECL|member|yuv_order
id|__u8
id|yuv_order
suffix:semicolon
multiline_comment|/* 18 0 = YUYV, 1 = UYVY */
DECL|member|unused2
id|__u8
id|unused2
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* 19 - 23 */
DECL|member|col_start
id|__u8
id|col_start
suffix:semicolon
multiline_comment|/* 24 */
DECL|member|col_end
id|__u8
id|col_end
suffix:semicolon
multiline_comment|/* 25 */
DECL|member|row_start
id|__u8
id|row_start
suffix:semicolon
multiline_comment|/* 26 */
DECL|member|row_end
id|__u8
id|row_end
suffix:semicolon
multiline_comment|/* 27 */
DECL|member|comp_enable
id|__u8
id|comp_enable
suffix:semicolon
multiline_comment|/* 28 0 = non compressed, 1 = compressed */
DECL|member|decimation
id|__u8
id|decimation
suffix:semicolon
multiline_comment|/* 29 0 = no decimation, 1 = decimation */
DECL|member|y_thresh
id|__u8
id|y_thresh
suffix:semicolon
multiline_comment|/* 30 */
DECL|member|uv_thresh
id|__u8
id|uv_thresh
suffix:semicolon
multiline_comment|/* 31 */
DECL|member|system_state
id|__u8
id|system_state
suffix:semicolon
multiline_comment|/* 32 */
DECL|member|grab_state
id|__u8
id|grab_state
suffix:semicolon
multiline_comment|/* 33 */
DECL|member|stream_state
id|__u8
id|stream_state
suffix:semicolon
multiline_comment|/* 34 */
DECL|member|fatal_error
id|__u8
id|fatal_error
suffix:semicolon
multiline_comment|/* 35 */
DECL|member|cmd_error
id|__u8
id|cmd_error
suffix:semicolon
multiline_comment|/* 36 */
DECL|member|debug_flags
id|__u8
id|debug_flags
suffix:semicolon
multiline_comment|/* 37 */
DECL|member|camera_state_7
id|__u8
id|camera_state_7
suffix:semicolon
multiline_comment|/* 38 */
DECL|member|camera_state_8
id|__u8
id|camera_state_8
suffix:semicolon
multiline_comment|/* 39 */
DECL|member|cr_achieved
id|__u8
id|cr_achieved
suffix:semicolon
multiline_comment|/* 40 */
DECL|member|fr_achieved
id|__u8
id|fr_achieved
suffix:semicolon
multiline_comment|/* 41 */
DECL|member|unused3
id|__u8
id|unused3
(braket
l_int|22
)braket
suffix:semicolon
multiline_comment|/* 42 - 63 */
)brace
suffix:semicolon
r_struct
id|usb_device
suffix:semicolon
DECL|struct|cpia_sbuf
r_struct
id|cpia_sbuf
(brace
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
DECL|member|urb
id|urb_t
op_star
id|urb
suffix:semicolon
)brace
suffix:semicolon
r_enum
(brace
DECL|enumerator|FRAME_UNUSED
id|FRAME_UNUSED
comma
multiline_comment|/* Unused (no MCAPTURE) */
DECL|enumerator|FRAME_READY
id|FRAME_READY
comma
multiline_comment|/* Ready to start grabbing */
DECL|enumerator|FRAME_GRABBING
id|FRAME_GRABBING
comma
multiline_comment|/* In the process of being grabbed into */
DECL|enumerator|FRAME_DONE
id|FRAME_DONE
comma
multiline_comment|/* Finished grabbing, but not been synced yet */
DECL|enumerator|FRAME_ERROR
id|FRAME_ERROR
comma
multiline_comment|/* Something bad happened while processing */
)brace
suffix:semicolon
DECL|struct|cpia_frame
r_struct
id|cpia_frame
(brace
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
multiline_comment|/* Frame buffer */
DECL|member|header
r_struct
id|cpia_frame_header
id|header
suffix:semicolon
multiline_comment|/* Header from stream */
DECL|member|width
r_int
id|width
suffix:semicolon
multiline_comment|/* Width application is expecting */
DECL|member|height
r_int
id|height
suffix:semicolon
multiline_comment|/* Height */
DECL|member|hdrwidth
r_int
id|hdrwidth
suffix:semicolon
multiline_comment|/* Width the frame actually is */
DECL|member|hdrheight
r_int
id|hdrheight
suffix:semicolon
multiline_comment|/* Height */
DECL|member|grabstate
r_volatile
r_int
id|grabstate
suffix:semicolon
multiline_comment|/* State of grabbing */
DECL|member|scanstate
r_int
id|scanstate
suffix:semicolon
multiline_comment|/* State of scanning */
DECL|member|curline
r_int
id|curline
suffix:semicolon
multiline_comment|/* Line of frame we&squot;re working on */
DECL|member|scanlength
r_int
id|scanlength
suffix:semicolon
multiline_comment|/* uncompressed, raw data length of frame */
DECL|member|bytes_read
r_int
id|bytes_read
suffix:semicolon
multiline_comment|/* amount of scanlength that has been read from *data */
DECL|member|wq
id|wait_queue_head_t
id|wq
suffix:semicolon
multiline_comment|/* Processes waiting */
)brace
suffix:semicolon
DECL|macro|CPIA_NUMFRAMES
mdefine_line|#define CPIA_NUMFRAMES&t;2
DECL|macro|CPIA_NUMSBUF
mdefine_line|#define CPIA_NUMSBUF&t;2
DECL|struct|usb_cpia
r_struct
id|usb_cpia
(brace
DECL|member|vdev
r_struct
id|video_device
id|vdev
suffix:semicolon
multiline_comment|/* Device structure */
DECL|member|dev
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
DECL|member|iface
r_int
r_char
id|iface
suffix:semicolon
DECL|member|lock
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|member|user
r_int
id|user
suffix:semicolon
multiline_comment|/* user count for exclusive use */
DECL|member|streaming
r_int
id|streaming
suffix:semicolon
multiline_comment|/* Are we streaming Isochronous? */
DECL|member|grabbing
r_int
id|grabbing
suffix:semicolon
multiline_comment|/* Are we grabbing? */
DECL|member|compress
r_int
id|compress
suffix:semicolon
multiline_comment|/* Should the next frame be compressed? */
DECL|member|fbuf
r_char
op_star
id|fbuf
suffix:semicolon
multiline_comment|/* Videodev buffer area */
DECL|member|curframe
r_int
id|curframe
suffix:semicolon
DECL|member|frame
r_struct
id|cpia_frame
id|frame
(braket
id|CPIA_NUMFRAMES
)braket
suffix:semicolon
multiline_comment|/* Double buffering */
DECL|member|cursbuf
r_int
id|cursbuf
suffix:semicolon
multiline_comment|/* Current receiving sbuf */
DECL|member|sbuf
r_struct
id|cpia_sbuf
id|sbuf
(braket
id|CPIA_NUMSBUF
)braket
suffix:semicolon
multiline_comment|/* Double buffering */
multiline_comment|/* Scratch space from the Isochronous pipe */
DECL|member|scratch
r_int
r_char
id|scratch
(braket
id|SCRATCH_BUF_SIZE
)braket
suffix:semicolon
DECL|member|scratchlen
r_int
id|scratchlen
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
