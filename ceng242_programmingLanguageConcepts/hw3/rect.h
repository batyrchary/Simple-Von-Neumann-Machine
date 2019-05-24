#ifndef __rect_h__
#define __rect_h__

// The rectangle structure will be used to access
// regions of interest inside frames. You should
// not modify this class - it is already implemented
// for you.
struct Rect
{
    int x; // x coordinate of the top-left corner
    int y; // y coordinate of the top-left corner
    int w; // width
    int h; // height

    Rect(int inX, int inY, int inW, int inH) :
        x(inX), y(inY), w(inW), h(inH) { }
};

#endif // __rect_h__
