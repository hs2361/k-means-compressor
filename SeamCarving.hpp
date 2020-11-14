#ifndef SEAMCARVING_HPP
#define SEAMCARVING_HPP

#include <iostream>
#include <math.h>
#include "ImageRead.hpp"
using namespace std;

class SeamCarving
{
private:
    float sobel_x[3][3] = {{-0.125, 0.0, 0.125}, {-0.5, 0, 0.5}, {-0.125, 0.0, 0.125}};
    float sobel_y[3][3] = {{-0.125, -0.5, -0.125}, {0.0, 0.0, 0.0}, {0.125, 0.5, 0.125}};
    int height, width;
    unsigned int channels;
    float **matrix;
    float **convImage = NULL;
    float **energy = NULL;
    int *path = NULL;
    void Convolution();
    void CalculateEnergy();
    void CalculatePath();
    void CarvePath(ImageReader &imread);

public:
    SeamCarving(float **, int, int, unsigned int);
    void fit(ImageReader &imread, int);
    ~SeamCarving();
};

SeamCarving::SeamCarving(float **matrix, int height, int width, unsigned int channels)
{
    this->matrix = matrix;
    this->height = height;
    this->width = width;
    this->channels = channels;

    convImage = new float *[height];
    for (int i = 0; i < height; i++)
    {
        convImage[i] = new float[width];
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            convImage[i][j] = 0;
    }

    energy = new float *[height];
    for (int i = 0; i < height; i++)
    {
        energy[i] = new float[width];
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            energy[i][j] = 0;
    }

    path = new int[height];
}

void SeamCarving::Convolution()
{
    float xConv, yConv;
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            xConv = 0;
            yConv = 0;
            for (int k = 0; k < channels; k++)
            {
                xConv += matrix[((i - 1) * width) + j - 1][k] * sobel_x[0][0] + matrix[((i - 1) * width) + j][k] * sobel_x[0][1] + matrix[((i - 1) * width) + j + 1][k] * sobel_x[0][2] +
                         matrix[(i * width) + j - 1][k] * sobel_x[1][0] + matrix[(i * width) + j][k] * sobel_x[1][1] + matrix[(i * width) + j + 1][k] * sobel_x[1][2] +
                         matrix[((i + 1) * width) + j - 1][k] * sobel_x[2][0] + matrix[((i + 1) * width) + j][k] * sobel_x[2][1] + matrix[((i + 1) * width) + j + 1][k] * sobel_x[2][2];

                yConv += matrix[((i - 1) * width) + j - 1][k] * sobel_y[0][0] + matrix[((i - 1) * width) + j][k] * sobel_y[0][1] + matrix[((i - 1) * width) + j + 1][k] * sobel_y[0][2] +
                         matrix[(i * width) + j - 1][k] * sobel_y[1][0] + matrix[(i * width) + j][k] * sobel_y[1][1] + matrix[(i * width) + j + 1][k] * sobel_y[1][2] +
                         matrix[((i + 1) * width) + j - 1][k] * sobel_y[2][0] + matrix[((i + 1) * width) + j][k] * sobel_y[2][1] + matrix[((i + 1) * width) + j + 1][k] * sobel_y[2][2];
            }
            convImage[i][j] = sqrtf(xConv * xConv + yConv * yConv);
        }
    }
}

void SeamCarving::CalculateEnergy()
{
    for (int i = 0; i < width; i++)
    {
        energy[height - 1][i] = convImage[height - 1][i];
    }
    for (int i = height - 2; i >= 0; i--)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
                energy[i][j] = min(convImage[i + 1][j], convImage[i + 1][j + 1]) + convImage[i][j];
            }
            else if (j == width - 1)
            {
                energy[i][j] = min(convImage[i + 1][j - 1], convImage[i + 1][j]) + convImage[i][j];
            }
            else
            {
                energy[i][j] = min(convImage[i + 1][j - 1], min(convImage[i + 1][j], convImage[i + 1][j + 1])) + convImage[i][j];
            }
        }
    }
}

void SeamCarving::CalculatePath()
{
    int index = 0;
    float mini = energy[0][0];
    for (int i = 0; i < width; i++)
    {
        if (mini < energy[0][i])
        {
            mini = energy[0][i];
            index = i;
        }
    }
    path[0] = index;
    for (int i = 1; i < height; i++)
    {
        if (index == 0)
        {
            (energy[i][0] < energy[i][1]) ? index = 0 : index = 1;
            path[i] = index;
        }
        else if (index == width - 1)
        {
            (energy[i][width - 1] < energy[i][width - 2]) ? index = width - 1 : index = width - 2;
            path[i] = index;
        }
        else
        {
            if (energy[i][index - 1] < energy[i][index] && energy[i][index - 1] < energy[i][index + 1])
                index = index - 1;
            else if (energy[i][index] < energy[i][index - 1] && energy[i][index] < energy[i][index + 1])
                index = index;
            else
                index = index + 1;
            path[i] = index;
        }
    }
}

void SeamCarving::CarvePath(ImageReader &imread)
{
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < channels; k++)
        {
            matrix[(i * width) + path[i]][k] = -1;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = path[i]; j < width - 1; j++)
        {
            energy[i][j] = energy[i][j + 1];
        }
    }

    int index = 0;
    for (int i = 0; i < height * width; i++)
    {
        if (matrix[i][0] == -1)
            continue;
        else
        {
            for (int k = 0; k < channels; k++)
            {
                matrix[index][k] = matrix[i][k];
            }
            index++;
        }
    }

    for (int i = 0; i < height; i++)
    {
        delete[] matrix[(height * width) - 1 - i];
    }

    imread.width--;
    width--;
}

void SeamCarving::fit(ImageReader &imread, int n_pixels)
{

    for (int i = 0; i < n_pixels; i++)
    {
        Convolution();
        CalculateEnergy();
        CalculatePath();
        CarvePath(imread);
    }
}

SeamCarving::~SeamCarving()
{
    for (int i = 0; i < height; i++)
        delete[] convImage[i];
    delete[] convImage;

    for (int i = 0; i < height; i++)
        delete[] energy[i];
    delete[] energy;

    delete[] path;
}

#endif