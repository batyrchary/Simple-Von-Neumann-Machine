#ifndef __frame_h__
#define __frame_h__

#include "pixel.h"
#include "rect.h"

// The frame class represents a frame (i.e. image) which is
// composed of width * height number of pixels "logically"
// laid out on a 2D grid. The term logically is used
// because even though the pixel data is stored in a single array,
// we assume that the first "width" pixels represent the
// first row of the frame, the pixel at position "width + 1"
// represents the first pixel in the second row of the
// frame and so on.
//
// TODO: Implement all the public interface functions
// in a file called "frame.cpp". Do not delete anything
// from this file but if necessary you can add variables
// and/or functions in the private part. You must ensure
// that all copies are deep copies.
class Frame
{
    public:
        // The default constructor creates an empty
        // frame (data = NULL) with zero dimensions
        Frame(); 

        // Creates a frame with the given dimensions.
        // data must be allocated but its contents
        // are irrelevant.
        Frame(int width, int height);

        // Creates a frame with the given dimensions.
        // Each pixel must be set to the given pixel.
        Frame(int width, int height, const Pixel& p);

        // The copy constructor
        Frame(const Frame& rhs);

        // The destructor
        ~Frame();

        // The assignment operator. Note that it must
        // return the reference of the current frame to
        // allow chained assignments.
        Frame& operator=(const Frame& rhs);

        // Returns a reference of the pixel at position (x, y).
        // Can be used to set the value of a pixel.
        Pixel& operator()(int x, int y);

        // Returns a constant reference of the pixel at 
        // position (x, y). Can be used to retrieve the
        // value of a pixel.
        const Pixel& operator()(int x, int y) const;

        // Returns a sub-frame of the current frame. The sub-frame
        // position and dimensions is specified in the rect parameter.
        Frame operator()(const Rect& rect) const;

        // Returns true if the current frame is equal to the
        // input frame (rhs). Conditions for equality are:
        // (1) their dimensions should match AND (2) they
        // must contain the same pixel data.
        bool operator==(const Frame& rhs) const;

        // The opposite of the equality function
        bool operator!=(const Frame& rhs) const;

        // Accessor functions for the width and height
        int getWidth() const;
        int getHeight() const;

        // Clears the entire frame to the given pixel's color values
        // (Each pixel is updated with the given pixel's colors)
        void clear(const Pixel& p);

        // Clears the given sub-region inside the frame.
        // (Pixels within the given rectangle are updated
        // with the given colors).
        void clear(const Rect& rect, const Pixel& p);

        // Crops the current frame to the given rectangle.
        void crop(const Rect& rect);

    private:
        Pixel* data;       // pixel data
        int width, height; // dimensions of the frame
};

#endif // __frame_h__
