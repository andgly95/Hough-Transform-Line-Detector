//
//  h4.cpp
//
// Hough Transform
//
//  Created by Andrew Glyadchenko on 9/18/17.
//
//

#include "ImageEditor.h"
#include "AccumulatorArray.h"
#include "image.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char **argv){
    
    if (argc!=5) {
        printf("Usage: %s file1 file2\n", argv[0]);
        return 0;
    }
    const string input_file(argv[1]);
    const string input_array(argv[2]);
    const string hough_threshold(argv[3]);
    const string output_file(argv[4]);
    
    int thresholdValue = stoi(hough_threshold,nullptr,10);
    
    Image an_image;
    Image output_image;


    if (!ReadImage(input_file, &an_image)) {
        cout <<"Can't open file " << input_file << endl;
        return 0;
    }
    if (!ReadImage(input_file, &output_image)) {
        cout <<"Can't open file " << input_file << endl;
        return 0;
    }
    

    
    Image *imageReference = &an_image;
    Image *output = &output_image;

    
    ImageEditor an_image_editor(imageReference);
    ImageEditor lined_image(output);
    
    AccumulatorArray* houghMap = new AccumulatorArray;
    
    int maxBright = houghMap->readBin(input_array, thresholdValue);

     vector< pair< pair<int, int>, pair<int, int> > > foundLines = houghMap->getLines();

    lined_image.drawLines(foundLines, output);
    
    if (!WriteImage(output_file, *output)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }
}
