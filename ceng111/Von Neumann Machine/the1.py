import os

data=[]
all_line=""
R1=0
R2=0
I=0

def zero():
	print "halting"
def one(): ##done
	global R1,R2,I
	R1=int(data[I+1])
	I=I+2

def two(): ##done
	global R1,R2,I	
	R2=int(data[I+1])
	I=I+2

def three(): ##done
	global R1,R2,I
	R1=int(data[int(data[I+1])])
	I=I+2

def four(): ##done
	global R1,R2,I
	R2=int(data[int(data[I+1])])
	I=I+2

def five(): ##done
	global R1,R2,I
	R1=R2
	I=I+1

def six(): ##done
	global R1,R2,I
	R1=int(data[R2])
	I=I+1

def seven(): ##done
	global R1,R2,I	
	data[int(R1)]=R2
	I=I+1

def eight(): ##done
	global R1,R2,I
	data[int(data[I+1])]=R1
	I=I+2

def nine(): ##done
	global R1,R2,I
	I=int(data[I+1])
	
def ten():
	global R1,R2,I
	if R1==0:
		I=I+2
	else:
		I=int(data[I+1])

def eleven(): ##done
	global R1,R2,I
	R1=R1+R2
	I=I+1

def twelve(): ##done
	global R1,R2,I
	R1=R1-R2
	I=I+1

def thirteen(): ##done
	global R1,R2,I
	R1=R1*R2
	I=I+1

def fourteen(): ##done
	global R1,R2,I
	R1=R1/R2
	I=I+1

def fifteen(): ##done
	global R1,R2,I
	R1=-R1
	I=I+1

def sixteen(): ##done
	global R1,R2,I
	if R1==R2:
		R1=0
	elif R1>R2:
		R1=1
	else:
		R1=-1
	I=I+1

options = {0 : zero,
           1 : one,
           2 : two,
           3 : three,
           4 : four,
           5 : five,
           6 : six,
           7 : seven,
           8 : eight,
           9 : nine,
           10 : ten,
           11 : eleven,
           12 : twelve,
           13 : thirteen,
           14 : fourteen,
           15 : fifteen,
           16 : sixteen,
}

with open("./input.txt") as f:
	content = f.readlines()
	all_line=all_line+content[-1].strip()

data=all_line.split(" ")

print "instructions:\n"
print data

print "\nR1 =",R1,"     R2 =",R2,"     I =",I,"\n"

ins=int(data[I]) 

while ins != 0:
	if ins < 0 or ins > 255 : 
		print "invalid instruction skipped\n"
	else:
		options[ins]()
		print "\nR1 =",R1,"     R2 =",R2,"     I =",I,"\n"
	ins=int(data[I])	

