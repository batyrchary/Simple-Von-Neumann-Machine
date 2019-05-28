import sys

def readMatrix(dimension):
	print ("Enter payoff matrix:")
	
	matrix=[]
	minimum=100

	lastrow=[]
	for i in range(0, dimension):
		row=raw_input()

		splitted=row.split(",")

		splitted = map(float, splitted)
		
		m=min(splitted)
		if m<minimum:
			minimum=m
		matrix.append(splitted)

		lastrow.append(-1.0)

	added=0
	if (minimum<0):
		added=minimum*(-1)

	
	for i in range(0,len(matrix)):
		row=matrix[i]
		for r in range(0,len(row)):
			row[r]=row[r]+added
		row.append(1.0)
		matrix[i]=row

	lastrow.append(0.0)
	matrix.append(lastrow)

	return [matrix, added]

def checkNeg(row):

	ret=0
	for r in row:
		if r<0:
			ret=1
			break
	return ret





def getColumn(matrix,column_index):

	column=[]
	for row_index in range(0,len(matrix)-1):
		row=matrix[row_index] 
		column.append(row[column_index])

	return column

def choosePivot(matrix,dimension):

	last_row=matrix[dimension]
	column_index=0

	for entry in last_row:
		if(entry<0):
			break
		column_index=column_index+1

	column=getColumn(matrix,column_index)
	lastColumn=getColumn(matrix,dimension)


	ratio=sys.float_info.max
	index=-1
	for i in range(0, len(column)):
		if column[i]<0:
			continue

		newRatio=sys.float_info.max-10
		if(column[i]!=0):
			newRatio=(lastColumn[i]/column[i])

		if(newRatio<ratio):
			ratio=newRatio
			index=i

#	print column
#	print lastColumn
	

	return [index,column_index]


def giveType(xy,rc):
	

	x1=xy[0]
	y1=xy[1]
	x2=rc[0]
	y2=rc[1]

	p=[]
	q=[]
	r=[]
	c=[]

	index=0
	if(x1==x2 and y1==y2):
		index=0
		p=[x1,y1]
		q=[x1,y1]
	
		r=[x1,y1]
		c=[x1,y1]
	

	elif(x1>x2 and y1>y2):#upleft
		index=1
		
		p=[x1,y1]
		q=[x2,y2]

		#r=[x2,y1]
		#c=[x1,y2]		

		c=[x2,y1]
		r=[x1,y2]		


	elif(x1>x2 and y1<y2):#upright
		index=1
		
		p=[x1,y1]
		q=[x2,y2]

		#r=[x2,y1]
		#c=[x1,y2]		

		c=[x2,y1]
		r=[x1,y2]		


	elif(x1<x2 and y1>y2):#bottomleft
		index=1
		
		p=[x1,y1]
		q=[x2,y2]

		r=[x1,y2]
		c=[x2,y1]	

	
	elif(x1<x2 and y1<y2):#bottomright
		index=1
		
		p=[x1,y1]
		q=[x2,y2]

		r=[x1,y2]
		c=[x2,y1]



	elif(x1>x2 and y1==y2): #up
		index=2
		
		p=[x1,y1]
		r=[x2,y2]

		difference=x1-x2
		difference=1
		y3=y1-difference
		if(y1-difference<0):
			y3=y1+difference



		q=[x2,y3]
		c=[x1,y3]




	elif(x1<x2 and y1==y2): #bottom
		index=3
		
		p=[x1,y1]
		c=[x2,y2]

		difference=x2-x1
		difference=1

		y3=y1-difference
		if(y1-difference<0):
			y3=y1+difference			


		q=[x2,y3]
		r=[x1,y3]

	
	elif(x1==x2 and y1>y2): #left
		index=2
		difference=y1-y2
		difference=1

		p=[x1,y1]
		
		down=False
		x3=x1-difference
		

		if(x1-difference<0):
			x3=x1+difference
			down=True

		if(down==True):
			r=[x2,y2]
			index=2
			q=[x3,y2]
			c=[x3,y1]

		else:
			c=[x2,y2]
			index=3
			q=[x3,y2]
			r=[x3,y1]

	elif(x1==x2 and y1<y2): #right
		index=2
		
		p=[x1,y1]

		down=False
		difference=y2-y1
		difference=1
		
		x3=x1-difference
		if(x1-difference<0):
			x3=x1+difference
			down=True


		if(down==True):
			r=[x2,y2]
			index=2
			q=[x3,y2]
			c=[x3,y1]

		else:
			c=[x2,y2]
			index=3
			q=[x3,y2]
			r=[x3,y1]



	return [p,q,r,c,index]








		




def giveValue(matrix,pqrcIndex):

	index=pqrcIndex[4]

	pi=pqrcIndex[0]#p_coordinate
	qi=pqrcIndex[1]#q_coordinate
	ri=pqrcIndex[2]#r_coordinate
	ci=pqrcIndex[3]#c_coordinate


	#print(pqrcIndex)
	#print(qi)

	#print(matrix)

	p=matrix[pi[0]][pi[1]]
	q=matrix[qi[0]][qi[1]]
	r=matrix[ri[0]][ri[1]]
	c=matrix[ci[0]][ci[1]]

	if(index==0): #p
		return 1.0/p

	elif(index==1): #q
		return q-((r*c)/p)

	elif(index==2): #r
		return r/p

	else: #c
		return (-1.0*c)/p





def iteration(matrix,dimension):

	xy=choosePivot(matrix,dimension)

	retMatrix=[]
	
	#print xy

	for r in range(0, dimension+1):
		row=[]
		for c in range(0, dimension+1):
			pqrcIndex=giveType(xy,[r,c])

		#	print(pqrcIndex)
			value=giveValue(matrix,pqrcIndex)
			if(value==0):
				value=0
			row.append(value)

			

		retMatrix.append(row)

	return [retMatrix,xy]








if __name__ == '__main__':

	
	d = raw_input("Enter dimension:")
	dimension=int(d)


	rowheader=dimension*[1]
	columnheader=dimension*[0]



	ret=readMatrix(dimension)

	matrix=ret[0]
	added=ret[1]


	
	print "Payoffs matrix"
	for i in range(0,dimension):
			row=matrix[i]
			printline="\t"
			for r in range(0,dimension):
				printline=printline+str(row[r]-added)+"\t"
			
			print printline


	corner=1.0
	while (checkNeg(matrix[dimension]) == 1):

		#print("-------------")
		#for r in matrix:
		#	print r

		matrix_pivot=iteration(matrix,dimension)	

		matrix=matrix_pivot[0]
		pivot=matrix_pivot[1]


		######flippingHeaders
		tmp=rowheader[pivot[0]]
		rowheader[pivot[0]]=columnheader[pivot[1]]
		columnheader[pivot[1]]=tmp


		######


	#	print("-------------")

	#	for r in matrix:
	#		print r

		corner=matrix[dimension][dimension]



	lastrow=matrix[dimension]
	lastcol=getColumn(matrix,dimension)


	print ("")
	print("-------------")
	
#	print (lastrow)
#	print (lastcol)

	'''
	print("-------------")
	print (rowheader)
	print (columnheader)

	print("-------------")
	'''


	'''
	print "Final augmented payoffs matrix"
	for i in range(0,dimension+1):
			row=matrix[i]
			printline="\t"
			for r in range(0,dimension+1):
				printline=printline+str(row[r])+"\t"
			
			print printline


	print ("")
	'''




	printline="Player1 strategies->"
	


	for i in range(0, len(rowheader)):
		
		value=0
		if(rowheader[i]==0):
			value=lastrow[i]/corner

			if(value<0):
				value=value*(-1)

#		printline=printline+"\t"+str(round(value,3))
		printline=printline+"\t"+str(value)


	print printline
	printline="Player2 strategies->"
	

	for i in range(0, len(columnheader)):
		value=0
		if(columnheader[i]==1):
			value=lastcol[i]/corner

			if(value<0):
				value=value*(-1)


#		printline=printline+"\t"+str(round(value,3))
		printline=printline+"\t"+str(value)

	print printline


	print "Value of game: "+str((1.0/corner)-added)




	




