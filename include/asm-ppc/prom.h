multiline_comment|/*&n; * Definitions for talking to the Open Firmware PROM on&n; * Power Macintosh computers.&n; *&n; * Copyright (C) 1996 Paul Mackerras.&n; */
DECL|typedef|phandle
r_typedef
r_void
op_star
id|phandle
suffix:semicolon
DECL|typedef|ihandle
r_typedef
r_void
op_star
id|ihandle
suffix:semicolon
r_extern
id|ihandle
id|prom_stdout
suffix:semicolon
r_extern
id|ihandle
id|prom_chosen
suffix:semicolon
r_extern
id|phandle
id|cpu_node
suffix:semicolon
r_extern
r_char
id|prom_display_path
(braket
)braket
suffix:semicolon
DECL|struct|reg_property
r_struct
id|reg_property
(brace
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|translation_property
r_struct
id|translation_property
(brace
DECL|member|virt
r_int
r_int
id|virt
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|phys
r_int
r_int
id|phys
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|property
r_struct
id|property
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|length
r_int
id|length
suffix:semicolon
DECL|member|value
r_int
r_char
op_star
id|value
suffix:semicolon
DECL|member|next
r_struct
id|property
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|device_node
r_struct
id|device_node
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|type
r_char
op_star
id|type
suffix:semicolon
DECL|member|node
id|phandle
id|node
suffix:semicolon
DECL|member|n_addrs
r_int
id|n_addrs
suffix:semicolon
DECL|member|addrs
r_struct
id|reg_property
op_star
id|addrs
suffix:semicolon
DECL|member|n_intrs
r_int
id|n_intrs
suffix:semicolon
DECL|member|intrs
r_int
op_star
id|intrs
suffix:semicolon
DECL|member|full_name
r_char
op_star
id|full_name
suffix:semicolon
DECL|member|properties
r_struct
id|property
op_star
id|properties
suffix:semicolon
DECL|member|parent
r_struct
id|device_node
op_star
id|parent
suffix:semicolon
DECL|member|child
r_struct
id|device_node
op_star
id|child
suffix:semicolon
DECL|member|sibling
r_struct
id|device_node
op_star
id|sibling
suffix:semicolon
DECL|member|next
r_struct
id|device_node
op_star
id|next
suffix:semicolon
multiline_comment|/* next device of same type */
DECL|member|allnext
r_struct
id|device_node
op_star
id|allnext
suffix:semicolon
multiline_comment|/* next in list of all nodes */
)brace
suffix:semicolon
multiline_comment|/* Prototypes */
r_void
m_abort
(paren
r_void
)paren
suffix:semicolon
r_void
id|prom_exit
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
op_star
id|call_prom
c_func
(paren
r_const
r_char
op_star
id|service
comma
r_int
id|nargs
comma
r_int
id|nret
comma
dot
dot
dot
)paren
suffix:semicolon
r_void
id|prom_print
c_func
(paren
r_const
r_char
op_star
id|msg
)paren
suffix:semicolon
r_void
id|prom_init
c_func
(paren
r_char
op_star
id|params
comma
r_int
id|unused
comma
r_void
(paren
op_star
)paren
(paren
r_void
op_star
)paren
)paren
suffix:semicolon
r_void
id|set_prom_callback
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|copy_device_tree
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_struct
id|device_node
op_star
id|find_devices
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_struct
id|device_node
op_star
id|find_type_devices
c_func
(paren
r_const
r_char
op_star
id|type
)paren
suffix:semicolon
r_struct
id|device_node
op_star
id|find_path_device
c_func
(paren
r_const
r_char
op_star
id|path
)paren
suffix:semicolon
r_int
r_char
op_star
id|get_property
c_func
(paren
r_struct
id|device_node
op_star
id|node
comma
r_const
r_char
op_star
id|name
comma
r_int
op_star
id|lenp
)paren
suffix:semicolon
r_void
id|print_properties
c_func
(paren
r_struct
id|device_node
op_star
id|node
)paren
suffix:semicolon
eof