// 313355786 yair cohen
#include "myfunction1.h"
#include "showBMP.h"
#include <string.h>



void doConvolution(Image *image, localPixel pixelsImg[], int apply, int malCalc)
{
    //int mn = m * n;
    //int malCalc = m*n*3;
    //pixel pixelsImg[malCalc];
    //pixel backupOrg[malCalc];
    
    
    // charsToPixels(image, pixelsImg);
    localPixel *imgData = (localPixel*)(image->data);
    memcpy(pixelsImg, imgData, malCalc);

    //memcpy(backupOrg, pixelsImg, malCalc);

    //smooth(backupOrg, pixelsImg, apply);
    int ii, jj;
    // dim = m
    //  will sum every color of pixel - for final result to return
    int red, blue, green, jjReset;
    int iiStop = m - 1, jjStop;
    int i, j, updateDim = (m - 2) * m;
    localPixel current_pixel;

    switch (apply)
    {
    case (2):

        for (i = m - 2; i; i--)
        {
            for (j = m - 2; j; --j)
            {
                // dst[updateDim + j] = applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale, filter);
                //*dst = applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale, filter);
                ii = i - 1;
                jj;
                // will sum every color of pixel - for final result to return
                red = 0;
                blue = 0;
                green = 0;
                jjReset = j - 1;
                iiStop = i + 1;
                jjStop = j + 1;

                //int min_intensity = 766; // arbitrary value that is higher than maximum possible intensity, which is 255*3=765
                //int max_intensity = -1;  // arbitrary value that is lower than minimum possible intensity, which is 0

                int iiDim = ii * m;
                for (; ii <= iiStop; ii++, iiDim += m)
                {

                    for (jj = jjReset; jj <= jjStop; jj++)
                    {

                        // apply kernel on pixel at [ii,jj]
                        // sum_pixels_by_weight(&sum, src[iiDim + jj], kernel[kRow][kCol]);
                        int iiDimJj = iiDim + jj;
                        // int weight = kernel[kRow][kCol];
                        current_pixel = *(imgData+iiDimJj);
                        if (ii != i || jj != j)
                        {
                            red -= (int)current_pixel.red;
                            green -= (int)current_pixel.green;
                            blue -= ((int)current_pixel.blue);
                        }
                        else
                        {
                            red += (int)current_pixel.red * 9;
                            green += ((int)current_pixel.green) * 9;
                            blue += ((int)current_pixel.blue) * 9;
                        }
                    }
                }

                // assign kernel's result to pixel at [i,j]
                // divide by kernel's weight
                if (red > 255)
                {
                    red = 255;
                }
                
                //red &= ~(red >> 31);
                //red &= ~(red >> 8);
                //red &= ((255- red) >> 31);
                //red |= ~(red >> 8);
                else if (red < 0)
                {
                    red = 0;
                }
                if (green > 255)
                {
                    green = 255;
                }
                //green &= ~(green >> 31);
                else if (green < 0)
                {
                    green = 0;
                }
                if (blue > 255)
                {
                    blue = 255;
                }
                //blue &= ~(blue >> 31);
                else if (blue < 0)
                {
                    blue = 0;
                }
                
                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = red;
                current_pixel.green = green;
                current_pixel.blue = blue;
                //pixel *temp = (pixel*) &(image->data);
                //temp += updateDim + j;
                //*temp = current_pixel;
                pixelsImg[updateDim + j] = current_pixel;
            }
            updateDim -= m;
        }
        break;

    case (1):

        for (i = m - 2; i; i--)
        {
            for (j = m - 2; j; --j)
            {
                // dst[updateDim + j] = applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale, filter);
                //*dst = applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale, filter);
                ii = i - 1;
                jj;
                // will sum every color of pixel - for final result to return
                red = 0;
                blue = 0;
                green = 0;
                jjReset = j - 1;
                iiStop = i + 1;
                jjStop = j + 1;
                //int min_intensity = 766; // arbitrary value that is higher than maximum possible intensity, which is 255*3=765
                //int max_intensity = -1;  // arbitrary value that is lower than minimum possible intensity, which is 0

                int iiDim = ii * m;
                //int limit = 254;
                //limit = limit << 3;
                //limit += 254;
                for (; ii <= iiStop; ii++, iiDim += m)
                {

                    for (jj = jjReset; jj <= jjStop; jj++)
                    {
                        //if (red > limit && blue > limit && green > limit){ break;}
                        // apply kernel on pixel at [ii,jj]
                        // sum_pixels_by_weight(&sum, src[iiDim + jj], kernel[kRow][kCol]);
                        //int iiDimJj = iiDim + jj;
                        // int weight = kernel[kRow][kCol];
                        current_pixel = *(imgData+iiDim+jj);
                        red += current_pixel.red;
                        green += current_pixel.green;
                        blue += current_pixel.blue;
                    }
                }

                // assign kernel's result to pixel at [i,j]
                // divide by kernel's weight
                red /= 9;
                green /= 9;
                blue /= 9;
                //no need to check for negative because we apply only positive actions upon the original pixels
                // no need to check for 255 because 255*9/9 <= 255 (for all maximal pixels in 255)
                /*if (red > 255)
                {
                    red = 255;
                }
                else if (red < 0)
                {
                    red = 0;
                }
                if (green > 255)
                {
                    green = 255;
                }
                /*else if (green < 0)
                {
                    green = 0;
                }
                if (blue > 255)
                {
                    blue = 255;
                }
                /*else if (blue < 0)
                {
                    blue = 0;
                }*/

                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = red;
                current_pixel.green = green;
                current_pixel.blue = blue;
                pixelsImg[updateDim + j] = current_pixel;
            }
            updateDim -= m;
        }
        break;
    case (3):

        for (i = m - 2; i; i--)
        {
            for (j = m - 2; j; --j)
            {
                // dst[updateDim + j] = applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale, filter);
                //*dst = applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale, filter);
                ii = i - 1;
                jj;
                // will sum every color of pixel - for final result to return
                red = 0;
                blue = 0;
                green = 0;
                jjReset = j - 1;
                iiStop = i + 1;
                jjStop = j + 1;
                //int min_intensity = 766; // arbitrary value that is higher than maximum possible intensity, which is 255*3=765
                //int max_intensity = -1;  // arbitrary value that is lower than minimum possible intensity, which is 0

                int iiDim = ii * m;
                for (; ii <= iiStop; ii++, iiDim += m)
                {

                    for (jj = jjReset; jj <= jjStop; jj++)
                    {

                        // apply kernel on pixel at [ii,jj]
                        // sum_pixels_by_weight(&sum, src[iiDim + jj], kernel[kRow][kCol]);
                        int iiDimJj = iiDim + jj;
                        // int weight = kernel[kRow][kCol];

                        if (ii == i)
                        {
                            current_pixel = *(imgData+iiDimJj);
                            red += current_pixel.red;
                            green += current_pixel.green;
                            blue += current_pixel.blue;
                            if (jj == j)
                            {
                                red += current_pixel.red;
                                green += current_pixel.green;
                                blue += current_pixel.blue;
                            }
                        }
                    }
                }

                // assign kernel's result to pixel at [i,j]
                // divide by kernel's weight
                red = red >> 2;
                green = green >> 2;
                blue = blue >> 2;
                //no need to check for negative because we apply only positive actions upon the original pixels
                //no need to check positive because also adding maximum 255*4 and than /4
                /*if (red > 255)
                {
                    red = 255;
                }
                /*else if (red < 0)
                {
                    red = 0;
                }
                if (green > 255)
                {
                    green = 255;
                }
                /*else if (green < 0)
                {
                    green = 0;
                }
                if (blue > 255)
                {
                    blue = 255;
                }
                /*else if (blue < 0)
                {
                    blue = 0;
                }*/

                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = red;
                current_pixel.green = green;
                current_pixel.blue = blue;
                pixelsImg[updateDim + j] = current_pixel;
            }
            updateDim -= m;
        }
        break;
    case (4):

        for (i = m - 2; i; i--)
        {
            for (j = m - 2; j; --j)
            {
                ii = i - 1;
                jj = 0;
                // will sum every color of pixel - for final result to return
                red = 0;
                blue = 0;
                green = 0;
                jjReset = j - 1;
                iiStop = i + 1;
                jjStop = j + 1;
                
                int iiDim = ii * m;
                for (; ii <= iiStop; ii++, iiDim += m)
                {

                    for (jj = jjReset; jj <= jjStop; jj++)
                    {

                        // apply kernel on pixel at [ii,jj]
                        // sum_pixels_by_weight(&sum, src[iiDim + jj], kernel[kRow][kCol]);
                        int iiDimJj = iiDim + jj;
                        // int weight = kernel[kRow][kCol];
                        if (ii == i)
                        {
                            current_pixel = *(imgData+iiDimJj);

                            if (jj == j)
                            {
                                red += current_pixel.red * 6;
                                green += current_pixel.green * 6;
                                blue += current_pixel.blue * 6;
                            }
                            else
                            {
                                //red += current_pixel.red * -2;
                                //green += current_pixel.green * -2;
                                //blue += current_pixel.blue * -2;
                                red -= current_pixel.red + current_pixel.red ;
                                green -= current_pixel.green + current_pixel.green ;
                                blue -= current_pixel.blue + current_pixel.blue ;
                            }
                        }
                    }
                }

                // assign kernel's result to pixel at [i,j]
                // divide by kernel's weight
                red = red >> 1;
                green = green >> 1;
                blue = blue >> 1;
                if (red > 255)
                {
                    red = 255;
                }
                
                //red &= ~(red >> 31);
                //red &= ~((255- red) >> 31);
                //red |= ~(red >> 8);
                else if (red < 0)
                {
                    red = 0;
                }
                if (green > 255)
                {
                    green = 255;
                }
                //green &= ~(green >> 31);
                else if (green < 0)
                {
                    green = 0;
                }
                if (blue > 255)
                {
                    blue = 255;
                }
                //blue &= ~(blue >> 31);
                else if (blue < 0)
                {
                    blue = 0;
                }
                
                /*red |= red >> 31;
                red &= ~(red >> 8);
                green |= green >> 31;
                green &= ~(green >> 8);
                blue |= blue >> 31;
                blue &= ~(blue >> 8);*/

                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red =  red ;
                current_pixel.green = green;
                current_pixel.blue =  blue;
                //printf (""%d %d %d\n", current_pixel.red, current_pixel.green, current_pixel.blue);
                pixelsImg[updateDim + j] = current_pixel;
            }
            updateDim -= m;
        }
        break;
    case(5): // apply = 5 - default?
        //somehow it works faster with comparing to zero
        for (i = m - 2; i; i--)
        {
            
            for (j = m - 2; j; --j)
            {
                //int oldMinRowDim = -1, oldMaxRowDim = -1;
                // dst[updateDim + j] = applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale, filter);
                //*dst = applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale, filter);
                ii = i - 1;
                jj;
                // will sum every color of pixel - for final result to return
                red = 0;
                blue = 0;
                green = 0;
                jjReset = j - 1;
                iiStop = i + 1;
                jjStop = j + 1;
                int min_intensity = 766; // arbitrary value that is higher than maximum possible intensity, which is 255*3=765
                int max_intensity = -1;  // arbitrary value that is lower than minimum possible intensity, which is 0
                int min_row, min_col, max_row, max_col;
                int intensity;
                int iiDim = ii * m;
                for (; ii <= iiStop; ii++, iiDim += m)
                {
                    //inner loop unroled:
                    
                    //for (jj = jjReset; jj <= jjStop; jj++)
                    //{

                        // apply kernel on pixel at [ii,jj]
                        // sum_pixels_by_weight(&sum, src[iiDim + jj], kernel[kRow][kCol]);
                        int iiDimJj = iiDim + j - 1;
                        // int weight = kernel[kRow][kCol];
                        current_pixel = *(imgData+iiDimJj);
                        red += current_pixel.red;
                        green += current_pixel.green;
                        blue += current_pixel.blue;
                        intensity = ((current_pixel.red) + (current_pixel.green) + (current_pixel.blue));

                        if (intensity <= min_intensity)
                        {
                            min_intensity = intensity;
                            min_row = ii;
                            min_col = j - 1;
                        }
                        if (intensity > max_intensity)
                        {
                            max_intensity = intensity;
                            max_row = ii;
                            max_col = j - 1;
                        }
                    //}
                        iiDimJj++;
                        // int weight = kernel[kRow][kCol];
                        current_pixel = *(imgData+iiDimJj);
                        red += current_pixel.red;
                        green += current_pixel.green;
                        blue += current_pixel.blue;
                        intensity = ((current_pixel.red) + (current_pixel.green) + (current_pixel.blue));

                        if (intensity <= min_intensity)
                        {
                            min_intensity = intensity;
                            min_row = ii;
                            min_col = j ;
                        }
                        if (intensity > max_intensity)
                        {
                            max_intensity = intensity;
                            max_row = ii;
                            max_col = j ;
                        }
                        iiDimJj++;
                        // int weight = kernel[kRow][kCol];
                        current_pixel = *(imgData+iiDimJj);
                        red += current_pixel.red;
                        green += current_pixel.green;
                        blue += current_pixel.blue;
                        intensity = ((current_pixel.red) + (current_pixel.green) + (current_pixel.blue));

                        if (intensity <= min_intensity)
                        {
                            min_intensity = intensity;
                            min_row = ii;
                            min_col = j + 1 ;
                        }
                        if (intensity > max_intensity)
                        {
                            max_intensity = intensity;
                            max_row = ii;
                            max_col = j + 1;
                        }
                }
                
                // filter out min and max

                // sum_pixels_by_weight(&sum, src[min_row*dim + min_col], -1);
                //int minRowDim = min_row * m + min_col, maxRowDim = max_row * m + max_col;
                //if (minRowDim != oldMinRowDim){
    
                current_pixel = *(imgData + min_row * m + min_col);
                localPixel max_pixel = *(imgData+max_row * m + max_col);
                // mult by -1
                red -= (current_pixel.red) + (max_pixel.red);
                green -= (current_pixel.green) + (max_pixel.green);
                blue -= (current_pixel.blue) +(max_pixel.blue);
                // assign kernel's result to pixel at [i,j]
                // divide by kernel's weight
                //float div = 1/7;
                red /= 7;
                green /= 7;
                blue /= 7;
                //no need to check because after filter - adding 255*7 the most - and than /7
                //for same reason - definetly positive
                /*if (red > 255)
                {
                    red = 255;
                }
                
                //red &= ~(red >> 31);
                //red &= ~((255- red) >> 31);
                //red |= ~(red >> 8);
                else if (red < 0)
                {
                    red = 0;
                }
                if (green > 255)
                {
                    green = 255;
                }
                //green &= ~(green >> 31);
                else if (green < 0)
                {
                    green = 0;
                }
                if (blue > 255)
                {
                    blue = 255;
                }
                //blue &= ~(blue >> 31);
                else if (blue < 0)
                {
                    blue = 0;
                }
                /*red |= red >> 31;
                red &= ~(red >> 8);
                green |= green >> 31;
                green &= ~(green >> 8);
                blue |= blue >> 31;
                blue &= ~(blue >> 8);*/


                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = red;
                current_pixel.green = green;
                current_pixel.blue = blue;
                pixelsImg[updateDim + j] = current_pixel;
            }
            updateDim -= m;
        }
    }
    // pixelsToChars(pixelsImg, image);
    imgData = (localPixel*)image->data;
    memcpy(imgData, pixelsImg, malCalc);
}
