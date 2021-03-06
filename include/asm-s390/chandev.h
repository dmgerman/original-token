multiline_comment|/*&n; *  include/asm-s390/chandev.h&n; *&n; *  S390 version&n; *    Copyright (C) 2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)&n; *&n; */
macro_line|#include &lt;asm/types.h&gt;
r_typedef
r_enum
(brace
DECL|enumerator|none
id|none
op_assign
l_int|0
comma
DECL|enumerator|ctc
id|ctc
op_assign
l_int|1
comma
DECL|enumerator|escon
id|escon
op_assign
l_int|2
comma
DECL|enumerator|lcs
id|lcs
op_assign
l_int|4
comma
DECL|enumerator|osad
id|osad
op_assign
l_int|8
comma
DECL|enumerator|claw
id|claw
op_assign
l_int|16
comma
DECL|typedef|chandev_type
)brace
id|chandev_type
suffix:semicolon
DECL|typedef|chandev_model_info
r_typedef
r_struct
id|chandev_model_info
id|chandev_model_info
suffix:semicolon
DECL|struct|chandev_model_info
r_struct
id|chandev_model_info
(brace
DECL|member|next
r_struct
id|chandev_model_info
op_star
id|next
suffix:semicolon
DECL|member|chan_type
id|chandev_type
id|chan_type
suffix:semicolon
DECL|member|cu_type
id|u16
id|cu_type
suffix:semicolon
DECL|member|cu_model
id|u8
id|cu_model
suffix:semicolon
DECL|member|max_port_no
id|u8
id|max_port_no
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|chandev
r_typedef
r_struct
id|chandev
id|chandev
suffix:semicolon
DECL|struct|chandev
r_struct
id|chandev
(brace
DECL|member|next
r_struct
id|chandev
op_star
id|next
suffix:semicolon
DECL|member|model_info
id|chandev_model_info
op_star
id|model_info
suffix:semicolon
DECL|member|devno
id|u16
id|devno
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|chandev_noauto_range
r_typedef
r_struct
id|chandev_noauto_range
id|chandev_noauto_range
suffix:semicolon
DECL|struct|chandev_noauto_range
r_struct
id|chandev_noauto_range
(brace
DECL|member|next
r_struct
id|chandev_noauto_range
op_star
id|next
suffix:semicolon
DECL|member|lo_devno
id|u16
id|lo_devno
suffix:semicolon
DECL|member|hi_devno
id|u16
id|hi_devno
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|chandev_force
r_typedef
r_struct
id|chandev_force
id|chandev_force
suffix:semicolon
DECL|struct|chandev_force
r_struct
id|chandev_force
(brace
DECL|member|next
r_struct
id|chandev_force
op_star
id|next
suffix:semicolon
DECL|member|chan_type
id|chandev_type
id|chan_type
suffix:semicolon
DECL|member|devif_num
id|s32
id|devif_num
suffix:semicolon
multiline_comment|/* -1 don&squot;t care e.g. tr0 implies 0 */
DECL|member|read_devno
id|u16
id|read_devno
suffix:semicolon
DECL|member|write_devno
id|u16
id|write_devno
suffix:semicolon
DECL|member|port_no
id|s16
id|port_no
suffix:semicolon
multiline_comment|/* where available e.g. lcs,-1 don&squot;t care */
DECL|member|do_ip_checksumming
id|u8
id|do_ip_checksumming
suffix:semicolon
DECL|member|use_hw_stats
id|u8
id|use_hw_stats
suffix:semicolon
multiline_comment|/* where available e.g. lcs */
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|devif_num
id|s32
id|devif_num
suffix:semicolon
multiline_comment|/* -1 don&squot;t care e.g. tr0 implies 0 */
DECL|member|read_irq
r_int
id|read_irq
suffix:semicolon
DECL|member|write_irq
r_int
id|write_irq
suffix:semicolon
DECL|member|forced_port_no
id|s16
id|forced_port_no
suffix:semicolon
multiline_comment|/* -1 don&squot;t care */
DECL|member|hint_port_no
id|u8
id|hint_port_no
suffix:semicolon
DECL|member|max_port_no
id|u8
id|max_port_no
suffix:semicolon
DECL|member|do_ip_checksumming
id|u8
id|do_ip_checksumming
suffix:semicolon
DECL|member|use_hw_stats
id|u8
id|use_hw_stats
suffix:semicolon
multiline_comment|/* where available e.g. lcs */
DECL|typedef|chandev_probeinfo
)brace
id|chandev_probeinfo
suffix:semicolon
DECL|typedef|chandev_probefunc
r_typedef
r_int
(paren
op_star
id|chandev_probefunc
)paren
(paren
id|chandev_probeinfo
op_star
id|probeinfo
)paren
suffix:semicolon
DECL|typedef|chandev_probelist
r_typedef
r_struct
id|chandev_probelist
id|chandev_probelist
suffix:semicolon
DECL|struct|chandev_probelist
r_struct
id|chandev_probelist
(brace
DECL|member|next
r_struct
id|chandev_probelist
op_star
id|next
suffix:semicolon
DECL|member|probefunc
id|chandev_probefunc
id|probefunc
suffix:semicolon
DECL|member|chan_type
id|chandev_type
id|chan_type
suffix:semicolon
)brace
suffix:semicolon
eof
