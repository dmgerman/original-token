multiline_comment|/*&n;   sound/aedsp16.c&n;&n;   Audio Excel DSP 16 software configuration routines&n;&n;   Copyright (C) 1995  Riccardo Facchetti (riccardo@cdc8g5.cdc.polimi.it)&n;&n;   Redistribution and use in source and binary forms, with or without&n;   modification, are permitted provided that the following conditions are&n;   met: 1. Redistributions of source code must retain the above copyright&n;   notice, this list of conditions and the following disclaimer. 2.&n;   Redistributions in binary form must reproduce the above copyright notice,&n;   this list of conditions and the following disclaimer in the documentation&n;   and/or other materials provided with the distribution.&n;&n;   THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND ANY&n;   EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED&n;   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n;   DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n;   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n;   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR&n;   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER&n;   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n;   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n;   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n;   SUCH DAMAGE.&n; */
multiline_comment|/*&n; * Include the main voxware header file. It include all the os/voxware/etc&n; * headers needed by this source.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;sound_config.h&quot;
macro_line|#ifndef AEDSP16_BASE
DECL|macro|CONFIG_AEDSP16
macro_line|#undef CONFIG_AEDSP16
macro_line|#endif
macro_line|#if defined(CONFIG_AEDSP16)
multiline_comment|/*&n;&n;   READ THIS&n;&n;   This module is intended for Audio Excel DSP 16 Sound Card.&n;&n;   Audio Excel DSP 16 is an SB pro II, Microsoft Sound System&n;   and MPU-401 compatible card.&n;   It is software-only configurable (no jumpers to hard-set irq/dma/mpu-irq),&n;   so before this module, the only way to configure the DSP under linux was&n;   boot the MS-BAU loading the sound.sys device driver (this driver soft-&n;   configure the sound board hardware by massaging someone of its registers),&n;   and then ctrl-alt-del to boot linux with the DSP configured by the DOG&n;   driver.&n;&n;   This module works configuring your Audio Excel DSP 16&squot;s&n;   irq, dma and mpu-401-irq. The voxware probe routines rely on the&n;   fact that if the hardware is there, they can detect it. The problem&n;   with AEDSP16 is that no hardware can be found by the probe routines&n;   if the sound card is not well configured. Sometimes the kernel probe&n;   routines can find an SBPRO even when the card is not configured (this&n;   is the standard setup of the card), but the SBPRO emulation don&squot;t work&n;   well if the card is not properly initialized. For this reason&n;&n;   InitAEDSP16_...()&n;&n;   routines are called before the voxware probe routines try to detect the&n;   hardware.&n;&n;   NOTE (READ THE NOTE TOO, IT CONTAIN USEFUL INFORMATIONS)&n;&n;   The Audio Excel DSP 16 Sound Card emulates both SBPRO and MSS;&n;   the voxware sound driver can be configured for SBPRO and MSS cards&n;   at the same time, but the aedsp16 can&squot;t be two cards!!&n;   When we configure it, we have to choose the SBPRO or the MSS emulation&n;   for AEDSP16. We also can install a *REAL* card of the other type&n;   (see [1], not tested but I can&squot;t see any reason for it to fail).&n;&n;   NOTE: If someone can test the combination AEDSP16+MSS or AEDSP16+SBPRO&n;   please let me know if it works.&n;&n;   The MPU-401 support can be compiled in together with one of the other&n;   two operating modes.&n;&n;   The board configuration calls, are in the probe_...() routines because&n;   we have to configure the board before probing it for a particular&n;   hardware. After card configuration, we can probe the hardware.&n;&n;   NOTE: This is something like plug-and-play: we have only to plug&n;   the AEDSP16 board in the socket, and then configure and compile&n;   a kernel that uses the AEDSP16 software configuration capability.&n;   No jumper setting is needed!&n;&n;   For example, if you want AEDSP16 to be an SBPro, on irq 10, dma 3&n;   you have just to make config the voxware package, configuring&n;   the SBPro sound card with that parameters, then when configure&n;   asks if you have an AEDSP16, answer yes. That&squot;s it.&n;   Compile the kernel and run it.&n;&n;   NOTE: This means that you can choose irq and dma, but not the&n;   I/O addresses. To change I/O addresses you have to set them&n;   with jumpers.&n;&n;   NOTE: InitAEDSP16_...() routines get as parameter the hw_config,&n;   the hardware configuration of the - to be configured - board.&n;   The InitAEDSP16() routine, configure the board following our&n;   wishes, that are in the hw_config structure.&n;&n;   You can change the irq/dma/mirq settings WITHOUT THE NEED to open&n;   your computer and massage the jumpers (there are no irq/dma/mirq&n;   jumpers to be configured anyway, only I/O port ones have to be&n;   configured with jumpers)&n;&n;   For some ununderstandable reason, the card default of irq 7, dma 1,&n;   don&squot;t work for me. Seems to be an IRQ or DMA conflict. Under heavy&n;   HDD work, the kernel start to erupt out a lot of messages like:&n;&n;   &squot;Sound: DMA timed out - IRQ/DRQ config error?&squot;&n;&n;   For what I can say, I have NOT any conflict at irq 7 (under linux I&squot;m&n;   using the lp polling driver), and dma line 1 is unused as stated by&n;   /proc/dma. I can suppose this is a bug of AEDSP16. I know my hardware so&n;   I&squot;m pretty sure I have not any conflict, but may be I&squot;m wrong. Who knows!&n;   Anyway a setting of irq 10, dma 3 works really fine.&n;&n;   NOTE: if someone can use AEDSP16 with irq 7, dma 1, please let me know&n;   the emulation mode, all the installed hardware and the hardware&n;   configuration (irq and dma settings of all the hardware).&n;&n;   This init module should work with SBPRO+MSS, when one of the two is&n;   the AEDSP16 emulation and the other the real card. (see [1])&n;   For example:&n;&n;   AEDSP16 (0x220) in SBPRO emu (0x220) + real MSS + other&n;   AEDSP16 (0x220) in MSS emu + real SBPRO (0x240) + other&n;&n;   MPU401 should work. (see [1])&n;&n;   [1] Not tested by me for lack of hardware.&n;&n;   TODO, WISHES AND TECH&n;&n;   May be there&squot;s lot of redundant delays, but for now I want to leave it&n;   this way.&n;&n;   Should be interesting eventually write down a new ioctl for the&n;   aedsp16, to let the suser() change the irq/dma/mirq on the fly.&n;   The thing is not trivial.&n;   In the real world, there&squot;s no need to have such an ioctl because&n;   when we configure the kernel for compile, we can choose the config&n;   parameters. If we change our mind, we can easily re-config the kernel&n;   and re-compile.&n;   Why let the suser() change the config parameters on the fly ?&n;   If anyone have a reasonable answer to this question, I will write down&n;   the code to do it.&n;&n;   More integration with voxware, using voxware low level routines to&n;   read-write dsp is not possible because you may want to have MSS&n;   support and in that case we can not rely on the functions included&n;   in sb_dsp.c to control 0x2yy I/O ports. I will continue to use my&n;   own I/O functions.&n;&n;   - About I/O ports allocation -&n;&n;   The request_region should be done at device probe in every sound card&n;   module. This module is not the best site for requesting regions.&n;   When the request_region code will be added to the main modules such as&n;   sb, adlib, gus, ad1848, etc, the requesting code in this module should&n;   go away.&n;&n;   I think the request regions should be done this way:&n;&n;   if (check_region(...))&n;   return ERR; // I/O region alredy reserved&n;   device_probe(...);&n;   device_attach(...);&n;   request_region(...); // reserve only when we are sure all is okay&n;&n;   Request the 2x0h region in any case if we are using this card.&n;&n;   NOTE: the &quot;(sbpro)&quot; string with which we are requesting the aedsp16 region&n;   (see code) does not mean necessarly that we are emulating sbpro.&n;   It mean that the region is the sbpro I/O ports region. We use this&n;   region to access the control registers of the card, and if emulating&n;   sbpro, I/O sbpro registers too. If we are emulating MSS, the sbpro&n;   registers are not used, in no way, to emulate an sbpro: they are&n;   used only for configuration pourposes.&n;&n;   Someone pointed out that should be possible use both the SBPRO and MSS&n;   modes because the sound card have all the two chipsets, supposing that&n;   the card is really two cards. I have tried something to have the two&n;   modes work together, but, for some reason unknown to me, without success.&n;&n;   I think all the soft-config only cards have an init sequence similar to&n;   this. If you have a card that is not an aedsp16, you can try to start&n;   with this module changing it (mainly in the CMD? I think) to fit your&n;   needs.&n;&n;   Started Fri Mar 17 16:13:18 MET 1995&n;&n;   v0.1 (ALPHA, was an user-level program called AudioExcelDSP16.c)&n;   - Initial code.&n;   v0.2 (ALPHA)&n;   - Cleanups.&n;   - Integrated with Linux voxware v 2.90-2 kernel sound driver.&n;   - SoundBlaster Pro mode configuration.&n;   - Microsoft Sound System mode configuration.&n;   - MPU-401 mode configuration.&n;   v0.3 (ALPHA)&n;   - Cleanups.&n;   - Rearranged the code to let InitAEDSP16 be more general.&n;   - Erased the REALLY_SLOW_IO. We don&squot;t need it. Erased the linux/io.h&n;   inclusion too. We rely on os.h&n;   - Used the  to get a variable&n;   len string (we are not sure about the len of Copyright string).&n;   This works with any SB and compatible.&n;   - Added the code to request_region at device init (should go in&n;   the main body of voxware).&n;   v0.4 (BETA)&n;   - Better configure.c patch for aedsp16 configuration (better&n;   logic of inclusion of AEDSP16 support)&n;   - Modified the conditional compilation to better support more than&n;   one sound card of the emulated type (read the NOTES above)&n;   - Moved the sb init routine from the attach to the very first&n;   probe in sb_card.c&n;   - Rearrangemens and cleanups&n;   - Wiped out some unnecessary code and variables: this is kernel&n;   code so it is better save some TEXT and DATA&n;   - Fixed the request_region code. We must allocate the aedsp16 (sbpro)&n;   I/O ports in any case because they are used to access the DSP&n;   configuration registers and we can not allow anyone to get them.&n;   v0.5&n;   - cleanups on comments&n;   - prep for diffs against v3.0-proto-950402&n;   v0.6&n;   - removed the request_region()s when compiling the MODULE sound.o&n;   because we are not allowed (by the actual voxware structure) to&n;   release_region()&n;&n; */
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;0.6&quot;&t;&t;/* Version of Audio Excel DSP 16 driver */
DECL|macro|AEDSP16_DEBUG
macro_line|#undef AEDSP16_DEBUG&t;&t;/* Define this to enable debug code     */
multiline_comment|/* Actually no debug code is activated  */
multiline_comment|/*&n; * Hardware related defaults&n; */
DECL|macro|IRQ
mdefine_line|#define IRQ  7&t;&t;&t;/* 5 7(default) 9 10 11                 */
DECL|macro|MIRQ
mdefine_line|#define MIRQ 0&t;&t;&t;/* 5 7 9 10 0(default), 0 means disable */
DECL|macro|DMA
mdefine_line|#define DMA  1&t;&t;&t;/* 0 1(default) 3                       */
multiline_comment|/*&n; * Commands of AEDSP16&squot;s DSP (SBPRO+special).&n; * For now they are CMDn, in the future they may change.&n; */
DECL|macro|CMD1
mdefine_line|#define CMD1 0xe3&t;&t;/* Get DSP Copyright                    */
DECL|macro|CMD2
mdefine_line|#define CMD2 0xe1&t;&t;/* Get DSP Version                      */
DECL|macro|CMD3
mdefine_line|#define CMD3 0x88&t;&t;/*                                      */
DECL|macro|CMD4
mdefine_line|#define CMD4 0x5c&t;&t;/*                                      */
DECL|macro|CMD5
mdefine_line|#define CMD5 0x50&t;&t;/* Set M&amp;I&amp;DRQ mask (the real config)   */
DECL|macro|CMD6
mdefine_line|#define CMD6 0x8c&t;&t;/* Enable Microsoft Sound System mode   */
multiline_comment|/*&n; * Offsets of AEDSP16 DSP I/O ports. The offest is added to portbase&n; * to have the actual I/O port.&n; * Register permissions are:&n; * (wo) == Write Only&n; * (ro) == Read  Only&n; * (w-) == Write&n; * (r-) == Read&n; */
DECL|macro|DSP_RESET
mdefine_line|#define DSP_RESET    0x06&t;/* offset of DSP RESET             (wo) */
DECL|macro|DSP_READ
mdefine_line|#define DSP_READ     0x0a&t;/* offset of DSP READ              (ro) */
DECL|macro|DSP_WRITE
mdefine_line|#define DSP_WRITE    0x0c&t;/* offset of DSP WRITE             (w-) */
DECL|macro|DSP_COMMAND
mdefine_line|#define DSP_COMMAND  0x0c&t;/* offset of DSP COMMAND           (w-) */
DECL|macro|DSP_STATUS
mdefine_line|#define DSP_STATUS   0x0c&t;/* offset of DSP STATUS            (r-) */
DECL|macro|DSP_DATAVAIL
mdefine_line|#define DSP_DATAVAIL 0x0e&t;/* offset of DSP DATA AVAILABLE    (ro) */
DECL|macro|RETRY
mdefine_line|#define RETRY           10&t;/* Various retry values on I/O opera-   */
DECL|macro|STATUSRETRY
mdefine_line|#define STATUSRETRY   1000&t;/* tions. Sometimes we have to          */
DECL|macro|HARDRETRY
mdefine_line|#define HARDRETRY   500000&t;/* wait for previous cmd to complete    */
multiline_comment|/*&n; * Size of character arrays that store name and version of sound card&n; */
DECL|macro|CARDNAMELEN
mdefine_line|#define CARDNAMELEN 15&t;&t;/* Size of the card&squot;s name in chars     */
DECL|macro|CARDVERLEN
mdefine_line|#define CARDVERLEN  2&t;&t;/* Size of the card&squot;s version in chars  */
multiline_comment|/*&n; * Bit mapped flags for calling InitAEDSP16(), and saving the current&n; * emulation mode.&n; */
DECL|macro|INIT_NONE
mdefine_line|#define INIT_NONE   (0   )
DECL|macro|INIT_SBPRO
mdefine_line|#define INIT_SBPRO  (1&lt;&lt;0)
DECL|macro|INIT_MSS
mdefine_line|#define INIT_MSS    (1&lt;&lt;1)
DECL|macro|INIT_MPU401
mdefine_line|#define INIT_MPU401 (1&lt;&lt;2)
DECL|macro|RESET_DSP16
mdefine_line|#define RESET_DSP16 (1&lt;&lt;3)
multiline_comment|/* Base HW Port for Audio Card          */
DECL|variable|portbase
r_static
r_int
id|portbase
op_assign
id|AEDSP16_BASE
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
op_assign
id|IRQ
suffix:semicolon
multiline_comment|/* irq for DSP I/O                      */
DECL|variable|mirq
r_static
r_int
id|mirq
op_assign
id|MIRQ
suffix:semicolon
multiline_comment|/* irq for MPU-401 I/O                  */
DECL|variable|dma
r_static
r_int
id|dma
op_assign
id|DMA
suffix:semicolon
multiline_comment|/* dma for DSP I/O                      */
multiline_comment|/* Init status of the card              */
DECL|variable|ae_init
r_static
r_int
id|ae_init
op_assign
id|INIT_NONE
suffix:semicolon
multiline_comment|/* (bitmapped variable)                 */
DECL|variable|oredparams
r_static
r_int
id|oredparams
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Will contain or&squot;ed values of params  */
DECL|variable|gc
r_static
r_int
id|gc
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* generic counter (utility counter)    */
DECL|struct|orVals
r_struct
id|orVals
(brace
multiline_comment|/* Contain the values to be or&squot;ed       */
DECL|member|val
r_int
id|val
suffix:semicolon
multiline_comment|/* irq|mirq|dma                         */
DECL|member|or
r_int
op_logical_or
suffix:semicolon
multiline_comment|/* oredparams |= TheStruct.or           */
)brace
suffix:semicolon
multiline_comment|/*&n; * Magic values that the DSP will eat when configuring irq/mirq/dma&n; */
multiline_comment|/* DSP IRQ conversion array             */
DECL|variable|orIRQ
r_static
r_struct
id|orVals
id|orIRQ
(braket
)braket
op_assign
(brace
(brace
l_int|0x05
comma
l_int|0x28
)brace
comma
(brace
l_int|0x07
comma
l_int|0x08
)brace
comma
(brace
l_int|0x09
comma
l_int|0x10
)brace
comma
(brace
l_int|0x0a
comma
l_int|0x18
)brace
comma
(brace
l_int|0x0b
comma
l_int|0x20
)brace
comma
(brace
l_int|0x00
comma
l_int|0x00
)brace
)brace
suffix:semicolon
multiline_comment|/* MPU-401 IRQ conversion array         */
DECL|variable|orMIRQ
r_static
r_struct
id|orVals
id|orMIRQ
(braket
)braket
op_assign
(brace
(brace
l_int|0x05
comma
l_int|0x04
)brace
comma
(brace
l_int|0x07
comma
l_int|0x44
)brace
comma
(brace
l_int|0x09
comma
l_int|0x84
)brace
comma
(brace
l_int|0x0a
comma
l_int|0xc4
)brace
comma
(brace
l_int|0x00
comma
l_int|0x00
)brace
)brace
suffix:semicolon
multiline_comment|/* DMA Channels conversion array        */
DECL|variable|orDMA
r_static
r_struct
id|orVals
id|orDMA
(braket
)braket
op_assign
(brace
(brace
l_int|0x00
comma
l_int|0x01
)brace
comma
(brace
l_int|0x01
comma
l_int|0x02
)brace
comma
(brace
l_int|0x03
comma
l_int|0x03
)brace
comma
(brace
l_int|0x00
comma
l_int|0x00
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * Buffers to store audio card informations&n; */
DECL|variable|AudioExcelName
r_static
r_char
id|AudioExcelName
(braket
id|CARDNAMELEN
op_plus
l_int|1
)braket
suffix:semicolon
DECL|variable|AudioExcelVersion
r_static
r_char
id|AudioExcelVersion
(braket
id|CARDVERLEN
op_plus
l_int|1
)braket
suffix:semicolon
r_static
r_void
DECL|function|tenmillisec
id|tenmillisec
(paren
r_void
)paren
(brace
r_for
c_loop
(paren
id|gc
op_assign
l_int|0
suffix:semicolon
id|gc
OL
l_int|1000
suffix:semicolon
id|gc
op_increment
)paren
id|tenmicrosec
(paren
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|WaitForDataAvail
id|WaitForDataAvail
(paren
r_int
id|port
)paren
(brace
r_int
id|loop
op_assign
id|STATUSRETRY
suffix:semicolon
r_int
r_char
id|ret
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|ret
op_assign
id|inb
(paren
id|port
op_plus
id|DSP_DATAVAIL
)paren
suffix:semicolon
multiline_comment|/*&n;         * Wait for data available (bit 7 of ret == 1)&n;       */
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|ret
op_amp
l_int|0x80
)paren
op_logical_and
id|loop
op_decrement
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_amp
l_int|0x80
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|ReadData
id|ReadData
(paren
r_int
id|port
)paren
(brace
r_if
c_cond
(paren
id|WaitForDataAvail
(paren
id|port
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
id|inb
(paren
id|port
op_plus
id|DSP_READ
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|CheckDSPOkay
id|CheckDSPOkay
(paren
r_int
id|port
)paren
(brace
r_return
(paren
(paren
id|ReadData
(paren
id|port
)paren
op_eq
l_int|0xaa
)paren
ques
c_cond
l_int|0
suffix:colon
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|ResetBoard
id|ResetBoard
(paren
r_int
id|port
)paren
(brace
multiline_comment|/*&n;     * Reset DSP&n;   */
id|outb
(paren
l_int|1
comma
(paren
id|port
op_plus
id|DSP_RESET
)paren
)paren
suffix:semicolon
id|tenmicrosec
(paren
)paren
suffix:semicolon
id|outb
(paren
l_int|0
comma
(paren
id|port
op_plus
id|DSP_RESET
)paren
)paren
suffix:semicolon
id|tenmicrosec
(paren
)paren
suffix:semicolon
id|tenmicrosec
(paren
)paren
suffix:semicolon
r_return
id|CheckDSPOkay
(paren
id|port
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|WriteDSPCommand
id|WriteDSPCommand
(paren
r_int
id|port
comma
r_int
id|cmd
)paren
(brace
r_int
r_char
id|ret
suffix:semicolon
r_int
id|loop
op_assign
id|HARDRETRY
suffix:semicolon
r_do
(brace
id|ret
op_assign
id|inb
(paren
id|port
op_plus
id|DSP_STATUS
)paren
suffix:semicolon
multiline_comment|/*&n;         * DSP ready to receive data if bit 7 of ret == 0&n;       */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ret
op_amp
l_int|0x80
)paren
)paren
(brace
id|outb
(paren
id|cmd
comma
id|port
op_plus
id|DSP_COMMAND
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|loop
op_decrement
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;[aedsp16] DSP Command (0x%x) timeout.&bslash;n&quot;
comma
id|cmd
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_int
DECL|function|InitMSS
id|InitMSS
(paren
r_int
id|port
)paren
(brace
id|tenmillisec
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|WriteDSPCommand
(paren
id|port
comma
id|CMD6
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;[aedsp16] CMD 0x%x: failed!&bslash;n&quot;
comma
id|CMD6
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|tenmillisec
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|SetUpBoard
id|SetUpBoard
(paren
r_int
id|port
)paren
(brace
r_int
id|loop
op_assign
id|RETRY
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|WriteDSPCommand
(paren
id|portbase
comma
id|CMD3
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;[aedsp16] CMD 0x%x: failed!&bslash;n&quot;
comma
id|CMD3
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|tenmillisec
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|WaitForDataAvail
(paren
id|port
)paren
op_logical_and
id|loop
op_decrement
)paren
suffix:semicolon
macro_line|#if defined(THIS_SHOULD_GO_AWAY)
r_if
c_cond
(paren
id|CheckDSPOkay
(paren
id|port
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;[aedsp16]     CheckDSPOkay: failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#else
r_if
c_cond
(paren
id|ReadData
(paren
id|port
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
(paren
l_string|&quot;[aedsp16] ReadData after CMD 0x%x: failed&bslash;n&quot;
comma
id|CMD3
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|WriteDSPCommand
(paren
id|portbase
comma
id|CMD4
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;[aedsp16] CMD 0x%x: failed!&bslash;n&quot;
comma
id|CMD4
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|WriteDSPCommand
(paren
id|portbase
comma
id|CMD5
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;[aedsp16] CMD 0x%x: failed!&bslash;n&quot;
comma
id|CMD5
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|WriteDSPCommand
(paren
id|portbase
comma
id|oredparams
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;[aedsp16] Initialization of (M)IRQ and DMA: failed!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|GetCardVersion
id|GetCardVersion
(paren
r_int
id|port
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
id|ver
(braket
l_int|3
)braket
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|ReadData
(paren
id|port
)paren
)paren
op_eq
op_minus
l_int|1
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;         * We alredy know how many int are stored (2), so we know when the&n;         * string is finished.&n;       */
id|ver
(braket
id|len
op_increment
)braket
op_assign
id|ret
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
OL
id|CARDVERLEN
)paren
suffix:semicolon
id|sprintf
(paren
id|AudioExcelVersion
comma
l_string|&quot;%d.%d&quot;
comma
id|ver
(braket
l_int|0
)braket
comma
id|ver
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|GetCardName
id|GetCardName
(paren
r_int
id|port
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|ReadData
(paren
id|port
)paren
)paren
op_eq
op_minus
l_int|1
)paren
multiline_comment|/*&n;&t;   * If no more data availabe, return to the caller, no error if len&gt;0.&n;&t;   * We have no other way to know when the string is finished.&n;&t; */
r_return
(paren
id|len
ques
c_cond
l_int|0
suffix:colon
op_minus
l_int|1
)paren
suffix:semicolon
id|AudioExcelName
(braket
id|len
op_increment
)braket
op_assign
id|ret
suffix:semicolon
)brace
r_while
c_loop
(paren
id|len
OL
id|CARDNAMELEN
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|InitializeHardParams
id|InitializeHardParams
(paren
r_void
)paren
(brace
id|memset
(paren
id|AudioExcelName
comma
l_int|0
comma
id|CARDNAMELEN
op_plus
l_int|1
)paren
suffix:semicolon
id|memset
(paren
id|AudioExcelVersion
comma
l_int|0
comma
id|CARDVERLEN
op_plus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|gc
op_assign
l_int|0
suffix:semicolon
id|orIRQ
(braket
id|gc
)braket
dot
op_logical_or
suffix:semicolon
id|gc
op_increment
)paren
r_if
c_cond
(paren
id|orIRQ
(braket
id|gc
)braket
dot
id|val
op_eq
id|irq
)paren
id|oredparams
op_or_assign
id|orIRQ
(braket
id|gc
)braket
dot
op_logical_or
suffix:semicolon
r_for
c_loop
(paren
id|gc
op_assign
l_int|0
suffix:semicolon
id|orMIRQ
(braket
id|gc
)braket
dot
op_logical_or
suffix:semicolon
id|gc
op_increment
)paren
r_if
c_cond
(paren
id|orMIRQ
(braket
id|gc
)braket
dot
op_logical_or
op_eq
id|mirq
)paren
id|oredparams
op_or_assign
id|orMIRQ
(braket
id|gc
)braket
dot
op_logical_or
suffix:semicolon
r_for
c_loop
(paren
id|gc
op_assign
l_int|0
suffix:semicolon
id|orDMA
(braket
id|gc
)braket
dot
op_logical_or
suffix:semicolon
id|gc
op_increment
)paren
r_if
c_cond
(paren
id|orDMA
(braket
id|gc
)braket
dot
id|val
op_eq
id|dma
)paren
id|oredparams
op_or_assign
id|orDMA
(braket
id|gc
)braket
dot
op_logical_or
suffix:semicolon
)brace
r_static
r_int
DECL|function|InitAEDSP16
id|InitAEDSP16
(paren
r_int
id|which
)paren
(brace
r_static
r_char
op_star
id|InitName
op_assign
l_int|NULL
suffix:semicolon
id|InitializeHardParams
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ResetBoard
(paren
id|portbase
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;[aedsp16] ResetBoard: failed!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#if defined(THIS_SHOULD_GO_AWAY)
r_if
c_cond
(paren
id|CheckDSPOkay
(paren
id|portbase
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;[aedsp16] CheckDSPOkay: failed!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|WriteDSPCommand
(paren
id|portbase
comma
id|CMD1
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;[aedsp16] CMD 0x%x: failed!&bslash;n&quot;
comma
id|CMD1
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|GetCardName
(paren
id|portbase
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;[aedsp16] GetCardName: failed!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;     * My AEDSP16 card return SC-6000 in AudioExcelName, so&n;     * if we have something different, we have to be warned.&n;   */
r_if
c_cond
(paren
id|strcmp
(paren
l_string|&quot;SC-6000&quot;
comma
id|AudioExcelName
)paren
)paren
id|printk
(paren
l_string|&quot;[aedsp16] Warning: non SC-6000 audio card!&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|WriteDSPCommand
(paren
id|portbase
comma
id|CMD2
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;[aedsp16] CMD 0x%x: failed!&bslash;n&quot;
comma
id|CMD2
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|GetCardVersion
(paren
id|portbase
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;[aedsp16] GetCardVersion: failed!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|SetUpBoard
(paren
id|portbase
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;[aedsp16] SetUpBoard: failed!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|which
op_eq
id|INIT_MSS
)paren
(brace
r_if
c_cond
(paren
id|InitMSS
(paren
id|portbase
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;[aedsp16] Can&squot;t initialize Microsoft Sound System mode.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;     * If we are resetting, do not print any message because we may be&n;     * in playing and we do not want lost too much time.&n;   */
r_if
c_cond
(paren
op_logical_neg
(paren
id|which
op_amp
id|RESET_DSP16
)paren
)paren
(brace
r_if
c_cond
(paren
id|which
op_amp
id|INIT_MPU401
)paren
id|InitName
op_assign
l_string|&quot;MPU401&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|which
op_amp
id|INIT_SBPRO
)paren
id|InitName
op_assign
l_string|&quot;SBPro&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|which
op_amp
id|INIT_MSS
)paren
id|InitName
op_assign
l_string|&quot;MSS&quot;
suffix:semicolon
r_else
id|InitName
op_assign
l_string|&quot;None&quot;
suffix:semicolon
id|printk
(paren
l_string|&quot;Audio Excel DSP 16 init v%s (%s %s) [%s]&bslash;n&quot;
comma
id|VERSION
comma
id|AudioExcelName
comma
id|AudioExcelVersion
comma
id|InitName
)paren
suffix:semicolon
)brace
id|tenmillisec
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if defined(AEDSP16_SBPRO)
r_int
DECL|function|InitAEDSP16_SBPRO
id|InitAEDSP16_SBPRO
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
multiline_comment|/*&n;     * If the card is alredy init&squot;ed MSS, we can not init it to SBPRO too&n;     * because the board can not emulate simultaneously MSS and SBPRO.&n;   */
r_if
c_cond
(paren
id|ae_init
op_amp
id|INIT_MSS
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ae_init
op_amp
id|INIT_SBPRO
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;     * For now we will leave this&n;     * code included only when INCLUDE_AEDSP16 is configured in, but it should&n;     * be better include it every time.&n;   */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ae_init
op_amp
id|INIT_MPU401
)paren
)paren
(brace
r_if
c_cond
(paren
id|check_region
(paren
id|hw_config-&gt;io_base
comma
l_int|0x0f
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;AEDSP16/SBPRO I/O port region is alredy in use.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;     * Set up the internal hardware parameters, to let the driver reach&n;     * the Sound Card.&n;   */
id|portbase
op_assign
id|hw_config-&gt;io_base
suffix:semicolon
id|irq
op_assign
id|hw_config-&gt;irq
suffix:semicolon
id|dma
op_assign
id|hw_config-&gt;dma
suffix:semicolon
r_if
c_cond
(paren
id|InitAEDSP16
(paren
id|INIT_SBPRO
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
macro_line|#if !defined(MODULE)
multiline_comment|/*&n;     * If we are compiling sound.o (MODULAR version) we can not&n;     * request any region because there is not a uninit routine that&n;     * can allow me to release the requested region.&n;   */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ae_init
op_amp
id|INIT_MPU401
)paren
)paren
id|request_region
(paren
id|hw_config-&gt;io_base
comma
l_int|0x0f
comma
l_string|&quot;aedsp16 (sbpro)&quot;
)paren
suffix:semicolon
macro_line|#endif
id|ae_init
op_or_assign
id|INIT_SBPRO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* AEDSP16_SBPRO */
macro_line|#if defined(AEDSP16_MSS)
r_int
DECL|function|InitAEDSP16_MSS
id|InitAEDSP16_MSS
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
multiline_comment|/*&n;     * If the card is alredy init&squot;ed SBPRO, we can not init it to MSS too&n;     * because the board can not emulate simultaneously MSS and SBPRO.&n;   */
r_if
c_cond
(paren
id|ae_init
op_amp
id|INIT_SBPRO
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ae_init
op_amp
id|INIT_MSS
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;     * For now we will leave this&n;     * code included only when INCLUDE_AEDSP16 is configured in, but it should&n;     * be better include it every time.&n;   */
r_if
c_cond
(paren
id|check_region
(paren
id|hw_config-&gt;io_base
comma
l_int|0x08
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;MSS I/O port region is alredy in use.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;     * We must allocate the AEDSP16 region too because these are the I/O ports&n;     * to access card&squot;s control registers.&n;   */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ae_init
op_amp
id|INIT_MPU401
)paren
)paren
(brace
r_if
c_cond
(paren
id|check_region
(paren
id|AEDSP16_BASE
comma
l_int|0x0f
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;AEDSP16 I/O port region is alredy in use.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;     * If we are configuring the card for MSS, the portbase for card&n;     * configuration is the default one (0x220 unless you have changed the&n;     * factory default with board switches), so no need to modify the&n;     * portbase variable.&n;     * The default is AEDSP16_BASE, that is the right value.&n;   */
id|irq
op_assign
id|hw_config-&gt;irq
suffix:semicolon
id|dma
op_assign
id|hw_config-&gt;dma
suffix:semicolon
r_if
c_cond
(paren
id|InitAEDSP16
(paren
id|INIT_MSS
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
macro_line|#if !defined(MODULE)
multiline_comment|/*&n;     * If we are compiling sound.o (MODULAR version) we can not&n;     * request any region because there is not a uninit routine that&n;     * can allow me to release the requested region. So when unloading&n;     * and then reloading it, we are going to have some nice Oops!&n;   */
id|request_region
(paren
id|hw_config-&gt;io_base
comma
l_int|0x08
comma
l_string|&quot;aedsp16 (mss)&quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
(paren
id|ae_init
op_amp
id|INIT_MPU401
)paren
)paren
id|request_region
(paren
id|AEDSP16_BASE
comma
l_int|0x0f
comma
l_string|&quot;aedsp16 (sbpro)&quot;
)paren
suffix:semicolon
id|ae_init
op_or_assign
id|INIT_MSS
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* AEDSP16_MSS */
macro_line|#if defined(AEDSP16_MPU401)
r_int
DECL|function|InitAEDSP16_MPU401
id|InitAEDSP16_MPU401
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_if
c_cond
(paren
id|ae_init
op_amp
id|INIT_MPU401
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;     * For now we will leave this&n;     * code included only when INCLUDE_AEDSP16 is configured in, but it should&n;     * be better include it every time.&n;   */
r_if
c_cond
(paren
id|check_region
(paren
id|hw_config-&gt;io_base
comma
l_int|0x02
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;SB I/O port region is alredy in use.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;     * We must allocate the AEDSP16 region too because these are the I/O ports&n;     * to access card&squot;s control registers.&n;   */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ae_init
op_amp
(paren
id|INIT_MSS
op_or
id|INIT_SBPRO
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|check_region
(paren
id|AEDSP16_BASE
comma
l_int|0x0f
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;AEDSP16 I/O port region is alredy in use.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;     * If mpu401, the irq and dma are not important, do not touch it&n;     * because we may use the default if sbpro is not yet configured,&n;     * we may use the sbpro ones if configured, and nothing wrong&n;     * should happen.&n;     *&n;     * The mirq default is 0, but once set it to non-0 value, we should&n;     * not touch it anymore (unless I write an ioctl to do it, of course).&n;   */
id|mirq
op_assign
id|hw_config-&gt;irq
suffix:semicolon
r_if
c_cond
(paren
id|InitAEDSP16
(paren
id|INIT_MPU401
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
macro_line|#if !defined(MODULE)
multiline_comment|/*&n;     * If we are compiling sound.o (MODULAR version) we can not&n;     * request any region because there is not a uninit routine that&n;     * can allow me to release the requested region.&n;   */
id|request_region
(paren
id|hw_config-&gt;io_base
comma
l_int|0x02
comma
l_string|&quot;aedsp16 (mpu401)&quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
(paren
id|ae_init
op_amp
(paren
id|INIT_MSS
op_or
id|INIT_SBPRO
)paren
)paren
)paren
id|request_region
(paren
id|AEDSP16_BASE
comma
l_int|0x0f
comma
l_string|&quot;aedsp16 (sbpro)&quot;
)paren
suffix:semicolon
id|ae_init
op_or_assign
id|INIT_MPU401
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* AEDSP16_MPU401 */
macro_line|#if 0&t;&t;&t;&t;/* Leave it out for now. We are not using this portion of code. */
multiline_comment|/*&n; * Entry point for a reset function.&n; * May be I will write the infamous ioctl :)&n; */
r_int
id|ResetAEDSP16
(paren
r_void
)paren
(brace
macro_line|#if defined(AEDSP16_DEBUG)
id|printk
(paren
l_string|&quot;[aedsp16] ResetAEDSP16 called.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|InitAEDSP16
(paren
id|RESET_DSP16
)paren
suffix:semicolon
)brace
macro_line|#endif /* 0 */
macro_line|#endif /* CONFIG_AEDSP16 */
eof
