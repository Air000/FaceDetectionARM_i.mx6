/*
 * File: faceDetectionARMKernel.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 27-Jun-2017 11:00:05
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "faceDetectionARMKernel.h"
#include "Nondirect.h"
#include "insertShape.h"
#include "faceDetectionARMKernel_emxutil.h"
#include "CascadeObjectDetector.h"
#include "faceDetectionARMKernel_data.h"
#include "CascadeClassifierCore_api.hpp"

/* Variable Definitions */
static vision_CascadeObjectDetector faceDetector;
static boolean_T faceDetector_not_empty;

/* Function Declarations */
static double rt_roundd_snf(double u);

/* Function Definitions */

/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * Arguments    : const unsigned char inRGB[921600]
 *                unsigned char outRGB[921600]
 * Return Type  : void
 */
void faceDetectionARMKernel(const unsigned char inRGB[921600], unsigned char
  outRGB[921600])
{
  vision_CascadeObjectDetector *obj;
  int num_bboxes;
  emxArray_int32_T *varargout_1;
  unsigned char b_inRGB[3];
  void * ptrObj;
  double obj_MinSize;
  int i0;
  boolean_T flag;
  static const double b[3] = { 0.29893602129377539, 0.58704307445112125,
    0.11402090425510336 };

  unsigned char u0;
  cell_wrap_3 varSizes[1];
  static const unsigned char inSize[8] = { 160U, 214U, 1U, 1U, 1U, 1U, 1U, 1U };

  boolean_T exitg1;
  static unsigned char inGray[307200];
  static const unsigned char uv0[8] = { 160U, 214U, 1U, 1U, 1U, 1U, 1U, 1U };

  double ScaleFactor;
  char ClassificationModel[125];
  static const char b_ClassificationModel[125] = { '/', 'm', 'e', 'd', 'i', 'a',
    '/', 'k', 'e', 'v', 'i', 'n', '/', 'w', 'o', 'r', 'k', '3', '/', 'M', 'A',
    'T', 'L', 'A', 'B', '/', 'R', '2', '0', '1', '7', 'a', '/', 't', 'o', 'o',
    'l', 'b', 'o', 'x', '/', 'v', 'i', 's', 'i', 'o', 'n', '/', 'v', 'i', 's',
    'i', 'o', 'n', 'u', 't', 'i', 'l', 'i', 't', 'i', 'e', 's', '/', 'c', 'l',
    'a', 's', 's', 'i', 'f', 'i', 'e', 'r', 'd', 'a', 't', 'a', '/', 'c', 'a',
    's', 'c', 'a', 'd', 'e', '/', 'h', 'a', 'a', 'r', '/', 'h', 'a', 'a', 'r',
    'c', 'a', 's', 'c', 'a', 'd', 'e', '_', 'f', 'r', 'o', 'n', 't', 'a', 'l',
    'f', 'a', 'c', 'e', '_', 'a', 'l', 't', '2', '.', 'x', 'm', 'l', '\x00' };

  unsigned int MergeThreshold;
  void * ptrDetectedObj;
  double obj_MaxSize;
  emxArray_int32_T *bboxes_;
  unsigned char b_inGray[34240];
  int MinSize_[2];
  int MaxSize_[2];
  int varargout_1_size[2];
  float varargout_1_data[36];
  int positionOut_data[36];
  unsigned char color_data[27];
  visioncodegen_ShapeInserter *h_ShapeInserter;

  /*  Kernel function for 'Face Detection on ARM Target using Code Generation' example */
  /*  Instantiate system object */
  if (!faceDetector_not_empty) {
    obj = &faceDetector;
    faceDetector.ScaleFactor = 1.1;
    faceDetector.MergeThreshold = 4.0;
    faceDetector.isInitialized = 0;
    ptrObj = NULL;
    cascadeClassifier_construct(&ptrObj);
    obj->pCascadeClassifier = ptrObj;
    flag = (obj->isInitialized == 1);
    if (flag) {
      obj->TunablePropsChanged = true;
    }

    for (i0 = 0; i0 < 2; i0++) {
      obj->MinSize[i0] = 20.0;
    }

    flag = (obj->isInitialized == 1);
    if (flag) {
      obj->TunablePropsChanged = true;
    }

    for (i0 = 0; i0 < 2; i0++) {
      obj->MaxSize[i0] = 80.0 + 26.0 * (double)i0;
    }

    ptrObj = obj->pCascadeClassifier;
    memcpy(&ClassificationModel[0], &b_ClassificationModel[0], 125U * sizeof
           (char));
    cascadeClassifier_load(ptrObj, ClassificationModel);
    c_CascadeObjectDetector_validat(obj);
    faceDetector_not_empty = true;
  }

  for (num_bboxes = 0; num_bboxes < 307200; num_bboxes++) {
    b_inRGB[0] = inRGB[num_bboxes];
    b_inRGB[1] = inRGB[num_bboxes + 307200];
    b_inRGB[2] = inRGB[num_bboxes + 614400];
    obj_MinSize = 0.0;
    for (i0 = 0; i0 < 3; i0++) {
      obj_MinSize += (double)b_inRGB[i0] * b[i0];
    }

    obj_MinSize = rt_roundd_snf(obj_MinSize);
    if (obj_MinSize < 256.0) {
      u0 = (unsigned char)obj_MinSize;
    } else {
      u0 = MAX_uint8_T;
    }

    inGray[num_bboxes] = u0;
  }

  emxInit_int32_T(&varargout_1, 2);

  /*  Create uninitialized memory in generated code */
  /*  Resize input image  */
  /*  Detect faces and create boundiong boxes around detected faces */
  obj = &faceDetector;
  if (faceDetector.isInitialized != 1) {
    faceDetector.isInitialized = 1;
    for (i0 = 0; i0 < 8; i0++) {
      varSizes[0].f1[i0] = inSize[i0];
    }

    faceDetector.inputVarSize[0] = varSizes[0];
    c_CascadeObjectDetector_validat(&faceDetector);
    obj->TunablePropsChanged = false;
  }

  if (obj->TunablePropsChanged) {
    c_CascadeObjectDetector_validat(obj);
    obj->TunablePropsChanged = false;
  }

  num_bboxes = 0;
  exitg1 = false;
  while ((!exitg1) && (num_bboxes < 8)) {
    if (obj->inputVarSize[0].f1[num_bboxes] != uv0[num_bboxes]) {
      for (i0 = 0; i0 < 8; i0++) {
        obj->inputVarSize[0].f1[i0] = inSize[i0];
      }

      exitg1 = true;
    } else {
      num_bboxes++;
    }
  }

  ptrObj = obj->pCascadeClassifier;
  ScaleFactor = obj->ScaleFactor;
  obj_MinSize = rt_roundd_snf(obj->MergeThreshold);
  if (obj_MinSize < 4.294967296E+9) {
    if (obj_MinSize >= 0.0) {
      MergeThreshold = (unsigned int)obj_MinSize;
    } else {
      MergeThreshold = 0U;
    }
  } else if (obj_MinSize >= 4.294967296E+9) {
    MergeThreshold = MAX_uint32_T;
  } else {
    MergeThreshold = 0U;
  }

  for (i0 = 0; i0 < 2; i0++) {
    obj_MinSize = obj->MinSize[i0];
    obj_MaxSize = obj->MaxSize[i0];
    obj_MinSize = rt_roundd_snf(obj_MinSize);
    if (obj_MinSize < 2.147483648E+9) {
      if (obj_MinSize >= -2.147483648E+9) {
        num_bboxes = (int)obj_MinSize;
      } else {
        num_bboxes = MIN_int32_T;
      }
    } else if (obj_MinSize >= 2.147483648E+9) {
      num_bboxes = MAX_int32_T;
    } else {
      num_bboxes = 0;
    }

    MinSize_[i0] = num_bboxes;
    obj_MinSize = rt_roundd_snf(obj_MaxSize);
    if (obj_MinSize < 2.147483648E+9) {
      if (obj_MinSize >= -2.147483648E+9) {
        num_bboxes = (int)obj_MinSize;
      } else {
        num_bboxes = MIN_int32_T;
      }
    } else if (obj_MinSize >= 2.147483648E+9) {
      num_bboxes = MAX_int32_T;
    } else {
      num_bboxes = 0;
    }

    MaxSize_[i0] = num_bboxes;
  }

  ptrDetectedObj = NULL;
  for (i0 = 0; i0 < 160; i0++) {
    for (num_bboxes = 0; num_bboxes < 214; num_bboxes++) {
      b_inGray[num_bboxes + 214 * i0] = inGray[3 * i0 + 480 * (3 * num_bboxes)];
    }
  }

  emxInit_int32_T(&bboxes_, 2);
  num_bboxes = cascadeClassifier_detectMultiScale(ptrObj, &ptrDetectedObj,
    b_inGray, 160, 214, ScaleFactor, MergeThreshold, MinSize_, MaxSize_);
  i0 = bboxes_->size[0] * bboxes_->size[1];
  bboxes_->size[0] = num_bboxes;
  bboxes_->size[1] = 4;
  emxEnsureCapacity((emxArray__common *)bboxes_, i0, sizeof(int));
  cascadeClassifier_assignOutputDeleteBbox(ptrDetectedObj, &bboxes_->data[0]);
  i0 = varargout_1->size[0] * varargout_1->size[1];
  varargout_1->size[0] = bboxes_->size[0];
  varargout_1->size[1] = bboxes_->size[1];
  emxEnsureCapacity((emxArray__common *)varargout_1, i0, sizeof(int));
  num_bboxes = bboxes_->size[0] * bboxes_->size[1];
  for (i0 = 0; i0 < num_bboxes; i0++) {
    varargout_1->data[i0] = bboxes_->data[i0];
  }

  emxFree_int32_T(&bboxes_);

  /*  Limit the number of faces to be detected in an image.  insertShape */
  /*  requires that bbox signal must be bounded */
  /*  Insert rectangle shape for bounding box */
  memcpy(&outRGB[0], &inRGB[0], 921600U * sizeof(unsigned char));
  varargout_1_size[0] = varargout_1->size[0];
  varargout_1_size[1] = 4;
  num_bboxes = varargout_1->size[0] * varargout_1->size[1];
  for (i0 = 0; i0 < num_bboxes; i0++) {
    varargout_1_data[i0] = (float)varargout_1->data[i0] * 3.0F;
  }

  emxFree_int32_T(&varargout_1);
  validateAndParseInputs(varargout_1_data, varargout_1_size, positionOut_data,
    MinSize_, color_data, MaxSize_);
  h_ShapeInserter = getSystemObjects(&h3111);
  if (1.0 != h_ShapeInserter->LineWidth) {
    h_ShapeInserter->cSFunObject.P0_RTP_LINEWIDTH = 1;
    h_ShapeInserter->LineWidth = 1.0;
  }

  if (h_ShapeInserter->isInitialized != 1) {
    h_ShapeInserter->isInitialized = 1;
  }

  Nondirect_stepImpl(h_ShapeInserter, outRGB, positionOut_data, MinSize_,
                     color_data, MaxSize_);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void faceDetectionARMKernel_init(void)
{
  faceDetector_not_empty = false;
}

/*
 * File trailer for faceDetectionARMKernel.c
 *
 * [EOF]
 */
