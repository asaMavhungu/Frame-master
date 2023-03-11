#ifndef _image_h
#define _image_h

#include <vector>
#include <fstream>

namespace MVHASA001
{
	

	class FrameSequence
	{

		int frames;

		std::vector<unsigned char **> imageSequence;

		public:

		FrameSequence(); // default constructor
		FrameSequence(const int height, const int width, std::fstream& imag);

	};

} // namespace MVHASA001


#endif