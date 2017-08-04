 //#include <ltiViewer2D.h>
//#include <ltiIOImage.h>
//#include <ltiImage.h>
#include <ltiTimer.h> 			//timer::start() timer::stop()
#include <ltiConvolution.h> 	//convolution()
#include <ltiChannel.h> 		//channel() 
#include <ltiGaussKernels.h>	//gaussKernel2D()
#include <ltiOctagonalKernel.h>	//octagonalKernel()
#include <ltiBoundaryExpansion.h> //boundaryExpansion()
#include "ltiFFT.h"
#include "ltiIFFT.h"
#include <fstream>
#include <iostream>
#include <math.h>
using namespace std;

void savedata(double** data, int x, int y, const char* filename)
{
    ofstream out(filename);
    out<<filename<<"= ["<<endl;
    for(int i=0; i<x; i++)
    {
    	for(int j=0; j<y; j++){
    		out<<data[i][j]<<" ";
    	}
        out<<";"<<endl;
    }
    out<<"];"<<endl;
    out<<"mesh("<<filename<<");"<<endl;
    out <<"pause();"<< endl;
    out.close();
}

/**
* Method to filter the image on the frecuency and time domain.
* @cols 
*/
void filterimage (int cols, int rows, int ksize, bool type, bool domain){
	// the channel to be filtered:
	lti::channel data(rows,cols);
	lti::convolution filter;                        // convolution operator
	lti::convolution::parameters param;             // parameters
	int padWidth =10;
	//Time domain
	if(domain){
		if(type){//gauss filter(separable)
			lti::gaussKernel2D<float> kernel(ksize,((ksize+2)/6)^2);
			param.setKernel(kernel);                        // use the gauss kernel
		}else{//octagonal filter(no separable)
			lti::octagonalKernel<float> kernel(ksize,((ksize+2)/6)^2);
			param.setKernel(kernel);                        // use the gauss kernel
		}
		filter.setParameters(param);                    // use given parameters
		// filter the channel and leave the result there too
		filter.apply(data);
	}else{//Frecuency domain
		lti::boundaryExpansion padding(padWidth);
		lti::fft fft2d;     // for 2-dimensional FFT
		lti::ifft ifft2d;   // for 2-dimensional inverse FFT
		lti::fft::parameters par2d;
		lti::channel re,im,origRe,origIm, multi;
		lti::ifft::parameters ipar2d;
		lti::channel origData(data);
		par2d.mode = lti::Polar;
		ifft2d.setParameters(par2d);
		fft2d.setParameters(par2d);
		if(type){//gauss filter(separable)
			lti::gaussKernel2D<float> kernel(ksize,((ksize+2)/6)^2);
			param.setKernel(kernel);                        // use the gauss kernel
		}else{//octagonal filter(no separable)
			lti::octagonalKernel<float> kernel(ksize,((ksize+2)/6)^2);
			param.setKernel(kernel);                        // use the gauss kernel
		}
		filter.setParameters(param);                    // use given parameters
		// filter the channel and leave the result there too
		filter.apply(data);
		padding.apply(data);
		fft2d.apply(origData, origRe, origIm);
		fft2d.apply(data, re, im);
		for(int i = 0; i< rows;i++ ){
			for(int j = 0; j< cols;j++ ){
				origData[i][j]=sqrt(pow(origRe[i][j], 2) + pow(origIm[i][j], 2));
				data[i][j]=sqrt(pow(re[i][j], 2) + pow(im[i][j], 2));
			}
		}
		multi.emultiply(data, origData);
		ifft2d.apply(re, im, data);   // inverse FFT
		ifft2d.apply(origRe, origIm, origData);   // inverse FFT
		padding = lti::boundaryExpansion(-padWidth);
		padding.apply(data);
	}
}

int main(int argc, char** argv)
{
    lti::timer time;   
    double timeacc; 
    double **times;
    times = new double*[10];
	for (int i=0; i<10; i++){
		times[i] = new double[10];
	}
    for(int i=0; i<10; i++){
    	int cols = 64*exp(0.3779108202*i);
    	int rows = 48*exp(0.3459461455*i);
		for(int j=0; j<10;j++){
			int ksize = 2*ceil(exp(0.6929299545*j))+1;
			int nmax = round(20*exp(-0.02842697646*i*j));
			timeacc = 0;
			cout <<"image: "<<cols<<"x"<<rows<<"    kernel: "<<ksize<<"x"<<ksize<<endl;
			for(int n=0; n<nmax; n++){
				time.start();
				//filtering
				filterimage(cols,rows,ksize, true, false);
				time.stop();	
				timeacc += time.getTime();
				cout<<n<<endl;
			}
			times[i][j] = timeacc/nmax;
		}
    }
    savedata(times, 10,10, (const char*)"nonseparableF.m");
    for (int i=0; i<10; i++) {
		delete [] times[i];
	}
	delete [] times;
} 	 
