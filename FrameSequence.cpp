#include "FrameSequence.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>



MVHASA001::FrameSequence::FrameSequence() : width(0), height(0), id(nullptr), source(nullptr)
{}

void MVHASA001::FrameSequence::readImage(std::string filename)
{
	std::ifstream in(filename, std::ios::binary);

	std::string format, commentBuffer, comment, line;
	int width = 0, height = 0, max_value = 0;

	// Read the first line to get the format
	std::getline(in, format);

	// Read any comment lines (starting with #)
	while (std::getline(in, commentBuffer)) 
	{
		if (commentBuffer[0] != '#') 
		{
			break;
		}
		comment = comment + commentBuffer;
	}

	// The last line that doesn't have '#' will be saved to comment
	std::istringstream iss(commentBuffer);
	iss >> width >> height;


	std::getline(in, line);
	std::istringstream iss2(line);
	iss2 >> max_value;

	// Remove whitespace
	in >> std::ws;

	// Allocate memory pixels
	unsigned char* buffer = new unsigned char[width * height];

	// Read the pixels into the buffer
	// Convert fron unsigned char to char to avoid type mismatch
	// because read() expects a char* not 'unsigned char*'
	in.read(reinterpret_cast<char*>(buffer), width * height);

	this->source = buffer;
	this->height = height;
	this->width = width;
}

void MVHASA001::FrameSequence::makeFrames(int windowHeight, int windowWidth, int x1, int y1, int x2, int y2)
{
	// Using y = mx + c to get line for tragectory
	float m = (y2 - y1)/(x2-x1);
	int c = y1;
	int y = 0;

	for (int x = x1; x < x2; x++)
	{
		y = m*x + c;
		// floor the answer to get an integer
		y = std::floor(y);

		unsigned char ** frame;
		frame = new unsigned char * [windowHeight];
		for(int i = y; i < y+windowHeight; i++)
		{

			for(int j = x; j < x+windowWidth; j++)
			{
				unsigned char pixel = this->source[i * this->width + j];
				frame[i][j] = pixel;
			}
		}

		this->imageSequence.push_back(frame);
	}

}