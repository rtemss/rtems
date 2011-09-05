--
--  RTEMS / Specification
--
--  DESCRIPTION:
--
--  This package provides the interface to the RTEMS API.
--
--  DEPENDENCIES:
--
--  NOTES:
--    RTEMS initialization and configuration are called from
--    the BSP side, therefore should never be called from ADA.
--
--  COPYRIGHT (c) 1997-2011.
--  On-Line Applications Research Corporation (OAR).
--
--  The license and distribution terms for this file may in
--  the file LICENSE in this distribution or at
--  http://www.rtems.com/license/LICENSE.
--
--  $Id: rtems-signal.ads,v 1.1 2011/02/16 15:52:29 joel Exp $
--

package RTEMS.Signal is

   --
   --  Signal Manager
   --

   procedure Catch (
      ASR_Handler : in     RTEMS.ASR_Handler;
      Mode_Set    : in     RTEMS.Mode;
      Result      :    out RTEMS.Status_Codes
   );

   procedure Send (
      ID         : in     RTEMS.ID;
      Signal_Set : in     RTEMS.Signal_Set;
      Result     :    out RTEMS.Status_Codes
   );

end RTEMS.Signal;

