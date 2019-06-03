#include <iostream>

using namespace std;

double eval(int *pj);

int vec[100];
double fitness,fitness1,fitness2=0;

void printer(int start, int end)
{
	for(int i=start; i<end; i++)
		cout<<vec[i]<<" ";	
	cout<<endl;
}

void init()
{
	for(int i = 0; i < 100; i++)
		vec[i] = 0;
}

int main()
{

	init();
	while(fitness2!=100)
	{
		for(int j = 0; j<100; j++)
		{
			fitness1=eval(vec);
			vec[j]=1;	
			fitness2=eval(vec);
			
			if(fitness1>fitness2)
				vec[j]=0;

			if (fitness2 == 100)
				break;

			cout << "fitness = " << fitness2 << endl;
			printer(0,100);
		}
		cout << "fitness = " << fitness2 << endl;
		printer(0,100);
	}

}

