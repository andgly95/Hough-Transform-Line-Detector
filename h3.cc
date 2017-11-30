//
//  h3.cpp
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
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char **argv){
    
    if (argc!=4) {
        printf("Usage: %s file1 file2\n", argv[0]);
        return 0;
    }
    const string input_file(argv[1]);
    const string output_image(argv[2]);
    const string output_file(argv[3]);
    
    Image an_image;

    if (!ReadImage(input_file, &an_image)) {
        cout <<"Can't open file " << input_file << endl;
        return 0;
    }
    /*if (!ReadImage(input_file, &output_image)) {
        cout <<"Can't open file " << input_file << endl;
        return 0;
    }*/
    

    
    Image *imageReference = &an_image;

    
    ImageEditor an_image_editor(imageReference);
    //ImageEditor hough_image(houghMapRef);
    
    AccumulatorArray* houghMap = an_image_editor.houghTransform(imageReference);
    int maxBright = houghMap->writeBin(output_file);
    Image *output = an_image_editor.houghImage(houghMap, maxBright);

    
    if (!WriteImage(output_image, *output)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }
}
