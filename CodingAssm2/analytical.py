import math
import sys

def strassen(n, n0):
	if(n == n0 or n < n0):
		return n**2 * (2*n -1)
	elif(n % 2 == 0):
		return 7*strassen(n/2, n0) + 18*(n/2)**2
	else:
		return 7*strassen(math.ceil(n/2) + 1, n0) + 18*(n/2 +1)**2

for j in range(1,int(sys.argv[1])+1):
	print strassen(int(sys.argv[1]),j)
