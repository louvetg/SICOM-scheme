
/**
 * @file read.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:30:11 2012
 * @brief Read routine for SFS.
 *
 * Read routine for SFS.
 */

#ifndef _READ_H_
#define _READ_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <errno.h>
#include "object.h"
#include <limits.h>

enum { S_OK, S_KO, S_END };

uint   sfs_get_sexpr(string input, FILE *fp);

object* sfs_read( char *input, uint *pos );
object* read_atom( char *input, uint *pos );
object* read_pair( char *input, uint *pos );
void Delete_space(char* input);
void Verif_Num(char* input, uint pos, char* Num);
void init_chaine(char* chaine, int a);
object* make_integer(char* Num, object* obj_Num);
void Verif_strg(char* input, uint pos, char* strg);
object* make_string(char* strg, object* obj_strg);
void Verif_Chara(char* input, uint pos, char* chara);
object* make_chara(char *chara, object* obj_chara);
object* make_symb(char* symb, object* obj_symb);
void Verif_symb(char* input, int pos, char* symb);
uint test_string(uint k, char* input);
uint test_taille_uint(char* num);
object* apost(char* input, uint* pos);

#ifdef __cplusplus
}
#endif

#endif /* _READ_H_ */
