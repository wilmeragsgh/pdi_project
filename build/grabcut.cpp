#include <Rcpp.h>
#include <fstream>
#include <string>
#include <stdlib.h>  
#include <stdio.h>  
#include <math.h>  
#include <opencv2/opencv.hpp>  
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

// [[Rcpp::export]]
RcppExport SEXP grabcut(SEXP f1, int minx, int miny, int maxx, int maxy) {
    std::string fname = Rcpp::as<std::string>(f1); 
    std::ifstream fi;
    fi.open(fname.c_str(),std::ios::in);
    cv::Mat img;  
    // Load image   
    img=cv::imread(fname.c_str());  
    if(!img.data)  
    {  
        printf("Could not load image file\n");  
        exit(0);  
    } 

    cv::Rect rectangle(4,4,4,4);

    cv::Mat result;
    cv::Mat bgModel,fgModel;

    cv::grabCut(img,    // input image
        result,   // segmentation result
        rectangle,// rectangle containing foreground 
        bgModel,fgModel, // models
        1,        // number of iterations
        cv::GC_INIT_WITH_RECT);   

    cv::compare(result,cv::GC_PR_FGD,result,cv::CMP_EQ);
    // Generate output image
    cv::Mat foreground(img.size(),CV_8UC3,cv::Scalar(255,255,255));
    img.copyTo(foreground,result); // bg pixels not copied
    unsigned sz = fname.size();
    //fname.resize(sz-4); // removin .bmp from the name to add transformation file
    std::string transformName ("grabcut_");
    //std::string formatName (".bmp");
    std::string outputname = transformName + fname.c_str();
    cv::imwrite("/home/explicarte/outputname.jpg", foreground);    
    //cvShowImage("mainWin", img );  
    //cvWaitKey(0);  
    //cvReleaseImage( &img );  
    Rcpp::CharacterVector rline = Rcpp::wrap(outputname);
    return rline;
}
