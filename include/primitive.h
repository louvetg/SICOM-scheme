#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "object.h"
#include "eval.h"

#define NB_PRIM 1

void init_tab_prim(char tab_form[NB_PRIM][STRLEN]);
void init_add_tab_prim(adress tab_add_form[NB_PRIM]);

object* moins (object* o);
object* plus (object* o);
object* produit (object* o);
object* quotient (object* o);
object* remainder (object* o);
object* egal (object* o);
object* inferio (object* o);
object* superio (object* o);
object* fabs (object* o);
object* isnull (object* o);
object* isboolean (object* o);
object* issymbol (object* o);
object* isinteger (object* o);
object* ischar (object* o);
object* isstring (object* o);	
object* ispair (object* o);
object* cons (object* o);	
object* car (object* o);
object* cdr (object* o);
object* setcar (object* o);	
object* setcdr (object* o);	
object* list (object* o);	
object* iseq (object* o);	
object* char2integer (object* o);	
object* integer2char (object* o);	
object* number2string (object* o);	
object* string2number (object* o);
object* symbol2string (object* o);	
object* string2symbol (object* o);



#ifdef __cplusplus
}
#endif

#endif /* _PRIMITIVE_H_ */
