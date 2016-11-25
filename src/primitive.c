#include "primitive.h"
#include <limits.h>



/**
*@fn void init_tab_form(char tab_form[NB_FORM][STRLEN])
*
*@brief Rempli un tableau contenant les noms des différentes formes qui seront intégrées à l'environnement meta.
*
*@param char tab_form[NB_FORM][STRLEN]) tableau allant contenir les noms de formes.
*/

void init_tab_prim(char tab_form[NB_PRIM][STRLEN]){
	strcpy(tab_form[0],"-");
	strcpy(tab_form[1],"+");
	strcpy(tab_form[2], "*");
	strcpy(tab_form[3], "/");
	strcpy(tab_form[4], "remainder");
	strcpy(tab_form[5], "=");
	strcpy(tab_form[6], "pair?");
	strcpy(tab_form[7],"cons");
	strcpy(tab_form[8],"string?");
	strcpy(tab_form[9], "char?");
	strcpy(tab_form[10], "<");
	strcpy(tab_form[11], ">");
	strcpy(tab_form[12], "abs");
	strcpy(tab_form[13], "null?");
	strcpy(tab_form[14],"boolean?");
	strcpy(tab_form[15],"symbol?");
	strcpy(tab_form[16], "integer?");
	strcpy(tab_form[17], "car");
	strcpy(tab_form[18], "cdr");
	strcpy(tab_form[19], "set-car!");
	strcpy(tab_form[20], "set-cdr!");
	strcpy(tab_form[21], "list?");
	strcpy(tab_form[22], "eq?");
	strcpy(tab_form[23], "char2integer");
	strcpy(tab_form[24], "integer->char");
	strcpy(tab_form[25], "number->string");
	strcpy(tab_form[26], "string->symbol");
	strcpy(tab_form[27], "symbol->string");
	strcpy(tab_form[28], "string->number");
}

/**
*@fn void init_tab_form(char tab_form[NB_FORM][STRLEN])
*
*@brief Rempli un tableau contenant les "adresse" des différentes formes qui seront intégrées à l'environnement meta.
*Les adresses sont des entiers qui seront utiliser dans le switch contenant les fonction C.
*
*@param uint num_tab_form[NB_FORM]) tableau allant contenir les "adresse" des formes.
*/

void init_add_tab_prim(object* (*prim[NB_PRIM])(object*)){
	prim[0] = *moins;
	prim[1] = *plus;
	prim[2] = *produit;
	prim[3] = *quotient;
	prim[4] = *remainder;
	prim[5] = *egal;
	prim[6] = *ispair;
	prim[7] = *cons;
	prim[8] = *isstring;
	prim[9] = *ischar;
	prim[10] = *inferio;
	prim[11] = *superio;
	prim[12] = *fabs;
	prim[13] = *isnull;
	prim[14] = *isboolean;
	prim[15] = *issymbol;
	prim[16] = *isinteger;
	prim[17] = *fcar;
	prim[18] = *fcdr;
	prim[19] = *setcar;
	prim[20] = *setcdr;
	prim[21] = *islist;
	prim[22] = *iseq;
	prim[23] = *char2integer;
	prim[24] = *integer2char;
	prim[25] = *number2string;
	prim[26] = *string2symbol;
	prim[27] = *symbol2string;
	prim[28] = *string2number;
}



/**
*@fn object* moins (object* o)
*
*@brief Soustraction
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/

object* moins (object* o){
	if (o == obj_empty_list) 
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_sous = make_object();
	obj_sous->type = SFS_NUMBER;
	obj_sous->this.number.this.integer = 0;
	if((car(o)-> type != SFS_NUMBER) ) 
    {
         WARNING_MSG("Au moins un argument non entier");
         return NULL;
    }
	if (cdr(o) == obj_empty_list) 
	{
		obj_sous= - car(o)->this.number.this.integer;
		return obj_sous;
	}
	else
    {
       if((car(cdr(o))-> type != SFS_NUMBER) )
        {
            WARNING_MSG("Au moins un argument non entier");
            return NULL;
        }

	int x = car(cdr(o))->this.number.this.integer; int a = car(o)->this.number.this.integer;
	 if( (x < 0) && (a > INT_MAX + x) ){
		WARNING_MSG("overflow: dépasse la limite des type int" );/*(- 3 -2147483646)*/
	 }
	 if( x > 0 && a < INT_MIN + x ){
		WARNING_MSG("overflow: dépasse la limite des type int" );/*(- -2147483647 10) (- -10 2147483647) */
	 }
        obj_sous->this.number.this.integer = car(o)->this.number.this.integer - car(cdr(o))->this.number.this.integer;
        o = cdr(o);
        while (cdr(o) != obj_empty_list)
        {
            if(car(cdr(o)) != SFS_NUMBER)
            {
                WARNING_MSG("Au moins un argument non entier");
                return NULL;
            }

	    int x = car(cdr(o))->this.number.this.integer; int a = obj_sous->this.number.this.integer;

	    if( (x < 0) && (a > INT_MAX + x) ){
		WARNING_MSG("overflow: dépasse la limite des type int" );/*(- 3 -2147483646)*/
	    }
	    if( x > 0 && a < INT_MIN + x ){
		WARNING_MSG("overflow: dépasse la limite des type int" );/*(- -2147483647 10) (- -10 2147483647) */
	    }


            obj_sous->this.number.this.integer = obj_sous->this.number.this.integer - car(cdr(o))->this.number.this.integer; 
            o = cdr(o);
        }
	}
	
	return obj_sous;
}

/**
*@fn object* plus (object* o)
*
*@brief Addition
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/

object* plus (object* o){
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_somme = make_object();
	obj_somme->type = SFS_NUMBER;
	obj_somme->this.number.this.integer = 0;
	do
	{
        	if(car(o) != SFS_NUMBER)
       		 {
          	 	WARNING_MSG("Au moins un argument non entier");
            	 	return NULL;
        	 }

		int x = car(o)->this.number.this.integer; int a = obj_somme->this.number.this.integer;
		if( (x > 0) && (a > INT_MAX - x) ){
			WARNING_MSG("overflow: dépasse la limite des type int" );/*(+ 20 2147483646)*/
	 	}
		if( x < 0 && a < INT_MIN - x ){
			WARNING_MSG("overflow: dépasse la limite des type int" );/*(+ -2147483646 -40)  */
	 	}

		obj_somme->this.number.this.integer = car(o)->this.number.this.integer+ obj_somme->this.number.this.integer;
		o = cdr(o);
	}while (o != obj_empty_list);
	
	return obj_somme;
}

/**
*@fn object* produit (object* o)
*
*@brief Multiplication
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/

object* produit (object* o){
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_produit = make_object();
	obj_produit->type = SFS_NUMBER;
	obj_produit->this.number.this.integer = 1;
	do
	{
	   
		if(car(o)->type != SFS_NUMBER ){
		    	WARNING_MSG("Au moins un argument non entier");
		   	return NULL;
		}

		int x = obj_produit->this.number.this.integer; int a = car(o)->this.number.this.integer;
		if( a > INT_MAX / x ){
			WARNING_MSG("overflow: dépasse la limite des type int" );
	 	}
		if( a < INT_MIN / x){
			WARNING_MSG("overflow: dépasse la limite des type int" );
	 	}
		if( a == -1 && x == INT_MIN){
			WARNING_MSG("overflow: dépasse la limite des type int" );
		}
		if( x == -1 && a == INT_MIN){
			WARNING_MSG("overflow: dépasse la limite des type int" );
		}

		obj_produit->this.number.this.integer = car(o)->this.number.this.integer* obj_produit->this.number.this.integer;

		o = cdr(o);
	}while (o != obj_empty_list);
	
	return obj_produit;
}

/**
*@fn object* quotient (object* o)
*
*@brief Division
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/

object* quotient (object* o){
	if ((o == obj_empty_list))
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if(car(o)->this.number.this.integer = 0)
    	{
        	WARNING_MSG("Division par 0");
        	return NULL;
   	}
	object* obj_divis = make_object();
	obj_divis->type = SFS_NUMBER;
	obj_divis->this.number.this.integer = 1;
   	if((car(o)->type != SFS_NUMBER)||(car(cdr(o))->type != SFS_NUMBER))
    	{
         	WARNING_MSG("Au moins un argument non entier");
         	return NULL;
    	}
	if(cdr(o) == obj_empty_list)
	{
        	obj_divis->this.number.this.integer = obj_divis->this.number.this.integer/ car(o)->this.number.this.integer;
		return obj_divis;
	}
	else
	{
		obj_divis->this.number.this.integer = car(o)->this.number.this.integer/ car(cdr(o))->this.number.this.integer;
		o = cdr(o);
		while (cdr(o) != obj_empty_list)
		{
			
			if(obj_divis->this.number.this.integer  == 0)
			{
				WARNING_MSG("Division par 0"); 
				return NULL;
			}
			if(car(o) != SFS_NUMBER)
            		{
               			 WARNING_MSG("Au moins un argument non entier");
                		 return NULL;
            		}
			obj_divis->this.number.this.integer =obj_divis->this.number.this.integer /  car(o)->this.number.this.integer;
			o = cdr(o);
		}
	}
	
	return obj_divis;
}

/**
*@fn object* remainder (object* o)
*
*@brief Renvoi le reste d'une division
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/


object* remainder (object* o){
	object* obj_reste = make_object();
	obj_reste->type = SFS_NUMBER;
	obj_reste->this.number.this.integer = 1;
	if ((o == obj_empty_list) || ( cdr(o) == obj_empty_list))
	{
		WARNING_MSG("Pas assez d'arguments - min 2");
		return NULL;
	}
	if (cdr(cdr(o))!= obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	if((car(o)->type != SFS_NUMBER) || (car(cdr(o))->type != SFS_NUMBER))
	{
        	WARNING_MSG("Au moins un argument non entier");
        	return NULL;
	}

	obj_reste->this.number.this.integer = car(o)->this.number.this.integer % car(cdr(o))->this.number.this.integer;
	
	return obj_reste;
}


/**
*@fn object* egal (object* o)
*
*@brief Evalue l'égalité
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/

object* egal (object* o){
	if ((o == obj_empty_list) || ( cdr(o) == obj_empty_list))
	{
		WARNING_MSG("Pas assez d'arguments - min 2");
		return NULL;
	}
	object* obj_res = make_object();
	do
	{
        if((car(o)->type != SFS_NUMBER)||(car(cdr(o))->type != SFS_NUMBER))
        {
            WARNING_MSG("Au moins un argument non entier");
            return NULL;
        }
		if (car(o)->this.number.this.integer == car(cdr(o))->this.number.this.integer)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res=obj_false;
			return obj_res;
		}
	}while (cdr(o) != obj_empty_list);
	
	return obj_res;
}

/**
*@fn object* inferio (object* o)
*
*@brief Evalue l'infériorité
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/

object* inferio (object* o){
	if ((o == obj_empty_list) || ( cdr(o) == obj_empty_list))
	{
		WARNING_MSG("Pas assez d'arguments - min 2");
		return NULL;
	}
	object* obj_res = make_object();
	obj_res->type = SFS_NUMBER;
	object* obj_res_prec = make_object();
	obj_res_prec->type = SFS_NUMBER;
	do
	{
		if((car(o)->type != SFS_NUMBER)|| (car(cdr(o))->type != SFS_NUMBER))
        	{
           	 WARNING_MSG("Au moins un argument non entier");
            	return NULL;
        	}
		if (car(o)->this.number.this.integer < car(cdr(o))->this.number.this.integer)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else if (car(o)->this.number.this.integer > car(cdr(o))->this.number.this.integer)
		{
			obj_res=obj_false;
			return obj_res;
		}
		else
		{
			WARNING_MSG("Il y a égalité");
			return NULL;
		}
	}while (cdr(o) != obj_empty_list);
	
	return obj_res;
}
/**
*@fn object* superio (object* o)
*
*@brief Evalue la superiorité
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/


object* superio (object* o){
	if ((o == obj_empty_list) || ( cdr(o) == obj_empty_list))
	{
		WARNING_MSG("Pas assez d'arguments - min 2");
		return NULL;
	}
	object* obj_res = make_object();
	obj_res->type = SFS_NUMBER;
	do
	{
		if((car(o)->type != SFS_NUMBER)|| (car(cdr(o))->type != SFS_NUMBER))
        	{
           	 	WARNING_MSG("Au moins un argument non entier");
            		return NULL;
        	}
		if (car(o)->this.number.this.integer > car(cdr(o))->this.number.this.integer)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else if (car(o)->this.number.this.integer < car(cdr(o))->this.number.this.integer)
		{
			obj_res=obj_false;
			return obj_res;
		}
		else
		{
			WARNING_MSG("Il y a égalité");
			return NULL;
		}
	}while (cdr(o) != obj_empty_list);
	
	return obj_res;
}

/**
*@fn object* fabs (object* o)
*
*@brief Evalue la valeur absolue
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/

object* fabs (object* o){
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if ((cdr(o))!= obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments ");
		return NULL;
	}
	if(car(o)->type != SFS_NUMBER)
   	{
        	WARNING_MSG("Au moins un argument non entier");
       		return NULL;
    	}
	object* obj_abs = make_object();
	obj_abs->type = SFS_NUMBER;
	if(car(o)->this.number.this.integer <0) 
	{
		obj_abs->this.number.this.integer= -car(o)->this.number.this.integer;
		return obj_abs;
	}
	else
	{
		return o;
	}
}


/**
*@fn object* isnull (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/

object* isnull (object* o){
	if (o == obj_empty_list)
	{
		return obj_true;
	}
	else
	{
		return obj_false;
	}
}


/**
*@fn object* isboolean? (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/


object* isboolean (object* o){
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_res = make_object();
	do
	{ 
		if ((car(o) == obj_true) || (car(o) == obj_false)  )
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res=obj_false;
			return obj_res;
		}
	}while (o != obj_empty_list);
	return obj_res;
}


/**
*@fn object* issymbol (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/

object* issymbol (object* o){
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_res = make_object();
	do
	{ 
		if (car(o)->type == SFS_SYMBOL)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res=obj_false;
			return obj_res;
		}
	}while (o != obj_empty_list);
	return obj_res;
}



/**
*@fn object* isinteger (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/


object* isinteger (object* o){
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_res = make_object();
	do
	{ 
		if (car(o)->type == SFS_NUMBER)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res=obj_false;
			return obj_res;
		}
	}while (o != obj_empty_list);
	return obj_res;
}




/**
*@fn object* ischar (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/


object* ischar (object* o){
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_res = make_object();
	do
	{ 
		if (car(o)->type == SFS_CHARACTER)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res=obj_false;
			return obj_res;
		}
	}while (o != obj_empty_list);
	return obj_res;
}




/**
*@fn object* isstring (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/

object* isstring (object* o){
    if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_res = make_object();
	do
	{ 
		if (car(o)->type == SFS_STRING)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res=obj_false;
			return obj_res;
		}
	}while (o != obj_empty_list);
	return obj_res;
}




/**
*@fn object* ispair (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/

object* ispair (object* o){
    if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_res = make_object();
	do
	{ 
		if (car(o)->type == SFS_PAIR)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res=obj_false;
			return obj_res;
		}
	}while (o != obj_empty_list);
	return obj_res;
}


/**
*@fn object* cons (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/

object* cons (object* o)
{
	if (o == obj_empty_list && cdr(o) == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if (cdr(cdr(o))!= obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	object* obj_cons = make_object();
	obj_cons->type = SFS_PAIR;
	
	obj_cons->this.pair.car = car(o);
	obj_cons->this.pair.cdr = car(cdr(o));

	return obj_cons;

}




/**
*@fn object* car (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/


object* fcar (object* o)	
{
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if (cdr(o) != obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	object* obj_car = make_object();
	obj_car->type = o->type;
	obj_car=car(car(o));
	return obj_car;
}


/**
*@fn object* cdr (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/



object* fcdr (object* o)	
{
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if (cdr(o) != obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	object* obj_cdr = make_object();
	obj_cdr->type = o->type;
	obj_cdr=cdr(car(o));
	return obj_cdr;
}




/**
*@fn object* setcar (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*
*/

object* setcar (object* o)
{
	if ((o == obj_empty_list) || (cdr(o) == obj_empty_list))
	{
		WARNING_MSG("Pas assez d'arguments - min 2");
		return NULL;
	}
	if (( car(o)->type != SFS_PAIR )||(car(cdr(o))-> type != SFS_NUMBER))
	{
		WARNING_MSG("set-car! ne s'applique pas à votre argument");
		return NULL;
	}
	object* obj_setcar = make_object();
	obj_setcar->type = SFS_PAIR;
	obj_setcar->this.pair.car= cdr(cdr(o))->this.number.this.integer;
	obj_setcar->this.pair.cdr= cdr(car(o))->this.number.this.integer;
	return obj_setcar;
}


/**
*@fn object* setcdr! (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/

object* setcdr (object* o)
{
	if ((o == obj_empty_list) || (cdr(o) == obj_empty_list))
	{
		WARNING_MSG("Pas assez d'arguments - min 2");
		return NULL;
	}
	if (( car(o)->type != SFS_PAIR )||(car(cdr(o))-> type != SFS_NUMBER))
	{
		WARNING_MSG("set-car! ne s'applique pas à votre argument");
		return NULL;
	}
	object* obj_setcdr = make_object();
	obj_setcdr->type = SFS_PAIR;
	obj_setcdr->this.pair.car= car(car(o))->this.number.this.integer;
	obj_setcdr->this.pair.cdr= cdr(o)->this.number.this.integer;
	return obj_setcdr;
}



/*
/**
*@fn object* islist (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/


object* islist (object* o){
	if( o == obj_empty_list){return obj_true;}
	if( o->type != SFS_PAIR){return obj_false;}
	o = car(o);
	while(1){
		if(o == obj_empty_list){return obj_true;}
		if(o->type != SFS_PAIR){return obj_false;}
		o = cdr(o);
	} 
}





/**
*@fn object* iseq (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*
*/

object* iseq (object* o)
{
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'argument - min 1");
		return NULL;
	}
	if (cdr(cdr(o)) != obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	object* obj_eq = make_object();
	if(car(o)->type == car(cdr(o))->type)
	{
		if ( (car(o)->this.number.this.integer==car(cdr(o))->this.number.this.integer))
			obj_eq = obj_true;
			return obj_eq;
        }
        else
		{
			obj_eq = obj_false;
			return obj_eq;
		}
}






/**
*@fn object* char2integer (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*
**/

object* char2integer (object* o)
{
	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if ((cdr(o))!= obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	if (o->type != SFS_CHARACTER)
	{
		WARNING_MSG("Argument invalide");
		return NULL;
	}
	object* obj_tranfs = make_object();
	obj_tranfs->type = SFS_NUMBER;
	obj_tranfs->this.number.this.integer = sscanf("%d", o);
	return obj_tranfs;
}



/**
*@fn object* integer2char (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/


object* integer2char (object* o)
{
 	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if ((cdr(o))!= obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	if (o->type != SFS_NUMBER)
	{
		WARNING_MSG("Argument depart mauvais type");
		return NULL;
	}
	object* obj_tranfs = make_object();
	obj_tranfs->type = SFS_CHARACTER;
	if (car(o) <126 || car(o) >0)
	{
		obj_tranfs->this.character= sscanf("%d", o->this.number.this.integer);
		return obj_tranfs;
	}
	else
	{
		WARNING_MSG("Argument invalide");
		return NULL;
	}
}




/**
*@fn object* number2string (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/


object* number2string (object* o)
{
 	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if ((cdr(o))!= obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	if (o->type != SFS_NUMBER)
	{
		WARNING_MSG("Argument invalide");
		return NULL;
	}
	object* obj_tranfs = make_object();
	obj_tranfs->type = SFS_STRING;
	obj_tranfs = sscanf("%d", o->this.number.this.integer);
	return obj_tranfs;
}




/**
*@fn object* string2number (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/


object* string2number (object* o)
{
 	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if ((cdr(o))!= obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	if (o->type != SFS_STRING)
	{
		WARNING_MSG("Argument invalide");
		return NULL;
	}
	object* obj_tranfs = make_object();
	obj_tranfs->type = SFS_NUMBER;
	obj_tranfs->this.number.this.integer = sscanf("%d", o);
	return obj_tranfs;
}




/**
*@fn object* symbol2string (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/


object* symbol2string (object* o)
{

 	if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if ((cdr(o))!= obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	if (o->type != SFS_SYMBOL)
	{
		WARNING_MSG("Argument invalide");
		return NULL;
	}
	object* obj_tranfs = make_object();
	obj_tranfs->type = SFS_STRING;
	obj_tranfs = sscanf("%s", o);
	return obj_tranfs;
}



/**
*@fn object* string2symbol (object* o)
*
*@brief
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
**/

object* string2symbol (object* o)
{
    if (o == obj_empty_list)
	{
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	if ((cdr(o))!= obj_empty_list)
	{
		WARNING_MSG("Trop d'arguments - max=2");
		return NULL;
	}
	if (o->type != SFS_STRING)
	{
		WARNING_MSG("Argument invalide");
		return NULL;
	}
	object* obj_tranfs = make_object();
	obj_tranfs->type = SFS_SYMBOL;
	obj_tranfs->type = sscanf("%c", o);
	return obj_tranfs;
}

