
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
	if (o == obj_empty_list){ return SFS_NIL; }
	return 0xFF;
}

object* test_symb(object* o){
	DEBUG_MSG("Test forme -- ");
	if (o->type != SFS_SYMBOL){ return NULL; }
	DEBUG_MSG("L'objet est de type symbole");

	int cond = 1;
	object* m;
	object* s;
	object* obj = obj_current;

	
	do{
		m = car(obj);
		cond = 1;
		DEBUG_MSG("Environnement d'adresse: %p", obj);
		if(m != obj_empty_list){
			do{
				if (car(car(m))->type == SFS_SYMBOL){
					DEBUG_MSG("Symbole stocké en mémoire: %s",car(car(m))->this.symbol);
					if (strcmp(car(car(m))->this.symbol, o->this.symbol) == 0){
						s = car(m);
						goto fin;
					}
				}
				else{
					DEBUG_MSG("L'element stocke n'est pas de type symbole ");
				}
				if (cdr(m) == obj_empty_list && cond == 1){
					cond = 0;
				}
				m = cdr(m);


			} while (cond);
		}
		obj = cdr(obj);
	}while(obj != obj_empty_list);

	return NULL;

fin:	return s;
}

/**
*@fn object* forme(object* o, uint tst_form, object* obj_meta)
*
*@brief Lien à travers un switch entre les adresses les fonction C des formes.
*
*@param object* o pointeur vers un objet de type pair dont le car est une forme connu.
*@param uint tst_form entier contenant "l'adresse" de la forme.
*@param object* obj_meta pointeur vers un objet dont le cdr.
*/

object* all_symb(object* o, object* tst_form){
	object* obj;
	switch (tst_form->type){
	case SFS_ADRESS_FORME:
		return (*(tst_form->this.fct))(o);
		break;
	case SFS_ADRESS_PRIM:
		obj = eval_prim(cdr(o));
		if(obj == NULL ){return NULL;}
		return (*tst_form->this.fct)(obj);
		break;
	default:
		printf("Forme inconnue erreur\n");
		return NULL;
		break;
	}
}


void ajout_tete_env(object* o, object* env){
	object* obj = make_object();
	obj->type = SFS_PAIR;
	obj->this.pair.cdr = env->this.pair.car;
	obj->this.pair.car = o;
	env->this.pair.car = obj;
}

object* eval_prim(object* o){
	if (o->type == SFS_PAIR){
		object* obj_pair = make_object();
		obj_pair->type = SFS_PAIR;
		obj_pair->this.pair.car = sfs_eval(car(o),obj_current);
		if(obj_pair->this.pair.car == NULL){return NULL;}
		obj_pair->this.pair.cdr = eval_prim(cdr(o));
		if(obj_pair->this.pair.cdr == NULL){return NULL;}
		return obj_pair;
	}
	if (test_auto_eval(o)){ return o; }
	if (o == obj_empty_list){ return o; }
	return NULL; /*erreur*/
}

object* eval_compound(object* input){
	object* body = car(input)->this.compound.body;
	object* envt = car(input)->this.compound.envt;
	object* param = car(input)->this.compound.param;
	
	object* p_current_param = cdr(input);
	while(p_current_param == obj_empty_list){
		
	}
	sfs_eval(body,envt);	
}


object* sfs_eval(object * input, object * evmt){
	object * mem_evmt = obj_current;
	obj_current = evmt;
	object* obj = input;
	uint atm = 1;


	uint tst_auto = test_auto_eval(obj);
		if (tst_auto != 0xFF){
			obj_current = mem_evmt;
			return input;
		}
	
	if (obj->type == SFS_PAIR){	
		if(car(obj)-> type ==SFS_PAIR){
			obj = sfs_eval(car(obj),obj_current);
			if(obj == NULL){return NULL ; }
			atm = 0;
					
		}
		else{
			obj = car(obj);
			atm = 0;
		}
	}

	if( obj->type == SFS_COMPOUND ){
		return eval_compound(input);
	}
	object*  tst_symb = test_symb(obj);
	if (tst_symb == NULL){
		if(atm){
			WARNING_MSG("%s, n'est pas stocké en mémoire", obj->this.symbol);
			obj_current = mem_evmt;
			return NULL;
		}
		else{WARNING_MSG("Car de la liste n'est pas une fonction");}
		obj_current = mem_evmt;
		return NULL;
	}
	if (cdr(tst_symb)->type == SFS_ADRESS_PRIM || cdr(tst_symb)->type == SFS_ADRESS_FORME){
		if(atm){
			WARNING_MSG("Expression invalide pour %s", obj->this.symbol);
			obj_current = mem_evmt;
			return NULL;
		}
		object* result = all_symb(input, cdr(tst_symb));
		obj_current = mem_evmt; 
		return result; 			
	}
	else{ 
		object* result = cdr(tst_symb);
		obj_current = mem_evmt;
		return result;
	}

}
