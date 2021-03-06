multiline_comment|/*&n; * Definitions for accessing the Feature Control Register (FCR)&n; * on Power Macintoshes and similar machines.  The FCR lets us&n; * enable/disable, reset, and power up/down various peripherals.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1998 Paul Mackerras &amp;&n; *                    Ben. Herrenschmidt.&n; *&n; * &n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASM_PPC_FEATURE_H
DECL|macro|__ASM_PPC_FEATURE_H
mdefine_line|#define __ASM_PPC_FEATURE_H
multiline_comment|/*&n; * The FCR selector for particular features vary somewhat between&n; * different machines.  So we abstract a list of features here&n; * and let the feature_* routines map them to the actual bits.&n; */
DECL|enum|system_feature
r_enum
id|system_feature
(brace
DECL|enumerator|FEATURE_null
id|FEATURE_null
comma
DECL|enumerator|FEATURE_Serial_reset
id|FEATURE_Serial_reset
comma
DECL|enumerator|FEATURE_Serial_enable
id|FEATURE_Serial_enable
comma
DECL|enumerator|FEATURE_Serial_IO_A
id|FEATURE_Serial_IO_A
comma
DECL|enumerator|FEATURE_Serial_IO_B
id|FEATURE_Serial_IO_B
comma
DECL|enumerator|FEATURE_SWIM3_enable
id|FEATURE_SWIM3_enable
comma
DECL|enumerator|FEATURE_MESH_enable
id|FEATURE_MESH_enable
comma
DECL|enumerator|FEATURE_IDE0_enable
id|FEATURE_IDE0_enable
comma
multiline_comment|/* Internal IDE */
DECL|enumerator|FEATURE_IDE0_reset
id|FEATURE_IDE0_reset
comma
multiline_comment|/* Internal IDE */
DECL|enumerator|FEATURE_IOBUS_enable
id|FEATURE_IOBUS_enable
comma
multiline_comment|/* Internal IDE */
DECL|enumerator|FEATURE_Mediabay_reset
id|FEATURE_Mediabay_reset
comma
DECL|enumerator|FEATURE_Mediabay_power
id|FEATURE_Mediabay_power
comma
DECL|enumerator|FEATURE_Mediabay_PCI_enable
id|FEATURE_Mediabay_PCI_enable
comma
DECL|enumerator|FEATURE_IDE1_enable
id|FEATURE_IDE1_enable
comma
multiline_comment|/* MediaBay IDE */
DECL|enumerator|FEATURE_IDE1_reset
id|FEATURE_IDE1_reset
comma
multiline_comment|/* MediaBay IDE */
DECL|enumerator|FEATURE_Mediabay_floppy_enable
id|FEATURE_Mediabay_floppy_enable
comma
DECL|enumerator|FEATURE_BMac_reset
id|FEATURE_BMac_reset
comma
DECL|enumerator|FEATURE_BMac_IO_enable
id|FEATURE_BMac_IO_enable
comma
DECL|enumerator|FEATURE_Modem_power
id|FEATURE_Modem_power
comma
DECL|enumerator|FEATURE_Slow_SCC_PCLK
id|FEATURE_Slow_SCC_PCLK
comma
DECL|enumerator|FEATURE_Sound_power
id|FEATURE_Sound_power
comma
DECL|enumerator|FEATURE_Sound_CLK_enable
id|FEATURE_Sound_CLK_enable
comma
DECL|enumerator|FEATURE_IDE2_enable
id|FEATURE_IDE2_enable
comma
DECL|enumerator|FEATURE_IDE2_reset
id|FEATURE_IDE2_reset
comma
DECL|enumerator|FEATURE_Mediabay_IDE_switch
id|FEATURE_Mediabay_IDE_switch
comma
multiline_comment|/* MB IDE bus switch */
DECL|enumerator|FEATURE_Mediabay_content
id|FEATURE_Mediabay_content
comma
multiline_comment|/* MB content indicator enable */
DECL|enumerator|FEATURE_Airport_reset
id|FEATURE_Airport_reset
comma
multiline_comment|/* Is it actually a reset ? */
DECL|enumerator|FEATURE_last
id|FEATURE_last
comma
)brace
suffix:semicolon
multiline_comment|/* Note about the device parameter: Each device gives it&squot;s own entry. If NULL,&n;   the feature function will just do nothing and return -EINVAL.&n;   The feature management will walk up the device tree until in reaches a recognized&n;   chip for which features can be changed and it will then apply the necessary&n;   features to that chip. If it&squot;s not found, -ENODEV is returned.&n;   Note also that feature_test/set/clear are interrupt-safe provided that they are&n;   called _after_ feature_init() is completed.&n; */
multiline_comment|/* Test whether a particular feature is enabled. May return -ENODEV*/
r_extern
r_int
id|feature_test
c_func
(paren
r_struct
id|device_node
op_star
id|device
comma
r_enum
id|system_feature
id|f
)paren
suffix:semicolon
multiline_comment|/* Set a particular feature. Returns 0 or -ENODEV */
r_extern
r_int
id|feature_set
c_func
(paren
r_struct
id|device_node
op_star
id|device
comma
r_enum
id|system_feature
id|f
)paren
suffix:semicolon
multiline_comment|/* Clear a particular feature */
r_extern
r_int
id|feature_clear
c_func
(paren
r_struct
id|device_node
op_star
id|device
comma
r_enum
id|system_feature
id|f
)paren
suffix:semicolon
multiline_comment|/* Initialize feature stuff */
r_extern
r_void
id|feature_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Additional functions related to Core99 machines&n; */
r_extern
r_void
id|feature_set_gmac_power
c_func
(paren
r_struct
id|device_node
op_star
id|device
comma
r_int
id|power
)paren
suffix:semicolon
multiline_comment|/* use constants in KeyLargo.h for the reset parameter */
r_extern
r_void
id|feature_set_gmac_phy_reset
c_func
(paren
r_struct
id|device_node
op_star
id|device
comma
r_int
id|reset
)paren
suffix:semicolon
r_extern
r_void
id|feature_set_usb_power
c_func
(paren
r_struct
id|device_node
op_star
id|device
comma
r_int
id|power
)paren
suffix:semicolon
r_extern
r_void
id|feature_set_firewire_power
c_func
(paren
r_struct
id|device_node
op_star
id|device
comma
r_int
id|power
)paren
suffix:semicolon
multiline_comment|/*&n; * Sleep related functions. At term, they should be high-priority notifiers&n; */
r_extern
r_void
id|feature_prepare_for_sleep
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|feature_wake_up
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __ASM_PPC_FEATURE_H */
macro_line|#endif /* __KERNEL__ */
eof
