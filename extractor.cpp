#include <iostream>
#include "FrameSequence.h"
#include <string>
#include <cstring>
#include <cstdio>
#include <vector>

using namespace MVHASA001;

int main(int argc, char* argv[])
{
	FrameSequence f;
	std::string imageName = argv[1];


	f.readImage(imageName);

	
	std::vector<int> points;
	std::vector<int> sizes;
	std::vector<std::string> properties; 

	int arr = 0;
	for (int i = 2; i < argc; ++i){


		if ( strcmp( argv[i], "-t") == 0)
		{
			arr = 1;
			continue;
		}
		else if ( strcmp (argv[i], "-s") == 0)
		{
			arr = 2;
			continue;
		}
		else if ( strcmp (argv[i], "-w") == 0)
		{
			arr = 3;
			continue;
		}

		switch (arr)
		{
		case 1:
			points.push_back(std::stoi(argv[i]));
			break;
		case 2:
			sizes.push_back(std::stoi(argv[i]));
			break;
		case 3:
			properties.push_back(argv[i]);
			break;
		
		default:
			break;
		}
	}

	int x1 = points[0];
	int y1 = points[1];
	int x2 = points[2];
	int y2 = points[3];


	int width = sizes[0];
	int height = sizes[1];

	bool invert= false;
	bool reverse = false;

	for (int i = 0; i < int (properties.size()); ++i)
	{
		std::string operation = properties[i];
		std::string filename = properties[i+1];

		invert = false;
		reverse = false;

		if (operation == "invert") invert = true;
		else if (operation == "reverse") reverse = true;
		else if (operation == "revinvert") 
		{
			reverse = true;
			invert = true;
		}

		f.makeFrames(height, width, x1, y1, x2, y2, invert, reverse, true);
		for (int i = 0; i < f.getFrameNum(); ++i)
		{
			f.writeFrames(filename, i, width, height);
		}
		++i;
	}

/*
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
	*/
	//f.writeFrames("asa.pgm", 0, 100, 100);

	return 0;
}