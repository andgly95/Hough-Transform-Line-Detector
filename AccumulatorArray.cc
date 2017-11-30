//
//  AccumulatorArray.cpp
//  
//
//  Created by Andrew Glyadchenko on 10/30/17.
//

#include "AccumulatorArray.h"
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

AccumulatorArray::AccumulatorArray(){
    votingBin = nullptr;
    imageRows = 0;
    imageColumns = 0;
    centerRow = 0;
    centerColumn = 0;
    maxLength = 0;

}

AccumulatorArray::AccumulatorArray(Image *an_image){
    imageRows = an_image->num_rows();
    imageColumns = an_image->num_columns();
    
    centerRow = imageRows / 2;
    centerColumn = imageColumns / 2;
    
    double diagonalSize = sqrt(double(imageRows * imageRows) + double(imageColumns * imageColumns));
    maxLength = int(diagonalSize);
    
    votingBin = new int*[maxLength];
    for(int i=0;i<maxLength;i++){
        votingBin[i] = new int[180];
        for (int j=0;j<180;j++){
            votingBin[i][j] = 0;
        }
    }
}

void AccumulatorArray::inputPixel(int rowI, int columnJ){
    double relativeX = centerColumn - columnJ;
    double relativeY = centerRow - rowI;
    for (int i=0;i<180;i++){
        double theta = i * (PI / 180);
        
        double rValue = (relativeX * cos(theta) + relativeY * sin(theta));
        
        int rValueInt;
        rValue = rValue + 0.5;
        rValueInt = int(rValue);
        
        votingBin[rValueInt+399][i]++;
    }
}

int AccumulatorArray::getBins(int i, int j){
    return votingBin[i][j];
}


int AccumulatorArray::writeBin(string outputFile){
    int binMax = 0;
    //int maxI, maxJ;
    ofstream votingBinOutput;
    votingBinOutput.open (outputFile);
    votingBinOutput << maxLength << endl << imageRows << endl << imageColumns << endl;
    for(int i=0;i<maxLength;i++){
        for(int j=0;j<180;j++){
            if (binMax < votingBin[i][j]){
                binMax = votingBin[i][j];
                //maxI = i;
                //maxJ = j;
            }
            votingBinOutput << votingBin[i][j] << " ";
        }
        votingBinOutput << endl;
    }
    //cout << "Max Bin Size: " << binMax << " at " << maxI << ":" << maxJ << endl;
    votingBinOutput.close();
    return binMax;
}

int AccumulatorArray::readBin(string inputFile, int threshold){
    int binMax = 0;
    //int maxI, maxJ;
    ifstream votingBinInput;
    votingBinInput.open (inputFile);
    
    votingBinInput >> maxLength;
    votingBinInput >> imageRows;
    votingBinInput >> imageColumns;
    
    centerRow = imageRows / 2;
    centerColumn = imageColumns / 2;
    
    votingBin = new int*[maxLength];
    
    for(int i=0;i<maxLength;i++){
        votingBin[i] = new int[180];
        for(int j=0;j<180;j++){
            int voteCount;
            votingBinInput >> voteCount;
            if(voteCount > threshold){
                votingBin[i][j] = voteCount;
                if (binMax < voteCount){
                    binMax = votingBin[i][j];
                    //maxI = i;
                    //maxJ = j;
                }
            }
            else {
                votingBin[i][j] = 0;
            }
        }
        //votingBinOutput << endl;
    }
    //cout << "Max Bin Size: " << binMax << " at " << maxI << ":" << maxJ << endl;
    votingBinInput.close();
    return binMax;
}

vector< pair< pair<int, int>, pair<int, int> > > AccumulatorArray::getLines(){
    vector< pair< pair<int, int>, pair<int, int> >> foundLines;
    int horizontal = 0;
    int vertical = 0;
    for(int i=1;i<maxLength;i++){
        for(int j=1;j<180;j++){
            //Check if bin is a local maximum
            if(votingBin[i][j] > votingBin[i-1][j-1] &&
               votingBin[i][j] > votingBin[i-1][j] &&
               votingBin[i][j] > votingBin[i-1][j+1] &&
               votingBin[i][j] > votingBin[i][j-1] &&
               votingBin[i][j] > votingBin[i][j+1] &&
               votingBin[i][j] > votingBin[i+1][j-1] &&
               votingBin[i][j] > votingBin[i+1][j] &&
               votingBin[i][j] > votingBin[i+1][j+1]){
                int x1, y1, x2, y2;
                x1 = y1 = x2 = y2 = 0;
                //cout << "R = " << i << "at " << j << endl;
                if(j >= 45 && j <= 135){
                    horizontal++;
                    //y = (r - x cos(t)) / sin(t)
                    x1 = 0;
                    y1 = int((double(i-(maxLength/2)) - (double(x1 - (centerColumn) ) * cos(double(j) * PI/180))) / sin(double(j) * PI/180)) + (centerRow-1);
                    x2 = imageColumns-1;
                    y2 = int((double(i-(maxLength/2)) - (double(x2 - (centerColumn) ) * cos(double(j) * PI/180))) / sin(double(j) * PI/180)) + (centerRow-1);
                }
                else{
                    vertical++;
                    //x = (r - y sin(t)) / cos(t);
                    y1 = 0;
                    x1 = int((double(i-(maxLength/2)) - (double(y1 - (centerRow) ) * sin(double(j) * PI/180))) / cos(double(j) * PI/180)) + (centerColumn-1);
                    y2 = imageRows-1;
                    x2 = int((double(i-(maxLength/2)) - (double(y2 - (centerRow) ) * sin(double(j) * PI/180))) / cos(double(j) * PI/180)) + (centerColumn-1);
                }
                //if(x1 >= 0 && x2 >= 0 && y1 >= 0 && y2 >= 0){
                  //  if(x1 <= imageColumns && x2 <= imageColumns && y1 <= imageRows && y2 <= imageRows){
                        foundLines.push_back(pair< pair<int, int>, pair<int, int> >(pair<int, int>(x1,y1), pair<int, int>(x2,y2)));
                        //cout << "Line pushed from " << x1 << "," << y1 << " to " << x2 << "," << y2 << endl;
                   // }
                //}
            }
        }
    }
    cout << "\nHorizontal lines: " << horizontal << "\nVertical lines: " << vertical << endl << endl;
    return foundLines;
}
