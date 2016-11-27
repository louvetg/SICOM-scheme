
/**
 * @file print.c
 * @author Gaspard LOUVET 
 * @date Tues sept 27 23:55 2016
 * @brief Printing stuff for SFS.
 *
 * Printing stuff for SFS.
 */

#include "print.h"
#include <stdio.h>


/**
 *@fn void sfs_print_atom(object* o)
 *
 *@brief Affiche l'atome dans la sortie standard
 *
 *@param object* Objet contenant l'atome à afficher
 *
 *
 */
 
void sfs_print_atom(object* o) {
	if (o->type == SFS_BOOLEAN){
		if (o->this.number.this.integer == 1){ printf("#t"); }
		if (o->this.number.this.integer == 0){ printf("#f"); }
	}
	if (o->type == SFS_CHARACTER){
		if(o->this.character == ' '){printf("#\\space");return;}
		if(o->this.character == '\n'){printf("#\\newline");return;} 
		else {printf("#\\%c",o->this.character); }
	}
	if (o->type == SFS_NIL){ printf(")"); }
	if (o->type == SFS_NUMBER){ 
		printf("%d",o->this.number.this.integer);
	}
	if (o->type == SFS_STRING){ printf("\"%s\"", o->this.strg); }
	if (o->type == SFS_SYMBOL){ printf("%s", o->this.strg); }
	if (o->type == SFS_UNDEF){ printf("#<undef>"); }

	return;
}

/**
 *@fn void sfs_print_pair(object* o)
 *
 *@brief Si l'object est une paire, alors on ouvre une parenthèse. Dans tous les cas,
 *  On affiche le car de l'expression considéré. Si l'expression est NIL, alors on met un " "
 * 	puis on affiche le cdr de l'expression. 
 *
 *@param object* Objet contenant la paire à afficher 
 *
 * */

void sfs_print_pair(object* o) {
	if (SFS_PAIR == o->this.pair.car->type){ printf("("); }
	if (SFS_NIL == o->this.pair.car->type){ printf("(");}
	sfs_print_b(o->this.pair.car);
	if(o->this.pair.cdr->type != SFS_NIL){printf(" ");}
	if (o->this.pair.cdr->type != SFS_PAIR && o->this.pair.cdr != obj_empty_list){ 
		printf(". "); 
		sfs_print_b(o->this.pair.cdr);
		printf(")");
	}
	else(sfs_print_b(o->this.pair.cdr));
	return;
}

/**
 *@fn void sfs_print_b(object* o)
 *
 *@brief Détermine si l'expression considérée est une paire ou un atome.
 *
 *@param object* Objet contenant l'expression à afficher
 *
 * */
 
void sfs_print_b(object* o) {
	
	if (SFS_PAIR == o->type) {
		sfs_print_pair(o);
	}
	else {
		sfs_print_atom(o);
	}
	return;
}

/**
 *@fn void sfs_print(object* o)
 *
 *@brief Si l'expression correspond à une paire, ou à NIL, alors on ouvre une "("
 *  Dans tous les cas, on appelle la fonction sfs_print_b.
 *
 *@param object* Objet contenant la s-expression à afficher
 *
 * */
 
void sfs_print(object* o){
	if(o->type == SFS_PAIR || o->type == SFS_NIL ){printf("(");}
	sfs_print_b(o);
}

