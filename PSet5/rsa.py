s = "Give me an A"
a = [(ord(c)) for c in s]
for b,i in enumerate(a):
	a[b] = '{0:08b}'.format(a[b])

message = int(''.join(a),2)

def encode(n,e,x):
	return pow(x,e,n)

print encode (46947848749720430529628739081,37267486263679235062064536973,message)