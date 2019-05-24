#include <iostream>
#include "frame.h"
using namespace std;

/*
 	   private:
        Pixel* data;       // pixel data
        int width, height; // dimensions of the frame
*/

Frame::Frame()
{
// The default constructor creates an empty frame (data = NULL) with zero dimensions
	data=NULL;
	width=0;
	height=0;
}



Frame::Frame(int w, int h)
{
// Creates a frame with the given dimensions.// data must be allocated but its contents are irrelevant.
 
 
	data=new Pixel[w*h];
	width=w;
	height=h;

}

///////////////////////////////////////////////////////////////////////////////////////////
Frame::Frame(int w, int h , const Pixel& p)
{
// Creates a frame with the given dimensions. // Each pixel must be set to the given pixel.

/*
 	   private:
        Pixel* data;       // pixel data
        int width, height; // dimensions of the frame
*/


	width=w;
	height=h;
	data=new Pixel[width*height];
	
	for (int i=0; i<height; i++)
	{
		for(int j=0; j<width;  j++)
		{
			data[i*width + j].setR(p.getR());
			data[i*width + j].setG(p.getG());
			data[i*width + j].setB(p.getB());
		}
	}



}
///////////////////////////////////////////////////////////////////////////////////////





Frame::Frame(const Frame& rhs)
{
  // The copy constructor

	if(&rhs != this)
	{
		//delete[] this->data;
		
	
		this->width=rhs.getWidth();
		this->height=rhs.getHeight();


		this->data=new Pixel[width*height];
	
		for (int i=0; i<height; i++)
		{
			for(int j=0; j<width;  j++)
			{
				this->data[i*width + j].setR((rhs.data[i*width+j]).getR());
				this->data[i*width + j].setG((rhs.data[i*width+j]).getG());
				this->data[i*width + j].setB((rhs.data[i*width+j]).getB());
			}
		}
		
	}
	else 
	{
		
	}



}


Frame::~Frame()
{
// The destructor


	delete[] data;
	
}



Frame& Frame::operator=(const Frame& rhs)
{
		//ilk once demolish yapman gerekyo
		this->width=rhs.getWidth();
		this->height=rhs.getHeight();
		delete[] this->data;

		this->data=new Pixel[width*height];
	
		for (int i=0; i<height; i++)
		{
			for(int j=0; j<width;  j++)
			{
				this->data[i*width + j].setR((rhs.data[i*width+j]).getR());
				this->data[i*width + j].setG((rhs.data[i*width+j]).getG());
				this->data[i*width + j].setB((rhs.data[i*width+j]).getB());
			}
		}
	return (*this);
}

Pixel& Frame::operator()(int x, int y)
{
	    // Returns a reference of the pixel at position (x, y).
        // Can be used to set the value of a pixel.


	return this->data[(this->getWidth())*y +x];

//p1 p2 p3
//p4 p5 p6
//p7 p8 p9
//when we are using the () operator with arguments x=0 and y=1,
//p4 is returned

}

const Pixel& Frame::operator()(int x, int y) const
{///////////////////////////////////////////////////////////////UNDONE
        // Returns a constant reference of the pixel at 
        // position (x, y). Can be used to retrieve the
        // value of a pixel.

	return this->data[(this->getWidth())*y +x];

//////////////////////////////////////////////////////////////
}

Frame Frame::operator()(const Rect& rect)const
{
        // Returns a sub-frame of the current frame. The sub-frame
        // position and dimensions is specified in the rect parameter.

	int y=rect.y;
	int x=rect.x;
	int wid=this->getWidth();
	int w=rect.w;
	int h=rect.h;


	Frame ret(w,h);
	for (int i=0; i<h; i++)
		{
		for(int j=0; j<w;  j++)
		{

				ret(j,i).setR(  (this->data[ y*wid + x + wid*i + j]).getR()  );
				ret(j,i).setG(  (this->data[ y*wid + x + wid*i + j]).getG()  );
				ret(j,i).setB(  (this->data[ y*wid + x + wid*i + j]).getB()  );
				
			}
		}
	return ret;

}
////////////////////////////////////////////////////////////////
bool Frame::operator==(const Frame& rhs)const
{
        // Returns true if the current frame is equal to the
        // input frame (rhs). Conditions for equality are:
        // (1) their dimensions should match AND (2) they
        // must contain the same pixel data.

		bool ret=true;
		
		if(((this->getWidth()) != rhs.getWidth()) || ((this->getHeight()) != rhs.getHeight()) )
		{
			ret=false;
		}
		else
		{
			int width=rhs.getWidth();
			int height=rhs.getHeight();
	
			for (int i=0; i<height; i++)
			{
				for(int j=0; j<width;  j++)
				{
				
					if(((rhs(j,i).getR()) != (this->data[i*width + j]).getR()) || ((rhs(j,i).getG()) != (this->data[i*width + j]).getG()) || ((rhs(j,i).getB()) != (this->data[i*width + j]).getB()) )
					{
						ret=false;
					}

				}
			}	
		}
return ret;

}


bool Frame::operator!=(const Frame& rhs)const
{

	return !((*this)==rhs);
}


int Frame::getWidth()const
{
	return width;
}

int Frame::getHeight()const
{
	return height;
}


void Frame::clear(const Pixel& p)
{
    // Clears the entire frame to the given pixel's color values
        // (Each pixel is updated with the given pixel's colors)

int height=this->getHeight();
int width=this->getWidth();

	for (int i=0; i<height; i++)
	{
		for(int j=0; j<width;  j++)
		{
			this->data[i*width + j].setR(p.getR());
			this->data[i*width + j].setG(p.getG());
			this->data[i*width + j].setB(p.getB());
		}
	}



}


void Frame::clear(const Rect& rect, const Pixel& p)
{
        // Clears the given sub-region inside the frame.
        // (Pixels within the given rectangle are updated
        // with the given colors).



	int y=rect.y;
	int x=rect.x;
	int wid=this->getWidth();
	int w=rect.w;
	int h=rect.h;



	for (int i=y; i<h+y; i++)
	{
		for(int j=x; j<w+x;  j++)
		{
			
			this->data[i*wid + j].setR(p.getR());
			this->data[i*wid + j].setG(p.getG());
			this->data[i*wid + j].setB(p.getB());
		}
	}



/*
	int y=rect.y;
	int x=rect.x;
	int wid=this->getWidth();
	int w=rect.w;
	int h=rect.h;

		for (int i=0; i<h; i++)
		{
			for(int j=0; j<w;  j++)
			{
				cout<<"icinde"<<" = "<<p.getR()<<endl;
				(this->data[ y*wid + x + wid*i + j]).setR(p.getR());
				(this->data[ y*wid + x + wid*i + j]).setG(p.getG());
				(this->data[ y*wid + x + wid*i + j]).setB(p.getB());
				
			}
		}*/

}


void Frame::crop(const Rect& rect)
{
	// Crops the current frame to the given rectangle

	(*this) = (*this)(rect);

}


/*
int main()
{

  Pixel p('9', '4', '5');
  	

//Frame(); 

Frame f1;
//cout<<f1.getWidth()<<endl;
//cout<<f1.getHeight()<<endl;

//      Frame(int width, int height);

Frame f2(3,3);
//cout<<f2.getWidth()<<endl;
//cout<<f2.getHeight()<<endl;

//cout<<(f2!=f1)<<endl;


//       Frame(int width, int height, const Pixel& p);
    
  	
Frame f3(4,2,p);

cout<<f3.getWidth()<<endl;
cout<<f3.getHeight()<<endl;


for(int i=0; i<2; i++)
{
	for(int j=0; j<4; j++)	
	{
		cout<<f3(j,i);
	}
	cout<<endl;
}


//Frame(const Frame& rhs);
Frame f4(f3);
cout<<f4.getWidth()<<endl;
cout<<f4.getHeight()<<endl;

for(int j=0; j<4; j++)	
{
	for(int i=0; i<2; i++)
	{
		cout<<f4(j,i);
	}
	cout<<endl;
}



f1=f3;
//Frame& operator=(const Frame& rhs);
cout<<f1.getWidth()<<endl;
cout<<f1.getHeight()<<endl;

for(int j=0; j<4; j++)	
{
	for(int i=0; i<2; i++)
	{
		cout<<f1(j,i);
	}
	cout<<endl;
}


//Pixel& operator()(int x, int y);
//cout<<f3(3,1)<<endl;

//Frame operator()(const Rect& rect) const;

Rect r(1,0,1,2);


Frame f6;
f6=f3(r);

for(int i=0; i<2; i++)
{
	for(int j=0; j<1; j++)	
	{
		cout<<f6(j,i);
	}
	cout<<endl;
}

//void clear(const Pixel& p);
Pixel p2('1','2','3');
f1.clear(p2);

for(int i=0; i<2; i++)
{
	for(int j=0; j<4; j++)	
	{
		cout<<f1(j,i);
	}
	cout<<endl;
}
//void clear(const Rect& rect, const Pixel& p);

cout<<"now"<<endl;
Frame f7;
(f3.clear(r,p2));

for(int i=0; i<2; i++)
{
	for(int j=0; j<1; j++)	
	{
		cout<<f3(j,i);
	}
	cout<<endl;
}


f3.crop(r);
for(int i=0; i<2; i++)
{
	for(int j=0; j<1; j++)	
	{
		cout<<f3(j,i);
	}
	cout<<endl;
}











  	  

return 0;
}

*/
