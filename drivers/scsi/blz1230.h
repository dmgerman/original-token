multiline_comment|/* blz1230.h: Defines and structures for the Blizzard 1230 SCSI IV driver.&n; *&n; * Copyright (C) 1996 Jesper Skov (jskov@cygnus.co.uk)&n; *&n; * This file is based on cyber_esp.h (hence the occasional reference to&n; * CyberStorm).&n; */
macro_line|#include &quot;NCR53C9x.h&quot;
macro_line|#ifndef BLZ1230_H
DECL|macro|BLZ1230_H
mdefine_line|#define BLZ1230_H
multiline_comment|/* The controller registers can be found in the Z2 config area at these&n; * offsets:&n; */
DECL|macro|BLZ1230_ESP_ADDR
mdefine_line|#define BLZ1230_ESP_ADDR 0x8000
DECL|macro|BLZ1230_DMA_ADDR
mdefine_line|#define BLZ1230_DMA_ADDR 0x10000
DECL|macro|BLZ1230II_ESP_ADDR
mdefine_line|#define BLZ1230II_ESP_ADDR 0x10000
DECL|macro|BLZ1230II_DMA_ADDR
mdefine_line|#define BLZ1230II_DMA_ADDR 0x10021
multiline_comment|/* The Blizzard 1230 DMA interface&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; * Only two things can be programmed in the Blizzard DMA:&n; *  1) The data direction is controlled by the status of bit 31 (1 = write)&n; *  2) The source/dest address (word aligned, shifted one right) in bits 30-0&n; *&n; * Program DMA by first latching the highest byte of the address/direction&n; * (i.e. bits 31-24 of the long word constructed as described in steps 1+2&n; * above). Then write each byte of the address/direction (starting with the&n; * top byte, working down) to the DMA address register.&n; *&n; * Figure out interrupt status by reading the ESP status byte.&n; */
DECL|struct|blz1230_dma_registers
r_struct
id|blz1230_dma_registers
(brace
DECL|member|dma_addr
r_volatile
r_int
r_char
id|dma_addr
suffix:semicolon
multiline_comment|/* DMA address      [0x0000] */
DECL|member|dmapad2
r_int
r_char
id|dmapad2
(braket
l_int|0x7fff
)braket
suffix:semicolon
DECL|member|dma_latch
r_volatile
r_int
r_char
id|dma_latch
suffix:semicolon
multiline_comment|/* DMA latch        [0x8000] */
)brace
suffix:semicolon
DECL|struct|blz1230II_dma_registers
r_struct
id|blz1230II_dma_registers
(brace
DECL|member|dma_addr
r_volatile
r_int
r_char
id|dma_addr
suffix:semicolon
multiline_comment|/* DMA address      [0x0000] */
DECL|member|dmapad2
r_int
r_char
id|dmapad2
(braket
l_int|0xf
)braket
suffix:semicolon
DECL|member|dma_latch
r_volatile
r_int
r_char
id|dma_latch
suffix:semicolon
multiline_comment|/* DMA latch        [0x0010] */
)brace
suffix:semicolon
DECL|macro|BLZ1230_DMA_WRITE
mdefine_line|#define BLZ1230_DMA_WRITE 0x80000000
r_extern
r_int
id|blz1230_esp_detect
c_func
(paren
r_struct
id|SHT
op_star
)paren
suffix:semicolon
r_extern
r_const
r_char
op_star
id|esp_info
c_func
(paren
r_struct
id|Scsi_Host
op_star
)paren
suffix:semicolon
r_extern
r_int
id|esp_queue
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_void
(paren
op_star
id|done
)paren
(paren
id|Scsi_Cmnd
op_star
)paren
)paren
suffix:semicolon
r_extern
r_int
id|esp_command
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|esp_abort
c_func
(paren
id|Scsi_Cmnd
op_star
)paren
suffix:semicolon
r_extern
r_int
id|esp_reset
c_func
(paren
id|Scsi_Cmnd
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|esp_proc_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|hostno
comma
r_int
id|inout
)paren
suffix:semicolon
DECL|macro|SCSI_BLZ1230
mdefine_line|#define SCSI_BLZ1230      { proc_dir:&t;&t;&amp;proc_scsi_esp, &bslash;&n;&t;&t;&t;    name:&t;&t;&quot;Blizzard1230 SCSI IV&quot;, &bslash;&n;&t;&t;&t;    detect:&t;&t;blz1230_esp_detect, &bslash;&n;&t;&t;&t;    release:&t;&t;NULL, &bslash;&n;&t;&t;&t;    queuecommand:&t;esp_queue, &bslash;&n;&t;&t;&t;    abort:&t;&t;esp_abort, &bslash;&n;&t;&t;&t;    reset:&t;&t;esp_reset, &bslash;&n;&t;&t;&t;    can_queue:          7, &bslash;&n;&t;&t;&t;    this_id:&t;&t;7, &bslash;&n;&t;&t;&t;    sg_tablesize:&t;SG_ALL, &bslash;&n;&t;&t;&t;    cmd_per_lun:&t;1, &bslash;&n;&t;&t;&t;    use_clustering:&t;DISABLE_CLUSTERING }
macro_line|#endif /* BLZ1230_H */
eof