/*
	Kaiqi Zhang
	Spring 2024
	CS 5330 Project 1

    Implement a filter that removes red color, a file name is required to run the program
*/

#include <cstdio>
#include <cstring>
#include <opencv2/opencv.hpp> 

int removeRedColor( cv::Mat &src, cv::Mat &dst ) {
    src.copyTo(dst);
    for (int i = 0; i < src.rows; i++){
        for (int j = 0; j < src.cols; j++){
            if (src.at<cv::Vec3b>(i, j)[2] >= 150 && src.at<cv::Vec3b>(i, j)[1] <= 100 && src.at<cv::Vec3b>(i, j)[0] <= 100) {
                        dst.at<cv::Vec3b>(i, j)[0] = 0;
                        dst.at<cv::Vec3b>(i, j)[1] = 0;
                        dst.at<cv::Vec3b>(i, j)[2] = 0;
            }
        }
    }
    return(0);
}

int main(int argc, char *argv[]) {
    cv::Mat src;
    char filename[256];

    if(argc < 2) {
		printf("usage: %s < image filename>\n", argv[0]);
		exit(-1);
	}
    strcpy(filename, argv[1]);
    src = cv::imread( filename ); 
    removeRedColor(src, src);
    
    
    cv::namedWindow(filename, 1);
    cv::imshow("processed.jpg", src);
    cv::imwrite("processed.jpg", src);

    cv::waitKey(0);
	cv::destroyWindow( filename );
	printf("Terminating\n");
    return(0);
}