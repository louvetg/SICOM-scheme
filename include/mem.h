
/**
 * @file mem.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:04:52 2012
 * @brief Memory wrappers for malloc/free.
 *
 * Memory wrappers for malloc/free.
 */

#ifndef _MEM_H_
#define _MEM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "object.h"
#include "forme.h"



void *sfs_malloc( size_t size );
void  sfs_free( void *ptr );

object * init_environnement();
object * init_meta_env(char tab_form[NB_FORM][STRLEN], object* obj_meta, adress tab_add_form[NB_FORM] );

#ifdef __cplusplus
}
#endif

#endif /* _MEM_H_ */
