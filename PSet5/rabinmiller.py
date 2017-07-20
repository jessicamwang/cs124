import random

def evenfac(num):
	num -= 1
	count = 0
	while(num%2==0):
		num=num/2
		count+=1
	return[count,num]

def chooserand(num):
	a = random.randint(2,num-2)
	if(num%a==0):
		return chooserand(num)
	else:
		return a

def rabinMiller(n,k,c=True):
	r,d = evenfac(n)
	print r,d
	for x in range(0, k):
		a = chooserand(n)
		print "witness: " + str(a)
		x = pow(a,d,n)
		print x
		if(x==1 or x==n-1):
			continue
		for i in range(0,r-1):
			x = pow(x,2,n)
			if(x==1):
				print "i " + str(i)
				return "composite"
			if(x==n-1):
				continue
		if(c):
			continue
		else:
			return "composite"
	return "probably prime"

print 294409 
print rabinMiller(294409,10)