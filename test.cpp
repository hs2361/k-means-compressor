#include <bits/stdc++.h>
#include <chrono>
#include "ImageRead.hpp"
#include "ImageWrite.hpp"
#include "ImageEdit.hpp"
#include "KMeans.hpp"
using namespace std;

int main()
{
    ImageReader imread("image.jpg", 3);
    ImageEdit edit(imread.matrix, imread.height, imread.width, imread.channels);
    edit.HorizontalFlip(imread);
    // KMeans model(256, imread.matrix, imread.height, imread.width, imread.channels);
    // int ITERATIONS = 20;
    // auto start = chrono::high_resolution_clock::now();
    // model.fit(ITERATIONS);
    // auto stop = chrono::high_resolution_clock::now();
    ImageWriter imsave("image2.png", imread.width, imread.height, imread.channels, imread.matrix);
    imsave.save();
    // auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    // std::cout << duration.count()/pow(10,6) << "s to compress the image" << endl;
    // return 0;
}