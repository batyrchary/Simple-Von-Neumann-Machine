#include <iostream>
#include <vector> 
#include <time.h> 
#include <stdlib.h>

using namespace std;


double eval(int *pj);
int vec[100],vecReserve[100];
double fitnessBefore=0,fitnessAfter=0;
int window=1,offset=0,oldoffset=0;


void flip(int j)
{
	if(vec[j]==0)
		vec[j]=1;
	else
		vec[j]=0;		
}

void printer(int start, int end)
{
	for(int i=start; i<end; i++)
		cout<<vec[i]<<" ";	
	cout<<endl;
}


int modify(int window, int offset)
{
	for (int i=0; i<100; i++)
		vecReserve[i]=vec[i];

	int limit=window*10+offset;
	if (limit>100)
		limit=100;
	for(int i=offset; i<limit; i++)
	{
		if(i%window==0)
			flip(i);
	}
	return limit;
}



void init()
{
	for(int i = 0; i < 100; i++)
		vec[i] = 0;
	fitnessBefore=eval(vec);
}

void moveForward()
{
	fitnessBefore=fitnessAfter;
	window=1;
	oldoffset=offset;
}

void moveBack()
{
	for (int i=0; i<100; i++)
		vec[i]=vecReserve[i];
	window++;
	offset=oldoffset;
}

int main()
{
	init();

	while(fitnessAfter<100)
	{
		offset=modify(window,offset);
		fitnessAfter=eval(vec);

		if(fitnessBefore<fitnessAfter)
			moveForward();
		else
			moveBack();

		cout<<"Fitness="<<fitnessAfter<<endl;
		printer(0,100);
	}

}