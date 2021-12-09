/*
 * linkedList.h
 *
 *  Created on: 12/04/2017
 *      Author: pjher
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef enum {False,True} bool;
typedef struct strNode * Node;
typedef struct strList * List;
typedef void * Type;
typedef Node Iterator;

List list_create(void (*destructor)(Type));
void list_destroy(List);
int  list_size(List);
void list_add(List, Type);
Type list_get(List, int p);
void list_set(List, Type, int p);
Type list_remove(List, int p);

Iterator list_begin(List);
Iterator list_end(List);
bool list_hasNext(Iterator);
bool list_hasPrior(Iterator);
Iterator list_next(Iterator);
Iterator list_prior(Iterator);
Type list_data(Iterator);



#endif /* LINKEDLIST_H_ */
