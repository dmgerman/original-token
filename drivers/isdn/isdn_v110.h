multiline_comment|/* $Id: isdn_v110.h,v 1.1 1998/02/20 17:32:11 fritz Exp $&n;&n; * Linux ISDN subsystem, V.110 related functions (linklevel).&n; *&n; * Copyright by Thomas Pfeiffer (pfeiffer@pds.de)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * $Log: isdn_v110.h,v $&n; * Revision 1.1  1998/02/20 17:32:11  fritz&n; * First checkin (not yet completely functionable).&n; *&n; */
macro_line|#ifndef _isdn_v110_h_
DECL|macro|_isdn_v110_h_
mdefine_line|#define _isdn_v110_h_
multiline_comment|/* isdn_v110_encode erh&#xfffd;lt len Nettodaten in buf, kodiert diese und liefert&n;   das Ergebnis wieder in buf. Wieviele Bytes kodiert wurden wird als&n;   return zur&#xfffd;ck gegeben. Diese Daten k&#xfffd;nnen dann 1:1 auf die Leitung&n;   gegeben werden.&n;*/
r_extern
r_struct
id|sk_buff
op_star
id|isdn_v110_encode
c_func
(paren
id|isdn_v110_stream
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
multiline_comment|/* isdn_v110_decode erh&#xfffd;lt vom input stream V110 kodierte Daten, die zu den&n;   V110 frames zusammengepackt werden m&#xfffd;ssen. Die Daten k&#xfffd;nnen an diese&n;   Schnittstelle so &#xfffd;bergeben werden, wie sie von der Leitung kommen, ohne&n;   darauf achten zu m&#xfffd;ssen, das frames usw. eingehalten werden.&n; */
r_extern
r_struct
id|sk_buff
op_star
id|isdn_v110_decode
c_func
(paren
id|isdn_v110_stream
op_star
comma
r_struct
id|sk_buff
op_star
)paren
suffix:semicolon
r_extern
r_int
id|isdn_v110_stat_callback
c_func
(paren
r_int
comma
id|isdn_ctrl
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
