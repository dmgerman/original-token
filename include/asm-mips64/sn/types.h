multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; * Copyright (C) 1999 by Ralf Baechle&n; */
macro_line|#ifndef _ASM_SN_TYPES_H
DECL|macro|_ASM_SN_TYPES_H
mdefine_line|#define _ASM_SN_TYPES_H
macro_line|#include &lt;linux/types.h&gt;
DECL|typedef|cpuid_t
r_typedef
r_int
r_int
id|cpuid_t
suffix:semicolon
DECL|typedef|cpumask_t
r_typedef
r_int
r_int
id|cpumask_t
suffix:semicolon
DECL|typedef|cnodemask_t
r_typedef
r_int
r_int
id|cnodemask_t
suffix:semicolon
DECL|typedef|nasid_t
r_typedef
r_int
r_int
id|nasid_t
suffix:semicolon
multiline_comment|/* node id in numa-as-id space */
DECL|typedef|cnodeid_t
r_typedef
r_int
r_int
id|cnodeid_t
suffix:semicolon
multiline_comment|/* node id in compact-id space */
DECL|typedef|partid_t
r_typedef
r_int
r_char
id|partid_t
suffix:semicolon
multiline_comment|/* partition ID type */
DECL|typedef|moduleid_t
r_typedef
r_int
r_int
id|moduleid_t
suffix:semicolon
multiline_comment|/* user-visible module number type */
DECL|typedef|cmoduleid_t
r_typedef
r_int
r_int
id|cmoduleid_t
suffix:semicolon
multiline_comment|/* kernel compact module id type */
DECL|typedef|clusterid_t
r_typedef
r_int
r_char
id|clusterid_t
suffix:semicolon
multiline_comment|/* Clusterid of the cell */
DECL|typedef|pfn_t
r_typedef
r_int
r_int
id|pfn_t
suffix:semicolon
DECL|typedef|vertex_hdl_t
r_typedef
id|dev_t
id|vertex_hdl_t
suffix:semicolon
multiline_comment|/* hardware graph vertex handle */
macro_line|#endif /* _ASM_SN_TYPES_H */
eof
