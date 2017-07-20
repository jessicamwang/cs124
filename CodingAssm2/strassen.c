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

void addMatrix(int** matA, int ai, int aj, int** matB, int bi, int bj, int dim, int sub, int** returnmat){
	for(int r = 0; r < dim; r++){
		for(int c = 0; c < dim; c++){
			returnmat[r][c] = matA[ai+r][aj+c] + (sub * matB[bi+r][bj+c]);
		}
	}
};

void copymat(int** data, int i, int j, int dim, int** returnmat){
	for(int r = 0; r < dim; r++){
		for(int c = 0; c < dim; c++){
			returnmat[r][c] = data[i+r][j+c];
		}
	}
};

void combineMatrix(int** matA, int** matB, int** matC, int** matD, int dim, int** returnmat){
	for(int r = 0; r < dim; r++){
		for(int c = 0; c < dim; c++){
			returnmat[r][c] = matA[r][c];
		}
	}

	for(int r = 0; r < dim; r++){
		for(int c = 0; c < dim; c++){
			returnmat[r][dim+c] = matB[r][c];
		}
	}

	for(int r = 0; r < dim; r++){
		for(int c = 0; c < dim; c++){
			returnmat[dim+r][c] = matC[r][c];
		}
	}

	for(int r = 0; r < dim; r++){
		for(int c = 0; c < dim; c++){
			returnmat[dim+r][dim+c] = matD[r][c];
		}
	}
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

int strassen(int** matA, int** matB, int dim, int n0, int** returnmat)
{
	if(dim <= n0)
	{
		matmix(matA, matB, dim, returnmat);
		return 0;
	}

	int** m1 = createArray(dim/2,dim/2);
	int** m2 = createArray(dim/2,dim/2);
	int** m3 = createArray(dim/2,dim/2);
	int** m4 = createArray(dim/2,dim/2);
	int** m5 = createArray(dim/2,dim/2);
	int** m6 = createArray(dim/2,dim/2);
	int** m7 = createArray(dim/2,dim/2);
	int** m1a = createArray(dim/2,dim/2);
	int** m1b = createArray(dim/2,dim/2);
	int** m2a = createArray(dim/2,dim/2);
	int** m2b = createArray(dim/2,dim/2);
	int** m3a = createArray(dim/2,dim/2);
	int** m3b = createArray(dim/2,dim/2);
	int** m4a = createArray(dim/2,dim/2);
	int** m4b = createArray(dim/2,dim/2);
	int** m5a = createArray(dim/2,dim/2);
	int** m5b = createArray(dim/2,dim/2);
	int** m6a = createArray(dim/2,dim/2);
	int** m6b = createArray(dim/2,dim/2);
	int** m7a = createArray(dim/2,dim/2);
	int** m7b = createArray(dim/2,dim/2);

	addMatrix(matA, 0, 0, matA, dim/2, dim/2, dim/2, 1, m1a);
	addMatrix(matB, 0, 0, matB, dim/2, dim/2, dim/2, 1, m1b);
	strassen(m1a, m1b, dim/2, n0, m1);
	
	addMatrix(matA, dim/2, 0, matA, dim/2, dim/2, dim/2, 1, m2a);
	copymat(matB, 0, 0, dim/2, m2b);
	strassen(m2a, m2b, dim/2, n0, m2);

	copymat(matA, 0, 0, dim/2, m3a);
	addMatrix(matB, 0 , dim/2, matB, dim/2, dim/2, dim/2, -1, m3b);
	strassen(m3a, m3b, dim/2, n0, m3);

	copymat(matA, dim/2, dim/2, dim/2, m4a);
	addMatrix(matB, dim/2, 0, matB, 0, 0, dim/2,-1, m4b);
	strassen(m4a, m4b, dim/2, n0, m4);

	addMatrix(matA, 0, 0, matA, 0, dim/2, dim/2,1,m5a);
	copymat(matB, dim/2, dim/2, dim/2, m5b);
	strassen(m5a, m5b, dim/2, n0, m5);

	addMatrix(matA, dim/2, 0, matA, 0, 0, dim/2,-1,m6a);
	addMatrix(matB, 0, 0, matB, 0, dim/2, dim/2,1,m6b);
	strassen(m6a, m6b, dim/2, n0, m6);

	addMatrix(matA, 0, dim/2, matA, dim/2, dim/2, dim/2,-1,m7a);
	addMatrix(matB, dim/2, 0,matB, dim/2, dim/2 ,dim/2,1,m7b);
	strassen(m7a, m7b, dim/2, n0, m7);

	int** c00 = createArray(dim/2,dim/2);
	int** c01 = createArray(dim/2,dim/2);
	int** c10 = createArray(dim/2,dim/2);
	int** c11 = createArray(dim/2,dim/2);

	addMatrix(m1, 0, 0, m4, 0, 0, dim/2,1,c00);
	addMatrix(c00, 0, 0, m5, 0, 0, dim/2, -1,c00);
	addMatrix(c00,0, 0, m7,0, 0, dim/2,1,c00);
	addMatrix(m3,0, 0, m5,0, 0, dim/2,1,c01);
	addMatrix(m2,0, 0, m4,0, 0, dim/2,1,c10);
	addMatrix(m1,0, 0, m2,0, 0, dim/2,-1,c11);
	addMatrix(c11,0, 0, m3,0, 0, dim/2, 1,c11);
	addMatrix(c11,0, 0, m6,0, 0, dim/2,1,c11);

	combineMatrix(c00, c01, c10, c11, dim/2, returnmat);

	destroyArray(m1);
	destroyArray(m2);
	destroyArray(m3);
	destroyArray(m4);
	destroyArray(m5);
	destroyArray(m6);
	destroyArray(m7);
	destroyArray(m1a);
	destroyArray(m1b);
	destroyArray(m2a);
	destroyArray(m2b);
	destroyArray(m3a);
	destroyArray(m3b);
	destroyArray(m4a);
	destroyArray(m4b);
	destroyArray(m5a);
	destroyArray(m5b);
	destroyArray(m6a);
	destroyArray(m6b);
	destroyArray(m7a);
	destroyArray(m7b);

	destroyArray(c00);
	destroyArray(c01);
	destroyArray(c10);
	destroyArray(c11);

	return 0;

}

int main(int argc, char *argv[]){

	int inputdim = atoi(argv[2]);
	int n0 = atoi(argv[1]);

	if(n0 == 0 || n0 > inputdim){
		n0 = 1;
	}

	int datadim = pow(2, ceil(log(inputdim)/log(2)));
	printf("input: %d, next: %d\n", inputdim, datadim);
	int** dataA = createArray(datadim,datadim);
	int** dataB = createArray(datadim,datadim);

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
        	if(col >= inputdim){
        		row++;
        		col=0;
        	}
        	if(row >= inputdim){
        		next = 0;
        		row=0;
        		col=0;
        	}
        }
        else{
        	dataB[row][col] = atoi(line);
        	col++;
        	if(col >= inputdim){
        		row++;
        		col=0;
        	}
        	if(row >= inputdim){
        		break;
        	}
        }
    }

    fclose(fp);
    if (line)
        free(line);

/*    printMatrix(dataA, datadim);
    printf("\n");
    printMatrix(dataB, datadim);
    printf("datadim: %d\n", datadim);*/

	int** finalMatrix = createArray(datadim,datadim);

	strassen(dataA, dataB, datadim, n0, finalMatrix);

/*	printf("Final Matrix \n");
	printMatrix(finalMatrix, datadim);
*/
	destroyArray(dataA);
	destroyArray(dataB);
	destroyArray(finalMatrix);

return 0;
}