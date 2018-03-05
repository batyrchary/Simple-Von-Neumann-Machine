
#include<iostream>
using namespace std;

void printer(int A[],int size)
{
	for(int i=0; i<size; i++)
		cout<<A[i]<<" ";
	cout<<endl;
}

void merge(int A[], int B[], int sizeA, int endA, int endB)
{
	int currentindex=endA+endB+1;
	for(int i=currentindex; i>=0; i--)
	{
		if(endB<0)
		{
			A[i]=A[endA];
			endA--;
		}
		else if(endA<0)
		{
			A[i]=B[endB];
			endB--;
		}
		else if(A[endA]>B[endB])
		{
			A[i]=A[endA];
			endA--;
		}	
		else
		{
			A[i]=B[endB];
			endB--;
		}	
	}
}

int findRotationPoint(int A[], int start, int end)
{
	int middle=(start+end)/2;
	if(A[start]==A[middle])	
		return start;
	
	if(A[start]>A[middle])
		return findRotationPoint(A, start, middle);

	else if (A[middle]>A[end])
		return findRotationPoint(A, middle, end);

	return -1;
}
int findInRotated(int A[], int start, int end, int f)
{
	//cout<<"start="<<start<<",end="<<end<<endl;
	int middle=(start+end)/2;

	if(f==A[middle])	
		return middle;

	
	if (A[start]>A[middle]) //irregular
	{
		if(A[middle]>f || A[start]<=f)
		{
			return findInRotated (A, start, middle-1, f);
		}
	}
	else if (A[start]<A[middle]) //regular
	{
		if(A[start]<=f && A[middle]>f)
		{
			return findInRotated (A, start, middle-1, f);
		}
	}


	if (A[end]<A[middle]) //irregular
	{
		if(A[middle]<f || A[end] >= f)
		{
			return findInRotated (A, middle+1, end, f);
		}
	}
	else if (A[end]>A[middle]) //regular
	{
		if(A[end]>=f && A[middle]<f)
		{
			return findInRotated (A, middle+1, end, f);
		}
	}
	return -1;
}

int index(string array[], int size)
{
	int current=0;
	for(int i=0; i<size; i++)
	{
		if(array[i]!="")
		{
			string tmp=array[i];
			array[i]=array[current];
			array[current]=tmp;
			current++;
		}
	}
	return 0;
	/*for(int i=0; i<size; i++)
	{
		cout<<array[i]<<endl;
	}
	cout<<endl;
	*/
}
int indexfinder(int array[], int start,int end,int str)
{
	int middle=(start+end)/2;
	if(array[middle]==str)
		return middle;
	
	int newend=middle-1;
	int newstart=middle+1;
	while(array[newend]==-1 && newend>=start)
		newend--;
	
	while(array[newstart]==-1 && newstart<=end)
		newstart++;

	if(array[newend]>=str)
		return indexfinder(array,start,newend,str);
	

	if(array[newstart]<=str)
		return indexfinder(array,newstart,end,str);

	return -1;
}


/*
Step 1. Sort all items by height  rst, and then by weight. This means that if all the heights are unique, then the items will be sorted by their height.
If heights are the same, items will be sorted by their weight.
Step 2. Find the longest sequence which contains increasing heights and increasing weights.
a) Start at the beginning of the sequence. Currently, max_sequence is empty.
b) If, for the next item, the height and the weight is not greater than those of the previous item, we mark this item as “un t” .
c) If the sequence found has more items than “max sequence”, it becomes “max sequence”. d) After that the search is repeated from the “un t item”, until we reach the end of the origi- nal sequence.
*/

int main()
{

	string stringarray[]={"at", "", "", "", "ball", "", "", "car", "", "", "dad", "", ""};

	int intarray[]={1, -1, -1, -1, 2, -1, -1, 3, -1, -1, 4, -1, -1};
	//cout<<index(stringarray,13, )<<endl;
	cout<<indexfinder(intarray,0,12,3)<<endl;

	int A[15]={1,3,5,7,9};
	int B[]={2,4,6,8};
	
	merge(A,B,9,4,3);
	printer(A,15);
	
	int rot[]={6,7,8,9,10,11,12,1,2,3,4,6};
	//cout<<findRotationPoint(rot, 0,11)<<endl;


	/*cout<< findInRotated(rot,0,11,1)<<endl;
	cout<< findInRotated(rot,0,11,2)<<endl;
	cout<< findInRotated(rot,0,11,3)<<endl;
	cout<< findInRotated(rot,0,11,4)<<endl;
	cout<< findInRotated(rot,0,11,5)<<endl;
	cout<< findInRotated(rot,0,11,6)<<endl;
	cout<< findInRotated(rot,0,11,7)<<endl;
	cout<< findInRotated(rot,0,11,8)<<endl;
	cout<< findInRotated(rot,0,11,9)<<endl;
	cout<< findInRotated(rot,0,11,10)<<endl;
	cout<< findInRotated(rot,0,11,11)<<endl;
	cout<< findInRotated(rot,0,11,12)<<endl;
*/	





}



