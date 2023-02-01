// 313355786 yair cohen
#include "myutil.h"
#include "myfunction1.h"
#include "myfunction.h"
#include "writeBMP.h"
#include "showBMP.h"
#include <stdlib.h>


void myfunction(Image *image, char* srcImgpName, char* blurRsltImgName, char* sharpRsltImgName, char* rowBlurRsltImgName, char* rowSharpRsltImgName, char* filteredBlurRsltImgName, char* filteredSharpRsltImgName, char flag) {
    
    int mn = m*n;
    int malCalc = mn*3;
    //malCalc = malCalc << 1;
    //malCalc += mn;
    
	//pixel* pixelsImg = malloc(malCalc);
	//pixel* backupOrg = malloc(malCalc);
    localPixel pixelsImg[mn];
    //pixel backupOrg[mn];
    
       
    
	/*
	* [1, 1, 1]
	* [1, 1, 1]
	* [1, 1, 1]
	*/
	//int blurKernel[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

	/*
	* [-1, -1, -1]
	* [-1, 9, -1]
	* [-1, -1, -1]
	*/
	//int sharpKernel[3][3] = {{-1,-1,-1},{-1,9,-1},{-1,-1,-1}};

	/*
	* [0, 0, 0]
	* [1, 2, 1]
	* [0, 0, 0]
	*/
	//int rowBlurKernel[3][3] = {{0, 0, 0}, {1, 2, 1}, {0, 0, 0}};

	/*
	* [0, 0, 0]
	* [-2, 6, -2]
	* [0, 0, 0]
	*/
	//int rowSharpKernel[3][3] = {{0, 0, 0},{-2,6,-2},{0, 0, 0}};
    switch (flag) {
	case ('1') :	
		// blur image
		doConvolution(image, pixelsImg,  1, malCalc); //case 1

		// write result image to file
		writeBMP(image, srcImgpName, blurRsltImgName);	

		// sharpen the resulting image
		doConvolution(image, pixelsImg, 2, malCalc); //case 2
		
		// write result image to file
		writeBMP(image, srcImgpName, sharpRsltImgName);	
        break;
     case('2'):	
		// blur image with row-blurring kernel
		doConvolution(image, pixelsImg, 3, malCalc); //case 3

		// write result image to file
		writeBMP(image, srcImgpName, rowBlurRsltImgName);

		// sharpen the resulting image with row-sharpening kernel
		doConvolution(image, pixelsImg, 4, malCalc); //case 4

		// write result image to file
		writeBMP(image, srcImgpName, rowSharpRsltImgName);	
        break;
      default:
		// apply extermum filtered kernel to blur image
		doConvolution(image, pixelsImg, 5, malCalc); // case 5

		// write result image to file
		writeBMP(image, srcImgpName, filteredBlurRsltImgName);

		// sharpen the resulting image
		doConvolution(image, pixelsImg, 2, malCalc); // case 2

		// write result image to file
		writeBMP(image, srcImgpName, filteredSharpRsltImgName);	
	}
    //free(pixelsImg);
	//free(backupOrg);
}

