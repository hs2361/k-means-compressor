#ifndef IMAGEEDIT_HPP
#define IMAGEEDIT_HPP

#include <iostream>
#include <cfloat>
#include <math.h>
#include <time.h>
using namespace std;

class ImageEdit
{
    private:
    int height, width;
    unsigned int channels;
    float** matrix;
    public:
    ImageEdit(float**, int, int, unsigned int);
    void VerticalFlip(ImageReader &imread);
    void HorizontalFlip(ImageReader &imread);
    void RGB2GRAY(ImageReader &imread); 
};

ImageEdit::ImageEdit(float** matrix, int height, int width, unsigned int channels)
{
    this->matrix = matrix;
    this->height = height;
    this->width = width;
    this->channels = channels;
}

void ImageEdit::RGB2GRAY(ImageReader &imread) {
    for(int i=0; i<height*width; i++) {
        matrix[i][0] = 0.3*matrix[i][0] + 0.59*matrix[i][1] + 0.11*matrix[i][2];
    }      
    imread.channels = 1;
    channels = 1;
};

void ImageEdit::VerticalFlip(ImageReader &imread) {
    float temp[channels];
    for(int i=0; i<(height/2); i++) {
        for(int j=0; j<width; j++) {
            for(int k=0;k<channels; k++) {
                temp[k] = matrix[(i*width)+j][k];
                matrix[(i*width)+j][k] = matrix[((height-1-i)*width) + j][k];
                matrix[((height-1-i)*width) + j][k] = temp[k];
            }
        }
    }
}

void ImageEdit::HorizontalFlip(ImageReader &imread) {
    float temp[channels];
    for(int i=0; i<height; i++) {
        for(int j=0; j<width/2 ;j++) {
            for(int k=0; k<channels; k++) {
                temp[k] = matrix[(i*width)+j][k];
                matrix[(i*width)+j][k] = matrix[(i*width)+(width-j-1)][k];
                matrix[(i*width)+(width-j-1)][k] = temp[k];
            }
        }
    }
}

#endif
