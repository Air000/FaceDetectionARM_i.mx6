/* 
 * Used by cgwrapper functions 
 *
 * Copyright 1995-2011 The MathWorks, Inc. 
 */

#ifndef CGCOMMON_HPP
#define CGCOMMON_HPP

#include "vision_defines.h"
#include "opencv2/opencv.hpp"

#ifdef PARALLEL
#define NUM_THREADS 4
#include <thread>
#include <vector>
#endif

using namespace std;
using namespace cv;

/////////////////////////////////////////////////////////////////////////////////
// cArrayToMat:
//  Fills up a given cv::Mat with the data from an array. 
//  The function transposes and interleaves column major array data into 
//  row major cv::Mat. 
//
//  Arguments:
//  ---------
//  in: Pointer to an array having column major data. data can
//      be n-channel matrices.
//      Supported data types are real_T (double), real32_T (single or float), 
//      uint8_T (uint8), uint16_T (uint16), uint32_T (uint32), int8_T (int8), 
//      int16_T (int16), int32_T (int32), or boolean_T (bool or logical).
//  out: Reference to OpenCV's cv::Mat with row major data.
//
//  Note:
//  ----
//  - The function reallocates memory for the cv::Mat if needed.
//  - This is a generic matrix conversion routine for any number of channels.
/////////////////////////////////////////////////////////////////////////////////

template <typename ImageDataType>
void copyToMat(ImageDataType *src, ImageDataType *dst, int start, int end, int numRows, int numCols)
{
  for (int i = start; i < end; ++i)
    {
      for (int j = 0; j < numCols; ++j)
        {
          *dst++ = src[i + j*numRows];
        }
    }
}

template <typename ImageDataType>
void copyToMatBGR(ImageDataType *src, ImageDataType *dst, int start, int end, int numRows, int numCols, int channels)
{
  int rc = numRows*numCols;

  for (int i = start; i < end; ++i)
    {
      for (int j = 0; j < numCols; ++j)
        {
          // OpenCV uses BGR ordering so we need to supply the data                                                                                                                                                
          // in the proper order, by counting backwards                                                                                                                                                            
          for (int k = (int)(channels-1); k >= 0; --k)
            {
              *dst++ = src[i + j*numRows + k*rc];
            }
        }
    }
}

template <typename ImageDataType>
void cArrayToMat(const ImageDataType *in, int numRows, int numCols, bool isRGB , cv::Mat &out)
{
    ImageDataType *imgData = (ImageDataType *)in;

	// assert that mxArray is 2D or 3D
    const int nChannels(isRGB ? 3 : 1);       
    int type = CV_MAKETYPE(cv::DataType<ImageDataType>::type,          
                           (int) nChannels);

    // allocates new matrix data unless the matrix already 
    // has specified size and type.
    // previous data is unreferenced if needed.
    out.create(static_cast<int32_T>(numRows),
               static_cast<int32_T>(numCols),
               type);

    ImageDataType *dst = reinterpret_cast<ImageDataType *>(out.data);

#ifdef PARALLEL
    vector<thread> workers;
    int blocks = numRows / NUM_THREADS;
    int start = 0, end = blocks;
#endif

    // convert column-major to row-major and interleave pixel data. OpenCV
    // stores multi-channel data in the interleaved format.        
    if (nChannels == 1)        
    {
#ifdef PARALLEL
        for( int t = 1; t <= NUM_THREADS; t++ )
        {
            if( t == NUM_THREADS )
                end += numRows % NUM_THREADS;

            workers.push_back( thread(copyToMat<ImageDataType>, imgData, &dst[start*numCols], start, end, numRows, numCols) );
            start = end;
            end = start + blocks;
        }
#else
        for (int i = 0; i < numRows; ++i)       
        {         
            for (int j = 0; j < numCols; ++j) 
            {
                *dst++ = imgData[i + j*numRows];
            }
        }
#endif
    }
    else
    {
#ifdef PARALLEL
        // assert that there are 3 color planes                                                                                                                                                                    
        for( int t = 1; t <= NUM_THREADS; t++ )
        {
            if( t == NUM_THREADS )
                end += numRows % NUM_THREADS;

            workers.push_back( thread(copyToMatBGR<ImageDataType>, imgData, &dst[start*numCols*nChannels],  start, end, numRows, numCols, nChannels) );
            start = end;
            end = start + blocks;
        }
#else
        int rc = numRows*numCols; 
        for (int i = 0; i < numRows; ++i)                
        {
            for (int j = 0; j < numCols; ++j)
            {
                // OpenCV uses BGR ordering so we need to supply the data
                // in the proper order, by counting backwards
                for (int k = (int)(nChannels-1); k >= 0; --k)
                {
                    *dst++ = imgData[i + j*numRows + k*rc];
                }
            }
        }
#endif
    } 

#ifdef PARALLEL
    for( thread &th : workers )
        th.join();
#endif
}

template <typename ImageDataType>
void copyToArray(ImageDataType *src, ImageDataType *dst, int start, int end , int numRows, int numCols)
{
    for( int i = start; i < end; i++ )
    {
        for( int j = 0; j < numCols; j++ )
        {
            dst[i+j*numRows] = *src++;
        }
    }
}

template <typename ImageDataType>
void copyToArrayBGR(ImageDataType *src, ImageDataType *dst, int start, int end , int numRows, int numCols, int channels)
{
    int rc = numRows*numCols;

    for (int i = start; i < end; ++i)
    {
        for (int j = 0; j < numCols; ++j)
          {
            // Count backwards since OpenCV uses BGR ordering of color data                                                                                                                                        
            for (int k = channels-1; k >= 0; --k)
            {
                dst[i + j*numRows + k*rc] = *src++;
            }
        }
    }
}

template <typename ImageDataType>
void cArrayFromMat(ImageDataType *outFeatures, const cv::Mat &in)
{
    //const int nDims = (in.channels() == 1 ? 2 : 3);
    int dims[3];
    dims[0] = in.size().height;
    dims[1] = in.size().width;
    dims[2] = 3;

    ImageDataType *imgData = (ImageDataType *)outFeatures;
    const int   numRows(dims[0]), numCols(dims[1]);    

    ImageDataType *src = reinterpret_cast<ImageDataType *>(in.data);

#ifdef PARALLEL
    vector<thread> workers;
    int blocks = numRows / NUM_THREADS;
    int start = 0, end = blocks;
#endif

    // convert column-major to row-major and interleave pixel data. OpenCV
    // stores multi-channel data in the interleaved format.        
    if (in.channels() == 1)        
    {
#if PARALLEL
        for( int t = 1; t <= NUM_THREADS; t++ )
        {
            if( t == NUM_THREADS )
                end += numRows % NUM_THREADS;

            workers.push_back( thread(copyToArray<ImageDataType>, &src[start*numCols], imgData, start, end, numRows, numCols) );
            start = end;
            end = start + blocks;
        }
#else
        // assert (nDims == 2);
        for (int i = 0; i < numRows; ++i)       
        {         
            for (int j = 0; j < numCols; ++j) 
            {
                imgData[i + j*numRows] = *src++;
            }
        }
#endif
    }
    else
    {
#if PARALLEL
        // assert that there are 3 color planes (i.e., dims[2] == 3); 
        for( int t = 1; t <= NUM_THREADS; t++ )
        {
            if( t == NUM_THREADS )
                end += numRows % NUM_THREADS;

            workers.push_back( thread(copyToArrayBGR<ImageDataType>, &src[start*numCols*in.channels()], imgData, start, end, numRows, numCols, in.channels()) );
            start = end;
            end = start + blocks;
        }
#else
        int rc = numRows*numCols; 
        for (int i = 0; i < numRows; ++i)                
        {
            for (int j = 0; j < numCols; ++j)
            {
                // Count backwards since OpenCV uses BGR ordering of color data
                for (int k = in.channels()-1; k >= 0; --k)
                {
                    imgData[i + j*numRows + k*rc] = *src++;
                }
            }
        }
#endif
    }    

#ifdef PARALLEL     
    for( thread &th : workers )
        th.join();
#endif
}

EXTERN_C LIBMWCVSTRT_API void cvRectToBoundingBox(const std::vector<cv::Rect> & rects, int32_T *boundingBoxes);


#endif //CGCOMMON_HPP

