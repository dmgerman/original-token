macro_line|#ifndef __LINUX_VIDEODEV_H
DECL|macro|__LINUX_VIDEODEV_H
mdefine_line|#define __LINUX_VIDEODEV_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020100
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#endif
DECL|struct|video_device
r_struct
id|video_device
(brace
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|hardware
r_int
id|hardware
suffix:semicolon
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|video_device
op_star
comma
r_int
id|mode
)paren
suffix:semicolon
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
r_struct
id|video_device
op_star
)paren
suffix:semicolon
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_struct
id|video_device
op_star
comma
r_char
op_star
comma
r_int
r_int
comma
r_int
id|noblock
)paren
suffix:semicolon
multiline_comment|/* Do we need a write method ? */
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_struct
id|video_device
op_star
comma
r_const
r_char
op_star
comma
r_int
r_int
comma
r_int
id|noblock
)paren
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020100
DECL|member|poll
r_int
r_int
(paren
op_star
id|poll
)paren
(paren
r_struct
id|video_device
op_star
comma
r_struct
id|file
op_star
comma
id|poll_table
op_star
)paren
suffix:semicolon
macro_line|#endif
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|video_device
op_star
comma
r_int
r_int
comma
r_void
op_star
)paren
suffix:semicolon
DECL|member|mmap
r_int
(paren
op_star
id|mmap
)paren
(paren
r_struct
id|video_device
op_star
comma
r_const
r_char
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|initialize
r_int
(paren
op_star
id|initialize
)paren
(paren
r_struct
id|video_device
op_star
)paren
suffix:semicolon
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
multiline_comment|/* Used to be &squot;private&squot; but that upsets C++ */
DECL|member|busy
r_int
id|busy
suffix:semicolon
DECL|member|minor
r_int
id|minor
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|videodev_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|VIDEO_MAJOR
mdefine_line|#define VIDEO_MAJOR&t;81
r_extern
r_int
id|video_register_device
c_func
(paren
r_struct
id|video_device
op_star
comma
r_int
id|type
)paren
suffix:semicolon
DECL|macro|VFL_TYPE_GRABBER
mdefine_line|#define VFL_TYPE_GRABBER&t;0
DECL|macro|VFL_TYPE_VBI
mdefine_line|#define VFL_TYPE_VBI&t;&t;1
DECL|macro|VFL_TYPE_RADIO
mdefine_line|#define VFL_TYPE_RADIO&t;&t;2
DECL|macro|VFL_TYPE_VTX
mdefine_line|#define VFL_TYPE_VTX&t;&t;3
r_extern
r_void
id|video_unregister_device
c_func
(paren
r_struct
id|video_device
op_star
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|VID_TYPE_CAPTURE
mdefine_line|#define VID_TYPE_CAPTURE&t;1&t;/* Can capture */
DECL|macro|VID_TYPE_TUNER
mdefine_line|#define VID_TYPE_TUNER&t;&t;2&t;/* Can tune */
DECL|macro|VID_TYPE_TELETEXT
mdefine_line|#define VID_TYPE_TELETEXT&t;4&t;/* Does teletext */
DECL|macro|VID_TYPE_OVERLAY
mdefine_line|#define VID_TYPE_OVERLAY&t;8&t;/* Overlay onto frame buffer */
DECL|macro|VID_TYPE_CHROMAKEY
mdefine_line|#define VID_TYPE_CHROMAKEY&t;16&t;/* Overlay by chromakey */
DECL|macro|VID_TYPE_CLIPPING
mdefine_line|#define VID_TYPE_CLIPPING&t;32&t;/* Can clip */
DECL|macro|VID_TYPE_FRAMERAM
mdefine_line|#define VID_TYPE_FRAMERAM&t;64&t;/* Uses the frame buffer memory */
DECL|macro|VID_TYPE_SCALES
mdefine_line|#define VID_TYPE_SCALES&t;&t;128&t;/* Scalable */
DECL|macro|VID_TYPE_MONOCHROME
mdefine_line|#define VID_TYPE_MONOCHROME&t;256&t;/* Monochrome only */
DECL|macro|VID_TYPE_SUBCAPTURE
mdefine_line|#define VID_TYPE_SUBCAPTURE&t;512&t;/* Can capture subareas of the image */
DECL|struct|video_capability
r_struct
id|video_capability
(brace
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|channels
r_int
id|channels
suffix:semicolon
multiline_comment|/* Num channels */
DECL|member|audios
r_int
id|audios
suffix:semicolon
multiline_comment|/* Num audio devices */
DECL|member|maxwidth
r_int
id|maxwidth
suffix:semicolon
multiline_comment|/* Supported width */
DECL|member|maxheight
r_int
id|maxheight
suffix:semicolon
multiline_comment|/* And height */
DECL|member|minwidth
r_int
id|minwidth
suffix:semicolon
multiline_comment|/* Supported width */
DECL|member|minheight
r_int
id|minheight
suffix:semicolon
multiline_comment|/* And height */
)brace
suffix:semicolon
DECL|struct|video_channel
r_struct
id|video_channel
(brace
DECL|member|channel
r_int
id|channel
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|tuners
r_int
id|tuners
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|macro|VIDEO_VC_TUNER
mdefine_line|#define VIDEO_VC_TUNER&t;&t;1&t;/* Channel has a tuner */
DECL|macro|VIDEO_VC_AUDIO
mdefine_line|#define VIDEO_VC_AUDIO&t;&t;2&t;/* Channel has audio */
DECL|member|type
id|__u16
id|type
suffix:semicolon
DECL|macro|VIDEO_TYPE_TV
mdefine_line|#define VIDEO_TYPE_TV&t;&t;1
DECL|macro|VIDEO_TYPE_CAMERA
mdefine_line|#define VIDEO_TYPE_CAMERA&t;2&t;
DECL|member|norm
id|__u16
id|norm
suffix:semicolon
multiline_comment|/* Norm set by channel */
)brace
suffix:semicolon
DECL|struct|video_tuner
r_struct
id|video_tuner
(brace
DECL|member|tuner
r_int
id|tuner
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|rangelow
DECL|member|rangehigh
id|ulong
id|rangelow
comma
id|rangehigh
suffix:semicolon
multiline_comment|/* Tuner range */
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|macro|VIDEO_TUNER_PAL
mdefine_line|#define VIDEO_TUNER_PAL&t;&t;1
DECL|macro|VIDEO_TUNER_NTSC
mdefine_line|#define VIDEO_TUNER_NTSC&t;2
DECL|macro|VIDEO_TUNER_SECAM
mdefine_line|#define VIDEO_TUNER_SECAM&t;4
DECL|macro|VIDEO_TUNER_LOW
mdefine_line|#define VIDEO_TUNER_LOW&t;&t;8&t;/* Uses KHz not MHz */
DECL|macro|VIDEO_TUNER_NORM
mdefine_line|#define VIDEO_TUNER_NORM&t;16&t;/* Tuner can set norm */
DECL|macro|VIDEO_TUNER_STEREO_ON
mdefine_line|#define VIDEO_TUNER_STEREO_ON&t;128&t;/* Tuner is seeing stereo */
DECL|member|mode
id|__u16
id|mode
suffix:semicolon
multiline_comment|/* PAL/NTSC/SECAM/OTHER */
DECL|macro|VIDEO_MODE_PAL
mdefine_line|#define VIDEO_MODE_PAL&t;&t;0
DECL|macro|VIDEO_MODE_NTSC
mdefine_line|#define VIDEO_MODE_NTSC&t;&t;1
DECL|macro|VIDEO_MODE_SECAM
mdefine_line|#define VIDEO_MODE_SECAM&t;2
DECL|macro|VIDEO_MODE_AUTO
mdefine_line|#define VIDEO_MODE_AUTO&t;&t;3
DECL|member|signal
id|__u16
id|signal
suffix:semicolon
multiline_comment|/* Signal strength 16bit scale */
)brace
suffix:semicolon
DECL|struct|video_picture
r_struct
id|video_picture
(brace
DECL|member|brightness
id|__u16
id|brightness
suffix:semicolon
DECL|member|hue
id|__u16
id|hue
suffix:semicolon
DECL|member|colour
id|__u16
id|colour
suffix:semicolon
DECL|member|contrast
id|__u16
id|contrast
suffix:semicolon
DECL|member|whiteness
id|__u16
id|whiteness
suffix:semicolon
multiline_comment|/* Black and white only */
DECL|member|depth
id|__u16
id|depth
suffix:semicolon
multiline_comment|/* Capture depth */
DECL|member|palette
id|__u16
id|palette
suffix:semicolon
multiline_comment|/* Palette in use */
DECL|macro|VIDEO_PALETTE_GREY
mdefine_line|#define VIDEO_PALETTE_GREY&t;1&t;/* Linear greyscale */
DECL|macro|VIDEO_PALETTE_HI240
mdefine_line|#define VIDEO_PALETTE_HI240&t;2&t;/* High 240 cube (BT848) */
DECL|macro|VIDEO_PALETTE_RGB565
mdefine_line|#define VIDEO_PALETTE_RGB565&t;3&t;/* 565 16 bit RGB */
DECL|macro|VIDEO_PALETTE_RGB24
mdefine_line|#define VIDEO_PALETTE_RGB24&t;4&t;/* 24bit RGB */
DECL|macro|VIDEO_PALETTE_RGB32
mdefine_line|#define VIDEO_PALETTE_RGB32&t;5&t;/* 32bit RGB */&t;
DECL|macro|VIDEO_PALETTE_RGB555
mdefine_line|#define VIDEO_PALETTE_RGB555&t;6&t;/* 555 15bit RGB */
DECL|macro|VIDEO_PALETTE_YUV422
mdefine_line|#define VIDEO_PALETTE_YUV422&t;7&t;/* YUV422 capture */
DECL|macro|VIDEO_PALETTE_YUYV
mdefine_line|#define VIDEO_PALETTE_YUYV&t;8
DECL|macro|VIDEO_PALETTE_UYVY
mdefine_line|#define VIDEO_PALETTE_UYVY&t;9&t;/* The great thing about standards is ... */
DECL|macro|VIDEO_PALETTE_YUV420
mdefine_line|#define VIDEO_PALETTE_YUV420&t;10
DECL|macro|VIDEO_PALETTE_YUV411
mdefine_line|#define VIDEO_PALETTE_YUV411&t;11&t;/* YUV411 capture */
DECL|macro|VIDEO_PALETTE_RAW
mdefine_line|#define VIDEO_PALETTE_RAW&t;12&t;/* RAW capture (BT848) */
DECL|macro|VIDEO_PALETTE_YUV422P
mdefine_line|#define VIDEO_PALETTE_YUV422P&t;13&t;/* YUV 4:2:2 Planar */
DECL|macro|VIDEO_PALETTE_YUV411P
mdefine_line|#define VIDEO_PALETTE_YUV411P&t;14&t;/* YUV 4:1:1 Planar */
DECL|macro|VIDEO_PALETTE_YUV420P
mdefine_line|#define VIDEO_PALETTE_YUV420P&t;15&t;/* YUV 4:2:0 Planar */
DECL|macro|VIDEO_PALETTE_YUV410P
mdefine_line|#define VIDEO_PALETTE_YUV410P&t;16&t;/* YUV 4:1:0 Planar */
DECL|macro|VIDEO_PALETTE_PLANAR
mdefine_line|#define VIDEO_PALETTE_PLANAR&t;13&t;/* start of planar entries */
DECL|macro|VIDEO_PALETTE_COMPONENT
mdefine_line|#define VIDEO_PALETTE_COMPONENT 7&t;/* start of component entries */
)brace
suffix:semicolon
DECL|struct|video_audio
r_struct
id|video_audio
(brace
DECL|member|audio
r_int
id|audio
suffix:semicolon
multiline_comment|/* Audio channel */
DECL|member|volume
id|__u16
id|volume
suffix:semicolon
multiline_comment|/* If settable */
DECL|member|bass
DECL|member|treble
id|__u16
id|bass
comma
id|treble
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|macro|VIDEO_AUDIO_MUTE
mdefine_line|#define VIDEO_AUDIO_MUTE&t;1
DECL|macro|VIDEO_AUDIO_MUTABLE
mdefine_line|#define VIDEO_AUDIO_MUTABLE&t;2
DECL|macro|VIDEO_AUDIO_VOLUME
mdefine_line|#define VIDEO_AUDIO_VOLUME&t;4
DECL|macro|VIDEO_AUDIO_BASS
mdefine_line|#define VIDEO_AUDIO_BASS&t;8
DECL|macro|VIDEO_AUDIO_TREBLE
mdefine_line|#define VIDEO_AUDIO_TREBLE&t;16&t;
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
DECL|macro|VIDEO_SOUND_MONO
mdefine_line|#define VIDEO_SOUND_MONO&t;1
DECL|macro|VIDEO_SOUND_STEREO
mdefine_line|#define VIDEO_SOUND_STEREO&t;2
DECL|macro|VIDEO_SOUND_LANG1
mdefine_line|#define VIDEO_SOUND_LANG1&t;4
DECL|macro|VIDEO_SOUND_LANG2
mdefine_line|#define VIDEO_SOUND_LANG2&t;8
DECL|member|mode
id|__u16
id|mode
suffix:semicolon
DECL|member|balance
id|__u16
id|balance
suffix:semicolon
multiline_comment|/* Stereo balance */
DECL|member|step
id|__u16
id|step
suffix:semicolon
multiline_comment|/* Step actual volume uses */
)brace
suffix:semicolon
DECL|struct|video_clip
r_struct
id|video_clip
(brace
DECL|member|x
DECL|member|y
id|__s32
id|x
comma
id|y
suffix:semicolon
DECL|member|width
DECL|member|height
id|__s32
id|width
comma
id|height
suffix:semicolon
DECL|member|next
r_struct
id|video_clip
op_star
id|next
suffix:semicolon
multiline_comment|/* For user use/driver use only */
)brace
suffix:semicolon
DECL|struct|video_window
r_struct
id|video_window
(brace
DECL|member|x
DECL|member|y
id|__u32
id|x
comma
id|y
suffix:semicolon
multiline_comment|/* Position of window */
DECL|member|width
DECL|member|height
id|__u32
id|width
comma
id|height
suffix:semicolon
multiline_comment|/* Its size */
DECL|member|chromakey
id|__u32
id|chromakey
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
DECL|member|clips
r_struct
id|video_clip
op_star
id|clips
suffix:semicolon
multiline_comment|/* Set only */
DECL|member|clipcount
r_int
id|clipcount
suffix:semicolon
DECL|macro|VIDEO_WINDOW_INTERLACE
mdefine_line|#define VIDEO_WINDOW_INTERLACE&t;1
DECL|macro|VIDEO_CLIP_BITMAP
mdefine_line|#define VIDEO_CLIP_BITMAP&t;-1
multiline_comment|/* bitmap is 1024x625, a &squot;1&squot; bit represents a clipped pixel */
DECL|macro|VIDEO_CLIPMAP_SIZE
mdefine_line|#define VIDEO_CLIPMAP_SIZE&t;(128 * 625)
)brace
suffix:semicolon
DECL|struct|video_capture
r_struct
id|video_capture
(brace
DECL|member|x
DECL|member|y
id|__u32
id|x
comma
id|y
suffix:semicolon
multiline_comment|/* Offsets into image */
DECL|member|width
DECL|member|height
id|__u32
id|width
comma
id|height
suffix:semicolon
multiline_comment|/* Area to capture */
DECL|member|decimation
id|__u16
id|decimation
suffix:semicolon
multiline_comment|/* Decimation divder */
DECL|member|flags
id|__u16
id|flags
suffix:semicolon
multiline_comment|/* Flags for capture */
DECL|macro|VIDEO_CAPTURE_ODD
mdefine_line|#define VIDEO_CAPTURE_ODD&t;&t;0&t;/* Temporal */
DECL|macro|VIDEO_CAPTURE_EVEN
mdefine_line|#define VIDEO_CAPTURE_EVEN&t;&t;1
)brace
suffix:semicolon
DECL|struct|video_buffer
r_struct
id|video_buffer
(brace
DECL|member|base
r_void
op_star
id|base
suffix:semicolon
DECL|member|height
DECL|member|width
r_int
id|height
comma
id|width
suffix:semicolon
DECL|member|depth
r_int
id|depth
suffix:semicolon
DECL|member|bytesperline
r_int
id|bytesperline
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|video_mmap
r_struct
id|video_mmap
(brace
DECL|member|frame
r_int
r_int
id|frame
suffix:semicolon
multiline_comment|/* Frame (0 - n) for double buffer */
DECL|member|height
DECL|member|width
r_int
id|height
comma
id|width
suffix:semicolon
DECL|member|format
r_int
r_int
id|format
suffix:semicolon
multiline_comment|/* should be VIDEO_PALETTE_* */
)brace
suffix:semicolon
DECL|struct|video_key
r_struct
id|video_key
(brace
DECL|member|key
id|__u8
id|key
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|flags
id|__u32
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|VIDEO_MAX_FRAME
mdefine_line|#define VIDEO_MAX_FRAME&t;&t;32
DECL|struct|video_mbuf
r_struct
id|video_mbuf
(brace
DECL|member|size
r_int
id|size
suffix:semicolon
multiline_comment|/* Total memory to map */
DECL|member|frames
r_int
id|frames
suffix:semicolon
multiline_comment|/* Frames */
DECL|member|offsets
r_int
id|offsets
(braket
id|VIDEO_MAX_FRAME
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|VIDEO_NO_UNIT
mdefine_line|#define &t;VIDEO_NO_UNIT&t;(-1)
DECL|struct|video_unit
r_struct
id|video_unit
(brace
DECL|member|video
r_int
id|video
suffix:semicolon
multiline_comment|/* Video minor */
DECL|member|vbi
r_int
id|vbi
suffix:semicolon
multiline_comment|/* VBI minor */
DECL|member|radio
r_int
id|radio
suffix:semicolon
multiline_comment|/* Radio minor */
DECL|member|audio
r_int
id|audio
suffix:semicolon
multiline_comment|/* Audio minor */
DECL|member|teletext
r_int
id|teletext
suffix:semicolon
multiline_comment|/* Teletext minor */
)brace
suffix:semicolon
DECL|macro|VIDIOCGCAP
mdefine_line|#define VIDIOCGCAP&t;&t;_IOR(&squot;v&squot;,1,struct video_capability)&t;/* Get capabilities */
DECL|macro|VIDIOCGCHAN
mdefine_line|#define VIDIOCGCHAN&t;&t;_IOWR(&squot;v&squot;,2,struct video_channel)&t;/* Get channel info (sources) */
DECL|macro|VIDIOCSCHAN
mdefine_line|#define VIDIOCSCHAN&t;&t;_IOW(&squot;v&squot;,3,struct video_channel)&t;/* Set channel &t;*/
DECL|macro|VIDIOCGTUNER
mdefine_line|#define VIDIOCGTUNER&t;&t;_IOWR(&squot;v&squot;,4,struct video_tuner)&t;&t;/* Get tuner abilities */
DECL|macro|VIDIOCSTUNER
mdefine_line|#define VIDIOCSTUNER&t;&t;_IOW(&squot;v&squot;,5,struct video_tuner)&t;&t;/* Tune the tuner for the current channel */
DECL|macro|VIDIOCGPICT
mdefine_line|#define VIDIOCGPICT&t;&t;_IOR(&squot;v&squot;,6,struct video_picture)&t;/* Get picture properties */
DECL|macro|VIDIOCSPICT
mdefine_line|#define VIDIOCSPICT&t;&t;_IOW(&squot;v&squot;,7,struct video_picture)&t;/* Set picture properties */
DECL|macro|VIDIOCCAPTURE
mdefine_line|#define VIDIOCCAPTURE&t;&t;_IOW(&squot;v&squot;,8,int)&t;&t;&t;&t;/* Start, end capture */
DECL|macro|VIDIOCGWIN
mdefine_line|#define VIDIOCGWIN&t;&t;_IOR(&squot;v&squot;,9, struct video_window)&t;/* Set the video overlay window */
DECL|macro|VIDIOCSWIN
mdefine_line|#define VIDIOCSWIN&t;&t;_IOW(&squot;v&squot;,10, struct video_window)&t;/* Set the video overlay window - passes clip list for hardware smarts , chromakey etc */
DECL|macro|VIDIOCGFBUF
mdefine_line|#define VIDIOCGFBUF&t;&t;_IOR(&squot;v&squot;,11, struct video_buffer)&t;/* Get frame buffer */
DECL|macro|VIDIOCSFBUF
mdefine_line|#define VIDIOCSFBUF&t;&t;_IOW(&squot;v&squot;,12, struct video_buffer)&t;/* Set frame buffer - root only */
DECL|macro|VIDIOCKEY
mdefine_line|#define VIDIOCKEY&t;&t;_IOR(&squot;v&squot;,13, struct video_key)&t;&t;/* Video key event - to dev 255 is to all - cuts capture on all DMA windows with this key (0xFFFFFFFF == all) */
DECL|macro|VIDIOCGFREQ
mdefine_line|#define VIDIOCGFREQ&t;&t;_IOR(&squot;v&squot;,14, unsigned long)&t;&t;/* Set tuner */
DECL|macro|VIDIOCSFREQ
mdefine_line|#define VIDIOCSFREQ&t;&t;_IOW(&squot;v&squot;,15, unsigned long)&t;&t;/* Set tuner */
DECL|macro|VIDIOCGAUDIO
mdefine_line|#define VIDIOCGAUDIO&t;&t;_IOR(&squot;v&squot;,16, struct video_audio)&t;/* Get audio info */
DECL|macro|VIDIOCSAUDIO
mdefine_line|#define VIDIOCSAUDIO&t;&t;_IOW(&squot;v&squot;,17, struct video_audio)&t;/* Audio source, mute etc */
DECL|macro|VIDIOCSYNC
mdefine_line|#define VIDIOCSYNC&t;&t;_IOW(&squot;v&squot;,18, int)&t;&t;&t;/* Sync with mmap grabbing */
DECL|macro|VIDIOCMCAPTURE
mdefine_line|#define VIDIOCMCAPTURE&t;&t;_IOW(&squot;v&squot;,19, struct video_mmap)&t;&t;/* Grab frames */
DECL|macro|VIDIOCGMBUF
mdefine_line|#define VIDIOCGMBUF&t;&t;_IOR(&squot;v&squot;, 20, struct video_mbuf)&t;/* Memory map buffer info */
DECL|macro|VIDIOCGUNIT
mdefine_line|#define VIDIOCGUNIT&t;&t;_IOR(&squot;v&squot;, 21, struct video_unit)&t;/* Get attached units */
DECL|macro|VIDIOCGCAPTURE
mdefine_line|#define VIDIOCGCAPTURE&t;&t;_IOR(&squot;v&squot;,22, struct video_capture)&t;/* Get frame buffer */
DECL|macro|VIDIOCSCAPTURE
mdefine_line|#define VIDIOCSCAPTURE&t;&t;_IOW(&squot;v&squot;,23, struct video_capture)&t;/* Set frame buffer - root only */
DECL|macro|BASE_VIDIOCPRIVATE
mdefine_line|#define BASE_VIDIOCPRIVATE&t;192&t;&t;/* 192-255 are private */
DECL|macro|VID_HARDWARE_BT848
mdefine_line|#define VID_HARDWARE_BT848&t;1
DECL|macro|VID_HARDWARE_QCAM_BW
mdefine_line|#define VID_HARDWARE_QCAM_BW&t;2
DECL|macro|VID_HARDWARE_PMS
mdefine_line|#define VID_HARDWARE_PMS&t;3
DECL|macro|VID_HARDWARE_QCAM_C
mdefine_line|#define VID_HARDWARE_QCAM_C&t;4
DECL|macro|VID_HARDWARE_PSEUDO
mdefine_line|#define VID_HARDWARE_PSEUDO&t;5
DECL|macro|VID_HARDWARE_SAA5249
mdefine_line|#define VID_HARDWARE_SAA5249&t;6
DECL|macro|VID_HARDWARE_AZTECH
mdefine_line|#define VID_HARDWARE_AZTECH&t;7
DECL|macro|VID_HARDWARE_SF16MI
mdefine_line|#define VID_HARDWARE_SF16MI&t;8
DECL|macro|VID_HARDWARE_RTRACK
mdefine_line|#define VID_HARDWARE_RTRACK&t;9
DECL|macro|VID_HARDWARE_ZOLTRIX
mdefine_line|#define VID_HARDWARE_ZOLTRIX&t;10
DECL|macro|VID_HARDWARE_SAA7146
mdefine_line|#define VID_HARDWARE_SAA7146    11
DECL|macro|VID_HARDWARE_VIDEUM
mdefine_line|#define VID_HARDWARE_VIDEUM&t;12&t;/* Reserved for Winnov videum */
DECL|macro|VID_HARDWARE_RTRACK2
mdefine_line|#define VID_HARDWARE_RTRACK2&t;13
DECL|macro|VID_HARDWARE_PERMEDIA2
mdefine_line|#define VID_HARDWARE_PERMEDIA2&t;14&t;/* Reserved for Permedia2 */
DECL|macro|VID_HARDWARE_RIVA128
mdefine_line|#define VID_HARDWARE_RIVA128&t;15&t;/* Reserved for RIVA 128 */
DECL|macro|VID_HARDWARE_PLANB
mdefine_line|#define VID_HARDWARE_PLANB&t;16&t;/* PowerMac motherboard video-in */
DECL|macro|VID_HARDWARE_BROADWAY
mdefine_line|#define VID_HARDWARE_BROADWAY&t;17&t;/* Broadway project */
DECL|macro|VID_HARDWARE_GEMTEK
mdefine_line|#define VID_HARDWARE_GEMTEK&t;18
multiline_comment|/*&n; *&t;Initialiser list&n; */
DECL|struct|video_init
r_struct
id|video_init
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|video_init
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
