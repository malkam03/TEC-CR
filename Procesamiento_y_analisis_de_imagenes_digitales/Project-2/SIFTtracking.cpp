/** 
 * \file   SIFTtracking.cpp
 *         Contains class SIFTtracking which tracks an object using 
 *		   SIFT to locate the features and FLANN to asociate them,
 *		   then it gets the homography of the image to project points.
 * \author Malcolm Davis, Miguel Taylor
 * \date   27.6.2017
 */

#include "SIFTtracking.h"

const char* const SIFTtracking::defaultConfigFile_ = "SIFTtracking.cfg";

SIFTtracking::SIFTtracking()
{
    // initialization of the attributes
    configurationFile_ = defaultConfigFile_;

    trainImage_ = "image.png";
    maskSuffix_ = "_mask";
    // parameters
    nfeatures_ = 0;
  	nOctaveLayers_ = 3;
  	contrastThreshold_ = 0.04;
  	edgeThreshold_ = 10.0;
  	sigma_ = 1.6;
    
}

void SIFTtracking::usage(int argc, char* argv[])
{
    std::cout << "\nUsage: " << argv[0]<< " [-c filename] [-h]\n\n";
    std::cout << "  -c Use the given filename instead of the default '"<< defaultConfigFile_ << "'\n";
    std::cout << "  -h Show this help\n";
    std::cout << "  \nWhile tracking on video:\n\n";
    std::cout << "  t Recapture the target image\n";
    std::cout << "  esc Stop the tracking\n"
    << std::endl;
}

bool SIFTtracking::parse(int argc, char* argv[])
{
    int i = 1;

    while (i < argc) {
        if (std::string(argv[i]) == "-c") {
            ++i;
            if (i < argc) {
                configurationFile_ = argv[i];
            }
            else {
                std::cout << "You must provide a valid configuration file name after -c" << std::endl;
                return false; // report error
            }
        }
        else if ((std::string(argv[i]) == "-h") || (std::string(argv[i]) == "--help")) {
            usage(argc, argv);
            return false;
        }
        else {
            std::cout << "Unrecognized option: " << std::string(argv[i]) << std::endl;
        }
        ++i;
    }
    return true;
}

int SIFTtracking::operator()(int argc, char* argv[])
{
	// Parse the command line parameters
    if (!parse(argc, argv)) {
        return EXIT_FAILURE;
    }

    libconfig::Config cfg;
    // Read the configuration file.
    try {
        cfg.readFile(configurationFile_.c_str());
    }
    catch (libconfig::FileIOException& exp) {
        //if the file doesn't exist, try to create it
        libconfig::Setting& root = cfg.getRoot();
        // Add settings to the configuration.
        root.add("trainImage", libconfig::Setting::TypeString) = trainImage_;
        root.add("maskSuffix", libconfig::Setting::TypeString) = maskSuffix_;
        libconfig::Setting& parameters = root.add("parameters", libconfig::Setting::TypeGroup);
        parameters.add("nfeatures", libconfig::Setting::TypeInt) = nfeatures_;
        parameters.add("nOctaveLayers", libconfig::Setting::TypeInt) = nOctaveLayers_;
        parameters.add("contrastThreshold", libconfig::Setting::TypeFloat) = contrastThreshold_;
        parameters.add("edgeThreshold", libconfig::Setting::TypeFloat) = edgeThreshold_;
        parameters.add("sigma", libconfig::Setting::TypeFloat) = sigma_;
        try {
            cfg.writeFile(configurationFile_.c_str());
            std::cerr << "New configuration successfully written to: " << configurationFile_.c_str() << std::endl;
        }
        catch (libconfig::FileIOException& exp) {
            std::cerr << "I/O error while writting file." << std::endl;
            return (EXIT_FAILURE);
        }
        try {
            cfg.readFile(configurationFile_.c_str());
        }
        catch (libconfig::FileIOException& exp) {
            std::cerr << "I/O error while reading file." << std::endl;
            return (EXIT_FAILURE);
        }
    }
    // Parse the configuration file
    catch (libconfig::ParseException& exp) {
        std::cerr << "Parse error at " << exp.getFile() << ":" << exp.getLine()
                  << " - " << exp.getError() << std::endl;
        return (EXIT_FAILURE);
    }
    // Read the configuration values
	libconfig::Setting& root = cfg.getRoot();
	libconfig::Setting& parameters = root["parameters"];
	if (!(
		cfg.lookupValue("trainImage", trainImage_)&&
		cfg.lookupValue("maskSuffix", maskSuffix_)&&
		parameters.lookupValue("nfeatures", nfeatures_)&&
		parameters.lookupValue("nOctaveLayers", nOctaveLayers_)&&
		parameters.lookupValue("contrastThreshold", contrastThreshold_)&&
		parameters.lookupValue("edgeThreshold", edgeThreshold_)&&
		parameters.lookupValue("sigma", sigma_)
	)) std::cerr << "There are parameters missing in the configuration file, default values loaded instead" << std::endl;

	//Start tracking
	track();
	
    return EXIT_SUCCESS;
}


int SIFTtracking::track()
{
    cv::Mat img1, img2, mask;
    cv::Mat desc1, desc2;
    cv::Mat gray1, gray2, maskGray;
    cv::SIFT filter;
    int key = 0;
    std::vector<cv::KeyPoint> keyPoints1, keyPoints2;
    bool track = true;

    cv::VideoCapture vid(0);
    img1 = cv::imread(trainImage_, CV_LOAD_IMAGE_COLOR); // Read the file
    mask = cv::imread(getMaskName(trainImage_), CV_LOAD_IMAGE_COLOR); // Read the mask
    cv::cvtColor(img1, gray1, CV_RGB2GRAY);

    if (!img1.data) // Check for invalid input
    {
        std::cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    if (!mask.data) // Check for invalid input
    {
        std::cout << "Could not open or find the mask" << std::endl;
        return -1;
    }

    int framesPerSecond = 30;
    if (!vid.isOpened()) {
        std::cout << "Error opening VideoCapture." << std::endl;
        return 0;
    }

    while (true) {
        if (!vid.read(img2))
            break;
        if(!track){
            cv::cvtColor(img1, gray1, CV_RGB2GRAY);
            if(!vid.read(img1))
                break; 
            //-- Show detected matches
            imshow("Choose Object", img1);
        }
        else{
            cv::cvtColor(img2, gray2, CV_RGB2GRAY);
            cv::cvtColor(mask, maskGray, CV_RGB2GRAY);
            

            // Apply the mask
            try {
                for (int i = 0; i < gray1.rows; i++) {
                    for (int j = 0; j < gray1.cols; j++) {
                        if ((int)maskGray.at<uchar>(i, j) == 255) {
                            continue;
                        }
                        else if ((int)maskGray.at<uchar>(i, j) == 0) {
                            gray1.at<uchar>(i, j) = (uchar) 0;
                        }
                        else {
                            std::cout << "Invalid mask value: "<< (int)maskGray.at<uchar>(i, j) <<" at "<<i<<","<<j<< std::endl;
                            //return -1;
                        }
                    }
                }
            }
            catch (...) {
                std::cout << "Invalid mask" << std::endl;
                return -1;
            }
            
            filter(img1, gray1, keyPoints1, desc1);
            filter(img2, gray2, keyPoints2, desc2);
            cv::drawKeypoints(img1, keyPoints1, img1);
            cv::drawKeypoints(img2, keyPoints2, img2);
            cv::FlannBasedMatcher matcher;
            std::vector<cv::DMatch> matches;
            matcher.match(desc1, desc2, matches);

            double max_dist = 0;
            double min_dist = 100;
            //-- Quick calculation of max and min distances between keypoints
            for (int i = 0; i < desc1.rows; i++) {
                double dist = matches[i].distance;
                if (dist < min_dist)
                    min_dist = dist;
                if (dist > max_dist)
                    max_dist = dist;
            }

            //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist,
            //-- or a small arbitary value ( 0.02 ) in the event that min_dist is very
            //-- small)
            //-- PS.- radiusMatch can also be used here.
            std::vector<cv::DMatch> good_matches;

            for (int i = 0; i < desc1.rows; i++) {
                if (matches[i].distance <= std::max(2.5* min_dist, 0.02)) {
                    good_matches.push_back(matches[i]);
                }
            }

            //-- Draw only "good" matches
            cv::Mat img_matches;
            drawMatches(gray1, keyPoints1, img2, keyPoints2,
                good_matches, img_matches, cv::Scalar::all(-1), cv::Scalar::all(-1),
                std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

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
            if (good_matches.size() >3 ){
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
            imshow("Object Tracking", img_matches);
        }
        key = cv::waitKey(100 / framesPerSecond);
        switch (key ){
            case 27: //Esc key to stop
                return 0;
                break;
            case  32: //space to aply the mask to the object
                track=true;
                cv::destroyWindow("Choose Object");
                break;
            case 116: //t to track a new object
                img1=cv::Scalar(255,255,255);
                track=false;
                cv::destroyWindow("Object Tracking");
                break;
            
        }
    } // Wait for a keystroke in the window
}


std::string SIFTtracking::getMaskName(const std::string& imgName) const
{
    std::string file(imgName);
    std::string::size_type pos = file.rfind('.');
    if (pos != std::string::npos) {
        file.insert(pos, maskSuffix_);
    }
    else {
        file += maskSuffix_;
    }
    return file;
}

int main(int argc, char* argv[])
{

    try {
        SIFTtracking obj;
        return obj(argc, argv);
    }
    catch (cv::Exception& exp) {
        std::cout << "An cv::Exception was thrown: ";
        std::cout << exp.what() << std::endl;
    }
    catch (std::exception& exp) {
        std::cout << "std::exception was thrown: ";
        std::cout << exp.what() << std::endl;
    }
    catch (...) {
        std::cout << "Unknown exception thrown!" << std::endl;
    }
    return EXIT_FAILURE;

} // main
