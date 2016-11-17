
/***********************************************************************************************************
/***********************************************************************************************************
/**** 
/****        Arithmétique entière
/**** 
/**** 


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
		WARNING_MSG("Le calcul est vide");
		return NULL;
	}
	object* obj_sous = make_object();
	obj_sous->type = SFS_NUMBER;
	obj_sous->this.num = 0;
	do
	{
		//verif qu'on atteint pas la limite -----------------------A VERIFIER
		if ((obj_sous <= INT_MIN) || (obj_sous >= INT_MAX))
		{
			WARNING_MSG("Overflow"); // message mais l'opération continue
		}		
		obj_sous->this.num = car(o)->this.num- obj_sous->this.num;
		o = cdr(o);
	}while (cdr(o) != obj_empty_list)
	//verif que la soustraction est un integer-----------------------A VERIFIER
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
		WARNING_MSG("Le calcul est vide");
		return NULL;
	}
	object* obj_somme = make_object();
	obj_somme->type = SFS_NUMBER;
	obj_somme->this.num = 0;
	do
	{
		//verif qu'on atteint pas la limite  -----------------------A VERIFIER
		if ((obj_somme <= INT_MIN) || (obj_somme >= INT_MAX))
		{
			WARNING_MSG("Overflow"); // message mais l'opération continue
		}		
		obj_somme->this.num = car(o)->this.num+ obj_somme->this.num;
		o = cdr(o);
	}while (cdr(o) != obj_empty_list)
	//verif que l'addition est un integer-----------------------A VERIFIER
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
		WARNING_MSG("Le calcul est vide");
		return NULL;
	}
	object* obj_produit = make_object();
	obj_produit->type = SFS_NUMBER;
	obj_produit->this.num = 1;
	do
	{
		//verif qu'on atteint pas la limite -----------------------A VERIFIER
		if ((obj_produit <= INT_MIN) || (obj_produit >= INT_MAX))
		{
			WARNING_MSG("Overflow"); // message mais l'opération continue
		}		
		obj_produit->this.num = car(o)->this.num* obj_produit->this.num;
		o = cdr(o);
	}while (cdr(o) != obj_empty_list)
	//verif que la multiplication est un integer-----------------------A VERIFIER
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
	if (o == obj_empty_list)
	{ 
		WARNING_MSG("Le calcul est vide");
		return NULL;
	}
	object* obj_divis = make_object();
	obj_divis->type = SFS_NUMBER;
	obj_divis->this.num = 1;
	do
	{
		//verif qu'on atteint pas la limite -----------------------A VERIFIER
		if ((obj_divis <= INT_MIN) || (obj_divis >= INT_MAX))
		{
			WARNING_MSG("Overflow");
		}
		if(obj_divis == 0)
		{
			WARNING_MSG("Division par 0"); // message mais l'opération continue
			return NULL;
		}
		obj_divis->this.num = car(o->this.num)/ obj_divis->this.num;
		o = cdr(o);
	}while (cdr(o) != obj_empty_list)
	//verif que la division est un integer-----------------------A VERIFIER
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
	if (o == obj_empty_list)
	{ 
		WARNING_MSG("Le calcul est vide");
		return NULL;
	}
	object* obj_res = make_object();
	obj_res->type = SFS_NUMBER;
	object* obj_res_prec = make_object();
	obj_res_prec->type = SFS_NUMBER;
	do
	{
		if (car(o)->type.num == car(cdr(o))->type.num)
		{
			obj_res->this.num = 1;
			if( obj_res->this.num && obj_res_prec)
			{
				obj_res_prec-> type.num = NULL; // C'est bien l'o-> type. num qui va annuler mon && ???
			}
			o = cdr(o);
		}
		else
		{
			obj_res_prec-> type.num = NULL;
			o = cdr(o);
		}
	}while (cdr(o) != obj_empty_list);
	//verif que le résultat est un bouleen-----------------------A VERIFIER
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
*/


object* inferio (object* o){  
	if (o == obj_empty_list)
	{ 
		WARNING_MSG("Le calcul est vide");
		return NULL;
	}
	object* obj_res = make_object();
	obj_res->type = SFS_NUMBER;
	object* obj_res_prec = make_object();
	obj_res_prec->type = SFS_NUMBER;
	do
	{
		if (car(o)->type.num < car(cdr(o))->type.num)
		{
			obj_res->this.num = 1;
			if( obj_false && obj_res)
			{
				obj_res_prec-> type.num = NULL; // C'est bien l'o-> type. num qui va annuler mon && ???
			}
			o = cdr(o);
		}
		else if (car(o)->type.num > car(cdr(o))->type.num)
		{
			obj_res_prec-> type.num = NULL;
			o = cdr(o);
		}
		else
		{
			WARNING_MSG("Il y a égalité");
			return NULL;
		}	
	}while (cdr(o) != obj_empty_list);
	//verif que le résultat est un bouleen-----------------------A VERIFIER
	return obj_res;
}







/**
*@fn object* superio (object* o)
*
*@brief Evalue l'infériorité
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/


object* superio (object* o){  
	if (o == obj_empty_list)
	{ 
		WARNING_MSG("Le calcul est vide");
		return NULL;
	}
	object* obj_res = make_object();
	obj_res->type = SFS_NUMBER;
	object* obj_res_prec = make_object();
	obj_res_prec->type = SFS_NUMBER;
	do
	{
		if (car(o)->type.num > car(cdr(o))->type.num)
		{
			obj_res->this.num = 1;
			if( obj_false && obj_res)
			{
				obj_res_prec-> type.num = NULL; // C'est bien l'o-> type. num qui va annuler mon && ???
			}
			o = cdr(o);
		}
		else if (car(o)->type.num< car(cdr(o))->type.num)
		{
			obj_res_prec-> type.num = NULL;
			o = cdr(o);
		}
		else
		{
			WARNING_MSG("Il y a égalité");
			return NULL;
		}	
	}while (cdr(obj_bis) != obj_empty_list);
	//verif que le résultat est un bouleen-----------------------A VERIFIER
	return obj_res;
}



/**
*@fn object* abs (object* o)
*
*@brief Evalue l'infériorité
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/


object* abs (object* o){ 
	 // --------------------------------A COMPLETER
}

/***********************************************************************************************************
/***********************************************************************************************************
/**** 
/****        Predicats
/**** 
/**** 



/**
*@fn object* boolean? (object* o)
*
*@brief 
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/


object* boolean? (object* o){ 
	if (o == obj_empty_list)
	{ 
		WARNING_MSG("L'expression est vide");
		return NULL;
	}
	object* obj_res = make_object();
	obj_res->type = SFS_NUMBER;
	if (cdr(o)->type. == obj_empty_list)
	{
		if(car
	return obj_res;
}



/**
*@fn object* null? (object* o)
*
*@brief 
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/


object* null? (object* o){ 
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
*@fn object* symbol? (object* o)
*
*@brief 
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/


object* symbol? (object* o){ 
	if (o == obj_empty_list)
	{ 
		WARNING_MSG("Le calcul est vide");
		return NULL;
	}
	object* obj_res == NULL;
	object* obj_res = make_object();
	while (cdr(o) != obj_empty_list)
	{
		if (o->type = SFS_SYMBOL)
		{
			obj_res = obj_true && obj_res;
			obj_bis = cdr(obj_bis);
		}
		else
		{
			obj_res = obj_false && obj_res;
			obj_bis = cdr(obj_bis);
		}
	return obj_res;
}

	





/***********************************************************************************************************
/***********************************************************************************************************
/**** 
/****        Manipulation de listes
/**** 
/**** 


/**
*@fn object* cons (object* o)
*
*@brief 
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/
	
	
object* cons (object* o)	
{
// --------------------------------------------A COMPLETER	
}
	
	
	

/**
*@fn object* car (object* o)
*
*@brief 
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/
	
	
object* car (object* o)	
{
	if (o == obj_empty_list)
	{ 
		WARNING_MSG("Trop peu d'arguments");
		return NULL;
	}	
	return car(o);	
}
	

/**
*@fn object* cdr (object* o)
*
*@brief 
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/
	
	
object* cdr (object* o)	
{
	if (o == obj_empty_list)
	{ 
		WARNING_MSG("Trop peu d'arguments");
		return NULL;
	}	
	return cdr(o);	
}	

/**
*@fn object* set-car! (object* o)
*
*@brief 
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/
	
	
object* set-car! (object* o)	
{
	
}
	
	
/**
*@fn object* set-cdr! (object* o)
*
*@brief 
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/
	
	
object* set-cdr! (object* o)	
{
	
}
