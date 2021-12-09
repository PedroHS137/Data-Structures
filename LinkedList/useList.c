/*
 * useList.c
 *
 *  Created on: 12/04/2017
 *      Author: pjher
 */
#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
int main(){
	int a=1,b=2,c=3,d=4,e=5;
	int *t,*t1,*t2,*t3;
	List l=list_create(NULL);
	list_add(l, &a);
	list_add(l, &b);
	list_add(l, &c);
	list_add(l, &d);
	list_add(l, &e);
	t=list_get(l, 3);
	printf("%d get: ",*t);

	t1=list_get(l, 5);
	printf("%d get: ",*t1);
	t2=list_remove(l, 0);
	t3=list_remove(l,3);
	list_destroy(l);


	return 0;
}

