#ifndef NORMALIZER_HPP
#define NORMALIZER_HPP

#include <iostream>
using namespace std;

class Normalizer {

    private:
    float** matrix;
    int height, width;
    unsigned int channels;

    public:
    Normalizer(float**, int, int, unsigned int);
    void normalize();
    void denormalize();
};

Normalizer::Normalizer(float** matrix, int height, int width, unsigned int channels) {
    this->matrix = matrix;
    this->height = height;
    this->width = width;
    this->channels = channels;
}

void Normalizer::normalize() {
    for(int i=0; i<height*width; i++) {
        for(int j=0; j<channels; j++) {
            matrix[i][j] = matrix[i][j] / 255.0;
        }
    }
}

void Normalizer::denormalize() {
    for(int i=0; i<height*width; i++) {
        for(int j=0; j<channels; j++) {
            matrix[i][j] = matrix[i][j] * 255.0;
        }
    }
}

#endif