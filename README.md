# FaceDetectionARM_i.mx6
source code from matlab codegen, porting to i.mx6, and use ipu to accelerate CSC
##  Start guide
* Generate cpp source code from matlab, refer to [official guide](https://cn.mathworks.com/help/vision/examples/detect-face-raspberry-pi2.html)
* Use `./build.sh` instead of `make -f faceDetectionARMMakefile` to build exe file on iMX6
* The exe file name is `main-arm`
* The `master` branch is the original code gen by matlab; the `ipu_test` branch, CSC(Color sapce convertion) accelerate by IPU
## About IPU acceleration
* i.MX6 IPU test example refer to [rogeriorps/ipu-examples](https://github.com/rogeriorps/ipu-examples)
* We use IPU to make YUV422 to RGB888 transfermation
* The original capture and display time is about 85ms per frame on i.MX6Q, while using IPU accelerate, the time is 43ms per frame.
## About the detection function `faceDetectionARMKernel(inRGB, outRGB)`
* The time consumption is about 200ms per frame
* Notice that the input and output arguments `inRGB` and `outRGB` is not the original RGB image from caputure output. \
We should use `cArrayFromMat<uint8_T>(smallImgs, rgbMat)`, `rgbMat` refer to origin RGB image caputure from cam, `smallImgs` refer to `inRGB`. \
Then use `cArrayToMat<uint8_T>(rgbU8, numRow, numCols, true, rgbMat)` to convert the `outRGB` from `faceDetectionARMKernel(inRGB, outRGB)` to normal RGB format 
* If we display the output `smallImgs` of `cArrayFromMat<uint8_T>(smallImgs, rgbMat)`, it will be a 4x3 grey color small images matrix.

