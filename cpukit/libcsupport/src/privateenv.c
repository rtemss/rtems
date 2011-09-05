/*
 *  Instantiate a private user environment for the calling thread.
 *
 *  Submitted by: fernando.ruiz@ctv.es (correo@fernando-ruiz.com)
 *
 *  COPYRIGHT (c) 1989-2010.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id: privateenv.c,v 1.17 2010/09/08 07:31:28 sh Exp $
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h> /* free */

#include <rtems.h>
#include <rtems/chain.h>
#include <rtems/libio_.h>

/* cleanup a user environment
 * NOTE: this must be called with
 *       thread dispatching disabled!
 */
static void
free_user_env(void *venv)
{
  rtems_user_env_t *env = (rtems_user_env_t*) venv ;

  if (env != &rtems_global_user_env
  #ifdef HAVE_USERENV_REFCNT
      && --env->refcnt <= 0
  #endif
  ) {
    rtems_filesystem_freenode( &env->current_directory);
    rtems_filesystem_freenode( &env->root_directory);
    free(env);
  }
}

rtems_status_code rtems_libio_set_private_env(void)
{
  rtems_status_code sc = RTEMS_SUCCESSFUL;
  rtems_id task_id = rtems_task_self();
  rtems_filesystem_location_info_t root_loc;
  rtems_filesystem_location_info_t current_loc;
  rtems_user_env_t *new_env = NULL;
  int rv = 0;

  rv = rtems_filesystem_evaluate_path("/", 1, 0, &root_loc, 0);
  if (rv != 0)
    goto error_0;

  rv = rtems_filesystem_evaluate_path("/", 1, 0, &current_loc, 0);
  if (rv != 0)
    goto error_1;

  /* 
   * Malloc is necessary whenever the current task does not
   * have its own environment in place. This could be:
   * a) it never had one
   * OR
   * b) it shared another task's environment
   */

  /* 
   * Bharath: I'm not sure if the check can be reduced to
   * if( rtems_current_user_env->task_id != task_id ) {
   */

  if (
    rtems_current_user_env == &rtems_global_user_env
      || rtems_current_user_env->task_id != task_id
  ) {
    new_env = malloc(sizeof(rtems_user_env_t));
    if (new_env == NULL)
      goto error_2;

    #ifdef HAVE_USERENV_REFCNT
      new_env->refcnt = 1;
    #endif

    sc = rtems_task_variable_add(
      RTEMS_SELF,
      (void*)&rtems_current_user_env,
      (void(*)(void *))free_user_env
    );
    if (sc != RTEMS_SUCCESSFUL)
      goto error_3;

    rtems_current_user_env = new_env;
  }

  /* Inherit the global values */
  *rtems_current_user_env = rtems_global_user_env;

  rtems_current_user_env->task_id = task_id;

  /*
   * Clone the pathlocs. In contrast to most other code we must _not_ free the
   * original locs because what we are trying to do here is forking off clones.
   * The reason is a pathloc can be allocated by the file system and needs to
   * be freed when deleting the environment.
   */
  rtems_filesystem_root = root_loc;
  rtems_filesystem_current = current_loc;

  return RTEMS_SUCCESSFUL;

error_3:
  free(new_env);

error_2:
  rtems_filesystem_freenode(&current_loc);

error_1:
  rtems_filesystem_freenode(&root_loc);

error_0:
  return RTEMS_NO_MEMORY;
}

/*
 *  Share the same private environment between two tasks:
 *      Task_id (remote) and RTEMS_SELF(current).
 */

/* NOTE:
 *
 * THIS CODE HAS NO PROTECTION IMPLEMENTED
 *
 * Tasks who wish to share their environments must
 *
 *  a) assert that no participants are concurrently
 *     executing
 *     libio_share_private_env() and/or libio_set_private_env()
 *
 *  b) mutex access to rtems_filesystem_current, rtems_filesytem_root
 *     while changing any of those (chdir(), chroot()).
 */

rtems_status_code rtems_libio_share_private_env(rtems_id task_id)
{
  rtems_status_code  sc;
  rtems_user_env_t * shared_user_env;
  rtems_id           current_task_id;

  /* 
   * get current task id 
   */
  current_task_id = rtems_task_self();

  /*
   * If this was an attempt to share the task with self,
   * if somebody wanted to do it... Lets tell them, its shared
   */

  if( task_id == current_task_id )
    return RTEMS_SUCCESSFUL;
  /* 
   * Try to get the requested user environment 
   */
  sc = rtems_task_variable_get(
	 task_id,
	 (void*)&rtems_current_user_env, 
	 (void*)&shared_user_env );

  /* 
   * If it was not successful, return the error code 
   */
    if (sc != RTEMS_SUCCESSFUL)
      return sc;

    /* 
     * If we are here, we have the required environment to be
     * shared with the current task
    */

    /*
     * If we have a current environment in place, we need to 
     * free it, since we will be sharing the variable with the
     * shared_user_env
     */

  if (rtems_current_user_env->task_id==current_task_id) {
    rtems_user_env_t  *tmp = rtems_current_user_env;
    free_user_env( tmp );
  }

  /* the current_user_env is the same pointer that remote env */
  rtems_current_user_env = shared_user_env;

  /* increase the reference count */
#ifdef HAVE_USERENV_REFCNT
  rtems_current_user_env->refcnt++;
#endif

  return RTEMS_SUCCESSFUL;
}
