/*
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: init.c,v 1.7 2011/02/22 09:47:34 ralf Exp $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <tmacros.h>
#include "test_support.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <rtems/libcsupport.h>

int TestFd;
uint8_t Buffer[256];
ssize_t TotalWritten;

#define FILE_NAME "biggie"

void open_it(bool readOnly, bool create)
{
  int flag = 0;

  if ( readOnly )
    flag |= O_RDONLY;
  else {
    if ( create )
      flag |= O_CREAT;
    flag |= O_RDWR;
  }

  /* open the file */
  puts( "open(" FILE_NAME ") - OK " );
  TestFd = open( FILE_NAME, flag, 0777 );
  rtems_test_assert( TestFd != -1 );
}

void write_helper(void)
{
  ssize_t written;

  TotalWritten = 0;
  puts( "write(" FILE_NAME ") - OK " );
  do {
    written = write( TestFd, Buffer, sizeof(Buffer) );
    if ( written == -1 ) {
      if ( errno == ENOSPC ) {
        printf( "Total written = %zd\n", TotalWritten );
        return;
      }
      fprintf(
        stderr,
        "Unable to create largest IMFS file (error=%s)\n",
        strerror(errno)
      );
      rtems_test_exit(0);
    }
    TotalWritten += written;
  } while (1);
  
}

void read_helper(void)
{
  uint8_t ch;
  ssize_t sc;
  int     i=0;

  puts( "read(" FILE_NAME ") - OK " );
  do {
    sc = read( TestFd, &ch, sizeof(ch) );
    if ( sc == 1 ) {
      if ( ch != (i%256) ) {
        fprintf(
          stderr,
          "MISMATCH 0x%02x != 0x%02x at offset %d\n",
          ch,
          i % 256,
          i
        );
        rtems_test_exit(0);
      }
      i++;
      continue;
    }
    /* Unsure if ENOSPC is the write error to be returned */
    if ( errno == ENOSPC && i == TotalWritten ) {
      puts( "File correctly read until ENOSPC returned\n" );
      return;
    }
    fprintf(
      stderr,
      "ERROR - at offset %d - returned %zd and error=%s\n",
      i,
      sc,
      strerror( errno )
    );
    rtems_test_exit(0);
  } while (1);
}

void truncate_helper(void)
{
  off_t position;
  off_t new;
  off_t sc;
  int   rc;

  position = lseek( TestFd, 0, SEEK_END );
  printf( "Seek to end .. returned %d\n", (int) position );
  rtems_test_assert( position == TotalWritten );

  puts( "lseek/ftruncate loop.." );
  new = position;
  do {
    sc = lseek( TestFd, new, SEEK_SET );
    rtems_test_assert( sc == new );

    rc = ftruncate( TestFd, new );
    if ( rc != 0 ) {
      fprintf(
	stderr,
	"ERROR - at offset %d - returned %d and error=%s\n",
	(int) new,
	rc,
	strerror( errno )
      );
    }
    rtems_test_assert( rc == 0 );
    --new;
  } while (new > 0);
}

void extend_helper(void)
{
  off_t position;
  off_t new;
  off_t sc;
  int   rc;

  position = lseek( TestFd, 0, SEEK_END );
  printf( "Seek to end .. returned %d\n", (int) position );

  /* 
   * test case to ftruncate a file to a length > its size 
   */

  rc = ftruncate( TestFd, 2 );
  rtems_test_assert( rc == 0 );

  puts( "lseek/ftruncate loop.." );
  new = position;
  do {
    sc = lseek( TestFd, new, SEEK_SET );
    if( sc == -1 ) {
      if( errno == ENOSPC ) {
	break;
      }
      else {
	rtems_test_assert( 0 );
      }
    }

    rc = ftruncate( TestFd, new );
    if ( rc != 0 ) {
      if( errno != ENOSPC ) {
	fprintf(
	  stderr,
	  "ERROR - at offset %d - returned %d and error=%s\n",
	  (int) new,
	  rc,
	  strerror( errno )
        );
	break;
      }
      else {
	break;
      }
    }
    rtems_test_assert( rc == 0 );
    ++new;
  } while ( 1 );
}

void close_it(void)
{
  int rc;

  puts( "close(" FILE_NAME ") - OK " );
  rc = close( TestFd );
  rtems_test_assert( rc == 0 );
}

void unlink_it(void)
{
  int rc;

  puts( "unlink(" FILE_NAME ") - OK" );
  rc = unlink( FILE_NAME );
  rtems_test_assert( rc == 0 );
}

rtems_task Init(
  rtems_task_argument argument
)
{
  int i;
  void *alloc_ptr = (void *)0;
  int position = 0;
  int status = 0;

  puts( "\n\n*** TEST IMFS 01 ***" );

  for (i=0 ; i<sizeof(Buffer) ; i++ )
    Buffer[i] = (uint8_t) i;

  open_it(false, true);
  write_helper();
  close_it();

  puts( "" );

  open_it(true, false);
  read_helper();
  close_it();
  
  open_it(false, false);
  truncate_helper();

  /*
   * Allocate the heap, so that extend cannot be successful
   */
  alloc_ptr = malloc( malloc_free_space() - 4 );

  extend_helper();

  /* 
   * free the allocated heap memory
   */
  free(alloc_ptr);

  extend_helper();
  position = lseek( TestFd , 0, SEEK_END );
  status = lseek( TestFd, position+2, SEEK_SET );
  rtems_test_assert( status == -1 );
  rtems_test_assert( errno == ENOSPC );

  close_it();
  unlink_it();

  puts( "*** END OF TEST IMFS 01 ***" );

  rtems_test_exit(0);
}

/* configuration information */

#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER

#define CONFIGURE_MAXIMUM_TASKS             1
#define CONFIGURE_IMFS_MEMFILE_BYTES_PER_BLOCK 16
#define CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS 4
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

#define CONFIGURE_INIT

#include <rtems/confdefs.h>
/* end of file */
