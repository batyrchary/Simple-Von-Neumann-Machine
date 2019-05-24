def exchange(st):
	i=0
	arr=[]
	while(i<len(st)):
		if(st[i]=='/'):
			arr.append('*')
		elif(st[i]=='*'):
			arr.append('/')
		else:
			arr.append(st[i])
		i=i+1
	return ''.join(arr)
def putss(st,index,op):
	sl=st[:index]
	sr=st[index+1:]
	
	if(sl[-1]!='('):
		sl=sl[:-1]+')'+sl[-1]##parantez yoksa 
	elif(sl[-1]=='('):#parazntez varsa###########daha kontrol edilmedi
		s=sl[::-1]
		k=0
		count=0
		inn=0
		for k in range (len(s)):
			 if(s[k]=='('):
			 	count=count+1
			 elif(s[k]==')'):
			 	count=count-1
			 if(count==0):
				inn=k
				break
		s=s[:inn]+')'+s[inn:]
		sl=s[::-1]
		
	if(sr[0]!=')'):
		sr=sr[0]+'('+sr[1:]##parantez yoksa 
	elif(sr[0]==')'):#parazntez varsa ############### kontrol edilmedi
		kk=0
		countt=0
		for kk in range (len(sr)):
			 if(sr[kk]==')'):
			 	countt=countt+1
			 elif(sr[kk]=='('):
			 	countt=countt-1
			 if(countt==0):
				innn=kk
				break
		sr=sr[:innn]+'('+sr[innn:]
	return sl+op+sr

def Eputss(st,index,op):
	sl=st[:index]
	sr=st[index+1:]
	
	if(sl[-1]!='('):
		sl=sl[:-1]+')'+sl[-1]##parantez yoksa 
	elif(sl[-1]=='('):#parazntez varsa###########daha kontrol edilmedi
		s=sl[::-1]
		k=0
		count=0
		inn=0
		for k in range (len(s)):
			 if(s[k]=='('):
			 	count=count+1
			 elif(s[k]==')'):
			 	count=count-1
			 if(count==0):
				inn=k
				break
		s=s[:inn]+')'+s[inn:]
		sl=s[::-1]
		
	if(sr[0]!=')'):
		sr=sr[0]+'('+sr[1:]##parantez yoksa 
	elif(sr[0]==')'):#parazntez varsa ############### kontrol edilmedi
		kk=0
		countt=0
		for kk in range (len(sr)):
			 if(sr[kk]==')'):
			 	countt=countt+1
			 elif(sr[kk]=='('):
			 	countt=countt-1
			 if(countt==0):
				innn=kk
				break
		sr=sr[:innn]+'('+sr[innn:]
	return sl+op+sr


def putt(st,index):
	
	sl=st[:index]
	sr=st[index:]#da duryo operator	
	if(sl[-1]!=')'):
		sl=sl[:-1]+'('+sl[-1]##parantez yoksa 
							############sikintili		
	elif(sl[-1]==')'):#parazntez varsa ################bakmadim
		s=sl[::-1]
		k=0
		count=0
		inn=0
		for k in range (len(s)):
			 if(s[k]=='('):
			 	count=count+1
			 elif(s[k]==')'):
			 	count=count-1
			 if(count==0):
				inn=k
				break
		s=s[:inn]+'('+s[inn:]
		sl=s[::-1]
	
	if(sr[1]!='('):
		sr=sr[0]+sr[1]+')'+sr[2:]##parantez yoksa 
	
	elif(sr[1]=='('):#parazntez varsa
		s=sr[::1]
		k=1
		count=0
		inn=0
		while (k<(len(s))):
			 #print 'k'
			 #print k
			 if(s[k]=='('):
			 	count=count+1
			 elif(s[k]==')'):
			 	count=count-1
			 if(count==0):
				inn=k
				break
			 k=k+1
		
		s=s[:inn]+')'+s[inn:]
		sr=s[::1]
	return sl+sr
def Eputt(st,index):
	
	sl=st[:index]
	sr=st[index:]#da duryo operator	
	if(sl[-1]!=')'):
		sl=sl[:-1]+'('+sl[-1]##parantez yoksa 
							############sikintili		
	elif(sl[-1]==')'):#parazntez varsa ################bakmadim
		s=sl[::-1]
		k=0
		count=0
		inn=0
		for k in range (len(s)):
			 if(s[k]=='('):
			 	count=count+1
			 elif(s[k]==')'):
			 	count=count-1
			 if(count==0):
				inn=k
				break
		s=s[:inn]+'('+s[inn:]
		sl=s[::-1]
	
	if(sr[1]!='('):
		sr=sr[0]+sr[1]+')'+sr[2:]##parantez yoksa 
	
	elif(sr[1]=='('):#parazntez varsa
		s=sr[::1]
		k=1
		count=0
		inn=0
		while (k<(len(s))):
			 #print 'k'
			 #print k
			 if(s[k]=='('):
			 	count=count+1
			 elif(s[k]==')'):
			 	count=count-1
			 if(count==0):
				inn=k
				break
			 k=k+1
		
		s=s[:inn]+')'+s[inn:]
		sr=s[::1]
	return sl+sr

		

def puts(st,op):
	sst=st
	if(op==10):#operation for '^'
		i=0
		count=0
		while(i<len(st)):
			if(st[i]=='^'):
				count=count+1
			i=i+1
		i=0
		
		st=st[::-1]
		if(count>0):
			for i in range (count):
				ii=0		
				k=0
				for k in range (len(st)):
					if(st[k]=='^'):
						ii=ii+1
						if((ii-1)==i):
							sst=putss(st,k,'^')
							break				
				st=sst
			sst=sst[::-1]
		
		
	elif(op==5):#operation for '*' and '/'
		i=0
		count=0
		while(i<len(st)):
			if(st[i]=='*' or st[i]=='/'):
				count=count+1
			i=i+1
		i=0
		if(count>0):
			for i in range (count):
				ii=0		
				k=0
				for k in range (len(st)):
					if(st[k]=='*' or st[k]=='/'):
						ii=ii+1
						if((ii-1)==i):
						#st=st
						#print "nigga"#dogry berya
						#print st
						#print k
						#print "nigga"
							sst=putt(st,k)
				st=sst
			sst=sst
	elif(op==3):#operation for '+' and '-'
		i=0
		count=0
		while(i<len(st)):
			if(st[i]=='+' or st[i]=='-'):
				count=count+1
			i=i+1
		i=0
		if(count>0):
			for i in range (count):
				ii=0		
				k=0
				for k in range (len(st)):
					if(st[k]=='+' or st[k]=='-'):
						ii=ii+1
						if((ii-1)==i):
						#st=st
						#print "nigga"#dogry berya
						#print st
						#print k
						#print "nigga"
							sst=putt(st,k)
				st=sst
			sst=sst
		
	return sst
def Eputs(st,op):
	sst=st
	if(op==2):#operation for '^'
		i=0
		count=0
		while(i<len(st)):
			if(st[i]=='^'):
				count=count+1
			i=i+1
		i=0
		
		st=st[::-1]
		if(count>0):
			for i in range (count):
				ii=0		
				k=0
				for k in range (len(st)):
					if(st[k]=='^'):
						ii=ii+1
						if((ii-1)==i):
							sst=Eputss(st,k,'^')
							break				
				st=sst
			sst=sst[::-1]
		
		
	elif(op==3):#operation for '*' and '/'
		i=0
		count=0
		while(i<len(st)):
			if(st[i]=='*'):####################################surda sikindi olabilir
				count=count+1
			i=i+1
		i=0
		if(count>0):
			for i in range (count):
				ii=0		
				k=0
				for k in range (len(st)):
					if(st[k]=='*'):
						ii=ii+1
						if((ii-1)==i):
						#st=st
						#print "nigga"#dogry berya
						#print st
						#print k
						#print "nigga"
							sst=Eputt(st,k)
				st=sst
			sst=sst
	elif(op==10):#operation for '+' and '-'
		i=0
		count=0
		while(i<len(st)):
			if(st[i]=='+'):
				count=count+1
			i=i+1
		i=0
		if(count>0):
			for i in range (count):
				ii=0		
				k=0
				for k in range (len(st)):
					if(st[k]=='+'):
						ii=ii+1
						if((ii-1)==i):
						#st=st
						#print "nigga"#dogry berya
						#print st
						#print k
						#print "nigga"
							sst=Eputt(st,k)
				st=sst
			sst=sst
	elif(op==5):#operation for '+' and '-'
		i=0
		count=0
		while(i<len(st)):
			if(st[i]=='-'):
				count=count+1
			i=i+1
		i=0
		if(count>0):
			for i in range (count):
				ii=0		
				k=0
				for k in range (len(st)):
					if(st[k]=='-'):
						ii=ii+1
						if((ii-1)==i):
						#st=st
						#print "nigga"#dogry berya
						#print st
						#print k
						#print "nigga"
							sst=Eputt(st,k)
				st=sst
			sst=sst
	elif(op==8):#operation for '*' and '/'
		i=0
		count=0
		while(i<len(st)):
			if(st[i]=='/'):####################################surda sikindi olabilir
				count=count+1
			i=i+1
		i=0
		if(count>0):
			for i in range (count):
				ii=0		
				k=0
				for k in range (len(st)):
					if(st[k]=='/'):
						ii=ii+1
						if((ii-1)==i):
						#st=st
						#print "nigga"#dogry berya
						#print st
						#print k
						#print "nigga"
							sst=Eputt(st,k)
				st=sst
			sst=sst
	
	return sst




def ToEarthian(st1):
	earr=[]
	eupdate=[]
	i=0
	#erasing spaces
	while(i<len(st1)):
		if(st1[i]!=' '):
			earr.append(st1[i])
		i=i+1
	###################################################
	estr=''.join(earr)
	estr=Eputs(estr,10)#puts paranthesis for +
	estr=Eputs(estr,8)#puts paranthesis for /
	estr=Eputs(estr,5)#puts paranthesis for -
	estr=Eputs(estr,3)#puts paranthesis for *
	estr=Eputs(estr,2)#puts paranthesis for ^
	estr=exchange(estr)# * ve / yerdegishtiryo	
	return estr




def ToZoitankian(st1):
	earr=[]
	eupdate=[]
	i=0
	#erasing spaces
	while(i<len(st1)):
		if(st1[i]!=' '):
			earr.append(st1[i])
		i=i+1
	###################################################
	estr=''.join(earr)
	estr=puts(estr,10)#puts paranthesis for ^
	estr=puts(estr,5)#puts paranthesis for * /
	estr=puts(estr,3)#puts paranthesis for + -
	estr=exchange(estr)# * ve / yerdegishtiryo	
	return estr
	#return ''.join(earr)
