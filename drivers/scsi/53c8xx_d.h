DECL|variable|SCRIPT
r_int
r_int
id|SCRIPT
(braket
)braket
op_assign
(brace
multiline_comment|/*&n;; NCR 53c810 driver, main script&n;; Sponsored by &n;;&t;iX Multiuser Multitasking Magazine&n;;&t;hm@ix.de&n;;&n;; Copyright 1993, Drew Eckhardt&n;;      Visionary Computing &n;;      (Unix and Linux consulting and custom programming)&n;;      drew@Colorado.EDU&n;;      +1 (303) 786-7975&n;;&n;; TolerANT and SCSI SCRIPTS are registered trademarks of NCR Corporation.&n;;&n;; PRE-ALPHA&n;;&n;; For more information, please consult &n;;&n;; NCR 53C810&n;; PCI-SCSI I/O Processor&n;; Data Manual&n;;&n;; NCR 53C710 &n;; SCSI I/O Processor&n;; Programmers Guide&n;;&n;; NCR Microelectronics&n;; 1635 Aeroplaza Drive&n;; Colorado Springs, CO 80916&n;; 1+ (719) 578-3400&n;;&n;; Toll free literature number&n;; +1 (800) 334-5454&n;;&n;; IMPORTANT : This code is self modifying due to the limitations of &n;;&t;the NCR53c7,8xx series chips.  Persons debugging this code with&n;;&t;the remote debugger should take this into account, and NOT set&n;;&t;breakpoints in modified instructions.&n;;&n;;&n;; Design:&n;; The NCR53c7x0 family of SCSI chips are busmasters with an onboard &n;; microcontroller using a simple instruction set.   &n;;&n;; So, to minimize the effects of interrupt latency, and to maximize &n;; throughput, this driver offloads the practical maximum amount &n;; of processing to the SCSI chip while still maintaining a common&n;; structure.&n;;&n;; Where tradeoffs were needed between efficiency on the older&n;; chips and the newer NCR53c800 series, the NCR53c800 series &n;; was chosen.&n;;&n;; While the NCR53c700 and NCR53c700-66 lacked the facilities to fully&n;; automate SCSI transfers without host processor intervention, this &n;; isnt the case with the NCR53c710 and newer chips which allow &n;;&n;; - reads and writes to the internal registers from within the SCSI&n;; &t;scripts, allowing the SCSI SCRIPTS(tm) code to save processor&n;; &t;state so that multiple threads of execution are possible, and also&n;; &t;provide an ALU for loop control, etc.&n;; &n;; - table indirect addressing for some instructions. This allows &n;;&t;pointers to be located relative to the DSA ((Data Structure&n;;&t;Address) register.&n;;&n;; These features make it possible to implement a mailbox style interface,&n;; where the same piece of code is run to handle I/O for multiple threads&n;; at once minimizing our need to relocate code.  Since the NCR53c700/&n;; NCR53c800 series have a unique combination of features, making a &n;; a standard ingoing/outgoing mailbox system, costly, Ive modified it.&n;;&n;; - Commands are stored in a linked list, rather than placed in &n;; &t;arbitrary mailboxes.  This simiplifies the amount of processing&n;;&t;that must be done by the NCR53c810.&n;;&n;; - Mailboxes are a mixture of code and data.  This lets us greatly&n;; &t;simplify the NCR53c810 code and do things that would otherwise&n;;&t;not be possible.&n;&n;;&n;; Note : the DSA structures must be aligned on 32 bit boundaries,&n;; since the source and destination of MOVE MEMORY instructions &n;; must share the same alignment and this is the alignment of the&n;; NCR registers.&n;;&n;&n;ABSOLUTE dsa_temp_jump_resume = 0&t;; Patch to dsa_jump_resume&n;    &t;    &t;    &t;    &t;    &t;; &t;in current dsa&n;ABSOLUTE dsa_temp_lun = 0&t;&t;; Patch to lun for current dsa&n;ABSOLUTE dsa_temp_dsa_next = 0&t;&t;; Patch to dsa next for current dsa&n;ABSOLUTE dsa_temp_sync = 0&t;&t;; Patch to address of per-target&n;&t;&t;&t;&t;&t;;&t;sync routine&n;ABSOLUTE dsa_temp_target = 0&t;&t;; Patch to id for current dsa&n;&n;&n;&n;ENTRY dsa_code_template&n;dsa_code_template:&n;&n;; Define DSA structure used for mailboxes&n;&n;; wrong_dsa loads the DSA register with the value of the dsa_next&n;; field.&n;;&n;wrong_dsa:&n;;&t;&t;Patch the MOVE MEMORY INSTRUCTION such that &n;;&t;&t;the destination address is that of the OLD next&n;;&t;&t;pointer.&n;&t;MOVE MEMORY 4, dsa_temp_dsa_next, reselected_ok + 8&n;&n;at 0x00000000 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000660
comma
multiline_comment|/*&n;&n;&t;MOVE dmode_memory_to_ncr TO DMODE&t;&n;&n;at 0x00000003 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE MEMORY 4, dsa_temp_dsa_next, addr_scratch&n;&n;at 0x00000005 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x00000008 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;CALL scratch_to_dsa&n;&n;at 0x0000000a : */
l_int|0x88080000
comma
l_int|0x00000800
comma
multiline_comment|/*&n;&t;JUMP reselected_check_next&n;&n;at 0x0000000c : */
l_int|0x80080000
comma
l_int|0x000005ac
comma
multiline_comment|/*&n;&n;ABSOLUTE dsa_check_reselect = 0&n;; dsa_check_reselect determines weather or not the current target and&n;; lun match the current DSA&n;ENTRY dsa_code_check_reselect&n;dsa_code_check_reselect:&n;&t;MOVE SSID TO SFBR&t;&t;; SSID contains 3 bit target ID&n;&n;at 0x0000000e : */
l_int|0x720a0000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;JUMP REL (wrong_dsa), IF NOT dsa_temp_target, AND MASK 7&n;&n;at 0x00000010 : */
l_int|0x80840700
comma
l_int|0x00ffffb8
comma
multiline_comment|/*&n;&t;MOVE dmode_memory_to_ncr TO DMODE&n;&n;at 0x00000012 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE MEMORY 1, reselected_identify, addr_sfbr&n;&n;at 0x00000014 : */
l_int|0xc0000001
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;JUMP REL (wrong_dsa), IF NOT dsa_temp_lun, AND MASK 7&n;&n;at 0x00000017 : */
l_int|0x80840700
comma
l_int|0x00ffff9c
comma
multiline_comment|/*&n;&t;MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x00000019 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;;&t;&t;Patch the MOVE MEMORY INSTRUCTION such that&n;;&t;&t;the source address is that of this dsas&n;;&t;&t;next pointer.&n;&t;MOVE MEMORY 4, dsa_temp_dsa_next, reselected_ok + 4&n;&n;at 0x0000001b : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x0000065c
comma
multiline_comment|/*&n;&t;CALL reselected_ok&n;&n;at 0x0000001e : */
l_int|0x88080000
comma
l_int|0x00000658
comma
multiline_comment|/*&n;&t;CALL dsa_temp_sync&t;&n;&n;at 0x00000020 : */
l_int|0x88080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;ENTRY dsa_jump_resume&n;dsa_jump_resume:&n;&t;JUMP 0&t;&t;&t;&t;; Jump to resume address&n;&n;at 0x00000022 : */
l_int|0x80080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;ENTRY dsa_zero&n;dsa_zero:&n;&t;MOVE dmode_ncr_to_memory TO DMODE&t;&t;&t;; 8&n;&n;at 0x00000024 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE MEMORY 4, addr_temp, dsa_temp_jump_resume&t;&t;; 16&t;&n;&n;at 0x00000026 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;MOVE dmode_memory_to_memory TO DMODE&t;&t;&t;; 28&n;&n;at 0x00000029 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;JUMP dsa_schedule&t;&t;&t;&t;&t;; 36&n;&n;at 0x0000002b : */
l_int|0x80080000
comma
l_int|0x000000b4
comma
multiline_comment|/*&n;ENTRY dsa_code_template_end&n;dsa_code_template_end:&n;&n;; Perform sanity check for dsa_fields_start == dsa_code_template_end - &n;; dsa_zero, puke.&n;&n;ABSOLUTE dsa_fields_start =  36&t;; Sanity marker&n;&t;&t;&t;&t;; &t;pad 12&n;ABSOLUTE dsa_next = 48&t;&t;; len 4 Next DSA&n; &t;&t;&t;&t;; del 4 Previous DSA address&n;ABSOLUTE dsa_cmnd = 56&t;&t;; len 4 Scsi_Cmnd * for this thread.&n;ABSOLUTE dsa_select = 60&t;; len 4 Device ID, Period, Offset for &n;&t;&t;&t; &t;;&t;table indirect select&n;ABSOLUTE dsa_msgout = 64&t;; len 8 table indirect move parameter for &n;&t;&t;&t;&t;;       select message&n;ABSOLUTE dsa_cmdout = 72&t;; len 8 table indirect move parameter for &n;&t;&t;&t;&t;;&t;command&n;ABSOLUTE dsa_dataout = 80&t;; len 4 code pointer for dataout&n;ABSOLUTE dsa_datain = 84&t;; len 4 code pointer for datain&n;ABSOLUTE dsa_msgin = 88&t;&t;; len 8 table indirect move for msgin&n;ABSOLUTE dsa_status = 96 &t;; len 8 table indirect move for status byte&n;ABSOLUTE dsa_msgout_other = 104&t;; len 8 table indirect for normal message out&n;&t;&t;&t;&t;; (Synchronous transfer negotiation, etc).&n;ABSOLUTE dsa_end = 112&n;&n;; Linked lists of DSA structures&n;ABSOLUTE issue_dsa_head = 0&t;; Linked list of DSAs to issue&n;ABSOLUTE reconnect_dsa_head = 0&t;; Link list of DSAs which can reconnect&n;&n;; These select the source and destination of a MOVE MEMORY instruction&n;ABSOLUTE dmode_memory_to_memory = 0x0&n;ABSOLUTE dmode_memory_to_ncr = 0x0&n;ABSOLUTE dmode_ncr_to_memory = 0x0&n;ABSOLUTE dmode_ncr_to_ncr = 0x0&n;&n;ABSOLUTE addr_scratch = 0x0&n;ABSOLUTE addr_sfbr = 0x0&n;ABSOLUTE addr_temp = 0x0&n;&n;&n;; Interrupts - &n;; MSB indicates type&n;; 0&t;handle error condition&n;; 1 &t;handle message &n;; 2 &t;handle normal condition&n;; 3&t;debugging interrupt&n;; 4 &t;testing interrupt &n;; Next byte indicates specific error&n;&n;; XXX not yet implemented, Im not sure if I want to - &n;; Next byte indicates the routine the error occurred in&n;; The LSB indicates the specific place the error occurred&n; &n;ABSOLUTE int_err_unexpected_phase = 0x00000000&t;; Unexpected phase encountered&n;ABSOLUTE int_err_selected = 0x00010000&t;&t;; SELECTED (nee RESELECTED)&n;ABSOLUTE int_err_unexpected_reselect = 0x00020000 &n;ABSOLUTE int_err_check_condition = 0x00030000&t;&n;ABSOLUTE int_err_no_phase = 0x00040000&n;ABSOLUTE int_msg_wdtr = 0x01000000&t;&t;; WDTR message received&n;ABSOLUTE int_msg_sdtr = 0x01010000&t;&t;; SDTR received&n;ABSOLUTE int_msg_1 = 0x01020000&t;&t;&t;; single byte special message&n;&t;&t;&t;&t;&t;&t;; received&n;&n;ABSOLUTE int_norm_select_complete = 0x02000000&t;; Select complete, reprogram&n;&t;&t;&t;&t;&t;&t;; registers.&n;ABSOLUTE int_norm_reselect_complete = 0x02010000&t;; Nexus established&n;ABSOLUTE int_norm_command_complete = 0x02020000 ; Command complete&n;ABSOLUTE int_norm_disconnected = 0x02030000&t;; Disconnected &n;ABSOLUTE int_norm_aborted =0x02040000&t;&t;; Aborted *dsa&n;ABSOLUTE int_norm_reset = 0x02050000&t;&t;; Generated BUS reset.&n;ABSOLUTE int_debug_break = 0x03000000&t;&t;; Break point&n;ABSOLUTE int_debug_scheduled = 0x03010000&t;; new I/O scheduled &n;ABSOLUTE int_debug_idle = 0x03020000&t;&t;; scheduler is idle&n;ABSOLUTE int_debug_dsa_loaded = 0x03030000&t;; dsa reloaded&n;ABSOLUTE int_debug_reselected = 0x03040000&t;; NCR reselected&n;ABSOLUTE int_debug_head = 0x03050000&t;&t;; issue head overwritten&n;&n;ABSOLUTE int_test_1 = 0x04000000&t;&t;; Test 1 complete&n;ABSOLUTE int_test_2 = 0x04010000&t;&t;; Test 2 complete&n;ABSOLUTE int_test_3 = 0x04020000&t;&t;; Test 3 complete&n;&t;&t;&t;&t;&t;&t;&n;EXTERNAL NCR53c7xx_msg_abort &t;&t;; Pointer to abort message&n;EXTERNAL NCR53c7xx_msg_reject &t;&t;; Pointer to reject message&n;EXTERNAL NCR53c7xx_zero&t;&t;&t;; long with zero in it, use for source&n;EXTERNAL NCR53c7xx_sink&t;&t;&t;; long to dump worthless data in&n;&n;; Pointer to final bytes of multi-byte messages&n;ABSOLUTE msg_buf = 0&n;&n;; Pointer to holding area for reselection information&n;ABSOLUTE reselected_identify = 0&n;ABSOLUTE reselected_tag = 0&n;&n;; Request sense command pointer, its a 6 byte command, should&n;; be constant for all commands since we allways want 16 bytes of &n;; sense and we dont need to change any fields as we did under &n;; SCSI-I when we actually cared about the LUN field.&n;;EXTERNAL NCR53c7xx_sense&t;&t;; Request sense command&n;&n;&n;; dsa_schedule  &n;; PURPOSE : after a DISCONNECT message has been recieved, and pointers&n;;&t;saved, insert the current DSA structure at the head of the &n;; &t;disconnected queue and fall through to the scheduler.&n;;&n;; CALLS : OK&n;;&n;; INPUTS : dsa - current DSA structure, reconnect_dsa_head - list&n;;&t;of disconnected commands&n;;&n;; MODIFIES : SCRATCH, reconnect_dsa_head&n;; &n;; EXITS : allways passes control to schedule&n;&n;ENTRY dsa_schedule&n;dsa_schedule:&n;&n;;&n;; Calculate the address of the next pointer within the DSA &n;; structure of the command that is currently disconnecting&n;;&n;    CALL dsa_to_scratch&n;&n;at 0x0000002d : */
l_int|0x88080000
comma
l_int|0x000007b8
comma
multiline_comment|/*&n;; XXX - we need to deal with the NCR53c710, which lacks an add with&n;;&t;carry instruction, by moving arround the DSA alignment to avoid&n;; &t;carry in situations like this.&n;    MOVE SCRATCH0 + dsa_next TO SCRATCH0&n;&n;at 0x0000002f : */
l_int|0x7e343000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH1 + 0 TO SCRATCH1 WITH CARRY&n;&n;at 0x00000031 : */
l_int|0x7f350000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH2 + 0 TO SCRATCH2 WITH CARRY&n;&n;at 0x00000033 : */
l_int|0x7f360000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH3 + 0 TO SCRATCH3 WITH CARRY&n;&n;at 0x00000035 : */
l_int|0x7f370000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;; Point the next field of this DSA structure at the current disconnected &n;; list&n;    MOVE dmode_ncr_to_memory TO DMODE&n;&n;at 0x00000037 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE MEMORY 4, addr_scratch, dsa_schedule_insert + 8&n;&n;at 0x00000039 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000100
comma
multiline_comment|/*&n;    MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x0000003c : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;dsa_schedule_insert:&n;    MOVE MEMORY 4, reconnect_dsa_head, 0 &n;&n;at 0x0000003e : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;; And update the head pointer.&n;    CALL dsa_to_scratch&n;&n;at 0x00000041 : */
l_int|0x88080000
comma
l_int|0x000007b8
comma
multiline_comment|/*&n;    MOVE dmode_ncr_to_memory TO DMODE&t;&n;&n;at 0x00000043 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE MEMORY 4, addr_scratch, reconnect_dsa_head&n;&n;at 0x00000045 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x00000048 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    WAIT DISCONNECT&n;&n;at 0x0000004a : */
l_int|0x48000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;; schedule&n;; PURPOSE : schedule a new I/O once the bus is free by putting the &n;;&t;address of the next DSA structure in the DSA register.&n;;&n;; INPUTS : issue_dsa_head - list of new commands&n;;&n;; CALLS : OK&n;;&n;; MODIFIES : SCRATCH, DSA &n;;&n;; EXITS : if the issue_dsa_head pointer is non-NULL, control&n;;&t;is passed to select.  Otherwise, control is passed to &n;;&t;wait_reselect.&n;&n;&n;ENTRY schedule&n;schedule:&n;    ; Point DSA at the current head of the issue queue.&n;    MOVE dmode_memory_to_ncr TO DMODE&n;&n;at 0x0000004c : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE MEMORY 4, issue_dsa_head, addr_scratch&n;&n;at 0x0000004e : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x00000051 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;    CALL scratch_to_dsa&n;&n;at 0x00000053 : */
l_int|0x88080000
comma
l_int|0x00000800
comma
multiline_comment|/*&n;&n;&n;&n;&n;    ; Check for a null pointer.&n;    MOVE DSA0 TO SFBR&n;&n;at 0x00000055 : */
l_int|0x72100000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP select, IF NOT 0&n;&n;at 0x00000057 : */
l_int|0x80040000
comma
l_int|0x00000194
comma
multiline_comment|/*&n;    MOVE DSA1 TO SFBR&n;&n;at 0x00000059 : */
l_int|0x72110000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP select, IF NOT 0&n;&n;at 0x0000005b : */
l_int|0x80040000
comma
l_int|0x00000194
comma
multiline_comment|/*&n;    MOVE DSA2 TO SFBR&n;&n;at 0x0000005d : */
l_int|0x72120000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP select, IF NOT 0&n;&n;at 0x0000005f : */
l_int|0x80040000
comma
l_int|0x00000194
comma
multiline_comment|/*&n;    MOVE DSA3 TO SFBR&n;&n;at 0x00000061 : */
l_int|0x72130000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP wait_reselect, IF 0&n;&n;at 0x00000063 : */
l_int|0x800c0000
comma
l_int|0x00000560
comma
multiline_comment|/*&n;&n;    &n;&n;&n;&n;;&n;; select&n;;&n;; PURPOSE : establish a nexus for the SCSI command referenced by DSA.&n;;&t;On success, the current DSA structure is removed from the issue &n;;&t;queue.  Usually, this is entered as a fall-through from schedule,&n;;&t;although the contingent allegience handling code will write&n;;&t;the select entry address to the DSP to restart a command as a &n;;&t;REQUEST SENSE.  A message is sent (usually IDENTIFY, although&n;;&t;additional SDTR or WDTR messages may be sent).  COMMAND OUT&n;;&t;is handled.&n;;&n;; INPUTS : DSA - SCSI command, issue_dsa_head&n;;&n;; CALLS : OK&n;;&n;; MODIFIES : SCRATCH, issue_dsa_head&n;;&n;; EXITS : on reselection or selection, go to select_failed&n;;&t;otherwise, fall through to data_transfer.  If a MSG_IN&n;;&t;phase occurs before &n;;&n;&n;ENTRY select&n;select:&n;&n;&n;&n;&n;    CLEAR TARGET&n;&n;at 0x00000065 : */
l_int|0x60000200
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;; XXX&n;;&n;; In effect, SELECTION operations are backgrounded, with execution&n;; continuing until code which waits for REQ or a fatal interrupt is &n;; encountered.&n;;&n;; So, for more performance, we could overlap the code which removes &n;; the command from the NCRs issue queue with the selection, but &n;; at this point I dont want to deal with the error recovery.&n;;&n;&n;&n;    SELECT ATN FROM dsa_select, select_failed&n;&n;at 0x00000067 : */
l_int|0x4300003c
comma
l_int|0x00000694
comma
multiline_comment|/*&n;    JUMP select_msgout, WHEN MSG_OUT&n;&n;at 0x00000069 : */
l_int|0x860b0000
comma
l_int|0x000001ac
comma
multiline_comment|/*&n;ENTRY select_msgout&n;select_msgout:&n;    MOVE FROM dsa_msgout, WHEN MSG_OUT&n;&n;at 0x0000006b : */
l_int|0x1e000000
comma
l_int|0x00000040
comma
multiline_comment|/*&n;&n;&n;&n;&n;&n;&n;&n;&n;&n;    ; Calculate address of dsa_next field&n;&n;    CALL dsa_to_scratch&n;&n;at 0x0000006d : */
l_int|0x88080000
comma
l_int|0x000007b8
comma
multiline_comment|/*&n;&n;    MOVE SCRATCH0 + dsa_next TO SCRATCH0&n;&n;at 0x0000006f : */
l_int|0x7e343000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH1 + 0 TO SCRATCH1 WITH CARRY&n;&n;at 0x00000071 : */
l_int|0x7f350000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH2 + 0 TO SCRATCH2 WITH CARRY&n;&n;at 0x00000073 : */
l_int|0x7f360000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH3 + 0 TO SCRATCH3 WITH CARRY&n;&n;at 0x00000075 : */
l_int|0x7f370000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;    ; Patch memory to memory move&n;    move dmode_ncr_to_memory TO DMODE&n;&n;at 0x00000077 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE MEMORY 4, addr_scratch, issue_remove + 4&n;&n;at 0x00000079 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x000001fc
comma
multiline_comment|/*&n;&n;&n;    ; And rewrite the issue_dsa_head pointer.&n;    MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x0000007c : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;issue_remove:&n;;&t;The actual UPDATE of the issue_dsa_head variable is &n;; &t;atomic, with all of the setup code being irrelevant to&n;;&t;weather the updated value being the old or new contents of &n;;&t;dsa_next field.&n;;&n;; &t;To insure synchronization, the host system merely needs to &n;;&t;do a XCHG instruction with interrupts disabled on the &n;;&t;issue_dsa_head memory address.&n;;&n;;&t;The net effect will be that the XCHG instruction will return&n;;&t;either a non-NULL value, indicating that the NCR chip will not&n;;&t;go into the idle loop when this command DISCONNECTS, or a NULL&n;;&t;value indicating that the NCR wrote first and that the Linux&n;;&t;code must rewrite the issue_dsa_head pointer and set SIG_P.&n;;&t;&n;&n;&n;    MOVE MEMORY 4, 0, issue_dsa_head&n;&n;at 0x0000007e : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;&n;&n;&n;&n;; After a successful selection, we should get either a CMD phase or &n;; some transfer request negotiation message.&n;&n;    JUMP cmdout, WHEN CMD&n;&n;at 0x00000081 : */
l_int|0x820b0000
comma
l_int|0x00000224
comma
multiline_comment|/*&n;    INT int_err_unexpected_phase, WHEN NOT MSG_IN &n;&n;at 0x00000083 : */
l_int|0x9f030000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;select_msg_in:&n;    CALL msg_in, WHEN MSG_IN&n;&n;at 0x00000085 : */
l_int|0x8f0b0000
comma
l_int|0x00000354
comma
multiline_comment|/*&n;    JUMP select_msg_in, WHEN MSG_IN&n;&n;at 0x00000087 : */
l_int|0x870b0000
comma
l_int|0x00000214
comma
multiline_comment|/*&n;&n;cmdout:&n;    INT int_err_unexpected_phase, WHEN NOT CMD&n;&n;at 0x00000089 : */
l_int|0x9a030000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;&n;&n;ENTRY cmdout_cmdout&n;cmdout_cmdout:&n;&n;    MOVE FROM dsa_cmdout, WHEN CMD&n;&n;at 0x0000008b : */
l_int|0x1a000000
comma
l_int|0x00000048
comma
multiline_comment|/*&n;&n;&n;&n;&n;;&n;; data_transfer  &n;; other_transfer&n;;&n;; PURPOSE : handle the main data transfer for a SCSI command in &n;;&t;two parts.  In the first part, data_transfer, DATA_IN&n;;&t;and DATA_OUT phases are allowed, with the user provided&n;;&t;code (usually dynamically generated based on the scatter/gather&n;;&t;list associated with a SCSI command) called to handle these &n;;&t;phases.&n;;&n;;&t;On completion, the user code passes control to other_transfer&n;;&t;which causes DATA_IN and DATA_OUT to result in unexpected_phase&n;;&t;interrupts so that data overruns may be trapped.&n;;&n;; INPUTS : DSA - SCSI command&n;;&n;; CALLS : OK&n;;&n;; MODIFIES : SCRATCH&n;;&n;; EXITS : if STATUS IN is detected, signifying command completion,&n;;&t;the NCR jumpst to command_complete.  If MSG IN occurs, a &n;;&t;CALL is made to msg_in.  Otherwise, other_transfer runs in &n;;&t;an infinite loop.&n;;&t;&n;&n;data_transfer:&n;    INT int_err_unexpected_phase, WHEN CMD&n;&n;at 0x0000008d : */
l_int|0x9a0b0000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    CALL msg_in, WHEN MSG_IN&n;&n;at 0x0000008f : */
l_int|0x8f0b0000
comma
l_int|0x00000354
comma
multiline_comment|/*&n;    INT int_err_unexpected_phase, WHEN MSG_OUT&n;&n;at 0x00000091 : */
l_int|0x9e0b0000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP do_dataout, WHEN DATA_OUT&n;&n;at 0x00000093 : */
l_int|0x800b0000
comma
l_int|0x0000026c
comma
multiline_comment|/*&n;    JUMP do_datain, WHEN DATA_IN&n;&n;at 0x00000095 : */
l_int|0x810b0000
comma
l_int|0x000002c4
comma
multiline_comment|/*&n;    JUMP command_complete, WHEN STATUS&n;&n;at 0x00000097 : */
l_int|0x830b0000
comma
l_int|0x00000508
comma
multiline_comment|/*&n;    JUMP data_transfer&n;&n;at 0x00000099 : */
l_int|0x80080000
comma
l_int|0x00000234
comma
multiline_comment|/*&n;&n;;&n;; On NCR53c700 and NCR53c700-66 chips, do_dataout/do_datain are fixed up &n;; whenever the nexus changes so it can point to the correct routine for &n;; that command.&n;;&n;&n;&n;; Nasty jump to dsa-&gt;dataout&n;do_dataout:&n;    CALL dsa_to_scratch&n;&n;at 0x0000009b : */
l_int|0x88080000
comma
l_int|0x000007b8
comma
multiline_comment|/*&n;    MOVE SCRATCH0 + dsa_dataout TO SCRATCH0&t;&n;&n;at 0x0000009d : */
l_int|0x7e345000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH1 + 0 TO SCRATCH1 WITH CARRY &n;&n;at 0x0000009f : */
l_int|0x7f350000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH2 + 0 TO SCRATCH2 WITH CARRY &n;&n;at 0x000000a1 : */
l_int|0x7f360000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH3 + 0 TO SCRATCH3 WITH CARRY &n;&n;at 0x000000a3 : */
l_int|0x7f370000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE dmode_ncr_to_memory TO DMODE&n;&n;at 0x000000a5 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE MEMORY 4, addr_scratch, dataout_to_jump + 4&n;&n;at 0x000000a7 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x000002b4
comma
multiline_comment|/*&n;    MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x000000aa : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;dataout_to_jump:&n;    MOVE MEMORY 4, 0, dataout_jump + 4 &n;&n;at 0x000000ac : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x000002c0
comma
multiline_comment|/*&n;dataout_jump:&n;    JUMP 0&n;&n;at 0x000000af : */
l_int|0x80080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;; Nasty jump to dsa-&gt;dsain&n;do_datain:&n;    CALL dsa_to_scratch&n;&n;at 0x000000b1 : */
l_int|0x88080000
comma
l_int|0x000007b8
comma
multiline_comment|/*&n;    MOVE SCRATCH0 + dsa_datain TO SCRATCH0&t;&n;&n;at 0x000000b3 : */
l_int|0x7e345400
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH1 + 0 TO SCRATCH1 WITH CARRY &n;&n;at 0x000000b5 : */
l_int|0x7f350000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH2 + 0 TO SCRATCH2 WITH CARRY &n;&n;at 0x000000b7 : */
l_int|0x7f360000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH3 + 0 TO SCRATCH3 WITH CARRY &n;&n;at 0x000000b9 : */
l_int|0x7f370000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE dmode_ncr_to_memory TO DMODE&n;&n;at 0x000000bb : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE MEMORY 4, addr_scratch, datain_to_jump + 4&n;&n;at 0x000000bd : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x0000030c
comma
multiline_comment|/*&n;    MOVE dmode_memory_to_memory TO DMODE&t;&t;&n;&n;at 0x000000c0 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;datain_to_jump:&n;    MOVE MEMORY 4, 0, datain_jump + 4&n;&n;at 0x000000c2 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000318
comma
multiline_comment|/*&n;datain_jump:&n;    JUMP 0&n;&n;at 0x000000c5 : */
l_int|0x80080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;&n;;&n;; other_transfer is exported because it is referenced by dynamically &n;; generated code.&n;;&n;ENTRY other_transfer&n;other_transfer:&n;&n;&n;&n;    INT int_err_unexpected_phase, WHEN CMD&n;&n;at 0x000000c7 : */
l_int|0x9a0b0000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    CALL msg_in, WHEN MSG_IN &n;&n;at 0x000000c9 : */
l_int|0x8f0b0000
comma
l_int|0x00000354
comma
multiline_comment|/*&n;    INT int_err_unexpected_phase, WHEN MSG_OUT&n;&n;at 0x000000cb : */
l_int|0x9e0b0000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    INT int_err_unexpected_phase, WHEN DATA_OUT&n;&n;at 0x000000cd : */
l_int|0x980b0000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    INT int_err_unexpected_phase, WHEN DATA_IN&n;&n;at 0x000000cf : */
l_int|0x990b0000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP command_complete, WHEN STATUS&n;&n;at 0x000000d1 : */
l_int|0x830b0000
comma
l_int|0x00000508
comma
multiline_comment|/*&n;    JUMP other_transfer&n;&n;at 0x000000d3 : */
l_int|0x80080000
comma
l_int|0x0000031c
comma
multiline_comment|/*&n;&n;;&n;; msg_in&n;; munge_msg&n;;&n;; PURPOSE : process messages from a target.  msg_in is called when the &n;;&t;caller hasnt read the first byte of the message.  munge_message&n;;&t;is called when the caller has read the first byte of the message,&n;;&t;and left it in SFBR.&n;;&n;;&t;Various int_* interrupts are generated when the host system&n;;&t;needs to intervene, as is the case with SDTR, WDTR, and&n;;&t;INITIATE RECOVERY messages.&n;;&n;;&t;When the host system handles one of these interrupts,&n;;&t;it can respond by rentering at reject_message, &n;;&t;which rejects the message and returns control to&n;;&t;the caller of msg_in or munge_msg, accept_message&n;;&t;which clears ACK and returns control, or reply_message&n;;&t;which sends the message pointed to by the DSA &n;;&t;msgout_other table indirect field.&n;;&n;;&t;DISCONNECT messages are handled by moving the command&n;;&t;to the reconnect_dsa_queue.&n;;&n;;&t;SAVE DATA POINTER and RESTORE DATA POINTERS are currently &n;;&t;treated as NOPS. &n;;&n;; INPUTS : DSA - SCSI COMMAND, SFBR - first byte of message (munge_msg&n;;&t;only)&n;;&n;; CALLS : NO.  The TEMP register isnt backed up to allow nested calls.&n;;&n;; MODIFIES : SCRATCH, DSA on DISCONNECT&n;;&n;; EXITS : On receipt of SAVE DATA POINTER, RESTORE POINTERS,&n;;&t;and normal return from message handlers running under&n;;&t;Linux, control is returned to the caller.  Receipt&n;;&t;of DISCONNECT messages pass control to dsa_schedule.&n;;&n;ENTRY msg_in&n;msg_in:&n;    MOVE 1, msg_buf, WHEN MSG_IN&n;&n;at 0x000000d5 : */
l_int|0x0f000001
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;munge_msg:&n;    JUMP munge_extended, IF 0x01&t;&t;; EXTENDED MESSAGE&n;&n;at 0x000000d7 : */
l_int|0x800c0001
comma
l_int|0x00000428
comma
multiline_comment|/*&n;    JUMP munge_2, IF 0x20, AND MASK 0xdf&t;; two byte message&n;&n;at 0x000000d9 : */
l_int|0x800cdf20
comma
l_int|0x0000039c
comma
multiline_comment|/*&n;;&n;; Ive seen a handful of broken SCSI devices which fail to issue&n;; a SAVE POINTERS message before disconnecting in the middle of &n;; a transfer, assuming that the DATA POINTER will be implicitly &n;; restored.  So, we treat the SAVE DATA POINTER message as a NOP.&n;;&n;; Ive also seen SCSI devices which dont issue a RESTORE DATA&n;; POINTER message and assume that thats implicit.&n;;&n;    JUMP accept_message, IF 0x02&t;&t;; SAVE DATA POINTER&n;&n;at 0x000000db : */
l_int|0x800c0002
comma
l_int|0x000004d8
comma
multiline_comment|/*&n;    JUMP accept_message, IF 0x03&t;&t;; RESTORE POINTERS &n;&n;at 0x000000dd : */
l_int|0x800c0003
comma
l_int|0x000004d8
comma
multiline_comment|/*&n;    JUMP munge_disconnect, IF 0x04&t;&t;; DISCONNECT&n;&n;at 0x000000df : */
l_int|0x800c0004
comma
l_int|0x000003b4
comma
multiline_comment|/*&n;    INT int_msg_1, IF 0x07&t;&t;&t;; MESSAGE REJECT&n;&n;at 0x000000e1 : */
l_int|0x980c0007
comma
l_int|0x01020000
comma
multiline_comment|/*&n;    INT int_msg_1, IF 0x0f&t;&t;&t;; INITIATE RECOVERY&n;&n;at 0x000000e3 : */
l_int|0x980c000f
comma
l_int|0x01020000
comma
multiline_comment|/*&n;    JUMP reject_message&n;&n;at 0x000000e5 : */
l_int|0x80080000
comma
l_int|0x000004b8
comma
multiline_comment|/*&n;&n;munge_2:&n;    JUMP reject_message&n;&n;at 0x000000e7 : */
l_int|0x80080000
comma
l_int|0x000004b8
comma
multiline_comment|/*&n;&n;munge_save_data_pointer:&n;    CLEAR ACK&n;&n;at 0x000000e9 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    RETURN&n;&n;at 0x000000eb : */
l_int|0x90080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;munge_disconnect:&n;    MOVE SCNTL2 &amp; 0x7f TO SCNTL2&n;&n;at 0x000000ed : */
l_int|0x7c027f00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    CLEAR ACK&n;&n;at 0x000000ef : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;&n;; Pass control to the DSA routine.  Note that we can not call&n;; dsa_to_scratch here because that would clobber temp, which &n;; we must preserve.&n;    MOVE DSA0 TO SFBR&n;&n;at 0x000000f1 : */
l_int|0x72100000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO SCRATCH0&n;&n;at 0x000000f3 : */
l_int|0x6a340000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA1 TO SFBR&n;&n;at 0x000000f5 : */
l_int|0x72110000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO SCRATCH1&n;&n;at 0x000000f7 : */
l_int|0x6a350000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA2 TO SFBR&n;&n;at 0x000000f9 : */
l_int|0x72120000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO SCRATCH2&n;&n;at 0x000000fb : */
l_int|0x6a360000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA3 TO SFBR&n;&n;at 0x000000fd : */
l_int|0x72130000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO SCRATCH3&n;&n;at 0x000000ff : */
l_int|0x6a370000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;    MOVE dmode_ncr_to_memory TO DMODE&n;&n;at 0x00000101 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE MEMORY 4, addr_scratch, jump_to_dsa + 4&n;&n;at 0x00000103 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000424
comma
multiline_comment|/*&n;    MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x00000106 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;jump_to_dsa:&n;    JUMP 0&n;&n;at 0x00000108 : */
l_int|0x80080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;&n;&n;&n;&n;munge_extended:&n;    CLEAR ACK&n;&n;at 0x0000010a : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    INT int_err_unexpected_phase, WHEN NOT MSG_IN&n;&n;at 0x0000010c : */
l_int|0x9f030000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE 1, msg_buf + 1, WHEN MSG_IN&n;&n;at 0x0000010e : */
l_int|0x0f000001
comma
l_int|0x00000001
comma
multiline_comment|/*&n;    JUMP munge_extended_2, IF 0x02&n;&n;at 0x00000110 : */
l_int|0x800c0002
comma
l_int|0x00000458
comma
multiline_comment|/*&n;    JUMP munge_extended_3, IF 0x03 &n;&n;at 0x00000112 : */
l_int|0x800c0003
comma
l_int|0x00000488
comma
multiline_comment|/*&n;    JUMP reject_message&n;&n;at 0x00000114 : */
l_int|0x80080000
comma
l_int|0x000004b8
comma
multiline_comment|/*&n;&n;munge_extended_2:&n;    CLEAR ACK&n;&n;at 0x00000116 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE 1, msg_buf + 2, WHEN MSG_IN&n;&n;at 0x00000118 : */
l_int|0x0f000001
comma
l_int|0x00000002
comma
multiline_comment|/*&n;    JUMP reject_message, IF NOT 0x02&t;; Must be WDTR&n;&n;at 0x0000011a : */
l_int|0x80040002
comma
l_int|0x000004b8
comma
multiline_comment|/*&n;    CLEAR ACK&n;&n;at 0x0000011c : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE 1, msg_buf + 3, WHEN MSG_IN&n;&n;at 0x0000011e : */
l_int|0x0f000001
comma
l_int|0x00000003
comma
multiline_comment|/*&n;    INT int_msg_wdtr&n;&n;at 0x00000120 : */
l_int|0x98080000
comma
l_int|0x01000000
comma
multiline_comment|/*&n;&n;munge_extended_3:&n;    CLEAR ACK&n;&n;at 0x00000122 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE 1, msg_buf + 2, WHEN MSG_IN&n;&n;at 0x00000124 : */
l_int|0x0f000001
comma
l_int|0x00000002
comma
multiline_comment|/*&n;    JUMP reject_message, IF NOT 0x01&t;; Must be SDTR&n;&n;at 0x00000126 : */
l_int|0x80040001
comma
l_int|0x000004b8
comma
multiline_comment|/*&n;    CLEAR ACK&n;&n;at 0x00000128 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE 2, msg_buf + 3, WHEN MSG_IN&n;&n;at 0x0000012a : */
l_int|0x0f000002
comma
l_int|0x00000003
comma
multiline_comment|/*&n;    INT int_msg_sdtr&n;&n;at 0x0000012c : */
l_int|0x98080000
comma
l_int|0x01010000
comma
multiline_comment|/*&n;&n;ENTRY reject_message&n;reject_message:&n;    SET ATN&n;&n;at 0x0000012e : */
l_int|0x58000008
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    CLEAR ACK&n;&n;at 0x00000130 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE 1, NCR53c7xx_msg_reject, WHEN MSG_OUT&n;&n;at 0x00000132 : */
l_int|0x0e000001
comma
(paren
(paren
r_int
r_int
)paren
op_amp
id|NCR53c7xx_msg_reject
)paren
comma
multiline_comment|/*&n;    RETURN&n;&n;at 0x00000134 : */
l_int|0x90080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;ENTRY accept_message&n;accept_message:&n;    CLEAR ACK&n;&n;at 0x00000136 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    RETURN&n;&n;at 0x00000138 : */
l_int|0x90080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;ENTRY respond_message&n;msg_respond:&n;    SET ATN&n;&n;at 0x0000013a : */
l_int|0x58000008
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    CLEAR ACK&n;&n;at 0x0000013c : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE FROM dsa_msgout_other, WHEN MSG_OUT&n;&n;at 0x0000013e : */
l_int|0x1e000000
comma
l_int|0x00000068
comma
multiline_comment|/*&n;    RETURN&n;&n;at 0x00000140 : */
l_int|0x90080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;;&n;; command_complete&n;;&n;; PURPOSE : handle command termination when STATUS IN is detected by reading&n;;&t;a status byte followed by a command termination message. &n;;&n;;&t;Normal termination results in an INTFLY instruction, and &n;;&t;the host system can pick out which command terminated by &n;;&t;examining the MESSAGE and STATUS buffers of all currently &n;;&t;executing commands;&n;;&n;;&t;Abnormal (CHECK_CONDITION) termination results in an&n;;&t;int_err_check_condition interrupt so that a REQUEST SENSE&n;;&t;command can be issued out-of-order so that no other command&n;;&t;clears the contingent allegience condition.&n;;&t;&n;;&n;; INPUTS : DSA - command&t;&n;;&n;; CALLS : OK&n;;&n;; EXITS : On successful termination, control is passed to schedule.&n;;&t;On abnormal termination, the user will usually modify the &n;;&t;DSA fields and corresponding buffers and return control&n;;&t;to select.&n;;&n;&n;ENTRY command_complete&n;command_complete:&n;    MOVE FROM dsa_status, WHEN STATUS&n;&n;at 0x00000142 : */
l_int|0x1b000000
comma
l_int|0x00000060
comma
multiline_comment|/*&n;&n;    MOVE SFBR TO SCRATCH0&t;&t;; Save status&n;&n;at 0x00000144 : */
l_int|0x6a340000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;ENTRY command_complete_msgin&n;command_complete_msgin:&n;    MOVE FROM dsa_msgin, WHEN MSG_IN&n;&n;at 0x00000146 : */
l_int|0x1f000000
comma
l_int|0x00000058
comma
multiline_comment|/*&n;; Indicate that we should be expecting a disconnect&n;    MOVE SCNTL2 &amp; 0x7f TO SCNTL2&n;&n;at 0x00000148 : */
l_int|0x7c027f00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    CLEAR ACK&n;&n;at 0x0000014a : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;    MOVE SCRATCH0 TO SFBR&t;&t;&t;&n;&n;at 0x0000014c : */
l_int|0x72340000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;;&n;; The SCSI specification states that when a UNIT ATTENTION condition&n;; is pending, as indicated by a CHECK CONDITION status message,&n;; the target shall revert to asynchronous transfers.  Since&n;; synchronous transfers parameters are maintained on a per INITIATOR/TARGET &n;; basis, and returning control to our scheduler could work on a command&n;; running on another lun on that target using the old parameters, we must&n;; interrupt the host processor to get them changed, or change them ourselves.&n;;&n;; Once SCSI-II tagged queueing is implemented, things will be even more&n;; hairy, since contingent allegience conditions exist on a per-target/lun&n;; basis, and issuing a new command with a different tag would clear it.&n;; In these cases, we must interrupt the host processor to get a request &n;; added to the HEAD of the queue with the request sense command, or we&n;; must automatically issue the request sense command.&n;&n;&n;&n;&n;    INTFLY&n;&n;at 0x0000014e : */
l_int|0x98180000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;    WAIT DISCONNECT&n;&n;at 0x00000150 : */
l_int|0x48000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;    JUMP schedule&n;&n;at 0x00000152 : */
l_int|0x80080000
comma
l_int|0x00000130
comma
multiline_comment|/*&n;command_failed:&n;    WAIT DISCONNECT&n;&n;at 0x00000154 : */
l_int|0x48000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    INT int_err_check_condition&n;&n;at 0x00000156 : */
l_int|0x98080000
comma
l_int|0x00030000
comma
multiline_comment|/*&n;&n;&n;&n;&n;;&n;; wait_reselect&n;;&n;; PURPOSE : This is essentially the idle routine, where control lands&n;;&t;when there are no new processes to schedule.  wait_reselect&n;;&t;waits for reselection, selection, and new commands.&n;;&n;;&t;When a successful reselection occurs, with the aid &n;;&t;of fixedup code in each DSA, wait_reselect walks the &n;;&t;reconnect_dsa_queue, asking each dsa if the target ID&n;;&t;and LUN match its.&n;;&n;;&t;If a match is found, a call is made back to reselected_ok,&n;;&t;which through the miracles of self modifying code, extracts&n;;&t;the found DSA from the reconnect_dsa_queue and then &n;;&t;returns control to the DSAs thread of execution.&n;;&n;; INPUTS : NONE&n;;&n;; CALLS : OK&n;;&n;; MODIFIES : DSA,&n;;&n;; EXITS : On successful reselection, control is returned to the &n;;&t;DSA which called reselected_ok.  If the WAIT RESELECT&n;;&t;was interrupted by a new commands arival signalled by &n;;&t;SIG_P, control is passed to schedule.  If the NCR is &n;;&t;selected, the host system is interrupted with an &n;;&t;int_err_selected which is usually responded to by&n;;&t;setting DSP to the target_abort address.&n;    &n;wait_reselect:&n;&n;&n;&n;    WAIT RESELECT wait_reselect_failed&n;&n;at 0x00000158 : */
l_int|0x50000000
comma
l_int|0x0000067c
comma
multiline_comment|/*&n;&n;reselected:&n;    ; Read all data needed to restablish the nexus - &n;    MOVE 1, reselected_identify, WHEN MSG_IN&n;&n;at 0x0000015a : */
l_int|0x0f000001
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;    ; Well add a jump to here after some how determining that &n;    ; tagged queueing isnt in use on this device.&n;reselected_notag:    &n;    MOVE MEMORY 1, NCR53c7xx_zero, reselected_tag&n;&n;at 0x0000015c : */
l_int|0xc0000001
comma
(paren
(paren
r_int
r_int
)paren
op_amp
id|NCR53c7xx_zero
)paren
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;&n;&n;&n;&n;    ; Point DSA at the current head of the disconnected queue.&n;    MOVE dmode_memory_to_ncr  TO DMODE&n;&n;at 0x0000015f : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE MEMORY 4, reconnect_dsa_head, addr_scratch&n;&n;at 0x00000161 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x00000164 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    CALL scratch_to_dsa&n;&n;at 0x00000166 : */
l_int|0x88080000
comma
l_int|0x00000800
comma
multiline_comment|/*&n;&n;    ; Fix the update-next pointer so that the reconnect_dsa_head&n;    ; pointer is the one that will be updated if this DSA is a hit &n;    ; and we remove it from the queue.&n;&n;    MOVE MEMORY 4, reconnect_dsa_head, reselected_ok + 8&n;&n;at 0x00000168 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000660
comma
multiline_comment|/*&n;&n;ENTRY reselected_check_next&n;reselected_check_next:&n;    ; Check for a NULL pointer.&n;    MOVE DSA0 TO SFBR&n;&n;at 0x0000016b : */
l_int|0x72100000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP reselected_not_end, IF NOT 0&n;&n;at 0x0000016d : */
l_int|0x80040000
comma
l_int|0x000005f4
comma
multiline_comment|/*&n;    MOVE DSA1 TO SFBR&n;&n;at 0x0000016f : */
l_int|0x72110000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP reselected_not_end, IF NOT 0&n;&n;at 0x00000171 : */
l_int|0x80040000
comma
l_int|0x000005f4
comma
multiline_comment|/*&n;    MOVE DSA2 TO SFBR&n;&n;at 0x00000173 : */
l_int|0x72120000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP reselected_not_end, IF NOT 0&n;&n;at 0x00000175 : */
l_int|0x80040000
comma
l_int|0x000005f4
comma
multiline_comment|/*&n;    MOVE DSA3 TO SFBR&n;&n;at 0x00000177 : */
l_int|0x72130000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP reselected_not_end, IF NOT 0&n;&n;at 0x00000179 : */
l_int|0x80040000
comma
l_int|0x000005f4
comma
multiline_comment|/*&n;    INT int_err_unexpected_reselect&n;&n;at 0x0000017b : */
l_int|0x98080000
comma
l_int|0x00020000
comma
multiline_comment|/*&n;&n;reselected_not_end:&n;    MOVE DSA0 TO SFBR&n;&n;at 0x0000017d : */
l_int|0x72100000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    ;&n;    ; XXX the ALU is only eight bits wide, and the assembler&n;    ; wont do the dirt work for us.  As long as dsa_check_reselect&n;    ; is negative, we need to sign extend with 1 bits to the full&n;    ; 32 bit width oof the address.&n;    ;&n;    ; A potential work arround would be to have a known alignment &n;    ; of the DSA structure such that the base address plus &n;    ; dsa_check_reselect doesnt require carryin from bytes &n;    ; higher than the LSB.&n;    ;&n;&n;    MOVE SFBR + dsa_check_reselect TO SCRATCH0&n;&n;at 0x0000017f : */
l_int|0x6e340000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA1 TO SFBR&n;&n;at 0x00000181 : */
l_int|0x72110000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR + 0xff TO SCRATCH1 WITH CARRY&n;&n;at 0x00000183 : */
l_int|0x6f35ff00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA2 TO SFBR&n;&n;at 0x00000185 : */
l_int|0x72120000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR + 0xff TO SCRATCH2 WITH CARRY&n;&n;at 0x00000187 : */
l_int|0x6f36ff00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA3 TO SFBR&n;&n;at 0x00000189 : */
l_int|0x72130000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR + 0xff TO SCRATCH3 WITH CARRY&n;&n;at 0x0000018b : */
l_int|0x6f37ff00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;    MOVE dmode_ncr_to_memory TO DMODE&n;&n;at 0x0000018d : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE MEMORY 4, addr_scratch, reselected_check + 4&n;&n;at 0x0000018f : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000654
comma
multiline_comment|/*&n;    MOVE dmode_memory_to_memory TO DMODE&n;&n;at 0x00000192 : */
l_int|0x78380000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;reselected_check:&n;    JUMP 0&n;&n;at 0x00000194 : */
l_int|0x80080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;&n;;&n;;&n;reselected_ok:&n;    MOVE MEMORY 4, 0, 0&t;&t;&t;&t;; Patched : first word&n;&n;at 0x00000196 : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t;; &t;is this successful &n;&t;&t;&t;&t;&t;&t;; &t;dsa_next&n;&t;&t;&t;&t;&t;&t;; Second word is &n;&t;&t;&t;&t;&t;&t;;&t;unsuccessful dsa_next&n;    CLEAR ACK&t;&t;&t;&t;&t;; Accept last message&n;&n;at 0x00000199 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    RETURN&t;&t;&t;&t;&t;; Return control to where&n;&n;at 0x0000019b : */
l_int|0x90080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;&n;&n;&n;selected:&n;    INT int_err_selected;&n;&n;at 0x0000019d : */
l_int|0x98080000
comma
l_int|0x00010000
comma
multiline_comment|/*&n;&n;;&n;; A select or reselect failure can be caused by one of two conditions : &n;; 1.  SIG_P was set.  This will be the case if the user has written&n;;&t;a new value to a previously NULL head of the issue queue.&n;;&n;; 2.  The NCR53c810 was selected or reselected by another device.&n;; &n;&n;wait_reselect_failed:&n;; Reading CTEST2 clears the SIG_P bit in the ISTAT register.&n;    MOVE CTEST2 &amp; 0x40 TO SFBR&t;&n;&n;at 0x0000019f : */
l_int|0x741a4000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP selected, IF NOT 0x40&n;&n;at 0x000001a1 : */
l_int|0x80040040
comma
l_int|0x00000674
comma
multiline_comment|/*&n;    JUMP schedule&n;&n;at 0x000001a3 : */
l_int|0x80080000
comma
l_int|0x00000130
comma
multiline_comment|/*&n;&n;select_failed:&n;    MOVE ISTAT &amp; 0x20 TO SFBR&n;&n;at 0x000001a5 : */
l_int|0x74142000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP reselected, IF NOT 0x20&n;&n;at 0x000001a7 : */
l_int|0x80040020
comma
l_int|0x00000568
comma
multiline_comment|/*&n;    MOVE ISTAT &amp; 0xdf TO ISTAT&n;&n;at 0x000001a9 : */
l_int|0x7c14df00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP schedule&n;&n;at 0x000001ab : */
l_int|0x80080000
comma
l_int|0x00000130
comma
multiline_comment|/*&n;&n;;&n;; test_1&n;; test_2&n;;&n;; PURPOSE : run some verification tests on the NCR.  test_1&n;;&t;copies test_src to test_dest and interrupts the host&n;;&t;processor, testing for cache coherency and interrupt&n;; &t;problems in the processes.&n;;&n;;&t;test_2 runs a command with offsets relative to the &n;;&t;DSA on entry, and is useful for miscellaneous experimentation.&n;;&n;&n;; Verify that interrupts are working correctly and that we dont &n;; have a cache invalidation problem.&n;&n;ABSOLUTE test_src = 0, test_dest = 0&n;ENTRY test_1&n;test_1:&n;    MOVE MEMORY 4, test_src, test_dest&n;&n;at 0x000001ad : */
l_int|0xc0000004
comma
l_int|0x00000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    INT int_test_1&n;&n;at 0x000001b0 : */
l_int|0x98080000
comma
l_int|0x04000000
comma
multiline_comment|/*&n;&n;;&n;; Run arbitrary commands, with test code establishing a DSA&n;;&n; &n;ENTRY test_2&n;test_2:&n;    CLEAR TARGET&n;&n;at 0x000001b2 : */
l_int|0x60000200
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    SELECT ATN FROM 0, test_2_fail&n;&n;at 0x000001b4 : */
l_int|0x43000000
comma
l_int|0x00000720
comma
multiline_comment|/*&n;    JUMP test_2_msgout, WHEN MSG_OUT&n;&n;at 0x000001b6 : */
l_int|0x860b0000
comma
l_int|0x000006e0
comma
multiline_comment|/*&n;ENTRY test_2_msgout&n;test_2_msgout:&n;    MOVE FROM 8, WHEN MSG_OUT&n;&n;at 0x000001b8 : */
l_int|0x1e000000
comma
l_int|0x00000008
comma
multiline_comment|/*&n;    MOVE FROM 16, WHEN CMD &n;&n;at 0x000001ba : */
l_int|0x1a000000
comma
l_int|0x00000010
comma
multiline_comment|/*&n;    MOVE FROM 24, WHEN DATA_IN&n;&n;at 0x000001bc : */
l_int|0x19000000
comma
l_int|0x00000018
comma
multiline_comment|/*&n;    MOVE FROM 32, WHEN STATUS&n;&n;at 0x000001be : */
l_int|0x1b000000
comma
l_int|0x00000020
comma
multiline_comment|/*&n;    MOVE FROM 40, WHEN MSG_IN&n;&n;at 0x000001c0 : */
l_int|0x1f000000
comma
l_int|0x00000028
comma
multiline_comment|/*&n;    MOVE SCNTL2 &amp; 0x7f TO SCNTL2&n;&n;at 0x000001c2 : */
l_int|0x7c027f00
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    CLEAR ACK&n;&n;at 0x000001c4 : */
l_int|0x60000040
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    WAIT DISCONNECT&n;&n;at 0x000001c6 : */
l_int|0x48000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;test_2_fail:&n;    INT int_test_2&n;&n;at 0x000001c8 : */
l_int|0x98080000
comma
l_int|0x04010000
comma
multiline_comment|/*&n;&n;ENTRY debug_break&n;debug_break:&n;    INT int_debug_break&n;&n;at 0x000001ca : */
l_int|0x98080000
comma
l_int|0x03000000
comma
multiline_comment|/*&n;&n;;&n;; initiator_abort&n;; target_abort&n;;&n;; PURPOSE : Abort the currently established nexus from with initiator&n;;&t;or target mode.&n;;&n;;  &n;&n;ENTRY target_abort&n;target_abort:&n;    SET TARGET&n;&n;at 0x000001cc : */
l_int|0x58000200
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    DISCONNECT&n;&n;at 0x000001ce : */
l_int|0x48000000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    CLEAR TARGET&n;&n;at 0x000001d0 : */
l_int|0x60000200
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    JUMP schedule&n;&n;at 0x000001d2 : */
l_int|0x80080000
comma
l_int|0x00000130
comma
multiline_comment|/*&n;    &n;ENTRY initiator_abort&n;initiator_abort:&n;    SET ATN&n;&n;at 0x000001d4 : */
l_int|0x58000008
comma
l_int|0x00000000
comma
multiline_comment|/*&n;; In order to abort the currently established nexus, we &n;; need to source/sink up to one byte of data in any SCSI phase, &n;; since the phase cannot change until REQ transitions &n;; false-&gt;true&n;    JUMP no_eat_cmd, WHEN NOT CMD&n;&n;at 0x000001d6 : */
l_int|0x82030000
comma
l_int|0x00000768
comma
multiline_comment|/*&n;    MOVE 1, NCR53c7xx_zero, WHEN CMD&n;&n;at 0x000001d8 : */
l_int|0x0a000001
comma
(paren
(paren
r_int
r_int
)paren
op_amp
id|NCR53c7xx_zero
)paren
comma
multiline_comment|/*&n;no_eat_cmd:&n;    JUMP no_eat_msg, WHEN NOT MSG_IN&n;&n;at 0x000001da : */
l_int|0x87030000
comma
l_int|0x00000778
comma
multiline_comment|/*&n;    MOVE 1, NCR53c7xx_sink, WHEN MSG_IN&n;&n;at 0x000001dc : */
l_int|0x0f000001
comma
(paren
(paren
r_int
r_int
)paren
op_amp
id|NCR53c7xx_sink
)paren
comma
multiline_comment|/*&n;no_eat_msg:&n;    JUMP no_eat_data, WHEN NOT DATA_IN&n;&n;at 0x000001de : */
l_int|0x81030000
comma
l_int|0x00000788
comma
multiline_comment|/*&n;    MOVE 1, NCR53c7xx_sink, WHEN DATA_IN&n;&n;at 0x000001e0 : */
l_int|0x09000001
comma
(paren
(paren
r_int
r_int
)paren
op_amp
id|NCR53c7xx_sink
)paren
comma
multiline_comment|/*&n;no_eat_data:&n;    JUMP no_eat_status, WHEN NOT STATUS&n;&n;at 0x000001e2 : */
l_int|0x83030000
comma
l_int|0x00000798
comma
multiline_comment|/*&n;    MOVE 1, NCR53c7xx_sink, WHEN STATUS&n;&n;at 0x000001e4 : */
l_int|0x0b000001
comma
(paren
(paren
r_int
r_int
)paren
op_amp
id|NCR53c7xx_sink
)paren
comma
multiline_comment|/*&n;no_eat_status:&n;    JUMP no_source_data, WHEN NOT DATA_OUT&n;&n;at 0x000001e6 : */
l_int|0x80030000
comma
l_int|0x000007a8
comma
multiline_comment|/*&n;    MOVE 1, NCR53c7xx_zero, WHEN DATA_OUT&n;&n;at 0x000001e8 : */
l_int|0x08000001
comma
(paren
(paren
r_int
r_int
)paren
op_amp
id|NCR53c7xx_zero
)paren
comma
multiline_comment|/*&n;no_source_data:&n;;&n;; If DSP points here, and a phase mismatch is encountered, we need to &n;; do a bus reset.&n;;&n;    MOVE 1, NCR53c7xx_msg_abort, WHEN MSG_OUT&n;&n;at 0x000001ea : */
l_int|0x0e000001
comma
(paren
(paren
r_int
r_int
)paren
op_amp
id|NCR53c7xx_msg_abort
)paren
comma
multiline_comment|/*&n;    INT int_norm_aborted&n;&n;at 0x000001ec : */
l_int|0x98080000
comma
l_int|0x02040000
comma
multiline_comment|/*&n;&n;;&n;; dsa_to_scratch&n;; scratch_to_dsa&n;;&n;; PURPOSE :&n;; &t;The NCR chips cannot do a move memory instruction with the DSA register &n;; &t;as the source or destination.  So, we provide a couple of subroutines&n;; &t;that let us switch between the DSA register and scratch register.&n;;&n;; &t;Memory moves to/from the DSPS  register also dont work, but we &n;; &t;dont use them.&n;;&n;;&n;&n; &n;dsa_to_scratch:&n;    MOVE DSA0 TO SFBR&n;&n;at 0x000001ee : */
l_int|0x72100000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO SCRATCH0&n;&n;at 0x000001f0 : */
l_int|0x6a340000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA1 TO SFBR&n;&n;at 0x000001f2 : */
l_int|0x72110000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO SCRATCH1&n;&n;at 0x000001f4 : */
l_int|0x6a350000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA2 TO SFBR&n;&n;at 0x000001f6 : */
l_int|0x72120000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO SCRATCH2&n;&n;at 0x000001f8 : */
l_int|0x6a360000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE DSA3 TO SFBR&n;&n;at 0x000001fa : */
l_int|0x72130000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO SCRATCH3&n;&n;at 0x000001fc : */
l_int|0x6a370000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    RETURN&n;&n;at 0x000001fe : */
l_int|0x90080000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;&n;scratch_to_dsa:&n;    MOVE SCRATCH0 TO SFBR&n;&n;at 0x00000200 : */
l_int|0x72340000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO DSA0&n;&n;at 0x00000202 : */
l_int|0x6a100000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH1 TO SFBR&n;&n;at 0x00000204 : */
l_int|0x72350000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO DSA1&n;&n;at 0x00000206 : */
l_int|0x6a110000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH2 TO SFBR&n;&n;at 0x00000208 : */
l_int|0x72360000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO DSA2&n;&n;at 0x0000020a : */
l_int|0x6a120000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SCRATCH3 TO SFBR&n;&n;at 0x0000020c : */
l_int|0x72370000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    MOVE SFBR TO DSA3&n;&n;at 0x0000020e : */
l_int|0x6a130000
comma
l_int|0x00000000
comma
multiline_comment|/*&n;    RETURN&n;&n;at 0x00000210 : */
l_int|0x90080000
comma
l_int|0x00000000
comma
)brace
suffix:semicolon
DECL|macro|A_addr_scratch
mdefine_line|#define A_addr_scratch&t;0x00000000
DECL|variable|A_addr_scratch_used
r_int
r_int
id|A_addr_scratch_used
(braket
)braket
op_assign
(brace
l_int|0x00000007
comma
l_int|0x0000003a
comma
l_int|0x00000046
comma
l_int|0x00000050
comma
l_int|0x0000007a
comma
l_int|0x000000a8
comma
l_int|0x000000be
comma
l_int|0x00000104
comma
l_int|0x00000163
comma
l_int|0x00000190
comma
)brace
suffix:semicolon
DECL|macro|A_addr_sfbr
mdefine_line|#define A_addr_sfbr&t;0x00000000
DECL|variable|A_addr_sfbr_used
r_int
r_int
id|A_addr_sfbr_used
(braket
)braket
op_assign
(brace
l_int|0x00000016
comma
)brace
suffix:semicolon
DECL|macro|A_addr_temp
mdefine_line|#define A_addr_temp&t;0x00000000
DECL|variable|A_addr_temp_used
r_int
r_int
id|A_addr_temp_used
(braket
)braket
op_assign
(brace
l_int|0x00000027
comma
)brace
suffix:semicolon
DECL|macro|A_dmode_memory_to_memory
mdefine_line|#define A_dmode_memory_to_memory&t;0x00000000
DECL|variable|A_dmode_memory_to_memory_used
r_int
r_int
id|A_dmode_memory_to_memory_used
(braket
)braket
op_assign
(brace
l_int|0x00000008
comma
l_int|0x00000019
comma
l_int|0x00000029
comma
l_int|0x0000003c
comma
l_int|0x00000048
comma
l_int|0x00000051
comma
l_int|0x0000007c
comma
l_int|0x000000aa
comma
l_int|0x000000c0
comma
l_int|0x00000106
comma
l_int|0x00000164
comma
l_int|0x00000192
comma
)brace
suffix:semicolon
DECL|macro|A_dmode_memory_to_ncr
mdefine_line|#define A_dmode_memory_to_ncr&t;0x00000000
DECL|variable|A_dmode_memory_to_ncr_used
r_int
r_int
id|A_dmode_memory_to_ncr_used
(braket
)braket
op_assign
(brace
l_int|0x00000003
comma
l_int|0x00000012
comma
l_int|0x0000004c
comma
l_int|0x0000015f
comma
)brace
suffix:semicolon
DECL|macro|A_dmode_ncr_to_memory
mdefine_line|#define A_dmode_ncr_to_memory&t;0x00000000
DECL|variable|A_dmode_ncr_to_memory_used
r_int
r_int
id|A_dmode_ncr_to_memory_used
(braket
)braket
op_assign
(brace
l_int|0x00000024
comma
l_int|0x00000037
comma
l_int|0x00000043
comma
l_int|0x00000077
comma
l_int|0x000000a5
comma
l_int|0x000000bb
comma
l_int|0x00000101
comma
l_int|0x0000018d
comma
)brace
suffix:semicolon
DECL|macro|A_dmode_ncr_to_ncr
mdefine_line|#define A_dmode_ncr_to_ncr&t;0x00000000
DECL|variable|A_dmode_ncr_to_ncr_used
r_int
r_int
id|A_dmode_ncr_to_ncr_used
(braket
)braket
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_dsa_check_reselect
mdefine_line|#define A_dsa_check_reselect&t;0x00000000
DECL|variable|A_dsa_check_reselect_used
r_int
r_int
id|A_dsa_check_reselect_used
(braket
)braket
op_assign
(brace
l_int|0x0000017f
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_cmdout
mdefine_line|#define A_dsa_cmdout&t;0x00000048
DECL|variable|A_dsa_cmdout_used
r_int
r_int
id|A_dsa_cmdout_used
(braket
)braket
op_assign
(brace
l_int|0x0000008c
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_cmnd
mdefine_line|#define A_dsa_cmnd&t;0x00000038
DECL|variable|A_dsa_cmnd_used
r_int
r_int
id|A_dsa_cmnd_used
(braket
)braket
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_dsa_datain
mdefine_line|#define A_dsa_datain&t;0x00000054
DECL|variable|A_dsa_datain_used
r_int
r_int
id|A_dsa_datain_used
(braket
)braket
op_assign
(brace
l_int|0x000000b3
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_dataout
mdefine_line|#define A_dsa_dataout&t;0x00000050
DECL|variable|A_dsa_dataout_used
r_int
r_int
id|A_dsa_dataout_used
(braket
)braket
op_assign
(brace
l_int|0x0000009d
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_end
mdefine_line|#define A_dsa_end&t;0x00000070
DECL|variable|A_dsa_end_used
r_int
r_int
id|A_dsa_end_used
(braket
)braket
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_dsa_fields_start
mdefine_line|#define A_dsa_fields_start&t;0x00000024
DECL|variable|A_dsa_fields_start_used
r_int
r_int
id|A_dsa_fields_start_used
(braket
)braket
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_dsa_msgin
mdefine_line|#define A_dsa_msgin&t;0x00000058
DECL|variable|A_dsa_msgin_used
r_int
r_int
id|A_dsa_msgin_used
(braket
)braket
op_assign
(brace
l_int|0x00000147
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_msgout
mdefine_line|#define A_dsa_msgout&t;0x00000040
DECL|variable|A_dsa_msgout_used
r_int
r_int
id|A_dsa_msgout_used
(braket
)braket
op_assign
(brace
l_int|0x0000006c
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_msgout_other
mdefine_line|#define A_dsa_msgout_other&t;0x00000068
DECL|variable|A_dsa_msgout_other_used
r_int
r_int
id|A_dsa_msgout_other_used
(braket
)braket
op_assign
(brace
l_int|0x0000013f
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_next
mdefine_line|#define A_dsa_next&t;0x00000030
DECL|variable|A_dsa_next_used
r_int
r_int
id|A_dsa_next_used
(braket
)braket
op_assign
(brace
l_int|0x0000002f
comma
l_int|0x0000006f
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_select
mdefine_line|#define A_dsa_select&t;0x0000003c
DECL|variable|A_dsa_select_used
r_int
r_int
id|A_dsa_select_used
(braket
)braket
op_assign
(brace
l_int|0x00000067
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_status
mdefine_line|#define A_dsa_status&t;0x00000060
DECL|variable|A_dsa_status_used
r_int
r_int
id|A_dsa_status_used
(braket
)braket
op_assign
(brace
l_int|0x00000143
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_temp_dsa_next
mdefine_line|#define A_dsa_temp_dsa_next&t;0x00000000
DECL|variable|A_dsa_temp_dsa_next_used
r_int
r_int
id|A_dsa_temp_dsa_next_used
(braket
)braket
op_assign
(brace
l_int|0x00000001
comma
l_int|0x00000006
comma
l_int|0x0000001c
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_temp_jump_resume
mdefine_line|#define A_dsa_temp_jump_resume&t;0x00000000
DECL|variable|A_dsa_temp_jump_resume_used
r_int
r_int
id|A_dsa_temp_jump_resume_used
(braket
)braket
op_assign
(brace
l_int|0x00000028
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_temp_lun
mdefine_line|#define A_dsa_temp_lun&t;0x00000000
DECL|variable|A_dsa_temp_lun_used
r_int
r_int
id|A_dsa_temp_lun_used
(braket
)braket
op_assign
(brace
l_int|0x00000017
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_temp_sync
mdefine_line|#define A_dsa_temp_sync&t;0x00000000
DECL|variable|A_dsa_temp_sync_used
r_int
r_int
id|A_dsa_temp_sync_used
(braket
)braket
op_assign
(brace
l_int|0x00000021
comma
)brace
suffix:semicolon
DECL|macro|A_dsa_temp_target
mdefine_line|#define A_dsa_temp_target&t;0x00000000
DECL|variable|A_dsa_temp_target_used
r_int
r_int
id|A_dsa_temp_target_used
(braket
)braket
op_assign
(brace
l_int|0x00000010
comma
)brace
suffix:semicolon
DECL|macro|A_int_debug_break
mdefine_line|#define A_int_debug_break&t;0x03000000
DECL|variable|A_int_debug_break_used
r_int
r_int
id|A_int_debug_break_used
(braket
)braket
op_assign
(brace
l_int|0x000001cb
comma
)brace
suffix:semicolon
DECL|macro|A_int_debug_dsa_loaded
mdefine_line|#define A_int_debug_dsa_loaded&t;0x03030000
DECL|variable|A_int_debug_dsa_loaded_used
r_int
r_int
id|A_int_debug_dsa_loaded_used
(braket
)braket
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_int_debug_head
mdefine_line|#define A_int_debug_head&t;0x03050000
DECL|variable|A_int_debug_head_used
r_int
r_int
id|A_int_debug_head_used
(braket
)braket
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_int_debug_idle
mdefine_line|#define A_int_debug_idle&t;0x03020000
DECL|variable|A_int_debug_idle_used
r_int
r_int
id|A_int_debug_idle_used
(braket
)braket
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_int_debug_reselected
mdefine_line|#define A_int_debug_reselected&t;0x03040000
DECL|variable|A_int_debug_reselected_used
r_int
r_int
id|A_int_debug_reselected_used
(braket
)braket
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_int_debug_scheduled
mdefine_line|#define A_int_debug_scheduled&t;0x03010000
DECL|variable|A_int_debug_scheduled_used
r_int
r_int
id|A_int_debug_scheduled_used
(braket
)braket
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_int_err_check_condition
mdefine_line|#define A_int_err_check_condition&t;0x00030000
DECL|variable|A_int_err_check_condition_used
r_int
r_int
id|A_int_err_check_condition_used
(braket
)braket
op_assign
(brace
l_int|0x00000157
comma
)brace
suffix:semicolon
DECL|macro|A_int_err_no_phase
mdefine_line|#define A_int_err_no_phase&t;0x00040000
DECL|variable|A_int_err_no_phase_used
r_int
r_int
id|A_int_err_no_phase_used
(braket
)braket
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_int_err_selected
mdefine_line|#define A_int_err_selected&t;0x00010000
DECL|variable|A_int_err_selected_used
r_int
r_int
id|A_int_err_selected_used
(braket
)braket
op_assign
(brace
l_int|0x0000019e
comma
)brace
suffix:semicolon
DECL|macro|A_int_err_unexpected_phase
mdefine_line|#define A_int_err_unexpected_phase&t;0x00000000
DECL|variable|A_int_err_unexpected_phase_used
r_int
r_int
id|A_int_err_unexpected_phase_used
(braket
)braket
op_assign
(brace
l_int|0x00000084
comma
l_int|0x0000008a
comma
l_int|0x0000008e
comma
l_int|0x00000092
comma
l_int|0x000000c8
comma
l_int|0x000000cc
comma
l_int|0x000000ce
comma
l_int|0x000000d0
comma
l_int|0x0000010d
comma
)brace
suffix:semicolon
DECL|macro|A_int_err_unexpected_reselect
mdefine_line|#define A_int_err_unexpected_reselect&t;0x00020000
DECL|variable|A_int_err_unexpected_reselect_used
r_int
r_int
id|A_int_err_unexpected_reselect_used
(braket
)braket
op_assign
(brace
l_int|0x0000017c
comma
)brace
suffix:semicolon
DECL|macro|A_int_msg_1
mdefine_line|#define A_int_msg_1&t;0x01020000
DECL|variable|A_int_msg_1_used
r_int
r_int
id|A_int_msg_1_used
(braket
)braket
op_assign
(brace
l_int|0x000000e2
comma
l_int|0x000000e4
comma
)brace
suffix:semicolon
DECL|macro|A_int_msg_sdtr
mdefine_line|#define A_int_msg_sdtr&t;0x01010000
DECL|variable|A_int_msg_sdtr_used
r_int
r_int
id|A_int_msg_sdtr_used
(braket
)braket
op_assign
(brace
l_int|0x0000012d
comma
)brace
suffix:semicolon
DECL|macro|A_int_msg_wdtr
mdefine_line|#define A_int_msg_wdtr&t;0x01000000
DECL|variable|A_int_msg_wdtr_used
r_int
r_int
id|A_int_msg_wdtr_used
(braket
)braket
op_assign
(brace
l_int|0x00000121
comma
)brace
suffix:semicolon
DECL|macro|A_int_norm_aborted
mdefine_line|#define A_int_norm_aborted&t;0x02040000
DECL|variable|A_int_norm_aborted_used
r_int
r_int
id|A_int_norm_aborted_used
(braket
)braket
op_assign
(brace
l_int|0x000001ed
comma
)brace
suffix:semicolon
DECL|macro|A_int_norm_command_complete
mdefine_line|#define A_int_norm_command_complete&t;0x02020000
DECL|variable|A_int_norm_command_complete_used
r_int
r_int
id|A_int_norm_command_complete_used
(braket
)braket
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_int_norm_disconnected
mdefine_line|#define A_int_norm_disconnected&t;0x02030000
DECL|variable|A_int_norm_disconnected_used
r_int
r_int
id|A_int_norm_disconnected_used
(braket
)braket
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_int_norm_reselect_complete
mdefine_line|#define A_int_norm_reselect_complete&t;0x02010000
DECL|variable|A_int_norm_reselect_complete_used
r_int
r_int
id|A_int_norm_reselect_complete_used
(braket
)braket
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_int_norm_reset
mdefine_line|#define A_int_norm_reset&t;0x02050000
DECL|variable|A_int_norm_reset_used
r_int
r_int
id|A_int_norm_reset_used
(braket
)braket
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_int_norm_select_complete
mdefine_line|#define A_int_norm_select_complete&t;0x02000000
DECL|variable|A_int_norm_select_complete_used
r_int
r_int
id|A_int_norm_select_complete_used
(braket
)braket
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_int_test_1
mdefine_line|#define A_int_test_1&t;0x04000000
DECL|variable|A_int_test_1_used
r_int
r_int
id|A_int_test_1_used
(braket
)braket
op_assign
(brace
l_int|0x000001b1
comma
)brace
suffix:semicolon
DECL|macro|A_int_test_2
mdefine_line|#define A_int_test_2&t;0x04010000
DECL|variable|A_int_test_2_used
r_int
r_int
id|A_int_test_2_used
(braket
)braket
op_assign
(brace
l_int|0x000001c9
comma
)brace
suffix:semicolon
DECL|macro|A_int_test_3
mdefine_line|#define A_int_test_3&t;0x04020000
DECL|variable|A_int_test_3_used
r_int
r_int
id|A_int_test_3_used
(braket
)braket
op_assign
(brace
)brace
suffix:semicolon
DECL|macro|A_issue_dsa_head
mdefine_line|#define A_issue_dsa_head&t;0x00000000
DECL|variable|A_issue_dsa_head_used
r_int
r_int
id|A_issue_dsa_head_used
(braket
)braket
op_assign
(brace
l_int|0x0000004f
comma
l_int|0x00000080
comma
)brace
suffix:semicolon
DECL|macro|A_msg_buf
mdefine_line|#define A_msg_buf&t;0x00000000
DECL|variable|A_msg_buf_used
r_int
r_int
id|A_msg_buf_used
(braket
)braket
op_assign
(brace
l_int|0x000000d6
comma
l_int|0x0000010f
comma
l_int|0x00000119
comma
l_int|0x0000011f
comma
l_int|0x00000125
comma
l_int|0x0000012b
comma
)brace
suffix:semicolon
DECL|macro|A_reconnect_dsa_head
mdefine_line|#define A_reconnect_dsa_head&t;0x00000000
DECL|variable|A_reconnect_dsa_head_used
r_int
r_int
id|A_reconnect_dsa_head_used
(braket
)braket
op_assign
(brace
l_int|0x0000003f
comma
l_int|0x00000047
comma
l_int|0x00000162
comma
l_int|0x00000169
comma
)brace
suffix:semicolon
DECL|macro|A_reselected_identify
mdefine_line|#define A_reselected_identify&t;0x00000000
DECL|variable|A_reselected_identify_used
r_int
r_int
id|A_reselected_identify_used
(braket
)braket
op_assign
(brace
l_int|0x00000015
comma
l_int|0x0000015b
comma
)brace
suffix:semicolon
DECL|macro|A_reselected_tag
mdefine_line|#define A_reselected_tag&t;0x00000000
DECL|variable|A_reselected_tag_used
r_int
r_int
id|A_reselected_tag_used
(braket
)braket
op_assign
(brace
l_int|0x0000015e
comma
)brace
suffix:semicolon
DECL|macro|A_test_dest
mdefine_line|#define A_test_dest&t;0x00000000
DECL|variable|A_test_dest_used
r_int
r_int
id|A_test_dest_used
(braket
)braket
op_assign
(brace
l_int|0x000001af
comma
)brace
suffix:semicolon
DECL|macro|A_test_src
mdefine_line|#define A_test_src&t;0x00000000
DECL|variable|A_test_src_used
r_int
r_int
id|A_test_src_used
(braket
)braket
op_assign
(brace
l_int|0x000001ae
comma
)brace
suffix:semicolon
DECL|macro|Ent_accept_message
mdefine_line|#define Ent_accept_message&t;0x000004d8
DECL|macro|Ent_cmdout_cmdout
mdefine_line|#define Ent_cmdout_cmdout&t;0x0000022c
DECL|macro|Ent_command_complete
mdefine_line|#define Ent_command_complete&t;0x00000508
DECL|macro|Ent_command_complete_msgin
mdefine_line|#define Ent_command_complete_msgin&t;0x00000518
DECL|macro|Ent_debug_break
mdefine_line|#define Ent_debug_break&t;0x00000728
DECL|macro|Ent_dsa_code_check_reselect
mdefine_line|#define Ent_dsa_code_check_reselect&t;0x00000038
DECL|macro|Ent_dsa_code_template
mdefine_line|#define Ent_dsa_code_template&t;0x00000000
DECL|macro|Ent_dsa_code_template_end
mdefine_line|#define Ent_dsa_code_template_end&t;0x000000b4
DECL|macro|Ent_dsa_jump_resume
mdefine_line|#define Ent_dsa_jump_resume&t;0x00000088
DECL|macro|Ent_dsa_schedule
mdefine_line|#define Ent_dsa_schedule&t;0x000000b4
DECL|macro|Ent_dsa_zero
mdefine_line|#define Ent_dsa_zero&t;0x00000090
DECL|macro|Ent_initiator_abort
mdefine_line|#define Ent_initiator_abort&t;0x00000750
DECL|macro|Ent_msg_in
mdefine_line|#define Ent_msg_in&t;0x00000354
DECL|macro|Ent_other_transfer
mdefine_line|#define Ent_other_transfer&t;0x0000031c
DECL|macro|Ent_reject_message
mdefine_line|#define Ent_reject_message&t;0x000004b8
DECL|macro|Ent_reselected_check_next
mdefine_line|#define Ent_reselected_check_next&t;0x000005ac
DECL|macro|Ent_respond_message
mdefine_line|#define Ent_respond_message&t;0x00000000
DECL|macro|Ent_schedule
mdefine_line|#define Ent_schedule&t;0x00000130
DECL|macro|Ent_select
mdefine_line|#define Ent_select&t;0x00000194
DECL|macro|Ent_select_msgout
mdefine_line|#define Ent_select_msgout&t;0x000001ac
DECL|macro|Ent_target_abort
mdefine_line|#define Ent_target_abort&t;0x00000730
DECL|macro|Ent_test_1
mdefine_line|#define Ent_test_1&t;0x000006b4
DECL|macro|Ent_test_2
mdefine_line|#define Ent_test_2&t;0x000006c8
DECL|macro|Ent_test_2_msgout
mdefine_line|#define Ent_test_2_msgout&t;0x000006e0
DECL|variable|LABELPATCHES
r_int
r_int
id|LABELPATCHES
(braket
)braket
op_assign
(brace
l_int|0x00000002
comma
l_int|0x0000000b
comma
l_int|0x0000000d
comma
l_int|0x0000001d
comma
l_int|0x0000001f
comma
l_int|0x0000002c
comma
l_int|0x0000002e
comma
l_int|0x0000003b
comma
l_int|0x00000042
comma
l_int|0x00000054
comma
l_int|0x00000058
comma
l_int|0x0000005c
comma
l_int|0x00000060
comma
l_int|0x00000064
comma
l_int|0x00000068
comma
l_int|0x0000006a
comma
l_int|0x0000006e
comma
l_int|0x0000007b
comma
l_int|0x00000082
comma
l_int|0x00000086
comma
l_int|0x00000088
comma
l_int|0x00000090
comma
l_int|0x00000094
comma
l_int|0x00000096
comma
l_int|0x00000098
comma
l_int|0x0000009a
comma
l_int|0x0000009c
comma
l_int|0x000000a9
comma
l_int|0x000000ae
comma
l_int|0x000000b2
comma
l_int|0x000000bf
comma
l_int|0x000000c4
comma
l_int|0x000000ca
comma
l_int|0x000000d2
comma
l_int|0x000000d4
comma
l_int|0x000000d8
comma
l_int|0x000000da
comma
l_int|0x000000dc
comma
l_int|0x000000de
comma
l_int|0x000000e0
comma
l_int|0x000000e6
comma
l_int|0x000000e8
comma
l_int|0x00000105
comma
l_int|0x00000111
comma
l_int|0x00000113
comma
l_int|0x00000115
comma
l_int|0x0000011b
comma
l_int|0x00000127
comma
l_int|0x00000153
comma
l_int|0x00000159
comma
l_int|0x00000167
comma
l_int|0x0000016a
comma
l_int|0x0000016e
comma
l_int|0x00000172
comma
l_int|0x00000176
comma
l_int|0x0000017a
comma
l_int|0x00000191
comma
l_int|0x000001a2
comma
l_int|0x000001a4
comma
l_int|0x000001a8
comma
l_int|0x000001ac
comma
l_int|0x000001b5
comma
l_int|0x000001b7
comma
l_int|0x000001d3
comma
l_int|0x000001d7
comma
l_int|0x000001db
comma
l_int|0x000001df
comma
l_int|0x000001e3
comma
l_int|0x000001e7
comma
)brace
suffix:semicolon
DECL|variable|INSTRUCTIONS
r_int
r_int
id|INSTRUCTIONS
op_assign
l_int|0x000000fe
suffix:semicolon
DECL|variable|PATCHES
r_int
r_int
id|PATCHES
op_assign
l_int|0x00000045
suffix:semicolon
eof
