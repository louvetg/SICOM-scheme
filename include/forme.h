#ifndef _FORME_H_
#define _FORME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "object.h"
#include "eval.h"

#define NB_FORM 8 /* Attention bien penser à nettoyer la solution si changement */

void init_tab_form(char tab_form[NB_FORM][STRLEN]);
void init_add_tab_form(object* (*forme[NB_FORM])(object*));
object* quote (object* o);
object* and (object* o);
object* or (object* o);
object* define(object* o);
object* set(object* o);
object* si(object* o);
object* lambda(object* o);
object* begin(object* o);
  
#ifdef __cplusplus
}
#endif

#endif /* _FORME_H_ */
