/** 
 * \file   SIFTtracking.cpp
 *         Contains an tracker for the use of the class
 * \author Malcolm Davis, Miguel Taylor
 * \date   27.6.2017
 */
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv/cv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <sstream> 
#include <iostream>
#include <fstream> 
#include <stdio.h>
#include "SIFTtracking.h"


int main( int argc, char** argv )
{
	
	int nFeatures, nOctaves;
	double contrastThreshold, edgeThreshold, sigma;
	nFeatures = 20;
	nOctaves = 3;
	contrastThreshold=0.04;
	edgeThreshold=10;
	sigma=1.6;
    if( argc != 1)
    {
     std::cout <<" Usage: run" << std::endl;
     return -1;
    }

    cv::Mat img1, img2, img1Temp, img2Temp, desc1, desc2, mask1, mask2;
    cv::SIFT filter(nFeatures, nOctaves, contrastThreshold, edgeThreshold, sigma);
    cv::FlannBasedMatcher matcher;
    int key=0;
    int framesPerSecond = 60;
    double max_dist; 
    double min_dist;
    bool track = false;
    cv::VideoCapture vid(0);
    if(!vid.isOpened())
    {
    	std::cout << "Error opening VideoCapture." << std::endl;
    	return 0;
    }
    while(true){
		if(!track){
			if(!vid.read(img1Temp)){
		    	std::cout << "Error opening VideoCapture." << std::endl;
				break;
			}
			else{
				cv::resize(img1Temp, img1, cv::Size(),  0.5, 0.5);
				cv::rectangle(img1,cv::Point(0,0),cv::Point(img1.cols ,1/5*img1.rows),cv::Scalar(0,0,0),CV_FILLED);
				cv::rectangle(img1,cv::Point(0,img1.rows-1/5*img1.rows),cv::Point(img1.cols ,img1.rows),cv::Scalar(0,0,0),CV_FILLED);
				cv::rectangle(img1,cv::Point(0,0),cv::Point(img1.cols*1/5 ,img1.rows),cv::Scalar(0,0,0),CV_FILLED);
				cv::rectangle(img1,cv::Point(img1.cols-img1.cols*1/5, 0),cv::Point(img1.cols ,img1.rows),cv::Scalar(0,0,0),CV_FILLED);
				cv::imshow( "Choose Object", img1 ); 
			}
		}else{
			if(!vid.read(img2Temp)){
				std::cout << "Error opening VideoCapture." << std::endl;
				break;
			}
			else{
				cv::resize(img2Temp, img2, cv::Size(), 0.5, 0.5);
			}
		}
	    if(img1.data && track)                              // Check for invalid input
	    {
	        cv::cvtColor(img1, mask1, CV_RGB2GRAY);
	        cv::cvtColor(img2, mask2, CV_RGB2GRAY);
			std::vector<cv::KeyPoint> keyPoints1, keyPoints2;
			std::vector< cv::DMatch > matches;
	       	filter(img1, mask1, keyPoints1, desc1);
	       	filter(img2, mask2, keyPoints2, desc2);
	       	matcher.match( desc1, desc2, matches );
	       	
	       	max_dist = 0;
	       	min_dist =100;

			//-- Quick calculation of max and min distances between keypoints
			for( int i = 0; i < desc1.rows; i++ )
			{ 
				  double dist = matches[i].distance;
				  if( dist < min_dist ) 
				  		min_dist = dist;
				  if( dist > max_dist ) 
				  		max_dist = dist;
			}
		  	//-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist,
		  	//-- or a small arbitary value ( 0.02 ) in the event that min_dist is very
		  	//-- small)
		  	//-- PS.- radiusMatch can also be used here.
		  	std::vector< cv::DMatch > good_matches;
		  	good_matches = matches;
		    for( int i = 0; i < desc1.rows; i++ )
		  	{ if( matches[i].distance <= std::max(2*min_dist, 0.02) )
		  	  { good_matches.push_back( matches[i]); }
		  	}

		  	//-- Draw only "good" matches
		  	cv::Mat img_matches;
		  	cv::drawMatches( img1, keyPoints1, img2, keyPoints2,
			good_matches, img_matches, cv::Scalar::all(-1), cv::Scalar::all(-1),
			std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

		  	/***************************/


		  	//-- Localize the object
		  	std::vector<cv::Point2f> obj;
		  	std::vector<cv::Point2f> scene;

		  	for( int i = 0; i < good_matches.size(); i++ )
		  	{
		  	  //-- Get the keypoints from the good matches
		  	  obj.push_back( keyPoints1[ good_matches[i].queryIdx ].pt );
		  	  scene.push_back( keyPoints1[ good_matches[i].trainIdx ].pt );
		  	}
		  	if (good_matches.size() >0 ){
			  	cv::Mat homog = cv::findHomography( obj, scene, 0 );

			  	//-- Get the corners from the image_1 ( the object to be "detected" )
			  	std::vector<cv::Point2f> obj_corners(4);
			  	obj_corners[0] = cvPoint(0,0); obj_corners[1] = cvPoint( img1.cols, 0 );
			  	obj_corners[2] = cvPoint( img1.cols, img1.rows ); obj_corners[3] = cvPoint( 0, img1.rows );
			  	std::vector<cv::Point2f> img2(4);

			  	cv::perspectiveTransform( obj_corners, img2, homog);

			  	//-- Draw lines between the corners (the mapped object in the scene - image_2 )
			  	cv::line(img_matches, img2[0] + cv::Point2f( img1.cols, 0), img2[1] + cv::Point2f( img1.cols, 0), cv::Scalar(0, 255, 0), 4 );
			  	cv::line(img_matches, img2[1] + cv::Point2f( img1.cols, 0), img2[2] + cv::Point2f( img1.cols, 0), cv::Scalar( 0, 255, 0), 4 );
			  	cv::line(img_matches, img2[2] + cv::Point2f( img1.cols, 0), img2[3] + cv::Point2f( img1.cols, 0), cv::Scalar( 0, 255, 0), 4 );
			  	cv::line(img_matches, img2[3] + cv::Point2f( img1.cols, 0), img2[0] + cv::Point2f( img1.cols, 0), cv::Scalar( 0, 255, 0), 4 );
			}


		  	//-- Show detected matches
		  	cv::imshow( "Object Tracking", img_matches );
	    }

	    key = (int)cv::waitKey(100/framesPerSecond)%256;
	    switch (key ){
		    case 27: //Esc key to stop
		    	return 0;
		    	break;
		    case  32: //space to aply the mask to the object
		    	track=true;
		    	mask1=img1;//Falta aplicar
		    	cv::destroyWindow("Choose Object");
		    	break;
		    case 116: //t to track a new object
		    	img1=cv::Scalar(255,255,255);
		    	track=false;
		    	cv::destroyWindow("Object Tracking");
		    	break;
		    
		}

	}                                          // Wait for a keystroke in the window
    return 0;
}


