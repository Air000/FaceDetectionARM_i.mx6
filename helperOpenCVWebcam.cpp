#include <time.h>
#include "opencv2/opencv.hpp"
#include "helperOpenCVWebcam.hpp"

#include "cgCommon.hpp"

using namespace cv;
using namespace std;

// Initializes webcam
void* opencvInitCam(const int frameW, const int frameH)
{
    VideoCapture *capture = new VideoCapture(2);
    capture->set(CV_CAP_PROP_FRAME_WIDTH, frameW);
    capture->set(CV_CAP_PROP_FRAME_HEIGHT, frameH);
 
    if (!capture->isOpened())  // check if we succeeded
        return 0;

    return (void *)capture;
}

// Reads RGB frame from webcam and copies it to a buffer
void opencvCaptureRGBFrameAndCopy(void *captureV, uint8_T *rgbU8)
{
    clock_t begin, end;
    unsigned int captureTime, transTime;

    begin = clock();
    VideoCapture* capture = (VideoCapture*)captureV;

    Mat frameRGBMat;
    (*capture) >> frameRGBMat;
    end = clock();
    captureTime = (end - begin)*1.0/CLOCKS_PER_SEC*1000;
    begin = clock();
    cArrayFromMat<uint8_T>(rgbU8, frameRGBMat);
    end = clock();
    transTime = (end - begin)*1.0/CLOCKS_PER_SEC*1000;
    printf("captureTime: %d, transTime: %d\n", captureTime, transTime);
}

void splitIntoSmallImgs(uint8_T *bigImg, uint8_T *smallImgs, int width, int height)
{
    cv::Mat rgbMat(height, width, CV_8UC3, bigImg);
    cArrayFromMat<uint8_T>(smallImgs, rgbMat);
    
   //cMatrixImgsFromBigImg<uint8_T>(smallImgs, bigImg, width, height); 
}
