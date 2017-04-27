/*
 * treeglist.c
 *
 *  Created on: Nov 15, 2016
 *      Author: beta
 */
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "treeglist.h"

_Bool isEmpty(char* pstr){
	return !strlen(pstr);
}

_Bool isValidLists(char* pstr){
	int left = 0, right =0;
	_Bool result = 1;
	char* pstore = pstr;

	if(pstr == NULL || strlen(pstr) >= MAX_TREE_SIZE)
		return 0;

	//if(*pstr != '(' && *(pstr+1) != '(')
	//	result = 0;

	for(; *pstr != 0; pstr++){
		switch(*pstr){
		case '(':
			left++;
			break;
		case ')':
			right++;
			break;
		default:
			break;
		}
	}

	if(left != right)
		result = 0;

	printf("Lists = %s result = %d \n", pstore, result);
	return result;
}

int spitHeadTail(char* pstr, char* phead, char* ptail){
	int i, hIndex, tIndex;
	int depth = 0;

	if(pstr == NULL || phead == NULL ||ptail == NULL){
		return ERROR;
	}


	if(pstr[0] == '('){
		depth = 1;
	}else{
		return ERROR;
	}

	hIndex = 0;
	tIndex = 0;
	phead[0] = 0;
	ptail[0] = 0;

	for(i = 1; pstr[i] != 0; i++){
		if(pstr[i] == '('){
			depth++;
			phead[hIndex++] = pstr[i];
		}else if(pstr[i] ==  ')'){
			depth--;
			phead[hIndex++] = pstr[i];
		}else if(pstr[i] ==  ','){
			if(depth == 1){
				phead[hIndex] = 0;
				i++;
				break;
			}else{
				phead[hIndex++] = pstr[i];
			}
		}else{
			phead[hIndex++] = pstr[i];
		}
	}


	if(depth == 0 || pstr[i] == 0){
		phead[hIndex-1] = 0;
		printf("head = %s \n", phead);
		return OK;
	}

	ptail[tIndex++] = '(';
	for(; pstr[i] != 0; i++){
		ptail[tIndex++] = pstr[i];
	}
	ptail[tIndex++] = 0;
	printf("head = %s \n", phead);
	printf("tail = %s \n", ptail);
	return OK;

}

int read(char* pstr, struct Node** root){
	char head[MAX_TREE_SIZE];
	char tail[MAX_TREE_SIZE];


	struct Node* pdataNode = NULL;
	struct Node* plinkNode = NULL;

	if(!isValidLists(pstr)){
		return ERROR;
	}

	//format A(B(C,D),E)
	if(pstr[0] != '('){
		MALLOC(pdataNode, sizeof(struct Node))
		*root = pdataNode;
		pdataNode->tag = 0;
		pdataNode->data = *pstr++;
		pdataNode->hp = NULL;
		if(*pstr == '('){
			return read(pstr, &(pdataNode->hp));
		}else{
			printf("recurce end \n");
			return OK;
		}
	}

	//format (A(B(C,D),E))
	MALLOC(plinkNode, sizeof(struct Node))
	*root = plinkNode;
	plinkNode->tag = 1;
	plinkNode->hp = NULL;
	plinkNode->tp = NULL;

	spitHeadTail(pstr, head, tail);

	if(!isEmpty(head)){
		read(head, &(plinkNode->hp));
	}

	if(!isEmpty(tail)){
		read(tail, &(plinkNode->tp));
	}
}

int write(char** pstr, struct Node* root){
	if(root == NULL || pstr == NULL){
		printf("NUll pointer.\n");
		return ERROR;
	}

	if(root->tag == 0){
		**pstr = root->data;
		(*pstr)++;
		if(root->hp != NULL){
			write(pstr, root->hp);
		}else{
			return OK;
		}
	}else{
		//first link node in the layer
		**pstr = '(';
		(*pstr)++;
		write(pstr, root->hp);

		struct Node* link = root->tp;
		while(link != NULL && link->tag == 1){
			**pstr = ',';
			(*pstr)++;
			write(pstr, link->hp);
			link = link->tp;
		}

		//end link node in the layer
		**pstr = ')';
		(*pstr)++;
	}
	**pstr = 0;
	return OK;
}
