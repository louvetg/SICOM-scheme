
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


		struct adress_t {

			uint addtype;

			union {
				struct  object_t* (*prim)(struct  object_t*);
				struct object_t* (*forme)(struct  object_t*);
				struct object_t* (*mem_forme)(struct  object_t*, struct  object_t*);
			}this;

		} adress;

        struct pair_t {
            struct object_t *car;
            struct object_t *cdr;
        }                pair;

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
#define SFS_ADRESS		 0x07
#define SFS_UNDEF		 0x08

#define ADD_PRIMITIVE     0x00
#define ADD_FORME	      0x01
#define ADD_MEM_FORME	  0x02

extern object* obj_empty_list;
extern object* obj_true;
extern object* obj_false;
extern object* obj_meta;
extern object* obj_undef;

object* obj_cpy(object*);


typedef struct adress_t adress;

#ifdef __cplusplus
}
#endif

#endif /* _OBJECT_H_ */
