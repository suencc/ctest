/*
 * aoegraph.c
 *
 *  Created on: Dec 17, 2016
 *      Author: beta
 */
#include "string.h"
#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "stack.h"

#define MAXVERTEX 128
#define MAXEDGE 128
#define MAXVEXNAME 8  //real length minus 1

#define MALLOC(p, s) \
	if(!((p) = malloc(s))){ \
		printf("Insufficient_memory"); \
		exit(EXIT_FAILURE); \
	}

typedef struct EdgeNode{
	int endVertexIndex;
	int weight;
	struct EdgeNode* next;
}EdgeNode;

typedef struct VertexNode{
	int inNum;
	char data[8];
	EdgeNode * firstedge;
}VertexNode, AdjLists[MAXVERTEX];

typedef struct{
	AdjLists adjLists;
	int edgeNum, vertexNum;
	Stack topsort;
	int etvs[MAXVERTEX];
	int ltvs[MAXVERTEX];
}Graph, *PGpraph;

EdgeNode* allocEdgeNode(){
	EdgeNode* p;
	MALLOC(p, sizeof(EdgeNode));
	p->endVertexIndex = -1;
	p->next = NULL;
	return p;
}

void freeEdgeNode(EdgeNode* p){
	free(p);
}
int getVertexIndex(Graph g, char* vexName){
	for(int i=0; i < MAXVERTEX; i++){
		if(0 == strcmp(g.adjLists[i].data, vexName))
			return i;
	}
}
void initGraph(Graph* graph){
	for(int i = 0; i < MAXVERTEX; i++){
		graph->adjLists[i].inNum = 0;
		memset(graph->adjLists[i].data, 0, MAXVEXNAME);
		graph->adjLists[i].firstedge = NULL;
	}

	graph->edgeNum = 0;
	graph->vertexNum = 0;

	InitStack(&graph->topsort);

	for (int i = 0; i < MAXVERTEX; i++){
		graph->etvs[i] = 0;
		graph->ltvs[i] = 0;
	}

}

void releaseGraph(Graph* graph){
	for(int i = 0; i < MAXVERTEX; i++){
		graph->adjLists[i].inNum = 0;
		memset(graph->adjLists[i].data, 0, MAXVEXNAME);

		EdgeNode* q, *p;
		q = graph->adjLists[i].firstedge;
		while(q != NULL){
			p = q->next;
			freeEdgeNode(q);
			q = p;
		}

		graph->adjLists[i].firstedge = NULL;
	}

	ReleaseStack(&graph->topsort);
	graph->edgeNum = 0;
	graph->vertexNum = 0;
}

void createGraph(Graph* graph){
	char vexName[MAXVEXNAME];
	int inNum;

	char beginVex[MAXVEXNAME];
	char endVex[MAXVEXNAME];
	int totalvex=0, totaledge=0;
	int weigth;

	printf("This graph most contains %d vertexs.Input total vertexs of the graph.\n", MAXVERTEX);
	scanf("%d", &totalvex);
	printf("input %d（vertex inNumber）:\n", totalvex);
	for(int i=0; i< totalvex; i++){
		scanf("%7s %d)", vexName, &inNum);

		printf("========%s, %d\n", vexName, inNum);
		strcpy(graph->adjLists[i].data, vexName);
		graph->adjLists[i].inNum = inNum;
	}
	printf("This graph most contains %d edges.Input total edges of the graph.\n", MAXEDGE);
	scanf("%d", &totaledge);
	printf("input  %d（begin end weigth）:\n", totaledge);

	int beginIndex, endIndex;
	for(int i =0; i < totaledge; i++){
		scanf("%7s %7s %d", beginVex, endVex, &weigth);
		printf("=========begin=%s, end=%s, weigth=%d\n", beginVex, endVex, weigth);

		EdgeNode* pedge = allocEdgeNode();
		beginIndex = getVertexIndex(*graph, beginVex);
		endIndex = getVertexIndex(*graph, endVex);

		pedge->endVertexIndex = endIndex;
		pedge->weight = weigth;
		pedge->next = graph->adjLists[beginIndex].firstedge;
		graph->adjLists[beginIndex].firstedge = pedge;
	}

	graph->edgeNum = totaledge;
	graph->vertexNum = totalvex;

}
void printGraph(Graph* g){
	printf("Print AOE adjacent list(vertexes=%d, edges=%d.\n", g->vertexNum, g->edgeNum);
	for(int i=0; i < g->vertexNum; i++){
		printf("%d    %s--->", g->adjLists[i].inNum, g->adjLists[i].data);

		EdgeNode* p = g->adjLists[i].firstedge;

		while(p != NULL){
			printf("[%s  %d]", g->adjLists[p->endVertexIndex].data, p->weight);
			p = p->next;
		}

		printf("\n");
	}
}

void printCritical(int beginVex, Graph* g){
	int ete, lte;
	int k;
	EdgeNode* pEdge = g->adjLists[beginVex].firstedge;

	ete = g->etvs[beginVex];
	while(pEdge){
		k = pEdge->endVertexIndex;
		lte = g->ltvs[k] - pEdge->weight;
		if(ete == lte){
			printf("<%s, %s>:%d\n", g->adjLists[beginVex].data, g->adjLists[k].data, pEdge->weight);
			printCritical(k, g);
		}
		pEdge = pEdge->next;
	}
	return;

}

bool sortTopLogic(Graph* g){
	Stack s;
	int i, k, gettop = 0;
	int count = 0;
	int* pEtv = g->etvs;

	InitStack(&s);
	ClearStack(&g->topsort);
	for(i = 0; i < MAXVERTEX; i++){
		pEtv[i] = 0;
	}

	for(i = 0; i < g->vertexNum; i++){
		if(0 == g->adjLists[i].inNum){
			Push(&s, i);
		}
	}

	printf("TopSort:");
	EdgeNode* pEdge;
	while(!IsEmpty(&s)){
		gettop = Pop(&s);
		Push(&g->topsort, gettop);
		count++;

		if(count == g->vertexNum){
			printf("%s\n", g->adjLists[gettop].data);
		}else{
			printf("%s--->", g->adjLists[gettop].data);
		}

		pEdge = g->adjLists[gettop].firstedge;
		while(NULL != pEdge){
			k = pEdge->endVertexIndex;
			g->adjLists[k].inNum--;

			if(0 == g->adjLists[k].inNum){
				Push(&s, k);
			}

			if(pEtv[gettop] + pEdge->weight > pEtv[k]){
				pEtv[k] = pEtv[gettop] + pEdge->weight;
			}

			pEdge = pEdge->next;
		}
	}

	return count == g->vertexNum;
}
void CriticalPath(Graph* g){
	EdgeNode* pEdge;
	Stack* pStack = &g->topsort;
	int i, k, gettop = 0;
	sortTopLogic(g);

	for(i = 0; i < MAXVERTEX; i++){
		g->ltvs[i] = g->etvs[g->vertexNum -1];
	}

	while(!IsEmpty(pStack)){
		gettop = Pop(pStack);
		pEdge = g->adjLists[gettop].firstedge;
		while(pEdge){
			k = pEdge->endVertexIndex;
			if(g->ltvs[k] - pEdge->weight < g->ltvs[gettop]){
				g->ltvs[gettop] = g->ltvs[k] - pEdge->weight;
			}
			pEdge = pEdge->next;
		}
	}

	//gettop is start vertex

	printf("CriticalPath:\n");
	printCritical(gettop, g);
	return;


}

int main(int argc, char* argv[]){
	Graph myg;
	initGraph(&myg);
	printf("Creating my graph.\n");
	createGraph(&myg);

	printGraph(&myg);

	//sortTopLogic(&myg);

	CriticalPath(&myg);
}
