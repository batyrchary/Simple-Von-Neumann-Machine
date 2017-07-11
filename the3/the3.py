import sys

distances=[]
indeces=[]

max_tuple=[1,2]

def dist(p1,p2):
	return ((p1[0]-p2[0])**2+(p1[1]-p2[1])**2)**0.5


def two_neighbors(element,lst):
	dis1=9876543211234567
	dis2=9876543211234567
	i1=-1
	i2=-1
	for e in lst:
		d=dist(element,e)
		if d<dis1:
			i1=lst.index(e)
			dis1=d
		elif d<dis2:
			i2=lst.index(e)
			dis2=d


	if dist(max_tuple[0],max_tuple[1]) > dis1 :
		max_tuple[0]=lst[i1]
		max_tuple[1]=element

	if dist(max_tuple[0],max_tuple[1]) > dis2 :
		max_tuple[0]=lst[i2]
		max_tuple[1]=element

	print "i1=",i1,"	i2=",i2,"	dis1=",dis1,"	dis2=",dis2






def order(lst):
	max_tuple[0]=lst[0]
	max_tuple[1]=lst[1]
	
	for element in lst:
		two_neighbors(element, lst)

	return lst


givenList = [ [2.4492935982947064e-16, 4.0], [2.0000000000000004, 3.4641016151377544] , [4.0, 0.0] , [-3.4641016151377539, 2.0000000000000013],[-1.9999999999999991, 3.4641016151377548] , [3.4641016151377548, 1.9999999999999998] ]
print order(givenList)