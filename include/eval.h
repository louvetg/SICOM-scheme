
/**
 * @file eval.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:10:38 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#ifndef _EVAL_H_
#define _EVAL_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "object.h"

object* eval_prim(object* o);
object* car(object * o);
object* cdr(object * o);
uint test_auto_eval(object* o);
object* test_symb(object* o);
uint test_primitive(object* o);
object* sfs_eval(object * o, object* evmt);
void ajout_tete(object* , object** );
object* supr_tete(object**);
void ajout_tete_env(object* o, object* env);
object* all_symb(object* o, object* tst_form);

#ifdef __cplusplus
}
#endif

#endif /* _EVAL_H_ */
