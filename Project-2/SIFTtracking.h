/** 
 * \file   SIFTtracking.h
 *         Contains class SIFTtracking which tracks an object using 
 *		   SIFT to locate the features and FLANN to asociate them,
 *		   then it gets the homography of the image to project points.
 * \author Malcolm Davis, Miguel Taylor
 * \date   27.6.2017
 */

#ifndef SIFT_TRACKING
#define SIFT_TRACKING

#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>
#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>

/**
 * Tracking algorithm using SIFT and FLANN
 */
class SIFTtracking {
public:
  /**
   * Default constructor
   */
  SIFTtracking();

  /**
   * The execution method
   */
  int operator()(int argc,char *argv[]);

  
protected:
  /**
   * Default configuration file name
   */
  static const char *const defaultConfigFile_;

  /**
   * Configuration file name
   */
  std::string configurationFile_;

  /**
   * Train image.
   *
   * This attribute contains the name of the input image
   */
  std::string trainImage_;

  /**
   * Mask suffix
   *
   * The mask for trainImage_, a corresponding mask is searched
   * which will have this suffix appended.
   */
  std::string maskSuffix_;
  
  /**
  * Number of features
  *
  * The number of features to look up on the image
  */
  int nfeatures_;
  
  /**
  * Number of octave layers
  *
  * The number of octave layers used on the scale domain
  * each octave octave layer contains the image filtered by 5 different Gaussians
  */
  int nOctaveLayers_;
  
  /**
  * Contrast Threshold
  *
  * The threshold used to ignore points that have not enough contrast
  * It should be reduced on low illumination enviroments
  */
  double contrastThreshold_;
  
  /**
  * Edge Threshold
  *
  * The threshold used to ignore points that are part of edges
  */
  double edgeThreshold_;
  
  /**
  * Sigma
  *
  * The sigma used on the filters
  */
  double sigma_;

  /**
   * Get the name of the mask file, given the image file
   */
  std::string getMaskName(const std::string& imgName) const;

private:
  /**
   * Print the usage of this example.
   */
  void usage(int argc,char *argv[]);

  /**
   * Parse the commands
   */
  bool parse(int argc,char *argv[]);
  
  /**
   * Start the tracking using SIFT and FLANN
   */
  int track();
};


#endif
