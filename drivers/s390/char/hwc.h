multiline_comment|/*&n; *  drivers/s390/char/hwc.h&n; *&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Peschke &lt;peschke@fh-brandenburg.de&gt;&n; *&n; *&n; *&n; */
macro_line|#ifndef __HWC_H__
DECL|macro|__HWC_H__
mdefine_line|#define __HWC_H__
DECL|macro|ET_OpCmd
mdefine_line|#define ET_OpCmd&t;&t;0x01
DECL|macro|ET_Msg
mdefine_line|#define ET_Msg&t;&t;0x02
DECL|macro|ET_StateChange
mdefine_line|#define ET_StateChange&t;0x08
DECL|macro|ET_PMsgCmd
mdefine_line|#define ET_PMsgCmd&t;&t;0x09
DECL|macro|ET_CntlProgOpCmd
mdefine_line|#define ET_CntlProgOpCmd&t;0x20
DECL|macro|ET_OpCmd_Mask
mdefine_line|#define ET_OpCmd_Mask&t;0x80000000
DECL|macro|ET_Msg_Mask
mdefine_line|#define ET_Msg_Mask&t;&t;0x40000000
DECL|macro|ET_StateChange_Mask
mdefine_line|#define ET_StateChange_Mask&t;0x01000000
DECL|macro|ET_PMsgCmd_Mask
mdefine_line|#define ET_PMsgCmd_Mask&t;0x00800000
DECL|macro|ET_CtlProgOpCmd_Mask
mdefine_line|#define ET_CtlProgOpCmd_Mask&t;0x00000001
DECL|macro|GMF_DOM
mdefine_line|#define GMF_DOM&t;&t;0x8000
DECL|macro|GMF_SndAlrm
mdefine_line|#define GMF_SndAlrm&t;0x4000
DECL|macro|GMF_HoldMsg
mdefine_line|#define GMF_HoldMsg&t;0x2000
DECL|macro|LTF_CntlText
mdefine_line|#define LTF_CntlText&t;0x8000
DECL|macro|LTF_LabelText
mdefine_line|#define LTF_LabelText&t;0x4000
DECL|macro|LTF_DataText
mdefine_line|#define LTF_DataText&t;0x2000
DECL|macro|LTF_EndText
mdefine_line|#define LTF_EndText&t;0x1000
DECL|macro|LTF_PromptText
mdefine_line|#define LTF_PromptText&t;0x0800
DECL|macro|HWC_COMMAND_INITIATED
mdefine_line|#define HWC_COMMAND_INITIATED&t;0
DECL|macro|HWC_BUSY
mdefine_line|#define HWC_BUSY&t;&t;2
DECL|macro|HWC_NOT_OPERATIONAL
mdefine_line|#define HWC_NOT_OPERATIONAL&t;3
DECL|macro|HWC_CMDW_READDATA
mdefine_line|#define HWC_CMDW_READDATA 0x00770005
DECL|macro|HWC_CMDW_WRITEDATA
mdefine_line|#define HWC_CMDW_WRITEDATA 0x00760005
DECL|macro|HWC_CMDW_WRITEMASK
mdefine_line|#define HWC_CMDW_WRITEMASK 0x00780005
DECL|macro|GDS_ID_MDSMU
mdefine_line|#define GDS_ID_MDSMU&t;&t;0x1310
DECL|macro|GDS_ID_MDSRouteInfo
mdefine_line|#define GDS_ID_MDSRouteInfo&t;0x1311
DECL|macro|GDS_ID_AgUnWrkCorr
mdefine_line|#define GDS_ID_AgUnWrkCorr&t;0x1549
DECL|macro|GDS_ID_SNACondReport
mdefine_line|#define GDS_ID_SNACondReport&t;0x1532
DECL|macro|GDS_ID_CPMSU
mdefine_line|#define GDS_ID_CPMSU&t;&t;0x1212
DECL|macro|GDS_ID_RoutTargInstr
mdefine_line|#define GDS_ID_RoutTargInstr&t;0x154D
DECL|macro|GDS_ID_OpReq
mdefine_line|#define GDS_ID_OpReq&t;&t;0x8070
DECL|macro|GDS_ID_TextCmd
mdefine_line|#define GDS_ID_TextCmd&t;&t;0x1320
DECL|macro|GDS_KEY_SelfDefTextMsg
mdefine_line|#define GDS_KEY_SelfDefTextMsg&t;0x31
DECL|macro|_HWCB_HEADER
mdefine_line|#define _HWCB_HEADER&t;u16&t;length; &bslash;&n;&t;&t;&t;u8&t;function_code; &bslash;&n;&t;&t;&t;u8&t;control_mask[3]; &bslash;&n;&t;&t;&t;u16&t;response_code;
DECL|macro|_EBUF_HEADER
mdefine_line|#define _EBUF_HEADER &t;u16&t;length; &bslash;&n;&t;&t;&t;u8&t;type; &bslash;&n;&t;&t;&t;u8&t;flags; &bslash;&n;&t;&t;&t;u16&t;_reserved;
r_typedef
r_struct
(brace
id|_EBUF_HEADER
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
DECL|typedef|evbuf_t
id|evbuf_t
suffix:semicolon
DECL|macro|_MDB_HEADER
mdefine_line|#define _MDB_HEADER&t;u16&t;length; &bslash;&n;&t;&t;&t;u16&t;type; &bslash;&n;&t;&t;&t;u32&t;tag; &bslash;&n;&t;&t;&t;u32&t;revision_code;
DECL|macro|_GO_HEADER
mdefine_line|#define _GO_HEADER&t;u16&t;length; &bslash;&n;&t;&t;&t;u16&t;type; &bslash;&n;&t;&t;&t;u32&t;domid; &bslash;&n;&t;&t;&t;u8&t;hhmmss_time[8]; &bslash;&n;&t;&t;&t;u8&t;th_time[3]; &bslash;&n;&t;&t;&t;u8&t;_reserved_0; &bslash;&n;&t;&t;&t;u8&t;dddyyyy_date[7]; &bslash;&n;&t;&t;&t;u8&t;_reserved_1; &bslash;&n;&t;&t;&t;u16&t;general_msg_flags; &bslash;&n;&t;&t;&t;u8&t;_reserved_2[10]; &bslash;&n;&t;&t;&t;u8&t;originating_system_name[8]; &bslash;&n;&t;&t;&t;u8&t;job_guest_name[8];
DECL|macro|_MTO_HEADER
mdefine_line|#define _MTO_HEADER&t;u16&t;length; &bslash;&n;&t;&t;&t;u16&t;type; &bslash;&n;&t;&t;&t;u16&t;line_type_flags; &bslash;&n;&t;&t;&t;u8&t;alarm_control; &bslash;&n;&t;&t;&t;u8&t;_reserved[3];
r_typedef
r_struct
(brace
id|_GO_HEADER
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
DECL|typedef|go_t
id|go_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|go
id|go_t
id|go
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
DECL|typedef|mdb_body_t
id|mdb_body_t
suffix:semicolon
r_typedef
r_struct
(brace
id|_MDB_HEADER
DECL|member|mdb_body
id|mdb_body_t
id|mdb_body
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
DECL|typedef|mdb_t
id|mdb_t
suffix:semicolon
r_typedef
r_struct
(brace
id|_EBUF_HEADER
DECL|member|mdb
id|mdb_t
id|mdb
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
DECL|typedef|msgbuf_t
id|msgbuf_t
suffix:semicolon
r_typedef
r_struct
(brace
id|_HWCB_HEADER
DECL|member|msgbuf
id|msgbuf_t
id|msgbuf
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
DECL|typedef|write_hwcb_t
id|write_hwcb_t
suffix:semicolon
r_typedef
r_struct
(brace
id|_MTO_HEADER
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
DECL|typedef|mto_t
id|mto_t
suffix:semicolon
DECL|variable|write_hwcb_template
r_static
id|write_hwcb_t
id|write_hwcb_template
op_assign
(brace
r_sizeof
(paren
id|write_hwcb_t
)paren
comma
l_int|0x00
comma
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
l_int|0x0000
comma
(brace
r_sizeof
(paren
id|msgbuf_t
)paren
comma
id|ET_Msg
comma
l_int|0x00
comma
l_int|0x0000
comma
(brace
r_sizeof
(paren
id|mdb_t
)paren
comma
l_int|0x0001
comma
l_int|0xD4C4C240
comma
l_int|0x00000001
comma
(brace
(brace
r_sizeof
(paren
id|go_t
)paren
comma
l_int|0x0001
)brace
)brace
)brace
)brace
)brace
suffix:semicolon
DECL|variable|mto_template
r_static
id|mto_t
id|mto_template
op_assign
(brace
r_sizeof
(paren
id|mto_t
)paren
comma
l_int|0x0004
comma
id|LTF_EndText
comma
l_int|0x00
)brace
suffix:semicolon
DECL|typedef|_hwcb_mask_t
r_typedef
id|u32
id|_hwcb_mask_t
suffix:semicolon
r_typedef
r_struct
(brace
id|_HWCB_HEADER
DECL|member|_reserved
id|u16
id|_reserved
suffix:semicolon
DECL|member|mask_length
id|u16
id|mask_length
suffix:semicolon
DECL|member|cp_receive_mask
id|_hwcb_mask_t
id|cp_receive_mask
suffix:semicolon
DECL|member|cp_send_mask
id|_hwcb_mask_t
id|cp_send_mask
suffix:semicolon
DECL|member|hwc_receive_mask
id|_hwcb_mask_t
id|hwc_receive_mask
suffix:semicolon
DECL|member|hwc_send_mask
id|_hwcb_mask_t
id|hwc_send_mask
suffix:semicolon
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
DECL|typedef|init_hwcb_t
id|init_hwcb_t
suffix:semicolon
DECL|variable|init_hwcb_template
r_static
id|init_hwcb_t
id|init_hwcb_template
op_assign
(brace
r_sizeof
(paren
id|init_hwcb_t
)paren
comma
l_int|0x00
comma
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
)brace
comma
l_int|0x0000
comma
l_int|0x0000
comma
r_sizeof
(paren
id|_hwcb_mask_t
)paren
comma
id|ET_OpCmd_Mask
op_or
id|ET_PMsgCmd_Mask
comma
id|ET_Msg_Mask
)brace
suffix:semicolon
DECL|macro|_GDS_VECTOR_HEADER
mdefine_line|#define _GDS_VECTOR_HEADER&t;u16&t;length; &bslash;&n;&t;&t;&t;&t;u16&t;gds_id;
DECL|macro|_GDS_SUBVECTOR_HEADER
mdefine_line|#define _GDS_SUBVECTOR_HEADER&t;u8&t;length; &bslash;&n;&t;&t;&t;&t;u8&t;key;
r_typedef
r_struct
(brace
id|_GDS_VECTOR_HEADER
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
DECL|typedef|gds_vector_t
id|gds_vector_t
suffix:semicolon
r_typedef
r_struct
(brace
id|_GDS_SUBVECTOR_HEADER
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
DECL|typedef|gds_subvector_t
id|gds_subvector_t
suffix:semicolon
r_typedef
r_struct
(brace
id|_HWCB_HEADER
)brace
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
DECL|typedef|read_hwcb_t
id|read_hwcb_t
suffix:semicolon
DECL|variable|read_hwcb_template
r_static
id|read_hwcb_t
id|read_hwcb_template
op_assign
(brace
id|PAGE_SIZE
comma
l_int|0x00
comma
(brace
l_int|0x00
comma
l_int|0x00
comma
l_int|0x80
)brace
)brace
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* __HWC_H__ */
eof
