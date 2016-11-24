
/**
 * @file mem.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:06:23 2012
 * @brief Memory wrappers for malloc/free.
 *
 * Memory wrappers for malloc/free.
 */

#include "mem.h"




void *sfs_malloc( size_t size ) {

    return malloc( size );
}

void  sfs_free( void *ptr ) {

    free( ptr );
}

object * init_meta_environnement(){
	obj_meta = make_object();
	obj_meta->type = SFS_PAIR;
	obj_meta->this.pair.car = obj_empty_list;
	obj_meta->this.pair.cdr = obj_empty_list;
	return obj_meta;
}

object * init_curr_environnement(){
	obj_meta = make_object();
	obj_meta->type = SFS_PAIR;
	obj_meta->this.pair.car = obj_empty_list;
	obj_meta->this.pair.cdr = obj_meta;
	return obj_meta;
}

object * init_meta_env(char tab_form[NB_FORM][STRLEN], object* obj_meta, object* (*forme[NB_FORM])(object*), char tab_prim[NB_PRIM][STRLEN], object* (*prim[NB_PRIM])(object*)){
	uint k = NB_FORM;
	uint j = NB_PRIM;
	uint i;
	object** list_pair_symb;
	object** symb;
	object** pair_symb;
	object** add;

	symb = calloc(k+j, sizeof(object*));
	for (i = 0; i < k+j; i++){ 
		symb[i] = calloc(1, sizeof(object*));
		symb[i]->type = SFS_SYMBOL; 
	}

	add = calloc(k+j, sizeof(object*));
	for (i = 0; i < k+j; i++){ 
		add[i] = calloc(1, sizeof(object*));
	}

	list_pair_symb  = calloc(k+j, sizeof(object*));
	for (i = 0; i < k+j; i++){ list_pair_symb[i] = calloc(1, sizeof(object*)); }

	pair_symb = calloc(k+j, sizeof(object*));
	for (i = 0; i < k+j; i++){ pair_symb[i] = calloc(1, sizeof(object*)); }

	for (i = 0; i < k; i++){
		

		symb[i]->type = SFS_SYMBOL;
		strcpy(symb[i]->this.symbol, tab_form[i]);

		add[i]->type = SFS_ADRESS_FORME;
		add[i]->this.fct = forme[i]; /* soucis de mémoire - diagnostique valgrind - à essayer de traiter */


		pair_symb[i]->type = SFS_PAIR;
		pair_symb[i]->this.pair.car = symb[i]; /* soucis de mémoire - diagnostique valgrind - à essayer de traiter */	
		pair_symb[i]->this.pair.cdr = add[i]; /* soucis de mémoire - diagnostique valgrind - à essayer de traiter */

		DEBUG_MSG("%d_Creation memoire de %s ayant pour adresse %p\n", i, pair_symb[i]->this.pair.car->this.symbol, pair_symb[i]->this.pair.cdr);

		list_pair_symb[i]->type = SFS_PAIR;
		list_pair_symb[i]->this.pair.car = pair_symb[i]; /* soucis de mémoire - diagnostique valgrind - à essayer de traiter */
		list_pair_symb[i]->this.pair.cdr = obj_empty_list; /* soucis de mémoire - diagnostique valgrind - à essayer de traiter */
		if (i > 0){ list_pair_symb[i - 1]->this.pair.cdr = list_pair_symb[i]; }
		else { obj_meta->this.pair.car = list_pair_symb[i]; }
	}

	for (i = k; i < k+j; i++){


		symb[i]->type = SFS_SYMBOL;
		strcpy(symb[i]->this.symbol, tab_prim[i-k]);

		add[i]->type = SFS_ADRESS_PRIM;
		add[i]->this.fct = prim[i-k]; /* soucis de mémoire - diagnostique valgrind - à essayer de traiter */


		pair_symb[i]->type = SFS_PAIR;
		pair_symb[i]->this.pair.car = symb[i]; /* soucis de mémoire - diagnostique valgrind - à essayer de traiter */
		pair_symb[i]->this.pair.cdr = add[i]; /* soucis de mémoire - diagnostique valgrind - à essayer de traiter */

		DEBUG_MSG("%d_Creation memoire de %s ayant pour adresse %p\n", i, pair_symb[i]->this.pair.car->this.symbol, pair_symb[i]->this.pair.cdr);

		list_pair_symb[i]->type = SFS_PAIR;
		list_pair_symb[i]->this.pair.car = pair_symb[i]; /* soucis de mémoire - diagnostique valgrind - à essayer de traiter */
		list_pair_symb[i]->this.pair.cdr = obj_empty_list; /* soucis de mémoire - diagnostique valgrind - à essayer de traiter */
		if (i > 0){ list_pair_symb[i - 1]->this.pair.cdr = list_pair_symb[i]; }
		else { obj_meta->this.pair.car = list_pair_symb[i]; }
	}
	return obj_meta;
}

