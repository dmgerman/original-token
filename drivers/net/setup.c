multiline_comment|/*&n; *&t;New style setup code for the network devices&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/netlink.h&gt;
r_extern
r_int
id|mkiss_init_ctrl_dev
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ppp_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|slip_init_ctrl_dev
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|strip_init_ctrl_dev
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|x25_asy_init_ctrl_dev
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|slhc_install
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|dmascc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|yam_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|awc4500_pci_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|awc4500_isa_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|awc4500_pnp_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|awc4500_365_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|arcnet_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|cpm_enet_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|dlci_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|lapbeth_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|sdla_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|sdla_c_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|abyss_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|madgemc_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|tms_pci_probe
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Pad device name to IFNAMSIZ=16. F.e. __PAD6 is tring of 9 zeros. */
DECL|macro|__PAD6
mdefine_line|#define __PAD6 &quot;&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&bslash;0&quot;
DECL|macro|__PAD5
mdefine_line|#define __PAD5 __PAD6 &quot;&bslash;0&quot;
DECL|macro|__PAD4
mdefine_line|#define __PAD4 __PAD5 &quot;&bslash;0&quot;
DECL|macro|__PAD3
mdefine_line|#define __PAD3 __PAD4 &quot;&bslash;0&quot;
DECL|macro|__PAD2
mdefine_line|#define __PAD2 __PAD3 &quot;&bslash;0&quot;
multiline_comment|/*&n; *&t;Devices in this list must do new style probing. That is they must&n; *&t;allocate their own device objects and do their own bus scans.&n; */
DECL|struct|net_probe
r_struct
id|net_probe
(brace
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* non-zero if autoprobe has failed */
)brace
suffix:semicolon
DECL|variable|__initdata
r_struct
id|net_probe
id|pci_probes
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/*&n;&t; *&t;Early setup devices&n;&t; */
macro_line|#if defined(CONFIG_DMASCC)
(brace
id|dmascc_init
comma
l_int|0
)brace
comma
macro_line|#endif&t;
macro_line|#if defined(CONFIG_DLCI)
(brace
id|dlci_setup
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#if defined(CONFIG_SDLA)
(brace
id|sdla_c_setup
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#if defined(CONFIG_LAPBETHER)
(brace
id|lapbeth_init
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#if defined(CONFIG_ARCNET)
(brace
id|arcnet_init
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#if defined(CONFIG_8xx)
(brace
id|cpm_enet_init
comma
l_int|0
)brace
comma
macro_line|#endif
multiline_comment|/*&n;&t; *&t;SLHC if present needs attaching so other people see it&n;&t; *&t;even if not opened.&n;&t; */
macro_line|#ifdef CONFIG_INET&t; 
macro_line|#if (defined(CONFIG_SLIP) &amp;&amp; defined(CONFIG_SLIP_COMPRESSED)) &bslash;&n;&t; || defined(CONFIG_PPP) &bslash;&n;    || (defined(CONFIG_ISDN) &amp;&amp; defined(CONFIG_ISDN_PPP))
(brace
id|slhc_install
comma
l_int|0
)brace
comma
macro_line|#endif&t;
macro_line|#endif
multiline_comment|/*&n;*&n;*&t;Wireless non-HAM&n;*&n;*/
macro_line|#ifdef CONFIG_AIRONET4500_NONCS
macro_line|#ifdef CONFIG_AIRONET4500_PCI
(brace
id|awc4500_pci_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_AIRONET4500_PNP
(brace
id|awc4500_pnp_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; *&t;Amateur Radio Drivers&n; */
macro_line|#ifdef CONFIG_YAM
(brace
id|yam_init
comma
l_int|0
)brace
comma
macro_line|#endif&t;/* CONFIG_YAM */
multiline_comment|/*&n; *&t;Token Ring Drivers&n; */
macro_line|#ifdef CONFIG_ABYSS
(brace
id|abyss_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_MADGEMC
(brace
id|madgemc_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_TMSPCI
(brace
id|tms_pci_probe
comma
l_int|0
)brace
comma
macro_line|#endif
(brace
l_int|NULL
comma
l_int|0
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Run the updated device probes. These do not need a device passed&n; *&t;into them.&n; */
DECL|function|network_probe
r_static
r_void
id|__init
id|network_probe
c_func
(paren
r_void
)paren
(brace
r_struct
id|net_probe
op_star
id|p
op_assign
id|pci_probes
suffix:semicolon
r_while
c_loop
(paren
id|p-&gt;probe
op_ne
l_int|NULL
)paren
(brace
id|p-&gt;status
op_assign
id|p
op_member_access_from_pointer
id|probe
c_func
(paren
)paren
suffix:semicolon
id|p
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;Initialise the line discipline drivers&n; */
DECL|function|network_ldisc_init
r_static
r_void
id|__init
id|network_ldisc_init
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_SLIP)
id|slip_init_ctrl_dev
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_X25_ASY)
id|x25_asy_init_ctrl_dev
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_MKISS)
id|mkiss_init_ctrl_dev
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_STRIP)
id|strip_init_ctrl_dev
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_PPP)
id|ppp_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|appletalk_device_init
r_static
r_void
id|__init
id|appletalk_device_init
c_func
(paren
r_void
)paren
(brace
macro_line|#if defined(CONFIG_IPDDP)
r_extern
r_int
id|ipddp_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_struct
id|net_device
id|dev_ipddp
op_assign
(brace
l_string|&quot;ipddp0&quot;
id|__PAD6
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0x0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
id|ipddp_init
)brace
suffix:semicolon
id|dev_ipddp
dot
id|init
c_func
(paren
op_amp
id|dev_ipddp
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_IPDDP */
)brace
multiline_comment|/*&n; *&t;The loopback device is global so it can be directly referenced&n; *&t;by the network code.&n; */
r_extern
r_int
id|loopback_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
DECL|variable|loopback_dev
r_struct
id|net_device
id|loopback_dev
op_assign
(brace
l_string|&quot;lo&quot;
id|__PAD2
comma
multiline_comment|/* Software Loopback interface&t;&t;*/
l_int|0x0
comma
multiline_comment|/* recv memory end&t;&t;&t;*/
l_int|0x0
comma
multiline_comment|/* recv memory start&t;&t;&t;*/
l_int|0x0
comma
multiline_comment|/* memory end&t;&t;&t;&t;*/
l_int|0x0
comma
multiline_comment|/* memory start&t;&t;&t;&t;*/
l_int|0
comma
multiline_comment|/* base I/O address&t;&t;&t;*/
l_int|0
comma
multiline_comment|/* IRQ&t;&t;&t;&t;&t;*/
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* flags&t;&t;&t;&t;*/
l_int|NULL
comma
multiline_comment|/* next device&t;&t;&t;&t;*/
id|loopback_init
multiline_comment|/* loopback_init should set up the rest&t;*/
)brace
suffix:semicolon
DECL|function|special_device_init
r_static
r_void
id|special_device_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_DUMMY
(brace
r_extern
r_int
id|dummy_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_struct
id|net_device
id|dummy_dev
op_assign
(brace
l_string|&quot;dummy&quot;
id|__PAD5
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
id|dummy_init
comma
)brace
suffix:semicolon
id|register_netdev
c_func
(paren
op_amp
id|dummy_dev
)paren
suffix:semicolon
)brace
macro_line|#endif&t;
macro_line|#ifdef CONFIG_EQUALIZER
(brace
r_extern
r_int
id|eql_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_struct
id|net_device
id|eql_dev
op_assign
(brace
l_string|&quot;eql&quot;
id|__PAD3
comma
multiline_comment|/* Master device for IP traffic load balancing */
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
multiline_comment|/* recv end/start; mem end/start */
l_int|0
comma
multiline_comment|/* base I/O address */
l_int|0
comma
multiline_comment|/* IRQ */
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* flags */
l_int|NULL
comma
multiline_comment|/* next device */
id|eql_init
multiline_comment|/* set up the rest */
)brace
suffix:semicolon
id|register_netdev
c_func
(paren
op_amp
id|eql_dev
)paren
suffix:semicolon
)brace
macro_line|#endif&t;
macro_line|#ifdef CONFIG_APBIF
(brace
r_extern
r_int
id|bif_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_struct
id|net_device
id|bif_dev
op_assign
(brace
l_string|&quot;bif&quot;
id|__PAD3
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
id|bif_init
)brace
suffix:semicolon
id|register_netdev
c_func
(paren
op_amp
id|bif_dev
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_NET_SB1000
(brace
r_extern
r_int
id|sb1000_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_struct
id|net_device
id|sb1000_dev
op_assign
(brace
l_string|&quot;cm0&quot;
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
id|sb1000_probe
)brace
suffix:semicolon
id|register_netdev
c_func
(paren
op_amp
id|sb1000_dev
)paren
suffix:semicolon
)brace
macro_line|#endif
id|register_netdev
c_func
(paren
op_amp
id|loopback_dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Initialise network devices&n; */
DECL|function|net_device_init
r_void
id|__init
id|net_device_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Devices supporting the new probing API */
id|network_probe
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Line disciplines */
id|network_ldisc_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Appletalk */
id|appletalk_device_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Special devices */
id|special_device_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* That kicks off the legacy init functions */
)brace
eof
