RRRR EEEE  AA  DDD    M   M EEEE
R  R E    A  A D  D   MM MM E
RRRR EEEE AAAA D  D   M M M EEEE
R R  E    A  A D  D   M   M E
R  R EEEE A  A DDD    M   M EEEE

Andrew Glyadchenko
Assignment 3

For this assignment I managed to complete all four parts, which work almost perfectly. I reengineered by ImageEditor class from the last assignment to execute most of the tasks, adding methods for Edge Detection and Hough Transform, and created an Accumulator Array class to store the Accumulator Array for the Hough transform.

The first part of the assignment, h1, was easy to set up. I simply had to write a method to apply a gaussian convolution to each pixel to reduce noice, and then apply two Sobel operators to each pixel to obtained the squared gradient. For h2 all I had to do was repurpose the code I’d written for p1 in assignment 2.

Part 3 took a while to figure out, as I initially tried to implement it using just the Image class to store the accumulator array, but I had difficulty getting the proper values for rho, and storing brightness values greater than 255. I ended up creating a separate class to store the Accumulator array, and realized that it made more sense to calculate the pixel coordinates from the center the image, rather than using row and collumn numbers. I also realized that by offsetting the array by 400 I could capture all of the positive and negative values for rho, and only use 180 angles. I also needed to output the Array as a text file, so I made a method to output the values with the angles delineated by spaces and the lengths delineated by newlines. I made the write method return the value of the highest bin, so that the program could then output the image of the hough transform and make the brightness of each bin proportional to the max. Afterwards to display the transform I created a method to output the image with all the brightness levels proportional to the number of votes out of 255.

To do part 4, I had to read the hough data from the output of p3, so I basically had to create a read method that performed the write in reverse, and repopulated a new Accumulator Array. However because part 4 uses a threshold to ignore bins below a certain amount, I decided to use the threshold to only read bins above the threshold, keeping all other bins at zero. Afterwards, I wrote a getLines() method for my accumulator array class that would take all of the nonempty bins in the array, and calculate lines to be pushed into a vector. This was the most challenging part of the assignment, as it took a lot of math as well as trial and error in order to convert the rho and theta values into endpoints in the image coordinates. Because the values had been calculated relative to the center of the image, I had to work out how to convert them into row and column values that could be later passed onto the DrawLine function. Because each line requires two endpoints and each endpoint contains an x and a y coordinate, I used std::pair to store each endpoint, and then another std::pair to store both endpoints as a line, that could be pushed into the vector. The returned vector is then input into the drawLines() method of the Image Editor, which extracts the endpoints from each line, modifies them to make sure they fit in the image size, and then draws them onto the original image.

The final output isn’t perfect, but generally tends to capture all of the lines in most images, however it does tend to capture a few diagonal lines that aren’t found in the image.

The threshold values used for the test files are the following
BinaryThreshold:
simple_1 - 75
simple_2 - 75
complex_1 - 115
HoughThreshold:
simple_1 - 250
simple_2 - 200
complex_1 - 150

Problems 1 and 2 are also in this directory as JPGs

The programs should compile with the make all command.

For h1 the command to run is ./h1 inputfile.pgm outputfile_edge.pgm 

For h2 the command to run is ./h2 inputfile_edge.pgm threshhold outputfile_binary.pgm 

For h3 the command to run is ./h3 inputfile_binary.pgm outputfile_houghimage.pgm outputfile_array.txt 

For h4 the command to run is ./h4 inputfile.pgm inputfile_array.txt threshold outputfile_output.pgm