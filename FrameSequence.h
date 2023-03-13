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
		std::string comment;

		std::vector<unsigned char **> imageSequence;

		public:

		FrameSequence(); // default constructor

		void readImage(std::string filename);
		void makeFrames(int windowHeight, int windowWidth, int x1, int y1, int x2, int y2, bool invert);
		void writeFrames(std::string outFile, int frameNo, int windowWidth, int windowHeight);

		int getHeight() { return height; }
		int getWidth() { return width; }
		std::string getComment() { return comment; }
		unsigned char * getSource() { return source; }
		std::vector<unsigned char **> getImageSequence() {return imageSequence;}
		int getFrameNum() {return imageSequence.size();}

	};

} // namespace MVHASA001


#endif