int* repeatedRandom_standardRandom(int maxIter, int* S, int* A, int len){
	for(int i = 0; i < maxIter; i++){
		int* newS = standard_random(len);
		if (get_residue(A, newS, len) < get_residue(A, S, len)) {
			S = newS;
		}
	}
	return S;
}

int* repeatedRandom_preparition(int maxIter, int* S, int* p, int* a, int len){
	for(int i = 0; i < maxIter; i++){
		int* newA = prepartition(p, a, len);
		if(kk(newA) < kk(newA))
		{
			a = newA;
		}
	}

	return a;
}

int64_t* hillclimbing_standardRandom(int maxIter, int64_t* S, int64_t* A, int len){
	int64_t* newS = malloc(sizeof(int64_t) * len);
	for(int i = 0; i < maxIter; i++){
		standard_neighbor(S, newS, len);
		if (get_residue(A, newS, len) < get_residue(A, S, len)) {
			S = newS;
		}
	}
	free(newS);
	return S;
}


int64_t* hillclimbing_prepartition(int maxIter, int64_t* p, int64_t* a, int len){
	int64_t* aPrime = malloc(sizeof(int64_t) * len);
	int64_t* newP = malloc(sizeof(int64_t) * len);
	int64_t* newA = malloc(sizeof(int64_t) * len);
	for(int i = 0; i < maxIter; i++){
		prepartition(p, a, aPrime, len);
		prepartition_neighbor(p, newP, len);
		prepartition(newP, a, newA, len);
		printf("%lld\n", kk_alg(aPrime, len));
		if(kk_alg(aPrime, len) > kk_alg(newA, len))
		{
			p = newP;
		}
	}
	free(aPrime);
	free(newP);
	free(newA);
	return p;
}

int64_t T(int iter){
	return pow(10,10)*pow(.8,iter/300);
}

int64_t* annealing_standardRandom(int maxIter, int64_t* S, int64_t* A, int len, int64_t* newnewS){
	int64_t* newS = malloc(sizeof(int64_t) * len);
	for(int i = 0; i < maxIter; i++){
		standard_neighbor(S, newS, len);
		int64_t p = exp(-(get_residue(A, newS, len)-resnewA = get_residue(A, S, len))/T(iter))
		if (get_residue(A, newS, len) < get_residue(A, S, len)) {
			S = newS;
		} else if (rand()%p == 0) {
			S = newS;
		}
		if (get_residue(A, S, len) < get_residue(A, newnewS, len)) {
			newnewS = S;
		}
	}
	free(newS);
	return newnewS;
}

int64_t* annealing_prepartition(int maxIter, int64_t* p, int64_t* a, int len, int64_t* newnewP){
	int64_t* aPrime = malloc(sizeof(int64_t) * len);
	int64_t* newP = malloc(sizeof(int64_t) * len);
	int64_t* newA = malloc(sizeof(int64_t) * len);
	int64_t* newaPrime = malloc(sizeof(int64_t) * len);
	for(int i = 0; i < maxIter; i++){
		prepartition(p, a, aPrime, len);
		prepartition_neighbor(p, newP, len);
		prepartition(newP, a, newA, len);
		prepartition(newnewP, a, newaPrime,len)
		int p = exp(-(kk_alg(newA, len)-kk_alg(aPrime, len))/T(iter))
		if (kk_alg(aPrime, len) > kk_alg(newA, len)) {
			a = newA;
		} else if (rand()%p == 0) {
			p = newP;
		}
		if (kk(aPrime,len)< kk(newaPrime,len)) {
			newnewP = newP;
		}
	}
	free(aPrime);
	free(newP);
	free(newA);
	free(newaPrime);
	return newnewP;
}
