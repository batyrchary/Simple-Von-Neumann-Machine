
from itertools import combinations
import math

groundList=[]
myList=[]

def twocombination(n):
	if(n==0):
		return 0
	
	#comb=math.factorial(n)/(2*math.factorial(n-2))
	comb=(n*(n-1))/2	
	return comb

#0 dem
#1 gop
def calculateTP():

	demTrue=[]
	demFalse=[]
	gopTrue=[]
	gopFalse=[]

	returned=[]

	counter=0
	TP=0
	for item in myList:

		if item=='0' and item == groundList[counter]:
			demTrue.append(item)
		if item=='0' and item != groundList[counter]:
			demFalse.append(item)
		if item=='1' and item == groundList[counter]:
			gopTrue.append(item)
		if item=='1' and item != groundList[counter]:
			gopFalse.append(item)
		counter=counter+1	
	
	lnDT=float(len(demTrue))
	lnDF=float(len(demFalse))
	lnGT=float(len(gopTrue))
	lnGF=float(len(gopFalse))

	comb1=twocombination(lnDT)
	comb2=twocombination(lnDF)
	comb3=twocombination(lnGT)
	comb4=twocombination(lnGF)
	
	TP=comb1+comb2+comb3+comb4
	returned.append(TP)

	FP=lnDT*lnDF+lnGT*lnGF
	returned.append(FP)

	FN=lnDT*lnGF+lnGT*lnDF
	returned.append(FN)
	'''
	print len(demTrue)
	print len(demFalse)
	print len(gopTrue)
	print len(gopFalse)
	'''
	purity=(max(lnDT, lnDF) + max(lnGT, lnGF))/(len(myList))
	returned.append(purity)

	return returned

if __name__ == '__main__':

	mine = open("gephi.csv","r")
	ground = open("label.txt","r")

	for line in mine:
		line=line.strip("\n")
		label=line.split(",")[1]
		groundList.append(label)


	for line in ground:
		line=line.strip("\n")
		myList.append(line)

	returned=calculateTP()
	TP=float(returned[0])
	FP=float(returned[1])
	FN=float(returned[2])
	purity=float(returned[3])
	print "TP="+str(TP)
	print "FP="+str(FP)
	print "FN="+str(FN)
	
	precision=TP/(TP+FP)
	recall=TP/(TP+FN)

	print "purity="+str(purity)
	print "precision="+str(precision)
	print "recall="+str(recall)








