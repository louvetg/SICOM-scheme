
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

object * init_environnement(){
	obj_meta = make_object();
	obj_meta->type = SFS_PAIR;
	obj_meta->this.pair.car = obj_empty_list;
	obj_meta->this.pair.cdr = obj_empty_list;
	return obj_meta;
}

object * init_meta_env(char tab_form[NB_FORM][STRLEN], object* obj_meta, adress tab_add_form[NB_FORM] ){
	uint k = NB_FORM;
	uint i;
	object** list_pair_forme;
	object** forme;
	object** pair_forme;
	object** num;

	forme = calloc(k, sizeof(object*));
	for (i = 0; i < k; i++){ 
		forme[i] = calloc(1, sizeof(object*));
		forme[i]->type = SFS_SYMBOL; 
	}

	num = calloc(k, sizeof(object*));
	for (i = 0; i < k; i++){ 
		num[i] = calloc(1, sizeof(object*));
		num[i]->type = SFS_ADRESS;
	}

	list_pair_forme  = calloc(k, sizeof(object*));
	for (i = 0; i < k; i++){ list_pair_forme[i] = calloc(1, sizeof(object*)); }

	pair_forme = calloc(k, sizeof(object*));
	for (i = 0; i < k; i++){ pair_forme[i] = calloc(1, sizeof(object*)); }

	for (i = 0; i < k; i++){
		
		DEBUG_MSG("%d_Contenu du tableau initial -- forme: %s, adresse: %d --",i,tab_form[i], tab_add_form[i]);
		forme[i]->type = SFS_SYMBOL;
		strcpy(forme[i]->this.symbol, tab_form[i]);

		num[i]->type = SFS_ADRESS;
		num[i]->this.adress = tab_add_form[i]; /* soucis de mémoire - diagnostique valgrind - à essayer de traiter */
		DEBUG_MSG("%d_Creation des objects -- forme: %s, adresse: %d --",i,forme[i]->this.symbol, num[i]->this.adress);

		pair_forme[i]->type = SFS_PAIR;
		pair_forme[i]->this.pair.car = forme[i]; /* soucis de mémoire - diagnostique valgrind - à essayer de traiter */	
		pair_forme[i]->this.pair.cdr = num[i]; /* soucis de mémoire - diagnostique valgrind - à essayer de traiter */

		DEBUG_MSG("%d_Creation mémoire de %s à l'adresse %d",i, pair_forme[i]->this.pair.car->this.symbol, pair_forme[i]->this.pair.cdr->this.adress);   

		list_pair_forme[i]->type = SFS_PAIR;
		list_pair_forme[i]->this.pair.car = pair_forme[i]; /* soucis de mémoire - diagnostique valgrind - à essayer de traiter */
		list_pair_forme[i]->this.pair.cdr = obj_empty_list; /* soucis de mémoire - diagnostique valgrind - à essayer de traiter */
		if (i > 0){ list_pair_forme[i - 1]->this.pair.cdr = list_pair_forme[i]; }
		else { obj_meta->this.pair.car = list_pair_forme[i]; }
	}
	return obj_meta;
}

