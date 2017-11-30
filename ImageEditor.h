//
//  ImageEditor.h
//
//
//  Created by Andrew Glyadchenko on 9/18/17.
//
//

#ifndef ImageEditor_hpp
#define ImageEditor_hpp

#include <stdio.h>
#include <cstdlib>
#include <string>
#include <math.h>
#include <vector>
#include "image.h"
#include "AccumulatorArray.h"


using namespace ComputerVisionProjects;

/**
 * @class ImageEditor
 * @brief A class that points to an Image object and supports operations for manipulating the image
 * @details
 * This object contains a pointer to an image object and contains methods that allow for converting
 * an image to a binary image, performing a Gaussian Blur, Squared Gradient, and Laplacian convolution to an image,
 * creating and displaying a Hough Transform on an image, and drawing a vector of lines onto an image
 */

class ImageEditor {
private:
    Image *activeImage;
protected:
    
    
 
    /**
     * Pixel Labeler
     * @params x and y are the position of the pixel being labeled
     *
     **/
    int labelPixel(int x, int y);
    
public:
    
    ImageEditor();
    
    /**
     *  Parameterized Constructor
     * @param addImage, takes a pointer to an image and sets the image as the active image
     * @post creates the ImageEditor object with the referenced Image loaded
     **/
    
    ImageEditor(Image *addImage);
    
    /**
     *  Binary Converter
     * @param threshhold the minimum value a pixel must be to register as an object
     * @post the image is converted into a binary image where background pixels are a 0 and objects are a 1
     **/
    
    void binaryConverter(int threshhold);
    
    /**
     *  Gaussian Blur Convolution
     * @param maskedOutput the image to write the blurred output to
     * @post A kernel of |1|2|1| is applied to each pixel of the original image and divided by 16
     *                   |2|4|2|
     *                   |1|2|1|
     * creating a slight blur which greatly reduces the noise in the image
     **/
    
    void gaussianBlur(Image* maskedOutput);
    
    /**
     *  Squared Gradient Convolution
     * @param maskedOutput the image to write the edge output to
     * @post A kernel of |-1|-2|-1| and |-1| 0| 1| are applied to each pixel of the original image
     *                   | 0| 0| 0|     |-2| 0| 2|
     *                   | 1| 2| 1|     | 1| 0| 1|
     * to calculate the first derivative of the intensity along both axis, and the summed square
     * of both convolutions gives the intensity of all the edges in the image
     **/
    
    void squaredGradient(Image* maskedOutput);
    
    /**
     *  Laplacian Convolution (NOT USED)
     * @param maskedOutput the image to write the edge output to
     * @post A kernel of | 0|-1| 0| is applied to each pixel of the original image
     *                   |-1| 4|-1|
     *                   | 0|-1| 0|
     * to calculate the second derivative of the intensity of the edges in the image
     **/
    
    void laplacian(Image* maskedOutput);
    
    /**
     *  Hough Transform
     * @param inputImage a binary to create a hough transformn for
     * @pre inputImage must be a binary edge image
     * @return Outputs an Accumulator array where each pixel votes on a bin for every angle theta
     **/
    
    AccumulatorArray* houghTransform(Image* inputImage);
    
    /**
     *  Hough Image
     * @param houghArray an accumulator array with the Hough transform of a binary image
     * @param maxBright, the maximum intensity of the largest bin
     * @return Outputs an Image that displays the Hough Transform, where the intensity of
     *  each pixel is proportional to the amount of votes in the corresponding bin
     **/
    
    Image* houghImage(AccumulatorArray* houghArray, int maxBright);
    
    /**
     *  Draw Lines
     * @param lineVector a vector of line segments, where each entry is a pair of endpoints,
        represented by a pair denoting x and y
     * @param output, the image to draw the lines onto
     * @post Draws all of the lines in the vector onto the active image, making sure they don't
     *   exceed the boundaries of the image
     **/
    
    void drawLines(std::vector<std::pair< std::pair<int, int>, std::pair<int, int> >> lineVector, Image* output);
    
    
};

#endif /* ImageEditor_hpp */
