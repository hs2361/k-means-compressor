#ifndef KMEANS_HPP
#define KMEANS_HPP

#include <iostream>
#include <cfloat>
#include <math.h>
#include <time.h>
using namespace std;

class KMeans
{
private:
    int height, width;
    unsigned int channels;
    float **matrix;
    int clusters;
    float **centroids;
    int *pixel_cluster_mapping;
    void computeClosestCentroid();
    void computeCentroids();
    void assignCentroids();

public:
    KMeans(int, float **, int, int, unsigned int);
    void showClusters();
    void fit(int);
    ~KMeans();
};

KMeans::KMeans(int clusters, float **matrix, int height, int width, unsigned int channels)
{

    int seed = time(0);
    srand(seed);

    this->clusters = clusters;
    this->matrix = matrix;
    this->height = height;
    this->width = width;
    this->channels = channels;

    centroids = new float *[clusters];
    for (int i = 0; i < clusters; i++)
    {
        centroids[i] = new float[channels];
    }

    for (int i = 0; i < clusters; i++)
    {
        int random = rand() % (height * width);
        for (int j = 0; j < channels; j++)
            centroids[i][j] = matrix[random][j];
    }

    pixel_cluster_mapping = new int[height * width];
    for (int i = 0; i < height * width; i++)
        pixel_cluster_mapping[i] = rand() % clusters;
}

void KMeans::showClusters()
{
    for (int i = 0; i < clusters; i++)
    {
        for (int j = 0; j < channels; j++)
            cout << centroids[i][j] << " ";
        cout << endl;
    }
}

void KMeans::computeClosestCentroid()
{

    for (int i = 0; i < height * width; i++)
    {
        int closestCentroid = pixel_cluster_mapping[i];
        float min_distance = FLT_MAX;
        float distance = min_distance;
        for (int j = 0; j < clusters; j++)
        {
            for (int k = 0; k < channels; k++)
            {
                distance += pow((matrix[i][k] - centroids[j][k]), 2);
            }
            distance = sqrt(distance);
            if (distance < min_distance)
            {
                min_distance = distance;
                closestCentroid = j;
            }
        }
        pixel_cluster_mapping[i] = closestCentroid;
    }
}

void KMeans::computeCentroids()
{

    for (int i = 0; i < clusters; i++)
    {
        for (int j = 0; j < channels; j++)
        {
            int newCoordinate = 0;
            int frequency = 0;
            for (int k = 0; k < height * width; k++)
            {
                if (pixel_cluster_mapping[k] == i)
                {
                    frequency++;
                    newCoordinate += matrix[k][j];
                }
            }
            if (frequency != 0)
            {
                newCoordinate = newCoordinate / frequency;
                centroids[i][j] = newCoordinate;
            }
        }
    }
}

void KMeans::assignCentroids()
{
    for (int i = 0; i < height * width; i++)
    {
        for (int j = 0; j < clusters; j++)
        {
            if (pixel_cluster_mapping[i] == j)
                for (int k = 0; k < channels; k++)
                {
                    matrix[i][k] = centroids[j][k];
                }
        }
    }
}

void KMeans::fit(int n_epochs)
{
    for (int i = 0; i < n_epochs; i++)
    {
        computeClosestCentroid();
        computeCentroids();
    }
    assignCentroids();
}

KMeans::~KMeans()
{

    for (int i = 0; i < clusters; i++)
    {
        delete[] centroids[i];
    }
    delete[] centroids;

    delete[] pixel_cluster_mapping;
}

#endif