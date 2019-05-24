#ifndef __pixel_h__
#define __pixel_h__

#include <ostream>

typedef unsigned char uchar;

// The pixel class represents a single pixel which is
// composed of "red", "green", and "blue" components.
// As these are defined to be unsigned char, valid
// component values are integers in range [0,255].
//
// TODO: Implement all the public interface functions
// in a file called "pixel.cpp". Do not delete anything
// from this file but if necessary you can add variables
// and/or functions in the private part.

class Pixel
{
    public:
        Pixel(uchar r = 0, uchar g = 0, uchar b = 0);

        // operator[]: can be used to update the color
        // components. index is one of {0, 1, 2} with
        // 0 representing red, 1 green, and 2 blue.
        uchar& operator[](int index);

        // Accessor version of the previous operator. Can
        // only be used to retrieve color values (cannot
        // update them as it returns a const reference).
        const uchar& operator[](int index) const;

        // Alternative accessors functions
        uchar getR() const;
        uchar getG() const;
        uchar getB() const;

        // Alternative mutator functions
        void setR(uchar r);
        void setG(uchar g);
        void setB(uchar b);

        // A friend function for printing the contents
        // of a pixel. If the pixel colors are 32, 45, and 102
        // the output should be look like: (32, 45, 102). Do
        // not print a new line after the closing parenthesis.
        friend std::ostream& operator<<(std::ostream& os, const Pixel& p);

    private:
        uchar red, green, blue;
};

#endif // __pixel_h__
