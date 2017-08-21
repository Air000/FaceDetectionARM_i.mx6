/*
 * File: insertShape.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 27-Jun-2017 11:00:05
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "faceDetectionARMKernel.h"
#include "insertShape.h"
#include "faceDetectionARMKernel_data.h"

/* Function Declarations */
static float rt_roundf_snf(float u);

/* Function Definitions */

/*
 * Arguments    : float u
 * Return Type  : float
 */
static float rt_roundf_snf(float u)
{
  float y;
  if ((float)fabs(u) < 8.388608E+6F) {
    if (u >= 0.5F) {
      y = (float)floor(u + 0.5F);
    } else if (u > -0.5F) {
      y = u * 0.0F;
    } else {
      y = (float)ceil(u - 0.5F);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * Arguments    : visioncodegen_ShapeInserter *iobj_0
 * Return Type  : visioncodegen_ShapeInserter *
 */
visioncodegen_ShapeInserter *getSystemObjects(visioncodegen_ShapeInserter
  *iobj_0)
{
  visioncodegen_ShapeInserter *b_iobj_0;
  b_iobj_0 = iobj_0;
  if (!h3111_not_empty) {
    b_iobj_0->isInitialized = 0;

    /* System object Constructor function: vision.ShapeInserter */
    b_iobj_0->cSFunObject.P0_RTP_LINEWIDTH = 1;
    b_iobj_0->LineWidth = 1.0;
    h3111_not_empty = true;
    h3111.isInitialized = 1;
  }

  return &h3111;
}

/*
 * Arguments    : const float position_data[]
 *                const int position_size[2]
 *                int positionOut_data[]
 *                int positionOut_size[2]
 *                unsigned char colorOut_data[]
 *                int colorOut_size[2]
 * Return Type  : void
 */
void validateAndParseInputs(const float position_data[], const int
  position_size[2], int positionOut_data[], int positionOut_size[2], unsigned
  char colorOut_data[], int colorOut_size[2])
{
  int ntilerows;
  int jcol;
  float f0;
  int ibmat;
  int itilerow;
  static const unsigned char uv2[3] = { MAX_uint8_T, MAX_uint8_T, 0U };

  positionOut_size[0] = position_size[0];
  positionOut_size[1] = 4;
  ntilerows = position_size[0] * position_size[1];
  for (jcol = 0; jcol < ntilerows; jcol++) {
    f0 = rt_roundf_snf(position_data[jcol]);
    if (f0 < 2.14748365E+9F) {
      if (f0 >= -2.14748365E+9F) {
        ibmat = (int)f0;
      } else {
        ibmat = MIN_int32_T;
      }
    } else if (f0 >= 2.14748365E+9F) {
      ibmat = MAX_int32_T;
    } else {
      ibmat = 0;
    }

    positionOut_data[jcol] = ibmat;
  }

  colorOut_size[0] = (signed char)position_size[0];
  colorOut_size[1] = 3;
  if (!((signed char)position_size[0] == 0)) {
    ntilerows = (signed char)position_size[0];
    for (jcol = 0; jcol < 3; jcol++) {
      ibmat = jcol * ntilerows;
      for (itilerow = 1; itilerow <= ntilerows; itilerow++) {
        colorOut_data[(ibmat + itilerow) - 1] = uv2[jcol];
      }
    }
  }
}

/*
 * File trailer for insertShape.c
 *
 * [EOF]
 */
