/*#include <stdafx.h>*/
#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
 
using namespace cv;
using namespace std;


IplImage *img1;
IplImage *img;
IplImage *frame;
int select_flag = 0;
CvPoint point;
int drag = 0;
int key = 0;
int goback=0;
CvRect rect;
void mouseHandler(int event, int x, int y, int flags, void* param)
{
 
/* user press left button */
if (event == CV_EVENT_LBUTTONDOWN && !drag)
{
point = cvPoint(x, y);
drag = 1;
}
/* user drag the mouse */
if (event == CV_EVENT_MOUSEMOVE && drag)
{
img1 = cvCloneImage(frame);
cvRectangle(img1,point,cvPoint(x, y),CV_RGB(255, 0, 0),3,8,0);
cvShowImage("result", img1);
 
}
/* user release left button */
if (event == CV_EVENT_LBUTTONUP && drag)
{
rect = cvRect(point.x,point.y,x-point.x,y-point.y);
drag = 0;
goback=1;
}
 
/* user click right button: reset all */
if (event == CV_EVENT_RBUTTONUP)
{
drag = 0;
}
}
int main(int argc, char* argv[])
{

img=cvLoadImage(argv[1]);
frame=cvLoadImage(argv[1]);
Mat image(img);
  
cvShowImage("result",frame);
////////////////////////////////////77//cvWaitKey(0);
cvNamedWindow( "result", CV_WINDOW_AUTOSIZE );
int h=frame->height;
int w=frame->width;
if(goback==0)
{
cvSetMouseCallback("result", mouseHandler, NULL);
key = cvWaitKey(1);
cvShowImage("result", frame);
cvWaitKey(0);
}
 
printf("\n %d,%d",rect.x,rect.y);
cv::Rect rectangle(rect.x,rect.y,rect.width,rect.height);
cv::Mat result;
cv::Mat bgModel,fgModel;
 
cv::grabCut(image,result,rectangle,bgModel,fgModel,1,cv::GC_INIT_WITH_RECT);
cv::compare(result,cv::GC_PR_FGD,result,cv::CMP_EQ);
 
cv::Mat foreground(image.size(),CV_8UC3,cv::Scalar(255,255,255));
image.copyTo(foreground,result);
imwrite( "/home/explicarte/Downloads/backup/UCV/Proyecto/pdi_project/foreground_mask.jpg", result );
imwrite( "/home/explicarte/Downloads/backup/UCV/Proyecto/pdi_project/foreground.jpg", foreground );
imshow("output",foreground);

// added
Mat background;
image.copyTo(background,~result);
//added
imwrite("/home/explicarte/Downloads/backup/UCV/Proyecto/pdi_project/background_mask.jpg",~result);
imwrite("/home/explicarte/Downloads/backup/UCV/Proyecto/pdi_project/background.jpg",background);
cvWaitKey(0);
 
cvDestroyWindow("result");
cvReleaseImage(&img1);
 
return 0;
}
