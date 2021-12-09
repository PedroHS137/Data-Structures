/*
 ============================================================================
 Name        : Set.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Set.h"

struct strNode {
	Type data;
	struct strNode *left, *right, *parent;
};

struct strSet {
	struct strNode *root;	//desde la raíz llegamos a cualquier elemento
	int size;
	CompareFunc compareFunc;
	PrintFunc printFunc;
	DestroyFunc destroyFunc;
};

Set set_create(CompareFunc cf, PrintFunc pf, DestroyFunc df){
	Set s=malloc(sizeof(struct strSet));
	s->compareFunc=cf;
	s->printFunc=pf;
	return s;
}
int set_size(Set s){
	return s->size;
}
bool set_add(Set s, Type t){
	Node n=malloc(sizeof(struct strNode));
	n->data=t;

	if(s->size==0){
		s->root=n;
	}
	else{
		Node actual=s->root;
		Node anterior;
		int amigat;
		while(actual!=NULL){
			amigat=s->compareFunc(actual->data,t);
			if(amigat==0){
				free(n);
				return FALSE;
			}
			else{
				anterior=actual;
				if(amigat>0){
					actual=actual->left;
				}
				else{
					actual=actual->right;
				}
			}
			addLink(anterior,n,amigat>0);
		}

	}
	s->size++;
	return TRUE;
}
bool set_contains(Set s, Type t){
	Node current;
		int status;
		if(s){
			current=s->root;
			while(current!=NULL){
				status=s->compareFunc(current->data, t);
				if(status==0)
					return TRUE;
				else{
					if(status>0)
						current=current->left;
					else
						current=current->right;
				}
			}
		}
		return FALSE;
}
void set_destroy(Set s){
	destroy(s->root);
	free(s);
}
bool set_remove(Set s, Type t){
	Node n=set_contains(s,t);
	if(n==NULL){
			return FALSE;
	}
		bool esHijoIzq = FALSE;
		if(n->parent != NULL)
			esHijoIzq = n->parent->left == n;

		removeBranch(s, n, esHijoIzq);

		s->size--;
		return TRUE;

}
void set_print(Set s){
	print(s->root, s->printFunc);
		printf("\n");
}

void addLink(Node padre, Node hijo, bool esHijoIzq){
	if(esHijoIzq){
			padre->left = hijo;
	}
		else{
			padre->right = hijo;
		}
		if(hijo!=NULL){
			hijo->parent = padre;
		}
}

void destroy(Node node, DestroyFunc df){
	if(node!=NULL){
			destroy(node->left,df);
			destroy(node->right,df);
			free(node);
		}
}
void print(Node n, PrintFunc pf){
	if(n!=NULL){
			printf("{");
			pf(n->data);
			print(n->left, pf);
			print(n->right, pf);
			printf("}");
		}
}
void removeBranch(Set s, Node n, bool esHijoIzq){
	if(n->left == NULL && n->right == NULL){ //es hoja
			if(n==s->root){
				s->root = NULL;
			}
			else{
				Node p = n->parent;
				addLink(p, NULL,esHijoIzq);
			}

			free(n);
		}
	 if(n->left != NULL && n->right == NULL){  //tiene hijo izquierdo
			if(n==s->root){
				s->root = n->left;
			}
			else{
				Node p = n->parent;
				addLink(p, n->left, esHijoIzq);
			}
			free(n);
		}
	 if(n->left == NULL && n->right != NULL){ // hijo derecho
	 		if(n==s->root){
	 			s->root = n->right;
	 		}
	 		else{
	 			Node p = n->parent;
	 			addLink(p, n->right, esHijoIzq);
	 		}

	 		free(n);
	 	}
	 else{
		 Node act=n;
		 Node prev;

		while(act!=NULL){
		 	prev=act;
		 	act=act->right;
		 	}

		 	 Node m=prev;

		 	 n->data=m->data;
		 	 Node t=m->parent;

		 	if(t==n || t==s->root){
		 		addLink(t, m->left, TRUE);
		 	}
		 	else{
				addLink(t, m->left, FALSE);
		 	}

		 	free(m);
	 }
}
