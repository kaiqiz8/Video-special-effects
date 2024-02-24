/*
	Kaiqi Zhang
	Spring 2024
	CS 5330 Project 1

	Displaying image that specified by users
*/
#include <cstdio>
#include <cstring>
#include <opencv2/opencv.hpp> 

int main(int argc, char *argv[]) {
	cv::Mat src;
	char filename[256];

	//check if enough command line arguments
	if(argc < 2) {
		printf("usage: %s < image filename>\n", argv[0]);
		exit(-1);
	}
	strcpy( filename, argv[1]);

	//read the image 
	src = cv::imread( filename ); 

	//test of the image read was successful
	if (src.data == NULL) { // no image data read from file
		printf("error: unable to read image %s\n", filename);
		exit(-1);
	}

	// successfully read an image file
	printf("Image size: %d rows, %d columns\n", (int)src.size().height, (int)src.size().width);
	//or src.rows, src.cols
	printf("Number of channel: %d\n", (int)src.channels());
	printf("Bytes per channel: %d\n", (int)src.elemSize() / src.channels());
	

	cv::namedWindow(filename, 1);
	cv::imshow(filename, src);

	cv::waitKey(0);
	cv::destroyWindow( filename );
	printf("Terminating\n");

	return(0);

}

