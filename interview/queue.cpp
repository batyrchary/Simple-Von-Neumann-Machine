#include <iostream>       // std::cout
#include <deque>          // std::deque
#include <list>           // std::list
#include <queue>          // std::queue

int main ()//Elements are pushed into the "back" of the specific container and popped from its "front".
{
  std::deque<int> mydeck (3,100);        // deque with 3 elements
  std::list<int> mylist (2,200);         // list with 2 elements

  std::queue<int> first;                 // empty queue
  std::queue<int> second (mydeck);       // queue initialized to copy of deque

  std::queue<int,std::list<int> > third; // empty queue with list as underlying container
  std::queue<int,std::list<int> > fourth (mylist);

  std::cout << "size of first: " << first.size() << '\n';
  std::cout << "size of second: " << second.size() << '\n';
  std::cout << "size of third: " << third.size() << '\n';
  std::cout << "size of fourth: " << fourth.size() << '\n';


////
  std::queue<int> myqueue;

  myqueue.push(12);
  myqueue.push(75);   // this is now the back

  myqueue.back() -= myqueue.front();

  std::cout << "myqueue.back() is now " << myqueue.back() << '\n';

  myqueue.emplace (10);
  myqueue.emplace (20);

  std::cout << "myqueue contains:\n";
  while (!myqueue.empty())
  {
    std::cout << myqueue.front() << '\n';
    myqueue.pop();
  }
/////
  std::queue<int> foo,bar;
  foo.push (10); foo.push(20); foo.push(30);
  bar.push (111); bar.push(222);

  foo.swap(bar);

  std::cout << "size of foo: " << foo.size() << '\n';
  std::cout << "size of bar: " << bar.size() << '\n';


///////



   std::priority_queue<std::string> mypq;

  mypq.emplace("orange");
  mypq.emplace("strawberry");
  mypq.emplace("apple");
  mypq.emplace("pear");
  mypq.push("melon");

  std::cout << "mypq contains:"<<mypq.size()<<" elements:";
  while (!mypq.empty())
  {
     std::cout << ' ' << mypq.top();

     mypq.pop();
  }
  std::cout << '\n';

  ///////
  std::priority_queue<int> foo2,bar2;
  foo2.push (15); foo2.push(30); foo2.push(10);
  bar2.push (101); bar2.push(202);

  foo2.swap(bar2);

  std::cout << "size of foo: " << foo2.size() << '\n';
  std::cout << "size of bar: " << bar2.size() << '\n';

  return 0;
}