/*
 * tree.h
 *
 *  Created on: Nov 16, 2016
 *      Author: beta
 */

#ifndef TREE_H_
#define TREE_H_
#include <stdlib.h>

#define OK 0
#define ERROR -1
#define TRUE 1
#define FALSE 0
#define MAX_TREE_SIZE 1024


#define MALLOC(p, s) \
	if(!((p) = malloc(s))){ \
		printf("Insufficient_memory"); \
		exit(EXIT_FAILURE); \
	}

//#include <stdbool.h>

struct Node{
	//tag == 0 data-hp; tag == 1 hp-tp
	int tag;
	struct Node* hp;
	union{
		char data;
		struct Node* tp;
	};
};

int read(char* pstr, struct Node** root);
int write(char** pstr, struct Node* root);

/*
struct Tree{
	struct Node* root;
	int (*read)(char* pstr, struct Node* root);
	int (*write)(char* strBuff, struct Tree tree);
	bool (*isequal)(struct Tree tree1, struct Tree tree2);
	int (*copy)(struct Tree srcTree, struct Tree dstTree);
	int (*clear)(struct Tree tree);
};*/


#endif /* TREE_H_ */
