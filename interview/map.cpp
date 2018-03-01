#include <iostream>
using namespace std;
#include <map>
#include <string>

int main ()
{
  map<char,string> mymap;

  mymap['a']="an element";
  mymap['b']="another element";
  mymap['c']=mymap['b'];

  cout << "mymap['a'] is " << mymap['a'] << '\n';
  cout << "mymap['b'] is " << mymap['b'] << '\n';
  cout << "mymap['c'] is " << mymap['c'] << '\n';
  cout << "mymap['d'] is " << mymap['d'] << '\n';

  cout << "mymap now contains " << mymap.size() << " elements.\n";

  //////////////////

  map<char,string> mymap2 (mymap.begin(),mymap.end());

  map<char,string> mymap3 (mymap2);
  /////////////////


  map<string,int> mymap4 = {
                { "alpha", 0 },
                { "beta", 0 },
                { "gamma", 0 } };

  mymap4.at("alpha") = 10;
  mymap4.at("beta") = 20;
  mymap4.at("gamma") = 30;


for (auto& x: mymap4) 
{
    cout << x.first << ": " << x.second << '\n';
}
//////////////////
for (map<char,string>::iterator it=mymap.begin(); it!=mymap.end(); ++it) //cbegin and cend for immutable purposes // use crbegin and crend to print backwards
    cout << it->first << " => " << it->second << '\n';
  
//mymap.clear();


  mymap.emplace('a',"newA");//Inserts a new element in the map if its key is unique
  mymap.emplace('d',"newD");//The insertion only takes place if no other element in the container has a key equivalent
  mymap.emplace('e',"newE");

  for (char c='a'; c<'h'; c++)
  {
    cout << c;
    if (mymap.count(c)>0) // since all elements are unique it can return 1
      cout << " is an element of mymap.\n";
    else 
      cout << " is not an element of mymap.\n";
  }
  for (map<char,string>::iterator it=mymap.begin(); it!=mymap.end(); ++it) //cbegin and cend for immutable purposes // use crbegin and crend to print backwards
    cout << it->first << " => " << it->second << '\n';
///////////////
/*
map<char,int>::iterator it;
it = mymap.find('b'); //Searches the container for an element with a key equivalent to k and returns an iterator to it if found, otherwise it returns an iterator to map::end.
  if (it != mymap.end())
    mymap.erase(it);

  while (!mymap.empty())
  {
    std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
    mymap.erase(mymap.begin());
  }
*/


  map<char,int> mymap6;

  // first insert function version (single parameter):
  mymap6.insert ( std::pair<char,int>('a',100) );
  mymap6.insert ( std::pair<char,int>('z',200) );

  std::pair<map<char,int>::iterator,bool> ret;
  ret = mymap6.insert ( std::pair<char,int>('z',500) );
  if (ret.second==false) {
    cout << "element 'z' already existed";
    cout << " with a value of " << ret.first->second << '\n';
  }

/*
std::map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  mymap['b']=40;
  mymap['c']=60;
  mymap['d']=80;
  mymap['e']=100;

  itlow=mymap.lower_bound ('b');  // itlow points to b
  itup=mymap.upper_bound ('d');   // itup points to e (not d!)

  mymap.erase(itlow,itup);        // erases [itlow,itup)
*/
//output
  //a => 20
//e => 100


/////////


  std::map<char,int> foo,bar;

  foo['x']=100;
  foo['y']=200;

  bar['a']=11;
  bar['b']=22;
  bar['c']=33;

  foo.swap(bar);

  std::cout << "foo contains:\n";
  for (std::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  std::cout << "bar contains:\n";
  for (std::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

/////////
  std::multimap<char,int> first; //allows multiple keys

  first.insert(std::pair<char,int>('a',10));
  first.insert(std::pair<char,int>('b',15));
  first.insert(std::pair<char,int>('b',20));
  first.insert(std::pair<char,int>('c',25));




  return 0;
}