DECL|macro|_PLUSB_INTPIPE
mdefine_line|#define _PLUSB_INTPIPE&t;&t;0x1
DECL|macro|_PLUSB_BULKOUTPIPE
mdefine_line|#define _PLUSB_BULKOUTPIPE&t;0x2
DECL|macro|_PLUSB_BULKINPIPE
mdefine_line|#define _PLUSB_BULKINPIPE&t;0x3
DECL|macro|_SKB_NUM
mdefine_line|#define _SKB_NUM&t;&t;1000
singleline_comment|//  7  6  5  4  3  2  1  0
singleline_comment|//  tx rx 1  0
singleline_comment|// 1110 0000 rxdata
singleline_comment|// 1010 0000 idle
singleline_comment|// 0010 0000 tx over
singleline_comment|// 0110      tx over + rxd
DECL|macro|_PLUSB_RXD
mdefine_line|#define _PLUSB_RXD&t;&t;0x40
DECL|macro|_PLUSB_TXOK
mdefine_line|#define _PLUSB_TXOK&t;&t;0x80
macro_line|#ifdef __KERNEL__
DECL|macro|_BULK_DATA_LEN
mdefine_line|#define _BULK_DATA_LEN&t;&t;16384
r_typedef
r_struct
(brace
DECL|member|skb_list
r_struct
id|list_head
id|skb_list
suffix:semicolon
DECL|member|skb
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|typedef|skb_list_t
DECL|typedef|pskb_list_t
)brace
id|skb_list_t
comma
op_star
id|pskb_list_t
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|usbdev
r_struct
id|usb_device
op_star
id|usbdev
suffix:semicolon
DECL|member|status
r_int
id|status
suffix:semicolon
DECL|member|connected
r_int
id|connected
suffix:semicolon
DECL|member|in_bh
r_int
id|in_bh
suffix:semicolon
DECL|member|opened
r_int
id|opened
suffix:semicolon
DECL|member|lock
id|spinlock_t
id|lock
suffix:semicolon
DECL|member|inturb
id|urb_t
op_star
id|inturb
suffix:semicolon
DECL|member|bulkurb
id|urb_t
op_star
id|bulkurb
suffix:semicolon
DECL|member|tx_skb_list
r_struct
id|list_head
id|tx_skb_list
suffix:semicolon
DECL|member|free_skb_list
r_struct
id|list_head
id|free_skb_list
suffix:semicolon
DECL|member|bh
r_struct
id|tq_struct
id|bh
suffix:semicolon
DECL|member|net_dev
r_struct
id|net_device
id|net_dev
suffix:semicolon
DECL|member|net_stats
r_struct
id|net_device_stats
id|net_stats
suffix:semicolon
DECL|typedef|plusb_t
DECL|typedef|pplusb_t
)brace
id|plusb_t
comma
op_star
id|pplusb_t
suffix:semicolon
macro_line|#endif
eof
