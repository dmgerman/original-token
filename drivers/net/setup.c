multiline_comment|/*&n; *&t;New style setup code for the network devices&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/netlink.h&gt;
r_extern
r_int
id|plip_init
c_func
(paren
r_void
)paren
suffix:semicolon
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
id|bpq_init
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
id|scc_init
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
id|acenic_probe
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
id|bigmac_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|bmac_probe
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
id|oaknet_init
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
id|dgrs_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|dmfe_reg_board
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|eepro100_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|epic100_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|happy_meal_probe
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
id|mace_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|myri_sbus_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ncr885e_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ne2k_pci_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|pcnet32_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|qec_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|rcpci_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|rr_hippi_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|rtl8139_probe
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
id|sis900_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|skge_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|sparc_lance_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|starfire_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|tc59x_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|tulip_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|via_rhine_probe
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|yellowfin_probe
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
macro_line|#if defined(CONFIG_SCC)
(brace
id|scc_init
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#if defined(CONFIG_DMASCC)
(brace
id|dmascc_init
comma
l_int|0
)brace
comma
macro_line|#endif&t;
macro_line|#if defined(CONFIG_BPQETHER)
(brace
id|bpq_init
comma
l_int|0
)brace
comma
macro_line|#endif
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
id|sdla_setup
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
macro_line|#if defined(CONFIG_PLIP)
(brace
id|plip_init
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
multiline_comment|/*&n; *&t;HIPPI&n; */
macro_line|#ifdef CONFIG_ROADRUNNER
(brace
id|rr_hippi_probe
comma
l_int|0
)brace
comma
macro_line|#endif
multiline_comment|/*&n; *&t;ETHERNET&n; */
multiline_comment|/*&n; *&t;SBUS Ethernet&n; */
macro_line|#ifdef CONFIG_HAPPYMEAL
(brace
id|happy_meal_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SUNLANCE
(brace
id|sparc_lance_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SUNQE
(brace
id|qec_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SUNBMAC
(brace
id|bigmac_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_MYRI_SBUS
(brace
id|myri_sbus_probe
comma
l_int|0
)brace
comma
macro_line|#endif
multiline_comment|/*&n; *&t;PowerPC Mainboard&n; */
macro_line|#ifdef CONFIG_MACE
(brace
id|mace_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_BMAC
(brace
id|bmac_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_NCR885E
(brace
id|ncr885e_probe
comma
l_int|0
)brace
comma
macro_line|#endif
multiline_comment|/*&n; *&t;IBM &quot;Oak&quot; Evaluation board&n; */
macro_line|#ifdef&t;CONFIG_OAKNET
(brace
id|oaknet_init
comma
l_int|0
)brace
comma
macro_line|#endif
multiline_comment|/*&n; *&t;PCI Ethernet&n; */
macro_line|#ifdef CONFIG_DGRS
(brace
id|dgrs_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_RCPCI
(brace
id|rcpci_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_VORTEX
(brace
id|tc59x_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_NE2K_PCI
(brace
id|ne2k_pci_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_PCNET32
(brace
id|pcnet32_probe
comma
l_int|0
)brace
comma
macro_line|#endif&t;
macro_line|#ifdef CONFIG_EEXPRESS_PRO100&t;/* Intel EtherExpress Pro/100 */
(brace
id|eepro100_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_DEC_ELCP 
(brace
id|tulip_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_EPIC100
(brace
id|epic100_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_RTL8139
(brace
id|rtl8139_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SIS900
(brace
id|sis900_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_DM9102
(brace
id|dmfe_reg_board
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_YELLOWFIN
(brace
id|yellowfin_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ACENIC
(brace
id|acenic_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SK98LIN
(brace
id|skge_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_VIA_RHINE
(brace
id|via_rhine_probe
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_ADAPTEC_STARFIRE
(brace
id|starfire_probe
comma
l_int|0
)brace
comma
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
