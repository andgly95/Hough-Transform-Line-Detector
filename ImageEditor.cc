//
//  ImageEditor.cpp
//  
//
//  Created by Andrew Glyadchenko on 9/18/17.
//
//

#include "ImageEditor.h"
#include "image.h"
#include <cstdio>
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using namespace ComputerVisionProjects;

ImageEditor::ImageEditor(){
    activeImage = nullptr;
}



ImageEditor::ImageEditor(Image *addImage){
    activeImage = addImage;
}

void ImageEditor::binaryConverter(int threshhold){
    for (int i=0;i<activeImage->num_rows();i++){
        for (int j=0;j<activeImage->num_columns();j++){
            if (activeImage->GetPixel(i,j) < threshhold){
                activeImage->SetPixel(i,j,0);
            }
            else if (activeImage->GetPixel(i,j) >= threshhold){
                activeImage->SetPixel(i,j,1);
            }
        }
    }
    activeImage->SetNumberGrayLevels(1);
    return;
}


void ImageEditor::squaredGradient(Image* maskedOutput){
    //cout << "method called\n";
    int maskX[9] = {-1,0,1,-2,0,2,-1,0,1};
    int maskY[9] = {-1,-2,-1,0,0,0,1,2,1};
    for (int i=1;i<activeImage->num_rows()-1;i++){
        for (int j=1;j<activeImage->num_columns()-1;j++){
            int pixels[9] = {activeImage->GetPixel(i-1,j-1),activeImage->GetPixel(i-1,j),activeImage->GetPixel(i-1,j+1),activeImage->GetPixel(i,j-1),activeImage->GetPixel(i,j),activeImage->GetPixel(i,j+1),activeImage->GetPixel(i+1,j-1),activeImage->GetPixel(i+1,j),activeImage->GetPixel(i+1,j+1)};
            
            int sumX = 0;
            int sumY = 0;
            
            for(int k=0;k<9;k++){
                sumX += maskX[k] * pixels[k];
                sumY += maskY[k] * pixels[k];
            }
            
            double squaredSums = double((sumX*sumX)+(sumY*sumY));
            squaredSums = sqrt(squaredSums);
            //cout << "edge value: " << i << " : " << j << " : "  << int(squaredSums) << endl;
            //cout << "sums: " << sumX << " : " << sumY << endl;
            if (squaredSums > 255){
                squaredSums = 255;
            }
            maskedOutput->SetPixel(i,j,int(squaredSums));
        }
    }
    return;
}
void ImageEditor::gaussianBlur(Image* maskedOutput){
    //cout << "method called\n";
    int maskBlur[9] = {1,2,1,2,4,2,1,2,1};
    //int maskY[9] = {-1,-2,-1,0,0,0,1,2,1};
    for (int i=1;i<activeImage->num_rows()-1;i++){
        for (int j=1;j<activeImage->num_columns()-1;j++){
            int pixels[9] = {activeImage->GetPixel(i-1,j-1),activeImage->GetPixel(i-1,j),activeImage->GetPixel(i-1,j+1),activeImage->GetPixel(i,j-1),activeImage->GetPixel(i,j),activeImage->GetPixel(i,j+1),activeImage->GetPixel(i+1,j-1),activeImage->GetPixel(i+1,j),activeImage->GetPixel(i+1,j+1)};
            
            int sumX = 0;
            //int sumY = 0;
            
            for(int k=0;k<9;k++){
                sumX += maskBlur[k] * pixels[k];
                //sumY += maskY[k] * pixels[k];
            }
            
            double squaredSums = double(sumX) / 16;
            //squaredSums = sqrt(squaredSums);
            //cout << "edge value: " << i << " : " << j << " : "  << int(squaredSums) << endl;
            //cout << "sums: " << sumX << " : " << sumY << endl;
            if (squaredSums > 255){
                squaredSums = 255;
            }
            //cout << "u dun fucked up " << i << ":" << j << endl;
            maskedOutput->SetPixel(i,j,int(squaredSums));
        }
    }
    return;
}

void ImageEditor::laplacian(Image* maskedOutput){
    //cout << "method called\n";
    int maskBlur[9] = {0,-1,0,-1,4,-1,0,-1,0};
    //int maskY[9] = {-1,-2,-1,0,0,0,1,2,1};
    for (int i=1;i<activeImage->num_rows()-1;i++){
        for (int j=1;j<activeImage->num_columns()-1;j++){
            int pixels[9] = {activeImage->GetPixel(i-1,j-1),activeImage->GetPixel(i-1,j),activeImage->GetPixel(i-1,j+1),activeImage->GetPixel(i,j-1),activeImage->GetPixel(i,j),activeImage->GetPixel(i,j+1),activeImage->GetPixel(i+1,j-1),activeImage->GetPixel(i+1,j),activeImage->GetPixel(i+1,j+1)};
            
            int sumX = 0;
            //int sumY = 0;
            
            for(int k=0;k<9;k++){
                sumX += maskBlur[k] * pixels[k];
                //sumY += maskY[k] * pixels[k];
            }
            
            double squaredSums = double(sumX) + 128;
            //squaredSums = sqrt(squaredSums);
            //cout << "edge value: " << i << " : " << j << " : "  << int(squaredSums) << endl;
            //cout << "sums: " << sumX << " : " << sumY << endl;
            if (squaredSums > 255){
                squaredSums = 255;
            }
            //cout << "u dun fucked up " << i << ":" << j << endl;
            maskedOutput->SetPixel(i,j,int(squaredSums));
        }
    }
    return;
}

AccumulatorArray* ImageEditor::houghTransform(Image* inputImage){
    
    AccumulatorArray* houghArray = new AccumulatorArray(inputImage);
    
    for (int i=1;i<activeImage->num_rows()-1;i++){
        for (int j=1;j<activeImage->num_columns()-1;j++){
            

            if (activeImage->GetPixel(i,j) == 1){
                houghArray->inputPixel(i,j);
            }
        }
    }
    
    return houghArray;
}

Image* ImageEditor::houghImage(AccumulatorArray* houghArray, int maxBright){
    Image* houghOutput = new Image();
    houghOutput->AllocateSpaceAndSetSize(houghArray->maxLength, 180);
    for(int i=0;i<houghOutput->num_rows();i++){
        for(int j=0;j<houghOutput->num_columns();j++){
            double intensity = double(houghArray->getBins(i,j)) / double(maxBright) * 255;
            //if (intensity > 255) intensity = 255;
            houghOutput->SetPixel(i,j,int(intensity));
        }
    }
    houghOutput->SetNumberGrayLevels(255);
    return houghOutput;
}

void ImageEditor::drawLines(vector<pair< pair<int, int>, pair<int, int> >> lineVector, Image* output){
    int vectorsize = lineVector.size();
    for(int i=0;i<vectorsize;i++){
        int x1 = (activeImage->num_columns() - lineVector[i].first.first);
        int y1 = (activeImage->num_rows() - lineVector[i].first.second);
        int x2 = (activeImage->num_columns() - lineVector[i].second.first);
        int y2 = (activeImage->num_rows() - lineVector[i].second.second);
        if(x1 >= 640){
            x1 = 639;
        }
        if(x1 <= 0){
            x1 = 0;
        }
        if(y1 >= 480){
            y1 = 479;
        }
        if(y1 <= 0){
            y1 = 0;
        }
        if(x2 >= 640){
            x2 = 639;
        }
        if(x2 <= 0){
            x2 = 0;
        }
        if(y2 >= 480){
            y2 = 479;
        }
        if(y2 <= 0){
            y2 = 0;
        }
        //cout << "DrawingLines "<< i << " " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
        //
        //cout << sqrt(((x2-x1) * (x2-x1)) + ((y2-y1) * (y2-y1))) << endl;
        //activeImage->AllocateSpaceAndSetSize(800,800);
        //cout << "Image Allocated: \n";
        //DrawLine(50,50,100,100,255,output);
        DrawLine(y1,x1,y2,x2,255,activeImage);
    }
}



