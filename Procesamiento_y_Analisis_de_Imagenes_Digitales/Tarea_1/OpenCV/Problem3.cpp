#include <iostream>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;
namespace po = boost::program_options;

int main(int argc, const char* argv[]){
    po::options_description description("ImageShow Usage");
    description.add_options()
        ("help,h", "Display this help message")
        ("file,f", po::value<string>(), "Input image.")
        ("version,v", "Display the version number");

    po::positional_options_description p;
    p.add("file", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(description).positional(p).run(), vm);
    po::notify(vm);

    if(vm.count("help")){
        cout << description;

        return 0;
    }

    if(vm.count("version")){
        cout << "Image Show 1.0" << endl;

        return 0;
    }
    if(vm.count("file")){
        string file = vm["file"].as<string>();
        Mat image;
        image = imread(file, CV_LOAD_IMAGE_COLOR);   // Read the file

        if(! image.data )                              // Check for invalid input
        {
            cout <<  "Could not open or find the image" << std::endl ;
            return -1;
        }
        namedWindow( "Problema 3", WINDOW_AUTOSIZE );// Create a window to display.
        imshow( "Problema 3", image );                   // Show the image on the window.

        waitKey(0);  
        return 0;
    }

    return -1;
}
