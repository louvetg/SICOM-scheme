#ifndef _FORME_H_
#define _FORME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "object.h"
#include "eval.h"

#define NB_FORM 7

#define QUOTE 0x01
#define SET 0x02
#define DEFINE 0x03
#define AND 0x04
#define OR 0x05
#define IF 0x06
#define BEGIN 0x07

void init_tab_form(char tab_form[NB_FORM][STRLEN]);
void init_num_tab_form(uint num_tab_form[NB_FORM]);
object* forme(object* o, uint tst_form, object* obj_meta);
object* quote (object* o);
object* and (object* o);
object* or (object* o);
object* define(object* o, object* obj_meta);
object* set(object* o, object* obj_meta);
object* si(object* o);
object* isbegin(object* o);
  
#ifdef __cplusplus
}
#endif

#endif /* _FORME_H_ */
