#include <stdio.h>
#include <stdlib.h>

struct LinkedList {
  int data;
  struct LinkedList* next;
};

typedef struct LinkedList* Node;

Node createNode(void);

void append(Node* head, int value);
void prepend(Node* head, int value);
void insert(Node* head, int value, int index);
void insertOrdered(Node* head, int value);
void removeNode(Node* head, int value);
void insertionSort(Node* head);
void reverseList(Node* head);
void swapNodes(Node* head, int firstVal, int secondVal);

void editNode(Node* head, int newValue, int position);
void findNode(Node* head, int value);
void countNodes(Node head);
void getAddress(Node head);

void printList(Node head);
void printAddresses(Node head);
void printChoices(void);

void dealloc(Node* head);

void writeList(Node* head);
void readFile(Node* head);

void splitList(Node* head, Node* head0, int idx);
void joinLists(Node* head, Node* head0);

int main(int argc, const char * argv[]) {
    
	Node head = NULL;
	Node head0 = NULL;
 	
	int choice, value;
	int idx, idxS;

	printChoices();
	
	while (1) {
		printf("Your choice: ");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				printf("Value: ");
				scanf("%d", &value);
				append(&head, value);
				break;
			case 2:
				printf("Value: ");
				scanf("%d", &value);
				prepend(&head, value);
				break;
			case 3:
				printf("Value: ");
				scanf("%d", &value);
				printf("Index: ");
				scanf("%d", &idx);
				insert(&head, value, idx);
				break;
			case 4:
				printf("Value: ");
				scanf("%d", &value);
				insertOrdered(&head, value);
				break;
			case 5:
				printf("Value: ");
				scanf("%d", &value);
				removeNode(&head, value);
				break;
			case 6:
				insertionSort(&head);
				break;
			case 7:
				reverseList(&head);
				break;
			case 8:
				printf("Value of first node: ");
				scanf("%d", &idx);
				printf("Value of second node: ");
				scanf("%d", &idxS);
				swapNodes(&head, idx, idxS);
				break;
			case 9:
				countNodes(head);
				break;
			case 10:
				printf("Value of node to find: ");
				scanf("%d", &value);
				findNode(&head, value);
				break;
			case 11:
				printf("Position where to edit: ");
				scanf("%d", &idx);
				printf("New value: ");
				scanf("%d", &value);
				editNode(&head, value, idx);
				break;
			case 12:
				getAddress(head);
				break;
			case 13:
				printAddresses(head);
				break;
			case 14:
				readFile(&head);
				break;
			case 15:
				writeList(&head);
				printf("Currennt list was successfully written to the file \n");
				break;
			case 16:
				printf("Index where to split: ");
				scanf("%d", &idx);
				splitList(&head, &head0, idx);
				// now there are two lists
				// each head points to beginning of a list
				// but we are working with head only
				printList(head);
				printList(head0);
				break;
			case 17:
				joinLists(&head, &head0);
				break;
			case 18:
				dealloc(&head);
				break;
			case 19:
				printList(head);
				break;
			case 20:
				printChoices();
				break;
			case 21:
				printf("Goodbye \n");
				exit(0);
		}
	}
	
  return 0;
}

Node createNode(void) {
  Node temp = malloc(sizeof(Node));
  temp -> next = NULL;
  return temp;
}

// add to the end
void append(Node* head, int value) {
    
	Node newNode, currNode;
	
	newNode = createNode();
	newNode -> data = value;
	
	if (*head == NULL) {
		*head = newNode;
	} 
	else {
		currNode = *head;
		while (currNode -> next) {
			currNode = currNode -> next;
		}
		currNode -> next = newNode;
	}
	
}

void printList(Node node) {
    
  while (node) {
    if (node -> next) {
			printf("%2d ->", node -> data);
    }
    else {
      printf("%2d \n", node -> data);
    }

		node = node -> next;
  }

}

// add to the beginning
void prepend(Node* head, int value) {
    
	Node newNode = createNode();
	newNode -> data = value;
	
	if (*head == NULL) {
		*head = newNode;
	} 
	else {
		newNode -> next = *head;
		*head = newNode;
	}
	
}

void insert(Node* head, int value, int index) {
            
  Node newNode = createNode();
  newNode -> data = value;

	if (index == 0) {
		newNode -> next = *head;
		*head = newNode;
		return;
	} 
			
	Node currNode = *head, tmp;
	while (currNode && --index) {
		currNode = currNode -> next;
	}

	if (index) {
		printf("Index out of bounds \n");
	} else {
		tmp = currNode -> next;
		currNode -> next = newNode;
		newNode -> next = tmp;
	}
	
}

void insertOrdered(Node* head, int value) {
    
	Node newNode = createNode();
  newNode -> data = value;
 			
	if (!*head || (*head) -> data > value) {
		newNode -> next = *head;
		*head = newNode;
	} 
	else {
		
		Node currNode = *head, tmp;
		
		while (currNode -> next && currNode -> next -> data < value) {
			currNode = currNode -> next;
		}

		newNode -> next = currNode -> next;
		currNode -> next = newNode;
	}

}

void reverseList(Node* head) {
    
	if (*head == NULL) {
		printf("The list is empty \n");
		return;
	}
	
	printf("reversing a list \n");
			
	Node currNode, prevNode, nextNode;
	currNode = *head;
	prevNode = NULL;
	
	while (currNode) {
		nextNode = currNode -> next;
		currNode -> next = prevNode;
		prevNode = currNode;
		currNode = nextNode;
	}
					
	*head = prevNode;
}

void removeNode(Node* head, int value) {
 
	Node tmp = *head, prev = NULL;

	if (tmp && tmp -> data == value) {
		*head = tmp -> next;
		free(tmp);
		return;
	}

	while (tmp && tmp -> data != value) {
		prev = tmp;
		tmp = tmp -> next;
	}

	if (tmp == NULL) {
		printf("Value is not in a list \n");
		return;
	}

	prev -> next = tmp -> next;
	free(tmp);
}

// mark first element as sorted
// then make shift and insert each
// element one by one
void insertionSort(Node* head) {
    
	if (*head == NULL) {
		printf("The list is empty \n");
		return;
	}

	printf("sorting \n");
		
	Node x, y, e;
	
	x = *head;
	*head = NULL;
	
	while (x != NULL) {
			
		e = x;
		x = x -> next;
		
		if (*head != NULL) {
			if ((e -> data) > ((*head) -> data)) {
				y = *head;
				while ((y -> next != NULL) && (e -> data > y -> next -> data)) {
					y = y -> next;
				}
				
				e -> next = y -> next;
				y -> next = e;		
			} 
			else {
				e -> next = *head;
				*head = e;
			}
		} else {
			e -> next = NULL;
			*head = e;
		}
	}

}

void findNode(Node* head, int value) {

	if (*head == NULL) {
		printf("The list is empty \n");
		return;
	}

	Node currNode = *head;

	while (currNode) {
		
		if ((currNode -> data) == value) {
			printf("found the node \n");
			return;
		}

		currNode = currNode -> next;
	}

	printf("node was not found \n");
}

void countNodes(Node head) {

	int nodeCount;

	for (nodeCount = 0; head != NULL; nodeCount++, head = head -> next);
	
	printf("there are %d nodes is a list \n", nodeCount);
}

void swapNodes(Node* head, int firstVal, int secondVal) {

	if (*head == NULL) {
		printf("The list is empty \n");
		return;
	}

	if (firstVal == secondVal) return;  
  
// Search for x (keep track of prevX and CurrX)
	Node prevFirst = NULL, currFirst = *head;
	while (currFirst && currFirst->data != firstVal)  
	{ 
		prevFirst = currFirst;  
		currFirst = currFirst->next;  
	}  

	// Search for y (keep track of prevY and currSecond)
	Node prevSecond = NULL, currSecond = *head;
	while (currSecond && currSecond->data != secondVal)  
	{  
		prevSecond = currSecond;  
		currSecond = currSecond->next;  
	}  

	// If either x or y is not present, nothing to do  
	if (currFirst == NULL || currSecond == NULL)  
		return;  

	// If x is not head of linked list  
	if (prevFirst != NULL)  
		prevFirst->next = currSecond;  
	else // Else make y as new head  
		*head = currSecond;  

	// If y is not head of linked list  
	if (prevSecond != NULL)  
		prevSecond->next = currFirst;  
	else // Else make x as new head  
		*head = currFirst;  

	// Swap next pointers  
	Node tmp = currSecond->next;
	currSecond->next = currFirst->next;
	currFirst->next = tmp;  
}

void editNode(Node* head, int newValue, int pos) {

	if (*head == NULL) {
		printf("The list is empty \n");
		return;
	}

	if (pos < 0) {
		printf("invalid index \n");
		return;
	}
	
	Node currNode;
	currNode = *head;

	while (currNode) {
		if (--pos == 0) {
			currNode -> data = newValue;
			break;
		}
		currNode = currNode -> next;
	}

	if (pos) {
		printf("index is out of range \n");
 	} else {
		 printf("node was successfully edited \n");
	 }

}

void getAddress(Node head) {

	if (head == NULL) {
		printf("The list is empty \n");
		return;
	}

	Node currNode = head;
	
	while (currNode -> next) {
		currNode = currNode -> next;
	}

	printf("last element is %d with address %p \n", currNode -> data, currNode);
}

void dealloc(Node* head) {

	Node tmp = *head;
	while (*head) {
		tmp = *head;
		*head = (*head) -> next	;
		free(tmp);
	}

}

void writeList(Node* head) {
	FILE* outfile;

	// open file for writing
	outfile = fopen("output.txt", "wb");

	if (outfile == NULL) {
		fprintf(stderr, "error while openning the file \n");
		exit(1);
	}

	Node tmp = *head;

	while (tmp) {
		fwrite(&(tmp -> data), sizeof(int), 1, outfile);
		tmp = tmp -> next;
		}

	fclose(outfile);
}

void readFile(Node* head) {
	FILE* inputfile;

	// open file for reading
	inputfile = fopen("output.txt", "r");

	if (inputfile == NULL) { 
		fprintf(stderr, "error while openning the file \n");
	}

	*head = createNode();
	fread(&((*head) -> data), sizeof(int), 1, inputfile);

	Node lastNode = *head;
	Node newNode;

	int bytesRead = 0;
	while (1) {
		newNode = createNode();
		bytesRead = fread(&(newNode -> data), sizeof(int), 1, inputfile);
		if (bytesRead == 0) {
			break;
		}
		lastNode -> next = newNode;
		lastNode = newNode;
	}

	fclose(inputfile);
}

void printAddresses(Node node) {

	Node nextNode;
	if (node -> next) {
		nextNode = node -> next;
	} else {
		printf("%p -> NULL", &node);
		return;
	}

	while (nextNode) {
		printf("%p\t%d  ->  %p\t%d \n", node, node -> data, nextNode, nextNode -> data);
		node = nextNode;
		if (nextNode -> next) {
			nextNode = nextNode -> next;
		} else break;
	}
}

// find that index
// make headO next element of that index
// make element at that index point to NULL
void splitList(Node* head, Node* head0, int idx) {

	if (!*head) {
		printf("The list is empty \n");
		return;
	}

	Node tmp;
	tmp = *head;

	int co = 0;
	while (++co < idx) {
		tmp = tmp -> next;
	}

	*head0 = tmp -> next;
	tmp -> next = NULL;
}

// add head0 to the end of the head
void joinLists(Node* head, Node* head0) {

	if (!*head || !*head0) {
		printf("There is only one list or no lists at all \nplease call 'Split list' first \n");
		return;
	}

	Node tmp = *head;
	while (tmp -> next) {
		tmp = tmp -> next;
	}

	tmp -> next = *head0;
}

void printChoices(void) {
	printf("1\tAdd node to the end \n");
	printf("2\tAdd node to the beginning \n");
	printf("3\tInsert node by index \n");
	printf("4\tInsert node in order \n");
	printf("5\tRemove node \n");
	printf("6\tSort \n");
	printf("7\tReverse list \n");
	printf("8\tSwap nodes \n");
	printf("9\tCount nodes \n");
	printf("10\tFind node \n");
	printf("11\tEdit node \n");
	printf("12\tGet address of last element \n");
	printf("13\tPrint addresses \n");
	printf("14\tRead list \n");
	printf("15\tWrite list \n");
	printf("16\tSplit list \n");
	printf("17\tJoin lists \n");
	printf("18\tDealloc \n");
	printf("19\tPrint list \n");
	printf("20\tPrint choices \n");
	printf("21\tQuit \n");
}
