

reader=open("cc-est2019-alldata.csv")


data1_dic={}

for line in reader:

	line=line.strip("\n\r")
	if "SUMLEV" in line:
		continue

	splitted=line.split(",")

	state=splitted[3]
	county=splitted[4].split(" County")[0]
	year=int(splitted[5])
	AGEGRP=splitted[6]
	TOT_POP=splitted[7]
	TOT_MALE=splitted[8]
	TOT_FEMALE=splitted[9]

	if (state, county) in data1_dic:
		old=data1_dic.get((state, county))
		oldyear=old[0]
		if year>oldyear:
			old=[year,AGEGRP,TOT_POP,TOT_MALE,TOT_FEMALE]

		data1_dic[(state, county)]=old

	else:
		data1_dic[(state, county)]=[year,AGEGRP,TOT_POP,TOT_MALE,TOT_FEMALE]


reader=open("housing_unit.txt")
data2_dic={}
for line in reader:

	if "United States" in line:
		continue

	line=line.strip("\n\r")

	splitted=line.split("\t")
	county=splitted[0].split(",")[0].split(" County")[0]
	state=splitted[0].split(", ")[1]
	

	housing=splitted[1].replace(",","")
	data2_dic[(state, county)]=housing
	#print state,county


states=["Alabama","Alaska","Arizona","Arkansas","California","Colorado","Connecticut","Delaware","Florida","Georgia","Hawaii","Idaho","Illinois","Indiana","Iowa","Kansas","Kentucky","Louisiana","Maine","Maryland","Massachusetts","Michigan","Minnesota","Mississippi","Missouri","Montana","Nebraska","Nevada","New Hampshire","New Jersey","New Mexico","New York","North Carolina","North Dakota","Ohio","Oklahoma","Oregon","Pennsylvania","Rhode Island","South Carolina","South Dakota","Tennessee","Texas","Utah","Vermont","Virginia","Washington","West Virginia","Wisconsin","Wyoming"]


reader=open("gdp.txt")
data3_dic={}
currentState=""
for line in reader:
	
	splitted=line.split("\t")
	if splitted[0] in states:
		currentState=splitted[0]
		continue

	county=line.split("\t")[0]
	gdp=line.split("\t")[1].replace("\n","")

	data3_dic[(currentState, county)]=gdp
	



reader=open("COVID-19_US-counties.csv")

for line in reader:
	line=line.strip("\n\r")

	if "date" in line:
		print line+",AGEGRP,TOT_POP,TOT_MALE,TOT_FEMALE,Housing,gdp"
		continue

	state=line.split(",")[2]
	county=line.split(",")[1]


	printline=line
	if (state, county) in data1_dic:
		d1=data1_dic.get((state, county))
		string_d1 = [str(i) for i in d1]
		printline=printline+","+",".join(string_d1[1:])
	else:
		printline=printline+",,,,,"
		continue


	if (state, county) in data2_dic:
		d2=data2_dic.get((state, county))
		printline=printline+","+d2
	else:
		printline=printline+","
		continue

	if (state, county) in data3_dic:
		d3=data3_dic.get((state, county))
		printline=printline+","+d3
	else:
		printline=printline+","
		continue


	print printline











	
