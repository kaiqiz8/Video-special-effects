/*
	Kaiqi Zhang
	Spring 2024
	CS 5330 Project 1

    Include file for a library of filter functions
*/

#ifndef FILTER_H
#define FILTER_H


#include <opencv2/opencv.hpp> 
int convertToGrayScaleAt(cv::Mat &src, cv::Mat &dst);
int sepiaToneFilter(cv::Mat &src, cv::Mat &dest);
int blur5x5_1( cv::Mat &src, cv::Mat &dst );
int blur5x5_2( cv::Mat &src, cv::Mat &dst );
int sobelX3x3( cv::Mat &src, cv::Mat &dst );
int sobelY3x3( cv::Mat &src, cv::Mat &dst );
int magnitude( cv::Mat &sx, cv::Mat &sy, cv::Mat &dst );
int blurQuantize( cv::Mat &src, cv::Mat &dst, int levels );
int mosaicFilter(cv::Mat& src, const std::vector<cv::Rect>& faces, int blockSize);
int haloFilter(cv::Mat& src, const std::vector<cv::Rect>& faces);
#endif

