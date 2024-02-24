/*
	Kaiqi Zhang
	Spring 2024
	CS 5330 Project 1

    Implement a minimum filter that replaces each pixel's value with the minimum value of its neighboring pixels within a defined neighborhood. A image file name is required to run the program
*/

#include <cstdio>
#include <cstring>
#include <opencv2/opencv.hpp> 

int main(int argc, char *argv[]) {
    cv::Mat src;
    char filename[256];

    if(argc < 2) {
		printf("usage: %s < image filename>\n", argv[0]);
		exit(-1);
	}

    strcpy(filename, argv[1]);
    src = cv::imread( filename ); 

    if (src.rows < 5 ||  src.cols < 5) {
        printf("Image is too small!");
        return -1;
    }
    cv::Mat result = src.clone();

    // Iterate through the image with a 5x5 sliding window
    for (int i = 2; i < src.rows - 2; ++i) {
        for (int j = 2; j < src.cols - 2; ++j) {
            // Extract a 5x5 matrix
            cv::Mat roi = src(cv::Range(i - 2, i + 3), cv::Range(j - 2, j + 3));
            std::vector<cv::Mat> channels;
            cv::split(roi, channels);

            // Find the minimum value in the matrix for each channel
            for (int k = 0; k < channels.size(); ++k) {
                double minVal, maxVal;
                cv::Point minLoc, maxLoc;
                cv::minMaxLoc(channels[k], &minVal, &maxVal, &minLoc, &maxLoc);
                // Set the center pixel with the minimum value for each channel
                result.at<cv::Vec3b>(i, j)[k] = minVal;
            }
            
        }
    }
    cv::imwrite("modified_with_min_filter.jpg", result);
    cv::imshow("Modified Image", result);
    cv::waitKey(0);


    return(0);
}