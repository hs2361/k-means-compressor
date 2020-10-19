#include <bits/stdc++.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
using namespace std;

class ImageReader{

    private:
    char* filename;
    int height, width, bpp;
    unsigned int channels;

    public:
    int ** matrix;
    ImageReader(char*, unsigned int);
    int length(){ return height*width;}
    int getChannels() {return channels;}
    ~ImageReader();
};

ImageReader::ImageReader(char* filename, unsigned int channels) {

    uint8_t* image = stbi_load(filename, &this->width, &this->height, &this->bpp, channels);
    this->filename = filename;
    this->channels = channels;

    matrix = new int*[height*width];
    for(int i = 0; i < height*width; i++)
        matrix[i] = new int[channels];
    
    for(int i = 0; i < height*width*channels; i+=channels) {
        uint8_t* pixel = image + i;
        for(int j = 0; j < channels; j++){
            matrix[i/channels][j] = pixel[j];
        }
    }
    stbi_image_free(image);
}

ImageReader::~ImageReader() {

    for(int i = 0; i < height*width; i++)
        delete[] matrix[i];
    delete[] matrix;

    delete filename;
}
