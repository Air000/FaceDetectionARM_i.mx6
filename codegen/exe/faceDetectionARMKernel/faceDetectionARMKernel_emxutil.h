/*
 * File: faceDetectionARMKernel_emxutil.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 27-Jun-2017 11:00:05
 */

#ifndef FACEDETECTIONARMKERNEL_EMXUTIL_H
#define FACEDETECTIONARMKERNEL_EMXUTIL_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "faceDetectionARMKernel_types.h"

/* Function Declarations */
extern void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, unsigned
  int elementSize);
extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);
extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);

#endif

/*
 * File trailer for faceDetectionARMKernel_emxutil.h
 *
 * [EOF]
 */
