#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int vertex;
    struct node* next;
} node;

node* createNode(int);

typedef struct AdjList {
    int numVerticies;
    struct node** adjLists;
} AdjList;

AdjList* createAdjList(int v);

int* alloc(int* mat, int rows, int cols);
void deallocList(node **lists, int v);

// add src to dest
void addEdge(AdjList* adjList, int src, int dest);

AdjList* inputAdjList(AdjList* adjList);
void inputMat(int* mat, int rows, int cols);

void printMat(int* mat, int rows, int cols);
void printAdjList(AdjList* AdjList);

int* incToAdjMat(int* inc, int v, int e);
int* adjListToInc(AdjList* adjList, int e);
AdjList* adjMatAdjList(int* adjMat, int v);

void convertFromInc(void);
void convertFromAdj(void);
void convertFromList(void);

int countInList(AdjList* adjList);

int main(void) {

	int choice;
	
	printf("1.\tInput Adjacency Matrix \n");
	printf("2.\tInput Incedence Matrix \n");
	printf("3.\tInput Adjacency List \n");
	
	do {
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				convertFromAdj();
				break;
			case 2:
				convertFromInc();
				break;
			case 3:
				convertFromList();
				break;
			default:
				printf("Are you sure that you pressed right key? \n");
			}
	} while (choice > 3 || choice < 1);

  return 0;
}

node* createNode(int v) {
	node* newNode = malloc(sizeof(struct node));
	newNode -> vertex = v;
	newNode -> next = NULL;
	return newNode;
}

AdjList* createAdjList(int v) {
    
	AdjList* AdjList = malloc(sizeof(AdjList));
	AdjList -> numVerticies = v;

	AdjList -> adjLists = malloc(v * sizeof(node*));

	for (int i = 0; i < v; i++) {
		AdjList -> adjLists[i] = NULL;
	}

	return AdjList;
}

// add edge from src to dest
void addEdge(AdjList* AdjList, int src, int dest) {
	node* newNode = createNode(dest);
	newNode -> next = AdjList -> adjLists[src];
	AdjList -> adjLists[src] = newNode;
}

void printAdjList(AdjList* AdjList) {
	int v;
	for (v = 0; v < AdjList -> numVerticies; v++) {
		node* temp = AdjList -> adjLists[v];
		printf("%d -> ", v + 1);
		while (temp) {
			printf("%d ", temp -> vertex);
			temp = temp -> next;
		}
		printf("\n");
	}
}

// col major
int* alloc(int *mat, int rows, int cols) {
  mat = calloc(rows * cols, sizeof(int));
  return mat;
}

void inputMat(int* mat, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			scanf("%d", &*(mat + cols * i + j));
		}
		printf("-------\n");
	}
}

void printMat(int* mat, int rows, int cols) {
    
		printf("Printing matrix \n");

    for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				printf("%3d", *(mat + cols * i + j));
			}
      printf("\n");
    }

}

AdjList* inputAdjList(struct AdjList* adjList) {

	int v = adjList -> numVerticies;
	int n;

	int elCo = 0;

	for (int i = 0; i < v; i++) {
		printf("How many edges do you want to add? \n");
		scanf("%d", &elCo);
		for (int j = 0; j < elCo; j++) {
			printf("add: ");
			scanf("%d", &n);
			printf("[%d] -> %d \n", i + 1, n);
			addEdge(adjList, i, n);
		}
	}

	printAdjList(adjList);
	return adjList;
}

// Incedence to Adjacency Matrix
int* incToAdjMat(int* inc, int v, int e) {
    
	int idxP = 0, idxM = 0;
	int currValue;

	int* adjMat = NULL;
	adjMat = alloc(adjMat, v, v);

	for (int i = 0; i < e; i++) {
		for (int j = 0; j < v; j++) {
			currValue = *(inc + v * i + j);
			if (currValue == 2) idxP = idxM = j;
			if (currValue == -1) idxM = j;
			if (currValue == 1) idxP = j;
		}

		*(adjMat + v * idxM + idxP) = 1;
	}

	free(inc);
	return adjMat;
}

// Adjacency Matrix to Adjacency List
AdjList* adjMatAdjList(int* adjMat, int v) {

	AdjList* adjList = createAdjList(v);

	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			if (*(adjMat + v * i + j)) {
					addEdge(adjList, i, j + 1);
			}
		}
	}
        
  free(adjMat);
  return adjList;
}

// Adjacency List to Incedence Matrix
int* adjListToInc(AdjList* adjList, int e) {
    
	int v = adjList -> numVerticies;
	
	int* inc = NULL;
	inc = alloc(inc, e, v);
	
	node *tmp;

	int k = 0;
	for (int i = 0; i < v; i++) {
		tmp = adjList-> adjLists[i];
		while (tmp) {
			if ((tmp -> vertex) - 1 == i) {
				*(inc + k * v + i) = 2;
			} else {
				*(inc + k * v + i) = -1;
				*(inc + k * v + (tmp -> vertex - 1)) = 1;
			}
			tmp = tmp -> next;
			k++;
		}
	}
	
	deallocList(adjList -> adjLists, v);
	return inc;
}

void convertFromInc(void) {
    
	int* mat = NULL;
	AdjList* adjList = NULL;

	int v, e;
	int n;

	printf("Number of verticies: ");
	scanf("%d", &v);

	printf("Number of edges: ");
	scanf("%d", &e);
	
	mat = alloc(mat, e, v);
	inputMat(mat, e, v);
	
	printf("To which you want to convert? \n");
	printf("1\tAdjacency Matrix \n");
	printf("2\tAdjacency List \n");
	
	do {
		printf("Choose: ");
		scanf("%d", &n);
	} while (n <= 0 || n > 2);
	
	switch (n) {
		case 1:
			mat = incToAdjMat(mat, v, e);
			printMat(mat, v, v);
			break;
		case 2:
			mat = incToAdjMat(mat, v, e);
			adjList = adjMatAdjList(mat, v);
			printAdjList(adjList);
			break;
	}

	deallocList(adjList->adjLists, v);
	free(mat);
}

void convertFromList(void) {
    
	int* mat = NULL;
	AdjList* adjList;

	int v, e;
	int n;

	printf("Number of verticies: ");
	scanf("%d", &v);
	
	adjList = createAdjList(v);
	inputAdjList(adjList);
	e = countInList(adjList);
	
	printf("To which you want to convert? \n");
	printf("1\tIncedence Matrix \n");
	printf("2\tAdjacency Matrix \n");
	
	do {
		printf("Choose: ");
		scanf("%d", &n);
	} while (n <= 0 || n > 2);
	
	switch (n) {
		case 1:
			mat = adjListToInc(adjList, e);
			printMat(mat, e, v);
			break;
		case 2:
			mat = adjListToInc(adjList, e);
			mat = incToAdjMat(mat, v, e);
			printMat(mat, v, v);
			break;
	}

  deallocList(adjList -> adjLists, v);
  free(mat);
}

void convertFromAdj(void) {
    
	int* mat = NULL;
	AdjList* adjList;

	int v, e;
	int n;

	printf("Number of verticies: ");
	scanf("%d", &v);

	mat = alloc(mat, v, v);
	inputMat(mat, v, v);
	
	printMat(mat, v, v);
	
	printf("To which you want to convert? \n");
	printf("1\tIncedence Matrix \n");
	printf("2\tAdjacency List \n");
	
	do {
		printf("Choose: ");
		scanf("%d", &n);
	} while (n <= 0 || n > 2);
	
	switch (n) {
		case 1:
			adjList = adjMatAdjList(mat, v);
			e = countInList(adjList);
			mat = adjListToInc(adjList, e);
			printMat(mat, e, v);
			break;
		case 2:
			adjList = adjMatAdjList(mat, v);
			printAdjList(adjList);
			deallocList(adjList -> adjLists, v);
			break;
		}

	free(mat);
}

int countInList(AdjList* adjList) {
	
	int k = 0;
	node* tmp;

	int v = adjList -> numVerticies;

	for (int i = 0; i < v; i++) {
		tmp = adjList -> adjLists[i];
		while (tmp) {
			tmp = tmp -> next;
			k++;
		}
	}
	
	return k;
}

void deallocList(node **list, int v) {
	node *tmp;
	for (int i = 0; i < v; i++) {
		node* currList = list[i];
		while (currList) {
			tmp = currList;
			currList = currList -> next;
			free(tmp);
		}
	}
			
	printf("list was deallocated \n");
}
    
