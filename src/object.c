
/**
 * @file object.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:02:57 2012
 * @brief Object definitions for SFS.
 *
 * Object definitions for SFS.
 */

#include "object.h"
#include "mem.h"



object* make_object(){
	return calloc(1, sizeof(object));	
}


object* init_empty_list() {
	object* a = calloc(1, sizeof(object));
	a->type = SFS_NIL;
	a->this.special = a;
	return a;
}

object* init_false(){
	object* a = calloc(1, sizeof(object));
	a->type = SFS_BOOLEAN ;
	a->this.number.this.integer = FALSE;
	a->this.number.numtype = NUM_INTEGER;
	return a;
}

object* init_true(){
	object* a = calloc(1, sizeof(object));
	a->type = SFS_BOOLEAN;
	a->this.number.this.integer = TRUE;
	a->this.number.numtype = NUM_INTEGER;
	return a;
}

object* init_undef(){
	object* a = calloc(1, sizeof(object));
	a->type = SFS_UNDEF;
}

/*object* obj_cpy(object* o){
	if (o == obj_empty_list){ return obj_empty_list; }
	if (o == obj_true){ return obj_true; }
	if (o == obj_false){ return obj_false; }
	if (o == obj_meta){ return obj_meta; }
	if (o == obj_undef){ return obj_undef; }
	object* obj;
	obj = make_object();
	obj->type = o->type;
	if (o->type != SFS_PAIR){
			obj->this = o->this;
	}
	else{
		
		obj->this.pair.car = obj_cpy(car(o));
		obj->this.pair.cdr = obj_cpy(cdr(o));
		
	}
	return obj;
}*/
