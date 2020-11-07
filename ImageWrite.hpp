#ifndef IMAGEWRITE_HPP
#define IMAGEWRITE_HPP

#include <bits/stdc++.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
using namespace std;

class ImageWriter
{

private:
    char *filename = NULL;
    int width = 0, height = 0;
    unsigned int channels = 0;
    string getExtension();
    float **matrix = NULL;

public:
    ImageWriter(char *, int, int, unsigned int, float **);
    void save();
};

ImageWriter::ImageWriter(char *filename, int width, int height, unsigned int channels, float **matrix)
{

    this->filename = filename;
    this->width = width;
    this->height = height;
    this->channels = channels;
    this->matrix = matrix;
}

string ImageWriter::getExtension()
{
    string n = filename;
    int i;
    for (i = n.length() - 1; i >= 0; i--)
    {
        if (n[i] == '.')
            break;
    }
    string ret;
    ret.push_back(n[i + 1]);
    ret.push_back(n[i + 2]);
    ret.push_back(n[i + 3]);
    return ret;
}

void ImageWriter::save()
{

    string extension = getExtension();

    uint8_t *image = new uint8_t[height * width * channels];
    for (int i = 0; i < height * width; i++)
    {
        for (int j = 0; j < channels; j++)
        {
            image[(i * channels) + j] = (uint8_t)matrix[i][j];
        }
    }
    if (extension == "png")
        stbi_write_png(filename, width, height, channels, image, width * channels);
    else if (extension == "jpg")
        stbi_write_jpg(filename, width, height, channels, image, 100);
    else if (extension == "bmp")
        stbi_write_bmp(filename, width, height, channels, image);
    else if (extension == "tga")
        stbi_write_tga(filename, width, height, channels, image);
    else
    {
        cout<<"Invalid Filename, Check extension!"<<endl;
        return;
    }
    
    delete[] image;
}

#endif