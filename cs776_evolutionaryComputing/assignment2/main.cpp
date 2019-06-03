#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector> 

using namespace std;

double eval(int *pj);


int vec[150];

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
	{
		if(i%50==0)
			cout<<endl;
		cout<<vec[i]<<" ";	
	}
	cout<<endl;
}

void simpleHillClimber(int iteration)
{
	int fitness1=0;
	int fitness2=0;

	for(int i=0; i<iteration; i++)
	{
		//for(int j = 0; j<150; j++)
		for(int j = 0; j<150; j=j+2)
		{
			flip(j);
			flip(j+1);	
			fitness2=eval(vec);
			
			if(fitness1>fitness2)//revert
			{
				flip(j);
				flip(j+1);
			}
			else
				fitness1=fitness2;

			//if(1>(rand() % 20))
			//{
			//	flip(rand() % 150);
			//	fitness1=eval(vec);
			//}

			if (fitness2 == 100)
				break;

			//cout << "fitness = " << fitness2 << endl;
			printer(0,150);
			cout << "fitness = " << fitness1 << endl;
		}
		cout << "fitness = " << fitness1 << endl;
	}
}


void randomHillClimber(int iteration)
{
	int fitness1=0;
	int fitness2=0;

	for(int i=0; i<iteration; i++)
	{
		int r=rand() % 150;
		flip(r);	
		fitness2=eval(vec);
			
		if(fitness1>fitness2) //&& (99>rand() % 100))//revert
		{
			flip(r);	
		}
		else
			fitness1=fitness2;
			
		if (fitness2 == 100)
			break;
		printer(0,150);
		cout << "fitness = " << fitness1 << endl;
	}
	//printer(0,150);
}




void init()
{
	for(int i = 0; i < 150; i++)
  		vec[i] = 0;
}

vector<int> maxdata;
void combinationUtil(int arr[], int data[], int start, int end, int index, int r, int maxFitness)
{
    if (index == r)
    {
        for (int j=0; j<r; j++)
        {
           // cout<<data[j]<<" ";
        	flip(data[j]);
        }
		double fitness=eval(vec);

		if (fitness<maxFitness)
		{
			for (int j=0; j<r; j++)
        		flip(data[j]);
		}
		else
		{	
			maxdata.clear();
			for (int j=0; j<r; j++)
				maxdata.push_back(data[j]);

			for (int j=0; j<r; j++)
        		flip(data[j]);

        	//cout<<"maxFitness"<<fitness<<endl;
			maxFitness=fitness;
		}
        return;
    }
    for (int i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i+1, end, index+1, r,maxFitness);
    }
}

void printCombination(int arr[], int n, int r)
{
    int data[r];
    double maxFitness=0;
    combinationUtil(arr, data, 0, n-1, 0, r,maxFitness);
}

void partition(int offset, int size)
{
	int array[size];
		
	for(int i=offset,j=0; i<offset+size; i++,j++)
		array[j]=i;


	for(int i=1; i<=size;i++)
	{
		printCombination(array,size,i);

		//cout<<"<<<<<<<<<<<<<<<>>>>>>>>>>>>>"<<endl;
	}
	for (vector<int>::iterator it = maxdata.begin(); it != maxdata.end(); ++it)
    	flip(*it);
    //printer(offset,offset+size);	
  	
}

void dimensionReduced(int offset, int size)
{
	double fitnessBefore=0,fitnessAfter=0;

	int partitions=150/size;
	int array[partitions];
		
	for(int i=offset,j=0; i<150; j++)
	{	array[j]=i;
		i=i+size;
	}
	int counter=0;
	for(int j=0; j<partitions; j++)
	{
		for(int k=0; k<partitions; k++)
		{
			//cout<<array[(k+j)%partitions]<<" ";
			int startingPoint=array[(k+j)%partitions];

			for(int c = 0; c < 150; c++)
				vec[c] = 0;
			
			for(int i=startingPoint; i<150; i=i+size)
			{
				partition(i,size);
				fitnessAfter=eval(vec);

				if(fitnessBefore>fitnessAfter)//revertchanges
				{
					for (vector<int>::iterator it = maxdata.begin(); it != maxdata.end(); ++it)
						flip(*it);
				}
				else
				{
					fitnessBefore=fitnessAfter;
				}
			}
			for(int i=0; i<startingPoint; i=i+size)
			{
				partition(i,size);
				fitnessAfter=eval(vec);

				if(fitnessBefore>fitnessAfter)//revertchanges
				{
					for (vector<int>::iterator it = maxdata.begin(); it != maxdata.end(); ++it)
						flip(*it);
				}
				else
				{
					fitnessBefore=fitnessAfter;
				}
			}

			if(fitnessBefore >99)
				return;
			printer(0,150);
			cout<<"fitness="<<fitnessBefore<<endl;
			counter++;
		}
		cout<<endl;
	}
}



void parallelHillClimbers(int number)
{

	int fitness1=0;
	int fitness2=0;
	for(int i=0; i<number; i++)
	{
		int initial=rand() % 150;

		int a=initial;
		int b=initial;

		for(; a<150 || b>-1; a++, b--)
		{

			if(a<150)
			{
				flip(a);
				fitness2=eval(vec);
				
				if(fitness1>fitness2)//revert
					flip(a);
				else
					fitness1=fitness2;
			}

			if(b>-1)
			{
				flip(b);
				
				fitness2=eval(vec);
				
				if(fitness1>fitness2)//revert
					flip(b);
				else
					fitness1=fitness2;
			}
			printer(0,150);
			cout << "fitness = " << fitness1 << endl;
		}
	}

}

int myvec[]=
{ 

1,0,1,0,1,0,1,1,0,1,1,0,0,1,0,

0,0,1,1,1,0,0,1,0,1,0,1,0,1,1,

0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,


0,1,1,0,0,1,0,0,0,1,1,0,0,1,0,
0,1,1,0,0,1,0,0,0,1,1,0,0,1,0,




0,1,1,0,0,0,0,0,1,1,1,0,0,1,0,
0,1,1,0,0,0,0,0,1,1,1,0,0,1,0,

0,1,1,0,0,1,0,0,1,1,1,0,0,1,0,
0,1,1,0,0,1,0,0,1,1,1,0,0,1,0,

0,0,0,0,0,0,0,0,0,0,0,0,0,0,0


};


int main()
{
 	init();

// 	cout<<"fitness = "<<eval(myvec)<<endl;

// 	simpleHillClimber(1000);
 //	randomHillClimber(10000);


 	
	dimensionReduced(0,5);//offset,size
	
//	parallelHillClimbers(1000);
  

}