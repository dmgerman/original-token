multiline_comment|/*&n; *    $Id: zorro.c,v 1.1.2.1 1998/06/07 23:21:02 geert Exp $&n; *&n; *    Zorro Expansion Device Names&n; *&n; *    Copyright (C) 1999-2000 Geert Uytterhoeven&n; *&n; *    This file is subject to the terms and conditions of the GNU General Public&n; *    License.  See the file COPYING in the main directory of this archive&n; *    for more details.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/zorro.h&gt;
multiline_comment|/*&n;     *  Just for reference, these are the boards we have a driver for in the&n;     *  kernel:&n;     *&n;     *  ZORRO_PROD_AMERISTAR_A2065&n;     *  ZORRO_PROD_BSC_FRAMEMASTER_II&n;     *  ZORRO_PROD_BSC_MULTIFACE_III&n;     *  ZORRO_PROD_BSC_OKTAGON_2008&n;     *  ZORRO_PROD_CBM_A2065_1&n;     *  ZORRO_PROD_CBM_A2065_2&n;     *  ZORRO_PROD_CBM_A4091_1&n;     *  ZORRO_PROD_CBM_A4091_2&n;     *  ZORRO_PROD_CBM_A590_A2091_1&n;     *  ZORRO_PROD_CBM_A590_A2091_2&n;     *  ZORRO_PROD_GVP_A1291&n;     *  ZORRO_PROD_GVP_A530_SCSI&n;     *  ZORRO_PROD_GVP_COMBO_030_R3_SCSI&n;     *  ZORRO_PROD_GVP_COMBO_030_R4_SCSI&n;     *  ZORRO_PROD_GVP_EGS_28_24_SPECTRUM_RAM&n;     *  ZORRO_PROD_GVP_EGS_28_24_SPECTRUM_REG&n;     *  ZORRO_PROD_GVP_GFORCE_030_SCSI&n;     *  ZORRO_PROD_GVP_GFORCE_040_060&n;     *  ZORRO_PROD_GVP_GFORCE_040_1&n;     *  ZORRO_PROD_GVP_GFORCE_040_SCSI_1&n;     *  ZORRO_PROD_GVP_IO_EXTENDER&n;     *  ZORRO_PROD_GVP_SERIES_II&n;     *  ZORRO_PROD_HELFRICH_PICCOLO_RAM&n;     *  ZORRO_PROD_HELFRICH_PICCOLO_REG&n;     *  ZORRO_PROD_HELFRICH_RAINBOW_II&n;     *  ZORRO_PROD_HELFRICH_SD64_RAM&n;     *  ZORRO_PROD_HELFRICH_SD64_REG&n;     *  ZORRO_PROD_HYDRA_SYSTEMS_AMIGANET&n;     *  ZORRO_PROD_INDIVIDUAL_COMPUTERS_BUDDHA&n;     *  ZORRO_PROD_INDIVIDUAL_COMPUTERS_CATWEASEL&n;     *  ZORRO_PROD_MACROSYSTEMS_RETINA_Z3&n;     *  ZORRO_PROD_MACROSYSTEMS_WARP_ENGINE_40xx&n;     *  ZORRO_PROD_PHASE5_BLIZZARD_1220_CYBERSTORM&n;     *  ZORRO_PROD_PHASE5_BLIZZARD_1230_II_FASTLANE_Z3_CYBERSCSI_CYBERSTORM060&n;     *  ZORRO_PROD_PHASE5_BLIZZARD_1230_IV_1260&n;     *  ZORRO_PROD_PHASE5_BLIZZARD_2060&n;     *  ZORRO_PROD_PHASE5_BLIZZARD_603E_PLUS&n;     *  ZORRO_PROD_PHASE5_CYBERSTORM_MK_II&n;     *  ZORRO_PROD_PHASE5_CYBERVISION64&n;     *  ZORRO_PROD_PHASE5_CYBERVISION64_3D&n;     *  ZORRO_PROD_VILLAGE_TRONIC_ARIADNE&n;     *  ZORRO_PROD_VILLAGE_TRONIC_ARIADNE2&n;     *  ZORRO_PROD_VILLAGE_TRONIC_PICASSO_II_II_PLUS_RAM&n;     *  ZORRO_PROD_VILLAGE_TRONIC_PICASSO_II_II_PLUS_REG&n;     *  ZORRO_PROD_VILLAGE_TRONIC_PICASSO_IV_Z3&n;     *&n;     *  And I guess these are automagically supported as well :-)&n;     *&n;     *  ZORRO_PROD_CBM_A560_RAM&n;     *  ZORRO_PROD_CBM_A590_A2052_A2058_A2091&n;     */
DECL|function|zorro_namedevice
r_void
id|__init
id|zorro_namedevice
c_func
(paren
r_struct
id|zorro_dev
op_star
id|dev
)paren
(brace
multiline_comment|/*&n;     *  Nah, we&squot;re not that stupid to put name databases in the kernel ;-)&n;     *  That&squot;s why we have zorroutils...&n;     */
id|sprintf
c_func
(paren
id|dev-&gt;name
comma
l_string|&quot;Zorro device %08x&quot;
comma
id|dev-&gt;id
)paren
suffix:semicolon
)brace
eof
