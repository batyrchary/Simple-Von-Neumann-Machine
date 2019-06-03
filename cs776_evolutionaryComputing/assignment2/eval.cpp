#include <iostream>
#include <vector>
using namespace std;


#define NQUEENS 15

int eval( int* state)
{
	int N=150;

  int numconflicts = 0;
  for(int i = 0; i < N; i++)
    {
      for(int j = i+1; j < N; j++)
	{
	  int diag = j-i;
	  if(state[i] == state[j])
	    numconflicts++;
	  if(state[i] == state[j]+diag) 
	    numconflicts++;
	  if(state[i] == state[j]-diag)
	    numconflicts++;
	}
    }
  return numconflicts;

}