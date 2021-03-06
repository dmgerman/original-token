multiline_comment|/*&n; *&n; * Lan Emulation client header file&n; *&n; * Marko Kiiskila carnil@cs.tut.fi&n; *&n; */
macro_line|#ifndef _LEC_H_
DECL|macro|_LEC_H_
mdefine_line|#define _LEC_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/atmdev.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/atmlec.h&gt;
macro_line|#if defined (CONFIG_BRIDGE) || defined(CONFIG_BRIDGE_MODULE)
macro_line|#include &lt;linux/if_bridge.h&gt;
DECL|variable|br_fdb_get_hook
r_struct
id|net_bridge_fdb_entry
op_star
(paren
op_star
id|br_fdb_get_hook
)paren
(paren
r_struct
id|net_bridge
op_star
id|br
comma
r_int
r_char
op_star
id|addr
)paren
suffix:semicolon
DECL|variable|br_fdb_put_hook
r_void
(paren
op_star
id|br_fdb_put_hook
)paren
(paren
r_struct
id|net_bridge_fdb_entry
op_star
id|ent
)paren
suffix:semicolon
macro_line|#endif /* defined(CONFIG_BRIDGE) || defined(CONFIG_BRIDGE_MODULE) */
DECL|macro|LEC_HEADER_LEN
mdefine_line|#define LEC_HEADER_LEN 16
DECL|struct|lecdatahdr_8023
r_struct
id|lecdatahdr_8023
(brace
DECL|member|le_header
r_int
r_int
id|le_header
suffix:semicolon
DECL|member|h_dest
r_int
r_char
id|h_dest
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|h_source
r_int
r_char
id|h_source
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|h_type
r_int
r_int
id|h_type
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|lecdatahdr_8025
r_struct
id|lecdatahdr_8025
(brace
DECL|member|le_header
r_int
r_int
id|le_header
suffix:semicolon
DECL|member|ac_pad
r_int
r_char
id|ac_pad
suffix:semicolon
DECL|member|fc
r_int
r_char
id|fc
suffix:semicolon
DECL|member|h_dest
r_int
r_char
id|h_dest
(braket
id|ETH_ALEN
)braket
suffix:semicolon
DECL|member|h_source
r_int
r_char
id|h_source
(braket
id|ETH_ALEN
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Operations that LANE2 capable device can do. Two first functions&n; * are used to make the device do things. See spec 3.1.3 and 3.1.4.&n; *&n; * The third function is intented for the MPOA component sitting on&n; * top of the LANE device. The MPOA component assigns it&squot;s own function&n; * to (*associate_indicator)() and the LANE device will use that&n; * function to tell about TLVs it sees floating through.&n; *&n; */
DECL|struct|lane2_ops
r_struct
id|lane2_ops
(brace
DECL|member|resolve
r_int
(paren
op_star
id|resolve
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|u8
op_star
id|dst_mac
comma
r_int
id|force
comma
id|u8
op_star
op_star
id|tlvs
comma
id|u32
op_star
id|sizeoftlvs
)paren
suffix:semicolon
DECL|member|associate_req
r_int
(paren
op_star
id|associate_req
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|u8
op_star
id|lan_dst
comma
id|u8
op_star
id|tlvs
comma
id|u32
id|sizeoftlvs
)paren
suffix:semicolon
DECL|member|associate_indicator
r_void
(paren
op_star
id|associate_indicator
)paren
(paren
r_struct
id|net_device
op_star
id|dev
comma
id|u8
op_star
id|mac_addr
comma
id|u8
op_star
id|tlvs
comma
id|u32
id|sizeoftlvs
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|atm_lane_ops
r_struct
id|atm_lane_ops
(brace
DECL|member|lecd_attach
r_int
(paren
op_star
id|lecd_attach
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|arg
)paren
suffix:semicolon
DECL|member|mcast_attach
r_int
(paren
op_star
id|mcast_attach
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|arg
)paren
suffix:semicolon
DECL|member|vcc_attach
r_int
(paren
op_star
id|vcc_attach
)paren
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
DECL|member|get_lecs
r_struct
id|net_device
op_star
op_star
(paren
op_star
id|get_lecs
)paren
(paren
r_void
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ATM LAN Emulation supports both LLC &amp; Dix Ethernet EtherType&n; * frames. &n; * 1. Dix Ethernet EtherType frames encoded by placing EtherType&n; *    field in h_type field. Data follows immediatelly after header.&n; * 2. LLC Data frames whose total length, including LLC field and data,&n; *    but not padding required to meet the minimum data frame length, &n; *    is less than 1536(0x0600) MUST be encoded by placing that length&n; *    in the the h_type field. The LLC field follows header immediatelly.&n; * 3. LLC data frames longer than this maximum MUST be encoded by placing&n; *    the value 0 in the h_type field.&n; *&n; */
multiline_comment|/* Hash table size */
DECL|macro|LEC_ARP_TABLE_SIZE
mdefine_line|#define LEC_ARP_TABLE_SIZE 16
DECL|struct|lec_priv
r_struct
id|lec_priv
(brace
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|lecid
r_int
r_int
id|lecid
suffix:semicolon
multiline_comment|/* Lecid of this client */
DECL|member|lec_arp_empty_ones
r_struct
id|lec_arp_table
op_star
id|lec_arp_empty_ones
suffix:semicolon
multiline_comment|/* Used for storing VCC&squot;s that don&squot;t have a MAC address attached yet */
DECL|member|lec_arp_tables
r_struct
id|lec_arp_table
op_star
id|lec_arp_tables
(braket
id|LEC_ARP_TABLE_SIZE
)braket
suffix:semicolon
multiline_comment|/* Actual LE ARP table */
DECL|member|lec_no_forward
r_struct
id|lec_arp_table
op_star
id|lec_no_forward
suffix:semicolon
multiline_comment|/* Used for storing VCC&squot;s (and forward packets from) which are to&n;           age out by not using them to forward packets. &n;           This is because to some LE clients there will be 2 VCCs. Only&n;           one of them gets used. */
DECL|member|mcast_fwds
r_struct
id|lec_arp_table
op_star
id|mcast_fwds
suffix:semicolon
multiline_comment|/* With LANEv2 it is possible that BUS (or a special multicast server)&n;           establishes multiple Multicast Forward VCCs to us. This list&n;           collects all those VCCs. LANEv1 client has only one item in this&n;           list. These entries are not aged out. */
DECL|member|lec_arp_lock_var
id|atomic_t
id|lec_arp_lock_var
suffix:semicolon
DECL|member|mcast_vcc
r_struct
id|atm_vcc
op_star
id|mcast_vcc
suffix:semicolon
multiline_comment|/* Default Multicast Send VCC */
DECL|member|lecd
r_struct
id|atm_vcc
op_star
id|lecd
suffix:semicolon
DECL|member|lec_arp_timer
r_struct
id|timer_list
id|lec_arp_timer
suffix:semicolon
multiline_comment|/* C10 */
DECL|member|maximum_unknown_frame_count
r_int
r_int
id|maximum_unknown_frame_count
suffix:semicolon
multiline_comment|/* Within the period of time defined by this variable, the client will send &n;   no more than C10 frames to BUS for a given unicast destination. (C11) */
DECL|member|max_unknown_frame_time
r_int
r_int
id|max_unknown_frame_time
suffix:semicolon
multiline_comment|/* If no traffic has been sent in this vcc for this period of time,&n;   vcc will be torn down (C12)*/
DECL|member|vcc_timeout_period
r_int
r_int
id|vcc_timeout_period
suffix:semicolon
multiline_comment|/* An LE Client MUST not retry an LE_ARP_REQUEST for a &n;   given frame&squot;s LAN Destination more than maximum retry count times,&n;   after the first LEC_ARP_REQUEST (C13)*/
DECL|member|max_retry_count
r_int
r_int
id|max_retry_count
suffix:semicolon
multiline_comment|/* Max time the client will maintain an entry in its arp cache in&n;   absence of a verification of that relationship (C17)*/
DECL|member|aging_time
r_int
r_int
id|aging_time
suffix:semicolon
multiline_comment|/* Max time the client will maintain an entry in cache when&n;   topology change flag is true (C18) */
DECL|member|forward_delay_time
r_int
r_int
id|forward_delay_time
suffix:semicolon
multiline_comment|/* Topology change flag  (C19)*/
DECL|member|topology_change
r_int
id|topology_change
suffix:semicolon
multiline_comment|/* Max time the client expects an LE_ARP_REQUEST/LE_ARP_RESPONSE&n;   cycle to take (C20)*/
DECL|member|arp_response_time
r_int
r_int
id|arp_response_time
suffix:semicolon
multiline_comment|/* Time limit ot wait to receive an LE_FLUSH_RESPONSE after the&n;   LE_FLUSH_REQUEST has been sent before taking recover action. (C21)*/
DECL|member|flush_timeout
r_int
r_int
id|flush_timeout
suffix:semicolon
multiline_comment|/* The time since sending a frame to the bus after which the&n;   LE Client may assume that the frame has been either discarded or&n;   delivered to the recipient (C22) */
DECL|member|path_switching_delay
r_int
r_int
id|path_switching_delay
suffix:semicolon
DECL|member|tlvs
id|u8
op_star
id|tlvs
suffix:semicolon
multiline_comment|/* LANE2: TLVs are new                */
DECL|member|sizeoftlvs
id|u32
id|sizeoftlvs
suffix:semicolon
multiline_comment|/* The size of the tlv array in bytes */
DECL|member|lane_version
r_int
id|lane_version
suffix:semicolon
multiline_comment|/* LANE2                              */
DECL|member|itfnum
r_int
id|itfnum
suffix:semicolon
multiline_comment|/* e.g. 2 for lec2, 5 for lec5        */
DECL|member|lane2_ops
r_struct
id|lane2_ops
op_star
id|lane2_ops
suffix:semicolon
multiline_comment|/* can be NULL for LANE v1  */
DECL|member|is_proxy
r_int
id|is_proxy
suffix:semicolon
multiline_comment|/* bridge between ATM and Ethernet    */
DECL|member|is_trdev
r_int
id|is_trdev
suffix:semicolon
multiline_comment|/* Device type, 0 = Ethernet, 1 = TokenRing */
)brace
suffix:semicolon
r_int
id|lecd_attach
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|arg
)paren
suffix:semicolon
r_int
id|lec_vcc_attach
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
r_int
id|lec_mcast_attach
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_int
id|arg
)paren
suffix:semicolon
r_struct
id|net_device
op_star
op_star
id|get_dev_lec
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|make_lec
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
)paren
suffix:semicolon
r_int
id|send_to_lecd
c_func
(paren
r_struct
id|lec_priv
op_star
id|priv
comma
id|atmlec_msg_type
id|type
comma
r_int
r_char
op_star
id|mac_addr
comma
r_int
r_char
op_star
id|atm_addr
comma
r_struct
id|sk_buff
op_star
id|data
)paren
suffix:semicolon
r_void
id|lec_push
c_func
(paren
r_struct
id|atm_vcc
op_star
id|vcc
comma
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_void
id|atm_lane_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|atm_lane_init_ops
c_func
(paren
r_struct
id|atm_lane_ops
op_star
id|ops
)paren
suffix:semicolon
macro_line|#endif _LEC_H_
eof
