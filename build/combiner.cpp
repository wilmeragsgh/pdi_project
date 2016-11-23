#include <Rcpp.h>
#include <fstream>
#include <string>
#include <stdlib.h>  
#include <stdio.h>  
#include <math.h>  
#include <opencv2/opencv.hpp>  
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
// [[Rcpp::export]]
RcppExport SEXP combineFB(SEXP f1,SEXP f2) {
  std::string foreground_file = Rcpp::as<std::string>(f1); 
  std::string background_file = Rcpp::as<std::string>(f2); 
  std::string mask ("/home/explicarte/Downloads/backup/UCV/Proyecto/pdi_project/foreground_mask.jpg");
  cv::Mat img_mask,foreground,background;
  img_mask = cv::imread(mask);
  foreground = cv::imread(foreground_file);
  background = cv::imread(background_file);
  cv::Mat output(background.size(),CV_8UC3,cv::Scalar(255,255,255));
  std::string outputname = ("combined_image.jpg");
  foreground.copyTo(output,img_mask);
  background.copyTo(output,~img_mask);
  imwrite(outputname, output);    
  //cvShowImage("mainWin", img );  
  //cvWaitKey(0);  
  //cvReleaseImage( &img );  
  Rcpp::CharacterVector rline = Rcpp::wrap(outputname);
  return rline;
}
