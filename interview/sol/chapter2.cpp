#include<iostream>
using namespace std;

class Node
{
	public:
	int data;
	Node *next;
	Node(int d=int())
	{
		data=d;
		next=NULL;
	}
};
class LinkedList
{
public:
	Node *zeroth;
	LinkedList()
	{
		zeroth = new Node(int ());
	}
	void append(int d)
	{
		Node *newNode=new Node(d);
		Node *tmp=zeroth;
		
		while(tmp->next!=NULL)
			tmp=tmp->next;
		
		tmp->next=newNode;
	}
	void print()
	{
		Node *tmp=zeroth->next;
		
		while(tmp)
		{
			cout<<tmp->data<<endl;
			tmp=tmp->next;
		}
	}




	void remove(int index)
	{
		Node * tmp=zeroth;
		for(int i=1;i<index; i++)
		{
			tmp=tmp->next;
		}
		Node *del=tmp->next;
		tmp->next=tmp->next->next;
		delete del;
	}


	void removeDup2()
	{
		bool duplicate[256];
		for(int i=0; i<256; i++)
			duplicate[i]=false;

		Node *tmp=zeroth->next;
		
		if(tmp==NULL)
			return;

		duplicate[tmp->data]=true;
		while(tmp->next)
		{
			if(duplicate[tmp->next->data])
			{
				Node *del=tmp->next;
				tmp->next=tmp->next->next;
				delete del;
			}
			else
				tmp=tmp->next;
		}


	}



	void nthToLast(int n)
	{
		Node *first=zeroth;
		Node *second=zeroth;
		for(int i=0; i<n; i++)
		{
			second=second->next;
		}

		while(second->next)
		{
			first=first->next;
			second=second->next;
		}
		cout<<first->data<<endl;

	}


void deleteNode(Node *n)
{
	Node *del=n->next;
	n->data=n->next->data;
	n->next=n->next->next;
	delete del;
}


void Sum(Node *zeroth1, Node *zeroth2)
{
	int counter=0;

	Node *tmp1=zeroth1;
	Node *tmp2=zeroth2;

	while(tmp1->next && tmp2->next)
	{
		int sum=( tmp1->next->data+tmp2->next->data+counter)%10;
		counter=( tmp1->next->data+tmp2->next->data+counter)/10;
		tmp1->next->data=sum;
		tmp1=tmp1->next;
		tmp2=tmp2->next;
	}
	while(tmp1->next)
	{
		int sum=( tmp1->next->data+counter)%10;
		counter=( tmp1->next->data+counter)/10;
		tmp1->next->data=sum;
		tmp1=tmp1->next;
	}
	while(tmp2->next)
	{
		int sum=( tmp2->next->data+counter)%10;
		counter=( tmp2->next->data+counter)/10;
		Node *s=new Node(sum);
		tmp1->next=s;
		tmp2=tmp2->next;

	}
	if(counter)
	{
		cout<<"asd"<<endl;
		Node *s=new Node(counter);
		cout<<tmp1->data<<endl;
	
	}


}


void beginning(Node *zeroth)
{
	Node *first=zeroth;
	Node *second=zeroth;
	
	while(second->next!=null)
	{
		first=first->next;
		second=second->next->next;
		if(first==second)
			break;
	}
	cout<<first->data<<endl;
	
}


};







int main()
{
/*	LinkedList* list=new LinkedList();
	list->append(1);
	list->append(2);
	list->append(3);
	list->append(4);
	list->print();
	cout<<"-----"<<endl;
//	list->nthToLast(1);

	list->deleteNode(list->zeroth->next->next);
	list->print();	
*/
	LinkedList* list1=new LinkedList();
	list1->append(3);
	list1->append(1);
	list1->append(5);
	
	list1->print();
	cout<<"-----"<<endl;
	LinkedList* list2=new LinkedList();
	list2->append(5);
	list2->append(9);
	list2->append(5);
	list2->append(5);
	list2->print();
	cout<<"-----"<<endl;



	


//	list1->Sum(list1->zeroth,list2->zeroth);
//	list1->print();
	




	//list->removeDup2();
	//list->print();
}
