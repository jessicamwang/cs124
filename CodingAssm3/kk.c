#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "heap.h"
#include "mt19937-64.h"
#include <inttypes.h>
#include <string.h>

struct timeval t;

/* print array of 64-bit numbers */
void print_sequence (int64_t* seq, int len) {
	for (int i = 0; i < len; i++){
		printf("%lld ", seq[i]);
	}
	printf("\n");
}

/* generate an array of random numbers 1 to n */
void rand_seq (int64_t* seq, int len, int64_t n) {
	for (int i = 0; i < len; i++){
		// is this right?
		seq[i] = genrand64_int64() % (n - 1) + 1;
	}
}

/* generate a random sequence of +1 or -1 of length len */
void standard_random (int64_t* seq, int len) {
	for (int i = 0; i < len; i ++) {
		if (rand()%2 == 0) {
			seq[i] = 1;
		}
		else {
			seq[i] = -1;
		}
	}
}

/* copies array a into array b */
void copy_array (int64_t* a, int64_t* b, int len) {
	for (int i = 0; i < len; i ++) {
		b[i] = a[i];
	}
}

/* generate random neighbor of s (alters s in place) */
void standard_neighbor (int64_t* s, int64_t* newS, int len) {
	copy_array(s, newS, len);
	int i = rand() % len;
	int j = rand() % len;
	// try again until i, j distinct
	while (i == j) {
		i = rand() % len;
		j = rand() % len;
	}
	newS[i] = newS[i] * -1;
	if (rand() % 2 == 0) {
		newS[j] = newS[j] * -1;
	}
}

/* prepartition array given P */
void prepartition (int64_t* p, int64_t* a, int64_t* newA, int len) {
	// initialize to 0
	for (int i = 0; i < len; i++) {
		newA[i] = 0;
	}
	// get new values according to P
	for (int i = 0; i < len; i ++) {
		newA[p[i]] = newA[p[i]] + a[i];
	}
}

/* generate random neighbor of p (alters in place) */
void sequence_neighbor (int64_t* s, int64_t* newS, int len) {
	copy_array(s, newS, len);
	int i = rand() % len;
	int j = rand() % len;
	// try again until i, j distinct
	while (newS[i] == j) {
		i = rand() % len;
		j = rand() % len;
	}
	newS[i] = j;
}


/* generate random neighbor of p (alters in place) */
void prepartition_neighbor (int64_t* p, int64_t* newP, int len) {
	copy_array(p, newP, len);
	int i = rand() % len;
	int j = rand() % len;
	// try again until i, j distinct
	while (newP[i] == j) {
		i = rand() % len;
		j = rand() % len;
	}
	newP[i] = j;
}

/* calculate residue given sequence of +1/-1 */
int64_t get_residue (int64_t* a, int64_t* seq, int len) {
	int64_t residue = 0;
	for (int i = 0; i < len; i++) {
		residue += a[i] * seq[i];
	}
	return llabs(residue);
}

/* runs KK algorithm on array and returns residue */
int64_t kk_alg (int64_t* a, int len) {
	maxHeap heap = initHeap(len);
	arrayToHeap(&heap, a, len);
	// heap.size returns the size of the heap
	while (heap.size > 1) {
		int64_t a = heap.element[0].num;
		delete(&heap);
		int64_t b = heap.element[0].num;
		delete(&heap);
		insert(&heap, a - b);
	}
	int64_t residue = heap.element[0].num;
	// delete the heap
	deleteHeap(&heap);
	return llabs(residue);
}

int64_t repeatedRandom_standardRandom(int maxIter, int64_t* S, int64_t* A, int len){
	int64_t* newS = malloc(sizeof(int64_t) * len);
	int64_t residue;
	int64_t new_res;
	for(int i = 0; i < maxIter; i++){
		standard_random(newS, len);
		residue = get_residue(A, S, len);
		new_res = get_residue(A, newS, len);
		// printf("%lld ", residue);
		if (new_res < residue) {
			residue = new_res;
			copy_array(newS, S, len);
		}
	}
	free(newS);
	return residue;
}


int64_t repeatedRandom_prepartition(int maxIter, int64_t* p, int64_t* a, int len){
	int64_t res;
	int64_t* newA = malloc(sizeof(int64_t) * len);
	int64_t* newP = malloc(sizeof(int64_t) * len);
	int64_t* aPrime = malloc(sizeof(int64_t) * len);
	for(int i = 0; i < maxIter; i++){
		prepartition(p, a, aPrime, len);
		rand_seq(newP, len, len);
		// printf("New P: ");
		// print_sequence(newP, len);
		prepartition(newP, a, newA, len);
		res = kk_alg(aPrime, len);
		// printf("%lld ", res);
		if(res > kk_alg(newA, len))
		{
			// copies array newP into p
			copy_array(newP, p, len);
		}
	}
	free(aPrime);
	free(newA);
	free(newP);
	return res;
}

int64_t hillclimbing_standardRandom(int maxIter, int64_t* S, int64_t* A, int len){
	int64_t* newS = malloc(sizeof(int64_t) * len);
	int64_t residue;
	for(int i = 0; i < maxIter; i++){
		standard_neighbor(S, newS, len);
		residue = get_residue(A, S, len);
		// printf("%lld ", residue);
		if (get_residue(A, newS, len) < residue) {
			copy_array(newS, S, len);
		}
	}
	free(newS);
	return residue;
}


int64_t hillclimbing_prepartition(int maxIter, int64_t* p, int64_t* a, int len){
	int64_t* aPrime = malloc(sizeof(int64_t) * len);
	int64_t* newP = malloc(sizeof(int64_t) * len);
	int64_t* newA = malloc(sizeof(int64_t) * len);
	int64_t residue;
	int64_t old_res;
	int64_t new_res;
	for(int i = 0; i < maxIter; i++){
		prepartition(p, a, aPrime, len);
		prepartition_neighbor(p, newP, len);
		prepartition(newP, a, newA, len);
		old_res = kk_alg(aPrime, len);
		new_res = kk_alg(newA, len);
		// printf("%lld ", kk_alg(aPrime, len));
		if(old_res > kk_alg(newA, len))
		{
			residue = new_res;
			copy_array(newP, p, len);
		}
	}
	free(aPrime);
	free(newP);
	free(newA);
	return residue;
}

double T(int iter){
	return pow(10,10)*pow(.8,iter/300);
}

int64_t annealing_standardRandom(int maxIter, int64_t* S, int64_t* A, int len, int64_t* newnewS){
	int64_t* newS = malloc(sizeof(int64_t) * len);
	int64_t residue;
	int64_t old_res;
	copy_array(S, newnewS, len);
	for(int i = 0; i < maxIter; i++){
		// printf("%lld ", get_residue(A, newnewS, len));
		standard_neighbor(S, newS, len);
		// printf("T: %f\n", T(i));
		double prob = exp(-(get_residue(A, newS, len)-get_residue(A, S, len))/T(i));
		// printf("Prob: %lld\n", prob);
		// get probability between 0 and 1
		double new_prob = rand() / RAND_MAX;
		if (get_residue(A, newS, len) < get_residue(A, S, len)) {
			copy_array(newS, S, len);
		} 
		else if (new_prob <= prob) 
		{
			copy_array(newS, S, len);
		}
		old_res = get_residue(A, newnewS, len);
		// get best solution thus far (newnewS)
		if (get_residue(A, S, len) < old_res) {
			residue = get_residue(A, S, len);
			copy_array(S, newnewS, len);
		}
	}
	free(newS);
	return residue;
}

int64_t annealing_prepartition(int maxIter, int64_t* p, int64_t* a, int len, int64_t* newnewP){
	int64_t* aPrime = malloc(sizeof(int64_t) * len);
	int64_t* newP = malloc(sizeof(int64_t) * len);
	int64_t* newA = malloc(sizeof(int64_t) * len);
	int64_t* newaPrime = malloc(sizeof(int64_t) * len);
	int64_t newA_res;
	int64_t aPrime_res;
	int64_t newaPrime_res;
	int64_t residue;
	for(int i = 0; i < maxIter; i++){
		// printf("%lld ", kk_alg(newaPrime, len));
		prepartition(p, a, aPrime, len);
		// random neighbor of S, S' (newP)
		prepartition_neighbor(p, newP, len);
		// A' corresponding to S'
		prepartition(newP, a, newA, len);
		prepartition(newnewP, a, newaPrime,len);

		// calculate residues
		aPrime_res = kk_alg(aPrime, len);
		newA_res = kk_alg(newA, len);
		newaPrime_res = kk_alg(newaPrime, len);

		// cooling schedule
		int prob = exp(-(newA_res - aPrime_res)/T(i));
		//get probability between 0 and 1
		double new_prob = rand() / RAND_MAX;
		
		if (aPrime_res > newA_res) {
			copy_array(newP, p, len);
		} else if (new_prob <= prob) {
			copy_array(newP, p, len);
		}

		prepartition(p, a, aPrime, len);
		aPrime_res = kk_alg(aPrime, len);

		if (aPrime_res < newaPrime_res) {
			residue = aPrime_res;
			copy_array(p, newnewP, len);
		}
	}
	free(aPrime);
	free(newP);
	free(newA);
	free(newaPrime);
	return residue;
}

int main(int argc, char *argv[])
{
	// initialize RNG
	gettimeofday(&t, NULL);
	srand(t.tv_usec * t.tv_sec);
	init_genrand64(t.tv_usec * t.tv_sec);

	// length of A
	int len = 100;

	// number of trials
	int numtrials = 50;

	// max value for A
	int64_t maxNum = pow(10,12);

	// allocate space for S, P, and A
	int64_t* seq = malloc(sizeof(int64_t) * len);
	int64_t* p = malloc(sizeof(int64_t) * len);
	int64_t* a = malloc(sizeof(int64_t) * len);

	// for simulated annealing
	int64_t* newnewS = malloc(sizeof(int64_t) * len);
	int64_t* newnewP = malloc(sizeof(int64_t) * len);

	// read in file of 100 numbers for A
	FILE * fp;

    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i < len; i++)
    {
        fscanf(fp, "%lld", &a[i]);
    }

	// create 50 random instances of A and save in file
	// for (int i = 0; i < numtrials; i++)
	// {
	// 	char buffer[32];
	// 	snprintf(buffer, sizeof(char) * 32, "instances/%i.txt", i);

	// 	FILE* file = fopen(buffer, "wb");

	// 	// generate random instance A
	// 	rand_seq(a, len, maxNum);
	// 	// write A to file
	// 	for (int j = 0; j < len; j++)
	// 	{
	// 		fprintf(file, "%lld\n", a[j]);
	// 	}
	// }

	// FILE* read;
	// char file_name[150];

	// clock_t start, diff;
	// float msec;
	// int64_t residue;
	// float runtime[numtrials];

	// printf("Residues:\n");
	// for (int i = 0; i < numtrials; i ++)
	// {
 //        sprintf(file_name, "/Users/akang/cs124_code/cs124_ps3/instances/%i.txt", i);
 //        // printf("%s\n", file_name);
	// 	read = fopen(file_name, "r");
	// 	if (read != NULL)
	// 	{
	// 		// read in A from file
	// 		for (int j = 0; j < len; j++)
	// 		{
	// 			fscanf(read, "%lld", &a[j]);
	// 		}

	// 		// get random standard solution
	// 		standard_random(seq, len);

	// 		// get random prepartition solution
	// 		rand_seq(p, len, len);

	// 		// for simulated annealing (standard)
	// 		copy_array(seq, newnewS, len);
	// 		copy_array(p, newnewP, len);

			
	// 		start = clock();
	// 		// residue = kk_alg(a, len);
	// 		residue = repeatedRandom_standardRandom(25000, seq, a, len);
	// 		// residue = hillclimbing_standardRandom(25000, seq, a, len);
	// 		// residue = annealing_standardRandom(25000, seq, a, len, newnewS);
	// 		// residue = repeatedRandom_prepartition(25000, p, a, len);
	// 		// residue = hillclimbing_prepartition(25000, p, a, len);
	// 		// residue = annealing_prepartition(25000, p, a, len, newnewP);
	// 		diff = clock() - start;
	// 		msec = (float) diff * 1000 / CLOCKS_PER_SEC;
	// 		runtime[i] = msec;
	// 		printf("%lld\n", residue);
	// 	}
	// 	else
	// 	{
	// 		printf("NULL");
	// 	}
	// 	fclose(read);
	// }

	// printf("Runtimes:\n");
	// for (int i = 0; i < numtrials; i++) 
	// {
	// 	printf("%f\n", runtime[i]);
	// }

    int64_t residue = kk_alg(a, len);
    printf("Residue: %lld\n", residue);

	free(p);
	free(a);
	free(seq);
	free(newnewS);
	free(newnewP);
	return 0;
}