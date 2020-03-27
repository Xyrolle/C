#include <stdio.h>

int main(void) {

	int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

	int i;

	unsigned long len = sizeof(arr) / 4;

	for (i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}

	printf("\n");

	int temp, temp1;

	int k;
	scanf("%d", &k);

	k = k % len;

	while (k--) {
		temp = arr[len - 1];
		for (i = len - 1; i > 0; i--) {
			arr[i] = arr[i - 1];  
		}
		arr[0] = temp;
	 }
	 
	for (i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}

  return 0;
}