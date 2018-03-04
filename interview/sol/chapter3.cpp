#include<iostream>
#include <vector>

using namespace std;


class Stackthree
{
	public:
	int threeStack[150];
	
	int maxCapacity;
	int top[3]={0,0,0};
	int current[3]={0,0,0};
	
	Stackthree()
	{
		//top[3]={0,0,0};
		//this->current={0,0,0};
		maxCapacity=50;
	}
	void push(int index, int newitem)
	{
		if(current[index]>maxCapacity)
			cout<<"exceeding"<<endl;

		current[index]++;
		threeStack[index*50+top[index]]=newitem;
		top[index]++;
	
	}
	void pop(int index, int &ret)	
	{
		if(current[index]<=0)
			cout<<"empty"<<endl;

		current[index]--;
		ret = threeStack[index*50+top[index]];
		top[index]--;
	}
};








class StackNode
{
	public:
	int item;
	StackNode* next;
	StackNode(int i=int())
	{
		item=i;
		next=NULL;		
	}
};
class Stack
{
	public:
	StackNode* top;
	int current;
	int numberofstacks;
	StackNode* mintop;
	vector<StackNode*> topofstacks;
	Stack()
	{
		top=NULL;
		mintop=NULL;
		//topofstacks=new vector();
		current=0;
		numberofstacks=0;
	}
	void push(int item)
	{
		/*if(mintop!=NULL)
		{
			if(item<=mintop->item )
			{
				StackNode *newN=new StackNode(item);
				newN->next=mintop;
				mintop=newN;
			}		
		}
		else
		{
			StackNode *newN=new StackNode(item);
				newN->next=mintop;
				mintop=newN;

		}*/

		

		StackNode* newNode=new StackNode(item);
		newNode->next=top;
		top=newNode;
		current++;



		if(current==3)
		{
			topofstacks.push_back(top);
			current=0;
			top=NULL;
		}

	}











	void pop(int &item)
	{
		
		if(current==0)
		{
			top=topofstacks[topofstacks.size()-1];
			topofstacks.pop_back();
			current=3;
		}
		StackNode* newNode=top;
		top=top->next;
		item=newNode->item;
		delete newNode;

		/*if(item==mintop->item)
		{
			StackNode *newN=mintop;
			mintop=mintop->next;
			delete newN;
		}*/
		current--;
		



	}
	/*int min()
	{
		return mintop->item;
	}*/






};


int main()
{

	Stack *mystack=new Stack();
	int i;
	mystack->push(5);
	mystack->push(15);
	//cout<<mystack->min()<<endl;
	mystack->push(3);
	//cout<<mystack->min()<<endl;
	mystack->pop(i);
	cout<<i<<endl;
	mystack->push(51);
	//cout<<mystack->min()<<endl;
	mystack->push(15);
	mystack->push(53);
	//cout<<mystack->min()<<endl;
	mystack->pop(i);
	cout<<i<<endl;
	//cout<<mystack->min()<<endl;
	mystack->push(5);

	mystack->push(2);
	//cout<<mystack->min()<<endl;
	mystack->push(1);
	mystack->pop(i);
	cout<<i<<endl;

	
}

/*
#include<iostream>
using namespace std;
#include<stack>

/*class Tower
{
	stack<int> disks;
	int index;

	
	int index()
	{
		return index;
	}
	void add(int disk)
	{
		if(disks.Empty() || disks.top>disk)
			disks.push(disk);
	}
	void moveTo(Tower destination)
	{
		int top=this->top();
		destination.add(top);
		this->pop();
	}
	void moveAll(int n, Tower destination, Tower buffer)
	{
		if(n>0)
		{
			moveAll(n-1, buffer, destination);
			moveTo(destination);
			buffer.moveAll(n-1,destination, this)
		}
	}

};*/

/*

	class MyQueue
{
	stack<int> s1,s2;
	
	MyQueue()
	{
		s1=new stack<int>();
		s2=new stack<int>();
	}
	void enqueue(int item)
	{
		s1.push(item);
	}

	int dequeue()
	{
		if(!s2.Empty())
			return s2.topPop();
		while(!s1.Empty())
			s2.push(s1.topPop());
		
		return s2.topPop();
	}
	
	int size()
	{
		return s1.size()+s2.size();
	}
	bool Empty()
	{
		return (s1.Empty() && s2.Empty());
	}


};*/
/*void Sort(stack<int> sOriginal, stack<int>sSorted)
{
	while(!sOriginal.Empty())
	{
		int item=sOriginal.topPop();
		while(sSorted.top()<item)
		{
			sOriginal.push(sSorted.topPop());	
		}
		sSorted.push(item);
	}
}*/









