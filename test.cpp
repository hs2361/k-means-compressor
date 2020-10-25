#include <bits/stdc++.h>
#include <chrono>
#include "ImageRead.hpp"
#include "ImageWrite.hpp"
#include "KMeans.hpp"
using namespace std;

int main()
{
    ImageReader imread("image.png", 3);
    KMeans model(256, imread.matrix, imread.height, imread.width, imread.channels);
    int ITERATIONS = 20;
    auto start = chrono::high_resolution_clock::now();
    model.fit(ITERATIONS);
    auto stop = chrono::high_resolution_clock::now();
    ImageWriter imsave("image2.png", imread.width, imread.height, imread.channels, model.matrix);
    imsave.save();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    std::cout << duration.count()/pow(10,6) << "s to compress the image" << endl;
    return 0;
}