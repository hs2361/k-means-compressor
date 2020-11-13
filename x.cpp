#include <iostream>
#include <filesystem>
#include "BatchCompressor.hpp"
using namespace std;

int main()
{
    // using directory_iterator = filesystem::directory_iterator;
    // for (const auto& dirEntry : directory_iterator("/home/harsh/Pictures"))
    //  std::cout << dirEntry << std::endl;
    BatchCompressor batch("C:\\Users\\debad\\Desktop\\oopl-project\\test", "C:\\Users\\debad\\Desktop\\oopl-project\\testDest", 16, "png", 5);
    batch.process();
    cout << "compressed\n";
    // cout << filesystem::create_directory("/home/harsh/test") << endl;
}
