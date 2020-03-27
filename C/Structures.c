#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
  char author[30];
  char title[30];
  int pages;
  int pubYear;
  int copies;
};

void allocList(struct Book **bookList, int bookAmount);
void fillKeyboard(struct Book *bookList, int bookAmount);
void printList(struct Book *bookList, int bookAmount);
void writeStruct(struct Book *bookList, int bookAmount);
void readStruct(struct Book *bookList, int bookAmount);
void printChoices(void);

void addBook(struct Book *bookList, int bookIndex);
void editBook(struct Book *bookList, int bookIndex);
void deleteBook(struct Book **bookList, int *bookAmount, int bookIndex);

void deallocateMemory(struct Book **bookList, int bookAmount);

struct Book findBook(struct Book *bookList, int bookAmount, char* title);

void addToEnd(struct Book **bookList, int* bookAmount);
void insertBook(struct Book **bookList, int* bookAmount, int bookIndex);
void sortBooks(struct Book *bookList, int bookAmount);

void quit(void);

int main(void) {

	struct Book *booksList = NULL;
	int* bookAmount = malloc(sizeof(int));

	int insertionIndex = 0;
	int deletionIndex = 0;
	int indexToChange = 0;

	char bookToFind[20];

	int choice;

	printChoices();

	while (1) {

		printf("enter your choice: ");
		scanf("%d", &choice);

		switch(choice) {
			case 1:
				printf("enter amount of books to hold: ");
				scanf("%d", &*bookAmount);
				allocList(&booksList, *bookAmount);
				break;
			case 2:
				fillKeyboard(booksList, *bookAmount);
				break;
			case 3:
				printList(booksList, *bookAmount);
				break;
			case 4:
				writeStruct(booksList, *bookAmount);
				break;
			case 5:
				readStruct(booksList, *bookAmount);
				break;
			case 6:
				addToEnd(&booksList, bookAmount);
				break;
			case 7:
				printf("enter index where to insert: ");
				scanf("%d", &insertionIndex);
				insertBook(&booksList, bookAmount, insertionIndex);
				break;
			case 8:
				printf("enter index of element to delete: ");
				scanf("%d", &deletionIndex);
				deleteBook(&booksList, bookAmount, deletionIndex);
				break;
			case 9:
				printf("enter index of element to change: ");
				scanf("%d", &indexToChange);
				editBook(booksList, indexToChange);
				break;
			case 10:
				printf("enter title of the book that you want to find: ");
				scanf("%s", &*bookToFind);
				findBook(booksList, *bookAmount, bookToFind);
				break;
			case 11:
				sortBooks(booksList, *bookAmount);
				break;
			case 12:
				printChoices();
				break;
			case 13:
				deallocateMemory(&booksList, *bookAmount);
				break;
			case 14:
				quit();
				break;
			default:
				printf("are you sure you entered the right command?\nEnter 12 to list available choices \n");
		}
	}
	
  return 0;
}

void allocList(struct Book **bookList, int bookAmount) {
  // *bookList = malloc(sizeof(struct Book) * bookAmount);
	*bookList = calloc(bookAmount, sizeof(struct Book));
  printf("memory for %d books was allocated \n", bookAmount);
}

void fillKeyboard(struct Book *bookList, int bookAmount) {
        
	int i = 0;

	while (bookAmount--) {
			addBook(bookList, i++);
	}

}

void addBook(struct Book *bookList, int bookIndex) {

	char authorName[30], title[30];
	
	printf("enter information about the book \n");
	
	printf("enter author: ");
	scanf("%s", *&authorName);
	strcpy(bookList[bookIndex].author, authorName);

	printf("enter title: ");
	scanf("%s", *&title);
	strcpy(bookList[bookIndex].title, title);

	printf("enter year of publication: ");
	scanf("%d", &bookList[bookIndex].pubYear);

	printf("enter amount of pages: ");
	scanf("%d", &bookList[bookIndex].pages);

	printf("enter amount of copies sold: ");
	scanf("%d", &bookList[bookIndex].copies);
}

void addToEnd(struct Book **bookList, int *bookAmount) {
    
	*bookList = realloc(*bookList, (sizeof(bookList) + 1) * sizeof(struct Book));
	addBook(*bookList, *bookAmount);

  ++*bookAmount;
}

void printList(struct Book *bookList, int bookAmount) {

	for (int i = 0; i < bookAmount; i++) {
			
		if (bookList == NULL) {
			printf("nothing to print \n");
			return;
		}

		printf("\n\tbook details");
		printf("\n--------------------\n");
		printf("author is: %s \n", bookList[i].author);
		printf("title is: %s \n", bookList[i].title);
		printf("amount of pages: %d \n", bookList[i].pages);
		printf("published in: %d \n", bookList[i].pubYear);
		printf("copies sold: %d \n", bookList[i].copies);
		printf("--------------------\n");
	}

}

struct Book findBook(struct Book *bookList, int bookAmount, char* title) {

	int i;

	for (i = 0; i < bookAmount; i++) {
			if (strcmp(bookList[i].title, title) == 0) {
					printf("found the book \n");
					return bookList[i];
			}
	}

	printf("sorry, the book was not found \n");
  return bookList[i];
}

void writeStruct(struct Book *bookList, int bookAmount) {

	FILE* outfile;
	
	// open file for writing
	outfile = fopen("output.txt", "wb");

	if (outfile == NULL) {
			fprintf(stderr, "error while openning the file \n");
			exit(1);
	}

	fwrite(bookList, sizeof(struct Book), bookAmount, outfile);
	fclose(outfile);
}

void readStruct(struct Book *bookList, int bookAmount) {

	FILE* inputfile;

	// open file for reading
	inputfile = fopen("output.txt", "rb");

	if (inputfile == NULL) {
			fprintf(stderr, "error while openning the file \n");
			exit(1);
	}

	fread(bookList, sizeof(struct Book), bookAmount, inputfile);
	fclose(inputfile);
}

void editBook(struct Book *bookList, int bookIndex) {
  printf("changing information of book number: %d \n", bookIndex + 1);
  addBook(bookList, bookIndex);
}

void deleteBook(struct Book **bookList, int *bookAmount, int bookIndex) {
    
	if (bookIndex >= *bookAmount) {
			printf("Error, index is out of bounds \n");
			return;
	}
	
	*bookList = realloc(*bookList, (sizeof(bookList) - 1) * sizeof(struct Book));
	
	// left shift all elements
	for (int i = bookIndex; i < *bookAmount; i++) {
		strcpy((*bookList)[i].author, (*bookList)[i + 1].author);
		strcpy((*bookList)[i].title, (*bookList)[i + 1].title);
		(*bookList)[i].pages = (*bookList)[i + 1].pages;
		(*bookList)[i].pubYear = (*bookList)[i + 1].pubYear;
		(*bookList)[i].copies = (*bookList)[i + 1].copies;
	}
	
	printf("book with number %d was successfully deleted \n", bookIndex + 1);
  --*(bookAmount);
}

void insertBook(struct Book** bookList, int* bookAmount, int bookIndex) {
    
	if ((bookIndex > *bookAmount) || (bookIndex < 0)) {
		printf("Error, index is out of bounds\n");
		return;
	}
	
	// we should reallocate the memory to hold one more
	*bookList = realloc(*bookList, (sizeof(bookList) + 1) * sizeof(struct Book));

	// right shift all elements after given index
	// to make space for a new one
	for (int i = (*bookAmount) - 1; i >= bookIndex; i--) {
		strcpy((*bookList)[i + 1].author, (*bookList)[i].author);
		strcpy((*bookList)[i + 1].title, (*bookList)[i].title);
		(*bookList)[i + 1].pages = (*bookList)[i].pages;
		(*bookList)[i + 1].pubYear = (*bookList)[i].pubYear;
		(*bookList)[i + 1].copies = (*bookList)[i].copies;
	}

	// add a new book
	addBook(*bookList, bookIndex);
  ++*bookAmount;
}

void sortBooks(struct Book *bookList, int bookAmount) {

	if (bookAmount < 2) {
		return;
	}

	printf("\n\t  sorting \n");
	
	struct Book temp;

	int swapped;
	int i = 0;

	do {
		swapped = 0;
		for (i = 0; i < bookAmount - 1; i++) {
			if (strcmp(bookList[i].title, bookList[i + 1].title) > 0) {
				temp = bookList[i];
				bookList[i] = bookList[i + 1];
				bookList[i + 1] = temp;
				swapped = 1;
			}
		}
	} while (swapped);

}

void deallocateMemory(struct Book **bookList, int bookAmount) {
	free(*bookList);
	*bookList = NULL;
	printf("deallocated \n");
}

void quit() {
    
	printf("are you sure you want to quit? y/n\n");
	
	char choice;
	do {
		scanf("%c", &choice);
	} while (choice != 'y' && choice != 'n');
	
	if (choice == 'y') {
		exit(0);
	}
	
}

void printChoices(void) {
	printf("1\tAllocate memory \n");
	printf("2\tFill books information from keyboard \n");
	printf("3\tList all available books \n");
	printf("4\tWrite books to the file \n");
	printf("5\tRead books from the file \n");
	printf("6\tAdd a book to the end \n");
	printf("7\tInsert a book \n");
	printf("8\tDelete a book \n");
	printf("9\tEdit a book \n");
	printf("10\tFind a book \n");
	printf("11\tSort books by title \n");
	printf("12\tList choices \n");
	printf("13\tDeallocate memory\n");
	printf("14\tExit\n");
}

