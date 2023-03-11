#ifndef _FrameSequence_h
#define _FrameSequence_h

#include <vector>
#include <string>
#include <fstream>

namespace MVHASA001
{
	

	class FrameSequence
	{

		int width, height;
		char *id;
		unsigned char * source;

		std::vector<unsigned char **> imageSequence;

		public:

		FrameSequence(); // default constructor

		void readImage(std::string filename);
		int makeFrames(std::string filename, int windowHeight, int windowWidth, int numFrames);

	};

} // namespace MVHASA001


#endif