#include "forme.h"


/**
*@fn void init_tab_form(char tab_form[NB_FORM][STRLEN])
*
*@brief Rempli un tableau contenant les noms des différentes formes qui seront intégrées à l'environnement meta.
*
*@param char tab_form[NB_FORM][STRLEN]) tableau allant contenir les noms de formes.
*/

void init_tab_form(char tab_form[NB_FORM][STRLEN]){
	strcpy(tab_form[0],"quote");
	strcpy(tab_form[1],"set!");
	strcpy(tab_form[2],"define");
	strcpy(tab_form[3],"and");
	strcpy(tab_form[4],"or");
	strcpy(tab_form[5],"if");
	strcpy(tab_form[6],"lambda");
	strcpy(tab_form[7],"begin");
}

/**
*@fn void init_tab_form(char tab_form[NB_FORM][STRLEN])
*
*@brief Rempli un tableau contenant les "adresse" des différentes formes qui seront intégrées à l'environnement meta.
*Les adresses sont des entiers qui seront utiliser dans le switch contenant les fonction C.
*
*@param uint num_tab_form[NB_FORM]) tableau allant contenir les "adresse" des formes.
*/

void init_add_tab_form(object* (*forme[NB_FORM])(object*)){
	forme[0] = *quote;
	forme[1] = *set;
	forme[2] = *define;
	forme[3] = *and;
	forme[4] = *or;
	forme[5] = *si;
	forme[6] = *lambda;
	forme[7] = *begin;
}


/**
*@fn object* quote(object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans quote
*/

object* define(object* o){

	object* obj_cdr = sfs_eval(car(cdr(cdr(o))),obj_current);

	if (obj_cdr == NULL){	
		return NULL;
	}
	
	if (cdr(cdr(cdr(o))) != obj_empty_list){ return NULL;/*erreur*/ }

	object* obj_pair = make_object();
	obj_pair->type = SFS_PAIR;
	obj_pair->this.pair.car = car(cdr(o));
	obj_pair->this.pair.cdr = obj_cdr;
	ajout_tete_env(obj_pair, obj_current);

return obj_undef;
}


object* set(object* o){
	object* obj = test_symb(car(cdr(o)));

	if (obj == NULL){
		WARNING_MSG("Variable inconnue ou de mauvaise forme");
		return NULL;
	}

	if(cdr(o) == obj_empty_list){
		WARNING_MSG("Expression invalide dans le set");
		return NULL;	
	}
	if(cdr(cdr(o)) == obj_empty_list){
		WARNING_MSG("Expression invalide dans le set");
		return NULL;	
	}
	if (cdr(obj)->type == SFS_ADRESS_PRIM || cdr(obj)->type == SFS_ADRESS_FORME){
		WARNING_MSG("Ecriture impossible, %s de l'environnement meta est protégé\n",car(obj)->this.symbol);
		return NULL;
	}

	obj->this.pair.cdr = sfs_eval(car(cdr(cdr(o))),obj_current);
	return obj_undef;
}

/**
*@fn object* quote(object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans quote
*/


object* quote(object* o){

	if (cdr(cdr(o)) != obj_empty_list){ 
		WARNING_MSG("quote ne prend que 1 argument. Synthaxe (quote <datum>)");
		return NULL; }
	{

	if ((car(o->this.pair.cdr))->type == SFS_PAIR ) { /* Cas d'une liste */
		o->this.pair.car = car(car(o->this.pair.cdr));
		o->this.pair.cdr = cdr(car(o->this.pair.cdr));
	}
	else{ /* Cas d'un atome */
		return car(cdr(o));
	}
	

	}
	return o;
}


/**
*@fn object* and (object* o)
*
*@brief fonction "AND"
*
*@param object* o pointeur sur la structure à évaluer
*
*@return object* o valeur évaluée: TRUE ou FALSE
*/

object* and(object* o){
	if (cdr(o) == obj_empty_list){ 
		WARNING_MSG("and prend 2 arguments. Synthaxe (and <test> <test>*)");/*Réel syntaxe (and <and>*) à voir pour remplacer*/
		return NULL; }
	object* obj_pair_pred = cdr(o);
	uint res = 1;
	uint end = 0;
	do{
		object* a = sfs_eval(obj_pair_pred->this.pair.car, obj_current);
		
		if (a == obj_false){ res = 0;}

		if (cdr(obj_pair_pred) == obj_empty_list){ 
			if (res != 0){ end = 1; }
			res = 0;
		}
		else { obj_pair_pred = cdr(obj_pair_pred); }
	} while (res);
	if (end){ return obj_true; }
	return obj_false;
}

/**
*@fn object* or (object* o)
*
*@brief fonction "OR"
*
*@param object* o pointeur sur la structure à évaluer
*
*@return object* o valeur évaluée: TRUE ou FALSE
*/

object* or(object* o){
	if (cdr(o) == obj_empty_list){ 
		WARNING_MSG("or prend 2 arguments. Synthaxe (or <test> <test>*)");/*Réel syntaxe (or <and>*) à voir pour remplacer*/
		return NULL;}
	object* obj_pair_pred = cdr(o);
	uint res = 1;
	uint end = 0;
	do{
		object* a = sfs_eval(obj_pair_pred->this.pair.car, obj_current);

		if (a != obj_false){res = 0;}

		if (cdr(obj_pair_pred) == obj_empty_list){
			if (res != 0){ end = 1; }
			res = 0;
		}
		else { obj_pair_pred = cdr(obj_pair_pred); }
	} while (res);
	if (end){ return obj_false; }
	return obj_true;
}



/**
*@fn object* si (object* o)
*
*@brief fonction "IF"
*
*@param object* o pointeur sur la structure à évaluer
*
*@return object* o consequence du predicat selectionné
*/

object* si(object* o){
	if (cdr(o) == obj_empty_list){ goto erreur_si; }
	object* test = sfs_eval(car(cdr(o)), obj_current);

	if (cdr(cdr(o)) == obj_empty_list){ goto erreur_si; }
	object* consequent = car(cdr(cdr(o)));

	object* alternate;
	if (cdr(cdr(cdr(o))) != obj_empty_list){
		alternate = car(cdr(cdr(cdr(o))));
		if (cdr(cdr(cdr(cdr(o)))) != obj_empty_list){ goto erreur_si; }
	}
	else{ alternate = obj_undef; }

	if (test == NULL){ 
		WARNING_MSG("Erreur lors de l'évaluation du test");
		return NULL; }
	

	if (test == obj_false){return sfs_eval(alternate, obj_current);}
	return sfs_eval(consequent, obj_current);
	
erreur_si:
	WARNING_MSG("if erreur de syntaxe. Synthaxe (if <expression> <tail expression> <tail expression>) ou (if <expression> <tail expression>)");/*Réel syntaxe (and <and>*) à voir pour remplacer*/
	return NULL; 

}



/**
*@fn object* lambda (object* o)
*
*@brief fonction "LAMBDA"
*
*@param object* o pointeur sur la structure à évaluer
*
*@return object* o
*/


object* lambda( object* o){
/* Vérification de la forme */

/* Creation de l'environement */
	object* env = make_object();
	env->type = SFS_PAIR;
	env->this.pair.car = obj_empty_list;
	env->this.pair.cdr = obj_current;

/* creation de l'obj comboun */
	object* obj_lambda = make_object();
	obj_lambda->type = SFS_COMPOUND;
	obj_lambda->this.compound.param = car(cdr(o));
	obj_lambda->this.compound.body = car(cdr(cdr(o)));
	obj_lambda->this.compound.envt = env;

	object* p_param = obj_lambda->this.compound.param;
	DEBUG_MSG("Environnement d'adresse: %p",obj_lambda->this.compound.envt);

	while(p_param != obj_empty_list){
		
		object* obj_pair = make_object();
		obj_pair->type = SFS_PAIR;
		obj_pair->this.pair.car = car(p_param);
		obj_pair->this.pair.cdr = obj_empty_list;
		ajout_tete_env(obj_pair, env);
		DEBUG_MSG("Création mémoire de %s à l'adresse: %p",obj_pair->this.pair.car->this.symbol, obj_pair);
		
		p_param = cdr(p_param);
	}
	return obj_lambda;	
}



/**
*@fn object* begin (object* o)
*
*@brief fonction "BEGIN"
*
*@param object* o pointeur sur la structure à évaluer
*
*@return object* o valeur évaluée: TRUE ou FALSE
*/

object* begin (object * o)
{
	if (o==obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments");
		return NULL;
	}
	while(cdr(o) != obj_empty_list)
	{
		o=cdr(o);
	}
	return o;
}
