# C++ Frame-master
## CSC3022 2023 Assignment 2

This project is a video render implemented in C++ which can do the following:

* Read in a PGM image file
* Extract frames from the image file in a tragectory
* Write out the seperate frames as PGM files

## Operation
This program is designed to process large images and extract specific frames based on user-defined parameters. The command line options for the program are as follows:

`extractor <inputPGMfile> [options]`

- ``<inputPGMfile>``: The large image file to be processed.

### Options
``-t <int> <int> <int> <int>``: Specifies the frame trajectory by providing the beginning and end origin pixel coordinates.

- Example: -t 10 20 100 150 (defines trajectory from pixel (10,20) to (100,150))


``-s <int> <int>``: Specifies the size of the small frame in pixels.

- Example: -s 50 50 (sets the size of the small frame to 50x50 pixels)

``-w <string> <string>``: Writes frames with the specified operation and name.

- Example: -w resize small_frame (writes frames with the operation 'resize' and the name 'small_frame')

### Operations for -w flag
- **none**: No modification of data.
- **invert**: Each pixel value 'v' becomes '255 - v'.
- **reverse**: Reverse output (write frames from last to first).
- **revinvert**: Reverse and invert output.


### Example
```bash
extractor input_image.pgm -t 10 20 100 150 -s 50 50 -w invert small_frame
```


## Files
Files used in the implementation

## 1. extractor.cpp
This contains our main function. It handles input/output from the user
## 2. FrameSequence.h
This file is the header file used the class and class memebers declarations

## 3. FrameSequence.cpp
This file initializes the functions declared in tags.h
### PGM file reading

The class method ```MVHASA001::FrameSequence::readImage(std::string filename)``` takes in a PGM file directory as input and converts the pixels of the file int an array holding ```unsigned char```

The contents of the header are also saved in their  own class members. ie. height and width are saved in ```FrameSequence->height``` and ```FrameSequence->width```.

The comments are also saved in their own class variables.

## Frame extraction
The method ```MVHASA001::FrameSequence::makeFrames()``` is used to extract frames from the much larger original image.
```int windowHeight, int windowWidth``` are used to determine the dimensions of the extracted frame.
```int x1, int y1, int x2, int y2``` are used to determine the starting point and ending point of extraction on the much larger image. In some cases a simple line graph eqation is used to calculate the co-ordinates of the next starting point. When this is not applicable (i.e. the X stays constant), the Y component is either incremented ot decrementeed to get the next point of extraction.
```bool reverse``` is used to determine if the extracted frames will be inserted onto the ```imageSequence``` vector from the back or from the front (i.e is the next rame inserted at the back or the front of the vecotor).
```bool accerleration``` is used to determine if frame skiping will be applied to give the illusion of acceleration.
```bool reset``` is used to determine if the current frame sequence needs to be cleared before the next frame sequence is ran. Useful for doing polyline tragectory

## Frame writing
The method ```MVHASA001::FrameSequence::writeFrames()``` is used to write out a certain frame onto a pgm file.
```outFile``` is the base name of the output file.
```invert``` is used to determine if the pixels of the extracted frames will be inverted or not.
```frameNo``` is the index of the frame in the ```imageSequence``` vector. This is also used as part of the output file name.
```int windowWidth, int windowHeight``` is used to determine the dimensions of the expected frame.