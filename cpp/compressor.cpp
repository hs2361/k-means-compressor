#include <iostream>
#include <chrono>
#include "ImageRead.hpp"
#include "ImageWrite.hpp"
#include "ImageEdit.hpp"
#include "KMeans.hpp"
#include "BatchCompressor.hpp"
#include "SeamCarving.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "Usage:\n";
        cout << "Image Compression(-c):\n-i: Path to the input image\n-o: Path to the output image\n-cl: (Optional, default: 64) Number of clusters used for compression\n-n: (Optional) Normalize the image before compression\n-it: (Optional, default: 5) Number of epochs for k-means compression\n";
        cout << "\nBatch Compression (-b):\n-i: Path to the input directory\n-o: Path to the output directory\n-f: Format for output images\n-cl: (Optional, default: 64) Number of clusters used for compression\n-it: (Optional, default: 5) Number of epochs for k-means compression\n";
        cout << "\nSeam Carving (-s):\n-i: Path to the input image\n-o: Path to the output image\n-p: (Optional, default: 1) Percentage of width to be retained\n";
        cout << "\nImage editing (-e):\n-g: Convert to grayscale\n-h: Flip the image horizontally\n-v: Flip the image vertically\n-i: Path to the input image\n-o: Path to the output image\n";
    }

    else
    {
        string input_path, output_path, format;
        bool single = false, batch = false, normalize = false, edit = false, seam_carve = false, horizontal_flip = false, vertical_flip = false, grayscale = false;
        int clusters = 64, epochs = 5;
        float retention = 1;

        for (int i = 0; i < argc; i++)
        {
            string arg = string(argv[i]);
            if (arg == "-c")
            {
                single = true;
            }
            if (arg == "-i")
            {
                input_path = argv[i + 1];
            }
            if (arg == "-o")
            {
                output_path = argv[i + 1];
            }
            if (arg == "-f")
            {
                format = argv[i + 1];
            }
            if (arg == "-b")
            {
                batch = true;
            }
            if (arg == "-n")
            {
                normalize = true;
            }
            if (arg == "-cl")
            {
                clusters = atoi(argv[i + 1]);
            }
            if (arg == "-it")
            {
                epochs = atoi(argv[i + 1]);
            }
            if (arg == "-e")
            {
                edit = true;
            }
            if (arg == "-s")
            {
                seam_carve = true;
            }
            if (arg == "-p")
            {
                retention = atof(argv[i + 1]);
            }
            if (arg == "-g")
            {
                grayscale = true;
            }
            if (arg == "-h")
            {
                horizontal_flip = true;
            }
            if (arg == "-v")
            {
                vertical_flip = true;
            }
        }

        if (edit)
        {
            if (input_path == "" || output_path == "" || (!grayscale && !horizontal_flip && !vertical_flip))
            {
                cout << "\nImage editing (-e):\n-g: Convert to grayscale\n-h: Flip the image horizontally\n-v: Flip the image vertically\n-i: Path to the input image\n-o: Path to the output image\n";
                return 0;
            }

            ImageReader imread((char *)input_path.c_str(), 3);
            ImageEdit editor(imread.matrix, imread.height, imread.width, imread.channels);
            if (grayscale)
                editor.RGB2GRAY(imread);
            if (horizontal_flip)
                editor.horizontalFlip(imread);
            if (vertical_flip)
                editor.verticalFlip(imread);
            ImageWriter writer((char *)output_path.c_str(), imread.width, imread.height, imread.channels, imread.matrix);
            writer.save();
        }
        if (seam_carve)
        {
            if (input_path == "" || output_path == "")
                cout << "\nSeam Carving (-s):\n-i: Path to the input image\n-o: Path to the output image\n-p: (Optional, default: 1) Percentage of width to be retained";
            ImageReader imread((char *)input_path.c_str(), 3);
            SeamCarving carver(imread.matrix, imread.height, imread.width, imread.channels);
            carver.fit(imread, (int)(imread.width * (1.0 - retention)));
            ImageWriter writer((char *)output_path.c_str(), imread.width, imread.height, imread.channels, imread.matrix);
            writer.save();
        }
        if (batch)
        {
            if (input_path == "" || output_path == "" || format == "")
                cout << "\nBatch Compression (-b):\n-i: Path to the input directory\n-o: Path to the output directory\n-f: Format for output images\n-c: (Optional, default: 128) Number of clusters used for compression\n-it: (Optional, default: 15) Number of epochs for k-means compression\n";
            BatchCompressor compressor(input_path, output_path, clusters, format, epochs, normalize);
            compressor.process();
        }
        else if (single)
        {
            ImageReader imread((char *)input_path.c_str(), 3);
            auto start = chrono::high_resolution_clock::now();
            chrono::_V2::system_clock::time_point stop;
            if (normalize)
            {
                Normalizer normalizer(imread.matrix, imread.height, imread.width, imread.channels);
                normalizer.normalize();
                KMeans compressor(clusters, imread.matrix, imread.height, imread.width, imread.channels);
                compressor.fit(epochs);
                normalizer.denormalize();
                stop = chrono::high_resolution_clock::now();
                ImageWriter writer((char *)output_path.c_str(), imread.width, imread.height, imread.channels, imread.matrix);
                writer.save();
            }
            else
            {
                KMeans compressor(clusters, imread.matrix, imread.height, imread.width, imread.channels);
                compressor.fit(epochs);
                stop = chrono::high_resolution_clock::now();
                ImageWriter writer((char *)output_path.c_str(), imread.width, imread.height, imread.channels, imread.matrix);
                writer.save();
            }
            auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
            std::cout << duration.count() / pow(10, 6) << "s to compress the image" << endl;
        }
    }
}
