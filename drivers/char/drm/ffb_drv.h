multiline_comment|/* $Id: ffb_drv.h,v 1.1 2000/06/01 04:24:39 davem Exp $&n; * ffb_drv.h: Creator/Creator3D direct rendering driver.&n; *&n; * Copyright (C) 2000 David S. Miller (davem@redhat.com)&n; */
multiline_comment|/* Auxilliary clips. */
r_typedef
r_struct
(brace
DECL|member|min
r_volatile
r_int
r_int
id|min
suffix:semicolon
DECL|member|max
r_volatile
r_int
r_int
id|max
suffix:semicolon
DECL|typedef|ffb_auxclip
DECL|typedef|ffb_auxclipPtr
)brace
id|ffb_auxclip
comma
op_star
id|ffb_auxclipPtr
suffix:semicolon
multiline_comment|/* FFB register set. */
DECL|struct|_ffb_fbc
r_typedef
r_struct
id|_ffb_fbc
(brace
multiline_comment|/* Next vertex registers, on the right we list which drawops&n;&t; * use said register and the logical name the register has in&n;&t; * that context.&n;&t; */
multiline_comment|/* DESCRIPTION&t;&t;DRAWOP(NAME)&t;*/
DECL|member|pad1
multiline_comment|/*0x00*/
r_int
r_int
id|pad1
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Reserved&t;&t;&t;&t;*/
DECL|member|alpha
multiline_comment|/*0x0c*/
r_volatile
r_int
r_int
id|alpha
suffix:semicolon
multiline_comment|/* ALPHA Transparency&t;&t;&t;*/
DECL|member|red
multiline_comment|/*0x10*/
r_volatile
r_int
r_int
id|red
suffix:semicolon
multiline_comment|/* RED&t;&t;&t;&t;&t;*/
DECL|member|green
multiline_comment|/*0x14*/
r_volatile
r_int
r_int
id|green
suffix:semicolon
multiline_comment|/* GREEN&t;&t;&t;&t;*/
DECL|member|blue
multiline_comment|/*0x18*/
r_volatile
r_int
r_int
id|blue
suffix:semicolon
multiline_comment|/* BLUE&t;&t;&t;&t;&t;*/
DECL|member|z
multiline_comment|/*0x1c*/
r_volatile
r_int
r_int
id|z
suffix:semicolon
multiline_comment|/* DEPTH&t;&t;&t;&t;*/
DECL|member|y
multiline_comment|/*0x20*/
r_volatile
r_int
r_int
id|y
suffix:semicolon
multiline_comment|/* Y&t;&t;&t;triangle(DOYF)&t;*/
multiline_comment|/*                      aadot(DYF)&t;*/
multiline_comment|/*                      ddline(DYF)&t;*/
multiline_comment|/*                      aaline(DYF)&t;*/
DECL|member|x
multiline_comment|/*0x24*/
r_volatile
r_int
r_int
id|x
suffix:semicolon
multiline_comment|/* X&t;&t;&t;triangle(DOXF)&t;*/
multiline_comment|/*                      aadot(DXF)&t;*/
multiline_comment|/*                      ddline(DXF)&t;*/
multiline_comment|/*                      aaline(DXF)&t;*/
DECL|member|pad2
multiline_comment|/*0x28*/
r_int
r_int
id|pad2
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Reserved&t;&t;&t;&t;*/
DECL|member|ryf
multiline_comment|/*0x30*/
r_volatile
r_int
r_int
id|ryf
suffix:semicolon
multiline_comment|/* Y (alias to DOYF)&t;ddline(RYF)&t;*/
multiline_comment|/*&t;&t;&t;aaline(RYF)&t;*/
multiline_comment|/*&t;&t;&t;triangle(RYF)&t;*/
DECL|member|rxf
multiline_comment|/*0x34*/
r_volatile
r_int
r_int
id|rxf
suffix:semicolon
multiline_comment|/* X&t;&t;&t;ddline(RXF)&t;*/
multiline_comment|/*&t;&t;&t;aaline(RXF)&t;*/
multiline_comment|/*&t;&t;&t;triangle(RXF)&t;*/
DECL|member|pad3
multiline_comment|/*0x38*/
r_int
r_int
id|pad3
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Reserved&t;&t;&t;&t;*/
DECL|member|dmyf
multiline_comment|/*0x40*/
r_volatile
r_int
r_int
id|dmyf
suffix:semicolon
multiline_comment|/* Y (alias to DOYF)&t;triangle(DMYF)&t;*/
DECL|member|dmxf
multiline_comment|/*0x44*/
r_volatile
r_int
r_int
id|dmxf
suffix:semicolon
multiline_comment|/* X&t;&t;&t;triangle(DMXF)&t;*/
DECL|member|pad4
multiline_comment|/*0x48*/
r_int
r_int
id|pad4
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Reserved&t;&t;&t;&t;*/
DECL|member|ebyi
multiline_comment|/*0x50*/
r_volatile
r_int
r_int
id|ebyi
suffix:semicolon
multiline_comment|/* Y (alias to RYI)&t;polygon(EBYI)&t;*/
DECL|member|ebxi
multiline_comment|/*0x54*/
r_volatile
r_int
r_int
id|ebxi
suffix:semicolon
multiline_comment|/* X&t;&t;&t;polygon(EBXI)&t;*/
DECL|member|pad5
multiline_comment|/*0x58*/
r_int
r_int
id|pad5
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Reserved&t;&t;&t;&t;*/
DECL|member|by
multiline_comment|/*0x60*/
r_volatile
r_int
r_int
id|by
suffix:semicolon
multiline_comment|/* Y&t;&t;&t;brline(RYI)&t;*/
multiline_comment|/*&t;&t;&t;fastfill(OP)&t;*/
multiline_comment|/*&t;&t;&t;polygon(YI)&t;*/
multiline_comment|/*&t;&t;&t;rectangle(YI)&t;*/
multiline_comment|/*&t;&t;&t;bcopy(SRCY)&t;*/
multiline_comment|/*&t;&t;&t;vscroll(SRCY)&t;*/
DECL|member|bx
multiline_comment|/*0x64*/
r_volatile
r_int
r_int
id|bx
suffix:semicolon
multiline_comment|/* X&t;&t;&t;brline(RXI)&t;*/
multiline_comment|/*&t;&t;&t;polygon(XI)&t;*/
multiline_comment|/*&t;&t;&t;rectangle(XI)&t;*/
multiline_comment|/*&t;&t;&t;bcopy(SRCX)&t;*/
multiline_comment|/*&t;&t;&t;vscroll(SRCX)&t;*/
multiline_comment|/*&t;&t;&t;fastfill(GO)&t;*/
DECL|member|dy
multiline_comment|/*0x68*/
r_volatile
r_int
r_int
id|dy
suffix:semicolon
multiline_comment|/* destination Y&t;fastfill(DSTY)&t;*/
multiline_comment|/*&t;&t;&t;bcopy(DSRY)&t;*/
multiline_comment|/*&t;&t;&t;vscroll(DSRY)&t;*/
DECL|member|dx
multiline_comment|/*0x6c*/
r_volatile
r_int
r_int
id|dx
suffix:semicolon
multiline_comment|/* destination X&t;fastfill(DSTX)&t;*/
multiline_comment|/*&t;&t;&t;bcopy(DSTX)&t;*/
multiline_comment|/*&t;&t;&t;vscroll(DSTX)&t;*/
DECL|member|bh
multiline_comment|/*0x70*/
r_volatile
r_int
r_int
id|bh
suffix:semicolon
multiline_comment|/* Y (alias to RYI)&t;brline(DYI)&t;*/
multiline_comment|/*&t;&t;&t;dot(DYI)&t;*/
multiline_comment|/*&t;&t;&t;polygon(ETYI)&t;*/
multiline_comment|/* Height&t;&t;fastfill(H)&t;*/
multiline_comment|/*&t;&t;&t;bcopy(H)&t;*/
multiline_comment|/*&t;&t;&t;vscroll(H)&t;*/
multiline_comment|/* Y count&t;&t;fastfill(NY)&t;*/
DECL|member|bw
multiline_comment|/*0x74*/
r_volatile
r_int
r_int
id|bw
suffix:semicolon
multiline_comment|/* X&t;&t;&t;dot(DXI)&t;*/
multiline_comment|/*&t;&t;&t;brline(DXI)&t;*/
multiline_comment|/*&t;&t;&t;polygon(ETXI)&t;*/
multiline_comment|/*&t;&t;&t;fastfill(W)&t;*/
multiline_comment|/*&t;&t;&t;bcopy(W)&t;*/
multiline_comment|/*&t;&t;&t;vscroll(W)&t;*/
multiline_comment|/*&t;&t;&t;fastfill(NX)&t;*/
DECL|member|pad6
multiline_comment|/*0x78*/
r_int
r_int
id|pad6
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Reserved&t;&t;&t;&t;*/
DECL|member|pad7
multiline_comment|/*0x80*/
r_int
r_int
id|pad7
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Reserved&t;&t;&t;&t;*/
multiline_comment|/* Setup Unit&squot;s vertex state register */
DECL|member|suvtx
multiline_comment|/*100*/
r_volatile
r_int
r_int
id|suvtx
suffix:semicolon
DECL|member|pad8
multiline_comment|/*104*/
r_int
r_int
id|pad8
(braket
l_int|63
)braket
suffix:semicolon
multiline_comment|/* Reserved&t;&t;&t;&t;*/
multiline_comment|/* Frame Buffer Control Registers */
DECL|member|ppc
multiline_comment|/*200*/
r_volatile
r_int
r_int
id|ppc
suffix:semicolon
multiline_comment|/* Pixel Processor Control&t;&t;*/
DECL|member|wid
multiline_comment|/*204*/
r_volatile
r_int
r_int
id|wid
suffix:semicolon
multiline_comment|/* Current WID&t;&t;&t;&t;*/
DECL|member|fg
multiline_comment|/*208*/
r_volatile
r_int
r_int
id|fg
suffix:semicolon
multiline_comment|/* FG data&t;&t;&t;&t;*/
DECL|member|bg
multiline_comment|/*20c*/
r_volatile
r_int
r_int
id|bg
suffix:semicolon
multiline_comment|/* BG data&t;&t;&t;&t;*/
DECL|member|consty
multiline_comment|/*210*/
r_volatile
r_int
r_int
id|consty
suffix:semicolon
multiline_comment|/* Constant Y&t;&t;&t;&t;*/
DECL|member|constz
multiline_comment|/*214*/
r_volatile
r_int
r_int
id|constz
suffix:semicolon
multiline_comment|/* Constant Z&t;&t;&t;&t;*/
DECL|member|xclip
multiline_comment|/*218*/
r_volatile
r_int
r_int
id|xclip
suffix:semicolon
multiline_comment|/* X Clip&t;&t;&t;&t;*/
DECL|member|dcss
multiline_comment|/*21c*/
r_volatile
r_int
r_int
id|dcss
suffix:semicolon
multiline_comment|/* Depth Cue Scale Slope&t;&t;*/
DECL|member|vclipmin
multiline_comment|/*220*/
r_volatile
r_int
r_int
id|vclipmin
suffix:semicolon
multiline_comment|/* Viewclip XY Min Bounds&t;&t;*/
DECL|member|vclipmax
multiline_comment|/*224*/
r_volatile
r_int
r_int
id|vclipmax
suffix:semicolon
multiline_comment|/* Viewclip XY Max Bounds&t;&t;*/
DECL|member|vclipzmin
multiline_comment|/*228*/
r_volatile
r_int
r_int
id|vclipzmin
suffix:semicolon
multiline_comment|/* Viewclip Z Min Bounds&t;&t;*/
DECL|member|vclipzmax
multiline_comment|/*22c*/
r_volatile
r_int
r_int
id|vclipzmax
suffix:semicolon
multiline_comment|/* Viewclip Z Max Bounds&t;&t;*/
DECL|member|dcsf
multiline_comment|/*230*/
r_volatile
r_int
r_int
id|dcsf
suffix:semicolon
multiline_comment|/* Depth Cue Scale Front Bound&t;&t;*/
DECL|member|dcsb
multiline_comment|/*234*/
r_volatile
r_int
r_int
id|dcsb
suffix:semicolon
multiline_comment|/* Depth Cue Scale Back Bound&t;&t;*/
DECL|member|dczf
multiline_comment|/*238*/
r_volatile
r_int
r_int
id|dczf
suffix:semicolon
multiline_comment|/* Depth Cue Z Front&t;&t;&t;*/
DECL|member|dczb
multiline_comment|/*23c*/
r_volatile
r_int
r_int
id|dczb
suffix:semicolon
multiline_comment|/* Depth Cue Z Back&t;&t;&t;*/
DECL|member|pad9
multiline_comment|/*240*/
r_int
r_int
id|pad9
suffix:semicolon
multiline_comment|/* Reserved&t;&t;&t;&t;*/
DECL|member|blendc
multiline_comment|/*244*/
r_volatile
r_int
r_int
id|blendc
suffix:semicolon
multiline_comment|/* Alpha Blend Control&t;&t;&t;*/
DECL|member|blendc1
multiline_comment|/*248*/
r_volatile
r_int
r_int
id|blendc1
suffix:semicolon
multiline_comment|/* Alpha Blend Color 1&t;&t;&t;*/
DECL|member|blendc2
multiline_comment|/*24c*/
r_volatile
r_int
r_int
id|blendc2
suffix:semicolon
multiline_comment|/* Alpha Blend Color 2&t;&t;&t;*/
DECL|member|fbramitc
multiline_comment|/*250*/
r_volatile
r_int
r_int
id|fbramitc
suffix:semicolon
multiline_comment|/* FB RAM Interleave Test Control&t;*/
DECL|member|fbc
multiline_comment|/*254*/
r_volatile
r_int
r_int
id|fbc
suffix:semicolon
multiline_comment|/* Frame Buffer Control&t;&t;&t;*/
DECL|member|rop
multiline_comment|/*258*/
r_volatile
r_int
r_int
id|rop
suffix:semicolon
multiline_comment|/* Raster OPeration&t;&t;&t;*/
DECL|member|cmp
multiline_comment|/*25c*/
r_volatile
r_int
r_int
id|cmp
suffix:semicolon
multiline_comment|/* Frame Buffer Compare&t;&t;&t;*/
DECL|member|matchab
multiline_comment|/*260*/
r_volatile
r_int
r_int
id|matchab
suffix:semicolon
multiline_comment|/* Buffer AB Match Mask&t;&t;&t;*/
DECL|member|matchc
multiline_comment|/*264*/
r_volatile
r_int
r_int
id|matchc
suffix:semicolon
multiline_comment|/* Buffer C(YZ) Match Mask&t;&t;*/
DECL|member|magnab
multiline_comment|/*268*/
r_volatile
r_int
r_int
id|magnab
suffix:semicolon
multiline_comment|/* Buffer AB Magnitude Mask&t;&t;*/
DECL|member|magnc
multiline_comment|/*26c*/
r_volatile
r_int
r_int
id|magnc
suffix:semicolon
multiline_comment|/* Buffer C(YZ) Magnitude Mask&t;&t;*/
DECL|member|fbcfg0
multiline_comment|/*270*/
r_volatile
r_int
r_int
id|fbcfg0
suffix:semicolon
multiline_comment|/* Frame Buffer Config 0&t;&t;*/
DECL|member|fbcfg1
multiline_comment|/*274*/
r_volatile
r_int
r_int
id|fbcfg1
suffix:semicolon
multiline_comment|/* Frame Buffer Config 1&t;&t;*/
DECL|member|fbcfg2
multiline_comment|/*278*/
r_volatile
r_int
r_int
id|fbcfg2
suffix:semicolon
multiline_comment|/* Frame Buffer Config 2&t;&t;*/
DECL|member|fbcfg3
multiline_comment|/*27c*/
r_volatile
r_int
r_int
id|fbcfg3
suffix:semicolon
multiline_comment|/* Frame Buffer Config 3&t;&t;*/
DECL|member|ppcfg
multiline_comment|/*280*/
r_volatile
r_int
r_int
id|ppcfg
suffix:semicolon
multiline_comment|/* Pixel Processor Config&t;&t;*/
DECL|member|pick
multiline_comment|/*284*/
r_volatile
r_int
r_int
id|pick
suffix:semicolon
multiline_comment|/* Picking Control&t;&t;&t;*/
DECL|member|fillmode
multiline_comment|/*288*/
r_volatile
r_int
r_int
id|fillmode
suffix:semicolon
multiline_comment|/* FillMode&t;&t;&t;&t;*/
DECL|member|fbramwac
multiline_comment|/*28c*/
r_volatile
r_int
r_int
id|fbramwac
suffix:semicolon
multiline_comment|/* FB RAM Write Address Control&t;&t;*/
DECL|member|pmask
multiline_comment|/*290*/
r_volatile
r_int
r_int
id|pmask
suffix:semicolon
multiline_comment|/* RGB PlaneMask&t;&t;&t;*/
DECL|member|xpmask
multiline_comment|/*294*/
r_volatile
r_int
r_int
id|xpmask
suffix:semicolon
multiline_comment|/* X PlaneMask&t;&t;&t;&t;*/
DECL|member|ypmask
multiline_comment|/*298*/
r_volatile
r_int
r_int
id|ypmask
suffix:semicolon
multiline_comment|/* Y PlaneMask&t;&t;&t;&t;*/
DECL|member|zpmask
multiline_comment|/*29c*/
r_volatile
r_int
r_int
id|zpmask
suffix:semicolon
multiline_comment|/* Z PlaneMask&t;&t;&t;&t;*/
DECL|member|auxclip
multiline_comment|/*2a0*/
id|ffb_auxclip
id|auxclip
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Auxilliary Viewport Clip&t;&t;*/
multiline_comment|/* New 3dRAM III support regs */
DECL|member|rawblend2
multiline_comment|/*2c0*/
r_volatile
r_int
r_int
id|rawblend2
suffix:semicolon
DECL|member|rawpreblend
multiline_comment|/*2c4*/
r_volatile
r_int
r_int
id|rawpreblend
suffix:semicolon
DECL|member|rawstencil
multiline_comment|/*2c8*/
r_volatile
r_int
r_int
id|rawstencil
suffix:semicolon
DECL|member|rawstencilctl
multiline_comment|/*2cc*/
r_volatile
r_int
r_int
id|rawstencilctl
suffix:semicolon
DECL|member|threedram1
multiline_comment|/*2d0*/
r_volatile
r_int
r_int
id|threedram1
suffix:semicolon
DECL|member|threedram2
multiline_comment|/*2d4*/
r_volatile
r_int
r_int
id|threedram2
suffix:semicolon
DECL|member|passin
multiline_comment|/*2d8*/
r_volatile
r_int
r_int
id|passin
suffix:semicolon
DECL|member|rawclrdepth
multiline_comment|/*2dc*/
r_volatile
r_int
r_int
id|rawclrdepth
suffix:semicolon
DECL|member|rawpmask
multiline_comment|/*2e0*/
r_volatile
r_int
r_int
id|rawpmask
suffix:semicolon
DECL|member|rawcsrc
multiline_comment|/*2e4*/
r_volatile
r_int
r_int
id|rawcsrc
suffix:semicolon
DECL|member|rawmatch
multiline_comment|/*2e8*/
r_volatile
r_int
r_int
id|rawmatch
suffix:semicolon
DECL|member|rawmagn
multiline_comment|/*2ec*/
r_volatile
r_int
r_int
id|rawmagn
suffix:semicolon
DECL|member|rawropblend
multiline_comment|/*2f0*/
r_volatile
r_int
r_int
id|rawropblend
suffix:semicolon
DECL|member|rawcmp
multiline_comment|/*2f4*/
r_volatile
r_int
r_int
id|rawcmp
suffix:semicolon
DECL|member|rawwac
multiline_comment|/*2f8*/
r_volatile
r_int
r_int
id|rawwac
suffix:semicolon
DECL|member|fbramid
multiline_comment|/*2fc*/
r_volatile
r_int
r_int
id|fbramid
suffix:semicolon
DECL|member|drawop
multiline_comment|/*300*/
r_volatile
r_int
r_int
id|drawop
suffix:semicolon
multiline_comment|/* Draw OPeration&t;&t;&t;*/
DECL|member|pad10
multiline_comment|/*304*/
r_int
r_int
id|pad10
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Reserved&t;&t;&t;&t;*/
DECL|member|lpat
multiline_comment|/*30c*/
r_volatile
r_int
r_int
id|lpat
suffix:semicolon
multiline_comment|/* Line Pattern control&t;&t;&t;*/
DECL|member|pad11
multiline_comment|/*310*/
r_int
r_int
id|pad11
suffix:semicolon
multiline_comment|/* Reserved&t;&t;&t;&t;*/
DECL|member|fontxy
multiline_comment|/*314*/
r_volatile
r_int
r_int
id|fontxy
suffix:semicolon
multiline_comment|/* XY Font coordinate&t;&t;&t;*/
DECL|member|fontw
multiline_comment|/*318*/
r_volatile
r_int
r_int
id|fontw
suffix:semicolon
multiline_comment|/* Font Width&t;&t;&t;&t;*/
DECL|member|fontinc
multiline_comment|/*31c*/
r_volatile
r_int
r_int
id|fontinc
suffix:semicolon
multiline_comment|/* Font Increment&t;&t;&t;*/
DECL|member|font
multiline_comment|/*320*/
r_volatile
r_int
r_int
id|font
suffix:semicolon
multiline_comment|/* Font bits&t;&t;&t;&t;*/
DECL|member|pad12
multiline_comment|/*324*/
r_int
r_int
id|pad12
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Reserved&t;&t;&t;&t;*/
DECL|member|blend2
multiline_comment|/*330*/
r_volatile
r_int
r_int
id|blend2
suffix:semicolon
DECL|member|preblend
multiline_comment|/*334*/
r_volatile
r_int
r_int
id|preblend
suffix:semicolon
DECL|member|stencil
multiline_comment|/*338*/
r_volatile
r_int
r_int
id|stencil
suffix:semicolon
DECL|member|stencilctl
multiline_comment|/*33c*/
r_volatile
r_int
r_int
id|stencilctl
suffix:semicolon
DECL|member|pad13
multiline_comment|/*340*/
r_int
r_int
id|pad13
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Reserved&t;&t;&t;&t;*/
DECL|member|dcss1
multiline_comment|/*350*/
r_volatile
r_int
r_int
id|dcss1
suffix:semicolon
multiline_comment|/* Depth Cue Scale Slope 1&t;&t;*/
DECL|member|dcss2
multiline_comment|/*354*/
r_volatile
r_int
r_int
id|dcss2
suffix:semicolon
multiline_comment|/* Depth Cue Scale Slope 2&t;&t;*/
DECL|member|dcss3
multiline_comment|/*358*/
r_volatile
r_int
r_int
id|dcss3
suffix:semicolon
multiline_comment|/* Depth Cue Scale Slope 3&t;&t;*/
DECL|member|widpmask
multiline_comment|/*35c*/
r_volatile
r_int
r_int
id|widpmask
suffix:semicolon
DECL|member|dcs2
multiline_comment|/*360*/
r_volatile
r_int
r_int
id|dcs2
suffix:semicolon
DECL|member|dcs3
multiline_comment|/*364*/
r_volatile
r_int
r_int
id|dcs3
suffix:semicolon
DECL|member|dcs4
multiline_comment|/*368*/
r_volatile
r_int
r_int
id|dcs4
suffix:semicolon
DECL|member|pad14
multiline_comment|/*36c*/
r_int
r_int
id|pad14
suffix:semicolon
multiline_comment|/* Reserved&t;&t;&t;&t;*/
DECL|member|dcd2
multiline_comment|/*370*/
r_volatile
r_int
r_int
id|dcd2
suffix:semicolon
DECL|member|dcd3
multiline_comment|/*374*/
r_volatile
r_int
r_int
id|dcd3
suffix:semicolon
DECL|member|dcd4
multiline_comment|/*378*/
r_volatile
r_int
r_int
id|dcd4
suffix:semicolon
DECL|member|pad15
multiline_comment|/*37c*/
r_int
r_int
id|pad15
suffix:semicolon
multiline_comment|/* Reserved&t;&t;&t;&t;*/
DECL|member|pattern
multiline_comment|/*380*/
r_volatile
r_int
r_int
id|pattern
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* area Pattern&t;&t;&t;&t;*/
DECL|member|pad16
multiline_comment|/*400*/
r_int
r_int
id|pad16
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Reserved&t;&t;&t;&t;*/
DECL|member|reset
multiline_comment|/*420*/
r_volatile
r_int
r_int
id|reset
suffix:semicolon
multiline_comment|/* chip RESET&t;&t;&t;&t;*/
DECL|member|pad17
multiline_comment|/*424*/
r_int
r_int
id|pad17
(braket
l_int|247
)braket
suffix:semicolon
multiline_comment|/* Reserved&t;&t;&t;&t;*/
DECL|member|devid
multiline_comment|/*800*/
r_volatile
r_int
r_int
id|devid
suffix:semicolon
multiline_comment|/* Device ID&t;&t;&t;&t;*/
DECL|member|pad18
multiline_comment|/*804*/
r_int
r_int
id|pad18
(braket
l_int|63
)braket
suffix:semicolon
multiline_comment|/* Reserved&t;&t;&t;&t;*/
DECL|member|ucsr
multiline_comment|/*900*/
r_volatile
r_int
r_int
id|ucsr
suffix:semicolon
multiline_comment|/* User Control &amp; Status Register&t;*/
DECL|member|pad19
multiline_comment|/*904*/
r_int
r_int
id|pad19
(braket
l_int|31
)braket
suffix:semicolon
multiline_comment|/* Reserved&t;&t;&t;&t;*/
DECL|member|mer
multiline_comment|/*980*/
r_volatile
r_int
r_int
id|mer
suffix:semicolon
multiline_comment|/* Mode Enable Register&t;&t;&t;*/
DECL|member|pad20
multiline_comment|/*984*/
r_int
r_int
id|pad20
(braket
l_int|1439
)braket
suffix:semicolon
multiline_comment|/* Reserved&t;&t;&t;&t;*/
DECL|typedef|ffb_fbc
DECL|typedef|ffb_fbcPtr
)brace
id|ffb_fbc
comma
op_star
id|ffb_fbcPtr
suffix:semicolon
DECL|struct|ffb_hw_context
r_struct
id|ffb_hw_context
(brace
DECL|member|is_2d_only
r_int
id|is_2d_only
suffix:semicolon
DECL|member|ppc
r_int
r_int
id|ppc
suffix:semicolon
DECL|member|wid
r_int
r_int
id|wid
suffix:semicolon
DECL|member|fg
r_int
r_int
id|fg
suffix:semicolon
DECL|member|bg
r_int
r_int
id|bg
suffix:semicolon
DECL|member|consty
r_int
r_int
id|consty
suffix:semicolon
DECL|member|constz
r_int
r_int
id|constz
suffix:semicolon
DECL|member|xclip
r_int
r_int
id|xclip
suffix:semicolon
DECL|member|dcss
r_int
r_int
id|dcss
suffix:semicolon
DECL|member|vclipmin
r_int
r_int
id|vclipmin
suffix:semicolon
DECL|member|vclipmax
r_int
r_int
id|vclipmax
suffix:semicolon
DECL|member|vclipzmin
r_int
r_int
id|vclipzmin
suffix:semicolon
DECL|member|vclipzmax
r_int
r_int
id|vclipzmax
suffix:semicolon
DECL|member|dcsf
r_int
r_int
id|dcsf
suffix:semicolon
DECL|member|dcsb
r_int
r_int
id|dcsb
suffix:semicolon
DECL|member|dczf
r_int
r_int
id|dczf
suffix:semicolon
DECL|member|dczb
r_int
r_int
id|dczb
suffix:semicolon
DECL|member|blendc
r_int
r_int
id|blendc
suffix:semicolon
DECL|member|blendc1
r_int
r_int
id|blendc1
suffix:semicolon
DECL|member|blendc2
r_int
r_int
id|blendc2
suffix:semicolon
DECL|member|fbc
r_int
r_int
id|fbc
suffix:semicolon
DECL|member|rop
r_int
r_int
id|rop
suffix:semicolon
DECL|member|cmp
r_int
r_int
id|cmp
suffix:semicolon
DECL|member|matchab
r_int
r_int
id|matchab
suffix:semicolon
DECL|member|matchc
r_int
r_int
id|matchc
suffix:semicolon
DECL|member|magnab
r_int
r_int
id|magnab
suffix:semicolon
DECL|member|magnc
r_int
r_int
id|magnc
suffix:semicolon
DECL|member|pmask
r_int
r_int
id|pmask
suffix:semicolon
DECL|member|xpmask
r_int
r_int
id|xpmask
suffix:semicolon
DECL|member|ypmask
r_int
r_int
id|ypmask
suffix:semicolon
DECL|member|zpmask
r_int
r_int
id|zpmask
suffix:semicolon
DECL|member|auxclip0min
r_int
r_int
id|auxclip0min
suffix:semicolon
DECL|member|auxclip0max
r_int
r_int
id|auxclip0max
suffix:semicolon
DECL|member|auxclip1min
r_int
r_int
id|auxclip1min
suffix:semicolon
DECL|member|auxclip1max
r_int
r_int
id|auxclip1max
suffix:semicolon
DECL|member|auxclip2min
r_int
r_int
id|auxclip2min
suffix:semicolon
DECL|member|auxclip2max
r_int
r_int
id|auxclip2max
suffix:semicolon
DECL|member|auxclip3min
r_int
r_int
id|auxclip3min
suffix:semicolon
DECL|member|auxclip3max
r_int
r_int
id|auxclip3max
suffix:semicolon
DECL|member|drawop
r_int
r_int
id|drawop
suffix:semicolon
DECL|member|lpat
r_int
r_int
id|lpat
suffix:semicolon
DECL|member|fontxy
r_int
r_int
id|fontxy
suffix:semicolon
DECL|member|fontw
r_int
r_int
id|fontw
suffix:semicolon
DECL|member|fontinc
r_int
r_int
id|fontinc
suffix:semicolon
DECL|member|area_pattern
r_int
r_int
id|area_pattern
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|ucsr
r_int
r_int
id|ucsr
suffix:semicolon
DECL|member|stencil
r_int
r_int
id|stencil
suffix:semicolon
DECL|member|stencilctl
r_int
r_int
id|stencilctl
suffix:semicolon
DECL|member|dcss1
r_int
r_int
id|dcss1
suffix:semicolon
DECL|member|dcss2
r_int
r_int
id|dcss2
suffix:semicolon
DECL|member|dcss3
r_int
r_int
id|dcss3
suffix:semicolon
DECL|member|dcs2
r_int
r_int
id|dcs2
suffix:semicolon
DECL|member|dcs3
r_int
r_int
id|dcs3
suffix:semicolon
DECL|member|dcs4
r_int
r_int
id|dcs4
suffix:semicolon
DECL|member|dcd2
r_int
r_int
id|dcd2
suffix:semicolon
DECL|member|dcd3
r_int
r_int
id|dcd3
suffix:semicolon
DECL|member|dcd4
r_int
r_int
id|dcd4
suffix:semicolon
DECL|member|mer
r_int
r_int
id|mer
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FFB_MAX_CTXS
mdefine_line|#define FFB_MAX_CTXS&t;32
DECL|enum|ffb_chip_type
r_enum
id|ffb_chip_type
(brace
DECL|enumerator|ffb1_prototype
id|ffb1_prototype
op_assign
l_int|0
comma
multiline_comment|/* Early pre-FCS FFB */
DECL|enumerator|ffb1_standard
id|ffb1_standard
comma
multiline_comment|/* First FCS FFB, 100Mhz UPA, 66MHz gclk */
DECL|enumerator|ffb1_speedsort
id|ffb1_speedsort
comma
multiline_comment|/* Second FCS FFB, 100Mhz UPA, 75MHz gclk */
DECL|enumerator|ffb2_prototype
id|ffb2_prototype
comma
multiline_comment|/* Early pre-FCS vertical FFB2 */
DECL|enumerator|ffb2_vertical
id|ffb2_vertical
comma
multiline_comment|/* First FCS FFB2/vertical, 100Mhz UPA, 100MHZ gclk,&n;&t;&t;&t;&t;   75(SingleBuffer)/83(DoubleBuffer) MHz fclk */
DECL|enumerator|ffb2_vertical_plus
id|ffb2_vertical_plus
comma
multiline_comment|/* Second FCS FFB2/vertical, same timings */
DECL|enumerator|ffb2_horizontal
id|ffb2_horizontal
comma
multiline_comment|/* First FCS FFB2/horizontal, same timings as FFB2/vert */
DECL|enumerator|ffb2_horizontal_plus
id|ffb2_horizontal_plus
comma
multiline_comment|/* Second FCS FFB2/horizontal, same timings */
DECL|enumerator|afb_m3
id|afb_m3
comma
multiline_comment|/* FCS Elite3D, 3 float chips */
DECL|enumerator|afb_m6
id|afb_m6
multiline_comment|/* FCS Elite3D, 6 float chips */
)brace
suffix:semicolon
DECL|struct|ffb_dev_priv
r_typedef
r_struct
id|ffb_dev_priv
(brace
multiline_comment|/* Misc software state. */
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
DECL|member|ffb_type
r_enum
id|ffb_chip_type
id|ffb_type
suffix:semicolon
DECL|member|card_phys_base
id|u64
id|card_phys_base
suffix:semicolon
DECL|member|miscdev
r_struct
id|miscdevice
id|miscdev
suffix:semicolon
multiline_comment|/* Controller registers. */
DECL|member|regs
id|ffb_fbcPtr
id|regs
suffix:semicolon
multiline_comment|/* Context table. */
DECL|member|hw_state
r_struct
id|ffb_hw_context
op_star
id|hw_state
(braket
id|FFB_MAX_CTXS
)braket
suffix:semicolon
DECL|typedef|ffb_dev_priv_t
)brace
id|ffb_dev_priv_t
suffix:semicolon
eof
