--
--  MPTEST / SPECIFICATION
--
--  DESCRIPTION:
--
--  This package is the specification for Test 2 of the RTEMS
--  Multiprocessor Test Suite.
--
--  DEPENDENCIES: 
--
--  
--
--  COPYRIGHT (c) 1989-2011.
--  On-Line Applications Research Corporation (OAR).
--
--  The license and distribution terms for this file may in
--  the file LICENSE in this distribution or at
--  http://www.rtems.com/license/LICENSE.
--
--  $Id: mptest.ads,v 1.9 2011/02/16 15:53:11 joel Exp $
--

with RTEMS;
with RTEMS.TASKS;

package MPTEST is

--
--  These arrays contain the IDs and NAMEs of all RTEMS tasks created
--  by this test.
--

   TASK_ID   : array ( RTEMS.UNSIGNED32 range 1 .. 3 ) of RTEMS.ID;
   TASK_NAME : array ( RTEMS.UNSIGNED32 range 1 .. 3 ) of RTEMS.NAME;

--
--  INIT
--
--  DESCRIPTION:
--
--  This RTEMS task initializes the application.
--

   procedure INIT (
      ARGUMENT : in     RTEMS.TASKS.ARGUMENT
   );
   pragma Convention (C, INIT);

--
--  TEST_TASK
--
--  DESCRIPTION:
--
--  This is the body of the RTEMS tasks which constitute this test.
--

   procedure TEST_TASK (
      ARGUMENT : in     RTEMS.TASKS.ARGUMENT
   );
   pragma Convention (C, TEST_TASK);

end MPTEST;
