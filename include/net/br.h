multiline_comment|/*&n; * Constants and structure definitions for the bridging code&n; */
macro_line|#if !defined(One)
DECL|macro|Zero
mdefine_line|#define Zero    0
DECL|macro|One
mdefine_line|#define One&t;1
macro_line|#endif  /* !defined(One) */
macro_line|#if !defined(TRUE)
DECL|macro|FALSE
mdefine_line|#define FALSE   0
DECL|macro|TRUE
mdefine_line|#define TRUE&t;1
macro_line|#endif /* !defined(TRUE) */
multiline_comment|/** port states. **/
DECL|macro|Disabled
mdefine_line|#define Disabled&t;0&t;&t;&t;  /* (4.4 5)&t; */
DECL|macro|Listening
mdefine_line|#define Listening&t;1&t;&t;&t;  /* (4.4.2)&t; */
DECL|macro|Learning
mdefine_line|#define Learning&t;2&t;&t;&t;  /* (4.4.3)&t; */
DECL|macro|Forwarding
mdefine_line|#define Forwarding&t;3&t;&t;&t;  /* (4 4 4)&t; */
DECL|macro|Blocking
mdefine_line|#define Blocking&t;4&t;&t;&t;  /* (4.4.1)&t; */
DECL|macro|No_of_ports
mdefine_line|#define No_of_ports 8
multiline_comment|/* arbitrary choice, to allow the code below to compile */
DECL|macro|All_ports
mdefine_line|#define All_ports (No_of_ports + 1)
multiline_comment|/*&n; * We time out our entries in the FDB after this many seconds.&n; */
DECL|macro|FDB_TIMEOUT
mdefine_line|#define FDB_TIMEOUT&t;300
multiline_comment|/*&n; * the following defines are the initial values used when the &n; * bridge is booted.  These may be overridden when this bridge is&n; * not the root bridge.  These are the recommended default values &n; * from the 802.1d specification.&n; */
DECL|macro|BRIDGE_MAX_AGE
mdefine_line|#define BRIDGE_MAX_AGE&t;&t;20
DECL|macro|BRIDGE_HELLO_TIME
mdefine_line|#define BRIDGE_HELLO_TIME&t;2
DECL|macro|BRIDGE_FORWARD_DELAY
mdefine_line|#define BRIDGE_FORWARD_DELAY&t;15
DECL|macro|HOLD_TIME
mdefine_line|#define HOLD_TIME&t;&t;1
DECL|macro|Default_path_cost
mdefine_line|#define Default_path_cost 10
multiline_comment|/*&n; * minimum increment possible to avoid underestimating age, allows for BPDU&n; * transmission time&n; */
DECL|macro|Message_age_increment
mdefine_line|#define Message_age_increment 1
DECL|macro|No_port
mdefine_line|#define No_port 0
multiline_comment|/*&n; * reserved value for Bridge&squot;s root port parameter indicating no root port,&n; * used when Bridge is the root - also used to indicate the source when&n; * a frame is being generated by a higher layer protocol on this host&n; */
multiline_comment|/** Configuration BPDU Parameters (4.5.1) **/
r_typedef
r_struct
(brace
r_union
(brace
r_struct
(brace
DECL|member|priority
r_int
r_int
id|priority
suffix:semicolon
DECL|member|ula
r_int
r_char
id|ula
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|p_u
)brace
id|p_u
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|bi
)brace
id|bi
suffix:semicolon
DECL|typedef|bridge_id_t
)brace
id|bridge_id_t
suffix:semicolon
DECL|macro|BRIDGE_PRIORITY
mdefine_line|#define BRIDGE_PRIORITY&t;bi.p_u.priority
DECL|macro|BRIDGE_ID_ULA
mdefine_line|#define BRIDGE_ID_ULA&t;bi.p_u.ula
DECL|macro|BRIDGE_ID
mdefine_line|#define BRIDGE_ID&t;bi.id
r_typedef
r_struct
(brace
DECL|member|protocol_id
r_int
r_int
id|protocol_id
suffix:semicolon
DECL|member|protocol_version_id
r_int
r_char
id|protocol_version_id
suffix:semicolon
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|macro|TOPOLOGY_CHANGE
mdefine_line|#define TOPOLOGY_CHANGE&t;&t;0x01
DECL|macro|TOPOLOGY_CHANGE_ACK
mdefine_line|#define TOPOLOGY_CHANGE_ACK&t;0x80
DECL|member|root_id
id|bridge_id_t
id|root_id
suffix:semicolon
multiline_comment|/* (4.5.1.1)&t; */
DECL|member|root_path_cost
r_int
r_int
id|root_path_cost
suffix:semicolon
multiline_comment|/* (4.5.1.2)&t; */
DECL|member|bridge_id
id|bridge_id_t
id|bridge_id
suffix:semicolon
multiline_comment|/* (4.5.1.3)&t; */
DECL|member|port_id
r_int
r_int
id|port_id
suffix:semicolon
multiline_comment|/* (4.5.1.4)&t; */
DECL|member|message_age
r_int
r_int
id|message_age
suffix:semicolon
multiline_comment|/* (4.5.1.5)&t; */
DECL|member|max_age
r_int
r_int
id|max_age
suffix:semicolon
multiline_comment|/* (4.5.1.6)&t; */
DECL|member|hello_time
r_int
r_int
id|hello_time
suffix:semicolon
multiline_comment|/* (4.5.1.7)&t; */
DECL|member|forward_delay
r_int
r_int
id|forward_delay
suffix:semicolon
multiline_comment|/* (4.5.1.8)&t; */
DECL|typedef|Config_bpdu
)brace
id|Config_bpdu
suffix:semicolon
multiline_comment|/** Topology Change Notification BPDU Parameters (4.5.2) **/
r_typedef
r_struct
(brace
DECL|member|protocol_id
r_int
r_int
id|protocol_id
suffix:semicolon
DECL|member|protocol_version_id
r_int
r_char
id|protocol_version_id
suffix:semicolon
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
DECL|typedef|Tcn_bpdu
)brace
id|Tcn_bpdu
suffix:semicolon
DECL|macro|BPDU_TYPE_CONFIG
mdefine_line|#define BPDU_TYPE_CONFIG&t;0
DECL|macro|BPDU_TYPE_TOPO_CHANGE
mdefine_line|#define BPDU_TYPE_TOPO_CHANGE&t;128
multiline_comment|/** Bridge Parameters (4.5.3) **/
r_typedef
r_struct
(brace
DECL|member|designated_root
id|bridge_id_t
id|designated_root
suffix:semicolon
multiline_comment|/* (4.5.3.1)&t; */
DECL|member|root_path_cost
r_int
r_int
id|root_path_cost
suffix:semicolon
multiline_comment|/* (4.5.3.2)&t; */
DECL|member|root_port
r_int
r_int
id|root_port
suffix:semicolon
multiline_comment|/* (4.5.3.3)&t; */
DECL|member|max_age
r_int
r_int
id|max_age
suffix:semicolon
multiline_comment|/* (4.5.3.4)&t; */
DECL|member|hello_time
r_int
r_int
id|hello_time
suffix:semicolon
multiline_comment|/* (4.5.3.5)&t; */
DECL|member|forward_delay
r_int
r_int
id|forward_delay
suffix:semicolon
multiline_comment|/* (4.5.3.6)&t; */
DECL|member|bridge_id
id|bridge_id_t
id|bridge_id
suffix:semicolon
multiline_comment|/* (4.5.3.7)&t; */
DECL|member|bridge_max_age
r_int
r_int
id|bridge_max_age
suffix:semicolon
multiline_comment|/* (4.5.3.8)&t; */
DECL|member|bridge_hello_time
r_int
r_int
id|bridge_hello_time
suffix:semicolon
multiline_comment|/* (4.5.3.9)&t; */
DECL|member|bridge_forward_delay
r_int
r_int
id|bridge_forward_delay
suffix:semicolon
multiline_comment|/* (4.5.3.10)&t; */
DECL|member|topology_change_detected
r_int
r_int
id|topology_change_detected
suffix:semicolon
multiline_comment|/* (4.5.3.11) */
DECL|member|topology_change
r_int
r_int
id|topology_change
suffix:semicolon
multiline_comment|/* (4.5.3.12)&t; */
DECL|member|topology_change_time
r_int
r_int
id|topology_change_time
suffix:semicolon
multiline_comment|/* (4.5.3.13)&t; */
DECL|member|hold_time
r_int
r_int
id|hold_time
suffix:semicolon
multiline_comment|/* (4.5.3.14)&t; */
DECL|member|top_change
r_int
r_int
id|top_change
suffix:semicolon
DECL|member|top_change_detected
r_int
r_int
id|top_change_detected
suffix:semicolon
DECL|typedef|Bridge_data
)brace
id|Bridge_data
suffix:semicolon
multiline_comment|/** Port Parameters (4.5.5) **/
r_typedef
r_struct
(brace
DECL|member|port_id
r_int
r_int
id|port_id
suffix:semicolon
multiline_comment|/* (4.5.5.1)&t; */
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
multiline_comment|/* (4.5.5.2)&t; */
DECL|member|path_cost
r_int
r_int
id|path_cost
suffix:semicolon
multiline_comment|/* (4.5.5.3)&t; */
DECL|member|designated_root
id|bridge_id_t
id|designated_root
suffix:semicolon
multiline_comment|/* (4.5.5.4)&t; */
DECL|member|designated_cost
r_int
r_int
id|designated_cost
suffix:semicolon
multiline_comment|/* (4.5.5.5)&t; */
DECL|member|designated_bridge
id|bridge_id_t
id|designated_bridge
suffix:semicolon
multiline_comment|/* (4.5.5.6)&t; */
DECL|member|designated_port
r_int
r_int
id|designated_port
suffix:semicolon
multiline_comment|/* (4.5.5.7)&t; */
DECL|member|top_change_ack
r_int
r_int
id|top_change_ack
suffix:semicolon
multiline_comment|/* (4.5.5.8)&t; */
DECL|member|config_pending
r_int
r_int
id|config_pending
suffix:semicolon
multiline_comment|/* (4.5.5.9)&t; */
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
DECL|member|fdb
r_struct
id|fdb
op_star
id|fdb
suffix:semicolon
multiline_comment|/* head of per port fdb chain */
DECL|typedef|Port_data
)brace
id|Port_data
suffix:semicolon
multiline_comment|/** types to support timers for this pseudo-implementation. **/
r_typedef
r_struct
(brace
DECL|member|active
r_int
r_int
id|active
suffix:semicolon
multiline_comment|/* timer in use. */
DECL|member|value
r_int
r_int
id|value
suffix:semicolon
multiline_comment|/* current value of timer,&n;&t;&t;&t;&t;&t;&t;   * counting up. */
DECL|typedef|Timer
)brace
id|Timer
suffix:semicolon
DECL|struct|fdb
r_struct
id|fdb
(brace
DECL|member|ula
r_int
r_char
id|ula
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|pad
r_int
r_char
id|pad
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
DECL|member|timer
r_int
r_int
id|timer
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|macro|FDB_ENT_VALID
mdefine_line|#define FDB_ENT_VALID&t;0x01
multiline_comment|/* AVL tree of all addresses, sorted by address */
DECL|member|fdb_avl_height
r_int
id|fdb_avl_height
suffix:semicolon
DECL|member|fdb_avl_left
r_struct
id|fdb
op_star
id|fdb_avl_left
suffix:semicolon
DECL|member|fdb_avl_right
r_struct
id|fdb
op_star
id|fdb_avl_right
suffix:semicolon
multiline_comment|/* linked list of addresses for each port */
DECL|member|fdb_next
r_struct
id|fdb
op_star
id|fdb_next
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IS_BRIDGED
mdefine_line|#define IS_BRIDGED&t;0x2e
DECL|macro|BR_MAX_PROTOCOLS
mdefine_line|#define BR_MAX_PROTOCOLS 32
DECL|macro|BR_MAX_PROT_STATS
mdefine_line|#define BR_MAX_PROT_STATS BR_MAX_PROTOCOLS
multiline_comment|/* policy values for policy field */
DECL|macro|BR_ACCEPT
mdefine_line|#define BR_ACCEPT 1
DECL|macro|BR_REJECT
mdefine_line|#define BR_REJECT 0
DECL|struct|br_stat
r_struct
id|br_stat
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|bridge_data
id|Bridge_data
id|bridge_data
suffix:semicolon
DECL|member|port_data
id|Port_data
id|port_data
(braket
id|No_of_ports
)braket
suffix:semicolon
DECL|member|policy
r_int
r_int
id|policy
suffix:semicolon
DECL|member|exempt_protocols
r_int
r_int
id|exempt_protocols
suffix:semicolon
DECL|member|protocols
r_int
r_int
id|protocols
(braket
id|BR_MAX_PROTOCOLS
)braket
suffix:semicolon
DECL|member|prot_id
r_int
r_int
id|prot_id
(braket
id|BR_MAX_PROT_STATS
)braket
suffix:semicolon
multiline_comment|/* Protocol encountered */
DECL|member|prot_counter
r_int
r_int
id|prot_counter
(braket
id|BR_MAX_PROT_STATS
)braket
suffix:semicolon
multiline_comment|/* How many packets ? */
)brace
suffix:semicolon
multiline_comment|/* defined flags for br_stat.flags */
DECL|macro|BR_UP
mdefine_line|#define BR_UP&t;&t;0x0001&t;/* bridging enabled */
DECL|macro|BR_DEBUG
mdefine_line|#define BR_DEBUG&t;0x0002&t;/* debugging enabled */
DECL|macro|BR_PROT_STATS
mdefine_line|#define BR_PROT_STATS&t;0x0004&t;/* protocol statistics enabled */
DECL|struct|br_cf
r_struct
id|br_cf
(brace
DECL|member|cmd
r_int
r_int
id|cmd
suffix:semicolon
DECL|member|arg1
r_int
r_int
id|arg1
suffix:semicolon
DECL|member|arg2
r_int
r_int
id|arg2
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* defined cmds */
DECL|macro|BRCMD_BRIDGE_ENABLE
mdefine_line|#define&t;BRCMD_BRIDGE_ENABLE&t;1
DECL|macro|BRCMD_BRIDGE_DISABLE
mdefine_line|#define&t;BRCMD_BRIDGE_DISABLE&t;2
DECL|macro|BRCMD_PORT_ENABLE
mdefine_line|#define&t;BRCMD_PORT_ENABLE&t;3&t;/* arg1 = port */
DECL|macro|BRCMD_PORT_DISABLE
mdefine_line|#define&t;BRCMD_PORT_DISABLE&t;4&t;/* arg1 = port */
DECL|macro|BRCMD_SET_BRIDGE_PRIORITY
mdefine_line|#define&t;BRCMD_SET_BRIDGE_PRIORITY&t;5&t;/* arg1 = priority */
DECL|macro|BRCMD_SET_PORT_PRIORITY
mdefine_line|#define&t;BRCMD_SET_PORT_PRIORITY&t;6&t;/* arg1 = port, arg2 = priority */
DECL|macro|BRCMD_SET_PATH_COST
mdefine_line|#define&t;BRCMD_SET_PATH_COST&t;7&t;/* arg1 = port, arg2 = cost */
DECL|macro|BRCMD_DISPLAY_FDB
mdefine_line|#define&t;BRCMD_DISPLAY_FDB&t;8&t;/* arg1 = port */
DECL|macro|BRCMD_ENABLE_DEBUG
mdefine_line|#define&t;BRCMD_ENABLE_DEBUG&t;9
DECL|macro|BRCMD_DISABLE_DEBUG
mdefine_line|#define&t;BRCMD_DISABLE_DEBUG&t;10
DECL|macro|BRCMD_SET_POLICY
mdefine_line|#define BRCMD_SET_POLICY&t;11&t;/* arg1 = default policy (1==bridge all) */
DECL|macro|BRCMD_EXEMPT_PROTOCOL
mdefine_line|#define BRCMD_EXEMPT_PROTOCOL&t;12&t;/* arg1 = protocol (see net/if_ether.h) */
DECL|macro|BRCMD_ENABLE_PROT_STATS
mdefine_line|#define BRCMD_ENABLE_PROT_STATS&t;13
DECL|macro|BRCMD_DISABLE_PROT_STATS
mdefine_line|#define BRCMD_DISABLE_PROT_STATS 14
DECL|macro|BRCMD_ZERO_PROT_STATS
mdefine_line|#define BRCMD_ZERO_PROT_STATS&t;15
multiline_comment|/* prototypes of exported bridging functions... */
r_void
id|br_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|br_receive_frame
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
multiline_comment|/* 3.5 */
r_int
id|br_tx_frame
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_int
id|br_ioctl
c_func
(paren
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_int
id|br_protocol_ok
c_func
(paren
r_int
r_int
id|protocol
)paren
suffix:semicolon
r_struct
id|fdb
op_star
id|br_avl_find_addr
c_func
(paren
r_int
r_char
id|addr
(braket
l_int|6
)braket
)paren
suffix:semicolon
r_int
id|br_avl_insert
(paren
r_struct
id|fdb
op_star
id|new_node
)paren
suffix:semicolon
multiline_comment|/* externs */
r_extern
r_struct
id|br_stat
id|br_stats
suffix:semicolon
eof
