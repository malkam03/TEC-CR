#include <ltiViewer2D.h>
#include "ltiIOBMP.h"
#include <iostream>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

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

        lti::ioBMP loader;
        lti::image img;
        if(loader.load(file,img)){
          lti::viewer2D view1;
          view1.show(img);  
          getchar();
        }else{
          cout << "The image "<<file <<" cannot be found." << endl;
          return -1;
        }
        return 0;
    }

    return -1;
}