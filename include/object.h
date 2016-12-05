
/**
 * @file object.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 17:49:46 2012
 * @brief Object definition for SFS.
 *
 * Object definition for SFS.
 */

#ifndef _OBJECT_H_
#define _OBJECT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "number.h"


typedef struct object_t {

    uint type;

    union {

        num              number;
        char             character;
        string           strg;
        string           symbol;
		
	struct object_t* (*fct)(struct  object_t*);

        struct pair_t {
            struct object_t *car;
            struct object_t *cdr;
        } pair;

	struct { 
		struct object_t *param;
		struct object_t *body;
		struct object_t *envt;
	} compound;

        struct object_t *special;

    }this;

} object;


object* make_object();
object* init_empty_list();
object* init_false();
object* init_true();
object* init_undef();

#define SFS_NUMBER       0x00
#define SFS_CHARACTER    0x01
#define SFS_STRING       0x02
#define SFS_PAIR         0x03
#define SFS_NIL          0x04
#define SFS_BOOLEAN      0x05
#define SFS_SYMBOL       0x06
#define SFS_ADRESS_FORME 0x07
#define SFS_UNDEF	 0x08
#define SFS_ADRESS_PRIM  0x09
#define SFS_COMPOUND	 0x0A

extern object* obj_empty_list;
extern object* obj_true;
extern object* obj_false;
extern object* obj_meta;
extern object* obj_undef;
extern object* obj_current;





#ifdef __cplusplus
}
#endif

#endif /* _OBJECT_H_ */
