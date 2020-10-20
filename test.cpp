#include <bits/stdc++.h>
#include "ImageRead.hpp"
#include "ImageWrite.hpp"
#include "KMeans.hpp"
using namespace std;

int main() {
    ImageReader imread("image.png",3);
    cout<<imread.width<<" "<<imread.height<<endl;
    KMeans model(256, imread.matrix, imread.height, imread.width, imread.channels);
    int ITERATIONS = 20;
    for(int i=0; i<ITERATIONS; i++) {
        model.computeClosestCentroid();
        model.computeCentroids();
    }
    model.assignCentroids();
    ImageWriter imsave("image2.png", imread.width, imread.height, imread.channels, model.matrix);
    imsave.save();
    return 0;
}