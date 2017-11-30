//
//  h1.cpp
//
// Finds edge points within an edge within an image
//
//  Created by Andrew Glyadchenko on 9/18/17.
//
//

#include "ImageEditor.h"
#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char **argv){
    
    if (argc!=3) {
        printf("Usage: %s file1 file2\n", argv[0]);
        return 0;
    }
    const string input_file(argv[1]);
    const string output_file(argv[2]);
    
    Image an_image;
    Image blurred_image;
    Image output_image;

    if (!ReadImage(input_file, &an_image)) {
        cout <<"Can't open file " << input_file << endl;
        return 0;
    }
    if (!ReadImage(input_file, &blurred_image)) {
        cout <<"Can't open file " << input_file << endl;
        return 0;
    }
    if (!ReadImage(input_file, &output_image)) {
        cout <<"Can't open file " << input_file << endl;
        return 0;
    }
    
    Image *imageReference = &an_image;
    Image *maskedReference = &blurred_image;
    Image *output = &output_image;
    
    ImageEditor an_image_editor(imageReference);
    ImageEditor masked_image(maskedReference);
    
    an_image_editor.gaussianBlur(maskedReference);
    masked_image.squaredGradient(output);

    
    
    if (!WriteImage(output_file, output_image)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }
}
