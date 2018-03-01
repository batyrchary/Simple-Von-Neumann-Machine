//List containers are implemented as doubly-linked lists;
//forward_list objects are single-linked lists,

#include <iostream>
using namespace std;
#include <list>

int main ()
{
  // constructors used in the same order as described above:
  list<int> first;                                // empty list of ints
  list<int> second (4,100);                       // four ints with value 100
  list<int> third (second.begin(),second.end());  // iterating through second
  list<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
 first.swap(second);

  second.assign (first.begin(),first.end()); // a copy of first

  int myints[]={1776,7,4};
  first.assign (myints,myints+3); 

cout<<first.front()<<endl; //front returns reference begin returns iterator poiting to beginning
cout<<first.back()<<endl; //back returns reference end returns iterator poiting to beginning


  std::cout << "The contents of fifth are: ";
  for (std::list<int>::iterator it = fourth.begin(); it != fourth.end(); it++)
    std::cout << *it << ' ';

  cout << '\n';

int sum (0);
list<int> mylist;
mylist.clear();

 for (int i=1;i<=10;++i) mylist.push_back(i);

mylist.remove(3); //Removes from the container all the elements that compare equal to val.
mylist.sort(); //nlogn
  while (!mylist.empty())
  {
     sum += mylist.front();
     mylist.pop_front();
  }



list<int>::iterator it;
it = mylist.begin();
  ++it;       // it points now to number 2

  mylist.insert (it,10);   

  return 0;
}