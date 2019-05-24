cmX = 0.0
cmY = 0.0
mass = 0.0
Pi = 3.1415926535897932
def cm(L):
	global cmX
	cmX=0
	global cmY
	cmY=0
	global mass
	mass=0
	def Equal(a,b):
		if(abs(a-b) < 0.000001):
			return True
		return False
	def Rec(Child):
		global cmX 
		global cmY
		global mass
		global Pi
		CircleMass = 0.0
		TriangleMass = 0.0
		a=0.0
		if (Child == []):
			return [cmX , cmY , mass]
		if (len(Child[0]) == 9):#rectangle
			Distance1 = ( (Child[0][1] - Child[0][3])**2 + (Child[0][2] - Child[0][4])**2 )**0.5# x1  x2
			Distance2 = ( (Child[0][1] - Child[0][5])**2 + (Child[0][2] - Child[0][6])**2 )**0.5# x1  x3
			Distance3 = ( (Child[0][1] - Child[0][7])**2 + (Child[0][2] - Child[0][8])**2 )**0.5# x1  x4
			Distance4 = ( (Child[0][3] - Child[0][5])**2 + (Child[0][4] - Child[0][6])**2 )**0.5# x2  x3
			Distance5 = ( (Child[0][3] - Child[0][7])**2 + (Child[0][4] - Child[0][8])**2 )**0.5# x2  x4
			Distance6 = ( (Child[0][5] - Child[0][7])**2 + (Child[0][6] - Child[0][8])**2 )**0.5# x3  x4
			a = max(Distance1,Distance2,Distance3,Distance4,Distance5,Distance6)
			#print a
			#print Distance1
			#print Distance2
			#print Distance3
			#print Distance4
			#print Distance5
			#print Distance6
			if ( Equal(a,Distance1)):
				x1=Child[0][1]
				y1=Child[0][2]
				x2=Child[0][3]
				y2=Child[0][4]
				
				x3=Child[0][5]
				y3=Child[0][6]
				
				x4=Child[0][7]
				y4=Child[0][8]
			
			elif (  Equal(a,Distance2)):
				x1=Child[0][1]
				y1=Child[0][2]
				x2=Child[0][5]
				y2=Child[0][6]
				
				x3=Child[0][3]
				y3=Child[0][4]
				
				x4=Child[0][7]
				y4=Child[0][8]
				
			elif( Equal(a,Distance3) ):
				x1=Child[0][1]
				y1=Child[0][2]
				x2=Child[0][7]
				y2=Child[0][8]
				
				x3=Child[0][3]
				y3=Child[0][4]
				
				x4=Child[0][5]
				y4=Child[0][6]
			
			elif( Equal(a,Distance4)):
				x1=Child[0][3]
				y1=Child[0][4]
				x2=Child[0][5]
				y2=Child[0][6]
				
				x3=Child[0][1]
				y3=Child[0][2]
				
				x4=Child[0][7]
				y4=Child[0][8]
				
			elif( Equal(a,Distance5)):
				x1=Child[0][3]
				y1=Child[0][4]
				x2=Child[0][7]
				y2=Child[0][8]
				
				x3=Child[0][1]
				y3=Child[0][2]
				
				x4=Child[0][5]
				y4=Child[0][6]
			
			elif( Equal(a,Distance6)):
				x1=Child[0][5]
				y1=Child[0][6]
				x2=Child[0][7]
				y2=Child[0][8]
				
				x3=Child[0][1]
				y3=Child[0][2]
				
				x4=Child[0][3]
				y4=Child[0][4]
				
			Triangle1 = (abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0)
			x11=float(x1+x2+x3)/3.0
			y11=float(y1+y2+y3)/3.0
			
			Triangle2 = (abs(x1 * (y2 - y4) + x2 * (y4 - y1) + x4 * (y1 - y2)) / 2.0)
			x22=float(x1+x2+x4)/3.0
			y22=float(y1+y2+y4)/3.0
			
			cmXXX=(x11 * Triangle1 + x22 * Triangle2)/(Triangle1 + Triangle2)
			cmYYY=(y11 * Triangle1 + y22 * Triangle2)/(Triangle1 + Triangle2)
			massSSS=Triangle1 + Triangle2
			massSSS=massSSS*Child[0][0]
			
			cmX=(cmX * mass + cmXXX * massSSS)/(massSSS + mass)
			cmY=(cmY * mass + cmYYY * massSSS)/(massSSS + mass)
			mass=massSSS + mass	
								
			#rectangle code"""
		if (len(Child[0]) == 7):
			#triangle code
			TriangleMass = Child[0][0]*(abs(Child[0][1] * (Child[0][4] - Child[0][6]) + Child[0][3] * (Child[0][6] - Child[0][2]) + Child[0][5] * (Child[0][2] - Child[0][4])) / 2.0)
			x=float(Child[0][1]+Child[0][3]+Child[0][5])/3.0
			y=float(Child[0][2]+Child[0][4]+Child[0][6])/3.0
			cmX=(cmX * mass + x * TriangleMass)/(TriangleMass + mass)
			cmY=(cmY * mass + y * TriangleMass)/(TriangleMass + mass)
			mass=TriangleMass + mass
		if (len(Child[0]) == 4):
			#circle code
			CircleMass = Pi * float(Child[0][3]) * float(Child[0][3]) * float(Child[0][0])
			cmX = (cmX * mass + float(Child[0][1]) * CircleMass) / (mass + CircleMass)
			cmY = (cmY * mass + float(Child[0][2]) * CircleMass) / (mass + CircleMass)
			mass += CircleMass
			#print "girdi"
		return Rec(Child[1::])
	return Rec(L)
