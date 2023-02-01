// 313355786 yair cohen
#ifndef __myfunc1_h
#define __myfunc1_h

#include "myutil.h"
#include "readBMP.h"

typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} localPixel;

//void doConvolution(Image *image, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale, bool filter, pixel* pixelsImg, pixel* backupOrg);
void doConvolution(Image *image,localPixel pixelsImg[], int aplly, int malCalc);



#endif

/*Param: 1 Average runtime: 0.689
Param: 2 Average runtime: 0.663
Param: 3 Average runtime: 1.406
===================================    500_pic/gibson_500.bmp    ===================================
Param: 1 Average runtime: 3.858
Param: 2 Average runtime: 2.066
Param: 3 Average runtime: 8.480
===================================    700_pic/Matera_700.bmp    ===================================
Param: 1 Average runtime: 10.192
Param: 2 Average runtime: 6.776
Param: 3 Average runtime: 19.960*/


