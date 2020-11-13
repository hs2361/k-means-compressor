#include <bits/stdc++.h>
#include <chrono>
#include "ImageRead.hpp"
#include "ImageWrite.hpp"
#include "ImageEdit.hpp"
#include "KMeans.hpp"
#include "Normalizer.hpp"
using namespace std;

int main()
{
    ImageReader imread("image2.png", 3);
    Normalizer normalizer(imread.matrix, imread.height, imread.width, imread.channels);
    normalizer.normalize();
    // ImageEdit edit(imread.matrix, imread.height, imread.width, imread.channels);
    // edit.horizontalFlip(imread);
    KMeans model(64, imread.matrix, imread.height, imread.width, imread.channels);
    int ITERATIONS = 5;
    auto start = chrono::high_resolution_clock::now();
    model.fit(ITERATIONS);
    model.showClusters();

    auto stop = chrono::high_resolution_clock::now();
    normalizer.denormalize();
    ImageWriter imsave("image3.png", imread.width, imread.height, imread.channels, imread.matrix);
    imsave.save();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    std::cout << duration.count()/pow(10,6) << "s to compress the image" << endl;
    return 0;
}