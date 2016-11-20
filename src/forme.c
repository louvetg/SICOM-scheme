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
}

/**
*@fn void init_tab_form(char tab_form[NB_FORM][STRLEN])
*
*@brief Rempli un tableau contenant les "adresse" des différentes formes qui seront intégrées à l'environnement meta.
*Les adresses sont des entiers qui seront utiliser dans le switch contenant les fonction C.
*
*@param uint num_tab_form[NB_FORM]) tableau allant contenir les "adresse" des formes.
*/

void init_add_tab_form(adress tab_add_form[NB_FORM]){
	tab_add_form[0].addtype = ADD_FORME;
	tab_add_form[0].this.forme = *quote;
	tab_add_form[1].addtype = ADD_MEM_FORME;
	tab_add_form[1].this.forme = *set;
	tab_add_form[2].addtype = ADD_MEM_FORME;
	tab_add_form[2].this.forme = *define;
	tab_add_form[3].addtype = ADD_FORME;
	tab_add_form[3].this.forme = *and;
	tab_add_form[4].addtype = ADD_FORME;
	tab_add_form[4].this.forme = *or;
	tab_add_form[5].addtype = ADD_FORME;
	tab_add_form[5].this.forme = *si;
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

object* forme(object* o, adress tst_form, object* obj_meta){
	switch(tst_form.addtype){
	case  ADD_FORME:
		return (*tst_form.this.forme)(o);
		break;
	case ADD_MEM_FORME:
		return (*tst_form.this.mem_forme)(o,obj_meta);
		break;
	default:
		printf("Forme inconnue erreur\n");
		return NULL;
		break;
	}
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

object* define(object* o, object* obj_meta){

	object* obj_car = make_object();
	obj_car->type = SFS_SYMBOL;
	strcpy(obj_car->this.symbol, o->this.pair.cdr->this.pair.car->this.symbol) ;

	object* obj_cdr = make_object();
	obj_cdr = obj_cpy(car(cdr(cdr(o))));
	obj_cdr = sfs_eval(obj_cdr);

	if (obj_cdr == NULL){	
		return NULL;}
	
	if (cdr(cdr(cdr(o))) != obj_empty_list){ return NULL;/*erreur*/ }

	object* obj_pair = make_object();
	obj_pair->type = SFS_PAIR;
	obj_pair->this.pair.car = obj_car;
	obj_pair->this.pair.cdr = obj_cdr;
	ajout_tete_env(obj_pair, obj_meta);

return obj_undef;
}


object* set(object* o, object* obj_meta){
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
	if (cdr(obj)->type == SFS_ADRESS){
		WARNING_MSG("Ecriture impossible, %s de l'environnement meta est protégé",car(obj)->this.symbol);
		return NULL;
	}

	free(obj->this.pair.cdr);
	object* val = make_object();
	val->type = sfs_eval(car(cdr(cdr(o))))->type;
	val->this = sfs_eval(car(cdr(cdr(o))))->this;
	obj->this.pair.cdr = val;
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
		object* p = make_object();
		p->type = car(cdr(o))->type;
		p->this = car(cdr(o))->this;
		return p;
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
		object* a = sfs_eval(obj_pair_pred->this.pair.car);
		
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
		object* a = sfs_eval(obj_pair_pred->this.pair.car);

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

object* si(object* o){
	if (cdr(o) == obj_empty_list){ goto erreur_si; }
	object* test = sfs_eval(car(cdr(o)));

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
	

	if (test == obj_false){return sfs_eval(alternate);}
	return sfs_eval(consequent);
	
erreur_si:
	WARNING_MSG("if erreur de syntaxe. Synthaxe (if <expression> <tail expression> <tail expression>) ou (if <expression> <tail expression>)");/*Réel syntaxe (and <and>*) à voir pour remplacer*/
	return NULL; 

}
