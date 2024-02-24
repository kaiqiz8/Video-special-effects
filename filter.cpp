/*
	Kaiqi Zhang
	Spring 2024
	CS 5330 Project 1

    Filter functions
*/

#include <cstdio>
#include <cstring>
#include <opencv2/opencv.hpp> 

// implement a grayscale filter
int convertToGrayScaleAt(cv::Mat &src, cv::Mat &dst) {
    src.copyTo(dst); //makes a copy of the original CostData
    for (int i = 0; i < src.rows; i++){
        for (int j = 0; j < src.cols; j++){
            for (int k = 0; k < src.channels(); k++) {
                int sum = 0.299 * src.at<cv::Vec3b>(i, j)[2] + 0.587 * src.at<cv::Vec3b>(i, j)[1] + 0.114 * src.at<cv::Vec3b>(i, j)[0];
                dst.at<cv::Vec3b>(i, j)[k] = sum;
            }
        }
    }

    return(0);
}

//implement a sepia tone filter
int sepiaToneFilter(cv::Mat &src, cv::Mat &dst) {
    src.copyTo(dst);
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            
            float oldRed = src.at<cv::Vec3b>(i, j)[2];
            float oldGreen = src.at<cv::Vec3b>(i, j)[1];
            float oldBlue = src.at<cv::Vec3b>(i, j)[0];

            float newRed = oldRed * 0.393 + oldGreen * 0.769 + oldBlue * 0.189;
            float newGreen = oldRed * 0.349 + oldGreen * 0.686 + oldBlue * 0.168;
            float newBlue = oldRed * 0.272 + oldGreen * 0.534 + oldBlue * 0.131;
            
            newRed = (newRed > 255) ? 255 : newRed;
            newBlue = (newBlue > 255) ? 255 : newBlue;
            newGreen = (newGreen > 255) ? 255 : newGreen;

            dst.at<cv::Vec3b>(i,j)[2] = newRed;
            dst.at<cv::Vec3b>(i,j)[1] = newGreen;
            dst.at<cv::Vec3b>(i,j)[0] = newBlue;
        }
    }
    return(0);
}
//implement a 5X5 Gaussian blur filter using at<> method of cv::Mat
int blur5x5_1( cv::Mat &src, cv::Mat &dst ) {
    src.copyTo(dst);

    for (int i = 2; i < src.rows - 2; i++){
        for (int j = 2; j < src.cols - 2; j++){
            for (int k = 0; k < src.channels(); k++) {
                int sum = src.at<cv::Vec3b>(i-2, j-2)[k] + 2 * src.at<cv::Vec3b>(i-2, j-1)[k] + 4 * src.at<cv::Vec3b>(i-2, j)[k] + 2 * src.at<cv::Vec3b>(i-2, j+1)[k] + src.at<cv::Vec3b>(i-2, j+2)[k]
                    + 2 * src.at<cv::Vec3b>(i-1, j-2)[k] + 4 * src.at<cv::Vec3b>(i-1, j-1)[k] + 8 * src.at<cv::Vec3b>(i-1, j)[k] + 4 * src.at<cv::Vec3b>(i-1, j+1)[k] + 2 * src.at<cv::Vec3b>(i-1, j+2)[k]
                    + 4 * src.at<cv::Vec3b>(i, j-2)[k] + 8 * src.at<cv::Vec3b>(i, j-1)[k] + 16 * src.at<cv::Vec3b>(i, j)[k] + 8 * src.at<cv::Vec3b>(i, j+1)[k] + 4 * src.at<cv::Vec3b>(i, j+2)[k]
                    + 2 * src.at<cv::Vec3b>(i+1, j-2)[k] + 4 * src.at<cv::Vec3b>(i+1, j-1)[k] + 8 * src.at<cv::Vec3b>(i+1, j)[k] + 4 * src.at<cv::Vec3b>(i+1, j+1)[k] + 2 * src.at<cv::Vec3b>(i+1, j+2)[k]
                        + src.at<cv::Vec3b>(i+2, j-2)[k] + 2 * src.at<cv::Vec3b>(i+2, j-1)[k] + 4 * src.at<cv::Vec3b>(i+2, j)[k] + 2 * src.at<cv::Vec3b>(i+2, j+1)[k] + src.at<cv::Vec3b>(i+2, j+2)[k];
                
                // normalize the value back to a range of [0, 255]
                sum /= 100;
                dst.at<cv::Vec3b>(i,j)[k] = sum;

            }
        }
    }

    return(0);
}

//implement a 5X5 Gaussian blur filter using the pointer method
int blur5x5_2( cv::Mat &src, cv::Mat &dst ) {
    src.copyTo(dst);
    for (int i = 2; i < src.rows - 2; i++){
        cv::Vec3b *ptrup2 = src.ptr<cv::Vec3b>(i-2);
        cv::Vec3b *ptrup1 = src.ptr<cv::Vec3b>(i-1);
        cv::Vec3b *ptrmd = src.ptr<cv::Vec3b>(i);
        cv::Vec3b *ptrdn1 = src.ptr<cv::Vec3b>(i+1);
        cv::Vec3b *ptrdn2 = src.ptr<cv::Vec3b>(i+2);
        cv::Vec3b *dptr = dst.ptr<cv::Vec3b>(i);

        for (int j = 2; j < src.rows - 2; j++) {
            for (int k = 0; k < src.channels(); k++) {
                int sum = ptrup2[j - 2][k] + 2 * ptrup2[j - 1][k] + 4 * ptrup2[j][k] + 2 * ptrup2[j + 1][k] + ptrup2[j + 2][k]
                        + 2 * ptrup1[j - 2][k] + 4 * ptrup1[j - 1][k] + 8 * ptrup1[j][k] + 4 * ptrup1[j + 1][k] + 2 * ptrup1[j + 2][k]
                        + 4 * ptrmd[j - 2][k] + 8 * ptrmd[j - 1][k] + 16 * ptrmd[j][k] + 8 * ptrmd[j + 1][k] + 4* ptrmd[j + 2][k]
                        + 2 * ptrdn1[j - 2][k] + 4 * ptrdn1[j - 1][k] + 8 * ptrdn1[j][k] + 4 * ptrdn1[j + 1][k] + 2* ptrdn1[j + 2][k]
                        + ptrdn2[j - 2][k] + 2 * ptrdn2[j - 1][k] + 4 * ptrdn2[j][k] + 2 * ptrdn2[j + 1][k] + ptrdn2[j + 2][k];
                sum /= 100;
                dptr[j][k] = sum;
                
            }
        }
    }
    return(0);
}

int sobelX3x3( cv::Mat &src, cv::Mat &dst ) {
    src.copyTo(dst);

    for (int i = 1; i < src.rows - 1; i++){
        for (int j = 1; j < src.cols - 1; j++){
            for (int k = 0; k < src.channels(); k++) {
                int sum = (-1) * src.at<cv::Vec3b>(i-1, j-1)[k] + src.at<cv::Vec3b>(i-1, j+1)[k] 
                        + (-2) * src.at<cv::Vec3b>(i, j-1)[k] + 2 * src.at<cv::Vec3b>(i, j+1)[k]
                        + (-1) * src.at<cv::Vec3b>(i+1, j-1)[k] + src.at<cv::Vec3b>(i+1, j+1)[k];

                dst.at<cv::Vec3b>(i,j)[k] = static_cast<short>(sum);
            }
        }
    }
    return(0);
}



int sobelY3x3( cv::Mat &src, cv::Mat &dst ) {
    src.copyTo(dst);

    for (int i = 1; i < src.rows - 1; i++){
        for (int j = 1; j < src.cols - 1; j++){
            for (int k = 0; k < src.channels(); k++) {
                int sum = src.at<cv::Vec3b>(i-1, j-1)[k] + 2 * src.at<cv::Vec3b>(i-1, j)[k] + src.at<cv::Vec3b>(i-1, j+1)[k] 
                        + (-1) * src.at<cv::Vec3b>(i+1, j-1)[k]  + (-2) * src.at<cv::Vec3b>(i+1, j)[k] + (-1) * src.at<cv::Vec3b>(i+1, j+1)[k];

                dst.at<cv::Vec3b>(i,j)[k] = static_cast<short>(sum);
            }
        }
    }
    return(0);
}

int magnitude( cv::Mat &sx, cv::Mat &sy, cv::Mat &dst ){
    sx.copyTo(dst);
    for (int i = 0; i < sx.rows; i++){
        for (int j = 0; j < sx.cols; j++){
            for (int k = 0; k < sx.channels(); k++) {
                float value1 = static_cast<float>(sx.at<cv::Vec3s>(i, j)[k]);
                float value2 = static_cast<float>(sy.at<cv::Vec3s>(i, j)[k]);
                dst.at<cv::Vec3s>(i, j)[k] = std::sqrt(value1 * value1 + value2 * value2);
            }   
        }        
    }
    return (0);
}

int blurQuantize( cv::Mat &src, cv::Mat &dst, int levels ) {
    float bucketSize = 255.0f / levels;
    blur5x5_2(src, dst);
    
    for (int i = 0; i < dst.rows; i++) {
        for (int j = 0; j < dst.cols; j++) {
            for (int k = 0; k < dst.channels(); k++) {
                float value = dst.at<cv::Vec3b>(i, j)[k];
                float quantizedValue = std::floor(value / bucketSize) * bucketSize;

                dst.at<cv::Vec3b>(i, j)[k] = quantizedValue;
            }
        }
    }
    return (0);
}

int mosaicFilter(cv::Mat& src, const std::vector<cv::Rect>& faces, int blockSize) {
    for (const cv::Rect & face : faces) {
        // Ensure the face rectangle is within the image boundaries
        cv::Rect validFace = face & cv::Rect(0, 0, src.cols, src.rows);

        cv::Mat faceROI = src(validFace);

        for (int i = 0; i < faceROI.rows; i += blockSize) {
            for (int j = 0; j < faceROI.cols; j += blockSize) {
                int blockWidth = std::min(blockSize, faceROI.cols - j);
                int blockHeight = std::min(blockSize, faceROI.rows - i);

                cv::Mat block = faceROI(cv::Range(i, i + blockHeight), cv::Range(j, j + blockWidth));

                cv::Scalar averageColor = cv::mean(block);
                block.setTo(averageColor);
            }
        }
    }

    return(0);
}

int haloFilter(cv::Mat& src, const std::vector<cv::Rect>& faces) {
    for (const cv::Rect & face : faces) {
        // Ensure the face rectangle is within the image boundaries
        cv::Rect validFace = face & cv::Rect(0, 0, src.cols, src.rows);

        int centerX = validFace.x + validFace.width / 2;
        int centerY = validFace.y - validFace.height / 4;

        cv::Point center(centerX, centerY);
        cv::Size axes(100, 50);
        

        cv::ellipse(src, center, axes, 0.0, 0.0, 360.0, cv::Scalar(0, 215, 255), 4);

    }
    return(0);
}

