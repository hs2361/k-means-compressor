#include <iostream>
#include <filesystem>
#include "BatchCompressor.hpp"
using namespace std;

int main(){
    // using directory_iterator = filesystem::directory_iterator;
    // for (const auto& dirEntry : directory_iterator("/home/harsh/Pictures"))
    //  std::cout << dirEntry << std::endl;
    BatchCompressor batch("/home/harsh/Pictures/testing","/home/harsh/Pictures/compressed", 16);
    batch.compress();
    cout << "compressed\n";
    // cout << filesystem::create_directory("/home/harsh/test") << endl;
}
