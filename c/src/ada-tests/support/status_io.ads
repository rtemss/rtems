--
--  Status_IO / Specification
--
--  DESCRIPTION:
--
--  This package instantiates the IO routines necessary to 
--  perform IO on data of the type Status.CODES.
--
--  DEPENDENCIES: 
--
--  
--
--  COPYRIGHT (c) 1989-1997.
--  On-Line Applications Research Corporation (OAR).
--
--  The license and distribution terms for this file may in
--  the file LICENSE in this distribution or at
--  http://www.rtems.com/license/LICENSE.
--
--  $Id: status_io.ads,v 1.4 2003/09/04 18:50:40 joel Exp $
--

with RTEMS;
with Text_IO;

package Status_IO is new Text_IO.Enumeration_IO( RTEMS.Status_Codes );

