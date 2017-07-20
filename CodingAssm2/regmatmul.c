#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int** createArray(int n, int m)
{
    int* values = calloc(n*n, sizeof(int));
    int** rows = malloc(n*sizeof(int*));
    for (int i=0; i<n; ++i)
    {
        rows[i] = values + i*m;
    }
    return rows;
}

void destroyArray(int** arr)
{
    free(*arr);
    free(arr);
}

void printMatrix(int** mat, int dim){
	for(int r = 0; r < dim; r++){
		for(int c = 0; c < dim; c++){
			printf("%d ", mat[r][c]);
		}
		printf("\n");
	}
}

int dotprod(int** dataA, int** dataB, int dim, int r, int c){
	int sum = 0;
	for(int i = 0; i < dim; i++){
		sum += dataA[r][i] * dataB[i][c];
	}
	return sum;
}

void matmix(int** dataA, int** dataB, int dim, int** returnmat){
	// iterate the rows of dataA
	for (int r = 0; r < dim; r++){
		for(int i = 0; i < dim; i++){
            for (int c = 0; c < dim; c++){
    			returnmat[r][c] += dataA[r][i] * dataB[i][c];
    		}
        }
	}
}

int main(int argc, char *argv[]){

	int datadim = atoi(argv[2]);

	printf("input: %d, next: %d\n", datadim, datadim);
	int** dataA = createArray(datadim,datadim);
	int** dataB = createArray(datadim,datadim);
	int** dataC = createArray(datadim,datadim);

	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(argv[3], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int row = 0;
    int col = 0;
    int next = 1;
    while ((read = getline(&line, &len, fp)) != -1) {
        if(next){
        	dataA[row][col] = atoi(line);
        	col++;
        	if(col >= datadim){
        		row++;
        		col=0;
        	}
        	if(row >= datadim){
        		next = 0;
        		row=0;
        		col=0;
        	}
        }
        else{
        	dataB[row][col] = atoi(line);
        	col++;
        	if(col >= datadim){
        		row++;
        		col=0;
        	}
        	if(row >= datadim){
        		break;
        	}
        }
    }

    fclose(fp);
    if (line)
        free(line);

    printMatrix(dataA, datadim);
    printf("\n");
    printMatrix(dataB, datadim);
    printf("datadim: %d\n", datadim);
    matmix(dataA, dataB, datadim, dataC);
    printMatrix(dataC, datadim);
}