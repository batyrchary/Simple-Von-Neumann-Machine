#include <iostream>
#include "video.h"
using namespace std;



//        Frame* frames; // frame data
  //      int nFrames;   // the number of frames in this video



Video::Video()
{
        // The default constructor creates an empty video
        // (frames = NULL) and zero number of frames
	frames=NULL;
	nFrames=0;
	kaldi=0;
}


Video::Video(const Video& rhs)
{
        // The copy constructor

	if(&rhs != this)
	{
		//delete[] this->data;

		nFrames=rhs.nFrames;	
		kaldi=rhs.kaldi;
		
		frames = new Frame[nFrames];
		
		for (int i=0; i<nFrames; i++)
		{
			frames[i]=rhs.frames[i];
		}
		
	}
	else 
	{
		
	}



}

Video::~Video()
{
	delete[] frames;
}



Video& Video::operator=(const Video& rhs)
{	
        // The assignment operator
		nFrames=rhs.nFrames;
		kaldi=rhs.kaldi;	
		delete[] this->frames;	
		frames = new Frame[nFrames];
		
		for (int i=0; i<nFrames; i++)
		{
			frames[i]=rhs.frames[i];
		}

return (*this);

}


Video& Video::operator<<(const Frame& frame)
{
        // Inserts the given frame at the end of this video.
        // Can be used by chaining: (video << frame1 << frame2 << ...)
	nFrames=nFrames+1;
	
	Frame* frame_yedek;
	frame_yedek = new Frame[nFrames];
	for (int i=0; i<nFrames-1; i++)
	{
		frame_yedek[i]=frames[i];
	}
	delete[] this->frames;	
	frame_yedek[nFrames-1]=frame;
	frames=frame_yedek;

	return (*this);
}



Video& Video::operator>>(Frame& frame)
{
        // Extracts a frame from the given video.
        // Can be used by chaining: (video >> frame1 >> frame2 >> ...)
        // Note that each application of this operator must return
        // the "next" frame.

		frame=frames[kaldi];
		kaldi++;


}

void Video::resetStream()
{

        // Resets the stream such that the first operator>> after a
        // call to this function will extract the first frame again.
	kaldi=0;
}

Frame Video::getFrame(int frameIndex)const
{
        // Retrieves the frame given by the frameIndex
	
	return frames[frameIndex];


}

void Video::dropFrame(int frameIndex)
{

        // Removes the frame given by the frameIndex.
        // After removal there should be no "gaps" in the
        // video. That is, the following frames must be
        // shifted to fill this gap.

	
	Frame *frame_yedek;
	frame_yedek = new Frame[nFrames-1];
	for (int i=0; i<frameIndex; i++)
	{
			frame_yedek[i]=frames[i];
	}
	for (int i=frameIndex+1; i<nFrames; i++)
	{
			frame_yedek[i-1]=frames[i];
	}
	delete[] this->frames;
	nFrames=nFrames-1;
	frames=frame_yedek;

}

void Video::trim(int startIndex, int endIndex)
{
	        // Trims the video such that it contains only the frames
        // between startIndex inclusive and endIndex exclusive.

	Frame *frame_yedek;
	frame_yedek = new Frame[endIndex-startIndex];
	for (int i=startIndex; i<endIndex; i++)
	{
			frame_yedek[i-startIndex]=frames[i];
	}

	delete[] this->frames;
	nFrames=endIndex-startIndex;
	frames=frame_yedek;

}


/*
int main()
{

	return 0;
}
*/

