import sys
# Split text file into string array
words = []
with open('buffy.txt', 'r') as lines:
	for line in lines:
		for word in line.split(" "):
			words.append(word)
lines.close()

# Intialize n
n = len(words)

# Intialize M and outfile
out = open('outfile40.txt', 'w')
M = 40

# Initilaize penality matrix and calculate values
penaltiyMatrix = [[0]*n for i in range(n)]
for i in range(0, n):
	for j in range(i,n):
		characterSum = 0
		for k in range(i,j+1):
			characterSum += len(words[k])
		if (M-j+i-characterSum < 0):
			penaltiyMatrix[i][j] = None
		else:
			penaltiyMatrix[i][j]= (M-j+i-characterSum)**3

# Initialize optimalPenalty and lineBreaks
optimalPenalty = [None]*n
lineBreaks = [None]*n

# evaulate optimalPenalty and lineBreaks
for i in range(n-1,-1,-1):
	# Intialize and set current minPenalty to int max
	minPenalty = sys.maxint
	# Intialize and set current line break to i (line only has word i)
	lineBreak = i

	# If words i to n fit in one line
	# 	Set optimalPenalty[i]=0 an lineBreaks[n] 
	# 	This indicates optimal configuration is one line
	if(penaltiyMatrix[i][n-1] != None):
		optimalPenalty[i]=0
		lineBreaks[i]=n

	# If words i to n don't fit into one line
	# Implement recursive step as discuessed in pset
	else:
		for k in range(i,n):
			if(penaltiyMatrix[i][k]== None):
				continue
			else:
				currentPenalty = penaltiyMatrix[i][k]+optimalPenalty[k+1]
				if (currentPenalty < minPenalty):
					minPenalty = currentPenalty
					lineBreak = k
		optimalPenalty[i] = minPenalty
		lineBreaks[i] = lineBreak

# Use lineBreaks to print out text
# lineBreaks allow you to find when to move to next line
# Discribed in pset
breakIndex = 0
while(breakIndex<n):
	endWord = lineBreaks[breakIndex]
	if (endWord == n):
		for i in range (breakIndex, endWord):
			out.write(words[i] + " ")
	else:
		for i in range (breakIndex, endWord +1):
			out.write(words[i] + " ")
		out.write('\n')
	breakIndex = endWord + 1

# #################################################################
# Initialize new M and outfile
M = 72
out1 = open('outfile72.txt', 'w')

# Initilaize penality matrix and calculate values
penaltiyMatrix = [[0]*n for i in range(n)]
for i in range(0, n):
	for j in range(i,n):
		characterSum = 0
		for k in range(i,j+1):
			characterSum += len(words[k])
		if (M-j+i-characterSum < 0):
			penaltiyMatrix[i][j] = None
		else:
			penaltiyMatrix[i][j]= (M-j+i-characterSum)**3

# Initialize optimalPenalty and lineBreaks
optimalPenalty = [None]*n
lineBreaks = [None]*n

# evaulate optimalPenalty and lineBreaks
for i in range(n-1,-1,-1):
	# Intialize and set current minPenalty to int max
	minPenalty = sys.maxint
	# Intialize and set current line break to i (line only has word i)
	lineBreak = i

	# If words i to n fit in one line
	# 	Set optimalPenalty[i]=0 an lineBreaks[n] 
	# 	This indicates optimal configuration is one line
	if(penaltiyMatrix[i][n-1] != None):
		optimalPenalty[i]=0
		lineBreaks[i]=n

	# If words i to n don't fit into one line
	# Implement recursive step as discuessed in pset
	else:
		for k in range(i,n):
			if(penaltiyMatrix[i][k]== None):
				continue
			else:
				currentPenalty = penaltiyMatrix[i][k]+optimalPenalty[k+1]
				if (currentPenalty < minPenalty):
					minPenalty = currentPenalty
					lineBreak = k
		optimalPenalty[i] = minPenalty
		lineBreaks[i] = lineBreak

# Use lineBreaks to print out text
# lineBreaks allow you to find when to move to next line
# Discribed in pset
breakIndex = 0
while(breakIndex<n):
	endWord = lineBreaks[breakIndex]
	if (endWord == n):
		for i in range (breakIndex, endWord):
			out1.write(words[i] + " ")
	else:
		for i in range (breakIndex, endWord +1):
			out1.write(words[i] + " ")
		out1.write('\n')
	breakIndex = endWord + 1