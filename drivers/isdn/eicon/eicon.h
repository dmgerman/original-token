multiline_comment|/* $Id: eicon.h,v 1.5 1999/03/29 11:19:41 armin Exp $&n; *&n; * ISDN low-level module for Eicon.Diehl active ISDN-Cards.&n; *&n; * Copyright 1998    by Fritz Elfert (fritz@wuemaus.franken.de)&n; * Copyright 1998,99 by Armin Schindler (mac@melware.de) &n; * Copyright 1999    Cytronics &amp; Melware (info@melware.de)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n; *&n; * $Log: eicon.h,v $&n; * Revision 1.5  1999/03/29 11:19:41  armin&n; * I/O stuff now in seperate file (eicon_io.c)&n; * Old ISA type cards (S,SX,SCOM,Quadro,S2M) implemented.&n; *&n; * Revision 1.4  1999/03/02 12:37:42  armin&n; * Added some important checks.&n; * Analog Modem with DSP.&n; * Channels will be added to Link-Level after loading firmware.&n; *&n; * Revision 1.3  1999/01/24 20:14:07  armin&n; * Changed and added debug stuff.&n; * Better data sending. (still problems with tty&squot;s flip buffer)&n; *&n; * Revision 1.2  1999/01/10 18:46:04  armin&n; * Bug with wrong values in HLC fixed.&n; * Bytes to send are counted and limited now.&n; *&n; * Revision 1.1  1999/01/01 18:09:41  armin&n; * First checkin of new eicon driver.&n; * DIVA-Server BRI/PCI and PRI/PCI are supported.&n; * Old diehl code is obsolete.&n; *&n; *&n; */
macro_line|#ifndef eicon_h
DECL|macro|eicon_h
mdefine_line|#define eicon_h
DECL|macro|EICON_IOCTL_SETMMIO
mdefine_line|#define EICON_IOCTL_SETMMIO   0
DECL|macro|EICON_IOCTL_GETMMIO
mdefine_line|#define EICON_IOCTL_GETMMIO   1
DECL|macro|EICON_IOCTL_SETIRQ
mdefine_line|#define EICON_IOCTL_SETIRQ    2
DECL|macro|EICON_IOCTL_GETIRQ
mdefine_line|#define EICON_IOCTL_GETIRQ    3
DECL|macro|EICON_IOCTL_LOADBOOT
mdefine_line|#define EICON_IOCTL_LOADBOOT  4
DECL|macro|EICON_IOCTL_ADDCARD
mdefine_line|#define EICON_IOCTL_ADDCARD   5
DECL|macro|EICON_IOCTL_GETTYPE
mdefine_line|#define EICON_IOCTL_GETTYPE   6
DECL|macro|EICON_IOCTL_LOADPCI
mdefine_line|#define EICON_IOCTL_LOADPCI   7 
DECL|macro|EICON_IOCTL_LOADISA
mdefine_line|#define EICON_IOCTL_LOADISA   8 
DECL|macro|EICON_IOCTL_GETVER
mdefine_line|#define EICON_IOCTL_GETVER    9 
DECL|macro|EICON_IOCTL_MANIF
mdefine_line|#define EICON_IOCTL_MANIF    90 
DECL|macro|EICON_IOCTL_FREEIT
mdefine_line|#define EICON_IOCTL_FREEIT   97
DECL|macro|EICON_IOCTL_TEST
mdefine_line|#define EICON_IOCTL_TEST     98
DECL|macro|EICON_IOCTL_DEBUGVAR
mdefine_line|#define EICON_IOCTL_DEBUGVAR 99
multiline_comment|/* Bus types */
DECL|macro|EICON_BUS_ISA
mdefine_line|#define EICON_BUS_ISA          1
DECL|macro|EICON_BUS_MCA
mdefine_line|#define EICON_BUS_MCA          2
DECL|macro|EICON_BUS_PCI
mdefine_line|#define EICON_BUS_PCI          3
multiline_comment|/* Constants for describing Card-Type */
DECL|macro|EICON_CTYPE_S
mdefine_line|#define EICON_CTYPE_S            0
DECL|macro|EICON_CTYPE_SX
mdefine_line|#define EICON_CTYPE_SX           1
DECL|macro|EICON_CTYPE_SCOM
mdefine_line|#define EICON_CTYPE_SCOM         2
DECL|macro|EICON_CTYPE_QUADRO
mdefine_line|#define EICON_CTYPE_QUADRO       3
DECL|macro|EICON_CTYPE_S2M
mdefine_line|#define EICON_CTYPE_S2M          4
DECL|macro|EICON_CTYPE_MAESTRA
mdefine_line|#define EICON_CTYPE_MAESTRA      5
DECL|macro|EICON_CTYPE_MAESTRAQ
mdefine_line|#define EICON_CTYPE_MAESTRAQ     6
DECL|macro|EICON_CTYPE_MAESTRAQ_U
mdefine_line|#define EICON_CTYPE_MAESTRAQ_U   7
DECL|macro|EICON_CTYPE_MAESTRAP
mdefine_line|#define EICON_CTYPE_MAESTRAP     8
DECL|macro|EICON_CTYPE_ISABRI
mdefine_line|#define EICON_CTYPE_ISABRI       0x10
DECL|macro|EICON_CTYPE_ISAPRI
mdefine_line|#define EICON_CTYPE_ISAPRI       0x20
DECL|macro|EICON_CTYPE_MASK
mdefine_line|#define EICON_CTYPE_MASK         0x0f
DECL|macro|EICON_CTYPE_QUADRO_NR
mdefine_line|#define EICON_CTYPE_QUADRO_NR(n) (n&lt;&lt;4)
DECL|macro|MAX_HEADER_LEN
mdefine_line|#define MAX_HEADER_LEN 10
multiline_comment|/* Struct for adding new cards */
DECL|struct|eicon_cdef
r_typedef
r_struct
id|eicon_cdef
(brace
DECL|member|membase
r_int
id|membase
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|id
r_char
id|id
(braket
l_int|10
)braket
suffix:semicolon
DECL|typedef|eicon_cdef
)brace
id|eicon_cdef
suffix:semicolon
DECL|macro|EICON_ISA_BOOT_MEMCHK
mdefine_line|#define EICON_ISA_BOOT_MEMCHK 1
DECL|macro|EICON_ISA_BOOT_NORMAL
mdefine_line|#define EICON_ISA_BOOT_NORMAL 2
multiline_comment|/* Struct for downloading protocol via ioctl for ISA cards */
r_typedef
r_struct
(brace
multiline_comment|/* start-up parameters */
DECL|member|tei
r_int
r_char
id|tei
suffix:semicolon
DECL|member|nt2
r_int
r_char
id|nt2
suffix:semicolon
DECL|member|skip1
r_int
r_char
id|skip1
suffix:semicolon
DECL|member|WatchDog
r_int
r_char
id|WatchDog
suffix:semicolon
DECL|member|Permanent
r_int
r_char
id|Permanent
suffix:semicolon
DECL|member|XInterface
r_int
r_char
id|XInterface
suffix:semicolon
DECL|member|StableL2
r_int
r_char
id|StableL2
suffix:semicolon
DECL|member|NoOrderCheck
r_int
r_char
id|NoOrderCheck
suffix:semicolon
DECL|member|HandsetType
r_int
r_char
id|HandsetType
suffix:semicolon
DECL|member|skip2
r_int
r_char
id|skip2
suffix:semicolon
DECL|member|LowChannel
r_int
r_char
id|LowChannel
suffix:semicolon
DECL|member|ProtVersion
r_int
r_char
id|ProtVersion
suffix:semicolon
DECL|member|Crc4
r_int
r_char
id|Crc4
suffix:semicolon
DECL|member|Loopback
r_int
r_char
id|Loopback
suffix:semicolon
DECL|member|oad
r_int
r_char
id|oad
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|osa
r_int
r_char
id|osa
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|spid
r_int
r_char
id|spid
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|boot_opt
r_int
r_char
id|boot_opt
suffix:semicolon
DECL|member|bootstrap_len
r_int
r_int
id|bootstrap_len
suffix:semicolon
DECL|member|firmware_len
r_int
r_int
id|firmware_len
suffix:semicolon
DECL|member|code
r_int
r_char
id|code
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Rest (bootstrap- and firmware code) will be allocated */
DECL|typedef|eicon_isa_codebuf
)brace
id|eicon_isa_codebuf
suffix:semicolon
multiline_comment|/* Struct for downloading protocol via ioctl for PCI cards */
r_typedef
r_struct
(brace
multiline_comment|/* start-up parameters */
DECL|member|tei
r_int
r_char
id|tei
suffix:semicolon
DECL|member|nt2
r_int
r_char
id|nt2
suffix:semicolon
DECL|member|WatchDog
r_int
r_char
id|WatchDog
suffix:semicolon
DECL|member|Permanent
r_int
r_char
id|Permanent
suffix:semicolon
DECL|member|XInterface
r_int
r_char
id|XInterface
suffix:semicolon
DECL|member|StableL2
r_int
r_char
id|StableL2
suffix:semicolon
DECL|member|NoOrderCheck
r_int
r_char
id|NoOrderCheck
suffix:semicolon
DECL|member|HandsetType
r_int
r_char
id|HandsetType
suffix:semicolon
DECL|member|LowChannel
r_int
r_char
id|LowChannel
suffix:semicolon
DECL|member|ProtVersion
r_int
r_char
id|ProtVersion
suffix:semicolon
DECL|member|Crc4
r_int
r_char
id|Crc4
suffix:semicolon
DECL|member|NoHscx30Mode
r_int
r_char
id|NoHscx30Mode
suffix:semicolon
multiline_comment|/* switch PRI into No HSCX30 test mode */
DECL|member|Loopback
r_int
r_char
id|Loopback
suffix:semicolon
multiline_comment|/* switch card into Loopback mode */
DECL|struct|q931_link_s
r_struct
id|q931_link_s
(brace
DECL|member|oad
r_int
r_char
id|oad
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|osa
r_int
r_char
id|osa
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|spid
r_int
r_char
id|spid
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|l
)brace
id|l
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|protocol_len
r_int
r_int
id|protocol_len
suffix:semicolon
DECL|member|dsp_code_num
r_int
r_int
id|dsp_code_num
suffix:semicolon
DECL|member|dsp_code_len
r_int
r_int
id|dsp_code_len
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|code
r_int
r_char
id|code
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Rest (protocol- and dsp code) will be allocated */
DECL|typedef|eicon_pci_codebuf
)brace
id|eicon_pci_codebuf
suffix:semicolon
multiline_comment|/* Data for downloading protocol via ioctl */
r_typedef
r_union
(brace
DECL|member|isa
id|eicon_isa_codebuf
id|isa
suffix:semicolon
DECL|member|pci
id|eicon_pci_codebuf
id|pci
suffix:semicolon
DECL|typedef|eicon_codebuf
)brace
id|eicon_codebuf
suffix:semicolon
multiline_comment|/* Data for Management interface */
r_typedef
r_struct
(brace
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|pos
r_int
id|pos
suffix:semicolon
DECL|member|length
r_int
id|length
(braket
l_int|50
)braket
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
l_int|700
)braket
suffix:semicolon
DECL|typedef|eicon_manifbuf
)brace
id|eicon_manifbuf
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* Kernel includes */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/isdnif.h&gt;
r_typedef
r_struct
(brace
DECL|member|length
id|__u16
id|length
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
multiline_comment|/* length of data/parameter field */
DECL|member|P
id|__u8
id|P
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* data/parameter field */
DECL|typedef|eicon_PBUFFER
)brace
id|eicon_PBUFFER
suffix:semicolon
macro_line|#include &quot;eicon_isa.h&quot;
multiline_comment|/* Macro for delay via schedule() */
DECL|macro|SLEEP
mdefine_line|#define SLEEP(j) {                     &bslash;&n;  current-&gt;state = TASK_INTERRUPTIBLE; &bslash;&n;  schedule_timeout(j);                 &bslash;&n;}
macro_line|#endif /* KERNEL */
DECL|macro|DSP_COMBIFILE_FORMAT_IDENTIFICATION_SIZE
mdefine_line|#define DSP_COMBIFILE_FORMAT_IDENTIFICATION_SIZE 48
DECL|macro|DSP_COMBIFILE_FORMAT_VERSION_BCD
mdefine_line|#define DSP_COMBIFILE_FORMAT_VERSION_BCD    0x0100
DECL|macro|DSP_FILE_FORMAT_IDENTIFICATION_SIZE
mdefine_line|#define DSP_FILE_FORMAT_IDENTIFICATION_SIZE 48
DECL|macro|DSP_FILE_FORMAT_VERSION_BCD
mdefine_line|#define DSP_FILE_FORMAT_VERSION_BCD         0x0100
DECL|struct|tag_dsp_combifile_header
r_typedef
r_struct
id|tag_dsp_combifile_header
(brace
DECL|member|format_identification
r_char
id|format_identification
(braket
id|DSP_COMBIFILE_FORMAT_IDENTIFICATION_SIZE
)braket
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|format_version_bcd
id|__u16
id|format_version_bcd
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|header_size
id|__u16
id|header_size
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|combifile_description_size
id|__u16
id|combifile_description_size
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|directory_entries
id|__u16
id|directory_entries
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|directory_size
id|__u16
id|directory_size
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|download_count
id|__u16
id|download_count
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|usage_mask_size
id|__u16
id|usage_mask_size
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|t_dsp_combifile_header
)brace
id|t_dsp_combifile_header
suffix:semicolon
DECL|struct|tag_dsp_combifile_directory_entry
r_typedef
r_struct
id|tag_dsp_combifile_directory_entry
(brace
DECL|member|card_type_number
id|__u16
id|card_type_number
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|file_set_number
id|__u16
id|file_set_number
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|t_dsp_combifile_directory_entry
)brace
id|t_dsp_combifile_directory_entry
suffix:semicolon
DECL|struct|tag_dsp_file_header
r_typedef
r_struct
id|tag_dsp_file_header
(brace
DECL|member|format_identification
r_char
id|format_identification
(braket
id|DSP_FILE_FORMAT_IDENTIFICATION_SIZE
)braket
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|format_version_bcd
id|__u16
id|format_version_bcd
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|download_id
id|__u16
id|download_id
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|download_flags
id|__u16
id|download_flags
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|required_processing_power
id|__u16
id|required_processing_power
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|interface_channel_count
id|__u16
id|interface_channel_count
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|header_size
id|__u16
id|header_size
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|download_description_size
id|__u16
id|download_description_size
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|memory_block_table_size
id|__u16
id|memory_block_table_size
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|memory_block_count
id|__u16
id|memory_block_count
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|segment_table_size
id|__u16
id|segment_table_size
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|segment_count
id|__u16
id|segment_count
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|symbol_table_size
id|__u16
id|symbol_table_size
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|symbol_count
id|__u16
id|symbol_count
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|total_data_size_dm
id|__u16
id|total_data_size_dm
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|data_block_count_dm
id|__u16
id|data_block_count_dm
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|total_data_size_pm
id|__u16
id|total_data_size_pm
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|data_block_count_pm
id|__u16
id|data_block_count_pm
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|t_dsp_file_header
)brace
id|t_dsp_file_header
suffix:semicolon
DECL|struct|tag_dsp_memory_block_desc
r_typedef
r_struct
id|tag_dsp_memory_block_desc
(brace
DECL|member|alias_memory_block
id|__u16
id|alias_memory_block
suffix:semicolon
DECL|member|memory_type
id|__u16
id|memory_type
suffix:semicolon
DECL|member|address
id|__u16
id|address
suffix:semicolon
DECL|member|size
id|__u16
id|size
suffix:semicolon
multiline_comment|/* DSP words */
DECL|typedef|t_dsp_memory_block_desc
)brace
id|t_dsp_memory_block_desc
suffix:semicolon
DECL|struct|tag_dsp_segment_desc
r_typedef
r_struct
id|tag_dsp_segment_desc
(brace
DECL|member|memory_block
id|__u16
id|memory_block
suffix:semicolon
DECL|member|attributes
id|__u16
id|attributes
suffix:semicolon
DECL|member|base
id|__u16
id|base
suffix:semicolon
DECL|member|size
id|__u16
id|size
suffix:semicolon
DECL|member|alignment
id|__u16
id|alignment
suffix:semicolon
multiline_comment|/* ==0 -&gt; no other legal start address than base */
DECL|typedef|t_dsp_segment_desc
)brace
id|t_dsp_segment_desc
suffix:semicolon
DECL|struct|tag_dsp_symbol_desc
r_typedef
r_struct
id|tag_dsp_symbol_desc
(brace
DECL|member|symbol_id
id|__u16
id|symbol_id
suffix:semicolon
DECL|member|segment
id|__u16
id|segment
suffix:semicolon
DECL|member|offset
id|__u16
id|offset
suffix:semicolon
DECL|member|size
id|__u16
id|size
suffix:semicolon
multiline_comment|/* DSP words */
DECL|typedef|t_dsp_symbol_desc
)brace
id|t_dsp_symbol_desc
suffix:semicolon
DECL|struct|tag_dsp_data_block_header
r_typedef
r_struct
id|tag_dsp_data_block_header
(brace
DECL|member|attributes
id|__u16
id|attributes
suffix:semicolon
DECL|member|segment
id|__u16
id|segment
suffix:semicolon
DECL|member|offset
id|__u16
id|offset
suffix:semicolon
DECL|member|size
id|__u16
id|size
suffix:semicolon
multiline_comment|/* DSP words */
DECL|typedef|t_dsp_data_block_header
)brace
id|t_dsp_data_block_header
suffix:semicolon
DECL|struct|tag_dsp_download_desc
r_typedef
r_struct
id|tag_dsp_download_desc
multiline_comment|/* be sure to keep native alignment for MAESTRA&squot;s */
(brace
DECL|member|download_id
id|__u16
id|download_id
suffix:semicolon
DECL|member|download_flags
id|__u16
id|download_flags
suffix:semicolon
DECL|member|required_processing_power
id|__u16
id|required_processing_power
suffix:semicolon
DECL|member|interface_channel_count
id|__u16
id|interface_channel_count
suffix:semicolon
DECL|member|excess_header_size
id|__u16
id|excess_header_size
suffix:semicolon
DECL|member|memory_block_count
id|__u16
id|memory_block_count
suffix:semicolon
DECL|member|segment_count
id|__u16
id|segment_count
suffix:semicolon
DECL|member|symbol_count
id|__u16
id|symbol_count
suffix:semicolon
DECL|member|data_block_count_dm
id|__u16
id|data_block_count_dm
suffix:semicolon
DECL|member|data_block_count_pm
id|__u16
id|data_block_count_pm
suffix:semicolon
DECL|member|p_excess_header_data
id|__u8
op_star
id|p_excess_header_data
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|p_download_description
r_char
op_star
id|p_download_description
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|p_memory_block_table
id|t_dsp_memory_block_desc
op_star
id|p_memory_block_table
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|p_segment_table
id|t_dsp_segment_desc
op_star
id|p_segment_table
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|p_symbol_table
id|t_dsp_symbol_desc
op_star
id|p_symbol_table
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|p_data_blocks_dm
id|__u16
op_star
id|p_data_blocks_dm
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|p_data_blocks_pm
id|__u16
op_star
id|p_data_blocks_pm
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|typedef|t_dsp_download_desc
)brace
id|t_dsp_download_desc
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_typedef
r_struct
(brace
DECL|member|Req
id|__u8
id|Req
suffix:semicolon
multiline_comment|/* pending request          */
DECL|member|Rc
id|__u8
id|Rc
suffix:semicolon
multiline_comment|/* return code received     */
DECL|member|Ind
id|__u8
id|Ind
suffix:semicolon
multiline_comment|/* indication received      */
DECL|member|ReqCh
id|__u8
id|ReqCh
suffix:semicolon
multiline_comment|/* channel of current Req   */
DECL|member|RcCh
id|__u8
id|RcCh
suffix:semicolon
multiline_comment|/* channel of current Rc    */
DECL|member|IndCh
id|__u8
id|IndCh
suffix:semicolon
multiline_comment|/* channel of current Ind   */
DECL|member|D3Id
id|__u8
id|D3Id
suffix:semicolon
multiline_comment|/* ID used by this entity   */
DECL|member|B2Id
id|__u8
id|B2Id
suffix:semicolon
multiline_comment|/* ID used by this entity   */
DECL|member|GlobalId
id|__u8
id|GlobalId
suffix:semicolon
multiline_comment|/* reserved field           */
DECL|member|XNum
id|__u8
id|XNum
suffix:semicolon
multiline_comment|/* number of X-buffers      */
DECL|member|RNum
id|__u8
id|RNum
suffix:semicolon
multiline_comment|/* number of R-buffers      */
DECL|member|X
r_struct
id|sk_buff_head
id|X
suffix:semicolon
multiline_comment|/* X-buffer queue           */
DECL|member|R
r_struct
id|sk_buff_head
id|R
suffix:semicolon
multiline_comment|/* R-buffer queue           */
DECL|member|RNR
id|__u8
id|RNR
suffix:semicolon
multiline_comment|/* receive not ready flag   */
DECL|member|complete
id|__u8
id|complete
suffix:semicolon
multiline_comment|/* receive complete status  */
DECL|member|busy
id|__u8
id|busy
suffix:semicolon
multiline_comment|/* busy flag                */
DECL|member|ref
id|__u16
id|ref
suffix:semicolon
multiline_comment|/* saved reference          */
DECL|typedef|entity
)brace
id|entity
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|No
r_int
id|No
suffix:semicolon
multiline_comment|/* Channel Number&t;        */
DECL|member|callref
r_int
r_int
id|callref
suffix:semicolon
multiline_comment|/* Call Reference              */
DECL|member|fsm_state
r_int
r_int
id|fsm_state
suffix:semicolon
multiline_comment|/* Current D-Channel state     */
DECL|member|eazmask
r_int
r_int
id|eazmask
suffix:semicolon
multiline_comment|/* EAZ-Mask for this Channel   */
DECL|member|queued
r_int
r_int
id|queued
suffix:semicolon
multiline_comment|/* User-Data Bytes in TX queue */
DECL|member|waitq
r_int
r_int
id|waitq
suffix:semicolon
multiline_comment|/* User-Data Bytes in wait queue */
DECL|member|waitpq
r_int
r_int
id|waitpq
suffix:semicolon
multiline_comment|/* User-Data Bytes in packet queue */
DECL|member|plci
r_int
r_int
id|plci
suffix:semicolon
DECL|member|ncci
r_int
r_int
id|ncci
suffix:semicolon
DECL|member|l2prot
r_int
r_char
id|l2prot
suffix:semicolon
multiline_comment|/* Layer 2 protocol            */
DECL|member|l3prot
r_int
r_char
id|l3prot
suffix:semicolon
multiline_comment|/* Layer 3 protocol            */
DECL|member|e
id|entity
id|e
suffix:semicolon
multiline_comment|/* Entity  &t;&t;&t;*/
DECL|member|cpn
r_char
id|cpn
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* remember cpn&t;&t;*/
DECL|member|oad
r_char
id|oad
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* remember oad&t;&t;*/
DECL|member|cause
r_int
r_char
id|cause
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Last Cause&t;&t;&t;*/
DECL|member|si1
r_int
r_char
id|si1
suffix:semicolon
DECL|member|si2
r_int
r_char
id|si2
suffix:semicolon
DECL|typedef|eicon_chan
)brace
id|eicon_chan
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ptr
id|eicon_chan
op_star
id|ptr
suffix:semicolon
DECL|typedef|eicon_chan_ptr
)brace
id|eicon_chan_ptr
suffix:semicolon
macro_line|#include &quot;eicon_pci.h&quot;
DECL|macro|EICON_FLAGS_RUNNING
mdefine_line|#define EICON_FLAGS_RUNNING  1 /* Cards driver activated */
DECL|macro|EICON_FLAGS_PVALID
mdefine_line|#define EICON_FLAGS_PVALID   2 /* Cards port is valid    */
DECL|macro|EICON_FLAGS_IVALID
mdefine_line|#define EICON_FLAGS_IVALID   4 /* Cards irq is valid     */
DECL|macro|EICON_FLAGS_MVALID
mdefine_line|#define EICON_FLAGS_MVALID   8 /* Cards membase is valid */
DECL|macro|EICON_FLAGS_LOADED
mdefine_line|#define EICON_FLAGS_LOADED   8 /* Firmware loaded        */
DECL|macro|EICON_BCH
mdefine_line|#define EICON_BCH            2 /* # of channels per card */
multiline_comment|/* D-Channel states */
DECL|macro|EICON_STATE_NULL
mdefine_line|#define EICON_STATE_NULL     0
DECL|macro|EICON_STATE_ICALL
mdefine_line|#define EICON_STATE_ICALL    1
DECL|macro|EICON_STATE_OCALL
mdefine_line|#define EICON_STATE_OCALL    2
DECL|macro|EICON_STATE_IWAIT
mdefine_line|#define EICON_STATE_IWAIT    3
DECL|macro|EICON_STATE_OWAIT
mdefine_line|#define EICON_STATE_OWAIT    4
DECL|macro|EICON_STATE_IBWAIT
mdefine_line|#define EICON_STATE_IBWAIT   5
DECL|macro|EICON_STATE_OBWAIT
mdefine_line|#define EICON_STATE_OBWAIT   6
DECL|macro|EICON_STATE_BWAIT
mdefine_line|#define EICON_STATE_BWAIT    7
DECL|macro|EICON_STATE_BHWAIT
mdefine_line|#define EICON_STATE_BHWAIT   8
DECL|macro|EICON_STATE_BHWAIT2
mdefine_line|#define EICON_STATE_BHWAIT2  9
DECL|macro|EICON_STATE_DHWAIT
mdefine_line|#define EICON_STATE_DHWAIT  10
DECL|macro|EICON_STATE_DHWAIT2
mdefine_line|#define EICON_STATE_DHWAIT2 11
DECL|macro|EICON_STATE_BSETUP
mdefine_line|#define EICON_STATE_BSETUP  12
DECL|macro|EICON_STATE_ACTIVE
mdefine_line|#define EICON_STATE_ACTIVE  13
DECL|macro|EICON_STATE_ICALLW
mdefine_line|#define EICON_STATE_ICALLW  14
DECL|macro|EICON_STATE_LISTEN
mdefine_line|#define EICON_STATE_LISTEN  15
DECL|macro|EICON_STATE_WMCONN
mdefine_line|#define EICON_STATE_WMCONN  16
DECL|macro|EICON_MAX_QUEUED
mdefine_line|#define EICON_MAX_QUEUED  8000 /* 2 * maxbuff */
DECL|macro|EICON_LOCK_TX
mdefine_line|#define EICON_LOCK_TX 0
DECL|macro|EICON_LOCK_RX
mdefine_line|#define EICON_LOCK_RX 1
r_typedef
r_struct
(brace
DECL|member|dummy
r_int
id|dummy
suffix:semicolon
DECL|typedef|eicon_mca_card
)brace
id|eicon_mca_card
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|isa
id|eicon_isa_card
id|isa
suffix:semicolon
DECL|member|pci
id|eicon_pci_card
id|pci
suffix:semicolon
DECL|member|mca
id|eicon_mca_card
id|mca
suffix:semicolon
DECL|typedef|eicon_hwif
)brace
id|eicon_hwif
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ret
id|__u8
id|ret
suffix:semicolon
DECL|member|id
id|__u8
id|id
suffix:semicolon
DECL|member|ch
id|__u8
id|ch
suffix:semicolon
DECL|typedef|eicon_ack
)brace
id|eicon_ack
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|code
id|__u8
id|code
suffix:semicolon
DECL|member|id
id|__u8
id|id
suffix:semicolon
DECL|member|ch
id|__u8
id|ch
suffix:semicolon
DECL|typedef|eicon_req
)brace
id|eicon_req
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ret
id|__u8
id|ret
suffix:semicolon
DECL|member|id
id|__u8
id|id
suffix:semicolon
DECL|member|ch
id|__u8
id|ch
suffix:semicolon
DECL|member|more
id|__u8
id|more
suffix:semicolon
DECL|typedef|eicon_indhdr
)brace
id|eicon_indhdr
suffix:semicolon
DECL|struct|msn_entry
r_typedef
r_struct
id|msn_entry
(brace
DECL|member|eaz
r_char
id|eaz
suffix:semicolon
DECL|member|msn
r_char
id|msn
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|next
r_struct
id|msn_entry
op_star
id|next
suffix:semicolon
DECL|typedef|msn_entry
)brace
id|msn_entry
suffix:semicolon
multiline_comment|/*&n; * Per card driver data&n; */
DECL|struct|eicon_card
r_typedef
r_struct
id|eicon_card
(brace
DECL|member|hwif
id|eicon_hwif
id|hwif
suffix:semicolon
multiline_comment|/* Hardware dependant interface     */
DECL|member|ptype
id|u_char
id|ptype
suffix:semicolon
multiline_comment|/* Protocol type (1TR6 or Euro)     */
DECL|member|bus
id|u_char
id|bus
suffix:semicolon
multiline_comment|/* Bustype (ISA, MCA, PCI)          */
DECL|member|type
id|u_char
id|type
suffix:semicolon
multiline_comment|/* Cardtype (EICON_CTYPE_...)       */
DECL|member|qnext
r_struct
id|eicon_card
op_star
id|qnext
suffix:semicolon
multiline_comment|/* Pointer to next quadro adapter   */
DECL|member|Feature
r_int
id|Feature
suffix:semicolon
multiline_comment|/* Protocol Feature Value           */
DECL|member|next
r_struct
id|eicon_card
op_star
id|next
suffix:semicolon
multiline_comment|/* Pointer to next device struct    */
DECL|member|myid
r_int
id|myid
suffix:semicolon
multiline_comment|/* Driver-Nr. assigned by linklevel */
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Statusflags                      */
DECL|member|ilock
r_int
r_int
id|ilock
suffix:semicolon
multiline_comment|/* Semaphores for IRQ-Routines      */
DECL|member|rcvq
r_struct
id|sk_buff_head
id|rcvq
suffix:semicolon
multiline_comment|/* Receive-Message queue            */
DECL|member|sndq
r_struct
id|sk_buff_head
id|sndq
suffix:semicolon
multiline_comment|/* Send-Message queue               */
DECL|member|rackq
r_struct
id|sk_buff_head
id|rackq
suffix:semicolon
multiline_comment|/* Req-Ack-Message queue            */
DECL|member|sackq
r_struct
id|sk_buff_head
id|sackq
suffix:semicolon
multiline_comment|/* Data-Ack-Message queue           */
DECL|member|ack_msg
id|u_char
op_star
id|ack_msg
suffix:semicolon
multiline_comment|/* Ptr to User Data in User skb     */
DECL|member|need_b3ack
id|__u16
id|need_b3ack
suffix:semicolon
multiline_comment|/* Flag: Need ACK for current skb   */
DECL|member|sbuf
r_struct
id|sk_buff
op_star
id|sbuf
suffix:semicolon
multiline_comment|/* skb which is currently sent      */
DECL|member|snd_tq
r_struct
id|tq_struct
id|snd_tq
suffix:semicolon
multiline_comment|/* Task struct for xmit bh          */
DECL|member|rcv_tq
r_struct
id|tq_struct
id|rcv_tq
suffix:semicolon
multiline_comment|/* Task struct for rcv bh           */
DECL|member|ack_tq
r_struct
id|tq_struct
id|ack_tq
suffix:semicolon
multiline_comment|/* Task struct for ack bh           */
DECL|member|msn_list
id|msn_entry
op_star
id|msn_list
suffix:semicolon
DECL|member|msgnum
r_int
r_int
id|msgnum
suffix:semicolon
multiline_comment|/* Message number for sending       */
DECL|member|IdTable
id|eicon_chan
op_star
id|IdTable
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* Table to find entity   */
DECL|member|ref_in
id|__u16
id|ref_in
suffix:semicolon
DECL|member|ref_out
id|__u16
id|ref_out
suffix:semicolon
DECL|member|nchannels
r_int
id|nchannels
suffix:semicolon
multiline_comment|/* Number of B-Channels             */
DECL|member|ReadyInt
r_int
id|ReadyInt
suffix:semicolon
multiline_comment|/* Ready Interrupt&t;&t;     */
DECL|member|bch
id|eicon_chan
op_star
id|bch
suffix:semicolon
multiline_comment|/* B-Channel status/control         */
DECL|member|status_buf
r_char
id|status_buf
(braket
l_int|256
)braket
suffix:semicolon
multiline_comment|/* Buffer for status messages       */
DECL|member|status_buf_read
r_char
op_star
id|status_buf_read
suffix:semicolon
DECL|member|status_buf_write
r_char
op_star
id|status_buf_write
suffix:semicolon
DECL|member|status_buf_end
r_char
op_star
id|status_buf_end
suffix:semicolon
DECL|member|interface
id|isdn_if
id|interface
suffix:semicolon
multiline_comment|/* Interface to upper layer         */
DECL|member|regname
r_char
id|regname
(braket
l_int|35
)braket
suffix:semicolon
multiline_comment|/* Name used for request_region     */
DECL|typedef|eicon_card
)brace
id|eicon_card
suffix:semicolon
multiline_comment|/* -----------------------------------------------------------**&n;** The PROTOCOL_FEATURE_STRING                                **&n;** defines capabilities and                                   **&n;** features of the actual protocol code. It&squot;s used as a bit   **&n;** mask.                                                      **&n;** The following Bits are defined:                            **&n;** -----------------------------------------------------------*/
DECL|macro|PROTCAP_TELINDUS
mdefine_line|#define PROTCAP_TELINDUS  0x0001  /* Telindus Variant of protocol code   */
DECL|macro|PROTCAP_MANIF
mdefine_line|#define PROTCAP_MANIF     0x0002  /* Management interface implemented    */
DECL|macro|PROTCAP_V_42
mdefine_line|#define PROTCAP_V_42      0x0004  /* V42 implemented                     */
DECL|macro|PROTCAP_V90D
mdefine_line|#define PROTCAP_V90D      0x0008  /* V.90D (implies up to 384k DSP code) */
DECL|macro|PROTCAP_EXTD_FAX
mdefine_line|#define PROTCAP_EXTD_FAX  0x0010  /* Extended FAX (ECM, 2D, T6, Polling) */
DECL|macro|PROTCAP_FREE4
mdefine_line|#define PROTCAP_FREE4     0x0020  /* not used                            */
DECL|macro|PROTCAP_FREE5
mdefine_line|#define PROTCAP_FREE5     0x0040  /* not used                            */
DECL|macro|PROTCAP_FREE6
mdefine_line|#define PROTCAP_FREE6     0x0080  /* not used                            */
DECL|macro|PROTCAP_FREE7
mdefine_line|#define PROTCAP_FREE7     0x0100  /* not used                            */
DECL|macro|PROTCAP_FREE8
mdefine_line|#define PROTCAP_FREE8     0x0200  /* not used                            */
DECL|macro|PROTCAP_FREE9
mdefine_line|#define PROTCAP_FREE9     0x0400  /* not used                            */
DECL|macro|PROTCAP_FREE10
mdefine_line|#define PROTCAP_FREE10    0x0800  /* not used                            */
DECL|macro|PROTCAP_FREE11
mdefine_line|#define PROTCAP_FREE11    0x1000  /* not used                            */
DECL|macro|PROTCAP_FREE12
mdefine_line|#define PROTCAP_FREE12    0x2000  /* not used                            */
DECL|macro|PROTCAP_FREE13
mdefine_line|#define PROTCAP_FREE13    0x4000  /* not used                            */
DECL|macro|PROTCAP_EXTENSION
mdefine_line|#define PROTCAP_EXTENSION 0x8000  /* used for future extentions          */
macro_line|#include &quot;eicon_idi.h&quot;
r_extern
id|eicon_card
op_star
id|cards
suffix:semicolon
r_extern
r_char
op_star
id|eicon_ctype_name
(braket
)braket
suffix:semicolon
DECL|function|eicon_schedule_tx
r_extern
id|__inline__
r_void
id|eicon_schedule_tx
c_func
(paren
id|eicon_card
op_star
id|card
)paren
(brace
id|queue_task
c_func
(paren
op_amp
id|card-&gt;snd_tq
comma
op_amp
id|tq_immediate
)paren
suffix:semicolon
id|mark_bh
c_func
(paren
id|IMMEDIATE_BH
)paren
suffix:semicolon
)brace
DECL|function|eicon_schedule_rx
r_extern
id|__inline__
r_void
id|eicon_schedule_rx
c_func
(paren
id|eicon_card
op_star
id|card
)paren
(brace
id|queue_task
c_func
(paren
op_amp
id|card-&gt;rcv_tq
comma
op_amp
id|tq_immediate
)paren
suffix:semicolon
id|mark_bh
c_func
(paren
id|IMMEDIATE_BH
)paren
suffix:semicolon
)brace
DECL|function|eicon_schedule_ack
r_extern
id|__inline__
r_void
id|eicon_schedule_ack
c_func
(paren
id|eicon_card
op_star
id|card
)paren
(brace
id|queue_task
c_func
(paren
op_amp
id|card-&gt;ack_tq
comma
op_amp
id|tq_immediate
)paren
suffix:semicolon
id|mark_bh
c_func
(paren
id|IMMEDIATE_BH
)paren
suffix:semicolon
)brace
r_extern
r_char
op_star
id|eicon_find_eaz
c_func
(paren
id|eicon_card
op_star
comma
r_char
)paren
suffix:semicolon
r_extern
r_int
id|eicon_addcard
c_func
(paren
r_int
comma
r_int
comma
r_int
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_void
id|eicon_io_transmit
c_func
(paren
id|eicon_card
op_star
id|card
)paren
suffix:semicolon
r_extern
r_void
id|eicon_irq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|eicon_io_rcv_dispatch
c_func
(paren
id|eicon_card
op_star
id|ccard
)paren
suffix:semicolon
r_extern
r_void
id|eicon_io_ack_dispatch
c_func
(paren
id|eicon_card
op_star
id|ccard
)paren
suffix:semicolon
r_extern
id|ulong
id|DebugVar
suffix:semicolon
macro_line|#endif  /* __KERNEL__ */
macro_line|#endif&t;/* eicon_h */
eof
