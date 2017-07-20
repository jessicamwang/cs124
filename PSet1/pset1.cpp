#include <iostream>
#include <limits.h>
using namespace std;

// recursive fib that will run until overflow int
// this program w
int recursive (int i, int j) {
	// check if next fib number is overflow int and will stop
	if(INT_MAX - j < i)
	{
		// return last fib number before overflow
		return j;
	}
	// call recursive function until overflow reaches
	return recursive(j, i+j);
}

// calculate the counter'th fib number
int recursive_mod_helper(int i, int j, int counter){
	// until counter is 0
	if (counter > 0){
		// sets new counter for recursive that is counter -1
		int newcounter = counter - 1;
		// call recursive with new counter
		// mod 2^15 to avoid seg fault
		recursive_mod_helper(j, (i+j)%32768, newcounter);
	}
	return counter;
}

// will find first fib number that takes over 1 min
int recursive_mod (int i, int j, int counter) {
	// set timer to 60 sec
	time_t end = time(NULL) + 60;
	// find counter'th fib number
	recursive_mod_helper(j, (i+j), counter);
	// if timer is still under 60 sec, run again with counter +1
    if (time(NULL) <= end)
    {
        int newcounter = counter + 1;
        recursive_mod(j, (i+j), newcounter);
    }
    // if timer is over 60 sec return counter-1 number 
    // counter is the nth fib num to be calculated under 1 min
    else {
    	cout << (counter-1) << '\n';
    	return counter-1;
    }
	return 0;
}

// find nth fib number through the iterative method
int iterative (int n) {
	// creates array and sets initial values
	int a [n+1];
	a[0] = 0;
	a[1] = 1;
	// loops through spaces of array
	for(int i = 2 ; i < n+1; i++) {
		a[i] = a[i-1] + a[i-2];
	}
	// returns nth fib number
	return a[n];
}

// find what is nth big number to be calculated in 1 min
int iterative_mod () {
	// sets array with initial values
	int a [3] = {1,1,2};
	// intializes counter of nth fib number
	int counter = 3;
	// sets timer end to 60 sec
	time_t end = time(NULL) + 60;
	// runs program for 60 sec
    while (time(NULL) <= end)
    {
        // changes value of array in iterative method mod 2^15
        int two = a[1];
        int three = a[2];
        a[2] = (a[0]+a[1])%32768;
        a[0] = two;
        a[1] = three;
        // increase counter of fib number
        counter++;
    }
    // returns nth fib number
    cout << counter << '\n';
	return counter;
}

// returns 2^nth fib number
int matrix(int n){
	// intializes matrix
	int matrix [4] = {0,1,1,1};
	// squares matrix n times
	// calculates matrix^(2^n))
	for(int i=0; i < n; i++){
        int first= matrix[0]*matrix[0] + matrix[1]*matrix[2];
		int second = matrix[0]*matrix[1] + matrix[1]*matrix[3];
		int third = matrix[2]*matrix[0] + matrix[3]*matrix[2];
		int fourth = matrix[2]*matrix[1] + matrix[3]*matrix[3];
		matrix[0] =first;
		matrix[1] =second;
		matrix[2] =third;
		matrix[3] =fourth;
	}
	// returns 2^nth fib number
	return matrix[1];
}

// returns n where 2^n is the highest fib number calculated in 1 min
int matrix_mod () {
	// intializes matrix
	int matrix [4] = {0,1,1,1};
	// intializes counter for 2^nth fib number
	int counter = 3;
	// intialzes timer end to 60 sec
	time_t end = time(NULL) + 60;
	// runs until timer runs out in 1 min
    while (time(NULL) <= end)
    {
    	// squares matrix mod 2^15
    	int first= (matrix[0]*matrix[0] + matrix[1]*matrix[2])%32768;
		int second = (matrix[0]*matrix[1] + matrix[1]*matrix[3])%32768;
		int third = (matrix[2]*matrix[0] + matrix[3]*matrix[2])%32768;
		int fourth = (matrix[2]*matrix[1] + matrix[3]*matrix[3])%32768;
		matrix[0] =first;
		matrix[1] =second;
		matrix[2] =third;
		matrix[3] =fourth;
		// increments counter
        counter++;
    }
    // returns n where 2^n is last fib number calculated in 1 min
    cout << counter << '\n';
	return counter;
}

int main() {
	// calculates average time of 9 recursive fib number until int overflow
	clock_t start_r = clock();
	recursive(1,1);
	recursive(1,1);
	recursive(1,1);
	recursive(1,1);
	recursive(1,1);
	recursive(1,1);
	recursive(1,1);
	recursive(1,1);
	recursive(1,1);
	clock_t end_r = clock();
	double time_r = (double) (end_r - start_r) / CLOCKS_PER_SEC /9 * 1000;
	cout << time_r << '\n';

	// calculates average time of 9 iterative fib number until int overflow
	clock_t start_i = clock();
	iterative(46);
	iterative(46);
	iterative(46);
	iterative(46);
	iterative(46);
	iterative(46);
	iterative(46);
	iterative(46);
	iterative(46);
	clock_t end_i = clock();
	double time_i = (double) (end_i - start_i) / CLOCKS_PER_SEC  /9 * 1000;
	cout << time_i << '\n';

	// calculates average time of 9 iterative fib number of 2^6th fib number
	clock_t start_m = clock();
	matrix(6);
	matrix(6);
	matrix(6);
	matrix(6);
	matrix(6);
	matrix(6);
	matrix(6);
	matrix(6);
	matrix(6);
	clock_t end_m = clock();
	double time_m = (double) (end_m - start_m) / CLOCKS_PER_SEC  /9 * 1000;
	cout << time_m << '\n';

	// returns nth fib number recursive method calculates in 1 min
	// recursive_mod(1,1,0);
	// returns nth fib number iterative method calculates in 1 min
	iterative_mod();
	// returns n where 2^nth fib number matrix method calculates in 1 min
	matrix_mod();

	return 0;
}