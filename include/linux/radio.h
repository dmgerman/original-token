multiline_comment|/*&n; * linux/radio.h&n; *&n; * Include for radio card support under linux&n; * Another pointless suid-binary removal utility... :-)&n; */
macro_line|#ifndef _LINUX_RADIO_H
DECL|macro|_LINUX_RADIO_H
mdefine_line|#define _LINUX_RADIO_H
macro_line|#include &lt;linux/ioctl.h&gt;
multiline_comment|/*&n; * Constants&n; */
multiline_comment|/* Various types of Radio card... */
multiline_comment|/* (NB.  I&squot;ve made this a bit-field.  It might make the difference one day.) */
DECL|macro|RADIO_TYPE_UNSUP
mdefine_line|#define&t;RADIO_TYPE_UNSUP&t;0x0000
DECL|macro|RADIO_TYPE_RTRACK
mdefine_line|#define&t;RADIO_TYPE_RTRACK&t;0x0001&t;/* AIMSlab RadioTrack (RadioReveal) card -- basic, to say the least */
DECL|macro|RADIO_TYPE_WINRADIO
mdefine_line|#define&t;RADIO_TYPE_WINRADIO&t;0x0002&t;/* Dunno, but made by someone */
DECL|macro|RADIO_TYPE_TYPHOON
mdefine_line|#define&t;RADIO_TYPE_TYPHOON&t;0x0004&t;/* It exists... */
multiline_comment|/* waveband types */
DECL|macro|RADIO_PROTOCOL_AM
mdefine_line|#define&t;RADIO_PROTOCOL_AM&t;0x0010&t;/* AM &quot;protocol&quot; */
DECL|macro|RADIO_PROTOCOL_FM
mdefine_line|#define&t;RADIO_PROTOCOL_FM&t;0x0020&t;/* FM &quot;protocol&quot; */
DECL|macro|RADIO_PROTOCOL_SSB
mdefine_line|#define&t;RADIO_PROTOCOL_SSB&t;0x0040&t;/* SSB */
multiline_comment|/* and no doubt some other stuff, too (Brian?) */
multiline_comment|/* the following are _very_ inaccurate; essentially, all that&n; * they do is provide a &quot;name&quot; for client programs&n; */
DECL|macro|RADIO_BAND_UNKNOWN
mdefine_line|#define&t;RADIO_BAND_UNKNOWN&t;0x0000&t;/* other */
DECL|macro|RADIO_BAND_AM_SW
mdefine_line|#define&t;RADIO_BAND_AM_SW&t;0x0100&t;/* short wave (?) */
DECL|macro|RADIO_BAND_AM_MW
mdefine_line|#define&t;RADIO_BAND_AM_MW&t;0x0200&t;/* medium wave (540 - 1600) */
DECL|macro|RADIO_BAND_AM_LW
mdefine_line|#define&t;RADIO_BAND_AM_LW&t;0x0400&t;/* long wave (150 - 270) */
DECL|macro|RADIO_BAND_FM_STD
mdefine_line|#define&t;RADIO_BAND_FM_STD&t;0x1000&t;/* &quot;standard&quot; FM band (i.e.  88 - 108 or so) */
multiline_comment|/* Since floating-point stuff is illegal in the kernel, we use these&n; * pairs of macros to convert to, and from userland floats&n; * (I hope these are general enough!)&n; */
multiline_comment|/* Remember to make sure that all of these are integral... */
multiline_comment|/* Also remember to pass sensible things in here (MHz for FM, kHz for AM) */
DECL|macro|RADIO_FM_RES
mdefine_line|#define&t;RADIO_FM_RES&t;&t;100&t;/* 0.01 MHZ */
DECL|macro|RADIO_FM_FRTOINT
mdefine_line|#define&t;RADIO_FM_FRTOINT(fl)&t;((int)(((float)(fl))*RADIO_FM_RES))
DECL|macro|RADIO_FM_INTTOFR
mdefine_line|#define&t;RADIO_FM_INTTOFR(fr)&t;((float)(((int)(fr))/RADIO_FM_RES))
multiline_comment|/* Old RadioTrack definitions&n;#define RADIO_FM_FRTOINT(fl)&t;((int)(((float)(fl)-88.0)*40)+0xf6c)&n;#define RADIO_FM_INTTOFR(fr)&t;((float)(((fr)-0xf6c)/40)+88.0)&n;*/
DECL|macro|RADIO_AM_RES
mdefine_line|#define&t;RADIO_AM_RES&t;&t;1&t;/* 1 kHz */
DECL|macro|RADIO_AM_FRTOINT
mdefine_line|#define&t;RADIO_AM_FRTOINT(fl)&t;((int)(((float)(fl))*RADIO_AM_RES))
DECL|macro|RADIO_AM_INTTOFR
mdefine_line|#define&t;RADIO_AM_INTTOFR(fr)&t;((float)(((int)(fr))/RADIO_AM_RES))
multiline_comment|/*&n; * Structures &n; */
multiline_comment|/* query structures */
DECL|struct|radio_cap
r_struct
id|radio_cap
(brace
DECL|member|dev_num
r_int
id|dev_num
suffix:semicolon
multiline_comment|/* device index */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* device type (see above) */
DECL|member|num_bwidths
r_int
id|num_bwidths
suffix:semicolon
multiline_comment|/* number of &quot;bandwidths&quot; supported */
DECL|member|volmin
DECL|member|volmax
r_int
id|volmin
comma
id|volmax
suffix:semicolon
multiline_comment|/* min/max in steps of one */
)brace
suffix:semicolon
DECL|struct|radio_band
r_struct
id|radio_band
(brace
DECL|member|dev_num
r_int
id|dev_num
suffix:semicolon
multiline_comment|/* device index (IN) */
DECL|member|index
r_int
id|index
suffix:semicolon
multiline_comment|/* &quot;bandwidth&quot; index (IN) */
DECL|member|proto
r_int
id|proto
suffix:semicolon
multiline_comment|/* protocol (AM, FM, SSB, etc) (OUT) */
DECL|member|types
r_int
id|types
suffix:semicolon
multiline_comment|/* see RADIO_BAND_* above */
DECL|member|freqmin
DECL|member|freqmax
r_int
id|freqmin
comma
id|freqmax
suffix:semicolon
multiline_comment|/* encoded according to the macros above */
DECL|member|strmin
DECL|member|strmax
r_int
id|strmin
comma
id|strmax
suffix:semicolon
multiline_comment|/* min/max signal strength (steps of 1) */
)brace
suffix:semicolon
multiline_comment|/* Previously, this was in four separate structures:&n; * radio_vol, radio_freq, radio_band and radio_sigstr,&n; * That was foolish, but now it&squot;s not so obvious what&squot;s going on.&n; * Be careful.&n; */
DECL|struct|radio_ctl
r_struct
id|radio_ctl
(brace
DECL|member|dev_num
r_int
id|dev_num
suffix:semicolon
multiline_comment|/* device index (IN) */
DECL|member|value
r_int
id|value
suffix:semicolon
multiline_comment|/* volume, frequency, band, sigstr */
)brace
suffix:semicolon
multiline_comment|/*&n; * ioctl numbers&n; */
multiline_comment|/* You have _how_ many radio devices? =) */
DECL|macro|RADIO_NUMDEVS
mdefine_line|#define&t;RADIO_NUMDEVS&t;_IOR(0x8c, 0x00, int)
DECL|macro|RADIO_GETCAPS
mdefine_line|#define&t;RADIO_GETCAPS&t;_IOR(0x8c, 0x01, struct radio_cap)
DECL|macro|RADIO_GETBNDCAP
mdefine_line|#define&t;RADIO_GETBNDCAP&t;_IOR(0x8c, 0x02, struct radio_band)
DECL|macro|RADIO_SETVOL
mdefine_line|#define&t;RADIO_SETVOL&t;_IOW(0x8c, 0x10, struct radio_ctl)
DECL|macro|RADIO_GETVOL
mdefine_line|#define&t;RADIO_GETVOL&t;_IOR(0x8c, 0x11, struct radio_ctl)
DECL|macro|RADIO_SETBAND
mdefine_line|#define&t;RADIO_SETBAND&t;_IOW(0x8c, 0x12, struct radio_ctl)
DECL|macro|RADIO_GETBAND
mdefine_line|#define&t;RADIO_GETBAND&t;_IOR(0x8c, 0x13, struct radio_ctl)
DECL|macro|RADIO_SETFREQ
mdefine_line|#define&t;RADIO_SETFREQ&t;_IOW(0x8c, 0x14, struct radio_ctl)
DECL|macro|RADIO_GETFREQ
mdefine_line|#define&t;RADIO_GETFREQ&t;_IOR(0x8c, 0x15, struct radio_ctl)
DECL|macro|RADIO_GETSIGSTR
mdefine_line|#define&t;RADIO_GETSIGSTR&t;_IOR(0x8c, 0x30, struct radio_ctl)
multiline_comment|/* kernel specific stuff... */
macro_line|#ifdef __KERNEL__
multiline_comment|/* Try to keep the number of function pointers to a minimum.&n; * Devices are responsible for updating, or otherwise, the&n; * variables here, not the outside wrapper.&n; */
r_struct
id|radio_device
suffix:semicolon
r_int
id|radio_add_device
c_func
(paren
r_struct
id|radio_device
op_star
id|newdev
)paren
suffix:semicolon
DECL|struct|radio_device
r_struct
id|radio_device
(brace
DECL|member|cap
r_struct
id|radio_cap
op_star
id|cap
suffix:semicolon
DECL|member|bands
r_struct
id|radio_band
op_star
id|bands
suffix:semicolon
multiline_comment|/* pointer to array of radio_bands */
DECL|member|setvol
r_int
(paren
op_star
id|setvol
)paren
(paren
r_struct
id|radio_device
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|curvol
r_int
id|curvol
suffix:semicolon
DECL|member|setband
r_int
(paren
op_star
id|setband
)paren
(paren
r_struct
id|radio_device
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|curband
r_int
id|curband
suffix:semicolon
DECL|member|setfreq
r_int
(paren
op_star
id|setfreq
)paren
(paren
r_struct
id|radio_device
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|curfreq
r_int
id|curfreq
suffix:semicolon
DECL|member|getsigstr
r_int
(paren
op_star
id|getsigstr
)paren
(paren
r_struct
id|radio_device
op_star
)paren
suffix:semicolon
DECL|member|next
r_struct
id|radio_device
op_star
id|next
suffix:semicolon
DECL|member|misc
r_void
op_star
id|misc
suffix:semicolon
multiline_comment|/* device internal storage... (eg i/o addresses, etc */
)brace
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_RADIO_H */
eof
