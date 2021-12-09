/*
 ============================================================================
 Name        : linkedList.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

struct strNode{
	Type data;
	struct strNode *prior, *next;
};

struct strList{
	int size;
	struct strNode *first, *last;
	struct strNode *preFirst, *postLast;
	void (*destructor)(Type);
};

List list_create(void (*destructor)(Type)){
	List l=malloc(sizeof(struct strList));
	l->preFirst=malloc(sizeof(struct strNode));
	l->postLast=malloc(sizeof(struct strNode));
	l->destructor=destructor;
	return l;

}
void list_destroy(List l){
	Node a=l->preFirst;
	Node t;
	while(a!=NULL){
		t=a;
		a=a->next;
		free(t);
	}
	free(l);
}
int  list_size(List l){
	return l->size;
}
void list_add(List l, Type t){
	Node a=malloc(sizeof(struct strNode));
	a->data=t;
	if(l->size==0){
			l->first = a;
			l->first->prior = l->preFirst;
			l->preFirst->next = l->first;
		}
	else{
		l->last->next=a;
		a->prior=l->last;
	}

	l->last = a;
	l->last->next = l->postLast;
	l->postLast->prior = l->last;
	l->size++;
}
Type list_get(List l, int p){
	if(p >= l->size)
			return NULL;

		int i;
		Node actual = l->first;

		for(i=0; i<p; i++)
			actual = actual->next;

		return actual->data;
}
void list_set(List l, Type t, int p){
	if(p >= l->size){
			return ;
	}

		int i;
		Node current = l->first;

		for(i=0; i<p; i++){
			current = current->next;
		}

		current->data = t;

}
Type list_remove(List l, int p){

	if(p >= l->size){
			return NULL;
	}
		int i;
		Node current = l->first;

		for(i=0; i<p; i++)
			current = current->next;

		Type t = current->data;

		if(current->prior != NULL)
			current->prior->next = current->next;

		if(current->next != NULL)
			current->next->prior = current->prior;


		if(p == 0){
			l->first = l->first->next;
			l->first->prior = l->preFirst;
			l->preFirst->next = l->first;
		}

		if(p == l->size - 1){
			l->last = l->last->prior;
			l->last->next = l->postLast;
			l->postLast->prior = l->last;
		}

		free(current);
		l->size--;
		return t;
}

Iterator list_begin(List l){
	return l->preFirst;
}
Iterator list_end(List l){
	return l->postLast;
}
bool list_hasNext(Iterator i){
	if(i->next!=NULL){
		return True;
	}
	return False;
}
bool list_hasPrior(Iterator i){
	if(i->prior!=NULL){
			return True;
		}
		return False;
}
Iterator list_next(Iterator i){
	return i->next;
}
Iterator list_prior(Iterator i){
	return i->prior;
}
Type list_data(Iterator i){
	return i->data;
}
