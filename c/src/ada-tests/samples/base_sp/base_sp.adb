--
--  MAIN / BODY
--
--  DESCRIPTION:
--
--  This is the entry point for Base Single Process Example of the
--  Sample Test Suite.
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
--  $Id: base_sp.adb,v 1.4 2011/02/16 15:53:12 joel Exp $
--

with RTEMS;
with RTEMS.TASKS;
with SPTEST;
with TEST_SUPPORT;

procedure Base_SP is
  INIT_ID : RTEMS.ID;
  STATUS  : RTEMS.STATUS_CODES;
begin

   RTEMS.TASKS.CREATE(
      RTEMS.BUILD_NAME(  'I', 'N', 'I', 'T' ),
      1,
      RTEMS.MINIMUM_STACK_SIZE,
      RTEMS.NO_PREEMPT,
      RTEMS.DEFAULT_ATTRIBUTES,
      INIT_ID,
      STATUS
   );
   TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_CREATE OF INIT" );


   RTEMS.TASKS.START(
      INIT_ID,
      SPTEST.INIT'ACCESS,
      0,
      STATUS
   );
   TEST_SUPPORT.DIRECTIVE_FAILED( STATUS, "TASK_START OF INIT" );

   loop
      delay 120.0;
   end loop;

end Base_SP;
