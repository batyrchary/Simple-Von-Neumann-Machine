#ifndef __video_h__
#define __video_h__

#include "frame.h"

// The video class represents a video which is basically
// a sequence of frames. 
//
// TODO: Implement all the public interface functions
// in a file called "video.cpp". Do not delete anything
// from this file but if necessary you can add variables
// and/or functions in the private part. You must ensure
// that all copies are deep copies.
class Video
{
    public:
        // The default constructor creates an empty video
        // (frames = NULL) and zero number of frames
        Video(); 

        // The copy constructor
        Video(const Video& rhs);

        // The destructor
        ~Video();

        // The assignment operator
        Video& operator=(const Video& rhs);

        // Inserts the given frame at the end of this video.
        // Can be used by chaining: (video << frame1 << frame2 << ...)
        Video& operator<<(const Frame& frame);

        // Extracts a frame from the given video.
        // Can be used by chaining: (video >> frame1 >> frame2 >> ...)
        // Note that each application of this operator must return
        // the "next" frame.
        Video& operator>>(Frame& frame);

        // Resets the stream such that the first operator>> after a
        // call to this function will extract the first frame again.
        void resetStream();

        // Retrieves the frame given by the frameIndex
        Frame getFrame(int frameIndex) const;

        // Removes the frame given by the frameIndex.
        // After removal there should be no "gaps" in the
        // video. That is, the following frames must be
        // shifted to fill this gap.
        void dropFrame(int frameIndex);

        // Trims the video such that it contains only the frames
        // between startIndex inclusive and endIndex exclusive.
        void trim(int startIndex, int endIndex);

    private:
        Frame* frames; // frame data
        int nFrames;   // the number of frames in this video
		int kaldi;
};

#endif // __video_h__
