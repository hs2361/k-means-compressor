#include <bits/stdc++.h>
#include "ImageRead.hpp"
#include "ImageWrite.hpp"
#include "KMeans.hpp"
using namespace std;

class BatchCompressor
{

private:
    string directory;
    string output_format;
    string output_dir;
    vector<string> images;
    int clusters;
    int iterations;
    inline bool ends_with(string, string);
    bool replace(string &, const string &, const string &);

public:
    BatchCompressor(string, string, int, string, int);
    void compress();
};

BatchCompressor::BatchCompressor(string directory, string output_dir, int clusters, string output_format = "png", int iterations = 10)
{
    this->directory = directory;
    this->output_format = output_format;
    this->output_dir = output_dir;
    this->clusters = clusters;
    this->iterations = iterations;
    filesystem::directory_iterator dir_traverser(directory);

    for (const auto &dirEntry : dir_traverser)
    {
        if (!dirEntry.is_directory())
        {
            if (ends_with(dirEntry.path(), "png") || ends_with(dirEntry.path(), "jpg") || ends_with(dirEntry.path(), "jpeg") || ends_with(dirEntry.path(), "tga") || ends_with(dirEntry.path(), "bmp"))
            {
                images.push_back(dirEntry.path());
            }
        }
    }
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

void BatchCompressor::compress()
{
    if (filesystem::create_directory(output_dir))
    {
        for (string img : images)
        {
            ImageReader reader((char *)img.c_str(), 3);
            KMeans model(clusters, reader.matrix, reader.height, reader.width, reader.channels);

            for (int i = 0; i < iterations; i++)
            {
                model.computeClosestCentroid();
                model.computeCentroids();
            }
            model.assignCentroids();
            replace(img, directory, "");
            cout << (char *)(output_dir + img).c_str() << endl;
            ImageWriter writer((char *)(output_dir + img).c_str(), reader.width, reader.height, reader.channels, model.matrix);
            // ImageWriter writer((char *)(output_dir + img).c_str(), reader.width, reader.height, reader.channels, model.matrix);
            writer.save();
        }
    }
    else
    {
        cout << "Failed to create directory\n";
    }
}
