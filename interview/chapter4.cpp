#include<iostream>
using namespace std;

int maxDepth(BinarNode* root)
{
	if(root==NULL)
		return 0;
	
	return Math.max(maxDepth(root->right),maxDepth(root->left))+1;
	
}
int minDepth(BinaryNode* root)
{
	if(root==NULL)
		return 0;
	return Math.min(minDepth(root->right),minDepth(root->left))+1;
}

bool balanced (BinaryNode* node)
{
	
	return maxDepth(node)-minDepth(node)<=1;	

}

///
/*
#include <iostream>
using namespace std;
#include <vector>
#include <queue>
#include <stack>


class Node{
	public:
	int item;
	vector<Node*>children;
	bool visited;
	Node(int d=int())
	{
		item=d;
		visited=false;
	}
};
bool routeFinderBFS(Node* source, Node* target){
	queue<Node*> Q;
	Q.push(source);
	
	while(!Q.empty())
	{
		Node* tmp=Q.front();
		Q.pop();
		if(tmp->visited)
			continue;		

		tmp->visited=true;
		cout<<"visited="<<tmp->item<<endl;
		if(tmp==target)
		{
			cout<<"done"<<endl;
			return true;
		}
		else
		{
			int numberofChild=tmp->children.size();
			for(int i=0; i< numberofChild; i++)
			{
				Q.push(tmp->children[i]);
			}
		}
	}
	return false;
}


bool routefinderDFS(Node* start, Node* target)
{
	stack<Node*> S;
	S.push(start);
		
	while(!S.empty())
	{
		Node* tmp=S.top();
		S.pop();
		
		if(tmp->visited)
			continue;	
		tmp->visited=true;
		cout<<"visited="<<tmp->item<<endl;
		if(tmp==target)
		{
			cout<<"done"<<endl;
			return true;
		}
		
		for(int i=tmp->children.size()-1; i>=0; i--)
		{
			S.push(tmp->children[i]);
		}

	}

	return false;	

}




int main()
{
	Node* start=new Node(1);

	for(int i=2; i<7; i++)
		start->children.push_back(new Node(i));

	for(int i=0; i<5; i++)
	{
		for(int j=10; j<15; j++)
			start->children[i]->children.push_back(new Node(j));
	}
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			for(int k=20; k<25; k++)
				start->children[i]->children[j]->children.push_back(new Node(k));
		}
	}


	//routeFinderBFS(start, start->children[2]->children[2]);//->children[1]);
	routefinderDFS(start, start->children[2]);//->children[2]);//->children[1]);
	
}

*/

/*
#include <iostream>
using namespace std;

class BinaryNode
{
public:
	int item;
	BinaryNode* right;
	BinaryNode* left;
	BinaryNode(int d=int())
	{
		item=d;
		right=NULL;	
		left=NULL;
	}
};

void  createBinaryTree(int array[], BinaryNode* root, int start, int end )
{
	if(start==end)
	{
		root->item=array[start];
		return;
	}
	else if(start+1==end)
	{
		root->item=array[end];
		root->left=new BinaryNode(array[start]);
		return;
	}
		
	int middle=(start+end)/2;

	BinaryNode* left=new BinaryNode();
	BinaryNode* right=new BinaryNode();
	
	root->right=right;
	root->left=left;

	root->item=array[middle];
	createBinaryTree(array, left, start, middle-1);
	createBinaryTree(array, right, middle+1, end);	
	
}
void print(BinaryNode* root)
{
	if(root==NULL)
		return;
	cout<<root->item<<endl;
	print(root->left);
	print(root->right);
}


int main()
{
	int array[10]={1,2,3,4,5,6,7,8,9,10};
	BinaryNode* root=new BinaryNode();
	createBinaryTree(array, root, 0,9);

	print(root);

}



*/


/*
#include<iostream>
using namespace std;
#include<queue>
#include<list>

class BinaryNode
{
	public:
	int item;
	BinaryNode* right;
	BinaryNode* left;
	
	BinaryNode(int d=int())
	{
		item=d;
		right=NULL;
		left=NULL;
	}	
};

void Link(BinaryNode* root)
{
	queue<BinaryNode*> Q;
	Q.push(root);
	Q.push(new BinaryNode(-1));
	vector<list<BinaryNode*>*> lists;
	list<BinaryNode*>* currentLevel=new list<BinaryNode*>();
	while(!Q.empty())
	{
		BinaryNode* tmp=Q.front();
		Q.pop();


		if(tmp->item==-1)
		{
			cout<<tmp->item<<endl;
			lists.push_back(currentLevel);
			currentLevel=new list<BinaryNode*>();
			if(Q.size()!= 0)
				Q.push(new BinaryNode(-1));
			continue;
		}
		currentLevel->push_back(tmp);
		cout<<tmp->item<<endl;
		if(tmp->left!=NULL)
			Q.push(tmp->left);
		if(tmp->right!=NULL)
			Q.push(tmp->right);
	}

	cout<<lists.size()<<endl;
	for(int i=0; i<lists.size(); i++)
	{
		for(int j=0; j<lists[i]->size(); j++)
		{	cout<<"item="<<lists[i]->front()->item<<endl;
			lists[i]->pop_front();
			j--;

		}

		cout<<endl;
	}

}

int main()
{
	BinaryNode* root=new BinaryNode(5);
	root->right= new BinaryNode(8);
	root->left= new BinaryNode(3);

	Link(root);

	
}



*/
/*
#include<iostream>
using namespace std;
#include<queue>
#include<list>

class BinaryNode
{
	public:
	int item;
	BinaryNode* right;
	BinaryNode* left;
	
	BinaryNode(int d=int())
	{
		item=d;
		right=NULL;
		left=NULL;
	}
	BinaryNode* insert(int d, int R)
	{
		if(R==1){
			right=new BinaryNode(d);
			return right;
		}
		else
		{
			left=new BinaryNode(d);
			return left;
		}
	}

};
void print(BinaryNode* root)
{
	if(root==NULL)
		return;
	cout<<root->item<<endl;
	print(root->left);
	print(root->right);
	
	
}

BinaryNode* findRoot(BinaryNode* large, BinaryNode* small)
{

	queue<BinaryNode*> q;

	q.push(large);

	while(!q.empty())
	{
	 	BinaryNode* tmp=q.front();
	 	q.pop();

	 	if(tmp->item==small->item)
	 		return tmp;

	 	if(tmp->left!=NULL)
		 	q.push(tmp->left);
		 if(tmp->right!=NULL)
		 	q.push(tmp->right);
	}
	return NULL;


	cout<<"item="<<large->item<<endl;
	if(large==NULL)
		return NULL;
	if(large->item == small->item)
		return large;
	
	BinaryNode* ret= findRoot(large->left, small);
	BinaryNode* ret2= findRoot(large->right, small);
	
	if(ret==NULL)
		return findRoot(large->right, small);
	return ret;
}
bool Match(BinaryNode* T1, BinaryNode* T2)
{
	if(T1==NULL && T2==NULL)
		return true;
	if(T1->item==T2->item)
		return (Match(T1->left, T2->left) && Match(T1->right, T2->right));
	else
		return false;
}
void printer(int sum, vector<int> path, int level) 
{
	for(int i=level; i>=0; i--)
	{
		sum=sum-path[i];
		cout<<path[i]<<" ";
		if(sum==0)
		{
			cout<<endl;
			break;
		}
	}

}

void findsum(BinaryNode* root, int sum, vector<int> path, int level)
{
	if(root==NULL)
		return;
	path.push_back(root->item);
	int tmp=sum;
	for(int i=level; i>=0; i--)
	{
		tmp=tmp-path[i];
		if(tmp==0)
		{
			printer(sum,path,level);
			break;
		}
	}
	if(root->left!=NULL)
		findsum(root->left,sum,path, level+1);
	if(root->right!=NULL)
		findsum(root->right,sum,path, level+1);

}





int main()
{
	BinaryNode* root=new BinaryNode(5);
	
	BinaryNode* newN=root->insert(4,1);

	newN=newN->insert(6,1);
	newN->insert(22,0);
	newN=newN->insert(2,1);
	newN=newN->insert(9,0);
	newN->insert(7,0);
	newN=newN->insert(43,1);
	newN=newN->insert(32,0);


	newN=root->insert(3,0);

	newN->insert(11,1);
	newN=newN->insert(33,0);
	newN->insert(21,1);
	newN=newN->insert(10,0);
	newN->insert(8,0);
	newN=newN->insert(53,1);
	newN=newN->insert(90,0);



//BinaryNode* root2=new BinaryNode(10);
//root2->insert(8,0);
//newN=root2->insert(53,1);
//newN=newN->insert(90,0);

BinaryNode* root2=new BinaryNode(2);
newN=root2->insert(9,0);
newN->insert(7,0);
newN=newN->insert(43,1);
newN=newN->insert(32,0);

std::vector<int> v;

findsum(root,15,v,0);

	print(root);
	cout<<"----"<<endl;
	print(root2);
cout<<"----"<<endl;
cout<<findRoot(root,root2)->item<<endl;
cout<<"----"<<endl;

	cout<<Match(findRoot(root,root2),root2)<<endl;

	
}



*/