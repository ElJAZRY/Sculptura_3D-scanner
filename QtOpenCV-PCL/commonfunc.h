#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<vector>
#include <opencv2/features2d.hpp>
#include <opencv2/features2d/features2d.hpp>
#include<iostream>
// Feature detection function headers
#include <opencv2/features2d/features2d.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>
#include<opencv2/xfeatures2d.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/features2d/features2d.hpp>






#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/PolygonMesh.h>



class commonFunc
{
public:
  commonFunc();

  // defining non-static functions
  void dispDepthColor(cv::Mat &depthMap, cv::Mat &depthColor);
  void dispDepthGray(cv::Mat &depthMap, cv::Mat &depthGray);

  // defining a static function
  static void static_dispDepthGray(cv::Mat &depthMap, cv::Mat &depthGray)
  {
    cv::normalize(depthMap, depthGray, 0, 255, CV_MINMAX);
    depthGray.convertTo(depthGray, CV_8UC3);
  }

  ////////////////////////////////////////////////////////////////
  //////////////// Opencv Image Processing Functions /////////////
  ////////////////////////////////////////////////////////////////
  // Convert color image to gray scale image
  void rgb2gray(cv::Mat &rgbImg, cv::Mat &grayImg);

  // Flip image left and right
  void flipImage(cv::Mat &rgbImg);


  // Detect feature points on image
  void featureExtraction(cv::Mat &rgbImg, std::vector<cv::KeyPoint> &keyPts);

  // Show detected keypoints on the color image
  void showKeyPoints(cv::Mat &rgbImg, std::vector<cv::KeyPoint> &keyPts);

  // Detect and match features between two images
  void featureMatching(cv::Mat &rgbImg01, std::vector<cv::KeyPoint> &keyPts01,
                       cv::Mat &rgbImg02, std::vector<cv::KeyPoint> &keyPts02,
                       std::vector< cv::DMatch > *matches, bool robustMatch = false);

  // Draw the feature matches
  void showFeatureMatches(cv::Mat &rgb_1, std::vector<cv::KeyPoint> &keyPts_1,
                          cv::Mat &rgb_2, std::vector<cv::KeyPoint> &keyPts_2,
                          std::vector< cv::DMatch > *matches);




  // Save detected features
  void saveFeatures(const cv::Mat &rgb_1, const cv::Mat &depth_1, std::vector<cv::KeyPoint> &keyPts_1,
                    const cv::Mat &rgb_2, const cv::Mat &depth_2, std::vector<cv::KeyPoint> &keyPts_2,
                    std::vector< cv::DMatch > *matches);

  // Convert uint8 depth to meters
  void depth2meter(const float feat_x, const float feat_y, const float rawDisparity,
                   float &x, float &y, float &z);
  void myDepth2meter(const float feat_x, const float feat_y, const float rawDisparity,
                   float &x, float &y, float &z);

  // Convert rgb + depth images to colored point clouds
  void rgbd2pointcloud(const cv::Mat &rgbImg, const cv::Mat &depthImg, const std::string &fileName);

  pcl::PointCloud<pcl::PointXYZRGB>::Ptr rgbd2pcl(const cv::Mat &rgbImg, const cv::Mat &depthImg);
};

#endif // COMMONFUNC_H
