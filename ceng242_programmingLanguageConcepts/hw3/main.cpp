#include <iostream>
#include "video.h"

using namespace std;

int main()
{
    Pixel p(3, 4, 5);

    cout << p << endl;

   for (int i = 0; i < 3; ++i)
    {
        p[i] = i + 100;
    }
    cout << p << endl;


    Frame emptyFrame;

    Frame frame1(600, 400);
    Frame frame2(600, 400, p);
    Frame frame3 = frame2;

    frame1 = frame3;


  
  Frame frame4(1024, 768);
    Frame frame5(320, 647);

    frame4 = frame3 = frame2;
    (frame5 = frame3) = frame2;

    cout << frame2(250, 150) << endl;
    cout << frame5(250, 150) << endl;

   frame5(250, 150) = Pixel(255, 254, 253);

    cout << frame5(250, 149) << endl;
    cout << frame5(250, 150) << endl;
    cout << frame5(250, 151) << endl;

    Frame subFrame = frame5(Rect(245, 145, 10, 20));
   cout << "width = " << subFrame.getWidth() << endl;
    cout << "height = " << subFrame.getHeight() << endl;
   cout << subFrame(5, 4) << endl;
    cout << subFrame(5, 5) << endl;
    cout << subFrame(5, 6) << endl;

    cout << "Clearing the subFrame" << endl;
    subFrame.clear(Pixel(3, 2, 1));
    cout << subFrame(5, 4) << endl;
    cout << subFrame(5, 5) << endl;
    cout << subFrame(5, 6) << endl;


    cout << "Partially clearing the subFrame" << endl;
    subFrame.clear(Rect(1, 1, 2, 2), Pixel(0, 0, 0));
   for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x)
        {
            cout << "(" << x << ", " << y << ") = " << subFrame(x, y) << endl;
        }
    }

    cout << "Cropping the subFrame" << endl;
    subFrame.crop(Rect(1, 1, 4, 3));
    for (int y = 0; y < 3; ++y)
    {
        for (int x = 0; x < 4; ++x)
        {
            cout << "(" << x << ", " << y << ") = " << subFrame(x, y) << endl;
        }
    }
//////////////
   Video v1;
    cout << "Inserting some frames to the video" << endl;
    for (int i = 0; i < 10; ++i)
    {
        v1 << frame5 << frame3;
    }

   Frame oddFrame, evenFrame;
    cout << "Checking if the inserted frames are correct" << endl;
    bool result = true;
    for (int i = 0; i < 10; ++i)
    {
        v1 >> oddFrame >> evenFrame;

        if (oddFrame != frame5 || evenFrame != frame3)
        {
            result = false;
            break;
        }
    }

    if (result)
    {
        cout << "Extracted frames match the inserted frames, so all good" << endl;
    }
    else
    {
        cout << "Failed to match the extracted frames with the inserted frames" << endl;
    }

    Video v2 = v1;

    // Note that we use index 10 to get the eleventh frame
    // as the first frame has index 0.
    Frame eleventhFrame = v2.getFrame(10);

    if (eleventhFrame == frame5)
    {
        cout << "The selected frame matched on a copy constructed video" << endl;
    }
    else
    {
        cout << "Failed to match the selected frame on a copy constructed video" << endl;
    }
/////
    cout << "Dropping frame with index 10 (eleventh frame)" << endl;
    v2.dropFrame(10);

    // The new eleventh frame is the twelfth frame of the original video
    eleventhFrame = v2.getFrame(10);

    if (eleventhFrame == frame3)
    {
        cout << "The selected frame matched on a copy constructed video after dropping a frame" << endl;
    }
    else
    {
        cout << "Failed to match the selected frame on a copy constructed video after dropping a frame" << endl;
    }
///
    cout << "Trimming the video such that the result contains only frames 10 and 11" << endl;
    v2.trim(10, 12);

    if (v2.getFrame(0) == frame3 &&
        v2.getFrame(1) == frame5)
    {
        cout << "The selected frames matched on a copy constructed video after dropping a frame and trimming it" << endl;
    }
    else
    {
        cout << "The selected frames matched on a copy constructed video after dropping a frame and trimming it" << endl;
    }

    return 0;
}
