#define _CRT_SECURE_NO_WARNINGS
#include "AD_List.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void main() {
	char inputFileName[100];
	char a, b, c;
	int count = 0;
	FILE* fp;
	GRAPH* gptr = createGraph();
	VERTEX* vtemp = NULL;

	printf("file name : ");
	scanf("%s", inputFileName);
	fp = fopen(inputFileName, "r");

	if (fp == NULL) {
		printf("failed to open file");
		exit(1);
	}
	while ((a = fgetc(fp)) != EOF) {
		if ((a != ' ') && (a != '\n')) {
			if (FindVertex(gptr, a) == NULL)
				InsertVertex(gptr, a);
		}
	}
	fseek(fp, 0, SEEK_SET);
	fgetc(fp);
	
	while ((a = fgetc(fp)) != EOF) {
		if ((a != ' ') && (a != '\n')) {
			if (count == 0) {
				b = a;
				count = 1;
			}
			else if (count == 1) {
				c = a;
				count = 2;
			}
			if (count == 2) {
				InsertArc(gptr, b, c);
				count = 0;
			}
		}
	}
	printf("\n");
	printf("The graph is : \n");
	PrintGraph(gptr);
	printf("\n");

	printf("Depth First Traversal : ");
	fseek(fp, 0, SEEK_SET);
	a = fgetc(fp);
	if ((a != ' ') && (a != '\n'))
		DepthFirstTraversal(FindVertex(gptr, a));
	printf("\n");
	ClearVisit(gptr);
	printf("\n");

	printf("Breadth First Traversal : ");
	fseek(fp, 0, SEEK_SET);
	a = fgetc(fp);
	if ((a != ' ') && (a != '\n'))
		BreadthFirstTraversal(gptr, a);
	ClearVisit(gptr);
	destroyGraph(gptr);
	fclose(fp);
}
