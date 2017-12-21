/*  C++ code for generating the Campbell-Robson CSF image.

This algorhtim generates one image in linear scale with the C(cols,rows)
function, and another image in logarithmic scale with the Cl(cols,rowas)
function.

*/
#include "grapher.cpp"
#include <iostream>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>       /* sqrt, sin, log, exp */

using namespace cv;
using namespace std;
namespace po = boost::program_options;

// precalculated constant = sqrt(2)*pi
#define sqrt2pi 4.442882938

//computes a sinusoidal function with variable frecuency
//given by: f = 1 / sqrt(2x)
double s( double x, int cols);

//computes a linear function with m = 127/(rows-1) and b = 0
double a( double y, int rows);

//creates the linear scale image given by:
//C(x) = s(x)*a(y)+128
Mat C( int cols, int rows);

//changes the linear varible x to a logarithmic scale
// f(x) = k*exp(alfa*x)
// f(0)	= fmax = k
// f(R-1) =	R-1 
double f( int x, int R);

//Shows a row of a channel
std::vector<int> channelRow(Mat *pChannel, int pRow);

//creates the logarithmic scale image given by:
//C(x) = s(f(x))*a(f(y))+128
Mat Cl( int cols, int rows);

int main (int argc, const char* argv[])
{
	int cols = 512;
	int rows = 512;
  int row;
  po::options_description description("ImageShow Usage");
  description.add_options()
      ("help,h", "Display this help message")
      ("rows,r", po::value<int>(), "Rows size.")
      ("cols,c", po::value<int>(), "Cols size.")
      ("showrow,x", po::value<int>(), "Show row.")
      ("lineal,l", "Lineal scale.");

  po::positional_options_description p;
  p.add("file", -1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv).options(description).positional(p).run(), vm);
  po::notify(vm);

  if(vm.count("help")){
    cout << description;
    return 0;
  }
  if(vm.count("rows")){
    rows = vm["rows"].as<int>();
  }
  if(vm.count("cols")){
    cols = vm["cols"].as<int>();
  }
  if(vm.count("lineal")){
    namedWindow( "lin", WINDOW_AUTOSIZE );
    imshow( "lin", C(cols,rows) );
    waitKey(0);
    return 0;
  }
  if(vm.count("showrow")){
    Mat tmp= Cl(cols,rows);
    row = vm["showrow"].as<int>();
    grapher<int> graph((int)cols/2+10,5,(int)cols/2+10, 128);
    std::vector<std::vector <int> > posiciones(1, std::vector<int>(cols));
    for(int i = 0; i< cols; i++){
        posiciones[0][i] = i;
    }
    std::vector<std::vector <int> > frecuencias;
    std::vector<std::string> titulo;
    frecuencias.push_back(channelRow(&tmp,row));
    titulo.push_back("Fila");
    std::cout << "todo bien" << std::endl;
    graph(&posiciones, &frecuencias, &titulo);
    waitKey(0);
    return 0;
  }

//linear scale image
  //logarithmic scale image 
  namedWindow( "log", WINDOW_AUTOSIZE );
  imshow( "log", Cl(cols,rows) );
  waitKey(0);
  return 0;
}

// x : input value
// cols : maximum value / number of columns
double s( double x, int cols){
  double correct = 0.125;
	return sin (sqrt2pi * sqrt((cols-1)+correct-x));
}

// y : input value
// rows : maximum value / number of rows
double a( double y, int rows){
	return 127.0/(rows-1)*y;
}

// cols : number of desired columns on the output image
// rows : number of desired rows on the output image
Mat C( int cols, int rows){
	Mat image(rows, cols, CV_8UC1, Scalar(0));
  	for(int x=0;x<cols;x++){
  		for(int y=0;y<rows;y++){
  			image.at<uint8_t>(y,x) = (uint8_t) (s(x,cols)*a(y,rows)+128);
  		}
  	}
  	return image;
}

// x : input value
// R : maximum value
// k : maximum frequency
double f( int x, int R){
	double k = 10;
	double alfa = log(pow((double)(R-1)/k,(double)1/(R-1)));
	return k*exp(alfa*x);
}

// cols : number of desired colums on the output image
// rows : number of desired rows on the output image
Mat Cl( int cols, int rows){
	Mat image(rows, cols, CV_8UC1, Scalar(0));
  	for(int x=0;x<cols;x++){
  		for(int y=0;y<rows;y++){
  			image.at<uint8_t>(y,x) = (uint8_t) (s(f(x,cols),cols)*a(f(y,rows),rows)+128);
  		}
  	}
  	return image;
}

/**
*
* @param pChannel mat with the image
* @param pRow
*/
std::vector<int> channelRow(Mat *pChannel, int pRow){
  std::vector<int> fondo (pChannel->cols, 0);
  for(unsigned i = 0; i< pChannel->cols; i++){
    fondo.at(i)=(int)pChannel->at<uchar>(pRow, i);
  }
  return fondo;
}
