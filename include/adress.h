
/**
 * @file number.h
 * @author François Cayre <cayre@yiking.(null)>
 * @date Sat Jun 23 00:42:34 2012
 * @brief Number handling.
 *
 * Number handling.
 */

#ifndef _ADRESS_H_
#define _ADRESS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "basic.h"
#include "object.h"

#define ADD_PRIMITIVE     0x00
#define ADD_FORME	      0x01
#define ADD_MEM_FORME	  0x02


typedef struct adress_t {

    uint addtype;

    union {
        object* (*prim)(object*);
        object* (*forme)(object*);
		object* (*mem_forme)(object*,object*);
    }this;

} adress;

#ifdef __cplusplus
}
#endif

#endif /* _ADRESS_H_ */
