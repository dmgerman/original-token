multiline_comment|/*&n; * drivers/pcmcia/pci_socket.h&n; *&n; * (C) Copyright 1999 Linus Torvalds&n; */
macro_line|#ifndef __PCI_SOCKET_H
DECL|macro|__PCI_SOCKET_H
mdefine_line|#define __PCI_SOCKET_H
r_struct
id|pci_socket_ops
suffix:semicolon
r_struct
id|socket_info_t
suffix:semicolon
DECL|struct|pci_socket
r_typedef
r_struct
id|pci_socket
(brace
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
DECL|member|cb_irq
DECL|member|io_irq
r_int
id|cb_irq
comma
id|io_irq
suffix:semicolon
DECL|member|base
r_void
op_star
id|base
suffix:semicolon
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|info
r_void
op_star
id|info
suffix:semicolon
DECL|member|op
r_struct
id|pci_socket_ops
op_star
id|op
suffix:semicolon
DECL|member|cap
id|socket_cap_t
id|cap
suffix:semicolon
DECL|member|event_lock
id|spinlock_t
id|event_lock
suffix:semicolon
DECL|member|events
r_int
r_int
id|events
suffix:semicolon
DECL|member|pcmcia_socket
r_struct
id|socket_info_t
op_star
id|pcmcia_socket
suffix:semicolon
DECL|member|tq_task
r_struct
id|tq_struct
id|tq_task
suffix:semicolon
DECL|member|poll_timer
r_struct
id|timer_list
id|poll_timer
suffix:semicolon
multiline_comment|/* A few words of private data for the low-level driver.. */
DECL|member|private
r_int
r_int
r_private
(braket
l_int|8
)braket
suffix:semicolon
DECL|typedef|pci_socket_t
)brace
id|pci_socket_t
suffix:semicolon
DECL|struct|pci_socket_ops
r_struct
id|pci_socket_ops
(brace
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|pci_socket
op_star
)paren
suffix:semicolon
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
r_struct
id|pci_socket
op_star
)paren
suffix:semicolon
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|pci_socket
op_star
)paren
suffix:semicolon
DECL|member|suspend
r_int
(paren
op_star
id|suspend
)paren
(paren
r_struct
id|pci_socket
op_star
)paren
suffix:semicolon
DECL|member|get_status
r_int
(paren
op_star
id|get_status
)paren
(paren
r_struct
id|pci_socket
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
DECL|member|get_socket
r_int
(paren
op_star
id|get_socket
)paren
(paren
r_struct
id|pci_socket
op_star
comma
id|socket_state_t
op_star
)paren
suffix:semicolon
DECL|member|set_socket
r_int
(paren
op_star
id|set_socket
)paren
(paren
r_struct
id|pci_socket
op_star
comma
id|socket_state_t
op_star
)paren
suffix:semicolon
DECL|member|get_io_map
r_int
(paren
op_star
id|get_io_map
)paren
(paren
r_struct
id|pci_socket
op_star
comma
r_struct
id|pccard_io_map
op_star
)paren
suffix:semicolon
DECL|member|set_io_map
r_int
(paren
op_star
id|set_io_map
)paren
(paren
r_struct
id|pci_socket
op_star
comma
r_struct
id|pccard_io_map
op_star
)paren
suffix:semicolon
DECL|member|get_mem_map
r_int
(paren
op_star
id|get_mem_map
)paren
(paren
r_struct
id|pci_socket
op_star
comma
r_struct
id|pccard_mem_map
op_star
)paren
suffix:semicolon
DECL|member|set_mem_map
r_int
(paren
op_star
id|set_mem_map
)paren
(paren
r_struct
id|pci_socket
op_star
comma
r_struct
id|pccard_mem_map
op_star
)paren
suffix:semicolon
DECL|member|proc_setup
r_void
(paren
op_star
id|proc_setup
)paren
(paren
r_struct
id|pci_socket
op_star
comma
r_struct
id|proc_dir_entry
op_star
id|base
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|pci_socket_ops
id|yenta_operations
suffix:semicolon
r_extern
r_struct
id|pci_socket_ops
id|ricoh_operations
suffix:semicolon
macro_line|#endif
eof
