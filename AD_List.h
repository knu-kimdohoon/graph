#include "Ad_Queue.h"

typedef struct graph {
	int count;
	struct vertex* headVertex;
	int (*compare)(void* argu1, void* argu2);
}GRAPH;

typedef struct vertex {
	struct vertex* pnextVertex;
	void* dataPtr;
	int inDegree;
	int outDegree;
	bool visited;
	struct arc* pArc;
}VERTEX;

typedef struct arc {
	VERTEX* destination;
	struct arc* pNextArc;
}ARC;

int compareChar(void* argu1, void* argu2) {
	char a = *(char*)argu1;
	char b = *(char*)argu2;
	return (int)(a)-(int)(b);
}

GRAPH* createGraph() {
	GRAPH* gptr = (GRAPH*)malloc(sizeof(GRAPH));
	if (gptr == NULL) {
		printf("failed to create graph");
		return NULL;
	}
	gptr->count = 0;
	gptr->headVertex = NULL;
	gptr->compare = compareChar;
	return gptr;
}

VERTEX* FindVertex(GRAPH* gptr, char data) {
	VERTEX* found = NULL;
	found = gptr->headVertex;
	char check = '\0';
	for (int i = 0; i < gptr->count; i++) {
		check = *(char*)found->dataPtr;
		if (check == data)
			return found;
		else
			found = found->pnextVertex;
	}
	return NULL;
}

int InsertVertex(GRAPH* gptr, char data) {
	int flag = 0;
	VERTEX* newVertex = (VERTEX*)malloc(sizeof(VERTEX));
	VERTEX* temp = NULL, * pre = NULL;
	if (newVertex == NULL) {
		printf("failed to create vertex\n");
		return 1;
	}
	newVertex->dataPtr = (void*)data;
	printf("%c\n", *(char*)newVertex->dataPtr);
	newVertex->pnextVertex = NULL;
	newVertex->pArc = NULL;
	newVertex->inDegree = 0;
	newVertex->outDegree = 0;
	newVertex->visited = false;

	if (gptr->count == 0) {
		gptr->headVertex = newVertex;
		gptr->count = 1;
	}
	else {
		temp = gptr->headVertex;
		for (int i = 0; i < gptr->count; i++) {
			flag = gptr->compare(&temp->dataPtr, &data);
			if (flag==0) {
				printf("%c is already in Graph\n", data);
				return 2;
			}
			else if (flag< 0) {
				pre = temp;
				temp = temp->pnextVertex;
			}
			else if (flag > 0) {
				newVertex->pnextVertex = temp;
				if (i == 0)
					gptr->headVertex = newVertex;
				else
					pre->pnextVertex = newVertex;
				gptr->count++;
				return 0;
			}
		}
		pre->pnextVertex = newVertex;
		gptr->count++;
		return 0;
	}
}

void destroyGraph(GRAPH* gptr) {
	ARC* dltArc = NULL, *dltArc2=NULL;
	VERTEX* dltVertex = NULL, *dltVertex2=NULL;
	int i = 0, j = 0;
	for (dltVertex = gptr->headVertex; dltVertex!=NULL; dltVertex=dltVertex2) {
		j = 0;
		for (dltArc = dltVertex->pArc; dltArc != NULL; dltArc = dltArc2) {
			dltArc2 = dltArc->pNextArc;
			printf("[%d] %c [%d]", i, (char*)dltArc->destination->dataPtr, j++);
			free(dltArc);
		}
		dltVertex2 = dltVertex->pnextVertex;
		printf("[%d]\n", i++);
		free(dltVertex);
	}
	free(gptr);
}
/*
int InsertArc(GRAPH* gptr, char start, char dest) {
	VERTEX* startVertex = NULL;
	VERTEX* destVertex = NULL;
	ARC* nowArc = NULL;
	ARC* preArc = NULL;
	ARC* newArc = (ARC*)malloc(sizeof(ARC));
	if (newArc == NULL) {
		printf("failed to create arc\n");
		return 1;
	}
	startVertex = FindVertex(gptr, start);
	destVertex = FindVertex(gptr, dest);
	newArc->destination = destVertex;
	newArc->pNextArc = NULL;
	nowArc = startVertex->pArc;
	preArc = startVertex->pArc;
	if (nowArc == NULL) {
		startVertex->pArc = newArc;
		startVertex->outDegree++;
		destVertex->inDegree++;
	}
	else {
		for (int i = 0; i < startVertex->outDegree; i++) {
			int check = gptr->compare(&nowArc->destination->dataPtr, &dest);
			if ( check == 0) {
				printf("%c to %c Arc is already in graph\n", start, dest);
				return 2;
			}
			else if (check < 0) {
				preArc = nowArc;
				nowArc = nowArc->pNextArc;
			}
			else if (check > 0) {
				newArc->pNextArc = nowArc;
				if (i == 0)
					startVertex->pArc = newArc;
				else
					preArc->pNextArc = newArc;
				startVertex->outDegree++;
				destVertex->inDegree++;
			}
		}
		preArc->pNextArc = newArc;
		startVertex->outDegree++;
		destVertex->inDegree++;
		return 0;
	}
}
*/