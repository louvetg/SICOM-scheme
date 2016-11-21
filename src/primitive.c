
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
	if (o == obj_empty_list) // Cas liste vide
	{ 
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_sous = make_object();
	obj_sous->type = SFS_NUMBER;
	obj_sous->this.number.this.integer = 0;
	if (cdr(o) == obj_empty_list) // Si 1 élément: on renvoie l'inverse
	{ 
		obj_sous= - car(o)->this.number.this.integer;
		return obj_sous;
	}
	else
	{
		obj_sous->this.number.this.integer = car(o)->this.number.this.integer - car(cdr(o))->this.number.this.integer;
		o = cdr(o);
		while (cdr(o) != obj_empty_list)
		{
			if ( (INT_MIN + o->this.number.this.integer) > obj_sous->this.number.this.integer) //verif qu'on atteint pas la limite
			{
				WARNING_MSG("Overflow"); // message mais l'opération continue
			}		
		obj_sous->this.num = obj_sous->this.num.this.integer - car(o)->this.number.this.integer; //(- a b) = a-b
		o = cdr(o);
		}
	}
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
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_somme = make_object();
	obj_somme->type = SFS_NUMBER;
	obj_somme->this.number.this.integer = 0;
	do
	{
		//verif qu'on atteint pas la limite  -----------------------A VERIFIER
		if (INT_MIN-o.this.number.this.integer > obj_somme)
		{
			WARNING_MSG("Overflow"); // message mais l'opération continue
		}		
		obj_somme->this.number.this.integer = car(o)->this.number.this.integer+ obj_somme->this.number.this.integer;
		o = cdr(o);
	}while (o != obj_empty_list)
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
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_produit = make_object();
	obj_produit->type = SFS_NUMBER;
	obj_produit->->this.number.this.integer = 1;
	do
	{
		//verif qu'on atteint pas la limite -----------------------A VERIFIER
		if (INT_MIN/o.this.number.this.integer > obj_produit)
		{
			WARNING_MSG("Overflow"); // message mais l'opération continue
		}		
		obj_produit->this.number.this.integer = car(o)->this.number.this.integer* obj_produit->this.number.this.integer;
		o = cdr(o);
	}while (o != obj_empty_list);
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
	if ((o == obj_empty_list))
	{ 
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_divis = make_object();
	obj_divis->type = SFS_NUMBER;
	obj_divis->this.number.this.integer = 1;
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
			//verif qu'on atteint pas la limite -----------------------A VERIFIER
			if(obj_divis->this.number.this.integer  == 0)
			{
				WARNING_MSG("Division par 0"); // message mais l'opération continue
				return NULL;
			}
			obj_divis->this.number.this.integer =obj_divis->this.number.this.integer /  car(o)->this.number.this.integer;
			o = cdr(o);
		}
	}
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
	obj_reste->this.number.this.integer = car(o)->this.number.this.integer % car(cdr(o))->this.number.this.integer;
	//verif que le reste est un integer-----------------------A VERIFIER
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
	}while (cdr(cdr(o)) != obj_empty_list);
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
	}while (cdr(cdr(o)) != obj_empty_list);
	//verif que le résultat est un bouleen-----------------------A VERIFIER
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
	}while (cdr(cdr(o)) != obj_empty_list);
	//verif que le résultat est un bouleen-----------------------A VERIFIER
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
*/


object* fabs (object* o){ 
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
	object* obj_abs = make_object();
	obj_abs->type = SFS_NUMBER;
	if(car(o)->this.number.this.integer <0) // ----------------------------o ou car(o)?
	{
		obj_abs->this.number.this.integer= -car(o)->this.number.this.integer;
		return obj_abs;
	}
	else
	{
		return o;
	}
}



/***********************************************************************************************************
/***********************************************************************************************************
/**** 
/****        Predicats
/**** 
/**** 




/**
*@fn object* isnull (object* o)
*
*@brief 
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/


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
*/


object* isboolean (object* o){ 
	if (o == obj_empty_list)
	{ 
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	
	object* obj_res = make_object();
	do
	{ // ------------------------ A VERIFIER
		if ((car(o)->this.number.this.integer == obj_true) || (car(o)->this.number.this.integer == obj_false)  )
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res=obj_false;
			return obj_res;
		}
	}while (cdr(cdr(o)) != obj_empty_list);
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
*/


object* issymbol (object* o){ 
	if (o == obj_empty_list)
	{ 
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}	
	object* obj_res = make_object();
	do
	{ // ------------------------ A VERIFIER
		if (car(o)->this.type == SFS_SYMBOL)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res=obj_false;
			return obj_res;
		}
	}while (cdr(cdr(o)) != obj_empty_list);
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
	{ // ------------------------ A VERIFIER
		if (car(o)->this.type == SFS_NUMBER)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res=obj_false;
			return obj_res;
		}
	}while (cdr(cdr(o)) != obj_empty_list);
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
*/


object* ischar (object* o){ 
	if (o == obj_empty_list)
	{ 
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_res = make_object();
	do
	{ // ------------------------ A VERIFIER
		if (car(o)->this.type == SFS_CHARACTER)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res=obj_false;
			return obj_res;
		}
	}while (cdr(cdr(o)) != obj_empty_list);
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
*/


object* isstring (object* o){ 
	if (o == obj_empty_list)
	{ 
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_res = make_object();
	do
	{ // ------------------------ A VERIFIER
		if (car(o)->this.type == SFS_STRING)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res=obj_false;
			return obj_res;
		}
	}while (cdr(cdr(o)) != obj_empty_list);
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
*/


object* ispair (object* o){ 
	if (o == obj_empty_list)
	{ 
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}
	object* obj_res = make_object();
	do
	{ // ------------------------ A VERIFIER
		if (car(o)->this.type == SFS_PAIR)
		{
			obj_res=obj_true;
			o = cdr(o);
		}
		else
		{
			obj_res=obj_false;
			return obj_res;
		}
	}while (cdr(cdr(o)) != obj_empty_list);
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
	object* obj_cons = make_object();
	obj_cons->type = SFS_PAIR;
	// -----------------------------N'affiche pas les . entre les paires, on doit analyser si '(a) ou 4 ? ou deja fait avant?
	obj_cons->this.pair.car = car (o);
	obj_cons->this.pair.cdr = cdr (o);
 
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
	
	
object* car (object* o)	// ---------------- a tester si o est une liste 
{
	if (o == obj_empty_list)
	{ 
		WARNING_MSG("Pas assez d'arguments - min 1");
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
	
	
object* cdr (object* o)	// ---------------- a tester si o est une liste 
{
	if (o == obj_empty_list)
	{ 
		WARNING_MSG("Pas assez d'arguments - min 1");
		return NULL;
	}	
	return cdr(o);	
}	

/**
*@fn object* setcar (object* o)
*
*@brief 
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/
	
	
object* setcar (object* o)	
{
	if ((o == obj_empty_list) || (cdr(o) == obj_empty_list))
	{ 
		WARNING_MSG("Pas assez d'arguments - min 2");
		return NULL;
	}
	if ( o->this.type != SFS_PAIR )
	{
		WARNING_MSG("set-car! ne s'applique pas à votre argument");
		return NULL;
	}
	object* obj_setcar = make_object();
	obj_setcar->type = SFS_PAIR;
	// ------------------- VERIFIER QUE LES ELEMENTS SONT BIEN DES NOMBRES?
	obj_setcar->this.pair.car= cdr(o)->this.number.this.integer;
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
*/
	
	
object* setcdr (object* o)	
{
	if ((o == obj_empty_list) || (cdr(o) == obj_empty_list))
	{ 
		WARNING_MSG("Pas assez d'arguments - min 2");
		return NULL;
	}
	if ( o->this.type != SFS_PAIR )
	{
		WARNING_MSG("set-car! ne s'applique pas à votre argument");
		return NULL;
	}
	object* obj_setcdr = make_object();
	obj_setcdr->type = SFS_PAIR;
	// ------------------- VERIFIER QUE LES ELEMENTS SONT BIEN DES NOMBRES?
	obj_setcdr->this.pair.car= car(car(o))->this.number.this.integer;
	obj_setcdr->this.pair.cdr= cdr(o)->this.number.this.integer;
	return obj_setcar;
}
	

		    
		    
/**
*@fn object* islist (object* o)
*
*@brief 
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/
	
	
object* islist (object* o)	
{
	//------------------------A FAIRE
}

		    
		    
		    
		    
/**
*@fn object* iseq (object* o)
*
*@brief 
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/
	
	
object* iseq (object* o)	
{
	//------------------------A FAIRE
}		    
		    
		    


		    
		    
/***********************************************************************************************************
/***********************************************************************************************************
/**** 
/****        Conversions de types
/**** 
/**** 




/**
*@fn object* char2integer (object* o)
*
*@brief 
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/
	
	
object* char2integer (object* o)	
{	
 
}		    




/**
*@fn object* integer2char (object* o)
*
*@brief 
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/
	
	
object* integer2char (object* o)	
{	
 
}		    




/**
*@fn object* number2string (object* o)
*
*@brief 
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/
	
	
object* number2string (object* o)	
{	
 
}		    




/**
*@fn object* string2number (object* o)
*
*@brief 
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/
	
	
object* string2number (object* o)	
{	
 
}			   




/**
*@fn object* symbol2string (object* o)
*
*@brief 
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/
	
	
object* symbol2string (object* o)	
{	
 
}		    



/**
*@fn object* string2symbol (object* o)
*
*@brief 
*
*@param object* o pointeur vers la structure étudiée
*
*@return object o* retourne l'expression passée dans la fonction
*/
	
	
object* string2symbol (object* o)	
{	
 
}
