
# Image Processing and Compression Library
## Overview
This library aims to provide its users with basic image processing operations along with ways to compress the images.
Currently the following operations are supported:
1. RGB to Grayscale
2. Horizontal and Vertical Flip

Support for more operations are welcome!

## Image Compression
Image compression is done using the k-means algorithm, pixel values are grouped together to form bands of pixels, hence making it more compressable for JPEG and other methods of compression.

### Results
<p align="center">
	<img src="https://drive.google.com/uc?export=view&id=1BU32rxhES8PYnSuKIEJHoetdFSLWIlN3" width="200">
	<img src="https://drive.google.com/uc?export=view&id=1Oty_3M9GRTVdfcXivr4d_75dMvbZiPFV" width="600">
</p>

## How to set up
**Note: You need to have GCC version > 10.2.0**

1. Clone the repo with `git clone https://github.com/DebadityaPal/k-means-compressor`
2. Run the software with CLI commands
The CLI commands are:
`g++ -std=c++17 compressor.cpp <args>`

## Usage
The arguments are listed below
```
Usage:
Image Compression(-c):
-i: Path to the input image
-o: Path to the output image
-cl: (Optional, default: 64) Number of clusters used for compression 
-n: (Optional) Normalize the image before compression
-it: (Optional, default: 5) Number of epochs for k-means compression

Batch Compression (-b):
-i: Path to the input directory
-o: Path to the output directory
-f: Format for output images
-cl: (Optional, default: 64) Number of clusters used for compression 
-it: (Optional, default: 5) Number of epochs for k-means compression

Seam Carving (-s):
-i: Path to the input image
-o: Path to the output image
-p: (Optional, default: 1) Percentage of width to be retained    
   
Image editing (-e):
-g: Convert to grayscale
-h: Flip the image horizontally
-v: Flip the image vertically
-i: Path to the input image
-o: Path to the output image
```
