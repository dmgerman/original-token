macro_line|#if&t;defined(CONFIG_WAVELAN)
DECL|macro|WAVELAN_ADDR_SIZE
mdefine_line|#define WAVELAN_ADDR_SIZE&t;6&t;/* Size of a MAC address */
DECL|macro|SA_ADDR0
mdefine_line|#define SA_ADDR0&t;&t;0x08&t;/* First octet of WaveLAN MAC addresses */
DECL|macro|SA_ADDR1
mdefine_line|#define SA_ADDR1&t;&t;0x00&t;/* Second octet of WaveLAN MAC addresses */
DECL|macro|SA_ADDR2
mdefine_line|#define SA_ADDR2&t;&t;0x0E&t;/* Third octet of WaveLAN MAC addresses */
DECL|macro|WAVELAN_MTU
mdefine_line|#define WAVELAN_MTU&t;&t;1500&t;/* Maximum size of WaveLAN packet */
multiline_comment|/*&n; * Parameter Storage Area (PSA).&n; */
DECL|typedef|psa_t
r_typedef
r_struct
id|psa_t
id|psa_t
suffix:semicolon
DECL|struct|psa_t
r_struct
id|psa_t
(brace
DECL|member|psa_io_base_addr_1
r_int
r_char
id|psa_io_base_addr_1
suffix:semicolon
multiline_comment|/* Base address 1 ??? */
DECL|member|psa_io_base_addr_2
r_int
r_char
id|psa_io_base_addr_2
suffix:semicolon
multiline_comment|/* Base address 2 */
DECL|member|psa_io_base_addr_3
r_int
r_char
id|psa_io_base_addr_3
suffix:semicolon
multiline_comment|/* Base address 3 */
DECL|member|psa_io_base_addr_4
r_int
r_char
id|psa_io_base_addr_4
suffix:semicolon
multiline_comment|/* Base address 4 */
DECL|member|psa_rem_boot_addr_1
r_int
r_char
id|psa_rem_boot_addr_1
suffix:semicolon
multiline_comment|/* Remote Boot Address 1 */
DECL|member|psa_rem_boot_addr_2
r_int
r_char
id|psa_rem_boot_addr_2
suffix:semicolon
multiline_comment|/* Remote Boot Address 2 */
DECL|member|psa_rem_boot_addr_3
r_int
r_char
id|psa_rem_boot_addr_3
suffix:semicolon
multiline_comment|/* Remote Boot Address 3 */
DECL|member|psa_holi_params
r_int
r_char
id|psa_holi_params
suffix:semicolon
multiline_comment|/* HOst Lan Interface (HOLI) Parameters */
DECL|member|psa_int_req_no
r_int
r_char
id|psa_int_req_no
suffix:semicolon
multiline_comment|/* Interrupt Request Line */
DECL|member|psa_unused0
r_int
r_char
id|psa_unused0
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|psa_univ_mac_addr
r_int
r_char
id|psa_univ_mac_addr
(braket
id|WAVELAN_ADDR_SIZE
)braket
suffix:semicolon
multiline_comment|/* Universal (factory) MAC Address */
DECL|member|psa_local_mac_addr
r_int
r_char
id|psa_local_mac_addr
(braket
id|WAVELAN_ADDR_SIZE
)braket
suffix:semicolon
multiline_comment|/* Local MAC Address */
DECL|member|psa_univ_local_sel
r_int
r_char
id|psa_univ_local_sel
suffix:semicolon
multiline_comment|/* Universal Local Selection */
DECL|macro|PSA_UNIVERSAL
mdefine_line|#define&t;&t;PSA_UNIVERSAL&t;0&t;&t;/* Universal (factory) */
DECL|macro|PSA_LOCAL
mdefine_line|#define&t;&t;PSA_LOCAL&t;1&t;&t;/* Local */
DECL|member|psa_comp_number
r_int
r_char
id|psa_comp_number
suffix:semicolon
multiline_comment|/* Compatibility Number: */
DECL|macro|PSA_COMP_PC_AT_915
mdefine_line|#define&t;&t;PSA_COMP_PC_AT_915&t;0 &t;/* PC-AT 915 MHz&t;*/
DECL|macro|PSA_COMP_PC_MC_915
mdefine_line|#define&t;&t;PSA_COMP_PC_MC_915&t;1 &t;/* PC-MC 915 MHz&t;*/
DECL|macro|PSA_COMP_PC_AT_2400
mdefine_line|#define&t;&t;PSA_COMP_PC_AT_2400&t;2 &t;/* PC-AT 2.4 GHz&t;*/
DECL|macro|PSA_COMP_PC_MC_2400
mdefine_line|#define&t;&t;PSA_COMP_PC_MC_2400&t;3 &t;/* PC-MC 2.4 GHz&t;*/
DECL|macro|PSA_COMP_PCMCIA_915
mdefine_line|#define&t;&t;PSA_COMP_PCMCIA_915&t;4 &t;/* PCMCIA 915 MHz&t;*/
DECL|member|psa_thr_pre_set
r_int
r_char
id|psa_thr_pre_set
suffix:semicolon
multiline_comment|/* Modem Threshold Preset */
DECL|member|psa_feature_select
r_int
r_char
id|psa_feature_select
suffix:semicolon
multiline_comment|/* ??? */
macro_line|#if&t;0
template_param
r_int
r_char
id|psa_decay_prm
suffix:semicolon
multiline_comment|/* Modem Decay */
macro_line|#endif&t;/* 0 */
DECL|member|psa_subband
r_int
r_char
id|psa_subband
suffix:semicolon
multiline_comment|/* Subband&t;*/
DECL|macro|PSA_SUBBAND_915
mdefine_line|#define&t;&t;PSA_SUBBAND_915&t;&t;0&t;/* 915 MHz&t;*/
DECL|macro|PSA_SUBBAND_2425
mdefine_line|#define&t;&t;PSA_SUBBAND_2425&t;1&t;/* 2425 MHz&t;*/
DECL|macro|PSA_SUBBAND_2460
mdefine_line|#define&t;&t;PSA_SUBBAND_2460&t;2&t;/* 2460 MHz&t;*/
DECL|macro|PSA_SUBBAND_2484
mdefine_line|#define&t;&t;PSA_SUBBAND_2484&t;3&t;/* 2484 MHz&t;*/
DECL|macro|PSA_SUBBAND_2430_5
mdefine_line|#define&t;&t;PSA_SUBBAND_2430_5&t;4&t;/* 2430.5 MHz&t;*/
macro_line|#if&t;0
template_param
r_int
r_char
id|psa_decay_updat_prm
suffix:semicolon
multiline_comment|/* Modem Decay Update ??? */
macro_line|#endif&t;/* 0 */
DECL|member|psa_quality_thr
r_int
r_char
id|psa_quality_thr
suffix:semicolon
multiline_comment|/* Modem Quality Threshold */
DECL|member|psa_mod_delay
r_int
r_char
id|psa_mod_delay
suffix:semicolon
multiline_comment|/* Modem Delay ??? */
DECL|member|psa_nwid
r_int
r_char
id|psa_nwid
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Network ID */
DECL|member|psa_undefined
r_int
r_char
id|psa_undefined
suffix:semicolon
multiline_comment|/* undefined */
DECL|member|psa_encryption_select
r_int
r_char
id|psa_encryption_select
suffix:semicolon
multiline_comment|/* Encryption On Off */
DECL|member|psa_encryption_key
r_int
r_char
id|psa_encryption_key
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Encryption Key */
DECL|member|psa_databus_width
r_int
r_char
id|psa_databus_width
suffix:semicolon
multiline_comment|/* 8/16 bit bus width */
DECL|member|psa_call_code
r_int
r_char
id|psa_call_code
suffix:semicolon
multiline_comment|/* ??? */
macro_line|#if&t;0
template_param
r_int
r_char
id|psa_auto_squelch
suffix:semicolon
multiline_comment|/* Automatic Squelch level On off ??? */
macro_line|#endif&t;/* 0 */
DECL|member|psa_no_of_retries
r_int
r_char
id|psa_no_of_retries
suffix:semicolon
multiline_comment|/* LAN Cont. No of retries */
DECL|member|psa_acr
r_int
r_char
id|psa_acr
suffix:semicolon
multiline_comment|/* LAN Cont. ACR */
DECL|member|psa_dump_count
r_int
r_char
id|psa_dump_count
suffix:semicolon
multiline_comment|/* number of Dump Commands in TFB */
DECL|member|psa_unused1
r_int
r_char
id|psa_unused1
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|psa_nwid_prefix
r_int
r_char
id|psa_nwid_prefix
suffix:semicolon
multiline_comment|/* ??? */
DECL|member|psa_unused2
r_int
r_char
id|psa_unused2
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|psa_conf_status
r_int
r_char
id|psa_conf_status
suffix:semicolon
multiline_comment|/* Card Configuration Status */
DECL|member|psa_crc
r_int
r_char
id|psa_crc
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* CRC over PSA */
DECL|member|psa_crc_status
r_int
r_char
id|psa_crc_status
suffix:semicolon
multiline_comment|/* CRC Valid Flag */
)brace
suffix:semicolon
macro_line|#if&t;STRUCT_CHECK == 1
DECL|macro|PSA_SIZE
mdefine_line|#define&t;PSA_SIZE&t;64
macro_line|#endif&t;/* STRUCT_CHECK == 1 */
multiline_comment|/*&n; * Modem Management Controller (MMC) write structure.&n; */
DECL|typedef|mmw_t
r_typedef
r_struct
id|mmw_t
id|mmw_t
suffix:semicolon
DECL|struct|mmw_t
r_struct
id|mmw_t
(brace
DECL|member|mmw_encr_key
r_int
r_char
id|mmw_encr_key
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* encryption key */
DECL|member|mmw_encr_enable
r_int
r_char
id|mmw_encr_enable
suffix:semicolon
multiline_comment|/* enable/disable encryption */
DECL|member|mmw_unused0
r_int
r_char
id|mmw_unused0
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|mmw_des_io_invert
r_int
r_char
id|mmw_des_io_invert
suffix:semicolon
multiline_comment|/* ??? */
DECL|member|mmw_unused1
r_int
r_char
id|mmw_unused1
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|mmw_loopt_sel
r_int
r_char
id|mmw_loopt_sel
suffix:semicolon
multiline_comment|/* looptest selection */
DECL|macro|MMW_LOOPT_SEL_UNDEFINED
mdefine_line|#define&t;&t;MMW_LOOPT_SEL_UNDEFINED&t;0x40&t;/* undefined */
DECL|macro|MMW_LOOPT_SEL_INT
mdefine_line|#define&t;&t;MMW_LOOPT_SEL_INT&t;0x20&t;/* activate Attention Request */
DECL|macro|MMW_LOOPT_SEL_LS
mdefine_line|#define&t;&t;MMW_LOOPT_SEL_LS&t;0x10&t;/* looptest without collision avoidance */
DECL|macro|MMW_LOOPT_SEL_LT3A
mdefine_line|#define&t;&t;MMW_LOOPT_SEL_LT3A&t;0x08&t;/* looptest 3a */
DECL|macro|MMW_LOOPT_SEL_LT3B
mdefine_line|#define&t;&t;MMW_LOOPT_SEL_LT3B&t;0x04&t;/* looptest 3b */
DECL|macro|MMW_LOOPT_SEL_LT3C
mdefine_line|#define&t;&t;MMW_LOOPT_SEL_LT3C&t;0x02&t;/* looptest 3c */
DECL|macro|MMW_LOOPT_SEL_LT3D
mdefine_line|#define&t;&t;MMW_LOOPT_SEL_LT3D&t;0x01&t;/* looptest 3d */
DECL|member|mmw_jabber_enable
r_int
r_char
id|mmw_jabber_enable
suffix:semicolon
multiline_comment|/* jabber timer enable */
DECL|member|mmw_freeze
r_int
r_char
id|mmw_freeze
suffix:semicolon
multiline_comment|/* freeze / unfreeze signal level */
DECL|member|mmw_anten_sel
r_int
r_char
id|mmw_anten_sel
suffix:semicolon
multiline_comment|/* antenna selection */
DECL|macro|MMW_ANTEN_SEL_SEL
mdefine_line|#define&t;&t;MMW_ANTEN_SEL_SEL&t;0x01&t;/* direct antenna selection */
DECL|macro|MMW_ANTEN_SEL_ALG_EN
mdefine_line|#define&t;&t;MMW_ANTEN_SEL_ALG_EN&t;0x02&t;/* antenna selection algorithm enable */
DECL|member|mmw_ifs
r_int
r_char
id|mmw_ifs
suffix:semicolon
multiline_comment|/* inter frame spacing */
DECL|member|mmw_mod_delay
r_int
r_char
id|mmw_mod_delay
suffix:semicolon
multiline_comment|/* modem delay */
DECL|member|mmw_jam_time
r_int
r_char
id|mmw_jam_time
suffix:semicolon
multiline_comment|/* jamming time */
DECL|member|mmw_unused2
r_int
r_char
id|mmw_unused2
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|mmw_thr_pre_set
r_int
r_char
id|mmw_thr_pre_set
suffix:semicolon
multiline_comment|/* level threshold preset */
DECL|member|mmw_decay_prm
r_int
r_char
id|mmw_decay_prm
suffix:semicolon
multiline_comment|/* decay parameters */
DECL|member|mmw_decay_updat_prm
r_int
r_char
id|mmw_decay_updat_prm
suffix:semicolon
multiline_comment|/* decay update parameters */
DECL|member|mmw_quality_thr
r_int
r_char
id|mmw_quality_thr
suffix:semicolon
multiline_comment|/* quality (z-quotient) threshold */
DECL|member|mmw_netw_id_l
r_int
r_char
id|mmw_netw_id_l
suffix:semicolon
multiline_comment|/* NWID low order byte */
DECL|member|mmw_netw_id_h
r_int
r_char
id|mmw_netw_id_h
suffix:semicolon
multiline_comment|/* NWID high order byte */
)brace
suffix:semicolon
macro_line|#if&t;STRUCT_CHECK == 1
DECL|macro|MMW_SIZE
mdefine_line|#define&t;MMW_SIZE&t;30
macro_line|#endif&t;/* STRUCT_CHECK == 1 */
DECL|macro|mmwoff
mdefine_line|#define&t;mmwoff(p,f) &t;(unsigned short)((void *)(&amp;((mmw_t *)((void *)0 + (p)))-&gt;f) - (void *)0)
multiline_comment|/*&n; * Modem Management Controller (MMC) read structure.&n; */
DECL|typedef|mmr_t
r_typedef
r_struct
id|mmr_t
id|mmr_t
suffix:semicolon
DECL|struct|mmr_t
r_struct
id|mmr_t
(brace
DECL|member|mmr_unused0
r_int
r_char
id|mmr_unused0
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|mmr_des_status
r_int
r_char
id|mmr_des_status
suffix:semicolon
multiline_comment|/* encryption status */
DECL|member|mmr_des_avail
r_int
r_char
id|mmr_des_avail
suffix:semicolon
multiline_comment|/* encryption available (0x55 read) */
DECL|member|mmr_des_io_invert
r_int
r_char
id|mmr_des_io_invert
suffix:semicolon
multiline_comment|/* des I/O invert register */
DECL|member|mmr_unused1
r_int
r_char
id|mmr_unused1
(braket
l_int|5
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|mmr_dce_status
r_int
r_char
id|mmr_dce_status
suffix:semicolon
multiline_comment|/* DCE status */
DECL|macro|MMR_DCE_STATUS_ENERG_DET
mdefine_line|#define&t;&t;MMR_DCE_STATUS_ENERG_DET&t;0x01&t;/* energy detected */
DECL|macro|MMR_DCE_STATUS_LOOPT_IND
mdefine_line|#define&t;&t;MMR_DCE_STATUS_LOOPT_IND&t;0x02&t;/* loop test indicated */
DECL|macro|MMR_DCE_STATUS_XMTITR_IND
mdefine_line|#define&t;&t;MMR_DCE_STATUS_XMTITR_IND&t;0x04&t;/* transmitter on */
DECL|macro|MMR_DCE_STATUS_JBR_EXPIRED
mdefine_line|#define&t;&t;MMR_DCE_STATUS_JBR_EXPIRED&t;0x08&t;/* jabber timer expired */
DECL|member|mmr_unused2
r_int
r_char
id|mmr_unused2
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* unused */
DECL|member|mmr_correct_nwid_l
r_int
r_char
id|mmr_correct_nwid_l
suffix:semicolon
multiline_comment|/* no. of correct NWID&squot;s rxd (low) */
DECL|member|mmr_correct_nwid_h
r_int
r_char
id|mmr_correct_nwid_h
suffix:semicolon
multiline_comment|/* no. of correct NWID&squot;s rxd (high) */
DECL|member|mmr_wrong_nwid_l
r_int
r_char
id|mmr_wrong_nwid_l
suffix:semicolon
multiline_comment|/* count of wrong NWID&squot;s received (low) */
DECL|member|mmr_wrong_nwid_h
r_int
r_char
id|mmr_wrong_nwid_h
suffix:semicolon
multiline_comment|/* count of wrong NWID&squot;s received (high) */
DECL|member|mmr_thr_pre_set
r_int
r_char
id|mmr_thr_pre_set
suffix:semicolon
multiline_comment|/* level threshold preset */
DECL|member|mmr_signal_lvl
r_int
r_char
id|mmr_signal_lvl
suffix:semicolon
multiline_comment|/* signal level */
DECL|member|mmr_silence_lvl
r_int
r_char
id|mmr_silence_lvl
suffix:semicolon
multiline_comment|/* silence level */
DECL|member|mmr_sgnl_qual
r_int
r_char
id|mmr_sgnl_qual
suffix:semicolon
multiline_comment|/* signal quality */
DECL|macro|MMR_SGNL_QUAL_0
mdefine_line|#define&t;&t;MMR_SGNL_QUAL_0&t;&t;0x01&t;/* signal quality 0 */
DECL|macro|MMR_SGNL_QUAL_1
mdefine_line|#define&t;&t;MMR_SGNL_QUAL_1&t;&t;0x02&t;/* signal quality 1 */
DECL|macro|MMR_SGNL_QUAL_2
mdefine_line|#define&t;&t;MMR_SGNL_QUAL_2&t;&t;0x04&t;/* signal quality 2 */
DECL|macro|MMR_SGNL_QUAL_3
mdefine_line|#define&t;&t;MMR_SGNL_QUAL_3&t;&t;0x08&t;/* signal quality 3 */
DECL|macro|MMR_SGNL_QUAL_S_A
mdefine_line|#define&t;&t;MMR_SGNL_QUAL_S_A&t;0x80&t;/* currently selected antenna */
DECL|member|mmr_netw_id_l
r_int
r_char
id|mmr_netw_id_l
suffix:semicolon
multiline_comment|/* NWID low order byte ??? */
DECL|member|mmr_unused3
r_int
r_char
id|mmr_unused3
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* unused */
)brace
suffix:semicolon
macro_line|#if&t;STRUCT_CHECK == 1
DECL|macro|MMR_SIZE
mdefine_line|#define&t;MMR_SIZE&t;30
macro_line|#endif&t;/* STRUCT_CHECK == 1 */
DECL|macro|MMR_LEVEL_MASK
mdefine_line|#define&t;MMR_LEVEL_MASK&t;0x3F
DECL|macro|mmroff
mdefine_line|#define&t;mmroff(p,f) &t;(unsigned short)((void *)(&amp;((mmr_t *)((void *)0 + (p)))-&gt;f) - (void *)0)
multiline_comment|/*&n; * Host Adaptor structure.&n; * (base is board port address).&n; */
DECL|typedef|hacs_u
r_typedef
r_union
id|hacs_u
id|hacs_u
suffix:semicolon
DECL|union|hacs_u
r_union
id|hacs_u
(brace
DECL|member|hu_command
r_int
r_int
id|hu_command
suffix:semicolon
multiline_comment|/* Command register */
DECL|macro|HACR_RESET
mdefine_line|#define&t;&t;HACR_RESET&t;&t;0x0001&t;/* Reset board */
DECL|macro|HACR_CA
mdefine_line|#define&t;&t;HACR_CA&t;&t;&t;0x0002&t;/* Set Channel Attention for 82586 */
DECL|macro|HACR_16BITS
mdefine_line|#define&t;&t;HACR_16BITS&t;&t;0x0004&t;/* 16 bits operation (0 =&gt; 8bits) */
DECL|macro|HACR_OUT0
mdefine_line|#define&t;&t;HACR_OUT0&t;&t;0x0008&t;/* General purpose output pin 0 */
multiline_comment|/* not used - must be 1 */
DECL|macro|HACR_OUT1
mdefine_line|#define&t;&t;HACR_OUT1&t;&t;0x0010&t;/* General purpose output pin 1 */
multiline_comment|/* not used - must be 1 */
DECL|macro|HACR_82586_INT_ENABLE
mdefine_line|#define&t;&t;HACR_82586_INT_ENABLE&t;0x0020&t;/* Enable 82586 interrupts */
DECL|macro|HACR_MMC_INT_ENABLE
mdefine_line|#define&t;&t;HACR_MMC_INT_ENABLE&t;0x0040&t;/* Enable MMC interrupts */
DECL|macro|HACR_INTR_CLR_ENABLE
mdefine_line|#define&t;&t;HACR_INTR_CLR_ENABLE&t;0x0080&t;/* Enable interrupt status read/clear */
DECL|member|hu_status
r_int
r_int
id|hu_status
suffix:semicolon
multiline_comment|/* Status Register */
DECL|macro|HASR_82586_INTR
mdefine_line|#define&t;&t;HASR_82586_INTR&t;&t;0x0001&t;/* Interrupt request from 82586 */
DECL|macro|HASR_MMC_INTR
mdefine_line|#define&t;&t;HASR_MMC_INTR&t;&t;0x0002&t;/* Interrupt request from MMC */
DECL|macro|HASR_MMC_BUSY
mdefine_line|#define&t;&t;HASR_MMC_BUSY&t;&t;0x0004&t;/* MMC busy indication */
DECL|macro|HASR_PSA_BUSY
mdefine_line|#define&t;&t;HASR_PSA_BUSY&t;&t;0x0008&t;/* LAN parameter storage area busy */
)brace
suffix:semicolon
DECL|typedef|ha_t
r_typedef
r_struct
id|ha_t
id|ha_t
suffix:semicolon
DECL|struct|ha_t
r_struct
id|ha_t
(brace
DECL|member|ha_cs
id|hacs_u
id|ha_cs
suffix:semicolon
multiline_comment|/* Command and status registers */
DECL|macro|ha_command
mdefine_line|#define &t;&t;ha_command&t;ha_cs.hu_command
DECL|macro|ha_status
mdefine_line|#define &t;&t;ha_status&t;ha_cs.hu_status
DECL|member|ha_mmcr
r_int
r_int
id|ha_mmcr
suffix:semicolon
multiline_comment|/* Modem Management Ctrl Register */
DECL|member|ha_pior0
r_int
r_int
id|ha_pior0
suffix:semicolon
multiline_comment|/* Program I/O Address Register Port 0 */
DECL|member|ha_piop0
r_int
r_int
id|ha_piop0
suffix:semicolon
multiline_comment|/* Program I/O Port 0 */
DECL|member|ha_pior1
r_int
r_int
id|ha_pior1
suffix:semicolon
multiline_comment|/* Program I/O Address Register Port 1 */
DECL|member|ha_piop1
r_int
r_int
id|ha_piop1
suffix:semicolon
multiline_comment|/* Program I/O Port 1 */
DECL|member|ha_pior2
r_int
r_int
id|ha_pior2
suffix:semicolon
multiline_comment|/* Program I/O Address Register Port 2 */
DECL|member|ha_piop2
r_int
r_int
id|ha_piop2
suffix:semicolon
multiline_comment|/* Program I/O Port 2 */
)brace
suffix:semicolon
macro_line|#if&t;STRUCT_CHECK == 1
DECL|macro|HA_SIZE
mdefine_line|#define HA_SIZE&t;&t;16
macro_line|#endif&t;/* STRUCT_CHECK == 1 */
DECL|macro|hoff
mdefine_line|#define&t;hoff(p,f) &t;(unsigned short)((void *)(&amp;((ha_t *)((void *)0 + (p)))-&gt;f) - (void *)0)
DECL|macro|HACR
mdefine_line|#define&t;HACR(p)&t;&t;hoff(p, ha_command)
DECL|macro|HASR
mdefine_line|#define&t;HASR(p)&t;&t;hoff(p, ha_status)
DECL|macro|MMCR
mdefine_line|#define&t;MMCR(p)&t;&t;hoff(p, ha_mmcr)
DECL|macro|PIOR0
mdefine_line|#define&t;PIOR0(p)&t;hoff(p, ha_pior0)
DECL|macro|PIOP0
mdefine_line|#define&t;PIOP0(p)&t;hoff(p, ha_piop0)
DECL|macro|PIOR1
mdefine_line|#define&t;PIOR1(p)&t;hoff(p, ha_pior1)
DECL|macro|PIOP1
mdefine_line|#define&t;PIOP1(p)&t;hoff(p, ha_piop1)
DECL|macro|PIOR2
mdefine_line|#define&t;PIOR2(p)&t;hoff(p, ha_pior2)
DECL|macro|PIOP2
mdefine_line|#define&t;PIOP2(p)&t;hoff(p, ha_piop2)
multiline_comment|/*&n; * Program I/O Mode Register values.&n; */
DECL|macro|STATIC_PIO
mdefine_line|#define STATIC_PIO&t;&t;0&t;/* Mode 1: static mode */
multiline_comment|/* RAM access ??? */
DECL|macro|AUTOINCR_PIO
mdefine_line|#define AUTOINCR_PIO&t;&t;1&t;/* Mode 2: auto increment mode */
multiline_comment|/* RAM access ??? */
DECL|macro|AUTODECR_PIO
mdefine_line|#define AUTODECR_PIO&t;&t;2&t;/* Mode 3: auto decrement mode */
multiline_comment|/* RAM access ??? */
DECL|macro|PARAM_ACCESS_PIO
mdefine_line|#define PARAM_ACCESS_PIO&t;3&t;/* Mode 4: LAN parameter access mode */
multiline_comment|/* Parameter access. */
DECL|macro|PIO_MASK
mdefine_line|#define PIO_MASK&t;&t;3&t;/* register mask */
DECL|macro|PIOM
mdefine_line|#define PIOM(cmd,piono)&t;&t;((u_short)cmd &lt;&lt; 10 &lt;&lt; (piono * 2))
DECL|macro|HACR_DEFAULT
mdefine_line|#define&t;HACR_DEFAULT&t;&t;(HACR_OUT0 | HACR_OUT1 | HACR_16BITS | PIOM(STATIC_PIO, 0) | PIOM(AUTOINCR_PIO, 1) | PIOM(PARAM_ACCESS_PIO, 2))
DECL|macro|HACR_INTRON
mdefine_line|#define&t;HACR_INTRON&t;&t;(HACR_82586_INT_ENABLE | HACR_MMC_INT_ENABLE | HACR_INTR_CLR_ENABLE)
DECL|macro|MAXDATAZ
mdefine_line|#define&t;MAXDATAZ&t;&t;(WAVELAN_ADDR_SIZE + WAVELAN_ADDR_SIZE + 2 + WAVELAN_MTU)
multiline_comment|/*&n; * Onboard 64k RAM layout.&n; * (Offsets from 0x0000.)&n; */
DECL|macro|OFFSET_RU
mdefine_line|#define OFFSET_RU&t;&t;0x0000
DECL|macro|OFFSET_CU
mdefine_line|#define OFFSET_CU&t;&t;0x8000
DECL|macro|OFFSET_SCB
mdefine_line|#define OFFSET_SCB&t;&t;(OFFSET_ISCP - sizeof(scb_t))
DECL|macro|OFFSET_ISCP
mdefine_line|#define OFFSET_ISCP&t;&t;(OFFSET_SCP - sizeof(iscp_t))
DECL|macro|OFFSET_SCP
mdefine_line|#define OFFSET_SCP&t;&t;I82586_SCP_ADDR
DECL|macro|RXBLOCKZ
mdefine_line|#define&t;RXBLOCKZ&t;&t;(sizeof(fd_t) + sizeof(rbd_t) + MAXDATAZ)
DECL|macro|TXBLOCKZ
mdefine_line|#define&t;TXBLOCKZ&t;&t;(sizeof(ac_tx_t) + sizeof(ac_nop_t) + sizeof(tbd_t) + MAXDATAZ)
DECL|macro|NRXBLOCKS
mdefine_line|#define&t;NRXBLOCKS&t;&t;((OFFSET_CU - OFFSET_RU) / RXBLOCKZ)
DECL|macro|NTXBLOCKS
mdefine_line|#define&t;NTXBLOCKS&t;&t;((OFFSET_SCB - OFFSET_CU) / TXBLOCKZ)
multiline_comment|/*&n; * This software may only be used and distributed&n; * according to the terms of the GNU Public License.&n; *&n; * For more details, see wavelan.c.&n; */
macro_line|#endif&t;/* defined(CONFIG_WAVELAN) */
eof
