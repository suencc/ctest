/*
 * test.c
 *
 *  Created on: Dec 7, 2016
 *      Author: beta
 */
#include <stdio.h>
#include "treeglist.h"

int main(int argc, char* argv[]){
	//char in[] = "(A(B(C,D),E))";
	char in[] = "(A(B(E(K,L),F),C(G),D(H(M),I,J)))";
	char out[100]= {0};
	struct Node* root = NULL;
	char* tmp = out;

	printf("The input expression：%s \n ", in);

	read(in, &root);

	write(&tmp, root);
	printf("The output expression：%s \n", out);
	system("pause");
}

