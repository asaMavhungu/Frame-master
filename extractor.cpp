#include <iostream>
#include "FrameSequence.h"
#include <string>
#include <cstring>

using namespace MVHASA001;

int main(int argc, char* argv[])
{
	std::cout << "Hello\n";
	FrameSequence f;
	std::string imageName = argv[1];
	f.readImage(imageName);

	int x1, y1, x2, y2;
	int width, height;
	std::string operation, name;

	for (int i = 2; i < argc; ++i){

		if ( strcmp( argv[i], "-t") == 0)
		{
			x1 = int(argv[i+1]);
			i++;
			y1 = int(argv[i+2]);
			i++;
			x2 = int(argv[i+3]);
			i++;
			y2 = int(argv[i+4]);
			i++;
		}
		else if ( strcmp (argv[i], "-s") == 0)
		{
			width = int(argv[i+1]);
			i++;
			height = int(argv[i+2]);
			i++;
		}
		else if ( strcmp (argv[i], "-w") == 0)
		{
			operation = argv[i+1];
			i++;
			name = argv[i+2];
			i++;
		}
	}
	f.makeFrames(height, width, x1, y1, x2, y2);

	return 0;
}