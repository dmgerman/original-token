multiline_comment|/***************************************************************************&bslash;&n;|*                                                                           *|&n;|*       Copyright 1993-1998 NVIDIA, Corporation.  All rights reserved.      *|&n;|*                                                                           *|&n;|*     NOTICE TO USER:   The source code  is copyrighted under  U.S. and     *|&n;|*     international laws.  Users and possessors of this source code are     *|&n;|*     hereby granted a nonexclusive,  royalty-free copyright license to     *|&n;|*     use this code in individual and commercial software.                  *|&n;|*                                                                           *|&n;|*     Any use of this source code must include,  in the user documenta-     *|&n;|*     tion and  internal comments to the code,  notices to the end user     *|&n;|*     as follows:                                                           *|&n;|*                                                                           *|&n;|*       Copyright 1993-1998 NVIDIA, Corporation.  All rights reserved.      *|&n;|*                                                                           *|&n;|*     NVIDIA, CORPORATION MAKES NO REPRESENTATION ABOUT THE SUITABILITY     *|&n;|*     OF  THIS SOURCE  CODE  FOR ANY PURPOSE.  IT IS  PROVIDED  &quot;AS IS&quot;     *|&n;|*     WITHOUT EXPRESS OR IMPLIED WARRANTY OF ANY KIND.  NVIDIA, CORPOR-     *|&n;|*     ATION DISCLAIMS ALL WARRANTIES  WITH REGARD  TO THIS SOURCE CODE,     *|&n;|*     INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGE-     *|&n;|*     MENT,  AND FITNESS  FOR A PARTICULAR PURPOSE.   IN NO EVENT SHALL     *|&n;|*     NVIDIA, CORPORATION  BE LIABLE FOR ANY SPECIAL,  INDIRECT,  INCI-     *|&n;|*     DENTAL, OR CONSEQUENTIAL DAMAGES,  OR ANY DAMAGES  WHATSOEVER RE-     *|&n;|*     SULTING FROM LOSS OF USE,  DATA OR PROFITS,  WHETHER IN AN ACTION     *|&n;|*     OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,  ARISING OUT OF     *|&n;|*     OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOURCE CODE.     *|&n;|*                                                                           *|&n;|*     U.S. Government  End  Users.   This source code  is a &quot;commercial     *|&n;|*     item,&quot;  as that  term is  defined at  48 C.F.R. 2.101 (OCT 1995),     *|&n;|*     consisting  of &quot;commercial  computer  software&quot;  and  &quot;commercial     *|&n;|*     computer  software  documentation,&quot;  as such  terms  are  used in     *|&n;|*     48 C.F.R. 12.212 (SEPT 1995)  and is provided to the U.S. Govern-     *|&n;|*     ment only as  a commercial end item.   Consistent with  48 C.F.R.     *|&n;|*     12.212 and  48 C.F.R. 227.7202-1 through  227.7202-4 (JUNE 1995),     *|&n;|*     all U.S. Government End Users  acquire the source code  with only     *|&n;|*     those rights set forth herein.                                        *|&n;|*                                                                           *|&n;&bslash;***************************************************************************/
multiline_comment|/* &n; * GPL licensing note -- nVidia is allowing a liberal interpretation of &n; * the documentation restriction above, to merely say that this nVidia&squot;s&n; * copyright and disclaimer should be included with all code derived &n; * from this source.  -- Jeff Garzik &lt;jgarzik@mandrakesoft.com&gt;, 01/Nov/99&n; */
multiline_comment|/* $XFree86: xc/programs/Xserver/hw/xfree86/vga256/drivers/nv/riva_hw.h,v 1.1.2.2 1998/12/22 16:33:19 hohndel Exp $ */
macro_line|#ifndef __RIVA_HW_H__
DECL|macro|__RIVA_HW_H__
mdefine_line|#define __RIVA_HW_H__
DECL|macro|RIVA_SW_VERSION
mdefine_line|#define RIVA_SW_VERSION 0x00010000
multiline_comment|/***************************************************************************&bslash;&n;*                                                                           *&n;*                             FIFO registers.                               *&n;*                                                                           *&n;&bslash;***************************************************************************/
multiline_comment|/*&n; * Raster OPeration. Windows style ROP3.&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|reserved00
r_int
id|reserved00
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|FifoFree
r_int
r_int
id|FifoFree
suffix:semicolon
DECL|member|Nop
r_int
r_int
id|Nop
suffix:semicolon
DECL|member|reserved01
r_int
id|reserved01
(braket
l_int|0x0BB
)braket
suffix:semicolon
DECL|member|Rop3
r_int
id|Rop3
suffix:semicolon
DECL|typedef|RivaRop
)brace
id|RivaRop
suffix:semicolon
multiline_comment|/*&n; * 8X8 Monochrome pattern.&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|reserved00
r_int
id|reserved00
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|FifoFree
r_int
r_int
id|FifoFree
suffix:semicolon
DECL|member|Nop
r_int
r_int
id|Nop
suffix:semicolon
DECL|member|reserved01
r_int
id|reserved01
(braket
l_int|0x0BD
)braket
suffix:semicolon
DECL|member|Shape
r_int
id|Shape
suffix:semicolon
DECL|member|reserved03
r_int
id|reserved03
(braket
l_int|0x001
)braket
suffix:semicolon
DECL|member|Color0
r_int
id|Color0
suffix:semicolon
DECL|member|Color1
r_int
id|Color1
suffix:semicolon
DECL|member|Monochrome
r_int
id|Monochrome
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|RivaPattern
)brace
id|RivaPattern
suffix:semicolon
multiline_comment|/*&n; * Scissor clip rectangle.&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|reserved00
r_int
id|reserved00
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|FifoFree
r_int
r_int
id|FifoFree
suffix:semicolon
DECL|member|Nop
r_int
r_int
id|Nop
suffix:semicolon
DECL|member|reserved01
r_int
id|reserved01
(braket
l_int|0x0BB
)braket
suffix:semicolon
DECL|member|TopLeft
r_int
id|TopLeft
suffix:semicolon
DECL|member|WidthHeight
r_int
id|WidthHeight
suffix:semicolon
DECL|typedef|RivaClip
)brace
id|RivaClip
suffix:semicolon
multiline_comment|/*&n; * 2D filled rectangle.&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|reserved00
r_int
id|reserved00
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|FifoFree
r_int
r_int
id|FifoFree
suffix:semicolon
DECL|member|Nop
r_int
r_int
id|Nop
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|reserved01
r_int
id|reserved01
(braket
l_int|0x0BC
)braket
suffix:semicolon
DECL|member|Color
r_int
id|Color
suffix:semicolon
DECL|member|reserved03
r_int
id|reserved03
(braket
l_int|0x03E
)braket
suffix:semicolon
DECL|member|TopLeft
r_int
id|TopLeft
suffix:semicolon
DECL|member|WidthHeight
r_int
id|WidthHeight
suffix:semicolon
DECL|typedef|RivaRectangle
)brace
id|RivaRectangle
suffix:semicolon
multiline_comment|/*&n; * 2D screen-screen BLT.&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|reserved00
r_int
id|reserved00
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|FifoFree
r_int
r_int
id|FifoFree
suffix:semicolon
DECL|member|Nop
r_int
r_int
id|Nop
suffix:semicolon
DECL|member|reserved01
r_int
id|reserved01
(braket
l_int|0x0BB
)braket
suffix:semicolon
DECL|member|TopLeftSrc
r_int
id|TopLeftSrc
suffix:semicolon
DECL|member|TopLeftDst
r_int
id|TopLeftDst
suffix:semicolon
DECL|member|WidthHeight
r_int
id|WidthHeight
suffix:semicolon
DECL|typedef|RivaScreenBlt
)brace
id|RivaScreenBlt
suffix:semicolon
multiline_comment|/*&n; * 2D pixel BLT.&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|reserved00
r_int
id|reserved00
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|FifoFree
r_int
r_int
id|FifoFree
suffix:semicolon
DECL|member|Nop
r_int
r_int
id|Nop
(braket
l_int|1
)braket
suffix:semicolon
DECL|member|reserved01
r_int
id|reserved01
(braket
l_int|0x0BC
)braket
suffix:semicolon
DECL|member|TopLeft
r_int
id|TopLeft
suffix:semicolon
DECL|member|WidthHeight
r_int
id|WidthHeight
suffix:semicolon
DECL|member|WidthHeightIn
r_int
id|WidthHeightIn
suffix:semicolon
DECL|member|reserved02
r_int
id|reserved02
(braket
l_int|0x03C
)braket
suffix:semicolon
DECL|member|Pixels
r_int
id|Pixels
suffix:semicolon
DECL|typedef|RivaPixmap
)brace
id|RivaPixmap
suffix:semicolon
multiline_comment|/*&n; * Filled rectangle combined with monochrome expand.  Useful for glyphs.&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|reserved00
r_int
id|reserved00
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|FifoFree
r_int
r_int
id|FifoFree
suffix:semicolon
DECL|member|Nop
r_int
r_int
id|Nop
suffix:semicolon
DECL|member|reserved01
r_int
id|reserved01
(braket
l_int|0x0BB
)braket
suffix:semicolon
DECL|member|reserved03
r_int
id|reserved03
(braket
(paren
l_int|0x040
)paren
op_minus
l_int|1
)braket
suffix:semicolon
DECL|member|Color1A
r_int
id|Color1A
suffix:semicolon
r_struct
(brace
DECL|member|TopLeft
r_int
id|TopLeft
suffix:semicolon
DECL|member|WidthHeight
r_int
id|WidthHeight
suffix:semicolon
DECL|member|UnclippedRectangle
)brace
id|UnclippedRectangle
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|reserved04
r_int
id|reserved04
(braket
(paren
l_int|0x080
)paren
op_minus
l_int|3
)braket
suffix:semicolon
r_struct
(brace
DECL|member|TopLeft
r_int
id|TopLeft
suffix:semicolon
DECL|member|BottomRight
r_int
id|BottomRight
suffix:semicolon
DECL|member|ClipB
)brace
id|ClipB
suffix:semicolon
DECL|member|Color1B
r_int
id|Color1B
suffix:semicolon
r_struct
(brace
DECL|member|TopLeft
r_int
id|TopLeft
suffix:semicolon
DECL|member|BottomRight
r_int
id|BottomRight
suffix:semicolon
DECL|member|ClippedRectangle
)brace
id|ClippedRectangle
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|reserved05
r_int
id|reserved05
(braket
(paren
l_int|0x080
)paren
op_minus
l_int|5
)braket
suffix:semicolon
r_struct
(brace
DECL|member|TopLeft
r_int
id|TopLeft
suffix:semicolon
DECL|member|BottomRight
r_int
id|BottomRight
suffix:semicolon
DECL|member|ClipC
)brace
id|ClipC
suffix:semicolon
DECL|member|Color1C
r_int
id|Color1C
suffix:semicolon
DECL|member|WidthHeightC
r_int
id|WidthHeightC
suffix:semicolon
DECL|member|PointC
r_int
id|PointC
suffix:semicolon
DECL|member|MonochromeData1C
r_int
id|MonochromeData1C
suffix:semicolon
DECL|member|reserved06
r_int
id|reserved06
(braket
(paren
l_int|0x080
)paren
op_plus
l_int|121
)braket
suffix:semicolon
r_struct
(brace
DECL|member|TopLeft
r_int
id|TopLeft
suffix:semicolon
DECL|member|BottomRight
r_int
id|BottomRight
suffix:semicolon
DECL|member|ClipD
)brace
id|ClipD
suffix:semicolon
DECL|member|Color1D
r_int
id|Color1D
suffix:semicolon
DECL|member|WidthHeightInD
r_int
id|WidthHeightInD
suffix:semicolon
DECL|member|WidthHeightOutD
r_int
id|WidthHeightOutD
suffix:semicolon
DECL|member|PointD
r_int
id|PointD
suffix:semicolon
DECL|member|MonochromeData1D
r_int
id|MonochromeData1D
suffix:semicolon
DECL|member|reserved07
r_int
id|reserved07
(braket
(paren
l_int|0x080
)paren
op_plus
l_int|120
)braket
suffix:semicolon
r_struct
(brace
DECL|member|TopLeft
r_int
id|TopLeft
suffix:semicolon
DECL|member|BottomRight
r_int
id|BottomRight
suffix:semicolon
DECL|member|ClipE
)brace
id|ClipE
suffix:semicolon
DECL|member|Color0E
r_int
id|Color0E
suffix:semicolon
DECL|member|Color1E
r_int
id|Color1E
suffix:semicolon
DECL|member|WidthHeightInE
r_int
id|WidthHeightInE
suffix:semicolon
DECL|member|WidthHeightOutE
r_int
id|WidthHeightOutE
suffix:semicolon
DECL|member|PointE
r_int
id|PointE
suffix:semicolon
DECL|member|MonochromeData01E
r_int
id|MonochromeData01E
suffix:semicolon
DECL|typedef|RivaBitmap
)brace
id|RivaBitmap
suffix:semicolon
multiline_comment|/*&n; * 3D textured, Z buffered triangle.&n; */
r_typedef
r_volatile
r_struct
(brace
DECL|member|reserved00
r_int
id|reserved00
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|FifoFree
r_int
r_int
id|FifoFree
suffix:semicolon
DECL|member|Nop
r_int
r_int
id|Nop
suffix:semicolon
DECL|member|reserved01
r_int
id|reserved01
(braket
l_int|0x0BC
)braket
suffix:semicolon
DECL|member|TextureOffset
r_int
id|TextureOffset
suffix:semicolon
DECL|member|TextureFormat
r_int
id|TextureFormat
suffix:semicolon
DECL|member|TextureFilter
r_int
id|TextureFilter
suffix:semicolon
DECL|member|FogColor
r_int
id|FogColor
suffix:semicolon
DECL|member|Control
r_int
id|Control
suffix:semicolon
DECL|member|AlphaTest
r_int
id|AlphaTest
suffix:semicolon
DECL|member|reserved02
r_int
id|reserved02
(braket
l_int|0x339
)braket
suffix:semicolon
DECL|member|FogAndIndex
r_int
id|FogAndIndex
suffix:semicolon
DECL|member|Color
r_int
id|Color
suffix:semicolon
DECL|member|ScreenX
r_float
id|ScreenX
suffix:semicolon
DECL|member|ScreenY
r_float
id|ScreenY
suffix:semicolon
DECL|member|ScreenZ
r_float
id|ScreenZ
suffix:semicolon
DECL|member|EyeM
r_float
id|EyeM
suffix:semicolon
DECL|member|TextureS
r_float
id|TextureS
suffix:semicolon
DECL|member|TextureT
r_float
id|TextureT
suffix:semicolon
DECL|typedef|RivaTexturedTriangle03
)brace
id|RivaTexturedTriangle03
suffix:semicolon
multiline_comment|/***************************************************************************&bslash;&n;*                                                                           *&n;*                        Virtualized RIVA H/W interface.                    *&n;*                                                                           *&n;&bslash;***************************************************************************/
r_struct
id|_riva_hw_inst
suffix:semicolon
r_struct
id|_riva_hw_state
suffix:semicolon
multiline_comment|/*&n; * Virtialized chip interface. Makes RIVA 128 and TNT look alike.&n; */
DECL|struct|_riva_hw_inst
r_typedef
r_struct
id|_riva_hw_inst
(brace
multiline_comment|/*&n;     * Chip specific settings.&n;     */
DECL|member|Architecture
r_int
id|Architecture
suffix:semicolon
DECL|member|Version
r_int
id|Version
suffix:semicolon
DECL|member|CrystalFreqKHz
r_int
id|CrystalFreqKHz
suffix:semicolon
DECL|member|RamAmountKBytes
r_int
id|RamAmountKBytes
suffix:semicolon
DECL|member|MaxVClockFreqKHz
r_int
id|MaxVClockFreqKHz
suffix:semicolon
DECL|member|RamBandwidthKBytesPerSec
r_int
id|RamBandwidthKBytesPerSec
suffix:semicolon
DECL|member|EnableIRQ
r_int
id|EnableIRQ
suffix:semicolon
DECL|member|IO
r_int
id|IO
suffix:semicolon
DECL|member|LockUnlockIO
r_int
id|LockUnlockIO
suffix:semicolon
DECL|member|LockUnlockIndex
r_int
id|LockUnlockIndex
suffix:semicolon
DECL|member|VBlankBit
r_int
id|VBlankBit
suffix:semicolon
DECL|member|FifoFreeCount
r_int
id|FifoFreeCount
suffix:semicolon
multiline_comment|/*&n;     * Non-FIFO registers.&n;     */
DECL|member|PCRTC
r_volatile
r_int
op_star
id|PCRTC
suffix:semicolon
DECL|member|PRAMDAC
r_volatile
r_int
op_star
id|PRAMDAC
suffix:semicolon
DECL|member|PFB
r_volatile
r_int
op_star
id|PFB
suffix:semicolon
DECL|member|PFIFO
r_volatile
r_int
op_star
id|PFIFO
suffix:semicolon
DECL|member|PGRAPH
r_volatile
r_int
op_star
id|PGRAPH
suffix:semicolon
DECL|member|PEXTDEV
r_volatile
r_int
op_star
id|PEXTDEV
suffix:semicolon
DECL|member|PTIMER
r_volatile
r_int
op_star
id|PTIMER
suffix:semicolon
DECL|member|PMC
r_volatile
r_int
op_star
id|PMC
suffix:semicolon
DECL|member|PRAMIN
r_volatile
r_int
op_star
id|PRAMIN
suffix:semicolon
DECL|member|FIFO
r_volatile
r_int
op_star
id|FIFO
suffix:semicolon
DECL|member|CURSOR
r_volatile
r_int
op_star
id|CURSOR
suffix:semicolon
DECL|member|CURSORPOS
r_volatile
r_int
op_star
id|CURSORPOS
suffix:semicolon
DECL|member|VBLANKENABLE
r_volatile
r_int
op_star
id|VBLANKENABLE
suffix:semicolon
DECL|member|VBLANK
r_volatile
r_int
op_star
id|VBLANK
suffix:semicolon
multiline_comment|/*&n;     * Common chip functions.&n;     */
DECL|member|Busy
r_int
(paren
op_star
id|Busy
)paren
(paren
r_struct
id|_riva_hw_inst
op_star
)paren
suffix:semicolon
DECL|member|CalcStateExt
r_void
(paren
op_star
id|CalcStateExt
)paren
(paren
r_struct
id|_riva_hw_inst
op_star
comma
r_struct
id|_riva_hw_state
op_star
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|LoadStateExt
r_void
(paren
op_star
id|LoadStateExt
)paren
(paren
r_struct
id|_riva_hw_inst
op_star
comma
r_struct
id|_riva_hw_state
op_star
)paren
suffix:semicolon
DECL|member|UnloadStateExt
r_void
(paren
op_star
id|UnloadStateExt
)paren
(paren
r_struct
id|_riva_hw_inst
op_star
comma
r_struct
id|_riva_hw_state
op_star
)paren
suffix:semicolon
DECL|member|SetStartAddress
r_void
(paren
op_star
id|SetStartAddress
)paren
(paren
r_struct
id|_riva_hw_inst
op_star
comma
r_int
)paren
suffix:semicolon
DECL|member|SetSurfaces2D
r_void
(paren
op_star
id|SetSurfaces2D
)paren
(paren
r_struct
id|_riva_hw_inst
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|SetSurfaces3D
r_void
(paren
op_star
id|SetSurfaces3D
)paren
(paren
r_struct
id|_riva_hw_inst
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|ShowHideCursor
r_int
(paren
op_star
id|ShowHideCursor
)paren
(paren
r_struct
id|_riva_hw_inst
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/*&n;     * Current extended mode settings.&n;     */
DECL|member|CurrentState
r_struct
id|_riva_hw_state
op_star
id|CurrentState
suffix:semicolon
multiline_comment|/*&n;     * FIFO registers.&n;     */
DECL|member|Rop
id|RivaRop
op_star
id|Rop
suffix:semicolon
DECL|member|Patt
id|RivaPattern
op_star
id|Patt
suffix:semicolon
DECL|member|Clip
id|RivaClip
op_star
id|Clip
suffix:semicolon
DECL|member|Pixmap
id|RivaPixmap
op_star
id|Pixmap
suffix:semicolon
DECL|member|Blt
id|RivaScreenBlt
op_star
id|Blt
suffix:semicolon
DECL|member|Bitmap
id|RivaBitmap
op_star
id|Bitmap
suffix:semicolon
DECL|member|Tri03
id|RivaTexturedTriangle03
op_star
id|Tri03
suffix:semicolon
DECL|typedef|RIVA_HW_INST
)brace
id|RIVA_HW_INST
suffix:semicolon
multiline_comment|/*&n; * Extended mode state information.&n; */
DECL|struct|_riva_hw_state
r_typedef
r_struct
id|_riva_hw_state
(brace
DECL|member|bpp
r_int
id|bpp
suffix:semicolon
DECL|member|width
r_int
id|width
suffix:semicolon
DECL|member|height
r_int
id|height
suffix:semicolon
DECL|member|repaint0
r_int
id|repaint0
suffix:semicolon
DECL|member|repaint1
r_int
id|repaint1
suffix:semicolon
DECL|member|screen
r_int
id|screen
suffix:semicolon
DECL|member|pixel
r_int
id|pixel
suffix:semicolon
DECL|member|horiz
r_int
id|horiz
suffix:semicolon
DECL|member|arbitration0
r_int
id|arbitration0
suffix:semicolon
DECL|member|arbitration1
r_int
id|arbitration1
suffix:semicolon
DECL|member|vpll
r_int
id|vpll
suffix:semicolon
DECL|member|pllsel
r_int
id|pllsel
suffix:semicolon
DECL|member|general
r_int
id|general
suffix:semicolon
DECL|member|config
r_int
id|config
suffix:semicolon
DECL|member|cursor0
r_int
id|cursor0
suffix:semicolon
DECL|member|cursor1
r_int
id|cursor1
suffix:semicolon
DECL|member|cursor2
r_int
id|cursor2
suffix:semicolon
DECL|member|offset0
r_int
id|offset0
suffix:semicolon
DECL|member|offset1
r_int
id|offset1
suffix:semicolon
DECL|member|offset2
r_int
id|offset2
suffix:semicolon
DECL|member|offset3
r_int
id|offset3
suffix:semicolon
DECL|member|pitch0
r_int
id|pitch0
suffix:semicolon
DECL|member|pitch1
r_int
id|pitch1
suffix:semicolon
DECL|member|pitch2
r_int
id|pitch2
suffix:semicolon
DECL|member|pitch3
r_int
id|pitch3
suffix:semicolon
DECL|typedef|RIVA_HW_STATE
)brace
id|RIVA_HW_STATE
suffix:semicolon
multiline_comment|/*&n; * External routines.&n; */
r_int
id|RivaGetConfig
c_func
(paren
id|RIVA_HW_INST
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * FIFO Free Count. Should attempt to yield processor if RIVA is busy.&n; */
DECL|macro|RIVA_FIFO_FREE
mdefine_line|#define RIVA_FIFO_FREE(hwinst,hwptr,cnt)                                    &bslash;&n;{                                                                           &bslash;&n;while ((hwinst).FifoFreeCount &lt; (cnt))                                      &bslash;&n;{                                                                           &bslash;&n;    (hwinst).FifoFreeCount = (hwinst).hwptr-&gt;FifoFree &gt;&gt; 2;                 &bslash;&n;}                                                                           &bslash;&n;(hwinst).FifoFreeCount -= (cnt);                                            &bslash;&n;}
macro_line|#endif /* __RIVA_HW_H__ */
eof
