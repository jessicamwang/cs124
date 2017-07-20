#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>

#define leftChild(x) 2 * x + 1
#define rightChild(x) 2 * x + 2
#define parent(x) (x - 1) / 2

typedef struct node{
	int64_t num;
} node;

typedef struct maxHeap {
	int size;
	node *element;
} maxHeap;

maxHeap initHeap(int size){
	maxHeap heap;
	heap.size = 0;
	heap.element = malloc(size * sizeof(node));
	return heap;
}

void swap(node *n1, node *n2){
	node temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

void sort(maxHeap *heap, int i){
	int largest = (leftChild(i) < heap->size && heap->element[leftChild(i)].num > heap->element[i].num) ? leftChild(i) : i;
	if(rightChild(i) < heap->size && heap->element[rightChild(i)].num > heap->element[largest].num){
		largest = rightChild(i);
	}
	if (largest != i){
		swap(&(heap->element[i]), &(heap->element[largest]));
		sort(heap, largest);
	}
}

void insert(maxHeap *heap, int64_t num){
	// 
	// The malloc of the insert does not work here
	// Only matters when adding nodes so size greater than initialized
	// 
	// if(heap->size){
	// 	heap->element = realloc(heap->element, (size+1)*sizeof(node);
	// } else {
	// 	heap->element = malloc(sizeof(node));
	// }

	node temp;
	temp.num = num;

	int i = (heap->size)++;
	heap->element = realloc(heap->element, heap->size*sizeof(node));
	while(i && temp.num > heap->element[parent(i)].num){
		heap->element[i] = heap->element[parent(i)];
		i = parent(i);
	}
	heap->element[i] = temp;
}

void delete(maxHeap *heap){
	if(heap->size){
		// printf("Deleting node %d\n", heap->element[0].num);
		// printf("Heap size 1: %i\n", heap->size);
		heap->element[0] = heap->element[--(heap->size)];
		// printf("Heap size 2: %i\n", heap->size);
		// heap->element = realloc(heap->element, heap->size*sizeof(node));
		sort(heap, 0);
	} else{
		printf("Heap is empty \n");
		free(heap->element);
	}
}

void arrayToHeap(maxHeap *heap, int64_t *array, int size) {
	for(int i = 0; i < size; i++){
		if(heap->size){
			heap->element = realloc(heap->element, (heap->size+1)*sizeof(node));
		} 
		else{
			heap->element = malloc(sizeof(node));
		}
		node temp;
		temp.num = array[i];
		heap->element[(heap->size)++] = temp;
	}

	for(int j = (heap->size - 1)/2; j>=0; j--){
		sort(heap, j);
	}
}

void deleteHeap(maxHeap *heap){
	free(heap->element);
}

void print(maxHeap *heap, int i){
	printf("%lld", heap->element[i].num);
	if(leftChild(i) < heap->size){
		print(heap, leftChild(i));
	}
	if(rightChild(i) < heap->size){
		print(heap, rightChild(i));
	}
}

void printZero(maxHeap *heap){
	printf("%lld", heap->element[0].num);
}