/*
	Kaiqi Zhang
	Spring 2024
	CS 5330 Project 1

    Open a video channel, create a window, display the video in stream and apply filters
*/

#include <cstdio>
#include <cstring>
#include <opencv2/opencv.hpp> 
#include "filter.h"
#include "faceDetect/faceDetect.h"

int main(int argc, char *argv[]) {
        cv::VideoCapture *capdev;

        // open the video device
        capdev = new cv::VideoCapture(1);
        if( !capdev->isOpened() ) {
                printf("Unable to open video device\n");
                return(-1);
        }

        // get some properties of the image
        cv::Size refS( (int) capdev->get(cv::CAP_PROP_FRAME_WIDTH ),
                        (int) capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
        capdev->set(cv::CAP_PROP_CONVERT_RGB, true);
        printf("Expected size: %d %d\n", refS.width, refS.height);

        cv::namedWindow("Video", 1); // identifies a window
        cv::Mat frame;

        // Set up face detect
        cv::Mat grey;
        std::vector<cv::Rect> faces;
        cv::Rect last(0, 0, 0, 0);
    
        bool convertToGray = false;
        bool keyHPressed = false;
        bool isSepiaTone = false;
        bool isBlurry = false;
        bool isSobelX = false;
        bool isSobelY = false;
        bool isGradient = false;
        bool isBlurQuant = false;
        bool isDetectFaces = false;
        bool isMosaicFace = false;
        bool isHaloFace = false;

        cv::Mat sobelX, sobelY;
    

        for(;;) {
                *capdev >> frame; // get a new frame from the camera, treat as a stream
                if( frame.empty() ) {
                    printf("frame is empty\n");
                    break;
                } 

                if (convertToGray) {
                    if (keyHPressed){
                        //CONVERT METHOD HERE
                        convertToGrayScaleAt(frame, frame);
                    } else {
                        cv::cvtColor(frame, frame, cv::COLOR_RGBA2GRAY);
                    }   
                }            

                if (isSepiaTone){
                    sepiaToneFilter(frame, frame);
                }

                if(isBlurry) {
                    blur5x5_2(frame, frame);
                }

                if (isSobelX) {
                    sobelX3x3(frame, sobelX);
                    cv::convertScaleAbs(sobelX, frame);
                }

                if (isSobelY) {
                    sobelY3x3(frame, sobelY);
                    cv::convertScaleAbs(sobelY, frame);
                }

                if (isGradient) {
                    sobelX3x3(frame, sobelX);
                    sobelY3x3(frame, sobelY);
                    cv::Mat gradient;
                    magnitude(sobelX, sobelY, gradient);
                    cv::convertScaleAbs(gradient, frame);
                }

                if (isBlurQuant) {
                    blurQuantize(frame, frame, 10);
                }

                if (isDetectFaces) {
                    cv::cvtColor( frame, grey, cv::COLOR_BGR2GRAY, 0);
                    detectFaces(grey, faces);
                    drawBoxes(frame, faces);
                    // add a little smoothing by averaging the last two detections
                    if( faces.size() > 0 ) {
                    last.x = (faces[0].x + last.x)/2;
                    last.y = (faces[0].y + last.y)/2;
                    last.width = (faces[0].width + last.width)/2;
                    last.height = (faces[0].height + last.height)/2;
                    }
                }

                if (isMosaicFace) {
                    cv::cvtColor( frame, grey, cv::COLOR_BGR2GRAY, 0);
                    detectFaces(grey, faces);
                    drawBoxes(frame, faces);
                    
                    // add a little smoothing by averaging the last two detections
                    if( faces.size() > 0 ) {
                    last.x = (faces[0].x + last.x)/2;
                    last.y = (faces[0].y + last.y)/2;
                    last.width = (faces[0].width + last.width)/2;
                    last.height = (faces[0].height + last.height)/2;
                    }
                    
                    mosaicFilter(frame, faces, 30);
                }

                if (isHaloFace) {
                    cv::cvtColor( frame, grey, cv::COLOR_BGR2GRAY, 0);
                    detectFaces(grey, faces);
                    haloFilter(frame, faces);

                }



                cv::imshow("Video", frame);
            
                // see if there is a waiting keystroke
                char key = cv::waitKey(10);
                if( key == 'q') {
                    break;
                } else if (key == 's') {
                    std::string currentcolor = convertToGray ? "grayscale" : "color";
                    std::string filename = "saved_image_" + currentcolor + "_.jpg";
                    cv::imwrite(filename, frame);
                    printf("Image saved as %s\n", filename.c_str());
                } else if (key == 'g') {
                    convertToGray = true;
                    printf("Switched to %s mode \n", convertToGray ? "grayscale" : "color");
                    
                } else if (key == 'h') {
                    keyHPressed = true;
                    printf("Using alternative grayscale method to convert color to Gray\n");
                } else if (key == 'a') {
                    isSepiaTone = true;
                    printf("Applying Sepia tone filter\n");
                } else if (key == 'b') {
                    isBlurry = true;
                    printf("Applying Blur 5*5 filter \n");
                } else if (key == 'x') {
                    isSobelX = true;
                    printf("Applying Sobel X filter\n");
                } else if (key == 'y') {
                    isSobelY = true;
                    printf("Applying Sobel Y filter\n");
                } else if (key == 'm') {
                    isGradient = true;
                    printf("Applying gradient magnitude filter\n");
                } else if (key == 'l') {
                    isBlurQuant = true;
                    printf("Applying Blur QUant filter\n");
                } else if (key == 'f') {
                    isDetectFaces = true;

                } else if (key == 'o') {
                    isMosaicFace = true;
                } else if (key == 'r') {
                    isHaloFace = true;
                }
        }

        delete capdev;
        return(0);
}