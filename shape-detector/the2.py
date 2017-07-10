import math
def slope(slopeX):
	a = slopeX[0][0]
	b = slopeX[0][1]
	c = slopeX[1][0]
	d = slopeX[1][1]

	if a==c: return 'sth'
	else: return (d-b)/(c-a)


def geo_wizard(variable):
	x1 = variable[0][0]
	x2 = variable[1][0]
	x3 = variable[2][0]
	x4 = variable[3][0]
	y1 = variable[0][1]
	y2 = variable[1][1]
	y3 = variable[2][1]
	y4 = variable[3][1]

	p1=[x1,y1]
	p2=[x2,y2]
	p3=[x3,y3]
	p4=[x4,y4]

	s1=slope([p1,p2])
	s2=slope([p1,p3])
	s3=slope([p1,p4])
	s4=slope([p2,p3])
	s5=slope([p2,p4])
	s6=slope([p3,p4])


#####################################################
	if (x1 == x2 == x3 == x4) or (y1 == y2 == y3 == y4): 
		return 'Line'
	if abs(s1-s2)<=10**-3 and abs(s1-s3)<=10**-3 and abs(s1-s4)<=10**-3 and abs(s1-s5)<=10**-3 and abs(s1-s6)<=10**-3 and abs(s2-s3)<=10**-3 and abs(s2-s4)<=10**-3 and abs(s2-s5)<=10**-3 and abs(s2-s6)<=10**-3 and abs(s3-s4)<=10**-3 and abs(s3-s5)<=10**-3 and abs(s3-s6)<=10**-3 and abs(s4-s5)<=10**-3 and abs(s4-s6)<=10**-3 and abs(s5-s6)<=10**-3: 
		return 'Line'

#####################################################

	d=(2*(x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2)))

	cX = ((y1*y1+x1*x1)*(y2-y3)+(y2*y2+x2*x2)*(y3-y1)+(y3*y3+x3*x3)*(y1-y2))/d
	cY = ((y1*y1+x1*x1)*(x3-x2)+(y2*y2+x2*x2)*(x1-x3)+(y3*y3+x3*x3)*(x2-x1))/d
  
	r1=math.sqrt((x1-cX)*(x1-cX)+(y1-cY)*(y1-cY))
	r2=math.sqrt((x2-cX)*(x2-cX)+(y2-cY)*(y2-cY))
	r3=math.sqrt((x3-cX)*(x3-cX)+(y3-cY)*(y3-cY))
	r4=math.sqrt((x4-cX)*(x4-cX)+(y4-cY)*(y4-cY))

	if (abs(r4-r1)<=10**-3) and (abs(r4-r2)<=10**-3) and (abs(r4-r3)<=10**-3) and (abs(r3-r1)<=10**-3) and (abs(r3-r2)<=10**-3) and (abs(r2-r1)<=10**-3): 
		return 'Circle'

#####################################################


#Check for A
  	nA1 = ((x1-x2),(y1-y2))
	nC1 = ((x3-x2),(y3-y2))
	nD1 = ((x4-x2),(y4-y2))

	d1 = nC1[0]*nD1[1]-nD1[0]*nC1[1]

	Wa1 = (nA1[0]*(nC1[1]-nD1[1])+nA1[1]*(nD1[0]-nC1[0])+nC1[0]*nD1[1]-nD1[0]*nC1[1])/d1
	Wb1 = (nA1[0]*nD1[1]-nA1[1]*nD1[0])/d1
	Wc1 = (nA1[1]*nC1[0]-nA1[0]*nC1[1])/d1


#Check for B
	nB2 = ((x2-x1),(y2-y1))
	nC2 = ((x3-x1),(y3-y1))
	nD2 = ((x4-x1),(y4-y1))

	d2 = nC2[0]*nD2[1]-nD2[0]*nC2[1]

	Wa2 = (nB2[0]*(nC2[1]-nD2[1])+nB2[1]*(nD2[0]-nC2[0])+nC2[0]*nD2[1]-nD2[0]*nC2[1])/d2
	Wb2 = (nD2[1]*nB2[0]-nD2[0]*nB2[1])/d2
	Wc2 = (nC2[0]*nB2[1]-nB2[0]*nC2[1])/d2

#Check for C
	nB3 = ((x2-x1),(y2-y1))
	nC3 = ((x3-x1),(y3-y1))
	nD3 = ((x4-x1),(y4-y1))

	d3 = nB3[0]*nD3[1]-nD3[0]*nB3[1]

	Wa3 = (nC3[0]*(nB3[1]-nD3[1])+nC3[1]*(nD3[0]-nB3[0])+nB3[0]*nD3[1]-nD3[0]*nB3[1])/d3
	Wb3 = (nC3[1]*nB3[0]-nC3[0]*nB3[1])/d3
	Wc3 = (nC3[1]*nB3[0]-nC3[0]*nB3[1])/d3

#Check for D
	nB4 = ((x2-x1),(y2-y1))
	nC4 = ((x3-x1),(y3-y1))
	nD4 = ((x4-x1),(y4-y1))

	d4 = nB4[0]*nC4[1]-nC4[0]*nB4[1]

	Wa4 = (nD4[0]*(nB4[1]-nC4[1])+nD4[1]*(nC4[0]-nB4[0])+nB4[0]*nC4[1]-nC4[0]*nB4[1])/d4
	Wb4 = (nD4[0]*nC4[1]-nD4[1]*nC4[0])/d4
	Wc4 = (nD4[1]*nB4[0]-nD4[0]*nB4[1])/d4

	if (0<Wa1<1 and 0<Wb1<1 and 0<Wc1<1) or (0<Wa2<1 and 0<Wb2<1 and 0<Wc2<1) or (0<Wa3<1 and 0<Wb3<1 and 0<Wc3<1) or (0<Wa4<1 and 0<Wb4<1 and 0<Wc4<1):
		 return 'Arbitraryquadrilateral'
	elif ((1<=Wa1 or Wa1<=0) and (1<=Wb1 or Wb1<=0) and (1<=Wc1 or Wc1<=0)) or ((1<=Wa2 or Wa2<=0) and (1<=Wb2 or Wb2<=0) and (1<=Wc2 or Wc2<=0)) or ((1<=Wa3 or Wa3<=0) and (1<=Wb3 or Wb3<=0) and (1<=Wc3 or Wc3<=0)) or ((1<=Wa4 or Wa4<=0) and (1<=Wb4 or Wb4<=0) and (1<=Wc4 or Wc4<=0)): 
		return 'Triangle'

