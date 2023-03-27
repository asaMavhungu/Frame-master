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
		else if ( strcmp (argv[i], "-p") == 0)
		{
			arr = 4;	
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
		case 4:
			arr = 1;
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

	if (width == 0 || height == 0)
	{
		std::cerr << "Error: Window dimensions should both be positive." << std::endl;
		return 1;
	}

	bool error = false;




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
		else if (operation == "none") 
		{
			reverse = false;
			invert = false;
		}

		if (points.size() == 4)
		{

			bool compose = true;

			if (x1 < 0 || y1< 0)
			{
				std::cerr << "Error: Starting point co-ordinates should both be positive." << std::endl;
				return 1;
			}

			if ( (x2 + width) > f.getWidth() || (y2+height) > f.getHeight())
			{
				std::cerr << "Error: End point co-ordinates are out of bound of PGM with dimensions " 
							<< f.getHeight() << " "
							<< f.getWidth() << " " 
							<< std::endl;
				return 1;
			}
			
			f.makeFrames(height, width, x1, y1, x2, y2, reverse, false, true);
			for (int i = 0; i < f.getFrameNum(); ++i)
			{
				f.writeFrames(filename, invert, i, width, height);
			}
			f.resetImageSequence();

		}
		else
		{
			x1 = points[0];
			y1 = points[1];

			for (int i = 2; i < points.size(); ++i)
			{
				x2 = points[i];
				y2 = points[i+1];

				bool compose = true;

				if (x1 < 0 || y1< 0)
				{
					std::cerr << "Error: Starting point co-ordinates should both be positive." << std::endl;
					compose = false;
					error = true;
				}

				if ( (x2 + width) > f.getWidth() || (y2+height) > f.getHeight())
				{
					std::cerr << "Error: End point co-ordinates are out of bound of PGM with dimensions " 
								<< f.getHeight() << " "
								<< f.getWidth() << " " 
								<< std::endl;
					compose = false;
					error = true;
				}

				if (compose)
					f.makeFrames(height, width, x1, y1, x2, y2, reverse,true, false);

				x1 = points[i];
				y1 = points[i+1];

				++i;
			}

			for (int i = 0; i < f.getFrameNum(); ++i)
			{
				f.writeFrames(filename, invert, i, width, height);
			}
			f.resetImageSequence();


		}

		++i;
	}
	
	if (error)
		return 1;
	return 0;
}