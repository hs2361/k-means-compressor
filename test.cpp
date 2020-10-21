#include <bits/stdc++.h>
#include "ImageRead.hpp"
#include "ImageWrite.hpp"
#include "KMeans.hpp"
using namespace std;

int main() {
    ImageReader imread("image.png",3);
    cout<<imread.width<<" "<<imread.height<<endl;
    KMeans model(16, imread.matrix, imread.height, imread.width, imread.channels);
    int ITERATIONS = 20;
    model.fit(ITERATIONS);
    ImageWriter imsave("image2.png", imread.width, imread.height, imread.channels, imread.matrix);
    imsave.save();
    return 0;
}