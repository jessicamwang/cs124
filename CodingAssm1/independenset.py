def T(n):
	if(n==0):
		return 1
	elif(n==1):
		return 2
	else:
		return T(n-1)+(2**(2**(n-1))-1)*T(n-2)

print(T(0))
print(T(1))
print(T(2))
print(T(3))
print(T(7))
