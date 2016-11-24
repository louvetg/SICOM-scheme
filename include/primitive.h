#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "object.h"
#include "eval.h"

#define NB_PRIM 29 /* Attention bien penser à nettoyer la solution si changement */

void init_tab_prim(char tab_form[NB_PRIM][STRLEN]);
void init_add_tab_prim(object* (*prim[NB_PRIM])(object*));
object* moins (object* o);
object* plus (object* o);
object* produit(object* o);
object* quotient(object* o);
object* remainder(object* o);
object* egal(object* o);




#ifdef __cplusplus
}
#endif

#endif /* _PRIMITIVE_H_ */
