#include <opencv2/opencv.hpp>
#include <sstream> 
#include <iostream>
#include <fstream> 

using namespace std;
using namespace cv;

const short calibraciondimensioncuadrado = 25; //milimetros
const Size dimensionestablero = Size(9,6); 




void drawAxes(cv::Mat &pImage, cv::InputArray pCameraMatrix, cv::InputArray pDistCoeffs,
    cv::InputArray pRvec, cv::InputArray pTvec, float pLength){
	// project axes
    std::vector< cv::Point3f > axisPoints;
    axisPoints.push_back(cv::Point3f(0, 0, 0));
    axisPoints.push_back(cv::Point3f(pLength, 0, 0));
    axisPoints.push_back(cv::Point3f(0, pLength, 0));
    axisPoints.push_back(cv::Point3f(0, 0, -pLength));
    std::vector< cv::Point2f > imagePoints;
    cv::projectPoints(axisPoints, pRvec, pTvec, pCameraMatrix, pDistCoeffs, imagePoints);
    // draw axes
    cv::line(pImage, imagePoints[0], imagePoints[1], cv::Scalar(0, 0, 255), 3);
    cv::line(pImage, imagePoints[0], imagePoints[2], cv::Scalar(0, 255, 0), 3);
    cv::line(pImage, imagePoints[0], imagePoints[3], cv::Scalar(255, 0, 0), 3);
}

int main (int argv, char** argc){
	cv::Mat frame, distanceCoefficients, rvec, tvec, cameraMatrix; 
	std::vector<cv::Point3d> objectPoints;
    for (int i = 0; i < dimensionestablero.height; i++) {
      for (int j = 0; j < dimensionestablero.width; j++) {
        objectPoints.push_back(cv::Point3d(double(j * calibraciondimensioncuadrado), float(i * calibraciondimensioncuadrado), 0));
      }
    }
	bool found, calibrated = false;
	cv::VideoCapture vid(0);
	if(!vid.isOpened())
	{
		std::cout << "Error opening VideoCapture." << std::endl;
		return 0;
	}
	//cargar calibracion
	cv::FileStorage fs("calibration_result.xml", cv::FileStorage::READ);
	if(fs.isOpened()){
		std::cout << "Loading calibration." << std::endl;
	    fs["Camera_Matrix"] >> cameraMatrix;
	    fs["Distortion_Coefficients"] >> distanceCoefficients;
	//	cv::solvePnP(objectPoints, foundPoints, cameraMatrix,distanceCoefficients, rvec, tvec);
		std::cout << "Calibration Loaded."<< std::endl; 
		calibrated=true;
	}else{
		std::cout << "File not found." << endl;
		return -1;
	}
	int framesPerSecond = 20;
	namedWindow("3DChessboard", CV_WINDOW_AUTOSIZE);
	std::cout << "Usage press:\n -l: to load calibration.\n -ESC: to exit."<< std::endl;
	while(true) {
		vector<Point2f> foundPoints;
		found = false;
		if(!vid.read(frame))
			break;
		found = findChessboardCorners(frame, dimensionestablero, foundPoints, CALIB_CB_FAST_CHECK );
		if(found && calibrated){
			cv::solvePnP(objectPoints, foundPoints, cameraMatrix,distanceCoefficients, rvec, tvec);
			//drawChessboardCorners(frame,dimensionestablero, foundPoints, found);
			drawAxes(frame,cameraMatrix,distanceCoefficients, rvec, tvec,3*calibraciondimensioncuadrado);
		}
		imshow("3DChessboard", frame);
		char character = waitKey(100/framesPerSecond);
		if( character==27){// ESC
			//salida
			std::cout << "Goodbye!" << std::endl;
			return 0;
			break;
		}		
	}
	return 0;
}
