
/**
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include "eval.h"


object* car(object * o){
	return o->this.pair.car;
}

object* cdr(object * o){
	return o->this.pair.cdr;
}

uint test_auto_eval(object* o){
	if (o->type == SFS_NUMBER){ return SFS_NUMBER; }
	if (o->type == SFS_BOOLEAN){ return SFS_BOOLEAN; }
	if (o->type == SFS_STRING){ return SFS_STRING; }
	if (o->type == SFS_CHARACTER){ return SFS_CHARACTER; }
	if (o->type == SFS_UNDEF){ return SFS_UNDEF; }
	return 0xFF;
}

object* test_symb(object* o){
	DEBUG_MSG("Test forme -- ");
	if (o->type != SFS_SYMBOL){ return NULL; }
	DEBUG_MSG("L'objet est de type symbole");

	uint k = 0;
	uint end = 0;
	int cond = 1;
	object* m;
	object* s;

	m = car(obj_meta);

	do{
		if (car(car(m))->type == SFS_SYMBOL){
		DEBUG_MSG("Symbole stocké en mémoire: %s ",car(car(m))->this.symbol);
			if (strcmp(car(car(m))->this.symbol, o->this.symbol) == 0){
				cond = 0;
				s = car(m);
			}
		}
		else{
			DEBUG_MSG("L'element stocke n'est pas de type symbole ");
		}
		if (cdr(m) == obj_empty_list && cond == 1){
			cond = 0;
			end = 1;
		}
		m = cdr(m);


	} while (cond);

	if (end){ return NULL; }

	return s;
}

uint test_primitive(object* o){
	return 0xFF;
}



void ajout_tete(object* cdr, object** p_stack_cdr){/*servait dans une première ebauche de eval*/
	object* o = make_object();
	o->type = SFS_PAIR;
	o->this.pair.cdr = *(p_stack_cdr);
	o->this.pair.car = cdr;
	*(p_stack_cdr) = o;
	return;
}

object* supr_tete(object** p_stack_cdr){/*servait dans une première ebauche de eval*/
	object* o = (*p_stack_cdr)->this.pair.car;
	object* f = *p_stack_cdr;
	*p_stack_cdr = (*p_stack_cdr)->this.pair.cdr;
	free(f);
	return o;
}



void ajout_tete_env(object* o, object* env){
	object* obj = make_object();
	obj->type = SFS_PAIR;
	obj->this.pair.cdr = env->this.pair.car;
	obj->this.pair.car = o;
	env->this.pair.car = obj;
}


object* sfs_eval(object * input){

	object* obj = input;
	uint atm = 1;


	uint tst_auto = test_auto_eval(obj);
		if (tst_auto != 0xFF){
			return input;
		}
	
	if (obj->type == SFS_PAIR){
			obj = car(obj);
			atm = 0;
		}

	object*  tst_symb = test_symb(obj);
	if (tst_symb == NULL){
		if(atm){
			WARNING_MSG("%s, n'est pas stocké en mémoire", obj->this.symbol);
			return NULL;
		}
		else{WARNING_MSG("Car de la liste n'est pas une fonction");}
		return NULL;
	}
	if (cdr(tst_symb)->type == SFS_ADRESS){
		if(atm){
			WARNING_MSG("Expression invalide pour %s", obj->this.symbol);
			return NULL;
		}
		return forme(input, cdr(tst_symb)->this.adress, obj_meta);			
	}
	else{ 
		return obj_cpy(cdr(tst_symb));
	}

}
