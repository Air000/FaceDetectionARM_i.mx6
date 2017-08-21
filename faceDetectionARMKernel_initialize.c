/*
 * File: faceDetectionARMKernel_initialize.c
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 27-Jun-2017 11:00:05
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "faceDetectionARMKernel.h"
#include "faceDetectionARMKernel_initialize.h"
#include "createShapeInserter_cg.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void faceDetectionARMKernel_initialize(void)
{
  rt_InitInfAndNaN(8U);
  faceDetectionARMKernel_init();
  createShapeInserter_cg_init();
}

/*
 * File trailer for faceDetectionARMKernel_initialize.c
 *
 * [EOF]
 */
