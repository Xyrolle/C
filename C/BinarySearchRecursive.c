#include <stdio.h>

int binarySearch(int* arr, int x, int left, int right) {

	if (left > right) {
		printf("Values does not exist in a given array \n");
		return 1;
	}

	int mid = left + ((right - left) / 2);

	if (arr[mid] == x) {
		printf("Found %d at index %d \n", x, mid);
	} else if (x < arr[mid]) {
		binarySearch(arr, x, left, mid - 1);
	} else {
		binarySearch(arr, x, mid + 1, right);
	}

	return 0;
} 

int main(void) {

	printf("Input value to find: ");

	int find;

	scanf("%d", &find);

	int arr[10] = {1, 5, 7, 10, 20, 40, 71, 80, 83, 85};  
	int leng = sizeof(arr) / sizeof(arr[0]) - 1;

	int val = binarySearch(arr, find, 0, leng);

  return 0;
}
