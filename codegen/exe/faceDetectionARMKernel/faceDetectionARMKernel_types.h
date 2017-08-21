/*
 * File: faceDetectionARMKernel_types.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 27-Jun-2017 11:00:05
 */

#ifndef FACEDETECTIONARMKERNEL_TYPES_H
#define FACEDETECTIONARMKERNEL_TYPES_H

/* Include Files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_cell_wrap_3
#define typedef_cell_wrap_3

typedef struct {
  unsigned int f1[8];
} cell_wrap_3;

#endif                                 /*typedef_cell_wrap_3*/

#ifndef struct_emxArray__common
#define struct_emxArray__common

struct emxArray__common
{
  void *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray__common*/

#ifndef typedef_emxArray__common
#define typedef_emxArray__common

typedef struct emxArray__common emxArray__common;

#endif                                 /*typedef_emxArray__common*/

#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T

struct emxArray_int32_T
{
  int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_int32_T*/

#ifndef typedef_emxArray_int32_T
#define typedef_emxArray_int32_T

typedef struct emxArray_int32_T emxArray_int32_T;

#endif                                 /*typedef_emxArray_int32_T*/

#ifndef typedef_vision_CascadeObjectDetector
#define typedef_vision_CascadeObjectDetector

typedef struct {
  int isInitialized;
  boolean_T TunablePropsChanged;
  cell_wrap_3 inputVarSize[1];
  double MinSize[2];
  double MaxSize[2];
  double ScaleFactor;
  double MergeThreshold;
  void * pCascadeClassifier;
} vision_CascadeObjectDetector;

#endif                                 /*typedef_vision_CascadeObjectDetector*/

#ifndef struct_vision_ShapeInserter_0
#define struct_vision_ShapeInserter_0

struct vision_ShapeInserter_0
{
  int S0_isInitialized;
  int P0_RTP_LINEWIDTH;
};

#endif                                 /*struct_vision_ShapeInserter_0*/

#ifndef typedef_vision_ShapeInserter_0
#define typedef_vision_ShapeInserter_0

typedef struct vision_ShapeInserter_0 vision_ShapeInserter_0;

#endif                                 /*typedef_vision_ShapeInserter_0*/

#ifndef typedef_visioncodegen_ShapeInserter
#define typedef_visioncodegen_ShapeInserter

typedef struct {
  int isInitialized;
  vision_ShapeInserter_0 cSFunObject;
  double LineWidth;
} visioncodegen_ShapeInserter;

#endif                                 /*typedef_visioncodegen_ShapeInserter*/
#endif

/*
 * File trailer for faceDetectionARMKernel_types.h
 *
 * [EOF]
 */
