#ifndef BATCHCOMPRESSOR_HPP
#define BATCHCOMPRESSOR_HPP

#include <iostream>
#include <string>
#include "filesystem.hpp"
#include "ImageRead.hpp"
#include "ImageWrite.hpp"
#include "KMeans.hpp"
#include "Normalizer.hpp"
using namespace std;
namespace fs = std::filesystem;

class BatchCompressor
{

private:
    string input_dir;
    string output_dir;
    string output_format;
    int clusters;
    int n_iterations;
    bool normalize;
    inline bool ends_with(string, string);
    bool replace(string &, const string &, const string &);

public:
    BatchCompressor(string, string, int, string, int, bool);
    void process();
};

BatchCompressor::BatchCompressor(string input_dir, string output_dir, int clusters, string output_format = "png", int n_iterations = 10, bool normalize = false)
{
    this->input_dir = input_dir;
    this->output_dir = output_dir;
    this->output_format = output_format;
    this->clusters = clusters;
    this->n_iterations = n_iterations;
    this->normalize = normalize;
}

bool BatchCompressor::ends_with(string value, string ending)
{
    if (ending.size() > value.size())
        return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

bool BatchCompressor::replace(string &str, const string &from, const string &to)
{
    size_t start_pos = str.find(from);
    if (start_pos == string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

void BatchCompressor::process()
{
    string path;
    if (filesystem::create_directory(output_dir))
    {
        for (auto &img : fs::directory_iterator(input_dir))
        {
            path = img.path().string();
            if (ends_with(path, "png") || ends_with(path, "jpg") || ends_with(path, "jpeg") || ends_with(path, "tga") || ends_with(path, "bmp"))
            {
                ImageReader imread((char *)path.c_str(), 3);
                if (normalize)
                {
                    Normalizer normalizer(imread.matrix, imread.height, imread.width, imread.channels);
                    normalizer.normalize();
                    KMeans model(clusters, imread.matrix, imread.height, imread.width, imread.channels);
                    model.fit(n_iterations);
                    replace(path, input_dir, "");
                    string output_path = output_dir + path;
                    normalizer.denormalize();
                    ImageWriter imsave((char *)output_path.c_str(), imread.width, imread.height, imread.channels, imread.matrix);
                    imsave.save();
                }
                else
                {
                    KMeans model(clusters, imread.matrix, imread.height, imread.width, imread.channels);
                    model.fit(n_iterations);
                    replace(path, input_dir, "");
                    string output_path = output_dir + path;
                    ImageWriter imsave((char *)output_path.c_str(), imread.width, imread.height, imread.channels, imread.matrix);
                    imsave.save();
                }
            }
        }
    }
}

#endif