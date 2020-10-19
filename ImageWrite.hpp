#include <bits/stdc++.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
using namespace std;

class ImageWriter {
    
    private:
    char* filename;
    int width, height;
    unsigned int channels;
    int** matrix;
    char* getExtension();

    public:
    ImageWriter(char*, int, int, unsigned int, int**);
    void save();
    ~ImageWriter();
};

ImageWriter::ImageWriter(char* filename, int width, int height, unsigned int channels, int** matrix) {

    this->filename = filename;
    this->width = width;
    this->height = height;
    this->channels = channels;
    this->matrix = matrix;
}

char* ImageWriter::getExtension() {
    string name = filename;
    int i;
    for(i = name.length() - 1; i>=0 ; i--) {
        if(name[i] == '.') break;
    }
    return (char*) name[i+1]+name[i+2]+name[i+3];
}

void ImageWriter::save() {

    // char* extension = getExtension();
    char* extension = "png";

    uint8_t* image = new uint8_t[height*width*channels];
    for(int i = 0; i<height*width; i++) {
        for(int j=0;j<channels;j++) {
            image[(i*channels) + j] = matrix[i][j];
        }
    }
    if(extension == "png")  
        stbi_write_png(filename, width, height, channels, image, width*channels);
    else if(extension == "jpg")
        stbi_write_jpg(filename, width, height, channels, image, 100);
    else if(extension == "bmp")
        stbi_write_bmp(filename, width, height, channels, image);
    else if(extension == "tga")
        stbi_write_tga(filename, width, height, channels, image);  
    else if(extension == "tga")
        stbi_write_tga(filename, width, height, channels, image);  

    delete extension;
    delete[] image;
}

ImageWriter::~ImageWriter() {

    delete filename;
    for(int i = 0; i < height*width; i++)
        delete[] matrix[i];
    delete[] matrix;
}