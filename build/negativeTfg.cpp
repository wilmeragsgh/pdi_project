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
RcppExport SEXP negativeTransformation1(SEXP f1,SEXP fb) {
    std::string fname = Rcpp::as<std::string>(f1); 
    std::ifstream fi;
    std::string mask;
    int fg = Rcpp::as<int >(fb);
    std::cout << fg;
    mask = "/home/explicarte/Downloads/backup/UCV/Proyecto/pdi_project/foreground_mask.jpg";
    cv::Mat img_mask;
    img_mask = cv::imread(mask);
    fi.open(fname.c_str(),std::ios::in);
    IplImage* img = 0;   
    int height,width,step,channels;  
    uchar *data;  
    int i,j,k;  
    // Load image   
    img=cvLoadImage(fname.c_str(),-1);  
    if(!img)  
    {  
        printf("Could not load image file\n");  
        exit(0);  
    }  
    // acquire image info  
    height    = img->height;    
    width     = img->width;    
    step      = img->widthStep;    
    channels  = img->nChannels;  
    data      = (uchar *)img->imageData;  
    // reverse image 
    #pragma omp parallel for collapse(3)
    for(i=0;i<height;i++)   
        for(j=0;j<width;j++)   
            for(k=0;k<channels;k++)  
                data[i*step+j*channels+k]=255-data[i*step+j*channels+k];
    //namedWindow("test.bmp", CV_WINDOW_AUTOSIZE );
    Mat im = img;
    cv::Mat output(im.size(),CV_8UC3,cv::Scalar(255,255,255));
    unsigned sz = fname.size();
    fname.resize(sz-4); // removin .bmp from the name to add transformation file
    std::string transformName ("_negative");
    std::string formatName (".bmp");
    std::string outputname = fname.c_str() + transformName + formatName;
    if(fg == 2){
      im.copyTo(output,img_mask); 
    } else{
      im.copyTo(output,~img_mask);
    }
    imwrite(outputname, output);    
    //cvShowImage("mainWin", img );  
    //cvWaitKey(0);  
    //cvReleaseImage( &img );  
    Rcpp::CharacterVector rline = Rcpp::wrap(outputname);
    return rline;
}
