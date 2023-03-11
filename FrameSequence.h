#ifndef _image_h
#define _image_h

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

		void readImage(std::string filename, int height, int width);
		int makeFrames(std::string filename, int windowHeight, int windowWidth, int numFrames);

	};

} // namespace MVHASA001


#endif