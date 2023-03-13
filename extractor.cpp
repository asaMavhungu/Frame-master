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

	std::string x1;
	std::string y1;
	std::string x2;
	std::string y2;
	std::string width;
	std::string height;
	std::string operation;
	std::string name;
	
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

	bool invert = false;
	if (operation == "invert")
		invert = true;


	for (int i : points)
	{
		std::cout << i << " ";
	}
	std::cout << "points" << std::endl;

	for (int i : sizes)
	{
		std::cout << i << " ";
	}
	std::cout << "sizes" << std::endl;

	for (std::string i : properties)
	{
		std::cout << i << " ";
	}
	std::cout << "properties"<< std::endl;

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