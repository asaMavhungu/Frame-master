#include <iostream>
#include "FrameSequence.h"
#include <string>
#include <cstring>
#include <cstdio>

using namespace MVHASA001;

int main(int argc, char* argv[])
{
	FrameSequence f;
	std::string imageName = argv[1];


	f.readImage(imageName);

	std::string x1;
	std::string y1;
	std::string x2;
	std::string y2;
	std::string width;
	std::string height;
	std::string operation;
	std::string name;
	

	for (int i = 2; i < argc; ++i){

		if ( strcmp( argv[i], "-t") == 0)
		{
			x1 = argv[i+1];
			y1 = argv[i+2];
			x2 = argv[i+3];
			y2 = argv[i+4];
			i++;i++;i++;i++;
		}
		else if ( strcmp (argv[i], "-s") == 0)
		{
			width = argv[i+1];
			height = argv[i+2];
			i++;i++;
		}
		else if ( strcmp (argv[i], "-w") == 0)
		{
			operation = argv[i+1];
			name = argv[i+2];
			i++;i++;
		}
	}

	bool invert = false;
	if (operation == "invert")
		invert = true;

	int heightP, widthP, x1P, y1P, x2P, y2P;
	heightP = std::stoi(height);
	widthP = std::stoi(width);
	x1P = std::stoi(x1);
	y1P = std::stoi(y1);
	x2P = std::stoi(x2);
	y2P = std::stoi(y2);
	f.makeFrames(heightP, widthP, x1P, y1P, x2P, y2P, invert);

	
	for (int i = 0; i < f.getFrameNum(); ++i)
	{
		std::string asa = "output_%d.pgm";
		f.writeFrames(asa, i, widthP, heightP);
	}
	
	//f.writeFrames("asa.pgm", 0, 100, 100);

	return 0;
}