/*
 * smalltopheap.c
 *
 *  Created on: Dec 22, 2016
 *      Author: beta
 */

#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"

#define MAX_ELEMENTS 200
#define IS_FULL(n) ((n) == MAX_ELEMENTS)
#define IS_EMPTY(n) (!(n))

typedef unsigned int UINT;

typedef struct{
	int key;
	char value[16];
}Element;

typedef struct{
	Element elements[MAX_ELEMENTS];
	UINT num;
}Heap;

bool isEmpty(Heap* heap){
	return IS_EMPTY(heap->num);
}

Element top(Heap* heap){
	return heap->elements[1];
}

Element pop(Heap* heap){
	UINT parent, child;
	Element item, tmp;

	if(isEmpty(heap)){
		printf("the heap is empty, cant't be pop\n");
		exit(EXIT_FAILURE);
	}

	item = heap->elements[1];
	tmp = heap->elements[heap->num--];

	parent = 1;
	child = 2;

	while(child <= heap->num){

		if(child < heap->num && heap->elements[child].key > heap->elements[child+1].key){
			child++;
		}

		if(tmp.key <= heap->elements[child].key){
			break;
		}

		heap->elements[parent] = heap->elements[child];
		parent = child;
		child *= 2;

	}
	heap->elements[parent] = tmp;
	return item;

}

Heap push(Heap* heap, Element item){
	int i;
	if(IS_FULL(heap->num)){
		printf("the heap is full.\n");
		exit(EXIT_FAILURE);
	}

	i = ++(heap->num);

	while(i > 1 && item.key < heap->elements[i/2].key){
		heap->elements[i] = heap->elements[i/2];
		i = i/2;
	}

	heap->elements[i] = item;

	return *heap;
}
int main(int argc, char* argv[]){
	Element item;

	Heap smallTop = {.num =0};
	printf("Creating small top heap.\n");
	printf("please input(id name).\n");
	for(int i = 0; i < 7; i++){
		scanf("%d %s", &item.key, item.value);
		push(&smallTop, item);
		//printf("current top:id %d, name %s\n", top(&smallTop).key, top(&smallTop).value);
	}

	printf("output in order:\n");
	while(!isEmpty(&smallTop)){
		item = pop(&smallTop);
		printf("id=%d  name=%s\n", item.key, item.value);

		//printf("current top:id %d, name %s\n", top(&smallTop).key, top(&smallTop).value);
	}

}
