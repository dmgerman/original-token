macro_line|#ifndef _LINUX_FD_H
DECL|macro|_LINUX_FD_H
mdefine_line|#define _LINUX_FD_H
DECL|macro|FDCLRPRM
mdefine_line|#define FDCLRPRM 0 /* clear user-defined parameters */
DECL|macro|FDSETPRM
mdefine_line|#define FDSETPRM 1 /* set user-defined parameters for current media */
DECL|macro|FDSETMEDIAPRM
mdefine_line|#define FDSETMEDIAPRM 1
DECL|macro|FDDEFPRM
mdefine_line|#define FDDEFPRM 2 /* set user-defined parameters until explicitly cleared */
DECL|macro|FDDEFMEDIAPRM
mdefine_line|#define FDDEFMEDIAPRM 2
DECL|macro|FDGETPRM
mdefine_line|#define FDGETPRM 3 /* get disk parameters */
DECL|macro|FDGETMEDIAPRM
mdefine_line|#define FDGETMEDIAPRM 3
DECL|macro|FDMSGON
mdefine_line|#define&t;FDMSGON  4 /* issue kernel messages on media type change */
DECL|macro|FDMSGOFF
mdefine_line|#define&t;FDMSGOFF 5 /* don&squot;t issue kernel messages on media type change */
DECL|macro|FDFMTBEG
mdefine_line|#define FDFMTBEG 6 /* begin formatting a disk */
DECL|macro|FDFMTTRK
mdefine_line|#define&t;FDFMTTRK 7 /* format the specified track */
DECL|macro|FDFMTEND
mdefine_line|#define FDFMTEND 8 /* end formatting a disk */
DECL|macro|FDSETEMSGTRESH
mdefine_line|#define FDSETEMSGTRESH&t;10&t;/* set fdc error reporting threshold */
DECL|macro|FDFLUSH
mdefine_line|#define FDFLUSH  11 /* flush buffers for media; either for verifying media, or for&n;                       handling a media change without closing the file&n;&t;&t;       descriptor */
DECL|macro|FDSETMAXERRS
mdefine_line|#define FDSETMAXERRS 12 /* set abortion and read_track threshold */
DECL|macro|FDGETMAXERRS
mdefine_line|#define FDGETMAXERRS 14 /* get abortion and read_track threshold */
DECL|macro|FDGETDRVTYP
mdefine_line|#define FDGETDRVTYP 16          /* get drive type: 5 1/4 or 3 1/2 */
DECL|macro|FDSETDRVPRM
mdefine_line|#define FDSETDRVPRM 20 /* set drive parameters */
DECL|macro|FDGETDRVPRM
mdefine_line|#define FDGETDRVPRM 21 /* get drive parameters */
DECL|macro|FDGETDRVSTAT
mdefine_line|#define FDGETDRVSTAT 22 /* get drive state */
DECL|macro|FDPOLLDRVSTAT
mdefine_line|#define FDPOLLDRVSTAT 23 /* get drive state */
DECL|macro|FDGETFDCSTAT
mdefine_line|#define FDGETFDCSTAT 25 /* get fdc state */
DECL|macro|FDWERRORCLR
mdefine_line|#define FDWERRORCLR  27 /* clear write error and badness information */
DECL|macro|FDWERRORGET
mdefine_line|#define FDWERRORGET  28 /* get write error and badness information */
DECL|macro|FDRESET
mdefine_line|#define FDRESET 24 /* reset FDC */
DECL|macro|FD_RESET_IF_NEEDED
mdefine_line|#define FD_RESET_IF_NEEDED 0
DECL|macro|FD_RESET_IF_RAWCMD
mdefine_line|#define FD_RESET_IF_RAWCMD 1
DECL|macro|FD_RESET_ALWAYS
mdefine_line|#define FD_RESET_ALWAYS 2
DECL|macro|FDBAILOUT
mdefine_line|#define FDBAILOUT 26 /* release all fdc locks */
DECL|macro|FD_CLEAR_RESET
mdefine_line|#define FD_CLEAR_RESET 0
DECL|macro|FD_COMPLETE_FORMAT
mdefine_line|#define FD_COMPLETE_FORMAT 1
DECL|macro|FD_UNLOCK_FDC
mdefine_line|#define FD_UNLOCK_FDC 2
DECL|macro|FDRAWCMD
mdefine_line|#define FDRAWCMD 30 /* send a raw command to the fdc */
DECL|macro|FDTWADDLE
mdefine_line|#define FDTWADDLE 40 /* flicker motor-on bit before reading a sector */
multiline_comment|/*&n; * Maximum number of sectors in a track buffer. Track buffering is disabled&n; * if tracks are bigger.&n; */
DECL|macro|MAX_BUFFER_SECTORS
mdefine_line|#define MAX_BUFFER_SECTORS 24 /* was 18 -bb */
DECL|macro|FD_FILL_BYTE
mdefine_line|#define FD_FILL_BYTE 0xF6 /* format fill byte */
DECL|macro|FD_2M
mdefine_line|#define FD_2M 0x4
DECL|macro|FD_SIZECODEMASK
mdefine_line|#define FD_SIZECODEMASK 0x38
DECL|macro|FD_SIZECODE
mdefine_line|#define FD_SIZECODE(floppy) (((((floppy)-&gt;rate&amp;FD_SIZECODEMASK)&gt;&gt; 3)+ 2) %8)
DECL|macro|FD_SECTSIZE
mdefine_line|#define FD_SECTSIZE(floppy) ( (floppy)-&gt;rate &amp; FD_2M ? &bslash;&n;&t;&t;&t;     512 : 128 &lt;&lt; FD_SIZECODE(floppy) )
DECL|macro|FD_PERP
mdefine_line|#define FD_PERP 0x40
macro_line|#ifndef ASSEMBLER
DECL|struct|floppy_struct
r_struct
id|floppy_struct
(brace
DECL|member|size
r_int
r_int
id|size
comma
multiline_comment|/* nr of sectors total */
DECL|member|sect
id|sect
comma
multiline_comment|/* sectors per track */
DECL|member|head
id|head
comma
multiline_comment|/* nr of heads */
DECL|member|track
id|track
comma
multiline_comment|/* nr of tracks */
DECL|member|stretch
id|stretch
suffix:semicolon
multiline_comment|/* !=0 means double track steps */
DECL|member|gap
r_int
r_char
id|gap
comma
multiline_comment|/* gap1 size */
DECL|member|rate
id|rate
comma
multiline_comment|/* data rate. |= 0x40 for perpendicular */
DECL|member|spec1
id|spec1
comma
multiline_comment|/* stepping rate, head unload time */
DECL|member|fmt_gap
id|fmt_gap
suffix:semicolon
multiline_comment|/* gap2 size */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* used only for predefined formats */
)brace
suffix:semicolon
DECL|struct|format_descr
r_struct
id|format_descr
(brace
DECL|member|device
DECL|member|head
DECL|member|track
r_int
r_int
id|device
comma
id|head
comma
id|track
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|floppy_max_errors
r_struct
id|floppy_max_errors
(brace
r_int
r_int
DECL|member|abort
m_abort
comma
multiline_comment|/* number of errors to be reached before aborting */
DECL|member|read_track
id|read_track
comma
multiline_comment|/* maximal number of errors permitted to read an&n;&t;&t;       * entire track at once */
DECL|member|reset
id|reset
comma
multiline_comment|/* maximal number of errors before a reset is tried */
DECL|member|recal
id|recal
comma
multiline_comment|/* maximal number of errors before a recalibrate is&n;&t;&t;       * tried */
multiline_comment|/*&n;&t;   * Threshold for reporting FDC errors to the console.&n;&t;   * Setting this to zero may flood your screen when using&n;&t;   * ultra cheap floppies ;-)&n;&t;   */
DECL|member|reporting
id|reporting
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|floppy_drive_params
r_struct
id|floppy_drive_params
(brace
DECL|member|cmos
r_char
id|cmos
suffix:semicolon
multiline_comment|/* cmos type */
multiline_comment|/* Spec2 is (HLD&lt;&lt;1 | ND), where HLD is head load time (1=2ms, 2=4 ms etc)&n;   * and ND is set means no DMA. Hardcoded to 6 (HLD=6ms, use DMA).&n;   */
DECL|member|max_dtr
r_int
r_int
id|max_dtr
suffix:semicolon
multiline_comment|/* Step rate, usec */
DECL|member|hlt
r_int
r_int
id|hlt
suffix:semicolon
multiline_comment|/* Head load/settle time, msec */
DECL|member|hut
r_int
r_int
id|hut
suffix:semicolon
multiline_comment|/* Head unload time (remnant of 8&quot; drives) */
DECL|member|srt
r_int
r_int
id|srt
suffix:semicolon
multiline_comment|/* Step rate, usec */
DECL|member|spinup
r_int
r_int
id|spinup
suffix:semicolon
multiline_comment|/* time needed for spinup ( in jiffies) */
DECL|member|spindown
r_int
r_int
id|spindown
suffix:semicolon
multiline_comment|/* timeout needed for spindown */
DECL|member|spindown_offset
r_int
r_char
id|spindown_offset
suffix:semicolon
multiline_comment|/* decides in which position the disk&n;&t;&t;&t;&t; * will stop */
DECL|member|select_delay
r_int
r_char
id|select_delay
suffix:semicolon
multiline_comment|/* delay to wait after select */
DECL|member|rps
r_int
r_char
id|rps
suffix:semicolon
multiline_comment|/* rotations per second */
DECL|member|tracks
r_int
r_char
id|tracks
suffix:semicolon
multiline_comment|/* maximum number of tracks */
DECL|member|timeout
r_int
r_int
id|timeout
suffix:semicolon
multiline_comment|/* timeout for interrupt requests */
DECL|member|interleave_sect
r_int
r_char
id|interleave_sect
suffix:semicolon
multiline_comment|/* if there are more sectors, use interleave */
DECL|member|max_errors
r_struct
id|floppy_max_errors
id|max_errors
suffix:semicolon
DECL|member|flags
r_char
id|flags
suffix:semicolon
multiline_comment|/* various flags, including ftd_msg */
multiline_comment|/*&n; * Announce successful media type detection and media information loss after&n; * disk changes.&n; * Also used to enable/disable printing of overrun warnings.&n; */
DECL|macro|FTD_MSG
mdefine_line|#define FTD_MSG 0x10
DECL|member|read_track
r_char
id|read_track
suffix:semicolon
multiline_comment|/* use readtrack during probing? */
multiline_comment|/*&n; * Auto-detection. Each drive type has eight formats which are&n; * used in succession to try to read the disk. If the FDC cannot lock onto&n; * the disk, the next format is tried. This uses the variable &squot;probing&squot;.&n; */
DECL|member|autodetect
r_int
id|autodetect
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* autodetected formats */
DECL|member|checkfreq
r_int
id|checkfreq
suffix:semicolon
multiline_comment|/* how often should the drive be checked for disk changes */
DECL|member|native_format
r_int
id|native_format
suffix:semicolon
multiline_comment|/* native format of this drive */
)brace
suffix:semicolon
DECL|struct|floppy_drive_struct
r_struct
id|floppy_drive_struct
(brace
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
multiline_comment|/* values for these flags */
DECL|macro|FD_NEED_TWADDLE
mdefine_line|#define FD_NEED_TWADDLE 1 /* more magic */
DECL|macro|FD_VERIFY
mdefine_line|#define FD_VERIFY 2 /* this is set at bootup to force an initial drive status&n;&t;&t;   inquiry*/
DECL|macro|FD_DISK_NEWCHANGE
mdefine_line|#define FD_DISK_NEWCHANGE 4 /* change detected, and no action undertaken yet to&n;&t;&t;&t;    clear media change status */
DECL|macro|FD_DRIVE_PRESENT
mdefine_line|#define FD_DRIVE_PRESENT 8
DECL|macro|FD_DISK_WRITABLE
mdefine_line|#define FD_DISK_WRITABLE 32
DECL|member|spinup_date
r_int
r_int
r_volatile
id|spinup_date
suffix:semicolon
DECL|member|select_date
r_int
r_int
r_volatile
id|select_date
suffix:semicolon
DECL|member|first_read_date
r_int
r_int
r_volatile
id|first_read_date
suffix:semicolon
DECL|member|probed_format
r_int
id|probed_format
suffix:semicolon
DECL|member|track
r_int
id|track
suffix:semicolon
multiline_comment|/* current track */
DECL|member|maxblock
r_int
id|maxblock
suffix:semicolon
multiline_comment|/* id of highest block read */
DECL|member|maxtrack
r_int
id|maxtrack
suffix:semicolon
multiline_comment|/* id of highest half track read */
DECL|member|generation
r_int
id|generation
suffix:semicolon
multiline_comment|/* how many diskchanges? */
multiline_comment|/*&n; * (User-provided) media information is _not_ discarded after a media change&n; * if the corresponding keep_data flag is non-zero. Positive values are&n; * decremented after each probe.&n; */
DECL|member|keep_data
r_int
id|keep_data
suffix:semicolon
multiline_comment|/* Prevent &quot;aliased&quot; accesses. */
DECL|member|fd_ref
r_int
id|fd_ref
suffix:semicolon
DECL|member|fd_device
r_int
id|fd_device
suffix:semicolon
DECL|member|last_checked
r_int
id|last_checked
suffix:semicolon
multiline_comment|/* when was the drive last checked for a disk change? */
)brace
suffix:semicolon
DECL|struct|floppy_write_errors
r_struct
id|floppy_write_errors
(brace
multiline_comment|/* Write error logging.&n;   *&n;   * These fields can be cleared with the FDWERRORCLR ioctl.&n;   * Only writes that were attempted but failed due to a physical media&n;   * error are logged.  write(2) calls that fail and return an error code&n;   * to the user process are not counted.&n;   */
DECL|member|write_errors
r_int
r_int
id|write_errors
suffix:semicolon
multiline_comment|/* number of physical write errors encountered */
multiline_comment|/* position of first and last write errors */
DECL|member|first_error_sector
r_int
r_int
id|first_error_sector
suffix:semicolon
DECL|member|first_error_generation
r_int
id|first_error_generation
suffix:semicolon
DECL|member|last_error_sector
r_int
r_int
id|last_error_sector
suffix:semicolon
DECL|member|last_error_generation
r_int
id|last_error_generation
suffix:semicolon
DECL|member|badness
r_int
r_int
id|badness
suffix:semicolon
multiline_comment|/* highest retry count for a read or write operation */
)brace
suffix:semicolon
DECL|struct|floppy_fdc_state
r_struct
id|floppy_fdc_state
(brace
DECL|member|spec1
r_int
id|spec1
suffix:semicolon
multiline_comment|/* spec1 value last used */
DECL|member|spec2
r_int
id|spec2
suffix:semicolon
multiline_comment|/* spec2 value last used */
DECL|member|dtr
r_int
id|dtr
suffix:semicolon
DECL|member|version
r_int
r_char
id|version
suffix:semicolon
multiline_comment|/* FDC version code */
DECL|member|dor
r_int
r_char
id|dor
suffix:semicolon
DECL|member|address
r_int
id|address
suffix:semicolon
multiline_comment|/* io address */
DECL|member|rawcmd
r_int
r_int
id|rawcmd
suffix:colon
l_int|2
suffix:semicolon
DECL|member|reset
r_int
r_int
id|reset
suffix:colon
l_int|1
suffix:semicolon
DECL|member|need_configure
r_int
r_int
id|need_configure
suffix:colon
l_int|1
suffix:semicolon
DECL|member|perp_mode
r_int
r_int
id|perp_mode
suffix:colon
l_int|2
suffix:semicolon
DECL|member|has_fifo
r_int
r_int
id|has_fifo
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|floppy_raw_cmd
r_struct
id|floppy_raw_cmd
(brace
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|rate
r_int
r_char
id|rate
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|member|cmd_count
r_int
r_char
id|cmd_count
suffix:semicolon
DECL|member|cmd
r_int
r_char
id|cmd
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|reply_count
r_int
r_char
id|reply_count
suffix:semicolon
DECL|member|reply
r_int
r_char
id|reply
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|track
r_int
id|track
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/* meaning of the various bytes */
multiline_comment|/* flags */
DECL|macro|FD_RAW_READ
mdefine_line|#define FD_RAW_READ 1
DECL|macro|FD_RAW_WRITE
mdefine_line|#define FD_RAW_WRITE 2
DECL|macro|FD_RAW_INTR
mdefine_line|#define FD_RAW_INTR 8
DECL|macro|FD_RAW_SPIN
mdefine_line|#define FD_RAW_SPIN 16
DECL|macro|FD_RAW_NEED_DISK
mdefine_line|#define FD_RAW_NEED_DISK 64
DECL|macro|FD_RAW_NEED_SEEK
mdefine_line|#define FD_RAW_NEED_SEEK 128
DECL|macro|FD_RAW_USER_SUPPLIED
mdefine_line|#define FD_RAW_USER_SUPPLIED 256
macro_line|#endif
eof
