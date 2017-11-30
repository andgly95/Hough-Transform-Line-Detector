//
//  AccumulatorArray.h
//  
//
//  Created by Andrew Glyadchenko on 10/30/17.
//

#ifndef AccumulatorArray_hpp
#define AccumulatorArray_hpp

#include <stdio.h>
#include <cstdlib>
#include <string>
#include <math.h>
#include <vector>
#include <image.h>

using namespace ComputerVisionProjects;

/**
 * @class Accumulator Array
 * @brief A class that creates an Accumulator Array to store an array of voting bins for a Hough Transform
 * @details
 * This object creates a two dimensional array to store voting bins for a Hough Transform. The number of rows
 * is calculated using the dimensions of the image to hold the maximum line lengths relative to the image center,
 * and the number of rows stores 180 possible angles for the line. The parameterized constructor creates the array
 * of an appropriate size, and the inputPixel function takes in the image coordinates of the pixel, and fills in
 * the accumulator array to vote on all possible lines in the image, relative to the center. The class also has
 * methods that support reading and writing the array to a file, and can generate a vector of line segments for
 * every line in the array above the threshhold.
 */

class AccumulatorArray {
private:
    int **votingBin;
    int imageRows;
    int imageColumns;
    int centerRow;
    int centerColumn;
public:
    const double PI  = 3.141592653589793238463;
    int maxLength;
    
    AccumulatorArray();
    
    /**
     *  Parameterized Constructor
     * @param an_image, takes a pointer to an image and calculates the center and max line length for the image,
     *   using it to initialize the array to the right size, and setting all bins to 0
     * @post creates the Accumulator Array object at the proper size, with all bins set to 0
     **/
    
    AccumulatorArray(Image *an_image);
    
    /**
     *  Input Pixel
     * @param i and j, the row and column of the pixel in the original image
     * @post Locates the coordinates of the pixel relative to the center, and calculates the rho value
     *  of the line at each angle theta at (X * cos(theta) + Y * sin(theta)). Increments the bucket by one
     *  at the rho value for each theta
     **/
    
    void inputPixel(int i, int j);
    
    /**
     *  Get Bins
     * @param i and j, the row and column number of the accumulator array to output
     * @return The number of votes in votingBin[i][j]
     **/
    
    int getBins(int i, int j);
    
    /**
     *  Write Bin
     * @param outputFile The name of the file to output the accumulator array to
     * @return The number of votes in the bin with the largest value
     * @post The method first writes the maxlength and dimentions of the image to the file using newlines
     *   and then outputs the number of votes for each theta seperated by a space, with a newline
     *   between every row
     **/
    int writeBin(std::string outputFile);
    
    /**
     *  Read Bin
     * @param inputFile The name of the file to read the accumulator array from
     * @param thresh The threshhold for bins to be read. If the number of votes in a bin is below the
     *   threshhold, a value of zero is input instead
     * @return The number of votes in the bin with the largest value
     * @post The method reads the maxlength and dimentions of the image from the file and creates a new voting
     *   bin array, and then inputs all of the values in the file. If the value is below the threshhold, a zero
     *   is read into the array instead.
     **/
    
    int readBin(std::string inputFile, int thresh);
    
    /**
     *  Get Lines
     * @return A vector of pairs of line endpoints for every bin in the array, relative to the image column/rows
     * @pre The array should be threshholded when read from a file, so that only the bins with votes
     *   above the threshhold get lines generated for them.
     * @algorithm The method scans through all bins in the array, and when one is found that isnt zero
     *   it checks to make sure there are no larger bins surrounding it. If it is a local maximum, then
     *   a pair of endpoints are calculated, with y = (r - x cos(t)) / sin(t) for angles between 45 and 135, and
     *   x = (r - y sin(t)) / cos(t) otherwise. Each endpoint is stored as a pair, which is then stored as another
     *   pair with the other endpoint. The pair is then pushed to the vector, which is returned after all bins have
     *   been checked
     **/
    
    std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > getLines();
};

#endif /* AccumulatorArray_hpp */
