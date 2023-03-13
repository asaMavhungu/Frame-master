#include "FrameSequence.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>



MVHASA001::FrameSequence::FrameSequence(void) : width(0), height(0), id(nullptr), source(nullptr)
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

	this->comment = comment;
	this->source = buffer;
	this->height = height;
	this->width = width;
	std::cout << "here";
}

void MVHASA001::FrameSequence::makeFrames(int windowHeight, int windowWidth, int x1, int y1, int x2, int y2)
{
	// Account for division by zero error during gradient calculation
	if ( x1 != x2)
	{
		std::cout << "here**************************4\n";
		// Using y = mx + c to get line for tragectory
		// The (x, y) coord will be the starting point of our current frame
		float m = (y2 - y1)/(x2-x1);

		// y intercept of tragectory line
		int c = y1 - m*x1;

		// Coords for the corresponding y for current x-cord iteration
		int y = 0;
		float x = 0;
		std::cout << "here**************************5\n";
		if (x1 < x2)
		{
			for (int x = x1; x < x2; x++)
			{
			
				y = m*x + c;
				// floor the answer to get an integer
				y = std::floor(y);

				unsigned char ** frame;
				frame = new unsigned char * [windowHeight];
				for(int row = y; row < y+windowHeight; ++row)
				{
					int i = row - y;
					frame[i] = new unsigned char[windowWidth];
					for(int col = x; col < x+windowWidth; ++col)
					{
						int j = col - x;
						unsigned char pixel = this->source[row * this->width + col];
						frame[i][j] = pixel;
					}
				}
				this->imageSequence.push_back(frame);
			}
		}
		else if (x1 > x2)
		{
			for (int x = x1; x > x2; x--)
			{
				y = m*x + c;
				// floor the answer to get an integer
				y = std::floor(y);

				unsigned char ** frame;
				frame = new unsigned char * [windowHeight];
				for(int row = y; row < y+windowHeight; ++row)
				{
					int i = row - y;
					frame[i] = new unsigned char[windowWidth];
					for(int col = x; col < x+windowWidth; ++col)
					{
						int j = col - x;
						unsigned char pixel = this->source[row * this->width + col];
						frame[i][j] = pixel;
					}
				}
				this->imageSequence.push_back(frame);
			}

		}
	}
	else
	{
		for (int y = y1; y < y2; y++)
		{
			unsigned char ** frame;
			frame = new unsigned char * [windowHeight];
			for(int row = y; row < y+windowHeight; ++row)
			{
				int i = row - y;
				frame[i] = new unsigned char[windowWidth];
				for(int col = x1; col < x1+windowWidth; ++col)
				{
					int j = col - x1;
					unsigned char pixel = this->source[row * this->width + col];
					frame[i][j] = pixel;
				}
			}
			this->imageSequence.push_back(frame);
		}
	}
}

void MVHASA001::FrameSequence::writeFrames(std::string outFile, int frameNo, int windowWidth, int windowHeight)
{

	char filename[256];
    sprintf(filename, outFile.c_str(), frameNo);
	std::cout << filename << std::endl;
	std::ofstream file(filename, std::ios::binary);
	file << "P5" << std::endl;
    file << windowWidth << " " << windowHeight << std::endl;
    file << "255" << std::endl;

	unsigned char** data = this->imageSequence[frameNo];
	for (int y = 0; y < windowHeight; y++) 
	{
		file.write(reinterpret_cast<const char*>(data[y]), windowWidth);
	}

}