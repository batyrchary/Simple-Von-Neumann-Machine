#include <iostream>
#include "pixel.h"
using namespace std;


Pixel::Pixel(uchar r, uchar g, uchar b)
{
	
	red= r;
	green=g;
	blue=b;
}



/////////////////////////////////////////////////////////////
        // operator[]: can be used to update the color
        // components. index is one of {0, 1, 2} with
        // 0 representing red, 1 green, and 2 blue.
uchar& Pixel::operator[](int index)
{

//cout<<"zaaa"<<endl;
	if(index==0)//red
	{
		return (this->red);
	}
	else if(index==1)//green
	{
		return (this->green);
	}
	else//blue
	{
		return (this->blue);
	}


}

/////////////////////////////////////////////////////////////

        // Accessor version of the previous operator. Can
        // only be used to retrieve color values (cannot
        // update them as it returns a const reference).
const uchar& Pixel::operator[](int index) const
{
/////////////////////////////////////////////////////////////////UNDONE
//cout<<"ba"<<endl;
	if(index==0)//red
	{
		return (this->red);
	}
	else if(index==1)//green
	{
		return (this->green);
	}
	else//blue
	{
		return (this->blue);
	}

///////////////////////////////////////////////////////////////////////
	
}
/////////////////////////////////////////////////////////////



uchar Pixel::getR()const
{
	return red;
}

uchar Pixel::getG()const
{
	return green;	
}

uchar Pixel::getB()const
{
	return blue;
}

void Pixel::setR(uchar r)
{
	red=r;
}

void Pixel::setG(uchar r)
{
	green=r;
}

void Pixel::setB(uchar r)
{
	blue=r;	
}
/////////////////////////////////////////////////////////////
        // A friend function for printing the contents
        // of a pixel. If the pixel colors are 32, 45, and 102
        // the output should be look like: (32, 45, 102). Do
        // not print a new line after the closing parenthesis.

ostream& operator<<(ostream& os, const Pixel& p)
{
	os << "(" <<(int)p.red << ", " << (int)p.green << ", " << (int)p.blue <<")"; 
	return os;
}
/////////////////////////////////////////////////////////////


/*
int main()
{

Pixel p(2,3,4);
cout<<p<<endl;

p[0]=10;
cout<<p<<endl;
cout<<(int)p[1]<<endl;




p.setR('5');
p.setG('6');
p.setB('7');

cout<<">>>>>>UPDATE<<<<<<<<<<<"<<endl;
cout<<"red = "<<p.getR()<<endl;
cout<<"green = "<<p.getG()<<endl;
cout<<"blue = "<<p.getB()<<endl;

cout<<p<<endl;


cout<<p[0]<<endl;
cout<<p[1]<<endl;
cout<<p[2]<<endl;

p[0]='8';
cout<<p[0]<<endl;

return 0;
}*/
