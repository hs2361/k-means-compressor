#include <bits/stdc++.h>
#include "ImageRead.hpp"
#include "ImageWrite.hpp"
using namespace std;

int main() {
    ImageReader imread("image.png",1);
    ImageWriter imsave("image2.png", 10, 10, 1, imread.matrix);
    return 0;
}