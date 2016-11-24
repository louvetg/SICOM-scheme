
/**
* @file read.c
* @author François Cayre <cayre@yiking.(null)>
* @date Fri Jun 15 18:31:05 2012
* @brief Read routine for SFS.
*
* Read routine for SFS.
*/

#include <stdio.h>
#include <ctype.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "read.h"



void flip(uint *i) {

	if (*i == FALSE) {
		*i = TRUE;
	}
	else {
		*i = FALSE;
	}
}

/*
* @fn char* first_usefull_char(char* line)
*
* @brief retourne un pointeur sur le premier caractere utile dans line
* ou NULL si line ne contient que des espaces et des commentaires
*/
char* first_usefull_char(char* line) {

	int i = 0;
	if (line == NULL) {
		return NULL;
	}
	i = 0;
	/* on saute les espaces */
	while (line[i] != '\0' && isspace(line[i])) {
		i++;
	}
	/* si fin de ligne => ligne inutile */
	if (line[i] == '\0') {
		return NULL;
	}
	/* si premier caractere non espace est ';' => ligne inutile */
	if (line[i] == ';') {
		return NULL;
	}
	return line + i; /* ligne utile */
}

/**
* @fn uint  sfs_get_sexpr( char *input, FILE *fp )
*
* @brief extrait la prochaine S-Expression dans le flux fp et la stocke dans input
* (meme si elle est repartie sur plusieurs lignes)
* @param fp (FILE *) flux d'entree (ouvert en ecriture, mode texte)
* @param input (char *) chaine allouee de taille BIGSTRING, dans laquelle la S-Expression sera stockée
*
* @return S_OK si une S-Expression apparemment valide a ete trouvee
* @return S_KO si on n'a pas trouve de S-Expression valide
* @return S_END si fin de fichier atteinte sans avoir lu de caractere utile.
*
* sfs_get_sexpr commence par lire une ligne dans fp,
* puis compte le nombre de parentheses ouvrantes et fermantes sur la ligne.
* Les parentheses dans des chaines et les caracteres Scheme #\( et #\)
* ne sont pas comptes.
*
* Si le compte devient zéro et que
*        - la ligne est fini, la fonction retourne S_OK
* 				- la ligne n'est pas fini la fonction retourne S_KO
*
* S'il y a plus de parentheses fermantes qu'ouvrantes,
* la fonction retourne S_KO.
* Les commentaires et espaces qui figurent a la fin de chaque ligne
* sont remplacés par un espace.
* Les espaces qui figurent a la fin de la S-Expression (y compris '\n')
* sont supprimés.
*
* Attention : cette fonction refuse les S-Expression multiple sur une seule ligne. Ainsi :
*    a b c
*    (qqchose) (autrechose)
*    (qqchose) 78
* seront considereees comme des erreurs
* et la fonction retournera S_KO
*
* @pre fp doit etre prealablement ouvert en lecture
* @pre input doit etre prealablement alloue en memoire, de taille BIGSTRING
*/

typedef enum {
	NOTHING,        /* rien n'a ete trouve encore.. */
	STRING_ATOME,   /* la premiere trouvee dans la ligne semble etre un atome */
	BASIC_ATOME,    /* la premiere trouvee dans la ligne semble etre d'une chaine */
	S_EXPR_PARENTHESIS, /* la premiere trouvee dans la ligne semble etre une expression parenthesee */
	FINISHED        /* on a trouve une S-Expr bien formee */
} EXPRESSION_TYPE_T;

uint  sfs_get_sexpr(char *input, FILE *fp) {
	int       parlevel = 0;
	uint      in_string = FALSE;
	uint      s = 0;
	char      k[BIGSTRING];
	char      *ret = NULL;
	char      *chunk = NULL;
	uint      i = 0;
	string    sfs_prompt;

	EXPRESSION_TYPE_T typeOfExpressionFound = NOTHING;

	parlevel = 0;
	memset(input, '\0', BIGSTRING);

	do {
		ret = NULL;
		chunk = NULL;

		/* si en mode interactif*/
		if (stdin == fp) {
			uint nspaces = 2 * parlevel;

			init_string(sfs_prompt);

			/* le prompt indique le niveau de parenthese
			et decale la prochaine entrée en fonction
			de ce niveau (un peu à la python)*/
			sprintf(sfs_prompt, "SFS:%u > ", parlevel);

			for (i = 0; i< nspaces; i++) {
				sfs_prompt[strlen(sfs_prompt)] = ' ';
			}

			/* si sur plusieurs lignes, le \n équivaut à un espace*/
			if (nspaces>0) {
				input[strlen(input) + 1] = '\0';
				input[strlen(input)] = ' ';
			}

			/*saisie de la prochaine ligne à ajouter dans l'input*/
			chunk = readline(sfs_prompt);
		}
		/*si en mode fichier*/
		else {
			chunk = k;
			memset(chunk, '\0', BIGSTRING);
			ret = fgets(chunk, BIGSTRING, fp);

			if (NULL == ret) {
				/* fin de fichier...*/
				if (parlevel != 0) {
					WARNING_MSG("Parse error: missing ')'");
					return S_KO;
				}
				return S_END;
			}

			if (strlen(chunk) == BIGSTRING - 1
				&& chunk[BIGSTRING - 1] != '\n'
				&& !feof(fp)) {
				WARNING_MSG("Too long line for this interpreter!");
				return S_KO;
			}
		}

		/* si la ligne est inutile
		=> on va directement à la prochaine iteration */
		if (first_usefull_char(chunk) == NULL) {
			continue;
		}


		s = strlen(chunk);

		if (s > 0) {
			if (strlen(input) + s > BIGSTRING - 1) {
				WARNING_MSG("Too long a S-expression for this interpreter!");
				return S_KO;
			}

			for (i = 0; i< strlen(chunk); i++) {
				/* si la fin de la ligne chunk est inutile,
				on ajoute un espace dans input et on sort de la boucle*/
				if (in_string == FALSE && first_usefull_char(chunk + i) == NULL) {
					chunk[i] = '\0';
					input[strlen(input)] = ' ';
					break;
				}


				switch (chunk[i]) {
				case '(':
					if (in_string == FALSE
						&& !(i>1 && chunk[i - 1] == '\\' && chunk[i - 2] == '#')) {
						parlevel++;
						typeOfExpressionFound = S_EXPR_PARENTHESIS;
					}
					break;
				case ')':
					if (in_string == FALSE
						&& !(i>1 && chunk[i - 1] == '\\' && chunk[i - 2] == '#')) {
						parlevel--;
						if (parlevel == 0) {
							typeOfExpressionFound = FINISHED;
						}
						if (parlevel < 0) {
							WARNING_MSG("Parse error : cannot start with ')'");
							return S_KO;
						}
					}
					break;
				case '"':
					if (i<2 || chunk[i - 1] != '\\') {
						if (in_string == FALSE) {
							if (typeOfExpressionFound == BASIC_ATOME) {
								WARNING_MSG("Parse error: invalid string after atom : '%s'", chunk + i);
								return S_KO;
							}
							in_string = TRUE;
							if (typeOfExpressionFound != S_EXPR_PARENTHESIS) {
								typeOfExpressionFound = STRING_ATOME;
							}
						}
						else {
							in_string = FALSE;
							if (typeOfExpressionFound == STRING_ATOME) {
								typeOfExpressionFound = FINISHED;
							}
						}
					}
					break;
				default:
					if (in_string == FALSE) {
						if (isspace(chunk[i])) {
							if (typeOfExpressionFound == BASIC_ATOME) {
								typeOfExpressionFound = FINISHED;
							}
						}
						else if (typeOfExpressionFound != S_EXPR_PARENTHESIS) {
							typeOfExpressionFound = BASIC_ATOME;
						}
					}
					break;
				}


				if (typeOfExpressionFound == FINISHED) {
					char *first_useful = first_usefull_char(chunk + i + 1);
					if (first_useful != NULL) {
						if (*first_useful == ')') {
							WARNING_MSG("Parse error: too many closing parenthesis')'");
						}
						else {
							WARNING_MSG("Parse error: invalid trailing chars after S-Expr : '%s'", chunk + i);
						}
						return S_KO;
					}
				}

				/* recopie char par char*/
				input[strlen(input)] = chunk[i];
			}
			if (in_string == TRUE) {
				WARNING_MSG("Parse error: non terminated string on line %s", chunk);
				return S_KO;
			}
		}


		if (parlevel > 0 && fp != stdin) {
			if (feof(fp)) {
				WARNING_MSG("Parse error: missing ')'");
				return S_KO;
			}

			if (input[strlen(input) - 1] == '\n') input[strlen(input) - 1] = ' ';
		}
	} while (parlevel > 0);

	/* Suppression des espaces restant a la fin de l'expression, notamment le dernier '\n' */
	while (isspace(input[strlen(input) - 1])) input[strlen(input) - 1] = '\0';

	if (stdin == fp) {
		add_history(input);
	}
	return S_OK;
}



/**
*@fn void Delete_space(char* input)
*
*@brief supprime tout les espaces en trop. Transforme \n , \r et \t en espace. Rajoute une espace à la fin de la chaine.
*
*@param char* input chaine extraite du flux d'entrée.
*
*/

void Delete_space(char* input){
	char temp[BIGSTRING];
	uint l = strlen(input);
	uint k;
	uint a = FALSE;
	for (k = 0; k < l; k++){
		if (test_string(k, input)){
			a = !(a ^ FALSE);
		}
		if ((input[k] == '\n' || input[k] == '\t' || input[k] == '\r') && !a){
			temp[k] = ' ';
		}
		else{ temp[k] = input[k]; }
	}
	temp[l] = '\0';
	l = strlen(temp);
	init_chaine(input, BIGSTRING);
	uint j = 0;
	a = FALSE;
	for (k = 0; k<l - 1; k++){
		if (test_string(k, temp)){
			a = !(a ^ FALSE);
		}
		if ((isspace(temp[k]) != 0 && isspace(temp[k + 1]) != 0) && !a){}
		else{
			input[j] = temp[k];
			j++;
		}
	}
	input[j] = temp[l - 1];
	input[j + 1] = ' ';
	input[j + 2] = '\0';
}

/**
*@fn object* sfs_read(char* input, uint* pos)
*
*@brief crée recursivement l'arbre représentant la S-expression.
*
*@param char* input chaine extraite du flux d'entrée.
*@param uint *pos position du premier caractère nous interressant dans la chaine input.
*
*@return object* correspondant à l'objet créé.
*@return NULL si la lecture échoue.
*/

object* sfs_read(char *input, uint *pos) {
	if (input[(*pos)] == ' '){
		(*pos) = (*pos) + 1;
	}
	if (input[(*pos)] == '(') {
		if (input[(*pos) + 1] == ')') {
			(*pos) += 2;
			return obj_empty_list;
		}
		if (input[(*pos) + 1] == ' ' && input[(*pos) + 2] == ')'){
			(*pos) += 3;
			return obj_empty_list;
		}
		else {
			(*pos)++;
			return read_pair(input, pos);
		}
	}
	else {
		return read_atom(input, pos);
	}
}

/**
*@fn object* read_pair(char* input, uint* pos)
*
*@brief crée un objet de type paire et appel sfs_read afin de remplir le car et le cdr.
*
*@param char* input chaine extraite du flux d'entrée.
*@param uint *pos position du premier caractère nous interressant dans la chaine input.
*
*@return object* correspondant à la pair créé.
*@return NULL si la lecture du car ou du cdr échoue.
*/


object* read_pair(char* input, uint* pos){

	object* obj_Pair = make_object();
	obj_Pair->type = SFS_PAIR;


	obj_Pair->this.pair.car = sfs_read(input, pos);
	if (obj_Pair->this.pair.car == NULL){ return NULL; }

	if (input[(*pos)] == ' '){
		(*pos) = (*pos) + 1;
	}

	if (input[*pos] == '.'){
		(*pos)++;
		obj_Pair->this.pair.cdr = sfs_read(input, pos);
		if (obj_Pair->this.pair.cdr == NULL){ return NULL; }
		else { return obj_Pair; }
	}

	if (input[*pos] == ')'){
		obj_Pair->this.pair.cdr = obj_empty_list;
		(*pos)++;
	}
	else {
		obj_Pair->this.pair.cdr = read_pair(input, pos);
		if (obj_Pair->this.pair.cdr == NULL){ return NULL; }
	}
	return obj_Pair;

}


/**
*@fn object* read_atom(char* input, uint* pos)
*
*@brief Prend un "bout" unitaire de la chaine d'entrée (+ / 1 / #\a / #t / ...) et crée l'objet correspondant.
*
*@param char* input chaine extraite du flux d'entrée.
*@param uint *pos position du premier caractère nous interressant dans la chaine input.
*
*@return object* correspondant à l'objet créé.
*@return NULL si l'objet ne doit pas exister (ex: #z).
*/

object* read_atom(char* input, uint* pos){

	if ((((input[*pos] == '-') || (input[*pos] == '+')) && (isdigit(input[*pos + 1]) != 0)) || (isdigit(input[*pos]) != 0 )){
		char Num[TEMPON];
		init_chaine(Num,TEMPON);
		Verif_Num(input, *pos , Num);
		if (Num[0] == '\0'){
			WARNING_MSG("Entier invalide en position %d", *pos);
			return NULL;
		}
		else {
			object* obj_Num = make_object();
			*pos = *pos + strlen(Num);
			obj_Num = make_integer(Num, obj_Num);
			return obj_Num;
		}
	}
	if (input[*pos] == '"'){
		char strg[TEMPON];
		init_chaine(strg,TEMPON);
		Verif_strg(input, *pos, strg);
		if (strg[0] == '\0'){
			WARNING_MSG("chaine de caractere invalide en position %d. Les chaine de caractère doivent faire moins de %d caractères", *pos, TEMPON);
			return NULL;
		}
		else {
			object* obj_strg = make_object();
			*pos = *pos + strlen(strg) + 2;
			obj_strg = make_string(strg, obj_strg);
			return obj_strg;
		}
	}
	if (input[*pos] == '#'){
		if (input[*pos + 1] == '\\'){
			char chara[TEMPON];
			init_chaine(chara,TEMPON);
			Verif_Chara(input, *pos, chara);
			if (chara[0] == '\0'){
				WARNING_MSG("caractere invalide en position %d", *pos);
				return NULL;
			}
			else {
				object* obj_chara = make_object();
				*pos = *pos + 3;
				obj_chara = make_chara(chara, obj_chara);
				return obj_chara;
			}
		}
		if ((input[*pos + 1] == 't') && (input[*pos + 2] == ' ' || input[*pos + 2] == ')')){
			*pos = *pos + 2;
			return obj_true;
		}
		if ((input[*pos + 1] == 'f') && (input[*pos + 2] == ' ' || input[*pos + 2] == ')')){
			*pos = *pos + 2;
			return obj_false;
		}
		WARNING_MSG("booleen invalide en position %d", *pos);
		return NULL;
	}

	if (input[*pos] == '\''){

		if (input[*pos] == ' '){ 
			return NULL; 
			WARNING_MSG("argument invalide pour ' (quote) en position %d", *pos);
		}
		*pos = *pos + 1;
		return apost(input, pos);
		
	}

	char symb[TEMPON];
	init_chaine(symb, TEMPON);
	Verif_symb(input, *pos, symb);
	if (symb[0] == '\0'){
		WARNING_MSG("symbole invalide en position %d, taille maximum pour un symbole est de %d caractères", *pos, TEMPON);
		return NULL;
	}
	else {
		object* obj_symb = make_object();
		*pos = *pos + strlen(symb);
		obj_symb = make_symb(symb, obj_symb);
		return obj_symb;
	}
}


/**
*@void init_chaine(char* chaine)
*
*@brief Rempli la chaine de caractère donnée en argument de '/0' plutôt que de 'î'.
*
*@param char* adresse de la chaine à initialisé.
*/


void init_chaine(char* chaine, int a){
	int k = 0;
	for (k = 0; k < a; k++){
		chaine[k] = '\0';
	}
}


/**
*@fn void Verif_Num(char* input, uint pos, char* Num)
*
*@brief Vérifie si la chaine de caractère contient bien un nombre à partir de la position donnée.
*Si la chaine contien bien un nombre il est conservé et retourné sous forme de chaine de caractère.
*
*@param char* input chaine extraite du flux d'entrée.
*@param uint pos position du premier caractère nous interressant dans la chaine input.
*@param char* Num adresse du tableau contenant la sortie.
*
*/


void Verif_Num(char* input, uint pos, char* Num){
	uint k = 0;
	do{
		Num[k] = input[pos + k];
		Num[k + 1] = '\0';
		k++;
	} while (isdigit(input[pos + k]) != 0 && k < TEMPON);
	if (isspace(input[pos + k]) != 0 || input[pos + k] == ')' || input[pos + k] == '\0' || input[pos + k] == '('){ return; }
	Num[0] = '\0';
	return;
}


/**
*@fn object* make_integer(char* Num, object* obj_Num)
*
*@brief Crée un objet de type int à partir du nombre contenu dans la chaine de caractère Num.
*
*@param char* Num chaine de caractère contenant le nombre.
*@param object* obj_Num pointeur vers la structure qui accueillera le nombre.
*
*@return Ne retourne NULL si erreur (gestion des erreurs à voir.).
*@return Retourne l'adresse de la structure contenant le nombre.
*/


object* make_integer(char* Num, object* obj_Num){
	char* eptr;
	if (test_taille_uint(Num) == 2){
		WARNING_MSG("%ld trop long pour etre stocké. Les entiers inférieur à %d sont stocké comme -inf", strtol(Num, &eptr, 0), INT_MIN);
		obj_Num->this.number.this.integer = INT_MIN;
	}
	if (test_taille_uint(Num) == 3){
		WARNING_MSG("%ld trop long pour etre stocké. Les entiers supérieur à %d sont stocké comme +inf", strtol(Num, &eptr, 0), INT_MAX);
		obj_Num->this.number.this.integer = INT_MAX;
	}
	if (test_taille_uint(Num) == 1){
		WARNING_MSG("Un entier est supérieur à %d ou inférieur à %d. Il est trop long pour etre lu", LONG_MAX , LONG_MIN);
		return NULL;
	}

	obj_Num->this.number.this.integer = strtol(Num, &eptr, 0);
	if (obj_Num->this.number.this.integer == 0 && (Num[0] != '0')){
		WARNING_MSG("erreur de stockage d'entier");
		return NULL;
	}
	obj_Num->type = SFS_NUMBER;
	obj_Num->this.number.numtype = NUM_INTEGER;
	return obj_Num;
}

/**
*@fn object* make_integer(char* Num, object* obj_Num)
*
*@brief Permet de savoir si le nombre compris dans la chaine de caractère peut être stocké dans un type uint.
*
*@param char* Num chaine de caractère contenant le nombre.
*
*@return 0 si taille dépassée. 1 sinon.
*/

uint test_taille_uint(char* num){
	errno = 0;
	char* eptr;
	long n = strtol(num, &eptr, 0);
	if (errno == ERANGE){ return 1; }
	if (n <= INT_MIN){ return 2; }
	if ( n >= INT_MAX ){ return 3; }
	else{ return 4; }
}


/**
*@fn void Verif_strg(char* input, uint pos, char* strg)
*
*@brief Vérifie si la chaine de caractère contien bien une chaine de caractère à partir de la position donnée.
*Si la chaine contien bien un nombre il est conservé et retourné sous forme de chaine de caractère.
*
*@param char* input chaine extraite du flux d'entrée.
*@param uint *pos position du premier caractère nous interressant dans la chaine input.
*@param char* strg adresse du tableau contenant la sortie.
*
*@"return" '/0' si la chaine ne contient pas de nombre dans strg.
*@"return" 'chaine représentative de la chaine de caractère' si nous sommes bien en présence d'une chaine de caractère dans strg.
*/


void Verif_strg(char* input, uint pos, char* strg){
	int k = 0;
	pos++;
	while ((test_string(pos + k, input) == 0) && k < TEMPON){
		strg[k] = input[pos + k];
		k++;
	}
	if (k >= TEMPON && test_string(pos+k, input) == 0){strg[0] = '\0'; }
}


/**
*@fn uint test_string(uint k, char* input)
*
*@brief Scrute pour chaque position k pour savoir si nous sommes en présence du caractère de fin de chaine de caractère.
*
*@param uint k position à scruter.
*@param char* input adresse du tableau contenant le flux d'entrée.
*
*@return 1 si en position k on a le caractère de fin de chaine 0 si non.
*/



uint test_string(uint k, char* input){
	if (k > 0 ){
		if (input[k] == '"' && input[k - 1] != '\\'){
			return 1;
		}
		else { return 0;}
	}
	else{
		if (input[k] == '"') {return 1;}
		else {return 0;}
	}
}

/**
*@fn object* make_string(char* strg, object* obj_strg)
*
*@brief Prend la chaine de caractère et la rentre dans la structure objet.
*
*@param char* strg chaine de caractère à copier.
*@param object* obj_strg objet devant contenir la chaine de caractère.
*
*@return NULL si soucis.
*@return l'objet contenant la chaine de caractère.
*/



object* make_string(char* strg, object* obj_strg){
	strcpy(obj_strg->this.strg, strg);
	if (strcmp(obj_strg->this.strg, strg) != 0){
		WARNING_MSG("La chaine de caractère: %s à mal été stockée.",strg);
		return NULL;
	}
	obj_strg->type = SFS_STRING;
	return obj_strg;
}


/**
*@fn void Verif_strg(char* input, uint pos, char* chara)
*
*@brief Copie dans une chaine le caractère se trouvant en position pos.
*
*@param char* input chaine extraite du flux d'entrée.
*@param uint *pos position du premier caractère nous interressant dans la chaine input.
*@param char* chara adresse du tableau contenant la sortie.
*
*@"return" '/0' si la chaine ne contient pas de charactère dans chara.
*@"return" 'chaine représentative du charactère' si nous sommes bien en présence d'une chaine de caractère dans chara.
*/



void Verif_Chara(char* input, uint pos, char* chara){
	uint k = 0;
	pos = pos + 2;
	do{
		chara[k] = input[pos + k];
		chara[k + 1] = '\0';
		k++;
	} while ((isspace(input[pos + k]) != 0 || input[pos + k] == ')') !=1 );
	if (chara[1]!= '\0' && strcmp(chara, "newline") != 0 && strcmp(chara, "space") != 0 ){
		chara[0] = '\0';
		return;
	}
	return;
}

/**
*@fn object* make_chara(char* chara, object* obj_chara)
*
*@brief Prend le caractère et le rentre dans la structure objet.
*
*@param char* chara chaine de caratère contenant le caractère.
*@param object* obj_chara objet devant contenir le caractère.
*
*@return NULL si soucis.
*@return l'objet contenant le caractère.
*/

object* make_chara(char *chara, object* obj_chara){
	if (chara[1] == '\0'){
		obj_chara->this.character = chara[0];
		obj_chara->type = SFS_CHARACTER;
		return obj_chara;
	}
	if (strcmp(chara, "newline") == 0){ /*a faire: trouver la fonction qui compare sans la case*/
		obj_chara->this.character = '\n';
		obj_chara->type = SFS_CHARACTER;
		return obj_chara;
	}
	if (strcmp(chara, "space") == 0){ /*a faire: trouver la fonction qui compare sans la case*/
		obj_chara->this.character = ' ';
		obj_chara->type = SFS_CHARACTER;
		return obj_chara;
	}
	WARNING_MSG("%s n'est pas un caractère possible", chara);
	return NULL;
}

/**
*@fn void Verif_symb(char* input, uint pos, char* symb)
*
*@brief Copie dans une chaine le symbole se trouvant en position pos.
*
*@param char* input chaine extraite du flux d'entrée.
*@param uint *pos position du premier caractère nous interressant dans la chaine input.
*@param char* symb adresse du tableau contenant la sortie.
*
*@"return" '/0' si la chaine ne contient pas de symbole dans symb.
*@"return" 'chaine représentative du symbole' si nous sommes bien en présence d'un symbole dans symb.
*/


void Verif_symb(char* input, int pos, char* symb){
	int k = 0;
	while (((input[pos + k] == ' ' || input[pos + k] == '(' || input[pos + k] == ')') ) != 1){ /*à terme remplacer cette longue condition par une fonction test. Gérer le \0 plutot que ajouter un ' ' à la fin. */
		symb[k] = input[pos + k];
		k++;
		if (k >= TEMPON && !(input[pos + k] == ' ' || input[pos + k] == '(' || input[pos + k] == ')')){
			 symb[0] = '\0';
			 return;
		}
	}
}

/**
*@fn object* make_symb(char* symb, object* obj_symb)
*
*@brief met le symbole contenu dans symb dans la structure obj_symb.
*
*@param char* symb chaine de caractère contenant le symbole.
*@param object* obj_symb pointeur vers la structure qui accueillera le symbole.
*
*@return retourne NULL si erreur.
*@return Retourne l'adresse de la structure contenant le symbole.
*/


object* make_symb(char* symb, object* obj_symb){
	obj_symb = make_string(symb, obj_symb);
	obj_symb->type = SFS_SYMBOL;
	return obj_symb;
}

/**
*@fn object* apost(char* input, uint* pos)
*
*@brief Remplace le caractère apostrophe par le symbole quote et crée l'arbre aproprié.
*
*@param char* input chaine de caractère en entrée.
*@param uint pos est la position de l'apostrophe.
*
*@return tete de l'arbre contenant quote et ses arguments.
*/

object* apost(char* input, uint* pos){
	object* pair_quote = make_object();
	pair_quote->type = SFS_PAIR;

	object* quote = make_object();
	quote->type = SFS_SYMBOL;
	strcpy(quote->this.symbol, "quote");

	object* cdr_quote = make_object();
	cdr_quote->type = SFS_PAIR;
	cdr_quote->this.pair.cdr = obj_empty_list;
	cdr_quote->this.pair.car = sfs_read(input, pos);

	pair_quote->this.pair.car = quote;
	pair_quote->this.pair.cdr = cdr_quote;
	return pair_quote;
}
