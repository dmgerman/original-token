multiline_comment|/*&n; * These are the public elements of the Linux kernel X.25 implementation.&n; */
macro_line|#ifndef&t;X25_KERNEL_H
DECL|macro|X25_KERNEL_H
mdefine_line|#define&t;X25_KERNEL_H
DECL|macro|PF_X25
mdefine_line|#define PF_X25&t;&t;&t;AF_X25
DECL|macro|SIOCX25SETSUBSCR
mdefine_line|#define&t;SIOCX25SETSUBSCR&t;(SIOCPROTOPRIVATE + 0)
multiline_comment|/*&n; *&t;Values for {get,set}sockopt.&n; */
DECL|macro|X25_QBITINCL
mdefine_line|#define&t;X25_QBITINCL&t;&t;1
DECL|macro|X25_PACKET_SIZE
mdefine_line|#define&t;X25_PACKET_SIZE&t;&t;10
DECL|macro|X25_WINDOW_SIZE
mdefine_line|#define&t;X25_WINDOW_SIZE&t;&t;11
DECL|macro|X25_THROUGHPUT_SPEED
mdefine_line|#define&t;X25_THROUGHPUT_SPEED&t;12
DECL|macro|X25_REVERSE_CHARGE
mdefine_line|#define&t;X25_REVERSE_CHARGE&t;13
multiline_comment|/*&n; *&t;X.25 Packet Size values.&n; */
DECL|macro|X25_PS16
mdefine_line|#define&t;X25_PS16&t;&t;4
DECL|macro|X25_PS32
mdefine_line|#define&t;X25_PS32&t;&t;5
DECL|macro|X25_PS64
mdefine_line|#define&t;X25_PS64&t;&t;6
DECL|macro|X25_PS128
mdefine_line|#define&t;X25_PS128&t;&t;7
DECL|macro|X25_PS256
mdefine_line|#define&t;X25_PS256&t;&t;8
DECL|macro|X25_PS512
mdefine_line|#define&t;X25_PS512&t;&t;9
DECL|macro|X25_PS1024
mdefine_line|#define&t;X25_PS1024&t;&t;10
DECL|macro|X25_PS2048
mdefine_line|#define&t;X25_PS2048&t;&t;11
DECL|macro|X25_PS4096
mdefine_line|#define&t;X25_PS4096&t;&t;12
multiline_comment|/*&n; *&t;X.25 Reset error and diagnostic codes.&n; */
DECL|macro|X25_ERR_RESET
mdefine_line|#define&t;X25_ERR_RESET&t;&t;100&t;/* Call Reset&t;&t;&t;*/
DECL|macro|X25_ERR_ROUT
mdefine_line|#define&t;X25_ERR_ROUT&t;&t;101&t;/* Out of Order&t;&t;&t;*/
DECL|macro|X25_ERR_RRPE
mdefine_line|#define&t;X25_ERR_RRPE&t;&t;102&t;/* Remote Procedure Error&t;*/
DECL|macro|X25_ERR_RLPE
mdefine_line|#define&t;X25_ERR_RLPE&t;&t;103&t;/* Local Procedure Error&t;*/
DECL|macro|X25_ERR_RNCG
mdefine_line|#define&t;X25_ERR_RNCG&t;&t;104&t;/* Network Congestion&t;&t;*/
DECL|macro|X25_ERR_RRDO
mdefine_line|#define&t;X25_ERR_RRDO&t;&t;105&t;/* Remote DTE Operational&t;*/
DECL|macro|X25_ERR_RNOP
mdefine_line|#define&t;X25_ERR_RNOP&t;&t;106&t;/* Network Operational&t;&t;*/
DECL|macro|X25_ERR_RINV
mdefine_line|#define&t;X25_ERR_RINV&t;&t;107&t;/* Invalid Call&t;&t;&t;*/
DECL|macro|X25_ERR_RNOO
mdefine_line|#define&t;X25_ERR_RNOO&t;&t;108&t;/* Network Out of Order&t;&t;*/
multiline_comment|/*&n; *&t;X.25 Clear error and diagnostic codes.&n; */
DECL|macro|X25_ERR_CLEAR
mdefine_line|#define&t;X25_ERR_CLEAR&t;&t;110&t;/* Call Cleared&t;&t;&t;*/
DECL|macro|X25_ERR_CBUSY
mdefine_line|#define&t;X25_ERR_CBUSY&t;&t;111&t;/* Number Busy&t;&t;&t;*/
DECL|macro|X25_ERR_COUT
mdefine_line|#define&t;X25_ERR_COUT&t;&t;112&t;/* Out of Order&t;&t;&t;*/
DECL|macro|X25_ERR_CRPE
mdefine_line|#define&t;X25_ERR_CRPE&t;&t;113&t;/* Remote Procedure Error&t;*/
DECL|macro|X25_ERR_CRRC
mdefine_line|#define&t;X25_ERR_CRRC&t;&t;114&t;/* Collect Call Refused&t;&t;*/
DECL|macro|X25_ERR_CINV
mdefine_line|#define&t;X25_ERR_CINV&t;&t;115&t;/* Invalid Call&t;&t;&t;*/
DECL|macro|X25_ERR_CNFS
mdefine_line|#define&t;X25_ERR_CNFS&t;&t;116&t;/* Invalid Fast Select&t;&t;*/
DECL|macro|X25_ERR_CSA
mdefine_line|#define&t;X25_ERR_CSA&t;&t;117&t;/* Ship Absent&t;&t;&t;*/
DECL|macro|X25_ERR_CIFR
mdefine_line|#define&t;X25_ERR_CIFR&t;&t;118&t;/* Invalid Facility Request&t;*/
DECL|macro|X25_ERR_CAB
mdefine_line|#define&t;X25_ERR_CAB&t;&t;119&t;/* Access Barred&t;&t;*/
DECL|macro|X25_ERR_CLPE
mdefine_line|#define&t;X25_ERR_CLPE&t;&t;120&t;/* Local Procedure Error&t;*/
DECL|macro|X25_ERR_CNCG
mdefine_line|#define&t;X25_ERR_CNCG&t;&t;121&t;/* Network Congestion&t;&t;*/
DECL|macro|X25_ERR_CNOB
mdefine_line|#define&t;X25_ERR_CNOB&t;&t;122&t;/* Not Obtainable&t;&t;*/
DECL|macro|X25_ERR_CROO
mdefine_line|#define&t;X25_ERR_CROO&t;&t;123&t;/* RPOA Out of Order&t;&t;*/
multiline_comment|/*&n; * An X.121 address, it is held as ASCII text, null terminated, up to 15&n; * digits and a null terminator.&n; */
r_typedef
r_struct
(brace
DECL|member|x25_addr
r_char
id|x25_addr
(braket
l_int|16
)braket
suffix:semicolon
DECL|typedef|x25_address
)brace
id|x25_address
suffix:semicolon
multiline_comment|/*&n; *&t;Linux X.25 Address structure, used for bind, and connect mostly.&n; */
DECL|struct|sockaddr_x25
r_struct
id|sockaddr_x25
(brace
DECL|member|sx25_family
id|sa_family_t
id|sx25_family
suffix:semicolon
multiline_comment|/* Must be AF_X25 */
DECL|member|sx25_addr
id|x25_address
id|sx25_addr
suffix:semicolon
multiline_comment|/* X.121 Address */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;DTE/DCE subscription options.&n; */
DECL|struct|x25_subscrip_struct
r_struct
id|x25_subscrip_struct
(brace
DECL|member|device
r_char
id|device
(braket
l_int|200
)braket
suffix:semicolon
DECL|member|extended
r_int
r_int
id|extended
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Routing table control structure.&n; */
DECL|struct|x25_route_struct
r_struct
id|x25_route_struct
(brace
DECL|member|address
id|x25_address
id|address
suffix:semicolon
DECL|member|sigdigits
r_int
r_int
id|sigdigits
suffix:semicolon
DECL|member|device
r_char
id|device
(braket
l_int|200
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
