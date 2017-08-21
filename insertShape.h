/*
 * File: insertShape.h
 *
 * MATLAB Coder version            : 3.3
 * C/C++ source code generated on  : 27-Jun-2017 11:00:05
 */

#ifndef INSERTSHAPE_H
#define INSERTSHAPE_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "faceDetectionARMKernel_types.h"

/* Function Declarations */
extern visioncodegen_ShapeInserter *getSystemObjects(visioncodegen_ShapeInserter
  *iobj_0);
extern void validateAndParseInputs(const float position_data[], const int
  position_size[2], int positionOut_data[], int positionOut_size[2], unsigned
  char colorOut_data[], int colorOut_size[2]);

#endif

/*
 * File trailer for insertShape.h
 *
 * [EOF]
 */
