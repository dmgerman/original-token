multiline_comment|/* $Id: rawhdlc.c,v 1.3 1998/06/17 19:51:21 he Exp $&n;&n; * rawhdlc.c     support routines for cards that don&squot;t support HDLC&n; *&n; * Author     Karsten Keil (keil@temic-ech.spacenet.de)&n; *            Brent Baccala &lt;baccala@FreeSoft.org&gt;&n; *&n; *&n; * Some passive ISDN cards, such as the Traverse NETJet and the AMD 7930,&n; * don&squot;t perform HDLC encapsulation over the B channel.  Drivers for&n; * such cards use support routines in this file to perform B channel HDLC.&n; *&n; * Bit-synchronous HDLC encapsulation is a means of encapsulating packets&n; * over a continuously transmitting serial communications link.&n; * It looks like this:&n; *&n; *      11111111101111110...........0111111011111111111&n; *      iiiiiiiiiffffffffdddddddddddffffffffiiiiiiiiiii&n; *&n; *      i = idle     f = flag     d = data&n; *&n; * When idle, the channel sends a continuous string of ones (mark&n; * idle; illustrated), or a continuous string of flag characters (flag&n; * idle).  The beginning of a data frame is marked by a flag character&n; * (01111110), then comes the actual data, followed by another flag&n; * character, after which another frame may be sent immediately (a&n; * single flag may serve as both the end of one frame and the start of&n; * the next), or the link may return to idle.  Obviously, the flag&n; * character can not appear anywhere in the data (or a false&n; * end-of-frame would occur), so the transmitter performs&n; * &quot;bit-stuffing&quot; - inserting a zero bit after every five one bits,&n; * irregardless of the original bit after the five ones.  Byte&n; * ordering is irrelevent at this point - the data is treated as a&n; * string of bits, not bytes.  Since no more than 5 ones may now occur&n; * in a row, the flag sequence, with its 6 ones, is unique.&n; *&n; * Upon reception, a zero bit that occur after 5 one bits is simply&n; * discarded.  A series of 6 one bits is end-of-frame, and a series of&n; * 7 one bits is an abort.  Once bit-stuffing has been corrected for,&n; * an integer number of bytes should now be present.  The last two&n; * of these bytes form the Frame Check Sequence, a CRC that is verified&n; * and then discarded.  Note that bit-stuffing is performed on the FCS&n; * just as if it were regular data.&n; *&n; *&n; *&n; * int make_raw_hdlc_data(u_char *src, u_int slen,&n; *                        u_char *dst, u_int dsize)&n; *&n; *   Used for transmission.  Copies slen bytes from src to dst, performing&n; *   HDLC encapsulation (flag bytes, bit-stuffing, CRC) in the process.&n; *   dsize is size of destination buffer, and should be at least&n; *   ((6*slen)/5)+5 bytes to ensure adequate space will be available.&n; *   Function returns length (in bytes) of valid destination buffer, or&n; *   0 upon destination overflow.&n; *&n; * void init_hdlc_state(struct hdlc_state *stateptr, int mode)&n; *&n; *   Initializes hdlc_state structure before first call to read_raw_hdlc_data&n; *&n; *   mode = 0: Sane mode&n; *   mode = 1/2: &n; *             Insane mode; NETJet use a shared unsigned int memory block (&n; * &t;       with busmaster DMA), the bit pattern of every word is &n; *  &t;       &lt;8 B1&gt; &lt;8 B2&gt; &lt;8 Mon&gt; &lt;2 D&gt; &lt;4 C/I&gt; &lt;MX&gt; &lt;MR&gt;&n; *&t;       according to Siemens IOM-2 interface, so we have to handle&n; *             the src buffer as unsigned int and have to shift/mask the&n; *             B-channel bytes.&n; *             mode 1 -&gt; B1  mode 2  -&gt; B2 data is used&n; *&n; * int read_raw_hdlc_data(struct hdlc_state *saved_state,&n; *                        u_char *src, u_int slen,&n; *                        u_char *dst, u_int dsize)&n; *&n; *   Used for reception.  Scans source buffer bit-by-bit looking for&n; *   valid HDLC frames, which are copied to destination buffer.  HDLC&n; *   state information is stored in a structure, which allows this&n; *   function to process frames spread across several blocks of raw&n; *   HDLC data.  Part of the state information is bit offsets into&n; *   the source and destination buffers.&n; *&n; *   A return value &gt;0 indicates the length of a valid frame, now&n; *   stored in the destination buffer.  In this case, the source&n; *   buffer might not be completely processed, so this function should&n; *   be called again with the same source buffer, possibly with a&n; *   different destination buffer.&n; *&n; *   A return value of zero indicates that the source buffer was&n; *   completely processed without finding a valid end-of-packet;&n; *   however, we might be in the middle of packet reception, so&n; *   the function should be called again with the next block of&n; *   raw HDLC data and the same destination buffer.  It is NOT&n; *   permitted to change the destination buffer in this case,&n; *   since data may already have begun to be stored there.&n; *&n; *   A return value of -1 indicates some kind of error - destination&n; *   buffer overflow, CRC check failed, frame not a multiple of 8&n; *   bits.  Destination buffer probably contains invalid data, which&n; *   should be discarded.  Call function again with same source buffer&n; *   and a new (or same) destination buffer.&n; *&n; *   Suggested calling sequence:&n; *&n; *      init_hdlc_state(...);&n; *      for (EACH_RAW_DATA_BLOCK) {&n; *         while (len = read_raw_hdlc_data(...)) {&n; *             if (len == -1) DISCARD_FRAME;&n; *             else PROCESS_FRAME;&n; *         }&n; *      }&n; *&n; *&n; * Test the code in this file as follows:&n; *    gcc -DDEBUGME -o rawhdlctest rawhdlc.c&n; *    ./rawhdlctest &lt; rawdata&n; *&n; * The file &quot;rawdata&quot; can be easily generated from a HISAX B-channel&n; * hex dump (CF CF CF 02 ...) using the following perl script:&n; *&n; * while(&lt;&gt;) {&n; *     @hexlist = split &squot; &squot;;&n; *     while ($hexstr = shift(@hexlist)) {&n; *         printf &quot;%c&quot;, hex($hexstr);&n; *     }&n; * }&n; *&n; */
macro_line|#ifdef DEBUGME
macro_line|#include &lt;stdio.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ppp_defs.h&gt;
macro_line|#include &quot;rawhdlc.h&quot;
multiline_comment|/* There&squot;s actually an identical copy of this table in the PPP code&n; * (ppp_crc16_table), but I don&squot;t want this code dependent on PPP&n; */
singleline_comment|// static 
DECL|variable|fcstab
id|__u16
id|fcstab
(braket
l_int|256
)braket
op_assign
(brace
l_int|0x0000
comma
l_int|0x1189
comma
l_int|0x2312
comma
l_int|0x329b
comma
l_int|0x4624
comma
l_int|0x57ad
comma
l_int|0x6536
comma
l_int|0x74bf
comma
l_int|0x8c48
comma
l_int|0x9dc1
comma
l_int|0xaf5a
comma
l_int|0xbed3
comma
l_int|0xca6c
comma
l_int|0xdbe5
comma
l_int|0xe97e
comma
l_int|0xf8f7
comma
l_int|0x1081
comma
l_int|0x0108
comma
l_int|0x3393
comma
l_int|0x221a
comma
l_int|0x56a5
comma
l_int|0x472c
comma
l_int|0x75b7
comma
l_int|0x643e
comma
l_int|0x9cc9
comma
l_int|0x8d40
comma
l_int|0xbfdb
comma
l_int|0xae52
comma
l_int|0xdaed
comma
l_int|0xcb64
comma
l_int|0xf9ff
comma
l_int|0xe876
comma
l_int|0x2102
comma
l_int|0x308b
comma
l_int|0x0210
comma
l_int|0x1399
comma
l_int|0x6726
comma
l_int|0x76af
comma
l_int|0x4434
comma
l_int|0x55bd
comma
l_int|0xad4a
comma
l_int|0xbcc3
comma
l_int|0x8e58
comma
l_int|0x9fd1
comma
l_int|0xeb6e
comma
l_int|0xfae7
comma
l_int|0xc87c
comma
l_int|0xd9f5
comma
l_int|0x3183
comma
l_int|0x200a
comma
l_int|0x1291
comma
l_int|0x0318
comma
l_int|0x77a7
comma
l_int|0x662e
comma
l_int|0x54b5
comma
l_int|0x453c
comma
l_int|0xbdcb
comma
l_int|0xac42
comma
l_int|0x9ed9
comma
l_int|0x8f50
comma
l_int|0xfbef
comma
l_int|0xea66
comma
l_int|0xd8fd
comma
l_int|0xc974
comma
l_int|0x4204
comma
l_int|0x538d
comma
l_int|0x6116
comma
l_int|0x709f
comma
l_int|0x0420
comma
l_int|0x15a9
comma
l_int|0x2732
comma
l_int|0x36bb
comma
l_int|0xce4c
comma
l_int|0xdfc5
comma
l_int|0xed5e
comma
l_int|0xfcd7
comma
l_int|0x8868
comma
l_int|0x99e1
comma
l_int|0xab7a
comma
l_int|0xbaf3
comma
l_int|0x5285
comma
l_int|0x430c
comma
l_int|0x7197
comma
l_int|0x601e
comma
l_int|0x14a1
comma
l_int|0x0528
comma
l_int|0x37b3
comma
l_int|0x263a
comma
l_int|0xdecd
comma
l_int|0xcf44
comma
l_int|0xfddf
comma
l_int|0xec56
comma
l_int|0x98e9
comma
l_int|0x8960
comma
l_int|0xbbfb
comma
l_int|0xaa72
comma
l_int|0x6306
comma
l_int|0x728f
comma
l_int|0x4014
comma
l_int|0x519d
comma
l_int|0x2522
comma
l_int|0x34ab
comma
l_int|0x0630
comma
l_int|0x17b9
comma
l_int|0xef4e
comma
l_int|0xfec7
comma
l_int|0xcc5c
comma
l_int|0xddd5
comma
l_int|0xa96a
comma
l_int|0xb8e3
comma
l_int|0x8a78
comma
l_int|0x9bf1
comma
l_int|0x7387
comma
l_int|0x620e
comma
l_int|0x5095
comma
l_int|0x411c
comma
l_int|0x35a3
comma
l_int|0x242a
comma
l_int|0x16b1
comma
l_int|0x0738
comma
l_int|0xffcf
comma
l_int|0xee46
comma
l_int|0xdcdd
comma
l_int|0xcd54
comma
l_int|0xb9eb
comma
l_int|0xa862
comma
l_int|0x9af9
comma
l_int|0x8b70
comma
l_int|0x8408
comma
l_int|0x9581
comma
l_int|0xa71a
comma
l_int|0xb693
comma
l_int|0xc22c
comma
l_int|0xd3a5
comma
l_int|0xe13e
comma
l_int|0xf0b7
comma
l_int|0x0840
comma
l_int|0x19c9
comma
l_int|0x2b52
comma
l_int|0x3adb
comma
l_int|0x4e64
comma
l_int|0x5fed
comma
l_int|0x6d76
comma
l_int|0x7cff
comma
l_int|0x9489
comma
l_int|0x8500
comma
l_int|0xb79b
comma
l_int|0xa612
comma
l_int|0xd2ad
comma
l_int|0xc324
comma
l_int|0xf1bf
comma
l_int|0xe036
comma
l_int|0x18c1
comma
l_int|0x0948
comma
l_int|0x3bd3
comma
l_int|0x2a5a
comma
l_int|0x5ee5
comma
l_int|0x4f6c
comma
l_int|0x7df7
comma
l_int|0x6c7e
comma
l_int|0xa50a
comma
l_int|0xb483
comma
l_int|0x8618
comma
l_int|0x9791
comma
l_int|0xe32e
comma
l_int|0xf2a7
comma
l_int|0xc03c
comma
l_int|0xd1b5
comma
l_int|0x2942
comma
l_int|0x38cb
comma
l_int|0x0a50
comma
l_int|0x1bd9
comma
l_int|0x6f66
comma
l_int|0x7eef
comma
l_int|0x4c74
comma
l_int|0x5dfd
comma
l_int|0xb58b
comma
l_int|0xa402
comma
l_int|0x9699
comma
l_int|0x8710
comma
l_int|0xf3af
comma
l_int|0xe226
comma
l_int|0xd0bd
comma
l_int|0xc134
comma
l_int|0x39c3
comma
l_int|0x284a
comma
l_int|0x1ad1
comma
l_int|0x0b58
comma
l_int|0x7fe7
comma
l_int|0x6e6e
comma
l_int|0x5cf5
comma
l_int|0x4d7c
comma
l_int|0xc60c
comma
l_int|0xd785
comma
l_int|0xe51e
comma
l_int|0xf497
comma
l_int|0x8028
comma
l_int|0x91a1
comma
l_int|0xa33a
comma
l_int|0xb2b3
comma
l_int|0x4a44
comma
l_int|0x5bcd
comma
l_int|0x6956
comma
l_int|0x78df
comma
l_int|0x0c60
comma
l_int|0x1de9
comma
l_int|0x2f72
comma
l_int|0x3efb
comma
l_int|0xd68d
comma
l_int|0xc704
comma
l_int|0xf59f
comma
l_int|0xe416
comma
l_int|0x90a9
comma
l_int|0x8120
comma
l_int|0xb3bb
comma
l_int|0xa232
comma
l_int|0x5ac5
comma
l_int|0x4b4c
comma
l_int|0x79d7
comma
l_int|0x685e
comma
l_int|0x1ce1
comma
l_int|0x0d68
comma
l_int|0x3ff3
comma
l_int|0x2e7a
comma
l_int|0xe70e
comma
l_int|0xf687
comma
l_int|0xc41c
comma
l_int|0xd595
comma
l_int|0xa12a
comma
l_int|0xb0a3
comma
l_int|0x8238
comma
l_int|0x93b1
comma
l_int|0x6b46
comma
l_int|0x7acf
comma
l_int|0x4854
comma
l_int|0x59dd
comma
l_int|0x2d62
comma
l_int|0x3ceb
comma
l_int|0x0e70
comma
l_int|0x1ff9
comma
l_int|0xf78f
comma
l_int|0xe606
comma
l_int|0xd49d
comma
l_int|0xc514
comma
l_int|0xb1ab
comma
l_int|0xa022
comma
l_int|0x92b9
comma
l_int|0x8330
comma
l_int|0x7bc7
comma
l_int|0x6a4e
comma
l_int|0x58d5
comma
l_int|0x495c
comma
l_int|0x3de3
comma
l_int|0x2c6a
comma
l_int|0x1ef1
comma
l_int|0x0f78
)brace
suffix:semicolon
DECL|macro|HDLC_ZERO_SEARCH
mdefine_line|#define HDLC_ZERO_SEARCH 0
DECL|macro|HDLC_FLAG_SEARCH
mdefine_line|#define HDLC_FLAG_SEARCH 1
DECL|macro|HDLC_FLAG_FOUND
mdefine_line|#define HDLC_FLAG_FOUND  2
DECL|macro|HDLC_FRAME_FOUND
mdefine_line|#define HDLC_FRAME_FOUND 3
DECL|macro|HDLC_NULL
mdefine_line|#define HDLC_NULL 4
DECL|macro|HDLC_PART
mdefine_line|#define HDLC_PART 5
DECL|macro|HDLC_FULL
mdefine_line|#define HDLC_FULL 6
DECL|macro|HDLC_FLAG_VALUE
mdefine_line|#define HDLC_FLAG_VALUE&t;0x7e
DECL|macro|MAKE_RAW_BYTE
mdefine_line|#define MAKE_RAW_BYTE for (j=0; j&lt;8; j++) { &bslash;&n;&t;&t;&t;bitcnt++;&bslash;&n;&t;&t;&t;out_val &gt;&gt;= 1;&bslash;&n;&t;&t;&t;if (val &amp; 1) {&bslash;&n;&t;&t;&t;&t;s_one++;&bslash;&n;&t;&t;&t;&t;out_val |= 0x80;&bslash;&n;&t;&t;&t;} else {&bslash;&n;&t;&t;&t;&t;s_one = 0;&bslash;&n;&t;&t;&t;&t;out_val &amp;= 0x7f;&bslash;&n;&t;&t;&t;}&bslash;&n;&t;&t;&t;if (bitcnt==8) {&bslash;&n;&t;&t;&t;&t;if (d_cnt == dsize) return 0;&bslash;&n;&t;&t;&t;&t;dst[d_cnt++] = out_val;&bslash;&n;&t;&t;&t;&t;bitcnt = 0;&bslash;&n;&t;&t;&t;}&bslash;&n;&t;&t;&t;if (s_one == 5) {&bslash;&n;&t;&t;&t;&t;out_val &gt;&gt;= 1;&bslash;&n;&t;&t;&t;&t;out_val &amp;= 0x7f;&bslash;&n;&t;&t;&t;&t;bitcnt++;&bslash;&n;&t;&t;&t;&t;s_one = 0;&bslash;&n;&t;&t;&t;}&bslash;&n;&t;&t;&t;if (bitcnt==8) {&bslash;&n;&t;&t;&t;&t;if (d_cnt == dsize) return 0;&bslash;&n;&t;&t;&t;&t;dst[d_cnt++] = out_val;&bslash;&n;&t;&t;&t;&t;bitcnt = 0;&bslash;&n;&t;&t;&t;}&bslash;&n;&t;&t;&t;val &gt;&gt;= 1;&bslash;&n;&t;&t;}
multiline_comment|/* Optimization suggestion: If needed, this function could be&n; * dramatically sped up using a state machine.  Each state would&n; * correspond to having seen N one bits, and being offset M bits into&n; * the current output byte.  N ranges from 0 to 4, M from 0 to 7, so&n; * we need 5*8 = 35 states.  Each state would have a table with 256&n; * entries, one for each input character.  Each entry would contain&n; * three output characters, an output state, an a byte increment&n; * that&squot;s either 1 or 2.  All this could fit in four bytes; so we need&n; * 4 bytes * 256 characters = 1 KB for each state (35 KB total).  Zero&n; * the output buffer before you start.  For each character in your&n; * input, you look it up in the current state&squot;s table and get three&n; * bytes to be or&squot;ed into the output at the current byte offset, and&n; * an byte increment to move your pointer forward.  A simple Perl&n; * script could generate the tables.  Given HDLC semantics, probably&n; * would be better to set output to all 1s, then use ands instead of ors.&n; * A smaller state machine could operate on nibbles instead of bytes.&n; * A state machine for 32-bit architectures could use word offsets&n; * instead of byte offsets, requiring 5*32 = 160 states; probably&n; * best to work on nibbles in such a case.&n; */
DECL|function|make_raw_hdlc_data
r_int
id|make_raw_hdlc_data
c_func
(paren
id|u_char
op_star
id|src
comma
id|u_int
id|slen
comma
id|u_char
op_star
id|dst
comma
id|u_int
id|dsize
)paren
(brace
r_register
id|u_int
id|i
comma
id|d_cnt
op_assign
l_int|0
suffix:semicolon
r_register
id|u_char
id|j
suffix:semicolon
r_register
id|u_char
id|val
suffix:semicolon
r_register
id|u_char
id|s_one
op_assign
l_int|0
suffix:semicolon
r_register
id|u_char
id|out_val
op_assign
l_int|0
suffix:semicolon
r_register
id|u_char
id|bitcnt
op_assign
l_int|0
suffix:semicolon
id|u_int
id|fcs
suffix:semicolon
id|dst
(braket
id|d_cnt
op_increment
)braket
op_assign
id|HDLC_FLAG_VALUE
suffix:semicolon
id|fcs
op_assign
id|PPP_INITFCS
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|slen
suffix:semicolon
id|i
op_increment
)paren
(brace
id|val
op_assign
id|src
(braket
id|i
)braket
suffix:semicolon
id|fcs
op_assign
id|PPP_FCS
(paren
id|fcs
comma
id|val
)paren
suffix:semicolon
id|MAKE_RAW_BYTE
suffix:semicolon
)brace
id|fcs
op_xor_assign
l_int|0xffff
suffix:semicolon
id|val
op_assign
id|fcs
op_amp
l_int|0xff
suffix:semicolon
id|MAKE_RAW_BYTE
suffix:semicolon
id|val
op_assign
(paren
id|fcs
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|MAKE_RAW_BYTE
suffix:semicolon
id|val
op_assign
id|HDLC_FLAG_VALUE
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|8
suffix:semicolon
id|j
op_increment
)paren
(brace
id|bitcnt
op_increment
suffix:semicolon
id|out_val
op_rshift_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
l_int|1
)paren
id|out_val
op_or_assign
l_int|0x80
suffix:semicolon
r_else
id|out_val
op_and_assign
l_int|0x7f
suffix:semicolon
r_if
c_cond
(paren
id|bitcnt
op_eq
l_int|8
)paren
(brace
r_if
c_cond
(paren
id|d_cnt
op_eq
id|dsize
)paren
r_return
l_int|0
suffix:semicolon
id|dst
(braket
id|d_cnt
op_increment
)braket
op_assign
id|out_val
suffix:semicolon
id|bitcnt
op_assign
l_int|0
suffix:semicolon
)brace
id|val
op_rshift_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bitcnt
)paren
(brace
r_while
c_loop
(paren
l_int|8
OG
id|bitcnt
op_increment
)paren
(brace
id|out_val
op_rshift_assign
l_int|1
suffix:semicolon
id|out_val
op_or_assign
l_int|0x80
suffix:semicolon
)brace
r_if
c_cond
(paren
id|d_cnt
op_eq
id|dsize
)paren
r_return
l_int|0
suffix:semicolon
id|dst
(braket
id|d_cnt
op_increment
)braket
op_assign
id|out_val
suffix:semicolon
)brace
r_return
id|d_cnt
suffix:semicolon
)brace
DECL|function|init_hdlc_state
r_void
id|init_hdlc_state
c_func
(paren
r_struct
id|hdlc_state
op_star
id|stateptr
comma
r_int
id|mode
)paren
(brace
id|stateptr-&gt;state
op_assign
id|HDLC_ZERO_SEARCH
suffix:semicolon
id|stateptr-&gt;r_one
op_assign
l_int|0
suffix:semicolon
id|stateptr-&gt;r_val
op_assign
l_int|0
suffix:semicolon
id|stateptr-&gt;o_bitcnt
op_assign
l_int|0
suffix:semicolon
id|stateptr-&gt;i_bitcnt
op_assign
l_int|0
suffix:semicolon
id|stateptr-&gt;insane_mode
op_assign
id|mode
suffix:semicolon
)brace
multiline_comment|/* Optimization suggestion: A similar state machine could surely&n; * be developed for this function as well.&n; */
DECL|function|read_raw_hdlc_data
r_int
id|read_raw_hdlc_data
c_func
(paren
r_struct
id|hdlc_state
op_star
id|saved_state
comma
id|u_char
op_star
id|src
comma
id|u_int
id|slen
comma
id|u_char
op_star
id|dst
comma
id|u_int
id|dsize
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_register
id|u_char
id|val
suffix:semicolon
r_register
id|u_char
id|state
op_assign
id|saved_state-&gt;state
suffix:semicolon
r_register
id|u_char
id|r_one
op_assign
id|saved_state-&gt;r_one
suffix:semicolon
r_register
id|u_char
id|r_val
op_assign
id|saved_state-&gt;r_val
suffix:semicolon
r_register
id|u_int
id|o_bitcnt
op_assign
id|saved_state-&gt;o_bitcnt
suffix:semicolon
r_register
id|u_int
id|i_bitcnt
op_assign
id|saved_state-&gt;i_bitcnt
suffix:semicolon
r_register
id|u_int
id|fcs
op_assign
id|saved_state-&gt;fcs
suffix:semicolon
r_register
id|u_int
op_star
id|isrc
op_assign
(paren
id|u_int
op_star
)paren
id|src
suffix:semicolon
multiline_comment|/* Use i_bitcnt (bit offset into source buffer) to reload &quot;val&quot;&n;&t; * in case we&squot;re starting up again partway through a source buffer&n;&t; */
r_if
c_cond
(paren
(paren
id|i_bitcnt
op_rshift
l_int|3
)paren
OL
id|slen
)paren
(brace
r_if
c_cond
(paren
id|saved_state-&gt;insane_mode
op_eq
l_int|1
)paren
(brace
id|val
op_assign
id|isrc
(braket
(paren
id|i_bitcnt
op_rshift
l_int|3
)paren
)braket
op_amp
l_int|0xff
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|saved_state-&gt;insane_mode
op_eq
l_int|2
)paren
(brace
id|val
op_assign
(paren
id|isrc
(braket
id|i_bitcnt
op_rshift
l_int|3
)braket
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
)brace
r_else
(brace
id|val
op_assign
id|src
(braket
id|i_bitcnt
op_rshift
l_int|3
)braket
suffix:semicolon
)brace
id|val
op_rshift_assign
id|i_bitcnt
op_amp
l_int|7
suffix:semicolon
)brace
multiline_comment|/* One bit per loop.  Keep going until we&squot;ve got something to&n;&t; * report (retval != 0), or we exhaust the source buffer&n;&t; */
r_while
c_loop
(paren
(paren
id|retval
op_eq
l_int|0
)paren
op_logical_and
(paren
(paren
id|i_bitcnt
op_rshift
l_int|3
)paren
OL
id|slen
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|i_bitcnt
op_amp
l_int|7
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|saved_state-&gt;insane_mode
op_eq
l_int|1
)paren
(brace
id|val
op_assign
id|isrc
(braket
(paren
id|i_bitcnt
op_rshift
l_int|3
)paren
)braket
op_amp
l_int|0xff
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|saved_state-&gt;insane_mode
op_eq
l_int|2
)paren
(brace
id|val
op_assign
(paren
id|isrc
(braket
id|i_bitcnt
op_rshift
l_int|3
)braket
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
)brace
r_else
(brace
id|val
op_assign
id|src
(braket
id|i_bitcnt
op_rshift
l_int|3
)braket
suffix:semicolon
)brace
macro_line|#ifdef DEBUGME
id|printf
c_func
(paren
l_string|&quot;Input byte %d: 0x%2x&bslash;n&quot;
comma
id|i_bitcnt
op_rshift
l_int|3
comma
id|val
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|val
op_eq
l_int|0xff
)paren
(brace
id|state
op_assign
id|HDLC_ZERO_SEARCH
suffix:semicolon
id|o_bitcnt
op_assign
l_int|0
suffix:semicolon
id|r_one
op_assign
l_int|0
suffix:semicolon
id|i_bitcnt
op_add_assign
l_int|8
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
macro_line|#ifdef DEBUGME
multiline_comment|/* printf(&quot;Data bit=%d (%d/%d)&bslash;n&quot;, val&amp;1, i_bitcnt&gt;&gt;3, i_bitcnt&amp;7);*/
macro_line|#endif
r_if
c_cond
(paren
id|state
op_eq
id|HDLC_ZERO_SEARCH
)paren
(brace
r_if
c_cond
(paren
id|val
op_amp
l_int|1
)paren
(brace
id|r_one
op_increment
suffix:semicolon
)brace
r_else
(brace
id|r_one
op_assign
l_int|0
suffix:semicolon
id|state
op_assign
id|HDLC_FLAG_SEARCH
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|state
op_eq
id|HDLC_FLAG_SEARCH
)paren
(brace
r_if
c_cond
(paren
id|val
op_amp
l_int|1
)paren
(brace
id|r_one
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|r_one
OG
l_int|6
)paren
(brace
id|state
op_assign
id|HDLC_ZERO_SEARCH
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|r_one
op_eq
l_int|6
)paren
(brace
id|o_bitcnt
op_assign
l_int|0
suffix:semicolon
id|r_val
op_assign
l_int|0
suffix:semicolon
id|state
op_assign
id|HDLC_FLAG_FOUND
suffix:semicolon
)brace
id|r_one
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|state
op_eq
id|HDLC_FLAG_FOUND
)paren
(brace
r_if
c_cond
(paren
id|val
op_amp
l_int|1
)paren
(brace
id|r_one
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|r_one
OG
l_int|6
)paren
(brace
id|state
op_assign
id|HDLC_ZERO_SEARCH
suffix:semicolon
)brace
r_else
(brace
id|r_val
op_rshift_assign
l_int|1
suffix:semicolon
id|r_val
op_or_assign
l_int|0x80
suffix:semicolon
id|o_bitcnt
op_increment
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|r_one
op_eq
l_int|6
)paren
(brace
id|o_bitcnt
op_assign
l_int|0
suffix:semicolon
id|r_val
op_assign
l_int|0
suffix:semicolon
id|r_one
op_assign
l_int|0
suffix:semicolon
id|i_bitcnt
op_increment
suffix:semicolon
id|val
op_rshift_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|r_one
op_ne
l_int|5
)paren
(brace
id|r_val
op_rshift_assign
l_int|1
suffix:semicolon
id|r_val
op_and_assign
l_int|0x7f
suffix:semicolon
id|o_bitcnt
op_increment
suffix:semicolon
)brace
id|r_one
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|state
op_ne
id|HDLC_ZERO_SEARCH
)paren
op_logical_and
op_logical_neg
(paren
id|o_bitcnt
op_amp
l_int|7
)paren
)paren
(brace
macro_line|#ifdef DEBUGME
id|printf
c_func
(paren
l_string|&quot;HDLC_FRAME_FOUND at i_bitcnt:%d&bslash;n&quot;
comma
id|i_bitcnt
)paren
suffix:semicolon
macro_line|#endif
id|state
op_assign
id|HDLC_FRAME_FOUND
suffix:semicolon
id|fcs
op_assign
id|PPP_INITFCS
suffix:semicolon
id|dst
(braket
l_int|0
)braket
op_assign
id|r_val
suffix:semicolon
id|fcs
op_assign
id|PPP_FCS
(paren
id|fcs
comma
id|r_val
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|state
op_eq
id|HDLC_FRAME_FOUND
)paren
(brace
r_if
c_cond
(paren
id|val
op_amp
l_int|1
)paren
(brace
id|r_one
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|r_one
OG
l_int|6
)paren
(brace
id|state
op_assign
id|HDLC_ZERO_SEARCH
suffix:semicolon
id|o_bitcnt
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|r_val
op_rshift_assign
l_int|1
suffix:semicolon
id|r_val
op_or_assign
l_int|0x80
suffix:semicolon
id|o_bitcnt
op_increment
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
id|r_one
op_eq
l_int|6
)paren
(brace
id|r_val
op_assign
l_int|0
suffix:semicolon
id|r_one
op_assign
l_int|0
suffix:semicolon
id|o_bitcnt
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|o_bitcnt
op_amp
l_int|7
)paren
(brace
multiline_comment|/* Alignment error */
macro_line|#ifdef DEBUGME
id|printf
c_func
(paren
l_string|&quot;Alignment error&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|state
op_assign
id|HDLC_FLAG_SEARCH
suffix:semicolon
id|retval
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|fcs
op_eq
id|PPP_GOODFCS
)paren
(brace
multiline_comment|/* Valid frame */
id|state
op_assign
id|HDLC_FLAG_FOUND
suffix:semicolon
id|retval
op_assign
(paren
id|o_bitcnt
op_rshift
l_int|3
)paren
op_minus
l_int|3
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* CRC error */
macro_line|#ifdef DEBUGME
id|printf
c_func
(paren
l_string|&quot;CRC error; fcs was 0x%x, should have been 0x%x&bslash;n&quot;
comma
id|fcs
comma
id|PPP_GOODFCS
)paren
suffix:semicolon
macro_line|#endif
id|state
op_assign
id|HDLC_FLAG_FOUND
suffix:semicolon
id|retval
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|r_one
op_eq
l_int|5
)paren
(brace
id|r_one
op_assign
l_int|0
suffix:semicolon
id|i_bitcnt
op_increment
suffix:semicolon
id|val
op_rshift_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
(brace
id|r_val
op_rshift_assign
l_int|1
suffix:semicolon
id|r_val
op_and_assign
l_int|0x7f
suffix:semicolon
id|o_bitcnt
op_increment
suffix:semicolon
)brace
id|r_one
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|state
op_eq
id|HDLC_FRAME_FOUND
)paren
op_logical_and
op_logical_neg
(paren
id|o_bitcnt
op_amp
l_int|7
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|o_bitcnt
op_rshift
l_int|3
)paren
op_ge
id|dsize
)paren
(brace
multiline_comment|/* Buffer overflow error */
macro_line|#ifdef DEBUGME
id|printf
c_func
(paren
l_string|&quot;Buffer overflow error&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|r_val
op_assign
l_int|0
suffix:semicolon
id|state
op_assign
id|HDLC_FLAG_SEARCH
suffix:semicolon
id|retval
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|dst
(braket
(paren
id|o_bitcnt
op_rshift
l_int|3
)paren
op_minus
l_int|1
)braket
op_assign
id|r_val
suffix:semicolon
id|fcs
op_assign
id|PPP_FCS
(paren
id|fcs
comma
id|r_val
)paren
suffix:semicolon
macro_line|#ifdef DEBUGME
id|printf
c_func
(paren
l_string|&quot;Output byte %d: 0x%02x; FCS 0x%04x&bslash;n&quot;
comma
(paren
id|o_bitcnt
op_rshift
l_int|3
)paren
op_minus
l_int|1
comma
id|r_val
comma
id|fcs
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
)brace
id|i_bitcnt
op_increment
suffix:semicolon
id|val
op_rshift_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* We exhausted the source buffer before anything else happened&n;&t; * (retval==0).  Reset i_bitcnt in expectation of a new source&n;&t; * buffer.  Other, we either had an error or a valid frame, so&n;&t; * reset o_bitcnt in expectation of a new destination buffer.&n;&t; */
r_if
c_cond
(paren
id|retval
op_eq
l_int|0
)paren
(brace
id|i_bitcnt
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|o_bitcnt
op_assign
l_int|0
suffix:semicolon
)brace
id|saved_state-&gt;state
op_assign
id|state
suffix:semicolon
id|saved_state-&gt;r_one
op_assign
id|r_one
suffix:semicolon
id|saved_state-&gt;r_val
op_assign
id|r_val
suffix:semicolon
id|saved_state-&gt;fcs
op_assign
id|fcs
suffix:semicolon
id|saved_state-&gt;o_bitcnt
op_assign
id|o_bitcnt
suffix:semicolon
id|saved_state-&gt;i_bitcnt
op_assign
id|i_bitcnt
suffix:semicolon
r_return
(paren
id|retval
)paren
suffix:semicolon
)brace
macro_line|#ifdef DEBUGME
DECL|variable|buffer
r_char
id|buffer
(braket
l_int|1024
)braket
suffix:semicolon
DECL|variable|obuffer
r_char
id|obuffer
(braket
l_int|1024
)braket
suffix:semicolon
DECL|function|main
id|main
c_func
(paren
)paren
(brace
r_int
id|buflen
op_assign
l_int|0
suffix:semicolon
r_int
id|len
suffix:semicolon
r_struct
id|hdlc_state
id|hdlc_state
suffix:semicolon
r_while
c_loop
(paren
(paren
id|buffer
(braket
id|buflen
)braket
op_assign
id|getc
c_func
(paren
id|stdin
)paren
)paren
op_ne
id|EOF
op_logical_and
id|buflen
OL
l_int|1024
)paren
(brace
id|buflen
op_increment
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;buflen = %d&bslash;n&quot;
comma
id|buflen
)paren
suffix:semicolon
id|init_hdlc_state
c_func
(paren
op_amp
id|hdlc_state
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
op_assign
id|read_raw_hdlc_data
c_func
(paren
op_amp
id|hdlc_state
comma
id|buffer
comma
id|buflen
comma
id|obuffer
comma
l_int|1024
)paren
)paren
(brace
r_if
c_cond
(paren
id|len
op_eq
op_minus
l_int|1
)paren
id|printf
c_func
(paren
l_string|&quot;Error @ byte %d/bit %d&bslash;n&quot;
comma
id|hdlc_state.i_bitcnt
op_rshift
l_int|3
comma
id|hdlc_state.i_bitcnt
op_amp
l_int|7
)paren
suffix:semicolon
r_else
(brace
id|printf
c_func
(paren
l_string|&quot;Frame received: len %d&bslash;n&quot;
comma
id|len
)paren
suffix:semicolon
)brace
)brace
id|printf
c_func
(paren
l_string|&quot;Done&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
