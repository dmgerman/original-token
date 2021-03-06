multiline_comment|/*&n; * IOCTL Command Codes&n; */
DECL|macro|SCIOCLOAD
mdefine_line|#define SCIOCLOAD&t;0x01&t;/* Load a firmware record */
DECL|macro|SCIOCRESET
mdefine_line|#define SCIOCRESET&t;0x02&t;/* Perform hard reset */
DECL|macro|SCIOCDEBUG
mdefine_line|#define SCIOCDEBUG&t;0x03&t;/* Set debug level */
DECL|macro|SCIOCREV
mdefine_line|#define SCIOCREV&t;0x04&t;/* Get driver revision(s) */
DECL|macro|SCIOCSTART
mdefine_line|#define SCIOCSTART&t;0x05&t;/* Start the firmware */
DECL|macro|SCIOCGETSWITCH
mdefine_line|#define SCIOCGETSWITCH&t;0x06&t;/* Get switch type */
DECL|macro|SCIOCSETSWITCH
mdefine_line|#define SCIOCSETSWITCH&t;0x07&t;/* Set switch type */
DECL|macro|SCIOCGETSPID
mdefine_line|#define SCIOCGETSPID&t;0x08&t;/* Get channel SPID */
DECL|macro|SCIOCSETSPID
mdefine_line|#define SCIOCSETSPID&t;0x09 &t;/* Set channel SPID */
DECL|macro|SCIOCGETDN
mdefine_line|#define SCIOCGETDN&t;0x0A&t;/* Get channel DN */
DECL|macro|SCIOCSETDN
mdefine_line|#define SCIOCSETDN&t;0x0B &t;/* Set channel DN */
DECL|macro|SCIOCTRACE
mdefine_line|#define SCIOCTRACE&t;0x0C&t;/* Toggle trace mode */
DECL|macro|SCIOCSTAT
mdefine_line|#define SCIOCSTAT&t;0x0D&t;/* Get line status */
DECL|macro|SCIOCGETSPEED
mdefine_line|#define SCIOCGETSPEED&t;0x0E&t;/* Set channel speed */
DECL|macro|SCIOCSETSPEED
mdefine_line|#define SCIOCSETSPEED&t;0x0F&t;/* Set channel speed */
DECL|macro|SCIOCLOOPTST
mdefine_line|#define SCIOCLOOPTST&t;0x10&t;/* Perform loopback test */
r_typedef
r_struct
(brace
DECL|member|device
r_int
id|device
suffix:semicolon
DECL|member|channel
r_int
id|channel
suffix:semicolon
DECL|member|command
r_int
r_int
id|command
suffix:semicolon
DECL|member|dataptr
r_void
op_star
id|dataptr
suffix:semicolon
DECL|typedef|scs_ioctl
)brace
id|scs_ioctl
suffix:semicolon
multiline_comment|/* Size of strings */
DECL|macro|SCIOC_SPIDSIZE
mdefine_line|#define SCIOC_SPIDSIZE&t;&t;49
DECL|macro|SCIOC_DNSIZE
mdefine_line|#define SCIOC_DNSIZE&t;&t;SCIOC_SPIDSIZE
DECL|macro|SCIOC_REVSIZE
mdefine_line|#define SCIOC_REVSIZE&t;&t;SCIOC_SPIDSIZE
DECL|macro|SCIOC_SRECSIZE
mdefine_line|#define SCIOC_SRECSIZE&t;&t;49
r_typedef
r_struct
(brace
DECL|member|tx_good
r_int
r_int
id|tx_good
suffix:semicolon
DECL|member|tx_bad
r_int
r_int
id|tx_bad
suffix:semicolon
DECL|member|rx_good
r_int
r_int
id|rx_good
suffix:semicolon
DECL|member|rx_bad
r_int
r_int
id|rx_bad
suffix:semicolon
DECL|typedef|ChLinkStats
)brace
id|ChLinkStats
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|spid
r_char
id|spid
(braket
l_int|49
)braket
suffix:semicolon
DECL|member|dn
r_char
id|dn
(braket
l_int|49
)braket
suffix:semicolon
DECL|member|call_type
r_char
id|call_type
suffix:semicolon
DECL|member|phy_stat
r_char
id|phy_stat
suffix:semicolon
DECL|member|link_stats
id|ChLinkStats
id|link_stats
suffix:semicolon
DECL|typedef|BRIStat
)brace
id|BRIStat
suffix:semicolon
DECL|typedef|POTStat
r_typedef
id|BRIStat
id|POTStat
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|call_type
r_char
id|call_type
suffix:semicolon
DECL|member|call_state
r_char
id|call_state
suffix:semicolon
DECL|member|serv_state
r_char
id|serv_state
suffix:semicolon
DECL|member|phy_stat
r_char
id|phy_stat
suffix:semicolon
DECL|member|link_stats
id|ChLinkStats
id|link_stats
suffix:semicolon
DECL|typedef|PRIStat
)brace
id|PRIStat
suffix:semicolon
DECL|typedef|PRIInfo
r_typedef
r_char
id|PRIInfo
suffix:semicolon
DECL|typedef|BRIInfo
r_typedef
r_char
id|BRIInfo
suffix:semicolon
DECL|typedef|POTInfo
r_typedef
r_char
id|POTInfo
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|acfa_nos
r_char
id|acfa_nos
suffix:semicolon
DECL|member|acfa_ais
r_char
id|acfa_ais
suffix:semicolon
DECL|member|acfa_los
r_char
id|acfa_los
suffix:semicolon
DECL|member|acfa_rra
r_char
id|acfa_rra
suffix:semicolon
DECL|member|acfa_slpp
r_char
id|acfa_slpp
suffix:semicolon
DECL|member|acfa_slpn
r_char
id|acfa_slpn
suffix:semicolon
DECL|member|acfa_fsrf
r_char
id|acfa_fsrf
suffix:semicolon
DECL|typedef|ACFAStat
)brace
id|ACFAStat
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|modelid
r_int
r_char
id|modelid
suffix:semicolon
DECL|member|serial_no
r_char
id|serial_no
(braket
l_int|13
)braket
suffix:semicolon
DECL|member|part_no
r_char
id|part_no
(braket
l_int|13
)braket
suffix:semicolon
DECL|member|load_ver
r_char
id|load_ver
(braket
l_int|11
)braket
suffix:semicolon
DECL|member|proc_ver
r_char
id|proc_ver
(braket
l_int|11
)braket
suffix:semicolon
DECL|member|iobase
r_int
id|iobase
suffix:semicolon
DECL|member|rambase
r_int
id|rambase
suffix:semicolon
DECL|member|irq
r_char
id|irq
suffix:semicolon
DECL|member|ramsize
r_int
id|ramsize
suffix:semicolon
DECL|member|interface
r_char
id|interface
suffix:semicolon
DECL|member|switch_type
r_char
id|switch_type
suffix:semicolon
DECL|member|l1_status
r_char
id|l1_status
suffix:semicolon
DECL|member|l2_status
r_char
id|l2_status
suffix:semicolon
DECL|member|dch_stats
id|ChLinkStats
id|dch_stats
suffix:semicolon
DECL|member|AcfaStats
id|ACFAStat
id|AcfaStats
suffix:semicolon
r_union
(brace
DECL|member|pristats
id|PRIStat
id|pristats
(braket
l_int|23
)braket
suffix:semicolon
DECL|member|bristats
id|BRIStat
id|bristats
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|potsstats
id|POTStat
id|potsstats
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|status
)brace
id|status
suffix:semicolon
r_union
(brace
DECL|member|priinfo
id|PRIInfo
id|priinfo
suffix:semicolon
DECL|member|briinfo
id|BRIInfo
id|briinfo
suffix:semicolon
DECL|member|potsinfo
id|POTInfo
id|potsinfo
suffix:semicolon
DECL|member|info
)brace
id|info
suffix:semicolon
DECL|typedef|boardInfo
)brace
id|boardInfo
suffix:semicolon
eof
